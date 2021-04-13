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

#ifndef _CTCRSDK_H_
#define _CTCRSDK_H_
/******************************************************************************\
*
*	header files
*
\******************************************************************************/
#include "ctstdr.h"
#include "ctoptn.h"
#include "ctaerr.h"

#define ctCAMOsdk_maxKEYLEN	64 /* Maximum encryption key length. */

#define ctPWDBUFSIZ	128

#ifdef LOW_HIGH
#define ctINTEL
#endif
/******************************************************************************\
*
*	start protection against c++ compilers
*
\******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************\
*
*	Defines
*
\******************************************************************************/
#define	rotl(x,n)			(((x) << ((n) & 0x1F)) | ((x) >> (32-((n) & 0x1F))))
#define	rotr(x,n)			(((x) >> ((n) & 0x1F)) | ((x) << (32-((n) & 0x1F))))
#define _get_byte0(x)		(((x) & 0xff000000L) >> 24)
#define _get_byte1(x)		(((x) & 0x00ff0000L) >> 16)
#define _get_byte2(x)		(((x) & 0x0000ff00L) >> 8)
#define _get_byte3(x)		((x) & 0x000000ffL)
#define _put_byte0(x,y)		x = ((x & 0x00ffffffL) | (((y) & 0xff) << 24))
#define _put_byte1(x,y)		x = ((x & 0xff00ffffL) | (((y) & 0xff) << 16))
#define _put_byte2(x,y)		x = ((x & 0xffff00ffL) | (((y) & 0xff) << 8))
#define _put_byte3(x,y)		x = ((x & 0xffffff00L) | (((y) & 0xff)))
/******************************************************************************\
*
*	typedefs
*
\******************************************************************************/
typedef ULONG	UINT4, ctMEM *pUINT4, ctMEM * ctMEM * ppUINT4;
/******************************************************************************\
*
*	ctcrstdr.c
*	Standard functions used by ctcrsdk library
*
\******************************************************************************/

void ctDECL _unpack32(const UINT4 * dw, int size, pUTEXT data);
void ctDECL _pack32(const UTEXT * data, pUINT4 dw, int size);
void ctDECL _shl32(pUINT4 dw, int size);
void ctDECL _put32(pUINT4 dw, int size, UINT4 val);
void ctDECL _expand32(UINT4 value, pUINT4 iv, int size);
UINT4 ctDECL ctcrc32(UTEXT ch, UINT4 crc);
UINT4 ctDECL crc32uint(UINT4 value, UINT4 crc);
UINT4 ctDECL crc32buffer(const UTEXT * ptr, size_t size, UINT4 crc);
UINT4 ctDECL crc32block(pULONG ptr, int size, UINT4 crc);

/******************************************************************************\
*
*	MD5 - Message Digest Algorithm
*
*	Copyright (C) 1991, RSA Data Security, Inc. All rights reserved.
*
*	License to copy and use this software is granted provided that it
*	is identified as the "RSA Data Security, Inc. MD5 Message-Digest
*	Algorithm" in all material mentioning or referencing this software
*	or this function.
*
*	License is also granted to make and use derivative works provided
*	that such works are identified as "derived from the RSA Data
*	Security, Inc. MD5 Message-Digest Algorithm" in all material
*	mentioning or referencing the derived work.  
*                                                                
*	RSA Data Security, Inc. makes no representations concerning either
*	the merchantability of this software or the suitability of this
*	software for any particular purpose. It is provided "as is"
*	without express or implied warranty of any kind.  
*                                                                
*	These notices must be retained in any copies of any part of this
*	documentation and/or software.  
*
*	Digest size is 16 bytes long
*
\******************************************************************************/
typedef struct 
{
	UINT4 state[4];
	UINT4 count[2];
	UTEXT buffer[64];
} MD5CTX, ctMEM * pMD5CTX;

