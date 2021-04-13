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

#ifndef __CTVERS_H__
#define __CTVERS_H__

/* ctSIBLING_VERSIONS: Product Version Numbers References */

#define ctEDGE_MAJOR		3	/* Major version number for RTG.	*/
#define ctRTG_MAJOR		3	/* Major version number for RTG.	*/
#define ctVER_MAJOR		12	/* Major version number.	    	*/
#define ctVER_MINOR		0 	/* Minor version number.	    	*/
#define ctVER_MINI		0	  /* Mini version number.	    	    	*/
#define ctVER_REVSN		144	/* Product Revision number.	*/
#define ctVER_REAL_REVSN	248841	/* Real SVN Revision number.	*/

#define ctVER_BASE_REVSN	0	/* Base SVN Revision number.	*/
#define ctVER_BASE_REAL_REVSN	0	/* Real Base rev. number (if patched).	*/

#define ctVER_BLDYY		20	/* Build year. */
#define ctVER_BLDMM		11	/* Build month. */
#define ctVER_BLDDD		19	/* Build day. */

#define ctVER_BASE_BLDYY	20	/* Base build year. */
#define ctVER_BASE_BLDMM	11	/* Base build month. */
#define ctVER_BASE_BLDDD	19	/* Base build day.*/

#define ctVER_CYEAR		2020	/* Current year.		    */

#ifdef ctPortEDGE
#define ctDISPLAY_MAJOR		ctEDGE_MAJOR
#else
#ifdef ctPortRTG
#define ctDISPLAY_MAJOR		ctRTG_MAJOR
#else
#define ctDISPLAY_MAJOR		ctVER_MAJOR
#endif
#endif

/*
** Use this macro to check if the major.minor.mini code version is greater than
** or equal to the specified version. For example:
**
** #if ctVER_GE(10,0,1) // if version 10.0.1 and later
*/
#define ctVER3_GE(major_ver,minor_ver,mini_ver) \
	((ctVER_MAJOR > (major_ver)) || \
	 (ctVER_MAJOR == (major_ver) && (ctVER_MINOR > (minor_ver) || \
	 ctVER_MINOR == (minor_ver) && ctVER_MINI >= (mini_ver))))

/*
** Use this macro to check if the code version is greater than or equal to the
** specified version. For example:
**
** #if ctVER_GE(9,6) // if version 9.6 and later
*/
#define ctVER_GE(major_ver,minor_ver) ((ctVER_MAJOR > (major_ver)) || (ctVER_MAJOR == (major_ver) && ctVER_MINOR >= (minor_ver)))

/*
** Use this macro to check if the code version is less than the specified
** version. For example:
**
** #if ctVER_LT(9,6) // if prior to version 9.6
*/
#define ctVER_LT(major_ver,minor_ver) ((ctVER_MAJOR < (major_ver)) || (ctVER_MAJOR == (major_ver) && ctVER_MINOR < (minor_ver)))

#define stringify2(x) #x
#define stringify(x) stringify2(x)
#define ictconcat2(x,y) x ## y
#define ictconcat(x,y) ictconcat2(x,y)

#ifdef UNICODE
#define ustringify2(x) L ## #x
#define ustringify(x) ustringify2(x)

#define ctPRODUCT_VERSION_STR_UNI stringify(ctVER_MAJOR) L"." \
	ustringify(ctVER_MINOR) L"." ustringify(ctVER_MINI) L"." ustringify(ctVER_REVSN) \
	L"(Build-" ustringify(ctVER_BLDDT) L")"
#endif

#define ctPRODUCT_VERSION_STR	stringify(ctVER_MAJOR) "." \
	stringify(ctVER_MINOR) "." stringify(ctVER_MINI) "." stringify(ctVER_REVSN) \
	"(Build-" stringify(ctVER_BLDDT) ")"

#define ctPRODUCT_VERSION_NUM	ctVER_MAJOR, ctVER_MINOR, ctVER_MINI, ctVER_REVSN

#define ctPRODUCT_COPYRIGHT_RES_STR "Copyright © 1992 - " stringify(ctVER_CYEAR) " FairCom Corporation"

