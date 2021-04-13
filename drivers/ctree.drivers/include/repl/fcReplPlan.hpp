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

#ifndef _FCREPLPLAN_HPP_
#define _FCREPLPLAN_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesreplplan.hpp"
#include "fcrcesreplfunc.hpp"
#include "fcrcesreplagent.hpp"

/* Forward class declaration */
class FCREPLReplPlan;
class FCREPLReplStat;
class FCREPLReplParallelStat;
class FCREPLReplParallelAnalyzer;
class FCREPLReplParallelApply;
class FCREPLReplExcep;
class FCREPLReplFunc;
class FCREPLReplAgent;
typedef FCREPLReplPlan *pFCREPLReplPlan, **ppFCREPLReplPlan;
typedef FCREPLReplStat *pFCREPLReplStat, **ppFCREPLReplStat;
typedef FCREPLReplParallelStat *pFCREPLReplParallelStat, **ppFCREPLReplParallelStat;
typedef FCREPLReplParallelAnalyzer *pFCREPLReplParallelAnalyzer, **ppFCREPLReplParallelAnalyzer;
typedef FCREPLReplParallelApply *pFCREPLReplParallelApply, **ppFCREPLReplParallelApply;
typedef FCREPLReplExcep *pFCREPLReplExcep, **ppFCREPLReplExcep;
typedef FCREPLReplFunc *pFCREPLReplFunc, **ppFCREPLReplFunc;
typedef FCREPLReplAgent *pFCREPLReplAgent, **ppFCREPLReplAgent;

/* ReplicationStatus table */
typedef enum
{
	FCREPL_REPL_INACTIVE  = 0,
	FCREPL_REPL_ACTIVE    = 1,
	FCREPL_REPL_STOPPING  = 2,
	FCREPL_REPL_STARTING  = 3,
	FCREPL_REPL_DEPLOYING = 4,
	FCREPL_REPL_PAUSED    = 5,
	FCREPL_REPL_RESYNCING = 6,
	FCREPL_REPL_ARCHIVED  = 7
} FCREPLReplStatus;

/* Replication Direction table */
typedef enum
{
	FCREPL_REPL_NONE    = 0, /* Still there is not Subscription assigned, so no direction   */
	FCREPL_REPL_NORMAL  = 1, /* All the replications are from Source DBEngine to the Target */
	FCREPL_REPL_REVERSE = 2, /* All the replications are from Target DBEngine to the Source */
	FCREPL_REPL_BOTH    = 3  /* There are replication from Source and from Target DBEngines */
} FCREPLReplDirection;

/* Replication Plan Direction table */
typedef enum
{
	FCREPL_REPLPLAN_ORI = 0, /* Original replication direction */
	FCREPL_REPLPLAN_REV = 1  /* Reverse replication direction  */
} FCREPLReplicationDirection;

/* Replication Statistic state */
typedef enum
{
	FCREPL_STAT_TARGET = 0,
	FCREPL_STAT_SOURCE = 1,
	FCREPL_STAT_PAUSED = 2,
	FCREPL_STAT_SELF   = 3
} FCREPLReplicationState;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Replication Plan
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetReplPlans
*               Retrieve all the replication plan entity objects
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanList [OUT]
*               Replication plan entity list
*
*               replPlanCount [OUT]
*               Number of replication plan entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetReplPlans(pFCREPLConn replConn, ppFCREPLReplPlan *replPlanList, int *replPlanCount);

