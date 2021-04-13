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

#ifndef _FCRCESREPLPLAN_HPP_
#define _FCRCESREPLPLAN_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"
#include "fccache.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#define RCES_REPLPLAN_LIST "replPlanList"
#define RCES_REPLPLAN_STATUS_LIST "replPlanStatusList"
#define RCES_REPLPLANDETAIL_LIST "replPlanDetailList"
#define RCES_SUBSDETAIL_LIST "subscriptionDetailList"
#define RCES_REPLPLAN_STATLIST "replPlanMonitorStatList"
#define RCES_REPLPLAN_EXCEPLIST "replPlanMonitorExceptionList"
#define RCES_REPLPLAN_OBJ "replPlan"
#define RCES_REPLPLAN_ID "id"
#define RCES_REPLPLAN_NAME "name"
#define RCES_REPLPLAN_PARTIAL "partial"
#define RCES_REPLPLAN_DESCRIPTION "description"
#define RCES_REPLPLAN_CHECKID "checkReplPlan"
#define RCES_REPLPLAN_ACTIONID "actionID"
#define RCES_REPLPLAN_TOTAL "total"
#define RCES_REPLPLAN_STATUS "status"
#define RCES_REPLPLAN_STATUS_CODE "statusCode"
#define RCES_REPLPLAN_STATUSTIME "statusTime"
#define RCES_REPLPLAN_STATUSMSG "statusMsg"
#define RCES_REPLPLAN_STATUSACTIONID "statusActionID"
#define RCES_REPLPLAN_SOURCEDBENGINE "sourceDBEngine"
#define RCES_REPLPLAN_SOURCEDBENGINEDETAIL "sourceDBEngineDetail"
#define RCES_REPLPLAN_TARGETDBENGINE "targetDBEngine"
#define RCES_REPLPLAN_TARGETDBENGINEDETAIL "targetDBEngineDetail"
#define RCES_REPLPLAN_SYNC "synchronous"
#define RCES_REPLPLAN_DIRECTION "direction"
#define RCES_REPLPLAN_RECURSIVE "recursive"
#define RCES_REPLPLAN_BACHSIZE "batchSize"
#define RCES_REPLPLAN_DEBUGMINLOG "debugMinLog"
#define RCES_REPLPLAN_EXCEPTIONMODE "exceptionMode"
#define RCES_REPLPLAN_LOCKRETRYCOUNT "lockRetryCount"
#define RCES_REPLPLAN_LOCKRETRYSLEEP "lockRetrySleep"
#define RCES_REPLPLAN_LOGCHANGEDETAILS "logChangeDetails"
#define RCES_REPLPLAN_READTIMEOUT "readTimeOut"
#define RCES_REPLPLAN_REMEMBERLOGPOS "rememberLogPos"
#define RCES_REPLPLAN_PARALLELAPPLY "parallelApply"
#define RCES_REPLPLAN_CHECKDEPENDENCIES "checkDependencies"
#define RCES_REPLPLAN_SYNCLOGWRITES "syncLogWrites"
#define RCES_REPLPLAN_ANALYZERTHREADSCOUNT "analyzerThreadsCount"
#define RCES_REPLPLAN_APPLYTHREADSCOUNT "applyThreadsCount"
#define RCES_REPLPLAN_FILEMASK "fileMask"
#define RCES_REPLPLAN_ISDEPLOYED "isDeployed"
#define RCES_REPLPLAN_ISPULLING "isPulling"
#define RCES_REPLPLAN_IGNOREPARTITION "ignorePartition"
#define RCES_REPLPLAN_EXTENSIONLIB "extensionLibrary"
#define RCES_REPLPLAN_REBUILDONDEPLOY "rebuildOnDeploy"
#define RCES_REPLPLAN_SOURCELOGPOS "sourceLogPos"
#define RCES_REPLPLAN_TARGETLOGPOS "targetLogPos"
#define RCES_REPLPLAN_SOURCETRANID "sourceTranID"
#define RCES_REPLPLAN_TARGETTRANID "targetTranID"
#define RCES_REPLPLAN_ISMONITORACTIVE "isMonitorActive"
#define RCES_REPLPLAN_MONITORTIME "monitorTime"
#define RCES_REPLPLAN_REFRESHRATE "refreshRate"
#define RCES_REPLPLAN_ISEXCEPLOGACTIVE "isExcepLogActive"
#define RCES_REPLPLAN_EXCEPLOGTIME "excepLogTime"
#define RCES_REPLPLAN_ISFUNCTIMEACTIVE "isFuncTimingActive"
#define RCES_REPLPLAN_FUNCTIMETIME "funcTimingTime"
#define RCES_REPLPLAN_CURRDIRECTION "currDirection"
#define RCES_REPLPLAN_CHECKCONN "checkConnection"
#define RCES_REPLPLAN_REFRESH "refreshRate"
#define RCES_REPLPLAN_BEGINTIME "beginTime"
#define RCES_REPLPLAN_ENDTIME "endTime"
#define RCES_REPLPLAN_SOURCE_LOGPOS "sourceLogPos"
#define RCES_REPLPLAN_TARGET_LOGPOS "targetLogPos"
#define RCES_REPLPLAN_CONFLICT "conflictDetection"
#define RCES_REPLPLAN_FORCEREPLACE "forceReplace"
#define RCES_REPLPLAN_EXCEP "exception"
#define RCES_REPLPLAN_FILELIST "fileList"
#define RCES_REPLPLAN_FILE "file"
#define RCES_REPLPLAN_IGNOREDEPLOY "ignoreDeploy"
#define RCES_REPLPLAN_BASIC "basic"
#define RCES_REPLPLAN_PUBLIST "publicationList"
#define RCES_REPLPLAN_WARNINGTHRESHOLD "warningThreshold"
#define RCES_REPLPLAN_ERRORTHRESHOLD "errorThreshold"
#define RCES_REPLPLAN_LATENCY "latency"
#define RCES_REPLPLAN_LATENCYTIME "latencyTime"
#define RCES_REPLPLAN_LATENCYREV "latencyRev"
#define RCES_REPLPLAN_LATENCYREVTIME "latencyRevTime"
#define RCES_REPLPLAN_HASNACKEXCEP "hasNonAckException"
#define RCES_REPLPLAN_ISINEXCEPDUMP "isInExceptionDump"
#define RCES_REPLPLAN_DELETE "delete"
#define RCES_REPLPLAN_DUMP "dump"
#define RCES_REPLPLAN_DUMPFILENAME "exceptionDumpFileName"
#define RCES_REPLPLAN_STAT_ID "statID"
#define RCES_REPLPLAN_DETAIL "detail"