void ctDECL MD5Init(pMD5CTX ctx);
void ctDECL MD5Update(pMD5CTX ctx, pUTEXT buffer, int buffer_size);
void ctDECL MD5Final(pUTEXT digest, pMD5CTX ctx);
void ctDECL MD5Round(pMD5CTX ctx);
/******************************************************************************\
*
*	SHA1 - Secure Hash Algorithm
*	Digest size is 20 bytes long
*
\******************************************************************************/
typedef struct 
{
    UINT4 state[5];
    UINT4 count[2];
    UTEXT buffer[64];
} SHACTX, ctMEM * pSHACTX;

void ctDECL SHAInit(pSHACTX ctx);
void ctDECL SHAUpdate(pSHACTX ctx, pUTEXT buffer, int buffer_size);
void ctDECL SHAFinal(pUTEXT digest, pSHACTX ctx);
/******************************************************************************\
*
*	SHA2 - Secure Hash Algorithm
*	Digest size is 32 bytes long
*
\******************************************************************************/
#ifdef ctN8 /* SHA512 requires native 64-bit integer support */
#define ctFeatSHA512
#endif
typedef struct 
{
#ifdef ctFeatSHA512
    ULONG8 state8[8];
    ULONG8 count8[2];
#endif
    UINT4 state[8];
    UINT4 count[2];
    UTEXT buffer[128];
    int   keylen;
} SHA2CTX, ctMEM * pSHA2CTX;

#define SHA256_HASH_LENGTH 32 /* size of SHA256 hash in bytes */
#define SHA512_HASH_LENGTH 64 /* size of SHA512 hash in bytes */

 int ctDECL SHA2Init(pSHA2CTX ctx, int keylen);
void ctDECL SHA2Update(pSHA2CTX ctx, pUTEXT buffer, int buffer_size);
void ctDECL SHA2Final(pUTEXT digest, pSHA2CTX ctx);
/******************************************************************************\
*
*	DES
*
*	DES encryption algorithm based on description published by 
*	Bruce Schneier,	Applied Cryptography 2nd Edition, ISBN 0-471-12845-7
*
\******************************************************************************/
typedef struct
{
	UINT4	ek[3][32];			/* encryption keys				*/
	UINT4	dk[3][32];			/* decryption keys				*/
	int		mode;				/* DES, 2DES, 3DES				*/
} DESCTX, ctMEM * pDESCTX;

int ctDECL DESInit(pDESCTX ctx, pUTEXT key, int keylen);
int ctDECL DESEncrypt(pDESCTX ctx, pUINT4 inblock, pUINT4 outblock);
int ctDECL DESDecrypt(pDESCTX, pUINT4 inblock, pUINT4 outblock);
/******************************************************************************\
*
*	Blowfish
*
*	Blowfish encryption algorithm implementation based on code made public by 
*	Bruce Schneier of Counterpane Internet Security Inc.
*	Please refer to www.counterpane.com/blowfish.html
*	Quote from Counterpane web site about Blowfish:
*	"Blowfish is unpatented and license-free, and is available free 
*	for all uses. "
*
\******************************************************************************/
#define bf_N        16

typedef struct
{
	int		keylen;
	UTEXT	key[56];
	UINT4	bf_P[bf_N + 2];
	UINT4	bf_S[4][256];
} BLFCTX, ctMEM * pBLFCTX;

int ctDECL BLFInit(pBLFCTX ctx, pUTEXT key, int keybytes);
int ctDECL BLFEncrypt(pBLFCTX ctx, pUINT4 inblock, pUINT4 outblock);
int ctDECL BLFDecrypt(pBLFCTX ctx, pUINT4 inblock, pUINT4 outblock);
/******************************************************************************\
*
*	Rijndael
*
*	Rijndael encryption algorithm implementation based on code made public by 
*	the Rijndael web page as one of NIST AES finalist
*	Please refer to http://www.esat.kuleuven.ac.be/~rijmen/rijndael/
*	Quote from Rijndael web site:
*	"Rijndael is available for free. You can use it for whatever purposes 
*	you want, irrespective of whether it is accepted as AES or not. "
*
\******************************************************************************/
typedef struct
{
	UTEXT  rij_pow_tab[256];
	UTEXT  rij_log_tab[256];
	UTEXT  rij_sbx_tab[256];
	UTEXT  rij_isb_tab[256];
	UINT4  rij_rco_tab[ 10];
	UINT4  rij_ft_tab[4][256];
	UINT4  rij_it_tab[4][256];
	UINT4  rij_fl_tab[4][256];
	UINT4  rij_il_tab[4][256];
	UINT4  rij_k_len;
	UINT4  rij_e_key[64];
	UINT4  rij_d_key[64];
	UINT4  rij_tab_gen;
	int 	mode;
} RIJCTX, ctMEM * pRIJCTX;
typedef RIJCTX AESCTX, ctMEM * pAESCTX;