#define ctPRODUCT_COPYRIGHT_STR	"Copyright (C) 1992 - " stringify(ctVER_CYEAR) " FairCom Corporation"
#define ctPRODUCT_COPYRIGHT_YEARS_STR	"1992-" stringify(ctVER_CYEAR)

#if ctVER_BASE_REVSN > 0
#define ctVER_BLDDT	ictconcat(ictconcat(ictconcat(ictconcat(ictconcat(ictconcat(ctVER_BASE_BLDYY,ctVER_BASE_BLDMM),ctVER_BASE_BLDDD),_),ctVER_BLDYY),ctVER_BLDMM),ctVER_BLDDD)
#else
#define ctVER_BLDDT	ictconcat(ictconcat(ctVER_BLDYY,ctVER_BLDMM),ctVER_BLDDD)
#endif

/*^**************************************************/
#ifndef CT_GLOBAL_VERSION
#define CT_GLOBAL_VERSION 	stringify(ctVER_MAJOR.ctVER_MINOR.ctVER_MINI.ctVER_REVSN)
#endif
#ifndef CT_GLOBAL_DISPLAY
#if ctVER3_GE(12,0,0)
#define CT_GLOBAL_DISPLAY 	stringify(ctDISPLAY_MAJOR.ctVER_MINOR.ctVER_MINI.ctVER_REVSN)
#else
#define CT_GLOBAL_DISPLAY 	CT_GLOBAL_VERSION
#endif
#endif
#ifndef CT_GLOBAL_BUILD
#define CT_GLOBAL_BUILD	  	stringify(ctVER_BLDDT)
#endif
/*~**************************************************/

/*^**************************************************/
/* ctSIBLING_PRODUCT_NAME: Product Name References */
#if ctVER3_GE(12,0,0)
#ifdef ctPortEDGE
#define ctPRODUCT_NAME1	"FairCom EDGE Server"
#else
#ifdef ctSQLMTFPG
#define ctPRODUCT_NAME1	"FairCom DB FQL Service"
#else
#ifdef ctPortRTG
#define ctPRODUCT_NAME1	"c-treeRTG Server"
#else
#ifdef ctSQLSRVR
#define ctPRODUCT_NAME1 "FairCom DB SQL Server"
#else
#define ctPRODUCT_NAME1	"FairCom DB Server"
#endif
#endif
#endif
#endif

#else	/* ~12,0,0 */

#ifdef ctPortEDGE
#define ctPRODUCT_NAME1	"c-treeEDGE Server"
#else
#ifdef ctSQLMTFPG
#define ctPRODUCT_NAME1	"c-treeACE FQL Service"
#else
#ifdef ctPortRTG
#define ctPRODUCT_NAME1	"c-treeRTG Server"
#else
#ifdef ctSQLSRVR
#define ctPRODUCT_NAME1 "c-treeACE SQL Server"
#else
#define ctPRODUCT_NAME1	"c-treeACE Server"
#endif
#endif
#endif
#endif



#endif 	/* ~12,0,0 */


/*^**************************************************/
/* ctSIBLING_PRODUCT_NAME: Product Name References */
#if (defined(__CTLANG_C__) || defined(__CTINIT_C__)) /* ctlang.c and ctinit.c */

#if ctVER3_GE(12,0,0)

#ifdef ctPortEDGE
       char *	DACrts = "Startup FairCom EDGE Server - V" ctPRODUCT_VERSION_STR "           ";
       char *	starts = "Startup FairCom EDGE Server - V" ctPRODUCT_VERSION_STR "           ";
       char	signon[]="FairCom EDGE V" CT_GLOBAL_DISPLAY " Server Is Operational    -SN 00000000\n"; /* Build */
       char	DACnon[]="FairCom EDGE V" CT_GLOBAL_DISPLAY " Server Is Operational    -SN 00000000\n"; /* Build */
