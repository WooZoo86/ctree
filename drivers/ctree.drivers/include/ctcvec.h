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

#ifndef ctCALLVECTORS
#define ctCALLVECTORS

#include "ctcomm.h"

#ifdef PROTOTYPE
extern  pCommFuncPtrs DllExport DllLoadDS ctNpGlobals(pSrvrGbls psg);
extern	NINT  DllLoadDS ctNpInit(pSrvrGbls pGlobals);
extern  NINT  DllLoadDS ctNpStart(pSrvrGbls pGlobals, pTEXT name, pTEXT comm);
extern	NINT  DllLoadDS ctNpStop(pSrvrGbls pGlobals);
extern	NINT  DllLoadDS ctNpOpen(pSrvrGbls pGlobals, pTEXT name, pUCOUNT handle, pUCOUNT action, ULONG size, ULONG protocol, UCOUNT openflag, UCOUNT openmode, UNLONG reserved);
extern	NINT  DllLoadDS ctNpClose(pSrvrGbls pGlobals, UCOUNT handle);
extern	NINT  DllLoadDS ctNpWrite(pSrvrGbls pGlobals, UCOUNT handle, pMTEXT pMsg1, ULONG msg1Len, pMTEXT pMsg2, ULONG msg2Len, pULONG byteswritten);
extern	NINT  DllLoadDS ctNpRead(pSrvrGbls pGlobals, UCOUNT handle, pMTEXT pMsg1, ULONG msg1Len, pMTEXT pMsg2, ULONG msg2Len, pULONG bytesread);
extern	NINT  DllLoadDS ctNpMakeNmPipe(pSrvrGbls pGlobals, pTEXT name, pULONG handle, UCOUNT omode, UCOUNT pmode, ULONG size1, ULONG protocol, LONG timeout, pTEXT ss);
extern	NINT  DllLoadDS ctNpDisconnectNmPipe(pSrvrGbls pGlobals, UCOUNT handle, NINT mode);
extern	NINT  DllLoadDS ctNpConnectNmPipe(pSrvrGbls pGlobals, UCOUNT handle);
extern	VRLEN DllLoadDS ctNpPackSiz(pSrvrGbls pGlobals, VRLEN size, pVRLEN ps_size);
extern	NINT  DllLoadDS ctNpSetAttribute(pSrvrGbls pGlobals, UCOUNT handle, NINT attribute, pVOID pValue);
extern	NINT  DllLoadDS ctNpGetAttribute(pSrvrGbls pGlobals, UCOUNT handle, NINT attribute, pVOID pValue);
extern	NINT  DllLoadDS ctNpPolice(pSrvrGbls pGlobals);

extern  NINT	NPdefer(pSrvrGbls pGlobals, LONG sleep);
extern  NINT    NPcttcre(pSrvrGbls pGlobals,pNINT pusrhnd, NINT (*taskptr)(VOID),UINT stksiz, NLONG parm);

extern	NINT	NPwaitWhile(pSrvrGbls pGlobals, pCOUNT F, LONG delay);

extern	NINT	NPctsemrqs(pSrvrGbls pGlobals, pSEMA sema, LONG wait, NINT own);
extern	NINT	NPctsemclr(pSrvrGbls pGlobals, pSEMA sema, NINT own);
extern	NINT	NPctsemwat(pSrvrGbls pGlobals, pSEMA sema, LONG wait, NINT own);

extern	NINT	NPctblkrqs(pSrvrGbls pGlobals, pSEMAblk sema, LONG wait, NINT own);
extern	NINT	NPctblkclr(pSrvrGbls pGlobals, pSEMAblk sema, NINT own);
extern	NINT	NPctblkwat(pSrvrGbls pGlobals, pSEMAblk sema, LONG wait, NINT own);

extern	NINT	NPcttimrqs(pSrvrGbls pGlobals, pSEMAtim sema, LONG wait, NINT own);
extern	NINT	NPcttimclr(pSrvrGbls pGlobals, pSEMAtim sema, NINT own);
extern	NINT	NPcttimwat(pSrvrGbls pGlobals, pSEMAtim sema, LONG wait, NINT own);

extern  pVOID	NPalloc(pSrvrGbls pGlobals, NINT n, UINT s);
extern	VOID	NPfree(pSrvrGbls pGlobals, pVOID p);
extern  VOID 	NPrevobj(pSrvrGbls pGlobals, pVOID pData, NINT size);
extern  NINT	NPusrstat(pSrvrGbls pGlobals, NINT own);
extern  NLONG 	NPGetSrVariable(pSrvrGbls pGlobals, NINT this_var);
extern  LONG 	NPctrt_printf(pSrvrGbls pGlobals, pTEXT p);
extern  NINT    NPgetactivestatus(pSrvrGbls pGlobals, NINT own);
extern  NINT    NPsetinactive(pSrvrGbls pGlobals, NINT own, NINT chkstt);
extern  NINT	NPUserAlive(pSrvrGbls pGlobals, NINT own);
#else
extern 	pCommFuncPtrs DllExport DllLoadDS ctNpGlobals();
extern	NINT  DllLoadDS ctNpInit();
extern 	NINT  DllLoadDS ctNpStart();
extern	NINT  DllLoadDS ctNpStop();
extern	NINT  DllLoadDS ctNpOpen();
extern	NINT  DllLoadDS ctNpClose();
extern	NINT  DllLoadDS ctNpWrite();
extern	NINT  DllLoadDS ctNpRead();
extern	NINT  DllLoadDS ctNpMakeNmPipe();
extern	NINT  DllLoadDS ctNpDisconnectNmPipe();
extern	NINT  DllLoadDS ctNpConnectNmPipe();
extern	VRLEN DllLoadDS ctNpPackSiz();
extern	NINT  DllLoadDS ctNpSetAttribute();
extern	NINT  DllLoadDS ctNpGetAttribute();
extern	NINT  DllLoadDS ctNpPolice();

extern  NINT	NPdefer();
extern  NINT    NPcttcre();

extern	NINT	NPwaitWhile();

extern	NINT	NPctsemrqs();
extern	NINT	NPctsemclr();
extern	NINT	NPctsemwat();

extern	NINT	NPctblkrqs();
extern	NINT	NPctblkclr();
extern	NINT	NPctblkwat();

extern	NINT	NPcttimrqs();
extern	NINT	NPcttimclr();
extern	NINT	NPcttimwat();

extern  pVOID	NPalloc();
extern	VOID	NPfree();
extern  VOID	NPrevobj();
extern  NINT	NPusrstat();
extern  LONG 	NPGetSrVariable();
extern  LONG 	NPctrt_printf();
extern  NINT	NPUserAlive();
#endif

#endif /* ~ctCALLVECTORS */
/* end ctcvec.h */