int ctDECL RIJInit(pRIJCTX ctx, pUTEXT key, int keylen);
int ctDECL RIJEncrypt(pRIJCTX ctx, pUINT4 in_blk, pUINT4 out_blk);
int ctDECL RIJDecrypt(pRIJCTX ctx, pUINT4 in_blk, pUINT4 out_blk);
int ctDECL AESInit(pAESCTX ctx, pUTEXT key, int keylen);
int ctDECL AESEncrypt(pAESCTX ctx, pUINT4 in_blk, pUINT4 out_blk);
int ctDECL AESDecrypt(pAESCTX ctx, pUINT4 in_blk, pUINT4 out_blk);
/******************************************************************************\
*
*	Twofish
*
*	Twofish encryption algorithm implementation based on code made public by 
*	Counterpane Internet Security Inc, as one of the NIST AES finalist
*	Please refer to www.counterpane.com/twofish.html
*	Quote from Counterpane web site about Twofish:
*	"Twofish is unpatented, and the source code is uncopyrighted and 
*	license-free; it is free for all uses. "
*
\******************************************************************************/
typedef struct
{
    UINT4	twf_k_len;
    UINT4	twf_l_key[40];
    UINT4	twf_s_key[4];
} TWFCTX, ctMEM * pTWFCTX;

int ctDECL TWFInit(pTWFCTX ctx, pUTEXT key, int keylen);
int ctDECL TWFEncrypt(pTWFCTX ctx, pUINT4 in_blk, pUINT4 out_blk);
int ctDECL TWFDecrypt(pTWFCTX ctx, pUINT4 in_blk, pUINT4 out_blk);
/******************************************************************************\
*
*	MDC - MD5 Cipher
*
*	This algorithm uses the MD5 one-way hash function to create a block cipher.
*	One way hash functions such as MD5 are not subject to export restrictions.
*	To create a block cipher using MD5 one-way hash function, we use the
*	following formula:
*
*	To encrypt data:
*		Ci = Pi .xor. H(K,Cj)
*
*	To decrypt data:
*		Pi = Ci .xor. H(K,Cj)
*
*	where:
*		K is a 96 byte key prepared by MDCInit function
*		Cj is the previous cipher text
*		Ci is the current cipher text
*		Pi is the current plain text
*
*	The block size is 128 bits and the algorithm accepts key lengths of
*	64, 128, 192 and 256 bits.
*
\******************************************************************************/
typedef struct
{
	MD5CTX	mdx;
} MDCCTX, ctMEM * pMDCCTX;

int ctDECL MDCInit(pMDCCTX ctx, pUTEXT key, int keylen);
int ctDECL MDCEncrypt(pMDCCTX ctx, pUINT4 inblock, pUINT4 outblock);
int ctDECL MDCDecrypt(pMDCCTX ctx, pUINT4 inblock, pUINT4 outblock);
#ifdef ctCAMOexample
/******************************************************************************\
*
*	REV - Example Cipher (reverses bytes)
*
*	This algorithm demonstrates how to add a custom cipher to FairCom's
*	encryption SDK.  The algorithm simply reverses the bytes of the input.
*
*	The block size is 128 bits and the algorithm accepts key lengths of
*	128 bits.
*
\******************************************************************************/
typedef struct
{
	MD5CTX	mdx;
} REVCTX, ctMEM * pREVCTX;

