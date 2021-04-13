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

/* DOS BASED Compiler  */

#include <string.h>
#include <stdlib.h>

/****************************************************************************/
/* Pointer Size Definitions */
/* These defines control the size of pointers used in c-tree */
/* YOU MUST DEFINE EITHER ctSP OR ctLP, BUT NOT BOTH. ctSP implies 2 byte pointers. */
/* ctLP implies 4 byte pointers. */

#ifndef ctSP	/* Small Pointers */
#ifndef ctLP	/* Large Pointers */
#define ctLP 	/* Default to 4 byte pointers. */
#endif
#endif

#ifdef 	ctSP
#ifdef	ctLP
#undef 	ctSP
#define ctLP /* Default to 4 byte pointers. */
#endif
#endif

#define ctPATH_SEP		'\\'
/****************************************************************************/

/****************************************************************************/
/* File issues: I/O; Create; Updates; ect                                   */
#define ctEXCLCREAT 	 /* skip open check during create                   */
			 /* Most 'creat' (or open with create flag) return  */
                         /* an error if a file already exists. Some older   */
                         /* compilers will not, and will proceed to wipe-out*/
                         /* the file during the 'creat' if it exists. These */
                         /* compilers require c-tree to check to see if the */
                         /* file already exists, before trying the 'creat'. */
                         /* The '#define ctEXCLCREAT' tells c-tree it does  */
                         /* not need to do this check, for the 'creat' will */
                         /* return an error and not wipe-out the file. 	    */
/****************************************************************************/

#define ct_NULL (char *)0 /* c-tree's NULL definition                       */
#ifndef SIZEOF
#define SIZEOF 	sizeof
#endif

/****************************************************************************/
/* C runtime library definitions */
#ifndef ctrt_snprintf
#if _MSC_VER <= 1800 /* VS2013 */
#define ctrt_snprintf	_snprintf
#else
#define ctrt_snprintf	snprintf
#endif
#endif

#define ctrt_fprintf	fprintf
#define ctrt_sprintf	sprintf
#ifndef ctrt_printf
#define ctrt_printf	printf
#endif
#define ctrt_fopen	fopen
#define ctrt_freopen	freopen
#define ctrt_fclose	fclose
#define ctrt_strcpy	strcpy
#define ctrt_strcat	strcat
#define ctrt_strncat	strncat
#define ctrt_strcmp	strcmp
#define ctrt_strncmp	strncmp
#define ctrt_strstr	strstr
#define ctrt_strlen	strlen
#define ctrt_strncpy	strncpy
#define ctrt_fscanf	fscanf
#define ctrt_exit	exit
#define ctrt_memcmp	memcmp
#define ctrt_tmpnam	tmpnam
#define ctrt_memchr	memchr
#define ctrt_qsort	qsort
#define ctrt_bsearch	bsearch

/****************************************************************************/
/* ctrt_getcwd instigates c-tree in Single User Transaction Processing Mode */
/* to use the defined function to fully qualify the PATH of the transaction */
/* logs in case the user does a chdir */
#if (defined(NOTFORCE) && defined(TRANPROC))
#define ctrt_getcwd	ctGetCwd /* For Qualifing TRANPROC LOG Paths */
#endif

/****************************************************************************/
/* The following #define are used to control various memory operations      */
/* in segmented environments. DOS enviroments should have these on.         */
#define BIGDELM           /* high speed end of field delimiter check        */
#ifndef DOSX286
#define ctcfill  ctcbill  /* Required with BIGDELM & BIGCHECK               */
#define BIGCHECK          /* check for fill character                       */
#endif
/****************************************************************************/


/****************************************************************************/
/* High Speed Compare defines */
#ifndef DOSX286
#define FASTCOMP    /* high speed assember key compare. Requires compar?.asm*/
#define FASTRIGHT   /* Use memmove right shifts */
#endif


/****************************************************************************/
/* Function Prototypes & Typedef Declarations defines */
#define ctCONV		  /* Prototype modifier */
#define ctDECL		  /* Prototype modifier */
#define ctDECLT		  /* Prototype modifier */

#ifdef DOSX286
#ifdef __BORLANDC__
#define ctMEM huge		  /* Memory model typedef modifier */
#else
#define ctMEM
#endif
#else
#define ctMEM
#endif
/****************************************************************************/

/****************************************************************************/
/* Various memory managment/compare operations */
#define icpylng(dp,sp,n) *dp++ = *sp++; *dp++ = *sp++; *dp++ = *sp++; *dp++ = *sp++
#define cpylng(dp,sp,n)  cpy4bf(dp,sp)
#define cpy4bf(dp,sp)    memcpy(dp,sp,4)
#define cpybuf(dp,sp,n)  memcpy(dp,sp,(UINT) (n))
#define ctsfill(dp,ch,n) memset(dp,ch,n)
#define ctrt_toupper	toupper

#ifndef ctrt_gets
#define ctrt_gets	gets
#endif

#ifdef ctSP
#define cpybig(d,s,n)	memcpy(d,s,(UINT) (n))
#define bigadr(tp,off)	(((pTEXT) (tp)) + ((UINT)(off)))
#define mblllc(n,s)	mballc(n,(UINT) (s))
#define cpylodl(d,s,n)	cpylod(d,s,(UINT) (n))
#define cpysrcl(d,s,n)	cpysrc(d,s,(UINT) (n))
#else
#define ctHFREE
#endif

#define DllLoadDS      /* Load data segment not used in DOS */

/* system dependent r-tree default output device names */
#define rtLPT0  "LPT0"
#define rtLPT1  "LPT1"
#define rtLPT2  "LPT2"

/****************************************************************************/
/* ntree needs */
#define NETFRMAT
#define cpymbuf		cpybuf
#define cpymsg		cpybuf
#define cpysrcm		cpysrcl

#ifdef ctPortVINES
#define __DOS__
#define ctPROTBYTES
#define ctBAN5
#endif
/****************************************************************************/
/* end of ctcmpl_d.h */
