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

/* ctSIBLING_HANDSHAKE_003 */
/* ctsrvr.set file key for c-treeACE Express Project */
#ifdef   ctPortACE_EXPRESS_HANDSHAKE_V9_0_0
#ifndef __CTCFGSET_H__
#define __CTCFGSET_H__

#ifdef ctFeatSETTINGS /* ctsrvr.set file support mandatory */

	ULONG	ctsetKey = 0x19191919;
#ifdef MULTITRD 	/* for code filter */
#ifdef HIGH_LOW
	ULONG actkey[]  = {0x12345678L,0x20000000L,0,0,0,0x87654321L,ctPRODUCT,0,0,0,0x19191919,0,0,0,0};
#else/*LOW_HIGH */
	ULONG actkey[]  = {0x12345678L,0x00000020L,0,0,0,0x87654321L,ctPRODUCT,0,0,0,0x19191919,0,0,0,0};
#endif
#endif

#else /* ~ctFeatSETTINGS */

	ULONG	ctsetKey = 0x23232323;
#ifdef MULTITRD 	/* for code filter */
#ifdef HIGH_LOW
	ULONG actkey[]  = {0x12345678L,0x20000000L,0,0,0,0x87654321L,ctPRODUCT,0,0,0,0x23232323,0,0,0,0};
#else/*LOW_HIGH */
	ULONG actkey[]  = {0x12345678L,0x00000020L,0,0,0,0x87654321L,ctPRODUCT,0,0,0,0x23232323,0,0,0,0};
#endif
#endif

#endif /* ~ctFeatSETTINGS */

#endif /* __CTCFGSET_H__ */
#endif /* ctPortACE_EXPRESS_HANDSHAKE_V9_0_0 */

/* end of ctcfg000.h */


