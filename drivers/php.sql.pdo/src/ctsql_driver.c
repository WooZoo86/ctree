/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: FairCom Corporation                                          |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "pdo/php_pdo.h"
#include "pdo/php_pdo_driver.h"
#include "php_pdo_ctsql.h"
#include "php_pdo_ctsql_int.h"
#include "Zend/zend_exceptions.h"

CTSQLRET pdo_ctsql_error(CTSQLRET errorCd, char *errorMsg, pdo_dbh_t *dbh, pdo_stmt_t *stmt, char *what, const char *file, int line) /* {{{ */
{
	CTSQLRET ret;
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle*)dbh->driver_data;
	pdo_ctsql_error_info *einfo = &H->einfo;
	pdo_ctsql_stmt *S = NULL;
	pdo_error_type *pdo_err = &dbh->error_code;
	char retStr[16];

	if (stmt) {
		S = (pdo_ctsql_stmt*)stmt->driver_data;

		einfo = &S->einfo;
		pdo_err = &stmt->error_code;
	}

	/* if error is provided by the caller */
	if (errorCd) {
		einfo->errcode = ret = errorCd;
		strncpy(einfo->errmsg, errorMsg, MAX_ERRMSG_LEN);
	}

	/* if error is not provided, retrieve it from the database connection */
	else {
		einfo->errcode = ret = ctsqlGetError(H->conn);
		strncpy(einfo->errmsg, ctsqlGetErrorMessage(H->conn), MAX_ERRMSG_LEN);
	}
	sprintf(retStr, "%d", abs(ret));
	strncpy(einfo->state, retStr, 5);

	strncpy(einfo->what, what, MAX_ERRWHAT_LEN);
	einfo->file = file;
	einfo->line = line;

	/* set the errors information into the PDO handles */
	strcpy(dbh->error_code, einfo->state);
	if (stmt) 
		strcpy(stmt->error_code, einfo->state);

	if (!dbh->methods) {
		zend_throw_exception_ex(php_pdo_get_exception(), einfo->errcode, "SQLSTATE[%s] %s: %d %s",
			einfo->state, einfo->what, einfo->errcode, einfo->errmsg);
	}

	return ret;
}
/* }}} */

static int pdo_ctsql_fetch_error_func(pdo_dbh_t *dbh, pdo_stmt_t *stmt, zval *info) /* {{{ */
{
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle *)dbh->driver_data;
	pdo_ctsql_error_info *einfo;

	einfo = &H->einfo;

	if (stmt) {
		pdo_ctsql_stmt *S = (pdo_ctsql_stmt*)stmt->driver_data;

		if (S->einfo.errmsg)
			einfo = &S->einfo;
	}

	if (einfo->errcode) {
		add_next_index_long(info, einfo->errcode);
		add_next_index_string(info, einfo->errmsg);
	}

	return 1;
}
/* }}} */

static int ctsql_handle_closer(pdo_dbh_t *dbh) /* {{{ */
{
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle *)dbh->driver_data;
	if (H) {

		if (H->conn)
		{

			/* disconnect from server */
			if (ctsqlDisconnect(H->conn) != CTSQLRET_OK)
				pdo_ctsql_drv_error("ctsqlDisconnect");

			/* release connection resources */
			ctsqlFreeConnection(H->conn);
			H->conn = NULL;
		}
		pefree(H,dbh->is_persistent);
		dbh->driver_data = NULL;
	}
	return 0;
}
/* }}} */

static int ctsql_handle_preparer(pdo_dbh_t *dbh, const char *sql, size_t sql_len, pdo_stmt_t *stmt, zval *driver_options) /* {{{ */
{
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle *)dbh->driver_data;
	pdo_ctsql_stmt *S = ecalloc(1, sizeof(*S));
	int ret;
	char *nsql = NULL;
	size_t nsql_len = 0;

	S->H = H;
	S->cursor = NULL;

	/* allocate string buffer for column data */
	if (!(S->data = ecalloc(sizeof(CTSQLCHAR), INIT_COL_LEN))) {
		pdo_ctsql_stmt_error2(CTSQLRET_ALLOC_FAILED, "Not able to allocate data", "ctsql_handle_preparer");
		return 0;
	}
	S->data_size = INIT_COL_LEN;

	/* allocate data buffer for column data */
	if (!(S->buffer = ecalloc(1, 8))) {
		pdo_ctsql_stmt_error2(CTSQLRET_ALLOC_FAILED, "Not able to allocate buffer", "ctsql_handle_preparer");
		return 0;
	}
	S->buffer_size = 8;

	/* before we prepare, we need to peek at the query; if it uses named parameters,
	* we want PDO to rewrite them for us */
	stmt->supports_placeholders = PDO_PLACEHOLDER_POSITIONAL;
	ret = pdo_parse_params(stmt, (char*)sql, sql_len, &nsql, &nsql_len);

	if (ret == 1) {
		/* query was re-written */
		sql = nsql;
	}
	else if (ret == -1) {
		/* couldn't grok it */
		strcpy(dbh->error_code, stmt->error_code);
		efree(S);
		return 0;
	}

	ret = 0;

	/* allocate new command */
	if (!(S->cmd = ctsqlNewCommand(H->conn))) {
		pdo_ctsql_drv_error("ctsqlNewCommand");
		goto cleanup;
	}

	/* prepare SQL command */
	if (ctsqlPrepare(S->cmd, (CTSQLCHAR*)sql) != CTSQLRET_OK) {
		pdo_ctsql_drv_error("ctsqlPrepare");
		goto cleanup;
	}

	stmt->driver_data = S;
	stmt->methods = &ctsql_stmt_methods;
	ret = 1;

