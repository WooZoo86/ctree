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

#ifndef _FCRCESREPLPARALLELSTAT_HPP_
#define _FCRCESREPLPARALLELSTAT_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#define RCES_REPLPSTAT_LIST "replPlanParallelStatList"
#define RCES_REPLPSTAT_ID "statID"
#define RCES_REPLPSTAT_DIRECTION "direction"
#define RCES_REPLPSTAT_TIME "time"
#define RCES_REPLPSTAT_MAIN "main"
#define RCES_REPLPSTAT_LS "logShip"
#define RCES_REPLPSTAT_LR "logRead"
#define RCES_REPLPSTAT_ANALYZER "analyzer"
#define RCES_REPLPSTAT_DEPENDENCY "dependency"
#define RCES_REPLPSTAT_APPLY "apply"
#define RCES_REPLPSTAT_TRAN_QUEUE_ENTRY "transactionProcessCounts"
#define RCES_REPLPSTAT_SOURCE_SERVER "sourceDbName"
#define RCES_REPLPSTAT_TARGET_SERVER "targetDbName"
#define RCES_REPLPSTAT_SOURCE_ID "sourceTaskID"
#define RCES_REPLPSTAT_TARGET_ID "targetTaskID"
#define RCES_REPLPSTAT_LOG_NUMBER "logNumber"
#define RCES_REPLPSTAT_LOG_POSITION "logPosition"
#define RCES_REPLPSTAT_STATE "state"
#define RCES_REPLPSTAT_SEQUENCE_NUMBER "sequenceNumber"
#define RCES_REPLPSTAT_ERROR "error"
#define RCES_REPLPSTAT_FUNCTION_NAME "functionName"
#define RCES_REPLPSTAT_NUMBER "number"
#define RCES_REPLPSTAT_FILES "files"
#define RCES_REPLPSTAT_STATUS "total"
#define RCES_REPLPSTAT_ANALYSIS "waitingOnAnalyze"
#define RCES_REPLPSTAT_DEPENDENCY_EVAL "waitingOnDependencyEval"
#define RCES_REPLPSTAT_GRAPH "waitingOnDependencyResolution"
#define RCES_REPLPSTAT_READY "waitingOnApply"
#define RCES_REPLPSTAT_LATENCY "latency"
#define RCES_REPLPSTAT_TOTAL "total"
#define RCES_REPLPSTAT_SOURCE_DBENGINE "sourceDBEngine"
#define RCES_REPLPSTAT_TARGET_DBENGINE "targetDBEngine"

#define RCES_REPLPSTAT_SUCCESS_COUNTS "transactionSuccessCounts"
#define RCES_REPLPSTAT_FAIL_COUNTS "transactionFailCounts"
#define RCES_REPLPSTAT_ADD "add"
#define RCES_REPLPSTAT_DELETE "delete"
#define RCES_REPLPSTAT_UPDATE "update"
#define RCES_REPLPSTAT_COMMIT "commit"

#define RCES_REPLPSTAT_SOURCE_CONNERROR "sourceConnectionError"
#define RCES_REPLPSTAT_TARGET_CONNERROR "targetConnectionError"

#define RCES_REPLPSTAT_REPL_PAUSED "replicationPaused"
#define RCES_REPLPSTAT_REPL_ABORTED "replicationAborted"
#define RCES_REPLPSTAT_REPL_FAILURE "transactionFailure"

#define RCES_REPLPSTAT_ANALYZE_COUNT "analyze"
#define RCES_REPLPSTAT_APPLY_COUNT "apply"
#define RCES_REPLPSTAT_THREAD_COUNT "threadCounts"

/* Replication statistic direction string values */
#define RCES_REPLDPSTAT_DIRECT "direct"
#define RCES_REPLDPTAT_REVERSE "reverse"

/* Replication statistic state string values */
#define RCES_REPLPSTAT_TARGET       "target"
#define RCES_REPLPSTAT_SOURCE       "source"
#define RCES_REPLPSTAT_PAUSED       "paused"
#define RCES_REPLPSTAT_SELF         "self"

