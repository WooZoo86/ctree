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
#include "Zend/zend_extensions.h"

static php_stream *ctsql_create_lob_stream(pdo_stmt_t * stmt,void *handle, int colno, CTSQL_STREAM_DIRECTION dir);

static int ctsql_stmt_dtor(pdo_stmt_t *stmt) /* {{{ */
{
	pdo_ctsql_stmt *S = (pdo_ctsql_stmt*)stmt->driver_data;

	/* free statement data buffers */
	if (S->data) {
		efree(S->data);
		S->data = NULL;
		S->data_size = 0;
	}
	if (S->buffer) {
		efree(S->buffer);
		S->buffer = NULL;
		S->buffer_size = 0;
	}

	/* free cursor */
	if (S->cursor)
	{
		ctsqlFreeCursor(S->cursor);
	}

	/* free command */
	if (S->cmd) {
		ctsqlClose(S->cmd);
		ctsqlFreeCommand(S->cmd);
	}

	/* free statement object */
	efree(S);

	return 1;
} /* }}} */

static int ctsql_stmt_execute(pdo_stmt_t *stmt) /* {{{ */
{
	pdo_ctsql_stmt *S = (pdo_ctsql_stmt*)stmt->driver_data;
	zval *parameter;
	INTEGER param_len = 0;

	/* if command has already been executed, free previous cursor */
	if (stmt->executed && S->cursor)
		ctsqlFreeCursor(S->cursor);

	/* execute the prepared command */
	if (ctsqlExecute(S->cmd, &S->cursor) != CTSQLRET_OK) {
		pdo_ctsql_stmt_error("ctsqlExecute");
		return 0;
	}

	if (stmt->bound_params) {
		/* check if there is any parameter that must be updated after execution */
		struct pdo_bound_param_data *param;

		ZEND_HASH_FOREACH_PTR(stmt->bound_params, param) {
			if (param->paramno >= 0) {

				if (Z_ISREF(param->parameter))
					parameter = Z_REFVAL(param->parameter);
				else
					parameter = &param->parameter;

				/* if parameter is INOUT, update its value */
				if ((param->param_type & PDO_PARAM_INPUT_OUTPUT) == PDO_PARAM_INPUT_OUTPUT) {

					/* check statement buffer size */
					param_len = ctsqlGetParameterLength(S->cmd, (INTEGER)param->paramno);
					if (S->buffer_size <= param_len) {
						efree(S->buffer);
						if (!(S->buffer = ecalloc(1, param_len))) {
							pdo_ctsql_stmt_error2(CTSQLRET_ALLOC_FAILED, "Not able to re-allocate data", "ctsql_stmt_execute");
							return 0;
						}
						S->buffer_size = param_len;
					}

					/* retrieve parameter content */
					if (ctsqlGetParameter(S->cmd, (INTEGER)param->paramno, S->buffer, S->buffer_size) != CTSQLRET_OK) {
						pdo_ctsql_stmt_error("ctsqlGetParameter");
						return 0;
					}

					/* delete old value */
					zval_ptr_dtor(parameter);

					/* set new value */
					switch (PDO_PARAM_TYPE(param->param_type)) {
					case PDO_PARAM_INT:
						ZVAL_LONG(parameter, *(zend_long*)S->buffer);
						break;
					case PDO_PARAM_BOOL:
						ZVAL_BOOL(parameter, *(zend_bool*)S->buffer);
						break;
					case PDO_PARAM_STR:
						ZVAL_STRINGL(parameter, S->buffer, param_len-1);
						break;
					default:
						pdo_ctsql_stmt_error2(20024, "Invalid INOUT parameter type", "ctsql_stmt_param_hook");
					}
				}
			}
		} ZEND_HASH_FOREACH_END();
	}

	/* retrieve row count for the execution */
	stmt->row_count = ctsqlAffectedRows(S->cmd);

	/* do first-time-only definition of bind/mapping stuff */
	if (!stmt->executed && S->cursor)
		stmt->column_count = (int)ctsqlGetColumnCount(S->cursor);

	return 1;
} /* }}} */

