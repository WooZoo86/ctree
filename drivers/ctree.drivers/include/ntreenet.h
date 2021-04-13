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
*   NTREENET.H
*	
*   This is the internal header file for the NetBios protocol. 
*	It automatically includes NTREELIB.H and is used by all modules
*	in the library. Uses should not include this module since it is
*   used internally by NTREE.
*
***********************************************************************/

#ifndef _NTREENET_INCLUDED
#define _NTREENET_INCLUDED

#include "ntreestd.h"

#ifdef ntNET

#define NCB_NAME_SIZE		16
#define NCB_MAX_SESSIONS	2
#define NCB_MAX_NCBS		4
#define NCB_MAX_NAMES		2
#define NCB_MAX_SEND		0xffffL

#ifdef ntWIN32
#define WIN32_MEAN_AND_LEAN
#include <windows.h>
#define ntNetbios(n)		Netbios(n)
#endif

#ifdef ntOS2

#define NCBNAMSZ		NCB_NAME_SIZE

typedef UTEXT * _Seg16	pBUFFER;
typedef struct _CMD_NCB	NCB;
typedef struct _RESET_NCB RESET_NCB;
typedef NCB*			pNCB;
typedef RESET_NCB*		pRESET_NCB;

typedef struct _CMD_NCB {
    UTEXT   ncb_command;            /* command code                   */
    UTEXT   ncb_retcode;            /* return code                    */
    UTEXT   ncb_lsn;                /* local session number           */
    UTEXT   ncb_num;                /* number of our network name     */
    pBUFFER	ncb_buffer;             /* address of message buffer      */
    UCOUNT	ncb_length;             /* size of message buffer         */
    UTEXT   ncb_callname[NCBNAMSZ]; /* blank-padded name of remote    */
    UTEXT   ncb_name[NCBNAMSZ];     /* our blank-padded netname       */
    UTEXT   ncb_rto;                /* rcv timeout/retry count        */
    UTEXT   ncb_sto;                /* send timeout/sys timeout       */
    pBUFFER	ncb_post;				/* POST routine address        */
    UTEXT   ncb_lana_num;           /* lana (adapter) number          */
    UTEXT   ncb_cmd_cplt;           /* 0xff => commmand pending       */
    UTEXT   ncb_reserve[14];        /* reserved, used by BIOS         */
};

struct _RESET_NCB
{
	UTEXT	ncb_command;
	UTEXT	ncb_retcode;
	UTEXT	ncb_lsn;
	UTEXT	ncb_num;
	pBUFFER	ncb_name_address;
	UCOUNT	ncb_length;
	UTEXT	ncb_req_sessions;
	UTEXT	ncb_req_commands;
	UTEXT	ncb_req_names;
	UTEXT	ncb_req_name_one;
	UTEXT	ncb_not_used1[ 12 ];
	UTEXT	ncb_act_sessions;
	UTEXT	ncb_act_commands;
	UTEXT	ncb_act_names;
	UTEXT	ncb_act_name_one;
	UTEXT	ncb_not_used2[ 4 ];
	UTEXT	ncb_load_session;
	UTEXT	ncb_load_commands;
	UTEXT	ncb_load_names;
	UTEXT	ncb_load_stations;
	UTEXT	ncb_not_used3[ 2 ];
	UTEXT	ncb_load_remote_names;
	UTEXT	ncb_not_used4[ 5 ];
	UCOUNT	ncb_id;
	UTEXT	ncb_lana_num;
	UTEXT	ncb_not_used5;
	UTEXT	ncb_reserved[ 14 ];
};

#define ntNetbios(n)	NETBIOS(n)

extern unsigned NETBIOS( NCB* );
#pragma linkage(NETBIOS, far16 pascal)

#endif /* ntOS2 */

#define NCB_SIZE			sizeof( NCB )

typedef struct tagNETBIOS	_NETBIOS;

typedef _NETBIOS ntFAR*		pNETBIOS;

#ifdef ntWIN
typedef NCB ntFAR*			pNCB;
#endif

struct tagNETBIOS
{
	pCONNECTION Connection;
	UTEXT	Netlana;
	UTEXT	Netlsn;
	UTEXT	Server[ NCB_NAME_SIZE + 1 ];
	UTEXT	Client[ NCB_NAME_SIZE + 1 ];
	LONG	BytesToRecv;
	NCB		Ncb;
	NINT	Mode;
};

#define NCB_NOWAIT			0x80

#define NCB_CALL			0x10
#define NCB_LISTEN			0x11
#define NCB_HANGUP			0x12
#define NCB_SEND			0x14
#define NCB_RECV			0x15
#define NCB_ADD_NAME		0x30
#define NCB_DEL_NAME		0x31
#define NCB_RESET			0x32
#define NCB_CANCEL			0x35

#define NCBERR_NONE			0
#define NCBERR_PENDING		0xff
#define NCBERR_ERROR		-1
#define NCBERR_INTERRUPTED	-2
#define NCBERR_DUPNAME		0x0d

#ifdef PROTOTYPE

NINT ntDECL ntNetCleanUp( pCONNECTION Connection );
NINT ntDECL ntNetOpen( pCONNECTION Connection );
NINT ntDECL ntNetCancel( pCONNECTION Connection );
NINT ntDECL ntNetClose( pCONNECTION Connection );
NINT ntDECL ntNetShutdown( pCONNECTION Connection );
NINT ntDECL ntNetSend( pCONNECTION Connection, pVOID Buffer, LONG BytesToSend, pLONG BytesSent );
NINT ntDECL ntNetSendVector( pCONNECTION Connection, pVECTOR Vector, NINT VectorCount, pLONG BytesSent );
NINT ntDECL ntNetReceive( pCONNECTION Connection, pVOID Buffer, LONG BufferSize, pLONG BytesReceived );
NINT ntDECL ntNetReadVector( pCONNECTION Connection, pVECTOR Vector, NINT VectorCount, pLONG BytesReceived );
NINT ntDECL ntNetSetOption( pCONNECTION Connection, NINT Option, LONG Value );
NINT ntDECL ntNetGetOption( pCONNECTION Connection, NINT Option, pLONG Value );

#else  /* PROTOTYPE */

NINT ntDECL ntNetCleanUp();
NINT ntDECL ntNetOpen();
NINT ntDECL ntNetCancel();
NINT ntDECL ntNetClose();
NINT ntDECL ntNetShutdown();
NINT ntDECL ntNetSend();
NINT ntDECL ntNetSendVector();
NINT ntDECL ntNetReceive();
NINT ntDECL ntNetReadVector();
NINT ntDECL ntNetSetOption();
NINT ntDECL ntNetGetOption();

#endif /* PROTOTYPE */

#endif	/* ntNET */

#endif	/* _NTREENET_INCLUDED */
