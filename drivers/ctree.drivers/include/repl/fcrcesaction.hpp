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

#ifndef _FCRCESACTION_HPP_
#define _FCRCESACTION_HPP_

#include "fc_rces.h"
#include "fcparam.hpp"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#define RCES_ACTION_OBJ                  "action"
#define RCES_ACTION_ID                   "actionID"
#define RCES_ACTION_STATUS               "status"
#define RCES_ACTION_PROGRESS             "progress"
#define RCES_ACTION_STATUSCODE           "statusCode"
#define RCES_ACTION_STATUSMSG            "statusMessage"
#define RCES_ACTION_CREATETIME           "createTime"
#define RCES_ACTION_STARTTIME            "startTime"
#define RCES_ACTION_CHECKGROUP           "checkGroup"
#define RCES_ACTION_AGENTID              "agentID"

/* Action status values */
#define RCES_ACTION_COMPLETED            "completed"
#define RCES_ACTION_PENDING              "pending"
#define RCES_ACTION_ERROR                "error"

/* Class type definitions */
class RCESAction;
typedef RCESAction *pRCESAction, **ppRCESAction;

/*^****************************************************************************\
*
*   RCESAction
*   Recon-e-Sense notification action class
*
\******************************************************************************/
class RCESAction
{
public:
	/* Constructors & destructor */
	RCESAction();
	RCESAction(pFCParamHash parameters, const char *description, RCESConsumerType consumerType, RCESActionType actionType,
		int replPlanID, RCESEntityType entityType, int entityPK, int parentActionID = -1, int ownerActionID = -1, double factor = 0,
		int fileVolumeID = -1, const char *filePath = NULL, const char *fileName = NULL, int waitSecs = 0);
	virtual ~RCESAction();

	/* Public services */
	static int ctCheckStatus(pRCESMasterProvider masterProv, int actionID, bool checkGroup, ppRCESAction action);
	static int ctCheckStatus(pRCESMasterProvider masterProv, int actionID, bool checkGroup, ppRCESJson result);
	static int ctCancel(pRCESMasterProvider masterProv, int actionID, bool checkGroup);
	static int ctCancel(pRCESMasterProvider masterProv, int actionID, bool checkGroup, ppRCESJson result);
	static int ctArchive(pRCESMasterProvider masterProv, int daysToArchive);

	/* Public methods */
	virtual int GetActionID() { return _actionID; };
	virtual int GetParentActionID() { return _parentActionID; };
	virtual int GetOwnerActionID() { return _ownerActionID; };
	virtual pFCParamHash GetParams() { return _params; };
	virtual const char *GetDescription() { return _desc; };
	virtual RCESActionType GetAction() { return _actionType; };
	virtual RCESEntityType GetEntity() { return _entityType; };
	virtual int GetEntityPK() { return _entityPK; };
	virtual const char *GetActionStr();
	virtual int GetWaitSecs() { return _waitSecs; };
	virtual int GetFileVolumeID() { return _fileVolumeID; };
	virtual const char *GetFilePath() { return _filePath; };
	virtual const char *GetFileName() { return _fileName; };
	virtual int GetProgress() { return _progress; };
	virtual pRCESJson GetJson();
	virtual int GetErrorCode() { return _errorCode; };
	virtual char *GetErrorMessage() { return _errorMessage; };
	virtual int GetAgentID() { return _agentID; };
	virtual int GetReplPlanID() { return _replPlanID; };
	virtual RCESConsumerType GetConsumer() { return _consumerType; };
	virtual int GetContentLen() { return _contentLen; };
	virtual void *GetContent() { return _content; };
	virtual double GetFactor() { return _factor; };

	void SetActionID(int actionID) { _actionID = actionID; };
	void SetTimeProcessed(RCESDateTime timeProcessed) { _timeProcessed = timeProcessed; };
	void SetErrorCode(int errorCode) { _errorCode = errorCode; };
	void SetErrorMessage(const char *errorMessage);
	void SetActionTime(RCESDateTime actionTime) { _actionTime = actionTime; };
	void SetProgress(int progress) { _progress = progress; };
	void SetEntityType(RCESEntityType entityType) { _entityType = entityType; };
	void SetEntityPK(int entityPK) { _entityPK = entityPK; };
	void SetOwnerActionID(int ownerActionID) { _ownerActionID = ownerActionID; };
	void SetAgentID(int agentID) { _agentID = agentID; };
	void SetContent(void *content, int contentLen);
	void SetFactor(double factor) { _factor = factor; };
	void SetAction(RCESActionType actionType) { _actionType = actionType; };

private:
	/* Private properties */
	int _actionID;
	int _parentActionID;
	int _ownerActionID;
	pFCParamHash _params;
	char *_desc;
	RCESConsumerType _consumerType;
	RCESActionType _actionType;
	int _replPlanID;
	RCESEntityType _entityType;
	int _entityPK;
	int _waitSecs;
	int _fileVolumeID;
	char *_filePath;
	char *_fileName;
	RCESDateTime _timeProcessed;
	int _errorCode;
	char *_errorMessage;
	RCESDateTime _actionTime;
	int _progress;
	int _agentID;
	int _contentLen;
	void *_content;
	double _factor;
};
/*~****************************************************************************/

#endif /* _FCRCESACTION_HPP_ */