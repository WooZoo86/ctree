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
*   @doc
*
*   @topic NTREE Data Communications Library |
*
*   NTREE is a powerfull and flexible high level API for developing
*   applications that communicates across networks and IPCs.
*
*   Any process can instigate multiple clients and/or server sessions.
*   A session may use any of the protocols supported for the
*       environment and any process may be server and client at the same
*       time.
*
*   NTREE was designed and coded from start to be ported to virtually
*       all environments that support the C language and has support for
*       networks or IPCs. If a given environment supports it, NTREE and
*       its protocols are dinamically loaded (Shared libraries, DLLs,
*       etc.).
*
*   Overall architecture allows for easy implementation of new
*   communications protocol with extensive use of framework design.
*
*   This program is the CONFIDENTIAL and PROPRIETARY property of
*   Faircom<rtm> Corporation. Any anauthorized use, reproduction or
*   transfer of this computer program is strictly prohibited.
*
*   Copyright (c) 1992 - 2020 FairCom Corporation. This is an unpublished
*   work, and is subject to limited distribution and restricted
*       disclosure only. All rights reserved.
*
************************************************************************
*
*      @module NTREELIB.H |
*      This is the base header file for the NTREE API. It must be included by
*      any module that makes references or calls to NTREE.
*
***********************************************************************/

#ifndef _NTREELIB_INCLUDED
#define _NTREELIB_INCLUDED

#ifdef ctPortUNIX
#ifndef CTREE_IS_USED
#define CTREE_IS_USED
#endif
#endif

#if (defined(ctntUNIX) || defined(ctPortUNIX))
#ifndef ntUNIX
#define ntUNIX
#endif
#endif

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef ntUNIX
#include <errno.h>
#endif

/*^***********************************/
#include "ntfcsrvr.h"		/* for use with the FairCom Server */
/*~***********************************/


/*************************************/
#ifdef  _MAC
#ifndef ntPortMAC
#define ntPortMAC
#endif
#endif
/*************************************/



/*************************************/
#ifdef  ctPortMAC_MSCX_MTCLIENT
#ifndef ntPortMAC
#define ntPortMAC
#endif
#endif
/*************************************/

/*************************************/
/* #define ntPortBAGO_KC */
/* #define ntPortCSAPI */

#if (defined(ntPortBAGO_KC) || defined(ntPortCSAPI)  || defined(ctPortWNT386))
#define ntPROTOCOLS_ALREADY_SET 
#define ntTCP

#ifdef  ntPortMAC	/* Apple MAC */
#define ntMSCX		/* VC++ v4.0 XCross compiler */
#define ntMAC
#else

#ifndef ntMSC
#define ntMSC 
#endif

#ifndef ntWINNT
#define ntWINNT
#endif

#endif

#ifndef ntNO_SEMA
#define ntSEMA_SUPPORT
#endif

/* #include <stdio.h> */
#endif
/*************************************/


/***********************************************************************
*
*       LIBRARY DEFINE OPTIONS 
*       =======================
***********************************************************************/
/* #define ntLIBGEN_KEEP_STATS */

#ifdef ntMT
#define ntLIBGEN_CTREE_QUEUES		/* Used for NTREE_CACHE support */
#endif

/* #define ntLIBGEN_INCLUDE_NTSELECT */



