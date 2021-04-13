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

#ifndef ctUSERH
#define ctUSERH


#ifndef ctPortWINCE
#ifdef ctFeatJOBMGTSYS			/* Activate job management subsystem logic */
#define RAB_CTJOB_WORK_080224
#endif
#endif


/*^***********************************/
/* Defines used for LoadLib and GetProcAddress */
#define CTUSER_RETVAL_OK 		   	0L
#define CTUSER_RETVAL_LOADLIB_ERROR 		-991L
#define CTUSER_RETVAL_GETPROCADDR_ERROR 	-992L

#define CTJOBMAIN_RETVAL_ALLOC_ERROR		-993L /* alloc error   - ~FAIRJOB~ client side submit jobs error */
#define CTJOBMAIN_RETVAL_TOOMANYJOBS_ERROR 	-994L /* too many jobs - ~FAIRJOB~ client side submit jobs error */

#define CTJOBMAIN_RETVAL_CTTCRE_ERROR 		-995L /* cttcre thread error - ~FAIRJOB~ client side submit jobs error */

#define CTJOBMAIN_RETVAL_SEMAWAITTIMEOUT_ERROR	-996L /* Wait timeout error - ~FAIRJOB~ client side submit jobs error */
							/* Here we were waiting for the launched thread to indicate its status */
							/* Yet we had to wait to long */
							
#define CTJOBMAIN_RETVAL_NOJOBSFOUND_ERROR 	-997L /* Could not find job def in array */
#define CTJOBMAIN_RETVAL_BUFFER_TO_BIG_ERROR 	-998L /* Syntax of buffer wrong- buffer to big */


#define CTJOBSCTUSERBUFSIZFLAG_INSIDE_LAUNCH    -1 /* This is the value we set the CTUSER bufsiz to to indicate a CTJOB launched by server keywords */
#define CTJOBSCTUSERBUFSIZFLAG_CLIENT_LAUNCH    -2 /* This is the value we set the CTUSER bufsiz to to indicate a CTJOB launched by CTSRVCTL from client side */


/*~***********************************/

/*^***********************************/
/* Function Prototypes */
#ifdef PROTOTYPE
LONG ctDECL CT_USER(pTEXT inString, pTEXT outBuffer, pVRLEN outBufLen);
#else
LONG ctDECL CT_USER();
#endif
/*~***********************************/


/*^***********************************/

/* This header file may be used for your special needs */

/*~***********************************/

#endif /* ~ctUSERH */
/* end of ctuser.h */
