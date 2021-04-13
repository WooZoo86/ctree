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

#ifndef ctSRVCH
#define ctSRVCH

#ifndef ctPortWDARM
#ifndef ctPortWINKE

#define ctSERVICE_BGD	1	/* NT Service Launch Background */
#define ctSERVICE_INT	2	/* NT Service Launch Interactive */

#define SERVICE_ID_DEFAULT0 _T("ctreeServer")
#define SERVICE_ID_DEFAULT2 _T("ctreeSQLServer")
#define SERVICE_ID_DEFAULT3 _T("ctreeJQLServer")

#define SERVICE_EXE_TYPE0 0 /* ctsrvr.exe */
#define SERVICE_EXE_TYPE2 2 /* ctreesql.exe */
#define SERVICE_EXE_TYPE3 3 /* ctreejql.exe */

/****************************************************************************/
/* Function prototypes. */
/****************************************************************************/
extern int  ServiceMainStub(void * pParm);
extern void WINAPI Handler(DWORD dwControl);

#ifdef __cplusplus
extern DWORD ErrorPrinter(const TCHAR* pszFcn, DWORD dwErr = GetLastError());
#else  /* ~__cplusplus */
extern DWORD ErrorPrinter(const TCHAR* pszFcn, DWORD dwErr);
#endif /* ~__cplusplus */
extern void LookupErrorMsg(TCHAR* pszMsg, int cch, DWORD dwError);
extern void PrintEvent(const TCHAR* psz);
extern void SendStatus(DWORD dwCurrentStatus, DWORD dwCheckpoint, DWORD dwWaitHint, DWORD dwControlsAccepted, DWORD dwExitCode, DWORD dwServiceSpecificExitCode);

#endif /* ~ctPortWINKE */
#endif /* ~ctPortWDARM */
#endif /* ctSRVCH */

/* end of ctsrvc.h  */
