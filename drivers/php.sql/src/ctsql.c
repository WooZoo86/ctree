#define FAIRCOM_MOD
#define FAIRCOM_CODE
#ifdef ZEND_WIN32
#include "ctsql_lib.h"
#include "sql_lib.h"
#endif
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_ini.h"
#ifndef ZEND_WIN32
#include "ctsql_lib.h"
#include "sql_lib.h"
#endif
#include "ctsql.h"

#ifdef ZEND_ENGINE_2
#include "zend_exceptions.h"
#else
/* PHP 4 compatibility */
# define OnUpdateLong	OnUpdateInt
#endif

/* If you declare any globals in ctsql.h uncomment this: */
ZEND_DECLARE_MODULE_GLOBALS(ctsql)


/* True global resources - no need for thread safety here */
static int le_connection;
#ifdef NOT_YET
static int le_pconnection;
#endif
static int le_queries;

unsigned long conn_counter=0;

/* Every user visible function must have an entry in ctsql_functions[].
*/
zend_function_entry ctsql_functions[] = {
	ZEND_FE(ctsql_connect,		NULL)
	ZEND_FE(ctsql_pconnect,		NULL)
	ZEND_FE(ctsql_close,		NULL)
	ZEND_FE(ctsql_errno,		NULL)
	ZEND_FE(ctsql_error,		NULL)
	ZEND_FE(ctsql_errpos,		NULL)
	ZEND_FE(ctsql_query,		NULL)
	ZEND_FE(ctsql_commit,		NULL)
	ZEND_FE(ctsql_rollback,		NULL)
	ZEND_FE(ctsql_fetch_assoc,	NULL)
	ZEND_FE(ctsql_fetch_row,	NULL)
	ZEND_FE(ctsql_fetch_object,	NULL)
	ZEND_FE(ctsql_fetch_array,	NULL)
	ZEND_FE(ctsql_free_result,	NULL)
	ZEND_FE(ctsql_num_fields,	NULL)
	ZEND_FE(ctsql_field_name,	NULL)
	ZEND_FE(ctsql_field_len,	NULL)
	ZEND_FE(ctsql_field_table,	NULL)
	ZEND_FE(ctsql_field_type,	NULL)
	ZEND_FE(ctsql_affected_rows,NULL)
	ZEND_FE(ctsql_end_of_fetch,	NULL)
	ZEND_FE(ctsql_field_info,	NULL)
	{NULL, NULL, NULL}	/* Must be the last line in ctsql_functions[] */
};

zend_module_entry ctsql_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    	STANDARD_MODULE_HEADER,
#endif
	"ctsql",
	ctsql_functions,
	ZEND_MINIT(ctsql),
	ZEND_MSHUTDOWN(ctsql),
	ZEND_RINIT(ctsql),		/* Replace with NULL if there's nothing to do at request start */
	ZEND_RSHUTDOWN(ctsql),	/* Replace with NULL if there's nothing to do at request end */
	ZEND_MINFO(ctsql),
#if ZEND_MODULE_API_NO >= 20010901
    	DRIVER_VERSION,          /* extension version number (string) */
#endif
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_CTSQL
ZEND_GET_MODULE(ctsql)
#endif


PHP_INI_BEGIN()
	/* we use STD_PHP_INI_* when need to update a variable PHP_INI_ENTRY otherwise */
	STD_PHP_INI_BOOLEAN("ctsql.allow_persistent","0",PHP_INI_SYSTEM,OnUpdateLong,allow_persistent,zend_ctsql_globals,ctsql_globals)
	PHP_INI_ENTRY("ctsql.default_port", "6597", PHP_INI_ALL, NULL)
	PHP_INI_ENTRY("ctsql.default_host", "localhost", PHP_INI_ALL, NULL)
	PHP_INI_ENTRY("ctsql.default_database", "ctreeSQL", PHP_INI_ALL, NULL)
	PHP_INI_ENTRY("ctsql.default_user", "admin", PHP_INI_ALL, NULL)
	PHP_INI_ENTRY("ctsql.default_password", "ADMIN", PHP_INI_ALL, NULL)
	STD_PHP_INI_ENTRY ("ctsql.rowsperfetch", "20", PHP_INI_ALL, OnUpdateLong, rowfetches,zend_ctsql_globals,ctsql_globals)
	STD_PHP_INI_ENTRY("ctsql.internal_debug_level","0",PHP_INI_SYSTEM, OnUpdateLong, php_ctsql_debug,zend_ctsql_globals,ctsql_globals)
	STD_PHP_INI_ENTRY ("ctsql.compatibility.error100", "0", PHP_INI_ALL, OnUpdateLong, exec_error_100,zend_ctsql_globals,ctsql_globals)
	STD_PHP_INI_ENTRY ("ctsql.querytimeout", "0", PHP_INI_ALL, OnUpdateLong, query_timeout,zend_ctsql_globals,ctsql_globals)
PHP_INI_END()


void *mymalloc (long size)
{
	void *tmp;
	tmp = emalloc(size);
	return (tmp);
}

void myfree (void **ptr)
{
	efree(*ptr);
	*ptr=NULL;
}

char *mystrdup(char* str)
{
	char *tmp;
	tmp = estrdup(str);
	return (tmp);
}

static void php_ctsql_init_globals(zend_ctsql_globals *globals)
{
#ifdef CURRQUERY
	globals->curr_qry = 0;
#endif
	globals->curr_conn = 0;
	globals->env = NULL;
	globals->curr_sqlca=NULL;
	globals->conn_ptr=NULL;
}


void _free_conn (struct connection *conn) 
{
	dh_sqlenv_hdl_t env = conn->env;
	struct sqlca *sqlca = conn ->sqlca;
	char *connection_name = conn->connection_name;

	dh_tm_mark_abort(env,dh_get_curtmhdl(env),sqlca);
	dh_tm_end_trans(env,dh_get_curtmhdl(env),sqlca);
	dh_sql_disconnect(env,SQL_DISCONNECT_CONNECTION,connection_name,sqlca);

	myfree((void **)&connection_name);
	dh_free_sqlenv(env);
	myfree((void **)&sqlca);
	myfree((void **)&conn);
}


void _free_query (struct query* qry) 
{
	if (qry) {
		SqldFree(qry);
		if (qry->tpe_puuid) {
			myfree((void **)&qry->tpe_puuid);
		}
		myfree((void **)&qry);
	}
}

void query_res_desctructor (zend_rsrc_list_entry *rsrc TSRMLS_DC) 
{
	struct query* qry= (struct query*)rsrc->ptr;
	_free_query (qry);
}

void conn_res_desctructor (zend_rsrc_list_entry *rsrc TSRMLS_DC) 
{
	struct connection *conn= (struct connection *)rsrc->ptr;
	_free_conn (conn);
}


ZEND_MINIT_FUNCTION(ctsql)
{

	ZEND_INIT_MODULE_GLOBALS(ctsql, php_ctsql_init_globals, NULL);
	
	REGISTER_INI_ENTRIES();
	
	le_connection = zend_register_list_destructors_ex(conn_res_desctructor, NULL,"connections",module_number);
	le_queries = zend_register_list_destructors_ex(query_res_desctructor, NULL,"queries",module_number);

	return SUCCESS;
}

ZEND_MSHUTDOWN_FUNCTION(ctsql)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

/* Remove if there's nothing to do at request start */
ZEND_RINIT_FUNCTION(ctsql)
{

	Ct_LS_FETCH()
	GSQLENV=NULL;
	GCONNECTION = 0;
	GCONN_PTR = NULL;
	ctSetErrorCode(0);
	ctSetErrorDesc("");
	ctSetErrorPos(0);
	return SUCCESS;
}

/* Remove if there's nothing to do at request end */
ZEND_RSHUTDOWN_FUNCTION(ctsql)
{
	Ct_LS_FETCH()
	return SUCCESS;
}

ZEND_MINFO_FUNCTION(ctsql)
{
	PHPAPI void php_info_print_table_row(int num_cols, ...);
	PHPAPI void php_info_print_table_start(void);
	PHPAPI void php_info_print_table_end(void);
	
	php_info_print_table_start();
	php_info_print_table_row(2, "ctree SQL support", "enabled");
	php_info_print_table_end();
	
	/* we do not whant php.ini entries to be displaied */
	/* DISPLAY_INI_ENTRIES(); */
}

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto resource ctsql_connect([string dbname [, string username [, string password]]])
	Open a connection to a c-tree SQL Server
