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

/************************************************************************
*
*	@module NTREEIPC.H |
*   This is the internal header file for NTREE IPC portable function
*	calls.
*
***********************************************************************/

#ifndef	_NTIPCLIB_INCLUDED
#define _NTIPCLIB_INCLUDED

#include "ntreestd.h"

#ifdef ntSHM

/***********************************************************************
*
*	Microsoft WINDOWS dependent code
*
***********************************************************************/
#ifdef ntWIN

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define INVALID_SEMAPHORE	NULL
#define INVALID_SHAREDMEM	NULL
#define INVALID_NAMEDPIPE	NULL

typedef HANDLE				SEMAPHORE;
typedef HANDLE				SHAREDMEM;
typedef HANDLE				NAMEDPIPE;

#define SEM_SECURITY		NULL
#define SEM_MAX_COUNT		1
#define SEM_ACCESS			(SEMAPHORE_ALL_ACCESS | SYNCHRONIZE)
#define SEM_INHERIT			NO

#define SHMEM_MAP_FLAGS		FILE_MAP_WRITE
#define SHMEM_HANDLE		((HANDLE)0xFFFFFFFF)
#define SHMEM_SECURITY		NULL
#define SHMEM_PROTECT		PAGE_READWRITE

#endif /* ntWIN */

/***********************************************************************
*
*	IBM OS/2 dependent code
*
***********************************************************************/

#ifdef ntOS2

#define INCL_DOSSEMAPHORES
#define INCL_DOSMEMMGR
#define INCL_ERRORS
#include <os2.h>
#include <os2\bsedos.h>
#include <bseerr.h>
#include <stdio.h>
#include <string.h>

#define INVALID_SEMAPHORE	NULL
#define INVALID_SHAREDMEM	NULL
#define INVALID_NAMEDPIPE          NULL

typedef HMTX				SEMAPHORE;
typedef pVOID				SHAREDMEM;
typedef HFILE                             NAMEDPIPE;

#endif /* ntOS2 */

/***********************************************************************
*
*	Unix dependent code
*
***********************************************************************/

#ifdef ntUNIX

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define ntIpcLastError()		errno
#define IpcChkBlking(c,m,l)	(c->ChkBlking ? (*c->ChkBlking)(c,m,l) : YES)

#define NTIPC_ACCESS		0777

#define INVALID_SEMAPHORE	(-1)
#define INVALID_SHAREDMEM	(-1)
#define INVALID_NAMEDPIPE	(-1)

typedef int					SEMAPHORE;
typedef int					SHAREDMEM;
typedef int					NAMEDPIPE;
typedef SEMAPHORE*			pSEMAPHORE;
typedef SHAREDMEM*			pSHAREDMEM;
typedef NAMEDPIPE*			pNAMEDPIPE;

#endif /* ntUNIX */

/***********************************************************************
*
*	System independent IPC code
*
***********************************************************************/

#define NTIPC_NAME				64
#define NTIPC_MAX_CONN			1024
#define NTIPC_RETRY				10

#define NTIPC_IDLE				0
#define NTIPC_LISTEN			1
#define NTIPC_READY				2
#define NTIPC_CLOSED			3
#define NTIPC_RTS				4
#define NTIPC_CTS				5
#define NTIPC_CONNECT			6

#define SHMEM_HEAD_SIZE			sizeof(SHMHEAD)
#define SHMEM_DATA_SIZE			(1024 * 64)
#define SHMEM_MAX_SIZE			(SHMEM_HEAD_SIZE + SHMEM_DATA_SIZE)

typedef struct
{
	UTEXT	Control[ NTIPC_MAX_CONN ];
	LONG	DataLength;			/* Number of bytes in data		*/
	LONG	Remaining;			/* Number of bytes remaining	*/
} SHMHEAD;

typedef SHMHEAD ntFAR*	pSHMHEAD;
#define SHMHEAD_SIZE	sizeof( SHMHEAD )

struct NTREEIPC
{
	pCONNECTION Connection;		/* Connection Pointer 					*/
	LONG		ConnectionId;	/* Connection Id number					*/
	SEMAPHORE	Semaphore;		/* Read Semaphore handle				*/
	SHAREDMEM	Object;			/* Shared memory object	handle			*/
#ifdef ntUNIX
	NAMEDPIPE	ServerPipe;		/* Server reads, client writes			*/
	NAMEDPIPE	ClientPipe;		/* Server writes, client reads			*/
#else
	NAMEDPIPE	Pipe;			/* Duplex pipe							*/
#endif
	pUTEXT		Pointer;		/* Shared memory base address			*/
	pSHMHEAD	Head;			/* Shared memory header pointer			*/
	pUTEXT		Data;			/* Shared memory data pointer			*/
	pTEXT		ServerName;		/* ServerName							*/
	NINT		Mode;			/* Mode-> NTREE_BLOCK or NTREE_NONBLOCK */
	NINT		Type;			/* Type-> NTREE_SERVER or NTREE_CLIENT	*/
#ifdef ntUNIX
	TEXT		CName[ NTIPC_NAME ];
	TEXT		SName[ NTIPC_NAME ];
#endif
};

typedef struct NTREEIPC*	pNTREEIPC;

#define NTREEIPC_SIZE		sizeof( struct NTREEIPC )

#ifdef	PROTOTYPE

pNTREEIPC ntIpcAlloc( pTEXT ServerName, NINT Type, NINT Mode );
NINT ntIpcFree( pNTREEIPC Handle );
NINT ntIpcCreate( pNTREEIPC Handle );
NINT ntIpcOpenServer( pNTREEIPC Handle );
NINT ntIpcOpenClient( pNTREEIPC Handle );
NINT ntIpcClose( pNTREEIPC Handle );
NINT ntIpcWriteVector( pNTREEIPC Handle, pVECTOR Vector, NINT VectorCount, pLONG BytesWriten );
NINT ntIpcReadVector( pNTREEIPC Handle, pVECTOR Vector, NINT VectorCount, pLONG BytesRead );

#else	/* PROTOTYPE */

void ntIpcDeinitialize();
pNTREEIPC ntIpcAlloc();
NINT ntIpcFree();
NINT ntIpcCreate();
NINT ntIpcOpenServer();
NINT ntIpcOpenClient();
NINT ntIpcClose();
NINT ntIpcWriteVector();
NINT ntIpcReadVector();

#endif	/* PROTOTYPE */

#endif	/* ntSHM */

#endif	/* _NTIPCLIB_INCLUDED */

