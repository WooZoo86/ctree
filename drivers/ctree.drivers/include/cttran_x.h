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
EXTERN LONG	 ctlogset;		/* default log set to use */
EXTERN LONG	 ctdmptim;		/* dynamic dump begin time */
EXTERN LONG	 ctdlgnum[ctMXLOGS];	/* beginning log during dump */
EXTERN LONG	 ctelgnum[ctMXLOGS];	/* ending log during dump */
EXTERN LONG	 ctdlgpos[ctMXLOGS];	/* position in ctdlgnum */
EXTERN LONG	 ctelgpos[ctMXLOGS];	/* position in ctelgnum */
EXTERN COUNT	 ctshdlfil;	/* shadow swap file # */

EXTERN LONG	 ctfwdlog[ctMXLOGS];	/* log for starting TRANFWD (ctrdmp) */
EXTERN LONG	 ctfwdpos[ctMXLOGS];	/* position for starting TRANFWD (ctrdmp) */
EXTERN LONG	 ctfwdpps[ctMXLOGS];	/* prev pos for starting TRANFWD (ctrdmp) */

#ifdef ctCACHE_MEMORY

typedef struct usrtrn {
	pSHADLST
		sh;	/* shadow tail	*/
	pSHADLST
		sv;	/* shadow savpt	*/
#ifdef ctRECBYTIDX
	pCOALST	cl;	/* coal list	*/
	NINT	cc;	/* coal current	*/
	NINT	ct;	/* coal total	*/
	NINT	cs;	/* coal status	*/
#endif
#ifdef ctFeatQUIET
	NINT	at;	/* active flag  */
#endif
#ifdef ctFeat6BT
	LONG	tr2;
	LONG	ix2;
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
	LONG	tl;	/* log status	*/
	LONG	ix;	/* index status	*/
	LONG	ty;	/* tran type	*/
	NINT	md;	/* tran mode	*/
	NINT	pt;	/* chkpt status	*/
	LONG	sm;	/* split marks	*/
	SEMA	ph;	/* semaphore	*/
	LONG	ls;	/* logset info	*/
#ifdef ctFeatADDKY_DEFERD
	pSHADLST
		ah;	/* ptr head skipped adds */
	pSHADLST
		ae;	/* ptr tail	         */
	pVOID	kc;	/* key context pointer	 */
#endif
#ifdef ctFeatIICT
	ppSHADLST
		ub;	/* hash bins for srchshd		*/
	HSHSTT	st;	/* preimage hash state structure	*/
	LONG	uv;	/* tran savepoint info			*/
	NINT	rf;	/* TRANRST() flag			*/
	NINT	ic;	/* IICT flag				*/
#endif
	NINT	uf;	/* recovery undo flg: undflg		*/
	} USRTRN;
typedef USRTRN ctMEM *	pUSRTRN;
typedef USRTRN ctMEM * ctMEM * ppUSRTRN;


EXTERN pTEXT	 ct_usrb;	/* base address for aligned memory	*/
EXTERN pUSRTRN	 ct_usr[MXU2];	/* user transaction structure		*/
#ifdef ctFeatIICT
EXTERN pTEXT	 ct_savb;	/* base address for aligned memory	*/
EXTERN pUSRTRN	 ct_sav[MXU2];  /* save transaction structure w/ IICT	*/
#endif

#define ct_usrsq(a)	ct_usr[a]->sq
#define ct_usrtr(a)	ct_usr[a]->tr
#ifdef ctFeatQUIET
#define ct_usrat(a)	ct_usr[a]->at
#endif
#ifdef ctFeat6BT
#define ct_usrtr2(a)	ct_usr[a]->tr2
#define ct_usrix2(a)	ct_usr[a]->ix2
#endif
#ifdef ctSUCTRAN
#define ct_usrbl(a)	ct_usr[a]->bl
#define ct_usrbp(a)	ct_usr[a]->bp
#define ct_usrel(a)	ct_usr[a]->el
#define ct_usrep(a)	ct_usr[a]->ep
#define ct_usrtv(a)	ct_usr[a]->tv
#define ct_usrtv2(a)	ct_usr[a]->tv2
#endif
#define ct_usrtl(a)	ct_usr[a]->tl
#define ct_usrix(a)	ct_usr[a]->ix
#define ct_usrsm(a)	ct_usr[a]->sm
#define ct_usrmd(a)	ct_usr[a]->md
#define ct_usrty(a)	ct_usr[a]->ty
#define ct_chkpt(a)	ct_usr[a]->pt
#define ct_usrsema(a)	ct_usr[a]->ph
#define ctlstshdm(a)	ct_usr[a]->sh
#define ctlstsavm(a)	ct_usr[a]->sv
#define ct_usrls(a)	ct_usr[a]->ls
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
#endif /* ctFeatIICT */