*/
ZEND_FUNCTION(ctsql_connect)
{
	php_ctsql_connect(INTERNAL_FUNCTION_PARAM_PASSTHRU,0);
}
/* }}} */

/* {{{ proto resource ctsql_pconnect([string [dbname [, string username [, string password]]])
	Open a connection to a c-tree SQL Server
*/
ZEND_FUNCTION(ctsql_pconnect) 
{
	php_ctsql_connect(INTERNAL_FUNCTION_PARAM_PASSTHRU,1);
}
/* }}} */

/* {{{ proto int ctsql_close [resource connectionID])
	Close a c-tree SQL connection 
*/
ZEND_FUNCTION(ctsql_close)
{
	zval **param;
	int resv;
	Ct_LS_FETCH()
	lval_t connection = GCONNECTION;

	resv = ZEND_NUM_ARGS();

	switch (resv) {
	case 1:
		if (zend_get_parameters_ex(1,&param)!= SUCCESS)
			WRONG_PARAM_COUNT;

		if (!isResource(*param)) {
			ctSetErrorCode(WRONG_CONN_ID);
			RETURN_FALSE;
		}
		convert_to_long_ex(param);
		connection = Z_LVAL_PP(param);

	case 0:
		break;
	default:
		WRONG_PARAM_COUNT;
	}
	
	if (!SwitchConnection(connection))
		RETURN_FALSE;
	
	zend_list_delete(GCONNECTION);
	ctInvalidateConnection();
	RETURN_TRUE;
}
/* }}} */

/* {{{ proto string ctsql_error()
	Returns the text of the error message from previous c-tree SQL operation 
*/
ZEND_FUNCTION(ctsql_error)
{
	Ct_LS_FETCH()
	
	DebugLog("ctsql_error", "", (int)return_value);
	switch (ctGetErrorCode())
	{
	case 0:
		RETURN_EMPTY_STRING();
	case WRONG_CONN_ID:
		RETURN_STRINGL("Wrong connection ID",19,1);
	case WRONG_QUERY_ID:
		RETURN_STRINGL("Wrong QueryResult ID",20,1);
	case SQL_ERR_NOTOPENED:
		RETURN_STRINGL("Cursor not opened",17,1);
	default:
		if (PSQLCA)
		{
			RETURN_STRINGL(PSQLCA->sqlerrm,PSQLCA->sqlerrml,1);
		}
		else
		{
			RETURN_STRING(ctGetErrorDesc(),1);
			//RETURN_EMPTY_STRING();
		}
	}
}
/* }}} */

/* {{{ proto int ctsql_errno()
	Returns the number of the error message from previous c-tree SQL operation
*/
ZEND_FUNCTION(ctsql_errno)
{
	Ct_LS_FETCH()
	long rc = ctGetErrorCode();

	DebugLog("ctsql_errno", "", (int)return_value);

	RETURN_LONG(rc);
}
/* }}} */

/* {{{ proto int ctsql_errpos()
	Returns the position of the error from previous c-tree SQL operation
*/
ZEND_FUNCTION(ctsql_errpos)
{
	Ct_LS_FETCH()
	long rc = ctGetErrorPos();

	DebugLog("ctsql_errpos", "", (int)return_value);

	RETURN_LONG(rc);
}
/* }}} */

/* {{{ proto resource ctsql_query(string query [, int connectionID])
	Send an SQL query to c-tree SQL returns TRUE (non-zero) or FALSE to indicate 
whether or not the query succeeded. For SELECT statements, ctsql_query() returns
a new query identifier.
*/
ZEND_FUNCTION(ctsql_query)
{
	zval **params[2];
	int resv;
	Ct_LS_FETCH()
	dh_char_t *sql_qry=NULL;
	struct query *tmp_qry;
	int rsqry;

	resv = ZEND_NUM_ARGS();
	DebugLog("ctsql_query","resv",resv);
	
	if (resv > 2 || zend_get_parameters_array_ex(resv,params)!= SUCCESS)
			WRONG_PARAM_COUNT;

	tmp_qry = mymalloc(sizeof(struct query));
	if (tmp_qry == NULL) {
		zend_error(E_ERROR, "memory allocation error");	
		goto error;
	}
	
	tmp_qry->fetched=0;
	tmp_qry->no_more=0;
	tmp_qry->sql_alloc=0;
	tmp_qry->sqldaptr=NULL;
	tmp_qry->tofetch=0;
	tmp_qry->tpe_pcur=NULL;
	tmp_qry->tpe_puuid=NULL;
	tmp_qry->conn = GCONNECTION;
	tmp_qry->tran_no = 0;

	switch (resv) {
	case 2:
		if (!isResource(*params[1])) {
			ctSetErrorCode(WRONG_CONN_ID);
			goto error;
		}
		convert_to_long_ex(params[1]);
		tmp_qry->conn=Z_LVAL_PP(params[1]);	
	case 1:
		convert_to_string_ex(params[0]);
		sql_qry = mystrdup(Z_STRVAL_PP(params[0]));
		break;
	default:
		WRONG_PARAM_COUNT;
		goto error;
	}	

	if (!SwitchConnection(tmp_qry->conn))
		goto error;
	DebugLog("ctsql_query",sql_qry,0);
	
	if (GCONN_PTR)
	{
		tmp_qry->tran_no = GCONN_PTR->tran_no;
	}
	rsqry = doquery(tmp_qry,sql_qry);
	myfree((void **)&sql_qry);
	switch (rsqry) {
		case QUERY_FETCH:
#if ZEND_MODULE_API_NO >= 20100525
			resv = zend_list_insert(tmp_qry,le_queries TSRMLS_CC);
#else
			resv = zend_list_insert(tmp_qry,le_queries);
#endif
#ifdef CURRQUERY
			GQUERY = resv;
#endif
			RETURN_RESOURCE(resv);
			break;
		case QUERY_ERROR:
			goto error;
			break;
		case QUERY_MEMORY:
			zend_error(E_ERROR, "memory allocation error");
			goto error;
			break;
		case QUERY_DONE:
#ifdef CURRQUERY
			ctInvalidateQuery();
#endif
			_free_query(tmp_qry);
			tmp_qry=NULL;
			RETURN_TRUE;
			break;
	}
error:
#ifdef CURRQUERY
	ctInvalidateQuery();
#endif
	_free_query(tmp_qry);
	tmp_qry=NULL;
	if (sql_qry)
	{
		myfree((void **)&sql_qry);
	}
	RETURN_FALSE;
}
/* }}} */


