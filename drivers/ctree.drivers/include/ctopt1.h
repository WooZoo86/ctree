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

#ifndef ctOPT1H
#define ctOPT1H

/*^**********************************/
/* OEM DEFINES 			    */

#include "ct_oem.h"

/* END OEM DEFINES 			    */
/*~**********************************/

#include "ctvers.h"

/*^***********************************/
#ifdef ctPortBATA
#define PWH 32 /* set password hash length to 32 because only SHA-256 is supported */
#ifndef CBPTR32
#define CBPTR32 /* CBPTR data type is 32 bit */
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortSOFTWAREAG
#define NO_ctFeatHTTPD
#define NO_ctFeatEMB_AGENT
#endif
/*~***********************************/

/*^**********************************/
/* SPECIAL FEATURE DEFINES	    */
/* 	(affect ctport.h)	    */

/*--------------------------------------------------------------*/
/* ctFeat6BT enables 6-byte transaction numbers. This extends   */
/* the likely lifetime related to transaction number overflow	*/
/* by a factor of 65536. For example, a 6-byte transaction	*/
/* number permits two-thousand years of 1000 transactions per	*/
/* second.							*/
/*								*/
/* ctFeat6BT requires ctHUGEFILE support.			*/
/*								*/
/* ctDBGanl  has not been updated for 6BT			*/
/* DBGbufage has not been updated for 6BT			*/
/* dbgHGHTRN has not been updated for 6BT			*/
/*								*/
/* DEFAULT:  ctFeat6BT is on					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeat6BT
#ifndef NO_ctHUGEFILE
#define ctFeat6BT
/*
** ctTEST6BT permits the starting transaction
** number to be manipulated, say to ensure crossing over the
** 4-byte transaction number.
*/
#define NO_ctTEST6BT /* for Test Only */
#ifndef NO_ctTEST6BT
#define ctTEST6BT	0xffffff00
#endif
#endif
#endif
/*~*******************/


/*--------------------------------------------------------------*/
/* ctFeatOLD_BCD_COMPAT						*/
/*								*/
/* DEFAULT: ctFeatOLD_BCD_COMPAT is off				*/
/*--------------------------------------------------------------*/

#ifdef ctPortLIFEPRO
#define ctFeatOLD_BCD_COMPAT	/* They use old BCD */
#endif
/*~*******************/


/*--------------------------------------------------------------*/
/* ctFeatEVENTLOG_VER2						*/
/*								*/
/* DEFAULT: ctFeatEVENTLOG_VER2 is on for V8 (ctFeat6BT), else	*/
/* it defaults off.						*/
/*--------------------------------------------------------------*/
#ifdef ctFeat6BT
#ifndef ctFeatEVENTLOG_VER2
#define ctFeatEVENTLOG_VER2
#endif
#endif
/*~*******************/


/*^*******************/
/*
** ctFeatCAMOsdkKEYWORD enables the use of the advanced encryption.
** This feature is supported by the ADVANCED_ENCRYPTION server configuration
** keyword and by the cmosdksup configuration field in bound server mode.
**
** DEFAULT:  ctFeatCAMOsdkKEYWORD is activated for server, bound server,
** client, and FairCom internal utility compilation.
*/
/*~*******************/
#ifndef ctNO_CAMO
#ifndef NO_ctCAMOsdk
#ifdef ctSRVR
#define ctFeatCAMOsdkKEYWORD
#define ctCAMOsdk 	/* FairCom Encryption SDK */
#endif
#ifdef ctBNDSRVR
#define ctFeatCAMOsdkKEYWORD
#define ctCAMOsdk 	/* FairCom Encryption SDK */
#endif
#ifdef ctPortFAIRCOM_INTERNAL_GEN
#define ctFeatCAMOsdkKEYWORD
#define ctCAMOsdk 	/* FairCom Encryption SDK */
#endif
#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctCLISIDE) || defined(ctSQLMTFPG)
#define ctCAMOsdk 	/* FairCom Encryption SDK */
#endif
#endif /* ~NO_ctCAMOsdk */
#endif /* ~ctNO_CAMO */
/*~*******************/

