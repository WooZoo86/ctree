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

/* 16 bit Windows 3.1x */
#include <string.h>
#include <stdlib.h>

#define ctLP
#define ctEXCLCREAT
#define ct_NULL (char *) 0

#ifdef _MT  /* From stddef.h for multi-thread */
#define OWNER	(*_threadid)
#define apOWNER (*_threadid)
#else
#define OWNER	(1)
#define apOWNER (1)
#endif

#define ctLSCAN		/* implies standard model fscanf/printf */

#ifndef SIZEOF
#define SIZEOF 	sizeof
#endif

#ifdef ctPortW16_MEDIUM_MEMORY_MODEL
#define ctrt_popen		ctrt_fopen
#else
#define ctrt_vsprintf		vsprintf
#define ctrt_sprintf		sprintf
#define ctrt_fopen		fopen
#define ctrt_popen		fopen
#endif

#ifndef ctrt_snprintf
#if _MSC_VER <= 1800 /* VS2013 */
#define ctrt_snprintf	_snprintf
#else
#define ctrt_snprintf	snprintf
#endif
#endif

#define ctrt_freopen		freopen
#define ctrt_fclose		fclose
#define ctrt_strcpy(a,b)	_fstrcpy((pTEXT) (a),(pTEXT) (b))
#define ctrt_strcat(a,b)	_fstrcat((pTEXT) (a),(pTEXT) (b))
#define ctrt_strncat(a,b,c)	_fstrncat((pTEXT) (a),(pTEXT) (b), c)
#define ctrt_strcmp(a,b)	_fstrcmp((pTEXT) (a),(pTEXT) (b))
#define ctrt_strncmp(a,b,n) 	_fstrncmp((pTEXT) (a), (pTEXT)(b), n)
#define ctrt_strlen(a)		_fstrlen((pTEXT) (a))
#define ctrt_strncpy(a,b,n)	_fstrncpy((pTEXT) (a),(pTEXT) (b),n)
#define ctrt_memcmp(a,b,n)	_fmemcmp((pVOID) (a),(pVOID) (b),n)
#define ctrt_memchr(a,b,n)	_fmemchr((pVOID) (a),(NINT) (b),n)
#define ctrt_toupper          	toupper
#define ctrt_qsort		qsort
#define ctrt_bsearch		bsearch

#ifndef ctrt_gets
#define ctrt_gets		gets
#endif

#if (defined(NOTFORCE) && defined(TRANPROC))
#define ctrt_getcwd		ctGetCwd /* For Qualifing TRANPROC LOG Paths */
#endif

#define memmove                 _fmemmove
#define ctALLOC
extern void _far * ct_alloc(unsigned int n, unsigned int size);
#define BIGDELM

#define ctPATH_SEP		'\\'

#define icpylng(dp,sp,n) *dp++ = *sp++; *dp++ = *sp++; *dp++ = *sp++; *dp++ = *sp++
#define cpylng(dp,sp,n)  cpy4bf(dp,sp)
#define cpy4bf(dp,sp)    _fmemcpy((pVOID) (dp),(pVOID) (sp),4)
#define cpybuf(dp,sp,n)  _fmemcpy((pVOID) (dp),(pVOID) (sp),(UINT) n)
#define ctsfill(dp,ch,n) _fmemset((pVOID) (dp),ch,n)

#ifndef __WATCOMC__
#define FASTCOMP
#define BIGCHECK
#endif

#define ctcfill          ctcbill
#define FASTRIGHT

#ifndef ctCONV
#define ctCONV
#endif

#ifndef ctDECL
#define ctDECL WINAPI _loadds 
#endif

#ifndef ctDECLV
#define ctDECLV _loadds 
#endif

#ifndef ctDECLT
#define ctDECLT WINAPI
#endif

#define ctMEM  far
#define ctFILE_ACCESS /* Drive Access control */

void cpynbuf(char far *,char far *,unsigned int);
void cpybig(char far *,char far *,long);
void ctafree(void far *);
int ctcfill(char far *,int,long);

extern ctCONV void  	ctDECL	ctrt_exit( int ret );
extern ctCONV int   	ctDECLV	ctrt_fscanf( FILE *fp, char far *fmt, ... );

#ifdef ctPortCONSOLE_APP
#ifndef ctrt_printf
#define ctrt_printf printf	/* ensure console (non-GUI) output */
#endif
#endif

#ifndef ctrt_printf
extern ctCONV void  	ctDECLV	ctrt_printf( char far *fmt, ... );
#endif

extern ctCONV void  	ctDECLV	ctrt_fncmon( char far *fmt, ... );
extern ctCONV void  	ctDECLV	ctrt_fprintf( FILE *fp, char far *fmt, ... );
extern ctCONV char far* ctDECL	ctrt_tmpnam( char far *);

#ifdef ctPortW16_MEDIUM_MEMORY_MODEL
extern ctCONV void  	ctDECLV	ctrt_sprintf( char far *, char far *, ... );
extern ctCONV FILE *	ctDECL	ctrt_fopen(char far *,char far *);
#endif

/* system dependent r-tree default output device names */
#define rtLPT0	"LPT0"
#define rtLPT1	"LPT1"
#define rtLPT2	"LPT2"

/****************************************************************************/
/* ntree needs */
#define NETFRMAT

#define WNDNET
#ifndef DllLoadDS
#define DllLoadDS 	_loadds
#endif
#define cpymbuf		cpybuf
#define cpymsg		cpybuf
#define cpysrcm		cpysrcl

/* Banyan Vines */
#ifdef ctPortVINES
#define ctPROTBYTES
#define ctBAN5
#define	NWPTR	FAR *
#endif
/****************************************************************************/

/* end of ctcmpl_w.h */