cleanup:
	if (nsql)
		efree(nsql);
	return ret;
}
/* }}} */

static zend_long ctsql_handle_doer(pdo_dbh_t *dbh, const char *sql, size_t sql_len) /* {{{ */
{
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle *)dbh->driver_data;
	zend_long rowcount = -1;
	pCTSQLCMD hCmd = NULL;

	/* allocate new command */
	if (!(hCmd = ctsqlNewCommand(H->conn))) {
		pdo_ctsql_drv_error("ctsqlNewCommand");
		goto cleanup;
	}

	/* prepare SQL command */
	if (ctsqlPrepare(hCmd, (CTSQLCHAR*)sql) != CTSQLRET_OK) {
		pdo_ctsql_drv_error("ctsqlPrepare");
		goto cleanup;
	}

	/* execute command */
	if (ctsqlExecute(hCmd, NULL) != CTSQLRET_OK) {
		pdo_ctsql_drv_error("ctsqlExecute");
		goto cleanup;
	}

	/* retrieve row count for the execution */
	rowcount = ctsqlAffectedRows(hCmd);

cleanup:
	/* release command resources */
	if (hCmd)
		ctsqlFreeCommand(hCmd);

	return rowcount;
}
/* }}} */

static int ctsql_handle_quoter(pdo_dbh_t *dbh, const char *unquoted, size_t unquotedlen, char **quoted, size_t *quotedlen, enum pdo_param_type paramtype ) /* {{{ */
{
	int qcount = 0;
	char const *cu, *l, *r;
	char *c;

	if (!unquotedlen) {
		*quotedlen = 2;
		*quoted = emalloc(*quotedlen+1);
		strcpy(*quoted, "''");
		return 1;
	}

	/* count single quotes */
	for (cu = unquoted; (cu = strchr(cu,'\'')); qcount++, cu++)
		; /* empty loop */

	*quotedlen = unquotedlen + qcount + 2;
	*quoted = c = emalloc(*quotedlen+1);
	*c++ = '\'';

	/* foreach (chunk that ends in a quote) */
	for (l = unquoted; (r = strchr(l,'\'')); l = r+1) {
		strncpy(c, l, r-l+1);
		c += (r-l+1);
		*c++ = '\'';			/* add second quote */
	}

    /* Copy remainder and add enclosing quote */
	strncpy(c, l, *quotedlen-(c-*quoted)-1);
	(*quoted)[*quotedlen-1] = '\'';
	(*quoted)[*quotedlen]   = '\0';

	return 1;
}
/* }}} */

static int ctsql_handle_begin(pdo_dbh_t *dbh) /* {{{ */
{
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle *)dbh->driver_data;
	/* is Autocommit on?  Need to disable it */
	if(dbh->auto_commit)
	{
		if (ctsqlSetAutoCommit(H->conn, CTSQL_FALSE) != CTSQLRET_OK) {
			pdo_ctsql_drv_error("ctsqlSetAutoCommit");
			return 0;
		}
	}
	/* start a new transaction  */
	if (ctsqlBegin(H->conn) != CTSQLRET_OK) {
		pdo_ctsql_drv_error("ctsqlBegin");
		return 0;
	}

	return 1;
}
/* }}} */

static int ctsql_handle_commit(pdo_dbh_t *dbh) /* {{{ */
{
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle *)dbh->driver_data;

	/* commit the current transaction  */
	if (ctsqlCommit(H->conn) != CTSQLRET_OK) {
		pdo_ctsql_drv_error("ctsqlCommit");
		return 0;
	}
	if(dbh->auto_commit)
	{
		if (ctsqlSetAutoCommit(H->conn, CTSQL_TRUE) != CTSQLRET_OK) {
			pdo_ctsql_drv_error("ctsqlSetAutoCommit");
			return 0;
		}
	}

	return 1;
}
/* }}} */

