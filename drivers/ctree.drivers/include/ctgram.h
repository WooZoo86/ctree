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

typedef union {
	COUNT   yInt;
	LONG    ySigned;
	ULONG   yUnsign;
	pTEXT   yText;
	double  yReal;
	PTREE   yTree;
} YYSTYPE;
#define IDENTIFIER	257
#define TEXTCONST	258
#define SIGNEDCONST	259
#define UNSIGNCONST	260
#define REALCONST	261
#define L_AND	262
#define L_OR	263
#define R_LT	264
#define R_LE	265
#define R_EQ	266
#define R_NE	267
#define R_GT	268
#define R_GE	269
#define T_INT	270
#define T_UNSIGNED	271
#define T_LONG	272
#define T_DOUBLE	273
#define F_ATOI	274
#define F_ATOL	275
#define F_ABS	276
#define F_LABS	277
#define F_FABS	278
#define F_ATOF	279
#define F_CEIL	280
#define F_FLOOR	281
#define F_FMOD	282
#define F_STRLEN	283
#define F_STRCMP	284
#define F_STRICMP	285
#define F_STRNCMP	286
#define F_STRNICMP	287
#define F_MEMCMP	288
extern YYSTYPE yylval;
/* end of ctgram.h */

