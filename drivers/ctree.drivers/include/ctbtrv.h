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


#ifndef	ctNOGLOBALS
*** YOU MUST COMPILE WITH #define ctNOGLOBALS ***
#endif
#ifndef	RESOURCE
*** YOU MUST COMPILE WITH #define RESOURCE ***
#endif
/* CTSUPER checked below... */

#define	BTI_SINT	short int

typedef	struct {
	BTI_SINT	keyPos;
	BTI_SINT	keyLen;
	BTI_SINT	keyFlag;
	TEXT		num_keys[4];
/*	LONG		num_keys;	no alignment guaranteed */
	TEXT		keyType;
	TEXT		Null;		/* not filled in yet */
	TEXT		notUsed[2];
	TEXT		manualKeyNumber;/* not filled in yet */
	TEXT		acsNumber;	/* not filled in yet */
} KEY_SPEC_TYPE;

typedef	struct {
	BTI_SINT	recordLength;
	BTI_SINT	pageSize;
	/* V6 format, V7 breaks into two 1 byte fields
	 * BTI_SINT	indexCount;
	 */
	union {
		struct {
			unsigned char	indexCount;
			unsigned char	file_version;
		} v7_bti_stat;
		BTI_SINT	indexCount;
	} bti_ver;
	TEXT		num_recs[4];
/*	LONG		num_recs;	no alignment guaranteed */
	BTI_SINT	fileFlags;
	TEXT		dupPointers;	/* not filled in yet */
	TEXT		NotUsed;
	BTI_SINT	preAlloc;
	/* KEY_SPEC_TYPE    up to 24(V5.1)  119(V6.1) */
} FILE_SPEC_TYPE;
				/* isam_err to stat */
typedef int	BTERRNO;
typedef struct {
	BTERRNO	stat;
	COUNT	ct_err;
} ERROR_CNV;
				/* sysiocod to stat */
typedef struct {
	BTERRNO	stat;
	COUNT	sys_errno;
} ERRNO_CNV;
				/* Schema Symbolic Constant */
typedef struct {
	pTEXT	name;
	COUNT	ftype;
} SCHEMA_CNV;
				/* Btrieve version */
typedef	struct	{
	COUNT	ver;
	COUNT	rev;
	TEXT	flg[1];
} BT_VER;

#define	MAX_INDEXES	119
typedef struct {
	COUNT	lokmod;
	COUNT	key_num;
	TEXT	variable;
	TEXT	compressed;
	TEXT	has_nonmods;	/* TRUE if this file has indexes that aren't modifiable */
	TEXT	is_huge;	/* flag if file is huge enabled */
	struct BT_OTHER_INDEXES {
		int	ismod;
/*		pVOID	keybefore;
		pVOID	keyafter;
*/
	} indexes[MAX_INDEXES];
	TEXT	bt_index_off;	/* turned on during a fast load */
	TEXT	bt_tran_off;	/* turned on during a fast load w/o logging */
} BT_OTHER;
				/* Position Block */
