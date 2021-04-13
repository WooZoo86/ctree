/*
 *      OFFICIAL NOTIFICATION: the following CONFIDENTIAL and PROPRIETARY 
 * 	property legend shall not be removed from this source code module 
 * 	for any reason.
 *
 *	This program is the CONFIDENTIAL and PROPRIETARY property 
 *	of FairCom(R) Corporation. Any unauthorized use, reproduction or
 *	transfer of this computer program is strictly prohibited. The 
 *      contents of this file may not be disclosed to third parties, copied or
 *      duplicated in any form, in whole or in part, without the prior written
 *      permission of the FairCom(R) Corporation.
 *
 *      Copyright (c) 1992 - 2020 FairCom Corporation.
 *	This is an unpublished work, and is subject to limited distribution and
 *	restricted disclosure only. ALL RIGHTS RESERVED.
 *
 *			RESTRICTED RIGHTS LEGEND
 *	Use, duplication, or disclosure by the Government is subject to
 *	restrictions set forth in subparagraph (c)(1)(ii) of the Rights in
 * 	Technical Data and Computer Software clause at DFARS 252.227-7013, and/or
 *      in similar or successor clauses in the FAR, DOD or NASA FAR Supplement.
 *      Unpublished rights reserved under the Copyright Laws of the United States.
 *	FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203.
 *
 *	c-treeACE(tm)	Version 11
 */

/* 
This header is included from ctopt2.h in the c-tree code code to set SQL options.
This header file is also used by FairCom as a global include for Dharma's
source code. We use this when we need to control #define's for our 
special purposes.  It is always included as the FIRST THING in any of
the Dharma's source (not ctree source), so it is intended to act as if these 
#define's are from the cammand line.
*/

#ifndef	 __CTSQL_LIB_H__
#define  __CTSQL_LIB_H__

#include "ctvers.h"

#ifndef FAIRCOM_CODE_SKIP /* never define it! it is used by code filtering */
#ifndef FAIRCOM_CODE
#error FAIRCOM_CODE must be defined
#endif
#endif

#ifdef ctSQLSRVR
#ifdef __cplusplus
extern "C" {
#endif
#include "ctstdr.h"
#include "ctoptn.h"
#ifdef __cplusplus
}
#endif
#endif

#ifndef MAX_SERVER_NAME
#define MAX_SERVER_NAME 255 /* maximum length of server name */
#endif

#ifndef ct_OEMH
#include "ct_oem.h"
#endif

#include "ctvers.h"			/* Build Info */

/*#define DHARMA_SQL_DB_CREATION */ 	/* use dharma's SQL db default creation way DO NOT TURN ON unless updating system tables creation logic*/

#define ctSQL_NO_COSTS 			/* deactivate STUB COSTS functions until improved */
/* #define ctSQL_USE_TABLE_SPACES */ 	/* enable the table spaces support */
#define ctSQL_PREPEND_OWNER 		/* enable the prepend owner support */
/* #define ctSQL_NO_FILEPERM */ 	/* relax file permissions */
#define ctSQL_VALIDATE_USER  		/* enable user authentication */
#define ctSQL_FASTDBCREATION		/* enable possibility to create template db */
#define ctSQL_CTDB_TEMPLATE 		/* use CTDB to create the template */
/* #define ctSQL_FORCEctreeSQL */ 	/* Always create the ctreeSQL database, even when another exists */
#define ctSQL_DEBUG_INDEX 		/* activate debug index support */
#define ctSQL_DBRENAME_DURING_COPY	/* logic to change the database name at "copy" time avoids problems with recovery*/

#define ctSQL_DYN_DBG 			/* activate support for dynamic debug on/off support*/


#define ctSQL_DB_CASE 			/* activate database sensitivity support */
#define ctSQL_PERSIST_DB_CASE 		/* persist the database sensitivity info into the db */
#define ctSQL_USE_PUSHDOWN   		/* enable the expression pushdown*/
#define ctSQL_ENV_LOOKUP		/* enable special os_setenv */

#ifndef ctSQL_MAX_FLDLEN		/* Could be overriddedn in ctsqlovr.h */
#ifdef  ctPortWINCE_SRVR				/* Windows CE Server uses 2000 */
#define ctSQL_MAX_FLDLEN 2000		/* maximum field length (Dh default to 2000) */
#else
#define ctSQL_MAX_FLDLEN_DEF_DEFINE
#define ctSQL_MAX_FLDLEN 8192
#endif
#endif