/*^*******************/
/*
** ctFeatREBUILD_OPT enables the use of rebuild enhancements, including
** the MAX_K_TO_USE and MAX_HANDLES server configuration keywords.
**
** DEFAULT:  ctFeatREBUILD_OPT is enabled only when
** ct_V90_GENERATION is defined.
*/
#ifdef ct_V90_GENERATION
#define ctFeatREBUILD_OPT
#endif
/*~*******************/


/*^*******************/
/* Support rebuild callback in all operational models */
#define RB_CALLBACK

/*~*******************/


/*^*******************/
/*
** ctFeatCFG_SCALE enables support for specifying a scaling factor
** of KB, MB, or GB for c-tree Server configuration options that accept
** numeric values.
**
** DEFAULT:  ctFeatCFG_SCALE is activated
*/
/*~*******************/
#ifdef ctSRVR
#define ctFeatCFG_SCALE
#endif
/*~*******************/

/*----------------------------------------------------------------------------
  ctFeatMAXFILE32 allows support for opening more than 32767 files.

  Enabled in v11.9.0 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,0)
#ifndef NO_ctFeatMAXFILE32
#define ctFeatMAXFILE32 /* support opening more than 32767 files */
#endif
#endif

/* check if the specified file number is in the range of a signed two-byte integer */
#define FILNO_IN_COUNT_RANGE(filno) ((filno) >= -32768 && (filno) <= 32767)

/*^*******************/
/*
** ctFeatSRVR_SDK_CSAPI_DEMOAPPSERVER enables support for the Demo Application
** Server that used the High-Speed Pipe mainline to illustrate the use of an
** application layer with the FairCom Advanced Core Engine. This was originally
** implemented with the JQL DLL as a samples for UPS_BRUCE.
** DEFAULT:  ctFeatSRVR_SDK_CSAPI_DEMOAPPSERVER is NOT activated
*/
/*~*******************/
#ifdef  ctFeatSRVR_SDK_CSAPI_DEMOAPPSERVER 	/* Defined by mtree in ctoptn.h when DemoAppServer switch is used */
#define ctFeatSRVR_SDK_CSAPI
#define ctFeatCUSTSRVMAIN			/* Server is launched via the ctThrdInit call by Application Server layer */
#endif
/*~*******************/

/*----------------------------------------------------------------------------
  ctFeatMTFPG_LOKCNFunqid corrects the generation of unique file IDs in
  multi-threaded FPUTFGET mode.

  Default: ctFeatMTFPG_LOKCNFunqid is ON.
----------------------------------------------------------------------------*/
#ifndef NO_ctFeatMTFPG_LOKCNFunqid
#define ctFeatMTFPG_LOKCNFunqid
#endif

/* END SPECIAL FEATURE DEFINES	    */
/*~**********************************/


/*~**********************************/
/* START OEM  FEATURE DEFINES	    */

/*^***********************************/



/*^***********************************/
#ifdef ctPortDHARMA_ATREE
/*^*******************/
/*
** Special needs for Dhrama source package.
*/
/*~*******************/
#ifndef NOT_LICENSED_FOR_REMOTE_CONN
#define NOT_LICENSED_FOR_REMOTE_CONN		23 /* needed by ctscfg.c for ctautlic.h not included */
#endif
#endif /* ctPortDHARMA_ATREE */
/*~***********************************/


/*^***********************************/
#ifdef ctPortGEOLOGIC
/*
Deactivate ctFeatDAR - turn off support for Direct Access Resources This is to
allow the files to be backward compatible with V9 files
*/
#define NO_ctFeatDAR 
#endif
/*~***********************************/


/*^***********************************/
#ifdef ctPortLIFEPRO

#ifdef ctCLIENT			/* c-tree Plus Client */
#ifndef ctMAXFIL
#define ctMAXFIL 3000
#endif
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif

