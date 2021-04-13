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

#include "ctsqlapi.h"

#define MAX_ERRMSG_LEN 1024
#define MAX_ERRWHAT_LEN 128
#define INIT_COL_LEN 64

extern pdo_driver_t pdo_ctsql_driver;

typedef struct {
	char state[6];
	int errcode;
	char errmsg[MAX_ERRMSG_LEN + 1];
	char what[MAX_ERRWHAT_LEN + 1];
	const char *file;
	int line;
} pdo_ctsql_error_info;

typedef struct {
	pCTSQLCONN conn;
	pdo_ctsql_error_info einfo;
} pdo_ctsql_db_handle;

typedef struct {
	CTSQLCHAR *data;
	int data_size;
	void *buffer;
	int buffer_size;
	pCTSQLCMD cmd;
	pCTSQLCURSOR cursor;
	pdo_ctsql_db_handle *H;
	pdo_ctsql_error_info einfo;
} pdo_ctsql_stmt;

CTSQLRET pdo_ctsql_error(CTSQLRET errorCd, char *errorMsg, pdo_dbh_t *dbh, pdo_stmt_t *stmt, char *what, const char *file, int line);
#define pdo_ctsql_drv_error(what)			pdo_ctsql_error(0, NULL, dbh, NULL, what, __FILE__, __LINE__)
#define pdo_ctsql_stmt_error(what)			pdo_ctsql_error(0, NULL, stmt->dbh, stmt, what, __FILE__, __LINE__)
#define pdo_ctsql_stmt_error2(errorCd, errorMsg, what)	pdo_ctsql_error(errorCd, errorMsg, stmt->dbh, stmt, what, __FILE__, __LINE__)
#define pdo_ctsql_init_error(errorCd, errorMsg, what)	pdo_ctsql_error(errorCd, errorMsg, dbh, NULL, what, __FILE__, __LINE__)

extern struct pdo_stmt_methods ctsql_stmt_methods;

typedef enum { CTSQL_STREAM_OUTPUT, CTSQL_STREAM_INPUT } CTSQL_STREAM_DIRECTION;
typedef struct ctsql_lob_self_ ctsql_lob_self; 

struct ctsql_lob_self_ {
	pdo_stmt_t * stmt;
	void *handle;
	int colnumber;
	char *fld_hdl;
	CTSQL_STREAM_DIRECTION direction;
	zend_off_t offset;
};
