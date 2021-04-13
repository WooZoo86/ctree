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
 *      Copyright (C) Dharma Systems Inc.        1988-2002. 
 *      Copyright (C) Dharma Systems (P) Ltd.    1988-2002. 
 * 
 *      This Module contains Proprietary Information of 
 *      Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 *      and should be treated as Confidential. 
 */

#ifndef _CTDBSDK_H_
#define _CTDBSDK_H_

/*^****************************************************************************/
#ifdef _CTREEDB_C_ 	/* Special concideration for CTDB source modules */
#ifndef ctSRVR
#ifndef ctOPT2H		/* Special ctoptn.h & ctopt2.h include controls */
#define ctOPT2H 	/* Prevent ctopt2.h header in initial ctoptn.h */
#include "ctoptn.h"	/* Compiler Options Header */
#undef	ctOPT2H    	/* Allow ctopt2.h for traditional ctoptn.h inclusion */
#endif
#ifdef ctMTCLIENT
#define ctCLIENTcore
#endif
#endif
#endif /* _CTREEDB_C_ */
/*~****************************************************************************/


/*^****************************************************************************\
*
*   Header Files
*
\******************************************************************************/
#ifndef CTDB_NOCTREEP
#include "ctreep.h"	/* ctree Plus Primary Header Files */
#endif /* CTDB_NOCTREEP */

#define CT_PROD_NAME "c-treeACE"

/*^****************************************************************************\
*
*	UNICODE check
*
\******************************************************************************/
#ifdef ctUNICODE
#define ctdbUNICODE
#endif

#ifdef ctdbUNICODE
#include "ctdbutf8.h"
#endif
/*^****************************************************************************\
*
*	CTDB Change log
*
\******************************************************************************/
#define CTDB_CNDX_IDX /* conditional index support in CTDB */
#define CTDB_FASTVLEN		/* Use fast variable record length functions	*/
#define CTDB_FILTER_020617	/* added code to support record filters		*/
#define CTDB_PAD_RESOURCE	/* target key formation resource		*/
#define CTDB_SUPERFILE		/* open superfile member			*/
#ifndef NO_CTDB_AUTO_SQLIMPORT
#define CTDB_AUTO_SQLIMPORT 	/* table added automatically to SQL systables	*/
#endif
#define CTDB_MIRROR  		/* mirroring support */
#define CTDB_UNIFRMAT		/* UNIFORMAT support */
#define CTDB_PATHPREFIX		/* enable path prefix feature */
#define CTDB_CALLBACK		/* enable CTDB callback feature */
#define ctdbRECORD_FILTER	/* enable support for context sensitive filters */
#define CTDB_SYSTEM_FILTER	/* implement system wide data records filters */
#define CTDB_DEFAULT_VALUE	/* implement field default value feature */
#define CTDB_MAX_FIXLEN_CHECK   /* check if the calculated fixed record size exceed 65535 if so make the table variable length*/
#define CTDB_DICTTRANCRTL	/* allow controlling transaction mode of dictionary files */
#define CTDB_FRMKEY_OPTIMIZE    /* avoid useless record (and possibly key) allocation before calling frmkey */
#define CTDB_DICTMERGE_API	/*enable dictionary merge API */
#define CTDB_FIX_ctSUSPEND      /* make BEGIN to always call LKISAM(ctSUSPEND) */
#define	CTDB_SUPERFILE_AUTO /* enables support for creating superfile host automatically */
#define CTDB_CHECK_SEGLEN /*do not assume that the segment length for *SCHSEG and *VARSEG matches the field length, but verify it */
#define CTDB_XSTRING_LEN  /*calculate the segment length for CT_?STRING and CT_F?STRING by removing the beginning extra bytes */
/*#define CTDB_OPEN_WITH_IFIL*/ /* allow using provided IFIL instead of ...withResources... approach */
#define CTDB_SYNC_DICT_UID	/*verify UID in the header of the dictionary and update it if necessary so that new entry get valid values */
#define CTDB_BLKIREC		/* blocking read support */
/*#define CTDB_VTABLES 	 */ /* support VTables */
/*#define CTDB_VTABLES_MRT */ /* support for MRTTable (requires CTDB_VTABLES)*/
#define CTDB_AUTO_PARTITION	/* Partitioned file support with hardcoded rule */
#define CTDB_CLOSE_NET_ERR 	/* trap ARQS_ERR and  ARSP_ERR on close,logout,disconnect and do not consider it as an error */

#define CTDB_TEMP_IDX	/* Added temporary index support */
#define CTDB_REUSE_RECORD_CRI	/* Reuse record criteria feature */
#ifndef ctPortWINKE_CLIENT
#ifdef CTDB_CNDX_IDX /* the following is dependent on CTDB_CNDX_IDX */
#ifdef ctFeatCNDX_V9
#define CTDB_EXPR_EVAL	/* Expression evaluation feature */
#endif
#endif
#endif
#define CTDB_DFLT_FIELD_VALUE /* Default field value persistent feature */
#ifndef NO_CTDB_DATAONLY_ISAM
#define CTDB_DATAONLY_ISAM /* use ISAM function in order to perform a CTOPEN_DATAONLY */
#endif
#ifdef ctFeatDAR
#define CTDB_IDENTITY /* identity field support */
#endif
#ifndef ctPortWINKE
#define CTDB_CALLBACK_LOAD /* support callback DLL load/unload*/
#endif
#ifdef ctPortMSIGA
#define CTDB_IMPERSONATE /* support impersonation feature */
#endif
#define CTDB_PHYNAME /* add support for logical and physical table name */
#define CTDB_RESULT_SET /* add support for result set feature in CTDB */
#if ctVER3_GE(10,2,0)
#define CTDB_VARSTRTERM  /* use schema information for variable length string terminator */
#endif
#ifdef ctPortSTR
#ifndef CTDB_VARSTRTERM
#define CTDB_VARSTRTERM  /* use schema information for variable length string terminator */
#endif
#endif
#define CTDB_FILEXT /* use new logic to handle file extension */
/*#define CTDB_VFIELDS*/ /* support Virtual Fields */
#ifndef MULTITRD /*ctdbMULTITRD is defined later so cannot be used here */
#define CTDB_OPT_DODA_IFIL /*optimize client/server DODA and IFIL calls by using a predefined temp buffer */
#endif
/*#define CTDB_ROUTER*/ /*table routing support */
#define CTDB_DEFER_KSEG  /*defer KSEG information retrival to the time it is needed */
#define CTDB_DEFER_CNDX_IDX /*defer Conditional index information retrival to the time it is needed */
#define CTDB_DEFER_TMPIDX /* defer temporary index identification to the the it is needed */
#define CTDB_BATCH_65536  /* handle more than 65536 total batches per session*/
#define CTDB_HASH_FILENAMES /* file name hashing to improve ctdbAddField performance */
#define CTDB_CTTIME_HMST /* CTTIME_HMST is available */
#define CTDB_CTTIME_HHMST /* CTTIME_HHMST is available */
#if ctVER3_GE(11,2,2)
#ifndef NO_CTDB_NEW_SQLIMP
#define CTDB_NEW_SQLIMP
#endif
#endif
#define CTDB_UTC_TIMESTAMP 		/* ctdbCurrentDateTimeUTC && ctdbCurrentTimestamp available */
#define CTDB_U16_VALIDATE 		/* UTF16 string validation */
#define CTDB_BACKGROUND_INDEX_LOAD 	/* support for initial index loading in background */
#define CTDB_INTERNAL_pINDEX  		/* store pCTDBINDEX information for internal indices */
#define CTDB_SHARED_DICTADD 		/* add to dictionay opening the table in shared mode (if possible), affect also SQLIMP*/
#ifdef  ctJSONCLIB			/* requires JSON support */
#define CTDB_TBLATTR 			/* table extra attributes support, includes xtd field attributes */
#endif
#define CTDB_CHECK_MINSTRLEN	/* check if the length specified for fixed string types is large enought to contain the minimum required, ie. string len or 1 byte*/
#define CTDB_PRECISION_CHECK	/* check if the CT_CURRENCY (for now) value fits into the defined precision */

/*^****************************************************************************\
*
*	CTDB Feature customization based on customers/Platforms/other Features
*
\******************************************************************************/
#ifdef ctThrds
#define CTDB_SMART_THRDS    /* during allocsession/freesession determine if a thrdattach/detach is necessary */
#endif

#ifdef MULTITRD
#define CTDB_ITIM_RETRY 	/* Retry for record read errors ITIM_ERR and FFLT_ERR	*/
/* #define CTDB_MINIMUM_RECORD_BUFFER_SIZE 1024 */ /* Minimum size for c-treeDB record buffer */
#endif

#ifndef ctCLIENT
#ifndef ctSQLSRVR
#ifndef ctLOCSIDE
#ifndef ctCLISIDE
#if !(defined(FPUTFGET) && defined(ctSQLMTFPG))
#undef CTDB_AUTO_SQLIMPORT 	/* this is only available on client, except for SQL Server .NET and CSAPI*/
#endif
#endif
#endif
#endif
#endif

#ifdef ctPortWINCE_SRVR
#undef CTDB_AUTO_SQLIMPORT 	/* this is only available on client, except for SQL Server .NET and CSAPI*/
#endif

#if defined(CTDB_AUTO_SQLIMPORT) || defined(ctSQLMTFPG)
#define CTDB_SQL_PATH_FIX /*if the database is SQL and the dictionary dir is SQL_SYS, default path to .. instead of the dicionary dir */
#endif

#ifdef ctPortNLM
#ifdef CTDB_CALLBACK
#undef CTDB_CALLBACK
#endif
#endif /*ctPortNLM*/

#ifdef ctPortOLYMPIA
#ifdef CTDB_CHECK_SEGLEN
#undef CTDB_CHECK_SEGLEN
#endif
#endif /*ctPortOLYMPIA*/

#ifdef ctPortEPSILON
#ifndef CTDB_VARSTRTERM
#define CTDB_VARSTRTERM  /* use schema information for variable length string terminator */
#endif
#endif /*ctPortEPSILON*/

#if ( ctVER_MAJOR>=10 || defined(ctFeatCOBOL) || defined(ctPortATTACH2) || defined(ctPortADVENT) )
#ifndef CTDB_VTABLES
#define CTDB_VTABLES
#endif
#ifndef CTDB_VTABLES_MRT
#define CTDB_VTABLES_MRT
#endif
#endif /* RAB:120705: Activated for all - ctFeatCOBOL and special OEMS */


#if defined ctFeatCOBOL && ctVER_GE(10,1)
#define CTDB_VFIELDS
#endif

#ifdef ctSQLMTFPG
#define CTDB_CALC_EXTR_SQLPATH
#endif

/*^****************************************************************************\
*
*	CTDB DLL export macros
*
\******************************************************************************/
#ifdef CTDB_DLLEXPORT
#ifdef ctPortWIN32
#ifdef ctDLLLIB
#ifdef ctdbDLLEXP
#define ctdbEXPORT	__declspec(dllexport)
#else	/* ctdbDLLEXP */
#define ctdbEXPORT	__declspec(dllimport)
#endif	/* ctdbDLLEXP */
#endif	/* ctDLLLIB */
#endif	/* ctPortWIN32 */
#endif /* CTDB_DLLEXPORT */

#ifndef ctdbEXPORT
#define ctdbEXPORT
#endif
/*^****************************************************************************\
*
*	CTDB calling convention macros
*
\******************************************************************************/
#define ctdbDECL	ctDECL			/* used for exported CTDB API functions	*/
#define ctdbLOCAL					/* used for internal CTDB functions		*/
/*^****************************************************************************\
*
*	CTDB Default defines
*
\******************************************************************************/
#define ctdbDEFAULT_dbengine    FAIRCOMS
#define ctdbDEFAULT_userid	    ""
#define ctdbDEFAULT_userword	""
/* #define CTDBCEPTLAYER */	/* If intercept layer defined */
#ifdef	CTDBCEPTLAYER		/* If intercept layer defined */
#define ctdbSTATIC	/* */
#else
#define ctdbSTATIC	static
#endif
#define ctdbDEFAULT_SQLIMP_LOCK CTLOCK_WRITE_BLOCK
/*^****************************************************************************\
*
*   Protect against C++ compilers
*
\******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*^****************************************************************************\
*
*   CTDB C API version
*
*   Bits  0-15   Build number
*   Bits 16-23   Version number
*   Bits 24-31   Release number
*
\******************************************************************************/
#define CTDB_C_BUILD_NBR        0x00000001
#define CTDB_C_VERSION_NBR      0x00010000
#define CTDB_C_RELEASE_NBR      0x00000000
#define CTDB_C_VERSION          (CTDB_C_RELEASE_NBR | CTDB_C_VERSION_NBR | CTDB_C_BUILD_NBR)
/*^****************************************************************************\
*
*   Misc defines for internal needs
*	NOTE: defined both here and in ctdbport.h ??????? BETTER HERE
\******************************************************************************/
#ifdef MULTITRD
#define ctdbMULTITRD
#endif
#ifdef ctSRVR
/*#define ctdbSETMSGLEN*/ /* Internal Server-side com buffer control */
#endif
/*^****************************************************************************\
*
*   Handle types
*
\******************************************************************************/
#define CTDB_SESSION_HANDLE_ID      0x0db1
#define CTDB_DATABASE_HANDLE_ID     0x0db2
#define CTDB_TABLE_HANDLE_ID        0x0db3
#define CTDB_RECORD_HANDLE_ID       0x0db4
#define CTDB_INDEX_HANDLE_ID        0x0db5
#define CTDB_FIELD_HANDLE_ID        0x0db6
#define CTDB_SEGMENT_HANDLE_ID      0x0db7
#define CTDB_RESOURCE_HANDLE_ID     0x0db8
#define CTDB_RESULTSET_HANDLE_ID    0x0db9
#define CTDB_RESULTSETCRI_HANDLE_ID 0x0dba
#define CTDB_FTI_HANDLE_ID          0x0dbb
#define CTDB_FTIDICT_HANDLE_ID      0x0dbc
/*^****************************************************************************\
*
*   CTDB Session Types
*
\******************************************************************************/
typedef enum
{
	CTSESSION_CTDB	= 0,
	CTSESSION_CTREE = 1,
	CTSESSION_SQL   = 2,
	CTSESSION_SQLINTERNAL = 3, /* for SQL engine internal use only */
	CTSESSION_SERVER = 4, /* for SERVER side internal use only */
	CTSESSION_SRVR_SQLIMP = 5 /* for SERVER side internal use only in SQLIMP logic*/
} CTSESSION_TYPE;
/*^****************************************************************************\
*
*   CTDB Session Parameters
*
\******************************************************************************/
typedef enum
{
	CT_BUFS = 1,
	CT_FILS,
	CT_SECT,
	CT_DBUFS,
	CT_USERPROF
} CTSESSION_PARAM;

/*^****************************************************************************\
*
*   CTDB Session SSL Parameters
*
\******************************************************************************/
typedef enum
{
	CTDB_SSL_CERT = 1,
	CTDB_SSL_DEBUG
} CTSESSIONSSL_PARAM;

#define CTDB_SESSION_PFILNAM        "ctdbdict"
#define CTDB_SESSION_FFILNAM        "ctdbdict"
#define CTDB_MAXID					32
/*^****************************************************************************\
*
*   CTDB C API Find modes
*
\******************************************************************************/
typedef enum
{
	CTFIND_EQ,
	CTFIND_LT,
	CTFIND_LE,
	CTFIND_GT,
	CTFIND_GE
} CTFIND_MODE;
/*^****************************************************************************\
*
*   CTDB C API Locate modes
*
\******************************************************************************/
typedef enum
{
	CTLOC_NONE,
	CTLOC_CASEIN,
	CTLOC_PARTIAL,
	CTLOC_CASEIN_PARTIAL
} CTLOC_MODE;
/*^****************************************************************************\
*
*   CTDB C API Date string format types
*
\******************************************************************************/
typedef enum
{
	CTDATE_DEF,			/* deprecated: do not use       */
	CTDATE_MDCY,		/* Date is mm/dd/ccyy           */
	CTDATE_MDY,			/* Date is mm/dd/yy             */
	CTDATE_DMCY,		/* Date is dd/mm/ccyy           */
	CTDATE_DMY,			/* Date is dd/mm/yy             */
	CTDATE_CYMD,		/* Date is ccyymmdd             */
	CTDATE_YMD			/* Date is yymmdd               */
} CTDATE_TYPE;

#define COBOL_INTOFDATE_BASE 0xFFFFFFFF  /* special CTDATE value to be used as JULIAN DATE for dates based on cobol's integer-of-date values */
/*^****************************************************************************\
*
*   CTDB C API Time string formattypes
*
\******************************************************************************/
typedef enum
{
	CTTIME_DEF,             /* deprecated: do not use       */
	CTTIME_HMSP,            /* Time is h|hh:mm:ss am|pm       */
	CTTIME_HMP,             /* Time is h|hh:mm am|pm          */
	CTTIME_HMS,             /* Time is h|hh:mm:ss (24 hour)   */
	CTTIME_HM,              /* Time is h|hh:mm (24 hour)      */
	CTTIME_MIL,             /* Time is hhmm (military)      */
	CTTIME_HHMSP,           /* Time is hh:mm:ss am|pm       */
	CTTIME_HHMP,            /* Time is hh:mm am|pm          */
	CTTIME_HHMS,            /* Time is hh:mm:ss (24 hour)   */
	CTTIME_HHM,             /* Time is hh:mm (24 hour)      */
	CTTIME_HMST,            /* Time is h|hh:mm:ss.ttt (24 hour)   */
	CTTIME_HHMST            /* Time is hh:mm:ss.ttt (24 hour)   */
} CTTIME_TYPE;

/*^****************************************************************************\
*
*   CTDB C API defaulf field content type
*
\******************************************************************************/
typedef enum
{
    CTDEF_NODFLT = 0,
    CTDEF_LITERAL = 1,
    CTDEF_USER = 2,
    CTDEF_NULL = 3,
    CTDEF_SYSDATE = 4,
    CTDEF_SYSTIME = 5,
    CTDEF_SYSTIMESTAMP = 6,
    CTDEF_UID =7
} CTDEF_TYPE;

/*^****************************************************************************\
*
*   CTDB C API Create table additional modes
*
\******************************************************************************/
typedef enum
{
	CTCREATE_NORMAL		= 0x00000000,
	CTCREATE_PREIMG		= 0x00000001,
	CTCREATE_TRNLOG		= 0x00000002,
	CTCREATE_WRITETHRU	= 0x00000004,
	CTCREATE_CHECKLOCK	= 0x00000008,
	CTCREATE_VRLEN		= 0x00000010,
	CTCREATE_NORECBYT	= 0x00000020,
	CTCREATE_NOROWID	= 0x00000040,
	CTCREATE_CHECKREAD	= 0x00000080,
	CTCREATE_HUGEFILE	= 0x00000100,
	CTCREATE_NODELFLD	= 0x00000200,
	CTCREATE_NONULFLD	= 0x00000400,
	CTCREATE_PARTAUTO	= 0x00000800, /* partitioned table */
	CTCREATE_V8DELFLD	= 0x00001000, /* create the table using sizeof(LONG)(4) bytes delfld size as it was in v9 and previous*/
	CTCREATE_COMPRESS	= 0x00002000, /* create table using data compression */
	CTCREATE_NOFLUSH	= 0x00004000, /* for non TRNLOG files, disbale disk flushing */
	CTCREATE_DYNPARTHOST	= 0x00008000, /* create the table as a dynamic partition host */
	CTCREATE_FLEXREC	= 0x00010000,  /* use flexible record format */
#ifdef ctBlockCompress
	CTCREATE_BLOCKCOMPRESSDAT = 0x00020000, /* create data file with block compression */
	CTCREATE_BLOCKCOMPRESSIDX = 0x00040000, /* create indexes with block compression */
#endif
	CTCREATE_AUTOMKDIR = 0x00080000,  /* create directories if needed */
	CTCREATE_NOCLSADD = 0x00100000  /* create does not close the file, does not update database dictionary */
} CTCREATE_MODE_E;

typedef NINT	CTCREATE_MODE;

#define UNDEF_PRT ((pVOID) 1)  /* generic fake pointer used also to indicate an undef partition rule, NULL indicates a partition rule not set */

/*^****************************************************************************\
*
*   CTDB C API Open table additional modes
*
\******************************************************************************/
typedef enum
{
	CTOPEN_NORMAL		= 0,
	CTOPEN_EXCLUSIVE	= 1,
	CTOPEN_PERMANENT	= 2,
	CTOPEN_CORRUPT		= 4,
	CTOPEN_CHECKLOCK	= 8,
	CTOPEN_CHECKREAD	= 16,
	CTOPEN_READONLY		= 32,
	CTOPEN_DATAONLY		= 64,
	CTOPEN_UNLOCKONCLOSE	= 128,
	CTOPEN_RAW	= 256 + CTOPEN_READONLY
} CTOPEN_MODE_E;

typedef NINT CTOPEN_MODE;
/*^****************************************************************************\
*
*   CTDB Recbyt and rowid index numbers
*
\******************************************************************************/
#define CTDB_RECBYT_IDXNO	10000
#define CTDB_ROWID_IDXNO	10001
#define CTDB_DATA_IDXNO		10002
#define CTDB_PARTITION_IDXNO	10003
/*^****************************************************************************\
*
*   CTDB C API state
*
\******************************************************************************/
typedef enum
{
	CTSTATE_NONE,
	CTSTATE_CREATETABLE,
	CTSTATE_OPENTABLE,
	CTSTATE_ALTERTABLE
} CTSTATE;
/*^****************************************************************************\
*
*   CTDB SDK Index types
*
\******************************************************************************/
typedef enum
{
	/* lower two bytes need to be aligned with c=tree KTYP_* definition in ctopt2.h */
	CTINDEX_FIXED                       = 0x00000000,  /* fixed length key               */
	CTINDEX_LEADING                     = 0x00000004,  /* COL_PREFIX - leading character compression  */
	CTINDEX_PADDING                     = 0x00000008,  /* COL_SUFFIX padding compression            */
	CTINDEX_LEADPAD                     = 0x0000000C,  /* COL_BOTH leading/padding compression    */
	CTINDEX_NOMOD                       = 0x00000080,  /* KTYP_NOISMKEYUPD - unmodifiable key    */
	/*CTINDEX_KMSKprt      = 0x00000060,*/  /* KMSKprt in partition search */
	CTINDEX_DFRIDX                      = 0x00000100,  /* KTYP_DFRIDX  - deferred index maintenance */
	CTINDEX_VARIABLE_LENGTH_COMPRESSION = 0x00000200,  /* KTYP_VLENNOD - index node contains offset list	*/
	CTINDEX_TRNMRKOPT                   = 0x00000400,  /* KTYP_TRNMRKOPT - transaction marks stored with keys	*/
	CTINDEX_RLE_KEY_COMPRESSION         = 0x00000800,  /* KTYP_KEYCOMPSRLE - index uses sRLE key compression	*/
	CTINDEX_CMPOFFSET                   = 0x00001000,  /* KTYP_CMPOFFSET - index uses compressed offsets	*/
	CTINDEX_CMPTRNMRK                   = 0x00002000,  /* KTYP_CMPTRNMRK - index uses compressed transaction marks */

	/*these following modes are not directly set in c-tree's index mode */
	CTINDEX_BCKLOAD                     = 0x00010000,  /* background index load */
	CTINDEX_ERROR                       = 0x7fffffff  /* index type error               */
} CTDBKEY_E;

#define CTINDEX_CTREEMASK 0x0000ffff

/* backward compatibility MACRO for renamed CTDBKEY_E enum entries*/
#define CTINDEX_VLENNOD CTINDEX_VARIABLE_LENGTH_COMPRESSION
#define CTINDEX_KEYCOMPSRLE CTINDEX_RLE_KEY_COMPRESSION

typedef NINT CTDBKEY;
/*^****************************************************************************\
*
*   Index segment modes
*
\******************************************************************************/
enum CTSEG_MODE_E
{
	CTSEG_REGSEG,				/* Absolute byte offset						 */
	CTSEG_INTSEG,				/* Absolute byte offset - unsigned int/long	 */
	CTSEG_UREGSEG,				/* Absolute byte offset - uppercase			 */
	CTSEG_SRLSEG,				/* Absolute byte offset - auto increment	 */
	CTSEG_VARSEG,				/* Relative field number					 */
	CTSEG_UVARSEG,				/* Relative field number - uppercase		 */
	CTSEG_SGNSEG	= 8,		/* Absolute byte offset - signed int/long	 */
	CTSEG_FLTSEG,				/* Absolute byte offset - float/double		 */
	CTSEG_DECSEG,				/* Absolute byte offset - not yet implemented*/
	CTSEG_BCDSEG,				/* Absolute byte offset - not yet implemented*/
	CTSEG_SCHSEG	= 12,		/* Absolute field number					 */
	CTSEG_USCHSEG,				/* Absolute field number - uppercase		 */
	CTSEG_VSCHSEG,				/* Absolute field number - pad strings		 */
	CTSEG_UVSCHSEG,				/* Absolute field number - pad strings upper */
	CTSEG_DESCENDING= 16,		/* Descending segment mode					 */
	CTSEG_ALTSEG	= 32,		/* Alternative collating sequence			 */
	CTSEG_ENDSEG	= 64,		/* END segment mode							 */
	CTSEG_UNCSEG	= 128,
	CTSEG_RECBYT	= 256,
	CTSEG_SCHSRL	= 257,		/* field # of schema for SRLSEG				 */
	CTSEG_GNXSEG	= 1024,
	CTSEG_INVALID	= 0xffff	/* invalid segment mode						 */
};

#define CTSEG_MASK	0x010f		/* permits a seg mode range 0-15 and 256-271 */