/* Replication status string values */
#define RCES_REPLPLAN_INACTIVE    "inactive"
#define RCES_REPLPLAN_ACTIVE      "active"
#define RCES_REPLPLAN_STOPPING    "stopping"
#define RCES_REPLPLAN_STARTING    "starting"
#define RCES_REPLPLAN_DEPLOYING   "deploying"
#define RCES_REPLPLAN_PAUSED      "paused"
#define RCES_REPLPLAN_RESYNCING   "resyncing"
#define RCES_REPLPLAN_ARCHIVED    "archived"

/* Replication status string values */
#define RCES_REPLPLAN_NONE    "none"
#define RCES_REPLPLAN_NORMAL  "normal"
#define RCES_REPLPLAN_REVERSE "reverse"
#define RCES_REPLPLAN_BOTH    "both"

/* Replication log position values */
#define RCES_LOGPOS_CURRENT "CURRENT"
#define RCES_LOGPOS_RESUME  "RESUME"

/* Global Replication Plan definitions */
#define RCES_DFTL_REFRESH_RATE 5

#define RCES_REPLPLAN_MAX_NAME 32

/* Class type forward definitions */
class RCESReplication;
class RCESConsumer;

/*^****************************************************************************\
*
*   RCESReplPlan
*   Recon-e-Sense replication plan class
*
*   Replication plan class
*
\******************************************************************************/
class RCESReplPlan
{
public:
	/* Constructors & destructor */
	RCESReplPlan();
	RCESReplPlan(pRCESReplPlan replPlan);
	RCESReplPlan(pRCESJson replPlan);
	virtual ~RCESReplPlan();

