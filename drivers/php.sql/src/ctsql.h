#ifndef PHP_CTSQL_H
#define PHP_CTSQL_H

/*supports*/
#define LVC_SUPPORT
#define LVB_SUPPORT
/*#ifdef ZEND_ENGINE_2*/
#define ARRAY_MEM_OPTIM /* use new method to populate array using reference in case of num & assoc */
/*#endif*/
#define LOB_BUF_SIZE 8192

/*********************************************************/
#define MAXVARNAMELEN TPE_MAX_IDLEN_P1
#define MAX_CONNECTION_LEN 32
#define MAXRowFETCH 256
typedef void * tpe_cursor_type;
typedef long lval_t ;

extern zend_module_entry ctsql_module_entry;
#define phpext_ctsql_ptr &ctsql_module_entry

#ifdef PHP_WIN32
#define PHP_CTSQL_API __declspec(dllexport)
#else
#define PHP_CTSQL_API
#endif


ZEND_MINIT_FUNCTION(ctsql);
ZEND_MSHUTDOWN_FUNCTION(ctsql);
ZEND_RINIT_FUNCTION(ctsql);
ZEND_RSHUTDOWN_FUNCTION(ctsql);
ZEND_MINFO_FUNCTION(ctsql);

/* exported functions declaration */

/*session*/

ZEND_FUNCTION(ctsql_connect);
ZEND_FUNCTION(ctsql_pconnect);
ZEND_FUNCTION(ctsql_close);
ZEND_FUNCTION(ctsql_error);
ZEND_FUNCTION(ctsql_errno);
ZEND_FUNCTION(ctsql_errpos);
ZEND_FUNCTION(ctsql_query);
ZEND_FUNCTION(ctsql_commit);
ZEND_FUNCTION(ctsql_rollback);
ZEND_FUNCTION(ctsql_fetch_assoc);
ZEND_FUNCTION(ctsql_fetch_row);
ZEND_FUNCTION(ctsql_fetch_object);
ZEND_FUNCTION(ctsql_fetch_array);
ZEND_FUNCTION(ctsql_free_result);
ZEND_FUNCTION(ctsql_num_fields);
ZEND_FUNCTION(ctsql_field_name);
ZEND_FUNCTION(ctsql_field_len);
ZEND_FUNCTION(ctsql_field_table);
ZEND_FUNCTION(ctsql_field_type);
ZEND_FUNCTION(ctsql_affected_rows);
ZEND_FUNCTION(ctsql_end_of_fetch);
ZEND_FUNCTION(ctsql_field_info);

struct query {
	lval_t conn;
	void *tpe_puuid; /* tpe_uuid__t */
	tpe_cursor_type tpe_pcur;
	struct sqlda *sqldaptr;
	char sql_alloc;
	short tofetch;
	short fetched;
	short no_more;
	long tran_no; /* we store here the tran_no when the query was executed */
};

struct connection {
	struct sqlca *sqlca;
	void * env; /*dh_sqlenv_hdl_t*/
	char *connection_name;
	long tran_no; /* we increment this value each transacion end */
};

ZEND_BEGIN_MODULE_GLOBALS(ctsql)
/* current connection */
lval_t curr_conn;
#ifdef CURRQUERY
/* current query */
lval_t curr_qry;
#endif
struct connection* conn_ptr;

/* current connection information */
struct sqlca *curr_sqlca;
void * env; /*dh_sqlenv_hdl_t*/
long errorcode;
char errordesc[128];
long errorpos;

/* general configuration values */
long allow_persistent;
long rowfetches;
long php_ctsql_debug;
long exec_error_100;
long query_timeout; /* 0 == infinite */

ZEND_END_MODULE_GLOBALS(ctsql)



/* In every function that needs to use variables in ctsql_globals,
   do call Ct_LS_FETCH(); after declaring other variables used by
   that function, and always refer to them as Ct_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define Ct_D	zend_ctsql_globals *ctsql_globals
#define Ct_DC	, Ct_D
#define Ct_C	ctsql_globals
#define Ct_CC , Ct_C
#define Ct_G(v) (ctsql_globals->v)
#define Ct_LS_FETCH() zend_ctsql_globals *ctsql_globals = ts_resource(ctsql_globals_id);
#else
#define Ct_D	
#define Ct_DC	
#define Ct_C	
#define Ct_CC
#define Ct_G(v) (ctsql_globals.v)
#define Ct_LS_FETCH() 
#endif

#define PSQLCA Ct_G(curr_sqlca)
#define GSQLENV Ct_G(env)
#define PSQLENV &Ct_G(env)
#define GCONNECTION Ct_G(curr_conn)
#define GCONN_PTR Ct_G(conn_ptr)
#ifdef CURRQUERY
#define GQUERY	Ct_G(curr_qry)
#endif
#define GDEBUG	Ct_G(php_ctsql_debug)


#define isResource(x)	((x)->type == IS_RESOURCE)
#define ctSetErrorCode(x)		Ct_G(errorcode) = x
#define ctGetErrorCode()		Ct_G(errorcode)
#define ctSetErrorDesc(x)		strcpy(Ct_G(errordesc), x)
#define ctGetErrorDesc()		Ct_G(errordesc)
#define ctSetErrorPos(x)		Ct_G(errorpos) = x
#define ctGetErrorPos()		Ct_G(errorpos)
#define ctInvalidateConnection()	PSQLCA=NULL;GSQLENV=NULL;GCONNECTION=0;GCONN_PTR=NULL;
#ifdef CURRQUERY
#define ctInvalidateQuery()		GQUERY=0;
#endif
#define DebugLog(x,y,z) if(GDEBUG!=0) _Debug_Log(x,y,z)

struct sqlda *SqldAlloc (tpe_cursor_type tpe_pcur);
void SqldFree(struct query *qry);
void FreeFetchMem(struct query *qry);
void AllocFetchMem(struct query *qry, short rows);
long sql_fetch(struct query *qry);
int PopulateAArray (struct sqlda *sqldap, zval* array);
int PopulateArray (int type,struct query *qry, zval* array);
void php_ctsql_connect(INTERNAL_FUNCTION_PARAMETERS,int persistent);
void php_ctsql_fetch(INTERNAL_FUNCTION_PARAMETERS, int result_type);
void php_ctsql_field_info(INTERNAL_FUNCTION_PARAMETERS, int result_type);
char *type2str(short type);
char *type2strex(short type);
int doquery(struct query *qry, char *qry_txt);
int SwitchConnection(lval_t param);
struct query *SwitchQuery(lval_t param);
void _Debug_Log(char*fnc, char *msg, int error);
unsigned char  *GetBlob(struct query *qry, void *ptr, long dtype, long *bytesread);
char  *GetClob(struct query *qry, void *ptr, long dtype);

#define ASSOCIATIVE 1
#define ENUMERATED 2
#define OBJECT ASSOCIATIVE

#define BOTH ASSOCIATIVE|ENUMERATED


#define FIELD_NAME	1
#define FIELD_LEN	2
#define FIELD_TYPE	3
#define FIELD_TABLE	4

#define QUERY_DONE 0
#define QUERY_FETCH -1
#define QUERY_ERROR 1
#define QUERY_MEMORY 2

#define ERR_BASE		4000
#define WRONG_CONN_ID	ERR_BASE + 1
#define WRONG_QUERY_ID	ERR_BASE + 2

#ifndef ZVAL_ADDREF  /* Required for PHP >5.3 */ 
#define ZVAL_ADDREF  Z_ADDREF_P 
#endif

#endif	/* PHP_CTSQL_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