typedef NINT	CTSEG_MODE;
/*^****************************************************************************\
*
*   CTDB state flags
*
\******************************************************************************/
#define CTDB_STATE_INACTIVE			1
#define CTDB_STATE_ACTIVE			2
/*^****************************************************************************\
*
*   CTDB lock modes
*
\******************************************************************************/
enum CT_LOCK_MODES_E
{
	CTLOCK_FREE,				/* free any locks							*/
	CTLOCK_READ,				/* non blocking read locks					*/
	CTLOCK_READ_BLOCK,			/* blocking read locks						*/
	CTLOCK_WRITE,				/* non blocking write locks					*/
	CTLOCK_WRITE_BLOCK,			/* blocking write locks						*/
	CTLOCK_RESET,				/* equivalent to first calling ctdbLock with*/
								/* CTLOCK_FREE followed by CTLOCK_WRITE		*/
	CTLOCK_SUSPEND,				/* temporarily suspend locking				*/
	CTLOCK_RESTORE_READ,		/* restore CTLOCK_READ mode					*/
	CTLOCK_RESTORE_READ_BLOCK,	/* restore CTLOCK_READ_BLOCK mode			*/
	CTLOCK_RESTORE_WRITE,		/* restore CTLOCK_WRITE mode				*/
	CTLOCK_RESTORE_WRITE_BLOCK	/* restore CTLOCK_WRITE_BLOCK mode			*/
};

typedef NINT	CTLOCK_MODE;
/*^****************************************************************************\
*
*   CTDB Keep Lock mode
*
\******************************************************************************/
typedef enum
{
    CTKEEP_FREE    = 0,			/* release all locks. Clear LKISAM state    */
    							/* this is the default mode					*/
    CTKEEP_LOCK    = 1,			/* keep all locks acquired before and during*/
     							/* transaction. Does not clear LKISAM state */
    CTKEEP_OUT     = 2,			/* release only locks obtained within trans */
    							/* and/or locks on records updated within   */
    							/* transaction. Does not clear LKISAM state */
    CTKEEP_OUTALL  = 3			/* unconditionally keep all locks acquired  */
                                /* before transaction began. Free locks     */
                                /* obtained within the transaction. Does not*/
                                /* clear LKISAM state    					*/
} CTKEEP_MODE;
/*^****************************************************************************\
*
*   CTDB begin transaction modes
*
\******************************************************************************/
typedef enum
{
	CTBEGIN_NONE	= 0,		/* No begin transaction mode set. Apply 	*/
								/* default begin transaction mode			*/
	CTBEGIN_PREIMG	= 1,		/* Transaction atomicity only. Auto-recovery*/
								/* is not availabe. Mutually exclusive with	*/
								/* CTBEGIN_TRNLOG.							*/
	CTBEGIN_TRNLOG	= 3,		/* Full transaction processing functionality*/
								/* including auto-recovery. Mutually 		*/
								/* exclusive to CTBEGIN_PREIMG. This is the	*/
								/* default begin transaction mode.			*/
	CTBEGIN_DEFER	= 4,		/* Defer begin transaction until update		*/
	CTBEGIN_AUTOSAVE= 8,		/* Automatically invokes savepoints after	*/
								/* each successful record or resource update*/
	CTBEGIN_TWOPHASE=16 		/* Enable two-phase commit transaction mode.*/
								/* ctdbPrepareCommit() is called for "first */
								/* phase commit", then ctdbCommit() for the */
								/* "second phase commit"					*/
} CTBEGIN_MODE;
/*^****************************************************************************\
*
*   CTDB Record buffer mode
*
\******************************************************************************/
#define CTRECBUF_MASK		0xffffL

#define CTRECBUF_AUTO		0	/* Automatic record buffer management	*/
#define CTRECBUF_STATIC		1	/* Record buffer managed by user		*/

#define CTRECBUF_RAW		(CTRECBUF_MASK + 1L)/* Raw record buffer	*/

typedef ULONG	CTRECBUF_MODE;
/*^****************************************************************************\
*
*   CTDB binary field handling mode
*
\******************************************************************************/
typedef enum
{
	CTDB_BINARY_UNKNOWN = 0,		/* table created by c-treeDB prior to v9  */
									/* it indicates that CT_ARRAY or CT_2STRING*/
									/* field may or may not have extra 4 bytes*/
									/* at the beginning of data				  */
	CTDB_BINARY_FIXED	= 1,		/* table created by c-treeDB with v9 and  */
									/* after, CT_ARRAY and CT_2STRING fields  */
									/* are handled correctly				  */
	CTDB_BINARY_WITH_LENGTH = 2,	/* table created prior to v9, but table   */
									/* was operated only with c-treeACE SQL and   */
									/* CT_ARRAY and CT_2STRING fields have    */
									/* four bytes at the beginning of the data*/
									/* resource was updated by utility        */
	CTDB_BINARY_WITHOUT_LENGTH = 3,	/* table created by c-treeDB prior to v9  */
									/* but utility has updated this resource  */
	/* following types are handled correctly (as CTDB_BINARY_FIXED) */
	/* but used to indicate SQL types sharing CT_2STRING/CT_4STRING c-tree type other than varbinary/lvarbinary */
	CTDB_BINARY_VARCHAR = 4,  /* VARCHAR/LVARCHAR field created by c-treeSQL in v10 */
	CTDB_BINARY_CLOB = 5, /* CLOB field created by c-treeSQL in v10*/

	CTDB_BINARY_BLOB = 6, /* BLOB field created by c-treeSQL in v10*/
	CTDB_NUMBER_MONEY = 7, /* NUMBER field used to store MONEY type (instead of using  CT_CURRENCY) */
	CTDB_FIELDFLAG_USER1  = 8,  /* field used to store USER type */
	CTDB_FIELDFLAG_USER2  = 9,  /* field used to store USER type */
	CTDB_FIELDFLAG_USER3  = 10, /* field used to store USER type */
	CTDB_FIELDFLAG_USER4  = 11, /* field used to store USER type */
	CTDB_FIELDFLAG_USER5  = 12, /* field used to store USER type */
	CTDB_FIELDFLAG_USER6  = 13, /* field used to store USER type */
	CTDB_FIELDFLAG_USER7  = 14, /* field used to store USER type */
	CTDB_FIELDFLAG_USER8  = 15, /* field used to store USER type */
	CTDB_FIELDFLAG_USER9  = 16, /* field used to store USER type */
	CTDB_FIELDFLAG_USER10 = 17, /* field used to store USER type */
	CTDB_BINARY_MAX /* Largest Enum value */
} CTDB_BINARY_FLAG;
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Vector unit size
*
\******************************************************************************/
#define CTDB_VECTOR_UNIT            16
/*^****************************************************************************\
*
*   Transaction Isolation levels
*
\******************************************************************************/
typedef enum
{
	CTTRANISO_CTREE	= -1,			/* c-tree default isolation level		*/
	CTTRANISO_READ_UNCOMMITED = 0,	/* read uncommited - not supported		*/
	CTTRANISO_READ_COMMITED = 1,	/* read commited						*/
	CTTRANISO_REPEATABLE_READ = 2,	/* repeatable read						*/
	CTTRANISO_SERIALIZABLE = 3		/* serializable							*/
} CTTRANISO;
/*^****************************************************************************\
*
*   SQL import callback modes
*
\******************************************************************************/
typedef enum
{
	CTSQLCB_ERROR = 1,              /* handle error                                    */
	CTSQLCB_WARNING	= 2,            /* handle warning                                  */
	CTSQLCB_CONFIRM_SKIPIDX	= 3,	/* confirm skipping index import                   */
	CTSQLCB_CONFIRM_PUTIFIL	= 4,	/* confirm PUTIFIL update                          */
	CTSQLCB_CONFIRM_NOPUTIFIL = 5,	/* confirm continuing after skipping PUTIFIL       */
	CTSQLCB_CONFIRM_REPLACELNK = 6,	/* confirm replacing existing table link           */
	CTSQLCB_CONFIRM_CHANGEPAD = 7,	/* confirm changing string pad strategy            */
	CTSQLCB_CONFIRM_SPACEPAD = 8,	/* confirm space padding or zeroes padding         */
	CTSQLCB_CONFIRM_NULLTERM = 9,	/* confirm NULL terminator                         */
	CTSQLCB_CONFIRM_PUTPAD = 10,	/* confirm updating PAD resource                   */
	CTSQLCB_CONFIRM_NOPUTPAD = 11,	/* confirm continuing after skipping upd PAD       */
	CTSQLCB_CONFIRM_SKPHIDFLD = 12,	/* confirm skip of FC-ODBC hidden field            */
	CTSQLCB_CONFIRM_SKPHFLDIDX = 13,/* confirm skip of hidden field's indexes          */
	CTSQLCB_RETURN_SYMTBLNAME = 14, /* return alternate symbolic table name            */
	CTSQLCB_ELAB_IDX = 15,          /* confirm index elaboration                       */
	CTSQLCB_PROMOTE_UINT = 16,      /* promote unsigned integer to greater signed type */
	CTSQLCB_RETURN_PRIIDXNAME = 17,	/* return primary key index name                   */
	CTSQLCB_RETURN_TBLUID = 18,     /* return table id                                 */
	CTSQLCB_STRING_PARTSEG = 19,    /* allow segments on strings missing last byte     */
	CTSQLCB_FORCE_PADDING = 20,     /* force string padding                            */
	CTSQLCB_RETURN_MAXFLDLEN = 21,  /* return maximum length of fields                 */
	CTSQLCB_RETURN_IDXMETHOD = 22,  /* return SQL index method id                      */
	CTSQLCB_CONFIRM_NONCONVIDS = 23,/* confirm import of non-conventional identifiers  */
	CTSQLCB_GRANT_PUBLIC = 24,      /* grant access to public (all SQL users)          */
	CTSQLCB_CONFIRM_PRIIDX = 25,    /* confirm if primary key (NO calls #17 YES is primary) */
	CTSQLCB_RETURN_TBLPREFIX = 26,  /* return prefix to table name                     */
	CTSQLCB_CONFIRM_MAXIDXENTRIES = 27,/* confirm continuing on reaching max idx fields */
	CTSQLCB_PROMOTE_UINT_CHECK = 28,   /* adde check constraint for promoted unsigned integer */
	CTSQLCB_GRANT_PUBLIC_RO = 29,      /* grant read-only access to public (all SQL users)    */
	CTSQLCB_CONFIRM_MAXKEYSEG = 30,    /* confirm continuing when #of seg > MAX_KEY_SEG  */
	CTSQLCB_CONFIRM_MAXIDX = 31,        /* confirm continuing when #of indices > MAX_DAT_KEY  */
	CTSQLCB_CONFIRM_INDEXTRUNC = 32,    /* allow indexes with rigthmost segment(s) on hidden field(s) */
	CTSQLCB_RETURN_TBLORIGIN = 33,  /* return table origin (10 chars) */
	CTSQLCB_CONFIRM_SKPREGFLD = 34,  /* confirm hiding of a field that would be exposed */
	CTSQLCB_CONFIRM_KEEPEXTRAS = 35,  /* keep information in sys*auth and syssynonyms tables during unlink/link operation */
	CTSQLCB_CONFIRM_NULKEY_IMP = 36 /* confirm import of ISAM keys with NUL key support */
} CTSQLCB_MODE;
/*^****************************************************************************\
*
*   CTDB Alter table actions
*
\******************************************************************************/
#define CTDB_ALTER_NORMAL		0	/* check for changes before altering	*/
#define CTDB_ALTER_INDEX		1	/* Force rebuild of all indexes			*/
#define CTDB_ALTER_FULL			3	/* Force full table rebuild				*/
#define CTDB_ALTER_FTI			4	/* Force rebuild af all Full Text indexes */
#define CTDB_ALTER_HOT			8	/* Force hot alter table */
#define CTDB_ALTER_PURGEDUP		0x1000	/* Purge duplicate record			*/
#define CTDB_ALTER_TRUNCATE		0x2000	/* Truncate the table - forces CTDB_ALTER_FULL */
#define CTDB_ALTER_OWNER		0x4000	/* Force owner reasignement			*/
#define CTDB_ALTER_KEEPTRAN		0x8000	/* use the existing transaction mode even during the alter*/
#define CTDB_ALTER_V8DELFLD		0x0100	/* force CTCREATE_V8DELFLD during alter table */
#define CTDB_ALTER_MASK			0x00ff
/*^****************************************************************************\
*
*   CTDB table rebuild mode
*
\******************************************************************************/
typedef enum
{
	CTREBUILD_NONE		= 0,		/* normal rebuild mode					*/
	CTREBUILD_PURGEDUP	= 1,		/* purge duplicate records				*/
	CTREBUILD_UPDATEIFIL= 2,		/* update table IFIL structure			*/
	CTREBUILD_DATAONLY	= 4, 		/* rebuild only the data file			*/
	CTREBUILD_COMPACT	= 8 		/* compact and rebuild			*/
} CTREBUILD_MODE;
/*^****************************************************************************\
*
*   CTDB Table types
*
\******************************************************************************/
typedef enum
{
	CTDB_TABLE_NONE = 0,			/* not table handle or table not active */
	CTDB_TABLE_SESSION_DICT,		/* session dictionary table 			*/
	CTDB_TABLE_DATABASE_DICT,		/* database dictionary table 			*/
	CTDB_TABLE_SQL_CATALOG,			/* ctreeSQL catalog table 				*/
	CTDB_TABLE_USER					/* user table 							*/
} CTDB_TABLE_TYPE;

/*^****************************************************************************\
*
*   CTDB SDK Full Text Index types
*
\******************************************************************************/

/* FTI creation options (internal)*/
#define CTDB_FTI_CREATE_DICT 0x00000001   /* create word/token dictionary*/
#define CTDB_FTI_CREATE_REFT  0x00000002  /* create reference table */


#define CTDB_FTI_MAX_TOKENPARAM 511
#define CTDB_FTI_DEF_TOKENSIZE 45 /* according to Wikipedia "Technical; coined to be the longest word" in English is 45 chars */

/* FTI options */
/*        generic   */
#define CTDB_FTI_OPTION_UPD         1    /* FTI update option (long)*/

/*        Dictionary */
#define CTDB_FTI_OPTION_TOKENSIZE    2    /* max token size (long)*/
#define CTDB_FTI_OPTION_TOKENIZER    3    /* tokenizer (long)*/
#define CTDB_FTI_OPTION_ICULANG      4    /* ICU tokenizer language (string)*/
#define CTDB_FTI_OPTION_ICUOPTION    5    /* ICU tokenizer normalization/strength/attributes (long) */
#define CTDB_FTI_OPTION_CUSTLIB      6    /* custom tokenizer dll (string)*/
#define CTDB_FTI_OPTION_CUSTPARAM    7    /* custom tokenizer params (string)*/
#ifdef REMOVED_20171012  /* option causing troubles and requiring path to be stored in resource. see devlog for further details*/
#define CTDB_FTI_OPTION_USE_EXISTING 8    /* set options base on existing one with the full name passed in (string and long) */
#endif
#define CTDB_FTI_OPTION_SUPERFILE    9    /* store in superfile (long)*/
#define CTDB_FTI_OPTION_STOP_LIST   10    /* set the list of stop words */
#define CTDB_FTI_OPTION_CNDXEXPR    11    /* set the conditional expression */




/* FTI options values */
/* the following are mutually exclusive i.e. specify only one of them */
#define CTDB_FTI_OPTION_UPD_ASYNC	0x00000000  /* perform FTI updates in background */
#define CTDB_FTI_OPTION_UPD_IMMEDIATE	0x00000001  /* perform FTI updates  */
#define CTDB_FTI_OPTION_UPD_ATCOMMIT	0x00000002  /* perform FTI updates during transaction commit */

#define CTDB_FTI_OPTION_MASK		0x000000FF  /* mask to distinguish mutually exclusive values */

/* the following can be or'd with the above */
#define CTDB_FTI_OPTION_IGNORE_EXISTING   0x00000100  /* do not load existing record upon index creation */
#define CTDB_FTI_OPTION_BACKLOAD_EXISTING 0x00000200  /* do not load existing record in background */

/* FTI tokenizer option, do not change assigned values as these are stored in resources!*/
#define CTDB_FTI_TOKENIZER_CUSTOM    0
#define CTDB_FTI_TOKENIZER_SIMPLE    1
#define CTDB_FTI_TOKENIZER_PORTER    2
#define CTDB_FTI_TOKENIZER_ICU       3


/* FTI fields modes (bitmask!!) */
#define CTDB_FTI_MODE_REG   0x00000001 /* default field treatment */
#define CTDB_FTI_MODE_UTF8  0x00000002 /* field format in utf8 */
#define CTDB_FTI_MODE_UTF16 0x00000004 /* field format in utf16 */

/* FTI superfile modes (mutually exlusive) */
#define CTDB_FTI_SUPERFILE_NO 0x00 /* default no superfile use */
#define CTDB_FTI_SUPERFILE_YES 0x01 /* index created as superfile member in FTI superfile for the table */
#define CTDB_FTI_SUPERFILE_IDX 0x02 /* index created as superfile (specific for the index) */
#define _CTDB_FTI_SUPERFILE_DAT 0x03 /* index created as superfile member in the table superfile (internal use only)*/


#ifdef CTDB_BACKGROUND_INDEX_LOAD
/*^****************************************************************************\
*
*   CTDB backgroundindex load
*
\******************************************************************************/
#define CTDB_BACKGROUND_IDXLOAD "$BIXL$"
#define CTDB_BACKGROUND_IDXSIZ 6
#endif

/*^****************************************************************************\
*
*   CTDB Callback types
*
\******************************************************************************/
typedef enum
{
	CTDB_ON_RECORD_MAPTOPARENT,		/* map child record to parent record	*/
	CTDB_ON_RECORD_MAPTOCHILD,		/* map parent record to child record	*/
	CTDB_ON_RECORD_INIT,			/* called after record initialization	*/
	CTDB_ON_RECORD_RESET,			/* called before record reset			*/
	CTDB_ON_RECORD_BEFORE_BUILD_KEY,/* called before a key is built			*/
	CTDB_ON_RECORD_AFTER_BUILD_KEY,	/* called after key is built			*/
	CTDB_ON_RECORD_BEFORE_READ,		/* called before record is read			*/
	CTDB_ON_RECORD_AFTER_READ,		/* called after record is read			*/
	CTDB_ON_RECORD_BEFORE_WRITE,	/* called before record is written		*/
	CTDB_ON_RECORD_AFTER_WRITE,		/* called after record is written		*/
	CTDB_ON_TABLE_OPEN,				/* called after data and index file open*/
	CTDB_ON_TABLE_CLOSE,			/* called before a table close			*/
	CTDB_ON_TABLE_GET_DODA,			/* called after a table open to get doda*/
	CTDB_ON_TABLE_GET_SCHEMA,		/* called after a table open to get schema */
	CTDB_ON_TABLE_GET_EXT_INFO,		/* called after a table open to get extended field info */
	CTDB_ON_TABLE_GET_RECLEN,		/* called after table open to retrieve fixed reclen */
	CTDB_ON_TABLE_ALTER,			/* called at alter table				*/
	CTDB_ON_TABLE_REBUILD,			/* called called during full alter table rebuild */
	CTDB_ON_TABLE_GET_IFIL,			/* called after a table open to get the IFIL */
	CTDB_ON_TABLE_OPEN_ERROR,		/* called before returning if the table open fails */
	CTDB_ON_TABLE_BEFORE_OPEN,		/* called before opening a table */
	CTDB_ON_TABLE_GET_VTABLE_INFO,	/* called when counting the number of VTABLES in a table */
	CTDB_ON_TABLE_GET_SCHEMANAMES,	/* called after a table open to get schema names for expression evaluator*/
	CTDB_ON_DATABASE_CONNECT,		/* called after a database connect		*/
	CTDB_ON_DATABASE_DISCONNECT,	/* called before a database disconnect	*/
	CTDB_ON_SESSION_LOGON,			/* called after a session logon			*/
	CTDB_ON_SESSION_LOGOUT,			/* called before a session logout		*/

	CTDB_ON_LAST_CALLBACK			/* last callback marker					*/
} CTDB_CALLBACK_TYPE;
/*^****************************************************************************\
*
*   CTDB Field Callback types
*
\******************************************************************************/
typedef enum {
	t_invalid,
	t_bool,
	t_signed,
	t_unsigned,
	t_float,
	t_string, /*generic string (used in get) */
	t_fstring, /* fixed length string (used in set) */
	t_vstring, /* vlength string (used in set) */
	t_bigint,
	t_ubigint,
	t_currency,
	t_number,
	t_UTF8,
	t_UTF16,
	t_blob /* Binary (or char) Large OBject */
	} CTDB_FIELD_METATYPE;

typedef enum
{
	CTDB_FIELD_GET_TYPE,				/* ctdbGetFieldType / ctdbGetFieldProperty / ctdbAddSegment*/
	CTDB_FIELD_GET_LENGTH,				/* ctdbGetFieldLength / ctdbGetFieldProperty / ctdbGetFieldSize*/
	CTDB_FIELD_GET,				/* _ctdbGet*Field */
	CTDB_FIELD_SET,				/* _ctdbSet*Field */
	CTDB_FIELD_ISNULL,				/* ctdbIsNULLField* */
	CTDB_FIELD_CLEAR,				/* ctdbClearField */
	CTDB_FIELD_DATA_LEN,				/* ctdbGetFieldDataLength */
	CTDB_FIELD_FIX_SEGMODE,				/* ctdbAddSegment*/
	CTDB_FIELD_GNXSEG,			/* ctdbAddSegment*/
	CTDB_FIELD_LAST_CALLBACK			/* last callback marker */
} CTDB_FIELD_CALLBACK_TYPE;

typedef struct {
	pVOID buffer;
	VRLEN length;
	NINT fix_padChar;
	NINT fix_dlmChar;
	TEXT fix_truncate; /*boolean value */
	pVOID var_rec;
} FLD_CBK_STRBUF, ctMEM* pFLD_CBK_STRBUF;

/*^****************************************************************************\
*
*   CTDB Record filter types
*
\******************************************************************************/
#ifdef ctdbRECORD_FILTER
typedef enum
{
	CTFILTER_NONE,				/* no filter is active			*/
	CTFILTER_TEXT,				/* filter is a text expression		*/
	CTFILTER_TREE				/* filter is a binary parse tree	*/
} CTFILTER_TYPE;
#endif
/*^****************************************************************************\
*
*   CTDB system wide record filters
*
\******************************************************************************/
#ifdef CTDB_SYSTEM_FILTER
typedef enum
{
	CTSYSFILTER_NONE = 0,			/* indicate no system wide record filter */
	CTSYSFILTER_READ = 1,			/* indicate a read system wide filter 	 */
	CTSYSFILTER_WRITE = 2			/* indicate a write system wide filter 	 */
} CTSYSFILTER;
#endif /* CTDB_SYSTEM_FILTER */
/*^****************************************************************************\
*
*   CTDB SQL system version
*
\******************************************************************************/
typedef enum
{
	CTSQL_NOTMATCH	= 0,
	CTSQL_VER1	= 1,
	CTSQL_VER2	= 2
} CTSQL_VERSION;
/*^****************************************************************************\
*
*   CTDB SQL check level
*
\******************************************************************************/
typedef enum
{
	CTSQL_DUMPSYSTAB	= 1,
	CTSQL_CHECKSTSTRU	= 2,
	CTSQL_CHECKSTDATA	= 3
} CTSQL_CHKLEVEL;
/*^****************************************************************************\
*
*   CTDB allocation types
*
\******************************************************************************/
typedef enum					/* Alternate memory alloc types(debugging 131111)*/
{
	CTDB_RECORD_BUFFER	= 1,		/* CTDB Record buffer alloc */ 
	UNDEF_POINTER = 2					/* pointer could point UNDEF_PRT and must not to be freed */
} CTDB_ALLOC_TYPE;

/*^****************************************************************************\
*
*   CTDB Field Status
*
\******************************************************************************/
#define CTDBFIELD_OLD			0x0000	/* Original field as read from table  */
#define CTDBFIELD_NEW			0x0001	/* Field added or inserted			  */
#define CTDBFIELD_DEL			0x0002	/* Original field deleted			  */
#define CTDBFIELD_MOVED			0x0004	/* Original field moved				  */
#define CTDBFIELD_NAME			0x0010	/* Field name changed				  */
#define CTDBFIELD_TYPE			0x0020	/* Field type changed				  */
#define CTDBFIELD_LEN			0x0040	/* Field length changed				  */
#define CTDBFIELD_RESOURCE		0x0080	/* Field resource changed			  */
#define CTDBFIELD_IDENTITY		0x0100	/* Field Identity added/updated		  */
#define CTDBFIELD_AUTOTS		0x0200	/* Field Automatic Time Stamp updated */
/*^****************************************************************************\
*
*   CTDB Index Segment Status
*
\******************************************************************************/
#define CTDBISEG_OLD			0x0000	/* Original segment as read from file */
#define CTDBISEG_NEW			0x0001	/* Segment added or inserted          */
#define CTDBISEG_DEL			0x0002  /* Original segment deleted           */
#define CTDBISEG_MOVED			0x0004	/* Original segment moved             */
#define CTDBISEG_MODE			0x0010	/* Segment mode changed               */
#define CTDBISEG_FIELD			0x0020	/* Segment field changed			  */
/*^****************************************************************************\
*
*   CTDB Index Status
*
\******************************************************************************/
#define CTDBINDEX_OLD			0x0000	/* Original index as read from file   */
#define CTDBINDEX_NEW			0x0001	/* Index added                        */
#define CTDBINDEX_DEL			0x0002	/* Original Index deleted             */
#define CTDBINDEX_KEYTYPE		0x0010  /* Index key type changed             */
#define CTDBINDEX_EMPCHAR		0x0020	/* Index empty char changed           */
#define CTDBINDEX_DUPFLAG		0x0040	/* Index duplicate flag changed       */
#define CTDBINDEX_NULLFLAG		0x0080	/* Index null flag changed            */
#define CTDBINDEX_AIDXNAM		0x0100  /* Index file name changed            */
#define CTDBINDEX_RIDXNAM		0x0200  /* Index symbolic name changed        */
/* the following will be activated when Bill fix it */
#define CTDBINDEX_DUPCNTFLAG	0x0400 /* Index distinct count flag changed  */
/*^****************************************************************************\
*
*   CTDB Full Text Index (FTI) Status
*
\******************************************************************************/
#define CTDBFTI_OLD			0x0000	/* Original FTI as read from file   */
#define CTDBFTI_NEW			0x0001	/* FTI added                        */
#define CTDBFTI_DEL			0x0002	/* Original FTI deleted but not yet "alter" */
#define CTDBFTI_OPTUPD			0x0004	/* Options updated */

