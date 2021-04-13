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

#ifndef _FCRCESREPLCTREE_HPP_
#define _FCRCESREPLCTREE_HPP_

#include "fc_rces.h"
#include "fcrcesrepl.hpp"
#include "fcrcesreplplan.hpp"

/*^****************************************************************************\
*
*   RCESReplCtree
*   Recon-e-Sense replication class for c-tree files
*
*   Manage the replication for the c-tree files in a replication plan
*
\******************************************************************************/
class RCESReplCtree : public RCESRepl
{
public:
	/* Constructors & destructor */
	RCESReplCtree(pRCESReplPlan replPlan, pRCESMasterProvider provider);
	virtual ~RCESReplCtree();

	/* Public Methods */
	void Start(int ownerActionID, const char *sourceLogPos, const char *targetLogPos, int *sourceAgentID, int *targetAgentID);
	void Stop(int ownerActionID, bool wait);
	void DumpFiles(int ownerActionID, bool forceReplace, const char *fileIDList);
	void CheckReplicationAgents();
	void CleanPendingReplication();
	void CheckPendingReplication();
	void Cancel(int actionID);
	void StartMonitor(int refreshRate);
	void StopMonitor();
	void StartExcepLog();
	void StopExcepLog();
	void StartFuncTime();
	void StopFuncTime();
	void ResetFuncTime();
	void GetFuncTimes(char **content, int *contentLen);
	void Pause();
	void Resume();
	void Resync(int *fileIDList, int fileCount, bool addNewFiles, int *actionID);

private:
	/* Private properties */

	/* Private methods */
	void _pushAction(int ownerActionID, RCESActionType actionType, const char *functionName, bool wait, int timeout, pFCParamHash param = NULL,
		int *sourceActionID = NULL, int *targetActionID = NULL);
	void _pushActionByAgent(int ownerActionID, RCESActionType actionType, const char *functionName, bool wait, int timeout,
		pFCParamHash param = NULL);
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESReplCtree *pRCESReplCtree, **ppRCESReplCtree;

#endif /* _FCRCESREPLCTREE_HPP_ */