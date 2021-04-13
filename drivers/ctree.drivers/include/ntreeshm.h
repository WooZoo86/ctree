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
*   NTREESHM.H
*	
*   This is the internal header file for the shared memory protocol. 
*	It automatically includes NTREELIB.H and is used by all modules
*	in the library. Uses should not include this module since it is
*   used internally by NTREE.
*
***********************************************************************/

#ifndef _NTREESHM_INCLUDED
#define _NTREESHM_INCLUDED

#include "ntreestd.h"

#ifdef ntSHM

#ifdef	PROTOTYPE

NINT ntDECL ntShmOpen( pCONNECTION Socket );
NINT ntDECL ntShmClose( pCONNECTION Socket );
NINT ntDECL ntShmShutdown( pCONNECTION Socket );
NINT ntDECL ntShmCleanUp( pCONNECTION Socket );
NINT ntDECL ntShmSend( pCONNECTION Socket, pVOID Buffer, LONG BytesToSend, pLONG BytesSent );
NINT ntDECL ntShmSendVector( pCONNECTION Connection, pVECTOR Vector, NINT Count, pLONG BytesSent );
NINT ntDECL ntShmReceive( pCONNECTION Socket, pVOID Buffer, LONG BufferSize, pLONG BytesReceived );
NINT ntDECL ntShmReadVector( pCONNECTION Connection, pVECTOR Vector, NINT Count, pLONG BytesReceived );
NINT ntDECL ntShmSetOption( pCONNECTION Socket, NINT Option, LONG Value );
NINT ntDECL ntShmGetOption( pCONNECTION Socket, NINT Option, pLONG Value );

#else	/* PROTOTYPE */

NINT ntDECL ntShmOpen();
NINT ntDECL ntShmClose();
NINT ntDECL ntShmShutdown();
NINT ntDECL ntShmCleanUp();
NINT ntDECL ntShmSend();
NINT ntDECL ntShmSendVector();
NINT ntDECL ntShmReceive();
NINT ntDECL ntShmReadVector();
NINT ntDECL ntShmSetOption();
NINT ntDECL ntShmGetOption();

#endif	/* PROTOTYPE */

#endif	/* ntSHM */

#endif	/* _NTREESHM_INCLUDED */
