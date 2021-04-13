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

/*^***********************************/
#ifdef ctPortUSE_W32DATA_SEG
#pragma data_seg ("RAYS_CTGVAR2_DATASEG")
#endif
#undef  EXTERN
#define EXTERN /* */
/*~***********************************/

#ifdef ctPortVINES
#ifdef RUNTCBTABLE
#define ctTASKER_H	"tasker.h"
#include ctTASKER_H
#endif
#endif

#ifdef MTDEBUG
EXTERN int bomb = 0;
#endif
#ifdef MTRCVR
EXTERN int ebomb = 0;
#endif

#include "ctrkey.h"

#include "ctstrc.h"
#ifdef CTBOUND
#include "ctbond.h"
#else
#include "ctcomm.h"
#endif /* CTBOUND */

/*
** optional instance handle types, prototypes and arguments
*/

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

#ifdef inExists
#define inType		, inTName
#define inHan		, ct_inName
#define pinHan		, inTName ct_inName
#define linHan		inTName ct_inName;
#else
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
#ifdef PROTOTYPE
#define pctLFNdef
typedef ctCONV ctLFN	(ctDECL	 *pctLFN)(COUNT, pVOID, pVOID);
typedef ctCONV ctLFN	(ctDECL	 *pctLFN2)(COUNT, pVOID);
typedef COUNT		 (*plcnFN)(NINT, COUNT, pVOID ,pVRLEN thType);
#else
typedef ctCONV ctLFN	(ctDECL	 *pctLFN)();
typedef ctCONV ctLFN	(ctDECL	 *pctLFN2)();
typedef COUNT		 (*plcnFN)();
#endif

#ifdef ctDBGSEMCNT
#define ctDBGSEMMOD	60
#define ctDBGSEMCAL	100
EXTERN	ULONG	ctsemcnt[ctDBGSEMMOD][ctDBGSEMCAL] = {0L,0L};
#ifdef ctDBGSEMBLK
EXTERN	ULONG	ctsemblk[ctDBGSEMMOD][ctDBGSEMCAL] = {0L,0L};
#endif
#endif /* ctDBGSEMCNT */

#ifdef TRANPROC
#include "cttran.h"
#endif

#ifdef ctCAMO
#define ctCAMSYSLEN	128
EXTERN pCAMFNC	ctglocamo = (pCAMFNC)0;
EXTERN pCAMINT	ctintcamo = (pCAMINT)0;
EXTERN ULONG	ctcamblk = (ULONG)0;
EXTERN NINT	ctcamsln =(NINT)0;
EXTERN NINT	ctcamlog =(NINT)0;
EXTERN NINT	ctcamadmn =(NINT)0;
EXTERN TEXT	ctcamsky[ctCAMSYSLEN] = { (TEXT)0 };
#endif

