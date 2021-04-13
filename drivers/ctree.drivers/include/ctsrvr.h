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


/*^***********************************/
#ifdef ctPortUSE_W32DATA_SEG
#pragma data_seg ("RAYS_CTSRVR_DATASEG")
#endif
/*~***********************************/

				/* ctTCread modes...			*/
#define ctTCmsg2	1	/* connect secondary handshake		*/
#define ctTCntio	2	/* regular read				*/
#define ctTCackn	3	/* regular write			*/
#define ctTCconn	4	/* client connect & first message	*/
#define ctTCdisc	5	/* client disconnects			*/
#define ctTCbegn	6	/* startup trap comm log		*/
#define ctTCfnsh	7	/* end log				*/

#define FCSRVR_CFG	"FCSRVR_CFG"
#define FCSRVR_SET	"FCSRVR_SET"
/*duplicated in ctinit.c*/
#define FCSRVR_LIC	"FCSRVR_LIC" 

#ifdef ctCTSRVR_C

#ifndef ctUSRLMTMSG
#define ctUSRLMTMSG	26
#endif

NINT rdycnt =(NINT)0;

#ifdef ctFeatSERVER_IS_UP_SEMA
       SEMAblk
	    ctFcServerIsUp   ={0};
#endif
#ifdef ctFeatSERVER_IS_DOWN_SEMA
       SEMAblk
	    ctFcServerIsDown ={0};
#endif

       SEMAblk
	    ctmainwait ={0};
	pTEXT ctadmmir =(pTEXT)0;
	NINT	srvcfgflg =(NINT)0;
	NINT	srvcfglin =(NINT)0;
	pTEXT	srvcfgfnm = NULL;
	NINT	srvsetflg =(NINT)0;
#ifdef ctFeatCFGsubdir
	pTEXT	cfgdir = "config";
#endif
	pTEXT	srvcfg	 = "ctsrvr.cfg";
	pTEXT	srvset	 = "ctsrvr.set";
	pTEXT	srvlic = NULL; /* server license filename set by ctSetLicenseFile() call */
	pTEXT	locdir = NULL; /* LOCAL_DIRECTORY set by ctSetLocalDirectory() call */
static LONG	ctsrvdly  = 10000L;	/* default 10 sec */

#ifndef ctPortMAC_MSCX /* Microsoft VC++ Mac XCross compiler */
#ifndef ctPortWIN32
#ifndef __MWERKS__
#ifndef ctPortHPUX11
long int atol();
#endif
#endif
#endif
#endif

#ifdef ctPortNLMold
unsigned char __ctype[2]; /* For Netware v3.x and v4.x */
#endif

		/*
		** server version:	2 heterogeneous
		**			3 auto curp/lock
		**			4 DELFIL client cleanup
		**			5 extended user validation info
		**			6 ctDEFERBEG support
		**			7 ATODEP possible (ctBEHAV_ATODEP)
		**			8 using new FC_USER structure
		**			9 enhanced ADMIN security
		**		       10 DAR disabled flg
		**		       11 server-side record image conversion
		*/

#define CTSVVRcurrent	CTSVVRrec_conv

#ifdef ctMULTIBYTEname

#ifdef ctHUGEFILE

#ifdef ctFeatCOMM_SUMCHK
COUNT	cti_svvr = (CTSVVRcurrent | ctsrvALTFILDEF | ctsrvHUGEFILE | ctsrvSUMCHK | ctsrvMB_FILNAM);
#else
COUNT	cti_svvr = (CTSVVRcurrent | ctsrvALTFILDEF | ctsrvHUGEFILE | ctsrvMB_FILNAM);
#endif
#else  /* ~ctHUGEFILE */
COUNT	cti_svvr = (CTSVVRcurrent | ctsrvALTFILDEF | ctsrvMB_FILNAM);
#endif /* ~ctHUGEFILE */

#else  /* ~ctMULTIBYTEname */

#ifdef ctHUGEFILE
#ifdef ctFeatCOMM_SUMCHK
COUNT	cti_svvr = (CTSVVRcurrent | ctsrvALTFILDEF | ctsrvHUGEFILE | ctsrvSUMCHK);
#else
COUNT	cti_svvr = (CTSVVRcurrent | ctsrvALTFILDEF | ctsrvHUGEFILE);
#endif

