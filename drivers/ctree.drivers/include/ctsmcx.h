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

#ifndef __CTSMCX_H__
#define __CTSMCX_H__
	
// Display the function monitor window.
void CreateFunctionMonitorWindow(void);

// Display message in function monitor window.
int ctrt_Cocoa_fncmon(long FM_cnt, int sOWNR, int mfn, char *tp_fnm, char *info, int mbr);

// Display a message in the message monitor window.
/* int ctrt_Cocoa_printf(char *fmt, ...); */ /* RAB020927: commented this out per redefine */

// Display an error message.
void show_errmsg(char *title, char *errmsg);

// Display the appropriate server image.
void show_image(int type);

// Setup Cocoa environment for a thread.
void *thread_stub_pre(void);

// Clean up Cocoa environment for a thread.
void thread_stub_post(void *pool);

#endif /* ~__CTSMCX_H__ */
/* end of ctsmcx.h */