typedef struct {
#ifdef RTREE
	RKEY	s1usrkey;
	RDAT	s1usrdat;
#endif
	COUNT	s1ct_dtmap;
	COUNT	s1ct_rvmap;
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
EXTERN NINT	ctgv_max =(NINT)0;
EXTERN LONG	ctgv_mode =(LONG)0;
#endif

/****************************************/
#ifdef ctThrds
#ifndef ctNOGLOBALS
typedef struct ctgvars
{
   struct ctgvars ctMEM
	       *pinstance;	/* instance link			*/
 TEXT		instname[IDZ];	/* name of this instance block	*/

} CTGVAR, ctMEM * pCTGVAR, ctMEM * ctMEM * ppCTGVAR;
/* #define ctWNGV	((pCTGVAR)ctThrdGet()) */
#endif
#endif
/****************************************/

#ifdef ctNOGLOBALS

#ifdef ctLOCLIB
#define CTBOUNDvar
#define UNBOUNDvar
#ifdef PROTOTYPE
EXTERN pCOUNT (*ctlfseggetp)(COUNT , COUNT ,ppCOUNT );
EXTERN VOID   (*ctlfsegputp)(COUNT ,COUNT ,COUNT ,COUNT ,COUNT );
EXTERN COUNT  (*ctgetseginfop)(COUNT ,COUNT ,COUNT );
#else
EXTERN pCOUNT (*ctlfseggetp)();
EXTERN VOID   (*ctlfsegputp)();
EXTERN COUNT  (*ctgetseginfop)();
#endif
#endif

#ifdef CTBOUND
#ifndef CTBOUNDvar
#define CTBOUNDvar
#endif
#else /* CTBOUND */
#ifndef UNBOUNDvar
#define UNBOUNDvar
#endif
#endif /* CTBOUND */

#define NUMHGHBINS	64

typedef struct ctgvars
{
   pCEPFNC	ctcepfnc;	/* ctree single entry point func ptr 	*/
   struct ctgvars ctMEM
	       *pinstance;	/* instance link			*/
   pVOID	psysvar;	/* pointer to system-wide  variables	*/
   pVOID	pusrvar;	/* pointer to user-private variables	*/
   pVOID	pctcalbks;	/* pointer to function callbacks	*/
   pVOID	sctcidxStk;	/* conditional index stack 		*/
#ifdef ctHUGEFILE
   pREVDEL	srevdel_ptr;	/* reversible delete file name list	*/
   pNUMRECHGH	snumhgh_ptr;	/* numrec high water mark list		*/
#else
   pVOID	srevdel_ptr;	/* reversible delete file name list	*/
   pVOID	snumhgh_ptr;	/* numrec high water mark list		*/
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
#endif
   LONG		scthghwrd;
   LONG		sctops;		/* set operation state bit mask		*/
   LONG		sctstate;	/* internal state bit mask		*/
   VRLEN	sctxvlen;	/* vlen combined op max buffer length	*/
   VRLEN	ssql_len;
   UINT		sct_trnfilsz;	/* size of ct_trnfil */
   UINT		sctdfrcls;	/* defer close count */
   NINT		ctusraflg;	/* attach flag */
   NINT		sct_dftot;
   NINT		sct_dfnum;
   NINT		sctcidxStkPtr;
   NINT		sctcidxCurCmd;
#ifdef ctFeatUDF_EXPR
   pVOID	sudflist;
   NINT		sisexpreval;
#endif
   NINT		srevdel_tot;
   NINT		srevdel_cur;
   NINT		snumhgh_tot;
   NINT		snumhgh_cur;
   NINT		sdedlst_tot;
   NINT		sdedlst_cur;
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
   COUNT	suerr_cod;	/* user error cod */
   COUNT	ssysiocod;	/* system error cod */
   COUNT	sisam_err;
   COUNT	sisam_fil;
   COUNT	ssql_status1;
   COUNT	ssql_status2;
   COUNT	scndxerr;
   COUNT	sct_mxfil;	/* maximum files specified in intree. 	*/
   COUNT	sctusrprf;	/* user profile word */
#ifdef ISAM_VARS
#ifdef RTREE
   COUNT	ssrtknm,ssrtdat,stmpdat;
#endif
#endif
   TEXT		instname[IDZ];	/* name of this instance block	*/
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
#ifdef CTBOUNDvar
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
   pTREBUF	 sct_btree;	/* ptr to beg of b-tree buffers		*/
   pDATBUF	 sct_dbufr;	/* ptr to beg of data file buffers	*/
   pCTFILE	 sct_key;	/* ptr to beg of ct_key file structures	*/
   pCTFILE	 sct_dat;	/* ptr to beg of data file structures	*/
   pCTFILE	 sct_vat;	/* ptr to beg of var data file struc	*/
   pLOKS	 sct_locks[LOKHBINS];
   pDFDEF	 sct_dfdef;
   pLOKS	 sct_ltail[LOKHBINS];
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
   ULONG sct_disklmt;	/* disk full threshold			*/
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
   ULONG sct_trbeg;	/* # transaction begins			*/
   ULONG sct_trend;	/* # transaction ends			*/
   ULONG sct_trabt;	/* # transaction aborts			*/
   ULONG sct_trsav;	/* # transaction savepoints		*/
   ULONG sct_trrst;	/* # transaction restores		*/
   ULONG sct_ribs;
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
   NINT	 sksgcurs;	/* key seg list controls		*/
   NINT	 sksgtots;
   pKSEGLST sksglsts;
   UINT	 srucesx;
#ifdef DBG749x
   UINT  sctlstfrq;
#endif
   UINT  sct_tmpseq;	/* temporary file sequence number	*/
   UINT	 sct_lhbins;
   UINT  sctconbins;	/* context bins				*/
   NINT	 sct_dq;	/* shrink task logical Q handle		*/
   NINT	 sct_cq; 	/* checkpoint task logical Q handle	*/
   UINT  snsplit;	/* node splits				*/
   UINT	 sekirtsx;
   UINT	 semitx;
   NINT	 scthghflx;	/* highest allocated FCB under ctFLEXFILE */
   NINT	 sctfnz;	/* superfile member max name size	*/
   NINT  sctmiroff;	/* if YES, turn off all mirroring	*/
   NINT  sctosIOlok;	/* if YES, need OS lock to force cache	*/
   UINT	 stimulx;
   COUNT sctconid;	/* last assigned context id		*/
   pULONG    spULI;
#ifdef TRANPROC
   pREBLST   sctrebhed;
   pREBLST   sctcmphed;
   pREBLST   sctmirhed;
   pREBLST   sctiblhed;
   ppSHADLST sct_ubit;
#ifdef DBGhash
   pLONG     sdbg_shsh_u;
#endif
   pTEXT sctmrklst;
   pTEXT sct_usrsp;
   pSHADLST sct_usrsl;
   pCOALST   sct_coalst;
   pTEXT sctlgbf;	/* transaction log buffer ptr */
   ppTEXT    sctlogmemanc;
   ppSHADLST sctlstshd;	/* linked list tail for pre-image list */
   ppSHADLST sctlstsav;	/* last save point pointer */
   ppCOMLST  scttrnanc; /* vulnerable tran hash list anchor */
   pCTFILE sctLnum;
   pCTFILE sctUnum;
   pCTFILE sctSnum;
   CTFILE sctLfil;	/* log file header */
   CTFILE sctUfil;	/* log file header */
   CTFILE sctSfil[2];	/* start file headers */
   LONG  strnwrn;	/* transaction # overflow warning flag	*/
   LONG  sfilwrn;	/* file ID overflow warning flag	*/
   LONG	 sprv_logser;	/* previous checkpoint log#	*/
   LONG	 sprv_chkpos;	/* previous checkpoint pos	*/
   LONG	 sprv_prvpos;	/* previous checkpoint back link*/
   LONG	 sctlogchklmt;
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
   LONG	 sct_lstlog;	/* previous checkpoint log# */
   LONG	 sct_lstpos;	/* previous checkpoint log position */
   LONG	 sctfwdlog;	/* log for starting TRANFWD (ctrdmp) */
   LONG	 sctfwdpos;	/* position for starting TRANFWD (ctrdmp) */
   LONG	 sctfwdpps;	/* prev pos for starting TRANFWD (ctrdmp) */
   LONG	 sct_usrtr[MXU2];/* active transaction # for user or zero */
#ifdef ctFeat6BT
   LONG	 sct_usrtr2[MXU2];
   LONG  sct_usrix2[MXU2];
#endif
   LONG	 sct_usrtl[MXU2];/* log file sequence number for BEGTRAN */
   LONG  sct_usrix[MXU2];/* log file index op number */
   LONG  sct_trnhghmrk;	/* threshold to warn about tran high-water mark */
   VRLEN sct_lbfsiz;	/* log buffer size */
   VRLEN sct_usrsz;
   UINT	 sct_shbins;
   UINT	 sct_shbyts;
   NINT	 sct_tryprvchk;	/* try previous checkpoint */
   NINT  sctsuplog;	/* suppress log flush on begin and end tran */
   NINT  sctfstr;
   NINT	 sctfwdned;
   NINT	 sct_chktrd;
   NINT	 sct_chkflg;	/* checkpoint in progress flag */
   NINT	 sct_logkep;	/* archive log count */
   NINT  sctskpfil;	/* skip missing files during recovery */
   NINT	 sctskpmir;	/* skip missing mirrors during recovery */
   NINT  sctbadmir;	/* skip missing or bad log mirrors during startup */
   NINT  sctfixlog;	/* non-zero means log size cannot increase */
   NINT  sctpdmp;	/* preimage dynamic dump flag */
   NINT  sctsflg;	/* ct_strip flag */
   NINT  sctbflg;	/* BAKMOD flag */
   NINT  sctdflg;	/* dynamic dump flag */
   NINT  sct_actrns;	/* # active transactions */
   NINT  sct_usrsi;
   NINT  sct_usrsv;
   NINT  sct_rstflg;	/* TRANRST() flag */
   NINT	 sctlogmem;
   NINT	 sctlogmemmax;
   NINT	 sctlogdet;
   NINT	 sctskpclnfil;
   NINT  sct_coalcr;
   NINT	 sct_coaltt;
   NINT	 sct_coalcs;
   LONG  sct_usrty[MXU2];/* ctSHADOW / ctLOGFIL transaction type */
   COUNT sctshdlfil;	/* shadow swap file # */
   COUNT sct_lgn;	/* current file# in log */
   COUNT sct_lerflg;	/* ctwrtlog error flag */
   TEXT	 sct_chkpt[MXU2];/* check point flag */
#endif /* TRANPROC */
#ifdef ctNogloSize
   pVOID   sctrebhed;
   pVOID   sctcmphed;
   pVOID   sctmirhed;
   pVOID   sctiblhed;
   ppVOID sct_ubit;
#ifdef DBGhash
   pLONG  sdbg_shsh_u;
#endif
   pVOID sctmrklst;
   pVOID sct_usrsp;
   pVOID sct_usrsl;
   pVOID sct_coalst;
   pVOID sctlgbf;	/* transaction log buffer ptr */
   ppVOID    sctlogmemanc;
   ppVOID sctlstshd;	/* linked list tail for pre-image list */
   ppVOID sctlstsav;	/* last save point pointer */
   ppVOID  scttrnanc; /* vulnerable tran hash list anchor */
   pVOID sctLnum;
   pVOID sctUnum;
   pVOID sctSnum;
   CTFILE sctLfil;	/* log file header */
   CTFILE sctUfil;	/* log file header */
   CTFILE sctSfil[2];	/* start file headers */
   LONG  strnwrn;	/* transaction # overflow warning flag	*/
   LONG  sfilwrn;	/* file ID overflow warning flag	*/
   LONG	 sprv_logser;	/* previous checkpoint log#	*/
   LONG	 sprv_chkpos;	/* previous checkpoint pos	*/
   LONG	 sprv_prvpos;	/* previous checkpoint back link*/
   LONG	 sctlogchklmt;
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
   LONG	 sct_lstlog;	/* previous checkpoint log# */
   LONG	 sct_lstpos;	/* previous checkpoint log position */
   LONG	 sctfwdlog;	/* log for starting TRANFWD (ctrdmp) */
   LONG	 sctfwdpos;	/* position for starting TRANFWD (ctrdmp) */
   LONG	 sctfwdpps;	/* prev pos for starting TRANFWD (ctrdmp) */
   LONG	 sct_usrtr[MXU2];/* active transaction # for user or zero */
#ifdef ctFeat6BT
   LONG	 sct_usrtr2[MXU2];
   LONG  sct_usrix2[MXU2];
#endif
   LONG	 sct_usrtl[MXU2];/* log file sequence number for BEGTRAN */
   LONG  sct_usrix[MXU2];/* log file index op number */
   LONG  sct_trnhghmrk;	/* threshold to warn about tran high-water mark */
   VRLEN sct_lbfsiz;	/* log buffer size */
   VRLEN sct_usrsz;
   UINT	 sct_shbins;
   UINT	 sct_shbyts;
   NINT	 sct_tryprvchk;	/* try previous checkpoint */
   NINT  sctsuplog;	/* suppress log flush on begin and end tran */
   NINT  sctfstr;
   NINT	 sctfwdned;
   NINT	 sct_chktrd;
   NINT	 sct_chkflg;	/* checkpoint in progress flag */
   NINT	 sct_logkep;	/* archive log count */
   NINT  sctskpfil;	/* skip missing files during recovery */
   NINT	 sctskpmir;	/* skip missing mirrors during recovery */
   NINT  sctbadmir;	/* skip missing or bad log mirrors during startup */
   NINT  sctfixlog;	/* non-zero means log size cannot increase */
   NINT  sctpdmp;	/* preimage dynamic dump flag */
   NINT  sctsflg;	/* ct_strip flag */
   NINT  sctbflg;	/* BAKMOD flag */
   NINT  sctdflg;	/* dynamic dump flag */
   NINT  sct_actrns;	/* # active transactions */
   NINT  sct_usrsi;
   NINT  sct_usrsv;
   NINT  sct_rstflg;	/* TRANRST() flag */
   NINT	 sctlogmem;
   NINT	 sctlogmemmax;
   NINT	 sctlogdet;
   NINT	 sctskpclnfil;
   NINT  sct_coalcr;
   NINT	 sct_coaltt;
   NINT	 sct_coalcs;
   LONG  sct_usrty[MXU2];/* ctSHADOW / ctLOGFIL transaction type */
   COUNT sctshdlfil;	/* shadow swap file # */
   COUNT sct_lgn;	/* current file# in log */
   COUNT sct_lerflg;	/* ctwrtlog error flag */
   TEXT	 sct_chkpt[MXU2];/* check point flag */
#endif /* ctNogloSize */
   VRLEN sct_bfsiz;	/* data buffer size			*/
   NINT  sctlogidxfrc;	/* ctLOGIDX override: YES-on HYS-off	*/
   NINT	 sctrdmp_flg;	/* signals dynamic dump recovery	*/
   NINT	 sctmdmp_flg;	/* signals dyn dump recovery had mirrors*/
   NINT	 sctxflg[5];	/* test tran work space flag		*/
   RNDFILE
	 sctxflgfd[5];	/* test tran work space file descriptor	*/
   pLONG sctridx_ptr;	/* dynamic dump index update list ptr	*/
   NINT  sctridx_cur;	/* dynamic dump index update current	*/
   NINT  sctridx_tot;	/* dynamic dump index update total	*/
   NINT	 sctrflg;	/* automatic recovery flag		*/
   NINT  sctnewlogs;	/* starting without logs		*/
   NINT	 sctstrcv_flg;	/* init automatic recovery		*/
   NINT	 sctrbflg;	/* rebuild flag				*/
   NINT	 sctfnstrat;	/* file name conversion startegy	*/
   NINT	 sctmnstrat;	/*    mirror conversion startegy	*/
   NINT	 scttflg;	/* stop server in progress		*/
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
   BHL	 sct_bavl[2];	/* buffer avl list anchors		*/
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
   TEXT	 sctifl_ext[2][EXZ];
				/* default IFIL extensions		*/

   UINT  sct_mxbuf;		/* available buffers specified in intree*/
   UINT  sctbufcnt;		/* buffers in use			*/
   UINT  sctbufhgh;		/* max buffers in use			*/
   UINT  sct_dxbuf;		/* available data file cache pages	*/
   UINT  sctdatcnt;		/* cache pages in use			*/
   UINT  sctdathgh;		/* max cache pages in use		*/
   UINT  sct_dxspllmt;		/* avail   data file special cache pages*/
   UINT  sct_dxsplcnt;		/* actual  data file special cache pages*/
   UINT  sct_dxsplhgh;		/* maximum data file special cache pages*/
   NINT	 sctmpagcache;		/* specify multiple page cache count	*/
   NINT  sct_maxvfil;		/* virtual file limit */
   NINT  sct_numvfil;		/* number of virtual files open		*/
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
   LONG    sct_npath1[MAXLEV];	/* array to trace path down B-tree. Assumes  */
				/* maximum of MAXLEV - 1 levels in B-tree.   */
   LONG    sct_npath2[MAXLEV];
   NINT  sct_nelem[MAXLEV];
   NINT  sct_tight[MAXLEV];
   NINT  sct_melem[MAXLEV];
   NINT  sprvlokf;		/* previous lock state: datno		*/
   NINT  sprvlokt;		/* previous lock state: lock type	*/	
   LONG  sprvlokp;		/* previous lock state: recbyt (lw)	*/	
#ifdef ctHUGEFILE
   LONG  sprvlokh;		/* previous lock state: recbyt (hw)	*/	
#endif
					
   TEXT sct_dupkey[MAXLEN+1];/* for searches of duplicate keys */
   TEXT sspkey[MAXLEN+1];	/* temporary storage for key values during */
				/* node updates 			   */

   NINT  sct_elm;		/* position within B-Tree node	*/
   NINT  sct_tky;		/* result of comparison between target	*/
				/* value and index entry.		*/
				/* ct_tky < 0 => target < index entry	*/
				/*	  = 0 => target = index entry	*/
				/*	  > 0 => target > index entry 	*/
   NINT  sct_tkp;		/* previous value of ct_tky		*/
   NINT  sct_sfxctp;		/* previous value of suffix count	*/
   LONG  sct_lnode1;		/* last node found during walk down tree */
   LONG  sct_fnode1;		/* node found during search/retrieval    */
   LONG  sct_nwnod1;		/* pointer to new node */
   LONG  sct_lnode2;		/* last node found during walk down tree */
   LONG  sct_fnode2;		/* node found during search/retrieval    */
   LONG  sct_nwnod2;		/* pointer to new node */
   LONG  sct_gsrl2;		/* next serial number for data file */
   LONG  sct_gsrl1;		/* next serial number for data file */
   NLONG sct_usernm;		/* system dependent user number */
   NINT  sct_trdflg;		/* thread operation flag */
   NINT  sbtlev;		/* b-tree level counter. used as index of */
				/* ct_npath				  */
   TEXT  sct_buf[CTBUFSIZ];	/* temporary io buffer */

/*
** ISAM global variables from ctisam.h
*/

#ifdef ISAM_VARS
   ppCOUNT	sctskyorg;
   ppCOUNT	sctskymap;
   pCTIS1	sctis1;
   ppCTIS2	sctis2;

   TEXT		sct_fndval[MAXLEN];

   COUNT	sct_nwrcfg;
   COUNT	sct_vfsg;

   COUNT	sct_ismlk;

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
   COUNT   sseqkey;		/* current keyno		*/
#endif
   TEXT    sseqbuf[MAXLEN];	/* holds matching "partial" key */
#ifdef MUSTFRCE
   TEXT	   sseqold[MAXLEN];
#else
#ifdef ctLOCLIB
   TEXT    sseqold[MAXLEN];
#else
#ifdef ctPortREALIA
   TEXT    sseqold[MAXLEN];
#endif /* ctPortREALIA */
#endif
#endif /* MUSTFRCE */
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
#endif /* CTBOUNDvar */
#ifdef UNBOUNDvar
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
#endif /* UNBOUNDvar */
   UINT		salign_override;

#ifdef PROTOTYPE
   NINT		(*intcalbak)(pCTINIT1 );
#else
   NINT		(*intcalbak)();
#endif

#ifdef CTBOUNDvar
   pTEXT	sct_rbuf;
#ifdef ctNogloTran
   pLOGTRNLST	slogtrn_lst;
   ppTEXT	sskplst_anc;
   pTEXT	sctlpathf[10];
   pTEXT	sctlpathm[10];
   pTEXT	slogptr;
   pLONG	sct_rcvlst;
   pLONG	sct_hdrlst;
   pLONG	sct_mbrlst;
   LONG		sct_trndlt;
   LONG		sct_cpdlt;
   LONG		sct_logchn;
   LONG		sct_loglmt;
   LONG		sct_logspc;
   LONG		sct_logrec;
   LONG		sct_logtrg;
   LONG		sct_blgpos;
   LONG		sct_logprg;
   LONG		sct_savprg;
   LONG		slogtrn_seq;
#ifdef ctFeat6BT
   LONG		sct_lowtrn2;
#endif
   ULONG	sct_lowtrn;
   LONG		sct_lnmlog;
   LONG		sct_hnmlog;
   LONG		sct_oldlog;
   LONG		scttopcmt;
   LONG		scttoplog;
   LONG		sctbegcmt;
   LONG		sctbeglog;
   LONG		slogbyt;
   LONG		slowpnt;
   LONG		shghcmt;
   LONG		shghlog;
   VRLEN	slogrem;
   VRLEN	slbfpag;
   NINT		slogtrn_tot;
   NINT		slogtrn_cur;
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
#endif /* ctNogloTran */
   VRLEN	sct_bsz;
   NINT		sctcatcnt;
   COUNT	srerr_cod;
   COUNT	srerr_fil;
   COUNT	sct_fp;
#ifdef RB_CALLBACK
   pRBLCBFNC srblcbfnc; /* ptr to rebuild callback func */
   ULONG     srblcbcnt; /* progress counter for rebuild callback func */
   UCOUNT    srblcbstp; /* progress step for rebuild callback func */
#endif
#endif /* CTBOUNDvar */

#ifdef ctCAMO
   pCAMFNC	sucamfnc;
   pTEXT	sucamptr;
   pTEXT	sct_cam;
   VRLEN	sct_camsiz;
   LONG		sucamlen;
#endif

} CTGVAR, ctMEM * pCTGVAR, ctMEM * ctMEM * ppCTGVAR;

#ifdef ctThrdApp

#ifndef ctCLIENTcore
#define ctWNGV	((pCTGVAR)ctThrdGet())
#endif

EXTERN NINT	ctgv_incr =(NINT)0;
EXTERN ppCTGVAR ctgv_thd =(ppCTGVAR)0;
#ifdef ctThrdRet
EXTERN ppVOID	ctgv_ptr =(ppVOID)0;
#endif

#else  /* ctThrdApp */
#ifdef ctThrdFPG

#ifdef CTPERM
EXTERN pCTGVAR ctWNGV =(pCTGVAR)0;
#else
#ifndef rtThrds
#define ctWNGV	((pCTGVAR)ctThrdGet())
#endif	/* ~rtThrds */
#endif

EXTERN NINT	ctgv_incr =(NINT)0;
EXTERN ppCTGVAR ctgv_thd =(ppCTGVAR)0;
#ifdef ctThrdRet
EXTERN ppVOID	ctgv_ptr =(ppVOID)0;
#endif

#else /* ctThrdFPG */

EXTERN pCTGVAR ctWNGV =(pCTGVAR)0;

#endif /* ctThrdFPG */
#endif /* ctThrdApp */

#define ctumxfil	ct_mxfil
#define cthghfil	ct_mxfil
#define commCmds	ctWNGV->scommCmds
#define commGbls	ctWNGV->scommGbls
#ifdef ctCAMOsdk
#define ctcamver	ctWNGV->sctcamver
#endif
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
#define pULI          ctWNGV->spULI
#define ctconid       ctWNGV->sctconid
#define ctconbins     ctWNGV->sctconbins
#ifdef DBGtree
#define ct_walkh      ctWNGV->sct_walkh
#define ct_walkt      ctWNGV->sct_walkt
#define ctlflg        ctWNGV->sctlflg
#endif /* DBGtree */
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
#define ct_locks      ctWNGV->sct_locks
#ifdef DBGhash
#define dbg_lhsh_u    ctWNGV->sdbg_lhsh_u
#endif
#define ct_dftot      ctWNGV->sct_dftot
#define ct_dfnum      ctWNGV->sct_dfnum
#define ct_dfdef      ctWNGV->sct_dfdef
#define ct_ltail      ctWNGV->sct_ltail
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
#define ct_trbeg      ctWNGV->sct_trbeg
#define ct_trend      ctWNGV->sct_trend
#define ct_trabt      ctWNGV->sct_trabt
#define ct_trsav      ctWNGV->sct_trsav
#define ct_trrst      ctWNGV->sct_trrst
#define ct_ribs       ctWNGV->sct_ribs
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
#define ksgtots	      ctWNGV->sksgtots
#define ksglsts	      ctWNGV->sksglsts
#define ct_dq         ctWNGV->sct_dq
#define ct_cq         ctWNGV->sct_cq
#define ctfnz         ctWNGV->sctfnz
#define rucesx        ctWNGV->srucesx
#define ekirtsx       ctWNGV->sekirtsx
#define timulx        ctWNGV->stimulx
#define emitx         ctWNGV->semitx
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
#define ctmrklst	ctWNGV->sctmrklst
#define ct_usrsp	ctWNGV->sct_usrsp
#define ct_usrsl	ctWNGV->sct_usrsl
#define ct_usrsz	ctWNGV->sct_usrsz
#define ctshdmem	ctWNGV->sctshdmem
#define ctusrsum	ctWNGV->sctusrsum
#define ctusrtot	ctWNGV->sctusrtot
#define ct_usrsi	ctWNGV->sct_usrsi
#define ct_usrsv	ctWNGV->sct_usrsv
#define ct_rstflg	ctWNGV->sct_rstflg
#define ct_shbins       ctWNGV->sct_shbins
#define ct_shbyts       ctWNGV->sct_shbyts
#define ct_trnhghmrk	ctWNGV->sct_trnhghmrk
#define ct_tryprvchk	ctWNGV->sct_tryprvchk
#define ctsuplog	ctWNGV->sctsuplog
#define ctfstr		ctWNGV->sctfstr
#define ctfwdned	ctWNGV->sctfwdned
#define ct_chktrd       ctWNGV->sct_chktrd
#define ctlgbf          ctWNGV->sctlgbf
#define ctlstshd        ctWNGV->sctlstshd
#define ctlstsav        ctWNGV->sctlstsav
#define ctlstshdm(a)    ctWNGV->sctlstshd[a]
#define ctlstsavm(a)    ctWNGV->sctlstsav[a]
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
#define ctfwdlog        ctWNGV->sctfwdlog
#define ctfwdpos        ctWNGV->sctfwdpos
#define ctfwdpps        ctWNGV->sctfwdpps
#define ct_usrtr(a)     ctWNGV->sct_usrtr[a]
#ifdef ctFeat6BT
#define ct_usrtr2(a)    ctWNGV->sct_usrtr2[a]
#define ct_usrix2(a)    ctWNGV->sct_usrix2[a]
#endif
#define ct_usrtl(a)     ctWNGV->sct_usrtl[a]
#define ct_usrix(a)     ctWNGV->sct_usrix[a]
#define ct_lbfsiz       ctWNGV->sct_lbfsiz
#define ct_chkflg       ctWNGV->sct_chkflg
#define ct_logkep       ctWNGV->sct_logkep
#define ctskpfil        ctWNGV->sctskpfil
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
#define ct_bfsiz      ctWNGV->sct_bfsiz
#define ctlogidxfrc   ctWNGV->sctlogidxfrc
#define ctrdmp_flg    ctWNGV->sctrdmp_flg
#define ctmdmp_flg    ctWNGV->sctmdmp_flg
#define ctxflg        ctWNGV->sctxflg
#define ctxflgfd      ctWNGV->sctxflgfd
#define ctridx_ptr    ctWNGV->sctridx_ptr
#define ctridx_cur    ctWNGV->sctridx_cur
#define ctridx_tot    ctWNGV->sctridx_tot
#define ctrflg        ctWNGV->sctrflg
#define ctnewlogs     ctWNGV->sctnewlogs
#define ctstrcv_flg   ctWNGV->sctstrcv_flg
#define ctrbflg       ctWNGV->sctrbflg
#define ctfnstrat     ctWNGV->sctfnstrat
#define ctmnstrat     ctWNGV->sctmnstrat
#define cttflg        ctWNGV->scttflg
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
#define ctifl_ext     ctWNGV->sctifl_ext

#define ct_mxbuf      ctWNGV->sct_mxbuf
#define ctbufcnt      ctWNGV->sctbufcnt
#define ctbufhgh      ctWNGV->sctbufhgh
#define ct_dxbuf      ctWNGV->sct_dxbuf
#define ctdatcnt      ctWNGV->sctdatcnt
#define ctdathgh      ctWNGV->sctdathgh
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
#define ct_npath1     ctWNGV->sct_npath1
#ifdef ctHUGEFILE
#define ct_npath2     ctWNGV->sct_npath2
#endif /* ctHUGEFILE */

#define ct_nelem      ctWNGV->sct_nelem
#define ct_tight      ctWNGV->sct_tight
#define ct_melem      ctWNGV->sct_melem
#define prvlokf       ctWNGV->sprvlokf
#define prvlokt       ctWNGV->sprvlokt
#define prvlokp       ctWNGV->sprvlokp
#define prvlokh       ctWNGV->sprvlokh
					       			
#define ct_dupkey     ctWNGV->sct_dupkey
#define spkey         ctWNGV->sspkey

#define ct_elm        ctWNGV->sct_elm
#define ct_tky        ctWNGV->sct_tky

#define ct_tkp        ctWNGV->sct_tkp
#define ct_sfxctp     ctWNGV->sct_sfxctp
#define ct_lnode1     ctWNGV->sct_lnode1
#define ct_fnode1     ctWNGV->sct_fnode1
#define ct_nwnod1     ctWNGV->sct_nwnod1
#ifdef ctHUGEFILE
#define ct_lnode2     ctWNGV->sct_lnode2
#define ct_fnode2     ctWNGV->sct_fnode2
#define ct_nwnod2     ctWNGV->sct_nwnod2
#define ct_gsrl2      ctWNGV->sct_gsrl2
#endif /* ctHUGEFILE */
#define ct_gsrl1      ctWNGV->sct_gsrl1
#define ct_trdflg     ctWNGV->sct_trdflg
#define btlev         ctWNGV->sbtlev
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
#define ct_savset     ctWNGV->sct_savset

#define seqbuf	      ctWNGV->sseqbuf
#ifdef MUSTFRCE
#define seqold	      ctWNGV->sseqold
#else
#ifdef ctPortREALIA
#define seqold	      ctWNGV->sseqold
#endif /* ctPortREALIA */
#endif
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
#define ct_loglmt	ctWNGV->sct_loglmt
#define ct_logspc	ctWNGV->sct_logspc
#define ct_logrec	ctWNGV->sct_logrec
#define ct_logtrg	ctWNGV->sct_logtrg
#define ct_blgpos	ctWNGV->sct_blgpos
#define ct_logprg	ctWNGV->sct_logprg
#define ct_savprg 	ctWNGV->sct_savprg
#ifdef ctFeat6BT
#define ct_lowtrn2 	ctWNGV->sct_lowtrn2
#endif
#define ct_lowtrn 	ctWNGV->sct_lowtrn
#define logtrn_seq	ctWNGV->slogtrn_seq
#define logtrn_tot	ctWNGV->slogtrn_tot
#define logtrn_cur	ctWNGV->slogtrn_cur
#define logtrn_lst	ctWNGV->slogtrn_lst
#define skplst_anc	ctWNGV->sskplst_anc
#define skplst_tot	ctWNGV->sskplst_tot
#define skplst_cur	ctWNGV->sskplst_cur
#define ct_lnmlog	ctWNGV->sct_lnmlog
#define ct_hnmlog	ctWNGV->sct_hnmlog
#define ct_oldlog	ctWNGV->sct_oldlog
#define ct_logspr	ctWNGV->sct_logspr
#define ct_logblk	ctWNGV->sct_logblk
#define ct_rcvlst	ctWNGV->sct_rcvlst
#define ct_hdrlst	ctWNGV->sct_hdrlst
#define ct_mbrlst	ctWNGV->sct_mbrlst
#define anydelmrk	ctWNGV->sanydelmrk
#define intpthflg	ctWNGV->sintpthflg
#define ctlpathfa	ctWNGV->sctlpathfa
#define ctlpathma	ctWNGV->sctlpathma
#define undflg		ctWNGV->sundflg
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
#define hghcmt	 	ctWNGV->shghcmt
#define hghlog	 	ctWNGV->shghlog
#else
#define tranactv	ctWNGV->stranactv
#define transavp	ctWNGV->stransavp
#endif /* TRANPROC */
#define ctcatcnt	ctWNGV->sctcatcnt
#define ct_bsz		ctWNGV->sct_bsz
#define ct_rbuf		ctWNGV->sct_rbuf
#define rerr_cod	ctWNGV->srerr_cod
#define rerr_fil	ctWNGV->srerr_fil
#define ct_fp		ctWNGV->sct_fp
#else /* CTBOUND */
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
#endif /* CTBOUND */
#define align_override	ctWNGV->salign_override

#ifdef ctCLIENT
#define ctdivs        ctWNGV->sctdivs
#endif
#define ctnusers      ctWNGV->sctnusers
#define ucamfnc	      ctWNGV->sucamfnc
#define ucamptr	      ctWNGV->sucamptr
#define ct_cam        ctWNGV->sct_cam
#define ct_camsiz     ctWNGV->sct_camsiz
#define ucamlen	      ctWNGV->sucamlen
#define nocamocomm    ctWNGV->snocamocomm
#define ctops	      ctWNGV->sctops
#define ctstate	      ctWNGV->sctstate
#define ctxvlen	      ctWNGV->sctxvlen
#define sql_len       ctWNGV->ssql_len
#define ctdfrcls      ctWNGV->sctdfrcls
#define ct_trnfilsz   ctWNGV->sct_trnfilsz
#define cthshift      ctWNGV->scthshift
#define ctmaxparm     ctWNGV->sctmaxparm
#define uerr_cod      ctWNGV->suerr_cod
#define sysiocod      ctWNGV->ssysiocod
#define isam_err      ctWNGV->sisam_err
#define isam_fil      ctWNGV->sisam_fil
#define sql_status1   ctWNGV->ssql_status1
#define sql_status2   ctWNGV->ssql_status2
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
#define revdel_ptr    ctWNGV->srevdel_ptr
#define revdel_tot    ctWNGV->srevdel_tot
#define revdel_cur    ctWNGV->srevdel_cur
#define numhgh_ptr    ctWNGV->snumhgh_ptr
#define numhgh_tot    ctWNGV->snumhgh_tot
#define numhgh_cur    ctWNGV->snumhgh_cur
#endif
#define dedlst_ptr    ctWNGV->sdedlst_ptr
#define dedlst_tot    ctWNGV->sdedlst_tot
#define dedlst_cur    ctWNGV->sdedlst_cur
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
#endif

#ifdef PROTOTYPE

#ifdef __cplusplus
extern "C" {
#endif

/**************************/
#ifdef ctCLIENT
#ifdef ctPortNUMEGA_TR
// MDS change
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

#else /* ~PROTOTYPE */
ctCONV pCTGVAR  ctDECL GetCtreeGV();
ctCONV void     ctDECL SetCtreeGV();
ctCONV pCTGVAR  ctDECL InitCtreeGV();
ctCONV VOID     ctDECL FreeCtreeGV();
#ifdef ctPortWINDOWSMSDOS
ctCONV BOOL     ctDECL ViewCtreeError();
#endif
#endif /* ~PROTOTYPE */


#else /* ~ctNOGLOBALS */

#ifdef CTBOUND
EXTERN pVOID		commCmds[MAXCOMMP] = {(pVOID)0};
#else
EXTERN pCommFuncPtrs	commCmds[MAXCOMMP] = {(pCommFuncPtrs)0};
#endif
EXTERN pVOID		commGbls[MAXCOMMP] = {(pVOID)0};

EXTERN NINT	dedlst_tot =(NINT)0;
EXTERN NINT	dedlst_cur =(NINT)0;
EXTERN pDEDLST	dedlst_ptr =(pDEDLST)0;
EXTERN NINT	ksgcurs =(NINT)0;
EXTERN NINT	ksgtots =(NINT)0;
EXTERN pKSEGLST	ksglsts =(pKSEGLST)0;
EXTERN UINT	align_override =(UINT)0;

#ifdef ctCLIENT
EXTERN pTEXT	ctusrbuf =(pTEXT)0;
EXTERN pLQMSG	ctlqmsg =(pLQMSG)0;
EXTERN pLOCLFILE hlocl =(pLOCLFILE)0;
EXTERN pLOCLAUX  hauxl =(pLOCLAUX)0;
EXTERN pltICON	 cthicon[ctCONBINS] ={(pltICON)0};
EXTERN pVOID	ctcidxStk =(pVOID)0;
EXTERN NINT	cthugflg =(NINT)0;
EXTERN NINT	ctreqsiz =(NINT)0;
EXTERN NINT	ctrspsiz =(NINT)0;
EXTERN NINT	ctinpoff =(NINT)0;
EXTERN NINT	ctoutoff =(NINT)0;
EXTERN VRLEN	ctusrlen =(VRLEN)0;
EXTERN VRLEN	ctusrpos =(VRLEN)0;
EXTERN VRLEN	ctsrvlen =(VRLEN)0;
EXTERN UTEXT	ctsflvr[8] = {(UTEXT)0};
EXTERN TEXT	ctnodnam[IDZ] ={(TEXT)0};
EXTERN NINT	ct_lq =(NINT)0;
EXTERN NINT	ctautotfrm =(NINT)0;
EXTERN NINT	ctmaxparm =(NINT)0;
EXTERN NINT	ctmaxdatkey =(NINT)0;
EXTERN NINT	ctisam_flg =(NINT)0;
EXTERN NINT	ct_autopos_clr =(NINT)0;
EXTERN NINT	ctsrvopt =(NINT)0;
EXTERN NINT	ctspclogon =(NINT)0;
EXTERN COUNT	ctsrvver =(COUNT)0;

EXTERN LONG	 ctnusers =(LONG)0;	/* number of users			*/
EXTERN LONG	 ctdivs =(LONG)0;
EXTERN LONG	 ctops =(LONG)0;		/* set operation state bit mask		*/
EXTERN LONG	 ctstate =(LONG)0;	/* internal state bit mask		*/
EXTERN VRLEN	 ctxvlen =(VRLEN)0;	/* vlen combined op max buffer length	*/
EXTERN VRLEN	 sql_len =(VRLEN)0;
EXTERN NINT	 ctcidxStkPtr =(NINT)0;
EXTERN NINT	 ctcidxCurCmd =(NINT)0;
#ifdef ctFeatUDF_EXPR
EXTERN pVOID udflist =(ppVOID)0;
EXTERN NINT  isexpreval =(NINT)0;
#endif
EXTERN NINT	 cthshift =(NINT)0;	/* huge shift				*/
EXTERN NINT	 ctrunfil =(NINT)0;
EXTERN NINT	 ctrcvfil =(NINT)0;
EXTERN NINT	 ct_adfil =(NINT)0;
EXTERN NINT	 frschgset =(NINT)0;
EXTERN NINT	 curchgset =(NINT)0;
EXTERN NINT	 frschgbat =(NINT)0;
EXTERN NINT	 curchgbat =(NINT)0;
EXTERN COUNT uerr_cod =(COUNT)0;		/* user error cod */
EXTERN COUNT sysiocod =(COUNT)0;		/* system error cod */
EXTERN COUNT isam_err =(COUNT)0;
EXTERN COUNT isam_fil =(COUNT)0;
EXTERN COUNT sql_status1 =(COUNT)0;
EXTERN COUNT sql_status2 =(COUNT)0;
EXTERN COUNT cndxerr =(COUNT)0;		/* conditional index error cod */
EXTERN COUNT ct_mxfil =(COUNT)0;		/* maximum files specified in intree. 	*/
EXTERN COUNT ctusrprf =(COUNT)0;		/* user profile word */
#ifdef RTREE
EXTERN COUNT	srtknm =(COUNT)0;
EXTERN COUNT	srtdat =(COUNT)0;
EXTERN COUNT	tmpdat =(COUNT)0;
#endif
EXTERN UTEXT 			ct_uflvr =(UTEXT)0;
EXTERN UTEXT 			ct_ualgn =(UTEXT)0;
EXTERN UTEXT			ct_upntr =(UTEXT)0;

#else /* ~ctCLIENT */

EXTERN LSTANC	ctlist[NUMCTLIST] ={NULL};

#ifdef MULTITRD

EXTERN ppVOID	ctgv_thd =(ppVOID)0;

#ifdef ctBEHAV_BLM
EXTERN pTREBUF	ctupdnod =(pTREBUF)0;
EXTERN pTREBUF	ctuptnod =(pTREBUF)0;
EXTERN pTREBUF	ctcomnod =(pTREBUF)0;
EXTERN pDATBUF	ctupddat =(pDATBUF)0;
EXTERN pDATBUF	ctuptdat =(pDATBUF)0;
EXTERN pDATBUF	ctcomdat =(pDATBUF)0;
#endif

EXTERN ppNINT	  ct_wf =(ppNINT)0;
EXTERN pNINT	  ct_vf =(pNINT)0;
#ifdef ctCUSTOM
EXTERN ppVOID	  spcustmem =(ppVOID)0;
EXTERN pLONG	  scustops =(pLONG)0;
#endif
#ifdef ctBEHAV_KILL_QUIET
EXTERN SEMAblk	  ctkillquiet = {0};
#define	ctKQuser	-21
#endif
#ifdef DBGhash
EXTERN SEMAmut	  dbg_hsema =(SEMAmut)0;
#endif

#ifdef ctCACHE_MEMORY
EXTERN pSEMA	  ctSsemap[ctSEMS] ={(pSEMA)0};
EXTERN pSEMAmut	  ctXsemap[ctSEMX] ={(pSEMAmut)0};
EXTERN pSEMAtim	  ctTsemap[ctSEMT] ={(pSEMAtim)0};
EXTERN pSEMAblk	  ctBsemap[ctSEMB] ={(pSEMAblk)0};
EXTERN pTEXT	  ctlsemab =(pTEXT)0;
EXTERN pTEXT	  ctSsemab =(pTEXT)0;
EXTERN pTEXT	  ctXsemab =(pTEXT)0;
EXTERN pTEXT	  ctTsemab =(pTEXT)0;
EXTERN pTEXT	  ctBsemab =(pTEXT)0;
EXTERN pTEXT	  ct_blkb =(pTEXT)0;
#else
EXTERN SEMAtim	  ctdnode_sema =(SEMAtim)0;
EXTERN SEMAmut	  ctstrfil_sem =(SEMA)0;
EXTERN SEMA	  ctmemtrk_sem =(SEMA)0;
EXTERN pNINT	  sct_usrsi =(pNINT)0;
#endif

EXTERN UNLONG	  ctdnd_red =(UNLONG)0;	/* delete node thread queue reads	*/
EXTERN UNLONG	  ctdnd_wrt =(UNLONG)0;	/* delete node thread queue writes	*/
EXTERN UNLONG	  ctdnd_rwt =(UNLONG)0;	/* delete node thread queue rewrites	*/
EXTERN UNLONG	  ctdnd_abn =(UNLONG)0;	/* delete node thread queue abandons	*/
EXTERN UNLONG	  ctdnd_rmv =(UNLONG)0;	/* delete node thread queue removals	*/
EXTERN UNLONG	  ctdnd_non =(UNLONG)0;	/* delete node thread queue no action	*/
EXTERN LONG	  ctash =(LONG)0;	/* system-wide async handle		*/
EXTERN LONG	  ctchkidle =(LONG)0;	/* seconds between chkpnt idle test */
EXTERN LONG	  nodedtime =(LONG)0;	/* node delete delay time	    */
EXTERN LONG	  nodertime =(LONG)0;	/* node reuse  delay time	    */
EXTERN UNLONG	  ctloktry =(UNLONG)0;	/* count of lock attempts	*/
EXTERN UNLONG	  ctlokhlk =(UNLONG)0;	/* subcount of hdr lock attempts*/
EXTERN UNLONG	  ctlokdny =(UNLONG)0;	/* count of locks denied	*/
EXTERN UNLONG	  ctlokblk =(UNLONG)0;	/* count of locks blocked	*/
EXTERN UNLONG	  ctlokhbk =(UNLONG)0;	/* subcount of header blocks	*/
EXTERN UNLONG	  ctlokdlk =(UNLONG)0;	/* count of dead locks		*/
EXTERN LONG	  ctlokch =(LONG)0;	/* lock check increment		*/
EXTERN LONG	  ctlokup =(LONG)0;	/* lock ckeck limit		*/
EXTERN LONG	  ctlokdn =(LONG)0;	/* lock check limit		*/
EXTERN LONG	  ctloknm =(LONG)0;	/* net locks over unlocks	*/
EXTERN LONG	  ctloknmx =(LONG)0;	/* max net locks over unlocks	*/
EXTERN NINT	  ctlokfl =(NINT)0;	/* net locks == 0 control flag	*/
EXTERN NINT	  ct_gstnot =(NINT)0;	/* if YES, no guest logons	*/
EXTERN NINT	  ct_blkadm =(NINT)0;	/* YES: must be adm group, HYS adm user */
EXTERN UINT	  ctchktran =(UINT)0;	/* idle chkpnt activity test	*/
EXTERN NINT	  ctmaxdatkey =(NINT)0;
EXTERN NINT	  ctmaxkeyseg =(NINT)0;
EXTERN NINT	  ctmaxusrfil =(NINT)0;
EXTERN NINT	  ctcacheline =(NINT)0;	/* cache-line size for multiCPU optimization */
EXTERN NINT	  ctrunlength =(NINT)0;	/* interval between buffer global mtx release*/
EXTERN NINT	  ctdnodeRunning =(NINT)0;
EXTERN NINT	  ctqchkpRunning =(NINT)0;
EXTERN NINT	  ctsyslgRunning =(NINT)0;
#ifdef ctPortMACOSX_COCOA
EXTERN NINT	  ctqmsgRunning =(NINT)0; /* Message monitor thread still running */
EXTERN NINT	  ctqfncRunning =(NINT)0; /* Function monitor thread still running */
#endif
EXTERN NINT	  ctactusr =(NINT)0;	/* number of threads active in forground */
EXTERN NINT	  ctworktyp[ctWORKsize] ={(NINT)0};
EXTERN NINT	  ct_mq[ctMAX_MONITOR] ={(NINT)0};
EXTERN NINT	  ct_smon[ctMAX_MONITOR] ={(NINT)0};
EXTERN UINT	  ct_trdmon[ctMAX_MONITOR] ={(UINT)0};
EXTERN COUNT	  ctadmfiles =(COUNT)0;

#else /* ~MULTITRD */

#ifdef ctHUGEFILE
EXTERN LONG	  cthghwrd =(LONG)0;
#endif /* ctHUGEFILE */
#ifndef TRANPROC
EXTERN COUNT	  tranactv =(COUNT)0;
EXTERN COUNT	  transavp =(COUNT)0;
#endif
#endif /* ~MULTITRD */

EXTERN CTFILE    ctfmru ={0};
EXTERN pCTFILE   ct_mru =(pCTFILE)0;
EXTERN ppCTFILE  ctfcbhdr =(ppCTFILE)0;
EXTERN pULONG	 pULI =(pULONG)0;
EXTERN pTREBUF	 ct_btree =(pTREBUF)0;	/* ptr to beg of b-tree buffers		*/
EXTERN pDATBUF	 ct_dbufr =(pDATBUF)0;	/* ptr to beg of data file buffers	*/
EXTERN pCTFILE	 ct_key =(pCTFILE)0;	/* ptr to beg of ct_key file structures	*/
EXTERN pCTFILE	 ct_dat =(pCTFILE)0;	/* ptr to beg of data file structures	*/
EXTERN pCTFILE	 ct_vat =(pCTFILE)0;	/* ptr to beg of var data file struc	*/
EXTERN pDFDEF	 ct_dfdef =(pDFDEF)0;
#ifndef ctCACHE_MEMORY
EXTERN pLONG	 sctshdmem =(pLONG)0;	/* shadow memory: excluding cntl structures */
EXTERN pLONG	 sctusrsum =(pLONG)0;	/* mem usage sum */
EXTERN pLONG	 sctusrtot =(pLONG)0;	/* mem usage limit */
#endif
EXTERN pTEXT	 ctsig_rdy =(pTEXT)0;	/* name of exe to launch on server ready*/
EXTERN pTEXT	 ctusrsig_rdy =(pTEXT)0; /* text passed to user defined signal ready function */
EXTERN pTEXT	 ctsig_mir =(pTEXT)0;	/* name of exe to launch on 1st mir trm	*/
EXTERN pTEXT	 ctsig_dwn =(pTEXT)0;	/* name of exe to launch on server down	*/
EXTERN pTEXT	 ctusrsig_dwn =(pTEXT)0; /* text passed to user defined signal down function */

#ifdef ctFeatSrvTimer
EXTERN UNLONG	 cttot_call =(UNLONG)0;
EXTERN UNLONG	 cttot_recv =(UNLONG)0;
EXTERN UNLONG	 cttot_work =(UNLONG)0;
EXTERN UNLONG	 cttot_send =(UNLONG)0;
#endif

EXTERN LONG	 ctclrlop =(LONG)0;
EXTERN LONG	 ctflslop =(LONG)0;
EXTERN LONG	 ctactfil =(LONG)0;
EXTERN LONG	 cttotfil =(LONG)0;
EXTERN LONG	 cttotblk =(LONG)0;
EXTERN LONG	 ctactfilx =(LONG)0;
EXTERN LONG	 cttotfilx =(LONG)0;
EXTERN LONG	 cttotblkx =(LONG)0;
EXTERN LONG	 ctmemlmt =(LONG)0;	/* max ctgetmem request  */
EXTERN LONG	 ctmemtot =(LONG)0;	/* space aggregate limit */
EXTERN LONG	 ctmemsum =(LONG)0;	/* current aggregate sum */
EXTERN LONG	 ctmemusr =(LONG)0;	/* system default user limit */
EXTERN LONG	 ctmemhgh =(LONG)0;	/* system memory highwater mark */
EXTERN LONG	 ctmemup =(LONG)0;	/* MEMORY_MONITOR limit */
EXTERN LONG	 ctmemdn =(LONG)0;	/* MEMORY_MONITOR limit */
EXTERN LONG	 ctmemch =(LONG)0;	/* MEMORY_MONITOR delta */
EXTERN ULONG	 ctmemtrk_up =(ULONG)0;
EXTERN ULONG	 ctmemtrk_dn =(ULONG)0;
EXTERN LONG	 ctmemtrk_ch =(LONG)0;
EXTERN ULONG	 ctmemtrk_net =(ULONG)0;
EXTERN VRLEN	 ct_qblock =(VRLEN)0;	/* SQL record buffer block size		*/
EXTERN VRLEN	 ct_gstmem =(VRLEN)0;	/* guest memory limit			*/
EXTERN LONG	 ct_timout =(LONG)0;	/* inactive tran timeout		*/
EXTERN LONG	 ct_usrmrl =(LONG)0;	/* user memory attribute bits		*/
#ifndef ctFeatL10_serno
extern ULONG	 ctghat[ctGhatSize];
#endif

EXTERN ULONG	 ct_disklmt =(ULONG)0;	/* disk full threshold			*/
EXTERN ULONG	 ct_dbrqs =(ULONG)0;	/* data buffer requests			*/
EXTERN ULONG	 ct_dbhit =(ULONG)0;	/* data buffer hits			*/
EXTERN ULONG	 ct_ibrqs =(ULONG)0;	/* index buffer requests		*/
EXTERN ULONG	 ct_ibhit =(ULONG)0;	/* index buffer hits			*/
EXTERN ULONG	 ct_rdops =(ULONG)0;	/* number of read operations		*/
EXTERN ULONG	 ct_rdbyt =(ULONG)0;	/* bytes read				*/
EXTERN ULONG	 ct_wrops =(ULONG)0;	/* number of write operations		*/
EXTERN ULONG	 ct_wrbyt =(ULONG)0;	/* bytes written			*/
EXTERN ULONG	 ct_rcops =(ULONG)0;	/* number of comm read operations	*/
EXTERN ULONG	 ct_rcbyt =(ULONG)0;	/* comm bytes read			*/
EXTERN ULONG	 ct_wcops =(ULONG)0;	/* number of comm write operations	*/
EXTERN ULONG	 ct_wcbyt =(ULONG)0;	/* comm bytes written			*/
EXTERN ULONG	 ct_trbeg =(ULONG)0;	/* # transaction begins			*/
EXTERN ULONG	 ct_trend =(ULONG)0;	/* # transaction ends			*/
EXTERN ULONG	 ct_trabt =(ULONG)0;	/* # transaction aborts			*/
EXTERN ULONG	 ct_trsav =(ULONG)0;	/* # transaction savepoints		*/
EXTERN ULONG	 ct_trrst =(ULONG)0;	/* # transaction restores		*/
EXTERN ULONG	 ct_ribs =(ULONG)0;
EXTERN LONG	 ct_ii[ctIDLEz] ={(LONG)0};/* idle task Q intervals		*/
#ifdef PROTOTYPE
EXTERN NINT    (*ct_ip[ctIDLEz])(VOID ); /* idle task func pointers	*/
#else
EXTERN NINT    (*ct_ip[ctIDLEz])();
#endif
EXTERN LONG	 ct_abnod =(LONG)0;	/* abort list node count		*/
EXTERN LONG	 ct_cmnod =(LONG)0;	/* pending node tran count		*/
EXTERN LONG	 ct_cmdat =(LONG)0;	/* pending data tran count		*/
EXTERN LONG	 ct_statflg =(LONG)0;	/* CTSTATUS flag			*/
EXTERN LONG	 ct_sysviewT =(LONG)0;	/* SYSVIEW WHAT				*/
EXTERN LONG	 ct_sysviewN =(LONG)0;	/* SYSVIEW WHEN				*/
EXTERN LONG	 ct_langflg =(LONG)0;	/* LANGUAGE flag			*/
#ifdef ctLOG_IDX
EXTERN LONG	 ct_numvi =(LONG)0;	/* vulnerable index update count	*/
#endif
EXTERN LONG	 ctquemon =(LONG)0;	/* node queue monitor threshold	*/
EXTERN LONG	 ctnusers =(LONG)0;	/* number of users			*/
EXTERN LONG	 ctnusersx =(LONG)0;	/* max number of users			*/
#ifdef ctSRVR
EXTERN LONG	 ctsusers =(LONG)0;	/* number of users in forced logoff	*/
#endif
EXTERN LONG	 ctstatus_size =(LONG)0;	/* size limit on CTSTATUS.FCS		*/
EXTERN NINT	 ctisolev =(NINT)0;	/* default isolation level		*/
#ifdef ctFeatCLRCHK
#ifdef MULTITRD
EXTERN NINT	 ctclrchk =(NINT)0;	/* bound server	USERPRF_CLRCHK setting	*/
#endif
#endif
EXTERN NINT	 ctstatus_purge =(NINT)0;/* CTSTATUS.FCS purge indicator		*/
#ifdef DBG749x
EXTERN UINT	 ctlstfrq =(UINT)0;
#endif
EXTERN UINT	 ct_tmpseq =(UINT)0;	/* temporary file sequence number	*/
EXTERN NINT	 ct_dftot =(NINT)0;
EXTERN NINT	 ct_dfnum =(NINT)0;
EXTERN NINT	 ctmiroff =(NINT)0;	/* if YES, turn off all mirroring	*/
EXTERN NINT	 ctosIOlok =(NINT)0;	/* if YES, need OS lock to force cache	*/
EXTERN NINT	 ctdedmon =(NINT)0;	/* deadloack monitor flag		*/
EXTERN NINT	 ctfncmon =(NINT)0;	/* function request monitor		*/
EXTERN NINT	 ctchkmon =(NINT)0;	/* checkpoint monitor flag		*/
EXTERN UINT	 rucesx =(UINT)0;
#ifdef ctSRVR
EXTERN NINT	 ct_fhlimit =(NINT)0;	/* override file handle limits/default	*/
#endif
EXTERN NINT	 cthshift =(NINT)0;	/* huge shift				*/
EXTERN NINT	 ct_dq =(NINT)0;		/* shrink task logical Q handle		*/
EXTERN NINT	 ct_rq =(NINT)0;		/* reclaim deleted space Q handle	*/
EXTERN NINT	 ct_cq =(NINT)0; 	/* checkpoint task logical Q handle	*/
EXTERN NINT	 ct_iq[ctIDLEz] ={(NINT)0};/* idle task Q handles			*/
EXTERN NINT	 ct_id[ctIDLEz] ={(NINT)0};/* idle task thread handles		*/
EXTERN NINT	 ctidle =(NINT)0;	/* YES: at most background activity	*/
EXTERN UINT	 nsplit =(UINT)0;	/* node splits				*/
EXTERN UINT	 ekirtsx =(UINT)0;
EXTERN UINT	 emitx =(UINT)0;
EXTERN NINT	 cthghflx =(NINT)0;	/* highest allocated FCB: ctFLEXFILE	*/
EXTERN NINT	 ctfnz =(NINT)0;		/* superfile member max name size	*/
#ifndef CTBOUND
EXTERN NINT	 ct_lq =(NINT)0;		/* logon logical Q handle		*/
EXTERN NINT	 ct_sq =(NINT)0;		/* event log queue			*/
EXTERN pTEXT	 ct_tmppth =(pTEXT)0;	/* temporary file default server path	*/
EXTERN pFILE	 ctfncfp =(pFILE)0;	/* optional file ptr for func monitor	*/
#endif
#ifdef TRANPROC
EXTERN ppTEXT	 ctlogmemanc =(ppTEXT)0;
EXTERN pREBLST	 ctrebhed =(pREBLST)0;	/* index rebuild list */
EXTERN pREBLST	 ctcmphed =(pREBLST)0;	/* compress rebuild list */
EXTERN pREBLST	 ctmirhed =(pREBLST)0;	/* mirror sync list */
EXTERN pREBLST	 ctiblhed =(pREBLST)0;	/* data (IFIL) rebuild list */
EXTERN LONG	 prv_logser =(LONG)0;	/* previous checkpoint log#		*/
EXTERN LONG	 prv_chkpos =(LONG)0;	/* previous checkpoint pos		*/
EXTERN LONG	 prv_prvpos =(LONG)0;	/* previous checkpoint back link	*/
EXTERN LONG	 ctlogchklmt =(LONG)0;	/* override checkpoint interval		*/
EXTERN LONG	 ct_trnhghmrk =(LONG)0;	/* threshold to warn tran high mark	*/
EXTERN UINT	 ct_shbins =(UINT)0;	/* shadow hash bins			*/
EXTERN UINT	 ct_shbyts =(UINT)0;	/* shadow hash bytes			*/
EXTERN NINT	 ct_tryprvchk =(NINT)0;	/* try previous checkpoint		*/
EXTERN NINT	 ctsuplog =(NINT)0;	/* suppress log flush on begin\end tran */
EXTERN NINT	 ctfstr =(NINT)0;	/* oldest start file #			*/
EXTERN NINT	 ctfwdned =(NINT)0;	/* ctrdmp requires TRANFWD		*/
EXTERN NINT	 ct_chktrd =(NINT)0;	/* thread id of checkpoint thread	*/
#endif
EXTERN UINT	 timulx =(UINT)0;
EXTERN UINT	 ct_lhbins =(UINT)0;	/* lock hash bins			*/
EXTERN UINT	 ctconbins =(UINT)0;	/* context bins				*/
#ifdef MULTITRD
EXTERN NINT	 ctrmsg =(NINT)0;	/* recovery in process message flag	*/
EXTERN NINT	 ct_commp =(NINT)0;	/* # of comm protocols in use		*/
EXTERN NINT	 ct_jobst =(NINT)0;	/* # of job threads  in use		*/
#endif
EXTERN VRLEN	 ct_bfsiz =(VRLEN)0;	/* data buffer size			*/
EXTERN NINT	 ctlogidxfrc =(NINT)0;	/* ctLOGIDX override: YES-on HYS-off	*/
EXTERN NINT	 ctrdmp_flg =(NINT)0;	/* signals dynamic dump recovery	*/
EXTERN NINT	 ctmdmp_flg =(NINT)0;	/* signals dyn dump recovery had mirrors*/
EXTERN NINT	 ctxflg[5] ={(NINT)0};	/* test tran work space flag		*/
EXTERN RNDFILE	 ctxflgfd[5] ={(RNDFILE)0};	/* test tran work space file descriptor	*/
EXTERN pLONG	 ctridx_ptr =(pLONG)0;	/* dynamic dump index update list ptr	*/
EXTERN NINT	 ctridx_cur =(NINT)0;	/* dynamic dump index update current	*/
EXTERN NINT	 ctridx_tot =(NINT)0;	/* dynamic dump index update total	*/
EXTERN NINT	 ctrflg =(NINT)0;	/* automatic recovery flag		*/
EXTERN NINT	 ctnewlogs =(NINT)0;	/* starting without logs		*/
EXTERN NINT	 ctstrcv_flg =(NINT)0;	/* init automatic recovery		*/
EXTERN NINT	 ctlogmem =(NINT)0;	/* preload log files to memory in rcvy	*/
EXTERN NINT	 ctlogmemmax =(NINT)0;	/* max log files to memory in rcvy	*/
EXTERN NINT	 ctlogdet =(NINT)0;	/* output recovery details		*/
EXTERN NINT	 ctskpclnfil =(NINT)0;	/* if on, skip clean files in recovery	*/
EXTERN NINT	 ctfnstrat =(NINT)0;	/* file name conversion startegy	*/
EXTERN NINT	 ctmnstrat =(NINT)0;	/*    mirror conversion startegy	*/
EXTERN NINT	 cttflg =(NINT)0;	/* stop server in progress		*/
#ifdef ctSRVR
EXTERN NINT	 cttloc =(NINT)0;	/* stop server locale (ctcatend: loc)	*/
#endif
EXTERN NINT	 ctapwflg =(NINT)0;	/* Check ADMIN pw flag			*/
EXTERN NINT	 ctfilcre =(NINT)0;	/* flag for create since checkpoint	*/
EXTERN NINT	 ct_hghu1 =(NINT)0;	/* high water mark thread(user) handle	*/
EXTERN COUNT	 ct_mxu1 =(COUNT)0;	/* max users plus origin		*/
EXTERN NINT	 ct_mxu1a =(NINT)0;
EXTERN NINT	 ct_cmnown =(NINT)0;	/* common onwer number (semaphores)	*/
EXTERN UINT	 ct_hshft =(UINT)0;	/* hash shift parameter			*/
EXTERN UINT	 ct_hbins =(UINT)0;	/* hash bins for buffers		*/
EXTERN UINT	 ct_dshft =(UINT)0;	/* datbuf hash shift parm		*/
EXTERN UINT	 ct_dbins =(UINT)0;	/* datbuf hash bins			*/
#ifdef ctLOG_IDX
EXTERN UINT	 ct_tbins =(UINT)0;	/* vulnerable tran# hash bins		*/
#endif
EXTERN BHL	 ct_bavl[2] ={0};	/* buffer avl list anchors		*/
EXTERN ppBHL     ct_bhla[NUMANCHOR] ={(ppBHL)0};
				/* buffer hash list anchors		*/
#ifdef DBGhash
EXTERN pLONG	 dbg_bhl_n =(pLONG)0;
EXTERN pLONG	 dbg_bhl_d =(pLONG)0;
#endif
EXTERN pTEXT	 ctsdname =(pTEXT)0;	/* server directory name		*/
EXTERN pTEXT	 ctsmname =(pTEXT)0;	/* mirror directory name		*/
EXTERN pTEXT	 ctsvname =(pTEXT)0;	/* server name				*/
EXTERN pTEXT	 ctsqname =(pTEXT)0;	/* server SQL name			*/
#ifdef ctPortVINESLOG
EXTERN TEXT	 ctlgname[MAX_NAME] ={(TEXT)0};
				/* server status log name		*/
#endif

#ifdef ctTRAP_COMM
#ifdef MULTITRD
#ifndef CTBOUND
EXTERN ULONG	 ctTCpos =(ULONG)0;	/* TrapComm buffer pos			*/
EXTERN ULONG	 ctTCsiz =(ULONG)0;	/* TrapComm buffer size			*/
EXTERN pFILE	 ctTCfp =(pFILE)0;	/* TrapComm stream file pointer		*/
EXTERN SEMAmut	 ctTCsema ={0};	/* TrapComm mutex			*/
EXTERN pTEXT	 ctTCbuf =(pTEXT)0;	/* TrapComm buffer pointer		*/
#endif
#endif
#endif /* ctTRAP_COMM */

EXTERN pTEXT	 ctscommp[MAXCOMMP] ={(pTEXT)0};
				/* server comm protocol			*/
				/* TrapComm mutex			*/

#ifdef ctFeatJOBMGTSYS 		/* FairCom Job Management System Subsystem */
EXTERN pTEXT	 ctsjobsf[MAXCTJOBS];	/* server ctjobs files		*/
#endif   

EXTERN pTEXT	 ct_del =(pTEXT)0;	/* constant 0xff array			*/
EXTERN UINT	 ct_delsiz =(UINT)0;	/* size of 0xff array			*/
EXTERN NINT	 ct_sqlsupr =(NINT)0;	/* sql superfile flag			*/
EXTERN UINT	 cts_list_m =(UINT)0;	/* list memory block size		*/
EXTERN UINT	 cts_sort_m =(UINT)0;	/* sort memory buffer size		*/
EXTERN UINT	 cts_bufr_m =(UINT)0;	/* bufr memory block size		*/
EXTERN TEXT	 ctifl_ext[2][EXZ] ={(TEXT)0,(TEXT)0};
				/* default IFIL extensions		*/
#ifdef MULTITRD
#ifdef ctBEHAV_freopen
#define ctMAX_freopen	4
EXTERN TEXT	 ctfrename[ctMAX_freopen][IDZ] ={(TEXT)0,(TEXT)0};
EXTERN pFILE	 ctfrefp[ctMAX_freopen] ={(pFILE)0};
EXTERN SEMAmut	 ctfresema[ctMAX_freopen]={0};
#endif /* ctBEHAV_freopen */
EXTERN UTEXT	 ct_sflvr =(UTEXT)0;	/* system flavor			*/
EXTERN UTEXT	 ct_salgn =(UTEXT)0;	/* system alignment			*/
EXTERN UTEXT	 ct_spntr =(UTEXT)0;	/* system pointer size			*/
#endif /* MULTITRD */

EXTERN UINT  ct_mxbuf =(UINT)0;		/* available buffers specified in intree*/
EXTERN UINT  ctbufcnt =(UINT)0;		/* buffers in use			*/
EXTERN UINT  ctbufhgh =(UINT)0;		/* max buffers in use			*/
EXTERN UINT  ct_dxbuf =(UINT)0;		/* availble data file buffers 		*/
EXTERN UINT  ctdatcnt =(UINT)0;		/* cache pages in use			*/
EXTERN UINT  ctdathgh =(UINT)0;		/* max cache pages in use		*/
EXTERN UINT  ct_dxspllmt =(UINT)0;	/* avail   data file special cache pages*/
EXTERN UINT  ct_dxsplcnt =(UINT)0;	/* actual  data file special cache pages*/
EXTERN UINT  ct_dxsplhgh =(UINT)0;	/* maximum data file special cache pages*/
EXTERN NINT  ctmpagcache =(NINT)0;	/* specify multiple page cache count	*/
#ifndef ctGINIT
extern NINT  ct_maxvfil;	/* maximum virtual files opened		*/
#endif
EXTERN NINT  ctrunfil =(NINT)0;
EXTERN NINT  ctrcvfil =(NINT)0;
EXTERN NINT  ct_adfil =(NINT)0;
EXTERN NINT  ct_numvfil =(NINT)0;	/* number of virtual files open		*/
EXTERN NINT  ct_avlfil =(NINT)0;		/* available file control block counter */
EXTERN COUNT ct_mxfil =(COUNT)0;		/* maximum files specified in intree. 	*/
EXTERN COUNT ct_ndsec =(COUNT)0;		/* # of sectors per node specified in intree */
EXTERN UCOUNT ct_ver1 =(UCOUNT)0;/* defines configuration options 128 header */
EXTERN UCOUNT ct_ver2 =(UCOUNT)0;/* defines configuration options XTD header */
EXTERN UCOUNT ct_ver3 =(UCOUNT)0;/* defines configuration options 6BT header */
EXTERN TEXT  ctsupsep =(TEXT)0;

#ifdef MULTITRD
#ifdef ctBEHAV_BLM
EXTERN LONG ct_nutcnt =(LONG)0;
EXTERN LONG ct_nupcnt =(LONG)0;
EXTERN LONG ct_dutcnt =(LONG)0;
EXTERN LONG ct_dupcnt =(LONG)0;
#endif

EXTERN SEMA ct_srvsema ={0};
EXTERN SEMA ct_uhnsema ={0};		/* user handle semaphore */

#ifndef ctCACHE_MEMORY
EXTERN SEMA ct_undsema =(SEMA)0;		/* single tran undo semaphore */
EXTERN SEMA ct_1dmsema =(SEMA)0;		/* enforce only 1 dump at-a-time */
EXTERN SEMA ct_dmpsema =(SEMA)0;		/* dynamic dump semaphore */
EXTERN SEMA ct_ismema =(SEMA)0;		/* ctismem semaphore */
EXTERN SEMA ct_vtsema =(SEMA)0;		/* vtclose semaphore */
EXTERN SEMA ct_nmvsema =(SEMA)0;		/* ct_numvfil sema */
EXTERN SEMA ct_avlsema =(SEMA)0;		/* available file counter */
EXTERN SEMA ct_chksema =(SEMA)0;		/* checkpoint semaphore */
EXTERN SEMA ct_abtsema =(SEMA)0;		/* node abort list semaphore */
EXTERN SEMA    ct_lflsema =(SEMA)0;	/* log file i/o semaphore */
EXTERN SEMAblk ct_lfwsema =(SEMAblk)0;	/* wait for collective log flush */
EXTERN SEMAmut ct_comsema =(SEMAmut)0;	/* index buffer commit list semaphore */
EXTERN SEMAmut ct_dcmsema =(SEMAmut)0;	/*  data  cache commit list semaphore */
EXTERN SEMAmut ct_lftsema =(SEMAmut)0;	/* log high-water flush mark control */
EXTERN SEMAmut tranac_sema =(SEMAmut)0;	/* control count of beg/end tran calls */
EXTERN SEMAmut ct_dbsema =(SEMAmut)0;	/* data cache control sema */
EXTERN SEMAmut ct_gvsema =(SEMAmut)0;	/* ctgv semaphore */
EXTERN SEMAmut ct_logsema =(SEMAmut)0; 	/* log position/buffer semaphore */
EXTERN SEMAmut ct_gnsema =(SEMAmut)0;	/* get node (getnod) semaphore */
#ifdef ctBEHAV_BLM
EXTERN SEMAmut ct_nutmtx =(SEMAmut)0;	/*    tran buffer page update list mutex */
EXTERN SEMAmut ct_nupmtx =(SEMAmut)0;	/* no tran buffer page update list mutex */
EXTERN SEMAmut ct_dutmtx =(SEMAmut)0;	/*    tran cache  page update list mutex */
EXTERN SEMAmut ct_dupmtx =(SEMAmut)0;	/* no tran cache  page update list mutex */
#endif
EXTERN SEMAmut ct_ocsema =(SEMAmut)0;	/* open / create semaphore */
EXTERN SEMAmut ct_llsema =(SEMAmut)0;	/* lock list semaphore */
EXTERN SEMAmut ct_facsema =(SEMAmut)0;	/* file lru access count */
EXTERN SEMAmut ct_utrsema =(SEMAmut)0; 	/* ct_usrtr[] semaphore */
EXTERN SEMAmut ct_memsema =(SEMAmut)0; 	/* memory allocation semaphore */
EXTERN SEMAmut ct_concsema =(SEMAmut)0; 	/* multi-procesor concurrency */
EXTERN SEMAmut	ct_ctlsema =(SEMAmut)0;
EXTERN SEMAmut	ct_pi1sema =(SEMAmut)0;
EXTERN SEMAmut	ct_pi2sema =(SEMAmut)0;
EXTERN SEMAmut	ct_pi4sema =(SEMAmut)0;
EXTERN SEMAmut	ct_pi8sema =(SEMAmut)0;
EXTERN SEMAmut	ct_piwsema =(SEMAmut)0;
EXTERN SEMAmut	ct_pixsema =(SEMAmut)0;
EXTERN SEMAmut	ct_piysema =(SEMAmut)0;
EXTERN SEMAmut	ct_pizsema =(SEMAmut)0;
EXTERN SEMAmut	ct_batsema =(SEMAmut)0;
EXTERN SEMAmut	ct_ilksema =(SEMAmut)0;
#endif /* ~ctCACHE_MEMORY */

EXTERN SEMAmut *ctlsemap[SEMTYP] ={(SEMAmut *)0};
EXTERN COUNT ct_numusr =(COUNT)0;		/* active users */
#endif

#ifdef ctSRVR

#ifndef ctCACHE_MEMORY
EXTERN SEMAmut ct_MPsema =(SEMAmut)0;	/* multi-processor mutex */
#endif

EXTERN pTEXT	pADMINu =(pTEXT)0;
EXTERN pTEXT	pADMINg =(pTEXT)0;
EXTERN pTEXT	pGUESTu =(pTEXT)0;
EXTERN pTEXT	pGUESTg =(pTEXT)0;
EXTERN pTEXT	pADMINw =(pTEXT)0;
EXTERN pTEXT	pADMINk =(pTEXT)0;
EXTERN NINT	ct_sesschg =(NINT)0;
EXTERN NINT	ct_fcrpvuln =(NINT)0;	/* vulnerable to nobTRAN FCRP_ERR's */
EXTERN NINT	ct_loclwarn =(NINT)0;	/* server warning: remote file	    */
#ifdef ctFeatCOMM_IO_BLOCK
EXTERN LONG	ctcomioblk =(LONG)0;	/* Block All Comm I/O */
#endif
#ifdef ctFeatSTARTUP_LOGON_BLOCK
EXTERN LONG	ctsublons =(LONG)0;	/* Start Up Block Logons */
#endif
#ifdef ctFeatNEW_DEAD_CLIENT
EXTERN LONG	ct_deadint =(LONG)0;	/* dead client detection interval */
EXTERN NINT	ct_deadclioff =(NINT)0;	/* new dead client detection disabled for old client */
#endif
EXTERN LONG	ct_prpriority = (LONG)0;/* server process priority */
#ifdef ctSQLSRVR
EXTERN LONG     ct_sqlport = (LONG)0;   /* port for SQL client connections */
#endif
#endif

#ifdef GNSERVER
EXTERN pDEDLOK ctdedlok =(pDEDLOK)0;	/* pointer to deadlock detection array */
#endif

#ifdef MULTITRD

EXTERN pSEMA	ctpundsema =(pSEMA)0;	/* 00 */
EXTERN pSEMA	ctp1dmsema =(pSEMA)0;	/* 01 */
EXTERN pSEMA	ctpdmpsema =(pSEMA)0;	/* 02 */
EXTERN pSEMAmut	ctstrfilpsem =(pSEMA)0;	/* 03 */
EXTERN pSEMA	ctmemtrkpsem =(pSEMA)0;	/* 04 */
EXTERN pSEMA	ctpismema =(pSEMA)0;	/* 05 */
/*
EXTERN pSEMA	available =(pSEMA)0;	   06
*/
EXTERN pSEMA	ctpvtsema =(pSEMA)0;	/* 07 */
EXTERN pSEMA	ctpnmvsema =(pSEMA)0;	/* 08 */
EXTERN pSEMA	ctpavlsema =(pSEMA)0;	/* 09 */
/*
EXTERN pSEMA	available =(pSEMA)0;	   10
*/
EXTERN pSEMA	ctpchksema =(pSEMA)0;	/* 11 */
EXTERN pSEMA	ctpabtsema =(pSEMA)0;	/* 12 */
/*
EXTERN pSEMA	available =(pSEMA)0;	   13
*/
EXTERN pSEMA	ctpuhnsema =(pSEMA)0;	/* 14 */
EXTERN pSEMA    ctplflsema =(pSEMA)0;	/* 15 */

EXTERN pSEMAmut ctpgnsema =(pSEMAmut)0;	/* 00 */
EXTERN pSEMAmut ctpocsema =(pSEMAmut)0;	/* 01 */
EXTERN pSEMAmut ctpllsema =(pSEMAmut)0;	/* 02 */
#ifdef ctFeatVIRTUAL_FILES
EXTERN pSEMAmut ctpfacsema =(pSEMAmut)0;	/* 03 */
#endif
EXTERN pSEMAmut ctputrsema =(pSEMAmut)0;	/* 04 */
EXTERN pSEMAmut	ctpcomsema =(pSEMAmut)0;	/* 05 */
EXTERN pSEMAmut ctpconcsema =(pSEMAmut)0;	/* 06 */
EXTERN pSEMAmut ctpMPsema =(pSEMAmut)0;	/* 07 */
EXTERN pSEMAmut ctpgvsema =(pSEMAmut)0;	/* 08 */
EXTERN pSEMAmut ctplogsema =(pSEMAmut)0;	/* 09 */
EXTERN pSEMAmut	ctpdbsema =(pSEMAmut)0;	/* 10 */
EXTERN pSEMAmut	ctplftsema =(pSEMAmut)0;	/* 11 */
EXTERN pSEMAmut	ptranacsema =(pSEMAmut)0;	/* 12 */
#ifdef ctBEHAV_BLM
EXTERN pSEMAmut ctpnupmtx =(pSEMAmut)0;	/* 13 */
EXTERN pSEMAmut ctpdupmtx =(pSEMAmut)0;	/* 14 */
EXTERN pSEMAmut ctpnutmtx =(pSEMAmut)0;	/* 15 */
EXTERN pSEMAmut ctpdutmtx =(pSEMAmut)0;	/* 16 */
#endif
EXTERN pSEMAmut	ctpdcmsema =(pSEMAmut)0;	/* 17 */

EXTERN pSEMAtim	ctdnodepsema =(pSEMAtim)0;	/* 00 */
EXTERN pSEMAblk	ctplfwsema =(pSEMAblk)0;	/* 00 */

#ifdef ctSTATIC_SEMA
EXTERN SEMA ctsresema[MXU2] ={0};
#endif

typedef struct thrdgv {
	NINT	 slOWNR;	/* self-referencing thread handle (OWNER) */
	NINT	 slCNTR;	/* self-referencing thread instance cntr  */
	NINT	 sisolev;
#ifdef ctCREATE_SEMA
	SEMA	 sresema;	/* reuseable semaphore for temp CTFILE	*/
#endif
	SEMAtim	 sctblktim;
	BATHDR	 batch;
#ifdef ctOldALCBAT
	COUNT	 sbatmax;
	COUNT	 sbatnum;
	pBATHDR	 ssavbat;
#else
	pSAVBAT	 sbatnum;
	ppSAVBAT ssavbat;
#endif
	HSTHDR	 history;
	pHSTLST	 histund;
	pSAVHST	 shstnum;
	ppSAVHST ssavhst;
	pSEGLST	 sseglsthdr;
	pVOID	 sctcidxStk;
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
	LONG  sctops;		/* set operation state bit mask		*/
	LONG  sctstate;		/* internal state bit mask		*/
	VRLEN sctxvlen;		/* vlen combined op max buffer length	*/
	LONG  sabnlog;		/* begtran log for abandoned tran	*/
	LONG  sresrv1;		/* spare members */
	LONG  sresrv2;
	LONG  sresrv3;
	LONG  strntime;		/* last begin tran time */
	NINT  snbrfile;		/* number of files in use */

#ifndef CTBOUND
	pVOID suserlqp;		/* user's request block */
	LONG  sresrv4;		/* spare members */
	LONG  sresrv5;
	LONG  sctops_clr;	/* operation state clear mask		*/
#ifdef ctHUGEFILE
	LONG  sautopos2;	/* auto current ISAM position */
#endif
	LONG  sautopos1;	/* auto current ISAM position */
	LONG  sautopart;	/* auto partition number */
	LONG  slogtime;		/* logon time */
	LONG  srqstime;		/* last request time */
	LONG  srqsfunc;		/* last rquest function # */
	LONG  sfncretflex;	/* special FLEXFILE ret values: only ctSRVR */
	LONG  susrrsvd[5];	/* spare members */
	NINT  srqssubf;		/* last request sub-function */
	NINT  sactflag;		/* active / inactive flag */
	TEXT  snodname[32];	/* node name */
#endif

#ifdef ctCAMOsdk
	LONG  sctcamver;
#endif
#ifdef ctHUGEFILE
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
#endif /* ctHUGEFILE */
	LONG  sct_gsrl1;	/* next serial number for data file */
	NLONG sct_usernm;	/* system dependent user number */
	UINT  sctdfrcls;	/* defer close count */
	NINT  sct_trdflg;	/* thread operation flag */
	NINT  sctcidxStkPtr;
	NINT  sctcidxCurCmd;
#ifdef ctFeatUDF_EXPR
	pVOID sudflist;
	NINT  sisexpreval;
#endif
	NINT  sabnflg;		/* counts stage of abandon tran processing */
	COUNT sctconid;
	TEXT  sct_userid[IDZ];	/* unique user id */
	TEXT  spare[PWZ];	/* unused ???? */
#ifdef ctSRVR
	UGRUP sct_userg[MAX_UGRUP];
				/* group list header */
#endif
	pFUSR sct_fup;		/* FUSR pointer for current file */
	ppctICON  sctconanc;	/* hash bins for context */
#ifdef DBGtree
	pVOID	  sct_walkh;	/* tree-walk degug list head */
	pVOID	  sct_walkt;	/* tree-walk degug list tail */
	NINT	  sctlflg;	/* load key flag	     */
#endif /* DBGtree */
#ifdef TRANPROC
	struct thrdgv
		 *trnlst;	/* transaction (hash) lists of users */
	ppSHADLST sct_ubit;	/* hash bins for srchshd */
#ifdef DBGhash
	pLONG     sdbg_shsh_u;
#endif
	pTEXT sctmrklst;	/* temp storage for exc marks during split */
	pTEXT sct_usrsp;	/* pointer to shadow swap buffer */
	pSHADLST sct_usrsl;	/* current shadow list element */
	VRLEN sct_usrsz;	/* swap buffer size */
	LONG  sct_usrtm;	/* activity time stamp (seconds) */
	LONG  gvresv2;
	NINT  sct_usrsv;	/* tran savepoint info */
	NINT  sct_rstflg;	/* TRANRST() flag */
#else
	COUNT stranactv;
	COUNT stransavp;
#endif
	NINT  sctrbflg;		/* rebuild flag */
	NINT  swhdrflg;		/* write header flag */
	ppLOKS sct_locks;	/* user lock table head */
	ppLOKS sct_ltail;	/* user lock table tail */
#ifdef DBGhash
	pLONG  sdbg_lhsh_u;
#endif
	COUNT sctusrprf;	/* user profile word */
	FILNO sctumxfil;	/* max files for user */
	FILNO scthghfil;	/* highest file number limit */
	NINT  sct_nelem[MAXLEV];
	NINT  sct_tight[MAXLEV];
	NINT  sct_melem[MAXLEV];
	NINT  sprvlokf;		/* previous lock state: datno		*/
	NINT  sprvlokt;		/* previous lock state: lock type	*/	
	LONG  sprvlokp;		/* previous lock state: recbyt (lw)	*/	
#ifdef ctHUGEFILE
	LONG  sprvlokh;		/* previous lock state: recbyt (hw)	*/	
#endif
	NINT  sct_tkp;		/* previous value of ct_tky		*/
	NINT  sct_sfxctp;	/* previous value of suffix count	*/
	NINT  sbtlev;		/* b-tree level counter. used as index of */
				/* ct_npath				  */
	NINT  sct_elm;		/* position within B-Tree node	*/
	NINT  sct_tky;		/* result of comparison between target	*/
				/* value and index entry.		*/
				/* ct_tky < 0 => target < index entry	*/
				/*	  = 0 => target = index entry	*/
				/*	  > 0 => target > index entry 	*/
	NINT  sct_flagpw;	/* temppw flag				*/
#ifdef ctTRSETtest
	NINT  trnbin;		/* tran hash bin			*/
#endif

	TEXT sct_dupkey[MAXLEN+1];/* for searches of duplicate keys */
	TEXT sspkey[MAXLEN+1];	/* temporary storage for key values during */
				/* node updates 			   */

	TEXT sct_temppw[PWZ];	/* temporary password  */
	TEXT sct_buf[CTBUFSIZ];	/* temporary io buffer */
	UTEXT sct_uflvr;	/* user flavor */
	UTEXT sct_ualgn;	/* user alignment */
	UTEXT sct_upntr;	/* user pointer size */

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
	COUNT sb_rerr_fil;
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

	pTEXT	sql_tbuf;
	pTEXT	sql_spos;
	LONG	 sql_olen;
	LONG	 sql_rlen;
	pVOID	 sql_db;
#ifdef ctPortNUMEGA_TR
	pVOID	ctuserstate;
#endif
	} CTGV;
typedef CTGV ctMEM *	pCTGV;

#ifdef TRANPROC

#define	cthHASHbins	1024
#define cthHASHmask	(cthHASHbins - 1)
EXTERN	pCTGV	cttrnhsh[cthHASHbins] ={(pCTGV)0};	/* transaction user hash list anchors */
					/* thHASHbins must be a power of two  */
#endif

typedef struct {
	pCTIS1  s1;
	ppCTIS2 s2;
	ppCOUNT sct_kyorg;
	ppCOUNT sct_kymap;
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
	COUNT   sseqkey;		/* current keyno		*/
#endif
	COUNT	sct_nwrcfg;
	COUNT	sct_vfsg;
	COUNT	sct_ismlk;
#ifdef RTREE
	COUNT	ssrtknm;
	COUNT	ssrtdat;
	COUNT	stmpdat;
#endif

	TEXT    sseqbuf[MAXLEN];	/* holds matching "partial" key */
	TEXT    sseqold[MAXLEN];	/* holds previous "partial" key */
	TEXT	sct_fndval[MAXLEN];
	} CTIS;
typedef CTIS ctMEM *	pCTIS;
typedef CTIS ctMEM * ctMEM * ppCTIS;

EXTERN pVOID   ctThrdUserVar[MXU2] ={(pVOID)0};

#ifndef CTBOUND
#ifdef ctCACHE_MEMORY

typedef struct usrcom {
	pTEXT	buf;
	VRLEN	len;
	VRLEN	pos;
	NINT	ver;
#ifdef ctHUGEFILE
	NINT	off;
#endif
	} USRCOM;
typedef USRCOM ctMEM *	pUSRCOM;
typedef USRCOM ctMEM * ctMEM * ppUSRCOM;

EXTERN pUSRCOM ct_com[MXU2] ={(pUSRCOM)0};
EXTERN pTEXT   ct_comb =(pTEXT)0;

#define ctusrbuf	ct_com[sOWNR]->buf
#define ctusrlen	ct_com[sOWNR]->len
#define ctusrpos	ct_com[sOWNR]->pos
#define ctclnver	ct_com[sOWNR]->ver
#define ctoutoffm(a)	ct_com[a]->off

#else /* ~ctCACHE_MEMORY */

EXTERN pTEXT   sctusrbuf[MXU2] ={(pTEXT)0}; /* user commbuffer */
EXTERN VRLEN   sctusrlen[MXU2] ={(VRLEN)0}; /* commbuffer length */
EXTERN VRLEN   sctusrpos[MXU2] ={(VRLEN)0}; /* position in buffer */
EXTERN NINT    sctclnver[MXU2] ={(NINT)0}; /* client version from pb.pbvr */
#ifdef ctHUGEFILE
EXTERN NINT    sctoutoff[MXU2] ={(NINT)0};	/* client dependent output_offset */
#endif

#define ctusrbuf	sctusrbuf[sOWNR]
#define ctusrlen	sctusrlen[sOWNR]
#define ctusrpos	sctusrpos[sOWNR]
#define ctclnver	sctclnver[sOWNR]
#define ctoutoffm(a)	sctoutoff[a]

#endif /* ~ctCACHE_MEMORY */
#endif /* ~CTBOUND */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ctFeatSrvTimer
EXTERN SRVTIMER		ctsrvtimer[MXU2] ={(SRVTIMER)0};
#endif

#ifdef ctFeatSrvLock
EXTERN SRVLOCK		ctsrvlock[MXU2] ={(SRVLOCK)0};
#endif

#ifdef ctCACHE_MEMORY
EXTERN pCTSTATV ctstatv[MXU2] ={(pCTSTATV)0};
EXTERN pTEXT	ctstatvb =(pTEXT)0;

#define uerr_codm(a)	ctstatv[a]->uec
#define isam_errm(a)	ctstatv[a]->iec

#else

EXTERN CTSTATV	ctstatv[MXU2] ={(CTSTATV)0};
EXTERN NINT	sctua[MXU2] ={(NINT)0};
EXTERN NINT	sctma[MXU2] ={(NINT)0};

#define uerr_codm(a)	ctstatv[a].uec
#define isam_errm(a)	ctstatv[a].iec
#endif

#ifdef __cplusplus
}
#endif

EXTERN VRLEN   ssql_len[MXU2] ={(VRLEN)0};
#ifdef ctPortVINES
#ifdef RUNTCBTABLE
EXTERN NINT    ctusrmapId =(NINT)0;
EXTERN taskid  ctusrhmap[MXU2] ={(taskid)0};
#else
EXTERN NINT    ctusrhmap[MXU2] ={(NINT)0};
#endif
#else
EXTERN NINT    ctusrhmap[MXU2] ={(NINT)0};
#endif
EXTERN NINT    ctusrhcnt[MXU2] ={(NINT)0};

EXTERN NINT	ctusraflg[MXU2] ={(NINT)0};/* HYS if independent thread attached */
#ifdef CTBOUND
EXTERN NINT	ctst[MXU2] ={(NINT)0};
#endif

EXTERN pCTGV   ctgv[MXU2] ={(pCTGV)0};

#ifdef CTTHRDH
#ifdef MULTITRD
EXTERN NLONG   ctrcparm[MXU2] ={(NLONG)0};
#endif
#endif

EXTERN ppCTIS  ctis =(ppCTIS)0;

EXTERN ppFUSR  ct_fusr =(ppFUSR)0;
EXTERN pBLKLST ct_blk[MXU2] ={(pBLKLST)0};

#ifdef DBGtree
#define ct_walkh	lctgv->sct_walkh
#define ct_walkt	lctgv->sct_walkt
#define ctlflg		lctgv->sctlflg
#endif /* DBGtree */
#define ct_ubit(owner)	ctgv[owner]->sct_ubit
#ifdef DBGhash
#define dbg_shsh_u(owner) ctgv[owner]->sdbg_shsh_u
#endif
#define ctconanc	lctgv->sctconanc
#define ctconid		lctgv->sctconid
#define ct_rstflg	lctgv->sct_rstflg
#define tranactv	lctgv->stranactv
#define transavp	lctgv->stransavp
#define abnlog		lctgv->sabnlog
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
#define isolev		lctgv->sisolev
#define ctblktim	lctgv->sctblktim
#define ctbatch		lctgv->batch
#define ctbatnum	lctgv->sbatnum
#define ctbatmax	lctgv->sbatmax
#define ct_savbat	lctgv->ssavbat
#define cthistory	lctgv->history
#define cthistund	lctgv->histund
#define cthstnum	lctgv->shstnum
#define ct_savhst	lctgv->ssavhst
#define ct_locks	lctgv->sct_locks
#define ct_ltail	lctgv->sct_ltail
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
#define ctdfrcls	lctgv->sctdfrcls
#define ctxvlen		lctgv->sctxvlen
#define seglsthdr	lctgv->sseglsthdr
#define ctcidxStk	lctgv->sctcidxStk
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
#define cthghwrd	lctgv->scthghwrd
#define fncret		lctgv->sfncret
#define fncretflex	lctgv->sfncretflex
#define ct_npath1	lctgv->sct_npath1
#ifdef ctHUGEFILE
#define ct_npath2	lctgv->sct_npath2
#endif /* ctHUGEFILE */
#define ct_nelem	lctgv->sct_nelem
#define ct_tight	lctgv->sct_tight
#define ct_melem	lctgv->sct_melem
#define prvlokf		lctgv->sprvlokf
#define prvlokt		lctgv->sprvlokt
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
#define ctmrklst	lctgv->sctmrklst
#ifndef ctCACHE_MEMORY
#define ctshdmem	sctshdmem[sOWNR]
#endif
#define ct_usrsv	lctgv->sct_usrsv
#define ct_usrsp	lctgv->sct_usrsp
#define ct_usrsl	lctgv->sct_usrsl
#define ct_usrsz	lctgv->sct_usrsz
#define ct_usrtm	lctgv->sct_usrtm
#endif
#define whdrflg		lctgv->swhdrflg
#define ctrbflg		lctgv->sctrbflg
#define ct_trdflg	lctgv->sct_trdflg
#define ct_userid	lctgv->sct_userid
#define ct_usernm	lctgv->sct_usernm
#define ct_sqlpwd	lctgv->sct_sqlpwd
#define ct_userg	lctgv->sct_userg
#define ct_fup		lctgv->sct_fup
#define ct_dupkey	lctgv->sct_dupkey
#define spkey		lctgv->sspkey
#define ct_elm		lctgv->sct_elm
#define ct_tky		lctgv->sct_tky
#define ct_tkp		lctgv->sct_tkp
#define ct_sfxctp	lctgv->sct_sfxctp
#define ct_lnode1	lctgv->sct_lnode1
#define ct_fnode1	lctgv->sct_fnode1
#define ct_nwnod1	lctgv->sct_nwnod1
#ifdef ctHUGEFILE
#define ct_lnode2	lctgv->sct_lnode2
#define ct_fnode2	lctgv->sct_fnode2
#define ct_nwnod2	lctgv->sct_nwnod2
#define ct_gsrl2	lctgv->sct_gsrl2
#endif /* ctHUGEFILE */
#define btlev		lctgv->sbtlev

#ifdef ctFeatSrvTimer
#define tim_prev	ctsrvtimer[sOWNR].stim_prev
#define tim_call	ctsrvtimer[sOWNR].stim_call
#define tim_recv	ctsrvtimer[sOWNR].stim_recv
#define tim_work	ctsrvtimer[sOWNR].stim_work
#define tim_send	ctsrvtimer[sOWNR].stim_send
#endif

#ifdef ctFeatSrvLock
#define loktry		ctsrvlock[sOWNR].sloktry
#define lokhlk		ctsrvlock[sOWNR].slokhlk
#define lokblk		ctsrvlock[sOWNR].slokblk
#define lokhbk		ctsrvlock[sOWNR].slokhbk
#define lokdlk		ctsrvlock[sOWNR].slokdlk
#define lokdny		ctsrvlock[sOWNR].slokdny
#endif

#ifdef ctCACHE_MEMORY
#ifdef CTPERM
#define uerr_cod	ctstatv[sOWNR]->uec
#define sysiocod	ctstatv[sOWNR]->sec
#define isam_err	ctstatv[sOWNR]->iec
#define isam_fil	ctstatv[sOWNR]->ifl
#define cndxerr		ctstatv[sOWNR]->cec
#define deltaconn	ctstatv[sOWNR]->dcn
#else
#define uerr_cod	ctstatv[OWNER]->uec
#define sysiocod	ctstatv[OWNER]->sec
#define isam_err	ctstatv[OWNER]->iec
#define isam_fil	ctstatv[OWNER]->ifl
#define cndxerr		ctstatv[OWNER]->cec
#define deltaconn	ctstatv[OWNER]->dcn
#endif
#define sql_status1	ctstatv[sOWNR]->ql1
#define sql_status2	ctstatv[sOWNR]->ql2
#define ctusrtot	ctstatv[sOWNR]->tot
#define ctusrsum	ctstatv[sOWNR]->sum
#define ctshdmem	ctstatv[sOWNR]->mem
#define ct_usrsi	ctstatv[sOWNR]->usi
#define ctua(a)		ctstatv[a]->ua
#define ctma(a)		ctstatv[a]->ma

#else /* ~ctCACHE_MEMORY */

#ifdef CTPERM
#define uerr_cod	ctstatv[sOWNR].uec
#define sysiocod	ctstatv[sOWNR].sec
#define isam_err	ctstatv[sOWNR].iec
#define isam_fil	ctstatv[sOWNR].ifl
#define cndxerr		ctstatv[sOWNR].cec
#define deltaconn	ctstatv[sOWNR].dcn
#else
#define uerr_cod	ctstatv[OWNER].uec
#define sysiocod	ctstatv[OWNER].sec
#define isam_err	ctstatv[OWNER].iec
#define isam_fil	ctstatv[OWNER].ifl
#define cndxerr		ctstatv[OWNER].cec
#define deltaconn	ctstatv[OWNER].dcn
#endif
#define sql_status1	ctstatv[sOWNR].ql1
#define sql_status2	ctstatv[sOWNR].ql2
#define ctua(a)		sctua[a]
#define ctma(a)		sctma[a]
#endif /* ~ctCACHE_MEMORY */

#define sql_len		ssql_len[sOWNR]
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

#else /* MULTITRD */

EXTERN BATHDR  ctbatch =(BATHDR)0;
EXTERN LONG    ct_spc =(LONG)0;
EXTERN LONG    ct_npath1[MAXLEV] ={(LONG)0};/* array to trace path down B-tree. Assumes  */
				 /* maximum of MAXLEV - 1 levels in B-tree.   */
#ifdef ctHUGEFILE
EXTERN LONG    ct_npath2[MAXLEV] ={(LONG)0};
#endif /* ctHUGEFILE */
#ifdef ctOldALCBAT
EXTERN COUNT   ctbatnum =(COUNT)0;
EXTERN COUNT   ctbatmax =(COUNT)0;
EXTERN pBATHDR ct_savbat =(pBATHDR)0;
#else
EXTERN pSAVBAT ctbatnum =(pSAVBAT)0;
EXTERN ppSAVBAT
	       ct_savbat =(ppSAVBAT)0;
#endif
EXTERN HSTHDR	cthistory =(HSTHDR)0;
EXTERN pHSTLST	cthistund =(pHSTLST)0;
EXTERN pSAVHST	cthstnum =(pSAVHST)0;
EXTERN ppSAVHST	ct_savhst =(ppSAVHST)0;
EXTERN pVOID	ctcidxStk =(pVOID)0;
EXTERN pSEGLST	seglsthdr =(pSEGLST)0;
EXTERN pTEXT	ct_trnfil =(pTEXT)0;
EXTERN NINT  ct_nelem[MAXLEV] ={(NINT)0};
EXTERN NINT  ct_tight[MAXLEV] ={(NINT)0};
EXTERN NINT  ct_melem[MAXLEV] ={(NINT)0};
EXTERN NINT	prvlokf =(NINT)0;
EXTERN NINT	prvlokt =(NINT)0;
EXTERN LONG	prvlokp =(LONG)0;
#ifdef ctHUGEFILE
EXTERN LONG	prvlokh =(LONG)0;
#endif
EXTERN NINT  ctcidxStkPtr =(NINT)0;
EXTERN NINT  ctcidxCurCmd =(NINT)0;
#ifdef ctFeatUDF_EXPR
EXTERN pVOID udflist =(ppVOID)0;
EXTERN NINT  isexpreval =(NINT)0;
#endif
EXTERN COUNT ctconid =(COUNT)0;
EXTERN ppctICON
	     ctconanc =(ppctICON)0;	/* hash bins for context */
#ifdef DBGtree
EXTERN pVOID ct_walkh =(pVOID)0;
EXTERN pVOID ct_walkt =(pVOID)0;
EXTERN NINT  ctlflg =(NINT)0;
#endif /* DBGtree */
#ifdef TRANPROC
#define ct_ubit(owner)	sct_ubit
EXTERN ppSHADLST sct_ubit =(ppSHADLST)0;	/* hash bins for srchshd */
#ifdef DBGhash
#define dbg_shsh_u(owner)	sdbg_shsh_u
EXTERN pLONG sdbg_shsh_u =(pLONG)0;
#endif
EXTERN pTEXT ctmrklst =(pTEXT)0;
EXTERN pTEXT ct_usrsp =(pTEXT)0;
EXTERN pSHADLST ct_usrsl =(pSHADLST)0;
EXTERN VRLEN ct_usrsz =(VRLEN)0;
EXTERN LONG  ctshdmem =(LONG)0;
EXTERN LONG  ctusrsum =(LONG)0;
EXTERN LONG  ctusrtot =(LONG)0;
EXTERN NINT  ct_usrsi =(NINT)0;
EXTERN NINT  ct_usrsv =(NINT)0;
EXTERN NINT  ct_rstflg =(NINT)0;		/* TRANRST() flag */
#endif
EXTERN NINT  ctrbflg =(NINT)0;
EXTERN ppLOKS ct_locks =(ppLOKS)0;
EXTERN ppLOKS ct_ltail =(ppLOKS)0;
#ifdef DBGhash
EXTERN pLONG  dbg_lhsh_u =(pLONG)0;
#endif
#ifdef ctCUSTOM
EXTERN pVOID  pcustmem =(pVOID)0;
EXTERN LONG   custops =(LONG)0;
#endif
#ifdef ctCAMO
EXTERN LONG   ucamlen =(LONG)0;
EXTERN pCAMFNC
	      ucamfnc =(pCAMFNC)0;
EXTERN pTEXT  ucamptr =(pTEXT)0;
EXTERN pTEXT  ct_cam =(pTEXT)0;
EXTERN VRLEN  ct_camsiz =(VRLEN)0;
#endif
EXTERN LONG   ctops =(LONG)0;		/* set operation state bit mask		*/
EXTERN LONG   ctstate =(LONG)0;		/* internal state bit mask		*/
EXTERN VRLEN  ctxvlen =(VRLEN)0;		/* vlen combined op max buffer length	*/
					
EXTERN TEXT ct_dupkey[MAXLEN+1] ={(TEXT)0};/* for searches of duplicate keys */
EXTERN TEXT spkey[MAXLEN+1] ={(TEXT)0};	/* temporary storage for key values during */
				/* node updates 			   */

EXTERN COUNT ctusrprf =(COUNT)0;		/* user profile word */
EXTERN UINT  ctdfrcls =(UINT)0;		/* defer close count */
EXTERN UINT  ct_trnfilsz =(UINT)0;	/* size of ct_trnfil */
EXTERN NINT  ct_elm =(NINT)0;		/* position within B-Tree node	*/
EXTERN NINT  ct_tky =(NINT)0;		/* result of comparison between target	*/
				/* value and index entry.		*/
				/* ct_tky < 0 => target < index entry	*/
				/*	  = 0 => target = index entry	*/
				/*	  > 0 => target > index entry 	*/
EXTERN NINT  ct_tkp =(NINT)0;		/* previous value of ct_tky		*/
EXTERN NINT  ct_sfxctp =(NINT)0;		/* previous value of suffix count	*/
EXTERN LONG  ct_lnode1 =(LONG)0;		/* last node found during walk down tree */
EXTERN LONG  ct_fnode1 =(LONG)0;		/* node found during search/retrieval    */
EXTERN LONG  ct_nwnod1 =(LONG)0;		/* pointer to new node */
#ifdef ctHUGEFILE
EXTERN LONG  ct_lnode2 =(LONG)0;		/* last node found during walk down tree */
EXTERN LONG  ct_fnode2 =(LONG)0;		/* node found during search/retrieval    */
EXTERN LONG  ct_nwnod2 =(LONG)0;		/* pointer to new node */
EXTERN LONG  ct_gsrl2 =(LONG)0;		/* next serial number for data file */
#endif /* ctHUGEFILE */
EXTERN LONG  ct_gsrl1 =(LONG)0;		/* next serial number for data file */
EXTERN NINT  ct_trdflg =(NINT)0;		/* thread operation flag */
EXTERN NINT  btlev =(NINT)0;		/* b-tree level counter. used as index of */
				/* ct_npath				  */
EXTERN COUNT uerr_cod =(COUNT)0;		/* user error cod */
EXTERN COUNT sysiocod =(COUNT)0;		/* system error cod */
EXTERN COUNT isam_err =(COUNT)0;
EXTERN COUNT isam_fil =(COUNT)0;
EXTERN VRLEN sql_len =(VRLEN)0;
EXTERN COUNT sql_status1 =(COUNT)0;
EXTERN COUNT sql_status2 =(COUNT)0;
EXTERN COUNT cndxerr =(COUNT)0;		/* conditional index error cod */
EXTERN UTEXT ct_uflvr =(UTEXT)0;
EXTERN UTEXT ct_ualgn =(UTEXT)0;
EXTERN UTEXT ct_upntr =(UTEXT)0;
EXTERN TEXT  ct_buf[CTBUFSIZ] ={(TEXT)0};	/* temporary io buffer */

#ifdef RB_CALLBACK
EXTERN pRBLCBFNC rblcbfnc =(pRBLCBFNC)0;
EXTERN ULONG     rblcbcnt =(ULONG)0;
EXTERN UCOUNT    rblcbstp =(UCOUNT)0;
#endif

#define ctumxfil	ct_mxfil
#define cthghfil	ct_mxfil

#endif

EXTERN UINT	ctlog9477 =(UINT)0;

#endif /* ~ctCLIENT */
#endif /* ctNOGLOBALS */

#include "ctfunp.h"

/*^***********************************/
#ifdef ctPortUSE_W32DATA_SEG
#pragma data_seg()
#pragma comment(linker,"/SECTION:RAYS_CTGVAR2_DATASEG,RWS")
#endif
/*~***********************************/

#endif /* ctGVARH */

/* end of ctgvar.h  */
