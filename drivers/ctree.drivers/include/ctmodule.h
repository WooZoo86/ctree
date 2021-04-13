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
#ifdef _WIN32

#ifdef UNICODE
#define ctLoadLib(l)               LoadLibraryA(l)
#else /* ~UNICODE */
#define ctLoadLib(l)               LoadLibrary(l)
#endif /* ~UNICODE */
#define ctFreeLib(h)               (0 == FreeLibrary((HMODULE)h))
#define ctGetFunc(h,f,p)           (p = (void *)GetProcAddress((HINSTANCE)h,f))
  
#else  /* ~_WIN32 */

/* If compiling with gcc 3.2.2 on HP/UX 11: */
#ifdef HPUX
#if ((__GNUC__ == 3) && (__GNUC_MINOR__ == 2) && (__GNUC_PATCHLEVEL__ == 2))
/*
** Use shl_load(), shl_unload(), and shl_findsym() instead of
** dlopen(), dlclose(), and dlsym().
*/
#define ctUSE_SHL_FUNC
#endif
#endif

#ifdef ctUSE_SHL_FUNC

#include <dl.h>
#define ctLoadLib(l)            shl_load(l,BIND_IMMEDIATE,0L)
#define ctFreeLib(h)            shl_unload(h)
#define ctGetFunc(h,f,p)        (0==shl_findsym(h,f,TYPE_PROCEDURE,&p))

#else  /* ~ctUSE_SHL_FUNC */

#include <dlfcn.h>
#define ctLoadLib(l)            dlopen(l,RTLD_NOW)
#define ctFreeLib(h)            dlclose(h)
#define ctGetFunc(h,f,p)        (p = (void *)dlsym(h,f))

#endif /* ~ctUSE_SHL_FUNC */

#endif /* ~_WIN32 */

