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

/* ctPortNLM - SQL Novell NLM Port header file */

#ifndef _CTCRTLNV_H
#define _CTCRTLNV_H

#define _WCHAR_T 		/* Prevent definition from c:\novell\ndk\clib\include\nlm\stdio.h line 34 syntax error */
#define wchar_t char
#define __USE_EXTERN_INLINES

#ifndef ctCMPLH /* prevent header from coming in again if ctcmpl.h */
#include <stdio.h>
#include <malloc.h>
#include <nlm/sys/types.h>
#include <nlm/sys/stat.h>
#include <nlm/fcntl.h>
#include <nlm/errno.h>
#include <nlm/sys/stat.h>
#include <time.h>
/* #include <process.h>	*/		/* NetWare OBSOLETE */
/* #include <advanced.h>*/		/* NetWare OBSOLETE */	
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
/* #include <ctype.h>	*/		/* RAB 990915 */
/* #include <conio.h>	*/		/* NetWare OBSOLETE */
#include <nwdir.h>
#include <nwthread.h>
#include <nwadv.h> 
#include <dirent.h>

#include <signal.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/bsdskt.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <errno.h>
#endif /* ~ctCMPLH */
 
#ifdef __cplusplus
extern "C" {
#endif

/*********************************************/
#define _fcNOSUPPORT_NOT_OK 	0	/* Not Supported Function Call, need to be checked out */
#define _fcNOSUPPORT_OK 	1	/* Not Supported Function Call, yet it is OK to ignore */
#define _fcNOSUPPORT_MAYBE_OK 	2	/* Not Supported Function Call, yet it is MAYBE OK to ignore */
#define _fcNOSUPPORT_ALTERNATE_OK 3	/* Not Supported Function Call, yet an alternate has been coded in its place */

void fcNLM_NotSupported(int, char*);	/* FairCom dummy function to trap all unsupported functions */
/*****************************************/

/*****************************************/
/* ctrt_ShowNLMinfo code Locations  */
#define rbshowNLM_LOC_CREATETHREAD	1		/* in ctpthd.c in cttcre() */
#define rbshowNLM_LOC_SQL_os_malloc	2		/* in ./sql/src/public/os/nlm/os_clib.cxx */
#define rbshowNLM_LOC_SQL_os_calloc	3		/* in ./sql/src/public/os/nlm/os_clib.cxx */
#define rbshowNLM_LOC_SQL_os_realloc	4		/* in ./sql/src/public/os/nlm/os_clib.cxx */
#define rbshowNLM_LOC_SQL_os_free	5		/* in ./sql/src/public/os/nlm/os_clib.cxx */
#define rbshowNLM_LOC_WINMAIN		6		/* in .\ctree\source\ntree\os\w32\CTWSUP.C - Just as program starts */
#define rbshowNLM_LOC_BEFORE_GUI_THREAD	7		/* in .\ctree\source\ntree\os\w32\CTWSUP.C - Before GUI Launched */
#define rbshowNLM_LOC_BEFORE_SRV_THREAD	8		/* in .\ctree\source\ntree\os\w32\CTWSUP.C - Before c-tree server mainline called  */
#define rbshowNLM_LOC_BEFORE_SQL_THREAD	9		/* in .\ctree\source\ctsrvr.c - Before SQL Subsystem thread is launched  */


/* ctrt_showNLMinfo Operation types */
#define rbshowNLM_OP_GENERAL		0		/* Nothing specific: Default */
#define rbshowNLM_OP_FAILED		-1		/* Operation failed */
#define rbshowNLM_OP_FIRSTTIME		1		/* First time opeation */
/*********************************************/



#ifdef DH_OS_WINNT
//#include "ct1rtlnv.h"
#else
#include "ct2rtlnv.h"
#endif

#define HCURSOR int
#define HANDLE int
#define HMODULE int
#define DWORD int
#define LPTSTR char*
#define LPSECURITY_ATTRIBUTES int
#define LPWSTR char*
#define VOID void
#define INFINITE 99999 /* os_thr.hxx */

#define FAR /* */
//#define AF_INET 0
#define HKEY int


//typedef unsigned int 	UINT;


#define os_memcpy               memcpy
#define os_memset               memset
#define os_memcmp               memcmp
#define ctdb_memset              memset
#define ctrt_memset              memset

#define _putenv putenv
#define _rmdir rmdir
#define _mkdir mkdir
#define _O_BINARY O_BINARY
#define _open open
#define _creat creat
#define _close close
#define _unlink unlink
#define _lseek lseek
#define _read read
#define _write write
#define _stat stat
#define _fstat fstat
#define _dup dup
#define _dup2 dup2
#define _access access
#define _isatty isatty
#define _fileno fileno
#define _cwait cwait
#define _strnicmp strnicmp
#define _stricmp stricmp
#define _fcvt fcvt
#define _ecvt ecvt

#define _getpid GetNLMID

#ifndef ctCMPLH /* RAB:060610: I for the life of me could not figure out why this gave error in ctsqlsys.c */
#ifndef __CTSQLSYS_C__
#ifndef __CTSQLDBS_C__

typedef bool BOOL;
#define CreateMutex ctrt_CreateMutex
int CreateMutex(int, BOOL, char*);

#define gethostbyname ctrt_gethostbyname 
hostent *ctrt_gethostbyname(const char *); 

#endif	/* __CTSQLDBS_C__ */
#endif	/* __CTSQLSYS_C__ */
#endif	/* ~ctCMPLH */

#define GetLastError ctrt_GetLastError
int ctrt_GetLastError(void);

#define CloseHandle ctrt_CloseHandle
int ctrt_CloseHandle(int);

#define WAIT_FAILED -1
#define WaitForSingleObject ctrt_WaitForSingleObject
int ctrt_WaitForSingleObject(int,int);

#define ReleaseMutex ctrt_ReleaseMutex
int ctrt_ReleaseMutex(int);

#define GetFullPathName ctrt_GetFullPathName
void ctrt_GetFullPathName(const char *, int, char *, char **);

#define Sleep ctrt_Sleep
void ctrt_Sleep(int);

//#define signal ctrt_signal
//int ctrt_signal(long, void(*)(int));


#define _strdate ctrt_strdate
int ctrt_strdate(char *);

//#define SIG_ERR 0
//#define SIG_IGN 0
//#define SIG_DFL 0

#define _getcwd getcwd
#define __isascii isascii

//#define SOCKET SKT /* See nlm/sys/socket.h */
#define socklen_t int
#define AF_LOCAL 0

#define WSAEADDRINUSE 	EADDRINUSE
#define WSAEWOULDBLOCK 	EWOULDBLOCK
#define WSAETIMEDOUT	ETIMEDOUT
#define WSAECONNRESET	ECONNRESET


#define socketpair ctrt_socketpair
int ctrt_socketpair(int,int,int,int*);

#define LoadLibrary ctrt_LoadLibrary
int ctrt_LoadLibrary(char *);

#define GetProcAddress ctrt_GetProcAddress
int ctrt_GetProcAddress(int, char *);

#define FreeLibrary ctrt_FreeLibrary
int ctrt_FreeLibrary(int);


/*********************************************/

#ifdef __cplusplus
}
#endif

#endif /* ~_CTCRTLNV_H */
/* end of ctcrtlnv.h */