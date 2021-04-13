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
*   NTREETCP.H
*
*   This is the internal header file for the TCP/IP Stream.
*  It automatically includes NTREELIB.H and is used by all modules
*  in the library. Uses should not include this module since it is
*   used internally by NTREE.
*
***********************************************************************/

#ifndef _NTREETC1_INCLUDED
#define _NTREETC1_INCLUDED

#include "ntreestd.h"

#ifdef ntTCP
#define ntTCPIP
#endif

#ifdef ntTCPIP

#ifdef ntWIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock.h>

#define pTCPARGLEN                             int *
#define pTCPADDRLEN                            int *
#define pOPTVAL                                const char ntFAR*
#define ntSOCLOSE                              closesocket
#define ntSOIOCTL			       ioctlsocket

#endif /* ntWIN */

#ifdef ntUNIX

#ifdef ctPortHP9000
#define _XOPEN_SOURCE_EXTENDED
#endif

#ifndef  ctntUNIX
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif

typedef int                                 SOCKET;
#define INVALID_SOCKET                      -1
#define SOCKET_ERROR                        -1
#define SOCKADDR_IN                         struct sockaddr
#define LPSOCKADDR                          struct sockaddr*
#define pOPTVAL                             const char ntFAR*
#define ntSOCLOSE                           close
#define ntSOIOCTL			    ioctl

#if defined(ctPortRS6000) || defined(ctPortSCO386)
#define pTCPARGLEN                          unsigned int *
#define pTCPADDRLEN                         unsigned int *
#else  /* ~(ctPortRS6000 || ctPortSCO386) */

#if defined(ctPortSOLARIS) || defined(ctPortMACOSX) || defined(ctPortHP9000)
#define pTCPARGLEN                          socklen_t *
#define pTCPADDRLEN                         socklen_t *
#else  /* ~(ctPortSOLARIS || ctPortMACOSX || defined(ctPortHP9000)) */

#define pTCPARGLEN                          int *
#define pTCPADDRLEN                         int *

#endif /* ~(ctPortSOLARIS || ctPortMACOSX || defined(ctPortHP9000)) */
#endif /* ~ctPortRS6000 */

#endif /* ntUNIX */

#ifdef ntOS2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types.h>
#include <netdb.h>
#include <sys\socket.h>
/* #include <netinet\tcp.h>	RAB removed */
/* #include <netinet\in.h>  	RAB removed */
#include <sys\ioctl.h>
/* #include <net\route.h> */
/* #include <net\if.h> */
/* #include <net\if_arp.h> */

typedef int                                 SOCKET;
#define INVALID_SOCKET                      -1
#define SOCKET_ERROR                        -1
#define SOCKADDR_IN                         struct sockaddr
#define LPSOCKADDR                          struct sockaddr*
#define pTCPARGLEN                          int *
#define pTCPADDRLEN                         int *
#define pOPTVAL                             char ntFAR*
#define ntSOCLOSE                           soclose
#define ntSOIOCTL			    ioctl

#endif /* ntOS2 */

#define ntTCPTIMEOUT                           0
#define ntTCPBLOCKTIME                         250000L
#define ntTCPHEADERSIZE                        (sizeof( UTEXT ) + sizeof( ULONG ))
#define ntTCPDATASIZE                          ( 1024 * 4 )
#define ntTCPFRAMESIZE                         (ntTCPHEADERSIZE + ntTCPDATASIZE)
#define ntTCPFRAMEMIN                          (1024 + ntTCPHEADERSIZE)

#define ntTCPMAXSEND                           (1024 * 16)
#define ntTCPMAXRECV                           (1024 * 31)

#define ntWINSOCKVER                           0x0101
#define ntTCPPORT                              7001 /* remember FairCom Legacy protocol used 5001 */
#define ntTCPMAXVECTOR 			       5

#define ntTCPLOWLEVELBUFF	4096 	/* Used in nttcpvec low	*/
					/* level recv & send	*/
					/* for systems without	*/
					/* readv & writev.	*/
	

typedef struct TCPSOCK ntFAR*            pTCPSOCK;

struct TCPSOCK
{
   pCONNECTION Connection;
   SOCKET   Socket;
   struct   sockaddr_in                  Addr;
   struct   sockaddr_in                  Peer;
   pUTEXT   Frame;
   LONG  FrameSize;
   LONG  FrameBytes;
   LONG  FrameIndex;
   LONG  DataSize;
   UTEXT FrameType;
   NINT  LastError;
   NINT  Mode;
   LONG  PreviousTotal;
};

