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

/* This file contains all the commonly used vendor specific string
 * literals. The literals in this file could be changed to suit
 * the customer environment, if required.
 */

/* ---------------------------------------------------------------------------
 * Change history
 * ---------------------------------------------------------------------------
 * Project Number : dc611
 * Date           : 2003-NOV-03
 * Title          : Porting Customer changes to Dharma/SQL 9.0
 * Description    : Introduced this file to define commonly used vendor
 *                  specific string literals.
 * ---------------------------------------------------------------------------
 */

/* ---------------------------------------------------------------------------
 * Change History
 * ---------------------------------------------------------------------------
 * Project Number : dc598
 * Date           : 2004-JUL-18
 * Title          : Dharma/SQL 10.0 Release Stabilization.(version_change)
 * ---------------------------------------------------------------------------
 */

/* ---------------------------------------------------------------------------
 * Change history
 * ---------------------------------------------------------------------------
 * Project Number : DC706
 * Date           : 2006-AUG-31
 * Title          : Dharma/SQL Access 11.0+.
 * Description    : Dharma/SQL Access and ODBC Driver version number changes:
 *                  New symbolic constants COPYRIGHT_YEAR1 and COPYRIGHT_YEAR2
 *                  introduced to store the year part of copy right information.
 * ---------------------------------------------------------------------------
 */
/* --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC727
 * Date           : 2008-APR-10
 * Title          : Customization Framework.
 * Description    : Used #if !defined(...) for various constants to define
 *                  dharma default values. 
 * --------------------------------------------------------------------------
 */
/* --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC753 / DC_20090538_3995
 * Date           : 2009-MAY-27
 * Title          : Dharma/SQL Access 11.05 Release
 * Description    : Fix for the bug - ODBC administrator does not show minor 
 *                  driver versions correctly: Corrected the version number
 *                  related conditional definitions. 
 * --------------------------------------------------------------------------
 */
/* --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC753 - DC_20090922_4036
 * Date           : 2009-OCT-07
 * Title          : Dharma/SQL Access 11.05 Release - File version not 
 *                  displayed for dhserver.dll
 * Description    : Changed sub version1 to make it equal to 3rd part 
 *                  of dharma version string. Also removed space and "\0"
 *                  from file version string definition.
 *                  Introduced new constants to store comments, 
 *                  file description, internal filename and 
 *                  original filename information of all the executables 
 *                  and dlls.
 * --------------------------------------------------------------------------
 */
/* ---------------------------------------------------------------------------
 * Change history
 * ---------------------------------------------------------------------------
 * Project Number : DC753
 * Date           : 2010-MAR-22
 * Title          : Dharma/SQL Access 11.05 Release
 * Description    : Changed C++ style comment marker to C style comment
 *                  marker.
 * ---------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change history
 * -------------------------------------------------------------------------
 * Project Number : DC761
 * Date           : 2010-AUG-09
 * Title          : Integration of SDK11.04 changes into SQL/Access.
 * -------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change history
 * -------------------------------------------------------------------------
 * Project Number : DC769
 * Date           : 2011-APR-27
 * Title          : Dharma/SQL Access release.
 * -------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change history
 * -------------------------------------------------------------------------
 * Project Number : DC769
 * Date           : 2011-AUG-19
 * Title          : Dharma/SQL Access release - Fix for customized INI file.
 * -------------------------------------------------------------------------
 */

/* DC727 BEGIN : Customization framework
 *
 * Included dh_custom.h that contains all customer specified definitions.
 */

#include	"dh_custom.h"

/* DC727 END : Customization framework */

/* DC727 END */

#ifndef         dh_literals_included
#define         dh_literals_included

/* We now have a centralized place for Build Info in ctvers.h */
#include "ctvers.h"

/* DC761 Begin */
#ifdef DH_ODBC_SDK
#define DBA_NAME "admin"

#ifdef DH_SDK_NON_COMMERCIAL_VERSION
#ifdef _UNICODE
#ifdef DH_SDK_FOR_JAVA
#define PRODUCT_NAME       "ctreeSQL/SDK For Java (Unicode, Non-Commercial)"
#else
#define PRODUCT_NAME       "ctreeSQL/SDK (Unicode, Non-Commercial)"
#endif
#define DRV_PRODUCT_NAME       "ctreeSQL/SDK (Unicode, Non-Commercial)"
#else
#ifdef DH_SDK_FOR_JAVA
#define PRODUCT_NAME       "ctreeSQL/SDK For Java (Non-Commercial)"
#else
#define PRODUCT_NAME       "ctreeSQL/SDK (Non-Commercial)"
#endif
#define DRV_PRODUCT_NAME       "ctreeSQL/SDK (Non-Commercial)"
#endif
#else
#ifdef _UNICODE
#ifdef DH_SDK_FOR_JAVA
#define PRODUCT_NAME       "ctreeSQL/SDK For Java (Unicode)"
#else
#define PRODUCT_NAME       "ctreeSQL/SDK (Unicode)"
#endif
#define DRV_PRODUCT_NAME       "ctreeSQL/SDK (Unicode)"
#else
#ifdef DH_SDK_FOR_JAVA
#define PRODUCT_NAME       "ctreeSQL/SDK For Java"
#else
#define PRODUCT_NAME       "ctreeSQL/SDK"
#endif
#define DRV_PRODUCT_NAME       "ctreeSQL/SDK"
#endif
#endif

