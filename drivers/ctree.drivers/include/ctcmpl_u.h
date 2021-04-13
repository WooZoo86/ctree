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

#ifndef ctCTCMPL_U
#define ctCTCMPL_U

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#ifdef ctPortLINUX
#include <time.h>
#endif

#include "ctvers.h"

#ifndef ctPortHPUX11
#ifndef ctPortQNXRTP
extern int errno;
#endif
#endif

#define ctHAS_GETPASS

#ifdef ctHAS_GETPASS
#include <pwd.h>
#include <unistd.h>
#endif

/*
** We now use memmove() to ensure correct results when the source and
** destination regions overlap.
*/
#define cpy4bf(dp,sp)    	memmove(dp,sp,4)
#define cpybig(dp,sp,n)	 	memmove(dp,sp,(UINT) (n))
#define cpybuf(dp,sp,n)  	memmove(dp,sp,(UINT) (n))
#define cpylng(dp,sp,n)  	cpy4bf(dp,sp)
#define cpylodl(hdp,sp,n) 	cpylod(hdp,sp,(UINT) (n))
#define cpymbuf			cpybuf
#define cpymsg			cpybuf
#define cpysrcl(dp,hsp,n) 	cpysrc(dp,hsp,(UINT) (n))
#define cpysrcm			cpysrcl
#define ct_NULL			0L
#define ctbfill(dp,ch,n) 	memset(dp,ch,(UINT) (n))
#define ctCONV
#define ctDECL
#define ctDECLT
#define ctEXCLCREAT
#define ctEXPORT
#define ctLOKCNT
#define ctMEM
#define ctmfill			ctbfill
#define ctPortUNIX
#define ctPATH_SEP		'/'
#define ctrt_fclose		fclose
#define ctrt_filcmp		strcmp
#define ctrt_filncmp		strncmp
#define ctrt_fgets		fgets
#define ctrt_ftell		ftell
#define ctrt_scanf		scanf
#ifdef ctHUGEFILE
#ifdef ctNO_64BIT_FILE
#define ctrt_fopen		fopen
#define ctrt_freopen		freopen
#else
#define ctrt_fopen		fopen64
#define ctrt_freopen		freopen64
#endif
#else	/* ~ctHUGEFILE */
#define ctrt_fopen		fopen
#define ctrt_freopen		freopen
#endif	/* ~ctHUGEFILE */
#define ctrt_fprintf		fprintf
#define ctrt_fscanf		fscanf
#define ctrt_getcwd		ctGetCwd
#define ctrt_memchr		memchr
#define ctrt_memcmp		memcmp
#define ctrt_memset		memset
#define ctrt_qsort		qsort
#define ctrt_bsearch		bsearch

#ifndef ctPortMACOSX_COCOA
extern ctCONV int ctrt_printf( const char *fmt, ... );
#endif

#ifdef PROTOTYPE
extern ctCONV void  	ctDECL	ctrt_exit( int ret );
#else
extern ctCONV void  	ctDECL	ctrt_exit();
#endif

#ifndef ctrt_snprintf
#define ctrt_snprintf		snprintf
#endif
#define ctrt_vsprintf		vsprintf
#define ctrt_sprintf		sprintf
#define ctrt_strcat		strcat
#define ctrt_strncat		strncat
#define ctrt_strcmp		strcmp
#define ctrt_strcpy		strcpy
#define ctrt_strlen		strlen
#define ctrt_strncmp		strncmp
#define ctrt_strncpy		strncpy
#define ctrt_strstr		strstr

#ifndef ctrt_tmpnam
#define ctrt_tmpnam		tmpnam
#endif

/* string operations with buffer size limits */
#define ctcr_sprintf		snprintf
#define ctcr_vsprintf		vsnprintf

#include <ctype.h>
#define ctrt_toupper		toupper

#ifndef ctPortMACOSX
#ifndef ctPort386BSD
#ifndef ctPortNETBSD386
#ifndef ctPortLINUX
#ifndef ctrt_gets
#define ctrt_gets		gets
#endif
#endif
#endif
#endif
#endif