/*^****************************************************************************\
*
*   CTDB Full Text Index Dictionary (FTID) Status
*
\******************************************************************************/
#define CTDBFTID_OLD			0x0000	/* Original FTID as read from file   */
#define CTDBFTID_NEW			0x0001	/* New FTID                          */
#define CTDBFTID_UPD			0x0002	/* updated FTID                      */

/*^****************************************************************************\
*
*   CTDB rebuild action
*
\******************************************************************************/
#define CTDB_REBUILD_NONE		0		/* Nothing to be done, table is ok	  */
#define CTDB_REBUILD_DODA		1		/* Update the table doda			  */
#define CTDB_REBUILD_RESOURCE	2		/* Update table FC!DFLD resource      */
#define CTDB_REBUILD_INDEX		4		/* Add new indices 					  */
#define CTDB_REBUILD_ALL		8		/* Rebuild all indices				  */
#define CTDB_REBUILD_FULL		16		/* Full table rebuild. A temporary	  */
										/* table is created and all data is	  */
										/* moved to new table building 		  */
										/* indices on the fly				  */
#ifdef CTDBINDEX_DUPCNTFLAG
#define CTDB_REDO_DSTCNT		32		/* activate/deactivate/calculate the  */
										/* duplicate index distinct key count */
#endif
#define CTDB_REBUILD_IDENTITY	64		/* Update the identity information    */
#define CTDB_REBUILD_FTI		128		/* Add new FTI                        */
#define CTDB_REBUILD_FTI_ALL	256		/* Redo all FTI to table              */
#define CTDB_REBUILD_HOT	512		/* Change schema using hot alter table */
#ifdef CTDB_BACKGROUND_INDEX_LOAD
#define CTDB_REBUILD_INDEX_SHARED	1024	/* Rebuild index can be done in shared mode*/
#endif
#define CTDB_REBUILD_AUTOTS	2048		/* Update the auto timestamp information */

/*^****************************************************************************\
*
*   CTDB Alter callback time during alter operation
*
\******************************************************************************/
#define CTDBALTER_TIME_START 0
#define CTDBALTER_TIME_END   1
#define CTDBALTER_TIME_ACTION  2
#define CTDBALTER_TIME_NOTRUNNING 3


/*^****************************************************************************\
*
*   CTDB BATCH Mandatory modes
*	Only one of the following must be used
*
\******************************************************************************/
#define CTBATCH_NONE		0x00		/* batch is not active				  */
#define CTBATCH_GET			0x01		/* retrieve records by partial key	  */
#define CTBATCH_RANGE		0x02		/* retrieve records by index range	  */
#define CTBATCH_PHYS		0x03		/* retrieve records by physical order */
#define CTBATCH_DEL			0x04		/* delete group of related records	  */
#define CTBATCH_INS			0x05		/* insert a group of records		  */
#define CTBATCH_UPD			0x06		/* REQRITE a group of records		  */
#define CTBATCH_MANDATORY	0xff 		/* mask for mandatory modes			  */
/*^****************************************************************************\
*
*   CTDB BATCH other modes
*	these batch modes should be or'ed in to mandatory modes
*
\******************************************************************************/
#define CTBATCH_GKEY		0x00000200		/* process records >= target key	  */
#define CTBATCH_LKEY		0x00000400		/* process records <= target key	  */
#define CTBATCH_VERIFY		0x00000800		/* verify target keys				  */
#define CTBATCH_LOCK_KEEP	0x00001000		/* keep locks after ctdbBatchEnd	  */
#define CTBATCH_LOCK_READ	0x00002000		/* apply read locks					  */
#define CTBATCH_LOCK_WRITE	0x00004000		/* apply write locks				  */
#define CTBATCH_LOCK_BLOCK	0x00008000		/* locks should block				  */
#define CTBATCH_LOCK_ONE	0x00010000		/* lock on during read				  */
#define CTBATCH_COMPLETE	0x00020000		/* return success only if all locked  */
#define CTBATCH_KEEPSRLSEG	0x00040000		/* keep serial segment on update      */
#define CTBATCH_AUTORESIZE	0x00080000		/* automatically resize buffer if not */
										/* large enough to contain at least 1 record */
#define CTBATCH_REVERSE		0x00100000		/* return range results in reverse order */
/*^****************************************************************************\
*
*   CTDB BATCH mode type
*
\******************************************************************************/
#define CTBATCH_RECORDS		128

typedef ULONG	CTBATCH_MODE;			/* batch modes 						  */
/*^****************************************************************************\
*
*   CTDB SETOPS types
*
\******************************************************************************/
typedef LONG		CTOPS_MODE;
typedef VRLEN		CTOPS_STATE;
/*^****************************************************************************\
*
*   CTDB Session attach modes
*
\******************************************************************************/
typedef enum
{
	CTATTACH_NONE,					/* Not attached 						  */
	CTATTACH_SESSION,				/* Attached to another session			  */
	CTATTACH_CTREEID,				/* Attached by c-tree instance id		  */
	CTATTACH_CURRENT				/* Attached to current c-tree instance	  */
} CTATTACH_MODE;

/*^****************************************************************************\
*
*   CTDB Record Ranges rangeFlags values
*
\******************************************************************************/
#define CTDB_RANGE_NORMAL   0x0000
#define CTDB_RANGE_INDEXONLY 0x0001

/*^****************************************************************************\
*
*   CTDB C API return codes
*
\******************************************************************************/
typedef enum
{
	CTDBRET_FAILURE		= -1,   /* CTDB C API Failed                		*/
	CTDBRET_OK		= 0,    /* CTDB C API return OK   			*/
	CTDBRET_BASE		= 4000, /* Base error number      			*/
	CTDBRET_NOMEMORY	= 4001,	/* Not enough memory      			*/
	CTDBRET_NULHANDLE	= 4002, /* Handle is NULL        			*/
	CTDBRET_NOTSESSION	= 4003, /* No session handle      			*/
	CTDBRET_INVARG		= 4004, /* Invalid argument       			*/
	CTDBRET_INDEXRANGE	= 4005, /* Index out of range     			*/
	CTDBRET_ARGSMALL	= 4006, /* Argument is too small  			*/
	CTDBRET_NULARG		= 4007, /* Null argument not valid			*/
	CTDBRET_ARGNUL		= 4008, /* Null argument not valid			*/
	CTDBRET_NOTOPEN		= 4009, /* Table is not open      			*/
	CTDBRET_NOTDATABASE	= 4010, /* Not a database handle  			*/
	CTDBRET_ISACTIVE	= 4011, /* Handle is active       			*/
	CTDBRET_NOTACTIVE	= 4012, /* Handle is not active   			*/
	CTDBRET_NOTTABLE	= 4013, /* Handle is not a table  			*/
	CTDBRET_NOSUCHFIELD	= 4014, /* Unknown field name     			*/
	CTDBRET_CANTDELETE	= 4015, /* Can't perform delete   			*/
	CTDBRET_FIELDEXIST	= 4016, /* Field already exists    			*/
	CTDBRET_NOTFIELD	= 4017, /* Not a field handle     			*/
	CTDBRET_NOTINDEX	= 4018, /* Not an index handle    			*/
	CTDBRET_INVTYPE		= 4019, /* Invalid field/key type 			*/
	CTDBRET_NOTSEGMENT	= 4020, /* Not a segment handle   			*/
	CTDBRET_DATABASEEXIST 	= 4021,	/* Database already exists			*/
	CTDBRET_TABLEEXIST	= 4022, /* Table already exists    			*/
	CTDBRET_NOSUCHTABLE	= 4023, /* Table does not exist   			*/
	CTDBRET_NOTRECORD	= 4024, /* Not a record handle    			*/
	CTDBRET_INTERNAL	= 4025, /* Internal error         			*/
	CTDBRET_INVFIND		= 4026, /* Invalid find mode      			*/
	CTDBRET_NODATA		= 4027, /* No data in record      			*/
	CTDBRET_INVFORMAT	= 4028, /* Invalid date or time format 			*/
	CTDBRET_INVDATE		= 4029, /* Invalid date           			*/
	CTDBRET_INVDAY		= 4030, /* Invalid date day       			*/
	CTDBRET_INVMONTH	= 4031, /* Invalid date month     			*/
	CTDBRET_INVYEAR		= 4032, /* Invalid date year      			*/
	CTDBRET_INVTIME		= 4033, /* Invalid packed CTTIME  			*/
	CTDBRET_INVHOUR		= 4034, /* Invalid hour           			*/
	CTDBRET_INVMINUTE	= 4035, /* Invalid minute         			*/
	CTDBRET_INVSECOND	= 4036, /* Invalid second         			*/
	CTDBRET_INVAMPM		= 4037, /* Invalid time AM or PM value 			*/
	CTDBRET_OVERFLOW	= 4038, /* Operation causes Overflow 			*/
	CTDBRET_UNDERFLOW	= 4039, /* Operation cause underflow 			*/
	CTDBRET_DIVBYZERO	= 4040, /* Division by zero error 			*/
	CTDBRET_INVDATETIME	= 4041, /* Invalid timestamp 				*/
	CTDBRET_CANTCONVERT	= 4042, /* Can't perform type conversion 		*/
	CTDBRET_TOOBIG      	= 4043, /* Argument is too big    			*/
	CTDBRET_NOSUCHPATH	= 4044,	/* Path does not exist	  			*/
	CTDBRET_NOSUCHINDEX	= 4045,	/* Unknown index number	  			*/
	CTDBRET_NOTFOUND	= 4046,	/* Not found	 		  		*/
	CTDBRET_INVSEGMODE	= 4047,	/* Invalid segment mode	  			*/
	CTDBRET_NOINDEX		= 4048,	/* Table has no indices				*/
	CTDBRET_NOSUCHSEGMENT 	= 4049,/* Invalid segment number			*/
	CTDBRET_INVICON		= 4050,	/* Invalid ISAM context handle			*/
	CTDBRET_INDEXEXIST	= 4051,	/* Index name already in use			*/
	CTDBRET_MOREDATA	= 4052,	/* Partial field data read			*/
	CTDBRET_NOINDEXNAME	= 4053,	/* Invalid index name				*/
	CTDBRET_NOTSUPPORTED 	= 4054,	/* Feature not supported			*/
	CTDBRET_INVLOCKMODE	= 4055,	/* Invalid lock mode				*/
	CTDBRET_NOLOCK		= 4056,	/* Record not locked				*/
	CTDBRET_NOWRITELOCK	= 4057,	/* Record is not locked	for writes		*/
	CTDBRET_NOTDICT		= 4058,	/* Dictionary handle not allocated		*/
	CTDBRET_NOTYET		= 4059,	/* Not yet implemented				*/
	CTDBRET_INVNUMBER	= 4060,	/* Invalid number				*/
	CTDBRET_INVPREC		= 4061,	/* Invalid number precision			*/
	CTDBRET_INVSCALE	= 4062,	/* Invalid number scale				*/
	CTDBRET_INVRECBUF	= 4063, /* Record buffer not large enough		*/
	CTDBRET_CANTDELRECBYT 	= 4064,/* recbyt index can't be deleted			*/
	CTDBRET_CANTDELROWID 	= 4065,/* rowid index can't be deleted			*/
	CTDBRET_NOROWID		= 4066, /* Table has no rowid index			*/
	CTDBRET_CANTCREATE	= 4067, /* cannot create a file (dupdb) 		*/
	CTDBRET_CANTCOPY	= 4068, /* cannot copy a file (dupdb) 			*/
	CTDBRET_NOTSUSPENDED 	= 4069,  /* can't restore lock				*/
	CTDBRET_INVISOLEVEL	= 4070,	/* invalid isolation level			*/
#ifdef CTDB_CNDX_IDX
	CTDBRET_CNDXFALSE	= 4071,	/* Cond. expr evaluates to false		*/
	CTDBRET_CNDXSYNTAX	= 4072, /* conditional expr. parser error		*/
	CTDBRET_CNDXTYPE	= 4073, /* Invalid type mixup 				*/
	CTDBRET_CNDXFIELD	= 4074, /* Unknown field name 				*/
	CTDBRET_CNDXINTERNAL 	= 4075, /* Internal yacc error 				*/
	CTDBRET_CNDXMEMORY	= 4076, /* Memory allocation failed 			*/
	CTDBRET_CNDXOVERFLOW 	= 4077, /* Stack overflow 				*/
	CTDBRET_CNDXUNDERFLOW 	= 4078,/* Stack Underflow 				*/
	CTDBRET_CNDXEXEC	= 4079, /* Invalid execution node 			*/
	CTDBRET_CNDXDIVISION	= 4080, /* Division by zero 				*/
	CTDBRET_CNDXNOSCHEMA 	= 4081, /* No record schema				*/
	CTDBRET_CNDXNORECBUF 	= 4082,	/* no record buffer				*/
	CTDBRET_CNDXSDAT	= 4083,	/* not enough data 				*/
#endif /* CTDB_CNDX_IDX  */
	CTDBRET_INVSESSIONTYPE	= 4084, /* invalid session type				*/
	CTDBRET_INVALTERACTION	= 4085,  /* invalid alter table action			*/
	CTDBRET_DIFFERENT 	= 4086,	/* records are different			*/
	CTDBRET_INVOPERATOR	= 4087,	/* invalid operator				*/
	CTDBRET_READONLY	= 4088,	/* table was open read only			*/
	CTDBRET_NOTIMPLEMENTED	= 4089, /* CALLBACK not implemented			*/
	CTDBRET_INVHANDLE	= 4090,	/* Invalid handle type				*/
	CTDBRET_INVCALLBACK	= 4091,	/* Invalid callback type			*/
	CTDBRET_CANTMOVE	= 4092,	/* Can't move segment				*/
	CTDBRET_INDEXDUPNAME	= 4093,	/* index name duplicated in database		*/
	CTDBRET_NOSUCHDATABASE	= 4094,/* database does not exit or not found		*/
	CTDBRET_NOSEGMENT	= 4095,	/* index has no segments			*/
	CTDBRET_BATCHNOTACTIVE	= 4096, /* batch operation not active			*/
	CTDBRET_BATCHISACTIVE	= 4097, /* batch operation is already active 		*/
	CTDBRET_INVBATCHMODE	= 4098,/* invalid batch mode				*/
	CTDBRET_NOTRESOURCE	= 4099,	/* Not a resource handle			*/
	CTDBRET_INVATTACH	= 4100,	/* Invalid session attach mode			*/
	CTDBRET_NOTATTACHED	= 4101,	/* Session not attached				*/
	CTDBRET_BINARYLENGTH	= 4102,/* Invalid binary field length			*/
	CTDBRET_ROUTERERROR	= 4103,	/* Router table error				*/
	CTDBRET_INVROUTERNAME	= 4104, /* invalid router table name			*/
	CTDBRET_INVROUTERNBR	= 4105, /* invalid number of fields in router 		*/
	CTDBRET_INVROUNTERMAP	= 4106, /* invalid router field mapping			*/
	CTDBRET_DBNOTSQL 	= 4107, /* the database is not SQL 			*/
	CTDBRET_INVBUFFER 	= 4108, /* the record buffer contains data causing field offset calculation going after the record size*/
	CTDBRET_CALLBACK_1 	= 4109, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_2 	= 4110, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_3 	= 4111, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_4 	= 4112, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_5 	= 4113, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_6 	= 4114, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_7 	= 4115, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_8 	= 4116, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_9 	= 4117, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_10 	= 4118, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_11 	= 4119, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_12 	= 4120, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_13 	= 4121, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_14 	= 4122, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_15 	= 4123, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_16 	= 4124, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_17 	= 4125, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_18 	= 4126, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_19 	= 4127, /* user error codes reserved to callback functions */
	CTDBRET_CALLBACK_20 	= 4128, /* user error codes reserved to callback functions */
	CTDBRET_CANTCHKUID  	= 4129, /* cannot properly check/update dictionary UID */ 
	CTDBRET_NOMOREVTRES 	= 4130, /* No more RESOURCE for vtable available on parent table */
	CTDBRET_VTABLEEXIST  	= 4131, /* The table has VTables defined in the dictionary */
	CTDBRET_VTABLETYPE  	= 4132, /* The VTable type in the dictionary mistmatches the one in the resource */
	CTDBRET_IDENTITYDEFINED = 4133, /* An Identity field has been already defined 	*/
	CTDBRET_NOIDENTITYDEFINED = 4134, /* An Identity field has not been defined 	*/
	CTDBRET_FLDISNULL 	= 4135, /* Field is null 				*/
	CTDBRET_RESERVEDNAME 	= 4136, /* Invalid use of reserved name 		*/
	CTDBRET_NOTSUP_IN_DICT 	= 4137, /* Feature not supported in Dictionary 		*/
	CTDBRET_INVFILENAME 	= 4138, /* Invalid file name */
	CTDBRET_ISVFIELD 	= 4139, /* operation not supported on Virtual field 	*/
	CTDBRET_HASVFIELD 	= 4140, /* operation not supported on tables with Virtual fields */
	CTDBRET_MISSINGVCLEAR 	= 4141, /* cannot add VFields without setting vclear function */
	CTDBRET_MISSINGVGET 	= 4142, /* Attempting a getfield operation on VField without having a "get" function */
	CTDBRET_MISSINGVSET 	= 4143, /* Attempting a setfield operation on VField without having a "set" function */
	CTDBRET_INVNUMBLEN 	= 4144,  /* CTNUMBER has invalid length 		*/
	CTDBRET_INVMILLISECOND 	= 4145, /* Invalid millisecond         			*/
	CTDBRET_INVLEGACYSEGMENT = 4146, /* Unable to compute legacy segment offset. 	*/
	CTDBRET_MSEC_NOTSUPPORTED = 4147, /* Millisecond precision not supported by c-tree data type in use */
	CTDBRET_PARTITION_DEFINED = 4148, /* file partition already defined */
	CTDBRET_NOTFTI	= 4149, /* Not a Full Text Index handle */
	CTDBRET_NOSUCHFTI = 4150, /* Unknown Full Text Index number or name*/
	CTDBRET_NOFTI	= 4151, /* Table has no Full Text Index */
	CTDBRET_FTI_NOFIELD	= 4152, /* Full Text Index defined with no associated field */
	CTDBRET_CANTATTACH = 4153, /* cannot attach (table handle linked to db not supported) */
	CTDBRET_NOMOREBATCHES = 4154, /*no room for more batches in the session*/
	CTDBRET_ISVTABLE = 4155,  /* operation not supported on VTABLES*/
	CTDBRET_FTS_SYNTAX = 4156, /* Full Text Search found a syntax error in the search query */
	CTDBRET_FTS_TOK_INIT = 4157, /* Full Text Search could not initialize the query tokenizer */
	CTDBRET_FTS_INVALID_STOP_LIST = 4158, /* An invalid stop list entry was specified */
	CTDBRET_FTS_RESERVED2 = 4159,
	CTDBRET_FTS_RESERVED3 = 4160,
	CTDBRET_ROWIDSEG = 4161,  /* attempt to create an index with rowid reference on table with no rowid support */
	CTDBRET_NOTFTID = 4162, /* Not a Full Text Index Dictionary handle */
	CTDBRET_CANNOTSET = 4163, /* FTI option cannot be set */
	CTDBRET_INVMRT_RECSIZ = 4164, /* MRT VTABLE record definition does not describe the entire fixed record portion of the parent table */
	CTDBRET_NOLOAD = 4165, /* background load thread not active for the current file */
	CTDBRET_LOADISACTIVE = 4166, /* background load thread is active for the current file */
	CTDBRET_NO_PATHS = 4167, /* transaction log files path or temporary path not set for standalone model */
	CTDBRET_FIXJSON = 4168, /* JSON field cannot reside in fixed record portion */
	CTDBRET_FIELDMASKFORBID = 4169, /* operation forbidden by field mask */
	CTDBRET_ALREADYSET = 4170, /* Filter already set, cannot be reset */
	CTDBRET_PREC_OVERFLOW = 4171, /* the value fits into the "C" type but overflows the defined precision */
	CTDBRET_FIELDATTRNOTSET = 4172 /* Field attribute not set */

/**************************************************************************************/
/* REMEMBER TO UPDATE ctreeSDK\ctreeAPI\ctree\sql\lib\dherrors file in the 21XXX area */
/* and to run dherr2.c in order to regen dherrors.h to be copied in ctree\include     */
/**************************************************************************************/
} CTDBRET;
/*^****************************************************************************\
*
*   CTDB C API return codes matching SQL error codes that may be returned during
*                           sqllink/unlink operations
*
\******************************************************************************/
/* SQL errors */
#define CTDB_ERR_FLDCNTHI -20050
#define CTDB_ERR_IDXCNTHI -20051
#define CTDB_ERR_ID_OVFLOW -20248

/*^****************************************************************************\
*
*   CTDB C API partition admin modes
*
\******************************************************************************/
typedef enum
{
	CTPART_PURGE		= ptADMINpurge,
	CTPART_ADD			= ptADMINadd,
	CTPART_ARCHIVE		= ptADMINarchive,
	CTPART_BASE			= ptADMINbase,
	CTPART_NUMBER		= ptADMINnumber,
	CTPART_REUSE		= ptADMINreuse,
	CTPART_ACTIVATE		= ptADMINactivate,
	CTPART_STATUS		= ptADMINstatus,
	CTPART_MULTI		= ptADMINmulti,
	CTPART_BASE_RAW		= ptADMINraw|ptADMINbase
} CTPART_MODE_E;

/*^****************************************************************************\
*
*   Support for 64 bit integers
*
*	c-tree headers define the ctN8 macro when the environment supports
*	native 64 bit integers. When that support doesn't exist, c-tree
*	simulates 64 bit integers using an array of two 32 bit unsigned
*	integers. Here we use c-tree's 64-bit integer data types and macros
*	to access those data types.
*
\******************************************************************************/

/* c-treeDB's signed 64-bit integer data type */
typedef LONG8	CTINT64, ctMEM* pCTINT64;

/* c-treeDB's unsigned 64-bit integer data type */
typedef ULONG8	CTUINT64, ctMEM* pCTUINT64;

#ifdef ctN8
/* combine a 32-bit high word value and a 32-bit low word value into a 64-bit integer value */
#define ctdbMAKE64(x,lo,hi)	((x) = (CTUINT64) ctMAKE64(hi,lo))
#else
/* combine a 32-bit high word value and a 32-bit low word value into a 64-bit integer value */
#define ctdbMAKE64(x,lo,hi)	(CTUINT64) ctMAKE64(x,hi,lo)
#endif

/* get the 32-bit low word value from the specified 64-bit integer value */
#define ctdbGETLOW(x)		(ULONG) ctGETLW64(x)

/* get the 32-bit high word value from the specified 64-bit integer value */
#define ctdbGETHGH(x)		(ULONG) ctGETHW64(x)

/* set the specified 64-bit integer value to zero */
#define ctdbZERO64(x)		ctZERO64(x)

/* check if the specified 64-bit integer value is zero */
#define ctdbISZERO64(x)		ctISZERO64(x)

/* get the address of the specified 64-bit integer expression */
#define ctdbPTR64(x)		ctPTR64(x)

/* assign the specified 64-bit integer value to the specified 64-bit integer variable */
#define ctdbCOPY64(x,y)		ctCOPY64(x,y)

