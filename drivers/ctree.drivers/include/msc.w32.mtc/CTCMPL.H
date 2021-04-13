/* Windows W32 compiler setup */

#ifndef ctCTCMPL
#define ctCTCMPL

#ifdef ctPortWDARM
#endif

#ifdef ctSQLSRVR
#define _CTYPE_DISABLE_MACROS
#endif


#ifdef CTREEPH
#ifndef CTPERM
#ifndef ctdbCTPERM
#ifdef MULTITRD
#ifdef ctThrds
#ifdef ctFeatSRVDLL

#define DllExtImp	__declspec(dllimport)

#endif
#endif
#endif
#endif
#endif
#endif

/*
** When building a CTUSER DLL, define DllExtImp to import data from the
** c-tree Server DLL.
*/
#ifdef ctCTUSER_C
#ifdef ctDLLLIB
#define DllExtImp	__declspec(dllimport)
#endif
#endif

#ifndef DllExtImp
#define DllExtImp
#endif

/*^***********************************/
/*
** For internal server modules, map fopen/freopen to ctrt_fopen/ctrt_freopen.
*/
#if defined(ctSRVR) && defined(CTPERM)

#ifndef NO_ctFeatWINctrt_fopen
#define ctFeatWINctrt_fopen
#endif

#ifndef NO_ctFeatWINctrt_freopen
#define ctFeatWINctrt_freopen
#endif

#endif /* ctSRVR && CTPERM */
/*~***********************************/

#ifdef ctPortWINCE
#define ctNoUnalignedLongs

#include <malloc.h>
#include <stdio.h>
#include <memory.h>
#include <windows.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#else

#ifdef ctPortWINKE

#define ctPortWINKEfltdrvr

#ifdef ctPortWINKEfltdrvr
#include <fltKernel.h>
#endif

/*
** #define ctFeatWINKE_USE_SEMA_FOR_MUTEX causes mbThrdMutex calls to use
** a semaphore object instead of a mutex object.
*/
#define ctFeatWINKE_USE_SEMA_FOR_MUTEX

#ifndef _NTDDK_
#ifndef _NTIFS_
#include <ntifs.h>
#endif
#endif
#include <ntstrsafe.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

typedef unsigned long DWORD;
typedef int BOOL;

#define WINAPI
#define CCHSIZ(n)			n,
#define INVALID_HANDLE_VALUE		(HANDLE)(LONG_PTR)-1
#define FILE_FLAG_SEQUENTIAL_SCAN	FILE_SEQUENTIAL_ONLY
#define FILE_FLAG_WRITE_THROUGH		FILE_WRITE_THROUGH
#define FILE_FLAG_RANDOM_ACCESS		FILE_RANDOM_ACCESS
#define ERROR_TOO_MANY_OPEN_FILES	STATUS_TOO_MANY_OPENED_FILES
#define ERROR_FILE_EXISTS		STATUS_OBJECT_NAME_COLLISION
#define ctALLOC
#define ct_alloc(n,s)			ctrt_alloc(n,s)
#define ctafree(p)			ExFreePoolWithTag(p, 'ERTC')

/*
** #define ctWINKEdbgstack enables tracking of remaining stack space
** in file create, delete, flush calls. The members of ctstack are
** set to the remaining stack size in the file system operation
** functions and are reset to zero on exit. If a stack overflow
** occurs, look at the members of ctstack for a non-zero stack
** size indicating which operation is active.
*/
#define ctWINKEdbgstack

#ifdef ctWINKEdbgstack
typedef struct {
	int	crestk;
	int	delstk;
	int	renstk;
	int	clsstk;
	int	flsstk;
	int	redstk;
	int	wrtstk;
} ctstk_t;
extern ctstk_t	ctstack;
#endif

/*
** #define ctWINKEdbgio enables tracking of disk I/O operations.
*/
#define ctWINKEdbgio

extern VOID report_ctsdio(VOID);

extern PDRIVER_OBJECT	pctDriverObject;