#ifndef ctSQL_MAX_DEFLEN		/* Could be overriddedn in ctsqlovr.h */
#if (ctSQL_MAX_FLDLEN < 8192)
#define ctSQL_MAX_DEFLEN ctSQL_MAX_FLDLEN
#else
#define ctSQL_MAX_DEFLEN 8192
#endif
#endif

#ifndef ctSQL_MAX_PATHLEN		/* Could be overriddedn in ctsqlovr.h */
#ifdef UNICODE				/* Windows CE Server uses 2000 */
#define ctSQL_MAX_PATHLEN 512		/* Be sure these values are in sync with MAX_NAME in ctopt2.h */
#else
#define ctSQL_MAX_PATHLEN 255
#endif
#endif

#define ctSQL_BUILTIN_PROC 		/* enable c-tree SQL faircom built-in stored procedure*/

#define ctSQL_DIRECTDB_CREATION		/* create database using ctdb without the template*/

/* #define ctSQL_DIRECTDB_DELETION */	/* delete existing database using ctdb without the template*/

#ifndef ctPortWINCE_SRVR

#define ctSQL_VERIFYDB			/* enable automatic database version verification and update */

#endif

#define ctSQL_STMT_TIMES		/* Log SQL STATEMENT execution time */
#ifndef ctPortRS6000
#define ctSQL_STMT_HRTIMES		/* Log SQL STATEMENT execution time with high resolution time*/
#endif

#define ctSQL_DHERRORS			/* use hard-coded DHERRORS */
#define ctSQL_NEWPADDING		/* new PADDING LOGIC, trim&pad only when necessary, pad to space by default */
#define ctSQL_TIMEOUT			/* SQL query timeout */
/* #define ctSQL_TIMEOUT_FETCH	*/	/* SQL query timeout summing fetch operations default:off*/
#define ctSQL_SPTDBG                    /* Stored procedure debug enhancement */
#ifndef UNICODE				/* because of compile issue in ctsqlclb.cxx for getenv() */
#define ctJQL_LOOK_INTO_ENV		/* c-tree Server looks for JAVA related variables in the env when not defined in ctsrvr.cfg */
#endif
/*#define ctSQL_OLDLOGGING*/           	/* enable old logging style in Dh code. When commented out dh log everything but panic into sql_server.log */
#define ctSQL_MINMAX_NOTNULL		/* enable MIN/MAX operators on index with NULL checking (NULL values skipped) */
#define ctSQL_DYN_LOCK_BLK		/* enable stored procedure to switch blocking locks on/off */
#define ctSQL_DBHANDLING_PROCS		/* enable stored procs to handle databases */
#define ctSQL_IGNORE_DIR_FAILURE	/* ignore directory creation failures during DB creation */
#define ctSQL_NOSSM_CACHE_ERR		/* avoid statement caching on c-tree / ctdb errors */