static int ctsql_stmt_param_hook(pdo_stmt_t *stmt, struct pdo_bound_param_data *param, enum pdo_param_event event_type) /* {{{ */
{
	CTSQLRET ret;
	pdo_ctsql_stmt *S = (pdo_ctsql_stmt*)stmt->driver_data;
	zval *parameter;
	php_stream *stm = NULL;
	BIT isNullFlag = 0;
	INTEGER paramIndex = (INTEGER)param->paramno;
	CTSQLTYPE paramType;
	union {
	INTEGER intValue;
	BIGINT bigIntValue;
	SMALLINT smallIntValue;
	TINYINT tinyIntValue;
	NUMERIC numericValue;
	SMALLFLOAT realValue;
	FLOATT floatValue;
	SQLDATE dateValue;
	SQLTIME timeValue;
	SQLTIMESTAMP tsValue;
	} Val;
	char buf[8192];
	

	if (Z_ISREF(param->parameter))
		parameter = Z_REFVAL(param->parameter);
	else
		parameter = &param->parameter;

	switch (event_type) {

	case PDO_PARAM_EVT_FREE:
	case PDO_PARAM_EVT_FETCH_PRE:
	case PDO_PARAM_EVT_FETCH_POST:
	case PDO_PARAM_EVT_NORMALIZE:
		break;

	case PDO_PARAM_EVT_ALLOC:
		/* do some basic checking */
		if(param->is_param) {
			/* if doesn't know the parameter index, try to find it be name */
			if (paramIndex == -1)
				paramIndex = ctsqlGetParameterIndexByName(S->cmd, ZSTR_VAL(param->name));
			if (paramIndex == -1) {
				pdo_ctsql_stmt_error("ctsqlGetParameterIndexByName");
				return 0;
			}
			/* check parameter type in c-tree */
			paramType = ctsqlGetParameterType(S->cmd, paramIndex);
			/* check parameter type in PDO */
			switch (PDO_PARAM_TYPE(param->param_type)) {
			case PDO_PARAM_STMT:
				return 0;
			case PDO_PARAM_NULL:
			case PDO_PARAM_STR:
				return 1;
			case PDO_PARAM_INT:
			case PDO_PARAM_BOOL:
				switch(paramType)
				{
				case CTSQL_LVC: /* implicitly set to null */
				case CTSQL_LVB:
				case CTSQL_BINARY:
				case CTSQL_VARBINARY:
				case CTSQL_DATE:
				case CTSQL_TIME:
				case CTSQL_TIMESTAMP:
					pdo_ctsql_stmt_error2(20024, "c-treeSQL PDO driver doesn't support PARAM_INT or PARAM_BOOL parameter for this datatype.", "ctsql_stmt_param_hook");
					return 0;
				}
				return 1;
			case PDO_PARAM_LOB:
				switch(paramType)
				{
				case CTSQL_LVC: 
				case CTSQL_LVB:
				case CTSQL_CHAR:
				case CTSQL_VARCHAR:
				case CTSQL_BINARY:
				case CTSQL_VARBINARY:
					return 1;
				}
				pdo_ctsql_stmt_error2(20024, "c-treeSQL PDO driver doesn't support PARAM_LOB for this datatype.", "ctsql_stmt_param_hook");
				return 0;
			}
		}
	case PDO_PARAM_EVT_EXEC_PRE:
		if (param->is_param) {

			/* if doesn't know the parameter index, try to find it be name */
			if (paramIndex == -1)
				paramIndex = ctsqlGetParameterIndexByName(S->cmd, ZSTR_VAL(param->name));
			if (paramIndex == -1) {
				/* ignore it */
				return 1;
			}

			/* check parameter type in c-tree */
			paramType = ctsqlGetParameterType(S->cmd, paramIndex);

			/* check parameter type in PDO */
			switch (PDO_PARAM_TYPE(param->param_type)) {
			case PDO_PARAM_STMT:
				return 0;

			case PDO_PARAM_NULL:
				switch(paramType)
				{
				case CTSQL_LVC: /* implicitly set to null */
				case CTSQL_LVB:
					return 1;
				default:
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, 0, 1, NULL)) == CTSQLRET_OK)
						return 1;
					break;
				}
				if (ret)
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn) , "ctsql_stmt_param_hook");
				else
					pdo_ctsql_stmt_error("ctsqlSetParameter(NULL)");
				return 0;

			case PDO_PARAM_LOB:
			{
				size_t n;
				/* pdo_ctsql_stmt_error2(20024, "c-treeSQL PDO driver doesn't support LOB parameter", "ctsql_stmt_param_hook"); */
				switch(paramType)
				{
				case CTSQL_LVC: /* process Post exec */
				case CTSQL_LVB:
					return 1;
				case CTSQL_CHAR:
				case CTSQL_VARCHAR:
				case CTSQL_BINARY:
				case CTSQL_VARBINARY:
					/* Handle here */
					break;
				default:
					pdo_ctsql_stmt_error2(20024, "c-treeSQL PDO driver doesn't support PARAM_LOB for this datatype.", "ctsql_stmt_param_hook");
					return 0;
				}
				/* try to retrieve input stream to bind into the command */
				php_stream_from_zval_no_verify(stm, parameter);
				if (stm) {
					isNullFlag = 0;
					n = php_stream_read(stm, buf, sizeof(buf));

				}else
					isNullFlag = 1;

				if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, n, isNullFlag, buf)) == CTSQLRET_OK)
					return 1;
				pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
				return 0;
			}
			case PDO_PARAM_INT:
			case PDO_PARAM_BOOL:
			case PDO_PARAM_STR:
			default:
				if(isNullFlag = Z_TYPE_P(parameter) == IS_NULL)
				{
					if(paramType == CTSQL_LVB || paramType == CTSQL_LVC)
						return 1;
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, 0, isNullFlag, NULL)) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				}

				switch (paramType) {
				case CTSQL_CHAR:
				case CTSQL_NCHAR:
				case CTSQL_NVARCHAR:
				case CTSQL_NCHAR_CS:
				case CTSQL_NVARCHAR_CS:
				case CTSQL_VARCHAR:
					convert_to_string_ex(parameter);
					/* 
					** Strings are null terminated according to 
					** http://www.phpinternalsbook.com/php5/zvals/basic_structure.html
					*/
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, (INTEGER)Z_STRLEN_P(parameter)+1, isNullFlag, Z_STRVAL_P(parameter))) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				case CTSQL_REAL:
					convert_to_double_ex(parameter);
					Val.realValue = (SMALLFLOAT)Z_DVAL_P(parameter);
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, (INTEGER)sizeof(SMALLFLOAT), isNullFlag, &Val.realValue)) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				case CTSQL_FLOAT:
					convert_to_double_ex(parameter);
					Val.floatValue = (FLOATT)Z_DVAL_P(parameter);
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, (INTEGER)sizeof(FLOATT), isNullFlag, &Val.floatValue)) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				case CTSQL_NUMERIC:
				case CTSQL_MONEY:
					convert_to_string_ex(parameter);
					if ((ret = ctsqlConvert(CTSQL_CHAR, &Z_STRVAL_P(parameter), sizeof(Z_STRVAL_P(parameter)), CT_STRING_LITERAL(""), CTSQL_NUMERIC, &Val.numericValue, sizeof(NUMERIC))) != CTSQLRET_OK) {
						pdo_ctsql_stmt_error2(ret, "Not able to convert STRING value into the NUMERIC", "ctsql_stmt_param_hook");
						return 0;
					}
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, (INTEGER)sizeof(NUMERIC), isNullFlag, &Val.numericValue)) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				case CTSQL_TINYINT:
				case CTSQL_BIT:
					convert_to_long_ex(parameter);
					Val.tinyIntValue = (TINYINT)Z_LVAL_P(parameter);
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, (INTEGER)sizeof(TINYINT), isNullFlag, &Val.tinyIntValue)) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				case CTSQL_SMALLINT:
					convert_to_long_ex(parameter);
					Val.smallIntValue = (SMALLINT)Z_LVAL_P(parameter);
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, (INTEGER)sizeof(SMALLINT), isNullFlag, &Val.smallIntValue)) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				case CTSQL_INTEGER:
					convert_to_long_ex(parameter);
					Val.intValue = (INTEGER)Z_LVAL_P(parameter);
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, (INTEGER)sizeof(INTEGER), isNullFlag, &Val.intValue)) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				case CTSQL_BIGINT:
					convert_to_long_ex(parameter);
					Val.bigIntValue.ll=(INTEGER)Z_LVAL_P(parameter);
					Val.bigIntValue.hl=(Z_LVAL_P(parameter)>>32);
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, (INTEGER)sizeof(BIGINT), isNullFlag, &Val.bigIntValue)) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				case CTSQL_BINARY:
				case CTSQL_VARBINARY:
					if (PDO_PARAM_TYPE(param->param_type) != PDO_PARAM_STR)
					{
						pdo_ctsql_stmt_error2(20024, "c-treeSQL PDO driver doesn't support PARAM_INT and PARAM_BOOL parameter for [VAR]BINARY types. Please use PARAM_STR instead.", "ctsql_stmt_param_hook");
						return 0;
					}
					convert_to_string_ex(parameter);
					if ((ret = ctsqlSetParameter(S->cmd, paramIndex, paramType, (INTEGER)Z_STRLEN_P(parameter), isNullFlag, Z_STRVAL_P(parameter))) == CTSQLRET_OK)
						return 1;
					pdo_ctsql_stmt_error2(ret, ctsqlGetErrorMessage(S->H->conn), "ctsql_stmt_param_hook");
					return 0;
				case CTSQL_TIMESTAMP:
				case CTSQL_DATE:
				case CTSQL_TIME:
				{
					INTEGER paramLen;

					if (paramType == CTSQL_TIMESTAMP)
						paramLen = sizeof(SQLTIMESTAMP);
					else if(paramType == CTSQL_TIME)
						paramLen = sizeof(SQLTIME);
					else
						paramLen = sizeof(SQLDATE);

					if (PDO_PARAM_TYPE(param->param_type) == PDO_PARAM_STR) {
						/* convert string parameter value into the correct type */
						convert_to_string_ex(parameter);
						if ((ret = ctsqlConvert(CTSQL_CHAR, Z_STRVAL_P(parameter), (INTEGER)Z_STRLEN_P(parameter), "", paramType, &Val.tsValue, sizeof(SQLTIMESTAMP))) != CTSQLRET_OK) {
							pdo_ctsql_stmt_error2(ret, "Not able to convert parameter value from STRING", "ctsql_stmt_param_hook");
							return 0;
						}
						if (ctsqlSetParameter(S->cmd, paramIndex, paramType, paramLen, isNullFlag, &Val.tsValue) == CTSQLRET_OK)
							return 1;
					}
					else {
						pdo_ctsql_stmt_error2(20024, "c-treeSQL PDO driver doesn't support PARAM_INT and PARAM_BOOL parameter for DATE, TIME AND TIMESTAMP types. Please use PARAM_STR instead.", "ctsql_stmt_param_hook");
						return 0;
					}
					pdo_ctsql_stmt_error2(20024, "c-treeSQL PDO driver doesn't support PARAM_INT and PARAM_BOOL parameter for TIMESTAMP/DATE/TIME types. Please use PARAM_STR instead.", "ctsql_stmt_param_hook");
					return 0;
				}

				case CTSQL_LVC:
				case CTSQL_LVB:
					// must be set after execution.
					if(PDO_PARAM_TYPE(param->param_type)== PDO_PARAM_STR)
						return 1;
					
					pdo_ctsql_stmt_error2(20024, "c-treeSQL PDO driver doesn't support PARAM_INT and PARAM_BOOL parameter for LONG types. Please use PARAM_STR instead.", "ctsql_stmt_param_hook");
					return 0;
					break;	

				default:
					pdo_ctsql_stmt_error2(20024, "Unsupported field type", "ctsql_stmt_describe");
					return 0;
				}

				pdo_ctsql_stmt_error("ctsqlSetParameter");
				return 0;
			}
		}
		break;

		case PDO_PARAM_EVT_EXEC_POST:
			if (!param->is_param) 
				return 1;

			/* if doesn't know the parameter index, try to find it by name */
			if (paramIndex == -1)
				paramIndex = ctsqlGetParameterIndexByName(S->cmd, ZSTR_VAL(param->name)) - 1;
			if (paramIndex == -1) {
				/* do nothing */
				return 1;
			}

			/* check parameter type in c-tree */
			paramType = ctsqlGetParameterType(S->cmd, paramIndex);
			/* Only LONG types are set post exec */
			if(paramType != CTSQL_LVC && paramType != CTSQL_LVB)
				return 1;

			if(PDO_PARAM_TYPE(param->param_type) == PDO_PARAM_STR)
			{
				convert_to_string_ex(parameter);
				if((ret = ctsqlSetBlob(S->cmd,paramIndex, Z_STRVAL_P(parameter),(INTEGER)Z_STRLEN_P(parameter),0)) != CTSQLRET_OK)
				{
					pdo_ctsql_stmt_error2(ret, "Failed to set LONG parameter value from PDO_PARAM_STR", "ctsql_stmt_param_hook");
					return 0;
				}
				return 1;
			}
				/* bind LOB parameter */
			else if (PDO_PARAM_TYPE(param->param_type) == PDO_PARAM_LOB)
			{
					/* we're a LOB being used for insert/update; transfer the data now */
					size_t n, amt;
					char *consume;

					/* create the lob stream to insert data into the command */
					php_stream *in_stream = ctsql_create_lob_stream(stmt,S->cmd, paramIndex, CTSQL_STREAM_INPUT);
					if (!in_stream) {
						pdo_ctsql_stmt_error("ctsql_create_lob_stream");
						return 0;
					}

					/* try to retrieve input stream to bind into the command */
					php_stream_from_zval_no_verify(stm, parameter);
					if (stm) {
						
						do {
							n = php_stream_read(stm, buf, sizeof(buf));
							if ((int)n <= 0) {
								break;
							}
							consume = buf;
							do {
								if (!(amt = php_stream_write(in_stream, consume, n)))
									break;
								n -= amt;
								consume += amt;
							} while (n);
						} while (1);
					}
					else if (Z_TYPE_P(parameter) == IS_STRING) {
						/* stick the string into the LOB */
						consume = Z_STRVAL_P(parameter);
						n = Z_STRLEN_P(parameter);
						if (n) {
							while (n) {
								amt = n;
								amt = php_stream_write(in_stream, consume, n);
								n -= amt;
							}
						}
					}
				
			}
			break;

	default:
		;
	}
	return 1;
} /* }}} */