/*^****************************************************************************\
*
*   CTDB Field types
*
*	Other field types, as already defined by c-tree are:
*
*	CT_BOOL			1 byte boolean value
*	CT_DATE			4 bytes date field
*	CT_TIME			4 bytes time field
*	CT_MONEY		4 bytes currency value with 2 decimal places
*	CT_BIGINT		8 bytes signed integer
*	CT_CURRENCY		8 bytes currency value with 4 decimal places
*	CT_NUMBER		17 bytes scaled BCD number
*
\******************************************************************************/
#define CT_TINYINT      CT_CHAR			/* 1 byte signed integer			*/
#define CT_UTINYINT     CT_CHARU		/* 1 byte unsigned integer			*/
#define CT_SMALLINT     CT_INT2			/* 2 bytes signed integer			*/
#define CT_USMALLINT    CT_INT2U		/* 2 bytes unsigned integer			*/
#define CT_INTEGER      CT_INT4			/* 4 bytes signed integer			*/
#define CT_UINTEGER     CT_INT4U		/* 4 bytes unsigned integer			*/
#define CT_BIGINT		CT_INT8			/* 8 bytes signed integer			*/
#define CT_UBIGINT		CT_INT8U		/* 8 bytes unsigned integer			*/
#define CT_FLOAT        CT_SFLOAT		/* 4 bytes floating point number	*/
#define CT_DOUBLE       CT_DFLOAT		/* 8 bytes floating point number	*/
#define CT_TIMESTAMP    CT_TIMES		/* 8 bytes time stamp 				*/
#define CT_BINARY       CT_F2STRING		/* fixed length binary data			*/
#define CT_CHARS        CT_FSTRING		/* fixed length character data		*/
#define CT_VARCHAR      CT_STRING		/* variable length character data	*/
#define CT_LVC     		CT_STRING		/* SQL long var char type			*/
#define CT_VARBINARY    CT_2STRING		/* variable length binary data		*/
#define CT_LVB   		CT_4STRING		/* SQL long var binary type			*/
#define CT_NCHAR		CT_F2UNICODE	/* fixed length UNICODE char data	*/ 
#define CT_NVARCHAR		CT_2UNICODE		/* variable length UNICODE char data	*/      
/*^****************************************************************************\
*
*   CTDB C API types
*
\******************************************************************************/
typedef NINT    CTBOOL, ctMEM *pCTBOOL;
typedef ULONG   CTUNSIGNED, ctMEM *pCTUNSIGNED;
typedef LONG    CTSIGNED, ctMEM *pCTSIGNED;
typedef ULONG   CTDATE, ctMEM *pCTDATE;
typedef ULONG   CTTIME, ctMEM *pCTTIME;
typedef ULONG   CTTIMEMS, ctMEM *pCTTIMEMS;
typedef LONG	CTMONEY, ctMEM *pCTMONEY;
#ifndef DOUBLE
#define DOUBLE double
#endif
typedef DOUBLE  CTFLOAT, ctMEM *pCTFLOAT;
typedef DOUBLE  CTDATETIME, ctMEM *pCTDATETIME;
typedef pTEXT   CTSTRING, ctMEM *pCTSTRING;
typedef pTEXT   CTJSON, ctMEM *pCTJSON;
typedef struct tagCTBLOB CTBLOB, ctMEM* pCTBLOB;
typedef NINT	CTDBTYPE, ctMEM* pCTDBTYPE;
typedef CTINT64	CTBIGINT, ctMEM* pCTBIGINT, ctMEM* ctMEM* ppCTBIGINT;
typedef CTUINT64 CTUBIGINT, ctMEM* pCTUBIGINT, ctMEM* ctMEM* ppCTUBIGINT;
typedef CTINT64	CTCURRENCY, ctMEM* pCTCURRENCY, ctMEM* ctMEM* ppCTCURRENCY;
typedef struct tagCTNUMBER CTNUMBER, ctMEM* pCTNUMBER, ctMEM* ctMEM* ppCTNUMBER;
/*^****************************************************************************\
*
*   CTDB C CTOFFSET and CTROWID types
*
\******************************************************************************/
typedef CTINT64		CTOFFSET, ctMEM *pCTOFFSET;
typedef CTINT64		CTROWID, ctMEM* pCTROWID;

/*^****************************************************************************\
*
*   CTDB c-tree MODEL types
*
\******************************************************************************/
typedef enum
{
	CTLIB_SINGLE    = 0x0001,  /* single user            */
	CTLIB_MUSER     = 0x0002,  /* multi user             */
	CTLIB_CLIENT    = 0x0004,  /* client                 */
	CTLIB_LOCLIB    = 0x0008,  /* loclib                 */
	CTLIB_SERVER    = 0x0010,  /* server side library    */
	CTLIB_THREA     = 0x0020,  /* multi thread           */
	CTLIB_TRAN      = 0x0040,  /* transaction processing */
	CTLIB_HUGE      = 0x0080  /* huge file support      */
} CTLIBTYPE_E;

typedef ULONG CTLIB_TYPE;
/*^****************************************************************************\
*
*   Handle types
*
\******************************************************************************/
typedef pVOID CTHANDLE;
typedef ppVOID pCTHANDLE;
typedef struct tagCTDBSESSION   CTDBSESSION, ctMEM *pCTDBSESSION, ctMEM * ctMEM *ppCTDBSESSION;
typedef struct tagCTDBDATABASE  CTDBDATABASE, ctMEM *pCTDBDATABASE, ctMEM * ctMEM * ppCTDBDATABASE;
typedef struct tagCTDBTABLE     CTDBTABLE, ctMEM *pCTDBTABLE, ctMEM * ctMEM *ppCTDBTABLE;
typedef struct tagCTDBICTX		CTDBICTX, ctMEM* pCTDBICTX, ctMEM* ctMEM* ppCTDBICTX;
typedef struct tagCTDBICON		CTDBICON, ctMEM *pCTDBICON, ctMEM* ctMEM* ppCTDBICON;
typedef struct tagCTDBDATA      CTDBDATA, ctMEM *pCTDBDATA, ctMEM * ctMEM *ppCTDBDATA;
typedef struct tagCTDBRECORD    CTDBRECORD, ctMEM *pCTDBRECORD, ctMEM * ctMEM *ppCTDBRECORD;
typedef struct tagCTDBINDEX     CTDBINDEX, ctMEM *pCTDBINDEX, ctMEM * ctMEM *ppCTDBINDEX;
typedef struct tagCTDBFIELD     CTDBFIELD, ctMEM *pCTDBFIELD, ctMEM * ctMEM *ppCTDBFIELD;
typedef struct tagCTDBISEG      CTDBISEG, ctMEM *pCTDBISEG, ctMEM * ctMEM *ppCTDBISEG;
typedef struct tagCTDBDICT      CTDBDICT, ctMEM *pCTDBDICT, ctMEM * ctMEM *ppCTDBDICT;
typedef struct tagCTDBLIST		ctMEM *pCTDBLIST, ctMEM * ctMEM *ppCTDBLIST;
typedef struct tagCTDBSUPER		ctMEM* pCTDBSUPER, ctMEM* ctMEM* ppCTDBSUPER;
typedef struct tagCTDBRESOURCE	CTDBRESOURCE, ctMEM* pCTDBRESOURCE, ctMEM* ctMEM* ppCTDBRESOURCE;
#ifdef CTDB_ROUTER
typedef struct tagCTDBROUTER	CTDBROUTER, ctMEM* pCTDBROUTER, ctMEM* ctMEM* ppCTDBROUTER;
#endif
typedef struct tagCTDBLOCCRI	CTDBLOCCRI, ctMEM* pCTDBLOCCRI, ctMEM* ctMEM* ppCTDBLOCCRI;
typedef struct tagCTDBVTABLEINFO	CTDBVTABLEINFO, ctMEM* pCTDBVTABLEINFO, ctMEM* ctMEM* ppCTDBVTABLEINFO;
typedef struct tagCTDBMRTTABLE	CTDBMRTTABLE, ctMEM* pCTDBMRTTABLE, ctMEM* ctMEM* ppCTDBMRTTABLE;
#ifdef CTDB_EXPR_EVAL
typedef struct tagCTDBEXPR      CTDBEXPR, ctMEM* pCTDBEXPR, ctMEM* ctMEM* ppCTDBEXPR;
#endif
typedef struct tagCTDBRESULTSETCRI  CTDBRESULTSETCRI, ctMEM* pCTDBRESULTSETCRI, ctMEM* ctMEM* ppCTDBRESULTSETCRI;
typedef struct tagCTDBRESULTSET     CTDBRESULTSET, ctMEM* pCTDBRESULTSET, ctMEM* ctMEM* ppCTDBRESULTSET;
typedef struct tagCTDBFTI        CTDBFTI, ctMEM *pCTDBFTI, ctMEM * ctMEM *ppCTDBFTI;
typedef struct tagCTDBFTIFLD   CTDBFTIFLD, ctMEM *pCTDBFTIFLD, ctMEM * ctMEM *ppCTDBFTIFLD;
typedef struct tagCTDBFTIDICT  CTDBFTIDICT, ctMEM *pCTDBFTIDICT, ctMEM * ctMEM *ppCTDBFTIDICT;

/*^****************************************************************************\
*
*   Callback function type
*
\******************************************************************************/
#ifdef CTDB_CALLBACK
typedef CTDBRET (ctdbDECL* ctdbCallbackFunc)(CTHANDLE Handle);
typedef pVOID (ctdbDECL* ctdbAllocFunc)(VRLEN size);
typedef void (ctdbDECL* ctdbFreeFunc)(pVOID ptr);
typedef UINT (*ctdbAlignFunc)(UINT alignment, UINT fkind, pVOID fadr);
typedef CTDBRET (ctdbDECL* ctsqlCallbackFunc)(CTHANDLE Handle, pTEXT cfgFileName);
typedef CTDBRET (ctdbDECL* ctsqlCallbackLoadedFunc)(COUNT type, pVOID ptr);
typedef CTDBRET (ctdbDECL* ctdbFldCallbackFunc)(CTHANDLE Handle, pVOID buffer, pVRLEN size, CTDB_FIELD_METATYPE rtype);
#endif

#ifdef CTDB_VFIELDS
typedef VOID (ctdbDECL* ctdbClearVfieldsFunc)(CTHANDLE Handle);
#else /*CTDB_VFIELDS*/
#define ctdbClearVfieldsFunc pVOID
#endif /*CTDB_VFIELDS*/


/*^****************************************************************************\
*
*   User Defined Function type
*
\******************************************************************************/
typedef VOID (ctdbDECL* ctdbUDFFunc)( ppVOID args, pVOID retval );

/*^****************************************************************************\
*
*   dictionary merge API
*
\******************************************************************************/
#ifdef CTDB_DICTMERGE_API
typedef VOID (ctdbDECL*logFunPtr) (NINT lvl, pTEXT mesg, CTDBRET error, pTEXT extra);
typedef CTDBRET (ctdbDECL *mergeFunPtr) (pCTDBLIST src_list, pCTDBLIST dst_list);

#define DIFF_NONE 0 /*no action yet for this entry */
#define DIFF_DST_KEEP 1 /*keep the dest record as it is */
#define DIFF_DST_REMOVE 2 /* remove the dest record */
#define DIFF_DST_REWRITE 3 /* replace the dest record on disk with the one in the list (in case we merge only some information)  CANNOT CHANGE THE UID*/
#define DIFF_SRC_IGNORE 4 /* ignore the record in the source list (we do not want it or we merge only some info) */
#define DIFF_SRC_COPY2DST 5 /* copy the record to the destination */

#define MERGE_LOG_ERR_1 1
#define MERGE_LOG_ERR_2 2
#define MERGE_LOG_ERR_3 3

#endif

/*^****************************************************************************\
*
*   CTNUMBER
*   CTDB NUMERIC data definition
*
\******************************************************************************/
#define CTNUMBER_SIZE			16

struct tagCTNUMBER
{
	COUNT	dec_num;	/* number of valid bytes in dec_digits */
	UTEXT	dec_digits[CTNUMBER_SIZE + 1];
};
/*^****************************************************************************\
*
*   CTBLOB
*   CTDB C API BLOB structure
*
\******************************************************************************/
struct tagCTBLOB
{
    VRLEN   size;               /* blob data size in bytes                  */
    pUTEXT  data;               /* data buffer                              */
    VRLEN	allocated;			/* allocated size of blob in bytes			*/
};
/*^****************************************************************************\
*
*   CTDBRESOURCE
*   CTDB C API Resource handling structure
*
\******************************************************************************/
#define CTDB_ASSIGN_RESOURCE_NUMBER	(ULONG)(0xffffffff)

struct tagCTDBRESOURCE
{
	UCOUNT	handle_id;
	CTHANDLE hTable;
	ULONG	type;
	ULONG	number;
	pTEXT	name;
	VRLEN	size;
	pVOID	data;
	CTBOOL	locked;
	CTOFFSET recbyt;
};

/*^****************************************************************************\
*
*   CTDB VTABLE RES
*   CTDB C API VTABLE Resource count callback structure
*
\******************************************************************************/

typedef enum
{
	VTABLE_UNDEFINED = 0,
	VTABLE_MRT = 0x00010000 /*_DICT_TYPE_VTABLE_MRT*/
} VTABLE_TYPE;

struct tagVTABLEOBJ
{
	UCOUNT id;
	VTABLE_TYPE type;
	pTEXT name;
};

struct tagCTDBVTABLEINFO
{
	pCTDBTABLE hTable;
	struct tagVTABLEOBJ *data;
	UCOUNT data_elements;
	UCOUNT actual_elements;
};

typedef enum
{
	MRT_IDX_INVALID	= -1,
	MRT_IDX_SET = 0,
	MRT_IDX_RNG = 1
} MRT_IDX_METHOD;

struct tagCTDBMRTTABLE
{
	pTEXT		VTableName;	/* VTable name */
	pConvMap	schema0;	/* c-tree ConvMap structure for main DODA */
	pTEXT		names0 ;	/* c-tree names for main DODA */
	pTEXT		MRTfltr;	/* MultiRecordTypesTable filter text */
	pVOID		MRTfilter_tree;	/* pre-parsed tree */
	NINT		defidx;	/* default index to use to help with filtering */
	pVOID		min;	/* lower bound key */
	pVOID		max;	/* upper bound key */
	VRLEN		minlen; /* lower bound key length */
	VRLEN		maxlen; /* upper bound key length */
	MRT_IDX_METHOD		method;
};

/*^****************************************************************************\
*
*   CTDB file extension handling
*   this enum contains valid values for the file name extention pesence checking.
*
\******************************************************************************/
typedef enum
{
	EXT_DETECT = 0, /* backward compatible behavior with no CTDB_FILEXT */
	/* the following affect:
	   ctdbOpen when handle is session based,
	   ctdbAddTable,
	   ctdbAddTableXtd 
	 */
	EXT_PRESENT = 1, /* filenames contain file extension */
	EXT_MISSING = 2, /* filenames do not contain file extension */
	/* the following affect ctdbAddTableXtd */
	EXT_PRESENT_L = 3, /* logical filename contains file extension physical does not*/
	EXT_PRESENT_P = 4 /* physical filename contains file extension logical does not*/
} EXT_INFO;

#ifdef	CTDB_FILEXT
#define CTDB_DEF_EXTHINT EXT_DETECT
#endif

/* drop/delete behavior */
#define DROPDEL_STRICT 0
#define DROPDEL_LAZY 1

/*^****************************************************************************\
*
*   CTDBFIELD
*   CTDB C API Field handle structure
*
\******************************************************************************/
struct tagCTDBFIELD
{
    UCOUNT      handle_id;      /* Field handle type                        */
    CTHANDLE    pTable;         /* Table handle                             */
    pTEXT       name;           /* Field name                               */
    pDATOBJ     dodaptr;		/* Field DODA entry							*/
    CTDBTYPE    ftype;          /* Field type                               */
    VRLEN       flen;           /* Field length                             */
    ULONG       flags;			/* Field change flags						*/
    NINT        fldno;			/* field number								*/
    pCTDBLIST   pSegments;		/* index segments that reference this field	*/
    pVOID       usertag;		/* user tag									*/
    CTBOOL		nonull;			/* field null flag: YES nul not allowed		*/
    UCOUNT		fprec;			/* field precision							*/
    COUNT		fscale;			/* field scale								*/
#ifdef CTDB_DEFAULT_VALUE
    pTEXT		defvalue;		/* field default value stored as string		*/
    VRLEN		deflength;		/* length of defvalue						*/
    CTDEF_TYPE	defflag;		/* indicate if default value is set and how */
    CTDATE_TYPE defdate;        /* default value date format: CTDATE_MDCY	*/
    CTTIME_TYPE deftime;        /* default value time format: CTTIME_HMS	*/	
#endif /* CTDB_DEFAULT_VALUE */
    CTDB_BINARY_FLAG binflag;	/* field binary flag						*/
#ifdef CTDB_CALLBACK
    ctdbFldCallbackFunc callback[CTDB_FIELD_LAST_CALLBACK];
#endif
#ifdef CTDB_VFIELDS
    pVOID		virt_info;      /* virtual field information */
#endif
    ULONG namehash; /* hash for file name */
#ifdef ctFeatAUTOSYSTIME
    TEXT autosystime;
#endif
#ifdef CTDB_TBLATTR
    pCTDBLIST attributes; /* list of pCTDBFIELDATTR */
#endif
};
/*^****************************************************************************\
*
*   CTDBISEG
*   CTDB C API Index segment structure
*
\******************************************************************************/
struct tagCTDBISEG
{
	UCOUNT		handle_id;		/* Segment handle type                      */
	CTHANDLE	pIndex;         /* Index handle                             */
	CTHANDLE	field;          /* field handle for the segment             */
	pISEG		isegptr;		/* IFIL IIDX ISEG pointer					*/
	NINT		offset;			/* absolute byte offset or field number		*/
	NINT		length;			/* segment length in bytes					*/
	CTSEG_MODE  mode;       	/* segment mode                             */
	ULONG		flags;			/* Segment change flags						*/
	pVOID		usertag;		/* user tag									*/
	ctKSEGDEF	kseg;			/* extended segment info					*/
	CTBOOL		kseg_used;		/* indicate if kseg was set or not			*/
	CTBOOL		kseg_changed;	/* indicate if kseg was changed				*/
	pTEXT		kseg_long_desc;	/* when ctFeatKSEGDEFxtd is on the content of kseg.kseg_desc may be larger than its size...*/
};
/*^****************************************************************************\
*
*   CTDBINDEX
*   CTDB C API Index handle structure
*
\******************************************************************************/
struct tagCTDBINDEX
{
	UCOUNT		handle_id;		/* Index handle type                        */
	CTHANDLE    pTable;     	/* Table handle                             */
	pCTDBLIST	segments;		/* Index segments							*/
	pIIDX		idxptr;			/* Pointer to IFIL IIDX entry				*/
	VRLEN       key_length; 	/* Key length                               */
	CTDBKEY     key_type;   	/* key type                                 */
	NINT        emptchar;   	/* empty character                          */
	CTBOOL      allow_duplicates;/* duplicate flag                          */
	CTBOOL      nullflag;       /* nul key flag                             */
	CTBOOL      is_temporary;   /* is this index a temporary index?         */
	pTEXT		ridxnam;		/* Symbolic index name						*/
	pTEXT       aidxnam;        /* Optional index file name                 */
	pCOUNT      altseq;         /* optional alternate sequence              */
	pUTEXT      pvbyte;         /* optional pointer to pad byte             */
	FILNO       idxno;          /* c-tree index number handle               */
	ULONG		flags;			/* Index change flags						*/
	pVOID		usertag;		/* user tag									*/
	ULONG		uid;			/* index uid								*/
#ifdef ctdbUNICODE
	ctKSEGDEF	unicode_kseg;			/* extended segment info for UNICODE		*/
	CTBOOL		unicode_kseg_used;		/* indicate if kseg was set or not			*/
	CTBOOL		unicode_kseg_changed;	/* indicate if kseg was changed				*/
#endif
	CTBOOL		distinct_count;	/* use c-tree dup. index distinct key count	*/
#ifdef CTDB_CNDX_IDX 
#ifdef 	CTDB_DEFER_CNDX_IDX
	CTBOOL		cndx_set;
#endif
	pTEXT		cndxExpr;		/* conditional expression	                */
#endif
};
/*^****************************************************************************\
*
*   CTDBDATA
*   CTDB C API field data structure
*
\******************************************************************************/
struct tagCTDBDATA
{
    VRLEN       number;         /* field number                             */
    VRLEN       bitnum;         /* nul flag bit number                      */
    pCTDBFIELD  field;          /* pointer to field handle                  */
    CTDBTYPE    ftype;          /* field type                               */
    pUTEXT      faddr;          /* field address in record buffer           */
    pUTEXT      fdata;          /* field data address                       */
    VRLEN       flen;           /* field defined length                     */
    VRLEN       fsize;          /* field actual data size                   */
    CTBOOL      isalloc;        /* indicates if fdata was allocated         */
    VRLEN       offset;         /* offset from DODA                         */
    CTBOOL      changed;        /* indicate that field has changed          */
    CTBOOL      isseg;          /* field is part of a segment               */
    pCTDBRECORD pRecord;        /* pointer to Record handle                 */
};
/*^****************************************************************************\
*
*   CTDBRECORD
*   CTDB C API Record handle structure
*
\******************************************************************************/
struct tagCTDBRECORD
{
    UCOUNT      handle_id;      /* Cursor handle type                       */
    pCTDBSESSION pSession;      /* Session handle                           */
    pCTDBDATABASE pDatabase;    /* Database handle                          */
    pCTDBTABLE  pTable;         /* Table handle                             */
    pUTEXT      recbuf;         /* Record buffer                            */
    VRLEN       recbuf_size;    /* size of allocated record buffer          */
    VRLEN       recbuf_len;     /* length of the record                     */
    VRLEN       fixrec_len;     /* fixed record length                      */
    CTOFFSET    recbyt;      	/* record offset                            */
    CTBOOL      is_new;         /* indicates a clear or new record buffer   */
    CTBOOL      has_changed;    /* record was modified                      */
    NINT		context;        /* c-tree ISAM context                      */
    pCTDBDATA   fields;         /* field data information                   */
    VRLEN       fields_count;   /* number of fields                         */
    VRLEN       version;        /* Record version                           */
    pCTDBDATA   pDelFlag;       /* Pointer to del flag field data           */
    pCTDBDATA   pNullFlag;      /* Pointer to nul flag field data           */
    NINT		idxno;			/* Default index							*/
    CTBOOL		need_resize;	/* Record buffer need resize				*/
    CTBOOL		set_flag;		/* indicates if a set is active or not		*/
    COUNT		set_handle;		/* indicates the set number					*/
    pVOID		set_key;		/* set target key							*/
    COUNT		set_keylen;		/* number of bytes in key					*/
    COUNT		set_keysize;	/* allocated size of set_key in bytes		*/
    NINT		vrlen_fld;		/* first field in variable length region	*/
    pVOID		usertag;		/* user tag									*/
    COUNT		setid;			/* c-tree Plus set number					*/
    CTBOOL		setused;		/* indicates if a set operation performed	*/
    CTRECBUF_MODE recbuf_mode;	/* record buffer mode						*/
    pVOID		keyval;			/* index scan key value buffer				*/
    NINT		keylen;			/* key value buffer size in bytes			*/
    CTBOOL		hasnumberfield;	/* indicate that the record has number field*/
#ifdef CTDB_CNDX_IDX 
    pTEXT		cndx_schema;	/* conditional expression schema			*/
    pTEXT		cndx_names;		/* conditional field names					*/
    pVOID		cndx_tree;		/* conditional execution tree				*/
    pTEXT		cndx_expr;		/* conditional expression					*/		
    LONG		cndx_tfilter;	/* expression type                          */

#endif /* CTDB_CNDX_IDX  */
	CTBOOL		range_flag;		/* flag to indicate if a range is active	*/
	CTBOOL		range_indexonly;	/* flag to indicate index only range (no actual record read) */
	FILNO		range_keyno;	/* keyno used to set the range				*/
#ifdef ctdbRECORD_FILTER
	pTEXT		filterexpr;		/* filter expression or filter parse tree	*/

#ifdef CTDB_REUSE_RECORD_CRI
    pTEXT		orifilterexpr;  /* original filter expression               */
#endif /* ~CTDB_REUSE_RECORD_CRI */

	CTFILTER_TYPE filtertype;	/* filter expression type					*/
#endif /* ~ctdbRECORD_FILTER */
	pCTDBDATA	pRowid;			/* pointer to rowid field data				*/
#ifdef CTDB_CALLBACK
	ctdbCallbackFunc callback[CTDB_ON_LAST_CALLBACK];
	pVOID	localTag;			/* local storage for callback code			*/
#endif
	COUNT		batchnum;		/* batch number. zero means no batch active	*/
	CTBATCH_MODE batch_mode;	/* current batch mode						*/
	LONG		batch_total;	/* total number of record in batch set		*/
	LONG		batch_avail;	/* number of entries locked;				*/
	LONG		batch_count;	/* number of objects in buffer				*/
	NINT		batch_keylen;	/* batch key length							*/
	NINT		batch_keysize;	/* allocated size of key buffer				*/
	pTEXT		batch_key; 		/* batch partial key buffer					*/
	CTOFFSET	batch_offset;	/* keep any offset of batches				*/
	pUTEXT		batch_buffer;	/* buffer for batch operations				*/
	pUTEXT		batch_ptr;		/* pointer to buffer for next operation		*/
	VRLEN		batch_size;		/* allocated size of batch_buffer			*/
	NINT		index_error;	/* number of index that caused error		*/
	pCTDBLIST	locate_cri;		/* locate criteria list						*/
	VRLEN		locate_idx;		/* locate index number for criteria			*/
	VRLEN		beg_hidden;		/* number hidden fields at the beginnig (getdata optimization)*/
#ifdef CTDB_BLKIREC
	CTBOOL		blk_flag;		/* blocking read flag*/
	LONG		blk_timeoutsec;	/* seconds to timeout (0 returns immediately) */
	pTEXT		blk_condition;	/* block condition */
#endif
#ifdef CTDB_RESULT_SET
	CTBOOL		is_rset_active;	/* result set active flag */
	pCTDBRESULTSET pActiveRSet; /* Active result set handle */
#endif
#ifdef CTDB_SUBRECORD
	CTBOOL		subrec_flag;	/* iterate over subrecords */
	NINT		subrec_count;	/* number of subrecords in this record */
	NINT		subrec_current;	/* current subrecord */
#endif
	CTBOOL		FTSearch_flag; /* indicates if a Full Text Search is active or not */
	NINT		FTIno;          /* Default Full Text Index	*/
	CTBOOL		autoid;        /* indicates if identity field value generation should be automatic or not */
#ifdef ctFeatFULLTEXTIDX
	FTSERR		fts_error;		/* Detailed full text search error */
#endif
	pCTDBLIST	fieldmask;
#ifdef ctFeatBATCHEXT
	pTEXT		batch_filter;
	pVOID		batch_rnglk;
	pVOID		batch_rnguk;
	NINT		batch_rngseg;
	pNINT		batch_rngop;
#endif
#ifdef ctFeatAUTOSYSTIME
	pCTDBLIST	autoassinged; /* list of fields that are automatically assigned by the server (excluding identity) */
#endif

};
/*^****************************************************************************\
*
*   CTDBLOCCRI
*   CTDB C API ctree plus record locate criteria handle
*
\******************************************************************************/
struct tagCTDBLOCCRI
{
	pTEXT	fieldName;			/* Criteria field name 						*/
	pTEXT	fieldValue;			/* Criteria field value 					*/
};
/*^****************************************************************************\
*
*   CTDBICON
*   CTDB C API ctree plus context handle
*
\******************************************************************************/
struct tagCTDBICTX
{
	NINT	ctx;				/* c-tree Plus context number 				*/
	NINT	count;				/* record buffers associated with context 	*/
};