/***********************************************************************
*
*       COMPILER DEFINES
*       ================
*
*       You must define one of the following flags in your makefile to
*       identify the compiler you are using.
*
*       ntMSC   refers to Microsoft C compilers
*       ntTCC   Borland Turbo C compiler
*       ntBCC   Borland C compiler
*       ntWTC   Watcom C compiler
*       ntICC   IBM C Set/2 compiler
*       ntSTC   any generic ANSI C compiler
*       ntGCC   GNU C compiler
*       ntCWP   Apple Mac Code Warrior Pro
*       ntMSCX  refers to Microsoft C Cross compiler for the MAC
*
*       You must define one of the following flags in you makefile to
*       identify the target operating system.
*
*       ntWIN16 refers to Microsoft Windows 3.x and WFW 3.11
*       ntWIN95 refers to Windows 95
*       ntWINNT refers to Windows NT
*       ntDOS   refers to MS-DOS 3.x and above
*       ntOS2   refers to OS/2 2.x and OS/2 3.0 Warp
*       ntUNIX  refers to all flavours of Unix
*       ntNLM   refers to Novell NLM
*       ntMAC   refers to Apple MacOS prior to MacOSX
*
*       COMPILER DEPENDENT DEFINES
*       ==========================
*
*       PROTOTYPE       This constant indicates that the compiler accepts
*                               function prototypes as described by the 'ANSI C'
*                               specification.
*
*       ntFAR           This constant defines the FAR memory model
*                               specification
*
*       ntAPI           This constant indicates the declaration for the
*                               exported functions.
*
*       ntDECL          This constant indicates the declaration for any
*                               function that are not exported but need to be
*                               seen by all modules of NTREE.
*
*
*       OPERATING SYSTEM DEPENDENT DEFINES
*       ==================================
*
*       ntWIN           Is automatically defined if ntWIN16 or ntWIN95 or
*                               ntWINNT is specified, and it refers to any version
*                               of Windows.
*
***********************************************************************/

/*^***********************************/
#ifdef ntWIN16

#ifndef NULL
#define NULL    ((void far*)0)
#endif

#define ntIOVEC

#ifndef ntPROTOCOLS_ALREADY_SET 
#define ntTCP
/* #define ntSPX  */
#endif /* ~ntPROTOCOLS_ALREADY_SET */

#endif /* ntWIN16 */
/*~***********************************/

/*^***********************************/
#ifdef ntWIN95
#define ntIOVEC

#ifndef ntPROTOCOLS_ALREADY_SET 
#define ntTCP
#define ntSHM
#define ntNET
/* #define ntSPX */
#endif /* ~ntPROTOCOLS_ALREADY_SET */

#endif /* ntWIN95 */
/*~***********************************/


/*^***********************************/
#ifdef ntWINNT
#define ntIOVEC

#ifndef ntPROTOCOLS_ALREADY_SET
#define ntTCP
#ifndef ctPortWINCE
#define ntSHM
#define ntNET
#endif
/* #define ntSPX */
#endif /* ~ntPROTOCOLS_ALREADY_SET */

#endif /* ntWINNT */
/*~***********************************/


/*^***********************************/
#ifdef ntMAC
#define ntIOVEC

#ifndef ntMSCX
#ifndef ntCWP
#define ntCWP
#endif
#endif

#ifndef ntPROTOCOLS_ALREADY_SET
#define ntTCP
#endif /* ~ntPROTOCOLS_ALREADY_SET */
#endif /* ntMAC */
/*~***********************************/


/*^***********************************/
#ifdef ntUNIX
#define ntIOVEC

#ifndef ntGCC
#ifndef ntSTC
#define ntSTC
#endif
#endif


#ifndef ntPROTOCOLS_ALREADY_SET
#define ntTCP
#define ntSHM
#endif /* ~ntPROTOCOLS_ALREADY_SET */

#endif /* ntUNIX */
/*~***********************************/


/*^***********************************/
#ifdef ntOS2
#define ntIOVEC

#ifndef ntPROTOCOLS_ALREADY_SET
#define ntSHM
#define ntNET
#define ntTCP
#endif /* ~ntPROTOCOLS_ALREADY_SET */

#endif /* ntOS2 */
/*~***********************************/

/***********************************************************************
*
*       Microsoft C/C++ compiler defines. Microsoft C/C++ compilers may be
*       used to compile NTREE for DOS, Windows 3.x, Windows 95 and
*       Windows NT.
*
***********************************************************************/

#ifdef ntMSC

#ifndef NO_PROTOTYPE
#define PROTOTYPE
#endif