#else  /* ~ctHUGEFILE */

COUNT	cti_svvr = CTSVVRcurrent;

#endif /* ~ctHUGEFILE */

#endif /* ~ctMULTIBYTEname */


NINT 	cttflgLogon = (NINT)0;
ULONG	ctmusers =(ULONG)0;
ULONG	ctxusers =(NINT)0;
NINT	ctsqldebug =(NINT)0;
pTEXT	ctsqlfile =(pTEXT)0;
pTEXT	cticuloc =(pTEXT)0;
LONG	ct_sesout =(LONG)0;
LONG	naptim =(LONG)0;
LONG	tctmemch =(LONG)0;
LONG	ct_ssdkflg =(LONG)0;
LONG	ct_perfflg =(LONG)0;
LONG	ct_consoleflg =(LONG)0;
#ifdef ctFeatSYSLOG
LONG	ct_syslogflg =(LONG)0;
ULONG	syslogRPbitmap = 0;
LONG	syslogRPerr = 0;
ULONG	syslogRPtime = 0;
LONG	syslogRPlognum = 0;
ULONG	syslogRPlogpos = 0;
syslogRP syslogRPlog;
#endif
LONG	ct_sqloflg =(LONG)0;			/* SQL_OPTION */
LONG	ct_sqlofl2 =(LONG)0;			/* SQL_OPTION (2)*/
LONG	ct_sqldflg =(LONG)0;			/* SQL_DEBUG */
LONG	ct_icuoflg =(LONG)0;
LONG	ct_ksggflg[ctKSEG_TYPE_LIMIT] ={(LONG)0};
LONG	ct_ksgsflg[ctKSEG_TYPE_LIMIT] ={(LONG)0};
NINT	ctksgsiz[ctKSEG_TYPE_LIMIT] ={(NINT)0};
NINT	ctksgcur =(NINT)0;
NINT	ctksgdeferrok =(NINT)0;
NINT	ct_diaginttot =(NINT)0;
NINT	ct_diagintnum =(NINT)0;
NINT	ct_diagstrtot =(NINT)0;
NINT	ct_diagstrnum =(NINT)0;
NINT	ct_ddtot =(NINT)0;
#ifdef ctFeatDYNAMIC_DUMP
NINT	ct_ddnum =(NINT)0;
#endif
pLONG	ct_diagint =(pLONG)0;
ppTEXT	ct_diagstr =(ppTEXT)0;
ppTEXT	ct_ddscript =(ppTEXT)0;
ULONG	ctlgonlmt =(ULONG)0;
ULONG	ctlgontim =(ULONG)0;
ULONG	ctlgonmust =(ULONG)0;
ULONG	ctbroadcastport =(ULONG)0;
pTEXT	ctbroadcastdata =(pTEXT)0;
LONG	ctbroadcastinterval =(LONG)0;
#define DIAG_INCR	12

#ifdef ctSYNC_DELAY
LONG	ct_syncdelay =(LONG)0;
#endif
NINT	ctsemmsl =(NINT)0;
NINT	tasker_pc =(NINT)0;
NINT	tasker_sp =(NINT)0;
NINT	tasker_np =(NINT)0;
NINT	tasker_loop =(NINT)0;
NINT	rqst_delay =(NINT)0;
NINT	rqst_delta =(NINT)0;
NINT	ctlog9074 =(NINT)0;
ULONG	ctset_users;
NINT	ctset_files;

NINT ctpf_stat =(NINT)0;
static LONG pf_beg =(LONG)0;
static LONG pf_end =(LONG)0;
static LONG pf_cum =(LONG)0;
static LONG pf_frq[CTI_MXFN + 1] ={(LONG)0};

/*^*******************/
#ifdef ctDIAG_FNC_MON
	/* The ctDIAG_FNCMON option activate logics which will hold the last 	*/
	/* ctDIAG_FNC_MON (defaults to 10) functions number called by each user */
	/* This allows, as an example, the ctcatend or Exception handler to dump*/
	/* the last function request by each user. 				*/
CTDIAGFNC ctdiagfncmon[ctMAXUSERS][ctDIAG_FNC_MON];
NINT	  ctdiagfncidx[ctMAXUSERS] ={(NINT)0};
ULONG	  ctdiagfnccnt[CTI_MXFN + 2] ={(ULONG)0}; /* plus terminators */