/* {{{ proto bool ctsql_commit([int connectionID])
	commit a transaction 
*/
ZEND_FUNCTION(ctsql_commit)
{
	zval **param;
	int resv;
	Ct_LS_FETCH()
	lval_t connection = GCONNECTION;

	resv = ZEND_NUM_ARGS();

	switch (resv) {
	case 1:
		if (zend_get_parameters_ex(1,&param)!= SUCCESS)
			WRONG_PARAM_COUNT;
		if (!isResource(*param)) {
			ctSetErrorCode(WRONG_CONN_ID);
			goto error;
		}
		convert_to_long_ex(param);
		connection = Z_LVAL_PP(param);
	case 0:
		break;
	default:
		WRONG_PARAM_COUNT;
	}
	if (!SwitchConnection(connection))
		RETURN_FALSE;
	dh_tm_end_trans(GSQLENV,dh_get_curtmhdl(GSQLENV),PSQLCA);
	ctSetErrorCode(PSQLCA->sqlcode);
	ctSetErrorDesc(PSQLCA->sqlerrm);
	ctSetErrorPos(PSQLCA->sqlerrd[4]);

	if (PSQLCA->sqlcode != 0){		
		goto errorl;
	}
	if (GCONN_PTR)
		GCONN_PTR->tran_no++;
		
	RETURN_TRUE;

errorl:
error:
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto int ctsql_rollback([int connectionID])
	abort a transaction
*/
ZEND_FUNCTION(ctsql_rollback)
{
	 
	Ct_LS_FETCH()
	zval **param;
	int resv;
	lval_t connection = GCONNECTION;
	struct connection *conn_ptr= GCONN_PTR;
	resv = ZEND_NUM_ARGS();

	switch (resv) {
	case 1:
		if (zend_get_parameters_ex(1,&param)!= SUCCESS)
			WRONG_PARAM_COUNT;
		if (!isResource(*param)) {
			ctSetErrorCode(WRONG_CONN_ID);
			goto error;
		}
		convert_to_long_ex(param);
		connection = Z_LVAL_PP(param);
	case 0:
		break;
	default:
		WRONG_PARAM_COUNT;
	}

	if (!SwitchConnection(connection))
		RETURN_FALSE;
	dh_tm_mark_abort(GSQLENV,dh_get_curtmhdl(GSQLENV),PSQLCA);
	ctSetErrorCode(PSQLCA->sqlcode);
	ctSetErrorDesc(PSQLCA->sqlerrm);
	ctSetErrorPos(PSQLCA->sqlerrd[4]);

	if (PSQLCA->sqlcode != 0){
		goto errorl;
	}
	dh_tm_end_trans(GSQLENV,dh_get_curtmhdl(GSQLENV),PSQLCA);
	ctSetErrorCode(PSQLCA->sqlcode);
	ctSetErrorDesc(PSQLCA->sqlerrm);
	ctSetErrorPos(PSQLCA->sqlerrd[4]);

	if (PSQLCA->sqlcode != 0){
		goto errorl;
	}
	
	if (GCONN_PTR)
		GCONN_PTR->tran_no++;

	RETURN_TRUE;

errorl:
error:
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto array ctsql_fetch_assoc(resource queryID)
   Fetch a result row as an associative array */

ZEND_FUNCTION(ctsql_fetch_assoc) {
	php_ctsql_fetch(INTERNAL_FUNCTION_PARAM_PASSTHRU, ASSOCIATIVE);
}
/* }}} */

/* {{{ proto array ctsql_fetch_row(resource queryID)
   Fetch a result row as an enumerated array */

ZEND_FUNCTION(ctsql_fetch_row) {
	php_ctsql_fetch(INTERNAL_FUNCTION_PARAM_PASSTHRU, ENUMERATED);
}
/* }}} */

/* {{{ proto array ctsql_fetch_object(resource queryID)
   Fetch a result row as an object */

ZEND_FUNCTION(ctsql_fetch_object) {
	php_ctsql_fetch(INTERNAL_FUNCTION_PARAM_PASSTHRU, OBJECT);
#ifdef OLD_CODE
	if (return_value->type==IS_ARRAY) {
		return_value->type=IS_OBJECT;
		return_value->value.obj.properties = return_value->value.ht;
		return_value->value.obj.ce = &zend_standard_class_def;
	}
#else
	if (Z_TYPE_P(return_value) == IS_ARRAY) {
		object_and_properties_init(return_value, ZEND_STANDARD_CLASS_DEF_PTR, Z_ARRVAL_P(return_value));
	}
#endif
}
/* }}} */

/* {{{ proto array ctsql_fetch_array(resource queryID)
   Fetch a result row as an array (both associative and numeric)*/

ZEND_FUNCTION(ctsql_fetch_array) {
	php_ctsql_fetch(INTERNAL_FUNCTION_PARAM_PASSTHRU, BOTH);
}
/* }}} */

/* {{{ proto void ctsql_free_result(resource queryID)
	Free result memory
*/
ZEND_FUNCTION(ctsql_free_result)
{
	Ct_LS_FETCH()
	zval **param;
	int resv;
	struct query *curr_qry;
	lval_t cqry;

	resv = ZEND_NUM_ARGS();
	switch (resv) {
	case 1:
		if (zend_get_parameters_ex(1,&param)!=SUCCESS)
			WRONG_PARAM_COUNT;

		if (!isResource(*param)) {
			ctSetErrorCode(WRONG_CONN_ID);
			goto error;
		}
		convert_to_long_ex(param);
		cqry = Z_LVAL_PP(param);
		break;
#ifdef CURRQUERY
	case 0:
		cqry = GQUERY;
		break;
#endif
	default:
		WRONG_PARAM_COUNT;
	}
	
	curr_qry = SwitchQuery(cqry);
	if (curr_qry==NULL) {
		goto error;
	}
	
	dh_sqlclose(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),curr_qry->tpe_pcur,PSQLCA);
	dh_release_cursor(GSQLENV,(tpe_cursor_type*) &curr_qry->tpe_pcur);
	ctSetErrorCode(PSQLCA->sqlcode);
	ctSetErrorDesc(PSQLCA->sqlerrm);
	ctSetErrorPos(PSQLCA->sqlerrd[4]);
	if (!PSQLCA->sqlcode)
	{
		zend_list_delete(cqry);
#ifdef CURRQUERY
		ctInvalidateQuery();
#endif
	}
	return;
error:
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto int ctsql_num_fields(resource queryID)
	Get number of fields in a query
*/
ZEND_FUNCTION(ctsql_num_fields)
{
	Ct_LS_FETCH()
	zval **param;
	int resv;
	struct query *curr_qry;
	lval_t cqry;
	
	
	resv = ZEND_NUM_ARGS();
	
	switch (resv) {
	case 1:
		if (zend_get_parameters_ex(1,&param)!=SUCCESS)
			WRONG_PARAM_COUNT;

		if (!isResource(*param)) {
			ctSetErrorCode(WRONG_QUERY_ID);
			goto error;
		}
		convert_to_long_ex(param);
		cqry = Z_LVAL_PP(param);
		break;
#ifdef CURRQUERY
	case 0:
		cqry = GQUERY;
		break;
#endif
	default:
		WRONG_PARAM_COUNT;
	}
	
	curr_qry = SwitchQuery(cqry);
	if (curr_qry==NULL)
		goto error;
		
	RETURN_LONG(curr_qry->sqldaptr->sqld_nvars);
error:
	RETURN_FALSE;
}
/* }}} */

/* {{{ proto string ctsql_field_name( resource queryID, int field_number)
	Get the name of the specified field in a query
*/
ZEND_FUNCTION(ctsql_field_name)
{
	php_ctsql_field_info(INTERNAL_FUNCTION_PARAM_PASSTHRU,FIELD_NAME);
}
/* }}} */

/* {{{ proto int ctsql_field_len( resource queryID, int field_number)
	Get the length of the specified field in a query
*/
ZEND_FUNCTION(ctsql_field_len)
{
	php_ctsql_field_info(INTERNAL_FUNCTION_PARAM_PASSTHRU,FIELD_LEN);
}
/* }}} */

/* {{{ proto string ctsql_field_table( resource queryID, int field_number)
	Get name of the table the specified field is in
*/
ZEND_FUNCTION(ctsql_field_table)
{
	php_ctsql_field_info(INTERNAL_FUNCTION_PARAM_PASSTHRU,FIELD_TABLE);
}

/*}}} */

/* {{{ proto string ctsql_field_type( resource queryID, int field_number)
	Get the type of the specified field in a result
*/
ZEND_FUNCTION(ctsql_field_type)
{
	php_ctsql_field_info(INTERNAL_FUNCTION_PARAM_PASSTHRU,FIELD_TYPE);
}
/* }}} */

/* {{{ proto int ctsql_affected_rows([resource connectionID])
	Get the type of the specified field in a result
*/
ZEND_FUNCTION(ctsql_affected_rows)
{
	zval **param;
	int resv;
	Ct_LS_FETCH()
	lval_t tmp_conn;

	resv = ZEND_NUM_ARGS();

	switch (resv) {
	case 1:
		if (zend_get_parameters_ex(1,&param)!= SUCCESS)
			WRONG_PARAM_COUNT;

		if (!isResource(*param)) {
			ctSetErrorCode(WRONG_CONN_ID);
			RETURN_FALSE;
		}
		convert_to_long_ex(param);
		tmp_conn = Z_LVAL_PP(param);
	case 0:
		tmp_conn = GCONNECTION;
		break;
	default:
		WRONG_PARAM_COUNT;
	}
	
	if(!SwitchConnection(tmp_conn))
		RETURN_FALSE;
		
	RETURN_LONG(PSQLCA->sqlerrd[2]);
}

/* }}} */

/* {{{ proto bool ctsql_end_of_fetch(resource QueryID)
	returns true in case of no more rows to fetch or error
*/
ZEND_FUNCTION(ctsql_end_of_fetch)
{
	zval **param;
	int resv;
	struct query *curr_qry;
	lval_t cqry;
	Ct_LS_FETCH()

	resv = ZEND_NUM_ARGS();
	
	switch (resv) {
		case 1:
			if (zend_get_parameters_ex(1,&param)!=SUCCESS)
				WRONG_PARAM_COUNT;
			if (!isResource(*param)) {
				ctSetErrorCode(WRONG_QUERY_ID);
				RETURN_TRUE;
			}
			convert_to_long_ex(param);
			cqry = Z_LVAL_PP(param);
			break;
#ifdef CURRQUERY
		case 0:
			cqry = GQUERY;
			break;
#endif
		default:
			WRONG_PARAM_COUNT;
	}

	curr_qry = SwitchQuery(cqry);
	
	if (!curr_qry) {
		ctSetErrorCode(WRONG_QUERY_ID);
		RETURN_TRUE;
	}

	if (curr_qry->sqldaptr==NULL) {
		ctSetErrorCode(WRONG_QUERY_ID);
		RETURN_TRUE;	
	}
	
	if (curr_qry->tofetch == 0)
	{
		AllocFetchMem(curr_qry, (short) Ct_G(rowfetches));

		if (curr_qry->sql_alloc==0) {
			zend_error(E_ERROR, "memory allocation error");
			RETURN_TRUE;
		}

		if (sql_fetch (curr_qry)!= SUCCESS) {
			FreeFetchMem(curr_qry);
			RETURN_TRUE;
		}	
	}	
	
	if (curr_qry->tofetch != 0)
	{
		RETURN_FALSE;
	}
	
	RETURN_TRUE;
}

/* }}} */

/* {{{ proto array ctsql_field_info(resource queryID, int field_number)
	Get the info (length, type etc.) of the specified field in a query
*/
ZEND_FUNCTION(ctsql_field_info) {
	zval **params[2];
	Ct_LS_FETCH()
	int resv;
	struct query *curr_qry;
	struct sqlda *sqldap;
	lval_t idx;
	lval_t cqry;
		dh_i32_t len;



	resv = ZEND_NUM_ARGS();
	if (zend_get_parameters_array_ex(resv,params)!= SUCCESS)
			WRONG_PARAM_COUNT;

#ifdef CURRQUERY
	cqry = GQUERY;
#endif
	switch (resv) {
#ifdef CURRQUERY
		case 2:
			if (!isResource(*params[1])) {
				ctSetErrorCode(WRONG_QUERY_ID);
				RETURN_FALSE;
			}
			convert_to_long_ex(params[1]);
			cqry = Z_LVAL_PP(params[1]);

		case 1:
			convert_to_long_ex(params[0]);		
			idx = Z_LVAL_PP(params[0]);
			break;
#else
		case 2:
			if (!isResource(*params[0])) {
				ctSetErrorCode(WRONG_QUERY_ID);
				RETURN_FALSE;
			}
			convert_to_long_ex(params[0]);
			cqry = Z_LVAL_PP(params[0]);
			convert_to_long_ex(params[1]);		
			idx = Z_LVAL_PP(params[1]);
			break;
#endif
		default:
			WRONG_PARAM_COUNT;
	}
	
	curr_qry = SwitchQuery(cqry);
	
	if (!curr_qry) {
		RETURN_FALSE;
	}
	sqldap = curr_qry->sqldaptr;
	if (sqldap==NULL) {
		ctSetErrorCode(WRONG_QUERY_ID);
		RETURN_FALSE;
	}
	
	if ( array_init(return_value) != SUCCESS ) {
		FreeFetchMem(curr_qry);
		zend_error(E_ERROR, "Internal Error #1");
		RETURN_FALSE;
	}

	add_assoc_string(return_value, "name", sqldap->sqld_varnames[idx], 1);
	switch (sqldap->sqld_types[idx])
			{
				case TPE_DT_LVC:      
				case TPE_DT_CHAR:
				case TPE_DT_VARCHAR:
					len = sqldap->sqld_lengths[idx]-1;
					break;
				default:
					len = sqldap->sqld_lengths[idx];
			}
	add_assoc_long(return_value, "len", len);
	add_assoc_string(return_value, "type", type2strex(sqldap->sqld_types[idx]), 1);
	add_assoc_long(return_value, "scale", sqldap->sqld_scale[idx]);
	add_assoc_long(return_value, "precision", sqldap->sqld_precision[idx]);
	add_assoc_bool(return_value, "nullflag", sqldap->sqld_flags[idx] == 1 ? 1 : 0 );
	return;
}


/*--------------------*/
/* INTERNAL FUNCTIONS */
/*--------------------*/

void php_ctsql_field_info(INTERNAL_FUNCTION_PARAMETERS, int result_type)
{
	zval **params[2];
	Ct_LS_FETCH()
	int resv;
	struct query *curr_qry;
	struct sqlda *sqldap;
	lval_t idx;
	lval_t cqry;


	resv = ZEND_NUM_ARGS();
	if (zend_get_parameters_array_ex(resv,params)!= SUCCESS)
			WRONG_PARAM_COUNT;

#ifdef CURRQUERY
	cqry = GQUERY;
#endif
	switch (resv) {
#ifdef CURRQUERY
		case 2:
			if (!isResource(*params[1])) {
				ctSetErrorCode(WRONG_QUERY_ID);
				goto error;
			}
			convert_to_long_ex(params[1]);
			cqry = Z_LVAL_PP(params[1]);

		case 1:
			convert_to_long_ex(params[0]);		
			idx = Z_LVAL_PP(params[0]);
			break;
#else
		case 2:
			if (!isResource(*params[0])) {
				ctSetErrorCode(WRONG_QUERY_ID);
				goto error;
			}
			convert_to_long_ex(params[0]);
			cqry = Z_LVAL_PP(params[0]);
			convert_to_long_ex(params[1]);		
			idx = Z_LVAL_PP(params[1]);
			break;
#endif
		default:
			WRONG_PARAM_COUNT;
	}
	
	curr_qry = SwitchQuery(cqry);
	
	if (!curr_qry) {
		goto error;
	}
	sqldap = curr_qry->sqldaptr;
	if (sqldap==NULL) {
		ctSetErrorCode(WRONG_QUERY_ID);
		goto error;	
	}
	switch (result_type) {
		case FIELD_NAME:
			RETURN_STRING(sqldap->sqld_varnames[idx],1);
			break;
		case FIELD_LEN:
			switch (sqldap->sqld_types[idx])
			{
				case TPE_DT_LVC:      
				case TPE_DT_CHAR:
				case TPE_DT_VARCHAR:
					RETURN_LONG(sqldap->sqld_lengths[idx]-1);
					break;
				default:
					RETURN_LONG(sqldap->sqld_lengths[idx]);
			}
			
			break;
		case FIELD_TYPE:
			RETURN_STRING(type2str(sqldap->sqld_types[idx]),1);
			break;
		case FIELD_TABLE:
			RETURN_STRING(sqldap->sqld_table_name[idx],1);
			break;
	}
error:
	RETURN_FALSE;
};


void php_ctsql_connect(INTERNAL_FUNCTION_PARAMETERS,int persistent)
{
	zval **params[3];
	int resv;
	dh_char_t conn[TPE_MAX_CONNLEN_P1];
	
	struct sqlca *sqlca=NULL;
	char tpe_uname[TPE_UNAME_LEN_P1];
	char tpe_pword[TPE_UNAME_LEN_P1];
	struct connection *tmp_conn;
	dh_char_t *conn_name;

	Ct_LS_FETCH()
	tpe_uname[0]='\0';
	tpe_pword[0]='\0';

	resv = ZEND_NUM_ARGS();
	if ( resv > 3 || (zend_get_parameters_array_ex(resv,params)!= SUCCESS))
			WRONG_PARAM_COUNT;
	
	sqlca = mymalloc(sizeof(struct sqlca));
	if (sqlca == NULL) {
		zend_error(E_ERROR, "memory allocation error");
		goto error;
	}
	memset(sqlca,0,sizeof(struct sqlca));
	
	tmp_conn = mymalloc(sizeof(struct connection));
	if (tmp_conn == NULL) 
	{
		zend_error(E_ERROR, "memory allocation error");
		goto error;
	}
	tmp_conn->sqlca = sqlca;
	tmp_conn->env = NULL;
	tmp_conn->connection_name = NULL;
	tmp_conn->tran_no = 1;
	
	/* verify if persistent connection are allowed */
	if (!Ct_G(allow_persistent)) { 
		persistent = 0;
	}
	
	if (persistent) { /* to be removed when supported */
		persistent = 0;
	}
	
	switch (resv) {
		case 0: /*nothing*/
			sprintf(conn,"%s@%s:%s",INI_STR("ctsql.default_port"), INI_STR("ctsql.default_host"),
										INI_STR("ctsql.default_database"));
			strcpy(tpe_uname,INI_STR("ctsql.default_user"));
			strcpy(tpe_pword,INI_STR("ctsql.default_password"));
			break;
		case 3: /*password*/
			convert_to_string_ex(params[2]);
			strcpy(tpe_pword,(char*)Z_STRVAL_PP(params[2]));
			/* fall trough */
		case 2: /*user*/
			convert_to_string_ex(params[1]);
			strcpy(tpe_uname,(char*)Z_STRVAL_PP(params[1]));
			/*fall trough*/
		case 1: /*hostname*/
			if (strchr((char *)Z_STRVAL_PP(params[0]),'@')!=NULL)
			{
				if (strchr((char *)Z_STRVAL_PP(params[0]),':')!=NULL)
				{
					sprintf(conn,"%s",(char *)Z_STRVAL_PP(params[0]));
				}
				else
				{
					sprintf(conn,"%s:%s",(char *)Z_STRVAL_PP(params[0]),INI_STR("ctsql.default_database"));
				}
			}
			else 
			{
				if (strchr((char *)Z_STRVAL_PP(params[0]),':')!=NULL)
				{
					sprintf(conn,"%s@%s",INI_STR("ctsql.default_port"),(char *)Z_STRVAL_PP(params[0]));
				}
				else
				{
					sprintf(conn,"%s@%s:%s",INI_STR("ctsql.default_port"),
						    INI_STR("ctsql.default_host"),(char *)Z_STRVAL_PP(params[0]));
				}
			}
			if (tpe_uname[0]=='\0')
				strcpy(tpe_uname,INI_STR("ctsql.default_user"));
			if (tpe_pword[0]=='\0')
				strcpy(tpe_pword,INI_STR("ctsql.default_password"));
			break;
	}

	conn_name = mymalloc(3 + strlen(conn) + strlen(tpe_uname) + strlen(tpe_pword) );
	if (conn_name == NULL)
	{
		zend_error(E_ERROR, "memory allocation error");
		goto error;
	}
	sprintf(conn_name,"%s$%s$%s",conn, tpe_uname, tpe_pword);
	tmp_conn->connection_name = conn_name;	
	
	if (persistent) {
		NULL;
		/* PLACE HOLDER */
	} else {
		zend_rsrc_list_entry new_entry;

		dh_alloc_sqlenv (&tmp_conn->env);
		if (tmp_conn->env == NULL)
		{
			zend_error(E_ERROR, "memory allocation error");
			goto error;
		}
		
		GSQLENV = tmp_conn->env;
		dh_sqlconnect(GSQLENV,conn,conn_name,tpe_uname,tpe_pword,
						(dh_char_t *) 0	,sqlca);
		ctSetErrorCode(sqlca->sqlcode);
		ctSetErrorDesc(sqlca->sqlerrm);
		ctSetErrorPos(sqlca->sqlerrd[4]);
		if (sqlca->sqlcode != 0)
		{
			goto error;
		}

		GCONNECTION=ZEND_REGISTER_RESOURCE(return_value, tmp_conn,le_connection);
		PSQLCA = sqlca;
		GCONN_PTR = tmp_conn;
		
		/* add to the hash list*/
		new_entry.ptr=(void *) return_value->value.lval;
		new_entry.type=le_index_ptr;
		if (zend_hash_update(&EG(regular_list), conn_name,strlen(conn_name)+1, (void *) &new_entry, sizeof(zend_rsrc_list_entry), NULL)==FAILURE) {
				goto error;
		}
	}
	
	return;
	
error:

	if (tmp_conn)
	{
		if(tmp_conn->connection_name)
		{
			myfree((void **)&tmp_conn->connection_name);
		}
		if (tmp_conn->env)
		{
			dh_free_sqlenv(tmp_conn->env);
			tmp_conn->env = NULL;
		}
		myfree((void **)&tmp_conn);
	}

	if (sqlca) {
		myfree((void **)&sqlca);
	}
	ctInvalidateConnection();
	RETURN_FALSE;
}


void php_ctsql_fetch(INTERNAL_FUNCTION_PARAMETERS, int result_type)
{
	char err[1024];
	int rv;
	zval **param;
	int resv;
	struct query *curr_qry;
	lval_t cqry;
	Ct_LS_FETCH()

	resv = ZEND_NUM_ARGS();
	
	switch (resv) {
		case 1:
			if (zend_get_parameters_ex(1,&param)!=SUCCESS)
				WRONG_PARAM_COUNT;
			if (!isResource(*param)) {
				ctSetErrorCode(WRONG_QUERY_ID);
				RETURN_FALSE;
			}
			convert_to_long_ex(param);
			cqry = Z_LVAL_PP(param);
			break;
#ifdef CURRQUERY
		case 0:
			cqry = GQUERY;
			break;
#endif
		default:
			WRONG_PARAM_COUNT;
	}

	curr_qry = SwitchQuery(cqry);
	
	if (!curr_qry) {
		RETURN_FALSE;
	}

	if (curr_qry->sqldaptr==NULL) {
		ctSetErrorCode(WRONG_QUERY_ID);
		RETURN_FALSE;	
	}

	if (curr_qry->tofetch == 0)
	{
		AllocFetchMem(curr_qry, (short) Ct_G(rowfetches));

		if (curr_qry->sql_alloc==0) {
			zend_error(E_ERROR, "memory allocation error");
			RETURN_FALSE;
		}

		if (sql_fetch (curr_qry)!= SUCCESS) {
			FreeFetchMem(curr_qry);
			RETURN_FALSE;
		}	
	}
	
	if (curr_qry->tran_no != 0)
	{
		if (curr_qry->tran_no < GCONN_PTR->tran_no)
		{
			ctSetErrorCode(SQL_ERR_NOTOPENED);
			RETURN_FALSE;
		}	
	}
	
	/* populate php associative array */

	if ( array_init(return_value) != SUCCESS ) {
		FreeFetchMem(curr_qry);
		zend_error(E_ERROR, "Internal Error #1");
		RETURN_FALSE;
	}
	
	if ((rv = PopulateArray(result_type,curr_qry,return_value)) != SUCCESS) {
		FreeFetchMem(curr_qry);
		sprintf(err,"Populate Array Error: %d",rv);
		zend_error(E_ERROR, err);
		RETURN_FALSE;
	}
	return;
}

char *type2str(short type) {
	switch(type) {
		case TPE_DT_DATE:
			return "date";
			break;
		
		case TPE_DT_TINYINT:
		case TPE_DT_SMALLINT:
		case TPE_DT_INTEGER:
		case TPE_DT_BIGINT:
			return "int";
			break; 
			
		case TPE_DT_MONEY:
			return "money";
			break;

		case TPE_DT_TIME:
			return "time";
			break;
			
		case TPE_DT_TIMESTAMP:
			return "timestamp";
			break;

		case TPE_DT_BINARY:  
#ifdef LVB_SUPPORT
		case TPE_DT_LVB:
#endif
			return "binary";
			break;

		case TPE_DT_BIT:
			return "bit";
			break;

#ifdef LVC_SUPPORT
		case TPE_DT_LVC:
#endif
		case TPE_DT_CHAR:
		case TPE_DT_VARCHAR:
			return "string";
			break;

		case TPE_DT_FLOAT:
		case TPE_DT_REAL:
		case TPE_DT_NUMERIC:
			return "real";
			break;

#ifndef LVC_SUPPORT
		case TPE_DT_LVC:
			return "unsupported";
#endif
#ifndef LVB_SUPPORT		
		case TPE_DT_LVB:
			return "unsupported";
#endif
		default:
			return "unknown";
			break;
	}
}

char *type2strex(short type) {
	switch(type) {
		case TPE_DT_DATE:
			return "date";
			break;
		case TPE_DT_TINYINT:
			return "tinyint";
			break;
		case TPE_DT_SMALLINT:
			return "smallint";
			break;
		case TPE_DT_INTEGER:
			return "int";
			break;
		case TPE_DT_BIGINT:
			return "bigint";
			break; 		
		case TPE_DT_MONEY:
			return "money";
			break;
		case TPE_DT_TIME:
			return "time";
			break;
		case TPE_DT_TIMESTAMP:
			return "timestamp";
			break;
		case TPE_DT_BINARY:  
			return "binary";
			break;
#ifdef LVB_SUPPORT
		case TPE_DT_LVB:
			return "lvarbinary";
			break;
#endif
		case TPE_DT_BIT:
			return "bit";
			break;

#ifdef LVC_SUPPORT
		case TPE_DT_LVC:
			return "lvarchar";
			break;
#endif
		case TPE_DT_CHAR:
			return "char";
			break;
		case TPE_DT_VARCHAR:
			return "varchar";
			break;
		case TPE_DT_FLOAT:
			return "float";
			break;
		case TPE_DT_REAL:
			return "real";
			break;
		case TPE_DT_NUMERIC:
			return "numeric";
			break;

#ifndef LVC_SUPPORT
		case TPE_DT_LVC:
			return "unsupported";
#endif
#ifndef LVB_SUPPORT		
		case TPE_DT_LVB:
			return "unsupported";
#endif
		default:
			return "unknown";
			break;
	}
}

struct sqlda *SqldAlloc (tpe_cursor_type tpe_pcur) {
	struct sqlda *mem;
	int resv;
	Ct_LS_FETCH()

	mem = sqld_alloc(1,MAXVARNAMELEN);
	
	if (mem == NULL) {
		goto error;
	}
	
	dh_sqldescribe(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),tpe_pcur,mem,PSQLCA);
	ctSetErrorCode(PSQLCA->sqlcode);
	ctSetErrorDesc(PSQLCA->sqlerrm);
	ctSetErrorPos(PSQLCA->sqlerrd[4]);
	if (PSQLCA->sqlcode){
		goto error;
	}
	
	if ((resv = mem->sqld_nvars)<0) { 
		sqld_free(mem);
		mem = sqld_alloc(-(resv),MAXVARNAMELEN);
		if (mem == NULL) {
			goto error;
		}
		{
			dh_sqldescribe(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),tpe_pcur,mem,PSQLCA);
			ctSetErrorCode(PSQLCA->sqlcode);
			ctSetErrorDesc(PSQLCA->sqlerrm);
			ctSetErrorPos(PSQLCA->sqlerrd[4]);
			if (PSQLCA->sqlcode){
				goto error;
			}
		}
	}

	return mem;
error:
	if (mem) 
		sqld_free(mem);
	return NULL;
}

