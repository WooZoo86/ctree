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

#ifndef ctCUSTH
#define ctCUSTH

#ifdef ctPortLCT
#ifndef ctPortUNIX		/* Not Supported yet for UNIX */
#ifndef ctSRVR_DOTNET_DLL	/* Not supported under DOTNET */
/* inclusion of LCT header files start here */
#define  ctLCT_DBIO_H	"lct_dbio.h"
#include ctLCT_DBIO_H
#endif
#endif
#endif

/* OPC1 Parameter Block Type:
	This type of function has the following restictions:
	1) cfn must be your custom function reference number.
	2) your server function must return a LONG integer.
	3) your server function must set the communications output buffer
	   length to zero:  MsgLen(ctusrbuf, OUTSEG) = 0;
	4) your function parameters are restricted by what you can place 
	   into the OPC1 structure. 
	5) there is no output data available with this function	type, 
	   except for the LONG return type.
	6) you cannot use this type of function for variable input or 
	   variable output data.
*/

typedef struct opc1 {
	LONG	cfn;		/* Mandatory custom function reference number */
	LONG	chn;		/* your custom LONG  parameter	*/
	COUNT	cs1;		/* your custom COUNT parameter 	*/
	COUNT	cs2;		/* your custom COUNT parameter 	*/
	LONG	cl3;		/* your custom LONG  parameter 	*/
#ifndef ctPortCTB
	LONG	cl4;		/* your custom LONG  parameter	*/
	LONG	cl5;		/* your custom LONG  parameter	*/
#endif
	TEXT	cvr[FNZ];	/* your custom string (up to 256 long) */
	} OPC1;
typedef OPC1 ctMEM * pOPC1;

/* OPC2 Parameter Block Type:
	This type of function has the following restictions:
	1) cfn must be your custom function reference number.
	2) your server function must return a LONG integer.
	3) your server function must set the communications output buffer
	   length to your output data length:  
	   MsgLen(ctusrbuf, OUTSEG) = mystuff;
	5) you can send variable input and output.

	The best way to establish this parameter block is as follows:
	1) allocate a block of memory with size as follows:
	   (size_of_your_input_data + sizeof(OPC2) - OPC2_CVR_SIZ)
	2) cast your memory pointer to OPC2 and fill in the data.
	   Note your user defined input data will start at cvr.
	   Be sure to set both input and output buffer lengths properly.
*/
#define OPC2_CVR_SIZ 8 
typedef struct opc2 {
	LONG	cfn;		/* Mandatory custom function reference number */
	LONG	chn;		/* your custom LONG  parameter	*/
	COUNT	cs1;		/* your custom COUNT parameter 	*/
	COUNT	cs2;		/* your custom COUNT parameter 	*/
	LONG	cl3;		/* your custom LONG  parameter 	*/
#ifndef ctPortCTB
	LONG	cl4;		/* your custom LONG  parameter	*/
	LONG	cl5;		/* your custom LONG  parameter	*/
#endif
	VRLEN	cil;		/* input buffer length - number of bytes starting at cvr */
	VRLEN	col;		/* output buffer length - the length of the second parm's buffer */
	TEXT	cvr[OPC2_CVR_SIZ]; /* address of your vlen data */
	} OPC2;
typedef OPC2 ctMEM * pOPC2;

extern char  custom_msg[];
extern char *custom_fnm[];

/*^***********************************/
/* Custom function reference numbers */
#define FN_ctcust_Login			1
#define FN_ctcust_Logout		2
#define FN_ctcust_Myfunction		3
/*~***********************************/

/*^***********************************/
/* Custom function Prototypes */
#ifdef PROTOTYPE
LONG MY_FUNCTIONz(pTEXT inBuffer, LONG inBufLen, pTEXT outBuffer, LONG outBufLen, pLONG newOutLen);
#else
LONG MY_FUNCTIONz();
#endif
/*~***********************************/

#endif /* ctCUSTH */

/* end of ctcust.h */
