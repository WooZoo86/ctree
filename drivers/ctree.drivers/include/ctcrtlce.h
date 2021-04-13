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

#ifndef _CTCRTLCE_H
#define _CTCRTLCE_H
#define  COREDLL			/* CONTROLS the definition of WINBASEAPI for emulator */
#define _ADVAPI32_		/* CONTROLS the definition of WINADVAPI for emulator */
#include <malloc.h>
#include <stdio.h>
#include <memory.h>
#include <windows.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <tchar.h>

//#define _CTSQLOCE_H							/* This define caused the following header to be ignored, so that all the Dharma  default seetings are used */
//#define DH_NETBUF_SIZE 256000 	/* was: 1500000 */
#include "ctsqlovr.h" 					/* Override Dharma SQL Engine base defines file for CE */

//#define  ctdbMEMSUM

#ifndef ctOPT2H
#define ctOPT2H
#include "ctoptn.h"
#undef ctOPT2H
#endif

#ifdef ctPortDIAD_FS
#define  ctDIADFILESYSTEM_H	"ctDiadFileSystem.h"
#include ctDIADFILESYSTEM_H
#endif

#ifndef UNICODE
#define _tcstod     strtod
#define _tcstol     strtol
#define _totupper   toupper
#define _totlower   tolower
#define _istupper   iswupper
#define _istlower   iswlower
#define _istdigit   isdigit
#define _istprint   isprint
#define _istspace   isspace
#define _tcsicmp    _stricmp
#define _tcsrchr    strrchr
#define _tcsncicmp  _strnicmp
#define _istalpha   isalpha
#endif

#ifndef ctPortWINCE_SRVR
#define ctPortWINCE_SRVR
#endif
 