/* Class type definitions */
class RCESReplParallelStat;
typedef RCESReplParallelStat *pRCESReplParallelStat, **ppRCESReplParallelStat;

/*^****************************************************************************\
*
*   RCESReplParallelAnalyzer
*   Recon-e-Sense replication statistic analyzer class
*
\******************************************************************************/
class RCESReplParallelAnalyzer
{
public:
	/* Constructors & destructor */
	RCESReplParallelAnalyzer();
	virtual ~RCESReplParallelAnalyzer();

	/* Public methods */
	RCESBigInt GetReplParallelStat() { return _replParallelStat; };
	int GetNumber() { return _number; };
	RCESReplicationState GetState() { return _state; };
	RCESBigInt GetSequenceNumber() { return _sequenceNumber; };
	int GetError() { return _error; };
	const char *GetFunctionName() { return _functionName; };

	void SetReplParallelStat(RCESBigInt replParallelStat) { _replParallelStat = replParallelStat; };
	void SetNumber(int number) { _number = number; };
	void SetState(RCESReplicationState state) { _state = state; };
	void SetSequenceNumber(RCESBigInt sequenceNumber) { _sequenceNumber = sequenceNumber; };
	void SetError(int error) { _error = error; };
	void SetFunctionName(const char *functionName);

	pRCESJson GetJson();

private:
	/* private properties */
	RCESBigInt _replParallelStat;
	int _number;
	RCESReplicationState _state;
	RCESBigInt _sequenceNumber;
	int _error;
	char *_functionName;

	/* private methods */
	void _init();
};
typedef RCESReplParallelAnalyzer *pRCESReplParallelAnalyzer, **ppRCESReplParallelAnalyzer;
/*~****************************************************************************/

/*^****************************************************************************\
*
*   RCESReplParallelApply
*   Recon-e-Sense replication statistic apply class
*
\******************************************************************************/
class RCESReplParallelApply
{
public:
	/* Constructors & destructor */
	RCESReplParallelApply();
	virtual ~RCESReplParallelApply();

	/* Public methods */
	RCESBigInt GetReplParallelStat() { return _replParallelStat; };
	int GetNumber() { return _number; };
	int GetTargetTaskID() { return _targetTaskID; };
	int GetLogNumber() { return _logNumber; };
	int GetLogPosition() { return _logPosition; };
	RCESReplicationState GetState() { return _state; };
	int GetFiles() { return _files; };
	RCESBigInt GetSequenceNumber() { return _sequenceNumber; };
	int GetError() { return _error; };
	const char *GetFunctionName() { return _functionName; };
	RCESBigInt GetCommitPass() { return _commitPass; };
	RCESBigInt GetAddPass() { return _addPass; };
	RCESBigInt GetDeletePass() { return _deletePass; };
	RCESBigInt GetUpdatePass() { return _updatePass; };
	RCESBigInt GetCommitFail() { return _commitFail; };
	RCESBigInt GetAddFail() { return _addFail; };
	RCESBigInt GetDeleteFail() { return _deleteFail; };
	RCESBigInt GetUpdateFail() { return _updateFail; };