void SqldFree(struct query *qry) {
	if (qry) {
		if (qry->sqldaptr!=NULL) {
			FreeFetchMem(qry);
			sqld_free(qry->sqldaptr);
			qry->sqldaptr=NULL;
		}
	}
}

void AllocFetchMem(struct query *qry, short rows) 
{
	int i,j;
	struct sqlda *mem;
	Ct_LS_FETCH()

	if (qry) 
	{
		mem = qry->sqldaptr;
		if (qry->sql_alloc == 0) 
		{
			qry->sql_alloc = 1;
			
			if (rows < 1 || rows > MAXRowFETCH)
				rows = 1;
			
			mem->sqld_arraysz = rows;
			for (i=0;i<mem->sqld_size;i++) 
			{
				mem->sqld_varptrs[i]=ecalloc(mem->sqld_lengths[i]*rows,sizeof(char));
				if (mem->sqld_varptrs[i] == NULL) 
				{
					for (j=0;j<i;j++) 
					{
						myfree((void **)&mem->sqld_varptrs[j]);
					}
					qry->sql_alloc = 0;
					break;
				}
				mem->sqld_ivarptrs[i]=ecalloc(rows,sizeof(short));
				if (mem->sqld_ivarptrs[i] == NULL) 
				{
					for (j=0;j<i;j++) 
					{
						myfree((void **)&mem->sqld_varptrs[j]);
						myfree((void **)&mem->sqld_ivarptrs[j]);
					}
					myfree((void **)&mem->sqld_varptrs[j]);
					qry->sql_alloc = 0;
					break;
				}
			}
		}
	}
}