/*
** The following macro definitions cause calls to these functions
** to be skipped.
*/
#define srvrflashmsg(legend)
#define srvrcopyright(legend)
#define initctsrvr()
#define startctsrvr()
#define stopctsrvr()

#ifdef NO_CTINOD_C
#define ct_uniqfile(fn1,fn2) ctrt_filcmp(fn1,fn2)
#endif

#define ctThrdHandle_defined
#define ctThrdHandle ctOWNER

/*
** Uncomment the following #define if work item functions
** make c-tree calls and so need a database connection ID (sOWNR).
**
#define ctWINKE_WORK_ITEM_OWNR_NEEDED
*/

/* WINKE_TODO */
#define ctPortWINKEcrt

#define _FILE_DEFINED
struct _ctiobuf {
        char *_ptr;
        int   _cnt;
        int   _base;
        int   _flag;
        __int64   _file;
        int   _charbuf;
        int   _bufsiz;
        char *_tmpfname;
        };
typedef struct _ctiobuf ctFILE;
#define FILE ctFILE

#else  /* ~ctPortWINKE */

#if _WIN32_WINNT < 0x0502
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0502 /* required for CopyFileEx */
#endif

#include <stdio.h>
#ifndef ctPortWDARM
#include <dos.h>
#include <io.h>
#include <malloc.h>
#include <fcntl.h>
#include <memory.h>
#endif
#include <winsock2.h>
#include <ws2tcpip.h> 
#ifndef ctPortWDARM
#include <windows.h>
#include <process.h>
#endif
#include <stddef.h>
#include <stdlib.h>
#ifndef ctPortWDARM
#include <conio.h>
#endif
#include <string.h>
#ifndef ctPortWDARM
#include <direct.h>
#endif
#include <time.h>

#endif /* ~ctPortWINKE */

#endif /* ~ctPortWINCE */


/*^***********************************/
#ifndef ctPortFAIRCOM_THREADS
#ifndef ctPortNATIVE_THREADS

#endif 	/* ~ctPortNATIVE_THREADS */
#endif	/* ~ctPortFAIRCOM_THREADS */
/*~***********************************/


/*^***********************************/
#ifdef ctPortFAIRCOM_THREADS

#ifdef ctSRVR
#ifndef SERVER_OSMSG
#define SERVER_OSMSG 	"For Windows 98/95 Operating System with FairCom Threads"
#endif
#define SERVER_OSMSG_NT "For Windows NT/2000 Operating System with FairCom Threads"
#endif

#endif /* ctPortFAIRCOM_THREADS */
/*~***********************************/


/*^***********************************/
#ifdef ctPortNATIVE_THREADS
#if (defined(ctSRVR) || defined(ctBNDSRVR))

#ifndef SERVER_OSMSG
#define SERVER_OSMSG 	"For Windows 64bit Operating System"
#endif
#define SERVER_OSMSG_NT "For Windows 64bit Operating System"

#endif /* ctSRVR or ctBNDSRVR */
#endif /* ctPortNATIVE_THREADS */
/*~***********************************/


/*^***********************************/
#ifdef ctPortNATIVE_THREADS
#if (defined(ctMTCLIENT) || defined(ctMTFPG))


#endif /* ctMTCLIENT */
#endif /* ctPortNATIVE_THREADS */
/*~***********************************/


/*^***********************************/
#ifndef ctPortWINDOWSNT
#define ctPortWINDOWSNT
#endif

#ifndef ctPortWIN32
#define ctPortWIN32
#define ctPortWIN64
#endif

#define LOW_HIGH
#define PERC_HD

#ifdef ctPortWINKE

extern void ctWINKEsleepthread(LONG msec);
extern int  ctWINKEflushfile(HANDLE hFile);
#define	ctDEFER_SLEEP ctWINKEsleepthread
#define ctSAVEdupRESET(fdh) ctWINKEflushfile((HANDLE)fdh)

#else  /* ~ctPortWINKE */

#define	ctDEFER_SLEEP	Sleep