#ifdef ntWIN16
#define ntWIN
#define ntFAR           far
#define ntDECL          far
#define ntAPI           far pascal
#endif /* ntWIN16 */

#ifdef  ntWIN95
#define ntFAR
#define ntDECL
#define ntAPI   __stdcall
#define ntWIN
#define ntWIN32
#endif  /* ntWIN95 */

#ifdef  ntWINNT
#define ntFAR
#define ntDECL
#define ntAPI   __stdcall
#define ntWIN
#define ntWIN32
#endif  /* ntWINNT */

#ifdef  ntDOS
#define ntFAR   far
#define ntDECL  far
#define ntAPI   far pascal
#endif  /* ntDOS */

#endif /* ntMSC */


/***********************************************************************
*
*       Microsoft C/C++ v4.0 Xcross compiler for the MAC.
*
***********************************************************************/

#ifdef ntMSCX

#ifndef NO_PROTOTYPE
#define PROTOTYPE
#endif

#define ntFAR
#define ntDECL
#define ntAPI   __stdcall

#ifndef ntMAC
#define ntMAC
#endif

#endif /* ntMSCX */

/***********************************************************************
*
*       Apple MAC Code Warrior Pro 
*       Use this compiler to build NTREE for Apple MAC 
*
***********************************************************************/

#ifdef ntCWP

#ifndef NO_PROTOTYPE
#define PROTOTYPE
#endif

#ifdef ntMAC
#define ntFAR
#define ntDECL
#define ntAPI
#endif /* ntMAC */

#endif /* ntCWP */


/***********************************************************************
*
*       Standard C compiler definitions, use mostly with
*       Unix systems.
*
***********************************************************************/
#ifdef ntSTC

#ifndef ctntUNIX
#ifndef NO_PROTOTYPE
#define PROTOTYPE 
#endif
#endif

#ifndef ctPortHP9000
extern int errno;
#endif

#ifdef  ntUNIX
#define ntFAR
#define ntDECL

#ifdef 	ntAPI
#undef 	ntAPI /* cannot understand why we get redefinition from ctnlib.c */
#endif
#define ntAPI

#endif /* ntUNIX */

#endif /* ntSTC */

/***********************************************************************
*
*       GNU C compiler definitions. GNU C compilers are use mostly with
*       Unix systems, specially with Linux.
*
***********************************************************************/

#ifdef ntGCC

#ifndef ctntUNIX
#ifndef NO_PROTOTYPE
#define PROTOTYPE
#endif
#endif

extern int errno;

#ifdef ntUNIX
#define ntFAR
#define ntDECL

#ifdef 	ntAPI
#undef 	ntAPI /* cannot understand why we get redefinition from ctnlib.c */
#endif
#define ntAPI

#endif /* ntUNIX */

#endif /* ntGCC */

/***********************************************************************
*
*       IBM Visual C++ compiler
*       Use this compiler to build NTREE for OS/2
*
***********************************************************************/

#ifdef ntICC

#ifndef NO_PROTOTYPE
#define PROTOTYPE
#endif

#ifdef ntOS2
#define ntFAR
#define ntDECL
#define ntAPI
#endif /* ntOS2 */

#endif /* ntICC */

/***********************************************************************
*
*       Define CTREE_IS_USED in your makefile if NTREE is being used with
*       C-tree Plus. This will avoid multiple declarations of the base
*       types used by NTREE. If NTREE is being used with C-tree Plus, you
*       must include NTREELIB.H after the C-tree Plus include files.
*
***********************************************************************/

#ifndef CTREE_IS_USED

