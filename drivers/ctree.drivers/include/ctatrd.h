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

#ifndef ctATRDH
#define ctATRDH

#define ctMINBNDTHREADS	  25 /* Min number of connections for BOUND thread model */
#define ctDFLTBNDTHREADS 128 /* Default number of connections for BOUND thread model */

#ifndef CTMUTEX
typedef struct ctmutex {
#ifdef ctFeatW32_MUTXCS
	CRITICAL_SECTION flag;
#else
#ifdef ctPortWIN64
	NLONG	flag;
#else
	LONG	flag;
#endif
#endif
	NINT	init;
} ctMUTEX;
#endif
typedef ctMUTEX ctMEM *	pctMUTEX;


#ifndef CTBLOCK
typedef struct ctblck {
#ifdef ctPortWIN64
	NLONG	flag;
#else
	LONG	flag;
#endif
	NINT	init;
#ifdef ctDBGRWLCNT
	NINT	locl;
#endif
} ctBLOCK;
#endif
typedef ctBLOCK ctMEM *	pctBLOCK;


#ifdef ctFeatThrdSemap_Native
#ifdef ctPortUNIX
#ifdef ctPortMACOSX
#include <dispatch/dispatch.h>
#else
#include <semaphore.h>
#endif
#endif
#endif

typedef struct ctsemap {
#ifdef ctFeatThrdSemap_Native
#ifdef ctPortWIN32
	HANDLE	shnd;
#else
#ifdef ctPortMACOSX
	dispatch_semaphore_t	shnd;
#else
	sem_t	shnd;
#endif
#endif
#else
	NINT	sqid;
	NINT	scnt;
#ifdef ctDBG_RWLOCK
	NINT	ownr;
	NINT	padg;
#endif
#endif
} ctSEMAP;
typedef ctSEMAP ctMEM * pctSEMAP;


#ifndef ctAppSTACKSIZE
#define ctAppSTACKSIZE	16384
#endif

#ifdef CTTHRDH
#define ctThrdCriticalIn	holdThreading();
#define ctThrdCriticalOut	freeThreading();
#endif

#ifdef ctPortMAC
#ifdef ctPortNATIVE_THREADS
#define ctThrdCriticalIn	ThreadBeginCritical();
#define ctThrdCriticalOut	ThreadEndCritical();
#endif
#endif

#ifdef ctPortNLM
#ifdef ctPortNATIVE_THREADS
#define ctThrdCriticalIn	printf("\nWARNING: ctThrdCriticalIn  not defined for NLM!\n");
#define ctThrdCriticalOut	printf("\nWARNING: ctThrdCriticalOut not defined for NLM!\n");
#endif
#endif


#ifdef PROTOTYPE
extern NINT mbThrdInit(NINT ,LONG );
extern NINT mbThrdTerm(VOID );
extern NINT mbThrdCreate(pctFUNC ,pVOID ,LONG );
extern VOID mbThrdExit(VOID );
extern NINT mbThrdSleep(LONG );
extern NINT mbThrdMutexGet(pctMUTEX );
extern NINT mbThrdMutexTry(pctMUTEX );
extern NINT mbThrdMutexRel(pctMUTEX );
extern NINT mbThrdMutexCls(pctMUTEX );
extern NINT mbThrdBlockGet(pctBLOCK ,LONG );
extern NINT mbThrdBlockWait(pctBLOCK ,LONG );
extern NINT mbThrdBlockRel(pctBLOCK );
extern NINT mbThrdBlockCls(pctBLOCK );
extern NINT mbThrdSemapInit(pctSEMAP ,NINT );
extern NINT mbThrdSemapGet(pctSEMAP );
extern NINT mbThrdSemapTry(pctSEMAP );
extern NINT mbThrdSemapRel(pctSEMAP );
extern NINT mbThrdSemapCls(pctSEMAP );
#else
extern NINT mbThrdInit();
extern NINT mbThrdTerm();
extern NINT mbThrdCreate();
extern VOID mbThrdExit();
extern NINT mbThrdSleep();
extern NINT mbThrdMutexGet();
extern NINT mbThrdMutexTry();
extern NINT mbThrdMutexRel();
extern NINT mbThrdMutexCls();
extern NINT mbThrdBlockGet();
extern NINT mbThrdBlockWait();
extern NINT mbThrdBlockRel();
extern NINT mbThrdBlockCls();
extern NINT mbThrdSemapInit();
extern NINT mbThrdSemapGet();
extern NINT mbThrdSemapTry();
extern NINT mbThrdSemapRel();
extern NINT mbThrdSemapCls();
#endif

typedef struct thrdstub {
	pctFUNC	actfnc;
	pVOID	arglst;
	pVOID	usrvar;
	ctBLOCK	stbblk;
	NINT	errcod;
	NINT	refcon;
	} ThrdStub;
typedef ThrdStub * pThrdStub;
#ifdef ctFeatSHAREDCRIT
#define CRIT_UNRESERVED 0x00000000UL
#define CRIT_AVAILABLE  0x00000001UL
#define CRIT_INUSE      0x00000002UL
#define CRIT_WRTPND     0x00000003UL /* write pending */

typedef AULONG RESERVATION, *pRESERVATION;
typedef struct reservationlist{
        RESERVATION * entry;
        struct reservationlist * next;
} RESERVATIONLIST;

typedef struct scrit {
        ctBLOCK block;
        RESERVATIONLIST tickets;
} ctSCRIT, * pctSCRIT;
#ifdef PROTOTYPE
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalInit(pctSCRIT);
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalTerm(pctSCRIT);
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalEnter(pctSCRIT,volatile RESERVATION *);
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalExit(pctSCRIT,volatile RESERVATION *);
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalCancelReservation(pctSCRIT, volatile RESERVATION *);
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalEnterExcl(pctSCRIT);
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalExitExcl(pctSCRIT);
#else
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalInit();
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalTerm();
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalEnter();
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalExit();
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalCancelReservation();
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalEnterExcl();
extern ctCONV  NINT  ctDECL ctThrdSharedCriticalExitExcl();

#endif
#endif 


#endif /* ctATRDH */

/* end of ctatrd.h */
