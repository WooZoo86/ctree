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

#ifndef ctPORTH
#define ctPORTH

/*
** ctport.h depends on some ctFeat options but NOT on those in ctopt2.h
** It does NOT depend on the major
** configuration options (such as ctHUGEFILE, TRANPROC, UNIFRMAT, LOW_HIGH,
** ctSRVR, or ctCLIENT), ctBEHAV options.
*/

#include "ctlfun.h"

#ifndef MAXLEN
#define MAXLEN		1024	/* maximum key length			*/
#endif
#if (MAXLEN > 255)
#define MAXLEN_GT_255
#endif

#define PERFORM_OFF	0
#define PERFORM_ON	1
#define PERFORM_DUMP	2

#ifdef ctFeatLegacyregister
#ifndef FAST
#define	FAST	register    			/* register variable	   */
#endif
#ifndef PFAST
#define PFAST	register			/* register parameter	   */
#endif
#else /*ctFeatLegacyregister*/
#ifdef FAST
#undef FAST
#endif
#ifdef PFAST
#undef PFAST
#endif
#define FAST
#define PFAST
#endif /*~ctFeatLegacyregister*/

#undef EXTERN
#define	EXTERN	extern				/* External variable	   */
#ifndef rbEXTERN_COMMENT
#define rbEXTERN_COMMENT /* */
#endif
#define	LOCAL	static				/* Local to module	   */

#ifndef ctINLINE
#ifdef _MSC_VER /* Microsoft Visual Studio compiler */
#define ctINLINE _inline
#else
#if (defined(ctPortRS6000) || defined(ctPortHP9000))
#define ctINLINE
#else
#define ctINLINE inline
#endif
#endif
#endif

#ifdef ctBAN5 /* Banyan 5.5 toolkit */
#undef VOID 
#endif

#define VOID	void

#ifndef ctEXPORT
#define ctEXPORT
#endif

#ifndef ctCONST
#define ctCONST const
#endif

typedef VOID ctMEM *	pVOID;
typedef ctCONST void ctMEM *	cpVOID;
typedef VOID ctMEM * ctMEM *	ppVOID;
typedef short int	COUNT;
typedef COUNT ctMEM *	pCOUNT;
typedef COUNT ctMEM * ctMEM *	ppCOUNT;
typedef unsigned short int	UCOUNT; /* some 16 bit compilers might  */
typedef UCOUNT ctMEM *	pUCOUNT;
				/* require unsigned int instead */
#ifndef SYS_NINT
typedef int		NINT;	/* natural integer */
#endif
#ifndef SYS_UINT
typedef unsigned int	UINT;
#endif

typedef NINT ctMEM *	pNINT;
typedef NINT ctMEM * ctMEM *	ppNINT;
typedef UINT ctMEM *	pUINT;

#ifdef ctPortWIN64
/* Win64's long int is 32 bits, but we want  */
/* NLONG/UNLONG to be the size of a pointer. */
typedef __int64		 NLONG;
typedef unsigned __int64 UNLONG;
#else
typedef long int	NLONG;
typedef unsigned long	UNLONG;
#endif
typedef NLONG ctMEM *  pNLONG;
typedef UNLONG ctMEM * pUNLONG;

#ifndef SYS_LONG
#ifndef LONG
typedef long int	LONG;
#endif
#endif
typedef LONG ctMEM *	pLONG;
typedef LONG ctMEM **	ppLONG;

#ifndef SYS_ULONG
#ifndef ULONG
typedef unsigned long	ULONG;
#endif
#endif
typedef ULONG ctMEM *	pULONG;

#ifdef SYS_LONG8
#define ctN8		/* special 8-byte integer compiler support */
#else
#ifndef LONG8
#ifdef ct8P
typedef long long	LONG8;
#define ctN8		/* native 8-byte integer compiler support */
#define ctLLd		"%lld"
#define ctLLx		"%llx"
#define ctLL03d		"%03lld"
#define ctLL04d         "%04lld"
#define ctLL05d         "%05lld"
#define ctLL06d         "%06lld"
#define ctLL12d		"%12lld"
#else
typedef LONG		LONG8[2];
#endif
#endif
#endif
typedef LONG8 ctMEM *	pLONG8;

#ifdef ctN8 /* native 8-byte integer compiler support */

#ifdef ctPortWIN32
typedef unsigned __int64	  ULONG8;
#else
typedef unsigned long long	  ULONG8;
#endif

#else  /* ~ctN8 */
typedef ULONG		ULONG8[2];
#endif /* ~ctN8 */

typedef  ULONG8 *		 pULONG8;
typedef pULONG8 *		ppULONG8;

#ifdef ctChkSysThidMtx
#ifdef ctPortWIN32
typedef UNLONG		THID;
#else
typedef pthread_t	THID;
#endif
#endif

#ifdef ctFeatCFG_SCALE
#ifdef ctN8
#define ctFeatCFG_SCALE_N8
#endif
#endif

#ifndef ctLLd
#define ctLLd		"%ld"
#endif
#ifndef ctLLx
#define ctLLx		"%lx"
#endif
#ifndef ctLL12d
#define ctLL12d		"%12ld"
#endif

#ifndef ctLLu
#ifdef ctPortWIN32
#define ctLLu		"%I64u"
#else
#define ctLLu		"%llu"
#endif
#endif

#ifdef ctPortWIN32
#define ctLLnd(n)       "%" #n "I64d"
#define ctLLnx(n)       "%" #n "I64x"
#else
#define ctLLnd(n)       "%" #n "lld"
#define ctLLnx(n)       "%" #n "llx"
#endif

#ifndef CCHSIZ
#define CCHSIZ(n)
#endif

typedef LONG		VRLEN;
typedef VRLEN ctMEM *	pVRLEN;

typedef LONG		IOSIZE;
typedef IOSIZE ctMEM *	pIOSIZE;
typedef char		TEXT;
typedef TEXT ctMEM *	pTEXT;
typedef ctCONST char ctMEM * cpTEXT;
typedef TEXT ctMEM * ctMEM * ppTEXT;

typedef VRLEN		CMPLEN;		/* compressed record length   */
typedef CMPLEN *	pCMPLEN;

typedef VRLEN		FLXDAT;		/* flexible record metadata (schema ID) */

#ifndef ctADR2LNG
#define ctADR2LNG	UNLONG		/* address to long conversion */
#endif

#ifndef ctLNG2ADR
#define ctLNG2ADR	(pVOID)(UNLONG)	/* long to address conversion */
#endif

#ifdef ctN8

/*
** Native 64-bit integer data type support:
*/

/* Create a 64-bit value from two 32-bit values */
#define ctMAKE64(hw, lw)	(LONG8)(((ULONG8)(hw) << 32) + (ULONG)(lw))

/* Get high word of a 64-bit value */
#define ctGETHW64(llval)	((LONG)((ULONG8)(llval) >> 32))

/* Get low word of a 64-bit value */
#define ctGETLW64(llval)	((ULONG)(llval))

/* set the specified 64-bit integer value to zero */
#define ctZERO64(x)		((x) = 0)

/* check if the specified 64-bit integer value is zero */
#define ctISZERO64(x)		(((x) == 0) ? YES : NO)

/* get the address of the specified 64-bit integer expression */
#define ctPTR64(x)		&x

/* dereference the address of the specified 64-bit integer expression */
#define ctDEREF64(x)		*(x)

/* assign the specified 64-bit integer value to the specified 64-bit integer variable */
#define ctCOPY64(x,y)		((x) = (y))

/* increment the specified 64-bit integer value */
#define ctINCR64(x)		(x)++

/* assign a 32-bit value to the specified 64-bit integer */
#define ctASSIGN32TO64(x,y)	x = (y)

/* compare two 64-bit values */
#define ctCOMPARE64(x,y)	((x) > (y) ? 1 : ((x) < (y) ? -1 : 0))

/* add two 64-bit values, result stored in x */
#define ctADDTO64(x,y)		((x) = ((x) + (y)))

/* multiply 64-bit value, result stored in x */
#define ctMULTBY64(x,y)		((x) = ((x) * (y)))

#else  /* ~ctN8 */

/*
** No native 64-bit integer data type support:
*/

#ifdef LOW_HIGH
#define ctLOW32			0 /* low word array position */
#define ctHIG32			1 /* high word array position */
#else /* LOW_HIGH */
#define ctLOW32			1 /* low word array position */
#define ctHIG32			0 /* high word array position */
#endif /* LOW_HIGH */

/* combine a 32-bit high word value and a 32-bit low word value into a 64-bit integer value */
#define ctMAKE64(x, hw, lw)	(x[ctLOW32]=(lw), x[ctHIG32]=(hw))

/* get the 32-bit low word value from the specified 64-bit integer value */
#define ctGETLW64(x)		(ULONG)(x[ctLOW32])

/* get the 32-bit high word value from the specified 64-bit integer value */
#define ctGETHW64(x)		(ULONG)(x[ctHIG32])

/* set the specified 64-bit integer value to zero */
#define ctZERO64(x)		(x[ctLOW32]=0, x[ctHIG32] = 0)

/* check if the specified 64-bit integer value is zero */
#define ctISZERO64(x)		((x[ctLOW32] == 0 && x[ctHIG32] == 0) ? YES : NO)

/* get the address of the specified 64-bit integer expression */
#define ctPTR64(x)		(x)

/* dereference the address of the specified 64-bit integer expression */
#define ctDEREF64(x)		(x)

/* assign the specified 64-bit integer value to the specified 64-bit integer variable */
#define ctCOPY64(x,y)		((x)[0]=(y)[0], (x)[1]=(y)[1])

/* increment the specified 64-bit integer value */
#define ctINCR64(x)		ctINCdlng((pLONG) &x[ctHIG32], (pLONG) &x[ctLOW32] DLN(1))

/* assign a 32-bit value to the specified 64-bit integer */
#define ctASSIGN32TO64(x,y)	(x[ctHIG32] = 0, x[ctLOW32] = (y))

/* compare two 64-bit values */
#define ctCOMPARE64(x,y)	ctCMPdlng(x[ctHIG32], x[ctLOW32], y[ctHIG32], y[ctLOW32] DLN(2))

/* add two 64-bit values, result stored in x */
#define ctADDTO64(x,y)		ctADDdlng(&x[ctHIG32], &x[ctLOW32], y[ctHIG32], y[ctLOW32] DLN(3))

/* multiply 64-bit value by 32-bit value, result stored in x */
#define ctMULTBY64(x,y)		ctMULdlng(&x[ctHIG32], &x[ctLOW32], (y) DLN(4))

#endif /* ~ctN8 */

#ifdef ct8P
/* Create a 64-bit pointer from two 32-bit values */
#define ctMAKEPTR(hw, lw) (((ULONG8)(hw) << 32) + (ULONG)(lw))
/* Get high word of a 64-bit pointer value */
#define ctGETHWPTR(pntr) ((ULONG)((ULONG8)(pntr) >> 32))
#else
/* Create a 32-bit pointer from two 32-bit values */
#define ctMAKEPTR(hw, lw) (lw)
/* Get high word of a 32-bit pointer value */
#define ctGETHWPTR(pntr) ((LONG)0)
#endif

/* Get low word of a 64-bit or 32-bit pointer value */
#define ctGETLWPTR(pntr) ((ULONG)(pntr))

#ifdef ctNO_WCHAR
typedef UCOUNT		WCHAR;		/* no wchar system support */
#else /* ~ctNO_WCHAR */

#ifndef SYS_WCHAR
#ifndef WCHAR
typedef wchar_t		WCHAR;
#endif
#endif

#endif /* ~ctNO_WCHAR */

typedef WCHAR ctMEM *	pWCHAR;

#ifndef __PROGRAM_COUNTER_TYPE__
#define __PROGRAM_COUNTER_TYPE__ UINT
#endif

typedef __PROGRAM_COUNTER_TYPE__ PROGRAM_COUNTER;

#ifdef ctPortMACOSX
/*
 * On Mac OS X, the system header MacTypes.h defines the ProcPtr data type.
 * If MacTypes.h has been #include'd, we #define ctProcPtr so that c-tree
 * does not redefine ProcPtr.
 */
#ifdef __MACTYPES__
#define ctProcPtr
#endif
#endif

#ifndef ctProcPtr
#define ctProcPtr
#ifndef ctPortMAC
#ifdef PROTOTYPE
typedef NINT (*ProcPtr)(VOID);
#else
typedef NINT (*ProcPtr)();
#endif
#endif /* ~ctPortMAC */
#endif

#ifdef PROTOTYPE
typedef NINT (*ctCallbackPtr)(pVOID msg,NINT msglen,pVOID aux,NINT auxlen);
#else
typedef NINT (*ctCallbackPtr)();
#endif

#ifndef ctDllDecl
#define ctDllDecl
#endif

#ifdef ctPortDIAD_FS
#define  ctDIADFILESYSTEM_H	"ctDiadFileSystem.h"
#include ctDIADFILESYSTEM_H
#endif

typedef FILE *		pFILE;
typedef pFILE *		ppFILE;
#ifdef CT_ANSI
typedef pFILE		RNDFILE;
#else
#ifndef ctRNDFILE
typedef int		RNDFILE;
#endif
typedef RNDFILE ctMEM *	pRNDFILE;
#endif

typedef unsigned char	UTEXT;	/* if unsigned char not supported, make char */
typedef UTEXT ctMEM *	pUTEXT;
typedef UTEXT ctMEM * ctMEM * ppUTEXT;
typedef LONG		POINTER,DATET; 
typedef POINTER ctMEM *	pPOINTER;
typedef char	       *TEXTPTR;
#define ctRECPT		LONG
#define pctRECPT	pLONG

/*
** Define the calling convention for the function pointer that is passed to
** qsort().
*/
#if (defined(ctPortWINKE) || defined(ctPortWINCE))
#define ctQSDECL __cdecl
#else
#define ctQSDECL
#endif

#ifdef YES
#undef YES
#endif
#ifdef NO
#undef NO
#endif
#ifdef HYS
#undef HYS
#endif
#ifdef HNO
#undef HNO
#endif
#define HYS	2
#define	YES	1			/* TRUE	 */
#define	NO	0			/* FALSE */
#define HNO	(-1)
#define HNOadd	(-2)			/* used with ctrelbuf */
#define HNOren	(-3)			/* used with chkmfid81 */

/* chnacs modes reflect state of underlying storage in a CTFILE */


#define ACCESS_IN_USE	'y'	/* opened for normal use */
#define ACCESS_NONE	'n'	/* FCB is unused and available for reuse */
#define ACCESS_CHANGING 'c'	/* Changing access mode. Typically from NONE to IN_USE */
#define ACCESS_DELETED	'd'	/* delete is pending transaction resolution */
#define ACCESS_MEMBER	'm'	/* file is a logical member of a host file. */
#define ACCESS_VIRTUAL	'v'     /* virtually open, physically closed */
#define ACCESS_RESERVED 'e'     /* 
				* FCB is closed during recovery
				* and we do not want the FCB to be reused. 
				*/

#define ACCESS_UNUSED 	'w'	/* appears this value is not used */

/* special FCB, not part of ctfcbhdr[].  tstfnm() will terr if encounters the following  */
#define ACCESS_DUMPSEG 	'z'	/* auto segmented dynamic dump stream file */	
#define ACCESS_SPECIAL	's'	/* 
				*   Special internal files: 
				*  Logfiles, file mutex, dump stream, etc. 
				* 
				*  */
/*
** ctFILELIST
*/

/* action arguments */
#define ctADDfilelist	0x00000001	/* bit for add list operations */
#define ctCFGfilelist	(0x00000002 | ctADDfilelist)	/* */

#define ctSRCfilelist	0x00000004	/* bit for search list operations */
#define ctCHGfilelist	(0x00000008 | ctSRCfilelist)	/* change val and mbr */
#define ctREMfilelist	(0x00000010 | ctSRCfilelist)	/* remove entry from list */

#define ctIDXfilelist	0x00000020	/* traverse file list in list order */
#define ctNOWfilelist	0x00000040	/* no wild card bit */

#define ctAUXfilelist	(0x00000080 | ctSRCfilelist)	/* set auxiliary info */
#define ctTRVfilelist	(0x00000100 | ctSRCfilelist)	/* retrieve aux ptr */

#define ctOWNfilelist	0x00000200 /* find an entry for sOWNR */
#define ctSTTfilelist	0x00000400 /* change the list type */
#define ctVALfilelist	(0x00000800 | ctSRCfilelist)	/* only change val */
#define ctMBRfilelist	(0x00001000 | ctSRCfilelist)	/* only change mbr */

/* state arguments */
#define ctEMPTYlist		(-1)
#define ctSPLCACHElist		1	/* SPECIAL_CACHE_FILE */
#define ctPRICACHElist		2	/* PRIME_CACHE, PRIME_CACHE_BY_KEY */
#define ctNO_CACHElist		3	/* NO_CACHE */
#define ctPRIINDEXlist		4	/* PRIME_INDEX */
#define ctNO_FLUSHlist		5	/* NO_FLUSH */
#define ctCHANNELSlist		6	/* SET_FILE_CHANNELS */
#define ctSNAPSHOTlist		7	/* SNAPSHOT_FILENAME */
#define ctLOGSETlist		8	/* LOGSET_ASSIGNMENT */
#define ctMEMFILElist		9	/* MEMORY_FILE */
#define ctAPPNAMElist		10	/* APP_NAME_LIST */
#define ctREPLICATElist		11	/* REPLICATE */
#define ctAUTO_PREIMGlist	12	/* AUTO_PREIMG */
#define ctPERMISSIONlist	13	/* FILE_PERMISSIONS */
#define ctFILEBLOCKlist		14
#define ctAUTO_TRNLOGlist	15	/* AUTO_TRNLOG */
#define ctREPLMAPlist		16
#define ctUNBUFFEREDIOlist	17	/* UNBUFFERED_IO */
#define ctKEEPOPENlist		18	/* KEEPOPEN_LIST */
#define ctCOMPRESSlist		19	/* COMPRESS_FILE */
#define ctFSCOMPRESSlist	20	/* FILESYS_COMPRESS_FILE */

/* number of file lists when ctFeatFILELISTmulti is enabled */
#define NUMBER_OF_FILE_LISTS	20


/*
** SNAPSHOT definitions
*/

/* bit map for varlen contents						*/
#define ctSNAPSHOTtruncated	1	/* buffer too small		*/
#define ctSNAPSHOTwrkstt	2	/* function times		*/
#define ctSNAPSHOTlogstt	4	/* individual log set stats	*/

/* Performance SNAPSHOT operation codes	*/

	/* Automatic snapshots go directly to the SYSLOG files. At a minimum,
	** the snapshot is comprised of the ctGSMS structure contents.
	*/

	/* Start automatic snapshots, or change time interval if automatic
	snapshots are already enabled. Automatic snapshots can be initiated from
	the configuration file with an entry: SNAPSHOT_INTERVAL <minutes> */
#define ctPSSstartAuto		1
	/* Stop automatic snapshots. */
#define ctPSSstopAuto		2
	/* Resume automatic snapshots with the same interval last used. */
#define ctPSSresumeAuto		3
	/* Start collection of function timing stats. This can be called whether
	or not automatic snapshots are currently active. It affects the contents
	of a snapshot, not when or if they occur. Function timings can also be
	enabled from the configuration file with the entry:
	DIAGNOSTICS SNAPSHOT_WORKTIME */
#define ctPSStimeWorkOn		7
	/* Turn off function timings. Function timings require a significant
	number of calls to the high resolution timer, and are more consistent
	with diagnostic or testing modes of operation. */
#define ctPSStimeWorkOff	8
	/* Clear function timing stats. */
#define ctPSStimeWorkClear	9

	/* Snapshots written to the SYSLOG files, either by an automatic
	** snapshot or an on demand snapshot, may contain user and/or
	** file information in addition to the system data. The user
	** information consists of the ctGUMS structure contents for each
	** user. If function timing is enabled, then user specific function
	** timings are also included. The file information consists of the
	** ctGFMS structure contents. To be included in the snapshots written
	** to the SYSLOG files, users and files must be activated. Each
	** user and file in a snapshot has a separate entry in the SYSLOG
	** files, but they share a common instance handle.
	**
	** ctSNAPSHOT() can be called multiple times to activate multiple
	** users and/or files, and user IDs and filenames may be expresed
	** as patterns with '?' and '*' wildcard matches. A pattern of
	** "*" implies ALL.
	*/

	/* Activate the user with the specified User ID. Use a pattern of "*" to
	activate all users. */
#define ctPSSaddUserID		10
	/* Activate the user with the specified thread handle. */
#define ctPSSaddUserHandle	11
	/* Activate the file with the specified file name. Use a pattern of "*"
	to activate all files. */
#define ctPSSaddFileName	15
	/* Activate the file with the specified file number. */
#define ctPSSaddFileNo		16

	/* Each of the following configuration entries can be used multiple
	** times to activate users and files. As above, the user IDs and
	** file names can be expressed as patterns.
	**
	**	SNAPSHOT_USERID		<user ID>
	**	SNAPSHOT_FILENAME	<file name>
	*/

	/* Undo all user activations. */
#define ctPSSclearUsers		18
	/* Undo all file activations. */
#define ctPSSclearFiles		19

	/* Users may define up to 8 different timing baskets. A begin
	** mark call establishes a high resolution starting time for
	** the specified basket. An end mark call, causes the specified
	** basket counter to be incremented, and the elapsed time is added
	** to the timing basket. The baskets are numbered from 0 to 7.
	*/

	/* Mark beginning time for user specified timing basket. */
#define ctPSSbegMark		20
	/* Mark ending time for user specified timing basket. */
#define ctPSSendMark		21

	/* On demand snapshots occur when ctSNAPSHOT is called with
	** one of the following operation codes. An on demand snapshot
	** takes place synchronously with the ctSNAPSHOT() call. An on
	** demand snapshot may result in SYSLOG entries, or the results
	** may be returned by the ctSNAPSHOT call. In the latter case,
	** only one snapshot (i.e., a system snapshot, a user snapshot or
	** a file snapshot) may be returned by the ctSNAPSHOT() routine.
	*/ 

	/* On demand snapshot of system written to SNAPSHOT.FCS, a simple text
	file. At this time only the system snapshot is available in
	SNAPSHOT.FCS. */
#define ctPSStext		23

	/* On demand snapshot of system and activated users and files written to
	SYSLOG. Multiple records will be written to SYSLOG if any users and/or
	files are activated. They will all share the same instance ID returned
	by the call. */
#define ctPSSnow		24
	/* On demand system snapshot returned directly. No entry is made in
	SYSLOG. */
#define ctPSSsystem		25
	/* On demand user snapshot returned directly. No entry is made in
	SYSLOG. The snapshot is for the user calling ctSNAPSHOT(). */
#define ctPSSuser		26
	/* On demand file snapshot returned directly. No entry is made in
	SYSLOG. The user file number is passed in to specify the file. */
#define ctPSSfile		27
	/* On demand test of the sleep (ct_udefer) routine and the yield
	characteristics of the platform under load. The load is based on
	whatever the system is doing at the time of the call. The call samples
	the ct_udefer and ctdefer(0) routines in real time. The results are
	returned to the SNAPSHOT.FCS text file. */
#define ctPSSsleepTest		28
	/* On demand snapshot of all open files written to SNAPFILE.FCS, a
	comma-delimited text file. */
#define ctPSScsvFile		29
	/* On demand snapshot of all open files written to SNAPFILE.FCS, a
	simple text file. */
#define ctPSStextFile		30
	/* Start collection of disk I/O timing stats. It affects the contents of
	a file snapshot. Disk I/O timings can also be enabled from configuration
	file with the entry: DIAGNOSTICS SNAPSHOT_IOTIME */
#define ctPSStimeFileIoOn	31
	/* Turn off disk I/O timings. Disk I/O timings require a significant
	number of calls to the high resolution timer, and are more consistent
	with diagnostic or testing modes of operation. */
#define ctPSStimeFileIoOff	32
	/* On demand snapshot of c-tree function timings written to
	SNAPFUNC.FCS, a comma-delimited text file. */
#define ctPSScsvFunc		33
	/* On demand snapshot of c-tree function timings written to
	SNAPFUNC.FCS, a simple text file. */
#define ctPSStextFunc		34
	/* On demand SQL system snapshot returned directly. No entry is made in
	SYSLOG. */
#define ctPSSsqlSystem		35
	/* On demand user snapshot returned directly. No entry is made in
	SYSLOG. The snapshot is for the user with the specified thread
	handle. */
#define ctPSSuserHandle		36
	/* On demand file snapshot returned directly. No entry is made in
	SYSLOG. The system file number is passed in to specify the file. */
#define ctPSSfileSystemHandle	37
	/* On demand transaction snapshot returned directly. No entry is made in
	SYSLOG. */
#define ctPSStransaction	38
	/* On demand replication reader snapshot returned directly. No entry is
	made in SYSLOG. */
#define ctPSSreplread		39
	/* On demand memory allocation snapshot returned directly. No entry is
	made in SYSLOG. */
#define ctPSSmemAlloc		40
	/* On demand CHECKLOCK_FILE list snapshot returned directly. No entry is
	made in SYSLOG. */
#define ctPSSchecklockfile	41
	/* On demand filelist snapshot returned directly. No entry is made in
	SYSLOG. */
#define ctPSSfilelist		42

/*
** The size of snapshot structures (the fixed portion of a snapshot),
** should all be a multiple of 32.
**
** structure members with a '^' in their comment are measured in
** high resolution time. To convert such a quantity, Q, to seconds and
** milliseconds the following scheme will work:
**
**		seconds = (Q / tps)
**		millisc = ((Q % tps) * 1000) / tps
**
** where tps is the ticks per second, and is returned in the scthrbastim
** member of the snapshot structure.
*/

/*
** System Snapshot Structure
*/

#define ctCHKPdetail	8	/* chkpnt time details			*/
#define ctTRNTdetail	24	/* tran time detail boxes		*/
#define ctTRNTlbox	40	/* tran time virtual detail boxes	*/
#define ctLOCKdetail	16	/* blocked lock time detail boxes	*/
#define ctLOCKlbox	24	/* blocked lock time virtual details	*/
#define ctXLOKdetail	16	/* blocked idx lock time detail boxes	*/
#define ctXLOKlbox	24	/* blocked idx lock time virtual details*/

/* Background flush bucket state information. */
typedef struct bgflsbkt_t {
	LONG8	datbastim;	/* base time for timing buckets		     */
	LONG8	datbktsiz;	/* timing bucket width in hi-res timer ticks */
	LONG	datbktcnt;	/* current number of timing buckets	     */
	LONG	datbktcur;	/* current timing bucket		     */
	LONG8	idxbastim;	/* base time for timing buckets		     */
	LONG8	idxbktsiz;	/* timing bucket width in hi-res timer ticks */
	LONG	idxbktcnt;	/* current number of timing buckets	     */
	LONG	idxbktcur;	/* current timing bucket		     */
	pLONG	pdatbkt;	/* timing bucket array for non-tran data     */
	pLONG	pidxbkt;	/* timing bucket array for non-tran index    */
} BGFLSBKT;

/* Background flush state information. */
typedef struct bgflss_t {
	LONG8	sctntdfls;	/* data cache flush count		*/
	LONG8	sctntifls;	/* index buffer flush count		*/
	LONG	sctntdlmt;	/* data file flush time limit		*/
	LONG	sctntilmt;	/* index flush time limit		*/
	LONG	sctntdage;	/* oldest dirty data page		*/
	LONG	sctntiage;	/* oldest dirty index buffer		*/
	LONG	sctntdbkt;	/* data file flush buckets (nominal)	*/
	LONG	sctntdbkc;	/* data file flush buckets (current)	*/
	LONG	sctntibkt;	/* index flush buckets (nominal)	*/
	LONG	sctntibkc;	/* data file flush buckets (current)	*/
	LONG	sctntdmax;	/* max dirty time for non-tran dat page */
	LONG	sctntimax;	/* max dirty time for non-tran idx bufr */
	LONG	sctntdMsec;	/* defer time after data flush (msec)	*/
	LONG	sctntdFlsh;	/* # of data flushes before deferring	*/
	LONG	sctntiMsec;	/* defer time after index flush (msec)	*/
	LONG	sctntiFlsh;	/* # of index flushes before deferring	*/
} BGFLSS, *pBGFLSS;

#define	BGFLSNT	0	/* index into bgflss for non-TRNLOG files	*/
#define	BGFLSTR	1	/* index into bgflss for TRNLOG files		*/

/* system snapshot versions */
#define ctGSMS_VERSION_FILEOPS		21 /* minimum snapshot version that includes fileops fields */
#define ctGSMS_VERSION_CTREPFLSBG	22 /* minimum snapshot version that includes replication log flush by background thread */
#define ctGSMS_VERSION_COMPFLG5		23 /* minimum snapshot version that includes 5th compatibility flag */

#define ctGSMSvern ctGSMS_VERSION_COMPFLG5	/* ctGSMS (system snapshot) version #	*/

typedef struct ctgsms {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	ULONG	fixlen;		/* length of fixed portion of snapshot	*/
	ULONG	varlen;		/* length of variable region (if any)	*/
	ULONG	contents;	/* bit map of var len contents		*/
	ULONG	logsets;	/* number of multiple log sets		*/
	LONG8	snapshottm;	/* snapshot time stamp: seconds since 70*/

	LONG8	sctdnd_red;	/* delete node thread queue reads	*/
	LONG8	sctdnd_wrt;	/* delete node thread queue writes	*/
	LONG8	sctdnd_rwt;	/* delete node thread queue rewrites	*/
	LONG8	sctdnd_abn;	/* delete node thread queue abandons	*/

	LONG8	sctdnd_rmv;	/* delete node thread queue removals (no longer used)	*/
	LONG8	sctdnd_non;	/* delete node thread queue no action	*/
	LONG8	sctloktry;	/* count of lock attempts		*/
	LONG8	sctlokhlk;	/* subcount of hdr lock attempts	*/

	LONG8	sctlokdny;	/* count of locks denied		*/
	LONG8	sctlokblk;	/* count of locks blocked		*/
	LONG8	sctlokhbk;	/* subcount of header blocks		*/
	LONG8	sctlokdlk;	/* count of dead locks			*/

	LONG8	sctlokfre;	/* count of locks freed			*/
	LONG8	sctlokrel;	/* count of blocks released		*/
	LONG8	sctlokcur;	/* current count of locks held		*/
	LONG8	sctblkcur;	/* current count of blocked requests	*/

	LONG8	scttrntim;	/* cumulative transaction time^		*/
	LONG8	scttrncnt;	/* cumulative transaction count		*/
	LONG8	scttrnmax;	/* maximum elapsed tran time^		*/

	ULONG	sct_compflg3;	/* 3rd compatibility word		*/
	LONG	sctrqtmonint;	/* request time monitor interval	*/

	LONG8	scttot_call;	/* system-wide c-tree calls		*/
	LONG8	scttot_recv;	/* system-wide time waiting for request^*/
	LONG8	scttot_work;	/* system-wide time performing requests^*/
	LONG8	scttot_send;	/* system-wide time to send request^	*/

	LONG8	sctmemhgh;	/* system memory highwater mark		*/
	LONG8	sctmemsum;	/* current aggregate sum		*/
#ifdef ctFeatATOMICop64
	volatile
	AULONG8	sct_dbrqs;	/* data buffer requests			*/
	volatile
	AULONG8	sct_dbhit;	/* data buffer hits			*/
#else
	LONG8	sct_dbrqs;	/* data buffer requests			*/
	LONG8	sct_dbhit;	/* data buffer hits			*/
#endif

#ifdef ctFeatATOMICop64
	volatile
	AULONG8	sct_ibrqs;	/* index buffer requests		*/
	volatile
	AULONG8	sct_ibhit;	/* index buffer hits			*/
#else
	LONG8	sct_ibrqs;	/* index buffer requests		*/
	LONG8	sct_ibhit;	/* index buffer hits			*/
#endif
	LONG8	sct_rdops;	/* number of read operations		*/
	LONG8	sct_rdbyt;	/* bytes read				*/

	LONG8	sct_wrops;	/* number of write operations		*/
	LONG8	sct_wrbyt;	/* bytes written			*/
	LONG8	sct_rcops;	/* number of comm read operations	*/
	LONG8	sct_rcbyt;	/* comm bytes read			*/

	LONG8	sct_wcops;	/* number of comm write operations	*/
	LONG8	sct_wcbyt;	/* comm bytes written			*/
	LONG8	sctwlgops;	/* number of log write operations	*/
	LONG8	sctwlgbyt;	/* bytes written to log file		*/

	LONG8	sctrlgops;	/* number of log read operations	*/
	LONG8	sctrlgbyt;	/* bytes read from log file		*/
	LONG8	sctxlgops;	/* number of log extension operations	*/
	LONG8	sctxlgbyt;	/* log file extension bytes		*/

	LONG8	sct_trbeg;	/* # transaction begins			*/
	LONG8	sct_trend;	/* # transaction ends			*/
	LONG8	sct_trabt;	/* # transaction aborts			*/
	LONG8	sct_trsav;	/* # transaction savepoints		*/

	LONG8	sct_trrst;	/* # transaction restores		*/
	LONG8	sct_trfls;	/* # transaction log flush writes	*/
	LONG8	sctsync_dosfls;	/* DOSFLUSH sync calls			*/
	LONG8	sctsync_logfil;	/* transaction log sync calls		*/

	LONG8	sctsync_regfil;	/* c-tree file sync calls		*/
	LONG8	scthrtimbas;	/* high res timer ticks per sec^	*/
	LONG8	sctchkpnttim;	/* cumulative checkpoint time^		*/
	LONG8	sctchkpntsiz;	/* cumulative checkpoint size		*/

	LONG8	sctchkpnt[ctCHKPdetail];
				/* intermediate checkpoint times^	*/

	LONG8	sctcmtdlytry;	/* cmtdly eligible count		*/
	LONG8	sctcmtdlycnt;	/* cmtdly concurrent trans exist	*/
	LONG8	sctcmtdlycoh;	/* cmtdly cohorts exist (success)	*/
	LONG8	sctcmtcohmax;	/* cmtdly max cohort count		*/

	LONG8	sctcmtdlyclr;	/* cmtdly cohort appeared (success)	*/
	LONG8	sctcmtlopclr;	/* cmtdly appeared loop count		*/
	LONG8	sctcmtdlynot;	/* cmtdly direct flush count		*/
	LONG8	sctcmtlopfls;	/* cmtdly log flush loop count		*/

	LONG8	sctcmtdlydfr;	/* cmtdly loop defer count		*/
	ULONG	sctcmtlopmax;	/* max loop defer count			*/
	ULONG	sctcmtmaxadp;	/* max adaptive LFW loop counter	*/
	LONG8	sctcmtavgadp;	/* avg adaptive LFW loop counter	*/
	LONG8	sctcmtlopfls2;	/* cmtdly log flush2 loop count		*/

	LONG8	stimchk[8];	/* diagnostic time ct_udefer check	*/

	LONG8	selapwrktim;	/* elapsed time func timings turned on	*/
	LONG8	selapsrvtim;	/* elapsed server operation time	*/
	LONG8	sctcmtblktim;	/* accum commit delay block time (requested) */
	LONG8	sctcmtclrtim;	/* accum commit delay clear time (requested) */

	LONG8	stimchktarget;	/* ct_udefer expected result		*/
	LONG8	stimchkconsec;	/* time between consecutive hrt in usec */
	LONG8	stimchkavg;	/* avg time ofr hrtimer call in usec	*/
	LONG8	sctcmtdlyfls;	/* cmtdly log flushed anyway (success)	*/

	LONG8	sctcmtfls;	/* commit/abort tran log flush rqst	*/
	LONG8	sctbegfls;	/*        begin tran log flush rqst	*/
	LONG8	sctidxfls;	/*       LOGIDX tran log flush rqst	*/
	LONG8	sctupdfls;	/* file 1st upd tran log flush rqst	*/

	LONG8	sctcmtavgdfr;	/* accum commit delay block time (actual) */
	LONG8	sctcmtmaxdfr;	/* max commit delay block time		*/
	LONG8	sctcmtdlyfls2;	/* dmtdly log flushed anyway2 (success)	*/
	LONG8	scttrnbox;	/* width of cttrndet boxes^		*/


	LONG8	sctlogfls;	/* log flush count			*/
	LONG8	sctlogtim;	/* log flush time			*/
#ifdef ctdbMEMSUM
	LONG8	sctSQLmemsum;	/* current aggregate sum for SQL	*/
	LONG8	sctDBmemsum;	/* current aggregate sum for CTDB-STUB  */
#else
	LONG8	available81[2];	/* available for future use		*/
#endif
	LONG8	sctredcmtlpc;	/* RED_CMTLOK loop count		*/
	LONG8	sctrepfls;	/* replication log flush rqst		*/
	LONG8	sctchkbufwrt;	/* checkpoint index buffer writes	*/
	LONG8	sctchkchewrt;	/* checkpoint data cache writes		*/
	ULONG	scttrndet[ctTRNTdetail];
				/* tran time detail			*/

	LONG	sctactfil;	/* # open physical files		*/
	LONG	scttotfil;	/* # open logical files			*/
	LONG	scttotblk;	/* # c-tree FCBs in use			*/
	LONG	sctactfilx;	/* max physical files opened		*/
	LONG	scttotfilx;	/* max logical files opened		*/
	LONG	scttotblkx;	/* max c-tree FCBs in use		*/
	ULONG	sctnusers;	/* number of users			*/
	ULONG	sctnusersx;	/* max number of users			*/

#ifdef ctFeatATOMICop64
	volatile
	AULONG	sctloknm;	/* net locks over unlocks		*/
	volatile
	AULONG	sctloknmx;	/* max net locks over unlocks		*/
#else
	LONG	sctloknm;	/* net locks over unlocks		*/
	LONG	sctloknmx;	/* max net locks over unlocks		*/
#endif
	ULONG	sct_mxbuf;	/* number of index buffer pages		*/
	ULONG	sctbufcnt;	/* index buffer pages in use		*/
	ULONG	sctbufhgh;	/* max index buffers in use		*/
	ULONG	sct_dxbuf;	/* available data cache pages 		*/
	ULONG	sctdatcnt;	/* data cache pages in use		*/
	ULONG	sctdathgh;	/* max data cache pages in use		*/

	ULONG	scmtblkseq;	/* not flow through cmtdly block	*/
	ULONG	sct_compflg;	/* compatibility flag			*/
	ULONG	sct_compflg2;	/* 2nd compatibility word		*/
	ULONG	sct_diagflg;	/* diagnostic flag			*/
	ULONG	sct_diagflg2;	/* 2nd diagnostic flag			*/
	LONG	sct_cmtdly;	/* commit delay				*/
	LONG	sct_chkdly;	/* checkpoint tranac_cnt delay		*/
	ULONG	sct_cmtscl;	/* cmtdlytim block to clear ratio	*/

	ULONG	sct_cmtbas;	/* cmtdlytim cohort size measure	*/
	ULONG	stimchkusec;	/* ct_udefer test interval in usec's	*/
	ULONG	stimchkiter;	/* ct_udefer test iterations		*/
	ULONG	sct_udefer_thld;/* ct_udefer usec threshold		*/
	ULONG	sct_udefer_64yd;/* sleep duration for 64 yields (usec)	*/
	ULONG	sctITIMretry;	/* ITIM_ERR auto retry count		*/
	ULONG	sctTPNDretry;	/* TPND_ERR auto retry count		*/
	ULONG	sctITIMlimit;	/* ITIM_ERR auto retry limit		*/
	ULONG	sctITIMfailed;	/* ITIM_ERR auto retry failed		*/
	ULONG	sctredcmtdfr;	/* RED_CMTLOK loop defer time millisecs	*/
	ULONG	sctredcmtlpr;	/* RED_CMTLOK loopers			*/
	ULONG	sctITIMdefer;	/* ITIM_ERR auto retry defer		*/

	LONG8	sctismaddcnt;	/* ISAM record add count		*/
	LONG8	sctismdelcnt;	/* ISAM record delete count		*/
	ULONG	sct_dxspllmt;	/* avail   data file special cache pages*/
	ULONG	sct_dxsplcnt;	/* actual  data file special cache pages*/
	ULONG	sct_dxsplhgh;	/* maximum data file special cache pages*/
	ULONG	sctcpcnt;	/* check point count			*/
	LONG	sct_numvfil;	/* number of virtual files open		*/
	LONG	sct_avlfil;	/* # available file control blocks	*/
#ifdef ctFeatATOMICop
	volatile
	AULONG	sctactusr;	/* number of threads active in foregrnd */
#else
	LONG	sctactusr;	/* number of threads active in foregrnd */
#endif
	LONG	sct_nutcnt;	/* # of index buffers on upd list (tran)*/

	LONG	sct_nupcnt;	/* # of index buffers on upd list	*/
	LONG	sct_dutcnt;	/* # of data caches on upd list (tran)	*/
	LONG	sct_dupcnt;	/* # of data caches on upd list		*/
	LONG	sctwatshtdwn;	/* wait on shut down in seconds		*/

	LONG8	sct_wrtcmp;	/* calls to ctwrtlog			*/
	LONG8	sct_no_cmp;	/* ctwrtlog below compression threshold	*/
	LONG8	sct_tp_cmp;	/* trantyp not compressed (DIFIMAGE)	*/
	LONG8	sct_rj_cmp;	/* ctwrtlg compression not effective	*/
	LONG8	sct_bytcmp;	/* total bytes saved by log compression	*/
	LONG	sctlogcmpfloor;	/* no log compression below this size	*/
	LONG	sctlogcmpfactor;/* out-size must not > this % of in-size*/

	COUNT	sct_mxfil;	/* total number of c-tree FCBs		*/
	COUNT	sct_ndsec;	/* # of sectors per node		*/
	UTEXT	sflvr;		/* server byte order			*/
	UTEXT	salgn;		/* server alignment			*/
	UTEXT	spntr;		/* server pointer size			*/
	TEXT	availt;
	LONG8	sctlokkil;	/* count of killed locks		*/

	LONG8	sctismupdcnt;	/* ISAM record update count		*/
	LONG8	sctismredcnt;	/* ISAM record read count		*/
	LONG8	sctloktim;	/* cumulative lock wait time^		*/
	LONG8	sctlokcnt;	/* cumulative lock wait count		*/
	LONG8	sctlokmax;	/* maximum elapsed lock wait time^	*/
	LONG8	sctlokbox;	/* width of detail boxes^		*/
	ULONG	sctlokdet[ctLOCKdetail];
				/* lock block time details		*/

	LONG8	sctxlktim;	/* cumulative idx lock wait time^	*/
	LONG8	sctxlkcnt;	/* cumulative idx lock wait count	*/
	LONG8	sctxlkmax;	/* maximum elapsed idx lock wait time^	*/
	LONG8	sctxlkbox;	/* width of detail boxes^		*/
	ULONG	sctxlkdet[ctXLOKdetail];
				/* idx lock block time details		*/

	TEXT	description[128];/* optional text description		*/

#ifdef ctFeatATOMICop
	volatile
	AULONG	sctcurusr;	/* threads in use total	(ctaddwork)	*/
	volatile
	AULONG	sctmaxusr;	/* max threads in use   (ctaddwork)	*/
#else
	LONG	sctcurusr;	/* threads in use total	(ctaddwork)	*/
	LONG	sctmaxusr;	/* max threads in use   (ctaddwork)	*/
#endif
	ULONG	scti_svvr;	/* server internal version number	*/
	ULONG	sctioblkretry;	/* I/O error auto retry count		*/
	ULONG	sct_compflg4;	/* 4th compatibility word		*/
	ULONG	sct_dxscan;	/* avail   scan cache pages		*/
	ULONG	sct_dxscancnt;	/* actual  scan cache pages		*/
	ULONG	sct_dxscanhgh;	/* maximum scan cache pages		*/

	ULONG	sct_hbTbuf;	/* index hash bin Threshold		*/
	ULONG	sct_hbRbuf;	/* index hash bin Reset limit		*/
	ULONG	sct_hbTcac;	/*  data hash bin Threshold		*/
	ULONG	sct_hbRcac;	/*  data hash bin Reset limit		*/
	ULONG	sct_diagflg3;	/* 3rd diagnostic flag			*/
	ULONG	sctmldmsec;	/* DELAYED_DURABILITY (in msecs)	*/
	LONG	sarplogint;	/* auto restore point log interval	*/
	LONG	sarptimout;	/* auto restore point tran timeout	*/

#ifdef ctFeatATOMICop64
	volatile
	AULONG8	sctdatflschk;	/*     data cache tran log checks	*/ 
#else
	LONG8	sctdatflschk;	/*     data cache tran log checks	*/ 
#endif
	LONG8	sctdatfls;	/* data cache tran log flush rqst	*/
	LONG8	sctmldfls;	/*   MAX LOG DEFER log flush rqst	*/

	LONG	sarpoptions;	/* auto restore point options		*/
	LONG	sarplastlog;	/* auto restore point last log written	*/

	LONG8	sphyopncnt;	/* number of physical file opens	*/
	LONG8	sphyclscnt;	/* number of physical file closes	*/

	BGFLSS	bgflss[2];	/* background flush state vars		*/

	LONG8	slogopncnt;	/* number of logical file opens		*/
	LONG8	slogclscnt;	/* number of logical file closes	*/
	LONG8	sfilcrecnt;	/* number of file creates		*/
	LONG8	sfilrencnt;	/* number of file renames		*/
	LONG8	sfildelcnt;	/* number of file deletes		*/
	LONG8	sctrepflsbg;	/* replication log flush by background thread */
	LONG8	savail83[2];	/* available for use */

	LONG	sct_mxfil32;	/* total number of c-tree FCBs		*/
	ULONG	sct_compflg5;	/* 5th compatibility word		*/
	LONG	savail4[6];	/* available for use */
/*
   NOTE: When modifying this structure, remember: 
     1) We require this structure's size to be a multiple of 32.
     2) Update revGSMSbyt() in ctstat.c as needed to byte flip the new fields.
     3) Increment the GSMS structure version (ctGSMSvern) above.
*/
} ctGSMS, ctMEM * pctGSMS;

/* Auto restore point options bits (ctGSMS sarpoptions field): */
#define ctARP_FAIL_AFTER_TIMEOUT 0x00000001	/* fail if trans active after timeout */
#define ctARP_WRITE_CHECKPOINT	 0x00000002	/* write a checkpoint */

typedef struct logst {
	LONG	lowlog; /* lowest numbered active log		*/
	LONG	curlog; /* current transaction log number	*/
	LONG	lstpnt; /* last byte position written to log	*/
	LONG	lstent;	/* last entry on disk or in log buffer	*/
	LONG	lstsuc;	/* byte position of last SUCTRAN entry	*/
} LOGST, ctMEM * pLOGST;

/* LOGST structure used internally in standalone library to avoid macro definition conflict for lstpnt and lstsuc */
typedef struct logsti {
	LONG	lowlog;  /* lowest numbered active log		*/
	LONG	curlog;  /* current transaction log number	*/
	LONG	slstpnt; /* last byte position written to log	*/
	LONG	lstent;  /* last entry on disk or in log buffer	*/
	LONG	slstsuc; /* byte position of last SUCTRAN entry	*/
} LOGSTI, ctMEM * pLOGSTI;

#define ctGTMSvern	1	/* ctGTMS (transaction snapshot) version #	*/
typedef struct ctgtms {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	LONG8	snapshottm;	/* snapshot time stamp: seconds since 70*/
	LONG8	tranno;		/* next transaction number		*/

	LOGST	lstt;		/* log state variables			*/
	ULONG	tfil;		/* next transaction file number		*/

	} ctGTMS, ctMEM * pctGTMS;

#define ctGRMSvern	1	/* ctGRMS (replication reader) version #	*/
/*
** The replication reader snapshot call returns a ctGRMS structure followed by
** retent RALOGX structures.
*/
typedef struct ctgrms {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	LONG	avlent;		/* number of available entries		*/
	LONG	retent;		/* number of entries returned		*/

	} ctGRMS, ctMEM * pctGRMS;

#define ctGCMSvern	1	/* ctGCMS (CHECKLOCK_LIST) version #	*/
/*
** The CHECKLOCK_LIST reader snapshot call returns a ctGCMS structure, where
** the buf field contains the CHECKLOCK_LIST filespecs as a string. Each
** filespec is followed by a newline and the last filespec is terminated with
** a null byte.
*/
typedef struct ctgcms {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	ULONG	length;		/* length of data stored in buf field	*/
	TEXT	buf[1];		/* CHECKLIST_FILE filespec entries	*/
} ctGCMS, ctMEM * pctGCMS;

#define ctGFLSvern	1	/* ctGFLS (filelist) version #		*/
typedef struct ctgfls {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	ULONG	length;		/* length of data stored in buf field	*/
	ULONG	numberOfEntries;/* number of entries returned in buf	*/
	TEXT	buf[1];		/* filelist entries			*/
} ctGFLS, ctMEM * pctGFLS;

/* c-tree Server file list entry information */
typedef struct ctFileListEntry_t {
	LONG	value;		/* value		*/
	LONG	member;		/* member		*/
	LONG	scale;		/* scale		*/
	TEXT	filename[1];	/* file name		*/
} ctFILE_LIST_ENTRY, *pctFILE_LIST_ENTRY;

#define ctGMMSvern	1	/* ctGMMS (memory snapshot) version #	*/
#define TOTMEMLIST	(24 /* NUMCTLIST */ + 1)

typedef struct ctgmms {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	LONG8	snapshottm;	/* snapshot time stamp: seconds since 70*/

	TEXT	memdsc[TOTMEMLIST][8]; /* Suballocator list description	*/
	LONG8	memalc[TOTMEMLIST]; /* Allocated suballocator memory	*/
	LONG8	memuse[TOTMEMLIST]; /* Used suballocator memory		*/

	} ctGMMS, ctMEM * pctGMMS;

/*
** The system snapshots may include individual log set statistics in
** the variable portion of the system snapshot. If available, these will
** follow the system structure and any available ctWRKSTT structures.
*/

typedef struct logstt {
	LONG8	sctsync_logfil;	/* transaction log sync calls		*/
	LONG8	scmtblkseq;	/* lack of smooth cmtdly block flow	*/
	LONG8	sctwlgops;	/* number of log write operations	*/
	LONG8	sctwlgbyt;	/* bytes written to log file		*/

	LONG8	sctrlgops;	/* number of log read operations	*/
	LONG8	sctrlgbyt;	/* bytes read from log file		*/
	LONG8	sctxlgops;	/* number of log extension operations	*/
	LONG8	sctxlgbyt;	/* log file extension bytes		*/

	LONG8	sct_trbeg;	/* # transaction begins			*/
	LONG8	sct_trend;	/* # transaction ends			*/
	LONG8	sct_trabt;	/* # transaction aborts			*/
	LONG8	sct_trsav;	/* # transaction savepoints		*/

	LONG8	sctchkpnttim;	/* cumulative checkpoint time^		*/
	LONG8	sctchkpntsiz;	/* cumulative checkpoint size		*/
	LONG8	sct_trfls;	/* log flush writes			*/
	ULONG	sctcpcnt;	/* checkpoint count			*/
	ULONG	avail40;

	LONG8	sctchkpnt[ctCHKPdetail];
				/* intermediate checkpoint times^	*/

	LONG8	sctcmtfls;	/* commit/abort tran log flush rqst	*/
	LONG8	sctbegfls;	/*        begin tran log flush rqst	*/
	LONG8	sctidxfls;	/*       LOGIDX tran log flush rqst	*/
	LONG8	sctupdfls;	/* file 1st upd tran log flush rqst	*/

	LONG8	sctcmtdlytry;	/* cmtdly eligible count		*/
	LONG8	sctcmtdlycnt;	/* cmtdly concurrent trans exist	*/
	LONG8	sctcmtdlycoh;	/* cmtdly cohorts exist (success)	*/
	LONG8	sctcmtcohmax;	/* cmtdly max cohort count		*/

	LONG8	sctcmtdlyclr;	/* cmtdly cohort appeared (success)	*/
	LONG8	sctcmtlopclr;	/* cmtdly appeared loop count		*/
	LONG8	sctcmtdlyfls;	/* cmtdly log flushed anyway (success)	*/
	LONG8	sctcmtlopfls;	/* cmtdly log flush loop count		*/

	LONG8	sctcmtdlydfr;	/* cmtdly loop defer count		*/
	ULONG	sctcmtlopmax;	/* max loop defer count			*/
	ULONG	sctcmtmaxadp;	/* max adaptive LFW loop counter	*/
	LONG8	sctcmtavgadp;	/* avg adaptive LFW loop counter	*/
	LONG8	sctcmtlopfls2;	/* cmtdly log flush2 loop count		*/

	LONG8	sctcmtdlynot;	/* cmtdly direct flush count		*/
	LONG8	sctcmtavgdfr;	/* avg commit delay block time		*/
	LONG8	sctcmtmaxdfr;	/* max commit delay block time		*/
	LONG8	sctcmtdlyfls2;	/* dmtdly log flushed anyway2 (success)	*/

	LONG8	sctlogfls;	/* log flush count			*/
	LONG8	sctlogtim;	/* log flush time			*/
	LONG8	sctchkbufwrt;	/* checkpoint index buffer writes	*/
	LONG8	sctchkchewrt;	/* checkpoint data cache writes		*/

	LONG8	sctrepfls;	/* replication log flush rqst		*/
	ULONG	sctmldmsec;	/* DELAYED_DURABILITY (in msecs)		*/
	ULONG	avail41[5];

	LONG8	sct_wrtcmp;	/* calls to ctwrtlog			*/
	LONG8	sct_no_cmp;	/* ctwrtlog below compression threshold	*/
	LONG8	sct_tp_cmp;	/* trantyp not compressed (DIFIMAGE)	*/
	LONG8	sct_rj_cmp;	/* ctwrtlg compression not effective	*/
	LONG8	sct_bytcmp;	/* total bytes saved by log compression	*/
	LONG8	sctdatflschk;	/*     data cache tran log checks	*/ 
	LONG8	sctdatfls;	/* data cache tran log flush rqst	*/
	LONG8	sctmldfls;	/*   MAX LOG DEFER log flush rqst	*/
	LONG8	sctrepflsbg;	/* replication log flush by background thread */
	} ctLOGSTT, ctMEM * pctLOGSTT;


/*
** File Snapshot Structure
*/

#define ctGFMSvern	3	/* ctGFMS (file snapshot) version #	*/
typedef struct ctgfms {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	ULONG	fixlen;		/* length of fixed portion of snapshot	*/
	ULONG	varlen;		/* length of variable region (if any)	*/
	LONG8	snapshottm;	/* snapshot time stamp: seconds since 70*/
	LONG8	phyrec;		/* physical file size			*/

	LONG8	numrec;		/* logical file size			*/
	LONG8	sernum;		/* serial number			*/
	LONG8	nument;		/* active entries			*/
	LONG8	hghtrn;		/* tran# high water mark for idx	*/

	LONG8	tstamp;		/* update time stamp			*/
	LONG8	mxfilz;		/* max file size			*/
	LONG8	fredops;	/* file specific # of read  ops		*/
	LONG8	fredbyt;	/* file specific # of bytes read	*/

	LONG8	fwrtops;	/* file specific # of write ops		*/
	LONG8	fwrtbyt;	/* file specific # of bytes written	*/
	LONG8	scthrtimbas;	/* high res timer ticks per sec^	*/
	LONG8	mhghbyt;	/* memory file high water bytes		*/

	LONG8	fredtim;	/* file specific disk read call time	*/
	LONG8	fwrttim;	/* file specific disk write call time	*/

	LONG8	avail8[6];

	LONG	idxhgt;		/* index height				*/
	ULONG	fileid;		/* unique file id			*/
	ULONG	servid;		/* unique server id			*/
	ULONG	timeid;		/* time id#				*/
	ULONG	nodsiz;		/* node size				*/
	ULONG	reclen;		/* fixed data record length		*/
	ULONG	logtyp;		/* permanent components of file mode	*/
	ULONG	maxkbl;		/* maximum key bytes leaf-var		*/

	ULONG	maxkbn;		/* maximum key bytes non leaf-var 	*/
	ULONG	filtyp;		/* flag for file type			*/
	ULONG	keylen;		/* key length 				*/
	ULONG	kmem;		/* key member #				*/
	ULONG	nmem;		/* number of members			*/
	ULONG	suptyp;		/* super file type 			*/
	ULONG	maxmrk;		/* maximum exc mark entries per leaf	*/
	ULONG	hdrseq;		/* wrthdr sequence #			*/

	ULONG	floktry;	/*  total lock attempts			*/
	ULONG	flokhlk;	/* header lock attempts			*/
	ULONG	flokblk;	/*  total lock wait count		*/
	ULONG	flokhbk;	/* header lock wait count		*/
	ULONG	flokdlk;	/* deadlocks				*/
	ULONG	flokdny;	/*  total locks denied			*/
	ULONG	flokfre;	/*  total locks freed			*/
	ULONG	flokrel;	/*  total blocks released		*/

	ULONG	flokcur;	/* current count of locks held		*/
	ULONG	fblkcur;	/* current count of blocked requests	*/
	ULONG	datlmt;		/* max number of special cache pages	*/
	ULONG	datspl;		/* actual number of special cache pages	*/
	ULONG	bufcnt;		/* number of buffer pages		*/
	ULONG	datcnt;		/* number of data cache pages		*/
	ULONG	numchn;		/* number of channels			*/
	ULONG	fusrcnt;	/* number of users with file open	*/

	ULONG	memcnt;		/* current # of memory records		*/
	ULONG	hghcnt;		/* high water # of memory recors	*/
	ULONG	flokkil;	/* killed locks				*/
	ULONG	updcnt;		/* count of updated pages		*/
	ULONG	updidxbuf;	/* count of updated index buffers	*/
	ULONG	avail4[3];

	ULONG	contents;	/* bit map of var len contents		*/
	LONG	segmax;		/* maximum # of segments		*/
	LONG	seglst;		/* # activated segments			*/
	UTEXT	updflg;		/* update (corrupt) flag		*/
	UTEXT	ktype;		/* file type flag			*/
	UTEXT	autodup;	/* duplicate flag			*/
	UTEXT	deltyp;		/* flag for type of idx delete		*/
	UTEXT	keypad;		/* padding byte				*/
	UTEXT	flflvr;		/* file flavor				*/
	UTEXT	flalgn;		/* file alignment			*/
	UTEXT	flpntr;		/* file pointer size			*/
	UTEXT	sflvr;		/* server byte order			*/
	UTEXT	salgn;		/* server alignment			*/
	UTEXT	spntr;		/* server pointer size			*/
	TEXT	availt[9];

	TEXT	filename[256];	/* file name				*/
/*
   NOTE: When modifying this structure, remember: 
     1) We require this structure's size to be a multiple of 32.
     2) Update revGFMSbyt() in ctstat.c as needed to byte flip the new fields.
     3) Increment the GFMS structure version (ctGFMSvern) above.
*/
} ctGFMS, ctMEM * pctGFMS;

/*
** User Snapshot Structure
*/

#define ctGUMSvern	2	/* ctGUMS (user snapshot) version #	*/
typedef struct ctgums {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	ULONG	fixlen;		/* length of fixed portion of snapshot	*/
	ULONG	varlen;		/* length of variable region (if any)	*/
	ULONG	contents;	/* bit map of var len contents		*/
	ULONG	unused;		/* available for use			*/
	LONG8	snapshottm;	/* snapshot time stamp: seconds since 70*/

	LONG8	strntsum;	/* user trntime sum^			*/
	LONG8	strntmax;	/* user trntime max^			*/
	LONG8	scthrtimbas;	/* high res timer ticks per sec^	*/
	LONG8	strntbox;	/* width of trntdet boxes^		*/
	LONG8	avail8[8];	/* available for use			*/

	LONG8	smarktim[8];	/* user mark elapsed times^		*/
	ULONG	smarkcnt[8];	/* user mark counts			*/

	ULONG	strntdet[ctTRNTdetail];
				/* trntime detail			*/

	ULONG	slOWNR;		/* thread handle (OWNER)		*/
	ULONG	sisolev;	/* transaction isolation level		*/
	ULONG	sctops;		/* set operation state bit mask		*/
	ULONG	sctstate;	/* internal state bit mask		*/
	ULONG	sabnlog;	/* begtran log for abandoned tran	*/
	ULONG	strntcnt;	/* user trntime count			*/
	ULONG	sctutrbeg;	/* user tran begin count		*/
	ULONG	sctutrend;	/* user tran end count			*/

	ULONG	sctutrabt;	/* user tran abort count		*/
	ULONG	snbrfile;	/* number of files in use		*/
	ULONG	slogtime;	/* logon time				*/
	ULONG	srqstime;	/* last request time			*/
	ULONG	srqsfunc;	/* last request function #		*/
	ULONG	srqssubf;	/* last request sub-function #		*/
	ULONG	sactflag;	/* active / inactive flag		*/
	ULONG	sct_trdflg;	/* thread operation flag		*/

	ULONG	sabnflg;	/* stage of abandon tran processing	*/
	ULONG	sctusrprf;	/* user profile word			*/
	ULONG	sctumxfil;	/* max files for user			*/
	ULONG	scthghfil;	/* highest file number limit		*/
	ULONG	sloktry;	/*  total lock attempts			*/
	ULONG	slokhlk;	/* header lock attempts			*/
	ULONG	slokblk;	/*  total lock wait count		*/
	ULONG	slokhbk;	/* header lock wait count		*/

	ULONG	slokdlk;	/* deadlocks				*/
	ULONG	slokdny;	/*  total locks denied			*/
	ULONG	slokfre;	/*  total locks freed			*/
	ULONG	slokrel;	/*  total blocks released		*/
	ULONG	slokcur;	/* current count of locks held		*/
	ULONG	sblkcur;	/* current count of blocked requests	*/
	ULONG	sctstat2;	/* internal state bit mask 2		*/
	ULONG	slokkil;	/* killed: removed from lock wait list	*/

	ULONG	sipaddr;	/* client IP address			*/
	ULONG   sip6addr[4];	/* client IPv6 address			*/
	ULONG	avail4[3];

	UTEXT	clflvr;		/* user flavor				*/
	UTEXT	clalgn;		/* user alignment			*/
	UTEXT	clpntr;		/* user pointer size			*/
	UTEXT	sflvr;		/* server byte order			*/
	UTEXT	salgn;		/* server alignment			*/
	UTEXT	spntr;		/* server pointer size			*/
	UTEXT	availt[26];

	TEXT	snodname[32];	/* node name				*/
	TEXT	sct_userid[32];	/* user id				*/
/*
   NOTE: When modifying this structure, remember: 
     1) We require this structure's size to be a multiple of 32.
     2) Update revGUMSbyt() in ctstat.c as needed to byte flip the new fields.
     3) Increment the GUMS structure version (ctGUMSvern) above.
*/
} ctGUMS, ctMEM * pctGUMS;

#define ctSQLSvern	2	/* ctSQLS (system snapshot) version #	*/
typedef struct ctsqls {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	ULONG	fixlen;		/* length of fixed portion of snapshot	*/
	ULONG	varlen;		/* length of variable region (if any)	*/
	ULONG	contents;	/* bit map of var len contents		*/
	ULONG	unused;		/* available for use			*/

	LONG8	snapshottm;	/* snapshot time stamp: seconds since 70*/
	LONG8	sctmemhgh;	/* SQL memory highwater mark		*/
	LONG8	sctmemsum;	/* current aggregate sum		*/
	LONG8	sctdscrqs;	/* dynamic statement cache requests	*/
	LONG8	sctdschit;	/* dynamic statement cache hits		*/
	LONG8	sctsscrqs;	/* static statement cache requests	*/
	LONG8	sctsschit;	/* static statement cache hits		*/

	LONG	sctmemcnt;	/* current net SQL memory allocations	*/
	LONG	sctdsctot;	/* current dynamic stmt cache entries	*/
	LONG	sctdschgh;	/* highest dynamic stmt cache entries	*/
	LONG	sctdscmax;	/* maximum dynamic stmt cache entries	*/
	LONG	sctssctot;	/* current static stmt cache entries	*/
	LONG	sctsschgh;	/* highest static stmt cache entries	*/
	LONG	sctsscmax;	/* maximum static stmt cache entries	*/

	UTEXT	sflvr;		/* server byte order			*/
	UTEXT	salgn;		/* server alignment			*/
	UTEXT	spntr;		/* server pointer size			*/
	TEXT	availt;		/* available for use			*/

	LONG	sctdyn;		/* current number of dynamic caches */
	LONG	sctsta;		/* current number of static caches */
	LONG	sctloc;		/* current number of local caches */
	LONG	sctlsctot;	/* current local stmt cache entries	*/
	LONG	sctlschgh;	/* highest local stmt cache entries	*/
	LONG	sctlscmax;	/* maximum local stmt cache entries	*/
	
	LONG8	sctlscrqs;	/* local statement cache requests	*/
	LONG8	sctlschit;	/* local statement cache hits		*/
	LONG8	sctidxonly;	/* Tuple fetches by index only scan */
	LONG8	sctidxrec;	/* Tuple fetches by index scan with record retrival */
	} ctSQLS, ctMEM * pctSQLS;

/* end of SNAPSHOT definitions */

/* replication agent states */
enum {
	raSTATmstcon = 1,	/* connecting to master server		*/
	raSTATlclcon = 2	/* connecting to local server		*/
};

enum {
	raSTATidle   = 0,	/* idle					*/
	raSTATmstop  = 1,	/* in call to master server		*/
	raSTATlclop  = 2,	/* in call to local server		*/
	raSTATpaused = 3,	/* replication agent has been paused	*/
	raSTATexited = 4	/* thread has exited			*/
};

#define FOREVER	for (;;)

#define ctLGON_TIME_INFINITE	(ULONG)-1

#ifndef ctUPF
#define ctUPF
#define USERPRF_NTKEY	 0x0001		/* DO NOT PERFORM AUTO TFRMKEY	*/
#define USERPRF_SAVENV	 0x0002		/* SAVENV MODE FOR TRANSACTIONS	*/
#define USERPRF_TRANREPL 0x0004		/* use transactional replication*/
#define USERPRF_SERIAL	 0x0008		/* ENABLE STRICT SERIALIZATION	*/
#define USERPRF_MEMABS	 0x0010		/* INTERNAL MEMORY MANAGEMENT	*/
#define USERPRF_NDATA	 0x0020		/* DO NOT PERFORM AUTO DATA -	*/
					/* 	UNIFRMAT CONVERSION	*/
#define USERPRF_LOCLIB	 0x0040		/* USE A LOCAL LIBRARY: not srvr*/
#define USERPRF_PTHTMP	 0x0080		/* add tmpname to input path	*/
					/* otherwise use system tmpname */
#define USERPRF_CODCNV	 0x0100		/* auto language conversion	*/
#define USERPRF_CLRCHK	 0x0200		/* clear transaction logs	*/
#define USERPRF_CUSTOM	 0x0400		/* custom server application	*/
#define USERPRF_ENCRYPT	 0x0800		/* enable encryption		*/
#define USERPRF_ADMSPCL	 0x1000		/* full admin logon		*/
#define USERPRF_LOGRED	 0x2000		/* read-only active log open	*/
#define USERPRF_REPLWRT	 0x4000		/* replication writer		*/
#endif /* ctUPF */

#define SYSMON_MAIN		0	/* mirror alerts & dynamic dumps*/
#define SYSMON_PERF		1	/* performance related events	*/
#define SYSMON_OFF		99	/*
					** only the same user thread that
					** started a SYSMON can call
					** SYSMON_OFF to cancel it. A user
					** thread in the ADMIN group can
					** cancel a SYSMON using the
					** following modes.
					*/
#define SYSMON_CANCEL_MAIN	100	/* cancel SYSMON_MAIN		*/
#define SYSMON_CANCEL_PERF	101	/* cancel SYSMON_PERF		*/
					/********************************/

/* connection options */
#define CONNOPT_WRITEOK		0x00000001	/* writes allowed to read-only server */
#define CONNOPT_FCTHREADS	0x00000002	/* FairCom threading enabled */

/* client library options */
#define CLIOPT_BROADCAST   0x00000001 /* enable client notification through broadcast reading thread */
#define CLIOPT_BROADCAST_DEBUG   0x00000002 /* enable client notification through broadcast reading debug */

/*
** performance monitor codes
*/
#define ctPMtimeBase		10000
#define	ctPMbegCheckpoint	10001
#define	ctPMendCheckpoint	10002
#define	ctPMbegLogExtension	10003
#define	ctPMendLogExtension	10004
#define ctPMLongTransaction	10005


#define ctFUSRCLRWRTLOG	0x00000001	/* used with ctBEHAV_FUSRCLR */
#define ctDEFERBEG	    0x0008	/* defer TRANBEG until update*/
#define ctSHADOW	    0x0010	/* shadow file		     */
#define ctLOGFIL	    0x0020	/* log file (=> shadow)	     */
#define ctTWOFASE	0x00000040	/* two phase transaction     */
#define ctPENDERR	0x00000080	/* pending error	     */
#define ctSAVENV	0x00000100	/* save environment	     */
#define ctAUTOTRN	0x00000200	/* automatic transaction     */
#define ctLKSTATE	0x00000400	/* LKISAM enabled	     */
#define ctDELUPDT	0x00000800	/* => ct_usrix is for delete */
#define ctSETSEGTRN	0x00001000	/* ctSETSEG transaction	     */
#define ctANYSEGTRN	0x00002000	/* any type SEG transaction  */
#define ctCOMMIT_SWAP	0x00004000	/* TRANEND/TRANBEG on swap   */
#define ctAUTOSAVE	    0x8000	/* automatic savepoints	     */
#define ctTRANDEP_DEL	0x00010000	/* TRANDEP DEL have occurred */
#define ctTRANDEP_SFM	0x00020000	/* TRANDEP DEL with MBR_SUPER*/
#define ctFORCEI	0x00040000	/* force image processing    */
#define ctDEFERCP	0x00080000	/* defer checkpoint	     */
#define ctTRANDEP_CRE	0x00100000	/* TRANDEP CRE have occurred */
#define ctTRANDEP_DRP	0x00200000	/* TRANDEP DROPIDX pending   */
#define ctNESTED_END	0x00400000	/* nested TRANEND call	     */
#define ctEXSPART_PND	0x00800000	/* partition exist pending   */
#define ctOVRFASE	0x01000000	/* tranovr processing	     */
#define ctCIPFASE	0x02000000	/* promote WRL to WXL phase  */
#define ctPENDREN	0x04000000	/* file rename pending	     */
#define ctPENDRNU	0x08000000	/* undo rename pending	     */
#define ctTRANDEP_REN	0x10000000	/* TRANDEP REN have occurred */
#define ctLIGHTTRAN	0x20000000	/* light weight tran: noflush*/
#define ctRSTHDR_OPS	0x40000000	/* restore header operations */
#define ctUNDO_OCMTX	0x80000000	/* undo...2() and rqs ocsema */

#define ctMSKSEGTRN	(ctSETSEGTRN | ctANYSEGTRN)

#define ctSAVECTREE	1
#define ctRESTORECTREE	2

/* GETRES() resmode bits: */
#define RES_LOCK	0x0001		/* lock the resource		*/
#define RES_TYPNUM	0x0002		/* search type type and number	*/
#define RES_TYPE	0x0004		/* search by resource type	*/
#define RES_FIRST	0x0008		/* read first resource		*/
#define	RES_NAME	0x0010		/* search by resource name	*/
#define RES_POS		0x0020		/* search by resource position	*/
#define RES_LENGTH	0x0040		/* return length of resource	*/
#define RES_NEXT	0x0080		/* read next resource		*/
#define RES_SRVR	0x0100		/* called within server		*/
#define RES_PPND	0x0200		/* prepend string		*/
#define RES_ENUM	0x0400		/* enumerate resource types	*/

/* BATSET()/BATSETX() mode bits: */
#define BAT_CAN		0x0001		/* cancel batch			*/
#define BAT_NXT		0x0002		/* subsequent batch retrieval	*/
#define BAT_GET		0x0003		/* batch retrieval		*/
#define BAT_DEL		0x0004		/* batch delete			*/
#define BAT_UPD		0x0005		/* batch rewrite		*/
#define BAT_INS		0x0006		/* batch insertion		*/
#define BAT_OPC_RESV	0x0007

#define BAT_PKEY	0x0000		/* partial key retrieval	*/
#define BAT_RET_FIX	0x0008		/* return fixed length portion	*/
#define BAT_VERIFY	0x0010		/* verify key and record image	*/
#define BAT_RET_REC	0x0020		/* return records w/ len & pos	*/
#define BAT_RET_POS	0x0040		/* return record positions	*/
#define BAT_RET_KEY	0x0080		/* return key values		*/
#define BAT_GKEY	0x0100		/* key order retrieval til EOF	*/
#define BAT_RPOS	0x0200		/* retrieve based on record pos	*/
#define BAT_KEYS	0x0400		/* retrieve based on key values	*/
#define BAT_LOK_RED	0x0800		/* read locks on retrieval	*/
#define BAT_LOK_WRT	0x1000		/* write locks on retrieval	*/
#define BAT_COMPLETE	0x2000		/* must acquire locks on entire
					   batch			*/
#define BAT_FLTR	0x4000		/* N/A: filters w/ SETFLTR()	*/
#define BAT_LOK_KEEP	0x8000		/* keep locks after batch ends	*/

#define BAT_PHYS	0x00010000	/* retrieve phys order til EOF	*/
#define BAT_RNGE	0x00020000	/* retrieve based on ALCRNG	*/
#define BAT_LKEY	0x00040000	/* reverse key order til BOF	*/
#define BAT_LOK_ONE	0x00080000	/* one-at-a-time record locks
					   released immediately after
					   record is read		*/
#define BAT_LOK_BLK	0x00100000	/* blocking RED or WRT locks	*/
#define BAT_RET_BLK	0x00200000	/* return records as contiguous
					   block w/o position info	*/
#define BAT_RET_RAW	0x00400000	/* no conversion of contents of
					   outbuf with heterogenious
					   connections			*/
#define BAT_INP_RAW	0x00800000	/* no conversion input buffer	*/
#define BAT_CLSE	0x01000000	/* close exhausted batch im-
					   mediately with ctFeatBATSIG	*/
#define	BAT_EXTENSIONS	0x02000000	/* reserved to indicate new
					   batch extensions in use	*/
#define	BAT_UPD_KEY	0x04000000	/* [var len] oldkey
						record image ...	*/
#define BAT_UPD_KEPSRL	0x08000000	/* update preserves serial nbr	*/
#define BAT_BTBZ_ERR	0x10000000	/* return req space on BTBZ_ERR	**
					** in bavail slot of PKEYREQ	*/
#define BAT_REVERSE	0x20000000	/* return results in reverse order */

/*
** batch update return status word
*/
#define BAT_STT_UPDATE	0x00000001	/* error on rewrite		*/
#define BAT_STT_ADD	0x00000002	/* error on insertion		*/
#define BAT_STT_DELETE	0x00000004	/* error on delete		*/
#define BAT_STT_REDIREC	0x00000008	/* error on reading old record	*/
#define BAT_STT_EQLKEY	0x00000010	/* error on equal key		*/
#define BAT_STT_BUFSIZ	0x00000020	/* record image area too small	*/
#define BAT_STT_FRMKEY	0x00000040	/* problem assembling or trans-
					   forming unique key value	*/
#define BAT_STT_GTVLEN	0x00000080	/* error on get var rec length	*/
#define BAT_STT_GETMEM	0x00000100	/* error allocating record buf	*/
#define BAT_STT_CONVERT	0x00000200	/* error converting rec image	*/

/*
** exclusive BAT options
*/
#define BAT_REQ_options	(BAT_PKEY | BAT_GKEY | BAT_LKEY | BAT_KEYS | BAT_RPOS | BAT_RNGE | BAT_PHYS) /* NOTE: BAT_PKEY == 0 */

#define BAT_LOK_options	(BAT_LOK_RED | BAT_LOK_WRT)

#define BAT_RET_options	(BAT_RET_REC | BAT_RET_FIX | BAT_RET_POS | BAT_RET_KEY | BAT_RET_BLK)

/*
** getIDfield modes
*/
#define updateValue	1	/* return next IDfield value and update the
				** IDfield value; for transaction file, must
				** be in active transaction		     */ 
#define reportValue	2	/* return next IDfield value but do not
				** update the IDfield			     */
#define deltaValue	3	/* return delta for IDfield		     */
#define startingValue	4	/* return starting value for IDfield	     */
#define lastparmValue	4	/* equal to the last mode value		     */

/*
** IDfield extended attributes
*/
#define IDfield_xtdatr_unsigned	0x00000001	/* unsigned IDfield	     */
#define IDfield_xtdatr_overflwd	0x00000002	/* values overflowed	     */
#define IDfield_xtdatr_versn__2	0x00000004	/* IDfield with xtdatr	     */
#define IDfield_xtdatr_versn__1	0x00000008	/* IDfield without xtdatr    */
#define IDfield_xtdatr_noovrflw	0x00000010	/* no overflow detection     */
#define IDfield_xtdatr_updated  0x00000020	/* xtdatr updated by	     **
						** xtdatrIDfield()	     */
#define IDfield_xtdatr_signed	0x00000040	/* signed IDfield: all tests **
						** of signed\unsigned use    **
						** only unsigned bit field   */

/*
** keydup attributes
*/

#define ctNODUPKEY	'\0'	/* no duplicates allowed		*/
#define ctDUPKEY	'\1'	/* duplicates allowed			*/
#define ctNOPDUPKEY	'\2'	/* no dupe within partition		*/
#define ctDISTINCTpart	'\3'	/* DUPKEY with whole & partial distinct	*/
#define ctDISTINCTuniq	'\4'	/* NODUPKEY with partial distinct	*/
#define ctDISTINCT	'\5'	/* DUPKEY with whole key distinct only	*/


/*
** file mode attributes
*/

#ifdef  ctSHARED
#undef  ctSHARED		/* conflict define in some Unix systems */
#endif

#define ctEXCLUSIVE 	0x0000		/* file in locked mode	     */
#define ctSHARED	0x0001		/* file in shared mode	     */
#define	ctVIRTUAL	0x0000		/* file is virtually opened  */
#define	ctPERMANENT	0x0002		/* file is physically opened */
#define	ctFIXED		0x0000		/* fixed length data	     */
#define	ctVLENGTH	0x0004		/* variable length data	     */
#define ctREADFIL	0x0008		/* read only file lock	     */
#define ctPREIMG	ctSHADOW	/* transactions w/o recovery */
#define ctTRNLOG	(ctLOGFIL | ctSHADOW) /* ctPREIMG + recovery */
#define ctWRITETHRU	0x0040		/* write thru buffering	     */
#define ctCHECKLOCK	0x0080		/* must own lock for update  */
#define ctDUPCHANEL	0x0100		/* two i/o channels	     */
#define ctSUPERFILE	0x0200		/* superfile shell	     */
#define ctCHECKREAD	0x0400		/* must own lock on read     */
#define ctDISABLERES	0x0800		/* disable resource on create*/
#define ctMIRROR_SKP	0x2000		/* OK to open primary w/o mir*/
#define ctOPENCRPT	0x4000		/* open corrupt file	     */
#define ctLOGIDX	0x8000		/* log index upper level     */

#define ctDUPCHANNEL	ctDUPCHANEL	/* accept both versions	     */
/*
** reuse file mode bits in unambiguous situations
*/
#define CTFILEUSRDATA	ctCHECKREAD	/* Special CTFILE Usr Data Flag-CTB */
#define CTEXWOPTS	ctCHECKREAD	/* Extended Write Operations	    */
#define ctMIRnam	ctDISABLERES	/* Special bit for mbopen/mbcrat to */
#define ctPRInam	~ctMIRnam	/* signify pri/mir name		    */

/*
** Special file mode bits used by mbopen()
*/
#define CTSPCOPN	0x00010000	/* Special read-only file open */

/*
** 8-byte extended file modes (ctHUGEFILE)
**
*/

#define ctFRC2HDRS	0x00000002L	/* forces extended (V7) header	   */
#define ctFRCXHDRS	ctFRC2HDRS
#define ctFILESEGM	0x00000008L	/* segmented file		   */
#define ctTRANDEP	0x00000010L	/* tran dependent create/delete	   */
#define ctFILEPOS8	0x00000040L	/* HUGE file			   */
#define ctNOSPACHK	0x00000080L	/* do not check for disk full	   */
#define ctNOENCRYP	0x00000100L	/* do not create with encryption   */
#define ctTRANMODE	0x00000200L	/* auto switch to ctLOGFIL	   */
#define ctPIMGMODE	0x00000400L	/* auto switch to ctSHADOW	   */
#define ctRSTRDEL	0x00000800L	/* trandep restorable delete	   */
/* service write-only	0x00001000L	   NOT available for use
**			0x00002000L	   future use
**			0x00004000L	   future use
**			0x00008000L	   NOT avilable for use
*/
#define ctNO2HDRS	0x00010000L	/* forces 128 byte (V6) header	   */
#define ctNO_XHDRS	ctNO2HDRS
#define ctLEXTSIZE	0x00020000L	/* large extent size		   */
#define ctFEXTSIZE	0x00040000L	/* first extent size		   */
#define ctMAXFILEZ	0x00080000L	/* maximum file size limit	   */
#define ctSPACEAVL	0x00100000L	/* spave available check enabled   */
#define ctSEGAUTO	0x00200000L	/* auto segment creation	   */
#define ctPARTHOST	0x00400000L	/* partition host file		   */
#define ctPARTAUTO	0x00800000L	/* auto partition naming (=> HOST) */
/* internal partition attributes	   NOT available for use
**			0x01000000L
**			0x02000000L
**			0x04000000L
**			0x08000000L
*/
#define ctADD2END	0x10000000L	/* deleted space is not re-used	   */
#define ct6BTRAN	0x20000000L	/* 6 byte transaction support	   */
#define ctNO6BTRAN	0x40000000L	/* no 6 byte tran support	   */
#define ctMEMFILE	0x80000000L	/* temporary memory resident file  */


/*
** flmode3
*/
#define ctMEMFILEindex	0x00100001L	/* temporary index for data MEMFILE.
					** 2 bits for "safety" since => auto
					** delete
					*/
#define ctTRNLOGthru	0x00000002L	/* use OS WRITETHRU instead of
					** buffer flushes for TRNLOG file
					** explicitly requested via
					** ctWRITETHRU file mode
					*/
		/*	0x00000004	is not available for use	   */
		/*	0x00000008	ctREPLICATE			   */
#define ctFILCRECHKmd3	0x00000010	/* signifies newly created file w/o
					** subsequent checkpoint
					*/
#define ctAUTO_PREIMG	0x00000020	/* AUTO_PREIMG turned on PREIMG	   */
#define ctAUTO_TRNLOG	0x00000040	/* AUTO_TRNLOG turned on TRNLOG	   */

#define ctREPLMAP	0x00000080	/* file is a replica		   */
#define ctSRVFILEmd3	0x00000100	/* special processing for API read */

		/*
		**	ctCompressRec, ctAugmentedFxd and ctIDFIELDint are
		**	used by splval AND flmode3. It is not essential
		**	that the splval and flmode3 bits match; it is a
		**	convenience.
		**
		**	several additional bits are be reserved for
		**	matching splval/flmode3 bits following 1000x
		*/

		/*	0x00000200	ctCompressRec			   */
		/*	0x00000400	ctAugmentedFxd			   */
		/*	0x00000800	ctIDFIELDint			   */
		/*	0x00001000	IS available (but not matching)	   */
		/*	0x00002000	ctNoFileSysFlush		   */
#define ctDYNPARTMBRmd3	 0x00004000L	/* dynamic partition members	   */
#define ctFLEXRECmd3	 0x00008000L	/* flexible record format	   */
#define ctNOISMKEYUPDmd3 0x00010000L	/* This data file has one or more
					** indices that do not allow an ISAM
					** record update to change the key.
					*/
#define ctDeferredIndexmd3 0x00020000	/* defer index operations	   */
#define ctIndexLoadPndgmd3 0x00040000	/* index load is pending	   */

		/*	0x00100000	is NOT available for use	   */

#define ctBlockCompressmd3 0x00200000L	/* file uses block compression	   */
#define ctVarlenNodeFmtmd3 0x00400000L	/* index file: improved efficiency of
					** variable-length key storage	   */
#define ctTranMarkOptmd3 0x00800000L	/* index file: improved efficiency of
					** transaction mark storage	   */
#define ctIndexCmpOffmd3 0x01000000L	/* index file: compressed offsets  */
#define ctIndexCmpMrkmd3 0x02000000L	/* index file: compressed transaction marks */
#define ctIndexCmpsRLEmd3 0x04000000L	/* index file: uses sRLE key compression */


/*
** XCREblk splval
*/
#define ctFILEOPENED	0x00000001L	/* file already opened		   */
#define ctINDEX4MEMF	0x00000002L	/* index for data MEMFILE	   */
#define ctKEEPOPEN	0x00000004L	/* file stays opened after last cls*/
#define ctREPLICATE	0x00000008L	/* create file with replication
					** enabled			   */
#define ctREPLICATEint	 0x00000010L	/* internal use only		   */
#define ctMEMFILEint	 0x00000020L	/* internal use only		   */
#define ctAUTO_PREIMGint 0x00000040L	/* internal use only		   */
#define ctAUTO_TRNLOGint 0x00000080L	/* internal use only		   */
#define ctATODEP	 0x00000100L	/* index/data TRANDEP consistency  */
#define ctCompressRec	 0x00000200L	/* compressed data records	   */
#define ctAugmentedFxd	 0x00000400L	/* records are inherently fixed
					** length			   */
#define ctIDFIELDint	 0x00000800L	/* partitioned file w/ IDfield	   */
#define ctAUTOMKDIR	 0x00001000L	/* create directories if needed    */
#define ctNoFileSysFlush 0x00002000L	/* skip file system flush for file */
#define ctDYNPARTMBR	 0x00004000L	/* dynamic partition members	   */
#define ctFLEXREC	 0x00008000L	/* flexible record format	   */
#define ctIDXOPENED	 0x00010000L	/* indices already opened	   */
#ifdef ctNOT_YET_IMPLEMENTED /* block compression is not yet implemented */
#define ctBlockCompress	 0x00020000L	/* file uses block compression	   */
#endif
#define ctKEEPOPENoffAtLogoff 0x00040000L /* clear keepopen on logoff	   */

/*
** Extended file open modes set by SetXtdFileOpenMode().
*/
#define ctXOPN_REDSHR	 0x00000001L	/* open with read-only sharing	   */
#define ctXOPN_COFILE_FILELOCK 0x00000002L /* inter-thread file locking hierarchy based on most restrictive co-file open */
#define ctXOPN_REPLADM	 0x00000004L	/* read/write open of replicated file for admin purposes */
#define ctXOPN_NORUCB_OK 0x00000008L	/* allow this file to be opened even if its RUCB DLL is not available */
#define ctXOPN_OPEN_IFNOT 0x00000010L	/* only open file is not already open by the caller */

/*
** BLKIREC
*/

#define ctBLKIREC_FIRST		1	/* no target used for these opcodes  */
#define ctBLKIREC_NEXT		2
#define ctBLKIREC_PREV		3
#define ctBLKIREC_LAST		4

#define ctBLKIREC_GT		10	/* target required for these opcodes */
#define ctBLKIREC_GTE		11
#define ctBLKIREC_EQL		12
#define ctBLKIREC_LTE		13
#define ctBLKIREC_LT		14


/* Flags used for the ctstate variable defined in CTGVAR		     */
/* ctstate is used for FairCom special internal reasons.		     */
#define CTSTATE_ODBC_READONLY	0x00000001L	/* ODBC read only control    */
#define CTSTATE_KANJI_CONVERT	0x00000002L	/* ODBC Kanji conversion     */
#define CTSTATE_NOFLUSH		0x00000004L	/* no flush on forced close  */
#define CTSTATE_CLISAM		0x00010000L
#define CTSTATE_PRTOPN		0x00020000L	/* partition member open     */
#define CTSTATE_HSTOPN		0x00040000L	/* partition host   open     */
#define CTSTATE_AFLUSH		0x00080000L	/* asynchronous flush thread */
#define CTSTATE_IDXIOR		0x00100000L	/* index disk read	     */
#define CTSTATE_DATIOR		0x00200000L	/* data  disk read	     */
#define CTSTATE_IDXIOW		0x00400000L	/* index disk write	     */
#define CTSTATE_DATIOW		0x00800000L	/* data  disk write	     */
#define CTSTATE_SNAPSHOT	0x01000000L	/* activated for snapshot    */
#define CTSTATE_LFW		0x02000000L	/* about to suspend on LFW   */
#define CTSTATE_SUS		0x04000000L	/* still suspended on LFW    */
#define CTSTATE_TRANDISC	0x08000000L	/* marked for TRAN disconnect*/
#define CTSTATE_CONTCLS		0x10000000L	/* continue with close	     */
#define CTSTATE_ISAMDFRCLS	0x20000000L	/* defer all cls/del shtifil */
#define CTSTATE_ADDKY_DEFERD	0x40000000L	/* defer key add ops on upd  */

#define CTSTATE_AVL_STPUSRA	CTSTATE_NOFLUSH	/* can be used in STPUSRA    */
#define ctNOFLUSH		0x0004
#define ctDISKIOshift		20		/* 20 bits		     */
#define ctDISKIObase		1000		/* sysiocod disk IO base val */
#define ctDISKIOshfmsk		0x0000000f	/* ctstate mask after shift  */
#define ctDISKIOmask		(CTSTATE_IDXIOR | CTSTATE_DATIOR | CTSTATE_IDXIOW | CTSTATE_DATIOW)


#define ctDISKIO_IDXR		0x0001		/* sysiocod test bits	     */
#define ctDISKIO_DATR		0x0002
#define ctDISKIO_IDXW		0x0004
#define ctDISKIO_DATW		0x0008


#define ctCNDXclbkCHR		'@'
#define ctCNDXclbkSTR		"@"
#define ctCNDXclbkREAD		'?'
#define ctCNDXclbkWRITE		'!'
#define ctCNDXclbkDLL		'#'

#define frmkeyCNDXskip		0x0001		/* skip conditional index
						** check during frmkey	    */

#define ctROWL_READ		1
#define ctROWL_WRITE		2
#define ctROWL_ADDREC		3
#define ctROWL_DELREC		4
#define ctROWL_RWTREC		5


	/* owner permissions	*/
#define OPF_NONE	0x00001L
#define OPF_READ	0x00002L
#define OPF_WRITE	0x00004L
#define OPF_DEF		0x00008L
#define OPF_DELETE	0x00010L
#define OPF_ALL		(OPF_READ | OPF_WRITE | OPF_DEF | OPF_DELETE)

	/* group permissions	*/
#define GPF_NONE	0x00020L
#define GPF_READ	0x00040L
#define GPF_WRITE	0x00080L
#define GPF_DEF		0x00100L
#define GPF_DELETE	0x00200L
#define GPF_ALL		(GPF_READ | GPF_WRITE | GPF_DEF | GPF_DELETE)

	/* world permissions	*/
#define WPF_NONE	0x00400L
#define WPF_READ	0x00800L
#define WPF_WRITE	0x01000L
#define WPF_DEF		0x02000L
#define WPF_DELETE	0x04000L
#define WPF_ALL		(WPF_READ | WPF_WRITE | WPF_DEF | WPF_DELETE)

#define OPF_NOPASS	0x08000L /* read only without password */
#define GPF_NOPASS	0x10000L
#define WPF_NOPASS	0x20000L

#define OPF_ISAMKOFF	0x40000L /* suppress full ISAM key buffer support */

#define ctNONEXCLUSIVE	(ctREADFIL | ctSHARED)
#define COMPLETE	ctEXCLUSIVE
#define PARTIAL		ctSHARED
#define NOTREUSE	0x0010		/* key type modifier: !reuse nodes  */

#define REGADD   	0	/* See ADDKEY: split full nodes in half     */
#define INCADD   	1	/* split nodes to handle increasing values  */
#define DECADD   	2	/* split nodes to handle decreasing values  */

#define FRSADD		0	/* See LOADKEY: first call to LOADKEY	    */
#define NXTADD		1	/* subsequent calls to LOADKEY		    */
#define BLDADD		2	/* call to signal completion of LOADKEY	    */

#ifndef ctLKIMDS
#define ctLKIMDS
#define	ctFREE		0	/* free all pending data record locks	    */
#define ctRESET		1	/* same as ctFREE followed by ctENABLE, etc.*/
#define ctENABLE	2	/* enable non-blocking data record locks    */
#define ctENABLE_BLK	3	/* enable blocking data record locks	    */
#define ctREADREC	4	/* enable read only record locks	    */
#define ctSUSPEND	5	/* temporarily suspend enable mode	    */
#define ctRESTORE	6	/* restore enable mode			    */
#define ctRESTRED	7	/* restore read lock mode		    */
#define ctRESTORE_BLK	8	/* restore enable_blk mode		    */
#define ctKEEP		9	/* no affect: as if LKISAM not called	    */
#define ctFREE_TRAN	10	/* used by TRANEND to signal FREE from tran */
#define ctREADREC_BLK	11	/* enable blocking data record read locks   */
#define ctLK_RSV	12		/* not used */
#define ctLK_RSV_BLK	13		/* not used */
#define ctRESTRED_BLK	14	/* restore blocking read lock mode	    */
#define ctRESTRSV	15		/* not used */
#define ctRESTRSV_BLK	16		/* not used */
#ifdef ctSS
#define ctSS_LOCK	17	/* enable strict serialization		    */
#endif
#define ctFREE_FILE	18	/* free all user locks for given data file  */
#ifdef ctSS
#define ctAG_LOCK	19	/* strict serialization aggregate lock	    */
#endif
#define ctFREE_ISAM	20	/* free all ISAM locks for given data file  */
#define ctCHKLOK	21	/* check for user lock			    */
#define ctFREE_WRTLOKS	22	/* free all write locks for a data file	    */
#define ctLOCK_FILE	23	/* acquire file level read or write lock    */
#define ctUNLOCK_FILE	24	/* release file level read or write lock    */
#define ctFREE_REDLOKS	25	/* free all read locks for a data file	    */
#define ctCHK_ANYLOK	26	/* check if the table has any user lock     */
#define ctCHKLOK_OTHER	27	/* check for lock by other connection/datno */
#define ctENABLE_BLKRQS 28	/* enable forced blocking data record locks */
/*
   Add new LOKREC() lock mode here and increment ctLOKMOD_LAST.
   NOTE: Before using 41 or greater for a new LOKREC() lock mode, check if
   overlap of LOKREC() lock values with the macros defined below will be a
   problem. If so, use the next unused value for a new LOKREC() lock mode.
*/
#define ctLOKMOD_LAST	28	/* last defined LOKREC() lock mode */
#define ctLOKMOD_MASK	0x000000ff /* valid range of LOKREC() lock modes */

#define ctLK_BLOCK	1	/* used with ctENABLE to make ctENABLE_BLK  */
#define ctGETLKISAM	128	/* LKISAM: return current lock state	    */
#endif

#define ctKEEP_OUT	41	/* keep locks obtained outside of tran and
				   not touched inside of tran		   */
#define ctKEEP_OUT_ALL	42	/* keep locks obtained outside of tran,
				   whether or not touched in transaction   */
#define ctFREEend	43	/* internal use				   */
#define ctKEEP_XFREED	44	/* keep all locks except those explicitly
				   freed during transaction		   */
#define ctDYNHASHskip_f	45	/* skip dynamic hash operations (on free)  */

/* lock options to be OR'd in with lock mode value: */
#define ctNOFLUSHtran	0x00000100 /* skip log flush on transaction end	   */
#define ctLK_RECR	0x00000200 /* recursive lock/unlock request	   */
/*
**			0x00000400 APPARENTLY not in use. double check
				   before assigning a new lock related
				   constant to 1024.
*/
#define ctLK_NotInUse	0x00000400
#define ctMARK_XFREED	0x00000800 /* mark explicitly freed locks in tran  */
#define ctIMPERSONATE	0x00001000 /* thread being impersonated		   */
#define ctQTwpuspndg	0x00002000 /* ctQTwpus pending			   */
#define ctDYNHASHskip_l	0x00004000 /* skip dynamic hash operations (on lock) */
#define ctMULTIOPNreplc	0x00008000 /* replacing primary lock (must update
				   ** system lock table user file number)  */

#define ctSS_LOCKOFF	1L	/* ctSS lock offset (code still uses literal)*/ 
#define ctAG_LOCKOFF	2L	/* offset for aggregate locks (code still uses literal)*/
#define INTENT_LOCKOFF	3L	/* intent/table locking offset */
#define	NEWREC_LOCKOFF	4L	/* NEWREC/inewvrec fallback offset */

#ifdef ctFeatRECRLOCK
#define ctTRNBEGLK	(ctENABLE | ctREADREC | ctLK_BLOCK | ctLK_RECR)
#else
#define ctTRNBEGLK	(ctENABLE | ctREADREC | ctLK_BLOCK)
#endif
/*
** special mode bits not for use with LKISAM
*/
#define ctNotForLKISAM	(ctMULTIOPNreplc | ctDYNHASHskip_l | ctQTwpuspndg | ctIMPERSONATE | ctMARK_XFREED | ctNOFLUSHtran | ctLK_NotInUse)


/*
** datno values for use with LOKREC's ctFREE_FILE mode to free all locks for all
** files of the specified types that are open by the caller:
**
** Example:
**
** LOKREC(ctFREEALL_TRAN,ctFREE_FILE,0);
*/
#ifdef ctFeatMAXFILE32
#define iFREEALL_INDICATOR	0x80000000	/* high bit set to indicate FREEALL */
#else
#define iFREEALL_INDICATOR	0x8000	/* high bit set to indicate FREEALL */
#endif
#define iFREEALL_INDICATOR2B	0x8000	/* 2-byte file number FREEALL indicator */
#define iFREEALL_NOTRAN		0x0001	/* non-transaction files	    */
#define iFREEALL_NOIICT		0x0002	/* transaction files not using IICT */
#define iFREEALL_IICT		0x0004	/* transaction files with IICT on   */

#define ctFREEALL_NOTRAN	(iFREEALL_INDICATOR | iFREEALL_NOTRAN)
#define ctFREEALL_NOIICT	(iFREEALL_INDICATOR | iFREEALL_NOIICT)
#define ctFREEALL_IICT		(iFREEALL_INDICATOR | iFREEALL_IICT)

#define ctFREEALL_TRAN		(ctFREEALL_NOIICT | ctFREEALL_IICT)
#define ctFREEALL_ALL		(ctFREEALL_NOTRAN | ctFREEALL_TRAN)


#define ctISAMLOCK	1	/* isam level lock			   */
#define ctNEWRECFLG	2	/* new record flag			   */
#define ctTRANLOCK	4	/* lock obtained or touched in transaction */
#define ctTRANOUT	8	/* lock obtained outside of transaction	   */
#define ctREPLCLOK	16	/* reopen deferred-close lock reassignment */
#define ctTRANMOV	32	/* var length record move on rewrite	   */
#define ctXFREED	64	/* explicit FREE requested for lock	   */
#define ctMULTIOPNlock	128	/* system lock with different file#, same
				** user					   */
/* note: values 256 and greater require more than 1 byte (see LOKS ltisam) */
#define ctFILESHARElock	256	/* lock request for file sharing support on
				** Unix systems				   */
#define ctFILEIOlock	512	/* file I/O lock request		   */
#define ctREMAPlock	1024	/* user lock table call requires remapping
				** the physical offset to a virtual offset */

/*
** Option bits that can be specified in ctuutbl81()'s options parameter:
*/
#define ctUUTBLremap	0x00000001 /* remap() physical offset to virtual   */
#define ctUUTBLiolok	0x00000002 /* I/O lock unlock request		   */
#define ctUUTBLfshrlok	0x00000004 /* File sharing lock unlock request	   */

/*
** Transaction Isolation Levels
*/
#define ctISONON	(-1)	/* no special isolation actions		 */ 
#define ctISODRT	0	/* dirty reads				 */
#define ctISOCLN	1	/* clean updates			 */
#define ctISORR		2	/* repeatable reads (individual records) */
#define ctISOSS		3	/* strict serialization			 */
#define ctISOMAX	3


/*
** GETFIL modes
*/
#define RECLEN		0
#define KEYLEN		1
#define FILTYP		2
#define FILMOD		3
#define REVMAP		4
#define KEYTYP		5
#define KEYDUP		6
#define NULKEY		7	/* ISAM nul key flag		*/
#define LOGSIZ		10
#define PHYSIZ		11
#define NODSIZ		12
#define KEYMEM		13
#define KEYPAD		14
#define FLDELM		15
#define RECPAD		16
#define MIRRST		17
#define RELKEY		18
#define PERMSK		19
#define FILDEF		20
#define ALIGNM		21
#define EXTSIZ		22
#define SUPTYP		23
#define SUPMBR		24
#define UPDFLG		25
#define XFLMOD		26
#define LXTSIZ		27
#define FXTSIZ		28
#define NKYMEM		29	/* number of members in index	*/
#define PRTKEY		30	/* relative partition key#	*/
#define BEGBYT		31	/* beginning byte of data area	*/
#define UNQKEY		32	/* replicated file unique key	*/
#define FLMODE2		33	/* flmode2			*/
#define FLMODE3		34	/* flmode3			*/
#define FILEID		35	/* seqn component of Unique ID	*/
#define TIMEID		36	/* time component of Unique ID	*/
#define SERVID		37	/* srvr component of Unique ID	*/
#define FRSACTPRT	38	/* first active partition #	*/
#define LSTACTPRT	39	/* last active partition #	*/
#define NUMACTPRT	40	/* number of active partitions	*/
#define SCHMID		41	/* current schema ID		*/
#define SRLPOS		42	/* SRLSEG/SCHSEG offset		*/
#define SRLLEN		43	/* SRLSEG/SCHSEG length		*/
#define MAXMBRPRT	44	/* max # of partition members*/

/*
** GETFILX modes
*/
#define DFRKOPS		0	/* deferred key operation count	*/
#define DFRKLOD		1	/* background index load pending*/

#define DATA_FILE	0
#define INDX_FILE	1
#define VDAT_FILE	2

#define NON_SUPER	0
#define HST_SUPER	1
#define MBR_SUPER	2
#define IDX_SUPER	6

/*
** GETNAM mode values
*/
#define FILNAM		0
#define FRSFLD		1
#define LSTFLD		2
#define IDXNAM		3
#define MIRNAM		4
#define OWNNAM		5
#define GRPNAM		6
#define DEXTNAM		7
#define IEXTNAM		8
/*
** modes >= 128 do NOT require a valid file number
*/
#define GETNAMsyswide	128
#define WRKDIR		128	/* server's working directory		*/
#define FILPTH		129	/* file path modifier			*/
#define MIRPTH		130	/* mirrored file path modifier		*/
#define SRVNAM		131	/* server name				*/
#define FIRST_ITEM	132	/* get first name on specified list	*/
#define NEXT_ITEM	133	/* get next name on list		*/
#define ctNODEID	134	/* server node ID for replication	*/
#define ctREPLVER	135	/* server replication support version	*/
#define CURTIME 	136	/* server current date time	*/
#define CURTIMETM 	137	/* server current date time in local TZ */
#define ctREPLOPTS	138	/* replication configuration options	*/
#define BASEDIR		139	/* server's base directory		*/

/* Offsets of values in output buffer for ctREPLOPTS mode: */
#define ctREPLOPT_SRLSEGSRC	0 /* REPL_SRLSEG_USE_SOURCE setting	*/
#define ctREPLOPT_IDENTITYSRC	1 /* REPL_IDENTITY_USE_SOURCE setting	*/


/*
** PUTHDR modes
*/
#define ctSERNUMhdr	1
#define ctTSTAMPhdr	2
#define ctNUMENThdr	3
#define ctTIMEIDhdr	4
#define ctLOGEOFhdr	5
#define ctPHYEOFhdr	6
#define ctDELSTKhdr	7
#define ctUNIQIDhdr	8

#define ctALIGNhdr	17
#define ctFLAVORhdr	18
#define ctXFLSEThdr	19
#define ctXFL_ONhdr	20
#define ctXFLOFFhdr	21
#define ctEXTSIZhdr	22
#define ctSUSSRLSEGhdr	23
#define ctREPLICATEhdr	24
#define ctMAXPARTMBRhdr	25	/* maximum partitions for this host; auto purge */

#define ctUSERhdr	32	/* this bit signifies non-permanent, user only*/
#define ctISAMKBUFhdr	33
#define ctSPLREFRESHhdr	34
#define ctSPLSTOPhdr	35
#define ctSPLRESUMEhdr	36
#define ctSCANCACHEhdr	37
#define ctDBGCMTLOKhdr	38
#define ctADDKYDFRhdr	39
#define ctLOCKDFRhdr	40
#define ctTRNPERShdr	41
#define ctISAMKBUFctx	42
#define ctSKIPSAVEhdr	43
#define ctSKIPSAVEISAMhdr 44
#define ctIDfieldOverRide 45
#define ctIICThdr	46
#define ctADDUNQFRShdr	47
#define ctNOFILELISThdr	48
#define ctMULTIOPNhdr	49
#define ctIDfieldPreserve 50
#define ctNOISMKEYUPDhdr 51

#define ctV7FILEhdr	64	/* this bit signifies only extended header use*/
#define ctMXFILZhdr	65
#define ctLXTSIZhdr	66
#define	ctGUIxIDXENThdr	67	/* turn on/off DEF_MASK_PRTENT */

/*
** special filno values for PUTHDR call with ctIICThdr mode.
*/
#define ctIICTbegin	-1	/* begin a new IICTxtd		*/
#define ctIICTcommit	-2	/* commit current IICTxtd	*/
#define ctIICTabort	-3	/* abort current IICTxtd	*/

/*
** special hdrval values for PUTHDR call with ctMULTIOPNhdr mode.
*/
#define ctMULTIOPNdifusr	1	/* multi open locks => diff user     */
#define ctMULTIOPNnodifusr	2	/* multi open locks => non-diff user */
#define ctMULTIOPNsamusr_1	3	/* multi open locks => same user     **
					** unlock with any co-file	     */
#define ctMULTIOPNsamusr_M	4	/* multi open locks => same user     **
					** unlock with a co-file holding lock*/

#define CHKNUL		'\1'

/*
**
** ctSYSPUT parmcode values
*/
#define ctCMTDLY_TIM		1	/* commit delay time (usec)	*/
#define ctCMTDLY_SCL		2	/* block to clear ratio (>= 1)	*/
#define ctCMTDLY_BAS		3	/* commit delay cohort size	*/
#define ctFILEIDsys		4	/* set fileid system value for
					** ctFILECOMPdbg only		*/

/* Transaction Modes */

#ifndef ctNONE
#define ctNONE		0
#else /* for backward compatibility */
#define NONE		0
#endif

#define RCVMOD		1	/* automatic recovery */
#define BAKMOD		2	/* rollback */
#define FWDMOD		3	/* forward roll */
#define MBRMOD		4

#define TRNNUM		0	/* transaction number: not used	*/
#define TRNTIM		1	/* system time stamp [cttime()]	*/
#define TRNRP		2	/* Restore Point: internal use	*/
#define	TRNROLBAK	3	/* Roll back to log position:	**
				** internal use			*/

#define SAVCURI		0
#define RSTCURI		1
#define SWTCURI		2

/* Isam Segment Modes */

#define REGSEG		0	/* no modification		*/
#define INTSEG		1	/* unsigned integer		*/
#define UREGSEG		2	/* upper case translation	*/
#define SRLSEG		3	/* 4-8 byte auto serial number	*/
#define VARSEG		4	/* no mod. var length field	*/
#define UVARSEG		5	/* upper case. var length field	*/
#define YOURSEG1	6	/* reserved for your use	*/
#define YOURSEG2	7	/* reserved for your use	*/
#define SGNSEG		8	/* signed integer segment	*/
#define FLTSEG		9	/* floating point segment	*/
#define DECSEG		10	/* old SQL BCD segment		*/
#define BCDSEG		11	/* ctDH_BCD BCD segment		*/
#define SCHSEG		12	/* field number from schema	*/
#define USCHSEG		13	/* upper case field # from sch	*/
#define VSCHSEG		14	/* fixed len treated as var	*/
#define UVSCHSEG	15	/* VSCHSEG + upper case		*/
#define XTDSEG		256	/* beginning of xtd segments	*/
#define RECBYT		256	/* record position (byte offset)*/
#define SCHSRL		257	/* field # of schema for SRLSEG */
#define SEGMSK		0x010f	/* permits a seg mode range 0-15
				   and 256-271 */
#define DSCSEG		0x0010	/* mode + 16 for descending	*/
#define ALTSEG		0x0020	/* mode + 32 for alternate seq	*/
#define ENDSEG		0x0040	/* reverses bytes in segment to */
				/* permit end of field searches	*/
#define UNCSEG		0x0080  /* Unicode segment modifier	*/
#define NOTPRT		0x0200	/* not part of key-to-partition
				   computation			*/
#define GNXSEG		0x0400	/* generic extended key segment */


#define OPS_ONCE_LOK	0x0004		/* 2 byte values to pass in rqst*/
#define OPS_ONCE_BLK	0x0020
#define OPS_ONCE_ADD_BLK 0x0040
#define OPS_ONCE_LOK_BLKRQS 0x0080
#define OPS_RSVD_2B4	0x0100		/* reserved for future use	*/

#define OPS_STATE_OFF	0x00000000
#define OPS_STATE_SET	0x00000001
#define OPS_STATE_ON	0x00000002
#define OPS_STATE_RET	0x00000003
#define OPS_STATE_VRET	0x00000004

#define OPS_UNLOCK_ADD	0x00000001	/* auto unlock on add		*/
#define OPS_UNLOCK_RWT	0x00000002	/* auto unlock on rewrite	*/
#define OPS_UNLOCK_UPD	(OPS_UNLOCK_ADD | OPS_UNLOCK_RWT)
#define OPS_LOCKON_GET	((LONG) OPS_ONCE_LOK) /* lock next fetch only	*/
#define OPS_VARLEN_CMB	0x00000008	/* get var len on one fetch	*/
#define OPS_SERVER_SHT	0x00000010	/* server is shutting down	*/
#define OPS_LOCKON_BLK	((LONG) OPS_ONCE_BLK) /* lock next fetch only	*/
#define OPS_LOCKON_ADD_BLK ((LONG) OPS_ONCE_ADD_BLK) /* lock next add only */
#define OPS_LOCKON_GET_BLKRQS ((LONG) OPS_ONCE_LOK_BLKRQS) /* lock next fetch only, force subsequent lock requests to block */
					/* RSVD_2B3			*/
					/* RSVD_2B4			*/
#define OPS_ADMOPN	0x00000200	/* ADMIN forced open (OPNFIL)	*/
#define OPS_OMITCP	0x00000400	/* omit files from checkpoint	*/
#define OPS_SKPDAT	0x00000800	/* replaces SKIPDATA file mode	*/
#define OPS_MIRROR_NOSWITCH 0x00001000	/* don't continue operation if  */
					/* mirror or primary fails.	*/

#define OPS_CLIENT_TRM	0x00002000	/* server has been terminated	*/
#define OPS_MIRROR_TRM	0x00004000	/* a primary or mirror has been */
					/* shutdown			*/
#define OPS_FUNCTION_MON 0x00008000	/* toggle function monitor	*/
#define OPS_LOCK_MON	0x00010000	/* toggle lock monitor		*/
#define OPS_TRACK_MON	0x00020000	/* toggle memory track monitor	*/
#define OPS_AUTOISAM_TRN 0x00040000	/* automatic ISAM transactions	*/
#define OPS_SERIAL_UPD	0x00080000	/* update serial# in SERIALNUM	*/
#define OPS_MEMORY_SWP	0x00100000	/* memory swapping active	*/
#define OPS_COMMIT_SWP	0x00200000	/* auto commit on swap occurred	*/
#define OPS_FLEXFILE	0x00400000	/* flex file increase		*/
#define OPS_CLRCURP	0x00800000	/* clear local-side curp info	*/
#define OPS_RBLD_CPY	0x01000000	/* mirror copy failed in rebuild*/
#define OPS_DEFER_CLOSE	0x02000000	/* if file is closed with active*/
					/* tran, defer close to TRANEND */
#define OPS_DISK_IO	0x04000000	/* sysiocod indicates disk IO	*/
#define OPS_NOFLUSH_TRN	0x08000000	/* AUTOISAM_TRN use NOFLUSHtran */
#define OPS_KEEPLOK_TRN 0x10000000	/* AUTOISAM_TRN use ctKEEP	*/
#define OPS_READLOCK	0x20000000	/* auto low level read lock	*/
#define OPS_CONV_STRING 0x40000000	/* Convert CT_STRING fields to  */
					/* CT_FSTRING fields in fixed	*/
					/* portion of record buffer	*/
#define OPS_TRANABT	0x80000000	/* transaction was aborted	*/

#define OPS_once	(OPS_ONCE_LOK | OPS_ONCE_BLK | OPS_ONCE_ADD_BLK | OPS_ONCE_LOK_BLKRQS)
#define OPS_lockon	(OPS_LOCKON_GET | OPS_LOCKON_BLK | OPS_LOCKON_GET_BLKRQS)
#define OPS_lockonALL	(OPS_lockon | OPS_LOCKON_ADD_BLK)
#define OPS_monitors	(OPS_FUNCTION_MON | OPS_LOCK_MON | OPS_TRACK_MON)
#define OPS_internal	(OPS_SERVER_SHT	| OPS_ADMOPN | OPS_OMITCP | OPS_SKPDAT | OPS_CLIENT_TRM | OPS_FLEXFILE | OPS_CLRCURP | OPS_RBLD_CPY | OPS_TRANABT)
#define OPS_server	(OPS_COMMIT_SWP | OPS_SERVER_SHT | OPS_CLIENT_TRM | OPS_MIRROR_TRM | OPS_MEMORY_SWP | OPS_TRANABT)
			/*
			** the above states are set on server side (for
			** client/server applications)
			*/
#define OPS_permanent	(OPS_SERVER_SHT | OPS_CLIENT_TRM | OPS_MIRROR_TRM | OPS_MEMORY_SWP)
			/*
			** the above states not to be cleared by a SET zero.
			*/

#ifdef RB_CALLBACK

#define RBLCB_DAT	'd'
#define RBLCB_IDX	'i'
#define RBLCB_MSG	'm'
#define RBLCB_LOG	'l'   /* callback to write to the log file */
#define RBLCB_CNT	'c'   /* callback to return number of records in file/index */
#define RBLCB_MCT	'p'   /* callback to return percentage complete * 10 (of current stage of rebuild) */

/* rebuild callback state */
typedef struct ctrbcbst {
	LONG	rcblen;	/* number of data bytes in structure */
	LONG	rcbhw;	/* counter high word value */
	COUNT	rcbrc;	/* rebuild callback return code */
} ctRBCBST, ctMEM * pctRBCBST;

/* Size of rebuild callback state structure, version 1 */
#define ctRCBLEN_V01 10

#endif

#define DEF_IFIL	0
#define DEF_MAP		1
#define DEF_NAMES	2
#define DEF_SQL1	3
#define DEF_SQL2	4
#define DEF_SQL3	5
#define DEF_DTREE1	6
#define DEF_DTREE2	7 
#define DEF_DTREE3	8 
#define DEF_NATLNG1	9
#define DEF_NATLNG2	10
#define DEF_NATLNG3	11
#define DEF_RESRVD1	12
/*
** ................	..
*/
#define DEF_RESRVD20	31
#define DEF_NUMBER	32

/*
** Ensure that DEF_NUMBER is at least as large as ctMAXMEMB+1 */
#ifdef ctMAXMEMB
#if DEF_NUMBER <= ctMAXMEMB
#undef DEF_NUMBER
#define DEF_NUMBER (ctMAXMEMB + 1)
#endif
#endif

#define DEF_IFILspcl	(DEF_NUMBER + 1)	/* ctDISTINCTset */

/* Here is where the RESOURCE numbers are defined. See RESOURCE types defined in ctopt2.h */

/* Resource Numbers for FC_MAIN resource type: */
#define FCRES_DATA	1	/* file definition data */
#define FCRES_SCRT	2	/* file security attributes */
#define FCRES_IDX	3	/* index file: alternate collating sequence */
/* #define FCRES_SQL	4 */	/* old macro, not used - available for use */
#define FCRES_CIDX	5	/* data file: conditional index resource */
#define FCRES_CAMO	6	/* file encryption */
#define FCRES_SEGM	7	/* segment resource */
#define FCRES_MGES	8	/* segment resource stand-in */
#define FCRES_PART	9	/* data file: partition resource */
#define FCRES_PRUL	10	/* data file: partition rule resource */
#define FCRES_ROWL	11	/* data file: row-level read security */
#define FCRES_WOWL	12	/* data file: row-level write security */
#define FCRES_ATTR	13	/* file-specific attributes */
#define FCRES_CMPREC	14	/* data file: data record compression */
#define FCRES_DFRK	15	/* data file: deferred index resource */
#define FCRES_RUCB	16	/* data file: record update callback resource */
#define FCRES_FLEXREC	17	/* data file: flexible record format resource */
#define FCRES_FTIDIC	18	/* Full Text Index Dictionary resource */
#define FCRES_BGLOAD	19	/* data file: Background load status */
#define FCRES_AUTOST	20	/* data file: automatic system time assignment resource */

#define FCRES_LAST	20	/* last FC_MAIN resource number used */
/*
NOTE: When adding values here, must also update definition of fcmain in ctrsrc.c
*/

/* Resource Numbers for FC_CTDB resource type: */
#define FCRES_DFLD	1	/* CTDB extended field information resource */
#define FCRES_DPAD	2	/* CTDB field padding resource */
#define FCRES_ROUT	3	/* CTDB table router resource */
#define FCRES_DFL2	4	/* CTDB default field value */
#define FCRES_TATT	5	/* CTDB table attributes resource */

/*
NOTE: When adding values here, must also update definition of fcctdb in ctrsrc.c
*/

/* Resource Numbers for FC_CTDB_VTABLES resource type: */
#define FCRES_CTDB_VTABLES 0		/* CTDB view resources from 0 to 199 */
#define FCRES_CTDB_VTABLES_END 199 	/* CTDB view resources from 0 to 199 */

/* Resource Numbers for FC_COBOL resource type: */
#define FCRES_COBOL_FEAT	0	/* COBOL feature resource - Concidered Legacy */
#define FCRES_COBOL_XML		1	/* COBOL XML resource  - Primary XML Schema info */
#define FCRES_COBOL_INFO	2	/* COBOL info resource - Concidered legacy */
#define FCRES_COBOL_DODA	1024	/* COBOL DODA resource - We never used this */
#define FCRES_COBOL_IFIL	2048	/* COBOL IFIL resource - We never used this */

/* Resource Numbers for FC_RTG resource type: */
#define FCRES_RTG_INFO	3		/* RTG info resource - XML - Main RTG resource with All core RTG necessaries */

#define FCRNAM_LEN	8		/* size of null-terminated resource name field */

/* Resource names for FC_MAIN resource type: */
#define FCRES_DEF_NAME	"FC!DEF"
#define FCRES_SCRT_NAME	"......."
#define FCRES_CIDX_NAME	"FC!CIDX"
#define FCRES_SEGM_NAME	"FC!SEGM"
#define FCRES_SEGA_NAME	"FC!SEGA"
#define FCRES_PART_NAME	"FC!PART"
#define FCRES_PRUL_NAME	"FC!PRUL"
#define FCRES_ROWL_NAME	"FC!ROWL"
#define FCRES_WOWL_NAME	"FC!WOWL"
#define FCRES_CMPREC_NAME "FC!CMPR"
#define FCRES_DFRK_NAME "FC!DFRK"
#define FCRES_RUCB_NAME "FC!RUCB"
#define FCRES_FLEXREC_NAME "FC!FLXR"
#define FCRES_FTIDIC_NAME "FC!FTID"
#define FCRES_BGLOAD_NAME "FC!BGLD"
#define FCRES_AUTOST_NAME "FC!AUST"

/* Resource names for FC_UNIC resource type: */
#define FCRES_KSEG_NAME	"FC!KSEG"

/* Resource names for FC_CTDB resource type: */
#define FCRES_DFLD_NAME		"FC!DFLD"
#define FCRES_DFL2_NAME		"FC!DFL2"
#define FCRES_DPAD_NAME		"FC!DPAD"
#define FCRES_ROUT_NAME		"FC!ROUT"
#define FCRES_VFLT_NAME		"FC!VFLT"
#define FCRES_VTNB_NAME		"FC!VTNB"
#define FCRES_TATT_NAME		"FC!TATT"

/* Resource names for FC_COBOL resource type: */
#define FCRES_COBOL_FEAT_NAME	"FC!COBF"
#define FCRES_COBOL_XML_NAME	"FC!COBX"
#define FCRES_COBOL_INFO_NAME	"FC!COBN"
#define FCRES_COBOL_DODA_NAME	"FC!COBD"
#define FCRES_COBOL_IFIL_NAME	"FC!COBI"

/* Resource names for FC_RTG resource type: */
#define FCRES_RTG_INFO_NAME	"FC!RTGI"

/* synonyms */

#define tfrmkey		TFRMKEY
#define alcset		ALCSET
#define chgset		CHGSET

#define FNSYSABS	1
#define FNSRVDIR	2
#define FNLOCSRV	3
#define FNMIRSRV	4

#ifdef ctFeatMAXFILE32

typedef LONG FILNO, *pFILNO; /* c-tree's user-level file number data type */
typedef LONG SYSNO, *pSYSNO; /* c-tree's system-level file number data type */
typedef struct ifil4 IFIL4, *pIFIL4; /* IFIL structure with 4-byte file numbers */
typedef struct ifil4 IFIL, *pIFIL; /* IFIL structure with 4-byte file numbers */
#ifdef ctSRVR
typedef struct ifilz IFILz, *pIFILz; /* IFIL stream with 2-byte file numbers */
#else
typedef struct ifil4z IFILz, *pIFILz; /* IFIL stream with 4-byte file numbers */
#endif

#else  /* ~ctFeatMAXFILE32 */

typedef COUNT FILNO, *pFILNO; /* c-tree's user-level file number data type */
typedef COUNT SYSNO, *pSYSNO; /* c-tree's system-level file number data type */
typedef struct ifil IFIL, *pIFIL; /* IFIL structure with 2-byte file numbers */
typedef struct ifilz IFILz, *pIFILz; /* IFIL stream with 2-byte file numbers */

#endif /* ~ctFeatMAXFILE32 */

typedef struct ifil IFIL2, *pIFIL2; /* IFIL structure with 2-byte file numbers */
typedef struct ifilz IFIL2z, *pIFIL2z; /* IFIL stream with 2-byte file numbers */

typedef COUNT CTERR; /* c-tree error code */
typedef COUNT CT_LOCK_MODE; /* c-tree lock mode */

typedef struct ctinit1 {
	COUNT	 initype;	/* MUST BE SET TO ONE (1) */
	UCOUNT	 maxuser;	/* maximum number of users */
	ULONG	 logspac;	/* space for log files in MB */
	LONG	 lmtmem;	/* max ctgetmem request */
#ifdef ct8P
	LONG8	 totmem;	/* total memory (0 => no limit) */
#else
	LONG	 totmem;	/* total memory (0 => no limit) */
#endif
	LONG	 usrmem;	/* default limit per user (0 => no limit) */
	LONG	 coopcmt;	/* co-operative commit factor */
	ULONG	 idxcmem;	/* index buffer memory */
	ULONG	 datcmem;	/* data buffer memory */
	pTEXT	 srvdirc;	/* server file directory */
	pTEXT	 mirdirc;	/*      mirror directory */
	pTEXT	 evenstr;	/* even start file */
	pTEXT	 odd_str;	/* odd start file */
	pTEXT	 evenlog;	/* even log files */
	pTEXT	 odd_log;	/* odd log files */
	pTEXT	 preimgf;	/* pre-image swap file prefix */
	pTEXT	 srvrnam;	/* server logical name */
	UINT	 idxbufs;	/* number of index buffers */
	UINT	 datbufs;	/* number of data buffers */
	SYSNO	 maxfile;	/* maximum number of data files and indices */
	COUNT	 bufsect;	/* 128 sectors per buffer */
	COUNT	 mirname;	/* FNMIRSRV */
	COUNT	 filname;	/* file name strategy:	0 no modification,
				** FNSYSABS		1 change to system abs,
				** FNSRVDIR		2 prepend srv direct,
				** FNLOCSRV		3 same as 2, but only
				**			  for mbopen\mbcrat
				*/
	LONG	 reservl;
	pTEXT	 evenstrm;	/* even start file */
	pTEXT	 odd_strm;	/* odd start file */
	pTEXT	 evenlogm;	/* even log files */
	pTEXT	 odd_logm;	/* odd log files */
	pTEXT	 ldapsrvr;	/* LDAP server name			 */
	NINT	 ldaptimeout;	/* LDAP connection timeout		 */
	pTEXT	 ldapbase;	/* LDAP base string			 */
#ifdef ctFeatOS_SECURITY_LDAP
	pTEXT	 admusr;	/* ADMIN super user name		 */
	pTEXT	 admgrp;	/* ADMIN group name			 */
	pTEXT	 gstusr;	/* GUEST user name			 */
	pTEXT	 gstgrp;	/* GUEST group name			 */
	pTEXT	 logingrp;	/* Must be member of this group to login */
#endif
	pTEXT	 ctsvport;	/* server port				 */
	NINT	 filcremode;	/* File create mode (e.g., 0666)	 */
#ifdef ctFeatCFG_SCALE_N8
	LONG8	 idxcmem64;	/* index buffer memory (64-bit)		 */
	LONG8	 datcmem64;	/* data buffer memory (64-bit)		 */
#endif
} CTINIT1;
typedef CTINIT1 ctMEM *	pCTINIT1;

typedef struct ctinit {
	pTEXT	evenstr;	/* START_EVEN			*/
	pTEXT	odd_str;	/* START_ODD			*/
	pTEXT	evenlog;	/* LOG_EVEN			*/
	pTEXT	odd_log;	/* LOG_ODD			*/
	pTEXT	preimgf;	/* PREIMAGE_FILE		*/
	pTEXT	evenstrm;	/* START_EVEN_MIRROR		*/
	pTEXT	odd_strm;	/* START_ODD_MIRROR		*/
	pTEXT	evenlogm;	/* LOG_EVEN_MIRROR		*/
	pTEXT	odd_logm;	/* LOG_ODD_MIRROR		*/

	pTEXT	resrvt0;
	pTEXT	resrvt1;
	pTEXT	resrvt2;
	pTEXT	locdirc;
	pTEXT	srvdirc;
	pTEXT	mirdirc;

	LONG	logspac;	/* LOG_SPACE			*/
	LONG	lmtmem;		/* LMT_MEMORY			*/
	ULONG	idxcmem;	/* IDX_MEMORY			*/
	ULONG	datcmem;	/* DAT_MEMORY			*/
	LONG	nodedel;	/* NODE_DELAY			*/
	LONG	statsiz;	/* CTSTATUS_SIZE		*/
	LONG	chkidle;	/* CHECKPOINT_IDLE		*/
	LONG	chkintv;	/* CHECKPOINT_INTERVAL		*/
	LONG	memmont;	/* MEMORY_MONITOR		*/
	LONG	trkmont;	/* MEMORY_TRACK			*/
	LONG	lokmont;	/* LOCK_MONITOR			*/
	LONG	coopcmt;	/* COMMIT_DELAY			*/
#ifdef ctFeatCFG_SCALE_N8
	LONG8	disklmt;	/* DISK_FULL_LIMIT		*/
#else
	ULONG	disklmt;	/* DISK_FULL_LIMIT		*/
#endif

	LONG	chkpfls;	/* CHECKPOINT_FLUSH		*/
	LONG	tranfls;	/* TRANSACTION_FLUSH		*/
	LONG	ct_compflg;	/* 1st compatibility word	*/
	LONG	ct_compflg2;	/* 2nd compatibility word	*/
	LONG	ct_compflg3;	/* 3rd compatibility word	*/
	LONG	ct_compflg4;	/* 4th compatibility word	*/
	ULONG	ct_compflg5;	/* 5th compatibility word	*/

	NINT	maxuser;	/* USERS			*/
	NINT	maxfile;	/* FILES			*/
	NINT	rcvfile;	/* RECOVER_FILES		*/
	NINT	pagesiz;	/* PAGE_SIZE			*/
	NINT	keeplog;	/* KEEP_LOGS			*/
	NINT	maxdkey;	/* MAX_DAT_KEY			*/
	NINT	maxkseg;	/* MAX_KEY_SEG			*/
	NINT	skpfile;	/* SKIP_MISSING_FILES		*/
	NINT	skpmfil;	/* SKIP_MISSING_MIRRORS		*/
	NINT	mirrors;	/* MIRRORS			*/
	NINT	flogidx;	/* FORCE_LOGIDX			*/
	NINT	chkmont;	/* CHECKPOINT_MONITOR		*/
	NINT	dedmont;	/* DEALOCK_MONITOR		*/
	NINT	maxvrtf;	/* MAX_VIRTUAL_FILES		*/
	NINT	fixdlog;	/* FIXED_LOG_SIZE		*/
	NINT	langflg;	/* LANGUAGE			*/
	NINT	maxufil;	/* MAX_FILES_PER_USER		*/
	NINT	logcode;	/* LOG_ENCRYPT			*/
	NINT	skpmlog;	/* SKIP_MISSING_LOG_MIRRORS	*/
	NINT	cchline;	/* CACHE_LINE			*/
	NINT	brunlen;	/* BUFFER_RUNLENGTH		*/
	NINT	mpagche;	/* MPAGE_CACHE			*/
	NINT	dspllmt;	/* SPECIAL CACHE PERCENTAGE	*/

	NINT	thrconc;	/* THREAD_CONCURRENCY		*/
	NINT	defchnl;	/* DEFAULT_CHANNELS		*/
	NINT	logpgsz;	/* LOG_PAGE_SIZE		*/
	NINT	cmosdksup;	/* ADVANCED_ENCRYPTION		*/

#ifdef CT_V8
	NINT	ctlogtmp;	/* LOG_TEMPLATE			*/
	NINT	dscan;		/* SCAN CACHE PERCENTAGE	*/
	NINT	resrvi7;
	NINT	resrvi8;
	NINT	resrvi9;

	NINT	resrvi11;
	NINT	resrvi12;
	NINT	resrvi13;
	NINT	resrvi14;
	NINT	resrvi15;
	NINT	resrvi16;
	NINT	resrvi17;
	NINT	resrvi18;

	LONG	resrvl6;
	LONG	resrvl7;
	LONG	resrvl8;
	LONG	resrvl9;
	LONG	resrvl11;
	LONG	resrvl12;
	LONG	resrvl13;
	LONG	resrvl14;
	LONG	resrvl15;
	LONG	resrvl16;
	LONG	resrvl17;
	LONG	resrvl18;
	LONG	resrvl19;
	LONG	resrvl20;
	LONG	resrvl21;
	LONG	resrvl22;

	pTEXT	resrvt3;
	pTEXT	resrvt4;
	pTEXT	resrvt5;
	pTEXT	resrvt6;
	pTEXT	resrvt7;
	pTEXT	resrvt8;
	pTEXT	resrvt9;
	pTEXT	resrvt10;
#endif

} ctINIT;
typedef ctINIT ctMEM *	pctINIT;

typedef struct pkeyreq {
	LONG	btotal;		/* total in set			*/
	LONG	bavail;		/* number available		*/
	LONG	breturn;	/* number returned		*/
	COUNT	siglen;		/* significant partial key len	*/
	TEXT	target[MAXLEN];	/* partial key target		*/
	} PKEYREQ;
typedef PKEYREQ ctMEM *	pPKEYREQ;
#define PKEYLEN	(3 * ctSIZE(LONG) + ctSIZE(COUNT))


typedef struct pkeyreq2 {
	ULONG	batchmode;	/* batch mode */
	ULONG	batchmode2; /* batch mode2 (future use)*/
	LONG	btotal;		/* total in set			*/
	LONG	bavail;		/* number available		*/
	LONG	breturn;	/* number returned		*/
	COUNT	siglen;		/* significant key len	(target/utarget size in bytes) */
	COUNT	nsegs;		/* number of segments in range */
	COUNT	nfields;	/* number of entries in fieldmask */
	pTEXT	target;		/* partial key target/lower-range in standlone it must point to a buffer as large as the key (ctnum->length)*/
	pTEXT	utarget;	/* upper-range	*/
	pNINT	operators;	/* operators array for range */
	pULONG	fldmask;	/* array of field number (DODA position)*/
	pTEXT	filter;		/* filter string in case of filter */
	LONG	bstartoffh; /* ctFeatPKEYREQ2_V starting offset (high word) for (batchmode & BAT_PHYS) */
	LONG	bstartoff;  /* ctFeatPKEYREQ2_V starting offset (low word) for (batchmode & BAT_PHYS) */
} PKEYREQ2;
typedef PKEYREQ2 ctMEM * pPKEYREQ2;
#define PKEYLEN2	(5 * ctSIZE(LONG) + 3 * ctSIZE(COUNT))

typedef struct xCREblk {
	LONG	x8mode;		/* new file modes			*/
	ULONG	segsiz;		/* 1st segment size (MB)		*/
	LONG	mxfilzhw;	/* high word max file size		*/
	LONG	mxfilzlw;	/*  low word max file size		*/
	LONG	fxtsiz;		/* first file extent size		*/
	LONG	lxtsiz;		/* file extent size			*/
	LONG	segmax;		/* maximum number of segments		*/
	ULONG	dskful;		/* disk full threshold			*/
	ULONG	filkey;		/* file encryption key			*/
	LONG	prtkey;		/* relative key# for partition key	*/
	LONG	splval;		/* special value parameter		*/
	LONG	rs4[3];		/* reserved for future use		*/
	LONG	instnc;		/* instance number			*/
	LONG	callparm;	/* call specific parameter		*/
} XCREblk;
typedef  XCREblk ctMEM *  pXCREblk;
typedef pXCREblk ctMEM * ppXCREblk;

typedef struct notblk {
	ULONG	action;		/* actual opcode		*/
	LONG	actor;		/* thread ID			*/
	LONG	tranhw;		/* transaction # HW		*/
	LONG	tranlw;		/* transaction # LW		*/
	LONG	opcode;		/* requested opcodes		*/
	LONG	objhandle;	/* requested (user) handle	*/
	LONG	idxmemno;	/* index member number		*/
	ULONG	contents;	/* actual contents bit map	*/
	ULONG	controls;	/* requested controls bit map	*/
	LONG	datahw;		/* data HW (eg rec pos)		*/
	LONG	datalw;		/* data LW			*/
	LONG	auxdhw;		/* auxilary info HW (eg old pos)*/
	LONG	auxdlw;		/* auxilary info LW		*/
	ULONG	varlen;		/* remaining length (if any)	*/
	} ctNOTBLK, * pctNOTBLK;

typedef struct notkey {
	COUNT	rkeyno;		/* 1st unique key # (relative)	*/
	COUNT	keylen;		/* key length			*/
	TEXT	keyvals[2 * MAXLEN]; /* key value / oldkey RWTV	*/
	} ctNOTKEY, * pctNOTKEY;

typedef struct notadd {
	LONG	reclen;
	ctNOTKEY
		notkey;
	} ctNOTADD, * pctNOTADD;

typedef struct notrwt {
	LONG	reclen;
	LONG	oldhw;
	LONG	oldlw;
	ctNOTKEY
		notkey;
	} ctNOTRWT, * pctNOTRWT;

typedef struct notdat {
	ctNOTBLK
		notblk;		/* status block			*/
	ctNOTKEY
		notkey;		/* key block			*/
	TEXT	notid[32];	/* ID block	[IDZ]		*/
	LONG	notrln;		/* record image length		*/
				/* followed by recbuf		*/
	} ctNOTDAT, * pctNOTDAT;

typedef struct usrprf {
	COUNT	utaskid;	/* internal task id		*/
	COUNT	uactflg;	/* active request indicator	*/
	TEXT	uname[32];	/* user id string		*/
	TEXT	ucominfo[32];	/* communication info		*/
	TEXT	urqst[16];	/* last request function name	*/
	LONG	umemsum;	/* user memory			*/
	LONG	ulogtim;	/* logon time			*/
	LONG	ucurtim;	/* current time			*/
	LONG	urqstim;	/* time of last request		*/
	LONG	utrntim;	/* time of last TRANBEG		*/
	LONG	unbrfil;	/* number of open files		*/
	LONG	urqstfn;	/* last request function #	*/
	TEXT	unodnam[32];	/* node ID information		*/
	} USRPRF;
typedef USRPRF ctMEM * pUSRPRF;
#define USRLSTSIZ	8193

/* Extended user information structure. The data returned from USERINFOX()
conforms to this structure definition. The structure consists of the same
fields as the USRPRF structure followed by additional fields. */
typedef struct usrprfx {
/* Same fields as USRPRF structure, but reserved replaces urqst: */
	COUNT	utaskid;	/* internal task id			*/
	COUNT	uactflg;	/* active request indicator		*/
	TEXT	uname[32];	/* user id string			*/
	TEXT	ucominfo[32];	/* communication info			*/
	TEXT	reserved[16];	/* unused field (overlaps USRPRF urqst) */
	LONG	umemsum;	/* user memory				*/
	LONG	ulogtim;	/* logon time				*/
	LONG	ucurtim;	/* current time				*/
	LONG	urqstim;	/* time of last request			*/
	LONG	utrntim;	/* time of last TRANBEG			*/
	LONG	unbrfil;	/* number of open files			*/
	LONG	urqstfn;	/* last request function number		*/
	TEXT	unodnam[32];	/* node ID information			*/
/* New fields, including larger field for function name: */
	TEXT	urqstx[32];	/* last request function name		*/
	ULONG8	uDiskReadOps;	/* number of disk read operations	*/
	ULONG8	uDiskReadBytes;	/* number of bytes read from disk	*/
	ULONG8	uDiskWriteOps;	/* number of disk write operations	*/
	ULONG8	uDiskWriteBytes;/* number of bytes written to disk	*/
	ULONG8	uDataCacheReqs; /* number of data cache requests	*/
	ULONG8	uDataCacheHits; /* number of data cache hits		*/
	ULONG8	uIndexCacheReqs;/* number of index cache requests	*/
	ULONG8	uIndexCacheHits;/* number of index cache hits		*/
	} USRPRFX;
typedef USRPRFX ctMEM * pUSRPRFX;

/*^**********************************/
/*
** USERINFOX() function call structure.
*/
#define USERINFOX_VERS_V01	1	/* initial version of structure	*/

#define USERINFOX_VERS_CUR	USERINFOX_VERS_V01	/* current version */

/* Size of USERINFOX() function data to pass to server. */
#define USERINFOXinsize_V01  (2*sizeof(UCOUNT) + 2*sizeof(ULONG)) /* version 1 input size */

typedef struct userinfoxprm {
	UCOUNT	StructVersion;	/* [IN] Version of this structure. */
	UCOUNT	TaskId;		/* [IN,OUT] On input, set to the task ID of the
				connection whose information is to be returned,
				or set it to zero to return the information for
				all connections. On output, this field is set to
				the number of entries that were written to the
				output buffer. */
	ULONG	UserInfoLength; /* [IN] Size of one connection info entry. */
	ULONG	OutBufferSize;	/* [IN,OUT] On input, set to the size of the
				output buffer. On output, holds the number of
				bytes written to the output buffer. If the
				required size is too small, the function returns
				error code VBSZ_ERR and sets OutBufferSize to
				the size required to hold information for all
				of the connections. */
	pTEXT	pOutBuffer;	/* [OUT] Buffer where the connection info is
				returned. */
} USRINFX, *pUSRINFX;

/*
** ctGetConnectionInfo() structure versions:
*/
#define ctCONINF_VERS_V01 1	/* initial version of structure */

/* Output data format for ctGetConnectionInfo() function: */
typedef struct ctconinf {
	COUNT	utaskid;	/* internal task id		*/
	COUNT	uactflg;	/* active request indicator	*/
	LONG	umemsum;	/* user memory			*/
	LONG	ulogtim;	/* logon time			*/
	LONG	ucurtim;	/* current time			*/
	LONG	urqstim;	/* time of last request		*/
	LONG	utrntim;	/* time of last TRANBEG		*/
	LONG	unbrfil;	/* number of open files		*/
	LONG	urqstfn;	/* last request function #	*/
	ULONG	sipaddr;	/* client IP address		*/
	ULONG	sip6addr[4];	/* client IPv6 address		*/
	TEXT	unodnam[32];	/* node ID information		*/
	TEXT	uname[32];	/* user id string		*/
	TEXT	ucominfo[32];	/* communication info		*/
	TEXT	urqst[32];	/* last request function name	*/
	} ctCONINF, ctMEM *pctCONINF;

#define ALTSEQSIZ	256
#define ALTSEQBYT	(ALTSEQSIZ * ctSIZE(COUNT))

typedef struct {
	LONG	blkoff;		/* offset from beginning of resource	*/
	UCOUNT	blklen;		/* total length    			*/
	UCOUNT	blkutl;		/* utilized length 			*/
	} DEFBLK;
typedef DEFBLK ctMEM *	pDEFBLK;

typedef struct {
	ULONG	restyp;
	ULONG	resnum;
	TEXT	resnam[FCRNAM_LEN];
	LONG	reslen;
	LONG	restim;
	DEFBLK	resblk[DEF_NUMBER];
	} RESDEF;
typedef RESDEF ctMEM *	pRESDEF;

typedef struct defdef {
	pVOID	 ddefptr;	/* pointer to definition data	*/
	VRLEN	 ddeflen;	/* actual length		*/
	VRLEN	 ddeftot;	/* total length including slack */
	COUNT	 ddefnum;	/* DEF_xxxx or IDX kmem		*/
	COUNT	 ddeftyp;	/* data or index definition	*/
	} DEFDEF;
typedef DEFDEF ctMEM *	pDEFDEF;

typedef struct defdefz {
	LONG	 ddefptr;	/* pointer to definition data	*/
	VRLEN	 ddeflen;	/* actual length		*/
	VRLEN	 ddeftot;	/* total length including slack */
	COUNT	 ddefnum;	/* DEF_xxxx or IDX kmem		*/
	COUNT	 ddeftyp;	/* data or index definition	*/
	} DEFDEFz;

typedef struct defdefw {
	LONG	 ddefptr;	/* pointer to definition data	*/
	LONG	 ddefptr2;
	VRLEN	 ddeflen;	/* actual length		*/
	VRLEN	 ddeftot;	/* total length including slack */
	COUNT	 ddefnum;	/* DEF_xxxx or IDX kmem		*/
	COUNT	 ddeftyp;	/* data or index definition	*/
	LONG	 ddefpad;
	} DEFDEFw;


#define ctDODA

typedef struct {
	pTEXT   fsymb;	/* ptr to optional symbol			*/
	pTEXT   fadr;	/* adr of structure member or other item	*/
	UCOUNT	ftype;	/* type indicator				*/
	UCOUNT	flen;	/* item length information			*/
	COUNT	fwhat;	/* structure classification			*/
	COUNT	flev;	/* file level reference				*/
	UCOUNT	fhrc;	/* file hierarchy				*/
	COUNT	frsv;	/* unused					*/
	pVOID	fusrp;	/* user assignable information block		*/
	pVOID	frsrv;	/* reserved					*/
	} DATOBJ;

typedef DATOBJ ctMEM *	pDATOBJ;

#ifndef CTBOUND
typedef struct {
	ULONG   fsymb;
	ULONG   fadr;
	UCOUNT	ftype;
	UCOUNT	flen;
	COUNT	fwhat;
	COUNT	flev;
	UCOUNT	fhrc;
	COUNT	frsv;
	ULONG	fusrp;
	ULONG	frsrv;
	} DATOBJ4;
typedef DATOBJ4 ctMEM *	pDATOBJ4;

typedef struct {
	ULONG   fsymb;
	ULONG	fpad1;
	ULONG   fadr;
	ULONG	fpad2;
	UCOUNT	ftype;
	UCOUNT	flen;
	COUNT	fwhat;
	COUNT	flev;
	UCOUNT	fhrc;
	COUNT	frsv;
	ULONG	fpad3;
	ULONG	fusrp;
	ULONG	fpad4;
	ULONG	frsrv;
	ULONG	fpad5;
	} DATOBJ8;
typedef DATOBJ8 ctMEM *	pDATOBJ8;
#endif

typedef struct convmap {
	UTEXT	flavor;
	UTEXT	align;
	UTEXT	flddelm;
	UTEXT	padding;
	VRLEN	maplen;
	VRLEN	nbrflds;
	VRLEN	nbrblks;
	} ConvMap;
typedef ConvMap ctMEM *	pConvMap;

typedef struct convblk {
	UCOUNT	len;
	UTEXT	kind;
	UTEXT	repcnt;
	} ConvBlk;
typedef ConvBlk ctMEM *	pConvBlk;

typedef struct convblk2 {
	UCOUNT	len;
	UCOUNT	kind;
	UTEXT	repcnt;
	UTEXT	pad;
	} ConvBlk2;
typedef ConvBlk2 ctMEM * pConvBlk2;

typedef struct cttm {
	LONG	tm_sec;
	LONG	tm_min;
	LONG	tm_hour;
	LONG	tm_mday;
	LONG	tm_mon;
	LONG	tm_year;
	LONG	tm_wday;
	LONG	tm_yday;
	LONG	tm_isdst;
	} ctTM;
typedef ctTM ctMEM * pctTM;

#define SCHEMA_MAP		1
#define SCHEMA_NAMES		2
#define SCHEMA_MAPandNAMES	3
#define SCHEMA_DODA		4

/*
** offset (bytes) of member of a structure [grep terms: OFFSET Offset OffSet]
*/
#ifdef ct8P
#define SegOff(struc, member)    	((NLONG)&(((struc *)0)->member))
#define ArraySegOff(struc, member)	((NLONG) (((struc *)0)->member))
#else
#define SegOff(struc, member)    	((NINT)&(((struc *)0)->member))
#define ArraySegOff(struc, member)	((NINT) (((struc *)0)->member))
#endif

#ifndef ctDTYPES
#define ctDTYPES

#ifdef  ctPortLIFEPRO
#ifndef ctFeatOLD_BCD_COMPAT
#define ctFeatOLD_BCD_COMPAT
#endif
#endif

#ifdef  ctPortCOVE
#ifndef ctFeatOLD_BCD_COMPAT
#define ctFeatOLD_BCD_COMPAT
#endif
#ifndef ctPortDAC
#define ctPortDAC /* DAC SQL BCD Support */
#endif
#endif

#ifndef ctFeatOLD_BCD_COMPAT
#define ctDH_BCD		/* CTDB (Dharma) BSD Support */
#endif

#define CT_BOOL		(1 << 3)
#define CT_CHAR		(2 << 3)
#define CT_CHARU	(3 << 3)
#define CT_INT2		((4 << 3) + 1)
#define CT_INT2U	((5 << 3) + 1)
#define CT_INT4		((6 << 3) + 3)
#define CT_INT4U	((7 << 3) + 3)
#define CT_MONEY	((8 << 3) + 3)
#define CT_DATE		((9 << 3) + 3)
#define CT_TIME		((10 << 3) + 3)
#define CT_SFLOAT	((11 << 3) + 3)
#define CT_DFLOAT	((12 << 3) + 7)

#ifdef ctDH_BCD
#define CT_SQLBCD	((13 << 3) + 1)	/* ctreeSQL BCD format */
#define CT_NUMBER	CT_SQLBCD
#else
#ifdef ctPortDAC
#define CT_SQLBCD	(13 << 3)	/* Old DAC format */
#else
#define CT_SQLBCDold	((13 << 3) + 3)
#define CT_SQLBCD	((13 << 3) + 4) /* ctPortLIFEPRO still uses this */
#endif
#endif

#define CT_EFLOAT	((14 << 3) + 7)
#define CT_TIMESold	((15 << 3) + 3)
#define CT_TIMES	((15 << 3) + 4)
#define CT_ARRAY	(16 << 3)
#define CT_CURRENCY	((17 << 3) + 7)

#define CT_FSTRING	(18 << 3)
#define CT_FPSTRING	(19 << 3)
#define CT_F2STRING	(20 << 3)
#define CT_F4STRING	(21 << 3)
#define CT_STRING	(CT_FSTRING + 2)
#define CT_PSTRING	(CT_FPSTRING + 2)
#define CT_2STRING	(CT_F2STRING + 2)
#define CT_4STRING	(CT_F4STRING + 2)

#define CT_FUNICODE	((22 << 3) + 1)
#define CT_UNICODE	((23 << 3) + 1)
#define CT_F2UNICODE	((24 << 3) + 1)
#define CT_2UNICODE	((25 << 3) + 1)
#define CT_RESRVD2	(26 << 3)
#define CT_AFTERunicode	CT_RESRVD2
#define CT_RESRVD3	(27 << 3)

#define CT_INT8		((28 << 3) + 7)
#define CT_INT8U	((29 << 3) + 7)

#define CT_RESRVD4	(30 << 3)
#define CT_RESRVD5	(31 << 3)
#define CT_LAST		CT_INT8U
#endif /* ~ctDTYPES */

#define CT_STRFLT	(CT_LAST + 1)
#define CT_STRLNG	(CT_LAST + 2)
#define CT_NUMSTR	(CT_LAST + 3)
#define CT_DBLSTR	(CT_LAST + 4)
#define CT_SUBSTR	(CT_LAST + 5)
#define CT_WLDCRD	(CT_LAST + 6)

/*^********************************************/
/*
** Extended c-tree data types:
*/
#define CT_DATXTD_MIN	0x0101	/* first extended data type value	*/
#define CT_DATXTD_MAX	0xffff	/* maximum possible data type value	*/

#define CT_TIMES_MS	0x0101	/* timestamp with millisec resolution	*/
#define CT_TIME_MS	0x0102	/* time with millisec resolution	*/
#define CT_JSON		0x0103	/* JSON document			*/
/* 1) Add a new data type here */

/* 2) When adding a data type, increment the count of data types */
#define CT_DATXTD_CNT	3	/* number of extended data types */

/* 3) Add an entry to the ctkindkeyxtd array in cttseg.c, indicating the segment mode to use for the new data type.*/
/* 4) Add an entry to the alignvals array in ctpifl.c, indicating the alignment to use for the new data type.*/
/* 5) Add an entry to the kindflvxtd array in ctpifl.c, indicating the length of the data type for purposes of reversing bytes in a heterogenous environment.*/
/* 6) Add an entry to the x array in flxrgetnullfieldvalue() in ctfrec.c, indicating the default value and length of default value */
/*~********************************************/


/* SECURITY() mode parameter values: */
#define SEC_FILEWORD		1	/* set password for file        */
#define SEC_FILEGRUP		2	/* set group for file           */
#define SEC_FILEMASK		3	/* set permission mask for file */
#define SEC_FILEOWNR		4	/* set owner for file           */
#define SEC_FAIL_LIMIT		5	/* set logon fail limit         */
#define SEC_TEMPPW		6	/* set temp logon password      */
#define SEC_FAIL_TIME		7	/* set logon fail time          */
#define SEC_MUST_TIME		8	/* set must logon time          */
#define SEC_BLOCK_NONADM	9	/* block non ADMIN group logons	*/
#define SEC_BLOCK_NONSUP	10	/* block non ADMIN user  logons	*/
#define SEC_BLOCK_OFF		11	/* turn block off		*/
#define SEC_BLOCK_KILL		12	/* NONSUP + kill any users/dumps*/
#define SEC_ADD_USER		13	/* add user account		*/
#define SEC_REMOVE_USER		14	/* remove user account		*/
#define SEC_CHANGE_USER_GROUPS	15	/* change user group membership	*/
#define SEC_CHANGE_USER_DESC	16	/* change user description	*/
#define SEC_CHANGE_USER_PASSWD	17	/* change user password		*/
#define SEC_CHANGE_USER_MEMORY	18	/* change user memory limit	*/
#define SEC_CHANGE_USER_XINFO	19	/* change user extended settings*/
#define SEC_ADD_GROUP		20	/* add group			*/
#define SEC_REMOVE_GROUP	21	/* remove group			*/
#define SEC_CHANGE_GROUP_DESC	22	/* change group description	*/
#define SEC_CHANGE_GROUP_MEMORY	23	/* change group memory limit	*/
#define SEC_CHANGE_ADVENC_PASSWD 24	/* change the master password
					   for advanced encryption	*/
#define SEC_CHANGE_USER_LOGLMT	25	/* change user logon limit	*/
#define SEC_CHANGE_GROUP_LOGLMT	26	/* change group logon limit	*/
#define SEC_CHECK_ADVENC_PASSWD 27	/* check the master password
					   for advanced encryption	*/

#define ctSEGLEN	1
#define ctSEGMOD	2
#define ctSEGPOS	3

/*
 * I/O Performance Monitoring
 */

#define	DataBufferRequests	0
#define DataBufferHits		1
#define	IndexBufferRequests	2
#define IndexBufferHits		3
#define NbrReadOperations	4
#define NbrBytesRead		5
#define NbrWriteOperations	6
#define NbrBytesWritten		7
#define ctIOPLMT		8

#define NbrCommReadOperations	8
#define NbrCommBytesRead	9
#define NbrCommWriteOperations	10
#define NbrCommBytesWritten	11
#define NbrTranSavepoint	12
#define NbrTranRestores		13
#define NbrTranBegins		14
#define NbrTranEnds		15
#define NbrTranAborts		16
#define NbrCheckPoints		17
#define SystemTimeValue		18
#define NbrSyncDosFlush		19
#define NbrSyncLogFile		20
#define NbrSyncCtreeFile	21
/*
**				22 - 31 available for future use
*/
#define ctIXPLMT		32


/*
** IIDX overload values for dxtdsiz
*/
#define ctNO_IDX_BUILD		3
#define ctREPL_CHECK		5
#define ctQUEUE_IDX_BUILD	7

/*
** Old method for specifying rebuild/compact options. Instead use the new
** method below.
*/
#define updateIFIL		-99
#define purgeIFIL		-101
#define badpartIFIL		-105
/* NOTE: each ...IFIL should be smaller by an increasing power of 2: the
** next values should be -113, -129, etc.  This permits arbitrary
** combinations of them to be unambiguously determined.
**
** possible combinations
*/
#define upIFILcmb	(updateIFIL + purgeIFIL)
#define ubIFILcmb	(updateIFIL + badpartIFIL)
#define pbIFILcmb	(purgeIFIL + badpartIFIL)
#define upbIFILcmb	(updateIFIL + purgeIFIL + badpartIFIL)

/*
** New method for specifying rebuild/compact options. Add new values here.
*/
#define updateIFILoption	0x0002
#define purgeIFILoption		0x0004
#define badpartIFILoption	0x0008
#define redosrlIFILoption	0x0010
#define chgcompressIFILoption	0x0020	/* compact: set compression on/off for new file */
/* value  0x0020 is available for rebuild */
#define setencryptIFILoption	0x0040	/* compact: use current ctSETENCRYPT state for new file */
/* value  0x0040 is available for rebuild */
#define errorOnCorruptIFILoption 0x0080
#define skipdatascanIFILoption	0x0100	/* rebuild: Skip scan of data file during rebuild */
#define chgflexrecIFILoption	0x0100	/* compact: set flexrec on/off for new file */
#define repairCorruptIFILoption 0x0200 /* compact & rebuild: opposite of errorOnCorrupt */
/* values 0x0400 through 0x2000 are available for compact and rebuild */
#define tfilnoIFILoldbit	0x4000	/* bit indicating old method is in use */

/* all supported values */
#define tfilnoIFILallCompact	(updateIFILoption|purgeIFILoption|badpartIFILoption|redosrlIFILoption|chgcompressIFILoption|setencryptIFILoption|errorOnCorruptIFILoption|chgflexrecIFILoption|repairCorruptIFILoption)
#define tfilnoIFILallRebuild	(updateIFILoption|purgeIFILoption|badpartIFILoption|redosrlIFILoption|errorOnCorruptIFILoption|skipdatascanIFILoption|repairCorruptIFILoption)

#define setIFILoptions(x) ((-(x)) & ~tfilnoIFILoldbit)

/* rebuild/compact purge bits */
#define PURGE_OPT 	0x00000001 /* original purge option */
#define REPAIR_OPT 	0x00000002 /* attempt repairs (bypass DCPT_ERR) */


/*
 * YOU MAY ADD ONE OR MORE OF THE FOLLOWING DEFINES TO MAINTAIN 
 * COMPATIBILITY WITH c-tree PLUS RELEASES PRIOR TO RELEASE C.
 *
#define FIXED		ctFIXED
#define KEEP		ctKEEP
 *
 */

/*
** system log class codes
*/
#define ctSYSLOGuser	  	0x001		/* user logon info	*/
#define ctSYSLOGddmp		0x002		/* dynamic dump info	*/
#define ctSYSLOGstat		0x003		/* CTSTATUS entries	*/
#define ctSYSLOGtmpuser	  	0x004		/* temp user logon info	*/
#define ctSYSLOGdelfil	  	0x005		/* file deletion	*/
#define ctSYSLOGanl	  	0x006		/* abort node list	*/
#define ctSYSLOGsnap		0x007		/* snapshot		*/
#define ctSYSLOGrstpnt		0x008		/* restore points	*/
#define ctSYSLOGsql 		0x010		/* SQL info	*/
#define ctSYSLOGpurge		0x400		/* special purge request*/
#define ctSYSLOGapi		0x401		/* beg of user defined	*/
						/* defined classes	*/
	/* user info event codes */
#define ctSYSLOGuserLOGON 	((LONG) 0x001)	/* successful logon	*/
#define ctSYSLOGuserLOGOFF	((LONG) 0x002)	/* logoff		*/
#define ctSYSLOGuserLOGFAIL	((LONG) 0x003)	/* failed logon		*/
#define ctSYSLOGuserADDUSER	((LONG) 0x004)	/* add new user		*/
#define ctSYSLOGuserCHGUSER	((LONG) 0x005)	/* modify user profile	*/
#define ctSYSLOGuserDELUSER	((LONG) 0x006)	/* delete user		*/
#define ctSYSLOGuserSQLLOGON 	((LONG) 0x007)	/* successful SQL logon	*/
#define ctSYSLOGuserSQLLOGOFF	((LONG) 0x008)	/* SQL logoff		*/
#define ctSYSLOGuserSQLLOGFAIL	((LONG) 0x009)	/* failed SQL logon	*/
	/* dynamic dump event codes */
#define ctSYSLOGddmpBEGIN	((LONG) 0x001)	/* begin dynamic dump	*/
#define ctSYSLOGddmpTRAN	((LONG) 0x002)	/* tran control file	*/
#define ctSYSLOGddmpCLEAN	((LONG) 0x003)	/* clean non-tran file	*/
#define ctSYSLOGddmpDIRTY	((LONG) 0x004)	/* dirty non-tran file	*/
#ifdef ctFeatEVENTLOG_VER2
#define ctSYSLOGddmpINFO	((LONG) 0x005)	/* dump information	*/
#define ctSYSLOGddmpWARN	((LONG) 0x006)	/* dump warning 	*/
#define ctSYSLOGddmpERR		((LONG) 0x007)	/* fatal dump error	*/
#endif
#define ctSYSLOGddmpEND		((LONG) 0x010)	/* end dynamic dump	*/

	/* file deletion event codes */
#define ctSYSLOGdelfRSTR	((LONG) 0x001)	/* restorable delete	*/
#define ctSYSLOGdelfTRAN	((LONG) 0x002)	/* tran dependent	*/
#define ctSYSLOGdelfNOTRAN	((LONG) 0x003)	/* not tran dependent	*/

	/* abort node list event codes */
#define ctSYSLOGanlADDDEL	((LONG) 0x001)	/* add / del pair	*/

	/* snapshot event codes */
#define ctSYSLOGsnapSYSTEM 	((LONG) 0x001)	/* system snapshot	*/
#define ctSYSLOGsnapFILE	((LONG) 0x002)	/* file snapshot	*/
#define ctSYSLOGsnapUSER	((LONG) 0x003)	/* user snapshot	*/

	/* restore point info event codes */
#define ctSYSLOGrstpntCREATE 	((LONG) 0x001)	/* create restore point */
#define ctSYSLOGrstpntRECOVERY	((LONG) 0x002)	/* recovery results	*/
#define ctSYSLOGrstpntTRANBAK	((LONG) 0x003)	/* TRANBAK results	*/
#define ctSYSLOGrstpntNOKEEP 	((LONG) 0x004)	/* create RP but no keep*/

	/* SQL info event codes */
#define ctSYSLOGsqlSTMT 	((LONG) 0x001)	/* SQL statement */

#define ctRPbvr		24	/* base variable region			*/
typedef struct rstpntsyslog {
	ULONG	bitmap;		/* syslog rstpnt bitmap			*/
	LONG	varlen;		/* len of var region (may be > ctRPbvr)	*/
	LONG8	rstpntsrn;	/* restore point serial number		*/
	LONG	rstpntlog;	/* restore point log#			*/
	ULONG	rstpntpos;	/* restore point log position		*/
	ULONG	rstpnttim;	/* restore point system time		*/
	LONG	rstpnttim2;	/* system time extension		*/
	LONG	skplog;		/* skip forward log number		*/
	ULONG	skppos;		/* skip forward log position		*/
	ULONG	avail;		/* available				*/
	ULONG	temptim;	/* time event added to temp event file	*/
	LONG	temptim2;	/* temptim extension			*/
	UCOUNT	rstpntver;	/* restore point version		*/
	UCOUNT	rstpnttyp;	/* restore point type			*/
	TEXT	var_region[ctRPbvr]; /* beginning of var region		*/
	} syslogRP, * psyslogRP;

#define syslogRPname		0x000001/* RP name in var region	*/
#define syslogRPminlogsync	0x000002/* DELAYED_DURABILITY on at crash*/
#define syslogRPrec_to_rstpnt	0x000004/* RECOVER_TO_RESTORE_POINT on	*/
#define syslogRPstart_rolbak	0x000008/* rollback attempted		*/
#define syslogRPpndg_rolbak	0x000010/* rollback to RP pending	*/
#define syslogRPno_rstpnt	0x000020/* NO restore points		*/
#define syslogRPno_rolbak_sup	0x000040/* rollback not supported	*/
#define syslogRPno_tran_undo	0x000080/* may be trans not undone	*/
#define syslogRProlbak_err	0x000100/* rollback error		*/
#define syslogRPskipto_err	0x000200/* error inserting skipto info	*/
#define syslogRPdef_not_rstpnt	0x000400/* RECOVER_TO_... NO by default */
#define syslogRPskip_pndg	0x000800/* skip pending rollback	*/
#define syslogRPno_tran_to_undo	0x001000/* no trans to undo, skip rolbak*/
#define syslogRProlbak_rstpnt	0x002000/* rollback to restore point	*/
#define syslogRPno_fnd_rstpnt	0x004000/* did not find restore point	*/
#define syslogRPskip_pndg_sync	0x008000/* skip pending rollback && MLS	*/
#define syslogRPpndg_rolbak_sync 0x10000/* rollback to RP pending && MLS*/
#define syslogRProlbak_not_rqst	0x020000/* rollback to RP not requested */
#define syslogRPavailable	0x040000/* available for use		*/

			/*
			** final system state indicators
			*/
#define syslogRP_FSrolbak	0x0080000/* successful rollback to RP	*/
#define syslogRP_FSno_rolbak_OK	0x0100000/* no rollback to RP. no MLS.	*/
#define syslogRP_FSrolbak_err	0x0200000/* rollback error		*/
#define syslogRP_FSno_rolbak_MLS 0x400000/* no rollback to RP, but MLS	*/
#define syslogRP_FSrolbak_NRP	0x0800000/* rollback did not find RP	*/
#define syslogRP_FSrolbak_chg	0x1000000/* rollback NORP. try explicit **
					 ** RECOVER_TO_RESTORE_POINT NO	*/
#define syslogRP_FSrolbak_chg2	0x2000000/* rollback NORB. try explicit **
					 ** RECOVER_TO_RESTORE_POINT NO	**
					 ** or YES			*/
#define syslogRP_FSrolbak_err2	0x4000000/* rollback error on skipto upd*/

			/*
			** final system state indicator test mask
			*/
#define syslogRP_FStest	(syslogRP_FSrolbak		| \
			 syslogRP_FSno_rolbak_OK	| \
			 syslogRP_FSrolbak_err		| \
			 syslogRP_FSno_rolbak_MLS	| \
			 syslogRP_FSrolbak_NRP		| \
			 syslogRP_FSrolbak_chg		| \
			 syslogRP_FSrolbak_chg2		| \
			 syslogRP_FSrolbak_err2)


#define SYSLOGmax	8192
#define SYSLOGidz	32
#ifdef ctFeatEVENTLOG_VER2
#define SYSLOGfix 	(11 * ctSIZE(LONG) + 2 * SYSLOGidz + 2 * ctSIZE(UCOUNT))
#else
#define SYSLOGfix 	( 7 * ctSIZE(LONG) + 2 * SYSLOGidz + ctSIZE(COUNT))
#endif
#define SYSLOGvar	(SYSLOGmax - SYSLOGfix + 2)

typedef struct ctslog {
	LONG	evclass;/* overall type of entry			*/
	LONG	event;	/* within each class, the particular event code */
	LONG	date;	/* date measured in days: r-tree compatible	*/
	LONG	time;	/* seconds past midnight			*/
	LONG	rsvrd;	/* for future use				*/
	LONG	seqnm;	/* sequence number				*/
	LONG	error;	/* uerr_cod at time of entry			*/
#ifdef ctFeatEVENTLOG_VER2
	ULONG	instid;	/* event instance ID, used to group events 	*/
#endif
	TEXT	userid[SYSLOGidz];	/* logon user ID		*/
	TEXT	nodnam[SYSLOGidz];	/* logon node name		*/
#ifdef ctFeatEVENTLOG_VER2
	ULONG	avail4[3];/* available-for-use padding to ensure vfld	*/
	UCOUNT	avail2;	  /* begins on a 16-byte boundary		*/
#endif
	UCOUNT	vlen;	/* length of variable region			*/
	TEXT	vfld[2];/* beginning of variable region			*/
	} SYSLOGrec, ctMEM * pSYSLOGrec;


#define cfgFILES		0
#define cfgUSERS		1
#define cfgIDX_MEMORY		2
#define cfgDAT_MEMORY		3
#define cfgTOT_MEMORY		4
#define cfgUSR_MEMORY		5
#define cfgPREIMAGE_FILE	6
#define cfgPAGE_SIZE		7
#define cfgCOMMIT_DELAY_USEC	8
#define cfgLOG_SPACE		9
#define cfgLOG_EVEN		10
#define cfgLOG_ODD		11
#define cfgSTART_EVEN		12
#define cfgSTART_ODD		13
#define cfgSERVER_DIRECTORY	14
#define cfgLOCAL_DIRECTORY	15
#define cfgSERVER_NAME		16
#define cfgDUMP			17
#define cfgSQL_DATABASE		18
#define cfgKEEP_LOGS		19
#define cfgCOMM_PROTOCOL	20
#define cfgMPAGE_CACHE		21
#define cfgLIST_MEMORY		22
#define cfgSORT_MEMORY		23
#define cfgBUFR_MEMORY		24
#define cfgPREIMAGE_HASH	25
#define cfgLOCK_HASH		26
#define cfgUSR_MEM_RULE		27
#define cfgGUEST_MEMORY		28
#define cfgQUERY_MEMORY		29
#define cfgTRAN_TIMEOUT		30
#define cfgMAX_DAT_KEY		31
#define cfgBUFFER_RUNLENGTH	32
#define cfgSEMAPHORE_BLK	33
#define cfgSESSION_TIMEOUT	34
#define cfgTASKER_SLEEP		35
#define cfgFILE_HANDLES		36
#define cfgMEMORY_MONITOR	37
#define cfgTASKER_PC		38
#define cfgTASKER_SP		39
#define cfgTASKER_NP		40
#define cfgNODE_DELAY		41
#define cfgDEADLOCK_MONITOR	42
#define cfgNODEQ_MONITOR	43
#define cfgCOMMIT_DELAY		44
#define cfgCHECKPOINT_MONITOR	45
#define cfgNODEQ_SEARCH		46
#define cfgMAX_KEY_SEG		47
#define cfgFUNCTION_MONITOR	48
#define cfgTASKER_LOOP		49
#define cfgREQUEST_DELAY	50
#define cfgREQUEST_DELTA	51
#define cfg9074_MONITOR		52
#define cfg9477_MONITOR		53
#define cfgSKIP_MISSING_FILES	54
#define cfgTMPNAME_PATH		55
#define cfgLOG_EVEN_MIRROR	56
#define cfgLOG_ODD_MIRROR	57
#define cfgSTART_EVEN_MIRROR	58
#define cfgSTART_ODD_MIRROR	59
#define cfgADMIN_MIRROR		60
#define cfgSKIP_MISSING_MIRRORS	61
#define cfgCOMMENTS		62
#define cfgMIRRORS		63
#define cfg749X_MONITOR		64
#define cfgCOMPATIBILITY	65
#define cfgDIAGNOSTICS		66
#define cfgCONTEXT_HASH		67
#define cfgGUEST_LOGON		68
#define cfgTRANSACTION_FLUSH	69
#define cfgCHECKPOINT_FLUSH	70
#define cfgLOCK_MONITOR		71
#define cfgMEMORY_TRACK		72
#define cfgSUPPRESS_LOG_FLUSH	73
#define cfgPREIMAGE_DUMP	74
#define cfgRECOVER_MEMLOG	75
#define cfgRECOVER_DETAILS	76
#define cfgCHECKPOINT_INTERVAL	77
#define cfgRECOVER_SKIPCLEAN	78
#define cfgSIGNAL_READY		79
#define cfgSIGNAL_MIRROR_EVENT	80
#define cfgCHECKPOINT_IDLE	81
#define cfgSIGNAL_DOWN		82
#define cfgFORCE_LOGIDX		83
#define cfgCHECKPOINT_PREVIOUS	84
#define cfgTRAN_HIGH_MARK	85
#define cfgCTSTATUS_MASK	86
#define cfgCTSTATUS_SIZE	87
#define cfgMONITOR_MASK		88
#define cfgRECOVER_FILES	89
#define cfgSYNC_DELAY		90
#define cfgDIAGNOSTIC_INT	91
#define cfgDIAGNOSTIC_STR	92
#define cfgMAX_VIRTUAL_FILES	93
#define cfgFIXED_LOG_SIZE	94
#define cfgLANGUAGE		95
#define cfgMAX_FILES_PER_USER	96
#define cfgLOG_ENCRYPT		97
#define cfgCONSOLE		98
#define cfgSKIP_MISSING_LOG_MIRRORS 99
#define cfgCONNECTIONS		100
#define cfgNULL_STRING		101
#define cfgLOGON_FAIL_LIMIT	102
#define cfgLOGON_FAIL_TIME	103
#define cfgADMIN_ENCRYPT	104
#define cfgDISK_FULL_LIMIT	105
#define cfgDISK_FULL_VOLUME	106
#define cfgSESSCHG_ENABLE	107
#define cfgADMIN_WORD		108
#define cfgADMIN_KEY		109
#define cfgSYSLOG		110
#define cfgLOGON_MUST_TIME	111
#define cfgBROADCAST_PORT	112
#define cfgBROADCAST_DATA	113
#define cfgBROADCAST_INTERVAL	114
#define cfgLMT_MEMORY		115
#define cfgMIRROR_DIRECTORY	116
#define cfgCTSRVR_CFG		117
#define cfgCACHE_LINE		118
#define cfgSYSVIEW_WHAT		119
#define cfgSYSVIEW_WHEN		120
#define cfgDEAD_CLIENT_INTERVAL	121
#define cfgSERVER_SDK		122
#define cfgSTARTUP_BLOCK_LOGONS	123
#define cfgPROCESS_PRIORITY     124
#define cfgSQL_PORT             125

/*
** 126 through 127 are available, but to avoid
** a capacity problem, a new general keyword list (cfg2)
** has been created below
*/
#define cfgLAST			126

#define cfgDISKIO_MODEL		128
#define cfgTRANPROC		129
#define cfgRESOURCE		130
#define cfgCTBATCH		131
#define cfgCTSUPER		132
#define cfgFUTURE1		133
#define cfgVARLDATA		134
#define cfgVARLKEYS		135
#define cfgPARMFILE		136
#define cfgRTREE		137
#define cfgCTS_ISAM		138
#define cfgBOUND		139
#define cfgNOGLOBALS		140
#define cfgPROTOTYPE		141
#define cfgPASCALst		142
#define cfgPASCAL24		143
#define cfgWORD_ORDER		144
#define cfgFUTURE2		145
#define cfgUNIFRMAT		146
#define cfgLOCLIB		147
#define cfgANSI			148
#define cfgFILE_SPECS		149
#define cfgPATH_SEPARATOR	150
#define cfgLOGIDX		151
#define cfgHISTORY		152
#define cfgCONDIDX		153
#define cfgSRV_MODEL		154

#define cfgUNIFRMATapp		cfgUNIFRMAT
#define cfgLOCLIBapp		cfgLOCLIB
#define cfgDISKIO_MODELapp	cfgDISKIO_MODEL
#define cfgBOUNDapp		cfgBOUND
#define cfgNOGLOBALSapp		cfgNOGLOBALS

#define cfgTRANPROCapp		161
#define cfgRESOURCEapp		162
#define cfgCTBATCHapp		163
#define cfgCTSUPERapp		164
#define cfgFUTURE1app		165
#define cfgVARLDATAapp		166
#define cfgVARLKEYSapp		167
#define cfgPARMFILEapp		168
#define cfgRTREEapp		169
#define cfgCTS_ISAMapp		170
#define cfgTHREADapp		171
#define cfgINIT_CTREEapp	172
#define cfgPROTOTYPEapp		173
#define cfgPASCALstapp		174
#define cfgPASCAL24app		175
#define cfgWORD_ORDERapp	176
#define cfgFUTURE2app		177
#define cfgANSIapp		178
#define cfgPATH_SEPARATORapp	179
#define cfgLOGIDXapp		180
#define cfgHISTORYapp		181
#define cfgCONDIDXapp		182
#define cfgSERIALNBR		183
#define cfgVERSIONID 		184
#define cfgPORTID		185
#define cfgMAX_CONNECT		186
#define cfgVERSIONID2 		187
#define cfgVERSIONID_BASE	188

#define cfgMEMORY_USAGE		192
#define cfgMEMORY_HIGH		193
#define cfgNET_ALLOCS		194
#define cfgDNODE_QLENGTH	195
#define cfgCHKPNT_QLENGTH	196
#define cfgSYSMON_QLENGTH	197
#define cfgMONAL1_QLENGTH	198
#define cfgMONAL2_QLENGTH	199
#define cfgLOGONS		200
#define cfgNET_LOCKS		201
#define cfgPHYSICAL_FILES	202
#define cfgOPEN_FILES		203
#define cfgOPEN_FCBS		204
#define cfgUSER_FILES		205
#define cfgUSER_MEMORY		206
#define cfgLOG_RECORD_LIMIT	207
#define cfgFEACHK		208
#define cfgMAX_LOGONS		209
#define cfgMAX_NET_LOCKS	210
#define cfgMAX_PHYSICAL_FILES	211
#define cfgMAX_OPEN_FILES	212
#define cfgMAX_OPEN_FCBS	213
#define cfgFLEX_FCBS		214
#define cfgSYSLOG_QLENGTH	215
#define cfgRSPACE_QLENGTH	216
#define cfgCACHE_PAGES		217
#define cfgCACHE_PAGES_INUSE	218
#define cfgCACHE_PAGES_MXUSE	219
#define cfgCACHE_PAGES_DED	220
#define cfgCACHE_PAGES_DEDINUSE	221
#define cfgCACHE_PAGES_DEDMXUSE	222
#define cfgBUFFER_PAGES		223
#define cfgBUFFER_PAGES_INUSE	224
#define cfgBUFFER_PAGES_MXUSE	225
#define cfgMAX_CLIENT_NODES	226
#define cfgMAX_CONN_PER_NODE	227
#define cfgLOCAL_CONN_ONLY	228
#define cfgPROCESS_ID		229
#define cfgCOUNTED_LOGONS	230
#define cfgCFGCHK		231
#define cfgCACHE_STAT_ARRAY_SIZE 232
#define cfgDATA_LRU_LISTS	233
#define cfgINDEX_LRU_LISTS	234
#define cfgMEMORY_HASH		235
#define cfgCACHE_PAGES_SCN	236
#define cfgCACHE_PAGES_SCNINUSE	237
#define cfgCACHE_PAGES_SCNMXUSE	238
#define cfgFEACHK2		239

#define ctCFGLMT		256	/* elements in configuration array */

/*
** additional general purpose configuration keywords (cfg2)
*/

#define cfg2SPECIAL_CACHE_PERCENT	0
#define cfg2SPECIAL_CACHE_FILE		1
#define cfg2PRIME_CACHE			2
#define cfg2PRIME_INDEX			3
#define cfg2NO_CACHE			4
#define cfg2NO_FLUSH			5
#define cfg2IDLE_TRANFLUSH		6
#define cfg2IDLE_NONTRANFLUSH		7
#define cfg2SIGNAL_USER_READY		8
#define cfg2SIGNAL_USER_DOWN		9
#define cfg2SET_FILE_CHANNELS		10
#define cfg2DEFAULT_CHANNELS		11
#define cfg2THREAD_CONCURRENCY		12
#define cfg2LOG_PAGE_SIZE		13
#define cfg2SNAPSHOT_INTERVAL		14
#define cfg2SNAPSHOT_FILENAME		15
#define cfg2SNAPSHOT_USERID		16
#define cfg2COMMIT_DELAY_SCALE		17
#define cfg2COMMIT_DELAY_BASE		18
#define cfg2UDEFER_THRESHOLD_USEC	19
#define cfg2UDEFER_64YIELD_USEC		20
#define cfg2SUPPRESS_LOG_SYNC		21
#define cfg2LOGSET_ASSIGNMENT		22
#define cfg2SNAPSHOT_TRANTIME_USEC	23
#define cfg2LONG_TRANSACTION_MS		24
#define cfg2PERF_MONITOR		25
#define cfg2MEMORY_FILE			26
#define cfg2SETENV			27
#define cfg2ADVANCED_ENCRYPTION		28
#define cfg2LOG_TEMPLATE		29
#define cfg2HUGE_TO_SEG_MB		30
#define cfg2APP_NAME_LIST		31
#define cfg2MAX_K_TO_USE		32
#define cfg2MAX_HANDLES			33
#define cfg2WAIT_ON_SHUTDOWN_SEC	34
#define cfg2REPLICATE			35
#define cfg2MAX_USER_LOG_ENTRY_BYTES	36
#define cfg2PRESYNC_THRESHOLD		37
#define cfg2LOG_COMPRESSION_THRESHOLD	38
#define cfg2LOG_COMPRESSION_FACTOR	39
#define cfg2SNAPSHOT_LOCKWAIT_USEC	40
#define cfg2FILEDEF_SECURITY_LEVEL	41
#define cfg2LDAP_SERVER			42
#define cfg2LDAP_TIMEOUT		43
#define cfg2LDAP_BASE			44
#define cfg2ADMIN_USER_GROUP		45
#define cfg2GUEST_USER_GROUP		46
#define cfg2LOGIN_ALLOWED_GROUP		47
#define cfg2SERVER_PORT			48
#define cfg2AUTO_PREIMG			49
#define cfg2FILE_PERMISSIONS		50
#define cfg2FILE_CREATE_MODE		51
#define cfg2ITIM_RETRY_LIMIT		52
#define cfg2MAX_SQL_ISOLATION_LEVEL	53
#define cfg2PRIME_CACHE_BY_KEY		54
#define cfg2CHECK_CONFIG		55
#define cfg2COMMIT_LOCK_DEFER_TIME_MS	56
#define cfg2LATCH_SPIN			57
#define cfg2LATCH_SLEEP			58
#define cfg2AUTO_TRNLOG			59
#define cfg2AUTO_TRNLOG_LIGHT		60
#define cfg2MATCHING_SEGMENT		61
#define cfg2NONMATCHING_SEGMENT		62
#define cfg2INHERIT_FILE_PERMISSIONS	63
#define cfg2AUTO_LOCK_RETRY		64
#define cfg2AUTO_LOCK_RETRY_SLEEP	65
#define cfg2MAX_USER_LOGS		66
#define cfg2CHKPDFC_LOG_LIMIT		67
#define cfg2REPL_READ_BUFFER_SIZE	68
#define cfg2JOB_QUEUE_INFO 		69
#define cfg2SQL_MIN_CARD 		70
#define cfg2BLOCKING_LOCK_TIMEOUT_SEC	71
#define cfg2ITIM_RETRY_DEFER		72
#define cfg2SKIP_CTADDWORK		73
#define cfg2INDEX_LRU_LISTS		74
#define cfg2DATA_LRU_LISTS		75
#define cfg2BUFBLK_RATIO		76
#define cfg2AUTO_CLNIDXX		77
#define cfg2DNODEQ_SHUTDOWN_LIMIT	78
#define cfg2CPU_AFFINITY		79
#define cfg2REQUEST_TIME_MONITOR	80
#define cfg2PROCESS_EXIT_COMMAND	81
#define cfg2DIST_COUNT_SEC		82
#define cfg2IO_BLOCK_SIZE		83
#define cfg2IO_ERROR_BLOCK_SIZE		84
#define cfg2REPL_MAPPINGS		85
#define cfg2LOCK_HASH_MAX		86
#define cfg2LOCK_HASH_LOADFAC		87
#define cfg2LOCK_HASH_REHASHFAC		88
#define cfg2LOCK_HASH_NOSHRINK		89
#define cfg2PREIMAGE_HASH_MAX		90
#define cfg2PREIMAGE_HASH_LOADFAC	91
#define cfg2PREIMAGE_HASH_REHASHFAC	92
#define cfg2PREIMAGE_HASH_NOSHRINK	93
#define cfg2SPLIT_NBR_OF_FILES		94
#define cfg2LOG_TEMPLATE_COPY_SLEEP_TIME 95
#define cfg2LOG_TEMPLATE_COPY_SLEEP_PCT	96
#define cfg2IO_ERROR_BLOCK_RETRY	97
#define cfg2IO_ERROR_BLOCK_SLEEP	98
#define cfg2DYNAMIC_DUMP_DEFER		99
#define cfg2ENABLE_TRANSFER_FILE_API	100
#define cfg2MEMORY_HASH			101
#define cfg2UNBUFFERED_IO		102
#define cfg2VSS_WRITER			103
#define cfg2REPL_SRLSEG_ALLOW_UNQKEY	104
#define cfg2REPL_SRLSEG_USE_MASTER	105
#define cfg2REPL_SRLSEG_USE_SOURCE	106
#define cfg2SKIP_INACCESSIBLE_FILES	107
#define cfg2MEMFILE_MAX_BINS		108
#define cfg2SQL_OPEN_TABLES		109
#define cfg2SQL_IDLE_TIMEOUT		110
#define cfg2CRITICAL_SECTION_SPIN	111
#define cfg2KEEPOPEN_LIST		112
#define cfg2REDIRECT			113
#define cfg2REDIRECT_IFIL		114
#define cfg2TRAN_OVERFLOW_THRESHOLD	115
#define cfg2SECURE_LOGONS_ONLY		116
#define cfg2VLEN_ERR_RETRY_LIMIT	117
#define cfg2CMPREC_TYPE			118
#define cfg2CMPREC_VERSION		119
#define cfg2CMPREC_DLL			120
#define cfg2KEEPOPEN_CLOSE_RETRY_LIMIT	121
#define cfg2SHMEM_DIRECTORY		122
#define cfg2REPL_NODEID			123
#define cfg2UNBUFFERED_LOG_IO		124
#define cfg2MASTER_KEY_FILE		125
#define cfg2PARTITION_ESTIMATE_LIMIT	126
#define cfg2AUTO_MKDIR			127
#define cfg2DISK_FULL_ACTION		128
#define cfg2SQL_PARTOPEN_COST		129
#define cfg2SQL_TRACE_CTREE_ERROR	130
#define cfg2COMPRESS_FILE		131
#define cfg2REPL_IDENTITY_USE_MASTER	132
#define cfg2REPL_IDENTITY_USE_SOURCE	133
#define cfg2SHMEM_PERMISSIONS		134
#define cfg2LDAP_APPLICATION_ID		135
#define cfg2LDAP_PREFIX			136
#define cfg2LDAP_ISAM_ALLOWED_GROUP	137
#define cfg2LDAP_SQL_ALLOWED_GROUP	138
#define cfg2LDAP_PORT			139
#define cfg2LDAP_SSL			140
#define cfg2LDAP_KEY_STORE		141
#define cfg2KEY_EXCHANGE_PARAMS		142
#define cfg2SUBSYSTEM			143
#define cfg2CACHE_STAT_ARRAY_SIZE	144
#define cfg2SQL_CONNECT_TIMEOUT_SEC	145
#define cfg2MAX_CONCURRENT_USER_ACCOUNTS 146
#define cfg2MAX_CONNECTIONS_PER_USER_ACCOUNT 147
#define cfg2MAX_ISAM_CONNECTIONS	148
#define cfg2MAX_SQL_CONNECTIONS		149
#define cfg2COALESCE_TRNLOG		150
#define cfg2LOAD_RTUSER_LIB		151
#define cfg2CTBPFX_LEVEL		152
#define cfg2DEBUG_FIXIDXBUFFERS		153
#define cfg2DEBUG_FIXDATCACHE		154
#define cfg2SCAN_CACHE_PERCENT		155
#define cfg2DEBUG_DELAY			156
#define cfg2USE_EMPTY_LIST		157
#define cfg2INDEX_HASHBIN_READER_PERCENT 158
#define cfg2INDEX_HASHBIN_RESET_LIMIT	159
#define cfg2DATA_HASHBIN_READER_PERCENT 160
#define cfg2DATA_HASHBIN_RESET_LIMIT	161
#define	cfg2PERMIT_NONTRAN_DUMP		162
#define	cfg2DYNAMIC_DUMP_DEFER_INTERVAL	163
#define	cfg2ALLOW_MASTER_KEY_CHANGE	164
#define	cfg2CHANGE_ENCRYPTION_ON_COMPACT 165
#define	cfg2MAX_FILE_WAIT_SECS		166
#define	cfg2SHMEM_KEY_ISAM		167
#define	cfg2SHMEM_KEY_SQL		168
#define	cfg2KEEPOPEN_FLUSH		169
/* #define cfg2AVAILABLE_FOR_REUSE	170 */
#define cfg2KEEP_RESTORE_POINTS		171
#define cfg2RECOVER_TO_RESTORE_POINT	172
#define cfg2SHMEM_GROUP			173
#define cfg2DELAYED_DURABILITY		174
#define cfg2UPDMARKS_SPLITCHK_PERCENT	175
#define cfg2NONTRAN_DATA_FLUSH_SEC	176
#define cfg2NONTRAN_INDEX_FLUSH_SEC	177
#define cfg2NONTRAN_DATA_FLUSH_BUCKETS	178
#define cfg2NONTRAN_INDEX_FLUSH_BUCKETS	179
#define cfg2COMMIT_DELAY_MINIMUM	180
#define cfg2TRAN_DATA_FLUSH_SEC		181
#define cfg2TRAN_INDEX_FLUSH_SEC	182
#define cfg2TRAN_DATA_FLUSH_BUCKETS	183
#define cfg2TRAN_INDEX_FLUSH_BUCKETS	184
#define cfg2LDAP_GROUP_CHECK		185
#define cfg2MAX_DFRIDX_LOGS		186
#define cfg2MAX_REPL_LOGS		187
#define cfg2MAX_REBUILD_QUEUE		188
#define cfg2TRANIDX_LOPN_ERR_CONTINUE	189
#define cfg2DELSTK_COMMIT_SEC		190
#define cfg2INTERMEDIATE_BLOCK_PAGING	191
#define cfg2CHECKLOCK_FILE		192
#define cfg2AUTOTRAN_ON_CREATE		193
#define cfg2DYNAMIC_DUMP_SYNC_INTERVAL	194
#define cfg2NONTRAN_FILESYS_FLUSH_OFF	195
#define cfg2DIST_ISAM_COUNTER_BUCKETS	196
#define cfg2FILESYS_COMPRESS_FILE	197
#define cfg2UNCSEG_KEYCOMPRESS		198
#define cfg2READONLY_SERVER		199
#define cfg2FILESYS_COMPRESS_UNCSEG	200
#define cfg2SHMEM_MAX_SPINNERS		201
#define cfg2RECOVERY_CHECK_DUPFID	202
#define cfg2CHECK_SYSTEM_FILEID		203
#define cfg2NODE_REUSE_DELAY		204
#define cfg2SQL_SESSION_TIMEOUT		205
#define cfg2OPTIMIZE_FILE_OPEN		206
#define cfg2PENDING_FILE_OPEN_RETRY_LIMIT 207
#define cfg2OPTIMIZE_FILE_CLOSE		208
#define cfg2LEAF_NODE_READ_LOCK		209
#define cfg2SUPPRESS_PATH_IN_IFIL	210
#define cfg2MAX_PREIMAGE_DATA		211
#define cfg2MAX_PREIMAGE_SWAP		212
#define cfg2OPEN_FILES_ALERT_THRESHOLD	213
#define cfg2LOCALCONN_ONLY          214
#define cfg2PLUGIN			215
#define cfg2LOG_FILE_ID_CHANGE		216
#define cfg2PLUGIN_CALLBACK		217
#define cfg2RECOVERY_RENAME_CHECK_FILE_ID 218
#define cfg2VSS_WRITER_QUIESCE_TIMEOUT	219
#define cfg2FILE_CLOSE_FLUSH		220
#define cfg2SYSTEM_FILE_ID_LIST		221
#define cfg2CLEANUP_ABLIST_ON_ABORT	222
#define cfg2TRUNCATE_FILE_TEST		223
#define cfg2HEAP_DEBUG_LEVEL		224
#define cfg2HEAP_DEBUG_EXCLUSION_LIST   225
#define cfg2MASTER_KEY_LIB		226
#define cfg2SYSTEM_TIMER_RESOLUTION	227
#define cfg2STACK_DUMP		        228
#define cfg2CHECK_FILENAME_VALIDITY	229
#define cfg2OPENSSL_ENCRYPTION		230
#define cfg2SYNC_COMMIT_TIMEOUT		231
#define cfg2LAST			232

/*
** special purpose configuration keywords
*/

#define cfgSQL_LOGFILE		0
#define cfgSQL_OPTION		1
#define cfgSQL_DEBUG		2
#define cfgSQL_SERVER_LOG_SIZE	3
#define sqlLAST			4

#define cfgICU_LOCALE			0
#define cfgICU_OPTION			1
#define cfgXTDKSEG_SEG_TYPE		2
#define cfgXTDKSEG_SRC_SIZE		3
#define cfgXTDKSEG_SRC_TYPE		4
#define cfgXTDKSEG_FAILED_DEFAULT_OK	5
#define ksgLAST				6

/*
** or'd to specify type of server
** (next type modifier would be 4, 8, etc.)
*/
#define cfgSRV_MODELbase		1
#define cfgSRV_MODELsql			2

/*
** compile time feature support (cfgFEACHK)
*/
#define cfgFEACHKplusName	((LONG)0x00000001) /* +name in PRM/TMPIIDXX   */
#define cfgFEACHKhugeFile	((LONG)0x00000002) /* huge file support	      */
#define cfgFEACHKcloseInTran	((LONG)0x00000004) /* close file in tran spprt*/
#define cfgFEACHKencryption	((LONG)0x00000008) /* encryption support      */
#define cfgFEACHKflexFile	((LONG)0x00000010) /* flex file limit support */
#define cfgFEACHKuniqFile	((LONG)0x00000020) /* unique file system spprt*/
#define cfgFEACHKdiskFull	((LONG)0x00000040) /* disk full system suprt  */
#define cfgFEACHKxtdCmp		((LONG)0x00000080) /* extended key compressn  */
#define cfgFEACHK6BT		((LONG)0x00000100) /* extended 6-byte tran#   */
#define cfgFEACHKoldBCD		((LONG)0x00000200) /* old BCD compatibility   */
#define cfgFEACHKeventLogVer2	((LONG)0x00000400) /* adv event log	      */
#define cfgFEACHKchkPntLst	((LONG)0x00000800) /* adj chkpnt list counters*/
#define cfgFEACHKnoFlushDel	((LONG)0x00001000) /* suppress flush on delete*/
#define cfgFEACHKzeroRecbyt	((LONG)0x00002000) /* zero RECBYT support     */
#define cfgFEACHKsysView	((LONG)0x00004000) /* system view log	      */
#define cfgFEACHKencrypTCPIP	((LONG)0x00008000) /* encrypt TCPIP	      */
#define cfgFEACHKlowlCRC	((LONG)0x00010000) /* comm low level CRC      */
#define cfgFEACHKcommSUMCHK	((LONG)0x00020000) /* comm sum check	      */
#define cfgFEACHKpag64K		((LONG)0x00040000) /* 64K page size supported */
#define cfgFEACHKreadShare	((LONG)0x00080000) /* read-only for shr'd file*/
#define cfgFEACHKsplCache	((LONG)0x00100000) /* dedicated cache support */
#define cfgFEACHKpriCache	((LONG)0x00200000) /* cache priming support   */
#define cfgFEACHKnoCache	((LONG)0x00400000) /* no cache data file list */
#define cfgFEACHKnoFlush	((LONG)0x00800000) /* skip flush on close     */
#define cfgFEACHKfpgCache	((LONG)0x01000000) /* data cache FPUTFGET     */
#define cfgFEACHKdataFilter	((LONG)0x02000000) /* data filters	      */
#define cfgFEACHKdepRename	((LONG)0x04000000) /* TRANDEP rename support  */
#define cfgFEACHKchannels	((LONG)0x08000000) /* flexible I/O channels   */
#define cfgFEACHKalgnchnl	((LONG)0x10000000) /* aligned IO channels     */
#define cfgFEACHKkeepopen	((LONG)0x20000000) /* KEEPOPEN 4 nonMEMFILES  */
#define cfgFEACHKiict		((LONG)0x40000000) /* immediate commit trans  */
#define cfgFEACHKxtdfldtyp	((LONG)0x80000000) /* extended data types     */

/*
** compile time feature support (cfgFEACHK2)
*/
#define cfgFEACHK2copyfile	((LONG)0x00000001) /* file copy API function  */
#define cfgFEACHK2repldefertran	((LONG)0x00000002) /* repl defer tran feature */
#define cfgFEACHK2getconninfo	((LONG)0x00000004) /* ctGetConnectionInfo() function */
#define cfgFEACHK2maxfile32	((LONG)0x00000008) /* 4 byte file numbers */

/*
** run time feature support
*/
#define cfgCFGCHKreplmap	((LONG)0x00000001) /* REPL_MAPPINGS in use    */
#define cfgCFGCHKmtclient	((LONG)0x00000002) /* mtclient DLL loaded     */
#define cfgCFGCHKxfrfile	((LONG)0x00000004) /* file transfer enabled   */
#define cfgCFGCHKadvenc		((LONG)0x00000008) /* advanced encryption enabled */

/*
 * configuration options that can be changed at run time using ctSETCFG().
 */
#define setcfgFUNCTION_MONITOR		1
#define setcfgCHECKPOINT_MONITOR	2
#define setcfgMEMORY_MONITOR		3
#define setcfgREQUEST_TIME_MONITOR	4
#define setcfgDYNAMIC_DUMP_DEFER	5
#define setcfgDYNAMIC_DUMP_DEFER_INTERVAL 6
#define setcfgCTSTATUS_MASK		7
#define setcfgDIAGNOSTICS		8
#define setcfgVSS_WRITER		9
#define setcfgCONFIG_OPTION		10
#define setcfgLOADKEY_OPTION		11

/*
 * Following defines support keywords which have a variety of string oriented
 * arguments.
 *
 * The function cfgsubset(NINT setnum,pTEXT kv) processes the arguments.
 */
#define subsetCOMP	0
#define subsetDIAG	1
#define subsetSTAT	2
#define subsetLANG	3
#define subsetCONS	4
#define subsetSLOG	5
#define subsetSVWT	6
#define subsetSVWN	7
#define subsetSQLO	8
#define subsetSQLD	9
#define subsetICUO	10
#define subsetKSGG	11
#define subsetKSGS	12
#define subsetSSDK	13
#define subsetPERF	14
#define subsetSDMP	15

/*
 * transaction history modes
 */

#define ctHISTlog	0x0001	/* set initial log or terminate		*/
#define ctHISTfirst	0x0002	/* get starting entry			*/
#define ctHISTnext	0x0004	/* get next     entry			*/
#define ctHISTfrwd	0x0008	/* scan logs forward (instead of back)	*/

#define ctHISTuser	0x0010	/* match user ID			*/
#define ctHISTnode	0x0020	/* match node name			*/
#define ctHISTpos	0x0040	/* match byte offset (record position)	*/
#define ctHISTkey	0x0080	/* match key value			*/
#define ctHISTloglmt	0x0100	/* limit on number of logs to scan	*/

/* reserve .......	0x0200	   for future use			*/
/* reserve .......	0x0400	   for internal use			*/
/* reserve .......	0x0800	   for internal use			*/

#define ctHISTdata	0x1000	/* return data record (image)		*/
#define ctHISTindx	0x2000	/* return key value			*/
#define ctHISTnet	0x4000	/* return net change, not intra details */
#define ctHISTinfo	0x8000	/* return identifying information	*/

#define ctHISTmapmask	0x00ff	/* HSTRSP imgmap length mask		*/
#define ctHISTkdel	0x0100	/* history key delete, no data image	*/
#define ctHISTdatfile	0x0200	/* data file entry returned		*/
#define ctHISTidxfile	0x0400	/* index file entry returned		*/
#define ctHISTvarfile	0x0800	/* variable length data file entry	*/

typedef struct hstrsp {
#ifdef ctFeat6BT
	LONG	tranno2;
#endif
	LONG	tranno;
	LONG	recbyt;
	LONG	lognum;
	ULONG	logpos;
	LONG	imglen;
	LONG	trntim;
	ULONG	trnfil;
	LONG	rechgh;
	UCOUNT	membno;
	UCOUNT	imgmap;
	COUNT	trntyp;
	COUNT	trnusr;
	} HSTRSP;
typedef HSTRSP ctMEM *	pHSTRSP;

/*
** extended flush (CTFLUSHX) modes
*/
#define ctFLUSHX_ISAM		0x00000001
#define ctFLUSHX_ASYNC		0x00000002
#define ctFLUSHX_LAST		0x00000004
#define ctFLUSHX_PERCENT	0x00000008
#define ctFLUSHX_BYTES		0x00000010
#define ctFLUSHX_USRALL		0x00000020
#define ctFLUSHX_SYSALL		0x00000040
#define ctFLUSHX_NONTRAN	0x00000080
#define ctFLUSHX_TRAN		0x00000100
/* reserved (ctFLUSHX_opnstp)	0x00000200  */
#define ctFLUSHX_NOSAVE		0x00000400
/* reserved (iFLUSH_TRNMOD)	0x00000800  */
#define ctFLUSHX_PRECLOSE	0x00001000 /* flush updated pages for file prior to closing file */
/* next ctFLUSHX_mode use:	0x00002000  */

#define UNLIMITEDFLUSH	   0xffffffff
/*
** asynchronous control modes
*/
#define ctASYNC_CANCEL		0x0001
#define ctASYNC_STATUS		0x0002

/*
** asynchronous thread types
*/
#define ctASYNC_FBASE		0x1000
#define ctASYNC_FLUSH		0x1001

/*
** asynchronous return values
*/
#define ctASYNC_completed	0	/* without error		*/
#define ctASYNC_cancelled	1	/* async thread cancelled	*/
#define ctASYNC_notfound	2	/* handle not found		*/
#define ctASYNC_badmode		3	/* bad mode parameter		*/
#define ctASYNC_running		4	/* async thread in progress	*/
/* return negative values if thread completes with error		*/


/*
** lock dump modes
*/
#define ctLOKDMPfile		0
#define ctLOKDMPuser		1
#define ctLOKDMPfileusers	6

/*
** lock dump reference numbers
*/
#define ctLOKDMPallfiles	-10
#define ctLOKDMPdatafiles	-11
#define ctLOKDMPindexfiles	-12
#define ctLOKDMPallusers	-13
#define ctLOKDMPcaller		-14

/*
** Database engine shutdown status codes
*/
#define ctSHTDWNnone		0	/* Shutdown not initiated	*/
#define ctSHTDWNstart		1	/* Shutdown initiated		*/
#define ctSHTDWNstopDIRTY	2	/* Shutdown completed, but some
					** clients remain active	*/
#define ctSHTDWNstopCLEAN	3	/* Shutdown completed with all
					** files closed and final
					** checkpoint logged		*/

/*
** ctFILBLK action codes
*/
#define ctFBblock		0x0001	/* block file access		*/
#define ctFBunblock		0x0002	/* unblock file access		*/
#define ctFBisam		0x0004	/* associated ISAM files	*/
#define ctFBlowl		0x0008	/* individual file		*/
#define ctFBsaveState		0x0010	/* save user's file state	*/
#define ctFBfailIfTranUpdated	0x0020	/* if a file has been updated in
					** a connection's transaction,
					** fail file block instead of
					** aborting the transaction.	*/
#define ctFBsuspend		0x0040	/* suspend file access		*/
#define ctFBautopen		0x0080	/* return FBLK_ERR (until auto
					** reopen)			*/
#define ctFBappopen		0x0100	/* return FBLK_ERR, then FBLK_RDO
					** when app can explicitly close
					** and reopen file		*/
#define ctFBdifuser		0x0200	/* different user can unblock
					** file access			*/
/*				0x0400	** reserved for internal use	*/
#define ctFBpersist		0x0800	/* file block survives blocker
					** disconnecting from server	*/
#define ctFBsysclose		0x1000	/* blocked file remains logically
					** opened, but is closed at
					** system level.		*/
/*				0x2000	** reserved for internal use	*/
/*				0x4000	** reserved for internal use	*/
/*				0x8000	** reserved for internal use	*/

/*
** ctQUIET action codes
**
** except for blockLogFiles, all other references to files
** imply c-tree data and/or index files
*/

#define ctQTblockFiles		      0x00000001  /* block files matching
						  ** filespec		      */
#define ctQTblockAllFiles	      0x00000002  /* block all files, ignore
						  ** filespec		      */
#define ctQTblockAllTranFiles	      0x00000004  /* block all files under
						  ** transaction control,
						  ** ignore filespec	      */
#define ctQTblockAllNonTranFiles      0x00000008  /* block all files not under
						  ** transaction control,
						  ** ignore filespec	      */
#define ctQTblockLogons		      0x00000010  /* block new logons	      */
#define ctQTblockTransactions	      0x00000020  /* block new transactions   */
#define ctQTblockError		      0x00000040  /* return error on block
						  ** instead of sleeping      */
#define ctQTnoActiveTran	      0x00000080  /* at the time the actions
						  ** specified by the above
						  ** blocking options are taken
						  ** ensure no transactions
						  ** are pending	      */
#define ctQTblockLogFiles	      0x00000100  /* block server log files
						  ** [requires ctQTnoActiveTran
						  ** and ctQTblockTransactions,
						  ** and blocked access to the
						  ** log files will sleep
						  ** regardless if
						  ** ctQTblockError is
						  ** specified]		      */

#define ctQTunblockTransactions	      0x00000200  /* permit new transactions  */
#define ctQTunblockLogons	      0x00000400  /* permit new logons	      */
#define ctQTunblockFiles	      0x00000800  /* permit file access	      */
#define ctQTunblockLogFiles	      0x00001000  /* permit log file access   */
/*				      0x00002000  reserved for internal use   */
#define ctQTblockAPI		      0x00004000  /* block all API's	      */
#define ctQTunblockAPI		      0x00008000  /* unblock all API's	      */
/*				      0x00010000  reserved for internal use   */
#define ctQTflushTranFiles	      0x00020000  /* flush before file block  */
#define ctQTflushNonTranFiles	      0x00040000  /* flush before file block  */
/*				      0x00080000  reserved for internal use   */
/*				      0x00100000  reserved for internal use   */
#define ctQTlog_restorepoint	      0x00200000  /* create log restore point */
#define ctQTlog_checkpoint	      0x00400000  /* checkpoint at restore pnt*/
#define ctQTunblockLogRestore	      0x00800000  /* permit new transactions  */
#define ctQTfailAfterTimeout	      0x01000000  /* abandon the quiesce attempt
						  ** if transactions are still
						  ** active after the timeout
						  ** period elapses */
#define ctQTwaitForReplReaders	      0x02000000  /* wait for replication log
						  ** readers to process the last
						  ** committed transaction */
#define ctQTignoreInactiveReplReaders 0x04000000  /* ignore any replication
						  ** readers that are not
						  ** currently connected */

#define ctQTavail3		      0x08000000  /* available for use */
#define ctQTavail4		      0x10000000  /* available for use */
#define ctQTavail5		      0x20000000  /* available for use */
#define ctQTavail6		      0x40000000  /* available for use */
#define ctQTavail7		      0x80000000  /* available for use */

#define ctQTblockALL (ctQTblockAllFiles | ctQTblockLogFiles | ctQTblockAPI)
#define ctQTflushAllFiles (ctQTflushTranFiles | ctQTflushNonTranFiles)

#define ctQTunblockALL (ctQTunblockTransactions | ctQTunblockLogons | ctQTunblockFiles | ctQTunblockLogFiles | ctQTunblockAPI | ctQTunblockLogRestore)

#define ctQTblockfileoptions (ctQTblockFiles | ctQTblockAllFiles | ctQTblockAllTranFiles | ctQTblockAllNonTranFiles)

#define ctQTblocks (ctQTblockALL | ctQTnoActiveTran | ctQTblockFiles | ctQTblockAllTranFiles | ctQTblockAllNonTranFiles | ctQTblockLogons | ctQTblockTransactions | ctQTlog_restorepoint)

/*
** ctLOKTIMOUT modes
*/

#define ctLTOdiagnostic		0x00000001	/* timeout generates diganostic
						** output		      */
#define ctLTOallusers		0x00000002	/* ADMIN user group requests
						** timeout for all users      */


/*
** Record bucket action codes
*/

#define	ctRECBKTrelease		0x00000001	/* Remove cache page from
						** record bucket hash list and
						** return it to LRU list.    */
#define	ctRECBKTupdated		0x00000002	/* Mark cache page updated   */
#define ctRECBKTflush		0x00000004	/* Write cache page to disk  */

/*
** ctLOKDYN action codes
*/
#define ctLOKDYNoptions		0x00000000	/* only return ctLOKDYN state */
#define ctLOKDYNdemote		0x00000001	/* turn off nodemote	      */
#define ctLOKDYNfree		0x00000002	/* turn off nofree	      */
#define ctLOKDYNnotranPersist	0x00000003	/* turn off tranPersist	      */
#define ctLOKDYNnolockDefer	0x00000004	/* turn off lockDefer	      */
#define ctLOKDYNnodemote	0x00000040	/* deny lock demotion w/o err */
#define ctLOKDYNnofree		0x00000080	/* deny lock free w/o err     */
#define ctLOKDYNtranPersist	0x00000100	/* lock persists unlock (tran)*/
#define ctLOKDYNlockDefer	0x00000200	/* lock causes deferred close */

/* reserve 0x00000400 0x00000800 0x00001000 for additional actions	      */
/* reserve 0x00000005 0x00000006 0x00000007 for additional action turn off    */

#define ctLOKDYNmask		(ctLOKDYNnodemote | ctLOKDYNnofree | ctLOKDYNtranPersist | ctLOKDYNlockDefer)



/*
** ctDISTINCTset actions
**
** ctDNCTifil is or'd with ctDNCTset/attribute/off/keysegoff to cause
** the corresponding IFIL entry to be updated. It is ignored with
** ctDNCTcompute.
**
** ctDNCTkeyseg_on is or'd with ctDNCTset/attribute/compute to include
** distinct counts for partial key values based on segment boundaries.
**
** ctDNCTkeysegoff is used alone to turn off partial distinct counts while
** maintaining whole key distinct counts. It has no real effect if it is or'd
** with ctDNCToff since ctDNCToff turns off all distinct support, including
** partial distinct counts.
*/

#define ctDNCTset       1	/* unconditionally compute/set distinct
				** count and set attribute on		*/
#define ctDNCTattribute 2	/* if DISTINCT already turned on, return
				** estimate, else as in ctDNCTset	*/
#define ctDNCTcompute   4	/* unconditionally compute distinct
				** count, but no change to attribute
				** or header's distinct count		*/
#define ctDNCTifil	8	/* update corresponding IFIL entry	*/
#define ctDNCToff	16	/* turn off distinct count support	*/
#define ctDNCTkeyseg_on	32	/* add keyseg partial distinct counts	*/
#define ctDNCTkeysegoff	64	/* turn keyseg partial distinct off	*/

/*
** partial key discount count value structure
*/
typedef struct dstsegv {
	LONG	nbrsegs;	/* number of segments			*/
	LONG	lensegs;	/* combined segment lengths		*/
	LONG	dstseg2;	/* high order distinct count		*/
	LONG	dstseg1;	/* low  order distinct count		*/
	} DSTSEGV, *pDSTSEGV;

/*
** ctImpersonateTask actions
*/

#define ctIMPallow	1	/* Allow the specified connection or all
				** connections (if taskid is ctIMPall)
				** to impersonate this connection.	*/
#define ctIMPdisallow	2	/* Do not allow this connection to be
				** impersonated (which is the default
				** setting for a connection). taskid is
				** ignored.				*/
#define ctIMPbegin	3	/* Begin impersonation of the connection
				** whose task ID is taskid.		*/
#define ctIMPend	4	/* End impersonation of the connection
				** that is currently being impersonated.
				** taskid is ignored.			*/

#define ctIMPall	1	/* Use as mode with ctIMPallow to allow
				** impersonation by any taskid.		*/

/*
** ctasskey modes
*/
#define	ctAKrrec	0	/* regular record call: the ctasskey code
				** depends on this zero value. Changing
				** ctAKrrec to a non-zero "bit" will require
				** coding changes in ctasskey		      */
#define ctAKprec	1	/* partial record call from rewrite	      */
#define ctAKorec	2	/* prec & segs outside prec already filled-in */
#define ctAKncdx	4	/* skip conditional index check		      */

/*
** ctMEMSTAT modes
*/
#define ctMEMSTATfull		0 /* Log all occurrences of each call stack   */
#define ctMEMSTATaggr		1 /* Log only one occurrence per call stack   */
#define ctMEMSTATgetseq		2 /* Get current memory alloc sequence number */
#define ctMEMSTATunload		3 /* Unload debug symbols for memory tracking */
#define ctMEMSTATopts		4 /* Set memory allocation tracking options   */

/*
** transaction log modes
*/
#define ctlogALL		1
#define ctlogLOG		2
#define ctlogSTART		3
#define ctlogLOG_EVEN		4
#define ctlogLOG_ODD		5
#define ctlogSTART_EVEN		6
#define ctlogSTART_ODD		7
#define ctlogSTATUS		8

#define ctlogALL_MIRROR		17
#define ctlogLOG_MIRROR		18
#define ctlogSTART_MIRROR	19
#define ctlogLOG_EVEN_MIRROR	20
#define ctlogLOG_ODD_MIRROR	21
#define ctlogSTART_EVEN_MIRROR	22
#define ctlogSTART_ODD_MIRROR	23

#ifndef ctWAITFOREVER
#define ctWAITFOREVER		((LONG) -1)
#endif
#ifndef ctNOWAIT
#define ctNOWAIT		((LONG) 0)
#endif
#ifndef qctBLOCK_INTERVAL
#define qctBLOCK_INTERVAL	3000	/* milliseconds */
#endif

#define ctThrdFIXED_THREADS	((LONG) 0x0001)
#define ctThrdSRV_MAIN		((LONG) 0x0002)
#define ctThrdCHECK_INIT	((LONG) 0x0004) /* check if ctThrdInit() has been called yet */

#define rtENGLISH		1
#define rtSJIS			2
#define rtEUC			4
#define rtLANGUAGEmask		(rtENGLISH | rtSJIS | rtEUC)
/* reserved for additional lang	8					*/
#define rtEXTDODAflag		0x0010	/* for internal use only	*/
#define rtFREDODAflag		0x0020	/* for internal use only	*/
#define rtBLOCKEDflag		0x0040	/* for internal use only	*/
#define rtNOWAITflag		0x0080	/* return w/o waiting for 	**
					** report to complete		*/

typedef struct segmdef {
	pTEXT	sgname;
	LONG	sgsize; /* in MBs */
	} SEGMDEF;
typedef SEGMDEF ctMEM *	pSEGMDEF;

#define ctEXISTING_SEGMENT_RENAME	1
#define ctEXISTING_SEGMENT_ERROR	2
#define ctEXISTING_SEGMENT_DELETE	3
#define ctEXISTING_SEGMENT_OVERWRITE	4

/*
** single entry point general parameters
*/
typedef struct sepblk {
	LONG	hghwrd;
	LONG	longval;
	VRLEN	sizeval;
	NINT	filno;
	} SEPBLK, ctMEM * pSEPBLK;

#define ctSEPLNGputkdef		1	/* PUTKSEGDEF			*/
#define ctSEPLNGgetkdef		2	/* GETKSEGDEF			*/
#define ctSEPLNGxfmkdef		3	/* XFMKSEGDEF			*/
#define ctSEPLNGctunic		4	/* ctunic			*/
#define ctSEPLNGgetxcreblk	5	/* GETXCREBLK			*/
#define ctSEPLNGctflushx	6	/* CTFLUSHX			*/
#define ctSEPLNGctasync		7	/* CTASYNC			*/
#define ctSEPLNGctksegswpchk	8	/* ctksegswpchk			*/
#define ctSEPLNGsnapshot	9	/* ctSNAPSHOT			*/
#define ctSEPLNGsysput		10	/* ctSYSPUT			*/
#define ctSEPLNGclsnam		11	/* ctCLSNAM			*/
#define ctSEPLNGsq_open		12	/* ctSysQueueOpen		*/
#define ctSEPLNGsq_close	13	/* ctSysQueueClose		*/
#define ctSEPLNGsq_write	14	/* ctSysQueueWrite		*/
#define ctSEPLNGsq_lifow	15	/* ctSysQueueLIFOWrite		*/
#define ctSEPLNGsq_read		16	/* ctSysQueueRead		*/
#define ctSEPLNGsq_mlen		17	/* ctSysQueueMlen		*/
#define ctSEPLNGsq_count	18	/* ctSysQueueCount		*/
#define ctSEPLNGsq_notify	19	/* ctNotify			*/
#define ctSEPLNGalcrng		20	/* ALCRNG			*/
#define ctSEPLNGblkred		21	/* BLKIREC			*/
#define ctSEPLNGtranusr		22	/* TRANUSR			*/
#define ctSEPLNGrp_setlogps	23	/* ctReplSetPosByLogPos		*/
#define ctSEPLNGrp_setlogtm	24	/* ctReplSetPosByTime		*/
#define ctSEPLNGrp_getfname	25	/* ctReplGetFileName		*/
#define ctSEPLNGrp_getnxtch	26	/* ctReplGetNextChange		*/
#define ctSEPLNGrp_persist	27	/* ctReplPersistMinLog		*/
#define ctSEPLNGsetcbrbl	28	/* SETCBRBL			*/
#define ctSEPLNGfilmtx		29	/* ctFILMTX			*/
#define ctSEPLNGloklst		30	/* ctLOKLST			*/
#define ctSEPLNGfilblk		31	/* ctFILBLK			*/
#define ctSEPLNGsetcfg		32	/* ctSETCFG			*/
#define ctSEPLNGfilwcd		33	/* ctFILWCD			*/
#define ctSEPLNGquiet		34	/* ctQUIET			*/
#define ctSEPLNGloktimout	35	/* ctLOKTIMOUT			*/
#define ctSEPLNGupdticu		36	/* ctUPDTICU			*/
#define ctSEPLNGgetopenfiles	37	/* ctGetOpenFiles		*/
#define ctSEPLNGgetfileusers	38	/* ctGetFileUsers		*/
#define ctSEPLNGgetfilelocks	39	/* ctGetFileLocks		*/
#define ctSEPLNGlokdyn		40	/* ctLOKDYN			*/
#define ctSEPLNGreplagent	41	/* ctReplAgentOp		*/
#define ctSEPLNGtransferfile	42	/* ctTransferFile		*/
#define ctSEPLNGestrng		43	/* ESTRNG			*/
#define ctSEPLNGsequence	44	/* ctSEQUENCE			*/
#define ctSEPLNGmasterctl	45	/* ctMASTERCTL			*/
#define ctSEPLNGdstestxtd	46	/* ctDISTINCTestXtd		*/
#define ctSEPLNGdstsetxtd	47	/* ctDISTINCTsetXtd		*/
#define ctSEPLNGverifyidx	48	/* ctVERIFYidx			*/
#define ctSEPLNGaddIDfield	49	/* addIDfield			*/
#define ctSEPLNGdelIDfield	50	/* delIDfield			*/
#define ctSEPLNGgetIDfield	51	/* getIDfield			*/
#define ctSEPLNGresetIDfield	52	/* resetIDfield			*/
#define ctSEPLNGwchIDfield	53	/* wchIDfield			*/
#define ctSEPLNGmemstat		54	/* ctMEMSTAT			*/
#define ctSEPLNGsetCOMPRESS	55	/* ctSETCOMPRESS		*/
#define ctSEPLNGxtdatrIDfield	56	/* xtdatrIDfield		*/
#define ctSEPLNGcopyfile	57	/* ctCopyFile			*/
#define ctSEPLNGverifyfile	58	/* ctVerifyFile			*/
#define ctSEPLNGgetfilx		59	/* GETFILX			*/
#define ctSEPLNGdfkctl		60	/* ctDeferredIndexControl	*/
#define ctSEPLNGrucbctl		61	/* ctRecordUpdateCallbackControl*/
#define ctSEPLNGrp_setfflt	62	/* ctReplSetFileFilter		*/
#define ctSEPLNGfulltext	63	/* ctFullText			*/
#define ctSEPLNGalterschema	64	/* ctAlterSchema		*/
#define ctSEPLNGrp_chkfflt	65	/* ctReplCheckFileFilter	*/
#define ctSEPLNGtempdir		66	/* ctTempDir			*/
#define ctSEPLNGlogrrsync	67	/* ctReplLogFileResync		*/
#define ctSEPLNGgetacctexptime	68	/* ctGetAccountExpirationTime	*/
#define ctSEPLNGgetconninfo	69	/* ctGetConnectionInfo		*/
#define ctSEPLNGupdkeyrecbyt	70	/* UpdateRecordOffsetForKey	*/
#define ctSEPLNGuserinfoxtd	71	/* USERINFOX			*/
#define ctSEPLNGsyncreplctrl	72	/* ctSyncReplControl		*/
#define ctSEPLNGaddAutoSysTimeFields	73	/* addAutoSysTimeFields	     */
#define ctSEPLNGRemoveAutoSysTimeFields	74	/* RemoveAutoSysTimeFields   */
#define ctSEPLNGWhichAutoSysTimeFields	75	/* WhichAutoSysTimeFields    */
#define ctSEPLNGUpdateAutoSysTimeFields	76	/* WhichAutoSysTimeFields    */
#define ctSEPLNGGetFileRegions	77	/* GetFileRegions		*/
#define ctSEPLNGgetopenfilesxtd	78	/* ctGetOpenFilesXtd		*/
#define ctSEPLNGrp_setlogposbytranid 79 /* ctReplSetPosByTransactionId */
#define ctSEPLNGctfilelist	80	/* ctFILELIST */
#define ctSEPLNGrp_readlogdata	81	/* ctReplReadLogData		*/
#define ctSEPLNGreplagentfunc	82	/* replication agent function call */
#define ctSEPLNGcleanupTranStateKeys 83	/* ctReplCleanupTranStateKeys */
#define ctSEPLNGclusterConfig	84	/* ctClusterConfig */
#define ctSEPLNGtruncateFile	85	/* ctTruncateFile */
/* ctSIBLING_SEPLNG: Add new sub-function # here and increment ctSEPLNGlimit */

#define ctSEPLNGlimit		86

/*
** extended key segment definition structures
** and parameters
*/
#define ctKSEGDLEN	32	/* length of desc string*/
typedef struct keysegdef {
	LONG	kseg_stat;	/* status (internal use)*/
	LONG	kseg_vrsn;	/* version info		*/
	LONG	kseg_ssiz;	/* source size		*/
	LONG	kseg_type;	/* segment type		*/
	LONG	kseg_styp;	/* source type		*/
	LONG	kseg_comp;	/* comparison options	*/
	LONG	kseg_rsv1;	/* internal use		*/
	LONG	kseg_rsv2;	/* internal use		*/
	TEXT	kseg_desc[ctKSEGDLEN];
				/* text specification	*/
				/* eg, locale string	*/
	} ctKSEGDEF;
typedef ctKSEGDEF ctMEM * pctKSEGDEF, ctMEM ** ppctKSEGDEF;
#define ctKSEGDEFlongs		8
#define ctKSEGDEFlongsLEN (ctKSEGDEFlongs * sizeof(LONG))

/*
** used with ctSEPLNG
*/
typedef struct keysegdefsep {
	LONG	segno;
	ctKSEGDEF
		kdef;
	} ctKSEGDEFsep, ctMEM * pctKSEGDEFsep;
#define ctKSEGDEFseplng		(ctKSEGDEFlongs + 1)

#define CTUNICfixlen			256
typedef struct ctunicsep {
	ConvBlk	blk;
	LONG	segno;
	LONG	datlen;
	TEXT	recpos[CTUNICfixlen];
	} CTUNICsep, ctMEM * pCTUNICsep;

typedef struct ctunicsep2 {
	ConvBlk2 blk;
	UCOUNT	pad;
	LONG	segno;
	LONG	datlen;
	TEXT	recpos[CTUNICfixlen];
	} CTUNICsep2, ctMEM * pCTUNICsep2;

#define ctKSEGnew			64	/* new, 1st time	*/
#define ctKSEGopn			128	/* opened		*/
#define ctKSEGrcr			256	/* recursive call	*/
#define ctKSEGdef			512	/* default opened	*/
#define ctKSEGfbk			1024	/* fallback opened	*/
#define ctKSEGnewMASK			63

#define ctKSEGserver			(-1)
#define ctKSEGapplic			(-2)
#define ctKSEGdata			(-3)
#define ctKSEGindex			(-4)
#define ctKSEGsegment			(-5)
#define ctKSEGhandle			(-6)
#define ctKSEGabandon			(-7)
#define ctKSEGfile			(-8)
#define ctKSEGcreidx			(-9)	/* extended key segment definitions for call to create new index */
#define ctKSEGmatch			1	/* force exact match search */

/* Extended key segment types used in kseg_type field of ctKSEGDEF structure: */
#define ctKSEG_TYPE_UNICODE		1	/* ICU Unicode Support	    */
#define ctKSEG_TYPE_RTG			2	/* COBOL USAGE IS DISPLAY   */
#define ctKSEG_TYPE_JSON		3	/* JSON index		    */

#define ctKSEG_TYPE_LIMIT		4	/* one more than last type  */

/* ctSIBLING_XTDKSEG - add new extended key segment type and increase ctKSEG_TYPE_LIMIT */

#define ctKSEG_SEGN_INDXFL		-1
#define ctKSEG_SEGN_DATAFL		-2
#define ctKSEG_SEGN_SYSTEM		-4

/*
** UNICODE specific ctKSEG_COMP options
*/
		/* strength */
#define ctKSEG_COMPU_S_PRIMARY		0x00000001
#define ctKSEG_COMPU_S_SECONDARY	0x00000002
#define ctKSEG_COMPU_S_TERTIARY		0x00000004
#define ctKSEG_COMPU_S_QUATERNARY	0x00000008
#define ctKSEG_COMPU_S_IDENTICAL	0x00000010
#define ctKSEG_COMPU_S_DEFAULT		0x00000020
#define ctKSEG_COMPU_S_RESERVED		0x00000040

#define ctKSEG_COMPU_S_TEST (ctKSEG_COMPU_S_PRIMARY | ctKSEG_COMPU_S_SECONDARY | ctKSEG_COMPU_S_TERTIARY | ctKSEG_COMPU_S_QUATERNARY | ctKSEG_COMPU_S_IDENTICAL | ctKSEG_COMPU_S_DEFAULT)

		/* normalization */
#define ctKSEG_COMPU_N_NONE		0x00000080
#define ctKSEG_COMPU_N_CAN_DECMP	0x00000100
#define ctKSEG_COMPU_N_CMP_DECMP	0x00000200
#define ctKSEG_COMPU_N_CAN_DECMP_CMP	0x00000400
#define ctKSEG_COMPU_N_CMP_DECMP_CAN	0x00000800
#define ctKSEG_COMPU_N_DEFAULT		0x00001000
#define ctKSEG_COMPU_N_RESERVED		0x00002000

#define ctKSEG_COMPU_N_TEST (ctKSEG_COMPU_N_NONE | ctKSEG_COMPU_N_CAN_DECMP | ctKSEG_COMPU_N_CMP_DECMP | ctKSEG_COMPU_N_CAN_DECMP_CMP | ctKSEG_COMPU_N_CMP_DECMP_CAN | ctKSEG_COMPU_N_DEFAULT)

#define ctKSEG_COMPU_N_NFD  ctKSEG_COMPU_N_CAN_DECMP
#define ctKSEG_COMPU_N_NFKD ctKSEG_COMPU_N_CMP_DECMP
#define ctKSEG_COMPU_N_NFC  ctKSEG_COMPU_N_CAN_DECMP_CMP
#define ctKSEG_COMPU_N_NFKC ctKSEG_COMPU_N_CMP_DECMP_CAN

		/* locale system default: default OK */
#define ctKSEG_COMPU_SYSDEFAULT_NOTOK	0x00004000
		/* locale fallback: default OK */
#define ctKSEG_COMPU_FALLBACK_NOTOK	0x00008000

		/* attributes */
#define ctKSEG_COMPU_A_FRENCH_ON	0x00010000
#define ctKSEG_COMPU_A_FRENCH_OFF	0x00020000
#define ctKSEG_COMPU_A_CASE_ON		0x00040000
#define ctKSEG_COMPU_A_CASE_OFF		0x00080000
#define ctKSEG_COMPU_A_DECOMP_ON	0x00100000
#define ctKSEG_COMPU_A_DECOMP_OFF	0x00200000
#define ctKSEG_COMPU_A_SHIFTED		0x00400000
#define ctKSEG_COMPU_A_NONIGNR		0x00800000
#define ctKSEG_COMPU_A_LOWER		0x01000000
#define ctKSEG_COMPU_A_UPPER		0x02000000
#define ctKSEG_COMPU_A_HANGUL		0x04000000

#define ctKSEG_STYP_PROVIDED	1
#define ctKSEG_STYP_UTF8	2
#define ctKSEG_STYP_UTF16	4
#define ctKSEG_STYP_UTF32	8	/* not supported */

#define ctKSEG_SSIZ_PROVIDED	(-1)
#define ctKSEG_SSIZ_COMPUTED	(-2)

/*
** RTG specific ctKSEG_COMP options
*/
#define ctKSEG_RTG_STYP_NUMSIGNED 0
#define ctKSEG_RTG_STYP_SCOMP2 1
#define ctKSEG_RTG_STYP_SCOMP3 2
#define ctKSEG_RTG_STYP_SBINARY 3
#define ctKSEG_RTG_STYP_BTDATE 4
#define ctKSEG_RTG_STYP_BTTIME 5

#define ctKSEG_RTG_COMP_TRAIL 0
#define ctKSEG_RTG_COMP_TRAILSEP 1
#define ctKSEG_RTG_COMP_LEADSEP 2
#define ctKSEG_RTG_COMP_LEAD 3

/*
** multibyte file name encoding support
*/

#define ctFnTypeNONE	0
#define ctFnTypeASCII	1
#define ctFnTypeUTF8	2
#define ctFnTypeUTF16	3
#define ctFnTypeUTF32	4
#define ctFnTypeLIMIT	5

#define ctFnPrefixNONE	ctFnPrefix[ctFnTypeNONE]
#define ctFnPrefixASCII	ctFnPrefix[ctFnTypeASCII]
#define ctFnPrefixUTF8	ctFnPrefix[ctFnTypeUTF8]
#define ctFnPrefixUTF16	ctFnPrefix[ctFnTypeUTF16]
#define ctFnPrefixUTF32	ctFnPrefix[ctFnTypeUTF32]
#define ctFnPrefixSIZE	8


/*
** partitioned file support
*/
				/* PTADMIN ptmode options		*/
#define ptADMINname	0x0001	/* partdesc is a file name (ignr prawno)*/
#define ptADMINkey	0x0002	/* partdesc is a key value (ignr prawno)*/
#define ptADMINraw	0x0004	/* use prawno (ignore partdesc)		*/
#ifdef ctIFNEEDED
/* The ptADMINmodify bit is available for use. */
#define ptADMINmodify	0x0008	/* modify standard operation. effect	**
				** depends on main ptmode option	*/
#endif
#define ptADMINpurge	0x0010	/* remove partition(s)			*/
#define ptADMINadd	0x0020	/* add partition(s)			*/
#define ptADMINarchive	0x0040	/* archive partitions(s)		*/
#define ptADMINbase	0x0080	/* modify lower limit on prawno		*/
#define ptADMINnumber	0x0100	/* modify limit on number of partitions	*/
#define ptADMINreuse	0x0200	/* reuse purged member raw #		*/
#define ptADMINactivate	0x0400	/* activate archived member		*/
#define ptADMINstatus	0x0800	/* return member status in sysiocod	*/
#define ptADMINmulti	0x1000	/* purge,archive,etc multiple partitions*/
#define ptADMINrule	0x2000	/* partdesc contains rule definition	*/
#define ptADMINrebuild	0x4000	/* rebuild partitions			*/
#define ptADMINnewthrd	0x8000	/* run PTADMIN in separate thread	*/

#define ptADMINid	(ptADMINname | ptADMINkey | ptADMINraw)
#define ptADMINops	(ptADMINpurge | ptADMINadd | ptADMINarchive | ptADMINbase | ptADMINnumber | ptADMINreuse | ptADMINactivate | ptADMINstatus | ptADMINrule | ptADMINrebuild)

/*  descriptive name for specific modifier				*/
#define	ptADMINdirty	ptADMINmodify	/* rebuild only dirty components*/

				/* partition member status codes	*/
#define pmSTATUSnone	0	/* member does not exist. IF CHANGED	*/
				/* FROM ZERO, SEE PTADMIN.		*/
#define pmSTATUSexst	1	/* member active			*/
#define pmSTATUSopnd	2	/* member active, and physically opened	*/
#define pmSTATUSarhv	3	/* member archived			*/
#define pmSTATUSpurg	4	/* member purged			*/
#define pmSTATUSrbld	5	/* member rebuilding			*/
#define pmSTATUSpnst	16	/* member new instance pending		*/
#define pmSTATUSpexs	17	/* member creation pending		*/
#define pmSTATUSpuse	18	/* member reuse pending			*/
#define pmSTATUSparc	19	/* member archive pending		*/
#define pmSTATUSppnd	20	/* member purge pending			*/



/*
** system queue support
*/

#define ctSYSQUEnamlen	64

#define ctSQ_MASK	127	/* mask internal modes		*/
#define ctSQ_1STRED	128	/* only 1st open can read	*/
				/* else any open can read	*/
#define ctSQ_OPNWRT	256	/* must open to write		*/
				/* else anyone can write	*/
#define ctSQ_1STCLS	512	/* shutdown by 1st opener	*/
				/* else shutdown when all users	*/
				/* close			*/
#define ctSQ_MONITOR	1024	/* track this system queue in   */
				/* memory file			*/

/* system queue monitor data structure */
typedef struct sqmdat {
	NINT	qhandle; /* system queue handle */
	TEXT	qname[ctSYSQUEnamlen]; /* system queue name */
} SQMDAT, *pSQMDAT;

/*
** ctNotify opcode options
*/
#define ctNT_ADDREC	1	/* ADDREC or ADDVREC		*/
#define ctNT_DELREC	2	/* DELREC or DELVREC		*/
#define ctNT_RWTREC	4	/* RWTREC or RWTVREC		*/
#define ctNT_CLSOBJ	8	/* close object			*/
#define ctNT_TOUCH	16	/* file touched (any update),
				** but only one notification per
				** transaction (if any)
				*/
#define ctNT_PARTIAL	32	/* notification does not span entire
				** transaction. some updates did not generate
				** a notification
				*/
#define ctNT_RWTPREC	64	/* RWTPREC			*/
#define ctNT_BLKIREC	128	/* used internally to indicate
				** call from BLKIREC
				*/


#define ctNT_ISMUPD	(ctNT_ADDREC | ctNT_DELREC | ctNT_RWTREC | ctNT_RWTPREC)

/*
** Deferred indexing operation codes.
*/
#define ctDFR_ADDKEY	1	/* deferred key add			*/
#define ctDFR_DELKEY	2	/* deferred key delete			*/
#define ctDFR_RWTKEY	3	/* deferred key rewrite			*/
#define ctDFR_RWTPKEY	4	/* deferred key partial rewrite		*/
#define ctDFR_LOADKEY	5	/* load index from data file records	*/
#define ctDFR_QUEUECB	6	/* invoke callback for all existing
				   data file records			*/
#define ctDFR_QUEUERC	7	/* convert records to current schema	*/

/* DFRKY status1 field attributes: */
#define ctDFR_TRANFRS	0x01	/* first deferred key operation in tran	*/
#define ctDFR_TRANCMT	0x02	/* transaction status: committed	*/
#define ctDFR_TRANABT	0x04	/* transaction status: aborted		*/
#define ctDFR_CBKONLY	0x08	/* operation is for callback only	*/
#define ctDFR_CBKEXS	0x10	/* record update callback exists	*/
#define ctDFR_CBKLOG	0x20	/* callback requires logging		*/
#define ctDFR_TRANLST	0x40	/* last deferred key operation in tran	*/
#define ctDFR_FLXREC	0x80	/* entry contains schema ID		*/

/* DFRKY status2 field attributes: */
#define ctDFR_LOADID	0x01	/* entry contains background load ID	*/

/*
** Record update callback operation codes. (Uses the same values as the
** deferred index operation codes.)
*/
#define ctRUCB_ADDREC	ctDFR_ADDKEY	/* record add			*/
#define ctRUCB_DELREC	ctDFR_DELKEY	/* record delete		*/
#define ctRUCB_RWTREC	ctDFR_RWTKEY	/* record rewrite		*/
#define ctRUCB_RWTPREC	ctDFR_RWTPKEY	/* partial record rewrite	*/

#define ctRUCB_CALLBACK_V1	1	/* original version of RUCB API */
#define ctRUCB_CALLBACK_V2	2	/* second version of RUCB API	*/
#define ctRUCB_CALLBACK_VERSION	ctRUCB_CALLBACK_V2

/*
** ctNotify controls options
*/
#define ctNT_CTL_STOP	1	/* stop notify			*/

/*
** ctNotify contents options
*/
#define ctNT_CON_UNQKEY	1	/* record buffer instead of key	*/
#define ctNT_CON_NODNAM	2	/* node name of actor		*/
#define ctNT_CON_RECBUF	4	/* record buffer [not on delete]*/


/*
** Index Range operators defined
*/
#define CTIX_not	0x0020		/* NOT => dual range	*/
#define CTIX_leq	0x0040		/* lower limit >=	*/
#define CTIX_ueq	0x0080		/* upper limit <=	*/
#define CTIX_msk	0x001f		/* ordinal mask		*/
#define CTIX_keepPos	0x0100		/* non-range index ops
					** allowed between NXTRNG /
					** PRVRNG calls
					*/
#define CTIX_SSG	0x0200		/* start segment group	*/
#define CTIX_ESG	0x0400		/* end segment group	*/

#define CTIX_SGopts	(CTIX_SSG | CTIX_ESG) /* segment group bits */

#define CTIX_EQi	0x0001
#define CTIX_GTi	0x0002
#define CTIX_GEi	0x0003
#define CTIX_LEi	0x0004
#define CTIX_LTi	0x0005
#define CTIX_NEi	0x0006
#define CTIX_BETi	0x0007	/* inclusive: (LL <= target <= UL)	*/
#define CTIX_BET_IEi	0x0008	/* mixed: (LL <= target < UL)		*/
#define CTIX_BET_EIi	0x0009	/* mixed: (LL < target <= UL)		*/
#define CTIX_BET_EEi	0x000a	/* exclusive: (LL < target < UL)	*/
#define CTIX_NOTBETi	0x000b	/* inclusive: not (LL <= target <= UL)	*/

/* All supported options: */
#define CTIX_ALLSUP	(CTIX_not | CTIX_leq | CTIX_ueq | CTIX_keepPos | \
			 CTIX_SGopts | CTIX_EQi | CTIX_GTi | CTIX_GEi | \
			 CTIX_LEi | CTIX_LTi | CTIX_NEi | CTIX_BETi | \
			 CTIX_BET_IEi | CTIX_BET_EIi | CTIX_BET_EEi | \
			 CTIX_NOTBETi)

#define CTIX_EQ		(CTIX_EQi	| CTIX_leq | CTIX_ueq)
#define CTIX_GT		(CTIX_GTi	| CTIX_ueq)
#define CTIX_GE		(CTIX_GEi	| CTIX_leq | CTIX_ueq)
#define CTIX_LE		(CTIX_LEi	| CTIX_leq | CTIX_ueq)
#define CTIX_LT		(CTIX_LTi	| CTIX_leq)
#define CTIX_NE		(CTIX_NEi	| CTIX_not)
#define CTIX_BET	(CTIX_BETi	| CTIX_leq | CTIX_ueq)
#define CTIX_BET_IE	(CTIX_BET_IEi	| CTIX_leq)
#define CTIX_BET_EI	(CTIX_BET_EIi	| CTIX_ueq)
#define CTIX_BET_EE	(CTIX_BET_EEi)
#define CTIX_NOTBET	(CTIX_NOTBETi	| CTIX_not)

/*
** File delete/rename options:
*/
#define ctFSflsdirmeta	0x00000001 /* flush directory metadata */
#define ctFSnonameconv	0x00000002 /* no filename conversion */

/*
** file system mode parameters
*/

/* the ctFScopy options may be combined: zero => abs copy, no directory ops */
#define ctFScopy_mkdir		0x00000001	/* make directory if necessary	    */
#define ctFScopy_new		0x00000002	/* do NOT overwrite existing file   */
#define ctFScopy_verify		0x00000004	/* compare src/dst after copy	    */

/* the ctFSpath options are mutually exclusive: zero is not allowed */
#define ctFSpath_file_exists	1	/* does file exist?		    */
#define ctFSpath_dir_exists	2	/* does directory exist?	    */
#define ctFSpath_mkdir		4	/* make directory		    */

#define ctFSpath_all		(				\
				ctFSpath_file_exists	||	\
				ctFSpath_dir_exists	||	\
				ctFSpath_mkdir			\
				)

/* ctchkcrepath mode parameters */
#define ctPATHchk 0
#define ctPATHcre 1


/*
** File mutex opcode options
*/
#define ctFILMTXrequest		1	/* acquire mutex		*/
#define ctFILMTXrelease		2	/* release mutex		*/
#define ctFILMTXrecursive	4	/* recursive request/release	*/
#define ctFILMTXcreate		8	/* create on acquisition if
					   necessary			*/
#define ctFILMTXdelete		16	/* delete file on release	*/
#define ctFILMTXnonpersistent	32	/* mutex will be released when
					   thread terminates [STPUSR],
					   but file will not be deleted	*/

#define ctFILMTXaction		(ctFILMTXrequest | ctFILMTXrelease)


/*
** File wildcard opcode options
*/
#define ctFILWCDfindfirst	1	/* start new search		*/
#define ctFILWCDfindnext	2	/* find next file		*/
#define ctFILWCDfindclose	4	/* terminate current search	*/


/*
** ctLOKLST: lock entry User description structure
*/
typedef struct lockid {
	LONG	ThrdID;			/* internal thread ID		*/
	TEXT	UserID[32];		/* logon ID [IDZ]		*/
	TEXT	NodeName[32];		/* optional network NodeName IDZ*/
	} LOCKID, * pLOCKID;

#define ctLastDeniedLock	(-999)	/* datno substitute for ctLOKLST*/


/*
** ctGetOpenFiles/ctGetFileUsers/ctGetFileLocks information structures
*/

typedef struct ctfilinfo {
	COUNT	filno;		/* system file number 			*/
	COUNT	status;		/* user count or user file number	*/
	TEXT	filtyp;		/* file type				*/
	TEXT	suptyp;		/* superfile type			*/
	TEXT	filnam[255];	/* file name				*/
} ctFILINF, ctMEM * pctFILINF;

typedef struct ctfilinfox {
	LONG	filno;		/* system file number 			*/
	LONG	status;		/* user count or user file number	*/
	TEXT	filtyp;		/* file type				*/
	TEXT	suptyp;		/* superfile type			*/
	TEXT	filnam[255];	/* file name				*/
} ctFILINFX, ctMEM * pctFILINFX;

/* file information structure formats: */
#define FILINF_ORIGINAL 1 /* original file info structure version (ctFILINF) */
#define FILINF_EXTENDED	2 /* new file info structure version (ctFILINFX) */

typedef struct ctusrinfo {
	NINT	taskid;		/* connection number			*/
	NINT	ufilno;		/* user file number			*/
	TEXT	usrnam[32];	/* user name				*/
} ctUSRINF, ctMEM * pctUSRINF;

#define ctLOKINFgetwaitlist	0x00000001

typedef struct ctwatinfo {
	NINT	loktyp;		/* lock type				*/
	NINT	taskid;		/* connection number			*/
	TEXT	usrnam[32];	/* user name				*/
} ctWATINF, ctMEM * pctWATINF;

typedef struct ctlokinfo {
	LONG8	recbyt;		/* offset of lock in file		*/
	NINT	loktyp;		/* lock type				*/
	NINT	taskid;		/* connection number			*/
	NINT	waitcnt;	/* number of waiters			*/
	TEXT	usrnam[32];	/* user name				*/
} ctLOKINF, ctMEM * pctLOKINF;


/*
** user supported compatibility options
*/
#define ctCompatUS_LogThru	((LONG) 0x0002000) /* transaction log
						      write-thru WIN32	      */
#define ctCompatUS_SYNC_LOG	((LONG) 0x0010000) /* transaction log
						      write-thru Unix	      */
#define ctCompatUS_FDATASYNC	((LONG)0x80000000) /* fdatasync vs fsync      */


/********************************************************/
/* Function Monitor Definitions 			*/
/* Function Name and Attributes structure definition 	*/
#define ctPFNAMES
#ifdef	ctPFNAMES

#define CTPF_NONE 		0	/* No special function monitor attr */
#define CTPF_HASOPENBLK		1	/* function parms has file name     */
#define CTPF_HASCREBLK		2	/* function parms has file name     */
#define CTPF_HASISAMBLK		3	/* function parms has file name     */
#define CTPF_HASIFIL		4	/* function parms has IFIL	    */
#define CTPF_HASSEPLNG		5	/* requires sub-function check	    */
#define CTPF_HASIFILtfilno	6	/* function parms has IFIL	    */
#define CTPF_HASIFILdfilno	7	/* function parms has IFIL	    */
#define CTPF_HASDATNO		8	/* function parms has a file num    */
#define CTPF_HASKEYNO		9	/* function parms has a file num    */
#define CTPF_HASFILNO		10	/* function parms has a file num    */
#define CTPF_HASNAME		11	/* function passed directly	    */

typedef struct {
	pTEXT   nam;		/* name of the function */
	NINT	typ;		/* Type indicator for function monitor */
	} CTPF_FNM;

#endif /* ctPFNAMES */
/********************************************************/

#ifdef ctPortMAC
#include "ctfun2.h"		/* Extra prototypes for strict compilers */
#endif

#define ctENCR	"0"
#define ctDES8	"1"
#define ctDES16	"2"
#define ctDES24	"3"
#define ctTWF16	"4"
#define ctTWF24	"5"
#define ctTWF32	"6"
#define ctRIJ16	"7" /* original AES implementation */
#define ctRIJ24	"8" /* original AES implementation */
#define ctRIJ32	"9" /* original AES implementation */
#define ctBLF8	"10"
#define ctBLF9	"11"
#define ctBLF10	"12"
#define ctBLF11	"13"
#define ctBLF12	"14"
#define ctBLF13	"15"
#define ctBLF14	"16"
#define ctBLF15	"17"
#define ctBLF16	"18"
#define ctBLF17	"19"
#define ctBLF18	"20"
#define ctBLF19	"21"
#define ctBLF20	"22"
#define ctBLF21	"23"
#define ctBLF22	"24"
#define ctBLF23	"25"
#define ctBLF24	"26"
#define ctBLF25	"27"
#define ctBLF26	"28"
#define ctBLF27	"29"
#define ctBLF28	"30"
#define ctBLF29	"31"
#define ctBLF30	"32"
#define ctBLF31	"33"
#define ctBLF32	"34"
#define ctBLF33	"35"
#define ctBLF34	"36"
#define ctBLF35	"37"
#define ctBLF36	"38"
#define ctBLF37	"39"
#define ctBLF38	"40"
#define ctBLF39	"41"
#define ctBLF40	"42"
#define ctBLF41	"43"
#define ctBLF42	"44"
#define ctBLF43	"45"
#define ctBLF44	"46"
#define ctBLF45	"47"
#define ctBLF46	"48"
#define ctBLF47	"49"
#define ctBLF48	"50"
#define ctBLF49	"51"
#define ctBLF50	"52"
#define ctBLF51	"53"
#define ctBLF52	"54"
#define ctBLF53	"55"
#define ctBLF54	"56"
#define ctBLF55	"57"
#define ctBLF56	"58"
#define ctENCRV "59" /* ctCAMOexample */
#define ctAES16	"60"
#define ctAES24	"61"
#define ctAES32	"62"
#define ctENCRCPY "98" /* copy encryption from datno */

/*
** keyval options for ctSETENCRYPT() call with mode of ctENCRCPY:
*/
#define ctENCRusrno	1 /* key holds user file number */
#define ctENCRsysno	2 /* key holds system file number */

#ifdef PROTOTYPE
typedef VOID (*ctexitfnc_t)(NINT, NINT);
#else
typedef VOID (*ctexitfnc_t)();
#endif

/*
** expression parser limits
*/

/* maximum length of a quoted string: see Quote2Text() in ctscan.c */
#define CNDX_MAX_TEXT		255

/* maximum expression stack size */
#define CNDX_MAX_STACK		1024

/* maximum token and pushback buffer size */
#define CNDX_MAX_TOKEN		8192

#ifdef ctThrds
#if defined(ctPortSOLARIS) || defined(ctPortRS6000) || defined(ctPortHPUX11) \
 || defined(ctPortLINUX) || defined(ctPortMACOSX) || defined(ctPortSCO5) \
 || defined(ctPortALPHA)

/* Use thread-safe localtime(), gmtime(), and asctime() functions. */
#define ctLOCALTIME_R

#endif
#endif /* ctThrds */

#define CTAPVRnewfcuser	11	/* we support new FC_USER structure */
#define CTAPVRdarflag	12	/* extended attribute bit indicates **
				** if DAR has been disabled	    */

#define CTSVVRnewfcuser	 8	/* we support new FC_USER structure */
#define CTSVVRadminsec	 9	/* enhanced ADMIN security */
#define CTSVVRdarflag	10	/* extended attribute bit indicates **
				** if DAR has been disabled	    */
#define CTSVVRrec_conv	11	/* supports server-side record	    **
				** image conversion		    */

#define DYNAMIC_DUMP_DEFER_MAX	5000 /* Maximum DYNAMIC_DUMP_DEFER time (msec) */
#define DYNAMIC_DUMP_DEFER_INTERVAL_MAX	5000 /* Maximum DYNAMIC_DUMP_DEFER_INTERVAL */

/*
** ctTransferFile mode bits
*/
#define ctXFRFIL_SEND	0x00000001	/* send file to server		*/
#define ctXFRFIL_RECV	0x00000002	/* receive file from server	*/

#define ctXFRFIL_RAW	0x00000004	/* raw file transfer		*/
#define ctXFRFIL_CTREE	0x00000008	/* c-tree file transfer		*/

#define ctXFRFIL_OVRWRT	0x00000010	/* overwrite existing file	*/

#define ctXFRFIL_MASTER	0x00000020	/* perform transfer with master	*/

#define ctXFRFIL_CLBK	0x00000040	/* use callback function	*/
#define ctXFRFIL_CREDIR 0x00000080	/* Create non-existant directories */
#define ctXFRFIL_CPYFIL 0x00000100	/* used for remote file copy	*/

/* All supported modes for version 1 of XFRFIL structure: */
#define ctXFRFIL_MODES_V01 (ctXFRFIL_SEND|ctXFRFIL_RECV|ctXFRFIL_RAW|ctXFRFIL_CTREE|ctXFRFIL_OVRWRT|ctXFRFIL_MASTER|ctXFRFIL_CLBK|ctXFRFIL_CREDIR)

/* All supported modes for version 2 of XFRFIL structure: */
#define ctXFRFIL_MODES_V02 (ctXFRFIL_MODES_V01|ctXFRFIL_CPYFIL)

/*
** ctTransferFile limits
*/
#define XFR_MIN_BLKSIZ	4096		/* 4 KB minimum block size	*/
#define XFR_MAX_BLKSIZ	1024*1024*1024	/* 1 GB maximum block size	*/

typedef struct ctxfrfil ctMEM * pctXFRFIL;

/*
** File transfer callback function prototype.
*/
#ifdef PROTOTYPE
typedef NINT (*pXFRFNC)(pctXFRFIL pxfr, pTEXT buf, pNINT plen);
#else
typedef NINT (*pXFRFNC)();
#endif

/*
** Additional file transfer information passed to callback function.
*/
typedef struct xfrinf_t {
	NINT	 ownr;	/* Task ID of client connection			*/
	NINT	 wqid;	/* ID of queue written by new thread		*/
	NINT	 rqid;	/* ID of queue read by new thread		*/
	pctXFRFIL pxfr;	/* Pointer to file transfer input parameters	*/
} XFRINF, *pXFRINF;

/*
** ctTransferFile parameters, version 1
*/
typedef struct ctxfrfil01 {
	LONG	ver;	/* Version of this structure	*/
	LONG	mode;	/* Transfer mode		*/
	pTEXT	srcnam;	/* Name of source file		*/
	pTEXT	dstnam;	/* Name of destination file	*/
	LONG	blksiz;	/* Transfer block size		*/
	LONG	ackint;	/* Acknowledgement interval	*/
	pXFRFNC	xfrfnc;	/* File transfer callback func	*/
	pXFRINF	xfrinf;	/* File transfer callback data	*/
} ctXFRFIL01;

/*
** ctTransferFile parameters
*/
typedef struct ctxfrfil {
	LONG	ver;	/* Version of this structure	*/
	LONG	mode;	/* Transfer mode		*/
	pTEXT	srcnam;	/* Name of source file		*/
	pTEXT	dstnam;	/* Name of destination file	*/
	LONG	blksiz;	/* Transfer block size		*/
	LONG	ackint;	/* Acknowledgement interval	*/
	pXFRFNC	xfrfnc;	/* File transfer callback func	*/
	pXFRINF	xfrinf;	/* File transfer callback data	*/
	pVOID	xfrufn; /* File transfer user callback	*/
	pVOID	xfrudt; /* File transfer user data	*/
} ctXFRFIL;

/*
** ctTransferFile parameter structure versions
*/
#define ctXFRFIL_VERS_V01 1		/* initial version of structure */
#define ctXFRFIL_VERS_V02 2		/* version of structure with callback */

#define ctXFRFIL_VERS_CUR ctXFRFIL_VERS_V02	/* current version */

/*
** Sequence number support definitions
*/

#define ctSEQcreate	1	/* ctCreateSequence function		*/
#define ctSEQdelete	2	/* ctDeleteSequence function		*/
#define ctSEQopen	3	/* ctOpenSequence function		*/
#define ctSEQclose	4	/* ctCloseSequence function		*/
#define ctSEQgetattr	5	/* ctGetSequenceAttrs function		*/
#define ctSEQsetattr	6	/* ctSetSequenceAttrs function		*/
#define ctSEQgetcurval	7	/* ctGetCurrentSequenceValue function	*/
#define ctSEQsetcurval	8	/* ctSetCurrentSequenceValue function	*/
#define ctSEQgetnxtval	9	/* ctGetNextSequenceValue function	*/

/* Name of the sequence files. */
#define SEQDATNAM "SEQUENCEDT.FCS"
#define SEQIDXNAM "SEQUENCEIX.FCS"

#define MAX_SEQ_NAME_LEN 32 /* maximum length of sequence name */

#define ctSEQINC	0x01	/* incrementing sequence */
#define ctSEQDEC	0x02	/* decrementing sequence */
#define ctSEQCYC	0x04	/* cycling sequence */
#define ctSEQTRM	0x08	/* terminating sequence */
#define ctSEQLIM	0x10	/* sequence has a limit */
#define ctSEQTRNDEP	0x20	/* sequence create and delete are committed
				at transaction commit time rather than
				immediately committing */
#define ctSEQCURFRS	0x40	/* Use the current value set on sequence create
				as the starting sequence value. Requires a call
				to get the next value before a call to read the
				current value. */

/* All supported options: */
#define ctSEQ_ALLSUP (ctSEQINC | ctSEQDEC | ctSEQCYC | ctSEQTRM | ctSEQLIM | ctSEQTRNDEP | ctSEQCURFRS)

/* Sequence file on-disk format: */
typedef struct ctseqattrdsk {
	LONG8	seqdel; /* delete flag/structure padding */
	LONG8	seqini; /* initial sequence value */
	LONG8	seqcur; /* current sequence value */
	LONG8	seqinc; /* sequence increment or decrement amount (always positive) */
	LONG8	seqlim; /* sequence limit */
	LONG	seqtyp; /* sequence type: incrementing or decrementing and cycling or terminating */
	TEXT	sequnk; /* non-zero indicates current sequence value is unknown */
	TEXT	seqnam[MAX_SEQ_NAME_LEN+1]; /* sequence name */
	TEXT	seqpad[2];
} ctSEQATTRD, ctMEM * pctSEQATTRD;

/* Size of sequence data record, file format 2 */
#define SEQRECLEN_V2 sizeof(ctSEQATTRD)

/* Size of data from seqini through seqlim. */
#define SEQCPYLEN (SegOff(ctSEQATTRD,seqtyp) - SegOff(ctSEQATTRD,seqini))

/* Size of data from sequnk through seqnam. */
#define SEQCPYLEN2 (SegOff(ctSEQATTRD,seqpad) - SegOff(ctSEQATTRD,sequnk))

typedef struct ctseqattr {
	LONG8	seqini; /* initial sequence value */
	LONG8	seqcur; /* current sequence value */
	LONG8	seqinc; /* sequence increment or decrement amount (always positive) */
	LONG8	seqlim; /* sequence limit */
	TEXT	seqtyp; /* sequence type: incrementing or decrementing and cycling or terminating */
	TEXT	sequnk; /* non-zero indicates current sequence value is unknown */
	TEXT	seqnam[MAX_SEQ_NAME_LEN+1]; /* sequence name */
	TEXT	seqpad;
} ctSEQATTR, ctMEM * pctSEQATTR;

/* Size of fixed-length ctSEQATTR data passed to server */
#define SEQFIXLEN (4 * sizeof(LONG8) + 2 * sizeof(TEXT))

/* Size of sequence data record */
#define SEQRECLEN (SEQFIXLEN + MAX_SEQ_NAME_LEN + 1)

/*
** ctVERIFYidx parameter structure versions
*/
#define ctVFYIDX_VERS_V01 1		/* initial version of structure */
#define ctVFYIDX_VERS_V02 2		/*
					**  initial version of input structure 
					**  +2nd version of output structure
					*/


/* maximum number of levels in tree for index verify structure */
#ifdef MAXLEV
#define VFYLEV	MAXLEV
#else
#define VFYLEV	15
#endif

/* ctVERIFYidx actions */
#define ctVFYIDXdelstk	0x00000001	/* check delete stack		*/
#define ctVFYIDXlink	0x00000002	/* check links			*/
#define ctVFYIDXleaf	0x00000004	/* check leaf nodes		*/
#define ctVFYIDXchkkey	0x00000008	/* check keys in leaf nodes	*/
#define ctVFYIDXstart	0x00000010	/* indicates start of operation	*/
#define ctVFYIDXend	0x00000020	/* indicates end of operation	*/
#define ctVFYIDXspace   0x00000040	/* analyze space usage. physical index only */



#define ctVFYIDXmessageCB	0x00000001 /* message callback code	*/
#define ctVFYIDXprogressCB	0x00000002 /* progress callback code	*/
/*				0x00000004 used by ctVFYFILerrorCB	*/
#define ctVFYIDXfunction	0x00000008 /* called from ctVERIFYidx	*/
#define ctVFYIDXutilityBehav	0x00000010 /* make the callbacks behave
					   ** as required by the ctvfyidx
					   ** utility			*/

/* Number of 4-byte input fields passed to server that are byte order sensitive */

/*
** NOTE: we pass the callback function addresses to the server but the server
** only checks if they are non-zero, so there is no need to reverse them.
*/

/* function prototype for index verify message callback function */
typedef ctCONV NINT (*pVFYMSGCBFNC)(pTEXT);

/* function prototype for index verify progress callback function */
typedef ctCONV NINT (*pVFYPRGCBFNC)(TEXT opcode, TEXT pct);

typedef struct vfyfilerrinf {
	LONG	verson;		/* version of this structure		*/
	LONG	errcod;		/* c-tree error code			*/
	LONG	syscod;		/* system error code			*/
} ctVFERRINF, *pctVFERRINF;

/* function prototype for file verify error callback function */
typedef ctCONV NINT (*pVFYERRCBFNC)(pctVFERRINF perrinfo, pTEXT msg);

/* ctVERIFYidx input parameters */
typedef struct ctvfyidxin {
	LONG	verson;		 /* version of this structure		*/
	LONG	action;		 /* which operations to perform		*/
	LONG	maxnod;		 /* maximum node counts	in output buf	*/
	TEXT	flags;		 /* options to pass to server		*/
	TEXT	pad[3];		 /* padding				*/
	pVFYMSGCBFNC
		fnmessage;	 /* optional message callback function	*/
	pVFYPRGCBFNC
		fnprogress;	 /* optional progress callback func	*/
} ctVFYIDXin, *pctVFYIDXin;

/* Size of input structure to pass to server */
#define ctVFYIDXinsize_V01 (SegOff(struct ctvfyidxin,pad)) /* version 1 */

/* Number of output fields before snodcnt in output parameter structure */
#define ctVFYIDXfixedoutflds_V01 6 /* for output structure version 1	*/
#define ctVFYIDXfixedoutflds_V02 7 /* for output structure version 2	*/

/* ctReplGetNextChange() client callback flags field bits: */
#define ctRCHkeepaliveCB	0x00000001 /* send keepalivecallback	*/

#define INVALID_FILNO -1
/*
** ctVerifyFile parameter structure versions
*/
#define ctVFYFIL_VERS_V01 1		/* initial version of structure */

/* ctVerifyFile actions */
#define ctVFopenExclusive	0x00000001	/* Open the files in exclusive
						** mode.		     */
#define ctVFchkDataOnly		0x00000002	/* Read data file in physical
						** order, not checking keys. */
#define ctVFchkDataWithKeys	0x00000004	/* Read data file in physical
						** order and check the keys. */
#define ctVFchkIndexOnly	0x00000008	/* Read index file in key order
						** and don't check record.   */
#define ctVFchkIndexWithRecord	0x00000010	/* Read index file in key order
						** and check keys in record. */
#define ctVFchkDeletedSpace	0x00000020	/* Check that all entries on
						the delete stack or in the space
						management index are valid. */

#define ctVFYFILall	(ctVFopenExclusive | ctVFchkDataOnly | \
			 ctVFchkDataWithKeys | ctVFchkIndexOnly | \
			 ctVFchkIndexWithRecord | ctVFchkDeletedSpace)

#define ctVFYFILmessageCB	0x00000001 /* message callback code	*/
#define ctVFYFILprogressCB	0x00000002 /* progress callback code	*/
#define ctVFYFILerrorCB		0x00000004 /* error callback code	*/
/*				0x00000008 used by ctVFYIDXfunction	*/
/*				0x00000010 used by ctVFYIDXutilityBehav */

/* ctVerifyFile parameters */
typedef struct ctvfyfil {
/* input parameters: */
	LONG	verson;		/* Version of this structure.		 */
	LONG	options;	/* Which operations to perform.		 */
	LONG	errbufsiz;	/* Size of optional error message buffer.*/
	LONG	chkkey;		/* Index files to check (0=all, 1=first
				** index in IFIL, 2=second index, etc).  */
	pTEXT	datnam;		/* Name of data file to check.		 */
	pTEXT	fileword;	/* Optional data file password.		 */
	pVFYMSGCBFNC
		fnmessage;	/* Optional message callback function.	 */
	pVFYPRGCBFNC
		fnprogress;	/* Optional progress callback function.	 */
	pVFYERRCBFNC
		fnerror;	/* Optional progress callback function.  */
	pTEXT	errbuf;		/* Optional error message buffer.	 */
/* We can add output parameters here if needed. */
} ctVFYFIL, *pctVFYFIL;

/* Size of input structure to pass to server */
#define ctVFYFILinsize_V01 (SegOff(struct ctvfyfil,datnam)) /* version 1 input size */
#define ctVFYFILoutsize_V01 (0) /* version 1 output size */

/* File verify progress opcodes. We use negative values so that ctVERIFYstatus()
** can distinguish the file verify progress opcodes from the index verify
** progress opcodes (ctVFYIDXdelstk, etc.). */
#define ctVFYFILdataStart	-1	/* Data scan starting		     */
#define ctVFYFILdataPct		-2	/* Reporting data scan pct complete  */
#define ctVFYFILdataEnd		-3	/* Data scan ending		     */
#define ctVFYFILindexStart	-4	/* Index scan starting		     */
#define ctVFYFILindexPct	-5	/* Reporting index scan pct complete */
#define ctVFYFILindexEnd	-6	/* Index scan ending		     */
#define ctVFYFILspaceStart	-7	/* Deleted space scan starting	     */
#define ctVFYFILspacePct	-8	/* Reporting delete space scan pct complete */
#define ctVFYFILspaceEnd	-9	/* Deleted space scan ending	     */


#define ctRTGmessageCB		0x00000001 /* message callback code	*/

/* function prototype for RTG message callback function */
#ifdef PROTOTYPE
typedef ctCONV NINT (*pRTGMSGCBFNC)(pTEXT);
#else
typedef ctCONV NINT (*pRTGMSGCBFNC)();
#endif

typedef pVOID  FCPHND;	 /* file copy handle			*/
typedef ppVOID pFCPHND;  /* pointer to file copy handle		*/
typedef pVOID  FCPOPR;	 /* file copy operation			*/
typedef ppVOID pFCPOPR;  /* pointer to file copy operation	*/

typedef struct cpyfil ctMEM * pCPYFIL;

/* File copy callback function data. */
typedef struct cpystt {
	pCPYFIL	pcpyfil; /* options passed to file copy function	*/
	pTEXT	filnam;	 /* name of the source file being copied	*/
	COUNT	val;	 /* percent complete or error code		*/
	TEXT	opcode;  /* operation code				*/
} CPYSTT, *pCPYSTT;

/* File copy callback function prototype. */
typedef NINT (*pCPYFNC)(pCPYSTT pcpystt);

#define ctCPYFILprogressCB	0x00000001 /* progress callback code	*/

/* File copy callback function opcodes. */
#define ctCPYCBKbeginfile	1	/* start file copy	*/
#define ctCPYCBKprogfile	2	/* file copy progress	*/
#define ctCPYCBKendfile		3	/* end file copy	*/
#define ctCPYCBKvrfyfile	4	/* file verify progress */

/* File copy option values. */
#define ctCFisam	  0x00000001 /* copy ISAM data and index	*/
#define ctCFlowlevel	  0x00000002 /* copy only specified file	*/
#define ctCFtoDir	  0x00000004 /* copy to specified directory	*/
#define ctCFtoName	  0x00000008 /* copy to specified file names	*/
#define ctCFifexistDelete 0x00000010 /* delete existing dest file	*/
#define ctCFcreateDirs	  0x00000020 /* create dest directories		*/ 
#define ctCFiferrorKeep	  0x00000040 /* keep all successfully-copied files
                                        if a subsequent file fails to be
					copied				*/
#define ctCFtoServer	  0x00000080 /* copy to remote server		*/
#define ctCFverify	  0x00000100 /* compare src/dst files after copy*/
#define ctCFskipIfilUpdate 0x00000200 /* skip Ifil Update		*/
#define ctCFallowSharedOpen 0x00000400 /* try opening file in shared mode if exclusive open fails */

#define ctCF_UNUSED 0xfffff800 /* unused cpoptions bits; update this as we use new bits */

#define MAXFNAME 255

/* File name structure. */
typedef struct ctfnam {
	TEXT	name[MAXFNAME];	/* Directory or file name.		*/
} CTFNAM, *pCTFNAM;

/*
** File copy server parameters.
*/

#define SRVPRM_VERS_V01	1	/* initial version of structure	*/

#define SRVPRM_VERS_CUR	SRVPRM_VERS_V01	/* current version */

typedef struct srvprm {
	NINT	versn;		/* Structure version			*/
	TEXT	userid[32];	/* User id [IDZ]			*/
	TEXT	userword[64];	/* User password [PWZX]			*/
	TEXT	servname[256];	/* Server name [FNZ]			*/
} SRVPRM, ctMEM * pSRVPRM;

/*
** File copy parameters.
*/

#define CPYPRM_VERS_V01	1	/* initial version of structure	*/

#define CPYPRM_VERS_CUR	CPYPRM_VERS_V01	/* current version */

/* Length of fixed length fields in CPYPRM structure */
#define CPYPRM_FIXED_LEN 4 * sizeof(LONG)

typedef struct ctcpyprm {
	LONG	versn;		/* Structure version			*/
	ULONG	cpoptions;	/* File copy options			*/
	ULONG	fboptions;	/* File block options			*/
	LONG	filnamcnt;	/* Number of file names			*/
	TEXT	fileword[10];	/* File password			*/
	SRVPRM	srvprm;		/* Server parameters			*/
	pCTFNAM srcfilnam;	/* Source file names			*/
	pCTFNAM	dstfilnam;	/* Destination directory or file names	*/
	FCPHND  fcphnd;		/* The associated file copy handle	*/
} CPYPRM, ctMEM * pCPYPRM, ctMEM ** ppCPYPRM;

/*
** File copy function call structure.
*/

#define CPYFIL_VERS_V01	1	/* initial version of structure	*/

#define CPYFIL_VERS_CUR	CPYFIL_VERS_V01	/* current version */

/* Length of fixed length fields in CPYPRM structure */
#define CPYFIL_FIXED_LEN 3 * sizeof(LONG)

typedef struct cpyfil {
	LONG	versn;		/* Structure version			*/
	LONG	ncpyprm;	/* Number of file copy parameter structs*/
	LONG	errbufsiz;	/* Size of optional error message buffer*/
	LONG	reserved;	/* Reserved for future use		*/
	pCPYPRM	pcpyprm;	/* File copy parameter structures	*/
	pCPYFNC	pcpyfnc;	/* Callback function			*/
	pVOID	pusrdata;	/* User data pointer			*/
	pTEXT	errbuf;		/* Optional error message buffer	*/
} CPYFIL;

typedef struct ifcpoplst *pFCPOPS;
typedef struct ifcpoplst {
	pCPYPRM item;
	pFCPOPS next;
	pFCPOPS prev;
} FCPOPS;

typedef struct ifcphnd {
	CPYFIL	cpyfil;
	pFCPOPS	pcpyops;
} FCPINF, *pFCPINF;

/* Client callback state information. */
typedef struct ccbst {
	NINT	bufsiz; /* size of data buffer		*/
	NINT	offset;	/* current offset in buffer	*/
} CCBST, *pCCBST;

/* function prototype for dynamic dump stream callback function */
#ifdef PROTOTYPE
typedef ctCONV NINT (*pDYNDMPCBFNC)(pVOID pctx,pVOID pdata,NINT datalen,NINT opcode);
#else
typedef ctCONV NINT (*pDYNDMPCBFNC)();
#endif

/* Dynamic dump options for client use: */

/* The DDOPT_RECVSTREAM and DDOPT_RECVSTATUS options can be used together or
** separately. When using these options, you must also set a callback function
** that receives the dump stream data and/or status messages from the server.
** Also optionally set a context pointer that you can use to maintain any
** state variables that your callback needs, and optionally set the size of
** the communication buffer. */

#define DDOPT_SENDSCRIPT	1 /* Send dump script to server		   */
#define DDOPT_RECVSTREAM	2 /* Receive dump stream from server	   */
#define DDOPT_RECVSTATUS	3 /* Receive status messages from server   */
#define DDOPT_SETCALLBK		4 /* Set callback function		   */
#define DDOPT_SETCONTEXT	5 /* Set callback function context pointer */
#define DDOPT_SETBUFSIZ		6 /* Set communication buffer size	   */

/* Dynamic dump callback opcodes */
#define ctDDCBKstream		0x00000001	/* dump stream data message*/
#define ctDDCBKstatus		0x00000002	/* dump status message	   */

/* Dynamic dump internal mode bits */
#define DDMD_SENDSCRIPT		0x00000001	/* client sending script   */
#define DDMD_RECVSTREAM		0x00000002	/* client receiving dump   */
#define DDMD_RECVSTATUS		0x00000004	/* client receiving status */

#define DDMD_ALLOPTIONS		(DDMD_SENDSCRIPT|DDMD_RECVSTREAM|DDMD_RECVSTATUS)

/*
** Dynamic dump statistic callback function structure.
*/
#define DDST_VERS_V01	1	/* initial version of structure	*/

#define DDST_VERS_CUR	DDST_VERS_V01	/* current version */

typedef struct ddstat {
	LONG	versn;		/* version of structure			*/
	COUNT	phase;		/* current dump phase			*/
	COUNT	errcod;		/* error code				*/
	LONG8	size;		/* total or current dump or file size	*/
	TEXT	filnam[256];	/* name of file being dumped		*/
} DDST, *pDDST;

/* dynamic dump phases */
#define DDP_BEGINDUMP 	1	/* begin dynamic dump			*/
#define DDP_BEGINFILE	2	/* begin dump of file			*/
#define DDP_PROGFILE	3	/* file progress notification		*/
#define DDP_ENDFILE	4	/* end dump of file			*/
#define DDP_ENDDUMP	5	/* end dynamic dump			*/
#define DDP_ERROR	6	/* dynamic dump unexpected error	*/
#define DDP_ERRFILE	7	/* dynamic dump error at file open	*/

/* dynamic dump immediate restore phases */
#define DDP_BEGINRESTORE 8	/* begin dynamic dump restore		*/
#define DDP_ENDRESTORE	 9	/* end dynamic dump restore		*/
#define DDP_BEGINROLBAK	10	/* begin rollback of files to dump start*/
#define DDP_ENDROLBAK	11	/* end rollback of files to dump start  */
#define DDP_BEGINCLNIDX	12	/* begin cleaning of index marks	*/
#define DDP_ENDCLNIDX	13	/* end cleaning of index marks		*/
#define DDP_BEGINUPDIFL	14	/* begin updating IFIL resources	*/
#define DDP_ENDUPDIFL	15	/* end updating IFIL resources		*/

/*
** ctDeferredIndexControl function call structure.
*/
#define DFKCTL_VERS_V01	1	/* initial version of structure	*/

#define DFKCTL_VERS_CUR	DFKCTL_VERS_V01	/* current version */

/* Size of input structure to pass to server */
#define DFKCTLinsize_V01  SegOff(DFKCTL,bufptr) /* version 1 input size */
#define DFKCTLoutsize_V01 (0) /* version 1 output size */

typedef struct dfkctl {
	COUNT	verson;	/* version of this structure	*/
	COUNT	opcode;	/* operation code		*/
	LONG	bufsiz;	/* buffer size			*/
	pVOID	bufptr;	/* input/output buffer		*/
#ifndef ct8P
	LONG	pad;
#endif
} DFKCTL, *pDFKCTL;

#define DFKSCB_VERS_V01	1	/* initial version of structure	*/

#define DFKSCB_VERS_CUR	DFKSCB_VERS_V01	/* current version */

/* fixed length size of DFKCTLsetcallback data when using 2-byte file numbers */
#define DFKSCB_FIXED_LEN (2 * sizeof(COUNT) + sizeof(LONG))
/* fixed length size of DFKCTLsetcallback data when using 4-byte file numbers */
#define DFKSCB4_FIXED_LEN (sizeof(COUNT) + 2 + sizeof(FILNO))

/* client side fixed length size of DFKCTLsetcallback data */
#ifdef ctFeatMAXFILE32
#define DFKSCB_FIXED_LEN_CS	DFKSCB4_FIXED_LEN
#else
#define DFKSCB_FIXED_LEN_CS	DFKSCB_FIXED_LEN
#endif

/* Size of input structure to pass to server */
#define DFKSCBinsize_V01  sizeof(DFKSCB) /* version 1 input size */
#define DFKSCBoutsize_V01 (0) /* version 1 output size */

/* Input buffer format for DFKCTLsetcallback opcode. */
typedef struct dfkscb {
	COUNT	verson;	/* Version of this structure	*/
#ifdef ctFeatMAXFILE32
	COUNT	pad;	/* Unused padding bytes		*/
	FILNO	datno;	/* Data file number		*/
#else
	COUNT	datno;	/* Data file number		*/
	TEXT	pad[4];	/* Unused padding bytes		*/
#endif
	pTEXT	datnam;	/* Data file name		*/
	pTEXT	dllname;/* Name of callback DLL		*/
	pTEXT	params;	/* Optional parameters		*/
} DFKSCB, *pDFKSCB;

#define DFKGCB_VERS_V01	1	/* initial version of structure	*/

#define DFKGCB_VERS_CUR	DFKGCB_VERS_V01	/* current version */

/* fixed length size of DFKCTLgetcallback data when using 2-byte file numbers */
#define DFKGCB_FIXED_LEN (2 * sizeof(COUNT) + sizeof(LONG))
/* fixed length size of DFKCTLgetcallback data when using 4-byte file numbers */
#define DFKGCB4_FIXED_LEN (sizeof(COUNT) + 6 + sizeof(FILNO) + sizeof(LONG))

/* client side fixed length size of DFKCTLgetcallback data */
#ifdef ctFeatMAXFILE32
#define DFKGCB_FIXED_LEN_CS	DFKGCB4_FIXED_LEN
#else
#define DFKGCB_FIXED_LEN_CS	DFKGCB_FIXED_LEN
#endif

/* Size of input structure to pass to server */
#define DFKGCBinsize_V01  sizeof(DFKGCB) /* version 1 input size */
#define DFKGCBoutsize_V01 (0) /* version 1 output size */

/* Input/output buffer format for DFKCTLgetcallback opcode. */
typedef struct dfkgcb {
	COUNT	verson;	/* Version of this structure	*/
#ifdef ctFeatMAXFILE32
	TEXT	pad[6];	/* Unused padding bytes		*/
	FILNO	datno;	/* Data file number		*/
#else
	COUNT	datno;	/* Data file number		*/
#endif
	LONG	bufsiz;	/* Output buffer size		*/
	pTEXT	datnam;	/* Data file name		*/
	pTEXT	outbuf;	/* Output buffer		*/
} DFKGCB, *pDFKGCB;

#define DFKQIL_VERS_V01	1	/* initial version of structure	*/
#define DFKQIL_VERS_V02	2	/* second version of structure	*/

#define DFKQIL_VERS_CUR	DFKQIL_VERS_V02	/* current version */

/* fixed length size of DFKCTLqueueload data when using 2-byte file numbers */
#define DFKQIL_FIXED_LEN (2 * sizeof(COUNT) + sizeof(LONG))
/* fixed length size of DFKCTLqueueload data when using 4-byte file numbers */
#define DFKQIL4_FIXED_LEN (sizeof(COUNT) + 6 + sizeof(FILNO) + sizeof(LONG))

/* client side fixed length size of DFKCTLqueueload data */
#ifdef ctFeatMAXFILE32
#define DFKQIL_FIXED_LEN_CS	DFKQIL4_FIXED_LEN
#else
#define DFKQIL_FIXED_LEN_CS	DFKQIL_FIXED_LEN
#endif

/* Size of input structure to pass to server, verson 1 */
#define DFKQILinsize_V01  sizeof(DFKQIL) /* version 1 input size */
#define DFKQILoutsize_V01 (0) /* version 1 output size */

/* Input buffer format for DFKCTLqueueload opcode, version 1. */
typedef struct dfkqil01 {
	COUNT	verson;	/* Version of this structure	*/
#ifdef ctFeatMAXFILE32
	TEXT	pad[6];	/* Unused padding bytes		*/
	FILNO	datno;	/* Data file number		*/
#else
	COUNT	datno;	/* Data file number		*/
#endif
	LONG	numidx;	/* Number of indices to load	*/
	pLONG	idxlst;	/* List of index file numbers	*/
} DFKQIL01, *pDFKQIL01;

/* Size of input structure to pass to server, version 2 */
#define DFKQILinsize_V02  sizeof(DFKQIL) /* version 2 input size */
#define DFKQILoutsize_V02 (0) /* version 2 output size */

/* Input buffer format for DFKCTLqueueload opcode, version 2. */
typedef struct dfkqil {
	COUNT	verson;	/* Version of this structure	*/
#ifdef ctFeatMAXFILE32
	TEXT	pad[6];	/* Unused padding bytes		*/
	FILNO	datno;	/* Data file number		*/
#else
	COUNT	datno;	/* Data file number		*/
#endif
	LONG	numidx;	/* Number of indices to load	*/
	pLONG	idxlst;	/* List of index file numbers	*/
	pTEXT	loadid;	/* Background load identifier	*/
} DFKQIL, *pDFKQIL;

#define DFKQRC_VERS_V01	1	/* initial version of structure	*/

#define DFKQRC_VERS_CUR	DFKQRC_VERS_V01	/* current version */

/* fixed length size of DFKCTLqueuerecconv data when using 2-byte file numbers */
#define DFKQRC_FIXED_LEN (2 * sizeof(COUNT))
/* fixed length size of DFKCTLqueuerecconv data when using 4-byte file numbers */
#define DFKQRC4_FIXED_LEN (sizeof(COUNT) + 2 + sizeof(FILNO))

/* client side fixed length size of DFKCTLqueuerecconv data */
#ifdef ctFeatMAXFILE32
#define DFKQRC_FIXED_LEN_CS	DFKQRC4_FIXED_LEN
#else
#define DFKQRC_FIXED_LEN_CS	DFKQRC_FIXED_LEN
#endif

/* Size of input structure to pass to server, verson 1 */
#define DFKQRCinsize_V01  sizeof(DFKQRC) /* version 1 input size */
#define DFKQRCoutsize_V01 (0) /* version 1 output size */

/* Input buffer format for DFKCTLqueuerecconv opcode, version 1. */
typedef struct dfkqrc {
	COUNT	verson;	/* Version of this structure	*/
#ifdef ctFeatMAXFILE32
	COUNT	pad;	/* pad for alignment		*/
	FILNO	datno;	/* Data file number		*/
#else
	COUNT	datno;	/* Data file number		*/
	LONG	pad;	/* pad for alignment		*/
#endif
	pTEXT	loadid;	/* Background load identifier	*/
} DFKQRC, *pDFKQRC;

/* opcode values */
#define	DFKCTLclearstats	1	/* Clear deferred index stats	*/
#define	DFKCTLgetstats		2	/* Retrieve deferred index stats */
#define	DFKCTLgetstate		3	/* Retrieve deferred index thread state */
#define	DFKCTLgetblstate	4	/* Retrieve background index load thread state */
#define	DFKCTLpausethrds	5	/* Pause deferred index thrds	*/
#define	DFKCTLresumethrds	6	/* Resume deferred index thrds	*/
#define	DFKCTLsetcallback	7	/* Set callback DLL		*/
#define	DFKCTLgetcallback	8	/* Get callback settings	*/
#define	DFKCTLqueueload		9	/* Queue index load		*/
#define	DFKCTLqueuerecconv	10	/* Queue conversion of records to the
					current schema definition */

typedef enum dfrkop {
	DFRKOPnone		= 0,	/* uninitialized value		*/
	DFRKOPstarting		= 1,	/* initializing			*/
	DFRKOPreadnextop	= 2,	/* reading next operation	*/
	DFRKOPperformop		= 3,	/* performing operation		*/
	DFRKOPoprcallback	= 4,	/* callback for performing operation */
	DFRKOPerrcallback	= 5,	/* callback when performing operation fails */
	DFRKOPopnfil		= 6,	/* opening file			*/
	DFRKOPclsfil		= 7,	/* closing file			*/
	DFRKOPbegintran		= 8,	/* starting transaction		*/
	DFRKOPrestore		= 9,	/* restoring to savepoint	*/
	DFRKOPcommit		= 10,	/* committing transaction	*/
	DFRKOPpaused		= 11,	/* paused			*/
	DFRKOPstopping		= 12,	/* shutting down		*/
	DFRKOPscanning		= 13,	/* scanning data file		*/
	DFRKOPlocking		= 14,	/* requesting lock		*/
	DFRKOPquiesced		= 15,	/* suspended by ctQUIET		*/
	DFRKOPidle		= 16	/* idle				*/
} DFRKOP;

/* deferred indexing statistics */
#define DFKSTTvern	1	/* DFKSTT (deferred indexing stats) version #	*/
typedef struct dfkstt {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	LONG8	tstamp;		/* Time stamp: seconds since 70		*/
	LONG8	opnok;		/* Successful file opens		*/
	LONG8	addok;		/* Successful adds			*/
	LONG8	delok;		/* Successful deletes			*/
	LONG8	rwtok;		/* Successful updates			*/
	LONG8	opnerr;		/* Failed file opens			*/
	LONG8	adderr;		/* Failed adds				*/
	LONG8	delerr;		/* Failed deletes			*/
	LONG8	rwterr;		/* Failed updates			*/
	LONG8	addskp;		/* Skipped adds				*/
	LONG8	delskp;		/* Skipped deletes			*/
	LONG8	rwtskp;		/* Skipped updates			*/
	LONG	qcnt;		/* Queue entries			*/
	LONG	lognum;		/* Log number of current scan pos	*/
	ULONG	logpos;		/* Offset of current scan pos		*/
	DFRKOP	curopT;		/* Current operation for tran thread	*/
	DFRKOP	curopN;		/* Current operation for non-tran thread*/
	DFRKOP	curopL;		/* Current operation for index load thread*/
} DFKSTT, *pDFKSTT;

/* background index load state information */
#define BLSTTvern	1	/* BLSTT (background index load) version #	*/
typedef struct dfkbis {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	LONG8	tstamp;		/* Time stamp: seconds since 70		*/
	LONG8	opnok;		/* Successful file opens		*/
	LONG8	addok;		/* Successful adds			*/
	LONG8	opnerr;		/* Failed file opens			*/
	LONG8	adderr;		/* Failed adds				*/
	LONG8	recbyt;		/* Current record offset for load	*/
	LONG	qcnt;		/* Queued load operations		*/
	DFRKOP	curop;		/* Current operation for thread		*/
	TEXT	datnam[255];	/* Data file name for load		*/
	TEXT	idxnam[255];	/* Index file name for load		*/
} BLSTT, *pBLSTT;

/*
** ctRecordUpdateCallbackControl function call structure.
*/
#define RUCBCTL_VERS_V01	1	/* initial version of structure	*/

#define RUCBCTL_VERS_CUR	RUCBCTL_VERS_V01	/* current version */

/* Size of input structure to pass to server */
#define RUCBCTLinsize_V01  SegOff(RUCBCTL,bufptr) /* version 1 input size */
#define RUCBCTLoutsize_V01 (0) /* version 1 output size */

typedef struct rucbctl {
	COUNT	verson;	/* version of this structure	*/
	COUNT	opcode;	/* operation code		*/
	LONG	bufsiz;	/* buffer size			*/
	pVOID	bufptr;	/* input/output buffer		*/
#ifndef ct8P
	LONG	pad;
#endif
} RUCBCTL, *pRUCBCTL;

#define RUCBACB_VERS_V01	1	/* initial version of structure	*/

#define RUCBACB_SIZE32_V01	(2 * sizeof(COUNT) + 3 * sizeof(LONG) + 5 *\
					sizeof(LONG))  /* 32bit size */
#define RUCBACB_SIZE64_V01	(2 * sizeof(COUNT) + 3 * sizeof(LONG) + 5 *\
					sizeof(LONG8)) /* 64bit size */

#ifdef ctFeatMAXFILE32
#define RUCBACB_SIZE32_MF32_V01	(sizeof(COUNT) + 2 + sizeof(FILNO) + 2 * sizeof(LONG) + 5 *\
					sizeof(LONG))  /* 32bit size */
#define RUCBACB_SIZE64_MF32_V01	(sizeof(COUNT) + 2 + sizeof(FILNO) + 2 * sizeof(LONG) + 5 *\
					sizeof(LONG8)) /* 64bit size */
#endif

#define RUCBACB_VERS_CUR	RUCBACB_VERS_V01	/* current version */
#define RUCBACB_SIZE32_CUR	RUCBACB_SIZE32_V01	/* current size 32bit */
#define RUCBACB_SIZE64_CUR	RUCBACB_SIZE64_V01	/* current size 64bit */

#ifdef ctFeatMAXFILE32
#define RUCBACB_SIZE32_MF32_CUR	RUCBACB_SIZE32_MF32_V01	/* current size 32bit (4-byte datno) */
#define RUCBACB_SIZE64_MF32_CUR	RUCBACB_SIZE64_MF32_V01	/* current size 64bit (4-byte datno) */
#endif

/* fixed length size of RUCBCTLaddcallback data when using 2-byte file numbers */
#define RUCBACB_FIXED_LEN (2 * sizeof(COUNT) + 2 * sizeof(LONG))
/* fixed length size of RUCBCTLaddcallback data when using 4-byte file numbers */
#define RUCBACB4_FIXED_LEN (sizeof(COUNT) + 2 + sizeof(FILNO) + 2 * sizeof(LONG))

/* client side fixed length size of RUCBCTLaddcallback data */
#ifdef ctFeatMAXFILE32
#define RUCBACB_FIXED_LEN_CS RUCBACB4_FIXED_LEN
#else
#define RUCBACB_FIXED_LEN_CS RUCBACB_FIXED_LEN
#endif

/*
** Supported record update callback call time (calltm) options. Values 1-7 are
** reserved for the sequential calltm value. The remaining bits can be used for
** other callback options.
*/
#define RUCBonrecupd	1	/* Call the callback function during the
				** record update.			    */
#define RUCBontrancmt	2	/* Call the callback function during the
				** transaction commit.			    */
#define RUCBqueuethrd	3	/* Queue the update to a background thread
				** that will call the callback after the
				** transaction commits.			    */
#define RUCBqueueapp	4	/* Queue the update to the transaction log or
				** memory queue. The application is responsible
				** for reading the log/queue.		    */

#define RUCBcalltmMASK	0x00000007 /* calltm option mask */

/*
** Other callback options:
*/
#define RUCBcallexist	0x00000008 /* When adding the callback function,
				   ** call it for all existing records. */
/* Next available bit:	0x00000010 */

/* Input buffer format for RUCBCTLaddcallback opcode. */
typedef struct rucbacb {
	COUNT	verson;	/* Version of this structure			    */
#ifdef ctFeatMAXFILE32
	COUNT	pad;	/* Padding to ensure 4-byte alignment of next field */
	FILNO	datno;	/* Data file number				    */
#else
	COUNT	datno;	/* Data file number				    */
#endif
	LONG	calltm; /* Time of function call			    */
	LONG	nfncnames; /* Number of function names			    */
#ifndef ctFeatMAXFILE32
	LONG	pad;	/* Padding to ensure 8-byte alignment of next field */
#endif
	pTEXT	datnam;	/* Data file name				    */
	pTEXT	cbname;	/* Unique name to identify this callback	    */
	pTEXT	dllname;/* Name of callback DLL				    */
	pTEXT	params;	/* Optional parameters				    */
	ppTEXT	fncnames;/* Callback function names			    */
#ifndef ct8P
	LONG	pad2[5];
#endif
} RUCBACB, *pRUCBACB;

#define RUCBGCB_VERS_V01	1	/* initial version of structure	*/

#define RUCBGCB_VERS_CUR	RUCBGCB_VERS_V01	/* current version */

/* fixed length size of RUCBCTLgetcallback data when using 2-byte file numbers */
#define RUCBGCB_FIXED_LEN (2 * sizeof(COUNT) + sizeof(LONG))
/* fixed length size of RUCBCTLgetcallback data when using 4-byte file numbers */
#define RUCBGCB4_FIXED_LEN (sizeof(COUNT) + 2 + sizeof(FILNO) + sizeof(LONG))

/* client side fixed length size of RUCBCTLgetcallback data */
#ifdef ctFeatMAXFILE32
#define RUCBGCB_FIXED_LEN_CS RUCBGCB4_FIXED_LEN
#else
#define RUCBGCB_FIXED_LEN_CS RUCBGCB_FIXED_LEN
#endif

/* Input/output buffer format for RUCBCTLgetcallback opcode. */
typedef struct rucbgcb {
	COUNT	verson;	/* Version of this structure		*/
#ifdef ctFeatMAXFILE32
	COUNT	pad;	/* Padding for 4-byte alignment		*/
	FILNO	datno;	/* Data file number			*/
#else
	COUNT	datno;	/* Data file number			*/
#endif
	LONG	bufsiz;	/* Output buffer size (input/output)	*/
	LONG	ncalbk; /* Number of callbacks (output)		*/
#ifndef ctFeatMAXFILE32
	LONG	pad;	/* Padding for 8-byte pointer alignment	*/
#endif
	pTEXT	datnam;	/* Data file name			*/
	pTEXT	outbuf;	/* Output buffer			*/
#ifndef ct8P
	LONG	pad2[2];
#endif
} RUCBGCB, *pRUCBGCB;

#define RUCBDCB_VERS_V01	1	/* initial version of structure	*/

#define RUCBDCB_VERS_CUR	RUCBDCB_VERS_V01	/* current version */

/* fixed length size of RUCBCTLdelcallback data when using 2-byte file numbers */
#define RUCBDCB_FIXED_LEN (2 * sizeof(COUNT))
/* fixed length size of RUCBCTLdelcallback data when using 4-byte file numbers */
#define RUCBDCB4_FIXED_LEN (sizeof(COUNT) + 2 + sizeof(FILNO))

/* client side fixed length size of RUCBCTLdelcallback data */
#ifdef ctFeatMAXFILE32
#define RUCBDCB_FIXED_LEN_CS RUCBDCB4_FIXED_LEN
#else
#define RUCBDCB_FIXED_LEN_CS RUCBDCB_FIXED_LEN
#endif

/* Input buffer format for RUCBCTLdelcallback opcode. */
typedef struct rucbdcb {
	COUNT	verson;	/* Version of this structure		*/
#ifdef ctFeatMAXFILE32
	COUNT	pad;	/* Padding for 4-byte alignment		*/
	FILNO	datno;	/* Data file number			*/
#else
	COUNT	datno;	/* Data file number			*/
	LONG	pad;	/* Padding for 8-byte pointer alignment	*/
#endif
	pTEXT	datnam;	/* Data file name			*/
	pTEXT	cbname;	/* Unique name to identify this callback*/
#ifndef ct8P
	LONG	pad2[2];
#endif
} RUCBDCB, *pRUCBDCB;

#define RUCBQCB_VERS_V01	1	/* initial version of structure	*/

#define RUCBQCB_VERS_CUR	RUCBQCB_VERS_V01	/* current version */

/* fixed length size of RUCBCTLqueuecallback data when using 2-byte file numbers */
#define RUCBQCB_FIXED_LEN (2 * sizeof(COUNT))
/* fixed length size of RUCBCTLqueuecallback data when using 4-byte file numbers */
#define RUCBQCB4_FIXED_LEN (sizeof(COUNT) + 2 + sizeof(FILNO))

/* client side fixed length size of RUCBCTLqueuecallback data */
#ifdef ctFeatMAXFILE32
#define RUCBQCB_FIXED_LEN_CS RUCBQCB4_FIXED_LEN
#else
#define RUCBQCB_FIXED_LEN_CS RUCBQCB_FIXED_LEN
#endif

/* Input buffer format for RUCBCTLqueuecallback opcode. */
typedef struct rucbqcb {
	COUNT	verson;	/* Version of this structure		*/
#ifdef ctFeatMAXFILE32
	COUNT	pad;	/* Padding for 4-byte alignment		*/
	FILNO	datno;	/* Data file number			*/
#else
	COUNT	datno;	/* Data file number			*/
	LONG	pad;	/* Padding for 8-byte pointer alignment	*/
#endif
	pTEXT	datnam;	/* Data file name			*/
	pTEXT	cbname;	/* Callback name			*/
	pTEXT	loadid;	/* Identifier for load operation	*/
#ifndef ct8P
	LONG	pad2[3];
#endif
} RUCBQCB, *pRUCBQCB;

/* opcode values */
#define	RUCBCTLaddcallback	1	/* Add a record update callback	   */
#define	RUCBCTLupdcallback	2	/* Update a record update callback */
#define	RUCBCTLdelcallback	3	/* Delete a record update callback */
#define	RUCBCTLgetcallback	4	/* Get callback settings	   */
#define	RUCBCTLqueuecallback	5	/* Queue background execution of
					   record update callback function
					   for all records in data file	   */

/*^**********************************/
/*
** ctFullText() function call structure.
*/
#define FTSP_VERS_V01	1	/* initial version of structure	*/

#define FTSP_VERS_CUR	FTSP_VERS_V01	/* current version */

/* Size of input structure to pass to server */
#define FTSPinsize_V01  SegOff(FTSP,bufptr) /* version 1 input size */
#define FTSPoutsize_V01 (0) /* version 1 output size */

typedef struct ftsprm {
	COUNT	verson;	/* version of this structure	*/
	COUNT	opcode;	/* operation code		*/
	LONG	bufsiz;	/* buffer size			*/
	pVOID	bufptr;	/* input/output buffer		*/
#ifndef ct8P
	LONG	pad;
#endif
} FTSP, *pFTSP;

#define FTSCRE_VERS_V01	1	/* initial version of structure	*/

#define FTSCRE_VERS_CUR	FTSCRE_VERS_V01	/* current version */

/* fixed length size of FTScreateindex data when using 2-byte file numbers */
#define FTSCRE_FIXED_LEN (2 * sizeof(COUNT) + 3 * sizeof(LONG))
/* fixed length size of FTScreateindex data when using 4-byte file numbers */
#define FTSCRE4_FIXED_LEN (sizeof(COUNT) + 6 + sizeof(FILNO) + 3 * sizeof(LONG))

/* client side fixed length size of FTScreateindex data */
#ifdef ctFeatMAXFILE32
#define FTSCRE_FIXED_LEN_CS FTSCRE4_FIXED_LEN
#else
#define FTSCRE_FIXED_LEN_CS FTSCRE_FIXED_LEN
#endif

/* Input buffer format for FTScreateindex opcode. */
typedef struct ftscre {
	COUNT	verson;	/* Version of this structure			*/
#ifdef ctFeatMAXFILE32
	TEXT	pad[6];	/* padding for alignment			*/
	FILNO	datno;	/* Data file number				*/
#else
	COUNT	datno;	/* Data file number				*/
#endif
	LONG	calltm;	/* Callback time				*/
	LONG	opts;	/* Full text index creation options (CTDB_FTI_CREATE_*)	*/
	LONG	mode;	/* File create mode (CTCREATE_MODE)		*/
	pTEXT	params;	/* Full text search parameters			*/
#ifndef ct8P
	LONG	pad2[1];
#endif
} FTSCRE, *pFTSCRE;

#define FTSDEL_VERS_V01	1	/* initial version of structure	*/

#define FTSDEL_VERS_CUR	FTSDEL_VERS_V01	/* current version */

/* fixed length size of FTSdeleteindex data when using 2-byte file numbers */
#define FTSDEL_FIXED_LEN (2 * sizeof(COUNT) + sizeof(LONG))
/* fixed length size of FTSdeleteindex data when using 4-byte file numbers */
#define FTSDEL4_FIXED_LEN (sizeof(COUNT) + 6 + sizeof(FILNO) + sizeof(LONG))

/* client side fixed length size of FTSdeleteindex data */
#ifdef ctFeatMAXFILE32
#define FTSDEL_FIXED_LEN_CS FTSDEL4_FIXED_LEN
#else
#define FTSDEL_FIXED_LEN_CS FTSDEL_FIXED_LEN
#endif

/* Input buffer format for FTSdeleteindex opcode. */
typedef struct ftsdel {
	COUNT	verson;	/* Version of this structure			*/
#ifdef ctFeatMAXFILE32
	TEXT	pad[6];	/* padding for alignment			*/
	FILNO	datno;	/* Data file number (-1 to not act on main file) */
#else
	COUNT	datno;	/* Data file number (-1 to not act on main file) */
#endif
	LONG	opts;	/* Full text search removal options */
	pTEXT	params;	/* Full text search removal params		*/
	pTEXT	path;	/* Data file path				*/
	pTEXT	name;	/* Data file name				*/
#ifndef ct8P
	LONG	pad2[3];
#endif
} FTSDEL, *pFTSDEL;

#define FTSALC_VERS_V01	1	/* initial version of structure	*/

#define FTSALC_VERS_CUR	FTSALC_VERS_V01	/* current version */

/* fixed length size of FTSallocft data when using 2-byte file numbers */
#define FTSALC_FIXED_LEN (4 * sizeof(COUNT))
/* fixed length size of FTSallocft data when using 4-byte file numbers */
#define FTSALC4_FIXED_LEN (sizeof(COUNT) + 2 + 2 * sizeof(FILNO) + sizeof(COUNT))

/* client side fixed length size of FTSallocft data */
#ifdef ctFeatMAXFILE32
#define FTSALC_FIXED_LEN_CS FTSALC4_FIXED_LEN
#else
#define FTSALC_FIXED_LEN_CS FTSALC_FIXED_LEN
#endif

/* Full text search error information */
typedef struct ftserrinf {
	NINT	errtype;  /* type of error that occurred */
	NINT	position; /* position in query string where error was detected */
} FTSERR, *pFTSERR;

#define FTSALCoutsize_V01 sizeof(FTSERR) /* output length */

/* Input buffer format for FTSallocft opcode. */
typedef struct ftsalc {
	COUNT	verson;	/* Version of this structure			*/
#ifdef ctFeatMAXFILE32
	COUNT	pad;	/* padding for alignment			*/
	FILNO	datno;	/* Data file number				*/
	FILNO	FTSno;	/* Full text index file number			*/
#else
	COUNT	datno;	/* Data file number				*/
	COUNT	FTSno;	/* Full text index file number			*/
#endif
	COUNT	mode;	/* Alloc mode					*/
#ifdef ctFeatMAXFILE32
	TEXT	pad2[2];/* padding for alignment			*/
#endif
	pTEXT	query;	/* Full text search parameters			*/
	FTSERR  ftserr;	/* Error details				*/
#ifndef ct8P
	LONG	pad3[1];
#endif
} FTSALC, *pFTSALC;

typedef enum ctftssynerr {
	FTS_ERROR_INVALID_QUERY_OPTION	= 1, /* Invalid syntax for query options */
	FTS_ERROR_BINOP_MISSING_OPERAND = 2, /* Missing operand for binary operator */
	FTS_ERROR_BINOP_INVALID_OPERAND = 3, /* Invalid operand for binary operator */
	FTS_ERROR_NO_QUERY		= 4, /* Query string evaluates to empty string */
	FTS_ERROR_INVALID_OPERATOR	= 5, /* Invalid operator */
	FTS_ERROR_INVALID_NEAR_VALUE	= 6, /* Invalid value for NEAR operator */
	FTS_ERROR_MISSING_QUOTE		= 7, /* Missing closing quote */
	FTS_ERROR_NEAR_NO_NEGATION	= 8, /* Cannot use negation on an operand of a NEAR operator */
	FTS_ERROR_ALL_NEGATED		= 9  /* Query cannot contain all negated words */
} CTFTS_SYNTAX_ERROR;

#define FTS_SYNTAX_ERROR_COUNT	9

#define FTSFRE_VERS_V01	1	/* initial version of structure	*/

#define FTSFRE_VERS_CUR	FTSFRE_VERS_V01	/* current version */

/* fixed length size of FTSfreeft data when using 2-byte file numbers */
#define FTSFRE_FIXED_LEN 2 * sizeof(COUNT)
/* fixed length size of FTSfreeft data when using 4-byte file numbers */
#define FTSFRE4_FIXED_LEN sizeof(COUNT) + 2 + sizeof(FILNO)

/* client side fixed length size of FTSfreeft data */
#ifdef ctFeatMAXFILE32
#define FTSFRE_FIXED_LEN_CS FTSFRE4_FIXED_LEN
#else
#define FTSFRE_FIXED_LEN_CS FTSFRE_FIXED_LEN
#endif

#define FTSMOV_VERS_V01	1	/* initial version of structure	*/

#define FTSMOV_VERS_CUR	FTSMOV_VERS_V01	/* current version */

/* fixed length size of FTSmoveft data when using 2-byte file numbers */
#define FTSMOV_FIXED_LEN (4 * sizeof(COUNT))
/* fixed length size of FTSmoveft data when using 4-byte file numbers */
#define FTSMOV4_FIXED_LEN (2 * sizeof(COUNT) + sizeof(FILNO))

/* client side fixed length size of FTSmoveft data */
#ifdef ctFeatMAXFILE32
#define FTSMOV_FIXED_LEN_CS FTSMOV4_FIXED_LEN
#else
#define FTSMOV_FIXED_LEN_CS FTSMOV_FIXED_LEN
#endif

/* Input buffer format for FTSmoveft opcode. */
typedef struct ftsmov {
	COUNT	verson;	/* Version of this structure			*/
#ifdef ctFeatMAXFILE32
	COUNT	opcode; /* Operation: first,last,next,prev		*/
	FILNO	datno;	/* Data file number				*/
#else
	COUNT	datno;	/* Data file number				*/
	COUNT	opcode; /* Operation: first,last,next,prev		*/
	COUNT	pad;
#endif
	pTEXT	recbuf;	/* Record buffer				*/
	pVRLEN	plen;	/* [in] recbuf size, [out] actual record len	*/
#ifndef ct8P
	LONG	pad2[2];
#endif
} FTSMOV, *pFTSMOV;

/* opcodes for FTSmoveft function call */
#define	FTSmoveftFRS		1	/* FirstInFT			*/
#define	FTSmoveftLST		2	/* LastInFT			*/
#define	FTSmoveftNXT		3	/* NextInFT			*/
#define	FTSmoveftPRV		4	/* PrevInFT			*/

/* Input buffer format for FTSfreeft opcode. */
typedef struct ftsfre {
	COUNT	verson;	/* Version of this structure			*/
#ifdef ctFeatMAXFILE32
	COUNT	pad;	/* padding for alignment			*/
	FILNO	datno;	/* Data file number				*/
#else
	COUNT	datno;	/* Data file number				*/
#endif
} FTSFRE, *pFTSFRE;

#define FTSGDR_VERS_V01	1	/* initial version of structure	*/

#define FTSGDR_VERS_CUR	FTSGDR_VERS_V01	/* current version */

/* fixed length size of FTSgetdictres data when using 2-byte file numbers */
#define FTSGDR_FIXED_LEN (2 * sizeof(COUNT)) /* we do not account for "filler" since not used in communication */
/* fixed length size of FTSgetdictres data when using 4-byte file numbers */
#define FTSGDR4_FIXED_LEN (sizeof(COUNT) + 2 + sizeof(FILNO))

/* client side fixed length size of FTSgetdictres data */
#ifdef ctFeatMAXFILE32
#define FTSGDR_FIXED_LEN_CS FTSGDR4_FIXED_LEN
#else
#define FTSGDR_FIXED_LEN_CS FTSGDR_FIXED_LEN
#endif

/* Input buffer format for FTSgetdictres opcode. */
typedef struct ftsgdr {
	COUNT	verson;	/* Version of this structure			*/
#ifdef ctFeatMAXFILE32
	COUNT	pad;	/* padding for alignment			*/
	FILNO	datno;	/* Data file number				*/
#else
	COUNT	datno;	/* Data file number				*/
	LONG	filler; /* not used, guarantees structure alignment	*/
#endif
	pTEXT	path;	/* Data file path				*/
	pTEXT	name;	/* FTI file name				*/
	pTEXT	recbuf;	/* Record buffer				*/
	pVRLEN	plen;	/* [in] recbuf size, [out] actual record len	*/
#ifndef ct8P
	LONG	pad2[4];
#endif
} FTSGDR, *pFTSGDR;

#define FTSREN_VERS_V01	1	/* initial version of structure	*/
#define FTSREN_VERS_V02	2	/* introduced origpath */
#define FTSREN_VERS_V03	3	/* introduced origname */

#define FTSREN_VERS_CUR	FTSREN_VERS_V03	/* current version */

#define FTSREN_FIXED_LEN (2 * sizeof(COUNT)) /* we do not account for "filler" since not used in communication */

/* Input buffer format for FTSrenameindexes opcode. */
typedef struct ftsren {
	COUNT	verson;     /* Version of this structure                    */
	COUNT	entries;    /* number of names specified in the array       */
	LONG	filler;     /* not used, guarantees structure alignment     */
	pTEXT origpath;     /* FTSREN_VERS_V02 original file path           */
	pTEXT origname;     /* FTSREN_VERS_V03 original file name           */
	pTEXT dataname;     /* datafile name                                */
	ppTEXT	oldnames;   /* old index names (for indices to be renamed)  */
	ppTEXT	newnames;   /* new index names (for indices to be renamed)  */
#ifndef ct8P
	LONG	pad[2];   /* was 3 before FTSREN_VERS_V03*/
#endif
} FTSREN, *pFTSREN;

/* opcode values */
#define	FTScreateindex		1	/* create full text index	*/
#define	FTSallocft		2	/* AllocFTSearch		*/
#define	FTSfreeft		3	/* FreeFTSearch			*/
#define	FTSmoveft		4	/* First/Last/Next/PrevInFT	*/
#define	FTSdeleteindex		5	/* remove full text index	*/
#define	FTSgetdictres		6	/* get FT dictionary resource	*/
#define	FTSrenameindexes	7	/* rename FTindices */

/*~**********************************/

/* record descriptor */
typedef struct recdsc {
	LONG	rdtype;		/* type of record descriptor */
	LONG	rdcount;	/* number of entries in record descriptor */
	LONG	oldrln;		/* old data record length */
	LONG	newrln;		/* new data record length */
	pVOID	prdspec;	/* record descriptor specification */
} RCDSC, *pRCDSC, **ppRCDSC;

#define RCDSCinsize_V01 (4 * sizeof(LONG))

/* record metadata state information */
typedef struct ctrmd {
	NINT	mdl;	/* total metadata length	*/
	NINT	mdbits;	/* what metadata is present	*/
	NINT	flxoff;	/* schema metadata offset	*/
	NINT	cmpoff;	/* compression metadata offset	*/
	NINT	skpcnt;	/* metadata bytes omitted	*/
} ctRMD, *pctRMD;

#define MDBIT_FLXREC	0x00000001 /* flexrec metadata */
#define MDBIT_CMPREC	0x00000002 /* compression metadata */

/* PTADMIN() parameters. */

#define ctPTAPMver1	1	/* initial version of structure. */

typedef struct ptaparms {
	LONG	verson;		/* structure version */
	LONG	prawno;		/* partition raw value */
	pTEXT	filnam;		/* name of partition host file */
	pTEXT	partdesc;	/* partition description */
	COUNT	ptmode;		/* partition mode */
} ctPTAPM, *pctPTAPM, **ppctPTAPM;

/* Length of fixed length data in marshalled ctPTAPM structure version 1 */
#define PTADMIN_PARAMS_FIXED_LENver1 (2 * sizeof(LONG) + sizeof(COUNT))

#define RESOURCE_ADD_PARAMSver1	1	/* initial version of structure. */

/* Resource add parameters. */
typedef struct resourceAddParams_t {
	LONG	verson;		/* structure version */
	LONG	varlen;		/* size of resource data in bytes */
	pVOID	resptr;		/* resource data */
} RESOURCE_ADD_PARAMS, *pRESOURCE_ADD_PARAMS, **ppRESOURCE_ADD_PARAMS;

/* Length of fixed length data in marshalled RESOURCE_ADD_PARAMS structure version 1 */
#define RESOURCE_ADD_PARAMS_FIXED_LENver1 (2 * sizeof(LONG))

#define RESOURCE_UPDATE_PARAMSver1	1	/* initial version of structure. */

/* Resource update parameters. */
typedef struct resourceUpdateParams_t {
	LONG	verson;		/* structure version */
	LONG	varlen;		/* size of resource data in bytes */
	pVOID	resptr;		/* resource data */
} RESOURCE_UPDATE_PARAMS, *pRESOURCE_UPDATE_PARAMS, **ppRESOURCE_UPDATE_PARAMS;

/* Length of fixed length data in marshalled RESOURCE_UPDATE_PARAMS structure version 1 */
#define RESOURCE_UPDATE_PARAMS_FIXED_LENver1 (2 * sizeof(LONG))

#define RESOURCE_DELETE_PARAMSver1	1	/* initial version of structure. */

/* Resource delete parameters. */
typedef struct resourceDeleteParams_t {
	LONG	verson;		/* structure version */
	LONG	varlen;		/* size of resource data in bytes */
	pVOID	resptr;		/* resource data */
} RESOURCE_DELETE_PARAMS, *pRESOURCE_DELETE_PARAMS, **ppRESOURCE_DELETE_PARAMS;

/* Length of fixed length data in marshalled RESOURCE_DELETE_PARAMS structure version 1 */
#define RESOURCE_DELETE_PARAMS_FIXED_LENver1 (2 * sizeof(LONG))

#define SETDEFBLKX_PARAMSver1	1	/* initial version of structure. */

/* SETDEFBLKX() parameters. */
typedef struct setDefBlkParams_t {
	LONG	verson;		/* structure version */
	LONG	alt;		/* alternate index */
	DEFDEF  def;		/* definition block data */
} SETDEFBLKX_PARAMS, *pSETDEFBLKX_PARAMS, **ppSETDEFBLKX_PARAMS;

/* Length of fixed length data in marshalled SETDEFBLKX_PARAMS structure version 1: verson, alt, def.ddeflen, def.ddeftot, def.ddefnum, def.ddeftyp */
#define SETDEFBLKX_PARAMS_FIXED_LENver1 (4 * sizeof(LONG) + 2 * sizeof(COUNT))

#define ADD_IDFIELD_PARAMSver1	1	/* initial version of structure. */

/* Add identity field parameters. */
typedef struct addIdFieldParams_t {
	LONG	verson;		/* structure version */
	NINT	fieldno;	/* field number */
	LONG8	startval;	/* start value */
	LONG	delta;		/* delta value */
} ADD_IDFIELD_PARAMS, *pADD_IDFIELD_PARAMS, **ppADD_IDFIELD_PARAMS;

#define DEL_IDFIELD_PARAMSver1	1	/* initial version of structure. */

/* Delete identity field parameters. */
typedef struct delIdFieldParams_t {
	LONG	verson;		/* structure version */
} DEL_IDFIELD_PARAMS, *pDEL_IDFIELD_PARAMS, **ppDEL_IDFIELD_PARAMS;

#define RESET_IDFIELD_PARAMSver1	1	/* initial version of structure. */

/* Reset identity field parameters. */
typedef struct resetIdFieldParams_t {
	LONG	verson;		/* structure version */
	LONG	pad;		/* unused padding */
	LONG8	nxtval;		/* next value */
} RESET_IDFIELD_PARAMS, *pRESET_IDFIELD_PARAMS, **ppRESET_IDFIELD_PARAMS;

#define XTDATR_IDFIELD_PARAMSver1	1	/* initial version of structure. */

/* Set extended attribute identity field parameters. */
typedef struct xtdatrIdFieldParams_t {
	LONG	verson;		/* structure version */
	LONG	xtdatr;		/* extended attribute value */
} XTDATR_IDFIELD_PARAMS, *pXTDATR_IDFIELD_PARAMS, **ppXTDATR_IDFIELD_PARAMS;

/*
** Temporary directory parameters.
*/

typedef pVOID  TDRHND;	 /* temporary directory handle			*/
typedef ppVOID pTDRHND;  /* pointer to temporary directory handle	*/
typedef pVOID  TDROPR;	 /* temporary directory operation		*/
typedef ppVOID pTDROPR;  /* pointer to temporary directory operation	*/

typedef struct tmpdir ctMEM * pTMPDIR;

/* Temporary directory callback function data. */
typedef struct tmpdstt {
	pTMPDIR	ptmpdir; /* options passed to temporary directory function	*/
	pTEXT	dirnam;	 /* name of the temporary directory			*/
	COUNT	val;	 /* percent complete or error code			*/
	TEXT	opcode;  /* operation code					*/
} TMPDSTT, *pTMPDSTT;

/* Temporary directory callback function prototype. */
typedef NINT(*pTDRFNC)(pTMPDSTT ptmpdstt);

#define ctTMPDIRprogressCB	0x00000001 /* progress callback code	*/

/* Temporary directory callback function opcodes. */
#define ctTMPDCBKbegindir	1	/* start temp directory			*/
#define ctTMPDCBKprogdir	2	/* temp directory progress		*/
#define ctTMPDCBKenddir		3	/* end temp directory			*/
#define ctTMPDCBKvrfydir	4	/* temp directory verify progress	*/
#define ctTMPDCBKbeginsdir	5	/* start sub directory			*/
#define ctTMPDCBKprogsdir	6	/* subs directory progress		*/
#define ctTMPDCBKendsdir	7	/* end sub directory			*/
#define ctTMPDCBKvrfysdir	8	/* sub directory verify progress	*/
#define ctTMPDCBKbeginfile	9	/* start file				*/
#define ctTMPDCBKendfile	10	/* end file				*/

/* Temp directory option values. */
#define ctTDRcreate       0x00000001 /* create temp directories			*/ 
#define ctTDRdelete       0x00000002 /* delete temp directories			*/ 

#define ctTDRdelRecurs    0x00000004 /* recursively delete directories		*/

#define MAXTDRNAME 255

/* Temporary directory name structure. */
typedef struct cttmpdirnam {
	TEXT	name[MAXTDRNAME];	/* Temp directory name.		*/
} CTTDRNAM, *pCTTDRNAM;

/*
** Temporary directory parameters.
*/

#define TDRPRM_VERS_V01	1	/* initial version of structure	*/

#define TDRPRM_VERS_CUR	TDRPRM_VERS_V01	/* current version */

/* Length of fixed length fields in TDRPRM structure */
#define TDRPRM_FIXED_LEN 3 * sizeof(LONG)

typedef struct cttdrprm {
	LONG		versn;		/* Structure version			*/
	ULONG		tdroptions;	/* Temporary directory options		*/
	LONG		dirnamcnt;	/* Number of directoriy names		*/
	pCTTDRNAM	dirnam;		/* Directory names			*/
	TDRHND		tdrhnd;		/* The associated temp dir handle	*/
} TDRPRM, ctMEM * pTDRPRM, ctMEM ** ppTDRPRM;

/*
** Temporary directory function call structure.
*/

#define TMPDIR_VERS_V01	1	/* initial version of structure	*/

#define TMPDIR_VERS_CUR	TMPDIR_VERS_V01	/* current version */

/* Length of fixed length fields in TMPDIR structure */
#define TMPDIR_FIXED_LEN 3 * sizeof(LONG)

typedef struct tmpdir {
	LONG		versn;		/* Structure version			*/
	LONG		ntdrprm;	/* Number of temp dir parameter structs */
	LONG		errbufsiz;	/* Size of optional error message buffer*/
	LONG		reserved;	/* Reserved for future use		*/
	pTDRPRM		ptdrprm;	/* Temp dir parameter structures	*/
	pTDRFNC		ptdrfnc;	/* Callback function			*/
	pVOID		pusrdata;	/* User data pointer			*/
	pTEXT		errbuf;		/* Optional error message buffer	*/
} TMPDIR;

typedef struct itdroplst *pTDROPS;
typedef struct itdroplst {
	pTDRPRM item;
	pTDROPS next;
	pTDROPS prev;
} TDROPS;

typedef struct itdrhnd {
	TMPDIR	tmpdir;
	pTDROPS	ptmpdops;
} TDRINF, *pTDRINF;


/*
** Multiple data record filter support definitions
*/

#define ctDATFLT_FCM_INDEX	0 /* Index of internal filter list	*/
#define ctDATFLT_USR_INDEX	1 /* Index of user filter list		*/
#define ctDATFLT_MAX_INDEX	2 /* Number of filter lists		*/

/*
** Data record filter options
*/
#define ctDATFLT_OPTION_CURCTX	0x0001 /* This data filter applies only
					  to the ISAM context in which
				          it was created.		*/

/*
** User and internal filters can use filter numbers in the range 0..16383.
** A call to SETFLTR uses filter number 16384. Bit 0x8000 indicates an
** internal filter.
*/
#define ctDATFLT_INDEX_MAX	0x3fff /* Largest allowed filter number	*/
#define ctDATFLT_INDEX_SETFLTR	0x4000 /* Filter number used by SETFLTR */
#define ctDATFLT_INTERNAL_BIT	0x8000 /* Bit set for internal filters	*/

/*
** RESETFLTR mode bits
*/
#define ctDATFLT_RESETN		0x0001 /* all SETFLTRN filters		*/
#define ctDATFLT_RESET		0x0002 /* SETFLTR filter		*/
#define ctDATFLT_RESETN_FCM	0x0004 /* all SETFLTRN internal filters	*/

/*
** The set of all valid RESETFLTR mode bits
*/
#define ctDATFLT_RESET_MASK (ctDATFLT_RESETN|ctDATFLT_RESET|ctDATFLT_RESETN_FCM)

/*
** Internal FairCom filter numbers.
*/
#define CTFLTNUM_MRT		 0 /* MRT filter			*/
#define CTFLTNUM_PUSHDOWN	 1 /* SQL pushdown filter		*/

typedef struct ctdtflt_t {
	pVOID	datflt;		/* pointer to filter		*/
	LONG	dttflt;		/* type of data filter		*/
	UCOUNT	fltnum;		/* data filter number		*/
	UCOUNT	fltopts;	/* data filter options		*/
	struct ctdtflt_t	/* pointer to next item in list */
		*fltnxt;
	struct ctdtflt_t	/* pointer to prev item in list	*/
		*fltprv;
} ctDTFLT, *pctDTFLT, **ppctDTFLT;

/* user-specific filename redirection list state information */
typedef struct uredlst {
	struct redlst
		*uredlst_ptr;	/* redirection rule list pointer*/
	NINT	uredlst_tot;	/* total allocated list entries	*/
	NINT	uredlst_cur;	/* total used list entries	*/
	} UREDLST, * pUREDLST;

/*
** VSS writer configuration modes:
*/

#define ctVSSW_SETDIAG	1	/* Set diagnostic mode			*/
#define ctVSSW_SETSVNM	2	/* Set c-tree Server process name	*/
#define ctVSSW_SET_QUIESCE_TIMEOUT 3 /* Set timeout for VSS writer quiesce call */

/* Structure used to test at compile time if ct8P is properly defined. */
typedef struct {
#ifdef ct8P
	TEXT	t[sizeof(char *) == 8];	/* If compile error here, ct8P is on but pointer is not 8 bytes. */
#else
	TEXT	t[sizeof(char *) == 4]; /* If compile error here, ct8P is off but pointer is not 4 bytes. */
#endif
} testctptrsize;

/*
** Directory traverse callback function
*/
#ifdef PROTOTYPE
typedef VOID(*pDirTraverseFunc)(pTEXT, pVOID);
#else
typedef VOID(*pDirTraverseFunc)();
#endif

/* Directory traverse callback function opcodes. */
#define ctTDCBKinit     1 /* initiate traverse  */
#define ctTDCBKterm     2 /* terminate traverse */
#define ctTDCBKbeginDir 3 /* start dir traverse */
#define ctTDCBKendDir   4 /* end dir traverse   */
#define ctTDCBKfile     5 /* file check         */
#define ctTDCBKfsError  6 /* file system error  */

/* Directory traverse option values. */
#define ctTDstopOnError  0x00000001 /* stop on any error, if not ignores any error during the directory traverse */
#define ctTDcheckFiles   0x00000002 /* callback instigated file by file                                          */

typedef struct ctdirtravdata {
	TEXT  opcode;     /* operation code                        */
	NINT  mode;       /* tranverse move                        */
	NINT  errcd;      /* error code                            */
	LONG  syserrcd;   /* system error code                     */
	LONG  errbufsiz;  /* size of optional error message buffer */
	pTEXT errbuf;     /* optional error message buffer	 */
	pVOID fileInfo;   /* current file info                     */
	COUNT pct;        /* percentage completed                  */
} DIRTRAVDATA, ctMEM * pDIRTRAVDATA;

/* Unique file ID data type for lock conflict detection in multi-threaded
FPUTFGET model (ctMTFPG_LOKCNF). */
#ifdef ctFeatMTFPG_LOKCNFunqid
typedef LONG8 ctFUID[2]; /* improved file unique ID */
#else
typedef LONG  ctFUID;	 /* original file unique ID */
#endif

/* Background load (of index or record update callback) status values: */
typedef enum bgldstt {
	BGLD_PENDING	= 0,	/* load is pending */
	BGLD_INPROGRESS	= 1,	/* load is in progress */
	BGLD_SUCCEEDED	= 2,	/* load completed successfully */
	BGLD_FAILED	= 3	/* load failed */
} BGLDSTT;

/* Background load (of index or record update callback) state record update options: */
typedef enum bgldupd {
	BGLD_UPDATE_ALL		= 0,	/* update all values */
	BGLD_UPDATE_STATUS	= 1	/* update current status */
} BGLDUPD;

#define BGLDIDZ 32

/* Background load (of index or record update callback) details: */
typedef struct bgldinf {
	LONG8	queuedtime;	/* time at which the load was queued	      */
	LONG8	statustime;	/* time at which current status was reported  */
	LONG8	offset;		/* current offset in file		      */
	LONG8	npass;		/* number of successful operations	      */
	LONG8	nfail;		/* number of failed operations		      */
	BGLDSTT	status;		/* current load status			      */
	LONG	errcod;		/* background load error code		      */
	LONG	curpct;		/* current percentage complete		      */
	LONG	pad;		/* padding for structure alignment	      */
	TEXT	cbname[BGLDIDZ];/* name of the callback function	      */
	TEXT	loadid[BGLDIDZ];/* ID for this background load operation      */
} BGLDINF, *pBGLDINF;

#define BGLDRES_VERS_V01	1	/* initial version of structure	*/

#define BGLDRES_VERS_CUR	BGLDRES_VERS_V01	/* current version */

/* Queued record update callback load resource format: */
typedef struct bgldres {
	ULONG	restyp;
	ULONG	resnum;
	TEXT	resnam[FCRNAM_LEN];
	LONG	verson;		/* version of structure			      */
	LONG	numbgl;		/* number of background load entries          */
	BGLDINF	bgldi[1];	/* list of background load entries	      */
} BGLDRES, *pBGLDRES, **ppBGLDRES;

/* ctEXPTM structure expstt field values: */
#define EXPTM_NONE	0	/* account has no expiration date */
#define EXPTM_EXPIRED	1	/* account has expiration date that has passed */
#define EXPTM_FUTURE	2	/* account has future expiration date */

/* User account expiration time information: */
typedef struct ctexptm {
	LONG	expdays;	/* days until account expires */
	UTEXT	exphours;	/* hours until account expires */
	UTEXT	expminutes;	/* minutes until account expires */
	UTEXT	expseconds;	/* seconds until account expires */
	UTEXT	expstt;		/* expiration date status */
} ctEXPTM, *pctEXPTM;

/* ct_usrtl() special values */
#define TL_TIMEOUT -6L          /* transaction exceeded time limit */
#define TL_MAXLOGS -5L		/* transaction exceeded max logs */
#define TL_UNDO_PENDING -4L	/* forcei failure */
#define TL_ENDTRAN_WRITTEN  -3L /* TRANEND or TRANABT */
#define TL_PREBEGIN -2L		/* set in ctwrtlog before > 0 */
#define TL_ABANDONED -1L	/* Transaction abandoned */
#define TL_NO_BEGIN 0L		/* no active TRANBEG in log */

/* Structure for enumerating resources in file */
typedef struct {
	ULONG	restyp;		/* input: resource type to search */
	TEXT	resdat[FCRES_LAST + 1];	/* output: resource status */
} FC_ENUM, *pFC_ENUM;


#define CT_STDOUT getCtreeSTDOUT()
#define CT_STDERR getCtreeSTDERR()


/* Input/output buffer format for addAutoSysTimeFields/WhichAutoSysTimeFields/UpdateAutoSysTimeFields */
typedef struct astfield {
	LONG	fieldno; /* field number */
	TEXT	mode;	/* set time  */
} A_STFIELD, *pA_STFIELD;
#define A_STFIELD_insize_V01 (sizeof(LONG)+sizeof(TEXT))

/* valid mode values in astfield */
#define CT_AUTOSYSTIME_OFF    0x00
#define CT_AUTOSYSTIME_CREATE 0x01
#define CT_AUTOSYSTIME_UPDATE 0x02

typedef struct astfields {
	COUNT	verson;	/* Version of this structure		*/
	COUNT	entries;/* number of entries in fields array*/
	LONG	pad; /* padding to ensure struct alignment */
	pA_STFIELD	fields;	/* fields array */
#ifndef ct8P
	LONG	pad2; /* padding to ensure same structure size for 32bit and 64bit compiles */
#endif
} A_STFIELDS, *pA_STFIELDS;

#define A_STFIELDS_VERS_V01	1	/* initial version of structure	*/

#define A_STFIELDS_VERS_CUR	A_STFIELDS_VERS_V01	/* current version */

#define A_STFIELDS_insize_V01 (sizeof(COUNT)*2)

/* valid mode values for internal stream functions*/
#define A_STFIELDS_stream_FULL 1
#define A_STFIELDS_stream_BASE 2
#define bigadr(tp,off) ((TEXT *)(tp)+(size_t)(off))

/* File region array entry for GetFileRegions() */
typedef struct fileRegion_t {
	ULONG8	offset; /* [OUT] starting record offset for region in the data file */
	ULONG8	length; /* [OUT] size of this region in bytes */
} FILE_REGION, *pFILE_REGION;

/* File region request parameter for GetFileRegions() */
typedef struct fileRegionRequest_t {
	COUNT	structVersion; /* [IN] version of this structure */
#ifdef ctFeatMAXFILE32
	COUNT	pad;		/* unused padding for alignment */
	FILNO	dataFileNumber; /* [IN] c-tree data file number */
	LONG	pad2;		/* unused padding for alignment */
#else
	COUNT	dataFileNumber; /* [IN] c-tree data file number */
#endif
	ULONG	numberOfRegions; /* [IN] number of array entries */
	pFILE_REGION fileRegions; /* [OUT] output array */
} FILE_REGION_REQUEST, *pFILE_REGION_REQUEST;

#define FILE_REGION_REQUEST_VERS_V01	1	/* initial version of structure	*/

#define FILE_REGION_REQUEST_VERS_CUR	FILE_REGION_REQUEST_VERS_V01	/* current version */

/* fixed length size of FILE_REGION_REQUEST data when using 2-byte file numbers */
#define FILE_REGION_REQUEST_insize_V01 (2 * sizeof(COUNT) + sizeof(ULONG))
/* fixed length size of FILE_REGION_REQUEST data when using 4-byte file numbers */
#define FILE_REGION_REQUEST4_insize_V01 (sizeof(COUNT) + 2 + sizeof(FILNO) + 4 + sizeof(ULONG))

/* client side fixed length size of FILE_REGION_REQUEST data */
#ifdef ctFeatMAXFILE32
#define FILE_REGION_REQUEST_insize_V01_CS FILE_REGION_REQUEST4_insize_V01
#else
#define FILE_REGION_REQUEST_insize_V01_CS FILE_REGION_REQUEST_insize_V01
#endif

/* Compile time check to verify that a NINT is the same size as a LONG */
typedef char check_sizeof_NINT_equals_sizeof_LONG[sizeof(NINT) == sizeof(LONG)];

/* return value from unique file check functions ct_uniqfile() and ct_uniqfile_fd() */
typedef enum UniqueFileReturn_t {
	UNIQFILE_ERROR = -1, /* error: could not check if same file */
	UNIQFILE_SAME_FILE = 0, /* the two file descriptors/file names refer to the same file */
	UNIQFILE_DIFFERENT_FILES = 1 /* the two file descriptors/file names refer to different files */
} UNIQFILE_RETURN;

/* Parameters for ctFILELIST() function call */
typedef struct ctFileListRequest_t {
	COUNT	structVersion; /* [IN] version of this structure */
	COUNT	pad; /* unused padding */
	LONG	value; /* [INOUT] value to set/get on the entry */
	LONG	member; /* [INOUT] second value to set/get on the entry */
	LONG	scale; /* [INOUT] second value to set/get on the entry */
	LONG	list; /* [IN] which list to act on */
	LONG	action; /* [IN] the action to take */
	TEXT 	filnam[255]; /* [IN] null-terminated filename */
} ctFILELIST_REQUEST, *pctFILELIST_REQUEST;

#define FILELIST_REQUEST_VERS_V01	1	/* initial version of structure	*/

#define FILELIST_REQUEST_VERS_CUR	FILELIST_REQUEST_VERS_V01	/* current version */

/* fixed length size of FILELIST_REQUEST data */
#define FILELIST_REQUEST_insize_V01 (2 * sizeof(COUNT) + 5 * sizeof(LONG))

/* Parameters for ctClusterConfig() function call */
typedef struct ctClusterConfigRequest_t {
	COUNT	structVersion; /* [IN] version of this structure */
	COUNT	pad; /* unused padding */
	LONG	inputOptions; /* [IN] input options */
	LONG	outputOptions; /* [IN] output options */
	LONG	outputBufferSize; /* [INOUT] size of output buffer */
	pTEXT	inputBuffer; /* [IN] input buffer */
} ctCLUSTER_CONFIG_REQUEST, *pctCLUSTER_CONFIG_REQUEST;

#define CLUSTER_CONFIG_REQUEST_VERS_V01	1	/* initial version of structure	*/

#define CLUSTER_CONFIG_REQUEST_VERS_CUR	CLUSTER_CONFIG_REQUEST_VERS_V01	/* current version */

/* fixed length size of CLUSTER_CONFIG_REQUEST data */
#define CLUSTER_CONFIG_REQUEST_insize_V01 (2 * sizeof(COUNT) + 3 * sizeof(LONG))

/* Parameters for ctTruncateFile() function call */
typedef struct ctTruncateFileRequest_t {
	COUNT	structVersion; /* [IN] version of this structure */
	COUNT	pad; /* unused padding */
	pTEXT	filename; /* [IN] file name */
	pTEXT	fileword; /* [IN] optional file password */
} ctTRUNCATE_FILE_REQUEST, *pctTRUNCATE_FILE_REQUEST;

#define TRUNCATE_FILE_REQUEST_VERS_V01	1	/* initial version of structure	*/

#define TRUNCATE_FILE_REQUEST_VERS_CUR	TRUNCATE_FILE_REQUEST_VERS_V01	/* current version */

/* fixed length size of TRUNCATE_FILE_REQUEST data */
#define TRUNCATE_FILE_REQUEST_insize_V01 (2 * sizeof(COUNT) + 3 * sizeof(LONG))

/* fixed length size of actual TRUNCATE_FILE_REQUEST data */
#define TRUNCATE_FILE_REQUEST_insize_actual_V01 sizeof(COUNT)

/* Log position. */
typedef struct ctlogposition_t {
	LONG	lognum;		/* Log number of current scan pos	*/
	ULONG	logpos;		/* Offset of current scan pos		*/
} ctLOGP, *pctLOGP;

/* ctREPL_READ_LOG_DATA_REQUEST status field bits */
typedef enum {
	REPLREAD_END_OF_LOG = 0x00000001 /* end of log */
} REPL_READ_LOG_DATA_STATUS;

/* Parameters for ctReplReadLogData() function call */
typedef struct ctReplReadLogDataRequest_t {
	COUNT	structVersion; /* [IN] version of this structure */
	COUNT	pad; /* unused padding */
	LONG	logNumber; /* [IN] transaction log number to read */
	LONG	offsetInLog; /* [IN] starting offset in log to read */
	ctLOGP	commitPosition; /* [IN] optional last commit position on target */
	ULONG	bytesRead; /* [OUT] number of bytes read */
	REPL_READ_LOG_DATA_STATUS status; /* [OUT] status bits */
} ctREPL_READ_LOG_DATA_REQUEST, *pctREPL_READ_LOG_DATA_REQUEST;

#define REPL_READ_LOG_DATA_REQUEST_VERS_V01	1	/* initial version of structure	*/

#define REPL_READ_LOG_DATA_REQUEST_VERS_CUR	REPL_READ_LOG_DATA_REQUEST_VERS_V01	/* current version */

/* fixed length size of REPL_READ_LOG_DATA_REQUEST input data */
#define REPL_READ_LOG_DATA_REQUEST_insize_V01 (2 * sizeof(COUNT) + 4 * sizeof(LONG))

/* Parameters for ctReplCleanupTranStateKeys() function call */
typedef struct ctReplCleanupTranStateKeysRequest_t {
	COUNT	structVersion; /* [IN] version of this structure */
	COUNT	pad; /* unused padding */
	ctLOGP	lastCommitPosition; /* [IN/OUT] on input, last commit position removed from tran state list; on output, commit position of last key removed from tran state index */
	LONG	numDeleted; /* [OUT] on success, the number of keys that were deleted */
} ctREPL_CLEANUP_TRAN_STATE_KEYS_REQUEST, *pctREPL_CLEANUP_TRAN_STATE_KEYS_REQUEST;

#define REPL_CLEANUP_TRAN_STATE_KEYS_REQUEST_VERS_V01	1	/* initial version of structure	*/

#define REPL_CLEANUP_TRAN_STATE_KEYS_REQUEST_VERS_CUR	REPL_CLEANUP_TRAN_STATE_KEYS_REQUEST_VERS_V01	/* current version */

/* fixed length size of REPL_CLEANUP_TRAN_STATE_KEYS_REQUEST input data */
#define REPL_CLEANUP_TRAN_STATE_KEYS_REQUEST_insize_V01 (2 * sizeof(COUNT) + 2 * sizeof(LONG))

/* size of ctReplCleanupTranStateKeys() output data */
#define REPL_CLEANUP_TRAN_STATE_KEYS_outsize_V01 (sizeof(ctLOGP) + sizeof(LONG))

/* mutually-exclusive makifil() modes: */
#define MAKIFIL_MBALLC 0 /* client or server, use mballc, 2 passes */
#define MAKIFIL_CTGETMEM 1 /* server, use ctgetmem */
#define MAKIFIL_RECOVERY 2 /* auto recovery */
#define MAKIFIL_CTGETMEM_KEEP_ORG 3 /* server, use ctgetmem, don't free original pointer */

/* makifil() mode bits: */
#define MAKIFIL_XCREBLK_INDEX_ONLY 0x00000004 /* option bit: xcreblk array for indexes only, no data file entry */

#endif /* ctPORTH */

/* end of ctport.h */
