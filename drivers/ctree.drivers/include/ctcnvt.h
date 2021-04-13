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



/* ================================================================ */
/*
File:	ConvertUTF.h
Author: Mark E. Davis
 * Copyright 1994-1999 IBM Corp.. All rights reserved.
 * 
 * IBM Corp. grants the user a nonexclusive right and license to use, execute,
 * display, modify, and prepare and/or have prepared derivative works of the
 * code, including but not limited to creating software products which
 * incorporate the code or derivative works thereof.
 * 
 * IBM Corp. grants the user a right and license to reproduce and distribute
 * the code as long as this entire copyright notice is reproduced in the code
 * or reproduction.
 * 
 * The code is provided AS-IS, and IBM Corp. disclaims all warranties,
 * either express or implied, including, but not limited to implied
 * warranties of merchantability and fitness for a particular purpose.
 * In no event will IBM Corp. be liable for any damages whatsoever (including,
 * without limitation, damages for loss of business profits, business
 * interruption, loss of business information, or other pecuniary
 * loss) arising out of the use or inability to use this code, even
 * if IBM Corp. has been advised of the possibility of such damages.
 * Because some states do not allow the exclusion or limitation of
 * liability for consequential or incidental damages, the above
 * limitation may not apply to you.
*/
/* ================================================================ */

/*
#include <stdio.h>
#include <stdlib.h>
 #include <types.h>
#include <string.h>
*/

/* ================================================================ */
/*	The following 4 definitions are compiler-specific.
	I would use wchar_t for UCS2/UTF16, except that the C standard
	does not guarantee that it has at least 16 bits, so wchar_t is
	no less portable than unsigned short!
*/

typedef ULONG	UCS4;
typedef UCOUNT	UCS2;
typedef UCOUNT	UTF16;
typedef UTEXT	UTF8;

#ifdef ctPortHP9000
#undef ctCONST
#define ctCONST /* */
#endif

#define kReplacementCharacter (UCS4)0x0000FFFD
ctCONST UCS4 kMaximumUCS2 =		(ULONG)0x0000FFFF;
ctCONST UCS4 kMaximumUTF16 =		(ULONG)0x0010FFFF;
ctCONST UCS4 kMaximumUCS4 =		(ULONG)0x7FFFFFFF;
/* ================================================================ */
/*	Each of these routines converts the text between *sourceStart and 
sourceEnd, putting the result into the buffer between *targetStart and
targetEnd. Note: the end pointers are *after* the last item: e.g. 
*(sourceEnd - 1) is the last item.

	The return result indicates whether the conversion was successful,
and if not, whether the problem was in the source or target buffers.

	After the conversion, *sourceStart and *targetStart are both
updated to point to the end of last text successfully converted in
the respective buffers.
*/

typedef enum {
	ok_ok, 			/* conversion successful */
	sourceExhausted,	/* partial character in source, but hit end */
	targetExhausted		/* insuff. room in target for conversion */
} ConversionResult;

#define ConvertUCS4toUTF16	ctConvertUCS4toUTF16
#define ConvertUTF16toUCS4	ctConvertUTF16toUCS4
#define ConvertUTF16toUTF8	ctConvertUTF16toUTF8
#define ConvertUTF8toUTF16	ctConvertUTF8toUTF16
#define ConvertUCS4toUTF8	ctConvertUCS4toUTF8
#define ConvertUTF8toUCS4	ctConvertUTF8toUCS4

#ifdef PROTOTYPE

ConversionResult	ConvertUCS4toUTF16 (
		UCS4** sourceStart, ctCONST UCS4* sourceEnd, 
		UTF16** targetStart, ctCONST UTF16* targetEnd);

ConversionResult	ConvertUTF16toUCS4 (
		UTF16** sourceStart, UTF16* sourceEnd, 
		UCS4** targetStart, ctCONST UCS4* targetEnd);

ConversionResult	ConvertUTF16toUTF8 (
		UTF16** sourceStart, ctCONST UTF16* sourceEnd, 
		UTF8** targetStart, ctCONST UTF8* targetEnd);
		
ConversionResult	ConvertUTF8toUTF16 (
		UTF8** sourceStart, UTF8* sourceEnd, 
		UTF16** targetStart, ctCONST UTF16* targetEnd);

ConversionResult	ConvertUCS4toUTF8 (
		UCS4** sourceStart, ctCONST UCS4* sourceEnd, 
		UTF8** targetStart, ctCONST UTF8* targetEnd);
		
ConversionResult	ConvertUTF8toUCS4 (
		UTF8** sourceStart, UTF8* sourceEnd, 
		UCS4** targetStart, ctCONST UCS4* targetEnd);

#else /* ~PROTOTYPE */

ConversionResult	ConvertUCS4toUTF16 ();
ConversionResult	ConvertUTF16toUCS4 ();
ConversionResult	ConvertUTF16toUTF8 ();
ConversionResult	ConvertUTF8toUTF16 ();
ConversionResult	ConvertUCS4toUTF8 ();
ConversionResult	ConvertUTF8toUCS4 ();

#endif /* ~PROTOTYPE */

/*
End of File:	ConvertUTF.H
*/
/* ================================================================ */

/* end of ctcnvt.h */
