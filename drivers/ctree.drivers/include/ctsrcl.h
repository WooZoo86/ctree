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

#ifndef ctSRCLH
#define ctSRCLH
#define ctSRCLHint

#define ADDKEY			mtc_ADDKEY
#define ADDREC			mtc_ADDREC
#define ADDRES			mtc_ADDRES
#define ADDVREC			mtc_ADDVREC
#define ALCBAT			mtc_ALCBAT
#define ALCSET			mtc_ALCSET
#define AVLFILNUM		mtc_AVLFILNUM
#define BATSET			mtc_BATSET
#define BATSETX			mtc_BATSETX
#define CHGBAT			mtc_CHGBAT
#define CHGHST			mtc_CHGHST
#define CHGICON			mtc_CHGICON
#define CHGSET			mtc_CHGSET
#define CLIFIL			mtc_CLIFIL
#define CLISAM			mtc_CLISAM
#define CLRFIL			mtc_CLRFIL
#define CLSFIL			mtc_CLSFIL
#define ctCopyFile		mtc_ctCopyFile
#define ctCLSNAM		mtc_ctCLSNAM
#define CLSICON			mtc_CLSICON
#define CMPIFIL			mtc_CMPIFIL
#define CMPIFILX		mtc_CMPIFILX
#define CMPIFILX8		mtc_CMPIFILX8
#define CREDAT			mtc_CREDAT
#define CREDATX			mtc_CREDATX
#define CREDATX8		mtc_CREDATX8
#define CREIDX			mtc_CREIDX
#define CREIDXX			mtc_CREIDXX
#define CREIDXX8		mtc_CREIDXX8
#define CREIFIL			mtc_CREIFIL
#define CREIFILX		mtc_CREIFILX
#define CREIFILX8		mtc_CREIFILX8
#define CREISAM			mtc_CREISAM
#define CREISAMX		mtc_CREISAMX
#define CREMEM			mtc_CREMEM
#define ctcdelm			mtc_ctcdelm
#define CTCHKPNT		mtc_CTCHKPNT
#define ctdidx			mtc_ctdidx
#define ctDISTINCTest		mtc_ctDISTINCTest
#define ctDISTINCTset		mtc_ctDISTINCTset
#define ctDISTINCTestXtd	mtc_ctDISTINCTestXtd
#define ctDISTINCTsetXtd	mtc_ctDISTINCTsetXtd
#define ctDROPIDX		mtc_ctDROPIDX
#define ctImpersonateTask	mtc_ctImpersonateTask
#define CTFLUSH			mtc_CTFLUSH
#define CTHIST			mtc_CTHIST
#define ctree			mtc_ctree
#define ctRENFIL		mtc_ctRENFIL
#ifndef ctrt_exit
#define ctrt_exit		mtc_ctrt_exit
#endif
#define CTSBLDX			mtc_CTSBLDX
#define ctSNAPSHOT		mtc_ctSNAPSHOT
#define ctTempDir		mtc_ctTempDir
#define ctReplLogFileResync	mtc_ctReplLogFileResync
#define cttestfunc		mtc_cttestfunc
#define ctThrdAttach		mtc_ctThrdAttach
#define ctThrdBlockCls		mtc_ctThrdBlockCls
#define ctThrdBlockGet		mtc_ctThrdBlockGet
#define ctThrdBlockInit		mtc_ctThrdBlockInit
#define ctThrdBlockRel		mtc_ctThrdBlockRel
#define ctThrdBlockWait		mtc_ctThrdBlockWait
#define ctThrdCreate		mtc_ctThrdCreate
#define ctThrdDetach		mtc_ctThrdDetach
#define ctThrdData		mtc_ctThrdData
#define ctThrdDataSet		mtc_ctThrdDataSet
#define ctThrdExit		mtc_ctThrdExit
#define ctThrdGet		mtc_ctThrdGet
#define ctThrdHandle		mtc_ctThrdHandle
#define ctThrdInit		mtc_ctThrdInit
#define ctThrdLIFOWrite		mtc_ctThrdLIFOWrite
#define ctThrdMutexCls		mtc_ctThrdMutexCls
#define ctThrdMutexGet		mtc_ctThrdMutexGet
#define ctThrdMutexInit		mtc_ctThrdMutexInit
#define ctThrdMutexRel		mtc_ctThrdMutexRel
#define ctThrdMutexTry		mtc_ctThrdMutexTry
#define ctThrdQueueClose	mtc_ctThrdQueueClose
#define ctThrdQueueCount	mtc_ctThrdQueueCount
#define ctThrdQueueMlen		mtc_ctThrdQueueMlen
#define ctThrdQueueOpen		mtc_ctThrdQueueOpen
#define ctThrdQueueRead		mtc_ctThrdQueueRead
#define ctThrdQueueWrite	mtc_ctThrdQueueWrite
#define ctThrdSemapCls		mtc_ctThrdSemapCls
#define ctThrdSemapGet		mtc_ctThrdSemapGet
#define ctThrdSemapInit		mtc_ctThrdSemapInit
#define ctThrdSemapRel		mtc_ctThrdSemapRel
#define ctThrdSemapTry		mtc_ctThrdSemapTry
#define ctThrdSet		mtc_ctThrdSet
#define ctThrdSleep		mtc_ctThrdSleep
#define ctThrdTerm		mtc_ctThrdTerm
#define cttseg			mtc_cttseg
#define ctuseg			mtc_ctuseg
#define CTUSER			mtc_CTUSER
#define ctSETHGH		mtc_ctSETHGH
#define ctGETHGH		mtc_ctGETHGH
#define DATENT			mtc_DATENT
#define DELBLD			mtc_DELBLD
#define DELCHK			mtc_DELCHK
#define DELFIL			mtc_DELFIL
#define DELIFIL			mtc_DELIFIL
#define DELREC			mtc_DELREC
#define DELRES			mtc_DELRES
#define DELRFIL			mtc_DELRFIL
#define DELVREC			mtc_DELVREC
#define ENARES			mtc_ENARES
#define EQLKEY			mtc_EQLKEY
#define EQLREC			mtc_EQLREC
#define EQLVREC			mtc_EQLVREC
#define ESTKEY			mtc_ESTKEY
#define FRCKEY			mtc_FRCKEY
#define FREBAT			mtc_FREBAT
#define FREHST			mtc_FREHST
#define FRESET			mtc_FRESET
#define FRESETN			mtc_FRESETN
#define frmkey			mtc_frmkey
#define frmkeyx			mtc_frmkeyx
#define FRSKEY			mtc_FRSKEY
#define FRSREC			mtc_FRSREC
#define FRSSET			mtc_FRSSET
#define FRSVREC			mtc_FRSVREC
#define FRSVSET			mtc_FRSVSET
#define GETALTSEQ		mtc_GETALTSEQ
#define GETCBRBLST		mtc_GETCBRBLST
#define GETCIDX			mtc_GETCIDX
#define GETCRES			mtc_GETCRES
#define GETCTREE		mtc_GETCTREE
#define GETCURK			mtc_GETCURK
#define GETCURKL		mtc_GETCURKL
#define GETCURP			mtc_GETCURP
#define GETDODA			mtc_GETDODA
#define GETFIL			mtc_GETFIL
#define GETFILX			mtc_GETFILX
#define GETIFIL			mtc_GETIFIL
#define GETIFILX		mtc_GETIFILX
#define GETMNAME		mtc_GETMNAME
#define GETNAM			mtc_GETNAM
#define GETRES			mtc_GETRES
#define GETVLEN			mtc_GETVLEN
#define GETXCREBLK		mtc_GETXCREBLK
#define GTEKEY			mtc_GTEKEY
#define GTEREC			mtc_GTEREC
#define GTEVREC			mtc_GTEVREC
#define GTKEY			mtc_GTKEY
#define GTREC			mtc_GTREC
#define GTVLEN			mtc_GTVLEN
#define GTVREC			mtc_GTVREC
#define IDXENT			mtc_IDXENT
#define INTISAM			mtc_INTISAM
#define INTISAMX		mtc_INTISAMX
#define INTREE			mtc_INTREE
#define INTREEX			mtc_INTREEX
#define IOPERFORMANCE		mtc_IOPERFORMANCE
#define IOPERFORMANCEX		mtc_IOPERFORMANCEX
#define LKISAM			mtc_LKISAM
#define LOADKEY			mtc_LOADKEY
#define LOKREC			mtc_LOKREC
#define ctLOKTIMOUT		mtc_ctLOKTIMOUT
#define ctLOKDMP		mtc_ctLOKDMP
#define ctLOKDYN		mtc_ctLOKDYN
#define ctLOKLST		mtc_ctLOKLST
#define ctTransferFile		mtc_ctTransferFile
#define LSTKEY			mtc_LSTKEY
#define LSTREC			mtc_LSTREC
#define LSTSET			mtc_LSTSET
#define LSTVREC			mtc_LSTVREC
#define LSTVSET			mtc_LSTVSET
#define LTEKEY			mtc_LTEKEY
#define LTEREC			mtc_LTEREC
#define LTEVREC			mtc_LTEVREC
#define LTKEY			mtc_LTKEY
#define LTREC			mtc_LTREC
#define LTVREC			mtc_LTVREC
#define MIDSET			mtc_MIDSET
#define MIDVSET			mtc_MIDVSET
#define NEWREC			mtc_NEWREC
#define NEWVREC			mtc_NEWVREC
#define NXTCTREE		mtc_NXTCTREE
#define NXTKEY			mtc_NXTKEY
#define NXTREC			mtc_NXTREC
#define NXTSET			mtc_NXTSET
#define NXTVREC			mtc_NXTVREC
#define NXTVSET			mtc_NXTVSET
#define OPNFIL			mtc_OPNFIL
#define OPNFILX			mtc_OPNFILX
#define OPNICON			mtc_OPNICON
#define OPNIFIL			mtc_OPNIFIL
#define OPNIFILX		mtc_OPNIFILX
#define OPNISAM			mtc_OPNISAM
#define OPNISAMX		mtc_OPNISAMX
#define OPNRFIL			mtc_OPNRFIL
#define OPNRFILX		mtc_OPNRFILX
#define ORDKEY			mtc_ORDKEY
#define PRMIIDX			mtc_PRMIIDX
#define PRMIIDX8		mtc_PRMIIDX8
#define PRVKEY			mtc_PRVKEY
#define PRVREC			mtc_PRVREC
#define PRVSET			mtc_PRVSET
#define PRVVREC			mtc_PRVVREC
#define PRVVSET			mtc_PRVVSET
#define PTADMIN			mtc_PTADMIN
#define PUTCRES			mtc_PUTCRES
#define PUTDODA			mtc_PUTDODA
#define PUTFIL			mtc_PUTFIL
#define PUTHDR			mtc_PUTHDR
#define PUTIFIL			mtc_PUTIFIL
#define PUTIFILX		mtc_PUTIFILX
#define PUTIFILX8		mtc_PUTIFILX8
#define RBLIFIL			mtc_RBLIFIL
#define RBLIFILX		mtc_RBLIFILX
#define RBLIFILX8		mtc_RBLIFILX8
#define RBLIIDX			mtc_RBLIIDX
#define RDVREC			mtc_RDVREC
#define REDIREC			mtc_REDIREC
#define REDIVREC		mtc_REDIVREC
#define REDREC			mtc_REDREC
#define REDVREC			mtc_REDVREC
#define RENIFIL			mtc_RENIFIL
#define RENIFILX		mtc_RENIFILX
#define REGCTREE		mtc_REGCTREE
#define reset_cur		mtc_reset_cur
#define reset_cur2		mtc_reset_cur2
#define RESETFLTR		mtc_RESETFLTR
#define RETREC			mtc_RETREC
#define RETVREC			mtc_RETVREC
#define RNGENT			mtc_RNGENT
#define RRDREC			mtc_RRDREC
#define RWTREC			mtc_RWTREC
#define RWTVREC			mtc_RWTVREC
#define RWTPREC			mtc_RWTPREC
#define SAVPCLR			mtc_SAVPCLR
#define SECURITY		mtc_SECURITY
#define SERIALNUM		mtc_SERIALNUM
#define SETALTSEQ		mtc_SETALTSEQ
#define ctSETCOMPRESS		mtc_ctSETCOMPRESS
#define SETCBRBL		mtc_SETCBRBL
#define SETCURI			mtc_SETCURI
#define ctSETCFG		mtc_ctSETCFG
#define ctSETENCRYPT		mtc_ctSETENCRYPT
#define setfndval		mtc_setfndval
#define SETFLTR			mtc_SETFLTR
#define SETFLTRN		mtc_SETFLTRN
#define SETFLTRX		mtc_SETFLTRX
#define SETLOGPATH		mtc_SETLOGPATH
#define SETNODE			mtc_SETNODE
#define SETOPS			mtc_SETOPS
#define SETVARBYTS		mtc_SETVARBYTS
#define STPSRV			mtc_STPSRV
#define STPUSR			mtc_STPUSR
#define STPUSRA			mtc_STPUSRA
#define SWTCTREE		mtc_SWTCTREE
#define SYSCFG			mtc_SYSCFG
#define SYSLOG			mtc_SYSLOG
#define SYSMON			mtc_SYSMON
#define TFRMKEY			mtc_TFRMKEY
#define TMPIIDXX		mtc_TMPIIDXX
#define TMPIIDXX8		mtc_TMPIIDXX8
#define TMPNAME			mtc_TMPNAME
#define TRANABT			mtc_TRANABT
#define TRANABTX		mtc_TRANABTX
#define TRANBEG			mtc_TRANBEG
#define TRANRDY			mtc_TRANRDY
#define TRANCLR			mtc_TRANCLR
#define TRANEND			mtc_TRANEND
#define TRANRST			mtc_TRANRST
#define TRANSAV			mtc_TRANSAV
#define TRANUSR			mtc_TRANUSR
#define TSTFILNUM		mtc_TSTFILNUM
#define TSTVREC			mtc_TSTVREC
#define UNRCTREE		mtc_UNRCTREE
#define UPDCIDX			mtc_UPDCIDX
#define UPDCURI			mtc_UPDCURI
#define ctUPDTICU		mtc_ctUPDTICU
#define UPDRES			mtc_UPDRES
#define ViewCtreeError		mtc_ViewCtreeError
#define WCHCTREE		mtc_WCHCTREE
#define WRTREC			mtc_WRTREC
#define WRTVREC			mtc_WRTVREC
#define ctaddusr		mtc_ctaddusr
#define ctchgusr		mtc_ctchgusr
#define ctgetseginfo		mtc_ctgetseginfo
#define ctlfsegget		mtc_ctlfsegget
#define ctlfsegput		mtc_ctlfsegput
/*
#define ctrt_printf		mtc_ctrt_printf
#define ctrt_filcmp		mtc_ctrt_filcmp
*/
#define ierr			mtc_ierr
#define mballc			mtc_mballc
#define mbfree			mtc_mbfree
#define mbfreel			mtc_mbfreel
#define mbfren			mtc_mbfren
#define mbfrenl			mtc_mbfrenl
#define nd_dig			mtc_nd_dig
#define vtclose			mtc_vtclose
#define cndxfree		mtc_cndxfree
#define cndxeval		mtc_cndxeval
#define cndxparse		mtc_cndxparse
#define cpynbuf			mtc_cpynbuf
#define cpylod			mtc_cpylod
#define cpysrc			mtc_cpysrc
#define USERINFO		mtc_USERINFO
#define USERLIST		mtc_USERLIST
#define STPSRVX			mtc_STPSRVX
#define ctsysint		mtc_ctsysint
#define cttime			mtc_cttime
#define cti_apvr		mtc_cti_apvr
#define ctklusr			mtc_ctklusr
#define dyndmp			mtc_dyndmp
#define SA_FILES		mtc_SA_FILES
#define SA_GROUP		mtc_SA_GROUP
#define SA_USERS		mtc_SA_USERS
#define SA_LOGOF		mtc_SA_LOGOF
#define SA_LOGON		mtc_SA_LOGON
#define GetServerInfo		mtc_GetServerInfo
#define GetServerInfoXtd	mtc_GetServerInfoXtd
#define GETKSEGDEF		mtc_GETKSEGDEF
#define PUTKSEGDEF		mtc_PUTKSEGDEF
#define XFMKSEGDEF		mtc_XFMKSEGDEF
#define CTASYNC			mtc_CTASYNC
#define CTFLUSHX		mtc_CTFLUSHX
#define ctNotify		mtc_ctNotify
#define ctFILBLK		mtc_ctFILBLK
#define ctFILMTX		mtc_ctFILMTX
#define ctFILWCD		mtc_ctFILWCD
#define ctQUIET			mtc_ctQUIET
#define ctSysQueueOpen		mtc_ctSysQueueOpen
#define ctSysQueueClose		mtc_ctSysQueueClose
#define ctSysQueueWrite		mtc_ctSysQueueWrite
#define ctSysQueueLIFOWrite	mtc_ctSysQueueLIFOWrite
#define ctSysQueueRead		mtc_ctSysQueueRead
#define ctSysQueueMlen		mtc_ctSysQueueMlen
#define ctSysQueueCount		mtc_ctSysQueueCount