/***********************************************************************
*
*       @flag   NO      | Boolean result of FALSE. Defined as 0.
*       @flag   YES     | Boolean result of TRUE. Defined as 1.
*       @flag   VOID    | Void type definition.
*       @flag   pVOID   | Pointer to VOID.
*       @flag   TEXT    | 8 bit signed char.
*       @flag   pTEXT   | Pointer to TEXT;
*       @flag   UTEXT   | 8 bit unsigned char.
*       @flag   pUTEXT  | Pointer to UTEXT.
*       @flag   COUNT   | 16 bit signed integer.
*       @flag   pCOUNT  | Pointer to COUNT.
*       @flag   UCOUNT  | 16 bit unsigned integer.
*       @flag   pUCOUNT | Pointer to UCOUNT.
*       @flag   LONG    | 32 bit signed integer.
*       @flag   pLONG   | Pointer to LONG.
*       @flag   ULONG   | 32 bit unsigned integer.
*       @flag   pULONG  | Pointer to ULONG.
*       @flag   NINT    | Natural integer for the environment.
*       @flag   pNINT   | Pointer to NINT.
*       @flag   NUINT   | Natural unsigned integer for the environment.
*       @flag   pNUINT  | Pointer to NUINT.
*       @flag   YESNO   | Boolean type that should hold YES or NO values.
*                         This type is defined to be the natural integer
*                         of the environment.
*                       
***********************************************************************/

#define NO                              0
#define YES                             1

#ifdef ntWIN16
#define VOID                    void
#endif
			
typedef char            TEXT;
typedef unsigned char   UTEXT;
typedef short           COUNT;
typedef unsigned short  UCOUNT;

#ifndef LONG
typedef long		LONG;
#endif
typedef unsigned long   ULONG;
typedef int             NINT;
typedef unsigned int    NUINT;
typedef TEXT ntFAR *    pTEXT;
typedef UTEXT ntFAR *   pUTEXT;
typedef COUNT ntFAR *   pCOUNT;
typedef UCOUNT ntFAR *  pUCOUNT;
typedef LONG ntFAR *    pLONG;
typedef ULONG ntFAR *   pULONG;
typedef void ntFAR *    pVOID;
typedef void ntFAR **   ppVOID;
typedef NINT ntFAR *    pNINT;
typedef NUINT ntFAR *   pNUINT;

#ifdef _WIN64
/* Win64's long int is 32 bits, but we want  */
/* NLONG/UNLONG to be the size of a pointer. */
typedef __int64		 NLONG;
typedef unsigned __int64 UNLONG;
#else
typedef long int	NLONG;
typedef unsigned long	UNLONG;
#endif

#endif  /* CTREE_IS_USED */

typedef NINT                    YESNO;

/***********************************************************************
*
*       @enum   NTREE_PROTOCOLS |
*                       Protocols supported by NTREE.
*
*       @emem   NTREE_TCP |
*                       TCP/IP stream sockets.  
*       @emem   NTREE_SPX |
*                       Novel SPX protocol.
*       @emem   NTREE_NET |
*                       NetBios protocol.
*       @emem   NTREE_SHM |
*                       Shared memory IPC.
*       @emem   NTREE_APT |
*                       AppleTalk protocol.
*
***********************************************************************/
enum NTREE_PROTOCOLS
{
	NTREE_TCP       = 1,
	NTREE_SPX,              
	NTREE_NET,              
	NTREE_SHM,      
	NTREE_APT,              

	NTREE_LAST_PROTOCOL
};

/***********************************************************************
*
*       @enum   NTREE_CONNECTIONS |
*                       Types of connections supported by NTREE.
*
*       @emem   NTREE_SERVER |
*                       Server type connection
*       @emem   NTREE_CLIENT |
*                       Client type connection
*
***********************************************************************/
enum NTREE_CONNECTIONS
{
	NTREE_SERVER = 1,
	NTREE_CLIENT
};