#else
#ifdef ctSQLMTFPG
       char *	DACrts = "Startup FairCom DB FQL Service - V" ctPRODUCT_VERSION_STR "       ";
       char *	starts = "Startup FairCom DB FQL Service - V" ctPRODUCT_VERSION_STR "       ";
       char	signon[]="FairCom DB  V" CT_GLOBAL_DISPLAY " FQL Service Is Operational-SN 00000000\n"; /* Build */
       char	DACnon[]="FairCom DB  V" CT_GLOBAL_DISPLAY " FQL Service Is Operational-SN 00000000\n"; /* Build */
#else
#ifdef ctPortRTG
       char *	DACrts = "Startup c-treeRTG Server - V" ctPRODUCT_VERSION_STR "            ";
       char *	starts = "Startup c-treeRTG Server - V" ctPRODUCT_VERSION_STR "            ";
       char	signon[]="c-treeRTG V" CT_GLOBAL_DISPLAY " Server Is Operational       -SN 00000000\n"; /* Build */
       char	DACnon[]="c-treeRTG V" CT_GLOBAL_DISPLAY " Server Is Operational       -SN 00000000\n"; /* Build */
#else
#ifdef ctSQLSRVR
       char *	DACrts = "Startup FairCom DB SQL Server - V" ctPRODUCT_VERSION_STR "        ";
       char *	starts = "Startup FairCom DB SQL Server - V" ctPRODUCT_VERSION_STR "        ";
       char	signon[]="FairCom DB V" CT_GLOBAL_DISPLAY " SQL Server Is Operational  -SN 00000000\n"; /* Build */
       char	DACnon[]="FairCom DB V" CT_GLOBAL_DISPLAY " SQL Server Is Operational  -SN 00000000\n"; /* Build */
#else
       char *	DACrts = "Startup FairCom DB Server - V" ctPRODUCT_VERSION_STR "            ";
       char *	starts = "Startup FairCom DB Server - V" ctPRODUCT_VERSION_STR "            ";
       char	signon[]="FairCom DB V" CT_GLOBAL_DISPLAY " Server Is Operational      -SN 00000000\n"; /* Build */
       char	DACnon[]="FairCom DB V" CT_GLOBAL_DISPLAY " Server Is Operational      -SN 00000000\n"; /* Build */
#endif
#endif
#endif
#endif

#else	/* ~12,0,0 */

#ifdef ctPortEDGE
       char *	DACrts = "Startup c-treeEDGE Server - V" ctPRODUCT_VERSION_STR "           ";
       char *	starts = "Startup c-treeEDGE Server - V" ctPRODUCT_VERSION_STR "           ";
       char	signon[]="c-treeEDGE V" CT_GLOBAL_VERSION " Server Is Operational      -SN 00000000\n"; /* Build */
       char	DACnon[]="c-treeEDGE V" CT_GLOBAL_VERSION " Server Is Operational      -SN 00000000\n"; /* Build */
#else
#ifdef ctSQLMTFPG
       char *	DACrts = "Startup c-treeACE FQL Service - V" ctPRODUCT_VERSION_STR "       ";
       char *	starts = "Startup c-treeACE FQL Service - V" ctPRODUCT_VERSION_STR "       ";
       char	signon[]="c-treeACE  V" CT_GLOBAL_VERSION " FQL Service Is Operational -SN 00000000\n"; /* Build */
       char	DACnon[]="c-treeACE  V" CT_GLOBAL_VERSION " FQL Service Is Operational -SN 00000000\n"; /* Build */
#else
#ifdef ctPortRTG
       char *	DACrts = "Startup c-treeRTG Server - V" ctPRODUCT_VERSION_STR "            ";
       char *	starts = "Startup c-treeRTG Server - V" ctPRODUCT_VERSION_STR "            ";
       char	signon[]="c-treeRTG V" CT_GLOBAL_VERSION " Server Is Operational       -SN 00000000\n"; /* Build */
       char	DACnon[]="c-treeRTG V" CT_GLOBAL_VERSION " Server Is Operational       -SN 00000000\n"; /* Build */