int ctDECL REVInit(pREVCTX ctx, pUTEXT key, int keylen);
int ctDECL REVEncrypt(pREVCTX ctx, pUINT4 inblock, pUINT4 outblock);
int ctDECL REVDecrypt(pREVCTX ctx, pUINT4 inblock, pUINT4 outblock);
#endif /* ctCAMOexample */
/******************************************************************************\
*
*	RNG - pseudo Random Number Generator
*
\******************************************************************************/
#define RNG_RESEED		16
#define RNG_SUCCESS		1
#define RNG_FAILED		0

#ifdef ctPortWIN32
#ifndef ctPortWNTMIPS
#ifndef ctPortWINKE
#ifndef ctPortWINCE_SRVR
#ifndef ctPortWINIOT
#define ctRNG_SEED
#define	ctRNG_SEED_WINDOWS
#endif
#endif
#endif
#endif
#endif

#ifdef ctPortUNIX
#ifndef ctPortNCRUNIX386
#define ctRNG_SEED
#define ctRNG_SEED_UNIX
#define ctRNG_SEED_DEV_RANDOM
#endif
#endif

#ifndef ctRNG_SEED
#define ctRNG_SEED_GENERIC
#endif

typedef struct
{
	UINT4	counter;
	UINT4	input[4];
	AESCTX	cipher;
} RNGCTX, ctMEM * pRNGCTX;

int ctDECL RNGInit(pRNGCTX rnx);
int ctDECL RNGRead(pRNGCTX rnx, pUTEXT buffer, int size);
void ctDECL RNGFinal(pRNGCTX rnx);
int FIPS_140_1(pUTEXT bit_string);


/******************************************************************************\
*
*	Openssl encryption.
*	This can be used by any Openssl supported cipher.  Uses the EVP
*	API.
*
\******************************************************************************/
#ifdef ctFeatSSL_ENCRYPT
#define FCSSL_BLOCKSIZE  2048  /* Ideally, this would match ctCAMOblkSIZE */
#define ctSSLMAX_BLOCK_LENGTH 16 /* Should be EVP_MAX_BLOCK_LENGTH in general. AES is 16 */
#define FCS_MAXKEY	64

typedef struct evp {
	const void * cipher;
	void * ctx;	
	unsigned char key[FCS_MAXKEY]; 
	unsigned char outbuf[FCSSL_BLOCKSIZE+ctSSLMAX_BLOCK_LENGTH]; /* working space */
	int keylen;
} EVPCTX;
#endif


/******************************************************************************\
*
*	Base64 encoding.
*	This can be used by any Openssl supported cipher.  Uses the EVP
*	API.
*
\******************************************************************************/
pTEXT Base64Encode(pTEXT inputBuffer, VRLEN inlen, pTEXT outBuffer, pVRLEN outlen);
pTEXT Base64Decode(pTEXT inputBuffer, pTEXT outbuf, pVRLEN outsize);

/******************************************************************************\
*
*	FCS - FairCom Cipher Standard interface
*	The FCSCTX provides a standard interface to all ciphers in library
*
\******************************************************************************/
enum _CIPHER_MODE
{
	CIPHER_ECB = 0,				/* Electronic CodeBook mode		*/
	CIPHER_CBC,				/* Cipher Block Chaining mode		*/
	CIPHER_OFB,				/* Output-FeedBack mode			*/
	CIPHER_OPENSSL=0x10000000,		/* Use OpenSSL implementation 		*/
	
};
#define CIPHER_MODE_MASK (~(CIPHER_OPENSSL))

enum _CIPHER_TYPES
{
	CIPHER_CAM = 1,				/* FairCom's original ctCAMO		*/
	CIPHER_DES,				/* DES					*/
	CIPHER_BLF,				/* Blowfish				*/
	CIPHER_TWF,				/* Twofish				*/
	CIPHER_RIJ,				/* Rijndael (legacy version)		*/
	CIPHER_MDC,				/* MD5 Block cipher			*/
	CIPHER_AES_2,				/* AES (second version)			*/
	CIPHER_AES,				/* AES (current version)		*/
#ifdef ctCAMOexample
	CIPHER_REV,				/* Example (just reverses bytes)	*/
#endif
	CIPHER_LAST				/* Last cipher marker			*/
};