	void SetReplParallelStat(RCESBigInt replParallelStat) { _replParallelStat = replParallelStat; };
	void SetNumber(int number) { _number = number; };
	void SetTargetTaskID(int targetTaskID) { _targetTaskID = targetTaskID; };
	void SetLogNumber(int logNumber) { _logNumber = logNumber; };
	void SetLogPosition(int logPosition) { _logPosition = logPosition; };
	void SetState(RCESReplicationState state) { _state = state; };
	void SetFiles(int files) { _files = files; };
	void SetSequenceNumber(RCESBigInt sequenceNumber) { _sequenceNumber = sequenceNumber; };
	void SetError(int error) { _error = error; };
	void SetFunctionName(const char *functionName);
	void SetCommitPass(RCESBigInt commitPass) { _commitPass = commitPass; };
	void SetAddPass(RCESBigInt addPass) { _addPass = addPass; };
	void SetDeletePass(RCESBigInt deletePass) { _deletePass = deletePass; };
	void SetUpdatePass(RCESBigInt updatePass) { _updatePass = updatePass; };
	void SetCommitFail(RCESBigInt commitFail) { _commitFail = commitFail; };
	void SetAddFail(RCESBigInt addFail) { _addFail = addFail; };
	void SetDeleteFail(RCESBigInt deleteFail) { _deleteFail = deleteFail; };
	void SetUpdateFail(RCESBigInt updateFail) { _updateFail = updateFail; };

	pRCESJson GetJson();

private:
	/* private properties */
	RCESBigInt _replParallelStat;
	int _number;
	int _targetTaskID;
	int _logNumber;
	int _logPosition;
	RCESReplicationState _state;
	int _files;
	RCESBigInt _sequenceNumber;
	int _error;
	char *_functionName;
	RCESBigInt _commitPass;
	RCESBigInt _addPass;
	RCESBigInt _deletePass;
	RCESBigInt _updatePass;
	RCESBigInt _commitFail;
	RCESBigInt _addFail;
	RCESBigInt _deleteFail;
	RCESBigInt _updateFail;

	/* private methods */
	void _init();
};
typedef RCESReplParallelApply *pRCESReplParallelApply, **ppRCESReplParallelApply;
/*~****************************************************************************/

/*^****************************************************************************\
*
*   RCESReplParallelStat
*   Recon-e-Sense replication statistic parallelism class
*
\******************************************************************************/
class RCESReplParallelStat
{
public:
	/* Constructors & destructor */
	RCESReplParallelStat();
	virtual ~RCESReplParallelStat();

	/* Public services */
	static int ctGetReplParallelStats(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int replStatListSize, int replStatStart, ppRCESReplParallelStat *replStatList, int *replStatCount, int *totalReplStats);
	static int ctGetReplParallelStats(pRCESMasterProvider masterProv, int replPlanID, bool threadDetails, RCESDateTime startTime, RCESDateTime endTime, bool isPaging, int replStatListSize, int replStatStart, ppRCESJson result);
	static int ctAddReplParallelStat(pRCESMasterProvider masterProv, pRCESReplParallelStat replStat);
	static const char *ctGetStateStr(RCESReplicationState state);
	static int ctArchive(pRCESMasterProvider masterProv, int daysToArchive);

