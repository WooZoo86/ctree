
/*
 *	Copyright (C) Dharma Systems Inc.        1988-2011.
 *	Copyright (C) Dharma Systems (P) Ltd.    1988-2011.
 *
 *	This Module contains Proprietary Information of
 *	Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 *	and should be treated as Confidential.
 */

/* --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC777
 * Date             : 2014-MAY-19
 * Title            : Dharma/SQL Access 14.0 Release.
 * ---------------------------------------------------------------------
 */

/* DC777 Begin */
#ifndef os_strfnc_included
#define os_strfnc_included

#include "string.h"

inline  dh_char_t    *os_strcpy (dh_char_t * str1, const dh_char_t * str2) 
{ 
    return (str2 ? (dh_char_t *)(_tcscpy (str1, (_TCHAR *)str2)) : (dh_char_t *)(_tcscpy(str1,(_TCHAR *)"")) );
}

inline dh_char_t *os_strncpy( dh_char_t *destptr, const dh_char_t * srcptr, dh_i32_t no_of_char )
{
    return (_tcsncpy (destptr, srcptr, no_of_char)) ;
}
#endif
/* DC777 End */