#ifdef ctSRVR			/* FairCom Server */
#define ctDBGanl	15000	/* Debug Circular Buffer for abort node list */
#define MAX_HANDLES 100
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#define ctSYNC_DELAY


/********************/
/*
Prior to 11/13/2001 when a LIFEPRO server or ctree was compiled
ctPortDAC was not defined so CT_SQLBCD had value of 108. When they
stored a DODA that a field of type CT_SQLBCD the field type of 108
was stored in the resource.  Their ODBC CUSTOM DLL was also compiled
to expect CT_SQLBCD to value a value of 108.
*/
#define ctFeatOLD_BCD_COMPAT	/* They use old BCD */
/********************/

#endif /* ctSRVR */

#ifndef ctCLIENT		/* Stand Alone Single User c-tree Plus */
#ifndef ctSRVR
#ifdef ctSTDLIB
#define MAX_HANDLES 100
#define ctSYNC_DELAY
#ifndef ctMAXFIL
#define ctMAXFIL 3000
#endif
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif
#endif
#endif

#ifndef NO_ctHUGEFILE
#ifndef ctHUGEFILE
#define ctHUGEFILE
#endif
#ifndef ctHUGEFILEsegm
#define ctHUGEFILEsegm
#endif
#endif /* ~NO_ctHUGEFILE */

#endif /* ctPortLIFEPRO */
/*~***********************************/


/*^***********************************/
#ifdef  ctPortAPPMAT
#ifndef NO_ctFeatPARTITION_BY_TIMESTAMP_DAY
#define ctFeatPARTITION_BY_TIMESTAMP_DAY
#define ctFeatPARTITION_BY_TIMESTAMP_DAY_GMT
#ifdef ctPortWNT386
#define ctFeatWINDOWS_LOCAL_FILE_TIME
#endif
#endif
#ifdef ctSRVR
#define ctFeatVLEN_ERRretry
#endif
#endif
/*~***********************************/


/*^***********************************/
#ifdef ctPortTPROCSYS
#if _MSC_VER == 1200
#define NO_ctFeatAEK256 /* not supported with VC6 compiler */
#else
#define ctFeatAEK256 /* increases the strength of c-tree's advanced encryption */
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortATTACH2
#if _MSC_VER == 1200
#define NO_ctFeatAEK256 /* not supported with VC6 compiler */
#else
#define ctFeatAEK256 /* increases the strength of c-tree's advanced encryption */
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef  ctPortHKJC
#ifndef NO_ctFeatPARTITION_BY_TIMESTAMP_DAY
#define ctFeatPARTITION_BY_TIMESTAMP_DAY
#define ctFeatPARTITION_BY_TIMESTAMP_DAY_GMT
#ifdef ctPortWNT386
/* #define ctFeatWINDOWS_LOCAL_FILE_TIME */ /* RAB:110109-NOT YET */
#endif
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef 	ctPortPHARMA

#ifdef ctSRVR
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#ifdef ctPortFAIRCOM_INTERNAL_GEN
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#endif /* ctPortPHARMA */
/*~***********************************/


/*^***********************************/
#if (defined(ctPortACI) || defined(ctPortVISA))

#ifdef ctLOCLIB			/* Special encyption for command line utilities    */
/* #define ctFeatUTILdotSET */	/* Remember, we have 2 type of command line utility*/
/* #define ctCAMO */	        /* encyption methods: 1) Like the ctsrvr.set method*/
#define ctFeatSETTINGS		/* and 2) like the TCP/IP enrypt method 	   */
#endif				/* These setting are for 1). Needs ctLOCLIB 	   */
				/* Note that method 2) was the primary method intially used for ACI */
#ifdef  ctSRVR
#define ctMAXUSERS 2048
#define ctBEHAV_CMTLOK		/* ctBEHAV_CMTLOK supports implied read locks to ensure con-	*/
				/* sistent reads without explicit locks even when a transaction	*/
				/* is transferring preimages to the file system.		*/
#define ctFeatSHUTDOWN_DIAG
#endif

