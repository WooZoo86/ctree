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

#ifndef __CTFTSTOK_INCLUDED
#define __CTFTSTOK_INCLUDED

struct ct_tokenizer_param
{
	char* param1;
	char* param2;
	unsigned long fieldmode;
};
typedef struct ct_tokenizer_param CTTKNZR_PARAM;

typedef void * (*CT_TOK_INIT) (char*, size_t, long, CTTKNZR_PARAM* , int*);
typedef int (*CT_TOK_RESET) (void *, char*, size_t);
typedef char * (*CT_TOK_NEXT) (void*, int *);
typedef void (*CT_TOK_END) (void*);

struct ct_tokenizer 
{
	CT_TOK_INIT ct_tok_init;
	CT_TOK_RESET ct_tok_reset;
	CT_TOK_NEXT ct_tok_next;
	CT_TOK_END ct_tok_end;
};

typedef struct ct_tokenizer CTTOKENIZER;

extern CTTOKENIZER tokenizers[];
#endif	/* PORTER_INCLUDED */

