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
*	@module NTREELIB.H |
*   This is the internal base header file for the NTREE source code. 
*	It automatically includes NTREELIB.H and is used by all modules
*	in the library. Uses should not include this module since it is
*   used internally by NTREE.
*
***********************************************************************/

#ifndef _NTREESTD_INCLUDED
#define _NTREESTD_INCLUDED
#ifdef 		_WIN32_WCE					
#include 	"ctcrtlce.h"			/* Used for Windows CE Port */
#endif
#include "ntreelib.h"

#ifdef _MAC
#ifndef ntMAC
#define ntMAC
#endif
#endif

#ifdef  ctPortMAC_MSCX_MTCLIENT
#ifndef ntMAC
#define ntMAC
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	ntTCP
#define ntTCPSTART		ntTcpStartUp
#else
#define ntTCPSTART		NULL
#endif

#ifdef	ntSPX
#define ntSPXSTART		ntSpxStartUp
#else
#define ntSPXSTART		NULL
#endif

#ifdef	ntNET
#define ntNETSTART		ntNetStartUp
#else
#define ntNETSTART		NULL
#endif

#ifdef	ntSHM
#define ntSHMSTART		ntShmStartUp
#else
#define ntSHMSTART		NULL
#endif

#ifdef	ntAPT
#define ntMACSTART		ntAptStartUp
#else
#define ntMACSTART		NULL
#endif

#define ntMin(a,b)	(((a) < (b)) ? (a) : (b))
#define ntMax(a,b)	(((a) > (b)) ? (a) : (b))

#define ntDEFER_VALUE					1

#define ntDELIMITER                     '@'
#define ntMAXNAME                       256
#define ntCOMPRESS_MIN_SIZE				128

/***********************************************************************
*
*	NTREE_FRAME_TYPES
*
***********************************************************************/
enum NTREE_FRAME_TYPES
{
	NTREE_FRAME_DATA = 1,
	NTREE_FRAME_ACK,	
	NTREE_FRAME_NAK,

	NTREE_FRAME_LAST
};


/***********************************************************************
*
* Struct NTSESSUSRDATA
*
***********************************************************************/
struct NTSESUSRDATA
{
NINT	QID;
};
#define NTSESUSRDATA_SIZE	sizeof( struct NTSESUSRDATA )


/***********************************************************************
*
* Struct SESSION
*
***********************************************************************/

struct SESSION
{
	pCONNECTION 	Head;			/* First connection struc ptr */
	NINT		TcpStartCount;		/* TCP/IP startup count. */
	NINT		ShmStartCount;		/* Shared memory id. */
	UNLONG		Socket;			/* TCP/IP Server listening Socket */
	COUNT		ioRefNum;		/* TCP/IP Server listening MAC ioRefNum */
	NINT		CurConnectionCnt;	/* Current Connection (User) Count */
	YESNO		IsListening;		/* Indicate if Socket is listening */
	int		ShmId;			/* Shared memory handle */
	int		SemId;			/* Shared memory semaphore */
	TEXT		IsNetStarted[256];	/* Indicates if Netbios was already started */
	NINT		SpxStartCount;		/* Counts how many connections was started */
	ULONG		SpxTaskId;		/* SPX TaskId */
#ifdef PROTOTYPE				/* Link to Protocols array */
	NINT (ntDECL* Start[ NTREE_LAST_PROTOCOL ])( pCONNECTION );
#else
	NINT (ntDECL* Start[ NTREE_LAST_PROTOCOL ])();
#endif
	pVOID   slSem;	 /* Session Select Protect Semaphore */
	pVOID   ssSem;	 /* Session Semaphore 	  */
	NINT	ssSet;	 /* Session Semaphore Flag */
	pNTSESUSRDATA UserData;	 /* User Data -OK to Use */
	pVOID	UsrPtr;		
};

#define SESSION_SIZE	sizeof( struct SESSION )