static int ctsql_stmt_fetch(pdo_stmt_t *stmt, enum pdo_fetch_orientation ori,	zend_long offset) /* {{{ */
{
	CTSQLRET ret;
	pdo_ctsql_stmt *S = (pdo_ctsql_stmt*)stmt->driver_data;

	/* for now, c-treeSQL supports only the NEXT featch direction */
	switch (ori) {
		case PDO_FETCH_ORI_NEXT:	break;
/*		case PDO_FETCH_ORI_PRIOR:	odbcori = SQL_FETCH_PRIOR; break;
		case PDO_FETCH_ORI_FIRST:	odbcori = SQL_FETCH_FIRST; break;
		case PDO_FETCH_ORI_LAST:	odbcori = SQL_FETCH_LAST; break;
		case PDO_FETCH_ORI_ABS:		odbcori = SQL_FETCH_ABSOLUTE; break;
		case PDO_FETCH_ORI_REL:		odbcori = SQL_FETCH_RELATIVE; break;*/
		default:
			pdo_ctsql_error(-1, "Fetch direction not support", stmt->dbh, stmt, "Fetch", __FILE__, __LINE__);
			return 0;
	}

	/* fetch next record from cursor */
	if ((ret = ctsqlNext(S->cursor)) != CTSQLRET_OK ) {
		if (ret != CTSQL_NOTFOUND)
			pdo_ctsql_stmt_error("ctsqlNext");
		return 0;
	}

	return 1;
} /* }}} */

