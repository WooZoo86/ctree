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


#ifdef MULTITRD
EXTERN UINT	 ctchkpstt;	/* checkpoint thread status */

#define ctCHKPbegin		 1
#define ctCHKPbuffers		 2
#define ctCHKPcache		 3
#define ctCHKPocsema		 4
#define ctCHKPchksema		 5
#define ctCHKPquiet		 6
#define ctCHKPtranac		 7
#define ctCHKPabtsema		 8
#define ctCHKPcomsema		 9
#define ctCHKPdcmsema		10
#define ctCHKPgotsemas		11
#define ctCHKPfiles		12
#define ctCHKPcalclength	13
#define ctCHKPchk_coms		14
#define ctCHKPlogsema		15
#define ctCHKPgvsema		16
#define ctCHKPcompose		17
#define ctCHKPabtnod		18
#define ctCHKPcpy_coms		19
#define ctCHKPgotcoms		20
#define ctCHKPwrtlog		21
#define ctCHKPstrfil		22
#define ctCHKPchkret		23
#define ctCHKPfinal		24
#define ctCHKPlogsema2		25
#define ctCHKPend		26
#define ctCHKPredque		27
#define ctCHKPidlechksema	28
#define ctCHKPidleabtsema	29
#define ctCHKPidlecomsema	30
#define ctCHKPidledcmsema	31
#define ctCHKPidlefresemas	32
#define ctCHKPerrque		33
#define ctCHKPcallchkp		34
#endif /* MULTITRD */

#ifndef ctNOGLOBALS
EXTERN LONG	 ctdmptim;	/* dynamic dump beginn time */
EXTERN LONG	 ctdlgnum;	/* beginning log during dump */
EXTERN LONG	 ctelgnum;	/* ending log during dump */
EXTERN LONG	 ctdlgpos;	/* position in ctdlgnum */
EXTERN LONG	 ctelgpos;	/* position in ctelgnum */
#ifndef ctFeatSNAPSHOT
EXTERN LONG	 ctcpcnt;	/* check point count */
#endif
EXTERN LONG	 ctcpchk;	/* check point count less delta */
EXTERN LONG	 ctelcnt;	/* check point count at last ENDLOG */
#ifndef ctFeatPREIMAGE_SWAP
EXTERN SYSNO	 ctshdlfil;	/* shadow swap file # */
#endif

EXTERN LONG	 ct_lstlog;	/* last checkpoint log#		*/
EXTERN ULONG	 ct_lstpos;	/* last checkpoint log position	*/
EXTERN LONG	 ct_strlog;	/* checkpoint log# at startup		*/
EXTERN ULONG	 ct_strpos;	/* checkpoint log position at startup	*/
EXTERN LONG	 ct_rcvlog;	/* oldest log required for recovery  */
EXTERN LONG	 ctfwdlog;	/* log for starting TRANFWD (ctrdmp) */
EXTERN ULONG	 ctfwdpos;	/* position for starting TRANFWD (ctrdmp) */
EXTERN ULONG	 ctfwdpps;	/* prev pos for starting TRANFWD (ctrdmp) */

#ifdef ctCACHE_MEMORY

#ifdef ctFeatIICT
/* When an IICT begins, it saves off the current transaction state, which is
** stored in fields of the USRTRN structure. When the IICT ends, it restores
** the original transaction state variables. However, an IICT should not be
** permitted to modify some of the transaction state variables, and so here
** we define the USRTRN2 structure to hold these values. */
typedef struct usrtrn2 {
	SEMA	sema;	/* ct_usrsema	*/
	LONG	sm;	/* split mark	*/
	LONG	tl;	/* log status	*/
#ifdef ctBEHAV_IICTflexSTT
	LONG	st3;	/* ctstat3 bits set by outer tran */
	LONG	st4;	/* ctstat4 bits set by outer tran */
	LONG	st5;	/* ctstat5 bits set by outer tran */
#endif
} USRTRN2, *pUSRTRN2;
#endif