/*^****************************************************************************\
*
*   Function:   fcReplPersistReplPlan
*               Add a Replication Plan entity into the database. If there already
*               is a Replication Plan with the given name, update the existing
*               record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlan [IN]
*               Replication Plan entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistReplPlan(pFCREPLConn replConn, pFCREPLReplPlan replPlan);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveReplPlan
*               Delete the Replication Plan by its identification.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Replication Plan identification
*
*               recursive [IN]
*               Recursive flag
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveReplPlan(pFCREPLConn replConn, int replPlanID, bool recursive);

/*^****************************************************************************\
*
*   Function:   fcReplDeploy (Ctree Replication Deploy)
*               Deploy an existing replication plan. Make sure that the target
*               file is up-to-dated and then start the replication.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*               forceReplace [IN]
*               Flag indicating that we should replace existing target files
*
*               actionID [OUT]
*               Action identification for the FS load action
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplDeploy(pFCREPLConn replConn, int replPlanID, bool forceReplace, int *actionID);

/*^****************************************************************************\
*
*   Function:   fcReplStart
*               Start an existing replication plan already deployed.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*               sourceLogPos [IN]
*               Source log position to start at
*
*               targetLogPos [IN]
*               Target log position to start at
*
*               ignoreDeploy [IN]
*               Flag indicating if we should check that the Replication has been
*               deployed before starting it
*
*               actionID [OUT]
*               Action identification for the FS load action
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplStart(pFCREPLConn replConn, int replPlanID, const char *sourceLogPos, const char *targetLogPos, bool ignoreDeploy, int *actionID);

/*^****************************************************************************\
*
*   Function:   fcReplStop
*               Stop an existing replication plan already deployed/started.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*               waitForCheck [IN]
*               Wait for double checking current replication status
*
*               actionID [OUT]
*               Action identification for the FS load action
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplStop(pFCREPLConn replConn, int replPlanID, bool waitForCheck, int *actionID);

/*^****************************************************************************\
*
*   Function:   fcReplCheck
*               Retrieve the current Replication Plan status. If "checkConnection" 
*               is set, make some validations in order to update its status and 
*               return its information. In case of checkConnection for all the 
*               DBEngines, an action ID is returned and the execution will happen 
*               in background.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*               checkConn [IN]
*               Check connection flag
*
*               replPlanList [OUT]
*               Replication Plan list entity object
*
*               replPlanCount [OUT]
*               Number of Replication Plan objects in the list
*
*               actionID [OUT]
*               Action identification returned in case of checkConnection for
*               all the Replication Plans.
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplCheck(pFCREPLConn replConn, int replPlanID, bool checkConn, ppFCREPLReplPlan *replPlanList, int *replPlanCount, int *actionID);

/*^****************************************************************************\
*
*   Function:   fcReplCancel
*               Cancel the current replication plan action for deployment or
*               start or stop.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*               actionID [IN]
*               Replication action identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplCancel(pFCREPLConn replConn, int replPlanID, int actionID);

/*^****************************************************************************\
*
*   Function:   fcReplStartMonitor
*               Start monitoring a Replication Plan. It starts loading into
*               Memphis some statistics snapshots by a frequence defined by
*               "refreshRate" and also all the exception logs happened starting
*               at the current time. If the Replication Plan is bi-directional,
*               it will start monitoring both directions.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*               refreshRate [IN]
*               Refresh rate in seconds use for determining the frequence of the
*               logged statistics snapshots
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplStartMonitor(pFCREPLConn replConn, int replPlanID, int refreshRate);

/*^****************************************************************************\
*
*   Function:   fcReplStopMonitor
*               Stop monitoring a Replication Plan. The history of what has
*               already been monitored will be kept in Memphis, but from this
*               point, it will stop logging snapshots, If the Replication Plan
*               is bi-directional, it will stop monitoring both directions.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplStopMonitor(pFCREPLConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Function:   fcReplGetStats
*               Retrieve the statistics for the Replication Plan for a given
*               period of time. The snapshot is retrieved for direct, reverse or
*               both directions.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Replication plan identification
*
*               begin [IN]
*               Begin time for the statistics retrival
*
*               end [IN]
*               End time for the statistics retrival
*
*               statListSize [IN]
*               Statistics list count to be retrieved
*
*               statStart [IN]
*               Statistics list start record
*
*               statList [OUT]
*               Statistics entity list
*
*               statCount [OUT]
*               Number of statistics entities in the list
*
*               totalReplStats [OUT]
*               Total statistics
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetStats(pFCREPLConn replConn, int replPlanID, FCREPLDateTime begin, FCREPLDateTime end, int statListSize, int statStart, ppFCREPLReplStat *statList, int *statCount, int *totalReplStats);

/*^****************************************************************************\
*
*   Function:   fcReplStartExcepLog
*               Start logging Replication Plan's exceptions. It starts loading
*               into Memphis all the exceptions from the given Replication Plan.
*               This status is stored in Replication Plan's table. It is started
*               by default when the Replication Plan is started.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplStartExcepLog(pFCREPLConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Function:   fcReplStopExcepLog
*               Stop logging a Replication Plan's exceptions. The history of
*               what has already been logged will be kept in Memphis, but from
*               this point, it will stop logging exceptions.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplStopExcepLog(pFCREPLConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Function:   fcReplGetExceptions
*               Retrieve the exceptions for the Replication Plan for a given
*               period of time. The snapshot is retrieved for direct, reverse or
*               both directions.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Replication plan identification
*
*               begin [IN]
*               Begin time for the statistics retrival
*
*               end [IN]
*               End time for the statistics retrival
*
*               excepListSize [IN]
*               Exception list count to be retrieved
*
*               excepStart [IN]
*               Exception list start record
*
*               excepList [OUT]
*               Exception entity list
*
*               excepCount [OUT]
*               Number of exception entities in the list
*
*               totalReplExceps [OUT]
*               Total exceptions
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetExceptions(pFCREPLConn replConn, int replPlanID, FCREPLDateTime begin, FCREPLDateTime end, int excepListSize, int excepStart, ppFCREPLReplExcep *excepList, int *excepCount, int *totalReplExceps);

/*^****************************************************************************\
*
*   Function:   fcReplPlanFuncTimeStart
*               Start collecting Function Timing for a given Replication Plan
*               execution.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplPlanFuncTimeStart(pFCREPLConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Function:   fcReplPlanFuncTimeStop
*               Stop collecting Function Timing for a given Replication Plan
*               execution.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplPlanFuncTimeStop(pFCREPLConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Function:   fcReplPlanFuncTimeReset
*               Reset the Function Timing information collected for a given
*               Replication Plan execution.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplPlanFuncTimeReset(pFCREPLConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Function:   fcReplPlanGetFuncTimes
*               Retrieve the Function Timing information for a given Replication
*               Plan execution.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Replication plan identification
*
*               sourceFuncList [OUT]
*               Source function timing list
*
*               sourceFuncCount [OUT]
*               Source function timing count
*
*               targetFuncList [OUT]
*               Target function timing list
*
*               targetFuncCount [OUT]
*               Target function timing count
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplPlanGetFuncTimes(pFCREPLConn replConn, int replPlanID, ppFCREPLReplFunc *sourceFuncList, int *sourceFuncCount, ppFCREPLReplFunc *targetFuncList, int *targetFuncCount);

/*^****************************************************************************\
*
*   Function:   fcReplPlanPause
*               Pause a given Replication Plan execution.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplPlanPause(pFCREPLConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Function:   fcReplPlanResume
*               Resume a given Replication Plan execution.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplPlanResume(pFCREPLConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Function:   fcReplGetTempName
*               Retrieve the next available default name for a Replication Plan.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               tempReplPlanName [OUT]
*               JSON with the temporary replication plan name
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetTempName(pFCREPLConn replConn, char *tempReplPlanName);

/*^****************************************************************************\
*
*   Function:   fcReplScanAgent
*               Retrieve all the current Replication Agents by the given criteria
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               osID [IN]
*               OpSystem identification
*
*               basePath [IN]
*               Base path to start the scan
*
*               replAgentList [OUT]
*               Replication agent list
*
*               replAgentCount [OUT]
*               Number of Replication agent in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplScanAgent(pFCREPLConn replConn, int osID, const char *basePath, ppFCREPLReplAgent *replAgentList, int *replAgentCount);

/*^****************************************************************************\
*
*   Function:   fcReplImportAgent
*               Import a list of Replication Agent setups into Replication Studio.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               simpleMode [IN]
*               Flag indicating if the import is supposed to be executed for
*               simple mode, meaning that some default values are assumed
*
*               replAgentList [INOUT]
*               Replication agent list
*
*               replAgentCount [INOUT]
*               Number of Replication agent in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplImportAgent(pFCREPLConn replConn, bool simpleMode, ppFCREPLReplAgent replAgentList, int replAgentCount);

/*^****************************************************************************\
*
*   Function:   fcReplAckExceptions
*               Acknowledge all the Replication Exceptions up to the current
*               moment a given Replication Plan execution.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Existing replication plan identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplAckExceptions(pFCREPLConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Function:   fcReplResyncFiles
*               Resync of published Files.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Replication Plan identification
*
*               fileIDList [IN]
*               Existing Published File identification list
*
*               fileCount [IN]
*               Number of Published Files to be added
*
*               actionID [OUT]
*               Action identification for the resync action
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplResyncFiles(pFCREPLConn replConn, int replPlanID, int *fileIDList, int fileCount, int *actionID);

/*^****************************************************************************\
*
*   Function:   fcReplGetArchivedReplPlans
*               Retrieve all the archived replication plan entity objects
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanList [OUT]
*               Replication plan entity list
*
*               replPlanCount [OUT]
*               Number of replication plan entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetArchivedReplPlans(pFCREPLConn replConn, ppFCREPLReplPlan *replPlanList, int *replPlanCount);

/*^****************************************************************************\
*
*   Method:     fcReplPlanArchive
*               Archive Replication Plan
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Replication plan identification
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPlanArchive(pRCESConn replConn, int replPlanID);

/*^****************************************************************************\
*
*   Method:     fcReplPlanRestore
*               Restore Replication Plan
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Replication plan identification
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPlanRestore(pRCESConn replConn, int replPlanID);



/*^****************************************************************************\
*
*   Class:      FCREPLReplPlan
*               A Replication Plan entity links two DBEngines, so multiple
*               subscriptions (FCREPLSubscription) instances can be part of that
*               in different directions, but all of them must be between the
*               same two DBEngine nodes.
*
\******************************************************************************/
class FCREPL_API FCREPLReplPlan : public RCESReplPlan
{
public:
	FCREPLReplPlan();
	FCREPLReplPlan(pFCREPLJson replPlan);

/*
** Getters
*/

