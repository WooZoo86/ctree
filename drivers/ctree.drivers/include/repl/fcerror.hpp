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
 *      Copyright (c) 2013 - 2020 FairCom Corporation.
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
 */

#ifndef _FCERROR_HPP_
#define _FCERROR_HPP_

#include <stdio.h>

#define FC_MAX_ERRMSG 1024

/*^****************************************************************************\
*
*   Pool error codes
*
\******************************************************************************/
typedef enum
{
	FC_SUCCESS          = 0,    /* OK                                           */
	FC_NOTFOUND         = 100,  /* Not found error                              */
	FC_MEM_ERR          = 8001, /* Memory allocation error                      */
	FC_POOL_LOCKED_ERR  = 8002, /* Pool is blocked                              */
	FC_POOL_INUSE_ERR   = 8003, /* Pool has at least one object in use          */
	FC_LISTFULL_ERR     = 8004, /* List is full                                 */
	FC_INVVOL_ERR       = 8005, /* Invalid volume                               */
	FC_NOTSUP_ERR       = 8006, /* Feature not supported                        */
	FC_CLASSNFOUND_ERR  = 8007, /* Class not found                              */
	FC_FUNCNFOUND_ERR   = 8008, /* Function not found                           */
	FC_INT_ERR          = 8009, /* Internal error                               */
	FC_CONFIG_ERR       = 9001  /* Couldn't initialize the configuration object */
} FCRET;

#endif /* _FCERROR_HPP_ */