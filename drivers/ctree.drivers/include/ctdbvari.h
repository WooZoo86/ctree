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

#ifndef _CTDBVARI_H_
#define _CTDBVARI_H_

/*^****************************************************************************\
*
*   Header Files
*
\******************************************************************************/
#include "ctdbsdk.h"


/*^****************************************************************************\
*
*   Protect against C++ compilers
*
\******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


/*^****************************************************************************\
*
*   CTDBTYPE Extension
*
\******************************************************************************/
#define CT_EMPTY		0		/* variant is empty: has no value	  	  	 */
#define CT_NULL			1		/* variant is NULL						  	 */

/*^****************************************************************************\
*
*   CTVARCHAR
*	structure to store string and binary data
*
\******************************************************************************/
typedef struct tagCTVARCHAR		CTVARCHAR, ctMEM* pCTVARCHAR, ctMEM* ctMEM* ppCTVARCHAR;

struct tagCTVARCHAR
{
	CTBOOL	byref;				/* indicate if string is by reference or not  */
	VRLEN	size;				/* allocated size in bytes					  */
	VRLEN	len;				/* length in bytes							  */
	pTEXT	data;				/* string data								  */
};
/*^****************************************************************************\
*
*   CTVARIANT
*	c-tree variant data structure
*	references are used for string and binary types only.
*
\******************************************************************************/
typedef struct tagCTVARIANT		CTVARIANT, ctMEM* pCTVARIANT, ctMEM* ctMEM* ppCTVARIANT;

struct tagCTVARIANT
{
	CTDBTYPE		vtype;		/* variant type, base on c-tree field types   */
	CTDATE_TYPE		datef;		/* date default format, used for conversion	  */
	CTTIME_TYPE		timef;		/* time default format, used for conversion	  */
	union
	{
		LONG		vint;		/* signed integer values 					  */
		ULONG		vuint;		/* unsigned integer values 					  */
		CTBIGINT 	vbig;		/* signed 64 bits integer values			  */
		CTMONEY		vmoney;		/* 32 bit currency value					  */
		CTCURRENCY	vcurrency;	/* 64 bit currency value					  */
		CTFLOAT		vfloat;		/* floating point values 					  */
		pCTNUMBER	vbcd;		/* numeric values							  */
		pCTVARCHAR	vchar;		/* string or binary data					  */
	} var;
};


/*^****************************************************************************\
*
*   function prototype
*	implemented in ctdbvar.c
*
\******************************************************************************/

#ifdef PROTOTYPE

