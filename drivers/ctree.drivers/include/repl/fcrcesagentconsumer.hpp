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

#ifndef _FCRCESAGENTCONSUMER_HPP_
#define _FCRCESAGENTCONSUMER_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESAgentConsumer;
typedef RCESAgentConsumer *pRCESAgentConsumer, **ppRCESAgentConsumer;

#define RCES_AGENTCONSUMER_ID "id"
#define RCES_AGENTCONSUMER_DBENGINE "dbEngine"
#define RCES_AGENTCONSUMER_LIST "actionExecs"
#define RCES_AGENTCONSUMER_TYPE "type" 
#define RCES_AGENTCONSUMER_LIBNAME "library" 
#define RCES_AGENTCONSUMER_STATUS "status"
#define RCES_AGENTCONSUMER_THRDCOUNT "threadCount"
#define RCES_AGENTCONSUMER_STATUSTIME "statusTime"

/* Agent consumer status values */
#define RCES_AGENTCONSUMER_INACTIVE   "inactive"
#define RCES_AGENTCONSUMER_ACTIVE     "active"

/*^****************************************************************************\
*
*   RCESAgentConsumer
*   Recon-e-Sense consumer status per agent class
*
\******************************************************************************/
class RCESAgentConsumer
{
public:
	/* Constructors & destructor */
	RCESAgentConsumer();
	RCESAgentConsumer(pRCESAgentConsumer agentConsumer);
	virtual ~RCESAgentConsumer();

	/* Public services */
	static int ctGetAgentConsumers(pRCESMasterProvider masterProv, int agentID, ppRCESAgentConsumer *agentConsumerList, int *agentConsumerCount);
	static int ctGetAgentConsumersByDB(pRCESMasterProvider masterProv, int dbEngineID, ppRCESAgentConsumer *agentConsumerList, int *agentConsumerCount);
	static int ctLoadActionExec(pRCESMasterProvider masterProv, int agentID, RCESConsumerType consumerType, const char *libName, int thrdCount, int osID = -1);
	static int ctLoadActionExecByDB(pRCESMasterProvider masterProv, int dbEngineID, RCESConsumerType consumerType, const char *libName, int thrdCount);
	static int ctUnloadActionExec(pRCESMasterProvider masterProv, int agentID, RCESConsumerType consumerType, int osID = -1);
	static int ctUnloadActionExecByDB(pRCESMasterProvider masterProv, int dbEngineID, RCESConsumerType consumerType);
	static const char *GetConsumerStr(RCESConsumerType consumerType);
	static RCESConsumerType GetConsumerType(const char *consumerName);
	static const char *GetConsumerLibName(RCESConsumerType consumerType);

	/* Public methods */
	int GetAgentID() { return _agentID; };
	RCESConsumerType GetConsumerType() { return _consumerType; };
	int GetThrdCount() { return _thrdCount; };
	bool IsActive() { return _active; };
	RCESDateTime GetStatusTime() { return _statusTime; };
	const char *GetStatusStr();
	const char *GetConsumerTypeStr();

	void SetAgentID(int agentID) { _agentID = agentID; };
	void SetConsumerType(RCESConsumerType consumerType) { _consumerType = consumerType; };
	void SetThrdCount(int thrdCount) { _thrdCount = thrdCount; };
	void SetActive(bool active) { _active = active; };
	void SetStatusTime(RCESDateTime statusTime) { _statusTime = statusTime; };

	pRCESJson GetJson();

protected:
	/* Protected properties */
	int _agentID;
	RCESConsumerType _consumerType;
	int _thrdCount;
	bool _active;
	RCESDateTime _statusTime;

	/* Protected methods */

private:
	/* Private methods */
	void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESAGENTCONSUMER_HPP_ */