#define ctsfill(dp,ch,n) 	memset(dp,ch,(UINT) (n))
#define fnCTSBLD
#define icpylng(dp,sp,n) 	*dp++ = *sp++; *dp++ = *sp++; *dp++ = *sp++; *dp++ = *sp++
#define mblllc(n,s)	 	mballc(n,(UINT) (s))
#define PERC_HD
#define FASTRIGHT   /* Use memmove right shifts */

#ifndef SIZEOF
#define SIZEOF 			sizeof
#endif

/*^***********************************/
#ifdef ctSRVR
#define ctDaemon    		become_daemon
#define ctMILLISECOND(t)	(t < 1 ? 0 : (t + 16) / 17)
#define ctUnixLaunch

#ifndef ctSRV_DEFAULTCOMM
#ifdef  ctSELECTthrd
#define ctSRV_DEFAULTCOMM	"FSTCPIP"
#else
#define ctSRV_DEFAULTCOMM	"F_TCPIP"
#endif
#endif  /* ctSRV_DEFAULTCOMM */

#else /* ~ctSRVR */

#ifndef ctBNDSRVR
#define ctNOEXCL 
#endif	

#endif /* ~ctSRVR */
/*~***********************************/


/*^***********************************/
#ifdef ctSRVR
#ifdef	ctSAVEunxFS
#ifndef	ctSAVEunxOC
/* 
Here we support the unxFS as the default, yet allow unxOC to override
with the COMPATIBILITY keyword. See ctsave.c for more info.
*/
#define ctSAVEunxOC
#endif
#endif
#endif
/*~***********************************/


/*^***********************************/
#define COMMIT_DELAY (-1L)
#ifdef	ctPortNATIVE_THREADS
#ifdef	ctSAVEunxFS
#undef  COMMIT_DELAY
#define COMMIT_DELAY (1000L)
#endif
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
/*
** Atomic operation support for Solaris
*/
#if defined(ctPortSOL386) || defined(ctPortSOLARIS10)
#ifndef ctPortSOLARIS_V5_9_OR_BEFORE
#include <sys/atomic.h>

/* 
 * NOTE: Most of these operations on Solaris do NOT guarantee a memory barrier/fence.
 * Using these primitives to provide an ordering of operations
 * requires explicit barriers. On modern SPARC and x86-64 hardware the memory barrier 
 * is not required.
 */
 
#define ctInterlockedAcquireBarrier() /* membar_enter() ifneeded */
#define ctInterlockedReleaseBarrier() /* membar_exit() ifneeded */

#define ctInterlockedIncrement32(n) atomic_inc_32_nv((volatile uint32_t *)&n)
#define ctInterlockedDecrement32(n) atomic_dec_32_nv((volatile uint32_t *)&n)
#define ctInterlockedCompareExchange32(target, newval, curval) \
	(atomic_cas_32((volatile uint32_t *)&(target), curval, newval) == curval ? 1 : 0)
#define ctInterlockedCompareExchangeAdrOf32(target, newval, curval) \
	(atomic_cas_32((volatile uint32_t *)(target), curval, newval) == curval ? 1 : 0)
#define ctInterlockedCompareExchangeAdrOf64(target, newval, curval) \
	(atomic_cas_64((volatile uint64_t *)(target), curval, newval) == curval ? 1 : 0)

#define ctInterlockedGet32(target) atomic_and_32_nv((volatile uint32_t *)&(target), 0xffffffff)
#define ctInterlockedGetAdrOf32(target) atomic_and_32_nv((volatile uint32_t *)(target), 0xffffffff)
#define ctInterlockedGet64(target) atomic_and_64_nv((volatile uint64_t *)&(target), (uint64_t)0xffffffffffffffff)

#define ctFeatATOMICop64
#define ctInterlockedIncrement64(n) atomic_inc_64_nv((volatile uint64_t *)&n)
#define ctInterlockedDecrement64(n) atomic_dec_64_nv((volatile uint64_t *)&n)
#define ctInterlockedIncrementAdrOf64(n) atomic_inc_64_nv((volatile uint64_t *)(n))
#define ctInterlockedDecrementAdrOf64(n) atomic_dec_64_nv((volatile uint64_t *)(n))
typedef uint64_t AULONG8;

typedef uint32_t AULONG;
#define ctFeatATOMICop
#endif
#endif
/*~***********************************/