/***********************************************************************
*
*       @enum   NTREE_OPTIONS |
*                       Option values supported by NTREE.
*
*       @emem   NTREE_SEND_COMPRESSED |
*                       Attempts to compress data before sending.
*       @emem   NTREE_RECV_COMPRESSED |
*                       Do not uncompress received data.
*       @emem   NTREE_BROADCAST |
*                       Allow transmission of broadcast messages.
*       @emem   NTREE_DONTLINGER |
*                       Don't block close waiting for unsent data to be sent.
*       @emem   NTREE_DONTROUTE |
*                       Do not route: send directly to interface.
*       @emem   NTREE_KEEPALIVE |
*                       Send Keep alive packets.
*       @emem   NTREE_SENDBUF |
*                       Specify buffer size for sends.
*       @emem   NTREE_RECVBUF |
*                       Specify buffer size of receives.
*       @emem   NTREE_NODELAY |
*                       Do not wait to send small packets.
*       @emem   NTREE_SERVER_TYPE |
*                       Set Novel NLM server type. You must set this
*                       value before calling ntOpen to open an SPX or
*                       IPX connection.
*		@emem	NTREE_STREAM |
*			Set the TCP/IP connection to stream mode.
*		@emem	NTREE_CACHE |
*			Set the TCP/IP connection to cache mode.
*		@emem	NTREE_STAT |
*			Set the TCP/IP connection to gather statistics.
*
***********************************************************************/
enum NTREE_OPTIONS
{
	NTREE_SEND_COMPRESSED = 1,
	NTREE_RECV_COMPRESSED,
	NTREE_BROADCAST,
	NTREE_DONTLINGER,
	NTREE_DONTROUTE,
	NTREE_KEEPALIVE,
	NTREE_SENDBUF,
	NTREE_RECVBUF,
	NTREE_NODELAY,
	NTREE_SERVER_TYPE,
	NTREE_STREAM,
	NTREE_CACHE,
	NTREE_STAT
};

/***********************************************************************
*
*       @enum   NTREE_MODES |
*                       NTREE operating modes.
*
*       @emem   NTREE_BLOCK |
*                       NTREE blocks on low level calls.
*
*       @emem   NTREE_NONBLOCK |
*                       NTREE calls <f ntDefer> if a low level call would block.
*
***********************************************************************/
/* The following defines the mode available for the ntOpen function */
/* NTREE_MODES */
#define NTREE_CONNECTION	((NINT)(0x0000))
#define NTREE_STREAMED		((NINT)(0x0001))
#define NTREE_CACHED		((NINT)(0x0002))
#define NTREE_BLOCK 		((NINT)(0x0004))
#define NTREE_NONBLOCK 		((NINT)(0x0008))
#define NTREE_STATS		((NINT)(0x0010))
/* #define NTREE_FUTURE2	((NINT)(0x0020)) */

enum NTREE_DEFER_RESULTS		/* Results from the defer function */
{
	NTREE_DEFER_CONTINUE,		/* Continue processing	*/
	NTREE_DEFER_ABORT		/* Abort processing and return NTERR_INTERRUPTED */
};

enum NTREE_DEFER_PRIORITIES
{
	NTREE_NEVER_WAIT,			/* If possible do not defer this thread */
	NTREE_MAY_WAIT,				/* Defer this thread but return control as soon as possible */
	NTREE_ANY_WAIT				/* Defer this thread and you may take your time */
};

enum NTREE_LOOPS
{
	NTREE_LOOP_ABORT,
	NTREE_LOOP_TCP_FLUSH,
	NTREE_LOOP_TCP_RECVLONG,
	NTREE_LOOP_TCP_RECEIVE,
	NTREE_LOOP_TCP_READVECTOR,
	NTREE_LOOP_TCP_PUT,
	NTREE_LOOP_TCP_GET,
	NTREE_LOOP_TCP_WRITE,
	NTREE_LOOP_TCP_READ,
	NTREE_LOOP_TCP_CONNECT,
	NTREE_LOOP_TCP_ACCEPT,
	NTREE_LOOP_TCP_CLOSESOCKET,
	NTREE_LOOP_TCP_SEND,
  	NTREE_LOOP_TCP_RECV,
	NTREE_LOOP_SHM_SEMWAIT,
	NTREE_LOOP_SHM_PIPEOPENREAD,
	NTREE_LOOP_SHM_PIPEOPENWRITE,
	NTREE_LOOP_SHM_PIPEREAD,
	NTREE_LOOP_SHM_PIPEWRITE,
	NTREE_LOOP_SHM_PIPECONNECT,
	NTREE_LOOP_SHM_SEMRELEASE,
	NTREE_LOOP_SHM_PIPELISTEN,
	NTREE_LOOP_NET_REQUEST,
	NTREE_LOOP_NET_SEND,
	NTREE_LOOP_NET_RECV,
	NTREE_LOOP_NET_READVECTOR
};

