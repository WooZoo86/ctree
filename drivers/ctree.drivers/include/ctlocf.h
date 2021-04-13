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

#ifndef ctLOCFH
#define ctLOCFH
#define ctLOCFHint

#ifdef ctFRCSNG
#ifdef ctPOSTFNC
#define frmkey		intfrmkey
#define frmkeyx		intfrmkeyx
#define TFRMKEY		intTFRMKEY
#define lTFRMKEY	intlTFRMKEY
#define TSTFILNUM	intTSTFILNUM
#endif
#else /* ~ctFRCSNG */
#define STPSRV		locSTPSRV
#define STPSRVX		locSTPSRVX
#define TFRMKEY		locTFRMKEY
#define uTFRMKEY	locuTFRMKEY
#define frmkey		locfrmkey
#define frmkeyx		locfrmkeyx
#ifndef ctLOCLIB
#define cttseg		loccttseg
#define ctuseg		locctuseg
#endif
#define TSTFILNUM	locTSTFILNUM
#endif /* ~ctFRCSNG */

#define CTASYNC		locCTASYNC
#define CTCHKPNT	locCTCHKPNT
#define CTFLUSH		locCTFLUSH
#define CTFLUSHX	locCTFLUSHX
#define OPNICON		locOPNICON
#define CHGICON		locCHGICON
#define CLSICON		locCLSICON
#ifdef ctCONDIDX
#define UPDCIDX		locUPDCIDX
#endif