typedef struct usrtrn {
	pSHADLST
		sh;	/* shadow tail	*/
	pSHADLST
		sv;	/* shadow savpt	*/
	LONG8	mem;	/* shd memory	*/
#ifdef ctFeatPREIMAGE_SWAP
	LONG8	shdmax;	/* preimage space mem limit	*/
	NINT	sPreimageSwapSysFilno; /* system file number of preimage swap file for this connection */
	NINT	sPreimageSwapUsrFilno; /* user file number of preimage swap file for this connection */
#endif
	pTEXT	sct_usrsp;	/* pointer to shadow swap buffer */
	pSHADLST sct_usrsl;	/* current shadow list element */
	VRLEN	sct_usrsz;	/* swap buffer size */
#ifdef ctBEHAV_FLUSH_NODE_MARKS
	pSHADLST
		nfl;	/* node flush list */
	pSFILHSH
		ffl;	/* file flush list */
	UINT	ffb;	/* number of hash bins */
	UINT	ffc;	/* current number of elements */
#endif
#ifdef ctRECBYTIDX
	pCOALST	cl;	/* coal list	*/
	NINT	cc;	/* coal current	*/
	NINT	ct;	/* coal total	*/
	NINT	cs;	/* coal status	*/
#endif
#ifdef ctFeatQUIET
	NINT	at;	/* active flag	*/
#endif
#ifdef ctFeat6BT
	LONG	tr2;
	LONG	ix2;
#endif
#ifdef ctXTDLOGgrp
	LONG	gr;	/* cur group #	*/
	LONG	gp;	/* store group #*/
#endif
#if (defined(ctXTDLOG) || defined(ctSUCTRAN))
	LONG	bl;	/* tranbeg log#	*/
	LONG	bp;	/* tranbeg pos	*/
	LONG	el;	/* tranend log#	*/
	LONG	ep;	/* tranend pos	*/
#ifdef ctSUCTRAN
	LONG	tv;	/* save tr	*/
	LONG	tv2;	/* save tr2	*/
#endif
#endif
	ULONG	sq;	/* usr tran seq#*/
	LONG	tr;	/* tran#	*/
#ifndef ctFeatIICT
	LONG	tl;	/* log status	*/
#endif
	LONG	ix;	/* index status	*/
	LONG	ty;	/* tran type	*/
	NINT	md;	/* tran mode	*/
	NINT	pt;	/* chkpt status	*/
#ifndef ctFeatIICT
	LONG	sm;	/* split marks	*/
#endif
#ifdef ctFeatDFRIDX
	LONG	dfrkln;	/* log number of first deferred key entry for tran */
	ULONG	dfrklp;	/* log offset of first deferred key entry for tran */
#ifdef ctFeatRUCB
	pSHADLST
		rucbh;	/* first record update callback DFRKEY entry */
	pSHADLST
		rucbt;	/* last record update callback DFRKEY entry */
#endif
#endif
#ifdef ctFeatADDKY_DEFERD
	pSHADLST
		ah;	/* ptr head skipped adds */
	pSHADLST
		ae;	/* ptr tail		 */
	pVOID	kc;	/* key context pointer	 */
#endif
#ifdef ctFeatIICT
	ppSHADLST
		ub;	/* hash bins for srchshd		*/
	HSHSTT	st;	/* preimage hash state structure	*/
	LONG	uv;	/* tran savepoint info			*/
	NINT	rf;	/* TRANRST() flag			*/
	NINT	ic;	/* IICT flag				*/
	UINT	df;	/* ctdfrcls				*/
	UINT	tb;	/* transaction hash bin			*/
	struct usrtrn
		*trnlstlnk; /* transaction (hash) lists of users*/
	NINT	ownr;	/* task ID				*/
#endif
#ifdef ctFeatFUSRCLRoptimize
	NINT	tf;	/* tran file list for ctfusrclr		*/
#endif
	NINT	uf;	/* recovery undo flg: undflg		*/
#ifdef ctFeatREPLICAT_SYNC
	pULONG	usraList; /* handles to sync repl agents that this transaction depends on */
	UCOUNT	usraCount; /* number of sync repl agents that this transaction depends on */
#endif
	} USRTRN;