#define ctReplSetFileFilter	mtc_ctReplSetFileFilter
#define ctReplCheckFileFilter	mtc_ctReplCheckFileFilter
#define ctReplSetFileStatus	mtc_ctReplSetFileStatus
#define ctReplGetFileStatus	mtc_ctReplGetFileStatus
#define ctReplSetPosByTime	mtc_ctReplSetPosByTime
#define ctReplSetPosByLogPos	mtc_ctReplSetPosByLogPos
#define ctReplPersistMinLog	mtc_ctReplPersistMinLog
#define ctReplGetPos		mtc_ctReplGetPos
#define ctReplGetNextChange	mtc_ctReplGetNextChange
#define ctReplGetFileName	mtc_ctReplGetFileName
#define ctReplReadFirstRecord	mtc_ctReplReadFirstRecord
#define ctReplReadNextRecord	mtc_ctReplReadNextRecord
#define ctReplReadRecordByKey	mtc_ctReplReadRecordByKey
#define ctReplInit		mtc_ctReplInit
#define ctReplTerm		mtc_ctReplTerm
#define ctReplConnect		mtc_ctReplConnect
#define ctReplDisconn		mtc_ctReplDisconn
#define ctReplOpenFile		mtc_ctReplOpenFile
#define ctReplCloseFile		mtc_ctReplCloseFile
#define ctReplChangeRecord	mtc_ctReplChangeRecord
#define ctReplTranCtl		mtc_ctReplTranCtl
#define ctReplAllocMem		mtc_ctReplAllocMem
#define ctReplFreeMem		mtc_ctReplFreeMem
#define ctReplAgentOp		mtc_ctReplAgentOp

