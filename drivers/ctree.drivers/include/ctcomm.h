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

#ifndef ctCOMMH
#define ctCOMMH

#include "ctcom2.h"
#ifdef ctFeatIPv6
#ifdef ctPortUNIX
#define  ctNETINET_IN_H	<netinet/in.h>
#include ctNETINET_IN_H
#endif
#endif

#ifdef ctBEHAV_POLL
#define  ctPOLL_H	<poll.h>
#include ctPOLL_H
#endif

#define ntpUSEHANDLE  /* Activate n-tree Plus Handle passed from server*/

#ifdef  ctPortNTREE_PLUS
#ifdef 	ctPortUNIX
#ifdef 	MULTITRD
#ifndef ctCOMM_POLICE_THREAD
#define ctCOMM_POLICE_THREAD
#endif 	/* ~ctCOMM_POLICE_THREAD */
#endif 	/* MULTITRD */
#endif  /* ctPortUNIX */
#endif  /* ctPortNTREE_PLUS */

#ifdef  ctPortNTREE_PLUS
#ifdef  ctPortNATIVE_THREADS
#ifdef  ctCOMM_POLICE_THREAD
/* This undef will invoke native thread blocking reads  */
/* without selected thread 				*/
/* #undef  ctCOMM_POLICE_THREAD */ 
#endif 	/* ctCOMM_POLICE_THREAD */
#endif  /* ctPortNATIVE_THREADS */
#endif  /* ctPortNTREE_PLUS */

#ifdef ctPortMAC
#ifndef ntpUSEHANDLE
#define ntpUSEHANDLE
#endif
#endif

#ifdef ctThrdApp
#ifndef ntpUSEHANDLE
#define ntpUSEHANDLE
#endif
#endif


/****************************************************/
/* Names available to use for COMM_PROTOCOL keyword */
#define ctUNXCOM_TCP_NAME 	"F_TCPIP"
#define ctUNXCOM_TCP_NAM2 	"FSTCPIP"
#define ctUNXCOM_TCP_NAM3 	"FMacTCP"
#define ctUNXCOM_TCP_IPV6	"F_TCPIPV6"
#define ctUNXCOM_OTPTCP_NAM 	"FMacOTP_TCP"
#define ctUNXCOM_OTPADSP_NAM 	"FMacOTP_ADSP"
#define ctUNXCOM_SSL_NAME	"F_SSL"
#define ctUNXCOM_SSLTCP_NAME	"FSSLTCP"
#define ctUNXCOM_SSLTCPV6_NAME	"FSSLTCPV6"
#define ctUNXCOM_CRYTCP_NAME 	"FETCPIP"
#define ctUNXCOM_SSLSPX_NAME	"FSSLSPX"
#define ctUNXCOM_ADSP_NAM 	"FADSP"
#define ctUNXCOM_SHM_NAME 	"FSHAREMM"
#define ctUNXCOM_QUE_NAME 	"FUNXMSGS"
#define ctUNXCOM_NTP_NAME 	"FNTREEP"
#define ctUNXCOM_QNX_NAME 	"FQNXMSGS"
#define ctUNXCOM_BAN_NAME 	"F_BANSPP"	/* Banyan Sequenced Packet Protocol */


/* n-tree Plus COMM_PROTOCOL protocol names */
#define ctUNXCOM_NTP_SHAREMM 	"SHARED_MEMORY"
#define ctUNXCOM_NTP_SHARED 	"SHARED"
#define ctUNXCOM_NTP_SHM 	"SHM"
#define ctUNXCOM_NTP_SM 	"SM"
#define ctUNXCOM_NTP_NETBIOS 	"NETBIOS"
#define ctUNXCOM_NTP_NB 	"NB"
#define ctUNXCOM_NTP_TCP_IP 	"TCP/IP"
#define ctUNXCOM_NTP_TCPIP 	"TCPIP"
#define ctUNXCOM_NTP_TCP 	"TCP"
#define ctUNXCOM_NTP_SPX 	"SPX"
#define ctUNXCOM_NTP_SPP 	"SPP"		/* Banyan Sequenced Packet Protocol */

/* These defines must coincide with enums in ntreelib.h */
#define ntpNTREE_TCP	((NINT)1)
#define ntpNTREE_SPX	((NINT)2)
#define ntpNTREE_NET	((NINT)3)
#define ntpNTREE_SHM	((NINT)4)

/* Legacy Protocol Identifiers */
#define lcyNTREE_TCP	((NINT)100)
#define lcyNTREE_TCPIPV6 ((NINT) 200)
#define lcyNTREE_SHM_V1 ((NINT)399)	/* Shared memory protocol without 32/64 bit compatibility */
#define lcyNTREE_SHM	((NINT)400)
#define lcyNTREE_QUE	((NINT)500)
#define lcyNTREE_QNX	((NINT)600)
#define lcyNTREE_BAN	((NINT)700)	/* Banyan Sequenced Packet Protocol */
#define lcyNTREE_MacIPX	((NINT)800)
#define lcyNTREE_SPX	((NINT)900)
/****************************************************/

/****************************************************************************/
#ifndef ctSEMA
#include "ctsema.h"
#endif

#ifdef ctPortVINESSEC
#ifndef ctST
#ifdef __OS2__
#define ctSTREETTA_H	<streetta.h>
#include ctSTREETTA_H
#else
#ifdef ctBAN5
#define ctST_H	<ST.h>
#include ctST_H
#else
#define ctSTREETTALK_H	<streettalk.h>
#include ctSTREETTALK_H
#endif
#endif
#define ctST
#endif
#endif

#ifdef ctSP
typedef char far * far *	ppMTEXT;
typedef char far *	pMTEXT;
#else
typedef char ctMEM *	pMTEXT;
typedef char ctMEM *	ctMEM * ppMTEXT;
#endif


/*
** TRAP_COMM header definition. Each entry in log begins with such a header.
**
** A connect is designated by an entry with 0xefef in the ownr member. The
** variable region after this connect header has a two byte thread ID and
** two bytes of flavor information (the clen member should be 4 for this
** connect entry).
**
** A disconnect looks like a connect except that ownr is 0xecec.
**
** A end of log is designated by an entry with 0xeded in the ownr member
** and a zero clen member.
**
** Note that each entry has client and server flavor values so that the type
** of data in the log and the flavor of the header can be determined.
*/
typedef struct TCh_ {
	ULONG	clen;	/* variable region length	*/
	ULONG	olen;	/* possible output length	*/
	UCOUNT	ownr;	/* thread ID	 		*/
	} TC_BUFHDR, * pTC_BUFHDR;
#define TCHDRSIZ	10

typedef struct TCc_ {
	UCOUNT	cmds;
	UCOUNT	ownr;
	UTEXT	flvr;
	UTEXT	sflv;
	} TC_CON, * pTC_CON;
#define TCCONSIZ	6

typedef struct TCb_ {
	LONG	stmp;
	UTEXT	sflv;
	} TC_BEG, * pTC_BEG;
#define TCBEGSIZ	5

#define ctTC_CONN	0xefef
#define ctTC_BEGN	0xeeee
#define ctTC_FNSH	0xeded
#define ctTC_DISC	0xecec
#define ctTC_ACKN	0xebeb

#define ctNPATTRIBUTE_RECEIVE_TIMEOUT	1
#define ctNPATTRIBUTE_SEND_TIMEOUT	2
#define ctNPATTRIBUTE_CLOSE_FORK	3

/* clistate bits */
#define CLISTATE_CLOSE_FORK 0x00000001L