void FreeFetchMem(struct query *qry) 
{
	int i;
	struct sqlda *mem;
	if (qry) 
	{
		mem = qry->sqldaptr;
		if (qry->sql_alloc) 
		{
			for (i=0;i<mem->sqld_size;i++) 
			{
				myfree((void **)&mem->sqld_varptrs[i]);
				myfree((void **)&mem->sqld_ivarptrs[i]);
			}
			qry->sql_alloc = 0;
		}
	}
}

long sql_fetch(struct query *qry) {
	dh_i32_t rc;
	Ct_LS_FETCH()

	dh_sqlfetch(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),qry->tpe_pcur,
				qry->sqldaptr,PSQLCA);
	
	rc = PSQLCA->sqlcode;
	ctSetErrorCode(rc);
	ctSetErrorDesc(PSQLCA->sqlerrm);
	ctSetErrorPos(PSQLCA->sqlerrd[4]);
	
	/* PSQLCA->sqlerrd[3] contains the number or rows fetched by dh_sqlfetch*/
	qry->tofetch = (short) PSQLCA->sqlerrd[3];
	qry->fetched = 0;

	if (rc == 100) /* cannot fetch all the rows requested */
	{
		PSQLCA->sqlcode = 0; /*it's not an error, so remove all the error information */
		PSQLCA->sqlerrml=0;
		strcpy(PSQLCA->sqlerrm,"");
		ctSetErrorCode(0);
		ctSetErrorDesc("");
		ctSetErrorPos(0);
		
		if (qry->tofetch != 0 && qry->no_more == 0) /* fetched some rows */
		{
				qry->no_more = 1;
			return SUCCESS;
		}
		else /* no more rows to be fetched */
		{
			qry->no_more = 1;
			return rc;
	}
	}

	if (rc != 0)
		return rc;
	
	return SUCCESS;
}

