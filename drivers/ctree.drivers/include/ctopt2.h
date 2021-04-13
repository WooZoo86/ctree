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

#ifndef ctOPT2H
#define ctOPT2H

/*^**********************************/
/* Activate ct_V90_GENERATION by default*/
#ifndef NO_ct_V90_GENERATION
#ifndef ct_V90_GENERATION
#define ct_V90_GENERATION
#endif
#endif
/*~**********************************/

/************************************/
#ifndef LOW_HIGH
#ifndef HIGH_LOW
One of these must be defined in ctcmpl.h
#endif
#endif

#ifndef PERC_H
#ifndef PERC_D
#ifndef PERC_HD
One of these must be defined in ctcmpl.h
#endif
#endif
#endif
/************************************/

/*^**********************************/

/*
** Alternative synchronization object
** strategies:
**		1) ctChkSownrMtx:    code permits redundant calls, uses
**		   sOWNR to check
**		2) ctChkSysThidMtx:  code permits redundant calls, uses
**		   system thread ID to check
**		3) ctNoRedundantMtx: code assumes no redundant calls
**		   (i.e., always makes request)
**
**		In the above, "to check" means that before attempting to
**		acquire the synchronization object, the ctxxxrqs() code
**		checks to see if the caller already holds the object. If so,
**		no system call is made, and the routine returns NO_ERROR.
**
**		Strategy #1 corresponds to the long standing way the code has
**		behaved (through August 2009). The other strategies are
**		designed to deal with issues caused by thread impersonation
**		where the sOWNR check is not sufficient.
**
**		ctSkipRedundantMtx (which may be turned on automatically)
**		causes known redundant calls to be skipped before the call
**		to ctxxxrqs() is made. This is a requirement for
**		ctNoRedundantMtx, and is turned on for this case. It will be
**		turned on for ctChkSysThidMtx unless it is explicitly
**		turned off by NO_ctSkipRedundantMtx. It may be turned on
**		for ctChkSownrMtx; but this modifies the behavior from the
**		long standing approach.
**
*/

/*
** ctNoRedundantMtx is enabled on all systems. The code assumes no
** redundant mutex calls exist and so the mutex request function always
** requests the mutex, regardless of the mutex owner's task ID.
*/
#ifndef NO_ctNoRedundantMtx
#define ctNoRedundantMtx
#endif

#ifdef ctChkSownrMtx
#undef ctChkSownrMtx
#endif

#ifdef ctNoRedundantMtx	/* code does not make redundant mutex calls	   */
#ifdef ctChkSysThidMtx	/* redundant calls are checked by system thread ID */
AT most one of these can be defined.
#endif
#endif

#ifndef ctNoRedundantMtx
#ifndef ctChkSysThidMtx
#define ctChkSownrMtx	/* redundant calls are checked by sOWNR		   */
#endif
#endif

#ifdef ctNoRedundantMtx
#define ctSkipRedundantMtx
#endif
#ifdef ctChkSysThidMtx
#ifndef NO_ctSkipRedundantMtx
#define ctSkipRedundantMtx
#endif
#endif


/*~**********************************/


#ifdef ctDBGstack

#define ctDBG_FNBcoverage

#ifdef ctPortWINKE

#define ct_retDBG
#define ctPREFNCapiALL	ctPREFNCstack
#define ctPOSTFNCapi	ctPOSTFNCstack

#ifdef __cplusplus
extern "C" {
#endif

extern NINT ctPREFNCstack(NINT fn,NINT filno);
extern VOID ctPOSTFNCstack(NINT fn,NINT filno,NINT errcod);

#ifdef __cplusplus
}
#endif

#else

#define ct_retDBG
#define ctPREFNCapiALL	ctPREFNCstack
#define ctPOSTFNCapi	ctPOSTFNCstack

#ifdef __cplusplus
extern "C" {
#endif

extern NINT ctPREFNCstack(NINT fn,NINT filno);
extern VOID ctPOSTFNCstack(NINT fn,NINT filno,NINT errcod);

#ifdef __cplusplus
}
#endif

/* #undef ctDBGstack	 stack debugging only supported for WINKE */

#endif
#endif


/*^*****************************************************************/
/* Macros to hook into function return			********** */
#define RNM(nn)		 nn				/*	   */
#ifdef ct_retDBG					/*    hook */
extern  NINT dbgret(NINT nn);				/*    hook */
#define ct_ret_void(nn) {dbgret(nn); return;}		/*    hook */
#define ct_ret(nn,rc)	{dbgret(nn); return(rc);}	/*    hook */
#else							/* no hook */
#define ct_ret_void(nn) return;				/* no hook */
#define ct_ret(nn,rc)	return(rc);			/* no hook */
#endif							/* no hook */
/* end of function return hooks				********** */
/*~*****************************************************************/

/*^*****************************************************************/
/* ctdmpstack() locale codes                            ********** */
#define DMPSTACK_EXIT			-1
#define DMPSTACK_REQUEST_TIME_ALERT	10001
#define DMPSTACK_RELBUF_UPDATE		10002
#define DMPSTACK_PTADMIN_PURGE_FAIL	10003
#define DMPSTACK_UNOD_ERR		10004
#define DMPSTACK_SEMCLR			10005
#define DMPSTACK_CTEXCEPTION		10006
#define DMPSTACK_CTDBSETERROR		10007
#define DMPSTACK_BPF			10008
#define DMPSTACK_PCRP_ERR		10009
#define DMPSTACK_KLNK_ERR		10010
#define DMPSTACK_QILK_PNUL_ERR		10011
#define DMPSTACK_SQL_PANIC		10012
#define DMPSTACK_ADD_MARK_HOLDTRAN	10013
#define DMPSTACK_WRTNOD_BAD_MARK	10014
#define DMPSTACK_SET_FILE_CORRUPT	10015
#define DMPSTACK_HEAP_FAULT		10016
#define DMPSTACK_FALG_ERR		10017
#define DMPSTACK_DMAP_ERR		10018
#define DMPSTACK_RVNUM_STILL_SET	10019
#define DMPSTACK_WIN_EXCEPTION_HANDLER  10020
#define DMPSTACK_POPN_ERR		10021
/* end of ctdmpstack() locale codes			********** */

/* ctdmpstackxtd option bits */
#define DMPSTACKXTD_OPT_DEFAULT 0 /* Use STACK_DUMP default */
#define DMPSTACKXTD_OPT_FULL    0x00000001 /* prefer full dump (windows only) */

/* STACK_DUMP values */
#define DMPSTACK_DISABLED   0 /* all stack generation disabled */
#define DMPSTACK_STACK_ONLY 1/* ignores DMPSTACKXTD_OPT_FULL */
#define DMPSTACK_CONTEXT    2 /* use DMPSTACKXTD_OPT setting if specified */
#define DMPSTACK_FULL_DUMP  3 /* Force all to use FULL_DUMP */


/*~*****************************************************************/

/*~**********************************/
/* NOTE: Jeff added #ifdef ctPortGEOQUEST logic here, because */
/* it requires turning off TRANPROC, and there are references */
/* to #ifdef TRANPROC prior to the main #ifdef ctPortGEOQUEST */
/* block that appears later in ctopt2.h. */
/*^***********************************/
#ifdef 	ctPortGEOQUEST
#ifdef ctSRVR
#ifndef ctSQLSRVR	/* Only ISAM Server is UNIFRMAT for GEOQUEST- SQL Server is normal */
#ifdef LOW_HIGH		/* Geoquest's UNIFRMAT server:			*/
#define UNIFRMAT	/* 1) Enable UNIFRMAT.				*/
#define NO_TRANPROC	/* 2) UNIFRMAT server doesn't support TRANPROC. */
#endif  /* LOW_HIGH */
#endif  /*~ctSQLSRVR */
#endif	/* ctSRVR */
#endif	/* ctPortGEOQUEST */
/*~***********************************/

/*~**********************************/
/* COMMVAULT ISAM UNIFRMAT Server */
/*^***********************************/
#ifdef 	ctPortCOMMVAULT
#ifdef ctSRVR
#ifdef UNIFRMAT		/* rab:140214- Now passed in from ctoptn.h via mtree */
#ifdef ctSQLSRVR	/* Only ISAM Server is UNIFRMAT for COMMVAULT when UNIFRMAT passed to mtree command line */
#undef UNIFRMAT		/* We do not support UNIFRMAT in SQL */
#else
#ifdef TRANPROC
#undef TRANPROC
#endif
#ifndef NO_TRANPROC
#define NO_TRANPROC	/* UNIFRMAT server doesn't support TRANPROC. */
#endif
#endif  /*~ctSQLSRVR */
#endif	/* UNIFRMAT */
#endif	/* ctSRVR */
#endif	/* ctPortCOMMVAULT */
/*~***********************************/


/*************************************/
/* check for TRANPROC turn off	     */
/*^***********************************/
#ifdef  TRANPROC
#ifdef	NO_TRANPROC
#undef	TRANPROC
#endif
#endif
/*~***********************************/

/*************************************/
/* indicate A3_TRNFIL support	     */
/* ctfary.h should define A3_TRNFIL  */
/*^***********************************/
#ifndef NO_A3_TRNFILsup
#define A3_TRNFILsup
#endif
/*~***********************************/

/***********************************/
#ifdef  ctEVALUATION
#ifndef NO_ctHUGEFILE
#ifndef	ctCLIENT
#define NO_ctHUGEFILE
#endif
#endif
#endif
/***********************************/


/************************************/
/* Activate HUGE for Clients */
#ifdef	ctLOCLIB
#ifndef NO_ctHUGEFILE
/* #define NO_ctHUGEFILE *//* HUGE not yet supported for LOCLIB */
#endif
#endif

#ifdef	ctCLIENT
#ifndef NO_ctHUGEFILE
#ifndef ctHUGEFILE		/* V7 Defaults to HUGE */
#define ctHUGEFILE
#endif

#ifndef ctHUGEFILEsegm
#define ctHUGEFILEsegm
#endif
#endif /* ~NO_ctHUGEFILE */

#endif /* ctCLIENT */


#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB)

#ifndef NO_ctSYSQUE
#ifndef ctSYSQUE		/* Client supports system queue functions */
#define ctSYSQUE
#endif
#endif

#endif /* ctCLIENT || ctMTCLIENT || ctLOCLIB */


/*^**********************************/
#ifdef	ctPortFAIRCOM_INTERNAL_GEN 	/* FairCom Utility Gens */
/* This define is used for our internal Single User utility gen (ctBEHAV_TranFileNbr) */
/* it is activated by mtree using the "x" parameter */
	
#ifndef NO_ctHUGEFILE
#ifndef ctHUGEFILE
#define ctHUGEFILE
#endif
#ifndef ctHUGEFILEsegm
#define ctHUGEFILEsegm
#endif
#endif /* ~NO_ctHUGEFILE */

/*-------------------*/
#ifndef ctNO_CAMO
#define ctCAMO     	/* File Encryption */
#define ctCAMOsys 	/* Special "hidden" key */
#endif
/*-------------------*/

/*-------------------*/
#ifndef ctNO_CAMO
#ifdef ctCAMOsdk 	/* FairCom Encryption SDK */
#define ctCAMOblk	/* FairCom block encryption */
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef CTVERBOSE
#define CTVERBOSE
#endif
/*-------------------*/

#endif	/* ctPortFAIRCOM_INTERNAL_GEN */
/*~**********************************/


/*^**********************************/
/*--------------------------------------------------------------*/
/* ctPortFAIRCOM_INTERNAL_GEN_DLL_RESTRICT_USE indicates the use*/
/* of DllMain in a c-tree DLL used to control which application	*/
/* is entitled to load this specific DLL. The ctdllmain.c is 	*/
/* used and linked into the DLL.				*/
/* Default: This define is controlled by m-tree when necessary.	*/
/* and was initially used for the GUI tools.			*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,2) || (ctVER3_GE(11,2,1) && defined(ctPortATTACH2))
#ifndef NO_ctPortFAIRCOM_INTERNAL_GEN_DLL_RESTRICT_USE
/* #define ctPortFAIRCOM_INTERNAL_GEN_DLL_RESTRICT_USE */
#ifdef  ctPortFAIRCOM_INTERNAL_GEN_DLL_RESTRICT_USE
#define ctPortFAIRCOM_INTERNAL_GEN_DLL_RESTRICT_USE_GUI_TOOLS
#endif
#endif
#endif
/*~**********************************/


/************************************/
/* MULTITRD Basic Defaults 	    */
#ifdef MULTITRD

/*-------------------*/
#ifdef ctdbCTPERM
#define CTPERM
#endif
/*-------------------*/

/*-------------------*/
#ifdef TRANPROC
#ifndef NO_ctTRSETtest
#define ctTRSETtest
#endif
#ifndef NO_ctContRecovery
#define ctContRecovery
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef NO_SUPERDEL
#ifndef CTSUPERDEL
#define CTSUPERDEL
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef NO_ctCACHE_MEMORY
#ifndef ctCACHE_MEMORY
#define ctCACHE_MEMORY
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef ctCACHE_LINE
#ifdef ct8P
#define ctCACHE_LINE	128	/* default cache line size for 64bit systems */
#else
#define ctCACHE_LINE	 32	/* default cache line size for 32bit systems */
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef NO_ctSHADOWMEM
#ifndef ctSHADOWMEM
#define ctSHADOWMEM
#endif
#endif
/*-------------------*/

#endif /* MULTITRD */
/************************************/


/************************************/
/* SQL Server Basic Defaults 	    */
#ifdef	ctSQLSRVR
#include "ctsql_lib.h"
#endif
/************************************/

/*^**********************************/
/* Activate new contional expression*/
#ifdef ct_V90_GENERATION

#ifndef NO_ctFeatCTDB	/* NO_ctFeatCTDB permits the DB layer to be excluded */
#ifndef ctFeatCTDB
#define ctFeatCTDB
#endif
#endif /* NO_ctFeatCTDB */

#ifdef  ctFeatCTDB
#ifndef ctFeatCNDX_V9
#ifdef ctN8
#define ctFeatCNDX_V9
#endif
#endif
#endif /* ctFeatCTDB */
#endif /* ct_V90_GENERATION */

/*~**********************************/


/************************************/
#ifndef ctSRVR
#ifndef ctFeatOTREE
#ifndef ctSQLMTFPG
#ifndef STREE_TRUNK
#define ctLAVE
#define ctLAVEeval
#endif
#endif
#endif
#endif
/************************************/

/************************************/
/* Server Basic Defaults 	    */
#ifdef ctSRVR
#ifndef NO_ctCUSTOM
#define ctCUSTOM		/* Activate Server's SDK Abilities */
#endif

#ifdef ct_V90_GENERATION

#ifndef NO_ctSS
/* #define ctSSrel2 */		/* second release of strict serialization */ /* Activated as of v8.26.1 (Build-050415) */
#endif				/* also remember there is a dependency on this setting in ctsql_lib.h */

#ifndef ctPortWINKE
#ifndef ctPortWINCE
#define ctIOSEMA		/* reduce use of individual file I/O semaphores */
#define ctIOSEMAmemfile		/* reduce use of index cache mutexes for memory index files */
#endif
#endif

#endif


/*-------------------*/
/* We default to Data Compression turned ON */
#ifndef NO_ctCMPREC
#ifndef ctCMPREC
#define ctCMPREC
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_ctHUGEFILE
#ifndef ctHUGEFILE		/* V7 Defaults to HUGE */
#define ctHUGEFILE
#endif

#ifndef NO_ctHUGEFILEsegm
#ifndef ctHUGEFILEsegm
#define ctHUGEFILEsegm
#endif
#endif
#endif /* ~NO_ctHUGEFILE */
/*-------------------*/

/*-------------------*/
#ifndef ctNO_CAMO
#define ctCAMO     	/* File Encryption */
#define ctCAMOsys 	/* Special "hidden" key */
#endif
/*-------------------*/

/*-------------------*/
#ifndef ctNO_CAMO
#ifdef ctCAMOsdk 	/* FairCom Encryption SDK */
#define ctCAMOblk	/* FairCom block encryption */
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef NO_MIRROR
#ifndef ctMIRROR
#define ctMIRROR	/* enable file mirrors */
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef NO_CONDIDX
#ifndef ctCONDIDX
#define ctCONDIDX	/* enable conditional index support */
#endif
#else
#ifdef ctCONDIDX
#undef ctCONDIDX	/* disable conditional index support */
#endif
#endif	/* NO_CONDIDX */
/*-------------------*/

/*-------------------*/
#ifdef CTBOUND
#undef CTBOUND
#endif

#ifndef NO_BOUND
#define NO_BOUND
#endif
/*-------------------*/

/*-------------------*/
#ifdef ctNOGLOBALS
#undef ctNOGLOBALS
#endif

#ifndef ctYESGLOBALS
#define ctYESGLOBALS
#endif
/*-------------------*/

/*-------------------*/
#ifdef rtSRVR
#ifndef rtDRIVERfunc
#define rtDRIVERfunc
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef NO_ctUNIQFILE
#ifndef ctUNIQFILE
#define ctUNIQFILE	/* automatic reassignment of duplicate file ID */
#endif
#endif

#ifndef ctPortMAC
#ifndef ctPortNLM
#ifndef ctDISKFULL
#define ctDISKFULL	/* support DISK_FULL_LIMIT configuration keyword */
#endif
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef CTVERBOSE
#define CTVERBOSE
#endif
/*-------------------*/

/*-------------------*/
#ifndef NO_ctTEST_LOCAL
#ifndef ctTEST_LOCAL
#ifdef ctPortWIN32
#define ctTEST_LOCAL
#endif
#endif
#endif /* ~NO_ctTEST_LOCAL */
/*-------------------*/

/*-------------------*/
/* Activate Multiple Transaction Logs support in v8.24 and forward... */
#define NO_ctMXLOGS /* Deactivated until more mileage */
#ifndef NO_ctMXLOGS
#ifndef ctMXLOGS
#define ctMXLOGS 3
#endif
#endif
/*-------------------*/

#ifndef ctPortWINKE
#ifndef NO_ctFeatCTSRVR_COMMP
#define ctFeatCTSRVR_COMMP	/* Communication protocol support */
#endif
#endif

#ifdef ctPortDotNET
#define ctFeatMULTITHRDINIT
#endif

#ifndef NO_ctPARTITION
#define ctPARTITION		/* Partitioned file support */
#endif

#endif /* ctSRVR */
/************************************/


/************************************/
#ifdef ctBNDSRVR

/*-------------------*/
#ifndef NO_ctHUGEFILE
#ifndef ctHUGEFILE		/* V7 Defaults to HUGE */
#define ctHUGEFILE
#endif

#ifndef ctHUGEFILEsegm
#define ctHUGEFILEsegm
#endif
#endif /* ~NO_ctHUGEFILE */
/*-------------------*/

/*-------------------*/
#ifndef ctNO_CAMO
#ifndef ctCAMO
#define ctCAMO     	/* File Encryption */
#endif
#ifndef ctCAMOsys
#define ctCAMOsys 	/* Special "hidden" key */
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef ctNO_CAMO
#ifdef ctCAMOsdk 	/* FairCom Encryption SDK */
#define ctCAMOblk	/* FairCom block encryption */
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef NO_MIRROR
#ifndef ctMIRROR
#define ctMIRROR
#endif
#endif
/*-------------------*/

/*-------------------*/
#ifndef NO_CONDIDX
#ifndef ctCONDIDX
#define ctCONDIDX	/* enable conditional index support */
#endif
#else
#ifdef ctCONDIDX
#undef ctCONDIDX	/* disable conditional index support */
#endif
#endif	/* NO_CONDIDX */
/*-------------------*/


/*-------------------*/
#ifndef ctPortMAC
#ifndef ctPortNLM
#ifndef ctDISKFULL
#define ctDISKFULL	/* support DISK_FULL_LIMIT configuration keyword */
#endif
#endif
#endif
/*-------------------*/

#ifdef ct_V90_GENERATION
#ifndef ctPortWINKE
#ifndef ctPortWINCE
#define ctIOSEMA	/* reduce use of individual file I/O semaphores */
#define ctIOSEMAmemfile	/* reduce use of index cache mutexes for memory index files */
#endif
#endif

#endif
#endif				/* ctBNDSRVR default settings */
/**********************************************/

/************************************/
/* c-tree Plus Basic Defaults 	    */

/*-------------------*/
#ifdef  ctPortUNIX

#ifdef TRANPROC

#ifndef ctPortMACOSX_10_3
#ifndef iSYNC_LOG
#define iSYNC_LOG
#endif

#ifdef ctPortLINUX
/*
** On Linux systems, we enable the O_SYNC/O_DSYNC option when creating
** or opening files rather than calling fcntl() with the F_SETFL mode
** because this system call ignores O_SYNC/O_DSYNC.
*/
#define iSYNC_LOG_AT_OPEN
#endif

#endif

#ifndef ctPortFREEBSD8
#ifndef ctPortMACOSX
#ifndef ctPortFREEBSD7
#ifndef ctPortSCO5
#if !defined(ctPortSTR) || !defined(__INTERIX)
#ifndef ctFeatUSE_FDATASYNC
#define ctFeatUSE_FDATASYNC
#endif
#endif
#endif
#endif
#endif
#endif

/*
** Do not support fdatasync() for a FairCom-threaded
** c-tree Server compile on SCO Unix.
*/
#ifdef ctPortSCO386
#ifdef ctPortFAIRCOM_THREADS
#undef ctFeatUSE_FDATASYNC
#endif
#endif

#ifdef	ctPortSOLARIS
#ifndef ctFeatDIRECTIO_LOG
#define ctFeatDIRECTIO_LOG
#endif
#endif

#endif /* TRANPROC */

#endif /* ctPortUNIX */
/*-------------------*/


/*-------------------*/
#ifndef ctYESGLOBALS
#ifndef MULTITRD
#ifndef ctNOGLOBALS
#define ctNOGLOBALS
#endif
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_RESOURCE
#ifndef RESOURCE
#define RESOURCE
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_BATCH
#ifndef CTBATCH
#define CTBATCH
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_SUPER
#ifndef CTSUPER
#define CTSUPER
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_VARLD
#ifndef VARLDATA
#define VARLDATA
#endif
#endif

#ifdef CTSUPERDEL
#ifndef VARLDATA
#undef CTSUPERDEL
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_VARLK
#ifndef VARLKEYS
#define VARLKEYS
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifdef ctPortDIAD_FS
/*
** Turn off parameter file support for the DIAD file system
** because fscanf is not supported.
*/
#undef PARMFILE
#define NO_PARMF
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_PARMF
#ifndef PARMFILE
#define PARMFILE
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_RTREE
#ifndef RTREE
#define RTREE
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_ISAM
#ifndef CTS_ISAM
#define CTS_ISAM
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef ctPASCALst
#define ctPASCALst
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_CONTEXT
#ifndef ctICONTEXT
#define ctICONTEXT
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef UNIFRMAT
#ifndef NO_UNIFM
#define NO_UNIFM
#endif
#endif
/*-------------------*/


/*-------------------*/
#ifndef NO_CONDIDX
#ifndef ctCONDIDX
#define ctCONDIDX	/* enable conditional index support */
#endif
#else
#ifdef ctCONDIDX
#undef ctCONDIDX	/* disable conditional index support */
#endif
#endif	/* NO_CONDIDX */
/*-------------------*/


/*-------------------*/
#ifndef NO_HISTORY
#ifdef  TRANPROC
#ifndef NO_CTHISTORY
#ifndef CTHISTORY
#define CTHISTORY	/* enables transaction history */
#endif
#endif
#endif
#endif
/*-------------------*/



/*-------------------*/
/*
** Platforms that support OS write through (instead of
** OS buffer flush). This write through is intended for
** systems where the OS write through is expected to be
** faster than issuing OS buffer flush calls.
**
** This form of write through is different from a
** c-tree ctWRITETHRU file mode. The c-tree file
** mode affects when c-tree issues a write request
** to send a c-tree cache/buffer page to the operating
** system, but does not control when
** the operating system clears its buffers to disk.
** This new write through (controlled through
** COMPATIBILTY keywords for TRANPROC data and index
** files) indicates that whenever c-tree clears its buffer,
** the write operation should go directly to disk.
*/

#ifdef ctPortWIN32
#define ctOSWRITETHRU
#endif

#ifdef iSYNC_LOG
#define ctOSWRITETHRU
#endif
/*-------------------*/


/*-------------------*/
/*
** For platforms that support ctOSWRITETHRU, it may be necessary to turn
** on ctOSWRITETHRUnodirupd if write operations performed with a file
** opened for OS WRITETHRU do NOT update the directory entries (meta data)
** for the file. Turning on ctOSWRITETHRUnodirupd causes file extensions
** to be followed by flushes. NOTE: all other flushes will be skipped by
** files with OS WRITETHRU turned on.
**
** flmode3 holds ctTRNLOGthru for data/index using writethru instead
** of buffer flushes
*/
#ifdef ctOSWRITETHRU

#ifdef ctPortWIN32
#define ctOSWRITETHRUnodirupd
#endif

#endif
/*-------------------*/
/*-------------------*/
#ifdef	ctPortWIN32
#ifdef	FPUTFGET

#ifdef ctPortWINCE
#define NO_ctTEST_LOCAL
#define NO_ctHUGEFILE
#undef  ctHUGEFILE
#endif

#ifndef ctPortWINCE

#ifndef ctPortWFW
#define ctPortWFW	/* ctsysio locking to force network cache flush */
#endif

#ifndef NO_ctPortWFWlockEx
#define ctPortWFWlockEx		/* use LockFileEx instead of LockFile */
#endif

#endif /* ctPortWINCE */

#ifndef NO_ctTEST_LOCAL
/*
** We default to ctTEST_LOCAL OFF because we have had reports of dirty reads
** occurring when reading data over the network while others are updating it
** when ctTEST_LOCAL is ON.
*/
/* #define ctTEST_LOCAL */
#endif

#endif	/* FPUTFGET */
#define ctBEHAV_READERROR	/* check for external interference on reads */
#endif	/* ctPortWIN32 */
/*-------------------*/


/*-------------------*/
#ifdef	ctPortWIN16
#ifdef	FPUTFGET
#ifndef ctPortWFW
/* #define ctPortWFW */ /* Invoke low-level ctsysio locking to force network cache flush */
#endif
#endif	/* FPUTFGET */
#endif	/* ctPortWIN16 */
/*-------------------*/


/*-------------------*/
#define ctFLEXFILE  	/* Use Flexible file support: this feature is always enabled */
/*-------------------*/


/*-------------------*/
#ifndef ctNO_CAMO
#ifndef ctCAMO
#if defined(ctCLIENT) || defined(ctMTCLIENT)
#define ctCAMO			/* File Encryption */
#endif
/* #define ctCAMOsys  */	/* Special "hidden" key */
#endif
#endif
/*-------------------*/

/* end c-tree Plus basic defaults 	*/
/************************************/

/**********************************************/
/* Other m-tree high level define adjustments */

#ifndef MULTITRD

#ifdef ctDBGSEMCNT
#undef ctDBGSEMCNT
#endif
#ifndef SMN
#define SMN(nn)
#define LMN(nn)
#endif

#ifdef ctCACHE_MEMORY
#undef ctCACHE_MEMORY
#endif

#endif /* ~MULTITRD */

#ifndef ctHUGEFILE
#ifdef ctDBGDLNGCNT
#undef ctDBGDLNGCNT
#endif
#endif

#ifdef 	ctMTCLIENT /* Multi-Threaded Client */
#ifndef ctThrdApp
#define ctThrdApp
#endif
#endif

#ifdef 	ctMTFPG /* Multi-Threaded FPUTFGET */

#ifndef NO_ctMTFPGreentrant
#if ctVER3_GE(11,2,0)
#if defined(ctPortWIN32) || ctVER3_GE(11,5,0)
/* Thread safety without serializing threads */
#define ctMTFPGreentrant
#endif
#endif
#endif

#ifndef CTBOUND
#define CTBOUND
#endif
#ifdef NO_BOUND
#undef NO_BOUND
#endif
#ifndef ctThrdFPG
#define ctThrdFPG
#endif
#ifdef ctMTFPGreentrant
#ifndef ctThrdApp
#define ctThrdApp
#endif
#endif
#define ctdefer	ctThrdSleep
#endif
/**********************************************/

/************************************************/
/* This section controls the output for many of */
/* the c-tree plus utilities (like rebuild).	*/
/* printf output Options */

/*************************/
/* If RB_OUTPUT or RB_INTERACTIVE was disabled in ctoptn.h, */
/* set flags to indicate this. */
#ifdef NO_RB_OUTPUT
#define CTOPTN_NO_RB_OUTPUT
#endif

#ifdef NO_RB_INTERACTIVE
#define CTOPTN_NO_RB_INTERACTIVE
#endif
/*************************/

/*************************/
/* No output for server  */
#ifdef ctSRVR

#ifndef NO_RB_OUTPUT
#define NO_RB_OUTPUT
#endif

#ifndef NO_RB_INTERACTIVE
#define NO_RB_INTERACTIVE
#endif

#endif /* ctSRVR */
/*************************/

/*************************/
/* No output for server  */
#ifdef ctBNDSRVR

#ifndef NO_RB_OUTPUT
#define NO_RB_OUTPUT
#endif

#ifndef NO_RB_INTERACTIVE
#define NO_RB_INTERACTIVE
#endif

#endif /* ctBNDSRVR */
/*************************/


/*************************/
/* No output for special rebuild */
#ifdef fnCTSBLD

#ifndef NO_RB_OUTPUT
#define NO_RB_OUTPUT
#endif

#ifndef NO_RB_INTERACTIVE
#define NO_RB_INTERACTIVE
#endif

#endif /* fnCTSBLD */
/*************************/

/*************************/
/* No output for WINDOWS  */
#if (defined(ctPortWIN32) || defined(MSWINDOWS))

#ifndef NO_RB_OUTPUT
#define NO_RB_OUTPUT
#endif

#ifndef NO_RB_INTERACTIVE
#define NO_RB_INTERACTIVE
#endif

#endif /* WIN32 */
/*************************/

/*************************/
#ifdef ctPortCONSOLE_APP

/* If RB_OUTPUT or RB_INTERACTIVE was disabled in ctoptn.h, */
/* keep them disabled.  Otherwise, enable them. */

#ifndef CTOPTN_NO_RB_OUTPUT
#undef NO_RB_OUTPUT
#endif

#ifndef CTOPTN_NO_RB_INTERACTIVE
#undef NO_RB_INTERACTIVE
#endif

#endif
/*************************/

/*************************/
/* If callback allowed, then no output */
#ifdef  RB_CALLBACK

#ifdef ctSRVR
#ifndef ctPortWINKE
#ifdef ctFeatCTSRVR_COMMP
#define RB_CALLBACK_SRVR
#endif
#endif
#endif

#ifndef NO_RB_OUTPUT
#define NO_RB_OUTPUT
#endif

#ifndef NO_RB_INTERACTIVE
#define NO_RB_INTERACTIVE
#endif

#endif /* RB_CALLBACK */
/*************************/

/*************************/
/* If output allowed, then turn it on */
#ifdef  NO_RB_OUTPUT
#undef  RB_OUTPUT
#else
#ifndef ctPortMSIGA
#define RB_OUTPUT
#endif
#endif

#ifdef  NO_RB_INTERACTIVE
#undef  RB_INTERACTIVE
#else
#define RB_INTERACTIVE
#endif
/*************************/

/*************************/
/* macro truncate address to UINT */
#ifndef ctTRUNCATE
#define ctTRUNCATE(adr)	((UINT) ((ctADR2LNG) (adr)))
#endif
/*************************/

/**************************/
/* partition requirements */
/* resource/huge/isam	  */

#ifdef FPUTFGET
#ifdef ctPARTITION
#undef ctPARTITION
#endif
#endif
#ifndef RESOURCE
#ifdef ctPARTITION
#undef ctPARTITION
#endif
#endif
#ifndef ctHUGEFILE
#ifdef ctPARTITION
#undef ctPARTITION
#endif
#endif
#ifndef CTS_ISAM
#ifdef ctPARTITION
#undef ctPARTITION
#endif
#endif
#ifndef ctCONDIDX
#ifdef ctPARTITION
#undef ctPARTITION
#endif
#endif

/* check partition instance support */
#ifdef ctPARTITION
#ifndef NO_ctPARTITIONinstnc
#define ctPARTITIONinstnc
#endif
#else
#ifdef ctPARTITIONinstnc
#undef ctPARTITIONinstnc
#endif
#endif

/* check enhanced IDXENT support */
#ifdef ctPARTITION
#ifndef NO_ctPARTITIONidxent
#define ctPARTITIONidxent
#endif
#else
#ifdef ctPARTITIONidxent
#undef ctPARTITIONidxent
#endif
#endif


/**************************/

#ifdef ctHUGEFILE
#ifdef FPUTFGET
#ifndef NO_ctHDR1
/*
** Turn on unified header I/O for HUGE files: entire header
** read and written in one operation. This relies on a
** change to the header locking strategy: instead of locking
** at both header offset 0 at FILEOFFS, only locks at 0 are
** made. Attempts to lock both at locations are handled by
** ignoring the second lock attempt (as well as its unlock).
*/
#define ctHDR1
#endif
#endif
#endif

/*
** ctFILXTR
**
** augment information for each file in checkpoint. ctFILXTRsiz,
** defined below, specifies how many extra bytes will be stored
** per file.
**
** The FX_CHKPHDR member of ax2hdr[] points to the offset in the
** checkpoint where the augmented information is stored.
**
** DEFAULT: turn on ctFILXTR
*/
#ifndef NO_ctFILXTR
#define ctFILXTR
#endif

#define ctFILXTRsiz	24	/* extra bytes per file in chedckpoint.	**
				** the tflmod header member is stored	**
				** for each file. The XZ_CHKPHDR member	**
				** of ax2hdr[] stores ctFILXTRsiz so	**
				** that if it is changed, the recovery	**
				** logic will know what is in the	**
				** checkpoint, regardless of the	**
				** current value.			**
				**					**
				** The code assumes ctFILXTRsiz is a	**
				** multiple of four.			**
				**					**
				**  4 => tflmod				**
				** 24 => tflmod tflmod2 tflmod3 flmode  **
				**       flmode2 flmode3		**
				**					**
				** flmode is stored as 4 bytes		**
				**					**
				** to ensure backward compatibility, do	**
				** not change the existing contents	**
				** and order of contents. increasing	**
				** ctFILXTRsiz means adding additional	**
				** fields to the end of existing fields */
#define FILXTRtflmod	0
#define FILXTRtflmod2	1
#define FILXTRtflmod3	2
#define FILXTRflmode	3
#define FILXTRflmode2	4
#define FILXTRflmode3	5

/*^********************************************/
/* { ctBEHAV... Options (Behavior options) */

/*--------------------------------------------------------------*/
/* ctBEHAV_SCHSEG maintains the padding behavior of SCHSEG and	*/
/* USCHSEG for CT_FPSTRING, CT_F2STRING and CT_F4STRING. The	*/
/* documentation specifies that NO padding will occur at the	*/
/* end of these three types of fields when used with SCHSEG and */
/* USCHSEG, but padding IS occuring. For example, if a		*/
/* CT_FPSTRING field with a length byte of 6 is used for an 8	*/
/* byte key segment, then c-tree mistakenly adds two bytes of	*/
/* padding (if SCHSEG or USCHSEG is used).			*/
/*								*/
/* DEFAULT: define ctBEHAV_SCHSEG. If ctBEHAV_SCHSEG is NOT	*/
/* defined, then no padding is added consistent with the	*/
/* documentation.						*/
/*--------------------------------------------------------------*/
#define ctBEHAV_SCHSEG

/*--------------------------------------------------------------*/
/* ctBEHAV_DumpDefer maintains the use of ctdefer() to sleep	*/
/* a dynamic dump thread until the (next) dump time. If		*/
/* ctBEHAV_DumpDefer is not defined, a timed semaphore is used	*/
/* which permits shutdown to clear the semaphore and cancel	*/
/* the dump thread. Ordinarily, this define is off unless timed	*/
/* semaphores are not accurate (e.g., Banyan)			*/
/*								*/
/* DEFAULT: ctBEHAV_DumpDefer is NOT defined.			*/
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/* ctBEHAV_StatusOpen causes the CTSTATUS.FCS log file to	*/
/* remain open after its first use. When this define is not	*/
/* used, the status file is opened and closed for each		*/
/* use. When the define is used, a fflush() is issued after	*/
/* each use. At this time, this define only affects MULTITRD	*/
/* implementations.						*/
/*								*/
/* DEFAULT: ctBEHAV_StatusOpen is defined (with MULTITRD)	*/
/*--------------------------------------------------------------*/
#ifndef ctPortOS2
#if (defined(MULTITRD) || defined(ctPortFAIRCOM_INTERNAL_GEN))
#ifndef NO_ctBEHAV_StatusOpen
#define ctBEHAV_StatusOpen
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_freopen causes stream file descriptors to be reused	*/
/* where possible. Most prominently is with dynamic dumps. A	*/
/* dump uses two streams: one for input of the dump script and	*/
/* one for output of the actual dump contents. Parameter file	*/
/* open and create use a stream file. RBLIFIL uses a stream for	*/
/* a temporary file to process unexpected duplicates and/or bad	*/
/* serial number keys.						*/
/*								*/
/* Some systems (e.g., SOLARIS) enforce a limit on stream files	*/
/* such that the file descriptor assigned to the file (by the	*/
/* OS) must be less than 256. This means that even if file	*/
/* descriptors are available, a fopen may fail if the descriptor*/
/* is above 255. The server will reserve streams with low	*/
/* file descriptors that can be used by the dynamic dump via	*/
/* the ctrt_freopen() call which reassigns the stream to another*/
/* file. Parameter file open and create, and RBLIFIL temporary	*/
/* file stream opens will attempt a regular stream open; if it	*/
/* fails, and if ctBEHAV_freopen is defined, then an attempt	*/
/* be made to reuse a stream.					*/
/*								*/
/* If ctBEHAV_freopen is defined, then ctBEHAV_StatusOpen	*/
/* will be forced on.						*/
/*								*/
/* NOTE: inorder to permit the status file to be "closed" via	*/
/* the action of ctBEHAV_freopen, then be sure to add		*/
/*	#define NO_ctBEHAV_StatusOpen				*/
/* to the option header or make file. Otherwie, freopen will	*/
/* not apply to the status file even though ctBEHAV_StatusOpen	*/
/* will still be forced on.					*/
/*								*/
/* DEFAULT: ctBEHAV_freopen is defined (with MULTITRD)		*/
/*--------------------------------------------------------------*/

#ifndef ctPortOS2
#ifndef ctPortWINKE
#ifndef ctPortWINCE_SRVR
#ifdef  MULTITRD
#ifndef NO_ctBEHAV_freopen
#ifndef ctPortDIAD_FS
#define ctBEHAV_freopen
#define ctBEHAV_freopenPARM
#endif
#endif
#endif
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_AbortOnClose maintains the abort of a pending	*/
/* transaction if the file has been updated by the process	*/
/* attempting the close. That is, the close operation continues,*/
/* but the pending transaction is aborted.			*/
/*								*/
/* DEFAULT: ctBEHAV_AbortOnClose is NOT defined unless TRANPROC */
/* is not defined.						*/
/*--------------------------------------------------------------*/
#ifndef TRANPROC
#ifndef ctBEHAV_AbortOnClose
#define ctBEHAV_AbortOnClose
#endif
#endif

#ifdef ctBEHAV_AbortOnClose
#define	tsticnm	tstifnm
#define tstcnm	tstfnm
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_TranFileNbr maintains the assignment of an internally*/
/* used transaction related file to the end of the file number	*/
/* range at the time automatic recovery has completed. With	*/
/* ctFLEXFILE defined, this may mean that the file number	*/
/* assigned will end up in the middle of the file number range	*/
/* as the range is automatically extended. This BEHAV define	*/
/* has no affect when ctFLEXFILE is not defined since the file	*/
/* number is always assigned to the end of the range in this	*/
/* case. Also, this BEHAV define has no affect if the appli-	*/
/* cation is not compiled user single-user TRANPROC.		*/
/*								*/
/* When ctFLEXFILE is defined and this BEHAV define is NOT	*/
/* defined, then the file number assigned to the internal	*/
/* file comes at the beginning of the file number range (which	*/
/* could cause a problem if the application uses hard coded	*/
/* file numbers).						*/
/*								*/
/* This define only applies to single-user TRANPROC applications*/
/*								*/
/* DEFAULT: ctBEHAV_TranFileNbr is NOT defined.			*/
/*--------------------------------------------------------------*/

/*-------------*/
#ifndef ctBEHAV_TranFileNbr
#ifdef	ctPortFAIRCOM_INTERNAL_GEN 	/* FairCom Utility Gens */
#ifdef	ctFLEXFILE
#ifdef  TRANPROC
#define ctBEHAV_TranFileNbr 		/* Must be on for ctrdmp */
#endif
#endif
#endif
#endif
/*-------------*/

/*--------------------------------------------------------------*/
/* ctBEHAV_DumpProtect permits clean dump of non-transaction	*/
/* files during dynamic dump. However, no consistency between	*/
/* files is guaranteed.						*/
/*								*/
/* DEFAULT: ctBEHAV_DumpProtect is defined when MULTITRD and	*/
/* TRANPROC are defined. To disable DumpProtect comment out	*/
/* the following defines.					*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifdef TRANPROC
#ifndef ctBEHAV_DumpProtect
#define ctBEHAV_DumpProtect
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_ULCNT supports user lock counts and a check for	*/
/* system lock table entries on a user-level close. If the lock */
/* balance count is out of synch, then the lock table is checked*/
/* and any orphan locks for the user are released. No such locks*/
/* should exist.						*/
/*								*/
/* DEFAULT: ctBEHAV_ULCNT is defined (but only makes sense if	*/
/* MULTITRD is defined.)					*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef ctBEHAV_NO_ULCNT
#define ctBEHAV_ULCNT
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_LOOKASIDE uses system level calls to implement a	*/
/* memory suballocator.						*/
/*								*/
/* if ctBEHAV_LOOKASIDE is on, then ctBEHAV_MEMSUB must be off.	*/
/* 								*/
/* DEFAULT: ctBEHAV_LOOKASIDE is off except for special ports.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_LOOKASIDE
#ifdef ctPortWINKE

#define ctBEHAV_LOOKASIDE
#define ctBEHAV_NO_MEMSUB

#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_MEMSEMA should be defined when the underlying memory */
/* routines are not thread safe.				*/
/*								*/
/* DEFAULT: ctBEHAV_MEMSEMA is not defined (and only makes	*/
/* sense) if MULTITRD or MULTIAPP is defined.			*/
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
/* ctBEHAV_MEMSUB should be defined to utilize the server's	*/
/* memory management subsystem. This subsystem trades off fewer	*/
/* calls to the system memory manager with more calls to the	*/
/* system semaphore routines. The sub-manager may also reduce	*/
/* memory fragmentation.					*/
/*								*/
/* To turn off ctBEHAV_MEMSUB at compile time, include		*/
/*	#define ctBEHAV_NO_MEMSUB				*/
/*								*/
/* DEFAULT: ctBEHAV_MEMSUB is defined.				*/
/*--------------------------------------------------------------*/
#ifndef ctBEHAV_NO_MEMSUB
#define ctBEHAV_MEMSUB
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_MEMSUB_SPCLST enables private suballocator lists	*/
/* in one or more specific classes of suballocator lists	*/
/* (e.g., LOKTYP). The reason for the private lists is to	*/
/* reduce the thread contention by replacing a global mutex for	*/
/* a "public" list with a separate mutex or even no mutex for	*/
/* each private list. For example, the LOKTYP list uses		*/
/* ctpllsema to control list access; but ctnum->thdrf is	*/
/* already held for each physical file when a LOKTYP item is	*/
/* allocated or freed, and the private list for a file means	*/
/* no new mutex is required to allocate or free a LOKTYP item.	*/
/*								*/
/* ctBEHAV_MEMSUB_SPCLST requires ctHUGEFILE and is not		*/
/* supported for ctPortWINKE.					*/
/*								*/
/* DEFAULT: ctBEHAV_MEMSUB_SPCLST is on by default.		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_MEMSUB_SPCLST
#define ctBEHAV_MEMSUB_SPCLST
#endif

#if !defined(MULTITRD) || defined(ctPortWINKE) || !defined(ctHUGEFILE)
#ifdef ctBEHAV_MEMSUB_SPCLST
#undef ctBEHAV_MEMSUB_SPCLST
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_LLSEMA modifies the usage of ctpllsema. Without this	*/
/* ctBEHAV ctpllsema controls global lock statistics, the	*/
/* acquisition of LOKTYP items from the suballocator, lock	*/
/* block lists, and deadlock detection [using the ct_wf, ct_vf	*/
/* and ctdedlok arrays]. With this ctBEHAV ctpllsema only	*/
/* controls deadlock detection. A new mutex, ctplmsema controls	*/
/* global lock statistics, and ctnum->thdrf (which was held	*/
/* already) controls lock block lists and access to private	*/
/* suballcator lists for each file (ala ctBEHAV_MEMSUB_SPCLST).	*/
/*								*/
/* ctBEHAV_LLSEMA requires ctBEHAV_MEMSUB_SPCLST		*/
/*								*/
/* DEFAULT: ctBEHAV_LLSEMA is on by default.			*/
/*--------------------------------------------------------------*/
#define ctBEHAV_LLSEMA

#if !defined(ctBEHAV_MEMSUB_SPCLST)
#ifdef ctBEHAV_LLSEMA
#undef ctBEHAV_LLSEMA
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_LOG_WRITETHRU should be defined for non-server (i.e.,*/
/* bound-servers and single-user TRANPROC) implementations in	*/
/* which it is derired to use synchronous log writes instead of	*/
/* buffered log writes plus log flushes. System specific code	*/
/* in ctsfio_a.c and ctsave.c must be in place (e.g., see the	*/
/* OS/2 implementation) to handle synchronous status on creates	*/
/* and opens (ctsfio_a.c), and to return immediately from a	*/
/* save call if synchronous writes are in use (ctsave.c).	*/
/*								*/
/* In server implementations, the use of synchronous log	*/
/* is handled through a COMPATIBILITY LOG_WRITETHRU entry	*/
/* in the server configuration file or settings file. It is not	*/
/* controlled through this behavior option.			*/
/*								*/
/* DEFAULT: ctBEHAV_LOG_WRITETHRU is NOT defined.		*/
/*								*/
/* With new BOUND and single-user COMPATIBILITY support, it is	*/
/* not necessary to use this ctBEHAV. But turning it on will be	*/
/* the same as setting ctCompatUS_LogThru in the compatibility	*/
/* configuration word.						*/
/*--------------------------------------------------------------*/


/*--------------------------------------------------------------*/
/* ctBEHAV_NOTRANFILE forces a FTYP_ERR(53) if a transaction	*/
/* controlled file mode is attempted on a create when TRANPROC	*/
/* is not defined. This pre 6.9 behavior. ctBEHAV_NOTRANFILE	*/
/* cannot be defined when TRANPROC is defined.			*/
/*								*/
/* DEFAULT: ctBEHAV_NOTRANFILE is NOT defined which permits	*/
/* files created in nonTRANPROC environments to automatically	*/
/* support transactions when opened in a TRANPROC environment.	*/
/*--------------------------------------------------------------*/
#ifdef TRANPROC
#ifdef ctBEHAV_NOTRANFILE
#undef ctBEHAV_NOTRANFILE
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_VAREOF permits the last record in a variable length	*/
/* file to grow in place as long as it fits within the current	*/
/* physical size of the file, and no other user is attempting	*/
/* to use the space immediately after the last record.		*/
/*								*/
/* ctBEHAV_VAREOFphys extends support to records that would	*/
/* grow beyond the current physical file size.			*/
/* ctBEHAV_VAREOFphys requires ctBEHAV_VAREOF. If this		*/
/* extension is enabled, it may be turned off at server		*/
/* runtime using COMPATIBILITY NO_VAR_PEOF			*/
/*								*/
/* DEFAULT: ctBEHAV_VAREOF is defined. To turn off at compile	*/
/* add #define ctBEHAV_NO_VAREOF				*/
/*--------------------------------------------------------------*/
#ifndef ctBEHAV_NO_VAREOF
#define ctBEHAV_VAREOF
#endif
#ifndef NO_ctBEHAV_VAREOFphys
#ifdef ctBEHAV_VAREOF
#define ctBEHAV_VAREOFphys
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_TRANOUT causes a variable length record which moves	*/
/* on a RWTVREC to inherit the ctTRANOUT attribute on its lock	*/
/* if the original record position had been locked outside the	*/
/* transaction. Without this behavior, a TRANEND(ctKEEP_OUT_ALL)*/
/* would NOT result in the new record position staying locked.	*/
/*								*/
/* DEFAULT:  ctBEHAV_TRANOUT is activated.			*/
/*--------------------------------------------------------------*/
#define ctBEHAV_TRANOUT


/*--------------------------------------------------------------*/
/* ctBEHAV_KEEP_OUT_trnseq causes ctKEEP_OUT to use		*/
/* ct_usrsq(sOWNR) to determine whether or not the lock was	*/
/* obtained in the current transaction (as opposed to a prior	*/
/* transaction and not freed in the prior transaction). Each	*/
/* thread (sOWNR) maintains a simple sequence number ct_usrsq()	*/
/* incremented at the beginning of each of their transactions.	*/
/* ct_usrsq() eliminates concerns with transactions that delay	*/
/* the assignment of their actual transaction number.		*/
/*								*/
/* COMPATIBILITY NO_KEEP_OUT_TRNSEQ will disable this new	*/
/* behavior.							*/
/*								*/
/* Whether or not ctBEHAV_KEEP_OUT_trnseq is defined, ct_usrsq	*/
/* will be maintained. At this time ct_usrsq is only utilized	*/
/* if the behavior is enabled.					*/
/*								*/
/* DEFAULT:  ctBEHAV_KEEP_OUT_trnseq is defined.		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_KEEP_OUT_trnseq
#ifdef TRANPROC
#define ctBEHAV_KEEP_OUT_trnseq
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_SERNUMUPD restores the incrementing of a data file's	*/
/* serial number during resource adds and variable length data	*/
/* record rewrites that move the record.			*/
/*								*/
/* These two situations do not use the new serial number.	*/
/*								*/
/* DEFAULT:  ctBEHAV_SERNUMUPD is NOT activated.		*/
/*--------------------------------------------------------------*/
/* #define ctBEHAV_SERNUMUPD */


/*--------------------------------------------------------------*/
/* ctBEHAV_BATUTFRM restores the calls to uTFRMKEY when		*/
/* BAT_RET_KEY is used with BATSET(). BAT_RET_KEY causes the	*/
/* key values for the records that satisfy the search request	*/
/* to be returned. uTFRMKEY undoes the reversible key trans-	*/
/* formations. Our documentation implies that uTFRMKEY will not */
/* be called, but we were calling it. Add this define to restore*/
/* this behavior.						*/
/*								*/
/* DEFAULT:  ctBEHAV_BATUTFRM is NOT activated.			*/
/*--------------------------------------------------------------*/
/* #define ctBEHAV_BATUTFRM */


/*--------------------------------------------------------------*/
/* ctBEHAV_RSTR_KEY causes a heterogeneous client to restore	*/
/* numeric key segments of target keys [e.g., GTEREC(key,target,*/
/* recbuf)] to their original order if they were switched as	*/
/* part of automatic TFRMKEY support. These segments have never */
/* been restored although we have always restored other numeric */
/* data switched in a heterogeneous system. This define only	*/
/* affects the ctappx.c module.					*/
/*								*/
/* DEFAULT:  ctBEHAV_RTSR_KEY is NOT activated.			*/
/*--------------------------------------------------------------*/
/* #define ctBEHAV_RSTR_KEY */


/*--------------------------------------------------------------*/
/* ctBEHAV_WRTMRK causes a write high-water mark to be main-	*/
/* tained so that partial cache page writes past this water-mark*/
/* can skip a read operation to prime the cache page.		*/
/*								*/
/* DEFAULT:  ctBEHAV_WRTMRK is activated except for FPUTFGET.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_WRTMRK
#define ctBEHAV_WRTMRK
#endif
#ifdef FPUTFGET
#ifdef ctBEHAV_WRTMRK
#undef ctBEHAV_WRTMRK
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_KILL_QUIET causes the SEC_BLOCK_KILL option of the	*/
/* SECURITY function to suspend internal threads that might	*/
/* operate on user files (such as the delete node thread). This */
/* should eliminate any user file I/O while the server is	*/
/* suspended.							*/
/*								*/
/* ctBEHAV_KILL_QUIETdbg will produce debugging info in CTSTATUS*/
/*								*/
/* DEFAULT:  ctBEHAV_KILL_QUIET is activated for server.	*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#define ctBEHAV_KILL_QUIET
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_BLM augments the buffer/cache hash routines, that	*/
/* work very efficiently for random access, with linked lists	*/
/* that permit more efficient traversing of buffers that have	*/
/* been updated (w/o the need to traverse the buffers that	*/
/* have not been updated). This should be helpful with very	*/
/* large buffer/cache spaces. ctBEHAV_BLM cannot be used unless	*/
/* MULTITRD is defined.						*/
/*								*/
/* DEFAULT:  ctBEHAV_BLM is activated for MULTITRD		*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctBEHAV_BLM
#define ctBEHAV_BLM
#endif
#else
#ifdef ctBEHAV_BLM
#undef ctBEHAV_BLM
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_IDLE_FLUSH permits a server to perform file flushing	*/
/* during IDLE periods. Low priority background threads, such	*/
/* the delete node thread, do not affect the IDLE state.	*/
/*								*/
/* Because the measure of idleness requires the faithful use of	*/
/* the ctaddwork/ctrmvwork routines, IDLE processes are imple-	*/
/* mented for servers, but not for BOUND-only MULTITRD.		*/
/*								*/
/* ctBEHAV_BLM is required for this option.			*/
/*								*/
/* DEFAULT:  ctBEHAV_IDLE_FLUSH is activated for ctSRVR		*/
/*--------------------------------------------------------------*/
#ifdef ctBEHAV_BLM
#ifndef NO_ctBEHAV_IDLE_FLUSH
#ifdef ctSRVR
#define ctBEHAV_IDLE_FLUSH
#endif
#endif
#endif

/*-------------------*/
/*
** if any IDLE process is defined, then ctWORKMON
** must be defined
*/
#ifdef ctBEHAV_IDLE_FLUSH
#define ctWORKMON
#endif
/*-------------------*/


/*--------------------------------------------------------------*/
/* ctBEHAV_CHECKFIX causes (ISAM level) ADDREC/RWTREC to check	*/
/* if the beginning of the record contains either a delete flag */
/* or a	resource mark. If so, a FBEG_ERR error is returned.	*/
/*								*/
/* In a server environment, the COMPATIBILITY NO_CHECKFIX	*/
/* turns off this record validation.				*/
/*								*/
/* DEFAULT:  ctBEHAV_CHECKFIX is on.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHECKFIX
#define ctBEHAV_CHECKFIX
#endif

#ifndef NO_ctBEHAV_4BINT
#define ctBEHAV_4BINT
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CHKPNTLST permits the commit buffer/cache list	*/
/* counters to be adjusted if they do not agree with the actual	*/
/* list contents. The contents and the counters should always	*/
/* match, but this behavior avoids terr(7057/7157) in the event	*/
/* they do not match.						*/
/*								*/
/* DEFAULT:  ctBEHAV_CHKPNTLST is on.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHKPNTLST
#define ctBEHAV_CHKPNTLST
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_NO_FLUSHDEL skips buffer/cache flushes for a file	*/
/* about to be deleted.						*/
/*								*/
/* ctFeatNO_FLUSH must be enabled for this behavior to take	*/
/* effect.							*/
/*								*/
/* DEFAULT:  ctBEHAV_NO_FLUSHDEL is on.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_NO_FLUSHDEL
#define ctBEHAV_NO_FLUSHDEL
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_ZEROAUTOSAVE causes, if the TRANBEG mode includes	*/
/* ctAUTOSAVE, an initial auto savepoint upon completion of the	*/
/* TRANBEG (instead of waiting until the 1st successful update	*/
/* operation). This simplifies code design since a TRANRST can	*/
/* always be called successfully (not just after the 1st good	*/
/* update).							*/
/*								*/
/* DEFAULT:  ctBEHAV_ZEROAUTOSAVE is on.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_ZEROAUTOSAVE
#define ctBEHAV_ZEROAUTOSAVE
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CLNOPENRCV changes how an index file's header count	*/
/* is maintained during automatic recovery if the index is found*/
/* to have a clean update flag.	If a checkpoint subsequently	*/
/* contains index header count information for this file, then	*/
/* the behavior	reverts back to standard processing.		*/
/*								*/
/* DEFAULT:  ctBEHAV_CLNOPENRCV is on.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CLNOPENRCV
#define ctBEHAV_CLNOPENRCV
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_PRGOLDLOGS looks for obsolete logs after successful	*/
/* startup. Such logs are not ordinarily purge until additional	*/
/* logs are created.But a startup / shutdown /startup sequence	*/
/* loses the obsolete log info (if no new logs are created after*/
/* the first startup).						*/
/*								*/
/* DEFAULT:  ctBEHAV_PRGOLDLOGS is on.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_PRGOLDLOGS
#define ctBEHAV_PRGOLDLOGS
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_RECHDRORD writes the record header for the unused	*/
/* portion of a variable length record (about to be returned to	*/
/* space management) before writing the shorter length into the	*/
/* record header at the beginning of the variable length record.*/
/*								*/
/* DEFAULT:  ctBEHAV_RECHDRORD is on.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_RECHDRORD
#define ctBEHAV_RECHDRORD
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_READERROR checks for unexpected read errors due to	*/
/* external causes such as another process locking a region of	*/
/* a file, and rendering the region unreadable. Windows is the	*/
/* prime example of an OS that generates a read error if another*/
/* another process locks the area. Unix generally permits one	*/
/* process to read a region loocked by another.			*/
/*								*/
/* DEFAULT:  ctBEHAV_READERROR is off except for Windows	*/
/*--------------------------------------------------------------*/
#ifdef ctBEHAV_READERROR
#ifdef NO_ctBEHAV_READERROR
#undef ctBEHAV_READERROR
#endif
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_LFWEVENT uses a thread suspend / thread resume	*/
/* approach to the commit delay blocking technique. The standard*/
/* approach uses ctblkrqs() to set the block, and the cohort of */
/* waiters stack-up behind a ctblkwat() call. This is fine so	*/
/* far, but the ctblkclr() that "frees" the waiters actually	*/
/* causes each of the waiters to get and immediately release the*/
/* block. This serializes their flow past the released block.	*/
/*								*/
/* Turning this on (see MOD#1759), changes from a ctblkrqs to a	*/
/* system specific thread suspend call (for the waiters), and a	*/
/* thread resume call to free the waiters. But no fast method	*/
/* was found to resume all the waiters any faster (or indeed as	*/
/* fast) than the serialized ctblkrqs/ctblkclr call that is	*/
/* routinely implemented for the ctblkwat routine.		*/
/*								*/
/* The LFWEVENT code after the blocker wakes up attempts to get */
/* lflsema with an infinite wait. This may subject to a deadlock*/
/* as described in MOD#0885 (ctree.1.doc).			*/
/*								*/
/* Examining thread docs did not reveal any low level object	*/
/* that permitted a group of waiting threads to be released with*/
/* one call AND that did not require each of the released	*/
/* threads to acquire a synchronization object. For example,	*/
/* conditioned variables support a broadcast call to release	*/
/* all waiting threads, but each of these threads must acquire	*/
/* a mutex! What is the point of the broadcast call?		*/
/*								*/
/* DEFAULT:  ctBEHAV_LFWEVENT is off				*/
/*--------------------------------------------------------------*/
#ifdef ctBEHAV_LFWEVENT
Make sure system dependent coding has been accomplished! This
includes making the thread handles public in the ctthdhnd array.
Checkout the possible deadlock described above.
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_USRSEMA changes the strategy for USR1 to acquiring	*/
/* the ct_usesema(USR2) when USR1 is "cleaning" a node's special*/
/* transaction marks during an ordinary ctgetnod81() call. If	*/
/* the owner of the mark, USR2, appears [before acquiring the	*/
/* ct_usrsema(USR2)] to be committing its transaction, then	*/
/* USR1 attempts to acquire ct_usrsema(USR2) with a NOWAIT. If	*/
/* it gets the sema, no change in procedure. If it fails to get	*/
/* the sema, we return an indication that the key update is	*/
/* still uncommitted.						*/
/*								*/
/* DEFAULT:  ctBEHAV_USRSEMA is on.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_USRSEMA
#define ctBEHAV_USRSEMA
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_MXLFW uses multiple lfwsema's to avoid the pre-	*/
/* block yield requirement. This DOES NOT establish separate	*/
/* log channels or commit delay channels; only one commit delay	*/
/* block is operable at a time.					*/
/*								*/
/* DEFAULT:  ctBEHAV_MXLFW is on if ctCACHE_MEMORY is on.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_MXLFW
#ifdef ctCACHE_MEMORY
#define ctBEHAV_MXLFW
#ifndef ctMXLFW
#define ctMXLFW		3
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_LFLSEMA gives the commit delay flushing thread a	*/
/* high priority when attempting to reacquire the lflsema. This */
/* option is available in the event a commit delay livelock is	*/
/* reported in CTSTATUS.FCS.					*/
/*								*/
/* DEFAULT:  ctBEHAV_LFLSEMA is off.				*/
/*--------------------------------------------------------------*/
/*
#define ctBEHAV_LFLSEMA
*/


/*--------------------------------------------------------------*/
/* ctBEHAV_TRANDISC enables logic to permit a transaction that	*/
/* appears inactive, and that will cause an increase in log	*/
/* files beyond the allowed limit, to be disconnected by closing*/
/* the communication channel of the client.			*/
/*								*/
/* This only applies to ctSRVR implementations			*/
/*								*/
/* DEFAULT:  ctBEHAV_TRANDISC is on for servers.		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_TRANDISC
#ifdef ctSRVR
#define ctBEHAV_TRANDISC
#endif
#endif

#ifndef ctSRVR
#ifdef ctBEHAV_TRANDISC
#undef ctBEHAV_TRANDISC
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_NEWLOG_TRAN uses a protected call to ctgettrn to	*/
/* initialize the starting transaction number for a new log	*/
/* file. This is only supported for MULTITRD			*/
/*								*/
/* ctBEHAV_NEWLOG_TRANhdr adds mutex protection to the		*/
/* transaction number written during log header writes.		*/
/*								*/
/* DEFAULT:  ctBEHAV_NEWLOG_TRAN is on for MULTITRD		*/
/* DEFAULT:  ctBEHAV_NEWLOG_TRANhdr is on for MULTITRD		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_NEWLOG_TRAN
#ifdef MULTITRD
#define ctBEHAV_NEWLOG_TRAN
#endif
#endif
#ifndef NO_ctBEHAV_NEWLOG_TRANhdr
#ifdef MULTITRD
#define ctBEHAV_NEWLOG_TRANhdr
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_MBR_SUPER puts a sticky bit in tflmod2 to indicate 	*/
/* superfile member status. The suptyp bit has a small window	*/
/* where it is cleared.						*/
/*								*/
/* DEFAULT:  ctBEHAV_MBR_SUPER is on for CTSUPER		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_MBR_SUPER
#ifdef CTSUPER
#define ctBEHAV_MBR_SUPER
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DUPLFATAL makes the DUPL_ERR(652) set the index 	*/
/* corupt flag if keys are rejected (duplicates or bad serial	*/
/* segs) and the rejected keys are only listed, with no purge of*/
/* the associated data and indices.				*/
/*								*/
/* For servers, this new behavior requires both the BEHAV and	*/
/* COMPATIBILITY DUPL_ERR_FATAL in the configuration info.	*/
/*								*/
/* DEFAULT:  ctBEHAV_DUPLFATAL is on for servers, off otherwise	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_DUPLFATAL
#ifdef ctSRVR
#ifndef ctBEHAV_DUPLFATAL
#define ctBEHAV_DUPLFATAL
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_STRICTOEM_LOGONu prevents an OEM ctree Client from 	*/
/* connecting to a standard c-tree server (non-oem server).	*/
/* Server and client must match					*/
/* DEFAULT:  ctBEHAV_STRICTOEM_LOGONu is off by default 	*/
/*           and is set on in each OEM specific section.       	*/
/* #define ctBEHAV_STRICTOEM_LOGONu 				*/
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/* ctBEHAV_STRICTOEM_LOGONu_CS_VERSION_CHECK prevents an OEM 	*/
/*  ctree Client from connecting to a server with a different	*/
/* Product version. Server and client version number must match.*/
/* ctVER_MAJOR - Major version number.				*/
/* ctVER_MINOR - Minor version number.				*/
/* ctVER_MINI  - Mini version number.				*/
/* ctVER_REVSN - Product Revision number.			*/
/* DEFAULT:  ctBEHAV_STRICTOEM_LOGONu_CS_VERSION_CHECK is off  	*/
/*           by default and is set on in each OEM specific section.*/
/* #define ctBEHAV_STRICTOEM_LOGONu_CS_VERSION_CHECK 		*/
/*--------------------------------------------------------------*/

/*--------------------------------------------------------------*/
/* ctBEHAV_ISAMDFRCLS causes all files closed or deleted by a	*/
/* call to an ISAM level close or delete to have the action	*/
/* deferred if anyone of the files requires the action to be	*/
/* deferred. Without this turned on, a call to close or delete	*/
/* an ISAM set of iles might result in some actual closes or	*/
/* deletes and some deferrals.					*/
/*								*/
/* DEFAULT:  ctBEHAV_ISAMDFRCLS is on by default 		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_ISAMDFRCLS
#ifndef ctBEHAV_AbortOnClose
#ifdef TRANPROC
#define ctBEHAV_ISAMDFRCLS
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_ITIMunlock causes locks obtained on records as part	*/
/* of an ISAM read that fail either a delete flag test or a key	*/
/* value consistency test to be freed before a retry is		*/
/* attempted. Without this turned on, the locks are freed when	*/
/* either LKISAM(FREE) or a transaction is completed, but the	*/
/* un-needed lock could cause a deadlock error.			*/
/*								*/
/* DEFAULT:  ctBEHAV_ITIMunlock is on by default 		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_ITIMunlock
#define ctBEHAV_ITIMunlock
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CTREErecurcnt enables a recursion counter for the    */
/* c-tree client single entry point function. This counter is   */
/* used to reset the client-side OPS_lockon state for recursive */
/* calls to the single entry point function.                    */
/*								*/
/* DEFAULT:  ctBEHAV_CTREErecurcnt is on by default 		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CTREErecurcnt
#define ctBEHAV_CTREErecurcnt
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_NEWVSPC causes new variable length record space to	*/
/* be marked as deleted before the end of a transaction. This	*/
/* avoids a VFLG_ERR(158) when another user is scanning un-	*/
/* committed new space in a variable length file in physical	*/
/* order. By new space we mean space added to the logical end	*/
/* of file.							*/
/*								*/
/* COMPATIBILITY NO_INIT_VSPACE turns off this change at	*/
/* server run-time.						*/
/*								*/
/* DEFAULT:  ctBEHAV_NEWVSPC is on by default for MULTITRD	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_NEWVSPC
#ifdef MULTITRD
#define ctBEHAV_NEWVSPC
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_LOGEXTFILrcv causes LOGEXTFIL log entries to be	*/
/* acted on during transaction redo. Ordinarily, LOGEXTFIL	*/
/* is only acted on during transaction undo. ctBEHAV_NEWVPSC	*/
/* causes a change in log entries that must be dealt with in	*/
/* one of two ways: (1) change the nature of log entry follow-	*/
/* ing the LOEXTFIL (specifically use OLDIMAGE/NEIMAGE instead	*/
/* of DIFIMAGE on variable record length headers and resource	*/
/* headers); or (2) act on LOGEXTFIL's during transaction	*/
/* redo during automatic recovery.				*/
/*								*/
/* By default the first approach will be used.			*/
/*								*/
/* ctSIBLING_ctdiff: when the 1st approach is used (i.e.,	*/
/* ctBEHAV_LOGEXTFILrcv is NOT enabled) ctIO_DRHD and ctIO_RSHD	*/
/* are used to inhibit the call to ctdiff when logging record	*/
/* and resource header I/O.					*/
/*								*/
/* DEFAULT:  ctBEHAV_LOGEXTFILrcv is off by default.		*/
/*--------------------------------------------------------------*/
/* #define ctBEHAV_LOGEXTFILrcv */


/*--------------------------------------------------------------*/
/* ctBEHAV_CHGPAGE permits the rebuild logic to reduce the	*/
/* page/node size during rebuild. This especially affects	*/
/* variable length files with their internal space management	*/
/* indices.							*/
/*								*/
/* Without this turned on, trying to rebuild a variable length	*/
/* data file with a smaller page size fails with KSIZ_ERR(40).	*/
/*								*/
/* DEFAULT:  ctBEHAV_CHGPAGE is on by default			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHGPAGE
#define ctBEHAV_CHGPAGE
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_SHTLOOP enables a check for pending closes, and	*/
/* optional retries if WAIT_ON_SHUTDOWN_SEC time limit is not	*/
/* exceeded.							*/
/*								*/
/* DEFAULT:  ctBEHAV_SHTLOOP is on by default			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SHTLOOP
#define ctBEHAV_SHTLOOP
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_ABTEXC uses a an internal file mode bit,		*/
/* ctFLMD_ABTEXC, to indicate whether or not a file requires	*/
/* the "global" tfil counter.					*/
/*								*/
/* DEFAULT:  ctBEHAV_ABTEXC is on by default for MULTITRD	*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctBEHAV_ABTEXC
#define ctBEHAV_ABTEXC
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CACHELOOP dynamically changes the ctdefer time from	*/
/* zero to ten milliseconds if the first data cache retry still	*/
/* leaves the thread waiting for the LRU data cache to be	*/
/* written to the OS.						*/
/*								*/
/* DEFAULT:  ctBEHAV_CACHELOOP is on by default for MULTITRD	*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctBEHAV_CACHELOOP
#define ctBEHAV_CACHELOOP
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CMTLOK supports implied read locks to ensure con-	*/
/* sistent reads without explicit locks even when a transaction	*/
/* is transferring preimages to the file system.		*/
/*								*/
/* ctBEHAV_CMTLOK requires MULTITRD, ctHUGEFILE and TRANPROC	*/
/*								*/
/* DEFAULT:  ctBEHAV_CMTLOK is enabled for server only when	*/
/* ct_V90_GENERATION is defined.				*/
/*--------------------------------------------------------------*/
#ifdef ct_V90_GENERATION
#ifndef NO_ctBEHAV_CMTLOK
#define ctBEHAV_CMTLOK
#endif
#endif

#ifdef ctBEHAV_CMTLOK
#ifndef MULTITRD
#undef ctBEHAV_CMTLOK
#else
#ifndef ctHUGEFILE
#undef ctBEHAV_CMTLOK
#else
#ifndef TRANPROC
#undef ctBEHAV_CMTLOK
#endif
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CHKSAVE enables the ctsave() routine, used to sync	*/
/* file system buffers to disk which is one of the slowest	*/
/* operations we encounter, to avoid the system call if no	*/
/* writes have been performed on the file descriptor in		*/
/* question since the last ctsave.				*/
/*								*/
/* CHKSAVE requires ctFeatCHANNELS and ctALGNCHNL at this phase	*/
/* of implementation.						*/
/*								*/
/*								*/
/* DEFAULT:  ctBEHAV_CHKSAVE is on by default			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHKSAVE
#define ctBEHAV_CHKSAVE
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CLN_GETNOD permits nonTRANPROC code to cleanup	*/
/* key-level transaction processing "locks" that have persisted	*/
/* on disk. ONly an index that is permitted to switch between	*/
/* TRANPROC and nonTRANPROC implementations is affected by this	*/
/* change.							*/
/*								*/
/* TRANPROC requires ctBEHAV_CLN_GETNOD, otherwise it is	*/
/* optional.							*/
/*								*/
/* DEFAULT:  ctBEHAV_CLN_GETNOD is on by default		*/
/*--------------------------------------------------------------*/
#ifdef NO_ctBEHAV_CLN_GETNOD
#ifdef TRANPROC			/* override NO_...		*/
#define ctBEHAV_CLN_GETNOD
#endif
#else
#define ctBEHAV_CLN_GETNOD
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_FILCRECHK changes the checkpoint behavior when a	*/
/* TRNLOG file is renamed or deleted. Without this enabled,	*/
/* a delete or rename that occurs after a file create, with no	*/
/* intervening checkpoint, will generate a checkpoint. This is	*/
/* to avoid recovery problems since recovery is not designed to	*/
/* redo	file create/delete sequences [unless the file is also	*/
/* TRANDEP in which case the checkpoints are not required].	*/
/*								*/
/* For servers, this new behavior can be suspended at run-time	*/
/* by adding COMPATIBILITY FILE_CREATE_CHECKPOINT		*/
/*								*/
/* DEFAULT:  ctBEHAV_FILCRECHK is on by default; but must be	*/
/* turned off ifndef ctHUGEFILE.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_FILCRECHK
#define ctBEHAV_FILCRECHK
#endif

#ifdef ctBEHAV_FILCRECHK
#ifndef ctHUGEFILE
#undef ctBEHAV_FILCRECHK
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_FLUSHonCLOSE forces a file system cache flush before	*/
/* physically closing a transaction logged or write-thru file.	*/
/* This ctBEHAV should be used when a file close does NOT cause	*/
/* a synchronous flush of the file system cache associated with	*/
/* the file.							*/
/*								*/
/* For servers, this new behavior can be suspended at run-time	*/
/* by adding COMPATIBILITY NO_SYS_FLUSH_ON_CLOSE to the		*/
/* configuration info.						*/
/*								*/
/* DEFAULT:  ctBEHAV_FLUSHonCLOSE is on by default		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_FLUSHonCLOSE
#define ctBEHAV_FLUSHonCLOSE
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_NATIVE_IFIL causes the client communication interface*/
/* to check for a mismatch between an ALIGNMENT_COMP override	*/
/* and the actual (native) alignment of the IFIL structure.	*/
/*								*/
/* DEFAULT:  ctBEHAV_NATIVE_IFIL is on by default		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_NATIVE_IFIL
#define ctBEHAV_NATIVE_IFIL
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_FCRESsec enables protection for FairCom file		*/
/* definition resources (FCRES) from accidental or malicious	*/
/* attempts to modify them using direct calls to the resource	*/
/* API.								*/
/*								*/
/* When ctBEHAV_FCRESsec is enabled, the server configuration	*/
/* keyword							*/
/*		FILEDEF_SECURITY_LEVEL <level>			*/
/* controls the strength of the security checks. The <level>	*/
/* maybe LOW, MEDIUM, or HIGH with a default of MEDIUM. LOW	*/
/* effectively turns off the security checks enabled by this	*/
/* #define. MEDIUM requires at least exclusive file locks to	*/
/* directly update a file definition. HIGH requires the user	*/
/* to have definition permissions (OPF_DEF) in addition to the	*/
/* file lock.							*/
/*								*/
/* MOD#10460 adds a 4th <level>: INTERNAL. INTERNAL enforces	*/
/* the restriction that a file definition resource update must	*/
/* be called from an API designed specifically to maintain the	*/
/* definition in question. A direct call to ADDRES/UPDRES/DELRES*/
/* will be denied.						*/
/*								*/
/* ctBEHAV_FCRESsec is off by default.				*/
/* ctBEHAV_FCRESsec requires server support.			*/
/*--------------------------------------------------------------*/
/*
#ifndef NO_ctBEHAV_FCRESsec
#ifdef ctSRVR
#define ctBEHAV_FCRESsec
#endif
#endif
*/

#ifdef ctBEHAV_FCRESsec
#ifndef ctSRVR
#undef ctBEHAV_FCRESsec
#endif
#endif

/* Enable setting and resetting of the CTSTAT2_FCRES ctstat2 bit. */
#define ctBEHAV_FCRESbit

#ifdef ctBEHAV_FCRESsec
#ifndef ctBEHAV_FCRESbit
#error ctBEHAV_FCRESsec requires ctBEHAV_FCRESbit
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_TCOL_ERR changes how ctTranLockOut checks for	*/
/* collisions between two processes using transaction logs. When*/
/* ctBEHAV_TCOL_ERR is enabled, a more restrictive approach	*/
/* ensures that two processes do not share any directories for	*/
/* the essential transaction-log-related files.			*/
/*								*/
/* ctBEHAV_TCOL_ERR is on by default.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_TCOL_ERR
#define ctBEHAV_TCOL_ERR
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_SS_TRNFIL eliminates calls to hasredlok() for non-	*/
/* transaction files when strict serialization has been invoked.*/
/* Without this enabled, hasredlok() may generate a negative	*/
/* read lock count warning while processing a non-transaction	*/
/* file. With this enabled, calls to ctaglok() [which acquires	*/
/* a special aggregate lock for serialization] are skipped for	*/
/* non-transaction files.					*/
/*								*/
/* ctBEHAV_SS_TRNFIL is on by default, but only affects code	*/
/* with advanced strict serialization support.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SS_TRNFIL
#define ctBEHAV_SS_TRNFIL
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_UPDATE_CONTEXT updates ISAM context key definitions	*/
/* when indexes are created and deleted.			*/
/*								*/
/* ctBEHAV_UPDATE_CONTEXT is enabled for ct_V90_GENERATION	*/
/* compiles only. We will turn it on in general once final QA	*/
/* testing is complete.						*/
/*--------------------------------------------------------------*/
#ifdef ct_V90_GENERATION
#define ctBEHAV_UPDATE_CONTEXT
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_UNDO_OCMTX coordinates the behavior of two threads	*/
/* where the 1st thread owns ctpocsema and is trying to clean-	*/
/* up special marks, and the 2nd thread is trying to finish	*/
/* a transaction and requires ctpocsema to perform a TRANDEP	*/
/* undo operation (e.g., ctundodel2()). In this situation, the	*/
/* 1st thread loops on calls to ctclup() while the 2nd thread	*/
/* stays blocked at the call to request the ctpocsema mutex.	*/
/* Developer Log entry 10323 contains a description of how	*/
/* to cause this deadlock problem.				*/
/*								*/
/* Requires ctBEHAV_USRSEMA and MULTITRD.			*/
/*								*/
/* DEFAULT:  ctBEHAV_UNDO_OCMTX is on.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_USRSEMA
#ifdef ctBEHAV_USRSEMA
#ifdef MULTITRD
#define ctBEHAV_UNDO_OCMTX
#endif
#endif
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_LOCK_rensup cause a lock to be placed on a superfile	*/
/* member header image [the image conatins the superfile member */
/* name and the contents of the superfile member header] when	*/
/* the rensup() routine is called. rensup() renames the super-	*/
/* file member by changing the entry in the superfile index	*/
/* directory and the name in the header image. The lock is	*/
/* required when commit read lock logic has been enabled other-	*/
/* wise some superfile operations such as deleting a superfile	*/
/* member can cause a CMLK_ERR(768).				*/
/*								*/
/* Requires ctBEHAV_CMTLOK					*/
/*								*/
/* DEFAULT: ctBEHAV_LOCK_rensup is on.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_LOCK_rensup
#ifdef ctBEHAV_CMTLOK
#define ctBEHAV_LOCK_rensup
#endif
#endif


/*
** default ctBEHAV_CLUP off for now

#ifndef NO_ctBEHAV_CLUP
#ifdef MULTITRD
#ifdef TRANPROC
#define	ctBEHAV_CLUP
#define ctCLUPary	32
#endif
#endif
#endif

**
*/


/*--------------------------------------------------------------*/
/* ctBEHAV_RETRY_FORCEI changes the key level lock clean-up by	*/
/* treating the 1st and 2nd phases of a transaction commit	*/
/* differently. Without this modification, ctacttrn81(), which	*/
/* checks whether or not a key level lock is for an active	*/
/* transaction, signals a retry if the key level lock is for a	*/
/* transaction that has begun a commit. With this modification,	*/
/* clean-up is retried only if the commit is in the 2nd phase	*/
/* signified by the start of forcei().				*/
/*								*/
/* The benefit of this change was highlighted by tests that	*/
/* introduced an indefinite delay between the 1st and 2nd	*/
/* phases of transaction commit.				*/
/*								*/
/* MULTITRD, TRANPROC and ctBEHAV_USRSEMA are required, and	*/
/* the default is on.						*/
/*--------------------------------------------------------------*/
#if defined(MULTITRD) && defined(TRANPROC) && defined(ctBEHAV_USRSEMA) && \
   !defined(ctBEHAV_RETRY_FORCEI)
#ifndef NO_ctBEHAV_RETRY_FORCEI
#ifndef ctPortDSTINTL		/* Per performace tests on 131111 */
#define ctBEHAV_RETRY_FORCEI	/* ctPortDSTINTL_ONLY_QUESTION */
#endif
#endif
#endif

#if defined(ctBEHAV_RETRY_FORCEI) && (!defined(MULTITRD) ||	\
   !defined(TRANPROC) || !defined(ctBEHAV_USRSEMA) ||		\
    defined(NO_ctBEHAV_USRSEMA))
#undef ctBEHAV_RETRY_FORCEI
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_ITIM_DEFER causes a defer(0) to occur before each	*/
/* ITIM_ERR retry. It may be especially useful in FairCom	*/
/* proprietary threading implementations which are not		*/
/* pre-emptive.							*/
/*								*/
/* MULTITRD is required, and the default is on.			*/
/*--------------------------------------------------------------*/
#define ctBEHAV_ITIM_DEFER

#ifdef ctBEHAV_ITIM_DEFER
#ifndef MULTITRD
#undef ctBEHAV_ITIM_DEFER
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_NEWLOCK permits calls to cts_lok81() with a new	*/
/* mode, ADD_LOCK_NEW, that denies a lock request if the caller	*/
/* already owns a lock on the requested record. In this case,	*/
/* cts_lok81() returns an LNEW_ERR.				*/
/*								*/
/* MULTITRD is required, and the default is off.		*/
/*--------------------------------------------------------------*/
/* #define ctBEHAV_NEWLOCK */

#ifdef ctBEHAV_NEWLOCK
#ifndef MULTITRD
#undef ctBEHAV_NEWLOCK
#endif
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_READLOCK permits a call to SETOPS(OPS_READLOCK,...)	*/
/* which invokes low level automatic read locks on every record	*/
/* read that does not already have a lock. The lock is freed	*/
/* automatically after the record is read. These automatic read	*/
/* locks will continue to be requested until SETOPS is used to	*/
/* turn off the state.						*/
/*								*/
/* The read locks are acquired with a blocking request so that	*/
/* (1) an existing application that adds the SETOPS call will	*/
/* not require any changes; and (2) a read request will block	*/
/* until the read lock is granted.				*/
/*								*/
/* MULTITRD and ctBEHAV_NEWLOCK are required, and the default	*/
/* is on.							*/
/*--------------------------------------------------------------*/
#define ctBEHAV_READLOCK

#ifdef ctBEHAV_READLOCK
#ifndef MULTITRD
#undef ctBEHAV_READLOCK
#endif
#ifndef ctBEHAV_NEWLOCK
#define ctBEHAV_NEWLOCK
#endif
#endif /* ctBEHAV_READLOCK */



/*--------------------------------------------------------------*/
/* ctBEHAV_IDXSTK changes two behaviors related to the reuse of	*/
/* deleted nodes. [Nodes deleted from an index may be placed on	*/
/* a delete stack for eventual reuse.]   (1) In single user	*/
/* TRANPROC the header is now written each time a node is	*/
/* pushed on top of the delete stack. (2) During automatic	*/
/* recovery (single or multi-user), more of an effort is made	*/
/* to maintain a delete stack.					*/
/*								*/
/* Without this turned on, A non-LOGIDX index always had its	*/
/* delete stack discarded if it was touched during recovery;	*/
/* and a LOGIDX index would discard its delete stack if any	*/
/* problem was found with the stack. Now the delete stack is	*/
/* attempted to be maintained with or without LOGIDX, and is	*/
/* used in part even if a problem is found somewhere down the	*/
/* delete stack.						*/
/*								*/
/* DEFAULT: ctBEHAV_IDXSTK is on for single user TRANPROC	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_IDXSTK
#ifdef TRANPROC
#ifndef MULTITRD
#define ctBEHAV_IDXSTK
#endif
#endif
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_SAVE_KYMAP preserves ct_kymap to avoid premature	*/
/* termination of the deletion of indices in ishtifil. When	*/
/* enabled, ishtifil behavior is only changed during the delete	*/
/* of superfile member indices that are nonTRAN or no		*/
/* transaction is active.					*/
/*								*/
/* ctBEHAV_SAVE_KYMAP requires MULTITRD support			*/
/* DEFAULT: ctBEHAV_SAVE_KYMAP is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SAVE_KYMAP
#ifdef MULTITRD
#define ctBEHAV_SAVE_KYMAP
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_HOST_MEMBER_LOCK switches the lock on newly reused	*/
/* space taken from the host SUPERFILE's spacemanagement pool	*/
/* to the the requesting member's file number. Otherwise a	*/
/* DADV_ERR(57) error may occur on a subsequent write to this	*/
/* space using the member's file number.			*/
/*								*/
/* ctBEHAV_HOST_MEMBER_LOCK require MUSTFRCE			*/
/* DEFAULT: ctBEHAV_HOST_MEMBER_LOCK is on			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_HOST_MEMBER_LOCK
#define ctBEHAV_HOST_MEMBER_LOCK
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_BATINS_CURI changes the batch insertion treatment of	*/
/* the current ISAM position. Instead of keeping the current	*/
/* ISAM position unchanged, when this BEHAV is enabled the	*/
/* current ISAM position becomes the last record inserted in	*/
/* the batch operation.						*/
/*								*/
/* DEFAULT: ctBEHAV_BATINS_CURI is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_BATINS_CURI
#define ctBEHAV_BATINS_CURI
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CHKMBRNAMLEN enforces the ctfnz file name limit on	*/
/* superfile members. Without this define, which is on by	*/
/* default, superfile member names that exceed the ctfnz limit	*/
/* are accepted, but the corresponding entry in the superfile	*/
/* directory index is truncated. This could lead to file	*/
/* creation errors DOPN_ERR and KOPN_ERR if the truncated name	*/
/* of new member matches the truncated name of an existing	*/
/* member. If this new behavior is enabled, then an attempt to	*/
/* create a superfile member with name longer than ctfnz	*/
/* results in a SNAM_ERR(418).					*/
/*								*/
/* COMPATIBILITY NO_CHKMBRNAMLEN turns off this new behavior to	*/
/* permit backward compatibility for cases where the truncated	*/
/* superfile member name did not cause a problem.		*/
/*								*/
/* DEFAULT: ctBEHAV_CHKMBRNAMLEN is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHKMBRNAMLEN
#define ctBEHAV_CHKMBRNAMLEN
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_AUTO_NONTRAN screens files on the AUTO_TRNLOG and	*/
/* AUTO_PREIMG configuration lists so that only files without	*/
/* transaction support in their file modes are enabled for	*/
/* automatic transactions. Without this define, any file	*/
/* appearing on the confiiguration lists will receive automatic	*/
/* transaction support. [If an explicit transaction has been	*/
/* started, then automatic transaction support is ignored.]	*/
/*								*/
/* DEFAULT: not defined						*/
/*--------------------------------------------------------------*/
/*
#define ctBEHAV_AUTO_NONTRAN
*/


/*--------------------------------------------------------------*/
/* ctBEHAV_DAYLIGHT_SAVINGS_TIME_ADJUSTMENT corrects the 	*/
/* computation of a date relative to today's date to account	*/
/* for differences in daylight savings time between today and	*/
/* the target date.						*/
/*								*/
/* DEFAULT: defined						*/
/*--------------------------------------------------------------*/
#define ctBEHAV_DAYLIGHT_SAVINGS_TIME_ADJUSTMENT


/*--------------------------------------------------------------*/
/* ctBEHAV_CHECK_DELETE_STACK adds diagnostic checks for a fixed*/
/* record length delete stack being set to all 0xff's. Even	*/
/* if this BEHAV is not turned on, the NEWREC routine now	*/
/* resets the delete stack to empty (and issues a CTSTATUS.FCS	*/
/* warning) if the delete stack is all 0xff's.			*/
/*								*/
/* DEFAULT: NOT defined						*/
/*--------------------------------------------------------------*/
/*
#define ctBEHAV_CHECK_DELETE_STACK
*/


/*--------------------------------------------------------------*/
/* ctBEHAV_RENFIL_FLUSH causes a file's buffer/cache pages to	*/
/* be flushed prior to a system level rename (which may be	*/
/* invoked by a TRANDEP delete as well as an explicit rename	*/
/* call such as ctRENFIL). This necessary since even though the	*/
/* file is opened exclusively, it may have updated buffer/cache	*/
/* pages which could receive a write request from another	*/
/* thread searching for the next available page; and the system	*/
/* level rename requires the file to be closed and then		*/
/* reopened.							*/
/*								*/
/* The renseg() internal routine, which manages renaming file	*/
/* segments, has not been modified (even though it has a close,	*/
/* reopen sequence) since it is called either for unused	*/
/* segments, or during the delete of a segmented file. In the	*/
/* former case, no data could be in buffer/cache pages, and in	*/
/* the latter case, the new flush logic is already effective.	*/
/* However, when the renaming of a segmented file (in entirety)	*/
/* is supported, we must check to ensure a flush occurs for the	*/
/* entire file before renseg is called for any of the segments.	*/
/*								*/
/* DEFAULT: defined for MULTITRD				*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctBEHAV_RENFIL_FLUSH
#define ctBEHAV_RENFIL_FLUSH
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_FATAL_FAILED_TRAN_IO causes failed write operations	*/
/* for TRNLOG files to cause the server to terminate with a	*/
/* ctcatend [L60 and Mx where x >= 1 and the value of x		*/
/* determines the specific ctcatend in the source]. In particu-	*/
/* lar, this change affects the write operations of buffer and	*/
/* cache pages, and header write operations for TRNLOG files.	*/
/* Additionally, failed ctcomexc81 operation [where ctcomexc81	*/
/* maintains the lists of unflused buffer and cache pages]	*/
/* cause a L60 ctcatend. ctcomexc81's only failure mode is a	*/
/* memory (sublist) allocation problem.				*/
/*								*/
/* COMPATIBILITY FAILED_TRAN_IO will restore prior behavior,	*/
/* effectively nullifying turning on this ctBEHAV for a server.	*/
/*								*/
/* DEFAULT: defined for TRANPROC (and requires TRANPROC)	*/
/*--------------------------------------------------------------*/
#ifdef TRANPROC
#ifndef NO_ctBEHAV_FATAL_FAILED_TRAN_IO
#define ctBEHAV_FATAL_FAILED_TRAN_IO
#endif
#else  /* ~TRANPROC */
#ifdef ctBEHAV_FATAL_FAILED_TRAN_IO
#undef ctBEHAV_FATAL_FAILED_TRAN_IO
#endif
#endif /* ~TRANPROC */


/*--------------------------------------------------------------*/
/* ctBEHAV_CHKP_SPLIT_COMMIT corrects an unusual automatic	*/
/* recovery problem that may occur when a transaction commit	*/
/* writes its TRANEND log entry and then is interrupted by a	*/
/* checkpoint before completing the commit. For the problem to	*/
/* occur, the split transaction commit must have had all its	*/
/* updated index nodes flushed to disk and not be using the	*/
/* ctLOGIDX mode. If this is the case, then the checkpoint	*/
/* contains conflicting information: (1) the transaction must	*/
/* be redone (at least with respect to data cache pages); and	*/
/* (2) the index may need some nodes to have their update	*/
/* operations undone (because of abort node list entries). The	*/
/* first of these is correct and the second is wrong.		*/
/*								*/
/* This BEHAV corrects the problem by checking entries in the	*/
/* abort node list against transactions that are being redone.	*/
/* If the transaction is on the redo list, then the abort node	*/
/* entry is ignored. [Fundamentally the problem arises because	*/
/* the abort node list cannot be purged until after the TRANEND	*/
/* is written to disk, but unless we introduce additional	*/
/* mutex control over the list purge and the checkpoint, we are	*/
/* open to this inconsistency. It is better to deal with the	*/
/* problem during recovery (which occurs infrequently) than	*/
/* during each and every checkpoint.]				*/
/*								*/
/* DEFAULT: defined for TRANPROC (and requires TRANPROC)	*/
/*--------------------------------------------------------------*/
#ifdef TRANPROC
#ifndef NO_ctBEHAV_CHKP_SPLIT_COMMIT
#define ctBEHAV_CHKP_SPLIT_COMMIT
#endif
#else  /* ~TRANPROC */
#ifdef ctBEHAV_CHKP_SPLIT_COMMIT
#undef ctBEHAV_CHKP_SPLIT_COMMIT
#endif
#endif /* ~TRANPROC */


/*--------------------------------------------------------------*/
/* ctBEHAV_NO_USER_LOCKS turns off all user lock table entries	*/
/* for single-user environments. Without this define, some	*/
/* operations such as LKISAM update user lock table entries	*/
/* even in single user applications; while other operations	*/
/* such as LOKREC(ctFREE_FILE) ignore the (single-user) user	*/
/* lock table entries. Whether or not ctBEHAV_NO_USER_LOCKS is	*/
/* defined, single-user applications do NOT make system lock	*/
/* calls. It is only a question of whether c-tree user lock	*/
/* tables will be maintained.					*/
/*								*/
/* ctBEHAV_NO_USER_LOCKS must not be turned on when MUSTFRCE is	*/
/* in effect. Further down in ctopt2.h, the state of MUSTFRCE	*/
/* is checked to determine if ctBEHAV_NO_USER_LOCKS must be	*/
/* turned off.							*/
/*								*/
/* Default: ctBEHAV_NO_USER_LOCKS is on for single-user systems	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_NO_USER_LOCKS
#define ctBEHAV_NO_USER_LOCKS
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_ADATA_FORCEI causes calls to ctcomexc81() for	*/
/* vulnerable data cache pages to be ignored if the call is	*/
/* made outside of the forcei() context. Two such out-of-	*/
/* context calls have been identified: variable length data	*/
/* file extension when ctBEHAV_NEWVSPC is defined; and		*/
/* (2) index file extension for a SUPERFILE member.		*/
/*								*/
/* ctBEHAV_ADATA_FORCEI only affects TRANPROC implementations.	*/
/*								*/
/* Default: ctBEHAV_ADATA_FORCEI is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_ADATA_FORCEI
#define ctBEHAV_ADATA_FORCEI
#endif


/*--------------------------------------------------------------*/
/* BAT_LOK_ONE changes the locking strategy for a batch from	*/
/*	(a) holding locks for the result set until the batch is	*/
/* completed; to						*/
/*	(b) only holding a record lock while the record is	*/
/* read.							*/
/*								*/
/* Before this modification, BAT_LOK_ONE was ignored unless	*/
/* BAT_PHYS was in effect. When ctBEHAV_BAT_LOK_ONE is defined,	*/
/* BAT_LOK_ONE will be active when BAT_PHYS and/or BAT_RET_REC	*/
/* or BAT_RET_FIX are part of the batch request mode. Other	*/
/* retrieval strategies such as BAT_RET_POS cannot be used with	*/
/* BAT_LOK_ONE, and the batch request will fail with a		*/
/* BTRQ_ERR(430).  When ctBEHAV_BAT_LOK_ONE is not defined, the	*/
/* behavior is the same as before the modification EXCEPT that	*/
/* using BAT_LOK_ONE without BAT_PHYS is not allowed (instead	*/
/* of being ignored) and returns a BTRQ_ERR.			*/
/*								*/
/* ctBEHAV_BAT_LOK_ONE is off by default.			*/
/*--------------------------------------------------------------*/
#ifndef ctBEHAV_BAT_LOK_ONE
#define ctBEHAV_BAT_LOK_ONE
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_WRTHDR_FORCEI changes how SH_HDRWORD entries that	*/
/* cause a file header write (wrthdr) in forcei() are processed.*/
/* When such a wrthdr() request is for an index file that has	*/
/* been recently opened and not yet been included in a check-	*/
/* point, then the current on disk values for nument1/2 are	*/
/* preserved (even though the current memory image about to be	*/
/* written to disk may have updated values). This change is to	*/
/* avoid an auto recovery problem with the index nument1/2	*/
/* values.							*/
/*								*/
/* ctBEHAV_WRTHDR_FORCEI only affects TRANPROC implementations.	*/
/*								*/
/* Default: ctBEHAV_WRTHDR_FORCEI is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_WRTHDR_FORCEI
#ifdef TRANPROC
#define ctBEHAV_WRTHDR_FORCEI
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CHKPDFC changes how a server behaves when logs are	*/
/* detected without any checkpoints. Ordinarily, several check-	*/
/* points are expected each log. Without this new behavior,	*/
/* two consecutive logs without checkpoints will cause the	*/
/* server to terminate with a CHKP_ERR(529). The new behavior	*/
/* is more forgiving and permits more logs to be written	*/
/* without checkpoints, and before stopping the server,		*/
/* introduces a short wait for each non-checkpoint log write	*/
/* in order to permit a checkpoint to occur if it is simply	*/
/* caught in a race condition. A CHKP_ERR(529) is still		*/
/* possible if a checkpoint is not written once the log write	*/
/* slow down has had a chance to take effect.			*/
/*								*/
/* ctBEHAV_CHKPDFC only affects MULTITRD, TRANPROC		*/
/* implementations.						*/
/*								*/
/* Default: ctBEHAV_CHKPDFC is on				*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifdef TRANPROC
#define ctBEHAV_CHKPDFC
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_PREFIX_SPLIT changes how a node with leading		*/
/* character compression is split when the computed node split	*/
/* point (expressed as a nth element of the node) will not work	*/
/* because too many bytes will be left in the original node.	*/
/* The original node split point calculation is based on the	*/
/* number of key values in the node, and does not take into	*/
/* account the degree of compression in the individual key	*/
/* values. Without this new behavior, there appears to be a bug	*/
/* when the new split point is recomputed: in some unusual	*/
/* cases not enough bytes have been retained in the original	*/
/* node (meaning too many bytes were shifted to the new node	*/
/* resulting in the memory overwrite. It is worth noting that	*/
/* the essentials of this code have not changed significantly	*/
/* since November, 1989; indicating that the bug is very	*/
/* obscure in actual application. The new behavior changes the	*/
/* recomputation of the node split point so that as many bytes	*/
/* as possible are retained in the original node.		*/
/*								*/
/* In the code, spltel holds the node split element. This is	*/
/* actually the ordinal number of the last key value to be	*/
/* retained in the original node.				*/
/*								*/
/* ctBEHAV_PREFIX_SPLIT only affects VARLKEYS			*/
/*								*/
/* Default: ctBEHAV_PREFIX_SPLIT is on				*/
/*--------------------------------------------------------------*/
#define ctBEHAV_PREFIX_SPLIT


/*--------------------------------------------------------------*/
/* ctBEHAV_RDLblocksRDL permits dellst81() to unlock a read	*/
/* lock that is unexpectedly blocking other read locks. Without	*/
/* the BEHAV turned on, and when ctSSrel2 is turned on, this	*/
/* situation leads to a terr(8698).				*/
/*								*/
/* Default: ctBEHAV_RDLblocksRDL is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_RDLblocksRDL
#define ctBEHAV_RDLblocksRDL
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_logext_tstupd causes ctlogext81() to invoke a call	*/
/* to tstupd() when an entry in pre-image space is made to mark	*/
/* a record location for possible re-use. Without this new	*/
/* behavior it was possible for an unexpected and very unusual	*/
/* error (say a NEWREC or NEWVREC failed with a DLOK_ERR) to	*/
/* cause a ctcatend.						*/
/*								*/
/* Default: ctBEHAV_logext_tstupd is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_logext_tstupd
#define ctBEHAV_logext_tstupd
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_tstupd_err causes some instances of tstupd() that	*/
/* did not check for an error return to now act on such an	*/
/* error return. Also, this modification makes two changes to	*/
/* tstupd: (1) if wrthdr() fails, then ctsave() is not called;	*/
/* and (2) a ctsave() error is returned by tstupd(). The	*/
/* wrthdr() and ctsave() are only called if the file header	*/
/* has not yet had it's updflg set.				*/
/*								*/
/* Some unexamined calls to tstupd() required significant	*/
/* recoding, and were not changed at this time. Such calls can	*/
/* be found in the code by searching for			*/
/*								*/
/*			ctSIBLING_tstupd_uerr_cod		*/
/*								*/
/* Default: ctBEHAV_tstupd_err is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_tstupd_err
#define ctBEHAV_tstupd_err
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CHECK_SPLIT checks the byte counts for the old and	*/
/* new node during a node split to ensure that neither node	*/
/* ends up with too many bytes. Such a result, if not detected,	*/
/* could cause a server crash. If detected, a BIDX_ERR is	*/
/* returned from the key addition operation and CTSTATUS.FCS	*/
/* receives an explanatory error message.			*/
/*								*/
/* Default: ctBEHAV_CHECK_SPLIT is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHECK_SPLIT
#define ctBEHAV_CHECK_SPLIT
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DLYLOGPRG changes the strategy for reducing the	*/
/* active number of transaction logs. Depending on various	*/
/* server configuration options, the number of active logs	*/
/* tends to stabilize after the server has been running	for	*/
/* a while. Sometimes the number of logs will grow, say	from	*/
/* an unusually long transaction. When this transaction	ends,	*/
/* the number of logs can be reduced. When this behavior is	*/
/* enabled, the reduction in the number of logs is delayed	*/
/* until the next checkpoint is completed. (Without this	*/
/* change, the reduction occurs at the time a new log is being	*/
/* created, but before the 1st checkpoint in the new log is	*/
/* performed.)							*/
/*								*/
/* Default: ctBEHAV_DLYLOGPRG is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_DLYLOGPRG
#ifdef TRANPROC
#define ctBEHAV_DLYLOGPRG
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_UNUSEDtran permits variable-length transaction	*/
/* controlled files to have the same space reclamation dynamics	*/
/* as non-transaction controlled files. When this ctBEHAV is	*/
/* enabled, it is possible, at server runtime, to revert to the	*/
/* old behavior (in which transaction controlled variable	*/
/* length files had much more restricted reclamation dynamics)	*/
/* by adding							*/
/* 		COMPATIBILITY	NO_VARLEN_TRAN_UNUSED		*/
/* to the server configuraion.					*/
/*								*/
/* TRANPROC is required.					*/
/*								*/
/* Default: ctBEHAV_UNUSEDtran is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_UNUSEDtran
#ifdef TRANPROC
#define ctBEHAV_UNUSEDtran
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CHKBUFUPD checks for unexpected buffer/cache page	*/
/* states during checkpoint processing to assemble the lists of	*/
/* vulnerable transactions due to unflushed buffer/cache pages.	*/
/* If a buffer/cache page is not on the BLM update list, it is	*/
/* added to the update list, and CTSTATUS.FCS receives a	*/
/* corresponding message. If the page's update flag is not set,	*/
/* then the vulnerable transaction list receives zero-trans-	*/
/* action-number entries, and CTSTATUS.FCS receives a corre-	*/
/* sponding message. NEITHER OF THESE CONDITIONS ARE CONSIDERED	*/
/* NORMAL. In the second situation, a subsequent automatic	*/
/* recovery would generate messages that zero-transaction-	*/
/* numbers were encountered.					*/
/*								*/
/* TRANPROC and ctBEHAV_BLM are required.			*/
/*								*/
/* Default: ctBEHAV_CHKBUFUPD is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHKBUFUPD
#ifdef TRANPROC
#ifdef ctBEHAV_BLM
#define ctBEHAV_CHKBUFUPD
#endif
#endif
#endif
#define CMTPAG_CHECK_LIMIT	6	/* # of checkpoints without	*/
					/* page appearing on update list*/
					/* before CTSTATUS error message*/

#if defined(ctBEHAV_CHKBUFUPD) || ( defined(CTBOUND) && defined(ctPortFAIRCOM_INTERNAL_GEN) )
/* check for unexpected buffer/cache page states during recovery */
#define ctBEHAV_CHKBUFUPDrcv
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_PUTHDRcommit changes how PUTHDR called for		*/
/* ctSERNUMhdr, ctLOGEOFhdr and ctPHYEOFhdr within a		*/
/* transaction behaves: when enabled, these updates are not	*/
/* (re)done at commit. COMPATIBILITY PUTHDR_COMMIT will restore	*/
/* the old behavior of re-doing the updates at commit. In	*/
/* either case, an abort causes the old value to be restored.	*/
/*								*/
/* TRANPROC is required.					*/
/*								*/
/* Default: ctBEHAV_PUTHDRcommit is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_PUTHDRcommit
#ifdef TRANPROC
#define ctBEHAV_PUTHDRcommit
#endif
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_SKPLOK_EXCL causes lock calls to be skipped for	*/
/* nonTRAN files opened exclusively. Note that this applies to	*/
/* newly created files which are always in exclusive mode	*/
/* (regardless of the file mode parameter). This ctBEHAV only	*/
/* applies to MULTITRD environments. At this time there is no	*/
/* way to specify individual files to be affected. When		*/
/* ctBEHAV_SKPLOK_EXCL is on, all nonTRAN files opened		*/
/* exclusively are affected.					*/
/*								*/
/* MULTITRD is required.					*/
/*								*/
/* Default: ctBEHAV_SKPLOK_EXCL is ON				*/
/*--------------------------------------------------------------*/
#define ctBEHAV_SKPLOK_EXCL



/*--------------------------------------------------------------*/
/* ctBEHAV_INVLDSPC causes a SUPERFILE member closed recursively*/
/* from a trancls() call to the host to have its (i.e., the	*/
/* member's) space mangement checked				*/
/*								*/
/* TRANPROC is required.					*/
/*								*/
/* Default: ctBEHAV_INVLDSPC is OFF				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_INVLDSPC
#ifdef TRANPROC
/* #define ctBEHAV_INVLDSPC */
#endif
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_SPCMGTRCV changes how a space management index is	*/
/* treated during automatic recovery. The space management	*/
/* index is not under transaction control. If the var length	*/
/* data file is corrupt, the space management index is		*/
/* discarded. But if the file is not corrupt, recovery code	*/
/* was invalidating the nument1/2 entries for the space		*/
/* management index while keeping the root1/2 entries. This	*/
/* caused an inconsistency. With the new behavior, we		*/
/* maintain the nument1/2 entries when the file is not		*/
/* corrupt (i.e., does not have its updflg set).		*/
/*								*/
/* TRANPROC is required.					*/
/*								*/
/* Default: ctBEHAV_SPCMGTRCV is ON				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SPCMGTRCV
#ifdef TRANPROC
#define ctBEHAV_SPCMGTRCV
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CHKRECSTATUS changes how ISAM level delete and	*/
/* rewrite operations behave when the current ISAM record is a	*/
/* deleted record. [When a DELREC/DELVREC succeeds, the record	*/
/* is removed, but the current ISAM position remains unchanged. */
/* This permits operations such as NXTREC or PRVREC to operate	*/
/* as expected after a delete.] Without ctBEHAV_CHKRECSTATUS,	*/
/* the operations typically show success and do not do		*/
/* anything. This change causes IRED_ERR(114) to occur except	*/
/* for memory files that typically get an ITIM_ERR(160) with	*/
/* this ctBEHAV turned on.					*/
/*								*/
/* Default: ctBEHAV_CHKRECSTATUS is ON				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHKRECSTATUS
#define ctBEHAV_CHKRECSTATUS
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_SCHSRL_ALIGN causes c-tree to consider the alignment	*/
/* of a SCHSRL field when calculating the offset at which the	*/
/* serial number is to be written.				*/
/*								*/
/* Default: ctBEHAV_SCHSRL_ALIGN is ON				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SCHSRL_ALIGN
#define ctBEHAV_SCHSRL_ALIGN
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_SPCLCLR causes SPCLSAV to perform some of the same	*/
/* logic used by SAVPCLR which most importantly permits the	*/
/* pre-image space hash bin entries to be updated as newer	*/
/* versions of a record image are added to pre-image space.	*/
/*								*/
/* Default: ctBEHAV_SPCLCLR is ON (for testing)			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SPCLCLR
#define ctBEHAV_SPCLCLR
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_UPDATEreshdr permits the dnum->thdrf mutex to be	*/
/* released during a wrthdr for updated resource anchor(s)	*/
/* dnum->reshdr1(2). thdrf is designed to be held for immediate	*/
/* updates, and holding it during wrthdr can lead to deadlocks.	*/
/* ct_tflstt(ctRESHDRflg) is used to control access to reshdr1/2*/
/* when the thdrf mutex is released prior to the wrthdr() call.	*/
/*								*/
/* Default: ctBEHAV_UPDATEreshdr is ON (for testing)		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_UPDATEreshdr
#ifdef MULTITRD
#define ctBEHAV_UPDATEreshdr
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_SKIPtmpidxerr permits a record read to skip over a	*/
/* record (returning the next available record and setting	*/
/* sysiocod to ITMP_COD) when an ITIM_ERR occurs on a temporary	*/
/* index, and permits a record delete to succeed that would	*/
/* have failed with a KDEL_ERR error because the key value does	*/
/* not exist in the temporary index.				*/
/*								*/
/* The previous behavior can be restored by specifying the	*/
/* option COMPATIBILITY TEMP_INDEX_ERROR in the	c-tree Server	*/
/* configuration file, or in standalone by compiling c-tree	*/
/* #define NO_ctBEHAV_SKIPtmpidxerr in ctoptn.h.		*/
/*								*/
/*								*/
/* Default: ctBEHAV_SKIPtmpidxerr is ON				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SKIPtmpidxerr
#define ctBEHAV_SKIPtmpidxerr
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_NODEQPEEK causes the delete node thread to peek at	*/
/* the next queue entry to deterine if it is for the same file	*/
/* as the current entry.					*/
/* If so, the delete node thread will attempt to keep the file	*/
/* open instead of closing the file after each queue entry is	*/
/* processed, and it will attempt to perform the update within	*/
/* the same transaction (if the file requires transaction	*/
/* processing) instead of committing the transaction after each	*/
/* queue entry is processed. There are compile time constants	*/
/* that limit the number of operations that can occur without	*/
/* a commit or a file close. This is to avoid conflicts with	*/
/* application threads that might arise from long transactions	*/
/* or keeping a file open in a mode that might conflict with	*/
/* an application. This new behavior will most directly benefit	*/
/* a case where an index (and its members) are purged causing a	*/
/* large number of nodes to be pruned from the same file.	*/
/*								*/
/* ctBEHAV_NODEQPEEK is ON					*/
/*--------------------------------------------------------------*/
#define NODEQ_TRNLEN		10
#define NODEQ_TRNLEN_SHTDWN	(10 * NODEQ_TRNLEN)
#define NODEQ_OPNLEN		20
#define NODEQ_OPNLEN_SHTDWN	(10 * NODEQ_OPNLEN)


/*--------------------------------------------------------------*/
/* ctBEHAV_CHKHSTLNK affects automatic recovery of SUPERFILEs.	*/
/* When ct_strip is used to rebuild an index within the		*/
/* SUPERFILE, it may cause the numrec1/2 header value to be	*/
/* advanced to the physical file size (to avoid clobbering	*/
/* nodes that may have been written, but the file header does	*/
/* not contain them). When this behavior is enabled, then, in	*/
/* addition to extending numrec1/2, a check is made to see if	*/
/* it is necessary to add record header links to ensure it is	*/
/* possible to traverse the SUPERFILE in physical order. These	*/
/* links will be added as necessary if the extended region	*/
/* from the old numrec1/2 position to the new numrec1/2		*/
/* position contains only FF fill or valid record headers.	*/
/*								*/
/* Default: ctBEHAV_CHKHSTLNK is ON				*/
/*	    requires TRANPROC and CTSUPER			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHKHSTLNK
#ifdef TRANPROC
#ifdef CTSUPER
#define ctBEHAV_CHKHSTLNK
#endif
#endif
#endif
#ifdef ctBEHAV_CHKHSTLNK
#ifndef TRANPROC
#undef ctBEHAV_CHKHSTLNK
#else
#ifndef CTSUPER
#undef ctBEHAV_CHKHSTLNK
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DATPOScntl modifies the release and acquisition of	*/
/* the data cache page semaphores (datsem). Without this turned	*/
/* on, the system behavior becomes erractic if the number of	*/
/* cache pages is very low. One sign of very low data cache is	*/
/* the "Performance WARNING: increase DAT_MEMORY" message sent	*/
/* to the server console. When ctBEHAV_DATPOScntl is turned on,	*/
/* even very low data cache levels should not affect the	*/
/* stability of the server although the same performance	*/
/* warnings will be generated.					*/
/*								*/
/* Default: ctBEHAV_DATPOScntl is ON				*/
/*	    requires MULITRD					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_DATPOScntl
#ifdef MULTITRD
#define ctBEHAV_DATPOScntl
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DATPPScntl causes the DPLIST mutex array to control	*/
/* the update of the pending data cache page ID (datpps).	*/
/* Without this turned on, the new approach of using an array	*/
/* of hash mutexes (instead of the global mutex ctpdbsema) did	*/
/* not properly control the datpps assignments, especially with	*/
/* very low data cache levels.					*/
/*								*/
/* Default: ctBEHAV_DATPPScntl is ON				*/
/*	    requires ctFeatDBSEMAhsh				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_DATPPScntl
#define ctBEHAV_DATPPScntl
/* check ctFeatDBSEMAhsh below */
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_SEP_CONC adds five additional mutexes, ctpc2ncsema	*/
/* through ctpc6ncsema; and moves a number of server state	*/
/* variables from the control of ctpconcsema to the new mutexes.*/
/*								*/
/* This serves two purposes: (1) to reduce mutex contention by	*/
/* eliminating unnecessary competition between ctpconcsema	*/
/* [used to control thread work flow issues] and unrelated	*/
/* state variables; and (2) to prepare the way for distributed	*/
/* mutex control [i.e., an array of mutex components] for some	*/
/* of the state variables.					*/
/*								*/
/* Default: ctBEHAV_SEP_CONC is ON				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SEP_CONC
#define ctBEHAV_SEP_CONC
#endif

#ifndef ctBEHAV_SEP_CONC
#define ctpc2ncsema	ctpconcsema
#define ctpc3ncsema	ctpconcsema
#define ctpc4ncsema	ctpconcsema
#define ctpc5ncsema	ctpconcsema
#define ctpc6ncsema	ctpconcsema
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_PKEYSIG changes the client-side interface for BATSET	*/
/* and BATSETX so that when a partial key is sent, the size of	*/
/* the buffer sent is just large enought to hold the PKETREQ	*/
/* structure state variables plus siglen bytes for the partial	*/
/* key. When this is not enabled, the entire PKEYREQ structure	*/
/* is sent which includes MAXLEN bytes for the partial key.	*/
/*								*/
/* This only affects client-side code. The server code works	*/
/* with either approach.					*/
/*								*/
/* Default: ctBEHAV_PKEYSIG is ON 				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_PKEYSIG
#define ctBEHAV_PKEYSIG
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_XTDHDR causes V6 file create calls (CREIFIL,		*/
/* CREIFILX, CREDAT, CREDATX, CREIDX and CREIDXX) to default	*/
/* to extended headers instead of V6 (128 byte) headers. When	*/
/* this define is enabled, system behavior will revert to V6	*/
/* headers if the server configuration file contains		*/
/* COMPATIBILITY REVERT_TO_V6HDR, or if a non-server		*/
/* application sets cth6flg to a non-zero value.		*/
/*								*/
/* For C/S systems we recognize 3 client types:			*/
/* 	1) old client: (ctclnver & ctclnMASK) < 9		*/
/*	2) new client with XTDHDR on: (ctclnver & ctclnXTDHDR)	*/
/*		is true						*/
/*	3) new client with XTDHDR off: (ctclnver & ctclnXTDHDR)	*/
/* 		is false && (ctclnver & ctclnMASK) > 8		*/
/*								*/
/* If the server has XTDHDR enabled, then clients (1) and (2)	*/
/* will get extended headers when the CRE...X() calls are made.	*/
/* If the server does not have XTDHDR enabled, then no clients	*/
/* will get extended headers on CRE...X() calls.		*/
/*								*/
/* NOTE: Unless the server configuration contains COMPATIBILITY	*/
/* 6BTRAN_NOT_DEFAULT, a transaction file with an extended	*/
/* header will use 6 byte transaction numbers.			*/
/*								*/
/* Default: ctBEHAV_XTDHDR is ON (requires ctHUGEFILE)		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_XTDHDR
#define ctBEHAV_XTDHDR
#endif
#ifndef ctHUGEFILE
#ifdef ctBEHAV_XTDHDR
#undef ctBEHAV_XTDHDR
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_ATODEP causes indices that are created by a rebuild	*/
/* or compact to have the same ctTRANDEP/ctRSTRDEL attributes	*/
/* turned as the data file has turned on. Without this behavior,*/
/* a call to RBLIFILX could cause the indices to be rebuilt	*/
/* without these TRANDEP attributes. A new client, even with	*/
/* the behavior turned on will not exhibit this new behavior	*/
/* if RBLIFIX8 is called since the XCREblk's passed to rebuild	*/
/* or compact will prevail.					*/
/*								*/
/* COMPATIBILITY NO_ATODEP will turn off this behavior even if	*/
/* the server is compiled with the behavior turned on.		*/
/*								*/
/* For C/S systems we recognize 3 client types:			*/
/* 	1) old client: (ctclnver & ctclnMASK) < 10		*/
/*	2) new client with ATODEP on: (ctclnver & ctclnATODEP)	*/
/*		is true						*/
/*	3) new client with ATODEP off: (ctclnver & ctclnATODEP)	*/
/* 		is false && (ctclnver & ctclnMASK) > 9		*/
/*								*/
/* If the server has ATODEP enabled, then clients (1) and (2)	*/
/* will get the consistent TRANDEP attributes (if the indices	*/
/* have to be recreated during rebuild or compact).		*/
/*								*/
/* Default: ctBEHAV_ATODEP is ON (requires ctHUGEFILE)		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_ATODEP
#define ctBEHAV_ATODEP
#endif
#if !defined(ctHUGEFILE)
#ifdef ctBEHAV_ATODEP
#undef ctBEHAV_ATODEP
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DELTRAN changes how nonTRANDEP file deletes are	*/
/* handled during automatic recovery. If this define is enabled,*/
/* then during transaction redo processing [tranred()] the file	*/
/* will be deleted. Ordinarily only TRANDEP files are deleted	*/
/* during tranred().						*/
/*								*/
/* At this time this option is for testing only			*/
/*								*/
/* Default: ctBEHAV_DELTRAN is OFF				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_DELTRAN
/* #define ctBEHAV_DELTRAN */
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_FCUSERconvert enables conversion of the user account	*/
/* records in FAIRCOM.FCS's USER.dat member data file from the	*/
/* original format to the new format.				*/
/*								*/
/* Default: ctBEHAV_FCUSERconvert is ON for c-tree Server.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_FCUSERconvert
#ifdef ctSRVR
#define ctBEHAV_FCUSERconvert
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_OPNLOG causes automatic recovery to track the	*/
/* location in the transaction log of the last clean open for	*/
/* an index file, and to use this position to determine whether	*/
/* or not to adjust the nument1/2 values at the end of a	*/
/* recovered transaction. If the transaction occurs after the	*/
/* open, then include the adjnent() adjustment. If, during	*/
/* recovery, the nument1/2 values are reset to zero at file	*/
/* open or to any value as part of a checkpoint, the last open	*/
/* log position is ignored.					*/
/*								*/
/* Default: ctBEHAV_OPNLOG is on by default.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_OPNLOG
#define ctBEHAV_OPNLOG
#endif


/*--------------------------------------------------------------*/
/* The following debugging logic was added to track down a 160  */
/* error involving PREIMAGE shared memory files. See SVN 14370. */
/* since issue is resolved, this logic was disabled 090127.     */
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CLN_DBG_LOOP
/* #define ctBEHAV_CLN_DBG_LOOP */
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CTUSERX changes how a call to CTUSERX sends data	*/
/* from the client to the server. The original version of the	*/
/* CTUSERX client-side code did not send the first two function	*/
/* parameters (ctlbufptr and ctlbufsiz) to the server, and it	*/
/* considered the input buffer (inbufptr) to be string data.	*/
/* The new version of CTUSERX sends all the parameters to the	*/
/* server and allows sending binary data in the input buffer.	*/
/*								*/
/* ctBEHAV_CTUSERX also redefines the sixth parameter of the	*/
/* CTUSERX function to pVRLEN instead of VRLEN. This change	*/
/* allows CTUSERX to return the length of the output data.	*/
/*								*/
/* Default: ctBEHAV_CTUSERX is on by default.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CTUSERX
#define ctBEHAV_CTUSERX
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_SAVPNT_NEWIMAGE changes the processing of new record	*/
/* images during a transaction commit when more than one image	*/
/* for a record exists due to the use of savepoints. When	*/
/* ctBEHAV_SAVPNT_NEWIMAGE is on, the code moves the most	*/
/* up-to-date record image to the end of the list of record	*/
/* images so that it appears in the transaction log with the	*/
/* log entries for the last update that was made to that record	*/
/* in that transaction.	When ctBEHAV_SAVPNT_NEWIMAGE is off,	*/
/* the record image appears in the location of the update that	*/
/* modified the largest portion of the record image.		*/
/*								*/
/* Default: ctBEHAV_SAVPNT_NEWIMAGE is on by default. Requires	*/
/* ctXTDLOG support.						*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SAVPNT_NEWIMAGE
#define ctBEHAV_SAVPNT_NEWIMAGE
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_KLLX enables a check for key level locks (martks) in	*/
/* index nodes for transactions undone by recovery. Servers	*/
/* will only perform this check if DIAGNOSTICS KLLX is included	*/
/* in the configuration information. Single user compiles must	*/
/* turn ctBEHAV_KLLX on explicitly at compile time.		*/
/*								*/
/* Default: ctBEHAV_KLLX is on by default for servers		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_KLLX
#ifdef ctSRVR
#define ctBEHAV_KLLX
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DYNHASH enables support for dynamic hash tables for: */
/* (a) each file's system lock table; (b) each user's transaction*/
/* pre-image space; and (c) each user's lock table. Whether or 	*/
/* not dynamic hashing is activated, these hash tables exist:  	*/
/* two is each user, and one for each file. By default dynamic  */
/* hashing is on at compile-time. 				*/
/*								*/
/* This was first activated by default in v9.2.0. At this stage	*/
/* of development, ctBEHAV_DYNHASH requires ctBEHAV_MEMSUB.	*/
/*								*/
/* Default: ctBEHAV_DYNHASH is on by default for servers	*/
/*--------------------------------------------------------------*/
#ifdef NO_ctBEHAV_DYNHASH
#ifdef ctDYNHASH
#undef ctDYNHASH
#endif
#else  /* ~NO_ctBEHAV_DYNHASH */
#ifdef  ctSRVR
#ifdef  ctBEHAV_MEMSUB
#define ctBEHAV_DYNHASH
#ifndef ctDYNHASH
#define ctDYNHASH
#endif
#endif
#endif /* ctSRVR */
#endif /* ~NO_ctBEHAV_DYNHASH */


/*--------------------------------------------------------------*/
/* ctBEHAV_VFORK changes ctlauch to use vfork() on unix systems.*/
/* Previous behavior was to use fork(), which duplicates the    */
/* entire processes address space.  This will cause the fork()  */
/* to fail for processes with a large memory footprint. 	*/
/* ctBEHAV_VFORK is OFF by default for Unix servers		*/
/* ctBEHAV_VFORK is ON  by default for Linux servers		*/
/*--------------------------------------------------------------*/
#if (!defined(ctPortPIM) && !defined(ctPortLINUX)) 	/* Prairie Interactive Messaging */
#define NO_ctBEHAV_VFORK 				/* activate for this customer and Linux */
#endif

#ifndef NO_ctBEHAV_VFORK
#ifdef  ctSRVR
#ifdef  ctPortUNIX
#define ctBEHAV_VFORK
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DETECT_DYNDMP_READ enables the detection of a	*/
/* possible livelock between a dynamic dump read operation on	*/
/* a segmented file, and an attempt to add a new segment to	*/
/* the same segmented file. The dump thread waits for the	*/
/* segmented to be added, and the segment-adding thread waits	*/
/* for the dump to complete. The new behavior allows the dump	*/
/* thread read operation to complete while the segment update	*/
/* remains waiting for the dynamic dump to complete.		*/
/*								*/
/* ctBEHAV_DETECT_DYNDMP_READ is on by default. It only		*/
/* affects MULTITRD code.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_DETECT_DYNDMP_READ
#define ctBEHAV_DETECT_DYNDMP_READ
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_SKIPAUTO permits automatic recovery, forward roll,	*/
/* and rollbacks to avoid errors due to TRANDEP files that have	*/
/* been created, deleted and/or renamed, causing the files to	*/
/* appear to be missing during the initial transaction log	*/
/* scan. Without this new behavior, SKIP_MISSING_FILES YES	*/
/* must be part of the configuration information to avoid	*/
/* missing file errors in these circumstances.			*/
/*								*/
/* In a server, this define invokes this new behavior unless	*/
/* COMPATIBILITY NO_AUTO_SKIP is included in the configuration	*/
/* info. Including NO_ctBEHAV_SKIPAUTO will disable this new	*/
/* behavior.							*/
/*								*/
/* ctBEHAV_SKIPAUTO is on by default. It requires ctHUGEFILE	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SKIPAUTO
#define ctBEHAV_SKIPAUTO
#endif
#ifndef ctHUGEFILE
#ifdef  ctBEHAV_SKIPAUTO
#undef  ctBEHAV_SKIPAUTO
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_SKIPAUTO_CLSTRAN modifies the initial transaction	*/
/* log scan routine so that CLSTRAN log entries may initiate a	*/
/* file open to determine if the file exists or should be	*/
/* placed on the auto missing files skip list. Without this new	*/
/* behavior, CLSTRAN log entries are ignored during the initial	*/
/* log scan. This change is made to addess the problem of	*/
/* correctly identifying that a file is actually missing when	*/
/* ctBEHAV_SKIPAUTO is on and the file is deleted or renamed	*/
/* by a process external to c-tree.				*/
/*								*/
/* COMPATIBILTY NO_CLSTRAN_OPEN will disable this new behavior	*/
/* at run-time.							*/
/*								*/
/* ctBEHAV_SKIPAUTO_CLSTRAN requires ctBEHAV_SKIPAUTO		*/
/*								*/
/* ctBEHAV_SKIPAUTO_CLSTRAN is on by default when		*/
/* ctBEHAV_SKIPAUTO is defined. NO_ctBEHAV_SKIPAUTO_CLSTRAN	*/
/* turns off this new behavior at compile-time.			*/
/*--------------------------------------------------------------*/
#ifdef ctBEHAV_SKIPAUTO_CLSTRAN
#undef ctBEHAV_SKIPAUTO_CLSTRAN
#endif
#ifndef NO_ctBEHAV_SKIPAUTO_CLSTRAN
#ifdef  ctBEHAV_SKIPAUTO
#define ctBEHAV_SKIPAUTO_CLSTRAN
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_PUTHDRreopen permits a file that has been (1) opened	*/
/* exclusively; (2) then updated by PUTHDR under transaction	*/
/* control; and (3) then closed (which is deferred because of	*/
/* the active transaction): to be reopened in SHARED mode.	*/
/* Without this new behavior, the reopen would have failed with	*/
/* a FNOP_ERR/FCNF_COD because of a special check particularly	*/
/* for such PUTHDR activity.					*/
/*								*/
/* However, the shared open does not permit other shared opens	*/
/* to occur until the transaction commits or aborts. It behaves	*/
/* as if the file is opened exclusively until the commit/abort	*/
/* occur, and the other shared opens fail with FNOP_ERR /	*/
/* FCNF_COD until the abort or commit.				*/
/*								*/
/* ctBEHAV_PUTHDRreopen is on by default.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_PUTHDRreopen
#define ctBEHAV_PUTHDRreopen
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_UNLOCKtorg causes the code that releases locks when	*/
/* committing a transaction to subtract the 'offset to origin'	*/
/* value from the record offset before calling iunlock81().	*/
/*								*/
/* ctBEHAV_UNLOCKtorg is on by default.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_UNLOCKtorg
#define ctBEHAV_UNLOCKtorg
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_MISSING_KEY causes sequential ISAM index-based	*/
/* retrieval routines to explicitly check if the current ISAM	*/
/* key buffer (see ctgetkbf() and the FCB member plen) contains	*/
/* an entry, or has not been updated to the current ISAM	*/
/* position. Without this modification, the operation uses	*/
/* what ever it finds in the current ISAM key buffer which	*/
/* could lead to unexpected results. In the vast majority of	*/
/* situations everything works as expected without this change.	*/
/* But a partial data record read or a conditional index	*/
/* constraint could leave one or more current ISAM key buffers	*/
/* out of date. With this modification, a retrieval returns an	*/
/* an error code if the current ISAM key buffer does not have	*/
/* a current entry: (1) not enough of the data record was read	*/
/* to form the key [DBUF_ERR(893)]; (2) a conditional index	*/
/* constraint caused the key value to "not exist" [NKEY_ERR	*/
/* (894)]; or (3) ctISAMKBUFhdr has been used to turn off key	*/
/* buffer updates to enhance performance [MBUF_ERR(892)].	*/
/*								*/
/* ctBEHAV_MISSING_KEY is on by default.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_MISSING_KEY
#define ctBEHAV_MISSING_KEY
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DELNOD_RCV causes the MULTITRD delete node logic	*/
/* that reorganizes upper levels of the index tree structure to	*/
/* immediately update the upper levels (instead of delaying the	*/
/* upper level reoprganization) during the index repair step of	*/
/* automatic recovery. The delayed update is designed to change	*/
/* the locking order to avoid deadlocks. But during recovery,	*/
/* there are no other threads updating the index tree structure.*/
/*								*/
/* ctBEHAV_DELNOD_RCV is on by default.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_DELNOD_RCV
#define ctBEHAV_DELNOD_RCV
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CMTLOK_optimize enables code that optimizes the	*/
/* use of commit read locks.					*/
/*								*/
/* Requires ctBEHAV_CMTLOK					*/
/*								*/
/* ctBEHAV_CMTLOK_optimize is on by default.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CMTLOK_optimize
#define ctBEHAV_CMTLOK_optimize
#endif

/* Optimized commit read lock support requires commit read lock support. */
#ifndef ctBEHAV_CMTLOK
#undef ctBEHAV_CMTLOK_optimize
#endif

/*
** ctBEHAV_CMTLOK_optimizeNLINK
**
** Use SH_IMAGE instead of SH_NLINK: SH_NLINK entry replaced with
** SH_IMAGE and attribute bit ctIO_NLINK turned on.
*/
#ifdef ctBEHAV_CMTLOK_optimize
#ifndef NO_ctBEHAV_CMTLOK_optimizeNLINK
#define ctBEHAV_CMTLOK_optimizeNLINK
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_REPIMGRWT saves a record image in preimage space for	*/
/* every update that is made to a particular record. Requires	*/
/* ctXTDLOG.							*/
/*								*/
/* ctBEHAV_REPIMGRWT is ON by default for c-tree Server.	*/
/*--------------------------------------------------------------*/
#ifdef  TRANPROC
#ifdef MULTITRD
#ifndef NO_ctBEHAV_REPIMGRWT
#define ctBEHAV_REPIMGRWT
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_THREADSAFE replaces non-threadsafe system calls with */
/* thread safe versions						*/
/*								*/
/* ctBEHAV_THREADSAFE is ON by default for c-tree Server in	*/
/* v10.1.3 and later.						*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_THREADSAFE
#ifdef MULTITRD
#if ctVER3_GE(10,2,0)
#define ctBEHAV_THREADSAFE
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_SERVER_DIRECTORY disables support for the c-tree	*/
/* Server's SERVER_DIRECTORY configuration option.		*/
/*								*/
/* ctBEHAV_SERVER_DIRECTORY is ON by default for c-tree Server.	*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctBEHAV_SERVER_DIRECTORY
#define ctBEHAV_SERVER_DIRECTORY
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_NoHdrLok causes lock table entries to be skipped,	*/
/* regardless of transaction state, for DLOCK81 calls to	*/
/* hdrpos1/2 and for LOCK81 calls to hdroff1/2. The locks are	*/
/* skipped because these lock calls always acquire the header	*/
/* semaphore ctnum->semaf.					*/
/*								*/
/* COMPATIBILITY LOCK_HEADER restores the lock table entries.	*/
/*								*/
/* ctBEHAV_NoHdrLok is ON by default for MULTITRD code.		*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctBEHAV_NoHdrLok
#define ctBEHAV_NoHdrLok
#endif
#else
#ifdef ctBEHAV_NoHdrLok
#undef ctBEHAV_NoHdrLok		/* requires MULTITRD support	*/
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_SKPLOK_EXCLtran causes locks on exclusively open	*/
/* TRNLOG files to be skipped. ctBEHAV_SKPLOK_EXCLtran requires	*/
/* ctBEHAV_SKPLOK_EXCL which skips locks on exclusively opened	*/
/* nonTRAN files.  						*/
/*								*/
/* COMPATIBILITY LOCK_EXCL_TRAN restores the locks on		*/
/* exclusively opened TRNLOG files				*/
/*								*/
/* ctBEHAV_SKPLOK_EXCLtran is ON by default for MULTITRD code.	*/
/*--------------------------------------------------------------*/
#if defined(MULTITRD) && defined(ctBEHAV_SKPLOK_EXCL)
#ifndef NO_ctBEHAV_SKPLOK_EXCLtran
#define ctBEHAV_SKPLOK_EXCLtran
#endif
#else
#ifdef ctBEHAV_SKPLOK_EXCLtran
#undef ctBEHAV_SKPLOK_EXCLtran	/* requires MULTITRD and SKPLOK_EXCL support */
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_GETNODLOOP changes the ctgetnod81() retry loop to	*/
/* gradually increase the defer time from zero to 10 milli-	*/
/* seconds instead of immediately using a 10 millisecond defer.	*/
/*								*/
/* DEFAULT:  ctBEHAV_GETNODLOOP is on by default for MULTITRD	*/
/* on Windows.							*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctBEHAV_GETNODLOOP
#ifdef ctPortWIN32
#define ctBEHAV_GETNODLOOP
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_FUSRCLR changes the mutex control on calls to	*/
/* ctfusrclr() made from clrshdlst() and reduces unnecessary	*/
/* initializations. ctputrsema was being held on calls to	*/
/* ctfusrclr() from clrshdlst(). With this ctBEHAV turned on,	*/
/* the mutex is not held when ctfusrclr() is called.		*/
/*								*/
/* DEFAULT:  ctBEHAV_FUSRCLR is on by default for MULTITRD	*/
/*--------------------------------------------------------------*/
#define ctBEHAV_FUSRCLR
#ifndef MULTITRD
#ifdef ctBEHAV_FUSRCLR
#undef ctBEHAV_FUSRCLR
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_FWDSAVP changes the search strategy through preimage	*/
/* space when multiple versions of a record image exist across	*/
/* savepoints by taking advantage of the links between the	*/
/* record versions. When enabled, the walk over preimage space	*/
/* looking for the latest version of the record follows the	*/
/* forward savepoint links instead of the forward chronological	*/
/* links. This is advantageous because the chronological links	*/
/* likely include a large number of entries of no consequence	*/
/* to finding the record image.					*/
/*								*/
/* DEFAULT:  ctBEHAV_FWDSAVP is on by default			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_FWDSAVP
#define ctBEHAV_FWDSAVP
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_CHKFUPD changes the behavior of srchshd81() by	*/
/* skipping the serach of pre-image space when the user has	*/
/* not updated the target file within the current transaction.	*/
/*								*/
/* DEFAULT:  ctBEHAV_CHKFUPD is on by default for TRANPROC.	*/
/* For MULTITRD either ctMULTIOPN or ctMULTIOPNerror must be	*/
/* defined.							*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHKFUPD
#ifdef TRANPROC
#define ctBEHAV_CHKFUPD
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_UPDPARTATTR applies PUTFIL() and PUTHDR() calls for 	*/
/* a partition host to all of that host's active partitions.	*/
/*								*/
/* DEFAULT:  ctBEHAV_UPDPARTATTR is on by default.		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_UPDPARTATTR
#define ctBEHAV_UPDPARTATTR
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DODA_PPND permits server-side and stand-alone calls	*/
/* to GETDODA to pass in a string to be prepended to each field	*/
/* name in the DODA. The mode parameter must have RES_PPND	*/
/* or'ed in, and the bufptr parametr holds the nul terminated	*/
/* prepend string.						*/
/*								*/
/* ctBEHAV_DODA_PPND also activates r-tree server code that	*/
/* causes field names in the files used by a script in a call	*/
/* to RTSCRIPT to be prepended with their respective file	*/
/* names. The file names have special characeters (such as ':'	*/
/* or '\' or '/' or ' ' or '.') replaced with underscores	*/
/* ('_'), and an underscore is placed between the file name	*/
/* and field name.						*/
/*								*/
/* DEFAULT:  ctBEHAV_DODA_PPND is off by default.		*/
/*--------------------------------------------------------------*/
#ifdef rtSRVR
#ifndef ctBEHAV_DODA_PPND
#define ctBEHAV_DODA_PPND
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_TIMESTAMP_SEG enforces an eight byte limit to the	*/
/* portion of the partition key value (see			*/
/* ctFeatPARTITION_BY_TIMESTAMP_DAY) used to map data records	*/
/* into partition members for the purpose of ensuring proper	*/
/* assignment of KINCprt and KORDprt attributes to		*/
/* non-partition indices. These attributes signify the type	*/
/* of optimizations available during index operations on	*/
/* non-partition indices.					*/
/*								*/
/* ctBEHAV_TIMESTAMP_SEG overrides/substitutes for using the	*/
/* NOTPRT modifier to indicate the first segmeng of a partition	*/
/* key value that is NOT used as part of the mapping. Also,	*/
/* ctBEHAV_TIMESTAMP_SEG causes the assignment of KINCprt and	*/
/* KORDprt attributes to be reset during an ISAM open.		*/
/*								*/
/* NOTE: IF THIS DEFINE IS ENABLED, WE ARE ASSUMING THERE	*/
/* ARE NO OTHER PARTITION INDICES IN USE SINCE WE DO NOT HAVE	*/
/* A METHOD TO IDENTIFY WHETHER OR NOT THE INDEX IS ACTUALLY	*/
/* BASED ON A TIMESTAMP.					*/
/*								*/
/* DEFAULT:  ctBEHAV_TIMESTAMP_SEG is off by default and	*/
/* requires ctFeatPARTITION_BY_TIMESTAMP_DAY			*/
/*--------------------------------------------------------------*/
/*
** #define ctBEHAV_TIMESTAMP_SEG
*/


/*--------------------------------------------------------------*/
/* ctBEHAV_setexcabt changes ctsetexc() so that only one call	*/
/* to ctabtexc81() is required to remove a node-tran pairing	*/
/* from the abort node list during a node split.		*/
/*								*/
/* Also we hold ctpabtsema for the entire removal and addition	*/
/* of the new abort node list entries to avoid a checkpoint	*/
/* that finds an inconsistent abort node list state. To reduce	*/
/* ctpabtsema contention, we build the new abort node list	*/
/* entries locally (without ctpabtsema control), and then add	*/
/* the new entries in one operation (instead of looping over	*/
/* each key value).						*/
/*								*/
/* DEFAULT:  ctBEHAV_setexcabt is ON by default in c-tree v9.6	*/
/* and later.							*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_setexcabt
#if ctVER_GE(9,6)
#define ctBEHAV_setexcabt
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_FSsyscopy changes ctFSunxcopy to use read()/write()  */
/* system calls rather than using the system() function to copy */
/* files.							*/
/*								*/
/* DEFAULT: ctBEHAV_FSsyscopy is on by default for unix	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_FSsyscopy
#ifdef ctPortUNIX
#define ctBEHAV_FSsyscopy
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_MYMARKS changes the behavior of ctclup() so that	*/
/* when it recognizes that all the key level locks (special	*/
/* marks) in the node belong to the calling thread for the	*/
/* current transaction, it is not necessary to cleanup any of	*/
/* the key level locks.						*/
/*								*/
/* This will help the performance of large transactions that	*/
/* repeatedly add/visit key values during the transaction	*/
/* because unnecessary attempts to cleanup pending key level	*/
/* locks for the same transaction will not be attempted.	*/
/* However, this new behavior only applies to nodes whose key	*/
/* level locks all belong to the calling user's current		*/
/* transaction.							*/
/*								*/
/* The new behavior will be skipped if COMPATIBILITY NO_MYMARKS	*/
/* is included in the configuration information.		*/
/*								*/
/* DEFAULT:  ctBEHAV_MYMARKS is on for v10.0.0 and later.	*/
/*--------------------------------------------------------------*/

#ifndef NO_ctBEHAV_MYMARKS
#ifdef TRANPROC
#if ctVER3_GE(10,0,0)
#define ctBEHAV_MYMARKS
#endif
#endif
#endif

#ifdef ctBEHAV_MYMARKS
#ifndef TRANPROC
#error ctBEHAV_MYMARKS requires TRANPROC
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_NXTMARKS changes the behavior of ctclup() when	*/
/* called for NXTKEY operations so that it only checks key	*/
/* level locks sufficient to satify the NXTKEY operation. In	*/
/* practice this means that if NXTKEY finds that the current	*/
/* position within the node (specified by rnode1/rnode2/relm)	*/
/* is valid, then ctclup is called with a special flag. Then	*/
/* cleanup starts at relm + 1 and only go as far as necessary	*/
/* to find one valid value.					*/
/*								*/
/* The new behavior will be skipped if COMPATIBILITY NO_NXTMARKS*/
/* is included in the configuration information.		*/
/*								*/
/* DEFAULT:  ctBEHAV_NXTMARKS is on for v10.0.0 and later. It	*/
/* requires TRANPROC, MULTITRD and ctHUGEFILE.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_NXTMARKS
#if defined(MULTITRD) && defined(ctHUGEFILE) && defined(TRANPROC)
#if ctVER3_GE(10,0,0)
#define ctBEHAV_NXTMARKS
#endif
#endif
#endif

#if defined(ctBEHAV_NXTMARKS) && !(defined(MULTITRD) && defined(ctHUGEFILE) && defined(TRANPROC))
#error ctBEHAV_NXTMARKS requires TRANPROC, MULTITRD and ctHUGEFILE
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DIR_BUF_RQS changes the behavior of ctgetnod81() so	*/
/* that in situations where (1) there is a good chance that the	*/
/* buffer holds the desired node, and (2) we would have have	*/
/* put the thread into our blocking "queue" using ctaddblk();	*/
/* we now directly call ctsemrqs(fndbuf->semaf), and then	*/
/* check for proper contents. If the buffer does not hold the	*/
/* desired node, or the buffer has been "promised" to another	*/
/* node (pnodeid1/2), we must retry. Otherwise we skip the	*/
/* overhead of our blocking list. Further, we have refined our	*/
/* analysis of the buffer state so we can attempt the direct	*/
/* acquisition of fndbuf->semaf in additional situations where	*/
/* we would have issued a retry (goto restart).			*/
/*								*/
/* COMPATIBILITY DIR_BUF_RQS is required to use the new		*/
/* approach. If the approach becomed the default, a		*/
/* COMPATIBILITY entry can be used to revert to the old		*/
/* approach.							*/
/*								*/
/* DEFAULT:  ctBEHAV_DIR_BUF_RQS is off by default (for now).	*/
/* It requires MULTITRD and ctHUGEFILE.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_DIR_BUF_RQS
#if defined(MULTITRD) && defined(ctHUGEFILE)
/* #define ctBEHAV_DIR_BUF_RQS */
#endif
#endif

#if defined(ctBEHAV_DIR_BUF_RQS) && !(defined(MULTITRD) && defined(ctHUGEFILE))
#undef ctBEHAV_DIR_BUF_RQS
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_FIDD_ERR changes the way tfil values are mapped to	*/
/* c-tree system file numbers during automatic recovery.	*/
/*								*/
/* Transaction log entries use a 4-byte temporary file number,	*/
/* or tfil, to identify the file. Every time a file is opened	*/
/* it is assigned a unique tfil. During automatic recovery, the	*/
/* routine put_lgtorc() is called to map each tfil to a c-tree	*/
/* system file number. Multiple opens of the same file		*/
/* encountered in the transaction logs result in each of the	*/
/* tfil values for the same file being mapped into the same	*/
/* c-tree system file number.					*/
/*								*/
/* In addition to the tfil used in each log entry, each file	*/
/* is assigned a unique 12-byte file ID at file creation. And	*/
/* file create and file open log entries contain this 12-byte	*/
/* ID as well as the tfil.					*/
/*								*/
/* When recovery opens a file and finds that the 12-byte file	*/
/* ID in the header does not match the 12-byte file ID in the	*/
/* create/open transaction log entry, recovery knows that this	*/
/* is the wrong instance of the file, and it maps the tfil	*/
/* number into a special code, NOT_OP_FID, instead of a valid	*/
/* c-tree system file number. When this happens to an index	*/
/* file, the tfil mapping to NOT_OP_FID occurs for each index	*/
/* member as well as the host index.				*/
/*								*/
/* When ctBEHAV_FIDD_ERR is enabled, index member tfil values	*/
/* are remapped to NOT_OP_FID_MBR so that recovery can		*/
/* distinguish between the remapped host index and remapped	*/
/* index members. This permits recovery to avoid unexpected	*/
/* problems when different versions of an index (i.e., indices	*/
/* with the same name but different 12-byte file ID's) have	*/
/* a diferent number of index members.				*/
/*								*/
/* DEFAULT:  ctBEHAV_FIDD_ERR is on				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_FIDD_ERR
#define ctBEHAV_FIDD_ERR
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_THDRF_RELDAT moves the acquisition of a file's thdrf	*/
/* mutex after the removal of a data cache page or index buffer	*/
/* from the global buffer update list. The cache page/buffer	*/
/* remains locked until thdrf is acquired. Previously thdrf was	*/
/* held during the call to remove the entry from the list, which*/
/* caused a deadlock between a checkpoint and file flush.	*/
/*								*/
/* DEFAULT:  ctBEHAV_THDRF_RELDAT is on by default		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_THDRF_RELDAT
#define ctBEHAV_THDRF_RELDAT
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_RESOURCE_RBLD changes the handling of the resource	*/
/* chain by RBLDATX. When it is defined, the header link	*/
/* (reshdr1/2) is NOT set to zero at the beginning of the	*/
/* rebuild (as it is without ctBEHAV_RESOURCE_RBLD). Problems	*/
/* arose when a rebuild was prematurely terminated and the	*/
/* header had lost its link to the resource chain, resulting	*/
/* in a RNON_ERR(401).						*/
/*								*/
/* With this enabled, the link to the resource chain is		*/
/* validated at the beginning of the rebuild (by seeing if it	*/
/* points to a valid resource). If it is validated, no change	*/
/* is made to reshdr1/2 unless scnres() finds it necessary. If	*/
/* it is not validated, then logres81() sets reshdr1/2 to the	*/
/* lowest restyp/resnum it finds during rebuild, and scnres()	*/
/* will	update it as necessary.					*/
/*								*/
/* The objective is to leave reshdr1/2 no worse off, possibly	*/
/* better, if a rebuild is prematurely terminated.		*/
/*								*/
/* DEFAULT:  ctBEHAV_RESOURCE_RBLD is on by default if		*/
/* RESOURCE is defined						*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_RESOURCE_RBLD
#ifdef RESOURCE
#define ctBEHAV_RESOURCE_RBLD
#endif
#endif
#if defined(ctBEHAV_RESOURCE_RBLD) && !defined(RESOURCE)
#undef ctBEHAV_RESOURCE_RBLD
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_TRANDEP_SCAN changes the automatic recovery log	*/
/* scan.							*/
/*								*/
/* If a server terminates abnormally it is likely that pending	*/
/* TRANDEP file deletes and renames, if any, will cause the	*/
/* target files to be on disk with temporary names and/or the	*/
/* new names. In some circumstances, log entries processed	*/
/* during the recovery log scan are skipped because log scan	*/
/* tried to access the file(s) using the original name(s).	*/
/*								*/
/* With this new behavior enabled, a "short" pre-scan of the	*/
/* log looks for such pending deletes and renames, and then	*/
/* the regular log scan can identify the files using the	*/
/* alternative names.						*/
/*								*/
/* COMPATIBILITY NO_TRANDEP_SCAN disables the new behavior.	*/
/*								*/
/* DEFAULT:  ctBEHAV_TRANDEP_SCAN is on by default		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_TRANDEP_SCAN
#ifdef ctHUGEFILE
#define ctBEHAV_TRANDEP_SCAN
#endif
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_WORKsync enables a new approach to the monitoring	*/
/* and updating of server state variables and user state	*/
/* variables related to tracking threads as they enter and	*/
/* leave the core code. This monitoring is most important for	*/
/* the ctFILBLK and ctQUIET routines.				*/
/*								*/
/* The new approach replaces a single, global mutex ctpconcsema	*/
/* with a new global mutex used more sparingly for some system	*/
/* state variables (such as cttflg and ctQTthrd), and with an	*/
/* array of user specific instances of the mutex to control the	*/
/* user-specific state variables (such as ctwa(thdid)). The	*/
/* purpose is to substantially reduce the contention for the	*/
/* global mutex.						*/
/*								*/
/* Further the global instance can also be enhanced by using	*/
/* reader/writer locks when available so that threads only	*/
/* checking a global state variable need only acquire a reader	*/
/* lock, and those updating the system state variable will	*/
/* acquire a write lock. ctBEHAV_WORKsyncRWL controls this	*/
/* subsidiary behavior change.					*/
/*								*/
/* Lastly, if atomic operations are available and		*/
/* ctBEHAV_WORKsyncRWL is enabled, then				*/
/* ctBEHAV_WORKsyncInterlocked will be enabled, and updates	*/
/* to ctcurusr and ctmaxusr will be through ctInterlockedXYZ	*/
/* routines further reducing the cost of synchronizing updates.	*/
/*								*/
/* NO_ctBEHAV_WORKsync disables the new behavior. If it is	*/
/* enabled and reader/writer locks are available, the use of	*/
/* the reader/writer locks will be disabled by defining		*/
/* NO_ctBEHAV_WORKsyncRWL. And if both ctBEHAV_WORKsync and	*/
/* ctBEHAV_WORKsyncRWL	are enabled, the use of the interlocked	*/
/* updates will be disabled if NO_ctBEHAV_WORKsyncInterlocked	*/
/* is defined.							*/
/*								*/
/* DEFAULT:  New behavior on by default for versions 9.6 or	*/
/* greater							*/
/*--------------------------------------------------------------*/
#if ctVER_GE(9,6)

#ifndef NO_ctBEHAV_WORKsync
#ifndef ctBEHAV_WORKsync
#if defined(MULTITRD) && defined(ctCACHE_MEMORY) && defined(ctBEHAV_SEP_CONC)
#define ctBEHAV_WORKsync
#endif
#endif
#endif

#endif

/*
** check for required support for ctBEHAV_WORKsync if it is
** defined externally. w/o support, turn off ctBEHAV_WORKsync
*/
#ifdef ctBEHAV_WORKsync
#if !defined(MULTITRD) || !defined(ctCACHE_MEMORY) || !defined(ctBEHAV_SEP_CONC)
#undef ctBEHAV_WORKsync
#endif
#endif


/*
** The defines for ctBEHAV_WORKsyncRWL and
** ctBEHAV_WORKsyncInterlocked are handled later in this
** header, after other dependencies have been established.
*/



/*--------------------------------------------------------------*/
/* ctBEHAV_FCBSTK replaces "for loops" to search for available	*/
/* FCB's with a simple push down stack of available FCB's. The	*/
/* control of the stack is under existing calls to ctpocsema.	*/
/* The motivation is to improve performance when the maximum	*/
/* number of files is large.					*/
/*								*/
/* When ctFeatKEEPOPENclose is also defined, we replace the	*/
/* "for loops" that look for the best available KEEPEOPN file	*/
/* (with usrcnt==1) with linked lists of available KEEPOPEN	*/
/* files, again under existing ctpocsema control.		*/
/*								*/
/*								*/
/* DEFAULT:  New behavior on by default for versions 9.6 or	*/
/* greater							*/
/*--------------------------------------------------------------*/
#if ctVER_GE(9,6)

#ifndef NO_ctBEHAV_FCBSTK
#ifndef ctBEHAV_FCBSTK
#if defined(MULTITRD) && defined(ctFLEXFILE)
#define ctBEHAV_FCBSTK
#endif
#endif
#endif

#endif

/*
** check for required support for ctBEHAV_FCBSTK if it is
** defined externally. w/o support, turn off ctBEHAV_FCBSTK
*/
#ifdef ctBEHAV_FCBSTK
#if !defined(MULTITRD) || !defined(ctFLEXFILE)
#undef ctBEHAV_FCBSTK
#else
#define EMPTY_KEEPOPEN	(pCTFILE) 0
#endif
#endif

/*
** check for debug monitoring (ctDBGfcbstk) of ctBEHAV_FCBSTK
**
** when ctDBGfcbstk is defined, the FCB availability counters
** are checked for consistency. in particular, the following
** should be true
** 		  ct_avlfil + cthghflx - ct_avlstk == ct_mxfil
** where
**		ct_avlfil	# of available FCBs
**		cthghflx	# of FCBs used at least once
**		ct_avlstk	# of FCBs on available stack
**		ct_mxfil	total # of FCBs
**
** at server start up, the stack is empty; ct_avlfil equals
** ct_mxfil; and cthghflx is zero. when a FCB is requested, it
** is popped off the stack if the stack is not empty; if it is
** empty, then we use the next unused FCB (where cthghflx tracks
** the number of FCBs that have been used).
**
** during automatic recovery, the stack is not used since recovery
** assumes FCBs are assigned in increasing order.
*/
#ifdef ctDBGfcbstk
#ifndef ctBEHAV_FCBSTK
#undef ctDBGfcbstk
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CLSFIL_ISAM causes an LISM_ERR(963) error to be	*/
/* returned if CLSFIL is called for an ISAM data file.		*/
/*								*/
/* COMPATIBILITY CLSFIL_ISAM restores the old behavior when	*/
/* CLSFIL is called for an ISAM data file.			*/
/*								*/
/*								*/
/* DEFAULT:  New behavior on by default for versions 9.6 or	*/
/* greater							*/
/*--------------------------------------------------------------*/
#if ctVER_GE(9,6)

#ifndef NO_ctBEHAV_CLSFIL_ISAM
#ifndef ctBEHAV_CLSFIL_ISAM
#ifdef CTS_ISAM
#define ctBEHAV_CLSFIL_ISAM
#endif
#endif
#endif

#endif

/*
** check for required support for ctBEHAV_CLSFIL_ISAM if it is
** defined externally. w/o support, turn off ctBEHAV_CLSFIL_ISAM
*/
#ifdef ctBEHAV_CLSFIL_ISAM
#ifndef CTS_ISAM
#undef ctBEHAV_CLSFIL_ISAM
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_FNCTIMupd uses ATOMIC update routines to maintain	*/
/* function timing stats. This reduces the calls to ctpc6ncsema	*/
/* which were made on every user API call routed through	*/
/* doserver(). It is still used to aggregate individual user	*/
/* function timings into system-wide stats, but this happens	*/
/* only one out of each 1024 function calls.			*/
/*								*/
/* ctBEHAV_FNCTIMupd is on by default as long as 64-bit		*/
/* interlocked update routines are supported (ctFeatATOMICop64)	*/
/*--------------------------------------------------------------*/
#if ctVER_GE(10,0)
#if !defined(NO_ctBEHAV_FNCTIMupd) && defined(ctFeatATOMICop64)
#define ctBEHAV_FNCTIMupd
#endif
#endif

#if defined(ctBEHAV_FNCTIMupd) && !defined(ctFeatATOMICop64)
#undef ctBEHAV_FNCTIMupd
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_MULTIOPN_DIFUSR changes the locking behavior when a	*/
/* client opens a file with more than one (user) file number,	*/
/* and issues locks on the same record using the different file	*/
/* numbers. With this define enabled and COMPATIBILITY		*/
/* MULTIOPN_DIFUSR in the configuration, then lock requests	*/
/* for the same user using different file numbers will be	*/
/* treated as if the lock requests were from different users.	*/
/*								*/
/* ctBEHAV_MULTIOPN_DIFUSR is on by default			*/
/* ctMULTIOPN is required					*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctBEHAV_MULTIOPN_DIFUSR) && defined(MULTITRD)
#define ctBEHAV_MULTIOPN_DIFUSR
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_MULTIOPN_LINK changes the way we find multiple opens	*/
/* of the same file by a single thread using different user	*/
/* file numbers. We refer to the collection of such files (that	*/
/* all map into the same ctnum->filnum) for a given thread as	*/
/* co-files. Before this change user co-files were found using	*/
/* a for loop to check all files opened by the user. With	*/
/* ctBEHAV_MULTIOPN_LINK enabled the FUSR structures for each	*/
/* co-file are in a circular linked list. Given a pointer to a	*/
/* particular FUSR structure we can immediately find all of	*/
/* its co-files or determine that it has no co-files.		*/
/*								*/
/* ctBEHAV_MULTIOPN_LINK is on for server by default in v10.3.0	*/
/* and later.							*/
/* Requires ctMULTIOPN.						*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctBEHAV_MULTIOPN_LINK) && defined(MULTITRD)
#define ctBEHAV_MULTIOPN_LINK
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_MULTIOPN_SAMUSR changes the locking behavior when a	*/
/* client opens a file with more than one (user) file number,	*/
/* and issues locks on the same record using the different file	*/
/* numbers. With this define enabled and COMPATIBILITY		*/
/* MULTIOPN_SAMUSR_1 or COMPATIBILITY MULTIOPN_SAMUSR_M in the	*/
/* configuration, then lock requests for the same user using	*/
/* different file numbers will be treated as if the lock	*/
/* requests were made by the same user on the same file.	*/
/*								*/
/* The two flavors of SAMUSR differ in their unlocking		*/
/* behavior. SAMUSR_1 permits an unlock of a record with a	*/
/* user file number that was not used to lock the record	*/
/* (provided that the the user file number corresponds to the	*/
/* same file as the user file number that was used in the call	*/
/* to lock the record). SAMUSR_M fails an unlock request if	*/
/* the user file number was not used in a lock request.		*/
/*								*/
/* ctBEHAV_MULTIOPN_SAMUSR is on by default for V10.3.0 or	*/
/* later, and ctBEHAV_MULTIOPN_LINK is required			*/
/* ctMULTIOPN is required					*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctBEHAV_MULTIOPN_SAMUSR) && defined(ctBEHAV_MULTIOPN_LINK)
#define ctBEHAV_MULTIOPN_SAMUSR
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_maxcnt attempts to improve performance, especially	*/
/* for large transactions, by eliminating unncessary looping	*/
/* over pre-image space entries. Pre-image space contains data	*/
/* record images, key values, savepoint markers, and a host of	*/
/* other file content related information. Each user has its	*/
/* own pre-image space that starts fresh for each transaction.	*/
/*								*/
/* Pre-image space may contain multiple images for data records	*/
/* depending on the use of regular and special savepoints, and	*/
/* depending on how records are updated within a transaction.	*/
/* srchshd81() uses a dynamic hash to quickly find a data	*/
/* record image in pre-image space no matter how many pre-image	*/
/* space entries exist, but if there are multiple occurrences	*/
/* of the data record, then additional pre-image entries must	*/
/* be examined. The shadcnt value for the first entry found	*/
/* indicates the maximum number of images for the data record,	*/
/* but there may be less. The fact that shadcnt may over state	*/
/* the number of images is the cause of the performance problem.*/
/*								*/
/* For small transactions with relatively few pre-image space	*/
/* entries, the performance degradation is quite small. But	*/
/* for large transactions, it can be significant.		*/
/*								*/
/* ctBEHAV_maxcnt changes the management of the pre-image	*/
/* entries so that the shadcnt value will match the actual	*/
/* number of images.						*/
/*								*/
/* ctBEHAV_maxcnt is on by default for V10.0 or greater		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_maxcnt
#if ctVER_GE(10,0)
#define ctBEHAV_maxcnt
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_ADJFILSIZ changes the behavior of the scndat()	*/
/* routine called by the internal data file rebuild routine	*/
/* RBLDATX() so that the header values for the physical file	*/
/* size match the actual file size on disk.			*/
/*								*/
/* The logical file size computation has been refined, making	*/
/* fixed and variable length files behave in a similar fashion.	*/
/*								*/
/* If a partial record or resource is found at the end of the	*/
/* file, CTSTATUS.FCS will contain the offset and length of the	*/
/* partial record. If the purgeIFIL option is on then (1) the	*/
/* partial recrd will be dumped to a temporary file in a manner	*/
/* similar to records that are purged because of duplicate keys	*/
/* (although a different temporary file will be used for the	*/
/* partial record dump); and (2) the partial record will be	*/
/* overwritten with 0xff bytes.					*/
/*								*/
/* ctBEHAV_ADJFILSIZ is on by default				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_ADJFILSIZ
#define ctBEHAV_ADJFILSIZ
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_REPLPOS changes the behavior of the replication	*/
/* agent positioning logic: the replication agent informs the	*/
/* source server of its log requirements, instead of the source	*/
/* server determining the log requirements as the agent reads	*/
/* from the logs.						*/
/*								*/
/* Default: ctBEHAV_REPLPOS is ON for v10 and later.		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_REPLPOS
#if ctVER_GE(10,0)
#ifdef TRANPROC
#define ctBEHAV_REPLPOS
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_POLL changes the behavior of communications logic to */
/* use the poll() function instead of the select() function	*/
/* in order to avoid limits on the value of file descriptors 	*/
/* used with select().  Unix-like systems typically limit the   */
/* value of the file descriptor to FD_SETSIZE, not merely the   */
/* number of descriptors.					*/
/*								*/
/* Default: ctBEHAV_POLL is ON for unix like systems            */
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_POLL
#ifdef ctPortUNIX
#define ctBEHAV_POLL
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_MBR_IDX_FID_MBR changes clropnhdr() treatment of	*/
/* SUPERFILE index members during recovery so that when the	*/
/* host index is assigned a pseudo lgtorc mapping of		*/
/* NO_OP_MBR - ctnum->filnum, the members of the index are	*/
/* assigned a pseudo mapping of NOT_OP_FID_MBR. Without this	*/
/* change, the index members are assigned NO_OP_MBR -		*/
/* ctnum->filnum (where ctnum is for the host index). In the	*/
/* case of a TRANDEP rename of a SUPERFILE (index) member,	*/
/* this caused a L64 ctcatend.					*/
/*								*/
/* NOT_OP_FID_MBR was originally used for index members,	*/
/* whether or not the host index was a member of a SUPERFILE,	*/
/* when a FIDD_ERR occurred for the host index.  This usage	*/
/* extends NOT_OP_FID_MBR to any instance of a deleted header	*/
/* for a SUPERFILE member index.				*/
/*								*/
/* [The first MBR in ctBEHAV_MBR_IDX_FID_MBR refers to an	*/
/* index file that is a member of a SUPERFILE. The second MBR	*/
/* refers to its index members (i.e., the other indices that	*/
/* reside in the SUPERFILE member index).]			*/
/*								*/
/* Default: ctBEHAV_MBR_IDX_FID_MBR is ON in			*/
/* version 10.0 and later.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_MBR_IDX_FID_MBR
#ifdef ctBEHAV_FIDD_ERR
#if ctVER_GE(10,0)
#define ctBEHAV_MBR_IDX_FID_MBR
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_QT_DYNDMP changes the way ctQUIET and Dynamic Dump	*/
/* interact. The ctp1dmsema, meant to avoid overlap between	*/
/* multiple dynamic dumps, and between ctQUIET and dynamic	*/
/* dumps, was not employed effectively in all cases. This	*/
/* modification changes how ctp1dmsema is employed. Also,	*/
/* ctaddwork() has been modified to better detect interactions	*/
/* between ctQUIET and dynamic dumps; and ctaddwork()		*/
/* invocation has been moved from the time idyndmp() thread	*/
/* is launched to the scheduled time of the actual dump.	*/
/*								*/
/* Default: ctBEHAV_QT_DYNDMP is ON in version 10.1.3		*/
/* and later.							*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_QT_DYNDMP
#ifdef ctWORKMON
#if ctVER3_GE(10,2,0)
#define ctBEHAV_QT_DYNDMP
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_LKISAM_MODES causes LKISAM to return a BMOD_ERR if	*/
/* the lokmod parameter includes any of the lock/transaction	*/
/* modifier bits not intended for use with LKISAM (see		*/
/* ctNotForLKISAM in ctport.h). COMPATIBILITY LKISAM_MODES	*/
/* will disable this error return by a server.			*/
/*								*/
/* Default: ctBEHAV_LKISAM_MODES is ON				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_LKISAM_MODES
#define ctBEHAV_LKISAM_MODES
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_CMP_RENAME changes the behavior of the file compact	*/
/* function's logic that replaces the original data file with	*/
/* the newly compacted data file. Instead of first deleting	*/
/* the original data file and then renaming the new data file	*/
/* to the original data file's name, c-tree first renames the	*/
/* original data file, then renames the new data file to the	*/
/* original name, and finally deletes the original (renamed)	*/
/* data file if successful, or renames the original data file	*/
/* to its original name if an error occurred.			*/
/*								*/
/* Default: ctBEHAV_CMP_RENAME is ON				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CMP_RENAME
#define ctBEHAV_CMP_RENAME
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_CHKALGN causes a client to ensure their are no	*/
/* alignment issues when a data record is sent to the server	*/
/* or read from the server. An alignment issue occurs when a	*/
/* field value must be moved to ensure compatibility with the	*/
/* target alignment. If there is an alignment issue, then the	*/
/* operation fails with a ALGN_ERR(992).			*/
/* 								*/
/* Until the client supports separate buffers into which the	*/
/* record image can be transformed to ensure correct alignment,	*/
/* the internal routines ctconvert28/38() cannot deal with the	*/
/* alignment issue.						*/
/*								*/
/* If ctBEHAV_CHKALGN is changed to default on, we may want to	*/
/* add configuration options:					*/
/*			     COMPATIBILITY CHECK_ALIGNMENT  or	*/
/*			     DIAGNOSTICS CHECK_ALIGNMENT	*/
/*								*/
/* so that existing applications that deal with alignment	*/
/* issues internally do not receive the ALGN_ERR(992) unless	*/
/* the alignment check is turned on in the configuration info.	*/
/*								*/
/* Default: ctBEHAV_CHKALGN is OFF				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CHKALGN
/*
** default off
**		#define ctBEHAV_CHKALGN
*/
#endif



/*--------------------------------------------------------------*/
/* ctBEHAV_CNVT38 extends the server side data record		*/
/* conversion support utilized by the batch update routines	*/
/* to the ISAM and low level routines that update data records. */
/*								*/
/* The primary reason to implement the associated code changes	*/
/* is to prepare for record conversions that require alignment	*/
/* adjustments. It is also possible that server side record	*/
/* conversions may be useful in other contexts. 		*/
/*								*/
/* NOTE: until cnvbuf38 and ctconvert28 are modified to handle	*/
/* alignment discrepancies, turning ctBEHAV_CNVT38 will not	*/
/* avoid the ALGN_ERR(992).					*/
/*								*/
/* Default: ctBEHAV_CNVT38 is OFF				*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctBEHAV_CNVT38) && \
     defined(ctSRVR)		&& \
    !defined(ctBNDSRVR)		&& \
     defined(ctBEHAV_CHKALGN)

#if ctVER3_GE(10,3,0)
/* #define ctBEHAV_CNVT38 */
#endif

#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_BAT_FXDCMP changes the behavior of the batch		*/
/* routines that retrieve and insert fixed length, compressed	*/
/* data records so that they are treated as fixed length data	*/
/* records instead of variable length records. In particular,	*/
/* this makes the batch routines consistent with the relatively */
/* new batch update option (BAT_UPD).				*/
/*								*/
/* NOTE: fixed length, compressed data records are actually	*/
/* variable length data records on disk, but the c-tree API	*/
/* treats as fixed length records.				*/
/*								*/
/* Default: ctBEHAV_BAT_FXDCMP is ON				*/
/*--------------------------------------------------------------*/
#if defined(ctCMPREC) && !defined(NO_ctBEHAV_BAT_FXDCMP)
#define ctBEHAV_BAT_FXDCMP
#endif
#if defined(ctBEHAV_BAT_FXDCMP) && !defined(ctCMPREC)
#undef ctBEHAV_BAT_FXDCMP
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_DEFER_ALTSEQ delays the reading of the alternate	*/
/* collating sequence for an index file until it is requested	*/
/* by the client library. The original behavior was to always	*/
/* read the alternate collating sequence when the index segment	*/
/* information was requested.					*/
/*								*/
/* Default: ctBEHAV_DEFER_ALTSEQ is ON				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_DEFER_ALTSEQ
#define ctBEHAV_DEFER_ALTSEQ
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_MULTIOPN_DIFUSRfile supports the MULTIOPN_DIFUSR and	*/
/* MULTIOPN_SAMUSR features on a per-file, per-connection	*/
/* level. When this behavior is enabled at compile time, a	*/
/* call to PUTHDR with mode of ctMULTIOPNhdr can be used to	*/
/* change the manner in which c-tree interprets lock/unlock	*/
/* calls on a particular record on different instances of the	*/
/* file that are open by a connection.				*/
/*								*/
/* We currently support the following four interpretations of	*/
/* lock requests made on multiple instances of a file by a	*/
/* particular connection:					*/
/*								*/
/*   ctMULTIOPNdifusr - locks treated as if by different users.	*/
/*	This is the default setting when the server uses the	*/
/*	COMPATIBILITY MULTIOPN_DIFUSR configuration option.	*/
/*								*/
/*   ctMULTIOPNsamusr_M - locks treated as if by same user,	*/
/*	but unlock requests must be made with a user file	*/
/*	number with which record has been locked. This is the	*/
/*	default setting when the server uses the		*/
/*	COMPATIBILITY MULTIOPN_SAMUSR_M config option.		*/
/*								*/
/*   ctMULTIOPNsamusr_1 - locks treated as if by same user,	*/
/*	and unlock requests can be made using any of the user	*/
/*	file numbers with which the file has been opened. This	*/
/*	is the default setting when the server uses the		*/
/*	COMPATIBILITY MULTIOPN_SAMUSR_1 config option.		*/
/*								*/
/*   ctMULTIOPNnodifusr - locks treated as if by same user but	*/
/*	unlocking behavior is inconsistent: only the release	*/
/*	of the lock acquired first actually removes the lock.	*/
/*	This is the default setting when the server does not	*/
/*	use any of the COMPATIBILITY MULTIOPN_xxxUSR config	*/
/*	options.						*/
/*								*/
/* ctBEHAV_MULTIOPN_DIFUSRfile is on for server by default in	*/
/* v10.2 and later, or when COBOL support is enabled.		*/
/* Requires ctBEHAV_MULTIOPN_DIFUSR or ctBEHAV_MULTIOPN_SAMUSR	*/
/* and ctBEHAV_ULCNT.						*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctBEHAV_MULTIOPN_DIFUSRfile) && defined(MULTITRD)
#if (defined(ctBEHAV_MULTIOPN_DIFUSR) || defined(ctBEHAV_MULTIOPN_SAMUSR)) && defined(ctBEHAV_ULCNT)
#if ctVER3_GE(10,2,0) || defined(ctFeatCOBOL)
#define ctBEHAV_MULTIOPN_DIFUSRfile
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_IICTflex changes the approach to detect inteference	*/
/* between the encompassing transaction and the IICT (both	*/
/* autotran and xtd varities). INstead of checking at the file	*/
/* level which denies transactions that do no intefere, we now	*/
/* base it on record level interference.			*/
/*								*/
/* The simplest case is when DIFUSR applies to the file and	*/
/* ctCHECKLOCK is enabled for the file, then record locking	*/
/* will avoid the interference. Otherwise we rely on checking	*/
/* the preimage space of the encompassing tansaction to find	*/
/* possible interference. This requires a special call		*/
/* (SHDIICT) to srchshd81().					*/
/*								*/
/* With or without this new approach, a TPND_ERR(420) may	*/
/* occur if unique keys are involved in the interference since	*/
/* the key update typically occur before the data record	*/
/* updates.							*/
/*								*/
/* ctBEHAV_IICTflex is on for server by default in v10.3 and	*/
/* later, or when COBOL support is enabled. Requires ctFeatIICT */
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_IICTflex
#if ctVER3_GE(10,2,0) || defined(ctFeatCOBOL)
#define ctBEHAV_IICTflex
#ifndef NO_ctBEHAV_IICTflexSTT
/* Improved handling of user file state when an IICT is allowed to update a
** file that the outer transaction updated. */
#ifdef ctFeatATOMICop
#define ctBEHAV_IICTflexSTT
#endif
#endif
#endif
#endif

/*
** check for the required ctFeatIICT support after the ctFeat
** section of this module
*/


/*--------------------------------------------------------------*/
/* ctBEHAV_SKIP_RESOURCES permits a file to be opened that may	*/
/* be corrupt and include a bad resource chain. The file open	*/
/* request must have ctDISABLERES and ctOPENCRPT included in	*/
/* the file mode. On a server, since we are skipping resources,	*/
/* we cannot check password security. Therefore this open file	*/
/* call must be made by a user in the ADMIN group.		*/
/*								*/
/* If the file is encrypted or compressed, resources are	*/
/* required to interpret the file. If these resources exist	*/
/* and cannot be accessed, the file open will still fail.	*/
/*								*/
/* For both server and non-server, the file is opened read	*/
/* only.							*/
/*								*/
/* Default: ctBEHAV_SKIP_RESOURCES is ON			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_SKIP_RESOURCES
#define ctBEHAV_SKIP_RESOURCES
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_UPDMARKS causes index updates to skip cleaning up	*/
/* key level marks for transaction-controlled indices.		*/
/*								*/
/* 1) calls to ctgetnod81() and chkremnod() have been modified	*/
/*    so that requests made while adding or deleting a key	*/
/*    value can be identified. If ctBEHAV_UPDMARKS is defined	*/
/*    at compile time, then the call to ctclup() is skipped.	*/
/*								*/
/* Note that ctclup() processes/removes key-level locks for	*/
/* transactions that have been committed or aborted.		*/
/*								*/
/* 2) the most obvious problem caused by skipping ctclup() is	*/
/*    that an attempt to update a key value with a pending	*/
/*    key-level lock (e.g., trying to add a unique value that	*/
/*    has already been added but not committed) results in a	*/
/*    TPND_ERR(420). By not cleaning up the key-level lock for	*/
/*    a committed or aborted transaction, the key update will	*/
/*    cause a TPND_ERR when it shouldn't.			*/
/*								*/
/* This problem can be addressed in two ways:			*/
/*								*/
/* (a) when a collision occurs with a key-level lock, attempt	*/
/*     to clean up only that particular key-level lock		*/
/*     [as compared to ctclup() that attempts to clean up all	*/
/*     the key level locks in the node]; or			*/
/*								*/
/* (b) take advantage of the existing, internal retry logic	*/
/*     that tries to perform the update ctTPND_ERR_RETRY times;	*/
/*     and on the retry change the ctgetnod81()/chkremnod81()	*/
/*     so that ctclup() will be performed.			*/
/*								*/
/* At least for now, (b) has been implemented because of its	*/
/* simplicity. This means that if a false TPND_ERR occurs,	*/
/* then the retry will clean the entire node (not just the	*/
/* particular lock in question), and then get the correct	*/
/* result.							*/
/*								*/
/* Default: ctBEHAV_UPDMARKS is ON v10.4.0 and later (server).	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_UPDMARKS
#if defined(MULTITRD) && defined(TRANPROC)
#if ctVER3_GE(10,4,0)
#define ctBEHAV_UPDMARKS
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_UPDMARKSsplit adds a check to nodes about to be	*/
/* split to see if there are candidates to be cleaned up	*/
/* [ctclup], and hence avoid the node split. The motivation for	*/
/* this option is that (with ctBEHAV_UPDMARKS) a large number	*/
/* of aborted add key operations may persist in the index	*/
/* leading to unnecessary nodes splits and the abort node list	*/
/* growing in size. The node splits and abort node list growth	*/
/* are not causing incorrect behavior, but they may be		*/
/* degrading performance.					*/
/*								*/
/* When a node is about to be split, and it contains a large	*/
/* number of key marks (i.e., transaction specific key level	*/
/* locks) that have not been cleaned up (because the		*/
/* ctBEHAV_UPDMARKS option skips key mark cleanup during index	*/
/* updates), then we defer the node split, attempt to clean up	*/
/* the key marks, and retry the add key operation.		*/
/*								*/
/* The cleanup (performed by calling ctclup) is not guaranteed	*/
/* to actually remove any key marks and/or make space in the	*/
/* node. If all of the marks are for pending transactions the	*/
/* marks will be skipped by ctclup. Also, even if there are	*/
/* marks for aborts and commits, the node may not have space	*/
/* created by the cleanup if the marks are for committed adds	*/
/* or aborted deletes. If the cleanup is effective, then the	*/
/* retry will add the key without a node split, and the abort	*/
/* node list will be shortened.					*/
/*								*/
/* When the add is retried, we disable the node split check so	*/
/* that we do not create a cycle of deferred node splits	*/
/* followed by additional retries.				*/
/*								*/
/* The tradeoff with this option is attempting the cleanup and	*/
/* performing the add key retry versus allowing uncleaned key	*/
/* marks to persist "too long" in the index: not causing a	*/
/* problem other than possible performance issues.		*/
/*								*/
/* This behavior can be disabled at run-time with a		*/
/* configuration entry:						*/
/*			UPDMARKS_SPLITCHK_PERCENT 0		*/
/*								*/
/* Default: ctBEHAV_UPDMARKSsplit is ON v10.5.0 and later	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_UPDMARKSsplit
#if defined(ctBEHAV_UPDMARKS) && ctVER3_GE(10,5,0)
#define ctBEHAV_UPDMARKSsplit
#endif
#endif

#if defined(ctBEHAV_UPDMARKSsplit) && !defined(ctBEHAV_UPDMARKS)
#undef ctBEHAV_UPDMARKSsplit
#endif

#ifndef ctUPDMARKS_SPLITCHK_DEFAULT
#define ctUPDMARKS_SPLITCHK_DEFAULT	33	/* percentage	*/
#endif
#if ctUPDMARKS_SPLITCHK_DEFAULT < 0 || ctUPDMARKS_SPLITCHK_DEFAULT > 101
#error ctUPDMARKS_SPLITCHK_DEFAULT is out of range
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_ABNTRAN changes abandoned transactions, which would	*/
/* not generate a (terminating) log entry, to an aborted	*/
/* transaction. The trantorg member of the TRANDSC structure	*/
/* is set to ABNTRAN so that abandoned transactions can be	*/
/* distinguished from aborted transactions (if necessary).	*/
/*								*/
/* This change in behavior ensures that, except in the case of	*/
/* a system crash, all BEGTRAN log entries will have a matching	*/
/* entry at the end of the transaction. This is particularly	*/
/* useful for the replication processing.			*/
/*								*/
/* ctBEHAV_ABNTRAN is on for server by default in v9.5.3	*/
/* and later. Requires ctXTDLOG (checked later).		*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctBEHAV_ABNTRAN) && ctVER3_GE(9,5,3)
#define ctBEHAV_ABNTRAN
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_RCVHDRUPD changes the way automatic recovery uses	*/
/* certain transaction log entries that contain information	*/
/* stored in the volatile region of a data file header that	*/
/* includes file size and delete stack entries. If a file has	*/
/* been closed cleanly, then we change the behavior of the	*/
/* internal rcvhdrupd() routine to use the header values. And	*/
/* LOGEXTFIL entries are also used to update file size header	*/
/* entries as needed. And at CLSTRAN a check is made for	*/
/* compatible file size header values.				*/
/*								*/
/* ctBEHAV_RCVHDRUPD is on by default.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_RCVHDRUPD
#define ctBEHAV_RCVHDRUPD
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_RBLDCHKPNT causes a checkpoint to be called just	*/
/* at the start of a RBLIFIL or CMPIFIL call. Without the	*/
/* checkpoint, a system crash after the rebuild/compact for	*/
/* TRANDEP ISAM files that were created just before the		*/
/* rebuild/compact could result in a failed automatic recovery;	*/
/* terminating with a FIDD_ERR(499).				*/
/*								*/
/* The rebuild/compact perform file operations (creates/renames)*/
/* that are not part of the transaction logs, and confused the	*/
/* create file log entries made before the rebuild/compact. The	*/
/* new checkpoint keeps potential tranred() operations from	*/
/* including the creates.					*/
/*								*/
/* ctBEHAV_RBLDCHKPNT is on by default when TRANPROC is enabled	*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctBEHAV_RBLDCHKPNT) && defined(TRANPROC)
#define ctBEHAV_RBLDCHKPNT
#endif
#if defined(ctBEHAV_RBLDCHKPNT) && !defined(TRANPROC)
#undef ctBEHAV_RBLDCHKPNT
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_IDfield_overflow supports the detection of IDfield	*/
/* overflow and unsigned IDfields (as well as the existing	*/
/* support for signed IDfields). The overflow detection is	*/
/* based on the number of bytes in the IDfield determined by the*/
/* associated DODA (from 1 to 8 bytes). If the underlying field	*/
/* definition in the associated DODA is for a variable length	*/
/* field, then the overflow detection is performed as if the	*/
/* field is 8 bytes.						*/
/*								*/
/* For IDfields added to a data file without this define	*/
/* enabled, the fields are treated as signed, regardless of	*/
/* the associated DODA. If the define is subsquently enabled,	*/
/* then at first subsequent open the IDfield attributes are	*/
/* updated to the new behavior unless a COMPATIBILITY keyword	*/
/* indicates otherwise.						*/
/*								*/
/* If the IDfield support is modified in the future to define	*/
/* an IDfield without an associated DODA (by specifying the	*/
/* offset and length directly), then we will want to also	*/
/* include a direct specification of whether the field is	*/
/* signed or unsigned.						*/
/*								*/
/* Default: ctBEHAV_IDfield_overflow is on for V10.5.0 or	*/
/* greater.							*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctBEHAV_IDfield_overflow) && ctVER3_GE(10,4,1)
#define ctBEHAV_IDfield_overflow
#define ctBEHAV_IDfield_overflow_ctopt2
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_EOR_CLSTRAN permits automatic recovery to write	*/
/* CLSTRAN entries for files that do not have a CLSTRAN in the	*/
/* log presumably because of a system crash.			*/
/*								*/
/* Generally the missing CLSTRAN does not cause a problem, but	*/
/* when rolling backward, a missing CLSTRAN can cause certain	*/
/* transaction undo actions to be skipped. This issue effects	*/
/* ctrdmp rollbacks and attempts to RECOVER_TO_RESTORE_POINT	*/
/* as part of a server restarting after a crash.		*/
/*								*/
/* The ctTRANATR_CLSTRAN_RCVR bit is turned on to indicate	*/
/* that the CLSTRAN has been written at the end of recovery.	*/
/* See also ctSIBLING_EOR_LOGGING.				*/
/*								*/
/* ctBEHAV_EOR_CLSTRAN defaults on for versions of 10.5.0	*/
/* or greater.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1) && defined(TRANPROC)
#ifndef NO_ctBEHAV_EOR_CLSTRAN
#define ctBEHAV_EOR_CLSTRAN
#endif
#endif

#if defined(ctBEHAV_EOR_CLSTRAN) && (!defined(TRANPROC) || !defined(ctXTDLOG))
#undef ctBEHAV_EOR_CLSTRAN
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_EOR_CLSTRAN2 changes the behavior of ctBEHAV_EOR_CLSTRAN in the
  following ways:

  1) When transcn81() is scanning forward from checkpoint and processes a file
     open or create entry, turn off the file's 'file closed at recovery' bit.
  2) When tranred() processes a CLSTRAN entry, only turn on the 'file closed
     at recovery' bit if the entry's tfil is the last (highest-numbered) tfil
     that transcn81() found for the file.
 
  Default: ctBEHAV_EOR_CLSTRAN2 is on in v11.8.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifndef NO_ctBEHAV_EOR_CLSTRAN2
#define ctBEHAV_EOR_CLSTRAN2
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_VFLG_ERR enables a physical order traversal of a	*/
/* variable-length data file to avoid a VFLG_ERR when other	*/
/* connections are adding records to the file at the same time	*/
/* that the physical order traversal is performed.		*/
/*								*/
/* When the physical order traversal reads a record header that	*/
/* has an invalid record mark, after it verifies that the	*/
/* record offset lies within the used portion of the file, the	*/
/* code now re-reads the record header and checks if its mark	*/
/* is valid. If so, it treats it in the appropriate manner for	*/
/* that record mark. If not, VFLG_ERR is returned.		*/
/*								*/
/* This re-check of the record header avoids the VFLG_ERR that	*/
/* is caused by the reader encountering unused (0xffff mark)	*/
/* space in the file that exists when a variable-length record	*/
/* add operation has extended the logical end of file (numrec1)	*/
/* but has not yet written a valid record mark to the record	*/
/* header for the new record.					*/
/*								*/
/* In order to avoid VFLG_ERR for a non-transaction file, this	*/
/* option also changes the variable-length record add logic for	*/
/* a non-transaction file: the active record mark is written	*/
/* before releasing the file header mutex.			*/
/*								*/
/* The server configuration option COMPATIBILITY NO_VFLG_ERR	*/
/* can be used to restore the original behavior.		*/
/*								*/
/* Default: ctBEHAV_VFLG_ERR is ON by default for MULTITRD	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_VFLG_ERR
#ifdef MULTITRD
#define ctBEHAV_VFLG_ERR
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_RCVHDRUPDnument changes the way automatic recovery	*/
/* handles updates to the nument field of a fixed-length data	*/
/* file header:							*/
/*								*/
/* 1. When recovery processes an OPNTRAN entry for a file that	*/
/*    is already open, it sets the nument value	in the file	*/
/*    control block to the value from the OPNTRAN entry.	*/
/*								*/
/* 2. Updates to nument that occur before the last open of the	*/
/*    file are ignored.						*/
/*								*/
/* ctBEHAV_RCVHDRUPDnument is on by default.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_RCVHDRUPDnument
#define ctBEHAV_RCVHDRUPDnument
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_CMPREC_optimize enables code that optimizes the	*/
/* record compression support.					*/
/*								*/
/* Requires ctCMPREC						*/
/*								*/
/* ctBEHAV_CMTREC_optimize is on in v10.6.0 and later and for	*/
/* ABACUS OEM.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,6,0) || defined(ctPortABACUS)
#ifndef NO_ctBEHAV_CMPREC_optimize
#ifdef ctCMPREC
#define ctBEHAV_CMPREC_optimize
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_DYNDMP_STREAM changes our writing of the dynamic	*/
/* dump backup file so that it can be written to a stream.	*/
/*								*/
/* This involves the following changes:				*/
/*								*/
/* a) Change the way in which we indicate in a dynamic dump	*/
/*    backup file that it includes logs or data and index files	*/
/*    that use encryption. In our original approach, at the end	*/
/*    of the dump (when we know that logs or data/index files	*/
/*    are using encryption), we seeked back to the start of the	*/
/*    dump backup file and wrote the attributes to the dump	*/
/*    file's first header.					*/
/*								*/
/*    In the new approach, the server writes the encryption	*/
/*    attributes to the final header of the dump backup file,	*/
/*    so there is no need to seek back to the start of the	*/
/*    dump file.						*/
/*								*/
/* b) The EXT_SIZE dump script option now defaults to NO, so	*/
/*    that the dump backup is written to a single file.		*/
/*								*/
/* ctBEHAV_DYNDMP_STREAM is on in v10.6.0 and later.		*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,6,0)
#ifndef NO_ctBEHAV_DYNDMP_STREAM
#define ctBEHAV_DYNDMP_STREAM
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_FLUSH_NODE_MARKS changes the behavior of a key add	*/
/* or delete operation on a transaction-controlled index that	*/
/* undoes the deletion or addition of that same key value in	*/
/* the same transaction. Prior to this modification, the key	*/
/* add or delete immediately forced the leaf node to disk.	*/
/*								*/
/* When ctBEHAV_FLUSH_NODE_MARKS is defined, if the key add or	*/
/* delete is removing the last key mark for that transaction,	*/
/* the buffer is still flushed immediately. Otherwise the	*/
/* buffer is marked as requiring flush when the transaction	*/
/* commits (if not flushed sooner). The transaction commit	*/
/* flushes those buffers that require flushing and syncs the	*/
/* index file to ensure that the changes are on disk.		*/
/*								*/
/* ctBEHAV_FLUSH_NODE_MARKS is on in v10.4.1 and later for	*/
/* TRANPROC compiles when ctBEHAV_BLM is defined.		*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1)
#ifndef NO_ctBEHAV_FLUSH_NODE_MARKS
#ifdef TRANPROC
#ifdef ctBEHAV_BLM
#define ctBEHAV_FLUSH_NODE_MARKS
#endif
#endif
#endif
#endif

#ifdef ctBEHAV_FLUSH_NODE_MARKS
#ifndef ctBEHAV_BLM
#error ctBEHAV_FLUSH_NODE_MARKS requires ctBEHAV_BLM
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_FPGHDRLOK corrects some inconsistencies in header	*/
/* locking in FPUTFGET mode for non-huge index files and	*/
/* variable-length data files. For both of these types of files,*/
/* we want to always lock the header by calling LOCK81() at	*/
/* offset hdrpos.						*/
/*								*/
/* ctBEHAV_FPGHDRLOK changes some DLOCK81() header lock calls	*/
/* for variable-length data files to LOCK81() header lock calls,*/
/* and ensures that LOCK81() calls for both hdroff and hdrpos	*/
/* are treated as locks at offset hdrpos.			*/
/*								*/
/* ctBEHAV_FPGHDRLOK is on for the FPUTFGET operational model	*/
/* in v11.0.0 and later.					*/
/*--------------------------------------------------------------*/

#if ctVER3_GE(10,99,0) || defined(ctPortTDSRX30)
#ifdef FPUTFGET
#ifndef NO_ctBEHAV_FPGHDRLOK
#define ctBEHAV_FPGHDRLOK
#endif
#endif
#endif

#ifdef FPUTFGET
/* Enable ctDBGwrthdrSEQNUM in order to check for improper header locking.
** It wrthdr() reads the header from disk and finds that the header sequence
** number differs from our in-memory header image, it logs a message to
** CTSTATUS.FCS.
**
** #define ctDBGwrthdrSEQNUM
*/

/*
** Enable ctTSTiopnfilwrthdr in order to make the wrthdr() call in iopnfilx()
** happen on each file open.
**
** #define ctTSTiopnfilwrthdr
*/
#endif
/*--------------------------------------------------------------*/
/* ctBEHAV_FPGIOLOK implements IO locking for unix systems,     */
/* to make the unix locking behave similar to windows.          */
/* This requires the ctLOCK_EXTENDED locking protocol.  	*/
/* ctLOCK_DIRECT should no longer be used.			*/
/*                                                              */
/* ctBEHAV_FPGIOLOK is on for unix FPUFGET compiles in V11.     */
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,99,0) || defined(ctPortTDSRX30)
#ifdef FPUTFGET
#ifdef ctPortUNIX
#ifndef NO_ctBEHAV_FPGIOLOK
#define ctBEHAV_FPGIOLOK
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_TLOGBUF_LFLSEMA causes tlogbuf() to acquire the log	*/
/* flush mutex to ensure that a log flush cannot be happening	*/
/* while tlogbuf() is writing to the log buffer.		*/
/*                                                              */
/* ctBEHAV_TLOGBUF_LFLSEMA is on for c-tree Server in v11.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,0,0)
#ifndef NO_ctBEHAV_TLOGBUF_LFLSEMA
#ifdef MULTITRD
#define ctBEHAV_TLOGBUF_LFLSEMA
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_MINIDXBUF reduces the minimum requirement on the	*/
/* number of index buffers for c-tree Server. When this feature	*/
/* is enabled, instead of requiring 3 * max_connections index	*/
/* buffers we limit the concurrency of calls to ctgetnod81()	*/
/* and lrubuf81() based on the actual number of allocated index	*/
/* buffers.							*/
/*								*/
/* If desired, the previous behavior can be reinstated by using	*/
/* the option COMPATIBILITY MINIMUM_INDEX_BUFFERS in ctsrvr.cfg.*/
/*                                                              */
/* ctBEHAV_MINIDXBUF is on for c-tree Server v11.1.0 and later.	*/
/* Requires the new index cache feature ctFeatNoIdxPndgList to	*/
/* be on (we check this requirement later).			*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,1,0)
#ifdef MULTITRD
#ifndef NO_ctBEHAV_MINIDXBUF
#ifndef ctBEHAV_MINIDXBUF
#define ctBEHAV_MINIDXBUF
/* Indicate that we turned on ctBEHAV_MINIDXBUF in ctopt2.h: */
#define ctBEHAV_MINIDXBUFctopt2
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_IDXMBRUPDFLG causes c-tree to set and check the	*/
/* update flag of the index member, not the index host.	This	*/
/* makes it possible to distinguish exactly which indices have	*/
/* errors.							*/
/*								*/
/* Default: ctBEHAV_IDXMBRUPDFLG is ON in version 11.2.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctBEHAV_IDXMBRUPDFLG
#define ctBEHAV_IDXMBRUPDFLG
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_REPIMGRWTCMB modifies replication's processing of	*/
/* multiple updates to a record by a transaction so that unique	*/
/* key conflicts do not occur with other transactions. This is	*/
/* accomplished by returning information to the replication	*/
/* agent so that it can combine multiple updates to a record	*/
/* in one transaction into a logically equivalent set of	*/
/* updates that cannot encounter unique key conflicts with	*/
/* other transactions.						*/
/*								*/
/* Default: ctBEHAV_REPIMGRWTCMB is ON in version 11.2.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctBEHAV_REPIMGRWTCMB
#define ctBEHAV_REPIMGRWTCMB
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_REPLMINLOG modifies the replication agent's		*/
/* calculation of its minimum log requirement. If a checkpoint	*/
/* contains the minimum log requirement for recovery (set by	*/
/* ctFeatLOWBEGLOG), the agent uses that value as its minimum	*/
/* log requirement.						*/
/*								*/
/* Default: ctBEHAV_REPLMINLOG is ON in version 11.2.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctBEHAV_REPLMINLOG
#define ctBEHAV_REPLMINLOG
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_CHECK_ICU_COLLATOR_VERSION modifies our checking of	*/
/* the ICU collator version. Our intent is to ensure that we	*/
/* detect the use of an ICU library that is not compatible with	*/
/* the collator version that was used when an index was		*/
/* created. With this #define enabled, we only error out if the	*/
/* version of the collator that the ICU library provides for	*/
/* the specified locale does not match the version of the	*/
/* collator that was used when the index was created.		*/
/*								*/
/* When this #define is off, we are more restrictive: we set a	*/
/* global variable to the ICU collator version the first time	*/
/* we open a collator, and we require that global version to	*/
/* match the collator for the index, but that means that we	*/
/* would only allow one collator to be used.			*/
/*								*/
/* Default: ctBEHAV_CHECK_ICU_COLLATOR_VERSION is ON in version */
/* 11.2.0 and later.						*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctBEHAV_CHECK_ICU_COLLATOR_VERSION
#define ctBEHAV_CHECK_ICU_COLLATOR_VERSION
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_COMPACT_SCAN changes the file compact's scan of	*/
/* variable length data files to ignore the logical end of file	*/
/* header value. Instead, like the rebuild, the compact reads	*/
/* record headers until end of file is reached (as indicated by	*/
/* a header read returning error READ_ERR). If an invalid	*/
/* record header is encountered, the compact scans the data	*/
/* file for a valid record header. If it finds a valid record	*/
/* header, if the errorOnCorruptIFILoption option is specified,	*/
/* the compact returns DCPT_ERR, otherwise it marks the invalid	*/
/* space deleted and continues reading record headers.		*/
/*								*/
/* Default: ctBEHAV_COMPACT_SCAN is ON in version 11.0.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,0,0)
#ifndef NO_ctBEHAV_COMPACT_SCAN
#define ctBEHAV_COMPACT_SCAN
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_CTCLUP_LRUBUF ensures that when a node is being	*/
/* cleaned up during automatic recovery in standalone mode	*/
/* [including during dynamic dump restore (ctrdmp), rollback or	*/
/* forward roll (ctfdmp)] the buffer holding the node cannot be	*/
/* reassigned to another index node. We accomplish this by	*/
/* removing the buffer from the LRU list at the top of ctclup() */
/* and adding the buffer back to the LRU list before ctclup()	*/
/* returns.							*/
/*								*/
/* Default: ctBEHAV_CTCLUP_LRUBUF is ON in version 10.4.0 and	*/
/* later in standalone mode with transaction control enabled.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0)
#ifndef NO_ctBEHAV_CTCLUP_LRUBUF
#if defined(TRANPROC) && !defined(MULTITRD)
#define ctBEHAV_CTCLUP_LRUBUF
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_RECOVER_KEYCOUNT modifies the maintenance of index	*/
/* key counts during automatic recovery. Currently we have	*/
/* limited the changes to dump restore. Now when an index is	*/
/* reconstructed during dump restore, we set its key count to	*/
/* the number of keys we found in the leaf nodes, and we turn	*/
/* on the clean open bit on the index file so that the rollback	*/
/* to the dump restore time adjusts the key counts only for the	*/
/* successful key add and delete operations.			*/
/*								*/
/* Default: ctBEHAV_RECOVER_KEYCOUNT is ON in standalone mode.	*/
/*--------------------------------------------------------------*/
#ifndef MULTITRD
#ifndef NO_ctBEHAV_RECOVER_KEYCOUNT
#define ctBEHAV_RECOVER_KEYCOUNT
#endif
#endif

/*--------------------------------------------------------------*/
/* ctBEHAV_CTRDMP_REDIRECT modifies the way that the dynamic	*/
/* dump restore utility, ctrdmp, applies redirect rules to the	*/
/* names of the files that are being restored. The old approach	*/
/* applied the redirect rule to the name of the file from the	*/
/* transaction log first if the file was already open when it	*/
/* was being backed up. Now ctrdmp only applies the redirect	*/
/* rules to the filename in the dump script. The dump script	*/
/* option !OLD_REDIRECT can be used in the dump restore script	*/
/* if you wish to restore the previous behavior.		*/
/*								*/
/* Default: ctBEHAV_CTRDMP_REDIRECT is ON.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_CTRDMP_REDIRECT
#define ctBEHAV_CTRDMP_REDIRECT
#endif

/*----------------------------------------------------------------------------
  To simulate multi-threaded FPUTFGET locking behavior on a Windows system,
  turn on ctBEHAV_WIN32unxlok below or in ctoptn.h. Note that this simulation
  is not perfect: although c-tree will turn on the same locking behavior macros,
  the system locking routines behave differently on Unix compared to Windows:
  on Unix systems, locks are per process rather than per thread.
-----------------------------------------------------------------------------*/
#ifdef ctPortWIN32
#ifdef ctMTFPG
/* #define ctBEHAV_WIN32unxlok */
#endif
#endif

/*----------------------------------------------------------------------------
  In the multi-user multi-threaded model, ctBEHAV_MTFPG_KEEPOPEN_LOCK tracks
  locks held on a file by all connections and keeps all descriptors for the
  file open until all locks are released. This behavior is enabled on all
  operating systems whose system file lock implementation releases all locks
  on a file if any file descriptor to the file is closed. 
----------------------------------------------------------------------------*/
#if (defined(ctPortUNIX) || defined(ctBEHAV_WIN32unxlok)) && defined(ctMTFPG)
#ifndef NO_ctBEHAV_MTFPG_KEEPOPEN_LOCK
#define ctBEHAV_MTFPG_KEEPOPEN_LOCK
#endif
#endif

/* ctKeepOpenLockListAdd modes: */
#define KOLLprecreate	1	/* called before attempting to create a file */
#define KOLLpostcreate	2	/* called after successfully creating a file */
#define KOLLpreopen	3	/* called before attempting to open a file   */
#define KOLLpostopen	4	/* called after successfully opening a file  */

/*----------------------------------------------------------------------------
  In the multi-user multi-threaded model, when we are keeping file descriptors
  open in order to preserve locks, if thread safety is enabled we also enable
  ctBEHAV_MTFPG_KEEPOPEN_LOCK_MLTDSC to use a separate file descriptor for each
  open request on a file. We do this because in this situation the file create,
  open, and close calls are not atomic, so if we chose to use only one file
  descriptor per file, we'd need some additional synchronization to make these
  functions atomic.

  In this operational model, if thread safety is not enabled, the c-tree calls
  are serialized, so we default to using only one file descriptor for all opens
  of the file.
----------------------------------------------------------------------------*/
#if defined(ctBEHAV_MTFPG_KEEPOPEN_LOCK) && defined(ctMTFPGreentrant)

#ifdef NO_ctBEHAV_MTFPG_KEEPOPEN_LOCK_MLTDSC
#error Keepopen file lock with reentrant support requires using multiple file descriptors
#endif

#define ctBEHAV_MTFPG_KEEPOPEN_LOCK_MLTDSC

#endif

/*----------------------------------------------------------------------------
  In the server operational model, ctBEHAV_COMNOD_UPDFLG puts the changing of
  an index buffer's update flag to 'n' for TRNLOG index files under control
  of the commit node mutex. This change in behavior is designed to avoid an
  index buffer ending up on the commit node list with its update flag set to
  'n'.

  Enabled for v11.2.2 and later
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,2,2)
#ifndef NO_ctBEHAV_COMNOD_UPDFLG
#if defined(MULTITRD) && defined(TRANPROC)
#define ctBEHAV_COMNOD_UPDFLG
#endif
#endif
#endif

/*----------------------------------------------------------------------------
 * ctBEHAV_DYNDUMP_PROTECT_NODESPLIT prevents index node splits from 
 * re-using deleted space while the index file is being written by a
 * dynamic dump operation.  Instead, the new node will be at the end 
 * of the file. Allowing such operations could result in an 
 * index that is non-restoreable by ctrdmp.
 *----------------------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctBEHAV_DYNDUMP_PROTECT_NODESPLIT
#define ctBEHAV_DYNDUMP_PROTECT_NODESPLIT
#endif
#endif /* MULTITRD */

/*----------------------------------------------------------------------------
  ctBEHAV_AUTOTRAN_ON_CREATE causes an ISAM level file create call in the
  server to automatically begin a transaction if the files that are being
  created use transaction control. The transaction is committed (or aborted
  if the create fails) before the create call returns.

  Enabled in v11.3.1 and later for all OEMs, and enabled in v11.2.2 and later
  for DST OEM.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1) || (ctVER3_GE(11,2,2) && defined(ctPortDSTINTL))
#ifdef TRANPROC
#ifndef NO_ctBEHAV_AUTOTRAN_ON_CREATE
#define ctBEHAV_AUTOTRAN_ON_CREATE
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_NONTRAN_FILESYS_FLUSH_OFF suppresses file system flush operations for
  non-ctTRNLOG data and index files, except for explicit CTFLUSH() calls.

  Enabled in v11.5.0 and later for standalone and server compiles.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,0)
#ifndef NO_ctBEHAV_NONTRAN_FILESYS_FLUSH_OFF
#ifndef ctCLIENT
#define ctBEHAV_NONTRAN_FILESYS_FLUSH_OFF
#endif
#endif
#endif

#ifdef ctBEHAV_NONTRAN_FILESYS_FLUSH_OFF

#ifdef ctCLIENT
#error ctBEHAV_NONTRAN_FILESYS_FLUSH_OFF not supported with ctCLIENT
#endif

#endif

/*----------------------------------------------------------------------------
  ctBEHAV_RUCB_AT_COMMIT moves the calling of record update callback functions
  during a transaction commit to early on in the transaction commit so that the
  callback functions can perform transaction-controlled operations if desired.
----------------------------------------------------------------------------*/
#ifndef NO_ctBEHAV_RUCB_AT_COMMIT
#define ctBEHAV_RUCB_AT_COMMIT
#endif

/*-----------------------------------------------------------------------------
  ctBEHAV_BEGTRANorder ensures that BEGTRAN entries are written to the
  transaction log in order of increasing transaction number. We accomplished
  this by moving the assignment of the transaction number under control of
  the log buffer mutex, ctplogsema.
-----------------------------------------------------------------------------*/
#if ctVER3_GE(11,2,2) 
#ifndef NO_ctBEHAV_BEGTRANorder
#define ctBEHAV_BEGTRANorder
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_MULTIOPN_SAMUSR_TRAN_UNLOCK changes the behavior of file lock release
  requests on transaction-controlled files that have co-files and that are using
  the MULTIOPN_SAMUSR_M or MULTIOPN_SAMUSR_1 modes. When releasing a system lock
  on a file that has co-files and that is using one of these MULTIOPN modes, we
  now check if the system lock is for an offset that is updated in the current
  transaction. If so, we preserve the system lock.

  Enabled in v11.2.2 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,2,2) 
#ifndef NO_ctBEHAV_MULTIOPN_SAMUSR_TRAN_UNLOCK
#if defined(ctBEHAV_MULTIOPN_SAMUSR) && defined(TRANPROC)
#define ctBEHAV_MULTIOPN_SAMUSR_TRAN_UNLOCK
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_ADMOPEN_SUPPRESS_IFIL changes the handling of the ctADMOPEN file mode
  bit in the following ways:
  
  1) If a non-server-side function call includes ctADMOPEN in the data or index
  file mode of the IFIL structure, we turn off that bit.
  2) When writing the IFIL information to the IFIL resource in the data file,
  we turn off the ctADMOPEN bit in the data and index file mode fields.

  Enabled in v11.3.2 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,2) 
#ifndef NO_ctBEHAV_ADMOPEN_SUPPRESS_IFIL
#define ctBEHAV_ADMOPEN_SUPPRESS_IFIL
#endif
#endif



/*----------------------------------------------------------------------------
  ctBEHAV_PATH_SUPPRESS_IFIL changes the handling of the IFIL resource
  
  1) pfilnam paths are no longer stored in the IFIL resource.  
  2) GETIFIL populates pfilnam based on the name used to open the file.
  3) aidxnam can now specify "+myIndex" to expect myIndex to reside in 
  the same directory as the data file.  This slightly modifies the prior
  "+" behavior that was only supported in PRMIIDX and TMPIIDX
  4) aidxnam can now specify "?myIndex".  This is like "+" behavior, 
  but the data file name is prefixed to the index name.
  e.g. ./data/myDataFile_myIndex
 
 Enabled in v11.6 and later. 
  ----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0) 
#ifndef NO_ctBEHAV_PATH_SUPPRESS_IFIL
#define ctBEHAV_PATH_SUPPRESS_IFIL 
#endif
#endif

/* Default value for the SUPPRESS_PATH_IN_IFIL option: */
#define SUPPRESS_PATH_IN_IFIL_DEFAULT "YES"

/*----------------------------------------------------------------------------
  ctBEHAV_NOMESSAGEBOX suppresses c-tree Server's displaying of error messages
  in dialog boxes on Windows systems. We made this change because displaying an
  error message in a dialog box can cause problems when c-tree Server is run as
  a Windows service.

  Enabled for c-tree Server.
----------------------------------------------------------------------------*/
#ifdef ctSRVR
#ifndef NO_ctBEHAV_NOMESSAGEBOX
#define ctBEHAV_NOMESSAGEBOX
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_CTSORT changes the behavior of c-tree's in-memory key sorting routine
  that is used when rebuilding or adding an index.

  When this option is enabled, c-tree's quicksort algorithm uses a random pivot
  instead of the midpoint of the sort range, and it counts the number of key
  comparisons that the quicksort has performed in order to switch to using the
  heapsort algorithm if the quicksort is found to be inefficient for a
  particular data set.

  Enabled in v11.5.2 and later for all OEMs, and enabled in v11.5.1 and later
  for the CHARGER1 OEM.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,2) || (ctVER3_GE(11,5,1) && defined(ctPortCHARGER1))
#ifndef NO_ctBEHAV_CTSORT
#define ctBEHAV_CTSORT
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_FIDD_NOT_OP_FID_MBR improves the mapping of index member tfils to
  a 'not open due to file ID mismatch' state during automatic recovery in
  order to avoid an L64 recovery error when the transaction log contains
  references to two versions of an index, with the later version having
  more members than the earlier version.

  When processing a log entry during automatic recovery that requires us to
  open the file referenced in the log entry, if we find that a file by that
  name is already open with a different file ID than the file ID in the log
  entry, we map the tfil of the host and the index members to a 'not open'
  state. But the already-open index file might have more index members than
  existed at that point in the transaction log, which means a tfil that we
  are trying to set to 'not open' was not associated with that index member
  (since it didn't exist) and it might already have a valid mapping to a
  file open by recovery.
  
  Now, when transaction redo processes a file create or file open log entry,
  and transaction undo processes a file close log entry, instead of failing
  with an L64 internal error when a mapping for a tfil that we think should
  be associated with an index member already exists, we preserve the existing
  mapping and allow recovery to proceed.

  Enabled in v11.6.1 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1) || defined(ctPortABACUS) /* Activated:Jeff K:v11.6.1:190730; */
#ifndef NO_ctBEHAV_FIDD_ERR_NOT_OP_FID_MBR
#define ctBEHAV_FIDD_ERR_NOT_OP_FID_MBR
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_SPCMGT_INVALIDATE_ON_ERROR changes the behavior when an error occurs
  adding a key to or deleting a key from the space management index of a
  variable-length data file. Instead of marking the index corrupt (which marks
  the data file corrupt), we invalidate the space management index by setting
  the root pointer header fields to zero.

  Enabled in v11.6.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifndef NO_ctBEHAV_SPCMGT_INVALIDATE_ON_ERROR
#define ctBEHAV_SPCMGT_INVALIDATE_ON_ERROR
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_FLUSH_BY_FILE changes the way data and index buffers are flushed
  by file.  
----------------------------------------------------------------------------*/
#ifndef NO_ctBEHAV_FLUSH_BY_FILE
#ifdef MULTITRD
#define ctBEHAV_FLUSH_BY_FILE
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_MULTIOPN_SAMUSR_M_FREE changes record unlock behavior when using the
  SAMUSR_M mode. Now only the user lock that matches the specified file number
  is freed, and the system lock is only freed when the last corresponding user
  lock is freed.

  Off by default.
----------------------------------------------------------------------------*/
#ifndef NO_ctBEHAV_MULTIOPN_SAMUSR_M_FREE
#ifdef ctBEHAV_MULTIOPN_SAMUSR
/* #define ctBEHAV_MULTIOPN_SAMUSR_M_FREE */
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_MULTIOPN_SAMUSR_M_FREE_FILE changes behavior of the ctFREE_FILE unlock
  mode when using the SAMUSR_M mode. Now only the user locks that match the
  specified file number are freed, and a system lock is only freed when the
  last corresponding user lock is freed.

  Off by default.
----------------------------------------------------------------------------*/
#ifndef NO_ctBEHAV_MULTIOPN_SAMUSR_M_FREE_FILE
#ifdef ctBEHAV_MULTIOPN_SAMUSR
/* #define ctBEHAV_MULTIOPN_SAMUSR_M_FREE_FILE */
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_PERMMASK_INHERIT changes the inheritance of file permissions in the
  following ways:
  
  1) Permission inheritance is now calculated when reading the permissions from
     the file, so the permissions as specified are stored in the file.
  2) Inheritance occurs from world to group and from world to owner. Inheritance
     from group to owner no longer occurs, as this doesn't make sense.
  3) Inheritance to group and owner occurs even if the GPF_NONE or OPF_NONE
     permission is specified.
  4) A bitmask was corrected so that world WRITE permission is properly
     inherited by group and owner.

  Enabled from v11.7.0 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,0)
#ifndef NO_ctBEHAV_PERMMASK_INHERIT
#define ctBEHAV_PERMMASK_INHERIT
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_CHGPAGE_COMPACT permits the compact logic to reduce the page/node
  size during compact. This especially affects variable length files with
  their internal space management indices.

  Without this turned on, trying to compact a variable length data file with
  a smaller page size fails with KSIZ_ERR(40).

  Enabled in v11.8.0 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifndef NO_ctBEHAV_CHGPAGE_COMPACT
#define ctBEHAV_CHGPAGE_COMPACT
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_BACKGROUND adjusts ctaddwork() logic so callers setting flag ctWORK_SUCCESS
  may safely call into the ctree core on return, regardless of return code.


----------------------------------------------------------------------------*/
#ifndef NO_ctBEHAV_BACKGROUND
#define ctBEHAV_BACKGROUND
#endif


/*----------------------------------------------------------------------------
  ctBEHAV_CHECK_ADVENC_PASSWD 

'ctcmpcif' should ask for master key password when changing encryption setting

Added an interactive prompt to 'ctcmpcif' to check whether the master password
is correct when trying to change the encryption strategy and the advanced
encryption is enabled in the server. In order to enable this feature please
enable ctBEHAV_CHECK_ADVENC_PASSWD when compiling ctcmpcif. In case the master
password is not correct or the user is not entitled to check the master password
the compact will not be done.

Default: Not Active
----------------------------------------------------------------------------*/
#define NO_ctBEHAV_CHECK_ADVENC_PASSWD
#ifndef NO_ctBEHAV_CHECK_ADVENC_PASSWD
#define ctBEHAV_CHECK_ADVENC_PASSWD
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_USR_FILES_RESERVED
  A small pool of user file numbers are reserved for internal usage by
  new function iAVLFILNUM().  Prevents potential crash due to internal usage of
  AVLFILNUM() when an fusr pointer has been saved on the stack.

Default: Enabled for MULTITRD
----------------------------------------------------------------------------*/
#ifndef NO_ctBEHAV_USR_FILES_RESERVED
#ifdef MULTITRD
#define ctBEHAV_USR_FILES_RESERVED
#endif
#endif


#ifdef ctBEHAV_USR_FILES_RESERVED
/* 
 * The reserved files are for:
 * preimage swap file
 * IICT preimage swap file.
 */
#define ctUSR_FILES_RESERVED 2
#define ctUSR_NET_RESERVED(gv) (ctUSR_FILES_RESERVED-(gv)->usedReserve) 
#define ctUSR_ACQUIRE_RESERVED(gv,num) (gv->usedReserve+=num)
#define ctUSR_RELEASE_RESERVED(gv,num) (gv->usedReserve-=num)
#else
#define ctUSR_FILES_RESERVED 0
#define ctUSR_NET_RESERVED(x) ctUSR_FILES_RESERVED 
#define ctUSR_ACQUIRE_RESERVED(gv,num) 
#define ctUSR_RELEASE_RESERVED(gv,num)
#endif

#define USER_FILNO_NEEDS_ALLOCATION(x) ((x) >= (ctumxfil - ctUSR_NET_RESERVED(lctgv)))
#define FILNO_ALLOC_REQUEST(x) ((x) + ctUSR_NET_RESERVED(lctgv))  /* adjust specific allocation requests */

/*----------------------------------------------------------------------------
  ctBEHAV_REENTRANT_INDEXES
  If a reentrant indexing operation is detected, allocate a separate set of
  IDXSTATE variables for the nested index operation.

Default: Enabled in v11.8.0 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifndef NO_ctBEHAV_REENTRANT_INDEXES
#define ctBEHAV_REENTRANT_INDEXES
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_LOG_FILE_ID_CHANGE writes a SYSTRAN log entry to the transaction log
  when a transaction-controlled file's file ID is being changed, rather than
  calling ct_chkfil() to scan the transaction log to search for references to
  that file name and its original file ID since the most recent checkpoint.
  This avoids the performance hit that we have experienced with the log scan,
  especially when using large transaction logs.

  Default: Enabled in v11.8.0 forward and special oems when transaction control is supported.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifdef TRANPROC
#ifndef NO_ctBEHAV_LOG_FILE_ID_CHANGE
#define ctBEHAV_LOG_FILE_ID_CHANGE
#endif
#endif
#endif

#if ctVER3_GE(11,8,0) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#define LOG_FILE_ID_CHANGE_DEFAULT	"YES"
#else
#define LOG_FILE_ID_CHANGE_DEFAULT	"NO"
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_RECOVERY_RENAME_CHECK_FILE_ID enables the following changes to
  automatic recovery processing that are intended to improve detection of a
  mismatched file:

  1) For a transaction-dependent log entry, when opening the file by its renamed
  file name, if the file exists on disk with a different file id than the one
  recorded in the log entry, instead of ignoring the file id mismatch, check if
  a subsequent transaction-dependent operation explains the existence of the
  file with its current file id. If so, allow recovery to continue; if not,
  fail recovery with error FIDD_ERR.

  2) When undoing a transaction-dependent file rename, if renaming the file to
  its original name fails, fail recovery.

  Default: Enabled in v11.8.0 forward and for SS&C OEM compiles.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || defined(ctPortDSTINTL)
#ifndef NO_ctBEHAV_RECOVERY_RENAME_CHECK_FILE_ID
#define ctBEHAV_RECOVERY_RENAME_CHECK_FILE_ID
#endif
#endif

/* default value for RECOVERY_RENAME_CHECK_FILE_ID option */
#define RECOVERY_RENAME_CHECK_FILE_ID_DEFAULT "YES"

/*----------------------------------------------------------------------------
  When ctBEHAV_SET_ACTLEN_EXCLUSIVE is enabled, an index that qualifies for
  read lock acquisition during key lookup (not update) operations has its
  actlen value set when the caller has a write lock on the index buffer. The
  previous behavior allowed actlen to be set on the index buffer when the caller
  had a read lock on the buffer.

  Default: Enabled for c-tree Server in v11.8.0 forward and special v11.6.1 OEMS. Requires IDXreader
  (checked later in this header file).
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifndef NO_ctBEHAV_SET_ACTLEN_EXCLUSIVE
#ifdef ctSRVR
#define ctBEHAV_SET_ACTLEN_EXCLUSIVE
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctBEHAV_FILE_CLOSE_FLUSH enables flushing of a c-tree data or index file when
  it is about to be physically closed, but before acquiring the file open/close
  mutex. This avoids potential delays on file open and close calls that can be
  caused by writing all the updated cache pages to the file while holding the
  file open/close mutex.
 
  Default: ctBEHAV_FILE_CLOSE_FLUSH is ON for c-tree Server in
  the v11.8.0 forward and special v11.6.1. Requires ctBEHAV_FLUSH_BY_FILE.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#if defined(ctSRVR) && defined(ctBEHAV_FLUSH_BY_FILE)
#ifndef NO_ctBEHAV_FILE_CLOSE_FLUSH
#define ctBEHAV_FILE_CLOSE_FLUSH
#endif
#endif
#endif

/* default value for FILE_CLOSE_FLUSH configuration option */
#define FILE_CLOSE_FLUSH_DEFAULT "YES"

#if ctVER3_GE(11,9,5)
#ifdef ctSRVR
#ifndef NO_ctBEHAV_CLEANUP_ABLIST_ON_ABORT
/*----------------------------------------------------------------------------
  ctBEHAV_CLEANUP_ABLIST_ON_ABORT enables a transaction abort to clean up
  the abort node lists of the indexes that the transaction updated. This is
  a performance optimization. Default: ON for c-tree Server in v11.9.5 and up.
----------------------------------------------------------------------------*/
#define ctBEHAV_CLEANUP_ABLIST_ON_ABORT
#endif
#endif
#endif

/* default value for CLEANUP_ABLIST_ON_ABORT configuration option */
#define CLEANUP_ABLIST_ON_ABORT_DEFAULT "YES"

#if ctVER3_GE(11,9,0)
#ifndef NO_ctBEHAV_MASTERCIPHER
/*----------------------------------------------------------------------------
  ctBEHAV_MASTERCIPHER allows ctree to work with multiple ADVANCED ENCRYPTION
  master ciphers and log ciphers by storing additional information in the 
  security resource
----------------------------------------------------------------------------*/
#define ctBEHAV_MASTERCIPHER
#endif
#endif

#if ctVER3_GE(11,9,5)
#ifndef NO_ctBEHAV_DEFAULT_CIPHER_AES
/*----------------------------------------------------------------------------
  ctBEHAV_DEFAULT_CIPHER_AES changes the default master cipher used with 
  ADVANCED_ENCRYPTION from CIPHER_RIJ to CIPHER_AES
----------------------------------------------------------------------------*/
#ifdef ctBEHAV_MASTERCIPHER
#define ctBEHAV_DEFAULT_CIPHER_AES
#endif
#endif
#endif


#ifndef NO_ctBEHAV_DLYLOGPRG2
/*----------------------------------------------------------------------------
 ctBEHAV_DLYLOGPRG2 Modifies the transaction log archiving and purging
 to keep logs for longer in some cases.
----------------------------------------------------------------------------*/
#define ctBEHAV_DLYLOGPRG2
#endif

#ifndef NO_ctBEHAV_SUPERFILE_HOST_CLOSE_ON_ERROR
/*----------------------------------------------------------------------------
 ctBEHAV_SUPERFILE_HOST_CLOSE_ON_ERROR closes an automatically-opened superfile
 host if an error occurs during a file create or open call. This code is not
 currently enabled. It is experimental code in case we need it in the future.
----------------------------------------------------------------------------*/
/* #define ctBEHAV_SUPERFILE_HOST_CLOSE_ON_ERROR */
#ifdef TRANPROC
/* #define ctBEHAV_SUPERFILE_HOST_CLOSE_ON_ERROR_TRANPROC */
#endif
#endif

#ifndef NO_ctBEHAV_LOGONHASH_USE_SHA512
/*----------------------------------------------------------------------------
 ctBEHAV_LOGONHASH_USE_SHA512 changes those logon password hash methods that
 previously used MD5 to use SHA512 instead.
----------------------------------------------------------------------------*/
#define ctBEHAV_LOGONHASH_USE_SHA512
#endif

/* } END ctBEHAV... Options */
/*~********************************************/


/**************************/

/*
** the second release of strict serialization requires the
** basic strict serialization support and the ctBEHAV_ULCNT
** support
*/
#ifdef NO_TRANPROC
#ifdef ctSSrel2
#undef ctSSrel2
#endif
#endif

#ifdef ctSSrel2

#ifndef ctSS
#define ctSS
#endif
#ifndef ctBEHAV_ULCNT
#define ctBEHAV_ULCNT
#endif

#ifndef ctFeatTRANISO
#define ctFeatTRANISO
#endif

#endif

/**************************/

#ifndef ctTIMUL
#define ctTIMUL	5000
#endif

#ifdef ctBEHAV_BLM
#define ctrelbufx(bp,own)	ctrelbuf(NO,bp,own)
#define ctreldatx(db,own)	ctreldat(db,own,NO)
#else
#define ctrelbufx(bp,own)	ctsemclr(&bp->semaf ,own)
#define ctreldatx(db,own)	ctsemclr(&db->datsem,own)
#endif


/*^*********************************************/
/* { ctDIAG... Options (Diagnostic options) */

/*^*******************/
/* The ctDIAGFORCE_EXCEPTION SHOULD NOT BE USED */
/* This is an internal diagnostics routine that will force a core
   dump whenever the SYSCFG function is called dump in order to verify
   the W32 Exception Handler Logic. FYI, the ctstop utility will call
   SYSCFG, and therefore is typically be used to test the exception.
*/
#ifdef ctPortWIN32
/* #define ctDIAGFORCE_EXCEPTION_DO_NOT_USE */
#endif
/*~*******************/

/*^*******************/
/*
The ctDIAG_FNCMON option activate logics which will hold the last
ctDIAG_FNC_MON (defaults to 10) functions called by each user.
This allows, as an example, the ctcatend or Exception handler to dump
the last functions requested by each user. It will also cause a global
counter to be maintained for all functions, allowing the option at
ctcatend time of display the total global call count of all functions.
These options are used in conjuction with the server keyword:
DIAGNOSTICS USER_FUNCTIONS
*/
/* #define ctDIAG_FNC_MON 10 */ /* defalts to display last 10 functions per client */

/*
The ctDIAG_FNC_MON_FNAM define is used to save the file names for
every OPNRFIL function call. It will only save the last
ctDIAG_FNC_MON_FNAM number of bytes of the file name. This option is
inefficient to use (only related to memory allocated) because it
reserves the ctDIAG_FNC_MON_FNAM buffer space for every function slot
call, yet only uses it (currenlty) for OPNRFIL. If there are long
file names (i.e.: with long paths etc.) this define can be increased,
at the cost of extra global memory allocated.  It defines the number
of tailing characters in the file name to save.
Because of the memory overhead, this option is deactivated by default.
*/
/* #define ctDIAG_FNC_MON_FNAM 24 */
/*~*******************/


/*^*******************/
/*
** ctDIAGnodeERR enables logging of index node errors to the file
** LOGIXERR.FCS.
**
** DEFAULT:  ctDIAGnodeERR is NOT enabled.
*/
/*~*******************/
#ifdef ctSRVR
/* #define ctDIAGnodeERR */
#endif

/*^*******************/
/*
** ctDIAGctsrvrExit enables the use of the DIAGNOSTICS PROCESS_EXIT
** configuration option to cause the c-tree Server process to create a
** process stack trace and display a dialog box before it exits.
**
** DEFAULT:  ctDIAGctsrvrExit is enabled.
*/
/*~*******************/
#ifdef ctSRVR

#define ctDIAGctsrvrExit

/*
** Uncomment #define ctDIAGctsrvrExitDumpStack to cause the c-tree Server
** to create a process stack trace before exiting.
*/
/* #define ctDIAGctsrvrExitDumpStack */

/*
** Uncomment #define ctDIAGctsrvrExitDialogBox to cause the c-tree Server
** to display the process exit messages in Windows dialog boxes instead of
** writing the messages to the c-tree Server status log.
*/
/* #define ctDIAGctsrvrExitDialogBox */

#endif

/*^*******************/
/*
** ctDIAGdlokERR enables tracking of the last location in the code
** where a DLOK_ERR error occurred for the current connection and
** the lock owner if available.
**
** DEFAULT:  ctDIAGdlokERR is NOT enabled.
*/
/*~*******************/
#ifdef ctSRVR
/* #define ctDIAGdlokERR */
#endif

/*^*******************/
/*
** ctDIAGselectERR enables logging of diagnostic messages to
** the file ctclient.log in the current directory when a TCP/IP
** socket select() call fails. The c-tree client-side code calls
** select() when sending/receiving data when the c-tree socket
** timeout feature is enabled.
**
** DEFAULT:  ctDIAGselectERR is NOT enabled.
*/
/*~*******************/
#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB)
/* #define ctDIAGselectERR */
#endif

/*^*******************/
/*
** ctDIAGctsrvrExitCmd enables the use of the PROCESS_EXIT_COMMAND
** configuration option. This option causes the c-tree Server process to
** execute the specified command when it calls exit(). This option can be used
** to confirm whether or not the c-tree Server proces called exit() and if so
** it can be used to get a stack trace for the exit() call.
**
** DEFAULT:  ctDIAGctsrvrExitCmd is enabled for c-tree Server compiles,
** except when compiling for Windows CE and the Windows kernel.
*/
/*~*******************/
#ifdef ctSRVR
#ifndef ctPortWINCE
#ifndef ctPortWINKE
#ifndef ctPortWINIOT
#define ctDIAGctsrvrExitCmd
#endif
#endif
#endif
#endif


/* } END ctDIAG... Options */
/*~********************************************/

#ifndef ctN8
/* These features require native 8-byte integers */
#define NO_ctFeatCOPYFILE
#define NO_ctFeatTRANSACTION_ID
#define NO_ctFeatTRANSFER_FILE
#define NO_ctFeatKSEGDEFxtd
#define NO_ctFeatRTG_CTDB /* no ctdb support in COBOL driver */
#define NO_ctFeatRTG_SQL /* no sql support in COBOL driver */
#define PWH 32 /* set password hash length to 32 because only SHA-256 is supported */
#define CBPTR32 /* CBPTR data type is 32 bit */
#endif

/*^********************************************/
/* { ctFeat... Options (Feature options) */


/*^*******************/
#if ((ctVER_MAJOR > 9))
#ifndef NO_ctFeatLicense10
#define ctFeatLicense10 /* Version 10 Licenseing */
#define ctFeatLic10Filename /* logic to allow license fiel to be named ctsrvr[SN].lic */
#define ctFeatL10_Connections /* logic to count the connections */
#define ctFeatL10_SQLasISAM /* logic to allows activating ISAM only part of SQL server */
#define ctFeatL10_serno /* logic to consider the 8 digits serial number "as is" with no special meaning for the 2 digit prefix */
#ifndef ctSQLMTFPG
#define ctFeatL10_CustomMsg /* custom message specified in vendor array */
#endif
#if ctVER_GE(10,2) /* starting with 10.2 we use V3 license */
#define ctFeatL10_V3 /* V3 license, features are off by default unless explicitely turned on in the license file */
#endif /*ctVER_GE(10,2)*/
#if defined(ctSRVR) || defined(ctSQLSRVR)
#define ctFeatL10_Feature1 /* logic to limit some c-tree server features (set #1)*/
#define ctFeatL10_Feature2 /* ogic to limit some c-tree server features (set #2)*/
#endif
#if ctVER_GE(10,1)
#define ctFeatL10_handshake /* logic to handle multiple handshakes */ /* ctSIBLING_HANDSHAKE */
#endif /*ctVER_GE*/
#endif
#endif

#ifdef ctFeatL10_handshake /* ctSIBLING_HANDSHAKE */
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif
/*~*******************/


/*^*******************/
				/* the ctFeatWIN32_GFIBH option activates*/
#ifdef ctPortWIN32		/* the WIN32 specific code to use the	*/
#ifndef NO_ctFeatWIN32_GFIBH
#define ctFeatWIN32_GFIBH	/* GetFileInformationByHandle()	to	*/
#endif				/* improve unique file id detection	*/
#endif
/*~*******************/
				/* See ctocfl.c and ctinod_a.c		*/

/*^*******************/
/* We had a special request to allow a zero value to be stored within 	*/
/* an index entry (Marco's BOM customer). Activating this define will	*/
/* activate this support. This feature is not formally endorced by FairCom.*/
/* #define ctFeatZERO_RECBYT_OK */
/*~*******************/


/*^*******************/
/* The ctFeat_SYSVIEW feature activates internal logic designed to produce*/
/* status reports triggered by specific events witin the server. 	*/
/* #define ctFeat_SYSVIEW */
/*~*******************/


/*^*******************/
/* TCP/COMMUNICATION Features: */
/* #define ctFeatCAMOCOMM - FairCom proprietary comm buffer encryption	*/

#ifdef	ctUNXCOM_CRYTCP
#ifndef ctFeatENCRYPTCPIP
#define ctFeatENCRYPTCPIP
#endif
#endif

#ifdef  ctFeatENCRYPTCPIP	/* from m-tree */
#define ctFeatCAMOCOMM
#endif
/*~*******************/


/*^*******************/
/* Special OS Specfic Message Window if server was not shut down properly */
#ifndef ctPortWINKE
#ifndef ctPortWINIOT
#ifndef NO_ctFeatDIRTY_SHUTDOWN_MSG
#define ctFeatDIRTY_SHUTDOWN_MSG
#endif
#endif
#endif
/*~*******************/

/*^*******************/
/* This define will implement the use of the fdatasync function in lieu of fsync */
/* Activating this keyword will allow the COMPATIBILITY FDATASYNC */
/* #define ctFeatUSE_FDATASYNC */
/*~*******************/


/*^*******************/
/* LOW LEVEL COMMUNICATION Features */
/* #define ctFeatLOWL_CRC - FairCom low level COMM buffer CRC check
** This feature only applies if the #define is active AND the server
** configuration contains: DIAGNOSTICS  LOWL_CRC_ON
*/
#ifdef ctSRVR
/* DO not activate the CRC by default for client or communications
backward compatibility will be compromised. The user must activate this
themselves and be sure to turn on DIAGNOSTICS LOWL_CRC_ON for it to work.
*/
#ifndef ctFeatLOWL_CRC
#ifdef ctFeatCTSRVR_COMMP
#define ctFeatLOWL_CRC
#endif
#endif

/* The crc check feature was deactivated for OS2 because of an unresolved
revobj, being included in ntree/sockets/ctnlib.c which needs to be a
NPrevobj. This will be adjusted in next release.
*/
#ifdef ctPortOS2
#undef ctFeatLOWL_CRC
#endif

#ifdef ctPortMAC
#undef ctFeatLOWL_CRC
#endif

#ifdef ctPortWINCE_SRVR
#undef ctFeatLOWL_CRC
#endif

#endif	/* ctSRVR  */
/*~*******************/


/*^*******************/
#ifdef ctHUGEFILE
#ifndef ctFeatLOWL_CRC
/*
** Add a sum check to the comm control block info. More efficient than CRC,
** but less comprehensive.
*/
#define ctFeatCOMM_SUMCHK
#endif
#endif
/*~*******************/

#ifndef ctDEFAULT_PAGE_SIZE
#if ctVER3_GE(11,9,5)
/* default database page size */
#define ctDEFAULT_PAGE_SIZE 32768
#else
/* default database page size */
#define ctDEFAULT_PAGE_SIZE 8192
#endif
#endif

/* default database sector size */
#define ctDEFAULT_SECTOR_SIZE (ctDEFAULT_PAGE_SIZE / 128)

/*^*******************/
/*
** Permit a maximum PAGE_SIZE of 65536. Without ctFeatPAG64K, the
** maximum PAGE_SIZE is 32768.
*/

#define ctFeatPAG64K


/*^*******************/
/*
** Enforce small PAGE_SIZEs of 512 or 256 bytes
*/

/*
** default for ctfnz in case of small page size
*/
#define MAX_NAMEsmallpage	128

#ifdef ctFeatPAG512

#ifdef ctFeatPAG256
**** mutually exclusive ****
#endif

#define ctSMLPAGdef
#ifdef ctHUGEFILE
#define DFL_ID_LENsmallpage	32
#undef  MAX_NAMEsmallpage
#define	MAX_NAMEsmallpage	64
#else
/* nonHUGE supports 512 without any changes to core definitions */
#endif
#endif

#ifdef ctFeatPAG256
#define ctSMLPAGdef
#define DFL_ID_LENsmallpage	15
#undef  MAX_NAMEsmallpage
#define MAX_NAMEsmallpage	48
#define IDZsmallpage		16
#endif
/*~*******************/


/*^*******************/
/* #define ctFeatCRIPPLE */ /* Internal define used by FairCom for Evaluation Editions */
/*~*******************/

#ifdef CTBOUND
#ifndef MULTITRD
#define ctFeatCLRCHK
#endif
#endif


/*^*******************/
/*
** LANGUAGE Feature. Activates text translation logic for non-ENGLISH output.
*/
/* #define ctFeatLANGUAGE */
/*~*******************/


/*^*******************/
/*
** ctFeatUSER_SIGNAL_READY - Support for user defined functions (server SDK)
** ctFeatUSER_SIGNAL_DOWN - Support for user defined functions (server SDK)
*/
/* #define ctFeatUSER_SIGNAL_READY */
/* #define ctFeatUSER_SIGNAL_DOWN */
/*~*******************/


/*^*******************/
/*
** STARTUP_LOGON_BLOCK Feature. Prevents logins when the server starts up.
*/
#ifdef ctSRVR
#ifndef ctFeatSTARTUP_LOGON_BLOCK
#define ctFeatSTARTUP_LOGON_BLOCK
#endif
#endif
/*~*******************/

/*^*******************/
/*
   ctFeatCOMM_IO_BLOCK Feature. Ability to set a global variable (ctcomioblk)
   to stop all COMM I/O. When this variable is TRUE all c-tree client calls
   are returned with a CIOB_ERR(765) error.
*/
#ifdef ctSRVR
#define ctFeatCOMM_IO_BLOCK
#endif
/*~*******************/


/*^*******************/
/* This define will include all code used for QA FOLLOW THRU */
#define ctFeat_QA_FOLLOW_THRU
/*~*******************/

/*^*******************/
/*
** ctFeatSrvTimer adds time profiles split between message receives (server
** waiting for a client request), server work (performing requested action),
** and message sends (response to client).
**
** The timing is done with a call to the macro ctrt_clock() which defaults
** to clock(). It is assumed that the routine returns an increasing measure
** of time based on CPU ticks or some other small time increment.
**
** ctFeatSrvTimer is only valid for the ctree server model.
**
** If ctFeatSNAPSHOT is also defined, then this feature depends on enabling
** by a DIAGNOSTICS SNAPSHOT_WORKTIME entry or an appropriate call to
** ctSNAPSHOT(). Also, a high resolution timer is used, and the
** ctrt_hrtimer macro replaces the ctrt_clock macro.
**
** DEFAULT:  ctFeatSrvTimer is NOT activated
*/
/*~*******************/
#if (defined(ctPortTLT) || defined(ctPortHCL))
#ifdef ctSRVR
#ifdef _DEBUG
#define ctFeatSrvTimer
/*#define ctMEMFILEdbg*/
#endif
#endif
#endif

#ifndef ctSRVR
#ifdef ctFeatSrvTimer
#undef ctFeatSrvTimer
#endif
#endif

#ifndef ctPortWINCE_SRVR
#ifndef ctrt_clock
#define ctrt_clock	clock
#endif
#endif


/*^*******************/
#ifndef ctrt_hrtimer

#ifdef ctPortHPUX11
#define ctrt_hrtimer(t)		t = gethrtime()
#define ctrt_hrtimbas(t)	t = 1000000000
#endif

#ifdef ctPortSOLARIS
#define ctrt_hrtimer(t)		t = gethrtime()
#define ctrt_hrtimbas(t)	t = 1000000000
#endif

#ifdef ctPortSOL386
#define ctrt_hrtimer(t)		t = gethrtime()
#define ctrt_hrtimbas(t)	t = 1000000000
#endif

#ifdef ctPortRS6000
#define ctrt_hrtimer(t)		t = aixhrtime()
#define ctrt_hrtimbas(t)	t = aixtimbas()
#endif

#ifdef ctPortMACOSX
#define ctrt_hrtimer(t)		t = mach_absolute_time()
#define ctrt_hrtimbas(t)	t = osxtimbas()
#endif

#ifdef ctPortWIN32
#ifdef ctPortWINKE
/* WINKE_TODO */
#define ctrt_hrtimer(t)		{LARGE_INTEGER i64; i64 = KeQueryPerformanceCounter(NULL); t = i64.QuadPart;}
#define ctrt_hrtimbas(t)	KeQueryPerformanceCounter((LARGE_INTEGER *) &t)
#else
#define ctrt_hrtimer(t)		QueryPerformanceCounter((LARGE_INTEGER *) &t)
#define ctrt_hrtimbas(t)	QueryPerformanceFrequency((LARGE_INTEGER *) &t)
#endif
#endif

#ifdef ctPortLINUX
#define ctrt_hrtimer(t)		{struct timeval v; gettimeofday(&v, NULL); t = v.tv_usec + ((LONG8)v.tv_sec*1000000);}
#define ctrt_hrtimbas(t)	t = 1000000
#endif

#ifdef ctPortSCO386
#ifdef ctN8
#define ctrt_hrtimer(t)		{struct timeval v; gettimeofday(&v, NULL); t = v.tv_usec + ((LONG8)v.tv_sec*1000000);}
#define ctrt_hrtimbas(t)	t = 1000000
#else
/* no native 64-bit int support, so our "high resolution" timer only has a 1-sec resolution for now */
#define ctrt_hrtimer(t)		{struct timeval v; gettimeofday(&v, NULL); t[ctHIG32] = 0; t[ctLOW32] = v.tv_sec;}
#define ctrt_hrtimbas(t)	{t[ctHIG32] = 0; t[ctLOW32] = 1;}
#endif
#endif

#ifdef ctPortQNXRTP
#define ctrt_hrtimer(t)		{struct timeval v; gettimeofday(&v, NULL); t = v.tv_usec + ((LONG8)v.tv_sec*1000000);}
#define ctrt_hrtimbas(t)	t = 1000000
#endif


#ifndef ctrt_hrtimer 		/* default settings - not yet implemented */
#define ctrt_hrtimer(t)		/**/
#define ctrt_hrtimbas(t)	/**/
#define NO_ctFeatSNAPSHOTtimer
#define NO_ctFeatBACKGROUNDflush
#endif

#endif /* ~ctrt_hrtimer */
/*~*******************/

/*^*******************/

#ifdef ctSRVR

/*
** Indicate here which platforms support getting and setting CPU affinity.
*/

#ifdef ctPortWIN32
#ifndef ctPortWINKE
#ifndef ctPortWINCE
#ifndef ctPortWINIOT
#define ctGET_CPU_AFFINITY_SUPPORTED
#define ctSET_CPU_AFFINITY_SUPPORTED
#endif
#endif
#endif
#endif

#ifdef ctPortSOLARIS
#define ctGET_CPU_AFFINITY_SUPPORTED
#define ctSET_CPU_AFFINITY_SUPPORTED
#endif

#ifdef ctPortRS6000
#define ctGET_CPU_AFFINITY_SUPPORTED
#endif

#endif /* ctSRVR */

/*~*******************/

#ifdef ctPortWINKE
#ifndef NO_ctBEHAV_MINSTACK
#define ctBEHAV_MINSTACK 	/* alloc large items instead of using stack */
#endif
#endif

/*^*******************/
/*
** ctFeatSrvLock adds lock counters for header requests, header blocks, and
** lock denials. Also a complete set of counters is maintained for each logon
** session. The output is reported in CTSTATUS.FCS.
**
** ctFeatSrvLock is only valid for the ctree server model.
**
** DEFAULT:  ctFeatSrvLock is NOT activated
*/
/*~*******************/
#if (defined(ctPortTLT) || defined(ctPortHCL))
#ifdef ctSRVR
#ifdef _DEBUG
#define ctFeatSrvLock
#endif
#endif
#endif

#if !defined(ctSRVR) && !defined(ctBNSDRVR)
#ifdef ctFeatSrvLock
#undef ctFeatSrvLock
#endif
#endif

/*^*******************/
/*
** ctFeatINC_ADDREC Feature. Changes behavior in ctism2.c for addikey81.
*/
/* #define ctFeatINC_ADDREC */ /* uneven node splitting during record addition*/
/*~*******************/

/*^*******************/
/*
** ctFeatSrvLockFile adds lock counters per ctFeatSrvLock, but on a file
** by file basis. The file specific counters are output with ctLOKDMP.
**
** ctFeatSrvLockFile is only valid if ctFeatSrvLock is enabled.
**
** DEFAULT:  ctFeatSrvLockFile is NOT activated
*/
/*~*******************/
#if (defined(ctPortTLT) || defined(ctPortHCL))
#ifdef ctSRVR
#ifdef _DEBUG
#define ctFeatSrvLockFile
#endif
#endif
#endif

#ifndef ctFeatSrvLock
#ifdef ctFeatSrvLockFile
#undef ctFeatSrvLockFile
#endif
#endif


/*^*******************/
/*
** ctFeatCTDB - used to control ctree depenancies to the CTDB Layer.
** Initially introduced when we added Partition Rules where a few
** ctdb function were used.
**
** NOTE: there is an important reference to ctFeatCTDB earlier in this header.
*/
/*~*******************/
/*
** #define ctFeatCTDB
*/


/*^*******************/
/*
** ctFeatIopFile adds I/O performance stats on a per file basis
** The file specific counters are output with ctLOKDMP.
**
** DEFAULT:  ctFeatIopFile is NOT activated
*/
/*~*******************/
/*
** #define ctFeatIopFile
*/

/*^*******************/
/* The ctFeat8K_LOGIO option causes the defines in cttran.h to be adjusted */
/* to use 8K log blocks. This was added by Jeff and Bill for ACI/VISA */
/* See settings in cttran.h for more information. */

#ifdef ctSRVR
#ifndef ctFeat8K_LOGIO
#define ctFeat8K_LOGIO 	/* activate by default */
#endif
#endif
/*~*******************/

/*^*******************/
/*
** ctFeatREADSHARE permits a file to be opened in SHARED mode
** while only granting read permission to the opener. This
** permits other users to open the file in SHARED mode. Without
** this behavior, a READFIL open was required which in turn
** blocks other SHARED open requests.
**
** With ctFeatREADSHARE activated, a SHARED open request with
** read only permission is achieved by setting both the ctSHARED
** and ctREADFIL bits on in the file mode.
**
** DEFAULT:  ctFeatREADSHARE is activated for MULTITRD
*/
/*~*******************/
#ifdef MULTITRD
#ifndef NO_ctFeatREADSHARE
#define ctFeatREADSHARE
#endif
#else
#ifdef ctFeatREADSHARE
#undef ctFeatREADSHARE
#endif
#endif

/*^*******************/

/*~*******************/
#ifdef ctHUGEFILE
#ifndef NO_ctFeatSPLCACHE
#define ctFeatSPLCACHE
#endif
#else
#ifdef ctFeatSPLCACHE
#undef ctFeatSPLCACHE
#endif
#endif
/*^*******************/

/*~*******************/
#ifdef ctHUGEFILE
#ifdef MULTITRD
#ifdef CTS_ISAM
#ifndef NO_ctFeatPRICACHE
#define ctFeatPRICACHE
#endif
#endif
#endif
#endif
#ifndef ctHUGEFILE
#ifdef ctFeatPRICACHE
#undef ctFeatPRICACHE
#endif
#endif
#ifndef MULTITRD
#ifdef ctFeatPRICACHE
#undef ctFeatPRICACHE
#endif
#endif
#ifndef CTS_ISAM
#ifdef ctFeatPRICACHE
#undef ctFeatPRICACHE
#endif
#endif
/*^*******************/

/*~*******************/
#ifdef ctHUGEFILE
#ifndef NO_ctFeatNO_CACHE
#define ctFeatNO_CACHE
#endif
#else
#ifdef ctFeatNO_CACHE
#undef ctFeatNO_CACHE
#endif
#endif
/*^*******************/

/*~*******************/
#if defined(ctHUGEFILE) && defined(MULTITRD) && !defined(NO_ctFeatKEEPOPEN)
#define ctFeatKEEPOPEN
#else
#ifdef ctFeatKEEPOPEN
#undef ctFeatKEEPOPEN
#endif
#endif
/*^*******************/

/*~*******************/
/*
** ctFeatSCANCACHE permits an application to place a specified
** data file in "scan" mode in order to modify the data cache page
** LRU algorithm. Ordinarily, a LRU scheme is used to determine the
** next available cache page. In instances where an application does
** not want to populate the cache with the contents of a data file as it
** is processed, a call to PUTHDR(datno,YES,ctSCANCACHEhdr) places datno,
** for the calling user only, in scan mode and only two cache pages are
** used to mediate between the OS file system and the read request. If
** a (portion of a) data record is already in cache, then a scanner will
** still use this existing cache page even though it is not one of the two
** scanner dedicated pages.
**
** The objective is to keep the cache from being populated with data
** that the application knows is not likely to be revisited.
**
** At this time, ctFeatSCANCACHE requires MULTITRD. Independent of
** MULTITRD, ctFeatSCANCACHE requires ctFeatSPLCACHE support.
**
** DEFAULT:  ctFeatSCANCACHE is activated
*/

#ifdef ctHUGEFILE
#ifdef MULTITRD
#ifdef ctFeatSPLCACHE
#ifndef NO_ctFeatSCANCACHE
#define ctFeatSCANCACHE
#endif
#endif
#endif
#endif

/* check for required support */
#ifndef ctHUGEFILE
#ifdef ctFeatSCANCACHE
#undef ctFeatSCANCACHE
#endif
#endif
#ifndef MULTITRD
#ifdef ctFeatSCANCACHE
#undef ctFeatSCANCACHE
#endif
#endif
#ifndef ctFeatSPLCACHE
#ifdef ctFeatSCANCACHE
#undef ctFeatSCANCACHE
#endif
#endif
/*^*******************/

/*~*******************/
#ifdef ctHUGEFILE
#ifndef NO_ctFeatNO_FLUSH
#ifdef ctBEHAV_BLM
#define ctFeatNO_FLUSH
#endif
#endif
#else
#ifdef ctFeatNO_FLUSH
#undef ctFeatNO_FLUSH
#endif
#endif

#ifdef ctBEHAV_NO_FLUSHDEL
#ifndef ctFeatNO_FLUSH
#undef ctBEHAV_NO_FLUSHDEL
#endif
#endif
/*^*******************/

/*^*******************/
/*
** ctFeatFPGCACHE supports data file caching under FPUTFGET
** when the data file is opened ctEXCLUSIVE. INTISAMX or
** INTREEX must be used to explicitly specify the number of
** data cache pages. (If FPUTFGET is not defined, then INTREE
** and INTSAM default the number of data cache pages to be the
** same as the number of index buffer pages.)
**
** DEFAULT:  ctFeatFPGCACHE is activated for FPUTFGET
*/
/*~*******************/
#ifdef FPUTFGET
#ifndef NO_ctFeatFPGCACHE
#define ctFeatFPGCACHE
#endif
#else
#ifdef ctFeatFPGCACHE
#undef ctFeatFPGCACHE
#endif
#endif

/*^*******************/
/*
** ctFeatDATFLT supports data file filtering on record reads.
** Data file filtering permits record retrieval satisfying
** specified conditions through our expresion evaluation or
** user defined callbacks.
**
** DEFAULT:  ctFeatDATFLT is activated with ctCONDIDX
*/
/*~*******************/
#ifdef ctCONDIDX
#ifndef NO_ctFeatDATFLT
#define ctFeatDATFLT
#endif
#else
#ifdef ctFeatDATFLT
#undef ctFeatDATFLT
#endif
#endif

/*^*******************/
/*
** ctFeatDATFLTsecurity supports row level security through
** data filters. Requires ctFeatDATFLT and ctSRVR.
**
** DEFAULT:  ctFeatDATFLTsecurity is activated for
** c-tree Servers with data filter support enabled
*/
/*~*******************/
#ifdef ctFeatDATFLT
#ifdef ctSRVR
#ifdef RESOURCE
#ifndef NO_ctFeatDATFLTsecurity
#define ctFeatDATFLTsecurity
#endif
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatDEP_RENAME supports TRANDEP rename operations. If
** on, a TRANDEP file must be renamed withh an active transaction.
** Without this feature, renames cannot be performed within an
** active transaction.
**
** DEFAULT:  ctFeatDEP_RENAME is activated for ctHUGEFILE
*/
/*~*******************/
#ifdef ctHUGEFILE
#ifndef NO_ctFeatDEP_RENAME
#define ctFeatDEP_RENAME
#endif
#else
#ifdef ctFeatDEP_RENAME
#undef ctFeatDEP_RENAME
#endif
#endif

/*^*******************/
/*
** ctFeatSET_CORE_SIZE sets the soft limit on the core file size for
** the c-tree Server process to the current hard limit value.
**
** DEFAULT:  ctFeatSET_CORE_SIZE is NOT activated
*/
/*~*******************/
/*
** #define ctFeatSET_CORE_SIZE
*/

/*--------------------------------------------------------------*/
/* ctFeat6BT enables 6-byte transaction numbers. Control	*/
/* ctFeat6BT in ctopt1.h.					*/
/*--------------------------------------------------------------*/
#ifndef ctHUGEFILE
#ifdef ctFeat6BT
#ifdef ctSRVR
ctFeat6BT requires ctHUGEFILE support /* Force Compile Error */
#else
#undef ctFeat6BT /* ctFeat6BT requires ctHUGEFILE support */
#undef ctTEST6BT /* ctTEST6BT requires ctFeat6BT support */
#endif
#endif
#endif

#ifdef ctFeat6BT
/*
** check for unsupported controls
*/
#ifdef DBGbufage
	???? not supported yet ????
#endif
#ifdef dbgHGHTRN
	???? not supported yet ????
#endif

#else /* ~ctFeat6BT */

#ifdef ctTEST6BT
#undef ctTEST6BT /* ctTEST6BT requires ctFeat6BT */
#endif

#endif /* ~ctFeat6BT */

/*^*******************/
/*
** ctFeatXTDCMP supports key compression amounts in excess of 255
** by using a key length dependent "compression factor" to store values
** greater than 255 in one byte by forcing the compression amount to
** be a multiplier of the compression factor.
**
** This feature requires ctHUGEFILE support because the index file must
** use an extended header.
**
** DEFAULT:  ctFeatXTDCMP is activated
*/
/*~*******************/

#ifndef NO_ctFeatXTDCMP
#define ctFeatXTDCMP
#ifndef ctHUGEFILE
#ifdef  ctFeatXTDCMP
#undef  ctFeatXTDCMP
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatCHANNELS supports more flexible I/O channel configurations.
** When ctFeatCHANNELS is turned on,
**
**	SET_FILE_CHANNELS <filename>#<nbr of channels>
**
** may be placed in the configuration file for each file you wish to
** specify the number of I/O channels regardless of whether or not
** DUPCHANEL is part of the file. Also,
**
**	DEFAULT_CHANNELS <nbr of channels>
**
** may be used to change the default number of I/O channels used when
** DUPCHANEL is in the file mode.
**
** DEFAULT:  ctFeatCHANNELS is activated
*/
/*~*******************/
#ifndef NO_ctFeatCHANNELS
#define ctFeatCHANNELS
#endif


/* CHANNELS requires MULTITRD and ctFLEXFILE */
#ifdef ctFeatCHANNELS
#ifndef MULTITRD
#undef ctFeatCHANNELS
#else
#ifndef ctFLEXFILE
#undef ctFeatCHANNELS
#endif
#endif
#endif

/* CHANNELS requires native threading */
#ifdef ctFeatCHANNELS
#ifndef ctPortNATIVE_THREADS
#undef ctFeatCHANNELS
#endif
#endif

#ifdef ctCACHE_MEMORY
#ifdef ctFeatCHANNELS
#define ctALGNCHNL	/*
			** align channel semaphores. this could be made
			** optional when ctCACHE_MEMORY and ctFeatCHANNELS
			** are defined, but it requires both of these
			** compile-time options to be valid.
			*/
#endif
#endif


/*^*******************/
/*
** ctMXLOGS supports simultaneous, multiple log sets. Individual
** resources, including checkpoint threads, mutexes and state variables,
** are avaiable for each log channel. A transaction can only operate on
** one log set. A client thread can operate only different log sets, but
** only one log set within a given transaction.
**
** ctMXLOGS requires:	TRANPROC   / MULTITRD / ctFeat6BT / ctBEHAV_BLM /
**			ctFLEXFILE / ctCACHE_MEMORY
**
** ctMXLOGS should be defined to be the maximum number of log sets desired.
** Typical values might be 2 or 4.
**
** Coding note:
**   variables/fields with trnlst in the name are one based. (1 to ctMXLOGS    )
**   variables/fields with logset in the name are zero based (0 to ctMXLOGS - 1)
**   i.e., trnlst == logset + 1
**
** DEFAULT:  ctMXLOGS defaults off
*/
/*~*******************/

#ifdef ctMXLOGS
#ifndef TRANPROC
#undef ctMXLOGS
#endif
#endif

#ifdef ctMXLOGS
#ifndef ctFeat6BT
#undef ctMXLOGS
#endif
#endif

#ifdef ctMXLOGS
#ifdef MULTITRD
#ifndef ctBEHAV_BLM
#undef ctMXLOGS
#endif
#endif
#endif

#ifdef ctMXLOGS
#ifndef ctFLEXFILE
#undef ctMXLOGS
#endif
#endif

#ifdef ctMXLOGS
#ifdef MULTITRD
#ifndef ctCACHE_MEMORY
#undef ctMXLOGS
#endif
#endif
#endif



/*^*******************/
/*
** ctFeatSNAPSHOT supports performance monitoring snap shots of the server.
** When ctFeatSNAPSHOT is turned on, a client may retieve a snap shop, and/or
** an automatic snap shot thread can store snap shots in the SYSLOG files.
**
** DEFAULT:  ctFeatSNAPSHOT is activated for servers that support 8-byte
** integers. Without a high-resolution timer, some aspects of the snapshot
** are not available (and ctFeatSNAPSHOTtimer is turned off).
*/
/*~*******************/

#ifndef NO_ctFeatSNAPSHOT
#define ctFeatSNAPSHOT
#ifdef ctrt_hrtimer
#ifndef NO_ctFeatSNAPSHOTtimer
#define ctFeatSNAPSHOTtimer
#endif
#endif
#endif

/* Snapshots require a server with 8-byte integers and HUGEFILE support */
#ifdef ctFeatSNAPSHOT
#ifndef ctSRVR
#undef ctFeatSNAPSHOT
#else
#ifndef ctHUGEFILE
#undef ctFeatSNAPSHOT
#else
#ifndef ctN8
#undef ctFeatSNAPSHOT
#endif
#endif
#endif
#endif


#ifdef ctFeatSNAPSHOT

/*
** turn on file stats support
*/
#ifndef ctFeatIopFile
#define ctFeatIopFile
#endif
#ifndef ctFeatSrvLock
#define ctFeatSrvLock
#endif
#ifndef ctFeatSrvLockFile
#define ctFeatSrvLockFile
#endif
#ifndef ctFeatSrvTimer
#define ctFeatSrvTimer
#endif

#else  /* ~ctFeatSNAPSHOT */

#ifdef ctFeatSNAPSHOTtimer
#undef ctFeatSNAPSHOTtimer
#endif

#endif /* ~ctFeatSNAPSHOT */

#define ctSNAPSHOTsrvr		1024

/*^*******************/
/*
** ctFeatMEMFILE supports data and index files that reside entirely in memory
** and never go to disk. The data files may be non-transaction or
** or ctPREIMG. Associated ISAM indices may be memory resident, or they
** may be temporary files that are deleted upon physical (i.e.,
** last user to) close.
**
** The ctMEMFILE file mode is or'ed into x8mode of the file's XCREblk
** to specify a memory file.
**
** The maximum allowed size for the file must be specified in the mxfilzlw
** and mxfilzhw members of the XCREblk structure.
**
** Mirrored, partitioned and segmented memory files are not supported.
** Memory files are not supported for FPUTFGET
**
** DEFAULT:  ctFeatMEMFILE is activated
*/
/*~*******************/

#ifndef NO_ctFeatMEMFILE
#define ctFeatMEMFILE
#endif

/* ctMEMFILE requires ctHUGEFILE and ~FPUTFGET */
#ifdef ctFeatMEMFILE
#ifndef ctHUGEFILE
#undef ctFeatMEMFILE
#else
#ifdef FPUTFGET
#undef ctFeatMEMFILE
#endif
#endif
#endif

/*^*******************/
/*
** ctFeatPSTACK enables the c-tree Server to write call stacks for all
** server threads to the file pstack<server_pid>.log in the event of
** a fatal server error.
**
** DEFAULT:  ctFeatPSTACK is activated for Unix and Windows systems.
*/
/*~*******************/

#ifdef ctSRVR

#ifdef ctPortUNIX
#define ctFeatPSTACK
#endif

#ifdef ctPortWIN32
#ifndef ctPortWINKE
#ifndef ctPortWINCE_SRVR
#ifndef ctPortWINIOT
#define ctFeatPSTACK
#endif
#endif
#endif
#endif



#endif /* ctSRVR */

/*^*******************/
/*
** ctFeatW32_MUTXCS changes the synchronization object used to implement
** mutex support on Win32 from a mutex object to a critical section object.
** Using this feature could enhance performance.
**
** DEFAULT:  ctFeatW32_MUTXCS is NOT activated.
*/
/*~*******************/

#ifdef ctPortWIN32
#ifdef MULTITRD
/*
Note: Activate this #define in msc.w32\ctcmpl.h.
#define ctFeatW32_MUTXCS
*/
#endif
#endif

/*^*******************/
/*
** ctFeatLOGTEMPLATE attempts to use preformed transaction logs, templates,
** to avoid bottlenecks while log files are extened.
**
** Requires V8 and ctHUGEFILE and MULTITRD
**
** DEFAULT:  ctFeatLOGTEMPLATE is activated.
*/
/*~*******************/

#ifndef NO_ctFeatLOGTEMPLATE
#ifdef ctHUGEFILE
#ifdef MULTITRD
#ifdef TRANPROC
#ifndef ctPortWINKE
#ifndef ctPortWINCE_SRVR
#define ctFeatLOGTEMPLATE
#define ctLOGtemplate	0x53464653
#define ctLOGclone	0x52474752
#endif
#endif
#endif
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatEXIT_CALLBACK enables the ability for an application to set a
** callback function to be executed when c-tree calls ctrt_exit(). The
** new API function ctSETEXITFNC() is used to set the callback function
** pointer.
**
** DEFAULT:  ctFeatEXIT_CALLBACK is NOT activated.
*/
/*~*******************/
/* #define ctFeatEXIT_CALLBACK */

/*^*******************/
/*
** ctFeatBlockingRead enables blocking read support through the c-tree API
** function BLKIREC. A blocking read permits an application to attempt a
** read, and if no records satisfy the read request, go to sleep until
** such a record exists or the block times out.
**
** DEFAULT:  ctFeatBlockingRead is activated.
*/
/*~*******************/

#ifndef NO_ctFeatBlockingRead
#ifdef CTS_ISAM
#define ctFeatBlockingRead
#endif
#endif

/*^*******************/
/*
** ctFeatFNCMEMSTATS enables tracking of memory allocation and free
** operations by client for each c-tree function.
**
** DEFAULT:  ctFeatFNCMEMSTATS is NOT activated.
*/
/*~*******************/

#ifdef ctSRVR
/*
#define ctFeatFNCMEMSTATS
#define ctfuncmemNET(x) if(x.alcbyt - x.frebyt > x.netbyt) x.netbyt = x.alcbyt - x.frebyt;
*/
#endif

/*^*******************/
/*
** ctFeatSQLMUTEX enables the use of a mutex rather than a timed semaphore
** for SQL mutex operations (os_acquire_mutex_lock/os_release_mutex_lock).
** A mutex is expected to be more efficient and is sufficient if these
** functions are always called with an infinite wait.
**
** DEFAULT:  ctFeatSQLMUTEX is activated for c-treeACE SQL Server compiles.
*/
/*~*******************/

#ifdef ctSQLSRVR
#define ctFeatSQLMUTEX
#endif

/*^*******************/
/*
** ctBNDentryPoint enables the routing of c-tree API calls to a common
** entry point function.
**
** DEFAULT:  ctBNDentryPoint is activated only for c-tree Server DLL compile.
*/
/*~*******************/

#ifdef ctFeatSRVDLL
#define ctBNDentryPoint
#define ctBNDentryPointMutex
#endif

/*^*******************/
/*
** ctFeatREPLICAT enables the c-tree replication API.
**
** DEFAULT:  ctFeatREPLICAT is enabled only when
** ct_V90_GENERATION is defined.
*/
/*~*******************/

#ifdef ct_V90_GENERATION
#ifndef NO_ctFeatREPLICAT
#define ctFeatREPLICAT
#endif
#endif

#if defined(ctLOCLIB) && !defined(ctCLISIDE)
#undef ctFeatREPLICAT
#endif

#ifdef ctMTFPG
#undef ctFeatREPLICAT
#endif

#ifndef TRANPROC
#undef ctFeatREPLICAT
#endif

#ifdef ctFeatREPLICAT
#ifndef ct_V90_GENERATION

**** cannot compile replication or extended log support without
**** ct_V90_GENERATION

#endif
#endif

#ifdef  ctFeatREPLICAT
#define ctXTDLOG	/* Enable extended log support		*/
#define ctFeatLOGREAD	/* Support read-only open of tran logs	*/
#endif

#if defined(ctFeatREPLICAT) && !defined(ctBEHAV_DLYLOGPRG)
#ifdef NO_ctBEHAV_DLYLOGPRG
#error ctBEHAV_DLYLOGPRG required by ctFeatREPLICAT to adjust logtrn_lst after recovery
#else
#define ctBEHAV_DLYLOGPRG
#endif
#endif

/*^*******************/
/*
** ctFeatREPLICAT_FLAGS enables the setting of status flags in
** replication change messages.
**
** DEFAULT:  ctFeatREPLICAT_FLAGS is activated
*/
/*~*******************/

#define ctFeatREPLICAT_FLAGS

/*^*******************/
/*
** ctFeatPRESYNC_TRNLST enables checkpoint data & index file sync before
** vulnerable transaction lists are completely determined.
**
** COMPATIBILITY PRESYNC_TRAN_LIST is required to use this feature. This
** feature only applies to server implementations.
**
** DEFAULT:  ctFeatPRESYNC_TRNLST is activated
*/
/*~*******************/

#ifndef NO_ctFeatPRESYNC_TRNLST
#ifdef ctSRVR
#define ctFeatPRESYNC_TRNLST
#endif
#endif

#ifdef ctFeatPRESYNC_TRNLST
#ifndef ctSRVR
#undef ctFeatPRESYNC_TRNLST
#endif
#endif

#ifndef ctPRESYNC_LIMIT
#define ctPRESYNC_LIMIT	(-1)	/* turn off pre-filesync vulnerable tran list */
#endif

#ifdef ctFeatPRESYNC_TRNLST
#ifndef ctWORKMON
#define ctWORKMON		/* ctactusr used for threshold test */
#endif
#endif


/*^*******************/
/*
** ctFeatMASKEDPASSWORDINPUT enables the ability to read passwords
** without echoing the characters entered by the user.
**
** DEFAULT:  ctFeatMASKEDPASSWORDINPUT is activated
*/
/*~*******************/
#if !defined(ctPortWINCE) && !defined(ctPortWINIOT)
#define ctFeatMASKEDPASSWORDINPUT
#endif


/*^*******************/
/*
** ctFeatION enables low level I/O calls to carry a unique location code [or
** I/O number, hence ION] useful in monitors and/or debugging output.
**
** Assume in the following that the I/O number is reported as "wxyz".
** Codes from 1000 to 1399, and 1900 to 1999 should be searched for by
** locating the macro ION(wxyz).
**
** Codes from 1400 to 1899 should be searched for by locating the macro
** ION(wxy0).
**
** Codes from 2000 to 2999 should be searched for by locating the macro
** ION(wx00  WITHOUT THE CLOSING PARENTHESIS.
**
** Codes above 9999 of the form "vwxyz" shold first be reduced modulo 10000,
** i.e., as wxyz.  Then use the above rules to decode wxyz. The multiple of
** 10000 is added in recusive calls to ctsysio81().
**
** DEFAULT:  ctFeatION is NOT activated
*/
/*~*******************/
/* #define ctFeatION */

/*^*******************/
/*
** ctFeatSHUTDOWN_DIAG enables the DIAGNOSTICS SHUTDOWN_COMM keyword, which
** causes the c-tree Server to log messages showing the operations
** performed at server shutdown to disconnect client connections.
**
** DEFAULT:  ctFeatSHUTDOWN_DIAG is activated
*/
/*~*******************/
#ifdef ctSRVR
#define ctFeatSHUTDOWN_DIAG
#endif

/*^*******************/
/*
** ctFeatNONBLK_SOCKIO enables TCP/IP socket I/O with
** a configurable timeout.
**
** DEFAULT:  ctFeatNONBLK_SOCKIO is activated
*/
/*~*******************/

#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctSRVR) || defined(ctLOCLIB)
#define ctFeatNONBLK_SOCKIO
#endif


/*^*******************/
/*
** ctFeatRWTPREC enables partial record rewrites using RWTPREC()
** ctHUGEFILE support is required.
**
** DEFAULT:  ctFeatRWTPREC is activated
*/
/*~*******************/
#ifndef NO_ctFeatRWTPREC
#ifdef ctHUGEFILE
#define ctFeatRWTPREC
#endif
#endif

#ifndef ctHUGEFILE
#ifdef  ctFeatRWTPREC
#undef  ctFeatRWTPREC
#endif
#endif


/*^*******************/
/*
** ctFeatRECRLOCK enables recursive lock and unlock calls. A recursive lock
** call is the same as a non-recursive call unless the record position being
** locked is already locked by the calling user. In this case, a recursive
** lock causes an internal counter to be incremented. This counter tracks
** how many recursive unlock calls must be made to actually unlock the record.
** If recursive lock calls have been made and a non-recursive unlock call
** is made, then the lock is released (without requiring additional unlock
** calls).
**
**
** MUSTFRCE and ctHUGEFILE support are required.
**
** DEFAULT:  ctFeatRECRLOCK is activated for MUSTFRCE compiles
*/
/*~*******************/
#ifndef NO_ctFeatRECRLOCK
#ifdef ctHUGEFILE
#define ctFeatRECRLOCK
#endif
#endif


/*^*******************/
/*
** ctFeatFILMTX enables a new API call ctFILMTX(pTEXT filename,NINT opcode)
** which supports a global mutex concept based on file locking. The file
** mutex is held at the process level, although individual threads can
** make recursive calls to the same mutex.
**
** filename points to the name of a file which is used only for the purpose
** of the mutex. The file need not be a c-tree file; and the file can,
** optionally, be created.
**
** DEFAULT:  ctFeatFILMTX is activated for all systems except
** Windows CE, the Windows kernel, and the DIAD filesystem.

*/
/*~*******************/
#ifndef ctPortWINCE
#ifndef ctPortWINKE
#ifndef ctPortDIAD_FS
#define ctFeatFILMTX
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatFILWCD enables a new API call ctFILWCD() which returns a list
** of filenames matching the specified filename with wildcard characters.
**
** DEFAULT:  ctFeatFILWCD is activated for c-tree Client/Server compiles
** for all systems except Windows CE and the Windows kernel.
*/
/*~*******************/
#ifndef ctPortWINCE
#ifndef ctPortWINKE
#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB) || defined(ctSRVR)
#define ctFeatFILWCD
#ifdef ctSRVR
#define ctFeatFILWCD_SRVR
#endif
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatLOKLST enables a new API call ctLOKLST that permits an appliction
** to find the user(s) that own a record lock and are waiting for the lock.
** The lock is specified by providing the datno and record offset.
**
** DEFAULT:  ctFeatLOKLST is activated
*/
/*~*******************/
#ifndef NO_ctFeatLOKLST
#define ctFeatLOKLST
#endif


/*^*******************/
/*
** ctFeatPERMISSIONS enables a new class of server configuration entries
** that permit default file permissions to be assigned to one or more
** groups including two special groups: WORLD and OWNER. The main use for
** this capability is to enforce permission flags on files that have already
** been created without a permission mask (i.e., the permission mask is zero
** at file create). A zero permission mask is equivalent to granting everyone
** all rights: OPF_ALL | GPF_ALL | WPF_ALL. [Note: ALL does not include the
** special NOPASS flag that permits a file to be pened for reading without
** supplying the file password. To grant NOPASS permission, it must be
** included explicitly.]
**
** The new configuration entries are of the form:
**	FILE_PERMISSIONS	groupID#pmodeA#...#pmodeZ
**
** where groupID is the name of a user group or the special groups WORLD
** and OWNER, The pmode entries are symbolic names for the possible permission
** flags: READ, WRITE, DEF, DELETE, ALL, NOPASS and NONE. NONE should not
** be used with any other permission flags. It indicates no permissions are
** granted. Granting a permission of WRITE, DEF or DELETE is equivalent to
** granting all of the lessor permissions. For example, READ#WRITE is
** equivalent to WRITE.
**
** If ctFeatPERMISSIONS is turned on at compile, but no FILE_PERMISSIONS
** entries are in the configuration file, there should be no new effect
** on behavior.
**
** DEFAULT:  ctFeatPERMISSIONS is activated. ctFeatPERMISSIONS requires
** ctSRVR support.
*/
/*~*******************/
#define ctFeatPERMISSIONS


/*^*******************/
/*
** ctFeatFILEUSRLST maintains, for each file that is open, a list of threads
** that currently have the file opened. Without ctFeatFILEUSRLST, we only
** have a count of the threads that have the file opened.
**
** DEFAULT:  ctFeatFILEUSRLST is activated for ct_V90_GENERATION.
**  ctFeatFILEUSRLST requires MULTITRD support.
*/
/*~*******************/
#ifdef ct_V90_GENERATION
#ifdef MULTITRD
#ifndef NO_ctFeatFILEUSRLST
#define ctFeatFILEUSRLST
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatFILEBLOCK enables a new API call, ctFILBLK(pTEXT filename,LONG action)
** that permits an authorized user to block access to a file, and subsequently
** restore access to the file.
**
** ctFeatFILEBLOCK cannot be turned on without MULTITRD
**
** DEFAULT:  ctFeatFILEBLOCK is activated. ctFeatFILEBLOCK requires
** ctFeatFILEUSRLST support and ctWORKMON support.
*/
/*~*******************/
#ifndef NO_ctFeatFILEBLOCK
#ifdef MULTITRD
#define ctFeatFILEBLOCK
#endif
#endif

#ifndef ctPortWIN32
#define ct_fullname_long	ct_fullname
#endif

#ifdef ctFeatFILEBLOCK
#ifndef ctFeatFILEUSRLST
#define ctFeatFILEUSRLST
#endif
#endif


/*^*******************/
/*
** ctFeatFScopy enables support for file system copy operations.
**
** DEFAULT:  ctFeatFScopy is activated for all systems except
** Windows CE, MacOS9 and prior, the Windows kernel, and
** Novell NetWare.
*/
/*~*******************/
#if (!defined(ctPortWINCE) && !defined(ctPortAPPLE7) && !defined(ctPortWINKE) && !defined(ctPortNLM) && !defined(ctPortWINIOT))
#define ctFeatFScopy
#endif


/*^*******************/
/*
** ctFeatFSpath enables support for file system path operations.
**
** DEFAULT:  ctFeatFSpath is activated for all systems except
** Windows CE, MacOS9 and prior, and the Windows kernel.
*/
/*~*******************/
#if (!defined(ctPortWINCE) && !defined(ctPortAPPLE7) && !defined(ctPortWINKE))
#define ctFeatFSpath
#endif


/*^*******************/
/*
** ctFeatWIN32_TEMPLATE_COPY enables the copying of transaction log template
** files using an external copy utility.
**
** DEFAULT:  ctFeatWIN32_TEMPLATE_COPY is activated
*/
/*~*******************/

#ifdef ctPortWIN32
#ifndef ctPortWINKE
#ifndef ctPortWINCE_SRVR
#if defined (ctSRVR) || defined(ctBNDSRVR)
#define ctFeatWIN32_TEMPLATE_COPY
#endif
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatINLINE_LOGON enables the c-tree Server's NewLogon() thread to
** accept a client connection when the attempt to create a new thread to
** listen for the next connection request fails.
**
** DEFAULT:  ctFeatINLINE_LOGON is activated
*/
/*~*******************/

#ifdef ctSRVR
#define ctFeatINLINE_LOGON
#endif


/*^*******************/
/*
** ctFeatFILE_OPEN_CALLBACK causes the c-tree Server to call user-defined
** callback functions on file open, create, and close operations.
**
** DEFAULT:  ctFeatFILE_OPEN_CALLBACK is NOT activated
*/
/*~*******************/

#ifdef ctSRVR
/* #define ctFeatFILE_OPEN_CALLBACK */
#endif


/*^*******************/
/*
** ctFeatCFGFILE enables configuration file support for the c-tree Server.
**
** DEFAULT:  ctFeatCFGFILE is activated.
*/
/*~*******************/

#ifdef ctSRVR
#ifndef NO_ctFeatCFGFILE
#define ctFeatCFGFILE
#endif
#endif


/*^*******************/
/*
** ctFeatCTUSER enables CT_USER API support.
**
** DEFAULT:  ctFeatCTUSER is activated.
*/
/*~*******************/

#ifndef NO_ctFeatCTUSER
#define ctFeatCTUSER
#endif


/*^*******************/
/*
** ctFeatSECURITY enables c-tree Server FAIRCOM.FCS security support.
**
** DEFAULT:  ctFeatSECURITY is activated.
*/
/*~*******************/

#ifndef NO_ctFeatSECURITY
#define ctFeatSECURITY
#endif


/*^*******************/
/*
** ctFeatSYSLOG enables c-tree Server system log file support.
**
** DEFAULT:  ctFeatSYSLOG is activated for c-tree Client/Server compiles.
*/
/*~*******************/

#ifndef NO_ctFeatSYSLOG
#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB) || defined(ctSRVR)
#define ctFeatSYSLOG
#endif
#endif


/*^*******************/
/*
** ctFeatSPACE_RECLAIM_QUEUE enables c-tree Server permanent deleted
** space reclamation queue support.
**
** DEFAULT:  ctFeatSPACE_RECLAIM_QUEUE is activated for server compiles.
*/
/*~*******************/

#ifdef MULTITRD
#ifndef NO_ctFeatSPACE_RECLAIM_QUEUE
#define ctFeatSPACE_RECLAIM_QUEUE
#endif
#endif

/*^*******************/
/*
** ctFeatSRVR_MONITOR enables c-tree Server message monitor
** logging support.
**
** DEFAULT:  ctFeatSRVR_MONITOR is activated for server compiles.
*/
/*~*******************/

#ifdef ctSRVR
#ifndef NO_ctFeatSRVR_MONITOR
#define ctFeatSRVR_MONITOR
#endif
#endif


/*^*******************/
/*
** ctFeatDIAGNOSE_UDEFER_CHK enables support for the
** DIAGNOSTICS CHECK_UDEFER c-tree Server configuration option.
**
** DEFAULT:  ctFeatDIAGNOSE_UDEFER_CHK is activated for server compiles.
*/
/*~*******************/

#ifdef ctSRVR
#ifndef NO_ctFeatDIAGNOSE_UDEFER_CHK
#define ctFeatDIAGNOSE_UDEFER_CHK
#endif
#endif


/*^*******************/
/*
** ctFeatFILE_COMPACT enables support for the
** file compression API function.
**
** DEFAULT:  ctFeatFILE_COMPACT is activated.
*/
/*~*******************/

#ifndef NO_ctFeatFILE_COMPACT
#define ctFeatFILE_COMPACT
#endif


/*^*******************/
/*
** ctFeatFILE_REBUILD enables support for the
** file rebuild API function.
**
** DEFAULT:  ctFeatFILE_REBUILD is activated.
*/
/*~*******************/

#ifndef NO_ctFeatFILE_REBUILD
#define ctFeatFILE_REBUILD
#endif


/*^*******************/
/*
** ctFeatIDLE_THREAD enables support for the
** c-tree Server's idle thread.
**
** DEFAULT:  ctFeatIDLE_THREAD is activated for server compiles.
*/
/*~*******************/

#ifdef ctSRVR
#ifndef NO_ctFeatIDLE_THREAD
#define ctFeatIDLE_THREAD
#endif
#endif


/*^*******************/
/*
** ctFeatDELETE_NODE_THRD enables support for the
** c-tree Server's delete node thread.
**
** DEFAULT:  ctFeatDELETE_NODE_THRD is activated for server compiles.
*/
/*~*******************/

#ifdef MULTITRD
#ifndef NO_ctFeatDELETE_NODE_THRD
#define ctFeatDELETE_NODE_THRD
#endif
#endif

/*
** Set the NODE_DELAY default value. See the cfgNODE_DELAY case in cfgkw()
** to understand how these values map to the effective NODE_DELAY values.
*/
#if ctVER3_GE(11,5,0) || defined(ctPortRTG)
/* Wait 1 second before acting on a delete node queue entry. */
#define ctDEFAULT_NODE_DELAY	0
#else
/* Wait 75 seconds before acting on a delete node queue entry. */
#define ctDEFAULT_NODE_DELAY	300
#endif

/*^*******************/
/*
** ctFeatDUPOPEN enables support for the dupopen() function.
**
** DEFAULT:  ctFeatDUPOPEN is activated.
*/
/*~*******************/

#ifndef NO_ctFeatDUPOPEN
#define ctFeatDUPOPEN
#endif


/*^*******************/
/*
** ctFeatVIRTUAL_FILES enables support for virtual files.
**
** DEFAULT:  ctFeatVIRTUAL_FILES is activated, but is disabled for c-tree Server
**           version 11.0.0 and later.
*/
/*~*******************/

#if defined(MULTITRD) && ctVER3_GE(11,0,0)
#define NO_ctFeatVIRTUAL_FILES
#endif

#ifndef NO_ctFeatVIRTUAL_FILES
#define ctFeatVIRTUAL_FILES
#endif


/*^*******************/
/*
** ctFeatDISK_FULL_CHECK enables support for disk free
** space checking.
**
** DEFAULT:  ctFeatDISK_FULL_CHECK is activated.
*/
/*~*******************/

#ifndef NO_ctFeatDISK_FULL_CHECK
#define ctFeatDISK_FULL_CHECK
#endif

#ifndef ctFeatDISK_FULL_CHECK
#undef ctDISKFULL
#endif


/*^*******************/
/*
** ctFeatISAM_SET enables support for ISAM set operations.
**
** DEFAULT:  ctFeatISAM_SET is activated.
*/
/*~*******************/

#ifndef NO_ctFeatISAM_SET
#define ctFeatISAM_SET
#endif


/*^*******************/
/*
** ctFeatISAM_RANGE enables support for ISAM range operations.
**
** DEFAULT:  ctFeatISAM_RANGE is activated.
*/
/*~*******************/

#ifndef NO_ctFeatISAM_RANGE
#define ctFeatISAM_RANGE
#endif
#ifndef NO_ctRNGEnxtprv
#ifdef ctFeatISAM_RANGE
#define ctRNGEnxtprv	/* turn on NXTKEY/PRVKEY range optimization */
#endif
#endif

/* ISAM range segment group support */
#if ctVER3_GE(11,3,0) || (ctVER3_GE(11,2,2) && defined(ctPortCHARGER1))
#ifndef NO_ctFeatISAM_RANGEseggrp
#define ctFeatISAM_RANGEseggrp
#endif
#endif

/* Bits in cthghwrd that ALCRNG uses to pass key buffer count to server: */
#define ALCRNG_NBUF_MASK 0x0000003

/* Bit in cthghwrd that ALCRNG uses to indicate that the client is using the
ALCRNG extended operator format: */
#define ALCRNGX_FORMAT 0x00000004

/*^*******************/
/*
** ctFeatASYNC enables support for the CTASYNC API function.
**
** DEFAULT:  ctFeatASYNC is activated.
*/
/*~*******************/

#ifndef NO_ctFeatASYNC
#define ctFeatASYNC
#endif


/*^*******************/
/*
** ctFeatKEY_ESTIMATE enables support for the ESTKEY and FRCKEY
** API functions.
**
** DEFAULT:  ctFeatKEY_ESTIMATE is activated.
*/
/*~*******************/

#ifndef NO_ctFeatKEY_ESTIMATE
#define ctFeatKEY_ESTIMATE
#endif


/*^*******************/
/*
** ctFeatIOPERFORMANCE enables support for the IOPERFORMANCE
** and IOPERFORMANCEX API functions.
**
** DEFAULT:  ctFeatIOPERFORMANCE is activated.
*/
/*~*******************/

#ifndef NO_ctFeatIOPERFORMANCE
#define ctFeatIOPERFORMANCE
#endif


/*^*******************/
/*
** ctFeatLOCK_DUMP enables support for the ctLOKDMP
** API function.
**
** DEFAULT:  ctFeatLOCK_DUMP is activated.
*/
/*~*******************/

#ifndef NO_ctFeatLOCK_DUMP
#define ctFeatLOCK_DUMP
#endif


/*^*******************/
/*
** ctFeatDYNAMIC_DUMP enables support for the c-tree Server's
** dynamic dump feature.
**
** DEFAULT:  ctFeatDYNAMIC_DUMP is activated for c-tree Server compiles.
*/
/*~*******************/

#ifdef ctSRVR
#ifndef NO_ctFeatDYNAMIC_DUMP
#ifdef TRANPROC
#define ctFeatDYNAMIC_DUMP
#endif
#endif
#endif

#ifndef ctFeatDYNAMIC_DUMP
#undef ctBEHAV_DumpProtect
#endif


/*^*******************/
/*
** ctFeatThrdXxx_API enables support for the c-tree Server's
** various thread API functions.
**
** DEFAULT:  ctFeatThrdXxx_API is activated for c-tree Server compiles.
*/
/*~*******************/

#ifndef NO_ctFeatThrdBlock_API
#define ctFeatThrdBlock_API
#endif
#ifndef NO_ctFeatThrdCreate_API
#define ctFeatThrdCreate_API
#endif
#ifndef NO_ctFeatThrdMutex_API
#define ctFeatThrdMutex_API
#endif
#ifndef NO_ctFeatThrdQueue_API
#define ctFeatThrdQueue_API
#endif
#ifndef NO_ctFeatThrdSemap_API
#define ctFeatThrdSemap_API
#ifdef MULTITRD
#ifndef NO_ctFeatThrdSemap_Native
#define ctFeatThrdSemap_Native
#endif
#endif
#endif
#ifndef NO_ctFeatThrdSleep_API
#define ctFeatThrdSleep_API
#endif


/*^*******************/
/*
** ctFeatTRANDEP enables support for transaction dependent
** file create and delete operations.
**
** DEFAULT:  ctFeatTRANDEP is activated for TRANPROC compiles.
*/
/*~*******************/

#ifdef TRANPROC
#ifndef NO_ctFeatTRANDEP
#define ctFeatTRANDEP
#endif
#endif


/*^*******************/
/*
** ctFeatRSTRDEL enables support for restorable
** file delete operations.
**
** DEFAULT:  ctFeatRSTRDEL is activated when transaction dependent
** file creates and deletes are supported.
*/
/*~*******************/

#ifdef ctFeatTRANDEP
#ifndef NO_ctFeatRSTRDEL
#define ctFeatRSTRDEL
#endif
#endif


/*^*******************/
/*
** ctFeatTRAN_BAK_FWD enables support for transaction rollback and
** forward roll operations.
**
** DEFAULT:  ctFeatTRAN_BAK_FWD is activated for TRANPROC compiles.
*/
/*~*******************/

#ifdef TRANPROC
#ifndef NO_ctFeatTRAN_BAK_FWD
#define ctFeatTRAN_BAK_FWD
#endif
#endif

#if defined(ctFeatTRAN_BAK_FWD) && !defined(TRANPROC)
#undef ctFeatTRAN_BAK_FWD
#endif

#if defined(ctFeatTRAN_BAK_FWD) && !defined(ctBEHAV_EOR_CLSTRAN) && \
	ctVER3_GE(10,4,1)
#ifdef NO_ctBEHAV_EOR_CLSTRAN
#error ctBEHAV_EOR_CLSTRAN required for transaction rollback
#else
/* NOTE: We check the other ctBEHAV_EOR_CLSTRAN requirements later. */
#define ctBEHAV_EOR_CLSTRAN
/* Indicate that we turned on ctBEHAV_EOR_CLSTRAN in ctopt2.h: */
#define ctBEHAV_EOR_CLSTRANctopt2
#endif
#endif


/*^*******************/
/*
** ctFeatREMOTE_FNCMON activates the ability to have a remote machine
** receive the function monitor output. This feature requires that the server be linked
** with the ntreep.lib (ntree Plus) libary. This feature uses the console based ntrfcnmon.exe utility
** that may be compiled from the ctree/source/rfncmon directory. This feature is activated by default for
** Windows CE (see ../ctree/source/msc.wce/Server/ctoptn.h)
**
** DEFAULT:  ctFeatREMOTE_FNCMON is NOT activated
*/
/*~*******************/
#ifdef ctSRVR
	/* #define ctFeatREMOTE_FNCMON */
#endif

/*^*******************/
/*
** ctFeatEVAL_TIMER causes the c-tree Server evaluation thread to use a c-tree
** timer, rather than a sleep operation, to wait for the specified interval.
** This approach allows the c-tree Server's shutdown function to signal the
** thread that the server is shutting down. When this feature is disabled,
** a c-tree Server process on Linux that is running as an evaluation server
** enters a defunct state when shut down, because the evaluation thread is
** still sleeping.
**
** DEFAULT:  ctFeatEVAL_TIMER is activated for c-tree Server compiles on Linux.
*/
/*~*******************/
#ifdef ctSRVR
#ifdef ctPortLINUX
#define ctFeatEVAL_TIMER
#endif
#endif


/*^*******************/
/*
** ctFeatPRVKEY_OPT supports two temporary key expansion buffers for leaf
** nodes with variable length keys that are traversed in reverse order.
** The permanent key expansion buffer helps when keys are traversed in
** increasing order, but is of no help when he order is reversed. The
** buffers are allocated when a request is made to extract a key near the
** end of the node, but before the previously extracted key. Without this
** optimization, each time a compressed key is retrieved in reverse order,
** the decompression routine must start at the beginning of the node.
** Now the decompression can begin at these intermediate positions for
** which the key expansion has been saved.
**
** This feature is off by default.
*/
/*~*******************/

/* #define ctFeatPRVKEY_OPT */
#define ctPRVKEY_OPT_MIN	30	/* minimum number of key values in
					** a node before optimization is
					** attempted.
					*/


/*^*******************/
/*
** ctFeatAUTO_SHMEM enables a c-tree TCP/IP client library to automatically
** use the shared memory protocol when the client is connecting to a server
** on the same Windows system as the client and the shared memory connection
** attempt succeeds.
**
** DEFAULT:  ctFeatAUTO_SHMEM is activated for c-tree TCP/IP client compiles.
*/
/*~*******************/

#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB)
#ifndef ctPortWINCE
#ifdef ctCOMMP_TCPIP
#ifndef NO_ctFeatAUTO_SHMEM
#define ctFeatAUTO_SHMEM
#endif
#endif
#endif
#endif

/*
** On Unix, turn off auto shared memory support if the code is being compiled
** without shared memory support.
*/
#ifdef ctPortUNIX
#ifndef ctFeatUNIX_SHMEM
#undef ctFeatAUTO_SHMEM
#endif
#endif

/*^*******************/
/*
** ctFeatAutoTranLow extends the auto ISAM transaction concept to low level
** operations, but ONLY when either AUTO_PREIMG or AUTO_TRNLOG cause a file
** to be opened/created in transaction mode.
**
** ctFeatAutoTranLow requires TRANPROC, ctSRVR and ctHUGEFILE support.
**
** DEFAULT:  ctFeatAutoTranLow is on by default.
*/
/*~*******************/
#ifndef NO_ctFeatAutoTranLow
#ifdef TRANPROC
#ifdef ctHUGEFILE
#ifdef ctSRVR
#define ctFeatAutoTranLow
#endif
#endif
#endif
#endif

/*^*******************/
/*
** ctFeatCATEND_RETURN causes ctcatend() and terr() to return
** instead of exiting the process.
**
** DEFAULT:  ctFeatCATEND_RETURN is on for Windows kernel and
** c-tree Server .NET DLL compiles only.
*/
/*~*******************/
#ifndef NO_ctFeatCATEND_RETURN

#ifdef ctPortWINKE
#define ctFeatCATEND_RETURN
#endif

#ifdef ctSRVR
#ifdef ctPortDotNET
#define ctFeatCATEND_RETURN
#endif
#endif

#endif

/*^*******************/
/*
** ctFeatAUTO_LOCK_RETRY enables support for automatic lock
** retries. The retry count is specified by the AUTO_LOCK_RETRY
** server configuration keyword.
**
** DEFAULT:  ctFeatAUTO_LOCK_RETRY is on for c-tree Server compiles.
*/
/*~*******************/
#ifdef ctSRVR
#define ctFeatAUTO_LOCK_RETRY
#endif

/*^*******************/
/*
** ctFeatFSCANF_STRING enables support for FairCom's version of
** the fscanf() function that supports the "%s" format specifier only.
**
** DEFAULT:  ctFeatFSCANF_STRING is on for c-tree Server compiles
** for the DIAD file system only.
*/
/*~*******************/
#ifdef ctPortDIAD_FS
#ifdef ctSRVR
#define ctFeatFSCANF_STRING
#endif
#endif


/*^*******************/
/*
** ctFeatKEEP_XFREED enables support for ctMARK_XFREED on transaction begins and
** ctKEEP_XFREED on transaction ends. ctMARK_XFREED causes unlock requests
** during a transaction to add a special attribute bit to the user lock table
** entry which indicates an explicit unlock request has been made and which
** ctKEEP_XFREED queries during a transaction end to determine whether or not
** the lock should be released.
**
** DEFAULT:  ctFeatKEEP_XFREED is on by default in v10.5.0 and later. It can
** only be on when TRANPROC is defined.
*/
/*~*******************/

#if ctVER3_GE(10,4,1)
#ifndef NO_ctFeatKEEP_XFREED
#define ctFeatKEEP_XFREED
#endif
#endif
#ifdef ctFeatKEEP_XFREED
#ifndef TRANPROC
#undef ctFeatKEEP_XFREED
#endif
#endif


/*^*******************/
/*
** ctFeatDUMP_NONCTREEFILES enables support for dumping non-c-tree files using the
** !NONCTREEFILES keyword in the !FILES section of a dynamic dump script.
**
** DEFAULT:  ctFeatDUMP_NONCTREEFILES is on by default.
*/
/*~*******************/

#define ctFeatDUMP_NONCTREEFILES


/*^*******************/
/*
** ctFeatREPL_NODEID enables support for maintaining a node id for replication
** log reader and log writer clients. The replication log scan logic uses the
** node id's to determine if operations for a particular transaction should be
** returned to a particular replication reader or not.
**
** DEFAULT:  ctFeatREPL_NODEID is activated except for the bound server model.
** We do not activate this option for the bound server model because the
** srvnodeid variable in ctscfg.c does not exist in that model.
*/
/*~*******************/

#ifndef ctBNDSRVR
#define ctFeatREPL_NODEID
#endif

/*^*******************/
/*
** ctFeatQUIET enables a new API call,
**
** 		ctQUIET(pTEXT filespec,LONG timeoutSEC,LONG action)
**
** that permits an authorized user to block various types of system activity.
** ctFeatQUIET cannot be turned on without ctFeatFILEBLOCK
**
** DEFAULT:  ctFeatQUIET is activated.
*/
/*~*******************/
#ifndef NO_ctFeatQUIET
#ifdef ctFeatFILEBLOCK
#define ctFeatQUIET
#endif
#endif

/*^*******************/
/*
** ctFeatMAX_USER_LOGS supports an optional limit on how many logs a
** transaction spans before it is aborted or abandoned. When turned on,
** the MAX_USER_LOGS configuration keyword takes as its argument the maximum
** number of logs a transaction may span. If a transaction exceeds the limit,
** an attempt is made to abort the transaction. If it cannot be aborted
** (say because we cannot perform the abort without causing the server to
** fail), we then abandon the transaction which means that the client thread
** loses its connection to the server. There is no guarantee that the
** transaction will not span more logs than the specified maximum, but the
** transaction will end within a reasonable number of logs.
**
** This feature requires MULTITRD and TRANPROC support.
**
** DEFAULT:  ctFeatMAX_USER_LOGS is activated.
*/
/*~*******************/

#ifdef  ctPortNLM
/* RAB:070510: not supported because the makeOWNER(thdid) is not defined in ctinit.c when ctThrds is not defined, as it is not in the NLM */
#define NO_ctFeatMAX_USER_LOGS
#endif

#ifndef NO_ctFeatMAX_USER_LOGS
#define ctFeatMAX_USER_LOGS
#endif

#ifdef ctFeatMAX_USER_LOGS
#ifndef TRANPROC
#undef ctFeatMAX_USER_LOGS
#else
#ifndef MULTITRD
#undef ctFeatMAX_USER_LOGS
#endif
#endif
#endif

/*^*******************/
/*
** ctFeatADDKY_DEFERD supports deferring a key add operation that is
** performed during an update operation for a transaction-controlled unique
** index.
**
** This feature requires ctXTDLOG support.
**
** DEFAULT:  ctFeatADDKY_DEFERD is activated for c-tree Server.
*/
/*~*******************/
#ifndef NO_ctFeatADDKY_DEFERD
#ifdef ctSRVR
#define ctFeatADDKY_DEFERD
#endif
#endif

/*^*******************/
/*
** ctFeatRECBKT enables c-tree record bucket data file support.
**
** DEFAULT:  ctFeatRECBKT is NOT activated.
*/
/*~*******************/
#ifndef NO_ctFeatRECBKT
#ifdef ctSRVR
/* #define ctFeatRECBKT */
/* #define ctFeatRECBKT_HASH_STAT */
#endif
#endif

/*^*******************/
/*
** ctFeatREPL_READ_BUFFER enables use of a transaction log read buffer for
** c-tree replication readers.
**
** DEFAULT:  ctFeatREPL_READ_BUFFER is activated for c-tree Server.
*/
/*~*******************/
#ifndef NO_ctFeatREPL_READ_BUFFER
#ifdef ctSRVR
#define ctFeatREPL_READ_BUFFER
#endif
#endif

/*^*******************/
/*
** ctFeatREPL_BATCH enables support for the c-tree Server returning a group
** of changes in a single call to ctReplGetNextChange().
**
** DEFAULT:  ctFeatREPL_BATCH is activated when replication support is enabled.
*/
/*~*******************/
#ifndef NO_ctFeatREPL_BATCH
#ifdef ctFeatREPLICAT
#define ctFeatREPL_BATCH
#endif
#endif


/*^*******************/
/*
** ctFeatJOBMGTSYS enables support for the Job Management Subsystem.
**
** DEFAULT:  ctFeatJOBMGTSYS is deactivated by default.
*/
/*~*******************/
#ifndef NO_ctFeatJOBMGTSYS
#define NO_ctFeatJOBMGTSYS
#endif


#ifndef NO_ctFeatJOBMGTSYS
#define ctFeatJOBMGTSYS		/* Activate job management subsystem logic */
#define MAXCTJOBS	50	/* max number of job threads allowed */
#endif				/* this controls how many job file names can be listed in the ctsrvr.cfg file */



/*^*******************/
/*
** When #define ctAppREPLENG_LIST is enabled in repleng.c and #define
** ctFeatREPLENG_LOCAL_LIST is NOT enabled, repleng's list management
** functions use memory files on the target c-tree Server. When #define
** ctFeatREPLENG_LOCAL_LIST IS enabled, repleng's list management
** functions are implemented entirely in the repleng process.
**
** DEFAULT:  ctFeatREPLENG_LOCAL_LIST is activated for non-server compiles.
*/
/*~*******************/
#ifndef MULTITRD
#define ctFeatREPLENG_LOCAL_LIST
#endif


/*^*******************/
/*
** ctFeatUSRBLKTIMOUT enables support for the user/thread blocking
** mechanism to permit timeout values. The blocking mechanism works by
** having a user/thread that encounters a blocking condition (such as a
** lock it must wait for) acquire its blocking object, ct_blk[ThdID]->semab,
** and then issue a wait call on the object. When another thread clears
** the blocking condition (such as releasing a lock), it clears the
** block, ct_blk[ThdID]->semab. With this feature, the wait can use a
** timeout value.
**
** This implementation has only applied the timeout capability to
** data file blocking lock requests. ctLOKTIMOUT sets the timeout value.
**
** DEFAULT:  ctFeatUSRBLKTIMOUT is activated by default.
*/
/*~*******************/
#ifndef NO_ctFeatUSRBLKTIMOUT
#ifdef MULTITRD
#define ctFeatUSRBLKTIMOUT
#endif
#endif


/*^*******************/
/*
** ctFeatDISKIOtime enables support for collecting disk read and write
** timings on a per-file basis.
**
** DEFAULT:  ctFeatDISKIOtime is activated for c-tree Server compiles
** when snapshot and high-resolution timer support is activated.
*/
/*~*******************/
#ifndef NO_ctFeatDISKIOtime
#ifdef MULTITRD
#ifdef ctFeatSNAPSHOTtimer
#define ctFeatDISKIOtime
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatSNAPSHOTfncfil enables support for collecting c-tree function call
** timings for each open file. When this feature is enabled, timings are
** collected for c-tree functions that take a c-tree file number as a
** parameter and the timings are grouped by file number.
**
** DEFAULT:  ctFeatSNAPSHOTfncfil is activated for c-tree Server compiles
** when snapshot and high-resolution timer support is activated.
*/
/*~*******************/
#ifndef NO_ctFeatSNAPSHOTfncfil
#ifdef MULTITRD
#ifdef ctFeatSNAPSHOTtimer
#define ctFeatSNAPSHOTfncfil
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatGNSEMAhsh enables support for controlling access to the index
** cache hash lists (INLIST and PNLIST) using one mutex for each hash list
** rather than a single mutex for all lists. When this compile-time option
** is enabled, the available page list (AVLIST) is controlled by its own
** separate mutex.
**
** DEFAULT:  ctFeatGNSEMAhsh is activated for c-tree Server compiles.
*/
/*~*******************/
#ifndef NO_ctFeatGNSEMAhsh
#ifdef MULTITRD
#ifdef ctHUGEFILE
#define ctFeatGNSEMAhsh
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatRWLOCKwindows enables reader/writer lock support on	*/
/* Windows systems.						*/
/*								*/
/* Default: ctFeatRWLOCKwindows is ON for the c-tree Server on	*/
/* Windows systems except for Windows CE and Windows kernel.	*/
/* Requires the Visual C 2008 compiler or later.		*/
/*--------------------------------------------------------------*/
#ifdef ctPortWIN32
#ifndef ctPortWINCE
#ifndef ctPortWINKE
#if defined(ctSRVR) || defined(ctBNDSRVR)
#if _MSC_VER > 1400
#ifndef NO_ctFeatRWLOCKwindows
#define ctFeatRWLOCKwindows
#endif
#endif
#endif
#endif
#endif
#endif

/*^*******************/
/*
** ctFeatRWLOCK enables support for controlling access to the INLIST index
** cache hash lists using reader/writer locks rather than mutexes.
**
** DEFAULT:  ctFeatRWLOCK is activated for c-tree Server compiles on Unix
** and Windows systems.
*/
/*~*******************/
#ifndef NO_ctFeatRWLOCK
#ifdef MULTITRD
#if defined(ctPortUNIX) || defined(ctFeatRWLOCKwindows)
#define ctFeatRWLOCK
#endif
#endif
#endif

/*
** check for reader/writer ctpconcsema support
**
** ctBEHAV_WORKsyncRWL cannot be defined externally.
*/
#ifdef ctBEHAV_WORKsyncRWL
#undef ctBEHAV_WORKsyncRWL
#endif

#ifdef ctBEHAV_WORKsync
#ifndef NO_ctBEHAV_WORKsyncRWL
#ifdef ctFeatRWLOCK
#define ctBEHAV_WORKsyncRWL
#endif
#endif
#endif



/*^*******************/
/*
** ctMTXtoWLOCK converts ctmutrqs/clr calls to ctrwlrqs/clr calls when
** Windows supports slim read/write locks.
**
** DEFAULT:  ctMTXtoWLOCK is off by default
*/
/*~*******************/
#ifdef ctMTXtoWLOCK
#if !defined(ctFeatRWLOCKwindows) || defined(ctDBGSEMCNT) || defined(ctDBGsemlst)
			/*
			** ctMTXtoWLOCK does not support debug counts or
			** ctDBGsemlst. Turn ctMTXtoWLOCK OFF.
			*/
#undef ctMTXtoWLOCK
#else
#ifndef NO_ctDBGSEMCNT
			/*
			** make sure ctDBGfcqa does not turn on ctDBGSEMCNT
			** when ctMTXtoWLOCK is enabled
			*/
#define NO_ctDBGSEMCNT
#endif
#endif
#endif

/*^*******************/
/*
** ctDBGhdrrqs keeps cthdrrqs(&ctnum->thdrf ...) from being converted to
** the standard mutex call ctmutrqs(&ctnum->thdrf ...). Without ctDBGhdrrqs,
** cthdrrqs() becomes ctmutrqs(). When ctDBGhdrrqs is defined, we must
** supply the cthdrrqs() routine to perform debugging and ultimately
** call ctmutrqs().
**
** DEFAULT:  ctDBGhdrrqs is off by default. Requires ctDBGfcqa && MULTITRD.
*/
/*~*******************/
#ifdef ctDBGhdrrqs
#ifndef MULTITRD
#undef ctDBGhdrrqs
#endif
#else
#define cthdrrqs	ctmutrqs
#endif

#ifdef ctDBGhdrrqs
#ifndef ctDBGfcqa
#define ctDBGfcqa
#endif
#endif


/*^*******************/
/*
** ctFeatSKIPaddwrk enables support for the c-tree Server configuration option
** SKIP_CTADDWORK YES, which causes the ctaddwork() and ctrmvwork() functions
** to take no action. This option is intended to be used for performance
** testing purposes and will be removed after these functions are changed to
** avoid unnecessary mutex contention.
**
** DEFAULT:  ctFeatSKIPaddwrk is activated for c-tree Server compiles.
*/
/*~*******************/
#ifndef NO_ctFeatSKIPaddwrk
#ifdef MULTITRD
#define ctFeatSKIPaddwrk
#endif
#endif


/*^*******************/
/*
** ctFeatAVLISTnum enables support for multiple index LRU lists. The
** number of LRU lists is controlled by the INDEX_LRU_LISTS server
** configuration option and defaults to 4.
**
** DEFAULT:  ctFeatAVLISTnum is activated for c-tree Server compiles.
*/
/*~*******************/
#ifndef NO_ctFeatAVLISTnum
#ifdef MULTITRD
#ifdef ctFeatGNSEMAhsh
#define ctFeatAVLISTnum
#define ctMAXAVLIST 100 /* Maximum number of index buffer LRU lists */
#endif
#endif
#endif

#ifdef ctFeatAVLISTnum
#ifndef ctFeatGNSEMAhsh
#undef ctFeatAVLISTnum
#endif
#endif


/*^*******************/
/*
** ctFeatBLKSEMA enables support for controlling access to buffer block
** lists through one or more separate mutexes instead of ctpgnsema.
**
** DEFAULT:  ctFeatBLKSEMA is activated for c-tree Server compiles.
*/
/*~*******************/
#ifndef NO_ctFeatBLKSEMA
#ifdef ctFeatGNSEMAhsh
#ifdef MULTITRD
#define ctFeatBLKSEMA
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatDBSEMAhsh enables support for controlling access to the data
** cache hash lists (DULIST and DPLIST) using one mutex for each hash list
** rather than a single mutex for all lists. When this compile-time option
** is enabled, the available page list (DALIST) is controlled by its own
** separate mutex.
**
** DEFAULT:  ctFeatDBSEMAhsh is activated for c-tree Server compiles.
*/
/*~*******************/
#ifndef NO_ctFeatDBSEMAhsh
#ifdef MULTITRD
#ifdef ctCACHE_MEMORY
#define ctFeatDBSEMAhsh
#else
cache-buffer mutex arrays require ctCACHE_MEMORY
#endif
#endif
#endif

#ifndef ctFeatDBSEMAhsh
#ifdef ctBEHAV_DATPPScntl
#undef ctBEHAV_DATPPScntl
#endif
#endif

/*^*******************/
/*
** ctFeatDALISTnum enables support for multiple data cache LRU lists. The
** number of LRU lists is controlled by the DATA_LRU_LISTS server
** configuration option and defaults to 4.
**
** DEFAULT:  ctFeatDALISTnum is activated for c-tree Server compiles.
*/
/*~*******************/
#ifndef NO_ctFeatDALISTnum
#ifdef MULTITRD
#ifdef ctFeatDBSEMAhsh
#define ctFeatDALISTnum
#define ctMAXDALIST 100 /* Maximum number of data cache LRU lists */
#endif
#endif
#endif

#ifdef ctFeatDALISTnum
#ifndef ctFeatDBSEMAhsh
#undef ctFeatDALISTnum
#endif
#endif


/*^*******************/
/*
** ctFeatSPLSEMA enables support for a global mutex to control special cache
** page counters: ctnum->datspl and ct_dxsplsnt.
**
** DEFAULT:  ctFeatSPLSEMA is activated for c-tree Server compiles.
*/
/*~*******************/
#ifndef NO_ctFeatSPLSEMA
#ifdef MULTITRD
#ifdef ctFeatDBSEMAhsh
#define ctFeatSPLSEMA
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatFILEUSERLOCKinfo enables support for retrieving the names of
** open files, a list of which connections have a particular file open,
** and a list of locks held on the specified file.
**
** DEFAULT:  ctFeatFILEUSERLOCKinfo is activated for c-tree client and
** c-tree Server compiles.
*/
/*~*******************/
#ifndef NO_ctFeatFILEUSERLOCKinfo
#if defined(MULTITRD) || defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB)
#define ctFeatFILEUSERLOCKinfo
#endif
#endif


/*^*******************/
/*
** ctFeatTRAN_TIMEOUT enables support for the c-tree Server's TRAN_TIMEOUT
** configuration option. This option can be used to enforce a time limit on
** transactions. A transaction that exceeds the specified time limit is
** aborted.
**
** DEFAULT:  ctFeatTRAN_TIMEOUT is activated for c-tree Server compiles.
*/
/*~*******************/
#ifndef NO_ctFeatTRAN_TIMEOUT
#define ctFeatTRAN_TIMEOUT
#endif

#ifdef ctFeatTRAN_TIMEOUT
#ifndef TRANPROC
#undef ctFeatTRAN_TIMEOUT
#else
#ifndef MULTITRD
#undef ctFeatTRAN_TIMEOUT
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatTRACK_CLIENT_ADDR causes the c-tree Server to track the IP address
** from which clients connect.
**
** DEFAULT:  ctFeatTRACK_CLIENT_ADDR is activated for c-tree Server compiles
** for all systems except Windows CE and the Windows kernel.
*/
/*~*******************/
#ifdef ctSRVR
#ifndef NO_ctFeatTRACK_CLIENT_ADDR
#ifndef ctPortWINCE
#ifndef ctPortWINKE
#define ctFeatTRACK_CLIENT_ADDR
#endif
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatDNODEQ_SHUTDOWN_LIMIT enables a configurable limit on the number of
** delete node queue entries that the c-tree Server processes when it is
** shutting down. If the option DNODEQ_SHUTDOWN_LIMIT is specified in the
** c-tree Server configuration file, then when the c-tree Server shuts down,
** if there are more than the specified number of entries in the delete node
** queue, the c-tree Server writes all the entries to a disk stream file
** named DNODEQUE.FCS.
**
** DNODEQ_SHUTDOWN_LIMIT 0 causes the c-tree Server to process all entries
** in the delete node queue when shutting down.
**
** The c-tree Server always attempts to open and read all entries from the
** file DNODEQUE.FCS into the delete node queue at startup, regardless of
** the DNODEQ_SHUTDOWN_LIMIT setting. The c-tree Server deletes the file
** DNODEQUE.FCS after populating the delete node queue with its contents.
** An administrator can delete the file DNODEQUE.FCS before starting the
** c-tree Server in order to avoid processing these persistent delete node
** queue entries.
**
** DEFAULT:  ctFeatDNODEQ_SHUTDOWN_LIMIT is activated for c-tree Server
** compiles when memory file support is enabled.
*/
/*~*******************/
#ifdef ctSRVR
#ifdef ctFeatMEMFILE
#ifndef NO_ctFeatDNODEQ_SHUTDOWN_LIMIT
#define ctFeatDNODEQ_SHUTDOWN_LIMIT
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatCPU_AFFINITY enables the CPU_AFFINITY configuration option.
**
** DEFAULT:  ctFeatCPU_AFFINITY is activated for c-tree Server compiles on
** systems that support setting CPU affinity (as indicated by the preprocessor
** macro ctSET_CPU_AFFINITY_SUPPORTED).
*/
/*~*******************/
#ifdef ctSRVR
#ifndef NO_ctFeatCPU_AFFINITY
#ifdef ctSET_CPU_AFFINITY_SUPPORTED
#define ctFeatCPU_AFFINITY
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatCPU_LIMIT enables support for checking the number of CPUs on which
** the c-tree Server process is licensed to run.
**
** DEFAULT:  ctFeatCPU_LIMIT is activated for c-tree Server compiles on
** systems that support checking CPU affinity (as indicated by the preprocessor
** macro ctGET_CPU_AFFINITY_SUPPORTED).
*/
/*~*******************/
#ifdef ctSRVR
#ifndef NO_ctFeatCPU_LIMIT
#ifdef ctGET_CPU_AFFINITY_SUPPORTED
#define ctFeatCPU_LIMIT
#endif
#endif
#endif


/*^*******************/
/*
** ctFeatREQUEST_TIME_MONITOR enables the REQUEST_TIME_MONITOR configuration
** option.
**
** DEFAULT:  ctFeatREQUEST_TIME_MONITOR is activated for c-tree Server compiles.
*/
/*~*******************/
#ifdef ctSRVR
#ifndef NO_ctFeatREQUEST_TIME_MONITOR
#define ctFeatREQUEST_TIME_MONITOR
#endif
#endif


/*^*******************/
/*
** ctFeatDISTbufcnt enables distributed computation of ctbufcnt when
** ctFeatAVLISTnum is on. It reduces extra mutex calls and reduces
** contention betweeen threads by controlling ctbufcnt with the
** ctFeatAVLISTnum mutex array.
**
** Turning this option on has the side effact of reducing the accuracy
** of the ctbufhgh attribute because ctbufhgh is only checked periodically,
** not every time ctbufcnt is incremented.
**
** DEFAULT:  ctFeatDISTbufcnt is on by default for v10.4.0 and later.
** Requires ctFeatAVLISTnum.
*/
/*~*******************/
#ifdef ctFeatAVLISTnum
#ifndef NO_ctFeatDISTbufcnt

#if ctVER3_GE(10,4,0) && defined(MULTITRD) && !defined(NO_ctFeat_V11_NewCache)
#define ctFeatDISTbufcnt	/* enable distributed computation of ctbufcnt */
#endif

#endif
#endif

#ifdef ctFeatDISTbufcnt
#ifndef ctFeatAVLISTnum
#undef ctFeatDISTbufcnt
#endif
#endif


/*^*******************/
/*
** ctFeatDISTdatcnt enables distributed computation of ctdatcnt when
** ctFeatDALISTnum is on. It reduces extra mutex calls and reduces
** contention betweeen threads by controlling ctdatcnt with the
** ctFeatDALISTnum mutex array.
**
** Turning this option on has the side effact of reducing the accuracy
** of the ctdathgh attribute because ctdathgh is only checked periodically,
** not every time ctdatcnt is incremented.
**
** DEFAULT:  ctFeatDISTdatcnt is on by default for v10.4.0 and later.
** Requires ctFeatDALISTnum.
*/
/*~*******************/
#ifdef ctFeatDALISTnum
#ifndef NO_ctFeatDISTdatcnt

#if ctVER3_GE(10,4,0) && defined(MULTITRD) && !defined(NO_ctFeat_V11_NewCache)
#define ctFeatDISTdatcnt	/* enable distributed computation of ctdatcnt */
#endif

#endif
#endif

#ifdef ctFeatDISTdatcnt
#ifndef ctFeatDALISTnum
#undef ctFeatDISTdatcnt
#endif
#endif


/*^*******************/
/*
** eliminate data-cache/index-buffer pending lists to streamline the
** search and update of the cache/buffer spaces.
**
** data cache space controlled by ctFeatNoDatPndgList
**	this feature eliminates the pending list for data cache pages
**	AND eliminates the data cache page LRU lists. the data LRU list
**	is replaced by a simple, systematic "crawl" over all the data
**	cache pages using static lists that cover all the cache pages.
**
**	an optional set of empty cache page lists is maintained
**	if ctFeatDatEmptyList is enabled. without the empty list
**	support, the crawl routine does not give prefence to unused
**	data cache pages when getting a cache page to assign to
**	a data request not found in cache space.
**
** index buffer space controlled by ctFeatNoIdxPndgList
**	this feature only eliminates the pending list for index buffers.
**	it does not eliminate the index buffer LRU list since the
**	index tree structure is conducive to LRU dynamics.
**
** ctFeatNoDatPndgList and ctFeatNoIdxPndgList can be turned on/off
** independently of each other.
**
** these are on by default for c-tree Server v10.4.0 and later
** unless NO_ctFeat_V11_NewCache is on.
*/
/*~*******************/

#if ctVER3_GE(10,4,0) && defined(MULTITRD) && !defined(NO_ctFeat_V11_NewCache)

#ifndef NO_ctFeatNoIdxPndgList
#ifdef ctFeatATOMICop
#define ctFeatNoIdxPndgList	/* eliminate index cache pending list */
#endif
#endif

#ifndef NO_ctFeatNoDatPndgList
#ifdef ctFeatATOMICop
#define ctFeatNoDatPndgList	/* eliminate data cache pending list */
#endif
#endif

#ifndef NO_ctFeatDatEmptyList
#ifdef ctFeatNoDatPndgList
#define ctFeatDatEmptyList	/* a set of empty cache page lists is maintained*/
#endif
#endif

#ifndef NO_UTRrwlock
#define UTRrwlock		/* use slim reader/writer locks for ctputrsema */
#endif

#ifndef NO_C3Nrwlock
#define C3Nrwlock		/* use slim reader/writer locks for ctpc3ncsema */
#endif

#ifndef NO_CPCrwlock
#define CPCrwlock		/* use slim reader/writer locks for ctpcpcsema */
#endif

#ifdef ctFeatRWLOCKwindows
#ifndef NO_ctFeatRWLOCKctree
/* #define ctFeatRWLOCKctree */	/* use c-tree reader/writer locks instead of
				** critical sections if Windows does not support
				** the reader/writer lock functions that we use */
#endif
#endif

#else

#define NO_ctFeatDISTdatcnt	/* no distributed computation of ctdatcnt */
#define NO_ctFeatDISTbufcnt	/* no distributed computation of ctbufcnt */
#define NO_ctFeatNoIdxPndgList	/* do not eliminate index cache pending list */
#define NO_ctFeatNoDatPndgList	/* do not eliminate data cache pending list */
#define NO_ctFeatDatEmptyList	/* no set of empty cache page lists is maintained */
#define NO_UTRrwlock		/* do not use slim reader/writer locks for ctputrsema */
#define NO_C3Nrwlock		/* do not use slim reader/writer locks for ctpc3ncsema */
#define NO_CPCrwlock		/* do not use slim reader/writer locks for ctpcpcsema */

#endif

#ifdef IHBxclmut
/*
** Index Hash Bin locks based on mutex
*/
#define pIHBLOCKmut	pSEMAmut
#define ctIHBrqs	ctmutrqs
#define ctIHBclr	ctmutclr
#define IHB_rwl		mtx
#define IHB_RWL(loktyp)
#define IHB_RWCA(loktyp,ownr) ownr
#else
/*
** Index Hash Bin locks based on slim reader/writer locks (if available)
*/
#define pIHBLOCKmut	pRWLOCKmut
#define ctIHBrqs	ctRWLrqs
#define ctIHBclr	ctRWLclr
#define IHB_rwl		rwl
#define IHB_RWL(loktyp)	RWL(loktyp)
#define IHB_RWCA(loktyp,ownr) RWCA(loktyp,ownr)
#endif

#ifdef DHBxclmut
/*
** Data Hash Bin locks based on mutex
*/
#define pDHBLOCKmut	pSEMAmut
#define ctDHBrqs	ctmutrqs
#define ctDHBclr	ctmutclr
#define DHB_rwl		mtx
#define DHB_RWL(loktyp)
#define DHB_RWCA(loktyp,ownr) ownr
#else
/*
** Data Hash Bin locks based on slim reader/writer locks (if available)
*/
#define pDHBLOCKmut	pRWLOCKmut
#define ctDHBrqs	ctRWLrqs
#define ctDHBclr	ctRWLclr
#define DHB_rwl		rwl
#define DHB_RWL(loktyp)	RWL(loktyp)
#define DHB_RWCA(loktyp,ownr) RWCA(loktyp,ownr)
#endif


#ifdef ctFeatNoIdxPndgList

#if	!defined(MULTITRD)		|| \
	!defined(ctHUGEFILE)		|| \
	!defined(ctBEHAV_BLM)		|| \
	!defined(ctFeatGNSEMAhsh)	|| \
	!defined(ctFeatAVLISTnum)	|| \
	!defined(ctFeatDISTbufcnt)	|| \
	!defined(ctFeatATOMICop)	|| \
	!defined(ctIOSEMAmemfile)

#error	ctFeatNoIdxPndgList support requirements not satisfied

#else

#if	!defined(NO_ctFeatIdxAdaptHashBinLocks) && \
	!defined(ctFeatIdxAdaptHashBinLocks)	&& \
	!defined(IHBxclmut)
#define ctFeatIdxAdaptHashBinLocks
#endif

#endif
#endif

#if	defined(ctFeatIdxAdaptHashBinLocks) && !defined(ctFeatNoIdxPndgList)
#error	ctFeatIdxAdaptHashBinLocks requires ctFeatNoIdxPndgList
#endif

#if	defined(ctFeatIdxAdaptHashBinLocks) && defined(IHBxclmut)
#error	ctFeatIdxAdaptHashBinLocks requires slim reader/writer locks
#endif

#if defined(ctBEHAV_MINIDXBUF) && !defined(ctFeatNoIdxPndgList)

#ifdef ctBEHAV_MINIDXBUFctopt2
/* If we turned on ctBEHAV_MINIDXBUF in ctopt2.h, turn it off. */
#undef ctBEHAV_MINIDXBUF
#else
/* Other code turned on ctBEHAV_MINIDXBUF: ERROR */
#error ctBEHAV_MINIDXBUF requires ctFeatNoIdxPndgList
#endif

#endif

#ifdef ctBEHAV_MINIDXBUF
/* Limit concurrency of ctgetnod81()/lrubuf81() calls if our traditional minimum
** index buffer requirement is not met. */
#define ctFeatMINIDXBUFsem

#ifdef ctDBGfcqa
#ifndef NO_ctFeatMINIDXBUFdbg
/* Enable debug options */
#define ctFeatMINIDXBUFdbg
#endif
#endif

/*
** ctGNCneeded() is used to check if we must acquire gncsema for a node request
** on the specified file.
*/
#ifdef ctFeatMEMFILE
/* gncsema is needed if getnod/lrubuf concurrency is being limited, and this
** connection has not already acquired gncsema, and the file is not a memory file. */
#define ctGNCneeded(ctnum) (ctgncsema_max && !(ctstat5 & CTSTAT5_MINIDXBUFSEM) && \
	!(ctnum->flmode2 & ctMEMFILE))
#else
/* gncsema is needed if getnod/lrubuf concurrency is being limited, and this
** connection has not already acquired gncsema. */
#define ctGNCneeded(ctnum) (ctgncsema_max && !(ctstat5 & CTSTAT5_MINIDXBUFSEM))
#endif

#endif

/**********************************************************************/

#ifdef ctFeatNoDatPndgList

#if	!defined(MULTITRD)		|| \
	!defined(ctHUGEFILE)		|| \
	!defined(ctBEHAV_BLM)		|| \
	!defined(ctBEHAV_DATPOScntl)	|| \
	!defined(ctFeatDBSEMAhsh)	|| \
	!defined(ctFeatDALISTnum)	|| \
	!defined(ctFeatATOMICop)	|| \
	!defined(ctFeatDISTdatcnt)

#error ctFeatNoDatPndgList support requirements not satisfied

#else

#if	!defined(NO_ctFeatDatEmptyList) && !defined(ctFeatDatEmptyList)
#define ctFeatDatEmptyList
#endif

#if	!defined(NO_ctFeatDatAdaptHashBinLocks) && \
	!defined(ctFeatDatAdaptHashBinLocks)	&& \
	!defined(DHBxclmut)
#define ctFeatDatAdaptHashBinLocks
#endif

#endif
#endif

#if	defined(ctFeatDatAdaptHashBinLocks) && !defined(ctFeatNoDatPndgList)
#error	ctFeatDatAdaptHashBinLocks requires ctFeatNoDatPndgList
#endif

#if	defined(ctFeatDatAdaptHashBinLocks) && defined(DHBxclmut)
#error	ctFeatDatAdaptHashBinLocks requires slim reader/writer locks
#endif

#if	defined(ctFeatDatEmptyList) && !defined(ctFeatNoDatPndgList)
#error	ctFeatDatEmptyList requires ctFeatNoDatPndgList
#endif

#ifdef ctFeatDatEmptyList
	/*
	** define number of extra empty sublists to avoid
	** undo contention when entire cache is becoming empty
	*/
#ifndef extraEmptyLists
#define extraEmptyLists		2
#endif
#else
#define extraEmptyLists		0
#endif

#if	defined(ctFeatNoDatPndgList)	&& \
	defined(ctFeatSCANCACHE)	&& \
	!defined(maxSCANCACHEpercent)
	/*
	** default compile-time max percentage of data cache
	** scan pages to 5%. at startup, the percentage defaults to 1% and
	** may be set any where from 0% to maxSCANCACHEpercent with
	** the configuration keyword SCAN_CACHE_PERCENT.
	*/
#define maxSCANCACHEpercent	5
#endif

/*
** debugging location macro for ChgBufStatusWordNewOld
*/
#ifdef ctDBGfcqa
#define cbsLOC(n)	,(n)
#else
#define cbsLOC(n)	/* loc */
#endif

/*
** debuging indicators for chkidxsemopn/chkdatsemopn routines
*/
#define semopnRQS	1
#define semopnCLR	2


/*--------------------------------------------------------------*/
/* ctFeatBATSIG causes sysiocod to be set to BTNO_COD on	*/
/* calls to BATSET/BATSETX that result in the current batch	*/
/* being closed. If the client application finds sysiocod set	*/
/* to BTNO_COD, then the application does not need to issue a	*/
/* BAT_CAN call before issuing a new batch request.		*/
/*								*/
/* For servers, this new behavior requires ctFeatBATSIG at	*/
/* compile-time AND the following server configuration entry:	*/
/*	COMPATIBILITY	BATCH_SIGNAL				*/
/*								*/
/* Default: ctFeatBATSIG is ON					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatBATSIG
#define ctFeatBATSIG
#endif


/*--------------------------------------------------------------*/
/* ctFeatSRVR_STRUCT causes many of the c-tree global variables */
/* to be assigned to a global structure. This is needed on the	*/
/* 64-bit Windows Itanium2 system in order to avoid a compile	*/
/* error (due to too many global variables) when building the	*/
/* c-treeSQL Server with debug symbols.				*/
/*								*/
/* Default: ctFeatSRVR_STRUCT is ON for 64-bit Windows Itanium	*/
/* compiles of the c-tree Server.				*/
/*--------------------------------------------------------------*/
#ifdef WIN64
#ifdef _IA64_
#ifdef ctSRVR
#ifndef NO_ctFeatSRVR_STRUCT
#define ctFeatSRVR_STRUCT
#endif
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatNODE_COUNTERS turns on counters, such as request and	*/
/* block counters, for the index buffers.			*/
/*								*/
/* Default: ctFeatNODE_COUNTERS is OFF for c-tree Server	*/
/* compiles.							*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#ifndef NO_ctFeatNODE_COUNTERS
/*
#define ctFeatNODE_COUNTERS
*/
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatDISTINCTkey enables an approximate count of the number	*/
/* of distinct key values in an index that allows duplicates. 	*/
/*								*/
/* This feature requires ctXTDLOG and ctBEHAV_PUTHDRcommit	*/
/* support (when TRANPROC is on).				*/
/*								*/
/* Default: ctFeatDISTINCTkey is ON when ctHUGEFILE is defined.	*/
/*--------------------------------------------------------------*/
#ifdef ctHUGEFILE
#ifndef NO_ctFeatDISTINCTkey
#define ctFeatDISTINCTkey
#endif
#endif

#ifdef ctFeatDISTINCTkey
#ifdef CTS_ISAM
#ifndef NO_ctFeatDISTINCTkeyseg
#define ctFeatDISTINCTkeyseg		/*
					** support partial key distinct
					** counts based on ISAM segments
					*/
#ifdef ctFeatDISTINCTkeysegDBG
#ifndef dsDBG
#define dsDBG	1			/* subscript for dstseg1[]	*/
#endif
#endif

#endif
#endif
#endif

#define ctMAXSEGdistinct	4	/* nbr of partial key distinct
					** counts maintained in the
					** index header. if ctFeatDISTINCTkeyseg
					** is not defined, space is still
					** reserved in the header.
					*/


/*--------------------------------------------------------------*/
/* ctFeatIO_BLOCK_SIZE enables support for the IO_BLOCK_SIZE	*/
/* configuration option, which breaks disk read and write	*/
/* operations into IO_BLOCK_SIZE-sized chunks.			*/
/*								*/
/* Default: ctFeatIO_BLOCK_SIZE is ON for c-tree Server	unless	*/
/* ctIOSEMAasync is enabled.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatIO_BLOCK_SIZE
#ifdef ctSRVR
#ifndef ctIOSEMAasync
#define ctFeatIO_BLOCK_SIZE
/*
** We turn on ctMAX_IO_SIZE to enable the I/O block size code in ctsdio_a.c.
** This code is controlled by #ifdef ctMAX_IO_SIZE for backward compatibility
** with the ctMAX_IO_SIZE feature that we originally implemented in standalone
** mode.
*/
#define ctMAX_IO_SIZE
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatLOKDYN turns on support for ctLOKDYN function.		*/
/* MULTITRD is required.					*/
/*								*/
/* Default: ctFeatLOKDYN is ON for c-tree Server		*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctFeatLOKDYN
#define ctFeatLOKDYN
#endif
#endif

#ifdef ctFeatLOKDYN
#ifndef MULTITRD
#undef ctFeatLOKDYN
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatTRANREPL turns on transactional replication support.	*/
/*								*/
/* We define transactional replication as one or more local	*/
/* c-tree Servers connecting to a master c-tree Server and	*/
/* using distributed transactions to update the master copy	*/
/* of c-tree data and index files when a client updates the	*/
/* local copy of the files.					*/
/*								*/
/* Default: ctFeatTRANREPL is ON for c-tree Server and		*/
/* replication agent.						*/
/*--------------------------------------------------------------*/
#if defined(ctSRVR) || defined(ctREPLAGENTcore)
#ifndef NO_ctFeatTRANREPL
#ifndef ctPortWINKE
#ifndef ctPortWINCE
#define ctFeatTRANREPL
#endif
#endif
#endif
#endif

/* Transactional replication requires huge file support */
#ifndef ctHUGEFILE
#undef ctFeatTRANREPL
#endif

/* Transactional replication requires replication support */
#ifndef ctFeatREPLICAT
#undef ctFeatTRANREPL
#endif


/*--------------------------------------------------------------*/
/* ctFeatLOGIDX_RECOVERY turns on LOGIDX processing during	*/
/* automatic recovery.						*/
/*								*/
/* Default: ctFeatLOGIDX_RECOVERY is ON by default.		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatLOGIDX_RECOVERY
#define ctFeatLOGIDX_RECOVERY
#endif


/*--------------------------------------------------------------*/
/* ctFeatLOCK_CACHE enables COMPATIBILITY LOCK_CACHE            */
/* which causes cache pages to be locked into physical memory   */
/* preventing the os from paging this portion of the server     */
/* Default: ctFeatLOCK_CACHE is OFF by default                  */
/*--------------------------------------------------------------*/
#ifndef ctPortPIM		/* Prairie Interactive Messaging */
#define NO_ctFeatLOCK_CACHE	/* activate for this customer */
#endif

#ifndef NO_ctFeatLOCK_CACHE
#ifdef  ctSRVR
#ifdef  ctPortUNIX
#define ctFeatLOCK_CACHE
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatIMPERSONATEtask turns on support for a connection	*/
/* impersonating another connection.				*/
/*								*/
/* Default: ctFeatIMPERSONATEtask is OFF by default for		*/
/* c-tree Server compiles.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatIMPERSONATEtask
#ifdef ctSRVR
/* #define ctFeatIMPERSONATEtask */
#endif
#endif

/* Impersonate task requires c-tree Server */
#ifndef ctSRVR
#undef ctFeatIMPERSONATEtask
#endif

/* Impersonate task requires ctThrds */
#ifndef ctThrds
#undef ctFeatIMPERSONATEtask
#endif


/*--------------------------------------------------------------*/
/* ctFeatTEMPLATE_COPY_OPT turns on support for a more		*/
/* efficient strategy for copying log template files.		*/
/*								*/
/* Default: ctFeatTEMPLATE_COPY_OPT is ON by default for	*/
/* c-tree Server compiles.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatTEMPLATE_COPY_OPT
#if defined (ctSRVR) || defined(ctBNDSRVR)
#define ctFeatTEMPLATE_COPY_OPT
#endif
#endif

/*
** The template copy sleep time is zero (off) by default. Use the
** LOG_TEMPLATE_COPY_SLEEP_TIME configuration option to change this setting.
*/
#define TEMPLATE_COPY_SLPTIM_DEFAULT  0

/*
** The template copy sleep percent is set to 15% by default. It is used
** only when the template copy sleep time is non-zero. Use the
** LOG_TEMPLATE_COPY_SLEEP_PCT configuration option to change this setting.
*/
#define TEMPLATE_COPY_SLPPCT_DEFAULT 15

#ifdef ctFeatTEMPLATE_COPY_OPT
#undef ctFeatWIN32_TEMPLATE_COPY
#endif


/*--------------------------------------------------------------*/
/* ctFeatDATFLTcallbackDLL turns on support for loading a	*/
/* filter callback DLL or shared library using the SETFLTR	*/
/* function.							*/
/*								*/
/* Default: ctFeatDATFLTcallbackDLL is ON by default for	*/
/* c-tree Server compiles.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatDATFLTcallbackDLL
#ifdef ctSRVR
#ifndef ctPortWINKE
#ifndef ctPortWINIOT
#define ctFeatDATFLTcallbackDLL
#endif
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatWORKcount turns on support for counting recursive	*/
/* calls to ctaddwork/ctrmvwork by a thread.			*/
/*								*/
/* Default: ctFeatWORKcount is ON by default for		*/
/* c-tree Server compiles.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatWORKcount
#ifdef ctSRVR
#define ctFeatWORKcount
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatFULL_DUMP turns on support for FULL_DUMP diagnostic	*/
/* keyword, which causes minidumps to create a full memory	*/
/* dump.							*/
/*								*/
/* Default: ctFeatFULL_DUMP is ON by default for Windows	*/
/* c-tree Server compiles.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatFULL_DUMP
#ifdef ctSRVR
#ifdef ctPortWIN32
#define ctFeatFULL_DUMP
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatREPL_SRLSEG turns on support for using an index that	*/
/* contains a SRLSEG segment as a replication unique index;	*/
/* and for writing the SRLSEG value set by the master server	*/
/* to the local server when adding a record to a replica. This	*/
/* support is disabled by default and can be enabled by		*/
/* specifying the following options in ctsrvr.cfg:		*/
/*								*/
/* REPL_SRLSEG_ALLOW_UNQKEY YES: allow an index that contains a	*/
/*	segment to be used as the replication unique index.	*/
/*								*/
/* REPL_SRLSEG_USE_MASTER YES: in the master/local replication	*/
/*	model, a local c-tree Server can use this option to	*/
/*	cause records added to local replicas to use the SRLSEG	*/
/*	value from the record added to the file on the master	*/
/*	c-tree Server.						*/
/*								*/
/* REPL_SRLSEG_USE_SOURCE YES: in the standard replication	*/
/*	model, a target c-tree Server can use this option to	*/
/*	cause records added to files by the replication agent	*/
/*	to use the SRLSEG value from the record on the source	*/
/*	c-tree Server.						*/
/*								*/
/* Default: ctFeatREPL_SRLSEG is ON by default for		*/
/* c-tree Server compiles.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatREPL_SRLSEG
#ifdef ctSRVR
#define ctFeatREPL_SRLSEG
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatREBUILD_CALLBACK_STATE turns on support for a rebuild	*/
/* callback state structure. During a rebuild operation, c-tree */
/* allocates memory for this structure if a rebuild callback	*/
/* function has been specified. The rebuild callback function	*/
/* can read the address of the callback	structure using the	*/
/* GETCBRBLST function.						*/
/*								*/
/* The rebuild callback structure provides additional		*/
/* information to the rebuild callback function, such as the	*/
/* high word of the record counter value; and it permits the	*/
/* rebuild callback function to set an error code in order to	*/
/* terminate the rebuild. The structure can be extended in the	*/
/* future to provide additional information to the rebuild	*/
/* callback function.						*/
/*								*/
/* In client/server mode the c-tree Server sends the rebuild	*/
/* callback structure data to the client process. The client	*/
/* process sends back only the rebuild callback return code.	*/
/*								*/
/* Default: ctFeatREBUILD_CALLBACK_STATE is ON by default for	*/
/* c-tree compiles.						*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatREBUILD_CALLBACK_STATE
#ifdef RB_CALLBACK
#define ctFeatREBUILD_CALLBACK_STATE
#endif
#endif

#ifdef ctFeatREBUILD_CALLBACK_STATE
#ifdef RB_CALLBACK_SRVR
/* srvrblcbfnc could fail with non-callback (e.g. communications) errors */
#define RCBERR(fnc,err) (((fnc)==srvrblcbfnc)?(err):RCBK_ERR) 
#else
#define RCBERR(fnc,err) RCBK_ERR
#endif
#define rblcbcntHW	ctGETHW64(rblcbcnt)
#define rblcbcntLW	ctGETLW64(rblcbcnt)
#define rblcbcntPCTd	ctLLd
#else
#define rblcbcntLW	rblcbcnt
#define rblcbcntPCTd	"%d"
#endif


/*--------------------------------------------------------------*/
/* ctFeatPARTITION_BY_TIMESTAMP_DAY turns on support for file	*/
/* partitioning using an 8-byte timestamp partition key. The	*/
/* partition number is the number of days elapsed since January	*/
/* 1, 1970.							*/
/*								*/
/* Default: ctFeatPARTITION_BY_TIMESTAMP_DAY is ON by default.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatPARTITION_BY_TIMESTAMP_DAY
#ifndef ctFeatPARTITION_BY_TIMESTAMP_DAY
#define ctFeatPARTITION_BY_TIMESTAMP_DAY
#endif
#ifndef NO_ctFeatPARTITION_BY_TIMESTAMP_DAY_GMT
#ifndef ctFeatPARTITION_BY_TIMESTAMP_DAY_GMT
#define ctFeatPARTITION_BY_TIMESTAMP_DAY_GMT
#endif
#endif
#endif

#ifndef ctFeatPARTITION_BY_TIMESTAMP_DAY
#ifdef  ctBEHAV_TIMESTAMP_SEG
#undef  ctBEHAV_TIMESTAMP_SEG
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatWINDOWS_LOCAL_FILE_TIME causes the partition key map	*/
/* function, kprawno(), to interpret the partition key value as	*/
/* an 8-byte timestamp that is the number of 100-nanosecond	*/
/* intervals since January 1, 1601, in the local time zone.	*/
/*								*/
/* NOTE: This #define only has an effect when the code is also	*/
/* compiled with #define ctFeatPARTITION_BY_TIMESTAMP_DAY. If	*/
/* the code is compiled with ctFeatPARTITION_BY_TIMESTAMP_DAY	*/
/* and without ctFeatWINDOWS_LOCAL_FILE_TIME, the partition key	*/
/* value is interpreted as a Unix timestamp.			*/
/*								*/
/* NOTE: This feature is only supported on Windows systems	*/
/* because it uses Windows API functions.			*/
/*								*/
/* Default: ctFeatWINDOWS_LOCAL_FILE_TIME is ON by default for	*/
/* Windows systems.						*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatWINDOWS_LOCAL_FILE_TIME
#ifdef ctFeatPARTITION_BY_TIMESTAMP_DAY
#ifdef ctPortWIN32
#ifndef ctFeatWINDOWS_LOCAL_FILE_TIME
#define ctFeatWINDOWS_LOCAL_FILE_TIME
#endif
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatTRANSFER_FILE turns on support for the file transfer	*/
/* API function ctTransferFile(). A client can use this		*/
/* function to send a file to or receive a file from a c-tree	*/
/* Server.							*/
/*								*/
/* Default: ctFeatTRANSFER_FILE is ON by default for c-tree	*/
/* client and server compiles.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatTRANSFER_FILE
#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB) || defined(ctSRVR)
#define ctFeatTRANSFER_FILE
#endif
#endif

/*
** If the c-tree server is built without communication protocol
** support, disable the file transfer feature.
*/
#ifdef ctSRVR
#ifndef ctFeatCTSRVR_COMMP
#undef ctFeatTRANSFER_FILE
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatDATFLT_DEFER_CALLBACK turns on support for deferring	*/
/* calls to data filter callback functions. Filter callback	*/
/* functions must be deferred until the completion of file	*/
/* open/close operations so that calls to c-tree functions made */
/* by the filter callback functions do not interfere with the	*/
/* original c-tree file open/close operation.			*/
/*								*/
/* Default: ctFeatDATFLT_DEFER_CALLBACK is ON by default for	*/
/* c-tree Server compiles.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatDATFLT_DEFER_CALLBACK
#ifdef ctFeatDATFLT
#ifdef ctSRVR
#define ctFeatDATFLT_DEFER_CALLBACK
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatUDF_EXPR turns on support for "User Defined Functions" */
/* feature. It will be available only with the "CTDB Expression */
/* Evaluation" (CTDB_EXPR_EVAL) feature. It is because we	*/
/* cannot assure that the function pointer will be available	*/
/* when it is set in the client and executed by the server, or	*/
/* if it is used for a conditional index expression.		*/
/*								*/
/* Default: ctFeatUDF_EXPR is ON by default for	c-tree		*/
/* compiles.							*/
/*--------------------------------------------------------------*/
#ifndef ctPortWINKE_CLIENT
#ifndef NO_ctFeatUDF_EXPR
#define ctFeatUDF_EXPR
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatSEQNUM turns on support for the c-tree sequence number	*/
/* API functions.						*/
/*								*/
/* Default: ctFeatSEQNUM is ON for c-tree Server in v9.6 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatSEQNUM
#ifdef ctHUGEFILE
#if ctVER_GE(9,6)
#ifdef ctSRVR
#define ctFeatSEQNUM
#endif
#endif
#endif
#endif


/*----------------------------------------------------------------------------
   ctFeatSEQNUM_FORMAT2 enables version 2 of the sequence data file format,
   which adds a delete flag padding field at the start of the sequence
   record. At server startup, the old sequence file format is converted to
   the new sequence file format.

   Enabled in v11.3.1 and later
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1)
#ifndef NO_ctFeatSEQNUM_FORMAT2
#define ctFeatSEQNUM_FORMAT2
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPLENG_LOCK_RETRY turns on support for the replication*/
/* agent's record read lock retry count and record read lock	*/
/* retry sleep options.						*/
/*								*/
/* DEFAULT:  ctFeatREPLENG_LOCK_RETRY is on by default for	*/
/* non-server compiles.						*/
/*--------------------------------------------------------------*/
#ifndef MULTITRD
#define ctFeatREPLENG_LOCK_RETRY
#endif


/*--------------------------------------------------------------*/
/* ctFeatTR_RDIF_ERRrstlok turns on support for restoring the	*/
/* lock state of local and master records to their state before	*/
/* the current record read operation when the current record	*/
/* read operation fails with error TR_RDIF_ERR.			*/
/*								*/
/* DEFAULT:  ctFeatTR_RDIF_ERRrstlok is ON by default.		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatTR_RDIF_ERRrstlok
#define ctFeatTR_RDIF_ERRrstlok
#endif

/*--------------------------------------------------------------*/
/* ctFeatW32HEAPalloc causes c-tree's memory suballocator to	*/
/* create and use a separate heap for each suballocator list.	*/
/* The heaps are created without mutex control because the	*/
/* memory suballocator serializes access to a heap.		*/
/*								*/
/* Default: ctFeatWINHEAPalloc is ON for server compiles on	*/
/* Windows systems except Windows CE and kernel.		*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#ifndef NO_ctFeatWINHEAPalloc
#ifdef ctPortWIN32
#ifndef ctPortWINCE
#ifndef ctPortWINKE
#define ctFeatWINHEAPalloc
#endif
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatMEMSUBX turns on support for multiple suballocator	*/
/* lists hashed based on sOWNR.	 This is intended to reduce	*/
/* contention on the individual lists.	This allows the		*/
/* number of suballocator lists to be controlled with the	*/
/* server keyword MEMORY_HASH					*/
/*								*/
/* Default: ctFeatMEMSUBX is on by default for 64 bit		*/
/*  c-tree Server compiles or servers with alignment >= 8 	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatMEMSUBX
#ifdef ctSRVR
#if (ctMEMALIGN >= 8)
#define ctFeatMEMSUBX
#elif defined(ctMEMALIGN8)
#define ctFeatMEMSUBX
#elif defined(ct8P)
#define ctFeatMEMSUBX
#else
/*
** Indicate that we did not turn on MEMORY_HASH support because
** the memory alignment requirements are not met.
*/
#define ctFeatMEMSUBX_NSUP
#endif
#endif
#endif

#ifndef ctFeatMEMSUBX
#define ctmem_bin 1
#endif


/*--------------------------------------------------------------*/
/* ctFeatVFYIDX_CS turns on support for the index verify	*/
/* function in client/server mode.				*/
/*								*/
/* Default: ctFeatVFYIDX_CS is ON by default. 			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatVFYIDX_CS
#define ctFeatVFYIDX_CS
#endif

/*
** The bound server model does not support the client/server
** index verify function.
*/
#ifdef ctFeatVFYIDX_CS
#ifdef ctBNDSRVR
#undef ctFeatVFYIDX_CS
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatDAR turns on support for Direct Access Resources	*/
/*								*/
/* Default: ctFeatDAR is on by default if ctHUGEFILE, ctXTDLOG	*/
/* and RESOURCE are enabled.					*/
/*								*/
/* NOTES:							*/
/*								*/
/* 1) The ctCLISIDE check below is intended to allow DAR	*/
/*    support when compiling the c-tree client code in the	*/
/*    LOCLIB model.						*/
/*								*/
/* 2) ctXTDLOG is only a requirement for TRANPROC compiles.	*/
/*								*/
/* DAR requires ctHUGEFILE					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatDAR
#ifdef ctHUGEFILE
#ifdef RESOURCE
/* NOTE: We check the other ctFeatDAR requirements later. */
#define ctFeatDAR
/* Indicate that we turned on ctFeatDAR in ctopt2.h: */
#define ctFeatDARctopt2
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatBLOCKCACHE enables sector aligned cache pages on win32 */
/* allocated in a single contiguous block.			*/
/*								*/
/* Default: ctFeatBLOCKCACHE is OFF by default. 		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatBLOCKCACHE
#ifdef ctPortWIN32
#ifdef ctSRVR
/* #define ctFeatBLOCKCACHE */
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatNOBUFFERING enables support for unbuffered I/O on	*/
/* Windows systems. Unbuffered I/O operations must be aligned	*/
/* sector boundaries, and in multiples of the sector size.  The */
/* memory being written to/from must also be sector aligned.	*/
/*								*/
/* Default: ctFeatNOBUFFERING is ON for c-tree Server compiles	*/
/* on Windows systems (except for Windows CE and the Windows	*/
/* kernel) and on Linux systems.		 		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatNOBUFFERING
#ifdef ctPortWIN32
#ifndef ctPortWINCE
#ifndef ctPortWINKE
#ifndef ctPortWINIOT
#ifdef ctSRVR
#define ctFeatNOBUFFERING
#define ctFeatBLOCKCACHE
#endif
#endif
#endif
#endif
#endif

#ifdef ctPortLINUX
#ifdef ctSRVR
#define ctFeatNOBUFFERING
#define ctFeatBLOCKCACHE
#endif
#endif

#endif

#ifdef ctFeatNOBUFFERING

/* only supported on Windows systems */
#ifndef ctPortWIN32
#ifndef ctPortLINUX
#error ctFeatNOBUFFERING is only supported on Windows and Linux systems
#endif
#endif

/* only supported for c-tree Server operational model */
#ifndef ctSRVR
#error ctFeatNOBUFFERING is only supported for the c-tree Server
#endif

/* requires ctFeatBLOCKCACHE */
#ifndef ctFeatBLOCKCACHE
#error ctFeatNOBUFFERING requires ctFeatBLOCKCACHE
#endif

#endif


/*--------------------------------------------------------------*/
/* ctFeatDEFER_OPNTRAN defers the assignment of a transaction	*/
/* file number to a transaction-controlled file until the file	*/
/* is updated.							*/
/*								*/
/* Default: ctFeatDEFER_OPNTRAN is ON for c-tree Server		*/
/* compiles.							*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatDEFER_OPNTRAN
#ifdef ctFeatREADSHARE
#define ctFeatDEFER_OPNTRAN
#endif
#endif

/* This feature requires ctFeatREADSHARE (which requires MULTITRD) */
#ifndef ctFeatREADSHARE
#undef ctFeatDEFER_OPNTRAN
#endif

/* only define for TRANPROC compiles */
#ifndef TRANPROC
#ifdef ctFeatDEFER_OPNTRAN
#undef ctFeatDEFER_OPNTRAN
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_TFLSEMA uses a dedicated mutex to control access to	*/
/* the "global" tfil counter.					*/
/*								*/
/* NOTE: THIS IS TO AVOID POSSIBLE DEADLOCKS BETWEEN OCSEMA AND */
/* LOGSEMA AND/OR DOTSEMA.					*/
/*								*/
/* ctBEHAV_TFLSEMA requires MULTITRD				*/
/*								*/
/* DEFAULT:  ctBEHAV_TFLSEMA is on by default when either	*/
/* ctFeatLOGTEMPLATE and/or ctFeatDEFER_OPNTRAN	are defined	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctBEHAV_TFLSEMA
#ifdef MULTITRD
#if defined(ctFeatLOGTEMPLATE) || defined(ctFeatDEFER_OPNTRAN)
#define ctBEHAV_TFLSEMA
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatREMBUFADR stores the address of the index buffer that	*/
/* holds the current index node.				*/
/*								*/
/* Default: ctFeatREMBUFADR is ON for c-tree Server compiles.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatREMBUFADR
#ifdef TRANPROC
#ifdef MULTITRD
#define ctFeatREMBUFADR
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatOPEN_SHARE_RDONLY causes the c-tree Server to open all	*/
/* files with read-only share permissions on Windows systems.	*/
/*								*/
/* Default: ctFeatOPEN_SHARE_RDONLY is ON for c-tree Server	*/
/* compiles.					 		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatOPEN_SHARE_RDONLY
#ifdef ctSRVR
#ifdef ctPortWIN32
#define ctFeatOPEN_SHARE_RDONLY
#endif
#endif
#endif

/* This feature requires ctFeatREADSHARE (which requires MULTITRD) */
#ifndef ctFeatREADSHARE
#undef ctFeatOPEN_SHARE_RDONLY
#endif


/*--------------------------------------------------------------*/
/* ctFeatFNAC_ERR causes c-tree to return error	FNAC_ERR when a	*/
/* file cannot be opened if the file exists but is not		*/
/* accessible.							*/
/*								*/
/* Default: ctFeatFNAC_ERR is ON.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatFNAC_ERR
#ifndef ctPortWINKE
#define ctFeatFNAC_ERR
#endif
#endif


/*---------------------------------------------------------*/
/* ctFeatCNDX_V9_NOSCHEMA turns on support for conditional */
/* expression without enforcing the existence of a DODA on */
/* the data file.                                          */
/* When the DODA is not available instead of returning the */
/* CMIS_ERR error, c-tree make an attempt to compile the   */
/* expression, if the expression contains fields reference,*/
/* the compilation fails with error CINI_ERR               */
/*				                           */
/* Default: ctFeatCNDX_V9_NOSCHEMA is ON                   */
/*---------------------------------------------------------*/
#ifndef NO_ctFeatCNDX_V9_NOSCHEMA
#define ctFeatCNDX_V9_NOSCHEMA
#endif

/* This feature requires ctFeatCNDX_V9 */
#ifndef ctFeatCNDX_V9
#ifdef ctFeatCNDX_V9_NOSCHEMA
#undef ctFeatCNDX_V9_NOSCHEMA
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatDATFLTmulti enables support for multiple data record	*/
/* filters per file.						*/
/*								*/
/* Default: ctFeatDATFLTmulti is ON for c-tree Server compiles.	*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#ifndef NO_ctFeatDATFLTmulti
#ifndef ctFeatDATFLTmulti
#define ctFeatDATFLTmulti
#endif
#endif
#endif
/*-------------------*/


/*--------------------------------------------------------------*/
/* ctFeatADMIN_SECURITY tightens the security restrictions on	*/
/* FAIRCOM.FCS. When this feature is enabled, the settings for	*/
/* the ADMIN user account and for accounts that are members of	*/
/* the ADMIN group can only be changed by the ADMIN user, with	*/
/* the following exception: any user account can change its own	*/
/* description and password.					*/
/*								*/
/* Default: ctFeatADMIN_SECURITY is ON for v9.6 and later	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatADMIN_SECURITY
#if ctVER_GE(9,6)
#define ctFeatADMIN_SECURITY
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatVSSWRITERsrv enables the Volume Shadow Copy Service	*/
/* running as a thread in the c-tree Server.			*/
/*								*/
/* Default: ctFeatVSSWRITERsrv is ON for c-tree Server on	*/
/* Windows systems.						*/
/*--------------------------------------------------------------*/

#ifndef NO_ctFeatVSSWRITERsrv
#ifdef ctPortWIN32
#ifndef ctPortWINCE
#ifndef ctPortWINKE
#ifdef ctSRVR
#define ctFeatVSSWRITERsrv
#endif
#endif
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatSHAREstate tracks the number of opens for a file that	*/
/* prevent write access to a file in order to improve c-tree's	*/
/* read-only sharing and adds a new sharing mode in which the	*/
/* opener is granted read/write access and other openers are	*/
/* only allowed read access.					*/
/*								*/
/* Default: ctFeatSHAREstate is ON for c-tree Server and	*/
/* c-tree client for v9.6 and later.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatSHAREstate
#if defined(ctSRVR) || defined(ctCLIENT) || defined(ctMTCLIENT)
#if ctVER_GE(9,6)
#define ctFeatSHAREstate
#endif
#endif
#endif

/* For c-tree Server, ctFeatSHAREstate requires ctFeatREADSHARE support. */
#if defined(ctSRVR) && !defined(ctFeatREADSHARE)
#undef ctFeatSHAREstate
#endif

/* For c-tree client, ctFeatSHAREstate requires ctBEHAV_CTREErecurcnt support. */
#if (defined(ctCLIENT) || defined(ctMTCLIENT)) && !defined(ctBEHAV_CTREErecurcnt)
#undef ctFeatSHAREstate
#endif

/*
** ctFeatSHAREstate requires huge file support because the client uses pblg2
** to pass the extended file mode to the c-tree Server.
*/
#ifndef ctHUGEFILE
#undef ctFeatSHAREstate
#endif


/*--------------------------------------------------------------*/
/* ctFeatXTDUSRCNT supports two new user file counters:		*/
/*	actusrcnt and thdusrcnt					*/
/*								*/
/* actusrcnt is the actual number of current user opens; it	*/
/* does not include KEEPOPENs. thsudrcnt is the number of	*/
/* threads that have the file open, which will be less than	*/
/* actusrcnt if one or more threads have opened the file	*/
/* more than once (i.e., as co-files).				*/
/*								*/
/* This feature is required for COBOL support.			*/
/*								*/
/* Default: ctFeatXTDUSRCNT is ON for c-tree Server for	v10.5	*/
/* and later, and for c-tree Server v10.3 and later when COBOL	*/
/* support is enabled.						*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctFeatXTDUSRCNT) && defined(MULTITRD) && \
    (ctVER3_GE(10,4,1) || ctVER3_GE(10,3,0) && defined(ctFeatCOBOL))
#define ctFeatXTDUSRCNT
#endif
#if defined(ctFeatXTDUSRCNT) && !defined(MULTITRD)
#undef ctFeatXTDUSRCNT
#endif


/*--------------------------------------------------------------*/
/* ctFeatCOFILE_FILELOCK supports ctXOPN_COFILE_FILELOCK which	*/
/* permits co-file opens with conflicting file modes as long	*/
/* as the open does not conflict with another thread's open(s).	*/
/*								*/
/* This feature is required for COBOL support.			*/
/*								*/
/* Default: ctFeatCOFILE_FILELOCK is ON for c-tree Server for	*/
/* v10.5 and later, and for c-tree Server v10.3 and later when	*/
/* COBOL support is enabled.					*/
/*--------------------------------------------------------------*/
#if !defined(NO_ctFeatCOFILE_FILELOCK) && \
    (ctVER3_GE(10,4,1) || ctVER3_GE(10,3,0) && defined(ctFeatCOBOL))
#if defined(ctFeatSHAREstate) && defined(ctBEHAV_MULTIOPN_LINK) && \
    defined(ctFeatXTDUSRCNT)
#define ctFeatCOFILE_FILELOCK
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatRCV_DETECT_INACCESSIBLE_FILES enables automatic	*/
/* recovery to detect that a file exists but is inaccessible.	*/
/* By default, when a file needed by automatic recovery is	*/
/* inaccessible, automatic recovery will fail, but the		*/
/* configuration option	SKIP_INACCESSIBLE_FILES YES (or the	*/
/* global variable ctskpiaf in standalone mode) can be used	*/
/* to skip files that are inaccessible during automatic		*/
/* recovery.							*/
/*								*/
/* Default: ctFeatRCV_DETECT_INACCESSIBLE_FILES is ON when	*/
/* transaction control is supported.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatRCV_DETECT_INACCESSIBLE_FILES
#ifdef TRANPROC
#define ctFeatRCV_DETECT_INACCESSIBLE_FILES
#endif
#endif



/*--------------------------------------------------------------*/
/* ctFeatLSTAVLptr enables an organizing principle for the	*/
/* linked list of suballocator memory lists (chunks): lists	*/
/* with available space are placed at the demarcation point	*/
/* (la->ancdiv). Lists that do not have available space and	*/
/* new lists are placed just before the demarcation point.	*/
/*								*/
/* Default: ctFeatLSTAVLptr is ON enabled.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatLSTAVLptr
#ifdef ctBEHAV_MEMSUB
#define ctFeatLSTAVLptr
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatHandlerEx enables the windows service Extended handler.*/
/* This allows the use of the SERVICE_CONTROL_PRESHUTDOWN	*/
/* notification to allow longer shutdown times.			*/
/*								*/
/* Default: ctFeatHANDLER_EX is ON for windows servers in	*/
/* version 10.0 and later.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatHANDLER_EX
#ifdef ctPortWIN32
#ifdef ctSRVR
#ifndef ctPortWINCE_SRVR
#if _MSC_VER >= 1500
#if ctVER_GE(10,0)
#define ctFeatHANDLER_EX
#endif
#endif
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatDNODEQindex enables an index on the entries in the	*/
/* delete node queue.						*/
/*								*/
/* Default: ctFeatDNODEQindex is OFF for c-tree Server when	*/
/* memory files and the delete node queue shutdown limit are	*/
/* supported.							*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#ifdef ctFeatMEMFILE
#ifdef ctFeatDNODEQ_SHUTDOWN_LIMIT
#ifndef NO_ctFeatDNODEQindex
/* #define ctFeatDNODEQindex */
#endif
#endif
#endif
#endif

#ifdef ctFeatDNODEQindex
#error The ctFeatDNODEQindex feature must be corrected before it can be enabled
#endif

/*--------------------------------------------------------------*/
/* ctFeatSHMEMspin enables spinning in the shared memory	*/
/* communication receive function while waiting for the peer	*/
/* to release the semaphore that indicates that the data is	*/
/* ready to read.						*/
/*								*/
/* Default: ctFeatSHMEMspin is ON for Windows compiles.		*/
/*--------------------------------------------------------------*/
#ifdef ctPortWIN32
#ifndef NO_ctFeatSHMEMspin
#define ctFeatSHMEMspin
#endif
#endif


#if defined(ctPortUNIX) && !defined(NO_ctFeatSHMEMspin)

/*
** Turn on support for shared memory spin on Unix systems.
*/
#define ctFeatSHMEMspin

/*
** On Unix systems, we support the shared memory spin only if the
** system supports atomic operations (either in all models or at
** least in our server model).
*/
#if !defined(ctFeatATOMICop) && !defined(ctFeatATOMICopSRVR)
#undef ctFeatSHMEMspin
#endif

/* Shared memory spin version 2 requires atomic operation support for both client and server. */
#if (ctVER3_GE(11,5,0) || (ctVER3_GE(11,2,3) && defined(ctPortRTG))) && defined(ctFeatATOMICop) && !defined(NO_ctFeatSHMEMspin2)

#define ctFeatSHMEMspin2

#endif /* check spin2 requirements */

#endif /* ctPortUNIX && ~NO_ctFeatSHMEMspin */

/*--------------------------------------------------------------*/
/* ctFeatABEND_ABORT enables the DIAGNOSTICS ABEND_ABORT 	*/
/* keyword, which causes a process abort in abnormal shutdown 	*/
/* conditions.							*/
/*								*/
/* Default: ctFeatABEND_ABORT is ON for non-windows		*/
/* server compiles						*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#ifndef NO_ctFeatABEND_ABORT
#ifndef ctPortWIN32
#define ctFeatABEND_ABORT
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctMULTIOPNerror fails multiple file opens of the same file	*/
/* by a (single) thread using different user file numbers. Such	*/
/* a multiple open attempt returns the MUOP_ERR(871).		*/
/*								*/
/* DEFAULT: ctMULTIOPNerror is off.				*/
/*--------------------------------------------------------------*/
/*
** #define ctMULTIOPNerror
*/

/*--------------------------------------------------------------*/
/* ctMULTIOPN supports multiple file opens of the same file by	*/
/* a (single) thread using different user file numbers. The	*/
/* main issues are the reverse mapping between a system file	*/
/* number and the user file number; and the management of the	*/
/* lock tables.							*/
/*								*/
/* The code previously permitted these multiple opens, but	*/
/* without proper support.					*/
/*								*/
/* DEFAULT: ctMULTIOPN is defined (with MULTITRD, but requires	*/
/* ctFeatFILEUSRLST && ctBEHAV_ULCNT && !ctMULTIOPNerror)	*/
/*--------------------------------------------------------------*/
#ifdef MULTITRD
#ifndef NO_ctMULTIOPN
#define ctMULTIOPN
#endif
#endif

#ifdef ctMULTIOPN
#if (!defined(ctFeatFILEUSRLST) || !defined(ctBEHAV_ULCNT) || defined(ctMULTIOPNerror) || !defined(MULTITRD))
#undef ctMULTIOPN
#endif
#endif

#if defined(MULTITRD) && defined(ctBEHAV_CHKFUPD) && !(defined(ctMULTIOPN) || defined(ctMULTIOPNerror))
/* cannot support ctBEHAV_CHKFUPD */
#undef ctBEHAV_CHKFUPD
#endif

#if defined(ctBEHAV_MULTIOPN_LINK) && !defined(ctMULTIOPN)
#undef ctBEHAV_MULTIOPN_LINK
#endif

#ifdef ctBEHAV_MULTIOPN_LINK
#if ctVER3_GE(10,5,0)
/* Use co-file links to efficiently check if file has deferred close under different user filno */
#define ctBEHAV_CHKDFROPN_COFILE
#endif
#endif

#if defined(ctBEHAV_MULTIOPN_DIFUSR) && !defined(ctMULTIOPN)
#undef ctBEHAV_MULTIOPN_DIFUSR
#endif

#if defined(ctBEHAV_MULTIOPN_SAMUSR) && !defined(ctMULTIOPN)
#undef ctBEHAV_MULTIOPN_SAMUSR
#endif

#ifndef ctBEHAV_MULTIOPN_SAMUSR
#undef ctBEHAV_MULTIOPN_SAMUSR_M_FREE
#undef ctBEHAV_MULTIOPN_SAMUSR_M_FREE_FILE
#endif

#if defined(ctBEHAV_MULTIOPN_DIFUSRfile) && !defined(ctBEHAV_MULTIOPN_DIFUSR) && !defined(ctBEHAV_MULTIOPN_SAMUSR)
#undef ctBEHAV_MULTIOPN_DIFUSRfile
#endif

#if defined(ctBEHAV_MULTIOPN_LINK) && !defined(ctLIMITmltlnk)
#define ctLIMITmltlnk	1024	/* maximum limit on co-file links */
#endif

#if defined(ctFeatCOFILE_FILELOCK) && (!defined(ctBEHAV_MULTIOPN_LINK)	|| \
				       !defined(ctFeatXTDUSRCNT)	|| \
				       !defined(ctFeatSHAREstate))
#undef ctFeatCOFILE_FILELOCK
#endif

#ifdef ctFeatCOFILE_FILELOCK
/*
** file mode levels from most to least restrictive
*/
#define ctFileModeRWNO		1	/* ctEXCLUSIVE			*/
#define ctFileModeRWRO		2	/* ctSHARED+ctXOPN_REDSHR	*/
#define ctFileModeRORO		3	/* ctREADFIL			*/
#define ctFileModeRWRW		4	/* ctSHARED			*/
#define ctFileModeRORW		5	/* ctREADFIL|ctSHARED		*/

#define	ctFileModeLevels	6
/*
** indicator placeholders when fu->filmodlev not assigned
*/
#define ctFileModeINIT		-1	/* not assigned yet		*/
#define ctFileModeMMBR		-2	/* index member			*/
#endif


/*--------------------------------------------------------------*/
/* ctFeatIICT enables support for Immediate Independent Commit	*/
/* Transactions (IICT). An IICT permits a thread in the middle	*/
/* of a transaction to issue an independent transaction based	*/
/* on a single ISAM operation that is committed immediately.	*/
/* Such an IICT behaves as if it has been submitted by a	*/
/* separate thread.						*/
/*								*/
/* Default: ctFeatIICT is ON by default in v9.6 and later.	*/
/* ctFeatIICT has not been implemented for single user mode.	*/
/*--------------------------------------------------------------*/
#if ctVER_GE(9,6) || defined(ctFeatCOBOL)
#ifndef NO_ctFeatIICT
#define ctFeatIICT
#endif
#endif

#ifdef  ctPortDSTINTL	/* Per performace tests on 131111 */
#ifndef ctPortRTG	/* ctPortDSTINTL_ONLY_QUESTION */
#undef  ctFeatIICT	/* We do not turn on IICT for DSTINTL standard (non-COBOL) gens */
#endif
#endif

#if !(defined(MULTITRD) && defined(ctCACHE_MEMORY) && defined(ctHUGEFILE) && defined(ctDYNHASH) && defined(ctBEHAV_USRSEMA) && defined(TRANPROC) && defined(ctMULTIOPN) && defined(CTS_ISAM))
			/* required support not enabled */
#ifdef ctFeatIICT
#undef ctFeatIICT
#endif
#endif			/* required support not enabled */

#define IICTbins	32	/* starting hash bins for temporary	**
				** pre-image space			*/

/*--------------------------------------------------------------*/
/* ctFeatMEMTRACK enables the c-tree Server to track all the	*/
/* memory allocations made through the memory suballocator.	*/
/*								*/
/* Default: ctFeatMEMTRACK is ON for server compiles on Windows	*/
/* and Linux kernel 2.6 and later systems.			*/
/*--------------------------------------------------------------*/

#ifdef ctSRVR
#ifndef NO_ctFeatMEMTRACK
#if (defined(ctPortWIN32) && _MSC_VER > 1400) || (defined(ctPortLINUX) && !defined(ctPort_LINUX_KERNEL_V2_4))
#ifndef ctPortWINKE
#ifndef ctPortWINCE
#ifndef ctPortFREEBSD8
#ifndef ctPort386BSD
#ifndef ctPortWINIOT
#define ctFeatMEMTRACK
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatSHDLST causes preimage space entries to be allocated	*/
/* using c-tree's memory suballocator so that they can take	*/
/* advantage of the MEMORY_HASH feature.			*/
/*								*/
/* Default: ctFeatSHDLST is ON for c-tree Server compiles when	*/
/* multiple memory suballocator list support and transaction	*/
/* control support are enabled.					*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#ifdef ctFeatMEMSUBX
#ifdef TRANPROC
#ifndef NO_ctFeatSHDLST
#define ctFeatSHDLST
#endif
#endif
#endif
#endif

/* ctFeatSHDLST requires c-tree Server */
#ifndef ctSRVR
#undef ctFeatSHDLST
#endif

/* ctFeatSHDLST requires MEMORY_HASH support (otherwise no benefit to it) */
#ifndef ctFeatMEMSUBX
#undef ctFeatSHDLST
#endif

/* ctFeatSHDLST requires TRANPROC support (otherwise no benefit to it) */
#ifndef TRANPROC
#undef ctFeatSHDLST
#endif

/*--------------------------------------------------------------*/
/* ctFeatBATLST causes batched records to be allocated	*/
/* using c-tree's memory suballocator so that they can take	*/
/* advantage of the MEMORY_HASH feature.			*/
/*								*/
/* Default: ctFeatBATLST is ON for c-tree Server compiles when	*/
/* multiple memory suballocator list support			*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#ifdef ctFeatMEMSUBX
#ifdef TRANPROC
#ifndef NO_ctFeatBATLST
#define ctFeatBATLST
#endif
#endif
#endif
#endif

/* ctFeatBATLST requires c-tree Server */
#ifndef ctSRVR
#undef ctFeatBATLST
#endif

/* ctFeatBATLST requires MEMORY_HASH support (otherwise no benefit to it) */
#ifndef ctFeatMEMSUBX
#undef ctFeatBATLST
#endif

/*--------------------------------------------------------------*/
/* ctFeatTRAN_OVERFLOW_THRESHOLD enables a server keyword to	*/
/* log a warning message to CTSTATUS.FCS when the server's	*/
/* current transaction number exceeds a user-defined value.	*/
/*								*/
/* Default: ctFeatTRAN_OVERFLOW_THRESHOLD is ON for c-tree	*/
/* Server compiles when	transaction control support is enabled.	*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#ifdef TRANPROC
#ifdef ctFeatCFG_SCALE_N8
#ifndef NO_ctFeatTRAN_OVERFLOW_THRESHOLD
#define ctFeatTRAN_OVERFLOW_THRESHOLD
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatLOGONSEC enhances the security of passwords passed to	*/
/* the c-tree Server when connecting.				*/
/*								*/
/* Default: ctFeatLOGONSEC is ON for v9.6 and later when c-tree */
/* encryption support is enabled.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatLOGONSEC
#if ctVER_GE(9,6)
#ifndef ctNO_CAMO
#ifndef ctFeatLOGONSEC
#define ctFeatLOGONSEC
#endif
#endif
#endif
#endif

/*
** This feature is supported for client and server models only, so we turn it
** off for other operational models.
*/
#ifndef ctCLIENT
#ifndef ctCLISIDE
#ifndef ctMTCLIENT
#ifndef ctSRVR
#ifdef ctFeatLOGONSEC
/* Remember that ctFeatLOGONSEC was on and we turned it off. */
#define UNDEF_ctFeatLOGONSEC
#endif
#undef ctFeatLOGONSEC
#endif
#endif
#endif
#endif

#ifdef ctFeatLOGONSEC
/* We require secure logons: the SECURE_LOGONS_ONLY NO option is not supported. */
#define ctFeatLOGONSECrequired
#endif

#ifndef ctCAMOsdk
#ifdef ctFeatLOGONSEC
#error ctFeatLOGONSEC requires ctCAMOsdk
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatVLEN_ERRretry enables a configurable retry when an	*/
/* ISAM variable-length record add or update fails with error	*/
/* VLEN_ERR.							*/
/*								*/
/* Default: ctFeatVLEN_ERRretry is OFF. Requires c-tree Server.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatVLEN_ERRretry
#ifdef ctSRVR
/* #define ctFeatVLEN_ERRretry */
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatSRLSEGreassign enables the ability for a file compact	*/
/* operation to assign new serial numbers to the records in the	*/
/* compacted file.						*/
/*								*/
/* Default: ctFeatSRLSEGreassign is ON.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatSRLSEGreassign
#define ctFeatSRLSEGreassign
#endif

/*--------------------------------------------------------------*/
/* ctFeatESTIMATE_SCALE changes ESTKEY behavior to increase	*/
/* the number of interations in binsrc as the number of records	*/
/* grows to maintain an approx. constant estimate precision.    */
/*								*/
/* Default: ctFeatESTIMATE_SCALE is ON. Requires c-tree Server.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatESTIMATE_SCALE
#ifdef ctSRVR
#ifdef ctHUGEFILE
#define ctFeatESTIMATE_SCALE
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatFILEupdpag tracks the number of updated cache pages  	*/
/* for each c-tree data file.					*/
/*								*/
/* Default: ctFeatFILEupdpag is ON. Requires c-tree Server and	*/
/* support for atomic operations.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatFILEupdpag
#ifdef ctSRVR
#ifdef ctFeatATOMICop
#define ctFeatFILEupdpag
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatFILEupdbuf tracks the number of updated index buffers	*/
/* for each c-tree index file.					*/
/*								*/
/* Default: ctFeatFILEupdbuf is ON in v11.9.5 and later.	*/
/* Requires c-tree Server and support for atomic operations.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatFILEupdbuf
#if defined(ctSRVR) && defined(ctFeatATOMICop)
#define ctFeatFILEupdbuf
#endif
#endif
#endif

#ifdef ctFeatFILEupdbuf
/* Increment the count of updated index buffers for the file that is associated with the specified index buffer. */
#define INCREMENT_UPDBUFCNT(buffer,check) { \
	pCTFILE hnum = (buffer)->keynm->hmem; \
	if (!(hnum->flmode2 & ctMEMFILE)) { \
		CTASSERT((buffer)->update != 'y'); \
		ctInterlockedIncrement32(hnum->updidxbuf); \
		if (check) { \
			CTASSERT(hnum->updidxbuf <= (ULONG) hnum->bufcnt); \
		} \
	} \
}
/* Decrement the count of updated index buffers for the file that is associated with the specified index buffer. */
#define DECREMENT_UPDBUFCNT(buffer) { \
	pCTFILE hnum = (buffer)->keynm->hmem; \
	if (!(hnum->flmode2 & ctMEMFILE)) { \
		CTASSERT(hnum->updidxbuf > 0); \
		ctInterlockedDecrement32(hnum->updidxbuf); \
	} \
}
#else
/* no-op */
#define INCREMENT_UPDBUFCNT(buffer,check)
/* no-op */
#define DECREMENT_UPDBUFCNT(buffer)
#endif

/*--------------------------------------------------------------*/
/* ctFeatFILEupdseq maintains a running sequence number		*/
/* incremented each time tstupd() is called. The sequence	*/
/* number is maintained for each logical file (e.g., index	*/
/* member), not just the physical file. It is allowed to turn	*/
/* over (i.e., increment back to zero). Requires ctFeatATOMICop */
/* with MULTITRD.						*/
/*								*/
/* Default: ctFeatFILEupdseq is ON.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatFILEupdseq
#if !defined(MULTITRD) || defined(ctFeatATOMICop)
#define ctFeatFILEupdseq
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatPARTSERbuf maintains buffers to optimize part_ser()	*/
/* for indices that do not match the partition index. Requires	*/
/* ctFeatFILEupdseq and ctPARTITION				*/
/*								*/
/* Default: ctFeatPARTSERbuf is ON.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatPARTSERbuf
#ifdef ctFeatFILEupdseq
#define ctFeatPARTSERbuf
#endif
#endif

#ifdef ctFeatPARTSERbuf
#ifndef ctPARTITION
#undef ctFeatPARTSERbuf
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatPARTSERrawno causes the internal routines (nxtpartno /	*/
/* prepartno) that step over partition members during index	*/
/* searches to skip unused raw partition numbers that fall	*/
/* outside of the active range of partitions.			*/
/*								*/
/* Default: ctFeatPARTSERrawno is ON.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatPARTSERrawno
#ifdef ctPARTITION
#define ctFeatPARTSERrawno
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatKEEPOPENclose enables the c-tree Server to close	*/
/* files that are in the KEEPOPEN state when necessary.		*/
/*								*/
/* When this feature is enabled, file create and open calls	*/
/* close KEEPOPEN files when insufficient file control blocks	*/
/* are available and user threads signal an administrative	*/
/* thread to close a data file and its associated indices when	*/
/* the number of updated cache pages for the data file drops to	*/
/* zero.							*/
/*								*/
/* Default: ctFeatKEEPOPENclose is ON. Requires c-tree Server,	*/
/* KEEPOPEN support, and file updated page count support.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatKEEPOPENclose
#ifdef ctSRVR
#ifdef ctFeatKEEPOPEN
#ifdef ctFeatFILEupdpag
#define ctFeatKEEPOPENclose
#endif
#endif
#endif
#endif

#ifdef ctFeatKEEPOPENclose
#if !defined(ctSRVR) || !defined(ctFeatKEEPOPEN) || !defined(ctFeatFILEupdpag) || !defined(ctBEHAV_FCBSTK)
#error ctFeatKEEPOPENclose requires a feature that is not enabled!
#endif
#endif

#ifndef ctFeatKEEPOPENclose
#undef ctBEHAV_SUPERFILE_HOST_CLOSE_ON_ERROR
#undef ctBEHAV_SUPERFILE_HOST_CLOSE_ON_ERROR_TRANPROC 
#endif

/*--------------------------------------------------------------*/
/* ctFeatKEEPOPENcloseV2 enables improvements to the KEEPOPEN	*/
/* support. The goal is to better preserve consistency of the	*/
/* KEEPOPEN mode for a data file and its associated indices.	*/
/*								*/
/* The changes include:						*/
/*								*/
/* 1) An internal ctCLSNAM call that is made because the ISAM	*/
/*    file state is changing in a way that requires us to turn	*/
/*    off KEEPOPEN for the files (such as low-level index	*/
/*    delete), proceed even if the data file's user count is	*/
/*    greater than 2.						*/
/*								*/
/* 2) ctCLSNAM simply ignores indices that do not have KEEPOPEN	*/
/*    on, rather than stopping with an FUSE_ERR.		*/
/*								*/
/* 3) If ctCLSNAM is opening an index file in order to turn off	*/
/*    KEEPOPEN and the file is already closed, continue with	*/
/*    the file open. (Only if it is the data file that is not	*/
/*    already open do we skip opening it it and indicate to the */
/*    caller that the file was not open.)			*/
/*								*/
/* 4) When opening a file, if the file is already open and is	*/
/*    to be kept open with KEEPOPEN but	the file does not yet	*/
/*    have KEEPOPEN enabled, then enable KEEPOPEN for the file.	*/
/*								*/
/* 5) When closing a data file, if the data file's unqnum FCB	*/
/*    has rvnum pointing to this data file that we are closing,	*/
/*    remove the rvnum link for that index file.		*/
/*								*/
/* Default: ctFeatKEEPOPENcloseV2 is ON when KEEPOPEN support	*/
/* is enabled, in v10.4.0 and later.				*/
/*--------------------------------------------------------------*/

#if ctVER3_GE(10,4,0)
#ifndef NO_ctFeatKEEPOPENcloseV2
#ifdef ctFeatKEEPOPENclose
#define ctFeatKEEPOPENcloseV2
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatNOBUFFERING_LOGFILE enables use of unbuffered I/O for	*/
/* the transaction log files. It is enabled by specifying the	*/
/* configuration option UNBUFFERED_LOG_IO YES in ctsrvr.cfg.	*/
/*								*/
/* Default: ctFeatNOBUFFERING_LOGFILE is ON for c-tree Server	*/
/* when unbuffered I/O support is enabled.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatNOBUFFERING_LOGFILE
#ifdef ctFeatNOBUFFERING
#ifdef ctSRVR
#ifdef TRANPROC
#define ctFeatNOBUFFERING_LOGFILE
#endif
#endif
#endif
#endif

#ifdef ctFeatNOBUFFERING_LOGFILE

#ifndef ctFeatNOBUFFERING
#error ctFeatNOBUFFERING_LOGFILE requires #define ctFeatNOBUFFERING
#endif

#ifndef ctSRVR
#error ctFeatNOBUFFERING_LOGFILE requires #define ctSRVR
#endif

#ifndef TRANPROC
#error ctFeatNOBUFFERING_LOGFILE requires #define TRANPROC
#endif

#endif

/*--------------------------------------------------------------*/
/* ctFeatIICTxtd enables support for extended Immediate		*/
/* Independent Commit Transactions (IICT). An extended IICT	*/
/* permits a thread to issue an independent transaction when a	*/
/* transaction is already active. This transaction can update	*/
/* files that have not been updated in the outer transaction.	*/
/*								*/
/* Default: ctFeatIICTxtd requires ctFeatIICT and is ON by	*/
/* default for v9.6 and later when ctFeatIICT is enabled.	*/
/*--------------------------------------------------------------*/
#if ctVER_GE(9,6) || defined(ctFeatCOBOL)
#ifdef ctFeatIICT
#define ctFeatIICTxtd
#endif
#endif

#ifdef ctFeatIICTxtd
#ifndef ctFeatIICT
#error ctFeatIICTxtd requires ctFeatIICT
#endif
#endif


/*--------------------------------------------------------------*/
/* ctBEHAV_IICTusrtrn -  simplify the transaction hash bin	*/
/* management and searching					*/
/*								*/
/* Optional setting to simplify the transaction hash bin	*/
/* management and searching given that the transaction hash	*/
/* bin link is part of the USRTRN structure. When		*/
/* ctBEHAV_IICTusrtrn is defined, this modified approach	*/
/* is used.							*/
/*--------------------------------------------------------------*/
#if ctVER_GE(10,1)
#ifdef ctFeatIICT
#define ctBEHAV_IICTusrtrn
#endif
#endif

#ifdef ctBEHAV_IICTusrtrn
#ifndef ctFeatIICT
#error ctBEHAV_IICTusrtrn requires ctFeatIICT
#endif
#endif

/*
** check if ctBEHAV_IICTflex has necessary support
*/
#if defined(ctBEHAV_IICTflex) && !defined(ctFeatIICT)
#undef ctBEHAV_IICTflex
#undef ctBEHAV_IICTflexSTT
#endif

#ifdef ctBEHAV_IICTflexSTT
#ifndef ctFeatFILEupdseq
#error ctBEHAV_IICTflexSTT requires ctFeatFILEupdseq
#endif
#endif

#ifdef ctBEHAV_IICTflexSTT
#ifndef ctBEHAV_FUSRCLR
#error ctBEHAV_IICTflexSTT requires ctBEHAV_FUSRCLR
#endif
#endif

#if defined(ctFeatIICT) || ( defined(CTBOUND) && defined(TRANPROC) )
/* Enable support for automatic recovery on transaction logs that contain
IICT activity if IICT support is enabled or if this is a standalone TRANPROC
library. */
#define ctFeatIICTrcv
#endif

/*--------------------------------------------------------------*/
/* ctFeatPARTITIONrename causes an ISAM level file rename of a	*/
/* partition host file to also rename all existing partition	*/
/* member files.						*/
/*								*/
/* ctFeatPARTITIONrename is ON by default.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatPARTITIONrename
#define ctFeatPARTITIONrename
#endif

/*^***********************************/
/* Enable advanced encryption for standalone mode - ctFeatAEK256 */
#if (!defined(ctSRVR) && !defined(ctBNDSRVR) && !defined(ctCLIENT) && !defined(ctMTCLIENT))
#ifndef ctNO_CAMO
#define ctCAMO     	/* File Encryption */
#define ctCAMOsys 	/* Special "hidden" key */
#define ctCAMOsdk 	/* FairCom Encryption SDK */
#define ctCAMOblk	/* FairCom block encryption */
#define ctFeatCAMOsdkKEYWORD
#endif
#endif
/*~***********************************/

/*--------------------------------------------------------------*/
/* ctFeatAEK256 increases the strength of c-tree's advanced	*/
/* encryption in the following ways:				*/
/*								*/
/* 1) Increase the length of the master advanced encryption key */
/*    from 128 bits to 256 bits.				*/
/*								*/
/* 2) When advanced encryption and transaction log encryption	*/
/*    are both enabled, increase the transaction log encryption	*/
/*    key length from 128 bits to 256 bits.			*/
/*								*/
/* 3) When advanced encryption and FAIRCOM.FCS encryption are	*/
/*    both enabled, encrypt FAIRCOM.FCS with AES encryption	*/
/*    instead of with FairCom's ctCAMO encryption.		*/
/*								*/
/* Default: ctFeatAEK256 is ON by default.	*/
/*--------------------------------------------------------------*/
#ifdef ctPortWIN32
#if _MSC_VER == 1200
#define NO_ctFeatAEK256 /* not supported with VC6 compiler */
#endif
#endif

#ifdef ctCAMOsdk
#ifdef ctHUGEFILE
#ifndef NO_ctFeatAEK256
#ifndef ctFeatAEK256
#define ctFeatAEK256
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatPARTITION_ESTIMATE changes how ESTKEY and ESTRNG	*/
/* work for partitioned files. Instead of calling ESTKEY/ESTRNG	*/
/* for each active partition (or covering partition), a small	*/
/* subset of the partitions are sampled, and the estimate is	*/
/* extrapolated from the samples. This new behavior can		*/
/* significantly reduce the time necessary to execute		*/
/* ESTKEY/ESTRNG (at the cost of a larger uncertainty in	*/
/* the estimate).						*/
/*								*/
/* If enabled, the default behavior is to only sample three	*/
/* active partitions unless either (1) ctPARTITION_ESTIMATElimit*/
/* is defined with a value greater than three; and/or (2) a	*/
/* server configuration file sets PARTITION_ESTIMATE_LIMIT to	*/
/* a value greater than three. If the configuration file entry	*/
/* sets the limit negative, the behavior resorts to calling	*/
/* ESTKEY/ESTRNG for each active partition (or covering		*/
/* partition).							*/
/*								*/
/* ctFeatPARTITION_ESTIMATE defaults on.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatPARTITION_ESTIMATE
#define ctFeatPARTITION_ESTIMATE
#endif
#ifndef ctPARTITION_ESTIMATElimit
#define ctPARTITION_ESTIMATElimit	3
#endif
#if ctPARTITION_ESTIMATElimit >= 0 && ctPARTITION_ESTIMATElimit < 3
#define ctPARTITION_ESTIMATElimit	3
#endif

/*--------------------------------------------------------------*/
/* ctFeatFILEBLOCKcounter causes c-tree to track the number of	*/
/* file blocks that are currently active. Having the count of	*/
/* active file blocks allows us to skip our file block check	*/
/* when the count is zero.					*/
/*								*/
/* Default: ctFeatFILEBLOCKcounter is ON when file block	*/
/* support is enabled.						*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatFILEBLOCKcounter
#ifdef ctFeatFILEBLOCK
#define ctFeatFILEBLOCKcounter
#endif
#endif

#ifdef ctFeatFILEBLOCKcounter
#ifndef ctFeatFILEBLOCK
#error ctFeatFILEBLOCKcounter requires ctFeatFILEBLOCK
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatFILENAMEhash causes the c-tree Server to create a hash	*/
/* table containing the names of all open files. This hash	*/
/* table is searched to determine if a file is already open.	*/
/*								*/
/* Default: ctFeatFILENAMEhash is ON for c-tree server and	*/
/* single user with TRANPROC support.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatFILENAMEhash
#if defined(ctSRVR) || defined(TRANPROC)
#define ctFeatFILENAMEhash
#endif
#endif

#ifdef ctFeatFILENAMEhash

#if !defined(ctSRVR) && !defined(TRANPROC)
#error ctFeatFILENAMEhash requires ctSRVR or TRANPROC
#endif

#ifdef ctMULTIBYTEname
#error ctFeatFILENAMEhash is not supported when ctMULTIBYTEname is enabled
#endif

#endif

/*
** ctDBG_FILENAMEhash enables code that checks that our filename hash list is
** in sync with the currently open file list. When this #define is enabled,
** chkopnx() checks both the hash list and the system FCB array to determine
** if a file is open and compares the results. If a discrepancy is found, the
** code calls our breakpoint function.
*/
#ifdef ctDBGfcqa
/* #define ctDBG_FILENAMEhash */
#endif

/*
** ctDBG_FILENAMEhashLOG enables code that logs all additions to and deletions
** from the filename hash list to the file hash.log. This #define is useful for
** finding out the history of operations on the filename hash list if the list
** is in an unexpected state.
*/
/* #define ctDBG_FILENAMEhashLOG */

/*--------------------------------------------------------------*/
/* ctFeatAUTO_MKDIR causes c-tree Server to automatically	*/
/* create directories that do not existing when creating a	*/
/* c-tree data or index file if AUTO_MKDIR YES is specified in	*/
/* ctsrvr.cfg.							*/
/*								*/
/* Also, the XCREblk splval bit ctAUTOMKDIR can be used to	*/
/* enable automatic directory creation for a particular file	*/
/* that is being created.					*/
/*								*/
/* Default: ctFeatAUTO_MKDIR is ON.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatAUTO_MKDIR
#define ctFeatAUTO_MKDIR
#endif

/*--------------------------------------------------------------*/
/* ctFeatDISKFULLaction enables support for the c-tree Server	*/
/* DISK_FULL_ACTION configuration option, which can be used to	*/
/* perform an action when available disk space reaches the	*/
/* specified limit.						*/
/*								*/
/* Default: ctFeatDISKFULLaction is ON for c-tree Server when	*/
/* support for 64-bit configuration option scaling and 64-bit	*/
/* file access are enabled.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatDISKFULLaction
#ifdef ctSRVR
#ifdef ctFeatCFG_SCALE_N8
#ifndef ctNO_64BIT_FILE
#define ctFeatDISKFULLaction
#endif
#endif
#endif
#endif

#ifdef ctFeatDISKFULLaction
#ifndef ctSRVR
#error ctFeatDISKFULLaction requires ctSRVR
#endif
#endif

#ifdef ctFeatDISKFULLaction
#ifndef ctFeatCFG_SCALE_N8
#error ctFeatDISKFULLaction requires ctFeatCFG_SCALE_N8
#endif
#endif

#ifdef ctFeatDISKFULLaction
#ifdef ctNO_64BIT_FILE
#error ctFeatDISKFULLaction requires 64-bit file support, but ctNO_64BIT_FILE is on
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatRESIZEuser increases the rate at which the users FUSR 	*/
/* array is resized.  This has a small performance benefit when */
/* a large number of files are opened rapidly.	This can be 	*/
/* disabled at run time with COMPATIBILITY FILELIST_GROWTH	*/
/*                                                              */
/* Default: ctFeatRESIZEuser is ON for c-tree Server            */
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatRESIZEuser
#ifdef ctSRVR
#define ctFeatRESIZEuser
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatPARTREPL enables additional transaction log entries	*/
/* that are required in order to replicate changes to		*/
/* partitioned files.						*/
/*								*/
/* Default: ctFeatPARTREPL is ON for c-tree Server v10.1.3 and	*/
/* later when partition support is enabled. Also requires	*/
/* replication support.						*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatPARTREPL
#ifdef ctPARTITION
#ifdef ctSRVR
#if ctVER3_GE(10,2,0)
#define ctFeatPARTREPL
#endif
#endif
#endif
#endif

#ifdef ctFeatPARTREPL
#ifndef ctSRVR
#error ctFeatPARTREPL requires ctSRVR
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPL_FILENAME_HASH enables the replication agent's	*/
/* filename hash list. We use this list to determine if a	*/
/* partition host file is already open.				*/
/*								*/
/* Default: ctFeatREPL_FILENAME_HASH is ON for c-tree client	*/
/* v9.6 and later. Requires replication node ID support.	*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatREPL_FILENAME_HASH
#if defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB)
#ifdef ctFeatREPL_NODEID
#if ctVER_GE(9,6)
#define ctFeatREPL_FILENAME_HASH
#endif
#endif
#endif
#endif

#ifdef ctFeatREPL_FILENAME_HASH
#ifndef ctFeatREPL_NODEID
#error ctFeatREPL_FILENAME_HASH requires ctFeatREPL_NODEID support
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatENCSTORE enables support for c-tree reading the master	*/
/* encryption key from an encrypted store.			*/
/*								*/
/* Default: ctFeatENCSTORE is ON for the platforms listed below	*/
/* when ctFeatAEK256 is enabled.				*/
/*--------------------------------------------------------------*/

#ifndef ctPortUNIX
#if _MSC_VER == 1200
#define NO_ctFeatENCSTORE
#endif
#ifdef ctPortBORLAND_W32
#define NO_ctFeatENCSTORE
#endif
#endif

#ifndef NO_ctFeatENCSTORE
#ifdef ctFeatAEK256

/* Windows */
#ifdef ctPortWIN32 
#define ctFeatENCSTORE
#endif

/* All Unix systems */
#ifdef ctPortUNIX
#define ctFeatENCSTORE
#endif

/* Use keyutils on Linux 2.6 kernel and later */
#if defined(ctPortLINUX) && !defined(ctPort_LINUX_KERNEL_V2_4)
#ifndef NO_ctFeatLINUXkeyutils
/* #define ctFeatLINUXkeyutils */
#endif
#endif

#define ENCSTORE_NAME "ctsrvr.fkf"

#ifdef ctPortWIN32
#define ENCSTORE_DESC "encrypted password store"
#endif

#ifdef ctFeatLINUXkeyutils
#define ENCSTORE_DESC "user key"
#else
#ifdef ctPortUNIX
#define ENCSTORE_DESC "password store"
#endif
#endif

#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatSUBST_IDENTITY turns on support for setting 	*/
/* identity field value directly by suppling the value in the rec buf.*/
/*								*/
/* Default: ctFeatSUBST_IDENTITY is ON by default for		*/
/* c-tree Server compiles for v11.3.1 and later.		*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatSUBST_IDENTITY
#ifdef  ctFeatDAR
#ifdef ctSRVR
#if ctVER3_GE(11,3,1)
#define ctFeatSUBST_IDENTITY
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPL_IDENTITY turns on support for replicating data	*/
/* files that contain an identity field.			*/
/*								*/
/* Default: ctFeatREPL_IDENTITY is ON by default for		*/
/* c-tree Server compiles for v9.6 and later.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatREPL_IDENTITY
#ifdef  ctFeatREPLICAT
#ifdef ctSRVR
#if ctVER_GE(9,6)
#ifdef TRANPROC
#ifdef  ctFeatDAR
#define ctFeatREPL_IDENTITY
#ifndef NO_ctFeatSUBST_IDENTITY
#define ctFeatSUBST_IDENTITY
#endif
#endif
#endif
#endif
#endif
#endif
#endif


#if defined ctFeatREPL_IDENTITY && ! defined ctFeatSUBST_IDENTITY
#error ctFeatREPL_IDENTITY requires ctFeatSUBST_IDENTITY
#endif

/*--------------------------------------------------------------*/
/* ctFeatPWDSEC turns on support for securely passing all	*/
/* passwords from client to server.				*/
/*								*/
/* Default: ctFeatPWDSEC is ON by default for v10 and later.	*/
/* Requires encryption, enhanced ADMIN security, and secure	*/
/* logon features.						*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatPWDSEC
#ifdef  ctHUGEFILE
#if defined(ctCAMOsdk) & defined(ctFeatADMIN_SECURITY) && defined(ctFeatLOGONSEC)
#if ctVER_GE(10,0)
#define ctFeatPWDSEC
#endif
#endif
#endif
#endif
/*
** Note: PWDSECHSHLEN gets redefined later on in this header file when
** ctFeatPWDLEN is enabled.
*/
#define PWDSECRNDLEN	16	   /* size of random value	*/
#define PWDSECHSHLEN	16	   /* size of hash value	*/
#define PWDSEC_BLKSIZ	16	   /* encryption block size	*/
#define PWDSEC_MSGDEC	0x01	   /* message is not encrypted	*/
#define PWDSEC_MSGENC	0x02	   /* message is encrypted	*/

#ifdef ctFeatPWDSEC
#ifndef ctCAMOsdk
#error The password security feature requires FairCom Encryption support.
#endif
#endif

#ifdef ctFeatPWDSEC
#ifndef ctFeatADMIN_SECURITY
#error The password security feature requires the enhanced ADMIN security feature.
#endif

#ifndef ctFeatLOGONSEC
#error The password security feature requires the secure logon feature.
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatPWDLEN turns on support for user passwords up to 63	*/
/* bytes long (instead of 9 bytes long before this change).	*/
/*								*/
/* Default: ctFeatPWDLEN is ON by default for v10 and later.	*/
/* Requires secure password support.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatPWDLEN
#ifdef  ctHUGEFILE
#if ctVER_GE(10,0)
#ifdef ctFeatPWDSEC
#define ctFeatPWDLEN
#endif
#endif
#endif
#endif

#ifdef ctFeatPWDLEN
#ifndef ctFeatPWDSEC
#error The long password feature requires the secure password feature.
#endif
#endif

#ifdef ctFeatPWDLEN
#ifdef ctFeatLONG_PASSWORD
#error The original long password feature cannot be enabled with the new long password feature.
#endif
#endif

#ifdef ctFeatPWDLEN
#ifdef ctSRVR
#ifndef ctBEHAV_FCUSERconvert
#error The long password feature requires the FAIRCOM.FCS user definition file conversion support.
#endif
#endif
#endif

#ifdef ctFeatPWDLEN

#define PWZX	64		/* maximum password length + 1		*/
#define PWS	32		/* password salt length			*/
#ifndef PWH
#define PWH	64		/* password hash length			*/
#endif
#define PWZX16	PWZX		/* max pass len (minimum 16)		*/
#define CTAPWLEN PWZX		/* application buffer password length	*/

#undef PWDSECRNDLEN
#define PWDSECRNDLEN	PWS	   /* size of random value	*/
#undef PWDSECHSHLEN
#define PWDSECHSHLEN	PWH	   /* size of hash value	*/

#else

/*
** If we turned off the secure logon feature above but the code is being
** compiled with the multiple DLL support, use the secure logon password
** length so that the standalone library's LOGBLK structure is compatible
** the client library's LOGBLK structure.
*/
#if defined(UNDEF_ctFeatLOGONSEC) && (defined(ctMULTIPLE_CTREE_DLLs) || defined(ctCLIENT_FOR_CTREE_DLLs))
#define PWZX	64		/* maximum password length + 1		*/
#else
#define PWZX	PWZ		/* maximum password length + 1		*/
#endif

#define PWZX16	16		/* max pass len (minimum 16)		*/
#define CTAPWLEN ctMAXPASSLEN	/* application buffer password length	*/

#endif

/*
** Enable our original long password support only if our new long password
** support is disabled.
*/
#ifndef ctFeatPWDLEN
#ifndef NO_ctFeatLONG_PASSWORD
#define ctFeatLONG_PASSWORD
#endif
#endif

#ifdef ctSRVR
#define ctFeatQTcamo
#define ctQTCK1	0xc34dbe81
#define ctQTCK2	0x9e785a6e
#endif

#define LPWD_DELAY 50

/*--------------------------------------------------------------*/
/* ctFeatLOGLMT turns on support for limiting users and groups	*/
/* to a specified number of concurrent logons.			*/
/*								*/
/* Default: ctFeatLOGLMT is ON by default for v10 and later.	*/
/* Requires ctFeatPWDLEN.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatLOGLMT
#if ctVER_GE(10,0)
#ifdef ctFeatPWDLEN
#define ctFeatLOGLMT
#endif
#endif
#endif

#ifdef ctFeatLOGLMT
#ifndef ctFeatPWDLEN
#error User and group logon limits require ctFeatPWDLEN support.
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatLOGONSECtr turns on support for secure logon for the	*/
/* local/master server architecture.				*/
/*								*/
/* Default: ctFeatLOGONSECtr is ON by default for v10 and later */
/* when the required options are enabled.			*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatLOGONSECtr
#if ctVER_GE(10,0)
#if defined(ctFeatLOGONSEC) && defined(ctFeatPWDLEN)
#define ctFeatLOGONSECtr
#endif
#endif
#endif

#ifdef ctFeatLOGONSECtr
#ifndef ctFeatLOGONSEC
#error Secure logon for local/master server requires secure logon support.
#endif
#endif

#ifdef ctFeatLOGONSECtr
#ifndef ctFeatPWDLEN
#error Secure logon for local/master server requires ctFeatPWDLEN support.
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPLmultipos turns on support for saving all of the	*/
/* replication reader log requirements in the transaction log.	*/
/*								*/
/* Default: ctFeatREPLmultipos is ON for v10 and later.		*/
/*--------------------------------------------------------------*/
#if ctVER_GE(10,0)
#ifndef NO_ctFeatREPLmultipos
#ifdef ctFeatREPLICAT
#ifdef TRANPROC
#define ctFeatREPLmultipos
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatSET_ALIGN enables an application to set the alignment	*/
/* value for the client library to use when it sends data	*/
/* record images to c-tree Server.				*/
/*								*/
/* Default: ctFeatSET_ALIGN is ON.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatSET_ALIGN
#define ctFeatSET_ALIGN
#endif

/*--------------------------------------------------------------*/
/* ctFeatOPENSSL enables the use of the OpenSSL library, used	*/
/* to support SSL for TCP/IP connections and to support secure	*/
/* password transmission from client to server when not using	*/
/* SSL.								*/
/*								*/
/* Default: ctFeatOPENSSL is ON for v10.1.3 and later for	*/
/* client and server on the operating systems listed below.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,2,0) || (ctVER3_GE(10,1,0) && defined(ctPortCHARGER1))
#ifndef NO_ctFeatOPENSSL
#if defined(ctSRVR) || defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctCLISIDE)
#if defined(ctPortWIN32) || defined(ctPortLINUX)
#define ctFeatOPENSSL
#ifdef ctFeatSSL
/* When ctFeatSSL is on, we statically link with the OpenSSL libraries, so
** use them instead of dynamically loading the OpenSSL DLLs. */
#define ctFeatOPENSSLstatic
#endif
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatKEYXCHG enables Diffie-Hellman key exchange, used	*/
/* to allow a c-tree client to securely send its password to	*/
/* c-tree Server.						*/
/*								*/
/* Default: ctFeatKEYXCHG is ON for v10.1.3 and later when 	*/
/* OpenSSL support is enabled.					*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,2,0) || (ctVER3_GE(10,1,0) && defined(ctPortCHARGER1))
#ifndef NO_ctFeatKEYXCHG
#if defined(ctHUGEFILE) && defined(ctFeatOPENSSL) && !defined(CTBOUND)
#define ctFeatKEYXCHG
#define ctFeatKEYXCHG_FC_RNG /* use FairCom random number generator for secure key exchange */
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatLDAP enables support for using an LDAP server for	*/
/* c-tree Server's user authentication. This feature replaces	*/
/* the old ctFeatOS_SECURITY_LDAP feature.			*/
/*								*/
/* Default: ctFeatLDAP is ON for v10.1.3 and later when		*/
/* OpenSSL support is enabled.					*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,2,0) || (ctVER3_GE(10,1,0) && defined(ctPortCHARGER1))
#ifndef NO_ctFeatLDAP
#ifdef ctHUGEFILE
#ifndef ctFeatOS_SECURITY
#ifdef ctFeatOPENSSL
#if defined(ctSRVR) || defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctCLISIDE)
#define ctFeatLDAP
#define ctDBGldap
#ifndef NO_ctFeatLDAPgroup
#define ctFeatLDAPgroup /* c-tree group support for LDAP */
#endif
#endif
#endif
#endif
#endif
#endif
#endif

#ifdef ctFeatLDAP
#ifndef ctFeatPWDLEN
#error c-tree LDAP support requires long password support
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatCFGsubsys enables support for c-tree Server's		*/
/* SUBSYSTEM keyword.						*/
/*								*/
/* Default: ctFeatCFGsubsys is ON for v10.1.3 and later.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,2,0) || (ctVER3_GE(10,1,0) && defined(ctPortCHARGER1))
#ifndef NO_ctFeatCFGsubsys
#ifdef ctSRVR
#define ctFeatCFGsubsys
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatCFGsubsys2 enables new support for c-tree Server's	*/
/* SUBSYSTEM keyword, which allow using SUBSYSTEM in .set files,*/
/* controls override of the entire SUBSYSTEM or of single key	*/
/* in the SUBSYSTEM.						*/
/*								*/
/* Default: ctFeatCFGsubsys2 is ON for v10.4.0 and later.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0)
#ifndef NO_ctFeatCFGsubsys2
#ifdef ctFeatCFGsubsys
#define ctFeatCFGsubsys2
#endif
#endif
#endif
/*--------------------------------------------------------------*/
/* ctFeatTMPPTH_FREE enables support for freeing c-tree's	*/
/* temporary file path buffer allocated by ctSetCtTempDirName() */
/* when c-tree is shutting down.				*/
/*								*/
/* Default: ctFeatTMPPTH_FREE is ON in standalone mode.		*/
/*--------------------------------------------------------------*/
#if defined(CTBOUND) && !defined(ctBNDSRVR)
#define ctFeatTMPPTH_FREE
#endif

/*--------------------------------------------------------------*/
/* ctFeatADDUNQKEYS_FIRST enables support for a file mode that	*/
/* causes ISAM record add operations in variable-length files	*/
/* to add all unique keys before allocating space for the	*/
/* record in the data file. This strategy speeds up record adds */
/* that fail due to a duplicate	unique key value because the	*/
/* space does not have to be made available again in the data	*/
/* file.							*/
/*								*/
/* Default: ctFeatADDUNQKEYS_FIRST is ON for c-tree Server	*/
/* version 10.1.0 and later when ctFeatREMBUFADR is enabled.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,1,0)
#if defined(ctSRVR) && defined(ctFeatREMBUFADR)
#ifndef NO_ctFeatADDUNQKEYS_FIRST
#define ctFeatADDUNQKEYS_FIRST
#endif
#endif
#endif

/* record offset placeholder values */
#define ADDUNQKEYSPH8	(ULONG8) 1
#define ADDUNQKEYSPH4	(ULONG) 1

/*--------------------------------------------------------------*/
/* c-tree Server's virtual file support can be disabled by	*/
/* compiling with MAXVFIL set to -1 or by specifying the option */
/* MAX_VIRTUAL_FILES -1 in ctsrvr.cfg. The compile-time option	*/
/* ctFeatVIRTUAL_FILES_flmode causes c-tree Server to set the	*/
/* ctPERMANENT filemode bit on all files when virtual file	*/
/* support is disabled.	Doing this allows c-tree Server to	*/
/* avoid acquiring the file's I/O mutex in io_ctsemrqs().	*/
/*								*/
/* Default: ctFeatVIRTUAL_FILES_flmode is ON for c-tree Server	*/
/* version 10.2.0 and later.					*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,2,0)
#ifdef ctSRVR
#ifndef NO_ctFeatVIRTUAL_FILES_flmode
#define ctFeatVIRTUAL_FILES_flmode
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatBATCH_ALLOC_OPT reduces memory allocations during	*/
/* physical order batch read operations in two ways:		*/
/*								*/
/* 1) saving the batch continuation pointer across batch calls	*/
/*    so that it can be reused, and				*/
/*								*/
/* 2) skipping the creation of the batch record offset list	*/
/*    when reading in physical order and not locking records	*/
/*    or only locking one record at a time.			*/
/*								*/
/* Default: ctFeatBATCH_ALLOC_OPT is ON for c-tree Server	*/
/* version 10.2.0 and later.					*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,2,0)
#ifdef ctSRVR
#ifndef NO_ctFeatBATCH_ALLOC_OPT
#define ctFeatBATCH_ALLOC_OPT
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatDISTcachestats enables distributed data and index	*/
/* cache statistic counters.					*/
/*								*/
/* Default: ctFeatDISTcachestats is ON for c-tree Server	*/
/* version 10.2.0 and later when the following features are	*/
/* supported: 64-bit atomic operations, snapshot, cache-line	*/
/* aligned memory.						*/
/*--------------------------------------------------------------*/
#if defined(ctSRVR) && defined(ctFeatATOMICop64) && defined(ctFeatSNAPSHOT) && defined(ctCACHE_MEMORY)
#ifndef NO_ctFeatDISTcachestats

#define ctFeatDISTcachestats

#define ctDISTcsDBRQS 0	/* data buffer requests		*/
#define ctDISTcsDBHIT 1	/* data buffer hits		*/
#define ctDISTcsIBRQS 2	/* index buffer requests	*/
#define ctDISTcsIBHIT 3	/* index buffer hits		*/

#define ctDISTcsTOTAL 4	/* total number of stat arrays	*/

/*
** Macro to get the address of the specified stat array entry for the specified
** stat type.
*/
#define ctGET_DIST_CACHE_PTR(typ, idx) \
	(AULONG8 *) ((pTEXT) ctcachestatary + \
	typ * ctcachestatcnt * ctcachestatsiz + \
	idx * ctcachestatsiz)

#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatLOGLMTusracct turns on support for limiting the number	*/
/* of concurrent distinct user account logons.			*/
/*								*/
/* Default: ctFeatLOGLMTusracct is on for v10.1 and later when	*/
/* ctFeatLOGLMT is on.						*/
/*--------------------------------------------------------------*/

#if ctVER_GE(10,1)
#ifndef NO_ctFeatLOGLMTusracct
#ifdef ctFeatLOGLMT
#define ctFeatLOGLMTusracct
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatDYNPARTMBR enables support for dynamic partition	*/
/* members.							*/
/*								*/
/* Default: ctFeatDYNPARTMBR is on for c-tree Server v10.1.3	*/
/* and later.							*/
/*--------------------------------------------------------------*/

#if ctVER3_GE(10,2,0)
#ifdef MULTITRD
#if (!defined(NO_ctFeatDYNPARTMBR) && defined(ctPARTITION) && defined(MULTITRD))
#define ctFeatDYNPARTMBR
#endif
#endif
#endif

#ifdef ctFeatDYNPARTMBR
#ifndef MULTITRD
#error Dynamic partition support is only available for c-tree Server
#endif
#endif

#ifdef ctFeatDYNPARTMBR
#ifndef ctPARTITION
#error Dynamic partition support is only available when ctPARTITION is enabled
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatCTDLLerrbuf enables support for passing an error	*/
/* buffer to ctdll_load().					*/
/*								*/
/* Default: ctFeatCTDLLerrbuf is on for v10.1.2 and later.	*/
/*--------------------------------------------------------------*/

#if ctVER3_GE(10,1,2)
#ifndef NO_ctFeatCTDLLerrbuf
#define ctFeatCTDLLerrbuf
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatZLIBdynamic causes c-tree to load the zlib compression	*/
/* library at run-time on Unix systems rather than statically	*/
/* linking with the zlib library at compile time.		*/
/*								*/
/* Default: ctFeatZLIBdynamic is on for v10.1.2 and later.	*/
/*--------------------------------------------------------------*/

#if ctVER3_GE(10,1,2)
#ifndef NO_ctFeatZLIBdynamic
#define ctFeatZLIBdynamic
#endif
#endif

#if defined(ctFeatZLIBdynamic) && !defined(ctFeatCTDLLerrbuf)
#error zlib dynamic load requires ctdll_load() error buffer support
#endif

/* Enable zlib compression support unless using the PRO SDK on Windows. */
#if !(defined(ctPortMTREEPRO) && defined(ctPortWIN32))
#ifndef NO_ctFeatZLIBsupport
#define ctFeatZLIBsupport
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatCLIENTID enables support for c-tree clients sending	*/
/* identifying information to c-tree Server when connecting.	*/
/*								*/
/* Default: ctFeatCLIENTID is ON for v10.3.0 and later.	*/
/* Requires long password support.				*/
/*--------------------------------------------------------------*/

#if ctVER3_GE(10,3,0)
#ifndef NO_ctFeatCLIENTID
#ifdef ctFeatPWDLEN
#define ctFeatCLIENTID
#endif
#endif
#endif

#ifdef ctFeatCLIENTID
#ifndef ctFeatPWDLEN
#error The Client ID feature requires long password support.
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatRTG_API enables support for the RTG API function.	*/
/*								*/
/* Default: ctFeatRTG_API is on for v10.2.0 and later.		*/
/*--------------------------------------------------------------*/

#if ctVER3_GE(10,2,0)
#ifndef NO_ctFeatRTG_API
#if (defined(MULTITRD) && !defined(ctBNDSRVR)) || defined(ctCLIENT) || defined(ctMTCLIENT) || (defined(ctLOCLIB) && !defined(ctFRCSNG))
#define ctFeatRTG_API
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatDIAG_CHKPNT_FILLST enables diagnostic checking of the	*/
/* checkpoint file list. Use the configuration option		*/
/* DIAGNOSTICS CHKPNT_FILLST to enable the diagnostic checks.	*/
/*								*/
/* Default: ctFeatDIAG_CHKPNT_FILLST is ON for c-tree Server.	*/
/*--------------------------------------------------------------*/
#if defined(MULTITRD) && defined(TRANPROC)
#ifndef NO_ctFeatDIAG_CHKPNT_FILLST
#define ctFeatDIAG_CHKPNT_FILLST
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatNOISMKEYUPD enables support for an index mode that	*/
/* prevents an ISAM record update from updating the key value	*/
/* for that index. An attempt to do so will fail with error	*/
/* NOISMKEYUPD_ERR(1001).					*/
/*								*/
/* Default: ctFeatNOISMKEYUPD is ON in v10.3.0 and later.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,3,0)
#ifndef NO_ctFeatNOISMKEYUPD
#define ctFeatNOISMKEYUPD
#endif
#endif

#if defined(ctSRVR) && defined(ctFeatNOISMKEYUPD) && !defined(NO_ctFeatNOISAMKEYUPDuser)
/*----------------------------------------------------------------------------
  ctFeatNOISAMKEYUPDuser enables the ability to turn on the "no ISAM key update"
  attribute for the specified open instance of an index file. Requires server.
----------------------------------------------------------------------------*/
#define ctFeatNOISAMKEYUPDuser
#endif

/*--------------------------------------------------------------*/
/* ctFeatINTERNAL_FILE_CONTROL enables automatic detection and	*/
/* avoidance of file access errors caused by the delete node	*/
/* and space reclamation threads having a file open when a user	*/
/* thread attempts to open the file in exclusive mode.		*/
/*								*/
/* Default: ctFeatINTERNAL_FILE_CONTROL is ON for c-tree Server */
/* in v10.4.0 and later. Requires atomic operation support.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0)
#ifndef NO_ctFeatINTERNAL_FILE_CONTROL
#ifdef MULTITRD
#ifdef ctFeatATOMICop
#define ctFeatINTERNAL_FILE_CONTROL
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatSET_THREAD_NAME causes c-tree Server to set a name	*/
/* for the threads that it creates. The Visual Studio		*/
/* debugger shows these thread names in the Threads window.	*/
/*								*/
/* Default: ctFeatSET_THREAD_NAME is ON for Windows systems	*/
/* when ctDBGfcqa is defined.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatSET_THREAD_NAME
#if defined(ctPortWIN32) && defined(ctDBGfcqa)
#define ctFeatSET_THREAD_NAME
#endif
#endif

#ifndef ctPortWIN32
/* ctFeatSET_THREAD_NAME is only supported on Windows */
#undef ctFeatSET_THREAD_NAME
#endif

/*--------------------------------------------------------------*/
/* ctFeatMEMTRACKmballc enables c-tree Server to track mballc()	*/
/* memory allocations.						*/
/*								*/
/* Default: ctFeatMEMTRACKmballc is ON for c-tree Server	*/
/* v10.4.0 and later.						*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0)
#ifdef ctSRVR
#ifndef NO_ctFeatMEMTRACKmballc
#define ctFeatMEMTRACKmballc
#endif
#endif
#endif

#ifdef ctFeatMEMTRACKmballc
#ifndef ctSRVR
#error ctFeatMEMTRACKmballc requires server
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatMEMTRACKsublist enables c-tree Server diagnostic	*/
/* memory tracking for each memory suballocator list.		*/
/*								*/
/* Default: ctFeatMEMTRACKsublist is ON for c-tree Server	*/
/* v10.4.0 and later. Requires memory tracking support and	*/
/* ctBEHAV_MEMSUB_SPCLST.					*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0)
#ifdef ctSRVR
#ifndef NO_ctFeatMEMTRACKsublist
#ifdef ctFeatMEMTRACK
#ifdef ctBEHAV_MEMSUB_SPCLST
#define ctFeatMEMTRACKsublist
#endif
#endif
#endif
#endif
#endif

#ifdef ctFeatMEMTRACKsublist

#ifndef ctFeatMEMTRACK
#error ctFeatMEMTRACKsublist requires ctFeatMEMTRACK
#endif

#ifndef ctSRVR
#error ctFeatMEMTRACKsublist requires server
#endif

#ifndef ctBEHAV_MEMSUB_SPCLST
#error ctFeatMEMTRACKsublist requires ctBEHAV_MEMSUB_SPCLST
#endif

#ifdef ctMXLOGS
#error ctFeatMEMTRACKsublist is not compatible with ctMXLOGS
#endif

#endif

/*--------------------------------------------------------------*/
/* ctFeatUNIX_SHMEMsocket changes c-tree Server's shared memory	*/
/* communication protocol for Unix systems to use a Unix file	*/
/* system (AF_UNIX) socket instead of a pair of named pipes for	*/
/* the initial communication between client and server when	*/
/* establishing the shared memory connection.			*/
/*								*/
/* Default: ctFeatUNIX_SHMEMsocket is ON for c-tree Server	*/
/* v10.0 and later on AIX, and is ON for c-tree Server v10.3.0	*/
/* and later on other Unix systems. Requires ctBEHAV_POLL.	*/
/*--------------------------------------------------------------*/
#if ctVER_GE(10,0) && defined(ctPortRS6000) || ctVER3_GE(10,3,0)
#ifndef NO_ctFeatUNIX_SHMEMsocket
#if defined(ctPortUNIX) && defined(ctBEHAV_POLL)
#define ctFeatUNIX_SHMEMsocket
#endif
#endif
#endif

#ifdef ctFeatUNIX_SHMEMsocket

#ifndef ctPortUNIX
#error ctFeatUNIX_SHMEMsocket is only for Unix systems
#endif

#ifndef ctBEHAV_POLL
#error ctFeatUNIX_SHMEMsocket requires ctBEHAV_POLL
#endif

#endif


/*--------------------------------------------------------------*/
/* ctFeatXTDFLDTYP enables support for additional c-tree data	*/
/* types.							*/
/*								*/
/* Default: ctFeatXTDFLDTYP is ON for c-tree v10.4.1 and later.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1)
#ifndef NO_ctFeatXTDFLDTYP
#define ctFeatXTDFLDTYP
#endif
#endif

#ifdef ctFeatXTDFLDTYP

#define ConvBlkN ConvBlk2
#define pConvBlkN pConvBlk2
#define CTUNICsepN CTUNICsep2
#define pCTUNICsepN pCTUNICsep2

#else

#define ConvBlkN ConvBlk
#define pConvBlkN pConvBlk
#define CTUNICsepN CTUNICsep
#define pCTUNICsepN pCTUNICsep

#endif

/*--------------------------------------------------------------*/
/* ctFeatTIMESTAMPmsec enables support for a c-tree data type	*/
/* that stores a timestamp with millisecond precision.		*/
/*								*/
/* Default: ctFeatTIMESTAMPmsec is ON when extended data type	*/
/* support is enabled.						*/
/*--------------------------------------------------------------*/

#ifndef NO_ctFeatTIMESTAMPmsec
#ifdef ctFeatXTDFLDTYP
#if ctVER3_GE(10,5,0)
#define ctFeatTIMESTAMPmsec
#endif
#endif
#endif

#ifdef ctFeatTIMESTAMPmsec
#ifndef ctFeatXTDFLDTYP
#error ctFeatTIMESTAMPmsec requires ctFeatXTDFLDTYP support
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatTIMEmsec enables support for a c-tree data type	*/
/* that stores a time with millisecond precision.		*/
/*								*/
/* Default: ctFeatTIMEmsec is ON when extended data type	*/
/* support is enabled.						*/
/*--------------------------------------------------------------*/

#ifndef NO_ctFeatTIMEmsec
#ifdef ctFeatXTDFLDTYP
#if ctVER3_GE(10,5,0)
#define ctFeatTIMEmsec
#endif
#endif
#endif

#ifdef ctFeatTIMEmsec
#ifndef ctFeatXTDFLDTYP
#error ctFeatTIMEmsec requires ctFeatXTDFLDTYP support
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatSHAREDCRIT enables support for ctThrdSharedCritical	*/
/* functions, which are a reader/writer lock with very		*/
/* scalable shared locks.		 			*/
/*								*/
/* Default: ctFeatSHAREDCRIT is ON when ctFeatATOMICop 		*/
/* and ctThrds support is enabled.				*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatSHAREDCRIT
#ifdef ctThrds
#ifdef ctFeatATOMICop
#define ctFeatSHAREDCRIT
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatCOPYFILE enables c-tree's file copy API function.	*/
/*								*/
/* Default: ctFeatCOPYFILE is ON in v10.5.0 and later for	*/
/* c-tree client and server models. The server model requires	*/
/* system file copy support and ISAM support.			*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1)
#ifndef NO_ctFeatCOPYFILE
#if (defined(ctSRVR) && defined(CTS_ISAM) && defined(ctFeatFScopy)) || defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctCLISIDE)
#define ctFeatCOPYFILE
#endif
#endif
#endif

#ifdef ctFeatCOPYFILE
#if !((defined(ctSRVR) && defined(CTS_ISAM) && defined(ctFeatFScopy)) || defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctCLISIDE))
#error ctFeatCOPYFILE requires Server with ISAM and system file copy support, or client
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatFLUSHdirmeta enables flushing directory metadata when	*/
/* a c-tree file is created, renamed, or deleted.		*/
/*								*/
/* Default: ctFeatFLUSHdirmeta is ON for c-tree version	10.5.0	*/
/* and later when transaction support is enabled. Not supported	*/
/* for DIAD file system, the Windows kernel, AIX systems, or	*/
/* when c-tree's multibyte file name feature is enabled.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1)
#ifndef NO_ctFeatFLUSHdirmeta
#ifdef TRANPROC
#if !defined(ctPortDIAD_FS) && !defined(ctPortWINKE) && !defined(ctMULTIBYTEname)
/* AIX and SCO does not support calling fsync() on directories, so we do not support
** the directory metadata flush feature on these systems. */
#if !defined(ctPortRS6000) && !defined(ctPortSCO386)
#define ctFeatFLUSHdirmeta
#endif
#endif
#endif
#endif
#endif

#ifdef ctFeatFLUSHdirmeta
#ifdef ctPortDIAD_FS
#define ctFeatFLUSHdirmeta not supported with DIAD file system
#endif
#ifdef ctPortWINKE
#define ctFeatFLUSHdirmeta not supported for Windows kernel
#endif
#ifdef ctPortRS6000
#define ctFeatFLUSHdirmeta not supported for AIX systems
#endif
#ifdef ctMULTIBYTEname
#define ctFeatFLUSHdirmeta not supported with multibyte filenames
#endif

#define ctrenfil(src,dst,flg,mode) renfilx(src,dst,flg,mode) 
#else /* ~ctFeatFLUSHdirmeta */
#define ctrenfil(src,dst,flg,mode) renfil(src,dst)
#endif

/*--------------------------------------------------------------*/
/* ctFeatLOGFLUSH_MOD permits a server to be run in a mode that	*/
/* reduces, to a minimum, transaction log flushes and log	*/
/* synchronization to disk, with the tradeoff that recovery	*/
/* can only go as far as the last Restore Point found in the	*/
/* logs. This means that transactions that commit successfully	*/
/* after the last restore point will not be included in		*/
/* automatic recovery. It is incumbent upon the server		*/
/* environment to maintain its own external "activity log"	*/
/* if it wishes to augment recovery to include updates after	*/
/* the last restore point (and before regular application	*/
/* programs are permitted to restart).				*/
/*								*/
/* When ctFeatLOGFLUSH_MOD is defined at compile-time, the	*/
/* configuration keyword DELAYED_DURABILITY enables this new	*/
/* behavior.							*/
/*								*/
/* ctFeatLOGFLUSH_MOD defaults on for server versions of 10.5.0	*/
/* or greater.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1) && defined(ctSRVR) && defined(TRANPROC)
#ifndef NO_ctFeatLOGFLUSH_MOD
#define ctFeatLOGFLUSH_MOD
#endif
#endif

#if defined(ctFeatLOGFLUSH_MOD) && !(defined(ctSRVR) && defined(TRANPROC))
#undef ctFeatLOGFLUSH_MOD
#endif


/*--------------------------------------------------------------*/
/* ctFeatRP permits a server to be run in a mode that		*/
/* reduces, to a minimum, transaction log flushes and log	*/
/* synchronization to disk, with the tradeoff that recovery	*/
/* can only go as far as the last Restore Point found in the	*/
/* logs. This means that transactions that commit successfully	*/
/* after the last restore point will not be included in		*/
/* automatic recovery. It is incumbent upon the server		*/
/* environment to maintain its own external "activity log"	*/
/* if it wishes to augment recovery to include updates after	*/
/* the last restore point (and before regular application	*/
/* programs are permitted to restart).				*/
/*								*/
/* ctFeatRP defaults on for server versions of 10.5.0 or greater*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1) 

#if defined(ctSRVR) && defined(TRANPROC) && \
	defined(ctFeatQUIET) && defined(ctFeatTRAN_BAK_FWD)
#ifndef NO_ctFeatRP
#define ctFeatRP
#endif
#endif

#if defined(CTBOUND) && defined(TRANPROC) && \
	defined(ctPortFAIRCOM_INTERNAL_GEN)
#ifndef NO_ctFeatRP
#define ctFeatRP
#endif
#endif

#endif

#if defined(ctFeatRP) && !(defined(ctSRVR) && defined(TRANPROC) && \
	defined(ctFeatQUIET) && defined(ctFeatTRAN_BAK_FWD))
#undef ctFeatLOGFLUSH_MOD
#endif

#if defined(ctFeatRP) && !defined(ctBEHAV_DLYLOGPRG)
#ifdef NO_ctBEHAV_DLYLOGPRG
#error ctBEHAV_DLYLOGPRG required by ctFeatRP to adjust logtrn_lst after recovery
#else
#define ctBEHAV_DLYLOGPRG
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatMAX_LOG_DEFER allows a maximum interval to be		*/
/* specified such that the interval between transaction log	*/
/* flushes will be guaranteed not to exceed this specified	*/
/* maximum. In turn this guarantees that a committed		*/
/* transaction will wait to be flushed to disk no longer than	*/
/* this specified maximum.					*/
/*								*/
/* ctFeatMAX_LOG_DEFER defaults on for server versions of	*/
/* 10.5.0 or greater when ctFeatLOGFLUSH_MOD is enabled		*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1) && defined(MULTITRD) && defined(TRANPROC) && \
	defined(ctFeatLOGFLUSH_MOD) && defined(ctrt_hrtimer)
#ifndef NO_ctFeatMAX_LOG_DEFER
#define ctFeatMAX_LOG_DEFER
#endif
#endif

#if defined(ctFeatMAX_LOG_DEFER) && (!defined(MULTITRD) || !defined(TRANPROC) \
	|| !defined(ctrt_hrtimer))
#undef ctFeatMAX_LOG_DEFER
#endif

/*--------------------------------------------------------------*/
/* ctFeatSHMEMgrp enables support for c-tree Server's		*/
/* SHMEM_GROUP configuration option, which is used to set the	*/
/* group for c-tree Server's shared memory resources on Unix	*/
/* systems.							*/
/*								*/
/* ctFeatSHMEMgrp is on for c-tree Server when Unix shared	*/
/* memory support is enabled.					*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#ifdef ctFeatUNIX_SHMEM
#define ctFeatSHMEMgrp
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatVERIFYfile enables support for the file verification	*/
/* function.							*/
/*								*/
/* Default: ctFeatVERIFYfile is ON in version 10.3.1 and later	*/
/* when client/server index verify support is enabled. Not	*/
/* supported in the bound server operational model.		*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,3,1)
#ifndef NO_ctFeatVERIFYfile
#ifdef ctFeatVFYIDX_CS
#define ctFeatVERIFYfile
#endif
#endif
#endif

#ifdef ctFeatVERIFYfile
#ifdef ctBNDSRVR
#undef ctFeatVERIFYfile
#endif
#endif

#ifdef ctFeatVERIFYfile

#ifdef ctBNDSRVR
#error The bound server model does not support the file verification function
#endif

#ifndef ctFeatVFYIDX_CS
#error The file verification function requires client/server index verify support
#endif

#endif


/*--------------------------------------------------------------*/
/* ctFeatLOCKfile enables file level locking support.		*/
/*								*/
/* Default: ctFeatLOCKfile is ON in version 10.4.1 and later	*/
/* for c-tree Server. Requires server, user lock count support,	*/
/* and cannot be used with strict serialization support.	*/
/* Requires the Visual C 2008 compiler or later.                */
#ifdef ctPortWIN32
#if _MSC_VER < 1500	
#define NO_ctFeatLOCKfile
#endif
#endif
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1)
#ifndef NO_ctFeatLOCKfile
#if defined(ctSRVR) && defined(ctBEHAV_ULCNT) && defined(ctMULTIOPN) && !defined(ctSS)

#define ctFeatLOCKfile
/* Defer intent lock creation until a table lock request occurs: */
#define ctFeatLOCKfileDFRILK

/* One entry user lock cache */
#ifndef NO_ctFeatUSRLOKcache
#define ctFeatUSRLOKcache
#endif

#endif
#endif
#endif

#ifdef ctFeatLOCKfile

#ifndef ctSRVR
#error File lock support requires c-tree Server.
#endif

#ifndef ctBEHAV_ULCNT
#error File lock support requires user lock count support.
#endif

#ifndef ctMULTIOPN
#error File lock support requires multiple file open support.
#endif

#ifdef ctSS
#error File lock support is not compatible with strict serialization support.
#endif

#if defined(ctMULTIOPN) && !defined(ctBEHAV_MULTIOPN_LINK)
#error File lock support requires multiple open link support when multiple open support is enabled.
#endif

#endif

/*--------------------------------------------------------------*/
/* ctFeatBACKGROUNDflush enables flushing of updated data cache	*/
/* pages and index buffers for non-transaction-controlled	*/
/* files within a defined time limit.				*/
/*								*/
/* Default: ctFeatBACKGROUNDflush is ON for c-tree Server	*/
/* v10.5.0 and later. Requires buffer list management and	*/
/* snapshot support.						*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,5,0)
#ifdef ctSRVR
#ifndef NO_ctFeatBACKGROUNDflush
#if defined(ctBEHAV_BLM) && defined(ctFeatSNAPSHOT)
#define ctFeatBACKGROUNDflush
#endif
#endif
#endif
#endif

#ifdef ctFeatBACKGROUNDflush

/* Background flush update list timing buckets */
#ifndef NO_ctFeatBACKGROUNDflushBKT
#ifdef TRANPROC
#define ctFeatBACKGROUNDflushBKT
#endif
#endif

/* For non-TRNLOG files: */
#define NTFLS_DAT_LIMIT_DEFAULT		0	/* Default maximum time in
						** seconds before flushing a
						** dirty data page. */
#define NTFLS_IDX_LIMIT_DEFAULT		0	/* Default maximum time in
						** seconds before flushing a
						** dirty index buffer. */

#define NTFLS_DAT_BUCKET_DEFAULT	10	/* Default number of counter
						** buckets for dirty data
						** pages. */
#define NTFLS_IDX_BUCKET_DEFAULT	10	/* Default number of counter
						** buckets for dirty index
						** buffers. */

/* For TRNLOG files: */
#ifndef TRFLS_DAT_LIMIT_DEFAULT
#define TRFLS_DAT_LIMIT_DEFAULT		-1	/* Default maximum time in
						** seconds before flushing a
						** dirty data page. */
#endif
#ifndef TRFLS_IDX_LIMIT_DEFAULT
#define TRFLS_IDX_LIMIT_DEFAULT		-1	/* Default maximum time in
						** seconds before flushing a
						** dirty index buffer. */
#endif

#define TRFLS_DAT_BUCKET_DEFAULT	10	/* Default number of counter
						** buckets for dirty data
						** pages. */
#define TRFLS_IDX_BUCKET_DEFAULT	10	/* Default number of counter
						** buckets for dirty index
						** buffers. */

#ifdef ctMXLOGS
#error ctFeatBACKGROUNDflush is not supported when ctMXLOGS is enabled
#endif

#ifndef ctBEHAV_BLM
#error ctFeatBACKGROUNDflush requires ctBEHAV_BLM
#endif

#ifndef ctFeatSNAPSHOT
#error ctFeatBACKGROUNDflush requires snapshot support
#endif

/* When background flush thread support is enabled, disable the idle flush threads. */
#undef ctFeatIDLE_THREAD

#endif

/*--------------------------------------------------------------*/
/* ctFeatMAXACTCONN enables setting a limit on the number of	*/
/* concurrently-active connections.				*/
/*								*/
/* Default: ctFeatMAXACTCONN is ON for c-tree Server version	*/
/* 10.4.0 and later. Requires ctWORKMON, ctCACHE_MEMORY,	*/
/* ctFeatATOMICop.		*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0) && !defined(ctPortDSTINTL) /* ctPortDSTINTL_ONLY_QUESTION */
#ifndef NO_ctFeatMAXACTCONN
#if defined(ctSRVR) && defined(ctWORKMON) && defined(ctCACHE_MEMORY) && \
    defined(ctFeatATOMICop) && defined (ctFeatLicense10)
#define ctFeatMAXACTCONN
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatKBUFrefresh enables automatic population of ISAM key	*/
/* buffers as needed when the up-front population of ISAM key	*/
/* buffers is disabled.						*/
/*								*/
/* Default: ctFeatKBUFrefresh is ON for c-tree version 10.6.0	*/
/* and later and for ABACUS OEM. Requires ctBEHAV_MISSING_KEY.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1) || defined(ctPortABACUS)
#ifndef NO_ctFeatKBUFrefresh
#ifdef ctBEHAV_MISSING_KEY
#define ctFeatKBUFrefresh
#endif
#endif
#endif

#ifdef ctFeatKBUFrefresh
#ifndef ctBEHAV_MISSING_KEY
#error ISAM key buffer refresh requires ctBEHAV_MISSING_KEY
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatKILLSOCKETtimeout enables an improved approach to	*/
/* unblocking a client that is waiting on a socket read: we use	*/
/* a socket timeout, and the thread checks a state variable on	*/
/* each timeout to know if it has been requested to terminate.	*/
/* In our previous approach, another thread closed the socket	*/
/* in order to unblock the thread waiting on the socket read,	*/
/* but that approach has the problem that the socket descriptor	*/
/* could be assigned to another file and the original thread	*/
/* could then use that file descriptor (including closing it).	*/
/*								*/
/* Default: ctFeatKILLSOCKETtimeout is ON for c-tree Server	*/
/* version 10.4.0 and later and for Spillman OEM compiles.	*/
/* Requires ctFeatNONBLK_SOCKIO.				*/
/*--------------------------------------------------------------*/
#if (ctVER3_GE(10,4,0) || defined(ctPortSPILLMAN)) && !defined(ctPortDSTINTL) /* ctPortDSTINTL_ONLY_QUESTION */
#ifndef NO_ctFeatKILLSOCKETtimeout
#ifdef ctSRVR
#ifdef ctFeatNONBLK_SOCKIO
#define ctFeatKILLSOCKETtimeout
/* Time to wait on socket receive before checking for kill request */
#define KILL_SOCKET_TIMEOUT	10
#endif
#endif
#endif
#endif

#ifdef ctFeatKILLSOCKETtimeout

#ifndef ctSRVR
#error ctFeatKILLSOCKETtimeout requires c-tree Server operational model
#endif

#ifndef ctFeatNONBLK_SOCKIO
#error ctFeatKILLSOCKETtimeout requires support for non-blocking socket I/O
#endif

#endif

/*--------------------------------------------------------------*/
/* ctFeatDFRIDX enables support for deferring index operations.	*/
/*								*/
/* Default: ctFeatDFRIDX is ON in version 10.5.0 and later.	*/
/* Requires huge file support (for extended header), system	*/
/* queue support if server (due to preimage space use involving */
/* ctNotify feature), ctLOGAUG if TRANPROC.			*/
/* Requires the Visual C 2008 compiler or later.                */
#ifdef ctPortWIN32
#if _MSC_VER < 1500	
#define NO_ctFeatDFRIDX
#endif
#endif
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,5,0)
#ifndef NO_ctFeatDFRIDX
#ifdef TRANPROC
#ifdef ctHUGEFILE
#define ctFeatDFRIDX
/* Indicate that we turned on ctFeatDFRIDX in ctopt2.h: */
#define ctFeatDFRIDXctopt2
#endif
#endif
#endif
#endif

#ifdef ctFeatDFRIDX
#ifndef ctHUGEFILE
#error Deferred index support requires huge file support.
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatFUSRrwlock enables reader/writer lock control around	*/
/* the reallocation of a connection's ct_fusr array.		*/
/*								*/
/* Default: ctFeatFUSRrwlock is ON in version 10.4.1 and later	*/
/* for c-tree Server. Requires reader/writer lock support.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,1)
#ifndef NO_ctFeatFUSRrwlock
#ifdef MULTITRD
#ifdef ctFeatRWLOCK
#define ctFeatFUSRrwlock
#endif
#endif
#endif
#endif

#if defined(ctFeatLOCKfile) && defined(MULTITRD) && !defined(ctFeatFUSRrwlock)
#error Table lock requires FUSR reader/writer locks
#endif

/*--------------------------------------------------------------*/
/* ctFeatPHYSICAL_CPU_COUNT enables counting of physical CPUs	*/
/* on the system without considering the number of CPUs that	*/
/* the c-tree Server process is bound to.			*/
/*								*/
/* Default: ctFeatPHYSICAL_CPU_COUNT is ON in version 10.6.0 	*/
/* and later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,6,0) || defined(ctPortACI)
#if (defined(ctPortAIX_5_2) || defined(ctPortAIX_5_3))
#ifndef NO_ctFeatPHYSICAL_CPU_COUNT
#define NO_ctFeatPHYSICAL_CPU_COUNT
#endif
#endif

#if (defined(ctPortWIN32) && _MSC_VER <= 1200)
#ifndef NO_ctFeatPHYSICAL_CPU_COUNT
#define NO_ctFeatPHYSICAL_CPU_COUNT
#endif
#endif

#ifndef NO_ctFeatPHYSICAL_CPU_COUNT
#define ctFeatPHYSICAL_CPU_COUNT
#endif
#endif

/* Modes for ctGetCPU_AFFINITY() */
#define ctGET_LOGICAL_CPUS	0
#define ctGET_PHYSICAL_CPUS	1

#ifndef ctCPU_COUNT_MODE
/* By default, we use our original method of counting logical CPUs. */
#define ctCPU_COUNT_MODE ctGET_LOGICAL_CPUS
#endif

#if ctVER3_GE(10,5,0)
#if (!defined(NO_ctFeatDYNPARTRUL) && defined(ctPARTITION))
#define ctFeatDYNPARTRUL
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatRUCB enables support for record update callbacks.	*/
/*								*/
/* Default: ctFeatRUCB is ON in version 10.5.0 and later.	*/
/* Requires deferred index support, and in server model also	*/
/* requires atomic operation support.				*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,5,0)
#ifndef NO_ctFeatRUCB
#if defined(ctFeatDFRIDX) && (!defined(MULTITRD) || defined(ctFeatATOMICop))
#define ctFeatRUCB
/* Indicate that we turned on ctFeatRUCB in ctopt2.h: */
#define ctFeatRUCBctopt2
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPL_FILTERfile enables support for controlling which	*/
/* files' updates are sent to a given replication agent.	*/
/*								*/
/* Default: ctFeatREPL_FILTERfile is ON in version 10.4.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0)
#ifndef NO_ctFeatREPL_FILTERfile
#ifdef ctFeatREPLICAT
#define ctFeatREPL_FILTERfile
#endif
#endif
#endif

#if defined(ctFeatREPL_FILTERfile) && defined(MULTITRD)
#define ctFeatREPL_FILTERfileSRV
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPL_FILTER_CHANGE adds the support for changing the   */
/* replication file filter on-the-fly                           */
/*                                                              */
/* Default: ctFeatREPL_FILTER_CHANGE is ON in the v11.3.1 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if defined(ctFeatREPL_FILTERfile) && ctVER3_GE(11,3,1)
#ifndef NO_ctFeatREPL_FILTER_CHANGE
#define ctFeatREPL_FILTER_CHANGE
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPL_DEFERtran enables support for delaying sending a	*/
/* transaction begin entry to a replication reader until the	*/
/* first operation in the transaction is going to be sent to	*/
/* the replication reader. This feature avoids sending empty  	*/
/* transactions to the replication reader when the replication	*/
/* reader is configured to receive activity for only some of	*/
/* the replicated files.					*/
/*								*/
/* Default: ctFeatREPL_DEFERtran is ON in version 10.4.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0)
#ifndef NO_ctFeatREPL_DEFERtran
#define ctFeatREPL_DEFERtran
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatMEMFILErefcnt adds state information to each memory	*/
/* file record so that the timing of the freeing of the memory	*/
/* record can be properly coordinated with concurrent readers.	*/
/*								*/
/* Default: ctFeatMEMFILErefcnt is ON for c-tree Server v10.4.0 */
/* and later. Requires memory file and atomic operation support.*/ 
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0)
#ifndef NO_ctFeatMEMFILErefcnt
#if defined(ctSRVR) && defined(ctFeatMEMFILE) && defined(ctFeatATOMICop)
#define ctFeatMEMFILErefcnt
#endif
#endif
#endif

/* Read the reference count value. */
#define ctMEMFILEgetrefcnt(curstate) (COUNT) (((curstate) & 0x7fffffff) >> 16)

/* Set the reference count value. */
#define ctMEMFILEsetrefcnt(curstate,newrefcnt) (((ULONG) (curstate) & 0x80000000) | ((curstate) & 0x0000ffff) | ((newrefcnt) << 16))

/* Read the delete bit. */
#define ctMEMFILEgetdelbit(curstate) (NINT) (((curstate) & 0x80000000) >> 31)

/* Set the delete bit. */
#define ctMEMFILEsetdelbit(curstate,delbit) (ULONG) (delbit ? ((curstate) | 0x80000000) : ((curstate) & 0x7fffffff))

/* Read the musr value. */
#define ctMEMFILEgetmusr(curstate) (NINT) (curstate & 0x0000ffff)

/* Set the musr value. */
#define ctMEMFILEsetmusr(curstate,musr) (ULONG) ((curstate & 0xffff0000) | (musr & 0x0000ffff))

/*--------------------------------------------------------------*/
/* ctFeatABLISThash changes the abort node list from a linear	*/
/* list to a hash list. The intent is to improve performance	*/
/* for transactions that add and/or delete many key values in a	*/
/* transaction-controlled index file.				*/
/*								*/
/* Default: ctFeatABLISThash is ON in v11.3.1 and later.	*/
/*--------------------------------------------------------------*/

#if ctVER3_GE(11,3,1)
#ifndef NO_ctFeatABLISThash
#ifdef MULTITRD
#define ctFeatABLISThash
#endif
#endif
#endif

#ifdef ctFeatABLISThash
#define NUMABL 128 /* number of abort node list hash bins per file */
#define ablistN(hash) ablist[hash]
#else
#define ablistN(hash) ablist
#endif

/*--------------------------------------------------------------*/
/* ctFeatCLICB introduces a general ability for a c-tree Server	*/
/* function to call back to the client before the c-tree	*/
/* function has finished its execution. We already supported	*/
/* this type of functionality for the index verify function	*/
/* for example. These generic client callbacks can be used by	*/
/* other c-tree functions.					*/
/*								*/
/* Default: ctFeatCLICB is ON for c-tree Server v11.0.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#ifdef ctSRVR
#if ctVER3_GE(11,0,0)
#ifndef NO_ctFeatCLICB
#define ctFeatCLICB
#endif
#endif
#endif

#if (defined(ctCLIENT) || defined(ctLOCLIB)) && !defined(ctFeatTRANSFER_FILE)
#define NO_ctFeatDYNDMPstream /* requires ctFeatTRANSFER_FILE */
#endif

/*--------------------------------------------------------------*/
/* ctFeatDYNDMPstream allows a client to request the server to	*/
/* send the dynamic dump stream directly to it through its	*/
/* communication channel.					*/
/*								*/
/* Default: ctFeatDYNDMPstream is ON for v11.0.0 and later.	*/
/* Using this feature in the server requires the client		*/
/* callback feature to be enabled.				*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,0,0)
#ifndef NO_ctFeatDYNDMPstream
#if !defined(ctSRVR) || defined(ctFeatCLICB)
#define ctFeatDYNDMPstream
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatFULLTEXTIDX allows support for full text type indexes  */
/*                                                              */
/* Default: ctFeatFULLTEXTIDX is ON in V11.3.1 and later	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,3,1)
#ifndef NO_ctFeatFULLTEXTIDX
#ifndef ctSQLMTFPG
#define ctFeatFULLTEXTIDX
/* Indicate that we turned on ctFeatFULLTEXTIDX in ctopt2.h: */
#define ctFeatFULLTEXTIDXctopt2
#define RUCBGCB_FULLTEXT_DLLNAME "<ctfultxt>"
#define RUCBGCB_FULLTEXT_CBKNAME "$FTS$"
#define RUCBGCB_FULLTEXT_CBKLOAD "$LDR$"
#define RUCBGCB_FULLTEXT_CBKSIZ 5 /* strlen(RUCBGCB_FULLTEXT_CBKNAME) */
#endif
#endif

#ifndef NO_ctFeatFTS_STOPLIST
/* stop list support */
#define ctFeatFTS_STOPLIST
#endif

#endif

/*--------------------------------------------------------------*/
/* ctFeatFTS_MULTI_FIELDS enables support for creating a full	*/
/* text index containing multiple fields.			*/
/*                                                              */
/* Default: OFF (not yet supported).                            */
/*--------------------------------------------------------------*/
/*
#define ctFeatFTS_MULTI_FIELDS
*/

/*--------------------------------------------------------------*/
/* ctFeatSRVRpower enables server connection concurrency	*/
/* control.							*/
/*								*/
/* Default: ctFeatSRVRpower is off.				*/
/* Requires ctFeatMAXACTCONN.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatSRVRpower
#if defined(ctSRVR) && defined(ctFeatMAXACTCONN)
/* #define ctFeatSRVRpower */
#endif
#endif

#ifdef ctFeatSRVRpower

#ifndef NO_ctFeatSRVRpowerLOK
/* Blocking lock requests take the time quantum into effect. After waiting for
** the time quantum on a lock request, a thread is made inactive. We also allow
** threads that are holding locks to be made inactive. */
#define ctFeatSRVRpowerLOK
#endif

/* Communication receive timeout is in milliseconds instead of seconds */
#define ctFeatCOMMtimeoutMSEC

#ifdef ctFeatKILLSOCKETtimeout
#undef KILL_SOCKET_TIMEOUT
/* Redefine time to wait on socket receive before checking for kill request
** in milliseconds instead of seconds. */
#define KILL_SOCKET_TIMEOUT	10000
#endif

#define ctTIMEOUT2MSEC(timeout) (timeout) /* This value is already in milliseconds */
#define ctSEC2TIMEOUT(timeout) ((timeout) * 1000) /* Convert this value from seconds to milliseconds */

#else

#define ctTIMEOUT2MSEC(timeout) ((timeout) * 1000) /* Convert this value from seconds to milliseconds */
#define ctSEC2TIMEOUT(timeout) (timeout) /* This value is in seconds; no conversion needed */

#endif

/*--------------------------------------------------------------*/
/* ctFeatCMTDLYMIN sets a minimum commit delay time. When the	*/
/* commit flush thread calculates how long to wait for cohorts	*/
/* before it flushes the log buffer, the minimum delay time is	*/
/* used as follows: if the calculated delay is greater than	*/
/* zero and less than the minimum time, then we use the minimum	*/
/* time.							*/
/*								*/
/* The minimum defaults to 1000 microseconds (1 millisecond)	*/
/* on systems that use our ct_udefer_yld() function for micro-	*/
/* second yields (Windows), and defaults to zero otherwise.	*/
/*								*/
/* If you wish to override the default, use the configuration	*/
/* option COMMIT_DELAY_MINIMUM <usec>. For example, if you want	*/
/* to set no minimum time, specify COMMIT_DELAY_MINIMUM 0. This	*/
/* configuration option converts a negative value to zero.	*/
/*								*/
/* Default: ctFeatCMTDLYMIN is ON for server when transaction	*/
/* processing is supported.					*/
/*--------------------------------------------------------------*/
#ifndef NO_ctFeatCMTDLYMIN
#if defined(TRANPROC) && defined(MULTITRD)
#define ctFeatCMTDLYMIN
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatDYNDMPrepl allows a dynamic dump to enable replication	*/
/* for specified files that it is backing up.			*/
/*								*/
/* Default: ctFeatDYNDMPrepl ON for v11.0.0 and later.		*/
/* Requires server and ctFeatDYNDMPstream.			*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,0,0)
#ifndef NO_ctFeatDYNDMPrepl
#if defined(ctSRVR) && defined(ctFeatDYNDMPstream) && defined(ctFeatREPLICAT)
#ifdef TRANPROC
#define ctFeatDYNDMPrepl
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatV11SERVERdefaults enables new c-tree Server default	*/
/* configuration option values.					*/
/*								*/
/* Default: ctFeatV11SERVERdefaults is ON for v11.0.0 server.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,0,0) && defined(ctSRVR)
#ifndef NO_ctFeatV11SERVERdefaults
#define ctFeatV11SERVERdefaults
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatPNDIDX enables support for creating indices when the	*/
/* data file is open in shared mode.				*/
/*								*/
/* Default: ctFeatPNDIDX is ON in version 11.0.0 and later.	*/
/* Requires deferred index support.				*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,0,0)
#ifndef NO_ctFeatPNDIDX
#define ctFeatPNDIDX
/* Indicate that we turned on ctFeatPNDIDX in ctopt2.h: */
#define ctFeatPNDIDXctopt2
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPL_EXCEPCB enables support for providing a callback  */
/* function for the Replication Exception.                      */
/*                                                              */
/* Default: ctFeatREPL_EXCEPCB is ON in version 11.0.0 and      */
/* later.                                                       */
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,0,0)
#ifndef NO_ctFeatREPL_EXCEPCB
#define ctFeatREPL_EXCEPCB
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPLAGENTprofile enables replication agent function	*/
/* call profiling.						*/
/*								*/
/* Default: ctFeatREPLAGENTprofile is ON in version 11.0.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,0,0)
#ifndef NO_ctFeatREPLAGENTprofile
#define ctFeatREPLAGENTprofile
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPLAGENTresync enables replication agent function	*/
/* to resync a list of files.					*/
/*								*/
/* Default: ctFeatREPLAGENTresync is ON in the v11.3.1 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,3,1)
#ifndef NO_ctFeatREPLAGENTresync
#define ctFeatREPLAGENTresync
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPLAGENTunreg enables replication agent function	*/
/* to unregister from the source server				*/
/*								*/
/* Default: ctFeatREPLAGENTunreg is ON in the v11.3.1 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,3,1)
#ifndef NO_ctFeatREPLAGENTunreg
#define ctFeatREPLAGENTunreg
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatMEMTRACKcorrect changes SNAPSHOT and SYSCFG calls	*/
/* to no longer use the ctmemsum, ctmemgh and ctmemtrk_net 	*/
/* counters, which have meaningless data in MULTITRD. 		*/
/*								*/
/* Default: ctFeatMEMTRACKcorrect is ON in version 10.4.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(10,4,0)
#ifndef NO_ctFeatMEMTRACKcorrect
#ifdef ctFeatMEMTRACKsublist
#define ctFeatMEMTRACKcorrect
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatADDIDXMBR allows PRMIIDX to add an index member to a	*/
/* host index.							*/
/*								*/
/* Default: ctFeatADDIDXMBR is ON for c-tree Server in version	*/
/* 11.2.0 and later.						*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifdef ctSRVR
#ifndef NO_ctFeatADDIDXMBR
#define ctFeatADDIDXMBR
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatRBLSORT enables rebuild sort improvements.		*/
/*								*/
/* Default: ctFeatRBLSORT is ON for c-tree Server in version	*/
/* 11.2.0 and later.						*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifdef ctSRVR
#ifndef NO_ctFeatRBLSORT
#define ctFeatRBLSORT
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatIOPRF enables collection of disk read and write call	*/
/* counts and times made by ctsysio81(). We used this option to	*/
/* measure the time spent in disk I/O calls during rebuild	*/
/* options in standalone mode.					*/
/*								*/
/* Note the following limitations of this code:			*/
/*								*/
/* 1) This code uses global variables with no mutex control,	*/
/*    so it is not appropriate to use in a multi-threaded	*/
/*    operational model if multiple threads will call		*/
/*    ctsysio81() at the same time.				*/
/*								*/
/* 2) We only added the high resolution timer calls for the	*/
/*    Windows disk read and write system calls used in the	*/
/*    standalone operational model. If we want to use this	*/
/*    feature on other operating systems or for the server	*/
/*    operational model, we'll need to add high resolution	*/
/*    timer calls in the proper location for those cases.	*/
/*								*/
/* Default: ctFeatIOPRF is OFF.					*/
/*--------------------------------------------------------------*/
/* #define ctFeatIOPRF */

/*--------------------------------------------------------------*/
/* ctFeatLOADKEYopt enables optimizations to LOADKEY.		*/
/*								*/
/* Default: ctFeatLOADKEYopt is ON in version 11.2.0 and later.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctFeatLOADKEYopt
#define ctFeatLOADKEYopt
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatLOADKEYoptSKIM optimizes the skim() routine, which is	*/
/* used to scan the tree if LOADKEY is called for an index that	*/
/* contains an existing tree. Instead of reading every node, we	*/
/* read only the leftmost and rightmost nodes at each level of	*/
/* the tree.							*/
/*								*/
/* Default: ctFeatLOADKEYoptSKIM is ON in version 11.2.0 and	*/
/* later.							*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctFeatLOADKEYoptSKIM
#define ctFeatLOADKEYoptSKIM
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatSHR2XCL enables support for switching a file from	*/
/* shared to exclusive mode as long as the file is open only	*/
/* once, by the calling connection.				*/
/*								*/
/* Default: ctFeatSHR2XCL is ON for c-tree Server in version	*/
/* 11.2.0 and later.						*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifdef ctSRVR
#ifndef NO_ctFeatSHR2XCL
#define ctFeatSHR2XCL
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatPOSIXSIGNALS adds logic for handling all POSIX defined	*/
/* signals							*/
/*								*/
/* Default: ctFeatPOSIXSIGNALS is ON for c-tree Server in 	*/
/* version 11.2.0 and later.					*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifdef ctSRVR
#ifndef NO_ctFeatPOSIXSIGNALS
#ifdef ctPortUNIX
#define ctFeatPOSIXSIGNALS
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatLOWBEGLOG adds an entry to the checkpoint header to	*/
/* hold the log number of the minimum log needed by recovery	*/
/* as of that checkpoint. That log is the log containing the	*/
/* transaction begin of the oldest transaction that is still	*/
/* pending as of the checkpoint.				*/
/*								*/
/* Default: ctFeatLOWBEGLOG is ON in version 11.2.0 and later.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctFeatLOWBEGLOG
#define ctFeatLOWBEGLOG
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatRBLSAVRESopt enables performance improvements to the	*/
/* scanning of an index during rebuild in order to read its	*/
/* resources. Previously these changes were controlled by	*/
/* #define ctFeatRBLSORT. By changing this to a new #define, we	*/
/* are able to enable it for all operational models without	*/
/* enabling the server-only rebuild enhancements for all models.*/
/*								*/
/* Default: ctFeatRBLSAVRESopt is ON in v11.2.0 and later.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctFeatRBLSAVRESopt
#define ctFeatRBLSAVRESopt
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatFPGloktimout enables blocking lock timeout support in	*/
/* FPUTFGET mode.						*/
/*								*/
/* Default: ctFeatFPGloktimout is ON in v11.2.0 and later for	*/
/* FPUTFGET mode on Windows systems for the SQL FPUTFGET model.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctFeatFPGloktimout
#if defined(FPUTFGET) && defined(ctPortWIN32)
#ifdef ctSQLMTFPG
#define ctFeatFPGloktimout
#define ctIOSEMA	/* reduce use of individual file I/O semaphores */
#define ctIOSEMAasync	/* use async I/O */
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatWAITFORopt reduces memory used for c-tree Server's	*/
/* lock wait-for graph by using one byte per entry instead of	*/
/* four bytes per entry.					*/
/*								*/
/* Default: ctFeatWAITFORopt is ON in v11.2.0 and later.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,2,0)
#ifndef NO_ctFeatWAITFORopt
#define ctFeatWAITFORopt
#endif
#endif

#ifndef ctFeatWAITFORopt
/*
** Wait-for graph uses one byte per entry.
*/
#define ct_wfGET(a,b) ct_wf[a][b]
#ifdef ctDBGfcqa
#define ct_wfINC(a,b) { if (++ct_wf[a][b] > 2) ctbpf(); }
#define ct_wfDEC(a,b) { if (--ct_wf[a][b] < 0) ctbpf(); }
#else
#define ct_wfINC(a,b) ++ct_wf[a][b]
#define ct_wfDEC(a,b) --ct_wf[a][b]
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatTRANIDX_LOPN_ERR_CONTINUE allows tranidx() to continue	*/
/* automatic transaction recovery when it can't open a previous	*/
/* log file. If recovery then completes successfully we log a	*/
/* message to CTSTATUS.FCS to indicate that all indexes active	*/
/* at the checkpoint used by recovery should be rebuilt.	*/
/*								*/
/* Default: ctFeatTRANIDX_LOPN_ERR_CONTINUE is ON.		*/
/*--------------------------------------------------------------*/
#define ctFeatTRANIDX_LOPN_ERR_CONTINUE

/*--------------------------------------------------------------*/
/* ctFeatFLSHSAVErwl uses a reader/writer lock instead of a	*/
/* tflstt bit to ensure that a file cannot be closed while it	*/
/* is being flushed.						*/
/*								*/
/* Default: Enabled in v11.3.0 and later.		*/
/* Requires reader/writer lock support.				*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,3,0)
#ifndef NO_ctFeatFLSHSAVErwl
#ifdef ctFeatRWLOCK
#define ctFeatFLSHSAVErwl
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatFILELISTrwl uses a reader/writer lock instead of the	*/
/* file open/close mutex to control access to the server's file	*/
/* lists.							*/
/*								*/
/* Default: Enabled in v11.3.0 and later.		*/
/* Requires reader/writer lock support.				*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,3,0)
#ifndef NO_ctFeatFILELISTrwl
#ifdef ctFeatRWLOCK
#define ctFeatFILELISTrwl
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatCRITSECTSPIN enables a configurable spin count on	*/
/* c-tree Server critical section/mutex requests.		*/
/*								*/
/* Default: ctFeatCRITSECTSPIN is ON for Windows when our mutex	*/
/* is implemented as a critical section (ctFeatW32_MUTXCS) and	*/
/* ON for Unix in v11.3.1 and later				*/
/*--------------------------------------------------------------*/
#ifdef ctThrds
#if defined(ctFeatW32_MUTXCS) || (defined(ctPortUNIX) && ctVER3_GE(11,3,1))
#ifndef NO_ctFeatCRITSECTSPIN
#define ctFeatCRITSECTSPIN
#endif
#endif
#endif

/* Default setting for CRITICAL_SECTION_SPIN configuration option. */
#ifdef ctPortWIN32
#define ctCRITSECTSPIN_DEFAULT 1000
#else
#define ctCRITSECTSPIN_DEFAULT 0
#endif

/*--------------------------------------------------------------*/
/* ctFeatSTANDARDIZE_LIBNAME enables an application to specify	*/
/* that a DLL or shared library name that is loaded by c-tree	*/
/* is to be converted to standard format for the target system.	*/
/* An one example, this feature makes it possible to store a	*/
/* system-independent reference to an external record update	*/
/* callback library in a c-tree data file.			*/
/*								*/
/* To use this feature, when you specify the name of the shared	*/
/* library or DLL, set its first character to the value		*/
/* ctLIBNAME_STANDARD_CHR (currently defined as '^').		*/
/*								*/
/* Default: ctFeatSTANDARDIZE_LIBNAME is ON by default in	*/
/* v11.0 and later.						*/
/*--------------------------------------------------------------*/
#if ctVER_GE(11,0)
#ifndef NO_ctFeatSTANDARDIZE_LIBNAME
#define ctFeatSTANDARDIZE_LIBNAME
#endif
#endif

#define ctLIBNAME_STANDARD_CHR '^' /* char to indicate that library name should be standardized */
#define ctLIBNAME_STANDARD_MAX 10 /* max chars added when standardizing library name ("lib" + ".dylib" + "\0") */
#define ctLIBNAME_STANDARD_LIB "lib" /* shared library prefix */
#define ctLIBNAME_STANDARD_LIBLEN (NINT) strlen(ctLIBNAME_STANDARD_LIB) /* length of shared library prefix */

/*--------------------------------------------------------------*/
/* ctFeatFLEXREC enables flexible record format support. A	*/
/* variable-length data file that uses this feature is able to	*/
/* alter its schema dynamically, without having to immediately	*/
/* convert all records to the new format. The database engine	*/
/* automatically converts records from old formats to the	*/
/* current format as they are read.				*/
/*								*/
/* Default: ctFeatFLEXREC is ON in v11.3.0 and later. Requires	*/
/* huge file support.						*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,3,0)
#ifndef NO_ctFeatFLEXREC
#ifdef ctHUGEFILE
#define ctFeatFLEXREC
/* Indicate that we turned on ctFeatFLEXREC in ctopt2.h: */
#define ctFeatFLEXRECctopt2
#define RUCBGCB_FLEXREC_CBKCONV "$CNV$"
#define RUCBGCB_FLEXREC_CBKSIZ 5  /* strlen(RUCBGCB_FLEXREC_CBKCONV) */
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatREPL_TARGET_SVN adds the replication replica server    */
/* name into the check point on the source server. Based on     */
/* that, we are able to list all the replication agents         */
/* registered by the source server and check to which target    */
/* server it is establishing the replication.                   */
/*                                                              */
/* Default: ctFeatREPL_TARGET_SVN is ON in v11.3.1 and later.	*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,3,1)
#ifndef ctFeatREPL_TARGET_SVN
#define ctFeatREPL_TARGET_SVN

#ifdef ctGRMSvern
#undef ctGRMSvern
#define ctGRMSvern	2	/* ctGRMS (replication reader) version #	*/
#endif

#endif
#endif

/*----------------------------------------------------------------------------
ctFeatBACKGROUNDflushRATE adds support for configuring a fixed rate of
background flushing of updated data cache pages and index buffers. The two
parameters that can be specified for the background flushing are:

	msec: The time in milliseconds to defer after flushing, and
	nfls: The number of flushes after which the defer occurs.

The background flush thread configuration options NONTRAN_DATA_FLUSH_SEC,
NONTRAN_INDEX_FLUSH_SEC, TRAN_DATA_FLUSH_SEC, AND TRAN_INDEX_FLUSH_SEC now
support specifying these parameters using the syntax rate=<msec>/<nfls>.

For example, to defer for 1 millisecond after every two flushes of updated
TRNLOG data cache pages, use this option:

	TRAN_DATA_FLUSH_SEC rate=1/2

Default: Enabled in v11.3.1 and later and for DST OEM compiles.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1) || defined(ctPortDSTINTL)
#ifdef ctFeatBACKGROUNDflush
#ifndef NO_ctFeatBACKGROUNDflushRATE
#define ctFeatBACKGROUNDflushRATE
#endif
#endif
#endif

/*----------------------------------------------------------------------------
ctFeatBACKGROUNDflushMTXOPT changes the background flush threads to avoid
holding the update list mutex while flushing an updated buffer.

Default: Enabled in v11.3.1 and later and for DST OEM compiles.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1) || defined(ctPortDSTINTL)
#ifdef ctFeatBACKGROUNDflush
#ifndef NO_ctFeatBACKGROUNDflushMTXOPT
#define ctFeatBACKGROUNDflushMTXOPT
#endif
#endif
#endif

#ifdef ctFeatBACKGROUNDflushMTXOPT
/* When the background flush mutex optimization is enabled, we don't have proper
mutex control over access to the background flush bucket state variables, so we
turn off support for the background flush buckets. */
#undef ctFeatBACKGROUNDflushBKT
#endif

/*----------------------------------------------------------------------------
  ctFeatDELSTK_COMMIT_SEC enables the DELSTK_COMMIT_SEC server configuration
  option. This option can be used to improve performance of committing record
  deletes in a fixed-length data file that uses the TDATA_WRITETHRU option.

  Specifying the option:
  
  DELSTK_COMMIT_SEC nsec

  in ctsrvr.cfg, where nsec is greater than zero, causes commits of fixed-
  length record deletes in files that use the TDATA_WRITETHRU option to only
  write the delete stack value to the file's header at most every nsec
  seconds. This means that in the event of a server crash, the delete stack
  value in the header can be out of date, not accounting for the last nsec
  seconds of deleted records. This just means that some space in the file
  will not be available for reuse after automatic recovery.

  Note the following limitation of this feature: the last nsec of updates to
  the delete stack can remain in memory (not written to the file's header on
  disk) for an arbitrary amount of time. Again, this only affects the ability
  to reuse space in the event of a server crash.

  Default: On for c-tree Server. Requires transaction control, huge file
  support, and high-resolution timer support.
----------------------------------------------------------------------------*/
#ifndef NO_ctFeatDELSTK_COMMIT_SEC
#if defined(ctSRVR) && defined(TRANPROC) && defined(ctHUGEFILE) && defined(ctrt_hrtimer)
#define ctFeatDELSTK_COMMIT_SEC
#endif
#endif

/* Limit for DELSTK_COMMIT_SEC option. */
#define MAX_DELSTK_COMMIT_SEC 30

/*--------------------------------------------------------------*/
/* ctFeatTEMPDIR enables c-tree's temporary directory API	*/
/* function.							*/
/*								*/
/* Default: ctFeatTEMPDIR is ON in v11.3.1 and later		*/
/* for c-tree client and server models. 			*/
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,3,1)
#ifndef NO_ctFeatTEMPDIR
#if (defined(ctSRVR) && defined(CTS_ISAM)) || defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctCLISIDE)
#define ctFeatTEMPDIR
#endif
#endif
#endif

#ifdef ctFeatTEMPDIR
#if !((defined(ctSRVR) && defined(CTS_ISAM)) || defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctCLISIDE))
#error ctFeatTEMPDIR requires Server with ISAM, or client
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatICONTEXTlowl extends ISAM contexts to also store the current low-level
  key value for each index file that is included in the ISAM context.

  Default: We default this option OFF because it is possible to avoid the
  issue that this option addresses simply by performing an ISAM record read
  after the low level key lookup (for example, GTEKEY then REDIREC/REDIVREC).
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1)
#ifndef NO_ctFeatICONTEXTlowl
/* #define ctFeatICONTEXTlowl */
#endif
#endif

#ifdef ctFeatICONTEXTlowl
#define ctCONBUFNKV 2 /* ISAM context stores ISAM and low-level key values */
#else
#define ctCONBUFNKV 1 /* ISAM context stores only ISAM key value */
#endif

/*----------------------------------------------------------------------------
  ctFeatRP_AUTO enables support for automatic restore points.

  Default: Enabled for server when restore point and subsystem support are
  enabled.
----------------------------------------------------------------------------*/
#if defined(ctSRVR) && defined(ctFeatRP) && defined(ctFeatCFGsubsys2)
#ifndef NO_ctFeatRP_AUTO
#define ctFeatRP_AUTO
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatREPL_EXTENSION_LIB enables support for the replication agent's
  extension library.

  Default: Enabled in v11.3.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,0)
#ifndef NO_ctFeatREPL_EXTENSION_LIB
#define ctFeatREPL_EXTENSION_LIB
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatINTERMEDIATE_BLOCK_PAGING replaces direct read and write operations
  on c-tree data files for intermediate blocks of the file (as determined by
  c-tree's block I/O routine) with reads and writes to c-tree cache pages.
  We use the scanner LRU feature to limit the number of cache pages that we
  use for the block read or write operation.

  Requires server operational model and scanner LRU feature.

  Enabled in v11.3.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1)
#ifndef NO_ctFeatINTERMEDIATE_BLOCK_PAGING
#ifdef MULTITRD
#ifdef ctFeatSCANCACHE
#define ctFeatINTERMEDIATE_BLOCK_PAGING
#endif
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatREPLICAT_QUIET enables support for ctQUIET() waiting for replication
  readers to finish processing all log entries and report that they are
  caught up before ctQUIET() returns to the caller.

  First activated in v11.3.1 - Requires replication support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1) || (ctVER3_GE(11,2,2) && defined(ctPortCHARGER1))
#ifndef NO_ctFeatREPLICAT_QUIET
#ifdef ctFeatREPLICAT
#define ctFeatREPLICAT_QUIET
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatDISKFULLactionEXT enables extensions to the DISK_FULL_ACTION server
  configuration option.

  Enabled in v11.3.1 forward. Requires disk full action support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1) || (ctVER3_GE(11,2,2) && defined(ctPortCHARGER1))
#ifndef NO_ctFeatDISKFULLactionEXT
#ifdef ctFeatDISKFULLaction

#define ctFeatDISKFULLactionEXT

#ifdef ctPortUNIX
#define ctFeatDISKFULLactionEXT_UNX
#endif

/* Default value in seconds for DISK_FULL_ACTION FREQ option: */
#define ctCFG_DEFAULT_DISK_FULL_ACTION_FREQ 60

/* Maximum value in seconds for DISK_FULL_ACTION FREQ option: */
#define ctCFG_MAX_DISK_FULL_ACTION_FREQ 32000000

/* Default value in seconds for DISK_FULL_ACTION MAXRUNTIME option: */
#define ctCFG_DEFAULT_DISK_FULL_ACTION_MAXRUNTIME 60

/* Maximum value in seconds for DISK_FULL_ACTION MAXRUNTIME option: */
#define ctCFG_MAX_DISK_FULL_ACTION_MAXRUNTIME 3600

#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatREPLAGENTstt enables support for the c-tree Server DLL to maintain a
  list of replication state pointers for each replication agent that has
  registered itself with the server DLL. Also controls the enhancements to
  ctReplAgentOp() to pass the agent ID to the server DLL.

  Enabled in v11.3.1 and later
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1)
#ifndef NO_ctFeatREPLAGENTstt
#if defined(TRANPROC) && defined(ctFeatREPLICAT)
#define ctFeatREPLAGENTstt
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatREPLAGENTargs enables support for the c-tree Server DLL to receive a
  list of command-line arguments used when initializing the database engine.

  Enabled in v11.3.1 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1) || (ctVER3_GE(11,2,2) && defined(ctPortCHARGER1))
#ifndef NO_ctFeatREPLAGENTargs
#define ctFeatREPLAGENTargs
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatCHECKLOCKrt enables support for turning on ctCHECKLOCK for the
  specified c-tree data files at runtime, using a c-tree Server configuration
  option or a call to the ctSETCFG() API function.

  Enabled in v11.3.1 forward. Requires server.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,3,1) || (ctVER3_GE(11,2,2) && defined(ctPortCHARGER1))
#ifdef ctSRVR
#ifndef NO_ctFeatCHECKLOCKrt
#define ctFeatCHECKLOCKrt
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatFUSRCLRoptimize optimizes the ctfusrclr() function, which updates
  user file state variables at the end of a transaction. Instead of looping
  over all files that are open by the calling connection, as we update files
  in a transaction we add them to a list, and ctfusrclr() loops over only the
  entries that are in the list.

  Enabled in v11.5.0 and later. Only implemented for server model.
  Requires ctBEHAV_FUSRCLR.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,0)
#ifndef NO_ctFeatFUSRCLRoptimize
#ifdef ctSRVR
#ifdef TRANPROC
#ifdef ctBEHAV_FUSRCLR
#define ctFeatFUSRCLRoptimize
#endif
#endif
#endif
#endif
#endif


/*-----------------------------------------------------------------------------
  ctFeatDumpSYNC enables optional periodic sync calls on the dynamic dump
  backup to reduce the amount of cache the filesystem devotes to this file.

  Enabled for Unix Servers
-----------------------------------------------------------------------------*/

#ifndef NO_ctFeatDumpSYNC
#ifdef ctSRVR
#ifdef ctPortUNIX
#ifdef ctFeatDYNDMPstream
#define ctFeatDumpSYNC
#define MAX_DUMP_SYNC_INTERVAL 0xffffffffUL
#define MIN_DUMP_SYNC_INTERVAL 0x00100000UL /* 1 MB */
#endif
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatDISTismcnt enables the use of distributed counters for the ISAM
  snapshot counters.

  Enabled in v11.2.2 forward. Only implemented for server model. Requires snapshot
  support and 64-bit atomic operation support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,2,2)
#if defined(ctSRVR) && defined(ctFeatSNAPSHOT) && defined(ctFeatATOMICop64)
#ifndef NO_ctFeatDISTismcnt
#define ctFeatDISTismcnt
#endif
#endif
#endif

/* Default number of distributed ISAM counter buckets. */
#define ctDEFAULT_DIST_ISAM_COUNTER_BUCKETS	8

/* Maximum number of distributed ISAM counter buckets. */
#define ctMAX_DIST_ISAM_COUNTER_BUCKETS		1024

/*----------------------------------------------------------------------------
  ctFeatDYNDMPirstx improves c-tree Server's control over the launching of the
  external ctrdmp process that occurs when performing an immediate restore
  during a dynamic dump. The server also reads the output of the dump restore
  and sends notifications to the client as to the progress of the dump restore
  if requested by the client.

  Enabled in v11.2.3 and later. Requires ctFeatDISKFULLactionEXT.
-----------------------------------------------------------------------------*/
#if ctVER3_GE(11,2,3)
#ifndef NO_ctFeatDYNDMPirstx
#ifdef ctFeatDISKFULLactionEXT
#define ctFeatDYNDMPirstx
#endif
#endif
#endif

#ifdef ctFeatDYNDMPirstx

#ifndef ctFeatDISKFULLactionEXT
#error Enhanced immediate restore process control requires disk full action extensions to be enabled.
#endif

#endif

/*----------------------------------------------------------------------------
  ctFeatCTRDMPprogress adds support to the ctrdmp utility for outputing
  progress messages when the !IMMEDIATE_RESTORE_WITH_PROGRESS dump script
  option is used.

  Enabled in v11.2.3 and later.
-----------------------------------------------------------------------------*/
#if ctVER3_GE(11,2,3)
#ifndef NO_ctFeatCTRDMPprogress
#define ctFeatCTRDMPprogress
#endif
#endif

#define DR_EVENT_NONE		0  /* no special event			    */
#define DR_EVENT_BEGIN_RESTORE	1  /* begin dump restore		    */
#define DR_EVENT_END_RESTORE	2  /* end dump restore			    */
#define DR_EVENT_BEGIN_FILE	3  /* begin restoring file		    */
#define DR_EVENT_PROGRESS_FILE	4  /* file restore progress		    */
#define DR_EVENT_END_FILE	5  /* end restoring file		    */
#define DR_EVENT_BEGIN_ROLLBACK	6  /* begin rollback of files to dump start */
#define DR_EVENT_END_ROLLBACK	7  /* end rollback of files to dump start   */
#define DR_EVENT_BEGIN_CLNIDX	8  /* begin cleaning of index marks	    */
#define DR_EVENT_END_CLNIDX	9  /* end cleaning of index marks	    */
#define DR_EVENT_BEGIN_UPDIFL	10 /* begin updating IFIL resources	    */
#define DR_EVENT_END_UPDIFL	11 /* end updating IFIL resources	    */

/*----------------------------------------------------------------------------
  ctFeatSUPHSTcofile enables support for opening a superfile host more than
  once per connection.

  Enabled by default for c-tree Server and c-tree client. Requires superfile
  and file share state support.
-----------------------------------------------------------------------------*/
#ifndef NO_ctFeatSUPHSTcofile
#if defined(ctSRVR) || defined(ctCLIENT) || defined(ctMTCLIENT)
#if defined(CTSUPER) && defined(ctFeatSHAREstate)
#define ctFeatSUPHSTcofile
#endif
#endif
#endif

#ifdef ctFeatSUPHSTcofile

#if defined(ctSRVR) || defined(ctCLIENT) || defined(ctMTCLIENT)
#ifndef ctFeatSHAREstate
#error Superfile host co-file support requires share state support for client and server models.
#endif
#endif

/* This bit indicates that a superfile host file number has been set. */
#define ctFeatSUPHSTset	0x8000
#endif

/*----------------------------------------------------------------------------
  ctFeatTRANISO enables transaction isolation level support.

  This feature is disabled by default.
-----------------------------------------------------------------------------*/
#ifndef NO_ctFeatTRANISO
/* #define ctFeatTRANISO */
#endif

/*----------------------------------------------------------------------------
  ctFeatTRANOVRoptimize optimizes loops in tranovr() over all files that are
  open by the current connection.

  When purging abort node list entries, instead of looping over all the open
  files, we loop over only the files that are in the list of files updated by
  the current transaction.

  When releasing table locks, we only loop until the table lock count is
  zero. (In the future, we could build a list of files containing table locks
  and loop over only those files. But for now this optimization improves the
  case where table locks are not used.)

  Enabled in v11.5.0 and later. Only implemented for server model.
  Requires ctFeatFUSRCLRoptimize because we use its ct_usrtf() list.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,0)
#ifndef NO_ctFeatTRANOVRoptimize
#ifdef ctFeatFUSRCLRoptimize
#define ctFeatTRANOVRoptimize
#endif
#endif
#endif

#ifdef ctFeatTRANOVRoptimize
#ifdef ctDBGfcqa
/* ctFeatTRANOVRoptimizeCHK checks the tranovr() optimization by looping over
over all files and checking if any should have had their abort node list entries
cleaned up but did not. */
#define ctFeatTRANOVRoptimizeCHK
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatCLRSHDLSToptimize optimizes the touch notification loop in clrshdlst()
  over all files that are open by the current connection.

  Instead of looping over all the open files, as we encounter files for which
  we need to report a touch notification, we add the files to the ct_usrtf()
  list, which has previously been emptied during commit processing.

  When we send the touch notifications, we loop over only the files that we
  have put into the list.

  Enabled in v11.5.0 and later. Only implemented for server model.
  Requires ctFeatFUSRCLRoptimize because we use its ct_usrtf() list.
  Requires ctBEHAV_IICTflexSTT because we use the trnlnko and trnplnko fields
  of the FUSR structure.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,0)
#ifndef NO_ctFeatCLRSHDLSToptimize
#if defined(ctFeatFUSRCLRoptimize) && defined(ctBEHAV_IICTflexSTT)
#define ctFeatCLRSHDLSToptimize
#endif
#endif
#endif

#ifdef ctFeatCLRSHDLSToptimize
#ifdef ctDBGfcqa
/* ctFeatCLRSHDLSToptimizeCHK checks the clrshdlst() optimization by looping over
over all files and checking if any have touch notification bits set after the
loop that clears the touch notification bits. */
#define ctFeatCLRSHDLSToptimizeCHK
#endif
#endif

/*--------------------------------------------------------------*/
/*
** ctFeatDeferAutotrn changes the approach to end automatic
** transactions by executing the transaction end logic after
** sending the answer back to the client application
** it controls the "deferred end of automatic transaction" code
** turned on by default for COBOL compilation (RTG)
*/
#if ctVER3_GE(11,5,0) || defined(ctPortRTG)
#if defined(ctSRVR)
#ifndef NO_ctFeatDeferAutotrn
#define ctFeatDeferAutotrn
#endif
#endif
#endif

/*
** deferred end of automatic transaction flags
*/

#define ctDFRAUTOTRN_NONE 0
#define ctDFRAUTOTRN_DEFER 1
#define ctDFRAUTOTRN_BEGIN 2
#define ctDFRAUTOTRN_END_OUT 3
#define ctDFRAUTOTRN_ABT 4
#define ctDFRAUTOTRN_END 5

/*----------------------------------------------------------------------------
  ctFeatQUEUEIDXLOAD enables support for queueing a load of a data file to a
  background thread. The load can be for a c-tree index, or it can be for a
  record update callback function. The key is added, or the record update
  callback function is called, for each record in the data file.

  Enabled in v11.5.0 and later for server. Requires deferred index support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,0)
#ifndef NO_ctFeatQUEUEIDXLOAD
#if defined(ctFeatDFRIDX) && defined(MULTITRD)
#define ctFeatQUEUEIDXLOAD
#endif
#endif
#endif

#ifdef ctFeatQUEUEIDXLOAD

#ifndef ctFeatDFRIDX
#error ctFeatQUEUEIDXLOAD requires deferred index support
#endif

#ifndef MULTITRD
#error ctFeatQUEUEIDXLOAD is only supported in the server model
#endif

#endif

/*----------------------------------------------------------------------------
  ctFeatDNODEQ_DELAY_ZERO changes the minimum delay for acting on a delete node
  queue entry from 1 second to zero seconds.

  Enabled in v11.5.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,0)
#ifndef NO_ctFeatDNODEQ_DELAY_ZERO
#define ctFeatDNODEQ_DELAY_ZERO
#endif
#endif

#ifdef ctFeatDNODEQ_DELAY_ZERO
/* Minimum delay (in seconds) for acting on a delete node queue entry. */
#define DNODEQ_MIN_DELAY	0
/* default delay for reuse list */
#define ctDEFAULT_REUSE_DELAY 0  /* 0 = immediate reuse */
/* Maximum number of retries in case of LNOD_ERR when the delete node thread
attempts to prune an empty node from an index tree. */
#define DNODEQ_MAX_LNOD_RETRY	20
#else
#define DNODEQ_MIN_DELAY	1
#define DNODEQ_MAX_LNOD_RETRY	2
#define ctDEFAULT_REUSE_DELAY   225  
#endif

/* Maximum number of retries in case of SWRT_ERR when the delete node thread
attempts to prune an empty node from an index tree. */
#define DNODEQ_MAX_SWRT_RETRY 4

/*----------------------------------------------------------------------------
  ctFeatREPLICAT_CHGBUF_COMPAT enables a compatibility check on the version of
  the replication change buffer used by a replication reader and by the source
  server. 

  Enabled in v11.5.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,0)
#ifndef NO_ctFeatREPLICAT_CHGBUF_COMPAT
#define ctFeatREPLICAT_CHGBUF_COMPAT
#endif
#endif

/* The version of the replication change buffer that we are using: */
#if ctVER3_GE(11,5,0)
/* Original replication change buffer plus 1-byte keyno and 1-byte avail: */
#define REPL_CHGBUF_VERSION	2
#else
/* Original replication change buffer structure: */
#define REPL_CHGBUF_VERSION	0
#endif

#if (REPL_CHGBUF_VERSION != 0) && !defined(ctFeatREPLICAT_CHGBUF_COMPAT)
#error Using a new version of the replication change buffer requires the replication change buffer compatibility check
#endif

/*----------------------------------------------------------------------------
  ctFeatREPLICAT_FLXDAT enables the passing of the schema ID for record images
  in replicated record add, delete, and update operations, and the new schema ID
  for alter schema operations.

  Enabled in v11.5.0 and later. Requires version 2 of replication change buffer
  structure.
----------------------------------------------------------------------------*/

#if ctVER3_GE(11,5,0)
#if (REPL_CHGBUF_VERSION >= 2)
#ifdef ctFeatFLEXREC
#ifndef NO_ctFeatREPLICAT_FLXDAT
#define ctFeatREPLICAT_FLXDAT
/* Indicate that we turned on ctFeatREPLICAT_FLXDAT in ctopt2.h: */
#define ctFeatREPLICAT_FLXDATctopt2
#endif
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatREPLICAT_TDELTA enables support for the source server to pass the
  relative time between the transaction commit and the current time on the
  source server system in the timestamp field of the replication change
  buffer structure for a transaction commit operation.

  Enabled in v11.5.0 and later. Requires version 2 of replication change buffer
  structure.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,0)
#if (REPL_CHGBUF_VERSION >= 2)
#ifndef NO_ctFeatREPLICAT_TDELTA
#define ctFeatREPLICAT_TDELTA
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatREADONLY_SRVR enables support for readonly server.
  a readonly server is a server that does not allow any kind of writes from
  clients. internal threads and replication agent still have r/w capability.
  Enabled in v11.6.0 and later. Requires c-tree Server.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifdef ctSRVR
#ifndef NO_ctFeatREADONLY_SRVR
#define ctFeatREADONLY_SRVR
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatLOCKSTATS enables tracking of c-tree lock statistics.

  Enabled by default.
----------------------------------------------------------------------------*/
#ifndef NO_ctFeatLOCKSTATS
#define ctFeatLOCKSTATS
#endif

/*----------------------------------------------------------------------------
  ctFeatSCNLOGkeepalive enables a replication reader to instruct the source
  server's ctReplGetNextChange() function to return an internal response to
  the client library within the specified time period in order to avoid the
  client timing out on a socket read operation.

  Enabled in v11.5.1 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,1)
#ifndef NO_ctFeatSCNLOGkeepalive
#define ctFeatSCNLOGkeepalive
#endif
#endif

#if defined(ctFeatSCNLOGkeepalive) && defined(ctSRVR)
#define ctFeatSCNLOGkeepaliveSRVR
#endif

/* Maximum time between keepalive messages in seconds. We limit this value to
255 because we store it in one byte of the filno field in the call to
ctReplGetNextChange(). */
#define MAX_SCNLOGkeepaliveValue	255 /* 0xff */

/* Set the keepalive time in ctReplGetNextChange()'s filno value. */
#define ctSetSCNLOGkeepaliveValue(filno,value) \
((filno) = (((filno) & 0xff00) | (UTEXT) (((value) > MAX_SCNLOGkeepaliveValue) ? MAX_SCNLOGkeepaliveValue : (value))))

/* Get the keepalive time from ctReplGetNextChange()'s filno value. */
#define ctGetSCNLOGkeepaliveValue(filno) (filno & 0x000000ff)

/*----------------------------------------------------------------------------
  ctFeatCHKFILXST adds a check for a file's existence to chkopnx(). This
  check can speed up opens of files that do not exist.

  Enabled in v11.5.1 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,1)
#ifndef NO_ctFeatCHKFILXST
#define ctFeatCHKFILXST
#endif
#endif

/* chkopnx() return codes: */
#define CO_RET_NOPN	-1	/* file is not open */
#define CO_RET_MNOT	-2	/* file already opened without mirror */
#define CO_RET_UQID	-3	/* file id uniqueness error */
#define CO_RET_UQIDT	-4	/* file id uniqueness error on TRNLOG file */
#define CO_RET_DPND	-5	/* file pending TRANDEP delete by other connection */
#define CO_RET_EXCT	-6	/* file open by different name and exact filename match is required */
#define CO_RET_VCLS	-7	/* insufficient file handles and could not find file to close for virtual processing */
#define CO_RET_UALC	-8	/* memory allocation error */
#define CO_RET_NXST	-9	/* file does not exist */
#define CO_RET_PNDO	-10	/* file open is pending */
#define CO_RET_UERR	-11	/* error checking if file is open; see uerr_cod for error code */

/*----------------------------------------------------------------------------
  ctFeatFILESYScompress adds support for enabling file system level compression
  on the specified c-tree data and index files. Use the FILESYS_COMPRESS_FILE
  configuration option to specify the files that are to be compressed.
  
  Enabled in v11.6.0 and later on Windows when compiling with the Visual
  Studio 2005 and later compiler.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifndef NO_ctFeatFILESYScompress
#if defined(ctPortWIN32) && _MSC_VER >= 1400
#define ctFeatFILESYScompress
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatFILESYScompressUNCSEG adds support for enabling file system level
  compression when creating an index file or an index member that has a
  Unicode key segment.
  
  Enabled for c-tree Server in v11.6.0 and later when file system level
  compression support is enabled.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifndef NO_ctFeatFILESYScompressUNCSEG
#ifdef ctFeatFILESYScompress
#ifdef ctSRVR
#define ctFeatFILESYScompressUNCSEG
#endif
#endif
#endif
#endif

/* Default value for the FILESYS_COMPRESS_UNCSEG option: */
#define FILESYS_COMPRESS_UNCSEG_DEFAULT	"NO"

/*----------------------------------------------------------------------------
  ctFeatUNCSEG_KEYCOMPRESS adds support for a c-tree Server configuration
  option that enables c-tree key compression on an index that has a Unicode key
  segment.

  To use this feature, add the option UNCSEG_KEYCOMPRESS YES to ctsrvr.cfg.

  Enabled in v11.6.0 and later for c-tree Server.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifdef ctSRVR
#ifndef NO_ctFeatUNCSEG_KEYCOMPRESS
#define ctFeatUNCSEG_KEYCOMPRESS
#endif
#endif
#endif

/* Default value for the UNCSEG_KEYCOMPRESS option: */
#define UNCSEG_KEYCOMPRESS_DEFAULT	"NO"

/*----------------------------------------------------------------------------
  ctFeatSHMEM_MAX_SPINNERS enables a c-tree Server configuration option to set
  the maximum number of shared memory connections that are allowed to spin at
  one time.

  Enabled in v11.6.0 and later for c-tree Server when shared memory spin support
  is enabled at compile time.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifdef ctSRVR
#ifdef ctFeatSHMEMspin
#ifndef NO_ctFeatSHMEM_MAX_SPINNERS
#define ctFeatSHMEM_MAX_SPINNERS
#endif
#endif
#endif
#endif

/* Default value for the SHMEM_MAX_SPINNERS option: */
#define SHMEM_MAX_SPINNERS_DEFAULT	"4"

/*----------------------------------------------------------------------------
  ctFeatLOCK_MONITOR enables support for c-tree Server's LOCK_MONITOR feature.

  Enabled by default for c-tree Server.
----------------------------------------------------------------------------*/
#ifdef ctSRVR
#ifndef NO_ctFeatLOCK_MONITOR
#define ctFeatLOCK_MONITOR
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatLOCKSTATSopt enables optimizations to the updates of c-tree Server's
  lock statistics in order to improve scalability.

  Enabled for c-tree Server when lock stats and 64-bit atomic operations are
  supported.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0) 
#if defined(ctSRVR) && defined(ctFeatLOCKSTATS) && defined(ctFeatATOMICop64)
#ifndef NO_ctFeatLOCKSTATSopt
#define ctFeatLOCKSTATSopt
/* Turn off LOCK_MONITOR support. */
#undef ctFeatLOCK_MONITOR
#endif
#endif
#endif

#if defined(ctBEHAV_LLSEMA) && (defined(ctFeatLOCK_MONITOR) || !defined(ctFeatLOCKSTATSopt))

/* ctplmsema is used: definitions for mutex request and release */
#ifdef ctDBGSEMCNT
#define ctPLMrqs(ps,own,loc)	ctmutrqs(ps,own,loc)
#else
#define ctPLMrqs(ps,own)	ctmutrqs(ps,own)
#endif
#define ctPLMclr(ps,own)	ctmutclr(ps,own)

#else

/* ctplmsema is not used: no-op definitions for mutex request and release */
#ifdef ctDBGSEMCNT
#define ctPLMrqs(ps,own,loc)
#else
#define ctPLMrqs(ps,own)
#endif
#define ctPLMclr(ps,own)

#endif

#ifdef ctFeatLOCKSTATSopt

#define ctLOKINC32(v) ctInterlockedIncrement32(v)
#define ctLOKDEC32(v) ctInterlockedDecrement32(v)
#define ctLOKINC64(v) ctInterlockedIncrement64(v)
#define ctLOKDEC64(v) ctInterlockedDecrement64(v)

#ifdef ct8P
#define ctLOKINCNL(v) ctInterlockedIncrement64(v)
#define ctLOKDECNL(v) ctInterlockedDecrement64(v)
#else
#define ctLOKINCNL(v) ctInterlockedIncrement32(v)
#define ctLOKDECNL(v) ctInterlockedDecrement32(v)
#endif

#else

#define ctLOKINC32(v) ++(v)
#define ctLOKDEC32(v) --(v)
#define ctLOKINC64(v) ++(v)
#define ctLOKDEC64(v) --(v)
#define ctLOKINCNL(v) ++(v)
#define ctLOKDECNL(v) --(v)

#endif

/*----------------------------------------------------------------------------
  ctFeatCTTIMEopt reduces calls to the time() system function by creating a
  thread that periodically stores the current system time in a global variable.
  When the global variable's value is non-zero, cttime() uses that value
  instead of calling time().

  Enabled for c-tree Server in v11.6.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0) 
#ifdef ctSRVR
#ifndef NO_ctFeatCTTIMEopt
#define ctFeatCTTIMEopt
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatDMPSEMArwlock changes the dmpsema synchronization object from a
  mutex to a reader/writer lock.

  Enabled in v11.6.0 and later when dynamic dump support is enabled.
  Requires reader/writer lock support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#if defined(ctFeatDYNAMIC_DUMP) && defined(ctFeatRWLOCK)
#ifndef NO_ctFeatDMPSEMArwlock
#define ctFeatDMPSEMArwlock
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatPWDEXP enables support for a user account password expiration period.

  Enabled in v11.6.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifndef NO_ctFeatPWDEXP
#define ctFeatPWDEXP
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatPWDREQ enables support for setting password requirements.

  Enabled in v11.6.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifndef NO_ctFeatPWDREQ
#define ctFeatPWDREQ
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatSUBSTcnv enables support for converting a path that uses a substituted
  drive letter on Windows to the actual path.

  Enabled in v11.6.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifdef ctPortWIN32
#ifndef NO_ctFeatSUBSTcnv
#ifndef ctPortWINIOT
#define ctFeatSUBSTcnv
#endif
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatRECOVERY_CHECK_DUPFID enables automatic recovery to detect that two
  files are using the same c-tree file ID and to take corrective action.

  Enabled in v11.6.0 and later when transaction support is enabled at compile
  time.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifndef NO_ctFeatRECOVERY_CHECK_DUPFID
#ifdef TRANPROC
#define ctFeatRECOVERY_CHECK_DUPFID
#endif
#endif
#endif

#ifdef ctFeatRECOVERY_CHECK_DUPFID
#ifndef NO_ctFeatRECOVERY_CHECK_DUPFID_TR
/*
  Bug fix for automatic recovery error involving TRANDEP rename: improve ability
  of recovery to detect that a file is part of a TRANDEP rename operation.
*/
#define ctFeatRECOVERY_CHECK_DUPFID_TR
#endif
#endif

/* Default value for the RECOVERY_CHECK_DUPFID configuration option. */
#define RECOVERY_CHECK_DUPFID_DEFAULT "YES"

/* chkfid() return codes: */
#define CHKFID_NOMATCH	-1	/* no file is open with matching ID	*/
#define CHKFID_CHKERR	-2	/* error checking file name		*/
#define CHKFID_DUPID	-3	/* duplicate file id exists		*/

/*----------------------------------------------------------------------------
  ctFeatRECOV_PATHEQUIV improves automatic recovery's file name comparison
  function so that it detects path specifications that are equivalent.

  Enabled in v11.6.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifndef NO_ctFeatRECOV_PATHEQUIV
#define ctFeatRECOV_PATHEQUIV
#endif
#endif

#ifndef ctFeatRECOV_PATHEQUIV
/* Use our simple filename comparison function during automatic recovery. */
#define ctrt_rcvfilcmp ctrt_filcmp
#endif

/*----------------------------------------------------------------------------
  ctFeatPUTHDR_UNIQID adds the ctUNIQIDhdr mode to the PUTHDR() function, which
  sets the file ID of a file to a unique value by either setting the timeid
  field to the current time if it has not been used yet in a call to PUTHDR()
  with mode of ctUNIQIDhdr, or setting the fileid field to the next available
  value as recorded in the transaction log header.

  Enabled for c-tree Server in v11.5.1 and later. Requires atomic operation
  support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,5,1)
#if defined(ctSRVR) && defined(ctFeatATOMICop)
#ifndef NO_ctFeatPUTHDR_UNIQID
#define ctFeatPUTHDR_UNIQID
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatCHECK_SYSTEM_FILEID enables the storing of a system-level file ID in
  the header of a c-tree file. When opening the file, we compare the header
  value to the current system-level file ID. If they differ, we reassign
  c-tree's file ID.

  Enabled in v11.6.0 and later when transaction support is enabled at compile time.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifndef NO_ctFeatCHECK_SYSTEM_FILEID
#ifdef TRANPROC
#define ctFeatCHECK_SYSTEM_FILEID
#endif
#endif
#endif

/* Default value for the CHECK_SYSTEM_FILEID configuration option. */
#define CHECK_SYSTEM_FILEID_DEFAULT "YES"

/*----------------------------------------------------------------------------
  ctFeatREPLICAT_PTADMIN enables support for replicating PTADMIN() operations.

  Enabled in v11.6.0 and later when replication support is enabled.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifdef ctFeatREPLICAT
#ifndef NO_ctFeatREPLICAT_PTADMIN
#define ctFeatREPLICAT_PTADMIN
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatENCSTORE_V2 enables enhancements to c-tree's encrypted store.

  Enabled in v11.6.0 and later on Windows.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0) || defined(ctPortDENTRIX)
#ifdef ctPortWIN32
#ifndef NO_ctFeatENCSTORE_V2
#define ctFeatENCSTORE_V2
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatKSEGDEFxtd enables enhancements to the extended key segment definition
  feature.

  Enabled in v11.7.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,0)
#ifndef NO_ctFeatKSEGDEFxtd
#define ctFeatKSEGDEFxtd
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatJSONfldtyp enables support for the JSON field type.

  Enabled in v11.7.0 and later. Requires extended field type support, extended
  key segment definition enhancements, and json-c library.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,0)
#if defined(ctFeatXTDFLDTYP) && defined(ctFeatKSEGDEFxtd) && defined(ctJSONCLIB)
#ifndef NO_ctFeatJSONfldtyp
#define ctFeatJSONfldtyp
#endif
#endif
#endif

#ifdef ctFeatJSONfldtyp
#if !defined(ctFeatXTDFLDTYP) || !defined(ctFeatKSEGDEFxtd) || !defined(ctJSONCLIB)
#error json support requires extended field type support, extended key segment definition enhancements, and json-c library.
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatXTDOPNMOD enables support for extended file open modes. Previously,
  this feature was enabled by ctFeatSHAREstate, which limited its use to
  client/server mode. Now this feature is enabled for all operational models,
  although some extended file open modes (such as ctXOPN_COFILE_FILELOCK and
  ctXOPN_REDSHR) are only supported in client/server mode.

----------------------------------------------------------------------------*/
#ifndef NO_ctFeatXTDOPNMOD
#define ctFeatXTDOPNMOD
#endif

/*----------------------------------------------------------------------------
  ctFeatVARLENnodefmt enables support for storing variable-length key data in
  index nodes.

  Enabled in v11.8.0 and later. Requires 6-byte transaction support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || defined(ctPortABACUS)
#ifndef NO_ctFeatVARLENnodefmt
#ifdef ctFeat6BT
#define ctFeatVARLENnodefmt
#endif
#endif
#endif

#define KEYOFFAVLVAL	"<<" /* fill value for next entry in key offset list */
#define KEYOFFAVLLEN	sizeof(UCOUNT) /* space for new offset at start of key offset list */
#define KEYOFFLEN	sizeof(UCOUNT) /* size of key offset in node */

#define NODESTAT_NOAVL	0x01 /* available before key offset region has been used */
#define NODESTAT_SHIFT	0x02 /* non-leaf node: shifted offsets right temporarily */

#ifdef ctFeatVARLENnodefmt
#define hghlen(buffer) (buffer->hghlen)
#endif

#if defined(ctDBGfcqa) && defined(CTBOUND)
/* For a debug compile in standalone mode, enable expval() counters. */
#define ctDBGexpvalCOUNTERS
#endif

/*----------------------------------------------------------------------------
  ctFeatTRNMRKOPT adds support for storing transaction marks with the keys
  in a leaf node when the index uses a key offset list.
    
  Enabled in v11.8.0 and later. Requires key offset list support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || defined(ctPortABACUS)
#ifndef NO_ctFeatTRNMRKOPT
#ifdef ctFeatVARLENnodefmt
#define ctFeatTRNMRKOPT
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatKEYCOMPRESSsRLE adds support for a key compression mode that uses
  sRLE compression.
    
  Enabled in v11.8.0 and later. Requires compression support and key offset
  list support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || defined(ctPortABACUS)
#ifndef NO_ctFeatKEYCOMPRESSsRLE
#if defined(ctCMPREC) && defined(ctFeatVARLENnodefmt)
#define ctFeatKEYCOMPRESSsRLE
#ifdef KC_ZLIB
#define ctCompressContext z_stream
#else
#define ctCompressContext sRLE_context
#endif
#endif
#endif
#endif

#define hghpnt(buffer) (buffer->ct_kyval + buffer->maxb)

/*----------------------------------------------------------------------------
  ctFeatCMPOFFSET enables support for compressing offsets in index nodes.

  Not yet enabled. Requires key offset list support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifndef NO_ctFeatCMPOFFSET
#ifdef ctFeatVARLENnodefmt
/* #define ctFeatCMPOFFSET */
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatCMPTRNMRK enables support for compressing transaction marks in
  index nodes.

  Not yet enabled. Still need to handle the possibility that deleting a key
  might find that insufficient space is available in the node to hold the
  transaction mark.

  Requires key offset list support and 6-byte transaction support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifndef NO_ctFeatCMPTRNMRK
#ifdef ctFeatVARLENnodefmt
#ifdef ctFeat6BT
/* #define ctFeatCMPTRNMRK */
#endif
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatOPTIMIZE_FILE_OPEN enables scalability improvements for file open calls.

  Enabled for c-tree Server in v11.7.1 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,1) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifdef ctSRVR
#ifndef NO_ctFeatOPTIMIZE_FILE_OPEN
#define ctFeatOPTIMIZE_FILE_OPEN
#endif
#endif
#endif

/* Default value for the OPTIMIZE_FILE_OPEN configuration option. */
#define OPTIMIZE_FILE_OPEN_DEFAULT	"YES"

#ifdef ctFeatOPTIMIZE_FILE_OPEN
#if defined(ctHUGEFILE) && !defined(NO_ctHDR1)
/* When optimized file open support is enabled, we also turn on unified header
I/O for HUGE files. */
#define ctHDR1
#endif
#endif

/* pforetry() fnc parameter values: */
#define PFO_OPEN	1 /* called from file open */
#define	PFO_CREATE	2 /* called from file create */
#define PFO_REBUILD	3 /* called from rebuild */

/* Maximum number of times to retry checking if file is open when the file
is in a pending open state. Zero= no limit */
#define DEFAULT_PENDING_FILE_OPEN_RETRIES "0"

/* opcode values for adding/removing entries to pending file open/close hash table */
#define ctPENDING_FILE_OPEN	1 /* pending file open */
#define ctPENDING_FILE_CLOSE	2 /* pending file close */
#define ctPENDING_FILE_DELETE	4 /* pending file delete */

/*----------------------------------------------------------------------------
  ctFeatFILRESopt enables improvements to resource reads during physical file
  open calls.

  Enabled for c-tree Server in v11.7.1 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,1) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifdef ctSRVR
#ifndef NO_ctFeatFILRESopt
#define ctFeatFILRESopt
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatGETRHDRopt optimizes the reading of a resource header by reading both
  the resource header and the resource ID in one call.

  Enabled for c-tree Server in v11.7.1 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,1) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifdef ctSRVR
#ifndef NO_ctFeatGETRHDRopt
#define ctFeatGETRHDRopt
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatBATCH_RANGE_REVERSE enables support for a batch range call that returns
  the results in reverse key order.

  Enabled in v11.6.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,0)
#ifndef NO_ctFeatBATCH_RANGE_REVERSE
#define ctFeatBATCH_RANGE_REVERSE
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatUPDATE_RECORD_OFFSET_FOR_KEY enables support for updating the record
  offset associated with a key in one function call.

  Enabled in v11.8.0 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || defined(ctPortCOMMVAULT)
#ifndef NO_ctFeatUPDATE_RECORD_OFFSET_FOR_KEY
#define ctFeatUPDATE_RECORD_OFFSET_FOR_KEY
#endif
#endif


/*----------------------------------------------------------------------------
  ctFeatBATCHEXT enables support for BAT_EXTENSIONS and PKEYREQ2

  Enabled in 11.6.1
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1)
#ifndef NO_ctFeatBATCHEXT
#define ctFeatBATCHEXT
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatBATCHCOLFLTR enables support for columns filtering.
  It depends on ctFeatBATCHEXT and ctFeatFLEXREC

  Enabled in 11.6.1
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1)
#ifdef ctFeatBATCHEXT
#ifdef ctFeatFLEXREC
#ifndef NO_ctFeatBATCHCOLFLTR
#define ctFeatBATCHCOLFLTR
#endif
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatPKEYREQ2_V enables support marshalling PKEYREQ2 with version number
  this changes also the way of requesting BAT_PHYS allowing (if supported)
  extended capabilities liker column filtering
  It depends on ctFeatBATCHEXT

  Enabled in v11.8.0 forward.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || defined(ctPortABACUS)
#ifdef ctFeatBATCHEXT
#ifndef NO_ctFeatPKEYREQ2_V
#define ctFeatPKEYREQ2_V
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatLEAF_NODE_READ_LOCK enables support for acquiring a read lock instead
  of a write lock on an index leaf node during a key retrieval call.

  Enabled in v11.7.1 forward for c-tree Server. Requires IDXreader (checked later
  in this header file).
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,1) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifndef NO_ctFeatLEAF_NODE_READ_LOCK
#ifdef ctSRVR
#ifndef ctBEHAV_SET_ACTLEN_EXCLUSIVE
#error Requires ctBEHAV_SET_ACTLEN_EXCLUSIVE
#endif
#define ctFeatLEAF_NODE_READ_LOCK
#define ctFeatLEAF_NODE_READ_LOCK_ctopt2
#endif
#endif
#endif

/* Default value for the LEAF_NODE_READ_LOCK configuration option. */
#define LEAF_NODE_READ_LOCK_DEFAULT	"YES"

/*----------------------------------------------------------------------------
  ctFeatCHKREMNOD_READ_LOCK allows chkremnod(), which is the function that
  checks if the specified index buffer contains the current index node for
  the calling connection on the specified file, to acquire a read lock instead
  of a write lock on the buffer when possible.

  Enabled in v11.7.1 forward. Requires leaf node read lock support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,1) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#if defined(ctFeatREMBUFADR) && defined(ctFeatLEAF_NODE_READ_LOCK)
#ifndef NO_ctFeatCHKREMNOD_READ_LOCK
#define ctFeatCHKREMNOD_READ_LOCK
#define ctFeatCHKREMNOD_READ_LOCK_ctopt2
#endif
#endif
#endif

/* chkremnod() option parameter bits: */
#define CRNOPT_NEXTOP	0x00000001	/* reading next key */
#define CRNOPT_READLOCK	0x00000002	/* ok to acquire read lock on index buffer */

/*----------------------------------------------------------------------------
  ctFeatPREIMAGE_SWAP enables swapping of preimage space entries to disk when
  the amount of preimage space used by a transaction exceeds the specified
  threshold.

  Enabled in v11.7.1 for 64-bit c-tree Server. Requires variable-length
  data file support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,1)
#if (!defined(TRANPROC) ||  defined(UNIFRMAT))
#define NO_ctFeatPREIMAGE_SWAP
#endif
#ifndef NO_ctFeatPREIMAGE_SWAP
#if defined(ct8P) && defined(ctSRVR) && defined(VARLDATA) && defined(ctBEHAV_CMTLOK_optimize)
#define ctFeatPREIMAGE_SWAP
#endif
#endif
#endif

#define GET_PREIMAGE_SWAP_SYSTEM_FCB() ctkey(CTU_PreimageSwapSysFilno(sOWNR))
#define GET_PREIMAGE_SWAP_SYSTEM_FILNO() CTU_PreimageSwapSysFilno(sOWNR)

/* Default value for MAX_PREIMAGE_DATA configuration option */
#define MAX_PREIMAGE_DATA_DEFAULT "1 GB"

/* Default value for MAX_PREIMAGE_SWAP configuration option */
#define MAX_PREIMAGE_SWAP_DEFAULT "0"

/*----------------------------------------------------------------------------
  ctFeatOPEN_FILES_ALERT enables diagnostic logging when the number of open
  logical files exceeds a configurable limit.

  Enabled in v11.7.1 forward for c-tree Server.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,1) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifdef ctSRVR
#ifndef NO_ctFeatOPEN_FILES_ALERT
#define ctFeatOPEN_FILES_ALERT
#endif
#endif
#endif

/* Default value for OPEN_FILES_ALERT_THRESHOLD configuration option */
#define OPEN_FILES_ALERT_THRESHOLD_DEFAULT "0"

#ifdef ctFeatOPEN_FILES_ALERT

/* Check if the open files alert threshold has been exceeded. */
#define ctCheckFileControlBlockThreshold \
	if (ctOpenFilesAlertThreshold && numfcb >= ctOpenFilesAlertThreshold) \
		ctOpenFilesAlertAction(numfcb);

/* Check if the number of open files has dropped below the alert threshold. */
#define ctCheckFileControlBlockThreshold2 \
	if (ctOpenFilesAlertHigh && numfcb < ctOpenFilesAlertThreshold) \
		ctOpenFilesAlertHigh = 0;

#else  /* ~ctFeatOPEN_FILES_ALERT */

#define ctCheckFileControlBlockThreshold /* no action */
#define ctCheckFileControlBlockThreshold2 /* no action */

#endif /* ~ctFeatOPEN_FILES_ALERT */

/* Increase the count of file control blocks in use by the specified amount and take related actions. */
#define ctINCREASE_FILE_CONTROL_BLOCK_COUNT(n) { \
	NINT	numfcb; \
	if ((numfcb = (cttotblk += (n))) > cttotblkx) \
		cttotblkx = cttotblk; \
	ctCheckFileControlBlockThreshold \
}

/* Reduce the count of file control blocks in use by the specified amount and take related actions. */
#define ctREDUCE_FILE_CONTROL_BLOCK_COUNT(n) { \
	NINT	numfcb; \
	if ((numfcb = (cttotblk -= (n))) < 0) \
		cttotblk = 0; \
	ctCheckFileControlBlockThreshold2 \
}

/*----------------------------------------------------------------------------
  ctFeatCONNECTION_LEVEL_IO_STATS enables collection of I/O statistics on a
  per-connection basis.

  Enabled in v11.7.1 forward for c-tree Server.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,1) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifdef ctSRVR
#ifndef NO_ctFeatCONNECTION_LEVEL_IO_STATS
#define ctFeatCONNECTION_LEVEL_IO_STATS
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatUSERINFO_EXTENDED enables support for the USERINFOX() API function.

  Enabled in v11.7.1 forward. In the server model, this feature requires the
  connection-level I/O statistics feature to be enabled.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,7,1) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifndef NO_ctFeatUSERINFO_EXTENDED
#if !defined(ctSRVR) || defined(ctFeatCONNECTION_LEVEL_IO_STATS)
#define ctFeatUSERINFO_EXTENDED
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatPersistCFG enables support for persisting selected configuration keyword
  settings modified at runtime by SECURITY API calls in FAIRCOM.FCS overwriting 
  at server startup any setting in ctsrvr.cfg

  enabled in v11.9.5 and later
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatPersistCFG
#define ctFeatPersistCFG
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatAWS enables support for AWS services.

  Enabled in v11.6.1 and later for c-tree Server and internal utility gen.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1)
#if defined(ctSRVR) || defined(ctPortFAIRCOM_INTERNAL_GEN)
#ifndef NO_ctFeatAWS
#define ctFeatAWS
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatAWS_KEY_STORE enables support for AWS key store services.

  Enabled in v11.6.1 and later for c-tree Server and internal utility gen.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1)
#ifdef ctFeatAWS
#ifndef NO_ctFeatAWS_KEY_STORE
#ifndef ctFeatAEKato
#define ctFeatAWS_KEY_STORE
#endif
#endif
#endif
#endif

#ifdef ctFeatAWS_KEY_STORE

#ifndef ctFeatAWS
#error The AWS key store feature requires support for AWS services.
#endif

#ifdef ctFeatAEKato
#error The AWS key store feature cannot be used with automatic advanced encryption key feature.
#endif

#endif

/*----------------------------------------------------------------------------
  ctFeatMASTERKEYLIB enables support for external library to provide 
  encryption master key from a custom library.
  Enabled in v11.8.0 and later for c-tree Server and internal utility gen.
  Requires SSL to encrypt and decrypt the password securely
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#if (defined(ctSRVR) || defined(ctPortFAIRCOM_INTERNAL_GEN)) && defined(ctFeatSSL)
#ifndef NO_ctFeatMASTERKEYLIB
#ifndef ctFeatMASTERKEYLIB
#define ctFeatMASTERKEYLIB
#endif
#endif
#endif
#endif


/*----------------------------------------------------------------------------
  ctFeatCHMPW_RECOVERY enables support for recoverability of an interrupted
  change to the master encryption key.

  Enabled in v11.6.1 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1)
#ifndef NO_ctFeatCHMPW_RECOVERY
#define ctFeatCHMPW_RECOVERY
#endif
#endif

/* The name of the log file used to recover from an interrupted change to the master encryption key. */
#define CHKMPW_RECOVERY_LOGFILE "CMPRECOV.FCS"
/* The name of the verification file used to recover from an interrupted change to the master encryption key. */
#define CHKMPW_RECOVERY_VFYFILE "CMPRECOVA.FCS"

/*----------------------------------------------------------------------------
  ctFeatSNAPSHOT_FILEOPS enables c-tree Server snapshot counters for the
  following operations on files:

  Logical file open, logical file close, physical file open, physical file
  close, file create, file rename, and file delete.

  Enabled in v11.6.1 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1)
#ifdef ctSRVR
#ifndef NO_ctFeatSNAPSHOT_FILEOPS
#define ctFeatSNAPSHOT_FILEOPS
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatFILENAMEhashFUNCopt changes the filename hash function so that it more
  evenly distributes filenames over the filename hash bins. Instead of summing
  the individual bytes of the filename, the hash function sums four bytes at a
  time.
----------------------------------------------------------------------------*/
#ifndef NO_ctFeatFILENAMEhashFUNCopt
#define ctFeatFILENAMEhashFUNCopt
#endif


/*----------------------------------------------------------------------------
  ctFeatLATTE_CONFIG changes latte configuration handling so SUBSYSTEM LATTE
  values may be changed at runtime rather than only at server initialization.
----------------------------------------------------------------------------*/
#ifndef NO_ctFeatLATTE_CONFIG
#ifdef ctSQL_LATTE
#ifdef ctFeatCFG_SCALE_N8
#define ctFeatLATTE_CONFIG
#endif
#endif
#endif

#ifdef ctFeatLATTE_CONFIG
#define HAS_LATTE_RUNTIME_CONFIG YES
#else
#define HAS_LATTE_RUNTIME_CONFIG NO
#endif

/*----------------------------------------------------------------------------
  ctFeatNEWctrcvlog changes the ctrcvlog function by 
  - renaming the original as i_ctrcvlog 
  - creating new logging functions that eventually call i_ctrcvlog 
  - rewriting ctrcvlog to use the new logging functions
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatNEWctrcvlog
/* #define ctFeatNEWctrcvlog  */
#endif
#endif

/* Function name/location macro */

/* Unknown TASKID */
#ifdef MULTITRD
#define TID_UNKNOWN OWNER /* sOWNR not available */
#else
#define TID_UNKNOWN 0
#endif

#define STRINGIFY(x) #x
/* Macro to generate "__FILE__:__LINE__" as string */
#define C_LOC_STR(file,line) file ":" STRINGIFY(line) 
#ifdef MULTITRD
#define CTTASKID(x) (x)
#else
#define CTTASKID(x) 0
#endif

#ifdef ctFeatNEWctrcvlog
/* Basic Logging Macro */
#define LOG_CTREE_MSG(id,whofor,subsystem,severity,tid,msg,olderr,err,errinfo,location,action) ctLogMsgAdvlog(id,whofor,subsystem,severity,CTTASKID(tid),msg,olderr,NULL,err,errinfo,ERR_UNUSED,ERR_UNUSED,location,action,C_LOC_STR(__FILE__,__LINE__))
/* Multipart logging handle declaration */
#define LOG_CTREE_MSG_HANDLE_INIT(hdl) void * hdl=NULL;
/* Multipart logging line */
#define LOG_CTREE_MSG_FRAGMENT(hdl,id,whofor,subsystem,severity,tid,msg,olderr,err,errinfo,location,action) do{ \
			if(hdl){ \
				ctLogMsgSetAdditionalMessage(hdl,msg,err,errinfo); \
			} else {  \
			  hdl=ctLogMsgGetHandle(id,whofor,subsystem,CTTASKID(tid),msg); \
			  ctLogMsgSetSeverity(hdl,severity); \
		          ctLogMsgSetFullError(hdl,err,errinfo); \
			  ctLogMsgSetLocation(hdl,location); \
			  ctLogMsgSetAction(hdl,action); \
			  ctLogMsgSetCodeLine(hdl,C_LOC_STR(__FILE__,__LINE__)); \
			}\
	  	    }while(0)
/* Multipart logging completion */
#define LOG_CTREE_MSG_FINAL(hdl) ctLogMsgDispatch(&hdl)

/* logging with modified message and additional error parameters */
#define LOG_CTREE_MSG_XTD(id,whofor,subsystem,severity,tid,oldmsg,olderr,newmsg,newerr,errinfo,usererr,systemerr,location,action) ctLogMsgAdvlog(id,whofor,subsystem,severity,CTTASKID(tid),oldmsg,olderr,newmsg,newerr,errinfo,usererr,systemerr,location,action,C_LOC_STR(__FILE__,__LINE__))
#else /* ctFeatNEWctrcvlog */
/* Logging Macro - ctrcvlog */
#define LOG_CTREE_MSG(id,whofor,subsystem,severity,tid,msg,olderr,err,errinfo,location,action) ctrcvlog(msg,olderr)

#define LOG_CTREE_MSG_HANDLE_INIT(hdl) 
/*Logging Macro - ctrcvlog */
#define LOG_CTREE_MSG_FRAGMENT(hdl,id,whofor,subsystem,severity,tid,msg,olderr,err,errinfo,location,action) ctrcvlog(msg,olderr)
#define LOG_CTREE_MSG_FINAL(hdl)
/*Logging Macro - ctrcvlog */
#define LOG_CTREE_MSG_XTD(id,whofor,subsystem,severity,tid,oldmsg,olderr,newmsg,newerr,errinfo,usererr,systemerr,location,action) ctrcvlog(oldmsg,olderr)
#endif /* ctFeatNEWctrcvlog */

/*----------------------------------------------------------------------------
  ctFeatADVLOG advanced log capabilities beyond ctrcvlog
  extend the new logging functions to support advanced capabilities.
  it requires ctFeatNEWctrcvlog
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatADVLOG
#ifdef ctFeatNEWctrcvlog
/*
#define ctFeatADVLOG
#define ctFeatADVLOG_msec
*/
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatREPLICAT_SYNC enables support for synchronous replication.

  Enabled in v11.9.5 and later when replication support is enabled.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatREPLICAT_SYNC
#ifdef ctFeatREPLICAT
#ifdef ctFeatATOMICop
/* synchronous replication support is enabled */
#define ctFeatREPLICAT_SYNC
#endif
#endif
#endif
#endif

#if defined(ctFeatREPLICAT_SYNC) && defined(ctSRVR)
/* synchronous replication support is enabled in server model */
#define ctFeatREPLICAT_SYNC_SRVR
#endif

/*----------------------------------------------------------------------------
  ctFeatLOCALHOST_BIND changes the behavior of the LOCAL_CONNECTION_ONLY keyword
  so that it binds the socket to 127.0.0.1 (::1 in IPV6) accepting connection
  only on the loopback device. Broadcast is turned off.
  This setting cannot be changed at runtime anymore.

----------------------------------------------------------------------------*/
#ifndef NO_ctFeatLOCALHOST_BIND
#ifdef ctSRVR
#ifdef ctFeatTRACK_CLIENT_ADDR
#define ctFeatLOCALHOST_BIND
#endif
#endif
#endif

/*--------------------------------------------------------------*/
/* ctFeatPLUGIN turns on support for the embedded plugins.      */
/*                                                              */
/* Default: ctFeatPLUGIN is ON for v11.7 and future             */
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,7,0)
#ifndef NO_ctFeatPLUGIN
#if defined(ctSRVR)
#define ctFeatPLUGIN
#define ctMAX_PLUGIN 32 /* Max number of plugins */
#endif
#endif
#endif

/*------------------------------------------------------------------------*/
/* ctFeatAUTOSYSTIME allows support for auto generated time/datetime/date */
/*                                                                        */
/* Default: ctFeatAUTOSYSTIME is ON for v11.8 and future                  */
/*------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifndef NO_ctFeatAUTOSYSTIME
#define ctFeatAUTOSYSTIME
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatRCVLSTopt augments the dynamic dump recovery file list with hash tables
  so that checking if a filename is on the recovery list is quick even when many
  files are on the recovery list.

  Enabled in v11.6.1 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1) /* Activated:Jeff K:v11.6.1:190725; Activated:Ray:v11.8.0 forward:190912 */
#ifndef NO_ctFeatRCVLSTopt
#ifdef CTBOUND
#define ctFeatRCVLSTopt
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatSYSQUEmonitor supports monitoring system queues by placing the queue
  handle and queue name into a memory file.

  Enabled for server in v11.6.1 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1)
#ifdef MULTITRD
#ifndef NO_ctFeatSYSQUEmonitor
#define ctFeatSYSQUEmonitor
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatRCVOPNopt speeds up automatic recovery's check for an already-open file
  by creating a hash table of the original and full filenames of files that
  are open. Without this enhancement, when auto recovery opens many files, a
  significant amount of time can be spent in the loop in chkfid().

  Enabled for TRANPROC compiles in v11.6.1 and later. Requires ctFeatFILENAMEhash.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,6,1) /* Activated:Jeff K:v11.6.1:190725; Activated:Ray:v11.8.0 forward:190912 */
#ifndef NO_ctFeatRCVOPNopt
#if defined(TRANPROC) && defined(ctFeatFILENAMEhash)
#define ctFeatRCVOPNopt
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatPART_AUTO_PURGE enables the automatic partition purge feature. This
  feature makes it possible to define a maximum number of active partitions
  for a partition host file. Whenever the creation of a new partition causes
  the number of partitions to exceed the maximum, the lowest-numbered partition
  is purged.

  Enabled in v11.8 and future for c-tree Server when partition support is on.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifndef NO_ctFeatPART_AUTO_PURGE
#if defined(ctPARTITION) && defined(ctSRVR)
#define ctFeatPART_AUTO_PURGE
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatCONFIG_OPTION_BUFFER enables the ctSetConfigurationOptions() function,
  which specifies c-tree Server configuration options in a memory buffer in the
  format of the c-tree Server configuration file.

  Enabled for c-tree Server.
----------------------------------------------------------------------------*/
#ifdef ctSRVR
#ifndef NO_ctFeatCONFIG_OPTION_BUFFER
#define ctFeatCONFIG_OPTION_BUFFER
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatCFGsubdir changes the default location for the server configuration file
  ctsrvr.cfg to ./config. If it is not found in that location, we try to open it
  in the working directory as before.

  Default: ctFeatCFGsubdir is ON for v11.8.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifndef NO_ctFeatCFGsubdir
#ifdef ctSRVR
#define ctFeatCFGsubdir
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatFORCE_BLOCKING_LOCK enables support for setting a state on a lock that
  causes a non-blocking lock request to automatically block.

  Default: ctFeatFORCE_BLOCKING_LOCK is ON for c-tree Server in v11.8.0 and up.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifdef ctSRVR
#ifndef NO_ctFeatFORCE_BLOCKING_LOCK
#define ctFeatFORCE_BLOCKING_LOCK
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatTRANSACTION_ID enables support for including a transaction id on a
  transaction's commit entry in the transaction log.

  Default: ctFeatTRANSACTION_ID is ON in v11.9.0 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,0)
#ifndef NO_ctFeatTRANSACTION_ID
#define ctFeatTRANSACTION_ID
#endif
#endif


/*----------------------------------------------------------------------------
  ctFeatCOMPACT_TRUNCATE enables support for truncate operation during compact

  Default: ctFeatCOMPACT_TRUNCATE is ON in v11.9.5 and later.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatCOMPACT_TRUNCATE
#define ctFeatCOMPACT_TRUNCATE
#endif
#endif

#ifdef ctFeatCOMPACT_TRUNCATE
#ifdef ctDBGfcqa
#ifndef NO_ctDEBUG_COMPACT_TRUNCATE
/* debug option to support triggering failures at specified points of compact operation */
#define ctDEBUG_COMPACT_TRUNCATE
#endif
#endif
#endif


/*--------------------------------------------------------------*/
/* ctFeatPLUGIN_CB turns on support for callback plugins.       */
/*                                                              */
/* Default: ctFeatPLUGIN_CB is ON for v11.8 and future          */
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,8,0)
#ifndef NO_ctFeatPLUGIN_CB
#if defined(ctFeatPLUGIN)
#define ctFeatPLUGIN_CB 
#endif
#endif
#endif


#ifdef ctFeatPLUGIN_CB
#define LoadExternalCallback(x) ctLinkPluginCallback(x)
#define UnloadExternalCallback(x) ctUnlinkPluginCallback(x)
#else
#define LoadExternalCallback(x) ctdll_load(x)
#define UnloadExternalCallback(x) ctdll_unload(x)
#endif


/*--------------------------------------------------------------*/
/* ctFeatVFYIDXspace turns on support for ctVFYIDXspace option  */
/*                                                              */
/* Default: ctFeatVFYIDXspace is ON for v11.9.5 and future      */
/*--------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatVFYIDXspace
#define ctFeatVFYIDXspace
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatOPNCNTatomic uses atomic operations instead of a mutex to serialize
  updates to the system file control block's opncnt field.

  Default: ctFeatOPNCNTatomic is ON in v11.8.0 forward and special v11.6.1.
  Requires atomic operation support.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,8,0) || (ctVER3_GE(11,6,1) && (defined(ctPortDSTINTL) || defined(ctPortHBRTG)))
#ifndef NO_ctFeatOPNCNTatomic
#ifdef ctFeatATOMICop
#define ctFeatOPNCNTatomic
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatFILELISTmulti changes the single file list into one file list for each
  file list type.

  Default: ON in v11.9.5 and later for the server.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatFILELISTmulti
#if defined(ctSRVR) && defined(ctFeatFILELISTrwl)
#define ctFeatFILELISTmulti
#endif
#endif
#endif

#ifdef ctFeatFILELISTmulti

/* we use a separate reader/writer lock for each file list */
#define CTRWLFLST(state) ctrwlflst[state - 1]

#define DEDLST_TOT(state) dedlst_tot[state - 1]
#define DEDLST_CUR(state) dedlst_cur[state - 1]
#define DEDLST_AVL(state) dedlst_avl[state - 1]
#define DEDLST_PTR(state) dedlst_ptr[state - 1]

#else

/* we use a single global reader/writer lock for all file lists */
#define CTRWLFLST(state) ctrwlflst

#define DEDLST_TOT(state) dedlst_tot
#define DEDLST_CUR(state) dedlst_cur
#define DEDLST_AVL(state) dedlst_avl
#define DEDLST_PTR(state) dedlst_ptr

#endif

#if ctVER3_GE(11,9,5)
#ifdef ctFeatOPTIMIZE_FILE_OPEN
#ifndef NO_ctFeatSYSTEM_FILE_ID_LIST
/*----------------------------------------------------------------------------
  ctFeatSYSTEM_FILE_ID_LIST enables tracking system file ids of open files in
  a global list.

  Default: ON in the v11.9.5 and up when file open optimization support is on
  at compile time.
----------------------------------------------------------------------------*/
#define ctFeatSYSTEM_FILE_ID_LIST

/* default value for SYSTEM_FILE_ID_LIST configuration option */
#define SYSTEM_FILE_ID_LIST_DEFAULT OPTIMIZE_FILE_OPEN_DEFAULT

#ifndef ctFeatCHECK_SYSTEM_FILEID
#ifndef NO_ctFeatCHECK_SYSTEM_FILEID
/* check system fileid turned on by system file id list feature */
#define ctFeatCHECK_SYSTEM_FILEID
#else
#error system file id list requires system file id check to be enabled
#endif
#endif

#endif
#endif
#endif

#if defined(ctPortSOLARIS_64) || defined(ctPortRS6000_64)
#ifndef NO_ct64BIT_DEVICE_ID
/*----------------------------------------------------------------------------
  ct64BIT_DEVICE_ID is on when the operating system uses a 64-bit device id
  instead of a 32-bit device id.
----------------------------------------------------------------------------*/
#define ct64BIT_DEVICE_ID
#endif
#endif

#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatREPLAGENTparallel
#if defined(ctFeatREPLICAT_SYNC) && !defined(ctSRVR)
/*----------------------------------------------------------------------------
  ctFeatREPLAGENTparallel enables parallelization in the replication agent.
  Requires synchronous replication support.
----------------------------------------------------------------------------*/
#define ctFeatREPLAGENTparallel
#endif
#endif
#endif

#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatREPLICAT_SRVRparallel
#ifdef ctFeatREPLICAT_SYNC_SRVR
/*----------------------------------------------------------------------------
  ctFeatREPLICAT_SRVRparallel enables parallelization of replication in the
  server. Requires synchronous replication support.
----------------------------------------------------------------------------*/
#define ctFeatREPLICAT_SRVRparallel
#endif
#endif
#endif

#ifdef ctFeatKEEPOPEN
#ifndef NO_ctFeatKEEPOPENoffAtLogoff
/*----------------------------------------------------------------------------
  ctFeatKEEPOPENoffAtLogoff enables a file state that causes the connection
  to turn off KEEPOPEN for the file when disconnecting.
----------------------------------------------------------------------------*/
#define ctFeatKEEPOPENoffAtLogoff
#endif
#endif

#if ctVER3_GE(11,9,5)
#ifdef ctJSONCLIB
#ifndef NO_ctFeatCLUSTER_OPTIONS
/*----------------------------------------------------------------------------
  ctFeatCLUSTER_OPTIONS enables support for using cluster options. Requires
  JSON C library support.
----------------------------------------------------------------------------*/
#define ctFeatCLUSTER_OPTIONS
#endif
#endif
#endif

#ifdef ctFeatPLUGIN
#ifndef NO_ctFeatPLUGIN_DYNAMIC
/*----------------------------------------------------------------------------
  ctFeatPLUGIN_DYNAMIC enables loading of plugins on demand.
----------------------------------------------------------------------------*/
#define ctFeatPLUGIN_DYNAMIC
#endif
#endif


#if ctVER3_GE(11,9,0) || defined(ctPortINFOTRAX) || defined(ctPortRTG)
#ifndef NO_ctFeatHEAP_DEBUGGING
#ifdef MULTITRD
/*----------------------------------------------------------------------------
  ctFeatHEAP_DEBUGGING enables runtime heap debugging options for the
  ctree suballocator (ctgetmem/ctputmem).
----------------------------------------------------------------------------*/
#define ctFeatHEAP_DEBUGGING
#define HEAP_DEBUG_OFF 0 /* use default allocator */
#define HEAP_DEBUG_LOW  1 /* default allocator with minimal overrun detection */
#define HEAP_DEBUG_MEDIUM 2 /* default allocator with a checks for overrun/underrun. small increase in memory usage  */
#define HEAP_DEBUG_HIGH  3 /* special allocator - immediate crash likely on heap buffer overrun, double free, use after free.  checks for underrun at free. Potential for significant increase in memory usage. */

#endif
#endif
#endif

#if ctVER3_GE(11,9,0)
#ifndef NO_ctFeatREADPRUNE
#ifdef MULTITRD
/*----------------------------------------------------------------------------
  ctFeatREADPRUNE enables pruning of empty leaf nodes that are read from disk.
----------------------------------------------------------------------------*/
#define ctFeatREADPRUNE
#endif
#endif
#endif

#ifndef NO_ctFeatHISTORY_COMBINED_IMAGE
/*----------------------------------------------------------------------------
  ctFeatHISTORY_COMBINED_IMAGE enables the transaction history function to
  properly read transaction log entries that contain both the record header
  and record body in one entry. Requires commit read lock optimizations.
----------------------------------------------------------------------------*/
#define ctFeatHISTORY_COMBINED_IMAGE
#endif




#if ctVER3_GE(11,8,0) && defined(ctSRVR) && defined(ctPortWIN32)
#ifndef NO_ctFeatSYSTEM_TIMER_RESOLUTION
/*----------------------------------------------------------------------------
  ctFeatSYSTEM_TIMER_RESOLUTION enables a configuration option to set the
  Windows system timer resolution. Enabled for c-tree Server on Windows.

  Requires ctFeatDLL_LOAD_OPTIONS (checked later).
----------------------------------------------------------------------------*/
#define ctFeatSYSTEM_TIMER_RESOLUTION

/* default system timer resolution */
#define DEFAULT_SYSTEM_TIMER_RESOLUTION "1"

#endif
#endif

#if ctVER3_GE(11,9,0)
#ifndef NO_ctFeatSTACK_DUMP
#ifdef ctFeatPSTACK
/*----------------------------------------------------------------------------
  ctFeatSTACK_DUMP enables the STACK_DUMP keyword and behavior changes.
----------------------------------------------------------------------------*/
#define ctFeatSTACK_DUMP
#define STACK_DUMP_DEFAULT "CONTEXT"
#endif
#endif
#endif

#ifndef NO_ctFeatDLL_LOAD_OPTIONS
#ifdef ctFeatCTDLLerrbuf
/*----------------------------------------------------------------------------
  ctFeatDLL_LOAD_OPTIONS enables option bits for loading c-tree DLLs.
  Requires ctFeatCTDLLerrbuf.
----------------------------------------------------------------------------*/
#define ctFeatDLL_LOAD_OPTIONS
#endif
#endif

#ifndef ctFeatDLL_LOAD_OPTIONS
/* system timer resolution requires c-tree DLL load options */
#undef ctFeatSYSTEM_TIMER_RESOLUTION
#endif

#ifndef NO_ctFeatCHECK_FILENAME_VALIDITY
#if ctVER3_GE(11,9,0)
/*----------------------------------------------------------------------------
  ctFeatCHECK_FILENAME_VALIDITY enables a check for invalid file names when
  creating and opening files.

  Enabled in v11.9.0 and later.
----------------------------------------------------------------------------*/
#define ctFeatCHECK_FILENAME_VALIDITY

/* default to checking file name validity */
#define DEFAULT_CHECK_FILENAME_VALIDITY "YES"

#endif
#endif

#ifndef NO_ctFeatSSL_ENCRYPT
#if ctVER3_GE(11,9,0)
#ifdef ctFeatSSL
/*----------------------------------------------------------------------------
  ctFeatSSL_ENCRYPT allows using Openssl library for Encryption
  with the OPENSSL_ENCRYPTION keyword. Default is to use Faircom encryption.

  Enabled in v11.9.0 and later.
----------------------------------------------------------------------------*/
#define ctFeatSSL_ENCRYPT
#endif
#endif
#endif

#ifndef NO_ctFeatSSL_ENCRYPT_DEFAULT
#if ctVER3_GE(11,9,5)
#ifdef ctFeatSSL_ENCRYPT
/*----------------------------------------------------------------------------
  ctFeatSSL_ENCRYPT_DEFAULT makes OPENSSL_ENCRYPTION keyword default to ON.

  Enabled in v11.9.5 and later.
----------------------------------------------------------------------------*/
#define ctFeatSSL_ENCRYPT_DEFAULT  
#define DEFAULT_SSL_ENCRYPT "YES"
#endif
#endif
#endif

#if ctVER3_GE(11,9,5)
#if defined(ctFeatREPLICAT) && defined(ctBEHAV_AUTOTRAN_ON_CREATE)
#if defined(ctSRVR) || defined(ctFeatREPLAGENTparallel)
#ifndef NO_ctFeatREPLICAT_DATA_DEFINITIONS
/*----------------------------------------------------------------------------
  ctFeatREPLICAT_DATA_DEFINITIONS enables support for replicating data
  definition operations such as file create, rename, and delete.

  Enabled in v11.9.5 and later when replication support is enabled.
  Requires automatic tran begin on file create. For non-server model,
  requires parallel replication support.
----------------------------------------------------------------------------*/
#define ctFeatREPLICAT_DATA_DEFINITIONS
#endif
#endif
#endif
#endif

#if defined(ctFeatNONBLK_SOCKIO) && (defined(ctCLIENT) || defined(ctMTCLIENT) || defined(ctLOCLIB))
#ifndef NO_ctFeatSOCKET_WAIT_INTERVAL
/*----------------------------------------------------------------------------
  ctFeatSOCKET_WAIT_INTERVAL enables the option to set a time interval in
  seconds for socket I/O calls, after which optional conditions can be checked
  and the operation can be retried.

  Enabled for client. Requires support for non-blocking socket I/O.
----------------------------------------------------------------------------*/
#define ctFeatSOCKET_WAIT_INTERVAL
#endif
#endif

#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatREPLICAT_SUPERFILE
/*----------------------------------------------------------------------------
  ctFeatREPLICAT_SUPERFILE enables replication of superfile hosts and members.
----------------------------------------------------------------------------*/
#define ctFeatREPLICAT_SUPERFILE
#endif
#endif

#ifdef STREE_TRUNK
#ifndef NO_ctFeatMAX_NAME_4K
/*----------------------------------------------------------------------------
  ctFeatMAX_NAME_4K increases the maximum supported file name length to 4KB.
----------------------------------------------------------------------------*/
/* #define ctFeatMAX_NAME_4K */
#endif
#endif

#ifdef STREE_TRUNK
#ifdef MULTITRD
#ifndef NO_ctFeatAUTO_SUPER_RESIZE
/*----------------------------------------------------------------------------
  ctFeatAUTO_SUPER_RESIZE checks FAIRCOM.FCS, ctdbdict.fsd, and known SQL database
  page size settings at startup.  If they don't match the server configuration
  ctscmp is launched to convert to the configured page size.
----------------------------------------------------------------------------*/
#define ctFeatAUTO_SUPER_RESIZE
#endif
#endif
#endif

#if ctVER3_GE(11,8,0)
#ifdef MULTITRD
#ifndef NO_ctFeatDUMP_ABORT
/*----------------------------------------------------------------------------
  ctFeatDUMP_ABORT allows a dynamic dump request use !DELAY option to have
  the dump give up rather than forcibly abort long lived transactions.
----------------------------------------------------------------------------*/
#define ctFeatDUMP_ABORT
#endif
#endif
#endif

#ifdef ctSRVR
#ifndef NO_ctFeatDEFAULT_SERVER_LICENSE
/*----------------------------------------------------------------------------
  ctFeatDEFAULT_SERVER_LICENSE enables a default server license that is compiled
  in to the server binary and is used if no license file is found.
----------------------------------------------------------------------------*/
#ifdef  ctPortMEMPHIS_SERVER
#define ctFeatDEFAULT_SERVER_LICENSE
#endif
#endif
#endif

/*----------------------------------------------------------------------------
  ctFeatREPLICAT_SYNC2 modifies synchronous replication processing to resolve
  some issues in the initial implementation of synchronous replication.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#if defined(ctFeatREPLICAT_SYNC) && !defined(NO_ctFeatREPLICAT_SYNC2)
#define ctFeatREPLICAT_SYNC2
#endif
#endif

#if defined(ctFeatREPLICAT_SYNC2) && defined(ctSRVR)
#define ctFeatREPLICAT_SYNC2_SRVR
#ifdef ctDBGfcqa
#define ctDBG_REPLICAT_SYNC2 /* synchronous replication debugging */
#endif
#endif

#define DEFAULT_SYNC_COMMIT_TIMEOUT "60" /* default SYNC_COMMIT_TIMEOUT is 60 seconds */

/*----------------------------------------------------------------------------
  ctFeatREPLAGENT_FILE_FILTER enables support for a server maintaining a list
  of persistent replication agent file filters.

  Requires synchronous replication support version 2.
----------------------------------------------------------------------------*/
#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatREPLAGENT_FILE_FILTER
#ifdef ctFeatREPLICAT_SYNC2
#define ctFeatREPLAGENT_FILE_FILTER
#endif
#endif
#endif

#if defined(ctFeatREPLAGENT_FILE_FILTER) && defined(ctSRVR)
#define ctFeatREPLAGENT_FILE_FILTER_SRVR
#endif

#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatCLIENT_SPLFEAT
/* enable special client features */
#ifndef ctFeatCLIENT_SPLFEAT
#define ctFeatCLIENT_SPLFEAT
#endif
#endif
#endif

#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatOPTIMIZE_INITIAL_LOG_TEMPLATE_CREATE
/*----------------------------------------------------------------------------
  ctFeatOPTIMIZE_INITIAL_LOG_TEMPLATE_CREATE speeds up the creation of the first
  transaction log when the server has COMPATIBILITY LOG_WRITETHRU enabled and is
  using log templates.
----------------------------------------------------------------------------*/
#define ctFeatOPTIMIZE_INITIAL_LOG_TEMPLATE_CREATE
#endif
#endif

#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatREPLAGENT_FILE_FILTER_REGEX
#ifdef ctFeatREPLAGENT_FILE_FILTER
/*----------------------------------------------------------------------------
  ctFeatREPLAGENT_FILE_FILTER_REGEX enables support for specifying a regular
  expression in a replication file filter.
----------------------------------------------------------------------------*/
#define ctFeatREPLAGENT_FILE_FILTER_REGEX
#endif
#endif
#endif

#ifdef STREE_TRUNK
#ifndef NO_ctFeatCLIENT_NOTIFY
#if defined(ctMTCLIENT) && defined(ctCOMMP_TCPIP)
/*----------------------------------------------------------------------------
  ctFeatCLIENT_NOTIFY enables support for a thread that monitors TCP/IP
  broadcast messages for a server failover notification.
----------------------------------------------------------------------------*/
#define ctFeatCLIENT_NOTIFY
#endif
#endif
#endif

/* the length of a null-terminated failover unique identifier; its format is xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx */
#define FAILOVER_UNIQUE_ID_LEN 37

#if ctVER3_GE(11,9,5)
#ifndef NO_ctFeatCOUNT_FCWORKERS
#ifdef ctSRVR
/*----------------------------------------------------------------------------
  ctFeatCOUNT_FCWORKERS enables a separate count of FairCom work connections.
----------------------------------------------------------------------------*/
#define ctFeatCOUNT_FCWORKERS
#endif
#endif
#endif

/* } END ctFeat... Options */
/*~********************************************/

#ifdef ctFeatATOMICop
/*
** ctInterlockedMax		signed 32-bit maximum
** ctInterlockedAdd8		signed 64-bit sum
** ctInterlockedModIncrement	signed 32-bit modular increment
**
** ctInterlockedXyz is a system independent implementation of an
** interlocked operation that requires only the basic system
** level interlocked support (ctupdt.c)
**
** the ctInterlockedXyz32/64 macro provides a calling sequence consistent
** with the other interlocked, system independent calls
*/
#define ctInterlockedMax32(max,candidate) ctInterlockedMax(&max,candidate)
#define ctInterlockedAdd64(sum,delta)     ctInterlockedAdd8(&sum,delta)
#define ctInterlockedModIncrement32(val,base) ctInterlockedModIncrement(&val,base)

/*
** check for interlocked ctpconcsema support
**
** ctBEHAV_WORKsyncInterlocked cannot be defined externally.
*/
#ifdef ctBEHAV_WORKsyncInterlocked
#undef ctBEHAV_WORKsyncInterlocked
#endif

#ifdef ctBEHAV_WORKsyncRWL
#ifndef NO_ctBEHAV_WORKsyncInterlocked
#define ctBEHAV_WORKsyncInterlocked
#endif
#endif

#endif

/* ictrt_filmtc() options: */
#define WC_SLASHEQUIV	0x00000002	/* consider / and \ to be equivalent */

/*^*********************************************/
/*
** Augmented Data records
**
** ctAUGREC support
**
** ctAUGREC is on by default or it is turned on when other
** types of augmentation are turned on, such as ctCMPREC (below).
** ctAUGREC requires ctHUGEFILE support.
**
**
** variable length data records have a record header that precedes
** the actual data record image. the application does not see the
** record header or manipulate it. It may be considered meta-data:
** data that describes the data record. the c-tree kernel is designed
** to seamlessly maintain and use the record header. in this context,
** we introduce the concept of augmented data records: records
** whose header is extended to provide more meta-data. to avoid
** reworking extensive parts of the c-tree kernel, and to avoid
** adding overhead to variable length files that are not augmented,
** we have chosen the following approach to augment the data record header:
**
**	(1) a variable length file whose records are augmented will
** have one or more bits set in the flmode3 header field to indicate
** the nature of the augmentation;
**	(2) the first four bytes after the record header will contain
** the length of the logical data record image (i.e., the length of
** the data record before any augmentation or transformation);
**	(3) if these first four bytes are zero, then we know that the
** actual data record image follows immediately without any augmentation
** or transformation;
**	(4) following the first four bytes will be zero or more bytes
** that describe the length of each type of meta-data that precedes
** the logical data record image: the nature of these bytes, if any,
** is determined by bits set in flmode3.
**	(5) an exception to (2) above is for ctVLENGTH files whose
** only augmentation is to turn on the ctAugmentedFxd bit at create which
** signifies that the data records are actually fixed in length even though
** they are contained in a variable length file. The ctAugmentedFxd
** bit is set in flmode3 for files that restrict records to a fixed length.
** if the VLENGTH file also has compression turned on, then both the
** ctAugmentedFxd and ctCompressRec bits are on and (2) above applies. (this
** latter situation corresponds to a fixed length data file with compression
** turned on.
*/

#ifndef NO_ctAUGREC
#ifdef ctHUGEFILE
#define ctAUGREC
#endif
#endif

/*
** Data Record compression is our first implementation of augmented
** data records that requires the four-byte logical length. The ctCompressRec
** bit is set in flmode3 for files with compressed data records. No
** additional meta-data is required beyond the logical data record length.
*/

/*
** ctCMPREC support
**
** This #define is typically controlled by the mtree options (ctoptn.h)
** and depends on an external compression LIB, and optional compression
** DLLs.
*/


/*
** for requests to decompress a partial image, ctCMPRECpartialAdj is
** the number of extra bytes of the partial compressed image we use
** in the decompression process. This is an arbitrary amount, and is
** based on (1) the assumption that the entire compressed image is not
** necessary to decompress the beginning of the image; and (2) the extra
** bytes will be enough to accommodate any internal compression data that
** might be part of the compressed image.
*/
#define ctCMPRECpartialAdj	32

/*
** Record Compression requires ctHUGEFILE
*/
#ifdef ctCMPREC
#ifndef ctHUGEFILE
#undef ctCMPREC
#endif
#endif

#if defined(ctCMPREC) && defined(ctBEHAV_CMTLOK_optimize) && defined(UNIFRMAT)
*** this is an unexpected, unsupported combination ***
#endif

#if (defined(ctCMPREC) || defined(ctFeatFLEXREC)) && !defined(ctAUGREC)
#define ctAUGREC
#endif

#if defined(ctFeatFLEXREC) && (!defined(ctCMPREC) || !defined(ctBEHAV_CMPREC_optimize))
/* If we turned on ctFeatFLEXREC in ctopt2.h, turn it off. */
#ifdef ctFeatFLEXRECctopt2
#undef ctFeatFLEXREC
#ifdef ctFeatBATCHCOLFLTR
#undef ctFeatBATCHCOLFLTR
#endif
#else
/* Other code turned on ctFeatFLEXREC: ERROR */
#error Flexible record format support requires data compression support
#endif
#endif

#if defined(ctFeatREPLICAT_FLXDAT) && !defined(ctFeatFLEXREC)
/* If we turned on ctFeatREPLICAT_FLXDAT in ctopt2.h, turn it off. */
#ifdef ctFeatREPLICAT_FLXDATctopt2
#undef ctFeatREPLICAT_FLXDAT
#else
/* Other code turned on ctFeatREPLICAT_FLXDAT: ERROR */
#error ctFeatREPLICAT_FLXDAT requires ctFeatFLEXREC
#endif
#endif

#ifdef ctFeatFLEXREC
#ifndef NO_ctFeatREPLICAT_FLEXREC
/* Enable replication support for FLEXREC files. */
#define ctFeatREPLICAT_FLEXREC
#endif
#endif

/*
** compression types
*/
#define ctCMPRECzlib	1
#define ctCMPRECuser	2
#define ctCMPRECsRLE	3

/*
** max zlib version supported. min zlib version is 1.
*/
#define ctCMPRECzlibMaxVrsn	1

/*
** Number of Compression Functions that must be supported
** by a compression subsystem
*/
#define NbrCmpFnc	8

/*
** compress/decompression routine status codes
*/
#define CMPREC_OK	0	/* NO_ERROR				*/
#define CMPREC_BUF	1	/* destination buffer too small		*/
#define CMPREC_DATA	2	/* compressed stream appears corrupt	*/
#define CMPREC_ERR	3	/* unexpected error: sysiocod set to	**
				** routine specific code		*/

/*~********************************************/

/*
** Number of Deferred Indexing Functions that can be defined by an application
*/
#define NbrDfrkFnc	4


/*
** Number of Record Update Callback Functions that can be defined by an application
*/
#define NbrRUCBFnc	3


/*^*********************************************/
/* check for any distributed count Features */

#if defined(ctFeatDISTbufcnt) || defined(ctFeatDISTdatcnt)
#define ctDISTcounts
#endif

/*~********************************************/

/*^*********************************************/
/* { ctDBG... Options (Internal debugging options) */

/*^*******************/
/*
** ctDBGupdflg turns on monitoring of changes to a file's updflg
**
** In a server, DIAGNOSTICS UPDFLG must also be present to generate
** debug output.
**
** When ctDBGupdflg is active, CTSTATUS.FCS receives messages of the
** form
**	UPDFLG: <filename> at updLoc=wxyz  updflg=NNx oldflg=OOx
**
** where the updLoc value (wxyz) indicates where the update flag
** was changed. For wxyz in the range of 1000-1999, search the c-tree
** source code for the string "ctSETupdflg(wxyz," and for wxyz greater
** than 1999 search the source for the string "UPD(wxyz)". The values above
** 1999 indicate that a call to tstupd or setidxcorrupt changed the updflg.
** The smaller values correspond to in-line changes of updflg.
*/
/*~*******************/
#ifdef ctSRVR
/* #define ctDBGupdflg */
#endif

/*^*******************/
/*
** ctDBGchkpnt_queue enables the logging of checkpoint queue status
** messages by the c-tree Server when CHECKPOINT_MONITOR YES is specified in
** the server configuration file.
**
** DEFAULT:  ctDBGchkpnt_queue is NOT activated
*/
/*~*******************/

#ifdef ctSRVR
/*
#define ctDBGchkpnt_queue
*/
#endif

/*^*******************/
/*
** ctDBGusrcnt enables the tracking of changes to the user count of a file.
**
** DEFAULT:  ctDBGusrcnt is NOT activated
*/
/*~*******************/

#ifdef ctSRVR
/*
#define ctDBGusrcnt
*/
#endif

/*^*******************/
/*
** ctDBGsemlst enables the tracking of synchronization objects
** acquired by c-tree threads.
**
** DEFAULT:  ctDBGsemlst is NOT activated
*/
/*~*******************/

#ifdef ctSRVR
/*
#define ctDBGsemlst
*/
#endif

#ifdef ctDBGsemlst
#define ctDBGSEM
#define ctDBGSEMCNT
#endif

/*^*******************/
/*
** ctDBGfcbio enables the tracking of I/O operations for a specified file.
**
** DEFAULT:  ctDBGfcbio is NOT activated
*/
/*~*******************/

#ifdef ctSRVR
/*
#define ctDBGfcbio
*/
#endif

/*^*******************/
/*
** ctDBGfcqa enables internal diagnostic options of interest to FairCom
** developers and QA testers. These options enable a variety of internal
** checks for unexpected situations.
**
** DEFAULT:  ctDBGfcqa is NOT enabled.
*/
/*~*******************/
#ifdef ctSRVR
/* #define ctDBGfcqa */
#endif

#ifdef ctDBGfcqa
#ifdef MULTITRD
#define ctDBGSEMrecur
#ifndef NO_ctDBGSEMCNT
#define ctDBGSEMBLK
#define ctDBGSEMCNT
#define ctDBGSEMTIM
#ifdef ctFeatIICT
#define ctDBGiict
#endif
#endif
#define ctDBGmemfill
#ifdef ctPortWIN32
/*#define ctDBGDLOK*/
#ifdef ctDBGDLOK
#define ctDBGSEM
#endif
#define ctPALLOC
#endif
#define ctDBGfcbstk
#endif
#endif

#ifdef ctDBGSEMCNT
					/*
					** see ctDBGSEMMOD in ctgvar.h for
					** the limit on nn. For example, if
					** ctDBGSEMMOD is 72, then the
					** max nn is 7099 since the 71xx
					** are used for a special memory
					** sub-allocator list breakdown.
					*/

#define SMN(nn)		,nn
#define LMN(nn)		,nn
#define PMN(nn)		nn
#define SQLSMN(nn)		,9700+nn
#ifdef ctDBG_RWLOCK
#ifndef ctDBGRWLCNT
#define ctDBGRWLCNT
#endif
#endif

#else /* ~ctDBGSEMCNT */

#define SMN(nn)
#ifdef ctDBGRWLCNT
#define LMN(nn)		,nn
#else
#define LMN(nn)
#endif
#define PMN(nn)		nn
#define SQLSMN(nn)

#endif /* ~ctDBGSEMCNT */

/*
** IDXrwlock uses slim reader/writer locks for idxsem. without
** IDXreader defined, all writer locks are used. with IDXreader
** defined, reader locks are acquired on idxsem for non-leaf nodes
** for indices that do not use key compression.
**
** NOTE: if IDXrwlock is not defined, then ctsemrqs is used to
** acquire idxsem.
**
** at this stage the reader locks are only acquired in the low level
** index search routines found in ctsrch.c
*/

#if	!defined(NO_IDXrwlock)	&& \
	!defined(IDXrwlock)	&& \
	defined(ctFeatNoIdxPndgList)
#define	IDXrwlock
#endif

#if	defined(IDXrwlock)		&& \
	(!defined(ctFeatRWLOCK) 	|| \
	 !defined(ctFeatNoIdxPndgList))
#undef IDXrwlock
#endif


#if !defined(NO_IDXreader) && !defined(IDXreader)
#define	IDXreader
#endif

#if defined(IDXreader) && !defined(IDXrwlock)
#undef IDXreader
#endif

#if defined(ctFeatLEAF_NODE_READ_LOCK) && !defined(IDXreader)
/* If we turned on ctFeatLEAF_NODE_READ_LOCK in ctopt2.h, turn it off. */
#ifdef ctFeatLEAF_NODE_READ_LOCK_ctopt2
#undef ctFeatLEAF_NODE_READ_LOCK
#else
/* Other code turned on ctFeatLEAF_NODE_READ_LOCK: ERROR */
#error ctFeatLEAF_NODE_READ_LOCK requires IDXreader support
#endif
#endif

#if defined(ctFeatCHKREMNOD_READ_LOCK) && !defined(ctFeatLEAF_NODE_READ_LOCK)
/* If we turned on ctFeatCHKREMNOD_READ_LOCK in ctopt2.h, turn it off. */
#ifdef ctFeatCHKREMNOD_READ_LOCK_ctopt2
#undef ctFeatCHKREMNOD_READ_LOCK
#else
/* Other code turned on ctFeatCHKREMNOD_READ_LOCK: ERROR */
#error ctFeatCHKREMNOD_READ_LOCK requires ctFeatLEAF_NODE_READ_LOCK support
#endif
#endif

#ifndef IDXreader
#undef ctBEHAV_SET_ACTLEN_EXCLUSIVE
#endif

/*
** use slim reader/writer locks for ctputrsema. ctputrsema controls
** the update of transaction state variables for a thread that
** other threads may query
*/
#if	!defined(NO_UTRrwlock)	&& \
	!defined(UTRrwlock)
#define	UTRrwlock
#endif

#if	defined(UTRrwlock)	&& \
	!defined(ctFeatRWLOCK)
#undef UTRrwlock
#endif

/*
** use slim reader/writer locks for ctpc3ncsema. ctpc3ncsema controls
** the update of system state variables related to dynamic dumps such as
** ctdflg. reader locks will enable threads testing the states to run
** concurrently.
*/
#if	!defined(NO_C3Nrwlock)	&& \
	!defined(C3Nrwlock)
#define	C3Nrwlock
#endif

#if	defined(C3Nrwlock)	&& \
	!defined(ctFeatRWLOCK)
#undef C3Nrwlock
#endif

/*
** use slim reader/writer locks for ctpcpcsema. ctpcpcsema controls
** the update of system state variables related to the checkpoint count
** and node abort list maintenance related to ctLOG_IDX. reader locks
** will enable threads testing the states to run concurrently.
*/
#if	!defined(NO_CPCrwlock)	&& \
	!defined(CPCrwlock)
#define	CPCrwlock
#endif

#if	defined(CPCrwlock)	&& \
	!defined(ctFeatRWLOCK)
#undef CPCrwlock
#endif



#ifdef IDXrwlock

#define IDX_RWL(loktyp)		loktyp
#define IDX_RWCA(loktyp,own)	RWCA(loktyp,own)
#ifdef ctDBGSEMCNT
#define ctIDXtry(ps,loktyp,own,loc)	ctRWLtry(ps,loktyp,own,loc)
#define ctIDXrqs(ps,loktyp,own,loc)	ctRWLrqs(ps,loktyp,own,loc)
#else
#define ctIDXtry(ps,loktyp,own,loc)	ctRWLtry(ps,loktyp,own)
#define ctIDXrqs(ps,loktyp,own,loc)	ctRWLrqs(ps,loktyp,own)
#endif
#define ctIDXclr		ctRWLclr
#define ctIDXcls(ps)		ctRWLcls(ps)

#else /* ~IDXrwlock */

#define IDX_RWL(loktyp)		no_parm
#define IDX_RWCA(loktyp,own)	own
#ifdef ctDBGSEMCNT
#define ctIDXtry(ps,loktyp,own,loc)	ctsemrqs(ps,NOWAIT,own,loc)
#define ctIDXrqs(ps,loktyp,own,loc)	ctsemrqs(ps,WAIT,own,loc)
#else
#define ctIDXtry(ps,loktyp,own,loc)	ctsemrqs(ps,NOWAIT,own)
#define ctIDXrqs(ps,loktyp,own,loc)	ctsemrqs(ps,WAIT,own)
#endif
#define ctIDXclr(ps,own)	ctsemclr(ps,own)
#define ctIDXcls(ps)		ctsemcls(ps)

#endif /* ~IDXrwlock */


#ifdef UTRrwlock

#define UTR_RWL(loktyp)		loktyp
#define UTR_RWCA(loktyp,own)	RWCA(loktyp,own)
#ifdef ctDBGSEMCNT
#define ctUTRrqs(ps,loktyp,own,loc)	ctRWLrqs(ps,loktyp,own,loc)
#else
#define ctUTRrqs(ps,loktyp,own,loc)	ctRWLrqs(ps,loktyp,own)
#endif
#define ctUTRclr		ctRWLclr
#define ctUTRcls(ps)		ctRWLcls(ps)

#else /* ~UTRrwlock */

#define UTR_RWL(loktyp)		no_parm
#define UTR_RWCA(loktyp,own)	own
#ifdef ctDBGSEMCNT
#define ctUTRrqs(ps,loktyp,own,loc)	ctmutrqs(ps,own,loc)
#else
#define ctUTRrqs(ps,loktyp,own,loc)	ctmutrqs(ps,own)
#endif
#define ctUTRclr(ps,own)	ctmutclr(ps,own)
#define ctUTRcls(ps)		ctmutcls(ps)

#endif /* ~UTRrwlock */

#ifdef C3Nrwlock

#define C3N_RWL(loktyp)		loktyp
#define C3N_RWCA(loktyp,own)	RWCA(loktyp,own)
#ifdef ctDBGSEMCNT
#define ctC3Nrqs(ps,loktyp,own,loc)	ctRWLrqs(ps,loktyp,own,loc)
#else
#define ctC3Nrqs(ps,loktyp,own,loc)	ctRWLrqs(ps,loktyp,own)
#endif
#define ctC3Nclr		ctRWLclr
#define ctC3Ncls(ps)		ctRWLcls(ps)

#else /* ~C3Nrwlock */

#define C3N_RWL(loktyp)		no_parm
#define C3N_RWCA(loktyp,own)	own
#ifdef ctDBGSEMCNT
#define ctC3Nrqs(ps,loktyp,own,loc)	ctmutrqs(ps,own,loc)
#else
#define ctC3Nrqs(ps,loktyp,own,loc)	ctmutrqs(ps,own)
#endif
#define ctC3Nclr(ps,own)	ctmutclr(ps,own)
#define ctC3Ncls(ps)		ctmutcls(ps)

#endif /* ~C3Nrwlock */

#ifdef CPCrwlock

#define CPC_RWL(loktyp)		loktyp
#define CPC_RWCA(loktyp,own)	RWCA(loktyp,own)
#ifdef ctDBGSEMCNT
#define ctCPCrqs(ps,loktyp,own,loc)	ctRWLrqs(ps,loktyp,own,loc)
#else
#define ctCPCrqs(ps,loktyp,own,loc)	ctRWLrqs(ps,loktyp,own)
#endif
#define ctCPCclr		ctRWLclr
#define ctCPCcls(ps)		ctRWLcls(ps)

#else /* ~CPCrwlock */

#define CPC_RWL(loktyp)		no_parm
#define CPC_RWCA(loktyp,own)	own
#ifdef ctDBGSEMCNT
#define ctCPCrqs(ps,loktyp,own,loc)	ctmutrqs(ps,own,loc)
#else
#define ctCPCrqs(ps,loktyp,own,loc)	ctmutrqs(ps,own)
#endif
#define ctCPCclr(ps,own)	ctmutclr(ps,own)
#define ctCPCcls(ps)		ctmutcls(ps)

#endif /* ~CPCrwlock */

/*
** define needRWLauxflds to support owner (ownr) and
** lock type (type) fields for slim reader/writer locks
*/
#if	defined(ctBEHAV_WORKsyncRWL)	|| \
	defined(IDXrwlock)		|| \
	defined(UTRrwlock)		|| \
	defined(C3Nrwlock)		|| \
	defined(CPCrwlock)
#define needRWLauxflds
#endif

/*^*******************/
/*
** ctDBGlowhsh introduces 10 millisecond delay in the middle of updating
** cache/buffer hash lists to ensure that proper mutex control is protecting
** the list contents
*/
/*~*******************/


/*^*******************/
/*
** ctDBGputhsh checks that the proper mutex is owned by the caller when
** updating the index buffer hash lists. terr(8484) through terr(8489)
** are raised in the event the proper mutex 'ownr' is not found.
*/
/*~*******************/

#ifdef ctDBGputhsh
#ifndef ctFeatGNSEMAhsh
#undef ctDBGputhsh
#endif
#endif


/*^*******************/
/*
** ctDBGputdsh checks that the proper mutex is owned by the caller when
** updating the data cache hash lists. terr(8494) through terr(8499)
** are raised in the event the proper mutex 'ownr' is not found.
*/
/*~*******************/

#ifdef ctDBGputdsh
#ifndef ctFeatDBSEMAhsh
#undef ctDBGputdsh
#endif
#endif


/*^*******************/
/*
** ctDBGRCVR logs automatic recovery details to the file RECOVERY.FCS when
** DIAGNOSTICS TRAN_RECOVERY is enabled in ctsrvr.cfg. Requires TRANPROC.
*/
/*~*******************/
#if ctVER3_GE(10,2,0)
#ifndef NO_ctDBGRCVR
#ifdef TRANPROC
#define ctDBGRCVR
/*
** When ctDBGRCVR is on at compile time for c-tree Server, it is only enabled
** at runtime if DIAGNOSTICS TRAN_RECOVERY is specified in ctsrvr.cfg.
*/
#define ctDBGRCVR_ON (ct_diagflg2 & ctDiagnose2TRAN_RECOVERY)
#endif
#endif
#endif

/* Intent lock diagnostic logging */
#ifdef ctFeatLOCKfile
#define ctDBGilk
#endif

/* Turn on ctDBGmemfile to log allocation and free calls for memory files
** to CTSTATUS.FCS. */
/* #define ctDBGmemfile */

/*----------------------------------------------------------------------------
  ctDBGfpglok enables diagnostic logging of c-tree lock calls, useful for
  studying lock behavior in the multi-threaded multi-user operational model.
-----------------------------------------------------------------------------*/
#ifdef ctMTFPG
/* #define ctDBGfpglok */
#endif

/* } END ctDBG... Options */
/*~********************************************/


/*^***********************************/
/* KidCat sets both these one */
#ifdef ctSRVR_MFC
#ifdef ctSRVR_MFC_001

#define ctFeatMFC_WinMainSTD		/* Use standard FairCom WinMain */
#undef  ctFeatMFC_WinMainEXTENDED	/* Use extended server Winmain 	*/
#undef  ctFeatMFC_MainWndEXTERNAL	/* Main window is external (mfc)*/
#undef  ctFeatMFC_ENDTHREAD		/* Server does endthread, not exit */
#undef  ctFeatMFC_m_pbShutdown		/* Use m_pbShutdown 		   */
#define ctFeatMFC_AUTH_SHUTDWN		/* Support mfc type ctAuthorizeShutdown */
#define ctFeatSERVER_IS_UP_SEMA		/* Support Server is up sema 	*/
#define ctFeatSERVER_IS_DOWN_SEMA	/* Support Server is down sema 	*/

#endif
#endif
/*~***********************************/

/*^***********************************/
/* FairCom's MFC Front End */
#ifdef ctSRVR_MFC
#ifndef ctSRVR_MFC_001

#undef  ctFeatMFC_WinMainSTD		/* Use standard FairCom WinMain */
#define ctFeatMFC_WinMainEXTENDED	/* Use extended server Winmain 	*/
#define ctFeatMFC_MainWndEXTERNAL	/* Main window is external (mfc)*/
#define ctFeatMFC_ENDTHREAD		/* Server does endthread, not exit */
#define ctFeatMFC_m_pbShutdown		/* Use m_pbShutdown 		   */
#define ctFeatMFC_AUTH_SHUTDWN		/* Support mfc type ctAuthorizeShutdown */
#define ctFeatSERVER_IS_UP_SEMA		/* Support Server is up sema 	*/
#define ctFeatSERVER_IS_DOWN_SEMA	/* Support Server is down sema 	*/

#endif
#endif
/*~***********************************/

#ifdef MULTITRD
#ifdef ctFeatAEKato
#ifndef ctFeatSETTINGS
#error This feature can only be enabled when settings file support is mandatory
#endif
#endif
#endif

#ifdef ctSYSQUE
#ifdef MULTITRD
#ifdef ctFeat6BT	/* V8 only			*/
#define ctSYSQUEsrvr
#endif
#endif
#endif

/*
** turn on support to impersonation of thread in order to abandon
** its transaction with a TRANABTX call
*/
#ifdef ctFeatMAX_USER_LOGS
#define ctIMPABNTRN
#else
#ifdef ctFeatTRAN_TIMEOUT
#define ctIMPABNTRN
#endif
#endif

#ifdef ctIMPABNTRN
#ifndef ctBEHAV_CTREErecurcnt
#define ctBEHAV_CTREErecurcnt
#endif
#endif



/**********************************************/
/* PREVIOUS CODE Options */

/*--------------------------------------------------------------*/
/* ctPREV_66A2_IFIL maintains the code to invoke conversion	*/
/* code for IFIL streams for alignment differences (as well as	*/
/* for byte ordering differences).				*/
/*								*/
/* DEFAULT: define ctPREV_66A2_IFIL. If this is not defined,	*/
/* then no alignment modification is made in the IFIL stream.	*/
/*--------------------------------------------------------------*/
#define ctPREV_66A2_IFIL

/*--------------------------------------------------------------*/
/* ctPREV_67A2_CTASSKEY maintains the code to use the local	*/
/* versions of the ctasskey() function in ctappx.c and ctismu.c	*/
/* instead of the new common code module ctassk.c		*/
/*								*/
/* DEFAULT: no ctPREV_66A2_IFIL. If this is not defined,	*/
/* then the new module is included in ctappx.c and ctismu.c.	*/
/*--------------------------------------------------------------*/
/* #define ctPREV_67A2_CTASSKEY */

/*----------------------------------------------------------------------*/
/* A new Flushing Mode was added in v610A to allow DOSFLUSH for both 	*/
/* NOTFORCE and FPUTFGET. Only perform flushdos for write thru files, 	*/
/* and only issue a save during file extensions for write thru files. 	*/
/* Under the server, this new feature can be deactivated or set to  	*/
/* previous operation by adding COMPATIBILITY PREV610A_FLUSH to config  */
/* file.								*/
/* By default, this define is off. Acivate only if you wish flush 	*/
/* to act as before v6,10A						*/
/* #define ctPREV_610A_FLUSH 						*/

/* Bill removed this define 11/2002. */
#ifdef	BILL_TOOK_OUT_FPUTFGET	/* FPUTFGET must flush each time it extends */
#define ctPREV_610A_FLUSH
#endif

/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* A new locking strategy for superfile inewvrec calls on behalf of a	*/
/* variable length datafile member has been implemented to avoid	*/
/* deadlocks with newnod81 calls for the space management index of the	*/
/* same variable length data file.					*/
/*									*/
/* By default, this define is off. To return to the orignal oder of	*/
/* locking strategy, turn on ctPREV_812A_HOSTLOCK.			*/
/* #define ctPREV_812A_HOSTLOCK						*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* forcel() now explicitly checks for TRNLOG vs PREIMG file attribute	*/
/* to avoid superfluous log entries for PREIMG files. To return to the	*/
/* previous code, turn on ctPREV_FORCEL_PREIMG.				*/
/*									*/
/* By default, this define is off.					*/
/* #define ctPREV_FORCEL_PREIMG						*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* With ctPREV_FORCEL_PREIMG off, forcel() now explicitly checks for	*/
/* TRNLOG vs PREIMG file attribute unless ctDD_PRE has been turned on	*/
/* for the file during a PREIMAGE_DUMP. To ignore the ctDD_PRE attribute*/
/* in forcel(), turn on	ctPREV_FORCEL_PREIMG2				*/
/*									*/
/* By default, this define is off.					*/
/* #define ctPREV_FORCEL_PREIMG2					*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* The wrthdr that occurs during an open when the file mode changes now	*/
/* uses a header lock to ensure a clean update under FPUTFGET.		*/
/*									*/
/* By default, this define is off.					*/
/* #define ctPREV_FPGHDRLOK						*/
/*----------------------------------------------------------------------*/


/*----------------------------------------------------------------------*/
/* Error handling during iclsfilx is problematic since we are trying	*/
/* to clean-up the file images and system resources. When ctPREV_CLSERR	*/
/* is defined, we proceed as before. Without this define, we attempt	*/
/* to clean-up the resources as well as possible (no premature returns) */
/* and mark the file as corrupt (if possible).				*/
/*									*/
/* By default this define is off for MULTITRD and on otherwise. (The	*/
/* non-MULTITRD code is essentially unaffected by the code changes to	*/
/* improve behavior on an error during file close.)			*/
/*----------------------------------------------------------------------*/
#ifndef MULTITRD
#ifndef ctPREV_CLSERR
#define ctPREV_CLSERR
#endif
#endif


/*----------------------------------------------------------------------*/
/* terr(206) signals an unexpected inconsistency between an index	*/
/* buffer and the file header during file close: the index buffer has	*/
/* its update flag set, but the file header does not.			*/
/*									*/
/* The code has been modified to continue the file close under this	*/
/* circumstance, but mark the file as corrupted. No terr(206) occurs.	*/
/* To revert to the terr(206) behavior, add ctPREV_CLS206.		*/
/*									*/
/* By default this define is off.					*/
/*----------------------------------------------------------------------*/
/* #define ctPREV_CLS206 */


/*----------------------------------------------------------------------*/
/* The interaction between UPDCIDX and PRMIIDX and ctDROPIDX showed	*/
/* problems the manner in which relative key information was maintained.*/
/* Changes designed to correct and enable more flexible use of UPDCIDX	*/
/* have been implemented, but may be undone by turning on this define.	*/
/*									*/
/* By default this define is off.					*/
/*----------------------------------------------------------------------*/
/* #define ctPREV_CIDXDROP */


/*----------------------------------------------------------------------*/
/* When CTFLUSH/CTFLUSHX are used to flush all open files, the open-	*/
/* close mutex was held as ctsave was called for all open files. This	*/
/* approach has been changed so the mutex is only held to test for the	*/
/* status of the file. To restore the old approach of holding the mutex	*/
/* for the entire set of ctsave calls, add this define.			*/
/*									*/
/* By default this define is off.					*/
/*----------------------------------------------------------------------*/
/* #define ctPREV_FLSHSAVE */


/*----------------------------------------------------------------------*/
/* Turn on ctPREV_ABLISTCLEAN to disable the cleanup of orphaned abort	*/
/* node list entries detected when a FCB is being reused after a file	*/
/* close in a subsequent open or create.				*/
/*									*/
/* By default this define is off.					*/
/*----------------------------------------------------------------------*/
/* #define ctPREV_ABLISTCLEAN */


/*----------------------------------------------------------------------*/
/* Turn on ctPREV_THDRFrunlength to disable the periodic release of the	*/
/* file header mutex ctnum->thdrf during file flush. With or without	*/
/* this define, this mutex is periodically released when an updated	*/
/* buffer/cache page is detected. But if a large number of non-updated	*/
/* pages are encountered, this mutex will be held if this define is	*/
/* turned on at compile time.						*/
/*									*/
/* By default this define is off.					*/
/*----------------------------------------------------------------------*/
/* #define ctPREV_THDRFrunlength */


/*----------------------------------------------------------------------*/
/* Turn on ctPREV_OPS_lockon to cause a SETOPS request to cancel a	*/
/* lockon type to cancel all lockon types. Without this define, the	*/
/* particular lockon type passed to the SETOPS call is turned off.	*/
/*									*/
/* By default this define is off.					*/
/*----------------------------------------------------------------------*/
/* #define ctPREV_OPS_lockon */


/*----------------------------------------------------------------------*/
/* Turn on ctPREV_CHARSEG to cause SCHSEG to assign a key segment type	*/
/* of REGSEG to a field type of CT_CHAR. Without this define, a CT_CHAR	*/
/* field is mapped into a key segment of type SGNSEG, so that the one-	*/
/* byte field is treated as a signed quantity. [The CT_CHARU is always	*/
/* treated as an unsigned byte.]					*/
/*									*/
/* By default this define is off.					*/
/*----------------------------------------------------------------------*/
/* #define ctPREV_CHARSEG */


/*----------------------------------------------------------------------*/
/* Turn on ctPREV_VCLS_ERR to revert to code that does not explicitly	*/
/* return an error code specifying that a call to vtclose has failed.	*/
/*									*/
/* By default this define is off.					*/
/*----------------------------------------------------------------------*/
/* #define ctPREV_VCLS_ERR */


/*--------------------------------------------------------------*/
/* ctPREV_ADDRECrelm permits the effects of BUG#0659 fix to	*/
/* be removed: ADDREC/RWTREC operations affect the low level	*/
/* current node information. By adding this define, ADDREC and  */
/* RWTREC operations will not affect low level current node info*/
/* and will therefore not intefere with calls to NXTKEY and	*/
/* PRVKEY. But ADDREC/RWTREC operations followed by NXTREC or	*/
/* PRVREC operations will not give the expected results when	*/
/* this	define is turned on.					*/
/*								*/
/* DEFAULT:  ctPREV_ADDRECrelm is off by default 		*/
/*--------------------------------------------------------------*/
/* #define ctPREV_ADDRECrelm */


/*--------------------------------------------------------------*/
/* ctPREV_REWRITE_KEY_ERROR permits a failed key assembly to be	*/
/* treated as a missing key instead of an error.		*/
/*								*/
/* DEFAULT:  ctPREV_REWRITE_KEY_ERROR is off by default 	*/
/*--------------------------------------------------------------*/
/* #define ctPREV_REWRITE_KEY_ERROR */


/*--------------------------------------------------------------*/
/* ctPREV_ctNOEXCL_FILELOCK maintains the code to acquire a	*/
/* file lock in FPUTFGET mode when exclusive file opens are	*/
/* not supported (i.e., on Unix systems when ctLOCK_EXCLUSIVE	*/
/* is NOT defined and ctNOEXCL IS defined).			*/
/*								*/
/* DEFAULT:  ctPREV_ctNOEXCL_FILELOCK is off by default 	*/
/*--------------------------------------------------------------*/
/* #define ctPREV_ctNOEXCL_FILELOCK */


/*--------------------------------------------------------------*/
/* ctPREV_STATUSLOG_FAIL_EXIT maintains the behavior of the	*/
/* c-tree status log write function exiting the process if	*/
/* the status log cannot be opened.				*/
/*								*/
/* DEFAULT:  ctPREV_STATUSLOG_FAIL_EXIT is off by default 	*/
/*--------------------------------------------------------------*/
/* #define ctPREV_STATUSLOG_FAIL_EXIT */


/*--------------------------------------------------------------*/
/* ctPREV_ctloghwrd eliminates the check for a deferred OPNTRAN	*/
/* if loghnd is found to be zero for a ctLOGFIL.		*/
/*								*/
/* DEFAULT:  ctPREV_ctloghwrd is off by default 		*/
/*--------------------------------------------------------------*/
/* #define ctPREV_ctloghwrd */

/*--------------------------------------------------------------*/
/* ctPREV_DFRIDX_OPNIFIL_OCSEMA restores the acquisition of the	*/
/* file open/close mutex in OPNIFILz() for the deferred index	*/
/* feature. We only expect to turn on this macro for testing or	*/
/* diagnostic purposes, in case we encounter problems with our	*/
/* new approach.						*/
/*								*/
/* DEFAULT:  ctPREV_DFRIDX_OPNIFIL_OCSEMA is off by default 	*/
/*--------------------------------------------------------------*/
/* #define ctPREV_DFRIDX_OPNIFIL_OCSEMA */

/* END PREVIOUS CODE Options */
/**********************************************/

/**********************************************/
/* DEBUG Options */

/*--------------------------------------------------------------*/
/* ctWATCH_THRD_START_STOP activates logic to call the 		*/
/* ctWatchThrdStartStop function at three locations: 		*/
/* 1) After successfull cttcre call (thread launched).		*/
/* 2) AT top of launched function (thread began to execute). 	*/
/* 3) From ctehdthread (thread ended). 				*/
/* The ctWatchThrdStartStop function records these events and 	*/
/* also provides a mode to display current thread activity.	*/
/*--------------------------------------------------------------*/
/* #define ctWATCH_THRD_START_STOP */

/*----------------------------------------------------------------------*/
/* CT_DIAGNOSE_LOGON_COMM activates client side debug output		*/
/* similar to the server's DIAGNOSTICS LOGON_COMM keyword.		*/
/* It provides communications info during the initial login process.	*/
/*----------------------------------------------------------------------*/
/* #define CT_DIAGNOSE_LOGON_COMM */

/*----------------------------------------------------------------------*/
/* DBGmemleak activates debug output of memory alloc's and free's	*/
/*----------------------------------------------------------------------*/
/* #define DBGmemleak */

#ifndef ctMEMLEAKfilnam
#define ctMEMLEAKfilnam		"MEMLEAK.FCS"
#endif

/*----------------------------------------------------------------------*/
/* DBGhash activates debug output of hash bin efficiency		*/
/*----------------------------------------------------------------------*/
/* #define DBGhash */


/*----------------------------------------------------------------------*/
/* DBGfrceword permits ctHUGEFILE to be tested with regular size files.	*/
/* Only the lower order 16 bits of each 4-byte file address word are	*/
/* used. For actual I/O, these are combined to create an actual 32-bit	*/
/* file position. DBGfrceword must be turned off if HUGE files are not	*/
/* supported.								*/
/*----------------------------------------------------------------------*/
/* #define DBGfrceword */
#ifdef DBGfrceword
#ifndef ctHUGEFILE
#undef DBGfrceword
#endif
#endif

/* END DEBUG Options */
/**********************************************/

#define ctFeatADAPTIVE_SPLIT

#ifdef MULTITRD
#ifdef ctBEHAV_freopen
#ifdef ctBEHAV_StatusOpen
#define ctBEHAV_StatusOpenHYS	/* keep open even with freopen */
#else
#define ctBEHAV_StatusOpen
#endif
#endif /* ctBEHAV_freopen */
#else  /* ~MULTITRD */
#ifdef ctBEHAV_freopen
#undef ctBEHAV_freopen
#endif
#endif /* ~MULTITRD */

/*
ctTPND_ERR_RETRY: permit compile-time control for automatic retry of
key updates with TPND_ERR. The value is the number of retrys to
attempt before returning the TPND_ERR. Suggested values for this
value are between three and ten. The retry logic only applies to the
server, and a ten millisecond delay is introduced before each retry.
*/
#define ctTPND_ERR_RETRY 6

/*
ctMAXZ_ERR_RETRY: permit compile-time control for automatic retry of
index extension with MAXZ_ERR. The value is the number of retrys to
attempt before returning the MAXZ_ERR. Suggested values for this
value are 1. The retry logic only applies to memory files with the server.
*/
#ifdef ctFeatDELETE_NODE_THRD
#define ctMAXZ_ERR_RETRY 1
#endif

#ifndef NO_ctLOG_IDX
#define ctLOG_IDX   	/* enables high speed index recovery file mode option */
#endif
#define ctDBEGFLSH	/* enables deferred begin tran flushing */


/*~***********************************/
#ifdef ctPortAUTOSOFT
#define ctSYNC_DELAY
#endif
/*^***********************************/


/*~***********************************/
#ifdef ctPortAFTI
#ifdef ctBNDSRVR
#define ctPortAFTI_BNDSRVR
#define ctFeatCLRCHK
#endif
#endif
/*^***********************************/


/*~***********************************/
#ifdef ctPortREALIA

#ifndef ctCLIENT
#ifndef ctSRVR
#define ctPortREALIA_STD 	/* Realia, standalone mode */
#ifdef ctBEHAV_WRTMRK
#undef ctBEHAV_WRTMRK		/*ca is dependent on header size */
#endif
#endif
#endif

#endif /* ctPortREALIA */
/*^***********************************/

/*~***********************************/
#ifdef ctPortMSIGA

#ifdef  FPUTFGET
#ifdef  ctPortUNIX
#ifndef ctLOCK_EXCLUSIVE
#define ctLOCK_EXCLUSIVE	/* support exclusive file locks under Unix */
#endif
#endif
#endif

#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */

#ifndef ctFeatABL
#define ctFeatABL
#endif

/***************************************/
#ifdef ctPortWINCE_SRVR /* Do not change settings for WinCE */

#ifdef ctSRVR
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#else  /* ~ctPortWINCE_SRVR */

#ifdef ctSRVR /* c-tree Server settings */

#define ctFEAT_OEM_CUSTOM_HANDSHAKE /* Activate Custom OEM Handshake */
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#define ctFeatRECRLOCK /* support recursive record locks */
#define ctFeatFILMTX   /* support file-based mutex */
#define ctFeatSEQNUM   /* support sequence number API */

#define ctFeatUSER_SIGNAL_READY
#define ctFeatUSER_SIGNAL_DOWN
/* #define ctFeatLANGUAGE */
#define ctFeatIMPERSONATEtask
/* #define ctFeatCONNGROUP */ /* Commented out on 100711 */

#ifdef ctFeatDAR
#define ctFeatRESERVE_RESPOS
/* Indicate that we turned on ctFeatRESERVE_RESPOS in ctopt2.h: */
#define ctFeatRESERVE_RESPOSctopt2
#endif

#endif /* end c-tree Server settings */

/*
** Increase the connection limit for both c-tree Server and for internal
** utility compilation.
*/
#if (defined(ctSRVR) || defined(ctPortFAIRCOM_INTERNAL_GEN))
#undef ctMAXUSERS
#if (defined(ctPortW64_ITANIUM_AMD) || defined(ctPortLINUX_64) || defined(ctPortRS6000_64) || defined(ctPortHP9000_64) || defined(ctPortMACOSX_64) || defined(ctPortSOLARIS_64))
#define ctMAXUSERS 15360
#else
#define ctMAXUSERS 4096
#endif
#endif
#ifdef ctPortFAIRCOM_INTERNAL_GEN
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#ifndef ctMAX_KEY_SEG
#define ctMAX_KEY_SEG 32
#endif

#undef	ctMAXFIL
#define ctMAXFIL 8192

#define ctFeatEXIT_CALLBACK

#endif /* ~ctPortWINCE_SRVR */
/***************************************/
#endif /* ctPortMSIGA */
/*^***********************************/

/*^***********************************/
#ifdef ctPortEPSILON
#ifndef NO_ctFeatIMPERSONATEtask
#ifdef ctSRVR
#ifndef ctFeatIMPERSONATEtask
#define ctFeatIMPERSONATEtask
#endif
#endif
#endif
#endif /*ctPortEPSILON*/
/*~***********************************/


/*^***********************************/
#ifdef ctPortWINCE_SRVR
#ifdef ctSRVR

#ifdef  ctMAXFIL
#undef	ctMAXFIL
#endif
#define ctMAXFIL 	512

#ifdef  ctMAXUSERS
#undef	ctMAXUSERS
#endif
#define ctMAXUSERS 	32

#endif	/* ctSRVR */
#endif 	/* ctPortWINCE_SRVR */
/*~***********************************/

/*^***********************************/
#ifdef ctPortOPIN
#define ctMAXUSERS 3000
#endif
/*~***********************************/


/*^***********************************/
#ifdef ctPortAMICUS
#ifdef  FPUTFGET
#define CTSUPER_noMBRLOCK	/* No superfile members exclusive	*/
#endif				/* OPNISAMX performance on NT 		*/
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortCTB
#ifdef ctSRVR
#ifndef ctCUSTOM
#define ctCUSTOM
#endif
#ifndef CTFILE_HAS_UsrData
#define CTFILE_HAS_UsrData
#endif
#endif
#endif /* ctPortCTB */
/*~***********************************/

/*^***********************************/
#ifdef 	ctPortGILBARCO
/* rab - 100208 - merged in Paolo's OEM from GILBARCO area and these were only set in StandAlone mode */
#if (!defined(ctSRVR) && !defined(ctBNDSRVR) && !defined(ctCLIENT) && !defined(ctMTCLIENT))
#define ctFeatREPLICAT
#ifndef FPUTFGET
#define ctMIRROR
#endif
#define ctCAMO
#define ctCAMOSYS
#define ctCAMOSTANDALONE	/* Support ctCAMO in StandAlone Mode */
#undef 	ctCAMOblk
#undef	ctCAMOsdk		/*  No advanced encryption support */
#define NO_ctCAMOsdk
#endif
#endif /* ctPortGILBARCO */
/*~***********************************/

/*^***********************************/
#ifdef 	ctPortSTI

#ifdef ctSRVR
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#ifdef ctPortFAIRCOM_INTERNAL_GEN
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#endif /* ctPortSTI */
/*~***********************************/

/*^***********************************/
#ifdef 	ctPortCITIBANK_POOLE

#ifdef ctSRVR
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#ifdef ctPortFAIRCOM_INTERNAL_GEN
#define ctFeatSETTINGS /* ctsrvr.set file support mandatory */
#endif

#ifdef ctCLIENT
#ifndef ctCAMO
#define ctCAMO	/* File Encryption */
#endif
#endif

#ifdef ctMTCLIENT
#ifndef ctCAMO
#define ctCAMO	/* File Encryption */
#endif
#endif

#define ctTRIPLE_DES
	/*
	ctTRIPLE_DES -	FEA#0116: security info in FAIRCOM.FCS
			can use triple DES encoding.
	*/

#define ctFeatNLMLongFileNames /* Support Long File Name with NLM */

#endif /* ctPortCITIBANK_POOLE */
/*~***********************************/

/*^***********************************/
#ifdef 	ctPortGEOQUEST
#ifdef ctSRVR

#ifndef ctFeatOS_SECURITY	/* Operating System Security 	*/
/* #define ctFeatOS_SECURITY */ /* GEOQUEST NOT USING NOW */
#endif

#ifndef CT_V7		/* Use older Port ID for V6 only. */
#define ctPREV_69A2	/* Because of older Port ID insockets ctnlib */
#endif

#endif	/* ctSRVR */
#endif	/* ctPortGEOQUEST */
/*~***********************************/


/*^***********************************/
#ifdef ctPortQUEST
#ifdef ctMAXFIL
#undef ctMAXFIL
#endif
#define ctMAXFIL 32000

#define MAX_HANDLES 255
#endif
/*~***********************************/


/*^***********************************/
#ifdef 	ctPortATTACHE

#ifdef ctSRVR
#ifndef ctPortCHE
#define ctPortCHE
#endif
/* Support file open/create/close callback functions. */
#define ctFeatFILE_OPEN_CALLBACK
#endif

#ifdef ctCLIENT
#ifndef ctCAMO
#define ctCAMO	/* File Encryption */
#endif
#endif

#ifdef ctMTCLIENT
#ifndef ctCAMO
#define ctCAMO	/* File Encryption */
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

#endif /* ctPortATTACHE */
/*~***********************************/

#ifdef  ctPortCHE
#ifndef CTFILE_HAS_UsrData
#define CTFILE_HAS_UsrData
#endif
#endif	/* ctPortCHE */

/*^***********************************/
#ifdef ctPortBOM

#define ctFeatZERO_RECBYT_OK
#define ctFeatMULTITHRDINIT

#ifdef  ctBNDSRVR
#ifndef ctHUGEFILE
#define ctHUGEFILE
#endif
#ifndef ctHUGEFILEsegm
#define ctHUGEFILEsegm
#endif
#define ctCAMO
#define ctCAMOsys
#endif

#endif /* ctPortBOM */
/*~***********************************/

/*^***********************************/
#ifdef ctPortMETODO_PAOLO_REMOVED_121214
/* #define ctBEHAV_STRICTOEM_LOGONu */	/* strict OEM LOGONs */

#ifdef ctSRVR
/*
** Support NewLogon() calling NewUser() to accept a connection
** when the NewUser() thread create attempt fails.
*/
#define ctFeatINLINE_LOGON

/*
** On Linux, support client authentication using LDAP.
** Removed per Marco 060626
*/
#ifdef ctPortLINUX
/* #define ctFeatOS_SECURITY_LDAP  */
#endif

#endif /* ctSRVR */

#endif /* ctPortMETODO */
/*~***********************************/


/*^***********************************/
#ifdef ctPortUPS_BRUCE
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif /* ctPortUPS_BRUCE */
/*~***********************************/

/*^***********************************/
#ifdef ctPortTDSRX30
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#ifdef ctSRVR
#define ctFeatSETTINGS 			/* ctsrvr.set file support mandatory */
#endif
#ifdef ctPortFAIRCOM_INTERNAL_GEN
#define ctFeatSETTINGS 			/* ctsrvr.set file support mandatory */
#endif
#endif /* ctPortTDSRX30 */
/*~***********************************/


/*^***********************************/
#ifdef ctPortAPPMAT
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif /* ctPortAPPMAT */
/*~***********************************/

/*^***********************************/
#ifdef ctPortADVENT
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif /* ctPortADVENT */
/*~***********************************/


/*^***********************************/
#ifdef ctPortBRACOBOL
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#ifndef ctCobolIS
#ifndef ctCobolEXTFH
#ifndef ctCobolACU
#error ctPortACECOBOL requires ctCobolEXTFH or ctCobolACU or ctCobolIS
#endif
#endif
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortMICROFOCUS
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#ifndef ctCobolIS
#ifndef ctCobolEXTFH
#ifndef ctCobolACU
#error ctPortACECOBOL requires ctCobolEXTFH or ctCobolACU or ctCobolIS
#endif
#endif
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortCOBOLIT
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#ifndef ctCobolIS
#ifndef ctCobolEXTFH
#ifndef ctCobolACU
#error ctPortACECOBOL requires ctCobolEXTFH or ctCobolACU or ctCobolIS
#endif
#endif
#endif
#endif
/*~***********************************/

/*^***********************************/
#ifdef ctPortCHARGER1
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif /* ctPortCHARGER1 */
/*~***********************************/

/*^***********************************/
#ifdef ctPortATTACH2
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#ifdef ctFeatLOGONSEC
#define ctBEHAV_STRICTOEM_LOGONu_CS_VERSION_CHECK 	/* strict Product Version Number Check */
#endif /* ctFeatLOGONSEC */
#endif /* ctPortATTACH2 */
/*~***********************************/


/*^***********************************/
#ifdef ctPortACECOBOL
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#ifndef ctCobolIS
#ifndef ctCobolEXTFH
#ifndef ctCobolACU
#error ctPortACECOBOL requires ctCobolEXTFH or ctCobolACU or ctCobolIS
#endif
#endif
#endif
#endif /* ctPortACECOBOL */
/*~***********************************/

/*^***********************************/
#ifdef ctPortABACUS
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#ifndef ctPortWINIOT
#define ctMAXUSERS 30000
#ifndef CTBOUND
#ifndef ctSRVR
#ifndef NO_ctBEHAV_CHECK_ADVENC_PASSWD
#ifndef ctBEHAV_CHECK_ADVENC_PASSWD 
#define ctBEHAV_CHECK_ADVENC_PASSWD /* turn on master key password checking for client utilities supporting it*/
#endif
#endif
#endif
#endif
#endif
#endif /* ctPortABACUS */
/*~***********************************/

/*^***********************************/
#ifdef ctPortACE_EXPRESS_HANDSHAKE_V9_0_0
#ifndef ctBEHAV_STRICTOEM_LOGONu
#define ctBEHAV_STRICTOEM_LOGONu	/* strict OEM LOGONs */
#endif
#endif /* ctPortACE_EXPRESS_HANDSHAKE_V9_0_0 */
/*~***********************************/

/* ctSIBLING_HANDSHAKE_007 */
/* ctSIBLING_HANDSHAKE: Add special setting for server, including ctBEHAV_STRICTOEM_LOGONu */


/*^***********************************/
#ifdef ctPortBEGO
#define ALT_KEY_LENGTH		13
#define PUNC_STRIP_LENGTH	34
#endif /* ctPortBEGO */

/* generic high speed key compare    */
#ifdef ctPortBEGO
#define comparf		compar
#else  /* ~ctPortBEGO */
#ifdef ctNOMEMCMP
#define comparf		compar
#else
#define comparf(a,b,k)	ctrt_memcmp(a,b,(NINT) ((k)->length))
#endif
#endif /* ~ctPortBEGO */
/*~***********************************/

/*^***********************************/
#if (ctVER_MAJOR == 10 && ctVER_MINOR == 99)  /* Time out V11 Pre-Release on Dec 1, 2015 */
#define ctFeatL10_EXPIRE "2015.12.01"
#define ctFeatL10_EVALUATION
#endif
/*~***********************************/

/*^***********************************/
#define ctfsync ctfdatasync
/*~***********************************/


#define ctTRAP_COMM	/*
			** Add communications trapping logic at compile.
			** Will not be effective unless DIAGNOSTICS TRAP_COMM
			** is added to server configuration file.
			*/

#ifdef ctSRVR
#ifndef ctFeatCTSRVR_COMMP
#undef ctTRAP_COMM
#endif
#endif

/**************/
#ifdef MULTITRD
#ifdef CTBOUND
#define ctThrdBnd
#define ctThrds
#endif
#endif
/**************/

/**************/
#ifdef ctThrdApp
#define ctThrds

#ifndef ctNOGLOBALS
#define ctNOGLOBALS
#endif

#ifndef OWNER
#define OWNER	ctOWNER()
#define ctThrdRet
#endif

/*^*******************/
/*
** For multi-threaded client compiles, use thread-specific data to store
** c-tree task IDs on systems that support this feature.
*/
#if defined(ctMTCLIENT) || defined(ctMTFPGreentrant)
#ifdef ctThrdRet

#ifdef ctPortWIN32
#define ctFeatNATIVEtaskid
#endif

#if defined(ctPortALPHA)  || defined(ctPortHP9000) || defined(ctPortLINUX)  ||\
    defined(ctPortMACOSX) || defined(ctPortQNXRTP) || defined(ctPortRS6000) ||\
    defined(ctPortSCO5)   || defined(ctPortSGI)    || defined(ctPortSOL386) ||\
    defined(ctPortSOLARIS)

#define ctFeatNATIVEtaskid

#ifndef ctPortSOLARIS10
/*
** Use a pthread thread-specific data key to store the c-tree task ID.
*/
#define ctFeatNATIVEtaskidpthread
#endif

#endif

#endif /* ctThrdRet */
#endif /* ctMTCLIENT */
/*~*******************/

#endif /* ctThrdApp */
/**************/
#ifdef ctThrdFPG
#define ctThrds

#ifndef ctNOGLOBALS
#define ctNOGLOBALS
#endif

#ifndef OWNER
#define OWNER	ctOWNER()
#define ctThrdRet
#endif

#endif /* ctThrdFPG */
/**************/

/**************/
#ifdef MULTITRD
#ifndef CTBOUND
#ifndef ctSRVR
#define ctSRVR
#endif
#endif
#define QPWD	"rq"
#endif
/**************/

/**************/
#ifndef ctSRVR
#ifdef ctDBGfhLIMIT
#undef ctDBGfhLIMIT	/* requires server support */
#endif
#endif
/**************/

#ifndef CTBOUND
#ifndef ctSRVR
#ifndef	ctCLIENT
#define ctCLIENT
#endif
#endif
#endif

#ifdef  ctCLIENT
#ifndef rtCLIENT
#define rtCLIENT /* Activate r-tree Client Support */
#endif

#ifndef NO_ctHUGEFILE
#ifndef ctHUGEFILE		/* default V7 client to HUGE support */
#define ctHUGEFILE
#endif

#ifndef ctHUGEFILEsegm
#define ctHUGEFILEsegm
#endif
#endif /* ~NO_ctHUGEFILE */

#endif	/* ctCLIENT */

/*
** server security options
*/

#ifdef ctFeatOS_SECURITY
#undef ctFeatOS_SECURITY
#endif

#ifdef ctSRVR
#ifdef ctFeatOS_SECURITY_UNIX
#ifdef ctFeatOS_SECURITY_LDAP

#error Only one alternative security model can be implemented

#endif
#endif

#ifdef ctFeatOS_SECURITY_UNIX
#define ctFeatOS_SECURITY
#endif

#ifdef ctFeatOS_SECURITY_LDAP
#define ctFeatOS_SECURITY
#endif

#endif /* ctSRVR */


/*
** ensure that generic extended key support is turned on
** if one or more components are turned on
*/
#ifndef ctXTDKEYSEG
#define ctXTDKEYSEG
#endif

#ifndef ctSRVR
#ifdef ctSYNC_DELAY
#undef ctSYNC_DELAY
#endif
#endif

#ifdef ctMULTIPLE_CTREE_DLLs
#ifdef ctPORTAUTOWIN
#undef ctPORTAUTOWIN /* no support for AUTOWIN if ctMULTIPLE_CTREE_DLLs */
#endif
#endif

#ifdef ctPORTAUTOWIN
#ifndef ctPREFNC
#define ctPREFNC	ct_win_inst
#endif
#define ctAutoID	GetCurrentTask()
#define ctAutoInst
#else /* ctPORTAUTOWIN */
#ifdef ctThrdFPG
#ifndef ctPREFNC
#define ctPREFNC	ctserl
#endif
#ifndef ctPOSTFNC
#define ctPOSTFNC	ctunserl
#endif
#ifdef ctThrdRet
#define ctAutoID	ctThrdID()
#else
#define ctAutoID	OWNER
#endif
#define ctAutoInst
#endif /* ctThrdFPG */
#endif /* ctPORTAUTOWIN */

/*
** ctPREFNC => calling the function ctPREFNC before each c-tree
** function
**
** ctFRCSNG => force single entry point calls
*/

/*
** PREFNC requires either LOCLIB or FRCSNG or CLIENT. If none, select FRCSNG.
*/
#ifdef ctPREFNC
#ifndef ctLOCLIB
#ifndef ctCLIENT
#ifndef ctFRCSNG
#define ctFRCSNG
#endif
#endif
#endif
#endif

/*
** You cannot configure both LOCLIB and FRCSNG. If so, only select LOCLIB.
*/
#ifdef ctLOCLIB
#ifdef ctFRCSNG
#undef ctFRCSNG
#endif
#endif

/*
** FRCSNG uses LOCLIB features, so c-tree must turn on LOCLIB if you select
** FRCSNG. This is not inconsistent with preceding undef since from this point
** forward, ctFRCSNG and ctLOCLIB both being defined is interpreted as
** forcing a single entry point without an actual LOCLIB implementation.
*/
#ifdef ctFRCSNG
#define ctLOCLIB
#endif

#if defined(ctFRCSNG) && defined(FPUTFGET) && !defined(ctLOCSIDE)

/* FPUTFGET with single-entry point c-tree function calls */
#define ctFRCSNG_FPUTFGET

#ifndef ctPREFNC
#define ctPREFNC myprefunc
#ifdef PROTOTYPE
extern NINT myprefunc(NINT fn);
#else
extern NINT myprefunc();
#endif
#endif

#ifndef ctPOSTFNC
#define ctPOSTFNC mypostfunc
#ifdef PROTOTYPE
extern NINT mypostfunc(NINT fn);
#else
extern NINT mypostfunc();
#endif
#endif

#endif /* ctFRCSNG && FPUTFGET && !ctLOCSIDE */

/*^***********************************/
/* Here we activate 4GB support (v6:not HUGE) for various platforms */
#ifndef ctHUGEFILE
#ifndef NO_LARGE_FILES

#ifdef  ctPortDGU386
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif

#ifdef  ctPortNETBSD386
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif

#ifdef  ctPortSOLARIS
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif

#ifdef  ctPortSOL386_LARGE_FILES
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif

#ifdef  ctPortHPUX11
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif

#ifdef  ctPortRS6000
#ifndef ctPortRS6_SYSV_REL_3
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif
#endif

#ifdef ctPortALPHA
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif

#endif /* ~NO_LARGE_FILES */
#endif /* ~ctHUGEFILE */
/*~***********************************/

/**********************************************/
/* Huge File Support */

/*----------------------------------------------------------------------*/
/* ctHUGEFILE enables support for data and/or index files which use	*/
/* upto 8 bytes tp specify a file position.				*/
/* ctHUGEFILEsign is a 4-byte mirror image value used as an extended	*/
/* header signature to verify extended headers				*/
/*----------------------------------------------------------------------*/
#define ctHUGEFILEsign	0x36353536

/*----------------------------------------------------------------------*/
/* ctHUGEFILEsegm allows a logical file to be spread over multiple	*/
/* segments. The simple case is based on fixed segment sizes and a	*/
/* straightforward file naming (numbering) convention. The flexible	*/
/* case uses a resource to store the logical-to-physical mapping rules.	*/
/*----------------------------------------------------------------------*/
#ifdef  ctHUGEFILEsegm
#ifndef ctHUGEFILE
#define ctHUGEFILE
#endif
#endif /* ctHUGEFILEsegm */

#ifdef  ctHUGEFILE
#ifndef NO_ctHUGEFILEsegm
#ifndef ctHUGEFILEsegm
#define ctHUGEFILEsegm
#endif
#endif
#endif /* ctHUGEFILE */

#ifdef ctHUGEFILE
#define ABTint4
#ifdef ctEVALUATION
#ifndef ctCLIENT
	** cannot compile an evaluation server with HUGEFILE support **
#endif
#endif
#endif /* ctHUGEFILE */

/*^***********************************/
#ifdef ctHUGEFILE
#ifndef NO_ctRECBYTIDX
#define ctRECBYTIDX		/* enable space reclaim and backward traverse */
#endif
#ifndef ctCOALdirect
#define ctCOALdirect	8	/* max number of in-line reclaims	      */
#endif
#ifndef ctCOALqueue
#define ctCOALqueue	64	/* max number of queued reclaims	      */
#endif
#ifndef ctCOALprmlmt
#define ctCOALprmlmt	32	/* skip permanent queue (but still queue real */
				/* time) if permanent queue count is less     */
				/* than this limit (i.e., small)	      */
				/* -1 implies to always use permanent queue   */
#endif
#endif /* ctHUGEFILE */
/*~***********************************/


/*^***********************************/
#ifdef ctHUGEFILE

#ifndef ctFeat_LARGE_FILES
#ifndef ctPortLINUX
#define ctFeat_LARGE_FILES	/* system defines for Unix-Solaris, AIX */
#endif
#endif

#ifdef ctLINUX_LARGE_FILES
#ifndef ctFeat_LARGE_FILES
#define ctFeat_LARGE_FILES
#endif
#endif

#endif
/*~***********************************/

/*----------------------------------------------------------------------*/
/* ctHUGEFILEint8 indicates that the environment supports 8-byte	*/
/* integers to use for file positions.					*/
/*----------------------------------------------------------------------*/

/*^***********************************/
#ifdef ctXTDLOG

#ifndef ct_V90_GENERATION

**** cannot compile replication or extended log support without
**** ct_V90_GENERATION

#endif

#undef ctXTDLOG
#endif

#ifdef ctCMPLOG

#ifndef ct_V90_GENERATION

**** cannot compile log compression support without
**** ct_V90_GENERATION

#endif

#endif

#ifdef ctREPLICATION
#undef ctREPLICATION
#endif

#ifdef ctHUGEFILE
#ifdef TRANPROC

#ifdef ct_V90_GENERATION

#ifndef NO_ctXTDLOG
#define ctXTDLOG		/* extended log support			*/
#ifndef ctXTDLOGmxusrlog	/* default user log entry length limit	*/
#define ctXTDLOGmxusrlog	16384
#endif
#endif

#ifndef NO_ctSUCTRAN
#ifndef ctSUCTRAN
#define ctSUCTRAN
#endif
#endif

#ifdef ctXTDLOG
#ifndef NO_ctREPLICATION
#ifndef NO_ctFeatREPLICAT
#ifndef ctREPLICATION
#define ctREPLICATION		/* file replication support		*/
#endif
#endif
#endif
#endif

#endif /* ct_V90_GENERATION */

/*
** Check ctFeatDAR requirements:
*/
#if defined(ctFeatDAR) && !(defined(ctHUGEFILE) && (defined(ctXTDLOG) || !defined(TRANPROC)))

/* If we turned on ctFeatDAR in ctopt2.h, turn it off. */
#ifdef ctFeatDARctopt2
#undef ctFeatDAR
#undef ctFeatSUBST_IDENTITY
#else

/* Other code turned on ctFeatDAR: ERROR */
#ifdef TRANPROC
#error ctFeatDAR requires huge file support and extended log support
#else
#error ctFeatDAR requires huge file support
#endif

#endif

#endif

/*
** Check ctFeatRESERVE_RESPOS requirements:
*/
#if defined(ctFeatRESERVE_RESPOS) && !defined(ctFeatDAR)

/* If we turned on ctFeatRESERVE_RESPOS in ctopt2.h, turn it off. */
#ifdef ctFeatRESERVE_RESPOSctopt2
#undef ctFeatRESERVE_RESPOS
#else
/* Other code turned on ctFeatRESERVE_RESPOS: ERROR */
#error ctFeatRESERVE_RESPOS requires DAR support
#endif

#endif

/*
** Check ctBEHAV_EOR_CLSTRAN requirements:
*/
#if defined(ctBEHAV_EOR_CLSTRAN) && !defined(ctXTDLOG)

/* If we turned on ctBEHAV_EOR_CLSTRAN in ctopt2.h, turn it off. */
#ifdef ctBEHAV_EOR_CLSTRANctopt2
#undef ctBEHAV_EOR_CLSTRANctopt2
#undef ctBEHAV_EOR_CLSTRAN
#else
/* Other code turned on ctBEHAV_EOR_CLSTRAN: ERROR */
#error ctBEHAV_EOR_CLSTRAN requires extended log support
#endif

#endif

#ifndef ctBEHAV_EOR_CLSTRAN
#undef ctBEHAV_EOR_CLSTRAN2
#endif

#ifndef ctXTDLOG
#ifdef ctFeatDISTINCTkey
#undef ctFeatDISTINCTkey
#endif
#ifdef ctFeatDISTINCTkeyseg
#undef ctFeatDISTINCTkeyseg
#endif

#ifdef ctBEHAV_REPIMGRWT
#undef ctBEHAV_REPIMGRWT
#endif

#ifdef ctLOGAUG
#undef ctLOGAUG
#endif
#ifndef NO_ctLOGAUG
#define NO_ctLOGAUG
#endif

#ifdef ctBEHAV_ABNTRAN
#undef ctBEHAV_ABNTRAN
#endif
#endif /* ~ctXTDLOG */

/* Optimized commit read lock support requires extended log support. */
#ifndef ctXTDLOG
#undef ctBEHAV_CMTLOK_optimize
#undef ctBEHAV_CMTLOK_optimizeNLINK
#undef ctFeatPREIMAGE_SWAP
#undef ctPARTITIONidxent
#undef ctFeatADDUNQKEYS_FIRST
#undef ctFeatDFRIDX
#undef ctFeatFLEXREC
#undef ctFeatTRANSACTION_ID
#undef ctFeatREPLICAT
#undef ctCMPREC
#undef ctFeatHISTORY_COMBINED_IMAGE
#endif

#ifndef ctBEHAV_PUTHDRcommit
#ifdef ctFeatDISTINCTkey
#undef ctFeatDISTINCTkey
#endif
#endif

#endif /* TRANPROC */
#endif /* ctHUGEFILE */

#ifndef ctCMPREC
#undef ctBEHAV_BAT_FXDCMP
#undef ctFeatKEYCOMPRESSsRLE
#undef ctBEHAV_CMPREC_optimize
#endif

#ifndef ctFeatFLEXREC
#undef ctFeatBATCHCOLFLTR
#endif

#if !defined(ctXTDLOG) || !defined(ctREPLICATION)
#undef ctFeatREPLICAT
#undef ctFeatREPLICAT_FLEXREC
#undef ctFeatLOGREAD
#undef ctFeatREPL_BATCH
#undef ctFeatREPL_NODEID
#undef ctFeatTRANREPL
#undef ctFeatPARTREPL
#undef ctFeatREPL_FILENAME_HASH
#undef ctBEHAV_REPIMGRWT
#undef ctBEHAV_REPLPOS
#undef ctFeatREPL_IDENTITY
#undef ctFeatREPLmultipos
#undef ctFeatREPLICAT_SYNC
#undef ctFeatREPLICAT_SYNC2
#undef ctFeatREPLICAT_SYNC_SRVR
#undef ctFeatREPLICAT_SYNC2_SRVR
#undef ctFeatREPLAGENT_FILE_FILTER
#undef ctFeatREPLAGENT_FILE_FILTER_SRVR
#undef ctFeatREPLAGENT_FILE_FILTER_REGEX
#undef ctFeatDYNDMPrepl
#undef ctFeatREPL_FILTERfile
#undef ctFeatREPL_FILTERfileSRV
#undef ctFeatREPLICAT_QUIET
#undef ctFeatREPLAGENTstt
#undef ctFeatREPLICAT_SRVRparallel
#undef ctFeatREPLICAT_DATA_DEFINITIONS
#undef ctFeatREPLICAT_SUPERFILE
#endif

#ifdef ctFeatREPLICAT
#ifdef ctSRVR
#define ctFeatREPLICAT_SRVR
#endif
#endif

#ifdef ctREPLICATION
#ifndef ctSUCTRAN
#define ctSUCTRAN
#endif
#endif

#ifndef ctXTDLOG
#ifdef ctFeatADDKY_DEFERD
#undef ctFeatADDKY_DEFERD
#endif

#ifdef ctBEHAV_SAVPNT_NEWIMAGE
#undef ctBEHAV_SAVPNT_NEWIMAGE
#endif
#endif

/*
** When replication support is enabled, optimized commit read lock support
** requires replication rewrite record image support.
*/
#ifdef ctFeatREPLICAT
#ifdef ctBEHAV_CMTLOK_optimize
#ifndef ctBEHAV_REPIMGRWT

/* Force Compile Error: */
Optimized commit read lock support requires replication rewrite record image support.

#endif
#endif
#endif

#ifdef ctBEHAV_REPIMGRWT
#ifndef ctBEHAV_SAVPNT_NEWIMAGE

/* Force Compile Error: */
Replication rewrite record image support requires savepoint newimage support.

#endif
#endif

/*^***********************************/
#ifdef ctCMPLOG
#ifdef ctXTDLOG

#ifndef ctCMPLOGthreshold
#define ctCMPLOGthreshold	128
#endif
#ifndef ctCMPLOGfactor
#define ctCMPLOGfactor		75
#endif

#else

#undef ctCMPLOG

#endif
#endif
/*~***********************************/

/*~***********************************/

/*~***********************************/
/* END Huge File Support */
/**********************************************/


#ifdef ctPortVINES
/* added for the definintion of size_t */
#include <sys/types.h>
#endif

/*
** ct_udefer check-out parameters
*/
#define ctUDFRusec	125
#define ctUDFRiter	1024

/*
** ctMEMALIGN is a "superset" of ctMEMALIGN8. If defined it overrides
** ctMEMALIGN8. If not, and ctMEMALIGN8 is defined, then ctMEMALIGN is
** defined to be 8
*/

#ifndef ctMEMALIGN
#ifdef  ctMEMALIGN8
#define ctMEMALIGN	8
#endif
#endif

/*
** if ctMEMALIGN is defined,then memory block headers will
** be forced to defined alignment. At this time, ctMEMALIGN
** and DBG749x are incompatible.
*/
#ifdef ctMEMALIGN
#ifdef DBG749x
**** CANNOT COMPILE IN DBG749x MODE WITH FORCED ALIGNMENT ****
#endif

#define ctMEMHDR	ctMEMALIGN
#define SIZpLSTHED	ctMEMALIGN
#endif /* ctMEMALIGN */


/* ***			    Capacity Constants			    *** */

#define BFRSIZ		2048	/* default data file buffer size	*/
#define DATABUFS	100	/* default # of data buffers		*/

#define See_ctport_h_for_MAXLEN	/* MAXLEN define has been moved to ctport.h */
				/* MAXLEN is the maximum key length	*/

#ifdef ctFeatMAX_NAME_4K
#ifdef ctMULTIBYTEname
#error ctMULTIBYTEname is not supported with ctFeatMAX_NAME_4K
#endif
#define MAX_NAME 4096 /* maximum file name length */
#endif

#ifdef ctMULTIBYTEname
#ifndef MAX_NAME
#define MAX_NAME	512
#endif
#endif

#ifndef MAX_NAME
#define MAX_NAME	255	/* maximum file name length		*/
#endif
#define RESNAME_LEN	64	/* resource logical name limit		*/
#ifndef MAXVFIL
#ifdef ctSRVR
#define	MAXVFIL		-1	/* open all files as ctPERMANENT */
#else
#define	MAXVFIL		32767	/* maximum virtual files open at same time */
#endif
#endif

#define MAX_SERVER_NAME 255 /* maximum length of server name */
#define MAX_SUPERFILE_MEMBER_NAME 255 /* maximum length of superfile member name */

/* ***			Variable Length Key & Field Constants	    *** */
#ifdef ctPADDING
#define PADDING		ctPADDING /* user defined padding. See ctopt1.h */
#else
#define PADDING		' '	/* trailing key padding			*/
#endif
#ifdef ctFIELD_DELIM
#define FIELD_DELIM	ctFIELD_DELIM /* user defined field delimiter. See ctopt1.h */
#else
#define FIELD_DELIM	'\0'	/* var length field delimiter		*/
#endif

/**************************************************************************/
/* ***			CT_SRVCTL COMMAND DELIMITER		    *** */
/*
When a client side program calls CTSRVCTL(), the first parameter (ctlbufptr) is
checked to see if it begins with the CTSRVCTLJOB string. This indicates that it
is a FairCom Server internal JOB command. This technique was initially
introduced when the ctjobs subsystem was authored.
*/
#ifdef  ctFeatJOBMGTSYS /* FairCom Job Management System Subsystem */
#define CTSRVCTLJOB	"~FAIRJOB~"		/* This string sequence indicates that the CTSRVCTL() is a ctFeatJOBMGTSYS command. */
#define CTNTREEPJOBSTOP "~FAIRJOB~STOP"		/* This string sequence is used by ntree jobs to STOP the network read loop */
#endif
/**************************************************************************/

/* ***			ctSUPERFILE NAME DELIMITER		    *** */
#define CTSUPSEP	'!'


#ifdef ctPortREALIA_STD
#undef CTSUPSEP
#define CTSUPSEP	'\x1F'
#endif /* ctPortREALIA_STD */

/* ***			   MIRROR NAME DELIMITER		    *** */
#define ctMIRROR_SEPchr	'|'
#define ctMIRROR_SEPstr	"|"

/* ***			  PATH SEPARATOR DEFAULT		    *** */
#ifndef ctPATH_SEP
#define ctPATH_SEP	'?'	/* ctcmpl.h should define ctPATH_SEP	*/
#endif

/* ***			  STATUS LOG NAME		    	    *** */
#ifndef CTSTATUSname
#define CTSTATUSname	"CTSTATUS.FCS"
#endif

/* ***			TEMPORARY FILENAME EXTENSION	    	    *** */
#ifndef CT_TMPNAME_EXT
#define CT_TMPNAME_EXT NULL
#endif

#ifndef ctMAX_USR_FIL
#ifdef CTBOUND
#define ctMAX_USR_FIL	1024	/* maximum files per user		*/
#else
#define ctMAX_USR_FIL	2048	/* maximum files per user		*/
#endif
#endif

#ifdef ctSRVR
#define ctMAX_USR_FIL_SRV 32767 /* default for MAX_FILES_PER_USER option */
#endif

#ifndef ctMEMLMT
#define ctMEMLMT	0L
#endif

/*
** DQMSG dflmx bit map values
*/
#define ctDFLMXmemf	0x0001  /* memory file */
#define ctDFLMXpruneNow 0x0002  /* file prune request */
#define ctDFLMXnoDelay  0x0004  /* immediate prune */
/*
** memory file definitions
*/
#ifndef ctMEMFILEshift		/* hash bin shift factor	*/
#define ctMEMFILEshift	4
#endif

/* special MHL musr value to indicate index node */
#define ctMEMNODEmusr	0x8000

/* default maximum # of hash bins per memory file */
#define ctMEMFILEmaxbinsDEFAULT 65537

/* default maximum # of entries in SQL CCacheTable */
#define ctSQLCCacheLimitDEFAULT 60

/* default network timeout before SQL idle function call */
#define ctSQLIdleTimeoutDEFAULT 2
/*
** buffer block list mutex bins
*/
#ifndef ctBUFBLKratio
#define ctBUFBLKratio	64	/* every 64 buffer pages has a block mutex */
#endif


#define ctQHDRSIZ	(ctSIZE(NINT) + ctSIZE(pVOID) + ctSIZE(pTEXT))

/*
 * The following capacity constants are used only by the ISAM routines and
 * the REBUILD routines.
 */

#define	ctEOK		-1	/* no more keys in ct_kymap	*/
#define ctDOR		-66	/* key is dormant, pending drop	*/

#ifdef ctMAXFIL
#define MAXFIL		ctMAXFIL
#else
/* maximum number of files (non-server) - may be overridden in ctoptn.h 	*/
#ifdef ctFLEXFILE
#define MAXFIL		ctMAX_USR_FIL
#else
#define MAXFIL		255
#endif
#endif /* ~ctMAXFIL */
#ifdef MULTITRD
#define MAX_DAT_KEY	ctmaxdatkey
#define ctMAX_DAT_KEY	64	/* server default. MAX_DAT_KEY is the runtime limit */
#else
#ifdef ctMAX_DAT_KEY
#define MAX_DAT_KEY	ctMAX_DAT_KEY
#else
#define MAX_DAT_KEY	64	/* max number of indices per data file	*/
#define ctMAX_DAT_KEY	MAX_DAT_KEY
#endif
#endif

/* ************* ************* ************* ************ ************* */
#define ctHLflavor	1
#define ctLHflavor	2

#define ctBYTEORDER	0
#define ctALIGNMENT	1
#define ctPNTRSIZE	2
#define ctUNIFRMAT	3

#ifndef ctrt_bstrlen
#define ctrt_bstrlen	strlen
#endif

/* ***			MultiByte Name Special Char		    *** */
#define ctMBchr		'&'

/*
** default wide-character support functions
*/

#ifndef ctrt_wcstrlen
#ifdef ctNO_WCHAR
#define ctrt_wcstrlen	ct_ucs2strlen
#else
#define ctrt_wcstrlen	wcslen
#endif
#endif
#ifndef ctWCHARsiz
#define ctWCHARsiz	2
#endif
#ifndef ctrt_wcstrxfrm
#define ctrt_wcstrxfrm	wcsxfrm
#endif
#ifndef ctrt_wcstrcpy
#define ctrt_wcstrcpy	wcscpy
#endif
#ifndef ctrt_wcstrncpy
#define ctrt_wcstrncpy	wcsncpy
#endif

/*
** if no unaligned longs allowed, assume that
** UFT16 must be word aligned
*/
#ifdef ctNoUnalignedLongs
#define ctNoUnalignedUTF16
#endif

#ifdef ctMULTIBYTEname

/*
** ctMULTIBYTElocal controls where name conversion occurs on calls
** to open/creat/rename/delete files. When not defined, it is assumed
** that names have been converted (to UTF8) before calling API
** routines
*/
#ifdef CTBOUND
#define ctMULTIBYTElocal
#endif

/*
** redefinition of ctrt_fopen to handle ctMULTIBYTEname support
*/

#ifdef ctrt_fopen

#ifdef ctCLB3C
/* include in-line source for ctMBfopen() when ctclb3.c is compiled */
#include "ctmbfo.c"
#else
extern pFILE ctMBfopen(pTEXT fn,pTEXT mode);
#endif

#undef  ctrt_fopen
#define ctrt_fopen	ctMBfopen

#endif /* ctrt_fopen */
/*
** if ctrt_fopen is NOT defined, then must code ctMULTIBYTEname support
** in the system specific ctrt_fopen code.
*/
#endif /* ctMULTIBYTEname */


/*****************************************/


#ifdef ctEVALUATION
#ifdef ctBOUND
#define ctEVALdata	130622
#define ctEVALlog	500008
#else
/* must be at least 300K to allow FAIRCOM.FCS */
#define ctEVALdata	300000
/* log limit set to (checkpoint-chunk * 3) */
#define ctEVALlog	(((LOGCHUNKN / 2) * 3) + 8)
#endif /* ~ctBOUND */
#define EVAL_ERR	   649
#ifdef ctMIRROR
#undef ctMIRROR
#endif
#endif

#ifndef ctMIRROR
#define cttrnopn	ctspcopn
#endif

#ifdef ctMIRROR
#ifdef ctMIRRORsave
#define ctsave		mbsave
#endif
#else
#define ctopen(c,m)	mbopen(c,c->flname,m)
#ifndef ctFeatMEMFILE /* Memory file support requires ctsave */
#define ctsave		mbsave
#endif
#endif

#ifdef PROTOTYPE
typedef NINT (*pctFUNC)(pVOID );
#define ctProtoVOID VOID
#else
typedef NINT (*pctFUNC)();
#define ctProtoVOID /* */
#endif


#ifdef MULTITRD
#ifndef ctSEMBLK

#ifdef ctSEMMTX
#define SEMAblk		SEMAtim
#define pSEMAblk	pSEMAtim
#define ctblkrqs	cttimrqs
#define ctblkclr	cttimclr
#define ctblkwat	cttimwat
#define ctblkcls	cttimcls
#else
#define SEMAblk		SEMA
#define pSEMAblk	pSEMA
#define ctblkrqs	ctsemrqs
#define ctblkclr	ctsemclr
#define ctblkwat	ctsemwat
#define ctblkcls	ctsemcls
#endif

#endif

#ifndef ctSEMTIM
#define SEMAtim		SEMA
#define pSEMAtim	pSEMA
#define cttimrqs	ctblkrqs
#define cttimclr	ctblkclr
#define cttimwat	ctblkwat
#define cttimcls	ctblkcls
#endif

#ifdef ctFeatRWLOCK

#ifdef ctDBG_RWLOCK
	/*
	** simulate read/write locks with ctSEMAP
	*/
#define RWLOCKmut	ctSEMAP
#define pRWLOCKmut	pctSEMAP
#ifndef RWLOCKmax
#define RWLOCKmax	8		/* max readers at one time */
#endif

#else /* ~ctDBG_RWLOCK */

	/*
	** ctRWLOCK defined in system dependent ctsthd.h
	*/
#define RWLOCKmut	ctRWLOCK
#define pRWLOCKmut	pctRWLOCK

#endif /* ~ctDBG_RWLOCK */

#define RWL(loktyp)	loktyp,
#ifdef ctPortWIN32
#define RWCA(loktyp,ownr) loktyp
#else
#define RWCA(loktyp,ownr) ownr
#endif

#define ctRWLrqs	ctrwlrqs
#define ctRWLtry	ctrwltry
#define ctRWLclr	ctrwlclr
#define ctRWLcls	ctrwlcls

#ifdef ctMTXtoWLOCK
#define ctmutrqs(p,o)	ctRWLrqs(p,CTWRITE,o)
#define ctmutclr(p,o)	ctRWLclr(p,CTWRITE)
#define ctmutcls(p)	ctrwlcls(p)

#define SEMAmut		RWLOCKmut
#define pSEMAmut	pRWLOCKmut
#define ctSEMUTX

#endif

#else /* ~ctFeatRWLOCK */

#define RWLOCKmut	SEMAmut
#define pRWLOCKmut	pSEMAmut
#define RWL(loktyp)
#define RWCA(loktyp,ownr) ownr
#define ctRWLrqs	ctmutrqs
#define ctRWLclr	ctmutclr
#define ctRWLcls	ctmutcls
#ifdef ctFeatGNSEMAhsh
#define rwl		mtx
#endif

#endif /* ~ctFeatRWLOCK */

#ifdef ctDBGRWLCNT
#ifndef ctDBG_RWLOCK
#undef ctDBGRWLCNT
#endif
#endif

/*
** ctpconcsema mutex options
*/

#define	CMN(nn)		nn

#ifdef ctBEHAV_WORKsync
#ifdef ctBEHAV_WORKsyncRWL

#ifdef ctPortWIN32
#define ctmutclrW(pmtx,owner)		ctRWLclr(pmtx ## _rwl,CTWRITE)
#define ctmutclrR(pmtx,owner)		ctRWLclr(pmtx ## _rwl,CTREAD)
#else
#define ctmutclrW(pmtx,owner)		ctRWLclr(pmtx ## _rwl,owner)
#define ctmutclrR(pmtx,owner)		ctRWLclr(pmtx ## _rwl,owner)
#endif

#else

/*
** assumes no c-tree threadID of zero. we reserve the zeroeth element of
** the array of mutex pointers for the global instance of the mutex.
*/

#define ctmutclrW(pmtx,owner)		ctmutclr(pmtx[0],owner)
#define ctmutclrR(pmtx,owner)		ctmutclr(pmtx[0],owner)

#endif

#define ctmutclrU(pmtx,owner)		ctmutclr(pmtx[owner],owner)
#define ctmutclrI(pmtx,owner,thrd)	ctmutclr(pmtx[thrd],owner)

#else

#define ctmutclrW(pmtx,owner)		ctmutclr(pmtx,owner)
#define ctmutclrR(pmtx,owner)		ctmutclr(pmtx,owner)
#define ctmutclrU(pmtx,owner)		ctmutclr(pmtx,owner)
#define ctmutclrI(pmtx,owner,thrd)	ctmutclr(pmtx,owner)

#endif

#ifdef ctDBGSEMCNT

#ifdef ctBEHAV_WORKsync
#ifdef ctBEHAV_WORKsyncRWL

#define ctmutrqsW(pmtx,owner,smn)	ctRWLrqs(pmtx ## _rwl,CTWRITE,owner,smn)
#define ctmutrqsR(pmtx,owner,smn)	ctRWLrqs(pmtx ## _rwl,CTREAD,owner,smn)

#else

#define ctmutrqsW(pmtx,owner,smn)	ctmutrqs(pmtx[0],owner,smn)
#define ctmutrqsR(pmtx,owner,smn)	ctmutrqs(pmtx[0],owner,smn)

#endif

#define ctmutrqsU(pmtx,owner,smn)	ctmutrqs(pmtx[owner],owner,smn)
#define ctmutrqsI(pmtx,owner,thrd,smn)	ctmutrqs(pmtx[thrd],owner,smn)

#else

#define ctmutrqsW(pmtx,owner,smn)	ctmutrqs(pmtx,owner,smn)
#define ctmutrqsR(pmtx,owner,smn)	ctmutrqs(pmtx,owner,smn)
#define ctmutrqsU(pmtx,owner,smn)	ctmutrqs(pmtx,owner,smn)
#define ctmutrqsI(pmtx,owner,thrd,smn)	ctmutrqs(pmtx,owner,smn)

#endif

#ifndef ctSEMUTX
#define SEMAmut		SEMA
#define pSEMAmut	pSEMA
#define ctmutclr	ctsemclr
#define ctmutcls	ctsemcls
#endif

#define ctsemrqs	ctsemrqsCNT
#define ctsemwat	ctsemwatCNT
#define ctmutrqs	ctmutrqsCNT

#ifdef ctSEMBLK
#define ctblkrqs	ctblkrqsCNT
#define ctblkwat	ctblkwatCNT
#endif
#ifdef ctSEMTIM
#define cttimrqs	cttimrqsCNT
#define cttimwat	cttimwatCNT
#endif

#ifndef ctDBGSEMBLK
#ifdef  ctDBGSEMTIM
#undef  ctDBGSEMTIM	/* requires ctDBGSEMBLK */
#endif
#endif

#ifndef ctrt_hrtimer
#ifdef  ctDBGSEMTIM
#undef  ctDBGSEMTIM	/* requires ctrt_hrtimer */
#endif
#endif

#else /* ~ctDBGSEMCNT */

#ifdef ctBEHAV_WORKsync
#ifdef ctBEHAV_WORKsyncRWL

#define ctmutrqsW(pmtx,owner,smn)	ctRWLrqs(pmtx ## _rwl,CTWRITE,owner)
#define ctmutrqsR(pmtx,owner,smn)	ctRWLrqs(pmtx ## _rwl,CTREAD,owner)

#else

#define ctmutrqsW(pmtx,owner,smn)		ctmutrqs(pmtx[0],owner)
#define ctmutrqsR(pmtx,owner,smn)		ctmutrqs(pmtx[0],owner)

#endif

#define ctmutrqsU(pmtx,owner,smn)		ctmutrqs(pmtx[owner],owner)
#define ctmutrqsI(pmtx,owner,thrd,smn)		ctmutrqs(pmtx[thrd],owner)

#else

#define ctmutrqsW(pmtx,owner,smn)		ctmutrqs(pmtx,owner)
#define ctmutrqsR(pmtx,owner,smn)		ctmutrqs(pmtx,owner)
#define ctmutrqsU(pmtx,owner,smn)		ctmutrqs(pmtx,owner)
#define ctmutrqsI(pmtx,owner,thrd,smn)		ctmutrqs(pmtx,owner)

#endif

#ifndef ctSEMUTX
#define SEMAmut		SEMA
#define pSEMAmut	pSEMA
#define ctmutrqs(s,o)	ctsemrqs(s,WAIT,o)
#define ctmutclr	ctsemclr
#define ctmutcls	ctsemcls
#define ctmutzro(s,o)	ctsemrqs(s,NOWAIT,o)
#endif

#ifdef ctDBGSEMBLK
#undef ctDBGSEMBLK	/* requires ctDBGSEMCNT support */
#endif
#ifdef ctDBGSEMTIM
#undef ctDBGSEMTIM
#endif

#endif /* ~ctDBGSEMCNT */


#ifdef ctCREATE_SEMA
#ifdef ctSTATIC_SEMA
**** ctCREATE_SEMA and ctSTATIC_SEMA are mutually exclusive options ****
#endif
#endif
#ifdef ctCREATE_SEMA
#define ctREUSE_SEMA
#endif
#ifdef ctSTATIC_SEMA
#define ctREUSE_SEMA
#endif

#endif

#ifdef ctCLIENT
#ifndef ctLOCFH
#define ctLOCFH
#endif
#endif

#ifdef TRANPROC
#define ctNogloTran
#endif

#ifdef  ctLOG_IDX
#ifndef TRANPROC
#undef  ctLOG_IDX
#endif
#endif

#ifdef ctLOG_IDX
#ifndef ctLOG_IDX_OLD
#define ctLOG_IDX_NEW	/* default to new approach */
#endif
#else /* ~ctLOG_IDX */
#ifdef ctLOG_IDX_OLD
#undef ctLOG_IDX_OLD
#endif
#ifdef ctLOG_IDX_NEW
#undef ctLOG_IDX_NEW
#endif
#endif /* ~ctLOG_IDX */

#ifdef	ctDBGanl
#ifndef	TRANPROC
#undef	ctDBGanl
#endif
#endif

#ifdef  CTHISTORY
#ifndef TRANPROC
#undef  CTHISTORY
#endif
#endif

#ifdef ctMXLOGS		/* history not supported (yet) with ctMXLOGS */
#ifdef CTHISTORY
#undef CTHISTORY
#endif
#endif

#ifdef ctCMPLOG
#ifdef CTHISTORY
#undef CTHISTORY
#endif
#endif

#ifdef ctBEHAV_UNUSEDtran
#ifndef TRANPROC
#undef ctBEHAV_UNUSEDtran
#endif
#endif

#ifdef MULTITRD

#define MAX_KEY_SEG	ctmaxkeyseg
#ifndef ctMAX_KEY_SEG
#define ctMAX_KEY_SEG	32
#endif

#else /* MULTITRD */

#ifdef ctMAX_KEY_SEG
#define MAX_KEY_SEG	ctMAX_KEY_SEG
#else
#define MAX_KEY_SEG	32	/* maximum number of segments per key	*/
#define ctMAX_KEY_SEG	MAX_KEY_SEG	/* so ctMAX_KEY_SEG defined for
					** both MULTITRD and not	*/
#endif

#endif /* MULTITRD */

#ifdef ctDBGDLNGCNT

#define DLN(nn)	,nn

#define ctUNKtyp	0
#define ctCMPtyp	1
#define ctADDtyp	2
#define ctSUBtyp	3
#define ctMULtyp	4
#define ctDIVtyp	5
#define ctMODtyp	6
#define ctINCtyp	7
#define ctDECtyp	8
#define ctMAXtyp	9

#else

#define DLN(nn)

#define ctCMPdlng	ctcmpdlng
#define ctADDdlng	ctadddlng
#define ctSUBdlng	ctsubdlng
#define ctINCdlng	ctincdlng
#define ctDECdlng	ctdecdlng
#define ctMULdlng	ctmuldlng
#define ctDIVdlng	ctdivdlng
#define ctMODdlng	ctmoddlng

#endif

/* ******************************************************************** */
/* ************************     S T O P    **************************** */
/* ***     D O   N O T   C H A N G E   T H E    F O L L O W I N G   *** */
/* ***   W I T H O U T   C H E C K I N G   W I T H   F A I R C O M  *** */
/* ******************************************************************** */

#ifdef ctXMEM
#undef ctXMEM
#endif /* ctXMEM */
#ifdef MULTITRD
#define ctXMEM
#else
#ifdef ctFLEXFILE
#define ctXMEM
#endif
#endif /* MULTITRD */

#ifndef ctrt_monitor
#define ctrt_monitor	ctrt_printf
#endif

#ifndef ctrt_fncmon
#define ctrt_fncmon	ctrt_printf
#endif

#ifndef ctrt_msgmon
#define ctrt_msgmon	ctrt_printf
#endif

#ifndef ctrt_wrtmsg
#define ctrt_wrtmsg	ctrt_printf
#endif

#ifdef ctMIRROR
#ifdef FPUTFGET
   *** Mirrored files are not supported under FPUTFGET ***
#endif
#endif

#ifndef ctFeatL10_serno
#define ctGhatSize	9 /* ctghat array size-see ctkrnl.c & ctgvar.h */
#ifndef ctFeatL10_serno
#define ctGhatSN 	4
#endif
#define ctGhatVersionid	3
#define ctGhatPortid	2
#endif
#define ctFIXSET	10

#ifndef ctFeatL10_serno
#ifndef ctCLIENT
#ifdef ctSRVR
#define ctdivs	((LONG) ctghat[ctGhatSN])
#define ctdivs_nocast	ctghat[ctGhatSN]
#else
#define ctdivs	((LONG) 0)
#endif
#endif
#endif /*ctFeatL10_serno*/

#ifdef ctLOCLIB
#ifndef ctNOGLOBALS
#define ctNOGLOBALS
#endif
#ifndef ctCONV
#define ctCONV
#endif
#endif

#ifdef ctNOGLOBALS

#ifdef ctLOCLIB
#ifndef TRANPROC
#define ctNogloSize
#define ctNogloTran
#endif
#endif /* ctLOCLIB */

#endif /* ctNOGLOBALS */

#ifndef ctMEMCHRtxt
#define ctMEMCHRtxt	pVOID
#endif

#ifndef ctSIZE
#define ctSIZE(X) ((UINT)sizeof(X))
#endif

#ifndef ctSIZET
#define ctSIZET	size_t
#endif

#ifndef ctALLOC
#ifdef ctPALLOC
#define ct_alloc(n,s)	palloc((ctSIZET)n*(ctSIZET)s)
#define ctafree(p)	pfree(p)
#else
#define ct_alloc(n,s)	calloc(((ctSIZET) (n)),((ctSIZET)(s)))
#define ctafree(p)	free(p)
#endif
#endif

#ifndef ctFileNone
#ifdef CT_ANSI
#define ctFileNone		((RNDFILE) NULL)
#else
#define ctFileNone		((RNDFILE) -1)
#endif
#endif /* ~ctFileNone */

#ifndef ctFileFailure
#ifdef CT_ANSI
#define ctFileFailure		== (RNDFILE) NULL
#else
#define ctFileFailure		< (RNDFILE) 0
#endif
#endif /* ~ctFileFailure */

#ifndef ctVDECL
#define ctVDECL ctDECL
#endif

#ifndef ctDECLV
#define ctDECLV ctDECL
#endif

#ifndef ctDECLT
#define ctDECLT ctDECL
#endif

#define PARM2 (COUNT)0
#define PARM3 (pVOID)0
#define PARM4 (pLONG)0
#define PARM5 (pVOID)0
#define PARM6 (pVRLEN)0
#define PARM7 (COUNT)0

/*
** client and
**    server versions:	1 to 31 for non-optional version updates
**			32, 64, 128, ... for optional version updates
**
**			To test for non-optional client version, use
**			(ctclnMASK & ctclnver). To test for an optional client
**			version update use (ctclnXXXXXX & ctclnver) where
**			XXXXXX is the optional version feature.
**
**			On the client side, tests for server versions are
**			the same except for the use of ctsrvXXXXXX and
**			ctsrvver.
*/

#define ctclnMASK	0x001f
#define ctclnFLEXFILE	0x00000020
#define ctclnHUGEFILE	0x00000040
#define ctclnSUMCHK	0x00000080
#define ctclnLOWL_CRC	0x00000100
#define ctclnMB_FILNAM	0x00000200
#define ctclnSTPSRVCTL	0x00000400
#define ctclnDEAD_CLI	0x00000800 /* New dead client detection protocol */
#define ctclnXTDHDR	0x00001000
#define ctclnATODEP	0x00002000
#define ctclnRBLCBSTT	0x00004000 /* Client supports rebuild callback state */
/*
** no more optional attribute bits with a signed, two-byte integer: cti_apvr
*/

#define ctsrvMASK	0x001f
#define ctsrvHUGEFILE	0x00000040
#define ctsrvSUMCHK	0x00000080
#define ctsrvLOWL_CRC	0x00000100
#define ctsrvMB_FILNAM	0x00000200
#define ctsrvALTFILDEF	0x00000400
#define ctsrvDEAD_CLI	0x00000800 /* New dead client detection protocol */
#define ctsrvUNIFRMAT	0x00001000
#define ctsrvMEMFILE	0x00002000
#define ctsrvXTDHDR	0x00004000
/*
** no more optional attribute bits with a signed, two-byte integer: cti_svvr
*/

#ifndef	ctPort16BIT
#ifndef	ctPortOS2
#define ctFeatNEW_DEAD_CLIENT
#endif
#endif

#ifdef ctFeatNEW_DEAD_CLIENT
#define ctDEAD_CLIENT_MARKER "\xff\xfe\xfd\xfc"
#endif

#ifndef ctMAXUSERS
#if defined(MULTITRD) || defined(ctPortFAIRCOM_INTERNAL_GEN)
#ifdef ct8P
/* Support up to 8192 connections on 64bit systems */
#define ctMAXUSERS	8192
#else
/* Support up to 2048 connections on 32bit systems */
#define ctMAXUSERS	2048
#endif
#else
#define ctMAXUSERS	4
#endif
#endif /* ~ctMAXUSERS */

#ifdef ctSQLSRVR
#define ADMUSERS	36
#else
#define ADMUSERS	31
#endif
#define MAXCOMMP	10

#ifdef ctFeatCOUNT_FCWORKERS
/* max number of worker threads */
#define MAXWORKERS	512
#else
#define MAXWORKERS	0
#endif

#define MXU2		(ctMAXUSERS + ADMUSERS + MAXCOMMP + MAXWORKERS + 1)
#ifndef MAXAPPS
#define MAXAPPS		(ctMAXUSERS + 1)
#endif

/*
** data cache attribute bits (datatr in DATBUF)
*/
#define	ctDATATRsplcache	0x00000001	/* dedicated cache page */
#define ctDATATRscancache	0x00000002	/* scanner LRU page	*/
#define ctDATATRintermedcache	0x00000004	/* intermediate block	*/



#ifndef ITIMretry
#ifdef ctPortREALIA_STD
#define	ITIMretry	100
#else  /* ~ctPortREALIA_STD */
#ifdef ctSS
#define	ITIMretry	20
#else
#define	ITIMretry	10
#endif
#endif /* ~ctPortREALIA_STD */
#endif

#define ITIMdeferOFF	(ULONG)-1
#ifndef ITIMdefer
#define ITIMdefer	ITIMdeferOFF
#endif

#define NOocsema	-199
#define CTRCVLOG_MSGONLY 30987	/* crazy error no: tell ctrcvlog only to output message	*/
				/* do not normal user and date. Ok to change this number*/
				/* if conflict */
#define CTRCVLOG_TRYOPEN 30988	/* crazy error no: tell ctrcvlog to try status log open */
#define TRD_SQL		0x000001
#define TRD_COMMP	0x000002
#define TRD_SBLD	0x000004
#define TRD_ISAM	0x000008
#define TRD_DUMP	0x000010
#define TRD_ADMIN	0x000020
#define TRD_SMON	0x000040
/* 0x000080 and 0x000100 and 0x000200 reserved for 3 additional monitors */
#define TRD_LOGON	0x000400
#define TRD_DNODE	0x000800	/* delete node thread */
#define TRD_RTREE	0x001000	/* r-tree execute thread */
#define TRD_RSPAC	0x002000	/* reclaim space thread */
#define	TRD_TBEG	0x004000	/* TRANBEG allowed during shutdown */
#define TRD_WOPEN	0x008000	/* wait for open (buffer flush) */
#define TRD_LOCAL	0x010000	/* local (server-side) thread */
#define TRD_ASYNC	0x020000	/* generic asynchronous thread */
#define TRD_REPL	0x040000	/* replicate log scanner */
#define TRD_PRIME	0x080000	/* prime cache thread */
#define TRD_IMP		0x100000	/* impersonating another connection */
#define TRD_KEPOPN	0x200000	/* KEEPOPEN file close thread */
#define TRD_DFRIDX	0x400000	/* deferred indexing thread */

#define USE_DEFAULT	(-2L)
#define SUSE_DEFAULT	(-2)
#define UDLK_TRN	(-3)

/* ctclup() cln_mode parameter values: */
#define CLN_CHKACT	0x00000001 /* option: check if the specified transaction is active */
#define CLN_CHKABT	0x00000002 /* option: check abort node list */
#define CLN_GETNOD	(0x00000004 | CLN_CHKACT | CLN_CHKABT) /* ctgetnod81() call */
#define CLN_GETRCV	0x00000008 /* ctgetnod81() call during recovrey */
#define CLN_CLOSE	(0x00000010 | CLN_CHKACT) /* physical close of file */
#define CLN_STRIP	(0x00000020 | CLN_CHKABT) /* ct_strip() */
#define CLN_ABTNOD	(0x00000040 | CLN_CHKACT | CLN_CHKABT) /* abort node list processing during recovery */
#define CLN_SPLNOD	(0x00000080 | CLN_CHKACT | CLN_CHKABT) /* node split */
#define CLN_DELETE	0x00000100 /* option: ctgetnod81(ctGN_CMT) call in standalone mode */
#define CLN_UNDO_OCMTX	0x00000200 /* option: coordinate access to ctpocsema */
#ifdef ctBEHAV_CLN_DBG_LOOP
#define CLN_DBG_LOOP	0x00000400 /* option: unused debug option */
#endif
#ifdef ctBEHAV_NXTMARKS
#define CLN_NXTMARKS	0x00000800 /* option: use NXTMARKS optimization */
#else
#define CLN_NXTMARKS	0 /* no-op */
#endif
#ifdef ctBEHAV_UPDMARKS
#define CLN_UPDMARKS	0x00001000 /* option: use UPDMARKS optimization */
#else
#define CLN_UPDMARKS	0 /* no-op */
#endif

/* ctclup() actions: */
#define CLN_RTRY	(-1) /* retry cleanup */
#define CLN_SKIP	0 /* key value is pending commit, ignore it */
#define CLN_COMMIT	1 /* key value is committed */
#define CLN_UNDO	2 /* undo the mark */

/* COMPATIBILITY definitions */
#define ctCompat5000		((LONG) 0x0000001)
#define ctCompatTranHistoryLogEntries ((LONG) 0x0000002)
#define ctCompatSpcmgt		((LONG) 0x0000004)
#define ctCompatStrmfl		((LONG) 0x0000008)
#define ctCompatWThru		((LONG) 0x0000010)
#define ctCompatMP		((LONG) 0x0000020)
#define ctCompatLogMir		((LONG) 0x0000040)
#define ctCompatAbtCls		((LONG) 0x0000080)
#define ctCompatNone		((LONG) 0x0000100)
#define ctCompatNoConfig	((LONG) 0x0000200)
#define ctCompatNoCommand	((LONG) 0x0000400)
#define ctCompatNonAdminShutdown ((LONG)0x0000800)
#define ctCompatMemLimits	((LONG) 0x0001000)
#define ctCompatLogThru		((LONG) 0x0002000)
#define ctCompatNoUniqFile	((LONG) 0x0004000)
#define ctCompatNLMLongFileNames ((LONG)0x0008000)
#define ctCompatSYNC_LOG	((LONG) 0x0010000)
#define ctCompatctSAVEunxOC	((LONG) 0x0020000)
#define ctCompatLaunchUsrThread	((LONG) 0x0040000)
#define ctCompatNLMDeferThreadSwitch	((LONG) 0x0080000)
#define ctCompatNoSpcMgtQueue	((LONG) 0x0100000)
#define ctCompatExactFileNames	((LONG) 0x0200000)
#define ctCompatForceWriteThru	((LONG) 0x0400000)
#define ctCompatNoShutDownDelay	((LONG) 0x0800000)
#define ctCompatNoTestLocal	((LONG) 0x1000000)
#define ctCompatOldFlush	((LONG) 0x2000000)
#define ctCompatNoBlockKill	((LONG) 0x4000000)
#define ctCompatCommDeadClient 	((LONG) 0x8000000)
#define ctCompatBatuTfrm 	((LONG)0x10000000)
#define ctCompatNoCheckFix 	((LONG)0x20000000)
#define ctCompatVDLFLG 		((LONG)0x40000000)
#define ctCompatFDATASYNC	((LONG)0x80000000)

/* start second compat word: ct_compflg2 */
#define ctCompat2DdSfmCreate	((LONG)0x00000001)
#define ctCompat2DdSfmDelete	((LONG)0x00000002)
#define ctCompat26btranNotDef	((LONG)0x00000004)
#define ctCompat26btranOnly	((LONG)0x00000008)
#define ctCompat2LFLwait	((LONG)0x00000010)
#define ctCompat2LFWadaptive	((LONG)0x00000020)
#define ctCompat2LargeCache	((LONG)0x00000040)
#define ctCompat2NoTranDisc	((LONG)0x00000080)
#define ctCompat2CpMtxRel	((LONG)0x00000100)
#define ctCompat2MemSkpFre	((LONG)0x00000200)
#define ctCompat2W32CharUpper	((LONG)0x00000400)
#define ctCompat2DUPLFATAL	((LONG)0x00000800)
#define ctCompat2CHARSEG	((LONG)0x00001000)
#define ctCompat2NOVSPACE	((LONG)0x00002000)
#define ctCompat2NoSigHandler	((LONG)0x00004000)
#define ctCompat2TDatThru	((LONG)0x00008000)
#define ctCompat2TIdxThru	((LONG)0x00010000)
#define ctCompat2RED_CMTLOK	((LONG)0x00020000)
#define ctCompat2NoSmartSave	((LONG)0x00040000)
#define ctCompat2FlushAllBuf	((LONG)0x00080000)
#define ctCompat2RepTranList	((LONG)0x00100000)
#define ctCompat2FilCreChk	((LONG)0x00200000)
#define ctCompat2NoFlushCls	((LONG)0x00400000)
#define ctCompat2NoExtShtdwn	((LONG)0x00800000)
#define ctCompat2RWTkeyError	((LONG)0x01000000)
#define ctCompat2NoChkMbrNam	((LONG)0x02000000)
#define ctCompat2NonAdminFB	((LONG)0x04000000)
#define ctCompat2FailedTranIO	((LONG)0x08000000)
#define ctCompat2UNUSEDtran	((LONG)0x10000000)
#define ctCompat2PUTHDRcommit	((LONG)0x20000000)
#define ctCompat2DirectIO	((LONG)0x40000000)
#define ctCompat2ClsFilUnblock	((LONG)0x80000000)

/* start third compat word: ct_compflg3 */
#define ctCompat3TempIndexErr	((LONG)0x00000001)
#define ctCompat3BatSig		((LONG)0x00000002)
#define ctCompat3h6flg		((LONG)0x00000004)
#define ctCompat3NoRED_CMTLOK	((LONG)0x00000008)
#define ctCompat3NoVarPeof	((LONG)0x00000010)
#define ctCompat3NoATODEP	((LONG)0x00000020)
#define ctCompat3NoKeepOut	((LONG)0x00000040)
#define ctCompat3LockCache	((LONG)0x00000080)
#define ctCompat3NoSkipAuto	((LONG)0x00000100)
#define	ctCompat3CPoverlap	((LONG)0x00000200)
#define	ctCompat3NoRelBufChk	((LONG)0x00000400)
#define ctCompat3NonAdminXfrFil ((LONG)0x00000800)
#define ctCompat3NoClstranOpen	((LONG)0x00001000)
#define ctCompat3NonAdminQT	((LONG)0x00002000)
#define ctCompat3RngeNoNxtkey	((LONG)0x00004000)
#define ctCompat3OpenShareRW	((LONG)0x00008000)
#define ctCompat3ctRWlock	((LONG)0x00010000)
#define ctCompat3LokHdr		((LONG)0x00020000)
#define ctCompat3LokXcl		((LONG)0x00040000)
#define ctCompat3EstScale	((LONG)0x00080000)
#define ctCompat3Encrypt128	((LONG)0x00100000)
#define ctCompat3LogEncrypt128	((LONG)0x00200000)
#define ctCompat3setexcabt	((LONG)0x00400000)
#define ctCompat3NoMyMarks	((LONG)0x00800000)
#define ctCompat3NoNxtMarks	((LONG)0x01000000)
#define ctCompat3NoBufBlk	((LONG)0x02000000)
#define ctCompat3BufRqs		((LONG)0x04000000)
#define ctCompat3FileGrowth	((LONG)0x08000000)
#define ctCompat3PartExclv	((LONG)0x10000000)
#define ctCompat3NoTrandepScan	((LONG)0x20000000)
#define ctCompat3NoAdrExpCheck	((LONG)0x40000000)
#define ctCompat3NoDataMapCheck	((LONG)0x80000000)

/* start fourth compat word: ct_compflg4 */
#define ctCompat4FFRandomAccess	((LONG)0x00000001)
#define ctCompat4CLSFIL_ISAM	((LONG)0x00000002)
#define ctCompat4MULTIOPN_DIFUSR ((LONG)0x00000004)
#define ctCompat4NonAdminDYNDUMP ((LONG)0x00000008)
#define ctCompat4NonAdminREPL   ((LONG)0x00000010)
#define ctCompat4NonAdminTRNHIST ((LONG)0x00000020)
#define ctCompat4segmax		((LONG)0x00000040)
#define	ctCompat4LKISAMmodes	((LONG)0x00000080)
#define	ctCompat4NOidxsemREADER	((LONG)0x00000100)
#define ctCompat4NO_BAT_FXDCMP	((LONG)0x00000200)
#define ctCompat4MULTIOPN_SAMUSR_1 ((LONG)0x00000400)
#define ctCompat4MULTIOPN_SAMUSR_M ((LONG)0x00000800)
#define ctCompat4NoUpdMarks	((LONG)0x00001000)
#define ctCompat4NO_IDFIELD_OVERFLOW_CONVERSION ((LONG)0x00002000)
#define ctCompat4NO_IDFIELD_OVERFLOW_DETECTION	((LONG)0x00004000)
#define ctCompat4FDLimit	((LONG)0x00008000)
#define ctCompat4RORWtoRORO	((LONG)0x00010000)
#define ctCompat4SHMEMpipe	((LONG)0x00020000)
#define ctCompat4NOFLUSHDIR	((LONG)0x00040000)
#define ctCompat4NOVFLG_ERR	((LONG)0x00080000)
#define ctCompat4NoRCVHDRUPDnument ((LONG)0x00100000)
#define ctCompat4NoDelNodQueue	((LONG)0x00200000)
#define ctCompat4NO_REPL_DEFER_TRAN ((LONG)0x00400000)
#define ctCompat4MINIDXBUF	((LONG)0x00800000)
#define ctCompat4AnyFixOff	((LONG)0x01000000)
#define ctCompat4TermOnSig	((LONG)0x02000000)
#define ctCompat4RenameOvrwrt	((LONG)0x04000000)
#define ctCompat4SqlImpADMpasswd	((LONG)0x08000000)
#define ctCompat4V11_DynDump	((LONG)0x10000000)
#define ctCompat4NoConfigPersist ((LONG)0x20000000)
#define ctCompat4CopyFileOpenShared ((LONG)0x40000000) /* ctCopyFile() opens files in shared mode */
#define ctCompat4KeepNodeOnRead ((LONG)0x80000000)

/* start fifth compat word: ct_compflg5 */
#define ctCompat5available	0x00000001 /* available for use */

/*
** ctCompatUS	user supported compatibility options for BOUND and
**		single-user (i.e., non-Server)
*/
#define ctCompatUS	(ctCompatLogThru | ctCompatSYNC_LOG | ctCompatFDATASYNC)
#define ctCompat2US	(0)



/* DIAGNOSTICS definitions */
#define ctDiagnoseWalk		((LONG) 0x0000001)
#define ctDiagnoseCompare	((LONG) 0x0000002)
#define ctDiagnoseLeak		((LONG) 0x0000004)
#define ctDiagnoseTlog		((LONG) 0x0000008)
#define ctDiagnoseQlog		((LONG) 0x0000010)
#define ctDiagnoseLlog		((LONG) 0x0000020)
#define ctDiagnoseSpcmgt	((LONG) 0x0000040)
#define ctDiagnoseComm1		((LONG) 0x0000080)
#define ctDiagnoseCustom	((LONG) 0x0000100)
#define ctDiagnoseLogonComm	((LONG) 0x0000200)
#define ctDiagnoseThdDmp	((LONG) 0x0000400)
#define ctDiagnoseDebug		((LONG) 0x0000800)
#define ctDiagnoseTrapComm	((LONG) 0x0001000)
#define ctDiagnoseFlog		((LONG) 0x0002000)
#define ctDiagnoseDDlog		((LONG) 0x0004000)
#define ctDiagnoseANL		((LONG) 0x0008000)
#define ctDiagnoseLokDmp	((LONG) 0x0010000)
#define ctDiagnoseNone		((LONG) 0x0020000)
#define ctDiagnoseNoExHndlr	((LONG) 0x0040000)
#define ctDiagnoseLowlCRC	((LONG) 0x0080000)
#define ctDiagnoseFncMon	((LONG) 0x0100000)
#define ctDiagnoseFrcShd	((LONG) 0x0200000)
#define ctDiagnoseCTSFIO_A	((LONG) 0x0400000)
#define ctDiagnoseWriteThru	((LONG) 0x0800000)
#define ctDiagnoseShowCtErrs	((LONG)0x01000000)
#define ctDiagnoseQAFollowThru	((LONG)0x02000000)
#define ctDiagnoseNot6BTfile	((LONG)0x04000000)
#define ctDiagnoseFlushBLM	((LONG)0x08000000)
#define ctDiagnoseWrkTim	((LONG)0x10000000)
#define ctDiagnoseSemTim	((LONG)0x20000000)
#define ctDiagnosePSSshtDwn	((LONG)0x40000000)
				/* avail 80000000 */
/* start second diagnose word: ct_diagflg2 */
#define ctDiagnose2intrmd	((LONG)0x00000001)
#define ctDiagnose2udeferChk	((LONG)0x00000002)
#define ctDiagnose2NoLogExt	((LONG)0x00000004)
#define ctDiagnose2L59		((LONG)0x00000008)
#define ctDiagnose2RemThrds	((LONG)0x00000010)
#define ctDiagnose2WrtErrDmp	((LONG)0x00000020)
#define ctDiagnose2UpdFlg	((LONG)0x00000040)
#define ctDiagnose2ShtdwnComm	((LONG)0x00000080)
#define ctDiagnose2DirectIO	((LONG)0x00000100)
#define ctDiagnose2AtoTrnChkLok	((LONG)0x00000200)
#define ctDiagnose2AtoTrnChkRed	((LONG)0x00000400)
#define ctDiagnose2AtoPreChkLok	((LONG)0x00000800)
#define ctDiagnose2AtoPreChkRed	((LONG)0x00001000)
#define ctDiagnose2DLOK_ERR	((LONG)0x00002000)
#define ctDiagnose2DProcExit	((LONG)0x00004000)
#define ctDiagnose2DReplRedBuf	((LONG)0x00008000)
#define ctDiagnose2IOTime	((LONG)0x00010000)
#define ctDiagnose2NodeTime	((LONG)0x00020000)
#define ctDiagnose2KLLX		((LONG)0x00040000)
#define ctDiagnose2FullDump	((LONG)0x00080000)
#define ctDiagnose2CtUserError	 ((LONG)0x00100000)
#define ctDiagnose2CtUserVerbose ((LONG)0x00200000)
#define ctDiagnose2VssWriter	((LONG)0x00400000)
#define ctDiagnose2Abort	((LONG)0x00800000)
#define ctDiagnose2MemTrack	((LONG)0x01000000)
#define ctDiagnose2SuballocOff	((LONG)0x02000000)
#define ctDiagnose2CMPRECall	((LONG)0x04000000)
#define ctDiagnose2PTADMIN	((LONG)0x08000000)
#define ctDiagnose2PCRP_ERR	((LONG)0x10000000)
#define ctDiagnose2REPLICATE	((LONG)0x20000000)
#define ctDiagnose2TRAN_RECOVERY ((LONG)0x40000000)
#define ctDiagnose2StatsNopndg	((LONG)0x80000000)
/* start third diagnose word: ct_diagflg3 */
#define ctDiagnose3DYNPARTNOMBR	((LONG)0x00000001)
#define ctDiagnose3STARTUP_INFO	((LONG)0x00000002)
#define ctDiagnose3CHKPNT_FILLST ((LONG)0x00000004)
#define ctDiagnose3NODEQ_MESSAGE ((LONG)0x00000008)
#define ctDiagnose3BACKGROUNDFLS ((LONG)0x00000010)
#define ctDiagnose3BACKGROUNDFLSBKT ((LONG)0x00000020)
#define ctDiagnose3MAXACTCONN	((LONG)0x00000040)
#define ctDiagnose3IICT		((LONG)0x00000080)
#define ctDiagnose3DFRIDX	((LONG)0x00000100)
#define ctDiagnose3RECLOK	((LONG)0x00000200)
#define ctDiagnose3READ_ERR	((LONG)0x00000400)
#define ctDiagnose3UNICODE	((LONG)0x00000800)
#define ctDiagnose3UNOD_ERR	((LONG)0x00001000)
#define ctDiagnose3CMTLOK	((LONG)0x00002000)
#define ctDiagnose3TR_RDIF_ERR	((LONG)0x00004000)
#define ctDiagnose3TR_TRAN_ERR	((LONG)0x00008000)
#define ctDiagnose3CHECKLOCK	((LONG)0x00010000)
#define ctDiagnose3LOG_PURGE	((LONG)0x00020000)
#define ctDiagnose3LDAP		((LONG)0x00040000)
#define ctDiagnose3FILE_BLOCK	((LONG)0x00080000)
#define ctDiagnose3FILE_CLOSE_FLUSH ((LONG)0x00100000)
#define ctDiagnose3CHECK_KEY_MARKS ((LONG)0x00200000)
#define ctDiagnose3SYSTEM_FILE_ID_LIST ((LONG)0x00400000)
#define ctDiagnose3HISTORY_API	((LONG)0x00800000)
#define ctDiagnose3FALG_ERR	((LONG)0x01000000)
#define ctDiagnose3DMAP_ERR	((LONG)0x02000000)
#define ctDiagnose3POPN_ERR	((LONG)0x04000000)

/* CTSTATUS_MASK definitions */
#define ctStatusVDP		((LONG) 0x001)
#define ctStatusFID		((LONG) 0x002)
#define ctStatusFCRP		((LONG) 0x004)
#define ctStatusWRTERR		((LONG) 0x008)
#define ctStatusATOTRN		((LONG) 0x010)
#define ctStatusDYNDMPFILES	((LONG) 0x020)

/* LANGUAGE definitions */
#define ctLangENGLISH		((LONG) 0x001)
#define ctLangITALIAN		((LONG) 0x002)
#define ctLangSPANISH		((LONG) 0x004)
#define ctLangPORTUGUESE	((LONG) 0x008)
#define ctLangSJIS		((LONG) 0x010)
#define ctLangEUC		((LONG) 0x020)


/* CONSOLE definitions */
#define ctConsoleNoMessageBox	((LONG) 0x001)
#define ctConsoleCtlCEnable	((LONG) 0x002)
#define ctConsoleNone		((LONG) 0x004)
#define ctConsoleNoPwrDwnPassword ((LONG) 0x008) /* MAC-bypass shutdown password
						    on system powerdown */
#define ctConsoleNoShutdownPrompt ((LONG) 0x010) /* By pass any shutdown
						    prompts */
#define ctConsoleToolTray	((LONG) 0x020) /* W32 Tool Tray (background) */
#define ctConsoleW9XService	((LONG) 0x040) /* W9X_SERVICE (background)   */


/* SYSLOG definitions */
#define ctSyslogUSR		((LONG) 0x00000001)	/* user logon/profile	    */
#define ctSyslogDMP		((LONG) 0x00000002)	/* dynamic dump entries	    */
#define ctSyslogNone		((LONG) 0x00000004)	/* block additional options */
#define ctSyslogSTAT		((LONG) 0x00000008)	/* add CTSTATUS entries	    */
#define ctSyslogCRYP		((LONG) 0x00000010)	/* encrypt SYSLOGxx.FCS	    */
#define ctSyslogSTART		((LONG) 0x00000020)	/* internal use		    */
#define ctSyslogADMIN		((LONG) 0x00000040)	/* only ADMIN group use API */
#define ctSyslogDISABLE		((LONG) 0x00000080)	/* disable API calls	    */
#define ctSyslogFAILTERM	((LONG) 0x00000100)	/* log fail: terminate srvr */
#define ctSyslogFAILPRGE	((LONG) 0x00000200)	/* log fail: purge	    */
#define ctSyslogFAILSTAT	((LONG) 0x00000400)	/* log fail: CTSTATUS	    */
#define ctSyslogDELFIL		((LONG) 0x00000800)	/* delete file entries	    */
#define ctSyslogANL		((LONG) 0x00001000)	/* abort node list entries  */
#define ctSyslogDYNDMPFILES	((LONG) 0x00002000)	/* files backed up by dyndmp*/
#define ctSyslogRSTPNT		((LONG) 0x00004000)	/* restore point events     */
#define ctSyslogSQLSTMT		((LONG) 0x00008000)	/* sql statements     */

/* SYSVIEW_WHAT definitions */
#define ctSysViewWhatALL	((LONG) 0x0001)	/* view ALL system resources*/
#define ctSysViewWhatUSRCNT	((LONG) 0x0002)	/* user count		    */
#define ctSysViewWhatUSRLST	((LONG) 0x0004)	/* list of users	    */
#define ctSysViewWhatFILCNT	((LONG) 0x0008)	/* open file count	    */
#define ctSysViewWhatFILLST	((LONG) 0x0010)	/* list of open files	    */
#define ctSysViewWhatTRNCNT	((LONG) 0x0020)	/* active transaction count */
#define ctSysViewWhatTRNLST	((LONG) 0x0040)	/* list of transactions	    */
#define ctSysViewWhatMEM	((LONG) 0x0080)	/* memory usage		    */
#define ctSysViewWhatLOGS	((LONG) 0x0100)	/* log characteristics	    */

/* SYSVIEW_WHEN definitions */
#define ctSysViewWhenALL	((LONG) 0x0001)	/* view at all report points*/
#define ctSysViewWhenCHKBEG	((LONG) 0x0002)	/* at beginning of chkpoint */
#define ctSysViewWhenCHKEND	((LONG) 0x0004)	/* at end of chkpoint	    */
#define ctSysViewWhenSHUT	((LONG) 0x0008)	/* at start of shutdown	    */
#define ctSysViewWhenLOGNUM	((LONG) 0x0010)	/* # of logs change	    */
#define ctSysViewWhenLOGSIZ	((LONG) 0x0020)	/* size of logs change	    */
#define ctSysViewWhenDMPBEG	((LONG) 0x0040)	/* at beginning of dyndmp   */
#define ctSysViewWhenDMPEND	((LONG) 0x0080)	/* at end of dyndmp	    */

#define ctSysViewLocCHKBEG	0
#define ctSysViewLocCHKEND	1
#define ctSysViewLocSHUT	2
#define ctSysViewLocLOGNUMinc	3
#define ctSysViewLocLOGSIZ	4
#define ctSysViewLocDMPBEG	5
#define ctSysViewLocDMPEND	6
#define ctSysViewLocLOGNUMdec	7

/* SQL_OPTION definitions */
#ifdef PAOLO_REMOVED_NOT_USED
#define ctSqlOptSUPERFILE	((LONG) 0x00000001) /* use superfiles with SQL  */
#else
#define ctSqlCTDBROWID		((LONG) 0x00000001) /* use ROWID compatible with ctdb */
#endif
#define ctSqlOptNONE		((LONG) 0x00000002) /* block additional options */
#define ctSqlOptOwnerFileNames	((LONG) 0x00000004) /* Prepend file name with owner */
#define ctSqlOptForceTemplate	((LONG) 0x00000008) /* Force Template Database creation attempt */
#define ctSqlNoSysSuperfile	((LONG) 0x00000010) /* disable system tables in superfile */
#define ctSqlNoUserValidation	((LONG) 0x00000020) /* disable the user validation, any user can connect */
#define ctSqlNoCardinality	((LONG) 0x00000040) /* disable the cardinality info to the optimizer */
#define ctSqlNoSelectivity	((LONG) 0x00000080) /* disable the selectivity info to the optimizer */
#define ctSqlNoCosts		((LONG) 0x00000100) /* disable the costs info to the optimizer */
#define ctSqlHMYES		((LONG) 0x00000200) /* enable Dharma Heap Management */
#define ctSqlUCase		((LONG) 0x00000400) /* database case insensitive */
#define ctSqlNoReverse		((LONG) 0x00000800) /* disable backward index scans */
#define ctSqlNoDBverify		((LONG) 0x00001000) /* disable database version verification */
#define ctSqlZeroPadding	((LONG) 0x00002000) /* Fixed string padding set to '\0' instead of ' ' */
#define ctSqlCheckHeap		((LONG) 0x00004000) /* enable heap memory check on free */
#define ctSqlNoSharedMem	((LONG) 0x00008000) /* disable SQL shared memory communication protocol */
#define ctSqlNonHuge		((LONG) 0x00010000) /* set default file creation to not HUGE */
#define ctSqlNoPushDown		((LONG) 0x00020000) /* disable RPN expression pushdown */
#define ctSqlPartialSeg		((LONG) 0x00040000) /* enable partial field segment handling */
#define ctSqlPreserveNoLock	((LONG) 0x00080000) /* enable "unsafe" lock free when using preserver cursor (Perceptive Request)*/
#define ctSqlUseRowid		((LONG) 0x00100000) /* create tables with rowid field*/
#define ctsqlUseRecbyt		((LONG) 0x00200000) /* create tables with recbyt index*/
#define ctsqlCallBackDLL	((LONG) 0x00400000) /* do not attempt to search and load the callback dll*/
#define ctsqlNoAutoAbort	((LONG) 0x00800000) /* do automatically rollback on deadlock or invalid transaction*/
#define ctsqlNoJVMLoadErr	((LONG) 0x01000000) /* suppress JVM library loading error messages (if any)*/
#define ctsqlCTSTRINGVarchar	((LONG) 0x02000000) /* use CTSTRING type for varchar */
#define ctsqlNoTblNameInIdxName	((LONG) 0x04000000) /* do not prepend index name with ctdb table name*/
#define ctsqlUseMM_notLATTE	((LONG) 0x08000000) /* fallback to MM instead of latte*/
#define ctsqlOldDelFldLen	((LONG) 0x10000000) /* use CTCREATE_V8DELFLD fiel mode when creating tables in SQL*/
#define ctsqlBADDATES2NULL	((LONG) 0x20000000) /* display invalid dates as NULL */
#define ctsqlCRY_SYSTBL		((LONG) 0x40000000) /* encrypt system table using CAMO or AES */
#define ctsqlUSE_DH_CASE	((LONG) 0x80000000) /* revert to use V10.0 CASE logic */

/* start second sql_option LONG: ct_sqlofl2 */
#define ctSqlNO_BINARY_PAD	((LONG) 0x00000001) /* do not comply to documentation, do not pad binary */
#define ctsql2IPv6Off		((LONG) 0x00000002) /* do not accept IPv6 connections (defined in os_net.cxx) */
#define ctsqlNO_MRTcard		((LONG) 0x00000004) /* do not use phisical table entries for MRT cardinality hint */
#define ctsqlNO_MRTsel		((LONG) 0x00000008) /* do not use phisical table entries for MRT selectivity calculation */
#define ctsqlFLEXREC		((LONG) 0x00000010) /* CREATE TABLE defaults to hot alter support activated */
#define ctsqlDELMRTHOST		((LONG) 0x00000020) /* DROP TABLE delete physical host table on last MRT drop */
#define ctsqlBADTIMES2NULL	((LONG) 0x00000040) /* display invalid time and timestamps as NULL*/
#define ctsqlLITERALCHAR	((LONG) 0x00000080) /* literal constant as fixed length CHAR (backward compatible)*/
#define ctsqlDROPDICTONLY	((LONG) 0x00000100) /* "drop table" deletes imported tables (backward compatible behavior)*/
#define ctsqlFPUTFGETrw		((LONG) 0x00000200) /* FPUTFGET storage engine in RW mode */
#define ctsqlPIDinNODENAME	((LONG) 0x00000400) /* default NODE name use the client pid if sent by the client */
#define ctsqlINTdivINTisINT	((LONG) 0x00000800) /* INT/INT result in INT type (MS SQL behavior) */

/* SQL_DEBUG definitions */
#define ctSqlDbgFUTURE_USE	((LONG) 0x00000001) /* Log SQL stub high level 	*/
#define ctSqlDbgNONE		((LONG) 0x00000002) /* block additional options */
#define ctSqlDbgLOGSTUBSHIGH	((LONG) 0x00000004) /* Log SQL stub high level 	*/
#define ctSqlDbgLOGSTUBSMED	((LONG) 0x00000008) /* Log SQL stub medioum level */
#define ctSqlDbgLOGSTUBSLOW	((LONG) 0x00000010) /* Log SQL stub low level */
#define ctSqlDbgINDEX		((LONG) 0x00000020) /* Log SQL Index scans */
#define ctSqlDbgINDEX_INFO	((LONG) 0x00000040) /* Log SQL key info */
#define ctSqlDbgLOG_TIMES	((LONG) 0x00000080) /* Log SQL STATEMENT execution time */
#define ctSqlDbgLOG_TIMES_FETCH ((LONG) 0x00000100) /* Log SQL STATEMENT fetch time */
#define ctSqlDbgINDEXDEFSEL	((LONG) 0x00000200) /* Log SQL Index default selectivity info*/
#define ctSqlDbgINDEXSEL	((LONG) 0x00000400) /* Log SQL Index selectivity info */
#define ctSqlDbgPANIC		((LONG) 0x00000800) /* SQL PANIC causes process abort */
#define ctSqlDbgLOGERRINFO	((LONG) 0x00001000) /* Log SQL errors with query info */
#define ctSqlDbgPANIC_STACK	((LONG) 0x00002000) /* SQL PANIC generates stack trace */
#define ctSqlDbgLOG_STMTS	((LONG) 0x00004000) /* Log SQL STATEMENT */

/* SERVER_SDK definitions */
#define ctServerSDK_HSPIPE_FROM_NET	((LONG) 0x0001)
#define ctServerSDK_HSPIPE_TO_MEMQ	((LONG) 0x0002)
#define ctServerSDK_HSPIPE_TO_DB	((LONG) 0x0004)
#define ctServerSDK_MEMQ_TO_DB		((LONG) 0x0008)

/* PERF_MONITOR definitions */
#define ctPMargALLEVT	 0x00000001
#define ctPMargCHKPNT	(0x00000002 | ctPMargALLEVT)
#define ctPMargLOGEXT	(0x00000004 | ctPMargALLEVT)
#define ctPMargTRNTIM	(0x00000008 | ctPMargALLEVT)

/*
** detect infinite loop in move right operation
**
**	ctMOVRGTlmt is an aribitray number which should be significantly
**	larger than any reasonable number of move right steps required
**	to search an index
*/
#define ctMOVRGTlmt	16384


#define C254		(C255 - 1)

#define	LOGTYPE		0
#define	STRFILE		2
#define TNAMES		4
#define IDXLOG		6
#define DATLOG		8

#define aqSIZE		512
#define pvSIZE		4

#define ctLNKSIZ	5	/* fixed length delete link length	  */
#define ctLNKSIZ8	9

#define ctLRGNODEpage	16384	/* very large nodes must be multiple of this */
#define RESHDRPFX	(ctSIZE(UCOUNT) + 2 * ctSIZE(VRLEN))
#define RESIDSIZE	(2 * ctSIZE(LONG))
#define RESHDRSIZ	(ctSIZE(UCOUNT) + 2 * ctSIZE(VRLEN) + 3 * ctSIZE(LONG))
#define FRESHDRINC	RESHDRSIZ
#define VRESHDRINC	(3 * ctSIZE(LONG))
#ifdef ctHUGEFILE
#define RESHDRSIZ8	(RESHDRSIZ + 2 * ctSIZE(LONG))
#define ctSEGvals	7	/* # of huge hdr values in log entries */
#endif /* ctHUGEFILE */
#define ctSEGLIST	8192		/* max segment list size */

#define CONVERT_NUL	0
#define CONVERT_IN	1
#define CONVERT_OUT	2
#define ctNOVARREG	((VRLEN) -1)

#define ctREGULAR_LOGON

/**********************/
/* Special ODBC Settings */
#define  ctOTPORT_H	"ctotport.h"
#ifdef   otGPS_TYPES
#include ctOTPORT_H
#endif
#ifdef   otPortAMICUS
#include ctOTPORT_H
#endif
/**********************/

#define LOGON		0
#define LOGOFF		1
#define STOPSRVR	2
#define STARTSRVR	3
#define LOGONu		4
#define LOGONspcl	0x0010	/* bit mask to OR into LOGON or LOGONu */
#define LOGONsalt	0x0020	/* get salt for specified user account */
#define LOGONwork	0x0040	/* fc worker logon */

#ifdef ctFeatPWDLEN

#define LOGONSECVER	2	   /* secure logon version	*/

#define LOGONSECHSHLEN1	16	   /* version 1 size of logon hash value */
#define LOGONSECHDRLEN1	4	   /* version 1 size of header field	 */

typedef struct lsblk {
	UTEXT	vers;		/* structure version	0x00 */
	UTEXT	attr;		/* attributes		0x01 */
	UTEXT	unused[2];	/* available for use	0x02 */
	UTEXT	salt[PWS];	/* salt value		0x04 */
	UTEXT	rand[PWS];	/* random value		0x24 */
} LSBLK, *pLSBLK;

typedef struct cvblk {
	LONG	revsn;		/* client revision	0x00 */
	UTEXT	major;		/* major client version	0x04 */
	UTEXT	minor;		/* minor client version	0x05 */
	UTEXT	mini;		/* mini client version  0x06 */
	UTEXT	pad;		/* unused pad byte	0x07 */
} CVBLK, *pCVBLK;

/* function prototype for secure logon password hash callback function */
#ifdef PROTOTYPE
typedef ctCONV NINT (*pLSHCBFNC)(pLSBLK plsblk, pUTEXT outbuf, NINT outlen);
#else
typedef ctCONV NINT (*pLSHCBFNC)();
#endif

#else

#define LOGONSECHSHLEN	16	   /* size of logon hash value	*/
#define LOGONSECHDRLEN	4	   /* size of header field	*/
#define LOGONSECVER	1	   /* secure logon version	*/

#endif

#define LOGONSECrmt	0x00000001 /* remote secure logon	*/
#define LOGONSECint	0x00000002 /* internal logon		*/

#ifndef COMMIT_DELAY
#define COMMIT_DELAY	10000	/* microseconds */
#endif
#define CHECK_DELAY	50000	/* microseconds */
#ifndef ctMILLISECOND
#define ctMILLISECOND(t)	(t)
#endif

#ifndef ct_udefer
/*
** Unix ct_udefer defaults to our ct_usleep
** routine that usually calls nanosecond().
*/
#ifdef ctPortUNIX
#define ct_udefer	ct_usleep
#endif
#endif

/*
** if no ct_udefer has been defined by this point.
** ct_udefer turns into a call to ct_udefer_sys that is
** conditionally implemented in ctinit.c, and that uses
** the yield technique below the threshold (if any), and
** otherwise calls ctdefer with the microseconds converted
** to milliseconds.
*/
#ifndef ct_udefer
#define	ctUDFRsys
#define ct_udefer(t)	ct_udefer_yld(t)
#endif


#define WAIT		-1L	/* inifinite	*/
#define NOWAIT		0L
#define SHORTWAIT	1L	/* smallest tick */
#ifdef MTDEBUG
#define WAITnodebug	-2L
#else
#ifdef DebugSemDeadLock
#define WAITnodebug	-2L
#else
#define WAITnodebug	WAIT
#endif
#endif


/*
  Special status values for the transaction file number (tfil) to c-tree file
  number map used during auto recovery. These values can be used instead of a
  valid c-tree file number (which is non-negative) to indicate a special state
  of the corresponding tfil. These values may be passed as input to put_lgtorc()
  in the lgn parameter and may be returned from ctlgtorc().
*/
#define NOT_OP_RCV	-3	/* file not open/not found by recovery */
#define NOT_OP_FID	-4	/* file found with the same name but with a different file ID */
#define NOT_OP_TRY	-5	/* file not found, retry later */
#define NOT_OP_FID_MBR	-6	/* FIDD_ERR: index member tfil map */
#define NOT_OP_SKP	-7	/* File was explicitly skipped */
#define NOT_OP_MBR	-20	/* superfile member not opened by recovery */

/* Supported values for the put_lgtorc() updflg parameter */
#define UF_UPDATE_NO		0	/* do not update existing tfil map */
#define UF_UPDATE_YES		2	/* update existing map unconditionally */
#define UF_UPDATE_IF_NOP	1	/* update existing map if NOT_OP_FID/NOT_OP_RCV */
#define UF_KEEP_IF_NOP		-1	/* keep existing map if NO_OP_FID/NOT_OP_FID_MBR */
#define UF_KEEP_YES		3	/* keep existing map unconditionally */

/*
** Log Set unused state values
*/
#define ctLSdlybeg	-7
#define ctLSnotuse	-11

/*
** System Queue Indices
*/
#define SHRINKQ		0
#define CHKPNTQ		1
#ifdef ctMXLOGS
#define ctQUEUE		(CHKPNTQ + ctMXLOGS)
#else
#define ctQUEUE		(CHKPNTQ + 1)
#endif
#define ctSDKQ		(ctQUEUE + 1)
#define SYSLOGQ		(ctSDKQ  + 1)
#define SPACEQ		(SYSLOGQ + 1)
#define IDLEQ0		(SPACEQ  + 1)
#define ctKOCQ		(IDLEQ0 + ctIDLEz)
#define NONTRANDTFLSQ	(ctKOCQ + 1)
#define NONTRANIXFLSQ	(ctKOCQ + 2)
#define TRANDTFLSQ	(ctKOCQ + 3)
#define TRANIXFLSQ	(ctKOCQ + 4)
#define PARTAUTOPURGEQ	(ctKOCQ + 5)

#ifdef ctPortMACOSX_COCOA
#define MSGLOGQ		(PARTAUTOPURGEQ + 1)
#define FNCLOGQ		(MSGLOGQ + 1)
#define MONITORQ0	(FNCLOGQ + 1)
#else  /* ctPortMACOSX_COCOA */
#define MONITORQ0	(PARTAUTOPURGEQ + 1)
#endif /* ctPortMACOSX_COCOA */

#define ctMAX_MONITOR	2
#define ctMAXQ		(MONITORQ0 + ctMAX_MONITOR)

/*
** support for ctBEHAV_CHKPDFC
*/
#ifdef ctBEHAV_CHKPDFC
#ifndef MULTITRD
#undef ctBEHAV_CHKPDFC
#endif
#endif


#ifndef ctSTACKSIZE
#define ctSTACKSIZE	65536
#endif
#define QCHUNK_SIZE	10000L
#define ctGidMem	0x00000002
#define ctAbsMem	0x00000004
#define ctPwdHsh	0x00000008
#define ctPwdHs2	0x00000010
#define ctPwdKeyExchg	0x00000020
#define ctUsrAuthLDAP	0x00000040
#define ctUsrInfoCLIENTID 0x00000080
#define ctUsrProtocolSSL 0x00000100

#ifdef ctFeatCLIENTID
#define ctCLIENTID_MASK ctUsrInfoCLIENTID
#else
#define ctCLIENTID_MASK 0
#endif

#ifdef ctFeatKEYXCHG
#define LATTR_MASK (ctPwdHsh|ctPwdHs2|ctPwdKeyExchg|ctCLIENTID_MASK)
#else
#define LATTR_MASK (ctPwdHsh|ctPwdHs2|ctCLIENTID_MASK)
#endif

/* User authentication types for SA_ADMIN API */
#define ctMAX_AUTHTYPES		2
#define ctAUTHTYPE_CTREE	"ctree"
#define ctAUTHTYPE_LDAP		"ldap"

/* Key exchange version number */
#ifdef ctBEHAV_LOGONHASH_USE_SHA512
#define CTKXVER		0x02
#else
#define CTKXVER		0x01
#endif

#define SHDHBINS	128
#define LOKHBINS	16
#define TRNHBINS	128
#define ctCONBINS	6
#define ctMEMSIG	0x4385

#define LOKHBINX	131072	/* default LOCK_HASH_MAX for ctDYNHASH	   */
#define LOKHloadF	6	/* avg entries per lock hash bin	   */
#define LOKHrehashF	4	/* fraction (1/4) of bins rehashed at once */
#define SHDHBINX	1048576	/* default PREIMAGE_HASH_MAX for ctDYNHASH */
#define SHADloadF	6	/* avg entries per preimage hash bin	   */
#define SHADrehashF	4	/* fraction (1/4) of bins rehashed at once */

#define ctHSHSTTbinrem	0x0001	/* indicate that dehash could not get
				** smaller array on list ptrs; so we can
				** double bins in place on next rehash	   */
#define ctHSHSTThitmax	0x0002	/* rehash denied by maxbins limit	   */
#define ctHSHSTTinproc	0x0004	/* hash list in use: avoid recursion problm*/

#define SEQNXT	1
#define SEQPRV	2
#define SEQFLT	32	/* modify SEQNXT/SEQPRV if filter retry */


#define EXS		0	/* exists			*/
#define SPC		1	/* pending			*/
#define UND		2	/* undoing pending		*/
#define RVS		3	/* part of SPC pair		*/
/* -------------------------------------------------------------*/
#define SPC_DIF		4	/* pending for dif tran		*/
#define UND_DIF		5	/* undoing pending for dif tran	*/

#define FN_MASK		0x00ff
#define FN_MASK_ISAM	0x0100
#define FN_MASK_LONG	0x0200
#define FN_MASK_VRLEN	0x0400
#define FN_MASK_OUTPUT	0x0800
#define FN_MASK_LOGON	0x1000
#define FN_MASK_NFCHK	0x2000
#define FN_MASK_OUTRET	0x4000

#define FN_BASE_LONG	150
#define FN_BASE_VRLEN	180
#define FN_BASE_TEXT	188

/* control structure list types for ctgetlst() & ctputlst() */
#ifndef PI_UNIT
#define PI_UNIT		16
#endif

#ifdef ctFeatSHDLST
#define KLNTYP		0
#define PI1TYP		1
#define PI2TYP		2
#define PI4TYP		3
#define PI8TYP		4
#define PIwTYP		5
#define PIxTYP		6
#define PIyTYP		7
#define PIzTYP		8
#define PIaTYP		9
#define PIbTYP		10
#define SHDTYP		11
#else
#define SHDTYP		0
#define KLNTYP		1
#define PI1TYP		2
#define PI2TYP		3
#define PI4TYP		4
#define PI8TYP		5
#define PIwTYP		6
#define PIxTYP		7
#define PIyTYP		8
#define PIzTYP		9
#define PIaTYP		10
#define PIbTYP		11
#endif
#ifdef ctFeatBATLST
#define PILAST		12    /* set to index of last hashed sublist < SEMTYP */
#else
#define PILAST		11    /* set to index of last  list */
#endif
#define BATTYP		12
#define ILKTYP		13
#define FNMTYP		14

#define SEMTYP		15    /* These types do not require semaphore control */

#ifdef ctMXLOGS

#define COMTYP		15			/* array of sublists */
#define ABTTYP		(COMTYP + ctMXLOGS)	/* array of sublists */
#define LOKTYP		(ABTTYP + ctMXLOGS)
#define DCMTYP		(LOKTYP + 1)		/* array of sublists */
#define IXCTYP		(DCMTYP + ctMXLOGS)
#define DTCTYP		(IXCTYP + 1)
#define CTCTYP		(DTCTYP + 1)
#define IXBTYP		(CTCTYP + 1)
#define DTBTYP		(IXBTYP + 1)		/*
						** IXBTYP and DTBTYP must be
						** the last two list types
						*/
#define NUMCTLIST	(DTBTYP + 1)

#else /* ~ctMXLOGS */

#define COMTYP		15
#define ABTTYP		16
#define LOKTYP		17
#define DCMTYP		18
#define IXCTYP		19
#define DTCTYP		20
#define CTCTYP		21
#define IXBTYP		22
#define DTBTYP		23
#define NUMCTLIST	24

#endif /* ~ctMXLOGS */

#ifdef MULTITRD

#ifdef ctFeatTRAN_TIMEOUT
#define ctTRNTIMOUTtot	1
#else
#define ctTRNTIMOUTtot	0
#endif

#ifdef ctFeatREQUEST_TIME_MONITOR
#define ctRQSTIMCHKtot	1
#else
#define ctRQSTIMCHKtot	0
#endif

#ifdef ctDISTcounts
#define ctDISTcountsWatTot	1
#else
#define ctDISTcountsWatTot	0
#endif

#ifdef ctMXLOGS

#define ctSEMS		(10 + 5 * ctMXLOGS)	/* global SEMA		*/
#define ctSEMX		(22 + 9 * ctMXLOGS)	/* global SEMAmut	*/

#ifdef ctBEHAV_CHKPDFC
#define ctCHKPDFCtot	ctMXLOGS
#else
#define ctCHKPDFCtot	0
#endif


#ifdef ctBEHAV_MXLFW
			/* one extra used as a place holder to simplify tests */
#define ctSEMB		(((ctMXLFW + 1) * ctMXLOGS) + 1)
#else
#define ctSEMB		(ctMXLOGS + 1)		/* global SEMAblk	*/
#endif

#else  /* ~ctMXLOGS */

#define ctSEMS		16	/* global SEMA		*/
#define ctSEMX		31	/* global SEMAmut	*/

#ifdef ctBEHAV_CHKPDFC
#define ctCHKPDFCtot	1
#else
#define ctCHKPDFCtot	0
#endif

#ifdef ctBEHAV_MXLFW
			/* one extra used as a place holder to simplify tests */
#define ctSEMB		(ctMXLFW + 2)
#else
#define ctSEMB		 2	/* global SEMAblk	*/
#endif

#endif /* ~ctMXLOGS */

#ifdef needRWLauxflds
#define ctSEMW		8	/* 4 of 8 in use now	*/
#endif

/* global SEMAtim */
#define ctSEMT		(2 + ctCHKPDFCtot + ctTRNTIMOUTtot + ctRQSTIMCHKtot + ctDISTcountsWatTot)

#define FIRST_USER_TASK	2

#define ctCPYFILBUF	131072

#ifdef ctMAXSORTBUF
#define	CTSORTBUF       ctMAXSORTBUF
#else
#define CTSORTBUF	16000
#endif

#define CTLISTBLK	16384		/* list   alloc block size	*/
#define CTLISTBUF	64000		/* buffer alloc block size	*/
#define CTDELSIZ	((UINT) 32768)	/* ct_del[] size		*/
#else
#define ctCPYFILBUF	49152

#ifdef ctMAXSORTBUF
#define	CTSORTBUF       ctMAXSORTBUF
#else
#define CTSORTBUF	16000
#endif

#define CTLISTBLK	2048		/* list   alloc block size	  */
#define CTDELSIZ	((UINT) 2048)	/* ct_del[] size (must be >= 512) */
#endif

#define COMMONOWN	ct_cmnown


/* ************	     ctNOGLOBALS REQUIRES CTS_ISAM	  ************* */
#ifdef ctNOGLOBALS
#ifndef CTS_ISAM
#define CTS_ISAM
#endif
#ifndef ISAM_VARS
#define ISAM_VARS
#endif
#endif

/* *********	    DISABLE FEATURES DEPENDENT ON CTS_ISAM      ******** */
#ifndef CTS_ISAM

#ifdef RTREE
#undef RTREE
#define NO_RTREE
#endif

#ifdef CTBATCH
#undef CTBATCH
#define NO_BATCH
#endif

#ifdef PARMFILE
#undef PARMFILE
#define NO_PARMF
#endif

#ifdef ctICONTEXT
#undef ctICONTEXT
#define NO_CONTEXT
#endif

#ifdef ctCONDIDX
#undef ctCONDIDX
#define NO_CONDIDX
#endif

#ifdef CTHISTORY
#undef CTHISTORY
#define NO_HISTORY
#endif

#endif /* ~CTS_ISAM */



/* ***********        FPUTONLY NO LONGER SUPPORTED          *********** */
#ifdef FPUTONLY
This configuartion option is no longer supported. Use NOTFORCE and
a file mode including ctWRITETHRU to force updates (on a file by file basis)
to disk. DO NOT USE ctWRITETHRU WITH A FILE SUPPORTING TRANSACTION LOGGING.
#endif

/* ***********          NO_BOUND IMPLIES NOTFORCE          *********** */
#ifndef CTBOUND
#ifdef FPUTFGET
#undef FPUTFGET
#define NOTFORCE
#endif
#endif

/* ***********        CTSUPER & RESOURCE IMPLY VARLDATA    *********** */
#ifdef CTSUPER
#ifndef VARLDATA
#define VARLDATA
#endif
#endif
#ifdef RESOURCE
#ifndef VARLDATA
#define VARLDATA
#endif
#endif

/* ***********          ctCONDIDX REQUIRES RESOURCE         *********** */
#ifndef RESOURCE
#ifdef ctCONDIDX
#undef ctCONDIDX
#define NO_CONDIDX
#endif
#endif

#ifdef ctCONDIDX
#ifdef ctHUGEFILE
#define ctDROPCOND
#endif
#endif

/* ***********       ctFeatDATFLT REQUIRES ctCONDIDX        *********** */
#ifndef ctCONDIDX
#ifdef  ctFeatDATFLT
#undef  ctFeatDATFLT
#endif
#endif

/* ***********       FPUTFGET CANNOT SUPPORT TRANPROC       *********** */
#ifdef FPUTFGET
#ifdef TRANPROC
#undef TRANPROC
#endif
#endif

/* ***********    DEFINE MLTORTRN IF MULTITRD OR TRANPROC   *********** */
#undef MLTORTRN
#ifdef MULTITRD
#define MLTORTRN
#endif
#ifdef TRANPROC
#ifndef MLTORTRN
#define MLTORTRN
#endif
#endif

/* ***********   CTSERVER & MULTITRD ARE MUTUALLY EXCLUSIVE  ********* */
#ifdef CTSERVER
#ifdef MULTITRD
	*** CTSERVER & MULTITRD are mutually exclusive ***
#endif
#endif

/* ***********  GNSERVER indicates either CTSERVER or MULTITRD  ****** */
#ifdef GNSERVER
#undef GNSERVER
#endif
#ifdef CTSERVER
#define GNSERVER
#endif
#ifdef MULTITRD
#define GNSERVER
#endif

/* ***********     FPUTFGET CANNOT BE USED WITH THE SERVER    ********* */
#ifdef GNSERVER
#ifdef FPUTFGET
#undef FPUTFGET
#define NOTFORCE
#endif
#endif

/* ***********   MUSTFRCE indicates multi-user requirements  ********* */
#ifdef MUSTFRCE
#undef MUSTFRCE
#endif
#ifdef FPUTFGET
#define MUSTFRCE
#endif
#ifdef GNSERVER
#define MUSTFRCE
#endif

/* ***********    DEFINE MFCORTRN IF MUSTFRCE OR TRANPROC   *********** */
#undef MFCORTRN
#ifdef MUSTFRCE
#define MFCORTRN
#endif
#ifdef TRANPROC
#ifndef MFCORTRN
#define MFCORTRN
#endif
#endif

/*
** determine if special unique file ID index is required
*/
#ifdef ctSRVR
#define ctNEEDinamidx
#endif
#ifdef TRANPROC
#ifndef ctNEEDinamidx
#define ctNEEDinamidx
#endif
#endif


/*
** ctFeatRECRLOCK requires MUSTFRCE support
*/
#ifdef  ctFeatRECRLOCK
#ifndef MUSTFRCE
#undef  ctFeatRECRLOCK
#endif
#endif

/*
** ctBEHAV_SKPLOK_EXCL requires MULTITRD support and ctFeatSrvLockFile
*/
#ifdef ctBEHAV_SKPLOK_EXCL
#if !defined(MULTITRD) || !defined(ctFeatSrvLockFile)
#undef ctBEHAV_SKPLOK_EXCL
#endif
#endif
#if defined(ctBEHAV_SKPLOK_EXCLtran) && !defined(ctBEHAV_SKPLOK_EXCL)
#undef ctBEHAV_SKPLOK_EXCLtran
#endif

/*
** ctBEHAV_HOST_MEMBER_LOCK requires MUSTFRCE support
*/
#ifdef ctBEHAV_HOST_MEMBER_LOCK
#ifndef MUSTFRCE
#undef ctBEHAV_HOST_MEMBER_LOCK
#endif
#endif

/*
** ctBEHAV_NO_USER_LOCKS requires NO MUSTFRCE (i.e., single user) support
*/
#ifdef ctBEHAV_NO_USER_LOCKS
#ifdef MUSTFRCE
#undef ctBEHAV_NO_USER_LOCKS
#endif
#endif

/*
** ctFeatPERMISSIONS requires ctSRVR support
*/
#ifdef  ctFeatPERMISSIONS
#ifndef ctSRVR
#undef  ctFeatPERMISSIONS
#endif
#endif

/*
** ctFeatFILEUSRLST, ctFeatFILEBLOCK and ctFeatQUIET require MULTITRD support,
** and ctFeatFILEBLOCK and/or ctFeatMAX_USER_LOGS and/or ctFeatTRAN_TIMEOUT
** forces ctWORKMON support
*/

#ifndef MULTITRD
#ifdef ctFeatFILEUSRLST
#undef ctFeatFILEUSRLST
#endif
#ifdef ctFeatFILEBLOCK
#undef ctFeatFILEBLOCK
#endif
#ifdef ctFeatQUIET
#undef ctFeatQUIET
#endif
#endif

#ifdef ctFeatFILEBLOCK
#define FILEBLOCK_TEST(x) (x)
#ifndef ctWORKMON
#define ctWORKMON
#endif
#else
#define FILEBLOCK_TEST(x) (0)
#endif
#ifdef ctFeatMAX_USER_LOGS
#ifndef ctWORKMON
#define ctWORKMON
#endif
#endif
#ifdef ctFeatTRAN_TIMEOUT
#ifndef ctWORKMON
#define ctWORKMON
#endif
#endif

/*
** ctFeatQUIET does not use ctBNDentryPointMutex; check for ctFeatSRVDLL
*/
#ifdef ctFeatQUIET
#define QUIET_TEST(x) (x)
#ifdef ctBNDentryPointMutex
#undef ctBNDentryPointMutex
#endif
#ifdef ctFeatSRVDLL
#define ctTESTsrvdllquiet
#endif
#else
#define QUIET_TEST(x) (0)
#endif

/* Connection group indicator */
#define ctCONNGROUPCHR (TEXT)0xa0

/*
** Connection group support requires communication protocol and
** cache memory support.
*/
#if !defined(ctFeatCTSRVR_COMMP) || !defined(ctCACHE_MEMORY)
#undef ctFeatCONNGROUP
#endif


/*
** redefine tstifnmcls/tstbfnm to tstifnm/tstfnm if no ctFeatFILEBLOCK
*/
#ifndef ctFeatFILEBLOCK
#ifdef MULTITRD
#define tstbfnm(sysno,usrno,thrd)	tstfnm(sysno,thrd)
#define tstifnmcls(usrno,cloze,thrd)	tstifnm(usrno,thrd)
#else
#ifdef ctMTFPGreentrant
#define tstbfnm(sysno,usrno,thrd)	tstfnm(sysno,ctWNGV)
#define tstifnmcls(usrno,cloze,thrd)	tstifnm(usrno,ctWNGV)
#else
#define tstbfnm(sysno,usrno,thrd)	tstfnm(sysno)
#define tstifnmcls(usrno,cloze,thrd)	tstfnm(usrno)
#endif
#endif
#endif


#ifndef ctPREV_610A_FLUSH

/* ***********         DOSFLUSH APPLIES TO ALL MODELS        ********* */
#ifndef DOSFLUSH
#define DOSFLUSH
#endif

#else

/* ***********       DOSFLUSH APPLIES ONLY TO FPUTFGET       ********* */
#ifdef NOTFORCE
#ifdef DOSFLUSH
#undef  DOSFLUSH
#define NO_FLUSH
#endif
#endif

#endif

/* ***********       CTASYNCR APPLIES ONLY TO MULTITRD       ********** */
#ifdef CTASYNCR
#ifndef MULTITRD
#undef CTASYNCR
#endif
#endif

/* *************              UNIFRMAT SUPPORT             ************* */
#ifdef UNIFRMAT
#ifdef LOW_HIGH
#define UNIFRMAT_HL_DISK	/* HIGH_LOW on disk */
#else
#define UNIFRMAT_LH_DISK	/* LOW_HIGH on disk */
#endif
#endif

/* *************     UNIFRMAT DOES NOT SUPPORT TRANPROC    ************* */
#ifdef UNIFRMAT
#ifdef TRANPROC
---- cannot compile a UNIFRMAT/TRANPROC c-tree LIBRARY ----
#endif
#endif

/* **************     DEFAULT FPUTFGET LOCKING MODELS     ************* */
#define ctLOCK_BLOCK	1		/* used in calls to ctfpglok81 */
#define ctLOCK_NBLCK	2
#define ctLOCK_UNLCK	4
#define ctLOCK_READ	8		/* read lock */
#define ctLOCK_CHECK	16		 


#ifdef FPUTFGET
#ifndef ctMAX_USRLOKS
#define ctMAX_USRLOKS	((ULONG)512)		/* users */
#endif
#ifndef ctMAX_MBRLOKS
#define ctMAX_MBRLOKS	((ULONG)1024)		/* superfile members */
#endif


#ifdef ctHUGEFILE

#ifndef ctLOCK_TOP
#if defined(ctPortWIN32) 

#define ctLOCK_TOPhw	(ct_lock_tophw)
#define ctLOCK_TOP	(ct_lock_top)	/* runtime 4GB or (4GB * 2GB) limit */

#elif defined(ctBEHAV_FPGIOLOK)

#define ctLOCK_TOPhw	((ULONG)0x7fffffff)
#define ctLOCK_TOP	((ULONG)0xffffffff)

#else /* ~ctPortWIN32 && ~ctBEHAV_FPGIOLOK */

#define ctLOCK_TOPhw	((ULONG)0x00000000)
#define ctLOCK_TOP	((ULONG)0x7fffffff)	/* 2GB limit */

#endif /* ~ctPortWIN32 */
#endif /* ~ctLOCK_TOP */

#define ctLOCK_OFFSEThw	 ctLOCK_TOPhw
#define ctLOCK_OFFSETlw	(ctLOCK_TOP   - (ctMAX_MBRLOKS * ctMAX_USRLOKS))

#else  /* ~ctHUGEFILE */

#ifndef ctLOCK_TOP
#ifdef ctPortWIN32
#define ctLOCK_TOP	((ULONG)0xffffffff)	/* 4GB limit */
#else
#ifdef ctFeat_LARGE_FILES
#define ctLOCK_TOP	((ULONG)0xffffffff)	/* 4GB limit */
#else
#define ctLOCK_TOP	((ULONG)0x7fffffff)	/* 2GB limit */
#endif
#endif
#endif /* ~ctLOCK_TOP */

#define ctLOCK_OFFSET	(ctLOCK_TOP - (ctMAX_MBRLOKS * ctMAX_USRLOKS))

#endif /* ~ctHUGEFILE */


#ifndef ctLOCK_OFFSETgps
#define ctLOCK_OFFSETgps	(0x40000000L)
#endif

#ifndef ctLOCK_EXTENDED
#ifndef ctLOCK_DIRECT
#ifndef ctLOCK_DUMMY
#ifndef ctLOCK_EXTENDEDgps

#ifdef ctBEHAV_FPGIOLOK
#define ctLOCK_EXTENDED
#elif defined(ctPortUNIX)
#define ctLOCK_DIRECT
#else
#define ctLOCK_EXTENDED
#endif

#endif /* ~ctLOCK_EXTENDEDgps */
#endif /* ~ctLOCK_DUMMY */
#endif /* ~ctLOCK_DIRECT */
#endif /* ~ctLOCK_EXTENDED */

#ifdef ctBEHAV_FPGIOLOK
#ifndef ctLOCK_EXTENDED
#error ctLOCK_EXTENDED required for correct unix locking
#endif
#endif

#if defined(ctPortUNIX) || defined(ctBEHAV_WIN32unxlok)
#ifdef 	ctMTFPG
#ifndef ctMTFPG_LOKCNF
#define ctMTFPG_LOKCNF
#endif
#endif /* ctMTFPG */
#endif /* ctPortUNIX */

/*----------------------------------------------------------------------------
   In the multi-threaded multi-user operational model, we use system locking.
   If system locking operates at the process level, not the thread level, we
   turn on #define ctMTFPG_LOKCNF to compensate for this behavior. If thread
   safety is also enabled in this model, we turn on ctBEHAV_MTFPG_LOKSRL
   in order to serialize read/write of the lock list for all connections,
   since one connection will read the lock list of another connection.
----------------------------------------------------------------------------*/
#if defined(ctMTFPG_LOKCNF) && defined(ctMTFPGreentrant)

#ifdef NO_ctBEHAV_MTFPG_LOKSRL
#error Inter-thread lock conflict detection with reentrant support requires lock list serialization
#endif

#define ctBEHAV_MTFPG_LOKSRL

#endif

#ifdef ctBEHAV_MTFPG_LOKSRL

#ifdef ctDYNHASH
#error Lock table state serialization is not yet supported with dynamic hash
#endif

#ifndef ctNOGLOBALS
#error Lock table state serialization requires ctNOGLOBALS support
#endif

#ifdef ctBEHAV_MULTIOPN_SAMUSR
#error Lock table state serialization is not yet supported with ctBEHAV_MULTIOPN_SAMUSR
#endif

/* Segmented files are not supported when lock table state serialization is required. */
#undef ctHUGEFILEsegm

/* ctserl_loc() locale codes, stored in SRLK_loc global variable: */
#define SRLKctuutbl81	1
#define SRLKctumtbl81	2
#define SRLKcturtbl	3
#define SRLKctulchk81	4
#define SRLKctuftbl	5
#define SRLKchkutbl81	6
#define SRLKctultbl81	7
#define SRLKctfilok	8
#define SRLKLKISAM	9
#define SRLKLOKREC	10
#define SRLKUDLOCK81	11
#define SRLKUNLOCK81	12
#define SRLKmbclosx	13
#define SRLKctsysio81	14

/* Boundary value for high word of offset in user lock table lock and unlock
calls. We compare the high word to this value. For a physical address, we
expect the high word to be less than this value. For a virtual address, we
expect the high word to be greater than this value. */
#define LOKSRLHWBND	0x3fffffff

#endif /* ctBEHAV_MTFPG_LOKSRL */

#ifndef ctLOCK_DUMMY

#define CTSUPER_noMBRLOCK	/* No superfile members exclusive by default*/
#ifndef CTSUPER_noMBRLOCK
#ifndef CTSUPER_MBRLOCK
#define CTSUPER_MBRLOCK
#endif
#endif

#ifndef ctLOKCNT
#define ctLOKCNT
#endif

#endif /* ~ctLOCK_DUMMY */

/*----------------------------------------------------------------------------
  ctBEHAV_FPUTFGET_READFIL ensures that when a file is open in read-only mode
  (ctREADFIL) in the FPUTFGET model on a Unix system, a shared (ctSHARED) open
  will fail, and vice-versa.

  Enabled by default for Unix systems in FPUTFGET mode.
----------------------------------------------------------------------------*/
#ifdef ctPortUNIX
#ifndef NO_ctBEHAV_FPUTFGET_READFIL
#define ctBEHAV_FPUTFGET_READFIL
#endif
#endif

#endif /* FPUTFGET */

/* ************* ************* ************* ************ ************* */


#define PERMFLAG	(ctVLENGTH | ctPREIMG | ctLOGFIL | ctWRITETHRU | ctCHECKLOCK | ctSUPERFILE | ctCHECKREAD | ctLOGIDX)

#ifndef NUMCHANEL
#define NUMCHANEL	2	/* # io channels per file when ctDUPCHANEL on */
#endif
#define MRKSIZ		4	/* exceptional element bytes per mark */
#define MRKSIZ2		6
#ifdef ctFeat6BT
#define MRKSIZX MRKSIZ2
#else
#define MRKSIZX MRKSIZ
#endif

#ifndef MAXLEV
#define MAXLEV		15	/* maximum height of B-Tree + 1		*/
#endif

#define	VARI_LEN	(ctSIZE(VRLEN) + 2 * ctSIZE(LONG))
#ifdef ctHUGEFILE
#define	VARI_LEN8	(ctSIZE(VRLEN) + 3 * ctSIZE(LONG))
#define VARI_LENX	VARI_LEN8
#else
#define VARI_LENX	VARI_LEN
#endif

#define ctNODEhdr	18
#define ctNODEhdr8	28

/*
**	size of permanent header information
**
**	HDRSIZ * ctHDRSCL is the V7/V8 header size. HDRSIZ is the V6
**	header size. V7 can process both V6 and V7 files. V8
**	can process V6, V7 & V8 files.
**	ctHDRUSE is the number of bytes actually in use with V7/V8 files
**	at the time of system compile. The rest of the header is
**	available for new header information. This remaining padding
**	should be all zeroes.
*/
#define HDRSIZ		128
#define ctHDRSCL	4			/* 512 byte header	*/
#define ctHDRUSE	456			/* bytes in use (0x1c8)
						** are based on
						** FC_DAR_NBR == 8
						*/
#define ctHDRPAD	(ctHDRSCL * HDRSIZ - ctHDRUSE)

/*
** NOTE: if PWZ is changed, then examine all uses of PDZ in structure
**	 definitions. As originally defined, PWZ + PDZ is a multiple of
**	 four.
**
**	 It is NOT recommended to change IDZ or PWZ since resource
**	 definitions will be affected, unless backward compatibility
**	 is not an issue.
*/
#define PDZ	2	 /* padding size */
#define EXZ	8	 /* Maximum IFIL name extension size		   */
#define PWZ	10	 /* Maximum password length (including terminator) */
#ifdef IDZsmallpage
#define IDZ	IDZsmallpage
#else
#define IDZ	32	 /* Maximum ID name length  (including terminator) */
#endif
#define DSZ	64	 /* group/user description information		   */
#ifdef ctFeatMAX_NAME_4K
#define FNZ	(MAX_NAME+1) /* parm block maximum name size		   */
#else
#define FNZ	256	 /* parm block maximum name size		   */
#endif
#define FNZW	(ctWCHARsiz * FNZ)
			 /* maximum multibyte name size			   */
#define ctSESSLEN 8	 /* SESSVAL passkey length			   */

/*
** ctMAXPASSLEN is the size of a buffer which holds a password to be
** passed to INTISAMX.
*/
#ifdef ctFeatLONG_PASSWORD
#define ctMAXPASSLEN	IDZ
#else
#define ctMAXPASSLEN	PWZ
#endif

#ifdef ctPortVINES
#define STZ	64	 /* streettalk length  				   */
#endif

#ifdef  MUSTFRCE
#define PRDRPEAT	10	/* # of times to retry predsr node	*/
#else
#define PRDRPEAT	0
#endif

typedef struct ugrup {
	NLONG	 groupnm;	/* system dependent group number*/
	TEXT	 groupid[IDZ];	/* ASCIIZ group id		*/
	} UGRUP;
#ifdef ctSP
typedef UGRUP far   *	pUGRUP;
#else
typedef UGRUP ctMEM *	pUGRUP;
#endif
#ifndef MAX_UGRUP
#define MAX_UGRUP	128	/* maximum number of user groups	*/
#endif

#ifndef CTBOUND

#define MAXVABS			3		/* input segments */
#define OUTSEG			(MAXVABS + 1)	/* output segment */
#define BEGMSG_OFFSET		(OUTSEG * ctSIZE(VRLEN))
#define INPUT_OFFSET		(BEGMSG_OFFSET + reqPARMBz) /* input data offset with 4-byte file number and huge file support */
#define OUTPUT_OFFSET		(BEGMSG_OFFSET + rspPARMBz) /* output data offset with 4-byte file number and huge file support */

#define INPUT_OFFSETH		(BEGMSG_OFFSET + reqPARMBzH) /* input data offset with huge file support */
#define OUTPUT_OFFSETH		(BEGMSG_OFFSET + rspPARMBzH) /* output data offset with huge file support */

#define INPUT_OFFSET4		(BEGMSG_OFFSET + reqPARMBz4) /* input data offset without huge file support */
#define OUTPUT_OFFSET4		(BEGMSG_OFFSET + rspPARMBz4) /* output data offset without huge file support */

#define MsgLen(mp,i)		*(((VRLEN *) mp) + i - 1)

#ifdef ctFeatCTSRVR_COMMP
#ifndef ctDBG_MsgLen
#define setMsgLen(tp,seg,loc,val)  MsgLen(tp,seg)  = val
#define addMsgLen(tp,seg,loc,val)  MsgLen(tp,seg) += (val)
#define getMsgLen(tp,seg)	   MsgLen(tp,seg)
#endif
#else
#define setMsgLen(tp,seg,loc,val)
#endif

/*^*****************************************************************/
/* LastOUTSEGvalue  1098  used by JAK				   */
/*~*****************************************************************/

#endif /* ~CTBOUND */

#ifndef ctrt_fwrite
#ifndef ctFWRITE
#define ctrt_fwrite	fwrite
#endif
#endif

#ifndef ctrt_fread
#ifndef ctFREAD
#define ctrt_fread	fread
#endif
#endif

#ifndef ctrt_fseek
#ifndef ctFSEEK
#define ctrt_fseek	fseek
#endif
#endif

#ifndef ctrt_setcwd
#define ctrt_setcwd	chdir
#endif

/*
** file copy system commands
*/
#ifdef copycmd
#undef copycmd
#endif
#ifdef ctPortWIN32
#define copycmd	"copy"
#endif
#ifdef ctPortUNIX
#define copycmd "cp"
#endif
#ifdef ctPortNLM
#define copycmd	"copy"
#endif


/* ******************************************************************** */
/* ***			SYMBOLIC CONSTANTS			   ***  */
/* ******************************************************************** */

#define ctREAD_COMPLETE	1
#define ctREAD_PARTIAL	2

#define	DRNZERO	 	(ctRECPT) 0
#define	NODEZERO	(LONG   ) 0

	/* 1st 2 nibbles used by suptyp & mstatus			*/
#define ctTRANAUXindex	0x0008	/* modify suptyp with idx indicator	*/
#define ctTRANAUXrstdel	0x0100	/* RSTRDEL				*/
#define ctTRANAUXtrndep	0x0200	/* TRANDEP				*/
#define ctTRANAUXhugfil	0x0400	/* Huge File				*/
#define ctTRANAUXtrncre	0x0800	/* just created TRANDEP (uncommitted)	*/
#define ctTRANAUXsetseg	0x1000	/* ctSETSEG transaction entries		*/
#define ctTRANAUXanyseg 0x2000	/* any type SEG transaction entry	*/
#define ctTRANAUXiict	0x4000	/* IICT entry				*/

#define MIRRORD	 	0x0001	/* xflmod: file is mirrored		    */
#define ctFRC2HDRSxfl	0x0002	/* xflmod: force 256 byte (V7) header	    */
#define ctPREIMAGE	0x0004	/* xflmod: TRNLOG swap during Dyn Dump	    */
#define ctFILESEGMxfl	0x0008	/* xflmod: segmented file		    */
#define ctTRANDEPxfl	0x0010	/* xflmod: tran dependent create/delete	    */
#define ctTEMPFILE	0x0020	/* xflmod: file created as special temp	    */
#define ctFILEPOS8xfl	0x0040	/* xflmod: file may exceed 4GB		    */
#define ctNOSPACHKxfl	0x0080	/* xflmod: do not check for disk full	    */
#define ctNOENCRYPxfl	0x0100	/* xflmod: do not create with encryption    */
#define ctTRANMODExfl	0x0200	/* xflmod: auto switch to ctLOGFIL	    */
#define ctPIMGMODExfl	0x0400	/* xflmod: auto switch to ctSHADOW	    */
#define ctRSTRDELxfl	0x0800	/* xflmod: tran dependent restorable delete */
#define ctSRVFILE	0x1000	/* xflmod: server/service write-only file   */

#define ctAUTOMODExfl	(ctTRANMODExfl | ctPIMGMODExfl)
#define ctRBLDXFLM	ctAUTOMODExfl

/*			0x8000     xflmod: NOT TO BE USED,		    */
/*					   but MSB of verson is available   */
/*					   for additional file mode bits    */

#define ctLOCLSSS	0x00010000	/* suspend SRLSEG (amsk)	    */
#define ctLOCLCIDX	0x00020000	/* pending UPDCIDX (amsk)	    */
#define ctLOCLCNVT38	0x00040000	/* use server-side ctconvert38	    */

/*
** internal XCREblk entries: not for use by application
*/
#define ctPARTMMBR	0x01000000L	/* partition member file	    */
#define ctPARTUNIQ	0x02000000L	/* global unique indices exist	    */
#define ctPARTSRLG	0x04000000L	/* global SRLSEG indices exist	    */
#define ctINDXUNIQ	0x08000000L	/* this index requires global uniq  */

#define ctLOCL2HDR	0x0080	/* client side indicator in amsk	    */
#define ctLOCLHOST	0x0100	/* client side partition host amsk	    */
#define ctLOCLNOISMKEYUPD 0x0200 /* client side no ISAM key update indicator */
#define ctLOCLDFRIDX	0x0400 /* client side deferred index indicator    */

#define ctTESTHUGE	ctFILEPOS8xfl
#define ctTEST2HDR	(ctTESTHUGE | ctFILESEGMxfl | ctFRC2HDRSxfl)
#define ctTESTmHDR	(ctTESTHUGE | ctFRC2HDRSxfl)
#define ctSETmHDR	(ctTESTHUGE | ctTRANDEPxfl  | ctFRC2HDRSxfl | ctRSTRDELxfl)
#define ctTEST8HDR	(ctFILEPOS8 | ctFILESEGM | ctFRC2HDRS | ctLEXTSIZE | ctFEXTSIZE | ctMAXFILEZ | ctSPACEAVL | ctPARTHOST | ctPARTMMBR | ctADD2END | ct6BTRAN)
#define ctPARTTEST	(ctPARTHOST | ctPARTAUTO)
#define ctTESTfmd2	(ct6BTRAN)	/* cresmem XCREblk need */

#define ctADMOPEN	 	0x1000	/* flmode */

/*
** tflmod
*/
#define ctHDRSIZflg	((LONG) 0x000001)/* tflmod:header already resized     */
#define ctFILEXISTflg	((LONG) 0x000002)/* tflmod:testing file existence     */
#define ctRBLINDX	((LONG) 0x000004)/* tflmod */
#define ctISAMKOFF	((LONG) 0x000008)/* tflmod */
#define ctRCVCREflg	((LONG) 0x000010)/* tflmod */
#define ctOPNCREflg	((LONG) 0x000020)/* tflmod */
#define ctGETCAMflg	((LONG) 0x000040)/* tflmod */
#define ctFXTSIZflg	((LONG) 0x000080)/* tflmod */
#define ctGETSEGflg	((LONG) 0x000100)/* tflmod */
#define ctLOGMIRflg	((LONG) 0x000200)/* tflmod */
#define ctSPLCREflg	((LONG) 0x000400)/* tflmod */
#define ctSRVDIRflg	((LONG) 0x000800)/* tflmod:SERVER_DIRECTORY prepended */
#define ctDFRCLSflg	((LONG) 0x001000)/* tflmod:CLSFIL defered until commit*/
#define ctDFRDELflg	((LONG) 0x002000)/* tflmod:DELFIL defered until commit*/
#define ctDBGANLflg	((LONG) 0x004000)/* tflmod:select for ANL debug       */
#define ctFPGXCLflg	((LONG) 0x008000)/* tflmod:FPG exclusive open (~THRU) */
#define ctLOGFILflg	((LONG)0x0010000)/* tflmod:log file open/create	      */
#define ctWRTHRUflg	((LONG)0x0020000)/* tflmod:preimg data file write thru*/
#define ctTRANDEPsfm	((LONG)0x0040000)/* tflmod:TRANDEP del with MBR_SUPER */
#define ctTRANDEPflg	((LONG)0x0080000)/* tflmod:just created TRANDEP file  */
#define ctTRANDEPund	((LONG)0x0100000)/* tflmod:undoing TRANDEP create     */
#define ctTRANDEPdel	((LONG)0x0200000)/* tflmod:end stage TRANDEP delete   */
#define ctTRANDEPism	((LONG)0x0400000)/* tflmod:ISAM level file	      */
#define ctDIRMIRflg	((LONG)0x0800000)/* tflmod:ctspcopn called for mirror */
#define ctTRANDEPcls	((LONG)0x1000000)/* tflmod:close restorable temp      */
#define ctSYSLOGsup	((LONG)0x2000000)/* tflmod:suppress SYSLOG entry      */
#define ctSPACMGTflg	((LONG)0x4000000)/* tflmod:VLENGTH spc mgt operation  */
#define ctMCLSERRflg    ((LONG)0x8000000)/* tflmod: low level error on mirror */
#define ctOSIOLOKflg	((LONG)0x10000000)/*tflmod: need IOlock to force cache*/
#define ctRECLAIMflg	((LONG)0x20000000)/*tflmod: reclaim message posted    */
#define ctDROPIDXflg	((LONG)0x40000000)/*tflmod: dropidx flag	      */
#define ctDROPIDXcls	((LONG)0x80000000)/*tflmod: dropidx pending: closed   */

#define tflmodTRANDEP	(ctTRANDEPflg | ctTRANDEPund | ctTRANDEPdel | ctTRANDEPism)

/*
** tflmod2
*/
#define ctUPDPARTflg2	((LONG)0x00000001) /* partition resource must be upd  */
#define ctHOSTOPNflg2	((LONG)0x00000002) /* partition opened by host	      */
#define ctEXSPARTflg2	((LONG)0x00000004) /* partition existence must be upd */
#define ctHOSTKEYflg2	((LONG)0x00000008) /* operate directly on host index  */
#define ctNODCLSPflg2	((LONG)0x00000010) /* file close buffer loop	      */
#define ctRCVRDELflg2	((LONG)0x00000020) /* delete during recovery	      */
#define ctNOCACHEflg2	((LONG)0x00000040) /* turn off data caching for file  */
#define ctHDRLOK0flg2	((LONG)0x00000080) /* HUGE header lock at 0x0	      */
#define ctHDRLOKcflg2	((LONG)0x00000100) /* HUGE header lock at 0xc	      */
#define ctNOFLUSHflg2	((LONG)0x00000200) /* stop file flush during shutdown */
#define ctNOVTCLSflg2	((LONG)0x00000400) /* protect file from vtclose	      */
#define ctRBLINDXflg2	((LONG)0x00000800) /* on index rebuild list: ctrebhed */
#define ctSPECLROflg2	((LONG)0x00001000) /* file's OS property set to RO    */
#define ctCLNOPENflg2	((LONG)0x00002000) /* opened with clean updflg in rcv */
#define ctCHANNELflg2	((LONG)0x00004000) /* # of IO channels specified      */
#define ctSNAPSHOTflg2	((LONG)0x00008000) /* activated for snapshot	      */
#define ctKEEPOPENflg2	((LONG)0x00010000) /* file stays opn after last close */
#define ctMBRSUPERflg2	((LONG)0x00020000) /* sticky MBR_SUPER bit	      */
#define ctBLANKLOGflg2	((LONG)0x00040000) /* blank log processed	      */
#define ctOSWRITETHRUflg2 ((LONG)0x00080000) /* open using OS write thru attr */
#define ctFLUSHEXTflg2	((LONG)0x00100000) /* must flush after extension      */
#define ctSUSSRLSEGflg2 ((LONG)0x00200000) /* suspend SRLSEG handling	      */
#define ctREPLICATEidx2	((LONG)0x00400000) /* unique index replicate flag     */
#define ctREPLICATEcfg2 ((LONG)0x00800000) /* replication specified in config */
#define ctRCVOPNHDRflg2	((LONG)0x01000000) /* ctrcvopn changed BEGCTL	      */
#define ctDBGCMTLOKflg2	((LONG)0x02000000) /* debugging ctBEHAV_CMTLOK	      */
#define ctXKYBUFflg2	((LONG)0x04000000) /* missing ISAM key buffer info    */
#define ctSYNCIOflg2	((LONG)0x08000000) /* O_SYNC I/O operations for file  */
#define ctOPNTRANflg2	((LONG)0x10000000) /* Defer OPNTRAN until r/w open    */
#define ctREC2FIXflg2	((LONG)0x20000000) /* reset phy/numrec2 message	      */
#define ctNONMTCSEGflg2	((LONG)0x40000000) /* unexpected, nonmatching segment */
#define ctBLKROPNflg2	((LONG)0x80000000) /* file opened for file blocker    */

/*
** tflmod3
*/
#define ctCLOSE_FDflg3	((LONG)0x00000001) /* sys level fd closed (ocsema)    */
#define ctINCHKPNTflg3	((LONG)0x00000002) /* file included in last checkpoint*/
#define ctFILCREflg3	((LONG)0x00000004) /* file creation in progress	      */
#define ctWRTHDRADJflg3	((LONG)0x00000008) /* wrthdradj redhdr request	      */
#define ctBLKMBROPNflg3	((LONG)0x00000010) /* blocker opened superfile mbr    */
#define ctRSVBLKFCBflg3	((LONG)0x00000020) /* reserve blocked FCB	      */
#define ctPUTHDRXCLflg3	((LONG)0x00000040) /* PUTHDR: stay exclusive	      */
#define ctLTO_DIAGflg3	((LONG)0x00000080) /* timeout diagnostics	      */
#define ctSKPLOKflg3	((LONG)0x00000100) /* skip write locks		      */
#define ctCLNIDXXflg3	((LONG)0x00000200) /* on the fly CLNIDXX in process   */
#define ctSETNUMENTflg3	((LONG)0x00000400) /* nument set during recovery      */
#define ctDYNHASHflg3	((LONG)0x00000800) /* skip dynamic dehash	      */
#define ctIDfield_flg3	((LONG)0x00001000) /* IDfield chkpnt processing	      */
#define ctGETDARflg3	((LONG)0x00002000) /* recvry/rbld expects to get DARs */
#define ctUNBUFFIOflg3	((LONG)0x00004000) /* unbuffered I/O		      */
#define ctSKIPSAVEflg3	((LONG)0x00008000) /* skip ctsave for this file	      */
#define ctDATARECDflg3	((LONG)0x00010000) /* rebuild found active data rec   */
#define ctIDfieldVflg3	((LONG)0x00020000) /* IDfield override		      */
#define ctRBLDSRLGflg3	((LONG)0x00040000) /* SRLSEG update: wrthdr	      */
#define ctRBLOGKEYflg3	((LONG)0x00080000) /* unexpected call to ctlogkey81   */
#define ctDBGHDRLKflg3	((LONG)0x00100000) /* skip ctDBGhdrlok I/O check      */
#define ctCMPRECCHKflg3	((LONG)0x00200000) /* include in CMPREC chkpnt list   */
#define ctKOCLOSEflg3	((LONG)0x00400000) /* KEEPOPEN file w/close pending   */
#define ctLTFLMAPflg3	((LONG)0x00800000) /* repl unq key set but no LTFLMAP */
#define ctMBRUPDflg3	((LONG)0x01000000) /* like fupd for file members      */
#define ctPRTENTCHKflg3	((LONG)0x02000000) /* include in PRTENT chkpnt list   */
#define ctTOUCHEDflg3	((LONG)0x04000000) /* touched: must set/reset locally */
#define ctAUTOMKDRflg3	((LONG)0x08000000) /* create directories if needed    */
#define ctPRTHSTCHKflg3	((LONG)0x10000000) /* include in PRTHST chkpnt list   */
#define ctFCBSTKflg3	((LONG)0x20000000) /* file on FCB available stack     */
#define ctISAMFILflg3	((LONG)0x40000000) /* non-MULTITRD ctXTMD_ISAM	      */
#define ctADDUNQFRSflg3	((LONG)0x80000000) /* ISAM add unique keys first      */

/*
** tflmod4
*/
#define ctIDfieldPflg4	((LONG)0x00000001) /* preserve IDfield value	      */
#define ctCHKPNTUPDflg4	((LONG)0x00000002) /* header updated by CHKPNT	      */
#define ctCLSTRANflg4	((LONG)0x00000004) /* transcn81 clean CLSTRAN	      */
#define ctRCVOPNUPDflg4	((LONG)0x00000008) /* header updated by ctrcvopn81    */
#define ctPRIMETHRDflg4	((LONG)0x00000010) /* is open by cache priming thread */
#define ctUPDTROROflg4	((LONG)0x00000020) /* update before conv to RORO      */
#define ctFILECLSDflg4	((LONG)0x00000040) /* file close detected during auto **
					   ** recovery			      */
#define ctRCVRCLSflg4	((LONG)0x00000080) /* iclsfilx called from trancls    */
#define ctDFRIDXCHKflg4	((LONG)0x00000100) /* include in DFRIDX chkpnt list   */
#define ctRUCBOPNflg4	((LONG)0x00000200) /* standalone mode: record update
					   ** file open callback function has
					   ** been called for this file	      */
#define ctCHECKLOCKflg4	((LONG)0x00000400) /* CHECKLOCK enabled by config     */
#define ctNOFLUSHflg4	((LONG)0x00000800) /* no-flush enabled by config      */
#define ctNORUCBOKflg4	((LONG)0x00001000) /* allow file open without RUCB DLL*/

/*
** tflstt: unlike tflmod2, tflstt requires synchronization
*/
#define ctDYNDMPmod	((LONG) 0x000001)/* tflstt:dynamic dump status flag   */
#define ctWRTHRUupd	((LONG) 0x000002)/* tflstt:preimg file write thru upd */
#define ctHOSTOPEN	((LONG) 0x000004)/* tflstt:			      */
#define ctREDFILflg	((LONG) 0x000008)/* tflstt:force read only during dump*/
#define ctHDRLOCKflg	((LONG) 0x000010)/* tflstt:FPUTFGET header lock on    */
#define ctPARTMTXflg	((LONG) 0x000020)/* permit only one create/open/reorg */
#define ctPARTCREflg	((LONG) 0x000040)/* control create thread completion  */
#define ctDYNDMPsfh	((LONG) 0x000080)/* dynamic dump host status flag     */
#define ctFLUSHmod	((LONG) 0x000100)/* flush status ctsave flag	      */
#define ctPARTBLKflg	((LONG) 0x000200)/* crepart() breakout occurred	      */
#define ctRESHDRflg	((LONG) 0x000400)/* reshdr1/2 update		      */
#define ctPARTCLSflg	((LONG) 0x000800)/* control create thread file close  */
#define ctPENDOPNflg    ((LONG) 0x001000)/* block opens until cleared         */

#define ctTFLSTTall	(ctDYNDMPmod | ctWRTHRUupd | ctHOSTOPEN | ctREDFILflg | ctHDRLOCKflg | ctPARTMTXflg | ctPARTCREflg | ctDYNDMPsfh | ctFLUSHmod | ctRESHDRflg | ctPARTCLSflg | ctPENDOPNflg)

#define tflsttSET	1
#define tflsttTST	2
#define tflsttOFF	3
#define tflsttGET	4 /* waits for bit to clear, and then sets bit */
#define tflsttWAIT      5 /* waits for bit to clear */


/*
** dnctflg header states: pending commit
*/
/*	ctDNCTexclusive	((LONG)0x00000001)    exclusive update		 */
#define ctDNCTpndOn	((LONG)0x00000002) /* DUPKEY->ctDISTINCT 	 */
#define ctDNCTpndOff	((LONG)0x00000004) /* ctDISTINCT->DUPKEY	 */
#define ctDNCTpndOnB	((LONG)0x00000008) /* DUPKEY->ctDISTINCTpart	 */
#define ctDNCTpndOffB	((LONG)0x00000010) /* ctDISTINCTpart->DUPKEY	 */
#define ctDNCTpndOnP	((LONG)0x00000020) /* ctDISTINCT->ctDISTINCTpart */
#define ctDNCTpndOffP	((LONG)0x00000040) /* ctDISTINCTpart->ctDISTINCT */
#define ctDNCTpndOnU	((LONG)0x00000080) /* NODUPKEY->ctDISTINCTuniq	 */
#define ctDNCTpndOffU	((LONG)0x00000100) /* ctDISTINCTuniq->NODUPKEY	 */

			/* all flags */
#define ctDNCTpndAll	(ctDNCTpndOn | ctDNCTpndOff | ctDNCTpndOnB | ctDNCTpndOffB | ctDNCTpndOnP | ctDNCTpndOffP | ctDNCTpndOnU | ctDNCTpndOffU)
			/* all on flags */
#define ctDNCTpndAllOn	(ctDNCTpndOn | ctDNCTpndOnB | ctDNCTpndOnP | ctDNCTpndOnU)
			/* all off flags */
#define ctDNCTpndAllOff	(ctDNCTpndOff | ctDNCTpndOffB | ctDNCTpndOffP | ctDNCTpndOffU)
			/* all partial on flags */
#define ctDNCTpndPartOn (ctDNCTpndOnB | ctDNCTpndOnP | ctDNCTpndOnU)
			/* all distinct off flags */
#define ctDNCTpndDstOff (ctDNCTpndOff | ctDNCTpndOffB | ctDNCTpndOffU)


/*
** ctFLMD
*/
#define ctFLMD_DFRCLS	0x0001		/* flmd: multi-user ctDFRCLSflg	      */
#define ctFLMD_DFRDEL	0x0002		/* flmd: multi-user ctDFRDELflg	      */
#define ctFLMD_CHKLOK	0x0004		/* flmd: user ctCHECKLOCK flag	      */
#define ctFLMD_CHKRED	0x0008		/* flmd: user ctCHECKREAD flag	      */
#define ctFLMD_HSTOPN	0x0010		/* flmd: partition opened by host     */
#define ctFLMD_HSTKEY	0x0020		/* flmd: operate on host index	      */
#define ctFLMD_WRTHDR	0x0040		/* flmd: fusrclr wrthru wrthdr	      */
#define ctFLMD_TOUCH	0x0080		/* flmd: touch notify		      */
#define ctFLMD_NONTFY	0x0100		/* flmd: data file update w/o  notify */
#define ctFLMD_YSNTFY	0x0200		/* flmd: data file update with notify */
#define ctFLMD_ABTEXC	0x0400		/* flmd: fupd reset ctfusrclr	      */
#define ctFLMD_CMTLOK	0x0800		/* flmd: turned on CMTLOKs	      */
#define ctFLMD_XKYBUF	0x1000		/* flmd: missing ISAM key buffer info */
#define ctFLMD_BLKRDO	0x2000		/* flmd: blocked file available	      */
#define ctFLMD_BLKMBR	0x4000		/* flmd: blocked superfile member     */
#define ctFLMD_BLKPND	0x8000		/* flmd: blocked file pending status  */

/*
** ctFLMD2
*/
#define ctFLMD2_REDSHR	0x00000001	/* flmd2: file open w/readonly share  */
#define ctFLMD2_IICT	0x00000002	/* flmd2: immed indep commit tran     */
#define ctFLMD2_IICTUPD	0x00000004	/* flmd2: file updated in IICT        */
#define ctFLMD2_RTREE	0x00000008	/* flmd2: opened by r-tree driver     */
#define ctFLMD2_IICTDFR	0x00000010	/* flmd2: close/delete dfr in IICTxtd */
#define ctFLMD2_ADMOPEN	0x00000020	/* flmd2: file opened with ctADMOPEN  */
#define ctFLMD2_ADDUNQ	0x00000040	/* flmd2: unique key already added    */
#define ctFLMD2_ADDUNQP	0x00000080	/* flmd2: we could not use our optimized
					** method to update the unique key's
					** record offset, so we used ADDKEY's
					** CHGADD mode. This created a new
					** preimage space entry, so we must
					** remove the old entry before the
					** record add operation completes. */
#define ctFLMD2_DYNPARTMBR 0x00000100	/* flmd2: this file is open as a dynamic
					** partition member. */
#define ctFLMD2_DIFUSR	 0x00000200	/* flmd2: treat locks as diff user    */
#define ctFLMD2_NODIFUSR 0x00000400	/* flmd2: treat locks as non-diff usr */
#define ctFLMD2_SAMUSR_1 0x00000800	/* flmd2: treat locks as same user    */
#define ctFLMD2_SAMUSR_M 0x00001000	/* flmd2: treat locks as same user    */
#define ctFLMD2_COFILE_FILELOCK 0x00002000 /* flmd2: special COBOL file locks */
#define ctFLMD2_SPCLACSS 0x00004000	/* flmd2: special internal access;
					** exclude from extended file
					** attributes			      */
#define ctFLMD2_REDILOK 0x00008000	/* flmd2: read intent lock exists     */
#define ctFLMD2_WRTILOK 0x00010000	/* flmd2: write intent lock exists    */
#define ctFLMD2_ABTEXCI 0x00020000	/* flmd2: IICT abort node list entries*/
#ifdef ctBEHAV_IDXMBRUPDFLG
#define ctFLMD2_AVAIL 0x00040000	/* flmd2: available		      */
#else
#define ctFLMD2_MBRUPDI 0x00040000	/* flmd2: IICT updated index member   */
#endif
#define ctFLMD2_RUCBOPN	0x00080000	/* flmd2: record update file open
					** callback function has been called
					** for this file		      */
#define ctFLMD2_TRNLST	0x00100000	/* flmd2: file on tran list	      */
#define ctFLMD2_TRNLSTI	0x00200000	/* flmd2: file on tran list (iict)    */
#define ctFLMD2_NOISMKEYUPD 0x00400000	/* flmd2: ISAM record update is not allowed to change the key value */

#define ctFLMD2_MLTOPN_MASK		(ctFLMD2_DIFUSR   | ctFLMD2_NODIFUSR | \
					 ctFLMD2_SAMUSR_1 | ctFLMD2_SAMUSR_M)
#define ctFLMD2_SAMUSR_MASK		(ctFLMD2_SAMUSR_1 | ctFLMD2_SAMUSR_M)

#define ctDFRREDflg	(ctDFRCLSflg   | ctDFRDELflg)
#define ctFLMD_DFRRED	(ctFLMD_DFRCLS | ctFLMD_DFRDEL)

#define ctXTMD_ISAM	0x00000001	/* xtmd: ISAM level user open/create  */
#define ctXTMD_HST	0x00000002	/* xtmd: SUPERFILE HOST		      */
#define ctXTMD_MBR	0x00000004	/* xtmd: SUPERFILE member (or SI)     */
#define ctXTMD_DIAG	0x00000008	/* xtmd: diagnostic timeout info      */
#define ctXTMD_NOTIMOUT	0x00000010	/* xtmd: no timeout		      */
#define ctXTMD_NOAUTOP	0x00000020	/* xtmd: do not update autopos	      */
#define ctXTMD_TRNPERS	0x00000040	/* xtmd: TRAN persistent locks enabled*/
#define ctXTMD_LOCKDFR	0x00000080	/* xtmd: LOCK defer close enabled     */
#define ctXTMD_IDfieldV	0x00000100	/* xtmd: IDfield override	      */
#ifdef ctBEHAV_IDXMBRUPDFLG
#define ctXTMD_AVAIL	0x00000200	/* xtmd: available		      */	
#else
#define ctXTMD_MBRUPD	0x00000200	/* xtmd: like fupd for all mbrs	      */
#endif
#define ctXTMD_PPPRG	0x00000400	/* xtmd: pending partition purge      */
#define ctXTMD_PPRG	0x00000800	/* xtmd: partition purged	      */
#define ctXTMD_PPARHV	0x00001000	/* xtmd: pending partition archive    */
#define ctXTMD_PARHV	0x00002000	/* xtmd: partition archived	      */
#define ctXTMD_IDfieldP	0x00004000	/* xtmd: preserve IDfield value	      */


#define ctSETLOGFILflg	/* always defined with new universal compatibility
			   support */

/*
** ISAM context sensitive file mode bits (ctICON iflmd member)
**
** ctSIBLING_IFLMD
*/
#define ctIFLMD_XKYBUF	0x0001	/* iflmd: missing key buffer info	     */
#define ctIFLMD_NKYBUF	0x0002	/* iflmd: no effect on key buffer status     */
#define ctIFLMD_KBUFOFF	0x0004	/* iflmd: key buffering off for this context */
#define ctIFLMD_KBUFON	0x0008	/* iflmd: key buffering on for this context  */



/*
** XCREblk splval "internal use only" mask. These bits will be ignored if
** set by an application.
*/
#define ctSPLVALint	(ctREPLICATEint | ctMEMFILEint | ctAUTO_PREIMGint | ctAUTO_TRNLOGint | ctIDFIELDint)


/*
** ctBEHAV_NEWLOG_TRAN only applies to TRANPROC; and ctBEHAV_NEWLOG_TRANhdr
** also requires ctLOGFILflg support
*/
#ifndef TRANPROC
#ifdef ctBEHAV_NEWLOG_TRAN
#undef ctBEHAV_NEWLOG_TRAN
#endif
#ifdef ctBEHAV_NEWLOG_TRANhdr
#undef ctBEHAV_NEWLOG_TRANhdr
#endif
#endif

#ifdef ctBEHAV_NEWLOG_TRANhdr
#ifndef ctSETLOGFILflg
**** we need ctLOGFILlfg support for mutex protected log header writes ***
#endif
#endif


#define ctserFWD	0	/* forward search through partitioned indices */
#define ctserBAK	1
#define ctserTWO	16	/* only two args, no target		      */

#define ctTEMPINDX	-105
#define CTVFSGnokeys	-10000

#define ctnlkMASK	0x0f
#define ctnlkCNDXflg	0x10
#define ctnlkTMPXflg	0x20
#define ctnlkINDXflg	0x40
#define ctnlkCNDXbth	(ctnlkCNDXflg | ctnlkTMPXflg)

#define ctCNDXexpr	0	/* tokenized expression			*/
#define ctCNDXclbk	1	/* callback specification		*/
#define ctCNDXifil	2	/* cond expr control struct		*/
#define ctCNDXdump	3	/* dump overload			*/
#define ctCNDXpart	4	/* expr belongs to partition host	*/
#define ctCNDXcdll	5	/* callback DLL specification		*/

#define FRCEADJ	 16
#define THRUADJ	 32
#define HISTADJ	 64
#define RCODADJ	128
#define SEGHADJ	256	/* segmented header I/O */
#define SEGABS	512	/* segmented absolute I/O */
#define SPCLCRE	1024
#define TLOGCRE	2048
#define SYNCADJ	4096	/* ctsync on/off around write */

#ifdef ctCAMO
#define RCODbit	RCODADJ
#else
#define RCODbit	0
#endif
#ifdef ctHUGEFILEsegm
#define SEGHbit	SEGHADJ
#define SEGAbit	SEGABS
#else
#define SEGHbit	0
#define SEGAbit	0
#endif

#define CTREAD	 0
#define CTWRITE	 1
/*
** the following opcodes are no longer used:
**
	#define CTWASYN  2
	#define CTNONE	 3
	#define CTXTND	 4
**
*/
#define CTSEGLOK 2		/* opcode for ctdecsegmdef lock call */
#define CTCLRBF	 5
#define CTREADP	 8
#define CTFRED	 (CTREAD  | FRCEADJ)
#define CTFWRT	 (CTWRITE | FRCEADJ)
#define CTURED	 (CTREAD  | THRUADJ)
#define CTUWRT	 (CTWRITE | THRUADJ)
#define CTCWRT	 (CTWRITE | SPCLCRE)
#define CTHISTR	 (CTREADP | HISTADJ)
#define CTRRED	 (CTFRED  | RCODbit)
#define CTREADHG (CTFRED  | SEGHbit | RCODbit)
#define CTWRITHG (CTFWRT  | SEGHbit | RCODbit)
#define CTREADAG (CTFRED  | SEGAbit | RCODbit)
#define CTWRITAG (CTFWRT  | SEGAbit | RCODbit)

#define ctDD_FIL	1	/* regular file entries */
#define ctDD_STR	2	/* start file entries */
#define ctDD_LOG	3	/* transaction log entries */
#define ctDD_DEF	4	/* first entry in dump file */
#define ctDD_CLN	5	/* non ctTRNLOG file is clean */
#define ctDD_END	6	/* last entry in dump file */
#define ctDD_DRT	7	/* non ctTRNLOG file is dirty */
#define ctDD_CNT	8	/* regular file extension entries */
#define ctDD_RCV	9	/* must force recovery during ctrdmp */
#define ctDD_SUP	10	/* header location info for MBR_SUPER */
#define ctDD_SEG	11	/* regular file segment definition entry */
#define ctDD_GDF	12	/* dump file segment definition */
#define ctDD_SFL	13	/* regular file - segmented */
#define ctDD_NXT	14	/* end of extent indicator */
#define ctDD_FFF	15	/* part of file ff filled */
#define ctDD_LST	15
#define ctDD_HUG	31	/* dsize entry in DEF block for HUGE dump */
#define ctDD_PRE	32	/* file temporarily set to ctLOGFIL */
#define ctDD_EXT	64	/* file extent size temporarily set non-zero */
#define ctDD_SKP	128	/* skip clean file during recovery */
#define ctDD_FRC	256	/* index recovery forced: modify nument */

/*
** Dynamic dump restore option bits:
*/
#define ctDR_OLDREDIR	0x00000001 /* use old redirect logic */
#define ctDR_DIAGRCV	0x00000002 /* enable diagnostic logging of recovery */
#define ctDR_DIAGLOG	0x00000004 /* enable RECOVER_DETAILS diagnostic logging */

/*
** Dynamic dump header attributes:
*/

/*
** The following values are used in the dattr field in the header at the
** beginning of the dynamic dump stream file.
*/
#define ctDA_ADVENC	0x00000001	/* file is using advanced encryption */
#define ctDA_LOGENC	0x00000002	/* transaction logs are encrypted    */


#ifndef ctDD_EXTSIZE
#ifdef ctBEHAV_DYNDMP_STREAM
#define ctDD_EXTSIZE	0 /* default to writing dynamic dump to one file */
#else
#define ctDD_EXTSIZE	(1024 * 1024 * 1024)
#endif
#endif


#ifdef ctSS
#define SSO	1	/* SS (strict serializer) logical Open lock */
#define SSCI	2	/* SS commit intent lock */
#define SSC	3	/* SS commit lock */
#define NSCI	4	/* NS (nonstrict serializer) commit intent lock */
#define NSC	5	/* NS commit lock */
#endif
#define RDL	6	/* read lock */
/* #define	WRL	7	** write lock held to reader commits */
/* #define	CIL	8	** pending WRL to WXL promotion */
#define WXL	9	/* exclusive write lock */
#define WXH	10	/* exclusive write lock (no aggregate check) */
#define CMT	11	/* commit I/O lock for forcei()			 */

#define ctAGRflg	1	/* supd: special SS aggregate read lock	 */
#define ct1STflg	2	/* supd: 1st attempt flag (SS wrtlok)	 */
#define ct1STlok	4	/* supd: 1st SS wrtlok acquired		 */

#define RIL	12	/* read intent lock	*/
#define WIL	13	/* write intent lock	*/
#define TRL	14	/* table read lock	*/
#define TWL	15	/* table write lock	*/

#define RIL_CK	-12	/* check if read intent lock can be acquired	 */
#define WIL_CK	-13	/* check if write intent lock can be acquired	 */

/* Intent lock queueing modes: */
	/*	0 */	/* We did not use 0 and 1 because we are passing */
	/*	1 */	/*   this value to ctaddblk() in the hdrflg	 */
			/*   parameter, which already uses these values. */
#define QI_NEW	2	/* new intent lock request			 */
#define QI_EXS	3	/* already blocked record lock request		 */

/* Table lock state (tlkstt) bits */
#define TLK_READLK	0x00000001	/* table read lock in effect	 */
#define TLK_WRITELK	0x00000002	/* table write lock in effect	 */
#define TLK_TRANLOCK	0x00000004	/* table lock acqd in tran	 */
#define TLK_TRANOUT	0x00000008	/* table lock acqd outside tran	 */
#define TLK_XFREED	0x00000010	/* table lock freed in tran	 */

/*
** work monitor constants
*/
#define ctWORKctree	0	/* c-tree clients			*/
#define ctWORKsql	1	/* SQL clients				*/
#define ctWORKchkpnt	2	/* Check Point thread			*/
#define ctWORKbackgrnd	3	/* low priority background threads	*/
#define ctWORKdyndmp	4	/* dynamic dump internal thread		*/
#define ctWORKrtree	5	/* r-tree internal thread		*/
#define ctWORKcbep	6	/* common bound entry point thread	*/
#define ctWORKcrethrd	7	/* partition create thread		*/
#define ctWORKnewuser	8	/* NewUser thread			*/
#define ctWORKlogon	9	/* NewLogon thread			*/
#define ctWORKptadmin	10	/* PTADMIN thread			*/
#define ctWORKsize	11	/* ctSIBLING_workprf_size		*/

#define ctWORK_MASK	0x000000ff /* valid work monitor range		*/

/*
** flags for the remainder of the 4-byte worktype value:
*/
#define ctWORK_SKPACT	0x00000100 /* skip active connection limit	*/
#define ctWORK_SUCCESS  0x00000200 /* ctaddwork Return code is informative only.  
				     terr() on critical failure */

/*
** idle task info
*/
#define ctIDLEflushT	0	/* flush transaction buffers		*/
#define ctIDLEflushN	1	/* flush non-transaction buffers	*/
#define ctIDLEz		2	/* maximum number of idle processes	*/
				/* ct_ii[] indicates which are active	*/

#define ctIDLEflushTint	15	/* default flushT interval in seconds	*/
#define ctIDLEflushNint	15	/* default flushN interval in seconds	*/

#define LEAF     1
#define NOLEAF   0
#define ctNODEOK 2

#define ALPHAKEY	'\0'

/*
** obsolete key types: no longer supported.
**
	INTKEY (1)
	SFLOATKEY (2)
	DFLOATKEY (3)
**
** so bits 1 and 2 are available.
*/
#define COL_PREFIX	 '\4'			/* leading character compression	*/
#define COL_SUFFIX	 '\10'			/*  8 decimal: padding compression	*/
#define COL_BOTH	 '\14'			/* 12 decimal: both of the above	*/
#define ALT_SEQ		 '\20'			/* 16 decimal: alternative col sequence	*/
#define MSK_ALT		 ~ALT_SEQ
#define KORDprt		 '\40'			/* 32 decimal: search like partition key*/
#define KINCprt		 '\100'			/* 64 decimal: covers partition key	*/
#define KMSKprt		 (KORDprt | KINCprt)
#define KTYP_NOISMKEYUPD ((UTEXT)'\200') 	/* 128 decimal: ISAM record update is not allowed to change the key value */

/* The ktype header field is one byte, so all the following values cannot be
stored in this field. However, the IIDX ikeytyp field is a two-byte value, so
the following values can be specified in ikeytyp. */
#define KTYP_DFRIDX 	 ((COUNT)0x0100) 	/* deferred index			*/
#define KTYP_VLENNOD	 ((COUNT)0x0200)	/* index node contains offset list	*/
#define KTYP_TRNMRKOPT	 ((COUNT)0x0400)	/* transaction marks stored with keys	*/
#define KTYP_KEYCOMPSRLE ((COUNT)0x0800)	/* index uses sRLE key compression	*/
#define KTYP_CMPOFFSET	 ((COUNT)0x1000)	/* index uses compressed offsets	*/
#define KTYP_CMPTRNMRK	 ((COUNT)0x2000)	/* index uses compressed transaction marks */

/* The key types that require key offset list support: */
#define ctKTYP_MASK_REQUIRES_VLENNOD (KTYP_TRNMRKOPT | KTYP_KEYCOMPSRLE | KTYP_CMPOFFSET | KTYP_CMPTRNMRK)

/* The flmode3 option bits that require key expansion: */
#define ctFLMODE3_MASK_REQUIRES_KEYEXP (ctIndexCmpsRLEmd3 | ctIndexCmpOffmd3 | ctIndexCmpMrkmd3)

/* flmode3 option bits that are not inherited from the host index when creating a member index: */
#define ctFLMODE3_MASK_NOT_INHERITED (ctVarlenNodeFmtmd3 | ctTranMarkOptmd3 | ctIndexCmpOffmd3 | ctIndexCmpMrkmd3 | ctIndexCmpsRLEmd3)

/*
** ctport.h defines ctNODUPKEY, ctDUPKEY, ctNOPDUPKEY as well as
** the distinct count options. These three defines are maintained
** for compatibility.
*/
#define NODUPKEY	'\0'	/* no duplicates allowed		*/
#define DUPKEY		'\1'	/* duplicates allowed			*/
#define NOPDUPKEY	'\2'	/* no dupe within partition		*/

/*
** FCB (non-header) distinct values
**
** 	values assigned to the distinct member of the CTFILE
**	control structure at file create or open. this member
**	of CTFILE is not part of the header written to disk.
**
**	no distinct support		'\0'
**	whole key distinct only		'\1'
**	unique with partial distinct	'\2'
**	whole and partial distinct	'\3'
*/

/* TREEBUFF confg field values: */
#define REGULAR  '\1'	/* confg == REGULAR for any node in an index that does
			not allow duplicates; DUPNONL also has this bit set;
			this bit indicates that an offset precedes the key value */
#define DUPLEAF  '\0'	/* confg == DUPLEAF for a leaf node in an index that allows duplicates */
#define DUPNONL	 '\3'	/* confg == DUPNONL for a non-leaf node in an index that allows duplicates */

#define DAT_CLOSE 0
#define IDX_CLOSE 1
#define VAT_CLOSE 2

#define ctINVLDSPC	16	/* invalidate space management: iclsfilx */
#define ctNOHDRWRT	32	/* no header write on auto recovery close*/
#define ctSHTDWNCLS	64	/* server closing files at end of shutdown */

/* Auxiliary file mode bits set by chkopnx() after opening the file and reading
its header: */
#define ctAUXMODdat	0x00000001	/* data file			*/
#define ctAUXMODidx	0x00000002	/* index file			*/
#define ctAUXMODvat	0x00000004	/* var len data file		*/
#define ctAUXMODnon	0x00000008	/* no tran proc			*/
#define ctAUXMODpre	0x00000010	/* preimage only		*/
#define ctAUXMODtrn	0x00000020	/* tran proc			*/
#define ctAUXMODred	0x00000040	/* read-share access (redshr)	*/
#define ctAUXMODhgh	0x00000080	/* clnleaf() already attempted	*/
#define ctAUXMODthru	0x00000100	/* ctTRNLOGthru			*/
#define ctAUXMODnbuf	0x00000200	/* unbuffered I/O is not permitted
					** for this file		*/
#define ctAUXMODopnf	0x00000400	/* called from OPNFIL		*/

/* ADDKEY() typadd parameter options: */
#define SUPADD		0x00000010	/* superfile index directory	*/
#define MODMODE		0x00000020	/* suppress chkred and tstupd	*/
#define CHGADD		0x00000040	/* special op on unique key upd	*/
#define IDXONLY		0x00000080	/* not for VLENGTH space index	*/
#define TSTMODE		0x00000100	/* suppress chkred only		*/
#define	SKPSPLT		0x00000200	/* skip UPDMARKS split check	*/
#define	UPDRECBYT	0x00000400	/* update record offset: like
					CHGADD, but only if key exists	*/

#define ctOUTpart	-2	/* ran out of partitions		*/
#define ctNOpart	-3	/* no partition encoded			*/
#define ctRETRYpart	-4	/* retry partition operation		*/
#define ctFILBLKpart	-5	/* file block on partition		*/
#define ctPURGpart	-6	/* internal ctFILBLK enabled purge	*/
#define ctARHVpart	-7	/* internal ctFILBLK enabled archive	*/
#define ctTESTpart	-99	/* test value (that cannot be assigned)	*/


#define SECSIZ   128		/* logical sector size. DO NOT CHANGE.	*/
#define CTBUFSIZ (MAX_NAME + 1)	/* ct_buf[] size */
#define ctUPDATED C255		/* C255 defined in ctcmpl.h */
#define DELFLG	  C255
#define RESFLG	  C254
#define COMPACT  '\143'		/* 0x63 'c': file compaction flag: must rebuild indices */
#define CTBADOPN '\122'		/* 0x52 'R': file corrupt on open */
#define CTBADLOP '\114'		/* 0x4C 'L': leaf level loop: must rebuild indices */
#define CMPMSK	 0x00ff

/*
** index key buffer indicator values
*/
#define kbNO	'\0'			/* no key value exists		  */
#define kbYES	'\1'			/* key value exists		  */
#ifdef ctBEHAV_MISSING_KEY
#define kbDNO	'\2'			/* insufficient data record image */
#define kbBNO	'\3'			/* ctISAMKBUFhdr: no buffer update*/
#endif

/*
** range control modes
*/
#define fwdRNG	0x0001		/* forward			*/
#define bakRNG	0x0002		/* backward			*/
#define intRNG	0x0010		/* init call			*/
#define lowRNG	0x0020		/* low level call		*/

#define frsRNG	(fwdRNG | intRNG)
#define lstRNG	(bakRNG | intRNG)
#define nxtRNG	fwdRNG
#define prvRNG	bakRNG


#define recbytDAT	'D'	/* RECBYT active data record indicator	   */
#define recbytRES	'R'	/* RECBYT resource record indicator	   */
#define recbytSPC	'S'	/* RECBYT deleted record indicator	   */

#define MAXAGE    0xffff	/* max age of lru counter before roll-over */
#define MAXSRLPOS 0xffff	/* no serial segment flag		   */

#define	LH_VER	 0x0001			/* LOW_HIGH option 		*/
#define	HL_VER	 0x0002			/* HIGH_LOW   "			*/

#define ADD_LOCK	0	/* cts_lok() flag: adding a lock	*/
#define ADD_LOCK_NEW	1	/*		   adding a lock only if**
				**		   no lock already exists*/
#define RED_LOCK	2	/*		   check if red locked	*/
#define MST_LOCK	3	/*		   check if wrt locked	*/
				/* ctSIBLING_CMTLOK			*/
#define WRT_CMTLOK	4	/*		   wrt commit lock	*/
#define WRT_CMTLOKU	5	/*		   wrt commit unlock	*/
#define RED_CMTLOKU	6	/*		   red commit unlock	*/
#define RED_CMTLOK	7	/*		   red commit lock	*/
#define CHG_UFLOCK	8	/* only change user file number		*/
#define ADD_LOCK_NODE	9	/* cts_lok() call for index node	*/
#define CHKLOK_OTHER	10	/* check lock by other connection/datno */

/* ***********     DEFINE LOCKING REQUIREMENTS & TESTS      *********** */
#define LOCK_TEST MST_LOCK

#ifdef ctPortREALIA_STD
#ifdef NDEBUG
#undef LOCK_TEST
#endif
#endif /* ctPortREALIA_STD */

#define SHDSRCH		128	/* 0x0080 no preimg search			*/
/* reserve ctHISTkchg	256	   for history key change: no data image*/
/* available		512	   for future use			*/
#define SHDLOCK		1024	/* 0x0400 ignore savepoint in search		*/
#define RESEXTFIL	1024	/* 0x0400 special modifier (overloaded on	**
				** SHDLOCK) only used in call to	**
				** ctlogext81 by a resource operation	*/
#define FLSHLOG		2048	/* 0x0800 trantyp requires log flush		*/
#define FLSHAGN		4096	/* 0x1000 may require a retry of log flush	*/
#define FLSHTRN		8192	/* 0x2000 trantyp requires log flush unless
				   suppress log flush (ctsuplog) is on	*/
#define TRANACT		16384	/* 0x4000 contributes to tranac_cnt		*/
#define SHDIICT		32768	/* 0x8000 like SHDLOCK, but over main preimage	*/

#define TRANMSK		(~SHDSRCH)
#define FLSHMSK		(~FLSHLOG & ~FLSHAGN & ~FLSHTRN & ~TRANACT)

#define LHDRCOMP	1
#define SH_HDRCP	(LHDRCOMP | SHDSRCH)
#define LADDKEY		2
#define SH_ADDKY	(LADDKEY | SHDSRCH)
#define LADDSI		(LADDKEY + 1)
#define LDELKEY		4
#define SH_DELKY	(LDELKEY | SHDSRCH)
#define LDELSI		(LDELKEY + 1)
#define SH_INVLD	6
#define iBEGTRAN	7
#ifdef ctDBEGFLSH
#define BEGTRAN		(iBEGTRAN | FLSHAGN		| TRANACT)
#else
#define BEGTRAN		(iBEGTRAN | FLSHAGN | FLSHTRN	| TRANACT)
#endif
#define SH_BEGTRAN	(BEGTRAN | SHDSRCH)
#define iENDTRAN	8
#define ENDTRAN		(iENDTRAN | FLSHAGN | FLSHTRN	| TRANACT)
#define iABRTRAN	9
#define ABRTRAN		(iABRTRAN | FLSHAGN | FLSHTRN	| TRANACT)
#define SH_NLINK	10			/* 0x0a */
#define NEWLINK		SH_NLINK	
#define SH_VLINK	11			/* 0x0b */
#define SH_IMAGE	12			/* 0x0c */
#define NEWIMAGE	SH_IMAGE			
#define OLDFILL		13			/* 0x0d */
#define OLDIMAGE	14			/* 0x0e */
#define DIFIMAGE	15			/* 0x0f */
#define RDYTRAN		16			/* 0x10 */
#define LHDRSHST	17			/* 0x11 */
#define LOGEXTFIL	18			/* 0x12 */
#define SH_EXTFIL	(LOGEXTFIL | SHDSRCH)
#define NODEXTFIL	19			/* 0x13 */
#define SH_NODFIL	(NODEXTFIL | SHDSRCH)
#define SH_QNODE	20			/* 0x14 */
#define LHDRWORD	21			/* 0x15 */
#define SH_HDRWORD	(LHDRWORD | SHDSRCH)
#define iUNDTRAN	22			/* 0x16 */
#define UNDTRAN		(iUNDTRAN | FLSHAGN | FLSHTRN	| TRANACT)
#define BEG2FASE	23			/* 0x17 */
#define ACK2FASE	24			/* 0x18 */
#define SH_RSTFIL	25			/* 0x19 */
#define LOGRSTFIL	SH_RSTFIL

#define iCHKPNT		26			/* 0x1a */
#define CHKPNT		(iCHKPNT | FLSHLOG)     /* 0x81a */
#define iOPNTRAN	27			/* 0x1b */
#define OPNTRAN		(iOPNTRAN | FLSHAGN)
#define CRETRAN		28			 /* 0x1c tran independent create */
#define DELTRAN		(29 | FLSHLOG | FLSHAGN) /* 0x181d tran independent delete */
#define CLSTRAN		30			/* 0x1e */
#define LLOGIN		31			/* 0x1f */
#define LLOGOFF		32			/* 0x20 */
#define UPDTRAN		33			/* 0x21 */
#define iENDLOG		34			/* 0x22 */
#define ENDLOG		(iENDLOG | FLSHLOG)	/* 0x822 */
#define LPRMIDX		35

#define RESTRAN		36
#define SH_WRITE	37
#define SH_REUSE	(38 | SHDSRCH)
#define SH_RSTRUS	39
#define ABNTRAN		40
#define LPABYTE		41
#define INDXADD		42
#define INDXDEL		43
#define LTFLMAP		44			/* tfil map (tranoff holds
						   map version)		      */
#define USRTRANI	45			/* TRANUSR entry (own tran#)  */
#define DSTINDEX	46			/* distinct index count	      */
#define HDRVALUE	47			/* header image at offset     */
#define PARTHST		48			/* partition host name        */
#define iRSTPNT		49			/* restore point: no act tran */
#define RSTPNT		(iRSTPNT | FLSHLOG)
#define SYSTRANI	50			/* TRANSYS entry (own tran#)  */

/* reserve 51 through 62 for tran types that get their own trannum */

#define DARWRDdir	63	/* DARWRD direct to log	*/
#define FRCTRAN		64	/* force log turnover	*/
#define SEGTRAN		65
#define LLOGNODE	66
#define getTRANNUM	66

/* remaining tran types use current trannum */

#define CMPTRAN		(67 | FLSHLOG)
#define ENCTRAN		68
#define SH_ENCTRAN	(ENCTRAN | SHDSRCH)
#define RENTRAN		(69 | FLSHLOG | FLSHAGN) /* new rename file	   */
#define RENTRANU	70			 /* undo rename file	   */
#define SEGMRES		71			 /* file segment definition*/
#define SH_SEGMRES	(SEGMRES | SHDSRCH)
#define CREDRAN		(72 | FLSHLOG | FLSHAGN) /* tran dependent create  */
#define SH_CREDRAN	(CREDRAN | SHDSRCH)
#define DELDRAN		(73 | FLSHLOG | FLSHAGN) /* tran dependent delete  */
#define SH_DELDRAN	(DELDRAN | SHDSRCH)
#define CRENRAN		74			 /* tran dependent cmt create */
#define DELNRAN		(75 | FLSHLOG | FLSHAGN) /* tran dependent cmt delete */

#define SPCLTRAN	76			 /* special trannum treatment */
#define INDXEND		76
#define INDXERR		77
#define INDXVUL		78
#define SUCTRAN		(79 | TRANACT)		/* opposite of UNDTRAN	      */
#define LCMPRECRES	80			/* data record compression    **
						** resource: not TRANdep      */

/*			81, 82			reserved for future use	      */
#define SPCLLAST	82
/******************************************************************************/


#define LPRMIDXDEP	83			/* tran dependent prmiidx */
#define SH_LPRMIDX	(LPRMIDXDEP | SHDSRCH)

#define SEGDCRE		(84 | FLSHLOG | FLSHAGN) /* tran dependent seg	      */
#define SH_SEGDCRE	(SEGDCRE | SHDSRCH)
#define SEGDDEL		(85 | FLSHLOG | FLSHAGN) /* tran dependent seg	      */
#define SH_SEGDDEL	(SEGDDEL | SHDSRCH)
#define SEGNCRE		86			 /* tran dependent cmt seg    */
#define SEGNDEL		(87 | FLSHLOG | FLSHAGN) /* tran dependent cmt seg    */
#define SEGMOLD		88			 /* old restorable segm def   */
#define SH_SEGMOLD	(SEGMOLD | SHDSRCH)
#define SH_RSPACE	(89 | SHDSRCH)		 /* reclaim deleted SFM space */
#define ALNEXTFIL	90
#define SH_ALNFIL	(ALNEXTFIL | SHDSRCH)
#define LDROPIDX	91			 /* TRANDEP drop index	      */
#define SH_LDROPIDX	(LDROPIDX | SHDSRCH)
#define LPARTRES	92
#define SH_PARTRES	(LPARTRES | SHDSRCH)
#define LHDRSNUM	93
#define SH_HDRSN	(LHDRSNUM | SHDSRCH)
#define RENDRAN		(94 | FLSHLOG | FLSHAGN) /* tran dependent rename  */
#define SH_RENDRAN	(RENDRAN | SHDSRCH)
#define RENNRAN		(95 | FLSHLOG | FLSHAGN) /* tran dependent cmt rename */

#define SH_APIACTN	(96 | SHDSRCH)		 /* API indicator	      */
#define SH_APIMAGE	(97 | SHDSRCH)		 /* API image		      */
#define LREPIMAGE	98	 		 /* replication old delete img*/
#define SH_REPIMAGE	(LREPIMAGE | SHDSRCH)
#define LFNDKEY		99
#define SH_FNDKY	(LFNDKEY | SHDSRCH)
#define USRTRAN		100			/* TRANUSR entry (cur tran#)  */
#define SH_USRTRAN	(USRTRAN | SHDSRCH)
#define SH_RSTHDR	(101 | SHDSRCH)		/* restore tmp header state   */
#define SH_RECRLK	(102 | SHDSRCH)		/* recursive lock/unlock      */
#define SH_ADDKY_DEFERD	103			/* deferred add key entry     */
#define SH_DELKY_PRTENT	(104 | SHDSRCH)		/* purged individual delete   */
#define DARWRD		105			/* DAR state variable update  */
#define SH_DARWRD	(105 | SHDSRCH)
#define LDFRKEY		106
#define SH_DFRKEY	(LDFRKEY | SHDSRCH)	/* Deferred key operation     */
#define LFLSIXBF	107
#define SH_FLSIXBF	(LFLSIXBF | SHDSRCH)	/* Index buffer requires flush
						** on transaction commit      */
#define SYSTRAN		108			/* TRANSYS entry (cur tran#)  */
#define SH_SYSTRAN	(SYSTRAN | SHDSRCH)
#define SYNCREPL_DEPEND	109			/* sync repl dependency (cur tran#)  */
#define SH_SYNCREPL_DEPEND	(SYNCREPL_DEPEND | SHDSRCH)

#define SH_AUTOST	(110 | SHDSRCH)/* auto system time changed */
#define ctMAXTRNTYP	110
/*			...					*/
/*			126	last available trannum		*/
#define SH_SPCLSAV	(127 | SHDSRCH)

/*
** RECRLK sub-types
*/
#define SH_RECRLK_LOCK		1	/* recursive lock		*/
#define SH_RECRLK_UNLOCK	2	/* recursive unlock		*/

/*
** RSTHDR sub-types
*/
#define SH_RSTHDR_IDXEXPupd	1	/* conditional index update	*/
#define SH_RSTHDR_IDXEXPdel	2	/* conditional index delete	*/
#define SH_RSTHDR_SECEXPred	3	/* row level  read filter	*/
#define SH_RSTHDR_SECEXPwrt	4	/* row level write filter	*/


/*
** RENTRAN sub-types
*/
#define RENTRANscn	0x0001	/* rename added during transcn		*/
#define RENTRANund	0x0002	/* rename added during tranund		*/
#define RENTRANred	0x0004	/* rename added during tranred		*/
#define RENTRANnew	0x0010	/* file renamed to new name		*/
#define RENTRANold	0x0020	/* file opened with new name		*/
#define RENTRANmtc	0x0100	/* search for renrst entry		*/
#define RENTRANopp	0x0200	/* search for opposite renrst entry	*/
#define RENTRANclr	0x1000	/* renrst entry cleared			*/

#define LTFLMAPon		1	/* establish data / UNQKEY map	*/
#define LTFLMAPoff		2	/* turn off data /UNQKEY map	*/
#define LTFLMAPno_unq_cfg	3	/* no UNQKEY, REP from CONFIG
					** info, turn off replication	*/
#define LTFLMAPlowlevel		4	/* no UNQKEY, hdr has REP bit,
					** low level OPN, mark file cor-
					** rupt, & turn off replication	*/
#define LTFLMAPshift		5	/* UNQKEY relative key number
					** for data file will shift;
					** companion LTFLMAPon entry
					** will follow			*/


#define FILEOFFS	12
#define COMITRAN	1L
#define FIRSTRAN	2L
#define HOLDTRAN	1

/* ctgetnod81() lokind base values: */
#define NOCTCLUP	1		/* Skip transaction mark cleanup.	     */
#define BUFRLOCK	2		/* Buffer lock(?). Does not seem to currently
					   have an effect on ctgetnod81().	     */
#define GNS		3		/* Check if the specified node is currently
					   in an index buffer. If it isn't, return
					   NULL instead of reading it in. If it is,
					   return a pointer to the index buffer while
					   still holding the index cache hash list
					   mutex.				     */

/* ctgetnod81() lokind modifier values: */
#define DBGTREEno	0x00000010	/* Index tree debug logging. (Not enabled.)  */
#define ctGN_CMT	0x00000020	/* Used in node prune call at transaction
					   commit in single-user tranproc mode.	     */
#define ctBNODnolog	0x00000040	/* do not log E69 message for this operation */
#define ctGN_NXTMARKS	0x00000080	/* ctgetnod81 called for next key op	     */
#define ctGN_READER	0x00000100	/* attempt slim reader lock on idxsem	     */
#define ctGN_REDUNDANT	0x00000200	/* ctgetnod81 call may be redundant	     */
#define ctGN_UPDATE	0x00000400	/* ctgetnod81 called for index update	     */
#define ctGN_GNCSEM	0x00000800	/* request getnod/lrubuf concurrency sema    */
#ifdef DBGtree
#define ctGN_ADD	4
#define ctGN_DEL	5
#define ctGN_UND	6
#define ctGN_SRC	7
#define ctGN_ABT	8
#define NOnd		(NO | DBGTREEno)
#define NOCTCLUPnd	(NOCTCLUP | DBGTREEno)
#define BUFRLOCKnd	(BUFRLOCK | DBGTREEno)
#define GNSnd		(GNS | DBGTREEno)
#else
#define NOnd		NO
#define NOCTCLUPnd	NOCTCLUP
#define BUFRLOCKnd	BUFRLOCK
#define GNSnd		GNS
#endif

/*
** tree traversal retry count
*/
#ifndef ctTREEretry
#define ctTREEretry	10 /* 020220 - 527 issue in FPUTFGET */
#endif
#ifndef ctTREEdelay
#define ctTREEdelay	5	/* milleseconds */
#endif
#ifndef ctROOTretry
#define ctROOTretry	7
#endif
#ifndef ctROOTdelay
#define ctROOTdelay	40	/* milleseconds */
#endif
#ifndef ctDNODEretry
#define ctDNODEretry	128	/* retry: deleted node in index */
#endif

#define ctTREEretry1	(ctTREEretry + 1)
#define ctROOTretry1	(ctROOTretry + 1)

#ifdef DBGnodeIO
#define DBGnodeIOopnfil	1
#define DBGnodeIOclsfil	2
#define DBGnodeIOextfil	3
#define DBGnodeIOnewnod	4
#define DBGnodeIOwrite	5
#define DBGnodeIOread	6
#define DBGnodeIOinit	7
#define DBGnodeIOreport	8
#define DBGnodeIOfree	9
#define DBGnodeIOgetnod	10
#define DBGnodeIOnlst1	11
#define DBGnodeIOnlst3	12
#define DBGnodeIOplst2	13
#define DBGnodeIOplst5	14
#define DBGnodeIOnlstr1	15
#define DBGnodeIOnlstr2	16
#define DBGnodeIOnlstr3	17
#define DBGnodeIOplstr1	18
#define DBGnodeIOplstr2	19
#define DBGnodeIOplstr3	20
#define DBGnodeIOplstr4	21
#define DBGnodeIOplstr5	22
#define DBGnodeIOplstr6	23
#define DBGnodeIOsucesr	24
#define DBGnodeIOterr	25
#define DBGnodeIOroot	26
#define DBGnodeIOlogoff	27
#define DBGnodeIOupdyes	28
#define DBGnodeIOupdno	29
#define DBGnodeIOidxfrs	30
#define DBGnodeIOchkmtc	31
#define DBGnodeIOflsbuf	32
#define DBGnodeIOrb1	33
#define DBGnodeIOrb2	34
#define DBGnodeIOrb3	35
#define DBGnodeIOrb4	36
#define DBGnodeIOrb5	37
#define DBGnodeIOrb6	38
#define DBGnodeIOrb7	39
#define DBGnodeIOrb8	40
#define DBGnodeIOrb9	41
#define DBGnodeIOrb10	42
#define DBGnodeIOrb11	43
#define DBGnodeIOrb12	44
#define DBGnodeIOrb13	45
#define DBGnodeIOrb14	46
#define DBGnodeIOrb15	47
#define DBGnodeIOrb16	48
#define DBGnodeIOrb17	49
#define DBGnodeIOrb18	50
#define DBGnodeIOrb19	51
#define DBGnodeIOrb20	52
#define DBGnodeIOrb21	53
#define DBGnodeIOrb22	54
#define DBGnodeIOrb23	55
#define DBGnodeIOrb24	56
#define DBGnodeIOlock	57
#define DBGnodeIOusralv	58
#define DBGnodeIOlokerr	59
#define DBGnodeIOunlock	60
#define DBGnodeIOulkerr	61
#define DBGnodeIOaddblk	62
#define DBGnodeIOlokerd	63
#define DBGnodeIOlokagn	64
#define DBGnodeIOloktry	65
#define DBGnodeIOuerr	66
#define DBGnodeIOpner1	67
#define DBGnodeIOpner2	68
#define DBGnodeIOpner3	69
#define DBGnodeIOwrterr	70
#define DBGnodeIOrederr	71
#define DBGnodeIOredhdr	72
#define DBGnodeIOwrthdr	73
#define DBGnodeIOfilhdr	74
#define DBGnodeIOmovrgt	75
#define DBGnodeIOlockReport 76
#define DBGnodeIOrb25	77
#define DBGnodeIOrb26	78
#endif /* DBGnodeIO */

#ifdef ctDIAGnodeERR
#define DBGnodeERRzeroreq	1	/* Zero node request			*/
#define DBGnodeERRlogieof	2	/* node exceeds logical index EOF	*/
#define DBGnodeERRmemitim	3	/* ctnodmemrec does not find buffer	*/
#define DBGnodeERRusralive	4	/* ctUserAlive returns non-zero		*/
#define DBGnodeERRusralive2	5	/* ctUserAlive returns non-zero		*/
#define DBGnodeERRlrubuf	6	/* lrubuf81 failure			*/
#define DBGnodeERRrednod	7	/* rednod81 failure			*/
#define DBGnodeERRnumexc	8	/* Invalid numexc node control field	*/
#endif

#define TRN_AFLAG	1
#define TRN_DFLAG	2
#define TRN_NODE	4
#define TRN_DATA	8
#define TRN_ABRT	16

#define TRN_ANODE	(TRN_NODE | TRN_AFLAG)
#define TRN_ADATA	(TRN_DATA | TRN_AFLAG)
#define TRN_AABRT	(TRN_NODE | TRN_AFLAG | TRN_ABRT)

#define TRN_DNODE	(TRN_NODE | TRN_DFLAG)
#define TRN_DDATA	(TRN_DATA | TRN_DFLAG)
#define TRN_DABRT	(TRN_NODE | TRN_DFLAG | TRN_ABRT)

#define ctNAMINDXadd	1
#define ctNAMINDXdel	2
#define ctNAMINDXeql	3

/*
** Transaction mark values: stored in two bits of 4- or 6-byte transaction mark
** value in leaf nodes of transaction-controlled indexes.
*/
#define DL_SRCH		0	/* no mark: key exists */
#define DL_ADDR		1	/* key is pending add */
#define DL_DLTR		2	/* key is pending delete */
#define DL_RVRS		3	/* pending delete followed by pending add with
				different offset in same transaction for unique
				index */

/* The following values are not stored in leaf nodes: */
/* values 4 and 5 are not currently used */
#define DL_DLTRexc	6	/* used in call to ctabtexc81() to remove the
				node (buf->nodeid2,buf->nodeid1) from the abort
				node list in one call for each node-transaction
				pairing. */

#ifdef ctDBGanl

#define dbgANLinit	1
#define dbgANLdump	2
#define dbgANLnewitem	3
#define dbgANLincitem	4
#define dbgANLdecitem	5
#define dbgANLrmvitem	6
#define dbgANLnumexc	7
#define dbgANLnotN	8
#define dbgANLnotT	9
#define dbgANLnotZ	10

#define dbgANLlocale	0xfff0
#define dbgANLmask	0x000f

#define DL_DLTR_00	(DL_DLTR | 0x0010)
#define DL_DLTR_01	(DL_DLTR | 0x0020)
#define DL_DLTR_06	(DL_DLTR | 0x0070)
#define DL_DLTR_08	(DL_DLTR | 0x0080)
#define DL_DLTR_10	(DL_DLTR | 0x00b0)
#define DL_DLTR_11	(DL_DLTR | 0x00c0)
#define DL_DLTR_12	(DL_DLTR | 0x00d0)
#define DL_DLTR_13	(DL_DLTR | 0x00e0)
#define DL_DLTR_15	(DL_DLTR | 0x0100)
#define DL_DLTR_16	(DL_DLTR | 0x0110)

#define DL_ADDR_01	(DL_ADDR | 0x0020)
#define DL_ADDR_02	(DL_ADDR | 0x0030)
#define DL_ADDR_03	(DL_ADDR | 0x0040)
#define DL_ADDR_04	(DL_ADDR | 0x0050)
#define DL_ADDR_05	(DL_ADDR | 0x0060)
#define DL_ADDR_07	(DL_ADDR | 0x0080)
#define DL_ADDR_08	(DL_ADDR | 0x0090)
#define DL_ADDR_09	(DL_ADDR | 0x00a0)
#define DL_ADDR_14	(DL_ADDR | 0x00f0)
#else  /* ~ctDBGanl */
#define DL_DLTR_00	DL_DLTR
#define DL_DLTR_01	DL_DLTR
#define DL_DLTR_06	DL_DLTR
#define DL_DLTR_08	DL_DLTR
#define DL_DLTR_10	DL_DLTR
#define DL_DLTR_11	DL_DLTR
#define DL_DLTR_12	DL_DLTR
#define DL_DLTR_13	DL_DLTR
#define DL_DLTR_15	DL_DLTR
#define DL_DLTR_16	DL_DLTR
#define DL_DLTR_17	DL_DLTR

#define DL_ADDR_01	DL_ADDR
#define DL_ADDR_02	DL_ADDR
#define DL_ADDR_03	DL_ADDR
#define DL_ADDR_04	DL_ADDR
#define DL_ADDR_05	DL_ADDR
#define DL_ADDR_07	DL_ADDR
#define DL_ADDR_08	DL_ADDR
#define DL_ADDR_09	DL_ADDR
#define DL_ADDR_14	DL_ADDR
#endif /* ~ctDBGanl */

/* ctDBGiict location codes */
#define DBGiict01	1
#define DBGiict02	2
#define DBGiict03	3
#define DBGiict04	4
#define DBGiict05	5
#define DBGiict06	6
#define DBGiict07	7
#define DBGiict08	8
#define DBGiict09	9
#define DBGiict10	10
#define DBGiict11	11
#define DBGiict12	12
#define DBGiict13	13
#define DBGiict14	14
#define DBGiict15	15
#define DBGiict16	16
#define DBGiict17	17
#define DBGiict18	18
#define DBGiict19	19
#define DBGiict20	20
#define DBGiict21	21

#define CURKEY		0
#define TMPKEY		1

#define AVLIST		0		/* bhlAV bavl[0] */
#define DALIST		1		/* bhlDA bavl[1] */
					/*
					** NUMANCHOR applies to following lists
					*/
#define INLIST		2		/* bhlIN bhla[0] */
#define DULIST		3		/* bhlDU bhla[1] */
#define NUMANCHOR	2
#ifdef MULTITRD
#define PNLIST		4		/* bhlPN bhla[2] */
#define DPLIST		5		/* bhlDP bhla[3] */
#undef  NUMANCHOR
#ifdef ctFeatRECBKT
#define DBLIST		4		/* bhlDB bhla[4] */
#define NUMANCHOR	5
#else
#define NUMANCHOR	4
#endif
#endif

#if defined(ctFeatNoDatPndgList) || defined(ctFeatNoIdxPndgList)
/*
** cache page status word values when operating without a pending list
*/

#define ctCPclear	0		/* valid page contents		  */
#define ctCPpending	1		/* page intended for reassignment **
					** may be valid. check pos1/2	  */
#define ctCPdummy	2		/* page is a dummy place holder	  */
#ifdef ctFeatDatEmptyList
#define ctCPempty	3		/* page on empty list		  */
#endif
#ifdef ctFeatSCANCACHE
#define ctCPscanner	4		/* scanner page			  */
#endif

#endif


/*
** internal file-based mutex ctFILMTX constants
*/
#define ctFILMTXheld	1
#define ctFILMTXunused	2

/*
** ctFeatFILEUSRLST ctusrlst() actions
*/
#define ctULinit	1	/* init user list for file		*/
#define ctULzero	2	/* empty user list for file		*/
#define ctULone		3	/* first user on list for file		*/
#define ctULinc		4	/* add user to list for file		*/
#define ctULdec		5	/* remove user from list for file	*/
#define ctULsrc		6	/* check if user is on list for file	*/
#define ctULidx		7	/* return Nth user on list for file	*/
#define ctULdfr		8	/* remove dfrcls user from list		*/

#define ctULbase	100	/* add to Thrd ID to distinguish a zero
				   Thrd ID from empty slot in user list	*/
#define ctULorgblkr	(-199)	/* substitute for terminated blocker	*/
#define ctULempty	999999	/* report empty slot in user list	*/

/*
** ctkilblk modes
*/
#define ctKBshtdwn	1	/* terminate thread due to server shutdown    */
#define ctKBtrmthd	2	/* terminate the thread only		      */
#define ctKBfilblk	4	/* trying to clear threads from core code     */
#define ctKBtimout	8	/* blocking lock timeout		      */
#define ctKBdiagnose	16	/* diagnostic output			      */

/*
** ctLOKTIMOUT internal modes (cannot be passed  by client side)
*/
#define ctLTOinternal   0x00000000      /* no internal modes defined    */

/*
** ctFeatFILEBLOCK and ctFeatQUIET and ctFeatMAX_USER_LOGS and
** ctFeatTRAN_TIMEOUT user work states ctwa(owner) under ctpconcsema
*/
#define ctFBnorqst	0x000000/* thread conected to server, but no request  */
#define ctFBactive	0x000002/* thread executing API: between add/rem work */
#define ctFBkilled	0x000004/* ctkilblk cleared fb_blk[]->semab	      */
#define ctFBbreakout	0x000008/* break out of loops with FBLK_ERR	      */
#define ctFBwork	0x000010/* non-chkpnt addwork in force		      */
#define ctFBsuspended	0x000020/* thread suspended in API by file block      */
#define ctQTtranbeg	0x000040/* thread blocked at TRANBEG		      */
#define ctQTlogon	0x000080/* thread blocked at INTREEz		      */
#define ctQTbreakout	0x000100/* non ctQTblockthread breakout		      */
#define ctQTfnshdel3	0x000200/* thread in ctfnshdel3() post commit routine */
#define ctQTtranabt	0x000400/* transaction aborted			      */
#define ctQTaddwork	0x000800/* thread blocked at ctaddwork()	      */
#define ctQTchkfilblk	0x001000/* thread executing ctFILBLK		      */
#define ctMLexceeded	0x002000/* MAX_USER_LOGS exceeded by thread	      */
#define ctMLtranabn	0x004000/* MAX_USER_LOGS tran aborted		      */
#define ctMLtryabort	0x008000/* attempting MAX_USER_LOS abort	      */
#define ctMLintranovr	0x010000/* thread performing tranovr()		      */
#define ctFBnoabort	0x020000/* ctFBsuspended state not abortable	      */
#define ctQTvalidusr	0x040000/* thread blocked in validusr()		      */
#define ctQTcrethrd	0x080000/* partition create thread		      */
#define ctTTexceeded	0x100000/* tran timeout exceeded		      */
#define ctTTtranabn	0x200000/* tran timeout tran aborted		      */
#define ctTTtryabort	0x400000/* tran timeout attempting abort	      */
#define ctABinline	0x800000/* delay abort/abandonment until inline	      */
#define ctABexempt     0x1000000/* exempt from abort/abandonment	      */
#define ctIMblock      0x2000000/* blocked by impersonation		      */
#define ctQTnewuser    0x4000000/* NewUser thread blocked at ctaddwork()      */
#define ctQTsuperusr   0x8000000/* super user logon after abandoned ctQUIET   */
#define ctQTdyndmpfrq 0x10000000/* idyndmp thrd in freq(repeating) loop	      */

#define ctQTsuspended	(ctQTlogon | ctQTaddwork | ctQTtranbeg)
#define ctUSERbreakout (ctFBbreakout | ctQTbreakout | ctMLexceeded | ctTTexceeded)


/*
** ctwv() state bits.
**
** (a) Changed under control of ctpconcsema, which is a separate mutex for each
**     connection when ctBEHAV_WORKsync is defined.
*/
#define ctWVactive	0x00000001 /* thread is active (a)		      */
#define ctWVactxmp	0x00000002 /* thread exempt from being made inactive  */
#define ctWVlokexs	0x00000004 /* thread holding one or more locks	      */
#define ctWVwaitng	0x00000008 /* thread waiting to become active	      */

/*
** ctFeatFILEBLOCK reserved action attributes
*/
#define ctFBshutdown	0x0400	/* permit ctcatend to unblock orphans	      */
#define ctFBunbflag	0x2000	/* ctFBunblock in progress		      */
#define ctFBblkflag	0x4000	/* ctFBblock in progress (before altlist)     */
#define ctFBquiet	0x8000	/* block called from ctQUIET		      */
#define ctFBinternal	(ctFBshutdown | ctFBunbflag | ctFBblkflag | ctFBquiet)

/*
** ctFeatFILEBLOCK flmp and fblku special values
*/
#define ctFBlogcls	-1	/* flmp:  unassigned or blocked by logical cls*/
#define ctFBnormal	-2	/* fblku: no block (else holds flmp)	      */
#define ctFBsyscls	-3	/* flmp:  blocked by sysclose		      */
#define ctFBsysclsblkr	-4	/* flmp:  blocker by sysclose		      */
#define ctFBsysclssus	-5	/* flmp:  suspended by sysclose		      */

/*
** ctQUIET reserved action attributes
*/
#define ctQTblockthreads	0x002000	/* block all threads in
						** ctaddwork()		      */
#define ctQTblockvalidusr	0x010000	/* block validusr()	      */
#define ctQTcheckpoint		0x080000	/* checkpoint indicator	      */
#define ctQTblocktranauto	0x100000	/* auto ctQTblockTransactions */
#define ctQTinternal		(ctQTblockthreads | ctQTblockvalidusr | ctQTcheckpoint | ctQTblocktranauto)

/*
** place holder for disconnected ctQTthrd
*/
#define ctQTorgblkr	(-299)



/*^**********************************************************************/
#define CT_STRING_LITERAL(s) s
/*
** RAB060102: For future use-not implemented yet -
** Means that all code is compiled for a complete UNICODE environment.
** #define ctPort_UNICODE
*/
#undef  ctPort_UNICODE	/* Not used yet. Future define when all internal c-tree is UNICODE */
#ifdef ctPortWIN32	/* RAB060102: in case we ever try for _UNICODE in Standard Windows-ON for Win CE	*/
#ifdef ctSRVR		/* RAB:060720: We qualified this to ctSRVR because the CT_STRING_LITERAL below is needed*/
			/*             for the Windows CE Server, yet is causes a compiler error in CPP: 	*/
			/*             because of ctdbDEFAULT_dbengine used in ctdbsdk.hpp			*/
#ifdef _UNICODE		/* On for most Windows CE Projects 							*/
/*
** RAB:051224: the L ## s is a trick I used from Dharma's headers in order
** not to get syntax errors. Seems to work fine.
*/
#undef  CT_STRING_LITERAL
#define CT_STR_LIT(s) L ## s
#define CT_STRING_LITERAL(s) CT_STR_LIT(s)
#endif
#endif /* ctSRVR */
#endif /* ctPortWIN32 */
/*~**********************************************************************/


/*
**
** The following modules all use the FCS file extent:  ctopt2.h, ctscrt.h,
**   ctclb2.c, ctclb3.c, ctdump.c, ctldmp.c, ctrdmp.c, ctsadm.c ctsrvr.c.
**
*/

#define FAIRCOMS	"FAIRCOMS"

#ifdef ctSRVR
#define uADMIN		pADMINu
#define uGUEST		pGUESTu
#define gADMIN		pADMINg
#define gGUEST		pGUESTg
#else
#ifdef ctPortUNIX
#define	uADMIN		"root"
#define gADMIN		"sysadmin"
#define uGUEST		"anonymous"
#define gGUEST		"GUEST"
#else
#define	uADMIN		"ADMIN"
#define gADMIN		uADMIN
#define uGUEST		"GUEST"
#define gGUEST		uGUEST
#endif
#endif

#ifdef MLTORTRN
#define FAIRSQLS	"SQL.FCS"
#endif

#define CT_V60	0			/* Version 6 Release Flag */
#define CT_V65	5
#define NEWIFIL				/* With Version 7, no longer req*/

/*
** ctstat2 status bits
**
** CTSTAT2_ADDREC through CTSTAT2_DELORG are
** included in tranatr member of TRANDSC when ctXTDLOG enabled
*/

#define CTSTAT2_ADDREC		0x00000001L	/* ADDREC		     */
#define CTSTAT2_RWTREC		0x00000002L	/* RWTREC		     */
#define CTSTAT2_DELREC		0x00000004L	/* DELREC		     */
#define CTSTAT2_ISAMUPD		0x00000008L	/* ISAM add/del/rwt	     */
#define CTSTAT2_RSRCUPD		0x00000010L	/* resource add/upd/del	     */
#define CTSTAT2_ADDORG		0x00000020L	/* ADD original operation    */
#define CTSTAT2_RWTORG		0x00000040L	/* RWT original operation    */
#define CTSTAT2_DELORG		0x00000080L	/* DEL original operation    */

#define ctORGOPS_SHIFT		5		/* bit shift from op to org  */
						/* ADDREC << SHIFT == ADDORG */

#define CTSTAT2_OPS	(CTSTAT2_ADDREC | CTSTAT2_RWTREC | CTSTAT2_DELREC)
#define CTSTAT2_ORG	(CTSTAT2_ADDORG | CTSTAT2_RWTORG | CTSTAT2_DELORG)
#define CTSTAT2_IOATRB	(CTSTAT2_ADDREC | CTSTAT2_RWTREC | CTSTAT2_DELREC | CTSTAT2_ISAMUPD | CTSTAT2_RSRCUPD)

/*
** CTSTAT2 bits that do NOT map into tranatr bits
*/

#define CTSTAT2_ISAMrowl	0x00000100L	/* ISAM row level filter in play      */
#define CTSTAT2_FCRES		0x00000200L	/* internal FCRES update	      */
#define CTSTAT2_SUBSRL		0x00000400L	/* substitute serial number value     */
#define CTSTAT2_CLSDWN		0x00000800L	/* iclsfilx called from ctdwnfil      */
#define CTSTAT2_NOREPL		0x00001000L	/* do not mark this operation for repl*/
#define CTSTAT2_DELNODCTL	0x00002000L	/* coordinate access to file with the
						   delete node thread		      */
#define CTSTAT2_RSPACECTL	0x00004000L	/* coordinate access to file with the
						   space reclamation thread	      */
#define CTSTAT2_CPRIMECTL	0x00008000L	/* coordinate access to file with a
						   cache priming thread		      */
#define CTSTAT2_FILEOPNBLK	0x00010000L	/* block file open on successful open */
#define CTSTAT2_KEPOPNCTL	0x00020000L	/* coordinate access to file with the
						   KEEPOPEN file close thread	      */
#define CTSTAT2_PARTMBRDEL	0x00040000L	/* opening partition mbr to delete it */
#define CTSTAT2_SETCURPONERR	0x00080000L	/* set curp in case of error	      */
#define CTSTAT2_TBLLOK		0x00400000L	/* unlocking records for table lock   */
#define CTSTAT2_DFRIDXCTL	0x00800000L	/* coordinate access to file with the
						** deferred indexing threads	      */
#define CTSTAT2_DYNDUMP_LOCK	0x01000000L	/* user holding physical file dynamic   
						 * dump read lock during node split   */

/* all thread file control control bits */
#define CTSTAT2_ALLTHRDCTL (CTSTAT2_DELNODCTL | CTSTAT2_RSPACECTL | CTSTAT2_CPRIMECTL | CTSTAT2_KEPOPNCTL | CTSTAT2_DFRIDXCTL)

#define CTSTAT2_ISAMFIL		0x10000000L	/* ISAM level data file open or create*/
#define CTSTAT2_FILBLK		0x20000000L	/* file blocker			      */
#define CTSTAT2_BLKIMP		0x40000000L	/* impersonated by file blocker	      */
#define CTSTAT2_BLKOPN		0x80000000L	/* ISAM autopen failed		      */

/*
** CTSTAT2 bits that are available for use
*/

#define CTSTAT2_AVAIL16		0x02000000L	/* available for use	     */
#define CTSTAT2_AVAIL17		0x04000000L	/* available for use	     */
#define CTSTAT2_AVAIL18		0x08000000L	/* available for use(tranatr)*/


/*
** I/O attributes for ctXTDLOG (included in tranatr)
*/
#define ctIO_DRHD		0x00000100	/* data record header /
						** del-link     	    */
#define ctIO_DRBD		0x00000200	/* data record body	    */
#define ctIO_RSHD		0x00000400	/* resource header	    */
#define ctIO_RSBD		0x00000800	/* resource body	    */
#define ctIO_SFDT		0x00001000	/* superfile host data	    */
#define ctIO_BTCH		0x00002000	/* batch data record adds   */
#define ctIO_UNIQ		0x00004000	/* unique key		    */
#define ctIO_RLEN		0x00008000	/* REPIMAGE holds old &
						** new length		    */

/*
** additional tranatr bits
*/
#define ctTRANATR_REP		0x00010000	/* replication enabled	    */
#define ctTRANATR_CMPREC	0x00020000	/* compressed record image  */
#define ctREPLFLG_WRITE		0x00040000	/* Replication writer status
						** flag			    */

/* NOTE: the interpretation of tranatr bit 0x00080000 depends on the preimage
** space entry type: */
#define ctDISTINCTlog		0x00080000	/* LADDKEY, LADDSI, LDELKEY,
						** LDELSI: index update affects
						** DISTINCT cnt		    */
#define ctFLEXREC_REP		0x00080000	/* LTFLMAP, NEWIMAGE, LREPIMAGE,
						** OLDIMAGE: replicated data
						** file with FLEXREC feature*/

/* NOTE: the interpretation of tranatr bit 0x00100000 depends on the preimage
** space entry type: */
#define ctIO_NLINK		0x00100000	/* SH_IMAGE is/starts-with
						** SH_NLINK		    */
#define ctIO_ADDUNQFRS		0x00100000	/* SH_ADDKEY is an add unique
						** key first operation      */

#define ctTRANATR_AUG		0x00200000	/* log entry is augmented   */
#define ctIO_REPIMGRWT_FRS	0x00400000	/* first rewritten record
						** image for replication    */
#define ctIO_REPIMGRWT		0x00800000	/* rewritten record image
						** for replication	    */
#define ctTRANATR_ADDKY_DEFERD1	0x01000000	/* first deferred addkey op */
#define ctTRANATR_ADDKY_DEFERD2	0x02000000	/* last deferred addkey op  */
#define ctIO_DAR		0x04000000	/* DAR body		    */

#define ctTRANATR_ADDKY_DEFERD	0x40000000	/* defer key add operations
						** on update		    */

/*
** tranatr bits that are available for use:
*/

#define ctTRANATR_AVAIL08	0x08000000	/* available for use(ctstat2) */

/*
** Special tranatr bits that are trantyp dependent
**
** NOTE: see TRANUSR() in cttran.c for a discussion
** of how tranatr is interpreted for the trantyp's
** of USRTRAN and USRTRANI.
*/

/*
** CLSTRAN special tranatr bit
*/
#define	ctTRANATR_CLSTRAN_RCVR	0x00000001	/* CLSTRAN entry made by auto **
						** recovery		      */

/*
** TRANDSC version bits
**
** ctTRANATR_CMP is on if the variable portion of the log image is compressed.
**
** For run-time extension of TRANDSC, 2 bits of tranatr are reserved.
** This permits up to 4 additional TRANDSC structures. It is envisioned
** that the log I/O would read the "base" TRANDSC structure, check these
** version bits, and read augmented portion of structure as required.
*/
#define ctTRANATR_V1		0x10000000	/* TRANDSC version bit 1      */
#define ctTRANATR_V2		0x20000000	/* TRANDSC version bit 2      */
#define ctTRANATR_CMP		0x80000000	/* transaction log compression*/

#define ctTRANATR_VER	(ctTRANATR_CMP | ctTRANATR_V1 |ctTRANATR_V2)


/*
** ctstat3 status bits
*/

#define CTSTAT3_ISAMIDX	 0x00000001L	/* ISAM index open/create	      */
#define CTSTAT3_BLKRCLS	 0x00000002L	/* BLKR logclose		      */
#define CTSTAT3_DFCSLOW	 0x00000004L	/* ctwrtlog slowed for CHKPDFC	      */
#define CTSTAT3_SKPICUV	 0x00000008L	/* skip ICU version check	      */
#define CTSTAT3_SAVPUPD	 0x00000010L	/* space reused since last savepoint  */
#define CTSTAT3_SKIPTMP	 0x00000020L	/* ITIM_ERR on tmp index; skip record */
#define CTSTAT3_NOLOKDE	 ctLOKDYNnodemote
					/* deny lock demotion 0x00000040      */
#define CTSTAT3_NOLOKFR	 ctLOKDYNnofree /* deny lock free 0x00000080	      */
#define CTSTAT3_TRNPERS  ctLOKDYNtranPersist
					/* locks persist unlock even if no
					** update inside transaction	      */
#define CTSTAT3_LOCKDFR	 ctLOKDYNlockDefer
					/* lock causes deferred close	      */
/* reserve 0x00000400 0x00000800 0x00001000 for additional ctLOKDYN actions   */
#define CTSTAT3_IPARTORD 0x00002000
#define CTSTAT3_PART	0x00004000	/* creating partitioned files	      */
#define CTSTAT3_PARTMMBR 0x00008000	/* creating partitioned member files  */
#define CTSTAT3_PARTRNG 0x00010000	/* KINCprt range request	      */
#define CTSTAT3_SYSRES	0x00020000	/* ADDRES called by system routine    */
#define CTSTAT3_IDfield	0x00040000	/* IDfield updated in transaction     */
#define CTSTAT3_DAR	0x00080000	/* add / delete DAR		      */
#define CTSTAT3_RBLDIDX	0x00100000	/* indices exist during rebuild	      */
#define CTSTAT3_SCANDAR	0x00200000	/* must scan data for DAR updates     */
#define CTSTAT3_SYSFLT	0x00400000	/* SETFLTRN called by system routine  */
#define CTSTAT3_ALTERTBL 0x00800000	/* alter table operation in progress  */
#define CTSTAT3_PARTRBLD 0x01000000	/* recursive calls to rebuld for      **
					** partitioned files		      */
#define CTSTAT3_PARTMRBL 0x02000000	/* PTADMIN call to rebuild partition  **
					** member			      */
#define CTSTAT3_PARTRBLX 0x04000000	/* RBLIDX or RBLMEM for partitioned   **
					** file: disables ctlogkey81 for GUIx */
#define CTSTAT3_RBLIDX   0x08000000	/* RBLIDX or RBLMEM processing	      */
#define CTSTAT3_DBGHDRLOK 0x10000000	/* skip semaf ownr check	      */
#define CTSTAT3_ISAMKEEPOPEN 0x20000000 /* ISAM KEEPOPEN for data & indices   */
#define CTSTAT3_REPLADMOPEN 0x40000000	/* read/write open of replicated file **
					** for admin purposes		      */
#define CTSTAT3_KOCLSADMOPEN 0x80000000	/* open KEEPOPEN file to close it     */


/*
** ctstat4 status bits
*/

#define CTSTAT4_FNSHDEL2 0x00000001L	/* in ctfnshdel2() routine	      */
#define CTSTAT4_PARTCLS	 0x00000002L	/* in ctpartcls() routine	      */
#define CTSTAT4_IICT_END 0x00000004L	/* completing IICTxtd operation	      */
#define CTSTAT4_PPRG_COD 0x00000008L	/* deleting purged unique global      **
					** index entry			      */
#define CTSTAT4_PRTiprg	 0x00000010L	/* nentiprg updated in transaction    */
#define CTSTAT4_RCV_PRM	 0x00000020L	/* called from reprmidx		      */
#define CTSTAT4_BUF_RQS	 0x00000040L	/* no addblk, direct buf->semaf rqs   */
#define CTSTAT4_ADDRESp	 0x00000080L	/* special ADDRES for placeholder res */
#define CTSTAT4_PPRG	 0x00000100L	/* internal ctFILBLK for part purge   */
#define CTSTAT4_PARHV	 0x00000200L	/* internal ctFILBLK for part archive */
#define CTSTAT4_HSTOPNCLS 0x00000400L	/* CLSFIL for partition opened by     **
					** host. manage numopnhst	      */
#define CTSTAT4_PARTRED  0x00000800L	/* ISAM read on partitioned file      */
#define CTSTAT4_KEPTOPN	 0x00001000L	/* open set KEEPOPEN mode on file     */
#define CTSTAT4_SUBID	 0x00002000L	/* substitute identity field value    */
#define CTSTAT4_ISAMCLS	 0x00004000L	/* ISAM level data file close	      */
#define CTSTAT4_IMPSTPUSR 0x00008000L	/* STPUSR by thread impersonator      */
#define CTSTAT4_CLSFIL_OK 0x00010000L	/* non-MULTITRD CLSFIL: no ISAM chk   */
#define CTSTAT4_INTLREAD 0x00020000L	/* internal record read call          */
#define CTSTAT4_UPDSECRES 0x00040000L	/* updating security resource on open */
#define CTSTAT4_A3_TRNFIL 0x00080000L	/* A3_TRNFIL NOT consistent	      */
#define CTSTAT4_ADVHDRUPD 0x00100000L	/* ADDVREC already updated hdr values */
#define CTSTAT4_SKPOPNERR 0x00200000L	/* skip some errors on file open      */
#define CTSTAT4_logsema	  0x00400000L	/* ctplogsema has been acquired	      */
#define CTSTAT4_NOFILELIST 0x00800000L	/* disable ctFILELIST search	      */
#define CTSTAT4_NEW_RNODE 0x01000000L	/* ctgetnod81 called from newnod81    **
					** for a node from getdelnod81	      */
#define CTSTAT4_DYNPARTOPN 0x02000000L	/* opening dynamic partition	      */
#define CTSTAT4_LOSTCONN 0x04000000L	/* client: lost connection to server  */
#define CTSTAT4_COFILE_UNLOCK 0x08000000L /* unlock based on co-file request  */
#define CTSTAT4_COFILE_CHGLOK 0x10000000L /* change cofile locks, if any      */
#define CTSTAT4_OPNRFIL_CLSDAT 0x20000000L /* OPNRFIL closing data file       */
#define CTSTAT4_FROMAPI	0x40000000L	/* called from CREDATX8 / CREIDXX8 /  **
					** OPNFILX			      */
#define CTSTAT4_CONVBLK1 0x80000000L	/* caller is using ConvBlk version 1  */


/*
** ctstat5 status bits
*/

#define CTSTAT5_DFRIDX		0x00000001L /* deferred index op in transaction */
#define CTSTAT5_MEMFILE_REFCNT	0x00000002L /* increment memory record reference count */
#define CTSTAT5_IGNORE_READERR	0x00000004L /* suppress read error diagnostics */
#define CTSTAT5_MINIDXBUFSEM	0x00000008L /* thread acquired minidxbuf sema */
#define CTSTAT5_IN_RUCB		0x00000010L /* thread in record update callback */
#define CTSTAT5_CLSIDXMBR	0x00000020L /* closing and removing index member */
#define CTSTAT5_ABLISTDEL	0x00000040L /* deleted abort node list entry */
#define CTSTAT5_RUCBADD		0x00000080L /* adding record update callback resource */
#define CTSTAT5_SYSIOGETLOCK	0x00000100L /* first recursive ctsysio81() call: keep lock */
#define CTSTAT5_SYSIORELLOCK	0x00000200L /* second recursive ctsysio81() call: free lock */
#define CTSTAT5_KEEPOPENLOCKCLS	0x00000400L /* keepopen file lock is closing file */
#define CTSTAT5_NOIDGEN		0x00000800L /* do not generate identity value */
#define CTSTAT5_PUTHDRINT	0x00001000L /* internal call to PUTHDR */
#define CTSTAT5_FRCFLSH		0x00002000L /* force flush for a no-flush file */
#define CTSTAT5_ISAMMBR		0x00004000L /* ISAM index member create */
#define CTSTAT5_CHKUCNF		0x00008000L /* MTFPG: user lock table has been checked */
#define CTSTAT5_NOULTBL		0x00010000L /* MTFPG: skip user level unlock */
#define CTSTAT5_SUPPRESS_RUCB	0x00020000L /* force open file to not start RU callback */
#define CTSTAT5_DELFILABTCLS	0x00040000L /* close file if its delete is undone by transaction abort */
#define CTSTAT5_CREIDXFSCMP	0x00080000L /* create index with file system level compression */
#define CTSTAT5_PNDFILOPN	0x00100000L /* signal pending file open during chkopnx() */
#define CTSTAT5_DFRFILCLS	0x00200000L /* defer system call to close file */
#define CTSTAT5_NONAMINDX	0x00400000L /* skip inamidx() calls for this operation */
#define CTSTAT5_NOLOWLIOERRLOG	0x00800000L /* skip DIAGNOSTICS LOWL_FILE_IO error logging for this operation */
#define CTSTAT5_NOCACHE		0x01000000L /* when creating a file, indicates NO_CACHE for this file */
#define CTSTAT5_NOGETCAMO	0x02000000L /* skip ctgetcamo() when opening file */
#define CTSTAT5_NOAUTOST	0x04000000L /* suppress automatic time stamp assignment */
#define CTSTAT5_LOCKONGETBLKRQS	0x08000000L /* OPS_LOCKON_GET_BLKRQS is in effect for this lock call */
#define CTSTAT5_SYSIDLISTADD	0x10000000L /* entry added to system file id list */
#define CTSTAT5_NORESOURCEREPL	0x20000000L /* suppress replication of resource add/del/upd */
#define CTSTAT5_FNSHDEL3	0x40000000L /* in ctfnshdel3() routine */
#define CTSTAT5_TRUNCATE	0x80000000L /* create/delete logging during file truncate operation */


/*
** ctstat6 status bits
*/

#define CTSTAT6_KEEPINDEX	0x00000001L /* keep existing index during rebuild/compact */

/*
** ctSIBLING_CTSTATE - Add additional ctstatN state variables here and update
** other locations that are marked with the ctSIBLING_CTSTATE comment.
*/


/* TRANSYS() subtypes */
#define TRANSYS_TRANUSR		0	/* TRANUSR log entry		*/
#define TRANSYS_ALTER_SCHEMA	1	/* alter schema log entry	*/
#define TRANSYS_REPL_RESYNC	2	/* replication file resync	*/
#define TRANSYS_PTADMIN		3	/* PTADMIN() operation		*/
#define TRANSYS_REASSIGN_FILE_ID 4	/* reassigning a file's file id	*/
#define TRANSYS_TRUNCATE_FILE	5	/* ctTruncateFile() operation	*/
#define TRANSYS_CREIFIL		6	/* CREIFIL() operation		*/
#define TRANSYS_SETDEFBLK	7	/* SETDEFBLKX() operation	*/
#define TRANSYS_RESADD		8	/* resource add operation	*/
#define TRANSYS_RESUPD		9	/* resource update operation	*/
#define TRANSYS_RESDEL		10	/* resource delete operation	*/
#define TRANSYS_CREATE_ISAM_INDEX 11	/* create ISAM index operation	*/
#define TRANSYS_DELIFIL		12	/* delete file operation	*/
#define TRANSYS_DROP_ISAM_INDEX 13	/* drop ISAM index operation	*/
#define TRANSYS_RENIFIL		14	/* rename ISAM file operation	*/
#define TRANSYS_ADD_IDFIELD	15	/* add identity field		*/
#define TRANSYS_DEL_IDFIELD	16	/* delete identity field	*/
#define TRANSYS_RESET_IDFIELD	17	/* reset identity field		*/
#define TRANSYS_XTDATR_IDFIELD	18	/* set identity field extended attribute */
#define TRANSYS_CREATE_DATA_FILE 19	/* low-level create of data file */
#define TRANSYS_DELETE_DATA_FILE 20	/* low-level delete of data file */
#define TRANSYS_SYNC_COMMIT	21	/* commit requires sync with replication */

/* when adding a new TRANSYS type here, update printSysTranType() in the ctldmp utility */

/* ctgv's sct_uflg field values */
#define UFLGklusr	0x00000001	/* terminating a connection	      */

/*
** ctFILBLK reverse file map tests (help with multiple open by same user)
*/
#define rvfltestFLMDon	1
#define rvfltestFLMDoff	2
#define rvfltestXTMDon	3
#define rvfltestXTMDoff	4


/* PRMIIDX controls */
#define holdREBUILD	NO
#define doREBUILD	YES
#define completeREBUILD	HYS
#define queueREBUILD	(HYS + 1)

/*
** file definition / format compatibility constants  ctSIBLING_DEF_MASK
**
** In the comment for each constant's definition we indicate if it's used for
** data and index files (F) or transaction logs (L). Some are single-use,
** and others are used for both. And for some bits we define two different
** macro names for the two usages (e.g., DEF_MASK_FLEXREC and DEF_MASK_XTDLOG).
**
** Before reusing a bit for a new file type, double-check that the code only
** currently uses the bit for the old file type.
*/

#define	DEF_MASK_IFIL2	0x00000001L	/* F:extended IFIL structures	*/
#define DEF_MASK_SPCMGT	0x00000002L	/* F:unambig superfile space mgmt */
#define DEF_MASK_PSCL24	0x00000004L	/* F:complete Pascal string def */
#define DEF_MASK_XTDPRM	0x00000008L	/* F:extended permission mask	*/
#define DEF_MASK_OPNTIM	0x00000010L	/* L:tran log file open has time*/
#define DEF_MASK_UNIACS 0x00000020L	/* F:UNIFRMAT alt col seq in IFIL */
#define DEF_MASK_UNIFRM 0x00000040L	/* F:UNIFRMAT create		*/
#define DEF_MASK_HUGEFL 0x00000080L	/* FL:ctHUGEFILE enabled	*/
#define DEF_MASK_HDRSZ4	0x00000100L	/* F:V7 HDRSIZ: 4 * 128		*/
#define DEF_MASK_V6PFIL	0x00000200L	/* FL:V6prime (V7 code w/o HUGE)*/
/* NOTE: DEF_MASK_HUGEFL and DEF_MASK_V6PFIL are mutually exclusive	*/
#define DEF_MASK_CAMSDK	0x00000400L	/* L:ctCAMOsdk in use with log	*/
#define DEF_MASK_PARTIN	0x00000800L	/* F:partition files now exist	*/
					/* does not => file is partition*/
#define DEF_MASK_XTDCMP 0x00001000L	/* F:extended key compression	*/
#define DEF_MASK_DSTKEY 0x00002000L	/* F:track distinct key counts	*/
#define DEF_MASK_DSTSEG 0x00004000L	/* F:track distinct partial counts*/
#define DEF_MASK_DAR	0x00008000L	/* F:DAR support		*/
#define DEF_MASK_CMPREC	0x00010000L	/* F:ctCompressRec file		*/
#define DEF_MASK_PRTENT 0x00020000L	/* F:enhanced IDXENT for GUIx	*/
#define	DEF_MASK_DODA2	0x00040000L	/* F:extended DODA structures	*/
#define	DEF_MASK_DFRIDX	0x00080000L	/* F:deferred index operations	*/
/*			0x00100000L
**
** save 0x00100000 to indicate a second DEF_MASK word is in use
**
** if we run out of DEF_MASK bits, then we use this saved bit to indicate
** library must support 2nd defrel word, say defrel2, in the extended header
*/
#define	DEF_MASK_FLEXREC	0x00200000L	/* F:flexible record format	*/
#define DEF_MASK_XTDLOG 	0x00200000L	/* L:extended TRAN log entries	*/
#define DEF_MASK_CMPLOG		0x00400000L	/* L:log compression enabled	*/
#define DEF_MASK_LOGAUG 	0x00800000L	/* L:augmented log entries:
						**   permits optional contents
						**   at beg of var region in
						**   log entry. each type of
						**   entry has its own content.
						**   lstmbr1 holds map of aug-
						**   mented entries in use.	*/
#define DEF_MASK_HDRVAL		0x01000000L	/* L:HDRVALUE entries in log	*/
#define DEF_MASK_TRANDEP_SCAN	0x02000000L	/* L:pre-scan enabled		*/
#define DEF_MASK_RSTPNT		0x04000000L	/* L:RSTPNT entries in log	*/
#define DEF_MASK_FPGLOK		0x08000000L	/* F:new FPUTFGET locking on Unix */
#define	DEF_MASK_IFIL3		0x10000000L	/* F:IFIL PATH suppression */
#define	DEF_MASK_VLENNOD	0x20000000L	/* F(index): improved node layout */
#define DEF_MASK_LOG_FILE_ID_CHANGE 0x20000000L	/* L:SYSTRAN file ID change log entry */
#define	DEF_MASK_MAXFILE32	0x40000000L	/* L:4-byte file count in chkpnt*/
/* ctSIBLING_LFRM_ERR(1)*/

/* Dynamic defrel bits for transaction log files. These bits are turned on as
needed, typically when a particular type of log entry is written to the log or
when a feature configurable at runtime (such as log encryption) is used. This
allows us to maintain backward log compatibility as long as the particular type
of log entry is not written or the feature is not used. */
#define LOG_FILE_DYNAMIC_DEF_MASK_OPTIONS (DEF_MASK_LOGAUG | DEF_MASK_CAMSDK | \
	DEF_MASK_HDRVAL | DEF_MASK_RSTPNT | DEF_MASK_LOG_FILE_ID_CHANGE)

/* IFIL VERSION */
#ifdef ctBEHAV_PATH_SUPPRESS_IFIL
#define DEF_MASK_IFIL_VER (DEF_MASK_IFIL2|DEF_MASK_IFIL3)
#else
#define DEF_MASK_IFIL_VER (DEF_MASK_IFIL2)
#endif

/*
** NOTE:	DEF_MASK_XTDLOG and DEF_MASK_CMPLOG are not included in
**		    ct_allsup because they only apply to the transaction
**		    log headers, and are managed separately.
**
**		If new log format changes are made that result in log
**		compatibility problems, define a new DEF_MASK_XXXX at
**		ctSIBLING_LFRM_ERR(1). Change the assignment of ctnum->defrel
**		at ctSIBLING_LFRM_ERR(2) as appropriate to include the new
**		DEF_MASK_XXXX. Examine/Update the code just before
**		ctSIBLING_LFRM_ERR(3) if it is necessary to add backward
**		compatibility checks. To support forward compatibilty
**		detection, or-in the new DEF_MASK_XXXX into ct_logsup
**		at ctSIBLING_LFRM_ERR(4). As additional features take
**		advantage of the HDRVALUE log entry, the
**
**			#if defined (ctPARTITIONidxent)
**
**		compiler directive below ctSIBLING_LFRM_ERR(5) will require
**		modification by adding additional "|| defined(...)"
**		terms.
**
**		LOG FORWARD-COMPATIBILITY DETECTION DOES NOT BEGIN UNTIL THIS
**		LINE OF CODE. THAT IS, A SERVER CREATED WITH THIS LINE OF CODE
**		WHICH HAS ct_logsup (formerly DEF_MASK_LOGSUP) DEFINED AS

			(DEF_MASK_OPNTIM | DEF_MASK_HUGEFL |
			 DEF_MASK_V6PFIL | DEF_MASK_XTDLOG |
			 DEF_MASK_CMPLOG)

**		WILL BE CAPABLE OF DETECTING A LOG IT CANNOT SUPPORT. OLDER
**		SERVERS WILL NOT BENEFIT FROM FORWARD LOG COMPATIBILITY
**		DETECTION. [svn revision 1687 September 2005]
*/

/*
** ctSIBLING_LOGMODE2(1)
**
** transaction log flmode2 bits. Used for log states that do not
** require defrel agreement. See ctSIBLING_LOGMODE2(2) for a location
** to turn on a ctLOGMODE2 bit.
*/
#define ctLOGMODE2_TRANDEP_SCAN	0x00000001	/* DELDRAN/RENDRAN in log     */

/*
** augmented log entry bit assignments
*/
#define ctLOGAUG_IDFIELD	0x00000001	/* IDfield updates	     */
#define ctLOGAUG_PRTENT		0x00000002	/* enhanced partition IDXENT */
#define ctLOGAUG_DARWRD		0x00000004	/* DAR state variable updates**
						** ala log header word	     */
#define ctLOGAUG_DFRIDX		0x00000008	/* deferred index operations */
#define ctLOGAUG_TRANSACTION_ID	0x00000010	/* transaction id	     */
#define ctLOGAUG_REPLAGENT_INFO	0x00000020	/* replication agent info    */

/* ctSIBLING_LOGAUG: when adding a new block to the augmented log region,
define a new macro here to use the next available bit, and update the
ctLOGAUG_UNUSED macro below to indicate that the bit has been used. */

#define ctLOGAUG_UNUSED		0xffffffc0	/* unused LOGAUG bits */

/*
** augmented log entry header size: bit map plus length of augmented
** region (including this header size)
*/
#define ctLOGAUGhdrsiz		(2 * ctSIZE(LONG))

/*
** compiler directives that require HDRVALUE support in the transaction
** logs
**
** ctSIBLING_LFRM_ERR(5)
*/
#if defined(ctPARTITIONidxent) || defined(ctFeatDFRIDX)
#define ctLOGHDRVAL
#endif

#ifdef ctFeatXTDCMP
#ifndef ctXTDCMPlength
#define ctXTDCMPlength	255
#endif
#endif

/******************************************************************************/


/*
**		Security Level
**
** except for ct_fcres_lev == ctNOminSecLev, the max of ct_fcres_lev and
** the FCRES specific security level determines the effectice security level
** required for FCRES [i.e., File Definition] resource update operations
*/
#define ctNOminSecLev	-1	/* ctBEHAV_FCRESsec has no effect	*/
#define ctEXCLminSecLev	0	/* an exclusive file lock		*/
#define ctOPFminSecLev	1	/* definition permission + lock		*/
#define ctNSUPminSecLev	2	/* cannot satisfy security		*/
#define ctINTminSecLev	3	/* only internal API calls supported	*/



/* bit masks for use with ct_usrsi */
#define ctMEMidx	0x01
#define ctMEMque	0x02
#define ctMEMswp	0x04
#define ctMEMlok	0x08

#ifdef ctPASCALst
#ifndef ctNotPASCAL24
#define ctPASCAL24
#endif
#endif

#define ctFUNCroot
#ifndef FPUTFGET
#ifndef ctHUGEFILE
#undef  ctFUNCroot
#ifdef MULTITRD
#define gtroot(knum,ownr)	(knum->root1)
#else
#define gtroot(knum)		(knum->root1)
#endif
#endif
#endif

#ifdef ctXMEM
#define cthkey(knum)	(knum->hmem)
#else
#define cthkey(knum)	(knum->kmem ? ctkey(knum->filnum - knum->kmem) : knum)
#endif

#define ctDATEXT	".dat"
#define ctIDXEXT	".idx"
#define UGFNAME	"FAIRCOM.FCS"
#define UGFMODE	(ctSHARED | ctTRNLOG | ctSUPERFILE | ctADMOPEN)

#ifdef ctPREV_27a0718
typedef struct align_test {
	LONG	m1;
	char	m2;
	LONG	m3;
	} ALIGN_TEST;
#else
typedef struct align_test {
	double	m1;
	char	m2;
	double	m3;
	} ALIGN_TEST;
#endif /* ctPREV_27a0718 */

typedef struct _sql_dec
{
	TEXT sign;
	TEXT scale;
	UINT dig0 : 4;
	UINT dig1 : 4;
	UINT dig2 : 4;
	UINT dig3 : 4;
	UINT dig4 : 4;
	UINT dig5 : 4;
	UINT dig6 : 4;
	UINT dig7 : 4;
	UINT dig8 : 4;
	UINT dig9 : 4;
	UINT dig10 : 4;
	UINT dig11 : 4;
	UINT dig12 : 4;
	UINT dig13 : 4;
	UINT dig14 : 4;
	UINT dig15 : 4;
} SQL_DEC, *pSQL_DEC;

typedef struct align_bcd {
	double		m1;
	char		m2;
	SQL_DEC		m3;
	} ALIGN_BCD;
typedef struct align_tim {
	double		m1;
	char		m2;
	double		m3; /* Support CT_TIMES as aligned like a double */
	} ALIGN_TIM;

#ifndef ALIGNMENT_COMP
#define ALIGNMENT_COMP	(SegOff(ALIGN_TEST,m3) - SegOff(ALIGN_TEST,m2))
#endif
#define ALIGNMENT_BCD	(SegOff(ALIGN_BCD ,m3) - SegOff(ALIGN_BCD ,m2))
#define ALIGNMENT_TIM	(SegOff(ALIGN_TIM ,m3) - SegOff(ALIGN_TIM ,m2))

#ifdef REVBIN
#undef REVBIN
#endif
#ifdef LOW_HIGH
#define REVBIN		/* UNIFRMAT_HL_DISK ???? */
#endif
#ifdef HIGH_LOW
#ifdef UNIFRMAT
#define REVBIN
#endif
#endif

#define rtEXTFLDnum	8

#define myioBUFLEN	256

/* pflgchk locales: */
#define ctPFaddkey	1	/* iaddkey	*/
#define ctPFnewrec	2	/* NEWREC	*/
#define ctPFretrec	3	/* iretrec	*/
#define ctPFwrtrec	4	/* WRTREC	*/
#define ctPFdelkey	5	/* ctdelkey	*/
#define ctPFaddrec	6	/* ADDREC	*/
#define ctPFrwtrec	7	/* RWTREC	*/
#define ctPFdelrec	8	/* DELREC	*/
#define ctPFenares	9	/* ENARES	*/
#define ctPFaddres	10	/* ADDRES	*/
#define ctPFdelres	11	/* DELRES	*/
#define ctPFupdres	12	/* UPDRES	*/
#define ctPFnewvrec	13	/* inewvrec	*/
#define ctPFretvrec	14	/* iretvrec	*/
#define ctPFwrtvrec	15	/* WRTVREC	*/
#define ctPFaddvrec	16	/* ADDVREC	*/
#define ctPFdelvrec	17	/* DELVREC	*/
#define ctPFrwtvrec	18	/* RWTVREC	*/
#define ctPFrwtprec	19	/* RWTPREC	*/

#ifdef MULTITRD
#define ctDFcamo	1	/* camo		*/
#define ctDFdelt	2	/* DELFIL	*/
#define ctDFsres	3	/* ctsetres	*/
#define ctDFstop	4	/* STPUSR	*/
#define ctDFuflx	5	/* UNDOFLEX	*/
#define ctDFopnf	6	/* OPNFIL	*/
#define ctDFsupr	7	/* iclsfilx	*/
#define ctDFclsf	8	/* CLSFIL	*/
#define ctDFundc	9	/* undocre2	*/
#define ctDFsfm		10	/* ctdwnfil SFM	*/
#define ctDFdfrk	11	/* ctdwnfil pending deferred index */
#endif

/* inamidx() locale parameter values: */
#define ctNIphdr	1	/* PUTHDR		*/
#define ctNIcrd8	2	/* CREDATX8		*/
#define ctNIcrd4	3	/* CREDATX		*/
#define ctNIcri8	4	/* CREIDXX8		*/
#define ctNIcri4	5	/* CREIDXX		*/
#define ctNIdwnf	6	/* ctdwnfil		*/
#define ctNIopnf	7	/* OPNFIL		*/
#define ctNIrcls	8	/* iclsfix (rflg)	*/
#define ctNIrest	9	/* resetfileid		*/
#define ctNIrbld	10	/* RBLDAT		*/
#define ctNIropn	11	/* ctrcvopn		*/
#define ctNIrop2	12	/* ctrcvopn		*/
#define ctNIrop3	13	/* ctrcvopn		*/
#define ctNItcls	14	/* trancls		*/
#define ctNIsbld	15	/* CTSBLD		*/
#define ctNIsupr	16	/* superfile		*/
#define ctNIupm2	17	/* undo idx add		*/
#define ctNIudr2	18	/* undo idx drop	*/
#define ctNIfdr2	19	/* finish idx drop	*/
#define ctNIspid	20	/* reset supmbr file id */
#define ctNIhwrd	21	/* cthdrword		*/

#define NAMILEN		12
#define NAMINDX		0
#define NAMINDXnum	ct_key
#define LOGINDX		1	/* index file number for auto recovery tfil to c-tree file number map */
#define DNQINDX		2	/* delete node queue memory index file number */

#define DNODE_IDX_KEYLEN 22	/* delete node queue memory index key length */

/* chkopnx() modes: */
#define CO_BASE		1	/* superfile host */
#define CO_CREATE	2	/* creating file */
#define CO_MEMBER	3	/* check superfile member */
#define CO_REGULAR	4	/* regular open */

#define ctTRN_FILES	3
#define ctRT_FILES	3

#ifdef TRANPROC
#define MAXFILt	(MAXFIL + ctTRN_FILES)
#else
#define MAXFILt	MAXFIL
#endif /* ~TRANPROC */

#define ctIFIL_8Padj	32   /* IFIL: per index len adjustment for 8-byte ptr */

typedef ctCONV COUNT (ctVDECL *pCEPFNC)(COUNT ,FILNO ,pVOID ,pLONG ,
				pVOID ,pVRLEN ,COUNT );
#ifdef ctHUGEFILE
typedef pTEXT (*pCAMFNC) (pTEXT ,LONG ,LONG ,VRLEN ,NINT ,LONG ,pTEXT ,LONG ,LONG );
#else  /* ~ctHUGEFILE */
typedef pTEXT (*pCAMFNC) (pTEXT ,LONG ,VRLEN ,NINT ,LONG ,pTEXT ,LONG ,LONG );
#endif /* ~ctHUGEFILE */
typedef NINT  (*pCAMINT) (VOID );

#ifdef PROTOTYPE
typedef ctCONV VOID (*pRBLCBFNC)(ULONG, TEXT, pTEXT);
#else
typedef ctCONV VOID (*pRBLCBFNC)();
#endif

#ifdef PROTOTYPE
typedef ctCONV VOID (*pAPICB)(NINT, NINT, pVOID);
#else
typedef ctCONV VOID (*pAPICB)();
#endif

#ifdef ctFeatMEMTRACK

#ifdef ctPortWIN32
typedef WORD (NTAPI *pRtlCaptureStackBackTrace_t)(
    __in DWORD FramesToSkip,
    __in DWORD FramesToCapture,
    __out_ecount(FramesToCapture) PVOID *BackTrace,
    __out_opt PDWORD BackTraceHash
);
#endif

/*
** Memory allocation header values used to indicate that a memory allocation
** made by a call to mballc() contains a memory tracking header:
*/
#if (ctMEMALIGN >= 8) || defined(ctMEMALIGN8)

/*
** The compilation requires 8-byte alignment, so we have four bytes available
** in the memory allocation header. We set the high bit of the most significant
** byte to indicate that the memory allocation contains a memory tracking
** header.
*/
#define ctMEMALC_HDR8 (TEXT) 0x80

/* Offset of the byte in which we set the memory allocation tracking bit. */
#ifdef LOW_HIGH
#define ctMEMALC_OFF 3
#else
#define ctMEMALC_OFF 0
#endif

#else
/*
** We do not have additional bytes available in the memory allocation header,
** so we set the high bit on the four-byte allocation size value to indicate
** that the memory allocation contains a memory tracking header.
*/
#define ctMEMALC_HDR4 (ULONG) 0x80000000
#endif

#endif /* ctFeatMEMTRACK */

/*
** assigned FairCom resource types (types 0 - 65536 are reserved)
*/
#define FC_MAINspcl	(-1)	/* ctDISTINCTset			*/
#define FC_MAIN		0	/* core file definition resource type	*/
#define FC_CTDB		1	/* CTDB file definition resource type	*/
#define FC_CTDB_VTABLES	2	/* CTDB virtual table definition resource type	*/
#define FC_CTDB_VTABLES_NBR	3	/* CTDB virtual table number definition resource type	*/
#define FC_COBOL	10	/* COBOL resource type			*/
#define FC_RTG		10	/* RTG resource type			*/
#define FC_DAR		11	/* Direct Access Resources
				** can only be added under exclusive
				** control. acts like an extension to
				** file header. not typically updated
				** with UPDRES().
				*/

			/* reserve 3 - 199 for other FC resource types	*/

			/*
			** reserve 200 - 299 for alternative core definitions
			*/
#define FC_MAIN_ALT	200
#define FC_MAIN_END	299

			/*
			** reserve 300 - 399 for alternative CTDB definitions
			*/
#define FC_CTDB_ALT	300
#define FC_CTDB_END	399

			/*
			** 400 - 999 available for other alternative
			** definitions
			*/


#define FC_UNIC		1000	/* Unicode alternative key segment	*/
#define FC_GNXS		1001	/* general purpose extended key segment	*/

			/*
			** reserve 1002 - 1063 for extended key segment types
			*/
#define FC_XKSG		1064	/* end of key segment types + 1		*/

#define FC_LAST		5000	/* end of FairCom core resources + 1	*/

/*
** Direct Access Resources
*/
					/* attrib bit map		*/
#define FC_DAR_reqmtx		0x0001	/* requires a mutex		*/
#define FC_DAR_unique		0x0002	/* only one per file		*/
#define FC_DAR_rednon		0x0004	/* read only file open allowed
					** if this DAR is not supported	*/
#define FC_DAR_dllnam		0x0008	/* darstr contains DLL name	*/
#define FC_DAR_unifmt		0x0010	/* special UNIFRMAT requirements*/
#define FC_DAR_update		0x0020	/* update flag (not permanent)	*/
#define FC_DAR_updtrn		0x0040	/* single user tran update flag
					** (not permanent)		*/
#define FC_DAR_delete		0x0080	/* DAR pending deletion		*/
#define FC_DAR_norbld		0x0100	/* DAR does not require rebuild
					** support			*/

					/* dartyp assignments		*/
#define FC_DAR_ANCHOR		0	/* DAR anchor			*/
#define FC_DAR_IDfield		1	/* identity field definition	*/

					/*
					** add new dartyp's above here and
					** increase FC_DAR_TYPES
					** accordingly
					**
					** ctSIBLING_DAR
					*/
#define FC_DAR_TYPES		2	/* total number of dartyp's	*/
#define FC_DAR_NBR		8	/* size of darnbr array. anchor
					** is not counted in darnbr
					** array. FC_DAR_NBR should be
					** a multiple of 4		*/


		/*
		** FC_DAR_IDfield specific
		** definitions
		*/
#define FC_DAR_IDfieldVer	1
#define FC_DAR_IDfieldAtt	(FC_DAR_unique | FC_DAR_rednon)
#define FC_DAR_IDfieldNam	"Identity Field"

#define IDfield_strval		IDfield->ary.darval8[0]	/* starting value */
#define IDfield_curval		IDfield->ary.darval8[1] /* current value  */
#define IDfield_delta		IDfield->ary.darval8[2]	/* delta	  */
#define IDfield_dodnum		IDfield->ary.darval4[6]	/* DODA field #   */
				/* supporting field values		  */
#define IDfield_dodoff		IDfield->ary.darval4[7] /* fld offset	  */
#define IDfield_dodlen		IDfield->bin.darval4[0] /* fld length	  */
#define IDfield_prvoff		IDfield->bin.darval4[1] /* previous offset*/
#define IDfield_prvlen		IDfield->bin.darval4[2] /* previous length*/
#define IDfield_fixflg		IDfield->bin.darval4[3] /* fixedOffset flg*/
#define IDfield_xtdatr		IDfield->bin.darval4[4] /* xtd attributes */
#define IDfield_ovrlen		IDfield->bin.darval4[5]	/* overflow len	  */

/*
** set ctport.h for IDfield_xtdatr bit values
**
** #define IDfield_xtdatr_......
*/

				/* size of check point list entry	  */
#define IDfield_CHKSIZ		(2 * ctSIZE(LONG) + ctSIZE(LONG8))


	/*
	** add new dartyp specific defines
	** above here
	**
	** ctSIBLING_DAR
	*/


	/*
	** DARmsg: pass DAR field updates back to client side.
	** each DAR specific component must have a size that is
	** a multiple of 4 (i.e., ctSIZE(LONG)).
	**
	** ctSIBLING_DAR
	*/

			/*
			** IDfield
			** msglen + dartyp + offset + len + field value
			*/
#define DARmsgIDfield	(4 * ctSIZE(LONG) + ctSIZE(LONG8))

			/*
			** Total DAR message length
			** tot msglen + DAR instances
			*/
#define DARmsgsiz	(ctSIZE(LONG) + DARmsgIDfield)
#define DARmsgary	(DARmsgsiz / ctSIZE(LONG))

#ifndef RESOURCE
#ifdef ctCAMO
#undef ctCAMO
#endif
#endif /* ~RESOURCE */
#ifndef ctCAMO
#ifdef ctCAMOsys
#undef ctCAMOsys
#endif
#endif /* ~ctCAMO */
#define ctCAMOe		1
#define ctCAMOd		2
#define ctCAMOr		3

#ifdef ctNOGLOBALS
#define ctREG_DEF_ID	"ctREG_DEF_ID"
#define ctREG_DEF_GV	"ctREG_DEF_GV"
#else
#ifdef ctThrds
#define ctREG_DEF_ID	"ctREG_MLT_ID"
#endif
#endif

#define ctSRVRSIDE	1
#define ctCLNTSIDE	2
#ifdef ctSEMCOM
#define LCLNT		3
#define LSRVR		4
#else
#define LCLNT	lclnt
#define LSRVR	lsrvr
#define ctcomrqs(l,sem,wait,by)	ctblkrqs(&l->sem,wait,-2)
#define ctcomwat(l,sem,wait,by)	ctblkwat(&l->sem,wait,-1)
#define ctcomclr(l,sem,by)	ctblkclr(&l->sem,-1)
#endif

/*
#ifndef ctX8convert
#define ctX4members
#endif
#ifndef ctX4members
#ifndef ctHUGEFILE
#define ctX4members
#endif
#endif
*/

#ifdef ctX4members

#define refl		reflk1
#define reblk		reblk1
#define iconpos		iconpos1
#define curp		curp1
#define curt		curt1
#define curr		curr1
#define retnod		retnod1
#define datpos		datpos1
#define datpps		datpps1
#define	phyrec		phyrec1
#define	delstk		delstk1
#define	numrec		numrec1
#define	reshdr		reshdr1
#define	lstmbr		lstmbr1
#define	sernum		sernum1
#define nument		nument1
#define root		root1
#define	lanchr		lanchr1
#define	hdrpos		hdrpos1
#define hdroff		hdroff1
#define nodstk		nodstk1
#define botstk		botstk1
#define nodeid		nodeid1
#define pnodeid		pnodeid1
#define sucesr		sucesr1
#define predsr		predsr1
#define recnum		recnum1
#define phylnk		phylnk1
#define cth_recbyt	cth_recbyt1
#define cth_pos		cth_pos1
#define cth_imgpos	cth_imgpos1
#define cth_chgbyt	cth_chgbyt1
#define cth_nxtpos	cth_nxtpos1
#define rlbpos		rlbpos1
#define sct_npath	sct_npath1
#define sct_lnode	sct_lnode1
#define sct_fnode	sct_fnode1
#define sct_nwnod	sct_nwnod1
#define begnod		begnod1
#define curnod		curnod1
#define prvnod		prvnod1
#define numnod		numnod1
#define ct_nnods	ct_nnods1
#define savbp_node	savbp_node1
#define tranpos		tranpos1
#define shadpos		shadpos1
#define lstent		lstent1
#define abpos		abpos1
#define ct_npath	ct_npath1
#define ct_lnode	ct_lnode1
#define ct_fnode	ct_fnode1
#define ct_nwnod	ct_nwnod1
#define ct_gsrl		ct_gsrl1

#endif /* ctX4members */

#ifdef ctHUGEFILE

#define HUGEOFF(x)	(x)
#define batpos1		batposH[1]
#define batpos2		batposH[0]

#define pLhw	LONG hw,
#define Lhw	hw,
#define lLhw	LONG hw;

#define pPLhw	pLONG phw,
#define PLhw	phw,
#define lPLhw	pLONG phw;

#define pRhw	ctRECPT hw,
#define Rhw	hw,
#define lRhw	ctRECPT hw;

#define pPRhw	pctRECPT phw,
#define PRhw	phw,
#define lPRhw	pctRECPT phw;

#define pFsiz	ULONG fsize2,
#define Fsiz	fsize2,
#define lFsiz	ULONG fsize2;

#define HWt(t)	,t
#define HWv(p)	p
#define HW(p)	p,
#define HWl(t)	t
#define HWw(p)	p;

#ifdef ctFeat6BT
#define pPLhwt	pLONG phwt,
#define PLhwt	phwt,
#define lPLhwt	pLONG phwt;

#define pLhwt	LONG hwt,
#define Lhwt	hwt,
#define lLhwt	LONG hwt;

#define HWT(t)	t,

#else

#define pPLhwt
#define PLhwt
#define lPLhwt

#define pLhwt
#define Lhwt
#define lLhwt

#define HWT(t)
#endif

#else  /* ~ctHUGEFILE */

#define HUGEOFF(x)	(0)
#define pLhw
#define Lhw
#define lLhw

#define pPLhw
#define PLhw
#define lPLhw

#define pRhw
#define Rhw
#define lRhw

#define pPRhw
#define PRhw
#define lPRhw

#define pFsiz
#define Fsiz
#define lFsiz

#define HWt(t)
#define HWv(p)
#define HW(p)
#define HWl(t)
#define HWw(p)

#define pPLhwt
#define PLhwt
#define lPLhwt

#define pLhwt
#define Lhwt
#define lLhwt

#define HWT(t)

#endif /* ~ctHUGEFILE */

#ifdef MULTITRD
/*
** MULTITRD optional function parameters (e.g., see chgField)
*/
#define pHWM(t,v)		t v,
#define HWM(v)			v,
#define lHWM(t,v)		t v;
#define HWMA(x)			x
#else
#define pHWM(t,v)
#define HWM(v)
#define lHWM(t,v)
#define HWMA(x)
#endif

/*
** The file transfer API requires huge file support due to the use of the
** pbrva and pbrvb fields of the comm request structure.
*/
#ifndef ctHUGEFILE
#undef ctFeatTRANSFER_FILE
#endif

#ifndef ctHUGEFILE
#ifdef ctIOSEMAmemfile
#undef ctIOSEMAmemfile
#endif
#endif

#ifndef ctHUGEFILEsegm
#define ctgsize81	ctfsize81
#endif

#ifndef MULTITRD
#ifdef ctFeat6BT
#define cttr_set81(Owner,Tnum2,Tnum)	ct_usrtr(Owner) = Tnum;ct_usrtr2(Owner) = Tnum2
#define cttr_rmv(Owner)			ct_usrtr(Owner) = ct_usrtr2(Owner) = 0
#else
#define cttr_set81(Owner,Tnum)	ct_usrtr(Owner) = Tnum
#define cttr_rmv(Owner)		ct_usrtr(Owner) = 0
#endif
#endif

/*
** exclusive file locks under Unix FPUTFGET
**
** When ctPREV_FPGHDRLOK is NOT defined, then a new header lock request
** will conflict with the ctNOEXCL actions when an exclusive file open
** is attempted. Change to ctLOCK_EXCLUSIVE strategy.
*/
#ifdef FPUTFGET
#if defined(ctPortUNIX) || defined(ctBEHAV_WIN32unxlok)
#ifndef ctPREV_FPGHDRLOK
#ifndef ctLOCK_EXCLUSIVE
#define ctLOCK_EXCLUSIVE	/* support exclusive file locks under Unix */
#endif
#endif
#endif
#endif

/*
** check support for ctBEHAV_CHKSAVE
*/
#ifdef ctBEHAV_CHKSAVE
#ifndef ctFeatCHANNELS
#undef ctBEHAV_CHKSAVE
#else
#ifndef ctALGNCHNL
#undef ctBEHAV_CHKSAVE
#endif
#endif
#endif

/*
** check for ctFeatDYNAMIC_DUMP and/or ctFeatQUIET support
*/
#ifdef ctFeatDYNAMIC_DUMP
#define ctDUMPorQUIET
#else
#ifdef ctFeatQUIET
#define ctDUMPorQUIET
#endif
#endif

/*
** check for ctLOGAUG
**
** requires ctHUGEFILE
*/
#ifndef NO_ctLOGAUG
#ifndef ctLOGAUG
#ifdef ctHUGEFILE
#ifdef TRANPROC
#define ctLOGAUG
#endif
#endif
#endif
#endif

#ifdef ctLOGAUG
#ifndef ctHUGEFILE
#undef ctLOGAUG
#endif
#endif

#if defined(ctBEHAV_IDfield_overflow) && (defined(TRANPROC) && !defined(ctLOGAUG) || !defined(ctFeatDAR))
/* If we turned on ctBEHAV_IDfield_overflow in ctopt2.h, turn it off. */
#ifdef ctBEHAV_IDfield_overflow_ctopt2
#undef ctBEHAV_IDfield_overflow
#else
/* Other code turned on ctBEHAV_IDfield_overflow: ERROR */
#error ctBEHAV_IDfield_overflow requires augmented log support (ctLOGAUG) and DAR support
#endif
#endif

#ifdef ctFeatMAXACTCONN

#ifndef ctWORKMON
/* because of ctaddwork() requirement. */
#error ctFeatMAXACTCONN requires ctWORKMON
#endif

#ifndef ctCACHE_MEMORY
/* because of ctwv() definition. */
#error ctFeatMAXACTCONN requires ctCACHE_MEMORY
#endif

#ifndef ctFeatATOMICop
/* because of atomic increment/decrement of current active connections. */
#error ctFeatMAXACTCONN requires ctFeatATOMICop
#endif

#endif /* ctFeatMAXACTCONN */

/*
** Check ctFeatDFRIDX requirements:
*/
#if defined(ctFeatDFRIDX) && (defined(UNIFRMAT) || !defined(ctHUGEFILE) || \
defined(ctSRVR) && !defined(ctSYSQUEsrvr) || \
defined(TRANPROC) && !defined(ctLOGAUG) || \
defined(ctBNDSRVR))

/* If we turned on ctFeatDFRIDX in ctopt2.h, turn it off. */
#ifdef ctFeatDFRIDXctopt2
#undef ctFeatDFRIDX
#else

/* Other code turned on ctFeatDFRIDX: ERROR */
#if defined(ctSRVR) && !defined(ctSYSQUEsrvr)
#error ctFeatDFRIDX requires system queue support
#else
#error ctFeatDFRIDX requires huge file support
#endif

#if defined(TRANPROC) && !defined(ctLOGAUG)
#error ctFeatDFRIDX requires augmented transaction log support
#endif

#endif

#endif

#if defined(ctFeatDFRIDX) && defined(MULTITRD)
#define ctFeatDFRIDXsrvr
#endif

#if defined(ctFeatRUCB) && !defined(ctFeatDFRIDX)
#ifdef ctFeatRUCBctopt2
#undef ctFeatRUCB
#else
#error Record update callback requires deferred index support
#endif
#endif

#if defined(ctFeatRUCB) && defined(ctSRVR)
#define ctFeatRUCBsrvr
#endif

#if defined(ctFeatPNDIDX) && !defined(ctFeatDFRIDX)
#ifdef ctFeatPNDIDXctopt2
#undef ctFeatPNDIDX
#else
#error Shared mode index create requires deferred index support
#endif
#endif

#if defined(ctFeatPNDIDX) && defined(ctSRVR)
#define ctFeatPNDIDXsrvr
#endif

#if defined(ctFeatFULLTEXTIDX) && !defined(ctFeatRUCB)
#ifdef ctFeatFULLTEXTIDXctopt2
#undef ctFeatFULLTEXTIDX
#else
#error Full text index requires record update callback support
#endif
#endif

/*
** support for single system call to flush all file system buffers
*/

#ifndef ctFlushAllOsBuffers
#ifdef ctPortUNIX
#define ctFlushAllOsBuffers	sync()
#endif
#endif


#ifdef ctFeatNOBUFFERING

/*
** FILE_FLAG_NO_BUFFERING alignment requirement; device dependent, usually 512
*/
#define SECTSZ ctnum->dscsiz

/* align on previous sector boundary */
#define sectaln(x) (ctnum->dscsiz ? ((ULONG)(x) / SECTSZ) * SECTSZ : (x))

/* smallest (N * SECTSZ) > x */
#define sectsz(x) ((((ULONG)(x) / SECTSZ) + 1) * SECTSZ)

#define sectrealn(x) ((ULONG)(x) % SECTSZ)

#else

#define sectaln(x)   (x)
#define sectsz(x)    (x)
#define sectrealn(x) (x)

#endif


/*
**
** support for "bound" common entry point: ctBNDentryPoint
**
** token concatenation macro
**
** using xppf permits macro substitution of ctFPprefix argument prior to
** actual expansion of ppf macro [see A12.3 in K&R 2nd Edition]
*/
#define ppf(pre,body)	pre ## body
#define xppf(pre,body)	ppf(pre,body)

#ifndef ctFPprefix
/*
** default function prefix
** [e.g., xppf(ctFPprefix,ADDKEY) generates ADDKEY -> fp_ADDKEY]
*/
#define ctFPprefix	fp_
#endif
/* ctcatend descriptive location codes */
/* normal locations */
#define CLEAN_ENDLOC	99	/* shutdown occurred for well defined reason. no error logging */
#define BANYON_ENDLOC	98	/* legacy BANYON killsrvr() */
#define APP_ENDLOC	97	/* bound thread shutdown request */

/* 
 * locations less than 97 are handled differently in ctcatend: 
 * - request for non transaction files to be flushed.
 * - logs ctcatend parameters to CTSTATUS.
 **/
#define EXCEPTION_ENDLOC 19	/* OS Exception handler invoked */
#define COMM_ERR_ENDLOC 42	/* Communications init err */
#define EARLYINIT_ENDLOC 73	/* early startup failure */
#define CTREEINIT_ENDLOC 74	/* general startup failure of iintree()  */
#define FATALERR_ENDLOC 0       /* terr, SQL panic, etc */

/* additional bits to pass information to ctcatend */
#define ENDLOC_MASK	0x00FF  /* mask off all LOC_FLAG values */
#define ALLOK_ENDLOC_FLAG  0x8000  /* an externally requested shutdown, applies to CLEAN_ENDLOC only.
				    * process exits with code 0 when set. */ 

/* Modes for connection state functions: */
#define ctCNSTTrepadm	1	/* replication admin state pointer */

/* ctSNAPSHOTmemalc modes */
#define FULLmemalc	1	/* get full ctGMMS structure */
#define TOTmemalc	2       /* get 2 8 byte integers with only totals */

/* Default SSL server certificate file name for client. */
#define CTSSL_DEFAULT_SERVER_CERTIFICATE "ctsrvr.pem"

/* ctSetCommProtocolOption() options: */
#define ctCOMMOPT_FSSLTCP_SERVER_CERTIFICATE	1
#define ctCOMMOPT_FSSLTCP_DEBUG_LOG		2
#define ctCOMMOPT_WRITES_ALLOWED		3
#define ctCOMMOPT_SOCKET_TIMEOUT		4
#define ctCOMMOPT_SOCKET_WAIT_INTERVAL		5
#define ctCOMMOPT_FCTHREADS			6

/* ctSetClientLibraryOption */
#define ctCLIOPT_BROADCAST_READ		1
#define ctCLIOPT_BROADCAST_DEBUG	2

/* cluster options for ctSetClusterOption() */
typedef enum {
	ctCLUSTER_OPTION_FAILOVER = 1, /* enable/disable failover */
	ctCLUSTER_OPTION_SERVER_LIST = 2, /* list of servers */
	ctCLUSTER_OPTION_SERVER_REQUIREMENTS = 3, /* server requirements */
	ctCLUSTER_OPTION_DIAG_CALLBACK = 4 /* diagnostic callback function */
} ctCLUSTER_OPTION;

/* input options for ctClusterConfig() */
typedef enum ctClusterInputOption_t {
	ctCLUSTER_SET_SERVER_REQUIREMENTS = 1 /* set the server requirements */
} ctCLUSTER_INPUT_OPTION;

/* output options for ctClusterConfig() */
typedef enum ctClusterOutputOption_t {
	ctCLUSTER_GET_SERVER_LIST = 1, /* get the server list */
	ctCLUSTER_GET_SERVER_ROLE = 2 /* get the server's role */
} ctCLUSTER_OUTPUT_OPTION;

/* ctclrcon mode values: */
#define CLRCON_ALL	1	/* Close all ISAM contexts for file */
#define CLRCON_FTS	2	/* Reset specified FTS pointer in ISAM contexts */

/* Server configuration modes: */
#define CFGMODE_SETFILE		NO		/* settings file */
#define CFGMODE_CMDLINE		HYS		/* command line */
#define CFGMODE_CFGFILE		YES		/* config file */
#define CFGMODE_RUNTIME		(HYS + 1)	/* runtime */

/* dynamic dump file syncronization */
#ifdef ctBEHAV_DYNDUMP_PROTECT_NODESPLIT
/* requires ctFeatRWLOCK */
#ifndef ctFeatRWLOCK
#undef ctBEHAV_DYNDUMP_PROTECT_NODESPLIT
#endif

#endif

#ifdef ctBEHAV_DYNDUMP_PROTECT_NODESPLIT
#define SMN2(x) SMN(x)
#define DYNDUMP_FILE_LOCK(file,owner)  ctrwlrqs(&file->dumpRWL,CTWRITE,owner)
#define DYNDUMP_FILE_UNLOCK(file,owner) ctrwlclr(&file->dumpRWL,RWCA(CTWRITE,owner))
#define DYNDUMP_FILE_TRYLOCK_SHARED(file,owner) ctrwltry(&file->dumpRWL,CTREAD,owner)
#define DYNDUMP_FILE_LOCK_SHARED(file,owner) ctrwlrqs(&file->dumpRWL,CTREAD,owner)
#define DYNDUMP_FILE_UNLOCK_SHARED(file,owner) ctrwlclr(&file->dumpRWL,RWCA(CTREAD,owner))
#else
#define SMN2(x)
#define DYNDUMP_FILE_LOCK(file,owner) ct_tflstt(file,owner,tflsttGET,ctDYNDMPmod)
#define DYNDUMP_FILE_LOCK_SHARED(file,owner) ct_tflstt(file,owner,tflsttGET,ctDYNDMPmod)
#define DYNDUMP_FILE_UNLOCK(file,owner) ct_tflstt(file,owner,tflsttOFF,ctDYNDMPmod)
#define DYNDUMP_FILE_UNLOCK_SHARED(file,owner) ct_tflstt(file,owner,tflsttOFF,ctDYNDMPmod)
#endif /* ctBEHAV_DYNDUMP_PROTECT_NODESPLIT */

#define AIDX_MARK_MATCHchr '+' /* index path matches data (user requested) */
#define AIDX_MARK_MATCHstr "+"
#define AIDX_MARK_INTERNALchr '*' /* index path matches data */
#define AIDX_MARK_INTERNALstr "*"
#define AIDX_MARK_PREFIXchr '?' /* prefix data name to index */
#define AIDX_MARK_PREFIXstr "?" /* prefix data name to index */
#define FTI_MARK_PREFIXchr '?' /* prefix data name to full text index */
#define FTI_MARK_PREFIXstr '?' /* prefix data name to full text index */
#define FTI_MARK_SUPERFILE_YESchr '!' /* full text index as superfile member in FTI superfile specific for the table*/
#define FTI_MARK_SUPERFILE_YESstr "!" /* full text index as superfile member in FTI superfile specific for the table*/
#define FTI_MARK_SUPERFILE_IDXchr '*' /* full text index created as superfile (specific for the FTI) */
#define FTI_MARK_SUPERFILE_IDXstr "*" /* full text index created as superfile (specific for the FTI) */
#define FTI_MARK_SUPERFILE_DATchr '+' /* full text index as superfile member in the table superfile */
#define FTI_MARK_SUPERFILE_DATstr "+" /* full text index as superfile member in the table superfile */


#ifdef ctBEHAV_PATH_SUPPRESS_IFIL
#define IS_SPECIAL_PUBLIC_AIDXNAM(x) (*(x) == AIDX_MARK_MATCHchr || \
	       *(x) == AIDX_MARK_PREFIXchr)
#define IS_SPECIAL_AIDXNAM(x) ( IS_SPECIAL_PUBLIC_AIDXNAM(x) || \
	       	*(x) == AIDX_MARK_INTERNALchr )

#else
#define IS_SPECIAL_AIDXNAM(x) (0)
#define IS_SPECIAL_PUBLIC_AIDXNAM(x) (0)
#endif

/* modes for ctrstdefx */
#define RSTDEFX_SKIP_PATH_CHANGE 0x00000001

#ifdef ctMIRROR
#define MIRROR_BUILD_AIDXNAM(a,b,c,d,e) buildAidxnam2(a,b,c,d,e)
#else
#define MIRROR_BUILD_AIDXNAM(a,b,c,d,e) buildAidxnam(a,b,c,d)
#endif


#ifdef ctDBGfcqa
#define CTASSERT(x) if(!(x)) { ctbpf(); }
#define CTCHECK(x,y) if((x) != (y)) { ctbpf(); }
#else
#define CTASSERT(x) 
#define CTCHECK(x,y) x
#endif

#define ctSET_STAT_BITS(word,bits) do{CTASSERT(((word) & (bits))==0) (word) |= (bits);}while(0)
#define ctCLR_STAT_BITS(word,bits) do{CTASSERT(((word) & (bits)) == bits) (word) &= ~(bits);}while(0)


#define DBGTREE_NEWROOT 1
#define DBGTREE_NEWCHILD 2 /* non leaf key add -> a child node offset */
#define DBGTREE_NEWPRED 3 /* predsr change */
#define DBGTREE_NEWSUCR 4 /* sucesr change */
#define DBGTREE_DELNODE 5 /* node removed */
#define DBGTREE_DELCHILD 6 /* non leaf key delete -> child node offset */
#define DBGTREE_NODESPLIT 7 /* non leaf split */
#define DBGTREE_FLUSH_LOG 8 /* flush the log */
#ifdef DBGTREEorg
#define DEBUG_TREE_LOG(a,b,c,d,e,f) LogTreeChange(a,b,c,d,e,f)
#define DEBUG_TREE_LOG_COND(cond,a,b,c,d,e,f) if(cond)LogTreeChange(a,b,c,d,e,f)
#else
#define DEBUG_TREE_LOG(a,b,c,d,e,f)
#define DEBUG_TREE_LOG_COND(cond,a,b,c,d,e,f)
#endif


/* 
 * ctDBGCALLBACK
 * enables set_debug_callback(NINT location, DBG_FUNC func) function.
 * the debug_locations enumeration defines the available
 * callback locations
 */
#ifdef ctDBGfcqa
#define ctDBGCALLBACK
#endif
typedef void (*DBG_FUNC)(void);
enum debug_locations
{
	PRUNE_NODE_BEGIN,
	PRUNE_NODE_BEFORE_PREDECESSOR_WRITE,
	PRUNE_NODE_BEFORE_SUCESSOR_WRITE,
	PRUNE_NODE_BEFORE_WRITE,
	PRUNE_NODE_BEFORE_NONLEAF_SUCESSOR_WRITE, 
	PRUNE_NODE_BEFORE_HIGHKEY_WRITE,
	PRUNE_NODE_BEFORE_PARENT_PRUNED,
	PRUNE_NODE_BEFORE_PARENT_WRITE,
	PRUNE_NODE_BEFORE_LOGIDX_END,
	PRUNE_NODE_END,
	SPLIT_NODE_AFTER_LEAF_BEGIN,
	SPLIT_NODE_AFTER_NONLEAF_BEGIN,
	SPLIT_NODE_AFTER_NEWNODE_WRITE,
	SPLIT_NODE_AFTER_OLDNODE_WRITE,
	SPLIT_NODE_AFTER_SUCCESSOR_WRITE, /* leaf only */
	SPLIT_NODE_AFTER_PARENT_TOUCHED,
	SPLIT_NODE_AFTER_ROOT_LEAF_WRITE, /* first root split */
	SPLIT_NODE_AFTER_ROOT_NONLEAF_WRITE,
	SPLIT_NODE_AFTER_ROOT_HEADER_WRITE,
	SPLIT_NODE_BEFORE_END,
	SPLIT_NODE_AFTER_LOGIDX_END,
	DEBUG_INVALID_LOCATION
};
#ifdef ctDBGCALLBACK
#define DEBUG_CALLBACK(loc) debug_callback(loc)
#define DEBUG_CALLBACK_RETURN(loc) debug_callback(loc)
#else
#define DEBUG_CALLBACK(loc)
#define DEBUG_CALLBACK_RETURN(loc) NO_ERROR
#endif




/* Macro to check if DIAGNOSTICS LOWL_FILE_IO logging is enabled. We check the
global setting and the connection state variable, which can be used to suppress
the logging. */
#define ctLOWL_FILE_IO_LOGGING_ENABLED ((ct_diagflg & ctDiagnoseCTSFIO_A) && (!lctgv || !(ctstat5 & CTSTAT5_NOLOWLIOERRLOG)))

#ifdef CTSTAT5_NOLOWLIOERRLOG
/* Suppress the DIAGNOSTICS LOWL_FILE_IO logging for this connection. */
#define ctSuppressLowlFileIOErrorLogging() ctstat5 |= CTSTAT5_NOLOWLIOERRLOG
/* Restore the DIAGNOSTICS LOWL_FILE_IO logging for this connection. */
#define ctRestoreLowlFileIOErrorLogging() ctstat5 &= ~CTSTAT5_NOLOWLIOERRLOG
#else
#define ctSuppressLowlFileIOErrorLogging()
#define ctRestoreLowlFileIOErrorLogging()
#endif

/* hash function calculation for 64-bit values */
#define ctCALCULATE_HASH64(key) \
	key = (~key) + (key << 18); \
	key = key ^ (key >> 31); \
	key = key * 21; \
	key = key ^ (key >> 11); \
	key = key + (key << 6); \
	key = key ^ (key >> 22);

/* ctSyncReplControl() operation codes: */
#define SRC_ADD_AGENT		1	/* add a sync repl agent */
#define SRC_DEL_AGENT		2	/* remove a sync repl agent */
#define SRC_ADD_FILE_AGENT_MAP	3	/* add a sync repl file-agent mapping */
#define SRC_DEL_FILE_AGENT_MAP	4	/* remove a sync repl file-agent mapping */

/* These bits indicate presence of variable-length data in the call to
ctReplGetNextChange(). If present, the data appears in the order in which we
define these bits: */
#define GETNEXTCHANGE_HAS_CMTPOS	0x00000001 /* commit position */

/* List of all varlen bits we have defined to date: */
#define GETNEXTCHANGE_ALL_VARLEN	(GETNEXTCHANGE_HAS_CMTPOS)

#ifndef ctPARTlimit
#ifdef ctFeatPARTITION_BY_TIMESTAMP_DAY
#define ctPARTlimit	65335	/* max. concurrently active partitions */
#else
#define ctPARTlimit	4096	/* max. concurrently active partitions */
#endif
#endif

/* CTPLUGIN.type values */
#define PLUGIN_TYPE_NOT_INIT 0 
#define PLUGIN_TYPE_RUNNABLE 1
#define PLUGIN_TYPE_CALLBACK 2

/* Special arguments to ctPlugin_describe() function */
#define CALLBACK_NUMBER -10000
#define CALLBACK_TOTAL_LENGTH -10001

#ifdef ctDBGfcqa
#define ctSETSTAT5(b) { if (ctstat5 & (b)) { ctbpf(); } ctstat5 |= (b); }
#define ctCLRSTAT5(b) { if (!(ctstat5 & (b))) { ctbpf(); } ctstat5 &= ~(b); }
#else
#define ctSETSTAT5(b) ctstat5 |= (b);
#define ctCLRSTAT5(b) ctstat5 &= ~(b);
#endif

#ifndef ctDBGfcqa
/* Set the specified index buffer's actlen field to the specified value. */
#define CTSETACTLEN(buffer,actlen_value,location) buffer->actlen = (actlen_value)
#endif

/* locations where TREBUF actlen field value is set */
typedef enum {
	SET_ACTLEN_compareKeyOffsetCompress	=  1,
	SET_ACTLEN_compareKeyPadCompress	=  2,
	SET_ACTLEN_ct_set_actlen		=  3,
	SET_ACTLEN_ctinsert81			=  4,
	SET_ACTLEN_ctinsert81_2			=  5,
	SET_ACTLEN_ctinsert81_3			=  6,
	SET_ACTLEN_ctinsert81_4			=  7,
	SET_ACTLEN_ctintnod81			=  8,
	SET_ACTLEN_delexp_1			=  9,
	SET_ACTLEN_delexp_2			= 10,
	SET_ACTLEN_expval_1			= 11,
	SET_ACTLEN_expval_2			= 12,
	SET_ACTLEN_expval_3			= 13,
	SET_ACTLEN_expval_4			= 14,
	SET_ACTLEN_expval_5			= 15,
	SET_ACTLEN_iaddkey			= 16,
	SET_ACTLEN_insexp81_1			= 17,
	SET_ACTLEN_insexp81_2			= 18,
	SET_ACTLEN_nodser_1			= 19,
	SET_ACTLEN_nodser_2			= 20,
	SET_ACTLEN_nodser_3			= 21,
	SET_ACTLEN_nodser_4			= 22,
	SET_ACTLEN_nodser_5			= 23,
	SET_ACTLEN_nodser_6			= 24,
	SET_ACTLEN_nodser_7			= 25,
	SET_ACTLEN_rednod81			= 26,
	SET_ACTLEN_update_unqkeys		= 27,
	SET_ACTLEN_valpnt			= 28
} setactlenloc_t;

#ifdef CTPERM /* this block contains code for internal use only */

#ifdef ctDBGfcqa
/* Check if the new ctstat value has any bits turned on that were off in the original value. */
#define CHECK_CTSTAT_BITS(originalValue,newValue) { \
	NINT	i; \
	for (i=0; i<(NINT) sizeof(LONG); i++) { \
		CTASSERT(!((((originalValue) >> i) & 1) == 0 && (((newValue) >> i) & 1) == 1)); \
	} \
}
#else
#define CHECK_CTSTAT_BITS(originalValue,newValue)
#endif

/* variable declarations for saving the current values of the ctstat state variables */
#define SAVE_CTSTAT_DECLARATIONS \
	LONG	sav_ctstate; \
	LONG	sav_ctstat2; \
	LONG	sav_ctstat3; \
	LONG	sav_ctstat4; \
	LONG	sav_ctstat5; \
	LONG	sav_ctstat6;
/* ctSIBLING_CTSTATE - add declaration for new ctstat state variables here */

/* save the current values of the ctstat state variables */
#define SAVE_CTSTAT_VALUES \
	sav_ctstate = ctstate; \
	sav_ctstat2 = ctstat2; \
	sav_ctstat3 = ctstat3; \
	sav_ctstat4 = ctstat4; \
	sav_ctstat5 = ctstat5; \
	sav_ctstat6 = ctstat6;
/* ctSIBLING_CTSTATE - save new ctstat state variable values here */

/* restore the saved values of the ctstat state variables */
#define RESTORE_CTSTAT_VALUES \
	CHECK_CTSTAT_BITS(sav_ctstate,ctstate); \
	CHECK_CTSTAT_BITS(sav_ctstat2,ctstat2); \
	CHECK_CTSTAT_BITS(sav_ctstat3,ctstat3); \
	CHECK_CTSTAT_BITS(sav_ctstat4,ctstat4); \
	CHECK_CTSTAT_BITS(sav_ctstat5,ctstat5); \
	ctstate = sav_ctstate; \
	ctstat2 = sav_ctstat2; \
	ctstat3 = sav_ctstat3; \
	ctstat4 = sav_ctstat4; \
	ctstat5 = sav_ctstat5; \
	ctstat6 = sav_ctstat6;
/* ctSIBLING_CTSTATE - restore new ctstat state variable values here */

#ifdef ctFeatOPNCNTatomic

/* get the value of opncnt */
#define GET_OPNCNT(ctnum,loc,retval) (retval) = ctInterlockedGet32((ctnum)->opncnt)

/* set opncnt to the specified value, using an atomic operation to serialize updates */
#define SET_OPNCNT(ctnum,value,loc) while (!ctInterlockedCompareExchange32((ctnum)->opncnt,(value),(ctnum)->opncnt)) { ; }

/* increment opncnt, using an atomic operation to serialize updates */
#define INCREMENT_OPNCNT(ctnum,loc) ctInterlockedIncrement32((ctnum)->opncnt)

#else  /* ~ctFeatOPNCNTatomic */

/* get the value of opncnt */
#define GET_OPNCNT(ctnum,loc,retval) { \
	ctmutrqs(ctpopncsema,sOWNR SMN(loc)); \
	(retval) = (ctnum)->opncnt; \
	ctmutclr(ctpopncsema,sOWNR); \
}

/* set opncnt to the specified value, using a mutex to serialize updates */
#define SET_OPNCNT(ctnum,value,loc) { \
	ctmutrqs(ctpopncsema,sOWNR SMN(loc)); \
	(ctnum)->opncnt = (value); \
	ctmutclr(ctpopncsema,sOWNR); \
}

/* increment opncnt, using a mutex to serialize updates */
#define INCREMENT_OPNCNT(ctnum,loc) { \
	ctmutrqs(ctpopncsema,sOWNR SMN(loc)); \
	(ctnum)->opncnt++; \
	ctmutclr(ctpopncsema,sOWNR); \
}

#endif /* ~ctFeatOPNCNTatomic */

/* reset opncnt value to 1 */
#define RESET_OPNCNT(ctnum,loc) { \
	SET_OPNCNT(ctnum,1,loc) \
	if ((ctnum)->psuper) { \
		SET_OPNCNT((ctnum)->psuper,1,loc) \
	} \
}

/* unique location codes for calls to ctrcvopn81() */
enum ctrcvopn_unqloc {
	RCVOPN_OPNRENTRAN	=  1,	/* opnrentran() */
	RCVOPN_SCAN_CLSTRAN	=  2,	/* transcn81() for CLSTRAN entry */
	RCVOPN_SCAN_DELTRAN	=  3,	/* transcn81() for DELTRAN entry */
	RCVOPN_SCAN_CHKPNT	=  4,	/* transcn81() for CHKPNT entry */
	RCVOPN_SCAN_OPNTRAN	=  5,	/* transcn81() for OPNTRAN entry */
	RCVOPN_SCAN_CRETRAN	=  6,	/* transcn81() for CRETRAN entry */
	RCVOPN_TRANUND_CLSTRAN	=  7,	/* tranund() for CLSTRAN entry */
	RCVOPN_TRANRED_OPNTRAN	=  8,	/* tranred() for OPNTRAN entry */
	RCVOPN_REDOCRE		=  9,	/* ctredocre1() */
	RCVOPN_RENTRANDEP_ORIG	= 10,	/* ctrentrandep() for original file name */
	RCVOPN_RENTRANDEP_HOST	= 11,	/* ctrentrandep() for original superfile host file name */
	RCVOPN_RENTRANDEP_REN	= 12,	/* ctrentrandep() for renamed file name */
	RCVOPN_UNDODEL_SUPMBR	= 13,	/* ctundodel1() for superfile member */
	RCVOPN_UNDODEL		= 14,	/* ctundodel1() */
	RCVOPN_UNDOREN		= 15	/* ctundoren1() */
};

/* unique location codes for calls to set file closed at end of recovery flag */
enum ctrcvSetFileClosedFlagLocation {
	SET_FILE_CLOSED_FLAG_1	=  1,
	SET_FILE_CLOSED_FLAG_2	=  2,
	SET_FILE_CLOSED_FLAG_3	=  3,
	SET_FILE_CLOSED_FLAG_4	=  4,
	SET_FILE_CLOSED_FLAG_5	=  5,
	SET_FILE_CLOSED_FLAG_6	=  6,
	SET_FILE_CLOSED_FLAG_7	=  7,
	SET_FILE_CLOSED_FLAG_8	=  8,
	SET_FILE_CLOSED_FLAG_9	=  9,
	SET_FILE_CLOSED_FLAG_10	= 10,
	SET_FILE_CLOSED_FLAG_11	= 11,
	SET_FILE_CLOSED_FLAG_12	= 12,
	SET_FILE_CLOSED_FLAG_13	= 13
};

/* unique location codes for calls to clear file closed at end of recovery flag */
enum ctrcvClearFileClosedFlagLocation {
	CLEAR_FILE_CLOSED_FLAG_1	= 1,
	CLEAR_FILE_CLOSED_FLAG_2	= 2,
	CLEAR_FILE_CLOSED_FLAG_3	= 3
};

#endif /* CTPERM - end of block containing code for internal use only */

/* get the next file list entry */
#define GET_NEXT_FILE_LIST_ENTRY(pfilelistEntry) (pctFILE_LIST_ENTRY)((pTEXT) (pfilelistEntry) + 3 * sizeof(ULONG) + (strlen((pfilelistEntry)->filename) + 1 + 3) / 4 * 4)

/* 
 * reference for FUSR variables
 * that exist in the CTFILE for standalone.
 */
#ifdef MULTITRD
#define GET_FUSR_MEMBER(fu,ctnum,member) (fu)->member
#else
#define	GET_FUSR_MEMBER(fu,ctnum,member) (ctnum)->member
#endif

/* size of the specified member of the specified structure */
#define SizeOfStructMember(struc,member) sizeof(((struc *)0)->member)

#ifdef ctCLIENT
#define LogMUSR_ERR(x) x
#endif

#endif /* ctOPT2H */

/* end of ctopt2.h */
