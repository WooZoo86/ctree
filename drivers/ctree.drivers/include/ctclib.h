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

/*^***********************************/
#ifdef ctPortNLM

#define  ctNLM_SYS_TYPES_H	<nlm/sys/types.h>
#define  ctNLM_SYS_STAT_H	<nlm/sys/stat.h>
#define  ctNLM_FCNTL_H		<nlm/fcntl.h>
#define  ctNLM_ERRNO_H		<nlm/errno.h>
#define  ctNLM_SYS_STAT_H	<nlm/sys/stat.h>
#include ctNLM_SYS_TYPES_H
#include ctNLM_SYS_STAT_H
#include ctNLM_FCNTL_H
#include ctNLM_ERRNO_H
#include ctNLM_SYS_STAT_H
#include <time.h>
#define ctNWSEMAPH_H	<nwsemaph.h>
#include ctNWSEMAPH_H
#ifdef N_PLAT_NLM
#define ctNWERRNO_H	<nwerrno.h>
#include ctNWERRNO_H
#endif
#define ctNWSIGNAL_H	<nwsignal.h>
#include ctNWSIGNAL_H
#define ctNWFATTR_H	<nwfattr.h>
#include ctNWFATTR_H

/* start - <nwnamspc.h> has GLOBAL define conflict */
#ifdef  GLOBAL
#define MYTMP_GLOBAL GLOBAL
#undef  GLOBAL
#endif

#define ctNWNAMSPC_H	<nwnamspc.h>
#include ctNWNAMSPC_H

#ifdef MYTMP_GLOBAL
#ifdef  GLOBAL
#undef  GLOBAL
#define GLOBAL	MYTMP_GLOBAL
#undef	MYTMP_GLOBAL
#endif
#endif
/* end - nwnamspc has GLOBAL define conflict */


#include <stdarg.h>
#ifdef LONG
#undef LONG
#endif

#endif /* ctPortNLM */
/*~***********************************/


/*^***********************************/
#ifdef ctPortUNIX

#ifndef ctPortVINES
#include <sys/types.h>


#ifdef ctPortLYNXOS386
#define ctTIME_H	<time.h>
#else
#define ctTIME_H	<sys/time.h>
#endif
#include ctTIME_H


#include <fcntl.h>
#endif 

#include <signal.h>
#include <errno.h>
#define ctUNISTD_H	<unistd.h>
#include ctUNISTD_H
#ifndef ctPortHPUX11
extern int errno;
#endif
#endif /* ctPortUNIX */
/*~***********************************/


/*^***********************************/
#ifndef ctPortMAC
#ifndef ctPortNLM
#ifndef ctPortUNIX
#ifndef ctPortWINCE
#ifndef ctPortWDARM
#include <fcntl.h>
#include <sys\types.h>		
#include <sys\stat.h>
#ifndef ctPortCW8W32 /* Code Warrior 8 W32 */
#include <share.h>		
#if (!(defined ctPortOS2) && !(defined ctPortDJGPPDOS))
#include <sys\locking.h>	
#endif
#endif /* ~ctPortCW8W32 */
#include <io.h>  
#include <direct.h>
#include <errno.h>		   
#include <time.h>
#include <stdarg.h>
#include <limits.h>
#endif /* ~ctPortWDARM */
#endif /* ~ctPortWINCE */
#endif /* ~ctPortUNIX */
#endif /* ~ctPortNLM */
#endif /* ~ctPortMAC */
/*~***********************************/


/*^***********************************/
#ifdef ctPortOS2
#define INCL_BASE
#define INCL_DOS
#define INCL_DOSFILEMGR
#define INCL_DOSSEMAPHORES
#define ctOS2_H	<os2.h>
#include ctOS2_H
#include <signal.h>
#endif
/*~***********************************/


