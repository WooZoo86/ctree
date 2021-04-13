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

#ifndef _CTDBAPI1_H_
#define _CTDBAPI1_H_

#ifdef  _CTDBAPI1_C_		/* if from main API source module */
#include "ctdbapia.h"
#else

#define ctdbDayOfWeek				ii_ctdbDayOfWeek
#define _ctdbGetDatno				ii_ctdbGetDatno
#define ctdbGetDay				ii_ctdbGetDay
#define ctdbGetHour				ii_ctdbGetHour
#define ctdbGetMinute				ii_ctdbGetMinute
#define ctdbGetMonth				ii_ctdbGetMonth
#define ctdbGetSecond				ii_ctdbGetSecond
#define ctdbGetYear				ii_ctdbGetYear
#define ctdbGetFieldNullFlag			ii_ctdbGetFieldNullFlag
#define ctdbGetIndexDuplicateFlag		ii_ctdbGetIndexDuplicateFlag
#define ctdbGetIndexNullFlag			ii_ctdbGetIndexNullFlag
#define ctdbGetIndexTemporaryFlag		ii_ctdbGetIndexTemporaryFlag
#define ctdbGetLockActive			ii_ctdbGetLockActive
#define ctdbGetLogonOnly			ii_ctdbGetLogonOnly
#define ctdbHasNullFieldSupport			ii_ctdbHasNullFieldSupport
#define ctdbIsActiveDatabase			ii_ctdbIsActiveDatabase
#define ctdbIsActiveSession			ii_ctdbIsActiveSession
#define ctdbIsActiveTable			ii_ctdbIsActiveTable
#define ctdbIsEditedRecord			ii_ctdbIsEditedRecord
#define ctdbIsExtSegment			ii_ctdbIsExtSegment
#define ctdbIsLeapYear				ii_ctdbIsLeapYear
#define ctdbIsLockActive			ii_ctdbIsLockActive
#define ctdbIsNewRecord				ii_ctdbIsNewRecord
#define ctdbIsNullField				ii_ctdbIsNullField
#define ctdbIsTransActive			ii_ctdbIsTransActive
#define ctdbIsVariableField			ii_ctdbIsVariableField
#define _ctdbSuperIsExclusive			ii_ctdbSuperIsExclusive
#define _ctdbSuperIsOpen			ii_ctdbSuperIsOpen
#define _ctdbTestBit				ii_ctdbTestBit
#define ctdbGetTableCreateMode			ii_ctdbGetTableCreateMode
#define ctdbGetDefDateType			ii_ctdbGetDefDateType
#define ctdbGetIndexKeyType			ii_ctdbGetIndexKeyType
#define _ctdbGetNumberOfIndexEntries		ii_ctdbGetNumberOfIndexEntries
#define _ctdbGetNumberOfRecords			ii_ctdbGetNumberOfRecords
#define _ctdbADDREC				ii_ctdbADDREC
#define _ctdbADDRES				ii_ctdbADDRES
#define _ctdbADDVREC				ii_ctdbADDVREC
#define _ctdbAVLFILNBR				ii_ctdbAVLFILNBR
#define ctdbAbort				ii_ctdbAbort
#define ctdbAddDatabase				ii_ctdbAddDatabase
#define ctdbAddLock				ii_ctdbAddLock
#define ctdbAddTable				ii_ctdbAddTable
#define ctdbAddTableXtd				ii_ctdbAddTableXtd
#define ctdbAlterTable				ii_ctdbAlterTable
#define ctdbBegin				ii_ctdbBegin
#define ctdbPrepareCommit			ii_ctdbPrepareCommit
#define ctdbBlobClear				ii_ctdbBlobClear
#define ctdbBlobSet				ii_ctdbBlobSet
#define ctdbBuildTargetKey			ii_ctdbBuildTargetKey
#define _ctdbCHGICON				ii_ctdbCHGICON
#define _ctdbCLRFIL				ii_ctdbCLRFIL
#define _ctdbCLSFIL				ii_ctdbCLSFIL
#define _ctdbCLSICON				ii_ctdbCLSICON
#define _ctdbCREDAT				ii_ctdbCREDAT
#define _ctdbCREIFILX				ii_ctdbCREIFILX
#define _ctdbCREIFILXX				ii_ctdbCREIFILXX
#define _ctdbClearDict				ii_ctdbClearDict
#define ctdbClearField				ii_ctdbClearField
#define ctdbClearRecord				ii_ctdbClearRecord
#define ctdbClearTableSuperFile			ii_ctdbClearTableSuperFile
#define ctdbCloseAll				ii_ctdbCloseAll
#define _ctdbCloseDict				ii_ctdbCloseDict
#define ctdbCloseTable				ii_ctdbCloseTable
#define ctdbCommit				ii_ctdbCommit
#define ctdbConnect				ii_ctdbConnect
#define ctdbCopyRecordBuffer			ii_ctdbCopyRecordBuffer
#define ctdbCreateDatabase			ii_ctdbCreateDatabase
#define _ctdbCreateDict				ii_ctdbCreateDict
#define ctdbCreateSession			ii_ctdbCreateSession
#define ctdbCreateTable				ii_ctdbCreateTable
#define ctdbCurrentDate				ii_ctdbCurrentDate
#define ctdbCurrentDateTime			ii_ctdbCurrentDateTime
#define ctdbCurrentTime				ii_ctdbCurrentTime
#define ctdbServerDateTime			ii_ctdbServerDateTime
#define _ctdbDELFIL				ii_ctdbDELFIL
#define _ctdbDELREC				ii_ctdbDELREC
#define _ctdbDELRFIL				ii_ctdbDELRFIL
#define _ctdbDELVREC				ii_ctdbDELVREC
#define ctdbDateCheck				ii_ctdbDateCheck
#define ctdbDatePack				ii_ctdbDatePack
#define ctdbDateTimeGetDate			ii_ctdbDateTimeGetDate
#define ctdbDateTimeGetTime			ii_ctdbDateTimeGetTime
#define ctdbDateTimePack			ii_ctdbDateTimePack
#define ctdbDateTimeSetDate			ii_ctdbDateTimeSetDate
#define ctdbDateTimeSetTime			ii_ctdbDateTimeSetTime
#define ctdbDateTimeToString			ii_ctdbDateTimeToString
#define ctdbDateTimeUnpack			ii_ctdbDateTimeUnpack
#define ctdbDateToString			ii_ctdbDateToString
#define ctdbDateUnpack				ii_ctdbDateUnpack
#define ctdbDelField				ii_ctdbDelField
#define ctdbDelFieldByName			ii_ctdbDelFieldByName
#define ctdbDelIndex				ii_ctdbDelIndex
#define ctdbDelLock				ii_ctdbDelLock
#define ctdbDelSegment				ii_ctdbDelSegment
#define ctdbDelSegmentEx			ii_ctdbDelSegmentEx
#define ctdbDeleteDatabase			ii_ctdbDeleteDatabase
#define _ctdbDeleteDict				ii_ctdbDeleteDict
#define ctdbDeleteRecord			ii_ctdbDeleteRecord
#define ctdbDeleteTable				ii_ctdbDeleteTable
#define _ctdbDictAddAllIndex			ii_ctdbDictAddAllIndex
#define _ctdbDictAddDatabase			ii_ctdbDictAddDatabase
#define _ctdbDictAddIndex			ii_ctdbDictAddIndex
#define _ctdbDictAddTable			ii_ctdbDictAddTable
#define _ctdbDictDropAllIndex			ii_ctdbDictDropAllIndex
#define _ctdbDictDropDatabase			ii_ctdbDictDropDatabase
#define _ctdbDictDropIndex			ii_ctdbDictDropIndex
#define _ctdbDictDropTable			ii_ctdbDictDropTable
#define _ctdbDictFindDatabase			ii_ctdbDictFindDatabase
#define _ctdbDictFindDatabaseByUID		ii_ctdbDictFindDatabaseByUID
#define _ctdbDictFindIndex			ii_ctdbDictFindIndex
#define _ctdbDictFindIndexByUID			ii_ctdbDictFindIndexByUID
#define _ctdbDictFindTable			ii_ctdbDictFindTable
#define _ctdbDictFindTableByUID			ii_ctdbDictFindTableByUID
#define _ctdbDictFirstDatabase			ii_ctdbDictFirstDatabase
#define _ctdbDictFirstTable			ii_ctdbDictFirstTable
#define _ctdbDictGetDatabaseUID			ii_ctdbDictGetDatabaseUID
#define _ctdbDictGetTableUID			ii_ctdbDictGetTableUID
#define _ctdbDictNextDatabase			ii_ctdbDictNextDatabase
#define _ctdbDictNextTable			ii_ctdbDictNextTable
#define _ctdbDictReserveIndex			ii_ctdbDictReserveIndex
#define _ctdbDictReserveTable			ii_ctdbDictReserveTable
#define _ctdbDictUpdateIndex			ii_ctdbDictUpdateIndex
#define ctdbDisconnect				ii_ctdbDisconnect
#define ctdbDisconnectAll			ii_ctdbDisconnectAll
#define ctdbDropDatabase			ii_ctdbDropDatabase
#define ctdbDropTable				ii_ctdbDropTable
#define _ctdbDumpDict				ii_ctdbDumpDict
#define _ctdbEndDebug				ii_ctdbEndDebug
#define _ctdbFINDREC				ii_ctdbFINDREC
#define _ctdbFRESET				ii_ctdbFRESET
#define _ctdbFileExist				ii_ctdbFileExist
#define ctdbFindDatabase			ii_ctdbFindDatabase
#define ctdbFindDatabaseByUID			ii_ctdbFindDatabaseByUID
#define _ctdbFindDict				ii_ctdbFindDict
#define _ctdbFindDictByUID			ii_ctdbFindDictByUID
#define ctdbFindRecord				ii_ctdbFindRecord
#define ctdbLocateRecord			ii_ctdbLocateRecord
#define ctdbSetRecordCriteria		ii_ctdbSetRecordCriteria
#define ctdbUpdateRecordCriteria		ii_ctdbUpdateRecordCriteria
#define ctdbGetBestIndex		    ii_ctdbGetBestIndex
#define ctdbAddLocateCriteria		ii_ctdbAddLocateCriteria
#define ctdbFindTable				ii_ctdbFindTable
#define ctdbFindTableByUID			ii_ctdbFindTableByUID
#define ctdbFindTarget				ii_ctdbFindTarget
#define ctdbFirstDatabase			ii_ctdbFirstDatabase
#define _ctdbFirstDict				ii_ctdbFirstDict
#define ctdbFirstRecord				ii_ctdbFirstRecord
#define ctdbFirstTable				ii_ctdbFirstTable
#define ctdbFloatToMoney			ii_ctdbFloatToMoney
#define _ctdbGETCURP				ii_ctdbGETCURP
#define _ctdbGETDODA				ii_ctdbGETDODA
#define _ctdbGETFIL				ii_ctdbGETFIL
#define _ctdbGETIFIL				ii_ctdbGETIFIL
#define _ctdbGETRES				ii_ctdbGETRES
#define _ctdbGETSCHEMA				ii_ctdbGETSCHEMA
#define _ctdbGETVLEN				ii_ctdbGETVLEN
#define ctdbGetActiveDatabaseUID		ii_ctdbGetActiveDatabaseUID
#define ctdbGetActiveTableUID			ii_ctdbGetActiveTableUID
#define ctdbGetDatabaseUID			ii_ctdbGetDatabaseUID
#define _ctdbGetDict				ii_ctdbGetDict
#define _ctdbGetDictUID				ii_ctdbGetDictUID
#define ctdbGetError				ii_ctdbGetError
#define ctdbGetFieldAsBinary			ii_ctdbGetFieldAsBinary
#define ctdbGetFieldAsBlob			ii_ctdbGetFieldAsBlob
#define ctdbGetFieldAsBool			ii_ctdbGetFieldAsBool
#define ctdbGetFieldAsDate			ii_ctdbGetFieldAsDate
#define ctdbGetFieldAsDateTime			ii_ctdbGetFieldAsDateTime
#define ctdbGetFieldAsFloat			ii_ctdbGetFieldAsFloat
#define ctdbGetFieldAsMoney			ii_ctdbGetFieldAsMoney
#define ctdbGetFieldAsSigned			ii_ctdbGetFieldAsSigned
#define ctdbGetFieldAsString			ii_ctdbGetFieldAsString
#define ctdbGetFieldAsTime			ii_ctdbGetFieldAsTime
#define ctdbGetFieldAsUnsigned			ii_ctdbGetFieldAsUnsigned
#define ctdbGetFieldProperties			ii_ctdbGetFieldProperties
#define _ctdbGetFldx				ii_ctdbGetFldx
#define ctdbGetIndexNbr				ii_ctdbGetIndexNbr
#define ctdbGetRecordCount			ii_ctdbGetRecordCount
#define ctdbGetRecordPos			ii_ctdbGetRecordPos
#define ctdbGetRecordKeyPos			ii_ctdbGetRecordKeyPos
#define ctdbGetSegmentNbr			ii_ctdbGetSegmentNbr
#define ctdbGetSessionPath			ii_ctdbGetSessionPath
#define ctdbGetTableUID				ii_ctdbGetTableUID
#define ctdbGetUserTag				ii_ctdbGetUserTag
#define _ctdbIconAdd				ii_ctdbIconAdd
#define _ctdbIconAlloc				ii_ctdbIconAlloc
#define _ctdbIconFree				ii_ctdbIconFree
#define _ctdbIconReset				ii_ctdbIconReset
#define _ctdbIconSwitch				ii_ctdbIconSwitch
#define _ctdbLKISAM				ii_ctdbLKISAM
#define _ctdbLOKREC				ii_ctdbLOKREC
#define ctdbLastRecord				ii_ctdbLastRecord
#define _ctdbListAdd				ii_ctdbListAdd
#define _ctdbListClear				ii_ctdbListClear
#define _ctdbListDelete				ii_ctdbListDelete
#define _ctdbListDeleteEx			ii_ctdbListDeleteEx
#define _ctdbListExchange			ii_ctdbListExchange
#define _ctdbListExpand				ii_ctdbListExpand
#define _ctdbListInsert				ii_ctdbListInsert
#define _ctdbListMove				ii_ctdbListMove
#define _ctdbListReplace			ii_ctdbListReplace
#define ctdbLock				ii_ctdbLock
#define ctdbLockRecord				ii_ctdbLockRecord
#define ctdbLogon				ii_ctdbLogon
#define ctdbLogout				ii_ctdbLogout
#define ctdbLongToMoney				ii_ctdbLongToMoney
#define _ctdbMOVREC				ii_ctdbMOVREC
#define _ctdbMOVSET				ii_ctdbMOVSET
#define ctdbMoneyAdd				ii_ctdbMoneyAdd
#define ctdbMoneyDiv				ii_ctdbMoneyDiv
#define ctdbMoneyMul				ii_ctdbMoneyMul
#define ctdbMoneySub				ii_ctdbMoneySub
#define ctdbMoneyToFloat			ii_ctdbMoneyToFloat
#define ctdbMoneyToLong				ii_ctdbMoneyToLong
#define ctdbMoneyToString			ii_ctdbMoneyToString
#define ctdbMoveField				ii_ctdbMoveField
#define ctdbNextDatabase			ii_ctdbNextDatabase
#define _ctdbNextDict				ii_ctdbNextDict
#define ctdbNextRecord				ii_ctdbNextRecord
#define ctdbNextTable				ii_ctdbNextTable
#define _ctdbOPNFIL				ii_ctdbOPNFIL
#define _ctdbOPNICON				ii_ctdbOPNICON
#define _ctdbOPNRFILX				ii_ctdbOPNRFILX
#define _ctdbOpenDict				ii_ctdbOpenDict
#define ctdbOpenTable				ii_ctdbOpenTable
#define ctdbOpenTableByUID			ii_ctdbOpenTableByUID
#define _ctdbPRMIIDX				ii_ctdbPRMIIDX
#define _ctdbTMPIIDX				ii_ctdbTMPIIDX
#define ctdbPrevRecord				ii_ctdbPrevRecord
#define _ctdbPutDict				ii_ctdbPutDict
#define _ctdbPutFldx				ii_ctdbPutFldx
#define _ctdbRBLIFILX				ii_ctdbRBLIFILX
#define _ctdbREDIREC				ii_ctdbREDIREC
#define _ctdbREDIVREC				ii_ctdbREDIVREC
#define _ctdbREDVREC				ii_ctdbREDVREC
#define _ctdbREGCTREE				ii_ctdbREGCTREE
#define _ctdbRENIFIL				ii_ctdbRENIFIL
#define _ctdbRWTREC				ii_ctdbRWTREC
#define _ctdbRWTVREC				ii_ctdbRWTVREC
#define _ctdbRWTPREC				ii_ctdbRWTPREC
#define ctdbReadRecord				ii_ctdbReadRecord
#define ctdbRecLock				ii_ctdbRecLock
#define ctdbRecUnlock				ii_ctdbRecUnlock
#define ctdbRecordSetOff			ii_ctdbRecordSetOff
#define ctdbRecordSetOn				ii_ctdbRecordSetOn
#define ctdbReleaseLocks			ii_ctdbReleaseLocks
#define ctdbReleaseTableLocks			ii_ctdbReleaseTableLocks
#define _ctdbRemoveDict				ii_ctdbRemoveDict
#define _ctdbRemoveDictByUID			ii_ctdbRemoveDictByUID
#define ctdbReopenDict				ii_ctdbReopenDict
#define ctdbResetAll				ii_ctdbResetAll
#define ctdbResetRecord				ii_ctdbResetRecord
#define ctdbRestoreSavePoint			ii_ctdbRestoreSavePoint
#define _ctdbSETCURI				ii_ctdbSETCURI
#define _ctdbSWTCTREE				ii_ctdbSWTCTREE
#define ctdbSeekRecord				ii_ctdbSeekRecord
#define ctdbSetDatabaseObjptr			ii_ctdbSetDatabaseObjptr
#define ctdbSetDefDateType			ii_ctdbSetDefDateType
#define ctdbSetDefFloatFormat			ii_ctdbSetDefFloatFormat
#define ctdbSetDefTimeType			ii_ctdbSetDefTimeType
#define ctdbSetDefaultIndex			ii_ctdbSetDefaultIndex
#define ctdbSetEditedRecord			ii_ctdbSetEditedRecord
#define ctdbSetError				ii_ctdbSetError
#define ctdbSetFieldAsBinary			ii_ctdbSetFieldAsBinary
#define ctdbSetFieldAsBlob			ii_ctdbSetFieldAsBlob
#define ctdbSetFieldAsBool			ii_ctdbSetFieldAsBool
#define ctdbSetFieldAsDate			ii_ctdbSetFieldAsDate
#define ctdbSetFieldAsDateTime			ii_ctdbSetFieldAsDateTime
#define ctdbSetFieldAsFloat			ii_ctdbSetFieldAsFloat
#define ctdbSetFieldAsMoney			ii_ctdbSetFieldAsMoney
#define ctdbSetFieldAsSigned			ii_ctdbSetFieldAsSigned
#define ctdbSetFieldAsString			ii_ctdbSetFieldAsString
#define ctdbSetFieldAsTime			ii_ctdbSetFieldAsTime
#define ctdbSetFieldAsUnsigned			ii_ctdbSetFieldAsUnsigned
#define ctdbSetFieldLength			ii_ctdbSetFieldLength
#define ctdbSetFieldName			ii_ctdbSetFieldName
#define ctdbSetFieldNullFlag			ii_ctdbSetFieldNullFlag
#define ctdbSetFieldPrecision			ii_ctdbSetFieldPrecision
#define ctdbSetFieldProperties			ii_ctdbSetFieldProperties
#define ctdbSetFieldScale			ii_ctdbSetFieldScale
#define ctdbIsFieldNumeric			ii_ctdbIsFieldNumeric
#define ctdbSetFieldType			ii_ctdbSetFieldType
#define ctdbSetIndexDuplicateFlag		ii_ctdbSetIndexDuplicateFlag
#define ctdbSetIndexEmptyChar			ii_ctdbSetIndexEmptyChar
#define ctdbSetIndexExtension			ii_ctdbSetIndexExtension
#define ctdbSetIndexKeyType			ii_ctdbSetIndexKeyType
#define ctdbSetIndexNullFlag			ii_ctdbSetIndexNullFlag
#define ctdbSetIndexTemporaryFlag		ii_ctdbSetIndexTemporaryFlag
#define ctdbSetIndexCndxExpr		ii_ctdbSetIndexCndxExpr
#define ctdbSetLockActive			ii_ctdbSetLockActive
#define ctdbSetLockMode				ii_ctdbSetLockMode
#define ctdbSetLogonOnly			ii_ctdbSetLogonOnly
#define ctdbSetNewRecord			ii_ctdbSetNewRecord
#define ctdbSetRecordOffset			ii_ctdbSetRecordOffset
#define ctdbSetRecordPos			ii_ctdbSetRecordPos
#define ctdbSetSegmentMode			ii_ctdbSetSegmentMode
#define ctdbSetSessionParams			ii_ctdbSetSessionParams
#define ctdbSetSessionPath			ii_ctdbSetSessionPath
#define ctdbSetTableDefaultDataExtentSize 	ii_ctdbSetTableDefaultDataExtentSize
#define ctdbSetTableDefaultIndexExtentSize	ii_ctdbSetTableDefaultIndexExtentSize
#define ctdbSetTableExtension			ii_ctdbSetTableExtension
#define ctdbSetTableGroupid			ii_ctdbSetTableGroupid
#define ctdbSetTableObjptr			ii_ctdbSetTableObjptr
#define ctdbSetTablePassword			ii_ctdbSetTablePassword
#define ctdbSetTablePath			ii_ctdbSetTablePath
#define ctdbSetTablePermission			ii_ctdbSetTablePermission
#define ctdbSetTableSuperFile			ii_ctdbSetTableSuperFile
#define ctdbSetUserTag				ii_ctdbSetUserTag
#define _ctdbStartDebug				ii_ctdbStartDebug
#define ctdbStringToDate			ii_ctdbStringToDate
#define ctdbStringToDateTime			ii_ctdbStringToDateTime
#define ctdbStringToMoney			ii_ctdbStringToMoney
#define ctdbStringToTime			ii_ctdbStringToTime
#define _ctdbSuperClose				ii_ctdbSuperClose
#define _ctdbSuperCreate			ii_ctdbSuperCreate
#define _ctdbSuperDrop				ii_ctdbSuperDrop
#define _ctdbSuperOpen				ii_ctdbSuperOpen
#define _ctdbSuperReopen			ii_ctdbSuperReopen
#define _ctdbSuperSetName			ii_ctdbSuperSetName
#define _ctdbSuperSetPath			ii_ctdbSuperSetPath
#define _ctdbSysTime				ii_ctdbSysTime
#define _ctdbTFRMKEY				ii_ctdbTFRMKEY
#define ctdbTimeCheck				ii_ctdbTimeCheck
#define ctdbTimePack				ii_ctdbTimePack
#define ctdbTimeToString			ii_ctdbTimeToString
#define ctdbTimeUnpack				ii_ctdbTimeUnpack
#define _ctdbUNRCTREE				ii_ctdbUNRCTREE
#define ctdbUnlock				ii_ctdbUnlock
#define _ctdbUnlockDict				ii_ctdbUnlockDict
#define ctdbUnlockRecord			ii_ctdbUnlockRecord
#define ctdbUnlockTable				ii_ctdbUnlockTable
#define ctdbUpdLock				ii_ctdbUpdLock
#define _ctdbWriteDict				ii_ctdbWriteDict
#define ctdbWriteRecord				ii_ctdbWriteRecord
#define _ctdb_FullPath				ii_ctdb_FullPath
#define _ctdb_GetFileExt			ii_ctdb_GetFileExt
#define _ctdb_GetFileName			ii_ctdb_GetFileName
#define _ctdb_GetFilePath			ii_ctdb_GetFilePath
#ifdef CTDB_MIRROR
#define _ctdb_GetMirrorFileName			ii_ctdb_GetMirrorFileName
#endif
#define _ctdbfrmkey				ii_ctdbfrmkey
#define ctdbGetFieldType			ii_ctdbGetFieldType
#define ctdbAddField				ii_ctdbAddField
#define ctdbAddIndex				ii_ctdbAddIndex
#define ctdbAddSegment				ii_ctdbAddSegment
#define ctdbAddSegmentByName			ii_ctdbAddSegmentByName
#define ctdbAddSegmentByNbr			ii_ctdbAddSegmentByNbr
#define ctdbAddSegmentEx			ii_ctdbAddSegmentEx
#define ctdbAllocDatabase			ii_ctdbAllocDatabase
#define ctdbAllocRecord				ii_ctdbAllocRecord
#define ctdbAllocSession			ii_ctdbAllocSession
#define ctdbAllocTable				ii_ctdbAllocTable
#define ctdbDuplicateRecord			ii_ctdbDuplicateRecord
#define ctdbFindActiveDatabase			ii_ctdbFindActiveDatabase
#define ctdbFindActiveDatabaseByUID		ii_ctdbFindActiveDatabaseByUID
#define ctdbFindActiveTable			ii_ctdbFindActiveTable
#define ctdbFindActiveTableByUID		ii_ctdbFindActiveTableByUID
#define ctdbGetActiveTableByUID			ii_ctdbGetActiveTableByUID
#define ctdbGetDatabaseHandle			ii_ctdbGetDatabaseHandle
#define ctdbGetField				ii_ctdbGetField
#define ctdbGetFieldByName			ii_ctdbGetFieldByName
#define ctdbGetFieldHandle			ii_ctdbGetFieldHandle
#define ctdbGetFirstActiveDatabase		ii_ctdbGetFirstActiveDatabase
#define ctdbGetFirstActiveTable			ii_ctdbGetFirstActiveTable
#define ctdbGetIndex				ii_ctdbGetIndex
#define ctdbGetIndexByName			ii_ctdbGetIndexByName
#define ctdbGetIndexByUID			ii_ctdbGetIndexByUID
#define ctdbGetIndexHandle			ii_ctdbGetIndexHandle
#define ctdbGetNextActiveDatabase		ii_ctdbGetNextActiveDatabase
#define ctdbGetNextActiveTable			ii_ctdbGetNextActiveTable
#define ctdbGetRecord				ii_ctdbGetRecord
#define ctdbGetRecordHandle			ii_ctdbGetRecordHandle
#define ctdbGetSegment				ii_ctdbGetSegment
#define ctdbGetSegmentField			ii_ctdbGetSegmentField
#define ctdbGetSegmentPartialField		ii_ctdbGetSegmentPartialField
#define ctdbGetSegmentHandle			ii_ctdbGetSegmentHandle
#define ctdbGetSessionHandle			ii_ctdbGetSessionHandle
#define ctdbGetTable				ii_ctdbGetTable
#define ctdbGetTableHandle			ii_ctdbGetTableHandle
#define ctdbInsField				ii_ctdbInsField
#define ctdbInsFieldByName			ii_ctdbInsFieldByName
#define ctdbInsSegment				ii_ctdbInsSegment
#define ctdbInsSegmentByName			ii_ctdbInsSegmentByName
#define ctdbInsSegmentByNbr			ii_ctdbInsSegmentByNbr
#define ctdbInsSegmentEx			ii_ctdbInsSegmentEx
#define _ctdbSelectHandle			ii_ctdbSelectHandle
#define ctdbGetLockMode				ii_ctdbGetLockMode
#define ctdbMoneyAbs				ii_ctdbMoneyAbs
#define ctdbGetTableOpenMode			ii_ctdbGetTableOpenMode
#define ctdbGetSegmentMode			ii_ctdbGetSegmentMode
#define ctdbGetDefTimeType			ii_ctdbGetDefTimeType
#define ctdbGetTablePermission			ii_ctdbGetTablePermission
#define _ctdbDictGetDatabaseCount		ii_ctdbDictGetDatabaseCount
#define _ctdbDictGetTableCount			ii_ctdbDictGetTableCount
#define ctdbGetDatabaseCount			ii_ctdbGetDatabaseCount
#define _ctdbGetDictCount			ii_ctdbGetDictCount
#define ctdbGetFieldNbr				ii_ctdbGetFieldNbr
#define ctdbGetFieldPrecision			ii_ctdbGetFieldPrecision
#define ctdbGetFieldScale			ii_ctdbGetFieldScale
#define ctdbGetIndexEmptyChar			ii_ctdbGetIndexEmptyChar
#define ctdbGetIndexNbrByName			ii_ctdbGetIndexNbrByName
#define ctdbGetSessionParams			ii_ctdbGetSessionParams
#define ctdbGetRecordNbr			ii_ctdbGetRecordNbr
#define ctdbGetTableCount			ii_ctdbGetTableCount
#define ctdbGetTableDefaultDataExtentSize	ii_ctdbGetTableDefaultDataExtentSize
#define ctdbGetTableDefaultIndexExtentSize	ii_ctdbGetTableDefaultIndexExtentSize
#define ctdbGetTableNbr				ii_ctdbGetTableNbr
#define _ctdbListCount				ii_ctdbListCount
#define _ctdbListIndexOf			ii_ctdbListIndexOf
#define _ctdbListSize				ii_ctdbListSize
#define _ctdbLocateDatabase			ii_ctdbLocateDatabase
#define _ctdbLocateTable			ii_ctdbLocateTable
#define ctdbLockCount				ii_ctdbLockCount
#define ctdbGetIndexUID				ii_ctdbGetIndexUID
#define ctdbBlobGetSize				ii_ctdbBlobGetSize
#define ctdbGetFieldDataLength			ii_ctdbGetFieldDataLength
#define ctdbGetFieldLength			ii_ctdbGetFieldLength
#define ctdbGetFieldNumberByName		ii_ctdbGetFieldNumberByName
#define ctdbGetFieldOffset			ii_ctdbGetFieldOffset
#define ctdbGetFieldSize			ii_ctdbGetFieldSize
#define ctdbGetIndexKeyLength			ii_ctdbGetIndexKeyLength
#define ctdbGetIndexSegmentCount		ii_ctdbGetIndexSegmentCount
#define ctdbGetRecordLength			ii_ctdbGetRecordLength
#define ctdbGetRecordSize			ii_ctdbGetRecordSize
#define ctdbGetTableFieldCount			ii_ctdbGetTableFieldCount
#define ctdbGetTableIndexCount			ii_ctdbGetTableIndexCount
#define _ctdb_lastdelimiter			ii_ctdb_lastdelimiter
#define ctdbBlobCmp				ii_ctdbBlobCmp
#define ctdbGetDefaultIndex			ii_ctdbGetDefaultIndex
#define ctdbGetFieldNumber			ii_ctdbGetFieldNumber
#define _ctdbGetHandleId			ii_ctdbGetHandleId
#define ctdbMoneyCmp				ii_ctdbMoneyCmp
#define ctdbSetSavePoint			ii_ctdbSetSavePoint
#define ctdbSetSingleSavePoint			ii_ctdbSetSingleSavePoint
#define ctdbBlobAlloc				ii_ctdbBlobAlloc
#define ctdbGetFieldData			ii_ctdbGetFieldData
#define _ctdbAllocDict				ii_ctdbAllocDict
#define ctdbAllocField				ii_ctdbAllocField
#define _ctdbAllocFldx				ii_ctdbAllocFldx
#define ctdbAllocIndex				ii_ctdbAllocIndex
#define ctdbAllocSegment			ii_ctdbAllocSegment
#define _ctdbListAlloc				ii_ctdbListAlloc
#define _ctdbListDup				ii_ctdbListDup
#define _ctdbListFree				ii_ctdbListFree
#define _ctdbListDeleteEx			ii_ctdbListDeleteEx
#define ctdbFindLock				ii_ctdbFindLock
#define ctdbLockItem				ii_ctdbLockItem
#define _ctdbAllocLock				ii_ctdbAllocLock
#define _ctdbFreeLock				ii_ctdbFreeLock
#define ctdbGetTableSuperFile			ii_ctdbGetTableSuperFile
#define _ctdbSuperAlloc				ii_ctdbSuperAlloc
#define _ctdbSuperFree				ii_ctdbSuperFree
#define _ctdbFieldTypeName			ii_ctdbFieldTypeName
#define ctdbGetDatabaseName			ii_ctdbGetDatabaseName
#define ctdbGetDatabasePath			ii_ctdbGetDatabasePath
#define ctdbGetDefFloatFormat			ii_ctdbGetDefFloatFormat
#define ctdbGetFieldName			ii_ctdbGetFieldName
#define ctdbGetIndexExtension			ii_ctdbGetIndexExtension
#define ctdbGetSegmentFieldName			ii_ctdbGetSegmentFieldName
#define ctdbGetServerName			ii_ctdbGetServerName
#define ctdbGetTableExtension			ii_ctdbGetTableExtension
#define ctdbGetTableGroupid			ii_ctdbGetTableGroupid
#define ctdbGetTableName			ii_ctdbGetTableName
#define ctdbGetTablePassword			ii_ctdbGetTablePassword
#define ctdbGetTablePath			ii_ctdbGetTablePath
#define ctdbGetUserLogonName			ii_ctdbGetUserLogonName
#define ctdbGetUserPassword			ii_ctdbGetUserPassword
#define _ctdbSuperGetName			ii_ctdbSuperGetName
#define _ctdb_MakeFilePath			ii_ctdb_MakeFilePath
#define _ctdb_stralloc				ii_ctdb_stralloc
#define _ctdb_strdup				ii_ctdb_strdup
#define _ctdb_strlastchar			ii_ctdb_strlastchar
#define ctdbBlobGetData				ii_ctdbBlobGetData
#define ctdbGetDatabaseObjptr			ii_ctdbGetDatabaseObjptr
#define ctdbGetFieldAddress			ii_ctdbGetFieldAddress
#define ctdbGetRecordBuffer			ii_ctdbGetRecordBuffer
#define ctdbGetTableObjptr			ii_ctdbGetTableObjptr
#define _ctdbListItem				ii_ctdbListItem
#define _ctdb_alloc				ii_ctdb_alloc
#define _ctdb_free				ii_ctdb_free
#define _ctdb_realloc				ii_ctdb_realloc
#define ctdbBlobFree				ii_ctdbBlobFree
#define _ctdbClearBit				ii_ctdbClearBit
#define ctdbClearError				ii_ctdbClearError
#define _ctdbFileNameOnly			ii_ctdbFileNameOnly
#define _ctdbFlipBit				ii_ctdbFlipBit
#define ctdbFreeDatabase			ii_ctdbFreeDatabase
#define _ctdbFreeDict				ii_ctdbFreeDict
#define ctdbFreeField				ii_ctdbFreeField
#define ctdbFreeIndex				ii_ctdbFreeIndex
#define ctdbFreeRecord				ii_ctdbFreeRecord
#define ctdbFreeSegment				ii_ctdbFreeSegment
#define ctdbFreeSession				ii_ctdbFreeSession
#define ctdbFreeTable				ii_ctdbFreeTable
#define _ctdbSetBit				ii_ctdbSetBit
#define ctdbCloneTable				ii_ctdbCloneTable
#define ctdbHelloWorld				ii_ctdbHelloWorld	/* CTDB HELLO WORLD */