#ifdef PROTOTYPE
extern NINT ctSHowDiagFncMon(NINT);
#else
extern NINT ctSHowDiagFncMon();
#endif

#endif /* ctDIAG_FNC_MON */
/*~*******************/


#ifdef ctPFNAMES
LONG FM_cnt = 0L;

#include "ctpfnm.h"
#endif /* ctPFNAMES */

/*
** ctASYNC Type Names
*/
pTEXT	ctas_names[] = {
	"-unknown-",
	"FLUSH",
	"-unlnown-"
};

UCOUNT ctTCspcl[ctTCfnsh + 1] = {
		0,		/* unused				*/
		0,		/* ctTCmsg2				*/
		0,		/* ctTCntio				*/
		ctTC_ACKN,	/* ctTCackn				*/
		ctTC_CONN,	/* ctTCconn				*/
		ctTC_DISC,	/* ctTCdisc				*/
		ctTC_BEGN,	/* ctTCbegn				*/
		ctTC_FNSH	/* ctTCfnsh				*/
	};

#else  /* ~ctCTSRVR_C */

extern NINT	rdycnt;
#ifdef ctFeatSERVER_IS_UP_SEMA
extern SEMAblk  ctFcServerIsUp;
#endif
#ifdef ctFeatSERVER_IS_DOWN_SEMA
extern SEMAblk  ctFcServerIsDown;
#endif
extern SEMAblk	ctmainwait;
extern pTEXT	ctadmmir;
extern NINT	srvcfgflg;
extern NINT	srvcfglin;
extern pTEXT	srvcfgfnm;
extern NINT	srvsetflg;
#ifdef ctFeatCFGsubdir
extern pTEXT	cfgdir;
#endif
extern pTEXT	srvcfg;
extern pTEXT	srvset;
extern pTEXT	srvlic;
extern pTEXT	locdir;
extern COUNT	cti_svvr;
extern NINT 	cttflgLogon;
extern ULONG	ctmusers;
extern ULONG	ctxusers;
extern NINT	ctsqldebug;
extern pTEXT	ctsqlfile;
extern pTEXT	cticuloc;
extern LONG	ct_sesout;
extern LONG	naptim;
extern LONG	tctmemch;
extern LONG	ct_ssdkflg;
extern LONG	ct_perfflg;
extern LONG	ct_consoleflg;
#ifdef ctFeatSYSLOG
extern LONG	ct_syslogflg;
extern ULONG	syslogRPbitmap;
extern LONG	syslogRPerr;
extern ULONG	syslogRPtime;
extern LONG	syslogRPlognum;
extern ULONG	syslogRPlogpos;
extern syslogRP syslogRPlog;
#endif
extern LONG	ct_sqloflg;			/* SQL_OPTION */
extern LONG	ct_sqlofl2;			/* SQL_OPTION (2)*/
extern LONG	ct_sqldflg;			/* SQL_DEBUG */
extern LONG	ct_icuoflg;
extern LONG	ct_ksggflg[ctKSEG_TYPE_LIMIT];
extern LONG	ct_ksgsflg[ctKSEG_TYPE_LIMIT];
extern NINT	ctksgsiz[ctKSEG_TYPE_LIMIT];
extern NINT	ctksgcur;
extern NINT	ctksgdeferrok;
extern NINT	ct_diaginttot;
extern NINT	ct_diagintnum;
extern NINT	ct_diagstrtot;
extern NINT	ct_diagstrnum;
extern NINT	ct_ddtot;
#ifdef ctFeatDYNAMIC_DUMP
extern NINT	ct_ddnum;
#endif
extern pLONG	ct_diagint;
extern ppTEXT	ct_diagstr;
extern ppTEXT	ct_ddscript;
extern ULONG	ctlgonlmt;
extern ULONG	ctlgontim;
extern ULONG	ctlgonmust;
extern ULONG	ctbroadcastport;
extern pTEXT	ctbroadcastdata;
extern LONG	ctbroadcastinterval;
#define DIAG_INCR	12

