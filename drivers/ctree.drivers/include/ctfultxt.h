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

#ifndef _ct_fultxt_included
#define _ct_fultxt_included
 /*********************************/
 /* FTS support tables definition */
 /*********************************/
#define TOKEN_DICT_EXT ".twd"
#define TOKEN_DICT_IDX_EXT ".twi"
#define REFR_TABLE_EXT ".trd"
#define REFR_TABLE_IDX_EXT ".tri"
#define FTI_SUPERFILE_EXT ".FTI"
#define FTID_SUPERFILE_EXT ".FTD"

/* Reference table for full text index on multiple fields- has field_id field. */
#define FTSrefRecFld	0	/* field number of rec_id field in reference table record */
#define FTSrefWordFld	1	/* field number of word_id field in reference table record */
#define FTSrefFieldFld  2	/* field number of field_id field in reference table record */
#define FTSrefOffsetFld 3	/* field number of offset field in reference table record */

/* Reference table for full text index on one field- no field_id field. */
#define FTSrefRecFld1	0	/* field number of rec_id field in reference table record */
#define FTSrefWordFld1	1	/* field number of word_id field in reference table record */
#define FTSrefOffsetFld1 2	/* field number of offset field in reference table record */

#define FTSrefwrIdx	0	/* index number of reference index */

#define FTSdicAttrFld	0	/* field number of attr field in dictionary table record */
#define FTSdicWordFld	1	/* field number of word field in dictionary table record */

#define FTSdicWordIdx	0	/* index number of word index */

/* Word dictionary attr field bits: */
#define FTSdicAttrSTOPWORD	0x0000001	/* stop word */

#define FTS_WORD_ID_LEN		4	/* 4-byte word ID */
#define FTS_FIELD_ID_LEN	2	/* 2-byte field number */
#define FTS_RECORD_ID_LEN	8	/* 8-byte record serial number (rowid) */

/* Length of reference table word index for a full text index that contains multiple fields:
word_id, field_id, rec_id */
#define FTSrefwrKeylen (FTS_WORD_ID_LEN + FTS_FIELD_ID_LEN + FTS_RECORD_ID_LEN)

/* Length of reference table word index for a full text index that contains one field:
word_id, rec_id */
#define FTSrefwrKeylen1 (FTS_WORD_ID_LEN + FTS_RECORD_ID_LEN)
/* Estimate the document count for each search term and pick the term with
the lowest cardinality. */
#ifdef ctSRVR
#define ctFeatFTS_ESTDOCCNT
#endif

/* Support for OR operator. Off because this support is not yet implemented. */
/*
#define ctFeatFTS_OR_SUPPORT
*/

/* Enable this option to support debug logging for diagnostic purposes. */
#define ctFeatFTS_DEBUG

#ifdef ctFeatFTS_DEBUG
typedef struct ftsqopt {
	NINT	debug;
} FTSQOPT, *pFTSQOPT;
#endif
typedef enum { QTN_ERROR, QTN_VALUE, QTN_FIRSTVALUE, QTN_STARTSWITH, QTN_PHRASE, QTN_NOT, QTN_AND, QTN_OR, QTN_NEAR } QueryTreeNodeType;
typedef struct QueryTreeNode
{
#ifdef ctFeatFTS_ESTDOCCNT
	LONG8	wordID;		/* word ID saved when estimating document count for this word */
#endif
	struct QueryTreeNode *left;		/* left subtree */
	struct QueryTreeNode *right;		/* right subtree */
	pTEXT	value;		/* the search word usually */
	QueryTreeNodeType type;		/* type of node */
	UINT	modifier;	/* modifier bits */
	ULONG	distance;	/* max distance between words for NEAR queries */
} QueryTreeNode;

/*************************/
/* FTS context structure */
/*************************/
typedef struct tagFTctx FTctx, ctMEM* pFTctx;
struct tagFTctx {
	CTHANDLE wRecord;	/* record handle for word dictionary */
	CTHANDLE rRecord;	/* record handle for reference table */

	QueryTreeNode*
		queryAST;	/* query abstract syntax tree */
#ifdef ctFeatFTS_ESTDOCCNT
	QueryTreeNode*
		firstWord;	/* first word to search */
#endif
	pVOID	tkhdl;		/* tokenizer handle */
	pTEXT	query;		/* query string */
	FILNO	idxno;		/* c-tree file number of data file's rowid index */
	COUNT	tok;		/* tokenizer list index, identifies tokenizer in use */
#ifdef ctIFNEEDED
	NINT	mode;
#endif
	NINT	field_count;	/* number of fields in the full text index */
	NINT	placeholder_count; /* number of placeholder values in tree */
	NINT	errtype;	/* error type */
	NINT	curpos;		/* current position in query string */
#ifdef ctFeatFTS_DEBUG
	FTSQOPT query_options;	/* options specified in query string */
#endif
};

#ifdef __cplusplus
extern "C" {
#endif
int _ctFTSconfirmQueryTreeMatch(pFTctx ctx, QueryTreeNode* tree, CTUBIGINT doc_id, CTHANDLE rRecord, CTHANDLE wRecord, pNINT perrcode);
ctCONV NINT ctDECL _ctFreeFTSearch(FILNO datno, pFTctx ctxOut);
ctCONV NINT ctDECL _ctAllocFTSearch(FILNO datno, COUNT FTSno, pTEXT query, NINT mode, pFTSERR pftserr, pFTctx *ctxOut);
NINT iGetFTIResources(NINT datno, pCTFNAM *pFTIs, pULONG count, pTEXT cbkbuf, LONG cbkbufsiz);
NINT iUpdFTIResources(NINT datno, pTEXT datname, pCTFNAM newnames, TEXT remote, pTEXT cbkbuf, LONG cbkbufsiz);
#ifdef __cplusplus
}
#endif

#endif /* _ct_fultxt_included */

/* end of ctfultxt.h */