/*^***********************************/
/*
** Atomic operation support for Linux
*/
#ifdef ctPortLINUX
#ifndef ctPort_LINUX_KERNEL_V2_4 /* No atomic operation support on Linux kernel before version 2.4 */
#ifndef ctPortFREEBSD8 /* No atomic operation support on FreeBSD8 */

#if defined(ctPortLINUX_RISC) && !defined(ct8P)
/* No gcc atomic support on 32-bit Linux RISC. */
#define NO_GCC_ATOMIC
#ifndef ctUSE_GLIB_2_0	/* still need ctUSE_GLIB_2_0 so the client shared memory works. */
#define ctUSE_GLIB_2_0
#endif
#endif

/* 
In order to allow various build on older Linix machines, we only support the
enhanced built-in atomic functions when the GNU compiler is GCC compiler 4.1.0
and later
*/
#if (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 1))
#ifndef NO_GCC_ATOMIC
#define NO_GCC_ATOMIC
#endif
#ifndef NO_ctFeatATOMICop64
#define NO_ctFeatATOMICop64
#endif
#endif
	
/* When compiling v11.6.0 and later with the GCC compiler 4.1.0 and later,
use GCC's built-in atomic functions instead of glib's atomic functions. */
#if ctVER3_GE(11,6,0) && (__GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 1))) && !defined(NO_GCC_ATOMIC)

#define ctInterlockedAcquireBarrier()
#define ctInterlockedReleaseBarrier()

#define ctInterlockedGet32(n)			__sync_add_and_fetch(&(n),0)
#define ctInterlockedGetAdrOf32(n)		__sync_add_and_fetch((n),0)
#define ctInterlockedIncrement32(n)		__sync_add_and_fetch(&(n),1)
#define ctInterlockedDecrement32(n)		__sync_add_and_fetch(&(n),-1)
#define ctInterlockedCompareExchange32(target, newval, curval) \
	__sync_bool_compare_and_swap(&(target), curval, newval)
#define ctInterlockedCompareExchangeAdrOf32(target, newval, curval) \
	__sync_bool_compare_and_swap(target, curval, newval)

#ifdef ctN8
#define ctFeatATOMICop64
#define ctInterlockedGet64(n)			__sync_add_and_fetch(&(n),0)
#define ctInterlockedIncrement64(n)		__sync_add_and_fetch(&(n),1)
#define ctInterlockedDecrement64(n)		__sync_add_and_fetch(&(n),-1)
#define ctInterlockedIncrementAdrOf64(n)	__sync_add_and_fetch((n),1)
#define ctInterlockedDecrementAdrOf64(n)	__sync_add_and_fetch((n),-1)
#define ctInterlockedCompareExchangeAdrOf64(target, newval, curval) \
	__sync_bool_compare_and_swap(target, curval, newval)
typedef unsigned long long AULONG8;
#endif

typedef unsigned int AULONG;
#define ctFeatATOMICop

#elif (defined(ctSRVR) || defined(ctBNDSRVR) || defined(ctPortRTG) || defined(ctUSE_GLIB_2_0))
/*
** We enable support for atomic operations on Linux as needed,
** because the functions that we use require linking with the glib-2.0 library.
** except we turn it on for all for RTG because of BTRV MT Client atomic needs.
** ctUSE_GLIB_2_0 is used by client compiles for shared memory.
*/

#include <glib.h>

#define ctInterlockedAcquireBarrier()
#define ctInterlockedReleaseBarrier()

#define ctInterlockedIncrement32(n) (g_atomic_int_exchange_and_add((gint *)&n, 1) + 1)
#define ctInterlockedDecrement32(n) (g_atomic_int_exchange_and_add((gint *)&n, -1) - 1)
#define ctInterlockedCompareExchange32(target, newval, curval) \
	g_atomic_int_compare_and_exchange((gint *)&(target), curval, newval)
#define ctInterlockedCompareExchangeAdrOf32(target, newval, curval) \
	g_atomic_int_compare_and_exchange((gint *)target, curval, newval)

#define ctInterlockedGet32(target) g_atomic_int_get((gint *)&(target))
#define ctInterlockedGetAdrOf32(target) g_atomic_int_get((gint *)(target))

