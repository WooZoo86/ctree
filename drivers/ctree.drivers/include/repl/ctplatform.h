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
 *      Copyright (c) 2013 - 2015 FairCom Corporation.
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
 */

#ifndef _CTPLATFORM_H_
#define _CTPLATFORM_H_

#ifndef _WINDOWS
#define _WINDOWS
#endif

#include <winsock2.h>
#include <windows.h>
#include <direct.h>

#define FCAPI WINAPI
#define FC_FUNC_RET unsigned long
#define FC_WAIT_TIMEOUT WAIT_TIMEOUT

#define FCULONG unsigned long

typedef long long TIMER;

#define CURRTIME time( NULL )
typedef time_t _TIMER;
#define localtime _localtime64

#define FCBigInt __int64

#define GetCurrentDir _getcwd

#define WIN_IGNORE_RECYCLE 1 /* Ignoring RECYCLE file notifications */

#define CT_DYNLIB_EXT ".dll"
#define CT_APP_EXT ".exe"
#define CT_CLIENT_DYN_LIB "mtclient.dll"
#define CT_SERVER_DYN_LIB "ctreedbs.dll"
#define CT_SQL_DYN_LIB "ctsqlapi.dll"
#define CT_MAIN_INIT_LIB "FcServerWinMain"

#endif /* _CTPLATFORM_H_ */