#ifdef __cplusplus
extern "C" {
#endif

/*********************************************/

#define _fcNOSUPPORT_NOT_OK 	0					/* Not Supported Function Call, need to be checked out */
#define _fcNOSUPPORT_OK 			1					/* Not Supported Function Call, yet it is OK to ignore */
#define _fcNOSUPPORT_MAYBE_OK 2		/* Not Supported Function Call, yet it is MAYBE OK to ignore */
#define _fcNOSUPPORT_ALTERNATE_OK 3			/* Not Supported Function Call, yet an alternate has been coded in its place */

_CRTIMP void __cdecl fcWCE_NotSupported(int, char*);				/* Windows CE Port: FairCom dummy function to trap all unsupported functions */
/*****************************************/


/*****************************************/
/* ctrt_ShowCEinfo code Locations  */
#define rbShowCE_LOC_CREATETHREAD 			1				/* in ctpthd.c in cttcre() */
#define rbShowCE_LOC_SQL_os_malloc			2				/* in ./sql/src/public/os/windows/os_clib.cxx */
#define rbShowCE_LOC_SQL_os_calloc			3				/* in ./sql/src/public/os/windows/os_clib.cxx */
#define rbShowCE_LOC_SQL_os_realloc			4				/* in ./sql/src/public/os/windows/os_clib.cxx */
#define rbShowCE_LOC_SQL_os_free				5				/* in ./sql/src/public/os/windows/os_clib.cxx */
#define rbShowCE_LOC_WINMAIN						6				/* in .\ctree\source\ntree\os\w32\CTWSUP.C - Just as program starts */
#define rbShowCE_LOC_BEFORE_GUI_THREAD	7				/* in .\ctree\source\ntree\os\w32\CTWSUP.C - Before GUI Launched */
#define rbShowCE_LOC_BEFORE_SRV_THREAD	8				/* in .\ctree\source\ntree\os\w32\CTWSUP.C - Before c-tree server mainline called  */
#define rbShowCE_LOC_BEFORE_SQL_THREAD	9				/* in .\ctree\source\ctsrvr.c - Before SQL Subsystem thread is launched  */


/* ctrt_ShowCEinfo Operation types */
#define rbShowCE_OP_GENERAL				0				/* Nothing specific: Default */
#define rbShowCE_OP_FAILED				-1			/* Operation failed */
#define rbShowCE_OP_FIRSTTIME			1				/* First time opeation */


_CRTIMP void __cdecl ctrt_ShowCEinfo(int loc, int op);					/* Show Windows CE OS system Info for debugging */
/*********************************************/

/*********************************************/
//#define RAB_IF_NEEDED_TIME
#ifdef 	RAB_IF_NEEDED_TIME
#ifndef _TM_DEFINED
struct tm {
	int tm_sec;	/* seconds after the minute - [0,59] */
	int tm_min;	/* minutes after the hour - [0,59] */
	int tm_hour;	/* hours since midnight - [0,23] */
	int tm_mday;	/* day of the month - [1,31] */
	int tm_mon;	/* months since January - [0,11] */
	int tm_year;	/* years since 1900 */
	int tm_wday;	/* days since Sunday - [0,6] */
	int tm_yday;	/* days since January 1 - [0,365] */
	int tm_isdst;	/* daylight savings time flag */
	};
#define _TM_DEFINED
#endif
#define asctime		ctrt_asctime
_CRTIMP char * __cdecl 	ctrt_asctime(const struct tm *);

#ifndef _TIME_T_DEFINED
typedef long time_t;		/* time value */
#define _TIME_T_DEFINED 	/* avoid multiple def's of time_t */
#endif
#define localtime 		ctrt_localtime
_CRTIMP struct tm * __cdecl 	ctrt_localtime(const time_t *);

#define ctime 		ctrt_ctime
_CRTIMP char * __cdecl 	ctrt_ctime(const time_t *);

#ifndef _CLOCK_T_DEFINED
typedef long clock_t;
#define _CLOCK_T_DEFINED
#endif

#define clock 		ctrt_clock
_CRTIMP clock_t __cdecl ctrt_clock(void);


#define mktime 		ctrt_mktime
_CRTIMP time_t __cdecl 	ctrt_mktime(struct tm *);

#define time 		ctrt_time
_CRTIMP time_t __cdecl 	ctrt_time(time_t *);

#define _tstrdate ctrt__strdate
#define _strdate	ctrt__strdate
_CRTIMP char * __cdecl 	ctrt__strdate(char *);

#endif /* ifdef RAB_IF_NEEDED_TIME */
/************************************************/



/*********************************************/
#define getenv 		ctrt_getenv
_CRTIMP char * __cdecl 	ctrt_getenv(const char *);

#define _putenv 	ctrt__putenv
_CRTIMP int    __cdecl 	ctrt__putenv(const char *);

#define strdup 		ctrt_strdup
_CRTIMP char * __cdecl 	ctrt_strdup(const char *);

#define  getpid 	ctrt_getpid
#define _getpid 	ctrt_getpid
_CRTIMP int __cdecl 	ctrt_getpid(void);
/*****************************************/

#define  getch 		ctrt__getch
#define _getch 		ctrt__getch
_CRTIMP int __cdecl 	ctrt__getch(void);

/*****************************************/
#define getcwd    	ctrt__getcwd
#define _getcwd    	ctrt__getcwd
#define _tgetcwd    	ctrt__getcwd
_CRTIMP char * __cdecl 	ctrt__getcwd(char *, int);

#define  _rmdir(a)	ctrt__rmdir((char *)a)
#define _trmdir(a)     	ctrt__rmdir((char *)a)
_CRTIMP int __cdecl 	ctrt__rmdir(const char *);	

#define  _mkdir		ctrt__mkdir
#define _tmkdir		ctrt__mkdir
_CRTIMP int __cdecl	ctrt__mkdir(const char *);
/*****************************************/


/*****************************************/
#ifndef ctCTCMPL

#ifdef ctPortDIAD_FS
#define fclose			(*ctfs_fclose)
/*
** fflush() does nothing on the DIAD file system
** because the DIAD does not cache writes.
*/
#define fflush(fp)		(0)
#define fgets			fs_fgets
#define fopen			fs_fopen_wrap
#define fprintf			fs_fprintf
#define fread			fs_fread_wrap
#define fscanf			fs_fscanf
#define fseek			(*ctfs_fseek)
#define ftell			(*ctfs_ftell)
#define fwrite(b,s,c,f)		fs_fwrite_wrap((void*)(b),s,c,f)
#undef stdout
#define stdout			NULL
#endif

#endif /* ~ctCTCMPL */

#undef	_tfopen
#define _tfopen fopen
#undef	_tfreopen
#define _tfreopen		ctrt_freopen
#define _freopen		ctrt_freopen
#define freopen			ctrt_freopen
_CRTIMP FILE * __cdecl 	ctrt_freopen(const char *, const char *, FILE *);

#define rewind 		ctrt_rewind
_CRTIMP void __cdecl 	ctrt_rewind(FILE *);

#define _stat		ctrt__stat
#define _tstat      	ctrt__stat
_CRTIMP int __cdecl 	ctrt__stat(const char *, struct _stat *);

#define _open		ctrt__open
#define _topen		ctrt__open
_CRTIMP int __cdecl	ctrt__open(const char *, int, ...);

#define _creat		ctrt__creat
#define _tcreat		ctrt__creat
_CRTIMP int __cdecl	ctrt__creat(const char *, int);

#define rename    	ctrt_rename
#define _trename    	ctrt_rename
_CRTIMP int __cdecl 	ctrt_rename(const char *, const char *);

#define _close    	ctrt__close
_CRTIMP int __cdecl 	ctrt__close(int);

#define _unlink    	ctrt__unlink
#define _tunlink    	ctrt__unlink
_CRTIMP int __cdecl 	ctrt__unlink(const char *);

#define _lseek    	ctrt__lseek
_CRTIMP long __cdecl	ctrt__lseek(int, long, int);

#define _read    	ctrt__read
_CRTIMP int __cdecl 	ctrt__read(int, void *, unsigned int);

#define _write    	ctrt__write
_CRTIMP int __cdecl 	ctrt__write(int, const void *, unsigned int);

#define _dup    	ctrt__dup
_CRTIMP int __cdecl 	ctrt__dup(int);

#define _dup2    	ctrt__dup2
_CRTIMP int __cdecl 	ctrt__dup2(int, int);

#define _access    	ctrt__access
#define _taccess    	ctrt__access
_CRTIMP int __cdecl 	ctrt__access(const char *, int);

#define _tsystem ctrt_system
_CRTIMP int __cdecl 	ctrt_system(const TCHAR* s);

#define _isatty ctrt__isatty
_CRTIMP int __cdecl 	ctrt__isatty(int);

/*****************************************/

/*****************************************/
#define stricmp _stricmp
/*****************************************/

/*****************************************/
#define _cwait    	ctrt__cwait
_CRTIMP int __cdecl 	ctrt__cwait(int *, int, int);

#define   perror(a)	ctrt_perror((char *)a)
#define _tperror(a)	ctrt_perror((char *)a)
_CRTIMP void __cdecl 	ctrt_perror(const char *); 

#define system		ctrt_system
#define _system		ctrt_system
_CRTIMP int __cdecl 	ctrt_system(const TCHAR *);

#define wcscoll    	ctrt_wcscoll
_CRTIMP int __cdecl 	ctrt_wcscoll(const wchar_t *, const wchar_t *);


#define abort		ctrt_abort
_CRTIMP int __cdecl 	ctrt_abort();

/*****************************************/

/*****************************************/
#define GetShortPathName ctrt_GetShortPathName
DWORD ctrt_GetShortPathName(LPCTSTR lpszLongPath,LPTSTR lpszShortPath,DWORD cchBuffer);

#define GetUserName ctrt_GetUserName
BOOL ctrt_GetUserName(LPTSTR lpBuffer,LPDWORD nSize);


#define GetFullPathName ctrt_GetFullPathName
DWORD WINAPI    	ctrt_GetFullPathName(LPCSTR lpFileName, DWORD nBufferLength,LPSTR lpBuffer, LPSTR *lpFilePart);

#define _GetFileType 	ctrt_GetFileType
#define GetFileType 	ctrt_GetFileType
DWORD WINAPI 		ctrt_GetFileType(HANDLE hFile);


#define GetMenu 	ctrt_GetMenu
WINUSERAPI HMENU WINAPI ctrt_GetMenu(HWND hWnd);

#define ModifyMenu 	ctrt_ModifyMenuA
WINUSERAPI BOOL WINAPI ctrt_ModifyMenuA(HMENU hMnu,UINT uPosition,UINT uFlags,UINT uIDNewItem,LPCSTR lpNewItem);

#ifdef IF_NEEDED
#undef  GetProcAddress
#define GetProcAddress ctrt_GetProcAddress
WINBASEAPI FARPROC WINAPI ctrt_GetProcAddress( HMODULE hModule, LPCSTR lpProcName );
#endif


//#define UnlockFile 	ctrt_UnlockFile
BOOL WINAPI 	ctrt_UnlockFile(HANDLE hFile,
    DWORD dwFileOffsetLow,
    DWORD dwFileOffsetHigh,
    DWORD nNumberOfBytesToUnlockLow,
    DWORD nNumberOfBytesToUnlockHigh
    );

//#define LockFile 	ctrt_LockFile
BOOL WINAPI 	ctrt_LockFile(
    HANDLE hFile,
    DWORD dwFileOffsetLow,
    DWORD dwFileOffsetHigh,
    DWORD nNumberOfBytesToLockLow,
    DWORD nNumberOfBytesToLockHigh
    );
/*****************************************/


/*****************************************/
//#define beginthreadex 	ctrt__beginthreadex
//#define __beginthreadex 	ctrt__beginthreadex
//#define _beginthreadex 	ctrt__beginthreadex
unsigned long __cdecl ctrt__beginthreadex(void *, unsigned,
        unsigned (__stdcall *) (void *), void *, unsigned, unsigned *);

//#define	endthreadex 	ctrt__endthreadex
//#define __endthreadex 	ctrt__endthreadex
//#define _endthreadex 	ctrt__endthreadex
void __cdecl ctrt__endthreadex(unsigned);
/*****************************************/


/*****************************************/
extern int errno;

#define _O_CREAT	0x0100  		/* create and open file */
#define  O_CREAT        _O_CREAT
#define _O_RDWR         0x0002 			/* open for reading and writing */
#define  O_RDWR         _O_RDWR
#define _O_RDONLY       0x0000  		/* open for reading only */
#define  O_RDONLY       _O_RDONLY

#define FILE_TYPE_DISK      0x0001

#define SIG_ERR (void (__cdecl *)(int))-1       /* signal error value */
#define SIG_IGN (void (__cdecl *)(int))1        /* ignore signal */
#define SIG_DFL (void (__cdecl *)(int))0        /* default signal action */
#define ENOENT          2

/*****************************************/

#ifdef __cplusplus
}
#endif


#endif /* ~_CTCRTLCE_H */
/* end of ctcrtlce.h */