#define ctSQL_UNICODE			/* Add support for Unicode field types NCHAR and NVARCHAR */
/*#define ctFeatSQL_AUTO_READ_LOCK*/	/* enable acquiring of low level automatic read locks for read operations that otherwise would not acquire a record lock. */
#define ctSQL_MINIMUM_CARD		/* cardinality function for optimizer returns at least ctsqlmincard rows (this helps the optimizer with empty tables */
#define ctSQL_SMART_ISAMKEYBUF		/* try to disable isamkey buff if the table is used only for reading */
#define	ctSQL_CTDBRENAMETABLE		/* rename table also update ctdb dictionary and physical file name */
#define ctSQL_TRANCTRL			/* enable possibility to create DB with a defined transaction system NONE/PREIMG/TRNLOG(def.)*/
#define ctSQL_CTOPTION			/* enable ctoption caluse in SELECT STATEMENTS */
#define ctSQL_BIGINT_FIX		/* enable fix for BIGINT byte ordering on HIGH_LOW machines */
#define ctSQL_PRESERVE_CURSOR		/* enable preserver cursor feature in the stubs */
#define ctSQL_TPLSCANFETCH_NOFIELD 	/* tpl_scan_fetch does not return ETPL_TUPLE_NOT_FOUND immediatly if the field list is NULL */
#define ctSQL_NO_TRAN_SNAPSHOT		/* avoid Dh code to handle transaction snapshot that in MM and our STUB is useless */
#define ctSQL_HANDLE_TRANABORT  	/* code modifications to handle transaction aborted internally by c-tree */
/*#define ctSQL_DDMPROTECT*/ 		/* avoid transaction abort during DDM operation Jeff & Paolo decided to remove this code because it does not protect in case the transaction is already gone*/
#define  ctSQL_IN_SEL_EURISTIC 5 	/* activate heuristic on the selectivity for IN operator and set the number of value to use from the IN set*/
#define ctSQL_CONVERTFN_MSSQL 		/* make convert() scalar function compatible with MS-SQL syntax */
/*#define ctSQL_NOROWID */  		/* create tables by default without rowid field */
#define ctSQL_NORECBYT 			/* create tables by default without recbyt index */
#define ctSQL_POOL_CLEANUP 		/* implement pooled close stub cleanup strategy  */
#define ctSQL_POOL_CLEANUP_RPC 		/*implement pooled close RPC changes */
#define ctFeatDISABLE_DH_POOL 		/* disable server side connection pooling */
#define ctSQL_DYN_JENV 			/* AttachJVM only when needed */
#define ctSQL_SMART_RDS_ARRAY 		/* rds_env_array is indexed directly by sOWNER */
#define ctSQL_JAVA_CACHE_ENH		/* Improvements to Java bytecode cache */

#define ctSQL_AUTO_ROLLBACK 		/* automatically rollback current transaction */

#define ctSQL_NOLOCKDEMOTION  		/* avoid implicit lock demotion when requesting read lock on a write locked record*/
#define ctSQL_LOCKFREECTRL  		/* do not free lock acquired before last savepoint */
/*#define MM_DBLKS_CHECK*/ 		/* diagnostics for double free in mm_array and mm_cache */
#define ctSQL_MSH  			/* charptr and binary marshalling an unmarshalling on bigendian changes to avoid 10000 bytes limitation on these platforms */
#define ctSQL_LVB_EXT 			/* new RPC-marshaling logic for LVB field to allow chuncks greater than 8192 bytes */
#define ctSQL_SYNTAX			/* enable Faircom Syntax enhacements */
#ifndef ctPortIMAGENOW
#define ctSQL_WHERE_SBQRY_CMP_SRCHXPR	/* enable support for subquery on left side of comparison operation in WHERE clause */
#endif
#ifdef DH_OS_UNIX_QNXRTP
#define ctSQL_NO_DOUBLES_IN_BIGT        /* avoid temporary storage in double type in big_t (long long) calculations.  This is disabled in public/generic/tpconv.hxx if DH_LONGLONG_SUPPORT is off */
#endif
#ifdef ctPortSIEMENS
#define ctSQL_SELIDX_DIAG
#endif
#define ctSQL_WHERE_SBQRY_BETWEEN	/* support WHERE subquery BETWEEN scalar_exp1 AND scalar_exp2 */
/*#define ctSQL_BATCHREAD_BUF_SIZ 128000*/ /* support for batch retrival in a buffer of X bytes */
#define ctSQL_USE_CHARUPPER   		/* support for CHARUPPER/CHARLOWER functions on windows */
#define ctSQL_PHYSCAN	        	/* enforce a physical data file scan during tbl_scan (if not recbyt or rowid index)*/
#define ctSQL_SETTRNMOD			/* enable fc_set_file_tran_state stored procedure for modifying a single files transaction mode */
#define ctSQL_ESTKEY_CACHE		/* selectivity cache */

#define FAIRCOM_MOD_DFLTALC		/* allocate buffer for default field value using length of default value string */
#define FAIRCOM_MOD_POLL		/* unix-like systems use poll() rather than select() */
#ifdef ctSQLSRVR 			/* server side only */
#define FAIRCOM_MOD_ENVMTX		/* use a separate mutex or reader/writer lock for each SQL environment cache */
#endif

#if defined(ctPortDENTRIX) || ctVER_GE(9,6)
#define FAIRCOM_MOD_LOGONSEC 		/* secure logon */
#endif

