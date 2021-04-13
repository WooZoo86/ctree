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

/* {{{ pdo_ctsql_functions[] */
const zend_function_entry pdo_ctsql_functions[] = {
	PHP_FE_END
};
/* }}} */

/* {{{ pdo_ctsql_module_entry */

#if ZEND_MODULE_API_NO >= 20050922
static const zend_module_dep pdo_ctsql_deps[] = {
	ZEND_MOD_REQUIRED("pdo")
	ZEND_MOD_END
};
#endif

zend_module_entry pdo_ctsql_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	pdo_ctsql_deps,
	"pdo_ctsql",
	pdo_ctsql_functions,
	PHP_MINIT(pdo_ctsql),
	PHP_MSHUTDOWN(pdo_ctsql),
	NULL,
	NULL,
	PHP_MINFO(pdo_ctsql),
	PHP_PDO_CTSQL_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PDO_CTSQL
ZEND_GET_MODULE(pdo_ctsql)
#endif

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pdo_ctsql)
{
	php_pdo_register_driver(&pdo_ctsql_driver);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(pdo_ctsql)
{
	php_pdo_unregister_driver(&pdo_ctsql_driver);
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pdo_ctsql)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "PDO Driver for c-treeSQL", "enabled");
	php_info_print_table_row(2, "Client API version", "12.0.0.144(Build-201119)");  /* FcLibMasterVERSIONSTAMP  pdo_ctsql.c:1 - DO NOT REMOVE THIS COMMENT */
	php_info_print_table_end();
}
/* }}} */