/* DC_20090922_4036 BEGIN */
/*
 * The following constants can be used to customize the names of all
 * executables and DLLs.
 */

/* Customization for server executable */
#define DH_SERVER_EXE_COMMENT "SDK"

#define DH_SERVER_EXE_DESC VENDOR "/SDK Database Server"

#define DH_SERVER_EXE_INTR_NAME "server executable"

#define DH_SERVER_EXE_NAME "ctreesql.exe"

/* Customization for dbdump executable */
#define DH_DBDUMP_EXE_COMMENT "SDK"

#define DH_DBDUMP_EXE_DESC VENDOR "/SDK Database Dump Tool"

#define DH_DBDUMP_EXE_INTR_NAME "dbdump"

#define DH_DBDUMP_EXE_NAME "dbdump.exe"

/* Customization for dbload executable */
#define DH_DBLOAD_EXE_COMMENT "SDK"

#define DH_DBLOAD_EXE_DESC VENDOR "/SDK Database Load Tool"

#define DH_DBLOAD_EXE_INTR_NAME "dbload"

#define DH_DBLOAD_EXE_NAME "dbload.exe"

/* Customization for dbschema executable */
#define DH_DBSCHEMA_EXE_COMMENT "SDK"

#define DH_DBSCHEMA_EXE_DESC VENDOR "/SDK Database Schema Generation Tool"

#define DH_DBSCHEMA_EXE_INTR_NAME "dbschema"

#define DH_DBSCHEMA_EXE_NAME "dbschema.exe"

/* Customization for efglc executable */
#define DH_EFGLC_EXE_COMMENT "SDK"

#define DH_EFGLC_EXE_DESC VENDOR "/SDK efglc executable"

#define DH_EFGLC_EXE_INTR_NAME "efglc"

#define DH_EFGLC_EXE_NAME "efglc.exe"

/* Customization for esqlc executable */
#define DH_ESQLC_EXE_COMMENT "SDK"

#define DH_ESQLC_EXE_DESC VENDOR "/SDK Embedded SQL/C Precompiler"

#define DH_ESQLC_EXE_INTR_NAME "esqlc"

#define DH_ESQLC_EXE_NAME "esqlc.exe"

/* Customization for mdcreate executable */
#define DH_FFCREAT_EXE_COMMENT "SDK"

#define DH_FFCREAT_EXE_DESC VENDOR "/SDK Database Creation Tool"

#define DH_FFCREAT_EXE_INTR_NAME "mdcreate"

#define DH_FFCREAT_EXE_NAME "mdcreate.exe"

/* Customization for isql executable */
#define DH_ISQL_EXE_COMMENT "SDK"

#define DH_ISQL_EXE_DESC VENDOR "/SDK Interactive SQL Tool"

#define DH_ISQL_EXE_INTR_NAME "isql"

#define DH_ISQL_EXE_NAME "isql.exe"

/* Customization for misql executable */
#define DH_MISQL_EXE_COMMENT "SDK"

#define DH_MISQL_EXE_DESC VENDOR "/SDK Merged Interactive SQL Tool"

#define DH_MISQL_EXE_INTR_NAME "misql"

#define DH_MISQL_EXE_NAME "misql.exe"

/* Customization for odbcisql executable */
#define DH_ODBCISQL_EXE_COMMENT "SDK"

#define DH_ODBCISQL_EXE_DESC VENDOR "/SDK ODBC Driver Based Interactive SQL Tool"

#define DH_ODBCISQL_EXE_INTR_NAME "odbcisql"

#define DH_ODBCISQL_EXE_NAME "odbcisql.exe"

/* Customization for dhsodbc dll */
#define DH_ODBC_DLL_COMMENT ""

#ifdef DH_SDK_NON_COMMERCIAL_VERSION
#ifdef _UNICODE
#define DH_ODBC_DLL_DESC VENDOR " ODBC Driver (Unicode, Non-Commercial)"
#define DH_ODBC_DLL_INTR_NAME "ODBC Driver DLL (Unicode, Non-Commercial)"
#else
#define DH_ODBC_DLL_DESC VENDOR " ODBC Driver (Non-Commercial)"
#define DH_ODBC_DLL_INTR_NAME "ODBC Driver DLL (Non-Commercial)"
#endif
#else
#ifdef _UNICODE
#define DH_ODBC_DLL_DESC VENDOR " ODBC Driver (Unicode)"
#define DH_ODBC_DLL_INTR_NAME "ODBC Driver DLL (Unicode)"
#else
#define DH_ODBC_DLL_DESC VENDOR " ODBC Driver"