#ifdef ctPortDIAD_FS
/*
** fflush() does nothing on the DIAD file system
** because the DIAD does not cache writes.
*/
#define ctSAVEdupRESET(fdh) (0)
#else
#ifdef ctFeatBlockCompressionFuncs
#define ctSAVEdupRESET(fdh) (LZFileIOFlushFileBuffers((HANDLE)(NLONG)(fdh)) == FALSE)
#else
#define ctSAVEdupRESET(fdh) (FlushFileBuffers((HANDLE)(NLONG)(fdh)) == FALSE)
#endif
#endif

#endif /* ~ctPortWINKE */

#define ctFileFailure == (RNDFILE)(LONG_PTR)INVALID_HANDLE_VALUE

#define rtLPT0	"LPT0"
#define rtLPT1	"LPT1"
#define rtLPT2	"LPT2"

/**** ****/
#define C255    		-1
#define COMMIT_DELAY		(1000L)

#ifdef ctPortW64_ITANIUM_AMD
/*
** Use memmove() on Itanium systems to ensure correct results
** when source and destination regions overlap.
*/
#define cpy4bf(dp,sp)    	memmove(dp,sp,4)
#define cpybig(d,s,n)   	memmove(d,s,(UINT) (n))
#define cpybuf(dp,sp,n)  	memmove(dp,sp,(UINT) (n))
#else
#define cpy4bf(dp,sp)    	memcpy(dp,sp,4)
#define cpybig(d,s,n)   	memcpy(d,s,(UINT) (n))
#define cpybuf(dp,sp,n)  	memcpy(dp,sp,(UINT) (n))
#endif

#define cpylng(dp,sp,n)  	cpy4bf(dp,sp)
#define cpylodl(d,s,n)  	cpylod(d,s,(UINT) (n))
#define cpymbuf			cpybuf
#define cpymsg			cpybuf
#define cpysrcl(d,s,n)  	cpysrc(d,s,(UINT) (n))
#define cpysrcm			cpysrcl
#define ct_NULL (char *) 	0
#define ctbfill(dp,ch,n) 	memset(dp,ch,(UINT) (n))
#define ctcfill        		ctcbill
#define ctCONV

#ifdef ctPortREALIA
#define ctDECL			__fastcall
#define ctDECLV			__cdecl
#else  /* ~ctPortREALIA */
#ifdef ctFeatVB			/* Special settings for Visual Basic */
#define ctDECL			_stdcall
#define ctDECLV			_stdcall
#else  /* ~ctFeatVB */
#define ctDECL
#define ctDECLV
#endif /* ~ctFeatVB */
#endif /* ~ctPortREALIA */

#define ctDECLT
#define ctEXCLCREAT
#define ctEXPORT 
#define ctMEM
#define ctMEMCHRtxt 		TEXT *
#define ctmfill         	ctbfill
#define ctMILLISECOND(t)        (t)

#ifdef ctThrds

/*
See note in ctopt2.h.
*/
#ifndef ctPortWINCE
#ifndef ctPortWINKE
#define ctFeatW32_MUTXCS
#endif
#endif
#define ctSEMMTX

#ifdef ctSEMMTX
#define	ctSEMTIM
#else  /* ~ctSEMMTX */

#define ctSEMUTX

#ifdef ctFeatW32_MUTXCS

/* use NT/W2000 critical section calls */
#define SEMAmut		SEMACS
#define pSEMAmut	pSEMACS

#else  /* ~ctFeatW32_MUTXCS */

/* use NT/W2000 mutex calls */
#define SEMAmut		SEMA
#define pSEMAmut	pSEMA

#endif /* ~ctFeatW32_MUTXCS */

#endif /* ~ctSEMMTX */

#endif /* MULTITRD */

#ifdef ctSRVR
#define ctrt_exit       	ctWINexit
#else
void ctDECL ctrt_exit(int ret);
#endif

