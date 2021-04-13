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

/* Windows W32 Threading setup */



#ifdef __cplusplus
extern "C" {
#endif

extern DllExtImp long tlsIndex;

#ifdef __cplusplus
}
#endif


#define ctSRVcleandown /* Special shutdown flag set for NT */

/*************************************/
#if (defined(ctSRVR) || defined(ctBNDSRVR))
#ifdef ctPortFAIRCOM_THREADS
#define ctNoThdParms
#endif
#else
#define ctThrdNoStackParm
#endif
/*************************************/

/*^***********************************/
#ifndef ctPortFAIRCOM_THREADS
#ifndef ctPortNATIVE_THREADS

#define OWNER   (1)

#endif 	/* ~ctPortNATIVE_THREADS */
#endif	/* ~ctPortFAIRCOM_THREADS */
/*~***********************************/


/*^***********************************/
#ifdef ctPortFAIRCOM_THREADS
#include <setjmp.h>
#define THRD_BUF	jmp_buf
#define ct_epc		environs[5]
#define ct_esp		environs[4]
#define ctsysnap	Sleep
#define OWNER   	((NINT)((Threads_ *)getThreadCtl())->current->refcon)
#define ctNEED_TID
#endif /* ctPortFAIRCOM_THREADS */
/*~***********************************/


/*^***********************************/
#ifdef ctPortNATIVE_THREADS

#ifdef MULTITRD
#ifdef ctPortAFTI_BNDSRVR
#define	OWNER	my_GetOWNER()
int	my_GetOWNER(void);
#else
#ifdef ctPortWINKE
extern int ctOWNER(VOID);
#define OWNER   ctOWNER()
#else
#define OWNER   (PtrToLong(TlsGetValue(tlsIndex)))
#endif
#endif
#endif

#ifdef ctThrds

#define CTBLOCK
typedef struct ctblck {
#ifdef ctFeatW32_MUTXCS
	CRITICAL_SECTION flag;
#else
	__int64	flag;
#endif
	__int64	ehan;
	int	stat;
	int	init;
} ctBLOCK;

#ifdef ctPortWINKE
extern  PRKMUTEX		ctThrdCrit;
#define ctThrdCriticalIn	KeWaitForSingleObject(ctThrdCrit, Executive, KernelMode, FALSE, NULL);
#define ctThrdCriticalOut	KeReleaseMutex(ctThrdCrit, FALSE);
#else
extern  CRITICAL_SECTION	ctThrdCrit;
#define ctThrdCriticalIn	EnterCriticalSection(&ctThrdCrit);
#define ctThrdCriticalOut	LeaveCriticalSection(&ctThrdCrit);
#endif

#endif /* ctThrds */

#endif /* ctPortNATIVE_THREADS */
/*~***********************************/

/* end of ctsthd.h */
