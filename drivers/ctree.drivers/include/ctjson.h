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

#ifndef _CTJSON_H_
#define _CTJSON_H_

#include <json.h>

#if defined(_MSC_VER) 
#ifdef FAIRCOM_JSON_EXPORT
#define JSON_API_EXPORT __declspec(dllexport)
#else
#define JSON_API_EXPORT
#endif
#else
#define JSON_API_EXPORT extern
#endif

#define CTJSON_SUCCESS_CODE 0
#define CTJSON_SUCCESS "Success"

#define JSON_SUCCESS "success"
#define JSON_ERROR "error"
#define JSON_ERROR_MSG "errorDesc"
#define JSON_ERROR_CODE "errorCode"

#define JSONDateTime time_t
#define JSONDateTimeMSec time_t
#ifdef _WINDOWS
#define JSONBigInt __int64
#else
#define JSONBigInt int64_t
#endif

/* JSON types */
typedef json_object CTJson, *pCTJson, **ppCTJson;
typedef array_list CTJsonArray, *pCTJsonArray, **ppCTJsonArray;
typedef enum json_type CTJsonType;

/* JSON function */
JSON_API_EXPORT void ctJsonFromString( const char *inString, ppCTJson outJson );
JSON_API_EXPORT void ctJsonToString( pCTJson inObj, const char **outString );

JSON_API_EXPORT const char *ctJsonGetString(pCTJson inObj);
JSON_API_EXPORT int ctJsonGetInt(pCTJson inObj);
JSON_API_EXPORT JSONBigInt ctJsonGetBigint(pCTJson inObj);
JSON_API_EXPORT int ctJsonGetBoolean(pCTJson inObj);
JSON_API_EXPORT double ctJsonGetDouble(pCTJson inObj);
JSON_API_EXPORT JSONDateTime ctJsonGetTimestamp(pCTJson inObj);
JSON_API_EXPORT JSONDateTime ctJsonGetDatetimeGMT(pCTJson inObj);
JSON_API_EXPORT JSONDateTimeMSec ctJsonGetDatetimeGMTMsec(pCTJson inObj);

JSON_API_EXPORT int ctJsonGetByName( pCTJson inObj, const char *name, ppCTJson outObj );
JSON_API_EXPORT int ctJsonGetLength(pCTJson inObj);
JSON_API_EXPORT int ctJsonGetArrayByName( pCTJson inObj, const char *name, ppCTJson outObj );
JSON_API_EXPORT int ctJsonGetStringByName( pCTJson inObj, const char *name, const char **outString );
JSON_API_EXPORT int ctJsonGetIntByName( pCTJson inObj, const char *name, int *outInt );
JSON_API_EXPORT int ctJsonGetDoubleByName(pCTJson inObj, const char *name, double *outDouble);
JSON_API_EXPORT int ctJsonGetBooleanByName( pCTJson inObj, const char *name, int *outBool );
JSON_API_EXPORT int ctJsonGetBigintByName( pCTJson inObj, const char *name, JSONBigInt *bigintValue );
JSON_API_EXPORT int ctJsonGetTimestampByName( pCTJson inObj, const char *name, JSONDateTime *timestampValue );
JSON_API_EXPORT int ctJsonGetDatetimeGMTByName(pCTJson inObj, const char *name, JSONDateTime *timestampValue);
JSON_API_EXPORT int ctJsonGetDatetimeGMTMsecByName(pCTJson inObj, const char *name, JSONDateTimeMSec *timestampValue);

JSON_API_EXPORT pCTJson ctJsonAllocArray();
JSON_API_EXPORT pCTJson ctJsonAlloc();
JSON_API_EXPORT pCTJson ctJsonAllocInt(int value);
JSON_API_EXPORT pCTJson ctJsonAllocString( const char* string );
JSON_API_EXPORT pCTJson ctJsonAllocBigint(JSONBigInt value);

JSON_API_EXPORT void ctJsonDelete(pCTJson inObj, const char *name);

JSON_API_EXPORT void ctJsonAdd( pCTJson inObj, const char *name, pCTJson newObj, int addReference);
JSON_API_EXPORT void ctJsonAddInt( pCTJson inObj, const char *name, int intValue );
JSON_API_EXPORT void ctJsonAddBoolean( pCTJson inObj, const char *name, int boolValue );
JSON_API_EXPORT void ctJsonAddBigint( pCTJson inObj, const char *name, JSONBigInt bigintValue );
JSON_API_EXPORT void ctJsonAddDouble(pCTJson inObj, const char *name, double doubleValue);
JSON_API_EXPORT void ctJsonAddString( pCTJson inObj, const char *name, const char *stringValue );
JSON_API_EXPORT void ctJsonAddTimestamp( pCTJson inObj, const char *name, JSONDateTime timestampValue );

JSON_API_EXPORT void ctJsonArrayAdd( pCTJson inArray, pCTJson newObj );
JSON_API_EXPORT void ctJsonArrayPutAtIndex(pCTJson inArray, int index, pCTJson newObj);

JSON_API_EXPORT int ctJsonArrayLength(pCTJson inArray);
JSON_API_EXPORT void ctJsonArrayGetIdx(pCTJson inArray, int index, ppCTJson outObj);
JSON_API_EXPORT void ctJsonArrayGetBytes(pCTJson inArray, void *buffer, int bufLen);

JSON_API_EXPORT CTJsonType ctJsonGetType(pCTJson inObj);
JSON_API_EXPORT int ctJsonIsType( pCTJson inObj, CTJsonType objType);

JSON_API_EXPORT void ctJsonRelease( pCTJson inObj);
JSON_API_EXPORT void ctJsonAddReference( pCTJson inObj);

#define ctJsonForEach(obj,key,val) json_object_object_foreach(obj,key,val)

JSON_API_EXPORT void ctJsonSetError( int errorCode, const char *errorMsg, ppCTJson retError );
JSON_API_EXPORT void ctJsonSetSuccess( pCTJson jsonObj );

JSON_API_EXPORT int ctJsonFileDump( const char *fileName, pCTJson jsonObj );
JSON_API_EXPORT int ctJsonFileDumpExt(const char *fileName, pCTJson jsonObj);
JSON_API_EXPORT void ctJsonFileLoad( const char *fileName, ppCTJson jsonObj );

/* As JSON doesn't support back slash, we support the regular slash and convert to the correct separator here */
JSON_API_EXPORT void ctSepToJson( char *path );
JSON_API_EXPORT void ctJsonToSep( char *path );

#endif /* _CTJSON_H_ */