	/* Public services */
	static int ctGetReplPlans(pRCESMasterProvider masterProv, int replPlanListSize, int replPlanStart, ppRCESReplPlan *replPlanList, int *replPlanCount, int *totalReplPlans);
	static int ctGetReplPlans(pRCESMasterProvider masterProv, bool details, bool basic, bool isPaging, int replPlanListSize, int replPlanStart, ppRCESJson result);
	static int ctGetReplPlansByName(pRCESMasterProvider masterProv, const char *name, bool partial, int replPlanListSize, int replPlanStart, ppRCESReplPlan *replPlanList, int *replPlanCount, int *totalReplPlans);
	static int ctGetReplPlansByName(pRCESMasterProvider masterProv, const char *name, bool partial, bool details, bool basic, bool isPaging, int replPlanListSize, int replPlanStart, ppRCESJson result);
	static int ctGetReplPlansByPublication(pRCESMasterProvider masterProv, int publicationID, ppRCESReplPlan *replPlanList, int *replPlanCount);
	static int ctGetArchivedReplPlans(pRCESMasterProvider masterProv, int replPlanListSize, int replPlanStart, ppRCESReplPlan *replPlanList, int *replPlanCount, int *totalReplPlans);
	static int ctGetArchivedReplPlans(pRCESMasterProvider masterProv, bool details, bool isPaging, int replPlanListSize, int replPlanStart, ppRCESJson result);
	static int ctGetArchivedReplPlansByName(pRCESMasterProvider masterProv, const char *name, bool partial, int replPlanListSize, int replPlanStart, ppRCESReplPlan *replPlanList, int *replPlanCount, int *totalReplPlans);
	static int ctGetArchivedReplPlansByName(pRCESMasterProvider masterProv, const char *name, bool partial, bool details, bool isPaging, int replPlanListSize, int replPlanStart, ppRCESJson result);
	static int ctGetReplPlan(pRCESMasterProvider masterProv, int replPlanID, ppRCESReplPlan replPlan);
	static int ctGetReplPlan(pRCESMasterProvider masterProv, int replPlanID, bool details, bool basic, bool isPaging, ppRCESJson replPlan);
	static int ctPersistReplPlan(pRCESMasterProvider masterProv, pRCESReplPlan replPlan);
	static int ctPersistReplPlan(pRCESMasterProvider masterProv, pRCESJson replPlan, ppRCESJson result);
	static int ctRemoveReplPlan(pRCESMasterProvider masterProv, int replPlanID, bool recursive);
	static int ctRemoveReplPlan(pRCESMasterProvider masterProv, int replPlanID, bool recursive, ppRCESJson result);
	static int ctGetReplFileList(pRCESMasterProvider masterProv, int replPlanID, int replFileListSize, int replFileStart, ppRCESReplFileList replFileList, int *replFileCount, int *totalReplFiles);
	static const char *GetStatusStr(RCESReplStatus status);
	static RCESReplStatus GetStatusFromStr(const char *statusStr);
	static void ctCheckAgent(pRCESMasterProvider masterProv, pRCESReplPlan replPlan, RCESReplicationDirection direction, pRCESDBEngineMngr dbEngineMngr);
	static int ctReplPlanArchive(pRCESMasterProvider masterProv, int replPlanID);
	static int ctReplPlanRestore(pRCESMasterProvider masterProv, int replPlanID);
	static int ctGetRulesFromReplPlan(pRCESMasterProvider masterProv, int replPlanID, bool isPaging, int ruleListSize, int ruleStart, ppRCESJson result);
	static int ctSetReplPlanStatus(pRCESMasterProvider masterProv, int replPlanID, RCESReplStatus status, const char *statusMsg, int actionID, int sourceAgentID = -1, int targetAgentID = -1);