	// Replication Plan status
	FCREPLReplStatus GetStatus() { return (FCREPLReplStatus)((pRCESReplPlan)this)->GetStatus(); };

	// Replication direction
	FCREPLReplDirection GetDirection() { return (FCREPLReplDirection)((pRCESReplPlan)this)->GetDirection(); };

/*
	Inherited getters

	// Replication Plan identification
	int GetID();

	// Replication Plan name
	char *GetName();

	// Replication Plan Description
	char *GetDescription();

    // Replication status code
    RCESReplStatus GetStatus();

	// Last time Replication Plan status has changed
	RCESDateTime GetStatusTime();

	// Message related to the Replication Plan status
	char *GetStatusMsg();

	// Action identification responsible for the Replication Plan new status.
	// It is linked to FCREPLAction class.
	int GetStatusActionID();

	// Source DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	int GetSourceDBEngineID();

    // Source DB engine ID
    virtual pRCESDBEngine GetSourceDBEngine();

	// Target DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	int GetTargetDBEngineID();

    // Target DB engine
    virtual pRCESDBEngine GetTargetDBEngine();

	// Is synchronous replication
	bool GetIsSync();

    // Warning threshold
    int GetWarningThreshold();
 
    // Error threshold
    int GetErrorThreshold();
 
    // Latency
    int GetLatency();
 
    // Latency time
    RCESDateTime GetLatencyTime();
 
    // Latency rev
    int GetLatencyRev();
 
    // Latency rev time
    RCESDateTime GetLatencyRevTime();

    // File mask
    char *GetFileMask();

	// Return if the Replication Plan has already been deployed
	bool GetIsDeployed();

	// Return if the Relication Plan is "pulling" (agent running on target)
	bool GetIsPulling();

	// Return if the Relication Plan is transforming partitioned source files into non-partitioned target ones
	bool GetIgnorePartition();

	// Extension library for the replication plan
	char *GetExtensionLib();

	// Return if during the deploy we are copying only the data files and index will be rebuilt
	bool GetRebuildOnDeploy();

	// Source transaction log position
	char *GetSourceLogPos();

	// Target transaction log position
	char *GetTargetLogPos();

    // Source transaction ID
    char *GetSourceTranID();
 
    // Target transaction ID
    char *GetTargetTranID();

	// Source Replication Studio agent identification.
	// It is linked to FCREPLDBAgent class.
	int GetSourceAgentID();

	// Target Replication Studio agent identification.
	// It is linked to FCREPLDBAgent class.
	int GetTargetAgentID();

	// Return if the Replication monitor feature is active.
	bool GetIsMonitorActive();

	// Time that the Replication monitor has been enabled or disabled.
	RCESDateTime GetMonitorTime();

    // Direction
    RCESReplDirection GetDirection();
 
    // Refresh rate
    int GetRefreshRate();

	// Return if the Replication exception log monitor is active.
	bool GetIsExcepLogActive();

	// Time that the Replication exception log monitor has been enabled or disabled.
	RCESDateTime GetExcepLogTime();

	// Return if the Replication function profiling is active.
	bool GetIsFuncTimeActive();

	// Time that the Replication function profiling has been enabled or disabled.
	RCESDateTime GetFuncTimeTime();

	// Return if the Replication is paused.
	bool GetIsPaused();

	// Time that the Replication has been psued or resumed.
	RCESDateTime GetPauseTime();

	// Replication has a filter on the source file to be replicated.
	bool IsFiltered();

	// File name with the Replication file filter.
	char *GetFileFilter();

    // Flag indicating if Replication Plan any non acknowledged exception
    bool HasNAckExcep();
 
    // Flag indicating if Replication Plan is during a exception dump process
    bool IsInExceptionDump();

	// Return if the Replication has an agent running on the source node.
	bool HasAgentOnSource();

	// Return if the Replication has an agent running on the target node.
	bool HasAgentOnTarget();

	
	** Following are c-tree replication specific setup. Please find more details on ctreplagent.cfg documentation
	
	// Replication batch size: batch_size
	int GetBatchSize();

	// Replication debug minimum log position: dbgminlog
	bool GetDebugMinLog();

	// Replication exception mode: exception_mode
	int GetExceptionMode();

	// Replication lock retry count: lock_retry_count
	int GetLockRetryCount();

	// Replication lock retry sleep: lock_retry_sleep
	int GetLockRetrySleep();

	// Replication log change details: log_change_details
	char *GetLogChangeDetails();

	// Replication read timeout: read_timeout_ms
	int GetReadTimeout();

	// Replication remember log position: remember_log_pos
	bool GetRememberLogPos();

	// Replication parallel apply enable flag: parallel_apply
	bool GetParallelApply();

	// Replication check dependencies enable flag: check_dependencies
	bool GetCheckDependencies();

	// Replication sync log writes enable flag: sync_log_writes
	bool GetSyncLogWrites();

	// Replication analyzer threads count: analyzer_threads_count
	int GetAnalyzerThreadsCount();

	// Replication apply threads count: apply_threads_count
	int GetApplyThreadsCount();

	// Replication conflict detection: check_update
	bool GetConflictDetection();
*/


/*
** Setters
*/