#if defined(FAIRCOM_MOD_LOGONSEC) && ctVER_GE(10,0)
#define FAIRCOM_MOD_PWDLEN 		/* password security enhancements */
#endif

#if defined(FAIRCOM_MOD_PWDLEN) && (ctVER3_GE(10,2,0) || (ctVER3_GE(10,1,0) && defined(ctPortCHARGER1)))
#if ((defined(DH_OS_WINNT) || defined(DH_OS_UNIX_LINUX)) && !defined(DH_OS_UNIX_QNXRTP))
#define FAIRCOM_MOD_KEY_EXCHANGE 	/* secure key exchange support */
#define FAIRCOM_MOD_KEY_EXCHANGE_FC_RNG /* use FairCom random number generator for secure key exchange */
#endif
#endif

#if ((ctVER_MAJOR > 9) || (ctVER_MAJOR == 9 && ctVER_MINOR>2))  /* Only support from v9.3 forward */
#define ctSQL_AMBIDX 		/* support for multiple indices with the same name belonging to different tables */
#endif

#define ctSQL_TEMPOPEN		/* support for opening a file at OS level that will be automatically deleted when closing it */
#define ctSQL_VARCHAR_OPT	/* changes the ctree type of VARCHAR fields from CT_STRING to CT_2STRING for improved performance */
#define ctSQL_CTDB_DBCOPY	/* ctdbDupDatabase only updates ctree file id for files listed in the dictionary, and uses PUTHDR, rather than directly modifying the file.  IFIL Resources are updated to new path. */
#define ctSQL_OPT_REVOKE	/* modifies the DDM statements used by the REVOKE command, and modifies systabauth and syscolauth indexes for improved performance */
#define ctSQL_LOCKTIMEOUT	/* enable timeout on blocking locks */
#define ctSQL_LOGICALID		/* enable syscolumns.logicalid column */
#define ctSQL_TRACK_ERROR	/* enable error tracking code */
#define ctSQL_NO_OVERFLOW_IN	/* enable logic to not return overflow error for IN values */
#define ctSQL_EASY_COSTS	/* when #define ctSQL_NO_COSTS is active (default) make the stub return hardcoded values for cost (the same one defined by Dharma) */
#define ctSQL_USE_OFFSET	/* use record offset as TID (tuple id) unless the query contains explicit reference to rowid */
#define ctSQL_MM_CTOR_CHG	/* use changes in the construction of MM tables so that constractors cannot fail */ 
#define ctSQL_PANIC_ONCBKLOAD 	/* panic if sqlcbk DLL load fails */
#define ctSQL_COMM_DBG 		/* diagnostig communication log */
#define ctSQL_CS_CLEANUP 	/* clean up character set managememt */
#define ctSQL_PAD_BINARY 	/* FIXED BINARY field padded with zeroes as per documentation */
/*#define ctSQL_SET_SUBCLASS*/ /* set the subclass value in sqlca. DO NOT TURN ON!!! this is used to control code we disabled that causes memory overwrite */
/*#define ctSQL_INTERNAL_LOCKTBL*/ /* activate internal lock table calls. DO NOT TURN ON!!! this is used to control code that perform lock table internally in the code, this lock table were never effective before lock table implementaion and seems to create problems*/
#define ctSQL_NEG_VIEW_ID	/* use negative numbers for view/aliases ids in systables */
#define ctSQL_BIN_STR	/* string conversion to binary are done by memcpy, not interpreted as hex values */
#define ctSQL_LONGHDL_NOT_PRESERVED /* long handle temp table used during updates not preserved at transaction end (unless preserve cursors is on)*/
/* #define ctSQL_NAMED_MUTEX */  /* allow locating a mutex by "name", not really used and buggy for UNICODE. #define added to remove existing code */
#define ctSQL_IDENTITY_INSERT  /* SET IDENTITY_INSERT support*/

