#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "ctmsklib.h"

CTMASLIB_DLL_EXPORT int ctGetSecretVersion(void)
{
    return(GET_SECRET_PARAMS_VER1);
}

CTMASLIB_DLL_EXPORT int ctGetSecret(ctGetSecretParams_t * GetSecretParams)
{
    int returnValue;
    ctSecureMasterKeyParams_t SecureMasterKeyParams;
    char myKey[] = "ADMIN";
    memset(&SecureMasterKeyParams, 0, sizeof(SecureMasterKeyParams));
    SecureMasterKeyParams.MasterKey = myKey;
    memcpy(SecureMasterKeyParams.SaltValue, GetSecretParams->SaltValue, sizeof(SecureMasterKeyParams.SaltValue));
    SecureMasterKeyParams.OutputBufferLength = GetSecretParams->OutputBufferLength;
    SecureMasterKeyParams.OutputBuffer = GetSecretParams->OutputBuffer;
    if (GetSecretParams->ErrorBuffer != NULL && GetSecretParams->ErrorBufferLength > 0)
    {
        SecureMasterKeyParams.ErrorBuffer = GetSecretParams->ErrorBuffer;
        SecureMasterKeyParams.ErrorBufferLength = GetSecretParams->ErrorBufferLength;
    }
    returnValue = ctSecureMasterKey(&SecureMasterKeyParams);
    return(returnValue);
}