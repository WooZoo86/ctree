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
#ifndef _CTDBGRAM_H_
#define _CTDBGRAM_H_

typedef union {
	NINT	yInt;
	pTEXT   yText;
	PTREE   yTree;
	pCTSYMBOL ySymb;
} YYSTYPE;
#define IDENTIFIER	257
#define CONSTANT	258
#define FUNCTION	259
#define L_AND	260
#define L_OR	261
#define R_LT	262
#define R_LE	263
#define R_EQ	264
#define R_NE	265
#define R_GT	266
#define R_GE	267
#define F_AS	268
#define F_CAST	269
#define F_FUNCTION	270
#define T_TYPE	271
#define F_ERROR	272
#define T_INT	273
#define T_UNSIGNED	274
#define T_DOUBLE	275
#define IS	276
#define NOT	277
#define NUL	278
extern YYSTYPE yylval;

#endif /* ~_CTDBGRAM_H_ */

/* end of ctdbgram.h */