	// Replication Plan status
	void SetStatus(FCREPLReplStatus status) { ((pRCESReplPlan)this)->SetStatus((RCESReplStatus)status); };

	// Source DBEngine object
	void SetSourceDBEngine(pFCREPLDBEngine sourceDBEngine) { ((pRCESReplPlan)this)->SetSourceDBEngine((pRCESDBEngine)sourceDBEngine); };

	// Target DBEngine object
	void SetTargetDBEngine(pFCREPLDBEngine targetDBEngine) { ((pRCESReplPlan)this)->SetTargetDBEngine((pRCESDBEngine)targetDBEngine); };

	// Replication Plan name
	void SetName(const char *name) { ((pRCESReplPlan)this)->SetName(name);  };

	// Replication Plan Description
	void SetDescription(const char *description) { ((pRCESReplPlan)this)->SetDescription(description); };

	// Message related to the Replication Plan status
	void SetStatusMsg(const char *statusMsg) { ((pRCESReplPlan)this)->SetStatusMsg(statusMsg); };

	// Source transaction log position
	void SetSourceLogPos(const char *sourceLogPos) { ((pRCESReplPlan)this)->SetSourceLogPos(sourceLogPos); };

	// Target transaction log position
	void SetTargetLogPos(const char *targetLogPos) { ((pRCESReplPlan)this)->SetTargetLogPos(targetLogPos); };

	// File name with the Replication file filter
	void SetFileFilter(const char *fileFilter) { ((pRCESReplPlan)this)->SetFileFilter(fileFilter); };

	// Replication log change details: log_change_details
	void SetLogChangeDetails(const char *logChangeDetails) { ((pRCESReplPlan)this)->SetLogChangeDetails(logChangeDetails); };