#define ADDKEY		locADDKEY
#define ADDREC		locADDREC
#define ADDRES		locADDRES
#define ADDVREC		locADDVREC
#define ALCBAT		locALCBAT
#define ALCSET		locALCSET
#define AVLFILNUM	locAVLFILNUM
#define CHGBAT		locCHGBAT
#define CHGHST		locCHGHST
#define CHGSET		locCHGSET
#define CLNIDXX		locCLNIDXX
#define CLSFIL		locCLSFIL
#define ctCLSNAM	locctCLSNAM
#define CLIFIL		locCLIFIL
#define CLISAM		locCLISAM
#define CLRFIL		locCLRFIL
#define CMPIFIL		locCMPIFIL
#define CMPIFILX	locCMPIFILX
#define CMPIFILX8	locCMPIFILX8
#define CREDAT		locCREDAT
#define CREDATX		locCREDATX
#define CREDATX8	locCREDATX8
#define CREIFIL		locCREIFIL
#define CREIFILX	locCREIFILX
#define CREIFILX8	locCREIFILX8
#define CREIDX		locCREIDX
#define CREIDXX		locCREIDXX
#define CREIDXX8	locCREIDXX8
#define CREMEM		locCREMEM
#ifdef ctFeatMAXFILE32
#undef CREISAM
#undef CREISAMX
#define CREISAM		locCREISAM4
#define CREISAMX	locCREISAMX4
#else
#define CREISAM		locCREISAM
#define CREISAMX	locCREISAMX
#endif
#define CTHIST		locCTHIST
#define GETCURP		locGETCURP
#define GETCURK		locGETCURK
#define GETCURKL	locGETCURKL
#define ctTransferFile	locctTransferFile
#define CTUSER		locCTUSER
#define CTUSERX		locCTUSERX
#define CTSRVCTL	locCTSRVCTL
#define CTSQLCTL	locCTSQLCTL
#define DELFIL		locDELFIL
#define DELIFIL		locDELIFIL
#define DELCHK		locDELCHK
#define DELBLD		locDELBLD
#define DELREC		locDELREC
#define DELRES		locDELRES
#define DELRFIL		locDELRFIL
#define DELVREC		locDELVREC
#define ctDROPIDX	locctDROPIDX
#define BATSET		locBATSET
#define BATSETX		locBATSETX
#define ENARES		locENARES
#define ESTKEY		locESTKEY
#define EXPIFIL		locEXPIFIL
#define EXPIFILX	locEXPIFILX
#define ctFILBLK	locctFILBLK
#define ctFILMTX	locctFILMTX
#define ctFILWCD	locctFILWCD
#define FRSSET		locFRSSET
#define FRSKEY		locFRSKEY
#define FRSREC		locFRSREC
#define FREBAT		locFREBAT
#define FREBATN		locFREBATN
#define FREHST		locFREHST
#define FREHSTN		locFREHSTN
#define FRESET		locFRESET
#define FRESETN		locFRESETN
#define GETALTSEQ	locGETALTSEQ
#ifdef ctCONDIDX
#define GETCRES		locGETCRES
#define GETCIDX		locGETCIDX
#endif
#define GETDODA		locGETDODA
#define GETDODAX	locGETDODAX
#define GETKSEGDEF	locGETKSEGDEF
#define GETFIL		locGETFIL
#define GETFILX		locGETFILX
#define GTEKEY		locGTEKEY
#define GTEREC		locGTEREC
#define GTKEY		locGTKEY
#define GTREC		locGTREC
#define GETIFIL		locGETIFIL
#define GETIFILX	locGETIFILX
#define EQLKEY		locEQLKEY
#define LTEKEY		locLTEKEY
#define LTEREC		locLTEREC
#define LTKEY		locLTKEY
#define LTREC		locLTREC
#define ORDKEY		locORDKEY
#define EQLREC		locEQLREC
#define GETRES		locGETRES
#define SERIALNUM	locSERIALNUM
#define GETMNAME	locGETMNAME
#define GETNAM		locGETNAM
#define TMPNAME		locTMPNAME
#ifdef ctFeatMAXFILE32
#undef INTREE
#undef INTREEX
#undef INTISAM
#undef INTISAMX
#define INTREE		locINTREE4
#define INTREEX		locINTREEX4
#define INTISAM		locINTISAM4
#define INTISAMX	locINTISAMX4
#else
#define INTREE		locINTREE
#define INTREEX		locINTREEX
#define INTISAM		locINTISAM
#define INTISAMX	locINTISAMX
#endif
#define FRCKEY		locFRCKEY
#define LSTSET		locLSTSET
#define LSTKEY		locLSTKEY
#define LSTREC		locLSTREC
#define LOADKEY		locLOADKEY
#define ctLOKDMP	locctLOKDMP
#define ctLOKDYN	locctLOKDYN
#define ctLOKLST	locctLOKLST
#define LOKREC		locLOKREC
#define ctLOKTIMOUT	locctLOKTIMOUT
#define LKISAM		locLKISAM
#define NEWREC		locNEWREC
#define NEWVREC		locNEWVREC
#define NXTSET		locNXTSET
#define NXTKEY		locNXTKEY
#define NXTREC		locNXTREC
#define IDXENT		locIDXENT
#define ctDISTINCTest	locctDISTINCTest
#define ctDISTINCTset	locctDISTINCTset
#define ctDISTINCTestXtd  locctDISTINCTestXtd
#define ctDISTINCTsetXtd  locctDISTINCTsetXtd
#define ctImpersonateTask locctImpersonateTask
#define DATENT		locDATENT
#define RNGENT		locRNGENT
#define OPNFIL		locOPNFIL
#define OPNFILX		locOPNFILX
#define OPNIFIL		locOPNIFIL
#define OPNIFILX	locOPNIFILX
#ifdef ctFeatMAXFILE32
#undef OPNISAM
#undef OPNISAMX
#define OPNISAM		locOPNISAM4
#define OPNISAMX	locOPNISAMX4
#else
#define OPNISAM		locOPNISAM
#define OPNISAMX	locOPNISAMX
#endif
#define OPNRFIL		locOPNRFIL
#define OPNRFILX	locOPNRFILX
#define PRMIIDX		locPRMIIDX
#define PRMIIDX8	locPRMIIDX8
#define MIDSET		locMIDSET
#define PRVSET		locPRVSET
#define PRVKEY		locPRVKEY
#define PRVREC		locPRVREC
#ifdef ctPARTITION
#define PTADMIN		locPTADMIN
#endif
#ifdef ctCONDIDX
#define PUTCRES		locPUTCRES
#endif
#define PUTDODA		locPUTDODA
#define PUTDODAX	locPUTDODAX
#define PUTIFIL		locPUTIFIL
#define PUTIFILX	locPUTIFILX
#define PUTIFILX8	locPUTIFILX8
#define PUTKSEGDEF	locPUTKSEGDEF
#define ctQUIET		locctQUIET
#define REDREC		locREDREC
#define REDIREC		locREDIREC
#define REDIVREC	locREDIVREC
#define RDVREC		locRDVREC
#define RBLIIDX		locRBLIIDX
#define RBLIFIL		locRBLIFIL
#define RBLIFILX	locRBLIFILX
#define RBLIFILX8	locRBLIFILX8
#define ctRENFIL	locctRENFIL
#define RENIFIL		locRENIFIL
#define RENIFILX	locRENIFILX
#define RETREC		locRETREC
#define RETVREC		locRETVREC
#define ctSETCFG	locctSETCFG
#define ctSETENCRYPT	locctSETENCRYPT
#define ctSETSEG	locctSETSEG
#define ctSNAPSHOT	locctSNAPSHOT
#define SPCLSAV		locSPCLSAV
#define ctSYSPUT	locctSYSPUT
#define RRDREC		locRRDREC
#define REDVREC		locREDVREC
#define UPDCURI		locUPDCURI
#define ctUPDTICU	locctUPDTICU
#define TRANABT		locTRANABT
#define TRANABTX	locTRANABTX
#define TRANBAK		locTRANBAK
#define TRANBEG		locTRANBEG
#define TRANRDY		locTRANRDY
#define TRANCLR		locTRANCLR
#define TRANEND		locTRANEND
#define TRANISO		locTRANISO
#define TRANRST		locTRANRST
#define TRANSAV		locTRANSAV
#define SPCLSAV		locSPCLSAV
#define TRANUSR		locTRANUSR
#define RWTREC		locRWTREC
#define RWTVREC		locRWTVREC
#define RWTPREC		locRWTPREC
#define SAVPCLR		locSAVPCLR
#define SECURITY	locSECURITY
#define SESSVAL		locSESSVAL
#define SESSINC		locSESSINC
#define SETALTSEQ	locSETALTSEQ
#define SETCBRBL	locSETCBRBL
#define GETCBRBLST	locGETCBRBLST
#define SETCURI		locSETCURI
#define SETFLTR		locSETFLTR
#define SETFLTRN	locSETFLTRN
#define SETFLTRX	locSETFLTRX
#define RESETFLTR	locRESETFLTR
#define SETNODE		locSETNODE
#define SETOPS		locSETOPS
#define SETVARBYTS	locSETVARBYTS
#ifndef sqlSTOP
#define STPUSR		locSTPUSR
#define STPUSRA		locSTPUSRA
#endif
#define SYSLOG		locSYSLOG
#define SYSMON		locSYSMON
#define TESTHUGE	locTESTHUGE
#define CTSBLDX		locCTSBLDX
#define TMPIIDXX	locTMPIIDXX
#define TMPIIDXX8	locTMPIIDXX8
#define GTVLEN		locGTVLEN
#define PUTFIL		locPUTFIL
#define UPDRES		locUPDRES
#define GETVLEN		locGETVLEN
#define GETXCREBLK	locGETXCREBLK
#define WRTREC		locWRTREC
#define WRTVREC		locWRTVREC
#define XFMKSEGDEF	locXFMKSEGDEF