enum NTREE_CHKBLOCK_STATES
{
	NTREE_STATE_OPEN,
	NTREE_STATE_READ,
	NTREE_STATE_WRITE
};

enum NTREE_CHKBLOCK_MODES
{
	NTREE_MODE_OPEN,
	NTREE_MODE_READ,
	NTREE_MODE_WRITE
};

/***********************************************************************
*
*       NTREE ERROR CODES
*
***********************************************************************/
enum NTREE_ERROR_CODES
{
	NTERR_NONE = 0,                         /*   0 */
	NTERR_NO_MEMORY,                        /*   1 */
	NTERR_NOT_STARTED,                      /*   2 */
	NTERR_NOT_CLOSED,                       /*   3 */
	NTERR_NOT_SUPPORTED,					/*   4 */
	NTERR_ALREADY_OPEN,                     /*   5 */
	NTERR_NOT_OPEN,                         /*   6 */
	NTERR_NO_DATA,                          /*   7 */
	NTERR_NULL,                             /*   8 */
	NTERR_CANT_START,                       /*   9 */
	NTERR_NOT_READY,                        /*  10 */
	NTERR_INV_VERSION,                      /*  11 */
	NTERR_IN_PROGRESS,                      /*  12 */
	NTERR_LOST_CONNECTION,					/*  13 */
	NTERR_CANT_CLEANUP,                     /*  14 */
	NTERR_CANT_OPEN,                        /*  15 */
	NTERR_ADDR_INUSE,                       /*  16 */
	NTERR_INV_ADDRESS,                      /*  17 */
	NTERR_NET_UNREACHED,					/*  18 */
	NTERR_TIMED_OUT,                        /*  19 */
	NTERR_CANT_CLOSE,                       /*  20 */
	NTERR_CANT_SEND,                        /*  21 */
	NTERR_CANT_RECV,                        /*  22 */
	NTERR_NO_OPTION,                        /*  23 */
	NTERR_CANT_SET_OPTION,					/*  24 */
	NTERR_CANT_GET_OPTION,					/*  25 */
	NTERR_CANT_COMPRESS,					/*  26 */
	NTERR_CANT_UNCOMPRESS,					/*  27 */
	NTERR_BUFFER_SMALL,                     /*  28 */
	NTERR_DATA_LOSS,                        /*  29 */
	NTERR_NOT_IMPLEMENTED,					/*  30 */
	NTERR_INV_MODE,                         /*  31 */
	NTERR_SYS_NOT_READY,					/*  32 */
	NTERR_NET_DOWN,                         /*  33 */
	NTERR_NO_DESCRIPTORS,					/*  34 */
	NTERR_TOO_MANY_CONNECTIONS,				/*  35 */
	NTERR_NO_BUFFERS,                       /*  36 */
	NTERR_CANCELED,                         /*  37 */
	NTERR_WOULD_BLOCK,                      /*  38 */
	NTERR_ALREADY_CLOSED,					/*  39 */
	NTERR_CANT_CANCEL,                      /*  40 */
	NTERR_CANT_SET_BLOCKING,				/*  41 */
	NTERR_NOT_READABLE,                     /*  42 */
	NTERR_NOT_WRITEABLE,					/*  43 */
	NTERR_READABLE,                         /*  44 */
	NTERR_WRITEABLE,                        /*  45 */
	NTERR_CANT_SELECT,                      /*  46 */
	NTERR_INTERRUPTED,                      /*  47 */
	NTERR_CLOSE_REQUEST,					/*  48 */
	NTERR_SEMAPHORE,                        /*  49 */
	NTERR_BROKEN_PIPE,                      /*  50 */
	NTERR_CANT_RESET,						/*  51 */
	NTERR_CONNECTION_CLOSED,				/*  52 */