/* Defines used to identify server variable to get */
#define CTNPct_compflg		0
#define CTNPcttflg		1
#define CTNPct_sesout		2
#define CTNPctgv  		3
#define CTNPctbroadcastport	4
#define CTNPctbroadcastdata	5
#define CTNPctbroadcastinterval	6
#define CTNPctdeadint		7
#define CTNPct_diagflg		8
#define CTNPct_diagflg2		9
#define CTNPctgvsema		10
#define CTNPctstatv		11
#define CTNPctbroadcastblk 	12

#define CTNPDELIMITER 			'@'
#define CTNPDELPROTOCOL			'^'
#define CTNPDEL2PROTOCOL		':'

#define	ctNPdisconn		0	/* Disconnect session only */
#define	ctNPdispose		1	/* Disconnect and free session resources */

typedef struct {
	pVOID	 lfseg;	/* optional key segment(for index)/key map(for data file) definitions */
	COUNT	 lfvar; /* # of var segments used in keys */
	UCOUNT	 lflen;	/* length */
	COUNT	 lftyp;	/* clstyp */
	COUNT	 lfmod;	/* file mode */
	COUNT	 lfkey;	/* key type & dup mode */
	FILNO	 lfrev;	/* key to dat map */
	pCOUNT	 lfalt;	/* alternative collating sequence */
} LOCLFILE;
typedef LOCLFILE ctMEM *	pLOCLFILE;

			/*
			** lfseg & lfvar not part of message; but app filno is.
			*/
#define LOCLSIZE2B	(5 * ctSIZE(COUNT) + ctSIZE(UCOUNT)) /* size of data sent to client for file open/create (uses 2-byte file number) */
#ifdef ctFeatMAXFILE32
#define LOCLSIZE	(3 * ctSIZE(COUNT) + ctSIZE(UCOUNT) + 2 * ctSIZE(FILNO)) /* size of data sent to client for file open/create (uses 4-byte file number) */
#else
#define LOCLSIZE	LOCLSIZE2B /* size of data sent to client for file open/create (uses 2-byte file number) */
#endif

typedef struct {
#ifdef ctXTDKEYSEG
	pNINT	kseg;	/* xtdkseg swap byte array */
#ifdef ctFeatKSEGDEFxtd
	ppctKSEGDEF
		pxksd;	/* array of pointers to extended key segment definitions */
	NINT	nxksd;	/* number of extended key segment definitions */
#endif
#endif
#ifdef ctCONDIDX
	pVOID	cndx;	/* conditional index ptr */
	LONG	tflt;	/* type of cond expr	 */
#endif
#ifdef ctPARTITION
	LONG	curpt;	/* current ISAM partition */
#endif
#ifdef ctHUGEFILE
	LONG	curp2;
#endif
	LONG	curp1;	/* current ISAM position */
	LONG	vlen;	/* combined variable length */
	LONG	amsk;	/* auxiliary mask */
#ifdef ctCONDIDX
	COUNT	relk;	/* relative key number */
#else
	COUNT	rsv2;	/* reserved */
#endif
	COUNT	dres;	/* disable resource flag */
} LOCLAUX;
typedef LOCLAUX ctMEM *	pLOCLAUX;

#ifdef ctXTDKEYSEG
#define ctKSEGAUXerror	(-1)
#define ctKSEGAUXlen2	(-2)
#define ctKSEGAUXstrlen (-8)
#endif

typedef struct reqpb {
	COUNT	 pbfn;	/* function #		*/
	COUNT	 pbfl;	/* file #		*/
	LONG	 pblg;	/* long value		*/
	VRLEN	 pbsz;	/* length		*/
	VRLEN	 pbol;	/* output length	*/
	COUNT	 pbmd;	/* mode			*/
	COUNT	 pbvr;	/* version #		*/
	COUNT	 pbna;	/* # of arguments	*/
	UCOUNT	 pbmp;	/* request map		*/
#ifdef ctHUGEFILE
	LONG	 pblg2;
	LONG	 pbrva;
	LONG	 pbrvb;
	ULONG	 pbchk;
#ifdef ctFeatMAXFILE32
	LONG	 pbfl32; /* file number (4 bytes) */
	LONG	 pbmd32; /* mode (4 bytes) */
#endif
#endif
} reqPARMB;
typedef reqPARMB ctMEM *	preqPARMB;

#ifdef ctHUGEFILE
#define hugPARMBz	16 /* size of request/response block fields for ctHUGEFILE */
#ifdef ctFeatMAXFILE32
#define mflPARMBREQz	8 /* size of request block fields for MAXFILE32 */
#define mflPARMBRSPz	8 /* size of response block fields for MAXFILE32 */
#else
#define mflPARMBREQz	0 /* no request block fields for MAXFILE32 */
#define mflPARMBRSPz	0 /* no response block fields for MAXFILE32 */
#endif

/*
** data record conversion indicated by pbrva
*/
#define ALNMSKpbrva	0x0000003f		/* 0x00000001 - 0x00000020   **
						** reserved for source align */
#define BYTORDpbrva	0x00000040		/* C/S byte order control    */
#define FLAVORpbrva	0x00000080		/* C/S byte order rec image  */
#define ALNOVRpbrva	0x00000100		/* Alignment override	     */

#endif /* ctHUGEFILE */

#define	reqPARMBz	ctSIZE(reqPARMB) /* request block size with huge file and 4-byte file number support */
#define	reqPARMBzH	(reqPARMBz - mflPARMBREQz) /* request block size with huge file support */
#define	reqPARMBz4	(reqPARMBz - hugPARMBz - mflPARMBREQz) /* request block size without huge file support */

typedef struct	rsppb {
	COUNT	 qbfn;	/* function #		*/
	COUNT	 qbfl;	/* file #		*/
	LONG	 qblg;	/* long value		*/
	LONG	 qbrv;	/* 2nd long		*/
	LONG	 qbr3;	/* 3rd long		*/
	VRLEN	 qbsz;	/* size value		*/
	COUNT	 qbsh;	/* short value		*/
	COUNT	 qber;	/* error code		*/
	COUNT	 qbef;	/* error file (ISAM)	*/
	COUNT	 qbio;	/* sysio code		*/
	LONG	 qbat;	/* attention channel	*/
#ifdef ctHUGEFILE
	LONG	 qblg2;
	LONG	 qbrv2;
	LONG	 qbr32;
	ULONG	 qbchk;
#ifdef ctFeatMAXFILE32
	LONG	 qbfl32; /* file number (4 bytes) */
	LONG	 qbef32; /* error file (4 bytes) */
#endif
#endif
} rspPARMB;
typedef rspPARMB ctMEM *	prspPARMB;

#define	rspPARMBz	ctSIZE(rspPARMB) /* response block size with huge file and 4-byte file number support */
#define	rspPARMBzH	(rspPARMBz - mflPARMBRSPz) /* response block size with huge file support */
#define	rspPARMBz4	(rspPARMBz - hugPARMBz - mflPARMBRSPz) /* response block size without huge file support */

typedef NLONG	Displace;
typedef UNLONG	RefVal;

typedef struct {
	pMTEXT	pMsg;
	ULONG	msgLen;
} MSGVEC;

typedef MSGVEC ctMEM * pMSGVEC;

#define ctSETMSG(m, p, l)		m.pMsg = (pMTEXT)p; \
										m.msgLen = (ULONG)l
#define ctGETMSG(msg)						msg.pMsg
#define ctGETMSGLEN(msg)					msg.msgLen

typedef struct {
	ULONG		 location;
	RefVal		 value;
} Reference;

typedef struct vab {
	ULONG		 flags;
	Reference	 ref;
	Displace	 reqLength;
	Displace	 posOffset;
	struct vab	*vabMate;
	struct vab	*nxtVab;
} VAB;
typedef VAB ctMEM *	pVAB;

