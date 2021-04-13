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

#ifdef  ctLOCBH
#ifndef ctLOCUH
#define ctLOCUH
#define ctLOCUHint

/*
** undo locale variety rename
*/

/* NOTE: add new definitions to ctsepl.h */
#include "ctsepl.h"
#undef ctFILELIST
#undef ctReplSetPosByTransactionId
#undef ctSetTransactionId
#undef GetFileRegions
#undef addAutoSysTimeFields
#undef RemoveAutoSysTimeFields
#undef WhichAutoSysTimeFields
#undef UpdateAutoSysTimeFields
#undef ctSyncReplControl
#undef USERINFOX
#undef UpdateRecordOffsetForKey
#undef ctGetConnectionInfo
#undef ctGetAccountExpirationTime
#undef ctSetCurrentSuperfileHost
#undef ctAlterSchema
#undef ctFullText
#undef AllocFTSearch
#undef FreeFTSearch
#undef FirstInFT
#undef LastInFT
#undef NextInFT
#undef PrevInFT
#undef ctRecordUpdateCallbackControl
#undef ctDeferredIndexControl
#undef ctCopyFile
#undef ctSETCOMPRESS
#undef ctMEMSTAT
#undef SetXtdFileOpenMode
#undef addIDfield
#undef delIDfield
#undef getIDfield
#undef resetIDfield
#undef xtdatrIDfield
#undef wchIDfield
#undef ctVERIFYidx
#undef ctVerifyFile
#undef ctReplMasterControl
#undef ctCreateSequence
#undef ctDeleteSequence
#undef ctOpenSequence
#undef ctCloseSequence
#undef ctGetSequenceAttrs
#undef ctSetSequenceAttrs
#undef ctGetCurrentSequenceValue
#undef ctSetCurrentSequenceValue
#undef ctGetNextSequenceValue
#undef ctTransferFile
#undef ctLOKDYN
#undef ctSETCFG
#undef ctSETSEG
#undef OPNIFILX
#undef PUTIFILX8
#undef PUTIFILX
#undef RBLIFILX8
#undef RBLIFILX
#undef CMPIFILX8
#undef CMPIFILX
#undef RENIFILX
#undef EXPIFILX
#undef CREIFILX8
#undef CREIFILX
#undef PRMIIDX8
#undef PRMIIDX
#undef RBLIIDX
#undef TMPIIDXX8
#undef TMPIIDXX
#undef TMPIIDX
#undef reset_cur
#undef GETMNAME
#undef GETNAM
#undef SECURITY
#undef GETFIL
#undef GETFILX
#undef PUTCRES
#undef GETCRES
#undef GETCIDX
#undef UPDCIDX
#undef OPNICON
#undef CHGICON
#undef CLSICON
#undef PUTFIL
#undef PUTHDR
#undef ADDKEY
#undef PTADMIN
#undef GETCURP
#undef GETCURK
#undef GETCURKL
#undef NEWREC
#undef RETREC
#undef REDIREC
#undef REDREC
#undef WRTREC
#undef DATENT
#undef LOKREC
#undef ctLOKTIMOUT
#undef ctLOKLST
#undef DELFIL
#undef ctDROPIDX
#undef DELCHK
#undef DELBLD
#undef ESTKEY
#undef RNGENT
#undef FRCKEY
#undef PUTDODAX
#undef PUTDODA
#undef CLISAM
#undef SERIALNUM
#undef STPUSR
#undef STPUSRA
#undef cttestfunc
#undef INTREEX
#ifdef ctFeatMAXFILE32
#undef INTREEX4
#define INTREEX INTREEX4
#endif
#undef OPNRFILX
#undef OPNFILX
#undef CLSFIL
#undef LKISAM
#undef ADDREC
#undef RWTREC
#undef DELREC
#undef TESTHUGE
#undef CLRFIL
#undef DELRFIL
#undef EQLREC
#undef GTEREC
#undef GTREC
#undef LTEREC
#undef LTREC
#undef NXTREC
#undef PRVREC
#undef FRSREC
#undef LSTREC
#undef RRDREC
#undef UPDCURI
#undef SETCURI
#undef CREISAMX
#undef OPNISAMX
#ifdef ctFeatMAXFILE32
#undef OPNISAMX4
#define OPNISAMX OPNISAMX4
#undef CREISAMX4
#define CREISAMX CREISAMX4
#endif
#undef CREDATX8
#undef CREDATX
#undef CREIDXX8
#undef CREIDXX
#undef CREMEM
#undef IDXENT
#undef ctDISTINCTest
#undef ctDISTINCTset
#undef ctDISTINCTestXtd
#undef ctDISTINCTsetXtd
#undef ctImpersonateTask
#undef LOADKEY
#undef EQLKEY
#undef GTEKEY
#undef FRSKEY
#undef LSTKEY
#undef NXTKEY
#undef PRVKEY
#undef GTKEY
#undef LTKEY
#undef LTEKEY
#undef ALCSET
#undef FRESET
#undef FRESETN
#undef CHGSET
#undef ALCBAT
#undef FREBAT
#undef FREBATN
#undef CHGBAT
#undef FREHST
#undef FREHSTN
#undef CHGHST
#undef BATSET
#undef BATSETX
#undef PERFORM
#undef USERLIST
#undef USERINFO
#undef ctklusr
#undef ctRENFIL
#undef SETFLTR
#undef SETFLTRN
#undef SETFLTRX
#undef RESETFLTR
#undef SETNODE
#undef ctLOKDMP
#undef CTUSER
#undef CTUSERX
#undef CTSQLCTL
#undef CTSRVCTL
#undef CT_USER
#undef CT_USERX
#undef CT_SQLCTL
#undef CT_SRVCTL
#undef SETOPS
#undef FRSSET
#undef MIDSET
#undef LSTSET
#undef NXTSET
#undef PRVSET
#undef SETALTSEQ
#undef SETVARBYTS
#undef GETALTSEQ
#undef SETDEFBLKX
#undef SETDEFBLK
#undef GTVLEN
#undef GETIFILX
#undef GETIFIL
#undef GETDODAX
#undef NEWVREC
#undef TSTVREC
#undef RETVREC
#undef GETRES
#undef ctdidx
#undef ADDRES
#undef UPDRES
#undef DELRES
#undef ENARES
#undef CTFLUSH
#undef CTCHKPNT
#undef CTCHKPNTX
#undef SYSMON
#undef SYSLOG
#undef WRTVREC
#undef RDVREC
#undef GETVLEN
#undef ADDVREC
#undef DELVREC
#undef RWTVREC
#undef RWTPREC
#undef REDVREC
#undef CLIFIL
#undef DELIFIL
#undef INTISAMX
#ifdef ctFeatMAXFILE32
#undef INTISAMX4
#define INTISAMX INTISAMX4
#endif
#undef TRANBEG
#undef TRANRDY
#undef TRANEND
#undef TRANABTX
#undef TRANRST
#undef TRANABT
#undef TRANCLR
#undef SAVPCLR
#undef TRANSAV
#undef SPCLSAV
#undef TRANISO
#undef AVLFILNUM
#undef TRANBAK
#undef TRANUSR
#undef setfndval
#undef SQR
#undef CTSBLDX
#undef CLNIDXX
#undef CTSQL
#undef TMPNAME
#undef IOPERFORMANCE
#undef IOPERFORMANCEX
#undef SYSCFG
#undef ORDKEY
#undef CTHIST
#undef EQLVREC
#undef GTEVREC
#undef GTVREC
#undef LTEVREC
#undef LTVREC
#undef NXTVREC
#undef PRVVREC
#undef FRSVREC
#undef LSTVREC
#undef FRSVSET
#undef MIDVSET
#undef LSTVSET
#undef NXTVSET
#undef PRVVSET
#undef REDIVREC
#undef reset_cur2
#undef ctSETENCRYPT
#undef SESSVAL
#undef SESSINC
#undef PUTKSEGDEF
#undef GETKSEGDEF
#undef XFMKSEGDEF
#undef BLKIREC
#undef GETXCREBLK
#undef CTFLUSHX
#undef CTASYNC
#undef ctSNAPSHOT
#undef ctSYSPUT
#undef ctCLSNAM
#undef ctUPDTICU
#undef ctFILBLK
#undef ctFILMTX
#undef ctFILWCD
#undef ctQUIET
#undef ctSysQueueOpen
#undef ctSysQueueClose
#undef ctSysQueueWrite
#undef ctSysQueueLIFOWrite
#undef ctSysQueueRead
#undef ctSysQueueMlen
#undef ctSysQueueCount
#undef ctNotify
#undef ctReplSetFileFilter
#undef ctReplCheckFileFilter
#undef ctReplSetPosByLogPos
#undef ctReplSetPosByTime
#undef ctReplGetFileName
#undef ctReplGetNextChange
#undef ctReplPersistMinLog
#undef ctReplAgentOp
#undef ctReplLogFileResync
#undef ALCRNG
#undef ESTRNG
#undef FRERNG
#undef FRSRNG
#undef LSTRNG
#undef FRSVRNG
#undef LSTVRNG
#undef NXTRNG
#undef PRVRNG
#undef NXTVRNG
#undef PRVVRNG
#undef ctThrdAttach
#undef ctThrdBlockCls
#undef ctThrdBlockGet
#undef ctThrdBlockInit
#undef ctThrdBlockRel
#undef ctThrdBlockWait
#undef ctThrdCreate
#undef ctThrdData
#undef ctThrdDataSet
#undef ctThrdDetach
#undef ctThrdExit
#undef ctThrdHandle
#undef ctThrdInit
#undef ctThrdLIFOWrite
#undef ctThrdMutexCls
#undef ctThrdMutexGet
#undef ctThrdMutexInit
#undef ctThrdMutexRel
#undef ctThrdMutexTry
#undef ctThrdQueueClose
#undef ctThrdQueueCount
#undef ctThrdQueueMlen
#undef ctThrdQueueOpen
#undef ctThrdQueueRead
#undef ctThrdQueueReadDirect
#undef ctThrdQueueWrite
#undef ctThrdQueueWriteDirect
#undef ctThrdSemapCls
#undef ctThrdSemapGet
#undef ctThrdSemapInit
#undef ctThrdSemapRel
#undef ctThrdSemapTry
#undef ctThrdSleep
#undef ctThrdTerm

