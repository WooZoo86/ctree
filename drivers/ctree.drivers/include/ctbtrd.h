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

#ifdef ctThrds

#ifdef ctCTBTRD_C
#undef EXTERN
#define EXTERN rbEXTERN_COMMENT
#endif

#ifdef makeOWNERsupport
#undef makeOWNERsupport
#endif
#ifdef makeOWNERpthread
#undef makeOWNERpthread
#endif

#ifdef ctBNDentryPointMutex
extern SEMAmut	cttrdmtx[MXU2];
extern ULONG	ctsessid[MXU2];
EXTERN NINT	ctkltrd;
#endif /* ctBNDentryPointMutex */

#ifndef ctThrdNonNative

#ifdef ctPortWIN32
extern	DllExtImp long tlsIndex;
#ifdef ctBNDentryPointMutex
extern	long   tlsIndexSess;
#endif
#ifdef ctPortWINKE
#define makeOWNER(id)	ctSetOWNER(id)
#else
#define makeOWNER(id)	TlsSetValue(tlsIndex, (LPVOID)(NLONG)(id))
#define makeSESSN(id)	TlsSetValue(tlsIndexSess, (LPVOID)(NLONG)(id))
#define SESSN		(ULONG)(NLONG)TlsGetValue(tlsIndexSess)
#endif
#define makeOWNERsupport
#endif

#ifdef ctPortNLM
				
#define makeOWNER(id)	SaveThreadDataAreaPtr((pVOID)id)	
#define makeOWNERsupport
#endif

#ifdef ctPortOS2
/* makeOWNER(id)	no action */
#define makeOWNERsupport
#endif

#ifdef ctPortHP9000
#define makeOWNERpthread
#endif
#ifdef ctPortLINUX
#define makeOWNERpthread
#endif
#ifdef ctPortSCO5
#define makeOWNERpthread
#endif
#ifdef ctPortALPHA
#define makeOWNERpthread
#endif
#ifdef ctPortRS6000
#define makeOWNERpthread
#endif
#ifdef ctPortSGI
#define makeOWNERpthread
#endif
#ifdef ctPortSOL386
#define makeOWNERpthread
#endif
#ifdef ctPortSOLARIS
#define makeOWNERpthread
#endif
#ifdef ctPortMACOSX
#define makeOWNERpthread
#endif
#ifdef ctPortQNXRTP
#define makeOWNERpthread
#endif
#ifdef ctPortFREEBSD7
#define makeOWNERpthread
#endif

#ifdef makeOWNERpthread

#ifdef ctFeatTHRDLOCALOWNER
extern  __thread int	ctownr;
#define makeOWNER(id)	ctownr = id
#else
extern	pthread_key_t   ctOwnerKey;
#define makeOWNER(id)	pthread_setspecific(ctOwnerKey, (void *)(NLONG)(id))
#endif

#ifdef ctBNDentryPointMutex
#ifdef ctFeatTHRDLOCALSESSN
extern  __thread int	ctsessn;
#define SESSN		ctsessn
#define makeSESSN(id)	ctsessn = id
#else
extern	pthread_key_t   ctSessnKey;
#define SESSN		(ULONG)pthread_getspecific(ctSessnKey)
#define makeSESSN(id)	pthread_setspecific(ctSessnKey, (void *)(NLONG)(id))
#endif
#endif

#define makeOWNERsupport

#endif /* makeOWNERpthread */

#else  /* ctThrdNonNative */
#define makeOWNERsupport
#endif /* ctThrdNonNative */

#endif /* ctThrds */

/* end of ctbtrd.h */