typedef USRTRN ctMEM *	pUSRTRN;
typedef USRTRN ctMEM * ctMEM * ppUSRTRN;


EXTERN pTEXT	 ct_usrb;	/* base address for aligned memory	*/
EXTERN pUSRTRN	 ct_usr[MXU2];	/* user transaction structure		*/
EXTERN pTEXT	 ctpusrsemab;	/* base address for aligned ct_usrsema	*/
EXTERN pSEMA	 ctpusrsema[MXU2];	/* array of ct_usrsema ptrs	*/
#ifdef ctFeatIICT
EXTERN pTEXT	 ct_savb;	/* base address for aligned memory	*/
EXTERN pUSRTRN	 ct_sav[MXU2];  /* save transaction structure w/ IICT	*/
#endif

#ifdef ctFeatDFRIDX
#define ct_usrdkln(a)	ct_usr[a]->dfrkln
#define ct_usrdklp(a)	ct_usr[a]->dfrklp
#ifdef ctFeatRUCB
#define rucbhed(a)	ct_usr[a]->rucbh
#define rucbend(a)	ct_usr[a]->rucbt
#endif
#endif
#define ct_usrsq(a)	ct_usr[a]->sq
#define ct_usrtr(a)	ct_usr[a]->tr  /* active transaction number. 1 == deferred begin. */
#ifdef ctFeatQUIET
#define ct_usrat(a)	ct_usr[a]->at
#endif
#ifdef ctXTDLOGgrp
#define ct_usrgr(a)	ct_usr[a]->gr
#define ct_usrgp(a)	ct_usr[a]->gp
#endif
#ifdef ctFeat6BT
#define ct_usrtr2(a)	ct_usr[a]->tr2 /* active transaction number - high 2 bytes */
#define ct_usrix2(a)	ct_usr[a]->ix2
#define ct_usrtb(a)	ct_usr[a]->tb
#endif
#ifdef ctSUCTRAN
#define ct_usrbl(a)	ct_usr[a]->bl
#define ct_usrbp(a)	ct_usr[a]->bp
#define ct_usrel(a)	ct_usr[a]->el
#define ct_usrep(a)	ct_usr[a]->ep
#define ct_usrtv(a)	ct_usr[a]->tv
#define ct_usrtv2(a)	ct_usr[a]->tv2
#endif
#define ct_usrix(a)	ct_usr[a]->ix
#ifdef ctFeatIICT
#define ct_usrsm(a)	((pUSRTRN2) ctpusrsema[a])->sm
#define ct_usrtl(a)	((pUSRTRN2) ctpusrsema[a])->tl
#ifdef ctBEHAV_IICTflexSTT
#define ct_usrst3(a)	((pUSRTRN2) ctpusrsema[a])->st3
#define ct_usrst4(a)	((pUSRTRN2) ctpusrsema[a])->st4
#define ct_usrst5(a)	((pUSRTRN2) ctpusrsema[a])->st5
#endif
#else
#define ct_usrsm(a)	ct_usr[a]->sm
#define ct_usrtl(a)	ct_usr[a]->tl /* Log number of TRANBEG. Negative values special. */
#endif
#define ct_usrmd(a)	ct_usr[a]->md
#define ct_usrty(a)	ct_usr[a]->ty  /* transaction type bits */
#define ct_chkpt(a)	ct_usr[a]->pt  /* enabled in ctwrtlog: YES=TRANBEG  NO=TRANEND
					  Also bits DATCOM_WINDOW IDXABT_WINDOW   */ 
