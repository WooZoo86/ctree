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

#define utilKWLEN 64
#define utilKVLEN 255

#define cfgUTILUSERID 0
#define cfgUTILPASSWD 1

typedef struct {
	TEXT  argname[utilKWLEN];
	TEXT  argval[utilKVLEN];
} UTILKW;

#define KWCNT	2

#if defined(ctPortWIN32) && defined(ctDLLLIB)
#ifdef CTUTLSET_C
__declspec(dllexport)
#else
__declspec(dllimport)
#endif
#endif
extern UTILKW	utilkeywds[KWCNT];
extern ULONG	ctsetKey;

#ifdef PROTOTYPE
extern NINT util_pre_scan(pNINT argc, ppTEXT argv);
extern VOID ctCommDec(pTEXT pMsg1, ULONG msg1Len, pTEXT pMsg2, ULONG msg2Len);
#else
extern NINT util_pre_scan();
extern VOID ctCommDec();
#endif

/* end of ctutlset.h */