/****************************************************************************/
/* Begin from ctcvec.h */
#ifdef ctSRVR
#ifndef MAXAPPS
  ----Server compilation must have MAXAPP already defined ----
#endif
#else /* ~ctSRVR */

#ifdef MAXAPPS
#undef MAXAPPS /* remove definition from ctopt2.h */
#endif

#define MAXAPPS	1 /* Client only has 1 */
#endif /* ~ctSRVR */

#ifdef  ctDLLOAD
#ifndef BUILDASDLL
#define BUILDASDLL
#endif
#endif

/*********************************************/
#ifdef BUILDASDLL

#ifdef ctPortWINDOWSNT
#define DllExport	__declspec(dllexport)
#define DllLoadDS	
#endif /* ctPortWINDOWSNT */

#ifdef ctPortOS2_2x
#define DllLoadDS	
#define DllExport
#endif /* ctPortOS2_2x */

#ifdef ctPortMAC
#define DllLoadDS	
#define DllExport
#endif /* ctPortMAC */

#ifdef ctPortUNIX
#define DllLoadDS	
#define DllExport
#endif /* ctPortUNIX */

/* Default DLL types */
#ifndef DllLoadDS
#define DllLoadDS	_loadds
#endif

#ifndef DllExport
#define DllExport	_export
#endif

#endif /* BUILDASDLL */
/*********************************************/

/*********************************************/
#ifndef BUILDASDLL 

#ifndef DllExport
#define DllExport
#endif

#ifndef DllLoadDS
#define DllLoadDS
#endif 

#endif /* ~BUILDASDLL */
/*********************************************/

#ifndef far
#define far
#endif

/**************************/ 

#define MAXSERVERS			 1
#define NPCALLVECTORS
#define MAXCTNPCALLBACKS		11
#define MAXCTNPCMDS			12

#define SYNC		false
#define ASYNC		true

#ifndef DeadLock
#define DeadLock  			(~0)
#define ct_NoWait   			(0)
#define ShortWait 			(9)
#define WaitForever 		(~0)
#endif

#define ctMAX_RETRIES	4
#define ctMIN_TIMEOUT	2

/* server broadcast port must be common and known to all clients 		*/
						/* Note we have given v6 	*/
						/* a broadcast of  -1 and v7	*/
						/* a broadcast of  -2 		*/
#define ctsrvBROADCAST_PORT	5595 		/* FAIRCOMS (5597) -2 		*/
#define ctsrvBROADCAST_ADDR	"234.5.6.7"
#define ctsrvBROADCAST_ADDR6 "ff12::1234:5678"
#define ctsrvBROADCAST_INTERVAL	10		/* every 10 sec */
#define ctsrvBROADCAST_INTERVAL_LIMIT 86400L	/* Value used to ensure user does not supply a crazy value for broadcast 	*/
						/* interval. We use (60 sec times 60 min times 24 hours)=86400 seconds. In other*/
						/* words, if the value is greater than once per day, it is to big. 		*/
#include "ctaddr.h"

typedef struct sessto {
	LONG	startTick;
	NINT	tripTime;
	NINT	minTimeout;
	NINT	currTimeout;
	NINT	nextTimeout;
	NINT	meanDev;
	TEXT	nRetries;
} SessRtt, ctMEM *pSessRtt;

typedef struct sessblk
{
	NLONG	hSessionId;
	NLONG	hSessionData;
	UCOUNT	recTimeOut;
	UCOUNT	sndTimeOut;
#ifdef ctIFNEEDED
	SessRtt	recRtt;
	SessRtt	sndRtt;
#endif
	TEXT	remoteName[MAX_SERVER_NAME];
	TEXT	localName[MAX_SERVER_NAME];

	UCOUNT	localSid;	/* session handle from open */
	UCOUNT	srvSid;		/* server session id if appropriate */
	UCOUNT	maxCmdSz;	/* maximum request size */
	UCOUNT	msgSize;	/* appl message size */
	ULONG	lsttick;	/* tickcount at last msg or tickle */
	ULONG	attributes;	/* n-tree Plus uses this for protocol id */
#ifdef ctSRVR
	ULONG	statebits;	/* Special state bits for this session */
#else
	UNLONG	reserved;
	ULONG	clistate;       /* client state information */
#endif
#ifdef ctFeatMAXACTCONN
	LONG	inactivetime;	/* time until connection is marked inactive */
#endif
#ifdef ctFeatKILLSOCKETtimeout
	LONG	killconn;	/* connection has been requested to terminate */
#endif
	pVOID	pGlobals;	/* Backward pointer to n-tree Global Handle */
#ifdef ctFeatSSL
	pVOID	ssldata;        /* SSL- secure socket layer specific data. */
#endif
	NINT	ntOWNR;		/* Thread Owner */
#ifdef ctFeatFOLLETT_HANG
	NINT	nOps;			/* Number of operations before suspending client. */
	NINT	nMin;			/* Number of minutes to suspend client. */
#endif
#ifdef ctFeatJEFFSCOMCODE
	NINT	connected;
#endif
#ifdef ctFeatLOWL_CRC
	NINT	useCRC;
#endif
#ifdef ctFeatNEW_DEAD_CLIENT
	NINT	deadClient;
#endif
#ifdef ctFeatNONBLK_SOCKIO
	NINT	socktimeout; /* max time in seconds to wait for socket I/O before erroring out */
#ifdef ctFeatSOCKET_WAIT_INTERVAL
	ULONG	socketWaitInterval; /* time in seconds to wait for socket I/O before retrying */
#endif
#endif
#ifdef ctFeatUNIX_SHMEM
#ifdef ctCLIENT
	pTEXT	shmemdir;
	NINT	shmemprm; /* permission mode: e.g., 660 */
#endif
#endif
#ifdef ctFeatCAMOCOMM
#ifdef ctCLIENT
	NINT	camo;
#endif
#endif
#ifdef ctFeatTRACK_CLIENT_ADDR
	ctUADDR_T clientAddr;
#endif
#ifdef ctFeatSHMEMspin
	LONG	sendctr;	/* our consecutive send count */
#endif
} Sessblk, ctMEM *pSessblk;

#ifdef ctFeatSOCKET_WAIT_INTERVAL
#define GET_SOCKET_WAIT_INTERVAL(pSession)	((pSession)->socketWaitInterval)
#else
#define GET_SOCKET_WAIT_INTERVAL(pSession)	0
#endif

/*
** The shared memory communication protocol for Windows stores some attributes
** for the shared memory spin feature in the Sessblk's lsttick field. We define
** some of these attributes here rather than in the shared memory ctnlib.h
** because we use this macro in ctappx.c and in ctlgon.c (in addition to the
** shared memory ctnlib.c).
*/
#define SESSION_SHMEM_SPIN		0x00000002	/* client and server support spin  */
#define SESSION_SHMEM_SPIN_OFF		0x00000004	/* spinning disabled for this conn */

/* These are defined in ctree/source/ntree/sharemm/unix/ctnlib_v10.h: */
/* #define SESSION_SHMEM_SPIN_START	0x00000008 */	/* enable spin for this conn	   */
/* #define SESSION_SHMEM_SPIN_STOP	0x00000010 */	/* disable spin for this conn	   */

#define SESSION_SHMEM_SPIN2		0x00000020	/* shared memory spin version 2	   */

/*
** Sessblk statebits field bits used by shared memory protocol on Unix:
*/
#define SHMEM_FLAG_LOGGING_OFF		0x00000001	/* client is logging off */
#define SHMEM_FLAG_FORCE_DISCONNECT     0x00000002	/* disconnect even if client is connected */

