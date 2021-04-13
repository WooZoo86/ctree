
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
 * Date             : 2014-FEB-19
 * Title            : Dharma/SQL Access 14.0 Release.
 * ---------------------------------------------------------------------
 */

/* DC777 Begin */
/* Esqlc uses the C preprocessor to allow #defines in .pc files
 * because the preprocessor evaluates #defines. It is necessary
 * to be able to include several #defines again when the actual
 * .c file is generated, so move those #defines to a seperate 
 * file.
 */

#if !defined DH_STRLIT_INCLUDED
#define DH_STRLIT_INCLUDED 1
#if !defined DH_STRING_LITERAL
#ifdef _UNICODE
#define DH_STRING_LITERAL(string_lit)   _T(string_lit)
#else
#define DH_STRING_LITERAL(string_lit)   string_lit
#endif 
#endif

#if !defined (DFLT_TPE_CHAR)
#ifdef _UNICODE
#define CSM_TPE_CHAR     TPE_DT_CHAR
#define CSM_TPE_VARCHAR  TPE_DT_VARCHAR
#define DFLT_TPE_CHAR    TPE_DT_NCHAR
#define DFLT_TPE_VARCHAR TPE_DT_NVARCHAR
#else
#define CSM_TPE_CHAR     TPE_DT_NCHAR
#define CSM_TPE_VARCHAR  TPE_DT_NVARCHAR
#define DFLT_TPE_CHAR    TPE_DT_CHAR
#define DFLT_TPE_VARCHAR TPE_DT_VARCHAR
#endif
#define TPE_DT_CHAR 1
#endif
#endif
/* DC777 End */