static int ctsql_stmt_describe(pdo_stmt_t *stmt, int colno) /* {{{ */
{
	pdo_ctsql_stmt *S = (pdo_ctsql_stmt*)stmt->driver_data;
	struct pdo_column_data *col = &stmt->columns[colno];
	CTSQLTYPE col_type = ctsqlGetColumnType(S->cursor, colno);

	/* retrieve columns name */
	col->name = zend_string_init(ctsqlGetColumnName(S->cursor, colno), strlen(ctsqlGetColumnName(S->cursor, colno)), 0);

	/* retrieve column size */
	col->maxlen = ctsqlGetColumnLength(S->cursor, colno);

	/* returning data as a string */
	switch (col_type) {
	case CTSQL_CHAR:
	case CTSQL_VARCHAR:
	case CTSQL_NCHAR:
	case CTSQL_NVARCHAR:
	case CTSQL_NCHAR_CS:
	case CTSQL_NVARCHAR_CS:
	case CTSQL_NUMERIC:
	case CTSQL_REAL:
	case CTSQL_FLOAT:
	case CTSQL_DATE:
	case CTSQL_MONEY:
	case CTSQL_TIME:
	case CTSQL_TIMESTAMP:
	case CTSQL_BINARY:
	case CTSQL_VARBINARY:
		col->param_type = PDO_PARAM_STR;
		break;

	case CTSQL_SMALLINT:
	case CTSQL_INTEGER:
	case CTSQL_TINYINT:
	case CTSQL_BIGINT:
		col->param_type = PDO_PARAM_INT;
		break;

	case CTSQL_BIT:
		col->param_type = PDO_PARAM_BOOL;
		break;

	case CTSQL_LVC:
	case CTSQL_LVB:
		col->param_type = PDO_PARAM_LOB;
		break;

	default:
		pdo_ctsql_stmt_error2(20024, "Unsupported field type", "ctsql_stmt_describe");
		return 0;
	}

	return 1;
} /* }}} */


