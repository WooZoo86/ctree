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
/* This file is to provide a backward compatibility header 		*/
/* for customer applications written in V6 and to be compiled with V7.	*/

#ifndef ctV6V7H
#define ctV6V7H

#ifdef CT_V7		/* Use only with V7 */

#define LOGIDX		ctLOGIDX
#define SHARED          ctSHARED
#define EXCLUSIVE	ctEXCLUSIVE
#define NONEXCLUSIVE	ctNONEXCLUSIVE
#define VIRTUAL	 	ctVIRTUAL
#define PERMANENT	ctPERMANENT
#define VLENGTH	 	ctVLENGTH
#define READFIL	 	ctREADFIL
#define PREIMG	 	ctPREIMG
#define TRNLOG	 	ctTRNLOG
#define WRITETHRU	ctWRITETHRU
#define CHECKLOCK	ctCHECKLOCK
#define DUPCHANEL	ctDUPCHANEL
#define SUPERFILE	ctSUPERFILE
#define CHECKREAD	ctCHECKREAD
#define DISABLERES	ctDISABLERES
#define MIRROR_SKP	ctMIRROR_SKP
#define OPENCRPT	ctOPENCRPT
#define ADMOPEN	 	ctADMOPEN
#define ENABLE	 	ctENABLE
#define ENABLE_BLK	ctENABLE_BLK
#define READREC_BLK	ctREADREC_BLK
#define RESTRED_BLK	ctRESTRED_BLK
#define RESET	 	ctRESET
#define READREC	 	ctREADREC
#define SUSPEND	 	ctSUSPEND
#define RESTORE	 	ctRESTORE
#define RESTORE_BLK	ctRESTORE_BLK
#define RESTRED	 	ctRESTRED
#define FREE	 	ctFREE
#define RESTRSV	 	ctRESTRSV
#define SS_LOCK	 	ctSS_LOCK
#define LK_BLOCK	ctLK_BLOCK
#define TRNBEGLK	ctTRNBEGLK
#define GETLKISAM	ctGETLKISAM
#define LOGFIL	 	ctLOGFIL
#define TWOFASE	 	ctTWOFASE
#define PENDERR	 	ctPENDERR
#define OVRFASE	 	ctOVRFASE
#define CIPFASE	 	ctCIPFASE
#define PENDREN	 	ctPENDREN
#define PENDRNU	 	ctPENDRNU
#define SAVENV	 	ctSAVENV
#define AUTOTRN	 	ctAUTOTRN
#define LKSTATE	 	ctLKSTATE
#define DELUPDT	 	ctDELUPDT
#define DEFERCP	 	ctDEFERCP
#define AUTOSAVE	ctAUTOSAVE
#define COMMIT_SWAP	ctCOMMIT_SWAP
#define TRANDEP_CRE	ctTRANDEP_CRE
#define TRANDEP_DEL	ctTRANDEP_DEL
#define TRANDEP_SFM	ctTRANDEP_SFM
#define SAVECTREE	ctSAVECTREE

#endif	/* CT_V7	*/

#endif /* ~ctV6V7H */
/* end of ctv6v7.h */