int PopulateArray (int type,struct query *qry, zval* array) {
	struct sqlda *sqldap;
	int i = 0;
	int j = 0;
	char *varptr;
	short ivar;
	
	qry->tofetch--;
	sqldap = qry->sqldaptr;
	j = qry->fetched++ ;

	for (i=0;i<sqldap->sqld_nvars;i++) 
	{ /*the number of output variables! */
#ifdef ARRAY_MEM_OPTIM
		zval *data;
#endif	
		varptr = sqldap->sqld_varptrs[i]+(j* sqldap->sqld_lengths[i]);
		ivar =	sqldap->sqld_ivarptrs[i][j];
		if (ivar==-1)
		{
			/* it is a null value */
			if (type & ENUMERATED)
#ifdef OLD_CODE
				add_index_unset(array,i);
#else
				add_index_null(array,i);
#endif
			if (type & ASSOCIATIVE)
#ifdef OLD_CODE
				add_assoc_unset(array,sqldap->sqld_varnames[i]);
#else
				add_assoc_null(array,sqldap->sqld_varnames[i]);
#endif
			
			continue;
		}
		switch(sqldap->sqld_types[i]) {
			case TPE_DT_NUMERIC: 
			case TPE_DT_DATE:      
			case TPE_DT_MONEY:    
			case TPE_DT_TIME:    
			case TPE_DT_TIMESTAMP:
			case TPE_DT_BINARY:  
			case TPE_DT_BIT:    
			case TPE_DT_BIGINT:
				{	
					char res[1024];
					int rv;
					rv = dh_conv_data(sqldap->sqld_types[i],sqldap->sqld_lengths[i],
								varptr,"",
								TPE_DT_CHAR,1024,res);
					if (rv) {
						return (15); /* cannot convert */
					}
					
#ifdef ARRAY_MEM_OPTIM
					MAKE_STD_ZVAL(data);
					ZVAL_STRING(data, res, 1);
					if (type & ENUMERATED)
						add_index_zval(array,i,data);
					if (type & ASSOCIATIVE)
					{
						if (type & ENUMERATED)
							ZVAL_ADDREF(data);
						add_assoc_zval(array,sqldap->sqld_varnames[i],data);
					}
#else
					if (type & ENUMERATED)
						add_index_string(array,i,res,1);
					if (type & ASSOCIATIVE)
						add_assoc_string(array,sqldap->sqld_varnames[i],res,1);
#endif
					
					break;
				}
			case TPE_DT_CHAR:
			case TPE_DT_VARCHAR:
				{
#ifdef ARRAY_MEM_OPTIM
					MAKE_STD_ZVAL(data);
					ZVAL_STRING(data, varptr, 1);
					if (type & ENUMERATED)
						add_index_zval(array,i,data);
					if (type & ASSOCIATIVE)
					{
						if (type & ENUMERATED)
							ZVAL_ADDREF(data);
						add_assoc_zval(array,sqldap->sqld_varnames[i],data);
					}
#else
					if (type & ENUMERATED)
						add_index_string(array,i,varptr,1);
					if (type & ASSOCIATIVE)
						add_assoc_string(array,sqldap->sqld_varnames[i],varptr,1);
#endif

					break;
				}
			case TPE_DT_TINYINT:
			case TPE_DT_SMALLINT:
			case TPE_DT_INTEGER:
				{
					dh_i32_t res;
					int rv;
					rv = dh_conv_data(sqldap->sqld_types[i],sqldap->sqld_lengths[i],
								varptr,"",
								TPE_DT_INTEGER,sizeof(dh_i32_t),&res);
					if (rv) {
						return (15); /* cannot convert */
					}
					if (type & ENUMERATED)
						add_index_long(array,i,(long)res);
					if (type & ASSOCIATIVE)
						add_assoc_long(array,sqldap->sqld_varnames[i],(long)res);
					break;
				}
			
			case TPE_DT_FLOAT:
			case TPE_DT_REAL:
				{
					double res;
					int rv;
					rv = dh_conv_data(sqldap->sqld_types[i],sqldap->sqld_lengths[i],
								varptr,"",
								TPE_DT_FLOAT,sizeof(double),&res);
					if (rv) {
						return (15); /* cannot convert */
					}
					
					if (type & ENUMERATED)
						add_index_double(array,i,res);
					if (type & ASSOCIATIVE)
						add_assoc_double(array,sqldap->sqld_varnames[i],res);
					
							
					break;
				}
		

			case TPE_DT_LVC: 
				{
#ifdef LVC_SUPPORT
					dh_char_t *res = NULL;
					res = GetClob(qry,varptr,sqldap->sqld_types[i]);	
					if (res == NULL) {
						return (15); /*cannot convert */
					}		
					/* dup the string. */
					/* the string is allocated in GetClob  */
#ifdef ARRAY_MEM_OPTIM
					MAKE_STD_ZVAL(data);
					ZVAL_STRING(data, res, 1);
					if (type & ENUMERATED)
						add_index_zval(array,i,data);
					if (type & ASSOCIATIVE)
					{
						if (type & ENUMERATED)
							ZVAL_ADDREF(data);
						add_assoc_zval(array,sqldap->sqld_varnames[i],data);
					}
#else
					if (type & ENUMERATED)
						add_index_string(array,i,res,1);
					if (type & ASSOCIATIVE)
						add_assoc_string(array,sqldap->sqld_varnames[i],res,1);
#endif					
					/* free the string */
					myfree((void **)&res);
					break;
#else
					return (15); /* cannot convert */
#endif
				}
			case TPE_DT_LVB: 
				{
#ifdef LVB_SUPPORT
					unsigned char *res = NULL;
					long len = 0;
					res = GetBlob(qry,varptr,sqldap->sqld_types[i],&len);	
					if (res == NULL) {
						return (15); /* cannot convert */
					}		
					/* dup the string. */
					/* the string is allocated in GetBlob */
#ifdef ARRAY_MEM_OPTIM
					MAKE_STD_ZVAL(data);
					ZVAL_STRINGL(data, res, len ,1);
					if (type & ENUMERATED)
						add_index_zval(array,i,data);
					if (type & ASSOCIATIVE)
					{
						if (type & ENUMERATED)
							ZVAL_ADDREF(data);
						add_assoc_zval(array,sqldap->sqld_varnames[i],data);
					}
#else
					if (type & ENUMERATED)
						add_index_stringl(array,i,res,len,1);
					if (type & ASSOCIATIVE)
						add_assoc_stringl(array,sqldap->sqld_varnames[i],res,len,1);
#endif					
					/* free the string */
					myfree((void **)&res);
					break;
#else
					return (15); /* cannot convert */
#endif
				}
			default: 
				return (30); /* unknown type */
		}
	}
	return (SUCCESS);
}