#define ctSQL_FULLTEXT     /* Full Text Index support */
#define ctSQL_UNLOCK_NOFIND  /* optimized logic in un/demote lock logic to avoid record reread when possible */
#define ctSQL_IF_EXISTS  /* IF [NOT] EXISTS suppoet for create and drop statements*/
#define ctSQL_IDLE_KILL /* SESSION_TIMEOUT ctsrvr.cfg keyword affect also SQL connections */
#define ctSQL_AUTO_INCREMENT  /* auto_increment support (similar to identity but with automatic detection of specified values) */
#define ctSQL_EMPTY_INSERT   /* allow "insert into xyz value ()" syntax*/
#define ctSQL_GENERIC_BADREC /* ctoption(badrec) applied also outside RTG for stub conversion errors*/
#define ctSQL_LOGON_FLG  /* cttflgLogon handling in rds_main */
#define ctSQL_INTs_DIV_IS_INT /* division between integer types result in integer type */
#define ctSQL_LOCKTABLE_ON_GETNEXTID /* apply exclusive table lock when executing creation of items requiring the "next is": views, stored procs, UDF, triggers, exec plan */

#ifdef FAIRCOM_CODE
#define ctSQL_AUTOIMPORT /* autoimport logic on missing table*/ 
#ifdef ctPortWIN32
#if _MSC_VER <= 1400	 /* Visual Studio 2005 */
#undef  ctSQL_AUTOIMPORT /* autoimport logic on missing table*/ /* ctSQL_AUTOIMPORT uses ctRWLOCK only supported in newer MS Compilers */
#endif
#endif
#endif

#define ctSQL_TRACK_ORIGIN /* track table origin with table id */
#define ctSQL_TRIGGER_CONTROL /* allow disabling triggers */
#define ctSQL_FLD_HDL_CHECK /* checksum on LONG field handle */
/*#define ctSQL_JVM_USER_DIR_LOCALDIR */  /* on windows only set the JVM user.dir to server's LOCAL_DIR (off by default) */


#if ctVER3_GE(11,7,1)
#ifdef ctSQL_RSS_FPUTFGET
#define ctSQL_DDL_IICT   /* turn on support for IICT when FPUTFGET library is in use*/
/*#define ctFeatIICT_FQLDEBUG*/ /* IICT usage debug code - TURN ON ONLY FOR INTERNAL DEBUGGING - ABSOLUTELY NOT IN ANY KIND OF PRODUCTION */
#endif
#define ctSQL_EXEC_COMPLETES /* complete tables pending constraints at exec time not at prepare */
#endif

#if ctVER3_GE(11,9,5) || defined(ctPortDENTRIX)
#define ctSQL_DAPRECISION 	/* precision is 32bit also in DA and in network packet*/
#define ctSQL_LARGE_FLDLEN 	/* support for field length larger than 32K */
#define ctSQL_NO_MAXIDXENTRIES /* removed SQL_MAXIDXENTRIES limit of the maximum total index component per table */
#endif

#ifdef STREE_TRUNK
#define DHARMA_FIX /* fix from Dharma that needs mileage before being turned on */
#endif

#if ctVER3_GE(11,9,5)
#define ctSQL_MULTIDB /* Dharma 15: support for queries across multiple db (which requires two phase commit)*/
#define ctSQL_COMPACT_TRUNCATE /* use c-tree's ISAM-level file truncate function for SQL truncate */
#define ctSQL_MONEY_SCALE_2_4 /* support scale 2 and 4 for money type */
#endif

#if (defined ctSQL_IDENTITY_INSERT || defined ctSQL_TRIGGER_CONTROL)
#define ctSQL_SET_ITEM_CMD /* SET xyz [ON|OFF] syntax support */
#endif

#if defined ctSQL_MAX_FLDLEN_DEF_DEFINE && defined ctSQL_LARGE_FLDLEN
#ifndef ctSQL_DAPRECISION
#error ctSQL_LARGE_FLDLEN requires ctSQL_DAPRECISION
#endif
#undef ctSQL_MAX_FLDLEN
/* cannot be larger than 16,777,215 (2^24-1) otherwise we need to review how we TPE_PACK_PREC_SCALE */
/* cannot be larger then 65535 -2 because in the DODA "UCOUNT	flen;" */
/* in case of UNICODE cannot be larger than 32767 - 2*/
#ifdef UNICODE
#define ctSQL_MAX_FLDLEN 32750 /* maximum field length (Dh default to 2000) */
#else
#define ctSQL_MAX_FLDLEN 65500 /* maximum field length (Dh default to 2000) */
#endif
#endif

