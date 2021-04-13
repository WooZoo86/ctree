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

#ifndef _CTDBAPI2_H_
#define _CTDBAPI2_H_

#ifdef  _CTDBAPI2_C_		/* if from main API source module */
#include "ctdbapib.h"
#else


#define _arrayToInt			ii_arrayToInt
#define _ctdbIdxno			ii_ctdbIdxno
#define _ctdbIfilDataMode		ii_ctdbIfilDataMode
#define _ctdbIfilIndexMode		ii_ctdbIfilIndexMode
#define _ctdbIsegField			ii_ctdbIsegField
#define _ctdbRecordMode			ii_ctdbRecordMode
#define _getDateItem			ii_getDateItem
#define _getDatePart			ii_getDatePart
#define _getTimeItem			ii_getTimeItem
#define _getTimePart			ii_getTimePart
#define _leapyr				ii_leapyr
#define _strToInt			ii_strToInt
#define _ctdbAllocDoda			ii_ctdbAllocDoda
#define _ctdbAllocDodaEx			ii_ctdbAllocDodaEx
#define _ctdbCheckExt			ii_ctdbCheckExt
#define _ctdbCheckUID			ii_ctdbCheckUID
#define _ctdb_CheckUID			ii_ctdb_CheckUID
#define _ctdbIfilAlloc			ii_ctdbIfilAlloc
#define _ctdbIsCompatibleFieldTypes	ii_ctdbIsCompatibleFieldTypes
#define _ctdbIsVarlenField		ii_ctdbIsVarlenField
#define _getAmPart			ii_getAmPart
#define _GetAmPart			ii_GetAmPart
#define _checkDateType			ii_checkDateType
#define _checkTimeType			ii_checkTimeType
#define _ctdbAddSegToField		ii_ctdbAddSegToField
#define _ctdbBlobCopy			ii_ctdbBlobCopy
#define _ctdbCheckField			ii_ctdbCheckField
#define _ctdbClearFieldNulBit		ii_ctdbClearFieldNulBit
#define _ctdbCloseCtree			ii_ctdbCloseCtree
#define _ctdbCreateIndexFromIfil		ii_ctdbCreateIndexFromIfil
#define _ctdbCreateTemporary		ii_ctdbCreateTemporary
#define _ctdbDelSegFromField		ii_ctdbDelSegFromField
#define _ctdbDumpDatabaseDictionary	ii_ctdbDumpDatabaseDictionary
#define _ctdbDumpDictionay		ii_ctdbDumpDictionary
#define _ctdbDumpSessionDictionary	ii_ctdbDumpSessionDictionary
#define _ctdbFixRecordBuffer		ii_ctdbFixRecordBuffer
#define _ctdbFixRecordBuffer		ii_ctdbFixRecordBuffer
#define _ctdbGETDODAORMAP		ii_ctdbGETDODAORMAP
#define _ctdbGetBoolField		ii_ctdbGetBoolField
#define _ctdbGetFieldCheck		ii_ctdbGetFieldCheck
#define _ctdbGetFloatField		ii_ctdbGetFloatField
#define _ctdbGetIntegerField		ii_ctdbGetIntegerField
#define _ctdbGetSignedField		ii_ctdbGetSignedField
#define _ctdbGetStringField		ii_ctdbGetStringField
#define _ctdbGetStringField		ii_ctdb_GetStringField
#define _ctdbGetUnsignedField		ii_ctdbGetUnsignedField
#define _ctdbInitRecord			ii_ctdbInitRecord
#define _ctdbInitSession			ii_ctdbInitSession
#define _ctdbInitTable			ii_ctdbInitTable
#define ctdbMakeNames			ii_ctdbMakeNames
#define _ctdbMoveRecord			ii_ctdbMoveRecord
#define _ctdbOpenInternal		ii_ctdbOpenInternal
#define _ctdbRebuildAll			ii_ctdbRebuildAll
#define _ctdbRebuildDoda			ii_ctdbRebuildDoda
#define _ctdbRebuildFull			ii_ctdbRebuildFull
#define _ctdbRebuildIndex		ii_ctdbRebuildIndex
#define _ctdbRecordContext		ii_ctdbRecordContext
#define _ctdbRecordResize		ii_ctdbRecordResize
#define _ctdbReopenCtree			ii_ctdbReopenCtree
#define _ctdbResetDatabase		ii_ctdbResetDatabase
#define _ctdbResetSession		ii_ctdbResetSession
#define _ctdbSetBoolField		ii_ctdbSetBoolField
#define _ctdbSetFieldCheck		ii_ctdbSetFieldCheck
#define _ctdbSetFixStringField		ii_ctdbSetFixStringField
#define _ctdbSetFloatField		ii_ctdbSetFloatField
#define _ctdbSetIntegerField		ii_ctdbSetIntegerField
#define _ctdbSetSignedField		ii_ctdbSetSignedField
#define _ctdbSetStringField		ii_ctdbSetStringField
#define _ctdbSetUnsignedField		ii_ctdbSetUnsignedField
#define _ctdbSetVarStringField		ii_ctdbSetVarStringField
#define _ctdbUpdateRecord		ii_ctdbUpdateRecord
#define _LOGOFF				ii__LOGOFF
#define _LOGON				ii__LOGON
#define _ctdbLocateField			ii_ctdbLocateField
#define _ctdbRebuildIndexCount		ii_ctdbRebuildIndexCount
#define _ctdbRebuildSegmentCount		ii_ctdbRebuildSegmentCount
#define _ctdbIfilReclen			ii_ctdbIfilReclen
#define _ctdbFixFieldLength		ii_ctdbFixFieldLength
#define _ctdbCheckFieldChanges		ii_ctdbCheckFieldChanges
#define _ctdbCheckIndexChanges		ii_ctdbCheckIndexChanges
#define _ctdbGetData			ii_ctdbGetData
#define _ctdbGetFieldFromIseg		ii_ctdbGetFieldFromIseg
#define _ctdbGetFieldFromVarSeg		ii_ctdbGetFieldFromVarSeg
#define _ctdbGetUniqueIndex		ii_ctdbGetUniqueIndex
#define _ctdbRebuildIfil			ii_ctdbRebuildIfil
#define _ctdbRebuildIidx			ii_ctdbRebuildIidx
#define _ctdbRebuildIseg			ii_ctdbRebuildIseg
#define _GETMEM				ii__GETMEM
#define _ctdbIfilName			ii_ctdbIfilName
#define _ctdbTemporaryName		ii_ctdbTemporaryName
#define _PUTMEM				ii__PUTMEM
#define _ctdbDEBUGData			ii__ctdbDEBUGData
#define _ctdbDebugDisplayHex		ii__ctdbDebugDisplayHex
#define _ctdbDebugDisplayText		ii__ctdbDebugDisplayText
#define _ctdbRecordDebugCall		ii__ctdbRecordDebugCall
#define _ctdbTableDisplayDetail		ii__ctdbTableDisplayDetail
#define _ctdbTableDebugDoda		ii__ctdbTableDebugDoda
#define _ctdbTableDebugIfil		ii__ctdbTableDebugIfil
#define _ctdbDatabaseMakePath		ii_ctdbDatabaseMakePath
#define _ctdbFreeDoda			ii_ctdbFreeDoda
#define _ctdbIfilFree			ii_ctdbIfilFree
#define _ctdbRebuildIfilFree		ii_ctdbRebuildIfilFree
#define _ctdbTableMakePath		ii_ctdbTableMakePath
#define _ctdbTime12Hour			ii_ctdbTime12Hour
#define _ctdbTime24Hour			ii_ctdbTime24Hour
#define _ctdb_Time24Hour			ii_ctdb_Time24Hour
#define _ctdbAddFromDefs  		ii_ctdbAddFromDefs