#ifdef ctSYNC_DELAY
extern LONG	ct_syncdelay;
#endif
extern NINT	ctsemmsl;
extern NINT	tasker_pc;
extern NINT	tasker_sp;
extern NINT	tasker_np;
extern NINT	tasker_loop;
extern NINT	rqst_delay;
extern NINT	rqst_delta;
extern NINT	ctlog9074;
extern ULONG	ctset_users;
extern NINT	ctset_files;

extern UCOUNT ctTCspcl[ctTCfnsh + 1];

#endif /* ~ctCTSRVR_C */

#ifdef PROTOTYPE
extern  VOID    setcfgsub(VOID);
extern  COUNT 	dyndmp(pVOID bufptr,VRLEN bufsiz);
	NINT  	ctntio(COUNT ,pTEXT ,pVAB ,pLQMSG );
LOCAL 	NINT 	nu_msg(pTEXT ,NINT );
#else
extern  VOID    setcfgsub();
extern  COUNT 	dyndmp();
	NINT 	ctntio();
LOCAL 	NINT 	nu_msg();
#endif

extern ULONG actkey[];
extern CTQUEUEI  ctqglobal[];
#ifndef ctFeatSRVR_STRUCT
extern LONG  nodedtime;
extern COUNT ct_mxu1;
#endif
#ifndef ctFeatSNAPSHOT
extern LONG  ct_cmtdly;
extern ULONG ct_cmtscl;
extern ULONG ct_cmtbas;
#endif

#ifdef TRANPROC
extern LONG ct_trndlt;
extern LONG ct_cpdlt;
#ifndef ctMXLOGS
extern LONG ct_logprg;
#endif
#endif
#ifdef MTDEBUG
extern LONG tmpWAIT;
extern int bomb;
#endif

extern ctCONV COUNT (ctDECL *ctfptr[])();
extern ctCONV LONG  (ctDECL *ctlptr[])();
extern ctCONV VRLEN (ctDECL *ctvptr[])();
extern ctCONV pTEXT (ctDECL *cttptr[])();

#ifdef PROTOTYPE
extern 	VOID 	logonNamedPipe(UNLONG);
extern 	pTEXT 	GetPipeName(VOID);
extern 	ULONG 	WriteErrorCode(UCOUNT, pLQMSG, NINT);
extern 	NINT 	NewUser(pTEXT);
extern 	COUNT 	doserver(pLQMSG, pLQMSG2);
extern 	VOID 	NewLogon(UNLONG);
extern	NINT	ctsrltyp(VOID );
extern	NINT	cthlpmsg(NINT rc,pCTINIT1 cfg);
extern  UINT    isspcsrv(UINT mode);
extern  UINT    isacesrv(VOID);
extern  NINT    showconnlimits(VOID);
#ifdef ctPortWIN32
extern 	NINT	ctGetOSVersion(VOID);
extern 	NINT	ctWINexit();
extern	VOID	setctDEVKEY(NINT);
extern	NINT	chkctSERVICE(VOID);
#endif

#ifdef ctPortMAC
extern 	NINT	ctrt_MACmonitor(pTEXT format, ...);
extern	VOID	exitMac(NINT status);
#endif

extern NINT ctTCread(NINT cmds,NINT type,pTEXT buf,NINT sOWNR,NINT errc,ULONG bytes,UTEXT flavor);
extern NINT ctTCinit(VOID );
extern NINT ictSetLocalDirectory(pCTINIT1 pc,pTEXT localdir);

#else

extern 	VOID 	logonNamedPipe();
extern 	pTEXT 	GetPipeName();
extern 	ULONG 	WriteErrorCode();
extern 	NINT 	NewUser();
extern 	COUNT 	doserver();
extern 	VOID 	NewLogon();
extern	NINT	ctsrltyp();
extern	NINT	cthlpmsg();
extern  UINT    isspcsrv();
extern  UINT    isacesrv();
extern  NINT    showconnlimits();

extern NINT ctTCread();
extern NINT ctTCinit();

#endif

#ifdef ctPortWIN32
#include "ctsrvc.h"
#endif

/*^***********************************/
#ifdef ctPortUSE_W32DATA_SEG
#pragma data_seg()
#pragma comment(linker,"/SECTION:RAYS_CTSRVR_DATASEG,RWS")
#endif
/*~***********************************/

/* end ctsrvr.h */