/*^***********************************/
#ifdef ctPortATTACH2
#ifndef ctBEHAV_STRICTOEM_LOGONu_CS_VERSION_CHECK
#define ctBEHAV_STRICTOEM_LOGONu_CS_VERSION_CHECK 	/* strict Product Version Number Check */
#endif
#endif /* ctPortATTACH2 */
/*~***********************************/

#ifdef UNICODE
#ifdef ctSQLSRVR
#define ctSQL_MBS_SUPPORT /* generic multi byte support class */
#define ctSQL_UTF8_SUPPORT
#endif
/*#define ctSQL_DB_COLLATOR*/ 	/* store ICU collater in system table, make it db based, store in indices XTDSEGs */
#define ctSQL_LATIN1_SUPPORT /* enable LATIN1 aka ISO-8859-1 support */
#ifdef ctPortABACUS
#define ctSQL_UTF8_SUPPORT_DEFAULT /* UTF-8 is the default charset */
#else
#define ctSQL_LATIN1_SUPPORT_DEFAULT /* latin1 Aka ISO-8859-1 is the default codepage */
#endif
#endif

#if ((ctVER_MAJOR > 9) || (ctVER_MAJOR == 9 && ctVER_MINOR>5))
/*#define ctSQL_PARTSRCH */	/* extended partition search strategy to allow returning keys in partition (not fully sorted) order */
#define ctSQL_INDEX_ONLY_SCAN	/* index only scan implementation */
#endif

#define ctSQL_CHECK_TO_DATA_ERR	/* in record_read_buffer checks for xxx_to_data return code for error */
/* #define ctSQL_DYN_RSSID_LATTEMM */   /* make RSS ID and multienv handling dynamic for LATTE and MM cohexist, not supported anymore */

#ifdef FAIRCOM_CODE
#if ctVER_GE(10,1)
#define ctSQL_DYN_STMT		/* allocate statement buffers dynamically */
#endif
#define ctSQL_CASE_TYPES  	/* new CASE return type handling */

#if ctVER_GE(10,4)
#define ctSQL_SP_RPC		/*implement RPC calls to dump and restore stored proc definition*/
#define ctSQL_STP_LANG		/* support for STP,UDF,TRIG in other languages than JAVA */
#ifdef DH_OS_WINNT
#if _MSC_VER > 1400		/* Must be after VS2005 */
#define ctSQL_STP_CLIRTM	/* support for STP,UDF,TRIG in .net (C#, VB, etc.) */
#endif
#endif

/*#define ctSQL_LV_SEC*/ 	/* additional checks on LV handling to avoid possibility to bypass security by hacking the field handle */
#endif

#if ctVER_GE(10,5)
#define ctSQL_FAIRCOM_FCS  /* user and group information in FAIRCOM.FCS, not in system tables */
#endif

#if ctVER_GE(11,1)
#define ctSQL_LATTE_HASHTBL  /* use HASH_TBLT for TPLAT_TEMP_HASH tables */
/*#define ctSQL_LATTE_HASHIDX */ /* use PHASH_IDXT for TPLAT_TEMP_DIDX_EQ dynamic index -- not working yet -- */
#endif

#define ctSQL_SCROLLABLE_FETCH  /* prepare resultset at execution time not at first fetch so that it is possible to know how many recrods contains the resultset */
#endif /*FAIRCOM_CODE*/


#ifdef ctSQL_LATTE
/* #define ctSQL_LATTE_STUB_TEST */  /* enable latte stub tests */
#endif
#if ctVER3_GE(10,2,0)
#define ctSQL_CTTBL  		/* cttbl syntax support */
#endif

#if ctVER_GE(10,2)
#define ctSQL_CRYSYSTBL		/* encrypt system table (unless ctsrvr.cfg specifies SQL_OPTION NO_CRYPT_SYSTBL) */ 
#endif

#ifdef ctSQLSRVR
#ifdef ctFeatATOMICop
#if !defined(_MSC_VER) ||  _MSC_VER > 1400    
#define ctSQL_SINGLE_LOG	/* all connections share a single descriptor to sql_server.log */
#endif
#endif
#endif

#ifdef ctSQL_SINGLE_LOG
#ifndef NO_ctSQL_SERVER_LOG_SIZE
#define ctSQL_SERVER_LOG_SIZE /* SQL_SERVER_LOG_SIZE configuration option to limit size of sql_server.log */
#endif
#endif