	// Extension library
	void SetExtensionLib(const char *extensionLib) { ((pRCESReplPlan)this)->SetExtensionLib(extensionLib); };

/*
	Inherited setters

	// Replication Plan identification
	void SetID(int id);

    // Replication Plan name
    void SetName(const char *name);
 
    // Replication Plan description
    void SetDescription(const char *description);
 
    // Replication Plan status
    void SetStatus(RCESReplStatus status);

	// Last time Replication Plan status has changed
	void SetStatusTime(RCESDateTime statusTime);

    // Replication Plan message
    void SetStatusMsg(const char *statusMsg);

	// Action identification responsible for the Replication Plan new status.
	// It is linked to FCREPLAction class.
	void SetStatusActionID(int statusActionID);

	// Source DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	void SetSourceDBEngineID(int sourceDBEngineID);

    // Source DB engine
    void SetSourceDBEngine(pRCESDBEngine sourceDBEngine);

	// Target DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	void SetTargetDBEngineID(int targetDBEngineID);

    // Target DB engine
    void SetTargetDBEngine(pRCESDBEngine targetDBEngine);

	// Is synchronous replication
	void SetIsSync(bool isSync);

    // Warning threshold
    void SetWarningThreshold(int warningThreshold);
 
    // Error threshold
    void SetErrorThreshold(int errorThreshold);
 
    // Latency
    void SetLatency(int latency);
 
    // Latency time
    void SetLatencyTime(RCESDateTime latencyTime);
 
    // Latency rev
    void SetLatencyRev(int latencyRev);
 
    // Latency rev time
    void SetLatencyRevTime(RCESDateTime latencyRevTime);

    // Log change details
    void SetLogChangeDetails(const char *logChangeDetails);
 
    // Parallel apply
    void SetParallelApply(bool parallelApply);
 
    // Check dependencies
    void SetCheckDependencies(bool checkDependencies);
 
    // Sync log writes
    void SetSyncLogWrites(bool syncLogWrites);
 
    // Analyzer threads count
    void SetAnalyzerThreadsCount(int analyzerThreadsCount);
 
    // Apply threads count
    void SetApplyThreadsCount(int applyThreadsCount);
 
    // File mask
    void SetFileMask(const char *fileMask);

	// Replication Plan has already been deployed
	void SetIsDeployed(bool isDeployed);

	// Relication Plan is "pulling" (agent running on target)
	void SetIsPulling(bool isPulling);

	// Relication Plan is transforming partitioned source files into non-partitioned target ones
	void SetIgnorePartition(bool ignorePartition);

	// Return if during the deploy we are copying only the data files and index will be rebuilt
	void SetRebuildOnDeploy(bool rebuildOnDeploy);

    // Source log position
    void SetSourceLogPos(const char *sourceLogPos);
 
    // Target log position
    void SetTargetLogPos(const char *targetLogPos);
 
    // Source transaction ID
    void SetSourceTranID(const char *sourceTranID);
 
    // Target transaction ID
    void SetTargetTranID(const char *targetTranID);

	// Source Replication Studio agent identification.
	// It is linked to FCREPLDBAgent class.
	void SetSourceAgentID(int sourceAgentID);

	// Target Replication Studio agent identification.
	// It is linked to FCREPLDBAgent class.
	void SetTargetAgentID(int targetAgentID);

    // Replication direction
    void SetDirection(ppRCESSubscription subsList, int subsCount);

	// Replication monitor feature is active.
	void SetIsMonitorActive(bool isMonitorActive);

	// Time that the Replication monitor has been enabled or disabled.
	void SetMonitorTime(RCESDateTime monitorTime);

    // Replication refresh rate
    void SetRefreshRate(int refreshRate);

	// Replication exception log monitor is active.
	void SetIsExcepLogActive(bool isExcepLogActive);

	// Time that the Replication exception log monitor has been enabled or disabled.
	void SetExcepLogTime(RCESDateTime excepLogTime);

	// Replication function profiling is active.
	void SetIsFuncTimeActive(bool isFuncTimeActive);

	// Time that the Replication function profiling has been enabled or disabled.
	void SetFuncTimeTime(RCESDateTime funcTimeTime);

	// Replication is paused
	void SetIsPaused(bool isPaused);

	// Time that the Replication has been psued or resumed.
	void SetPauseTime(RCESDateTime pausedTime);

	// Replication has a filter on the source file to be replicated
	void SetIsFiltered(bool isFiltered);

    // Replication file filter
    void SetFileFilter(const char *fileFilter);

	// Flag indicating if Replication Plan any non acknowledged exception
	void SetHasNAckExcep(bool hasNAckExcep);

	// Flag indicating if Replication Plan is during a exception dump process
	void SetIsInExceptionDump(bool isInExceptionDump);


	** Following are c-tree replication specific setup. Please find more details on ctreplagent.cfg documentation

	// Replication batch size: batch_size
	void SetBatchSize(int batchSize);

	// Replication debug minimum log position: dbgminlog
	void SetDebugMinLog(bool debugMinLog);

	// Replication exception mode: exception_mode
	void SetExceptionMode(int exceptionMode);

	// Replication lock retry count: lock_retry_count
	void SetLockRetryCount(int lockRetryCount);

	// Replication lock retry sleep: lock_retry_sleep
	void SetLockRetrySleep(int lockRetrySleep);

	// Replication read timeout: read_timeout_ms
	void SetReadTimeout(int readTimeout);

	// Replication remember log position: remember_log_pos
	void SetRememberLogPos(bool rememberLogPos);

	// Replication conflict detection: check_update
	void SetConflictDetection(bool conflictDetection);
*/
};