	static int ctReplDeploy(pRCESMasterProvider masterProv, int replPlanID, bool forceReplace, int *actionID);
	static int ctReplStart(pRCESMasterProvider masterProv, int replPlanID, const char *sourceLogPos, const char *targetLogPos, bool ignoreDeploy, int *actionID);
	static int ctReplStop(pRCESMasterProvider masterProv, int replPlanID, bool waitForCheck, int *actionID);
	static int ctReplCheck(pRCESMasterProvider masterProv, int replPlanID, bool checkConn, ppRCESReplPlan *replPlanList, int *replPlanCount, int *actionID = NULL);
	static int ctCancelRepl(pRCESMasterProvider masterProv, int replPlanID, int actionID);
	static int ctReplStartMonitor(pRCESMasterProvider masterProv, int replPlanID, int refreshRate);
	static int ctReplStopMonitor(pRCESMasterProvider masterProv, int replPlanID);
	static int ctReplGetStats(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, int statListSize, int statStart, ppRCESReplStat *statList, int *statCount, int *totalReplStats);
	static int ctReplGetStats(pRCESMasterProvider masterProv, int replPlanID, bool detail, RCESDateTime begin, RCESDateTime end, bool isPaging, int statListSize, int statStart, ppRCESJson result);
	static int ctReplGetParallelStatByID(pRCESMasterProvider masterProv, int replPlanID, RCESBigInt id, ppRCESReplParallelStat parallelStat);
	static int ctReplGetParallelStatByID(pRCESMasterProvider masterProv, int replPlanID, RCESBigInt id, bool threadDetails, ppRCESJson result);
	static int ctReplGetParallelStats(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, int statListSize, int statStart, ppRCESReplParallelStat *statList, int *statCount, int *totalReplStats);
	static int ctReplGetParallelStats(pRCESMasterProvider masterProv, int replPlanID, bool threadDetails, RCESDateTime begin, RCESDateTime end, bool isPaging, int statListSize, int statStart, ppRCESJson result);
	static int ctReplStartExcepLog(pRCESMasterProvider masterProv, int replPlanID);
	static int ctReplStopExcepLog(pRCESMasterProvider masterProv, int replPlanID);
	static int ctReplGetExceptions(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, const char *dumpFileName, int excepListSize, int excepStart, ppRCESReplExcep *excepList, int *excepCount, int *totalReplExceps);
	static int ctReplGetExceptions(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, const char *dumpFileName, bool isPaging, int excepListSize, int excepStart, ppRCESJson result);
	static int ctReplCleanExceptions(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, bool deleteFlag, int *totalReplExceps);
	static int ctReplCleanExceptions(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, bool deleteFlag, ppRCESJson result);
	static int ctReplPlanFuncTimeStart(pRCESMasterProvider masterProv, int replPlanID);
	static int ctReplPlanFuncTimeStop(pRCESMasterProvider masterProv, int replPlanID);
	static int ctReplPlanFuncTimeReset(pRCESMasterProvider masterProv, int replPlanID);
	static int ctReplPlanGetFuncTimes(pRCESMasterProvider masterProv, int replPlanID, ppRCESReplFunc *sourceFuncList, int *sourceFuncCount, ppRCESReplFunc *targetFuncList, int *targetFuncCount);
	static int ctReplPlanGetFuncTimes(pRCESMasterProvider masterProv, int replPlanID, ppRCESJson result);
	static int ctReplPlanPause(pRCESMasterProvider masterProv, int replPlanID);
	static int ctReplPlanResume(pRCESMasterProvider masterProv, int replPlanID);
	static int ctGetTempReplPlanName(pRCESMasterProvider masterProv, char *tempReplPlanName);
	static int ctReplPlanAckExceptions(pRCESMasterProvider masterProv, int replPlanID);
	static int ctResyncFiles(pRCESMasterProvider masterProv, int replPlanID, int *fileIDList, int fileCount, bool addNewFiles, int *actionID);
	static int ctScanReplAgent(pRCESMasterProvider masterProv, int osID, const char *basePath, ppRCESReplAgent *replAgentList, int *replAgentCount);
	static int ctScanReplAgent(pRCESMasterProvider masterProv, int osID, const char *basePath, ppRCESJson result);
	static int ctImportReplAgent(pRCESMasterProvider masterProv, bool simpleMode, ppRCESReplAgent replAgentList, int replAgentCount);
	static int ctImportReplAgent(pRCESMasterProvider masterProv, bool simpleMode, pRCESJson replAgentListObj, ppRCESJson result);

	static int ctCheckAddedFile(pRCESMasterProvider masterProv, pRCESFile newFile, pRCESDatabase database);
	static int ctCheckRemovedFile(pRCESMasterProvider masterProv, pRCESFile oldFile, pRCESDatabase database);

