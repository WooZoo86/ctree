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

#ifndef _FCRCESREPLSTAT_HPP_
#define _FCRCESREPLSTAT_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#define RCES_REPLSTAT_LIST "replPlanMonitorStatList"
#define RCES_REPLSTAT_ID "statID"
#define RCES_REPLSTAT_DIRECTION "direction"
#define RCES_REPLSTAT_TIME "time"
#define RCES_REPLSTAT_SOURCE_DBENGINE "sourceDBEngine"
#define RCES_REPLSTAT_TARGET_DBENGINE "targetDBEngine"
#define RCES_REPLSTAT_LOG_NUMBER "logNumber"
#define RCES_REPLSTAT_LOG_POSITION "logPosition"
#define RCES_REPLSTAT_STATE "state"
#define RCES_REPLSTAT_SEQUENCE_NUMBER "sequenceNumber"
#define RCES_REPLSTAT_FUNCTION_NAME "functionName"
#define RCES_REPLSTAT_LATENCY "latency"
#define RCES_REPLSTAT_TOTAL "total"

#define RCES_REPLSTAT_SUCCESS_COUNTS "transactionSuccessCounts"
#define RCES_REPLSTAT_FAIL_COUNTS "transactionFailCounts"
#define RCES_REPLSTAT_ADD "add"
#define RCES_REPLSTAT_DELETE "delete"
#define RCES_REPLSTAT_UPDATE "update"
#define RCES_REPLSTAT_COMMIT "commit"

#define RCES_REPLSTAT_SOURCE_CONNERROR "sourceConnectionError"
#define RCES_REPLSTAT_TARGET_CONNERROR "targetConnectionError"

#define RCES_REPLSTAT_REPL_PAUSED "replicationPaused"
#define RCES_REPLSTAT_REPL_ABORTED "replicationAborted"
#define RCES_REPLSTAT_REPL_FAILURE "transactionFailure"

/* Replication statistic direction string values */
#define RCES_REPLSTAT_DIRECT "direct"
#define RCES_REPLSTAT_REVERSE "reverse"

/* Replication statistic status string values */
#define RCES_REPLSTAT_CONNECTED    "Connected"
#define RCES_REPLSTAT_DISCONNECTED "Disconnected"

/* Replication statistic state string values */
#define RCES_REPLSTAT_TARGET       "target"
#define RCES_REPLSTAT_SOURCE       "source"
#define RCES_REPLSTAT_PAUSED       "paused"
#define RCES_REPLSTAT_SELF         "self"
#define RCES_REPLSTAT_EXITED       "exited"
#define RCES_REPLSTAT_ERROR        "error"

/* Class type definitions */
class RCESReplStat;
typedef RCESReplStat *pRCESReplStat, **ppRCESReplStat;

/*^****************************************************************************\
*
*   RCESReplStat
*   Recon-e-Sense replication statistic class
*
\******************************************************************************/
class RCESReplStat
{
public:
	/* Constructors & destructor */
	RCESReplStat();
	virtual ~RCESReplStat();

	/* Public services */
	static int ctGetReplStats(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int replStatListSize, int replStatStart, ppRCESReplStat *replStatList, int *replStatCount, int *totalReplStats);
	static int ctGetReplStats(pRCESMasterProvider masterProv, int replPlanID, bool detail, RCESDateTime startTime, RCESDateTime endTime, bool isPaging, int replStatListSize, int replStatStart, ppRCESJson result);
	static int ctAddReplStat(pRCESMasterProvider masterProv, pRCESReplStat replStat);
	static const char *ctGetStateStr(RCESReplicationState state);
	static int ctArchive(pRCESMasterProvider masterProv, int daysToArchive);

	/* Public methods */
	RCESBigInt GetID() { return _id; };
	int GetReplPlanID() { return _replPlanID; };
	RCESReplicationDirection GetDirection() { return _direction; };
	RCESDateTime GetTime() { return _time; };
	bool GetIsSourceDBConnected() { return _isSourceDBConnected; };
	bool GetIsTargetDBConnected() { return _isTargetDBConnected; };
	int GetLogNumber() { return _logNumber; };
	int GetLogPosition() { return _logPosition; };
	RCESReplicationState GetState() { return _state; };
	RCESBigInt GetSequenceNumber() { return _sequenceNumber; };
	char *GetFunctionName() { return _functionName; };
	RCESBigInt GetCommitPass() { return _commitPass; };
	RCESBigInt GetAddPass() { return _addPass; };
	RCESBigInt GetDeletePass() { return _deletePass; };
	RCESBigInt GetUpdatePass() { return _updatePass; };
	RCESBigInt GetCommitFail() { return _commitFail; };
	RCESBigInt GetAddFail() { return _addFail; };
	RCESBigInt GetDeleteFail() { return _deleteFail; };
	RCESBigInt GetUpdateFail() { return _updateFail; };
	int GetLatency() { return _latency; };

	void SetID(RCESBigInt id) { _id = id; };
	void SetReplPlanID(int replPlanID) { _replPlanID = replPlanID; };
	void SetDirection(RCESReplicationDirection direction) { _direction = direction; };
	void SetTime(RCESDateTime time) { _time = time; };
	void SetIsSourceDBConnected(bool isSourceDBConnected) { _isSourceDBConnected = isSourceDBConnected; };
	void SetIsTargetDBConnected(bool isTargetDBConnected) { _isTargetDBConnected = isTargetDBConnected; };
	void SetLogNumber(int logNumber) { _logNumber = logNumber; };
	void SetLogPosition(int logPosition) { _logPosition = logPosition; };
	void SetState(RCESReplicationState state) { _state = state; };
	void SetSequenceNumber(RCESBigInt sequenceNumber) { _sequenceNumber = sequenceNumber; };
	void SetFunctionName(const char *functionName);
	void SetCommitPass(RCESBigInt commitPass) { _commitPass = commitPass; };
	void SetAddPass(RCESBigInt addPass) { _addPass = addPass; };
	void SetDeletePass(RCESBigInt deletePass) { _deletePass = deletePass; };
	void SetUpdatePass(RCESBigInt updatePass) { _updatePass = updatePass; };
	void SetCommitFail(RCESBigInt commitFail) { _commitFail = commitFail; };
	void SetAddFail(RCESBigInt addFail) { _addFail = addFail; };
	void SetDeleteFail(RCESBigInt deleteFail) { _deleteFail = deleteFail; };
	void SetUpdateFail(RCESBigInt updateFail) { _updateFail = updateFail; };
	void SetLatency(int latency) { _latency = latency; };

	pRCESJson GetJson(bool detail);

private:
	/* private properties */
	RCESBigInt _id;
	int _replPlanID;
	RCESReplicationDirection _direction;
	RCESDateTime _time;
	bool _isSourceDBConnected;
	bool _isTargetDBConnected;
	int _logNumber;
	int _logPosition;
	RCESReplicationState _state;
	RCESBigInt _sequenceNumber;
	char *_functionName;
	RCESBigInt _commitPass;
	RCESBigInt _addPass;
	RCESBigInt _deletePass;
	RCESBigInt _updatePass;
	RCESBigInt _commitFail;
	RCESBigInt _addFail;
	RCESBigInt _deleteFail;
	RCESBigInt _updateFail;
	int _latency;

	/* private methods */
	void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESREPLSTAT_HPP_ */