/*^****************************************************************************\
*
*   Class:      FCREPLReplStat
*               A Replication Plan Statistic entity has a set of monitoring
*               information specific for a given Replication Plan. 
*
\******************************************************************************/
class FCREPL_API FCREPLReplStat : public RCESReplStat
{
public:
	FCREPLReplStat();

/*
** Getters
*/

	// Replication Plan direction: Original or Reverse
	FCREPLReplicationDirection GetDirection() { return (FCREPLReplicationDirection)((pRCESReplStat)this)->GetDirection(); };

	// Replication Plan state
	FCREPLReplicationState GetState() { return (FCREPLReplicationState)((pRCESReplStat)this)->GetState(); };

/*
	Inherited setters

	// Replication Plan identification.
	// It is linked to FCREPLReplPlan class.
	int GetReplPlanID();

    // Direction
    RCESReplicationDirection GetDirection();

	// Statistic time.
	RCESDateTime GetTime();

	// Return if source DBEngine is connected.
	bool GetIsSourceDBConnected();

	// Return if target DBEngine is connected.
	bool GetIsTargetDBConnected();

	// Transaction log file number.
	int GetLogNumber();

	// Transaction log position.
	int GetLogPosition();

    // State
    RCESReplicationState GetState();

	// Statistic sequence number.
	RCESBigInt GetSequenceNumber();

	// Statistic function name.
	char *GetFunctionName();

	// Number of Commit pass.
	RCESBigInt GetCommitPass();

	// Number of Add pass.
	RCESBigInt GetAddPass();

	// Number of Delete pass.
	RCESBigInt GetDeletePass();

	// Number of Update pass.
	RCESBigInt GetUpdatePass();

	// Number of Commit fail.
	RCESBigInt GetCommitFail();

	// Number of Add fail.
	RCESBigInt GetAddFail();

	// Number of Dele fail.
	RCESBigInt GetDeleteFail();

	// Number of Update fail.
	RCESBigInt GetUpdateFail();

	// Replication latency.
	int GetLatency();
*/


/*
** Setters
*/

	// Replication Plan direction: Original or Reverse
	void SetDirection(FCREPLReplicationDirection direction) { ((pRCESReplStat)this)->SetDirection((RCESReplicationDirection)direction); };

	// Replication Plan state
	void SetState(FCREPLReplicationState state) { ((pRCESReplStat)this)->SetDirection((RCESReplicationDirection)state); };

	// Statistic function name.
	void SetFunctionName(const char *functionName) { ((pRCESReplStat)this)->SetFunctionName(functionName); };

/*
	Inherited setters

	// Replication Plan identification.
	// It is linked to FCREPLReplPlan class.
	void SetReplPlanID(int replPlanID);

    // Direction
    void SetDirection(RCESReplicationDirection direction);

	// Statistic time.
	void SetTime(RCESDateTime time);

	// Return if source DBEngine is connected.
	void SetIsSourceDBConnected(bool isSourceDBConnected);

	// Return if target DBEngine is connected.
	void SetIsTargetDBConnected(bool isTargetDBConnected);

	// Transaction log file number.
	void SetLogNumber(int logNumber);

	// Transaction log position.
	void SetLogPosition(int logPosition);

    // State
    void SetState(RCESReplicationState state);

	// Statistic sequence number.
	void SetSequenceNumber(RCESBigInt sequenceNumber);

    // Function name
    void SetFunctionName(const char *functionName);

	// Number of Commit pass.
	void SetCommitPass(RCESBigInt commitPass);

	// Number of Add pass.
	void SetAddPass(RCESBigInt addPass);

	// Number of Delete pass.
	void SetDeletePass(RCESBigInt deletePass);

	// Number of Update pass.
	void SetUpdatePass(RCESBigInt updatePass);

	// Number of Commit fail.
	void SetCommitFail(RCESBigInt commitFail);

	// Number of Add fail.
	void SetAddFail(RCESBigInt addFail);

	// Number of Dele fail.
	void SetDeleteFail(RCESBigInt deleteFail);

	// Number of Update fail.
	void SetUpdateFail(RCESBigInt updateFail);

	// Replication latency.
	void SetLatency(int latency);
*/
};

/*^****************************************************************************\
*
*   Class:      FCREPLReplParallelAnalyzer
*               A Replication Plan Analyzer Statistic entity has a set of 
*               monitoring information specific for a given Replication Plan.
*
\******************************************************************************/
class FCREPL_API FCREPLReplParallelAnalyzer : public RCESReplParallelAnalyzer
{
public:
	FCREPLReplParallelAnalyzer();

	/*
	** Getters
	*/

	// Replication state
	FCREPLReplicationState GetState() { return (FCREPLReplicationState)((pRCESReplParallelAnalyzer)this)->GetState(); };


	/*
	** Setters
	*/

	// Replication state
	void SetState(FCREPLReplicationState state) { ((pRCESReplParallelAnalyzer)this)->SetState((RCESReplicationState)state); };
};

/*^****************************************************************************\
*
*   Class:      FCREPLReplParallelApply
*               A Replication Plan Apply Statistic entity has a set of
*               monitoring information specific for a given Replication Plan.
*
\******************************************************************************/
class FCREPL_API FCREPLReplParallelApply : public RCESReplParallelApply
{
public:
	FCREPLReplParallelApply();

	/*
	** Getters
	*/

	// Replication state
	FCREPLReplicationState GetState() { return (FCREPLReplicationState)((pRCESReplParallelApply)this)->GetState(); };