#define ctdidx		locctdidx
#define SETDEFBLK	locSETDEFBLK
#define SETDEFBLKX	locSETDEFBLKX
#define setfndval	locsetfndval
#define TSTVREC		locTSTVREC
#define cttestfunc	loccttestfunc
#define IOPERFORMANCE	locIOPERFORMANCE
#define IOPERFORMANCEX	locIOPERFORMANCEX
#define reset_cur	locreset_cur
#define reset_cur2	locreset_cur2
#define SYSCFG		locSYSCFG
#define PUTHDR		locPUTHDR

#define EQLVREC		locEQLVREC
#define FRSVREC		locFRSVREC
#define NXTVREC		locNXTVREC
#define PRVVREC		locPRVVREC
#define LSTVREC		locLSTVREC
#define GTEVREC		locGTEVREC
#define GTVREC		locGTVREC
#define LTEVREC		locLTEVREC
#define LTVREC		locLTVREC
#define FRSVSET		locFRSVSET
#define NXTVSET		locNXTVSET
#define PRVVSET		locPRVVSET
#define LSTVSET		locLSTVSET
#define MIDVSET		locMIDVSET
#define BLKIREC		locBLKIREC

#define ALCRNG		locALCRNG
#define ESTRNG		locESTRNG
#define FRERNG		locFRERNG
#define FRSRNG		locFRSRNG
#define NXTRNG		locNXTRNG
#define PRVRNG		locPRVRNG
#define LSTRNG		locLSTRNG
#define FRSVRNG		locFRSVRNG
#define NXTVRNG		locNXTVRNG
#define PRVVRNG		locPRVVRNG
#define LSTVRNG		locLSTVRNG

