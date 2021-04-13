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

/*************************************/
#ifdef  ctUNXCOM_NTP
#ifndef ctntUNIX
#define ctntUNIX
#endif
#endif

#ifdef 	ctntUNIX
#define ctOPT2H
#include "ctoptn.h"
#ifndef ctFeatSRVR_SDK_CSAPI
#define CTREE_IS_USED
#endif

#ifdef ctPortHP9000
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/time.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#ifndef ctPortHP9000
#ifndef ctPortSUN41
#ifndef ctPortINTERACTIVE
#ifndef ctPortAPPLEAUX
#ifndef ctPortLINUX
#include <sys/select.h>
#endif
#endif
#endif
#endif
#endif

#ifdef ctPortAPPLEAUX
#include <sys/file.h>
#define  mkfifo(p,m)  mknod(p,((m) | S_IFIFO),0)
#endif

#ifdef ctPortINTERACTIVE
#include <net/errno.h>
#include <sys/tty.h>
#include <sys/sioctl.h>
#include <sys/pty.h>
#define  mkfifo(p,m)  mknod(p,((m) | S_IFIFO),0)
#endif

#if (defined(ctPortSOLARIS) || defined(ctPortSOL386) || defined(ctPortATTUNIX386))
#include <sys/filio.h>
#endif

#define ntUNIX

#ifndef TCP_NODELAY
#define TCP_NODELAY     0x0001
#endif

#endif /* ctntUNIX */
/*************************************/

/*************************************/
#ifdef  ctW32COM_NTP
#ifndef ctntWIN32
#define ctntWIN32
#endif
#endif

#ifdef 	ctntWIN32
#define ctOPT2H
#include "ctoptn.h"
#ifndef ctFeatSRVR_SDK_CSAPI
#define CTREE_IS_USED
#endif

#ifndef	ntWINNT
#define ntWINNT
#endif

#ifndef ntMSC
#define ntMSC
#endif

#endif /* ctntWIN32 */
/*************************************/

/*************************************/
/* Apple MAC */
#ifdef  ctMACCOM_NTP
#ifndef ctntMAC
#define ctntMAC
#endif
#endif

#ifdef 	ctntMAC
#define ctOPT2H
#include "ctoptn.h"
#ifndef ctFeatSRVR_SDK_CSAPI
#define CTREE_IS_USED
#endif

#ifndef	ntMAC
#define ntMAC
#endif

#ifndef ntCWP
#define ntCWP		/* Code Warrior Pro */
#endif

#endif /* ctntMAC */
/*************************************/


/*************************************/
#ifdef  ctOS2COM_NTP
#ifndef ctntOS2
#define ctntOS2
#endif
#endif

#ifdef 	ctntOS2
#define ctOPT2H
#include "ctoptn.h"
#ifndef ctFeatSRVR_SDK_CSAPI
#define CTREE_IS_USED
#endif

#ifndef ntICC
#define ntICC
#endif

#ifndef ntOS2
#define ntOS2
#endif

#ifndef TCP_NODELAY
#define TCP_NODELAY     0x01 /* from tcpip\include\netinet\tcp.h */
#endif

#endif /* ctntOS2 */
/*************************************/


/*************************************/
#ifdef  ctDOSCOM_NTP
#ifndef ctntDOS
#define ctntDOS
#endif
#endif

#ifdef 	ctntDOS
#define ctOPT2H
#include "ctoptn.h"
#ifndef ctFeatSRVR_SDK_CSAPI
#define CTREE_IS_USED
#endif

#ifndef ntMSC
#define ntMSC
#endif

#ifndef ntDOS
#define ntDOS
#endif

#endif /* ctntDOS */
/*************************************/


/*************************************/
#ifdef  ctW16COM_NTP
#ifndef ctntWIN16
#define ctntWIN16
#endif
#endif

#ifdef 	ctntWIN16
#define ctOPT2H
#include "ctoptn.h"
#ifndef ctFeatSRVR_SDK_CSAPI
#define CTREE_IS_USED
#endif

#ifndef ntMSC
#define ntMSC
#endif

#ifndef ntWIN16
#define ntWIN16
#endif

#endif /* ctntWIN16 */
/*************************************/

/*************************************/
#ifdef  ctOPT2H
#define ntPROTOCOLS_ALREADY_SET /* protocols set by c-tree code */
#endif
/*************************************/

/* end of ntfcsrvr.h */