#define DH_ODBC_DLL_INTR_NAME "ODBC Driver DLL"
#endif
#endif

#define DH_ODBC_DLL_NAME "dhsodbc.dll"

/* Customization for dhsetup dll */
#define DH_SETUP_DLL_COMMENT ""

#ifdef DH_SDK_NON_COMMERCIAL_VERSION
#ifdef _UNICODE
#define DH_SETUP_DLL_DESC VENDOR " ODBC Driver Setup (Unicode, Non-Commercial)"
#define DH_SETUP_DLL_INTR_NAME "ODBC Driver Setup DLL (Unicode, Non-Commercial)"
#else
#define DH_SETUP_DLL_DESC VENDOR " ODBC Driver Setup (Non-Commercial)"
#define DH_SETUP_DLL_INTR_NAME "ODBC Driver Setup DLL (Non-Commercial)"
#endif
#else
#ifdef _UNICODE
#define DH_SETUP_DLL_DESC VENDOR " ODBC Driver Setup (Unicode)"
#define DH_SETUP_DLL_INTR_NAME "ODBC Driver Setup DLL (Unicode)"
#else
#define DH_SETUP_DLL_DESC VENDOR " ODBC Driver Setup"

#define DH_SETUP_DLL_INTR_NAME "ODBC Driver Setup DLL"
#endif
#endif

#define DH_SETUP_DLL_NAME "dhsetup.dll"

/* Customization for odbcdir dll */
#define DH_ODBCDIR_DLL_COMMENT ""

#define DH_ODBCDIR_DLL_DESC VENDOR " Direct ODBC Driver DLL"

#define DH_ODBCDIR_DLL_INTR_NAME "odbcdir dll"

#define DH_ODBCDIR_DLL_NAME "odbcdir.dll"

/* Customization for pcntreg executable */
#define DH_PCNTREG_EXE_COMMENT "SDK"

#define DH_PCNTREG_EXE_DESC VENDOR "/SDK Windows Service Registration Tool"

#define DH_PCNTREG_EXE_INTR_NAME "pcntreg"

#define DH_PCNTREG_EXE_NAME "pcntreg.exe"
/* DC_20090922_4036 END */ 

#endif
/* DC761 End */

/* Macro for Connection string prefix.
 * This macro is used as the prefix when connection string is constructed.
 *
 * This literal is used in following files:
 * src/odcb/src/attrib.cxx
 * Functions : odbc_dsn_t::build_con_str() and odbc_driver_t::build_con_str().
 *
 * snw/snr/snr_nxp.cxx
 * Function:dxp_hdl_t::dxp_build_clthdl().
 */

#if !defined(CONSTR_PREFIX) /* DC727 */
#define CONSTR_PREFIX      "dharma"
#endif  /* DC727 */

/* Macro for Product Name.
 * This literal is used for displaying the product name.
 *
 * This literal is used in following files:
 * src/odbc/src/dherr.cxx
 * Functions : dh_odbc_err_t::get_sqlstate(), dh_odbc_err_t::get_sqldiagrec()
 *             and dh_odbc_err_t::get_sqldiagfield().
 *
 * src/odbc/src/info.cxx
 * Function  : DBC::SQLGetInfo().
 *
 * src/public/os/winnt/os_net.cxx
 * Function : void setup_winsock().
 *
 * src/public/os/winnt/pcntreg.cxx
 * Function: void Usage().
 */

#if !defined(PRODUCT_NAME)
#define PRODUCT_NAME       "ctreeSQL"
#endif

#if !defined(DRV_PRODUCT_NAME)
#define DRV_PRODUCT_NAME  PRODUCT_NAME
#endif

/* Macro for Company name.
 * The two literals below are used for displaying the banner on the screen.
 *
 * This literal is used in following file:
 * src/public/generic/version.cxx
 * Function : tpe_print_banner().
 */

#if !defined(COMPANY_NAME1) /* DC727 */
#define COMPANY_NAME1      "FairCom Corporation"
#endif   /* DC727 */
#if !defined(COMPANY_NAME2) /* DC727 */
#define COMPANY_NAME2      "Dharma Systems Inc"
#endif   /* DC727 */

/* Macro for caption Dharma Data Source Login.
 * This literal is used as a caption of the dialog box and message box.
 *
 * This literal is used in following files:
 * src/odbc/src/os_conn.cxx
 * Function: RETCODE DBC::call_connect().
 *
 * src/odbc/src/login.rc
 */