	NTERR_LAST_ERROR
};

/***********************************************************************
*
*       @type   pSESSION |
*                       Handle to NTREE Session. You must aquire a NTREE session
*                       handle before attempting to open any connections.
*
***********************************************************************/
typedef struct SESSION ntFAR*   pSESSION;


/***********************************************************************
*
*       @type   pNTSESUSRDATA |
*         		Handle to a NTREE Session UserData. 
*
***********************************************************************/
typedef struct NTSESUSRDATA ntFAR*   pNTSESUSRDATA;


/***********************************************************************
*
* @type   pNTSTATISTICS |
*         Handle to a NTREE statistics. 
*
***********************************************************************/
typedef struct NTSTATISTICS ntFAR* pNTSTATISTICS;

/***********************************************************************
*
* @type   pNTUSRDATA |
*         Handle to a NTREE Connection UserData. 
*
***********************************************************************/
typedef struct NTUSRDATA ntFAR* pNTUSRDATA;


/***********************************************************************
*
* @type   pCONNECTION |
*         Handle to a NTREE connection. Most NTREE functions require a
*         NTREE connection handle.
*
***********************************************************************/
typedef struct CONNECTION ntFAR* pCONNECTION;
typedef struct CONNECTION ntFAR* ntFAR* ppCONNECTION;

/***********************************************************************
*
*       @type   pVECTOR |
*                       Pointer to <t iovec> struct.
*
*       @type   iovec |
*                       Vector definition for <f ntWriteVector> and <f ntReadVector>
*                       function calls.
*       @member pVOID | iov_base |
*                       Starting address of buffer.
*       @member int | iov_base |
*                       Size of buffer in bytes.
*
***********************************************************************/
#ifdef ntIOVEC
struct NTiovec
{
	pVOID   iov_base;
	NINT    iov_len;
};
#endif /* ntIOVEC */
typedef struct NTiovec ntFAR*     pVECTOR;
typedef struct NTiovec ntFAR      IO_VEC;


/***********************************************************************
*
*       Function prototypes.
*
***********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef PROTOTYPE

pSESSION ntAPI ntInitialize( pVOID );
NINT ntAPI ntDeinitialize( pSESSION Session );
YESNO ntAPI ntQuery( pSESSION Session, NINT Protocol );
pCONNECTION ntAPI ntStartUp( pSESSION Session, NINT Protocol, NINT Connection, pTEXT ServerName );
NINT ntAPI ntCleanUp( pCONNECTION Socket );
NINT ntAPI ntOpen( pCONNECTION Socket, NINT Mode );
NINT ntAPI ntClose( pCONNECTION Socket );
NINT ntAPI ntCloseAll( pSESSION Session );
NINT ntAPI ntStats( pCONNECTION Socket );
NINT ntAPI ntStatsConsole( pCONNECTION Socket );
NINT ntAPI ntAbort( pCONNECTION Connection );
NINT ntAPI ntAbortAll( pSESSION Session );
NINT ntAPI ntShutdown( pCONNECTION Socket );
NINT ntAPI ntWrite( pCONNECTION Socket, pVOID Buffer, LONG BytesToSend, pLONG BytesSent );
NINT ntAPI ntWriteVector( pCONNECTION Connection, pVECTOR Vector, NINT Count, pLONG BytesSent );
NINT ntAPI ntRead( pCONNECTION Socket, pVOID Buffer, LONG BufferSize, pLONG BytesReceived );
NINT ntAPI ntReadVector( pCONNECTION Connection, pVECTOR Vector, NINT Count, pLONG BytesReceived );
NINT ntAPI ntSetOption( pCONNECTION Socket, NINT Option, LONG Value );
NINT ntAPI ntGetOption( pCONNECTION Socket, NINT Option, pLONG Value );
YESNO ntAPI ntInProgress( pCONNECTION Connection );
pTEXT ntAPI ntGetServerName( pCONNECTION Socket );
NINT ntAPI ntGetProtocol( pCONNECTION Socket );
NINT ntAPI ntGetConnection( pCONNECTION Socket );
YESNO ntAPI ntIsOpen( pCONNECTION Socket );
pTEXT ntAPI ntParseHostName( pTEXT ServerName );
pTEXT ntAPI ntParseServerName( pTEXT ServerName );
void ntAPI ntMemory( pVOID (*MemAlloc)(LONG), void (*MemFree)(pVOID) );
void ntAPI ntCallBack( pCONNECTION Connection, 
		       NINT (ntDECL* Defer)(pCONNECTION, LONG, NINT), 
		       NINT (ntDECL* ChkBlking)( pCONNECTION, NINT, NINT ));
ULONG ntAPI ntCurrentSystemTime(void);

#else   /* PROTOTYPE */

