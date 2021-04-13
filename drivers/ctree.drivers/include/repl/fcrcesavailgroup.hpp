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

#ifndef _FCRCESAVAILGROUP_HPP_
#define _FCRCESAVAILGROUP_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
	#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESAvailGroup;
class RCESReplica;
class RCESMasterProvider;
typedef RCESAvailGroup *pRCESAvailGroup, **ppRCESAvailGroup;
typedef RCESReplica *pRCESReplica, **ppRCESReplica;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_AVAILGROUP_LIST "availGroupList"
#define RCES_AVAILGROUP "availGroup"
#define RCES_AVAILGROUP_ID "id"
#define RCES_AVAILGROUP_NAME "name"
#define RCES_AVAILGROUP_DESCRIPTION "description"
#define RCES_AVAILGROUP_PARTIAL "partial"
#define RCES_AVAILGROUP_DETAIL "detail"
#define RCES_AVAILGROUP_TOTAL "total"
#define RCES_AVAILGROUP_STATUS "status"
#define RCES_AVAILGROUP_STATUS_CODE "statusCode"
#define RCES_AVAILGROUP_STATUSTIME "statusTime"
#define RCES_AVAILGROUP_STATUSMSG "statusMsg"
#define RCES_AVAILGROUP_STATUSACTIONID "statusActionID"
#define RCES_AVAILGROUP_ISDEPLOYED "isDeployed"
#define RCES_AVAILGROUP_REPLICASTATUS "replicaStatus"
#define RCES_AVAILGROUP_REPLICASTATUS_CODE "replicaStatusCode"
#define RCES_AVAILGROUP_ACTIONID "actionID"
#define RCES_AVAILGROUP_CHECKCONN "checkConnection"
#define RCES_AVAILGROUP_IGNOREDEPLOY "ignoreDeploy"
#define RCES_AVAILGROUP_CANFAILOVERASYNC "canFailoverToAsyncReplica"
#define RCES_AVAILGROUP_HEARTBEAT_FREQUENCY "heartbeatFrequency"
#define RCES_AVAILGROUP_HEARTBEAT_TIMEOUT "heartbeatTimeout"

#define RCES_AVAILGROUP_FILENAME "availGroup.json"

/*^****************************************************************************\
*
*   RCESAvailGroup
*   Recon-e-Sense Availability Group class
*
\******************************************************************************/
class RCESAvailGroup
{
	public:
		/* Constructors & destructor */
		RCESAvailGroup();
		RCESAvailGroup(pRCESAvailGroup availGroup);
		RCESAvailGroup(pRCESJson availGroup);
		virtual ~RCESAvailGroup();

		/* Public services */
		static int ctGetAvailGroups(pRCESMasterProvider masterProv, int aGroupListSize, int aGroupStart, ppRCESAvailGroup *aGroupList, int *aGroupCount, int *totalAvailGroups);
		static int ctGetAvailGroups(pRCESMasterProvider masterProv, bool detail, bool isPaging, int aGroupListSize, int aGroupStart, ppRCESJson result);
		static int ctGetAvailGroupsByName(pRCESMasterProvider masterProv, const char *name, bool partial, int aGroupListSize, int aGroupStart, ppRCESAvailGroup *aGroupList, int *aGroupCount, int *totalAvailGroups);
		static int ctGetAvailGroupsByName(pRCESMasterProvider masterProv, const char *name, bool detail, bool partial, bool isPaging, int aGroupListSize, int aGroupStart, ppRCESJson result);
		static int ctGetAvailGroup(pRCESMasterProvider masterProv, int availGroupID, ppRCESAvailGroup availGroup);
		static int ctGetAvailGroup(pRCESMasterProvider masterProv, int availGroupID, bool detail, int isPaging, ppRCESJson result);
		static int ctPersistAvailGroup(pRCESMasterProvider masterProv, pRCESAvailGroup availGroup);
		static int ctPersistAvailGroup(pRCESMasterProvider masterProv, pRCESJson availGroup, ppRCESJson result);
		static int ctRemoveAvailGroup(pRCESMasterProvider masterProv, int availGroupId);
		static int ctRemoveAvailGroup(pRCESMasterProvider masterProv, int availGroupId, ppRCESJson result);
		static int ctPersistReplicasToGroup(pRCESMasterProvider masterProv, int availGroupID, ppRCESReplica replicaList, int replicaCount);
		static int ctPersistReplicasToGroup(pRCESMasterProvider masterProv, int availGroupID, ppRCESReplica replicaList, int replicaCount, ppRCESJson result);
		static int ctRemoveReplicasFromGroup(pRCESMasterProvider masterProv, int *dbEngineIDList, int dbEngineCount);
		static int ctRemoveReplicasFromGroup(pRCESMasterProvider masterProv, int availGroupID, int *dbEngineIDList, int dbEngineCount, ppRCESJson result);
		static void ctCleanSecondaryReplicas(pRCESReplica primary, ppRCESReplica replicaList, int replicaCount);

