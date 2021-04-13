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
#ifndef CT_SRLE_H
#define CT_SRLE_H
#define ctsRLE_LOOKUP_TABLE

struct tag_sRLE
{
	TEXT level;
	TEXT strategy;
};
typedef struct tag_sRLE sRLE;

struct tag_sRLE_context
{
#ifdef ctsRLE_LOOKUP_TABLE
	TEXT chars[256];
#else
	VRLEN len;
	TEXT chars[3];
#endif
};
typedef struct tag_sRLE_context sRLE_context;

#define ctsRLE_LEVEL_SPACES (TEXT) 0x01
#define ctsRLE_LEVEL_ZEROES (TEXT) 0x02
#define ctsRLE_LEVEL_DIGIT0 (TEXT) 0x04
#define ctsRLE_LEVEL_DEFAULT (TEXT) 0x00 /*act as 7*/

#define ctsRLE_STRATEGY_DEFAULT (TEXT) 0x00

#endif
/* end of ct_srle.h */