#define ctlstshdm(a)	ct_usr[a]->sh
#define ctlstsavm(a)	ct_usr[a]->sv
#ifdef ctBEHAV_FLUSH_NODE_MARKS
#define ct_nodflslst(a)	 ct_usr[a]->nfl /* node flush list */
#define ct_filflslst(a)	 ct_usr[a]->ffl /* file flush list */
#define ct_filflsbins(a) ct_usr[a]->ffb /* number of hash bins */
#define ct_filflsnent(a) ct_usr[a]->ffc /* current number of elements */
#endif
#ifdef ctFeatFUSRCLRoptimize
#define ct_usrtf(a)	ct_usr[a]->tf
#endif
#ifdef ctRECBYTIDX
#define ct_coalst(a)	ct_usr[a]->cl
#define ct_coalcr(a)	ct_usr[a]->cc
#define ct_coaltt(a)	ct_usr[a]->ct
#define ct_coalcs(a)	ct_usr[a]->cs
#endif
#ifdef ctFeatADDKY_DEFERD
#define skpaddhed(a)	ct_usr[a]->ah
#define skpaddend(a)	ct_usr[a]->ae
#define skpkeyctx(a)	ct_usr[a]->kc
#endif
#define undflg(a)	ct_usr[a]->uf
#define ctshdmem	ct_usr[sOWNR]->mem
#define ct_usrsp	ct_usr[sOWNR]->sct_usrsp
#define ct_usrsl	ct_usr[sOWNR]->sct_usrsl
#define ct_usrsz	ct_usr[sOWNR]->sct_usrsz
#define CTU_MaxPreimageData(a)	ct_usr[a]->shdmax
#define CTU_PreimageSwapSysFilno(a)	ct_usr[a]->sPreimageSwapSysFilno
#define CTU_PreimageSwapUsrFilno(a)	ct_usr[a]->sPreimageSwapUsrFilno
#define CTU_usraList(a)			ct_usr[a]->usraList
#define CTU_usraCount(a)		ct_usr[a]->usraCount

/*
** pointer to thread's usrsema. usrsema moved out of USRTRN to
** simplify ctFeatIICT support and further reduce false cache-line hits.
*/
#define ct_usrsema(a)	ctpusrsema[a]

#ifdef ctFeatIICT
#define iictflg(a)	ct_usr[a]->ic
#define ct_ubit(a)	ct_usr[a]->ub
#define shadstt(a)	ct_usr[a]->st
#define ct_usrsv(a)	ct_usr[a]->uv
#define ct_rstflg(a)	ct_usr[a]->rf

/*
** subset of ct_sav[] elements that are
** explicity referenced
*/
#define ct_savtr(a)	ct_sav[a]->tr
#define ct_savtr2(a)	ct_sav[a]->tr2
#define ct_savix(a)	ct_sav[a]->ix
#define ct_savix2(a)	ct_sav[a]->ix2
#define ct_savty(a)	ct_sav[a]->ty
#define ct_savbl(a)	ct_sav[a]->bl
#define ct_savbp(a)	ct_sav[a]->bp
#define ct_savpt(a)	ct_sav[a]->pt
#define ct_savuf(a)	ct_sav[a]->uf
#define ct_savtb(a)	ct_sav[a]->tb
#define ctsavshdm(a)	ct_sav[a]->sh
#define ctsavshdmem(a)	ct_sav[sOWNR]->mem
#define CTUSAV_MaxPreimageData(a)	ct_sav[a]->shdmax
#endif /* ctFeatIICT */

#else /* ~ctCACHE_MEMORY */