#else
#ifdef ctSQLSRVR
       char *	DACrts = "Startup c-treeACE SQL Server - V" ctPRODUCT_VERSION_STR "        ";
       char *	starts = "Startup c-treeACE SQL Server - V" ctPRODUCT_VERSION_STR "        ";
       char	signon[]="c-treeACE V" CT_GLOBAL_VERSION " SQL Server Is Operational   -SN 00000000\n"; /* Build */
       char	DACnon[]="c-treeACE V" CT_GLOBAL_VERSION " SQL Server Is Operational   -SN 00000000\n"; /* Build */
#else
       char *	DACrts = "Startup c-treeACE Server - V" ctPRODUCT_VERSION_STR "            ";
       char *	starts = "Startup c-treeACE Server - V" ctPRODUCT_VERSION_STR "            ";
       char	signon[]="c-treeACE V" CT_GLOBAL_VERSION " Server Is Operational       -SN 00000000\n"; /* Build */
       char	DACnon[]="c-treeACE V" CT_GLOBAL_VERSION " Server Is Operational       -SN 00000000\n"; /* Build */
#endif
#endif
#endif
#endif



#endif 	/* ~12,0,0 */

       /*
       ** NOTE: Code in ctsrvrmaininit() expects that the signon and DACnon
       ** strings end with the 8-digit serial number followed by a newline.
       ** If we change this, we must also change the code in ctsrvrmaininit().
       */
static char*	cpyrgt = "Copyright (c) 1992 - " stringify(ctVER_CYEAR) " FairCom Corporation.\nALL RIGHTS RESERVED.";
#endif /* __CTLANG_C__ */
/*~****************************************************/


/*^*****************************************************/
/*

Here we verify that our REAL SVN Reference numbers (ctVER_REAL_REVSN) are in
sync with our Product Revision numbers (ctVER_REVSN) set above. Below are the
"base anchors" used for each MAJOR.MINOR product reference.

Note: These same ctVER_RC_ANCHOR defines must be same as in fjstamp.c
*/
#define ctVER_RC_ANCHOR 174000

/* Verification */
#ifndef ctVER_RC_ANCHOR
/* RAB:180913: We have deprecated this check for we now increment the rev number by 1 each time */
/* #error No Anchor revision number set */
#endif
#define ctVER_XCROSS_CHECK_REVSN  (ctVER_RC_ANCHOR + ctVER_REVSN)
#if (ctVER_XCROSS_CHECK_REVSN != ctVER_REAL_REVSN)
/* RAB:180913: We have deprecated this check for we now increment the rev number by 1 each time */
/* #error There is a problem with the Revision Numbers */
#endif
#if (ctVER_BASE_REVSN > 0 || ctVER_BASE_REAL_REVSN > 0)
#define ctVER_XCROSS_CHECK_REAL_REVSN  (ctVER_RC_ANCHOR + ctVER_BASE_REVSN)
#if (ctVER_XCROSS_CHECK_REAL_REVSN != ctVER_BASE_REAL_REVSN)
/* RAB:180913: We have deprecated this check for we now increment the rev number by 1 each time */
/* #error There is a problem with the Revision Numbers */
#endif
#endif
/*~**************************************************/

#endif /* ~ __CTVERS_H__ */

/*^**************************************************/
#ifdef __CTLICN_C__			/* ctlicn.c */
#ifndef __CTVERS_H__CTLICN_C__
#define __CTVERS_H__CTLICN_C__
static const char	vrn[]	= "v" ctPRODUCT_VERSION_STR "                   ";
static const char	cpy[]	= "Copyright (c) 1992 - " stringify(ctVER_CYEAR) " FairCom Corporation.";
#endif /* ~__CTVERS_H__CTLICN_C__ */
#endif /* __CTLICN_C__ */
/*~**************************************************/



/*^**************************************************/
#ifdef ctSYSIH				/* ctsysi.h */
#ifndef __CTVERS_H__ctSYSIH
#define __CTVERS_H__ctSYSIH

#if ctVER_MAJOR >= 10

/* 0xC + major(5 bits, 10..41), minor (5 bits, 0..31), revision (20 bits, 1..1048575) */
#define ctVersionBuildId (0xC0000000 + ((ctVER_MAJOR-10) << 25) + (ctVER_MINOR << 20) + ctVER_REVSN)

#else

