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

#ifndef ctNAMEPIPE
#define ctNAMEPIPE

#ifdef CTBOUND
#include "ctbond.h"
#endif
#include "ctcvec.h"

#ifdef ctDLLOAD
#define BUILDASDLL
#endif

#define NERR_SUCCESS		0x00
#define NERR_BROKEN_PIPE	0x01
#define NERR_INVALID_PARAMETER	0x02
#define NERR_BUFFER_TO_SMALL	0x03
#define NERR_TIME_OUT		0x04
#define NERR_INTERRUPT		0x05
#define NERR_INVALID_HANDLE	0x06
#define NERR_INVALID_NAME	0x07
#define NERR_PATH_NOT_FOUND	0x08
#define NERR_NOT_ENOUGH_MEM	0x09
#define NERR_ADVERTISING	0x0A
#define NERR_RECEIVE		0x0B
#define NERR_SEND		0x0C
#define NERR_ENDPOINT		0x0D

/*
** Error codes returned by c-tree Server shared memory connection function
** on Unix systems:
*/
#define SHMEM_ERR_INVALID_HANDLE 	-1
#define SHMEM_ERR_NOT_ENOUGH_MEM	-2
#define SHMEM_ERR_CANT_CREATE_PIPE	-3
#define SHMEM_ERR_CANT_OPEN_PIPE	-4
#define SHMEM_ERR_LOGON_WAIT_FAILED	-5
#define SHMEM_ERR_CANT_READ_PIPE	-6
#define SHMEM_ERR_CONNECT_CANCELED	-7
#define SHMEM_ERR_SHMEM_GET_FAILED	-8
#define SHMEM_ERR_SEMA_GET_FAILED	-9
#define SHMEM_ERR_INCOMPATIBLE_VERSION	-10
#define SHMEM_ERR_SHMEM_ATTACH_FAILED	-11
#define SHMEM_ERR_CANT_WRITE_PIPE	-12
#define SHMEM_ERR_SEM_LGON_INVALID	-13

/*
** Error code returned by c-tree Server shared memory disconnect function
** on Unix systems:
*/
#define SHMEM_ERR_CLIENT_ATTACHED	-1

/* SERVER should be defined to the name of the registered server. It
 * is used by AppleTalk Name Binding Protocol to get the proper 
 * session listening socket for the server.
 */
#define CTRE		0x43434343L

#ifdef LOW_HIGH
#define ctHIWORD(l) ((COUNT)((((LONG)(l)) >> 16) & 0xFFFF))
#define ctLOWORD(l) ((COUNT)(LONG)(l))
#else
#define ctLOWORD(l) ((COUNT)((((LONG)(l)) >> 16) & 0xFFFF))
#define ctHIWORD(l) ((COUNT)(LONG)(l))
#endif

/*
 * prototypes
 */

#ifdef PROTOTYPE
extern pSessblk 	at_SessionValidate(pSrvrGbls pGlobals, UCOUNT handle);
extern UINT 		at_SessionNew(pSrvrGbls pGlobals, UCOUNT cmdSize, pTEXT pServerName, ULONG attributes, UCOUNT theSrvId, UCOUNT recTimeOut, UCOUNT sndTimeOut);
extern VOID 		at_SessionDispose(pSrvrGbls pGlobals, pSessblk pSession);
extern NINT 		at_SessionOpen(pSrvrGbls pGlobals, pSessblk pSession);
extern NINT 		at_SessionSSLOpen(pSrvrGbls pGlobals, pSessblk pSession);
extern VOID 		at_SessionClose(pSrvrGbls pGlobals, pSessblk pSession);
extern NINT		at_SessionSend(pSrvrGbls pGlobals, pSessblk pSession, pMTEXT pMsg1, ULONG msg1Len, pMTEXT pMsg2, ULONG msg2Len, pULONG pBytesSent);
extern NINT		at_SessionReceive(pSrvrGbls pGlobals, pSessblk pSession, pMTEXT pMsg1, ULONG msg1Len, pMTEXT pMsg2, ULONG msg2Len, pULONG pBytesRead);
extern NINT             at_SessionReallocCommBuffer(pSrvrGbls pGlobals, pSessblk pSession, ULONG newbufsiz);
extern NINT 		at_SessionMake(pSrvrGbls pGlobals, pSessblk pSession);
extern NINT 		at_SessionConnect(pSrvrGbls pGlobals, pSessblk pSession);
extern NINT 		at_SessionDisconnect(pSrvrGbls pGlobals, pSessblk pSession);
extern VOID 		at_CommunicationInit(pSrvrGbls pGlobals);
extern NINT 		at_CommunicationStart(pSrvrGbls pGlobals, pTEXT name);
extern NINT 		at_SessionSetAttribute(pSrvrGbls pGlobals, pSessblk pSession, NINT attribute, pVOID pValue);
extern VOID 		at_CommunicationStop(pSrvrGbls pGlobals);
extern NINT 		at_CommunicationPolice(pSrvrGbls pGlobals);

#else

extern pSessblk 	at_SessionValidate();
extern UINT 		at_SessionNew();
extern VOID 		at_SessionDispose();
extern NINT 		at_SessionOpen();
extern NINT 		at_SessionSSLOpen();
extern VOID 		at_SessionClose();
extern NINT		at_SessionSend();
extern NINT		at_SessionReceive();
extern NINT             at_SessionReallocCommBuffer();
extern NINT 		at_SessionMake();
extern NINT 		at_SessionConnect();
extern NINT 		at_SessionDisconnect();
extern VOID 		at_CommunicationInit();
extern NINT 		at_CommunicationStart();
extern VOID 		at_CommunicationStop();
extern NINT 		at_SessionSetAttribute();
extern NINT 		at_CommunicationPolice();

#endif /* ~PROTOTYPE */
#endif /* ~ctNAMEPIPE */

/* end ctnpip.h */