EXTERN LONG	 ctsusrsq[MXU2];/* user transaction sequence number	*/
EXTERN LONG	 ctsusrtr[MXU2];/* active transaction # for user or zero*/
#ifdef ctFeatQUIET
EXTERN NINT	 ctsusrat[MXU2];/* active transaction flag		*/
#endif
#ifdef ctXTDLOGgrp
EXTERN LONG	 ctsusrgr[MXU2];/* update group # for user or zero	*/
EXTERN LONG	 ctsusrgp[MXU2];/* store  group # for user		*/
#endif
#ifdef ctFeat6BT
EXTERN LONG	 ctsusrtr2[MXU2];
EXTERN LONG	 ctsusrix2[MXU2];
#endif
#ifdef ctSUCTRAN
EXTERN LONG	 ctsusrbl[MXU2];
EXTERN LONG	 ctsusrbp[MXU2];
EXTERN LONG	 ctsusrel[MXU2];
EXTERN LONG	 ctsusrep[MXU2];
EXTERN LONG	 ctsusrtv[MXU2];
EXTERN LONG	 ctsusrtv2[MXU2];
#endif
EXTERN LONG	 ctsusrtl[MXU2];/* log file sequence number for BEGTRAN	*/
EXTERN LONG	 ctsusrix[MXU2];/* log file index op number		*/
#ifdef MULTITRD
EXTERN LONG	 ctsusrsm[MXU2];/* number of marks in split node process*/
#endif
EXTERN NINT	 ctsusrmd[MXU2];/* save transaction mode		*/
EXTERN pSEMA	 ctsusrsema;	/* commit/abort processing semaphore	*/
EXTERN LONG	 ctsusrty[MXU2];/* ctSHADOW / ctLOGFIL transaction type	*/
EXTERN NINT	 ctschkpt[MXU2];/* check point flag 			*/
EXTERN ppSHADLST ctlstshd;	/* linked list tail for pre-image list	*/
EXTERN ppSHADLST ctlstsav;	/* last save point pointer		*/
#ifdef ctBEHAV_FLUSH_NODE_MARKS
EXTERN pSHADLST  ctsnodflslst[MXU2];  /* node flush list */
EXTERN pSFILHSH  ctsfilflslst[MXU2];  /* file flush list */
EXTERN UINT	 ctsfilflsbins[MXU2]; /* number of hash bins */
EXTERN UINT	 ctsfilflsnent[MXU2]; /* current number of elements */
#endif
#ifdef ctRECBYTIDX
EXTERN pCOALST	 ctscoalst[MXU2];
EXTERN NINT	 ctscoalcr[MXU2];
EXTERN NINT	 ctscoaltt[MXU2];
EXTERN NINT	 ctscoalcs[MXU2];
#endif
#ifdef ctFeatADDKY_DEFERD
EXTERN ppSHADLST sskpaddhed[MXU2];
EXTERN ppSHADLST sskpaddend[MXU2];
EXTERN pVOID     sskpkeyctx[MXU2];
#endif

#ifdef MULTITRD
#define ct_usrsq(a)	ctsusrsq[a]
#define ct_usrtr(a)	ctsusrtr[a]
#ifdef ctFeatQUIET
#define ct_usrat(a)	ctsusrat[a]
#endif
#ifdef ctXTDLOGgrp
#define ct_usrgr(a)	ctsusrgr[a]
#define ct_usrgp(a)	ctsusrgp[a]
#endif
#ifdef ctFeat6BT
#define ct_usrtr2(a)	ctsusrtr2[a]
#define ct_usrix2(a)	ctsusrix2[a]
#endif
#ifdef ctSUCTRAN
#define ct_usrbl(a)	ctsusrbl[a]
#define ct_usrbp(a)	ctsusrbp[a]
#define ct_usrel(a)	ctsusrel[a]
#define ct_usrep(a)	ctsusrep[a]
#define ct_usrtv(a)	ctsusrtv[a]
#define ct_usrtv2(a)	ctsusrtv2[a]
#endif
#define ct_usrtl(a)	ctsusrtl[a]
#define ct_usrix(a)	ctsusrix[a]
#define ct_usrsm(a)	ctsusrsm[a]
#define ct_usrmd(a)	ctsusrmd[a]
#define ct_usrty(a)	ctsusrty[a]
#define ct_chkpt(a)	ctschkpt[a]
#define ct_usrsema(a)	(ctsusrsema+(a))	/* change to pSEMA from SEMA */
#endif /* MULTITRD */
#ifdef ctRECBYTIDX
#define ct_coalst(a)	ctscoalst[a]
#define ct_coalcr(a)	ctscoalcr[a]
#define ct_coaltt(a)	ctscoaltt[a]
#define ct_coalcs(a)	ctscoalcs[a]
#endif
#define ctlstshdm(a)	ctlstshd[a]
#define ctlstsavm(a)	ctlstsav[a]
#ifdef ctBEHAV_FLUSH_NODE_MARKS
#define ct_nodflslst(a)  ctsnodflslst[a]  /* node flush list */
#define ct_filflslst(a)  ctsfilflslst[a]  /* file flush list */
#define ct_filflsbins(a) ctsfilflsbins[a] /* number of hash bins */
#define ct_filflsnent(a) ctsfilflsnent[a] /* current number of elements */
#endif
#ifdef ctFeatADDKY_DEFERD
#define skpaddhed(a)	sskpaddhed[a]
#define skpaddend(a)	sskpaddend[a]
#define skpkeyctx(a)	sskpkeyctx[a]
#endif