#else /* ~ctCACHE_MEMORY */

EXTERN LONG	 ctsusrtr[MXU2];/* active transaction # for user or zero*/
#ifdef ctFeatQUIET
EXTERN NINT	 ctsusrat[MXU2];/* active transaction flag		*/
#endif
EXTERN LONG	 ctsusrtl[MXU2];/* log file sequence number for BEGTRAN	*/
EXTERN LONG	 ctsusrix[MXU2];/* log file index op number		*/
#ifdef MULTITRD
EXTERN LONG	 ctsusrsm[MXU2];/* number of marks in split node process*/
EXTERN NINT	 ctsusrmd[MXU2];/* save transaction mode		*/
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
EXTERN pSEMA	 ctsusrsema;	/* commit/abort processing semaphore	*/
EXTERN LONG	 ctsusrty[MXU2];/* ctSHADOW / ctLOGFIL transaction type	*/
EXTERN NINT	 ctschkpt[MXU2];/* check point flag 			*/
EXTERN ppSHADLST ctlstshd;	/* linked list tail for pre-image list	*/
EXTERN ppSHADLST ctlstsav;	/* last save point pointer		*/
#ifdef ctRECBYTIDX
EXTERN pCOALST	 ctscoalst[MXU2];
EXTERN NINT	 ctscoalcr[MXU2];
EXTERN NINT	 ctscoaltt[MXU2];
EXTERN NINT	 ctscoalcs[MXU2];
#endif
#ifdef ctFeatADDKY_DEFERD
EXTERN ppSHADLST sskpaddhed[MXU2];
EXTERN ppSHADLST sskpaddend[MXU2];
EXTERN pVOID	 sskpkeyctx[MXU2];
#endif

#ifdef MULTITRD
#define ct_usrsq(a)	ctsusrsq[a]
#define ct_usrtr(a)	ctsusrtr[a]
#ifdef ctFeatQUIET
#define ct_usrat(a)	ctsusrat[a]
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
#define ct_usrsema(a)	ctsusrsema[a]
#endif /* MULTITRD */
#ifdef ctRECBYTIDX
#define ct_coalst(a)	ctscoalst[a]
#define ct_coalcr(a)	ctscoalcr[a]
#define ct_coaltt(a)	ctscoaltt[a]
#define ct_coalcs(a)	ctscoalcs[a]
#endif
#define ctlstshdm(a)	ctlstshd[a]
#define ctlstsavm(a)	ctlstsav[a]
#ifdef ctFeatADDKY_DEFERD
#define skpaddhed(a)	sskpaddhed[a]
#define skpaddend(a)	sskpaddend[a]
#define skpkeyctx(a)	sskpkeyctx[a]
#endif

#endif /* ~ctCACHE_MEMORY */

EXTERN NINT	 ctpflg;	/* protected dump in play 		*/
EXTERN CTFILE	 ctLfil[ctMXLOGS];	/* log file header */
EXTERN CTFILE	 ctUfil;	/* log file header */
EXTERN pCTFILE	 ctLnum[ctMXLOGS];
EXTERN pCTFILE	 ctUnum;
EXTERN CTFILE	 ctSfil[ctMXLOGS][2];	/* start file headers */
EXTERN pCTFILE	 ctSnum[ctMXLOGS];
EXTERN VRLEN	 ct_lbfsiz;	/* log buffer size */
EXTERN NINT	 ctsflg;	/* ct_strip flag */
EXTERN NINT	 ctbflg;	/* BAKMOD flag */
EXTERN NINT	 ctdflg;	/* dynamic dump flag */
#ifdef ctFeatDYNAMIC_DUMP
EXTERN NINT	 ctpdmp;	/* pre-image dynamic dump flag */
#endif
EXTERN NINT	 ct_logkep;	/* archive log count */
EXTERN NINT	 ctskpfil;	/* skip missing files during recovery */
EXTERN NINT	 ctskpato;	/* skip missing files automatic for TRANDEP */
#ifdef ctFeatRCV_DETECT_INACCESSIBLE_FILES
EXTERN NINT	 ctskpiaf;	/* skip inaccessible files during recovery */
#endif
EXTERN NINT	 ctskpmir;	/* skip missing mirrors during recovery */
EXTERN NINT	 ctbadmir;	/* skip missing or bad log mirrors at startup */
EXTERN LONG	 ctfixlog;	/* non-zero means log size cannot increase */
EXTERN COUNT	 ct_lgn;	/* current file# in log */
#endif

/* end of cttran_x.h */
