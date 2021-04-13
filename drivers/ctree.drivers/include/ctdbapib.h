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

#ifndef _CTDBAPIB_H_
#define _CTDBAPIB_H_

CTDB_STATIC COUNT ii_arrayToInt(pTEXT pStr, NINT index, NINT length);
CTDB_STATIC COUNT ii_ctdbIdxno(pCTDBRECORD pRec);
CTDB_STATIC COUNT ii_ctdbIfilDataMode(pCTDBTABLE pTable, CTBOOL IsOpen);
CTDB_STATIC COUNT ii_ctdbIfilIndexMode(pCTDBTABLE pTable);
CTDB_STATIC COUNT ii_ctdbIsegField(pCTDBTABLE pTable, pCTDBFIELD pField);
CTDB_STATIC COUNT ii_ctdbRecordMode(pCTDBTABLE pTable);
CTDB_STATIC COUNT ii_getDateItem(pTEXT pStr);
CTDB_STATIC COUNT ii_getDatePart(pTEXT pStr, NINT index, NINT count);
CTDB_STATIC COUNT ii_getTimeItem(pTEXT pStr);
CTDB_STATIC COUNT ii_getTimePart(pTEXT pStr, NINT index, NINT count);
CTDB_STATIC COUNT ii_leapyr(COUNT year, COUNT month, COUNT day);
CTDB_STATIC COUNT ii_strToInt(pTEXT pStr);
CTDB_STATIC CTBOOL ii_ctdbAllocDoda(pCTDBTABLE pTable, CTBOOL IsCreate);
CTDB_STATIC CTBOOL ii_ctdbAllocDodaEx(pCTDBTABLE pTable, CTBOOL IsCreate, CTBOOL DefFields);
CTDB_STATIC CTBOOL ii_ctdbCheckExt(pTEXT filnam, pTEXT dext);
CTDB_STATIC CTBOOL ii_ctdbCheckUID(CTHANDLE Handle, ULONG uid);
CTDB_STATIC CTBOOL ii_ctdb_CheckUID(CTHANDLE Handle, ULONG uid);
CTDB_STATIC CTBOOL ii_ctdbIfilAlloc(pCTDBTABLE pTable, CTBOOL IsCreate);
CTDB_STATIC CTBOOL ii_ctdbIsCompatibleFieldTypes(pCTDBFIELD pField);
CTDB_STATIC CTBOOL ii_ctdbIsVarlenField(pCTDBFIELD pField);
CTDB_STATIC CTBOOL ii_getAmPart(pTEXT pStr);
CTDB_STATIC CTBOOL ii_GetAmPart(pTEXT pStr);
CTDB_STATIC CTDBRET ii_checkDateType(CTDATE_TYPE DateType);
CTDB_STATIC CTDBRET ii_checkTimeType(CTTIME_TYPE TimeType);
CTDB_STATIC CTDBRET ii_ctdbAddSegToField(CTHANDLE hField, CTHANDLE hIseg);
CTDB_STATIC CTDBRET ii_ctdbBlobCopy(pCTBLOB pvalue, pVOID buffer, VRLEN size);
CTDB_STATIC CTDBRET ii_ctdbCheckField(pCTDBTABLE pTable, pTEXT Name);
CTDB_STATIC CTDBRET ii_ctdbClearFieldNulBit(pCTDBRECORD pRecord, pCTDBDATA pField);
CTDB_STATIC CTDBRET ii_ctdbCloseCtree(CTHANDLE Handle);
CTDB_STATIC CTDBRET ii_ctdbCreateIndexFromIfil(pCTDBTABLE pTable);
CTDB_STATIC CTDBRET ii_ctdbCreateTemporary(pCTDBTABLE pTable, pTEXT name);
CTDB_STATIC CTDBRET ii_ctdbDelSegFromField(CTHANDLE fField, CTHANDLE hIseg);
CTDB_STATIC CTDBRET ii_ctdbDumpDatabaseDictionary(FILE *fd, CTHANDLE hDatabase);
CTDB_STATIC CTDBRET ii_ctdbDumpDictionary(FILE *fd, pCTDBDICT pDict);
CTDB_STATIC CTDBRET ii_ctdbDumpSessionDictionary(FILE *fd, CTHANDLE hSession);
CTDB_STATIC CTDBRET ii_ctdbFixRecordBuffer(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET ii_ctdbFixRecordBuffer(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET ii_ctdbGETDODAORMAP(COUNT datno, ppVOID ppDoda, pVRLEN pSize, NINT doda_mode);
CTDB_STATIC CTDBRET ii_ctdbGetBoolField(pCTDBDATA pField, pCTBOOL pValue);
CTDB_STATIC CTDBRET ii_ctdbGetFieldCheck(CTHANDLE Handle, NINT FieldNbr, ppCTDBRECORD ppRec, ppCTDBTABLE ppTable, ppCTDBDATA ppField);
CTDB_STATIC CTDBRET ii_ctdbGetFloatField(pCTDBDATA pField, pCTFLOAT pValue);
CTDB_STATIC CTDBRET ii_ctdbGetIntegerField(pCTDBDICT pDict, NINT field, pULONG data);
CTDB_STATIC CTDBRET ii_ctdbGetSignedField(pCTDBDATA pField, pCTSIGNED pValue);
CTDB_STATIC CTDBRET ii_ctdbGetStringField(pCTDBDATA pField, CTSTRING pValue, pVRLEN pLength, CTBOOL AddNul);
CTDB_STATIC CTDBRET ii_ctdb_GetStringField(pCTDBDICT pDict, NINT field, pTEXT data, VRLEN size);
CTDB_STATIC CTDBRET ii_ctdbGetUnsignedField(pCTDBDATA pField, pCTUNSIGNED pValue);
CTDB_STATIC CTDBRET ii_ctdbInitRecord(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET ii_ctdbInitSession(pCTDBSESSION pSession);
CTDB_STATIC CTDBRET ii_ctdbInitTable(pCTDBTABLE pTable);
CTDB_STATIC CTDBRET ii_ctdbMakeNames(pCTDBDICT pDict, pTEXT FileName, ppTEXT supername, ppTEXT tablename);
CTDB_STATIC CTDBRET ii_ctdbMoveRecord(CTHANDLE Handle, NINT Direction);
CTDB_STATIC CTDBRET ii_ctdbOpenInternal(pCTDBTABLE pTable, CTOPEN_MODE OpenMode);
CTDB_STATIC CTDBRET ii_ctdbRebuildAll(CTHANDLE Handle, CTOPEN_MODE mode, CTBOOL PurgeDup);
CTDB_STATIC CTDBRET ii_ctdbRebuildDoda(CTHANDLE Handle);
CTDB_STATIC CTDBRET ii_ctdbRebuildFull(CTHANDLE Handle, CTOPEN_MODE oldmode, CTBOOL PurgeDup);
CTDB_STATIC CTDBRET ii_ctdbRebuildIndex(CTHANDLE Handle, CTOPEN_MODE mode, CTBOOL *isPermIdxUpd);
CTDB_STATIC CTDBRET ii_ctdbRecordContext(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET ii_ctdbRecordResize(pCTDBRECORD pRecord);
CTDB_STATIC CTDBRET ii_ctdbReopenCtree(CTHANDLE Handle, CTOPEN_MODE mode);
CTDB_STATIC CTDBRET ii_ctdbResetDatabase(pCTDBDATABASE pDatabase);
CTDB_STATIC CTDBRET ii_ctdbResetSession(pCTDBSESSION pSession);
CTDB_STATIC CTDBRET ii_ctdbSetBoolField(pCTDBDATA pData, CTBOOL value);
CTDB_STATIC CTDBRET ii_ctdbSetFieldCheck(CTHANDLE Handle, NINT FieldNbr, ppCTDBRECORD ppRec, ppCTDBTABLE ppTable, ppCTDBDATA ppField);
CTDB_STATIC CTDBRET ii_ctdbSetFixStringField(pCTDBDATA pData, pVOID buffer, VRLEN length, COUNT padChar, CTBOOL truncate);
CTDB_STATIC CTDBRET ii_ctdbSetFloatField(pCTDBDATA pData, CTFLOAT value);
CTDB_STATIC CTDBRET ii_ctdbSetIntegerField(pCTDBDICT pDict, NINT field, ULONG data);
CTDB_STATIC CTDBRET ii_ctdbSetSignedField(pCTDBDATA pData, CTSIGNED value);
CTDB_STATIC CTDBRET ii_ctdbSetStringField(pCTDBDICT pDict, NINT field, pTEXT data);
CTDB_STATIC CTDBRET ii_ctdbSetUnsignedField(pCTDBDATA pData, CTUNSIGNED value);
CTDB_STATIC CTDBRET ii_ctdbSetVarStringField(pCTDBRECORD pRecord, pCTDBDATA pData, pVOID buffer, VRLEN length);
CTDB_STATIC CTDBRET ii_ctdbUpdateRecord(pCTDBRECORD pRecord);
CTDB_STATIC NINT ii__LOGOFF(pCTDBSESSION pDb);
CTDB_STATIC NINT ii__LOGON(pCTDBSESSION pDb, pTEXT dbengine, pTEXT userid, pTEXT passwd);
CTDB_STATIC NINT ii_ctdbLocateField(pCTDBTABLE pTable, pTEXT Name);
CTDB_STATIC NINT ii_ctdbRebuildIndexCount(pCTDBTABLE pTable);
CTDB_STATIC NINT ii_ctdbRebuildSegmentCount(pCTDBINDEX pIndex);
CTDB_STATIC UCOUNT ii_ctdbIfilReclen(pCTDBTABLE pTable);
CTDB_STATIC VRLEN ii_ctdbFixFieldLength(CTDBTYPE Type, VRLEN Length);
CTDB_STATIC NINT ii_ctdbCheckFieldChanges(pCTDBTABLE pTable);
CTDB_STATIC NINT ii_ctdbCheckIndexChanges(pCTDBTABLE pTable);
            pCTDBDATA ii_ctdbGetData(pCTDBRECORD pRecord, VRLEN FieldNbr);
CTDB_STATIC pCTDBFIELD ii_ctdbGetFieldFromIseg(pCTDBTABLE pTable, pISEG pIseg);
CTDB_STATIC pCTDBFIELD ii_ctdbGetFieldFromVarSeg(pCTDBTABLE pTable, pISEG pIseg);
CTDB_STATIC pCTDBINDEX ii_ctdbGetUniqueIndex(pCTDBTABLE pTable);
CTDB_STATIC pIFIL ii_ctdbRebuildIfil(pCTDBTABLE pTable);
CTDB_STATIC pIIDX ii_ctdbRebuildIidx(pCTDBTABLE pTable, NINT count);
CTDB_STATIC pISEG ii_ctdbRebuildIseg(pCTDBTABLE pTable, pCTDBINDEX pIndex, NINT count, pNINT keylen);
CTDB_STATIC pTEXT ii__GETMEM(VRLEN siz);
CTDB_STATIC pTEXT ii_ctdbIfilName(pCTDBTABLE pTable);
CTDB_STATIC pTEXT ii_ctdbTemporaryName(pCTDBTABLE pTable);
CTDB_STATIC void ii__PUTMEM(pTEXT ptr);
CTDB_STATIC void ii__ctdbDEBUGData(CTHANDLE hRecord);
CTDB_STATIC void ii__ctdbDebugDisplayHex(FILE *fd, pUTEXT data, VRLEN size);
CTDB_STATIC void ii__ctdbDebugDisplayText(FILE *fd, pTEXT data, VRLEN size);
CTDB_STATIC void ii__ctdbRecordDebugCall(pTEXT func, CTHANDLE hRecord, CTDBRET retcode);
CTDB_STATIC void ii__ctdbTableDebugCall(pTEXT func, CTHANDLE hTable, CTDBRET retcode);
CTDB_STATIC void ii__ctdbTableDebugDoda(FILE *fd, pCTDBTABLE pTable);
CTDB_STATIC void ii__ctdbTableDebugIfil(FILE *fd, pCTDBTABLE pTable);
CTDB_STATIC void ii_ctdbDatabaseMakePath(pDICTDATA pData, pTEXT Name, pTEXT Path);
CTDB_STATIC void ii_ctdbFreeDoda(pCTDBTABLE pTable);
CTDB_STATIC void ii_ctdbIfilFree(pCTDBTABLE pTable);
CTDB_STATIC void ii_ctdbRebuildIfilFree(pIFIL ifilptr);
CTDB_STATIC void ii_ctdbTableMakePath(pDICTDATA pData, pTEXT Name, pTEXT Path);
CTDB_STATIC void ii_ctdbTime12Hour(pCOUNT hour, pCTBOOL IsAm);
CTDB_STATIC void ii_ctdbTime24Hour(pCOUNT hour, CTBOOL IsAm);
CTDB_STATIC void ii_ctdb_Time24Hour(pCOUNT hour, CTBOOL IsAm);
CTDB_STATIC CTDBRET _ctdbAddFromDefs (pCTDBTABLE pTable, CTDBFILEDEF *defs);

#endif /* ~_CTDBAPIB_H_ */

/* end of ctdbapix.h */



