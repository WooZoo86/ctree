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

#ifndef ctSQLALLH
#define ctSQLALLH
/* Global Header File included into ALL Dharma SQL source code */

/*^************************************/
/* OEM Specific and ctree option Header File */
#include "ct_oem.h"				/* Allow OEM header to globally define to all SQL modules */

/*~************************************/
#ifndef __COMM_API_CXX__
#ifndef __COMM_NIF_CS_CXX__
#ifndef __CTSQLDBS_C__
#ifndef __CTSQLSTP__
#ifndef __CTSQLSYS_C__
#ifndef __DBDEPLOY_CXX__
#ifndef __DBSC_CXX__
#ifndef __DDM_FNS1_CXX__
#ifndef __DDM_FNS4_CXX__
#ifndef __DDM_FNS5_CXX__
#ifndef __DDM_FNS6_CXX__
#ifndef __DDMJAVACACHE_CXX__
#ifndef __DT_BIN_CXX__
#ifndef __GCACHE_CXX__
#ifndef __MSG_LOG_CXX__
#ifndef __MULTIENV_CXX__
#ifndef __PSR_PVTL_CXX__
#ifndef __RDS_ENV_CXX__
#ifndef __RDSPROCS_CXX__
#ifndef __RSS_HDL_CXX__
#ifndef __RSS_MISC_CXX__
#ifndef __RSS_TM_CXX__
#ifndef __SNR_MISC_CXX__
#ifndef __SNR_NW_CXX__
#ifndef __SQL_IAPI_CXX__
#ifndef __SQLSFN2_CXX__
#ifndef __SQLSFN4_CXX__
#ifndef __SQLTRANS_CXX__
#ifndef __SSM_CXX__
#ifndef __STUBCTDB_CXX__
#ifndef __STUBCTDB_CXX__
#ifndef __STUB_ENV_CXX__
#ifndef __STUB_FTS_CXX__
#ifndef __STUB_HDL_CXX__
#ifndef __STUB_IDX_CXX__
#ifndef __STUB_SEG_CXX__
#ifndef __STUB_SEQUENCES_CXX__
#ifndef __STUB_SRVGLOB_CXX__
#ifndef __STUB_STA_CXX__
#ifndef __STUB_THR_CXX__
#ifndef __STUB_TID_CXX__
#ifndef __STUB_TM_CXX__
#ifndef __STUB_TPL_CXX__
#ifndef __SYSCREAT_CXX__
#ifndef __TCP_DMN_CXX__
#ifndef __XEC_EFN2_CXX__
#ifndef __XEC_TBL1_CXX__
#ifndef __XEC_TBL2_CXX__
#ifndef __OS_CLIB_CXX__
#ifndef __SQL_LIB_H__
#ifndef __DOTNET_CXX__
#ifndef __COMM_NIF_SS_CXX__
#ifndef __COMM_NIN_SS_CXX__
#ifndef __CTSQLAPI_CPP__
#ifndef __OS_DHJNI_CXX__

#ifndef ctOPT2H
#define ctOPT2H
#include "ctoptn.h"				/* Bring in ctoptn.h without ctopt2.h */
#undef ctOPT2H
#endif

#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

/*^************************************/
/* Windows CE Port */
#if (defined(FAIRCOM_MOD) && defined(_WIN32_WCE))		/* FAIRCOM_MOD - RAB:051104: Windows CE Port */
#include "ctcrtlce.h"
#endif
/*~************************************/

/*^************************************/
/* Novell NLM Port */
#if (defined(FAIRCOM_MOD) && defined(ctPortNLM))
#include "ctcrtlnv.h"					/* ct C RTL Novell */
#endif
/*~************************************/

/*^************************************/
/* Here we can include a header file that is used to override the Dharma internal SQL Capacities */
#ifdef 		ctSQL_OVERRIDE_CAPACITIES
#include 	"ctsqlovr.h"										/* Override internal SQL Capacity Settings (#defines) */
#endif
/*~************************************/

/*
** Suppress the following warning messages:
**
** warning C4274: #ident ignored; see documentation for #pragma comment(exestr, 'string')
**
** warning C4291: 'void *__cdecl dlink_t::operator new(unsigned int,unsigned char *)' :
** no matching operator delete found; memory will not be freed if initialization throws an exception
*/
#ifdef _MSC_VER
#pragma warning(disable:4274)
#pragma warning(disable:4291)
#endif

/* If using Visual Studio 2005 or later: */
#if ( _MSC_VER >= 1400 )
/* Suppress "'function' was declared deprecated" warning */
#pragma warning(disable : 4996)
#endif

#ifdef ctSQLSRVR
#define CTPERM
#endif

#endif /* ~ctSQLALLH */
/* end of ctsqlall.h */