#endif /* ~ctCACHE_MEMORY */

EXTERN NINT	 ctpflg;	/* protected dump in play 		*/
EXTERN pTEXT	 ctlgbf;	/* transaction log buffer ptr		*/
#ifdef ctLOG_IDX
EXTERN ppCOMLST  cttrnanc;	/* vulnerable tran hash list anchor	*/
#endif
EXTERN CTFILE	 ctLfil;	/* log file header */
EXTERN CTFILE	 ctUfil;	/* log file header */
EXTERN pCTFILE	 ctLnum;
EXTERN pCTFILE	 ctUnum;
EXTERN CTFILE	 ctSfil[2];	/* start file headers */
EXTERN pCTFILE	 ctSnum;
EXTERN ULONG	 ct_lbfsiz;	/* log buffer size */
EXTERN NINT	 ctsflg;	/* ct_strip flag */
EXTERN NINT	 ctbflg;	/* BAKMOD flag */
EXTERN NINT	 ctdflg;	/* dynamic dump flag */
EXTERN NINT	 ctdflg_drt;	/* permit nonTRAN file dynamic dumps */
EXTERN NINT	 ct_actrns;	/* # active transactions */
#ifdef ctFeatDYNAMIC_DUMP
EXTERN NINT	 ctpdmp;	/* pre-image dynamic dump flag */
#endif
EXTERN NINT	 ct_chkflg;	/* checkpoint in progress flag */
EXTERN NINT	 ct_logkep;	/* archive log count */
EXTERN NINT	 ctskpfil;	/* skip missing files during recovery */
EXTERN NINT	 ctskpato;	/* skip missing files automatic for TRANDEP */
#ifdef ctFeatRCV_DETECT_INACCESSIBLE_FILES
EXTERN NINT	 ctskpiaf;	/* skip inaccessible files during recovery */
#endif
EXTERN NINT	 ctskpmir;	/* skip missing mirrors during recovery */
EXTERN NINT	 ctbadmir;	/* skip missing or bad log mirrors at startup */
EXTERN LONG	 ctfixlog;	/* non-zero means log size cannot increase */
EXTERN NINT	 ct_lerflg;	/* ctwrtlog error flag */
EXTERN SYSNO	 ct_lgn;	/* current file# in log */
#ifdef ctFeatTRANIDX_LOPN_ERR_CONTINUE
EXTERN NINT      tranidx96cont;	/* continue in case of tranidx LOPN_ERR */
#endif
#ifdef ctFeatDELSTK_COMMIT_SEC
EXTERN NINT      delstkcmtsec;	/* max. delay of deferred delete stack commit */
#endif
#endif

/* end of cttran_s.h */