/* 0xMMmrrrrr */ /* MM is major(+0xA0), m is minor, rrrrr revision */
#if ctVER_REVSN < 10000
#define ctVersionBuildId ictconcat(ictconcat(ictconcat(ictconcat(0xA,ctVER_MAJOR),ctVER_MINOR),0),ctVER_REVSN)
#else
#define ctVersionBuildId ictconcat(ictconcat(ictconcat(0xA,ctVER_MAJOR),ctVER_MINOR),ctVER_REVSN)
#endif

#endif

#endif /* ~__CTVERS_H__ctSYSIH */
#endif /* ctSYSIH */
/*~**************************************************/


/*^**************************************************/
#ifdef __CTKRNL_C__			/* ctkrnl.c */
#ifndef __CTVERS_H__CTKRNL_C__
#define __CTVERS_H__CTKRNL_C__
static char vrsn[] = "v" ctPRODUCT_VERSION_STR; /* DO NOT MODIFY PER COPYRIGHT NOTIFICATION */
#endif /* ~__CTVERS_H__CTKRNL_C__ */
#endif /* __CTKRNL_C__ */
/*~**************************************************/


/*^**************************************************/
#ifdef __FCACTVAT_C__		      /* fcactvat.c */
#ifndef __CTVERS_H__FCACTVAT_C__
#define __CTVERS_H__FCACTVAT_C__
char		suVER[] = "ACTIVATE Faircom Corporation v" ctPRODUCT_VERSION_STR;
char		suVER2[] = "v" ctPRODUCT_VERSION_STR;
#endif /* ~__CTVERS_H__FCACTVAT_C__ */
#endif /* __FCACTVAT_C__ */
/*~**************************************************/


/*^**************************************************/
#ifdef __RENNLM_C__			/* rennlm.c */
#ifndef __CTVERS_H__RENNLM_C__
#define __CTVERS_H__RENNLM_C__
char		suVER[] = "v" ctPRODUCT_VERSION_STR;
#endif /* ~__CTVERS_H__RENNLM_C__ */
#endif /* __RENNLM_C__ */
/*~**************************************************/

/*^**************************************************/
/*

For now, we must manually maintain the Java source in this file:
 ..\sql\src\jdbc\ctreeDriver.java

Approx line 386:
    public int getMajorVersion()
    {
    // ctree version information - major	- Build Info
        return 900;
    }

Approx line 392:
    public int getMinorVersion()
    {
    // ctree version information - minor	- Build Info
        return 11467;
    }
*/
/*~**************************************************/

/*^**************************************************/
#ifdef dh_literals_included	/* dh_literals.h */
#ifndef dh_literals_defs
#define dh_literals_defs
/*
** Define the following macros when dh_literals.h includes this header file.
*/

#define ODBC_FILEVERSION ctPRODUCT_VERSION_NUM
#ifdef UNICODE
#define ACCESS_VERSION ctPRODUCT_VERSION_STR_UNI
#define DRIVER_VERSION ctPRODUCT_VERSION_STR_UNI
#define COPYRIGHT_DATE "1992-" ustringify(ctVER_CYEAR) L"."
#else
#define ACCESS_VERSION ctPRODUCT_VERSION_STR
#define DRIVER_VERSION ctPRODUCT_VERSION_STR
#define COPYRIGHT_DATE "1992-" stringify(ctVER_CYEAR) "."
#endif

#define	DH_MAJOR_VERSION	ctVER_MAJOR
#define	DH_MINOR_VERSION	ctVER_MINOR
#define	DH_SUB_MINOR_VERSION1	ctVER_MINI
#define	DH_SUB_MINOR_VERSION2	ctVER_REVSN
#define	DH_VER_FILEVERSION_STR	CT_GLOBAL_VERSION
#define COPYRIGHT_YEAR1 "1988"
#define COPYRIGHT_YEAR2 ctVER_CYEAR

#define dotNET_PROVIDER_VERSION CT_GLOBAL_VERSION

#endif /* ~dh_literals_defs */
#endif /* dh_literals_included */
/*~**************************************************/

/* end of ctvers.h */