#undef CREDAT
#undef CREIDX
#undef OPNFIL
#undef OPNISAM
#undef CREISAM
#ifdef ctFeatMAXFILE32
#undef OPNISAM4
#define OPNISAM OPNISAM4
#undef CREISAM4
#define CREISAM CREISAM4
#endif
#undef OPNRFIL
#undef GETDODA
#undef OPNIFIL
#undef INTREE
#undef INTISAM
#ifdef ctFeatMAXFILE32
#undef INTREE4
#define INTREE INTREE4
#undef INTISAM4
#define INTISAM INTISAM4
#endif
#undef PUTIFIL
#undef RENIFIL
#undef CREIFIL
#undef CMPIFIL
#undef RBLIFIL
#undef EXPIFIL

#undef REGCTREE
#undef GETCTREE
#undef NXTCTREE
#undef SWTCTREE
#undef WCHCTREE
#undef UNRCTREE

#undef SETCBRBL
#undef GETCBRBLST
#undef SETLOGPATH
#undef SETSFLV
#undef SETWNAM
#undef STPSRV
#undef STPSRVX
#undef TFRMKEY
#undef TSTFILNUM
#undef cttseg
#undef ctuseg
#undef frmkey
#undef ctotAlign
#undef ctSETHGH
#undef ctGETHGH
#undef frmkeyx

#undef ctGetOpenFiles
#undef ctGetOpenFilesXtd
#undef ctGetFileUsers
#undef ctGetFileLocks

#undef ctGetUserErrorCode
#undef ctGetIsamErrorCode
#undef ctGetIsamFileNbr
#undef ctGetSystemErrorCode

#undef ctLOCBH

#undef ctTempDir

#undef ctLOCUHint
#endif /* ~ctLOCUH */
#endif /*  ctLOCBH */

/* end ctlocu.h */