#if !defined(DATA_SOURCE_LOGIN) /* DC727 */
#define DATA_SOURCE_LOGIN  "ctreeSQL Data Source Login"
#endif   /* DC727 */

/* Macro for Vendor name.
 * This macro is used for displaying the vendor name.
 *
 * This literal is used in following files:
 * src/public/os/winnt/os_winnt.cxx
 * Functions : GetListenerName() and GetSoftwareName().
 *
 * src/public/generic/version.cxx
 * Function : tpe_print_banner().
 *
 * src/odbc/src/dherr.cxx
 * Functions : dh_odbc_err_t::get_sqlstate(), dh_odbc_err_t ::get_sqldiagrec(),
 *             and dh_odbc_err_t::get_sqldiagfield().
 */

#if !defined(VENDOR) /* DC727 */
#define VENDOR             "FairCom"
#endif  /* DC727 */

/* Macro for DBA 
 * This macro is used in src/public/env/env.hxx.
 */

#if !defined(DBA_NAME) /* DC727 */
#define DBA_NAME "admin"
#endif /* DC727 */

/*dc598 BEGIN : Dharma/SQL 10.0 Release Stabilization.*/
/* DC769 BEGIN */
/*
 * Dharma versions
 */
/* ctSIBLING_VERSIONS: Product Version Numbers References */
#ifdef DH_ODBC_INT
#if !defined(ACCESS_VERSION) /* DC727 */
#define ACCESS_VERSION "2.0.0"
#endif /* DC727 */
#if !defined(DRIVER_VERSION) /* DC727 */
#define DRIVER_VERSION "02.00.0000"
#endif /* DC727 */
#else
#if !defined(ACCESS_VERSION) /* DC727 */
#define ACCESS_VERSION "15.02.00.0000" 
#endif /* DC727 */
#if !defined(DRIVER_VERSION) /* DC727 */
#define DRIVER_VERSION "15.02.00.0000"
#endif /* DC727 */
#endif 

#if !defined(DH_MAJOR_VERSION)
#define	DH_MAJOR_VERSION	15
#endif

#if !defined(DH_MINOR_VERSION)
#define	DH_MINOR_VERSION	02
#endif

#if !defined(DH_SUB_MINOR_VERSION1) /* DC_20090538_3995 */ 
#define	DH_SUB_MINOR_VERSION1	00
#endif

#if !defined(DH_SUB_MINOR_VERSION2) /* DC_20090538_3995 */
#define	DH_SUB_MINOR_VERSION2	000
#endif

#if !defined(DH_VER_FILEVERSION_STR)
#define	DH_VER_FILEVERSION_STR	"15.02.00.0000"
#endif

#if !defined(COPYRIGHT_YEAR1)  /* DC727 */
#define COPYRIGHT_YEAR1 "2020"
#endif /* DC727 */
#if !defined(COPYRIGHT_YEAR2)  /* DC727 */
#define COPYRIGHT_YEAR2 "2020"
#endif /* DC727 */
#if !defined(COPYRIGHT_DATE)  /* DC727 */
#define COPYRIGHT_DATE "1992 - 2020"
#endif /* DC727 */
/* DC769 END */
/* DC727 BEGIN */

#if !defined(TPE_DATADIR_ENV_NAME)
#define	TPE_DATADIR_ENV_NAME	"TPE_DATADIR"
#endif
                                                                                                                             
#if !defined(DATA_IN_TPEDATADIR_WITH_DBNAME)
#define	DATA_IN_TPEDATADIR_WITH_DBNAME	1
#endif

/* For  Case-Insensitive comparision */
#if !defined(DH_CASE_INSENSITIVE_COL)
#define	DH_CASE_INSENSITIVE_COL		0
#endif

/* DC727 END */

/* DC727 BEGIN */
                                                                                                                             
#if  !defined(DH_EMPTY_ZERODOT_STR_IS_NULL)
#define	DH_EMPTY_ZERODOT_STR_IS_NULL	0
#endif
                                                                                                                             
#if !defined(DH_PADDING_CHAR)
#define	DH_PADDING_CHAR	DH_CHAR_LITERAL(' ')
#endif
                                                                                                                             
#if !defined(DH_ADDITIONAL_ERR_MGRS)
#define	DH_ADDITIONAL_ERR_MGRS	0
#define	DH_ADDITIONAL_ERR_MGR_ENUMS
#endif
                                                                                                                             
#if !defined(DH_ERR_MGR_DUMMY)
#define	DH_ERR_MGR_DUMMY	0
#endif

/* The DH_XEC_INVAL_TREES is defined in order to invalidate the trees */

#if !defined(DH_XEC_INVAL_TREES)
#define	DH_XEC_INVAL_TREES	0
#endif

