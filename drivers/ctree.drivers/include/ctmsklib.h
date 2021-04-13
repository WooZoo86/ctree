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

#ifndef CTMSKLIB_H
#define CTMSKLIB_H

#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/pem.h>
#include <time.h>
#include <string.h>
#ifndef MEMDW
#define MEMDW(n) (((n) % (16)) ? (n) + (16) - (n) % (16) : (n))
#endif

/* version 1 of ctGetSecretParams_t structure */
#define GET_SECRET_PARAMS_VER1	1

/* size of the salt value */
#define GET_SECRET_SALT_LENGTH 256

/* parameters for the ctGetSecret() function */
typedef struct _ctGetSecretParams_t {
	int	Version; /* [IN] version of this structure */
	char	SaltValue[GET_SECRET_SALT_LENGTH]; /* [IN] salt value */
	char	*OutputBuffer; /* [OUT] output buffer */
	size_t	OutputBufferLength; /* [IN] size of output buffer */
    char    *ErrorBuffer; /* [OUT] optional error buffer */
    size_t  ErrorBufferLength; /* [IN] size of the optional error buffer */
} ctGetSecretParams_t;

/* parameters for the ctSecureMasterKey() function */
typedef struct _ctSecureMasterKeyParams_t {
	char	*MasterKey; /* [IN] the master key as a null-terminated string */
	char	SaltValue[GET_SECRET_SALT_LENGTH]; /* [IN] salt value */
	char	*OutputBuffer; /* [OUT] output buffer */
	size_t	OutputBufferLength; /* [IN] size of output buffer */
    char    *ErrorBuffer; /* [OUT] optional error buffer */
    size_t  ErrorBufferLength; /* [IN] size of the optional error buffer */
} ctSecureMasterKeyParams_t;
typedef int(*ctGetSecretFuncVersion_t)(void);
typedef int(*ctGetSecretFunc_t)(ctGetSecretParams_t *GetSecretParams);
typedef struct ctmaslibfnc
{
    ctGetSecretFuncVersion_t ctGetSecretVersion;
    ctGetSecretFunc_t ctGetSecret;
} ctMASLIB, *pctMASLIB;

#if (defined(_WIN32) && !defined(__FAIRCOM_ISAM_CPP__))
#define CTMASLIB_DLL_EXPORT __declspec(dllexport)
#else
#define CTMASLIB_DLL_EXPORT
#endif

#ifdef _WIN32
/* sprintf with output buffer size check */
#define safe_sprintf(str,size,format,...)	_snprintf_s(str,size,_TRUNCATE,format,__VA_ARGS__)
#else
/* sprintf with output buffer size check */
#define safe_sprintf		snprintf
#endif

#ifdef __cplusplus
extern "C" {
#endif
int ctSecureMasterKey(ctSecureMasterKeyParams_t *SecureMasterKeyParams);
#ifdef __cplusplus
}
#endif

#endif /* ~CTMSKLIB_H */