struct tagCTDBICON
{
	pCTDBICTX list;				/* list of context associated with table	*/
	NINT	  size;				/* total number of context handles			*/
	NINT	  count;			/* used number of context handles			*/
	NINT	  current;			/* current table context					*/
};
/*^****************************************************************************\
*
*   CTTABLE
*   CTDB C API Table handle structure
*
\******************************************************************************/
struct tagCTDBTABLE
{
    UCOUNT      handle_id;      /* Table handle type                        */
    CTHANDLE    pSession;       /* Session handle                           */
    CTHANDLE    pDatabase;      /* Database handle                          */
    CTBOOL      is_active;      /* Indicates if table is active             */
    pTEXT       logical_name;   /* Table name to operate on the table       */
    pTEXT       physical_name;  /* Table name on disk                       */
    pTEXT       path;           /* Table path                               */
    pTEXT       fext;           /* Table name extension                     */
    pTEXT       iext;           /* Index nbame extension                    */
    pTEXT       password;       /* Table password                           */
    pTEXT       groupid;        /* Table group id                           */
    LONG        permmask;       /* Table permission mask                    */
    pCTDBLIST	indices;		/* Vector of active indices for the table	*/
    pCTDBLIST	fields;			/* Vector of active fields for the table	*/
    FILNO       datno;          /* c-tree data file number                  */
    CTCREATE_MODE create_mode;  /* c-tree data file mode                    */
    CTOPEN_MODE	open_mode;      /* c-tree index file mode                   */
    NINT        dxtdsiz;        /* c-tree data extent size                  */
    NINT        ixtdsiz;        /* c-tree index extent size                 */
    pIFIL       ifilptr;        /* c-tree IFIL                              */
    VRLEN       ifil_size;      /* allocated ifil size                      */
    pDATOBJ     dodaptr;        /* c-tree DODA                              */
    VRLEN       doda_size;      /* allocated doda size                      */
    pConvMap	schemaptr;	    /* c-tree ConvMap structure		            */
    VRLEN	    schema_size;	/* allocated ConvMap size		            */
    pCTDBICON   context;        /* ISAM contexts associated with table      */
    VRLEN       fixreclen;      /* fixed record length                      */
    VRLEN       dodacount;      /* number of fields in doda                 */
    CTBOOL      isvarlen;       /* table has variable length records        */
                                /* 3 pecial marker to set that is a fixed size table (field wise) which length is greater than the maximum fixed size*/
                                /* 4 special marker to set that is a compressed (logically) fixed size table */
                                /* 5 special marker to keep the VLENGTH info on truncate */
    VRLEN       version;        /* table info version number                */
	ULONG		uid;			/* table unique identifier					*/
	pVOID		objptr;			/* C++ object pointer						*/
	pCTDBLIST	records;		/* list of records attached to table		*/
	CTBOOL		has_nulfield;	/* indicates null field support				*/
	pCTDBSUPER	hSuper;			/* Superfile handle							*/
	NINT		noresfld;		/* number of reserved fields				*/
    pVOID		usertag;		/* user tag									*/
    CTSTATE		state;			/* table internal state						*/
    CTBOOL		dirty;			/* table need to be reopened after commit	*/
    CTBOOL		has_recbyt;		/* indicates if table has recbyt index		*/
    NINT		recbyt_ix;		/* recbyt index number						*/
    CTBOOL		has_rowid;		/* indicate if table has rowid index		*/
    NINT		rowid_ix;		/* rowid index number						*/
    NINT		rowid_fld;		/* rowid field number in doda				*/
    NINT		indexcount;		/* number of user indexes					*/
    TEXT		padchar;		/* target key formation padding character	*/
    TEXT		dlmchar;		/* target key formation field delimiter		*/
#ifdef CTDB_FILTER_020617		/* added code to support record filters		*/
	pTEXT		filterexpr;		/* last record filter expression			*/
	CTBOOL		filtered;		/* indicate if filter is active or not		*/
#endif /* CTDB_FILTER_020617 */
	CTBOOL		has_delfield;	/* indicate if table has $DELFLD$ field		*/
#ifdef CTDB_MIRROR
	pTEXT       mirror_name;	/* Mirror Table name                        */
	pTEXT       mirror_path;    /* Mirror Table path                        */
#endif
	CTBOOL		temp_flag;		/* alter table temporary flag on			*/
	NINT		temp_mode;		/* CTDB_TRANMODE or CTDB_PINGMODE			*/
	pCTDBLIST	alterlist;		/* list of alter table info record			*/
#ifdef CTDB_CALLBACK
	CTDB_TABLE_TYPE table_type;	/* indicate the table type					*/
	ctdbCallbackFunc callback[CTDB_ON_LAST_CALLBACK];
	pVOID		localTag;		/* local storage for callback code			*/
	NINT		rebuild_perc;	/* percentage of table rebuild				*/
	CTDBRET		doda_ret;		/* error code after loading DODA			*/
	NINT		alter_action;
#endif
	COUNT		alter_time;
#ifdef CTDB_DEFAULT_VALUE
	NINT		defcount;		/* number of field default value set		*/
#endif /* CTDB_DEFAULT_VALUE */
#ifdef ctdbUNICODE
	ctKSEGDEF	unicode_kseg;			/* extended segment info for UNICODE		*/
	CTBOOL		unicode_kseg_used;		/* indicate if kseg was set or not			*/
	CTBOOL		unicode_kseg_changed;	/* indicate if kseg was changed				*/
#endif
	pTEXT		owner;			/* indicate a table owner. Set before create*/
#ifdef PAOLO_MOVED_TO_SESSION_090611
	COUNT		batch_count;	/* the next available batch number			*/
#endif
#ifdef CTDB_ROUTER
	pCTDBROUTER	router;			/* table routing handle						*/
#endif
#ifdef CTDB_OPEN_WITH_IFIL
	pIFIL		user_ifil;		/* ifil provided by the callback code		*/
#endif
#ifdef CTDB_VTABLES
	UINT		VTableNumber;	/* definition (DODA&IFIL) identifier*/
	VTABLE_TYPE	VTableType; /* type of VTable */	
	pVOID		pVTable; /* pointer to VTable specific structure */
#endif
#ifdef 	CTDB_AUTO_PARTITION
	pCTDBINDEX prtidx; /* partition index */
	LONG callparm; /* number of bits for partition number */
	UCOUNT prtmaxmbr; /* maximum active partition members (for auto purge) */
#endif
#ifdef 	CTDB_IDENTITY
	pTEXT	identity_fld;
	CTINT64		identity_seed;
	CTINT64		identity_incr;
#endif
#ifdef CTDB_EXPR_EVAL
	pCTDBLIST	expr_list;		/* expression list							*/
	pTEXT		cndx_names;		/* field name list used in expression tress	*/
#endif
	pTEXT index_basename;		/* based name for index automatic name generation */
#ifdef CTDB_TEMP_IDX
	pCTDBLIST	temp_indices;	/* Vector of active temporary indices   	*/
#endif
#ifdef CTDB_RESULT_SET
	pCTDBLIST	resultSetList;	/* List of Result Set handles */
#endif
	UINT field_alignment; /* field alignment in effect defaults to ctdbALIGMENT */
#ifdef CTDB_FILEXT
	EXT_INFO ext_hint;
#endif
#ifdef CTDB_VFIELDS
	pCTDBLIST	vfields;	/* Vector of active Virtual fields for the table */
	ctdbClearVfieldsFunc vclear;	/* listClear for vfields */
#endif
	pTEXT partdesc;   /*pointer to a partdesc buffer for dyn partitions */
#ifdef CTDB_AUTO_PARTITION
	pTEXT prtrule; /* partition rule (if any) */
#endif
	pCTDBLIST FTIs; /* Full Text Indices active on the table */
	CTBOOL fldCheck; /* flag used internally to indicate to not perform field name checking during AddField*/
#ifdef CTDB_INTERNAL_pINDEX
	pCTDBINDEX rowididx; /* rowid index information */
	pCTDBINDEX recbytidx; /* recbyt index information */
#endif
#ifdef ctMTFPG
	pVOID dictdata; /* internallly use, do not touch it */
#endif
	UCOUNT dict_mark; /* dictionary mark see _DICT_VERATTR_TBL_* */
};
/*^****************************************************************************\
*
*   CTDBDATABASE
*   CTDB C API Database handle structure
*
\******************************************************************************/
struct tagCTDBDATABASE
{
    UCOUNT      handle_id;      /* Database handle type                     */
    CTHANDLE    pSession;       /* Handle to session                        */
    CTBOOL      is_active;      /* Indicates if database is active          */
    pCTDBDICT   pDict;          /* Dictionary handle                        */
    pTEXT       name;           /* Database name                            */
    pTEXT       path;           /* Database path                            */
	pCTDBLIST	tables;			/* List of active tables for the database	*/
	ULONG		uid;			/* Database unique identifier				*/
	pVOID		objptr;			/* C++ object pointer						*/
    pVOID		usertag;		/* user tag									*/
    pCTDBLIST	indices;		/* database index tuple list				*/
    NINT		counter;		/* database index tuple counter				(*/
#ifdef CTDB_AUTO_SQLIMPORT
    NINT isSQL; /* 0 = no, 1 = SQL, 2 = SQL+FPUTFGET, 4...*/
#endif
	pTEXT		sqlowner;		/* owner of the table in ctreeSQL			*/
	pCTDBLIST	children;		/* table handles linked to this database	*/
#ifdef CTDB_CALLBACK
	ctdbCallbackFunc callback[CTDB_ON_LAST_CALLBACK];
	pVOID		localTag;		/* special tag for callback code			*/
	CTBOOL badrecords;	/* makes function reading records to return only records causing a callback error */
#endif
	CTBOOL		exclusive;		/* indicate if database should be exclusive	*/
#ifdef CTDB_DICTTRANCRTL
	CTBEGIN_MODE dict_tranmode;		/* indicates the transaction mode for the dictionary */
#endif
#ifdef	CTDB_FILEXT
	EXT_INFO ext_hint;
#endif
	TEXT dropdelopt; /* option for drop/del behavior with missing files */
#ifdef CTDB_VTABLES_MRT
	TEXT droplastMRT; /* option to drop/delete the host table on last MRT drop*/
#endif
	CTBOOL dbdict_super; /* dictionary is in a superfile */
#ifdef CTDB_SHARED_DICTADD
	CTBOOL shared_dict_add; /* attempt OPEN_NORMAL when adding to dictionaries */
#endif
};

/* regular SQL marker*/
#define SQLMARK_SQL 1
/* SQL with FPUTFGET storage engine marker */
#define SQLMARK_SQLFPG 2

/*^****************************************************************************\
*
*   SQL Import function pointer prototypes and defines
*
\******************************************************************************/
#define SQLIMP_PRINT_EMSG 0
#define SQLIMP_PRINT_WMSG 1
#define SQLIMP_PRINT_MSG  2
#define SQLIMP_IO_FNC (pVOID)(NLONG) 1 /* pointing to invalid memory as place holder to "default old behavior functions */
#define SQLIMP_CBK_FNC NULL 
#define SQLIMP_REUSE_LOGON (pVOID)(NLONG) 1 /*pointing to invalid memory as place holder to be used as srvnam to indicate reuse of session*/
#define SQLIMP_REUSE_DB (pVOID)(NLONG) 2 /*pointing to invalid memory as place holder to be used as srvnam to indicate reuse of database and session*/

typedef CTBOOL (*SQLCBF)(CTSQLCB_MODE, pTEXT, CTBOOL, pVOID);
typedef CTBOOL (*SQLCBFX)(pVOID, CTSQLCB_MODE, pTEXT, CTBOOL, pVOID);
typedef VOID   (*PRINTFNC)(NINT lvl, pTEXT msg, pVOID tag);
typedef pTEXT  (*GETINPUT)(pTEXT Message, pTEXT Buffer, NINT MaxCount, pVOID tag);

/*^****************************************************************************\
*
*   CTDBSESSION
*   CTDB C API Session handle structure
*
\******************************************************************************/
struct tagCTDBSESSION
{
    UCOUNT      handle_id;      /* Session handle type                      */
    CTBOOL      is_active;      /* indicates of session is active or not    */
    pTEXT       server_name;    /* c-tree server name                       */
    pTEXT       user_name;      /* c-tree user name                         */
#ifdef CTDB_KEEP_PASSWORD
    pTEXT       user_password;  /* c-tree user password                     */
#endif
    pTEXT       session_path;   /* Default session path                     */
    pCTDBDICT   pDict;          /* Dictionary handle                        */
	pCTDBLIST	databases;		/* List of active databases					*/
    NINT        error_code;     /* CTDB C API error code                    */
    CTBOOL      tran_pending;   /* Transaction processing initiated         */
    NINT        bufs;           /* number of buffers for index files        */
    NINT        fils;           /* number of files                          */
    NINT        sect;           /* number of node sectors                   */
    NINT        dbufs;          /* number of buffers for data files         */
    NINT        userprof;       /* user profile mask                        */
    CTDATE_TYPE defdate;        /* default date format: CTDATE_TYPE_MDY     */
    CTTIME_TYPE deftime;        /* default time format: CTTIME_TYPE_HMP     */
    pTEXT		deffloat;		/* default float format for conversion		*/
    pTEXT		ctreeid;		/* ctree plus instance identifier			*/
    NINT		ctreeid_size;	/* ctree plus instance id allocated size	*/
    CTBOOL		logon_only;		/* ctree plus logon only. no dictionaries	*/
    CTBOOL		srvinternal;	/* server side internal calls (for threads not associated with a client connection) */
    pVOID		usertag;		/* user tag									*/
	pCTDBLIST	droplist;		/* list of dropped tables					*/
	COUNT		setid;			/* c-tree Plus set number counter			*/
	CTBOOL		tpidrop;		/* transaction pending index drop			*/
	COUNT		lockmode;		/* current lock mode						*/
	CTTRANISO	isolevel;		/* current transaction isolation level		*/	
#ifdef ctdbMULTITRD
    pVOID       lqmsg_mem;      /* special server logon logic               */
    pVOID       ctusebuf_mem;   /* special server logon logic               */
#endif
	CTSESSION_TYPE sess_type;	/* indicates the session type 				*/
	SQLCBF SQLcallback;
	SQLCBFX SQLcallbackXtd;
	pVOID SQLcallbackCtx;
#ifdef CTDB_AUTO_SQLIMPORT
	CTBOOL isSQL;
#endif
	pCTDBLIST	children;		/* databases handles linked to this session	*/
	CTKEEP_MODE keepmode;		/* transaction locks keep mode				*/
#ifdef CTDB_PATHPREFIX
	pTEXT		path_prefix;	/* path prefix feature						*/
#endif
#ifdef CTDB_CALLBACK
	ctdbCallbackFunc callback[CTDB_ON_LAST_CALLBACK];
	pVOID		localTag;		/* special tag for callback code			*/	
#ifdef CTDB_CALLBACK_LOAD
	ctsqlCallbackFunc RegisterSDK;
	ctsqlCallbackFunc UnRegisterSDK;
	ctsqlCallbackLoadedFunc SDKLoaded;
	pVOID hLib;
	CTBOOL RegisteredSDK;
#endif
#endif
	pCTDBLIST	alterlist;		/* list of table altered during transaction */
#ifdef CTDB_CALLBACK
	ctdbAllocFunc onAlloc;		/* invoke CTDB memory allocation			*/
	ctdbFreeFunc onFree;		/* invoke CTDB free memory					*/
	ctdbAlignFunc onAlign;		/* invoke ctree field alignment 			*/
#endif
	CTBOOL		exclusive;		/* indicate if session should be exclusive	*/
#ifdef MULTITRD
	NINT		m_sessid;
#endif
	CTBEGIN_MODE tranmode;		/* begin transaction mode					*/
	CTBOOL		setops_flag;	/* indicate if setups was called or not		*/
	LONG		setops_mode;	/* current setops mode						*/
	CTATTACH_MODE attached;		/* attached mode							*/
#ifdef CTDB_DICTTRANCRTL
	CTBEGIN_MODE dbdict_tranmode;		/* indicates the transaction mode for the dictionary */
#endif
#ifdef CTDB_BATCH_65536
	COUNT		_batch_count;	/* the next available batch number			*/
	pCTDBLIST	batch_numbers;
#else
	COUNT		batch_count;	/* the next available batch number			*/
#endif
	TEXT		path_sep;		/* the path separator for this session */
	pTEXT     ssl_cert;  /* SSL certificate */
	pTEXT     ssl_debug; /* SSL debug log file */
	CTBOOL    ssl; /* use SSL communication protocobl*/
	CTBOOL    dbdict_super; /* dictionary is in a superfile */
	pTEXT	  logpath; /* transaction logs path for standalone */
	pTEXT	  statuspath; /* status log path for standalone */
	pTEXT	  tmppath; /* temporary files path for standalone */
	pTEXT	  dictname; /* session dictionary name*/
};

#ifdef CTDB_EXPR_EVAL
struct tagCTDBEXPR
{
    pVOID   expr_tree;  /* execution tree   */
    LONG    expr_type;  /* expression type  */
};
#endif /* CTDB_EXPR_EVAL */

/*^****************************************************************************\
*
*   CTDBRESULTSETCRI
*   CTDB C API result set criteria handle
*
\******************************************************************************/
struct tagCTDBRESULTSETCRI
{
    COUNT       handle_id;       /* Result Set Criteria handle type          */
    CTHANDLE    pResulSet;       /* Result Set handle                        */
    CTHANDLE    pField;          /* Field handle                             */
    pTEXT       lowValue;        /* Low criteria field value                 */
    pTEXT       highValue;       /* High criteria field value                */
    COUNT       lowValueBufSiz;  /* Low criteria field value buffer size     */
    COUNT       highValueBufSiz; /* Low criteria field value buffer size     */
    NINT        op;              /* Operator: CTIX_EQ, CTIX_GT, CTIX_GE, etc */
};

/*^****************************************************************************\
*
*   CTDBRESULTSET
*   CTDB C API result set handle
*
\******************************************************************************/
struct tagCTDBRESULTSET
{
    COUNT       handle_id;  /* Result Set handle type                   */
    pTEXT       name;       /* Result set name                          */
    CTHANDLE    pTable;     /* Table handle                             */
    pCTDBLIST   criList;    /* List of criteria                         */
    VRLEN       bestIdxNbr; /* Best index nbr for the criteria list     */
};


/*^****************************************************************************\
*
*   CTDBFTI
*   CTDB C API Full Text Search handle
*
\******************************************************************************/
struct tagCTDBFTIFLD
{
	pTEXT       fldname;           /* Field name                               */
	ULONG mode;
};

struct tagCTDBFTIDICT
{
	UCOUNT      handle_id;	/* FTI handle type */
	CTHANDLE    pSession;	/* Session handle */
	ULONG	    flags;	/* FTID change flags */
	/* from this point FTI options */
	UCOUNT      tokensize;
	UCOUNT      tokenizer;
	pTEXT       tokenparam;
	pTEXT       tokenparam2;
	pTEXT       stoplist;	/* list of stop words */
	pTEXT       dictpath;	/* dictionary file path (null indicates datafile directory) */
	pTEXT       dictname;	/* dictionary file name (null indicates private dictionary) */
	CTBOOL	    superfile;  /* YES = dictionary built as a superfile member, dictname indicates if standalone or in the one of the reference table */
};

struct tagCTDBFTI
{
    UCOUNT      handle_id;     /* FTI handle type                          */
    CTHANDLE    pTable;        /* Table handle                             */
    ULONG       flags;         /* FTI change flags                        */
    pCTDBLIST   FTIfields;        /* Indexed Fields                           */
    pTEXT name;
    pCTDBFTIDICT dictionary;
    UCOUNT options;
    ULONG uid;  /* FTI uid */
    TEXT sfile; /* 0 = no superfile; 1 = superfile per data ; 2 = superfile per index; 3 = datafile superfile*/
    pTEXT resname;
#ifdef CTDB_CNDX_IDX 
    pTEXT   cndxExpr;		/* conditional expression	                */
#endif
};

/* c-treeACE SQL import API function option structure definition */
typedef struct tagCTSQLIMPOPTS {
	pTEXT	tblnam;	/* <table_name>: name of table to import	*/
	pTEXT	symnam;	/* -n <symbolic_name>: symbolic table name	*/
	pTEXT	prefix;	/* -q <prefix>: table name prefix */
	pTEXT	dbsnam;	/* -d <database_name>: name of c-treeACE SQL database (default: ctreeSQL) */
	pTEXT	srvnam;	/* -s <server_name>: c-treeACE SQL Server name (default: FAIRCOMS) */
	pTEXT	usrnam;	/* -u <user_name>: userid for connecting to	c-treeACE SQL Server */
	pTEXT	usrpwd;	/* -a <password>: password for authentication	*/
	pTEXT	tblown;	/* -o <owner>: assign table owner		*/
	pTEXT	prikey;	/* -m <idname>: set 'idxname' as primary key*/
	pTEXT	paddin; /* -f <s|z|sz>: force string padding to (s)paces (z)eroes or (sz)spaces zero terminated */
	SQLCBF	clbkfn;	/* callback function				*/
	NINT	chkfld;	/* -k: skip fields that don't comply with conventional identifier rules */
	NINT	skpidx;	/* -x: skip indices				*/
	NINT	rmlink;	/* -r: unlink table from database		*/
	NINT	frctbl;	/* -c: allow table names that don't comply with	*/
	NINT	grntpb;	/* -b: grant public access permissions	*/
	NINT	nonint; /* -i: non-interactive mode: ignore errors and continue */
	NINT	grntro;	/* -B: grant public read-only access permissions	*/
	NINT	promot;	/* -p: promote unsigned types to greater signed type	*/
	NINT	prmver;	/* -P: promote unsigned types to greater signed type and set check for fitting value */
	NINT	strinz;	/* -z: allow indices with missing string terminator in key segments */
	NINT	lobsiz;	/* -l <size>: specify LONGVAR* field size threshold */
	NINT	ignnam;	/* -g: ignore existing index name in IFIL resource */
	NINT	nintrl;	/* -j: non-interactive relink of existing table*/
#ifdef CTDB_NEW_SQLIMP
	pTEXT	script; /* -w: build script file with CREATE statements. (don't import table) */
	pTEXT	extdef; /* -e: get DODA definitions in XML format from 'xmlfile */
	PRINTFNC print_message; /* ctSQLImportTable print message function*/
	GETINPUT fget_input; /* ctSQLImportTable interactive mode input function */
	pVOID	usertag; /* user tag for print_message and fget_input */
	NINT	dropstrict; /* error out when dropping table if missing in dictionaries */
	CTBOOL	keepextra; /* keep existing permissions and synonym (does not remove nor add them), there is no ctsqlimp switch for this option*/
#endif
} CTSQLIMPOPTS, *pCTSQLIMPOPTS;
#ifdef CTDB_CALLBACK
typedef CTDBRET(ctdbDECL* ctsqlImpSetOptsCallbackFunc)(pCTDBSESSION pSession, pTEXT dbname, pTEXT tblowner, pTEXT tblname, CTSQLIMPOPTS **opts);
#endif
/* structure to populate the inconsistency found between ctdb and SQL 
   internal dictionary */
#define MAX_SQL_DICT_ERRORS  100
typedef struct intDICTERROR {
        pTEXT   tblnam;	   /* <table_name>: name of table with inconsistency	            */
        pTEXT   idxnam;	   /* <index_name>: name of index with inconsistency	            */
        pTEXT   fldnam;	   /* <field_name>: name of field with inconsistency	            */
        LONG    uid;       /* <table_id>: table/index identification	                     */
        LONG    errorcd;   /* <error_code>: error code for the inconsistency found	      */
        pTEXT   errormsg;  /* <error_message>: error messsage for the inconsistency found	*/
} DICTERROR, *pDICTERROR;

/*
** Maximum number of options passed to c-treeACE SQL import API function.
** This value sets the size of the argv array that is initialized in
** ictSQLImportTable().
*/
#define CTSQLIMPMAXOPTS 33