#define ctunic		locctunic

#define ctNotify		locctNotify
#define ctSysQueueOpen		locctSysQueueOpen
#define ctSysQueueClose		locctSysQueueClose
#define ctSysQueueWrite		locctSysQueueWrite
#define ctSysQueueLIFOWrite	locctSysQueueLIFOWrite
#define ctSysQueueRead		locctSysQueueRead
#define ctSysQueueMlen		locctSysQueueMlen
#define ctSysQueueCount		locctSysQueueCount

#define ctReplSetFileFilter	locctReplSetFileFilter
#define ctReplCheckFileFilter	locctReplCheckFileFilter
#define ctReplSetPosByLogPos	locctReplSetPosByLogPos
#define ctReplSetPosByTime	locctReplSetPosByTime
#define ctReplGetFileName	locctReplGetFileName
#define ctReplGetNextChange	locctReplGetNextChange
#define ctReplPersistMinLog	locctReplPersistMinLog
#define ctReplAgentOp		locctReplAgentOp
#define ctReplLogFileResync	locctReplLogFileResync

#define ctGetOpenFiles		locctGetOpenFiles
#define ctGetOpenFilesXtd	locctGetOpenFilesXtd
#define ctGetFileUsers		locctGetFileUsers
#define ctGetFileLocks		locctGetFileLocks

#define ctCreateSequence	locctCreateSequence
#define ctDeleteSequence	locctDeleteSequence
#define ctOpenSequence		locctOpenSequence
#define ctCloseSequence		locctCloseSequence
#define ctGetSequenceAttrs	locctGetSequenceAttrs
#define ctSetSequenceAttrs	locctSetSequenceAttrs
#define ctGetCurrentSequenceValue locctGetCurrentSequenceValue
#define ctSetCurrentSequenceValue locctSetCurrentSequenceValue
#define ctGetNextSequenceValue	locctGetNextSequenceValue

#define ctReplMasterControl	locctReplMasterControl
#define ctVERIFYidx		locctVERIFYidx
#define ctVerifyFile		locctVerifyFile

#define addIDfield		locaddIDfield
#define delIDfield		locdelIDfield
#define getIDfield		locgetIDfield
#define resetIDfield		locresetIDfield
#define xtdatrIDfield		locxtdatrIDfield
#define wchIDfield		locwchIDfield
#define SetXtdFileOpenMode	locSetXtdFileOpenMode
#define ctMEMSTAT		locctMEMSTAT
#define ctSETCOMPRESS		locctSETCOMPRESS
#define ctDeferredIndexControl	locctDeferredIndexControl
#define ctRecordUpdateCallbackControl locctRecordUpdateCallbackControl
#define ctFullText		locctFullText
#define AllocFTSearch		locAllocFTSearch
#define FreeFTSearch		locFreeFTSearch
#define FirstInFT		locFirstInFT
#define LastInFT		locLastInFT
#define NextInFT		locNextInFT
#define PrevInFT		locPrevInFT
#define ctAlterSchema		locctAlterSchema
#define ctSetCurrentSuperfileHost locctSetCurrentSuperfileHost
#define ctGetAccountExpirationTime locctGetAccountExpirationTime
#define ctGetConnectionInfo	locctGetConnectionInfo
#define UpdateRecordOffsetForKey locUpdateRecordOffsetForKey
#define USERINFOX		locUSERINFOX
#define ctSyncReplControl	locctSyncReplControl
#define addAutoSysTimeFields locaddAutoSysTimeFields
#define RemoveAutoSysTimeFields locRemoveAutoSysTimeFields
#define WhichAutoSysTimeFields locWhichAutoSysTimeFields
#define UpdateAutoSysTimeFields locUpdateAutoSysTimeFields
#define GetFileRegions		locGetFileRegions
#define ctSetTransactionId	locctSetTransactionId
#define ctReplSetPosByTransactionId locctReplSetPosByTransactionId
#define ctFILELIST		locctFILELIST
/* NOTE: add new definitions to ctsepl.h */
#include "ctsepl.h"

#undef ctLOCFHint
#endif /* ~ctLOCFH */

/* end of ctlocf.h */