	/* Public methods */
	int GetID() { return _id; };
	char *GetName() { return _name; };
	char *GetDescription() { return _description; };
	RCESReplStatus GetStatus() { return _status; };
	RCESDateTime GetStatusTime() { return _statusTime; };
	char *GetStatusMsg() { return _statusMsg; };
	int GetStatusActionID() { return _statusActionID; };
	int GetSourceDBEngineID() { return _sourceDBEngineID; };
	virtual pRCESDBEngine GetSourceDBEngine() { return _sourceDBEngine; };
	int GetTargetDBEngineID() { return _targetDBEngineID; };
	virtual pRCESDBEngine GetTargetDBEngine() { return _targetDBEngine; };
	bool GetIsSync() { return _isSync; };
	int GetWarningThreshold() { return _warningThreshold; };
	int GetErrorThreshold() { return _errorThreshold; };
	int GetLatency() { return _latency; };
	RCESDateTime GetLatencyTime() { return _latencyTime; };
	int GetLatencyRev() { return _latencyRev; };
	RCESDateTime GetLatencyRevTime() { return _latencyRevTime; };
	int GetBatchSize() { return _batchSize; };
	bool GetDebugMinLog() { return _debugMinLog; };
	int GetExceptionMode() { return _exceptionMode; };
	int GetLockRetryCount() { return _lockRetryCount; };
	int GetLockRetrySleep() { return _lockRetrySleep; };
	char *GetLogChangeDetails() { return _logChangeDetails; };
	int GetReadTimeout() { return _readTimeout; };
	bool GetRememberLogPos() { return _rememberLogPos; };
	bool GetParallelApply() { return _parallelApply; };
	bool GetCheckDependencies() { return _checkDependencies; };
	bool GetSyncLogWrites() { return _syncLogWrites; };
	int GetAnalyzerThreadsCount() { return _analyzerThreadsCount; };
	int GetApplyThreadsCount() { return _applyThreadsCount; };
	char *GetFileMask() { return _fileMask; };
	bool GetIsDeployed() { return _isDeployed; };
	bool GetIsPulling() { return _isPulling; };
	bool GetIgnorePartition() { return _ignorePartition; };
	char *GetExtensionLib() { return _extensionLib; };
	bool GetRebuildOnDeploy() { return _rebuildOnDeploy; };
	char *GetSourceLogPos() { return _sourceLogPos; };
	char *GetTargetLogPos() { return _targetLogPos; };
	char *GetSourceTranID() { return _sourceTranID; };
	char *GetTargetTranID() { return _targetTranID; };
	int GetSourceAgentID() { return _sourceAgentID; };
	int GetTargetAgentID() { return _targetAgentID; };
	bool GetIsMonitorActive() { return _isMonitorActive; };
	RCESDateTime GetMonitorTime() { return _monitorTime; };
	RCESReplDirection GetDirection() { return _direction; };
	int GetRefreshRate() { return _refreshRate; };
	bool GetIsExcepLogActive() { return _isExcepLogActive; };
	RCESDateTime GetExcepLogTime() { return _excepLogTime; };
	bool GetIsFuncTimeActive() { return _isFuncTimeActive; };
	RCESDateTime GetFuncTimeTime() { return _funcTimeTime; };
	bool GetIsPaused() { return _isPaused; };
	RCESDateTime GetPauseTime() { return _pauseTime; };
	bool GetConflictDetection() { return _conflictDetection; };
	bool IsFiltered() { return _isFiltered; };
	char *GetFileFilter() { return _fileFilter; };
	bool HasNAckExcep() { return _hasNAckExcep; };
	bool IsInExceptionDump() { return _isInExceptionDump; };

	bool HasAgentOnSource() {
		return _direction == RCES_REPL_BOTH ||
			(_direction == RCES_REPL_NORMAL && !_isPulling) ||
			(_direction == RCES_REPL_REVERSE && _isPulling);
	};
	bool HasAgentOnTarget() {
		return _direction == RCES_REPL_BOTH ||
			(_direction == RCES_REPL_NORMAL && _isPulling) ||
			(_direction == RCES_REPL_REVERSE && !_isPulling);
	};