#ifdef ctPortDIAD_FS
#define fclose			(*ctfs_fclose)
/*
** fflush() does nothing on the DIAD file system
** because the DIAD does not cache writes.
*/
#define fflush(fp)
#define fgets			fs_fgets
#define fopen			fs_fopen_wrap
#define fprintf			fs_fprintf
#define fread			fs_fread_wrap
#define freopen			fs_freopen
#define fscanf			fs_fscanf
#define fseek			(*ctfs_fseek)
#define ftell			(*ctfs_ftell)
#define fwrite			fs_fwrite_wrap
#undef stdout
#define stdout			NULL
#endif

#define ctrt_setcwd		ctWINchdir
#define ctrt_fclose     	fclose
#ifdef ctFeatWINctrt_fopen
extern FILE *ctrt_fopen(const char *filename, const char *mode);
#else
#define ctrt_fopen      	fopen
#endif
#define ctrt_popen		fopen
#ifdef ctPortWINKEcrt
/* WINKE_TODO */
#undef stdin
#define stdin			NULL
#undef stdout
#define stdout			NULL
#define fopen			ctrt_fopen
#define fread			ctrt_fread
#define fwrite			ctrt_fwrite
#define fgets			ctrt_fgets
#define ftell			ctrt_ftell
#define fseek			ctrt_fseek
#define fflush			ctrt_fflush
#define fscanf			ctrt_fscanf
#define fprintf			ctrt_fprintf
#define fclose			ctrt_fclose
#define atof			ctrt_atof
#define ceil			ctrt_ceil
#define floor			ctrt_floor
#define strtol			ctrt_strtol
#define fmod			ctrt_fmod
#define modf			ctrt_modf
#define isalpha(ch)		((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
#define isalnum(ch)		((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
#define ctrt_printf
#else
#ifdef ctFeatWINctrt_freopen
extern FILE *ctrt_freopen(const char *filename, const char *mode, FILE *fp);
#else
#define ctrt_freopen		freopen
#endif
#define ctrt_fprintf    	fprintf
#define ctrt_fgets		fgets
#define ctrt_ftell		ftell
#define ctrt_scanf		scanf
#endif
#define ctrt_fscanf     	fscanf
#define ctrt_memchr     	memchr
#define ctrt_memcmp     	memcmp
#define ctrt_memset     	memset
#define ctrt_fork		(0)
#define ctrt_execf		return(-1)
#define ctrt_execl(a,b,c)	spawnl(P_NOWAIT,a,b,c)
#define ctrt_qsort	qsort
#define ctrt_bsearch	bsearch

#define isatty(x) _isatty(x)
#define fileno(x) _fileno(x)

#ifdef ctPortDotNET_APP
#define ctrt_printf net_printf
#endif

#ifndef ctrt_printf
int ctDECLV ctrt_printf(const char *, ... );
#endif

#ifdef ctSRVR
#define ctrt_monitor		ctrt_msgmon
#define ctrt_fncmon		ctrt_fncmon /* see ctwsup.c */
#define ctrt_msgmon		ctrt_msgmon /* see ctwsup.c */
#define ctrt_wrtmsg		ctrt_wrtmsg /* see ctwsup.c */
extern  VOID ctDECLV ctrt_wrtmsg( char * fmt, ... );
extern 	VOID ctDECLV ctrt_msgmon( char * fmt, ... );
extern	VOID ctDECLV ctrt_fncmon( char * fmt, ... );
#else
#define ctrt_monitor		ctrt_printf
#define ctrt_fncmon		ctrt_printf
#define ctrt_msgmon		ctrt_printf
#endif /* ~ctSRVR */

#ifdef ctPortWINIOT
#define chdir  _chdir
#define getcwd _getcwd
#endif

#ifdef ctPortWINKE

#define ctrt_vsprintf    	RtlStringCchVPrintfA
#define ctrt_sprintf    	RtlStringCchPrintfA
#define ctrt_strcpy     	RtlStringCchCopyA
#define ctrt_strcat     	RtlStringCchCatA
#define ctdb_sprintf		ctrt_sprintf
#define ctdb_stricmp		ctrt_stricmp
#define ctdb_fopen		ctrt_fopen
#define ctdb_fclose		ctrt_fclose