/*
** Sessblk statebits field bits used by TCP/IP protocol:
*/
#define TCPIP_FLAG_CAMOCOMM		0x00000001	/* TCP/IP protocol camo indicator */
#define TCPIP_FLAG_CLIENT_BYTORD	0x00000002	/* send message length in client byte order */
#define TCPIP_FLAG_SSL_CONNECT		0x00000004	/* establish SSL connection */

typedef struct SrvrSessGbls {
	UCOUNT	srvNbr;
	UCOUNT	maxcmd;
/*	UCOUNT	maxmsgin;  */
/*	UCOUNT	maxmsgout; */
	UCOUNT	maxusers;
	UCOUNT	activeUsers;
	TEXT	origName[MAX_SERVER_NAME];	
	NLONG	hServerSessionData;
	pVOID	pGlobals;    /* Backward pointer to n-tree Plus Global Handle */
} SrvrSessGbls, ctMEM *pSrvSessGbls;

typedef struct SrvrGbls {
NLONG		hServerGlobalData;
SEMA		srvSema;
/*TEXT 		isWNE; */		/* nonzero if WaitNextEvent trap is valid */
/*NINT		newat; */		/* non zero if new version of at drivers */
LONG  		signature;		/* inited flag	*/
COUNT		nbrSessions;		/* active session count */
ULONG		maxPacketSize;		/* maximum size transmission on this adapter */
pVOID		com_cmds;      		/* Communications functions pointers */
pVOID 		srv_callBackCmds; 	/* Server's function pointers */
pSrvSessGbls	sSess[MAXSERVERS + 1];	/* array of ptrs to sessions */
pSessblk 	cSess[MAXAPPS + 1];
TEXT		sName[MAX_SERVER_NAME];
TEXT		ProtocolText[24];	/* Protocol Console text */
pVOID 		ntpSession;		/* n-tree Plus base point */
pVOID		ntDllLoadHandle;	/* Load Library Handle use to FreeLibrary on Unload */
NINT		ntpProtocol;		/* n-tree Plus Protocol id */
NINT		ntpShutDown;		/* Server Shutdown indicator */
SEMA		SelectProtect;		/* Select Thread Protect Semaphore */
#ifdef ctPortWIN32
LONG		tlsIndex;		/* TlsAlloc Index to pass to DLL */
#endif
#if defined(ctFeatSSL) && defined(ctCLIENT) || defined(ctLOCLIB)
LONG		sslError;		/* SSL error code */
#endif
#ifdef ctFeatTRANSFER_FILE
#if defined(ctCLIENT) || defined(ctLOCLIB)
NINT		xfrmode;		/* file transfer mode			  */
NINT		xfrinit;		/* file transfer initialization flag	  */
NINT		xfrackn;		/* file transfer acknowledgement interval */
VRLEN		xfrcbsz;		/* client comm buff size before file xfr  */
VRLEN		xfrsbsz;		/* server comm buff size before file xfr  */
#ifdef ctFeatCOPYFILE
LONG8		xfrtotbytes;		/* total bytes to transfer		  */
LONG8		xfrcurbytes;		/* bytes transferred so far		  */
#endif
#endif
#endif
} SrvrGbls, ctMEM * pSrvrGbls, ctMEM * ctMEM * ppSrvrGbls;

/* end from ctcvec.h */
/****************************************************************************/


/****************************************************************************/
/* Prototypes of Communications DLL functions called from server			*/
#ifdef PROTOTYPE
typedef NINT DllLoadDS (*NpInitFuncPtr)(pSrvrGbls pGlobals);
typedef NINT DllLoadDS (*NpStartFuncPtr)(pSrvrGbls pGlobals, pTEXT name, pTEXT comm);
typedef NINT DllLoadDS (*NpMakeFuncPtr)(pSrvrGbls pGlobals, pTEXT name, pULONG handle,
						UCOUNT omode, UCOUNT pmode, ULONG size1, ULONG size2, LONG timeout,
						pTEXT ss);
typedef NINT DllLoadDS (*NpConnectFuncPtr)(pSrvrGbls pGlobals, UCOUNT handle);
typedef NINT DllLoadDS (*NpReadFuncPtr)(pSrvrGbls pGlobals, UCOUNT handle, pMTEXT pMsg1,
						ULONG msg1Len, pMTEXT pMsg2, ULONG msg2Len, pULONG bytesread);
typedef NINT DllLoadDS (*NpDisconnectFuncPtr)(pSrvrGbls pGlobals, UCOUNT handle, NINT mode);
typedef NINT DllLoadDS (*NpWriteFuncPtr)(pSrvrGbls pGlobals, UCOUNT handle, pMTEXT pMsg1,
						ULONG msg1Len, pMTEXT pMsg2, ULONG msg2Len, pULONG byteswritten);
typedef NINT DllLoadDS (*NpSetAttrFuncPtr)(pSrvrGbls pGlobals, UCOUNT handle,
							NINT attribute, pVOID pValue);
typedef NINT DllLoadDS (*NpGetAttrFuncPtr)(pSrvrGbls pGlobals, UCOUNT handle,
						NINT attribute, pVOID pValue);
typedef NINT DllLoadDS (*NpCloseFuncPtr)(pSrvrGbls pGlobals, UCOUNT handle);
typedef NINT DllLoadDS (*NpStopFuncPtr)(pSrvrGbls pGlobals);
typedef NINT DllLoadDS (*NpOpenFuncPtr)(pSrvrGbls pGlobals, pTEXT name, pUCOUNT handle, 
						pUCOUNT action, ULONG size, ULONG attribute, UCOUNT openflag,
						UCOUNT openmode, UNLONG reserved);
typedef VRLEN DllLoadDS (*NpPackSizFuncPtr)(pSrvrGbls pGlobals, VRLEN size, pVRLEN ps_size);
typedef NINT DllLoadDS (*NpPoliceFuncPtr)(pSrvrGbls pGlobals);

#ifdef ctFeatAUTO_SHMEM
typedef VOID DllLoadDS (*CmInitFuncPtr)(pSrvrGbls pGlobals);
typedef NINT DllLoadDS (*CmStartFuncPtr)(pSrvrGbls pGlobals, pTEXT name);
typedef NINT DllLoadDS (*CmMakeFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession);
typedef NINT DllLoadDS (*CmConnectFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession);
typedef NINT DllLoadDS (*CmReadFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession, pMTEXT pMsg1,
						ULONG msg1Len, pMTEXT pMsg2, ULONG msg2Len, pULONG bytesread);
typedef NINT DllLoadDS (*CmDisconnectFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession);
typedef NINT DllLoadDS (*CmWriteFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession, pMTEXT pMsg1,
						ULONG msg1Len, pMTEXT pMsg2, ULONG msg2Len, pULONG byteswritten);
typedef NINT DllLoadDS (*CmSetAttrFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession,
							NINT attribute, pVOID pValue);
typedef VOID DllLoadDS (*CmCloseFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession);
typedef VOID DllLoadDS (*CmStopFuncPtr)(pSrvrGbls pGlobals);
typedef NINT DllLoadDS (*CmOpenFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession);
typedef NINT DllLoadDS (*CmPoliceFuncPtr)(pSrvrGbls pGlobals);
typedef VOID DllLoadDS (*CmDisposeFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession);
typedef UINT DllLoadDS (*CmNewFuncPtr)(pSrvrGbls pGlobals, UCOUNT cmdSize, pTEXT pServerName, ULONG attributes,
				       UCOUNT theSrvId, UCOUNT recTimeOut, UCOUNT sndTimeOut);
typedef pSessblk DllLoadDS (*CmValidFuncPtr)(pSrvrGbls pGlobals, UCOUNT handle);
#endif