static ssize_t ctsql_blob_write(php_stream *stream, const char *buf, size_t count)
{
	ctsql_lob_self *self = (ctsql_lob_self*)stream->abstract;
	pdo_stmt_t * stmt = self->stmt;
	CTSQLRET ret;
	if(count >= 0x80000000) {
		pdo_ctsql_stmt_error2(CTSQLRET_BADLEN, "Invalid length", "ctsql_blob_write");
		return -1;
	}
	/* set blob stream portion */
	if(ret = ctsqlSetBlob((pCTSQLCMD)self->handle, (INTEGER)self->colnumber, (void *)buf, (INTEGER)count, (INTEGER)self->offset) ) {
		pdo_ctsql_stmt_error2(ret, "ctsqlSetBlob failure", "ctsql_blob_write");
		return -1;
	}

	self->offset += count;
	return count;
} 

static ssize_t ctsql_blob_read(php_stream *stream, char *buf, size_t count) 
{
	ctsql_lob_self *self = (ctsql_lob_self*)stream->abstract;
	pdo_stmt_t * stmt = self->stmt;
	INTEGER bytesread;
	CTSQLRET ret;
	if(count >= 0x80000000){
		pdo_ctsql_stmt_error2(CTSQLRET_BADLEN, "Invalid length", "ctsql_blob_read");
		return -1;
	}

	/* get blob stream portion */
	if (ret = ctsqlGetBlobByAddress((pCTSQLCURSOR)self->handle, (TINYINT*) self->fld_hdl, (void *)buf, (INTEGER)count, (INTEGER)self->offset, &bytesread)){
		pdo_ctsql_stmt_error2(ret, "ctsqlGetBlob failure", "ctsql_blob_read");
		return -1;
	}

	self->offset += bytesread;
	if (bytesread < count) {
		stream->eof = 1;
	}

	return bytesread;
} 