/*^****************************************************************************\
*
*   CTDB C API Session function prototypes
*
\******************************************************************************/
ctdbEXPORT CTHANDLE ctdbDECL ctdbAllocSession(CTSESSION_TYPE SessionType);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAllocSessionXtd(CTSESSION_TYPE SessionType, CTDBRET *status);
ctdbEXPORT VOID ctdbDECL ctdbFreeSession(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbLogon(CTHANDLE Handle, pTEXT dbengine, pTEXT userid, pTEXT password);
ctdbEXPORT CTDBRET ctdbDECL ctdbLogout(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetServerName(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetUserLogonName(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetUserPassword(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetSessionParams(CTHANDLE Handle, CTSESSION_PARAM ParamType);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetSessionParams(CTHANDLE Handle, CTSESSION_PARAM ParamType, NINT value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetSessionSSLParams(CTHANDLE Handle, CTSESSIONSSL_PARAM ParamType, pTEXT value);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsSSLActive(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetSSL(CTHANDLE Handle, CTBOOL flag);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsActiveSession(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetSessionHandle(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetError(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetError(CTHANDLE Handle, CTDBRET ErrorCode);
ctdbEXPORT VOID ctdbDECL ctdbClearError(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsTransActive(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSyncTransactionState(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbBegin(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbPrepareCommit(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbCommit(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbAbort(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbSetSavePoint(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbSetSingleSavePoint(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbRestoreSavePoint(CTHANDLE Handle, int SavePoint);
ctdbEXPORT CTDBRET ctdbDECL ctdbClearSavePoint(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetSessionPath(CTHANDLE Handle, pTEXT Path, VRLEN PathSize);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetSessionPath(CTHANDLE Handle, pTEXT Path);
ctdbEXPORT CTDBRET ctdbDECL ctdbFirstDatabase(CTHANDLE Handle, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
ctdbEXPORT CTDBRET ctdbDECL ctdbNextDatabase(CTHANDLE Handle, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindDatabase(CTHANDLE Handle, pTEXT Name, pTEXT Path, VRLEN PathSize);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindDatabaseByUID(CTHANDLE Handle, ULONG uid, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
ctdbEXPORT CTDBRET ctdbDECL ctdbCreateSession(CTHANDLE Handle, pTEXT dbengine, pTEXT userid, pTEXT password);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFirstActiveDatabase(CTHANDLE Handle, pVRLEN pScanIndex);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetNextActiveDatabase(CTHANDLE Handle, pVRLEN pScanIndex);
ctdbEXPORT CTHANDLE ctdbDECL ctdbFindActiveDatabase(CTHANDLE Handle, pTEXT Name);
ctdbEXPORT CTHANDLE ctdbDECL ctdbFindActiveDatabaseByUID(CTHANDLE Handle, ULONG uid);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDefFloatFormat(CTHANDLE Handle, pTEXT format);
ctdbEXPORT pTEXT ctdbDECL ctdbGetDefFloatFormat(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetLogonOnly(CTHANDLE Handle, CTBOOL flag);
ctdbEXPORT CTBOOL ctdbDECL ctdbGetLogonOnly(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetDatabaseCount(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetUserTag(CTHANDLE Handle, ppVOID tagptr);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetUserTag(CTHANDLE Handle, pVOID tagptr);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsLockActive(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbLock(CTHANDLE Handle, CTLOCK_MODE mode);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnlock(CTHANDLE Handle);
ctdbEXPORT CTLOCK_MODE ctdbDECL ctdbGetLockMode(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTransactionIsolation(CTHANDLE Handle, CTTRANISO isolevel);
ctdbEXPORT CTTRANISO ctdbDECL ctdbGetTransactionIsolation(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetSessionType(CTHANDLE Handle, CTSESSION_TYPE SessionType);
ctdbEXPORT CTSESSION_TYPE ctdbDECL ctdbGetSessionType(CTHANDLE Handle);
ctdbEXPORT CTLIB_TYPE ctdbDECL ctdbGetLibType(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetKeepLock(CTHANDLE Handle, CTKEEP_MODE mode);
ctdbEXPORT CTKEEP_MODE ctdbDECL ctdbGetKeepLock(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetCurrentNodeName(CTHANDLE Handle, pTEXT NodeName);
ctdbEXPORT CTDBRET ctdbDECL ctdbSwitchInstance(CTHANDLE Handle);

#ifdef CTDB_PATHPREFIX
ctdbEXPORT CTDBRET ctdbDECL ctdbSetPathPrefix(CTHANDLE Handle, pTEXT path);
ctdbEXPORT CTDBRET ctdbDECL ctdbClearPathPrefix(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetPathPrefix(CTHANDLE Handle);
#endif

#ifdef CTDB_CALLBACK
ctdbEXPORT NINT ctdbDECL ctdbGetHandleType(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetCallback(CTHANDLE Handle, CTDB_CALLBACK_TYPE CallBackType, ctdbCallbackFunc CallBackFunc);
ctdbEXPORT ctdbCallbackFunc ctdbDECL ctdbGetCallback(CTHANDLE Handle, CTDB_CALLBACK_TYPE CallBackType);
ctdbEXPORT CTDBRET ctdbDECL ctdbClearCallback(CTHANDLE Handle, CTDB_CALLBACK_TYPE CallBackType);
ctdbEXPORT CTDBRET ctdbDECL ctdbClearAllCallback(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetLocalTag(CTHANDLE Handle, pVOID pTag);
ctdbEXPORT pVOID ctdbDECL ctdbGetLocalTag(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldCallback(CTHANDLE Handle, CTDB_FIELD_CALLBACK_TYPE CallBackType, ctdbFldCallbackFunc CallBackFunc);
#endif

ctdbEXPORT CTBOOL ctdbDECL ctdbIsSQLServer(CTHANDLE Handle);
ctdbEXPORT LONG ctdbDECL ctdbGetSystemConfig(NINT index);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetSessionExclusive(CTHANDLE Handle, CTBOOL flag);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsSessionExclusive(CTHANDLE Handle);
ctdbEXPORT CTATTACH_MODE ctdbDECL ctdbGetAttachMode(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbAttachSession(CTHANDLE Handle, CTHANDLE Session, CTATTACH_MODE mode, CTBOOL isTransactionActive);
ctdbEXPORT CTDBRET ctdbDECL ctdbDetachSession(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetConfigurationFile(pTEXT cfgfil);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetLicenseFile(pTEXT licfil);
ctdbEXPORT CTDBRET ctdbDECL ctdbStartDatabaseEngine(VOID);
ctdbEXPORT VOID ctdbDECL ctdbStopDatabaseEngine(VOID);
ctdbEXPORT NINT ctdbDECL ctdbAcquireSessionId(VOID);
ctdbEXPORT VOID ctdbDECL ctdbReleaseSessionId(NINT sessid);
ctdbEXPORT NINT ctdbDECL ctdbGetSessionId(CTHANDLE Handle);
ctdbEXPORT VOID ctdbDECL ctdbSetSessionId(CTHANDLE Handle, NINT sessid);
ctdbEXPORT CTBEGIN_MODE ctdbDECL ctdbGetTransactionMode(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTransactionMode(CTHANDLE Handle, CTBEGIN_MODE mode);
ctdbEXPORT CTOPS_MODE ctdbDECL ctdbGetOperationState(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetOperationState(CTHANDLE Handle, CTOPS_MODE mode, CTOPS_STATE state);
ctdbEXPORT CTBOOL ctdbDECL ctdbGetAutoCommit(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetAutoCommit(CTHANDLE Handle, CTBOOL flag);
ctdbEXPORT VOID ctdbDECL ctdbSetSqlCallBack(CTHANDLE Handle, SQLCBF SQLcallback);
ctdbEXPORT NINT ctdbDECL ctdbGetCtreeOWNER(VOID);
ctdbEXPORT VOID ctdbDECL ctdbSetCtreeOWNER(NINT owner);
ctdbEXPORT CTDBRET ctdbDECL ctdbLoadCallbackLib(CTHANDLE Handle, pTEXT libname, pTEXT inifile, CTBOOL registercallbacks);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnLoadCallbackLib(CTHANDLE Handle, CTBOOL unregonly);
ctdbEXPORT CTDBRET ctdbDECL ctdbBeginImpersonation(CTHANDLE Handle, NINT taskId);
ctdbEXPORT CTDBRET ctdbDECL ctdbEndImpersonation(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetProductName(CTHANDLE Handle, ppTEXT prodName, COUNT bufLen);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetProductVersion(CTHANDLE Handle, ppTEXT prodVersion, COUNT bufLen);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetMaxConnections(CTHANDLE Handle, pLONG maxConn);
ctdbEXPORT CTDATETIME ctdbDECL ctdbServerDateTime(CTHANDLE hSession);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDictTranMode(CTHANDLE Handle, CTBEGIN_MODE tranmode);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetLocalDirectory(pTEXT localdir);

ctdbEXPORT CTDBRET ctdbDECL ctdbSETENCRYPT(pTEXT mod, pTEXT key, VRLEN keylen);
ctdbEXPORT CTDBRET ctdbDECL ctdbSETENCRYPTParam(CTBOOL advEncActive, pTEXT masterKeyFile);

ctdbEXPORT CTDBRET ctdbDECL ctdbSetLogPath(CTHANDLE hSession, pTEXT path);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetStatusLogPath(CTHANDLE hSession, pTEXT path);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTempPath(CTHANDLE hSession, pTEXT path);

/*^****************************************************************************\
*
*   CTDB C API Database function prototypes
*
\******************************************************************************/
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetDatabaseHandle(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAllocDatabase(CTHANDLE Handle);
ctdbEXPORT VOID ctdbDECL ctdbFreeDatabase(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbConnect(CTHANDLE Handle, pTEXT Name);
ctdbEXPORT CTDBRET ctdbDECL ctdbDisconnect(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbDisconnectAll(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbCreateDatabase(CTHANDLE Handle, pTEXT Name, pTEXT Path);
ctdbEXPORT CTDBRET ctdbDECL ctdbAddDatabase(CTHANDLE Handle, pTEXT Name, pTEXT Path);
ctdbEXPORT CTDBRET ctdbDECL ctdbDeleteDatabase(CTHANDLE Handle, pTEXT Name);
ctdbEXPORT CTDBRET ctdbDECL ctdbDropDatabase(CTHANDLE Handle, pTEXT Name);
ctdbEXPORT CTDBRET ctdbDECL ctdbFirstTable(CTHANDLE Handle, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
ctdbEXPORT CTDBRET ctdbDECL ctdbNextTable(CTHANDLE Handle, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindTable(CTHANDLE Handle, pTEXT Name, pTEXT Path, VRLEN PathSize);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindTableByUID(CTHANDLE Handle, ULONG uid, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
ctdbEXPORT CTDBRET ctdbDECL ctdbAddTable(CTHANDLE Handle, pTEXT Name, pTEXT Path);
ctdbEXPORT CTDBRET ctdbDECL ctdbAddTableXtd(CTHANDLE Handle, pTEXT Name, pTEXT PhysicName, pTEXT Path);
ctdbEXPORT CTDBRET ctdbDECL _ctdbAddActiveTable(CTHANDLE Database, CTHANDLE Table);
ctdbEXPORT CTDBRET ctdbDECL ctdbAddMRTTable(pCTDBDATABASE pDatabase, pTEXT Name, pTEXT ParentName, UINT info);
ctdbEXPORT CTDBRET ctdbDECL ctdbDeleteTable(CTHANDLE Handle, pTEXT TableName, pTEXT Password);
ctdbEXPORT CTDBRET ctdbDECL ctdbDropTable(CTHANDLE Handle, pTEXT TableName);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetDatabaseUID(CTHANDLE Handle, pTEXT Name, pULONG puid);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetTableUID(CTHANDLE Handle, pTEXT Name, pULONG puid);
ctdbEXPORT pVOID ctdbDECL ctdbGetDatabaseObjptr(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDatabaseObjptr(CTHANDLE Handle, pVOID ptr);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFirstActiveTable(CTHANDLE Handle, pVRLEN pScanRec);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetNextActiveTable(CTHANDLE Handle, pVRLEN pScanRec);
ctdbEXPORT CTHANDLE ctdbDECL ctdbFindActiveTable(CTHANDLE Handle, pTEXT Name);
ctdbEXPORT CTHANDLE ctdbDECL ctdbFindActiveTableByUID(CTHANDLE Handle, ULONG uid);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetActiveDatabaseUID(CTHANDLE Handle, pULONG puid);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsActiveDatabase(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetDatabasePath(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetDatabaseName(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetTableCount(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetActiveTableByUID(CTHANDLE Handle, ULONG uid);
ctdbEXPORT pTEXT ctdbDECL ctdbGetDefaultSqlTableOwner(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDefaultSqlTableOwner(CTHANDLE Handle, pTEXT sqlowner);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsSQLDatabase(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDatabaseExclusive(CTHANDLE Handle, CTBOOL flag);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsDatabaseExclusive(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbDumpSysTablesSQLStruct(pCTDBDATABASE dbHandle, pTEXT currDumpFileName);
ctdbEXPORT CTDBRET ctdbDECL ctdbCheckSysTablesSQLStructVersion(pTEXT currDumpFileName, CTSQL_VERSION *checkedVersion, pDICTERROR Error[], NINT *ErrorCount);
ctdbEXPORT CTDBRET ctdbDECL ctdbCheckSysTablesSQLInfo(pCTDBDATABASE pDatabase, pDICTERROR Error[], NINT *ErrorCount);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetVTableInfoFromDict(pCTDBDATABASE pDatabase, pTEXT name, ULONG type, pCTDBVTABLEINFO VTableRes);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetDatabaseTransactionMode(CTHANDLE Handle, CTBEGIN_MODE *ptranmode);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDictInSuperfile(CTHANDLE Handle, CTBOOL superfile);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindTableDictionaryMark(CTHANDLE Handle, pTEXT Name, pUCOUNT Dictattr);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDatabaseTableMarkFilter(CTHANDLE Handle, UCOUNT Dictattr);


/*^****************************************************************************\
*
*   CTDB C API Table function prototypes
*
\******************************************************************************/
ctdbEXPORT VOID ctdbDECL _ctdbIfilFree(pCTDBTABLE pTable);
ctdbEXPORT VOID ctdbDECL _ctdbFreeVTablePtr(pVOID pTable, VTABLE_TYPE type);
ctdbEXPORT pVOID ctdbDECL _ctdbAllocVTablePtr(VTABLE_TYPE type);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetTableHandle(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAllocTable(CTHANDLE Handle);
ctdbEXPORT VOID ctdbDECL ctdbFreeTable(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsActiveTable(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetTablePath(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetTableName(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetTableExtension(CTHANDLE Handle);
ctdbEXPORT VRLEN ctdbDECL ctdbGetTableIndexCount(CTHANDLE Handle);
ctdbEXPORT VRLEN ctdbDECL ctdbGetTableFieldCount(CTHANDLE Handle);
ctdbEXPORT CTOPEN_MODE ctdbDECL ctdbGetTableOpenMode(CTHANDLE Handle);
ctdbEXPORT CTCREATE_MODE ctdbDECL ctdbGetTableCreateMode(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetTableDefaultDataExtentSize(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetTableDefaultIndexExtentSize(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTablePath(CTHANDLE Handle, pTEXT Path);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTableExtension(CTHANDLE Handle, pTEXT fExt);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTableDefaultDataExtentSize(CTHANDLE Handle, NINT size);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTableDefaultIndexExtentSize(CTHANDLE Handle, NINT size);
ctdbEXPORT CTDBRET ctdbDECL ctdbCreateTable(CTHANDLE Handle, pTEXT TableName, CTCREATE_MODE CreateMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbCreateMRTTable(CTHANDLE Handle, pTEXT VTableName, pTEXT ParentName, CTCREATE_MODE CreateMode, pTEXT filter);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetVTableInfoFromTable(pCTDBVTABLEINFO VTableRes);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAllocVTableInfo(pCTDBTABLE pTable, UCOUNT size);
ctdbEXPORT VOID ctdbDECL ctdbFreeVTableInfo(pCTDBVTABLEINFO Info);
ctdbEXPORT CTDBRET ctdbDECL ctdbRenameTable(CTHANDLE Handle, pTEXT oldname, pTEXT newname);
ctdbEXPORT CTDBRET ctdbDECL ctdbMoveTable(CTHANDLE Handle, pTEXT oldname, pTEXT newpath, pTEXT newname);
ctdbEXPORT CTDBRET ctdbDECL ctdbOpenTable(CTHANDLE Handle, pTEXT TableName, CTOPEN_MODE OpenMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbOpenTableByUID(CTHANDLE Handle, ULONG uid, CTOPEN_MODE OpenMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbCloseTable(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbCloseAll(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetTablePassword(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetTableGroupid(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetIndexExtension(CTHANDLE Handle);
ctdbEXPORT LONG ctdbDECL ctdbGetTablePermission(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTablePassword(CTHANDLE Handle, pTEXT password);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTableGroupid(CTHANDLE Handle, pTEXT groupid);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexExtension(CTHANDLE Handle, pTEXT ext);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTablePermission(CTHANDLE Handle, LONG permmask);
ctdbEXPORT pVOID ctdbDECL ctdbGetTableObjptr(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTableObjptr(CTHANDLE Handle, pVOID ptr);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetActiveTableUID(CTHANDLE Handle, pULONG puid);
ctdbEXPORT CTDBRET ctdbDECL ctdbAlterTable(CTHANDLE Handle, NINT Action);
ctdbEXPORT CTDBRET ctdbDECL _ctdbIconAlloc(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL _ctdbIconFree(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL _ctdbIconReset(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL _ctdbIconAdd(CTHANDLE Handle, pNINT pIcon);
ctdbEXPORT CTDBRET ctdbDECL _ctdbIconSwitch(CTHANDLE Handle, pNINT pIcon);
ctdbEXPORT CTDBRET ctdbDECL _ctdbIconRelease(CTHANDLE Handle, NINT Icon);
ctdbEXPORT CTDBRET ctdbDECL _ctdbIconAttach(CTHANDLE Handle, NINT Icon);
ctdbEXPORT CTDBRET ctdbDECL ctdbResetAll(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbHasNullFieldSupport(CTHANDLE Handle);
ctdbEXPORT pCTDBSUPER ctdbDECL ctdbGetTableSuperFile(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTableSuperFile(CTHANDLE Handle, pCTDBSUPER pSuper);
ctdbEXPORT CTDBRET ctdbDECL ctdbClearTableSuperFile(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnlockTable(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnlockTableWriteLocks(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetTableNbr(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetTable(CTHANDLE Handle, NINT index);
ctdbEXPORT CTBOOL ctdbDECL ctdbHasRecbyt(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbHasRowid(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsVTable(CTHANDLE Handle);
ctdbEXPORT UINT ctdbDECL ctdbGetVTableNumber(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetMRTTableFilter(CTHANDLE Handle, pTEXT condition);
ctdbEXPORT NINT ctdbDECL ctdbGetTablePartitionIndexNbr(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTablePartitionIndexNbr(CTHANDLE Handle, NINT idxno);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTablePartitionNumberBits(CTHANDLE Handle, UCOUNT bitno);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTablePartitionRule(CTHANDLE Handle, pTEXT expr);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTablePartitionMaximumActive(CTHANDLE Handle, UCOUNT max);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetMRTTableDefaultIndex(CTHANDLE Handle, NINT idxno, pVOID min, VRLEN minlen, pVOID max, VRLEN maxlen, MRT_IDX_METHOD method);
ctdbEXPORT CTDBRET ctdbPartAdminByName(CTHANDLE handle,pTEXT partname,CTPART_MODE_E partmode,pCOUNT partstatus);
ctdbEXPORT CTDBRET ctdbPartAdminByKey(CTHANDLE handle,pVOID keyval,CTPART_MODE_E partmode,pCOUNT partstatus);
ctdbEXPORT CTDBRET ctdbPartAdminByNumber(CTHANDLE handle,LONG partno,CTPART_MODE_E partmode,pCOUNT partstatus);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIdentityField(CTHANDLE Handle, pTEXT FieldName, CTINT64 seed, CTINT64 increment);
ctdbEXPORT pTEXT ctdbDECL ctdbGetIdentityField(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbGetIdentityFieldDetails(CTHANDLE Handle, pLONG8 seed, pLONG8 increment);
ctdbEXPORT LONG ctdbDECL ctdbGetFirstPartition(CTHANDLE Handle);
ctdbEXPORT LONG ctdbDECL ctdbGetLastPartition(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTablePartitionDynMbrs(CTHANDLE Handle, pTEXT partdesc);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTableDictionaryMark(CTHANDLE Handle, UCOUNT mark);
ctdbEXPORT CTDBRET ctdbDECL ctdbTruncateTable(CTHANDLE Handle);

#ifdef CTDB_CNDX_IDX 
ctdbEXPORT CTDBRET ctdbDECL ctdbUpdateCndxIndex(CTHANDLE Handle, NINT indexnbr, pTEXT cndexpr);
ctdbEXPORT CTDBRET ctdbDECL ctdbUpdateCndxIndexByName(CTHANDLE Handle, pTEXT indexname, pTEXT cndexpr);
ctdbEXPORT NINT ctdbDECL ctdbGetCndxIndexLength(CTHANDLE Handle, NINT indexnbr);
ctdbEXPORT NINT ctdbDECL ctdbGetCndxIndexLengthByName(CTHANDLE Handle, pTEXT indexname);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetCndxIndex(CTHANDLE Handle, NINT indexnbr, pTEXT buffer, NINT bufferlen);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetCndxIndexByName(CTHANDLE Handle, pTEXT indexname, pTEXT buffer, NINT bufferlen);
#endif /* CTDB_CNDX_IDX  */

ctdbEXPORT CTDBRET ctdbDECL ctdbGetPadChar(CTHANDLE Handle, pTEXT pPadchar, pTEXT pDmlchar);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetPadChar(CTHANDLE Handle, NINT padchar, NINT dmlchar);
ctdbEXPORT CTDBRET ctdbDECL ctdbUpdatePadChar(CTHANDLE Handle, NINT padchar, NINT dmlchar, CTBOOL rebuild);

ctdbEXPORT CTDBRET ctdbDECL ctdbUpdateCreateMode(CTHANDLE Handle, CTCREATE_MODE mode);
ctdbEXPORT CTBOOL ctdbDECL ctdbHasDelField(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetDatno(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetIdxnoByNumber(CTHANDLE Handle, NINT index);
ctdbEXPORT NINT ctdbDECL ctdbGetIdxnoByName(CTHANDLE Handle, pTEXT indexname);

ctdbEXPORT CTDBRET ctdbDECL ctdbRemoveTable(CTHANDLE Handle);

#ifdef CTDB_CALLBACK
ctdbEXPORT CTDB_TABLE_TYPE ctdbDECL ctdbGetTableType(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetRebuildProgress(CTHANDLE Handle);
#endif

#ifdef CTDB_SYSTEM_FILTER
ctdbEXPORT CTDBRET ctdbDECL ctdbSystemFilterOn(CTHANDLE Handle, CTSYSFILTER mode);
ctdbEXPORT CTDBRET ctdbDECL ctdbSystemFilterOff(CTHANDLE Handle, CTSYSFILTER mode);
#endif /* CTDB_SYSTEM_FILTER */

ctdbEXPORT CTDBRET ctdbDECL ctdbSetTableKSeg(CTHANDLE Handle, pctKSEGDEF pKSeg);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetTableKSeg(CTHANDLE Handle, pctKSEGDEF pKSeg);

ctdbEXPORT ULONG ctdbDECL ctdbGetTableStatus(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbAttachTable(CTHANDLE Handle, NINT datno);
ctdbEXPORT CTDBRET ctdbDECL ctdbAttachTableXtd(CTHANDLE Handle, NINT datno, NINT nbrfields, pDATOBJ dodaptr, pIFIL ifilptr);
ctdbEXPORT CTDBRET ctdbDECL ctdbDetachTable(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetTableOwner(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetTableOwner(CTHANDLE Handle, pTEXT owner);
ctdbEXPORT CTDBRET ctdbDECL ctdbRebuildTable(CTHANDLE Handle, CTREBUILD_MODE mode);
ctdbEXPORT COUNT ctdbDECL ctdbSetCallbackOnRebuild(pRBLCBFNC funcptr, UCOUNT step);

ctdbEXPORT CTHANDLE ctdbDECL ctdbAllocResource(CTHANDLE Handle, ULONG type, ULONG number, pTEXT name);
ctdbEXPORT CTDBRET ctdbDECL ctdbFreeResource(CTHANDLE resource);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnlockResource(CTHANDLE resource);
ctdbEXPORT CTDBRET ctdbDECL ctdbAddResource(CTHANDLE resource, pVOID data, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbDeleteResource(CTHANDLE resource);
ctdbEXPORT CTDBRET ctdbDECL ctdbUpdateResource(CTHANDLE resource, pVOID data, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbFirstResource(CTHANDLE resource, CTBOOL lock);
ctdbEXPORT CTDBRET ctdbDECL ctdbNextResource(CTHANDLE resource, CTBOOL lock);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindResource(CTHANDLE resource, ULONG type, ULONG number, CTBOOL lock);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindResourceByName(CTHANDLE resource, pTEXT name, CTBOOL lock);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsResourceLocked(CTHANDLE resource);
ctdbEXPORT ULONG ctdbDECL ctdbGetResourceType(CTHANDLE resource);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetResourceType(CTHANDLE resource, ULONG type);
ctdbEXPORT ULONG ctdbDECL ctdbGetResourceNumber(CTHANDLE resource);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetResourceNumber(CTHANDLE resource, ULONG number);
ctdbEXPORT pTEXT ctdbDECL ctdbGetResourceName(CTHANDLE resource);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetResourceName(CTHANDLE resource, pTEXT name);
ctdbEXPORT VRLEN ctdbDECL ctdbGetResourceDataLength(CTHANDLE resource);
ctdbEXPORT pVOID ctdbDECL ctdbGetResourceData(CTHANDLE resource);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetResourceData(CTHANDLE resource, pVOID data, VRLEN size);

ctdbEXPORT CTDB_BINARY_FLAG ctdbDECL ctdbGetBinaryFlag(CTHANDLE Handle, NINT fldno);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetBinaryFlag(CTHANDLE Handle, NINT fldno, CTDB_BINARY_FLAG flag);
ctdbEXPORT pCTDBFIELD ctdbDECL _ctdbGetFieldFromVarSeg(pCTDBTABLE pTable, pISEG pIseg);
ctdbEXPORT CTDBRET ctdbDECL ctdbCloneTable(CTHANDLE tarHandle, pTEXT tarTableName, CTHANDLE srcHandle);

ctdbEXPORT CTDBRET ctdbDECL ctdbFilterAll(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbAddVTableResource(CTHANDLE Parent, CTHANDLE Child);
ctdbEXPORT CTDBRET ctdbDECL ctdbRemoveVTableResource(CTHANDLE Parent, NINT number);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetExtensionHint(CTHANDLE Handle, EXT_INFO ExtHint);
ctdbEXPORT EXT_INFO ctdbDECL ctdbGetExtensionHint(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbPUTHDR(CTHANDLE hTable,LONG hdrval,COUNT mode);
ctdbEXPORT CTDBRET ctdbDECL ctdbLOKTIMOUT(CTHANDLE hTable,LONG mode,LONG timeoutSEC);
ctdbEXPORT CTDBRET ctdbDECL ctdbCheckRecordSchemaConversion(CTHANDLE Handle, pBGLDINF status);
ctdbEXPORT CTDBRET ctdbDECL ctdbStartRecordSchemaConversion(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbTableHasCallback(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbTableHasLocks(CTHANDLE Handle);

/*^****************************************************************************\
*
*   CTDB C API Record function prototypes
*
\******************************************************************************/
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetRecordHandle(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAllocRecord(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbDuplicateRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbCopyRecordBuffer(CTHANDLE Source, CTHANDLE Dest);
ctdbEXPORT CTDBRET ctdbDECL ctdbAssignRecordBuffer(CTHANDLE Handle, pVOID pBuffer, VRLEN reclen);
ctdbEXPORT VOID ctdbDECL ctdbFreeRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbResetRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbFirstRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbLastRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbNextRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbPrevRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindTarget(CTHANDLE Handle, pVOID target, CTFIND_MODE FindMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindRecord(CTHANDLE Handle, CTFIND_MODE FindMode);
ctdbEXPORT CTBOOL  ctdbDECL ctdbLocateRecord(CTHANDLE Handle, CTLOC_MODE LocateMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetRecordCriteria(CTHANDLE Handle, CTLOC_MODE LocateMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbUpdateRecordCriteria(CTHANDLE Handle, CTLOC_MODE LocateMode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetBestIndex(CTHANDLE Handle, pCTDBLIST fieldNameList, CTLOC_MODE LocateMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbAddLocateCriteria(CTHANDLE Handle, CTSTRING LocateFieldName, CTSTRING LocateFieldValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbClearRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbReadRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbWriteRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbDeleteRecord(CTHANDLE Handle);
ctdbEXPORT pVOID ctdbDECL ctdbGetRecordBuffer(CTHANDLE Handle);
ctdbEXPORT VRLEN ctdbDECL ctdbGetRecordLength(CTHANDLE Handle);
ctdbEXPORT VRLEN ctdbDECL ctdbGetRecordSize(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsNewRecord(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsEditedRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetNewRecord(CTHANDLE Handle, CTBOOL flag);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetEditedRecord(CTHANDLE Handle, CTBOOL flag);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetRecordBuffer(CTHANDLE Handle, pVOID pBuffer, VRLEN reclen, CTRECBUF_MODE mode);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsNullField(CTHANDLE Handle, NINT FieldNbr);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetRecordPos(CTHANDLE Handle, pCTOFFSET pOffset);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetRecordKeyPos(CTHANDLE Handle, pCTOFFSET pPosition);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetRecordPos(CTHANDLE Handle, CTOFFSET offset);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetRecordOffset(CTHANDLE Handle, CTOFFSET offset);
ctdbEXPORT CTDBRET ctdbDECL ctdbSeekRecord(CTHANDLE Handle, CTOFFSET offset);
ctdbEXPORT NINT ctdbDECL ctdbGetDefaultIndex(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetDefaultIndexName(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDefaultIndex(CTHANDLE Handle, NINT indexno);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDefaultIndexByName(CTHANDLE Handle, pTEXT name);
ctdbEXPORT NINT ctdbDECL ctdbGetFieldNumberByName(CTHANDLE Handle, pTEXT FieldName);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsBool(CTHANDLE Handle, NINT FieldNbr, pCTBOOL pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsSigned(CTHANDLE Handle, NINT FieldNbr, pCTSIGNED pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsUnsigned(CTHANDLE Handle, NINT FieldNbr, pCTUNSIGNED pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsDate(CTHANDLE Handle, NINT FieldNbr, pCTDATE pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsTime(CTHANDLE Handle, NINT FieldNbr, pCTTIME pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsTimeMsec(CTHANDLE Handle, NINT FieldNbr, pCTTIMEMS pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsMoney(CTHANDLE Handle, NINT FieldNbr, pCTMONEY pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsFloat(CTHANDLE Handle, NINT FieldNbr, pCTFLOAT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsDateTime(CTHANDLE Handle, NINT FieldNbr, pCTDATETIME pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsString(CTHANDLE Handle, NINT FieldNbr, CTSTRING pValue, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsJSON(CTHANDLE Handle, NINT FieldNbr, CTJSON pValue, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsBinary(CTHANDLE Handle, NINT FieldNbr, pVOID pValue, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsBlob(CTHANDLE Handle, NINT FieldNbr, pCTBLOB pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsBigint(CTHANDLE Handle, NINT FieldNbr, pCTBIGINT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsUnsignedBigint(CTHANDLE Handle, NINT FieldNbr, pCTUBIGINT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsCurrency(CTHANDLE Handle, NINT FieldNbr, pCTCURRENCY pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsNumber(CTHANDLE Handle, NINT FieldNbr, pCTNUMBER pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsBool(CTHANDLE Handle, NINT FieldNbr, CTBOOL Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsSigned(CTHANDLE Handle, NINT FieldNbr, CTSIGNED Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsUnsigned(CTHANDLE Handle, NINT FieldNbr, CTUNSIGNED Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsDate(CTHANDLE Handle, NINT FieldNbr, CTDATE Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsTime(CTHANDLE Handle, NINT FieldNbr, CTTIME Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsTimeMsec(CTHANDLE Handle, NINT FieldNbr, CTTIMEMS value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsMoney(CTHANDLE Handle, NINT FieldNbr, CTMONEY Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsFloat(CTHANDLE Handle, NINT FieldNbr, CTFLOAT Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsDateTime(CTHANDLE Handle, NINT FieldNbr, CTDATETIME Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsString(CTHANDLE Handle, NINT FieldNbr, CTSTRING Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsJSON(CTHANDLE Handle, NINT FieldNbr, CTJSON Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsBinary(CTHANDLE Handle, NINT FieldNbr, pVOID pValue, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsBlob(CTHANDLE Handle, NINT FieldNbr, pCTBLOB pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsBigint(CTHANDLE Handle, NINT FieldNbr, CTBIGINT Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsUnsignedBigint(CTHANDLE Handle, NINT FieldNbr, CTUBIGINT Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsCurrency(CTHANDLE Handle, NINT FieldNbr, CTCURRENCY Value);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsNumber(CTHANDLE Handle, NINT FieldNbr, pCTNUMBER pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetRecordCount(CTHANDLE Handle, pCTUINT64 pCount);
ctdbEXPORT CTDBRET ctdbDECL ctdbRecordSetOn(CTHANDLE Handle, NINT siglen);
ctdbEXPORT CTDBRET ctdbDECL ctdbRecordSetOff(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsRecordSetOn(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsVariableField(CTHANDLE Handle, NINT FieldNbr);
ctdbEXPORT VRLEN ctdbDECL ctdbGetFieldDataLength(CTHANDLE Handle, NINT FieldNbr);
ctdbEXPORT VRLEN ctdbDECL ctdbGetFieldSize(CTHANDLE Handle, NINT FieldNbr);
ctdbEXPORT VRLEN ctdbDECL ctdbGetFieldOffset(CTHANDLE Handle, NINT FieldNbr);
ctdbEXPORT pVOID ctdbDECL ctdbGetFieldAddress(CTHANDLE Handle, NINT FieldNbr);
ctdbEXPORT CTDBRET ctdbDECL ctdbClearField(CTHANDLE Handle, NINT FieldNbr);
ctdbEXPORT CTDBRET ctdbDECL ctdbLockRecord(CTHANDLE Handle, NINT mode);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnlockRecord(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbBuildTargetKey(CTHANDLE Handle, CTFIND_MODE FindMode, pVOID targetkey, pVRLEN targetlen);
ctdbEXPORT pCTDBDATA ctdbDECL ctdbGetFieldData(pCTDBRECORD pRecord, NINT FieldNbr);
ctdbEXPORT NINT ctdbDECL ctdbGetRecordNbr(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetRecord(CTHANDLE Handle, NINT index);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetRowid(CTHANDLE Handle, pCTROWID pRowid);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindRowid(CTHANDLE Handle, CTROWID rowid, CTFIND_MODE FindMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbFirstKey(CTHANDLE Handle, pCTOFFSET pOffset);
ctdbEXPORT CTDBRET ctdbDECL ctdbLastKey(CTHANDLE Handle, pCTOFFSET pOffset);
ctdbEXPORT CTDBRET ctdbDECL ctdbNextKey(CTHANDLE Handle, pCTOFFSET pOffset);
ctdbEXPORT CTDBRET ctdbDECL ctdbPrevKey(CTHANDLE Handle, pCTOFFSET pOffset);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindKey(CTHANDLE Handle, pCTOFFSET pOffset, CTFIND_MODE FindMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbFindTargetKey(CTHANDLE Handle, pVOID target, pCTOFFSET pOffset, CTFIND_MODE FindMode);
ctdbEXPORT pVOID ctdbDECL ctdbGetKeyval(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetKeylen(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL _ctdbRecordSetSize(pCTDBRECORD pRecord, VRLEN reclen);
ctdbEXPORT CTDBRET ctdbDECL _ctdbUpdateRecord(pCTDBRECORD pRecord, const CTBOOL isNew);
ctdbEXPORT CTDBRET ctdbDECL ctdbRecordBlockingReadOn(CTHANDLE Handle, LONG timeoutsec, pTEXT condition);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsRecordBlockingReadOn(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbRecordBlockingReadOff(CTHANDLE Handle);

#ifdef CTDB_CNDX_IDX 
ctdbEXPORT CTDBRET ctdbDECL ctdbCndxCompile(CTHANDLE Handle, pTEXT cndexpr);
ctdbEXPORT CTDBRET ctdbDECL ctdbCndxEval(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbCndxFree(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbCndxGetExpression(CTHANDLE Handle);
#endif /* CTDB_CNDX_IDX  */

#ifdef CTDB_FILTER_020617
ctdbEXPORT CTDBRET ctdbDECL ctdbFilterRecord(CTHANDLE Handle, pTEXT cndexpr);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsFilteredRecord(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetFilter(CTHANDLE Handle);

#ifdef ctdbRECORD_FILTER
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFilter(CTHANDLE Handle, pVOID expr, CTFILTER_TYPE exprtype);
ctdbEXPORT CTFILTER_TYPE ctdbDECL ctdbGetFilterType(CTHANDLE Handle);
#endif
#endif /* CTDB_FILTER_020617 */

ctdbEXPORT CTLOCK_MODE ctdbDECL ctdbGetRecordLock(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbCompareRecords(CTHANDLE Handle1,CTHANDLE Handle2);

ctdbEXPORT CTDBRET ctdbDECL ctdbRecordAtPercentile(CTHANDLE Handle, NINT pecent);
ctdbEXPORT CTDBRET ctdbDECL ctdbRecordPosAtOffset(CTHANDLE Handle, pCTOFFSET offset);
#ifdef ctN8
ctdbEXPORT ULONG8 ctdbDECL ctdbEstimateSpan(CTHANDLE Handle, pVOID key1, pVOID key2);
#endif

ctdbEXPORT CTDBRET ctdbDECL ctdbRecordRangeOn(CTHANDLE Handle, NINT SegCount, pVOID lRange, pVOID uRange, pNINT operators);
ctdbEXPORT CTDBRET ctdbDECL ctdbRecordRangeXtdOn(CTHANDLE Handle, NINT SegCount, pVOID lRange, pVOID uRange, pNINT operators, ULONG rangeFlag);
ctdbEXPORT CTDBRET ctdbDECL ctdbRecordRangeOff(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsRecordRangeOn(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSwitchContext(CTHANDLE Handle);

#ifdef ctdbUNICODE
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsUTF16(CTHANDLE Handle, NINT FieldNbr, pWCHAR pValue, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAsUTF32(CTHANDLE Handle, NINT FieldNbr, pULONG pValue, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsUTF16(CTHANDLE Handle, NINT FieldNbr, pWCHAR pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAsUTF32(CTHANDLE Handle, NINT FieldNbr, pULONG pValue);
#endif /* ctdbUNICODE */

ctdbEXPORT LONG ctdbDECL ctdbBatchLoaded(CTHANDLE Handle);
ctdbEXPORT LONG ctdbDECL ctdbBatchLocked(CTHANDLE Handle);
ctdbEXPORT LONG ctdbDECL ctdbBatchTotal(CTHANDLE Handle);
ctdbEXPORT CTBATCH_MODE ctdbDECL ctdbBatchMode(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbEndBatch(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbInsertBatch(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsBatchActive(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbNextBatch(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetBatch(CTHANDLE Handle, CTBATCH_MODE mode, VRLEN targetLen, VRLEN bufferLen);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetBatchFilter(CTHANDLE Handle, pTEXT expr);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetBatchRangeOn(CTHANDLE Handle, NINT SegCount, pVOID lRange, pVOID uRange, pNINT operators);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetBatchRangeOff(CTHANDLE Handle);

ctdbEXPORT NINT ctdbDECL ctdbGetErrorIndex(CTHANDLE Handle);
ctdbEXPORT LONG ctdbDECL ctdbNumberOfKeyEntries(CTHANDLE Handle, NINT index);
ctdbEXPORT CTDBRET ctdbDECL ctdbJumpToRecord(CTHANDLE Handle, LONG offset);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetLastIdentity(CTHANDLE Handle, pLONG8 value);

ctdbEXPORT CTDBRET ctdbDECL ctdbParseRecordExpr(CTHANDLE Handle, pTEXT expr, pCTDBTYPE exprType, pNINT exprIdx);
ctdbEXPORT CTDBRET ctdbDECL ctdbEvalExprAsSigned(CTHANDLE Handle, NINT exprIdx, pCTSIGNED exprValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbEvalExprAsDate(CTHANDLE Handle, NINT exprIdx, pCTDATE exprValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbEvalExprAsTime(CTHANDLE Handle, NINT exprIdx, pCTTIME exprValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbEvalExprAsDateTime(CTHANDLE Handle, NINT exprIdx, pCTDATETIME exprValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbEvalExprAsNumber(CTHANDLE Handle, NINT exprIdx, pCTNUMBER exprValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbEvalExprAsString(CTHANDLE Handle, NINT exprIdx, pTEXT exprValue, pVRLEN exprValueLen);

ctdbEXPORT CTDBRET ctdbDECL ctdbAddUserDefFunc(CTHANDLE Handle, pTEXT funcName, ctdbUDFFunc funcPointer, CTDBTYPE funcRetType, pCTDBTYPE funcArgTypes, COUNT funcArgCount);

ctdbEXPORT CTHANDLE ctdbDECL ctdbGetActiveResultSet(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbFTSearchOn(CTHANDLE Handle, pTEXT query, NINT mode);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsFTSearchOn(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbFTSearchOff(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIdentityOff(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIdentityOn(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsIdentityOff(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFTSErrorDetails(CTHANDLE Handle, pNINT error, pNINT position);

ctdbEXPORT CTDBRET ctdbDECL ctdbAddToFieldMask(CTHANDLE Handle, NINT FieldNbr);
ctdbEXPORT CTDBRET ctdbDECL ctdbRemoveFieldMask(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsFieldMaskOn(CTHANDLE Handle);

/*^****************************************************************************\
*
*   CTDB C API Index function prototypes
*
\******************************************************************************/
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetIndexHandle(CTHANDLE Handle);
ctdbEXPORT pCTDBINDEX ctdbDECL ctdbAllocIndex(CTHANDLE Handle);
ctdbEXPORT VOID ctdbDECL ctdbFreeIndex(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddIndex(CTHANDLE Handle, pTEXT name, CTDBKEY key_type, CTBOOL AllowDuplicates, CTBOOL NullFlag);
ctdbEXPORT CTDBRET ctdbDECL ctdbDelIndex(CTHANDLE Handle, NINT IndexNumber);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetIndex(CTHANDLE Handle, NINT IndexNumber);
ctdbEXPORT NINT ctdbDECL ctdbGetIndexNbrByName(CTHANDLE Handle, pTEXT name);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetIndexByName(CTHANDLE Handle, pTEXT name);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetIndexByUID(CTHANDLE Handle, ULONG uid);
ctdbEXPORT VRLEN ctdbDECL ctdbGetIndexSegmentCount(CTHANDLE Handle);
ctdbEXPORT VRLEN ctdbDECL ctdbGetIndexKeyLength(CTHANDLE Handle);
ctdbEXPORT CTDBKEY ctdbDECL ctdbGetIndexKeyType(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetIndexEmptyChar(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbGetIndexDuplicateFlag(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbGetIndexNullFlag(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbGetIndexTemporaryFlag(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexKeyType(CTHANDLE Handle, CTDBKEY KeyType);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexEmptyChar(CTHANDLE Handle, NINT EmptyChar);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexDuplicateFlag(CTHANDLE Handle, CTBOOL DupFlag);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexNullFlag(CTHANDLE Handle, CTBOOL NulFlag);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexTemporaryFlag(CTHANDLE Handle, CTBOOL TempFlag);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexCndxExpr(CTHANDLE Handle, pTEXT conditionExpr);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetIndexNbr(CTHANDLE Handle, pVRLEN pNumber);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetIndexUID(CTHANDLE Handle, pTEXT Name, pULONG puid);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexFilename(CTHANDLE Handle, pTEXT path, pTEXT filename);
ctdbEXPORT pTEXT ctdbDECL ctdbGetIndexFilename(CTHANDLE Handle);
ctdbEXPORT NINT ctdbGetIdxno(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexDistinctKeyCountFlag(CTHANDLE Handle, CTBOOL Flag);
ctdbEXPORT CTBOOL ctdbDECL ctdbGetIndexDistinctKeyCountFlag(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbEstimateNumberOfDistinctKeyEntries(CTHANDLE Handle, LONG nsegs, pDSTSEGV vsegs, pLONG asegs, pCTUINT64 pCount);

ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexKSeg(CTHANDLE Handle, pctKSEGDEF pKSeg);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetIndexKSeg(CTHANDLE Handle, pctKSEGDEF pKSeg);


ctdbEXPORT ULONG ctdbDECL ctdbGetIndexStatus(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetIndexName(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetIndexName(CTHANDLE Handle, pTEXT IndexName);
ctdbEXPORT CTDBRET ctdbDECL ctdbCheckIndexBackgroundLoad(CTHANDLE Handle, pBGLDINF status);

/*^****************************************************************************\
*
*   CTDB C API Full Text Search function prototypes
*
\******************************************************************************/
ctdbEXPORT pCTDBFTIDICT ctdbDECL ctdbAllocFTIDict(CTHANDLE Handle);
ctdbEXPORT VOID ctdbDECL ctdbFreeFTIDict(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFTIDictHandle(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFTIDictOption(CTHANDLE Handle, UCOUNT option, pTEXT pvalue, ULONG lvalue);
#ifdef REMOVED_20171012 /* option causing troubles and requiring path to be stored in resource. see devlog for further details*/
ctdbEXPORT CTDBRET ctdbDECL ctdbCreateFTIDict (CTHANDLE Handle, pTEXT name, pTEXT path, CTCREATE_MODE CreateMode);
#endif

ctdbEXPORT CTDBRET ctdbDECL _ctdbGetFTIDictResourceParamFromFile(CTHANDLE Handle, pTEXT name, pTEXT path, ppCTDBFTIDICT pHandle);
ctdbEXPORT CTDBRET ctdbLOCAL _ctdbCreateFTIDictResourceParam(pCTDBFTIDICT pFTID, ppTEXT rtext);
ctdbEXPORT CTDBRET ctdbLOCAL _ctdbCreateFTIResourceParam(pCTDBFTI pFTI, ppTEXT rtext);
ctdbEXPORT CTDBRET ctdbLOCAL _ctdbParseFTIDictResourceParam(pTEXT params, ppCTDBFTIDICT pFTID_out, pNINT fwd);
ctdbEXPORT CTDBRET ctdbLOCAL _ctdbParseFTIResourceParam(pCTDBTABLE pTable, pTEXT datname, pTEXT params, LONG calltm, ppCTDBFTI pFTI_out);
ctdbEXPORT CTDBRET ctdbLOCAL _ctdbUpdateNameInFTIParam(pTEXT params, pTEXT name, ppTEXT newparams);

ctdbEXPORT pCTDBFTI ctdbDECL ctdbAllocFTI(CTHANDLE Handle);
ctdbEXPORT VOID ctdbDECL ctdbFreeFTI(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFTIHandle(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddFTI(CTHANDLE Handle, pTEXT name);
ctdbEXPORT CTDBRET ctdbDECL ctdbAddFTIField(CTHANDLE Handle, CTHANDLE FieldHandle, ULONG mode);
ctdbEXPORT CTDBRET ctdbDECL ctdbAddFTIFieldByName(CTHANDLE Handle, NINT Number, pTEXT FieldName, ULONG mode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFTI(CTHANDLE Handle, NINT Number);
ctdbEXPORT CTDBRET ctdbDECL ctdbDelFTI(CTHANDLE Handle, NINT Number);
ctdbEXPORT COUNT ctdbDECL ctdbGetTableFTICount(CTHANDLE Handle);
ctdbEXPORT ULONG ctdbDECL ctdbGetFTIStatus(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetFTIFieldCount(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFTIField(CTHANDLE Handle, NINT FieldNumber);
ctdbEXPORT ULONG ctdbDECL ctdbGetFTIFieldMode(CTHANDLE Handle, NINT FieldNumber);
ctdbEXPORT COUNT ctdbDECL ctdbGetFTINbrByName(CTHANDLE Handle, pTEXT name);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFTIByName(CTHANDLE Handle, pTEXT name);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDefaultFTI(CTHANDLE Handle, NINT Number);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFTIOption(CTHANDLE Handle, UCOUNT option, pTEXT pvalue, ULONG lvalue);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFTIByUID(CTHANDLE Handle, ULONG uid);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFTINbr(CTHANDLE Handle, pVRLEN pNumber);
ctdbEXPORT pTEXT ctdbDECL ctdbGetFTIName(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFTICndxExpr(CTHANDLE Handle, pTEXT conditionExpr);
ctdbEXPORT CTDBRET ctdbDECL ctdbCheckFTIBackgroundLoad(pCTDBFTI pFTI, pBGLDINF status);
ctdbEXPORT CTDBRET ctdbDECL ctdbStartFTIBackgroundLoad(pCTDBFTI pFTI);
/*backward compatible function, deprecated */
ctdbEXPORT CTDBRET ctdbDECL ctdbFTICheckBackgroundLoad(pCTDBFTI pFTI, pBGLDINF status);
ctdbEXPORT CTDBRET ctdbDECL ctdbFTIStartBackgroundLoad(pCTDBFTI pFTI);
/* end of deprecated functions */

/*^****************************************************************************\
*
*   CTDB C API Index Segment function prototypes
*
\******************************************************************************/
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetSegmentHandle(CTHANDLE Handle);
ctdbEXPORT pCTDBISEG ctdbDECL ctdbAllocSegment(CTHANDLE Handle);
ctdbEXPORT VOID ctdbDECL ctdbFreeSegment(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsExtSegment(CTSEG_MODE SegMode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetSegment(CTHANDLE Handle, NINT SegNumber);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetSegmentField(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetSegmentPartialField(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetSegmentFieldName(CTHANDLE Handle);
ctdbEXPORT CTSEG_MODE ctdbDECL ctdbGetSegmentMode(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetSegmentLength(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetSegmentMode(CTHANDLE Handle, CTSEG_MODE SegMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetSegmentNbr(CTHANDLE Handle, pVRLEN pNumber);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddSegment(CTHANDLE Handle, CTHANDLE FieldHandle, CTSEG_MODE SegMode);
ctdbEXPORT CTHANDLE ctdbDECL _i_ctdbAddSegment(CTHANDLE Handle, CTHANDLE FieldHandle, CTSEG_MODE SegMode, CTBOOL intcall);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddSegmentEx(CTHANDLE Handle, NINT offset, NINT length, CTSEG_MODE SegMode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddSegmentByNbr(CTHANDLE Handle, NINT IndexNbr, NINT FieldNbr, CTSEG_MODE SegMode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddSegmentByName(CTHANDLE Handle, NINT IndexNbr, pTEXT FieldName, CTSEG_MODE SegMode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbInsSegment(CTHANDLE Handle, NINT SegNumber, CTHANDLE FieldHandle, CTSEG_MODE SegMode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbInsSegmentByNbr(CTHANDLE Handle, NINT IndexNbr, NINT SegNumber, NINT FieldNbr, CTSEG_MODE SegMode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbInsSegmentByName(CTHANDLE Handle, NINT IndexNbr, NINT SegNumber, pTEXT FieldName, CTSEG_MODE SegMode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbInsSegmentEx(CTHANDLE Handle, NINT SegNumber, NINT offset, NINT length, CTSEG_MODE SegMode);
ctdbEXPORT CTDBRET ctdbDECL ctdbDelSegment(CTHANDLE Handle, NINT SegNumber);
ctdbEXPORT CTDBRET ctdbDECL ctdbDelSegmentEx(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddRowIdSegment(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddJSONSegment(CTHANDLE Handle, CTHANDLE FieldHandle, pTEXT key, CTDBTYPE type, VRLEN size);

ctdbEXPORT CTDBRET ctdbDECL ctdbSetKSegDefaults(pctKSEGDEF pKSeg);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetSegmentKSeg(CTHANDLE Handle, pctKSEGDEF pKSeg);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetSegmentKSeg(CTHANDLE Handle, pctKSEGDEF pKSeg);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetJSONSegmentProperties(CTHANDLE Handle, ppTEXT pKey, pCTDBTYPE pType, pVRLEN size);


ctdbEXPORT ULONG ctdbDECL ctdbGetSegmentStatus(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbMoveSegment(CTHANDLE Handle, NINT newIndex);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetSegmentField(CTHANDLE Handle, CTHANDLE field);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetJSONSegmentField(CTHANDLE Handle, CTHANDLE field, pTEXT key, CTDBTYPE type, VRLEN size);

/*^****************************************************************************\
*
*   CTDB C API Field function prototypes
*
\******************************************************************************/
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFieldHandle(CTHANDLE Handle);
ctdbEXPORT pCTDBFIELD ctdbDECL ctdbAllocField(pCTDBTABLE pTable, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength);
ctdbEXPORT VOID ctdbDECL ctdbFreeField(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddField(CTHANDLE Handle, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength);
ctdbEXPORT CTHANDLE ctdbDECL ctdbInsField(CTHANDLE Handle, NINT Index, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength);
ctdbEXPORT CTHANDLE ctdbDECL ctdbInsFieldByName(CTHANDLE Handle, pTEXT FieldIndex, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength);
ctdbEXPORT CTDBRET ctdbDECL ctdbDelField(CTHANDLE Handle, NINT Index);
ctdbEXPORT CTDBRET ctdbDECL ctdbDelFieldByName(CTHANDLE Handle, pTEXT FieldName);
ctdbEXPORT CTDBRET ctdbDECL ctdbMoveField(CTHANDLE Handle, NINT newIndex);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetField(CTHANDLE Handle, NINT Index);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetFieldByName(CTHANDLE Handle, pTEXT FieldName);
ctdbEXPORT NINT ctdbDECL ctdbGetFieldNumber(CTHANDLE Handle, pTEXT FieldName);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldProperties(CTHANDLE Handle, ppTEXT FieldName, pCTDBTYPE pType, pVRLEN pLength);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldProperties(CTHANDLE Handle, pTEXT FieldName, CTDBTYPE Type, VRLEN Length);
ctdbEXPORT NINT ctdbDECL ctdbGetFieldNbr(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetFieldName(CTHANDLE Handle);
ctdbEXPORT VRLEN ctdbDECL ctdbGetFieldLength(CTHANDLE Handle);
ctdbEXPORT CTDBTYPE ctdbDECL ctdbGetFieldType(CTHANDLE Handle);
ctdbEXPORT CTBOOL ctdbDECL ctdbGetFieldNullFlag(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetFieldPrecision(CTHANDLE Handle);
ctdbEXPORT NINT ctdbDECL ctdbGetFieldScale(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldNullFlag(CTHANDLE Handle, CTBOOL flag);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldPrecision(CTHANDLE Handle, NINT fprec);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldScale(CTHANDLE Handle, NINT fscale);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldName(CTHANDLE Handle, pTEXT name);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldLength(CTHANDLE Handle, VRLEN len);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldType(CTHANDLE Handle, CTDBTYPE type);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsFieldNumeric(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldAutoSysTime(CTHANDLE Handle, CTBOOL create, CTBOOL update); 
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldAutoSysTime(CTHANDLE Handle, pCTBOOL create, pCTBOOL update);
ctdbEXPORT pTEXT ctdbDECL ctdbGetFieldStringEncoding(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldStringEncoding(CTHANDLE Handle, pTEXT encoding);

#ifdef CTDB_DEFAULT_VALUE
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldDefaultValue(CTHANDLE Handle, pTEXT value, VRLEN length);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldDefaultValueType(CTHANDLE Handle, CTDEF_TYPE def_type);
ctdbEXPORT CTDEF_TYPE ctdbDECL ctdbGetFieldDefaultValueType(CTHANDLE Handle);
ctdbEXPORT pTEXT ctdbDECL ctdbGetFieldDefaultValue(CTHANDLE Handle, pVRLEN pLength);
ctdbEXPORT CTDBRET ctdbDECL ctdbClearFieldDefaultValue(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbClearAllFieldDefaultValue(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldDefaultDateTimeType(CTHANDLE Handle, CTDATE_TYPE dateType, CTTIME_TYPE timeType);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsFieldDefaultValueSet(CTHANDLE Handle);
ctdbEXPORT CTDATE_TYPE ctdbDECL ctdbGetFieldDefaultDateType(CTHANDLE Handle);
ctdbEXPORT CTTIME_TYPE ctdbDECL ctdbGetFieldDefaultTimeType(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbGetFieldDefaultValueAsBinary(CTHANDLE Handle, pTEXT buffer, pVRLEN pLength);
#endif /* CTDB_DEFAULT_VALUE */

ctdbEXPORT ULONG ctdbDECL ctdbGetFieldStatus(CTHANDLE Handle);
ctdbEXPORT CTDB_BINARY_FLAG ctdbDECL ctdbGetFieldBinaryFlag(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetFieldBinaryFlag(CTHANDLE Handle, CTDB_BINARY_FLAG flag);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddVirtualField(CTHANDLE Handle, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength, pVOID VirtualInfo);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetVirtualFieldClear(CTHANDLE Handle, ctdbClearVfieldsFunc vclear);

/*^****************************************************************************\
*
*   CTDB C API Date functions
*
\*****************************************************************************/
ctdbEXPORT CTDBRET ctdbDECL ctdbDateCheck(NINT year, NINT month, NINT day);
ctdbEXPORT CTDBRET ctdbDECL ctdbDatePack(pCTDATE pDate, NINT year, NINT month, NINT day);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateUnpack(CTDATE date, pNINT pyear, pNINT pmonth, pNINT pday);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateToString(CTDATE date, CTDATE_TYPE DateType, pTEXT pStr, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringToDate(pTEXT pStr, CTDATE_TYPE DateType, pCTDATE pDate);
ctdbEXPORT NINT ctdbDECL ctdbGetDay(CTDATE date);
ctdbEXPORT NINT ctdbDECL ctdbGetMonth(CTDATE date);
ctdbEXPORT NINT ctdbDECL ctdbGetYear(CTDATE date);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsLeapYear(CTDATE date);
ctdbEXPORT NINT ctdbDECL ctdbDayOfWeek(CTDATE date);
ctdbEXPORT CTDATE_TYPE ctdbDECL ctdbGetDefDateType(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDefDateType(CTHANDLE Handle, CTDATE_TYPE DateType);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrentDate(pCTDATE pDate);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringFormatToDate(pTEXT pStr, pTEXT Mask, pCTDATE pDate, CTDATE julianbase);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateToStringFormat(CTDATE Date, pTEXT Mask, pTEXT pStr, CTDATE julianbase);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringFormatToTime(pTEXT pStr, pTEXT Mask, pCTTIME pTime);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringFormatToTimeMsec(pTEXT pStr, pTEXT Mask, pCTTIMEMS pTime);
ctdbEXPORT CTDBRET ctdbDECL ctdbTimeToStringFormat(CTTIME Time, pTEXT Mask, pTEXT pStr);
ctdbEXPORT CTDBRET ctdbDECL ctdbTimeMsecToStringFormat(CTTIMEMS Time, pTEXT Mask, pTEXT pStr);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringFormatToDateTime(pTEXT pStr, pTEXT Mask, pCTDATETIME pDateTime, CTDATE julianbase);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeToStringFormat(CTDATETIME DateTime, pTEXT Mask, pTEXT pStr, CTDATE julianbase);
ctdbEXPORT NINT ctdbDECL _getDateTimeComponent(pTEXT pStr, pTEXT Mask, TEXT Component);
ctdbEXPORT NINT ctdbDECL _setDateTimeComponent(ULONG Value, pTEXT pStr, pTEXT Mask, TEXT Component);
ctdbEXPORT CTBOOL ctdbDECL _ctdbDateTimeStringFormatSort(pTEXT mask);

/*^****************************************************************************\
*
*   CTDB C API Time functions
*
\*****************************************************************************/
ctdbEXPORT CTDBRET ctdbDECL ctdbTimeCheck(NINT hour, NINT minute, NINT second);
ctdbEXPORT CTDBRET ctdbDECL ctdbTimeCheckMsec(NINT hour, NINT minute, NINT second, NINT millisec);
ctdbEXPORT CTDBRET ctdbDECL ctdbTimePack(pCTTIME pTime, NINT hour, NINT minute, NINT second);
ctdbEXPORT CTDBRET ctdbDECL ctdbTimeUnpack(CTTIME Time, pNINT hour, pNINT minute, pNINT second);
ctdbEXPORT CTDBRET ctdbDECL ctdbTimePackMsec(pCTTIMEMS pTime, NINT hour, NINT minute, NINT second, NINT millisec);
ctdbEXPORT CTDBRET ctdbDECL ctdbTimeUnpackMsec(CTTIMEMS Time, pNINT hour, pNINT minute, pNINT second, pNINT millisec);
ctdbEXPORT CTDBRET ctdbDECL ctdbTimeToString(CTTIME Time, CTTIME_TYPE TimeType, pTEXT pStr, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringToTime(pTEXT pStr, CTTIME_TYPE TimeType, pCTTIME pTime);
ctdbEXPORT CTDBRET ctdbDECL ctdbTimeMsecToString(CTTIMEMS Time, CTTIME_TYPE TimeType, pTEXT pStr, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringToTimeMsec(pTEXT pStr, CTTIME_TYPE TimeType, pCTTIMEMS pTime);
ctdbEXPORT NINT ctdbDECL ctdbGetHour(CTTIME Time);
ctdbEXPORT NINT ctdbDECL ctdbGetMinute(CTTIME Time);
ctdbEXPORT NINT ctdbDECL ctdbGetSecond(CTTIME Time);
ctdbEXPORT CTTIME_TYPE ctdbDECL ctdbGetDefTimeType(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbSetDefTimeType(CTHANDLE Handle, CTTIME_TYPE TimeType);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrentTime(pCTTIME pTime);

/*^****************************************************************************\
*
*   CTDB C API DateTime functions
*
\*****************************************************************************/
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimePack(pCTDATETIME pDateTime, NINT year, NINT month, NINT day, NINT hour, NINT minute, NINT second);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeUnpack(CTDATETIME DateTime, pNINT pYear, pNINT pMonth, pNINT pDay, pNINT pHour, pNINT pMinute, pNINT pSecond);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimePackMsec(pCTDATETIME pDateTime, NINT year, NINT month, NINT day, NINT hour, NINT minute, NINT second, NINT millisec);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeUnpackMsec(CTDATETIME DateTime, pNINT pYear, pNINT pMonth, pNINT pDay, pNINT pHour, pNINT pMinute, pNINT pSecond, pNINT pMillisec);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeGetDate(CTDATETIME DateTime, pCTDATE pDate);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeGetTime(CTDATETIME DateTime, pCTTIME pTime);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeGetTimeMsec(CTDATETIME DateTime, pCTTIMEMS pTime);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeSetDate(pCTDATETIME pDateTime, CTDATE Date);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeSetTime(pCTDATETIME pDateTime, CTTIME Time);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeSetTimeMsec(pCTDATETIME pDateTime, CTTIMEMS Time);
ctdbEXPORT CTDBRET ctdbDECL ctdbDateTimeToString(CTDATETIME DateTime, CTDATE_TYPE DateType, CTTIME_TYPE TimeType, pTEXT pStr, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringToDateTime(pTEXT pStr, pCTDATETIME pDateTime, CTDATE_TYPE DateType, CTTIME_TYPE TimeType);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrentDateTime(pCTDATETIME pDateTime);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrentDateTimeUTC(pCTDATETIME pDateTime);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrentTimestamp(pULONG8 timestamp);

/*^****************************************************************************\
*
*   CTDB C API Money functions
*
\*****************************************************************************/
ctdbEXPORT CTDBRET ctdbDECL ctdbMoneyToLong(CTMONEY money, pLONG pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbLongToMoney(CTSIGNED value, pCTMONEY pMoney);
ctdbEXPORT CTDBRET ctdbDECL ctdbMoneyToFloat(CTMONEY money, pCTFLOAT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbFloatToMoney(CTFLOAT value, pCTMONEY pMoney);
ctdbEXPORT CTDBRET ctdbDECL ctdbMoneyToString(CTMONEY money, pTEXT pStr, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringToMoney(pTEXT pStr, pCTMONEY pMoney);
ctdbEXPORT CTDBRET ctdbDECL ctdbMoneyAdd(CTMONEY left, CTMONEY right, pCTMONEY pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbMoneySub(CTMONEY left, CTMONEY right, pCTMONEY pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbMoneyMul(CTMONEY left, CTMONEY right, pCTMONEY pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbMoneyDiv(CTMONEY left, CTMONEY right, pCTMONEY pResult);
ctdbEXPORT NINT ctdbDECL ctdbMoneyCmp(CTMONEY left, CTMONEY right);
ctdbEXPORT CTMONEY ctdbDECL ctdbMoneyAbs(CTMONEY left);

/*^****************************************************************************\
*
*   CTDB C API Blob functions
*
\*****************************************************************************/
ctdbEXPORT pCTBLOB ctdbDECL ctdbBlobAlloc(VRLEN size);
ctdbEXPORT VOID ctdbDECL ctdbBlobFree(pCTBLOB pBlob);
ctdbEXPORT pVOID ctdbDECL ctdbBlobGetData(pCTBLOB pBlob);
ctdbEXPORT VRLEN ctdbDECL ctdbBlobGetSize(pCTBLOB pBlob);
ctdbEXPORT CTDBRET ctdbDECL ctdbBlobSet(pCTBLOB pBlob, cpVOID buffer, VRLEN size);
ctdbEXPORT NINT ctdbDECL ctdbBlobCmp(pCTBLOB left, pCTBLOB right);
ctdbEXPORT CTDBRET ctdbDECL ctdbBlobClear(pCTBLOB pBlob);

/*^****************************************************************************\
*
*   CTDB C API Big Integer functions
*
\*****************************************************************************/
ctdbEXPORT CTDBRET ctdbDECL ctdbBigIntToLong(CTBIGINT value, pLONG pLong);
ctdbEXPORT CTDBRET ctdbDECL ctdbBigIntToULong(CTBIGINT value, pULONG pLong);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnsignedBigIntToLong(CTUBIGINT value, pLONG pLong);
ctdbEXPORT CTDBRET ctdbDECL ctdbLongToBigInt(LONG value, pCTBIGINT pBigInt);
ctdbEXPORT CTDBRET ctdbDECL ctdbLongToUnsignedBigInt(LONG value, pCTUBIGINT pUBigInt);
ctdbEXPORT CTDBRET ctdbDECL ctdbULongToBigInt(ULONG value, pCTBIGINT pBigInt);
ctdbEXPORT CTDBRET ctdbDECL ctdbULongToUnsignedBigInt(ULONG value, pCTUBIGINT pUBigInt);
ctdbEXPORT CTDBRET ctdbDECL ctdbBigIntToFloat(CTBIGINT value, pCTFLOAT pFloat);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnsignedBigIntToFloat(CTUBIGINT value, pCTFLOAT pFloat);
ctdbEXPORT CTDBRET ctdbDECL ctdbFloatToBigInt(CTFLOAT value, pCTBIGINT pBigInt);
ctdbEXPORT CTDBRET ctdbDECL ctdbFloatToUnsignedBigInt(CTFLOAT value, pCTUBIGINT pUBigInt);
ctdbEXPORT CTDBRET ctdbDECL ctdbBigIntToString(CTBIGINT value, pTEXT pStr, NINT size);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnsignedBigIntToString(CTUBIGINT value, pTEXT pStr, NINT size);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringToBigInt(pTEXT pStr, pCTBIGINT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringToUnsignedBigInt(pTEXT pStr, pCTUBIGINT pValue);

/*^****************************************************************************\
*
*   CTDB C API Currency functions
*
\*****************************************************************************/
ctdbEXPORT CTDBRET ctdbDECL ctdbMoneyToCurrency(CTMONEY money, pCTCURRENCY pCurrency);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyToMoney(CTCURRENCY currency, pCTMONEY pMoney);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyToLong(CTCURRENCY currency, pCTSIGNED pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbLongToCurrency(CTSIGNED value, pCTCURRENCY pCurrency);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyToBigInt(CTCURRENCY currency, pCTBIGINT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyToUnsignedBigInt(CTCURRENCY currency, pCTUBIGINT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbBigIntToCurrency(CTBIGINT value, pCTCURRENCY pCurrency);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnsignedBigIntToCurrency(CTUBIGINT value, pCTCURRENCY pCurrency);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyToFloat(CTCURRENCY currency, pCTFLOAT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbFloatToCurrency(CTFLOAT value, pCTCURRENCY pCurrency);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyToString(CTCURRENCY currency, pTEXT pStr, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringToCurrency(pTEXT pStr, pCTCURRENCY pCurrency);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyAdd(CTCURRENCY left, CTCURRENCY right, pCTCURRENCY pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencySub(CTCURRENCY left, CTCURRENCY right, pCTCURRENCY pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyMul(CTCURRENCY left, CTCURRENCY right, pCTCURRENCY pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyDiv(CTCURRENCY left, CTCURRENCY right, pCTCURRENCY pResult);
ctdbEXPORT NINT ctdbDECL ctdbCurrencyCmp(CTCURRENCY left, CTCURRENCY right);
#ifdef ctN8
ctdbEXPORT CTCURRENCY ctdbDECL ctdbCurrencyAbs(CTCURRENCY value);
#endif
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyRound(pCTCURRENCY value, NINT scale);

/*^****************************************************************************\
*
*   CTDB C API numeric functions
*
\*****************************************************************************/

ctdbEXPORT CTDBRET ctdbDECL ctdbMoneyToNumber(CTMONEY money, pCTNUMBER pNumber);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberToMoney(pCTNUMBER pNumber, pCTMONEY pMoney);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberToLong(pCTNUMBER pNumber, pLONG pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbLongToNumber(LONG value, pCTNUMBER pNumber);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberToBigInt(pCTNUMBER pNumber, pCTBIGINT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberToUnsignedBigInt(pCTNUMBER pNumber, pCTUBIGINT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbBigIntToNumber(CTBIGINT value, pCTNUMBER pNumber);
ctdbEXPORT CTDBRET ctdbDECL ctdbUnsignedBigIntToNumber(CTUBIGINT value, pCTNUMBER pNumber);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberToCurrency(pCTNUMBER pNumber, pCTCURRENCY pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbCurrencyToNumber(CTCURRENCY value, pCTNUMBER pNumber);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberToFloat(pCTNUMBER pNumber, pCTFLOAT pValue);
ctdbEXPORT CTDBRET ctdbDECL ctdbFloatToNumber(CTFLOAT value, pCTNUMBER pNumber);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberToString(pCTNUMBER pNumber, pTEXT pStr, VRLEN size);
ctdbEXPORT CTDBRET ctdbDECL ctdbStringToNumber(pTEXT pStr, pCTNUMBER pNumber);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberAdd(pCTNUMBER pLeft, pCTNUMBER pRight, pCTNUMBER pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberSub(pCTNUMBER pLeft, pCTNUMBER pRight, pCTNUMBER pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberMul(pCTNUMBER pLeft, pCTNUMBER pRight, pCTNUMBER pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberDiv(pCTNUMBER pLeft, pCTNUMBER pRight, pCTNUMBER pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberZero(pCTNUMBER pNumber);
ctdbEXPORT CTBOOL ctdbDECL ctdbIsNumberZero(pCTNUMBER pNumber);
ctdbEXPORT NINT ctdbDECL ctdbNumberCmp(pCTNUMBER pLeft, pCTNUMBER pRight);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberAbs(pCTNUMBER pSource, pCTNUMBER pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberNegate(pCTNUMBER pSource, pCTNUMBER pResult);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberCopy(pCTNUMBER pDest, pCTNUMBER pSource);
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberRound(pCTNUMBER num, NINT scale);
#ifdef ctFeatABL
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberTruncate(pCTNUMBER num, NINT scale);
#endif
ctdbEXPORT CTDBRET ctdbDECL ctdbNumberGetDecimal(pCTNUMBER data, pNINT digit_before, pNINT digit_after);

/*^****************************************************************************\
*
*   CTDB C API RestulSet functions
*
\*****************************************************************************/
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetResultSetHandle(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAllocateResultSet(CTHANDLE Handle, pTEXT ResSetName);
ctdbEXPORT VOID ctdbDECL ctdbFreeResultSet(CTHANDLE Handle);
ctdbEXPORT CTDBRET ctdbDECL ctdbResultSetOnOff(CTHANDLE Handle, CTHANDLE RecordHandle, 
                                               CTBOOL OnOffFlag, CTBOOL AutoSortFlag, 
                                               CTLOC_MODE LocateMode);
ctdbEXPORT CTHANDLE ctdbDECL ctdbGetResultSetByName(CTHANDLE Handle, pTEXT ResSetName);

ctdbEXPORT CTHANDLE ctdbDECL ctdbGetResultSetCriHandle(CTHANDLE Handle);
ctdbEXPORT CTHANDLE ctdbDECL ctdbAddCriteria(CTHANDLE Handle, CTHANDLE FieldHandle, 
                                             pTEXT LowValue, pTEXT HighValue, NINT CriteriaOp);
ctdbEXPORT CTDBRET ctdbDECL ctdbRemoveCriteria(CTHANDLE Handle, CTHANDLE CriteriaHandle);
ctdbEXPORT CTDBRET ctdbDECL ctdbUpdateCriteria(CTHANDLE Handle, pTEXT LowValue, pTEXT HighValue);

/*^****************************************************************************\
*
*   CTDB C API HELLO WORLD - FairCom Internal Code Placement Tutorial
*
\*****************************************************************************/
ctdbEXPORT CTDBRET ctdbDECL ctdbHelloWorld(pTEXT HelloFileName,pTEXT HelloTextData,NINT HelloNintData, ULONG HelloULongData, CTFLOAT HelloFloatData); /* CTDB HELLO WORLD */
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTDB C merge dictionaries API.
*
\*****************************************************************************/
#ifdef CTDB_DICTMERGE_API
ctdbEXPORT CTDBRET ctdbDECL ctdbMergeDatabaseDictionary (CTHANDLE src, CTHANDLE dst, mergeFunPtr mrgfun, logFunPtr logfun);
ctdbEXPORT CTDBRET ctdbDECL ctdbMergeSessionDictionary (CTHANDLE src, CTHANDLE dst, mergeFunPtr mrgfun, logFunPtr logfun);
#endif /*CTDB_DICTMERGE_API*/
/*~****************************************************************************/

/* c-treeACE SQL import API function prototype */
extern NINT ctSQLImportTable(pCTSQLIMPOPTS pctsqlimpopts);

/*^****************************************************************************\
*
*   CTDB C API Partition Admin Support
*
\*****************************************************************************/
ctdbEXPORT CTDBRET ctdbDECL ctdbPartAdminByName(CTHANDLE handle,pTEXT partname,CTPART_MODE_E partmode,pCOUNT partstatus);
ctdbEXPORT CTDBRET ctdbDECL ctdbPartAdminByKey(CTHANDLE handle,pVOID keyval,CTPART_MODE_E partmode,pCOUNT partstatus);
ctdbEXPORT CTDBRET ctdbDECL ctdbPartAdminByNumber(CTHANDLE handle,LONG partno,CTPART_MODE_E partmode,pCOUNT partstatus);
/*~****************************************************************************/

ctdbEXPORT CTDBRET ctdbDECL ctdbFirstSubrec(pCTDBRECORD pRecord);
ctdbEXPORT CTDBRET ctdbDECL ctdbNextSubrec(pCTDBRECORD pRecord);
ctdbEXPORT CTDBRET ctdbDECL ctdbNthSubrec(pCTDBRECORD pRecord,NINT subrecno);
struct PTREE_S; /* forward declaration */
#ifdef ctN8
ctdbEXPORT LONG8 ctdbptGetInteger( struct PTREE_S* Tree );
#endif
ctdbEXPORT struct PTREE_S* ctdbptPutSet( VRLEN Value );
ctdbEXPORT VOID ctdbptFreeMem( pVOID Memory );
ctdbEXPORT struct PTREE_S* ctdbptCopyIntoSet(struct PTREE_S* set, struct PTREE_S* node);
ctdbEXPORT VOID ctdbptDestroy( struct PTREE_S* Tree );
ctdbEXPORT struct PTREE_S* ctdbptAddToExprList(struct PTREE_S* List, struct PTREE_S* expr);
ctdbEXPORT struct PTREE_S* ctdbptPutNode( COUNT NodeType, COUNT ExprType, struct PTREE_S* Left, struct PTREE_S* Right );
ctdbEXPORT struct PTREE_S* ctdbptPutInteger( LONG8 Value );
ctdbEXPORT COUNT ctdbptGetExprType( struct PTREE_S* Tree );
ctdbEXPORT struct PTREE_S* ctdbptPutTime(CTTIME Value);
ctdbEXPORT struct PTREE_S* ctdbptPutTimeMsec(CTTIMEMS Value);
ctdbEXPORT struct PTREE_S* ctdbptPutStamp(CTDATETIME Value);
ctdbEXPORT struct PTREE_S* ctdbptPutText( pTEXT Value, VRLEN len, NINT byref );
ctdbEXPORT struct PTREE_S* ctdbptPutNumber(pCTNUMBER Value);
ctdbEXPORT struct PTREE_S* ctdbptPutDate(CTDATE Value);
ctdbEXPORT struct PTREE_S* ctdbptPutField( COUNT NodeType, COUNT ExprType, UINT Value );
ctdbEXPORT struct PTREE_S* ctdbptPutRecinfo(CTHANDLE table, pTEXT names, struct PTREE_S* Right);
ctdbEXPORT struct PTREE_S* ctdbptPutNULL();
ctdbEXPORT struct PTREE_S* ctdbptPutUTF16(pTEXT Value, VRLEN bytes_len, NINT byref);

#ifdef __cplusplus
}
#endif /* ~__cplusplus */
#endif /* ~_CTDBSDK_H_ */

#ifdef ctPortWINKE_CLIENT
#ifdef ctdbCTPERM
#include "ctkifc.h"
#undef ctDECLH
#include "ctdecl.h"
#endif
#endif

#ifdef ctdbCTPERM
/* When compiling c-treeDB core code, we define BOOL so that using it causes the
compilation to fail. In our core code we want to use CTBOOL instead of BOOL
because BOOL is typically defined only on Windows systems. */
#define BOOL _ERROR__USE_CTBOOL_INSTEAD_OF_BOOL
#endif

/* end of ctdbsdk.h */

