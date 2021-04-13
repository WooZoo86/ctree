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

/*^***********************************/
#ifdef ctLOCBHint /* function definitions for ctlocb.h */
/*
** change API names to a local variety: e.g., ADDKEY -> fp_ADDKEY
**
** ctFPprefix default definition in ctopt2.h
*/
#define ctReplReadLogData		xppf(ctFPprefix,ctReplReadLogData)
#define ctReplCleanupTranStateKeys	xppf(ctFPprefix,ctReplCleanupTranStateKeys)
#define ctClusterConfig                 xppf(ctFPprefix,ctClusterConfig)
#define ctTruncateFile                  xppf(ctFPprefix,ctTruncateFile)
#define ctWorkerThrdAttach		xppf(ctFPprefix,ctWorkerThrdAttach)
/* ctSIBLING_SEPLNG: Add entry for new function here */

#endif /* end function definitions for ctlocb.h */
/*~***********************************/

/*^***********************************/
#ifdef ctLOCFHint /* function definitions for ctlocf.h */

#define ctReplReadLogData		locctReplReadLogData
#define ctReplCleanupTranStateKeys	locctReplCleanupTranStateKeys
#define ctClusterConfig                 locctClusterConfig
#define ctTruncateFile                  locctTruncateFile
#define ctWorkerThrdAttach		locctWorkerThrdAttach
/* ctSIBLING_SEPLNG: Add entry for new function here */

#endif /* end function definitions for ctlocf.h */
/*~***********************************/

/*^***********************************/
#ifdef ctLOCUHint /* function definitions for ctlocu.h */
/*
** undo locale variety rename
*/
#undef ctReplReadLogData
#undef ctReplCleanupTranStateKeys
#undef ctClusterConfig
#undef ctTruncateFile
#undef ctWorkerThrdAttach
/* ctSIBLING_SEPLNG: Add entry for new function here */

#endif /* end function definitions for ctlocu.h */
/*~***********************************/

/*^***********************************/
#ifdef ctSRCLHint /* function definitions for ctsrcl.h */

#define ctReplReadLogData		mtc_ctReplReadLogData
#define ctReplCleanupTranStateKeys	mtc_ctReplCleanupTranStateKeys
#define ctClusterConfig                 mtc_ctClusterConfig
#define ctTruncateFile                  mtc_ctTruncateFile
#define ctWorkerThrdAttach		mtc_ctWorkerThrdAttach
/* ctSIBLING_SEPLNG: Add entry for new function here */

#endif /* end function definitions for ctsrcl.h */
/*~***********************************/

/* end ctsepl.h */
