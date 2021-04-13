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
 *      Copyright (c) 2013 - 2020 FairCom Corporation.
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

#ifndef _FCRCESCONFIG_HPP_
#define _FCRCESCONFIG_HPP_

#include "fc_rces.h"
#include "fcparam.hpp"
#include "fcconfig.hpp"
#include "fcrcesaux.hpp"
#include "fcaux.hpp"
#include "ctAgent.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Forward class and type definitions */
class RCESLogger;
typedef RCESLogger *pRCESLogger, **ppRCESLogger;

#define RCES_TRACE_DBENGINE "dbEngine"
#define RCES_TRACE_ENABLE "enable"
#define RCES_TRACE_WEBENABLE "webEnable"

class RCESDBEngineTrace {
public:
	RCESDBEngineTrace(int dbEngineID, bool enabled) {
		_dbEngineID = dbEngineID;
		_enabled = enabled;
	};

	virtual ~RCESDBEngineTrace() {};

	int GetDBEngineID() { return _dbEngineID; };
	bool GetEnabled() { return _enabled; };

private:
	int _dbEngineID;
	bool _enabled;
};
typedef RCESDBEngineTrace *pRCESDBEngineTrace, **ppRCESDBEngineTrace;

/*^****************************************************************************\
 *
 *   RCESConfig
 *   Recon-e-Sense configuration class
 *
 * Supported keywords from ctagent.json configuration file:
 *
 *  EMBEDDED YES - default is YES (it means if Replication Studio agent will be standalone or embedded in a DBEngine)
 *  LOG_FILE <file name> - default is NULL (no log)
 *  MEMPHIS_TYPE <CTREE> or <ODBC> - default is <CTREE>
 *  MEMPHIS_SERVER_NAME <master server name> - default is <MEMPHIS>
 *  MEMPHIS_SQL_PORT <master server SQL port> - default is <6597>
 *  MEMPHIS_HOST <master server host> - default is <>
 *  MEMPHIS_DATABASE <master database name> - default is <MEMPHIS>
 *  MEMPHIS_MAX_CONN <maximum master connection count> - default is <16>
 *  QUEUE_THREAD_COUNT <queue thread count for the non-ctree consumer> - default is 4
 *  LOCAL_CTREE_CHECK <YES or NO> - default is YES
 *  CTREE_CHECK_MASK <File mask to be checked as c-tree file>. Supported multiple masks delimited by [;] - default is <*.dat;*.idx>
 *  DBENGINE_CHECK <YES for automatic scan and track c-tree DBEngine changes> - default is YES
 *  VERBOSE_SCAN_COUNT <frequency of scan files to be displayed> or <0> - default is <0>
 *  VERBOSE_SHOW_NAME <YES for display file name on scan message displayed> or <NO> - default is <NO>
 *  LOCAL_CONN_POOL_SIZE <local connection pool size> - default is 50
 *  SCAN_THREAD_COUNT <scan thread count> - default is 50
 *  ADV_FULL_MASK <YES for enable the full mask advanced filter by the callback> - default is NO
 *  MASTER_CONN_POOL_SIZE = <master connection pool size> - default is 10
 *  LOAD_THREAD_COUNT = <load thread count to insert the filesystem blocks into the master DB> - default is 4
 *  STANDALONE_AGENT <YES for standalone agent only> - default is <YES>
 *  TRACE NO - default is NO  (enable the tracing for the Replication Studio agent)
 *  DBENGINE_CONN_BY_IP <YES | NO | ip address> - Define how the DBEngine should be connected by the Replication Studio - default is <NO>
 *  ACCEPT_CONN <YES | NO> - Flag indicating if the agent accept external connection or not - default is <YES>
 *  JVM_LIB <JBM library path> - default is <>, if embedded in a SQL server, use the JVM from SQL
 *  MANAGED <YES | NO> - Flag indicating if the agent is managed or not by Memphis - default is <YES>
 *  CFG_FILE_LIST <List of replication agent configuration names delimited by |> - default is <>
 *
 *  *** Memphis server specific keywords ***
 *  WEB_TRACE NO - default is NO  (enable the tracing for the Web Server)
 *  INACTIVE_TIMEOUT <pool inactive timeout in seconds> - default is 60 (1 minute)
 *  MEMPHIS_CONN_POOL_SIZE <memphis connection pool size> - default is 100
 *  CHECKSTATUS_WAIT <seconds to wait for the next DBEngine Status check> - default is 30 seconds
 *  DEBUG_WEB_API <YES for WEB API debug> - default is NO
 *  ARCHIVE_ACTION <number of days to wait before archiving ACTION events> - default is 1
 *  ARCHIVE_LOG <number of days to wait before archiving LOG events> - default is 7
 *  ARCHIVE_REPLSTAT <number of days to wait before archiving REPLSTAT events> - default is 7
 *  CHECK_DBENGINE_THRD_COUNT <number of threads to be used for checking DBEngines status> - default is 10
 *  CHECK_REPLPLAN_THRD_COUNT <number of threads to be used for checking Replication Plan status> - default is 5
 *
\******************************************************************************/
class RCESConfig : public FCConfig
{
public:
	/* Constructors & destructor */
	RCESConfig(const char *localPath, const char *configFileName, bool *isShutdown, RCESLogAgent agentType, p_ctplugin_checkLicense licenseCheckerFunc);
	RCESConfig(pCTAGENTTHD ctAgentThrdData, RCESLogAgent agentType);
	RCESConfig(const char *masterHost, const char *masterServerName, const char *masterSQLPort, const char *masterDatabase, const char *masterLogin, const char *masterPass, p_ctplugin_checkLicense licenseCheckerFunc);
	virtual ~RCESConfig();