#else	/* ~PROTOTYPE */

typedef NINT DllLoadDS (*NpInitFuncPtr)();
typedef NINT DllLoadDS (*NpStartFuncPtr)();
typedef NINT DllLoadDS (*NpMakeFuncPtr)();
typedef NINT DllLoadDS (*NpConnectFuncPtr)();
typedef NINT DllLoadDS (*NpReadFuncPtr)();
typedef NINT DllLoadDS (*NpDisconnectFuncPtr)();
typedef NINT DllLoadDS (*NpWriteFuncPtr)();
typedef NINT DllLoadDS (*NpSetAttrFuncPtr)();
typedef NINT DllLoadDS (*NpGetAttrFuncPtr)();
typedef NINT DllLoadDS (*NpCloseFuncPtr)();
typedef NINT DllLoadDS (*NpStopFuncPtr)();
typedef NINT DllLoadDS (*NpOpenFuncPtr)();
typedef VRLEN DllLoadDS (*NpPackSizFuncPtr)();
typedef NINT DllLoadDS (*NpPoliceFuncPtr)();

#ifdef ctFeatAUTO_SHMEM
typedef NINT DllLoadDS (*CmInitFuncPtr)();
typedef NINT DllLoadDS (*CmStartFuncPtr)();
typedef NINT DllLoadDS (*CmMakeFuncPtr)();
typedef NINT DllLoadDS (*CmConnectFuncPtr)();
typedef NINT DllLoadDS (*CmReadFuncPtr)();
typedef NINT DllLoadDS (*CmDisconnectFuncPtr)();
typedef NINT DllLoadDS (*CmWriteFuncPtr)();
typedef NINT DllLoadDS (*CmSetAttrFuncPtr)();
typedef NINT DllLoadDS (*CmCloseFuncPtr)();
typedef NINT DllLoadDS (*CmStopFuncPtr)();
typedef NINT DllLoadDS (*CmOpenFuncPtr)();
typedef NINT DllLoadDS (*CmPoliceFuncPtr)();
typedef VOID DllLoadDS (*CmDisposeFuncPtr)();
typedef UINT DllLoadDS (*CmNewFuncPtr)();
typedef pSessblk DllLoadDS (*CmValidFuncPtr)();
#endif

#endif 	/* ~PROTOTYPE */


typedef struct CommFuncStruct {
NpInitFuncPtr 		NpINIT;
NpStartFuncPtr 		NpSTART;
NpStopFuncPtr		NpSTOP;
NpMakeFuncPtr 		NpMAKE;
NpConnectFuncPtr	NpCONNECT;
NpDisconnectFuncPtr	NpDISCONNECT;
NpReadFuncPtr		NpREAD;
NpWriteFuncPtr		NpWRITE;
NpSetAttrFuncPtr	NpSETATTR;
NpGetAttrFuncPtr	NpGETATTR;
NpOpenFuncPtr		NpOPEN;
NpCloseFuncPtr		NpCLOSE;
NpPackSizFuncPtr	NpPACKSIZ;
NpPoliceFuncPtr		NpPOLICE;
} CommFuncPtrs, ctMEM *pCommFuncPtrs;

#ifdef ctFeatAUTO_SHMEM
typedef struct CmFuncStruct {
CmInitFuncPtr 		CmINIT;
CmStartFuncPtr 		CmSTART;
CmStopFuncPtr		CmSTOP;
CmMakeFuncPtr 		CmMAKE;
CmConnectFuncPtr	CmCONNECT;
CmDisconnectFuncPtr	CmDISCONNECT;
CmReadFuncPtr		CmREAD;
CmWriteFuncPtr		CmWRITE;
CmSetAttrFuncPtr	CmSETATTR;
CmOpenFuncPtr		CmOPEN;
CmCloseFuncPtr		CmCLOSE;
CmPoliceFuncPtr		CmPOLICE;
CmDisposeFuncPtr	CmDISPOSE;
CmNewFuncPtr		CmNEW;
CmValidFuncPtr		CmVALID;
} CmFuncPtrs, ctMEM *pCmFuncPtrs;
#endif

/****************************************************************************/

/****************************************************************************/
/* Prototypes of server functions that will be called from communications DLL */
#ifdef PROTOTYPE
typedef NINT DllLoadDS  (*SvDeferFuncPtr)(LONG);
typedef NINT DllLoadDS  (*SvCttcreFuncPtr)(pNINT ,NINT (*)(VOID ),UINT ,NLONG );

#ifdef ctDBGSEMCNT
typedef NINT DllLoadDS  (*SvBlkrqsFuncPtr)(pSEMAblk sema,LONG wait,NINT own,NINT loc);
typedef NINT DllLoadDS 	(*SvBlkwatFuncPtr)(pSEMAblk sema,LONG wait,NINT own,NINT loc);
#else
typedef NINT DllLoadDS  (*SvBlkrqsFuncPtr)(pSEMAblk sema,LONG wait,NINT own);
typedef NINT DllLoadDS 	(*SvBlkwatFuncPtr)(pSEMAblk sema,LONG wait,NINT own);
#endif
typedef NINT DllLoadDS  (*SvBlkclrFuncPtr)(pSEMAblk sema,NINT own);

#ifdef ctDBGSEMCNT
typedef NINT DllLoadDS 	(*SvSemRqsFuncPtr)(pSEMA sema,LONG wait,NINT own,NINT loc);
#else
typedef NINT DllLoadDS 	(*SvSemRqsFuncPtr)(pSEMA sema,LONG wait,NINT own);
#endif
typedef NINT DllLoadDS 	(*SvSemClrFuncPtr)(pSEMA sema,NINT own);
typedef NINT DllLoadDS 	(*SvSemWatFuncPtr)(pSEMA sema, LONG wait, NINT own);

#ifdef ctDBGSEMCNT
typedef NINT DllLoadDS 	(*SvTimRqsFuncPtr)(pSEMAtim sema,LONG wait,NINT own,NINT loc);
#else
typedef NINT DllLoadDS 	(*SvTimRqsFuncPtr)(pSEMAtim sema,LONG wait,NINT own);
#endif
typedef NINT DllLoadDS 	(*SvTimClrFuncPtr)(pSEMAtim sema,NINT own);
#ifdef ctDBGSEMCNT
typedef NINT DllLoadDS 	(*SvTimWatFuncPtr)(pSEMAtim sema, LONG wait, NINT own,NINT loc);
#else
typedef NINT DllLoadDS  (*SvTimWatFuncPtr)(pSEMAtim sema, LONG wait, NINT own);
#endif

typedef pTEXT       	(*SvMballcFuncPtr)(NINT numobj,UINT sizobj);
typedef VOID        	(*SvMbfreeFuncPtr)(pVOID objptr);
typedef pTEXT       	(*SvGetMemFuncPtr)(VRLEN iosize);
typedef VOID        	(*SvPutMemFuncPtr)(pTEXT loc);

typedef NINT    	(*SvWaitWhileFuncPtr)(pCOUNT F, LONG delay);
typedef VOID DllLoadDS 	(*SvRevObjFuncPtr)(pVOID pData, NINT size);
typedef NINT 		(*SvUsrStatFuncPtr)(NINT own);

typedef	NLONG DllLoadDS (*SvGetSrVarFuncPtr)(NINT this_var);
typedef LONG 		(*SvPrintfFuncPtr)(pTEXT p);

typedef NINT 		(*SvGetActvStatusFuncPtr)(NINT sOWNR);
typedef NINT 		(*SvSetInactiveFuncPtr)(NINT sOWNR,NINT chkstt);