static int ctsql_blob_close(php_stream *stream, int close_handle) 
{
	ctsql_lob_self *self = (ctsql_lob_self*)stream->abstract;
	if (self->fld_hdl)
		free(self->fld_hdl);
#ifdef GC_DELREF
	GC_DELREF(&self->stmt->std);
#else
	GC_REFCOUNT(&self->stmt->std)--;
#endif
	efree(self);
	return 0;
} 

static int ctsql_blob_flush(php_stream *stream) 
{
	return 0;
}
static int ctsql_blob_seek(php_stream *stream, zend_off_t offset, int whence, zend_off_t *newoffset)
{
	ctsql_lob_self *self = (ctsql_lob_self*)stream->abstract;
	*newoffset = self->offset = offset;
	return 0;
}

static php_stream_ops ctsql_blob_stream_ops = {
	ctsql_blob_write,
	ctsql_blob_read,
	ctsql_blob_close,
	ctsql_blob_flush,        /* stream_flush */
	"pdo_ctsql blob stream", /* stream_label */
	ctsql_blob_seek,
	NULL,                    /* stream_cast */
	NULL,                    /* stream_stat */
	NULL                     /* stream_set_option */
};

static php_stream *ctsql_create_lob_stream(pdo_stmt_t * stmt,void *handle, int colno, CTSQL_STREAM_DIRECTION dir)
{
	php_stream *stm;
	ctsql_lob_self *self = ecalloc(1, sizeof(ctsql_lob_self));
	char * hdl = ctsqlGetVariableAddress((pCTSQLCURSOR)handle, colno);
	if (dir == CTSQL_STREAM_INPUT || hdl != NULL) /* for input (to the db) streams we do not use hdl */
	{
		self->stmt = stmt;
		self->handle = handle;
		self->colnumber = colno;
		self->direction = dir;
		self->offset = 0;
		if (hdl)
			self->fld_hdl = strdup(hdl);
		else
			self->fld_hdl = NULL;

		stm = php_stream_alloc(&ctsql_blob_stream_ops, self, 0, "r+b");
		if (stm) {
#ifdef GC_ADDREF
			GC_ADDREF(&stmt->std);
#else
			GC_REFCOUNT(&stmt->std)++;
#endif
			return stm;
		}
		/* stream alloc failure, cleanup */
		else if(self->fld_hdl)
			free(self->fld_hdl);
		
	}
	efree(self);
	return NULL;
}