/*^***********************************/
#ifdef ctPortWIN16
/* these temp buffers are used by several functions and are declared here */
/* so that they will have a segment address of DS and not SS */
char TempBuf[MAX_NAME], TempBuf1[MAX_NAME];
HANDLE hInst;                /* handle to c-tree instance */

#include <stdlib.h>

#define HA_OFFSET(vp)	((((UCOUNT far *) &(vp)))[0])
#define HA_SELCTR(vp)	((((UCOUNT far *) &(vp)))[1])
#define BLOCK		((UCOUNT) 63488)
#endif /* ctPortWIN16 */
/*~***********************************/


/*^***********************************/
#ifdef ctPortDOS
#define HA_OFFSET(vp)	((((UCOUNT *) &(vp)))[0])
#define HA_SELCTR(vp)	((((UCOUNT *) &(vp)))[1])
#define BLOCK		((UCOUNT) 63488)
#endif /* ctPortDOS */
/*~***********************************/


/*^***********************************/
#ifdef ctPortMAC
#define ctFILES_H <files.h>
#define ctERRORS_H <errors.h>
#define ctDIALOGS_H <Dialogs.h>
#define ctOSUTILS_H <OSUtils.h>
#define ctMEMORY_H <memory.h>
#define ctFONTS_H <fonts.h>
#define ctMENUS_H <Menus.h>
#define ctDEVICES_H <Devices.h>
#define ctEVENTS_H <Events.h>
#define ctSOUND_H <Sound.h>
#define ctSEGLOAD_H <SegLoad.h>
#define ctTYPES_H <types.h>
#define ctGESTALT_H <Gestalt.h>
#define ctQUICKDRAW_H <quickdraw.h>
#define ctSTDARG_H <stdarg.h> 
#define ctSTDLIB_H <stdlib.h> 
#define ctSHUTDOWN_H <ShutDown.h>
#include ctFILES_H
#include ctFILES_H
#include ctDIALOGS_H
#include ctOSUTILS_H
#include ctMEMORY_H
#include ctFONTS_H
#include ctMENUS_H
#include ctDEVICES_H
#include ctEVENTS_H
#include ctSOUND_H
#include ctSEGLOAD_H
#include ctTYPES_H
#include ctGESTALT_H
#include ctQUICKDRAW_H
#include ctSTDARG_H
#include ctSTDLIB_H
#include ctSHUTDOWN_H

#define TimeLM 0x20C		/*[GLOBAL VAR] Time has name conflict w/ type. Clock time (extrapolated) [long]*/
#define SH_DENYNO (1)
#define SH_DENYWR (2)
#define SH_DENYRW (4)

#ifndef ctPortMAC_MSCX_SRVR	/* Microsoft VC++ Mac XCross compiler */
extern int errno;
#endif

