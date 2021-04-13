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

#include "ctstdr.h"
#include "ctoptn.h"

#if defined(ctPortWIN64)
#include "config.h.x64"

#elif defined(ctPortWIN32)
#include "config.h.w32"

#elif defined(ctPortMACOSX_64)
#include "config.h.osx64"

#elif defined(ctPortMACOSX)
#include "config.h.osx32"

#elif defined(ctPortLINUX_64)
#include "config.h.linux26_64"

#elif defined(ctPortLINUX)
#include "config.h.linux26_32"

#elif defined(ctPortRS6000_64)
#include "config.h.aix7164"

#elif defined(ctPortRS6000)
#include "config.h.aix7132"

#elif defined(ctPortSOLARIS_64)
#include "config.h.sol1164"

#elif defined(ctPortSOLARIS)
#include "config.h.sol1132"

#else
#error json-c-0.13 config.h has not been set up for this platform.
#endif

/* end of config.h */