static int ctsql_handle_rollback(pdo_dbh_t *dbh) /* {{{ */
{
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle *)dbh->driver_data;

	/* abort the current transaction  */
	if (ctsqlAbort(H->conn) != CTSQLRET_OK) {
		pdo_ctsql_drv_error("ctsqlAbort");
		return 0;
	}
	if(dbh->auto_commit)
	{
		if (ctsqlSetAutoCommit(H->conn, CTSQL_TRUE) != CTSQLRET_OK) {
			pdo_ctsql_drv_error("ctsqlSetAutoCommit");
			return 0;
		}
	}

	return 1;
}
/* }}} */

static int ctsql_handle_set_attribute(pdo_dbh_t *dbh, zend_long attr, zval *val) /* {{{ */
{
	zend_long lval = zval_get_long(val);
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle *)dbh->driver_data;

	if (attr == PDO_ATTR_AUTOCOMMIT) {
		/* set auto-commit attribute */
		if (ctsqlSetAutoCommit(H->conn, (BIT)lval) != CTSQLRET_OK) {
			pdo_ctsql_drv_error("ctsqlSetAutoCommit");
			return 0;
		}
		return 1;
	}

	return 0;
}
/* }}} */

static int ctsql_handle_get_attribute(pdo_dbh_t *dbh, zend_long attr, zval *return_value)  /* {{{ */
{
	pdo_ctsql_db_handle *H = (pdo_ctsql_db_handle *)dbh->driver_data;

	switch (attr) {

		case PDO_ATTR_AUTOCOMMIT:
			/* retrieve auto-commit attribute */
			ZVAL_BOOL(return_value, ctsqlGetAutoCommit(H->conn));
			return 1;

		default:
			return 0;

	}

	return 0;

}
/* }}} */

static struct pdo_dbh_methods ctsql_methods = {
	ctsql_handle_closer,
	ctsql_handle_preparer,
	ctsql_handle_doer,
	ctsql_handle_quoter,
	ctsql_handle_begin,
	ctsql_handle_commit,
	ctsql_handle_rollback,
	ctsql_handle_set_attribute,
	NULL,   /* last id */
	pdo_ctsql_fetch_error_func,
	ctsql_handle_get_attribute,
	NULL,   /* check_liveness */
	NULL	/* get_driver_methods */
};

static int pdo_ctsql_handle_factory(pdo_dbh_t *dbh, zval *driver_options) /* {{{ */
{
	int ret = 0;
	pdo_ctsql_db_handle *sess;
	char connStr[256];
	int i;
	struct pdo_data_src_parser vars[] = {
		{ "port",   "6597",	0 },
		{ "host",   "local",	0 },
		{ "dbname", "ctreeSQL",	0 },
		{ "ssl",    NULL,   	0}
	};

	if (!(sess = pecalloc(1, sizeof(*sess), dbh->is_persistent))) {
		pdo_ctsql_init_error(CTSQLRET_ALLOC_FAILED, "Not able to allocate session", "pecalloc");
		goto cleanup;
	}

	memset(sess, 0, sizeof(*sess));
	dbh->driver_data = sess;

	/* build the connection string */
	php_pdo_parse_data_source(dbh->data_source, dbh->data_source_len, vars, 4);
	sprintf(connStr, "%s@%s:%s", vars[0].optval, vars[1].optval, vars[2].optval);

	/* allocate connection handle */
	if ((sess->conn = ctsqlNewConnection()) == NULL) {
		pdo_ctsql_init_error(CTSQLRET_ALLOC_FAILED, "Not able to allocate connection handle", "ctsqlNewConnection");
		goto cleanup;
	}

	/* set SSL */
	if (vars[3].optval != NULL) {
		if (ctsqlSetSSL(sess->conn, vars[3].optval) != CTSQLRET_OK) {
			pdo_ctsql_drv_error("ctsqlSetSSL");
			goto cleanup;
		}
	}
	/* connect to server */
	if (ctsqlConnect(sess->conn, connStr, dbh->username, dbh->password) != CTSQLRET_OK) {
		pdo_ctsql_drv_error("ctsqlConnect");
		goto cleanup;
	}

	/* enable autocommit */
	if (ctsqlSetAutoCommit(sess->conn, CTSQL_TRUE) != CTSQLRET_OK) {
		pdo_ctsql_drv_error("ctsqlSetAutoCommit");
		goto cleanup;
	}

	dbh->methods = &ctsql_methods;
	dbh->alloc_own_columns = 1;
	dbh->native_case = PDO_CASE_NATURAL;

	ret = 1;

cleanup:
	for (i = 0; i < sizeof(vars) / sizeof(vars[0]); i++) {
		if (vars[i].freeme) {
			efree(vars[i].optval);
		}
	}

	if (!ret)
		ctsql_handle_closer(dbh);

	return ret;
}
/* }}} */

pdo_driver_t pdo_ctsql_driver = {
	PDO_DRIVER_HEADER(ctsql),
	pdo_ctsql_handle_factory
};
/* }}} */
