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

#ifndef ctSYSIH
#define ctSYSIH

#include "ctvers.h"			/* We now have a centralized place for Build Info in ctvers.h */


/*******************************************************/
/* version defines */

#ifdef ctNOVCHK
#undef ctNOVCHK
#endif
#define ctNOVCHK         0x77700000L

#ifdef ctV6424F
#undef ctV6424F
#endif
#define ctV6424F         0x7776424FL

#ifdef ctV6526A
#undef ctV6526A
#endif
#define ctV6526A         0x7776526AL

#ifdef ctV6626B
#undef ctV6626B
#endif
#define ctV6626B         0x7776626BL

#ifdef ctV6728B
#undef ctV6728B
#endif
#define ctV6728B         0x7776728BL

#ifdef ctV6728C
#undef ctV6728C
#endif
#define ctV6728C         0x7776728CL

#ifdef ctV6829A
#undef ctV6829A
#endif
#define ctV6829A         0x7776829AL

#ifdef ctV6830A
#undef ctV6830A
#endif
#define ctV6830A         0x7776830AL

#ifdef ctV6932A
#undef ctV6932A
#endif
#define ctV6932A         0x7776832AL

#ifdef  ctV6A34A
#undef  ctV6A34A
#endif
#define ctV6A34A         0x7776A34AL

#ifdef  ctV6C40A
#undef  ctV6C40A
#endif
#define ctV6C40A         0x7776C40AL

#ifdef  ctV7A54A
#undef  ctV7A54A
#endif
#define ctV7A54A         0x7777A54AL

#ifdef  ctV7C60A
#undef  ctV7C60A
#endif
#define ctV7C60A         0x7777C60AL

/* New released as of 2/2003 for .12 releases */
#ifdef  ctV6C062C
#undef  ctV6C062C
#endif			  
#define ctV6C062C         0x7776C62CL

#ifdef  ctV7C082C
#undef  ctV7C082C
#endif
#define ctV7C082C         0x7777C82CL

#ifdef  ctV8C112C
#undef  ctV8C112C
#endif
#define ctV8C112C         0x778C112CL

#ifdef  ctV8E840A
#undef  ctV8E840A
#endif
#define ctV8E840A         0x778E840AL

#define ctVERSIONID90beta 0x7790000BL	/* v9.0 beta release */

#define ctVERSIONID90	  0x77900000L	/* v9.0 release */

#define ctVERSIONID100	  0x77A00000L	/* v10.0 release */

/* ctSIBLING_VERSIONID: Add new version ID definition here */


/* ctSIBLING_VERSIONID: Change to reflect current shipping working version */
#if ctVER_MAJOR > 9
#define ctVersionid ctVERSIONID100	/* v10.0 release */
#else
#define ctVersionid ctVERSIONID90	/* v9.0 release */
#endif



/**********************************/

#define ctPortid88OPEN			0x11222211L
#define ctPortidATTUNIX386		0x11333311L
#define ctPortidVINES			0x11444411L
#define ctPortidCHORUS			0x11555511L
#define ctPortidOS2_2x			0x11666611L
#define ctPortidALPHA			0x11777711L
#define ctPortidHP9000			0x11888811L
#define ctPortidINTERACTIVE		0x11999911L
#define ctPortidLYNXOS386		0x11AAAA11L
#define ctPortidAPPLEAUX		0x11BBBB11L
#define ctPortidNECEWS4800		0x11CCCC11L
#define ctPortidWNT386			0x11DDDD11L
#define ctPortidQNX			0x11EEEE11L
#define ctPortidRS6000			0x11FFFF11L
#define ctPortidQNXRTP			0x22111122L
#define ctPortidOS2_1x			0x22333322L
#define ctPortidSCO386			0x22444422L
#define ctPortidMSDOS			0x22555522L
#define ctPortidSUN41			0x22666622L
#define ctPortidMSWINDOWS		0x22777722L
#define ctPortidSOLARIS			0x22888822L
#define ctPortidNLM			0x22999922L
#define ctPortidMIPSABI			0x22AAAA22L
#define ctPortidAPPLE7			0x22BBBB22L
#define ctPortidWIN95			0x22CCCC22L
#define ctPortidLINUX			0x22DDDD22L
#define ctPortidSYSMAN			0x22EEEE22L
#define ctPortidWNTALPHA		0x22FFFF22L
#define ctPortidWNTMIPS			0x33111133L
#define ctPortidSOL386			0x33222233L
#define ctPortidWindowsNT_PowerPC	0x33333333L
#define ctPortidSolarisPowerPC		0x33444433L
#define ctPortid386BSD			0x33555533L
#define ctPortidSGI			0x33666633L
#define ctPortidSPARC_LINUX		0x33777733L
#define ctPortidMACOSX			0x33888833L
#define ctPortidMACLNX			0x33999933L
#define ctPortidNETBSD386		0x33AAAA33L
#define ctPortidDGU386			0x33BBBB33L
#define ctPortidWINCE			0x33CCCC33L
#define ctPortidNCRUNIX386		0x33DDDD33L
#define ctPortidRASPBIAN		0x33EEEE33L


/* Please use 		0x33FFFF33L next and change this comment */

