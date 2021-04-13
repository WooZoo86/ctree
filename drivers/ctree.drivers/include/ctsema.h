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

#ifndef ctSEMAH
#define ctSEMAH

#ifndef ctSEMA
#define ctSEMA

#ifdef ctDBGSEM 
#define SNAMELEN	5
#endif

#ifdef ctFeatW32_MUTXCS
typedef struct mutex {
#ifdef ctDBGsemlst
	NINT			sown;
#endif
	CRITICAL_SECTION	flag;
#ifdef ctChkSysThidMtx
	THID			thid;
#endif
	NINT			ownr;
	NINT			padg;
#ifdef ctDBGSEM 
	TEXT			snam[SNAMELEN];    /* debugging */
#endif
#ifdef ctDBGSEMCNT
	NINT			loc;
#endif
#ifdef ctDBGDLOK
#ifdef ctDBGSEMCNT
	NINT			preloc;
#endif
	UCOUNT			id;
#endif
} SEMACS;
typedef SEMACS ctMEM *	pSEMACS;
#endif /* ctFeatW32_MUTXCS */

#if defined(ctSEMMTX) && defined(ctFeatW32_MUTXCS)

typedef SEMACS SEMA;
typedef pSEMACS pSEMA;

#ifndef MULTITRD
typedef SEMA SEMAblk;
typedef pSEMA pSEMAblk;
#endif

#else  /* ~(ctSEMMTX && ctFeatW32_MUTXCS) */

typedef struct semaphore {
#ifdef ctDBGsemlst
	NINT	sown;
#endif
#ifdef ctPortWIN64
	NLONG	flag;
#else
	LONG	flag;
#endif
#ifdef ctChkSysThidMtx
	THID	thid;
#endif
	NINT	ownr;
	NINT	padg;
#ifdef ctDBGSEM 
	TEXT	snam[SNAMELEN];    /* debugging */
#endif
#ifdef ctDBGSEMCNT
	NINT	loc;
#endif
#ifdef ctDBGDLOK
#ifdef ctDBGSEMCNT
	NINT	preloc;
#endif
	UCOUNT	id;
#endif	
} SEMA;
typedef SEMA ctMEM *	pSEMA;

#ifndef MULTITRD
typedef SEMA SEMAblk, SEMAtim;
typedef pSEMA pSEMAblk, pSEMAtim;
#endif

#endif /* ~(ctSEMMTX && ctFeatW32_MUTXCS) */

#ifdef ctSEMMTX
typedef struct semaphore_tim {
#ifdef ctDBGsemlst
	NINT	sown;
#endif
#ifdef ctPortWIN64
	NLONG	flag;
#else
	LONG	flag;
#endif
#ifdef ctChkSysThidMtx
	THID	thid;
#endif
	NINT	ownr;
	NINT	padg;
#ifdef ctDBGSEM 
	TEXT	snam[SNAMELEN];    /* debugging */
#endif
#ifdef ctDBGSEMCNT
	NINT	loc;
#endif
#ifdef ctDBGDLOK
#ifdef ctDBGSEMCNT
	NINT	preloc;
#endif
	UCOUNT	id;
#endif
} SEMAtim;
typedef SEMAtim ctMEM *	pSEMAtim;
#endif

typedef struct stkstk {
	struct
	stkstk ctMEM
		*sp;	/* link list  */
	LONG	 st;	/* used last  */
	LONG	 sv;	/* long parm  */
	UINT	 sz;	/* stack size */
} STKSTK;
typedef STKSTK ctMEM *	pSTKSTK;
#define STKADJ	 ctSIZE(STKSTK)
#define STKIDL	 10L

#endif /* ~ctSEMA */

#ifdef ctSEMAunxpthd

/* Unix pthread sema definitions. */

#ifdef ctDBGSEM 
#define SNAMELEN	5
#endif

typedef struct semaphore {
#ifdef ctFeatLATCH
	ctlatch_t	mutex;
#else
	pthread_mutex_t mutex;
#endif
	int             flag;
#ifdef ctChkSysThidMtx
	void *		thid;
#endif
	int       	ownr;
	int       	padg;
	sigset_t	smask;
#ifdef ctDBGSEM
        char		snam[SNAMELEN];    /* debugging */
#endif
#ifdef ctDBGSEMCNT
	int		loc;
#endif
} SEMA;
typedef SEMA *  pSEMA;

typedef struct semaphore_tim {
	pthread_mutex_t mutex;
	pthread_cond_t	cond;
	int             flag;
#ifdef ctChkSysThidMtx
	void *		thid;
#endif
	int       	ownr;
	int       	padg;
	sigset_t	smask;
#ifdef ctDBGSEM
        char		snam[SNAMELEN];    /* debugging */
#endif
#ifdef ctDBGSEMCNT
	int		loc;
#endif
} SEMAtim;
typedef SEMAtim *  pSEMAtim;

#endif /* ctSEMAunxpthd */

#endif /* ~ctSEMAH */

/* end of ctsema.h */