	/* Public services */
	static int ctUpdateTrace(pRCESMasterProvider masterProv, int enableWebTrace, int globalEnableTrace, ppRCESDBEngineTrace traceList, int traceListCount);
	static int ctUpdateTrace(pRCESMasterProvider masterProv, int enableWebTrace, int globalEnableTrace, pRCESJson traceListObj, ppRCESJson result);
	static int ctGetTrace(pRCESMasterProvider masterProv, bool *globalTrace, bool *webTrace);
	static int ctGetTrace(pRCESMasterProvider masterProv, ppRCESJson result);

	static RCESParam GetKeyCd(const char *keyName);
	static const char *GetKeyName(RCESParam key);

	/* Public methods */
	bool Matches(pFCConfig config);
	const char *GetParam(const char *key);
	const char *GetParam(RCESParam param);
	bool HasCtreeLocalCheck() { return _hasCtreeLocalCheck; };
	bool HasMultiThreadScan() { return atoi(GetParam(SCAN_THREAD_COUNT)) > 0; };
	bool IsAdvFullMask() { return _isAdvFullMask; };
	static void PrintfConfigOptions();
	void GetUser(char *authFileName, char **userName, char **userPass);
	int GetLocalDBEngineID() { return _localDBEngineID; };
	int GetAgentID() { return _agentID; };
	bool IsEmbedded() { return _isEmbedded; };
	void *GetLocalLibHandle() { return _localLibHandle; };
	pRCESLogger GetLoggerLocal() { return _loggerLocal; };
	RCESLogAgent GetAgentType() { return _agentType; };
	const char *GetAgentName() { return _agentName; };
	const char *GetLocalServerName() { return _localServerName; };
	const char *GetLocalUserName() { return _localUserName; };
	const char *GetLocalUserPass() { return _localUserPass; };
	bool IsWebAPIDebug() { return _isWebAPIDebug; };
	int GetMemphisDBVolID() { return _memphisDBVolID; };
	const char *GetMemphisDBDir() { return _memphisDBDir; };
	const char *GetLocalPath() { return _localPath; };
	char *GetLocalPathBuffer();
	FCPool<RCESMasterConnPooled> *GetMasterConnPool() { return _masterConnPool; };
	bool IsShutDown() { return *_isShutDown != 0; };
	bool IsTrace() { return _isTrace; };
	bool IsWebTrace() { return _isWebTrace; };
	bool HasFSScan() { return _hasFSScan; };
	int GetMasterOS() { return _masterOS; };
	int GetAgentOS() { return _agentOS; };
	bool IsMasterAgent() { return _masterOS == _agentOS; };
	bool IsCheckDBEngine() { return _isCheckDBEngine; };
	const char *GetMasterLogin() { return _masterLogin; };
	const char *GetMasterPass() { return _masterPass; };
	FCHashTable<RCESReplPlanMngr> *GetReplPlanMngrHash() { return _replPlanMngrHash; };
	FCHashTable<RCESDBEngineMngr> *GetDBEngineMngrHash() { return _dbEngineMngrHash; };
	FCHashTable<RCESFailOverMngr> *GetFailOverMngrHash() { return _failOverMngrHash; };
	FCHashTable<ReplicationAgentData> *GetReplAgentDataHash() { return _replAgentDataHash; };
	FCHashTable<ReplicationMonitorData> *GetReplMonitorDataHash() { return _replMonitorDataHash; };
	FCHashTable<ReplicationDumpData> *GetReplDumpDataHash() { return _replDumpDataHash; };
	FCHashTable<RCESReplAgentMngr> *GetReplAgentMngrHash() { return _replAgentMngrHash; };
	RCESPlatform GetPlatform() { return _platform; };
	const char *GetPlatformName();
	bool GetAcceptConn() { return _acceptConn; }
	RCESReadOnly GetReadOnly() { return _readOnly; }
	const char *GetJVMLibPath() { return _jvmLibPath; };
	void CleanFailOverMngrHash();
	bool IsConnected();
	void Shutdown();
	int CheckLicense(ctPLUGIN_LIC_MODE mode) { if (_licenseChecker) return _licenseChecker(mode); else return false; };
	bool IsManaged() { return _managed; };
	char **GetCfgFileList() { return _cfgFileList; };
	int GetCfgFileCount() { return _cfgFileListCount; };