	void SetID(int id) { _id = id; };
	void SetName(const char *name);
	void SetDescription(const char *description);
	void SetStatus(RCESReplStatus status) { _status = status; };
	void SetStatusTime(RCESDateTime statusTime) { _statusTime = statusTime; };
	void SetStatusMsg(const char *statusMsg);
	void SetStatusActionID(int statusActionID) { _statusActionID = statusActionID; };
	void SetSourceDBEngineID(int sourceDBEngineID) { _sourceDBEngineID = sourceDBEngineID; };
	void SetSourceDBEngine(pRCESDBEngine sourceDBEngine) { _sourceDBEngine = sourceDBEngine; };
	void SetTargetDBEngineID(int targetDBEngineID) { _targetDBEngineID = targetDBEngineID; };
	void SetTargetDBEngine(pRCESDBEngine targetDBEngine) { _targetDBEngine = targetDBEngine; };
	void SetIsSync(bool isSync) { _isSync = isSync; };
	void SetWarningThreshold(int warningThreshold) { _warningThreshold = warningThreshold; };
	void SetErrorThreshold(int errorThreshold) { _errorThreshold = errorThreshold; }
	void SetLatency(int latency) { _latency = latency; }
	void SetLatencyTime(RCESDateTime latencyTime) { _latencyTime = latencyTime; }
	void SetLatencyRev(int latencyRev) { _latencyRev = latencyRev; }
	void SetLatencyRevTime(RCESDateTime latencyRevTime) { _latencyRevTime = latencyRevTime; }
	void SetBatchSize(int batchSize) { _batchSize = batchSize; };
	void SetDebugMinLog(bool debugMinLog) { _debugMinLog = debugMinLog; };
	void SetExceptionMode(int exceptionMode) { _exceptionMode = exceptionMode; };
	void SetLockRetryCount(int lockRetryCount) { _lockRetryCount = lockRetryCount; };
	void SetLockRetrySleep(int lockRetrySleep) { _lockRetrySleep = lockRetrySleep; };
	void SetLogChangeDetails(const char *logChangeDetails);
	void SetReadTimeout(int readTimeout) { _readTimeout = readTimeout; };
	void SetRememberLogPos(bool rememberLogPos) { _rememberLogPos = rememberLogPos; };
	void SetParallelApply(bool parallelApply) { _parallelApply = parallelApply; };
	void SetCheckDependencies(bool checkDependencies) { _checkDependencies = checkDependencies; };
	void SetSyncLogWrites(bool syncLogWrites) { _syncLogWrites = syncLogWrites; };
	void SetAnalyzerThreadsCount(int analyzerThreadsCount) { _analyzerThreadsCount = analyzerThreadsCount; };
	void SetApplyThreadsCount(int applyThreadsCount) { _applyThreadsCount = applyThreadsCount; };
	void SetFileMask(const char *fileMask);
	void SetIsDeployed(bool isDeployed) { _isDeployed = isDeployed; };
	void SetIsPulling(bool isPulling) { _isPulling = isPulling; };
	void SetIgnorePartition(bool ignorePartition) { _ignorePartition = ignorePartition; };
	void SetExtensionLib(const char *extensionLib);
	void SetRebuildOnDeploy(bool rebuildOnDeploy) { _rebuildOnDeploy = rebuildOnDeploy; };
	void SetSourceLogPos(const char *sourceLogPos);
	void SetTargetLogPos(const char *targetLogPos);
	void SetSourceTranID(const char *sourceTranID);
	void SetTargetTranID(const char *targetTranID);
	void SetSourceAgentID(int sourceAgentID) { _sourceAgentID = sourceAgentID; };
	void SetTargetAgentID(int targetAgentID) { _targetAgentID = targetAgentID; };
	void SetDirection(ppRCESSubscription subsList, int subsCount);
	void SetIsMonitorActive(bool isMonitorActive) { _isMonitorActive = isMonitorActive; };
	void SetMonitorTime(RCESDateTime monitorTime) { _monitorTime = monitorTime; };
	void SetRefreshRate(int refreshRate) { _refreshRate = refreshRate; };
	void SetIsExcepLogActive(bool isExcepLogActive) { _isExcepLogActive = isExcepLogActive; };
	void SetExcepLogTime(RCESDateTime excepLogTime) { _excepLogTime = excepLogTime; };
	void SetIsFuncTimeActive(bool isFuncTimeActive) { _isFuncTimeActive = isFuncTimeActive; };
	void SetFuncTimeTime(RCESDateTime funcTimeTime) { _funcTimeTime = funcTimeTime; };
	void SetIsPaused(bool isPaused) { _isPaused = isPaused; };
	void SetPauseTime(RCESDateTime pausedTime) { _pauseTime = pausedTime; };
	void SetConflictDetection(bool conflictDetection) { _conflictDetection = conflictDetection; };
	void SetIsFiltered(bool isFiltered) { _isFiltered = isFiltered; };
	void SetFileFilter(const char *fileFilter);
	void SetHasNAckExcep(bool hasNAckExcep) { _hasNAckExcep = hasNAckExcep; }
	void SetIsInExceptionDump(bool isInExceptionDump) { _isInExceptionDump = isInExceptionDump; }

