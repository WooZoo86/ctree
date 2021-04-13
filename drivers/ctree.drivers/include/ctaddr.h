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

#ifndef CTADDR_H
#define CTADDR_H

#if defined(ctPortUNIX) || defined(DH_OS_UNIX)
#ifndef ctNETINET_IN_H
#define ctNETINET_IN_H <netinet/in.h>
#include ctNETINET_IN_H
#endif 
#endif

#if defined(ctFeatIPv6) || defined(ctFeatSQLIPv6)
#if defined(ctPortWIN32) || defined(DH_OS_WINNT)
#define  ctIN6ADDR_H	<in6addr.h>
#include ctIN6ADDR_H
#endif /* ~WIN32 */

typedef struct {
	int type;
	union {
		struct in_addr i4;
		struct in6_addr i6;
	} addr;
} ctUADDR_T;
#define ctADDR_T ctUADDR_T
#define FAMILYSZ(x) (((x)==AF_INET) ? sizeof(struct in_addr):sizeof(struct in6_addr))
#if defined(ctPortWIN32) || defined(DH_OS_WINNT)
#define V4addr(x) ((x).addr.i4.S_un.S_addr)
#else
#define V4addr(x) ((x).addr.i4.s_addr)
#endif
#define ctADDR_T_ADDRESS(x) ((x).addr)
#define ctADDR_T_TYPE(x) ((x).type)
#else /* ~IPV6 */

#ifdef ctPortUNIX 
#ifndef ctSYS_SOCKET_H
#define ctSYS_SOCKET_H
#include <sys/socket.h>
#endif
#endif

#ifdef ctPORTH
typedef LONG ctADDR_T;
typedef ULONG ctUADDR_T;
#else
typedef dh_i32_t ctADDR_T;
typedef dh_u32_t ctUADDR_T;
#endif
#define V4addr(x) x
#define FAMILYSZ(x) sizeof(ctUADDR_T)
#define ctADDR_T_ADDRESS(x) (x)
#define ctADDR_T_TYPE(x) AF_INET
#endif /* ~IPV6 */

#ifndef INADDR_NONE
#define INADDR_NONE ((in_addr_t)0xffffffff)
#endif
#endif