/*
** On Linux we only support 64-bit atomic increment and decrement for 64-bit
** compiles because we use the pointer functions.
*/
#if defined(ct8P) && !defined(NO_ctFeatATOMICop64)
#define ctFeatATOMICop64
#define ctInterlockedGet64(n)			(AULONG8) g_atomic_pointer_get(&n)
#define ctInterlockedIncrement64(n)		(g_atomic_pointer_add(&n, 1) + 1)
#define ctInterlockedDecrement64(n)		(g_atomic_pointer_add(&n, -1) - 1)
#define ctInterlockedIncrementAdrOf64(n)	(g_atomic_pointer_add(n, 1) + 1)
#define ctInterlockedDecrementAdrOf64(n)	(g_atomic_pointer_add(n, -1) - 1)
#define ctInterlockedCompareExchangeAdrOf64(target, newval, curval) \
	g_atomic_pointer_compare_and_exchange(target, curval, newval)
typedef unsigned long long AULONG8;
#endif

typedef gint AULONG;
#define ctFeatATOMICop

#else
/* Server model supports atomic operations. */
#define ctFeatATOMICopSRVR
#endif
#endif /* ~ctPortFREEBSD8 */
#endif /* ~ctPort_LINUX_KERNEL_V2_4 */
#endif /* ctPortLINUX */
/*~***********************************/

/*^***********************************/
/*
** Atomic operation support for Mac OS X
*/
#ifdef ctPortMACOSX

#include <libkern/OSAtomic.h>

#define ctInterlockedAcquireBarrier()
#define ctInterlockedReleaseBarrier()

#define ctInterlockedIncrement32(n) OSAtomicIncrement32Barrier((int32_t *)&n)
#define ctInterlockedDecrement32(n) OSAtomicDecrement32Barrier((int32_t *)&n)
#define ctInterlockedCompareExchange32(target, newval, curval) \
	OSAtomicCompareAndSwap32Barrier(curval, newval, (int32_t *)&(target))
#define ctInterlockedCompareExchangeAdrOf32(target, newval, curval) \
	OSAtomicCompareAndSwap32Barrier(curval, newval, (int32_t *)(target))

#define ctInterlockedGet32(target) \
	OSAtomicAnd32Barrier(0xffffffff, (uint32_t *)&(target))
#define ctInterlockedGetAdrOf32(target) \
	OSAtomicAnd32Barrier(0xffffffff, (uint32_t *)(target))

/*
** Mac OS X Supports 64-bit atomic operations except for 32-bit PPC compiles.
*/
#if defined(__ppc64__) || defined(__i386__) || defined(__x86_64__)
#define ctFeatATOMICop64
#define ctInterlockedCompareExchangeAdrOf64(target, newval, curval) \
	OSAtomicCompareAndSwap64Barrier(curval, newval, (int64_t *)(target))
#define ctInterlockedGet64(target) \
	OSAtomicAdd64Barrier(0, (int64_t *)&(target))
#define ctInterlockedIncrement64(n) OSAtomicIncrement64Barrier((int64_t *)&n)
#define ctInterlockedDecrement64(n) OSAtomicDecrement64Barrier((int64_t *)&n)
#define ctInterlockedIncrementAdrOf64(n) OSAtomicIncrement64Barrier((int64_t *)n)
#define ctInterlockedDecrementAdrOf64(n) OSAtomicDecrement64Barrier((int64_t *)n)
typedef int64_t AULONG8;
#endif

typedef int32_t AULONG;
#define ctFeatATOMICop

#endif
/*~***********************************/

/*^***********************************/
/*
** Atomic operation support for AIX
*/
#ifdef ctPortRS6000

#include <sys/atomic_op.h>

/* 
 * WARNING: Most of these operations on AIX do NOT use barriers/fences. 
 * Using these primitives to provide an ordering of operations requires
 * explicit barriers.  (aix_ctInterlockedCompareExchangeXX includes a barrier)
 */

#define ctInterlockedAcquireBarrier() __lwsync()  /* lwsync is a full fence */
#define ctInterlockedReleaseBarrier() __lwsync()

#define ctInterlockedIncrement32(n) (fetch_and_add((atomic_p)&n, 1) + 1)
#define ctInterlockedDecrement32(n) (fetch_and_add((atomic_p)&n, -1) - 1)
#define ctInterlockedCompareExchange32(target, newval, curval) \
	aix_ctInterlockedCompareExchange32((AULONG *)&(target), newval, (LONG)(curval))
