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

#ifndef _NTREETC2_INCLUDED
#define _NTREETC2_INCLUDED

#include "ntreestd.h"

#ifdef ntTCP
#define ntTCPIP
#endif

#ifdef ntTCPIP

/*^***********************************/
#ifdef ntMAC

#ifndef  ctntMAC
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <Devices.h>
#include <Files.h>
#include <StandardFile.h>
#include <GestaltEqu.h> 
#include <memory.h>
#include <MacTCP.h>
#include "AddressXlation.h"
#endif /* ~ctntMAC */

#define SOCK_STREAM     1               /* stream socket */
#define INADDR_ANY		(unsigned long)0x00000000
#define SOL_SOCKET      0xffff          /* options for socket level */
#define SO_DONTROUTE    0x0010          /* just use interface addresses */
#define SO_KEEPALIVE    0x0008          /* keep connections alive */
#define TCP_NODELAY     0x0001
#define IPPROTO_TCP     6               /* tcp */
#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */

/*
 * Commands for ioctlsocket(),  taken from the BSD file fcntl.h.
 *
 *
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
 */
#define IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define IOC_VOID        0x20000000      /* no parameters */
#define IOC_OUT         0x40000000      /* copy out parameters */
#define IOC_IN          0x80000000      /* copy in parameters */
#define IOC_INOUT       (IOC_IN|IOC_OUT)
                                        /* 0x20000000 distinguishes new &
                                           old ioctl's */
#define _IO(x,y)        (IOC_VOID|((x)<<8)|(y))

#define _IOR(x,y,t)     (IOC_OUT|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define _IOW(x,y,t)     (IOC_IN|(((long)sizeof(t)&IOCPARM_MASK)<<16)|((x)<<8)|(y))

#define FIONREAD    _IOR('f', 127, unsigned long) /* get # bytes to read */
#define FIONBIO     _IOW('f', 126, unsigned long) /* set/clear non-blocking i/o */
#define FIOASYNC    _IOW('f', 125, unsigned long) /* set/clear async i/o */

/*
 * Structure used by kernel to store most
 * addresses.
 */
struct mac_sockaddr {
        unsigned short sa_family;              /* address family */
        char    sa_data[14];            /* up to 14 bytes of direct address */
};

/*
 * Socket address, internet style.
 */
struct mac_in_addr {
        union {
                struct { unsigned char s_b1,s_b2,s_b3,s_b4; } S_un_b;
                struct { unsigned short s_w1,s_w2; } S_un_w;
                unsigned long S_addr;
        } S_un;
#define s_addr  S_un.S_addr
                                /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2
                                /* host on imp */
#define s_net   S_un.S_un_b.s_b1
                                /* network */
#define s_imp   S_un.S_un_w.s_w2
                                /* imp */
#define s_impno S_un.S_un_b.s_b4
                                /* imp # */
#define s_lh    S_un.S_un_b.s_b3
                                /* logical host */
};

struct mac_sockaddr_in {
        short   sin_family;
        unsigned short sin_port;
        struct  mac_in_addr sin_addr;
        char    sin_zero[8];
};

/*
 * Structures returned by network data base library, taken from the
 * BSD file netdb.h.  All addresses are supplied in host order, and
 * returned in network order (suitable for use in system calls).
 */
struct  mac_hostent {
        char    * h_name;		/* official name of host */
        char    ** h_aliases;		/* alias list */
        short   h_addrtype;             /* host address type */
        short   h_length;               /* length of address */
        char    ** h_addr_list;		/* list of addresses */
	long 	h_addr;		        /* MAC address */
/* #define h_addr  h_addr_list[0]  */    /* address, for backward compat */
};

/*****/

#define ntHostEnt	mac_hostent
#define ntSEND		mac_send
#define ntRECV		mac_recv
#define ntGetHostName	mac_gethostname
#define ntGetHostByName mac_gethostbyname
#define ntSetSockOpt	mac_setsockopt
#define ntGetSockOpt	mac_getsockopt
#define ntSOCKET	mac_socket
#define ntHTONS		mac_htons
#define ntHTONL		mac_htonl
#define ntNTOHL		mac_ntohl
#define ntBIND		mac_bind
#define ntACCEPT	mac_accept
#define ntCONNECT	mac_connect
#define ntLISTEN	mac_listen
#define ntCLOSE		mac_close
#define ntSHUTDOWN	mac_shutdown
#define ntIOCTL		mac_ioctl

/* typedef int                              SOCKET; */
typedef unsigned long                       SOCKET; /* MacTCP stream */
#define INVALID_SOCKET                      -1
#define SOCKET_ERROR                        -1
#define SOCKADDR_IN                         struct mac_sockaddr_in
#define LPSOCKADDR                          struct mac_sockaddr_in *
#define pOPTVAL                             const char ntFAR*
#define ntSOCLOSE                           ntCLOSE
#define ntSOIOCTL			    ntIOCTL
#define pTCPARGLEN                          int *
#define pTCPADDRLEN                         int *