/*
 * Do not have the following code enabled so that if customization is
 * not needed we will save time by avoiding changing each source file.
 */
/*
#if !defined(DH_JDBC_PKG_NAME)
#define       DH_JDBC_PKG_NAME        "dharma.jdbc"
#endif
*/

#if !defined(DH_JDBC_DRIVER_CLASS_NAME)
#define       DH_JDBC_DRIVER_CLASS_NAME        "DharmaDriver"
#endif

#if !defined(DH_SQLSP_PKG_NAME)
#define	DH_SQLSP_PKG_NAME	"dharma.sqlsp"
#endif

#if !defined(DH_SQLSP_CLASS_DIR)
#define	DH_SQLSP_CLASS_DIR	"dharma/sqlsp"
#endif

#if !defined(DH_SQLSP_HEADER_FILE_PREFIX)
#define	DH_SQLSP_HEADER_FILE_PREFIX	"dharma_sqlsp"
#endif

#if !defined(JNI_FUNCTION_NAME)
#define	JNI_FUNCTION_NAME(x,y)	x##dharma_sqlsp##y
#endif

#if !defined(DH_SQLSP_DDMJAVACACHE)
#define	DH_SQLSP_DDMJAVACACHE	"dharma_sqlsp_DDMJavaCache.h"
#endif

#if !defined(DH_SQLSP_DHSQLRESULTSET)
#define	DH_SQLSP_DHSQLRESULTSET	"dharma_sqlsp_DhSQLResultSet.h"
#endif
 
#if !defined(DH_SQLSP_SQLDA)
#define	DH_SQLSP_SQLDA		"dharma_sqlsp_SQLDA.h"
#endif

#if !defined(DH_SQLSP_JAVASQL)
#define	DH_SQLSP_JAVASQL	"dharma_sqlsp_JavaSQL.h"
#endif

#if !defined(DH_SQLSP_JAVASPLOADER)
#define	DH_SQLSP_JAVASPLOADER	"dharma_sqlsp_JavaSPloader.h"
#endif

#if !defined(DH_SQLSP_DHSQLEXCEPTION)
#define	DH_SQLSP_DHSQLEXCEPTION	"dharma_sqlsp_DhSQLException.h"
#endif

#if !defined(DH_RSSSTUBS_JNICALL)
#define	DH_RSSSTUBS_JNICALL	0
#endif
                                                                                                                             
/* DC727 END */

/* DC727 BEGIN */

#if !defined(DH_ODBC_INV_KW_CHARS)
#define	DH_ODBC_INV_KW_CHARS	"{}(),;?*=!@\\"
#endif

#if !defined(DH_CONN_DLG_SERVICE_REQD)
#define DH_CONN_DLG_SERVICE_REQD	1
#endif

#if !defined(DH_ODBC_SETUP_TITLE)
#define	DH_ODBC_SETUP_TITLE	"Dharma ODBC Setup"
#endif

/* DC727 END */

/* DC727 BEGIN */

#if !defined(DH_DFLT_ISOLATION_LEVEL)
#define	DH_DFLT_ISOLATION_LEVEL	SERIALIZABLE
#endif
                                                                                                                             
                                                                                                                             
#if !defined(DH_LOWERCASE_UID)
#define	DH_LOWERCASE_UID	1
#endif
                                                                                                                             
#if !defined(DH_ISQL_USAGE_WITH_NOARGS)
#define	DH_ISQL_USAGE_WITH_NOARGS	0
#endif
                                                                                                                             
#if !defined(DH_PASSWD_SALT)
#define	DH_PASSWD_SALT		0
#endif
                                                                                                                             
#if !defined(DH_STATIC_JVM)
#define	DH_STATIC_JVM		0
#endif
                                                                                                                             
#if !defined(DH_FOREIGN_KEY_COL_NAME_CHANGED)
#define	DH_FOREIGN_KEY_COL_NAME_CHANGED	0
#endif
                                                                                                                             
#if !defined(DH_CONN_MESSAGE)
#define	DH_CONN_MESSAGE		0
#endif

#if !defined(DH_MULTIPLE_CONN_ATTEMPTS)
#define	DH_MULTIPLE_CONN_ATTEMPTS	1
#endif

#if !defined(DH_CHECK_SVR_ADMN_PRIV)
#ifdef FAIRCOM_MOD
#define	DH_CHECK_SVR_ADMN_PRIV	0 /* (used in tcp_dmn.cxx*/
#else
#define	DH_CHECK_SVR_ADMN_PRIV	1
#endif
#endif

#if !defined(DH_MORE_STACK)
#define	DH_MORE_STACK		0
#endif
                                                                                                                             
#if !defined(DH_WIN_CURR_UNAME)
#define	DH_WIN_CURR_UNAME	0
#endif
                                                                                                                             
