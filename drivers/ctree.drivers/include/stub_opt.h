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
 *	In addition:
 *	This Module also contains Proprietary Information of
 *	Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 *	and should be treated as Confidential.
 *	
 *	Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *	Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *	
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
 
 /*

	Stub options

	STUB_ROWID_START
		Return 0 if ROWID should start at zero
		Return 1 if ROWID should start at one

	STUB_PADCHAR
		Return the pad char
		By default the pad char is space

	STUB_HUGEFILE
		Return 0 if tables are to be created without CTCREATE_HUGEFILE
		Return 1 if tables are to be created with CTCREATE_HUGEFILE

	STUB_OWNERNAME
		Return 0 if tables are to be created without the owner name
		Return 1 if tables are to be created with the owner name
	STUB_SYSSUPERFILE
		Return 0 if systables are not to be created in the dictionary superfile
		Return 1 if systables are to be created in the dictionary superfile

	STUB_CTREE_FILE_PERM
		Return the file permission

	STUB_JQL_SERVER
		Return 0 if the server is a standard SQL server
		Return 1 if the server is a JQL server

	STUB_MAX_FLDLEN
		Return the value of TPE_MAX_FLDLEN which is the maximum length of a non LONG* field

	STUB_DUPKEY_ERROR
		Enables dupkey error based on index number

	STUB_STMT_TIMES
		Return 1 if "SQL_DEBUG LOG_TIMES" is on

	STUB_STMT_TIMES_FETCH
		Return 1 if "SQL_DEBUG LOG_TIMES_FETCH" is on
	
	STUB_PARTIAL_SEG
		Return 0 if partial segment is not supported
		Return 1 if partial segment is supported but not enabled
		Return 2 if partial segment is supported and enabled

	STUB_MAX_FIELDS
		Return the value of TPE_MAX_FIELDS which is the maximum nuomber of fields per table

	STUB_CTSTRING_VARCHAR
		Return 1 if SQL_OPTION CTSTRING_VARCHAR is on

	STUB_BADDATES_ASNULL
		Return 1 if SQL_OPTION BADDATES_ASNULL is on
*/

#ifndef __STUB_OPT_H
#define __STUB_OPT_H

#ifdef __cplusplus
extern "C" {
#endif
#define STUB_ROWID_START	1
#define STUB_PADCHAR		2
#define STUB_HUGEFILE		3
#define STUB_OWNERNAME		4
#define STUB_SYSSUPERFILE	5
#define STUB_CTREE_FILE_PERM	6
#define STUB_JQL_SERVER		7
#define STUB_MAX_FLDLEN		8
#define STUB_DUPKEY_ERROR	9
#define STUB_STMT_TIMES		10
#define STUB_STMT_TIMES_FETCH	11
#define STUB_USE_PUSHDOWN	12
#define STUB_PARTIAL_SEG	13
#define STUB_NOROWID		14
#define STUB_NORECBYT		15
#define STUB_NO_AUTO_ROLLBACK	16
#define STUB_DISAB_PUSHDOWN	17 /* disable the pushdown support*/
#define STUB_MAX_FIELDS		18
#define STUB_INDEXWITHTABLE 19 /*ctSQL_AMBIDX*/
#define STUB_CTSTRING_VARCHAR 20
#define STUB_MAXIDXENTRIES	21
#define STUB_MAX_IDSLEN		22
#define STUB_BADDATES_ASNULL	23
#define STUB_HOTALTER	24
#define STUB_DELMRTHOST 25
#define STUB_BADTIMES_ASNULL 26

#define STUB_NO_REVERSE_INDEX 27
#define STUB_PARTIION_OPEN_COST 28
#define STUB_MAX_ISOLATION_LVL 29
#define STUB_PRESERVE_NO_LOCK 30
#define STUB_SQLCALLBACKDLL 31
#define STUB_SQLNOSELECTIVITY 32
#define STUB_SQLNOUSERVALIDATION 33
#define STUB_SQLNOCARDINALITY 34
#define STUB_SQLOLDDELFLDLEN 35
#define STUB_SQLNOMRTSEL 36
#define STUB_SQLNOMRTCARD 37
#define STUB_SQLUSEDHCASE 38
#define STUB_SQLUSEMM 39
#define STUB_SQLNOCOST 40
#define STUB_SQLFPUTFGET 41
#define STUB_TRACED_ERROR 42
#define STUB_DROP_IMPORTED 43
#define STUB_STMT_DDM_LEVEL 44
#define STUB_CHARSET_SUPPORTED 45
#define STUB_SQLFPUTFGETRW 46
#define STUB_PIDNODE 47
#define STUB_INT_DIV_INT_IS_INT 48


int stub_options(int);

#ifdef __cplusplus
}
#endif
#endif
/* end of stub_srvglob.h */