	void SetMasterOS(int masterOS) { _masterOS = masterOS; };
	void SetAgentOS(int agentOS) { _agentOS = agentOS; };
	void SetLocalDBEngineID(int localDBEngineID) { _localDBEngineID = localDBEngineID; };
	void SetAgentID(int agentID) { _agentID = agentID; };
	void SetIsEmbedded(bool isEmbedded) { _isEmbedded = isEmbedded; };
	void SetLocalLibHandle(void *localLibHandle) { _localLibHandle = localLibHandle; };
	void SetAgentType(RCESLogAgent agentType) { _agentType = agentType; };
	void SetAgentName(const char *agentName);
	void SetLocalServerName(const char *localServerName);
	void SetLocalUserName(const char *localUserName);
	void SetLocalUserPass(const char *localUserPass);
	void SetWebAPIDebug(bool enable) { _isWebAPIDebug = enable; };
	void SetMemphisDBVolID(int volumeID) { _memphisDBVolID = volumeID; };
	void SetMemphisDBDir(const char *dbDir);
	void SetLocalPath(const char *localPath);
	void SetMasterConnPool(FCPool<RCESMasterConnPooled> *masterConnPool) { _masterConnPool = masterConnPool; };
	void SetTrace(bool isTrace) { _isTrace = isTrace; };
	void SetWebTrace(bool webTrace) { _isWebTrace = webTrace; };
	void SetFSScan(bool fsScan) { _hasFSScan = fsScan; };
	void SetMasterLogin(const char *masterLogin);
	void SetMasterPass(const char *masterPass);
	void SetDBEngineMngrHash(FCHashTable<RCESDBEngineMngr> *dbEngineMngrHash) { _dbEngineMngrHash = dbEngineMngrHash; };
	void SetAcceptConn(bool acceptConn) { _acceptConn = acceptConn; };
	void SetReadOnly(RCESReadOnly readOnly) { _readOnly = readOnly; };
	void SetJVMLibPath(const char *jvmLibPath);
	void SetIsConnected(bool isConnected);

private:
	/* Private Properties */
	bool _hasCtreeLocalCheck;
	bool _isMemoryQueue;
	int _masterOS;
	int _agentOS;
	bool _isAdvFullMask;
	bool _isCheckDBEngine;
	RCESLogAgent _agentType;
	char *_agentName;
	int _localDBEngineID;
	int _agentID;
	bool _isEmbedded;
	void *_localLibHandle;
	pRCESLogger _loggerLocal;
	char *_localServerName;
	char *_localUserName;
	char *_localUserPass;
	bool _isWebAPIDebug;
	int _memphisDBVolID;
	char *_memphisDBDir;
	char *_localPath;
	int *_isShutDown;
	bool _freeShutdown;
	bool _isTrace;
	bool _isWebTrace;
	bool _hasFSScan;
	char *_masterLogin;
	char *_masterPass;
	FCHashTable<RCESReplPlanMngr> *_replPlanMngrHash;
	FCHashTable<RCESDBEngineMngr> *_dbEngineMngrHash;
	FCHashTable<ReplicationAgentData> *_replAgentDataHash;
	FCHashTable<ReplicationMonitorData> *_replMonitorDataHash;
	FCHashTable<ReplicationDumpData> *_replDumpDataHash;
	FCHashTable<RCESReplAgentMngr> *_replAgentMngrHash;
	RCESPlatform _platform;
	bool _acceptConn;
	RCESReadOnly _readOnly;
	char *_jvmLibPath;
	FCHashTable<RCESFailOverMngr> *_failOverMngrHash;
	void *_mutex;
	bool _isConnected;
	p_ctplugin_checkLicense _licenseChecker;
	bool _managed;
	char *_cfgFileListStr;
	int _cfgFileListCount;
	char **_cfgFileList;

	/* Private Methods */
	void _checkArguments(int argc, const char *argv[]);
	void _loadAdvConfig(const char *configFileName);
	void _loadAdvConfig(pCTAGENTTHD ctAgentThrdData);
	const char *_checkDefaultValue(RCESParam key);
	bool _cfgscan(char *line, char **key, char **value);
	void _init();
	FCPool<RCESMasterConnPooled> *_masterConnPool;
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESConfig *pRCESConfig, **ppRCESConfig;

#endif /* _FCRCESCONFIG_HPP_ */