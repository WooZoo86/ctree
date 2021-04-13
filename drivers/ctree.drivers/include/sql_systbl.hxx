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
 
#ifndef __SYSTABLES_INCLUDED
#define __SYSTABLES_INCLUDED
#include "os_clib.hxx"

#ifdef UNICODE
#if (defined FAIRCOM_CODE && defined ctSQL_FAIRCOM_FCS)
#define SYSTABLES_NUM 47
#else
#define SYSTABLES_NUM 49
#endif
#else /* UNICODE */
#if (defined FAIRCOM_CODE && defined ctSQL_FAIRCOM_FCS)
#define SYSTABLES_NUM 45
#else
#define SYSTABLES_NUM 47
#endif
#endif /* UNICODE */
dh_char_t* sql_system_tables_list[SYSTABLES_NUM] = {
 DH_STRING_LITERAL("sys_chk_constrs"),
 DH_STRING_LITERAL("sys_chkcol_usage"),
 DH_STRING_LITERAL("sys_keycol_usage"),
 DH_STRING_LITERAL("sys_ref_constrs"),
 DH_STRING_LITERAL("sys_tbl_constrs"),
 DH_STRING_LITERAL("sysattachtbls"),
 DH_STRING_LITERAL("sysbigintstat"),
 DH_STRING_LITERAL("syscalctable"),
 DH_STRING_LITERAL("syscharstat"),
 DH_STRING_LITERAL("syscolauth"),
#if (defined FAIRCOM_CODE && defined ctSQL_FAIRCOM_FCS)
 DH_STRING_LITERAL("syscolgroupauth"),
#endif
 DH_STRING_LITERAL("syscolstat"),
 DH_STRING_LITERAL("syscolumns"),
 DH_STRING_LITERAL("sysdatatypes"),
 DH_STRING_LITERAL("sysdatestat"),
 DH_STRING_LITERAL("sysdbauth"),
 DH_STRING_LITERAL("sysdblinks"),
 DH_STRING_LITERAL("sysfloatstat"),
 DH_STRING_LITERAL("sysgroupauth"),
#if !(defined FAIRCOM_CODE && defined ctSQL_FAIRCOM_FCS)
 DH_STRING_LITERAL("sysgroups"),
 DH_STRING_LITERAL("sysgroupusers"),
#endif
 DH_STRING_LITERAL("sysidcase"),
 DH_STRING_LITERAL("sysidentity"),
 DH_STRING_LITERAL("sysidxstat"),
 DH_STRING_LITERAL("sysindexes"),
 DH_STRING_LITERAL("sysintstat"),
 DH_STRING_LITERAL("sysmoneystat"),
#ifdef UNICODE
 DH_STRING_LITERAL("sysncharstat"),
#endif
 DH_STRING_LITERAL("sysnumstat"),
#ifdef UNICODE
 DH_STRING_LITERAL("sysnvarcharstat"),
#endif
 DH_STRING_LITERAL("sysprocbin"),
 DH_STRING_LITERAL("sysproccolumns"),
 DH_STRING_LITERAL("sysprocedures"),
 DH_STRING_LITERAL("sysproctext"),
 DH_STRING_LITERAL("sysrealstat"),
 DH_STRING_LITERAL("syssequences"),
 DH_STRING_LITERAL("syssmintstat"),
 DH_STRING_LITERAL("syssynonyms"),
 DH_STRING_LITERAL("systabauth"),
 DH_STRING_LITERAL("systables"),
 DH_STRING_LITERAL("systblspaces"),
 DH_STRING_LITERAL("systblstat"),
 DH_STRING_LITERAL("systimestat"),
 DH_STRING_LITERAL("systinyintstat"),
 DH_STRING_LITERAL("systrigcols"),
 DH_STRING_LITERAL("systrigger"),
 DH_STRING_LITERAL("systsstat"),
#if !(defined FAIRCOM_CODE && defined ctSQL_FAIRCOM_FCS)
 DH_STRING_LITERAL("sysuserauth"),
#endif
 DH_STRING_LITERAL("sysvarcharstat"),
 DH_STRING_LITERAL("sysviews")
};

dh_boolean is_sql_systable(dh_char_t *tbl)
{
	int rv = 0;
	int min = 0;
	int max = SYSTABLES_NUM - 1;
	int chk = 0;
	
	while (min <= max)
	{
		chk = (min+max)/2;
		rv = os_strcmp(tbl,sql_system_tables_list[chk]);
		if (rv == 0)
			return (1); /* it's a system table*/
		if (rv < 0)
			max = chk - 1;
		else
			min = chk + 1;
	}
	return (0); /*is not a systable*/
}
#endif /*__SYSTABLES_INCLUDED*/