#if !defined(DH_PROMPT_FOR_PASSWD)
#define	DH_PROMPT_FOR_PASSWD	0
#endif
                                                                                                                             
#if !defined(DH_GET_FROM_ENV)
#define	DH_GET_FROM_ENV		0
#endif

/* DC769 Begin */
/* 
 * Symbol DH_SQL_ACC_INI_FILE is already documented in the manual.
 * But, symbol DH_SQL_INI_FILE was introduced later. Due to this new symbol, 
 * customization of INI file using DH_SQL_ACC_INI_FILE did not work. 
 * In order to make the documented symbol work as expected, added the 
 * following code to make both the symbols equal.
 */
#if defined(DH_SQL_ACC_INI_FILE)
#define DH_SQL_INI_FILE  DH_SQL_ACC_INI_FILE
#else
#undef DH_SQL_INI_FILE
#endif
/* Dc769 End */

/* DC761 Begin */
#if !defined(DH_SQL_INI_FILE)
#ifdef DH_ODBC_SDK
#define	DH_SQL_INI_FILE	"dhsodbc.ini"
#else
#ifdef DH_ODBC_INT
#define	DH_SQL_INI_FILE	"dhodbci.ini"
#else
#define	DH_SQL_INI_FILE	"dhsql.ini"
#endif
#endif
#endif
/* DC761 End */


#if !defined(DH_LIC_CHECK)
#define	DH_LIC_CHECK		0
#endif
                                                                                                                             
#if !defined(DH_DATA_IN_FF)
#define DH_DATA_IN_FF		0
#endif

#if !defined(DH_SET_CURR_TXN)
#define DH_SET_CURR_TXN		0
#endif

#if !defined(DH_DBS_GENERATE_SYSTEM_TBLS)
#define	DH_DBS_GENERATE_SYSTEM_TBLS	0
#endif

#if !defined(DH_DBDUMP_PASSWD_REQUIRED)
#define	DH_DBDUMP_PASSWD_REQUIRED	1
#endif

#if !defined(DH_DUMMY_EUID)
#define	DH_DUMMY_EUID	0
#endif

#if !defined(DH_ENABLE_VCHAR)
#define DH_ENABLE_VCHAR  1
#endif

#if !defined(DH_ERR_ON_CHAR_OVERFLOW)
#define DH_ERR_ON_CHAR_OVERFLOW	1
#endif

#if !defined(DH_IDCASE_SUPPORTED_IN_DB)
#define DH_IDCASE_SUPPORTED_IN_DB	1
#endif
/* DC727 END */

/* DC_20090922_4036 BEGIN */ /* DC753 */

/* 
 * The following constants can be used to customize the names of all 
 * executables and DLLs.
 */

/* Customization for server executable */ /* DC753 */
#if !defined(DH_SERVER_EXE_COMMENT)
#define DH_SERVER_EXE_COMMENT "SQL"
#endif

#if !defined(DH_SERVER_EXE_DESC )
#define DH_SERVER_EXE_DESC VENDOR "/SQL Database Server"
#endif

#if !defined(DH_SERVER_EXE_INTR_NAME)
#define DH_SERVER_EXE_INTR_NAME "server executable"
#endif

#if !defined(DH_SERVER_EXE_NAME)
#define DH_SERVER_EXE_NAME "dhserver.exe"
#endif

/* Customization for dbdump executable */ /* DC753 */
#if !defined(DH_DBDUMP_EXE_COMMENT)
#define DH_DBDUMP_EXE_COMMENT "SQL"
#endif

#if !defined(DH_DBDUMP_EXE_DESC )
#define DH_DBDUMP_EXE_DESC VENDOR "/SQL Database Dump Tool"
#endif

#if !defined(DH_DBDUMP_EXE_INTR_NAME)
#define DH_DBDUMP_EXE_INTR_NAME "dbdump"
#endif

#if !defined(DH_DBDUMP_EXE_NAME)
#define DH_DBDUMP_EXE_NAME "dbdump.exe"
#endif

/* Customization for dbload executable */ /* DC753 */
#if !defined(DH_DBLOAD_EXE_COMMENT)
#define DH_DBLOAD_EXE_COMMENT "SQL"
#endif

#if !defined(DH_DBLOAD_EXE_DESC )
#define DH_DBLOAD_EXE_DESC VENDOR "/SQL Database Load Tool"
#endif

#if !defined(DH_DBLOAD_EXE_INTR_NAME)
#define DH_DBLOAD_EXE_INTR_NAME "dbload"
#endif

#if !defined(DH_DBLOAD_EXE_NAME)
#define DH_DBLOAD_EXE_NAME "dbload.exe"
#endif