enum _CIPHER_ERROR
{
	CIPHER_OK = 0,				/* no errors detected			*/
	CIPHER_INVCONTEXT,			/* invalid context			*/
	CIPHER_INVTYPE,				/* invalid cipher type			*/
	CIPHER_INVMODE,				/* invalid cipher mode			*/
	CIPHER_INVKEYLEN,			/* invalid key length			*/
	CIPHER_INVIVLEN,			/* invalid iv length			*/
	CIPHER_INVBLOCKLEN,			/* invalid block length			*/
	CIPHER_NULARG,				/* invalid data argument		*/
	CIPHER_NOMEMORY,			/* out of heap memory			*/
	CIPHER_UNKNOWN,				/* unknown error condition		*/
	CIPHER_OSSLERR				/* OpenSSL specific error		*/
};

#ifdef ctFeatSSL_ENCRYPT_DEFAULT
#define DEFAULT_CIPHER_MODE CIPHER_CBC|CIPHER_OPENSSL
#else
#define DEFAULT_CIPHER_MODE CIPHER_CBC
#endif


#define FCS_MAXSIZE		4
	
typedef int (*encfnc_t)(pVOID, pUINT4, pUINT4);
typedef int (*decfnc_t)(pVOID, pUINT4, pUINT4);

#define FCSCTX_ATTR_COPY_IV 0x00000001	/* memcpy iv instead of _pack32	*/
#define FCSCTX_ATTR_OPENSSL 0x00000002  /* prefer openssl implementation   */

typedef struct
{
	int		type;		/* cipher type			*/
	int		mode;		/* cipher mode			*/
	int		block;		/* cipher block size		*/
	int		ivlen;		/* valid iv bytes 		*/
	UINT4	iv[FCS_MAXSIZE];	/* initial vector		*/
	UTEXT	ek[FCS_MAXSIZE*4];	/* OFB mode encrypt register	*/
	int		scip;		/* OFB mode index		*/
	encfnc_t	encrypt;
	decfnc_t	decrypt;
	LONG		attr;		/* cipher attributes		*/
	union
	{
		DESCTX des;
		BLFCTX blf;
		TWFCTX twf;
		RIJCTX rij;
		MDCCTX mdc;
#ifdef ctCAMOexample
		REVCTX rev;
#endif
#ifdef ctFeatSSL_ENCRYPT
		EVPCTX osl; /* any OPENSSL CIPHER */
#endif
	} context;
} FCSCTX, ctMEM * pFCSCTX;

typedef struct {
	UTEXT	mb_rand[16];
	UTEXT	mb_fill[96];
	UTEXT	mb_hash[16];
} masbuf_t;

#ifdef ctFeatAEK256
typedef struct {
	LONG	es_len;		/* data length (size of this structure)	*/
	UTEXT	es_rand[16];	/* random number (salt)			*/
	UTEXT	es_pass[64];	/* encryption key			*/
	UTEXT	es_hash[16];	/* hash of salt and key			*/
	LONG	es_plen;	/* encryption key length		*/
} encstore_t;
#endif

extern NINT	ctcmologcip;	/* Default log cipher. */
#ifdef ctFeatCAMOsdkKEYWORD
extern NINT	cmosdksup;	/* Advanced encryption support status. */
extern NINT	chgmstkey;	/* Allow changing master encryption key.*/
extern NINT	cmpchgenc;	/* Allow compact to change encryption settings. */
#endif

#ifdef ctFeatSSL_ENCRYPT
/*  OpenSSL encryption Init is CIPHER ctx->type specific*/
int ctDECL ctOpenSSLInit(FCSCTX * ctx, const unsigned char * key, int keylen, const unsigned char * iv, int ivlen);

/* Other OpenSSL encryption functions are CIPHER independent */ 
int ctDECL ctOpenSSLEncrypt(FCSCTX * ctx, unsigned char * data, int size);
int ctDECL ctOpenSSLDecrypt(FCSCTX * ctx, unsigned char * data, int size);
int ctDECL ctOpenSSLFinal(FCSCTX * ctx);
#endif

