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
*	@module NTREESPX.H |
*   This is the internal header file for NTREE SPX portable function
*	calls.
*
***********************************************************************/

#ifndef	_NTSIPX32_INCLUDED
#define _NTSIPX32_INCLUDED

#include <ntypes.h>
#include <nwsipx32.h>

typedef struct _NTSPX	NTSPX;
typedef NTSPX ntFAR*	pNTSPX;

struct _NTSPX
{
	pTEXT				Name;
	UCOUNT				Type;
	YESNO				IsServer;
	UCOUNT				Socket;
	UCOUNT				SeqNbr;
	SIPXSOCK_HANDLE		hSocket;
	SIPXCONN_HANDLE		hConn;
	SIPX_SERVICE_INFO	ServerInfo;
	SIPXMUXGRP_HANDLE	hMuxGroup;
	PNWTCB				pTcb;
	PNWTCB				pRecvTcb;
	PNWTCB				pList;
	PNWTCB				pTxTcb[ SPX_MAX_TXTCB ];
	PNWTCB				pRxTcb[ SPX_MAX_RXTCB ];
	FRAGMENT			TxFrag[ SPX_MAX_TXTCB ];
	FRAGMENT			RxFrag[ SPX_MAX_RXTCB ];
	pUTEXT				TxPack[ SPX_MAX_TXTCB ];
	pUTEXT				RxPack[ SPX_MAX_RXTCB ];
	pUTEXT				Packet;
	LONG				PacketSize;
	LONG				TotalBytes;
};

#endif	/* _NTSIPX32_INCLUDED */
