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

#ifndef CTSSL_H
#define CTSSL_H

#undef  __
#ifdef PROTOTYPE
#define __(args)        args
#else
#define __(args)        ()
#endif

#ifdef ctFeatOPENSSLstatic

#include <openssl/bio.h>
#include <openssl/pem.h>
#include <openssl/err.h>

typedef     NINT (*pBIO_freeFNC) __((BIO *));
typedef    BIO * (*pBIO_new_fileFNC) __((cpTEXT filename, cpTEXT mode));
typedef BIGNUM * (*pBN_bin2bnFNC) __((const unsigned char *, NINT, BIGNUM *));
typedef     NINT (*pBN_bn2binFNC) __((const BIGNUM *, pUTEXT));
typedef BIGNUM * (*pBN_dupFNC)__((const BIGNUM *));
typedef     VOID (*pBN_freeFNC) __((BIGNUM *));
typedef     NINT (*pBN_num_bitsFNC) __((const BIGNUM *));
typedef     DH * (*pDH_newFNC) __((VOID));
typedef     NINT (*pDH_compute_keyFNC) __((pUTEXT, const BIGNUM *, DH *));
typedef     VOID (*pDH_freeFNC) __((DH *));
typedef     NINT (*pDH_generate_keyFNC) __((DH *));
typedef unsigned long (*pERR_get_errorFNC) __((VOID));
typedef     DH * (*pPEM_read_bio_DHparamsFNC) __((BIO *bp, DH **x, pem_password_cb *cb, pVOID u));

typedef DH CTDH, * CTPDH;
typedef BIGNUM CTBN, * CTPBN;
typedef BIO CTBIO, * CTPBIO;

#ifndef ctFeatSSL
extern   VOID BIO_free __((CTPBIO));
extern CTPBIO BIO_new_file __((cpTEXT filename, cpTEXT mode));
extern  CTPBN BN_bin2bn __((const unsigned char *, NINT, CTPBN));
extern   NINT BN_bn2bin __((CTPBN, pUTEXT));
extern   VOID BN_free __((CTPBN));
extern   NINT BN_num_bits __((const CTPBN));
extern  CTPDH DH_new __((VOID));
extern   NINT DH_compute_key __((pUTEXT, CTPBN, CTPDH));
extern   VOID DH_free __((CTPDH));
extern   NINT DH_generate_key __((CTPDH));
extern unsigned long ERR_get_error __((VOID));
extern  CTPDH PEM_read_bio_DHparams __((CTPBIO bp, CTPDH *x, pVOID cb, pVOID u));
#endif

#define ctpBN_num_bytes(a) BN_num_bytes(a)

#else  /* ~ctFeatOPENSSLstatic */

typedef struct {
	int pad;
	int version;
	void *p;
	void *g;
	long length;
	void *pub_key;
	void *priv_key;
} CTDH, *CTPDH;

typedef void CTBN, * CTPBN;
typedef void CTBIO, * CTPBIO;

typedef   VOID (*pBIO_freeFNC) __((CTPBIO));
typedef CTPBIO (*pBIO_new_fileFNC) __((cpTEXT filename, cpTEXT mode));
typedef  CTPBN (*pBN_bin2bnFNC) __((pUTEXT, NINT, CTPBN));
typedef   NINT (*pBN_bn2binFNC) __((CTPBN, pUTEXT));
typedef  CTPBN (*pBN_dupFNC) __((const CTPBN));
typedef   VOID (*pBN_freeFNC) __((CTPBN));
typedef   NINT (*pBN_num_bitsFNC) __((const CTPBN));
typedef  CTPDH (*pDH_newFNC) __((VOID));
typedef   NINT (*pDH_compute_keyFNC) __((pUTEXT, CTPBN, CTPDH));
typedef   VOID (*pDH_freeFNC) __((CTPDH));
typedef   NINT (*pDH_generate_keyFNC) __((CTPDH));
typedef unsigned long (*pERR_get_errorFNC) __((VOID));
typedef  CTPDH (*pPEM_read_bio_DHparamsFNC) __((CTPBIO bp, CTPDH *x, pVOID cb, pVOID u));

#define ctpBN_num_bytes(a) ((ctpBN_num_bits(a)+7)/8)