int doquery(struct query *qry, char *qry_txt)
{
	Ct_LS_FETCH()
	struct sqlca in_sqlca;
	int opened=0;
	int is_select = 0;
	int is_call = 0;

	qry->tofetch = 0;
	qry->fetched = 0;
	qry->tpe_puuid=mymalloc(sizeof(tpe_uuid__t)); 
	if (qry->tpe_puuid==NULL) {
		return QUERY_MEMORY;
	}
	os_uuid_gen (qry->tpe_puuid);

	dh_set_cursor(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),
				(tpe_cursor_type *)&qry->tpe_pcur,
				qry->tpe_puuid,1,(dh_char_t *)qry_txt,
				PSQLCA);

	ctSetErrorCode(PSQLCA->sqlcode);
	ctSetErrorDesc(PSQLCA->sqlerrm);
	ctSetErrorPos(PSQLCA->sqlerrd[4]);
	if (PSQLCA->sqlcode != 0){
		DebugLog("doquery","dh_set_cursor",PSQLCA->sqlcode);
		goto error;
	}
	
	if (Ct_G(query_timeout) > 0)
	{
		dh_set_query_timeout(GSQLENV, (tpe_cursor_type) qry->tpe_pcur, (dh_u16_t)Ct_G(query_timeout));
	}

	dh_sqlprepare(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),
					(tpe_cursor_type) qry->tpe_pcur,PSQLCA);
	ctSetErrorCode(PSQLCA->sqlcode);
	ctSetErrorDesc(PSQLCA->sqlerrm);
	ctSetErrorPos(PSQLCA->sqlerrd[4]);
	if (PSQLCA->sqlcode != 0){
		DebugLog("doquery","dh_sqlprepare",PSQLCA->sqlcode);
		goto error;
	}
		
	if (strncmp(PSQLCA->dynamic_function,"SELECT",6)==0)
		is_select = 1;
		
	else if (strcmp(PSQLCA->dynamic_function,"CALL PROCEDURE")==0)
	{
		struct sqlda *mem;

		dh_sqlexecute(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),
		              (tpe_cursor_type) qry->tpe_pcur,
		              (struct sqlda *)0,PSQLCA);
		if (PSQLCA->sqlcode != 0){
			DebugLog("doquery","dh_sqlexecute",PSQLCA->sqlcode);
			goto error;
		}
		
		if ((mem = sqld_alloc(1,MAXVARNAMELEN)) == NULL)
		{
			PSQLCA->sqlcode = SQL_ERR_NOMEM;
			goto error;
		}
		
		dh_sqldescribe(GSQLENV, dh_get_curtmhdl(GSQLENV), dh_get_curdbhdl(GSQLENV),
		                (tpe_cursor_type) qry->tpe_pcur, mem, PSQLCA);

		if (PSQLCA->sqlcode != 0) {
			sqld_free(mem);
			goto error;
		}
		if (mem->sqld_nvars != 0)
		{
			is_select = 1;
		}
		else
		{
			is_call = 1;
		}
		sqld_free(mem);
	}
	
	
		
	if (is_select)
	{
		dh_sqldeclare(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),
					(tpe_cursor_type) qry->tpe_pcur,
					(struct sqlda *)0,PSQLCA);
		ctSetErrorCode(PSQLCA->sqlcode);
		ctSetErrorDesc(PSQLCA->sqlerrm);
		ctSetErrorPos(PSQLCA->sqlerrd[4]);
		if (PSQLCA->sqlcode != 0){
			DebugLog("doquery","dh_sqldeclare",PSQLCA->sqlcode);
			goto error;
		}
		
		dh_sqlopen(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),
					(tpe_cursor_type) qry->tpe_pcur,
					(struct sqlda *)0,PSQLCA);
		ctSetErrorCode(PSQLCA->sqlcode);
		ctSetErrorDesc(PSQLCA->sqlerrm);
		ctSetErrorPos(PSQLCA->sqlerrd[4]);
		if (PSQLCA->sqlcode != 0){
			DebugLog("doquery","dh_sqlopen",PSQLCA->sqlcode);
			goto error;
		}
		opened = 1;			
		/* global sqldaptr allocation */
		SqldFree(qry);
		qry->sqldaptr = SqldAlloc((tpe_cursor_type) qry->tpe_pcur);

		if (qry->sqldaptr==NULL) {
			if (qry->tpe_puuid) {
				myfree((void **)&qry->tpe_puuid);
			}	
			return QUERY_MEMORY;		
		}

		return QUERY_FETCH;
	} else {
		/* non select query */
		if (!is_call)
		{
			dh_sqlexecute(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),(tpe_cursor_type)qry->tpe_pcur,(struct sqlda *)NULL,PSQLCA);
			if (PSQLCA->sqlcode == 100 && !Ct_G(exec_error_100))
			{
				PSQLCA->sqlcode = 0; 
				PSQLCA->sqlerrml=0;
				strcpy(PSQLCA->sqlerrm,"");
			}
			ctSetErrorCode(PSQLCA->sqlcode);
			ctSetErrorDesc(PSQLCA->sqlerrm);
			ctSetErrorPos(PSQLCA->sqlerrd[4]);
			if (PSQLCA->sqlcode != 0){
				DebugLog("doquery","dh_sqlexecute",PSQLCA->sqlcode);
				goto error;
			}
		}
		dh_release_cursor(GSQLENV,(tpe_cursor_type*) &qry->tpe_pcur);
		SqldFree(qry);
		if (qry->tpe_puuid) {
			myfree((void **)&qry->tpe_puuid);
		}
		return QUERY_DONE;
	}
	