extern	pTEXT	pfcstr(pTEXT c,pTEXT p,NINT n);
extern	COUNT	myMACsopen(pTEXT afilnam,COUNT acflag,COUNT shflag);
extern	COUNT	sopenWithType(pTEXT afilnam,COUNT acflag,COUNT shflag,ULONG type,ULONG creator);
extern	COUNT	doCreate(pTEXT pname,COUNT vRefNum,ULONG type,ULONG creator);
extern	COUNT	doCloseMac(COUNT xfd);
extern	NINT	fcloseMac(pFILE stream);
extern	pFILE	fopenMac(pTEXT filename,pTEXT mode);
extern	COUNT	setfposMac(pFILE file,VRLEN pos,NINT mode);
extern	pTEXT	strcatMac(pTEXT dp,pTEXT sp);
extern	pTEXT	strcpyMac(pTEXT dp,pTEXT sp);
extern	pTEXT	strncpyMac(pTEXT dp,pTEXT sp,VRLEN n);
extern	pTEXT	memsetMac(pTEXT dp,NINT ch,VRLEN n);
extern	NINT	strcmpMac(pTEXT s1,pTEXT s2);
extern	NINT	strncmpMac(pTEXT s1,pTEXT s2,VRLEN n);
extern	NINT	memcmpMac(pTEXT s1,pTEXT s2,VRLEN n);
extern	pTEXT	memcpyMac(pTEXT s1,pTEXT s2,VRLEN n);
extern	NINT	strlenMac(pTEXT s);
extern	NINT	printfMac(pTEXT format,...);
extern	NINT	fprintfMac(pFILE stream,pTEXT format,...);
extern	NINT	sprintfMac(pTEXT stream,pTEXT format,...);
extern	LONG	getone(pTEXT buf,pVRLEN left,pFILE stream,NINT skiplead);
extern	NINT	fscanfMac(pFILE stream,pTEXT format,...);
extern	NINT	sscanfMac(pTEXT stream,pTEXT format,...);
extern  NINT	ctMACgetcwd(pTEXT cwd,NINT maxlen);
extern	VOID	exitMac(NINT status);
extern	pVOID	memoryMac(ULONG nbr,ULONG size);
extern	VOID	memoryfreeMac(pTEXT p);
extern	pTEXT	tmpnamMac(pTEXT newname);
extern	NINT	toupperMac(NINT c);
extern	VOID	alertMac(COUNT icon,COUNT err,pTEXT msg,VRLEN len);
extern	VRLEN	macDoPrint(pTEXT *orig,pTEXT format,va_list args);
extern	LONG	fstoiMac(pTEXT buf,pVRLEN left,pFILE stream,NINT base);
extern	LONG	stoiMac(FAST pTEXT *instr,NINT base);
extern	pTEXT	ltosMac(ULONG n,pTEXT buf,NINT base);
extern	pTEXT 	setMemHdr(pTEXT p, Handle h);
extern  COUNT	myMacio(COUNT op_code,RNDFILE cfd,LONG recbyt,pVOID bufadr,VRLEN iosize,pLONG pretsiz);
extern 	COUNT	myMAClockf(COUNT filno,COUNT lmode,ULONG recbyt,ULONG siglen);
extern	COUNT	DosBufReset(COUNT ref);
#endif /* ctPortMAC */
/*~***********************************/


/****************************************************************************/
/* ctclib prototypes */
#ifdef PROTOTYPE

/* ctsthd.c */
#ifndef ctFeatPOSIXSIGNALS
extern VOID killsrvr(NINT);
#endif
extern VOID stopsrvr(NINT);

/* ctsfio.c */
extern NINT ctGetCwd(pTEXT cwd, NINT buflen);
extern NINT ctFileAccess(pTEXT filnam);

/* ctsdos.c */
#ifdef ctPort16BIT
pTEXT mblllc(NINT numobj,VRLEN sizobj);
VOID cthfree(pVOID p);
VOID ctbfill(pVOID dp,NINT ch,VRLEN n);
pTEXT bigadr(pTEXT tp,VRLEN offset);
void cpybig(pTEXT dp,pTEXT sp,VRLEN n);
VOID cpylodl(ppTEXT hdp,pVOID sp,VRLEN n);
VOID cpysrcl(pVOID dp,ppTEXT hsp,VRLEN n);
static UINT doio(NINT op_code,NINT cfd,pVOID bufadr,UINT len);
VRLEN comparu(pTEXT np,pTEXT op,VRLEN remlen);
NINT CTCFILL( pTEXT tp, NINT ch, UINT len );
#ifdef ctPortWIN16
ctCONV BOOL ctDECL ViewCtreeError( HWND hWnd );
#endif
#endif /* ctPort16BIT */

#endif /* PROTOTYPE */

#ifndef PROTOTYPE
extern VOID killsrvr();
extern VOID stopsrvr();
extern NINT ctGetCwd();
extern NINT ctFileAccess();
#endif

#ifdef ctSRVR
#ifndef ctFeatSNAPSHOT
extern LONG ct_compflg;
extern LONG ct_compflg2;
extern LONG ct_diagflg;
#endif
#endif

/****************************************************************************/

/* end of ctclib.h */
