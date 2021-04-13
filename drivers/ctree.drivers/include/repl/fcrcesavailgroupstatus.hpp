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
 *      Copyright (c) 2013 - 2014 FairCom Corporation.
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

#ifndef _FCRCESAVAILGROUPSTATUS_HPP_
#define _FCRCESAVAILGROUPSTATUS_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
	#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESAvailGroupStatus;
class RCESReplicaStatus;
class RCESMasterProvider;
typedef RCESAvailGroupStatus *pRCESAvailGroupStatus, **ppRCESAvailGroupStatus;
typedef RCESReplicaStatus *pRCESReplicaStatus, **ppRCESReplicaStatus;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_AVAILGROUPSTATUS_LIST "availGroupStatus"
#define RCES_AVAILGROUPSTATUS_ID "id"
#define RCES_AVAILGROUPSTATUS_NAME "name"
#define RCES_AVAILGROUPSTATUS_STATUS "status"
#define RCES_AVAILGROUPSTATUS_STATUS_CODE "statusCode"
#define RCES_AVAILGROUPREPLSTATUS_STATUS "replStatus"
#define RCES_AVAILGROUPREPLSTATUS_STATUS_CODE "replStatusCode"

/*^****************************************************************************\
*
*   RCESAvailGroupStatus
*   Recon-e-Sense Availability Group status class
*
\******************************************************************************/
class RCESAvailGroupStatus
{
public:
	/* Constructors & destructor */
	RCESAvailGroupStatus();
	RCESAvailGroupStatus(pRCESAvailGroupStatus availGroupStatus);
	RCESAvailGroupStatus(pRCESJson availGroupStatus);
	virtual ~RCESAvailGroupStatus();

	/* Public services */
	static int ctGetAvailGroupStatus(pRCESMasterProvider masterProv, int availGroupID, ppRCESAvailGroupStatus availGroupStatus);
	static int ctGetAvailGroupStatus(pRCESMasterProvider masterProv, int availGroupID, ppRCESJson result);
	static int ctGetAvailGroupStatusByName(pRCESMasterProvider masterProv, const char *availGroupName, ppRCESAvailGroupStatus availGroupStatus);
	static int ctGetAvailGroupStatusByName(pRCESMasterProvider masterProv, const char *availGroupName, ppRCESJson result);

	/* Public methods */
	int GetID() { return _id; };
	const char *GetName() { return _name; };
	RCESEngineStatus GetStatus() { return _status; };
	RCESReplStatus GetReplStatus() { return _replStatus; };
	int GetReplicaCount() { return _replicaCount; };
	ppRCESReplicaStatus GetReplicaStatusList() { return _replicaStatusList; };

	void SetID(int id) { _id = id; };
	void SetName(const char *name);
	void SetStatus(RCESEngineStatus status) { _status = status; };
	void SetReplStatus(RCESReplStatus replStatus) { _replStatus = replStatus; };
	void SetReplicaStatusList(ppRCESReplicaStatus replicaStatusList, int replicaCount) { _replicaCount = replicaCount; _replicaStatusList = replicaStatusList; };

	pRCESJson GetStatusJson();
	pRCESJson GetJson();

private:
	/* private methods */
	void _init();

	/* Private properties */
	int _id;
	char *_name;
	RCESEngineStatus _status;
	RCESReplStatus _replStatus;
	int _replicaCount;
	ppRCESReplicaStatus _replicaStatusList;
};
/*~****************************************************************************/

#endif /* _FCRCESAVAILGROUPSTATUS_HPP_ */