	pRCESJson GetJson(bool details, bool basic, pRCESMasterProvider masterProv = NULL);
	void Update(pRCESJson replPlanPatch);
	void GetStatusJson(pRCESJson replStatus, pRCESMasterProvider masterProv = NULL);
	bool IsRemote();

	virtual void LockMutex() {};
	virtual void FreeMutex() {};

protected:
	/* protected properties */
	int _id;
	char *_name;
	char *_description;
	RCESReplStatus _status;
	RCESDateTime _statusTime;
	char *_statusMsg;
	int _statusActionID;
	int _sourceDBEngineID;
	pRCESDBEngine _sourceDBEngine;
	int _targetDBEngineID;
	pRCESDBEngine _targetDBEngine;
	bool _isSync;
	int _warningThreshold;
	int _errorThreshold;
	int _latency;
	RCESDateTime _latencyTime;
	int _latencyRev;
	RCESDateTime _latencyRevTime;
	int _batchSize;
	bool _debugMinLog;
	int _exceptionMode;
	int _lockRetryCount;
	int _lockRetrySleep;
	char *_logChangeDetails;
	int _readTimeout;
	bool _rememberLogPos;
	bool _parallelApply;
	bool _checkDependencies;
	bool _syncLogWrites;
	int _analyzerThreadsCount;
	int _applyThreadsCount;
	char *_fileMask;
	bool _isDeployed;
	bool _isPulling;
	bool _ignorePartition;
	char *_extensionLib;
	bool _rebuildOnDeploy;
	char *_sourceLogPos;
	char *_targetLogPos;
	char *_sourceTranID;
	char *_targetTranID;
	RCESReplDirection _direction;
	int _sourceAgentID;
	int _targetAgentID;
	bool _isMonitorActive;
	RCESDateTime _monitorTime;
	int _refreshRate;
	bool _isExcepLogActive;
	RCESDateTime _excepLogTime;
	bool _isFuncTimeActive;
	RCESDateTime _funcTimeTime;
	bool _isPaused;
	RCESDateTime _pauseTime;
	bool _conflictDetection;
	bool _isFiltered;
	char *_fileFilter;
	bool _hasNAckExcep;
	bool _isInExceptionDump;

private:
	/* private methods */
	void _init();
	const char *_getDirectionStr();
	void _addStatusJson(pRCESMasterProvider masterProv, pRCESJson jsonObj);
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   RCESReplStatusInfo
*   Recon-e-Sense replication status info class
*
\******************************************************************************/
class RCESReplStatusInfo
{
public:
	/* Constructors & destructor */
	RCESReplStatusInfo();
	virtual ~RCESReplStatusInfo();

	/* Public methods */
	int GetActionID() { return _actionID; };
	RCESReplStatus GetStatus() { return _status; };
	bool GetIsMonitorActive() { return _isMonitorActive; };
	bool GetIsExcepLogActive() { return _isExcepLogActive; };
	bool GetIsFuncTimeActive() { return _isFuncTimeActive; };
	bool GetIsPaused() { return _isPaused; };

	void SetActionID(int actionID) { _actionID = actionID; };
	void SetStatus(RCESReplStatus status) { _status = status; };
	void SetIsMonitorActive(bool isMonitorActive) { _isMonitorActive = isMonitorActive; };
	void SetIsExcepLogActive(bool isExcepLogActive) { _isExcepLogActive = isExcepLogActive; };
	void SetIsFuncTimeActive(bool isFuncTimeActive) { _isFuncTimeActive = isFuncTimeActive; };
	void SetIsPaused(bool isPaused) { _isPaused = isPaused; };

private:
	/* private properties */
	int _actionID;
	RCESReplStatus _status;
	bool _isMonitorActive;
	bool _isExcepLogActive;
	bool _isFuncTimeActive;
	bool _isPaused;

	/* private methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESReplPlan *pRCESReplPlan, **ppRCESReplPlan;
typedef RCESReplStatusInfo *pRCESReplStatusInfo, **ppRCESReplStatusInfo;

#endif /* _FCRCESREPLPLAN_HPP_ */