#endif /* ~ctFeatOPENSSLstatic */

typedef struct ctssli {
	NINT				sctsslenabled;
	pTEXT				sdllname;
	pVOID				sdllhandle;
	pBIO_freeFNC			spBIO_free;
	pBIO_new_fileFNC		spBIO_new_file;
	pBN_bin2bnFNC			spBN_bin2bn;
	pBN_bn2binFNC			spBN_bn2bin;
	pBN_dupFNC			spBN_dup;
	pBN_freeFNC			spBN_free;
	pBN_num_bitsFNC			spBN_num_bits;
	pDH_compute_keyFNC		spDH_compute_key;
	pDH_freeFNC			spDH_free;
	pDH_generate_keyFNC		spDH_generate_key;
	pDH_newFNC			spDH_new;
	pERR_get_errorFNC		spERR_get_error;
	pPEM_read_bio_DHparamsFNC	spPEM_read_bio_DHparams;
} CTSSLI, *pCTSSLI;

#define CT_SSL_FIRST_FUNCTION		spBIO_free

#define ctsslenabled			ctsslinf.sctsslenabled

#define ctssldllname			ctsslinf.sdllname
#define ctsslfnccount			ctsslinf.sfnccount
#define ctsslfncnames			ctsslinf.spfncnames
#define ctpBIO_free			ctsslinf.spBIO_free
#define ctpBIO_new_file			ctsslinf.spBIO_new_file
#define ctpBN_bin2bn			ctsslinf.spBN_bin2bn
#define ctpBN_bn2bin			ctsslinf.spBN_bn2bin
#define ctpBN_dup			ctsslinf.spBN_dup
#define ctpBN_free			ctsslinf.spBN_free
#define ctpBN_num_bits			ctsslinf.spBN_num_bits
#define ctpDH_compute_key		ctsslinf.spDH_compute_key
#define ctpDH_free			ctsslinf.spDH_free
#define ctpDH_generate_key		ctsslinf.spDH_generate_key
#define ctpDH_new			ctsslinf.spDH_new
#define ctpERR_get_error		ctsslinf.spERR_get_error
#define ctpPEM_read_bio_DHparams	ctsslinf.spPEM_read_bio_DHparams

/* Diffie-Hellman secure key exchange parameters. */

#define CTKXLEN	128	/* 1024 bit secure key exchange prime/key length */

#ifdef __CTINIT_C__
UTEXT ctkxparams_p[CTKXLEN] = {
	0xCD,0x11,0x69,0x5B,0xC1,0x5F,0x15,0x4E,0xFE,0x84,0x99,0x31,
	0x8C,0x3B,0xF2,0x5E,0xCD,0x07,0x96,0x3D,0xFC,0xFF,0xC1,0x7A,
	0x22,0xCB,0xD5,0xE1,0x8A,0x45,0xD8,0x1B,0x68,0x8A,0xBB,0x7A,
	0x3D,0xCD,0xE0,0xA8,0x4F,0x65,0x31,0x79,0x5E,0xFD,0xE1,0xF5,
	0xB0,0x15,0x5F,0x69,0xC3,0xD0,0x8E,0xDD,0x1E,0x5F,0x5D,0x67,
	0x5F,0xC6,0xB4,0x02,0xF9,0xF9,0x73,0x9C,0x59,0x68,0x28,0x24,
	0x09,0xE8,0x99,0x27,0xDA,0x15,0x07,0xED,0xE9,0xEA,0x08,0x2C,
	0xA6,0x15,0xB9,0xFE,0xD7,0x24,0x3B,0xB0,0x4D,0x2F,0x34,0xA4,
	0x7D,0x41,0x8B,0x1A,0x6B,0xAA,0x71,0x4F,0xF6,0x3E,0xEC,0x5B,
	0x85,0x5D,0xC3,0xB5,0xBF,0x8E,0xEF,0xE3,0x5D,0xC2,0x69,0x92,
	0xC7,0xD2,0xCA,0x72,0x34,0x8E,0x35,0x33
};
UTEXT ctkxparams_g = 0x02;
#else
extern UTEXT ctkxparams_p[CTKXLEN];
extern UTEXT ctkxparams_g;
#endif

#endif /* ~CTSSL_H */

/* end of ctssl.h */