#if defined(ctCLIENT) || defined(ctMTCLIENT)
#define ctFeatNONBLK_SOCKIO
#endif

#ifdef ctSRVR
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#ifdef ctPortFAIRCOM_INTERNAL_GEN
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */

#define ctCPU_COUNT_MODE ctGET_PHYSICAL_CPUS /* Count physical CPUs */

#endif
/*~***********************************/


/*~***********************************/
#ifdef ctPortFAIRISAAC
#ifdef MULTITRD
#define ctBEHAV_THREADSAFE
#endif
#endif /* ctPortFAIRISAAC */
/*^***********************************/

/*~***********************************/
#ifdef ctPortESA
#ifdef FPUTFGET

#ifdef  ctMAXFIL
#undef  ctMAXFIL
#endif
#define ctMAXFIL 10000 	/* maximum number of c-tree files */

#ifdef MAXVFIL
#undef MAXVFIL
#endif
#define MAXVFIL 500 	/* maximum number of system file descriptors */

#define NO_IDXENT  /* disable index entries count */
#define ctFeatINC_ADDREC /* uneven node splitting during record addition*/
#endif
#endif /* ~ctPortESA */
/*^***********************************/


/*^***********************************/
#ifdef ctPortSTI
/* enable new transaction mode rev 3878 */
#define ctFeatKEEP_XFREED

/*
** Defer calls to data record filter callback functions during file open and
** close operations until the end of the operation.
*/
#ifdef ctSRVR
#define ctFeatDATFLT_DEFER_CALLBACK
/* #define ctDBGSEMCNT */ /* rab: 120311: deactivate debug option for production */
/* #define ctDBGSEMrecur */
#endif

/*
** Allow only the ADMIN account to change the settings of ADMIN group members.
** (Any user account can still change its own description and password.)
*/
#define ctFeatADMIN_SECURITY

#if defined(CTBOUND) && !defined(MULTITRD) && !defined(ctPortFAIRCOM_INTERNAL_GEN)
/* Standalone mode compile for STI */
#define ctPortSTI_STANDALONE
#endif

#ifdef ctPortSTI_STANDALONE

/*
** Customizations for standalone mode for STI
*/

/* Set status log name */
#define CTSTATUSname	"STCTREE.LOG"

#endif /* ctPortSTI_STANDALONE */

/* Set temporary filename extension */
#define CT_TMPNAME_EXT ".TMP"

#if defined(ctSRVR) || defined(ctPortFAIRCOM_INTERNAL_GEN) || defined(FPUTFGET)
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#define ctFeatAEKato
#endif

#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortEMPIRE
#define NO_ctFEAT_STRONGSIGN /* relax string sign enforcement in ctdbnet.h */
#endif
/*~***********************************/

/*^***********************************/
#if (defined(ctPortTLT) || defined(ctPortHCL))
#define NO_ctFEAT_STRONGSIGN /* relax string sign enforcement in ctdbnet.h */
/* #define ctFeatJEFFSCOMCODE */ /* 171126: Rab took out for V11.5 */
#define ctPARTITION
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#define ctBEHAV_BAT_LOK_ONE
/* Use c-tree's memory suballocator for allocations up to 64 KB */
#define PI_UNIT 512
/* Enable c-tree reader/writer lock support for Windows */
#define ctFeatRWLOCKctree
#endif
/*~***********************************/


/*^***********************************/
#ifdef ctPortCOVE
#define ctFeatOLD_BCD_COMPAT	/* They use old BCD */
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortSOFTWAREAG_LEGACY
#define ctNO_CAMO
#endif
/*~***********************************/

/*^***********************************/
#ifdef  ctPortZEACOM
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif
/*~***********************************/

/*^***********************************/
#ifdef  ctPortGTECH
#ifndef ctFeatNONADMINkeywords
#define ctFeatNONADMINkeywords
#endif
#endif
/*~***********************************/


/*^***********************************/
#if defined(ctCobolIS) || defined(ctCobolACU) || defined(ctCobolEXTFH) || defined(ctPortHBRTG)

