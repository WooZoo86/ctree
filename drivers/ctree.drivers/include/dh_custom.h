/* ----------------------------------------------------------------------
 *
 *      Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *      Copyright (C) Dharma Systems (P) Ltd.    1992 - 2020.
 *
 *      This Module contains Proprietary Information of
 *      Dharma Systems Inc. and Dharma Systems (P) Ltd.
 *      and should be treated as Confidential.
 *-----------------------------------------------------------------------
 */

/* ------------------------------------------------------------------------
 *  File Description:
 * ------------------------------------------------------------------------
 *  This is a customization file. Customers can modify values of constants
 *  defined in this file to suit their requirements.
 * -------------------------------------------------------------------------
 */

/*
 * ---------------------------------------------------------------------------
 * Change history
 * ---------------------------------------------------------------------------
 * Project Number : DC737 
 * Date           : 2008-APR-10
 * Title          : Customization Framework 
 * Description    : Introduced this file to define commonly used customer 
 *                  specific definitions.
 * ---------------------------------------------------------------------------
 */

#ifndef         dh_custom_included
#define         dh_custom_included

/* 
 * Define customizable constants here. 
 *
 * Usually you can redefine any constant/macro that is already defined 
 * in either dh_literals.h or sql_lib.h with a value that is specific 
 * to your database system/storage system provided the constant is already
 * defined in one of those files using the following construct:
 *
 *	#if !defined(...)
 *      #define ....
 *      #endif
 * 
 * so that your definition is effective.
 *
 * An example is constant CONSTR_PREFIX that is used in connection strings.
 *
 * Another example is TPE_MAX_FLDLEN that defines maximum length for 
 * character or binary columns. 
 */
#ifdef FAIRCOM_MOD
#define PRODUCT_NAME       "ctreeSQL"
#define COMPANY_NAME1      "FairCom Corporation"
#define COMPANY_NAME2      "Dharma Systems Pvt Ltd-Dharma Systems Inc"
#define DATA_SOURCE_LOGIN  "ctreeSQL Data Source Login"
#define VENDOR             "FairCom"
#define DBA_NAME           "admin"
#define DH_JDBC_PKG_NAME   "ctree.jdbc"

#define DH_ODBC_SETUP_TITLE "c-treeACE ODBC Setup"

#define	DH_SQLSP_DDMJAVACACHE "ctree_sqlsp_DDMJavaCache.h"
#define DH_SQLSP_CLASS_DIR "ctree/sqlsp"
#define	DH_SQLSP_DHSQLRESULTSET "ctree_sqlsp_DhSQLResultSet.h"
#define	DH_SQLSP_SQLDA "ctree_sqlsp_SQLDA.h"
#define	DH_SQLSP_JAVASQL "ctree_sqlsp_JavaSQL.h"
#define	DH_SQLSP_JAVASPLOADER "ctree_sqlsp_JavaSPloader.h"
#define	DH_SQLSP_DHSQLEXCEPTION "ctree_sqlsp_DhSQLException.h"
#define DH_SQLSP_PKG_NAME "ctree.sqlsp"
#define	DH_SQLSP_HEADER_FILE_PREFIX	"ctree_sqlsp"
#define	JNI_FUNCTION_NAME(x,y)	x##ctree_sqlsp##y

#define DH_DFLT_ISOLATION_LEVEL READ_COMMITTED
#define DATA_IN_TPEDATADIR_WITH_DBNAME 1
#define TPE_DATADIR_ENV_NAME "TPE_DATADIR"

#define	DH_ODBC_INV_KW_CHARS	"{}(),;?*=!\\"
#define	DH_DAEMON_PORT 6597

#endif /*FAIRCOM_MOD*/
#endif
