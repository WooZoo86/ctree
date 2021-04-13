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

#ifndef _FCRCESAGENT_HPP_
#define _FCRCESAGENT_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESAgent;
class RCESAgentConsumer;
typedef RCESAgent *pRCESAgent, **ppRCESAgent;
typedef RCESAgentConsumer *pRCESAgentConsumer, **ppRCESAgentConsumer;

#define RCES_AGENT_LIST "agentList"
#define RCES_AGENT "agent"
#define RCES_AGENT_ID "id"
#define RCES_AGENT_OS "opSystem" 
#define RCES_AGENT_WORKINGVOLUME "workingVolume"
#define RCES_AGENT_WORKINGDIR "workingDir"
#define RCES_AGENT_DBENGINE "dbEngine"
#define RCES_AGENT_STATUS "status"
#define RCES_AGENT_STATUS_CODE "statusCode"
#define RCES_AGENT_STATUSTIME "statusTime"
#define RCES_AGENT_TOTAL "total"
#define RCES_AGENT_RECURSIVE "recursive"

/* Agent status values */
#define RCES_AGENT_INACTIVE   "inactive"
#define RCES_AGENT_ACTIVE     "active"
#define RCES_AGENT_STOPPING   "stopping"
#define RCES_AGENT_STARTING   "starting"

/*^****************************************************************************\
*
*   RCESAgent
*   Recon-e-Sense agent class
*
\******************************************************************************/
class RCESAgent
{
public:
	/* Constructors & destructor */
	RCESAgent();
	RCESAgent(pRCESAgent agent);
	virtual ~RCESAgent();

	/* Public services */
	static int ctGetAgents(pRCESMasterProvider masterProv, int osID, int agentListSize, int agentStart, ppRCESAgent *agentList, int *agentCount, int *totalAgents);
	static int ctGetAgents(pRCESMasterProvider masterProv, int osID, bool isPaging, int agentListSize, int agentStart, ppRCESJson result);
	static int ctGetAgent(pRCESMasterProvider masterProv, int agentID, ppRCESAgent agent);
	static int ctGetAgent(pRCESMasterProvider masterProv, int agentID, ppRCESJson result);
	static int ctGetAgentByDBEngine(pRCESMasterProvider masterProv, int dbEngineID, ppRCESAgent agent);
	static int ctGetAgentByDBEngine(pRCESMasterProvider masterProv, int dbEngineID, ppRCESJson result);
	static int ctGetAgentByPath(pRCESMasterProvider masterProv, int workingVolumeID, const char *workingDir, ppRCESAgent agent);
	static int ctPersistAgent(pRCESMasterProvider masterProv, pRCESAgent agent);
	static int ctRemoveAgent(pRCESMasterProvider masterProv, int agentID, bool recursive);
	static int ctRemoveAgent(pRCESMasterProvider masterProv, int agentID, bool recursive, ppRCESJson result);
	static int ctCheckAgentStatus(pRCESMasterProvider masterProv, int agentID, ppRCESAgent *agentList, int *agentCount);
	static int ctCheckAgentStatus(pRCESMasterProvider masterProv, int agentID, ppRCESJson result);
	static int ctSetAgentStatus(pRCESMasterProvider masterProv, int agentID, RCESAgentStatus status);

	/* Public methods */
	int GetID() { return _id; };
	int GetOSID() { return _osID; };
	int GetDBEngineID() { return _dbEngineID; };
	RCESAgentStatus GetStatus() { return _status; };
	const char *GetStatusStr();
	RCESDateTime GetStatusTime() { return _statusTime; };
	int GetWorkingVolumeID() { return _workingVolumeID; };
	char *GetWorkingDir() { return _workingDir; };
	char *GetWorkingVolumeName() { return _workingVolumeName; };
	ppRCESAgentConsumer GetConsumerList() { return _agentConsumerList; };
	int GetConsumerCount() { return _agentConsumerCount;  };

	void SetID(int id) { _id = id; };
	void SetOSID(int osID) { _osID = osID; };
	void SetDBEngineID(int dbEngineID) { _dbEngineID = dbEngineID; };
	void SetStatus(RCESAgentStatus status) { _status = status; };
	void SetStatusTime(RCESDateTime statusTime) { _statusTime = statusTime; };
	void SetWorkingVolumeID(int workingVolumeID) { _workingVolumeID = workingVolumeID; };
	void SetWorkingVolumeName(const char *workingVolumeName);
	void SetWorkingDir(const char *workingDir);
	void SetConsumerList(ppRCESAgentConsumer agentConsumerList, int agentConsumerCount) { _agentConsumerList = agentConsumerList; _agentConsumerCount = agentConsumerCount; };

	pRCESJson GetJson();

protected:
	/* Protected properties */
	int _id;
	int _osID;
	int _dbEngineID;
	RCESEngineStatus _status;
	RCESDateTime _statusTime;
	int _workingVolumeID;
	char *_workingVolumeName;
	char *_workingDir;
	ppRCESAgentConsumer _agentConsumerList;
	int _agentConsumerCount;

	/* Protected methods */

private:
	/* Private methods */
	void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESAGENT_HPP_ */