#else  /* ~ctPortWINKE */

#define ctrt_vsprintf    	vsprintf
#define ctrt_sprintf    	sprintf
#define ctrt_strcpy     	strcpy
#define ctrt_strcat     	strcat
#define ctdb_fopen		ctrt_fopen
#define ctdb_fclose		ctrt_fclose

/*^***********************************/
/*
** String operations with buffer size limits:
*/
#if _MSC_VER >= 1400

/*
** Visual Studio 2005 and later compilers support variadic macros, so we use
** that feature to insert the _TRUNCATE parameter. We use these functions and
** the _TRUNCATE parameter for the following reason:
**
** When the formatted data does not fit into the output buffer, using _TRUNCATE
** causes these functions to write as much data as will fit into the output
** buffer, including a null terminator, instead of zeroing out the output buffer
** and calling the C runtime's invalid parameter handler.
*/
#define ctcr_sprintf(str,size,format,...)	_snprintf_s(str,size,_TRUNCATE,format,__VA_ARGS__)
#define ctcr_vsprintf(str,size,format,...)	_vsnprintf_s(str,size,_TRUNCATE,format,__VA_ARGS__)

#else

#if _MSC_VER == 1200

#define ctcr_sprintf	_snprintf
#define ctcr_vsprintf	_vsnprintf

#else

/*
** Visual Studio 2003 and earlier compilers do not support variadic macros, so
** we use sprintf_s and vsprintf_s. But note that these functions throw an
** exception if the output buffer is too small to hold the formatted data.
*/
#define ctcr_sprintf	sprintf_s
#define ctcr_vsprintf	vsprintf_s

#endif

#endif
/*~***********************************/

#endif /* ~ctPortWINKE */

#ifndef ctrt_snprintf
#if _MSC_VER <= 1800 /* VS2013 */
#define ctrt_snprintf	_snprintf
#else
#define ctrt_snprintf	snprintf
#endif
#endif

#define ctrt_strncat     	strncat
#define ctrt_strcmp     	strcmp
#ifdef ctPortWINCE
#define ctrt_stricmp     	_stricmp
#define ctrt_strnicmp     	_strnicmp
#else
#ifndef ctPortWINKE
#define ctrt_stricmp     	stricmp
#define ctrt_strnicmp     	strnicmp
#endif
#endif
#define ctrt_strlen     	strlen
#define ctrt_strncpy    	strncpy
#define ctrt_strncmp		strncmp
#define ctrt_strstr		strstr
#ifdef ctUSE_TEMPENV
char *ctDECL ctrt_tmpnam(char *);
#else
#ifndef ctPortWINKEcrt
#ifndef ctPortSTI_STANDALONE
#define ctrt_tmpnam     	tmpnam
#endif
#endif
#endif

#ifdef  ctSRVR
#ifndef ctPortWINKE
#define ctUSE_CHARUPPER
#endif
#endif

#ifdef  ctUSE_CHARUPPER
char ctDECL ctrt_toupper(char);
#else
#define ctrt_toupper    	toupper
#endif
#ifndef ctPortWINKEcrt
#if _MSC_VER >= 1900
extern char * gets(char *buf);
#endif
#define ctrt_gets		gets
#endif
#define ctsfill(dp,ch,n) 	memset(dp,ch,n)
#define ctSTATIC_SEMA
#define ctSTRICTANSI
#define DllLoadDS
#define FASTRIGHT
#define icpylng(dp,sp,n) 	*dp++ = *sp++; *dp++ = *sp++; *dp++ = *sp++; *dp++ = *sp++
#define mblllc(n,s)     	mballc(n,(UINT) (s))
#ifndef SIZEOF
#define SIZEOF 			sizeof
#endif
#ifndef ctPortWDARM
#ifndef ctPortWINKE
#define SYS_UINT
#endif
#define SYS_ULONG
#endif
#define ctRNDFILE
#define ctPATH_SEP		'\\'
typedef __int64 RNDFILE;
/*~***********************************/


