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

#ifndef ctSQLOVRH
#define ctSQLOVRH

/* Here we can include a header file that is used to override the Dharma internal SQL Capacities */
/* This header file can be used to supply different Dharma #define override files based
on Platform or whatever you wish */

/*^************************************/
/* Here we have an OEM for UPS_BRUCE Project
*/
#ifdef ctPortUPS_BRUCE
#if (defined(WIN32) && !defined(_WIN32_WCE))
#define  ctCTSQLO01_H	"ctsqlo01.h"
#include ctCTSQLO01_H
#endif
#endif
/*~************************************/


/*^************************************/
/* Windows CE Port */
#ifdef 		_WIN32_WCE								/* Windows CE Port */
#include 	"ctsqloce.h"							
#endif
/*~************************************/

/*^************************************/
/* Here we currently used the same file used for our Windows CE Port, yet it is possible, if you
need to, to change this to a file specific for Windows (non0CE).
*/
#if (defined(WIN32) && !defined(_WIN32_WCE))
#include 	"ctsqloce.h"							/* Override internal SQL Capacity Settings (#defines) */
#endif
/*~************************************/

#endif /* ~ctSQLOVRH */
/* end of ctsqlovr.h */