#endif /* ntMAC */
/*~***********************************/


/*^***********************************/
#ifdef ntWIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock.h>

#ifndef SOCKADDR_IN
#define SOCKADDR_IN                            struct sockaddr_in /* RAB:990721 */
#endif

#define pTCPARGLEN                             int *
#define pTCPADDRLEN                            int *
#define pOPTVAL                                const char ntFAR*
#define ntSOCLOSE                              closesocket
#define ntSOIOCTL			       ioctlsocket

#endif /* ntWIN */
/*~***********************************/


/*^***********************************/
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
/* #define SOCKADDR_IN                      struct sockaddr */ /* RAB:990721 */
#define SOCKADDR_IN                         struct sockaddr_in /* RAB:990721 */
#define LPSOCKADDR                          struct sockaddr*
#define pOPTVAL                             const char ntFAR*
#define ntSOCLOSE                           close
#define ntSOIOCTL			    ioctl

#ifdef ctPortRS6000
#define pTCPARGLEN                          unsigned int *
#define pTCPADDRLEN                         unsigned int *
#else  /* ~ctPortRS6000 */

#if defined(ctPortSOLARIS) || defined(ctPortMACOSX) || defined(ctPortHP9000)
#define pTCPARGLEN                          socklen_t *
#define pTCPADDRLEN                         socklen_t *
#else  /* ~(ctPortSOLARIS || ctPortMACOSX || defined(ctPortHP9000)) */

#define pTCPARGLEN                          int *
#define pTCPADDRLEN                         int *

#endif /* ~(ctPortSOLARIS || ctPortMACOSX || defined(ctPortHP9000)) */
#endif /* ~ctPortRS6000 */

#endif /* ntUNIX */
/*~***********************************/


/*^***********************************/
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
/* #define SOCKADDR_IN                      struct sockaddr */ /* RAB:990721 */
#define SOCKADDR_IN                         struct sockaddr_in /* RAB:990721 */
#define LPSOCKADDR                          struct sockaddr*
#define pTCPARGLEN                          int *
#define pTCPADDRLEN                         int *
#define pOPTVAL                             char ntFAR*
#define ntSOCLOSE                           soclose
#define ntSOIOCTL			    ioctl

#endif /* ntOS2 */
/*~***********************************/


/*^***********************************/
#ifndef ntSEND
#define ntSEND 		send
#endif

#ifndef ntRECV
#define ntRECV 		recv
#endif


#ifndef ntGetHostName
#define ntGetHostName 	gethostname
#endif


#ifndef ntGetHostByName
#define ntGetHostByName gethostbyname
#endif

#ifndef ntHostEnt
#define ntHostEnt 	hostent
#endif

#ifndef ntSetSockOpt
#define ntSetSockOpt 	setsockopt
#endif

#ifndef ntGetSockOpt
#define ntGetSockOpt 	getsockopt
#endif

#ifndef ntSOCKET
#define ntSOCKET 	socket
#endif

#ifndef ntHTONS
#define ntHTONS		htons
#endif

#ifndef ntHTONL
#define ntHTONL		htonl
#endif

#ifndef ntNTOHL
#define ntNTOHL		ntohl
#endif

#ifndef ntBIND
#define ntBIND		bind
#endif

#ifndef ntACCEPT
#define ntACCEPT	accept
#endif

#ifndef ntCONNECT
#define ntCONNECT	connect
#endif

#ifndef ntLISTEN
#define ntLISTEN	listen
#endif

#ifndef ntCLOSE
#define ntCLOSE		close
#endif

#ifndef ntSHUTDOWN
#define ntSHUTDOWN	shutdown
#endif

#ifndef ntIOCTL
#define ntIOCTL		ioctl
#endif

/*~***********************************/


/*^***********************************/
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
/*~***********************************/
	

/*^***********************************/
typedef struct TCPSOCK ntFAR* pTCPSOCK;

struct TCPSOCK
{
   pCONNECTION Connection;
   SOCKET   Socket;
   SOCKADDR_IN	Addr;
   SOCKADDR_IN	Peer;
   pUTEXT	Frame;
   LONG  FrameSize;
   LONG  FrameBytes;
   LONG  FrameIndex;
   LONG  DataSize;
   UTEXT FrameType;
   NINT  LastError;
   NINT  Mode;
   LONG  PreviousTotal;
#ifdef ntMAC
   OSErr ioResult;
   COUNT ioRefNum; 	/* MAC ref */
   UCOUNT myPort;
   ULONG  myAddr;
#endif
};

#define TCPSOCK_SIZE	sizeof( struct TCPSOCK )
/*~***********************************/


/*^***********************************/
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
NINT ntDECL TcpCloseSocket( pSESSION Session );
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
/*~***********************************/

#endif   /* ntTCPIP */

#endif   /* _NTREETC2_INCLUDED */