typedef VOID		(*SvLogErrFuncPtr)(pSrvrGbls pGlobals, pSessblk pSession, pTEXT pMsg1, ULONG msg1Len, pTEXT pMsg2, ULONG msg2Len);
typedef NINT 		(*SvUserAliveFuncPtr)(NINT chkcomm);

#else 	/* ~PROTOTYPE */

typedef NINT DllLoadDS  (*SvDeferFuncPtr)();
typedef NINT DllLoadDS  (*SvCttcreFuncPtr)();

typedef NINT DllLoadDS  (*SvBlkrqsFuncPtr)();
typedef NINT DllLoadDS  (*SvBlkclrFuncPtr)();
typedef NINT DllLoadDS  (*SvBlkwatFuncPtr)();

typedef NINT DllLoadDS 	(*SvSemRqsFuncPtr)();
typedef NINT DllLoadDS 	(*SvSemClrFuncPtr)();
typedef NINT DllLoadDS 	(*SvSemWatFuncPtr)();

typedef NINT DllLoadDS 	(*SvTimRqsFuncPtr)();
typedef NINT DllLoadDS 	(*SvTimClrFuncPtr)();
typedef NINT DllLoadDS 	(*SvTimWatFuncPtr)();

typedef pTEXT       	(*SvMballcFuncPtr)();
typedef VOID        	(*SvMbfreeFuncPtr)();
typedef pTEXT       	(*SvGetMemFuncPtr)();
typedef VOID        	(*SvPutMemFuncPtr)();

typedef NINT    	(*SvWaitWhileFuncPtr)();
typedef VOID DllLoadDS 	(*SvRevObjFuncPtr)();
typedef NINT 		(*SvUsrStatFuncPtr)();

typedef	NLONG DllLoadDS (*SvGetSrVarFuncPtr)();
typedef LONG 		(*SvPrintfFuncPtr)();

typedef VOID		(*SvLogErrFuncPtr)();
typedef NINT 		(*SvUserAliveFuncPtr)();

#endif 	/* ~PROTOTYPE */

typedef struct SrvrFuncStruct {
SvDeferFuncPtr		SvDEFER;
SvCttcreFuncPtr		SvCTTCRE;

SvBlkrqsFuncPtr		SvBLKRQS;
SvBlkclrFuncPtr		SvBLKCLR;
SvBlkwatFuncPtr		SvBLKWAT;

SvSemRqsFuncPtr		SvSEMRQS;
SvSemClrFuncPtr		SvSEMCLR;
SvSemWatFuncPtr		SvSEMWAT;

SvTimRqsFuncPtr		SvTIMRQS;
SvTimClrFuncPtr		SvTIMCLR;
SvTimWatFuncPtr		SvTIMWAT;

SvMballcFuncPtr		SvMBALLC;
SvMbfreeFuncPtr		SvMBFREE;

SvGetMemFuncPtr		SvGETMEM;
SvPutMemFuncPtr		SvPUTMEM;

SvWaitWhileFuncPtr 	SvWAITWHILE;
SvRevObjFuncPtr		SvREVOBJ;
SvUsrStatFuncPtr	SvUSRSTAT;

SvGetSrVarFuncPtr 	SvGETSRVAR;
SvPrintfFuncPtr		SvPRINTF;

SvSetInactiveFuncPtr	SvSetInactive;
SvGetActvStatusFuncPtr	SvGetActvStatus;

SvLogErrFuncPtr		SvLOGERR;
SvUserAliveFuncPtr	SvUserAlive;

} SrvrFuncPtrs, ctMEM *pSrvrFuncPtrs;
/****************************************************************************/
#ifdef PROTOTYPE
typedef pCommFuncPtrs DllExport DllLoadDS (ctDllDecl *NpGlobalsFuncPtr)(pSrvrGbls psg);
#else																	
typedef pCommFuncPtrs DllExport DllLoadDS (ctDllDecl *NpGlobalsFuncPtr)();
#endif
/****************************************************************************/

/****************************************************************************/

#ifdef NO_BOUND

#define LQMSG_RSVD_DOSVIMP	0x00000001	/* doserver() impersonate */

typedef struct lqmsg {
	VRLEN	lmlen[OUTSEG]; /* Protocol Byte Box */
	pMTEXT	lctusrbuf;
	pCommFuncPtrs lcommcmds;
	pUGRUP  lgptr;
	SEMA	lclnt;
	SEMA	lsrvr;
	LONG	lcpid;	/* communications protocol id */
	LONG	lupid;
	LONG	lmemu;
	LONG	lattr;
	LONG	lrsv1;
	LONG	lrsv2;
	VRLEN	lsize;
	COUNT	lerrc;
	COUNT	lmode;
	COUNT	lslct;
	UCOUNT	lhdl;
	UCOUNT	lrsvd;
	COUNT	ltask;
	UTEXT	lflvr;
	UTEXT	lalgn;
	TEXT	lusid[IDZ];
	TEXT	luswd[PWZ];
} LQMSG;

#ifdef ctFeatPWDLEN
typedef struct lqmsgx {
	VRLEN	lmlen[OUTSEG]; /* Protocol Byte Box */
	pMTEXT	lctusrbuf;
	pCommFuncPtrs lcommcmds;
	pUGRUP  lgptr;
	SEMA	lclnt;
	SEMA	lsrvr;
	LONG	lcpid;	/* communications protocol id */
	LONG	lupid;
	LONG	lmemu;
	LONG	lattr;
	LONG	lrsv1;
	LONG	lrsv2;
	VRLEN	lsize;
	COUNT	lerrc;
	COUNT	lmode;
	COUNT	lslct;
	UCOUNT	lhdl;
	UCOUNT	lrsvd;
	COUNT	ltask;
	UTEXT	lflvr;
	UTEXT	lalgn;
	TEXT	lusid[IDZ];
	TEXT	luswd[PWZX];
} LQMSGX;
#endif

#ifdef ctPortUNIX
typedef struct lqmsg_shm {
	VRLEN	lmlen[OUTSEG]; /* Protocol Byte Box */
	pMTEXT	lctusrbuf;
#ifndef ct8P
	LONG	lctusrbufpad;
#endif
	pCommFuncPtrs lcommcmds;
#ifndef ct8P
	LONG	lcommcmdspad;
#endif
	pUGRUP  lgptr;
#ifndef ct8P
	LONG	lgptrpad;
#endif
	LONG8	lclntpid;
	LONG8	lsrvruid;
	LONG	lcpid;	/* communications protocol id */
	LONG	lupid;
	LONG	lmemu;
	LONG	lattr;
	LONG8	lrsv1;
	LONG8	lrsv2;
	VRLEN	lsize;
	COUNT	lclnt;
	COUNT	lsrvr;
	COUNT	lerrc;
	COUNT	lmode;
	COUNT	lslct;
	UCOUNT	lhdl;
	UCOUNT	lrsvd;
	COUNT	ltask;
	UTEXT	lflvr;
	UTEXT	lalgn;
	TEXT	lusid[IDZ];
	TEXT	luswd[PWZ];
} LQMSG_SHM, *pLQMSG_SHM;
#endif

typedef struct {
	VRLEN	lmlen[OUTSEG];
	TEXT	lctusrbuf[4];
	TEXT	rab_xx_lcommcmds[4];
	TEXT	lgptr[4];
	TEXT	lclnt[8];
	TEXT	lsrvr[8];
	LONG	lcpid;	/* communications protocol id */
	LONG	lupid;
	LONG	lmemu;
	LONG	lattr;
	LONG	lrsv1;
	LONG	lrsv2;
	VRLEN	lsize;
	COUNT	lerrc;
	COUNT	lmode;
	COUNT	lslct;
	UCOUNT	lhdl;
	UCOUNT	lrsvd;
	COUNT	ltask;
	UTEXT	lflvr;
	UTEXT	lalgn;
	TEXT	lusid[IDZ];
	TEXT	luswd[PWZ];
} LOGON_REQUEST, ctMEM *pLOGON_REQUEST;