/***********************************************************************
*
* Struct NTSTATISTICS
*
***********************************************************************/
struct NTSTATISTICS
{
clock_t	ntOpenTime;		/* clock when socket was opened */
clock_t ntCloseTime;		/* clock when socket was closed */
clock_t ntCloseQTime;		/* clock when Q was closed */
clock_t	ntFirstWriteTime;	/* clock first write		*/
clock_t ntFirstReadTime;	/* clock first read		*/
ULONG	TotalBytesToSend; 	/* from ntWrite */
ULONG	TotalBytesSent;		/* from ntWrite */
ULONG	TotalBytesReceived;	/* from ntRead  */
ULONG	TotalBytesQSent;	/* from ntQueRead */
ULONG	TotalBytesQReceived;	/* from ntQueRead */
NINT    Stream;			/* Steam Mode indicator */
NINT    Cache;			/* Cached Mode indicator */
};
#define NTSTATISTICS_SIZE	sizeof( struct NTSTATISTICS )


/***********************************************************************
*
* Struct NTUSRDATA
*
***********************************************************************/
#define NTU_BUF_SIZE		1048576
struct NTUSRDATA
{
LONG	NoBytesReadYetNotProcessed;
LONG	NoBytesProcessed;
pTEXT	CurBufPtr;
TEXT	ReadBuffer[NTU_BUF_SIZE];
};
#define NTUSRDATA_SIZE	sizeof( struct NTUSRDATA )


/***********************************************************************
*
* Struct CONNECTION
*
***********************************************************************/

struct CONNECTION
{
	pTEXT   ServerName;
	pTEXT   HostName;
	pVOID   Handle;
	NINT	Protocol;               
	NINT	Type;
	NINT	Mode;
	YESNO   IsOpen;
	YESNO	InProgress;
	YESNO	CancelCall;
	pVOID   ctSem;		/* Connection Semaphore */
	NINT	ctSet;		/* Connection Semaphore Flag */
	ULONG	ntprqstime; 	/* Last Communication request time for timeout */		
	NINT	ntOWNR;		/* Thread id */
	NINT	UsrNum;		/* User Number */
	NINT    Stream;		/* Steam Mode indicator */
	NINT    Cache;		/* Cached Mode indicator */
	pNTSTATISTICS 	Stats; 	/* Connection statistics */
	pNTUSRDATA	UserData;	/* Connection User Purpose */
#ifdef ntMAC
	unsigned long 	fd;
#else
	UNLONG		fd;
#endif

	pCONNECTION 	Next;
	pSESSION 	Session;

#ifdef PROTOTYPE
	NINT (ntDECL* Defer)( pCONNECTION, LONG Wait, NINT Location );
	NINT (ntDECL* ChkBlking)( pCONNECTION, NINT Mode, NINT Location );
	NINT (ntDECL* Open)( pCONNECTION );
	NINT (ntDECL* Close)( pCONNECTION );
	NINT (ntDECL* Shutdown)( pCONNECTION );
	NINT (ntDECL* CleanUp)( pCONNECTION );
	NINT (ntDECL* Send)( pCONNECTION, pVOID, LONG, pLONG );
	NINT (ntDECL* SendVector)( pCONNECTION, pVECTOR, NINT, pLONG );
	NINT (ntDECL* Receive)( pCONNECTION, pVOID, LONG, pLONG );
	NINT (ntDECL* RecvVector)( pCONNECTION, pVECTOR, NINT, pLONG );
	NINT (ntDECL* SetOption)( pCONNECTION, NINT, LONG );
	NINT (ntDECL* GetOption)( pCONNECTION, NINT, pLONG );
#else
	NINT (ntDECL* Defer)();
	NINT (ntDECL* ChkBlking)();
	NINT (ntDECL* Open)();
	NINT (ntDECL* Close)();
	NINT (ntDECL* Shutdown)();
	NINT (ntDECL* CleanUp)();
	NINT (ntDECL* Send)();
	NINT (ntDECL* SendVector)();
	NINT (ntDECL* Receive)();
	NINT (ntDECL* RecvVector)();
	NINT (ntDECL* SetOption)();
	NINT (ntDECL* GetOption)();
#endif
};

#define CONNECTION_SIZE		sizeof( struct CONNECTION )

/***********************************************************************
*
*	External memory allocation links.
*
***********************************************************************/