/* Customization for dbschema executable */ /* DC753 */
#if !defined(DH_DBSCHEMA_EXE_COMMENT)
#define DH_DBSCHEMA_EXE_COMMENT "SQL" 
#endif

#if !defined(DH_DBSCHEMA_EXE_DESC )
#define DH_DBSCHEMA_EXE_DESC VENDOR "/SQL Database Schema Generation Tool"
#endif

#if !defined(DH_DBSCHEMA_EXE_INTR_NAME)
#define DH_DBSCHEMA_EXE_INTR_NAME "dbschema"
#endif

#if !defined(DH_DBSCHEMA_EXE_NAME)
#define DH_DBSCHEMA_EXE_NAME "dbschema.exe"
#endif

/* Customization for efglc executable */ /* DC753 */
#if !defined(DH_EFGLC_EXE_COMMENT)
#define DH_EFGLC_EXE_COMMENT "SQL" 
#endif

#if !defined(DH_EFGLC_EXE_DESC )
#define DH_EFGLC_EXE_DESC VENDOR "/SQL efglc executable"
#endif

#if !defined(DH_EFGLC_EXE_INTR_NAME)
#define DH_EFGLC_EXE_INTR_NAME "efglc"
#endif

#if !defined(DH_EFGLC_EXE_NAME)
#define DH_EFGLC_EXE_NAME "efglc.exe"
#endif

/* Customization for esqlc executable */ /* DC753 */
#if !defined(DH_ESQLC_EXE_COMMENT)
#define DH_ESQLC_EXE_COMMENT "SQL" 
#endif

#if !defined(DH_ESQLC_EXE_DESC )
#define DH_ESQLC_EXE_DESC VENDOR "/SQL Embedded SQL/C Precompiler"
#endif

#if !defined(DH_ESQLC_EXE_INTR_NAME)
#define DH_ESQLC_EXE_INTR_NAME "esqlc" 
#endif

#if !defined(DH_ESQLC_EXE_NAME)
#define DH_ESQLC_EXE_NAME "esqlc.exe"
#endif

/* Customization for syscreat executable */ /* DC753 */
#if !defined(DH_SYSCREAT_EXE_COMMENT)
#define DH_SYSCREAT_EXE_COMMENT "SQL" 
#endif

#if !defined(DH_SYSCREAT_EXE_DESC )
#define DH_SYSCREAT_EXE_DESC VENDOR "/SQL Database Creation Tool"
#endif

#if !defined(DH_SYSCREAT_EXE_INTR_NAME)
#define DH_SYSCREAT_EXE_INTR_NAME "syscreat" 
#endif

#if !defined(DH_SYSCREAT_EXE_NAME)
#define DH_SYSCREAT_EXE_NAME "syscreat.exe"
#endif

/* Customization for ffcreat executable */ /* DC753 */
#if !defined(DH_FFCREAT_EXE_COMMENT)
#define DH_FFCREAT_EXE_COMMENT "SQL" 
#endif

#if !defined(DH_FFCREAT_EXE_DESC )
#define DH_FFCREAT_EXE_DESC VENDOR "/SQL Database Creation Tool"
#endif

#if !defined(DH_FFCREAT_EXE_INTR_NAME)
#define DH_FFCREAT_EXE_INTR_NAME "ffcreat" 
#endif

#if !defined(DH_FFCREAT_EXE_NAME)
#define DH_FFCREAT_EXE_NAME "ffcreat.exe"
#endif

/* Customization for isql executable */ /* DC753 */
#if !defined(DH_ISQL_EXE_COMMENT)
#define DH_ISQL_EXE_COMMENT "SQL" 
#endif

#if !defined(DH_ISQL_EXE_DESC )
#define DH_ISQL_EXE_DESC VENDOR "/SQL Interactive SQL Tool"
#endif

#if !defined(DH_ISQL_EXE_INTR_NAME)
#define DH_ISQL_EXE_INTR_NAME "isql"
#endif

#if !defined(DH_ISQL_EXE_NAME)
#define DH_ISQL_EXE_NAME "isql.exe"
#endif

/* Customization for misql executable */ /* DC753 */
#if !defined(DH_MISQL_EXE_COMMENT)
#define DH_MISQL_EXE_COMMENT "SQL"
#endif

#if !defined(DH_MISQL_EXE_DESC )
#define DH_MISQL_EXE_DESC VENDOR "/SQL Merged Interactive SQL Tool"
#endif

#if !defined(DH_MISQL_EXE_INTR_NAME)
#define DH_MISQL_EXE_INTR_NAME "misql"
#endif

#if !defined(DH_MISQL_EXE_NAME)
#define DH_MISQL_EXE_NAME "misql.exe"
#endif

/* Customization for odbcisql executable */ /* DC753 */
#if !defined(DH_ODBCISQL_EXE_COMMENT)
#define DH_ODBCISQL_EXE_COMMENT "SQL" 
#endif