/*
** Attributes specified by client in LOGON_REQUEST's lattr field:
*/
#define ctLOGREQAttrCLIENTID	0x00000001	/* Client supports client ID info */
#define ctLOGREQAttrSSL		0x00000002	/* Client requests SSL connection */

/*
** Client Side Attribute - LCBYT extras used in special handsshake logic 
*/
#define ctLCBYTAttrENTGUITOOLS	((LONG)0x00000001) /* Enterprise GUI Tool Client   */
#define ctLCBYTAttrSHMEMspin	((LONG)0x00000002) /* Shared memory spin loop support */
#define ctLCBYTAttrDARdisabled	((LONG)0x00000004) /* DAR support is disabled */
#define ctLCBYTAttrPWDSEC	((LONG)0x00000008) /* Enhanced password security support */
#define ctLCBYTAttrPWDLEN	((LONG)0x00000010) /* Long password: FC_USER version 3 */
#define ctLCBYTAttrA3_TRNFIL	((LONG)0x00000020) /* A3_TRNFIL supported     */
#define ctLCBYTAttrNOISMKEYUPD	((LONG)0x00000040) /* Supports no ISAM key update feature */
#define ctLCBYTAttrREPLFULLNAME	((LONG)0x00000080) /* Replication: return full filename from source server */
#define ctLCBYTAttrXTDFLDTYP	((LONG)0x00000100) /* Supports extended data type range */
#define ctLCBYTAttrFCSMBODBC	((LONG)0x00000200) /* FairCom ODBC Driver */
#define ctLCBYTAttrDFRIDX	((LONG)0x00000400) /* Supports deferred index feature */
#define ctLCBYTAttrREPLQUIET	((LONG)0x00000800) /* Replication: responsd to ctQUIET() request */
#define ctLCBYTAttrSHMEMspin2	((LONG)0x00001000) /* Shared memory spin loop support version 2 */
#define ctLCBYTAttrREPLCVTSUBST ((LONG)0x00002000) /* Replication: filename from source server with SUBST converted to actual path */
#define ctLCBYTAttrSYSQUE2	((LONG)0x00004000) /* Client uses new sysque marshalling */
#define ctLCBYTAttrWRITEALLOWED	((LONG)0x00008000) /* Connection can write to read-only server */
#define ctLCBYTAttrPKEYREQ2_V	((LONG)0x00010000) /* client supports PKEYREQ2 with verion marshalling*/
#define ctLCBYTAttrMAXFILE32	((LONG)0x00020000) /* Client library supports 4-byte file numbers */
#define ctLCBYTAttrFCTHREADS	((LONG)0x00040000) /* FairCom threads enabled */

/*
** Server Attributes
*/
#define ctSRBYTAttrSHMEMspin	((LONG)0x00000001) /* Shared memory spin loop support */
#define ctSRBYTAttrNEWtfilno	((LONG)0x00000002) /* Server supports new rebuild/compact tfilno options */
#define ctSRBYTAttrDARdisabled	((LONG)0x00000004) /* Server does not support DAR feature */
#define ctSRBYTAttrPWDSEC	((LONG)0x00000008) /* Enhanced password security support */
#define ctSRBYTAttrPWDLEN	((LONG)0x00000010) /* Long password: FC_USER version 3 */
#define ctSRBYTAttrMSTHSH	((LONG)0x00000020) /* Master server password hash */
#define ctSRBYTAttrA3_TRNFIL	((LONG)0x00000040) /* A3_TRNFIL supported     */
#define ctSRBYTAttrCNVT38	((LONG)0x00000080) /* CNVT38 supported        */
#define ctSRBYTAttrXTDFLDTYP	((LONG)0x00000100) /* Supports extended data type range */
#define ctSRBYTAttrALCRNGX	((LONG)0x00000200) /* Supports ALCRNG extended operator range */
#define ctSRBYTAttrSHMEMspin2	((LONG)0x00000400) /* Shared memory spin loop support version 2 */
#define ctSRBYTAttrSUPHSTcofile	((LONG)0x00000800) /* Can set superfile host file number */
#define ctSRBYTAttrREPLchgbcmp	((LONG)0x00001000) /* Server checks for compatible replication change buffer version */
#define ctSRBYTAttrPWDEXP	((LONG)0x00002000) /* Server supports password expiration */
#define ctSRBYTAttrKSEGDEFxtd	((LONG)0x00004000) /* Server supports extended key definition enhancements */
#define ctSRBYTAttrSYSQUE2	((LONG)0x00008000) /* Server uses new sysque marshalling */
#define ctSRBYTAttrPKEYREQ2	((LONG)0x00010000) /* Server supports pKEYREQ2 in batch calls */
#define ctSRBYTAttrHasDevProd	((LONG)0x00020000) /* Server returns its development/production license status in ctSRBYTAttrIsProdSrvr bit */
#define ctSRBYTAttrIsProdSrvr	((LONG)0x00040000) /* If ctSRBYTAttrHasDevProd bit is set, this bit is 0 for a development server or 1 for a production server */
#define ctSRBYTAttrSyncRepl	((LONG)0x00080000) /* Server supports synchronous replication enhancements */
#define ctSRBYTAttrOPS_LOCKON_ADD_BLK ((LONG)0x00100000) /* Server supports OPS_LOCKON_ADD_BLK SETOPS() mode */
#define ctSRBYTAttrPKEYREQ2_V	((LONG)0x00200000) /* Server supports PKEYREQ2 with verion marshalling */
#define ctSRBYTAttrOPS_LOCKON_GET_BLKRQS ((LONG)0x00400000) /* Server supports OPS_LOCKON_GET_BLKRQS SETOPS() mode */
#define ctSRBYTAttrLOKREC_ENABLE_BLKRQS ((LONG)0x00800000) /* Server supports ctENABLE_BLKRQS LOKREC() mode */
#define ctSRBYTAttrMAXFILE32	((LONG)0x01000000) /* Server supports 4-byte file numbers */

typedef struct lqmsg2 {
	TEXT	lnodname[IDZ];
	TEXT	ltickle;
	UTEXT	lpntr;
	UTEXT	lcbyt;	/* client ID byte */
	UTEXT	lrsv2;
	VRLEN	lhugflg;
	VRLEN	lreqsiz;
	VRLEN	lrspsiz;
	VRLEN	linpoff;
	VRLEN	loutoff;
	ULONG	lcbytatr; /* client Attributes - see ctLCBYTAttr above for bit settings */
	UTEXT	lrcbvern; /* replication change buffer version */
	UTEXT	rtgdrv; /* RTG driver "flavor" ctPortRTG*/
	TEXT	pad[66];
} LQMSG2;

typedef struct lqrsp {
	LONG	divs;
	LONG	nusers;
	UTEXT	sflvr[8];
	UCOUNT	sndTimeOut;
	UCOUNT	recTimeOut;
	ULONG	srbytatr; /* server Attributes - see ctSRBYTAttr above for bit settings */
	UTEXT	pad[104];
} LQRSP;

#ifdef ctSP
typedef LQMSG far   *	pLQMSG;
typedef LQMSG2 far   *	pLQMSG2;
typedef LQRSP far   *	pLQRSP;
#else
typedef LQMSG ctMEM *	pLQMSG;
typedef LQMSG2 ctMEM *	pLQMSG2;
typedef LQRSP ctMEM *	pLQRSP;
#endif