#ifdef ctPort88OPEN
#define ctPortid	ctPortid88OPEN
#endif

#ifdef ctPortATTUNIX386
#define ctPortid	ctPortidATTUNIX386
#endif

#ifdef ctPortVINES
#ifdef ctSRVR
#define ctPortid	ctPortidVINES
#endif
#endif

#ifdef ctPortCHORUS
#define ctPortid	ctPortidCHORUS
#endif

#ifdef ctPortOS2_2x
#define ctPortid	ctPortidOS2_2x
#endif

#ifdef ctPortALPHA
#define ctPortid	ctPortidALPHA
#endif

#ifdef ctPortHP9000
#define ctPortid	ctPortidHP9000
#endif

#ifdef ctPortINTERACTIVE
#define ctPortid	ctPortidINTERACTIVE
#endif

#ifdef ctPortLYNXOS386
#define ctPortid	ctPortidLYNXOS386
#endif

#ifdef ctPortAPPLEAUX
#define ctPortid	ctPortidAPPLEAUX
#endif

#ifdef ctPortNECEWS4800
#define ctPortid	ctPortidNECEWS4800
#endif

#ifndef ctPortWINCE	/* Windows CE */
#ifdef ctPortWNT386
#ifndef ctPortid
#define ctPortid	ctPortidWNT386
#endif
#endif
#endif

#ifdef ctPortQNX
#define ctPortid	ctPortidQNX
#endif

#ifdef ctPortRS6000
#define ctPortid	ctPortidRS6000
#endif

#ifdef ctPortQNXRTP
#define ctPortid	ctPortidQNXRTP
#endif

#ifdef ctPortOS2_1x
#define ctPortid	ctPortidOS2_1x
#endif

#ifdef ctPortSCO386
#define ctPortid	ctPortidSCO386
#endif

#ifdef ctPortMSDOS
#ifndef ctPortWNT386
#define ctPortid	ctPortidMSDOS
#endif
#endif

#ifdef ctPortSUN41
#define ctPortid	ctPortidSUN41
#endif

#ifdef ctPortMSWINDOWS
#define ctPortid	ctPortidMSWINDOWS
#endif

#ifdef ctPortSOLARIS
#define ctPortid	ctPortidSOLARIS
#endif

#ifdef ctPortNLM
#define ctPortid	ctPortidNLM
#endif

#ifdef ctPortMIPSABI
#define ctPortid	ctPortidMIPSABI
#endif

#ifdef ctPortAPPLE7
#define ctPortid	ctPortidAPPLE7
#endif

#ifdef ctPortWIN95
#ifndef ctPortid
#define ctPortid	ctPortidWIN95
#endif
#endif

#ifndef ctPortFREEBSD8
#ifndef ctPortMACLNX	/* Apple Linux (PPC) */
#ifndef ctPortSPARC_LINUX
#ifndef ctPortRASPBIAN
#ifdef  ctPortLINUX 	/* Intel based LINUX */
#define ctPortid	ctPortidLINUX
#endif
#endif
#endif
#endif
#endif

#ifdef ctPortSYSMAN
#define ctPortid	ctPortidSYSMAN
#endif

#ifdef ctPortWNTALPHA
#define ctPortid	ctPortidWNTALPHA
#endif

#ifdef ctPortWNTMIPS
#define ctPortid	ctPortidWNTMIPS
#endif

#ifdef ctPortSOL386
#define ctPortid	ctPortidSOL386
#endif

#ifdef ctPortWindowsNT_PowerPC     /* Windows NT Power PC */
#define ctPortid	ctPortidWindowsNT_PowerPC
#endif

#ifdef ctPortSolarisPowerPC     /* Solaris Power PC */
#define ctPortid	ctPortidSolarisPowerPC
#endif

#ifdef ctPort386BSD     /* 386 BSD UNIX */
#define ctPortid	ctPortid386BSD
#endif

#ifdef ctPortFREEBSD8
#ifndef ctPortid
#define ctPortid	ctPortid386BSD
#endif
#endif

#ifdef ctPortSGI	/* SGI Unix */
#define ctPortid	ctPortidSGI
#endif

#ifdef ctPortSPARC_LINUX	/* SUN SPARC LINUX */
#define ctPortid	ctPortidSPARC_LINUX
#endif

#ifdef ctPortMACOSX	/* MAC OS X or later*/
#define ctPortid	ctPortidMACOSX
#endif


#ifdef ctPortMACLNX	/* Apple Linux (PPC) */
#define ctPortid	ctPortidMACLNX
#endif

#ifdef ctPortNETBSD386     /* NetBSD Intel */
#define ctPortid	ctPortidNETBSD386
#endif

#ifdef ctPortDGU386     /* DATA GENERAL AVIION (Intel) */
#define ctPortid	ctPortidDGU386
#endif

#ifdef ctPortWINCE	/* Windows CE */
#define ctPortid	ctPortidWINCE
#endif

#ifdef ctPortNCRUNIX386
#define ctPortid	ctPortidNCRUNIX386
#endif

#ifdef ctPortRASPBIAN
#define ctPortid ctPortidRASPBIAN
#endif

#endif /* ctSYSIH */

/* end of ctsysi.h */