#define TCPSOCK_SIZE                     sizeof( struct TCPSOCK )

#ifdef   PROTOTYPE

NINT ntDECL ntTcpOpen( pCONNECTION Socket );
NINT ntDECL ntTcpClose( pCONNECTION Socket );
NINT ntDECL ntTcpShutdown( pCONNECTION Socket );
NINT ntDECL ntTcpCleanUp( pCONNECTION Socket );
NINT ntDECL ntTcpReceive( pCONNECTION Socket, pVOID Buffer, LONG BufferSize, pLONG BytesReceived );
NINT ntDECL ntTcpSend( pCONNECTION Socket, pVOID Buffer, LONG BytesToSend, pLONG BytesSent );
NINT ntDECL ntQueSend( pCONNECTION Socket, pVOID Buffer, LONG BytesToSend, pLONG BytesSent );
NINT ntDECL ntTcpReadVector( pCONNECTION Connection, pVECTOR Vector, NINT Count, pLONG BytesReceived );
NINT ntDECL ntTcpWriteVector( pCONNECTION Connection, pVECTOR Vector, NINT Count, pLONG BytesSent );
NINT ntDECL ntTcpRecvVector( pCONNECTION Connection, pVECTOR Vector, NINT Count, pLONG BytesReceived );
NINT ntDECL ntTcpSendVector( pCONNECTION Connection, pVECTOR Vector, NINT Count, pLONG BytesSent );
NINT ntDECL ntTcpSetOption( pCONNECTION Socket, NINT Option, LONG Value );
NINT ntDECL ntTcpGetOption( pCONNECTION Socket, NINT Option, pLONG Value );

pVOID ntDECL ntTcpHandle( pCONNECTION Connection );
UCOUNT ntDECL ntTcpPort( pTEXT ServerName );
ULONG ntDECL ntTcpHostAddr( pCONNECTION Socket );

NINT ntDECL TcpStartup( void );
NINT ntDECL TcpCleanup( void );

SOCKET ntDECL TcpSocket( pTCPSOCK Handle, NINT Family );
NINT ntDECL TcpBind( pTCPSOCK Handle, SOCKET Socket, ULONG Addr, UCOUNT Port );
NINT ntDECL TcpConnect( pTCPSOCK Handle, SOCKET Socket, ULONG Addr, UCOUNT Port );
NINT ntDECL TcpListen( pTCPSOCK Handle, SOCKET Socket );
NINT ntDECL TcpAccept( pTCPSOCK Handle, SOCKET Socket );
NINT ntDECL TcpClose( pTCPSOCK Handle );
NINT ntDECL TcpCloseSocket( SOCKET Socket );
NINT ntDECL TcpShutdown( pTCPSOCK Handle );
NINT ntDECL TcpSetBlocking( pTCPSOCK Handle, SOCKET Socket, ULONG BlockFlag );
NINT ntDECL TcpCheckWrite( SOCKET Socket, NINT Mode, NINT DefaultError );
NINT ntDECL TcpCheckRead( SOCKET Socket, NINT Mode, NINT DefaultError );

#else /* PROTOTYPE */

NINT ntDECL ntTcpOpen();
NINT ntDECL ntTcpClose();
NINT ntDECL ntTcpShutdown();
NINT ntDECL ntTcpCleanUp();
NINT ntDECL ntTcpReceive();
NINT ntDECL ntTcpSend();
NINT ntDECL ntQueSend();
NINT ntDECL ntTcpReadVector();
NINT ntDECL ntTcpWriteVector();
NINT ntDECL ntTcpRecvVector();
NINT ntDECL ntTcpSendVector();
NINT ntDECL ntTcpSetOption();
NINT ntDECL ntTcpGetOption();

pVOID ntDECL ntTcpHandle();
UCOUNT ntDECL ntTcpPort();
ULONG ntDECL ntTcpHostAddr();

NINT ntDECL TcpStartup();
NINT ntDECL TcpCleanup();

SOCKET ntDECL TcpSocket();
NINT ntDECL TcpBind();
NINT ntDECL TcpConnect();
NINT ntDECL TcpListen();
NINT ntDECL TcpAccept();
NINT ntDECL TcpClose();
NINT ntDECL TcpCloseSocket();
NINT ntDECL TcpShutdown();
LONG ntDECL TcpSend();
LONG ntDECL TcpRecv();
NINT ntDECL TcpSetBlocking();
NINT ntDECL TcpCheckWrite();
NINT ntDECL TcpCheckRead();

#endif   /* PROTOTYPE */

#endif   /* ntTCPIP */

#endif   /* _NTREETC1_INCLUDED */