	/* Public methods */
	RCESBigInt GetID() { return _id; };
	int GetReplPlanID() { return _replPlanID; };
	RCESReplicationDirection GetDirection() { return _direction; };
	RCESDateTime GetTime() { return _time; };
	bool GetIsSourceDBConnected() { return _isSourceDBConnected; };
	bool GetIsTargetDBConnected() { return _isTargetDBConnected; };
	const char *GetSourceServer() { return _sourceServer; };
	const char *GetTargetServer() { return _targetServer; };
	int GetLogShipSourceTaskID() { return _lsSourceTaskID; };
	int GetLogShipLogNumber() { return _lsLogNumber; };
	int GetLogShipLogPosition() { return _lsLogPosition; };
	RCESReplicationState GetLogShipState() { return _lsState; };
	RCESBigInt GetLogShipSequenceNumber() { return _lsSequenceNumber; };
	int GetLogShipError() { return _lsError; };
	const char *GetLogShipFunctionName() { return _lsFunctionName; };
	int GetLogReadSourceTaskID() { return _lrSourceTaskID; };
	int GetLogReadTargetTaskID() { return _lrTargetTaskID; };
	int GetLogReadLogNumber() { return _lrLogNumber; };
	int GetLogReadLogPosition() { return _lrLogPosition; };
	RCESReplicationState GetLogReadState() { return _lrState; };
	RCESBigInt GetLogReadSequenceNumber() { return _lrSequenceNumber; };
	int GetLogReadError() { return _lrError; };
	const char *GetLogReadFunctionName() { return _lrFunctionName; };
	RCESReplicationState GetDependencyState() { return _depState; };
	RCESBigInt GetDependencySequenceNumber() { return _depSequenceNumber; };
	int GetDependencyError() { return _depError; };
	const char *GetDependencyFunctionName() { return _depFunctionName; };
	int GetQueueStatusCount() { return _queueStatusCount; };
	int GetQueueAnalysisCount() { return _queueAnalysisCount; };
	int GetQueueDependencyCount() { return _queueDependencyCount; };
	int GetDependencyGraphCount() { return _dependencyGraphCount; };
	int GetQueueReadyCount() { return _queueReadyCount; };
	RCESBigInt GetCommitPass() { return _commitPass; };
	RCESBigInt GetAddPass() { return _addPass; };
	RCESBigInt GetDeletePass() { return _deletePass; };
	RCESBigInt GetUpdatePass() { return _updatePass; };
	RCESBigInt GetCommitFail() { return _commitFail; };
	RCESBigInt GetAddFail() { return _addFail; };
	RCESBigInt GetDeleteFail() { return _deleteFail; };
	RCESBigInt GetUpdateFail() { return _updateFail; };
	int GetLatency() { return _latency; };
	ppRCESReplParallelAnalyzer GetAnalyzerList() { return _analyzerList; };
	int GetAnalyzerCount() { return _analyzerCount; };
	ppRCESReplParallelApply GetApplyList() { return _applyList; };
	int GetApplyCount() { return _applyCount; };


	void SetID(RCESBigInt id) { _id = id; };
	void SetReplPlanID(int replPlanID) { _replPlanID = replPlanID; };
	void SetDirection(RCESReplicationDirection direction) { _direction = direction; };
	void SetTime(RCESDateTime time) { _time = time; };
	void SetIsSourceDBConnected(bool isSourceDBConnected) { _isSourceDBConnected = isSourceDBConnected; };
	void SetIsTargetDBConnected(bool isTargetDBConnected) { _isTargetDBConnected = isTargetDBConnected; };
	void SetSourceServer(const char *sourceServer);
	void SetTargetServer(const char *targetServer);
	void SetLogShipSourceTaskID(int lsSourceTaskID) { _lsSourceTaskID = lsSourceTaskID; };
	void SetLogShipLogNumber(int lsLogNumber) { _lsLogNumber = lsLogNumber; };
	void SetLogShipLogPosition(int lsLogPosition) { _lsLogPosition = lsLogPosition; };
	void SetLogShipState(RCESReplicationState lsState) { _lsState = lsState; };
	void SetLogShipSequenceNumber(RCESBigInt lsSequenceNumber) { _lsSequenceNumber = lsSequenceNumber; };
	void SetLogShipError(int lsError) { _lsError = lsError; };
	void SetLogShipFunctionName(const char *lsFunctionName);
	void SetLogReadSourceTaskID(int lrSourceTaskID) { _lrSourceTaskID = lrSourceTaskID; };
	void SetLogReadTargetTaskID(int lrTargetTaskID) { _lrTargetTaskID = lrTargetTaskID; };
	void SetLogReadLogNumber(int lrLogNumber) { _lrLogNumber = lrLogNumber; };
	void SetLogReadLogPosition(int lrLogPosition) { _lrLogPosition = lrLogPosition; };
	void SetLogReadState(RCESReplicationState lrState) { _lrState = lrState; };
	void SetLogReadSequenceNumber(RCESBigInt lrSequenceNumber) { _lrSequenceNumber = lrSequenceNumber; };
	void SetLogReadError(int lrError) { _lrError = lrError; };
	void SetLogReadFunctionName(const char *lrFunctionName);
	void SetDependencyState(RCESReplicationState depState) { _depState = depState; };
	void SetDependencySequenceNumber(RCESBigInt depSequenceNumber) { _depSequenceNumber = depSequenceNumber; };
	void SetDependencyError(int depError) { _depError = depError; };
	void SetDependencyFunctionName(const char *depFunctionName);
	void SetQueueStatusCount(int queueStatusCount) { _queueStatusCount = queueStatusCount; };
	void SetQueueAnalysisCount(int queueAnalysisCount) { _queueAnalysisCount = queueAnalysisCount; };
	void SetQueueDependencyCount(int queueDependencyCount) { _queueDependencyCount = queueDependencyCount; };
	void SetQueueReadyCount(int queueReadyCount) { _queueReadyCount = queueReadyCount; };
	void SetDependenceGraphCount(int dependencyGraphCount) { _dependencyGraphCount = dependencyGraphCount; };
	void SetCommitPass(RCESBigInt commitPass) { _commitPass = commitPass; };
	void SetAddPass(RCESBigInt addPass) { _addPass = addPass; };
	void SetDeletePass(RCESBigInt deletePass) { _deletePass = deletePass; };
	void SetUpdatePass(RCESBigInt updatePass) { _updatePass = updatePass; };
	void SetCommitFail(RCESBigInt commitFail) { _commitFail = commitFail; };
	void SetAddFail(RCESBigInt addFail) { _addFail = addFail; };
	void SetDeleteFail(RCESBigInt deleteFail) { _deleteFail = deleteFail; };
	void SetUpdateFail(RCESBigInt updateFail) { _updateFail = updateFail; };
	void SetLatency(int latency) { _latency = latency; };
	void SetAnalyzerList(ppRCESReplParallelAnalyzer analyzerList) { _analyzerList = analyzerList; };
	void SetAnalyzerCount(int analyzerListCount) { _analyzerCount = analyzerListCount; };
	void SetApplyList(ppRCESReplParallelApply applyList) { _applyList = applyList; };
	void SetApplyCount(int applyCount) { _applyCount = applyCount; };