/*^***********************************/
#ifdef ctSRVR
#define ctNO_OVERRIDE_FD_SETSIZE /* TCP/IP protocol: Do not adjust systems default for FD_SETSIZE */
#define ctSELECTthrd		
#define ctServerShell
#define ctSRV_DEFAULTCOMM	"F_TCPIP"
#endif
/*~***********************************/


/*^***********************************/
#if (defined(ctPortFAIRCOM_THREADS) || defined(ctPortNATIVE_THREADS))
#include "ctsthd.h"  /* FairCom System Threading Header */
#else
#define OWNER   (1)
#endif
/*~***********************************/

/*^***********************************/
/* #define rabSERVER_DLL_EXPERIMENT */
#ifdef  rabSERVER_DLL_EXPERIMENT
#ifdef ctSRVR
#define rbEXTERN_COMMENT extern
#define ctPortUSE_W32DATA_SEG
#endif
#endif
/*~***********************************/

#define ctMEMALIGN8

#define ctNoUnalignedLongs
#define ALIGNMENT_COMP  8

#define ct8P
#define SYS_LONG
#define SYS_ULONG
#define SYS_LONG8
typedef __int64 LONG8;
#define ctLLd           "%I64d"
#define ctLLu           "%I64u"
#define ctLLx           "%I64x"
#define ctLL03d         "%03I64d"
#define ctLL04d         "%04I64d"
#define ctLL05d         "%05I64d"
#define ctLL06d         "%06I64d"
#define ctLL12d         "%12I64d"

#ifdef  ctPortWINKE
#define _INC_MATH	/* prevent math.h from comming in */
#endif

#include "ctsysi.h" 	/* FairCom Server ctPortid header file */

#ifdef ctPortWINCE
#include "ctcrtlce.h"
#endif

#ifdef ctPortWDARM
#include "ctcrtlam.h"
#endif

#ifdef ctSQL_OVERRIDE_CAPACITIES
#include "ctsqlovr.h"							/* Override internal SQL Capacity Settings (#defines) */
#endif

/*^***********************************/
/*
** Atomic operation support for Windows
*/
#define ctInterlockedAcquireBarrier()
#define ctInterlockedReleaseBarrier()

#define ctInterlockedIncrement32(n) InterlockedIncrement(&n)
#define ctInterlockedDecrement32(n) InterlockedDecrement(&n)
#define ctInterlockedCompareExchange32(target, newval, curval) \
	(InterlockedCompareExchange(&target, newval, curval) == curval ? 1 : 0)

#define ctInterlockedCompareExchangeAdrOf32(target, newval, curval) \
	(InterlockedCompareExchange(target, newval, curval) == curval ? 1 : 0)
#define ctInterlockedCompareExchangeAdrOf64(target, newval, curval) \
	(InterlockedCompareExchange64(target, newval, curval) == curval ? 1 : 0)

#define ctInterlockedGet32(target) InterlockedAnd(&target, 0xffffffff)
#define ctInterlockedGetAdrOf32(target) InterlockedAnd(target, 0xffffffff)
#define ctInterlockedGet64(target) InterlockedAnd64(&target, (__int64)0xffffffffffffffff)

#define ctInterlockedIncrementAdrOf64(n) \
        InterlockedIncrement64(n)
#define ctInterlockedDecrementAdrOf64(n) \
        InterlockedDecrement64(n)

#ifndef NO_ctFeatATOMICop64
#if _MSC_VER > 1400
#define ctFeatATOMICop64
#endif
#endif
#define ctInterlockedIncrement64(n) InterlockedIncrement64(&n)
#define ctInterlockedDecrement64(n) InterlockedDecrement64(&n)
typedef __int64 AULONG8;

typedef DWORD AULONG;
#ifndef NO_ctFeatATOMICop
#define ctFeatATOMICop
#endif
/*~***********************************/

#endif /* ~ctCTCMPL */
/* end of ctcmpl.h */


