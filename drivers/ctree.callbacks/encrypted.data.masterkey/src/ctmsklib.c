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

#include "ctmsklib.h"

int ctSecureMasterKey(ctSecureMasterKeyParams_t *SecureMasterKeyParams)
{
    int i = 0;
    int ErrorCode = 1;
    AES_KEY enc_key;
    size_t padLength;
    RSA * rsa = NULL;
    BIO *keybio = NULL;
    size_t EncryptedBufferLength;
    size_t MasterKeyLength;

    char publicKey[] = "-----BEGIN PUBLIC KEY-----\n"\
        "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAzjM21fp6ZI8rV4ihKDuk\n"\
        "tKpE/dypugvbydbnOAgfC8e25hrLkzg0DSNFPNmnwK1SAk6LCWeERPqv7v9XfJJc\n"\
        "FH64B0yLPrRH0WzBFkkQGeal2oBnirpq/5/vnKEMFW9cD7q+N6HzQW7dKiA49kG5\n"\
        "aDMUuUY0s6/sAikTge8vfrnmwKfgx6LdcqRlwyOjBoh7uEreMxmOV7dSBvDVUWzm\n"\
        "U2ZFzifqhNcgjzHlfhpmAzAZoerr5CsJGbAg5w/QoYbs8lvVmlRhAnSE8Fr/v+DQ\n"\
        "HZFb4Il5v9svzKDHu/Ui+anR5lPMZj8hZ7M2xbvPC6vvikZ6TdO+MovkEP4kB0VZ\n"\
        "uwIDAQAB\n"\
        "-----END PUBLIC KEY-----";

    if (!SecureMasterKeyParams || !SecureMasterKeyParams->MasterKey || !SecureMasterKeyParams->OutputBuffer) {
	 /* Error: Missing required parameter */
	 goto err_ret;
    }

    MasterKeyLength = strlen(SecureMasterKeyParams->MasterKey) + 1;
    if (MasterKeyLength > SecureMasterKeyParams->OutputBufferLength) {
        if (SecureMasterKeyParams->ErrorBuffer != NULL && SecureMasterKeyParams->ErrorBufferLength > 0)
        {
            safe_sprintf(SecureMasterKeyParams->ErrorBuffer, SecureMasterKeyParams->ErrorBufferLength, "Master Key Library Error: Invalid input buffer length");
        }
        goto err_ret;
    }
    /* Init OpenSSL Items */
    keybio = BIO_new_mem_buf(publicKey, -1);
    if (keybio == NULL)
    {
        if (SecureMasterKeyParams->ErrorBuffer != NULL && SecureMasterKeyParams->ErrorBufferLength > 0)
        {
            safe_sprintf(SecureMasterKeyParams->ErrorBuffer, SecureMasterKeyParams->ErrorBufferLength, "Master Key Library Error: Cannot initialize OpenSSL");
        }
        goto err_ret;
    }
    rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    if (rsa == NULL)
    {
        if (SecureMasterKeyParams->ErrorBuffer != NULL && SecureMasterKeyParams->ErrorBufferLength > 0)
        {
            safe_sprintf(SecureMasterKeyParams->ErrorBuffer, SecureMasterKeyParams->ErrorBufferLength, "Master Key Library Error: Cannot read OpenSSL Public Key");
        }
        goto err_ret;
    }
    if (SecureMasterKeyParams->OutputBufferLength < RSA_size(rsa)) {
        if (SecureMasterKeyParams->ErrorBuffer != NULL && SecureMasterKeyParams->ErrorBufferLength > 0)
        {
            safe_sprintf(SecureMasterKeyParams->ErrorBuffer, SecureMasterKeyParams->ErrorBufferLength, "Master Key Library Error: The output buffer is too small to hold the RSA encrypted data");
        }
        goto err_ret;
    }
    EncryptedBufferLength = MEMDW(MasterKeyLength);
    padLength = EncryptedBufferLength - MasterKeyLength;
    /* max message length for RSA encrypt/decrypt:
    with RSA_PKCS1_PADDING: keylen/8 - 11
    with RSA_PKCS1_OAEP_PADDING: keylen/8 - 2h - 2; h is SHA-1 = 160/8 */
    if (EncryptedBufferLength > RSA_size(rsa) - 42) {
        if (SecureMasterKeyParams->ErrorBuffer != NULL && SecureMasterKeyParams->ErrorBufferLength > 0)
        {
            safe_sprintf(SecureMasterKeyParams->ErrorBuffer, SecureMasterKeyParams->ErrorBufferLength, "Master Key Library Error: Input length exceeds maximum message length for the RSA key length");
        }
        goto err_ret;
    }
    if (AES_set_encrypt_key((unsigned char*)SecureMasterKeyParams->SaltValue, GET_SECRET_SALT_LENGTH, &enc_key) != 0)
    {
        if (SecureMasterKeyParams->ErrorBuffer != NULL && SecureMasterKeyParams->ErrorBufferLength > 0)
        {
            safe_sprintf(SecureMasterKeyParams->ErrorBuffer, SecureMasterKeyParams->ErrorBufferLength, "Master Key Library Error: Cannot set AES encryption key");
        }
        goto err_ret;
    }
    
    srand((unsigned int)time(NULL));
    /* Prepare the buffer for the salt */
    memcpy(SecureMasterKeyParams->OutputBuffer, SecureMasterKeyParams->MasterKey, MasterKeyLength);
    EncryptedBufferLength = MEMDW(MasterKeyLength);
    if (padLength)
    {
        memset(SecureMasterKeyParams->OutputBuffer + MasterKeyLength, rand() % 256, padLength);
    }

    /* Apply salt */
    for (i = 0; i < EncryptedBufferLength; i = i + 16)
    {
        AES_encrypt((const unsigned char *)SecureMasterKeyParams->OutputBuffer + i, (unsigned char *)SecureMasterKeyParams->OutputBuffer + i, &enc_key);
    }
    /* Encrypt using public cert */
    EncryptedBufferLength = RSA_public_encrypt((int)EncryptedBufferLength, (unsigned char*)SecureMasterKeyParams->OutputBuffer, (unsigned char*)SecureMasterKeyParams->OutputBuffer, rsa, RSA_PKCS1_OAEP_PADDING);
    if (EncryptedBufferLength == -1)
    {
        if (SecureMasterKeyParams->ErrorBuffer != NULL && SecureMasterKeyParams->ErrorBufferLength > 0)
        {
            safe_sprintf(SecureMasterKeyParams->ErrorBuffer, SecureMasterKeyParams->ErrorBufferLength, "Master Key Library Error: Cannot encrypt using public key");
        }
        goto err_ret;
    }
    ErrorCode = 0;

err_ret:
    if (keybio)
	    BIO_free(keybio);
    if (rsa)
	    RSA_free(rsa);
    return ErrorCode;
}