#define ctFeatCOBOL

#if defined(ctCLIENT) || defined(ctLOCLIB) || defined(ctMTCLIENT)
#ifndef ctCUSTOM
#define ctCUSTOM
#endif
#endif

#ifdef  ctPortHBRTG
#define ctMAX_KEY_SEG		72	/* maximum key segments	*/
#endif

#ifndef MULTITRD
#ifndef ctMAX_DAT_KEY
#define ctMAX_DAT_KEY		128	/* maximum indices per data file	*/
#endif
#ifndef ctMAX_KEY_SEG
#define ctMAX_KEY_SEG		32	/* maximum key segments	*/
#endif
#endif
#ifndef ctMAXMEMB
#define	ctMAXMEMB		127	/* maximum additional index members	*/
#endif

#if defined(ctSRVR) || defined(ctCLIENT) || defined(ctMTCLIENT)
#ifndef ctFeatSHAREstate
#define ctFeatSHAREstate
#endif
#endif

#ifdef TRANPROC
#ifndef ctFeatKEEP_XFREED
#define ctFeatKEEP_XFREED
#endif
#endif

#endif
/*~***********************************/

/*^***********************************/
#ifdef  ctPortVERYANT

#ifndef ctCobolIS
#error ctPortVERYANT requires ctCobolIS
#endif

#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif
/*~***********************************/

/*^***********************************/
#ifdef  ctPortMICROFOCUS
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */

#ifndef ctCobolEXTFH
#error ctPortMICROFOCUS requires ctCobolEXTFH
#endif

#endif
/*~***********************************/

/*^***********************************/
#ifdef  ctPortCGM
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif
/*~***********************************/


/*^***********************************/
#ifdef  ctPortCGMFRIE
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif
/*~***********************************/

/*^***********************************/
#ifdef  ctPortIMAGENOW
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */

#ifdef MULTITRD
#define CTDB_ITIM_RETRY	/* Retry for record read errors ITIM_ERR and FFLT_ERR	*/
#define CTDB_MINIMUM_RECORD_BUFFER_SIZE 1024 /* Minimum size for c-treeDB record buffer */
#define ctDIAGdlokERR /* Enable DLOK_ERR diagnostics */
#endif

#endif
/*~***********************************/

/*^***********************************/
#ifdef  ctPortDRBOOKMAN
#define ctPADDING		'\0' /* override c-tree's PADDING definition */
#ifdef  ctPortMACOSX
#define ctPortDRBOOKOSX
#endif
/* Enable support for the file transfer function. */
#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB) || defined(ctSRVR)
#define ctFeatTRANSFER_FILE
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortDSTINTL /* ctPortDSTINTL_ONLY_QUESTION */

#ifdef ctSRVR
#define ctFeatREBUILD_OPT
#define ctFeatDEFER_OPNTRAN
/* #define ctIOSEMA */
#endif

#ifndef ctLOCLIB    
#define ctPARTITION
#endif

#ifdef ctPortDSTINTL_PERFTEST
/* Compile-time options for DST performance test. */
#define ctDBGSEMBLK
#define ctDBGSEMCNT
#define ctDBGSEMTIM
#define ctIOSEMA
#define ctIOSEMAmemfile
#define ctFeatGNSEMAhsh
#define ctFeatSKIPaddwrk
#define ctFeatAVLISTnum
#define ctFeatDBSEMAhsh
#define ctFeatDALISTnum
#ifdef ctPortSOLARIS
#define ctFeatRWLOCK
#endif
#endif

/* Use c-tree Server's original cache logic. */
#define NO_ctFeat_V11_NewCache

#ifdef ctSRVR
/* We enable these two v11 index cache enhancements in order to gain the full
benefit of our leaf node read lock optimization: */
#define ctFeatDISTbufcnt	/* enable distributed computation of ctbufcnt */
#define ctFeatNoIdxPndgList	/* eliminate index cache pending list */
#endif