	/*
	** Setters
	*/

	// Replication state
	void SetState(FCREPLReplicationState state) { ((pRCESReplParallelApply)this)->SetState((RCESReplicationState)state); };
};

/*^****************************************************************************\
*
*   Class:      FCREPLReplParallelStat
*               A Replication Plan Statistic entity has a set of monitoring
*               information specific for a given Replication Plan.
*
\******************************************************************************/
class FCREPL_API FCREPLReplParallelStat : public RCESReplParallelStat
{
public:
	FCREPLReplParallelStat();

	/*
	** Getters
	*/

	// Replication Plan direction: Original or Reverse
	FCREPLReplicationDirection GetDirection() { return (FCREPLReplicationDirection)((pRCESReplParallelStat)this)->GetDirection(); };

	// Replication LogShip state
	FCREPLReplicationState GetLogShipState() { return (FCREPLReplicationState)((pRCESReplParallelStat)this)->GetLogShipState(); };

	// Replication LogRead state
	FCREPLReplicationState GetLogReadState() { return (FCREPLReplicationState)((pRCESReplParallelStat)this)->GetLogReadState(); };

	// Replication Dependency state
	FCREPLReplicationState GetDependencyState() { return (FCREPLReplicationState)((pRCESReplParallelStat)this)->GetDependencyState(); };

	// Replication Analyzer List
	ppFCREPLReplParallelAnalyzer GetAnalyzerList() { return (ppFCREPLReplParallelAnalyzer)((pRCESReplParallelStat)this)->GetAnalyzerList(); };

	// Replication Apply List
	ppFCREPLReplParallelApply GetApplyList() { return (ppFCREPLReplParallelApply)((pRCESReplParallelStat)this)->GetApplyList(); };


	/*
	** Setters
	*/

	// Replication Plan direction: Original or Reverse
	void SetDirection(FCREPLReplicationDirection direction) { ((pRCESReplParallelStat)this)->SetDirection((RCESReplicationDirection)direction); };

	// Replication LogShip state
	void SetLogShipState(FCREPLReplicationState state) { ((pRCESReplParallelStat)this)->SetLogShipState((RCESReplicationState)state); };

	// Replication LogRead state
	void SetLogReadState(FCREPLReplicationState state) { ((pRCESReplParallelStat)this)->SetLogReadState((RCESReplicationState)state); };

	// Replication Dependency state
	void SetDependencyState(FCREPLReplicationState state) { ((pRCESReplParallelStat)this)->SetDependencyState((RCESReplicationState)state); };

	// Replication Analyzer List
	void SetAnalyzerList(ppFCREPLReplParallelAnalyzer analyzerList) { ((pRCESReplParallelStat)this)->SetAnalyzerList((ppRCESReplParallelAnalyzer)analyzerList); };

	// Replication Apply List
	void SetApplyList(ppFCREPLReplParallelApply applyList) { ((pRCESReplParallelStat)this)->SetApplyList((ppRCESReplParallelApply)applyList); };
};

/*^****************************************************************************\
*
*   Class:      FCREPLReplExcep
*               A Replication Plan Exception entity has a exception event
*               detail information for a Replication Plan.
*
\******************************************************************************/
class FCREPL_API FCREPLReplExcep : public RCESReplExcep
{
public:
	FCREPLReplExcep();
	

/*
** Getters
*/

	// Replication Plan direction: Original or Reverse
	FCREPLReplicationDirection GetDirection() { return (FCREPLReplicationDirection)((pRCESReplExcep)this)->GetDirection(); };

/*
	Inherited getters

	// Replication Plan identification.
	// It is linked to FCREPLReplPlan class.
	int GetReplPlanID();

    // Replication Direction
    RCESReplicationDirection GetDirection();
 
    // Replication exception sequence number.
    RCESBigInt GetSequenceNumber();

	// Replication exception time.
	RCESDateTime GetTime();

    // Transaction number.
    RCESBigInt GetTransactionNumber();

    // Transaction log entry time.
    RCESDateTime GetLogEntryTime();

	// Transaction log file number.
	int GetLogNumber();

	// Transaction log position.
	int GetLogPosition();

	// File identification.
	int GetFileID();

	// Replication operation name.
	const char *GetOperation();

	// Exception error code.
	int GetErrorCode();

	// File name.
	const char *GetFileName();
*/


/*
** Setters
*/

	// Replication Plan direction: Original or Reverse
	void SetDirection(FCREPLReplicationDirection direction) { ((pRCESReplExcep)this)->SetDirection((RCESReplicationDirection)direction); };

	// Replication operation name.
	void SetOperation(const char *operation) { ((pRCESReplExcep)this)->SetOperation(operation); };

	// File name.
	void SetFileName(const char *fileName) { ((pRCESReplExcep)this)->SetFileName(fileName); };

/*
	Inherited setters

	// Replication Plan identification.
	// It is linked to FCREPLReplPlan class.
	void SetReplPlanID(int replPlanID);

    // Replication direction
    void SetDirection(RCESReplicationDirection direction);

    // Replication exception sequence number.
    void SetSequenceNumber(RCESBigInt sequenceNumber);

	// Replication exception time.
	void SetTime(RCESDateTime time);

    // Transaction number.
    void SetTransactionNumber(RCESBigInt transactionNumber);

    // Transaction log entry time.
    void SetLogEntryTime(RCESDateTime logEntryTime);

	// Transaction log file number.
	void SetLogNumber(int logNumber);

	// Transaction log position.
	void SetLogPosition(int logPostion);

	// File identification.
	void SetFileID(int fileID);

    // Operation
    void SetOperation(const char *operation);

	// Exception error code.
	void SetErrorCode(int errorCode);

    // File name
    void SetFileName(const char *fileName);
*/
};