static int ctsql_stmt_get_col(pdo_stmt_t *stmt, int colno, char **ptr, size_t *len, int *caller_frees) /* {{{ */
{
	int ret = 0, ctRet = CTSQLRET_OK;
	pdo_ctsql_stmt *S = (pdo_ctsql_stmt*)stmt->driver_data;
	CTSQLTYPE paramType;
	INTEGER collen;
	int type = PDO_PARAM_TYPE((&stmt->columns[colno])->param_type);

	/* check column type in c-tree */
	paramType = ctsqlGetColumnType(S->cursor, colno);
	collen = ctsqlGetColumnLength(S->cursor, colno);

	if (ctsqlIsColumnNull(S->cursor, colno)) {
		/* NULL value */
		*ptr = NULL;
		*len = 0;
		return 1;
	}
	else if (paramType == CTSQL_LVC || paramType == CTSQL_LVB) {
		/* treat BLOB and CLOB values */
		*ptr = (char*)ctsql_create_lob_stream(stmt,S->cursor, colno, CTSQL_STREAM_OUTPUT);
		*len = (size_t)0;
		return *ptr ? 1 : 0;
	}
	else {
		/* check if column type is already a string */
		if (paramType == CTSQL_CHAR || paramType == CTSQL_VARCHAR || 
		    paramType == CTSQL_BINARY ||paramType == CTSQL_VARBINARY || 
		    paramType == CTSQL_NCHAR || paramType == CTSQL_NVARCHAR ||
		    paramType == CTSQL_NCHAR_CS || paramType == CTSQL_NVARCHAR_CS) {

			/* check if the buffer allocated for the command is large enough */
			if (S->data_size <= collen) {
				efree(S->data);
				if (!(S->data = ecalloc(sizeof(CTSQLCHAR), collen + 1))) {
					pdo_ctsql_stmt_error2(CTSQLRET_ALLOC_FAILED, "Not able to re-allocate data", "ctsql_stmt_get_col");
					return 0;
				}
				S->data_size = collen + 1;
			}

			memset(S->data, 0, S->data_size);

			/* retrieve column content already in string format */
			switch (paramType) {
			case CTSQL_CHAR:
			case CTSQL_VARCHAR:
				ret = (ctsqlGetChar(S->cursor, colno, S->data) == CTSQLRET_OK);
				break;

			case CTSQL_NCHAR:
			case CTSQL_NVARCHAR:
			case CTSQL_NCHAR_CS:
			case CTSQL_NVARCHAR_CS:
				ret = (ctsqlGetNChar(S->cursor, colno, S->data) == CTSQLRET_OK);
				break;
			case CTSQL_BINARY:
			case CTSQL_VARBINARY:
				{
					int bytes;
					ret = ((bytes = ctsqlGetBytes(S->cursor, colno, (UTINYINT*)S->data, S->data_size)) >= 0);
					if(ret)
					{
						*ptr = S->data;
						*len = bytes;
						*caller_frees = 0;
						return 1;
					}
					
				}
				break;
			}

			if (ret) {
				*ptr = S->data;
				*len = strlen(S->data);
				*caller_frees = 0;
				return 1;
			}
			else {
				pdo_ctsql_stmt_error("ctsql_stmt_get_col - string");
				return 0;
			}
		}
		else {
			/* check if the buffer allocated for the command is large enough */
			if (S->buffer_size <= collen) {
				efree(S->buffer);
				if (!(S->buffer = ecalloc(1, collen))) {
					pdo_ctsql_stmt_error2(CTSQLRET_ALLOC_FAILED, "Not able to re-allocate data", "ctsql_stmt_get_col");
					return 0;
				}
				S->buffer_size = collen;
			}

			/* retrieve column content */
			switch (paramType) {
			case CTSQL_NUMERIC:
				ret = (ctsqlGetNumeric(S->cursor, colno, (NUMERIC*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_SMALLINT:
				ret = (ctsqlGetSmallInt(S->cursor, colno, (SMALLINT*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_INTEGER:
				ret = (ctsqlGetInteger(S->cursor, colno, (INTEGER*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_REAL:
				ret = (ctsqlGetReal(S->cursor, colno, (SMALLFLOAT*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_FLOAT:
				ret = (ctsqlGetFloat(S->cursor, colno, (FLOATT*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_DATE:
				ret = (ctsqlGetDate(S->cursor, colno, (SQLDATE*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_MONEY:
				ret = (ctsqlGetMoney(S->cursor, colno, (NUMERIC*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_TIME:
				ret = (ctsqlGetTime(S->cursor, colno, (SQLTIME*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_TIMESTAMP:
				ret = (ctsqlGetTimeStamp(S->cursor, colno, (SQLTIMESTAMP*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_TINYINT:
				ret = (ctsqlGetTinyInt(S->cursor, colno, (TINYINT*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_BIT:
				ret = (ctsqlGetBit(S->cursor, colno, (BIT*)S->buffer) == CTSQLRET_OK);
				break;

			case CTSQL_BIGINT:
				ret = (ctsqlGetBigInt(S->cursor, colno, (BIGINT*)S->buffer) == CTSQLRET_OK);
				break;

			default:
				pdo_ctsql_stmt_error2(20024, "Unsupported field type", "ctsql_stmt_get_col");
				return 0;
			}

			if (ret) {
				if (type == PDO_PARAM_STR) {
					/* convert current column content into string */
					if ((ctRet = ctsqlConvert(paramType, S->buffer, collen, "", CTSQL_CHAR, S->data, S->data_size)) != CTSQLRET_OK) {
						pdo_ctsql_stmt_error2(ctRet, "Not able to convert column to string", "ctsql_stmt_get_col");
						return 0;
					}

					*ptr = S->data;
					*len = strlen(S->data);
				}

				else if (type == PDO_PARAM_INT) {
					zend_long longValue;

					/* convert from smallint to zend_long */
					if (paramType == CTSQL_TINYINT)
						longValue = (zend_long)*((TINYINT*)S->buffer);
					else if (paramType == CTSQL_SMALLINT)
						longValue = (zend_long)*((SMALLINT*)S->buffer);
					else if (paramType == CTSQL_INTEGER)
						longValue = (zend_long)*((INTEGER*)S->buffer);
					else if (paramType == CTSQL_BIGINT) {
#ifdef ZEND_ENABLE_ZVAL_LONG64
						BIGINT bigInt = *(BIGINT*)S->buffer;
						zend_long hl = (zend_long)bigInt.hl;
						longValue = (hl << 32) + bigInt.ll;
#else
						pdo_ctsql_stmt_error("ctsql_stmt_get_col - BIGINT not support on 32 bit driver");
						return 0;
#endif
					}
					else {
						pdo_ctsql_stmt_error("ctsql_stmt_get_col - Invalid PDO type");
						return 0;
					}

					memcpy(S->buffer, &longValue, sizeof(zend_long));
					
					/* keep values as integer */
					*ptr = S->buffer;
					*len = sizeof(zend_long);
				}

				else if (type == PDO_PARAM_BOOL) {
					zend_bool boolValue = (zend_bool)(*((BIT*)S->buffer) == CTSQL_TRUE);
					memcpy(S->buffer, &boolValue, sizeof(zend_bool));

					/* keep values as BOOLEAN */
					*ptr = S->buffer;
					*len = sizeof(zend_bool);
				}

				else {
					pdo_ctsql_stmt_error("ctsql_stmt_get_col - Invalid PDO type");
					return 0;
				}

				*caller_frees = 0;
				return 1;
			}
			else {
				pdo_ctsql_stmt_error("ctsql_stmt_get_col - non-string");
				return 0;
			}
		}
	}

	return 0;
} /* }}} */

struct pdo_stmt_methods ctsql_stmt_methods = {
	ctsql_stmt_dtor,
	ctsql_stmt_execute,
	ctsql_stmt_fetch,
	ctsql_stmt_describe,
	ctsql_stmt_get_col,
	ctsql_stmt_param_hook
};
