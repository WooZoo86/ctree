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

/* The following defines were changed between V6 and V7			*/
/* This file is to provide a forward compatibility header 		*/
/* for customer applications written in V7 and to be compiled with V6.	*/

#ifndef ctV7V6H
#define ctV7V6H

#ifndef CT_V7		/* Use only with V6 */

#ifndef ctLOGIDX
#define ctLOGIDX	LOGIDX
#endif
#define ctSHARED	SHARED
#define ctEXCLUSIVE	EXCLUSIVE
#define ctNONEXCLUSIVE	NONEXCLUSIVE
#define ctVIRTUAL	VIRTUAL
#define ctPERMANENT	PERMANENT
#define ctVLENGTH	VLENGTH
#define ctREADFIL	READFIL
#define ctPREIMG	PREIMG
#define ctTRNLOG	TRNLOG
#define ctWRITETHRU	WRITETHRU
#define ctCHECKLOCK	CHECKLOCK
#define ctDUPCHANEL	DUPCHANEL
#define ctSUPERFILE	SUPERFILE
#define ctCHECKREAD	CHECKREAD
#define ctDISABLERES	DISABLERES
#define ctMIRROR_SKP	MIRROR_SKP
#define ctOPENCRPT	OPENCRPT
#define ctADMOPEN	ADMOPEN
#define ctENABLE	ENABLE
#define ctENABLE_BLK	ENABLE_BLK
#define ctREADREC_BLK	READREC_BLK
#define ctRESTRED_BLK	RESTRED_BLK
#define ctRESET		RESET
#define ctREADREC	READREC
#define ctSUSPEND	SUSPEND
#define ctRESTORE	RESTORE
#define ctRESTORE_BLK	RESTORE_BLK
#define ctRESTRED	RESTRED
#define ctFREE		FREE
#define ctRESTRSV	RESTRSV
#define ctSS_LOCK	SS_LOCK
#define ctLK_BLOCK	LK_BLOCK
#define ctTRNBEGLK	TRNBEGLK
#define ctGETLKISAM	GETLKISAM
#define ctLOGFIL	LOGFIL
#define ctTWOFASE	TWOFASE
#define ctPENDERR	PENDERR
#define ctOVRFASE	OVRFASE
#define ctCIPFASE	CIPFASE
#define ctPENDREN	PENDREN
#define ctPENDRNU	PENDRNU
#define ctSAVENV	SAVENV
#define ctAUTOTRN	AUTOTRN
#define ctLKSTATE	LKSTATE
#define ctDELUPDT	DELUPDT
#define ctDEFERCP	DEFERCP
#define ctAUTOSAVE	AUTOSAVE
#define ctCOMMIT_SWAP	COMMIT_SWAP
#define ctTRANDEP_CRE	TRANDEP_CRE
#define ctTRANDEP_DEL	TRANDEP_DEL
#define ctTRANDEP_SFM	TRANDEP_SFM
#define ctSAVECTREE	SAVECTREE

#endif	/* ~CT_V7	*/

#endif /* ~ctV7V6H */
/* end of ctv7v6.h */

