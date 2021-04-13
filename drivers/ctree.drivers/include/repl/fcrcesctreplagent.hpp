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
 *      Copyright (c) 2013 - 2015 FairCom Corporation.
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

#ifndef _FCRCESREPLAGENT_HPP_
#define _FCRCESREPLAGENT_HPP_

#include "fcrcesaux.hpp"
#include "fcrcesreplfunc.hpp"

/* Class type definitions */

/*^****************************************************************************\
*
*       RCES DLL export macros
*
\******************************************************************************/

/* Replication agent API for ctree */
int rcesEXPORT RCESStartReplAgent( pAgentThrdData agentThrdData, void **agentThrdHandle );
int rcesEXPORT RCESCheckReplConnected(pAgentThrdData agentThrdData);
void rcesEXPORT RCESStartReplExcepLog( pAgentThrdData agentThrdData );
void rcesEXPORT RCESStopReplExcepLog( pAgentThrdData agentThrdData );
void rcesEXPORT RCESStartReplFuncTime( pAgentThrdData agentThrdData );
void rcesEXPORT RCESStopReplFuncTime( pAgentThrdData agentThrdData );
void rcesEXPORT RCESResetReplFuncTime( pAgentThrdData agentThrdData );
int rcesEXPORT RCESGetReplFuncTimes( pAgentThrdData agentThrdData, char **funcTimesBuffer, int *bufferLen );
void rcesEXPORT RCESPauseRepl( pAgentThrdData agentThrdData );
void rcesEXPORT RCESResumeRepl( pAgentThrdData agentThrdData );
int rcesEXPORT RCESResyncRepl(pAgentThrdData agentThrdData, const char *fileList, char *resyncName, int resyncNameLen);
int rcesEXPORT RCESStartResyncThrd(pResyncThrdData resyncThrdData, void **resyncThrdHandle);
void rcesEXPORT RCESStopResyncThrd(pResyncThrdData resyncThrdData, void *resyncThrdHandle);
int rcesEXPORT RCESUpdateFileFilter(pAgentThrdData agentThrdData);

/*^****************************************************************************\
*
*   Auxiliary functions
*
\******************************************************************************/


#endif /* _FCRCESREPLAGENT_HPP_ */