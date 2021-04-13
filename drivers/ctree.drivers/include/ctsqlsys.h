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

#ifndef __CTSQLSYS_H__
#define __CTSQLSYS_H__

#define  ctSQL_LIB_H	"sql_lib.h"
#include ctSQL_LIB_H


/* Added for syscreat tool  */
#ifdef errno 
#undef errno
#endif
#define errno GetLastError()

extern dh_i32_t sys_main (dh_i32_t, dh_char_t **);
extern dh_i32_t server_main (dh_i32_t ,dh_char_t **);
extern NINT dmnxx_main(pNLONG a_args);
extern NINT sysxx_main(pNLONG a_args);

#ifdef PAOLO_REMOVED_DH14_MERGE
#ifdef DH_OS_UNIX
inline dh_char_t    *os_strcpy (dh_char_t *str1, const dh_char_t *str2)
{
#ifdef UNICODE
	return (str2 ? wcscpy (str1, str2) : (dh_char_t *) 0);
#else
	return (str2 ? strcpy (str1, str2) : (dh_char_t *) 0);
#endif
}
#else  /* ~DH_OS_UNIX */
inline  dh_char_t   *os_strcpy (dh_char_t *str1, const dh_char_t *str2)
{
	return (str2 ? (dh_char_t *)(_tcscpy (str1, (_TCHAR *)str2)) : (dh_char_t *)(_tcscpy(str1,(_TCHAR *)"")) );
}
#endif /* ~DH_OS_UNIX */
#endif /*PAOLOREMOVED*/

#ifdef ctPortNLM	/* RAB: 070521: the ctsqlsys was coming up with undefined os_strcpy on NLM */
#ifndef os_strcpy	/* Perhaps we resticted some header include'ds which causes this */
#ifdef UNICODE		/* This is an EZ work around */
#define os_strcpy	wcscpy
#else  /* ~UNICODE */
#define os_strcpy	strcpy
#endif /* ~UNICODE */
#endif
#endif

#endif  /*  __CTSQLSYS_H__  */

/* end of ctsqlsys.h */

