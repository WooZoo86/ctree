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
#ifndef _CTDBUTF8_H_
#define _CTDBUTF8_H_
/*^****************************************************************************\
*
*   Header Files
*
\******************************************************************************/
#include "ctstdr.h"
#include "ctoptn.h"
#ifdef ctCLIENT
#define ctCLIENTcore
#endif
#ifdef ctThrdFPG
#define CTPERM
#endif
#include "cterrc.h"
#include "ctstrc.h"
#include "ctgvar.h"
#include "ctv7v6.h" /* ensure backward compatibility with c-tree Plus v6 */
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Check for UNICODE
*
\******************************************************************************/
#ifdef ctUNICODE
#define ctdbUNICODE
#endif /* ctUNICOIDE */

/*^****************************************************************************\
*
*   The rest of the header file is only available of ctdbUNICODE is defined
*
\******************************************************************************/
#ifdef ctdbUNICODE
#ifdef ctPortWIN32
#if _MSC_VER > 1500
#include <stdint.h>
#endif
#else
#include <stdint.h>
#endif
#define  ctUNICODE_UTF8_H	"unicode/utf8.h"
#define  ctUNICODE_UCHAR_H	"unicode/uchar.h"
#include ctUNICODE_UTF8_H
#include ctUNICODE_UCHAR_H
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Protect against C++ compilers
*
\******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTDB macros for UTF-8 support
*
\******************************************************************************/
#define ctdb_u8_islower(c)		(u_isULowercase((UChar32)(c)) ? YES : NO)
#define ctdb_u8_isupper(c)		(u_isUUppercase((UChar32)(c)) ? YES : NO)
#define ctdb_u8_isdigit(c)		(u_isdigit((UChar32)(c)) ? YES : NO)
#define ctdb_u8_isxdigit(c)		(u_isxdigit((UChar32)(c)) ? YES : NO)
#define ctdb_u8_isletter(c)		(u_isUAlphabetic((UChar32)(c)) ? YES : NO)
#define ctdb_u8_isalpha(c)		(u_isalpha((UChar32)(c)) ? YES : NO)
#define ctdb_u8_isalnum(c)		(u_isalnum((UChar32)(c)) ? YES : NO)
#define ctdb_u8_isspace(c)		(u_isUWhiteSpace((UChar32)(c)) ? YES : NO)
#define ctdb_u8_toupper(c)		((UChar32)u_toupper((UChar32)(c)))
#define ctdb_u8_tolower(c)		((UChar32)u_tolower((UChar32)(c)))
#define ctdb_u8_digit(c,radix)	((NINT)u_digit((c),(radix)))
/*~****************************************************************************/

/*^****************************************************************************\
*
*   CTDB functions for UTF-8 support
*
\******************************************************************************/
NINT ctDECL ctdb_u8_stricmp(cpTEXT s1, cpTEXT s2);
NINT ctDECL ctdb_u8_strcmp(cpTEXT s1, cpTEXT s2);
NINT ctDECL ctdb_u8_strncmp(cpTEXT s1, cpTEXT s2, NINT n);
pTEXT ctDECL ctdb_u8_strupper(cpTEXT s1, pTEXT s2, NINT size);
pTEXT ctDECL ctdb_u8_strlower(cpTEXT s1, pTEXT s2, NINT size);
NINT ctDECL ctdb_u8TOu16(const TEXT * u8str, pWCHAR u16str, NINT u16size);
NINT ctDECL ctdb_u16TOu8(const WCHAR * u16str, pTEXT u8str, NINT u8size);
NINT ctDECL ctdb_u8TOu16x(const TEXT * u8str, VRLEN u8size, pWCHAR u16str, NINT u16size, NINT chkpad);
NINT ctDECL ctdb_u16TOu8x(const WCHAR * u16str, VRLEN u16chr, pTEXT u8str, NINT u8size, NINT chkpad);
NINT ctDECL ctdb_u8TOu32(const TEXT * u8str, pULONG u32str, NINT u32size);
NINT ctDECL ctdb_u32TOu8(const ULONG * u32str, pTEXT u8str, NINT u8size);
NINT ctDECL ctdb_u16TOu32(const UCOUNT * u16str, pULONG u32str, NINT u32size);
NINT ctDECL ctdb_u32TOu16(const ULONG * u32str, pWCHAR u16str, NINT u16size);
NINT ctDECL ctdb_u16_validate(const UCOUNT * u16str,NINT u16size);

/*~****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* ctUNICODE */
#endif /* _CTDBUTF8_H_ */

/* end of ctdbutf8.h */
