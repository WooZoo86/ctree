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

#ifndef ctGVARH
#define ctGVARH

#ifdef ctPortVINES
#ifdef RUNTCBTABLE
#define ctTASKER_H	"tasker.h"
#include ctTASKER_H
#endif
#endif

#ifdef MTDEBUG
EXTERN int bomb;
#endif
#ifdef MTRCVR
EXTERN int ebomb;
#endif

#include "ctrkey.h"

#include "ctstrc.h"
#ifdef CTBOUND
#include "ctbond.h"
#ifdef ctFeatAUTO_SHMEM
#include "ctcomm.h"
#endif
#else
#include "ctcomm.h"
#endif /* CTBOUND */
#ifdef ctFeatKEYCOMPRESSsRLE
#include "ct_srle.h"
#endif
/*
** optional instance handle types, prototypes and arguments
*/

#ifdef pupdN
#undef pupdN
#endif
#define UPD(xx)	, xx
#define updN	, updLoc
#define pupdN	, UINT	updLoc
#define lupdN	UINT	updLoc;

#ifdef pioN
#undef pioN
#endif
#ifdef ctFeatION	/* I/O locale Number */
#define ION(xx)	, xx
#define ioN	, ioLoc
#define pioN	, UINT	ioLoc
#define lioN	UINT	ioLoc;
#else
#define ION(xx)
#define ioN
#define pioN
#define lioN
#endif

#ifdef MULTITRD
#define inTName		pCTGV
#define ct_inName	lctgv
#define inExists

#ifdef ctSUPPRESS_thHandle
#define ctSTH
#else
#define thTName		NINT
#define thName		sOWNR
#define thExists
#endif /* ~ctSUPPRESS_thHandle */
#endif /* MULTITRD */

#ifdef ctThrdApp
#define inTName		pCTGVAR
#define ct_inName	ctWNGV
#define inExists
#endif /* ctThrdApp */

#ifdef ctMTFPGreentrant
struct ctgvars; /* forward declaration */
#define thTName		struct ctgvars *
#define thName		ctWNGV
#define thExists
#endif

#ifdef inExists
#define inType1		inTName
#define inHan1		ct_inName
#define pinHan1		inTName ct_inName
#define inType		, inType1
#define inHan		, inHan1
#define pinHan		, pinHan1
#define linHan		inTName ct_inName;
#else
#define inHan1
#define pinHan1		VOID
#define inType
#define inHan
#define pinHan
#define linHan
#endif /* ~inExists */

#ifdef thExists
#define thType1		thTName
#define thHan1		thName
#define pthHan1		thTName thName
#define thType		, thType1
#define thHan		, thHan1
#define pthHan		, pthHan1
#define lthHan		thTName thName;
#else
#define thType
#ifdef InstantC
#define thHan1		0
#else
#define thHan1
#endif

#define thHan
#define pthHan1		VOID
#define pthHan
#define lthHan
#endif /* ~thExists */

typedef ctRECPT 	   ctLFN;
#define pctLFNdef
typedef ctCONV ctLFN	(ctDECL	 *pctLFN)(FILNO, pVOID, pVOID);
typedef ctCONV ctLFN	(ctDECL	 *pctLFN2)(FILNO, pVOID);
typedef COUNT		 (*plcnFN)(NINT, FILNO, pVOID ,pVRLEN thType);

/*
** parameter structures for compression routines (ctCMPREC)
*/

typedef struct ctzlib1 {	/* zlib version 1 */
	NINT	level;
	NINT	method;
	NINT	windowBits;
	NINT	memLevel;
	NINT	strategy;
	} ctZLIB1, *pctZLIB1;

#ifdef ctDBGSEMCNT
#define ctDBGSEMMOD	73
#define ctDBGSEMCAL	100
				/*
				** last of ctDBGSEMMOD (72xx) used for
				** breakdown of SEMCNTs for LISTYPE sema's. so
				** the range of ordinary SMN numbers is
				** 0000 to HH99 where HH is ctDBGSEMMOD - 2.
				*/

EXTERN	ULONG	ctsemcnt[ctDBGSEMMOD][ctDBGSEMCAL];
#ifdef ctDBGSEMBLK
#ifdef ctDBGSEMTIM
EXTERN	LONG8	ctsemtim[ctDBGSEMMOD][ctDBGSEMCAL];
#endif
EXTERN	ULONG	ctsemblk[ctDBGSEMMOD][ctDBGSEMCAL];
EXTERN	ULONG	ctsemout[ctDBGSEMMOD][ctDBGSEMCAL];
#endif
#endif /* ctDBGSEMCNT */

#ifdef ctDBGDLNGCNT
#define ctDBGDLNGMOD	60
#define ctDBGDLNGCAL	100
EXTERN	ULONG	ctdlngcnt[ctDBGDLNGMOD][ctDBGDLNGCAL];
EXTERN	NINT	ctdlngtyp[ctDBGDLNGMOD][ctDBGDLNGCAL];
#endif /* ctDBGDLNGCNT */

#ifdef ctDBGfcbio
EXTERN NINT	ctdbgfcbio_filno;	/* System file number of target file	*/
EXTERN RNDFILE	ctdbgfcbio_filhnd;	/* File descriptor of target file	*/
#endif

#ifdef TRANPROC
#include "cttran.h"
#endif

#ifdef ctCAMO
#define ctCAMSYSLEN	128
EXTERN pCAMFNC	ctglocamo;
EXTERN pCAMINT	ctintcamo;
EXTERN ULONG	ctcamblk;
EXTERN NINT	ctcamsln;
EXTERN NINT	ctcamlog;
EXTERN NINT	ctcamadmn;
EXTERN TEXT	ctcamsky[ctCAMSYSLEN];
#endif

typedef struct {
#ifdef RTREE
	RKEY	s1usrkey;
	RDAT	s1usrdat;
#endif
	FILNO	s1ct_dtmap;
	FILNO	s1ct_rvmap;
#ifdef ctCONDIDX
	COUNT	s1ct_rlkey;
#endif
	COUNT	s1ct_nlkey;
	TEXT	s1ct_nlchr;
	TEXT	s1ct_vfin;
	} CTIS1;
typedef CTIS1 ctMEM *	pCTIS1;

typedef struct {
	COUNT	s2ct_sgpos;
	COUNT	s2ct_sglen;
	COUNT	s2ct_sgmod;
#ifdef ctXTDKEYSEG
	NINT	s2ct_sghnd;
#endif
	} CTIS2;
typedef CTIS2 ctMEM *	pCTIS2;
typedef CTIS2 ctMEM * ctMEM * ppCTIS2;

			/* Global Variables */

#ifdef ctThrds
EXTERN NINT	ctgv_max;
EXTERN LONG	ctgv_mode;
#endif

/****************************************/
#ifdef ctThrds
#ifndef ctNOGLOBALS
/*
** application threads co-existing with server kernel threads
*/
typedef struct ctsvars
{
   struct ctsvars ctMEM
	       *pinstance;	/* instance link			*/
 NINT		ct_taskid;	/* owner id for this instance		*/
 TEXT		instname[IDZ];	/* name of this instance block		*/
} CTSVAR, ctMEM * pCTSVAR, ctMEM * ctMEM * ppCTSVAR;

EXTERN CTSVAR	ctWNSV[MXU2];
#endif
#endif
/****************************************/

#ifdef __cplusplus
extern "C" {
#endif

EXTERN UINT timulx,emitx;
EXTERN UINT sigdevstt;

#ifdef __cplusplus
}
#endif


#ifdef ctNOGLOBALS

#ifdef ctLOCLIB
#define CTBOUNDvar
#define UNBOUNDvar
EXTERN pCOUNT (*ctlfseggetp)(FILNO , COUNT ,ppCOUNT );
EXTERN VOID   (*ctlfsegputp)(FILNO ,COUNT ,COUNT ,COUNT ,COUNT );
EXTERN COUNT  (*ctgetseginfop)(FILNO ,COUNT ,COUNT );
#endif

#endif /* ctNOGLOBALS */

#if defined(ctNOGLOBALS) || defined(ctFeatSRVDLL)

#ifdef CTBOUND
#ifndef CTBOUNDvar
#define CTBOUNDvar
#endif
#else /* CTBOUND */
#ifndef UNBOUNDvar
#define UNBOUNDvar
#endif
#endif /* CTBOUND */

#ifdef ctNOGLOBALS
#define NUMHGHBINS	64
#else
#define NUMHGHBINS	1024	/* See also ctrcvr_s.c, ctrcvr_x.c	*/
#endif

/* dynamic dump recovery list element */
typedef struct rcvlstele {
	struct rcvlstele *
		next;	/* next entry in this hash bin */
	pLONG	lstbuf;	/* pointer to ct_rcvlst list entry */
	TEXT	filnam_full[MAX_NAME]; /* file name converted to full path */
} RCVLSTELE, * pRCVLSTELE;

/* dynamic dump recovery list hash table */
typedef struct rcvlsthsh {
	pRCVLSTELE h; /* head of list for this hash bin */
	pRCVLSTELE t; /* tail of list for this hash bin */
} RCVLSTHSH, * pRCVLSTHSH;

#ifdef ctFeatCLUSTER_OPTIONS

/* cluster diagnostic opcodes */
typedef enum clientClusterDiagOpcode_t {
        CLIENT_CLUSTER_DIAG_CONNECT_TO_SPECIFIED_SERVER = 1, /* connect to server name passed in */
        CLIENT_CLUSTER_DIAG_CONNECT_TO_CURRENT_SERVER = 2, /* connect to current server */
        CLIENT_CLUSTER_DIAG_CONNECT_TO_NEXT_SERVER = 3, /* connect to next server in list */
        CLIENT_CLUSTER_DIAG_CONNECT_TO_REDIRECTED_SERVER = 4 /* connect to redirected server name */
} CLIENT_CLUSTER_DIAG_OPCODE;

/* cluster diagnostic callback function */
typedef NINT (*pCLIENT_CLUSTER_DIAG_CALLBACK)(NINT opcode,pTEXT format, ...);

/* client side cluster state info */
typedef struct clientClusterState_t {
	pTEXT	serverList; /* list of servers for high availability as a JSON string */
        pTEXT   serverConnectionAttempted; /* one byte for each server list entry; non-zero indicates we tried connecting to that server */
	pTEXT	serverRequirements; /* requirements for server as a JSON string */
	pVOID	serverListJsonObject; /* list of servers for high availability as a JSON object */
        pCLIENT_CLUSTER_DIAG_CALLBACK diagnosticCallbackFunction; /* diagnostic callback function */
	TEXT	useFailover; /* non-zero if failover is enabled */
	NINT	currentServer; /* index of current server in server list */
        NINT    currentDbEngine; /* id of server we're currently connected to */
        NINT    redirectedDbEngine; /* id of server we should connect to */
        NINT    numberOfServers; /* number of servers in server list */
} CLIENT_CLUSTER_STATE, *pCLIENT_CLUSTER_STATE;

#endif /* ctFeatCLUSTER_OPTIONS */

typedef struct ctgvars
{
   pCEPFNC	ctcepfnc;	/* ctree single entry point func ptr 	*/
   struct ctgvars ctMEM
	       *pinstance;	/* instance link			*/
   TEXT		instname[IDZ];	/* name of this instance block	*/
   COUNT	sctusrprf;	/* user profile word */
   COUNT	suerr_cod;	/* user error cod */
   COUNT	sisam_err;
#ifdef ctPortWINKE
   LONG		ssysiocod;	/* system error cod */
#else
   COUNT	ssysiocod;	/* system error cod */
#endif
   FILNO	sisam_fil;

/************************************************************************
 * NOTE: Do not add fields to the CTGVAR structure above this comment,
 *       so that the offsets of the above fields remain unchanged from
 *       release to release.
 ************************************************************************/

   pVOID	psysvar;	/* pointer to system-wide  variables	*/
   pVOID	pusrvar;	/* pointer to user-private variables	*/
   pVOID	pctcalbks;	/* pointer to function callbacks	*/
   pVOID	sctcidxStk;	/* conditional index stack 		*/
#ifdef ctHUGEFILE
#ifdef ctBEHAV_TRANDEP_SCAN
   pREVDEL	srevpre_ptr;	/* reversible delete file name list	*/
#endif
   pREVDEL	srevdel_ptr;	/* reversible delete file name list	*/
   pNUMRECHGH	snumhgh_ptr;	/* numrec high water mark list		*/
#else
   pVOID	srevdel_ptr;	/* reversible delete file name list	*/
   pVOID	snumhgh_ptr;	/* numrec high water mark list		*/
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
   ppCMPRECRES	scmprec_ptr;	/* unique compresion resource list	*/
#else
   pVOID	scmprec_ptr;
#endif
   pDEDLST	sdedlst_ptr;	/* dedicated file list anchor		*/
   pRENRST	srenrst_ptr;	/* rename recovery list anchor		*/
   pSEGLST	sseglsthdr;	/* pending segment list header		*/
   pTEXT	sct_trnfil;	/* tran undo file list			*/
   UNLONG	ct_taskid;	/* save task ID info			*/
   LONG		sctnusers;	/* number of users			*/
#if defined ctCLIENT && !defined ctFeatL10_serno
   LONG		sctdivs;
#else
   LONG		xctdivs;
#endif
#ifdef ctCAMOsdk
   LONG		sctcamver;
#else
   LONG		xctcamver;
#endif
#ifdef ctFeatRECRLOCK
   LONG		snetrecr;
#else
   LONG		xnetrecr;
#endif
   ULONG	sctITIMlimit;
#ifdef ctBEHAV_ITIM_DEFER
   ULONG	sctITIMdefer;
#endif
#ifdef ctCMPLOG
   NINT		slogcmpcnt;	/* usage counter			*/
   VRLEN	slogcmplen;	/* log compression buffer length	*/
   pTEXT	slogcmpbuf;	/* ptr to log compression buffer	*/
#endif
   LONG		scthghwrd;
   LONG		sctops;		/* set operation state bit mask		*/
   LONG		sctstate;	/* internal state bit mask		*/
   LONG		sctstat2;	/* internal state bit mask 2		*/
   LONG		sctstat3;	/* internal state bit mask 3		*/
   LONG		sctstat4;	/* internal state bit mask 4		*/
   LONG		sctstat5;	/* internal state bit mask 5		*/
   LONG		sctstat6;	/* internal state bit mask 6		*/
/* ctSIBLING_CTSTATE - Add new state variable here */
   VRLEN	sctxvlen;	/* vlen combined op max buffer length	*/
   NINT		sctstatg;	/* keyseg distinct count indicator	*/
   NINT		smemsubflg;	/* memory subsystem flag		*/
   UINT		sct_trnfilsz;	/* size of ct_trnfil */
   UINT		sctdfrcls;	/* defer close count */
   NINT		ctusraflg;	/* attach flag */
   NINT		sct_dftot;
   NINT		sct_dfnum;
#ifdef ctFeatDISKFULLaction
   NINT		sct_dfatot;
   NINT		sct_dfanum;
#endif
#ifdef ctFeatFILMTX
   NINT		sfilmtx_tot;
   NINT		sfilmtx_num;
#endif
   NINT		sctcidxStkPtr;
   NINT		sctcidxCurCmd;
#ifdef ctFeatUDF_EXPR
   pVOID	sudflist;
   NINT		sisexpreval;
#endif
#ifdef ctBEHAV_TRANDEP_SCAN
   NINT		srevpre_tot;
   NINT		srevpre_cur;
#endif
   NINT		srevdel_tot;
   NINT		srevdel_cur;
   NINT		snumhgh_tot;
   NINT		snumhgh_cur;
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
   NINT		scmprec_tot;
   NINT		scmprec_cur;
#else
   NINT		scmprec_tot_fake;
   NINT		scmprec_cur_fake;
#endif
   NINT		sdedlst_tot;
   NINT		sdedlst_cur;
   NINT		sdedlst_avl;
   NINT		srenrst_tot;
   NINT		srenrst_cur;
   NINT		scthshift;	/* huge shift				*/
   NINT		sctmaxparm;
   NINT		sctrunfil;
   NINT		sctrcvfil;
   NINT		sct_adfil;
   NINT		sfrschgset;
   NINT		scurchgset;
   NINT		sfrschgbat;
   NINT		scurchgbat;
   COUNT	scndxerr;
   SYSNO	sct_mxfil;	/* maximum files specified in intree. 	*/
#ifdef ISAM_VARS
#ifdef RTREE
   SYSNO	ssrtknm,ssrtdat,stmpdat;
#endif
#endif
   UTEXT 	sct_uflvr;
   UTEXT 	sct_ualgn;
   UTEXT	sct_upntr;	/* client pointer size */
#ifdef CTBOUND
   pVOID		scommCmds[MAXCOMMP];
#else
   pCommFuncPtrs	scommCmds[MAXCOMMP];
#endif
   pVOID		scommGbls[MAXCOMMP];
   COUNT	snocamocomm;
#ifdef ctCLIENT
   pltICON	scthicon[ctCONBINS];
#else
   pVOID	cthiconfake[ctCONBINS];
#endif
#ifdef RB_CALLBACK
   pRBLCBFNC	srblcbfnc; /* ptr to rebuild callback func */
#ifdef ctFeatREBUILD_CALLBACK_STATE
   pctRBCBST	srblpcbst; /* pointer to rebuild callback state */
#endif
#endif
#ifdef ctFeatVFYIDX_CS
   pVFYMSGCBFNC	svfymsgcbfnc; /* index verify message callback function	*/
   pVFYPRGCBFNC	svfyprgcbfnc; /* index verify progress callback function*/
   NINT         svfyflags;    /* index verify internal options		*/
#endif
#ifdef ctFeatVERIFYfile
   pVFYERRCBFNC	svfyerrcbfnc; /* file verify error callback function    */
#endif
#ifdef ctFeatRTG_API
   pRTGMSGCBFNC	srtgmsgcbfnc; /* RTG message callback function */
   pVOID	srtgmsgcbusrctx; /* RTG message callback user context ptr */
#endif
#ifdef ctFeatCOPYFILE
  pCPYFNC	scpfprgcbfnc; /* ctCopyFile progress callback function */
#endif
#ifdef ctFeatTEMPDIR
  pTDRFNC	stdrprgcbfnc; /* ctTempDir progress callback function */
#endif
#ifdef ctFeatDYNDMPstream
   pDYNDMPCBFNC	sdyndmpcbfnc; /* Dynamic dump stream callback function  */
   pVOID	sdyndmpcbctx; /* User-defined state pointer		*/
   ULONG	sdyndmpopts;  /* Dynamic dump options			*/
   ULONG	sdyndmpcbsiz; /* Communication buffer size		*/
#endif

/*
** Above this location in the structure, the standalone and client structures
** are identical. Add new fields above this comment that you wish to reside at
** the same offset in the standalone and client models.
*/

#ifdef ctFeatSET_ALIGN
   TEXT		sappalign;	/* application data alignment		*/
#endif

#ifdef ctFeatLOGONSECtr
   pLSHCBFNC	sctlshfnc;	/* secure logon hash callback function	*/
#else
   pVOID	xsctlshfnc;	/* secure logon hash callback function	*/
#endif
#ifdef ctFeatCLIENTID
   pVOID	spcidblk;	/* client id info block			*/
   VRLEN	scidblklen;	/* size of client id info block		*/
#else
   pVOID	xpcidblk;
   VRLEN	xcidblklen;
#endif

#if defined(CTBOUNDvar) || defined(ctFeatOTREE) || defined(otOTREE)
   LSTANC	sctlist[NUMCTLIST];
   CTFILE   sctfmru;
   pCTFILE  sct_mru;
   ppCTFILE sctfcbhdr;
   ppctICON sctconanc;
#ifdef DBGtree
   pVOID	 sct_walkh;	/* tree walk header			*/
   pVOID	 sct_walkt;	/* tree walk tail			*/
   NINT		 sctlflg;	/* load flag				*/
#endif /* DBGtree */
#ifdef ctFeatPARTITION_ESTIMATE
   NINT		 sctprtestlimit;/* maximum partitions to sample		*/
   NINT		 sctprtestpct;	/* max percent of partitions to sample	*/
#endif
#ifdef ctFeatFILEBLOCKcounter
   ULONG	 sctfilblkcnt;	/* current number of file blocks	*/
#endif
   NINT		 sct_initerr;	/* c-tree initialization failed		*/
#ifdef ctFeatFILENAMEhash
   pFNAMHSH	 sct_fnhash;	/* open file name hash table		*/
   UINT		 sct_fnbins;	/* open file name hash bin count	*/
#endif
#ifdef ctFeatLOGLMT
   pLLHSH	 sct_llhash;	/* user/group logon limit hash table	*/
   UINT		 sct_llbins;	/* user/group logon limit hash bin count*/
#ifdef ctFeatLOGLMTusracct
   NINT		 ndusracct;	/* distinct user accounts currently logged on */
   NINT		 mdusracct;	/* maximum distinct user accounts allowed */
   NINT		 mcusracct;	/* maximum connections per user account */
#endif
#endif
#ifdef ctFeatAUTO_MKDIR
   NINT		 sctautomkdir;	/* automatically create directories	*/
#endif
   pTREBUF	 sct_btree;	/* ptr to beg of b-tree buffers		*/
   pDATBUF	 sct_dbufr;	/* ptr to beg of data file buffers	*/
   pCTFILE	 sct_key;	/* ptr to beg of ct_key file structures	*/
   pCTFILE	 sct_dat;	/* ptr to beg of data file structures	*/
   pCTFILE	 sct_vat;	/* ptr to beg of var data file struc	*/
#ifdef ctDYNHASH
   pULOKHSH	 sct_locksb;
   HSHSTT	 sct_lokstt;
#else
   pLOKS	 sct_locksb[LOKHBINS];
   pLOKS	 sct_ltailb[LOKHBINS];
#endif
   pDFDEF	 sct_dfdef;
#ifdef ctFeatDISKFULLaction
   pDFDEF	 sct_dfadef;	/* DISK_FULL_ACTION list */
#endif
#ifdef ctFeatFILMTX
   pFILMTX	 sfilmtx_ary;
#endif
#ifdef DBGhash
   LONG	 	 sdbg_lhsh_u[LOKHBINS];
#endif
   LONG	 sctactfil;	/* c-tree files physically opened	*/
   LONG	 scttotfil;	/* c-tree files opened			*/
   LONG	 scttotblk;	/* c-tree file control blocks in use	*/
   LONG	 sctactfilx;	/* max files physically opened	*/
   LONG	 scttotfilx;	/* max files opened			*/
   LONG	 scttotblkx;	/* max file control blocks in use	*/
   LONG  sctloknmx;	/* max net locks			*/
   LONG	 sct_spc;
#ifdef ctFeatCFG_SCALE_N8
   LONG8 sct_disklmt;	/* disk full threshold			*/
#else
   ULONG sct_disklmt;	/* disk full threshold			*/
#endif
   ULONG sct_dbrqs;	/* data buffer requests			*/
   ULONG sct_dbhit;	/* data buffer hits			*/
   ULONG sct_ibrqs;	/* index buffer requests		*/
   ULONG sct_ibhit;	/* index buffer hits			*/
   ULONG sct_rdops;	/* number of read operations		*/
   ULONG sct_rdbyt;	/* bytes read				*/
   ULONG sct_wrops;	/* number of write operations		*/
   ULONG sct_wrbyt;	/* bytes written			*/
   ULONG sct_rcops;	/* number of comm read operations	*/
   ULONG sct_rcbyt;	/* comm bytes read			*/
   ULONG sct_wcops;	/* number of comm write operations	*/
   ULONG sct_wcbyt;	/* comm bytes written			*/
   ULONG sctwlgops;	/* number of log write operations	*/
   ULONG sctwlgbyt;	/* bytes written to log file		*/
   ULONG sctrlgops;	/* number of log read operations	*/
   ULONG sctrlgbyt;	/* bytes read from log file		*/
   ULONG sctxlgops;	/* number of log extension operations	*/
   ULONG sctxlgbyt;	/* log file extension bytes		*/
   ULONG sct_trbeg;	/* # transaction begins			*/
   ULONG sct_trend;	/* # transaction ends			*/
   ULONG sct_trabt;	/* # transaction aborts			*/
   ULONG sct_trsav;	/* # transaction savepoints		*/
   ULONG sct_trrst;	/* # transaction restores		*/
   ULONG sct_trfls;	/* # transaction flush log writes	*/
   ULONG sct_ribs;
   ULONG sctsync_dosfls;/* DOSFLUSH sync calls			*/
   ULONG sctsync_logfil;/* transaction log sync calls		*/
   ULONG sctsync_regfil;/* c-tree file sync calls		*/
   ULONG sct_abseq;	/* abort list sequence number		*/
   LONG	 sct_abnod;	/* abort list node count		*/
   LONG	 sct_cmnod;	/* pending node tran count		*/
   LONG	 sct_cmdat;	/* pending data tran count		*/
   LONG	 sct_statflg;	/* CTSTATUS flag			*/
   LONG	 sct_sysviewT;	/* SYSVIEW WHAT				*/
   LONG	 sct_sysviewN;	/* SYSVIEW WHEN				*/
   LONG  sct_langflg;	/* LANGUAGE flag			*/
#ifdef ctNogloTran
   LONG	 sct_numvi;	/* vulnerable index update count	*/
   ULONG sendcnt;	/* end log count			*/
#endif
   LONG	 sct_compflg;	/* 1st compatibility word		*/
   LONG	 sct_compflg2;	/* 2nd compatibility word		*/
   LONG	 sct_compflg3;	/* 3rd compatibility word		*/
   LONG	 sct_compflg4;	/* 4th compatibility word		*/
   ULONG sct_compflg5;	/* 5th compatibility word		*/
   LONG  sct_diagflg;	/* 1st diagnostics word			*/
   LONG  sct_diagflg2;	/* 2nd diagnostics word			*/
   LONG  sct_diagflg3;	/* 3rd diagnostics word			*/
   NINT	 sksgcurs;	/* key seg list controls		*/
   NINT	 sksgtots;
   pKSEGLST sksglsts;
#ifdef DBG749x
   UINT  sctlstfrq;
#endif
   UINT  sct_tmpseq;	/* temporary file sequence number	*/
   UINT	 sct_lhbins;
#ifdef ctDYNHASH
   UINT	 sct_lhbinx;
   UINT	 sct_lhLoadF;
   UINT	 sct_lhRehashF;
   UINT	 sct_lhMaxBins;
   UINT	 sct_ulMaxBins;
   UINT	 sct_ulNoShrink;
   UINT	 sct_lhNoShrink;
#ifdef TRANPROC
   UINT	 sct_shbinx;
   UINT	 sct_shLoadF;
   UINT	 sct_shRehashF;
   UINT	 sct_shMaxBins;
   UINT	 sct_shNoShrink;
#endif
#endif
#ifdef ctPortYMF
   UINT	 sct_spltNbrFls;
#endif
   UINT  sctconbins;	/* context bins				*/
   NINT	 sct_dq;	/* shrink task logical Q handle		*/
   NINT	 sct_cq; 	/* checkpoint task logical Q handle	*/
   UINT  snsplit;	/* node splits				*/
   NINT	 scthghflx;	/* highest allocated FCB under ctFLEXFILE */
   NINT	 sctfnz;	/* superfile member max name size	*/
   NINT  sctmiroff;	/* if YES, turn off all mirroring	*/
   NINT  sctosIOlok;	/* if YES, need OS lock to force cache	*/
   COUNT sctconid;	/* last assigned context id		*/
   pTEXT sct_tmppth;	/* temporary file default path		*/
#ifdef ctFeatTMPPTH_FREE
   NINT  sct_tmppth_allocd; /* temporary file path is allocated	*/
#endif
#if defined(TRANPROC) || defined(ctFeatOTREE) || defined(otOTREE)
#ifndef TRANPROC
#define pSHADLST void *
#define ppSHADLST void **
#define pCOALST void *
#endif
   pREBLST   sctrebhed;
   pREBLST   sctcmphed;
   pREBLST   sctmirhed;
   pREBLST   sctiblhed;
   ppSHADLST sct_ubit;
#ifdef DBGhash
   pLONG     sdbg_shsh_u;
#endif
   pTEXT sct_usrsp;
   pSHADLST sct_usrsl;
   pCOALST   sct_coalst;
   pTEXT sctlgbf;	/* transaction log buffer ptr */
   ppTEXT    sctlogmemanc;
   ppSHADLST sctlstshd;	/* linked list tail for pre-image list */
   ppSHADLST sctlstsav;	/* last save point pointer */
   ppCOMLST  scttrnanc; /* vulnerable tran hash list anchor */
#ifdef ctFeatADDKY_DEFERD
   ppSHADLST sskpaddhed; /* linked list head for 1st skipped/deferred add */
   ppSHADLST sskpaddend; /* linked list tail				  */
   pVOID     sskpkeyctx; /* key context ptr for skipped/deferred add      */
#endif
   pCTFILE sctLnum;
   pCTFILE sctUnum;
   pCTFILE sctSnum;
   CTFILE sctLfil;	/* log file header */
   CTFILE sctUfil;	/* log file header */
   CTFILE sctSfil[2];	/* start file headers */
   LONG  strnwrn;	/* transaction # overflow warning flag	*/
   LONG  sfilwrn;	/* file ID overflow warning flag	*/
   LONG	 sprv_logser;	/* previous checkpoint log#	*/
   ULONG sprv_chkpos;	/* previous checkpoint pos	*/
   ULONG sprv_prvpos;	/* previous checkpoint back link*/
   ULONG sctlogchklmt;
   LONG  sctshdmem;	/* shadow memory: excluding control structures */
   LONG  sctusrsum;
   LONG  sctusrtot;
   LONG	 sctdmptim;	/* dynamic dump begin time */
   LONG	 sctdlgnum;	/* beginning log during dump */
   LONG	 sctelgnum;	/* ending log during dump */
   ULONG sctdlgpos;	/* position in ctdlgnum */
   ULONG sctelgpos;	/* position in ctelgnum */
   LONG	 sctcpcnt;	/* check point count */
   LONG	 sctcpchk;	/* check point count less delta */
   LONG  sctelcnt;	/* check point count at last ENDLOG */
   LONG	 sct_lstlog;	/* last checkpoint log# */
   ULONG sct_lstpos;	/* last checkpoint log position */
   LONG	 sct_strlog;	/* checkpoint log# at startup */
   LONG	 sct_strpos;	/* checkpoint log position at startup */
   LONG	 sct_rcvlog;	/* oldest log required for recovery  */
   LONG	 sctfwdlog;	/* log for starting TRANFWD (ctrdmp) */
   ULONG sctfwdpos;	/* position for starting TRANFWD (ctrdmp) */
   ULONG sctfwdpps;	/* prev pos for starting TRANFWD (ctrdmp) */
   ULONG sct_usrsq[MXU2];/* user transaction sequence number	  */
   LONG	 sct_usrtr[MXU2];/* active transaction # for user or zero */
#ifdef ctFeat6BT
   LONG	 sct_usrtr2[MXU2];
   LONG  sct_usrix2[MXU2];
#endif
#ifdef ctFeatDFRIDX
  LONG   sct_usrdkln[MXU2];/* log number of first deferred key entry for tran */
  LONG   sct_usrdklp[MXU2];/* log offset of first deferred key entry for tran */
  LONG   sct_usrdkln2[MXU2];/* log number of last deferred key entry for tran */
  LONG   sct_usrdklp2[MXU2];/* log offset of last deferred key entry for tran */
#if defined(ctFeatRUCB) && defined(TRANPROC)
  pSHADLST srucbh[MXU2]; /* first record update callback DFRKEY entry */
  pSHADLST srucbt[MXU2]; /* last record update callback DFRKEY entry */
#endif
#endif
#ifdef ctXTDLOGgrp
   LONG	 sct_usrgr[MXU2];/* current group # for user or zero */
   LONG	 sct_usrgp[MXU2];/* store group # for user	     */
#endif
   LONG	 sct_usrtl[MXU2];/* log file sequence number for BEGTRAN */
   LONG  sct_usrix[MXU2];/* log file index op number */
   LONG  sct_trnhghmrk;	/* threshold to warn about tran high-water mark */
#ifdef ctSUCTRAN
   LONG	 sct_usrbl[MXU2];/* log file sequence number for BEGTRAN */
   LONG	 sct_usrbp[MXU2];/* log file position for BEGTRAN */
   LONG	 sct_usrel[MXU2];/* log file sequence number for ENDTRAN */
   LONG	 sct_usrep[MXU2];/* log file position for ENDTRAN */
   LONG  sct_usrtv[MXU2];/* save tran# for SUCTRAN pending list */
   LONG  sct_usrtv2[MXU2];
#endif
#ifdef ctXTDLOG
   VRLEN sct_mxusrlog;	/* maximum size of user log entry (var len portion */
#endif
   ULONG sct_lbfsiz;	/* log buffer size */
   VRLEN sct_usrsz;
   NINT	 sct_usrmd[MXU2];/* transaction TRANBEG mode */
   UINT	 sct_shbins;
   UINT	 sct_shbyts;
   NINT	 sct_tryprvchk;	/* try previous checkpoint */
   NINT  sctsuplog;	/* suppress log flush and sync on begin and end tran */
   NINT  sctsuplogsync;	/* suppress log sync on begin and end tran */
   NINT  sctfstr;
   NINT	 sctfwdned;
   NINT	 sct_chktrd;
   NINT	 sct_chkflg;	/* checkpoint in progress flag */
   NINT	 sct_logkep;	/* archive log count */
   NINT  sctskpfil;	/* skip missing files during recovery */
   NINT  sctskpato;	/* skip missing files automatic for trandep */
#ifdef ctFeatRCV_DETECT_INACCESSIBLE_FILES
   NINT  sctskpiaf;	/* skip inaccessible files during recovery */
#endif
   NINT	 sctskpmir;	/* skip missing mirrors during recovery */
   NINT  sctbadmir;	/* skip missing or bad log mirrors during startup */
   LONG  sctfixlog;	/* non-zero means log size cannot increase */
#ifdef ctFeatDYNAMIC_DUMP
   NINT  sctpdmp;	/* preimage dynamic dump flag */
#endif
   NINT  sctsflg;	/* ct_strip flag */
   NINT  sctbflg;	/* BAKMOD flag */
   NINT  sctdflg;	/* dynamic dump flag */
   NINT  sct_actrns;	/* # active transactions */
   NINT  sct_usrsi;
   LONG  sct_usrsv;
   NINT  sct_rstflg;	/* TRANRST() flag */
   NINT	 sctlogmem;
   NINT	 sctlogmemmax;
   NINT	 sctlogdet;
   NINT	 sctskpclnfil;
   NINT  sct_coalcr;
   NINT	 sct_coaltt;
   NINT	 sct_coalcs;
   LONG  sct_usrty[MXU2];/* ctSHADOW / ctLOGFIL transaction type */
   SYSNO sctshdlfil;	/* shadow swap file # */
   SYSNO sct_lgn;	/* current file# in log */
   COUNT sct_lerflg;	/* ctwrtlog error flag */
   TEXT	 sct_chkpt[MXU2];/* check point flag */
#ifndef TRANPROC
#undef pSHADLST
#undef ppSHADLST
#undef pCOALST
#endif
#endif /* TRANPROC || ctFeatOTREE || otOTREE */
#ifdef ctNogloSize
   pVOID   sctrebhed;
   pVOID   sctcmphed;
   pVOID   sctmirhed;
   pVOID   sctiblhed;
   ppVOID sct_ubit;
#ifdef DBGhash
   pLONG  sdbg_shsh_u;
#endif
   pVOID sct_usrsp;
   pVOID sct_usrsl;
   pVOID sct_coalst;
   pVOID sctlgbf;	/* transaction log buffer ptr */
   ppVOID    sctlogmemanc;
   ppVOID sctlstshd;	/* linked list tail for pre-image list */
   ppVOID sctlstsav;	/* last save point pointer */
   ppVOID  scttrnanc; /* vulnerable tran hash list anchor */
#ifdef ctFeatADDKY_DEFERD
   ppVOID sskpaddhed; /* linked list head for 1st skipped/deferred add */
   ppVOID sskpaddend; /* linked list tail			       */
   pVOID  sskpkeyctx; /* key context ptr for skipped/deferred add      */
#endif
   pVOID sctLnum;
   pVOID sctUnum;
   pVOID sctSnum;
   CTFILE sctLfil;	/* log file header */
   CTFILE sctUfil;	/* log file header */
   CTFILE sctSfil[2];	/* start file headers */
   LONG  strnwrn;	/* transaction # overflow warning flag	*/
   LONG  sfilwrn;	/* file ID overflow warning flag	*/
   LONG	 sprv_logser;	/* previous checkpoint log#	*/
   ULONG sprv_chkpos;	/* previous checkpoint pos	*/
   ULONG sprv_prvpos;	/* previous checkpoint back link*/
   ULONG sctlogchklmt;
   LONG  sctshdmem;	/* shadow memory: excluding control structures */
   LONG  sctusrsum;
   LONG  sctusrtot;
   LONG	 sctdmptim;	/* dynamic dump beginn time */
   LONG	 sctdlgnum;	/* beginning log during dump */
   LONG	 sctelgnum;	/* ending log during dump */
   LONG	 sctdlgpos;	/* position in ctdlgnum */
   LONG	 sctelgpos;	/* position in ctelgnum */
   LONG	 sctcpcnt;	/* check point count */
   LONG	 sctcpchk;	/* check point count less delta */
   LONG  sctelcnt;	/* check point count at last ENDLOG */
   LONG	 sct_lstlog;	/* last checkpoint log# */
   ULONG sct_lstpos;	/* last checkpoint log position */
   LONG	 sct_strlog;	/* checkpoint log# at startup */
   ULONG sct_strpos;	/* checkpoint log position at startup */
   LONG	 sct_rcvlog;	/* oldest log required for recovery  */
   LONG	 sctfwdlog;	/* log for starting TRANFWD (ctrdmp) */
   ULONG sctfwdpos;	/* position for starting TRANFWD (ctrdmp) */
   ULONG sctfwdpps;	/* prev pos for starting TRANFWD (ctrdmp) */
   ULONG sct_usrsq[MXU2];/* user transaction sequence number	  */
   LONG	 sct_usrtr[MXU2];/* active transaction # for user or zero */
#ifdef ctFeat6BT
   LONG	 sct_usrtr2[MXU2];
   LONG  sct_usrix2[MXU2];
#endif
#ifdef ctFeatDFRIDX
  LONG   sct_usrdkln[MXU2];/* log number of first deferred key entry for tran */
  LONG   sct_usrdklp[MXU2];/* log offset of first deferred key entry for tran */
  LONG   sct_usrdkln2[MXU2];/* log number of last deferred key entry for tran */
  LONG   sct_usrdklp2[MXU2];/* log offset of last deferred key entry for tran */
#endif
#ifdef ctXTDLOGgrp
   LONG	 sct_usrgr[MXU2];/* current group # for user or zero */
   LONG	 sct_usrgp[MXU2];/* store group # for user	     */
#endif
   LONG	 sct_usrtl[MXU2];/* log file sequence number for BEGTRAN */
   LONG  sct_usrix[MXU2];/* log file index op number */
   LONG  sct_trnhghmrk;	/* threshold to warn about tran high-water mark */
#ifdef ctSUCTRAN
   LONG	 sct_usrbl[MXU2];/* log file sequence number for BEGTRAN */
   LONG	 sct_usrbp[MXU2];/* log file position for BEGTRAN */
   LONG	 sct_usrel[MXU2];/* log file sequence number for ENDTRAN */
   LONG	 sct_usrep[MXU2];/* log file position for ENDTRAN */
   LONG  sct_usrtv[MXU2];/* save tran# for SUCTRAN pending list */
   LONG  sct_usrtv2[MXU2];
#endif
#ifdef ctXTDLOG
   VRLEN sct_mxusrlog;	/* maximum size of user log entry (var len portion */
#endif
   ULONG sct_lbfsiz;	/* log buffer size */
   VRLEN sct_usrsz;
   UINT	 sct_shbins;
   UINT	 sct_shbyts;
   NINT	 sct_tryprvchk;	/* try previous checkpoint */
   NINT  sctsuplog;	/* suppress log flush on begin and end tran */
   NINT  sctsuplogsync;	/* suppress log sync on begin and end tran */
   NINT  sctfstr;
   NINT	 sctfwdned;
   NINT	 sct_chktrd;
   NINT	 sct_chkflg;	/* checkpoint in progress flag */
   NINT	 sct_logkep;	/* archive log count */
   NINT  sctskpfil;	/* skip missing files during recovery */
   NINT  sctskpato;	/* skip missing files automatic for trandep */
#ifdef ctFeatRCV_DETECT_INACCESSIBLE_FILES
   NINT  sctskpiaf;	/* skip inaccessible files during recovery */
#endif
   NINT	 sctskpmir;	/* skip missing mirrors during recovery */
   NINT  sctbadmir;	/* skip missing or bad log mirrors during startup */
   LONG  sctfixlog;	/* non-zero means log size cannot increase */
#ifdef ctFeatDYNAMIC_DUMP
   NINT  sctpdmp;	/* preimage dynamic dump flag */
#endif
   NINT  sctsflg;	/* ct_strip flag */
   NINT  sctbflg;	/* BAKMOD flag */
   NINT  sctdflg;	/* dynamic dump flag */
   NINT  sct_actrns;	/* # active transactions */
   NINT  sct_usrsi;
   LONG  sct_usrsv;
   NINT  sct_rstflg;	/* TRANRST() flag */
   NINT	 sctlogmem;
   NINT	 sctlogmemmax;
   NINT	 sctlogdet;
   NINT	 sctskpclnfil;
   NINT  sct_coalcr;
   NINT	 sct_coaltt;
   NINT	 sct_coalcs;
   LONG  sct_usrty[MXU2];/* ctSHADOW / ctLOGFIL transaction type */
   SYSNO sctshdlfil;	/* shadow swap file # */
   SYSNO sct_lgn;	/* current file# in log */
   COUNT sct_lerflg;	/* ctwrtlog error flag */
   TEXT	 sct_chkpt[MXU2];/* check point flag */
#endif /* ctNogloSize */
   ULONG sct_lstchktim;	/* last checkpoint time stamp		*/
   VRLEN sct_bfsiz;	/* data buffer size			*/
   NINT  sctlogidxfrc;	/* ctLOGIDX override: YES-on HYS-off	*/
   ULONG sctrdmp_opt;	/* dynamic dump option bits		*/
   NINT	 sctrdmp_memlog; /* dynamic dump RECOVER_MEMLOG setting	*/
   NINT	 sctrdmp_flg;	/* signals dynamic dump recovery	*/
   NINT	 sctmdmp_flg;	/* signals dyn dump recovery had mirrors*/
   NINT	 sctfdmp_flg;	/* signals forward roll	operation	*/
   NINT	 sctxflg[5];	/* test tran work space flag		*/
   RNDFILE
	 sctxflgfd[5];	/* test tran work space file descriptor	*/
   pLONG sctridx_ptr;	/* dynamic dump index update list ptr	*/
   NINT  sctridx_cur;	/* dynamic dump index update current	*/
   NINT  sctridx_tot;	/* dynamic dump index update total	*/
   NINT	 sclnidxx_flag;	/* on the fly CLNIDXX flag		*/
   NINT	 sctrflg;	/* automatic recovery flag		*/
#ifdef ctFeatRECOVERY_CHECK_DUPFID
/* processing transaction-dependent operation during recovery	*/
   NINT	 srecovery_TRANDEP_operation;
#endif
   NINT  sdrtyflg;	/* dirty shutdown detected		*/
#ifdef ctFeatLOGFLUSH_MOD
   NINT  sctminlogsync; /* YES / NO: DELAYED_DURABILITY enabled	*/
#endif
#ifdef ctFeatRP
   NINT  sctkep_rp_rcv;	/* YES / NO: RECOVER_TO_RESTORE_POINT	*/
   NINT  sctkep_rp_cfg;	/* RECOVER_TO_RESTORE_POINT entry in	**
			** ctsrvr.cfg				*/
   NINT  sctkep_rp_num;	/* number of restore points to keep	*/
   NINT  sctkep_rp_act;	/* number of restore points active	*/
   NINT  sctkep_rp_fnd;	/* restore point found during rollback	*/
   NINT  sctkep_rp_req;	/* DELAYED_DURABILITY on at system crash*/
   ULONG sctkep_rp_tim;	/* time of last restore point		*/
   LONG8 sctkep_rp_srn;	/* restore point serial number		*/
#endif
   LONG  sct_endser;	/* last log during auto recovery	*/
#ifdef ctBEHAV_EOR_CLSTRAN
   NINT  sct_clstrn;	/* any CLSTRAN written at end of recvry	*/
#endif
   NINT  sctnewlogs;	/* starting without logs		*/
   NINT	 sctstrcv_flg;	/* init automatic recovery		*/
   NINT	 sctrbflg;	/* rebuild flag				*/
   NINT	 sctfnstrat;	/* file name conversion strategy	*/
   NINT	 sctmnstrat;	/*    mirror conversion strategy	*/
   NINT	 scttflg;	/* stop server in progress		*/
   NINT	 scttflg_L;	/* stop server in progress (logsema ctl)*/
   NINT	 sctrint_L;	/* recovery interrupted flg(logsema ctl)*/
   NINT  sctfilcre;	/* flag for create since checkpoint	*/
   COUNT sct_mxu1;	/* max users plus origin		*/
   NINT	 sct_cmnown;	/* common onwer number (semaphores)	*/
   UINT	 sct_hshft;	/* hash shift parameter			*/
   UINT	 sct_hbins;	/* hash bins for buffers		*/
   UINT	 sct_dshft;	/* datbuf hash shift parm		*/
   UINT	 sct_dbins;	/* datbuf hash bins			*/
#ifdef ctNogloTran
   UINT	 sct_tbins;	/* vulnerable tran# hash bins		*/
#endif
#ifdef ctFeatAVLISTnum
   BHL	 sct_ibavl[ctMAXAVLIST]; /* index buffer avl list anchors */
#endif
#ifdef ctFeatDALISTnum
   BHL	 sct_dbavl[ctMAXDALIST]; /* data buffer avl list anchors */
#endif
#if !defined(ctFeatAVLISTnum) || !defined(ctFeatDALISTnum)
   BHL	 sct_bavl[2];	/* buffer avl list anchors		*/
#endif
   ppBHL sct_bhla[NUMANCHOR];/* buffer hash list anchors	*/
#ifdef DBGhash
   pLONG sdbg_bhl_n;
   pLONG sdbg_bhl_d;
#endif
   pTEXT sctsdname;	/* server directory name		*/
   pTEXT sctsmname;	/* mirror directory name		*/
   pTEXT sctsvname;	/* server name				*/
   pTEXT sctsqname;	/* server SQL name			*/
#ifdef ctPortVINESLOG
   TEXT	 sctlgname[MAX_NAME];	/* server status log name	*/
#endif

   pTEXT sctscommp[MAXCOMMP];	/* server comm protocol		*/

#ifdef ctFeatJOBMGTSYS 		/* FairCom Job Management System Subsystem */
   pTEXT sctsjobsf[MAXCTJOBS];	/* server ctjobs files		*/
#endif   

   pTEXT sct_del;	/* constant 0xff array			*/
   UINT	 sct_delsiz;	/* size of 0xff array			*/
   UINT	 scts_list_m;	/* list memory block size		*/
   UINT	 scts_sort_m;	/* sort memory buffer size		*/
   UINT	 scts_bufr_m;	/* bufr memory block size		*/

   UINT  sct_mxbuf;		/* available buffers specified in intree*/
   UINT  sctbufcnt;		/* buffers in use			*/
   UINT  sctbufhgh;		/* max buffers in use			*/
   UINT  sct_dxbuf;		/* available data file cache pages	*/
   UINT  sctdatcnt;		/* cache pages in use			*/
   UINT  sctdathgh;		/* max cache pages in use		*/
#ifdef ctHUGEFILEsegm
   NINT	 sctmtcsegflg;		/* matching segment action		*/
   NINT	 sctnonsegflg;		/* nonmatching segment action		*/
#endif
#ifdef ctFeatSPLCACHE
   UINT  sct_dxspllmt;		/* avail   data file special cache pages*/
   UINT  sct_dxsplcnt;		/* actual  data file special cache pages*/
   UINT  sct_dxsplhgh;		/* maximum data file special cache pages*/
#endif
   NINT	 sctmpagcache;		/* specify multiple page cache count	*/
#ifdef ctFeatVIRTUAL_FILES
   NINT  sct_maxvfil;		/* virtual file limit */
   NINT  sct_numvfil;		/* number of virtual files open		*/
#endif
   NINT  sct_avlfil;		/* available file control block counter */
   COUNT sct_ndsec;		/* # of sectors per node specified in intree */
   UCOUNT sct_ver1;		/* defines configuration options 128 header */
   UCOUNT sct_ver2;		/* defines configuration options XTD header */
   UCOUNT sct_ver3;		/* defines configuration options 6BT header */
   TEXT  sctsupsep;

#ifdef ctOldALCBAT
   COUNT   sbatmax;
   COUNT   sbatnum;
   pBATHDR ssavbat;
#else
   pSAVBAT sbatnum;
   ppSAVBAT
	   ssavbat;
#endif
   BATHDR  batch;
   HSTHDR  history;
   pHSTLST histund;
   pSAVHST shstnum;
   ppSAVHST
	   ssavhst;
   NINT  sprvlokf;		/* previous lock state: datno		*/
   NINT  sprvlokt;		/* previous lock state: lock type	*/	
   NINT  sprvlokt2;		/* previous lock state: lock type	*/	
   LONG  sprvlokp;		/* previous lock state: recbyt (lw)	*/	
#ifdef ctHUGEFILE
   LONG  sprvlokh;		/* previous lock state: recbyt (hw)	*/	
#endif
   IDXSTATE idxstate;  /* users default index state. Access with acquireIdxOpState() */
   LONG  sct_gsrl2;		/* next serial number for data file */
   LONG  sct_gsrl1;		/* next serial number for data file */
#ifdef ctFeatDAR
   LONG	 sIDfield_lstoff;	/* last IDfield field offset	    */
   LONG8 sct_IDfield;		/* next IDfield number for data file. note:
				** ct_IDfield set before update while ct_gsrl
				** set after update
				*/
#endif
   NLONG sct_usernm;		/* system dependent user number */
   NINT  sct_trdflg;		/* thread operation flag */
   TEXT  sct_buf[CTBUFSIZ];	/* temporary io buffer */

/*
** ISAM global variables from ctisam.h
*/

#ifdef ISAM_VARS
   pFILNO	*sctskyorg;
   pFILNO	*sctskymap;
   pCTIS1	sctis1;
   ppCTIS2	sctis2;

   TEXT		sct_fndval[MAXLEN];

   COUNT	sct_nwrcfg;
   FILNO	sct_vfsg;

   COUNT	sct_ismlk;
   COUNT	sct_fndlen;	/* bytes in ct_fndval to save	*/
#ifdef ctFeatRECRLOCK
   NINT		sct_ismrc;
#endif

#ifdef ctOldALCSET
   pSAVSET  sct_savset;

   COUNT   sseqlen;		/* significant length of key	*/
   COUNT   sseqkey;		/* current keyno		*/
   COUNT   sseqnum;		/* current set number		*/
   COUNT   smaxqset;
#else
   ppSAVSET
	   sct_savset;		/* pointer to hash anchors	*/
   pSAVSET sseqnum;		/* current set pointer		*/
   COUNT   sseqlen;		/* significant length of key	*/
   FILNO   sseqkey;		/* current keyno		*/
#endif
   TEXT    sseqbuf[MAXLEN];	/* holds matching "partial" key */
   TEXT	   sseqold[MAXLEN];
#endif

#ifdef ctFeatLOADKEYopt
   TEXT sl_apnod[MAXLEV];	/* node has been initialized by addtoparent */
   TEXT sl_maxukp;		/* maximum % full requested in leaf node    */
   UINT sl_maxukb;		/* maximum key bytes requested in leaf node */
#endif
   TEXT sl_lastkey[MAXLEN];
   LONG sl_begnod1;
   LONG sl_curnod1;
   LONG sl_prvnod1;
   LONG sl_begnod2;
   LONG sl_curnod2;
   LONG sl_prvnod2;
   LONG sl_savbp_node2;
   LONG sl_numnod2;
   LONG sl_ct_nnods2[MAXLEV];
   LONG sl_numnod1;
   LONG sl_ct_nnods1[MAXLEV];
   NINT sl_elem;
   NINT sl_started;
   pTREBUF sl_savbp;
   pCTFILE sl_savbp_knum;
   LONG  sl_savbp_node1;
   VRLEN sl_hdradj;

   COUNT stranactv;
   COUNT stransavp;
   UINT  slstsiz[NUMCTLIST];
#ifdef DBG749x
   UINT  slstchk[NUMCTLIST];
#endif
   VRLEN slstcnt[NUMCTLIST];
#endif /* CTBOUNDvar || ctFeatOTREE || otOTREE */
   NINT  sctbpfx_level;
#if defined(UNBOUNDvar) || defined(ctFeatOTREE) || defined(otOTREE) 
   pTEXT	sctusrbuf;
#ifdef ctCLIENT
   pLQMSG	sctlqmsg;
   pLOCLFILE	shlocl;
   pLOCLAUX	shauxl;
   NINT		scthugflg;
   NINT		sctreqsiz;
   NINT		sctrspsiz;
   NINT		sctinpoff;
   NINT		sctoutoff;
#else
   pVOID	ctlqfake;
   pVOID	hloclfake;
   pVOID	hauxlfake;
   NINT		hugflgfake;
   NINT		reqsizfake;
   NINT		rspsizfake;
   NINT		inpofffake;
   NINT		outofffake;
#endif
   VRLEN	sctusrlen;
   VRLEN	sctusrpos;
   VRLEN	sctsrvlen;
   UTEXT	sctsflvr[8];
   TEXT		sctnodnam[IDZ];
   NINT		sct_lq;		/* logon logical Q handle		*/
   NINT		sctautotfrm;
   NINT		sctmaxdatkey;
   NINT		sctisam_flg;
   NINT		sct_autopos_clr;
   NINT		sctsrvopt;
   NINT		sctspclogon;
   COUNT	sctsrvver;
   ULONG	sctsrbytatr;	/* Server attributes			*/
#endif /* UNBOUNDvar || ctFeatOTREE || otOTREE */
#ifdef ctBEHAV_XTDHDR
   NINT		scth6flg;	/* restore V6 header for non-X8 creates	*/
#endif
   UINT		salign_override;

   NINT		(*intcalbak)(pCTINIT1 );

#ifdef CTBOUNDvar
   pTEXT	sct_rbuf;
#ifdef ctNogloTran
   pLOGTRNLST	slogtrn_lst;
#ifdef ctFeatRP
   pRPLIST	srplist_ptr;
#else
   pRPLIST	srplist_ptrx;
#endif
#ifdef TRANPROC
   pTRNSTORE	sredolist_ptr;
#else
   pVOID	sredolist_ptr;
#endif
   ppTEXT	sskplst_anc;
   pTEXT	sctlpathf[10];
   pTEXT	sctlpathm[10];
   pTEXT	slogptr;
   pLONG	sct_rcvlst; /* dynamic dump recovery filename list */
#ifdef ctFeatRCVLSTopt
   pRCVLSTHSH	sct_rcvhshOrig; /* dynamic dump recovery hash table for original filename */
#ifdef ctFeatRECOV_PATHEQUIV
   pRCVLSTHSH	sct_rcvhshFull; /* dynamic dump recovery hash table for full filename */
#endif
   UINT		sct_rcvhshBins; /* number of hash bins for dynamic dump recovery filename hash table */
#endif
#ifdef ctFeatRCVOPNopt
   pRCVOPNLSTHSH sct_rcvopnhshOrig; /* auto recovery hash table for original filename */
#ifdef ctFeatRECOV_PATHEQUIV
   pRCVOPNLSTHSH sct_rcvopnhshFull; /* auto recovery hash table for full filename */
#endif
   UINT		sct_rcvopnhshBins; /* number of hash bins for auto recovery filename hash table */
#endif
   pLONG	sct_hdrlst;
   pLONG	sct_mbrlst;
   pLONG	sct_clnlst;
   LONG		sct_trndlt;
   LONG		sct_cpdlt;
   ULONG	sct_logchn;
   ULONG	sct_logpts;
   ULONG	sct_loglmt;
   ULONG	sct_logspc;
   LONG		sct_logrec;
   ULONG	sct_logtrg;
   ULONG	sct_blgpos;
   LONG		sct_logprg;
   LONG		sct_savprg;
#ifdef ctBEHAV_DLYLOGPRG
   LONG		sct_begprg;
   LONG		sct_numprg;
   LONG		sct_newprg;
   LONG		sct_lstsav;
#endif
   LONG		slogtrn_seq;
#ifdef ctFeat6BT
   LONG		sct_lowtrn2;
#endif
   ULONG	sct_lowtrn;
   LONG		sct_lnmlog;
   LONG		sct_hnmlog;
   LONG		sct_oldlog;
   LONG		sct_replog;
   ULONG	scttopcmt;
   LONG		scttoplog;
   LONG		sctbegcmt;
   LONG		sctbeglog;
   ULONG	slogbyt;
   ULONG	slowpnt;
   ULONG	slstpnt;
   ULONG	slstsuc;
   ULONG	shghcmt;
   LONG		shghlog;
#ifdef ctFeatLOGREAD
   NINT		sctlogred;
   NINT		sctreplopts;
#endif
   ULONG	slogrem;
   VRLEN	slbfpag;
   NINT		slogtrn_tot;
   NINT		slogtrn_cur;
#ifdef ctFeatRP
   NINT		srplist_tot;
   NINT		srplist_cur;
#endif
   NINT		sredolist_tot;
   NINT		sredolist_cur;
   NINT		sskplst_tot;
   NINT		sskplst_cur;
   NINT		sct_logspr;
   NINT		sanydelmrk;
   NINT		sintpthflg;
   NINT		sctlpathfa[10];
   NINT		sctlpathma[4];
   NINT		snumhgh[NUMHGHBINS];
   COUNT	sreserved;
   COUNT	sct_logblk;
   TEXT		sundflg[(MXU2 + 3) & ~3]; /* ensure a multiple of 4 */
#ifdef ctFeatLOWBEGLOG
   LONG		slowbeglog; /* lowest log with begin of active trans */
#endif
#ifdef  ctBEHAV_DLYLOGPRG2
   LONG		slowbeglog_cp; /* low log w/begin of tran in last checkpoint */
#endif
#endif /* ctNogloTran */
#ifndef MULTITRD
   NINT		sctstatlogflg;		  /* Status log path set if non-zero */
   TEXT		sctstatlogpath[MAX_NAME]; /* Status log path */
#endif
   VRLEN	sct_bsz;
   NINT		sctcatcnt;
   COUNT	srerr_cod;
   FILNO	srerr_fil;
   COUNT	sct_fp;
#ifdef RB_CALLBACK
#ifdef ctFeatREBUILD_CALLBACK_STATE
   LONG8	srblcbcnt; /* progress counter for rebuild callback func */
#else
   ULONG	srblcbcnt; /* progress counter for rebuild callback func */
#endif
   UCOUNT	srblcbstp; /* progress step for rebuild callback func */
#endif
   NINT		sctfilcremode;		/* File create mode (e.g., 0666) */
   NINT		sctmaxsqlisolvl;	/* Maximum SQL isolation level (MAX_SQL_ISOLATION_LEVEL keyword) */
#endif /* CTBOUNDvar */

#ifdef ctCAMO
   pCAMFNC	sucamfnc;
   pTEXT	sucamptr;
   pTEXT	sct_cam;
   VRLEN	sct_camsiz;
   LONG		sucamlen;
#endif
#ifdef ctFeatTRANSFER_FILE
#if defined(ctCLIENT) || defined(ctLOCLIB)
   pFILE	sctfilexfrfp;	/* file pointer for ctTransferFile operation */
#endif
#endif
#if defined(ctCLIENT) || defined(ctLOCLIB)
   NINT		sctrecur;	/* ctree() recursion counter	*/
   NINT		sandaborted;	/* an (external) abort occurred	*/
   pAPICB	sapicallback;	/* ctree() API callback function */
#ifdef ctFeatNONBLK_SOCKIO
   NINT		sctsocktimeout; /* max time in seconds to wait for socket I/O before erroring out */
#ifdef ctFeatSOCKET_WAIT_INTERVAL
   NINT		sctSocketWaitInterval; /* time in seconds to wait for socket I/O before retrying */
#endif
#endif
#ifdef ctFeatUNIX_SHMEM
   pTEXT	sctshmemdir;	/* Directory for shared memory files */
   NINT		sctshmemprm;	/* Permission for shared memory resources */
#ifdef ctFeatSHMEMgrp
   pTEXT	sctshmemgrp;	/* Group for shared memory resources */
#endif
#endif
#ifdef ctFeatPWDSEC
   UTEXT	scturn[PWDSECRNDLEN];
   UTEXT	sctuhp[PWDSECHSHLEN];
#endif
#endif
#ifdef ctFeatNOBUFFERING_LOGFILE
   NINT		sctnobuflogs;	/* Use unbuffered I/O for transaction logs */
#endif
#ifdef ctFeatNOBUFFERING
   NINT		sctunbufio;	/* Using unbuffered I/O option	*/
#endif
#ifdef ctFeatENCSTORE
   pTEXT	sctmstkeyfil;	/* Encrypted master key file	*/
#endif
#ifdef ctFeatREBUILD_OPT
   ULONG	sctmaxktouse;	/* MAX_K_TO_USE for rebuild	*/
   NINT		sctmaxhandles;	/* MAX_HANDLES for rebuild	*/
#endif
#ifdef ctFeatRWLOCKwindows
   /* Reader/writer lock function pointers: */
   pRWLFNC	sInitRWLock;	/* Initialize reader/writer lock*/
   pRWLFNC	sAcqRWLockExc;	/* Acquire exclusive lock	*/
   pRWLFNC	sAcqRWLockShr;	/* Acquire shared lock		*/
   pRWLFNCret	sTryRWLockExc;	/*     Try exclusive lock	*/
   pRWLFNCret	sTryRWLockShr;	/*     Try shared lock		*/
   pRWLFNC	sRelRWLockExc;	/* Release exclusive lock	*/
   pRWLFNC	sRelRWLockShr;	/* Release shared lock		*/
   pRWLFNC	sDestroyRWLock;	/* Destroy reader/writer lock	*/
#endif
#ifdef ctFeatAUTO_SHMEM
   CmFuncPtrs	sctcommfns;	/* communication protocol function pointers */
#endif
   ULONG	sct_allsup;	/* bit mask for FREL_ERR test. replaces  **
				** DEF_MASK_ALLSUP			 */
#ifdef TRANPROC
   ULONG	sct_logsup;	/* bit mask for LFRM_ERR test. replaces  **
				** DEF_MASK_LOGSUP			 */
#ifdef ctLOGAUG
   ULONG	sct_logaug;	/* bit mask for LAUG_ERR test		 */
#endif
#ifdef ctRECBYTIDX
   NINT  	sctcoaltran;	/* coalesce of non-recbyt ctTRNLOG files  */
#endif
#endif
#ifdef ctUNICODE
#ifndef ctBEHAV_CHECK_ICU_COLLATOR_VERSION
   LONG		skseg_icuv;	/* current ICU runtime collation version */
#endif
   LONG		skseg_icuE;	/* last ICU file version in error	 */
   TEXT		skseg_icuD[ctKSEGDLEN];
				/* last ICU file locale in error	 */
#endif
#ifdef ctFeatUDF_EXPR
    pVOID	udflist;
    NINT	isexpreval;
#endif
#ifdef ctFeatSEQNUM
#ifndef MULTITRD
    FILNO	ssequfl;	/* sequence file user file number */
    COUNT	sseqcnt;	/* number of open sequences	  */
#endif
#endif
#ifdef ctBEHAV_CMPREC_optimize
    LONG	schkcmprec;	/* check if record is compressed  */
    VRLEN	sskpimglen;	/* skip leading bytes of record image */
    pTEXT	scmprecbuf;	/* compressed record image buffer */
    VRLEN	scmprecsiz;	/* size of compressed record buffer */ 
#endif
#ifdef ctPARTITION
    pCTFILE	srblhnum;	/* partition rebuild host dnum	  */
    NINT	srblrawno;	/* partition rebuild member rawno */
    NINT	sprmidxcnt;	/* number of partition members	  **
				** calling reprmidx in recovery	  */
#endif
#ifdef ctFeatXTDOPNMOD
    LONG	sxtdopnmod;	/* extended file open mode	  */
#endif
#ifdef ctFeatSUPHSTcofile
    FILNO	scursuphstno;	/* current superfile host file number */
#endif
#ifdef ctNOGLOBALS
#ifdef ctFeatMEMFILE
    LONG	sctMEMFILEmaxbins; /* max hash bins for memory file */
#endif
#endif
#ifdef ctSRVR
    pctUSRST    spusrstate;	/* saved connection state	  */
    LONG8	strnovrflwthr;	/* transaction number overflow threshold */
#ifdef ctFeatLOGONSEC
    LONG	sctseclgn;	/* secure logon setting		  */
#endif
#endif
#ifdef ctCLIENT
#ifdef ctFeatREPLICAT
    pVOID	spvrepstt;	/* replication agent state pointer */
    ULONG	sreploptions;	/* replication agent options	   */
#endif
    ULONG	sconnoptions;	/* client connection options	   */
#ifdef ctFeatCLIENT_NOTIFY
    TEXT	sfailoverUniqueID[FAILOVER_UNIQUE_ID_LEN]; /* failover unique identifier read from broadcast read thread at connect time */
#endif
#endif

#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
    NINT	susr_cmprec_type;
    NINT	susr_cmprec_vrsn;
    UINT	susr_cmprec_plen;
    UINT	susr_cmprec_allc;
    pTEXT	susr_cmprec_parm;
    TEXT	susr_cmprec_dll[MAX_NAME];
#endif
#ifdef ctFeatOPENSSL
    CTSSLI	sctsslinf;	/* State information for SSL support	 */
    NINT	sctssl_avail;	/* Indicates SSL init status	*/
    TEXT	sctssl_errmsg[256]; /* SSL init error buffer	*/
#endif
#ifdef ctFeatPARTREPL
    pCTFILE	screpart_host[MXU2]; /* partition host FCB pointer used to set
				     ** phost during member create */
#endif
#ifdef rtSRVR
    pTEXT	rtuserlibname;	/* Name of RTUSER DLL/shared library to load */
#endif

    ctZLIB1	sctzlib1;
#if defined(ctCMPREC) && defined(ctFeatZLIBdynamic)
    NINT	sctzlib_avail;	/* Indicates zlib init status	*/
    TEXT	sctzlib_errmsg[256]; /* zlib init error buffer	*/
#endif
#ifdef ctFeatKBUFrefresh
    pTEXT	skbufrec;	/* Buffer to hold the record image that	**
				** we read to refresh ISAM key buffers.  */
    LONG	skbufrecsiz;	/* Size of the record image buffer.	 */
#endif
#ifdef ctFeatRUCB
#ifndef MULTITRD
    pVOID	srucbsess;	/* Record update callback function: user-
				** defined pointer for connection-level
				** state information			*/
#endif
#endif
#if defined(ctCLIENT) || defined(ctLOCLIB)
#ifdef ctFeatSSL
    pTEXT	ssslsrvcertfile;/* Name of file containing server certificate.*/
    pTEXT	sssldbglog;	/* SSL debug log file name.		      */
#endif
#ifdef ctFeatCLUSTER_OPTIONS
    CLIENT_CLUSTER_STATE clusterState; /* client side cluster state */
#endif
#endif
#ifdef ctFeatFULLTEXTIDX
	pVOID sctdbSessionHandle; /* ctdb attached session */
#endif
#ifdef ctFeatADDIDXMBR
    NINT	snaddmbr;	/* Number of index members being added. */
#endif
#ifdef ctFeatFPGloktimout
    LONG	sutimout;	/* all files user block timeout		*/
    NINT	sdtimout;	/* diagnostic indicator			*/
#endif
#ifdef ctFeatTRANIDX_LOPN_ERR_CONTINUE
    NINT        stranidx96cont;	/* continue in case of tranidx LOPN_ERR */
#endif
#ifdef ctFeatDELSTK_COMMIT_SEC
    NINT        sdelstkcmtsec;	/* max. delay of deferred delete stack commit */
#endif
#ifdef ctFeatFLEXREC
    pVOID	sprecmetadata;	/* record metadata pointer		*/
#endif
#ifdef ctFeatTEMPDIR
    FILNO	stmpdirdatno;	/* temp dir file user file number */
#endif
#ifdef ctFeatINTERMEDIATE_BLOCK_PAGING
    NINT	sintblkpgs;	/* use data cache pages for intermediate
				block I/O operations to ensure consistency */
#endif
#ifdef ctBEHAV_AUTOTRAN_ON_CREATE
    NINT	satotrncre;	/* automatic transaction on ISAM file create */
#endif
#ifdef ctBEHAV_NONTRAN_FILESYS_FLUSH_OFF
    NINT	sctnontranfsflushoff; /* no file system flush for non-TRNLOG files */
#endif
#ifdef ctFeatKSEGDEFxtd
#ifdef ctCLIENT
    pTEXT	spuksegdef;	/* extended key segment definition in internal format */
    NINT	snuksegdef;	/* size of extended key segment definitions */
#else
    ppctKSEGDEF	spuksegdef;	/* array of extended key segment definition pointers */
    NINT	snuksegdef;	/* number of extended key segment definition pointers */
#endif
#endif
#ifdef ctDBGfpglok
    NINT	sdbgrec;	/* set by application to track record locks */
    NINT	sdbgcnt;	/* current count of record locks */
#endif
    UTEXT	srtgdrvflavor; /* RTG driver "flavor" ctPortRTG */
#ifdef ctFeatADVLOG
    ctADVLOG	sAdvLog;	/* SUBSYSTEM AUDIT LOG */
#endif
#ifdef ctFeatKEYCOMPRESSsRLE
    ctCompressContext *  spkcRLEctxCmp;  /* Key Compression compression */
    ctCompressContext *  spkcRLEctxExp;  /* Key Compression expansion */
    CMPRECFNC	skcRLEfnc;       /* Key Compression descriptor */
#endif
#ifdef ctFeatTRANSACTION_ID
    ULONG8	transactionId; /* transaction id */
#endif
    itim_err_context_t itim_err_context; /* context in which ITIM_ERR occurred */
#ifdef ctDEBUG_COMPACT_TRUNCATE
    NINT        truncateForcedErrorLocation; /* location of forced error in file truncate */
    TEXT        truncateExitOnForcedError; /* non-zero if process is to exit at forced error location in file truncate */
#endif
#ifdef ctDBG_REPLICAT_SYNC2
    NINT        syncReplForcedErrorLocation; /* location of forced error for testing synchronous replication */
    TEXT        syncReplExitOnForcedError; /* non-zero if process is to exit at forced error location */
#endif
#ifdef ctFeatCHECK_FILENAME_VALIDITY
    TEXT	checkFileNameValidity; /* check for valid filename on create and open */
#endif
} CTGVAR, ctMEM * pCTGVAR, ctMEM * ctMEM * ppCTGVAR;
#endif /* ctNOGLOBALS || ctFeatSRVDLL */

#ifdef CTBOUND
EXTERN pTEXT ctlocdir; /* local directory for standalone mode */
EXTERN pTEXT ctmstkeyfilnam; /* master key file name */
#endif

#ifdef ctNOGLOBALS

#ifdef ctThrdApp

#ifndef ctCLIENTcore
#ifndef ctMTFPGreentrant
#define ctWNGV	((pCTGVAR)ctThrdGet())
#endif
#endif

/*
** Ensure unique name for this variable when a process loads both the server
** and the multi-threaded client shared library.
*/
#define ctgv_thd mtc_ctgv_thd

EXTERN NINT	ctgv_incr;
EXTERN ppCTGVAR ctgv_thd;
#ifdef ctThrdRet
EXTERN ppVOID	ctgv_ptr;
#endif
#ifdef ctFeatCRITSECTSPIN
EXTERN LONG	critsectspin;	/* critical section spin limit	  */
#endif

#else  /* ctThrdApp */
#ifdef ctThrdFPG

#ifndef ctMTFPGreentrant
#ifdef CTPERM
EXTERN pCTGVAR ctWNGV;
#else
#ifndef rtThrds
#define ctWNGV	((pCTGVAR)ctThrdGet())
#endif	/* ~rtThrds */
#endif
#endif

EXTERN NINT	ctgv_incr;
EXTERN ppCTGVAR ctgv_thd;
#ifdef ctThrdRet
EXTERN ppVOID	ctgv_ptr;
#endif

#else /* ctThrdFPG */

EXTERN pCTGVAR ctWNGV;

#endif /* ctThrdFPG */
#endif /* ctThrdApp */

#define ctumxfil	ct_mxfil
#define cthghfil	ct_mxfil
#define commCmds	ctWNGV->scommCmds
#define commGbls	ctWNGV->scommGbls
#ifdef ctCAMOsdk
#define ctcamver	ctWNGV->sctcamver
#endif
#define netrecr		ctWNGV->snetrecr
#define ctITIMlimit	ctWNGV->sctITIMlimit
#define ctITIMdefer	ctWNGV->sctITIMdefer
#define cthghwrd	ctWNGV->scthghwrd

#ifdef CTBOUND
#define ctrebhed	ctWNGV->sctrebhed
#define ctcmphed	ctWNGV->sctcmphed
#define ctmirhed	ctWNGV->sctmirhed
#define ctiblhed	ctWNGV->sctiblhed
#define lstsiz		ctWNGV->slstsiz
#ifdef DBG749x
#define lstchk		ctWNGV->slstchk
#endif
#define lstcnt		ctWNGV->slstcnt
#define ctlist		ctWNGV->sctlist

#define ctfmru        ctWNGV->sctfmru
#define ct_mru        ctWNGV->sct_mru
#define ctfcbhdr      ctWNGV->sctfcbhdr
#define ctconanc      ctWNGV->sctconanc
#define ctconid       ctWNGV->sctconid
#define ct_tmppth     ctWNGV->sct_tmppth
#define ct_tmppth_allocd ctWNGV->sct_tmppth_allocd
#define ctconbins     ctWNGV->sctconbins
#ifdef DBGtree
#define ct_walkh      ctWNGV->sct_walkh
#define ct_walkt      ctWNGV->sct_walkt
#define ctlflg        ctWNGV->sctlflg
#endif /* DBGtree */
#ifdef ctFeatPARTITION_ESTIMATE
#define ctprtestlimit ctWNGV->sctprtestlimit
#define ctprtestpct   ctWNGV->sctprtestpct
#endif
#ifdef ctFeatFILEBLOCKcounter
#define ctfilblkcnt   ctWNGV->sctfilblkcnt
#endif
#define ct_initerr    ctWNGV->sct_initerr
#ifdef ctFeatFILENAMEhash
#define ct_fnhash   ctWNGV->sct_fnhash
#define ct_fnbins   ctWNGV->sct_fnbins
#endif
#ifdef ctFeatLOGLMT
#define ct_llhash   ctWNGV->sct_llhash
#define ct_llbins   ctWNGV->sct_llbins
#ifdef ctFeatLOGLMTusracct
#define ndusracct   ctWNGV->sndusracct
#define mdusracct   ctWNGV->smdusracct
#define mcusracct   ctWNGV->smcusracct
#endif
#endif
#ifdef ctFeatAUTO_MKDIR
#define ctautomkdir   ctWNGV->sctautomkdir
#endif
#define ct_btree      ctWNGV->sct_btree
#define ct_dbufr      ctWNGV->sct_dbufr
#define ct_key        ctWNGV->sct_key
#define ct_dat        ctWNGV->sct_dat
#define ct_vat        ctWNGV->sct_vat
#ifdef DBG749x
#define ctlstfrq      ctWNGV->sctlstfrq
#endif
#define ct_tmpseq     ctWNGV->sct_tmpseq
#define ct_lhbins     ctWNGV->sct_lhbins
#define ct_lhbinx     ctWNGV->sct_lhbinx
#define ct_lhLoadF    ctWNGV->sct_lhLoadF
#define ct_lhRehashF  ctWNGV->sct_lhRehashF
#define ct_lhMaxBins  ctWNGV->sct_lhMaxBins
#define ct_ulMaxBins  ctWNGV->sct_ulMaxBins
#define ct_shMaxBins  ctWNGV->sct_shMaxBins
#define ct_lhNoShrink ctWNGV->sct_lhNoShrink
#define ct_ulNoShrink ctWNGV->sct_ulNoShrink
#define ct_shNoShrink ctWNGV->sct_shNoShrink
#ifdef ctPortYMF
#define ct_spltNbrFls ctWNGV->sct_spltNbrFls
#endif
#ifdef DBGhash
#define dbg_lhsh_u    ctWNGV->sdbg_lhsh_u
#endif
#define ct_dftot      ctWNGV->sct_dftot
#define ct_dfnum      ctWNGV->sct_dfnum
#define ct_dfdef      ctWNGV->sct_dfdef
#define ct_dfatot     ctWNGV->sct_dfatot
#define ct_dfanum     ctWNGV->sct_dfanum
#define ct_dfadef     ctWNGV->sct_dfadef
#ifdef ctFeatFILMTX
#define filmtx_tot    ctWNGV->sfilmtx_tot
#define filmtx_num    ctWNGV->sfilmtx_num
#define filmtx_ary    ctWNGV->sfilmtx_ary
#endif
#ifdef ctDYNHASH
#define ct_lokstt     ctWNGV->sct_lokstt
#define ct_locksb     ctWNGV->sct_locksb
#define ct_locks(bin) ctWNGV->sct_locksb[bin].h
#define ct_ltail(bin) ctWNGV->sct_locksb[bin].t
#else
#define ct_locksb     ctWNGV->sct_locksb
#define ct_locks(bin) ctWNGV->sct_locksb[bin]
#define ct_ltail(bin) ctWNGV->sct_ltailb[bin]
#endif
#define ctactfil      ctWNGV->sctactfil
#define cttotfil      ctWNGV->scttotfil
#define cttotblk      ctWNGV->scttotblk
#define ctactfilx     ctWNGV->sctactfilx
#define cttotfilx     ctWNGV->scttotfilx
#define cttotblkx     ctWNGV->scttotblkx
#define ctloknmx      ctWNGV->sctloknmx
#define ct_spc	      ctWNGV->sct_spc
#define ct_disklmt    ctWNGV->sct_disklmt
#define ct_dbrqs      ctWNGV->sct_dbrqs
#define ct_dbhit      ctWNGV->sct_dbhit
#define ct_ibrqs      ctWNGV->sct_ibrqs
#define ct_ibhit      ctWNGV->sct_ibhit
#define ct_rdops      ctWNGV->sct_rdops
#define ct_rdbyt      ctWNGV->sct_rdbyt
#define ct_wrops      ctWNGV->sct_wrops
#define ct_wrbyt      ctWNGV->sct_wrbyt
#define ct_rcops      ctWNGV->sct_rcops
#define ct_rcbyt      ctWNGV->sct_rcbyt
#define ct_wcops      ctWNGV->sct_wcops
#define ct_wcbyt      ctWNGV->sct_wcbyt
#define ctwlgops      ctWNGV->sctwlgops
#define ctwlgbyt      ctWNGV->sctwlgbyt
#define ctrlgops      ctWNGV->sctrlgops
#define ctrlgbyt      ctWNGV->sctrlgbyt
#define ctxlgops      ctWNGV->sctxlgops
#define ctxlgbyt      ctWNGV->sctxlgbyt
#define ct_trbeg      ctWNGV->sct_trbeg
#define ct_trend      ctWNGV->sct_trend
#define ct_trabt      ctWNGV->sct_trabt
#define ct_trsav      ctWNGV->sct_trsav
#define ct_trrst      ctWNGV->sct_trrst
#define ct_trfls      ctWNGV->sct_trfls
#define ct_ribs       ctWNGV->sct_ribs
#define ctsync_dosfls ctWNGV->sctsync_dosfls
#define ctsync_logfil ctWNGV->sctsync_logfil
#define ctsync_regfil ctWNGV->sctsync_regfil
#define ct_abseq      ctWNGV->sct_abseq
#define ct_abnod      ctWNGV->sct_abnod
#define ct_cmnod      ctWNGV->sct_cmnod
#define ct_cmdat      ctWNGV->sct_cmdat
#define ct_statflg    ctWNGV->sct_statflg
#define ct_sysviewT   ctWNGV->sct_sysviewT
#define ct_sysviewN   ctWNGV->sct_sysviewN
#define ct_langflg    ctWNGV->sct_langflg
#define ct_numvi      ctWNGV->sct_numvi
#define endcnt        ctWNGV->sendcnt
#define ksgcurs	      ctWNGV->sksgcurs
#define ct_compflg    ctWNGV->sct_compflg	/* 1st compatibility word	*/
#define ct_compflg2   ctWNGV->sct_compflg2	/* 2nd compatibility word	*/
#define ct_compflg3   ctWNGV->sct_compflg3	/* 3rd compatibility word	*/
#define ct_compflg4   ctWNGV->sct_compflg4	/* 4th compatibility word	*/
#define ct_compflg5   ctWNGV->sct_compflg5	/* 5th compatibility word	*/
#define ct_diagflg    ctWNGV->sct_diagflg	/* 1st diagnostics word		*/
#define ct_diagflg2   ctWNGV->sct_diagflg2	/* 2nd diagnostics word		*/
#define ct_diagflg3   ctWNGV->sct_diagflg3	/* 3rd diagnostics word		*/
#define ksgtots	      ctWNGV->sksgtots
#define ksglsts	      ctWNGV->sksglsts
#define ct_dq         ctWNGV->sct_dq
#define ct_cq         ctWNGV->sct_cq
#define ctfnz         ctWNGV->sctfnz
#ifndef BOUND
#define ct_lq         ctWNGV->sct_lq
#endif
#define ctmiroff	ctWNGV->sctmiroff
#define ctosIOlok	ctWNGV->sctosIOlok
#ifdef TRANPROC
#define ct_ubit(owner)	ctWNGV->sct_ubit
#ifdef DBGhash
#define dbg_shsh_u(owner) ctWNGV->sdbg_shsh_u
#endif
#define ct_usrsp	ctWNGV->sct_usrsp
#define ct_usrsl	ctWNGV->sct_usrsl
#define ct_usrsz	ctWNGV->sct_usrsz
#define ctshdmem	ctWNGV->sctshdmem
#define ctusrsum	ctWNGV->sctusrsum
#define ctusrtot	ctWNGV->sctusrtot
#define ct_usrsi	ctWNGV->sct_usrsi
#define ct_usrsv(a)	ctWNGV->sct_usrsv
#define ct_rstflg(a)	ctWNGV->sct_rstflg
#define ct_shbins       ctWNGV->sct_shbins
#define ct_shbyts       ctWNGV->sct_shbyts
#define ct_trnhghmrk	ctWNGV->sct_trnhghmrk
#define ct_tryprvchk	ctWNGV->sct_tryprvchk
#define ctsuplog	ctWNGV->sctsuplog
#define ctsuplogsync	ctWNGV->sctsuplogsync
#define ctfstr		ctWNGV->sctfstr
#define ctfwdned	ctWNGV->sctfwdned
#define ct_chktrd       ctWNGV->sct_chktrd
#define ctlgbf          ctWNGV->sctlgbf
#define ctlstshd        ctWNGV->sctlstshd
#define ctlstsav        ctWNGV->sctlstsav
#define ctlstshdm(a)    ctWNGV->sctlstshd[a]
#define ctlstsavm(a)    ctWNGV->sctlstsav[a]
#ifdef ctFeatADDKY_DEFERD
#define skpaddhed(a)	ctWNGV->sskpaddhed[a]
#define skpaddend(a)	ctWNGV->sskpaddend[a]
#define skpkeyctx(a)	ctWNGV->sskpkeyctx[a]
#endif
#ifdef ctLOG_IDX
#define cttrnanc        ctWNGV->scttrnanc
#endif
#define ctLnum          ctWNGV->sctLnum
#define ctUnum          ctWNGV->sctUnum
#define ctSnum          ctWNGV->sctSnum
#define ctLfil          ctWNGV->sctLfil
#define ctUfil          ctWNGV->sctUfil
#define ctSfil          ctWNGV->sctSfil
#define ctdmptim        ctWNGV->sctdmptim
#define ctdlgnum        ctWNGV->sctdlgnum
#define ctelgnum        ctWNGV->sctelgnum
#define ctdlgpos        ctWNGV->sctdlgpos
#define ctelgpos        ctWNGV->sctelgpos
#define ctcpcnt         ctWNGV->sctcpcnt
#define ctcpchk         ctWNGV->sctcpchk
#define ctelcnt         ctWNGV->sctelcnt
#define ct_lstlog       ctWNGV->sct_lstlog
#define ct_lstpos       ctWNGV->sct_lstpos
#define ct_strlog       ctWNGV->sct_strlog
#define ct_strpos       ctWNGV->sct_strpos
#define ct_rcvlog       ctWNGV->sct_rcvlog
#define ctfwdlog        ctWNGV->sctfwdlog
#define ctfwdpos        ctWNGV->sctfwdpos
#define ctfwdpps        ctWNGV->sctfwdpps
#define ct_usrsq(a)     ctWNGV->sct_usrsq[a]
#define ct_usrtr(a)     ctWNGV->sct_usrtr[a]
#define ct_usrmd(a)     ctWNGV->sct_usrmd[a]
#ifdef ctFeat6BT
#define ct_usrtr2(a)    ctWNGV->sct_usrtr2[a]
#define ct_usrix2(a)    ctWNGV->sct_usrix2[a]
#endif
#ifdef ctFeatDFRIDX
#define ct_usrdkln(a)	ctWNGV->sct_usrdkln[a]
#define ct_usrdklp(a)	ctWNGV->sct_usrdklp[a]
#define ct_usrdkln2(a)	ctWNGV->sct_usrdkln2[a]
#define ct_usrdklp2(a)	ctWNGV->sct_usrdklp2[a]
#if defined(ctFeatRUCB) && defined(TRANPROC)
#define rucbhed(a)	ctWNGV->srucbh[a]
#define rucbend(a)	ctWNGV->srucbt[a]
#endif
#endif
#ifdef ctXTDLOGgrp
#define ct_usrgr(a)     ctWNGV->sct_usrgr[a]
#define ct_usrgp(a)     ctWNGV->sct_usrgp[a]
#endif
#define ct_usrtl(a)     ctWNGV->sct_usrtl[a]
#define ct_usrix(a)     ctWNGV->sct_usrix[a]
#ifdef ctSUCTRAN
#define ct_usrbl(a)     ctWNGV->sct_usrbl[a]
#define ct_usrbp(a)     ctWNGV->sct_usrbp[a]
#define ct_usrel(a)     ctWNGV->sct_usrel[a]
#define ct_usrep(a)     ctWNGV->sct_usrep[a]
#define ct_usrtv(a)     ctWNGV->sct_usrtv[a]
#define ct_usrtv2(a)    ctWNGV->sct_usrtv2[a]
#endif
#ifdef ctXTDLOG
#define ct_mxusrlog	ctWNGV->sct_mxusrlog
#endif
#define ct_lbfsiz       ctWNGV->sct_lbfsiz
#define ct_chkflg       ctWNGV->sct_chkflg
#define ct_logkep       ctWNGV->sct_logkep
#define ctskpfil        ctWNGV->sctskpfil
#define ctskpato        ctWNGV->sctskpato
#define ctskpiaf	ctWNGV->sctskpiaf
#define ctskpmir        ctWNGV->sctskpmir
#define ctbadmir        ctWNGV->sctbadmir
#define ctfixlog        ctWNGV->sctfixlog
#define ctpdmp          ctWNGV->sctpdmp
#define ct_usrty(a)     ctWNGV->sct_usrty[a]
#ifdef ctRECBYTIDX
#define ct_coalst(a)	ctWNGV->sct_coalst
#define ct_coalcr(a)	ctWNGV->sct_coalcr
#define ct_coaltt(a)	ctWNGV->sct_coaltt
#define ct_coalcs(a)	ctWNGV->sct_coalcs
#endif
#define ctshdlfil       ctWNGV->sctshdlfil
#define ct_lgn          ctWNGV->sct_lgn
#define ctsflg          ctWNGV->sctsflg
#define ctbflg          ctWNGV->sctbflg
#define ctdflg          ctWNGV->sctdflg
#define ct_actrns       ctWNGV->sct_actrns
#define ct_lerflg       ctWNGV->sct_lerflg
#define ct_chkpt(a)     ctWNGV->sct_chkpt[a]
#define ctlogmem        ctWNGV->sctlogmem
#define ctlogdet        ctWNGV->sctlogdet
#define ctlogmemmax     ctWNGV->sctlogmemmax
#define ctlogmemanc     ctWNGV->sctlogmemanc
#define trnwrn		ctWNGV->strnwrn
#define filwrn		ctWNGV->sfilwrn
#define prv_logser	ctWNGV->sprv_logser
#define prv_chkpos	ctWNGV->sprv_chkpos
#define prv_prvpos	ctWNGV->sprv_prvpos
#define ctlogchklmt	ctWNGV->sctlogchklmt
#define ctskpclnfil	ctWNGV->sctskpclnfil
#endif
#ifdef ctFeatRUCB
#define rucbsess	ctWNGV->srucbsess
#endif
#define ct_lstchktim  ctWNGV->sct_lstchktim
#define ct_bfsiz      ctWNGV->sct_bfsiz
#define ctlogidxfrc   ctWNGV->sctlogidxfrc
#define ctrdmp_opt    ctWNGV->sctrdmp_opt
#define ctrdmp_memlog ctWNGV->sctrdmp_memlog
#define ctrdmp_flg    ctWNGV->sctrdmp_flg
#define ctmdmp_flg    ctWNGV->sctmdmp_flg
#define ctfdmp_flg    ctWNGV->sctfdmp_flg
#define ctxflg        ctWNGV->sctxflg
#define ctxflgfd      ctWNGV->sctxflgfd
#define ctridx_ptr    ctWNGV->sctridx_ptr
#define ctridx_cur    ctWNGV->sctridx_cur
#define ctridx_tot    ctWNGV->sctridx_tot
#define clnidxx_flag  ctWNGV->sclnidxx_flag
#define ctrflg        ctWNGV->sctrflg
#define recovery_TRANDEP_operation ctWNGV->srecovery_TRANDEP_operation
#define drtyflg       ctWNGV->sdrtyflg
#define ctminlogsync  ctWNGV->sctminlogsync
#define ctkep_rp_rcv  ctWNGV->sctkep_rp_rcv
#define ctkep_rp_cfg  ctWNGV->sctkep_rp_cfg
#define ctkep_rp_num  ctWNGV->sctkep_rp_num
#define ctkep_rp_act  ctWNGV->sctkep_rp_act
#define ctkep_rp_fnd  ctWNGV->sctkep_rp_fnd
#define ctkep_rp_req  ctWNGV->sctkep_rp_req
#define ctkep_rp_tim  ctWNGV->sctkep_rp_tim
#define ct_clstrn     ctWNGV->sct_clstrn
#define ct_endser     ctWNGV->sct_endser
#define ctkep_rp_srn  ctWNGV->sctkep_rp_srn
#define ctnewlogs     ctWNGV->sctnewlogs
#define ctstrcv_flg   ctWNGV->sctstrcv_flg
#define ctrbflg       ctWNGV->sctrbflg
#define ctfnstrat     ctWNGV->sctfnstrat
#define ctmnstrat     ctWNGV->sctmnstrat
#define cttflg        ctWNGV->scttflg
#define cttflg_L      ctWNGV->scttflg_L
#define ctrint_L      ctWNGV->sctrint_L
#define ctfilcre      ctWNGV->sctfilcre
#define ct_mxu1       ctWNGV->sct_mxu1
#define ct_cmnown     ctWNGV->sct_cmnown
#define ct_hshft      ctWNGV->sct_hshft
#define ct_hbins      ctWNGV->sct_hbins
#define ct_dshft      ctWNGV->sct_dshft
#define ct_dbins      ctWNGV->sct_dbins
#ifdef ctLOG_IDX
#define ct_tbins      ctWNGV->sct_tbins
#endif
#define ct_bavl       ctWNGV->sct_bavl
#define ct_bhla       ctWNGV->sct_bhla
#ifdef DBGhash
#define dbg_bhl_n     ctWNGV->sdbg_bhl_n
#define dbg_bhl_d     ctWNGV->sdbg_bhl_d
#endif
#define ctsdname      ctWNGV->sctsdname
#define ctsmname      ctWNGV->sctsmname
#define ctsvname      ctWNGV->sctsvname
#define ctsqname      ctWNGV->sctsqname
#ifdef ctPortVINESLOG
#define ctlgname      ctWNGV->sctlgname
#endif
#define ctscommp      ctWNGV->sctscommp

#ifdef ctFeatJOBMGTSYS 				/* FairCom Job Management System Subsystem */
#define ctsjobsf      ctWNGV->sctsjobsf
#endif   

#define cts_list_m    ctWNGV->scts_list_m
#define cts_sort_m    ctWNGV->scts_sort_m
#define cts_bufr_m    ctWNGV->scts_bufr_m

#define ct_mxbuf      ctWNGV->sct_mxbuf
#define ctbufcnt      ctWNGV->sctbufcnt
#define ctbufhgh      ctWNGV->sctbufhgh
#define ct_dxbuf      ctWNGV->sct_dxbuf
#define ctdatcnt      ctWNGV->sctdatcnt
#define ctdathgh      ctWNGV->sctdathgh
#define ctmtcsegflg   ctWNGV->sctmtcsegflg
#define ctnonsegflg   ctWNGV->sctnonsegflg
#define ct_dxspllmt   ctWNGV->sct_dxspllmt
#define ct_dxsplcnt   ctWNGV->sct_dxsplcnt
#define ct_dxsplhgh   ctWNGV->sct_dxsplhgh
#define ctmpagcache   ctWNGV->sctmpagcache
#define ct_ndsec      ctWNGV->sct_ndsec
#define ct_maxvfil    ctWNGV->sct_maxvfil
#define ct_numvfil    ctWNGV->sct_numvfil
#define ct_avlfil     ctWNGV->sct_avlfil
#define ct_ver1       ctWNGV->sct_ver1
#define ct_ver2       ctWNGV->sct_ver2
#define ct_ver3       ctWNGV->sct_ver3
#define ct_del        ctWNGV->sct_del
#define ct_delsiz     ctWNGV->sct_delsiz
#define ctsupsep      ctWNGV->sctsupsep
#define ct_savbat     ctWNGV->ssavbat
#define ctbatnum      ctWNGV->sbatnum
#define ctbatmax      ctWNGV->sbatmax
#define ctbatch       ctWNGV->batch
#define cthstnum      ctWNGV->shstnum
#define ct_savhst     ctWNGV->ssavhst
#define cthistory     ctWNGV->history
#define cthistund     ctWNGV->histund

#define prvlokf       ctWNGV->sprvlokf
#define prvlokt       ctWNGV->sprvlokt
#define prvlokt2      ctWNGV->sprvlokt2
#define prvlokp       ctWNGV->sprvlokp
#define prvlokh       ctWNGV->sprvlokh


#ifdef ctHUGEFILE
#define ct_gsrl2      ctWNGV->sct_gsrl2
#endif /* ctHUGEFILE */
#define ct_gsrl1      ctWNGV->sct_gsrl1
#define IDfield_lstoff ctWNGV->sIDfield_lstoff
#define ct_IDfield    ctWNGV->sct_IDfield
#define ct_trdflg     ctWNGV->sct_trdflg
#define nsplit        ctWNGV->snsplit

#define ct_buf        ctWNGV->sct_buf

#ifdef ISAM_VARS
#define ctskyorg      ctWNGV->sctskyorg
#define ctskymap      ctWNGV->sctskymap
#define ctis1         ctWNGV->sctis1
#define ctis2         ctWNGV->sctis2

#define ct_fndval     ctWNGV->sct_fndval
#define ct_nwrcfg     ctWNGV->sct_nwrcfg
#define ct_vfsg       ctWNGV->sct_vfsg
#define ct_ismlk      ctWNGV->sct_ismlk
#define ct_fndlen     ctWNGV->sct_fndlen
#ifdef ctFeatRECRLOCK
#define ct_ismrc      ctWNGV->sct_ismrc
#endif
#define ct_savset     ctWNGV->sct_savset

#define seqbuf	      ctWNGV->sseqbuf
#define seqold	      ctWNGV->sseqold
#define seqlen	      ctWNGV->sseqlen
#define seqkey	      ctWNGV->sseqkey
#define seqnum	      ctWNGV->sseqnum
#ifdef ctOldALCSET
#define maxqset	      ctWNGV->smaxqset
#endif /* ctOldALCSET */
#endif
#ifdef TRANPROC
#define ctlpathf	ctWNGV->sctlpathf
#define ctlpathm	ctWNGV->sctlpathm
#define ct_trndlt	ctWNGV->sct_trndlt
#define ct_cpdlt	ctWNGV->sct_cpdlt
#define ct_logchn	ctWNGV->sct_logchn
#define ct_logpts	ctWNGV->sct_logpts
#define ct_loglmt	ctWNGV->sct_loglmt
#define ct_logspc	ctWNGV->sct_logspc
#define ct_logrec	ctWNGV->sct_logrec
#define ct_logtrg	ctWNGV->sct_logtrg
#define ct_blgpos	ctWNGV->sct_blgpos
#define ct_logprg	ctWNGV->sct_logprg
#define ct_savprg	ctWNGV->sct_savprg
#ifdef ctBEHAV_DLYLOGPRG
#define ct_begprg	ctWNGV->sct_begprg
#define ct_numprg	ctWNGV->sct_numprg
#define ct_newprg	ctWNGV->sct_newprg
#define ct_lstsav	ctWNGV->sct_lstsav
#endif
#ifdef ctFeat6BT
#define ct_lowtrn2 	ctWNGV->sct_lowtrn2
#endif
#define ct_lowtrn 	ctWNGV->sct_lowtrn
#define logtrn_seq	ctWNGV->slogtrn_seq
#define logtrn_tot	ctWNGV->slogtrn_tot
#define logtrn_cur	ctWNGV->slogtrn_cur
#define logtrn_lst	ctWNGV->slogtrn_lst
#define rplist_tot	ctWNGV->srplist_tot
#define rplist_cur	ctWNGV->srplist_cur
#define rplist_ptr	ctWNGV->srplist_ptr
#define redolist_tot	ctWNGV->sredolist_tot
#define redolist_cur	ctWNGV->sredolist_cur
#define redolist_ptr	ctWNGV->sredolist_ptr
#define skplst_anc	ctWNGV->sskplst_anc
#define skplst_tot	ctWNGV->sskplst_tot
#define skplst_cur	ctWNGV->sskplst_cur
#define ct_lnmlog	ctWNGV->sct_lnmlog
#define ct_hnmlog	ctWNGV->sct_hnmlog
#define ct_oldlog	ctWNGV->sct_oldlog
#define ct_replog	ctWNGV->sct_replog
#define ct_logspr	ctWNGV->sct_logspr
#define ct_logblk	ctWNGV->sct_logblk
#define ct_rcvlst	ctWNGV->sct_rcvlst
#define ct_rcvhshOrig	ctWNGV->sct_rcvhshOrig
#define ct_rcvhshFull	ctWNGV->sct_rcvhshFull
#define ct_rcvhshBins	ctWNGV->sct_rcvhshBins
#define ct_rcvopnhshOrig ctWNGV->sct_rcvopnhshOrig
#define ct_rcvopnhshFull ctWNGV->sct_rcvopnhshFull
#define ct_rcvopnhshBins ctWNGV->sct_rcvopnhshBins
#define ct_hdrlst	ctWNGV->sct_hdrlst
#define ct_mbrlst	ctWNGV->sct_mbrlst
#define ct_clnlst	ctWNGV->sct_clnlst
#define anydelmrk	ctWNGV->sanydelmrk
#define intpthflg	ctWNGV->sintpthflg
#define ctlpathfa	ctWNGV->sctlpathfa
#define ctlpathma	ctWNGV->sctlpathma
#define undflg(a)	ctWNGV->sundflg[a]
#define lowbeglog	ctWNGV->slowbeglog
#define lowbeglog_cp	ctWNGV->slowbeglog_cp
#define numhgh		ctWNGV->snumhgh
#define cttopcmt	ctWNGV->scttopcmt
#define cttoplog	ctWNGV->scttoplog
#define ctbegcmt	ctWNGV->sctbegcmt
#define ctbeglog	ctWNGV->sctbeglog
#define logrem	 	ctWNGV->slogrem
#define lbfpag	 	ctWNGV->slbfpag
#define logptr	 	ctWNGV->slogptr
#define logbyt	 	ctWNGV->slogbyt
#define lowpnt	 	ctWNGV->slowpnt
#define lstpnt	 	ctWNGV->slstpnt
#define lstsuc	 	ctWNGV->slstsuc
#define hghcmt	 	ctWNGV->shghcmt
#define hghlog	 	ctWNGV->shghlog
#ifdef ctFeatLOGREAD
#define ctlogred	ctWNGV->sctlogred
#define ctreplopts	ctWNGV->sctreplopts
#endif
#else
#define tranactv	ctWNGV->stranactv
#define transavp	ctWNGV->stransavp
#endif /* TRANPROC */
#define ctstatlogflg	ctWNGV->sctstatlogflg
#define ctstatlogpath	ctWNGV->sctstatlogpath
#define ctcatcnt	ctWNGV->sctcatcnt
#define ct_bsz		ctWNGV->sct_bsz
#define ct_rbuf		ctWNGV->sct_rbuf
#define rerr_cod	ctWNGV->srerr_cod
#define rerr_fil	ctWNGV->srerr_fil
#define ct_fp		ctWNGV->sct_fp
#endif /* CTBOUND */
#if !defined(CTBOUND) || defined(ctFeatOTREE) || defined(otOTREE)
#define ctusrbuf	ctWNGV->sctusrbuf
#define ctlqmsg		ctWNGV->sctlqmsg
#define hlocl		ctWNGV->shlocl
#define hauxl		ctWNGV->shauxl
#define cthicon		ctWNGV->scthicon
#define cthugflg	ctWNGV->scthugflg
#define ctreqsiz	ctWNGV->sctreqsiz
#define ctrspsiz	ctWNGV->sctrspsiz
#define ctinpoff	ctWNGV->sctinpoff
#define ctoutoff	ctWNGV->sctoutoff
#define ctusrlen	ctWNGV->sctusrlen
#define ctusrpos	ctWNGV->sctusrpos
#define ctsrvlen	ctWNGV->sctsrvlen
#define ctsflvr		ctWNGV->sctsflvr
#define ctnodnam	ctWNGV->sctnodnam
#define ct_lq		ctWNGV->sct_lq
#define ctautotfrm	ctWNGV->sctautotfrm
#define ctmaxdatkey	ctWNGV->sctmaxdatkey
#define ctisam_flg	ctWNGV->sctisam_flg
#define ct_autopos_clr	ctWNGV->sct_autopos_clr
#define ctsrvopt	ctWNGV->sctsrvopt
#define ctspclogon	ctWNGV->sctspclogon
#define ctsrvver	ctWNGV->sctsrvver
#define ctsrbytatr	ctWNGV->sctsrbytatr
#ifdef ctLOCLIB
#define ct_tmppth       ctWNGV->sct_tmppth
#define ct_tmppth_allocd ctWNGV->sct_tmppth_allocd
#endif
#endif /* ~CTBOUND || ctFeatOTREE || otOTREE */
#define ctbpfx_level  ctWNGV->sctbpfx_level
#ifdef ctBEHAV_XTDHDR
#define cth6flg		ctWNGV->scth6flg
#endif
#define align_override	ctWNGV->salign_override

#ifndef ctFeatL10_serno
#ifdef ctCLIENT
#define ctdivs        ctWNGV->sctdivs
#endif
#endif
#define ctnusers      ctWNGV->sctnusers
#define ucamfnc	      ctWNGV->sucamfnc
#define ucamptr	      ctWNGV->sucamptr
#define ct_cam        ctWNGV->sct_cam
#define ct_camsiz     ctWNGV->sct_camsiz
#define ucamlen	      ctWNGV->sucamlen
#define ctrecur	      ctWNGV->sctrecur
#define andaborted    ctWNGV->sandaborted
#define apicallback   ctWNGV->sapicallback

#ifdef ctFeatNONBLK_SOCKIO
#define ctsocktimeout ctWNGV->sctsocktimeout
#define ctSocketWaitInterval ctWNGV->sctSocketWaitInterval
#endif
#ifdef ctFeatUNIX_SHMEM
#define ctshmemdir    ctWNGV->sctshmemdir
#define ctshmemprm    ctWNGV->sctshmemprm
#ifdef ctFeatSHMEMgrp
#define ctshmemgrp    ctWNGV->sctshmemgrp
#endif
#endif
#ifdef ctFeatPWDSEC
#define cturn         ctWNGV->scturn
#define ctuhp         ctWNGV->sctuhp
#endif
#ifdef ctFeatNOBUFFERING_LOGFILE
#define ctnobuflogs   ctWNGV->sctnobuflogs
#endif
#ifdef ctFeatNOBUFFERING
#define ctunbufio     ctWNGV->sctunbufio
#endif
#ifdef ctFeatENCSTORE
#define ctmstkeyfil   ctWNGV->sctmstkeyfil
#endif
#ifdef ctFeatTRANSFER_FILE
#define ctfilexfrfp   ctWNGV->sctfilexfrfp	/* file pointer for ctTransferFile operation */
#endif

#ifdef ctFeatREBUILD_OPT
#define ctmaxktouse   ctWNGV->sctmaxktouse	/* MAX_K_TO_USE for rebuild*/
#define ctmaxhandles  ctWNGV->sctmaxhandles	/* MAX_HANDLES for rebuild*/
#endif
#define InitRWLock    ctWNGV->sInitRWLock
#define AcqRWLockExc  ctWNGV->sAcqRWLockExc
#define AcqRWLockShr  ctWNGV->sAcqRWLockShr
#define TryRWLockExc  ctWNGV->sTryRWLockExc
#define TryRWLockShr  ctWNGV->sTryRWLockShr
#define RelRWLockExc  ctWNGV->sRelRWLockExc
#define RelRWLockShr  ctWNGV->sRelRWLockShr
#define DestroyRWLock ctWNGV->sDestroyRWLock
#ifdef ctFeatAUTO_SHMEM
#define ctcommfns     ctWNGV->sctcommfns	/* communication protocol function pointers */
#endif
#define ct_allsup     ctWNGV->sct_allsup
#define ct_logsup     ctWNGV->sct_logsup
#define ct_logaug     ctWNGV->sct_logaug
#ifdef ctUNICODE
#ifndef ctBEHAV_CHECK_ICU_COLLATOR_VERSION
#define kseg_icuv     ctWNGV->skseg_icuv
#endif
#define kseg_icuE     ctWNGV->skseg_icuE
#define kseg_icuD     ctWNGV->skseg_icuD
#endif
#define nocamocomm    ctWNGV->snocamocomm
#define ctops	      ctWNGV->sctops
#ifdef ctCMPLOG
#define logcmpcnt     ctWNGV->slogcmpcnt
#define logcmpbuf     ctWNGV->slogcmpbuf
#define logcmplen     ctWNGV->slogcmplen
#endif
#define ctstate	      ctWNGV->sctstate
#define ctstat2	      ctWNGV->sctstat2
#define ctstat3	      ctWNGV->sctstat3
#define ctstat4	      ctWNGV->sctstat4
#define ctstat5	      ctWNGV->sctstat5
#define ctstat6	      ctWNGV->sctstat6
/* ctSIBLING_CTSTATE - Add new state variable here */
#define ctxvlen	      ctWNGV->sctxvlen
#define ctstatg	      ctWNGV->sctstatg
#define ctdfrcls      ctWNGV->sctdfrcls
#define	memsubflg     ctWNGV->smemsubflg
#define ct_trnfilsz   ctWNGV->sct_trnfilsz
#define cthshift      ctWNGV->scthshift
#define ctmaxparm     ctWNGV->sctmaxparm

#define uerr_cod      ctWNGV->suerr_cod
#define sysiocod      ctWNGV->ssysiocod
#define isam_err      ctWNGV->sisam_err
#define isam_fil      ctWNGV->sisam_fil
/* Define macros that can be used to get and set the c-tree error code values,
even if the error code macros get redefined (by ctreep.h for example). */
#define ct_get_uerr_cod( )	(ctWNGV ? ctWNGV->suerr_cod : -1)
#define ct_set_uerr_cod(e)	(ctWNGV ? (ctWNGV->suerr_cod = (e), 0) : -1)
#define ct_get_sysiocod( )	(ctWNGV ? ctWNGV->ssysiocod : -1)
#define ct_set_sysiocod(e)	(ctWNGV ? (ctWNGV->ssysiocod = (e), 0) : -1)
#define ct_get_isam_err( )	(ctWNGV ? ctWNGV->sisam_err : -1)
#define ct_set_isam_err(e)	(ctWNGV ? (ctWNGV->sisam_err = (e), 0) : -1)
#define ct_get_isam_fil( )	(ctWNGV ? ctWNGV->sisam_fil : -1)
#define ct_set_isam_fil(e)	(ctWNGV ? (ctWNGV->sisam_fil = (e), 0) : -1)

#define cndxerr       ctWNGV->scndxerr
#define seglsthdr     ctWNGV->sseglsthdr
#define ct_trnfil     ctWNGV->sct_trnfil
#define ctcidxStk     ctWNGV->sctcidxStk
#define ctcidxStkPtr  ctWNGV->sctcidxStkPtr
#define ctcidxCurCmd  ctWNGV->sctcidxCurCmd
#ifdef ctFeatUDF_EXPR
#define udflist       ctWNGV->sudflist
#define isexpreval    ctWNGV->sisexpreval
#endif
#ifdef ctHUGEFILE
#define revpre_ptr    ctWNGV->srevpre_ptr
#define revpre_tot    ctWNGV->srevpre_tot
#define revpre_cur    ctWNGV->srevpre_cur
#define revdel_ptr    ctWNGV->srevdel_ptr
#define revdel_tot    ctWNGV->srevdel_tot
#define revdel_cur    ctWNGV->srevdel_cur
#define numhgh_ptr    ctWNGV->snumhgh_ptr
#define numhgh_tot    ctWNGV->snumhgh_tot
#define numhgh_cur    ctWNGV->snumhgh_cur
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
#define cmprec_ptr    ctWNGV->scmprec_ptr
#define cmprec_tot    ctWNGV->scmprec_tot
#define cmprec_cur    ctWNGV->scmprec_cur
#endif
#define dedlst_ptr    ctWNGV->sdedlst_ptr
#define dedlst_tot    ctWNGV->sdedlst_tot
#define dedlst_cur    ctWNGV->sdedlst_cur
#define dedlst_avl    ctWNGV->sdedlst_avl
#define renrst_ptr    ctWNGV->srenrst_ptr
#define renrst_tot    ctWNGV->srenrst_tot
#define renrst_cur    ctWNGV->srenrst_cur
#define ctrunfil      ctWNGV->sctrunfil
#define ctrcvfil      ctWNGV->sctrcvfil
#define ct_adfil      ctWNGV->sct_adfil
#define frschgset     ctWNGV->sfrschgset
#define curchgset     ctWNGV->scurchgset
#define frschgbat     ctWNGV->sfrschgbat
#define curchgbat     ctWNGV->scurchgbat
#define cthghflx      ctWNGV->scthghflx
#define ct_mxfil      ctWNGV->sct_mxfil
#define ctusrprf      ctWNGV->sctusrprf
#ifdef ISAM_VARS
#ifdef RTREE
#define srtknm        ctWNGV->ssrtknm
#define srtdat        ctWNGV->ssrtdat
#define tmpdat        ctWNGV->stmpdat
#endif
#endif
#define ct_uflvr      ctWNGV->sct_uflvr
#define ct_ualgn      ctWNGV->sct_ualgn
#define ct_upntr      ctWNGV->sct_upntr

#ifdef RB_CALLBACK
#define rblcbfnc      ctWNGV->srblcbfnc
#define rblcbcnt      ctWNGV->srblcbcnt
#define rblcbstp      ctWNGV->srblcbstp
#ifdef ctFeatREBUILD_CALLBACK_STATE
#define rblpcbst      ctWNGV->srblpcbst
#endif
#endif
#ifdef ctFeatVFYIDX_CS
#define vfymsgcbfnc   ctWNGV->svfymsgcbfnc
#define vfyprgcbfnc   ctWNGV->svfyprgcbfnc
#define vfyflags      ctWNGV->svfyflags
#endif
#ifdef ctFeatVERIFYfile
#define vfyerrcbfnc   ctWNGV->svfyerrcbfnc
#endif
#ifdef ctFeatRTG_API
#define rtgmsgcbfnc    ctWNGV->srtgmsgcbfnc
#define rtgmsgcbusrctx ctWNGV->srtgmsgcbusrctx
#endif
#ifdef ctFeatCOPYFILE
#define cpfprgcbfnc   ctWNGV->scpfprgcbfnc
#endif
#ifdef ctFeatTEMPDIR
#define tdrprgcbfnc   ctWNGV->stdrprgcbfnc
#endif
#ifdef ctFeatDYNDMPstream
#define dyndmpcbfnc   ctWNGV->sdyndmpcbfnc
#define dyndmpcbctx   ctWNGV->sdyndmpcbctx
#define dyndmpcbopt   ctWNGV->sdyndmpopts
#define dyndmpcbsiz   ctWNGV->sdyndmpcbsiz
#endif
#ifdef ctFeatSET_ALIGN
#define appalign      ctWNGV->sappalign
#endif
#define sequfl        ctWNGV->ssequfl
#define seqcnt        ctWNGV->sseqcnt
#define chkcmprec     ctWNGV->schkcmprec
#define skpimglen     ctWNGV->sskpimglen
#define cmprecbuf     ctWNGV->scmprecbuf
#define cmprecsiz     ctWNGV->scmprecsiz
#define ctpvrepstt    ctWNGV->spvrepstt
#define reploptions   ctWNGV->sreploptions
#define connoptions   ctWNGV->sconnoptions
#define usrFailoverUniqueID ctWNGV->sfailoverUniqueID

#define ctfilcremode  ctWNGV->sctfilcremode
#define rblhnum	      ctWNGV->srblhnum
#define rblrawno      ctWNGV->srblrawno
#define prmidxcnt     ctWNGV->sprmidxcnt
#define xtdopnmod     ctWNGV->sxtdopnmod
#define cursuphstno   ctWNGV->scursuphstno
#define ctMEMFILEmaxbins ctWNGV->sctMEMFILEmaxbins
#define pusrstate     ctWNGV->spusrstate
#define trnovrflwthr  ctWNGV->strnovrflwthr
#define ctseclgn      ctWNGV->sctseclgn
#define usr_cmprec_type	ctWNGV->susr_cmprec_type
#define usr_cmprec_vrsn	ctWNGV->susr_cmprec_vrsn
#define usr_cmprec_plen	ctWNGV->susr_cmprec_plen
#define usr_cmprec_dll	ctWNGV->susr_cmprec_dll
#define usr_cmprec_allc	ctWNGV->susr_cmprec_allc
#define usr_cmprec_parm	ctWNGV->susr_cmprec_parm
#define ctzlib1		ctWNGV->sctzlib1
#define ctzlib_avail	ctWNGV->sctzlib_avail
#define ctzlib_errmsg	ctWNGV->sctzlib_errmsg
#define ctssl_avail	ctWNGV->sctssl_avail
#define ctssl_errmsg	ctWNGV->sctssl_errmsg
#define ctcoaltran	ctWNGV->sctcoaltran
#define ctsslinf	ctWNGV->sctsslinf
#define crepart_host	ctWNGV->screpart_host
#define rtuserlibname	ctWNGV->srtuserlibname
#define kbufrec		ctWNGV->skbufrec
#define kbufrecsiz	ctWNGV->skbufrecsiz
#define ctdbSessionHandle ctWNGV->sctdbSessionHandle
#define naddmbr		ctWNGV->snaddmbr
#define tranidx96cont   ctWNGV->stranidx96cont
#define delstkcmtsec    ctWNGV->sdelstkcmtsec
#define precmetadata	ctWNGV->sprecmetadata
#define tmpdirdatno	ctWNGV->stmpdirdatno
#define intblkpgs	ctWNGV->sintblkpgs
#define atotrncre	ctWNGV->satotrncre
#define ctnontranfsflushoff ctWNGV->sctnontranfsflushoff
#define puksegdef	ctWNGV->spuksegdef
#define nuksegdef	ctWNGV->snuksegdef
#define rtgdrvflavor	ctWNGV->srtgdrvflavor
#define ctsAdvLog	ctWNGV->sAdvLog
#define pkcRLEctxCmp	ctWNGV->spkcRLEctxCmp
#define pkcRLEctxExp	ctWNGV->spkcRLEctxExp
#define kcRLEfnc	ctWNGV->skcRLEfnc
#define CTU_transactionId ctWNGV->transactionId
#define CTU_itim_err_context ctWNGV->itim_err_context
#define CTU_truncateForcedErrorLocation ctWNGV->truncateForcedErrorLocation
#define CTU_truncateExitOnForcedError ctWNGV->truncateExitOnForcedError
#define ctCheckFileNameValidity ctWNGV->checkFileNameValidity

#ifdef __cplusplus
extern "C" {
#endif

/**************************/
#ifdef ctCLIENT
#ifdef ctPortNUMEGA_TR
/* MDS change */
#ifdef FPUTFGET
#ifdef __BORLANDC__
COUNT ctEXPORT FAR PASCAL PurgeNext (int action_code);
#else
COUNT ctDECL PurgeNext (int action_code);
#endif
#else
#define PurgeNext(code) TRUE;
#endif
#ifdef WIN32
#ifdef __BORLANDC__
int ctEXPORT FAR PASCAL ctLock (int handle, unsigned long node, unsigned long len);
int ctEXPORT FAR PASCAL ctUnlock (int handle, unsigned long node, unsigned long len);
#else
int ctDECL ctLock (int handle, unsigned long node, unsigned long len);
int ctDECL ctUnlock (int handle, unsigned long node, unsigned long len);
#endif
#endif
#endif /* ctPortNUMEGA_TR */
#endif /* ctCLIENT */
/**************************/

ctCONV pCTGVAR  ctDECL GetCtreeGV( void );
ctCONV void     ctDECL SetCtreeGV( pCTGVAR );
ctCONV pCTGVAR  ctDECL InitCtreeGV( void );
ctCONV VOID     ctDECL FreeCtreeGV( pCTGVAR lpGV );
#ifdef ctPortWINDOWSMSDOS
ctCONV BOOL     ctDECL ViewCtreeError( HWND hWnd );
#endif

#ifdef __cplusplus
}
#endif

EXTERN pULONG	 pULI;

#else /* ~ctNOGLOBALS */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ctFeatSRVR_STRUCT

/*
** Declare the global variables as fields in a global structure. The macro
** EXTSTR is defined to an empty string.
*/
#define EXTSTR
EXTERN struct {

#else

/*
** Declare the global variables as individual global variables. The macro
** EXTSTR is defined to the value of EXTERN.
*/
#define EXTSTR EXTERN

#endif

#ifndef ctFeatSNAPSHOT
#ifdef MUSTFRCE
EXTERN ULONG	ctITIMlimit;
#ifdef ctBEHAV_ITIM_DEFER
EXTERN ULONG	ctITIMdefer;
#endif
#endif
#endif

EXTSTR pULONG	 pULI;
#ifdef CTBOUND
EXTSTR pVOID		commCmds[MAXCOMMP];
#else
EXTSTR pCommFuncPtrs	commCmds[MAXCOMMP];
#endif
EXTSTR pVOID		commGbls[MAXCOMMP];

#ifdef ctSUCTRAN
EXTSTR NINT	redolist_tot;
EXTSTR NINT	redolist_cur;
EXTSTR pTRNSTORE
		redolist_ptr;
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
EXTSTR ppCMPRECRES
		cmprec_ptr;
EXTSTR NINT	cmprec_tot;
EXTSTR NINT	cmprec_cur;
#endif
#ifdef ctFeatFILELISTmulti
EXTSTR NINT	dedlst_tot[NUMBER_OF_FILE_LISTS];
EXTSTR NINT	dedlst_cur[NUMBER_OF_FILE_LISTS];
EXTSTR NINT	dedlst_avl[NUMBER_OF_FILE_LISTS];
EXTSTR pDEDLST	dedlst_ptr[NUMBER_OF_FILE_LISTS];
#else
EXTSTR NINT	dedlst_tot;
EXTSTR NINT	dedlst_cur;
EXTSTR NINT	dedlst_avl;
EXTSTR pDEDLST	dedlst_ptr;
#endif
EXTSTR NINT	ksgcurs;
EXTSTR NINT	ksgtots;
EXTSTR pKSEGLST	ksglsts;
EXTSTR UINT	align_override;
#ifdef ctFeatRTG_API
EXTSTR   pRTGMSGCBFNC	rtgmsgcbfnc; 	/* RTG message callback function */
EXTSTR   pVOID	        rtgmsgcbusrctx; /* RTG message callback user context ptr */
#endif
#ifdef ctFeatSET_ALIGN
EXTSTR TEXT	sappalign;
#endif

#ifdef ctCLIENT
EXTERN pTEXT	ctusrbuf;
EXTERN pLQMSG	ctlqmsg;
EXTERN pLOCLFILE hlocl;
EXTERN pLOCLAUX  hauxl;
EXTERN pltICON	 cthicon[ctCONBINS];
EXTERN pVOID	ctcidxStk;
EXTERN NINT	cthugflg;
EXTERN NINT	ctreqsiz;
EXTERN NINT	ctrspsiz;
EXTERN NINT	ctinpoff;
EXTERN NINT	ctoutoff;
EXTERN VRLEN	ctusrlen;
EXTERN VRLEN	ctusrpos;
EXTERN VRLEN	ctsrvlen;
EXTERN UTEXT	ctsflvr[8];
EXTERN TEXT	ctnodnam[IDZ];
EXTERN NINT	ct_lq;
EXTERN NINT	ctautotfrm;
EXTERN NINT	ctmaxparm;
EXTERN NINT	ctmaxdatkey;
EXTERN NINT	ctisam_flg;
EXTERN NINT	ct_autopos_clr;
EXTERN NINT	ctsrvopt;
EXTERN NINT	ctspclogon;
EXTERN COUNT	ctsrvver;
EXTERN ULONG	ctsrbytatr;	/* Server attributes			*/

#ifdef ctCMPLOG
EXTERN NINT	logcmpcnt;	/* usage counter			*/
EXTERN VRLEN	logcmplen;	/* log compression buffer length	*/
EXTERN pTEXT	logcmpbuf;	/* ptr to log compression buffer	*/
#endif
EXTERN ULONG	 ctnusers;	/* number of users			*/
EXTERN LONG	 ctdivs;
EXTERN LONG	 ctops;		/* set operation state bit mask		*/
EXTERN LONG	 ctstate;	/* internal state bit mask		*/
EXTERN LONG	 ctstat2;	/* internal state bit mask 2		*/
EXTERN LONG	 ctstat3;	/* internal state bit mask 3		*/
EXTERN LONG	 ctstat4;	/* internal state bit mask 4		*/
EXTERN LONG	 ctstat5;	/* internal state bit mask 5		*/
EXTERN LONG	 ctstat6;	/* internal state bit mask 6		*/
/* ctSIBLING_CTSTATE - Add new state variable here */
EXTERN VRLEN	 ctxvlen;	/* vlen combined op max buffer length	*/
EXTERN NINT	 ctstatg;	/* keyseg distinct count indicator	*/
EXTERN NINT	 ctcidxStkPtr;
EXTERN NINT	 ctcidxCurCmd;
#ifdef ctFeatUDF_EXPR
EXTERN pVOID udflist;
EXTERN NINT  isexpreval;
#endif
EXTERN NINT	 cthshift;	/* huge shift				*/
EXTERN NINT	 ctrunfil;
EXTERN NINT	 ctrcvfil;
EXTERN NINT	 ct_adfil;
EXTERN NINT	 frschgset;
EXTERN NINT	 curchgset;
EXTERN NINT	 frschgbat;
EXTERN NINT	 curchgbat;

EXTERN COUNT uerr_cod;		/* user error cod */
EXTERN COUNT sysiocod;		/* system error cod */
EXTERN COUNT isam_err;
EXTERN COUNT isam_fil;
/* Define macros that can be used to get and set the c-tree error code values,
even if the error code macros get redefined (by ctreep.h for example). */
#define ct_get_uerr_cod( )	(uerr_cod)
#define ct_set_uerr_cod(e)	(uerr_cod = (e), 0)
#define ct_get_sysiocod( )	(sysiocod)
#define ct_set_sysiocod(e)	(sysiocod = (e), 0)
#define ct_get_isam_err( )	(isam_err)
#define ct_set_isam_err(e)	(isam_err = (e), 0)
#define ct_get_isam_fil( )	(isam_fil)
#define ct_set_isam_fil(e)	(isam_fil = (e), 0)

EXTERN COUNT cndxerr;		/* conditional index error cod */
EXTERN SYSNO ct_mxfil;		/* maximum files specified in intree. 	*/
EXTERN COUNT ctusrprf;		/* user profile word */
#ifdef RTREE
EXTERN SYSNO	srtknm,srtdat,tmpdat;
#endif
EXTERN UTEXT 			ct_uflvr;
EXTERN UTEXT 			ct_ualgn;
EXTERN UTEXT			ct_upntr;

#else /* ~ctCLIENT */

EXTSTR LSTANC	ctlist[NUMCTLIST];

#ifdef ctMXLOGS

EXTERN pTEXT	ctlogset_pth[ctMXLOGS];	/* logset paths			*/
EXTERN LONG 	ctlogset;		/* default log channel		*/
EXTERN NINT	ctlogset_act;		/* active number of log sets	*/

EXTERN struct lsgv {
	LONG8	ctsync_logfil_mx;
	LONG8	cmtblkseq_mx;
	LONG8	ctwlgops_mx;
	LONG8	ctwlgbyt_mx;
	LONG8	ctrlgops_mx;
	LONG8	ctrlgbyt_mx;
	LONG8	ctxlgops_mx;
	LONG8	ctxlgbyt_mx;
	LONG8	ct_trbeg_mx;
	LONG8	ct_trend_mx;
	LONG8	ct_trabt_mx;
	LONG8	ct_trfls_mx;

#ifdef ctFeatSNAPSHOT
	LONG8	ctchkpnttim_mx;
	LONG8	ctchkpnt_mx[8];
	LONG8	ctchkpntsiz_mx;
	LONG8	ctcmtdlytry_mx;
	LONG8	ctcmtdlycnt_mx;
	LONG8	ctcmtdlycoh_mx;
	LONG8	ctcmtcohmax_mx;
	LONG8	ctcmtdlyclr_mx;
	LONG8	ctcmtlopclr_mx;
	LONG8	ctcmtdlyfls_mx;
	LONG8	ctcmtlopfls_mx;
	LONG8	ctcmtdlydfr_mx;
	ULONG	ctcmtlopmax_mx;
	ULONG	ctcmtmaxadp_mx;
	LONG8	ctcmtavgadp_mx;
	LONG8	ctcmtdlyfls2_mx;
	LONG8	ctcmtlopfls2_mx;
	LONG8	ctcmtdlynot_mx;
	LONG8	ctcmtavgdfr_mx;
	LONG8	ctcmtmaxdfr_mx;
	LONG8	ctcmtfls_mx;
	LONG8	ctbegfls_mx;
	LONG8	ctidxfls_mx;
	LONG8	ctupdfls_mx;
	LONG8	ctlogfls_mx;
	LONG8	ctlogtim_mx;
	LONG8	ctchkbufwrt_mx;	/* checkpoint index buffer writes	*/
	LONG8	ctchkchewrt_mx;	/* checkpoint data cache writes		*/
	LONG8	ctrepfls_mx;	/* replication log flush rqst		*/
	LONG8	ct_wrtcmp_mx;	/* calls to ctwrtlog			*/
	LONG8	ct_no_cmp_mx;	/* ctwrtlog below compression threshold	*/
	LONG8	ct_tp_cmp_mx;	/* trantyp not compressed (DIFIMAGE)	*/
	LONG8	ct_rj_cmp_mx;	/* ctwrtlg compression not effective	*/
	LONG8	ct_bytcmp_mx;	/* total bytes saved by log compression	*/
#endif /* ctFeatSNAPSHOT */

	pDATBUF	ctcomdat_mx;
	LONG	ct_cmdat_mx;	/* pending data tran count	*/

	pTREBUF	ctcomnod_mx;
	LONG	ct_cmnod_mx;	/* pending node tran count	*/

#ifdef ctFeatPRESYNC_TRNLST
	LONG	ct_cmdat2_mx;	/* auxiliary data tran count	*/
	LONG	ct_cmnod2_mx;	/* auxiliary node tran count	*/
	LONG	ct_cmdatp_mx;	/* prelist data tran count	*/
	LONG	ct_cmnodp_mx;	/* prelist node tran count	*/
	pCOMLST	ct_cmdat2_ptr_mx;
	pCOMLST	ct_cmnod2_ptr_mx;
	pTEXT	ct_cmnod2_pre_mx;
	pTEXT	ct_cmdat2_pre_mx;
	NINT	ct_cmflg2_mx;
	NINT	ct_cmdat2_flg_mx;
	NINT	ct_cmnod2_flg_mx;
#endif

	pTREBUF	ctuptnod_mx;
	LONG	ct_nutcnt_mx;

	pDATBUF	ctuptdat_mx;
	LONG	ct_dutcnt_mx;

	NINT	tranac_cnt_mx;	/* number of concurrent beg/end */
	UINT	ctchktran_mx;	/* idle chkpnt activity test	*/
	NINT	ct_chktrd_mx;	/* thread id of checkpoint thread*/
	NINT	chkwait_mx;

	NINT	ctfilcre_mx;	/* flag for create since checkpoint	*/
	NINT	ct_chkflg_mx;	/* checkpoint in progress flag */
	UINT	ctchkpstt_mx;	/* checkpoint thread status */

	ULONG	ct_lstchktim_mx;/* last checkpoint time stamp	*/
	LONG	ct_abseq_mx;	/* abort list sequence number	*/
	LONG	ct_abnod_mx;	/* abort list node count	*/
	NINT	ct_lfltrd_mx;	/* thread id of cmtdly blk thread*/
	NINT	ctlflwait_mx;

	LONG	ct_numvi_mx;	/* vulnerable index update count*/
	LONG	prv_logser_mx;	/* previous checkpoint log#	*/
	LONG	prv_chkpos_mx;	/* previous checkpoint pos	*/
	LONG	prv_prvpos_mx;	/* previous checkpoint back link*/

	NINT	ct_cq_mx;	/* checkpoint task logical Q handle	*/
	NINT	ctqchkpRunning_mx;
	NINT	ctfstr_mx;	/* oldest start file #		*/
	NINT	ctnewlogs_mx;	/* starting without logs	*/

	LONG	ct_logchn_mx;	/* log chunk size */
	LONG	ct_logpts_mx;	/* chkpts per log */
	LONG	ct_loglmt_mx;	/* log size limit */
	LONG	ct_logspc_mx;	/* aggregate log space */
	LONG	ct_logrec_mx;	/* record length limit */
	LONG	ct_logtrg_mx;	/* resize log trigger: ~= 1.1 * ct_logrec */
	LONG	ct_logprg_mx;	/* log purge count */
	LONG	ct_savprg_mx;
#ifdef ctBEHAV_DLYLOGPRG
	LONG	ct_begprg_mx;	/* first log to purge on decrease */
	LONG	ct_numprg_mx;	/* number of logs to purge on decrease */
	LONG	ct_newprg_mx;	/* number of logs after decrease */
	LONG	ct_lstsav_mx;	/* last check point when decrease detetcted */
#endif
	LONG	ct_lowtrn2_mx;
	ULONG	ct_lowtrn_mx;
	LONG	ct_lnmlog_mx;	/*  low numbered log */
	LONG	ct_hnmlog_mx;	/* high numbered log */
	LONG	ct_oldlog_mx;	/* lowest numbered, possibly left-over, log # */
	LONG	ct_replog_mx;	/* lowest numbered log required for repl      */
	NINT	logtrn_tot_mx;
	NINT	logtrn_cur_mx;
	LONG	logtrn_seq_mx;
	pLOGTRNLST
		logtrn_lst_mx;
	NINT	redolist_tot_mx;
	NINT	redolist_cur_mx;
	pTRNSTORE
		redolist_ptr_mx;

	VRLEN	logrem_mx;	/* bytes remaining in log buffer	*/
	pTEXT	logptr_mx;	/* pointer to current offset in buffer  */
	LONG	logbyt_mx;	/* absolute byte position of beginning
				** of log buffer
				*/
	LONG	lowpnt_mx;	/* oldest active absolute byte position
				** on buffer page boundary in log buffer
				*/
	LONG	lstpnt_mx;	/* last abs byte position of actual content
				** written to log
				*/
	LONG	lstsuc_mx;	/* absolute byte position of beginning of
				** last SUCTRAN entry in log
				*/
	LONG	hghcmt_mx;	/* furthest point for pending commits   */
	LONG	hghlog_mx;
	LONG	cttopcmt_mx;	/* furthest point flushed */
	LONG	cttoplog_mx;
	LONG	ctbegcmt_mx;	/* begin tran high water mark */
	LONG	ctbeglog_mx;

	NINT	curlfwchn_mx;	/* current lfw channel: 0 to (ctMXLFW - 1) */
	UINT	commit_seq_mx;
	NINT	commit_cnt_mx;	/* number of pending flushes	*/
	NINT	ct_actrns_mx;	/* # active transactions */
	NINT	commit_prv_mx;	/* number of pending clears	*/

	LONG	ctchkplog_mx;	/* checkpoint log indicator  */
	ULONG	endcnt_mx;	/* end log count	     */

	LONG	ctcpcnt_mx;	/* check point count */

	LONG	ctcpchk_mx;	/* check point count less delta */
	LONG	ctelcnt_mx;	/* check point count at last ENDLOG */

	LONG	ct_lstlog_mx;	/* last checkpoint log#	*/
	LONG	ct_lstpos_mx;	/* last checkpoint log position*/
	pTEXT	ctlgbf_mx;	/* transaction log buffer ptr */

	ppCOMLST
		cttrnanc_mx;	/* vulnerable tran hash list anchor	*/

	NINT	ct_lerflg_mx;	/* ctwrtlog error flag */
	} ctstatemx[ctMXLOGS];

#define xctsync_logfil(ls)	ctstatemx[ls].ctsync_logfil_mx
#define xcmtblkseq(ls)	ctstatemx[ls].cmtblkseq_mx
#define xctwlgops(ls)	ctstatemx[ls].ctwlgops_mx
#define xctwlgbyt(ls)	ctstatemx[ls].ctwlgbyt_mx
#define xctrlgops(ls)	ctstatemx[ls].ctrlgops_mx
#define xctrlgbyt(ls)	ctstatemx[ls].ctrlgbyt_mx
#define xctxlgops(ls)	ctstatemx[ls].ctxlgops_mx
#define xctxlgbyt(ls)	ctstatemx[ls].ctxlgbyt_mx
#define xct_trbeg(ls)	ctstatemx[ls].ct_trbeg_mx
#define xct_trend(ls)	ctstatemx[ls].ct_trend_mx
#define xct_trabt(ls)	ctstatemx[ls].ct_trabt_mx
#define xct_trfls(ls)	ctstatemx[ls].ct_trfls_mx

#ifdef ctFeatSNAPSHOT
#define xctchkpnttim(ls)	ctstatemx[ls].ctchkpnttim_mx
#define xctchkpnt(ls)		ctstatemx[ls].ctchkpnt_mx
#define xctchkpntsiz(ls)	ctstatemx[ls].ctchkpntsiz_mx
#define xctcmtdlytry(ls)	ctstatemx[ls].ctcmtdlytry_mx
#define xctcmtdlycnt(ls)	ctstatemx[ls].ctcmtdlycnt_mx
#define xctcmtdlycoh(ls)	ctstatemx[ls].ctcmtdlycoh_mx
#define xctcmtcohmax(ls)	ctstatemx[ls].ctcmtcohmax_mx
#define xctcmtdlyclr(ls)	ctstatemx[ls].ctcmtdlyclr_mx
#define xctcmtlopclr(ls)	ctstatemx[ls].ctcmtlopclr_mx
#define xctcmtdlyfls(ls)	ctstatemx[ls].ctcmtdlyfls_mx
#define xctcmtlopfls(ls)	ctstatemx[ls].ctcmtlopfls_mx
#define xctcmtdlydfr(ls)	ctstatemx[ls].ctcmtdlydfr_mx
#define xctcmtlopmax(ls)	ctstatemx[ls].ctcmtlopmax_mx
#define xctcmtavgdfr(ls)	ctstatemx[ls].ctcmtavgdfr_mx
#define xctcmtmaxadp(ls)	ctstatemx[ls].ctcmtmaxadp_mx
#define xctcmtavgadp(ls)	ctstatemx[ls].ctcmtavgadp_mx
#define xctcmtmaxdfr(ls)	ctstatemx[ls].ctcmtmaxdfr_mx
#define xctcmtdlyfls2(ls)	ctstatemx[ls].ctcmtdlyfls2_mx
#define xctcmtlopfls2(ls)	ctstatemx[ls].ctcmtlopfls2_mx
#define xctcmtdlynot(ls)	ctstatemx[ls].ctcmtdlynot_mx
#define xctcmtfls(ls)		ctstatemx[ls].ctcmtfls_mx
#define xctbegfls(ls)		ctstatemx[ls].ctbegfls_mx
#define xctidxfls(ls)		ctstatemx[ls].ctidxfls_mx
#define xctupdfls(ls)		ctstatemx[ls].ctupdfls_mx
#define xctlogfls(ls)		ctstatemx[ls].ctlogfls_mx
#define xctlogtim(ls)		ctstatemx[ls].ctlogtim_mx
#define xctchkbufwrt(ls)	ctstatemx[ls].ctchkbufwrt_mx
#define xctchkchewrt(ls)	ctstatemx[ls].ctchkchewrt_mx
#define xctrepfls(ls)		ctstatemx[ls].ctrepfls_mx
#define xct_wrtcmp(ls)		ctstatemx[ls].ct_wrtcmp_mx
#define xct_no_cmp(ls)		ctstatemx[ls].ct_no_cmp_mx
#define xct_tp_cmp(ls)		ctstatemx[ls].ct_tp_cmp_mx
#define xct_rj_cmp(ls)		ctstatemx[ls].ct_rj_cmp_mx
#define xct_bytcmp(ls)		ctstatemx[ls].ct_bytcmp_mx
#endif /* ctFeatSNAPSHOT */

#define	xctcomdat(ls)	ctstatemx[ls].ctcomdat_mx
#define	xct_cmdat(ls)	ctstatemx[ls].ct_cmdat_mx
#define	xctcomnod(ls)	ctstatemx[ls].ctcomnod_mx
#define	xct_cmnod(ls)	ctstatemx[ls].ct_cmnod_mx
#ifdef ctFeatPRESYNC_TRNLST
#define	xct_cmdat2(ls)	ctstatemx[ls].ct_cmdat2_mx
#define	xct_cmnod2(ls)	ctstatemx[ls].ct_cmnod2_mx
#define	xct_cmdatp(ls)	ctstatemx[ls].ct_cmdatp_mx
#define	xct_cmnodp(ls)	ctstatemx[ls].ct_cmnodp_mx
#define	xct_cmdat2_ptr(ls)	ctstatemx[ls].ct_cmdat2_ptr_mx
#define	xct_cmdat2_pre(ls)	ctstatemx[ls].ct_cmdat2_pre_mx
#define	xct_cmnod2_ptr(ls)	ctstatemx[ls].ct_cmnod2_ptr_mx
#define	xct_cmnod2_pre(ls)	ctstatemx[ls].ct_cmnod2_pre_mx
#define	xct_cmflg2(ls)		ctstatemx[ls].ct_cmflg2_mx
#define	xct_cmdat2_flg(ls)	ctstatemx[ls].ct_cmdat2_flg_mx
#define	xct_cmnod2_flg(ls)	ctstatemx[ls].ct_cmnod2_flg_mx
#endif
#define	xctuptnod(ls)	ctstatemx[ls].ctuptnod_mx
#define	xct_nutcnt(ls)	ctstatemx[ls].ct_nutcnt_mx
#define	xctuptdat(ls)	ctstatemx[ls].ctuptdat_mx
#define	xct_dutcnt(ls)	ctstatemx[ls].ct_dutcnt_mx
#define	xtranac_cnt(ls)	ctstatemx[ls].tranac_cnt_mx
#define	xctchktran(ls)	ctstatemx[ls].ctchktran_mx
#define	xct_chktrd(ls)	ctstatemx[ls].ct_chktrd_mx
#define	xchkwait(ls)	ctstatemx[ls].chkwait_mx
#define	xct_lfltrd(ls)	ctstatemx[ls].ct_lfltrd_mx
#define	xctlflwait(ls)	ctstatemx[ls].ctlflwait_mx
#define	xctfilcre(ls)	ctstatemx[ls].ctfilcre_mx
#define	xct_chkflg(ls)	ctstatemx[ls].ct_chkflg_mx
#define	xctchkpstt(ls)	ctstatemx[ls].ctchkpstt_mx
#define	xct_abseq(ls)	ctstatemx[ls].ct_abseq_mx
#define	xct_abnod(ls)	ctstatemx[ls].ct_abnod_mx
#define	xct_numvi(ls)	ctstatemx[ls].ct_numvi_mx
#define	xprv_logser(ls)	ctstatemx[ls].prv_logser_mx
#define	xprv_chkpos(ls)	ctstatemx[ls].prv_chkpos_mx
#define	xprv_prvpos(ls)	ctstatemx[ls].prv_prvpos_mx
#define	xct_cq(ls)	ctstatemx[ls].ct_cq_mx
#define	xct_lstchktim(ls)	ctstatemx[ls].ct_lstchktim_mx
#define	xctqchkpRunning(ls)	ctstatemx[ls].ctqchkpRunning_mx
#define	xctfstr(ls)	ctstatemx[ls].ctfstr_mx
#define	xctnewlogs(ls)	ctstatemx[ls].ctnewlogs_mx
#define	xct_logchn(ls)	ctstatemx[ls].ct_logchn_mx
#define	xct_logpts(ls)	ctstatemx[ls].ct_logpts_mx
#define	xct_loglmt(ls)	ctstatemx[ls].ct_loglmt_mx
#define	xct_logspc(ls)	ctstatemx[ls].ct_logspc_mx
#define	xct_logrec(ls)	ctstatemx[ls].ct_logrec_mx
#define	xct_logtrg(ls)	ctstatemx[ls].ct_logtrg_mx
#define	xct_logprg(ls)	ctstatemx[ls].ct_logprg_mx
#define	xct_savprg(ls)	ctstatemx[ls].ct_savprg_mx
#ifdef ctBEHAV_DLYLOGPRG
#define	xct_begprg(ls)	ctstatemx[ls].ct_begprg_mx
#define	xct_numprg(ls)	ctstatemx[ls].ct_numprg_mx
#define	xct_newprg(ls)	ctstatemx[ls].ct_newprg_mx
#define	xct_lstsav(ls)	ctstatemx[ls].ct_lstsav_mx
#endif
#define	xct_lowtrn2(ls)	ctstatemx[ls].ct_lowtrn2_mx
#define	xct_lowtrn(ls)	ctstatemx[ls].ct_lowtrn_mx
#define	xct_lnmlog(ls)	ctstatemx[ls].ct_lnmlog_mx
#define	xct_hnmlog(ls)	ctstatemx[ls].ct_hnmlog_mx
#define	xct_oldlog(ls)	ctstatemx[ls].ct_oldlog_mx
#define	xct_replog(ls)	ctstatemx[ls].ct_replog_mx
#define	xlogtrn_tot(ls)	ctstatemx[ls].logtrn_tot_mx
#define	xlogtrn_cur(ls)	ctstatemx[ls].logtrn_cur_mx
#define	xlogtrn_seq(ls)	ctstatemx[ls].logtrn_seq_mx
#define	xlogtrn_lst(ls)	ctstatemx[ls].logtrn_lst_mx
#define	xredolist_tot(ls)	ctstatemx[ls].redolist_tot_mx
#define	xredolist_cur(ls)	ctstatemx[ls].redolist_cur_mx
#define	xredolist_ptr(ls)	ctstatemx[ls].redolist_ptr_mx
#define	xlogrem(ls)	ctstatemx[ls].logrem_mx
#define	xlogptr(ls)	ctstatemx[ls].logptr_mx
#define	xlogbyt(ls)	ctstatemx[ls].logbyt_mx
#define	xlowpnt(ls)	ctstatemx[ls].lowpnt_mx
#define	xlstpnt(ls)	ctstatemx[ls].lstpnt_mx
#define	xlstsuc(ls)	ctstatemx[ls].lstsuc_mx
#define	xhghcmt(ls)	ctstatemx[ls].hghcmt_mx
#define	xhghlog(ls)	ctstatemx[ls].hghlog_mx
#define	xcttopcmt(ls)	ctstatemx[ls].cttopcmt_mx
#define	xcttoplog(ls)	ctstatemx[ls].cttoplog_mx
#define	xctbegcmt(ls)	ctstatemx[ls].ctbegcmt_mx
#define	xctbeglog(ls)	ctstatemx[ls].ctbeglog_mx
#define	xcurlfwchn(ls)	ctstatemx[ls].curlfwchn_mx
#define	xcommit_seq(ls)	ctstatemx[ls].commit_seq_mx
#define	xcommit_cnt(ls)	ctstatemx[ls].commit_cnt_mx
#define	xct_actrns(ls)	ctstatemx[ls].ct_actrns_mx
#define	xcommit_prv(ls)	ctstatemx[ls].commit_prv_mx
#define	xctchkplog(ls)	ctstatemx[ls].ctchkplog_mx
#define	xendcnt(ls)	ctstatemx[ls].endcnt_mx
#define	xctcpcnt(ls)	ctstatemx[ls].ctcpcnt_mx
#define	xctcpchk(ls)	ctstatemx[ls].ctcpchk_mx
#define	xctelcnt(ls)	ctstatemx[ls].ctelcnt_mx
#define	xct_lstlog(ls)	ctstatemx[ls].ct_lstlog_mx
#define	xct_lstpos(ls)	ctstatemx[ls].ct_lstpos_mx
#define	xctlgbf(ls)	ctstatemx[ls].ctlgbf_mx
#define	xcttrnanc(ls)	ctstatemx[ls].cttrnanc_mx
#define	xct_lerflg(ls)	ctstatemx[ls].ct_lerflg_mx

#endif /* ctMXLOGS */

#ifndef DllExtImp
#define DllExtImp
#endif

#if defined(ctFeatNoIdxPndgList) || defined(ctFeatNoDatPndgList)

EXTERN	ppULONG8	nopndg_stats;
EXTERN	pTEXT		nopndg_statsb;

#if defined(NopndgStatsInline) && defined(NopndgStatsIgnore)
#error At most one of NopndgStatsInline and NopndgStatsIgnore may be defined
#endif

#ifdef NopndgStatsInline
/*
** Inline updates
*/
#define incrementNopndg(stat)		(*nopndg_stats[stat])++
#define incrementNopndg32(stat)		(*((pULONG)nopndg_stats[stat]))++
#define percentNopndg32(stat1,stat2)	((*((pULONG)nopndg_stats[stat1]) *  \
					100) / *((pULONG)nopndg_stats[stat2]))
#else
#ifdef NopndgStatsIgnore
/*
** Ignore stats
*/
#define incrementNopndg(stat)		/* incrementNopndg(stat) */
#define incrementNopndg32(stat)		/* incrementNopndg32(stat) */
#define percentNopndg32(stat1,stat2)	/* percentNopndg32(stat1,stat2) */
#else
/*
** Default: function calls that do nothing unless
**
**		DIAGNOSTICS STATS_NOPNDGLIST
**
** is in configuration file.
*/
#define incrementNopndg(stat)		DiagnosticIncrementNopndg(stat)
#endif
#endif

#define	tstCmtc		0	/* cache hash mtc but PENDING - debug	*/
#define	cacdum_get	1	/* cache hash mtc but DUMMY   - debug	*/
#define	cacdum		2	/* cache hash mtc DUMMY retries		*/
#define	cacmtc_get	3	/* cache hash mtc NO (after datsem) dbg	*/
#define	cacmtc		4	/* cache hash mtc NO retries		*/
#define	cntemp		5	/* no page on empty list		*/
#define	empstt		6	/* could not go EMPTY to PENDING cache	*/
#define	tstBmtc		7	/* buffer hash mtc but pending - debug	*/
#define	bufdum_get	8	/* buffer hash mtc but DUMMY   - debug	*/
#define	bufdum		9	/* buffer hash mtc DUMMY retries	*/
#define	bufmtc_get	10	/* buffer hash mtc NO (after idxsem) dbg*/
#define	bufmtc		11	/* buffer hash mtc NO retries		*/
#define	buflok		12	/* buffer hash read lock to write lock	*/
#define cacscn_nak	13	/* crawl naked collision  scan page	*/
#define cacscn		14	/* crawl       collision  scan page	*/
#define cacemp_nak	15	/* crawl naked collision empty page	*/
#define cacemp		16	/* crawl       collision empty page	*/
#define cacclr		17	/* crawl       collision clear page	*/
#define bufreqs_red	18	/* index hash bin searches w/ redlok 	*/
#define bufhits_red	19	/* index hash bin search hits w/ redlok	*/
#define cacreqs_red	20	/*  data hash bin searches w/ redlok 	*/
#define cachits_red	21	/*  data hash bin search hits w/ redlok	*/
#define	caclok		22	/* cache hash read lock to write lock	*/
#define bufredlok	23	/* idxsem reader locks in ctgetnod81	*/
#define bufleaf		24	/* idxsem reader locks on leaf node	*/

#define 		nopndg_statsMAX	32

#endif

#ifdef MULTITRD

EXTSTR NINT	ctsrvthrd;	/* main ctsrvr thread handle */
#ifdef ctFeatQUIET
EXTSTR NINT	ctQTthrd;	/* thread processing ctQUIET */
EXTSTR NINT	ctQTvalidusrcnt;/* validusr() counter	     */
EXTSTR LONG	ctQTaction;	/* active quiet block codes  */
EXTSTR NINT	ctQTclnup;	/* vulnerable cleanup state  */
EXTSTR NINT	ctQTstart;	/* vulnerable startup state  */
EXTSTR NINT	ctQTthrdabn;	/* abandoned ctQTthrd	     */
EXTSTR pTEXT	ctQTlogbuf;	/* temp log buffer for logon **
				** & logoff by ctQUIET thrd  **
				** with ctQTblockLogFiles    */
#ifdef ctFeatPWDLEN
EXTSTR TEXT	ctQTpslt[PWS];	/* special logon buffer      */
EXTSTR TEXT	ctQTpslp[PWS];	/* special logon buffer pndg */
EXTSTR LONG	ctQTpatr;	/* special logon buffer      */
EXTSTR LONG	ctQTpatp;	/* special logon buffer pndg  */
#endif
#ifdef ctCAMOsdk
EXTSTR TEXT	ctQTwpus[PWZX16];/* special logon buffer      */
EXTSTR TEXT	ctQTwpnd[PWZX16];/* special logon buffer pndg */
#else
EXTSTR TEXT	ctQTwpus[PWZX];	/* special logon buffer	     */
EXTSTR TEXT	ctQTwpnd[PWZX];	/* special logon buffer pndg */
#endif
#endif
EXTSTR NINT	ctlogtmp;
EXTSTR ppVOID	ctgv_thd;
#ifdef ctFeatWIN32_TEMPLATE_COPY
EXTSTR TEXT	ctlogtmpcpyutl[MAX_NAME];
#endif

#ifdef ctBEHAV_BLM
EXTSTR pTREBUF	ctupdnod;	/* newest entry in non-tran index update list */
EXTSTR pDATBUF	ctupddat;	/* newest entry in non-tran data update list */
#ifdef ctFeatBACKGROUNDflush
EXTSTR pTREBUF	ctupdnod_tail;	/* oldest entry in non-tran index update list */
EXTSTR pDATBUF	ctupddat_tail;	/* oldest entry in non-tran data update list */
EXTSTR pTREBUF	ctuptnod_tail;	/* oldest entry in TRNLOG index update list */
EXTSTR pDATBUF	ctuptdat_tail;	/* oldest entry in TRNLOG data update list */
#endif
#ifdef ctFeatBACKGROUNDflushBKT
EXTSTR BGFLSBKT bgflsbkt[2];	/* background flush bucket state */
#endif

#ifdef ctMXLOGS
EXTERN UINT	ctXsemaD;		/* aligned mutex delta	*/
EXTERN pTEXT	ctXsemaL;		/* logsema origin	*/
#else
EXTSTR pDATBUF	ctcomdat;
EXTSTR pTREBUF	ctcomnod;
EXTSTR pTREBUF	ctuptnod;	/* newest entry in tran index update list */
EXTSTR pDATBUF	ctuptdat;	/* newest entry in tran data update list */
#endif

#endif /* ctBEHAV_BLM */

#ifdef ctBEHAV_FLUSH_NODE_MARKSorg
EXTSTR LONG	cpflscnt;	/* number of nodes requiring chkpnt flush */
#endif

EXTSTR LONG	cpucountmode;	/* logical or physical CPU count */

#ifdef ctFeatWAITFORopt
#define ctWFBITS 2 /* number of bits for each wait-for graph entry */
EXTSTR NINT	  ct_wfsize;	/* size of wait-for list for each connection */
#endif
typedef TEXT CTWF, *pCTWF, **ppCTWF;
EXTSTR ppCTWF	  ct_wf;
EXTSTR pNINT	  ct_vf;
#ifdef ctCUSTOM
EXTSTR ppVOID	  spcustmem;
EXTSTR pLONG	  scustops;
#endif
#ifdef ctBEHAV_KILL_QUIET
EXTSTR SEMAblk	  ctkillquiet;
#define	ctKQuser	-21
#endif
#ifdef DBGhash
EXTSTR SEMAmut	  dbg_hsema;
#endif

#ifdef ctFeatREPLICAT
EXTSTR SEMAmut	  ct_repmtx;
#endif
#ifdef ctFeatFILMTX
EXTSTR SEMAmut	  filmtx_mtx;
#endif

#ifdef ctCACHE_MEMORY
EXTSTR SEMAmut	  ct_usrbmtx;
EXTSTR pSEMA	  ctSsemap[ctSEMS];
EXTSTR pSEMAmut	  ctXsemap[ctSEMX];
EXTSTR pSEMAtim	  ctTsemap[ctSEMT];
EXTSTR pSEMAblk	  ctBsemap[ctSEMB];
#ifdef ctSEMW
EXTSTR pRWLOCKmut ctWsemap[ctSEMW];
#endif
EXTSTR pTEXT	  ctlsemab;
EXTSTR pTEXT	  ctSsemab;
EXTSTR pTEXT	  ctXsemab;
EXTSTR pTEXT	  ctTsemab;
EXTSTR pTEXT	  ctBsemab;
#ifdef ctSEMW
EXTSTR pTEXT	  ctWsemab;
#endif
EXTSTR pTEXT	  ct_blkb;
#ifdef ctFeatIMPERSONATEtask
EXTSTR pTEXT	  im_blkb;
#endif
#ifdef ctFeatFILEBLOCK
EXTSTR pTEXT	  fb_blkb;
#endif
#ifdef ctBEHAV_WORKsync
EXTSTR pSEMAmut	  ctpconcsema[MXU2];
EXTSTR pTEXT	  ctbconcsema;
#endif
#else
EXTSTR SEMAtim	  ctdnode_sema;
EXTSTR SEMAmut	  ctstrfil_sem;
EXTSTR SEMA	  ctmemtrk_sem;
EXTSTR pNINT	  sct_usrsi;
#endif

EXTSTR LONG	  cthugeseg;	/* huge to autoseg segment size		*/
EXTSTR LONG	  cthugemax;	/* huge to autoseg segment max		*/
EXTSTR LONG	  ctash;	/* system-wide async handle		*/
EXTSTR LONG	  ctchkidle;	/* seconds between chkpnt idle test */
EXTSTR LONG	  nodedtime;	/* node delete delay time	    */
EXTSTR LONG	  nodertime;	/* node reuse  delay time	    */
#ifdef ctFeatLOCK_MONITOR
EXTSTR LONG	  ctlokch;	/* lock check increment		*/
EXTSTR LONG	  ctlokup;	/* lock ckeck limit		*/
EXTSTR LONG	  ctlokdn;	/* lock check limit		*/
#endif
EXTSTR NINT	  presync_limit;/* threshold for pre-filesync tran list */
#ifdef ctFeatLOCK_MONITOR
EXTSTR NINT	  ctlokfl;	/* net locks == 0 control flag	*/
#endif
EXTSTR NINT	  ct_gstnot;	/* if YES, no guest logons	*/
EXTSTR NINT	  ct_blkadm;	/* YES: must be adm group, HYS adm user */
#ifdef ctMXLOGS
#else
EXTSTR UINT	  ctchktran;		/* idle chkpnt activity test	*/
EXTSTR NINT	  ctqchkpRunning;
#endif

EXTSTR NINT	  ctmaxdatkey;
EXTSTR NINT	  ctmaxkeyseg;
EXTSTR NINT	  ctmaxusrfil;
EXTSTR NINT	  ctcacheline;	/* cache-line size for multiCPU optimization */
EXTSTR NINT	  ctrunlength;	/* interval between buffer global mtx release*/
EXTSTR NINT	  ctdnodeRunning;
#ifdef ctFeatTRAN_TIMEOUT
EXTSTR NINT	  cttrntimoutRunning; /* transaction timeout thread running indicator */
#endif
#ifdef ctFeatREQUEST_TIME_MONITOR
EXTSTR NINT	  ctrqtmonRunning; /* request time monitor thread running indicator */
EXTSTR LONG	  ctrqtmonint_new; /* new request time monitor interval */
#endif
#ifdef ctFeatCPU_LIMIT
EXTSTR NINT	  ctcpulmtRunning; /* CPU limit thread running indicator */
#endif
EXTSTR NINT	  ctbroadcastRunning; /* Broadcast thread running indicator */
#ifdef ctFeatKEEPOPENclose
EXTSTR NINT	  ctKEEPOPENcloseRunning; /* KEEPOPENclose thread running indicator */
#endif
#ifdef ctDISTcounts
EXTSTR NINT	  ctDISTcountsRunning;
#endif
#ifdef ctFeatDISKFULLaction
EXTSTR NINT	  ctDISKFULLactionRunning; /* DISKFULLaction thread running indicator */
#endif
#ifdef ctFeatRECBKT
EXTSTR NINT	  ctrbktflsRunning; /* record bucket cache flush thread still running */
EXTSTR NINT	  ct_rbktflsq; 	/* record bucket cache flush logical Q handle	*/
#endif
EXTSTR NINT	  ctsyslgRunning;
EXTSTR NINT	  ct_channels;	/* duplicate IO channel factor	*/
EXTSTR NINT	  ctlog_pagesize;   /* log page size */
EXTSTR NINT	  cthr_concurrency; /* thread concurrency (multi-cpu) */
#ifdef ctPortMACOSX_COCOA
EXTSTR NINT	  ctqmsgRunning; /* Message monitor thread still running */
EXTSTR NINT	  ctqfncRunning; /* Function monitor thread still running */
#endif
/*
**		  ctworktyp not being used
EXTSTR NINT	  ctworktyp[ctWORKsize];
*/
EXTSTR NINT	  ct_mq[ctMAX_MONITOR];
EXTSTR NINT	  ct_smon[ctMAX_MONITOR];
EXTSTR UINT	  ct_trdmon[ctMAX_MONITOR];
EXTSTR SYSNO	  ctadmfiles;

#ifdef ctFeatLOCK_CACHE
EXTSTR LONG  	  ct_syspagsz;
#endif

#ifdef ctFeatREBUILD_OPT
EXTSTR ULONG	  ctmaxktouse;	/* MAX_K_TO_USE for rebuild	*/
EXTSTR NINT	  ctmaxhandles;	/* MAX_HANDLES for rebuild	*/
#endif

#ifdef ctFeatRWLOCKwindows
/* Reader/writer lock function pointers: */
EXTSTR pRWLFNC    InitRWLock;	/* Initialize reader/writer lock*/
EXTSTR pRWLFNC    AcqRWLockExc;	/* Acquire exclusive lock	*/
EXTSTR pRWLFNC    AcqRWLockShr;	/* Acquire shared lock		*/
EXTSTR pRWLFNCret TryRWLockExc;	/*     Try exclusive lock	*/
EXTSTR pRWLFNCret TryRWLockShr;	/*     Try shared lock		*/
EXTSTR pRWLFNC    RelRWLockExc;	/* Release exclusive lock	*/
EXTSTR pRWLFNC	  RelRWLockShr;	/* Release shared lock		*/
EXTSTR pRWLFNC    DestroyRWLock;/* Destroy reader/writer lock	*/
#endif

#ifndef ctFeatSNAPSHOT
EXTSTR ULONG	ct_udefer_thld;
EXTSTR ULONG	ct_udefer_64yd;
EXTSTR ULONG	ctITIMlimit;
#ifdef ctBEHAV_ITIM_DEFER
EXTSTR ULONG	ctITIMdefer;
#endif
#ifdef ctBEHAV_CMTLOK
EXTSTR ULONG	ctredcmtdfr;	/* RED_CMTLOK loop defer time (milliseconds) */
#endif
#ifdef ctFeatREQUEST_TIME_MONITOR
EXTSTR LONG	ctrqtmonint;	/* request time monitor interval */
#endif
#endif

#ifdef ctDIAGctsrvrExitCmd
EXTSTR	NINT	ctShutdownStatus;	/* Database engine shutdown code. */
EXTSTR  TEXT	ctProcessExitCmd[255];	/* PROCESS_EXIT_COMMAND option.	  */
#endif

#ifdef ctFeatIO_BLOCK_SIZE
EXTSTR  LONG	ctioblksiz;		/* IO_BLOCK_SIZE option.	  */
EXTSTR  LONG	ctioerrblksiz;		/* IO_ERROR_BLOCK_SIZE option.	  */
EXTSTR  LONG	ctioerrblkretry;	/* IO_ERROR_BLOCK_RETRY option.	  */
EXTSTR  LONG	ctioerrblksleep;	/* IO_ERROR_BLOCK_SLEEP option.	  */
#endif

EXTSTR  LONG	ctdyndmplopdfr;		/* DYNAMIC_DUMP_DEFER option.	  */
EXTSTR  LONG	ctdyndmplopdfrint;	/* DYNAMIC_DUMP_DEFER_INTERVAL option.	  */

#ifdef ctFeatTRANSFER_FILE
EXTSTR  NINT	ctxfrfil_api;		/* ENABLE_TRANSFER_FILE_API option*/
#endif

#ifdef ctFeatVSSWRITERsrv
EXTSTR  NINT	ctvsswriter;		/* VSS_WRITER option		  */
EXTSTR	TEXT	ctvsswriterQuiesceTimeoutSet; /* non-zero indicates that the VSS_WRITER_QUIESCE_TIMEOUT option is set*/
EXTSTR  NINT	ctvsswriterQuiesceTimeout; /* VSS_WRITER_QUIESCE_TIMEOUT option */
#endif

#ifdef ctFeatREPL_SRLSEG
EXTSTR	NINT	ctreplsrlAllowUnqkey;	/* REPL_SRLSEG_ALLOW_UNQKEY option*/
EXTSTR	NINT	ctreplsrlUseMaster;	/* REPL_SRLSEG_USE_MASTER option  */
EXTSTR	NINT	ctreplsrlUseSource;	/* REPL_SRLSEG_USE_SOURCE option  */
#endif

#ifdef ctFeatREPL_IDENTITY
EXTSTR	NINT	ctreplidfUseMaster;	/* REPL_IDENTITY_USE_MASTER option */
EXTSTR	NINT	ctreplidfUseSource;	/* REPL_IDENTITY_USE_SOURCE option */
#endif

#ifdef ctFeatTEMPLATE_COPY_OPT
EXTSTR	NINT	ctlogtmpcpyslp;	/* LOG_TEMPLATE_COPY_SLEEP_TIME */
EXTSTR	NINT	ctlogtmpcpypct; /* LOG_TEMPLATE_COPY_SLEEP_PCT */
#endif

EXTSTR	NINT	ctchkcfg;	/* CHECK_CONFIG keyword */
EXTSTR	NINT	did_preconfig;	/* preprocessed configuration file	*/

#ifdef ctFeatLATCH
EXTSTR  LONG	ct_latchspin;	/* spin count for latch */
EXTSTR  LONG	ct_latchsleep;	/* sleep time (in microseconds) for latch */
#endif

#ifdef ctFeatEVAL_TIMER
EXTSTR	SEMAtim	ctevalsem;	/* evaluation thread timer */
#endif

#ifdef ctFeatRECBKT
EXTSTR	pDATBUF ctdatbuf[MXU2];	/* data cache page acquired by ADDREC */
#endif

#ifdef ctFeatREPL_READ_BUFFER
EXTSTR	ULONG	ctrepredbufsiz;	/* replication log read buffer size	*/
#endif

#ifdef ctFeatSKIPaddwrk
EXTSTR  NINT	ctskpaddwrk;	/* ctaddwork/ctrmvwork take no action	*/
#endif

#ifdef ctFeatAVLISTnum
EXTSTR  LONG    ctavlistcnt;	/* number of index LRU lists		*/
#endif

#ifdef ctFeatDALISTnum
EXTSTR  LONG    ctdalistcnt;	/* number of data cache lists		*/
#endif
#ifdef ctFeatDatEmptyList
EXTSTR	UINT	useEmptyList;	/* YES / NO				*/
EXTSTR  LONG    ctdalistsiz;	/* size of data cache lists		*/
#endif
#if 0
#ifdef ctFeatNoDatPndgList
EXTSTR	ULONG	nopndg_cacstt;
EXTSTR	ULONG	nopndg_cacmtc;
#ifdef ctDBGfcqa
EXTSTR	ULONG	nopndg_tstCmtc;		/* number of cacstt==pending	*/
EXTSTR	ULONG	nopndg_cacstt_get;	/* ctgetnod calls with dummy	*/
EXTSTR	ULONG	nopndg_cacmtc_get;	/* ctgetnod calls with no match	*/
#endif
#endif
#ifdef ctFeatDatEmptyList
EXTSTR	ULONG	nopndg_cntemp;
EXTSTR	ULONG	nopndg_empstt;
#endif
#ifdef ctFeatNoIdxPndgList
EXTSTR	ULONG	nopndg_bufstt;		/* retries dummy buffer pages	*/
EXTSTR	ULONG	nopndg_bufmtc;		/* retries buffer no match	*/
EXTSTR	ULONG	nopndg_buflok;		/* retries buffer chg bin lok	*/
#ifdef ctDBGfcqa
EXTSTR	ULONG	nopndg_tstBmtc;		/* number of bufstt==pending	*/
EXTSTR	ULONG	nopndg_bufstt_get;	/* ctgetnod calls with dummy	*/
EXTSTR	ULONG	nopndg_bufmtc_get;	/* ctgetnod calls with no match	*/
#endif
#endif
#endif /* 0 ???? */

#ifdef ctFeatDISTcachestats
EXTSTR  AULONG8 *ctcachestatary;/* cache stat array entries		*/
EXTSTR  pTEXT	ctcachestatbas; /* base address of memory block		*/
EXTSTR  LONG    ctcachestatcnt; /* number of cache stat entries		*/
EXTSTR  NINT    ctcachestatsiz; /* cache stat array element size	*/
#endif

#ifdef ctFeatDNODEQ_SHUTDOWN_LIMIT
/*
** Limit on number of delete node queue entries to process when the
** c-tree Server is shutting down. If the delete node queue contains
** more than this number of entries, the entire queue is written to
** the file DNODEQUE.FCS.
*/
EXTSTR  NINT	ctdnodeShutdownLimit;
#endif
#ifdef ctFeatUNIX_SHMEM
EXTSTR	pTEXT	ctshmemdir;	/* Directory for shared memory files */
EXTSTR	NINT	ctshmemprm;	/* Permission for shared memory resources */
#ifdef ctFeatSHMEMgrp
EXTSTR	pTEXT	ctshmemgrp;	/* Group for shared memory resources */
#endif
EXTSTR  NINT    ctshmemkeyism;	/* ISAM shared memory resource key */
EXTSTR  NINT    ctshmemkeysql;	/* SQL shared memory resource key */
#endif
#ifdef ctFeatMAX_LOG_DEFER
EXTSTR	LONG	ct_maxlogdefer;	/* maximum msec's between tran log flushes.  **
				** specified in whole seconds but internally **
				** msecs are used.			     */
EXTSTR	LONG8	cttoptim;	/* time of last tran log flush: usec/hrtimer */
EXTSTR  NINT	ct_maxlogdefer_Running;
				/* maxlogdefer thread running indicator	     */
#endif
#ifdef ctFeatREPLICAT_SYNC_SRVR
EXTSTR  NINT	ct_replflushlog_Running; /* replflushlog thread running indicator */
#endif
#ifdef ctBEHAV_UPDMARKSsplit
EXTSTR	LONG	ct_updmrk_splitchk;/* threshold percentage of key marks on   **
				   ** node split to call ctclup. defaults to **
				   ** ctUPDMARKS_SPLITCHK_DEFAULT (33)	     */
#endif
#ifdef ctFeatNOBUFFERING_LOGFILE
EXTSTR	NINT	ctnobuflogs;	/* Use unbuffered I/O for transaction logs */
#endif
#ifdef ctFeatNOBUFFERING
EXTSTR  NINT	ctunbufio;	/* Using unbuffered I/O option	*/
#endif
#ifdef ctFeatENCSTORE
EXTSTR	pTEXT	ctmstkeyfil;	/* Encrypted master key file */
#endif
#ifdef ctFeatKEEPOPEN
EXTSTR	NINT	ctkepopnfls;	/* Flush KEEPOPEN file on last user close */
#endif

EXTERN SEMAmut ct_rstpntmtx;	/* restore point mutex to avoid relying on **
				** ctpchksema when determining lowlog in   **
				** ctwrtlog				   */

#ifdef ctFeatPLUGIN
EXTSTR pTEXT   ctplugin_list[ctMAX_PLUGIN];         /* plugin list */
EXTSTR NINT    ctplugin_count;                      /* plugin count */
EXTSTR pTEXT   ctplugin_cb_list[ctMAX_PLUGIN];       /* plugin_callback list */
EXTSTR NINT    ctplugin_cb_count;		     /* plugin_callback count */
#ifdef ctFeatPLUGIN_DYNAMIC
EXTERN SEMAmut ctpluginMutex; /* mutex used to serialize plugin load on demand */
/* acquire exclusive access to the plugin list */
#define PLUGIN_LIST_LOCK(sOWNR,loc) ctmutrqs(&ctpluginMutex,sOWNR SMN(loc))
/* unlock the plugin list */
#define PLUGIN_LIST_UNLOCK(sOWNR) ctmutclr(&ctpluginMutex,sOWNR)
#else
/* no op */
#define PLUGIN_LIST_LOCK(sOWNR,loc)
/* no op */
#define PLUGIN_LIST_UNLOCK(sOWNR)
#endif
#endif

#ifdef ctFeatSSL
EXTSTR ctSUSSL ctsSSL;				/* SUBSYSTEM COMM_PROTOCOL SSL */
#endif
#ifdef ctFeatRP_AUTO
EXTSTR ctSUARP ctsARP;				/* SUBSYSTEM TRNLOG AUTO_RESTORE_POINT */
#endif
#ifdef ctFeatPWDREQ
EXTSTR ctSUPWR ctsPWR;				/* SUBSYSTEM SECURITY PASSWORD */
#endif
#ifdef ctFeatADVLOG
EXTSTR ctADVLOG ctsAdvLog;			/* SUBSYSTEM AUDIT LOG */
#endif
#ifdef ctFeatKEYCOMPRESSsRLE
EXTSTR ctCompressContext *  pkcRLEctxCmp;  /* Key Compression compression */
EXTSTR ctCompressContext *  pkcRLEctxExp;  /* Key Compression expansion */
EXTSTR CMPRECFNC kcRLEfnc;          /* Key Compression descriptor */
#endif
#ifdef ctFeatHEAP_DEBUGGING
EXTSTR NINT ctHeapDebugLevel;			/* HEAP_DEBUG_LEVEL */
EXTSTR NINT ctHeapDebugExclusionList[NUMCTLIST];  /* HEAP_DEBUG_EXCLUSION_LIST */
#endif
#ifdef ctFeatSTACK_DUMP
EXTSTR NINT ctdmpstack_behavior; 		/* STACK_DUMP */
#endif

#else /* ~MULTITRD */

#ifdef ctHUGEFILE
EXTERN LONG	  cthghwrd;
#endif /* ctHUGEFILE */
#ifdef ctFeatRECRLOCK
EXTERN LONG	  netrecr;
#endif
#ifndef TRANPROC
EXTERN COUNT	  tranactv;
EXTERN COUNT	  transavp;
#endif
#endif /* ~MULTITRD */

#ifdef ctFeatPARTITION_ESTIMATE
EXTSTR NINT	 ctprtestlimit;		/* maximum partitions to sample */
EXTSTR NINT	 ctprtestpct;		/* max percent of partitions to sample */
#endif
#ifdef ctFeatFILEBLOCKcounter
EXTSTR ULONG	 ctfilblkcnt;		/* current number of file blocks */
#endif
#ifdef MULTITRD
EXTSTR NINT	 ct_initerr;		/* c-tree initialization failed	 */
#endif
#ifdef ctFeatFILENAMEhash
EXTSTR pFNAMHSH	 ct_fnhash;		/* open file name hash table	 */
EXTSTR UINT	 ct_fnbins;		/* open file name hash bin count */
#endif
#ifdef ctFeatLOGLMT
EXTSTR pLLHSH	 ct_llhash;		/* user/group logon limit hash table	 */
EXTSTR UINT	 ct_llbins;		/* user/group logon limit hash bin count */
#ifdef ctFeatLOGLMTusracct
EXTSTR NINT	 ndusracct;		/* distinct user accounts currently logged on */
EXTSTR NINT	 mdusracct;		/* maximum distinct user accounts allowed */
EXTSTR NINT	 mcusracct;		/* maximum connections per user account */
#endif
#endif
#ifdef ctFeatAUTO_MKDIR
EXTSTR NINT	 ctautomkdir;		/* automatically create directories	*/
#endif
#ifdef ctBEHAV_LOOKASIDE
EXTSTR pVOID	 ctla_ptr[NUMCTLIST];	/* array of lookaside list pointers */
#endif
#ifdef ctFeatVIRTUAL_FILES
EXTSTR CTFILE    ctfmru;
EXTSTR pCTFILE   ct_mru;
#endif
EXTSTR ppCTFILE  ctfcbhdr;
#ifdef ctFeatFILEUSRLST
EXTSTR pUSRLSTANC
		 ctfcbusr;	/* ptr to array of user list pointers	*/
#endif
EXTSTR pTREBUF	 ct_btree;	/* ptr to beg of b-tree buffers		*/
EXTSTR pDATBUF	 ct_dbufr;	/* ptr to beg of data file buffers	*/
EXTSTR pCTFILE	 ct_key;	/* ptr to beg of ct_key file structures	*/
#ifdef ctBEHAV_FCBSTK
EXTSTR pCTFILE	 ct_fcbstk;	/* ptr to top of stack of available FCB	*/
#endif
EXTSTR pCTFILE	 ct_dat;	/* ptr to beg of data file structures	*/
EXTSTR pCTFILE	 ct_vat;	/* ptr to beg of var data file struc	*/
EXTSTR pDFDEF	 ct_dfdef;
#ifdef ctFeatDISKFULLaction
EXTSTR pDFDEF	 ct_dfadef;	/* DISK_FULL_ACTION list		*/
#endif
#ifdef ctFeatFILMTX
EXTSTR pFILMTX	 filmtx_ary;
#endif
#ifdef ctFeatSNAPSHOT
EXTSTR pUSRLST	 ct_ussanc;	/* dynamically allocated user list: anchor  */
#endif
#ifndef ctCACHE_MEMORY
EXTSTR pLONG	 sctshdmem;	/* shadow memory: excluding cntl structures */
EXTSTR pLONG	 sctusrsum;	/* mem usage sum */
EXTSTR pLONG	 sctusrtot;	/* mem usage limit */
#endif
EXTSTR pTEXT	 ctsig_rdy;	/* name of exe to launch on server ready*/
EXTSTR pTEXT	 ctusrsig_rdy;	/* text passed to user defined signal ready function */
EXTSTR pTEXT	 ctsig_mir;	/* name of exe to launch on 1st mir trm	*/
EXTSTR pTEXT	 ctsig_dwn;	/* name of exe to launch on server down	*/
EXTSTR pTEXT	 ctusrsig_dwn;	/* text passed to user defined signal down function */
EXTSTR ULONG	 ct_allsup;	/* bit mask for FREL_ERR test. replaces **
				** DEF_MASK_ALLSUP			*/
#ifdef TRANPROC
EXTSTR ULONG	 ct_logsup;	/* bit mask for LFRM_ERR test. replaces  **
				** DEF_MASK_LOGSUP			 */
#ifdef ctLOGAUG
EXTSTR ULONG	 ct_logaug;	/* bit mask for LAUG_ERR test		 */
#endif
#endif

#ifdef ctUNICODE
#ifndef ctBEHAV_CHECK_ICU_COLLATOR_VERSION
EXTSTR LONG	 kseg_icuv;	/* current ICU runtime collation version */
#endif
EXTSTR LONG	 kseg_icuE;	/* last ICU file version in error	 */
EXTSTR TEXT	 kseg_icuD[ctKSEGDLEN];
				/* last ICU file locale in error	 */
#endif
#ifdef ctFeatUSRBLKTIMOUT
EXTSTR LONG	ct_atimout;	/* ADMIN user group user all files timeout */
EXTSTR NINT	ct_dtimout;	/* diagnostic indicator			   */
#endif
#ifndef ctFeatSNAPSHOT
EXTSTR LONG	 ct_compflg;	/* 1st compatibility word		*/
EXTSTR LONG	 ct_compflg2;	/* 2nd compatibility word		*/
EXTSTR LONG	 ct_compflg3;	/* 3rd compatibility word		*/
EXTSTR LONG	 ct_compflg4;	/* 4th compatibility word		*/
EXTSTR ULONG	 ct_compflg5;	/* 5th compatibility word		*/
EXTSTR LONG	 ct_diagflg;	/* 1st diagnostics word			*/
EXTSTR LONG	 ct_diagflg2;	/* 2nd diagnostics word			*/
EXTSTR LONG	 ct_diagflg3;	/* 3rd diagnostics word			*/
#endif

EXTSTR LONG	 ctclrlop;
EXTSTR LONG	 ctflslop;
EXTSTR LONG	 ctmemlmt;	/* max ctgetmem request  */
#ifdef ct8P
EXTSTR LONG8	 ctmemtot;	/* space aggregate limit */
#else
EXTSTR LONG	 ctmemtot;	/* space aggregate limit */
#endif
EXTSTR LONG	 ctmemusr;	/* system default user limit */
#ifdef ctN8
EXTSTR LONG8	 ctmemup;	/* MEMORY_MONITOR limit */
EXTSTR LONG8	 ctmemdn;	/* MEMORY_MONITOR limit */
#else
EXTSTR LONG	 ctmemup;	/* MEMORY_MONITOR limit */
EXTSTR LONG	 ctmemdn;	/* MEMORY_MONITOR limit */
#endif
EXTSTR LONG	 ctmemch;	/* MEMORY_MONITOR delta */
EXTSTR ULONG	 ctmemtrk_up;
EXTSTR ULONG	 ctmemtrk_dn;
EXTSTR LONG	 ctmemtrk_ch;
EXTSTR ULONG	 ctmemtrk_net;
EXTSTR VRLEN	 ct_qblock;	/* SQL record buffer block size		*/
EXTSTR VRLEN	 ct_gstmem;	/* guest memory limit			*/
EXTSTR LONG	 ct_timout;	/* inactive tran timeout		*/
EXTSTR LONG	 ct_usrmrl;	/* user memory attribute bits		*/

#ifdef ctFeatCFG_SCALE_N8
EXTSTR LONG8	 ct_disklmt;	/* disk full threshold			*/
#else
EXTSTR ULONG	 ct_disklmt;	/* disk full threshold			*/
#endif
EXTSTR ULONG	 ct_ribs;
EXTSTR LONG	 ct_ii[ctIDLEz];/* idle task Q intervals		*/
EXTSTR NINT	 ct_ii_nsT;	/* no save flags Tran			*/
EXTSTR NINT	 ct_ii_nsN;	/* no save flags NoTran			*/
EXTSTR NINT    (*ct_ip[ctIDLEz])(VOID ); /* idle task func pointers	*/

#ifdef ctMXLOGS
#else
EXTSTR ULONG	 ct_abseq;	/* abort list sequence number		*/
EXTSTR LONG	 ct_abnod;	/* abort list node count		*/
EXTSTR LONG	 ct_cmnod;	/* pending node tran count		*/
EXTSTR LONG	 ct_cmdat;	/* pending data tran count		*/
#ifdef ctFeatPRESYNC_TRNLST
EXTSTR LONG	 ct_cmnod2;	/* auxiliary node tran count		*/
EXTSTR LONG	 ct_cmdat2;	/* auxiliary data tran count		*/
EXTSTR LONG	 ct_cmnodp;	/* prelist node tran count		*/
EXTSTR LONG	 ct_cmdatp;	/* prelist data tran count		*/
EXTSTR pCOMLST	 ct_cmnod2_ptr;
EXTSTR pCOMLST	 ct_cmdat2_ptr;
EXTSTR pTEXT	 ct_cmnod2_pre;
EXTSTR pTEXT	 ct_cmdat2_pre;
EXTSTR NINT	 ct_cmflg2;
EXTSTR NINT	 ct_cmnod2_flg;
EXTSTR NINT	 ct_cmdat2_flg;
#endif
#ifdef ctLOG_IDX
EXTSTR LONG	 ct_numvi;	/* vulnerable index update count	*/
#endif
#endif

EXTSTR LONG	 ct_statflg;	/* CTSTATUS flag			*/
EXTSTR LONG	 ct_sysviewT;	/* SYSVIEW WHAT				*/
EXTSTR LONG	 ct_sysviewN;	/* SYSVIEW WHEN				*/
EXTSTR LONG	 ct_langflg;	/* LANGUAGE flag			*/
EXTSTR LONG	 ctquemon;	/* node queue monitor threshold	*/
#ifdef ctSRVR
EXTSTR LONG	 ctsusers;	/* number of users in forced logoff	*/
EXTSTR ULONG	 ctclsfil;	/* running iclsfilx call count		*/
EXTSTR LONG	 ctclspnd;	/* numer of iclsfilx calls pending	*/
#endif
#ifdef ctFeatPERMISSIONS
EXTSTR LONG	 ct_wpf;	/* default WORLD permission flag	*/
EXTSTR LONG	 ct_opf;	/* default OWNER permission flag	*/
EXTSTR LONG	 ct_gpfcnt;	/* # of group permission flags		*/
#endif
EXTSTR LONG	 ctstatus_size;	/* size limit on CTSTATUS.FCS		*/
EXTSTR NINT	 ctisolev;	/* default isolation level		*/
#ifdef ctFeatCLRCHK
#ifdef MULTITRD
EXTSTR NINT	 ctclrchk;	/* bound server	USERPRF_CLRCHK setting	*/
#endif
#endif
EXTSTR NINT	 ctstatus_purge;/* CTSTATUS.FCS purge indicator		*/
#ifdef DBG749x
EXTSTR UINT	 ctlstfrq;
#endif

EXTSTR NINT	 ctbpfx_level;	/* default zero: only break on critical **
				** tests. the higher ctbpfx_level, the	**
				** more debugging tests that will be	**
				** caught.				*/
#ifdef ctDBGfcqaDelay
EXTSTR LONG	 ctdbgDelay;	/* milliseconds of artificial delay	*/
#endif
#ifdef ctDBGfcqa
EXTSTR NINT	 dbgfixbuf;	/* force specified # of idx buffers	*/
EXTSTR NINT	 dbgfixcac;	/* force specified # of dat cache pages	*/
#endif

EXTSTR UINT	 ct_tmpseq;	/* temporary file sequence number	*/
EXTSTR NINT	 ct_dftot;
EXTSTR NINT	 ct_dfnum;
#ifdef ctFeatDISKFULLaction
EXTSTR NINT	 ct_dfatot;
EXTSTR NINT	 ct_dfanum;
#endif
EXTSTR NINT	 memsubflg;	/* memory subsystem flag		*/
#ifdef ctFeatFILMTX
EXTSTR NINT	 filmtx_tot;
EXTSTR NINT	 filmtx_num;
#endif
EXTSTR NINT	 ctmtcsegflg;	/* matching segment action		*/
EXTSTR NINT	 ctnonsegflg;	/* nonmatching segment action		*/
EXTSTR NINT	 ctatotrnlgt;	/* if YES, AUTO_TRNLOG uses ctLIGHTTRAN */
EXTSTR NINT	 ctmiroff;	/* if YES, turn off all mirroring	*/
EXTSTR NINT	 ctosIOlok;	/* if YES, need OS lock to force cache	*/
EXTSTR NINT	 ctdedmon;	/* deadlock monitor flag		*/
EXTSTR NINT	 ctfncmon;	/* function request monitor		*/
EXTSTR NINT	 ctchkmon;	/* checkpoint monitor flag		*/
#ifdef ctFeatSNAPSHOT
EXTSTR NINT	 ct_usstot;	/* user ID snapshot list		*/
EXTSTR NINT	 ct_ussnum;
#endif
#ifdef ctSRVR
EXTSTR NINT	 ct_fhlimit;	/* override file handle limits/default	*/
#endif
EXTSTR NINT	 cthshift;	/* huge shift				*/
EXTSTR NINT	 ct_dq;		/* shrink task logical Q handle		*/
EXTSTR NINT	 ct_rq;		/* reclaim deleted space Q handle	*/
#ifdef ctFeatKEEPOPENclose
EXTSTR NINT	 ct_kocq;	/* KEEPOPENclose queue handle		*/
#endif
#ifdef ctFeatDFRIDX
EXTSTR NINT	 ct_dfridxq;	/* Deferred index queue handle		*/
#endif
#ifdef ctFeatSRVRpower
EXTSTR NINT	 ct_conwatq;	/* Connection wait queue handle		*/
EXTSTR SEMAmut	 ct_conwatm;	/* Connection wait queue mutex		*/
#endif

#ifdef ctMXLOGS
#else
EXTSTR NINT	 ct_cq; 	/* checkpoint task logical Q handle	*/
#endif

#ifdef ctFeatIDLE_THREAD
EXTSTR NINT	 ct_iq[ctIDLEz];/* idle task Q handles			*/
EXTSTR NINT	 ct_id[ctIDLEz];/* idle task thread handles		*/
EXTSTR NINT	 ctidle;	/* YES: at most background activity	*/
#endif
EXTSTR UINT	 nsplit;	/* node splits				*/
EXTSTR NINT	 cthghflx;	/* highest allocated FCB: ctFLEXFILE	*/
EXTSTR NINT	 ctfnz;		/* superfile member max name size	*/
#ifdef ctBEHAV_FCBSTK
EXTSTR NINT	 ct_avlstk;	/* number of FCB on available stack	*/
#ifdef ctFeatKEEPOPENclose
EXTSTR NINT	 ct_totkep;	/* number of FCB on KEEPOPEN avl lists	*/
#endif
#endif
#ifndef CTBOUND
EXTSTR NINT	 ct_lq;		/* logon logical Q handle		*/
EXTSTR NINT	 ct_sq;		/* event log queue			*/
EXTSTR pFILE	 ctfncfp;	/* optional file ptr for func monitor	*/
#endif
EXTSTR pTEXT	 ct_tmppth;	/* temporary file default path		*/
#ifdef TRANPROC
EXTSTR ppTEXT	 ctlogmemanc;
EXTSTR pREBLST	 ctrebhed;	/* index rebuild list */
EXTSTR pREBLST	 ctcmphed;	/* compress rebuild list */
EXTSTR pREBLST	 ctmirhed;	/* mirror sync list */
EXTSTR pREBLST	 ctiblhed;	/* data (IFIL) rebuild list */
EXTSTR ULONG	 ctlogchklmt;	/* override checkpoint interval		*/
EXTSTR LONG	 ct_trnhghmrk;	/* threshold to warn tran high mark	*/
#ifdef ctRECBYTIDX
EXTSTR NINT 	 ctcoaltran;	/* coalesce of non-recbyt ctTRNLOG files  */
#endif
#ifdef ctMXLOGS
#else
EXTSTR ULONG	 prv_logser;	/* previous checkpoint log#		*/
EXTSTR ULONG	 prv_chkpos;	/* previous checkpoint pos		*/
EXTSTR ULONG	 prv_prvpos;	/* previous checkpoint back link	*/
EXTSTR NINT	 ct_chktrd;	/* thread id of checkpoint thread	*/
EXTSTR NINT 	 ctfstr;	/* oldest start file #			*/
EXTSTR NINT	 ctnewlogs;	/* starting without logs		*/
#ifdef ctBEHAV_LFLSEMA
EXTSTR NINT	 ct_lfltrd;	/* thread id of cmtdly blk thread	*/
EXTSTR NINT	 ctlflwait;
#endif
#endif

EXTSTR UINT	 ct_shbins;	/* shadow hash bins			*/
EXTSTR UINT	 ct_shbyts;	/* shadow hash bytes			*/
EXTSTR NINT	 ct_tryprvchk;	/* try previous checkpoint		*/
EXTSTR NINT	 ctsuplog;	/* suppress log flush and sync begin\end*/
EXTSTR NINT	 ctsuplogsync;	/* suppress log sync on begin\end tran	*/
EXTSTR NINT	 ctfwdned;	/* ctrdmp requires TRANFWD		*/
#endif
EXTSTR UINT	 ct_lhbins;	/* lock hash bins			*/
#ifdef ctDYNHASH
EXTSTR UINT	 ct_lhbinx;	/* lock hash bins max			*/
EXTSTR UINT	 ct_lhLoadF;	/* lock hash load factor		*/
EXTSTR UINT	 ct_lhRehashF;	/* lock hash rehash factor		*/
EXTSTR UINT	 ct_lhMaxBins;	/* lock hash max bins used by a file	*/
EXTSTR UINT	 ct_ulMaxBins;	/* lock hash max bins used by a user	*/
EXTSTR UINT	 ct_ulNoShrink;	/* turnoff reduction in hash bins	*/
EXTSTR UINT	 ct_lhNoShrink;	/* turnoff reduction in hash bins	*/
#ifdef TRANPROC
EXTSTR UINT	 ct_shbinx;	/* lock hash bins max			*/
EXTSTR UINT	 ct_shLoadF;	/* lock hash load factor		*/
EXTSTR UINT	 ct_shRehashF;	/* lock hash rehash factor		*/
EXTSTR UINT	 ct_shMaxBins;	/* preimg hash max bins used by a user	*/
EXTSTR UINT	 ct_shNoShrink;	/* turnoff reduction in hash bins	*/
#endif
#ifdef ctPortYMF
EXTSTR UINT	 ct_spltNbrFls;	/* split rule number of files		*/
#endif
#endif
EXTSTR UINT	 ctconbins;	/* context bins				*/
#ifdef MULTITRD
EXTSTR NINT	 ctrmsg;	/* recovery in process message flag	*/
EXTSTR NINT	 ct_commp;	/* # of comm protocols in use		*/
EXTSTR NINT	 ct_jobst;	/* # of job threads in use		*/
EXTSTR NINT	 ct_commdis;	/* comm protocol support disabled	*/
#endif
#ifdef ctBEHAV_FCRESsec
EXTSTR NINT	 ct_fcres_lev;	/* required security level to update
				   FCRES resource entries: default zero	*/
#endif
EXTSTR VRLEN	 ct_bfsiz;	/* data buffer size			*/
EXTSTR NINT	 ctlogidxfrc;	/* ctLOGIDX override: YES-on HYS-off	*/
EXTSTR ULONG	 ctrdmp_opt;	/* dynamic dump option bits		*/
EXTSTR NINT	 ctrdmp_memlog; /* dynamic dump RECOVER_MEMLOG setting	*/
EXTSTR NINT	 ctrdmp_flg;	/* signals dynamic dump recovery	*/
EXTSTR NINT	 ctmdmp_flg;	/* signals dyn dump recovery had mirrors*/
EXTSTR NINT	 ctfdmp_flg;	/* signals forward roll	operation	*/
EXTSTR NINT	 ctxflg[5];	/* test tran work space flag		*/
EXTSTR RNDFILE	 ctxflgfd[5];	/* test tran work space file descriptor	*/
#if defined(ctFeatFPGloktimout) && defined(ctPortWIN32)
EXTSTR HANDLE	 ctxflgev[5];	/* test tran work space event handle	*/
#endif
EXTSTR pULONG	 ctridx_ptr;	/* dynamic dump index update list ptr	*/
EXTSTR NINT	 ctridx_cur;	/* dynamic dump index update current	*/
EXTSTR NINT	 ctridx_tot;	/* dynamic dump index update total	*/
EXTSTR NINT	 clnidxx_flag;	/* on the fly CLNIDXX flag		*/
EXTSTR NINT	 ctrflg;	/* automatic recovery flag              */
#ifdef ctFeatRECOVERY_CHECK_DUPFID
	/* processing transaction-dependent operation during recovery	*/
EXTSTR NINT	 recovery_TRANDEP_operation;
#endif
EXTSTR NINT	 ctstrcv_flg;	/* init automatic recovery		*/
#ifdef ctFeatLOGFLUSH_MOD
EXTSTR UINT	 ctminlogsync;	/* YES / NO: DELAYED_DURABILITY enabled	*/
#endif
#ifdef ctFeatRP
EXTSTR UINT	 ctkep_rp_rcv;	/* YES / NO: RECOVER_TO_RESTORE_POINT	*/
EXTSTR UINT	 ctkep_rp_cfg;	/* RECOVER_TO_RESTORE_POINT entry in	**
				** ctsrvr.cfg				*/
EXTSTR NINT	 ctkep_rp_num;	/* number of restore points to keep	*/
EXTSTR NINT	 ctkep_rp_act;	/* number of restore points active	*/
EXTSTR NINT	 ctkep_rp_fnd;	/* restore point found during rollback	*/
EXTSTR NINT	 ctkep_rp_req;	/* DELAYED_DURABILITY on at system crash*/
EXTSTR ULONG	 ctkep_rp_tim;	/* time of last restore point		*/
EXTSTR LONG8	 ctkep_rp_srn;	/* restore point serial number		*/
#endif
EXTSTR LONG	 ct_endser;	/* last log during auto recovery	*/
#ifdef ctBEHAV_EOR_CLSTRAN
EXTSTR NINT	 ct_clstrn;	/* any CLSTRAN written at end of recvry	*/
#endif
EXTSTR NINT	 ctlogmem;	/* preload log files to memory in rcvy	*/
EXTSTR NINT	 ctlogmemmax;	/* max log files to memory in rcvy	*/
EXTSTR NINT	 ctlogdet;	/* output recovery details		*/
EXTSTR NINT	 ctskpclnfil;	/* if on, skip clean files in recovery	*/
EXTSTR NINT	 ctfnstrat;	/* file name conversion strategy	*/
EXTSTR NINT	 ctmnstrat;	/*    mirror conversion strategy	*/
#ifdef ctSRVR
EXTSTR NINT	 cttloc;	/* stop server locale (ctcatend: loc)	*/
#endif
EXTSTR NINT	 ctapwflg;	/* Check ADMIN pw flag			*/

#ifdef ctMXLOGS
#else
EXTSTR ULONG	 ct_lstchktim;	/* last checkpoint time stamp		*/
EXTSTR NINT	 ctfilcre;	/* flag for create since checkpoint	*/
#endif
#ifdef ctFeatMAX_USER_LOGS
EXTSTR NINT	 ct_mul;	/* maximum user logs in 1 transaction	*/
#endif
#ifdef ctFeatDFRIDXsrvr
EXTSTR NINT	 ct_maxdfridxlogs; /* maximum logs for deferred index log scan */
#endif
#ifdef ctFeatREPLICAT
EXTSTR NINT	 ct_maxrepllogs; /* maximum logs for replication log scan */
#endif
#ifdef ctFeatRBLSORT
#if defined(ctFeatCFG_SCALE) && defined(ct8P)
EXTSTR LONG8	 ct_maxrblqueue; /* maximum rebuild queue size		*/
#else
EXTSTR ULONG	 ct_maxrblqueue; /* maximum rebuild queue size		*/
#endif
#endif
#ifdef ctFeatDumpSYNC
EXTSTR ULONG     ctDumpSyncInterval;   /* periodic sync of dump file in bytes */
#endif
#ifdef ctBEHAV_CHKPDFC
EXTSTR NINT	 ct_dfc;	/* maximum logs w/o checkpoint		*/
#endif

EXTSTR NINT	 ct_hghu1;	/* high water mark thread(user) handle	*/
EXTSTR COUNT	 ct_mxu1;	/* max users plus origin		*/
EXTSTR NINT	 ct_mxu1a;
EXTSTR NINT	 ct_mxu1b;
EXTSTR NINT	 ct_cmnown;	/* common onwer number (semaphores)	*/
EXTSTR UINT	 ct_hshft;	/* hash shift parameter			*/
EXTSTR UINT	 ct_hbins;	/* hash bins for buffers		*/
#ifdef ctFeatBLKSEMA
EXTSTR UINT	 ct_bbins;	/* block bins for buffers		*/
EXTSTR UINT	 ct_bbinsrat;	/* optional block bins ratio		*/
#endif
EXTSTR UINT	 ct_dshft;	/* datbuf hash shift parm		*/
EXTSTR UINT	 ct_dbins;	/* datbuf hash bins			*/
#ifdef ctBEHAV_XTDHDR
EXTSTR NINT	 cth6flg;	/* restore V6 header for non-X8 creates	*/
#endif
#ifdef ctBEHAV_ATODEP
EXTSTR NINT	 ctatodep;	/* TRANDEP consistency enabled for RBLD	*/
#endif
#ifdef ctLOG_IDX
EXTSTR UINT	 ct_tbins;	/* vulnerable tran# hash bins		*/
#endif
#ifdef ctFeatAVLISTnum
EXTSTR ppBHLARY	 ct_ibavl;	/* index buffer avl list anchors	*/
EXTSTR pTEXT	 ct_ibavlb;
#endif
#ifdef ctFeatDALISTnum
#ifdef ctFeatNoDatPndgList
EXTSTR ppCRAWL	 ct_dbavl;
#else
EXTSTR ppBHLARY	 ct_dbavl;	/* data buffer avl list anchors		*/
#endif
EXTSTR pTEXT	 ct_dbavlb;	/* cache aligned base address		*/
#ifdef ctFeatDatEmptyList
EXTSTR ppEMPDAT	 ct_dbempl;
EXTSTR pTEXT	 ct_dbemplb;
EXTSTR LONG	ctLmtEmp;	/* first use threshold			*/
EXTSTR LONG	ct1stEmp;	/* approximate first use counter	*/
EXTSTR UINT	ctaddempl;	/* add to empty list list number	*/
EXTSTR UINT	ctrmvempl;	/* rmv to empty list list number	*/
#endif
#endif
#if !defined(ctFeatAVLISTnum) || !defined(ctFeatDALISTnum)
EXTSTR BHL	 ct_bavl[2];	/* buffer avl list anchors		*/
#endif
				/* buffer hash list anchors		*/
EXTSTR ppBHL     ct_bhla[NUMANCHOR];
#if defined(ctFeatDBSEMAhsh) || defined(ctFeatGNSEMAhsh)
EXTSTR ppBHLARY  ct_bhlR[NUMANCHOR];
EXTSTR pTEXT	 ct_bhlRb[NUMANCHOR];
#endif
#ifdef DBGhash
EXTSTR pLONG	 dbg_bhl_n;
EXTSTR pLONG	 dbg_bhl_d;
#endif
EXTSTR pTEXT	 ctsdname;	/* server directory name		*/
EXTSTR pTEXT	 ctsmname;	/* mirror directory name		*/
EXTSTR pTEXT	 ctsvname;	/* server name				*/
EXTSTR pTEXT	 ctsqname;	/* server SQL name			*/
#ifdef ctPortVINESLOG
EXTSTR TEXT	 ctlgname[MAX_NAME];
				/* server status log name		*/
#endif

#ifdef ctTRAP_COMM
#ifdef MULTITRD
#ifndef CTBOUND
EXTSTR ULONG	 ctTCpos;	/* TrapComm buffer pos			*/
EXTSTR ULONG	 ctTCsiz;	/* TrapComm buffer size			*/
EXTSTR pFILE	 ctTCfp;	/* TrapComm stream file pointer		*/
EXTSTR SEMAmut	 ctTCsema;	/* TrapComm mutex			*/
EXTSTR pTEXT	 ctTCbuf;	/* TrapComm buffer pointer		*/
#endif
#endif
#endif /* ctTRAP_COMM */

EXTSTR pTEXT	 ctscommp[MAXCOMMP];
				/* server comm protocol			*/
				/* TrapComm mutex			*/

#ifdef ctFeatJOBMGTSYS 		/* FairCom Job Management System Subsystem */
EXTSTR pTEXT	 ctsjobsf[MAXCTJOBS];	/* server ctjobs files		*/
#endif   

EXTSTR pTEXT	 ct_del;	/* constant 0xff array			*/
EXTSTR UINT	 ct_delsiz;	/* size of 0xff array			*/
EXTSTR NINT	 ct_sqlsupr;	/* sql superfile flag			*/
EXTSTR UINT	 cts_list_m;	/* list memory block size		*/
EXTSTR UINT	 cts_sort_m;	/* sort memory buffer size		*/
EXTSTR UINT	 cts_bufr_m;	/* bufr memory block size		*/
#ifdef MULTITRD
#ifdef ctBEHAV_freopen
#define ctMAX_freopen	4
EXTSTR TEXT	 ctfrename[ctMAX_freopen][IDZ];
EXTSTR pFILE	 ctfrefp[ctMAX_freopen];
EXTSTR SEMAmut	 ctfresema[ctMAX_freopen];
#endif /* ctBEHAV_freopen */
EXTSTR UTEXT	 ct_sflvr;	/* system flavor			*/
EXTSTR UTEXT	 ct_salgn;	/* system alignment			*/
EXTSTR UTEXT	 ct_spntr;	/* system pointer size			*/
#endif /* MULTITRD */

EXTSTR NINT  ctmpagcache;	/* specify multiple page cache count	*/
EXTSTR NINT  ctrunfil;
EXTSTR NINT  ctrcvfil;
EXTSTR NINT  ct_adfil;
EXTSTR UCOUNT ct_ver1;		/* defines configuration options 128 header */
EXTSTR UCOUNT ct_ver2;		/* defines configuration options XTD header */
EXTSTR UCOUNT ct_ver3;		/* defines configuration options 6BT header */
EXTSTR TEXT  ctsupsep;

#ifdef MULTITRD

#ifdef ctSQLSRVR
EXTSTR NINT ctsqlinitdone;	/* Indicates when SQL database initialization is done.
				** Used to make the ISAM logon threads wait
				** until SQL database initialization finishes. */
#endif
#ifdef ctFeatDYNAMIC_DUMP
EXTSTR SEMA ct_srvsema;
#endif
EXTSTR SEMA ct_uhnsema;		/* user handle semaphore */

#ifndef ctCACHE_MEMORY
EXTSTR SEMA ct_undsema;		/* single tran undo semaphore */
EXTSTR SEMA ct_dmpsema;		/* dynamic dump semaphore */
EXTSTR SEMA ct_ismema;		/* ctismem semaphore */
#ifdef ctFeatVIRTUAL_FILES
EXTSTR SEMA ct_vtsema;		/* vtclose semaphore */
EXTSTR SEMA ct_nmvsema;		/* ct_numvfil sema */
#endif
EXTSTR SEMA ct_avlsema;		/* available file counter */
EXTSTR SEMA ct_chksema;		/* checkpoint semaphore */
EXTSTR SEMA ct_abtsema;		/* node abort list semaphore */
EXTSTR SEMA    ct_lflsema;	/* log file i/o semaphore */
#ifdef ctBEHAV_CHKPDFC
EXTSTR SEMAtim ct_chkpblk;	/* chkp / log write interlock */
#endif
#ifdef ctDUMPorQUIET
EXTSTR SEMAblk ct_1dmsema;	/* enforce only 1 dump at-a-time */
#endif
EXTSTR SEMAblk ct_lfwsema;	/* wait for collective log flush */
EXTSTR SEMAtim ct_snapsema;	/* wait for next snapshot */
#ifdef ctFeatTRAN_TIMEOUT
EXTSTR SEMAtim ct_trntimsema;	/* wait for next trntimout check */
#endif
#ifdef ctFeatREQUEST_TIME_MONITOR
EXTSTR SEMAtim ct_rqtmonsema;	/* wait for next request time check */
#endif
#ifdef ctDISTcounts
EXTSTR SEMAtim ct_DISTcountsWat;/* wait for next DISTcounts update */
#endif
EXTSTR SEMAmut ct_comsema;	/* index buffer commit list semaphore */
EXTSTR SEMAmut ct_dcmsema;	/*  data  cache commit list semaphore */
EXTSTR SEMAmut ct_lftsema;	/* log high-water flush mark control */
EXTSTR SEMAmut tranac_sema;	/* control count of beg/end tran calls */
#ifndef ctFeatDBSEMAhsh
EXTSTR SEMAmut ct_dbsema;	/* data cache control sema */
#endif
EXTSTR SEMAmut ct_gvsema;	/* ctgv semaphore */
EXTSTR SEMAmut ct_logsema; 	/* log position/buffer semaphore */
#ifndef ctFeatGNSEMAhsh
EXTSTR SEMAmut ct_gnsema;	/* get node (getnod) semaphore */
#endif
#ifdef ctBEHAV_BLM
EXTSTR SEMAmut ct_nutmtx;	/*    tran buffer page update list mutex */
EXTSTR SEMAmut ct_nupmtx;	/* no tran buffer page update list mutex */
EXTSTR SEMAmut ct_dutmtx;	/*    tran cache  page update list mutex */
EXTSTR SEMAmut ct_dupmtx;	/* no tran cache  page update list mutex */
#endif
#ifdef ctFeatSNAPSHOTtimer
EXTSTR SEMAmut ct_lokmtx;	/* ctlokdet mutex */
EXTSTR SEMAmut ct_xlkmtx;	/* ctxlkdet mutex */
#endif
#ifdef ctFeatGNSEMAhsh
#ifndef ctFeatAVLISTnum
EXTSTR SEMAmut ctavlsema;
#endif
#ifdef ctFeatBLKSEMA
EXTSTR pSEMAmut ctpgnsemaBK;
#endif
#endif
#ifdef ctFeatDBSEMAhsh
#ifndef ctFeatDALISTnum
EXTSTR SEMAmut ctdavsema;
#endif
#ifdef ctFeatSPLSEMA
EXTSTR SEMAmut ct_splsema;
#endif
#endif
#ifdef ctFeatDEFER_OPNTRAN
EXTSTR SEMAmut ct_dotsema;	/* deferred open-logging mutex */
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
EXTSTR SEMAmut ct_cmprecmtx;	/* compression resource handle mutex */
#endif
EXTSTR SEMAmut ct_ocsema;	/* open / create semaphore */
EXTSTR SEMAmut ct_tflsema;	/* tfil (file handle for log entries) mutex */
#ifdef ctBEHAV_LLSEMA
EXTSTR SEMAmut ct_llsema;	/* deadlock detection */
#if defined(ctFeatLOCKSTATS) && !defined(ctFeatLOCKSTATSopt)
EXTSTR SEMAmut ct_lmsema;	/* global lock stats */
#endif
#else
EXTSTR SEMAmut ct_llsema;	/* lock list semaphore */
#endif
EXTSTR SEMAmut ct_facsema;	/* file lru access count */
#ifndef UTRrwlock
EXTSTR SEMAmut ct_utrsema; 	/* ct_usrtr[] semaphore */
#endif
EXTSTR SEMAmut ct_memsema; 	/* memory allocation semaphore */
#ifndef ctBEHAV_WORKsync
EXTSTR SEMAmut ct_concsema; 	/* multi-procesor concurrency */
#endif
EXTSTR SEMAmut ct_opncsema; 	/* multi-procesor concurrency */
#ifdef ctBEHAV_SEP_CONC
EXTSTR SEMAmut ct_c2ncsema; 	/* multi-procesor concurrency ** available** */
#ifndef C3Nrwlock
EXTSTR SEMAmut ct_c3ncsema; 	/* multi-procesor concurrency */
#endif
EXTSTR SEMAmut ct_c4ncsema; 	/* multi-procesor concurrency */
EXTSTR SEMAmut ct_c5ncsema; 	/* multi-procesor concurrency */
EXTSTR SEMAmut ct_c6ncsema; 	/* multi-procesor concurrency */
#endif
EXTSTR SEMAmut	ct_ctlsema;
EXTSTR SEMAmut	ct_pi1sema;
EXTSTR SEMAmut	ct_pi2sema;
EXTSTR SEMAmut	ct_pi4sema;
EXTSTR SEMAmut	ct_pi8sema;
EXTSTR SEMAmut	ct_piwsema;
EXTSTR SEMAmut	ct_pixsema;
EXTSTR SEMAmut	ct_piysema;
EXTSTR SEMAmut	ct_pizsema;
EXTSTR SEMAmut	ct_piasema;
EXTSTR SEMAmut	ct_pibsema;
EXTSTR SEMAmut	ct_batsema;
EXTSTR SEMAmut	ct_ilksema;
#endif /* ~ctCACHE_MEMORY */

EXTSTR SEMAmut *ctlsemap[SEMTYP];
#ifdef ctFeatMEMSUBX
EXTSTR NINT	ctmem_bin;
EXTSTR SEMAmut ** ctlsemapx;
EXTSTR pTEXT	ctlsemapxf;
#endif
EXTSTR COUNT ct_numusr;		/* active users */
#ifdef ctFeatPRICACHE
EXTSTR NINT	prime_on;
#endif
#endif

#ifdef ctSRVR

#ifndef ctCACHE_MEMORY
EXTSTR SEMAmut ct_MPsema;	/* multi-processor mutex */
#endif

EXTSTR pTEXT	pADMINu;
EXTSTR pTEXT	pADMINg;
EXTSTR pTEXT	pGUESTu;
EXTSTR pTEXT	pGUESTg;
EXTSTR pTEXT	pADMINw;
EXTSTR pTEXT	pADMINk;
EXTSTR NINT	ct_sesschg;
EXTSTR NINT	ct_fcrpvuln;	/* vulnerable to nobTRAN FCRP_ERR's */
EXTSTR NINT	ct_loclwarn;	/* server warning: remote file	    */
#ifdef ctFeatCOMM_IO_BLOCK
EXTSTR LONG	ctcomioblk;	/* Block All Comm I/O */
#endif
#ifdef ctFeatSTARTUP_LOGON_BLOCK
EXTSTR LONG	ctsublons;	/* Start Up Block Logons */
#ifdef ctSQLSRVR
EXTSTR TEXT	ctStartupBlockAllSqlLogons; /* Block all SQL logons at startup */
#endif
#endif
#ifdef ctFeatNEW_DEAD_CLIENT
EXTSTR LONG	ct_deadint;	/* dead client detection interval */
EXTSTR NINT	ct_deadclioff;	/* new dead client detection disabled for old client */
#endif
EXTSTR LONG	ct_prpriority;  /* server process priority */

#ifdef ctCMPLOG

#ifndef ctFeatSNAPSHOT
EXTSTR VRLEN	ctlogcmpfloor;	/* no log compression below this size	*/
EXTSTR VRLEN	ctlogcmpfactor;	/* compressed size must not exceed this
				   percent of input size		*/
#endif
#endif

#if defined(ctFeatOS_SECURITY_LDAP) || defined(ctFeatLDAP)
EXTSTR pTEXT	ctldapsrvr;	/* LDAP server name 			*/
EXTSTR NINT	ctldaptimeout;	/* LDAP connection timeout 		*/
EXTSTR pTEXT	ctldapbase;	/* LDAP base string 			*/
#endif
#ifdef ctFeatOS_SECURITY_LDAP
EXTSTR pTEXT	ctlogingrp;	/* Must be member of this group to login*/
#endif
#ifdef ctFeatLDAP
EXTSTR pTEXT	ctldapaid;	/* LDAP application ID			*/
EXTSTR pTEXT	ctldappfx;	/* LDAP login prefix 			*/
EXTSTR pTEXT	ctldapismgrp;	/* Must be member of this group for ISAM login */
EXTSTR pTEXT	ctldapsqlgrp;	/* Must be member of this group for SQL login */
EXTSTR ULONG	ctldapport;	/* LDAP server port number		*/
EXTSTR NINT	ctldapssl;	/* Use SSL for LDAP connection		*/
#ifdef ctFeatENCSTORE
#define MAX_LDAPAPPST	256
EXTSTR pTEXT	ctldapappst;	/* Application state info		*/
#endif
#endif
#ifdef ctFeatKEYXCHG
EXTSTR pVOID	ctkxparams;	/* Key exchange parameters		*/
EXTSTR NINT	ctkxlen;	/* Key exchange key length		*/
#endif
#if defined(ctFeatOPENSSL) && defined(ctSRVR)
EXTSTR CTSSLI	ctsslinf;	/* State information for SSL support	 */
#endif
#ifdef ctFeatPARTREPL
EXTSTR pCTFILE	crepart_host[MXU2]; /* partition host FCB pointer used to set
				    ** phost during member create */
#endif
#ifdef rtSRVR
EXTSTR pTEXT	rtuserlibname;	/* Name of RTUSER DLL/shared library to load */
#endif

#ifdef ctSQLSRVR
EXTSTR NINT ct_trdattr[MXU2];	/* thread attributes			*/
#ifdef ctSQL_SHMEM
EXTSTR TEXT ct_sqlcommp[MXU2];	/* SQL thread communication protocol	*/
#endif
#endif

#endif /* ctSRVR */

#if (defined(ctSRVR) || defined(ctBNDSRVR))
#ifdef ctDISTcounts
EXTSTR LONG	ctDISTcountsSec;/* interval between aggregate update	*/
#endif
#endif

#ifdef ctFeatDISTismcnt
EXTSTR NINT	ctisamcounterbuckets;	/* number of distributed ISAM counter buckets */
#endif

#ifdef ctFeatSNAPSHOT
EXTSTR LONG8	ctsnap_bsrvtim;	/* beginning of server operation highres*/
EXTSTR LONG8	ctsnap_bwrktim;	/* beginning of current func time intrvl*/
EXTSTR LONG8	ctsnap_bwrkbas;	/* cummulative func time intervals	*/
EXTSTR LONG8	cthr_trntim;	/* long transaction threshold in highres*/
EXTSTR ULONG	ctsnap_bsrvclk;	/* beg server operation based on cttime	*/
EXTSTR ULONG	ctsnap_trntim;	/* histogram width for tran time in usec*/
EXTSTR ULONG	ctperf_trntim;	/* long transaction threshold in msec	*/
EXTSTR LONG	ctsnap_time;	/* time interval for automatic snapshot */
EXTSTR NINT	ctsnap_tcnt;	/* snapshot thread count		*/
EXTSTR NINT	ctsnap_thid;	/* snapshot thread ID			*/
EXTSTR NINT	ctsnap_allusers;/* all users activated for snapshots	*/
EXTSTR NINT	ctsnap_allfiles;/* all files activated for snapshots	*/
EXTSTR NINT	ctsnap_wrktim;	/* Y/N: any work time measures made	*/
EXTSTR ULONG	ctsnap_loktim;	/* histogram width for lock wait in usec*/

#define ctMAXfnc	256

#define ctMAXsub	ctSEPLNGlimit

EXTSTR ctWRKSTT ct_fncwrk[ctMAXfnc + ctMAXsub];
EXTSTR ctWRKSTT ctufncwrk[MXU2][ctMAXfnc + ctMAXsub];
#ifdef ctFeatSNAPSHOTfncfil
/*
** ctWRKSTT_ARRAY_SIZE is the size in bytes of the array of ctWRKSTT structures
** allocated to store the function timings for one c-tree file.
*/
#define ctWRKSTT_ARRAY_SIZE ((ctMAXfnc + ctMAXsub) * ctSIZE(ctWRKSTT))
EXTSTR pctWRKSTT *ctffncwrk;	/* function counts and timings by file	*/
#endif
#endif

#ifdef GNSERVER
EXTSTR pDEDLOK ctdedlok;	/* pointer to deadlock detection array */
#endif

#ifdef MULTITRD

#ifdef ctMXLOGS

EXTERN pSEMA	ctpundsema;
#ifdef ctFeatDYNAMIC_DUMP
EXTERN pSEMA	ctpdmpsema;
#endif
EXTERN pSEMA	ctmemtrkpsem;
EXTERN pSEMA	ctpismema;
#ifdef ctFeatVIRTUAL_FILES
EXTERN pSEMA	ctpvtsema;
EXTERN pSEMA	ctpnmvsema;
#endif
EXTERN pSEMA	ctpavlsema;
EXTERN pSEMA	ctpchksema[ctMXLOGS];
EXTERN pSEMA	ctpabtsema[ctMXLOGS];
EXTERN pSEMA	ctpuhnsema;
EXTERN pSEMA    ctplflsema[ctMXLOGS];

#ifdef ctFeatSNAPSHOTtimer
EXTERN pSEMAmut ctplokmtx;
EXTERN pSEMAmut ctpxlkmtx;
#endif
#ifndef ctFeatGNSEMAhsh
EXTERN pSEMAmut ctpgnsema;
#endif
#ifdef ctFeatDEFER_OPNTRAN
EXTERN pSEMAmut ctpdotsema;
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
EXTERN pSEMAmut ctpcmprecmtx;	/* compression resource handle mutex */
#endif
EXTERN pSEMAmut ctpocsema;
EXTERN pSEMAmut ctptflsema;
EXTERN pSEMAmut ctpcpocsema[ctMXLOGS];
EXTERN pSEMAmut ctpllsema;
#if defined(ctFeatLOCKSTATS) && !defined(ctFeatLOCKSTATSopt)
#ifdef ctBEHAV_LLSEMA
EXTERN pSEMAmut ctplmsema;
#endif
#endif
#ifdef ctFeatVIRTUAL_FILES
EXTERN pSEMAmut ctpfacsema;
#endif
#ifdef UTRrwlock
EXTERN pRWLOCKmut ctputrsema;
#else
EXTERN pSEMAmut ctputrsema;
#endif
EXTERN pSEMAmut	ctpcomsema[ctMXLOGS];
#ifdef ctBEHAV_WORKsync
#ifdef ctBEHAV_WORKsyncRWL
EXTERN pRWLOCKmut ctpconcsema_rwl;
#endif
#else
EXTERN pSEMAmut ctpconcsema;
#endif
#ifndef ctFeatOPNCNTatomic
EXTERN pSEMAmut ctpopncsema;
#endif
#ifdef ctBEHAV_SEP_CONC
#ifdef C3Nrwlock
EXTERN pRWLOCKmut ctpc3ncsema;
#else
EXTERN pSEMAmut ctpc3ncsema;
#endif
EXTERN pSEMAmut ctpc4ncsema;
EXTERN pSEMAmut ctpc5ncsema;
EXTERN pSEMAmut ctpc6ncsema;
#endif
#ifdef CPCrwlock
EXTERN pRWLOCKmut ctpcpcsema;
#else
EXTERN pSEMAmut ctpcpcsema;
#endif
EXTERN pSEMAmut ctpMPsema;
EXTERN pSEMAmut ctpgvsema;
EXTERN pSEMAmut ctplogsema[ctMXLOGS];
#ifndef ctFeatDBSEMAhsh
EXTERN pSEMAmut	ctpdbsema;
#endif
#ifdef ctFeatSPLSEMA
EXTERN pSEMAmut ctpsplsema;
#endif
EXTERN pSEMAmut	ctplftsema[ctMXLOGS];
EXTERN pSEMAmut	ptranacsema[ctMXLOGS];
EXTERN pSEMAmut ctpnupmtx;
EXTERN pSEMAmut ctpdupmtx;
EXTERN pSEMAmut ctpnutmtx[ctMXLOGS];
EXTERN pSEMAmut ctpdutmtx[ctMXLOGS];
EXTERN pSEMAmut	ctpdcmsema[ctMXLOGS];
EXTERN pSEMAmut	ctstrfilpsem[ctMXLOGS];
#ifdef ctFeatGNSEMAhsh
#ifndef ctFeatAVLISTnum
EXTERN SEMAmut ctavlsema;
#endif
#ifdef ctFeatBLKSEMA
EXTERN pTEXT	 ctpgnsemaBKb;
EXTERN pSEMAmut *ctpgnsemaBK;
#endif
#endif
#ifdef ctFeatDBSEMAhsh
#ifndef ctFeatDALISTnum
EXTERN SEMAmut ctdavsema;
#endif
#endif
EXTERN SEMAtim ctbroadcastblk;
EXTERN pSEMAtim	ctdnodepsema;
#ifdef ctFeatTRAN_TIMEOUT
EXTERN pSEMAtim	ctptrntimsema;
#endif
#ifdef ctFeatREQUEST_TIME_MONITOR
EXTERN pSEMAtim ctprqtmonsema;
#endif
#ifdef ctDISTcounts
EXTERN pSEMAtim ctpDISTcountsWat;
#endif
EXTERN pSEMAtim	ctpsnapsema;
#ifdef ctBEHAV_CHKPDFC
EXTERN pSEMAtim	ctpchkpblk[ctMXLOGS];
#endif

#ifdef ctBEHAV_MXLFW
EXTERN pSEMAblk	ctplfwsema[ctMXLOGS][ctMXLFW + 1];
#else
EXTERN pSEMAblk	ctplfwsema[ctMXLOGS];
#endif
#ifdef ctDUMPorQUIET
EXTERN pSEMAblk	ctp1dmsema;
#endif

#else /* ~ctMXLOGS */

EXTSTR pSEMA	ctpundsema;	/* 00 */
/*
EXTSTR pSEMA	available	   01
*/
#ifdef ctFeatDYNAMIC_DUMP
#ifdef ctFeatDMPSEMArwlock
EXTSTR ctRWLOCK ct_dmpsema;	/* dynamic dump reader/writer lock */
EXTSTR pctRWLOCK ctpdmpsema;
/*
EXTSTR pSEMA	available	   02
*/
#else
EXTSTR pSEMA	ctpdmpsema;	/* 02 */
#endif
#else
/*
EXTSTR pSEMA	available	   02
*/
#endif
/*
EXTSTR pSEMA	available	   03
*/
EXTSTR pSEMA	ctmemtrkpsem;	/* 04 */
EXTSTR pSEMA	ctpismema;	/* 05 */
/*
EXTSTR pSEMA	available	   06
*/
#ifdef ctFeatVIRTUAL_FILES
EXTSTR pSEMA	ctpvtsema;	/* 07 */
EXTSTR pSEMA	ctpnmvsema;	/* 08 */
#endif
EXTSTR pSEMA	ctpavlsema;	/* 09 */
/*
EXTSTR pSEMA	available	   10
*/
EXTSTR pSEMA	ctpchksema;	/* 11 */
EXTSTR pSEMA	ctpabtsema;	/* 12 */
/*
EXTSTR pSEMA	available	   13
*/
EXTSTR pSEMA	ctpuhnsema;	/* 14 */
EXTSTR pSEMA    ctplflsema;	/* 15 */

#ifndef ctFeatGNSEMAhsh
EXTSTR pSEMAmut ctpgnsema;	/* 00 */
#endif
#ifdef ctFeatFILELISTrwl
#ifdef ctFeatFILELISTmulti
EXTSTR ctRWLOCK	ctrwlflst[NUMBER_OF_FILE_LISTS];	/* file list reader/writer lock */
#else
EXTSTR ctRWLOCK	ctrwlflst;	/* file list reader/writer lock */
#endif
#endif
EXTSTR pSEMAmut ctpocsema;	/* 01 */
EXTSTR pSEMAmut ctpllsema;	/* 02 */
#ifdef ctFeatVIRTUAL_FILES
EXTSTR pSEMAmut ctpfacsema;	/* 03 */
#endif
#ifdef UTRrwlock
EXTSTR pRWLOCKmut ctputrsema;
#else
EXTSTR pSEMAmut ctputrsema;	/* 04 */
#endif
EXTSTR pSEMAmut	ctpcomsema;	/* 05 */
#ifdef ctBEHAV_WORKsync
#ifdef ctBEHAV_WORKsyncRWL
EXTSTR pRWLOCKmut ctpconcsema_rwl;
#endif
#else
EXTSTR pSEMAmut ctpconcsema;	/* 06 */
#endif
EXTSTR pSEMAmut ctpMPsema;	/* 07 */
EXTSTR pSEMAmut ctpgvsema;	/* 08 */
EXTSTR pSEMAmut ctplogsema;	/* 09 */
#ifdef ctFeatDBSEMAhsh
#ifdef ctFeatSPLSEMA
EXTSTR pSEMAmut	ctpsplsema;	/* 10 */
#endif
#else
EXTSTR pSEMAmut	ctpdbsema;	/* 10 */
#endif
EXTSTR pSEMAmut	ctplftsema;	/* 11 */
EXTSTR pSEMAmut	ptranacsema;	/* 12 */
#ifdef ctBEHAV_BLM
EXTSTR pSEMAmut ctpnupmtx;	/* 13 */
EXTSTR pSEMAmut ctpdupmtx;	/* 14 */
EXTSTR pSEMAmut ctpnutmtx;	/* 15 */
EXTSTR pSEMAmut ctpdutmtx;	/* 16 */
#endif
EXTSTR pSEMAmut	ctpdcmsema;	/* 17 */
EXTSTR pSEMAmut	ctstrfilpsem;	/* 18 */
#ifndef ctFeatOPNCNTatomic
EXTSTR pSEMAmut ctpopncsema;	/* 19 */
#endif
EXTSTR pSEMAmut ctptflsema;	/* 20 */

#ifdef ctFeatSNAPSHOTtimer
EXTSTR pSEMAmut ctplokmtx;	/* 21 */
EXTSTR pSEMAmut ctpxlkmtx;	/* 22 */
#endif
#if defined(ctFeatLOCKSTATS) && !defined(ctFeatLOCKSTATSopt)
#ifdef ctBEHAV_LLSEMA
EXTSTR pSEMAmut	ctplmsema;	/* 23 */
#endif
#endif
#ifdef ctFeatGNSEMAhsh
#ifndef ctFeatAVLISTnum
EXTSTR SEMAmut ctavlsema;
#endif
#ifdef ctFeatBLKSEMA
EXTSTR pTEXT	 ctpgnsemaBKb;
EXTSTR pSEMAmut *ctpgnsemaBK;
#endif
#endif
#ifdef ctFeatDBSEMAhsh
#ifndef ctFeatDALISTnum
EXTSTR SEMAmut ctdavsema;
#endif
#ifdef ctFeatSPLSEMA
EXTSTR SEMAmut ct_splsema;
#endif
#endif

#ifdef ctBEHAV_SEP_CONC
#ifdef C3Nrwlock
EXTSTR pRWLOCKmut ctpc3ncsema;
#else
EXTSTR pSEMAmut ctpc3ncsema;	/* 24 */
#endif
EXTSTR pSEMAmut ctpc4ncsema;	/* 25 */
EXTSTR pSEMAmut ctpc5ncsema;	/* 26 */
EXTSTR pSEMAmut ctpc6ncsema;	/* 27 */
#endif
#ifdef CPCrwlock
EXTSTR pRWLOCKmut ctpcpcsema;
#else
EXTSTR pSEMAmut ctpcpcsema;	/* 28 */
#endif
#ifdef ctFeatDEFER_OPNTRAN
EXTSTR pSEMAmut ctpdotsema;	/* 29 */
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
EXTSTR pSEMAmut ctpcmprecmtx;	/* 30 */
#endif
EXTSTR SEMAtim ctbroadcastblk;
EXTSTR pSEMAtim	ctdnodepsema;	/* 00 */
EXTSTR pSEMAtim	ctpsnapsema;	/* 01 */
#ifdef ctFeatTRAN_TIMEOUT
EXTSTR pSEMAtim	ctptrntimsema;	/* 02 */
#endif
#ifdef ctFeatREQUEST_TIME_MONITOR
EXTSTR pSEMAtim ctprqtmonsema;	/* 03 */
#endif
#ifdef ctDISTcounts
EXTSTR pSEMAtim ctpDISTcountsWat; /* 04 */
#endif
#ifdef ctBEHAV_CHKPDFC
EXTSTR pSEMAtim	ctpchkpblk;	/* 05 */
#endif

#ifdef ctBEHAV_MXLFW
EXTSTR pSEMAblk	ctplfwsema[ctMXLFW + 1];
				/* 00  thru ctMXLFW */
#ifdef ctDUMPorQUIET
EXTSTR pSEMAblk	ctp1dmsema;	/* ctMXLFW + 01 */
#endif
#else
EXTSTR pSEMAblk	ctplfwsema;	/* 00 */
#ifdef ctDUMPorQUIET
EXTSTR pSEMAblk	ctp1dmsema;	/* 01 */
#endif
#endif

#endif /* ~ctMXLOGS */

#ifdef ctSTATIC_SEMA
EXTSTR SEMA ctsresema[MXU2];
#endif

EXTSTR NINT ctfilcremode;	/* File create mode (e.g., 0666) */
EXTSTR NINT ctmaxsqlisolvl;	/* Maximum SQL isolation level (MAX_SQL_ISOLATION_LEVEL keyword) */
#ifndef ctBEHAV_PERMMASK_INHERIT
EXTSTR NINT ctinhfilprm;	/* INHERIT_FILE_PERMISSIONS setting */
#endif
#ifdef ctFeatAUTO_LOCK_RETRY
EXTSTR NINT ctlokretry;		/* AUTO_LOCK_RETRY setting */
EXTSTR NINT ctlokretrysleep;	/* AUTO_LOCK_RETRY_SLEEP setting */
#endif
#ifdef ctSRVR
EXTSTR NINT ctufilmod;		/* File mode attributes to apply to all file create/open calls */
#endif
#ifdef ctFeatCONNGROUP
EXTSTR NINT ctcusers;		/* current number of counted connections */
#endif
#ifdef ctFeatCOUNT_FCWORKERS
EXTSTR ULONG ctWorkerCount; /* current number of worker connections */
EXTSTR ULONG ctMaxWorkerCount; /* maximum number of worker connections */
#endif

#ifdef ctPortDIAD_FS
EXTSTR	fs_fopen_t	ctfs_fopen;
EXTSTR	fs_fclose_t	ctfs_fclose;
EXTSTR	fs_fseek_t	ctfs_fseek;
EXTSTR	fs_fread_t	ctfs_fread;
EXTSTR	fs_fwrite_t	ctfs_fwrite;
EXTSTR	fs_filelength_t	ctfs_filelength;
EXTSTR	fs_fileno_t	ctfs_fileno;
EXTSTR	fs_remove_t	ctfs_remove;
EXTSTR	fs_ftell_t	ctfs_ftell;
EXTSTR	fs_rename_t	ctfs_rename;
#endif

#ifdef ctFeatTRANREPL
EXTSTR	pVOID		ctClientHandle; /* Handle to dynamically loaded client module */
EXTSTR  pTEXT		ctClientModuleName; /* Name of dynamically loaded client module */
EXTSTR  pTEXT		ctClientServerName; /* Name of master c-tree Server */
EXTSTR	TEXT		ctReplMapFile[MAX_NAME]; /* Name of REPL_MAPPINGS file */
#endif

#ifdef ctFeatMEMFILE
EXTSTR	LONG		ctMEMFILEmaxbins; /* max hash bins for memory file */
#endif
#ifdef ctFeatCRITSECTSPIN
EXTSTR	LONG		critsectspin;	  /* critical section spin limit   */
#endif
EXTSTR  LONG8		trnovrflwthr;	  /* transaction number overflow threshold */
#ifdef ctFeatLOGONSEC
EXTSTR  LONG		ctseclgn;	  /* secure logon setting */
#endif
#ifdef ctFeatVLEN_ERRretry
EXTSTR	LONG		ctVLEN_ERRlimit;  /* VLEN_ERR retry limit */
#endif
#ifdef ctFeatKEEPOPENclose
EXTSTR	LONG		ctKEEPOPENcloselimit; /* KEEPOPEN close retry limit */
#endif

#ifdef CTPERM /* this block contains code for internal use only */

#ifdef ctFeatOPTIMIZE_FILE_OPEN
EXTSTR	LONG		ctpforetrylimit; /* pending file open retry limit */
EXTSTR	pPFOHSH		ctPendingFileOpenHashTable;	/* pending open file name hash table	 */
EXTSTR	UINT		ctPendingFileOpenHashBins;	/* pending open file name hash bin count */
#ifdef ctFeatSYSTEM_FILE_ID_LIST
EXTSTR	pSYSIDHSH	ctSysidHashTable; /* hash table for storing system file ids */
EXTSTR	UINT		ctSysidHashBins; /* number of hash bins in system file id hash table */
EXTSTR	RWLOCKmut	ctSysidHashTableRwlock; /* reader/writer lock for sytsem file id hash table */
EXTSTR	ULONG		numberOfSystemFileIdListEntries; /* number of entries in system file id hash table */
EXTSTR	TEXT		systemFileIdList; /* SYSTEM_FILE_ID_LIST configuration option */
#endif
#endif
#ifdef ctBEHAV_CLEANUP_ABLIST_ON_ABORT
EXTSTR	TEXT		cleanupAblistOnAbort; /* CLEANUP_ABLIST_ON_ABORT configuration option */
#endif

#endif /* CTPERM - end of block containing code for internal use only */

#ifdef ctSQLSRVR
EXTSTR	NINT		ctsqlpartopencost;	/* SQL cost value for opening partition */
#endif
#ifdef ctFeatMEMTRACK
#ifdef ctPortWIN32
EXTSTR	pRtlCaptureStackBackTrace_t
			pRtlCaptureStackBackTrace; /* Function pointer for RtlCaptureStackBackTrace */
#endif
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
EXTSTR	NINT		def_cmprec_type;
EXTSTR	NINT		def_cmprec_vrsn;
EXTSTR	UINT		def_cmprec_plen;
EXTSTR	pTEXT		def_cmprec_parm;
EXTSTR	TEXT		def_cmprec_dll[MAX_NAME];
#endif
#ifdef ctFeatINTERMEDIATE_BLOCK_PAGING
EXTSTR	NINT		intblkpgs; /* use data cache pages for intermediate
				   block I/O operations to ensure consistency */
#endif
#ifdef ctBEHAV_AUTOTRAN_ON_CREATE
EXTSTR	NINT		atotrncre; /* automatic transaction on ISAM file create */
#endif
#ifdef ctBEHAV_NONTRAN_FILESYS_FLUSH_OFF
EXTSTR	NINT		ctnontranfsflushoff; /* no file system flush for non-TRNLOG files */
#endif
#ifdef ctFeatSNAPSHOT
EXTSTR	NINT		ssOnShutdown; /* SNAPSHOT_SHUTDOWN  and server initialized */
#endif
#ifdef ctFeatSRVR_STRUCT
} ctgs; /* end of global variable structure */

/*
** Redefine global variable names to structure members.
*/
#define pULI			ctgs.pULI
#define commCmds		ctgs.commCmds
#define commGbls		ctgs.commGbls
#define redolist_tot		ctgs.redolist_tot
#define redolist_cur		ctgs.redolist_cur
#define redolist_ptr		ctgs.redolist_ptr
#define cmprec_ptr		ctgs.cmprec_ptr
#define cmprec_cur		ctgs.cmprec_cur
#define cmprec_tot		ctgs.cmprec_tot
#define dedlst_tot		ctgs.dedlst_tot
#define dedlst_cur		ctgs.dedlst_cur
#define dedlst_avl		ctgs.dedlst_avl
#define dedlst_ptr		ctgs.dedlst_ptr
#define ksgcurs			ctgs.ksgcurs
#define ksgtots			ctgs.ksgtots
#define ksglsts			ctgs.ksglsts
#define align_override		ctgs.align_override
#ifdef ctFeatRTG_API
#define  rtgmsgcbfnc  	        ctgs.rtgmsgcbfnc 	/* RTG message callback function */
#define  rtgmsgcbusrctx  	ctgs.rtgmsgcbusrctx 	/* RTG message callback user context ptr */
#endif
#define appalign		ctgs.sappalign
#define ctlist			ctgs.ctlist
#define ctsrvthrd		ctgs.ctsrvthrd
#define ctQTthrd		ctgs.ctQTthrd
#define ctQTthrdabn		ctgs.ctQTthrdabn
#define ctQTlogbuf		ctgs.ctQTlogbuf
#define ctQTvalidusrcnt		ctgs.ctQTvalidusrcnt
#define ctQTaction		ctgs.ctQTaction
#define ctQTclnup		ctgs.ctQTclnup
#define ctQTstart		ctgs.ctQTstart
#define ctQTpslt		ctgs.ctQTpslt
#define ctQTpslp		ctgs.ctQTpslp
#define ctQTpatr		ctgs.ctQTpatr
#define ctQTpatp		ctgs.ctQTpatp
#define ctQTwpus		ctgs.ctQTwpus
#define ctQTwpnd		ctgs.ctQTwpnd
#define ctlogtmp		ctgs.ctlogtmp
#define ctgv_thd		ctgs.ctgv_thd
#define ctlogtmpcpyutl		ctgs.ctlogtmpcpyutl
#define ctupdnod		ctgs.ctupdnod
#define ctupddat		ctgs.ctupddat
#define ctupdnod_tail		ctgs.ctupdnod_tail
#define ctupddat_tail		ctgs.ctupddat_tail
#define ctcomdat		ctgs.ctcomdat
#define ctcomnod		ctgs.ctcomnod
#define ctuptnod		ctgs.ctuptnod
#define ctuptdat		ctgs.ctuptdat
#define cpflscnt		ctgs.cpflscnt
#define cpucountmode		ctgs.cpucountmode
#define ct_wfsize		ctgs.ct_wfsize
#define ct_wf			ctgs.ct_wf
#define ct_vf			ctgs.ct_vf
#define spcustmem		ctgs.spcustmem
#define scustops		ctgs.scustops
#define ctkillquiet		ctgs.ctkillquiet
#define dbg_hsema		ctgs.dbg_hsema
#define ct_repmtx		ctgs.ct_repmtx
#define filmtx_mtx		ctgs.filmtx_mtx
#define ct_usrbmtx		ctgs.ct_usrbmtx
#define ctSsemap		ctgs.ctSsemap
#define ctXsemap		ctgs.ctXsemap
#define ctTsemap		ctgs.ctTsemap
#define ctBsemap		ctgs.ctBsemap
#define ctlsemab		ctgs.ctlsemab
#define ctSsemab		ctgs.ctSsemab
#define ctXsemab		ctgs.ctXsemab
#define ctTsemab		ctgs.ctTsemab
#define ctBsemab		ctgs.ctBsemab
#ifdef ctSEMW
#define ctWsemap		ctgs.ctWsemap
#define ctWsemab		ctgs.ctWsemab
#endif
#define ct_blkb			ctgs.ct_blkb
#define im_blkb			ctgs.im_blkb
#define fb_blkb			ctgs.fb_blkb
#ifdef ctBEHAV_WORKsync
#define ctpconcsema		ctgs.ctpconcsema
#define ctbconcsema		ctgs.ctbconcsema
#endif
#define ctdnode_sema		ctgs.ctdnode_sema
#define ctstrfil_sem		ctgs.ctstrfil_sem
#define ctmemtrk_sem		ctgs.ctmemtrk_sem
#define sct_usrsi		ctgs.sct_usrsi
#define cthugeseg		ctgs.cthugeseg
#define cthugemax		ctgs.cthugemax
#define ctash			ctgs.ctash
#define ctchkidle		ctgs.ctchkidle
#define nodedtime		ctgs.nodedtime
#define nodertime		ctgs.nodertime
#define ctlokch			ctgs.ctlokch
#define ctlokup			ctgs.ctlokup
#define ctlokdn			ctgs.ctlokdn
#define presync_limit		ctgs.presync_limit
#define ctlokfl			ctgs.ctlokfl
#define ct_gstnot		ctgs.ct_gstnot
#define ct_blkadm		ctgs.ct_blkadm
#define ctchktran		ctgs.ctchktran
#define ctqchkpRunning		ctgs.ctqchkpRunning
#define ctmaxdatkey		ctgs.ctmaxdatkey
#define ctmaxkeyseg		ctgs.ctmaxkeyseg
#define ctmaxusrfil		ctgs.ctmaxusrfil
#define ctcacheline		ctgs.ctcacheline
#define ctrunlength		ctgs.ctrunlength
#define ctdnodeRunning		ctgs.ctdnodeRunning
#define cttrntimoutRunning	ctgs.cttrntimoutRunning
#define ctrqtmonRunning		ctgs.ctrqtmonRunning
#define ctrqtmonint_new		ctgs.ctrqtmonint_new
#define ctcpulmtRunning		ctgs.ctcpulmtRunning
#define ctbroadcastRunning	ctgs.ctbroadcastRunning
#define ctShutdownStatus	ctgs.ctShutdownStatus
#define ctProcessExitCmd	ctgs.ctProcessExitCmd
#define ctioblksiz		ctgs.ctioblksiz
#define ctioerrblksiz		ctgs.ctioerrblksiz
#define ctioerrblkretry		ctgs.ctioerrblkretry
#define ctioerrblksleep		ctgs.ctioerrblksleep
#define ctdyndmplopdfr		ctgs.ctdyndmplopdfr
#define ctdyndmplopdfrint	ctgs.ctdyndmplopdfrint
#define ctxfrfil_api		ctgs.ctxfrfil_api
#define ctvsswriter		ctgs.ctvsswriter
#define ctreplsrlAllowUnqkey	ctgs.ctreplsrlAllowUnqkey
#define ctreplsrlUseMaster	ctgs.ctreplsrlUseMaster
#define ctreplsrlUseSource	ctgs.ctreplsrlUseSource
#define ctreplidfUseMaster	ctgs.ctreplidfUseMaster
#define ctreplidfUseSource	ctgs.ctreplidfUseSource
#define ctlogtmpcpyslp		ctgs.ctlogtmpcpyslp
#define ctlogtmpcpypct		ctgs.ctlogtmpcpypct
#define ctKEEPOPENcloseRunning	ctgs.ctKEEPOPENcloseRunning
#define ctDISTcountsRunning	ctgs.ctDISTcountsRunning
#define ctDISKFULLactionRunning	ctgs.ctDISKFULLactionRunning
#define ctrbktflsRunning	ctgs.ctrbktflsRunning
#define ct_rbktflsq		ctgs.ct_rbktflsq
#define ctsyslgRunning		ctgs.ctsyslgRunning
#define ct_channels		ctgs.ct_channels
#define ctlog_pagesize		ctgs.ctlog_pagesize
#define cthr_concurrency	ctgs.cthr_concurrency
#define ctqmsgRunning		ctgs.ctqmsgRunning
#define ctqfncRunning		ctgs.ctqfncRunning
/*
#define ctworktyp		ctgs.ctworktyp
*/
#define ct_mq			ctgs.ct_mq
#define ct_smon			ctgs.ct_smon
#define ct_trdmon		ctgs.ct_trdmon
#define ctadmfiles		ctgs.ctadmfiles
#define ctmaxktouse		ctgs.ctmaxktouse
#define ctmaxhandles		ctgs.ctmaxhandles
#define InitRWLock		ctgs.InitRWLock
#define AcqRWLockExc		ctgs.AcqRWLockExc
#define AcqRWLockShr		ctgs.AcqRWLockShr
#define TryRWLockExc		ctgs.TryRWLockExc
#define TryRWLockShr		ctgs.TryRWLockShr
#define RelRWLockExc		ctgs.RelRWLockExc
#define RelRWLockShr		ctgs.RelRWLockShr
#define DestroyRWLock		ctgs.DestroyRWLock
#ifndef ctFeatSNAPSHOT
#define ct_udefer_thld		ctgs.ct_udefer_thld
#define ct_udefer_64yd		ctgs.ct_udefer_64yd
#define ctITIMlimit		ctgs.ctITIMlimit
#define ctITIMdefer		ctgs.ctITIMdefer
#define ctredcmtdfr		ctgs.ctredcmtdfr
#define ctrqtmonint		ctgs.ctrqtmonint
#endif
#define ctchkcfg		ctgs.ctchkcfg
#define did_preconfig		ctgs.did_preconfig
#define ct_latchspin		ctgs.ct_latchspin
#define ct_latchsleep		ctgs.ct_latchsleep
#define ctevalsem		ctgs.ctevalsem
#define ctdatbuf		ctgs.ctdatbuf
#define ctrepredbufsiz		ctgs.ctrepredbufsiz
#define ctskpaddwrk		ctgs.ctskpaddwrk
#define ctavlistcnt		ctgs.ctavlistcnt
#define ctdalistcnt		ctgs.ctdalistcnt
#define useEmptyList		ctgs.useEmptyList
#define ctdalistsiz		ctgs.ctdalistsiz
#if 0
#define nopndg_cacstt		ctgs.nopndg_cacstt
#define nopndg_cacmtc		ctgs.nopndg_cacmtc
#define nopndg_cntemp		ctgs.nopndg_cntemp
#define nopndg_empstt		ctgs.nopndg_empstt
#define nopndg_bufstt		ctgs.nopndg_bufstt
#define nopndg_bufmtc		ctgs.nopndg_bufmtc
#define nopndg_buflok		ctgs.nopndg_buflok
#define nopndg_tstBmtc		ctgs.nopndg_tstBmtc
#define nopndg_bufstt_get	ctgs.nopndg_bufstt_get
#define nopndg_bufmtc_get	ctgs.nopndg_bufmtc_get
#define nopndg_tstBmtc		ctgs.nopndg_tstCmtc
#define nopndg_bufstt_get	ctgs.nopndg_cacstt_get
#define nopndg_bufmtc_get	ctgs.nopndg_cacmtc_get
#endif /* 0 ???? */
#define ctcachestatary		ctgs.ctcachestatary
#define ctcachestatbas		ctgs.ctcachestatbas
#define ctcachestatcnt		ctgs.ctcachestatcnt
#define ctcachestatsiz		ctgs.ctcachestatsiz
#define ctdnodeShutdownLimit	ctgs.ctdnodeShutdownLimit
#define ctshmemdir		ctgs.ctshmemdir
#define ctshmemprm		ctgs.ctshmemprm
#define ctshmemgrp		ctgs.ctshmemgrp
#define ctshmemkeyism		ctgs.ctshmemkeyism
#define ctshmemkeysql		ctgs.ctshmemkeysql
#define ct_maxlogdefer		ctgs.ct_maxlogdefer
#define ct_updmrk_splitchk	ctgs.ct_updmrk_splitchk
#define cttoptim		ctgs.cttoptim
#define ct_maxlogdefer_Running	ctgs.ct_maxlogdefer_Running
#define ctnobuflogs		ctgs.ctnobuflogs
#define ctunbufio		ctgs.ctunbufio
#define ctmstkeyfil		ctgs.ctmstkeyfil
#define ctkepopnfls		ctgs.ctkepopnfls
#define ctla_ptr		ctgs.ctla_ptr
#define ctfmru			ctgs.ctfmru
#define ct_mru			ctgs.ct_mru
#define ctfcbhdr		ctgs.ctfcbhdr
#define ctfcbusr		ctgs.ctfcbusr
#define ctprtestlimit		ctgs.ctprtestlimit
#define ctprtestpct		ctgs.ctprtestpct
#define ctfilblkcnt		ctgs.ctfilblkcnt
#define ct_fnhash		ctgs.ct_fnhash
#define ct_fnbins		ctgs.ct_fnbins
#define ct_llhash		ctgs.ct_llhash
#define ct_llbins		ctgs.ct_llbins
#define ctautomkdir		ctgs.ctautomkdir
#define ct_btree		ctgs.ct_btree
#define ct_dbufr		ctgs.ct_dbufr
#define ct_key			ctgs.ct_key
#define ct_fcbstk		ctgs.ct_fcbstk
#define ct_dat			ctgs.ct_dat
#define ct_vat			ctgs.ct_vat
#define ct_dfdef		ctgs.ct_dfdef
#define ct_dfadef		ctgs.ct_dfadef
#define filmtx_ary		ctgs.filmtx_ary
#define ct_ussanc		ctgs.ct_ussanc
#define sctshdmem		ctgs.sctshdmem
#define sctusrsum		ctgs.sctusrsum
#define sctusrtot		ctgs.sctusrtot
#define ctsig_rdy		ctgs.ctsig_rdy
#define ctusrsig_rdy		ctgs.ctusrsig_rdy
#define ctsig_mir		ctgs.ctsig_mir
#define ctsig_dwn		ctgs.ctsig_dwn
#define ctusrsig_dwn		ctgs.ctusrsig_dwn
#define ct_allsup		ctgs.ct_allsup
#define ct_logsup		ctgs.ct_logsup
#define ct_logaug		ctgs.ct_logaug
#ifndef ctBEHAV_CHECK_ICU_COLLATOR_VERSION
#define kseg_icuv		ctgs.kseg_icuv
#endif
#define kseg_icuE		ctgs.kseg_icuE
#define kseg_icuD		ctgs.kseg_icuD
#define ct_atimout		ctgs.ct_atimout
#define ct_dtimout		ctgs.ct_dtimout
#ifndef ctFeatSNAPSHOT
#define ct_compflg		ctgs.ct_compflg
#define ct_compflg2		ctgs.ct_compflg2
#define ct_compflg3		ctgs.ct_compflg3
#define ct_compflg4		ctgs.ct_compflg4
#define ct_compflg5		ctgs.ct_compflg5
#define ct_diagflg		ctgs.ct_diagflg
#define ct_diagflg2		ctgs.ct_diagflg2
#define ct_diagflg3		ctgs.ct_diagflg3
#endif
#define ctclrlop		ctgs.ctclrlop
#define ctflslop		ctgs.ctflslop
#define ctmemlmt		ctgs.ctmemlmt
#define ctmemtot		ctgs.ctmemtot
#define ctmemusr		ctgs.ctmemusr
#define ctmemup			ctgs.ctmemup
#define ctmemdn			ctgs.ctmemdn
#define ctmemup			ctgs.ctmemup
#define ctmemdn			ctgs.ctmemdn
#define ctmemch			ctgs.ctmemch
#define ctmemtrk_up		ctgs.ctmemtrk_up
#define ctmemtrk_dn		ctgs.ctmemtrk_dn
#define ctmemtrk_ch		ctgs.ctmemtrk_ch
#define ctmemtrk_net		ctgs.ctmemtrk_net
#define ct_qblock		ctgs.ct_qblock
#define ct_gstmem		ctgs.ct_gstmem
#define ct_timout		ctgs.ct_timout
#define ct_usrmrl		ctgs.ct_usrmrl
#define ct_disklmt		ctgs.ct_disklmt
#define ct_disklmt		ctgs.ct_disklmt
#define ct_ribs			ctgs.ct_ribs
#define ct_ii			ctgs.ct_ii
#define ct_ii_nsT		ctgs.ct_ii_nsT
#define ct_ii_nsN		ctgs.ct_ii_nsN
#define ct_ip			ctgs.ct_ip
#define ct_abseq		ctgs.ct_abseq
#define ct_abnod		ctgs.ct_abnod
#define ct_cmnod		ctgs.ct_cmnod
#define ct_cmdat		ctgs.ct_cmdat
#define ct_cmnod2		ctgs.ct_cmnod2
#define ct_cmdat2		ctgs.ct_cmdat2
#define ct_cmnodp		ctgs.ct_cmnodp
#define ct_cmdatp		ctgs.ct_cmdatp
#define ct_cmnod2_ptr		ctgs.ct_cmnod2_ptr
#define ct_cmdat2_ptr		ctgs.ct_cmdat2_ptr
#define ct_cmnod2_pre		ctgs.ct_cmnod2_pre
#define ct_cmdat2_pre		ctgs.ct_cmdat2_pre
#define ct_cmflg2		ctgs.ct_cmflg2
#define ct_cmnod2_flg		ctgs.ct_cmnod2_flg
#define ct_cmdat2_flg		ctgs.ct_cmdat2_flg
#define ct_numvi		ctgs.ct_numvi
#define ct_statflg		ctgs.ct_statflg
#define ct_sysviewT		ctgs.ct_sysviewT
#define ct_sysviewN		ctgs.ct_sysviewN
#define ct_langflg		ctgs.ct_langflg
#define ctquemon		ctgs.ctquemon
#define ctsusers		ctgs.ctsusers
#define ctclsfil		ctgs.ctclsfil
#define ctclspnd		ctgs.ctclspnd
#define ct_wpf			ctgs.ct_wpf
#define ct_opf			ctgs.ct_opf
#define ct_gpfcnt		ctgs.ct_gpfcnt
#define ctstatus_size		ctgs.ctstatus_size
#define ctisolev		ctgs.ctisolev
#define ctclrchk		ctgs.ctclrchk
#define ctstatus_purge		ctgs.ctstatus_purge
#define ctlstfrq		ctgs.ctlstfrq
#define ctbpfx_level		ctgs.ctbpfx_level
#define ctdbgDelay		ctgs.ctdbgDelay
#define dbgfixbuf		ctgs.dbgfixbuf
#define dbgfixcac		ctgs.dbgfixcac
#define ct_tmpseq		ctgs.ct_tmpseq
#define ct_dftot		ctgs.ct_dftot
#define ct_dfnum		ctgs.ct_dfnum
#define ct_dfatot		ctgs.ct_dfatot
#define ct_dfanum		ctgs.ct_dfanum
#define memsubflg		ctgs.memsubflg
#define filmtx_tot		ctgs.filmtx_tot
#define filmtx_num		ctgs.filmtx_num
#define ctmtcsegflg		ctgs.ctmtcsegflg
#define ctnonsegflg		ctgs.ctnonsegflg
#define ctatotrnlgt		ctgs.ctatotrnlgt
#define ctmiroff		ctgs.ctmiroff
#define ctosIOlok		ctgs.ctosIOlok
#define ctdedmon		ctgs.ctdedmon
#define ctfncmon		ctgs.ctfncmon
#define ctchkmon		ctgs.ctchkmon
#define ct_usstot		ctgs.ct_usstot
#define ct_ussnum		ctgs.ct_ussnum
#define ct_fhlimit		ctgs.ct_fhlimit
#define cthshift		ctgs.cthshift
#define ct_dq			ctgs.ct_dq
#define ct_rq			ctgs.ct_rq
#define ct_kocq			ctgs.ct_kocq
#define ct_dfridxq		ctgs.ct_dfridxq
#define ct_cq			ctgs.ct_cq
#define ct_iq			ctgs.ct_iq
#define ct_id			ctgs.ct_id
#define ctidle			ctgs.ctidle
#define nsplit			ctgs.nsplit
#define cthghflx		ctgs.cthghflx
#define ctfnz			ctgs.ctfnz
#define ct_avlstk		ctgs.ct_avlstk
#define ct_totkep		ctgs.ct_totkep
#define ct_lq			ctgs.ct_lq
#define ct_sq			ctgs.ct_sq
#define ctfncfp			ctgs.ctfncfp
#define ct_tmppth		ctgs.ct_tmppth
#define ctlogmemanc		ctgs.ctlogmemanc
#define ctrebhed		ctgs.ctrebhed
#define ctcmphed		ctgs.ctcmphed
#define ctmirhed		ctgs.ctmirhed
#define ctiblhed		ctgs.ctiblhed
#define ctlogchklmt		ctgs.ctlogchklmt
#define ct_trnhghmrk		ctgs.ct_trnhghmrk
#define prv_logser		ctgs.prv_logser
#define prv_chkpos		ctgs.prv_chkpos
#define prv_prvpos		ctgs.prv_prvpos
#define ct_chktrd		ctgs.ct_chktrd
#define ctfstr			ctgs.ctfstr
#define ctnewlogs		ctgs.ctnewlogs
#define ct_lfltrd		ctgs.ct_lfltrd
#define ctlflwait		ctgs.ctlflwait
#define ct_shbins		ctgs.ct_shbins
#define ct_shbyts		ctgs.ct_shbyts
#define ct_tryprvchk		ctgs.ct_tryprvchk
#define ctsuplog		ctgs.ctsuplog
#define ctsuplogsync		ctgs.ctsuplogsync
#define ctfwdned		ctgs.ctfwdned
#define ct_lhbins		ctgs.ct_lhbins
#define ct_lhbinx		ctgs.ct_lhbinx
#define ct_lhLoadF		ctgs.ct_lhLoadF
#define ct_lhRehashF		ctgs.ct_lhRehashF
#define ct_lhMaxBins		ctgs.ct_lhMaxBins
#define ct_ulMaxBins		ctgs.ct_ulMaxBins
#define ct_lhNoShrink		ctgs.ct_lhNoShrink
#define ct_ulNoShrink		ctgs.ct_ulNoShrink
#define ct_shbinx		ctgs.ct_shbinx
#define ct_shLoadF		ctgs.ct_shLoadF
#define ct_shRehashF		ctgs.ct_shRehashF
#define ct_shMaxBins		ctgs.ct_shMaxBins
#define ct_shNoShrink		ctgs.ct_shNoShrink
#ifdef ctPortYMF
#define ct_spltNbrFls		ctgs.ct_spltNbrFls
#endif
#define ctconbins		ctgs.ctconbins
#define ctrmsg			ctgs.ctrmsg
#define ct_commp		ctgs.ct_commp
#define ct_jobst		ctgs.ct_jobst
#define ct_commdis		ctgs.ct_commdis
#define ct_fcres_lev		ctgs.ct_fcres_lev
#define ct_bfsiz		ctgs.ct_bfsiz
#define ctlogidxfrc		ctgs.ctlogidxfrc
#define ctrdmp_opt		ctgs.ctrdmp_opt
#define ctrdmp_memlog		ctgs.ctrdmp_memlog
#define ctrdmp_flg		ctgs.ctrdmp_flg
#define ctmdmp_flg		ctgs.ctmdmp_flg
#define ctfdmp_flg		ctgs.ctfdmp_flg
#define ctxflg			ctgs.ctxflg
#define ctxflgfd		ctgs.ctxflgfd
#define ctridx_ptr		ctgs.ctridx_ptr
#define ctridx_cur		ctgs.ctridx_cur
#define ctridx_tot		ctgs.ctridx_tot
#define clnidxx_flag		ctgs.clnidxx_flag
#define ctrflg			ctgs.ctrflg
#define recovery_TRANDEP_operation ctgs.recovery_TRANDEP_operation
#define ctstrcv_flg		ctgs.ctstrcv_flg
#define ctlogmem		ctgs.ctlogmem
#define ctlogmemmax		ctgs.ctlogmemmax
#define ctlogdet		ctgs.ctlogdet
#define ctskpclnfil		ctgs.ctskpclnfil
#define ctfnstrat		ctgs.ctfnstrat
#define ctmnstrat		ctgs.ctmnstrat
#define cttloc			ctgs.cttloc
#define ctapwflg		ctgs.ctapwflg
#define ct_lstchktim		ctgs.ct_lstchktim
#define ctfilcre		ctgs.ctfilcre
#define ct_mul			ctgs.ct_mul
#define ct_maxdfridxlogs	ctgs.ct_maxdfridxlogs
#define ct_maxrepllogs		ctgs.ct_maxrepllogs
#define ct_maxrblqueue		ctgs.ct_maxrblqueue
#define ctDumpSyncInterval	ctgs.ctDumpSyncInterval
#define ct_dfc			ctgs.ct_dfc
#define ct_hghu1		ctgs.ct_hghu1
#define ct_mxu1			ctgs.ct_mxu1
#define ct_mxu1a		ctgs.ct_mxu1a
#define ct_mxu1b		ctgs.ct_mxu1b
#define ct_cmnown		ctgs.ct_cmnown
#define ct_hshft		ctgs.ct_hshft
#define ct_hbins		ctgs.ct_hbins
#define ct_bbins		ctgs.ct_bbins
#define ct_bbinsrat		ctgs.ct_bbinsrat
#define ct_dshft		ctgs.ct_dshft
#define ct_dbins		ctgs.ct_dbins
#define cth6flg			ctgs.cth6flg
#define ctatodep		ctgs.ctatodep
#define ct_tbins		ctgs.ct_tbins
#define ct_ibavl		ctgs.ct_ibavl
#define ct_ibavlb		ctgs.ct_ibavlb
#define ct_dbempl		ctgs.ct_dbempl
#define ct_dbemplb		ctgs.ct_dbemplb
#define ctLmtEmp		ctgs.ctLmtEmp
#define ct1stEmp		ctgs.ct1stEmp
#define ctaddempl		ctgs.ctaddempl
#define ctrmvempl		ctgs.ctrmvempl
#define ct_dbavl		ctgs.ct_dbavl
#define ct_dbavlb		ctgs.ct_dbavlb
#define ct_bavl			ctgs.ct_bavl
#define ct_bhla			ctgs.ct_bhla
#define ct_bhlR			ctgs.ct_bhlR
#define ct_bhlRb		ctgs.ct_bhlRb
#define dbg_bhl_n		ctgs.dbg_bhl_n
#define dbg_bhl_d		ctgs.dbg_bhl_d
#define ctsdname		ctgs.ctsdname
#define ctsmname		ctgs.ctsmname
#define ctsvname		ctgs.ctsvname
#define ctsqname		ctgs.ctsqname
#define ctlgname		ctgs.ctlgname
#define ctTCpos			ctgs.ctTCpos
#define ctTCsiz			ctgs.ctTCsiz
#define ctTCfp			ctgs.ctTCfp
#define ctTCsema		ctgs.ctTCsema
#define ctTCbuf			ctgs.ctTCbuf
#define ctscommp		ctgs.ctscommp
#define ctsjobsf		ctgs.ctsjobsf
#define ct_del			ctgs.ct_del
#define ct_delsiz		ctgs.ct_delsiz
#define ct_sqlsupr		ctgs.ct_sqlsupr
#define cts_list_m		ctgs.cts_list_m
#define cts_sort_m		ctgs.cts_sort_m
#define cts_bufr_m		ctgs.cts_bufr_m
#define ctfrename		ctgs.ctfrename
#define ctfrefp			ctgs.ctfrefp
#define ctfresema		ctgs.ctfresema
#define ct_sflvr		ctgs.ct_sflvr
#define ct_salgn		ctgs.ct_salgn
#define ct_spntr		ctgs.ct_spntr
#define ctmpagcache		ctgs.ctmpagcache
#define ctrunfil		ctgs.ctrunfil
#define ctrcvfil		ctgs.ctrcvfil
#define ct_adfil		ctgs.ct_adfil
#define ct_ver1			ctgs.ct_ver1
#define ct_ver2			ctgs.ct_ver2
#define ct_ver3			ctgs.ct_ver3
#define ctsupsep		ctgs.ctsupsep
#define ct_srvsema		ctgs.ct_srvsema
#define ct_uhnsema		ctgs.ct_uhnsema
#define ct_undsema		ctgs.ct_undsema
#define ct_dmpsema		ctgs.ct_dmpsema
#define ct_ismema		ctgs.ct_ismema
#define ct_vtsema		ctgs.ct_vtsema
#define ct_nmvsema		ctgs.ct_nmvsema
#define ct_avlsema		ctgs.ct_avlsema
#define ct_chksema		ctgs.ct_chksema
#define ct_abtsema		ctgs.ct_abtsema
#define ct_lflsema		ctgs.ct_lflsema
#define ct_chkpblk		ctgs.ct_chkpblk
#define ct_1dmsema		ctgs.ct_1dmsema
#define ct_lfwsema		ctgs.ct_lfwsema
#define ct_snapsema		ctgs.ct_snapsema
#define ct_trntimsema		ctgs.ct_trntimsema
#define ct_rqtmonsema		ctgs.ct_rqtmonsema
#define ct_comsema		ctgs.ct_comsema
#define ct_dcmsema		ctgs.ct_dcmsema
#define ct_lftsema		ctgs.ct_lftsema
#define tranac_sema		ctgs.tranac_sema
#define ct_dbsema		ctgs.ct_dbsema
#define ct_gvsema		ctgs.ct_gvsema
#define ct_logsema		ctgs.ct_logsema
#define ct_gnsema		ctgs.ct_gnsema
#define ct_nutmtx		ctgs.ct_nutmtx
#define ct_nupmtx		ctgs.ct_nupmtx
#define ct_dutmtx		ctgs.ct_dutmtx
#define ct_dupmtx		ctgs.ct_dupmtx
#define ct_lokmtx		ctgs.ct_lokmtx
#define ct_xlkmtx		ctgs.ct_xlkmtx
#define ctphnsemaIN		ctgs.ctphnsemaIN
#define ctphnsemaPN		ctgs.ctphnsemaPN
#define ctavlsema		ctgs.ctavlsema
#define ctavlsema		ctgs.ctavlsema
#define ctpgnsemaBK		ctgs.ctpgnsemaBK
#define ctphbsemaDU		ctgs.ctphbsemaDU
#define ctphbsemaDP		ctgs.ctphbsemaDP
#define ctdavsema		ctgs.ctdavsema
#define ctdavsema		ctgs.ctdavsema
#define ct_splsema		ctgs.ct_splsema
#define ct_dotsema		ctgs.ct_dotsema
#define ct_cmprecmtx		ctgs.ct_cmprecmtx
#define ct_ocsema		ctgs.ct_ocsema
#define ct_tflsema		ctgs.ct_tflsema
#define ct_llsema		ctgs.ct_llsema
#ifdef ctBEHAV_LLSEMA
#define ct_lmsema		ctgs.ct_lmsema
#endif
#define ct_facsema		ctgs.ct_facsema
#define ct_utrsema		ctgs.ct_utrsema
#define ct_memsema		ctgs.ct_memsema
#ifndef ctBEHAV_WORKsync
#define ct_concsema		ctgs.ct_concsema
#endif
#define ct_cnc2sema		ctgs.ct_cnc2sema
#define ct_ctlsema		ctgs.ct_ctlsema
#define ct_pi1sema		ctgs.ct_pi1sema
#define ct_pi2sema		ctgs.ct_pi2sema
#define ct_pi4sema		ctgs.ct_pi4sema
#define ct_pi8sema		ctgs.ct_pi8sema
#define ct_piwsema		ctgs.ct_piwsema
#define ct_pixsema		ctgs.ct_pixsema
#define ct_piysema		ctgs.ct_piysema
#define ct_pizsema		ctgs.ct_pizsema
#define ct_piasema		ctgs.ct_piasema
#define ct_pibsema		ctgs.ct_pibsema
#define ct_batsema		ctgs.ct_batsema
#define ct_ilksema		ctgs.ct_ilksema
#define ctmem_bin		ctgs.ctmem_bin
#define ctlsemapx		ctgs.ctlsemapx
#define ctlsemapxf		ctgs.ctlsemapxf
#define ctlsemap		ctgs.ctlsemap
#define ct_numusr		ctgs.ct_numusr
#define prime_on		ctgs.prime_on
#define ct_MPsema		ctgs.ct_MPsema
#define pADMINu			ctgs.pADMINu
#define pADMINg			ctgs.pADMINg
#define pGUESTu			ctgs.pGUESTu
#define pGUESTg			ctgs.pGUESTg
#define pADMINw			ctgs.pADMINw
#define pADMINk			ctgs.pADMINk
#define ct_sesschg		ctgs.ct_sesschg
#define ct_fcrpvuln		ctgs.ct_fcrpvuln
#define ct_loclwarn		ctgs.ct_loclwarn
#define ctcomioblk		ctgs.ctcomioblk
#define ctsublons		ctgs.ctsublons
#define ct_deadint		ctgs.ct_deadint
#define ct_deadclioff		ctgs.ct_deadclioff
#define ct_prpriority		ctgs.ct_prpriority
#ifndef ctFeatSNAPSHOT
#define ctlogcmpfloor		ctgs.ctlogcmpfloor
#define ctlogcmpfactor		ctgs.ctlogcmpfactor
#endif
#define ctldapsrvr		ctgs.ctldapsrvr
#define ctldapaid		ctgs.ctldapaid
#define ctldappfx		ctgs.ctldappfx
#define ctldapismgrp		ctgs.ctldapismgrp
#define ctldapsqlgrp		ctgs.ctldapsqlgrp
#define ctldapport		ctgs.ctldapport
#define ctldapssl		ctgs.ctldapssl
#define ctldapapp		ctgs.ctldapappst
#define ctldaptimeout		ctgs.ctldaptimeout
#define ctldapbase		ctgs.ctldapbase
#define ctlogingrp		ctgs.ctlogingrp
#define ctkxparams		ctgs.ctkxparams
#define ct_trdattr		ctgs.ct_trdattr
#define ct_sqlcommp		ctgs.ct_sqlcommp
#define ctsnap_bsrvtim		ctgs.ctsnap_bsrvtim
#define ctsnap_bwrktim		ctgs.ctsnap_bwrktim
#define ctsnap_bwrkbas		ctgs.ctsnap_bwrkbas
#define cthr_trntim		ctgs.cthr_trntim
#define ctsnap_bsrvclk		ctgs.ctsnap_bsrvclk
#define ctsnap_trntim		ctgs.ctsnap_trntim
#define ctperf_trntim		ctgs.ctperf_trntim
#define ctsnap_time		ctgs.ctsnap_time
#define ctsnap_tcnt		ctgs.ctsnap_tcnt
#define ctsnap_thid		ctgs.ctsnap_thid
#define ctsnap_allusers		ctgs.ctsnap_allusers
#define ctsnap_allfiles		ctgs.ctsnap_allfiles
#define ctsnap_wrktim		ctgs.ctsnap_wrktim
#define ctsnap_loktim		ctgs.ctsnap_loktim
#define ct_fncwrk		ctgs.ct_fncwrk
#define ctufncwrk		ctgs.ctufncwrk
#define ctffncwrk		ctgs.ctffncwrk
#define ctdedlok		ctgs.ctdedlok
#define ctpundsema		ctgs.ctpundsema
#define ctpdmpsema		ctgs.ctpdmpsema
#define ctmemtrkpsem		ctgs.ctmemtrkpsem
#define ctpismema		ctgs.ctpismema
#define ctpvtsema		ctgs.ctpvtsema
#define ctpnmvsema		ctgs.ctpnmvsema
#define ctpavlsema		ctgs.ctpavlsema
#define ctpchksema		ctgs.ctpchksema
#define ctpabtsema		ctgs.ctpabtsema
#define ctpuhnsema		ctgs.ctpuhnsema
#define ctplflsema		ctgs.ctplflsema
#define ctplokmtx		ctgs.ctplokmtx
#define ctpxlkmtx		ctgs.ctpxlkmtx
#define ctpgnsema		ctgs.ctpgnsema
#define ctpdotsema		ctgs.ctpdotsema
#define ctpcmprecmtx		ctgs.ctpcmprecmtx
#define ctrwlflst		ctgs.ctrwlflst
#define ctpocsema		ctgs.ctpocsema
#define ctptflsema		ctgs.ctptflsema
#define ctpcpocsema		ctgs.ctpcpocsema
#define ctpllsema		ctgs.ctpllsema
#ifdef ctBEHAV_LLSEMA
#define ctplmsema		ctgs.ctplmsema
#endif
#define ctpfacsema		ctgs.ctpfacsema
#define ctputrsema		ctgs.ctputrsema
#define ctpcomsema		ctgs.ctpcomsema
#ifdef ctBEHAV_WORKsync
#ifdef ctBEHAV_WORKsyncRWL
#define ctpconcsema_rwl		ctgs.ctpconcsema_rwl
#endif
#else
#define ctpconcsema		ctgs.ctpconcsema
#endif
#define ctpcnc2sema		ctgs.ctpcnc2sema
#ifndef ctFeatOPNCNTatomic
#define ctpopncsema		ctgs.ctpopncsema
#endif
#define ctpc3ncsema		ctgs.ctpc3ncsema
#define ctpc4ncsema		ctgs.ctpc4ncsema
#define ctpc5ncsema		ctgs.ctpc5ncsema
#define ctpc6ncsema		ctgs.ctpc6ncsema
#define ctpcpcsema		ctgs.ctpcpcsema
#define ctpMPsema		ctgs.ctpMPsema
#define ctpgvsema		ctgs.ctpgvsema
#define ctplogsema		ctgs.ctplogsema
#define ctpdbsema		ctgs.ctpdbsema
#define ctpsplsema		ctgs.ctpsplsema
#define ctplftsema		ctgs.ctplftsema
#define ptranacsema		ctgs.ptranacsema
#define ctpnupmtx		ctgs.ctpnupmtx
#define ctpdupmtx		ctgs.ctpdupmtx
#define ctpnutmtx		ctgs.ctpnutmtx
#define ctpdutmtx		ctgs.ctpdutmtx
#define ctpdcmsema		ctgs.ctpdcmsema
#define ctstrfilpsem		ctgs.ctstrfilpsem
#define ctphnsemaIN		ctgs.ctphnsemaIN
#define ctphnsemaPN		ctgs.ctphnsemaPN
#define ctavlsema		ctgs.ctavlsema
#define ctavlsema		ctgs.ctavlsema
#define ctpgnsemaBKb		ctgs.ctpgnsemaBKb
#define ctpgnsemaBK		ctgs.ctpgnsemaBK
#define ctphbsemaDU		ctgs.ctphbsemaDU
#define ctphbsemaDP		ctgs.ctphbsemaDP
#define ctdavsema		ctgs.ctdavsema
#define ctdavsema		ctgs.ctdavsema
#define ctbroadcastblk		ctgs.ctbroadcastbk
#define ctdnodepsema		ctgs.ctdnodepsema
#define ctptrntimsema		ctgs.ctptrntimsema
#define ctprqtmonsema		ctgs.ctprqtmonsema
#define ctpsnapsema		ctgs.ctpsnapsema
#define ctpchkpblk		ctgs.ctpchkpblk
#define ctplfwsema		ctgs.ctplfwsema
#define ctplfwsema		ctgs.ctplfwsema
#define ctp1dmsema		ctgs.ctp1dmsema
#define ctpundsema		ctgs.ctpundsema
#define available		ctgs.available
#define ctpdmpsema		ctgs.ctpdmpsema
#define available		ctgs.available
#define available		ctgs.available
#define ctmemtrkpsem		ctgs.ctmemtrkpsem
#define ctpismema		ctgs.ctpismema
#define available		ctgs.available
#define ctpvtsema		ctgs.ctpvtsema
#define ctpnmvsema		ctgs.ctpnmvsema
#define ctpavlsema		ctgs.ctpavlsema
#define available		ctgs.available
#define ctpchksema		ctgs.ctpchksema
#define ctpabtsema		ctgs.ctpabtsema
#define available		ctgs.available
#define ctpuhnsema		ctgs.ctpuhnsema
#define ctplflsema		ctgs.ctplflsema
#define ctpgnsema		ctgs.ctpgnsema
#define ctpdotsema		ctgs.ctpdotsema
#define ctpcmprecmtx		ctgs.ctpcmprecmtx
#define ctrwlflst		ctgs.ctrwlflst
#define ctpocsema		ctgs.ctpocsema
#define ctpllsema		ctgs.ctpllsema
#ifdef ctBEHAV_LLSEMA
#define ctplmsema		ctgs.ctplmsema
#endif
#define ctpfacsema		ctgs.ctpfacsema
#define ctputrsema		ctgs.ctputrsema
#define ctpcomsema		ctgs.ctpcomsema
#ifdef ctBEHAV_WORKsync
#ifdef ctBEHAV_WORKsyncRWL
#define ctpconcsema_rwl		ctgs.ctpconcsema_rwl
#endif
#else
#define ctpconcsema		ctgs.ctpconcsema
#endif
#define ctpMPsema		ctgs.ctpMPsema
#define ctpgvsema		ctgs.ctpgvsema
#define ctplogsema		ctgs.ctplogsema
#define ctpsplsema		ctgs.ctpsplsema
#define ctpdbsema		ctgs.ctpdbsema
#define ctplftsema		ctgs.ctplftsema
#define ptranacsema		ctgs.ptranacsema
#define ctpnupmtx		ctgs.ctpnupmtx
#define ctpdupmtx		ctgs.ctpdupmtx
#define ctpnutmtx		ctgs.ctpnutmtx
#define ctpdutmtx		ctgs.ctpdutmtx
#define ctpdcmsema		ctgs.ctpdcmsema
#define ctstrfilpsem		ctgs.ctstrfilpsem
#define ctpcnc2sema		ctgs.ctpcnc2sema
#define ctptflsema		ctgs.ctptflsema
#define ctplokmtx		ctgs.ctplokmtx
#define ctpxlkmtx		ctgs.ctpxlkmtx
#define ctphnsemaIN		ctgs.ctphnsemaIN
#define ctphnsemaPN		ctgs.ctphnsemaPN
#define ctavlsema		ctgs.ctavlsema
#define ctavlsema		ctgs.ctavlsema
#define ctpgnsemaBKb		ctgs.ctpgnsemaBKb
#define ctpgnsemaBK		ctgs.ctpgnsemaBK
#define ctphbsemaDU		ctgs.ctphbsemaDU
#define ctphbsemaDP		ctgs.ctphbsemaDP
#define ctdavsema		ctgs.ctdavsema
#define ctdavsema		ctgs.ctdavsema
#define ct_splsema		ctgs.ct_splsema
#define available		ctgs.available
#define ctbroadcastblk		ctgs.ctbroadcastblk
#define ctdnodepsema		ctgs.ctdnodepsema
#define ctpsnapsema		ctgs.ctpsnapsema
#define ctptrntimsema		ctgs.ctptrntimsema
#define ctprqtmonsema		ctgs.ctprqtmonsema
#define ctpchkpblk		ctgs.ctpchkpblk
#define ctplfwsema		ctgs.ctplfwsema
#define ctp1dmsema		ctgs.ctp1dmsema
#define ctplfwsema		ctgs.ctplfwsema
#define ctp1dmsema		ctgs.ctp1dmsema
#define ctsresema		ctgs.ctsresema
#define ctfilcremode		ctgs.ctfilcremode
#define ctmaxsqlisolvl		ctgs.ctmaxsqlisolvl
#define ctinhfilprm		ctgs.ctinhfilprm
#define ctlokretry		ctgs.ctlokretry
#define ctlokretrysleep		ctgs.ctlokretrysleep
#define ctufilmod		ctgs.ctufilmod
#define ctcusers		ctgs.ctcusers
#define ctfs_fopen		ctgs.ctfs_fopen
#define ctfs_fclose		ctgs.ctfs_fclose
#define ctfs_fseek		ctgs.ctfs_fseek
#define ctfs_fread		ctgs.ctfs_fread
#define ctfs_fwrite		ctgs.ctfs_fwrite
#define ctfs_filelength		ctgs.ctfs_filelength
#define ctfs_fileno		ctgs.ctfs_fileno
#define ctfs_remove		ctgs.ctfs_remove
#define ctfs_ftell		ctgs.ctfs_ftell
#define ctfs_rename		ctgs.ctfs_rename
#define ctClientHandle		ctgs.ctClientHandle
#define ctClientModuleName	ctgs.ctClientModuleName
#define ctClientServerName	ctgs.ctClientServerName
#define ctMEMFILEmaxbins	ctgs.ctMEMFILEmaxbins
#define ctcritsectspin		ctgs.critsectspin
#define trnovrflwthr		ctgs.trnovrflwthr
#define ctseclgn		ctgs.ctseclgn
#define ctVLEN_ERRlimit		ctgs.ctVLEN_ERRlimit
#define ctKEEPOPENcloselimit	ctgs.ctKEEPOPENcloselimit
#define ctpforetrylimit		ctgs.ctpforetrylimit
#define ctsqlpartopencost	ctgs.ctsqlpartopencost
#define pRtlCaptureStackBackTrace ctgs.pRtlCaptureStackBackTrace
#define ctcoaltran		ctgs.ctcoaltran
#define def_cmprec_type		ctgs.def_cmprec_type
#define def_cmprec_vrsn		ctgs.def_cmprec_vrsn
#define def_cmprec_plen		ctgs.def_cmprec_plen
#define def_cmprec_dll		ctgs.def_cmprec_dll
#define def_cmprec_parm		ctgs.def_cmprec_parm
#define ctsslinf		ctgs.ctsslinf
#define crepart_host		ctgs.crepart_host
#define rtuserlibname		ctgs.rtuserlibname
#define ctminlogsync		ctgs.ctminlogsync
#define ctkep_rp_rcv		ctgs.ctkep_rp_rcv
#define ctkep_rp_cfg		ctgs.ctkep_rp_cfg
#define ctkep_rp_num		ctgs.ctkep_rp_num
#define ctkep_rp_act		ctgs.ctkep_rp_act
#define ctkep_rp_fnd		ctgs.ctkep_rp_fnd
#define ctkep_rp_req		ctgs.ctkep_rp_req
#define ctkep_rp_tim		ctgs.ctkep_rp_tim
#define ct_clstrn		ctgs.ct_clstrn
#define ct_endser		ctgs.ct_endser
#define ctkep_rp_srn		ctgs.ctkep_rp_srn

#ifdef ctFeatPLUGIN
#define ctplugin_list                    ctgs.ctplugin_list
#define ctplugin_count                   ctgs.ctplugin_count
#endif

#define intblkpgs			 ctgs.intblkpgs
#define atotrncre			 ctgs.atotrncre
#define ctnontranfsflushoff		 ctgs.ctnontranfsflushoff
#define ssOnShutdown			 ctgs.ssOnShutdown

#endif /* ctFeatSRVR_STRUCT */

#ifndef ctCLIENT
#ifndef ctFeatL10_serno
extern ULONG	 ctghat[ctGhatSize];
#endif
extern NINT      ct_maxvfil;	/* maximum virtual files opened		*/
EXTERN DllExtImp NINT	 cttflg;/* stop server in progress		*/
EXTERN DllExtImp NINT	 cttflg_L;/* stop server in progress:logsema ctl*/
EXTERN DllExtImp NINT	 ctrint_L;/* recovery interrupted:   logsema ctl*/
#endif

#ifdef ctSRVR
EXTERN pTEXT	ctsvport;	/* server port				*/
#endif

#ifdef ctSQLSRVR
EXTERN	NINT	ctsqlmincard;	/* ctree SQL minimum table/index cardinality */
EXTERN LONG     ct_sqlport;     /* port for SQL client connections */
EXTERN LONG     ctSQLIdleTimeout;     /* Network timeout for SQL connections before running fc_idle*/
EXTERN LONG     ctSQLCCacheLimit;     /* maximum # of open table cache entries */
EXTERN COUNT	ctSQLTraceCtreeError; /* Error to trace in ct_exception() */
EXTERN COUNT	ctSQLconntimeout;     /* max server wait for client response before authentication */
EXTERN LONG     ctSQLIdleKill;     /* Network timeout for SQL connections before closing the socket killing connection */
#endif

#ifdef ctDBGsemlst
/* maximum number of entries in thread's sema list */
#define MAXTSEM	24

/* synchronization object types */
#define BLKOBJ	1	/* block	*/
#define MUTOBJ	2	/* mutex	*/
#define SEMOBJ	3	/* semaphore	*/
#define TIMOBJ	4	/* timer	*/

/* sync object list entry */
typedef struct {
	union {
		pSEMAblk	blck;
		pSEMAmut	mutx;
		pSEMA		sema;
		pSEMAtim	stim;
		pVOID		pntr;
	} objptr;
	NINT	objtyp;
	NINT	objloc;
} SEMINF, *pSEMINF;

/* sync object list for a c-tree instance */
typedef struct {
	NINT	cnt;		/* Count of sema list entries */
	NINT	hgh;		/* Max number of sema list entries */
	NINT	ovf;		/* Count of times list overflowed */
	SEMINF	lst[MAXTSEM];	/* Sema list */
} SEMLST;

/* sync object list for all c-tree instances */
SEMLST ctsemlst[MXU2];

#endif /* ctDBGsemlst */

#ifdef RB_CALLBACK_SRVR
typedef struct {
	pLQMSG		lqp;
	pLQMSG2		plqmsg2;
	preqPARMB	ppb;
	prspPARMB	pqb;
} RBLPARMS;
#endif

#ifdef ctFeatTRANSFER_FILE
/*
** Communication state variables used by the server's file transfer function.
*/
typedef struct {
	pLQMSG		lqp;	/* comm data				*/
	pLQMSG2		plqmsg2;/* extended comm data			*/
	preqPARMB	ppb;	/* comm request block			*/
	prspPARMB	pqb;	/* comm response block			*/
#ifdef ctFeatTRANREPL
	pXFRINF		pxfrinf;/* parameters for master file transfer	*/
#endif
} XFRPRMS, ctMEM * pXFRPRMS;
#endif

#if defined(ctFeatVFYIDX_CS) || defined(ctFeatVERIFYfile)
/*
** Communication state variables used by the server's index verification and
** file verification functions.
*/
typedef struct {
	pLQMSG		lqp;	/* comm data				*/
	pLQMSG2		plqmsg2;/* extended comm data			*/
	preqPARMB	ppb;	/* comm request block			*/
	prspPARMB	pqb;	/* comm response block			*/
	TEXT		flags;	/* specified options			*/
	NINT		pct;	/* last percent reported to client	*/
} VFYPRMS, ctMEM * pVFYPRMS;
#endif

#ifdef ctFeatSCNLOGkeepaliveSRVR
/*
** Communication state variables used by the server's ctReplGetNextChange()
** function.
*/
typedef struct {
	pLQMSG		lqp;	/* comm data				*/
	pLQMSG2		plqmsg2;/* extended comm data			*/
	preqPARMB	ppb;	/* comm request block			*/
	prspPARMB	pqb;	/* comm response block			*/
	TEXT		flags;	/* specified options			*/
} RCHPRMS, ctMEM * pRCHPRMS;
#endif

#ifdef ctFeatRTG_API
/*
** Communication state variables used by the server's RTG function.
*/
typedef struct {
	pTEXT		crec;
	size_t		creclen;
	pTEXT		rpcbuf;
	size_t		l_rpcbuf;
} RTGUSRMEM, ctMEM * pRTGUSRMEM;
typedef struct {
	pLQMSG		lqp;	/* comm data				*/
	pLQMSG2		plqmsg2;/* extended comm data			*/
	preqPARMB	ppb;	/* comm request block			*/
	prspPARMB	pqb;	/* comm response block			*/
	TEXT		flags;	/* specified options			*/
	pRTGUSRMEM	pusr;	/* user-defined pointer			*/
} RTGPRMS, ctMEM * pRTGPRMS;
#endif

#ifdef ctFeatCOPYFILE
/*
** Communication state variables used by the server's ctCopyFile function.
*/
typedef struct {
	pLQMSG		lqp;	/* comm data				*/
	pLQMSG2		plqmsg2;/* extended comm data			*/
	preqPARMB	ppb;	/* comm request block			*/
	prspPARMB	pqb;	/* comm response block			*/
	pVOID		pusr;	/* user-defined pointer			*/
	TEXT		pct;	/* last percent reported to client	*/
} CPFPRMS, ctMEM * pCPFPRMS;
#endif

#ifdef ctFeatTEMPDIR
/*
** Communication state variables used by the server's ctTempDir function.
*/
typedef struct {
	pLQMSG		lqp;	/* comm data				*/
	pLQMSG2		plqmsg2;/* extended comm data			*/
	preqPARMB	ppb;	/* comm request block			*/
	prspPARMB	pqb;	/* comm response block			*/
	pVOID		pusr;	/* user-defined pointer			*/
	TEXT		pct;	/* last percent reported to client	*/
} TDRPRMS, ctMEM * pTDRPRMS;
#endif

#ifdef ctFeatCLICB
/*
** Communication state variables used by the server's client callbacks.
*/
typedef struct {
	pLQMSG		lqp;	/* comm data				*/
	pLQMSG2		plqmsg2;/* extended comm data			*/
	preqPARMB	ppb;	/* comm request block			*/
	prspPARMB	pqb;	/* comm response block			*/
} CLICBP, ctMEM * pCLICBP;
#endif

#if defined(ctFeatDFRIDXsrvr) && defined(ctDBGfcqa)
/* dfrkf diagnostics: list of deferred index reader/writer locks that this
** connection is holding. */
typedef struct dfkfd {
	pVOID	rwlock;
	struct dfkfd *
		next;
} DFKFD, *pDFKFD;
#endif

typedef struct thrdgv
{
	NINT	 slOWNR;	/* self-referencing thread handle (OWNER) */
	NINT	 slCNTR;	/* self-referencing thread instance cntr  */
#ifdef ctDBGstack
	LONG	 sstkbase;	/* stack baseline			*/
	LONG	 sstkaapi;	/* stack at entry to API		*/
	LONG	 sstktrip;	/* tripped over stack baseline		*/
#endif
#ifdef ctFeatUSRBLKTIMOUT
	LONG	 sutimout;	/* all files user block timeout		*/
	NINT	 sdtimout;	/* diagnostic indicator			*/
#endif
#ifdef TRANPROC
#ifdef ctDYNHASH
	UINT	 spreiseq;	/* preimage space sequence number	*/
#endif
	NINT	 sisolev;
#endif
	NINT	 sapplst;	/* APP_NAME_LIST user index		*/
#ifdef ctCREATE_SEMA
	SEMA	 sresema;	/* reuseable semaphore for temp CTFILE	*/
#endif
	SEMAtim	 sctblktim;
#ifdef CTBATCH
	BATHDR	 batch;
#ifdef ctOldALCBAT
	COUNT	 sbatmax;
	COUNT	 sbatnum;
	pBATHDR	 ssavbat;
#else
	pSAVBAT	 sbatnum;
	ppSAVBAT ssavbat;
#endif
#endif
#if defined(ctFeatNoDatPndgList)
	GENBUF	 sdumcacpag;	/* dummy data cache page stub		*/
#endif
#if defined(ctFeatNoIdxPndgList)
	GENBUF	 sdumbufpag;	/* dummy index buffer page stub		*/
#endif
#ifdef CTHISTORY
	HSTHDR	 history;
	pHSTLST	 histund;
	pSAVHST	 shstnum;
	ppSAVHST ssavhst;
#endif
#ifdef ctHUGEFILEsegm
	pSEGLST	 sseglsthdr;
#endif
#ifdef ctCONDIDX
	pVOID	 sctcidxStk;
#ifdef ctFeatCTDB
#ifdef ctFeatCNDX_V9
	pVOID	 sctcidxRecInfo; /* user buffer for PT_RECINFO node	*/
	VRLEN	 sctcidxMaxFlds; /* max fields for PT_RECINFO doda	*/
#endif
#endif
#endif
#ifdef rtSRVR
	pVOID	 srtinst;	/* r-tree instance (rtGVAR)		*/
#endif

#ifdef ctCAMO
	pCAMFNC
	      sucamfnc;
	pTEXT sucamptr;
	pTEXT sct_cam;
	VRLEN sct_camsiz;
	LONG  sucamlen;
#endif
#ifdef ctCMPLOG
	NINT  slogcmpcnt;	/* usage counter			*/
	VRLEN slogcmplen;	/* log compression buffer length	*/
	pTEXT slogcmpbuf;	/* ptr to log compression buffer	*/
#endif
	LONG  sctops;		/* set operation state bit mask		*/
	LONG  sctstate;		/* internal state bit mask		*/
	LONG  sctstat2;		/* internal state bit mask 2		*/
	LONG  sctstat3;		/* internal state bit mask 3		*/
	LONG  sctstat4;		/* internal state bit mask 4		*/
	LONG  sctstat5;		/* internal state bit mask 5		*/
	LONG  sctstat6;		/* internal state bit mask 6		*/
/* ctSIBLING_CTSTATE - Add new state variable here */
	VRLEN sctxvlen;		/* vlen combined op max buffer length	*/
	NINT  sctstatg;		/* keyseg distinct count indicator	*/
#ifdef TRANPROC
	LONG  sabnlog;		/* begtran log for abandoned tran	*/
	LONG  slfwchn;		/* lfwsema channel: ctMXLFW		*/
	UINT  scmtseq;		/* commit_seq number (commit delay)	*/
#ifdef ctFeatLOKDYN
	NINT  sudlokdyn;	/* set only direct unlock call		*/
#endif
#ifdef ctBEHAV_CMTLOK
	NINT  scmtfil;		/* RED_CMTLOK system file #		*/
	LONG  scmtlhw;		/* RED_CMTLOK lock pos high word	*/
	LONG  scmtllw;		/* RED_CMTLOK lock pos low  word	*/
#endif
#endif
#if defined(ctFeatINTERNAL_FILE_CONTROL) && defined(ctFeatPRICACHE)
	NINT  sprichetaskid;	/* cache priming thread task ID		*/
#endif
#if defined(ctFeatINTERNAL_FILE_CONTROL) && defined(ctFeatDFRIDX)
	NINT  sdfridxtaskid;	/* deferred indexing thread task ID	*/
#endif
#ifdef ctFeatRUCB
	pVOID srucbsess;	/* Record update callback function: user-
				** defined pointer for connection-level
				** state information			*/
#endif
#ifdef ctFeatSNAPSHOT
	LONG8 smarkbeg[8];	/* user defined mark beg HR time	*/
	LONG8 smarktim[8];	/* user defined mark elapsed HR times	*/
	ULONG smarkcnt[8];	/* user defined mark counts		*/
	LONG8 strntime;		/* user tran (beg) time */
	LONG8 strntdly;		/* user tran (dlybegtran) time */
	LONG8 strntsum;		/* user trntime sum	*/
	LONG8 strntmax;		/* user trntime max	*/
	ULONG strntcnt;		/* user trntime count	*/
	ULONG strntdet[ctTRNTdetail];
				/* user trntime detail	*/
	ULONG sctutrbeg;	/* user tran beg count	*/
	ULONG sctutrend;	/* user tran beg count	*/
	ULONG sctutrabt;	/* user tran beg count	*/
#else
	LONG  strntime;		/* last begin tran time */
	LONG  strntdly;		/* last begin (dlybegtran) time */
#endif
	NINT  snbrfile;		/* number of files in use */
#ifdef ctSSrel2
	NINT  snumredlzr;	/* number of files user is the redlzr */
#endif

#ifndef CTBOUND
	pVOID suserlqp;		/* user's request block */
	LONG  sctops_clr;	/* operation state clear mask		*/
#ifdef ctHUGEFILE
	LONG  sautopos2;	/* auto current ISAM position */
#endif
	LONG  sautopos1;	/* auto current ISAM position */
#ifdef ctPARTITION
	LONG  sautopart;	/* auto partition number */
#endif
	LONG  slogtime;		/* logon time */
	LONG  srqstime;		/* last request time */
	LONG  srqsfunc;		/* last request function # */
	LONG  sfncretflex;	/* special FLEXFILE ret values: only ctSRVR */
	NINT  srqssubf;		/* last request sub-function */
	NINT  sactflag;		/* active / inactive flag */
	TEXT  snodname[32];	/* node name */
#endif

#ifdef ctCAMOsdk
	LONG  sctcamver;
#endif
#ifdef ctFeatRECRLOCK
	LONG  snetrecr;		/* net recursive call count */
#endif
#ifdef ctHUGEFILE
	LONG  spbrva;		/* "out-of-channel" pbrva from client	 */
	LONG  scthghwrd;
#endif
	LONG  sfncret;		/* special function ret values: only MULTITRD */
	LONG  sct_npath1[MAXLEV];/* array to trace path down B-tree. Assumes  */
				 /* maximum of MAXLEV - 1 levels in B-tree.   */
	LONG  sct_lnode1;	/* last node found during walk down tree */
	LONG  sct_fnode1;	/* node found during search/retrieval    */
	LONG  sct_nwnod1;	/* pointer to new node */
#ifdef ctHUGEFILE
	LONG  sct_npath2[MAXLEV];
	LONG  sct_lnode2;	/* last node found during walk down tree */
	LONG  sct_fnode2;	/* node found during search/retrieval    */
	LONG  sct_nwnod2;	/* pointer to new node */
	LONG  sct_gsrl2;	/* next serial number for data file */
#ifdef ctFeatLOKLST
	LONG  sct_ldnybyt2;	/* last denied lock position - high word */
#endif
#endif /* ctHUGEFILE */
#ifdef ctFeatLOKLST
	LONG  sct_ldnybyt1;	/* last denied lock position -  low word */
#endif
	LONG  sct_gsrl1;	/* next serial number for data file */
#ifdef ctFeatDAR
	LONG  sIDfield_lstoff;	/* last IDfield field offset	    */
	LONG8 sct_IDfield;	/* next IDfield number for data file. note:
				** ct_IDfield before last update while ct_gsrl
				** after last update
				*/
#endif
#if defined(ctFeatOS_SECURITY_UNIX) || defined(ctFeatOS_SECURITYuseIDnum)
	NLONG sct_usernm;	/* system dependent user number */
#endif
#ifdef TRANPROC
	UINT  sctdfrcls;	/* defer close count */
#endif
#ifdef ctFeatLOKLST
	NINT  sct_ldnyfil;	/* last denied lock position - datno + 1 */
#endif
	NINT  sct_trdflg;	/* thread operation flag */
	NINT  sctcidxStkPtr;
	NINT  sctcidxCurCmd;
#ifdef ctFeatUDF_EXPR
	pVOID sudflist;
	NINT  sisexpreval;
#endif
#ifdef ctFeatTRANREPL
	NINT  sctClientConn;	/* is client connection established? */
	NINT  sctTranActive;	/* is tran active on master system? */
#endif
#ifdef TRANPROC
	NINT  sabnflg;		/* counts stage of abandon tran processing */
#endif
#ifdef ctICONTEXT
	COUNT sctconid;
#endif
	TEXT  sct_userid[IDZ];	/* unique user id */
#ifdef ctSRVR
#ifdef ctFeatSECURITY
	UGRUP sct_userg[MAX_UGRUP];
				/* group list header */
#endif
#endif
#ifdef ctMULTIOPN
	NINT  sct_mltopn;	/* multi-open flag		 */
	ULONG sct_fseq;		/* thread private FUSR sequence# */
#endif
#ifdef ctDBGlcnt
	ULONG sct_dbglcnt;	/* debug sequence # for ctdbglcnt*/
#endif
	pFUSR sct_fup;		/* FUSR pointer for current file */
#ifdef ctICONTEXT
	ppctICON  sctconanc;	/* hash bins for context */
#endif
#ifdef DBGtree
	pVOID	  sct_walkh;	/* tree-walk degug list head */
	pVOID	  sct_walkt;	/* tree-walk degug list tail */
	NINT	  sctlflg;	/* load key flag	     */
#endif /* DBGtree */
#ifdef TRANPROC
#ifndef ctFeatIICT
	struct thrdgv
		 *trnlstlnk;	/* transaction (hash) lists of users	*/
	ppSHADLST sct_ubit;	/* hash bins for srchshd		*/
#ifdef ctDYNHASH
	HSHSTT	 sshadstt;	/* preimage hash state structure	*/
#endif
	LONG  sct_usrsv;	/* tran savepoint info			*/
	NINT  sct_rstflg;	/* TRANRST() flag			*/
#endif
#ifdef DBGhash
	pLONG     sdbg_shsh_u;
#endif
#ifdef ctBEHAV_CLUP
	pctCLUP  sct_pclup;	/* pointer to array of ctCLUPs	*/
	NINT  sct_clupflg;	/* ctclup flag			*/
	NINT  sct_clupcnt;	/* number of transactions	*/
	ctCLUP sct_clupstr[ctCLUPary];
				/* "static" array of ctCLUPs	*/
#endif
#else
	COUNT stranactv;
	COUNT stransavp;
#endif
	LONG  sct_uflgs;	/* user flags */
	LONG  sct_kltsk;	/* task ID that requested this connection to
				** terminate */
	NINT  sctrbflg;		/* rebuild flag */
	NINT  swhdrflg;		/* write header flag */
#ifdef ctDYNHASH
	pULOKHSH
	       sct_locksb;
	HSHSTT sct_lokstt;
#else
	ppLOKS sct_locksb;	/* user lock table head */
	ppLOKS sct_ltailb;	/* user lock table tail */
#endif
#ifdef DBGhash
	pLONG  sdbg_lhsh_u;
#endif
	COUNT sctusrprf;	/* user profile word */
	FILNO sctumxfil;	/* max files for user */
	FILNO scthghfil;	/* highest file number limit */
	NINT  sprvlokf;		/* previous lock state: datno		*/
	NINT  sprvlokt;		/* previous lock state: lock type	*/	
	NINT  sprvlokt2;	/* previous lock state: lock type	*/	
	LONG  sprvlokp;		/* previous lock state: recbyt (lw)	*/	
#ifdef ctHUGEFILE
	LONG  sprvlokh;		/* previous lock state: recbyt (hw)	*/	
#endif
	IDXSTATE idxstate;  /* users default index state */
	NINT  sct_flagpw;	/* temppw flag				*/
#ifdef ctTRSETtest
	NINT  trnbin;		/* tran hash bin			*/
#endif

#ifdef ctFeatLOGLMT
	TEXT	loglmt;		/* user/group logon count was incremented  */
#endif
	TEXT sct_dupkey[MAXLEN+1];/* for searches of duplicate keys */
	TEXT sspkey[MAXLEN+1];	/* temporary storage for key values during */
				/* node updates 			   */

#ifdef ctFeatSECURITY
	TEXT sct_temppw[PWZ];	/* temporary password  */
#endif
	TEXT sct_buf[CTBUFSIZ];	/* temporary io buffer */
	UTEXT sct_uflvr;	/* user flavor */
	UTEXT sct_ualgn;	/* user alignment */
	UTEXT sct_upntr;	/* user pointer size */

#ifdef ctFeatLOADKEYopt
	TEXT sl_apnod[MAXLEV];	/* node has been initialized by addtoparent */
	TEXT sl_maxukp;		/* maximum % full requested in leaf node    */
	UINT sl_maxukb;		/* maximum key bytes requested in leaf node */
#endif
	TEXT sl_lastkey[MAXLEN];
	LONG sl_begnod1;
	LONG sl_curnod1;
	LONG sl_prvnod1;
#ifdef ctHUGEFILE
	LONG sl_begnod2;
	LONG sl_curnod2;
	LONG sl_prvnod2;
	LONG sl_numnod2;
	LONG sl_ct_nnods2[MAXLEV];
#endif /* ctHUGEFILE */
	LONG sl_numnod1;
	LONG sl_ct_nnods1[MAXLEV];
	NINT sl_elem;
	NINT sl_started;
	pTREBUF sl_savbp;
	VRLEN sl_hdradj;

	pTEXT sb_ct_rbuf;
	pctRECPT sb_ct_pbuf;
	COUNT sb_rerr_cod;
	FILNO sb_rerr_fil;
	COUNT sb_ct_fp;
	COUNT sb_ct_redom;
	VRLEN sb_ct_bsz;
	LONG sb_ct_spc;

	NINT	 sksgcuru;	/* user key seg def list controls	*/
	NINT	 sksgtotu;
	pKSEGLST sksglstu;

	LONG	 sua_han;	/* async thread's async handle		*/
	NINT	 sua_cal;	/* launcher's thread ID			*/
	NINT	 sua_cnt;	/* launcher's instance counter		*/
	NINT	 sua_typ;	/* async thread's type			*/

	pctUASYNC
		 sua_lst;	/* async launcher's list		*/
	NINT	 sua_cur;
	NINT	 sua_tot;

#ifdef ctSYSQUEsrvr
	NINT	 sqreadg;	/* reading queue (handle + 1)		*/
	pVOID	 sqlinks;	/* creator system queue links		*/
#endif
#ifdef ctPortNUMEGA_TR
	pVOID	ctuserstate;
#endif
#ifdef ctFeatFNCMEMSTATS
	NINT	scurfnc;
#endif
#ifdef ctFeatLOGREAD
	NINT	sctlogred;	/* Log reader flag			*/
	NINT	sctreplopts;	/* Replication options			*/
	pCTFILE	suctLnum;	/* Transaction log file control block	*/
	pctCNXH	spcnxhnd;	/* Replication connection handle	*/
	pctCHGB	spchgbuf;	/* Replication change buffer		*/
#endif
#ifdef ctFeatSCANCACHE
	NINT	sscanfiles;	/* number of files user has in scanning mode */
#endif
#ifdef RB_CALLBACK
	pRBLCBFNC srblcbfnc; /* ptr to rebuild callback func */
#ifdef ctFeatREBUILD_CALLBACK_STATE
	pctRBCBST srblpcbst; /* pointer to rebuild callback state */
	LONG8	  srblcbcnt; /* progress counter for rebuild callback func */
#else
	ULONG     srblcbcnt; /* progress counter for rebuild callback func */
#endif
	UCOUNT    srblcbstp; /* progress step for rebuild callback func */
#ifdef RB_CALLBACK_SRVR
	RBLPARMS  srblparms; /* rebuild callback parameters */
#endif
#endif
#ifdef ctFeatTRANSFER_FILE
	pXFRPRMS  sxfrparms; /* file transfer parameters */
#endif
#ifdef ctFeatVFYIDX_CS
	pVFYPRMS  svfyparms; /* verifyidx parameters */
#endif
#ifdef ctFeatSCNLOGkeepaliveSRVR
	pRCHPRMS  srchparms; /* ctReplGetNextChange parameters */
#endif
#ifdef ctFeatRTG_API
	pRTGPRMS  srtgparms; /* RTG callback parameters */
#endif
#ifdef ctFeatCOPYFILE
	pCPFPRMS  scpfparms; /* ctCopyFile callback parameters */
#endif
#ifdef ctFeatTEMPDIR
	pTDRPRMS  stdrparms; /* ctTempDir callback parameters */
#endif
#ifdef ctFeatCLICB
	CLICBP	  sclicbp;   /* client callback state variables */
#endif
	COUNT	  sctopnmod; /* file open mode flags automatically applied */
#ifdef ctSQLSRVR
#ifdef ctSQL_SHMEM
	COUNT	  ssqlcommp; /* SQL client communication protocol */
#endif
#endif
#ifdef ctFeatFILWCD
	pctOS_FILE_FIND_INFO
		  sctpfilwcd;/* ctFILWCD wildcard search state */
#ifndef ctPortUNIX
	NINT	  sctwcdcnv; /* ctFILWCD path name conversion state */
#endif
#endif
#ifdef ctDIAGdlokERR
	NINT	  sctdlok_loc;	/* Last location of DLOK_ERR	*/
	NINT	  sctdlok_own;	/* Owner of lock on DLOK_ERR	*/
#endif
#ifdef ctFeatGNSEMAhsh
	pIHBLOCKmut sphnsemaINusr; /* INLIST mutex for GNS call to ctgetnod81 */
#ifndef ctFeatNoIdxPndgList
	pSEMAmut  sphnsemaPNusr;/* PNLIST mutex for GNS call to ctgetnod81 */
#endif
#endif
#ifdef ctFeatREPL_SRLSEG
	ctRECPT	  susrsnum1;    /* user serial number low word */
	ctRECPT	  susrsnum2;    /* user serial number high word */
#endif
#ifdef ctFeatUDF_EXPR
	pVOID	  udflist;
	NINT	  isexpreval;
#endif
#ifdef ctFeatSEQNUM
	FILNO	  ssequfl;	/* sequence file user file number */
	COUNT	  sseqcnt;	/* number of open sequences	  */
#endif
#ifdef ctBEHAV_CMTLOK_optimize
	pTEXT     scmbiobuf;	/* buffer for combined record I/O */
	VRLEN     scmbiolen;	/* size of combined I/O buffer	  */
	NINT      scmbiostt;	/* combined I/O status code	  */
/*
** Commit read lock check state variables for each connection.
**
** Set cmlkchksiz to the buffer size to indicate that ctblock81() must check if
** a commit read lock is needed when it reads the record header.
**
** ctblock81() sets cmlkchkres to the commit read lock state.
*/
	VRLEN	  scmlkchksiz;	/* commit lock buffer size	  */
	SYSNO	  scmlkfilnum;	/* file number for commit lock	  */
	COUNT	  scmlkchkres;	/* cmtlok() result		  */
#endif
#ifdef ctBEHAV_CMPREC_optimize
	LONG	  schkcmprec;	/* check if record is compressed  */
	VRLEN	  sskpimglen;	/* skip leading bytes of record image */
	pTEXT	  scmprecbuf;	/* compressed record image buffer */
	VRLEN	  scmprecsiz;	/* size of compressed record buffer */
#endif
#ifdef ctFeatNOBUFFERING
	pTEXT	  subiobuf;	/* buffer for unbuffered I/O 	  */
	VRLEN	  subiolen;	/* size of I/O buffer		  */
#endif
#ifdef ctFeatDAR
	LONG	  DARmsg[DARmsgary];
				/* client-side record image update*/
#endif
#ifdef ctPARTITION
	pCTFILE   srblhnum;	/* partition rebuild host dnum	  */
	NINT	  srblrawno;	/* partition rebuild member rawno */
	NINT	  sprmidxcnt;	/* number of partition members	  **
				** calling reprmidx in recovery	  */
#endif
#ifdef ctFeatXTDOPNMOD
	LONG	  sxtdopnmod;	/* extended file open mode	  */
#endif
#ifdef ctFeatSUPHSTcofile
	FILNO	  scursuphstno;	/* current superfile host file number */
#endif
#ifdef ctSRVR
	pctUSRST  spusrstate;	/* saved connection state	  */
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
	NINT	  susr_cmprec_type;
	NINT	  susr_cmprec_vrsn;
	UINT	  susr_cmprec_plen;
	UINT	  susr_cmprec_allc;
	pTEXT	  susr_cmprec_parm;
	TEXT	  susr_cmprec_dll[MAX_NAME];
#endif
#ifdef ctFeatKEEPOPENclose
	NINT	  skofilno;	/* file in KEEPOPEN state	  */
#ifdef ctBEHAV_FCBSTK
	NINT	  skofcbs;	/* getctm block size		  */
#endif
#ifdef CTSUPER
	FILNO	  ssuphstno;	/* user file number of superfile host that was
				** automatically opened when opening a member
				*/
#endif
#endif
#ifdef ctFeatIdxAdaptHashBinLocks
	ULONG	  sbufreqs;	/* index hash bin searches (32bit)	*/
	ULONG	  sbufhits;	/* index hash bin search hits (32bit)	*/
#endif
#ifdef ctFeatDatAdaptHashBinLocks
	ULONG	  scacreqs;	/*  data hash bin searches (32bit)	*/
	ULONG	  scachits;	/*  data hash bin search hits (32bit)	*/
#endif
#ifdef ctDBGfcqa
	NINT	datsemopn;	/* # of open datsem calls: never expect	**
				** more than 1 datsem to be held by a	**
				** thread at any one time		*/
	NINT	idxsemopn;	/* # of open idxsem calls: never expect	**
				** more than 3 idxsem's to be held by a **
				** thread at any one time		*/
#endif
#ifdef ctFeatKBUFrefresh
	pTEXT	skbufrec;	/* Buffer to hold the record image that	**
				** we read to refresh ISAM key buffers.  */
	LONG	skbufrecsiz;	/* Size of the record image buffer.	 */
#endif
#ifdef ctFeatMEMFILErefcnt
	pTEXT	smemfilrefcnt;	/* Memory address of the memory file record
				** buffer whose reference count we have
				** incremented. */
	NINT	smemfilsysno;	/* System file number of the file that holds
				** the memory record whose reference count we
				** have incremented. */
#endif
#ifdef ctFeatSRVRpower
	LONG8	sacthrtim;	/* Total time thread has been in active state,
				** in high-resolution timer ticks. */
	double	spwrdelay;	/* cumulative pending delay count */
#endif
#if defined(ctFeatDFRIDXsrvr) && defined(ctDBGfcqa)
	pDFKFD	sdfrkf;		/* Deferred index rwlock last acquired by this
				** connection. */
#endif
#ifdef ctFeatREPLICAT
	pVOID	spradstt;	/* Replication admin state pointer. */
#endif
#ifdef ctFeatDFRIDXsrvr
	pVOID	sdfrkrwlock;	/* Deferred index rwlock held during RUCB. */
#endif
#ifdef ctFeatFULLTEXTIDX
	pVOID sctdbSessionHandle;
#endif
#ifdef ctFeatADDIDXMBR
	NINT	snaddmbr;	/* Number of index members being added. */
#endif
#ifdef ctFeatLOCKfile
	NINT	stlkcnt;	/* Current number of table locks. */
#endif
#ifdef ctBEHAV_FLUSH_NODE_MARKS
	pSHADLST scurshd;	/* Current preimage space entry. */
#endif
#ifdef ctFeatFLEXREC
	pVOID	sprecmetadata;	/* record metadata pointer */
#endif
#ifdef ctFeatTEMPDIR
	FILNO	stmpdirdatno;	/* temp dir file user file number */
#endif
#ifdef ctFeatDeferAutotrn
	TEXT	sdfrautotrn; /* deferred end of automatic transaction flag */
#endif
#ifdef ctFeatKSEGDEFxtd
	ppctKSEGDEF
		spuksegdef;	/* array of extended key segment definition pointers */
	NINT	snuksegdef;	/* number of extended key segment definition pointers */
#endif
#ifdef ctFeatCONNECTION_LEVEL_IO_STATS
	/* I/O statistics for this connection: */
	ULONG8	sDiskReadOps;	/* number of disk read operations	*/
	ULONG8	sDiskReadBytes; /* number of bytes read from disk	*/
	ULONG8	sDiskWriteOps;	/* number of disk write operations	*/
	ULONG8	sDiskWriteBytes;/* number of bytes written to disk	*/
	ULONG8	sDataCacheReqs; /* number of data cache requests	*/
	ULONG8	sDataCacheHits; /* number of data cache hits		*/
	ULONG8	sIndexCacheReqs;/* number of index cache requests	*/
	ULONG8	sIndexCacheHits;/* number of index cache hits		*/
#endif
#ifdef ctFeatTRANSACTION_ID
	ULONG8	transactionId; /* transaction id */
#endif
	itim_err_context_t itim_err_context; /* context in which ITIM_ERR occurred */
#ifdef ctDEBUG_COMPACT_TRUNCATE
        NINT    truncateForcedErrorLocation; /* location of forced error in file truncate */
        TEXT    truncateExitOnForcedError; /* non-zero if process is to exit at forced error location in file truncate */
#endif
#ifdef ctDBG_REPLICAT_SYNC2
        NINT    syncReplForcedErrorLocation; /* location of forced error for testing synchronous replication */
        TEXT    syncReplExitOnForcedError; /* non-zero if process is to exit at forced error location */
#endif
	TEXT	checkConflictingOpenFilno; /* check if the connection already has the file open with a conflicting access mode */
	FILNO	conflictingOpenFilno; /* file number that the connection has already open with a conflicting access mode */
#ifdef ctFeatSYSTEM_FILE_ID_LIST
	LONG8	sdevid; /* system file id device id for the file that is being opened */
	LONG8	sfileidx; /* system file id file index for the file that is being opened */
#endif
	pTEXT	pathOverride; /* path to use for open call */
#ifdef ctFeatKEEPOPENoffAtLogoff
        TEXT    keepOpenOffAtLogoff; /* turn off keepopen for selected files at logoff */
#endif
#ifdef ctBEHAV_USR_FILES_RESERVED
	NINT	usedReserve; /* count of reserved filno's in use */
#endif
#ifdef ctFeatREPLICAT_SYNC2_SRVR
	ULONG	syncCommitLog;	/* SYNC_COMMIT log#	*/
	ULONG	syncCommitPos;	/* SYNC_COMMIT pos	*/
	ULONG	syncCommitDataLength; /* size of data in SYNC_COMMIT entry */
#endif
#ifdef ctDBG_SYNCREPL_COMMIT_WAIT
	LONG8	syncCommitWaitTime; /* total time waited on sync commit notification */
	LONG8	syncCommitWaitCount; /* total number of sync commit notification waits */
	LONG8	syncCommitWriteLogTime; /* total time waited on flushed log writes for sync commit */
	LONG8	syncCommitWriteLogCount; /* total number of flushed log writes for sync commit */
#endif
	} CTGV;
typedef CTGV ctMEM *	pCTGV;

#ifdef ctFeatREPLICAT
EXTERN pctCNXH ctreplst;	/* push down stack of replication threads */
#ifdef ctFeatREPLICAT_SRVRparallel
EXTERN pctCNXH ctLogShipList;	/* list of log ship state entries */
EXTERN ctRWLOCK ctLogShipListRWL; /* reader/writer lock for list ship state list */
#endif
#endif

#ifdef TRANPROC

#define	cthHASHbins	1024
#define cthHASHmask	(cthHASHbins - 1)
#ifdef ctFeatIICT
EXTERN	pUSRTRN	cttrnhsh[cthHASHbins];	/* transaction user hash list anchors */
					/* thHASHbins must be a power of two  */
#else
EXTERN	pCTGV	cttrnhsh[cthHASHbins];	/* transaction user hash list anchors */
					/* thHASHbins must be a power of two  */
#endif
#endif

typedef struct {
	pCTIS1  s1;
	ppCTIS2 s2;
	pFILNO *sct_kyorg;
	pFILNO *sct_kymap;
#ifdef ctOldALCSET
	pSAVSET sct_savset;

	COUNT   sseqlen;		/* significant length of key	*/
	COUNT   sseqkey;		/* current keyno		*/
	COUNT   sseqnum;		/* current set number		*/
	COUNT   smaxqset;
#else
	ppSAVSET
		sct_savset;		/* pointer to hash anchors	*/
	pSAVSET	sseqnum;		/* current set pointer		*/
	COUNT   sseqlen;		/* significant length of key	*/
	FILNO   sseqkey;		/* current keyno		*/
#endif
	COUNT	sct_nwrcfg;
	FILNO	sct_vfsg;
	COUNT	sct_ismlk;
	COUNT	sct_fndlen;		/* bytes in ct_fndval to save	*/
#ifdef ctFeatRECRLOCK
	NINT	sct_ismrc;
#endif
#ifdef RTREE
	FILNO	ssrtknm;
	FILNO	ssrtdat;
	FILNO	stmpdat;
#endif

	TEXT    sseqbuf[MAXLEN];	/* holds matching "partial" key */
	TEXT    sseqold[MAXLEN];	/* holds previous "partial" key */
	TEXT	sct_fndval[MAXLEN];
	} CTIS;
typedef CTIS ctMEM *	pCTIS;
typedef CTIS ctMEM * ctMEM * ppCTIS;

EXTERN pVOID   ctThrdUserVar[MXU2];

#ifndef CTBOUND

typedef struct ismcom {
	pLQMSG		lqp;
	pLQMSG2		plqmsg2;
	preqPARMB	ppb;
	prspPARMB	pqb;
#if defined(ctFeatCLIENTID) && defined(ctFeatLOGONSECtr)
	pVOID		pclientid;
	NINT		clientidlen;
#endif
} ISMCOM, *pISMCOM;

#ifdef ctCACHE_MEMORY

typedef struct usrcom {
	pTEXT	buf;
	VRLEN	len;
	VRLEN	pos;
	NINT	ver;
	ULONG	atr;
#ifdef ctHUGEFILE
	NINT	off;
#endif
#ifdef ctFeatTRACK_CLIENT_ADDR
	ctUADDR_T ipaddr; /* client IP address */
#endif
#ifdef ctFeatPWDSEC
	UTEXT	hp[PWDSECHSHLEN];
#endif
#ifdef ctFeatLOGONSECtr
	ISMCOM	isc;		/* communication vars for ISAM connect	   */
#endif
#ifdef ctFeatCONNGROUP
	COUNT	conngrptsk;	/* connection group task ID		   */
	COUNT	mytaskid;	/* task ID for this connection		   */
	COUNT	conndlt;	/* change in ctcusers for this connection  */
	struct
	usrcom *conngrpnxt;	/* next entry in connection group list	   */
	struct
	usrcom *conngrpprv;	/* previous entry in connection group list */
#endif
#ifdef ctFeatLOGLMT
	TEXT	loglmt;		/* user/group logon count was incremented  */
#endif
	TEXT	rcbvern;	/* replication change buffer version	   */
#ifdef ctFeatDMPSEMArwlock
	TEXT	dmpsemastt;	/* dmpsema state for this connection. Values:
				DMPSEMA_NOLOCK, CTREAD, or CTWRITE */
#endif
#ifdef ctFeatCOUNT_FCWORKERS
	TEXT	isWorker;	/* is a worker connection */
#endif
} USRCOM;
typedef USRCOM ctMEM *	pUSRCOM;
typedef USRCOM ctMEM * ctMEM * ppUSRCOM;

EXTERN pUSRCOM ct_com[MXU2];
EXTERN pTEXT   ct_comb;

#define ctusrbuf	ct_com[sOWNR]->buf
#define ctusrlen	ct_com[sOWNR]->len
#define ctusrpos	ct_com[sOWNR]->pos
#define ctclnver	ct_com[sOWNR]->ver
#define ctclnatr	ct_com[sOWNR]->atr
#define ctoutoffm(a)	ct_com[a]->off
#define ctusripaddr	ct_com[sOWNR]->ipaddr
#define ctusrhp		ct_com[sOWNR]->hp
#define ctusrismcom	ct_com[sOWNR]->isc
#define ctusrconngrptsk	ct_com[sOWNR]->conngrptsk
#define ctusrconngrpnxt	ct_com[sOWNR]->conngrpnxt
#define ctusrconngrpprv	ct_com[sOWNR]->conngrpprv
#define ctdmpsemastt(a)	ct_com[a]->dmpsemastt

#else /* ~ctCACHE_MEMORY */

#ifdef ctFeatCTSRVR_COMMP
EXTERN pTEXT   sctusrbuf[MXU2]; /* user commbuffer */
EXTERN VRLEN   sctusrlen[MXU2]; /* commbuffer length */
EXTERN VRLEN   sctusrpos[MXU2]; /* position in buffer */
EXTERN NINT    sctclnver[MXU2]; /* client version from pb.pbvr */
EXTERN ULONG   sctclnatr[MXU2]; /* client attributes */
#ifdef ctHUGEFILE
EXTERN NINT    sctoutoff[MXU2];	/* client dependent output_offset */
#endif
#ifdef ctFeatTRACK_CLIENT_ADDR
EXTERN ULONG   sctusripaddr[MXU2]; /* client IP address */
#endif
#ifdef ctFeatPWDSEC
EXTERN UTEXT   sctusrhp[MXU2][PWDSECHSHLEN];
#endif
#ifdef ctFeatLOGONSECtr
EXTERN ISMCOM  sctusrismcom[MXU2];
#endif
#endif /* ctFeatCTSRVR_COMMP */

#define ctusrbuf	sctusrbuf[sOWNR]
#define ctusrlen	sctusrlen[sOWNR]
#define ctusrpos	sctusrpos[sOWNR]
#define ctclnver	sctclnver[sOWNR]
#define ctclnatr	sctclnatr[sOWNR]
#define ctoutoffm(a)	sctoutoff[a]
#define ctusripaddr	sctusripaddr[sOWNR]
#define ctusrhp		sctusrhp[sOWNR]
#define ctusrismcom	sctusrismcom[sOWNR]

#endif /* ~ctCACHE_MEMORY */
#endif /* ~CTBOUND */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ctFeatSrvTimer
EXTERN SRVTIMER		ctsrvtimer[MXU2];
#endif

#ifdef ctFeatSrvLock
EXTERN SRVLOCK		ctsrvlock[MXU2];
#endif

#ifdef ctFeatFNCMEMSTATS
#include "ctparm.h"
EXTERN FNCMEM		ctfuncmem[MXU2][CTI_MXFN+1];
EXTERN LONG8		mballccnt;
EXTERN LONG8		mbfreecnt;
EXTERN LONG8		ctgetmemcnt;
EXTERN LONG8		ctputmemcnt;
#endif

#ifdef ctCACHE_MEMORY
EXTERN DllExtImp pCTSTATV ctstatv[MXU2];
EXTERN pTEXT	ctstatvb;

#define uerr_codm(a)	ctstatv[a]->uec
#define isam_errm(a)	ctstatv[a]->iec
#define sysiocodm(a)	ctstatv[a]->sec

#else

EXTERN DllExtImp CTSTATV	ctstatv[MXU2];
EXTERN NINT	sctua[MXU2];
EXTERN NINT	sctma[MXU2];
#ifdef ctWORKMON
EXTERN NINT	sctwa[MXU2];
#ifdef ctFeatWORKcount
EXTERN NINT	sctwc[MXU2];
#endif
#endif
#ifdef ctFeatFILEBLOCK
EXTERN NINT	sctfbp[MXU2];	/* file block: pending file status change */
EXTERN NINT	sctfbs[MXU2];	/* file block: active			  */
EXTERN NINT	sctfbr[MXU2];	/* file block: blocker			  */
#endif

#define uerr_codm(a)	ctstatv[a].uec
#define isam_errm(a)	ctstatv[a].iec
#define sysiocodm(a)	ctstatv[a].sec
#endif

#ifdef __cplusplus
}
#endif

#ifdef ctPortVINES
#ifdef RUNTCBTABLE
EXTERN NINT    ctusrmapId;
EXTERN taskid  ctusrhmap[MXU2];
#else
EXTERN NINT    ctusrhmap[MXU2];
#endif
#else
EXTERN NINT    ctusrhmap[MXU2];
#endif
EXTERN NINT    ctusrhcnt[MXU2];

EXTERN NINT	ctusraflg[MXU2];	/* HYS if independent thread attached */
#ifdef ctFeatCOUNT_FCWORKERS
EXTERN TEXT	ctusrwflg[MXU2];	/* non-zero if this is a worker thread */
#endif
#ifdef CTBOUND
EXTERN NINT	ctst[MXU2];
#endif

EXTERN pCTGV   ctgv[MXU2];

#ifdef CTTHRDH
EXTERN NLONG   ctrcparm[MXU2];
#endif

EXTERN ppCTIS  ctis;

EXTERN ppFUSR  ct_fusr;
#ifdef ctFeatFUSRrwlock
EXTERN RWLOCKmut ct_furwlk[MXU2];	/* reader/writer lock for ct_fusr */
#endif
EXTERN pBLULST ct_blk[MXU2];
#ifdef ctFeatIMPERSONATEtask
EXTERN pBLKLST im_blk[MXU2];
#endif
#ifdef ctFeatFILEBLOCK
EXTERN pBLKLST fb_blk[MXU2];
#endif
#ifdef ctFeatCPU_LIMIT
EXTERN SEMAtim ctCPU_LIMITsema; /* wait for next CPU limit check */
#endif
#ifdef ctFeatDISKFULLaction
EXTERN SEMAtim ctDISKFULLactionsema; /* wait for next DISK FULL check */
#endif

#ifdef ctDBGstack
#define stkbase		lctgv->sstkbase
#define stkaapi		lctgv->sstkaapi
#define stktrip		lctgv->sstktrip
#endif
#ifdef DBGtree
#define ct_walkh	lctgv->sct_walkh
#define ct_walkt	lctgv->sct_walkt
#define ctlflg		lctgv->sctlflg
#endif /* DBGtree */
#ifdef DBGhash
#define dbg_shsh_u(owner) ctgv[owner]->sdbg_shsh_u
#endif
#ifndef ctFeatIICT
#define ct_ubit(owner)	ctgv[owner]->sct_ubit
#define shadstt(owner)	lctgv->sshadstt
#define ct_usrsv(owner)	lctgv->sct_usrsv
#define ct_rstflg(owner)lctgv->sct_rstflg
#endif
#define ctconanc	lctgv->sctconanc
#define ctconid		lctgv->sctconid
#define tranactv	lctgv->stranactv
#define transavp	lctgv->stransavp
#define abnlog		lctgv->sabnlog
#define cmtseq		lctgv->scmtseq
#define cmtfil		lctgv->scmtfil
#define cmtlhw		lctgv->scmtlhw
#define cmtllw		lctgv->scmtllw
#define lfwchn		lctgv->slfwchn
#ifdef ctCMPLOG
#define logcmpcnt	lctgv->slogcmpcnt
#define logcmpbuf	lctgv->slogcmpbuf
#define logcmplen	lctgv->slogcmplen
#endif
#ifndef CTBOUND
#define ctops_clr	lctgv->sctops_clr
#endif
#ifdef ctCREATE_SEMA
#define resema		lctgv->sresema
#endif
#ifdef ctSTATIC_SEMA
#define resema		ctsresema[sOWNR]
#endif
#define lOWNER		lctgv->slOWNR
#define lINSTC		lctgv->slCNTR
#ifdef TRANPROC
#define preiseq		lctgv->spreiseq
#define isolev		lctgv->sisolev
#endif
#define applst		lctgv->sapplst
#define ctblktim	lctgv->sctblktim
#define ctbatch		lctgv->batch
#define ctbatnum	lctgv->sbatnum
#define ctbatmax	lctgv->sbatmax
#define ct_savbat	lctgv->ssavbat
#define cthistory	lctgv->history
#define cthistund	lctgv->histund
#define cthstnum	lctgv->shstnum
#define ct_savhst	lctgv->ssavhst
#ifdef ctDYNHASH
#define ct_lokstt	lctgv->sct_lokstt
#define ct_locksb	lctgv->sct_locksb
#define ct_locks(bin)	lctgv->sct_locksb[bin].h
#define ct_ltail(bin)	lctgv->sct_locksb[bin].t
#else
#define ct_locksb	lctgv->sct_locksb
#define ct_locks(bin)	lctgv->sct_locksb[bin]
#define ct_ltailb	lctgv->sct_ltailb
#define ct_ltail(bin)	lctgv->sct_ltailb[bin]
#endif
#ifdef DBGhash
#define dbg_lhsh_u	lctgv->sdbg_lhsh_u
#endif
#define ctusrprf	lctgv->sctusrprf
#define ctumxfil	lctgv->sctumxfil
#define cthghfil	lctgv->scthghfil
#define ucamfnc		lctgv->sucamfnc
#define ucamptr		lctgv->sucamptr
#define ct_cam		lctgv->sct_cam
#define ct_camsiz	lctgv->sct_camsiz
#define ucamlen		lctgv->sucamlen
#define ctops		lctgv->sctops
#define ctstate		lctgv->sctstate
#define ctstat2		lctgv->sctstat2
#define ctstat3		lctgv->sctstat3
#define ctstat4		lctgv->sctstat4
#define ctstat5		lctgv->sctstat5
#define ctstat6		lctgv->sctstat6
/* ctSIBLING_CTSTATE - Add new state variable here */
#define ctstatg		lctgv->sctstatg
#define udlokdyn	lctgv->sudlokdyn
#define ctdfrcls	lctgv->sctdfrcls
#define ctxvlen		lctgv->sctxvlen
#define seglsthdr	lctgv->sseglsthdr
#define ctcidxStk	lctgv->sctcidxStk
#define ctcidxRecInfo	lctgv->sctcidxRecInfo
#define ctcidxMaxFlds	lctgv->sctcidxMaxFlds
#define ctcidxStkPtr	lctgv->sctcidxStkPtr
#define ctcidxCurCmd	lctgv->sctcidxCurCmd
#ifdef ctFeatUDF_EXPR
#define udflist		lctgv->sudflist
#define isexpreval	lctgv->sisexpreval
#endif
#ifdef ctHUGEFILE
#define autopos2	lctgv->sautopos2
#endif
#define autopos1	lctgv->sautopos1
#define autopart	lctgv->sautopart
#define logtime		lctgv->slogtime
#define trntime		lctgv->strntime
#define trntdly		lctgv->strntdly
#if defined(ctFeatINTERNAL_FILE_CONTROL) && defined(ctFeatPRICACHE)
#define prichetaskid	lctgv->sprichetaskid
#endif
#if defined(ctFeatINTERNAL_FILE_CONTROL) && defined(ctFeatDFRIDX)
#define dfridxtaskid	lctgv->sdfridxtaskid
#endif
#ifdef ctFeatRUCB
#define rucbsess	lctgv->srucbsess
#endif
#ifdef ctFeatSNAPSHOT
#define markbeg		lctgv->smarkbeg
#define marktim		lctgv->smarktim
#define markcnt		lctgv->smarkcnt
#define trntsum		lctgv->strntsum
#define trntmax		lctgv->strntmax
#define trntcnt		lctgv->strntcnt
#define trntdet		lctgv->strntdet
#define ctutrbeg	lctgv->sctutrbeg
#define ctutrend	lctgv->sctutrend
#define ctutrabt	lctgv->sctutrabt
#endif
#define rqstime		lctgv->srqstime
#define rqsfunc		lctgv->srqsfunc
#define rqssubf		lctgv->srqssubf
#define userlqp		lctgv->suserlqp
#define nodname		lctgv->snodname
#define nbrfile		lctgv->snbrfile
#define actflag		lctgv->sactflag
#define cominfo		lctgv->scominfo
#ifdef ctCAMOsdk
#define ctcamver	lctgv->sctcamver
#endif
#define netrecr		lctgv->snetrecr
#define cthghwrd	lctgv->scthghwrd
#define fncret		lctgv->sfncret
#define fncretflex	lctgv->sfncretflex
#define prvlokf		lctgv->sprvlokf
#define prvlokt		lctgv->sprvlokt
#define prvlokt2	lctgv->sprvlokt2
#define prvlokp		lctgv->sprvlokp
#define prvlokh		lctgv->sprvlokh
#ifdef ctCUSTOM
#define pcustmem	spcustmem[sOWNR]
#define custops		scustops[sOWNR]
#endif
#ifndef ctCACHE_MEMORY
#define ct_usrsi	sct_usrsi[sOWNR]
#define ctusrsum	sctusrsum[sOWNR]
#define ctusrtot	sctusrtot[sOWNR]
#endif
#ifdef TRANPROC
#ifndef ctCACHE_MEMORY
#define ctshdmem	sctshdmem[sOWNR]
#endif
#ifdef ctBEHAV_CLUP
#define ct_clupflg	lctgv->sct_clupflg
#define ct_clupcnt	lctgv->sct_clupcnt
#define ct_clupstr	lctgv->sct_clupstr
#define ct_pclup	lctgv->sct_pclup
#endif
#endif
#define ct_uflgs	lctgv->sct_uflgs
#define ct_kltsk	lctgv->sct_kltsk
#define whdrflg		lctgv->swhdrflg
#define ctrbflg		lctgv->sctrbflg
#define ct_trdflg	lctgv->sct_trdflg
#define ct_userid	lctgv->sct_userid
#define ct_usernm	lctgv->sct_usernm
#define ct_sqlpwd	lctgv->sct_sqlpwd
#define ct_userg	lctgv->sct_userg
#define ct_mltopn	lctgv->sct_mltopn
#define ct_dbglcnt	lctgv->sct_dbglcnt
#define ct_fseq		lctgv->sct_fseq
#define ct_fup		lctgv->sct_fup
#ifdef ctHUGEFILE
#define ct_gsrl2	lctgv->sct_gsrl2
#define ct_ldnybyt2	lctgv->sct_ldnybyt2
#endif /* ctHUGEFILE */
#define IDfield_lstoff	lctgv->sIDfield_lstoff
#define ct_IDfield	lctgv->sct_IDfield
#define ct_ldnybyt1	lctgv->sct_ldnybyt1
#define ct_ldnyfil	lctgv->sct_ldnyfil

#define qreadg		lctgv->sqreadg
#define qlinks		lctgv->sqlinks

#ifdef ctFeatSrvTimer
#define tim_call	ctsrvtimer[sOWNR].stim_call
#define tim_recv	ctsrvtimer[sOWNR].stim_recv
#define tim_work	ctsrvtimer[sOWNR].stim_work
#define tim_send	ctsrvtimer[sOWNR].stim_send
#define tim_prev	ctsrvtimer[sOWNR].stim_prev
#define tmpwrk		ctsrvtimer[sOWNR].stmpwrk
#define tmprcv		ctsrvtimer[sOWNR].stmprcv
#define tmpsnd		ctsrvtimer[sOWNR].stmpsnd
#define tmpcal		ctsrvtimer[sOWNR].stmpcal
#endif

#ifdef ctFeatSrvLock
#define loktry		ctsrvlock[sOWNR].sloktry
#define lokhlk		ctsrvlock[sOWNR].slokhlk
#define lokblk		ctsrvlock[sOWNR].slokblk
#define lokhbk		ctsrvlock[sOWNR].slokhbk
#define lokdlk		ctsrvlock[sOWNR].slokdlk
#define lokdny		ctsrvlock[sOWNR].slokdny
#define lokfre		ctsrvlock[sOWNR].slokfre
#define lokrel		ctsrvlock[sOWNR].slokrel
#define lokkil		ctsrvlock[sOWNR].slokkil
#endif

#ifdef ctCACHE_MEMORY
#ifdef CTPERM

#define uerr_cod	ctstatv[sOWNR]->uec
#define sysiocod	ctstatv[sOWNR]->sec
#define isam_err	ctstatv[sOWNR]->iec
#define isam_fil	ctstatv[sOWNR]->ifl
/* Define macros that can be used to get and set the c-tree error code values,
even if the error code macros get redefined (by ctreep.h for example). */
#define ct_get_uerr_cod( )	(ctstatv && ctstatv[sOWNR] ? ctstatv[sOWNR]->uec : -1)
#define ct_set_uerr_cod(e)	(ctstatv && ctstatv[sOWNR] ? (ctstatv[sOWNR]->uec = (e), 0) : -1)
#define ct_get_sysiocod( )	(ctstatv && ctstatv[sOWNR] ? ctstatv[sOWNR]->sec : -1)
#define ct_set_sysiocod(e)	(ctstatv && ctstatv[sOWNR] ? (ctstatv[sOWNR]->sec = (e), 0) : -1)
#define ct_get_isam_err( )	(ctstatv && ctstatv[sOWNR] ? ctstatv[sOWNR]->iec : -1)
#define ct_set_isam_err(e)	(ctstatv && ctstatv[sOWNR] ? (ctstatv[sOWNR]->iec = (e), 0) : -1)
#define ct_get_isam_fil( )	(ctstatv && ctstatv[sOWNR] ? ctstatv[sOWNR]->ifl : -1)
#define ct_set_isam_fil(e)	(ctstatv && ctstatv[sOWNR] ? (ctstatv[sOWNR]->ifl = (e), 0) : -1)

#define cndxerr		ctstatv[sOWNR]->cec
#define deltaconn	ctstatv[sOWNR]->dcn
#else

#define uerr_cod	ctstatv[OWNER]->uec
#define sysiocod	ctstatv[OWNER]->sec
#define isam_err	ctstatv[OWNER]->iec
#define isam_fil	ctstatv[OWNER]->ifl
/* Define macros that can be used to get and set the c-tree error code values,
even if the error code macros get redefined (by ctreep.h for example). */
#define ct_get_uerr_cod( )	(ctstatv && ctstatv[OWNER] ? ctstatv[OWNER]->uec : -1)
#define ct_set_uerr_cod(e)	(ctstatv && ctstatv[OWNER] ? (ctstatv[OWNER]->uec = (e), 0) : -1)
#define ct_get_sysiocod( )	(ctstatv && ctstatv[OWNER] ? ctstatv[OWNER]->sec : -1)
#define ct_set_sysiocod(e)	(ctstatv && ctstatv[OWNER] ? (ctstatv[OWNER]->sec = (e), 0) : -1)
#define ct_get_isam_err( )	(ctstatv && ctstatv[OWNER] ? ctstatv[OWNER]->iec : -1)
#define ct_set_isam_err(e)	(ctstatv && ctstatv[OWNER] ? (ctstatv[OWNER]->iec = (e), 0) : -1)
#define ct_get_isam_fil( )	(ctstatv && ctstatv[OWNER] ? ctstatv[OWNER]->ifl : -1)
#define ct_set_isam_fil(e)	(ctstatv && ctstatv[OWNER] ? (ctstatv[OWNER]->ifl = (e), 0) : -1)

#define cndxerr		ctstatv[OWNER]->cec
#define deltaconn	ctstatv[OWNER]->dcn
#endif
#define ctusrtot	ctstatv[sOWNR]->tot
#define ctusrsum	ctstatv[sOWNR]->sum
#define ct_usrsi	ctstatv[sOWNR]->usi
#define ctua(a)		ctstatv[a]->ua
#define ctma(a)		ctstatv[a]->ma
#ifdef ctWORKMON
#define ctwa(a)		ctstatv[a]->wa
#ifdef ctFeatWORKcount
#define ctwc(a)		ctstatv[a]->wc
#endif
#ifdef ctFeatMAXACTCONN
#define ctwv(a)		ctstatv[a]->wv
#endif
#endif
#ifdef ctFeatFILEBLOCK
#define ctfbp(a)	ctstatv[a]->fbp
#define ctfbs(a)	ctstatv[a]->fbs
#define ctfbr(a)	ctstatv[a]->fbr
#endif

#else /* ~ctCACHE_MEMORY */

#ifdef CTPERM

#define uerr_cod	ctstatv[sOWNR].uec
#define sysiocod	ctstatv[sOWNR].sec
#define isam_err	ctstatv[sOWNR].iec
#define isam_fil	ctstatv[sOWNR].ifl
/* Define macros that can be used to get and set the c-tree error code values,
even if the error code macros get redefined (by ctreep.h for example). */
#define ct_get_uerr_cod( )	(ctstatv ? ctstatv[sOWNR].uec : -1)
#define ct_set_uerr_cod(e)	(ctstatv ? (ctstatv[sOWNR].uec = (e), 0) : -1)
#define ct_get_sysiocod( )	(ctstatv ? ctstatv[sOWNR].sec : -1)
#define ct_set_sysiocod(e)	(ctstatv ? (ctstatv[sOWNR].sec = (e), 0) : -1)
#define ct_get_isam_err( )	(ctstatv ? ctstatv[sOWNR].iec : -1)
#define ct_set_isam_err(e)	(ctstatv ? (ctstatv[sOWNR].iec = (e), 0) : -1)
#define ct_get_isam_fil( )	(ctstatv ? ctstatv[sOWNR].ifl : -1)
#define ct_set_isam_fil(e)	(ctstatv ? (ctstatv[sOWNR].ifl = (e), 0) : -1)

#define cndxerr		ctstatv[sOWNR].cec
#define deltaconn	ctstatv[sOWNR].dcn
#else

#define uerr_cod	ctstatv[OWNER].uec
#define sysiocod	ctstatv[OWNER].sec
#define isam_err	ctstatv[OWNER].iec
#define isam_fil	ctstatv[OWNER].ifl
/* Define macros that can be used to get and set the c-tree error code values,
even if the error code macros get redefined (by ctreep.h for example). */
#define ct_get_uerr_cod( )	(ctstatv ? ctstatv[OWNER].uec : -1)
#define ct_set_uerr_cod(e)	(ctstatv ? (ctstatv[OWNER].uec = (e), 0) : -1)
#define ct_get_sysiocod( )	(ctstatv ? ctstatv[OWNER].sec : -1)
#define ct_set_sysiocod(e)	(ctstatv ? (ctstatv[OWNER].sec = (e), 0) : -1)
#define ct_get_isam_err( )	(ctstatv ? ctstatv[OWNER].iec : -1)
#define ct_set_isam_err(e)	(ctstatv ? (ctstatv[OWNER].iec = (e), 0) : -1)
#define ct_get_isam_fil( )	(ctstatv ? ctstatv[OWNER].ifl : -1)
#define ct_set_isam_fil(e)	(ctstatv ? (ctstatv[OWNER].ifl = (e), 0) : -1)

#define cndxerr		ctstatv[OWNER].cec
#define deltaconn	ctstatv[OWNER].dcn
#endif
#define ctua(a)		sctua[a]
#define ctma(a)		sctma[a]
#ifdef ctWORKMON
#define ctwa(a)		sctwa[a]
#ifdef ctFeatWORKcount
#define ctwc(a)		sctwc[a]
#endif
#endif
#ifdef ctFeatFILEBLOCK
#define ctfbp(a)	sctfbp[a]
#define ctfbs(a)	sctfbs[a]
#define ctfbr(a)	sctfbr[a]
#endif
#endif /* ~ctCACHE_MEMORY */

#define ct_uflvr	lctgv->sct_uflvr
#define ct_ualgn	lctgv->sct_ualgn
#define ct_upntr	lctgv->sct_upntr
#define ct_temppw	lctgv->sct_temppw
#define ct_flagpw	lctgv->sct_flagpw
#define ct_buf		lctgv->sct_buf
#define ct_gsrl1	lctgv->sct_gsrl1
#define ct_rbuf		lctgv->sb_ct_rbuf
#define ct_pbuf		lctgv->sb_ct_pbuf
#define rerr_cod	lctgv->sb_rerr_cod
#define rerr_fil	lctgv->sb_rerr_fil
#define ct_fp		lctgv->sb_ct_fp
#define ct_redom	lctgv->sb_ct_redom
#define ct_bsz		lctgv->sb_ct_bsz
#define ct_spc		lctgv->sb_ct_spc
#define ksgcuru		lctgv->sksgcuru
#define ksgtotu		lctgv->sksgtotu
#define ksglstu		lctgv->sksglstu
#define ua_han		lctgv->sua_han
#define ua_cal		lctgv->sua_cal
#define ua_cnt		lctgv->sua_cnt
#define ua_typ		lctgv->sua_typ
#define ua_cur		lctgv->sua_cur
#define ua_tot		lctgv->sua_tot
#define ua_lst		lctgv->sua_lst
#define curfnc		(lctgv ? lctgv->scurfnc : 0)
#ifdef ctFeatLOGREAD
#define ctlogred	lctgv->sctlogred
#define ctreplopts	lctgv->sctreplopts
#endif
#ifdef ctFeatSCANCACHE
#define scanfiles	lctgv->sscanfiles
#endif
#ifdef RB_CALLBACK
#define rblcbfnc	lctgv->srblcbfnc
#define rblcbcnt	lctgv->srblcbcnt
#define rblcbstp	lctgv->srblcbstp
#ifdef ctFeatREBUILD_CALLBACK_STATE
#define rblpcbst	lctgv->srblpcbst
#endif
#ifdef RB_CALLBACK_SRVR
#define rblparms	lctgv->srblparms
#endif
#endif
#ifdef ctFeatTRANSFER_FILE
#define xfrparms	lctgv->sxfrparms
#endif
#ifdef ctFeatVFYIDX_CS
#define vfyparms	lctgv->svfyparms
#endif
#ifdef ctFeatSCNLOGkeepaliveSRVR
#define rchparms	lctgv->srchparms
#endif
#ifdef ctFeatRTG_API
#define rtgparms	lctgv->srtgparms
#endif
#ifdef ctFeatDeferAutotrn 
#define  dfrautotrn	lctgv->sdfrautotrn
#endif
#define puksegdef	lctgv->spuksegdef
#define nuksegdef	lctgv->snuksegdef
#ifdef ctFeatCOPYFILE
#define cpfparms	lctgv->scpfparms
#endif
#ifdef ctFeatTEMPDIR
#define tdrparms	lctgv->stdrparms
#endif
#ifdef ctFeatCLICB
#define clicblqp	lctgv->sclicbp.lqp
#define clicblq2	lctgv->sclicbp.plqmsg2
#define clicbppb	lctgv->sclicbp.ppb
#define clicbpqb	lctgv->sclicbp.pqb
#endif
#define ctopnmod	lctgv->sctopnmod
#define ctsqlcommp	lctgv->ssqlcommp
#define ctpfilwcd	lctgv->sctpfilwcd
#define ctwcdcnv	lctgv->sctwcdcnv
#define ctdlok_loc	lctgv->sctdlok_loc
#define ctdlok_own	lctgv->sctdlok_own
#ifdef ctFeatREPL_SRLSEG
#define usrsnum1	lctgv->susrsnum1
#define usrsnum2	lctgv->susrsnum2
#endif
#define phnsemaINusr	lctgv->sphnsemaINusr
#define phnsemaPNusr	lctgv->sphnsemaPNusr
#define sequfl		lctgv->ssequfl
#define seqcnt		lctgv->sseqcnt
#define cmbiobuf	lctgv->scmbiobuf
#define cmbiolen	lctgv->scmbiolen
#define cmbiostt	lctgv->scmbiostt
#define cmlkchksiz	lctgv->scmlkchksiz
#define cmlkfilnum	lctgv->scmlkfilnum
#define cmlkchkres	lctgv->scmlkchkres
#define chkcmprec	lctgv->schkcmprec
#define skpimglen	lctgv->sskpimglen
#define cmprecbuf	lctgv->scmprecbuf
#define cmprecsiz	lctgv->scmprecsiz
#define ubiobuf		lctgv->subiobuf
#define ubiolen		lctgv->subiolen
#define rblhnum		lctgv->srblhnum
#define rblrawno	lctgv->srblrawno
#define prmidxcnt	lctgv->sprmidxcnt
#define xtdopnmod	lctgv->sxtdopnmod
#define cursuphstno	lctgv->scursuphstno
#define pusrstate	lctgv->spusrstate
#define usr_cmprec_type	lctgv->susr_cmprec_type
#define usr_cmprec_vrsn	lctgv->susr_cmprec_vrsn
#define usr_cmprec_plen	lctgv->susr_cmprec_plen
#define usr_cmprec_dll	lctgv->susr_cmprec_dll
#define usr_cmprec_allc	lctgv->susr_cmprec_allc
#define usr_cmprec_parm	lctgv->susr_cmprec_parm
#define kofilno		lctgv->skofilno
#define cachits		lctgv->scachits
#define bufreqs		lctgv->sbufreqs
#define bufhits		lctgv->sbufhits
#define cacreqs		lctgv->scacreqs
#define kbufrec		lctgv->skbufrec
#define kbufrecsiz	lctgv->skbufrecsiz
#define memfilrefcnt	lctgv->smemfilrefcnt
#define memfilsysno	lctgv->smemfilsysno
#define ctdbSessionHandle lctgv->sctdbSessionHandle
#define naddmbr		lctgv->snaddmbr
#define usr_tlkcnt	lctgv->stlkcnt
#define curshd		lctgv->scurshd
#define precmetadata	lctgv->sprecmetadata
#define tmpdirdatno	lctgv->stmpdirdatno
#define CTU_transactionId lctgv->transactionId
#define CTU_itim_err_context lctgv->itim_err_context
#define CTU_truncateForcedErrorLocation lctgv->truncateForcedErrorLocation
#define CTU_truncateExitOnForcedError lctgv->truncateExitOnForcedError
#define CTU_syncReplForcedErrorLocation lctgv->syncReplForcedErrorLocation
#define CTU_syncReplExitOnForcedError lctgv->syncReplExitOnForcedError

	/* ~MULTITRD */
#else	/* ~MULTITRD */
	/* ~MULTITRD */

EXTERN NINT    ct_maxvfil;	/* maximum virtual files opened		*/
EXTERN NINT    cttflg_L;/* stop server in progress:logsema ctl*/
EXTERN BATHDR  ctbatch;
EXTERN LONG    ct_spc;
#ifdef ctOldALCBAT
EXTERN COUNT   ctbatnum;
EXTERN COUNT   ctbatmax;
EXTERN pBATHDR ct_savbat;
#else
EXTERN pSAVBAT ctbatnum;
EXTERN ppSAVBAT
	       ct_savbat;
#endif
EXTERN HSTHDR	cthistory;
EXTERN pHSTLST	cthistund;
EXTERN pSAVHST	cthstnum;
EXTERN ppSAVHST	ct_savhst;
EXTERN pVOID	ctcidxStk;
EXTERN pSEGLST	seglsthdr;
EXTERN pTEXT	ct_trnfil;
EXTERN NINT	prvlokf;
EXTERN NINT	prvlokt;
EXTERN NINT	prvlokt2;
EXTERN LONG	prvlokp;
#ifdef ctHUGEFILE
EXTERN LONG	prvlokh;
#endif
EXTERN NINT  ctcidxStkPtr;
EXTERN NINT  ctcidxCurCmd;
#ifdef ctFeatUDF_EXPR
EXTERN pVOID udflist
EXTERN NINT  isexpreval
#endif
EXTERN COUNT ctconid;
EXTERN ppctICON
	     ctconanc;	/* hash bins for context */
#ifdef DBGtree
EXTERN pVOID ct_walkh;
EXTERN pVOID ct_walkt;
EXTERN NINT  ctlflg;
#endif /* DBGtree */
#ifdef TRANPROC
#define ct_ubit(owner)	sct_ubit
EXTERN ppSHADLST sct_ubit;	/* hash bins for srchshd */
#ifdef DBGhash
#define dbg_shsh_u(owner)	sdbg_shsh_u
EXTERN pLONG sdbg_shsh_u;
#endif
EXTERN pTEXT ct_usrsp;
EXTERN pSHADLST ct_usrsl;
EXTERN VRLEN ct_usrsz;
EXTERN LONG  ctshdmem;
EXTERN LONG  ctusrsum;
EXTERN LONG  ctusrtot;
EXTERN NINT  ct_usrsi;
EXTERN LONG  sct_usrsv;
EXTERN NINT  sct_rstflg;		/* TRANRST() flag */
#define ct_usrsv(a)	sct_usrsv
#define ct_rstflg(a)	sct_rstflg
#endif
EXTERN NINT  ctrbflg;
#ifdef ctDYNHASH
EXTERN pULOKHSH
	      ct_locksb;
EXTERN HSHSTT ct_lokstt;
#define ct_locks(bin)	ct_locksb[bin].h
#define ct_ltail(bin)	ct_locksb[bin].t
#else
EXTERN ppLOKS ct_locksb;
EXTERN ppLOKS ct_ltailb;
#define ct_locks(bin)	ct_locksb[bin]
#define ct_ltail(bin)	ct_ltailb[bin]
#endif
#ifdef DBGhash
EXTERN pLONG  dbg_lhsh_u;
#endif
#ifdef ctCUSTOM
EXTERN pVOID  pcustmem;
EXTERN LONG   custops;
#endif
#ifdef ctCAMO
EXTERN LONG   ucamlen;
EXTERN pCAMFNC
	      ucamfnc;
EXTERN pTEXT  ucamptr;
EXTERN pTEXT  ct_cam;
EXTERN VRLEN  ct_camsiz;
#endif
EXTERN LONG   ctops;		/* set operation state bit mask		*/
EXTERN LONG   ctstate;		/* internal state bit mask		*/
EXTERN LONG   ctstat2;		/* internal state bit mask 2		*/
EXTERN LONG   ctstat3;		/* internal state bit mask 3		*/
EXTERN LONG   ctstat4;		/* internal state bit mask 4		*/
EXTERN LONG   ctstat5;		/* internal state bit mask 5		*/
EXTERN LONG   ctstat6;		/* internal state bit mask 6		*/
/* ctSIBLING_CTSTATE - Add new state variable here */
EXTERN VRLEN  ctxvlen;		/* vlen combined op max buffer length	*/
EXTERN NINT   ctstatg;		/* keyseg distinct count indicator	*/
					

EXTERN COUNT ctusrprf;		/* user profile word */
EXTERN UINT  ctdfrcls;		/* defer close count */
EXTERN UINT  ct_trnfilsz;	/* size of ct_trnfil */
EXTERN IDXSTATE ct_idxstate; /* index state. Access with acquireIdxOpState() */ 
#ifdef ctHUGEFILE
EXTERN LONG  ct_gsrl2;		/* next serial number for data file */
#endif /* ctHUGEFILE */
EXTERN LONG  ct_gsrl1;		/* next serial number for data file */
#ifdef ctFeatDAR
EXTERN LONG8 ct_IDfield;	/* next IDfield number for data file. note:
				** ct_IDfield before last update while ct_gsrl
				** after last update
				*/
#endif
EXTERN NINT  ct_trdflg;		/* thread operation flag */

EXTERN COUNT uerr_cod;		/* user error cod */
EXTERN COUNT sysiocod;		/* system error cod */
EXTERN COUNT isam_err;
EXTERN COUNT isam_fil;
/* Define macros that can be used to get and set the c-tree error code values,
even if the error code macros get redefined (by ctreep.h for example). */
#define ct_get_uerr_cod( )	(uerr_cod)
#define ct_set_uerr_cod(e)	(uerr_cod = (e), 0)
#define ct_get_sysiocod( )	(sysiocod)
#define ct_set_sysiocod(e)	(sysiocod = (e), 0)
#define ct_get_isam_err( )	(isam_err)
#define ct_set_isam_err(e)	(isam_err = (e), 0)
#define ct_get_isam_fil( )	(isam_fil)
#define ct_set_isam_fil(e)	(isam_fil = (e), 0)

EXTERN COUNT cndxerr;		/* conditional index error cod */
EXTERN UTEXT ct_uflvr;
EXTERN UTEXT ct_ualgn;
EXTERN UTEXT ct_upntr;
EXTERN TEXT  ct_buf[CTBUFSIZ];	/* temporary io buffer */

#ifdef RB_CALLBACK
EXTERN pRBLCBFNC rblcbfnc;
EXTERN ULONG     rblcbcnt;
EXTERN UCOUNT    rblcbstp;
#endif

#ifdef ctPARTITION
EXTERN pCTFILE	rblhnum;	/* partition rebuild host dnum	  */
EXTERN NINT	rblrawno;	/* partition rebuild member rawno */
EXTERN NINT	prmidxcnt;	/* number of partition members	  **
				** calling reprmidx in recovery	  */
#endif
#define ctumxfil	ct_mxfil
#define cthghfil	ct_mxfil

#endif /* ~MULTITRD */

EXTERN UINT	ctlog9477;
EXTERN ctZLIB1	ctzlib1;	/* holds zlib vrsn 1 defaults	*/
#if defined(ctCMPREC) && defined(ctFeatZLIBdynamic)
EXTERN NINT	ctzlib_avail;	/* Indicates zlib init status	*/
EXTERN TEXT	ctzlib_errmsg[256]; /* zlib init error buffer	*/
#endif
#ifdef ctFeatOPENSSL
EXTERN NINT	ctssl_avail;	/* Indicates SSL init status	*/
EXTERN TEXT	ctssl_errmsg[256]; /* SSL init error buffer	*/
#endif

#endif /* ~ctCLIENT */

#ifdef __cplusplus
}
#endif

#endif /* ~ctNOGLOBALS */

#ifdef __cplusplus
extern "C" {
#endif

/*
** Globals
*/

#ifdef ctFeatDatAdaptHashBinLocks
EXTERN ULONG	ct_hbTcacG;
EXTERN ULONG	ct_hbRcacG;
#endif

#ifdef ctFeatIdxAdaptHashBinLocks
EXTERN ULONG	ct_hbTbufG;
EXTERN ULONG	ct_hbRbufG;
#endif

EXTERN UINT rucesx,ekirtsx;

/*
** Performance Monitoring Statistics
*/

#ifdef ctFeatSNAPSHOT

EXTERN ctGSMS	ctGSMSi;

#define ctdnd_red	ctGSMSi.sctdnd_red
#define ctdnd_wrt	ctGSMSi.sctdnd_wrt
#define ctdnd_rwt	ctGSMSi.sctdnd_rwt
#define ctdnd_abn	ctGSMSi.sctdnd_abn
#define ctdnd_rmv	ctGSMSi.sctdnd_rmv
#define ctdnd_non	ctGSMSi.sctdnd_non
#define ctloktry	ctGSMSi.sctloktry
#define ctlokhlk	ctGSMSi.sctlokhlk
#define ctlokdny	ctGSMSi.sctlokdny
#define ctlokfre	ctGSMSi.sctlokfre
#define ctlokrel	ctGSMSi.sctlokrel
#define ctlokblk	ctGSMSi.sctlokblk
#define ctlokhbk	ctGSMSi.sctlokhbk
#define ctlokdlk	ctGSMSi.sctlokdlk
#define ctlokkil	ctGSMSi.sctlokkil
#define cttrntim	ctGSMSi.scttrntim
#define cttrncnt	ctGSMSi.scttrncnt
#define cttrndet	ctGSMSi.scttrndet
#define cttrnbox	ctGSMSi.scttrnbox
#define ctloktim	ctGSMSi.sctloktim
#define ctlokcnt	ctGSMSi.sctlokcnt
#define ctlokmax	ctGSMSi.sctlokmax
#define ctlokdet	ctGSMSi.sctlokdet
#define ctlokbox	ctGSMSi.sctlokbox
#define ctxlktim	ctGSMSi.sctxlktim
#define ctxlkcnt	ctGSMSi.sctxlkcnt
#define ctxlkmax	ctGSMSi.sctxlkmax
#define ctxlkdet	ctGSMSi.sctxlkdet
#define ctxlkbox	ctGSMSi.sctxlkbox
#define cttot_call	ctGSMSi.scttot_call
#define cttot_recv	ctGSMSi.scttot_recv
#define cttot_work	ctGSMSi.scttot_work
#define cttot_send	ctGSMSi.scttot_send
#define ctmemhgh	ctGSMSi.sctmemhgh
#define ctmemsum	ctGSMSi.sctmemsum
#define ct_dbrqs	ctGSMSi.sct_dbrqs
#define ct_dbhit	ctGSMSi.sct_dbhit
#define ct_ibrqs	ctGSMSi.sct_ibrqs
#define ct_ibhit	ctGSMSi.sct_ibhit
#define ct_rdops	ctGSMSi.sct_rdops
#define ct_rdbyt	ctGSMSi.sct_rdbyt
#define ct_wrops	ctGSMSi.sct_wrops
#define ct_wrbyt	ctGSMSi.sct_wrbyt
#define ct_rcops	ctGSMSi.sct_rcops
#define ct_rcbyt	ctGSMSi.sct_rcbyt
#define ct_wcops	ctGSMSi.sct_wcops
#define ct_wcbyt	ctGSMSi.sct_wcbyt
#define ctwlgops	ctGSMSi.sctwlgops
#define ctwlgbyt	ctGSMSi.sctwlgbyt
#define ctrlgops	ctGSMSi.sctrlgops
#define ctrlgbyt	ctGSMSi.sctrlgbyt
#define ctxlgops	ctGSMSi.sctxlgops
#define ctxlgbyt	ctGSMSi.sctxlgbyt
#define ct_trbeg	ctGSMSi.sct_trbeg
#define ct_trend	ctGSMSi.sct_trend
#define ct_trabt	ctGSMSi.sct_trabt
#define ct_trsav	ctGSMSi.sct_trsav
#define ct_trrst	ctGSMSi.sct_trrst
#define ct_trfls	ctGSMSi.sct_trfls
#define ct_compflg	ctGSMSi.sct_compflg
#define ct_compflg2	ctGSMSi.sct_compflg2
#define ct_compflg3	ctGSMSi.sct_compflg3
#define ct_compflg4	ctGSMSi.sct_compflg4
#define ct_compflg5	ctGSMSi.sct_compflg5
#define ct_diagflg	ctGSMSi.sct_diagflg
#define ct_diagflg2	ctGSMSi.sct_diagflg2
#define ct_diagflg3	ctGSMSi.sct_diagflg3
#define ct_cmtdly	ctGSMSi.sct_cmtdly
#define ct_chkdly	ctGSMSi.sct_chkdly
#define ct_cmtscl	ctGSMSi.sct_cmtscl
#define ct_cmtbas	ctGSMSi.sct_cmtbas
#define ct_udefer_thld	ctGSMSi.sct_udefer_thld
#define ct_udefer_64yd	ctGSMSi.sct_udefer_64yd
#define ctITIMretry	ctGSMSi.sctITIMretry
#define ctITIMlimit	ctGSMSi.sctITIMlimit
#define ctITIMdefer	ctGSMSi.sctITIMdefer
#define ctITIMfailed	ctGSMSi.sctITIMfailed
#define ctredcmtdfr	ctGSMSi.sctredcmtdfr
#define ctredcmtlpr	ctGSMSi.sctredcmtlpr
#define ctredcmtlpc	ctGSMSi.sctredcmtlpc
#define ctTPNDretry	ctGSMSi.sctTPNDretry
#define ctwatshtdwn	ctGSMSi.sctwatshtdwn
#define ctsync_dosfls	ctGSMSi.sctsync_dosfls
#define ctsync_logfil	ctGSMSi.sctsync_logfil
#define ctsync_regfil	ctGSMSi.sctsync_regfil
#define cthrtimbas	ctGSMSi.scthrtimbas
#define ctchkpnttim	ctGSMSi.sctchkpnttim
#define ctchkpnt	ctGSMSi.sctchkpnt
#define ctchkpntsiz	ctGSMSi.sctchkpntsiz
#define ctcmtdlytry	ctGSMSi.sctcmtdlytry
#define ctcmtdlycnt	ctGSMSi.sctcmtdlycnt
#define ctcmtdlycoh	ctGSMSi.sctcmtdlycoh
#define ctcmtcohmax	ctGSMSi.sctcmtcohmax
#define ctcmtdlyclr	ctGSMSi.sctcmtdlyclr
#define ctcmtlopclr	ctGSMSi.sctcmtlopclr
#define ctcmtdlyfls	ctGSMSi.sctcmtdlyfls
#define ctcmtlopfls	ctGSMSi.sctcmtlopfls
#define ctcmtdlydfr	ctGSMSi.sctcmtdlydfr
#define ctcmtlopmax	ctGSMSi.sctcmtlopmax
#define ctcmtavgdfr	ctGSMSi.sctcmtavgdfr
#define ctcmtmaxdfr	ctGSMSi.sctcmtmaxdfr
#define ctcmtavgadp	ctGSMSi.sctcmtavgadp
#define ctcmtmaxadp	ctGSMSi.sctcmtmaxadp
#define ctcmtdlyfls2	ctGSMSi.sctcmtdlyfls2
#define ctcmtlopfls2	ctGSMSi.sctcmtlopfls2
#define ctcmtdlynot	ctGSMSi.sctcmtdlynot
#define ctchkbufwrt	ctGSMSi.sctchkbufwrt
#define ctchkchewrt	ctGSMSi.sctchkchewrt
#define ctcmtfls	ctGSMSi.sctcmtfls
#define ctbegfls	ctGSMSi.sctbegfls
#define ctidxfls	ctGSMSi.sctidxfls
#define ctupdfls	ctGSMSi.sctupdfls
#define ctdatflschk	ctGSMSi.sctdatflschk
#define ctdatfls	ctGSMSi.sctdatfls
#define ctmldfls	ctGSMSi.sctmldfls
#define ctmldmsec	ctGSMSi.sctmldmsec
#define elapwrktim	ctGSMSi.selapwrktim
#define ctcmtblktim	ctGSMSi.sctcmtblktim
#define ctcmtclrtim	ctGSMSi.sctcmtclrtim
#define ctactfil	ctGSMSi.sctactfil
#define cttotfil	ctGSMSi.scttotfil
#define cttotblk	ctGSMSi.scttotblk
#define ctactfilx	ctGSMSi.sctactfilx
#define cttotfilx	ctGSMSi.scttotfilx
#define cttotblkx	ctGSMSi.scttotblkx
#define ctnusers	ctGSMSi.sctnusers
#define ctnusersx	ctGSMSi.sctnusersx
#define ctloknm		ctGSMSi.sctloknm
#define ctloknmx	ctGSMSi.sctloknmx
#define ct_hbTbuf	ctGSMSi.sct_hbTbuf
#define ct_hbRbuf	ctGSMSi.sct_hbRbuf
#define ct_mxbuf	ctGSMSi.sct_mxbuf
#define ctbufcnt	ctGSMSi.sctbufcnt
#define ctbufhgh	ctGSMSi.sctbufhgh
#define ct_hbTcac	ctGSMSi.sct_hbTcac
#define ct_hbRcac	ctGSMSi.sct_hbRcac
#define ct_dxbuf	ctGSMSi.sct_dxbuf
#define ctdatcnt	ctGSMSi.sctdatcnt
#define ctdathgh	ctGSMSi.sctdathgh
#define cmtblkseq	ctGSMSi.scmtblkseq
#define ct_dxscan	ctGSMSi.sct_dxscan
#define ct_dxscancnt	ctGSMSi.sct_dxscancnt
#define ct_dxscanhgh	ctGSMSi.sct_dxscanhgh
#define ct_dxspllmt	ctGSMSi.sct_dxspllmt
#define ct_dxsplcnt	ctGSMSi.sct_dxsplcnt
#define ct_dxsplhgh	ctGSMSi.sct_dxsplhgh
#define cttrnmax	ctGSMSi.scttrnmax
#define ctcpcnt		ctGSMSi.sctcpcnt
#define ct_numvfil	ctGSMSi.sct_numvfil
#define ct_avlfil	ctGSMSi.sct_avlfil
#define ctactusr	ctGSMSi.sctactusr
#define ctcurusr	ctGSMSi.sctcurusr
#define ctmaxusr	ctGSMSi.sctmaxusr
#define ct_nutcnt	ctGSMSi.sct_nutcnt
#define ct_nupcnt	ctGSMSi.sct_nupcnt
#define ct_dutcnt	ctGSMSi.sct_dutcnt
#define ct_dupcnt	ctGSMSi.sct_dupcnt
#define	ct_wrtcmp	ctGSMSi.sct_wrtcmp
#define	ct_no_cmp	ctGSMSi.sct_no_cmp
#define	ct_tp_cmp	ctGSMSi.sct_tp_cmp
#define	ct_rj_cmp	ctGSMSi.sct_rj_cmp
#define	ct_bytcmp	ctGSMSi.sct_bytcmp
#ifdef ctFeatMAXFILE32
#define ct_mxfil	ctGSMSi.sct_mxfil32
#else
#define ct_mxfil	ctGSMSi.sct_mxfil
#endif
#define ct_ndsec	ctGSMSi.sct_ndsec
#define ctlogfls	ctGSMSi.sctlogfls
#define ctlogtim	ctGSMSi.sctlogtim
#define ctlogcmpfloor	ctGSMSi.sctlogcmpfloor
#define ctlogcmpfactor	ctGSMSi.sctlogcmpfactor
#ifdef ctdbMEMSUM
#define ctSQLmemsum	ctGSMSi.sctSQLmemsum
#define ctDBmemsum	ctGSMSi.sctDBmemsum
#endif
#define ctrepfls	ctGSMSi.sctrepfls
#define ctismaddcnt	ctGSMSi.sctismaddcnt
#define ctismdelcnt	ctGSMSi.sctismdelcnt
#define ctismupdcnt	ctGSMSi.sctismupdcnt
#define ctismredcnt	ctGSMSi.sctismredcnt
#define ctrqtmonint	ctGSMSi.sctrqtmonint
#define ctioblkretry	ctGSMSi.sctioblkretry

#ifdef ctSQLSRVR

EXTERN ctSQLS	ctSQLSi;

#define ctsql_memhgh	ctSQLSi.sctmemhgh
#define ctsql_memsum	ctSQLSi.sctmemsum
#define ctsql_dscrqs	ctSQLSi.sctdscrqs
#define ctsql_dschit	ctSQLSi.sctdschit
#define ctsql_sscrqs	ctSQLSi.sctsscrqs
#define ctsql_sschit	ctSQLSi.sctsschit
#define ctsql_memcnt	ctSQLSi.sctmemcnt
#define ctsql_dsctot	ctSQLSi.sctdsctot
#define ctsql_dschgh	ctSQLSi.sctdschgh
#define ctsql_dscmax	ctSQLSi.sctdscmax
#define ctsql_ssctot	ctSQLSi.sctssctot
#define ctsql_sschgh	ctSQLSi.sctsschgh
#define ctsql_sscmax	ctSQLSi.sctsscmax

#endif /* ctSQLSRVR */


	/* ~ctFeatSNAPSHOT */
#else	/* ~ctFeatSNAPSHOT */
	/* ~ctFeatSNAPSHOT */

#ifdef ctrt_hrtimer
EXTERN LONG8	  cthrtimbas;	/* high resolution ticks per second	*/
#endif

EXTERN UNLONG	  ctdnd_red;	/* delete node thread queue reads	*/
EXTERN UNLONG	  ctdnd_wrt;	/* delete node thread queue writes	*/
EXTERN UNLONG	  ctdnd_rwt;	/* delete node thread queue rewrites	*/
EXTERN UNLONG	  ctdnd_abn;	/* delete node thread queue abandons	*/
EXTERN UNLONG	  ctdnd_rmv;	/* delete node thread queue removals	*/
EXTERN UNLONG	  ctdnd_non;	/* delete node thread queue no action	*/
EXTERN UNLONG	  ctloktry;	/* count of lock attempts	*/
EXTERN UNLONG	  ctlokhlk;	/* subcount of hdr lock attempts*/
EXTERN UNLONG	  ctlokdny;	/* count of locks denied	*/
EXTERN UNLONG	  ctlokfre;	/* count of locks freed		*/
EXTERN UNLONG	  ctlokrel;	/* count of blocks released	*/
EXTERN UNLONG	  ctlokblk;	/* count of locks blocked	*/
EXTERN UNLONG	  ctlokhbk;	/* subcount of header blocks	*/
EXTERN UNLONG	  ctlokdlk;	/* count of dead locks		*/
EXTERN UNLONG	  ctlokkil;	/* count of killed locks (removed
				** from lock wait list)		*/
#ifdef MULTITRD
#ifdef TRANPROC
EXTERN UNLONG	  cttrntim;	/* cumulative transaction time	*/
EXTERN UNLONG	  cttrnmax;	/* maximum transaction time	*/
EXTERN UNLONG	  cttrncnt;	/* cumulative transaction count	*/
#ifndef ctMXLOGS
EXTERN ULONG	  cmtblkseq;	/* commit delay block stats	*/
#endif
#endif
EXTERN LONG	  ctloknm;	/* net locks over unlocks	*/
#endif
#ifdef ctFeatSrvTimer
EXTERN UNLONG	 cttot_call;
EXTERN UNLONG	 cttot_recv;
EXTERN UNLONG	 cttot_work;
EXTERN UNLONG	 cttot_send;
#endif

#ifndef ctNOGLOBALS
#ifdef ctN8
EXTERN LONG8	 ctmemhgh;	/* system memory highwater mark */
EXTERN LONG8	 ctmemsum;	/* current aggregate sum */
#else
EXTERN LONG	 ctmemhgh;	/* system memory highwater mark */
EXTERN LONG	 ctmemsum;	/* current aggregate sum */
#endif
EXTERN ULONG	 ct_dbrqs;	/* data buffer requests			*/
EXTERN ULONG	 ct_dbhit;	/* data buffer hits			*/
EXTERN ULONG	 ct_ibrqs;	/* index buffer requests		*/
EXTERN ULONG	 ct_ibhit;	/* index buffer hits			*/
EXTERN ULONG	 ct_rdops;	/* number of read operations		*/
EXTERN ULONG	 ct_rdbyt;	/* bytes read				*/
EXTERN ULONG	 ct_wrops;	/* number of write operations		*/
EXTERN ULONG	 ct_wrbyt;	/* bytes written			*/
EXTERN ULONG	 ct_rcops;	/* number of comm read operations	*/
EXTERN ULONG	 ct_rcbyt;	/* comm bytes read			*/
EXTERN ULONG	 ct_wcops;	/* number of comm write operations	*/
EXTERN ULONG	 ct_wcbyt;	/* comm bytes written			*/

#ifndef ctMXLOGS
EXTERN ULONG	 ctwlgops;	/* number of log write operations	*/
EXTERN ULONG	 ctwlgbyt;	/* bytes written to log file		*/
EXTERN ULONG	 ctrlgops;	/* number of log read operations	*/
EXTERN ULONG	 ctrlgbyt;	/* bytes read from log file		*/
EXTERN ULONG	 ctxlgops;	/* number of log extension operations	*/
EXTERN ULONG	 ctxlgbyt;	/* log file extension bytes		*/
EXTERN ULONG	 ct_trbeg;	/* # transaction begins			*/
EXTERN ULONG	 ct_trend;	/* # transaction ends			*/
EXTERN ULONG	 ct_trabt;	/* # transaction aborts			*/
EXTERN ULONG	 ct_trfls;	/* # transaction log flush writes	*/
EXTERN ULONG	 ctsync_logfil; /* transaction log sync calls		*/
#endif /* ~ctMXLOGS */
EXTERN ULONG	 ct_trsav;	/* # transaction savepoints		*/
EXTERN ULONG	 ct_trrst;	/* # transaction restores		*/

EXTERN LONG	 ctwatshtdwn;	/* wait on shut down in seconds		*/
EXTERN ULONG	 ctsync_dosfls; /* DOSFLUSH sync calls			*/
EXTERN ULONG	 ctsync_regfil; /* c-tree file sync calls		*/

EXTERN LONG	 ctactfil;
EXTERN LONG	 cttotfil;
EXTERN LONG	 cttotblk;
EXTERN LONG	 ctactfilx;
EXTERN LONG	 cttotfilx;
EXTERN LONG	 cttotblkx;
EXTERN LONG	 ctnusers;	/* number of users			*/
EXTERN LONG	 ctnusersx;	/* max number of users			*/
EXTERN LONG	 ctloknmx;	/* max net locks over unlocks		*/
EXTERN UINT  ct_hbTbuf;		/* index hash bin threshold: read lock	**
				** expressed as percent			*/
EXTERN ULONG ct_hbRbuf;		/* index hash bin stat reset limit	**
				** expressed in number of hash bin	**
				** searches				*/
EXTERN UINT  ct_mxbuf;		/* available buffers specified in intree*/
EXTERN UINT  ctbufcnt;		/* buffers in use			*/
EXTERN UINT  ctbufhgh;		/* max buffers in use			*/
EXTERN UINT  ct_hbTcac;		/*  data hash bin threshold: read lock	**
				** expressed as percent			*/
EXTERN ULONG ct_hbRcac;		/*  data hash bin stat reset limit	**
				** expressed in number of hash bin	**
				** searches				*/
EXTERN UINT  ct_dxbuf;		/* availble data file buffers 		*/
EXTERN UINT  ctdatcnt;		/* cache pages in use			*/
EXTERN UINT  ctdathgh;		/* max cache pages in use		*/
EXTERN UINT  ct_dxscan;		/* avail   data file scan    cache pages*/
EXTERN UINT  ct_dxscancnt;	/* actual  data file scan    cache pages*/
EXTERN UINT  ct_dxscanhgh;	/* maximum data file scan    cache pages*/
EXTERN UINT  ct_dxspllmt;	/* avail   data file special cache pages*/
EXTERN UINT  ct_dxsplcnt;	/* actual  data file special cache pages*/
EXTERN UINT  ct_dxsplhgh;	/* maximum data file special cache pages*/
EXTERN NINT  ct_numvfil;	/* number of virtual files open		*/
EXTERN NINT  ct_avlfil;		/* available file control block counter */
EXTERN SYSNO ct_mxfil;		/* maximum files specified in intree. 	*/
EXTERN COUNT ct_ndsec;		/* # of sectors per node specified in intree */
#endif /* ~ctNOGLOBALS */

EXTERN NINT	  ctactusr;	/* number of threads active in forground */
EXTERN NINT	  ctcurusr;	/* number of threads active in total	 */
EXTERN NINT	  ctmaxusr;	/* MaxNbr of threads active in total	 */
#ifdef ctBEHAV_BLM
EXTERN LONG ct_nutcnt;
EXTERN LONG ct_nupcnt;
EXTERN LONG ct_dutcnt;
EXTERN LONG ct_dupcnt;
#endif

#endif /* ~ctFeatSNAPSHOT */

#ifdef __cplusplus
}
#endif

#ifdef ctFeatEXIT_CALLBACK
EXTERN ctexitfnc_t	ctexitfnc;
#endif /* ctFeatEXIT_CALLBACK */

#define ctmrklst	idxstate->sctmrklst
#define ct_dupkey	idxstate->sct_dupkey
#define spkey		idxstate->sspkey
#define ct_elm		idxstate->sct_elm
#define ct_tky		idxstate->sct_tky
#define ct_tkp		idxstate->sct_tkp
#define ct_sfxctp	idxstate->sct_sfxctp
#define ct_lnode1	idxstate->sct_lnode1
#define ct_fnode1	idxstate->sct_fnode1
#define ct_nwnod1	idxstate->sct_nwnod1
#define btlev		idxstate->sbtlev
#define ct_lnode2	idxstate->sct_lnode2
#define ct_fnode2	idxstate->sct_fnode2
#define ct_nwnod2	idxstate->sct_nwnod2
#define ct_npath1	idxstate->sct_npath1
#define ct_npath2	idxstate->sct_npath2
#define ct_nelem	idxstate->sct_nelem
#define ct_tight	idxstate->sct_tight
#define ct_melem	idxstate->sct_melem

#ifdef ctNOGLOBALS
typedef CTGVAR USERVAR;
#define acquireIdxOpState() getUserIdxOpState(ctWNGV)
#define releaseIdxOpState(x) relUserIdxOpState(x,ctWNGV)
#define GET_IDXSTATE_LOCAL(x) (x->idxstate)
#define GET_IDXSTATE_CACHE() GET_IDXSTATE_LOCAL(ctWNGV)
/* special direct access to cached member. No recursion check  */
#define GET_IDXSTATE_MEMBER(mem) (GET_IDXSTATE_CACHE().s##mem)
/* reference for some CTGVAR var->mem.   */
#define GET_USERVAR_MEMBER(var,mem) ((var)->s##mem)
/* reference for some CTGVAR var->mem.   */
#define GET_GVAR_MEMBER(var,mem) ((var)->s##mem)

#elif defined(MULTITRD)
typedef CTGV USERVAR;
#define acquireIdxOpState() getUserIdxOpState(lctgv)
#define releaseIdxOpState(x) relUserIdxOpState(x,lctgv)
#define GET_IDXSTATE_LOCAL(x) (x->idxstate)
#define GET_IDXSTATE_CACHE() GET_IDXSTATE_LOCAL(lctgv)
/* special direct access to cached member. No recursion check  */
#define GET_IDXSTATE_MEMBER(mem) (GET_IDXSTATE_CACHE().s##mem)
/* reference for some CTGV var->mem */
#define GET_USERVAR_MEMBER(var,mem) ((var)->s##mem)
/* reference for ctGSMSi members */
#define GET_GVAR_MEMBER(var,mem) (mem)

#else
typedef void USERVAR;
#define acquireIdxOpState() getUserIdxOpState(NULL)
#define releaseIdxOpState(x) relUserIdxOpState(x,NULL)
#define GET_IDXSTATE_CACHE() (ct_idxstate)
#define GET_IDXSTATE_LOCAL(x) (ct_idxstate)
/* special direct access to cached member. No recursion check  */
#define GET_IDXSTATE_MEMBER(mem) (mem)
/* reference of global value mem */
#define GET_USERVAR_MEMBER(var,mem) (mem)
/* reference of global value mem */
#define GET_GVAR_MEMBER(var,mem) (mem)
#endif

#include "ctfunp.h"

#ifdef ctFeatINTERNAL_FILE_CONTROL
EXTERN volatile AULONG delnodstt;	/* delete node thread state */
EXTERN volatile AULONG rspacestt;	/* space reclm thread state */
#ifdef ctFeatKEEPOPEN
EXTERN volatile AULONG kepopnstt;	/* KEEPOPEN close thread state */
#endif
#ifdef ctFeatPRICACHE
EXTERN volatile AULONG cprimestt[MXU2];	/* cache prime thread state */
#endif
#ifdef ctFeatDFRIDX
EXTERN volatile AULONG dfridxstt[MXU2];	/* deferred indexing thread state */
#endif
/*
** Maximum time in seconds to wait for internal threads to close a file.
**   Set to -1 to disable the file control feature.
**   Set to zero to have no time limit.
**   Set to a positive value to specify a time limit.
*/
EXTERN NINT maxfilewaitsecs;

#define TRDSTTnormal	0	/* normal operation of internal thread  */
#define TRDSTTmstclose	1	/* signal internal thread to close file */
#define TRDSTTdidclose	2	/* internal thread has closed file	*/
#endif

#ifdef ctFeatMAXACTCONN
EXTERN volatile AULONG ctcuractconn; /* current number of active connections */
EXTERN volatile AULONG cthghactconn; /* high water number of active connections */
#ifdef ctFeatSRVRpower
EXTERN volatile AULONG cthghactdly; /* high water active connection delay */
#ifdef ctFeatATOMICop64
EXTERN volatile AULONG8 cttotactdly; /* total number of active connection delays */
EXTERN volatile AULONG8 ctsumactdly; /* sum of active connection delay times */
#else
EXTERN ULONG8 cttotactdly; /* total number of active connection delays */
EXTERN ULONG8 ctsumactdly; /* sum of active connection delay times */
#endif
#endif
#endif

#ifdef ctFeatMINIDXBUFsem
EXTERN ctSEMAP	ctgncsema;	/* semaphore used to control ctgetnod81() concurrency */
EXTERN NINT	ctgncsema_max;	/* max threads in ctgetnod81() at one time */
#ifdef ctFeatMINIDXBUFdbg
EXTERN NINT	ctgncsema_ownr;	/* last thread that acquired the gncsema */
#endif
#endif

#ifdef ctFeatMINIDXBUFdbg
EXTERN LONG	ctlrubufcur;	/* current # of threads in lrubuf81() */
EXTERN LONG	ctlrubufhgh;	/* highest # of threads in lrubuf81() */
#endif

#ifdef ctDBGkeepopen

#ifndef ctFeatATOMICop
#error ctDBGkeepopen requires atomic operation support
#endif

/*
** State variables file file open/close diagnostic logging.
*/
EXTERN	pFILE	kofp;		/* Debug log file pointer. */
EXTERN	AULONG	uopnctr[MXU2];	/* Current file open/close call sequence number
				** for each connection. */
EXTERN	pTEXT	uopnfnc[MXU2];	/* Current file open/close function name for
				** each connection. */
EXTERN	volatile
	AULONG	opnctr;		/* Current serverwide file open/close call
				** sequence number. */
#endif

#ifdef ctFeatV11SERVERdefaults
/* These variables indicate if the specified configuration option is using
** its default value. */
EXTERN NINT	checkpoint_flush_default;	/* CHECKPOINT_FLUSH	   */
EXTERN NINT	checkpoint_interval_default;	/* CHECKPOINT_INTERVAL	   */
EXTERN NINT	commit_delay_default;		/* COMMIT_DELAY		   */
EXTERN NINT	ctstatus_size_default;		/* CTSTATUS_SIZE	   */
EXTERN NINT	dat_memory_default;		/* DAT_MEMORY		   */
EXTERN NINT	idx_memory_default;		/* IDX_MEMORY		   */
EXTERN NINT	log_space_default;		/* LOG_SPACE		   */
EXTERN NINT	log_template_default;		/* LOG_TEMPLATE		   */
EXTERN NINT	nontran_data_flush_sec_default;	/* NONTRAN_DATA_FLUSH_SEC  */
EXTERN NINT	nontran_index_flush_sec_default;/* NONTRAN_INDEX_FLUSH_SEC */
EXTERN NINT	sort_memory_default;		/* SORT_MEMORY		   */
EXTERN NINT	tran_data_flush_sec_default;	/* TRAN_DATA_FLUSH_SEC	   */
EXTERN NINT	tran_index_flush_sec_default;	/* TRAN_INDEX_FLUSH_SEC	   */
#endif /* ctFeatV11SERVERdefaults */
#ifdef ctFeatREADONLY_SRVR
EXTERN NINT	ctsrvr_readonly;	/* indicates server in redonly mode */
#endif
#ifdef ctFeatUNCSEG_KEYCOMPRESS
EXTERN NINT	uncseg_keycompress;	/* Automatically enable key compression
					when creating an index that uses a
					Unicode key segment mode. */
#endif
#ifdef ctFeatFILESYScompressUNCSEG
EXTERN NINT	fscompress_uncseg;	/* Automatically enable file system
					level compression when creating an index
					that uses a Unicode key segment mode. */
#endif
#ifdef ctFeatSHMEM_MAX_SPINNERS
EXTERN NINT	ctshmmaxspinners;	/* Maximum number of shared memory
					connections that are allowed to spin
					at one time. */
#endif
#ifdef ctFeatRECOVERY_CHECK_DUPFID
EXTERN NINT	ctrcvchkdupfid;		/* During automatic recovery, check for
					different files that are using the same
					file ID. */
#endif
#ifdef ctFeatCHECK_SYSTEM_FILEID
EXTERN NINT	ctchksysfid;		/* When opening a file, check if the
					file's system file ID has changed. If
					so, reassign its c-tree file ID. */
#endif
#ifdef ctSRVR
EXTERN TEXT	ctuniproc;		/* This system has only one CPU core. */
#endif
#ifdef ctFeatOPTIMIZE_FILE_OPEN
EXTERN NINT	ctfilopnopt;		/* Enable optimizations to file open
					operations. */
#endif
#ifdef ctFeatLEAF_NODE_READ_LOCK
EXTERN NINT	ctLeafNodeReadLock;	/* Acquire read lock on leaf node during
					a key retrieval call. */
#else
#define ctLeafNodeReadLock NO		/* The option to acquire read locks on
					leaf nodes during key retrieval is off
					at compile time. */
#endif
#ifdef ctFeatOPEN_FILES_ALERT
EXTERN NINT	ctOpenFilesAlertThreshold; /* Call the open files alert function
					when the number of open logical files
					exceeds this threshold. */
EXTERN NINT	ctOpenFilesAlertHigh;	/* If non-zero, the threshold has been
					reached and this variable holds the
					high-water mark. If the number of open
					files drops below the threshold, we set
					this value back to zero. */
#endif
#ifdef ctBEHAV_PATH_SUPPRESS_IFIL
EXTERN NINT	ctSuppressPathInIFIL;	/* Enable improved storage of paths in
					the IFIL resource. */
#endif
#ifdef ctFeatPREIMAGE_SWAP
EXTERN ULONG8	ctMaxPreimageData;	/* Maximum amount of preimage data
					allowed in memory before swapping
					to disk. */
EXTERN ULONG8	ctMaxPreimageSwap;	/* Maximum allowed size of preimage swap
					file. */
#endif
#ifdef ctFeatSYSTEM_TIMER_RESOLUTION
EXTERN UINT	ctSystemTimerResolution; /* requested system timer resolution in milliseconds */
EXTERN TEXT	ctRequestedSystemTimerResolution; /* non-zero if system timer resolution value was specified in config file */
#endif

#ifdef ctFeatMEMTRACKmballc
#define mballc(n,s) mballcx(n,s,NO)
#define mbfree(p) mbfreex(p,NO)
#endif

#ifdef ctFeatDMPSEMArwlock

/*----------------------------------------------------------------------------
   ctpdmpsema is a reader/writer lock:
----------------------------------------------------------------------------*/
/* Is the specified task ID holding ctpdmpsema? */
#define ctDSMisownr(own)	(ctdmpsemastt(own) != DMPSEMA_NOLOCK)

/* Acquire ctpdmpsema for the specified access mode (blocking call). */
#ifdef ctDBGSEMCNT
#define ctDSMrqs(ps,mode,own,loc)	{ctrwlrqs(ps,mode,sOWNR,loc); ctdmpsemastt(own) = mode;}
#else
#define ctDSMrqs(ps,mode,own,loc)	{ctrwlrqs(ps,mode,sOWNR); ctdmpsemastt(own) = mode;}
#endif

/* Acquire ctpdmpsema for the specified access mode (non-blocking call). */
#ifdef ctDBGSEMCNT
#define ctDSMtry(ps,mode,own,loc)	(!ctrwltry(ps,mode,sOWNR,loc) ? (ctdmpsemastt(own) = mode,0) : 1)
#else
#define ctDSMtry(ps,mode,own,loc)	(!ctrwltry(ps,mode,sOWNR) ? (ctdmpsemastt(own) = mode,0) : 1)
#endif

/* Release ctpdmpsema. */
#define ctDSMclr(ps,own)	{ctrwlclr(ps,RWCA(ctdmpsemastt(own),own)); ctdmpsemastt(own) = DMPSEMA_NOLOCK;}

/* dmpsemastt value that indicates that the connection is not holding dmpsema: */
#define DMPSEMA_NOLOCK	-1

#else

/*----------------------------------------------------------------------------
   ctpdmpsema is a mutex:
----------------------------------------------------------------------------*/
/* Is the specified task ID holding ctpdmpsema? */
#define ctDSMisownr(own)	(ctpdmpsema->ownr == own)

/* Acquire ctpdmpsema (blocking call). */
#ifdef ctDBGSEMCNT
#define ctDSMrqs(ps,mode,own,loc)	ctsemrqs(ps,WAIT,sOWNR,loc)
#else
#define ctDSMrqs(ps,mode,own,loc)	ctsemrqs(ps,WAIT,sOWNR)
#endif

/* Acquire ctpdmpsema (non-blocking call). */
#ifdef ctDBGSEMCNT
#define ctDSMtry(ps,mode,own,loc)	ctsemrqs(ps,NOWAIT,sOWNR,loc)
#else
#define ctDSMtry(ps,mode,own,loc)	ctsemrqs(ps,NOWAIT,sOWNR)
#endif

/* Release ctpdmpsema. */
#define ctDSMclr(ps,own)	ctsemclr(ps,own)

#endif

#ifdef ctFeatREPLICAT_SYNC_SRVR
EXTERN pSRFHSH	ct_srfhash; /* sync repl file agent hash table */
EXTERN UINT	ct_srfnbins; /* sync repl file agent hash bin count */
EXTERN SEMAmut	ct_srfmtx; /* sync repl file agent hash table mutex */
#endif

#if defined(ctFeatRCVOPNopt) && defined(MULTITRD)
EXTERN pRCVOPNLSTHSH ct_rcvopnhshOrig; /* auto recovery hash table for original filename */
#ifdef ctFeatRECOV_PATHEQUIV
EXTERN pRCVOPNLSTHSH ct_rcvopnhshFull; /* auto recovery hash table for full filename */
#endif
EXTERN UINT ct_rcvopnhshBins; /* number of hash bins for auto recovery filename hash table */
#endif

#ifdef ctFeatAWS
EXTERN ctAWSF  ctAWSfnc; /* AWS functions */
#endif
#ifdef ctFeatAWS_KEY_STORE
EXTERN ctSUAWS ctsAWS; /* SUBSYSTEM EXTERNAL_KEY_STORE AWS */
#endif
#ifdef ctFeatMASTERKEYLIB
EXTERN pTEXT pMasterKeyLib; /*name of the library where to load the custom master key prompt*/
#endif
#ifdef ctSQL_SERVER_LOG_SIZE
EXTERN NINT	sql_server_log_size; /* size limit on sql_server.log file */
#endif
#ifdef ctBEHAV_LOG_FILE_ID_CHANGE
EXTERN NINT	log_file_id_change; /* special log entry when file id is reassigned */
EXTERN NINT	log_file_id_change_set; /* YES= value set by app or config; HYS= after c-tree init so can't be changed */
#endif
#ifdef ctBEHAV_RECOVERY_RENAME_CHECK_FILE_ID
EXTERN TEXT	recovery_rename_check_file_id; /* recovery checks file id of renamed file; and fails if undo rename fails */
#endif
#ifdef ctBEHAV_FILE_CLOSE_FLUSH
EXTERN TEXT	file_close_flush; /* flush updated cache pages for file before closing it */
#endif

#ifdef CTPERM /* this block contains code for internal use only */

/* file list action function pointer */
typedef NINT (*pFILELIST_ACTION_FUNCTION)(pTEXT filnam,pLONG pvalue,pLONG pmember,pNINT pscale,NINT action);

/* file list action function pointer list */
EXTERN pFILELIST_ACTION_FUNCTION filelistAction[NUMBER_OF_FILE_LISTS];

EXTERN TEXT	dbengine_initialized; /* non-zero indicates that the database engine has been initialized */

#ifdef ctSRVR
#ifdef ctFeatCHECK_FILENAME_VALIDITY
EXTERN TEXT	ctCheckFileNameValidity; /* check for valid filename on create and open */
#endif
#ifdef ctFeatREPLICAT_SYNC_SRVR
EXTERN NINT	ctSyncCommitTimeout; /* sync commit timeout in seconds (0=no timeout) */
#endif
#ifdef ctFeatREPLICAT_SYNC2_SRVR
EXTERN SERVER_ROLE ctServerRole; /* server's role */
#endif
#ifdef ctFeatREPLAGENT_FILE_FILTER
EXTERN REPLAGENT_FILE_FILTER_LIST replAgentFileFilterList; /* list of replication agent file filters */
EXTERN ctRWLOCK replAgentFileFilterListRWL; /* replication agent file filter list reader/writer lock */
#endif
#endif /* ctSRVR */

#endif /* CTPERM - end of block containing code for internal use only */

#endif /* ctGVARH */

/* end of ctgvar.h  */
