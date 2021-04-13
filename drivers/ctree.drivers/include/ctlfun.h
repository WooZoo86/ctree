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

#ifndef ctLFUNH
#define ctLFUNH

/*^****************/
#ifdef  ctPortMSIGA
#define ctNO_Commit
#define	CommitCtree				TRANEND

#define ctNO_RenameFile
#define RenameFileCtree				ctRENFIL
#endif
/*~****************/


/*^****************/
#ifdef ctPortCAPIZZI
#define ctNO_Abort
#define	ctAbort					TRANABT

#define ctNO_Commit
#define	ctCommit				TRANEND

#define ctNO_GetRecord
#define	ctGetRecord				EQLREC
#endif
/*~****************/


#ifndef ctNO_Abort
#define	Abort					TRANABT
#endif
#define AbortXtd				TRANABTX
#define	AddKey					ADDKEY
#define	AddRecord				ADDREC
#define	AddCtResource				ADDRES
#define	AddVRecord				ADDVREC
#define	AllocateBatch				ALCBAT
#define	AllocateRange				ALCRNG
#define	AllocateSet				ALCSET
#define AvailableFileNbr			AVLFILNUM
#define	Begin					TRANBEG
#define BlockingISAMRead			BLKIREC
#define	BuildKey				frmkey				
#define	BuildKeyXtd				frmkeyx
#define	ChangeBatch				CHGBAT
#define ChangeHistory				CHGHST
#define ChangeISAMContext			CHGICON
#define	ChangeSet				CHGSET
#define CleanIndexXtd				CLNIDXX
#define	ClearTranError				TRANCLR
#define	CloseCtFile				CLSFIL
#define CloseCtFileByName			ctCLSNAM
#define	CloseIFile				CLIFIL
#define	CloseConnection				CLCONN
#define	CloseISAM				CLISAM
#define CloseISAMContext			CLSICON
#define	CloseRFile				CLRFIL
#ifndef ctNO_Commit
#define	Commit					TRANEND
#endif
#define CompactIFile				CMPIFIL
#define CompactIFileXtd				CMPIFILX
#define	CompactIFileXtd8			CMPIFILX8
#define	CreateDataFile				CREDAT
#define	CreateDataFileXtd			CREDATX
#define	CreateDataFileXtd8			CREDATX8
#define	CreateIFile				CREIFIL
#define	CreateIFileXtd				CREIFILX
#define	CreateIFileXtd8				CREIFILX8
#define	CreateIndexFile				CREIDX
#define	CreateIndexFileXtd			CREIDXX
#define	CreateIndexFileXtd8			CREIDXX8
#define	CreateIndexMember			CREMEM
#define	CreateISAM				CREISAM
#define	CreateISAMXtd				CREISAMX
#define CtreeAsynchronous			CTASYNC
#define CtreeCheckPoint				CTCHKPNT
#define CtreeFlushFile				CTFLUSH
#define CtreeFlushFileXtd			CTFLUSHX
#define CtreeUserOperation			CTUSER
#define CtreeUserOperationXtd			CTUSERX
#define CtreeStdServerControl			CTSRVCTL
#define CtreeSqlServerControl			CTSQLCTL
#define	CurrentFileOffset			GETCURP
#define	CurrentISAMKey				GETCURK
#define CurrentLowLevelKey			GETCURKL
#define	DeleteCtFile				DELFIL
#define DeleteIFile				DELIFIL
#define	DeleteKey				DELCHK
#define	DeleteKeyBlind				DELBLD
#define	DeleteRecord				DELREC
#define	DeleteCtResource			DELRES
#define DeleteRFile				DELRFIL
#define	DeleteVRecord				DELVREC
#define	DoBatch					BATSET
#define	DoBatchXtd				BATSETX
#define DropIndex				ctDROPIDX
#define	EnableCtResource			ENARES
#define	EstimateKeySpan				ESTKEY
#define EstimateRange				ESTRNG
#define ExportIFile				EXPIFIL
#define ExportIFileXtd				EXPIFILX
#define FileBlock				ctFILBLK
#define FindFileByName				ctFILWCD
#define FirstInRange				FRSRNG
#define FirstInVRange				FRSVRNG
#define	FirstInSet				FRSSET
#define	FirstInVSet				FRSVSET
#define	FirstKey				FRSKEY
#define	FirstRecord				FRSREC
#define	FirstVRecord				FRSVREC
#define	FreeBatch				FREBAT
#define	FreeBatchNbr				FREBATN
#define FreeHistory				FREHST
#define FreeHistoryNbr				FREHSTN
#define	FreeRange				FRERNG
#define	FreeSet					FRESET
#define	FreeSetNbr				FRESETN
#define	GetAltSequence				GETALTSEQ
#define GetConditionalIndexResource		GETCRES
#define GetConditionalIndex			GETCIDX
#define GetCtreePointer				GETCTREE
#define	GetDODA					GETDODA
#define	GetDODAXtd				GETDODAX
#define	GetCtFileInfo				GETFIL
#define	GetCtFileInfoXtd			GETFILX
#define	GetGTEKey				GTEKEY
#define	GetGTERecord				GTEREC
#define	GetGTEVRecord				GTEVREC
#define	GetGTKey				GTKEY
#define	GetGTRecord				GTREC
#define	GetGTVRecord				GTVREC
#define	GetIFile				GETIFIL
#define	GetIFileXtd				GETIFILX
#define	GetKey					EQLKEY
#define	GetLTEKey				LTEKEY
#define	GetLTERecord				LTEREC
#define	GetLTEVRecord				LTEVREC
#define	GetLTKey				LTKEY
#define	GetLTRecord				LTREC
#define	GetLTVRecord				LTVREC
#define GetORDKey				ORDKEY
#ifndef ctNO_GetRecord
#define	GetRecord				EQLREC
#endif
#define	GetVRecord				EQLVREC
#define	GetCtResource				GETRES
#define	GetSerialNbr				SERIALNUM
#define GetSuperFileNames			GETMNAME
#define	GetSymbolicNames			GETNAM
#define	GetCtTempFileName			TMPNAME
#define GetXtdCreateBlock			GETXCREBLK
#define GetXtdKeySegmentDef			GETKSEGDEF
#define	InitCTree				INTREE
#define	InitCTreeXtd				INTREEX
#define	InitISAM				INTISAM
#define	InitISAMXtd				INTISAMX
#define	KeyAtPercentile				FRCKEY
#define LastInRange				LSTRNG
#define LastInVRange				LSTVRNG
#define	LastInSet				LSTSET
#define	LastInVSet				LSTVSET
#define	LastKey					LSTKEY
#define	LastRecord				LSTREC
#define	LastVRecord				LSTVREC
#define	LoadKey					LOADKEY
#define	LockCtData				LOKREC
#define LockDump				ctLOKDMP
#define LockDynamics				ctLOKDYN
#define	LockISAM				LKISAM
#define LockList				ctLOKLST
#define	NewData					NEWREC
#define	NewVData				NEWVREC
#define NextCtree				NXTCTREE
#define NextInRange				NXTRNG
#define NextInVRange				NXTVRNG
#define	NextInSet				NXTSET
#define	NextInVSet				NXTVSET
#define	NextKey					NXTKEY
#define	NextRecord				NXTREC
#define	NextVRecord				NXTVREC
#define	NbrOfDistinctKeyEntriesEstimated	ctDISTINCTest
#define	NbrOfDistinctKeyEntriesSet		ctDISTINCTset
#define	NbrOfDistinctKeyEntriesEstimatedXtd	ctDISTINCTestXtd
#define	NbrOfDistinctKeyEntriesSetXtd		ctDISTINCTsetXtd
#define	NbrOfKeyEntries				IDXENT
#define	NbrOfRecords				DATENT
#define NbrOfKeysInRange			RNGENT
#define	OpenCtFile				OPNFIL
#define	OpenCtFileXtd				OPNFILX
#define	OpenIFile				OPNIFIL
#define	OpenIFileXtd				OPNIFILX
#define	OpenISAM				OPNISAM
#define OpenISAMContext				OPNICON
#define	OpenISAMXtd				OPNISAMX
#define	OpenFileWithResource			OPNRFIL
#define	OpenFileWithResourceXtd			OPNRFILX
#define PartitionAdmin				PTADMIN
#define PermIIndex				PRMIIDX
#define PermIIndex8				PRMIIDX8
#define	PositionSet				MIDSET
#define	PositionVSet				MIDVSET
#define PreviousInRange				PRVRNG
#define PreviousInVRange			PRVVRNG
#define	PreviousInSet				PRVSET
#define	PreviousInVSet				PRVVSET
#define	PreviousKey				PRVKEY
#define	PreviousRecord				PRVREC
#define	PreviousVRecord				PRVVREC
#define PutConditionalIndexResource		PUTCRES
#define	PutDODA					PUTDODA
#define	PutDODAXtd				PUTDODAX
#define PutIFile				PUTIFIL
#define PutIFileXtd				PUTIFILX
#define PutIFileXtd8				PUTIFILX8
#define PutXtdKeySegmentDef			PUTKSEGDEF
#define QuietCtree				ctQUIET
#define	ReadData				REDREC
#define ReadIsamData				REDIREC
#define ReadIsamVData				REDIVREC
#define	ReadVData				RDVREC
#define RebuildIIndex				RBLIIDX
#define	RebuildIFile				RBLIFIL
#define	RebuildIFileXtd				RBLIFILX
#define	RebuildIFileXtd8			RBLIFILX8
#define RegisterCtree				REGCTREE
#define	ReleaseData				RETREC
#define	ReleaseVData				RETVREC
#ifndef ctNO_RenameFile
#define RenameFile				ctRENFIL
#endif
#define RenameIFile				RENIFIL
#define RenameIFileXtd				RENIFILX
#define	ReplaceSavePoint			SPCLSAV				
#define	ReReadRecord				RRDREC
#define	ReReadVRecord				REDVREC
#define ResetDataFilters			RESETFLTR
#define	ResetRecord				UPDCURI
#define	RestoreSavePoint			TRANRST
#define	ReWriteRecord				RWTREC
#define	ReWritePartialRecord			RWTPREC
#define	ReWriteVRecord				RWTVREC
#define SavePointClear				SAVPCLR
#define	Security				SECURITY
#define	SetAlternateSequence			SETALTSEQ
#define SetBlockingLockTimeout			ctLOKTIMOUT
#ifdef RB_CALLBACK
#define SetCallbackOnRebuild			SETCBRBL
#endif
#define SetCompress				ctSETCOMPRESS
#define SetSystemConfigurationOption		ctSETCFG
#define SetDataFilter				SETFLTR
#define SetDataFilterNbr			SETFLTRN
#define SetEncryption				ctSETENCRYPT
#define SetNodeName				SETNODE
#define SetOperationState			SETOPS
#define	SetRecord				SETCURI
#define	SetSavePoint				TRANSAV
#define SetFileSegments				ctSETSEG
#define	SetVariableBytes			SETVARBYTS
#define SnapShot				ctSNAPSHOT
#define StopServer				STPSRV
#define StopServerXtd				STPSRVX
#ifndef sqlSTOP
#define	StopUser				STPUSR
#define	StopUserAsync				STPUSRA
#endif
#define SuperfilePrepassXtd			CTSBLDX
#define SwitchCtree				SWTCTREE
#define SystemLog				SYSLOG
#define SystemMonitor				SYSMON
#define SystemConfiguration			SYSCFG
#define SystemParameterPut			ctSYSPUT
#define TempIIndexXtd				TMPIIDXX
#define TempIIndexXtd8				TMPIIDXX8
#define TestFileNbr				TSTFILNUM
#define TestHugeFile				TESTHUGE
#define TransactionHistory			CTHIST
#define TransactionIsoLevel			TRANISO
#define TransactionReady			TRANRDY
#define	TransformKey				TFRMKEY
#define TransformXtdSegment			XFMKSEGDEF
#define	TransformSegment			cttseg				
#define	VDataLength				GTVLEN
#define UnRegisterCtree				UNRCTREE
#define	UntransformSegment			ctuseg				
#define UpdateConditionalIndex			UPDCIDX
#define	UpdateFileMode				PUTFIL
#define UpdateHeader				PUTHDR
#define ctUpdateICUversion			ctUPDTICU
#define	UpdateCtResource			UPDRES
#define UserLogEntry				TRANUSR
#define	VRecordLength				GETVLEN
#define WhichCtree				WCHCTREE
#define	WriteData				WRTREC
#define	WriteVData				WRTVREC
#define AddAutoSysTimeFields    addAutoSysTimeFields 
#endif /* ctLFUNH */

/* end of ctlfun.h */