#ifdef ctPortVINESSEC
typedef struct stmsg {
	TEXT	susid[IDZ];
	TEXT	sgrp[IDZ];
	IPCPORT sport;
	ULONG	sstamp;
	ULONG	sdate;
	TEXT	sserver[6];
	TEXT	sfiller[2];
} STMSG;

#ifdef ctSP
typedef STMSG far   *	pSTMSG;
#else
typedef STMSG ctMEM *	pSTMSG;
#endif

#endif /* ctPortVINESSEC */

#endif /* NO_BOUND */

#define	PutMessage	1
#define ctGetMessage	2
#define FnlMessage	3

#define DataTerminated		0x000001L
#define EndOfMessage		0x000002L
#define MustSendNow			0x000004L
#define RefIsMemory			0x000008L
#define MustBeData			0x000010L
#define WaitForCompletion	0x000020L
#define RefIsUnused			0x000040L

#define WaitEverPeekShtdwn (-31939) /* Unused unique value */

/*
** If the string that is passed to ctNPctrt_printf() specifies the following
** special value as its first byte, the string is written to CTSTATUS.FCS
** only. Otherwise the string is written to CTSTATUS.FCS and to standard
** output.
*/
#define NP_PRINTLOG '\x01'

/****************************************************************************/
#define gSrvSema			pGlobals->srvSema
/*#define gIsWNE			pGlobals->isWNE */
/*#define gNewAT			pGlobals->newat */
#define gSignature			pGlobals->signature
#define gNbrSessions			pGlobals->nbrSessions
#define gMaxPacketSize			pGlobals->maxPacketSize
#define gSSess				pGlobals->sSess
#define gCSess				pGlobals->cSess
#define gCmds				(pGlobals->com_cmds)
#define gCmds2				pGlobals->com_cmds
#define gSName 				pGlobals->sName 
#define gCallBackCmds 			(pGlobals->srv_callBackCmds)
#define gCallBackCmds2 			pGlobals->srv_callBackCmds
#define ghSrvrGlobalData 		pGlobals->hServerGlobalData
#define gntpSession 		    	pGlobals->ntpSession
#define gntDllLoadHandle		pGlobals->ntDllLoadHandle
#define gntProtocolText			pGlobals->ProtocolText
#define gntShutDown			pGlobals->ntpShutDown
/****************************************************************************/

/* Network I/O Locations */
/****************/
#define ctNET_IO_APPX_WRITE   ((NpWriteFuncPtr)(*(ctlqmsg->lcommcmds->NpWRITE)))
#define ctNET_IO_TRAP_WRITE   (*(lqmsg.lcommcmds->NpWRITE))
#define ctNET_IO_APPX_READ    ((NpReadFuncPtr)(*(ctlqmsg->lcommcmds->NpREAD)))
#define ctNET_IO_TRAP_READ    ((NpReadFuncPtr)(*(lqmsg.lcommcmds->NpREAD)))
#define ctNET_IO_APPX_CLOSE   ((NpCloseFuncPtr)(*(lcommcmds->NpCLOSE)))
#define ctNET_IO_APPX_START   ((NpStartFuncPtr)(*(pLqMsg->lcommcmds->NpSTART)))
#define ctNET_IO_APPX_OPEN    ((NpOpenFuncPtr)(*(pLqMsg->lcommcmds->NpOPEN)))
#define ctNET_IO_APPX_PACKSIZ ((NpPackSizFuncPtr)(*(pLqMsg->lcommcmds->NpPACKSIZ)))
#define ctNET_IO_APPX_WRITE2  ((NpWriteFuncPtr)(*(pLqMsg->lcommcmds->NpWRITE)))
#define ctNET_IO_APPX_READ2   ((NpReadFuncPtr)(*(pLqMsg->lcommcmds->NpREAD)))
#define ctNET_IO_APPX_WRITE3  ((NpWriteFuncPtr)(*(pLqMsg->lcommcmds->NpWRITE)))
#define ctNET_IO_APPX_READ3   ((NpReadFuncPtr)(*(pLqMsg->lcommcmds->NpREAD)))
#define ctNET_IO_APPX_GETATTR ((NpGetAttrFuncPtr)(*(pLqMsg->lcommcmds->NpGETATTR)))
#define ctNET_IO_APPX_SETATTR ((NpSetAttrFuncPtr)(*(pLqMsg->lcommcmds->NpSETATTR)))
#define ctNET_IO_APPX_GETATTR2 ((NpGetAttrFuncPtr)(*(pLqMsg->lcommcmds->NpGETATTR)))
#define ctNET_IO_APPX_SETATTR2 ((NpSetAttrFuncPtr)(*(pLqMsg->lcommcmds->NpSETATTR)))
/****************/

/****************/
#define ctNET_IO_LGON_WRITE		(*(l->lcommcmds->NpWRITE))
#define ctNET_IO_LGON_MAKE		(*(lcommcmds->NpMAKE))
#define ctNET_IO_LGON_CONNECT		(*(lcommcmds->NpCONNECT))
#define ctNET_IO_LGON_READ		(*(lcommcmds->NpREAD))
#define ctNET_IO_LGON_DISCONN		(*(lcommcmds->NpDISCONNECT))
#define ctNET_IO_LGON_READ2		(*(lcommcmds->NpREAD))
#define ctNET_IO_LGON_SETATTR		(*(lcommcmds->NpSETATTR))
#define ctNET_IO_LGON_WRITE2		(*(lcommcmds->NpWRITE))
#define ctNET_IO_LGON_DISCONN2		(*(lcommcmds->NpDISCONNECT))
#define ctNET_IO_TRAN_DISCONN		(*(lcommcmds->NpDISCONNECT))
/****************/

/****************/
#define ctNET_IO_NTIO_WRITE		(*(lqp->lcommcmds->NpWRITE))
#define ctNET_IO_NTIO_READ		(*(lqp->lcommcmds->NpREAD))
/****************/

/****************/
#define ctNET_IO_SUSR_DISCONN	   	(*(lqp->lcommcmds->NpDISCONNECT))
/****************/

/****************/
#define ctNET_IO_SRVR_START		(*commCmds[i]->NpSTART) 
/****************/

/****************/
#define ctNET_IO_ASUP_INIT		(*(cfp->NpINIT))
#define ctNET_IO_ASUP_STOP		(*(lcommcmds->NpSTOP))
#define ctNET_IO_ASUP_PACKSIZ		(*(ctlqmsg->lcommcmds->NpPACKSIZ))
/****************/

/****************/
#define ctNET_IO_SSUP_INIT		(*(cfp->NpINIT))
#define ctNET_IO_SSUP_STOP		(*(lcommcmds->NpSTOP))
#define ctNET_IO_SSUP_POLICE		(*(cfp->NpPOLICE))
/****************/					

/****************/					
#define ctNET_IO_CATEND_DISCONN		(*(cfp->NpDISCONNECT))
/****************/					


enum RemoteInfo
{
	INFO_REMOTE_PID,
	INFO_REMOTE_TID,
	INFO_REMOTE_UID,
	INFO_REMOTE_INVALID
};
#ifdef __cplusplus
extern "C" {
#endif
LONG GetRemoteInfo(pSessblk, enum RemoteInfo);
#ifdef ctFeatIPv6
ctADDR_T * GetHostAddress(const TEXT * pHostName, ctADDR_T * addr);
#endif
ULONG GetHostAddressV4(const TEXT * pHostName);
pTEXT ct_inet_ntop(NINT family, pVOID addptr, pTEXT strptr, size_t len);
#ifdef __cplusplus
}
#endif
/****************************************************************************/
#endif /* ctCOMMH */

/* end of ctcomm.h */