#define ctInterlockedCompareExchangeAdrOf32(target, newval, curval) \
	aix_ctInterlockedCompareExchange32((AULONG *)target, newval, (LONG)(curval))
#ifdef ct8P
#define ctInterlockedCompareExchangeAdrOf64(target, newval, curval) \
	aix_ctInterlockedCompareExchange64((AULONG8 *)target, newval, (LONG8)(curval))
#endif

#define ctInterlockedGet32(target) \
	fetch_and_and((AULONG *)&(target), 0xffffffff)
#define ctInterlockedGetAdrOf32(target) \
	fetch_and_and((AULONG *)(target), 0xffffffff)
#define ctInterlockedGet64(target) \
	fetch_and_andlp((AULONG8 *)&(target), 0xffffffffffffffffULL)

/*
** On AIX we only support 64-bit atomic increment and decrement for 64-bit
** compiles because fetch_and_addlp() only operates on a 64-bit value in a
** 64-bit compile.
*/
#ifdef ct8P
#define ctFeatATOMICop64
#define ctInterlockedIncrement64(n) (fetch_and_addlp((atomic_l)&n, 1) + 1)
#define ctInterlockedDecrement64(n) (fetch_and_addlp((atomic_l)&n, -1) - 1)
#define ctInterlockedIncrementAdrOf64(n) (fetch_and_addlp((atomic_l)n, 1) + 1)
#define ctInterlockedDecrementAdrOf64(n) (fetch_and_addlp((atomic_l)n, -1) - 1)
typedef long AULONG8;
#endif

typedef int AULONG;
#define ctFeatATOMICop

#endif
/*~***********************************/

/*^***********************************/
/*
** Atomic operation support for FreeBSD 8 and later
*/
#ifdef ctPortFREEBSD8
#include <machine/atomic.h>

/* 
 * NOTE: Most of these operations on FreeBSD do NOT guarantee barriers/fences. 
 * Using these primitives to guarantee an ordering of operations requires
 * explicit barriers on some hardware.
 */
#define ctInterlockedAcquireBarrier() /* rmb() ifneeded */
#define ctInterlockedReleaseBarrier() /* wmb() ifneeded */

#define ctInterlockedIncrement32(n) (atomic_fetchadd_32((volatile u_int *)&(n), 1) + 1)
#define ctInterlockedDecrement32(n) (atomic_fetchadd_32((volatile u_int *)&(n), -1) - 1)
#define ctInterlockedCompareExchange32(target, newval, curval) \
	atomic_cmpset_32((volatile u_int *)&(target), curval, newval)
#define ctInterlockedCompareExchangeAdrOf32(target, newval, curval) \
	atomic_cmpset_32((volatile u_int *)(target), curval, newval)

#define ctInterlockedGet32(target) atomic_load_acq_int((volatile u_int *)&(target))
#define ctInterlockedGetAdrOf32(target) atomic_load_acq_int((volatile u_int *)(target))

#ifdef ct8P
#define ctFeatATOMICop64
#define ctInterlockedCompareExchangeAdrOf64(target, newval, curval) \
	atomic_cmpset_64((volatile u_long *)(target), curval, newval)
#define ctInterlockedGet64(target) atomic_load_acq_long((volatile u_long *)&(target))
#define ctInterlockedIncrement64(n) (atomic_fetchadd_long((volatile u_long *)&(n), 1) + 1)
#define ctInterlockedDecrement64(n) (atomic_fetchadd_long((volatile u_long *)&(n), -1) - 1)
#define ctInterlockedIncrementAdrOf64(n) (atomic_fetchadd_long((volatile u_long *)(n), 1) + 1)
#define ctInterlockedDecrementAdrOf64(n) (atomic_fetchadd_long((volatile u_long *)(n), -1) - 1)
typedef long long AULONG8;
#endif

typedef int AULONG;
#define ctFeatATOMICop

#endif
/*~***********************************/

/*^***********************************/
/*
** Atomic operation support Not Yet Implemented
*/
#ifndef ctFeatATOMICop

#define AULONG ULONG

#endif
/*~***********************************/

#endif /* ~ctCTCMPL_U */
/* end ctcmpl_u.h */
