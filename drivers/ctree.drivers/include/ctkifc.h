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

#ifndef ctCTKIFC_H
#define ctCTKIFC_H

#define _NTDDK_
#define _NTSTRSAFE_H_INCLUDED_

#undef ctrt_exit
#define ctrt_exit exit

#undef ctrt_printf
#define ctrt_printf printf

#include "ctlfun.h"

#undef isam_err
#define isam_err ctGetIsamErrorCode()
#undef uerr_cod
#define uerr_cod ctGetUserErrorCode()
#undef isam_fil
#define isam_fil ctGetIsamFileNbr()
#undef sysiocod
#define sysiocod ctGetSystemErrorCode()

#define BUFFER_SIZE		1024
#define CTREE_PORT_NAME	L"\\CtreePort"

typedef HRESULT (WINAPI *pFilterConnectCommunicationPort_t)(
    IN LPCWSTR lpPortName,
    IN DWORD dwOptions,
    IN LPCVOID lpContext OPTIONAL,
    IN WORD wSizeOfContext,
    IN LPSECURITY_ATTRIBUTES lpSecurityAttributes OPTIONAL,
    OUT HANDLE *hPort
);

typedef HRESULT (WINAPI *pFilterSendMessage_t)(
    IN HANDLE hPort,
    IN LPVOID lpInBuffer OPTIONAL,
    IN DWORD dwInBufferSize,
    IN OUT LPVOID lpOutBuffer OPTIONAL,
    IN DWORD dwOutBufferSize,
    OUT LPDWORD lpBytesReturned
);

typedef struct _CT_COMMAND {
	COUNT	fn;
	COUNT	filno;
	pVOID	ptr1;
	pLONG	plong;
	pVOID	ptr2;
	pVRLEN	psize;
	COUNT	mode;
	NINT	retval;
} CT_COMMAND, *PCT_COMMAND;

typedef struct _CT_MESSAGE {
	CT_COMMAND	command;
} CT_MESSAGE, *PCT_MESSAGE;

typedef struct {
	LPTHREAD_START_ROUTINE	func;
	LPVOID			parm;
	LPVOID			uvar;
	LONG			mode;
} THREAD_DATA, ctMEM *pTHREAD_DATA;

extern HANDLE	ctsport;
extern HMODULE					hFltDll;
extern pFilterConnectCommunicationPort_t	pFilterConnectCommunicationPort;
extern pFilterSendMessage_t			pFilterSendMessage;

#endif /* ~ctCTKIFC_H */

/* end of ctkifc.h */