ctdbEXPORT pCTVARIANT ctDECL ctvarAlloc(void);
ctdbEXPORT pCTVARIANT ctDECL ctvarDuplicate(pCTVARIANT pVar);
ctdbEXPORT pCTVARIANT ctDECL ctvarFree(pCTVARIANT pVar);
ctdbEXPORT CTDBRET ctDECL ctvarCopy(pCTVARIANT Dest, pCTVARIANT Source);
ctdbEXPORT CTDBRET ctDECL ctvarClear(pCTVARIANT pVar);
ctdbEXPORT CTBOOL ctDECL ctvarIsString(pCTVARIANT pVar);
ctdbEXPORT CTBOOL ctDECL ctvarIsNumeric(pCTVARIANT pVar);
ctdbEXPORT CTBOOL ctDECL ctvarIsInteger(pCTVARIANT pVar);
ctdbEXPORT CTBOOL ctDECL ctvarIsDateOrTime(pCTVARIANT pVar);
ctdbEXPORT CTBOOL ctDECL ctvarIsNumber(pCTVARIANT pVar);
ctdbEXPORT CTBOOL ctDECL ctvarIsEmpty(pCTVARIANT pVar);
ctdbEXPORT CTBOOL ctDECL ctvarIsNull(pCTVARIANT pVar);
ctdbEXPORT CTBOOL ctDECL ctvarIsByref(pCTVARIANT pVar);
ctdbEXPORT CTDBTYPE ctDECL ctvarGetType(pCTVARIANT pVar);
ctdbEXPORT CTDBRET ctDECL ctvarSetDateType(pCTVARIANT pVar, CTDATE_TYPE DateType);
ctdbEXPORT CTDBRET ctDECL ctvarSetTimeType(pCTVARIANT pVar, CTTIME_TYPE TimeType);
ctdbEXPORT CTDATE_TYPE ctDECL ctvarGetDateType(pCTVARIANT pVar);
ctdbEXPORT CTTIME_TYPE ctDECL ctvarGetTimeType(pCTVARIANT pVar);
ctdbEXPORT CTDBRET ctDECL ctvarGetBool(pCTVARIANT pVar, pCTBOOL pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetSigned(pCTVARIANT pVar, pCTSIGNED pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetUnsigned(pCTVARIANT pVar, pCTUNSIGNED pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetDate(pCTVARIANT pVar, pCTDATE pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetTime(pCTVARIANT pVar, pCTTIME pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetDateTime(pCTVARIANT pVar, pCTDATETIME pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetBigint(pCTVARIANT pVar, pCTBIGINT pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetMoney(pCTVARIANT pVar, pCTMONEY pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetCurrency(pCTVARIANT pVar, pCTCURRENCY pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetNumber(pCTVARIANT pVar, pCTNUMBER pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetFloat(pCTVARIANT pVar, pCTFLOAT pValue);
ctdbEXPORT CTDBRET ctDECL ctvarGetString(pCTVARIANT pVar, pTEXT pValue, pVRLEN size);
ctdbEXPORT CTDBRET ctDECL ctvarSetNull(pCTVARIANT pVar);
ctdbEXPORT CTDBRET ctDECL ctvarSetEmpty(pCTVARIANT pVar);
ctdbEXPORT CTDBRET ctDECL ctvarSetBool(pCTVARIANT pVar, CTBOOL Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetSigned(pCTVARIANT pVar, CTSIGNED Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetUnsigned(pCTVARIANT pVar, CTUNSIGNED Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetDate(pCTVARIANT pVar, CTDATE Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetTime(pCTVARIANT pVar, CTTIME Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetDateTime(pCTVARIANT pVar, CTDATETIME Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetBigint(pCTVARIANT pVar, CTBIGINT Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetMoney(pCTVARIANT pVar, CTMONEY Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetCurrency(pCTVARIANT pVar, CTCURRENCY Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetNumber(pCTVARIANT pVar, pCTNUMBER pValue);
ctdbEXPORT CTDBRET ctDECL ctvarSetFloat(pCTVARIANT pVar, CTFLOAT Value);
ctdbEXPORT CTDBRET ctDECL ctvarSetString(pCTVARIANT pVar, pTEXT pValue, VRLEN size);
ctdbEXPORT CTDBRET ctDECL ctvarSetStringByref(pCTVARIANT pVar, pTEXT pValue, VRLEN size);
ctdbEXPORT CTDBRET ctDECL ctvarConvert(pCTVARIANT pVar, CTDBTYPE toType);

ctdbEXPORT CTDBRET ctDECL ctvarAdd(pCTVARIANT pLeft, pCTVARIANT pRight, pCTVARIANT pRes);
ctdbEXPORT CTDBRET ctDECL ctvarSub(pCTVARIANT pLeft, pCTVARIANT pRight, pCTVARIANT pRes);
ctdbEXPORT CTDBRET ctDECL ctvarMul(pCTVARIANT pLeft, pCTVARIANT pRight, pCTVARIANT pRes);
ctdbEXPORT CTDBRET ctDECL ctvarDiv(pCTVARIANT pLeft, pCTVARIANT pRight, pCTVARIANT pRes);
ctdbEXPORT CTDBRET ctDECL ctvarMod(pCTVARIANT pLeft, pCTVARIANT pRight, pCTVARIANT pRes);
ctdbEXPORT CTDBRET ctDECL ctvarNegate(pCTVARIANT pLeft, pCTVARIANT pRes);
ctdbEXPORT CTDBRET ctDECL ctvarNot(pCTVARIANT pLeft, pCTVARIANT pRes, CTBOOL Logical);
ctdbEXPORT CTDBRET ctDECL ctvarAnd(pCTVARIANT pLeft, pCTVARIANT pRight, pCTVARIANT pRes, CTBOOL Logical);
ctdbEXPORT CTDBRET ctDECL ctvarOr(pCTVARIANT pLeft, pCTVARIANT pRight, pCTVARIANT pRes, CTBOOL Logical);
ctdbEXPORT CTDBRET ctDECL ctvarXor(pCTVARIANT pLeft, pCTVARIANT pRight, pCTVARIANT pRes, CTBOOL Logical);
ctdbEXPORT NINT ctDECL ctvarCmp(pCTVARIANT pLeft, pCTVARIANT pRight, CTBOOL IgnoreCase);

#else /* PROTOTYPE */

#endif /* ~PROTOTYPE */

/*~****************************************************************************/
#ifdef __cplusplus
}
#endif /* ~__cplusplus */
#endif /* ~_CTDBVARI_H_ */

/* end of ctdbvar.h */