	pRCESJson GetJson(bool threadDetails);

private:
	/* private properties */
	RCESBigInt _id;
	int _replPlanID;
	RCESReplicationDirection _direction;
	RCESDateTime _time;
	bool _isSourceDBConnected;
	bool _isTargetDBConnected;
	char *_sourceServer;
	char *_targetServer;
	int _lsSourceTaskID;
	int _lsLogNumber;
	int _lsLogPosition;
	RCESReplicationState _lsState;
	RCESBigInt _lsSequenceNumber;
	int _lsError;
	char *_lsFunctionName;
	int _lrSourceTaskID;
	int _lrTargetTaskID;
	int _lrLogNumber;
	int _lrLogPosition;
	RCESReplicationState _lrState;
	RCESBigInt _lrSequenceNumber;
	int _lrError;
	char *_lrFunctionName;
	RCESReplicationState _depState;
	RCESBigInt _depSequenceNumber;
	int _depError;
	char *_depFunctionName;
	int _queueStatusCount;
	int _queueAnalysisCount;
	int _queueDependencyCount;
	int _dependencyGraphCount;
	int _queueReadyCount;
	RCESBigInt _commitPass;
	RCESBigInt _addPass;
	RCESBigInt _deletePass;
	RCESBigInt _updatePass;
	RCESBigInt _commitFail;
	RCESBigInt _addFail;
	RCESBigInt _deleteFail;
	RCESBigInt _updateFail;
	int _latency;
	ppRCESReplParallelAnalyzer _analyzerList;
	int _analyzerCount;
	ppRCESReplParallelApply _applyList;
	int _applyCount;

	/* private methods */
	void _init();
	bool _getSourceConnError();
	bool _getTargetConnError();
	bool _getPaused();
	bool _getAborted();
	bool _getFailure();
};
/*~****************************************************************************/

#endif /* _FCRCESREPLPARALLELSTAT_HPP_ */