/* ctCreateEncryptedStore options: */

#define ctCES_SYSLEVEL	0x00000001	/* Create an encrypted store that can be
					** decrypted by any user account on the
					** system. */
#define ctCES_ENTROPY	0x00000002	/* Include entropy data */

/*
 Error codes returned from ctCreateEncryptedStore() and ctReadEncryptedStore():
*/
#define ENCST_ERR_INTERNAL	-1	/* internal error */
#define ENCST_ERR_NOT_SUPPORTED	1	/* feature not supported */
#define ENCST_ERR_MAX_KEYLEN	2	/* key length exceeds maximum */
#define ENCST_ERR_MEMALLOC	3	/* memory allocation failure */
#define ENCST_ERR_RNDGEN	4	/* error generating random value */
#define ENCST_ERR_CREATE	5	/* could not create encrypted store file */
#define ENCST_ERR_WRITE		6	/* error writing to encrypted store file */
#define ENCST_ERR_ENCRYPT	7	/* error encrypting data */
#define ENCST_ERR_ADDKEYRING	8	/* could not add key to keyring */
#define ENCST_ERR_SETPERM	9	/* could not set permission on encrypted store file */
#define	ENCST_ERR_OPEN		10	/* could not open encrypted store file */
#define	ENCST_ERR_READ		11	/* could not read encrypted store file */
#define	ENCST_ERR_SEEK		12	/* could not seek to offset in encrypted store file */
#define ENCST_ERR_DECRYPT	13	/* error decrypting data */
#define ENCST_ERR_GETKEY	14	/* could not get key from keyring */
#define ENCST_ERR_VERIFY	15	/* key store data verification failed */

int   ctDECL FCSInit(pFCSCTX ctx, int type, int mode, pUTEXT key, int keylen, pUTEXT iv, int ivlen);
int   ctDECL FCSEncrypt(pFCSCTX ctx, pUTEXT data, int size);
int   ctDECL FCSDecrypt(pFCSCTX ctx, pUTEXT data, int size);
void   ctDECL FCSResetIV(pFCSCTX ctx, const UTEXT * iv, int ivlen);
int   ctDECL FCSFinal(pFCSCTX ctx);
#ifdef ctFeatAEK256
int   ctDECL FCSCreateMasterFile(pTEXT password, VRLEN passlen, pTEXT filnam, pTEXT errbuf, VRLEN keylen, NINT errbuflen);
int   ctDECL FCSVerifyMasterPassword(pTEXT password, VRLEN passlen, pTEXT filnam, pTEXT errbuf, NINT errbuflen);
#else
int   ctDECL FCSCreateMasterFile(pTEXT password, pTEXT filnam);
int   ctDECL FCSVerifyMasterPassword(pTEXT password, pTEXT filnam, pTEXT errbuf);
#endif
pTEXT ctDECL FCSGetPassword(pTEXT prompt);
NINT  ctDECL ctcmogetmaspwd(pTEXT masfilnam);
#ifdef ctFeatENCSTORE
NINT  ctDECL ctCreateEncryptedStore(pTEXT key, NINT keylen, pTEXT encnam, pTEXT errbuf, NINT errbuflen, NINT options);
NINT  ctDECL ctReadEncryptedStore(pTEXT fkfname, pTEXT pvfname, pTEXT key, NINT keylen, pTEXT errbuf, NINT errbuflen);
#endif
/******************************************************************************\
*
*	Key Generation routines
*
*	GenMasterKey  	- Generate master key from a user supplied password
*	GenSessionKey	- Generate session key
*
\******************************************************************************/
void ctDECL GenMasterKey(pTEXT password, int pwdbytes, pUTEXT key, int keybytes);
void ctDECL GenSessionKey(pRNGCTX rnx, pUTEXT SessionKey, int keylen);
/******************************************************************************\
*
*	end protection against c++ compilers
*
\******************************************************************************/
#ifdef __cplusplus
}
#endif
/******************************************************************************/
#endif /* _CTCRSDK_H_ */

/* end of ctcrsdk.h */

