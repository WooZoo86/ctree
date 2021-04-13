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

#ifndef ctVRECH
#define ctVRECH

#define	VDEL_FLAG	0xfdfd
#define VACT_FLAG	0xfafa
#define	VNOD_FLAG	0xfbbf
#define VRES_FLAG	0xfefe
#define VLNK_FLAG	0xfcfc

#define SIZVPAD		ctSIZE(UCOUNT)
#define	SIZVHDR		(ctSIZE(UCOUNT) + 2 * ctSIZE(VRLEN))
#define SIZRHDR		(SIZVHDR + ctSIZE(LONG))
#define SIZSHDR		(SIZVHDR + 2 * ctSIZE(LONG))
#define SIZSHDR8	(SIZVHDR + 3 * ctSIZE(LONG))

#define	VDEL_OLD	0xfdfd
#define VACT_OLD	0xfafa
#define	VNOD_OLD	0xfbfb
#define SIZVHDR_OLD	6

#endif /* ctVRECH */

/* end of header */