		static pRCESAvailGroup ctLoadFromDisk(pRCESConfig config);

		/* Public methods */
		int GetID() { return _id; };
		const char *GetName() { return _name; };
		const char *GetDescription() { return _description; };
		RCESEngineStatus GetStatus() { return _status; };
		RCESDateTime GetStatusTime() { return _statusTime; };
		char *GetStatusMsg() { return _statusMsg; };
		int GetStatusActionID() { return _statusActionID; };
		bool IsDeployed() { return _isDeployed; };
		RCESReplStatus GetReplicaStatus() { return _replicaStatus; };
		int GetReplicaCount() { return _replicaCount; };
		ppRCESReplica GetReplicaList() { return _replicaList; };
		pRCESReplica GetPrimaryReplica();
		bool IsStarted() { return _replicaStatus != RCES_REPL_INACTIVE; };
		bool CanFailoverAsync() { return _canFailoverAsync; };
		pRCESReplica GetPreviousPrimary() { return _previousPrimary; };
		int GetHeartbeatFrequency() { return _heartbeatFrequency; };
		int GetHeartbeatTimeout() { return _heartbeatTimeout; };

		void SetID( int id ) { _id = id; };
		void SetName( const char *name );
		void SetDescription( const char *description );
		void SetStatus(RCESEngineStatus status) { _status = status; };
		void SetStatusTime(RCESDateTime statusTime) { _statusTime = statusTime; };
		void SetStatusMsg(const char *statusMsg);
		void SetStatusActionID(int statusActionID) { _statusActionID = statusActionID; };
		void SetIsDeployed(bool isDeployed) { _isDeployed = isDeployed; };
		void SetReplicaStatus(RCESReplStatus replicaStatus) { _replicaStatus = replicaStatus; };
		void SetReplicaList(ppRCESReplica replicaList, int replicaCount) { _replicaCount = replicaCount; _replicaList = replicaList; };
		void SetCanFailoverAsync(bool canFailoverAsync) { _canFailoverAsync = canFailoverAsync; };
		void SetPreviousPrimary(pRCESReplica previousPrimary) { _previousPrimary = previousPrimary; };
		void SetHeartbeatFrequency(int heartbeatFrequency) { _heartbeatFrequency = heartbeatFrequency; };
		void SetHeartbeatTimeout(int heartbeatTimeout) { _heartbeatTimeout = heartbeatTimeout; };

		pRCESJson GetJson(bool detail);
		void Update(pRCESJson availGroupPatch);
		void DumpToDisk(pRCESConfig config);

	private:
		/* private methods */
		void _init();

		/* Private properties */
		int _id;
		char *_name;
		char *_description;
		RCESEngineStatus _status;
		RCESDateTime _statusTime;
		char *_statusMsg;
		int _statusActionID;
		bool _isDeployed;
		RCESReplStatus _replicaStatus;
		int _replicaCount;
		ppRCESReplica _replicaList;
		bool _canFailoverAsync;
		pRCESReplica _previousPrimary;
		int _heartbeatFrequency;
		int _heartbeatTimeout;
};
/*~****************************************************************************/

#endif /* _FCRCESAVAILGROUP_HPP_ */