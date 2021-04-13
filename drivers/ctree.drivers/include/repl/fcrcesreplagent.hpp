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

#ifndef _FCRCESREPLAGENT_HPP_
#define _FCRCESREPLAGENT_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESReplAgent;
typedef RCESReplAgent *pRCESReplAgent, **ppRCESReplAgent;

#define RCES_REPLAGENT_OS_ID "opSystem"
#define RCES_REPLAGENT_PATH "path"
#define RCES_REPLAGENT_NAME "name"
#define RCES_REPLAGENT_SOURCESERVER "sourceServer"
#define RCES_REPLAGENT_TARGETSERVER "targetServer"
#define RCES_REPLAGENT_SOURCENODEID "sourceNodeID"
#define RCES_REPLAGENT_TARGETNODEID "targetNodeID"
#define RCES_REPLAGENT_BASE_PATH "basePath"
#define RCES_REPLAGENT_LIST "replAgentList"
#define RCES_REPLAGENT_REPLPLAN "replPlan"
#define RCES_REPLAGENT_PUBLICATION "publication"
#define RCES_REPLAGENT_SUBSCRIPTION "subscription"
#define RCES_REPLAGENT_SIMPLEMODE "simpleMode"

/*^****************************************************************************\
*
*   RCESReplAgent
*   Recon-e-Sense Replication Agent class
*
\******************************************************************************/
class RCESReplAgent
{
public:
	/* Constructors & destructor */
	RCESReplAgent();
	RCESReplAgent(pRCESReplAgent replAgent);
	RCESReplAgent(pRCESJson replAgent);
	virtual ~RCESReplAgent();

	/* Public services */
	static int ctScanReplAgent(pRCESMasterProvider masterProv, int osID, const char *basePath, ppRCESReplAgent *replAgentList, int *replAgentCount);
	static int ctScanReplAgent(pRCESMasterProvider masterProv, int osID, const char *basePath, ppRCESJson result);
	static int ctImportReplAgent(pRCESMasterProvider masterProv, bool simpleMode, ppRCESReplAgent replAgentList, int replAgentCount);
	static int ctImportReplAgent(pRCESMasterProvider masterProv, bool simpleMode, pRCESJson replAgentListObj, ppRCESJson result);

	/* Public methods */
	int GetActionID() { return _actionID; };
	int GetOSID() { return _osID; };
	const char *GetPath() { return _path; };
	const char *GetName() { return _name; };
	const char *GetSourceServer() { return _sourceServer; };
	const char *GetTargetServer() { return _targetServer; };
	const char *GetSourceNodeID() { return _sourceNodeID; };
	const char *GetTargetNodeID() { return _targetNodeID; };
	RCESRET GetErrorCode() { return _errorCode; };
	const char *GetErrorMsg() { return _errorMsg; };

	const char *GetReplPlanName() { return _replPlan_name; };
	const char *GetReplPlanDesc() { return _replPlan_desc; };

	int GetPubID() { return _pub_id; };
	const char *GetPubName() { return _pub_name; };
	const char *GetPubDesc() { return _pub_desc; };
	int GetPubDatabaseID() { return _pub_databaseID; };

	const char *GetSubsName() { return _subs_name; };
	const char *GetSubsDesc() { return _subs_desc; };
	int GetSubsDatabaseID() { return _subs_databaseID; };

	void SetActionID(int actionID) { _actionID = actionID; };
	void SetOSID(int osID) { _osID = osID; };
	void SetPath(const char *path);
	void SetName(const char *name);
	void SetSourceServer(const char *sourceServer);
	void SetTargetServer(const char *targetServer);
	void SetSourceNodeID(const char *sourceNodeID);
	void SetTargetNodeID(const char *targetNodeID);
	void SetErrorCode(RCESRET errorCode) { _errorCode = errorCode; };
	void SetErrorMsg(const char *errorMsg);

	pRCESJson GetJson(bool keyWithError);

private:
	/* Private properties */
	int _actionID;
	int _osID;
	char *_path;
	char *_name;
	char *_sourceServer;
	char *_targetServer;
	char *_sourceNodeID;
	char *_targetNodeID;
	RCESRET _errorCode;
	char *_errorMsg;

	/* Non persisted properties */
	char *_replPlan_name;
	char *_replPlan_desc;

	int _pub_id;
	char *_pub_name;
	char *_pub_desc;
	int _pub_databaseID;

	char *_subs_name;
	char *_subs_desc;
	int _subs_databaseID;

	void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESREPLAGENT_HPP_ */