/* By default, disable flushing of dirty TRNLOG data pages. */
#define TRFLS_DAT_LIMIT_DEFAULT		-1

/* By default, disable flushing of dirty TRNLOG index buffers. */
#define TRFLS_IDX_LIMIT_DEFAULT		-1

/* Disable acquisition of log flush mutex in tlogbuf(). */
#define NO_ctBEHAV_TLOGBUF_LFLSEMA

#endif /* ctPortDSTINTL */
/*~***********************************/

/*^***********************************/
#ifdef ctPortTOPTECH
#ifdef ctSRVR
#define ctDBGupdflg	/* turns on monitoring of changes to a file's updflg */
#endif
#endif /* ctPortTOPTECH */
/*~***********************************/

/*^***********************************/
#ifdef ctPortSIEMENS

#ifdef ctSQLSRVR

/*
** Support acquiring low level automatic read locks on every record read that
** does not already have a lock. The lock is freed automatically after the
** record is read.
*/
#define ctBEHAV_READLOCK

/*
** Cause SQL clients to acquire low level automatic read locks for
** read operations that otherwise would not acquire a record lock.
*/
#define ctFeatSQL_AUTO_READ_LOCK

#endif /* ctSQLSRVR */

#ifdef ctSRVR
/*
** We turned off ctDBGclsfil because it can cause deadlocks when the
** CTSTATUS_SIZE option is used.
*/
/* #define ctDBGclsfil */
#define ctDBGfcbio
#endif

#endif /* ctPortSIEMENS */
/*~***********************************/

/*^***********************************/
#ifdef ctPortBENEFITPLAN			
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortGREENBOX			
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortHIKER		
#ifndef ctMAX_KEY_SEG
#define ctMAX_KEY_SEG		32	/* maximum key segments	*/
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortABACUS		
#ifndef ctMAX_KEY_SEG
#define ctMAX_KEY_SEG		32	/* maximum key segments	*/
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortDENTRIX
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#ifndef NO_ctFeatAEK256
#define ctFeatAEK256 			/* increases the strength of c-tree's advanced encryption */
#endif

#if defined(ctSRVR) || defined(ctPortFAIRCOM_INTERNAL_GEN) 
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#ifndef ctSQL_RSS_FPUTFGET /* FQL SQL FPUTFGET Storage System - NOT in FQL Server */
#define ctFeatAWS
#define ctFeatAWS_KEY_STORE
#endif
#endif

#ifndef ctFeatLOGONSEC
#define ctFeatLOGONSEC	/* Activate Secure Logon */
#endif

#endif /* ctPortDENTRIX */
/*~***********************************/


/*^***********************************/
#ifdef ctPortSTR
#ifndef ctSRVR
#define ctPADDING		((char)0x00) /* override c-tree's PADDING definition */
#define ctFIELD_DELIM		((char)0x07) /* override c-tree's var length field delimiter */
#endif

#ifdef ctSQLSRVR
#define CTDB_VARSTRTERM
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortYMF
#ifndef ctSQL_NOROWID
#define ctSQL_NOROWID			/* create tables by default without rowid field */
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortWILSHIRE
#ifndef ctMAX_KEY_SEG
#define ctMAX_KEY_SEG 32
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortTHOMSON
#ifndef CTDB_SUBRECORD
#define CTDB_SUBRECORD /* enable subrecord support */
#endif
#endif
/*~***********************************/


/* END OEM  FEATURE DEFINES	    */
/*~**********************************/

/*^**********************************/
/* File Format Indicators */
#define CT_V6	 0x0080			/* c-tree version 6.0		*/
#define CT_V7	 0x0090			/* c-tree version 7.0 (XHDR)	*/
#define CT_V8	 0x00a0			/* c-tree version 8.0 (6BTRAN)	*/
/*~**********************************/

/*^**********************************/
/* Command Line-Level Default Defines */
#ifdef ctSRVR
#ifndef NO_ctSYSQUE