typedef	struct {
	COUNT	datno;		/* 2bytes current datno */
	COUNT	keyno;		/* 2bytes current keyno */
	COUNT	supno;		/* 2bytes current superfile datno */
	COUNT	supfm;		/* 2bytes current superfile filmod */
	IFIL	ifil;		/* 36bytes */
	VRLEN	recptr;		/* 4bytes current record pointer */
	pTEXT	bufptr;		/* 4bytes record buffer pointer */
	VRLEN	buflen;		/* 4bytes current buffer length */
	pVOID	ifilmem;	/* 4bytes from GETIFIL (mbfree this) */
	BT_OTHER *bt_otherp;	/* 4bytes pointer to other BT data */
#if defined(PROFILE_TIMES) && defined (SUPER_PROFILE)
	struct str_optimes {
		long calls[2];
		struct timeval total_time[2];
	} *optimes;
/*#define	PROF_PTR	sizeof(void *)*/
#define	MAX_OP		64
#else
/*#define	PROF_PTR	0*/
#endif
	pTEXT	filename;	/* table's path without the server */
	pTEXT	serv_n_file;	/* set for debug log */
	NINT	inst_num;	/* server's slot number in server_insts[] */
	COUNT	last_op;	/* last operation performed */

/* !!WARNING!! DO NOT add new members to CT_POSBLK struct
 * CT_POSBLK is full, add new struct members to BT_OTHER instead
 * NOTE: DST's BlockID feature use the last byte of CT_POSBLK structure */

#ifdef OLD_CODE
/* NOTE! eventhough this filler isn't used anymore, 
 * CT_POSBLK must be <= 128 bytes
 */
	/* we store the filename for debugging here,
	 * a 64 bit machine requires this to be smaller to still be 128 bytes
	 */
#if defined(ct8P) || defined(__alpha)
	TEXT    dummy[19-PROF_PTR];
#else
	TEXT	dummy[62-PROF_PTR];
#endif
#endif /* OLD_CODE */
} CT_POSBLK;
				/*
				 * Position Block only have 128 bytes
				 * allocated in user application.
				 * Unfortunately, there is no space 
				 * to hold whole buffer obtained 
				 * GETIFIL(). CT_POSBLK only holds
				 * IFIL. If you need IIDX or ISEG,
				 * you should call GETIFIL() each
				 * time.
				 */

/* The posBlock passed by Btrieve application points to a 128 bytes area.
 * We use this area to store the CT_POSBLK thus its size must be <= 128 bytes.
 * The code below is a trick to cause a compile error if CT_POSBLK size is > 128 bytes.
 * NOTE: compiling for 64-bit enlarges the struct due to 8-bytes pointers */
typedef char CT_POSBLK_must_be_less_or_equal_128_bytes[2*(sizeof(CT_POSBLK) <= 128)-1];

/* File Flag Value */
#define	BT_FMOD_VAR	     1		/* Variable Length Record */
#define	BT_FMOD_BLN	     2		/* Brank Truncation */
#define	BT_FMOD_PRE	     4		/* Brank Truncation */
#define	BT_FMOD_CMP	     8		/* Data Compression */
#define	BT_FMOD_KEY	    16		/* Key Only File    */
#define	BT_FMOD_10S	    64		/* 10% Free Space   */
#define	BT_FMOD_20S	   128		/* 20% Free Space   */
#define	BT_FMOD_30S	   192		/* 30% Free Space   */

/* Key Flag Value */

#define	BT_KFLG_DUP	0x0001		/* Duplicate */
#define	BT_KFLG_MOD	0x0002		/* Modifiable */
#define	BT_KFLG_BIN	0x0004		/* Binary */
#define	BT_KFLG_NUL	0x0008		/* Null */
#define	BT_KFLG_SEG	0x0010		/* Segmented */
#define	BT_KFLG_ALT	0x0020		/* Alt Col Seq Enable */
#define	BT_KFLG_DSC	0x0040		/* Decending Key Seg. */
#define	BT_KFLG_SUP	0x0080		/* Supplemental */
#define	BT_KFLG_EXT	0x0100		/* Extended Key Seg. */
#define	BT_KFLG_MAN	0x0200		/* Manual */

/* Extended Key Types */

#define	BT_KTYP_STR	0		/* String */
#define	BT_KTYP_INT	1		/* Integer (signed int)*/
#define	BT_KTYP_FLT	2		/* Float (IEEE) */
#define	BT_KTYP_DAT	3		/* Date  */
#define	BT_KTYP_TIM	4		/* Time  */
#define	BT_KTYP_DEC	5		/* Decimal */
#define	BT_KTYP_MON	6		/* Money */
#define	BT_KTYP_LOG	7		/* Logical */
#define	BT_KTYP_NUM	8		/* Numeric */
#define	BT_KTYP_BFL	9		/* BFloat (Not supported C)*/
#define	BT_KTYP_LST	10		/* Lstring (1stByte has len.)*/
#define	BT_KTYP_ZST	11		/* Zstring (Null terminated)*/
#define	BT_KTYP_UBN	14		/* Unsigned Binary */
#define	BT_KTYP_INC	15		/* Auto Increment */