CTDB_STATIC COUNT _arrayToInt(pTEXT pStr, NINT index, NINT length);
CTDB_STATIC COUNT _ctdbIdxno(pCTDBRECORD pRec);
CTDB_STATIC COUNT _ctdbIfilDataMode(pCTDBTABLE pTable, CTBOOL IsOpen);
CTDB_STATIC COUNT _ctdbIfilIndexMode(pCTDBTABLE pTable);
CTDB_STATIC COUNT _ctdbIsegField(pCTDBTABLE pTable, pCTDBFIELD pField);
CTDB_STATIC COUNT _ctdbRecordMode(pCTDBTABLE pTable);
CTDB_STATIC COUNT _getDateItem(pTEXT pStr);
CTDB_STATIC COUNT _getDatePart(pTEXT pStr, NINT index, NINT count);
CTDB_STATIC COUNT _getTimeItem(pTEXT pStr);
CTDB_STATIC COUNT _getTimePart(pTEXT pStr, NINT index, NINT count);
CTDB_STATIC COUNT _leapyr(COUNT year, COUNT month, COUNT day);
CTDB_STATIC COUNT _strToInt(pTEXT pStr);
CTDB_STATIC CTBOOL _ctdbAllocDoda(pCTDBTABLE pTable, CTBOOL IsCreate);
CTDB_STATIC CTBOOL _ctdbAllocDodaEx(pCTDBTABLE pTable, CTBOOL IsCreate, CTBOOL DefFields);
CTDB_STATIC CTBOOL _ctdbCheckExt(pTEXT filnam, pTEXT dext);
CTDB_STATIC CTBOOL _ctdbCheckUID(CTHANDLE Handle, ULONG uid);
CTDB_STATIC CTBOOL _ctdb_CheckUID(CTHANDLE Handle, ULONG uid);
CTDB_STATIC CTBOOL _ctdbIfilAlloc(pCTDBTABLE pTable, CTBOOL IsCreate);
CTDB_STATIC CTBOOL _ctdbIsCompatibleFieldTypes(pCTDBFIELD pField);
CTDB_STATIC CTBOOL _ctdbIsVarlenField(pCTDBFIELD pField);
CTDB_STATIC CTBOOL _getAmPart(pTEXT pStr);
CTDB_STATIC CTBOOL _GetAmPart(pTEXT pStr);
CTDB_STATIC CTDBRET _checkDateType(CTDATE_TYPE DateType);
CTDB_STATIC CTDBRET _checkTimeType(CTTIME_TYPE TimeType);
CTDB_STATIC CTDBRET _ctdbAddSegToField(CTHANDLE hField, CTHANDLE hIseg);
CTDB_STATIC CTDBRET _ctdbBlobCopy(pCTBLOB pvalue, pVOID buffer, VRLEN size);
CTDB_STATIC CTDBRET _ctdbCheckField(pCTDBTABLE pTable, pTEXT Name);
CTDB_STATIC CTDBRET _ctdbClearFieldNulBit(pCTDBRECORD pRecord, pCTDBDATA pField);
CTDB_STATIC CTDBRET _ctdbCloseCtree(CTHANDLE Handle);
CTDB_STATIC CTDBRET _ctdbCreateIndexFromIfil(pCTDBTABLE pTable);
CTDB_STATIC CTDBRET _ctdbCreateTemporary(pCTDBTABLE pTable, pTEXT name);
CTDB_STATIC CTDBRET _ctdbDelSegFromField(CTHANDLE fField, CTHANDLE hIseg);
CTDB_STATIC CTDBRET _ctdbDumpDatabaseDictionary(FILE *fd, CTHANDLE hDatabase);
CTDB_STATIC CTDBRET _ctdbDumpDictionay(FILE *fd, pCTDBDICT pDict);
CTDB_STATIC CTDBRET _ctdbDumpSessionDictionary(FILE *fd, CTHANDLE hSession);
CTDB_STATIC CTDBRET _ctdbFixRecordBuffer(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET _ctdbFixRecordBuffer(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET _ctdbGETDODAORMAP(COUNT datno, ppVOID ppDoda, pVRLEN pSize, NINT doda_mode);
CTDB_STATIC CTDBRET _ctdbGetBoolField(pCTDBDATA pField, pCTBOOL pValue);
CTDB_STATIC CTDBRET _ctdbGetFieldCheck(CTHANDLE Handle, NINT FieldNbr, ppCTDBRECORD ppRec, ppCTDBTABLE ppTable, ppCTDBDATA ppField);
CTDB_STATIC CTDBRET _ctdbGetFloatField(pCTDBDATA pField, pCTFLOAT pValue);
CTDB_STATIC CTDBRET _ctdbGetIntegerField(pCTDBDICT pDict, NINT field, pULONG data);
CTDB_STATIC CTDBRET _ctdbGetSignedField(pCTDBDATA pField, pCTSIGNED pValue);
CTDB_STATIC CTDBRET _ctdbGetStringField(pCTDBDATA pField, CTSTRING pValue, pVRLEN pLength, CTBOOL AddNul);
CTDB_STATIC CTDBRET _ctdbGetStringField(pCTDBDICT pDict, NINT field, pTEXT data, VRLEN size);
CTDB_STATIC CTDBRET _ctdbGetUnsignedField(pCTDBDATA pField, pCTUNSIGNED pValue);
CTDB_STATIC CTDBRET _ctdbInitRecord(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET _ctdbInitSession(pCTDBSESSION pSession);
CTDB_STATIC CTDBRET _ctdbInitTable(pCTDBTABLE pTable);
CTDB_STATIC CTDBRET ctdbMakeNames(pCTDBDICT pDict, pTEXT FileName, ppTEXT supername, ppTEXT tablename);
CTDB_STATIC CTDBRET _ctdbMoveRecord(CTHANDLE Handle, NINT Direction);
CTDB_STATIC CTDBRET _ctdbOpenInternal(pCTDBTABLE pTable, CTOPEN_MODE OpenMode);
CTDB_STATIC CTDBRET _ctdbRebuildAll(CTHANDLE Handle, CTOPEN_MODE mode, CTBOOL PurgeDup);
CTDB_STATIC CTDBRET _ctdbRebuildDoda(CTHANDLE Handle);
CTDB_STATIC CTDBRET _ctdbRebuildFull(CTHANDLE Handle, CTOPEN_MODE oldmode, CTBOOL PurgeDup);
CTDB_STATIC CTDBRET _ctdbRebuildIndex(CTHANDLE Handle, CTOPEN_MODE mode, CTBOOL *isPermIdxUpd);
CTDB_STATIC CTDBRET _ctdbRecordContext(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET _ctdbRecordResize(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET _ctdbReopenCtree(CTHANDLE Handle, CTOPEN_MODE mode);
CTDB_STATIC CTDBRET _ctdbResetDatabase(pCTDBDATABASE pDatabase);
CTDB_STATIC CTDBRET _ctdbResetSession(pCTDBSESSION pSession);
CTDB_STATIC CTDBRET _ctdbSetBoolField(pCTDBDATA pData, CTBOOL value);
CTDB_STATIC CTDBRET _ctdbSetFieldCheck(CTHANDLE Handle, NINT FieldNbr, ppCTDBRECORD ppRec, ppCTDBTABLE ppTable, ppCTDBDATA ppField);
CTDB_STATIC CTDBRET _ctdbSetFixStringField(pCTDBDATA pData, pVOID buffer, VRLEN length, COUNT padChar, CTBOOL truncate);
CTDB_STATIC CTDBRET _ctdbSetFloatField(pCTDBDATA pData, CTFLOAT value);
CTDB_STATIC CTDBRET _ctdbSetIntegerField(pCTDBDICT pDict, NINT field, ULONG data);
CTDB_STATIC CTDBRET _ctdbSetSignedField(pCTDBDATA pData, CTSIGNED value);
CTDB_STATIC CTDBRET _ctdbSetStringField(pCTDBDICT pDict, NINT field, pTEXT data);
CTDB_STATIC CTDBRET _ctdbSetUnsignedField(pCTDBDATA pData, CTUNSIGNED value);
CTDB_STATIC CTDBRET _ctdbSetVarStringField(pCTDBRECORD pRecord, pCTDBDATA pData, pVOID buffer, VRLEN length);
CTDB_STATIC CTDBRET _ctdbUpdateRecord(pCTDBRECORD pRecord, const CTBOOL isNew);
CTDB_STATIC NINT _LOGOFF(pCTDBSESSION pDb);
CTDB_STATIC NINT _LOGON(pCTDBSESSION pDb, pTEXT dbengine, pTEXT userid, pTEXT passwd);
CTDB_STATIC NINT _ctdbLocateField(pCTDBTABLE pTable, pTEXT Name);
CTDB_STATIC NINT _ctdbRebuildIndexCount(pCTDBTABLE pTable);
CTDB_STATIC NINT _ctdbRebuildSegmentCount(pCTDBINDEX pIndex);
CTDB_STATIC UCOUNT _ctdbIfilReclen(pCTDBTABLE pTable);
CTDB_STATIC VRLEN _ctdbFixFieldLength(CTDBTYPE Type, VRLEN Length);
CTDB_STATIC NINT _ctdbCheckFieldChanges(pCTDBTABLE pTable);
CTDB_STATIC NINT _ctdbCheckIndexChanges(pCTDBTABLE pTable);
            pCTDBDATA _ctdbGetData(pCTDBRECORD pRecord, VRLEN FieldNbr);
CTDB_STATIC pCTDBFIELD _ctdbGetFieldFromIseg(pCTDBTABLE pTable, pISEG pIseg);
CTDB_STATIC pCTDBFIELD _ctdbGetFieldFromVarSeg(pCTDBTABLE pTable, pISEG pIseg);
CTDB_STATIC pCTDBINDEX _ctdbGetUniqueIndex(pCTDBTABLE pTable);
CTDB_STATIC pIFIL _ctdbRebuildIfil(pCTDBTABLE pTable);
CTDB_STATIC pIIDX _ctdbRebuildIidx(pCTDBTABLE pTable, NINT count);
CTDB_STATIC pISEG _ctdbRebuildIseg(pCTDBTABLE pTable, pCTDBINDEX pIndex, NINT count, pNINT keylen);
CTDB_STATIC pTEXT _GETMEM(VRLEN siz);
CTDB_STATIC pTEXT _ctdbIfilName(pCTDBTABLE pTable);
CTDB_STATIC pTEXT _ctdbTemporaryName(pCTDBTABLE pTable);
CTDB_STATIC void _PUTMEM(pTEXT ptr);
CTDB_STATIC void _ctdbDEBUGData(CTHANDLE hRecord);
CTDB_STATIC void _ctdbDebugDisplayHex(FILE *fd, pUTEXT data, VRLEN size);
CTDB_STATIC void _ctdbDebugDisplayText(FILE *fd, pTEXT data, VRLEN size);
CTDB_STATIC void _ctdbRecordDebugCall(pTEXT func, CTHANDLE hRecord, CTDBRET retcode);
CTDB_STATIC void _ctdbTableDisplayDetail(pTEXT func, CTHANDLE hTable, CTDBRET retcode, pTEXT fileName);
CTDB_STATIC void _ctdbTableDebugDoda(FILE *fd, pCTDBTABLE pTable);
CTDB_STATIC void _ctdbTableDebugIfil(FILE *fd, pCTDBTABLE pTable);
CTDB_STATIC void _ctdbDatabaseMakePath(pDICTDATA pData, pTEXT Name, pTEXT Path);
CTDB_STATIC void _ctdbFreeDoda(pCTDBTABLE pTable);
CTDB_STATIC void _ctdbIfilFree(pCTDBTABLE pTable);
CTDB_STATIC void _ctdbRebuildIfilFree(pIFIL ifilptr);
CTDB_STATIC void _ctdbTableMakePath(pDICTDATA pData, pTEXT Name, pTEXT Path);
CTDB_STATIC void _ctdbTime12Hour(pCOUNT hour, pCTBOOL IsAm);
CTDB_STATIC void _ctdbTime24Hour(pCOUNT hour, CTBOOL IsAm);
CTDB_STATIC void _ctdb_Time24Hour(pCOUNT hour, CTBOOL IsAm);
CTDB_STATIC CTDBRET _ctdbAddFromDefs (pCTDBTABLE pTable, CTDBFILEDEF *defs);

#endif /* ~_CTDBAPI2_C_	*/
#endif /* ~_CTDBAPI2_H_ */


/* end of ctdbapi2.h */

