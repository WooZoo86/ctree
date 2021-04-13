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

#ifdef	CTDBCEPTLAYER	/* If intercept layer defined */

#undef ctdbDayOfWeek				
#undef _ctdbGetDatno				
#undef ctdbGetDay				
#undef ctdbGetHour				
#undef ctdbGetMinute				
#undef ctdbGetMonth				
#undef ctdbGetSecond				
#undef ctdbGetYear				
#undef ctdbGetFieldNullFlag			
#undef ctdbGetIndexDuplicateFlag		
#undef ctdbGetIndexNullFlag			
#undef ctdbGetIndexTemporaryFlag		
#undef ctdbGetLockActive			
#undef ctdbGetLogonOnly			
#undef ctdbHasNullFieldSupport			
#undef ctdbIsActiveDatabase			
#undef ctdbIsActiveSession			
#undef ctdbIsActiveTable			
#undef ctdbIsEditedRecord			
#undef ctdbIsExtSegment			
#undef ctdbIsLeapYear				
#undef ctdbIsLockActive			
#undef ctdbIsNewRecord				
#undef ctdbIsNullField				
#undef ctdbIsTransActive			
#undef ctdbIsVariableField			
#undef _ctdbSuperIsExclusive			
#undef _ctdbSuperIsOpen				
#undef _ctdbTestBit				
#undef ctdbGetTableCreateMode			
#undef ctdbGetDefDateType			
#undef ctdbGetIndexKeyType			
#undef _ctdbGetNumberOfIndexEntries		
#undef _ctdbGetNumberOfRecords			
#undef _ctdbADDREC				
#undef _ctdbADDRES				
#undef _ctdbADDVREC				
#undef _ctdbAVLFILNBR				
#undef ctdbAbort				
#undef ctdbAddDatabase				
#undef ctdbAddLock				
#undef ctdbAddTable				
#undef ctdbAddTableXtd				
#undef ctdbAlterTable				
#undef ctdbBegin				
#undef ctdbPrepareCommit
#undef ctdbBlobClear				
#undef ctdbBlobSet				
#undef ctdbBuildTargetKey			
#undef _ctdbCHGICON				
#undef _ctdbCLRFIL				
#undef _ctdbCLSFIL				
#undef _ctdbCLSICON				
#undef _ctdbCREDAT				
#undef _ctdbCREIFILX				
#undef _ctdbCREIFILXX				
#undef _ctdbClearDict				
#undef ctdbClearField				
#undef ctdbClearRecord				
#undef ctdbClearTableSuperFile			
#undef ctdbCloseAll				
#undef _ctdbCloseDict				
#undef ctdbCloseTable				
#undef ctdbCommit				
#undef ctdbConnect				
#undef ctdbCopyRecordBuffer			
#undef ctdbCreateDatabase			
#undef _ctdbCreateDict				
#undef ctdbCreateSession			
#undef ctdbCreateTable				
#undef ctdbCurrentDate				
#undef ctdbCurrentDateTime			
#undef ctdbCurrentTime				
#undef ctdbServerDateTime	
#undef _ctdbDELFIL				
#undef _ctdbDELREC				
#undef _ctdbDELRFIL				
#undef _ctdbDELVREC				
#undef ctdbDateCheck				
#undef ctdbDatePack				
#undef ctdbDateTimeGetDate			
#undef ctdbDateTimeGetTime			
#undef ctdbDateTimePack			
#undef ctdbDateTimeSetDate			
#undef ctdbDateTimeSetTime			
#undef ctdbDateTimeToString			
#undef ctdbDateTimeUnpack			
#undef ctdbDateToString			
#undef ctdbDateUnpack				
#undef ctdbDelField				
#undef ctdbDelFieldByName			
#undef ctdbDelIndex				
#undef ctdbDelLock				
#undef ctdbDelSegment				
#undef ctdbDelSegmentEx			
#undef ctdbDeleteDatabase			
#undef _ctdbDeleteDict				
#undef ctdbDeleteRecord			
#undef ctdbDeleteTable				
#undef _ctdbDictAddAllIndex			
#undef _ctdbDictAddDatabase			
#undef _ctdbDictAddIndex			
#undef _ctdbDictAddTable			
#undef _ctdbDictDropAllIndex			
#undef _ctdbDictDropDatabase			
#undef _ctdbDictDropIndex			
#undef _ctdbDictDropTable			
#undef _ctdbDictFindDatabase			
#undef _ctdbDictFindDatabaseByUID		
#undef _ctdbDictFindIndex			
#undef _ctdbDictFindIndexByUID			
#undef _ctdbDictFindTable			
#undef _ctdbDictFindTableByUID			
#undef _ctdbDictFirstDatabase			
#undef _ctdbDictFirstTable			
#undef _ctdbDictGetDatabaseUID			
#undef _ctdbDictGetTableUID			
#undef _ctdbDictNextDatabase			
#undef _ctdbDictNextTable			
#undef _ctdbDictReserveIndex			
#undef _ctdbDictReserveTable			
#undef _ctdbDictUpdateIndex			
#undef ctdbDisconnect				
#undef ctdbDisconnectAll			
#undef ctdbDropDatabase			
#undef ctdbDropTable				
#undef _ctdbDumpDict				
#undef _ctdbEndDebug				
#undef _ctdbFINDREC				
#undef _ctdbFRESET				
#undef _ctdbFileExist				
#undef ctdbFindDatabase			
#undef ctdbFindDatabaseByUID			
#undef _ctdbFindDict				
#undef _ctdbFindDictByUID			
#undef ctdbFindRecord				
#undef ctdbLocateRecord				
#undef ctdbSetRecordCriteria				
#undef ctdbUpdateRecordCriteria				
#undef ctdbGetBestIndex				
#undef ctdbAddLocateCriteria		
#undef ctdbFindTable				
#undef ctdbFindTableByUID			
#undef ctdbFindTarget				
#undef ctdbFirstDatabase			
#undef _ctdbFirstDict				
#undef ctdbFirstRecord				
#undef ctdbFirstTable				
#undef ctdbFloatToMoney			
#undef _ctdbGETCURP				
#undef _ctdbGETDODA				
#undef _ctdbGETFIL				
#undef _ctdbGETIFIL				
#undef _ctdbGETRES				
#undef _ctdbGETSCHEMA				
#undef _ctdbGETVLEN				
#undef ctdbGetActiveDatabaseUID		
#undef ctdbGetActiveTableUID			
#undef ctdbGetDatabaseUID			
#undef _ctdbGetDict				
#undef _ctdbGetDictUID				
#undef ctdbGetError				
#undef ctdbGetFieldAsBinary			
#undef ctdbGetFieldAsBlob			
#undef ctdbGetFieldAsBool			
#undef ctdbGetFieldAsDate			
#undef ctdbGetFieldAsDateTime			
#undef ctdbGetFieldAsFloat			
#undef ctdbGetFieldAsMoney			
#undef ctdbGetFieldAsSigned			
#undef ctdbGetFieldAsString			
#undef ctdbGetFieldAsTime			
#undef ctdbGetFieldAsUnsigned			
#undef ctdbGetFieldProperties			
#undef _ctdbGetFldx				
#undef ctdbGetIndexNbr				
#undef ctdbGetRecordCount			
#undef ctdbGetRecordPos			
#undef ctdbGetRecordKeyPos			
#undef ctdbGetSegmentNbr			
#undef ctdbGetSessionPath			
#undef ctdbGetTableUID				
#undef ctdbGetUserTag				
#undef _ctdbIconAdd				
#undef _ctdbIconAlloc				
#undef _ctdbIconFree				
#undef _ctdbIconReset				
#undef _ctdbIconSwitch				
#undef _ctdbLKISAM				
#undef _ctdbLOKREC				
#undef ctdbLastRecord				
#undef _ctdbListAdd				
#undef _ctdbListClear				
#undef _ctdbListDelete				
#undef _ctdbListDeleteEx			
#undef _ctdbListExchange			
#undef _ctdbListExpand				
#undef _ctdbListInsert				
#undef _ctdbListMove				
#undef _ctdbListReplace				
#undef _ctdbListSort				
#undef ctdbLock				
#undef ctdbLockRecord				
#undef ctdbLogon				
#undef ctdbLogout				
#undef ctdbLongToMoney				
#undef _ctdbMOVREC				
#undef _ctdbMOVSET				
#undef ctdbMoneyAdd				
#undef ctdbMoneyDiv				
#undef ctdbMoneyMul				
#undef ctdbMoneySub				
#undef ctdbMoneyToFloat			
#undef ctdbMoneyToLong				
#undef ctdbMoneyToString			
#undef ctdbMoveField				
#undef ctdbNextDatabase			
#undef _ctdbNextDict				
#undef ctdbNextRecord				
#undef ctdbNextTable				
#undef _ctdbOPNFIL				
#undef _ctdbOPNICON				
#undef _ctdbOPNRFILX				
#undef _ctdbOpenDict				
#undef ctdbOpenTable				
#undef ctdbOpenTableByUID				
#undef _ctdbPRMIIDX				
#undef _ctdbTMPIIDX				
#undef ctdbPrevRecord				
#undef _ctdbPutDict				
#undef _ctdbPutFldx				
#undef _ctdbRBLIFILX				
#undef _ctdbREDIREC				
#undef _ctdbREDIVREC				
#undef _ctdbREDVREC				
#undef _ctdbREGCTREE				
#undef _ctdbRENIFIL				
#undef _ctdbRWTREC				
#undef _ctdbRWTVREC				
#undef _ctdbRWTPREC				
#undef ctdbReadRecord				
#undef ctdbRecLock				
#undef ctdbRecUnlock				
#undef ctdbRecordSetOff			
#undef ctdbRecordSetOn				
#undef ctdbReleaseLocks			
#undef ctdbReleaseTableLocks			
#undef _ctdbRemoveDict				
#undef _ctdbRemoveDictByUID			
#undef ctdbReopenDict				
#undef ctdbResetAll				
#undef ctdbResetRecord				
#undef ctdbRestoreSavePoint			
#undef _ctdbSETCURI				
#undef _ctdbSWTCTREE				
#undef ctdbSeekRecord				
#undef ctdbSetDatabaseObjptr			
#undef ctdbSetDefDateType			
#undef ctdbSetDefFloatFormat			
#undef ctdbSetDefTimeType			
#undef ctdbSetDefaultIndex			
#undef ctdbSetEditedRecord			
#undef ctdbSetError				
#undef ctdbSetFieldAsBinary			
#undef ctdbSetFieldAsBlob			
#undef ctdbSetFieldAsBool			
#undef ctdbSetFieldAsDate			
#undef ctdbSetFieldAsDateTime			
#undef ctdbSetFieldAsFloat			
#undef ctdbSetFieldAsMoney			
#undef ctdbSetFieldAsSigned			
#undef ctdbSetFieldAsString			
#undef ctdbSetFieldAsTime			
#undef ctdbSetFieldAsUnsigned			
#undef ctdbSetFieldLength			
#undef ctdbSetFieldName			
#undef ctdbSetFieldNullFlag			
#undef ctdbSetFieldPrecision			
#undef ctdbSetFieldProperties			
#undef ctdbSetFieldScale			
#undef ctdbSetFieldType			
#undef ctdbSetIndexDuplicateFlag		
#undef ctdbSetIndexEmptyChar			
#undef ctdbSetIndexExtension			
#undef ctdbSetIndexKeyType			
#undef ctdbSetIndexNullFlag			
#undef ctdbSetIndexTemporaryFlag		
#undef ctdbSetIndexCndxExpr
#undef ctdbSetLockActive			
#undef ctdbSetLockMode				
#undef ctdbSetLogonOnly			
#undef ctdbSetNewRecord			
#undef ctdbSetRecordOffset			
#undef ctdbSetRecordPos			
#undef ctdbSetSegmentMode			
#undef ctdbSetSessionParams			
#undef ctdbSetSessionPath			
#undef ctdbSetTableDefaultDataExtentSize 	
#undef ctdbSetTableDefaultIndexExtentSize	
#undef ctdbSetTableExtension			
#undef ctdbSetTableGroupid			
#undef ctdbSetTableObjptr			
#undef ctdbSetTablePassword			
#undef ctdbSetTablePath			
#undef ctdbSetTablePermission			
#undef ctdbSetTableSuperFile			
#undef ctdbSetUserTag				
#undef _ctdbStartDebug				
#undef ctdbStringToDate			
#undef ctdbStringToDateTime			
#undef ctdbStringToMoney			
#undef ctdbStringToTime			
#undef _ctdbSuperClose				
#undef _ctdbSuperCreate				
#undef _ctdbSuperDrop				
#undef _ctdbSuperOpen				
#undef _ctdbSuperReopen				
#undef _ctdbSuperSetName			
#undef _ctdbSuperSetPath			
#undef _ctdbSysTime				
#undef _ctdbTFRMKEY				
#undef ctdbTimeCheck				
#undef ctdbTimePack				
#undef ctdbTimeToString			
#undef ctdbTimeUnpack				
#undef _ctdbUNRCTREE				
#undef ctdbUnlock				
#undef _ctdbUnlockDict				
#undef ctdbUnlockRecord			
#undef ctdbUnlockTable				
#undef ctdbUpdLock				
#undef _ctdbWriteDict				
#undef ctdbWriteRecord				
#undef _ctdb_FullPath				
#undef _ctdb_GetFileExt				
#undef _ctdb_GetFileName			
#undef _ctdb_GetFilePath			
#ifdef CTDB_MIRROR
#undef _ctdb_GetMirrorFileName
#endif
#undef _ctdbfrmkey				
#undef ctdbGetFieldType			
#undef ctdbAddField				
#undef ctdbAddIndex				
#undef ctdbAddSegment				
#undef ctdbAddSegmentByName			
#undef ctdbAddSegmentByNbr			
#undef ctdbAddSegmentEx			
#undef ctdbAllocDatabase			
#undef ctdbAllocRecord				
#undef ctdbAllocSession			
#undef ctdbAllocTable				
#undef ctdbDuplicateRecord			
#undef ctdbFindActiveDatabase			
#undef ctdbFindActiveDatabaseByUID		
#undef ctdbFindActiveTable			
#undef ctdbFindActiveTableByUID		
#undef ctdbGetActiveTableByUID			
#undef ctdbGetDatabaseHandle			
#undef ctdbGetField				
#undef ctdbGetFieldByName			
#undef ctdbGetFieldHandle			
#undef ctdbGetFirstActiveDatabase		
#undef ctdbGetFirstActiveTable			
#undef ctdbGetIndex				
#undef ctdbGetIndexByName			
#undef ctdbGetIndexByUID			
#undef ctdbGetIndexHandle			
#undef ctdbGetNextActiveDatabase		
#undef ctdbGetNextActiveTable			
#undef ctdbGetRecord				
#undef ctdbGetRecordHandle			
#undef ctdbGetSegment				
#undef ctdbGetSegmentField
#undef ctdbGetSegmentPartialField			
#undef ctdbGetSegmentHandle			
#undef ctdbGetSessionHandle			
#undef ctdbGetTable				
#undef ctdbGetTableHandle			
#undef ctdbInsField				
#undef ctdbInsFieldByName			
#undef ctdbInsSegment				
#undef ctdbInsSegmentByName			
#undef ctdbInsSegmentByNbr			
#undef ctdbInsSegmentEx			
#undef _ctdbSelectHandle			
#undef ctdbGetLockMode				
#undef ctdbMoneyAbs				
#undef ctdbGetTableOpenMode			
#undef ctdbGetSegmentMode			
#undef ctdbGetDefTimeType			
#undef ctdbGetTablePermission			
#undef _ctdbDictGetDatabaseCount		
#undef _ctdbDictGetTableCount			
#undef ctdbGetDatabaseCount			
#undef _ctdbGetDictCount			
#undef ctdbGetFieldNbr				
#undef ctdbGetFieldPrecision			
#undef ctdbGetFieldScale			
#undef ctdbGetIndexEmptyChar			
#undef ctdbGetIndexNbrByName			
#undef ctdbGetSessionParams			
#undef ctdbGetRecordNbr			
#undef ctdbGetTableCount			
#undef ctdbGetTableDefaultDataExtentSize	
#undef ctdbGetTableDefaultIndexExtentSize	
#undef ctdbGetTableNbr				
#undef _ctdbListCount				
#undef _ctdbListIndexOf				
#undef _ctdbListSize				
#undef _ctdbLocateDatabase			
#undef _ctdbLocateTable				
#undef ctdbLockCount				
#undef ctdbGetIndexUID				
#undef ctdbBlobGetSize				
#undef ctdbGetFieldDataLength			
#undef ctdbGetFieldLength			
#undef ctdbGetFieldNumberByName		
#undef ctdbGetFieldOffset			
#undef ctdbGetFieldSize			
#undef ctdbGetIndexKeyLength			
#undef ctdbGetIndexSegmentCount		
#undef ctdbGetRecordLength			
#undef ctdbGetRecordSize			
#undef ctdbGetTableFieldCount			
#undef ctdbGetTableIndexCount			
#undef _ctdb_lastdelimiter			
#undef ctdbBlobCmp				
#undef ctdbGetDefaultIndex			
#undef ctdbGetFieldNumber			
#undef _ctdbGetHandleId				
#undef ctdbMoneyCmp				
#undef ctdbSetSavePoint	
#undef ctdbSetSingleSavePoint			
#undef ctdbBlobAlloc				
#undef ctdbGetFieldData			
#undef _ctdbAllocDict				
#undef ctdbAllocField				
#undef _ctdbAllocFldx				
#undef ctdbAllocIndex				
#undef ctdbAllocSegment			
#undef _ctdbListAlloc				
#undef _ctdbListDup				
#undef _ctdbListFree				
#undef _ctdbListDeleteEx
#undef ctdbFindLock				
#undef ctdbLockItem				
#undef _ctdbAllocLock				
#undef _ctdbFreeLock				
#undef ctdbGetTableSuperFile			
#undef _ctdbSuperAlloc				
#undef _ctdbSuperFree				
#undef _ctdbFieldTypeName			
#undef ctdbGetDatabaseName			
#undef ctdbGetDatabasePath			
#undef ctdbGetDefFloatFormat			
#undef ctdbGetFieldName			
#undef ctdbGetIndexExtension			
#undef ctdbGetSegmentFieldName			
#undef ctdbGetServerName			
#undef ctdbGetTableExtension			
#undef ctdbGetTableGroupid			
#undef ctdbGetTableName			
#undef ctdbGetTablePassword			
#undef ctdbGetTablePath			
#undef ctdbGetUserLogonName				
#undef ctdbGetUserPassword			
#undef _ctdbSuperGetName			
#undef _ctdb_MakeFilePath			
#undef _ctdb_stralloc				
#undef _ctdb_strdup				
#undef _ctdb_strlastchar			
#undef ctdbBlobGetData				
#undef ctdbGetDatabaseObjptr			
#undef ctdbGetFieldAddress			
#undef ctdbGetRecordBuffer			
#undef ctdbGetTableObjptr			
#undef _ctdbListItem				
#undef _ctdb_alloc				
#undef _ctdb_free				
#undef _ctdb_realloc				
#undef ctdbBlobFree				
#undef _ctdbClearBit				
#undef ctdbClearError				
#undef _ctdbFileNameOnly			
#undef _ctdbFlipBit				
#undef ctdbFreeDatabase			
#undef _ctdbFreeDict				
#undef ctdbFreeField				
#undef ctdbFreeIndex				
#undef ctdbFreeRecord				
#undef ctdbFreeSegment				
#undef ctdbFreeSession				
#undef ctdbFreeTable				
#undef _ctdbSetBit				
#undef ctdbCloneTable				
#undef ctdbHelloWorld	/* CTDB HELLO WORLD */


#endif /* CTDBCEPTLAYER	If intercept layer defined */