pSESSION ntAPI ntInitialize();
NINT ntAPI ntDeinitialize();
YESNO ntAPI ntQuery();
pCONNECTION ntAPI ntStartUp();
NINT ntAPI ntCleanUp();
NINT ntAPI ntOpen();
NINT ntAPI ntClose();
NINT ntAPI ntCloseAll();
NINT ntAPI ntStats();
NINT ntAPI ntStatsConsole();
NINT ntAPI ntAbort();
NINT ntAPI ntAbortAll();
NINT ntAPI ntShutdown();
NINT ntAPI ntWrite();
NINT ntAPI ntWriteVector();
NINT ntAPI ntRead();
NINT ntAPI ntReadVector();
NINT ntAPI ntSetOption();
NINT ntAPI ntGetOption();
YESNO ntAPI ntInProgress();
pTEXT ntAPI ntGetServerName();
NINT ntAPI ntGetProtocol();
NINT ntAPI ntGetConnection();
YESNO ntAPI ntIsOpen();
pTEXT ntAPI ntParseHostName();
pTEXT ntAPI ntParseServerName();
void ntAPI ntMemory();
void ntAPI ntCallBack();
ULONG ntAPI ntCurrentSystemTime();
#endif  /* PROTOTYPE */

#ifdef ntMT
#define NQUE_ERR	90	/* Could not create queue */
#define QWRT_ERR	91	/* Queue write error */
#define QMRT_ERR	92	/* Queue memory error during write */
#define QRED_ERR	93	/* Queue read error */
#define CQUE_ERR	514	/* Queue has been closed */
#define NTIM_ERR	156	/* timeout error */
#define ctCONV
#define ctDECL
extern ctCONV  NINT ctDECL ntThrdInit(void);
extern ctCONV  NINT ctDECL ntFlushQueue(NINT qid);
extern ctCONV  NINT ctDECL ctThrdQueueOpen(void );
extern ctCONV  NINT ctDECL ctThrdQueueClose(NINT );
extern ctCONV  NINT ctDECL ctThrdQueueWrite(NINT ,pVOID ,NINT );
extern ctCONV  NINT ctDECL ctThrdQueueWriteDirect(NINT ,pVOID ,NINT );
extern ctCONV  NINT ctDECL ctThrdLIFOWrite(NINT ,pVOID ,NINT );
extern ctCONV  NINT ctDECL ctThrdQueueRead(NINT ,pVOID ,NINT ,LONG );
extern ctCONV  NINT ctDECL ctThrdQueueReadDirect(NINT ,ppVOID ,pNINT ,LONG );
extern ctCONV  NINT ctDECL ctThrdQueueMlen(NINT ,LONG );
extern ctCONV  LONG ctDECL ctThrdQueueCount(NINT );
#endif	/* ntMT 	*/

#ifdef __cplusplus
}
#endif

#endif  /* _NTREELIB_INCLUDED */
