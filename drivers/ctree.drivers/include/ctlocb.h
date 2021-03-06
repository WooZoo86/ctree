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

#ifndef ctLOCBH
#define ctLOCBH
#define ctLOCBHint

/*
** change API names to a local variety: e.g., ADDKEY -> fp_ADDKEY
**
** ctFPprefix default definition in ctopt2.h
*/

/* NOTE: add new definitions to ctsepl.h */
#include "ctsepl.h"
#define ctFILELIST		xppf(ctFPprefix,ctFILELIST)
#define ctReplSetPosByTransactionId xppf(ctFPprefix,ctReplSetPosByTransactionId)
#define ctSetTransactionId	xppf(ctFPprefix,ctSetTransactionId)
#define GetFileRegions		xppf(ctFPprefix,GetFileRegions)
#define addAutoSysTimeFields	xppf(ctFPprefix,addAutoSysTimeFields)
#define RemoveAutoSysTimeFields xppf(ctFPprefix,RemoveAutoSysTimeFields)
#define WhichAutoSysTimeFields	xppf(ctFPprefix,WhichAutoSysTimeFields)
#define UpdateAutoSysTimeFields xppf(ctFPprefix,UpdateAutoSysTimeFields)
#define ctSyncReplControl	xppf(ctFPprefix,ctSyncReplControl)
#define USERINFOX		xppf(ctFPprefix,USERINFOX)
#define UpdateRecordOffsetForKey xppf(ctFPprefix,UpdateRecordOffsetForKey)
#define ctGetConnectionInfo	xppf(ctFPprefix,ctGetConnectionInfo)
#define ctGetAccountExpirationTime xppf(ctFPprefix,ctGetAccountExpirationTime)
#define ctAlterSchema		xppf(ctFPprefix,ctAlterSchema)
#define ctFullText		xppf(ctFPprefix,ctFullText)
#define AllocFTSearch		xppf(ctFPprefix,AllocFTSearch)
#define FreeFTSearch		xppf(ctFPprefix,FreeFTSearch)
#define FirstInFT		xppf(ctFPprefix,FirstInFT)
#define LastInFT		xppf(ctFPprefix,LastInFT)
#define NextInFT		xppf(ctFPprefix,NextInFT)
#define PrevInFT		xppf(ctFPprefix,PrevInFT)
#define ctDeferredIndexControl	xppf(ctFPprefix,ctDeferredIndexControl)
#define ctRecordUpdateCallbackControl	xppf(ctFPprefix,ctRecordUpdateCallbackControl)
#define ctCopyFile		xppf(ctFPprefix,ctCopyFile)
#define ctSETCOMPRESS		xppf(ctFPprefix,ctSETCOMPRESS)
#define ctMEMSTAT		xppf(ctFPprefix,ctMEMSTAT)
#define SetXtdFileOpenMode	xppf(ctFPprefix,SetXtdFileOpenMode)
#define addIDfield		xppf(ctFPprefix,addIDfield)
#define delIDfield		xppf(ctFPprefix,delIDfield)
#define getIDfield		xppf(ctFPprefix,getIDfield)
#define resetIDfield		xppf(ctFPprefix,resetIDfield)
#define xtdatrIDfield		xppf(ctFPprefix,xtdatrIDfield)
#define wchIDfield		xppf(ctFPprefix,wchIDfield)
#define ctVERIFYidx		xppf(ctFPprefix,ctVERIFYidx)
#define ctVerifyFile		xppf(ctFPprefix,ctVerifyFile)
#define ctReplMasterControl	xppf(ctFPprefix,ctReplMasterControl)
#define ctCreateSequence	xppf(ctFPprefix,ctCreateSequence)
#define ctDeleteSequence	xppf(ctFPprefix,ctDeleteSequence)
#define ctOpenSequence		xppf(ctFPprefix,ctOpenSequence)
#define ctCloseSequence		xppf(ctFPprefix,ctCloseSequence)
#define ctGetSequenceAttrs	xppf(ctFPprefix,ctGetSequenceAttrs)
#define ctSetSequenceAttrs	xppf(ctFPprefix,ctSetSequenceAttrs)
#define ctGetCurrentSequenceValue xppf(ctFPprefix,ctGetCurrentSequenceValue)
#define ctSetCurrentSequenceValue xppf(ctFPprefix,ctSetCurrentSequenceValue)
#define ctGetNextSequenceValue	xppf(ctFPprefix,ctGetNextSequenceValue)
#define ctReplLogFileResync	xppf(ctFPprefix,ctReplLogFileResync)
#define ctTempDir		xppf(ctFPprefix,ctTempDir)
#define ctTransferFile		xppf(ctFPprefix,ctTransferFile)
#define ctLOKDYN		xppf(ctFPprefix,ctLOKDYN)
#define ctSETCFG		xppf(ctFPprefix,ctSETCFG)
#define ctSETSEG		xppf(ctFPprefix,ctSETSEG)
#define OPNIFILX		xppf(ctFPprefix,OPNIFILX)
#define PUTIFILX8		xppf(ctFPprefix,PUTIFILX8)
#define PUTIFILX		xppf(ctFPprefix,PUTIFILX)
#define RBLIFILX8		xppf(ctFPprefix,RBLIFILX8)
#define RBLIFILX		xppf(ctFPprefix,RBLIFILX)
#define CMPIFILX8		xppf(ctFPprefix,CMPIFILX8)
#define CMPIFILX		xppf(ctFPprefix,CMPIFILX)
#define RENIFILX		xppf(ctFPprefix,RENIFILX)
#define EXPIFILX		xppf(ctFPprefix,EXPIFILX)
#define CREIFILX8		xppf(ctFPprefix,CREIFILX8)
#define CREIFILX		xppf(ctFPprefix,CREIFILX)
#define PRMIIDX8		xppf(ctFPprefix,PRMIIDX8)
#define PRMIIDX			xppf(ctFPprefix,PRMIIDX)
#define RBLIIDX			xppf(ctFPprefix,RBLIIDX)
#define TMPIIDXX8		xppf(ctFPprefix,TMPIIDXX8)
#define TMPIIDXX		xppf(ctFPprefix,TMPIIDXX)
#define TMPIIDX			xppf(ctFPprefix,TMPIIDX)
#define reset_cur		xppf(ctFPprefix,reset_cur)
#define GETMNAME		xppf(ctFPprefix,GETMNAME)
#define GETNAM			xppf(ctFPprefix,GETNAM)
#define SECURITY		xppf(ctFPprefix,SECURITY)
#define GETFIL			xppf(ctFPprefix,GETFIL)
#define GETFILX			xppf(ctFPprefix,GETFILX)
#define PUTCRES			xppf(ctFPprefix,PUTCRES)
#define GETCRES			xppf(ctFPprefix,GETCRES)
#define GETCIDX			xppf(ctFPprefix,GETCIDX)
#define UPDCIDX			xppf(ctFPprefix,UPDCIDX)
#define OPNICON			xppf(ctFPprefix,OPNICON)
#define CHGICON			xppf(ctFPprefix,CHGICON)
#define CLSICON			xppf(ctFPprefix,CLSICON)
#define PUTFIL			xppf(ctFPprefix,PUTFIL)
#define PUTHDR			xppf(ctFPprefix,PUTHDR)
#define ADDKEY			xppf(ctFPprefix,ADDKEY)
#define PTADMIN			xppf(ctFPprefix,PTADMIN)
#define GETCURP			xppf(ctFPprefix,GETCURP)
#define GETCURK			xppf(ctFPprefix,GETCURK)
#define GETCURKL		xppf(ctFPprefix,GETCURKL)
#define NEWREC			xppf(ctFPprefix,NEWREC)
#define RETREC			xppf(ctFPprefix,RETREC)
#define REDIREC			xppf(ctFPprefix,REDIREC)
#define REDREC			xppf(ctFPprefix,REDREC)
#define WRTREC			xppf(ctFPprefix,WRTREC)
#define DATENT			xppf(ctFPprefix,DATENT)
#define LOKREC			xppf(ctFPprefix,LOKREC)
#define ctLOKTIMOUT		xppf(ctFPprefix,ctLOKTIMOUT)
#define ctLOKLST		xppf(ctFPprefix,ctLOKLST)
#define DELFIL			xppf(ctFPprefix,DELFIL)
#define ctDROPIDX		xppf(ctFPprefix,ctDROPIDX)
#define DELCHK			xppf(ctFPprefix,DELCHK)
#define DELBLD			xppf(ctFPprefix,DELBLD)
#define ESTKEY			xppf(ctFPprefix,ESTKEY)
#define RNGENT			xppf(ctFPprefix,RNGENT)
#define FRCKEY			xppf(ctFPprefix,FRCKEY)
#define PUTDODAX		xppf(ctFPprefix,PUTDODAX)
#define PUTDODA			xppf(ctFPprefix,PUTDODA)
#define CLISAM			xppf(ctFPprefix,CLISAM)
#define SERIALNUM		xppf(ctFPprefix,SERIALNUM)
#define STPUSR			xppf(ctFPprefix,STPUSR)
#define STPUSRA			xppf(ctFPprefix,STPUSRA)
#define cttestfunc		xppf(ctFPprefix,cttestfunc)
#ifdef ctFeatMAXFILE32
#undef INTREEX
#define INTREEX4		xppf(ctFPprefix,INTREEX4)
#define INTREEX INTREEX4
#else
#define INTREEX			xppf(ctFPprefix,INTREEX)
#endif
#define OPNRFILX		xppf(ctFPprefix,OPNRFILX)
#define OPNFILX			xppf(ctFPprefix,OPNFILX)
#define CLSFIL			xppf(ctFPprefix,CLSFIL)
#define LKISAM			xppf(ctFPprefix,LKISAM)
#define ADDREC			xppf(ctFPprefix,ADDREC)
#define RWTREC			xppf(ctFPprefix,RWTREC)
#define DELREC			xppf(ctFPprefix,DELREC)
#define TESTHUGE		xppf(ctFPprefix,TESTHUGE)
#define CLRFIL			xppf(ctFPprefix,CLRFIL)
#define DELRFIL			xppf(ctFPprefix,DELRFIL)
#define EQLREC			xppf(ctFPprefix,EQLREC)
#define GTEREC			xppf(ctFPprefix,GTEREC)
#define GTREC			xppf(ctFPprefix,GTREC)
#define LTEREC			xppf(ctFPprefix,LTEREC)
#define LTREC			xppf(ctFPprefix,LTREC)
#define NXTREC			xppf(ctFPprefix,NXTREC)
#define PRVREC			xppf(ctFPprefix,PRVREC)
#define FRSREC			xppf(ctFPprefix,FRSREC)
#define LSTREC			xppf(ctFPprefix,LSTREC)
#define RRDREC			xppf(ctFPprefix,RRDREC)
#define UPDCURI			xppf(ctFPprefix,UPDCURI)
#define SETCBRBL		xppf(ctFPprefix,SETCBRBL)
#define GETCBRBLST		xppf(ctFPprefix,GETCBRBLST)
#define SETCURI			xppf(ctFPprefix,SETCURI)
#ifdef ctFeatMAXFILE32
#undef OPNISAMX
#define OPNISAMX4		xppf(ctFPprefix,OPNISAMX4)
#define OPNISAMX OPNISAMX4
#undef CREISAMX
#define CREISAMX4		xppf(ctFPprefix,CREISAMX4)
#define CREISAMX CREISAMX4
#else
#define CREISAMX		xppf(ctFPprefix,CREISAMX)
#define OPNISAMX		xppf(ctFPprefix,OPNISAMX)
#endif
#define CREDATX8		xppf(ctFPprefix,CREDATX8)
#define CREDATX			xppf(ctFPprefix,CREDATX)
#define CREIDXX8		xppf(ctFPprefix,CREIDXX8)
#define CREIDXX			xppf(ctFPprefix,CREIDXX)
#define CREMEM			xppf(ctFPprefix,CREMEM)
#define IDXENT			xppf(ctFPprefix,IDXENT)
#define ctDISTINCTest		xppf(ctFPprefix,ctDISTINCTest)
#define ctDISTINCTset		xppf(ctFPprefix,ctDISTINCTset)
#define ctDISTINCTestXtd	xppf(ctFPprefix,ctDISTINCTestXtd)
#define ctDISTINCTsetXtd	xppf(ctFPprefix,ctDISTINCTsetXtd)
#define ctImpersonateTask	xppf(ctFPprefix,ctImpersonateTask)
#define LOADKEY			xppf(ctFPprefix,LOADKEY)
#define EQLKEY			xppf(ctFPprefix,EQLKEY)
#define GTEKEY			xppf(ctFPprefix,GTEKEY)
#define FRSKEY			xppf(ctFPprefix,FRSKEY)
#define LSTKEY			xppf(ctFPprefix,LSTKEY)
#define NXTKEY			xppf(ctFPprefix,NXTKEY)
#define PRVKEY			xppf(ctFPprefix,PRVKEY)
#define GTKEY			xppf(ctFPprefix,GTKEY)
#define LTKEY			xppf(ctFPprefix,LTKEY)
#define LTEKEY			xppf(ctFPprefix,LTEKEY)
#define ALCSET			xppf(ctFPprefix,ALCSET)
#define FRESET			xppf(ctFPprefix,FRESET)
#define FRESETN			xppf(ctFPprefix,FRESETN)
#define CHGSET			xppf(ctFPprefix,CHGSET)
#define ALCBAT			xppf(ctFPprefix,ALCBAT)
#define FREBAT			xppf(ctFPprefix,FREBAT)
#define FREBATN			xppf(ctFPprefix,FREBATN)
#define CHGBAT			xppf(ctFPprefix,CHGBAT)
#define FREHST			xppf(ctFPprefix,FREHST)
#define FREHSTN			xppf(ctFPprefix,FREHSTN)
#define CHGHST			xppf(ctFPprefix,CHGHST)
#define BATSET			xppf(ctFPprefix,BATSET)
#define BATSETX			xppf(ctFPprefix,BATSETX)
#define PERFORM			xppf(ctFPprefix,PERFORM)
#define USERLIST		xppf(ctFPprefix,USERLIST)
#define USERINFO		xppf(ctFPprefix,USERINFO)
#define ctklusr			xppf(ctFPprefix,ctklusr)
#define ctRENFIL		xppf(ctFPprefix,ctRENFIL)
#define SETFLTR			xppf(ctFPprefix,SETFLTR)
#define SETFLTRN		xppf(ctFPprefix,SETFLTRN)
#define RESETFLTR		xppf(ctFPprefix,RESETFLTR)
#define SETNODE			xppf(ctFPprefix,SETNODE)
#define ctLOKDMP		xppf(ctFPprefix,ctLOKDMP)
#define CTUSER			xppf(ctFPprefix,CTUSER)
#define CTUSERX			xppf(ctFPprefix,CTUSERX)
#define CTSQLCTL		xppf(ctFPprefix,CTSQLCTL)
#define CTSRVCTL		xppf(ctFPprefix,CTSRVCTL)
#define CT_USER			xppf(ctFPprefix,CT_USER)
#define CT_USERX		xppf(ctFPprefix,CT_USERX)
#define CT_SQLCTL		xppf(ctFPprefix,CT_SQLCTL)
#define CT_SRVCTL		xppf(ctFPprefix,CT_SRVCTL)
#define SETOPS			xppf(ctFPprefix,SETOPS)
#define FRSSET			xppf(ctFPprefix,FRSSET)
#define MIDSET			xppf(ctFPprefix,MIDSET)
#define LSTSET			xppf(ctFPprefix,LSTSET)
#define NXTSET			xppf(ctFPprefix,NXTSET)
#define PRVSET			xppf(ctFPprefix,PRVSET)
#define SETALTSEQ		xppf(ctFPprefix,SETALTSEQ)
#define SETVARBYTS		xppf(ctFPprefix,SETVARBYTS)
#define GETALTSEQ		xppf(ctFPprefix,GETALTSEQ)
#define SETDEFBLKX		xppf(ctFPprefix,SETDEFBLKX)
#define SETDEFBLK		xppf(ctFPprefix,SETDEFBLK)
#define GTVLEN			xppf(ctFPprefix,GTVLEN)
#define GETIFILX		xppf(ctFPprefix,GETIFILX)
#define GETIFIL			xppf(ctFPprefix,GETIFIL)
#define GETDODAX		xppf(ctFPprefix,GETDODAX)
#define NEWVREC			xppf(ctFPprefix,NEWVREC)
#define TSTVREC			xppf(ctFPprefix,TSTVREC)
#define RETVREC			xppf(ctFPprefix,RETVREC)
#define GETRES			xppf(ctFPprefix,GETRES)
#define ctdidx			xppf(ctFPprefix,ctdidx)
#define ADDRES			xppf(ctFPprefix,ADDRES)
#define UPDRES			xppf(ctFPprefix,UPDRES)
#define DELRES			xppf(ctFPprefix,DELRES)
#define ENARES			xppf(ctFPprefix,ENARES)
#define CTFLUSH			xppf(ctFPprefix,CTFLUSH)
#define CTCHKPNT		xppf(ctFPprefix,CTCHKPNT)
#define CTCHKPNTX		xppf(ctFPprefix,CTCHKPNTX)
#define SYSMON			xppf(ctFPprefix,SYSMON)
#define SYSLOG			xppf(ctFPprefix,SYSLOG)
#define WRTVREC			xppf(ctFPprefix,WRTVREC)
#define RDVREC			xppf(ctFPprefix,RDVREC)
#define GETVLEN			xppf(ctFPprefix,GETVLEN)
#define ADDVREC			xppf(ctFPprefix,ADDVREC)
#define DELVREC			xppf(ctFPprefix,DELVREC)
#define RWTVREC			xppf(ctFPprefix,RWTVREC)
#define RWTPREC			xppf(ctFPprefix,RWTPREC)
#define REDVREC			xppf(ctFPprefix,REDVREC)
#define CLIFIL			xppf(ctFPprefix,CLIFIL)
#define DELIFIL			xppf(ctFPprefix,DELIFIL)
#ifdef ctFeatMAXFILE32
#undef INTISAMX
#define INTISAMX4		xppf(ctFPprefix,INTISAMX4)
#define INTISAMX INTISAMX4
#else
#define INTISAMX		xppf(ctFPprefix,INTISAMX)
#endif
#define TRANBEG			xppf(ctFPprefix,TRANBEG)
#define TRANRDY			xppf(ctFPprefix,TRANRDY)
#define TRANEND			xppf(ctFPprefix,TRANEND)
#define TRANABTX		xppf(ctFPprefix,TRANABTX)
#define TRANRST			xppf(ctFPprefix,TRANRST)
#define TRANABT			xppf(ctFPprefix,TRANABT)
#define TRANCLR			xppf(ctFPprefix,TRANCLR)
#define SAVPCLR			xppf(ctFPprefix,SAVPCLR)
#define TRANSAV			xppf(ctFPprefix,TRANSAV)
#define SPCLSAV			xppf(ctFPprefix,SPCLSAV)
#define TRANISO			xppf(ctFPprefix,TRANISO)
#define AVLFILNUM		xppf(ctFPprefix,AVLFILNUM)
#define TRANBAK			xppf(ctFPprefix,TRANBAK)
#define TRANUSR			xppf(ctFPprefix,TRANUSR)
#define setfndval		xppf(ctFPprefix,setfndval)
#define SQR			xppf(ctFPprefix,SQR)
#define CTSBLDX			xppf(ctFPprefix,CTSBLDX)
#define CLNIDXX			xppf(ctFPprefix,CLNIDXX)
#define CTSQL			xppf(ctFPprefix,CTSQL)
#define TMPNAME			xppf(ctFPprefix,TMPNAME)
#define IOPERFORMANCE		xppf(ctFPprefix,IOPERFORMANCE)
#define IOPERFORMANCEX		xppf(ctFPprefix,IOPERFORMANCEX)
#define SYSCFG			xppf(ctFPprefix,SYSCFG)
#define ORDKEY			xppf(ctFPprefix,ORDKEY)
#define CTHIST			xppf(ctFPprefix,CTHIST)
#define EQLVREC			xppf(ctFPprefix,EQLVREC)
#define GTEVREC			xppf(ctFPprefix,GTEVREC)
#define GTVREC			xppf(ctFPprefix,GTVREC)
#define LTEVREC			xppf(ctFPprefix,LTEVREC)
#define LTVREC			xppf(ctFPprefix,LTVREC)
#define NXTVREC			xppf(ctFPprefix,NXTVREC)
#define PRVVREC			xppf(ctFPprefix,PRVVREC)
#define FRSVREC			xppf(ctFPprefix,FRSVREC)
#define LSTVREC			xppf(ctFPprefix,LSTVREC)
#define FRSVSET			xppf(ctFPprefix,FRSVSET)
#define MIDVSET			xppf(ctFPprefix,MIDVSET)
#define LSTVSET			xppf(ctFPprefix,LSTVSET)
#define NXTVSET			xppf(ctFPprefix,NXTVSET)
#define PRVVSET			xppf(ctFPprefix,PRVVSET)
#define REDIVREC		xppf(ctFPprefix,REDIVREC)
#define reset_cur2		xppf(ctFPprefix,reset_cur2)
#define ctSETENCRYPT		xppf(ctFPprefix,ctSETENCRYPT)
#define SESSVAL			xppf(ctFPprefix,SESSVAL)
#define SESSINC			xppf(ctFPprefix,SESSINC)
#define PUTKSEGDEF		xppf(ctFPprefix,PUTKSEGDEF)
#define GETKSEGDEF		xppf(ctFPprefix,GETKSEGDEF)
#define XFMKSEGDEF		xppf(ctFPprefix,XFMKSEGDEF)
#define BLKIREC			xppf(ctFPprefix,BLKIREC)
#define GETXCREBLK		xppf(ctFPprefix,GETXCREBLK)
#define CTFLUSHX		xppf(ctFPprefix,CTFLUSHX)
#define CTASYNC			xppf(ctFPprefix,CTASYNC)
#define ctSNAPSHOT		xppf(ctFPprefix,ctSNAPSHOT)
#define ctSYSPUT		xppf(ctFPprefix,ctSYSPUT)
#define ctCLSNAM		xppf(ctFPprefix,ctCLSNAM)
#define ctFILBLK		xppf(ctFPprefix,ctFILBLK)
#define ctFILMTX		xppf(ctFPprefix,ctFILMTX)
#define ctFILWCD		xppf(ctFPprefix,ctFILWCD)
#define ctQUIET			xppf(ctFPprefix,ctQUIET)
#define ctSysQueueOpen		xppf(ctFPprefix,ctSysQueueOpen)
#define ctSysQueueClose		xppf(ctFPprefix,ctSysQueueClose)
#define ctSysQueueWrite		xppf(ctFPprefix,ctSysQueueWrite)
#define ctSysQueueLIFOWrite	xppf(ctFPprefix,ctSysQueueLIFOWrite)
#define ctSysQueueRead		xppf(ctFPprefix,ctSysQueueRead)
#define ctSysQueueMlen		xppf(ctFPprefix,ctSysQueueMlen)
#define ctSysQueueCount		xppf(ctFPprefix,ctSysQueueCount)
#define ctNotify		xppf(ctFPprefix,ctNotify)
#define ctReplSetFileFilter	xppf(ctFPprefix,ctReplSetFileFilter)
#define ctReplCheckFileFilter	xppf(ctFPprefix,ctReplCheckFileFilter)
#define ctReplSetPosByLogPos	xppf(ctFPprefix,ctReplSetPosByLogPos)
#define ctReplSetPosByTime	xppf(ctFPprefix,ctReplSetPosByTime)
#define ctReplGetFileName	xppf(ctFPprefix,ctReplGetFileName)
#define ctReplGetNextChange	xppf(ctFPprefix,ctReplGetNextChange)
#define ctReplPersistMinLog	xppf(ctFPprefix,ctReplPersistMinLog)
#define ctReplAgentOp		xppf(ctFPprefix,ctReplAgentOp)
#define ctUPDTICU		xppf(ctFPprefix,ctUPDTICU)
#define ALCRNG			xppf(ctFPprefix,ALCRNG)
#define ESTRNG			xppf(ctFPprefix,ESTRNG)
#define FRERNG			xppf(ctFPprefix,FRERNG)
#define FRSRNG			xppf(ctFPprefix,FRSRNG)
#define LSTRNG			xppf(ctFPprefix,LSTRNG)
#define FRSVRNG			xppf(ctFPprefix,FRSVRNG)
#define LSTVRNG			xppf(ctFPprefix,LSTVRNG)
#define NXTRNG			xppf(ctFPprefix,NXTRNG)
#define PRVRNG			xppf(ctFPprefix,PRVRNG)
#define NXTVRNG			xppf(ctFPprefix,NXTVRNG)
#define PRVVRNG			xppf(ctFPprefix,PRVVRNG)
#define ctThrdAttach		xppf(ctFPprefix,ctThrdAttach)
#define ctThrdBlockCls		xppf(ctFPprefix,ctThrdBlockCls)
#define ctThrdBlockGet		xppf(ctFPprefix,ctThrdBlockGet)
#define ctThrdBlockInit		xppf(ctFPprefix,ctThrdBlockInit)
#define ctThrdBlockRel		xppf(ctFPprefix,ctThrdBlockRel)
#define ctThrdBlockWait		xppf(ctFPprefix,ctThrdBlockWait)
#define ctThrdCreate		xppf(ctFPprefix,ctThrdCreate)
#define ctThrdData		xppf(ctFPprefix,ctThrdData)
#define ctThrdDataSet		xppf(ctFPprefix,ctThrdDataSet)
#define ctThrdDetach		xppf(ctFPprefix,ctThrdDetach)
#define ctThrdExit		xppf(ctFPprefix,ctThrdExit)
#ifdef ctFeatThrdCreate_API
#ifndef ctThrdHandle
#define ctThrdHandle		xppf(ctFPprefix,ctThrdHandle)
#endif
#endif
#define ctThrdInit		xppf(ctFPprefix,ctThrdInit)
#define ctThrdLIFOWrite		xppf(ctFPprefix,ctThrdLIFOWrite)
#define ctThrdMutexCls		xppf(ctFPprefix,ctThrdMutexCls)
#define ctThrdMutexGet		xppf(ctFPprefix,ctThrdMutexGet)
#define ctThrdMutexInit		xppf(ctFPprefix,ctThrdMutexInit)
#define ctThrdMutexRel		xppf(ctFPprefix,ctThrdMutexRel)
#define ctThrdMutexTry		xppf(ctFPprefix,ctThrdMutexTry)
#define ctThrdQueueClose	xppf(ctFPprefix,ctThrdQueueClose)
#define ctThrdQueueCount	xppf(ctFPprefix,ctThrdQueueCount)
#define ctThrdQueueMlen		xppf(ctFPprefix,ctThrdQueueMlen)
#define ctThrdQueueOpen		xppf(ctFPprefix,ctThrdQueueOpen)
#define ctThrdQueueRead		xppf(ctFPprefix,ctThrdQueueRead)
#define ctThrdQueueWrite	xppf(ctFPprefix,ctThrdQueueWrite)
#ifndef ctFeatSRVR_SDK_CSAPI_DEMOAPPSERVER	/* RAB:060630 - Srv DLL App Server Demo */
#define ctThrdQueueReadDirect	xppf(ctFPprefix,ctThrdQueueReadDirect)
#define ctThrdQueueWriteDirect	xppf(ctFPprefix,ctThrdQueueWriteDirect)
#endif
#define ctThrdSemapCls		xppf(ctFPprefix,ctThrdSemapCls)
#define ctThrdSemapGet		xppf(ctFPprefix,ctThrdSemapGet)
#define ctThrdSemapInit		xppf(ctFPprefix,ctThrdSemapInit)
#define ctThrdSemapRel		xppf(ctFPprefix,ctThrdSemapRel)
#define ctThrdSemapTry		xppf(ctFPprefix,ctThrdSemapTry)
#define ctThrdSleep		xppf(ctFPprefix,ctThrdSleep)
#define ctThrdTerm		xppf(ctFPprefix,ctThrdTerm)