/*^****************************************************************************\
*
*   Class:      FCREPLReplFunc
*               A Replication Plan Function Timing entity has the profiling
*               information by Function call for a specific Replication Plan.
*
\******************************************************************************/
class FCREPL_API FCREPLReplFunc : public RCESReplFunc
{
public:
	FCREPLReplFunc();

/*
** Getters
*/

/*
	Inherited getters

	// Replication function name.
	const char *GetName();

	// Total percentage time spent on this function.
	int GetTotalPercent();

	// Total time spent on this function.
	RCESBigInt GetTotalTime();

	// Number of calls for this function.
	RCESBigInt GetCalls();

	// Average time spent on this function call.
	RCESBigInt GetAverageTime();
*/


/*
** Setters
*/

	// Replication function name.
	void SetName(const char *name) { ((pRCESReplFunc)this)->SetName(name); };

/*
	Inherited setters

    // Name
    void SetName(const char *name);

    // Total percentage time spent on this function.
	void SetTotalPercent(int totalPercent);

	// Total time spent on this function.
	void SetTotalTime(RCESBigInt totalTime);

	// Number of calls for this function.
	void SetCalls(RCESBigInt calls);

	// Average time spent on this function call.
	void SetAverageTime(RCESBigInt averageTime);
*/
};

/*^****************************************************************************\
*
*   Class:      FCREPLReplAgent
*               A Replication Agent entity refers to an existing Replication 
*               Agent physically set based on the previous technology 
*               (ctreplagent).
*
\******************************************************************************/
class FCREPL_API FCREPLReplAgent : public RCESReplAgent
{
public:
	FCREPLReplAgent();
	FCREPLReplAgent(pFCREPLJson replAgent);

/*
** Getters
*/

/*
	Inherited getters

	// Action identification for the Replication Agent.
	// It is linked to the FCREPLAction class.
	int GetActionID();

	// Replication Agent OpSystem identification.
	// It is linked to the FCREPLOpSystem class.
	int GetOSID();

	// Replication Agent path.
	const char *GetPath();

	// Replication Agent name.
	const char *GetName();

	// Source server connection string.
	const char *GetSourceServer();

	// Target server connection string.
	const char *GetTargetServer();

	// Source server node identification.
	const char *GetSourceNodeID();

	// Source server node identification.
	const char *GetTargetNodeID();

	// Error code.
	RCESRET GetErrorCode();

	// Error message.
	const char *GetErrorMsg();

	// Replication Plan name.
	const char *GetReplPlanName();

	// Replication Plan description.
	const char *GetReplPlanDesc();

	// Publication identification.
	// It is linked to the FCREPLPublication class.
	int GetPubID();

	// Publication name.
	const char *GetPubName();

	// Publication description.
	const char *GetPubDesc();

	// Publication database identification.
	// It is linked to the FCREPLPublication class.
	int GetPubDatabaseID();

	// Subscription name.
	const char *GetSubsName();

	// Subscription description.
	const char *GetSubsDesc();

	// Subscription database identification.
	// It is linked to the FCREPLDatabase class.
	int GetSubsDatabaseID();
*/


/*
** Setters
*/

	// Replication Agent path.
	void SetPath(const char *path) { ((pRCESReplAgent)this)->SetPath(path); };

	// Replication Agent name.
	void SetName(const char *name) { ((pRCESReplAgent)this)->SetName(name); };

	// Source server connection string.
	void SetSourceServer(const char *sourceServer) { ((pRCESReplAgent)this)->SetSourceServer(sourceServer); };

	// Target server connection string.
	void SetTargetServer(const char *targetServer) { ((pRCESReplAgent)this)->SetTargetServer(targetServer); };

	// Source server node identification.
	void SetSourceNodeID(const char *sourceNodeID) { ((pRCESReplAgent)this)->SetSourceNodeID(sourceNodeID); };

	// Source server node identification.
	void SetTargetNodeID(const char *targetNodeID) { ((pRCESReplAgent)this)->SetTargetNodeID(targetNodeID); };

	// Error message.
	void SetErrorMsg(const char *errorMsg) { ((pRCESReplAgent)this)->SetErrorMsg(errorMsg); };

/*
	Inherited setters

	// Action identification for the Replication Agent.
	// It is linked to the FCREPLAction class.
	void SetActionID(int actionID);

	// Replication Agent OpSystem identification.
	// It is linked to the FCREPLOpSystem class.
	void SetOSID(int osID);

    // Path
    void SetPath(const char *path);
 
    // Name
    void SetName(const char *name);
 
    // Source server
    void SetSourceServer(const char *sourceServer);
 
    // Target server
    void SetTargetServer(const char *targetServer);
 
    // Source node ID
    void SetSourceNodeID(const char *sourceNodeID);
 
    // Target node ID
    void SetTargetNodeID(const char *targetNodeID);

	// Error code.
	void SetErrorCode(RCESRET errorCode);

    // Error message
    void SetErrorMsg(const char *errorMsg);
*/
};

#endif /* _FCREPLPLAN_HPP_ */