#ifdef	__UNIX__
#define	DIR_SEP		'/'
#else
#define	DIR_SEP		'\\'
#endif
#ifdef PROTOTYPE
pTEXT	mballc(NINT , UINT);
#else
pTEXT	mballoc();
#endif
		/*
		 * c-tree recbuf   0-1: 2 bytes for delete flag
		 *                 using COUNT as a delete flag is
		 *                 for portability (vs just 1st byte).
		 *		   2-3: 2 bytes for an update counter
		 *			(used for conflict error checking)
		 * c-tree recbuf   4-7: 4 bytes for storing SRLSEG
		 *                 auto increment counter for STEP
		 *                 operation. c-tree does not support
		 *                 physical order NXT/PRV REC especially
		 *                 in SUPERFILE. keyno == 1 is reserved
		 *                 for this segment to handle STEP 
		 *                 operation.
		 *
		 * c-tree recbuf   8-[end] is for actual user record 
		 *                 buffer.
		 */

/*#define	DELFLG_LEN	(sizeof(COUNT))*/
#define	DELFLG_LEN	(sizeof(LONG))	/* needed to align worst case... */
#define SERNO_TYPE	LONG
#define	RECBYT_LEN	(sizeof(SERNO_TYPE))

/*#define DEFAULT_XTDSIZ	4096 */	/* minimum xtdsiz for all .dat .idx */
#define FILENAME_HAS_FULLPATH
#define	BT_SEPARATE_IDX		/* each index has separate index file */
#undef	BT_SUPERFILE 		/* Use super file for one Btreive file */

#ifdef	BT_SUPERFILE
#ifndef	CTSUPER
*** YOU MUST COMPILE WITH #define CTSUPER ***
#endif
#ifdef	FILENAME_HAS_FULLPATH
#undef	FILENAME_HAS_FULLPATH
#endif
#endif	/* BT_SUPERFILE */

#define	DODA_EXTENT	".dda"	/* for DODA setup file */
#define	SERVER_ALIGN	4	/* needed if server is 32bit aligned */

#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(P) (P=P)
#endif

#ifdef ctBTRIEVE_API

#ifdef ctPortWIN32
#define BTI_API ctCONV COUNT WINAPI
#define DLLexport __declspec(dllexport)
#define DLLimport __declspec(dllimport)
#else
#define BTI_API ctCONV COUNT ctDECL
#define DLLexport
#define DLLimport extern
#endif

DLLexport BTI_API BTRV(
	UCOUNT	operation,
	pVOID	posBlock,
	pVOID	dataBuffer,
	pUCOUNT	dataLength,
	pVOID	keyBuffer,
	COUNT	keyNumber );
DLLexport BTI_API BTRVID(
	UCOUNT	operation,
	pVOID	posBlock,
	pVOID	dataBuffer,
	pUCOUNT	dataLength,
	pVOID	keyBuffer,
	COUNT	keyNumber,
	pUTEXT	clientID );
DLLexport BTI_API BTRCALL(
	UCOUNT	operation,
	pVOID	posBlock,
	pVOID	dataBuffer,
	pULONG	dataLength,
	pVOID	keyBuffer,
	UTEXT	keyLength,
	TEXT	ckeynum );
DLLexport BTI_API BTRCALLID(
	UCOUNT	operation,
	pVOID	posBlock,
	pVOID	dataBuffer,
	pULONG	dataLength,
	pVOID	keyBuffer,
	UTEXT	keyLength,
	TEXT	ckeynum,
	pUTEXT	clientID );
	
#endif /* ctBTRIEVE_API */

/* end of ctbtrv.h */