#define CREDAT			xppf(ctFPprefix,CREDAT)
#define CREIDX			xppf(ctFPprefix,CREIDX)
#define OPNFIL			xppf(ctFPprefix,OPNFIL)
#ifdef ctFeatMAXFILE32
#undef OPNISAM
#define OPNISAM4		xppf(ctFPprefix,OPNISAM4)
#define OPNISAM OPNISAM4
#undef CREISAM
#define CREISAM4		xppf(ctFPprefix,CREISAM4)
#define CREISAM CREISAM4
#else
#define OPNISAM			xppf(ctFPprefix,OPNISAM)
#define CREISAM			xppf(ctFPprefix,CREISAM)
#endif
#define OPNRFIL			xppf(ctFPprefix,OPNRFIL)
#define GETDODA			xppf(ctFPprefix,GETDODA)
#define OPNIFIL			xppf(ctFPprefix,OPNIFIL)
#ifdef ctFeatMAXFILE32
#undef INTREE
#define INTREE4			xppf(ctFPprefix,INTREE4)
#define INTREE INTREE4
#undef INTISAM
#define INTISAM4		xppf(ctFPprefix,INTISAM4)
#define INTISAM INTISAM4
#else
#define INTREE			xppf(ctFPprefix,INTREE)
#define INTISAM			xppf(ctFPprefix,INTISAM)
#endif
#define PUTIFIL			xppf(ctFPprefix,PUTIFIL)
#define RENIFIL			xppf(ctFPprefix,RENIFIL)
#define CREIFIL			xppf(ctFPprefix,CREIFIL)
#define CMPIFIL			xppf(ctFPprefix,CMPIFIL)
#define RBLIFIL			xppf(ctFPprefix,RBLIFIL)
#define EXPIFIL			xppf(ctFPprefix,EXPIFIL)

