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

#ifndef CTFUNTH
#define CTFUNTH

#ifdef __cplusplus
extern "C" {
#endif

extern  LONG  tranupd(NINT updmod,NINT trnmod,LONG trnval,pVOID updinfo);
extern  NINT  read_temp_event_file(NINT sOWNR );
extern  NINT  adjlogtrn(NINT savprg pthHan);
extern  NINT  eorCLSTRAN(pCTFILE ctnum pthHan);
extern  pRPLIST memRestorePointList(pNINT retcod);
extern  NINT  addRestorePointList(pTRANDSC tp,pRPLIST,pTEXT dp,LONG rplog,LONG rppos pthHan);
extern  NINT  makeRestoreName(pTEXT buf,LONG log,LONG time,NINT chkpntflg);
extern  NINT  makeRestorePoint(pCTFILE stnum,pTEXT name,LONG time,LONG log,ULONG pos,LONG chklog,ULONG chkpos,NINT sOWNR);
extern  NINT  chkmogcac(pDATBUF db,NINT loc,NINT sOWNR);
extern  NINT  rcvopnlev(pCTFILE ctnum,NINT sOWNR);
extern  NINT  cttrandoDARWRD(NINT mode,NINT undoTRAN,pCTFILE ctnum,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT  ctlogDARWRD(pCTFILE ctnum,pDAR dar,pTEXT oldimg,NINT withOPNTRAN,NINT offset,NINT len pthHan);
extern  NINT  ctSaveAutoSTInfo(pCTFILE ctnum pthHan);
extern  VOID  ctRestoreAutoSTInfo(pSHADLST sl pthHan);
extern  VOID  ctFreeAutoSTInfo(pTEXT buf);
extern  NINT  fileAtrbCntlrqs(pCTFILE ctnum,NINT sOWNR);
extern  NINT  fileAtrbCntlclr(pCTFILE ctnum,NINT sOWNR);
extern  NINT  chkiictupd(pCTFILE ctnum,LONG hw,LONG recbyt,NINT hdrsiz,NINT ufil,NINT sOWNR);
extern  NINT  dmppreimgspc(pSHADLST sl,pTEXT msg,NINT sOWNR);
extern  pTEXT ctchktrandep_nam(pTEXT filnam,pNINT pos,ULONG tfil);
extern  NINT  ctchktrandep_pre(NINT mode,ULONG tfil);
extern  NINT  ctchktrandep_end(pTRANDSC pd);
#ifdef MULTITRD
extern  NINT  chkfilupd(pCTFILE ctnum,pFUSR fu,NINT sOWNR);
#endif
extern  NINT  usrfilupd(pCTFILE ctnum,NINT ownr);
extern  NINT  test_dfropntran(pCTFILE ctnum,NINT sOWNR);
extern  NINT  ctrcvDAR(pCTFILE ctnum,pTRANDSC tp,pTEXT bp,NINT redo,NINT updmod pthHan);
extern  NINT  cttrnDAR(pSHADLST sl,NINT commit pthHan);
extern  NINT  ctlogdst(pCTFILE ctnum,NINT opnmod pthHan);
extern  NINT  ctlogprtent(pCTFILE ctnum,NINT opnmod pthHan);
extern  NINT  ctlogprthst(pCTFILE ctnum,NINT opnmod pthHan);
extern  NINT  savp_collapse(pSHADLST sl,NINT spclflg pthHan);
extern  NINT  listdfrdkeys(pCTFILE knum,COUNT relkey,pTEXT idxval,pLhw LONG recbyt,NINT sOWNR);
extern  VOID  setdfrdkeyctx(pVOID keyctx);
extern  NINT  dodfrdkeys(ppVOID pkeyctx,pCOUNT prelkey,NINT mode);
extern  NINT  ct_mul_abandon(NINT thdid,NINT sOWNR);
extern  NINT  wrthdradj(pCTFILE ctnum pthHan);

#ifdef ctSSrel2
extern  NINT  clrredlzr(pCTFILE ctnum,NINT sOWNR);
#endif

#ifdef ctCMPLOG
extern  NINT  ctcmpexp(pTEXT dest,VRLEN destlen,pTEXT src,VRLEN srclen);
#ifdef ctFeatSNAPSHOT
extern  VRLEN ctcmplen(pTRANDSC ptran,ppTEXT pbufadr,pULONG cmpbyt,pNINT cmptyp pthHan);
#else
extern  VRLEN ctcmplen(pTRANDSC ptran,ppTEXT pbufadr pthHan);
#endif
extern  VRLEN cttrnlenx(pTRANDSC tp,pVRLEN pmlen);
extern  COUNT cttrnmemx(pTRANDSC tp,pCTFILE ctnum,VRLEN mlen,VRLEN vlen,pVRLEN pvspc,ppTEXT pbp,ULONG logpos pthHan);
extern  pTEXT ctcmpbuf(VRLEN len pthHan);
extern  COUNT lctiox(pTRANDSC ptran,pCTFILE ctnum,ULONG logpos,pTEXT tp,VRLEN mlen,VRLEN vlen pthHan pioN);
extern  COUNT cctiox(pTRANDSC ptran,pCTFILE ctnum,ULONG logpos,pTEXT tp,VRLEN mlen,NINT partial pthHan pioN);
#endif

extern  NINT  ctlogtflmap(pCTFILE dnum,pCTFILE knum,NINT mapmode pthHan);
extern  NINT  ctredoren1(pTRANDSC tp,pTEXT bp pthHan);
extern  NINT  ctexcp81(pTREBUF buffer,NINT elm,NINT adflag,pLhwt LONG tran);

#ifdef ctMXLOGS
extern  pCOMLST cttrnset81x(NINT logset,pLhwt LONG tranno);
extern  NINT  cttrnfnd81x(NINT logset,pLhwt LONG tranno,NINT yank,NINT sOWNR);
extern  NINT  kw_lscint(VOID );
extern  NINT  ctflogset(pCTFILE ctnum,pTEXT filnam);
extern	LONG  getlstpntx(NINT logset,NINT sOWNR,pLONG plstsuc);
extern  LONG  getlstpntredx(NINT logset,NINT sOWNR,LONG lognum);
extern  NINT  dlybegtran(NINT logset,NINT sOWNR);
extern  pTEXT ctlnamex(NINT logset,pTEXT lognam,LONG ln,NINT filetype);
extern  LONG  ctwrtlogx(NINT logset,pLONG ep,pTRANDSC tp,pVOID dp pthHan);
extern  VOID  ct_setlogerrx(NINT logset,NINT sOWNR);
extern  COUNT ctchkpntix(NINT lofset,NINT mode,LONG cmode);
extern  COUNT ctlogopnx(NINT logset,COUNT filno,pTEXT filnam,pCTFILE ctnum,NINT opnmod);

extern  NINT ct_chkfilx(pNINT plogset,pTEXT fn,pLONG idkey,NINT sOWNR);
extern  VOID cttrnclrx(NINT logset);
extern  NINT logtmemx(NINT logset,NINT loc,VRLEN memsiz pthHan);
extern  COUNT ctrcvopn81x(NINT logset,pTEXT filnam,ULONG tfil,pCTFILE ctnum,LONG tlen,pLhw LONG hp1,pLONG fid,ULONG logpos,NINT updmod,NINT scnopn,NINT loc);
extern  NINT ctqchkpx(UNLONG unlogset);
extern  VOID ctqchkpstopx(NINT logset);
extern  VOID ctchkpstatex(NINT logset);
extern  LONG ctupdlgx(NINT logset,NINT updmod,NINT trnmod,LONG trnval);
extern  NINT ct_inactlogx(NINT logset,LONG prglog,NINT reduce_flag pthHan);
extern  VOID ctstund81x(NINT logset,NINT mode,pLhwt LONG tranno,LONG lp,LONG ep);
#ifndef ctlogrqs
#ifdef ctDBGSEMCNT
extern  NINT ctlogrqsx(NINT logset,NINT own,NINT loc);
#else
extern  NINT ctlogrqsx(NINT logset,NINT own);
#endif
#endif

#else  /* ~ctMXLOGS */

extern  NINT  dlybegtran(NINT sOWNR);
extern  ULONG  getlstpnt(NINT sOWNR,pULONG plstsuc);
extern  NINT  getlogstate(NINT sOWNR,pLOGST plogstt);
extern  LONG  getlstpntred(NINT sOWNR,LONG lognum);

#endif /* ~ctMXLOGS */

extern void ctrcvSetFileClosedFlag(pCTFILE ctnum,NINT loc);

#ifdef MULTITRD
#ifndef ctlogclr
extern  NINT ctlogclr(pSEMAmut sema,NINT own,NINT dbgchk);
#endif
#ifndef ctlogrqs
#ifdef ctDBGSEMCNT
extern  NINT ctlogrqs(pSEMAmut sema,NINT own,NINT loc);
#else
extern  NINT ctlogrqs(pSEMAmut sema,NINT own);
#endif
#endif
#endif /* MULTITRD */

extern  VOID resetabtnod(pCTFILE knum pthHan);
extern  pTEXT gettenv(NINT sOWNR,pVRLEN plen);
extern  NINT ct_inactlog(LONG prglog,NINT reduce_flag pthHan);
extern  VOID cpytrnkey(pTEXT logkey,pTRANDSC tp);
extern  VOID cpytrnkey(pTEXT logkey,pTRANDSC tp);
extern  VOID cpykeynum(pPLhwt pLONG ptnum,pTEXT logkey);
extern  VOID cpynumkey(pTEXT logkey,pPLhwt pLONG ptnum);
extern  VOID cpytrnfil(pTEXT logkey,pULONG ptfil);
extern  NINT srchshdSP(pCTFILE ctnum,pTEXT bufadr,pLhw LONG recbyt,VRLEN slen,UINT shmode pthHan);
extern  NINT ctlogsnum(pCTFILE ctnum,LONG hsnum,LONG lsnum pthHan);
extern  NINT ctundoptmbr2(pCTFILE dnum,pVOID info,NINT locale pthHan);
extern  NINT ctifildrp(NINT tranmod,NINT sOWNR);
extern  NINT logtmem(NINT loc,VRLEN memsiz pthHan);
extern  VOID terr_abtexc(NINT err_no,NINT sOWNR,pLhw LONG node1,pCTFILE knum,pTEXT idxval);
extern  NINT ctundodrp2(pTEXT tp,NINT internal,NINT undflg pthHan);
extern  NINT ctlogdropidx(pCTFILE knum,pCTFILE dnum,NINT idxno,NINT nmem,NINT keyno pthHan);
extern  NINT quecoal(pCTFILE vnum,pRQMSG pr);
extern  NINT chkcoal81(pCTFILE ctnum,pTEXT recbuf,pLhw LONG lw,NINT sOWNR);
extern  NINT trycoal(NINT sOWNR);
#ifdef ctMULTIOPN
extern  NINT cttrnultbl81(pRhw ctRECPT pntr,pCTFILE ctnum,NINT sOWNR,NINT lokmod,NINT trnmod,NINT idatno);
#else
extern  NINT cttrnultbl81(pRhw ctRECPT pntr,pCTFILE ctnum,NINT sOWNR,NINT lokmod,NINT trnmod);
#endif
extern  NINT ctTranLockOut(NINT starting);
extern  NINT ct_dirtystart(NINT mode);
extern  NINT ctsetaux(pCTFILE ctnum,pTRANDSC tp,pSHADLST sl pthHan);
extern  NINT ctredores1seg(pCTFILE ctnum,pTRANDSC tp,pTEXT bp pthHan);
extern  COUNT ctrcvopn81(pTEXT filnam,ULONG tfil,pCTFILE ctnum,LONG tlen,pLhw LONG hp1,pLONG fid,ULONG logpos,NINT updmod,NINT scnopn,NINT loc,NINT unqloc);
extern  ULONG getfileid(pCTFILE Lnum,NINT incflg pthHan);
extern  COUNT ctssopn(COUNT datno,NINT sOWNR);
extern  COUNT ctaglok(COUNT datno,NINT sOWNR);
#ifdef MULTITRD
extern  NINT  hasredlok(pFUSR fu);
#endif
extern  NINT pflgchk(FILNO filno,pCTFILE hnum,NINT mode,NINT loc,NINT sOWNR);
#ifdef ctDBGanl
extern  NINT ctanlchk(pCTFILE ctnum);
extern  NINT ctanllog(NINT dbgmode,pCTFILE knum,pLhw pVOID xp,NINT locale,NINT mode,NINT num pthHan);
extern  NINT ctanlbuf(NINT mode,pTREBUF buf pthHan);
#endif
extern  pSHADLST ctshash81(NINT ownr,SYSNO filno,pLhw LONG recbyt,pNINT panc,ppSHADLST pphl,UINT shf);
extern  NINT tststrfil(pCTFILE ctnum,NINT err);
extern  NINT ctarcnam(pTEXT ap,pTEXT np,TEXT a,pTEXT mp,NINT mflag);
#ifdef ctHUGEFILE
extern  NINT chkbldskplststt(pREVDEL pr,NINT mode);
extern  NINT iupdhost(pCTFILE spnum,pCTFILE lgnum,LONG hp2,LONG hp1 pthHan);
extern  NINT ctxdotrandep(NINT ops,NINT cmt,pTRANDSC tp);
extern  NINT ctcmttrandep(pLONG pflrdo,pLONG pfludo);
extern  NINT ctbldtrandep81(NINT ops,pLhwt LONG tranno,LONG cretrn,ULONG tfil,pTEXT fn);
extern  pTEXT ctchktrandep(NINT mode,ULONG tfil,LONG cretrn,pTEXT fn,pLONG fid);
extern  LONG ctrentrandep(NINT updmod pthHan);
extern  VOID ctclntrandep(VOID );
extern  VOID resetTRANDEPdel(NINT sOWNR);
extern  NINT ctfnshdel2(pSHADLST sl,NINT sOWNR,NINT supflg);
extern  VOID ctfnshdel3(NINT sOWNR);
extern  NINT ctfnshdrp2(pSHADLST sl,NINT sOWNR);
extern  VOID setchnacs(pCTFILE ctnum,UINT state pthHan);
extern  NINT ctredocre1(NINT updmod,pTRANDSC tp,ppTEXT tbp pthHan);
extern  NINT ctredodel1(NINT updmod,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT ctundocre1(NINT trntyp,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT ctundocre2(pSHADLST sl,pCTFILE ctnum,NINT internal pthHan);
extern  NINT ctundodel1(NINT updmod,NINT trntyp,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT ctundodel2(pSHADLST sl,pCTFILE ctnum,pTEXT tp,NINT internal,LONG tpos2 pthHan);
extern  NINT ctundoren1(NINT updmod,NINT trntyp,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT ctundoren2(pSHADLST sl,pCTFILE ctnum,pTEXT tp,NINT internal,LONG tpos2 pthHan);
extern  NINT ctundoren3(NINT updmod,LONG hp2,LONG hp1,ULONG tfil,pLONG fid,pTEXT op,pTEXT np pthHan);
extern  NINT ctundoprm2(UINT ilen,pTEXT tp pthHan);
extern  NINT ctlogdep(NINT opcode,pCTFILE ctnum,pCTFILE hnum,pTEXT fn,FILNO irvmap pthHan);
extern  NINT ctrlcsegmdef(pCTFILE ctnum,NINT newmax);
extern  NINT ctlogsegmopn(pCTFILE ctnum pthHan);
extern  NINT ctchksegmdef(pCTFILE ctnum,pSEGCHK segdat,pTEXT segptr,NINT nxtflg pthHan);
extern  NINT ctrcvsegmdef(pTRANDSC tp,pTEXT bp,NINT scnflg pthHan);
extern  NINT ctdelseg(pCTFILE ctnum,NINT sOWNR);
extern  NINT ctredocre1seg(pCTFILE ctnum,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT ctundocre1seg(NINT trntyp,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT ctundocre2seg(pSHADLST sl,pCTFILE ctnum,pTEXT bp pthHan);
extern  NINT ctredodel1seg(pCTFILE ctnum,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT ctundodel1seg(NINT updmod,NINT trntyp,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT ctundodel2seg(pSHADLST sl,pCTFILE ctnum,pTEXT tp pthHan);
extern  NINT ctfnshdel2seg(pSHADLST sl,NINT sOWNR,NINT supflg);
extern  NINT ctundores1seg(NINT updmod,pCTFILE ctnum,pTRANDSC tp,pTEXT bp pthHan);
extern  NINT ctundores2seg(pSHADLST sl,pCTFILE ctnum,pTEXT tp pthHan);
#endif
extern  VOID setdmpflg(pCTFILE ctnum);
extern  VOID clrdmpflg(pCTFILE hnum);
extern  VOID ct_setlogerr(NINT sOWNR);
#ifdef ctCAMO
extern  NINT ctlogcamo(pCTFILE ctnum,NINT stage);
extern  NINT ctrcvcamo(pTRANDSC tp,pTEXT bp);
#endif /* ctCAMO */
#ifdef CTHISTORY
extern  void ctfreehlst(ppHSTLST bp);
#endif
extern  NINT ctfmatch(pCTFILE hnum,pLONG fid);
#ifdef dbgHGHTRN
extern  NINT dbghghtrn(LONG tran,pTEXT locale,pCTFILE knum);
#endif
#ifdef MULTITRD
extern  NINT cttr_rmv(NINT sOWNR);
extern  NINT cttr_set81(NINT sOWNR,pLhwt LONG tranno);
extern  NINT ctsetiso(pCTFILE dnum,pFUSR fu,NINT sOWNR);
extern  NINT ctsetisodb(COUNT datno);
extern  VOID ctchkpstate(VOID );
#else
extern  VOID ctfreelp(VOID );
extern  NINT ctrt_getcwd(pTEXT cwd,NINT maxlen);
#endif
extern  LONG ctgettrn81(pPLhwt NINT log,NINT sOWNR);
#ifdef ctLOG_IDX
extern  NINT cttrnindx81(pTREBUF buf,pTEXT kp,pLhw LONG node,NINT mode);
extern  pCOMLST cttrnset81(pLhwt LONG tranno);
extern  NINT cttrnfnd81(pLhwt LONG tranno,NINT yank,NINT sOWNR);
extern  VOID cttrnclr(VOID );
#endif
extern  COUNT lctio(pCTFILE ctnum,ULONG logpos,pTEXT tp,VRLEN vlen pioN);
#ifdef ctMIRROR
extern  NINT ctmirlst(pCTFILE ctnum,NINT mirswt);
#endif

#ifdef ctMXLOGS
extern  NINT ctmaklogtmpx(NINT logset,LONG src,LONG dst,NINT my_template);
extern  NINT ctqchkpx(UNLONG unlogset);
extern  VOID ctqchkpstopx(NINT logset);
#else
extern  NINT ctmaklogtmp(LONG src,LONG dst,NINT my_template);
extern  NINT ctqchkp(pTEXT sp);
extern  NINT ctqchkpstop(VOID);
#endif

extern  VOID cttrnfre(VOID);
extern  COUNT clnleaf(SYSNO filno,NINT mode);
extern  VOID ctinvshd(pSHADLST sl pthHan);
extern  UCOUNT ctsumlog(pTRANDSC tp);
extern  NINT ctsumchk(pCTFILE ctnum,VRLEN vlen,ULONG logpos,pTRANDSC tp pthHan);
extern  NINT cthdrword(SYSNO filno,pTEXT buf,NINT len,NINT newone);
extern  COUNT ctlogpidx(pCTFILE knum,COUNT memb,pUTEXT pvbyte);
extern  COUNT ctlogiidx81(pCTFILE dnum,NINT keyno,NINT idxno,pIFIL ifilptr HWt(pXCREblk) HWv(pxcreblk));
extern  COUNT ctloghwrd(pCTFILE knum,pTEXT oldwrd,pTEXT newwrd,COUNT offset,NINT len);
extern  pTEXT ctgetshd(pVOID bufadr,pSHADLST sl,VRLEN iosize pthHan);
extern  COUNT ctputshd(pSHADLST sl,pTEXT bufadr,VRLEN iosize,pTEXT bufadr2,VRLEN iosize2 pthHan);
extern  VOID ctfreshd(pSHADLST sl pthHan);
extern  VOID ctputtenv(NINT sOWNR,pTEXT envbuf,VRLEN len);
extern  NINT ctmrkact81(NINT cln_mode,pLhwt LONG mtran,pTREBUF buffer pthHan);
extern  NINT ctintlog(pCTFILE ctnum);
extern  ULONG ctprvlog(pCTFILE ctnum,NINT op_code);
extern  NINT ctautotran(NINT sOWNR,LONG updmod,pCTFILE ctnum);
extern  NINT ctautotranlow(NINT sOWNR,pCTFILE ctnum,NINT keeplock);
extern  NINT ctstrtran(UCOUNT flmode);
extern  NINT ctendtran(NINT serr);
extern  NINT ctstrsavp(pCTFILE ctnum);
extern  NINT ictstrsavp(UCOUNT flmode);
extern  NINT ctendsavp(NINT tranflag,NINT serr);
extern  pTEXT ctlname(pTEXT lognam,LONG ln,NINT filetype);
#ifndef comparu
extern  VRLEN comparu(pTEXT np,pTEXT op,VRLEN remlen);
#endif
extern  SYSNO ctlgtorc(ULONG tfil,NINT must_exist,pLONG pmbrflg);
extern  void ctstund81(NINT mode,pLhwt LONG tranno,ULONG lp,LONG lognum);
extern  NINT ctputimg81(NINT testtyp,NINT typimage,SYSNO tranfil,pLhw LONG tranpos,pTEXT bp,VRLEN vlen);
extern  VRLEN ctdiff(pTEXT np,VRLEN nl,pTEXT op,VRLEN ol,ppTEXT dp,pVRLEN dspc,VRLEN hdrlen pthHan);
extern  VOID cttranbf(pTREBUF buf,LONG old,LONG newone);
#ifdef ctBEHAV_USRSEMA
extern  NINT ctacttrn81(pLhwt LONG tran_no,pNINT povrflag,NINT cln_mode pthHan);
#else
extern  COUNT ctacttrn81(pLhwt LONG tran_no,pNINT povrflag pthHan);
#endif
extern  COUNT cttrnalc(COUNT nusers);
extern  VRLEN cttrnlen(pTRANDSC tp);
extern  COUNT prtlog(pULONG plogpos,COUNT mode,pLONG plogser,COUNT tt,LONG fpos,LONG tn,pULONG ptf);
extern  COUNT srchshd81(pVOID phs,NINT ownr,pLhw LONG recbyt,pCTFILE ctnum,VRLEN iosize,pVOID bufadr,ppSHADLST psl,NINT mode,ppSHADLST lsl,pVRLEN pread,NINT ctioatrb);
extern  NINT updtshd81z(NINT ownr,pLhw LONG recbyt,pCTFILE ctnum,VRLEN iosize,pVOID bufadr,NINT mode,VRLEN torigin,NINT ctioatrb pthHan);
extern  NINT updtshd81x(NINT ownr,pLhw LONG recbyt,pCTFILE ctnum,VRLEN iosize,pVOID bufadr,NINT mode,VRLEN torigin pthHan);
extern  NINT updtshd81(NINT ownr,pLhw LONG recbyt,pCTFILE ctnum,VRLEN iosize,pVOID bufadr,NINT mode pthHan);
extern  NINT testshd(COUNT loc);
extern  NINT prtshd(COUNT own);
extern  LONG ctupdlg(NINT updmod,NINT trnmod,LONG trnval,pVOID updinfo);
extern  VOID fusrclr(COUNT mode,NINT sOWNR);
extern  ULONG ctwrtlog(pLONG ep,pTRANDSC tp,pVOID dp pthHan);
#ifdef ctPortVINESLOG
extern  NINT dbuglog(LONG pos,COUNT fil,pTEXT tp,UCOUNT class);
#endif
extern  COUNT ctputhdr(pCTFILE ctnum);
extern  COUNT ctlogext81(NINT sOWNR,pLhw LONG pntr,pCTFILE ctnum,pVOID tp,NINT len,NINT mode);
extern  COUNT ctlogcmp(pCTFILE ctnum,pCTFILE mtnum,pTEXT hdrbuf);
extern  COUNT ctwrtcmp(pCTFILE ctnum,pCTFILE mtnum,pTEXT hdrbuf);
extern  VOID ctlgqnod81(NINT ownr,pCTFILE knum,pLhw LONG node);
extern  COUNT ctlogkey81(COUNT mode,pCTFILE knum,pTEXT target,pRhw LONG recbyt);
extern  COUNT ctlogopn(SYSNO filno,pTEXT filnam,pCTFILE ctnum,NINT opnmod);
extern  LONG ctlogcmprec(pCTFILE dnum,pTRANDSC ptran,NINT opnmod pthHan);
extern  LONG ctlogflexrec(pCTFILE dnum,pTRANDSC ptran,NINT opnmod pthHan);
extern  COUNT ctcreinfo(pTEXT filnam,pCTFILE ctnum);
extern  COUNT ctchkpnti(NINT mode,LONG cmode);
extern COUNT ctlogcfil(NINT,FILNO);

extern  NINT ctNINTlog(pCTFILE ctnum);
extern  NINT ctflslog(pCTFILE ctnum,NINT trntyp,NINT sOWNR);
extern  COUNT tranovr(pPLhwt pLONG plwt,NINT mode,COUNT lokmod);
extern  NINT ctlgfile81(NINT op_code,pCTFILE ctnum,pLhwt LONG begtrn,ULONG beglen,LONG logser,pULONG chkpos);
extern  COUNT ctstrfil(VOID );
extern  COUNT cttrnmem(pCTFILE ctnum,VRLEN vlen,pVRLEN pvspc,ppTEXT pbp,ULONG logpos pthHan);
extern  NINT ctlgswitch(pCTFILE ctnum,NINT op_code,LONG chgser);
extern  LONG TRANBAK(COUNT trnmod,LONG trnval);
extern  LONG TRANFWD(COUNT trnmod,LONG prvpos);

/*******************************/
#ifdef ctPortSOFTWAREAG_LEGACY
#ifdef ctPortSMARTS
/* ctclb2.c */
extern NINT	ctrt_exit(NINT);
extern VOID 	clsksglst(pNINT, pNINT, ppKSEGLST);

/* ctclb3.c */
extern NINT	ctabnusr(NINT);

/* ctdelk.c */
extern NINT	iTRANABT(void);

/* ctifil.c */
extern NINT 	chkseglst(pCTFILE, NINT, COUNT pthHan);

/* ctiidx.c */
extern NINT 	ctchkunqidx(pXCREblk, pIFIL, pIIDX, pNINT, NINT, NINT);

/* ctocfl.c */
extern NINT 	iTRANABT(void);
extern VOID     clsksglst(pNINT, pNINT, ppKSEGLST);

/* ctrcvr.c */
extern NINT 	ctredores1seg(pCTFILE, pTRANDSC, pTEXT pthHan);

/* cttran.c */
extern NINT 	ctfnshdrp2(pSHADLST, NINT);

#endif /* ctPortSMARTS */
#endif /* ctPortSOFTWAREAG_LEGACY */
/*******************************/

extern NINT     ctrsthdrstate(pSHADLST sl pthHan);
extern NINT     ctrsthdrfnsh(pSHADLST sl,NINT sOWNR);
extern NINT     ctshdcpy(pSHADLST sl, NINT mode pthHan);
extern VOID     rmvdfrdkey(pSHADLST sl pthHan);
#ifdef MULTITRD
extern NINT     ctfnshcre(pFUSR fu,pCTFILE ctnum pthHan);
#endif

#ifdef __cplusplus
}
#endif

#endif /* CTFUNTH */