/* All servers support Q'ing and Notification */
/* as of v8.14 commercial Gen 040824 */
#ifndef ctThrds
#define ctThrds
#endif
#ifndef ctSYSQUE
#define ctSYSQUE
#endif

#endif	/* ~NO_ctSYSQUE */
#endif 	/* ctSRVR */
/*~**********************************/

#define ctMAXFIL16 (30000 + ctTRN_FILES) /* maximum number of c-tree files for COUNT data type */

#ifdef ctFeatMAXFILE32
/* maximum number of files open at a time */
#define CT_MAX_OPEN_FILES 1000000
#else
/* maximum number of files open at a time */
#define CT_MAX_OPEN_FILES 32767
#endif

#ifdef ctFeatMAXFILE32
/* rename the c-tree initialization functions so we can detect application incompatibility */
#define CREISAM CREISAM4
#define CREISAMX CREISAMX4
#define INTISAM INTISAM4
#define INTISAMX INTISAMX4
#define INTREE INTREE4
#define INTREEX INTREEX4
#define OPNISAM OPNISAM4
#define OPNISAMX OPNISAMX4
#endif

/*^**********************************/
/*
** For FairCom utility compiles, set ctMAXFIL to a large value.
** Note that this code overrides the ctMAXFIL definition in ctoptn.h.
*/
#ifdef ctPortFAIRCOM_INTERNAL_GEN
#ifdef  ctMAXFIL
#undef  ctMAXFIL
#endif
#ifdef ctFeatMAXFILE32
#define ctMAXFIL (CT_MAX_OPEN_FILES + ctTRN_FILES) /* maximum number of c-tree files */
#else
#define ctMAXFIL (30000 + ctTRN_FILES) 	/* maximum number of c-tree files */
#endif
#endif
/*~**********************************/

/* We set ctMAXMEMB here because it's referenced in ctport.h */

#ifndef ctMAXMEMB
#define	ctMAXMEMB		127	/* maximum additional index members	*/
#endif

#define MAXMEMB		ctMAXMEMB


/*^*******************/
/*
** ctFeatIPv6 allows the c-tree Server to track IPv6 addresses in addition to IPv4.
**
** DEFAULT:  ctFeatIPv6 is activated for windows and linux.
** ctFeatIPv6 and ctFeatSQLIPv6 should be consistent. See ctsql_lib.h
** BE SURE TO MAINTAIN BOTH ctopt1.h and ctsql_lib.h 
*/
/*~*******************/
#if ( defined(ctPort_LINUX_KERNEL_V2_4) || defined(ctPortQNXRTP) )
#define NO_ctFeatIPv6
#endif

#ifndef NO_ctFeatIPv6
#ifndef NO_ctFeatSQLIPv6
#ifdef ctPortWIN32
#if _MSC_VER  >= 1500
#ifndef ctFeatIPv6
#define ctFeatIPv6		/* Handle IPv6 for current windows compilers */
#endif
#endif
#endif
#ifdef ctPortLINUX
#ifndef ctPortFREEBSD8
#if (defined(ctSRVR) || defined(ctSQLSRVR))
#ifndef ctFeatIPv6
#define ctFeatIPv6		/* Handle IPv6 for linux */		
#endif
#endif
#endif
#endif
#endif /* ~NO_ctFeatSQLIPv6 */
#endif /* ~NO_ctFeatIPv6 */
/*~***********************************/

/*^*******************/
/*
** ctFeatBlockCompression enables support for block level compression of files.
** ctFeatLZFileIoEnableHooks enables API hooking of Win32 APIs rather than #ifdef code changes to call Compressed APIs.
** seems to require compiling lzfileio with #define LZFILEIO_OPTION_ENABLE_WINAPIHOOK
*/
/*~*******************/

#ifndef NO_ctFeatBlockCompression
/* #define ctFeatBlockCompression */
#endif

#ifdef ctFeatBlockCompression
/* Use block compression functions rather than API hooks */
#define ctFeatBlockCompressionFuncs 
#endif

#endif /* ctOPT1H  */
/* end of ctopt1.h */