#define REGCTREE		xppf(ctFPprefix,REGCTREE)
#define GETCTREE		xppf(ctFPprefix,GETCTREE)
#define NXTCTREE		xppf(ctFPprefix,NXTCTREE)
#define SWTCTREE		xppf(ctFPprefix,SWTCTREE)
#define WCHCTREE		xppf(ctFPprefix,WCHCTREE)
#define UNRCTREE		xppf(ctFPprefix,UNRCTREE)

#define SETCBRBL		xppf(ctFPprefix,SETCBRBL)
#define GETCBRBLST		xppf(ctFPprefix,GETCBRBLST)
#define SETLOGPATH		xppf(ctFPprefix,SETLOGPATH)
#define SETSFLV			xppf(ctFPprefix,SETSFLV)
#define SETWNAM			xppf(ctFPprefix,SETWNAM)
#define STPSRV			xppf(ctFPprefix,STPSRV)
#define STPSRVX			xppf(ctFPprefix,STPSRVX)
#define TFRMKEY			xppf(ctFPprefix,TFRMKEY)
#define TSTFILNUM		xppf(ctFPprefix,TSTFILNUM)
#define cttseg			xppf(ctFPprefix,cttseg)
#define ctuseg			xppf(ctFPprefix,ctuseg)
#define frmkey			xppf(ctFPprefix,frmkey)
#define ctotAlign		xppf(ctFPprefix,ctotAlign)
#define ctSETHGH		xppf(ctFPprefix,ctSETHGH)
#define ctGETHGH		xppf(ctFPprefix,ctGETHGH)
#define frmkeyx			xppf(ctFPprefix,frmkeyx)

#define ctGetOpenFiles		xppf(ctFPprefix,ctGetOpenFiles)
#define ctGetOpenFilesXtd	xppf(ctFPprefix,ctGetOpenFilesXtd)
#define ctGetFileUsers		xppf(ctFPprefix,ctGetFileUsers)
#define ctGetFileLocks		xppf(ctFPprefix,ctGetFileLocks)

#define ctGetUserErrorCode	xppf(ctFPprefix,ctGetUserErrorCode)
#define ctGetIsamErrorCode	xppf(ctFPprefix,ctGetIsamErrorCode)
#define ctGetIsamFileNbr	xppf(ctFPprefix,ctGetIsamFileNbr)
#define ctGetSystemErrorCode	xppf(ctFPprefix,ctGetSystemErrorCode)
#define ctSetCurrentSuperfileHost xppf(ctFPprefix,ctSetCurrentSuperfileHost)
#define SETFLTRX		xppf(ctFPprefix,SETFLTRX)

#undef ctLOCBHint
#endif /* ~ctLOCBH */

/* end ctlocb.h */
