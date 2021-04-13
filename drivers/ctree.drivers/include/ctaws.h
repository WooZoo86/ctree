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

#ifndef ctAWS_H
#define ctAWS_H

#define CTAWS_ERROR_NULL_PARAMETER		1
#define CTAWS_ERROR_INSUFFICIENT_BUFFER_SIZE	2

/*^***********************************/
/*
** String operations with buffer size limits:
*/
#if _MSC_VER >= 1400

/*
** Visual Studio 2005 and later compilers support variadic macros, so we use
** that feature to insert the _TRUNCATE parameter. We use these functions and
** the _TRUNCATE parameter for the following reason:
**
** When the formatted data does not fit into the output buffer, using _TRUNCATE
** causes these functions to write as much data as will fit into the output
** buffer, including a null terminator, instead of zeroing out the output buffer
** and calling the C runtime's invalid parameter handler.
*/
#define ctaws_sprintf(str,size,format,...)	_snprintf_s(str,size,_TRUNCATE,format,__VA_ARGS__)
#define ctaws_vsprintf(str,size,format,...)	_vsnprintf_s(str,size,_TRUNCATE,format,__VA_ARGS__)

#else

#if _MSC_VER == 1200

#define ctaws_sprintf	_snprintf
#define ctaws_vsprintf	_vsnprintf

#else

/*
** Visual Studio 2003 and earlier compilers do not support variadic macros, so
** we use sprintf_s and vsprintf_s. But note that these functions throw an
** exception if the output buffer is too small to hold the formatted data.
*/
#define ctaws_sprintf	sprintf_s
#define ctaws_vsprintf	vsprintf_s

#endif

#endif
/*~***********************************/

typedef struct ctawscredentials {
	char *AWSAccessKeyId;
	char *AWSSecretKey;
} ctAWSCredentials, *pctAWSCredentials;

typedef struct ctawsclientconfig {
	const char *region;
} ctAWSClientConfig, *pctAWSClientConfig;

/* Function pointer for memory allocation function. */
typedef void *(*ctAWSallocFunc_t)(size_t size);

/* Function pointer definitions: */
typedef int (*ctAWSgetLibraryVersionFunc_t)(void);
typedef int (*ctAWSinitFunc_t)(void);
typedef int (*ctAWSshutdownFunc_t)(void);
typedef int (*ctAWSgetCredentialsFunc_t)(pctAWSCredentials pAWSCredentials, int TimeoutSec,
	int *pStopWaiting, int IsService, ctAWSallocFunc_t pAllocFunc, int *pErrorCode, char *ErrorBuffer, size_t ErrorBufferLength);
typedef int (*ctAWSgetSecretFunc_t)(const char *SecretId, const char *VersionStage,
	pctAWSCredentials pAWSCredentials, pctAWSClientConfig pAWSClientConfig,
	char *OutputBuffer, size_t OutputBufferLength, int *pErrorCode,
	char *ErrorBuffer, size_t ErrorBufferLength);
typedef int (*ctAWSputSecretFunc_t)(const char *SecretId, const char *SecretValue, 
	pctAWSCredentials pAWSCredentials, pctAWSClientConfig pAWSClientConfig,
	int *pErrorCode, char *ErrorBuffer, size_t ErrorBufferLength);

/* Exported functions: */
#ifdef __cplusplus
extern "C" {
#endif

#if (defined(_WIN32) && !defined(__FAIRCOM_ISAM_CPP__))
#define CTAWS_DLL_EXPORT __declspec(dllexport)
#else
#define CTAWS_DLL_EXPORT
#endif

#define CTAWS_LIBRARY_VERSION 1 /* Initial version of the c-tree AWS interface library. */

extern CTAWS_DLL_EXPORT int ctAWSgetLibraryVersion(void);
extern CTAWS_DLL_EXPORT int ctAWSinit(void);
extern CTAWS_DLL_EXPORT int ctAWSshutdown(void);
extern CTAWS_DLL_EXPORT int ctAWSgetCredentials(pctAWSCredentials pAWSCredentials, int TimeoutSec,
	int *pStopWaiting, int IsService, ctAWSallocFunc_t pAllocFunc, int *pErrorCode, char *ErrorBuffer, size_t ErrorBufferLength);
extern CTAWS_DLL_EXPORT int ctAWSgetSecret(const char *SecretId, const char *VersionStage,
	pctAWSCredentials pAWSCredentials, pctAWSClientConfig pAWSClientConfig,
	char *OutputBuffer, size_t OutputBufferLength, int *pErrorCode,
	char *ErrorBuffer, size_t ErrorBufferLength);
extern CTAWS_DLL_EXPORT int ctAWSputSecret(const char *SecretId, const char *SecretValue, 
	pctAWSCredentials pAWSCredentials, pctAWSClientConfig pAWSClientConfig,
	int *pErrorCode, char *ErrorBuffer, size_t ErrorBufferLength);

#ifdef __cplusplus
}
#endif

#endif /* ~ctAWS_H */

/* end of ctaws.h */