/***********************************************************************
*
*	Function prototypes
*
***********************************************************************/

#define NtpDefer(c,w,l)			((c->Defer) ? (*c->Defer)(c,w,l) : NTREE_DEFER_CONTINUE )
#define NtpHandleDefer(h,w,l)   ((h->Connection->Defer) ? (*h->Connection->Defer)(h->Connection, w, l) : NTREE_DEFER_CONTINUE )
#define ntSetCancel(c,v)		c->CancelCall = (v)
#define ntHandleSetCancel(h,v)	h->Connection->CancelCall = (v)
#define ntGetCancel(c)			((c->CancelCall) ? YES : NO)
#define ntHandleGetCancel(h)	((h->Connection->CancelCall) ? YES : NO)

#ifdef PROTOTYPE
extern pVOID (*ntAllocLink)( LONG );
extern void  (*ntFreeLink)( pVOID );
#else
extern pVOID (*ntAllocLink)();
extern void  (*ntFreeLink)();
#endif

#ifdef	PROTOTYPE

#ifdef ntTCP
void ntTcpDeinitialize( pSESSION Session );
#endif
#ifdef ntSHM
void ntShmDeinitialize( pSESSION Session );
#endif

#ifdef ntSPX
#ifdef ntWIN16
void ntDECL ntSpxDeinit( pSESSION Session );
#endif
#endif

NINT ntDECL ntTcpStartUp( pCONNECTION Socket );
NINT ntDECL ntSpxStartUp( pCONNECTION Socket );
NINT ntDECL ntNetStartUp( pCONNECTION Socket );
NINT ntDECL ntShmStartUp( pCONNECTION Socket );

pVOID ntDECL ntMemAlloc( LONG Size );
void ntDECL ntMemFree( pVOID Buffer );
pVOID ntDECL ntMemFill( pVOID Buffer, NINT Char, LONG Size );
pVOID ntDECL ntMemCopy( pVOID Dest, pVOID Source, LONG Size );

NINT ntDECL ntTextLen( pTEXT Text );
pTEXT ntDECL ntTextDup( pTEXT Text );
pTEXT ntDECL ntTextAlloc( NINT Size );
void ntDECL ntTextFree( pTEXT Text );
pTEXT ntDECL ntTextCopy( pTEXT Dest, pTEXT Source );
pTEXT ntDECL ntTextMove( pTEXT Dest, pTEXT Source, NINT Size );
pTEXT ntDECL ntTextChar( pTEXT Text, NINT Char );

NINT NtssSemrqs(pSESSION Session, NINT SemId);
NINT NtssSemclr(pSESSION Session, NINT SemId);
NINT ntDefer( pCONNECTION Connection, LONG Wait, NINT Location );
NINT ntChkBlking( pCONNECTION Connection, NINT Mode, NINT  Location );
void ntAcceptKill(pSESSION Session, pTEXT svnam);

#else	/* PROTOTYPE */

#ifdef ntTCP
void ntTcpDeinitialize();
#endif
#ifdef ntSHM
void ntShmDeinitialize();
#endif

#ifdef ntSPX
#ifdef ntWIN16
void ntDECL ntSpxDeinit();
#endif
#endif

NINT ntDECL ntTcpStartUp();
NINT ntDECL ntSpxStartUp();
NINT ntDECL ntNetStartUp();
NINT ntDECL ntShmStartUp();

pVOID ntDECL ntMemAlloc();
void ntDECL ntMemFree();
pVOID ntDECL ntMemFill();
pVOID ntDECL ntMemCopy();

NINT ntDECL ntTextLen();
pTEXT ntDECL ntTextDup();
pTEXT ntDECL ntTextAlloc();
void ntDECL ntTextFree();
pTEXT ntDECL ntTextCopy();
pTEXT ntDECL ntTextMove();
pTEXT ntDECL ntTextChar();

NINT NtssSemrqs();
NINT NtssSemclr();
NINT ntDefer();
NINT ntChkBlking();
VOID ntAcceptKill();

#endif	/* PROTOTYPE */

#ifdef __cplusplus
}
#endif

#endif	/* _NTREESTD_INCLUDED */

/* end of ntreestd.h */