#if !defined(DH_ODBCISQL_EXE_DESC )
#define DH_ODBCISQL_EXE_DESC VENDOR "/SQL ODBC Driver Based Interactive SQL Tool"
#endif

#if !defined(DH_ODBCISQL_EXE_INTR_NAME)
#define DH_ODBCISQL_EXE_INTR_NAME "odbcisql"
#endif

#if !defined(DH_ODBCISQL_EXE_NAME)
#define DH_ODBCISQL_EXE_NAME "odbcisql.exe"
#endif

/* Customization for pcntreg executable */ /* DC753 */
#if !defined(DH_PCNTREG_EXE_COMMENT)
#define DH_PCNTREG_EXE_COMMENT "SQL" 
#endif

#if !defined(DH_PCNTREG_EXE_DESC )
#define DH_PCNTREG_EXE_DESC VENDOR "/SQL Windows Service Registration Tool"
#endif

#if !defined(DH_PCNTREG_EXE_INTR_NAME)
#define DH_PCNTREG_EXE_INTR_NAME "pcntreg" 
#endif

#if !defined(DH_PCNTREG_EXE_NAME)
#define DH_PCNTREG_EXE_NAME "pcntreg.exe"
#endif

/* Customization for pefglc executable */ /* DC753 */
#if !defined(DH_PEFGLC_EXE_COMMENT)
#define DH_PEFGLC_EXE_COMMENT "SQL"
#endif

#if !defined(DH_PEFGLC_EXE_DESC )
#define DH_PEFGLC_EXE_DESC VENDOR "/SQL pefglc executable"
#endif

#if !defined(DH_PEFGLC_EXE_INTR_NAME)
#define DH_PEFGLC_EXE_INTR_NAME "pefglc"
#endif

#if !defined(DH_PEFGLC_EXE_NAME)
#define DH_PEFGLC_EXE_NAME "pefglc.exe"
#endif

/* Customization for dhserver dll */ /* DC753 */
#if !defined(DH_SERVER_DLL_COMMENT)
#define DH_SERVER_DLL_COMMENT "SQL" 
#endif

#if !defined(DH_SERVER_DLL_DESC )
#define DH_SERVER_DLL_DESC VENDOR "/SQL Database Server DLL" 
#endif

#if !defined(DH_SERVER_DLL_INTR_NAME)
#define DH_SERVER_DLL_INTR_NAME "server dll"
#endif

#if !defined(DH_SERVER_DLL_NAME)
#define DH_SERVER_DLL_NAME "dhserver.dll"
#endif

/* Customization for dhodbc dll */ /* DC753 */
#if !defined(DH_ODBC_DLL_COMMENT)
#define DH_ODBC_DLL_COMMENT ""
#endif

#if !defined(DH_ODBC_DLL_DESC )
#define DH_ODBC_DLL_DESC VENDOR " ODBC Driver"
#endif

#if !defined(DH_ODBC_DLL_INTR_NAME)
#define DH_ODBC_DLL_INTR_NAME "ODBC Driver DLL"
#endif

#if !defined(DH_ODBC_DLL_NAME)
#define DH_ODBC_DLL_NAME "dhodbc.dll"
#endif

/* Customization for dhsetup dll */ /* DC753 */
#if !defined(DH_SETUP_DLL_COMMENT)
#define DH_SETUP_DLL_COMMENT ""
#endif

#if !defined(DH_SETUP_DLL_DESC )
#define DH_SETUP_DLL_DESC VENDOR " ODBC Driver Setup" 
#endif

#if !defined(DH_SETUP_DLL_INTR_NAME)
#define DH_SETUP_DLL_INTR_NAME "ODBC Driver Setup DLL" 
#endif

#if !defined(DH_SETUP_DLL_NAME)
#define DH_SETUP_DLL_NAME "dhsetup.dll"
#endif

/* Customization for odbcdir dll */ /* DC753 */
#if !defined(DH_ODBCDIR_DLL_COMMENT)
#define DH_ODBCDIR_DLL_COMMENT "" 
#endif

#if !defined(DH_ODBCDIR_DLL_DESC )
#define DH_ODBCDIR_DLL_DESC VENDOR " Direct ODBC Driver DLL" 
#endif

#if !defined(DH_ODBCDIR_DLL_INTR_NAME)
#define DH_ODBCDIR_DLL_INTR_NAME "odbcdir dll" 
#endif

#if !defined(DH_ODBCDIR_DLL_NAME)
#define DH_ODBCDIR_DLL_NAME "odbcdir.dll"
#endif
/* DC_20090922_4036 END  */

/*dc598 END : Dharma/SQL 10.0 Release Stabilization.*/
#endif /*dh_literals_included*/