#define BLKIREC			mtc_BLKIREC
#define ALCRNG			mtc_ALCRNG
#define ESTRNG			mtc_ESTRNG
#define FRERNG			mtc_FRERNG
#define FRSRNG			mtc_FRSRNG
#define NXTRNG			mtc_NXTRNG
#define PRVRNG			mtc_PRVRNG
#define LSTRNG			mtc_LSTRNG
#define FRSVRNG			mtc_FRSVRNG
#define NXTVRNG			mtc_NXTVRNG
#define PRVVRNG			mtc_PRVVRNG
#define LSTVRNG			mtc_LSTVRNG

#define ctGetOpenFiles		mtc_ctGetOpenFiles
#define ctGetOpenFilesXtd	mtc_ctGetOpenFilesXtd
#define ctGetFileUsers		mtc_ctGetFileUsers
#define ctGetFileLocks		mtc_ctGetFileLocks

#define addIDfield		mtc_addIDfield
#define delIDfield		mtc_delIDfield
#define getIDfield		mtc_getIDfield
#define resetIDfield		mtc_resetIDfield
#define xtdatrIDfield		mtc_xtdatrIDfield
#define wchIDfield		mtc_wchIDfield
#define SetXtdFileOpenMode	mtc_SetXtdFileOpenMode
#define ctMEMSTAT		mtc_ctMEMSTAT
#define ctDeferredIndexControl	mtc_ctDeferredIndexControl
#define ctRecordUpdateCallbackControl mtc_ctRecordUpdateCallbackControl
#define ctFullText		mtc_ctFullText
#define AllocFTSearch		mtc_AllocFTSearch
#define FreeFTSearch		mtc_FreeFTSearch
#define FirstInFT		mtc_FirstInFT
#define LastInFT		mtc_LastInFT
#define NextInFT		mtc_NextInFT
#define PrevInFT		mtc_PrevInFT
#define ctSetCurrentSuperfileHost mtc_ctSetCurrentSuperfileHost
#define ctGetAccountExpirationTime mtc_ctGetAccountExpirationTime
#define ctGetConnectionInfo	mtc_ctGetConnectionInfo
#define UpdateRecordOffsetForKey	mtc_UpdateRecordOffsetForKey
#define USERINFOX		mtc_USERINFOX
#define ctSyncReplControl	mtc_ctSyncReplControl
#define addAutoSysTimeFields mtc_addAutoSysTimeFields
#define RemoveAutoSysTimeFields mtc_RemoveAutoSysTimeFields
#define WhichAutoSysTimeFields mtc_WhichAutoSysTimeFields
#define UpdateAutoSysTimeFields mtc_UpdateAutoSysTimeFields
#define GetFileRegions		mtc_GetFileRegions
#define ctSetCurrentSuperfileHost mtc_ctSetCurrentSuperfileHost
#define ctReplSetPosByTransactionId mtc_ctReplSetPosByTransactionId
#define ctFILELIST		mtc_ctFILELIST
/* NOTE: add new definitions to ctsepl.h */
#include "ctsepl.h"

#undef ctSRCLHint
#endif /* ctSRCLH */