#if defined(ctSQLSRVR) 
#define ctSQL_NOSIGNALS 	/* disables all signal related system calls from SQL */
#endif

/* the following #defines control dharma's capabilities that we disabled or changed the default state (enab vs. disab) ...*/
/*BEGIN*/
/*features enabled */

/*features disabled*/

/* default changed*/
#define ctSQL_DISAB_DO_AHEAD	/* do_ahead disable by deafult, can be turned on by SETENV DH_DO_AHEAD=Y */

/*END*/


#if defined(DH_OS_WINNT) || defined(CTSQL_UNIX_SHMEM)
#ifndef _WIN32_WCE
#ifndef ctPortNLM
#ifndef DH_OS_UNIX_LINUX_KERNEL_V2_4
#define ctSQL_SHMEM		/* SQL shared memory communication protocol support */
#endif
#endif
#endif
#endif

#ifndef ctSQLSRVR /*client side only defines */
#ifdef DH_OS_WINNT
#define FAIRCOM_NONBLK_SOCKIO
#endif
#endif

#ifdef ctSQLSRVR /* server side only defines */
#define ctSQLUNIQUE  			/* unique SQL/JQL server */
#ifdef DH_OS_WINNT
#ifndef _WIN32_WCE
#ifndef ctPortNLM
#define ctSQL_CACHESTATS		/* SQL statement cache statics collection for ctSNAPSHOT */
#endif
#endif
#endif

#ifndef ctSQL_LATTE_STUB_TEST 
#define ctSQL_CTREE_MEMALLOC 		/* allocate memory through c-tree Plus sub-allocator */
#ifdef _WIN32_WCE
#define ctSQL_CTREE_MEMALLOC_WCE	/* special implementation of this memory system for Windows CE Server */
#endif
#endif

#define ctSQL_CHECKHEAP /*enables memory buffer overflow and double free checking*/
#endif

#ifdef ctSQL_USE_PUSHDOWN		/* Required Updated Expression Analyzer */
#define ctFeatCNDX_V9			/* V9 Generation Expression Analyzer support(Ricardo's improvements for SQL PushDowns Jan-2004) */
#endif



/* sanity checks */
#ifndef ctSQL_DB_CASE
#ifdef ctSQL_PERSIST_DB_CASE
#undef ctSQL_PERSIST_DB_CASE
#endif
#endif

#ifndef ct_V90_GENERATION	
#define ct_V90_GENERATION 	/* Ray activated as of v8.27.0 Build(050831) */
#endif

#ifdef ct_V90_GENERATION
/* 
 * For the JDBC driver the default isolation level is defined in
 * src/snw/snj/DharmaIsolationLvl.java file
*/ 
#define ctSQL_ISOLATION_V8C 		/* New isolation level changes by Paolo in 3/2004 */
#define ctSQL_ISOLATION_V8C_DICT 	/* do not switch isolation level for dictionaries */
#define ctSQL_SUPPORT_ISOLVL2 		/* allow isolation level 1 & 2 (otherwise only 1) */
#ifndef ctSSrel2
/* #define ctSSrel2 */			/* allow isolation level 3 */
#endif
#endif /* ct_V90_GENERATION */

#ifdef ctSQL_FASTDBCREATION
#define ctSQL_TEMPLATE_DB "__Master"
#endif

/* disable features to configure dharma's original system table creation using SQL */
#ifdef DHARMA_SQL_DB_CREATION
#undef ctSQL_AMBIDX
#undef ctSQL_VERIFYDB
#undef ctSQL_DIRECTDB_CREATION
#undef ctSQL_VALIDATE_USER
#undef ctSQL_FASTDBCREATION
#undef ctSQL_CTDB_TEMPLATE
#undef ctSQL_PREPEND_OWNER
#undef ctSQL_LATTE
#undef ctSQL_STP_LANG
#undef ctSQL_STP_CLIRTM
#undef ctSQL_SP_RPC
#endif

/* Shared object visibility */

#if defined DH_OS_UNIX_LINUX && ! defined DH_OS_UNIX_FREEBSD8
#define HIDDEN __attribute__((visibility("hidden")))
#define GLOBAL_OP __attribute__((always_inline))
#elif defined(DH_OS_UNIX_SOLARIS)
#define HIDDEN __hidden
#define GLOBAL_OP
#else
#define HIDDEN
#define GLOBAL_OP
#endif