error:
	ctSetErrorCode(PSQLCA->sqlcode);
	ctSetErrorDesc(PSQLCA->sqlerrm);
	ctSetErrorPos(PSQLCA->sqlerrd[4]);
	if (qry->tpe_pcur!=NULL)
	{
		if (opened) 
		{
			dh_sqlclose(GSQLENV,dh_get_curtmhdl(GSQLENV),dh_get_curdbhdl(GSQLENV),(tpe_cursor_type)qry->tpe_pcur,&in_sqlca);
			if (in_sqlca.sqlcode!=0)
				zend_error(E_WARNING, "dh_sqlclose error 2");
		}
		dh_release_cursor(GSQLENV,(tpe_cursor_type*) &qry->tpe_pcur);
	}
	
	if (qry->tpe_puuid) {
		myfree((void **)&qry->tpe_puuid);
	}
	return QUERY_ERROR;
};

int SwitchConnection(lval_t param)
{
	int restype;
	struct connection *tmp_conn;

	Ct_LS_FETCH()
	TSRMLS_FETCH();
	
	if (param == 0)
	{
		ctSetErrorCode(WRONG_CONN_ID);
		ctInvalidateConnection();
		return (0);
	}
	if (GCONNECTION != param)
	{
		DebugLog("Switch connection","",0);
		tmp_conn = zend_list_find((int)param,&restype);
		if (!tmp_conn || restype!=le_connection) {
			ctSetErrorCode(WRONG_CONN_ID);
			ctInvalidateConnection();
			return (0);
		}
		PSQLCA= tmp_conn->sqlca;
		GSQLENV= tmp_conn->env;
		GCONNECTION = param;
		GCONN_PTR = tmp_conn;
		ctSetErrorCode(tmp_conn->sqlca->sqlcode); /* set the error code */
		ctSetErrorDesc(tmp_conn->sqlca->sqlerrm);
		ctSetErrorPos(tmp_conn->sqlca->sqlerrd[4]);
	}
	return (1);
}

struct query *SwitchQuery(lval_t param)
{
	int restype;
	struct query *tmp_query;

	Ct_LS_FETCH()
	TSRMLS_FETCH();
	
	if (param == 0)
	{
		ctSetErrorCode(WRONG_QUERY_ID);
#ifdef CURRQUERY
		ctInvalidateQuery();
#endif
		DebugLog("SwitchQuery","wrong param",0);
		return (NULL);
	}
	
	tmp_query = zend_list_find((int)param,&restype);
	if (!tmp_query|| restype!=le_queries) {
		ctSetErrorCode(WRONG_QUERY_ID);
#ifdef CURRQUERY
		ctInvalidateQuery();
#endif
		DebugLog("SwitchQuery","cannot find query",0);
		return (NULL);
	}
	if (!SwitchConnection(tmp_query->conn))
	{
#ifdef CURRQUERY
		ctInvalidateQuery();
#endif
		DebugLog("SwitchQuery","cannot switch connection",0);
		return(NULL);
	}
#ifdef CURRQUERY
	GQUERY = param;
#endif
	return (tmp_query);
}

void _Debug_Log(char*fnc, char *msg, int error)
{
	FILE *log;
	Ct_LS_FETCH()
	
	if (GDEBUG)
	{
		log = fopen("/tmp/php","at");
		if (log)
		{
			if (error)
				fprintf(log,"fn:%s cn:[%d] msg:%s err:%d\n",fnc,GCONNECTION,(msg!=NULL)?msg:"NULL",error);
			else
				fprintf(log,"fn:%s cn:[%d] msg:%s \n",fnc,GCONNECTION,(msg!=NULL)?msg:"NULL");
			fclose(log);
		} else {
			zend_error(E_WARNING, "debug active, file open error");	
		}
	}
	
}

unsigned char *GetBlob(struct query *qry, void *ptr, long dtype, long *bytesread)
{
	tpe_binary_t bin;
	unsigned char *rv=NULL;

	Ct_LS_FETCH()
	
	*bytesread = 0;
	if (dtype == TPE_DT_LVB)
	{
		dh_i32_t r=1;
		dh_i32_t len=0;
		dh_i32_t allocsize=0;
		
		while (r!=0)
		{
			if (allocsize == *bytesread) /* we need to expand the buffer */
			{
				allocsize = *bytesread + TPE_MAX_FLDLEN;
				rv = erealloc(rv, allocsize);
				if (rv == NULL)
					goto Exit;
			}

			dh_sqlgetdata(GSQLENV, dh_get_curtmhdl(GSQLENV), dh_get_curdbhdl(GSQLENV), qry->tpe_pcur, TPE_DT_BINARY, ptr, 
							TPE_MAX_FLDLEN, *bytesread, &bin, &r, PSQLCA);
			
			if (bin.tb_len)
				memcpy((void*)&rv[*bytesread],(void*)bin.tb_data, bin.tb_len);

			ctSetErrorCode(PSQLCA->sqlcode);
			ctSetErrorDesc(PSQLCA->sqlerrm);
			ctSetErrorPos(PSQLCA->sqlerrd[4]);
			if (PSQLCA->sqlcode != 0)
				goto Exit;
			*bytesread += bin.tb_len;
		}
	}
Exit:
	return rv;
}

dh_char_t  *GetClob(struct query *qry, void *ptr, long dtype)
{
	long bytesread = 0;
	dh_char_t *rv=NULL;
	Ct_LS_FETCH()

	if (dtype == TPE_DT_LVC)
	{
		dh_i32_t r=1;
		dh_i32_t len=0;
		dh_i32_t allocsize=0;
		
		while (r!=0)
		{
			if (allocsize == bytesread) /* we need to expand the buffer */
			{
				allocsize = bytesread + LOB_BUF_SIZE;
				rv = erealloc(rv, allocsize);
				if (rv == NULL)
					goto Exit;
			}
			dh_sqlgetdata(GSQLENV, dh_get_curtmhdl(GSQLENV), dh_get_curdbhdl(GSQLENV), qry->tpe_pcur, TPE_DT_CHAR, ptr, 
							(allocsize-bytesread), bytesread, &rv[bytesread], &r, PSQLCA);
			ctSetErrorCode(PSQLCA->sqlcode);
			ctSetErrorDesc(PSQLCA->sqlerrm);
			ctSetErrorPos(PSQLCA->sqlerrd[4]);
			if (PSQLCA->sqlcode != 0)
				goto Exit;
			bytesread += r;
		}
	}
Exit:

	return rv;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