NINT ctdbDayOfWeek(CTDATE date);
COUNT _ctdbGetDatno(CTHANDLE hTable);
NINT ctdbGetDay(CTDATE date);
NINT ctdbGetHour(CTTIME Time);
NINT ctdbGetMinute(CTTIME Time);
NINT ctdbGetMonth(CTDATE date);
NINT ctdbGetSecond(CTTIME Time);
NINT ctdbGetYear(CTDATE date);
CTBOOL ctdbGetFieldNullFlag(CTHANDLE Handle);
CTBOOL ctdbGetIndexDuplicateFlag(CTHANDLE Handle);
CTBOOL ctdbGetIndexNullFlag(CTHANDLE Handle);
CTBOOL ctdbGetIndexTemporaryFlag(CTHANDLE Handle);
CTBOOL ctdbGetLockActive(pCTDBLOCK pLock);
CTBOOL ctdbGetLogonOnly(CTHANDLE Handle);
CTBOOL ctdbHasNullFieldSupport(CTHANDLE Handle);
CTBOOL ctdbIsActiveDatabase(CTHANDLE Handle);
CTBOOL ctdbIsActiveSession(CTHANDLE Handle);
CTBOOL ctdbIsActiveTable(CTHANDLE Handle);
CTBOOL ctdbIsEditedRecord(CTHANDLE Handle);
CTBOOL ctdbIsExtSegment(CTSEG_MODE SegMode);
CTBOOL ctdbIsLeapYear(CTDATE date);
CTBOOL ctdbIsLockActive(CTHANDLE Handle);
CTBOOL ctdbIsNewRecord(CTHANDLE Handle);
CTBOOL ctdbIsNulField(CTHANDLE Handle, NINT FieldNbr);
CTBOOL ctdbIsTransActive(CTHANDLE Handle);
CTBOOL ctdbIsVariableField(CTHANDLE Handle, NINT FieldNbr);
CTBOOL _ctdbSuperIsExclusive(pCTDBSUPER pSuper);
CTBOOL _ctdbSuperIsOpen(pCTDBSUPER pSuper);
CTBOOL _ctdbTestBit(pUTEXT pArray, NINT BitNumber);
CTCREATE_MODE ctdbGetTableCreateMode(CTHANDLE Handle);
CTDATE_TYPE ctdbGetDefDateType(CTHANDLE Handle);
CTDBKEY ctdbGetIndexKeyType(CTHANDLE Handle);
CTDBRET _ctdbGetNumberOfIndexEntries(COUNT idxno, pULONG pCount);
CTDBRET _ctdbGetNumberOfRecords(COUNT filnum, CTBOOL IsVarLen, pULONG pCount);
CTDBRET _ctdbADDREC(FILNO datno, pVOID recbuf);
CTDBRET _ctdbADDRES(FILNO datno, pVOID resptr, VRLEN varlen);
CTDBRET _ctdbADDVREC(FILNO datno, pVOID recbuf, VRLEN reclen);
CTDBRET _ctdbAVLFILNBR(NINT numfils, pCOUNT pDatno);
CTDBRET ctdbAbort(CTHANDLE Handle);
CTDBRET ctdbAddDatabase(CTHANDLE Handle, pTEXT Name, pTEXT Path);
CTDBRET ctdbAddLock(pCTDBLOCK pLock, FILNO datno, LONG recbyt, CTLOCK_MODE mode);
CTDBRET ctdbAddTable(CTHANDLE Handle, pTEXT Name, pTEXT Path);
CTDBRET ctdbAddTableXtd(CTHANDLE Handle, pTEXT Name, pTEXT PhysicName, pTEXT Path);
CTDBRET ctdbAlterTable(CTHANDLE Handle, NINT Action);
CTDBRET ctdbBegin(CTHANDLE Handle);
CTDBRET ctdbPrepareCommit(CTHANDLE Handle);
CTDBRET ctdbBlobClear(pCTBLOB pBlob);
CTDBRET ctdbBlobSet(pCTBLOB pBlob, cpVOID buffer, VRLEN size);
CTDBRET ctdbBuildTargetKey(CTHANDLE Handle, CTFIND_MODE FindMode, pVOID targetkey, pVRLEN targetlen);
CTDBRET _ctdbCHGICON(COUNT context);
CTDBRET _ctdbCLRFIL(FILNO datno);
CTDBRET _ctdbCLSFIL(FILNO datno);
CTDBRET _ctdbCLSICON(COUNT context);
CTDBRET _ctdbCREDAT(CTHANDLE Handle, FILNO datno, pTEXT filnam, UCOUNT datlen, UCOUNT xtdsiz, COUNT filmod, LONG permmask, pTEXT groupid, pTEXT fileword);
CTDBRET _ctdbCREIFILX(pCTDBTABLE pTable);
CTDBRET _ctdbCREIFILXX(pIFIL ifilptr, pDATOBJ dodaptr, NINT nfields, pTEXT fileword, LONG permmask, pTEXT groupid, pTEXT dext, pTEXT iext);
CTDBRET _ctdbClearDict(pCTDBDICT pDict);
CTDBRET ctdbClearField(CTHANDLE Handle, NINT FieldNbr);
CTDBRET ctdbClearRecord(CTHANDLE Handle);
CTDBRET ctdbClearTableSuperFile(CTHANDLE Handle);
CTDBRET ctdbCloseAll(CTHANDLE Handle);
CTDBRET _ctdbCloseDict(pCTDBDICT pDict);
CTDBRET ctdbCloseTable(CTHANDLE Handle);
CTDBRET ctdbCommit(CTHANDLE Handle);
CTDBRET ctdbConnect(CTHANDLE Handle, pTEXT Name);
CTDBRET ctdbCopyRecordBuffer(CTHANDLE pSource, CTHANDLE pDest);
CTDBRET ctdbCreateDatabase(CTHANDLE Handle, pTEXT Name, pTEXT Path);
CTDBRET _ctdbCreateDict(pCTDBDICT pDict, pTEXT FileName, CTBOOL superfile);
CTDBRET ctdbCreateSession(CTHANDLE Handle, pTEXT dbengine, pTEXT userid, pTEXT password);
CTDBRET ctdbCreateTable(CTHANDLE Handle, pTEXT TableName, CTCREATE_MODE CreateMode);
CTDBRET ctdbCurrentDate(pCTDATE pDate);
CTDBRET ctdbCurrentDateTime(pCTDATETIME pDateTime);
CTDBRET ctdbCurrentTime(pCTTIME pTime);
CTDATETIME ctdbServerDateTime(CTHANDLE hSession);
CTDBRET _ctdbDELFIL(FILNO datno);
CTDBRET _ctdbDELREC(FILNO datno);
CTDBRET _ctdbDELRFIL(FILNO datno);
CTDBRET _ctdbDELVREC(FILNO datno);
CTDBRET ctdbDateCheck(NINT year, NINT month, NINT day);
CTDBRET ctdbDatePack(pCTDATE pDate, NINT year, NINT month, NINT day);
CTDBRET ctdbDateTimeGetDate(CTDATETIME DateTime, pCTDATE pDate);
CTDBRET ctdbDateTimeGetTime(CTDATETIME DateTime, pCTTIME pTime);
CTDBRET ctdbDateTimePack(pCTDATETIME pDateTime, NINT year, NINT month, NINT day, NINT hour, NINT minute, NINT second);
CTDBRET ctdbDateTimeSetDate(pCTDATETIME pDateTime, CTDATE Date);
CTDBRET ctdbDateTimeSetTime(pCTDATETIME pDateTime, CTTIME Time);
CTDBRET ctdbDateTimeToString(CTDATETIME DateTime, CTDATE_TYPE DateType, CTTIME_TYPE TimeType, pTEXT pStr, VRLEN size);
CTDBRET ctdbDateTimeUnpack(CTDATETIME DateTime, pNINT pYear, pNINT pMonth, pNINT pDay, pNINT pHour, pNINT pMinute, pNINT pSecond);
CTDBRET ctdbDateToString(CTDATE date, CTDATE_TYPE DateType, pTEXT pStr, VRLEN size);
CTDBRET ctdbDateUnpack(CTDATE date, pNINT pyear, pNINT pmonth, pNINT pday);
CTDBRET ctdbDelField(CTHANDLE Handle, NINT Index);
CTDBRET ctdbDelFieldByName(CTHANDLE Handle, pTEXT FieldName);
CTDBRET ctdbDelIndex(CTHANDLE Handle, NINT IndexNumber);
CTDBRET ctdbDelLock(pCTDBLOCK pLock, FILNO datno, LONG recbyt);
CTDBRET ctdbDelSegment(CTHANDLE Handle, NINT SegNumber);
CTDBRET ctdbDelSegmentEx(CTHANDLE Handle);
CTDBRET ctdbDeleteDatabase(CTHANDLE Handle, pTEXT Name);
CTDBRET _ctdbDeleteDict(pCTDBDICT pDict);
CTDBRET ctdbDeleteRecord(CTHANDLE Handle);
CTDBRET ctdbDeleteTable(CTHANDLE Handle, pTEXT TableName, pTEXT Password);
CTDBRET _ctdbDictAddAllIndex(CTHANDLE hDatabase, CTHANDLE hTable);
CTDBRET _ctdbDictAddDatabase(CTHANDLE hSession, pTEXT name, pTEXT path, CTBOOL superfile);
CTDBRET _ctdbDictAddIndex(CTHANDLE hDatabase, CTHANDLE hTable, NINT indexno);
CTDBRET _ctdbDictAddTable(CTHANDLE hDatabase, pTEXT name, pTEXT path, pTEXT fext, pTEXT mirr_name, pTEXT mirr_path, UCOUNT dict_mark);
CTDBRET _ctdbDictDropAllIndex(CTHANDLE hDatabase, CTHANDLE hTable);
CTDBRET _ctdbDictDropDatabase(CTHANDLE hSession, pTEXT name);
CTDBRET _ctdbDictDropIndex(CTHANDLE hDatabase, CTHANDLE hTable, pTEXT name);
CTDBRET _ctdbDictDropTable(CTHANDLE hDatabase, pTEXT name);
CTDBRET _ctdbDictFindDatabase(CTHANDLE hSession, pTEXT name, pDICTDATA pData);
CTDBRET _ctdbDictFindDatabaseByUID(CTHANDLE hSession, ULONG uid, pDICTDATA pData);
CTDBRET _ctdbDictFindIndex(CTHANDLE hDatabase, pTEXT name, pDICTDATA pData);
CTDBRET _ctdbDictFindIndexByUID(CTHANDLE hDatabase, ULONG uid, pDICTDATA pData);
CTDBRET _ctdbDictFindTable(CTHANDLE hDatabase, pTEXT name, pDICTDATA pData);
CTDBRET _ctdbDictFindTableByUID(CTHANDLE hDatabase, ULONG uid, pDICTDATA pData);
CTDBRET _ctdbDictFirstDatabase(CTHANDLE hSession, pDICTDATA pData);
CTDBRET _ctdbDictFirstTable(CTHANDLE hDatabase, pDICTDATA pData);
CTDBRET _ctdbDictGetDatabaseUID(CTHANDLE hSession, pTEXT name, pULONG puid);
CTDBRET _ctdbDictGetTableUID(CTHANDLE hDatabase, pTEXT name, pULONG puid);
CTDBRET _ctdbDictNextDatabase(CTHANDLE hSession, pDICTDATA pData);
CTDBRET _ctdbDictNextTable(CTHANDLE hDatabase, pDICTDATA pData);
CTDBRET _ctdbDictReserveIndex(CTHANDLE hDatabase, pTEXT name, pULONG puid);
CTDBRET _ctdbDictReserveTable(CTHANDLE hDatabase, pTEXT name, pULONG puid);
CTDBRET _ctdbDictUpdateIndex(CTHANDLE hDatabase, CTHANDLE hTable);
CTDBRET ctdbDisconnect(CTHANDLE Handle);
CTDBRET ctdbDisconnectAll(CTHANDLE Handle);
CTDBRET ctdbDropDatabase(CTHANDLE Handle, pTEXT Name);
CTDBRET ctdbDropTable(CTHANDLE Handle, pTEXT TableName);
CTDBRET _ctdbDumpDict(CTHANDLE hSession, CTHANDLE hDatabase);
CTDBRET _ctdbEndDebug(pCTDBDBUG hDebug);
CTDBRET _ctdbFINDREC(FILNO datno, COUNT idxno, pVOID target, pVOID recbuf, pLONG pOffset, NINT FindMode);
CTDBRET _ctdbFRESET(void);
CTDBRET _ctdbFileExist(pTEXT Path, pTEXT Name, pTEXT Ext);
CTDBRET ctdbFindDatabase(CTHANDLE Handle, pTEXT Name, pTEXT Path, VRLEN PathSize);
CTDBRET ctdbFindDatabaseByUID(CTHANDLE Handle, ULONG uid, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
CTDBRET _ctdbFindDict(pCTDBDICT pDict, ULONG Type, ULONG Status, pTEXT Name);
CTDBRET _ctdbFindDictByUID(pCTDBDICT pDict, ULONG uid);
CTDBRET ctdbFindRecord(CTHANDLE Handle, CTFIND_MODE FindMode);
CTBOOL  ctdbLocateRecord(CTHANDLE Handle, CTLOC_MODE LocateMode);
CTDBRET ctdbSetRecordCriteria(CTHANDLE Handle, CTLOC_MODE LocateMode);
CTDBRET ctdbUpdateRecordCriteria(CTHANDLE Handle, CTLOC_MODE LocateMode);
CTHANDLE ctdbGetBestIndex(CTHANDLE Handle, pCTDBLIST fieldNameList, CTLOC_MODE LocateMode);
CTDBRET ctdbAddLocateCriteria(CTHANDLE Handle, CTSTRING LocateFieldName, CTSTRING LocateFieldValue);
CTDBRET ctdbFindTable(CTHANDLE Handle, pTEXT Name, pTEXT Path, VRLEN PathSize);
CTDBRET ctdbFindTableByUID(CTHANDLE Handle, ULONG uid, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
CTDBRET ctdbFindTarget(CTHANDLE Handle, pVOID target, CTFIND_MODE FindMode);
CTDBRET ctdbFirstDatabase(CTHANDLE Handle, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
CTDBRET _ctdbFirstDict(pCTDBDICT pDict, ULONG Type, ULONG Status);
CTDBRET ctdbFirstRecord(CTHANDLE Handle);
CTDBRET ctdbFirstTable(CTHANDLE Handle, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
CTDBRET ctdbFloatToMoney(CTFLOAT value, pCTMONEY pMoney);
CTDBRET _ctdbGETCURP(FILNO datno, pLONG pOffset);
CTDBRET _ctdbGETDODA(FILNO datno, ppDATOBJ ppDoda, pVRLEN pSize);
CTDBRET _ctdbGETFIL(FILNO datno, COUNT mode, pLONG pInfo);
CTDBRET _ctdbGETIFIL(FILNO datno, ppIFIL ppIfil, pVRLEN pSize);
CTDBRET _ctdbGETRES(FILNO datno, pVOID resptr, pVOID buffer, VRLEN bufsize, COUNT resmode);
CTDBRET _ctdbGETSCHEMA(FILNO datno, ppConvMap ppSchema, pVRLEN pSize);
CTDBRET _ctdbGETVLEN(FILNO datno, pVRLEN pLen);
CTDBRET ctdbGetActiveDatabaseUID(CTHANDLE Handle, pULONG puid);
CTDBRET ctdbGetActiveTableUID(CTHANDLE Handle, pULONG puid);
CTDBRET ctdbGetDatabaseUID(CTHANDLE Handle, pTEXT Name, pULONG puid);
CTDBRET _ctdbGetDict(pCTDBDICT pDict, pDICTDATA pData);
CTDBRET _ctdbGetDictUID(pCTDBDICT pDict, pULONG puid);
CTDBRET ctdbGetError(CTHANDLE Handle);
CTDBRET ctdbGetFieldAsBinary(CTHANDLE Handle, NINT FieldNbr, pVOID pValue, VRLEN size);
CTDBRET ctdbGetFieldAsBlob(CTHANDLE Handle, NINT FieldNbr, pCTBLOB pValue);
CTDBRET ctdbGetFieldAsBool(CTHANDLE Handle, NINT FieldNbr, pCTBOOL pValue);
CTDBRET ctdbGetFieldAsDate(CTHANDLE Handle, NINT FieldNbr, pCTDATE pValue);
CTDBRET ctdbGetFieldAsDateTime(CTHANDLE Handle, NINT FieldNbr, pCTDATETIME pValue);
CTDBRET ctdbGetFieldAsFloat(CTHANDLE Handle, NINT FieldNbr, pCTFLOAT pValue);
CTDBRET ctdbGetFieldAsMoney(CTHANDLE Handle, NINT FieldNbr, pCTMONEY pValue);
CTDBRET ctdbGetFieldAsSigned(CTHANDLE Handle, NINT FieldNbr, pCTSIGNED pValue);
CTDBRET ctdbGetFieldAsString(CTHANDLE Handle, NINT FieldNbr, CTSTRING pValue, VRLEN size);
CTDBRET ctdbGetFieldAsTime(CTHANDLE Handle, NINT FieldNbr, pCTTIME pValue);
CTDBRET ctdbGetFieldAsUnsigned(CTHANDLE Handle, NINT FieldNbr, pCTUNSIGNED pValue);
CTDBRET ctdbGetFieldProperties(CTHANDLE Handle, ppTEXT FieldName, pCTDBTYPE pType, pVRLEN pLength);
CTDBRET _ctdbGetFldx(CTHANDLE hTable);
CTDBRET ctdbGetIndexNbr(CTHANDLE Handle, pVRLEN pNumber);
CTDBRET ctdbGetRecordCount(CTHANDLE Handle, pULONG pCount);
CTDBRET ctdbGetRecordPos(CTHANDLE Handle, pLONG pOffset);
CTDBRET ctdbGetRecordKeyPos(CTHANDLE Handle, pCTOFFSET pPosition);
CTDBRET ctdbGetSegmentNbr(CTHANDLE Handle, pVRLEN pNumber);
CTDBRET ctdbGetSessionPath(CTHANDLE Handle, pTEXT Path, VRLEN PathSize);
CTDBRET ctdbGetTableUID(CTHANDLE Handle, pTEXT Name, pULONG puid);
CTDBRET ctdbGetUserTag(CTHANDLE Handle, ppVOID tagptr);
CTDBRET _ctdbIconAdd(CTHANDLE Handle, pNINT pIcon);
CTDBRET _ctdbIconAlloc(CTHANDLE Handle);
CTDBRET _ctdbIconFree(CTHANDLE Handle);
CTDBRET _ctdbIconReset(CTHANDLE Handle);
CTDBRET _ctdbIconSwitch(CTHANDLE Handle, pNINT pIcon);
CTDBRET _ctdbLKISAM(COUNT mode);
CTDBRET _ctdbLOKREC(FILNO datno, COUNT mode, LONG recbyt);
CTDBRET ctdbLastRecord(CTHANDLE Handle);
CTDBRET _ctdbListAdd(pCTDBLIST hList, pVOID Item);
CTDBRET _ctdbListClear(pCTDBLIST hList);
CTDBRET _ctdbListDelete(pCTDBLIST hList, NINT Index);
CTDBRET _ctdbListDeleteEx(pCTDBLIST hList, pVOID Item);
CTDBRET _ctdbListExchange(pCTDBLIST hList, NINT Index1, NINT Index2);
CTDBRET _ctdbListExpand(pCTDBLIST hList);
CTDBRET _ctdbListInsert(pCTDBLIST hList, NINT Index, pVOID Item);
CTDBRET _ctdbListMove(pCTDBLIST hList, NINT CurIndex, NINT NewIndex);
CTDBRET _ctdbListReplace(pCTDBLIST hList, NINT Index, pVOID Item);
CTDBRET ctdbLock(CTHANDLE Handle, CTLOCK_MODE mode);
CTDBRET ctdbLockRecord(CTHANDLE Handle, CTLOCK_MODE mode);
CTDBRET ctdbLogon(CTHANDLE Handle, pTEXT dbengine, pTEXT userid, pTEXT password);
CTDBRET ctdbLogout(CTHANDLE Handle);
CTDBRET ctdbLongToMoney(CTSIGNED value, pCTMONEY pMoney);
CTDBRET _ctdbMOVREC(FILNO datno, COUNT idxno, pVOID recbuf, pLONG pOffset, NINT Direction);
CTDBRET _ctdbMOVSET(FILNO datno, COUNT idxno, pVOID target, pVOID recbuf, COUNT siglen, pLONG pOffset, NINT Direction);
CTDBRET ctdbMoneyAdd(CTMONEY left, CTMONEY right, pCTMONEY pResult);
CTDBRET ctdbMoneyDiv(CTMONEY left, CTMONEY right, pCTMONEY pResult);
CTDBRET ctdbMoneyMul(CTMONEY left, CTMONEY right, pCTMONEY pResult);
CTDBRET ctdbMoneySub(CTMONEY left, CTMONEY right, pCTMONEY pResult);
CTDBRET ctdbMoneyToFloat(CTMONEY money, pCTFLOAT pValue);
CTDBRET ctdbMoneyToLong(CTMONEY money, pCTSIGNED pValue);
CTDBRET ctdbMoneyToString(CTMONEY money, pTEXT pStr, VRLEN size);
CTDBRET ctdbMoveField(CTHANDLE Handle, NINT newIndex);
CTDBRET ctdbNextDatabase(CTHANDLE Handle, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
CTDBRET _ctdbNextDict(pCTDBDICT pDict, ULONG Type, ULONG Status);
CTDBRET ctdbNextRecord(CTHANDLE Handle);
CTDBRET ctdbNextTable(CTHANDLE Handle, pTEXT Name, VRLEN NameSize, pTEXT Path, VRLEN PathSize);
CTDBRET _ctdbOPNFIL(CTHANDLE Handle, FILNO datno, pTEXT filnam, COUNT filmod);
CTDBRET _ctdbOPNICON(FILNO datno, pCOUNT pContext);
CTDBRET _ctdbOPNRFILX(CTHANDLE pTable, pTEXT filnam, NINT filmod, pTEXT fileword, pTEXT dext, pCOUNT pdatno);
CTDBRET _ctdbOpenDict(pCTDBDICT pDict, pTEXT FileName, CTBOOL OpenExclusive);
CTDBRET ctdbOpenTable(CTHANDLE Handle, pTEXT TableName, CTOPEN_MODE OpenMode);
CTDBRET ctdbOpenTableByUID(CTHANDLE Handle, ULONG uid, CTOPEN_MODE OpenMode);
CTDBRET _ctdbPRMIIDX(pIFIL ifilptr);
CTDBRET _ctdbTMPIIDX(pIFIL ifilptr);
CTDBRET ctdbPrevRecord(CTHANDLE Handle);
CTDBRET _ctdbPutDict(pCTDBDICT pDict, pDICTDATA pData);
CTDBRET _ctdbPutFldx(CTHANDLE hTable);
CTDBRET _ctdbRBLIFILX(CTHANDLE Handle, pIFIL ifilptr, pTEXT datext, pTEXT idxext, LONG permmask, pTEXT groupid, pTEXT fileword);
CTDBRET _ctdbREDIREC(FILNO datno, LONG offset, pVOID recbuf);
CTDBRET _ctdbREDIVREC(FILNO datno, LONG offset, pVOID recbuf, pVRLEN pLen);
CTDBRET _ctdbREDVREC(FILNO datno, pVOID recbuf, VRLEN recsize);
CTDBRET _ctdbREGCTREE(pTEXT regid);
CTDBRET _ctdbRENIFIL(pIFIL ifilptr);
CTDBRET _ctdbRWTREC(FILNO datno, pVOID recbuf);
CTDBRET _ctdbRWTVREC(FILNO datno, pVOID recbuf, VRLEN reclen);
CTDBRET _ctdbRWTPREC(FILNO datno, pVOID recbuf, VRLEN reclen);
CTDBRET ctdbReadRecord(CTHANDLE Handle);
CTDBRET ctdbRecLock(pCTDBLOCK pLock, FILNO datno, LONG recbyt, CTLOCK_MODE mode);
CTDBRET ctdbRecUnlock(pCTDBLOCK pLock, FILNO datno, LONG recbyt);
CTDBRET ctdbRecordSetOff(CTHANDLE Handle);
CTDBRET ctdbRecordSetOn(CTHANDLE Handle, NINT siglen);
CTDBRET ctdbReleaseLocks(pCTDBLOCK pLock);
CTDBRET ctdbReleaseTableLocks(pCTDBLOCK pLock, FILNO datno);
CTDBRET _ctdbRemoveDict(pCTDBDICT pDict, ULONG type, ULONG Status, pTEXT Name);
CTDBRET _ctdbRemoveDictByUID(pCTDBDICT pDict, ULONG uid);
CTDBRET ctdbReopenDict(pCTDBDICT pDict, CTBOOL OpenExclusive);
CTDBRET ctdbResetAll(CTHANDLE Handle);
CTDBRET ctdbResetRecord(CTHANDLE Handle);
CTDBRET ctdbRestoreSavePoint(CTHANDLE Handle, NINT SavePoint);
CTDBRET _ctdbSETCURI(FILNO datno, LONG offset, pVOID recbuf, VRLEN reclen);
CTDBRET _ctdbSWTCTREE(pTEXT regid);
CTDBRET ctdbSeekRecord(CTHANDLE Handle, LONG offset);
CTDBRET ctdbSetDatabaseObjptr(CTHANDLE Handle, pVOID ptr);
CTDBRET ctdbSetDefDateType(CTHANDLE Handle, CTDATE_TYPE DateType);
CTDBRET ctdbSetDefFloatFormat(CTHANDLE Handle, pTEXT format);
CTDBRET ctdbSetDefTimeType(CTHANDLE Handle, CTTIME_TYPE TimeType);
CTDBRET ctdbSetDefaultIndex(CTHANDLE Handle, NINT indexno);
CTDBRET ctdbSetEditedRecord(CTHANDLE Handle, CTBOOL flag);
CTDBRET ctdbSetError(CTHANDLE Handle, CTDBRET ErrorCode);
CTDBRET ctdbSetFieldAsBinary(CTHANDLE Handle, NINT FieldNbr, pVOID value, VRLEN size);
CTDBRET ctdbSetFieldAsBlob(CTHANDLE Handle, NINT FieldNbr, pCTBLOB pValue);
CTDBRET ctdbSetFieldAsBool(CTHANDLE Handle, NINT FieldNbr, CTBOOL Value);
CTDBRET ctdbSetFieldAsDate(CTHANDLE Handle, NINT FieldNbr, CTDATE Value);
CTDBRET ctdbSetFieldAsDateTime(CTHANDLE Handle, NINT FieldNbr, CTDATETIME Value);
CTDBRET ctdbSetFieldAsFloat(CTHANDLE Handle, NINT FieldNbr, CTFLOAT Value);
CTDBRET ctdbSetFieldAsMoney(CTHANDLE Handle, NINT FieldNbr, CTMONEY Value);
CTDBRET ctdbSetFieldAsSigned(CTHANDLE Handle, NINT FieldNbr, CTSIGNED Value);
CTDBRET ctdbSetFieldAsString(CTHANDLE Handle, NINT FieldNbr, CTSTRING Value);
CTDBRET ctdbSetFieldAsTime(CTHANDLE Handle, NINT FieldNbr, CTTIME Value);
CTDBRET ctdbSetFieldAsUnsigned(CTHANDLE Handle, NINT FieldNbr, CTUNSIGNED Value);
CTDBRET ctdbSetFieldLength(CTHANDLE Handle, VRLEN len);
CTDBRET ctdbSetFieldName(CTHANDLE Handle, pTEXT name);
CTDBRET ctdbSetFieldNullFlag(CTHANDLE Handle, CTBOOL flag);
CTDBRET ctdbSetFieldPrecision(CTHANDLE Handle, NINT fprec);
CTDBRET ctdbSetFieldProperties(CTHANDLE Handle, pTEXT FieldName, CTDBTYPE Type, VRLEN Length);
CTDBRET ctdbSetFieldScale(CTHANDLE Handle, NINT fscale);
CTDBRET ctdbSetFieldType(CTHANDLE Handle, CTDBTYPE type);
CTBOOL ctdbIsFieldNumeric(CTHANDLE Handle);
CTDBRET ctdbSetIndexDuplicateFlag(CTHANDLE Handle, CTBOOL DupFlag);
CTDBRET ctdbSetIndexEmptyChar(CTHANDLE Handle, NINT EmptyChar);
CTDBRET ctdbSetIndexExtension(CTHANDLE Handle, pTEXT ext);
CTDBRET ctdbSetIndexKeyType(CTHANDLE Handle, CTDBKEY KeyType);
CTDBRET ctdbSetIndexNullFlag(CTHANDLE Handle, CTBOOL NulFlag);
CTDBRET ctdbSetIndexTemporaryFlag(CTHANDLE Handle, CTBOOL TempFlag);
CTDBRET ctdbSetIndexCndxExpr(CTHANDLE Handle, pTEXT conditionExpr);
CTDBRET ctdbSetLockActive(pCTDBLOCK pLock, CTBOOL flag);
CTDBRET ctdbSetLockMode(pCTDBLOCK pLock, CTLOCK_MODE mode);
CTDBRET ctdbSetLogonOnly(CTHANDLE Handle, CTBOOL flag);
CTDBRET ctdbSetNewRecord(CTHANDLE Handle, CTBOOL flag);
CTDBRET ctdbSetRecordOffset(CTHANDLE Handle, LONG offset);
CTDBRET ctdbSetRecordPos(CTHANDLE Handle, LONG offset);
CTDBRET ctdbSetSegmentMode(CTHANDLE Handle, CTSEG_MODE SegMode);
CTDBRET ctdbSetSessionParams(CTHANDLE Handle, CTSESSION_PARAM ParamType, NINT value);
CTDBRET ctdbSetSessionPath(CTHANDLE Handle, pTEXT Path);
CTDBRET ctdbSetTableDefaultDataExtentSize(CTHANDLE Handle, NINT size);
CTDBRET ctdbSetTableDefaultIndexExtentSize(CTHANDLE Handle, NINT size);
CTDBRET ctdbSetTableExtension(CTHANDLE Handle, pTEXT fExt);
CTDBRET ctdbSetTableGroupid(CTHANDLE Handle, pTEXT groupid);
CTDBRET ctdbSetTableObjptr(CTHANDLE Handle, pVOID ptr);
CTDBRET ctdbSetTablePassword(CTHANDLE Handle, pTEXT password);
CTDBRET ctdbSetTablePath(CTHANDLE Handle, pTEXT Path);
CTDBRET ctdbSetTablePermission(CTHANDLE Handle, LONG permmask);
CTDBRET ctdbSetTableSuperFile(CTHANDLE Handle, pCTDBSUPER pSuper);
CTDBRET ctdbSetTableUID(CTHANDLE Handle, pTEXT Name, ULONG uid);
CTDBRET _ctdbStartDebug(pCTDBDBUG hDebug, pTEXT fileName);
CTDBRET ctdbStringToDate(pTEXT pStr, CTDATE_TYPE DateType, pCTDATE pDate);
CTDBRET ctdbStringToDateTime(pTEXT pStr, pCTDATETIME DateTime, CTDATE_TYPE DateType, CTTIME_TYPE TimeType);
CTDBRET ctdbStringToMoney(pTEXT pStr, pCTMONEY pMoney);
CTDBRET ctdbStringToTime(pTEXT pStr, CTTIME_TYPE TimeType, pCTTIME pTime);
CTDBRET _ctdbSuperClose(pCTDBSUPER pSuper);
CTDBRET _ctdbSuperCreate(pCTDBSUPER pSuper);
CTDBRET _ctdbSuperDrop(pCTDBSUPER pSuper);
CTDBRET _ctdbSuperOpen(pCTDBSUPER pSuper, CTBOOL exclusive);
CTDBRET _ctdbSuperReopen(pCTDBSUPER pSuper, CTBOOL exclusive);
CTDBRET _ctdbSuperSetName(pCTDBSUPER pSuper, pTEXT path, pTEXT name, pTEXT ext);
CTDBRET _ctdbSuperSetPath(pCTDBSUPER pSuper, pTEXT path);
CTDBRET _ctdbSysTime(pCOUNT pYear, pCOUNT pMonth, pCOUNT pDay, pCOUNT pHour, pCOUNT pMinute, pCOUNT pSecond);
CTDBRET _ctdbTFRMKEY(FILNO keyno, pVOID target);
CTDBRET ctdbTimeCheck(NINT hour, NINT minute, NINT second);
CTDBRET ctdbTimePack(pCTTIME pTime, NINT hour, NINT minute, NINT second);
CTDBRET ctdbTimeToString(CTTIME Time, CTTIME_TYPE TimeType, pTEXT pStr, VRLEN size);
CTDBRET ctdbTimeUnpack(CTTIME Time, pNINT hour, pNINT minute, pNINT second);
CTDBRET _ctdbUNRCTREE(pTEXT regid);
CTDBRET ctdbUnlock(CTHANDLE Handle);
CTDBRET _ctdbUnlockDict(pCTDBDICT pDict);
CTDBRET ctdbUnlockRecord(CTHANDLE Handle);
CTDBRET ctdbUnlockTable(CTHANDLE Handle);
CTDBRET ctdbUpdLock(pCTDBLOCK pLock, FILNO datno, LONG recbyt, CTLOCK_MODE mode);
CTDBRET _ctdbWriteDict(pCTDBDICT pDict);
CTDBRET ctdbWriteRecord(CTHANDLE Handle);
CTDBRET _ctdb_FullPath(pTEXT Path, VRLEN PathSize);
CTDBRET _ctdb_GetFileExt(pTEXT FileName, pTEXT pExt, VRLEN ExtSize);
CTDBRET _ctdb_GetFileName(pTEXT FileName, pTEXT pName, VRLEN NameSize);
CTDBRET _ctdb_GetFilePath(pTEXT FileName, pTEXT pPath, VRLEN PathSize);
#ifdef CTDB_MIRROR
CTDBRET _ctdb_GetMirrorFileName(pTEXT FileName, pTEXT pName, VRLEN NameSize);
#endif
CTDBRET _ctdbfrmkey(COUNT idxno, pUTEXT recbuf, pTEXT key, LONG pntr, VRLEN datlen);
CTDBTYPE ctdbGetFieldType(CTHANDLE Handle);
CTHANDLE ctdbAddField(CTHANDLE Handle, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength);
CTHANDLE ctdbAddIndex(CTHANDLE Handle, pTEXT name, CTDBKEY key_type, CTBOOL AllowDuplicates, CTBOOL NullFlag);
CTHANDLE ctdbAddSegment(CTHANDLE Handle, CTHANDLE FieldHandle, CTSEG_MODE SegMode);
CTHANDLE ctdbAddSegmentByName(CTHANDLE Handle, NINT IndexNbr, pTEXT FieldName, CTSEG_MODE SegMode);
CTHANDLE ctdbAddSegmentByNbr(CTHANDLE Handle, NINT IndexNbr, NINT FieldNbr, CTSEG_MODE SegMode);
CTHANDLE ctdbAddSegmentEx(CTHANDLE Handle, NINT offset, NINT length, CTSEG_MODE SegMode);
CTHANDLE ctdbAllocDatabase(CTHANDLE Handle);
CTHANDLE ctdbAllocRecord(CTHANDLE Handle);
CTHANDLE ctdbAllocSession(CTSESSION_TYPE SessionType);
CTHANDLE ctdbAllocTable(CTHANDLE Handle);
CTHANDLE ctdbDuplicateRecord(CTHANDLE Handle);
CTHANDLE ctdbFindActiveDatabase(CTHANDLE Handle, pTEXT Name);
CTHANDLE ctdbFindActiveDatabaseByUID(CTHANDLE Handle, ULONG uid);
CTHANDLE ctdbFindActiveTable(CTHANDLE Handle, pTEXT Name);
CTHANDLE ctdbFindActiveTableByUID(CTHANDLE Handle, ULONG uid);
CTHANDLE ctdbGetActiveTableByUID(CTHANDLE Handle, ULONG uid);
CTHANDLE ctdbGetDatabaseHandle(CTHANDLE Handle);
CTHANDLE ctdbGetField(CTHANDLE Handle, NINT Index);
CTHANDLE ctdbGetFieldByName(CTHANDLE Handle, pTEXT FieldName);
CTHANDLE ctdbGetFieldHandle(CTHANDLE Handle);
CTHANDLE ctdbGetFirstActiveDatabase(CTHANDLE Handle, pVRLEN pScanIndex);
CTHANDLE ctdbGetFirstActiveTable(CTHANDLE Handle, pVRLEN pScanRec);
CTHANDLE ctdbGetIndex(CTHANDLE Handle, NINT IndexNumber);
CTHANDLE ctdbGetIndexByName(CTHANDLE Handle, pTEXT name);
CTHANDLE ctdbGetIndexByUID(CTHANDLE Handle, ULONG uid);
CTHANDLE ctdbGetIndexHandle(CTHANDLE Handle);
CTHANDLE ctdbGetNextActiveDatabase(CTHANDLE Handle, pVRLEN pScanIndex);
CTHANDLE ctdbGetNextActiveTable(CTHANDLE Handle, pVRLEN pScanRec);
CTHANDLE ctdbGetRecord(CTHANDLE Handle, NINT index);
CTHANDLE ctdbGetRecordHandle(CTHANDLE Handle);
CTHANDLE ctdbGetSegment(CTHANDLE Handle, NINT SegNumber);
CTHANDLE ctdbGetSegmentField(CTHANDLE Handle);
CTHANDLE ctdbGetSegmentPartialField(CTHANDLE Handle);
CTHANDLE ctdbGetSegmentHandle(CTHANDLE Handle);
CTHANDLE ctdbGetSessionHandle(CTHANDLE Handle);
CTHANDLE ctdbGetTable(CTHANDLE Handle, NINT index);
CTHANDLE ctdbGetTableHandle(CTHANDLE Handle);
CTHANDLE ctdbInsField(CTHANDLE Handle, NINT Index, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength);
CTHANDLE ctdbInsFieldByName(CTHANDLE Handle, pTEXT FieldIndex, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength);
CTHANDLE ctdbInsSegment(CTHANDLE Handle, NINT SegNumber, CTHANDLE FieldHandle, CTSEG_MODE SegMode);
CTHANDLE ctdbInsSegmentByName(CTHANDLE Handle, NINT IndexNbr, NINT SegNumber, pTEXT FieldName, CTSEG_MODE SegMode);
CTHANDLE ctdbInsSegmentByNbr(CTHANDLE Handle, NINT IndexNbr, NINT SegNumber, NINT FieldNbr, CTSEG_MODE SegMode);
CTHANDLE ctdbInsSegmentEx(CTHANDLE Handle, NINT SegNumber, NINT offset, NINT length, CTSEG_MODE SegMode);
CTHANDLE _ctdbSelectHandle(CTHANDLE Handle, NINT HandleId);
CTLOCK_MODE ctdbGetLockMode(pCTDBLOCK pLock);
CTMONEY ctdbMoneyAbs(CTMONEY left);
CTOPEN_MODE ctdbGetTableOpenMode(CTHANDLE Handle);
CTSEG_MODE ctdbGetSegmentMode(CTHANDLE Handle);
CTTIME_TYPE ctdbGetDefTimeType(CTHANDLE Handle);
LONG ctdbGetTablePermission(CTHANDLE Handle);
NINT _ctdbDictGetDatabaseCount(CTHANDLE hSession);
NINT _ctdbDictGetTableCount(CTHANDLE hDatabase);
NINT ctdbGetDatabaseCount(CTHANDLE Handle);
NINT _ctdbGetDictCount(pCTDBDICT pDict, ULONG Type, ULONG Status);
NINT ctdbGetFieldNbr(CTHANDLE Handle);
NINT ctdbGetFieldPrecision(CTHANDLE Handle);
NINT ctdbGetFieldScale(CTHANDLE Handle);
NINT ctdbGetIndexEmptyChar(CTHANDLE Handle);
NINT ctdbGetIndexNbrByName(CTHANDLE Handle, pTEXT name);
NINT ctdbGetSessionParams(CTHANDLE Handle, CTSESSION_PARAM ParamType);
NINT ctdbGetRecordNbr(CTHANDLE Handle);
NINT ctdbGetTableCount(CTHANDLE Handle);
NINT ctdbGetTableDefaultDataExtentSize(CTHANDLE Handle);
NINT ctdbGetTableDefaultIndexExtentSize(CTHANDLE Handle);
NINT ctdbGetTableNbr(CTHANDLE Handle);
NINT _ctdbListCount(pCTDBLIST hList);
NINT _ctdbListIndexOf(pCTDBLIST hList, pVOID Item);
NINT _ctdbListSize(pCTDBLIST hList);
NINT _ctdbLocateDatabase(pCTDBSESSION pSession, pTEXT Name);
NINT _ctdbLocateTable(pCTDBDATABASE pDatabase, pTEXT Name);
NINT ctdbLockCount(pCTDBLOCK pLock);
CTDBRET ctdbGetIndexUID(CTHANDLE Handle, pTEXT Name, pULONG puid);
VRLEN ctdbBlobGetSize(pCTBLOB pBlob);
VRLEN ctdbGetFieldDataLength(CTHANDLE Handle, NINT FieldNbr);
VRLEN ctdbGetFieldLength(CTHANDLE Handle);
NINT ctdbGetFieldNumberByName(CTHANDLE Handle, pTEXT FieldName);
VRLEN ctdbGetFieldOffset(CTHANDLE Handle, NINT FieldNbr);
VRLEN ctdbGetFieldSize(CTHANDLE Handle, NINT FieldNbr);
VRLEN ctdbGetIndexKeyLength(CTHANDLE Handle);
VRLEN ctdbGetIndexSegmentCount(CTHANDLE Handle);
VRLEN ctdbGetRecordLength(CTHANDLE Handle);
VRLEN ctdbGetRecordSize(CTHANDLE Handle);
VRLEN ctdbGetTableFieldCount(CTHANDLE Handle);
VRLEN ctdbGetTableIndexCount(CTHANDLE Handle);
VRLEN _ctdb_lastdelimiter(pTEXT str, TEXT delimiter);
NINT ctdbBlobCmp(pCTBLOB left, pCTBLOB right);
NINT ctdbGetDefaultIndex(CTHANDLE Handle);
NINT ctdbGetFieldNumber(CTHANDLE Handle, pTEXT FieldName);
NINT _ctdbGetHandleId(CTHANDLE Handle);
NINT ctdbMoneyCmp(CTMONEY left, CTMONEY right);
NINT ctdbSetSavePoint(CTHANDLE Handle);
pCTBLOB ctdbBlobAlloc(VRLEN size);
pCTDBDATA ctdbGetFieldData(pCTDBRECORD pRecord, NINT FieldNbr);
pCTDBDICT _ctdbAllocDict(CTHANDLE Handle, CTBOOL is_session);
pCTDBFIELD ctdbAllocField(pCTDBTABLE pTable, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength);
pCTDBFLDR _ctdbAllocFldx(CTHANDLE hTable);
pCTDBINDEX ctdbAllocIndex(CTHANDLE Handle);
pCTDBISEG ctdbAllocSegment(CTHANDLE Handle);
pCTDBLIST _ctdbListAlloc(void);
pCTDBLIST _ctdbListDup(pCTDBLIST hList);
pCTDBLIST _ctdbListFree(pCTDBLIST hList);
CTDBRET _ctdbListDeleteEx(pCTDBLIST hList, pVOID Item);
pCTDBLKI ctdbFindLock(pCTDBLOCK pLock, FILNO datno, LONG recbyt);
pCTDBLKI ctdbLockItem(pCTDBLOCK pLock, NINT index);
pCTDBLOCK _ctdbAllocLock(void);
pCTDBLOCK _ctdbFreeLock(pCTDBLOCK pLock);
pCTDBSUPER ctdbGetTableSuperFile(CTHANDLE Handle);
pCTDBSUPER _ctdbSuperAlloc(CTHANDLE Handle);
pCTDBSUPER _ctdbSuperFree(pCTDBSUPER pSuper);
pTEXT _ctdbFieldTypeName(CTDBTYPE ftype);
pTEXT ctdbGetDatabaseName(CTHANDLE Handle);
pTEXT ctdbGetDatabasePath(CTHANDLE Handle);
pTEXT ctdbGetDefFloatFormat(CTHANDLE Handle);
pTEXT ctdbGetFieldName(CTHANDLE Handle);
pTEXT ctdbGetIndexExtension(CTHANDLE Handle);
pTEXT ctdbGetSegmentFieldName(CTHANDLE Handle);
pTEXT ctdbGetServerName(CTHANDLE Handle);
pTEXT ctdbGetTableExtension(CTHANDLE Handle);
pTEXT ctdbGetTableGroupid(CTHANDLE Handle);
pTEXT ctdbGetTableName(CTHANDLE Handle);
pTEXT ctdbGetTablePassword(CTHANDLE Handle);
pTEXT ctdbGetTablePath(CTHANDLE Handle);
pTEXT ctdbGetUserLogonName(CTHANDLE Handle);
pTEXT ctdbGetUserPassword(CTHANDLE Handle);
pTEXT _ctdbSuperGetName(pCTDBSUPER pSuper);
pTEXT _ctdb_MakeFilePath(pTEXT Path, pTEXT Name);
pTEXT _ctdb_stralloc(VRLEN size);
pTEXT _ctdb_strdup(cpTEXT str);
pTEXT _ctdb_strlastchar(pTEXT str);
pVOID ctdbBlobGetData(pCTBLOB pBlob);
pVOID ctdbGetDatabaseObjptr(CTHANDLE Handle);
pVOID ctdbGetFieldAddress(CTHANDLE Handle, NINT FieldNbr);
pVOID ctdbGetRecordBuffer(CTHANDLE Handle);
pVOID ctdbGetTableObjptr(CTHANDLE Handle);
pVOID _ctdbListItem(pCTDBLIST hList, NINT Index);
pVOID _ctdb_alloc(VRLEN size, VRLEN count);
pVOID _ctdb_free(pVOID ptr);
pVOID _ctdb_realloc(pVOID ptr, VRLEN size, VRLEN count, VRLEN newCount);
void ctdbBlobFree(pCTBLOB pBlob);
void _ctdbClearBit(pUTEXT pArray, NINT BitNumber);
void ctdbClearError(CTHANDLE Handle);
void _ctdbFileNameOnly(pTEXT Name);
void _ctdbFlipBit(pUTEXT pArray, NINT BitNumber, CTBOOL flag);
void ctdbFreeDatabase(CTHANDLE Handle);
void _ctdbFreeDict(pCTDBDICT pDict);
void ctdbFreeField(CTHANDLE Handle);
void ctdbFreeIndex(CTHANDLE Handle);
void ctdbFreeRecord(CTHANDLE Handle);
void ctdbFreeSegment(CTHANDLE Handle);
void ctdbFreeSession(CTHANDLE Handle);
void ctdbFreeTable(CTHANDLE Handle);
void _ctdbSetBit(pUTEXT pArray, NINT BitNumber);
CTDBRET ctdbCloneTable(CTHANDLE tarHandle, pTEXT tarTableName, CTHANDLE srcHandle);
CTDBRET ctdbHelloWorld(pTEXT HelloFileName,pTEXT HelloTextData,NINT HelloNintData, ULONG HelloULongData, CTFLOAT HelloFloatData); /* CTDB HELLO WORLD */

#endif /* ~_CTDBAPI1_C_	*/
#endif /* ~_CTDBAPI1_H_ */

/* end of ctdbapi1.h */