/*
** #define ctSQL_PROFILE_STUB causes stub functions to call profiling functions
** on entry to and on exit from the stub functions. The stub_enter() and
** stub_exit() functions collect call count and timing statistics. When a SQL
** client disconnects the server writes the statistics to the file SQLSTUB.FCS.
*/
/* #define ctSQL_PROFILE_STUB */



/*^*******************/
/*
** ctFeatSQLIPv6 allows the c-tree Server to track IPv6 addresses in addition to IPv4.
**
** DEFAULT:  ctFeatSQLIPv6 is activated for windows and linux.
** ctFeatSQLIPv6 requires ctFeatIPv6, but that is not defined in all SQL modules.
** BE SURE TO MAINTAIN BOTH ctopt1.h and ctsql_lib.h 
*/
/*~*******************/
#if ( defined(DH_OS_UNIX_LINUX_KERNEL_V2_4) || defined(DH_OS_UNIX_QNXRTP) )
#define NO_ctFeatIPv6
#endif

#if defined(ctSQLSRVR) && !defined(ctFeatIPv6)
/* c-treeSQL Server: c-tree headers indicate that ISAM IPv6 support is not
** enabled, so don't enable SQL IPv6 support. */
#define NO_ctFeatIPv6
#endif

#ifndef NO_ctFeatIPv6
#ifndef NO_ctFeatSQLIPv6
#ifdef DH_OS_WINNT
#if _MSC_VER  >= 1500
#ifndef ctFeatSQLIPv6
#define ctFeatSQLIPv6		/* Handle IPv6 for current windows compilers */
#endif
#endif
#endif
#ifdef  DH_OS_UNIX_LINUX
#ifndef DH_OS_UNIX_FREEBSD8
#ifndef ctFeatSQLIPv6
#define ctFeatSQLIPv6		/* Handle IPv6 for linux */		
#endif
#endif
#endif
#endif /* ~NO_ctFeatSQLIPv6 */
#endif /* ~NO_ctFeatIPv6 */

/*^*******************/
/*
** ctFeatTRACK_CLIENT_ADDR causes the c-tree Server to track the IP address
** from which clients connect.
**
** DEFAULT:  ctFeatTRACK_CLIENT_ADDR is activated for c-treeACE SQL Server compiles
** for all platforms except Windows CE.
*/
/*~*******************/
#ifdef ctSQLSRVR
#ifndef NO_ctFeatTRACK_CLIENT_ADDR
#ifndef ctPortWINCE_SRVR
#define ctFeatTRACK_CLIENT_ADDR
#endif
#endif
#endif

#include "ctsqlray.h"						/* Special SQL helper functions and settings */


#ifdef REMOVED_DEFINES_AND_CODE
/* these defines were removed and the code they controlled activated as if the defined was ON*/
#define ctSQL_ENGINE_V8C
#define ctSQL_ENGINE_V90
#define ctSQL_USE_INDEX_RANGE 
#define ctSQL_PARTSEG			/* allow handling of partial field segments */
#define ctSQL_SYSSUPERFILE		/* superfile SQL Catalog */
#define CTDBSDK    /* initialy used to distingus ctdb base code in the stub from original dharma stub implementation over c-tree?*/
#define RAB_V90_ISSUE  /* issues that RAB fixed in V9 during dhrama code merge*/
#define RAB_030303_ACTIVE
#define ctSTUBIXSCAN_OPTIMIZE_UPPER_RANGE
#define ctSQL_LOADCALLBACK_ONCE 	/* load the CTSQL SDK shared library only one at server startup */
/* these defined were removed and the code they controlled removed as well since the define was OFF */
#define ctSQL_USE_TABLENAMES
#define PAOLO_REMOVED... /*with dates pre 2011*/
#define RAB_SUPER_FILES_WILL_NOT_WORK
#define RICARDO_NO_PATH_IN_INDEX_NAME
#define OLD_V73
#define ctSQL_DEF_SEL_ALL_OP
/* removed define controlling dead code (not used anywere)*/
#define STUB_NO_TYPEID

#endif

#endif /* ~__CTSQL_LIB_H__ */

/* end of ctsql_lib.h */
