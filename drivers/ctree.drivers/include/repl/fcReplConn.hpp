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

#ifndef _FCREPLCONN_HPP_
#define _FCREPLCONN_HPP_

#include "fcReplCommon.hpp"
#include "fcReplLog.hpp"
#include "fcrcesconn.hpp"

/* Forward class declaration */
class FCREPLConfig;
typedef FCREPLConfig *pFCREPLConfig, **ppFCREPLConfig;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Connection
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplConnect (Ctree Replication connection)
*               Create a connection object for the Memphis database based on a
*               configuration object.
*               It will keep the config object, logger object and database
*               connection.
*
*   Parameters: config [IN]
*               Configuration object
*
*               replConn [OUT]
*               New replication connection object
*
*               errorMsg [OUT]
*               Error message buffer
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplConnect(pFCREPLConfig config, ppFCREPLConn replConn, char **errorMsg);

/*^****************************************************************************\
*
*   Function:   fcReplConnect (Ctree Replication connection)
*               Create a connection object for the Memphis database based on
*               Memphis login information. It will create internally a basic
*               configuration object.
*               It will keep the config object, logger object and database
*               connection.
*
*   Parameters: masterHost [IN]
*               Master server host
*
*               masterServerName [IN]
*               Master server name
*
*               masterSQLPort [IN]
*               Master SQL port
*
*               masterDatabase [IN]
*               Master database name
*
*               masterLogin [IN]
*               Master database user login
*
*               masterPass [IN]
*               Master database user password
*
*               replConn [OUT]
*               New replication connection handle
*
*               errorMsg [OUT]
*               Error message buffer
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplConnect(const char *masterHost, const char *masterServerName, const char *masterSQLPort, const char *masterDatabase, const char *masterLogin, const char *masterPass, ppFCREPLConn replConn, char **errorMsg);

/*^****************************************************************************\
*
*   Function:   fcReplDisconnect (Ctree Replication connection)
*               Disconnect from Memphis database.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplDisconnect(pFCREPLConn replConn);



/*^****************************************************************************\
*
*   Class:      FCREPLConfig
*               Replication Studio settings. Basically it sets the Memphis 
*               connection information, but we have also a number of advanced
*               options that could be configured. Usually it is loaded from
*               ctagent.json configuration file. We have the following options 
*               supported:
*
*  EMBEDDED YES - default is YES  (it means if Replication Studio agent will be standalone or embedded in a DBEngine)
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
class FCREPL_API FCREPLConfig : public RCESConfig
{
public:
	FCREPLConfig(const char *localPath, const char *configFileName, bool *isShutdown, FCREPLLogAgent agentType);
	FCREPLConfig(const char *masterHost, const char *masterServerName, const char *masterSQLPort, const char *masterDatabase, const char *masterLogin, const char *masterPass);

/*
** Getters
*/

	// Local agent type: DBEngine, ReplStudio, ReplAgent, WebServer, etc
	FCREPLLogAgent GetAgentType() { return (FCREPLLogAgent)((pRCESConfig)this)->GetAgentType(); };

/*
	Inherited getters

    // Check if the provided configuration object matches the current one
    bool Matches(pFCConfig config);

    // Retrieve an advanced configuration by its KEY
    const char *GetParam(const char *key);

    // Retrieve an advanced configuration by its Param
    const char *GetParam(RCESParam param);

    // Return if connection will check for local c-tree files: LOCAL_CTREE_CHECK
	bool HasCtreeLocalCheck();

	// Return if File System scan is set to be executed in multi-threaded mode: SCAN_THREAD_COUNT
	bool HasMultiThreadScan();

	// Return if File System scan has an full mask advanced filter by the callback: ADV_FULL_MASK
	bool IsAdvFullMask();

    // Printf the configuration options
    static void PrintfConfigOptions();
 
    // Retrieve the user name and password
    void GetUser(char *authFileName, char **userName, char **userPass);

	// Local DBEngine identification.
	// It is linked to FCREPLDBEngine class
	int GetLocalDBEngineID();

	// Local agent identification.
	// It is linked to FCREPLAgent class
	int GetAgentID() { return _agentID; };

	// Return if current agent is embedded to a DBEngine
	bool IsEmbedded();

	// Local library handle: can be mtclient.dll or ctreedbs.dll handles
	void *GetLocalLibHandle();

    // Local logger
    pRCESLogger GetLoggerLocal();
 
    // Agent type
    RCESLogAgent GetAgentType();

	// Local agent name
	const char *GetAgentName();

	// Local server name
	const char *GetLocalServerName();

	// Local user name
	const char *GetLocalUserName();

	// Local user password
	const char *GetLocalUserPass();

	// Return if Web API Debug is enabled
	bool IsWebAPIDebug();

	// Memphis Volume identification.
	// It is linked to FCREPLVolume class
	int GetMemphisDBVolID();

	// Memphis directory
	const char *GetMemphisDBDir();

	// Local directory path
	const char *GetLocalPath();

    // Retrieve a path buffer populated with the local directory
    char *GetLocalPathBuffer();
 
    // Master conn pool
    FCPool<RCESMasterConnPooled> *GetMasterConnPool();

	// Return if local server is shuting down
	bool IsShutDown();

	// Return if trace is active
	bool IsTrace();

	// Return if Web trace is active
	bool IsWebTrace();

	// Return if its local agent is executing a FileSystem scan
	bool HasFSScan();

	// Memphis OpSystem identification.
	// It is linked to FCREPLOpSystem class
	int GetMasterOS();

	// Local OpSystem identification.
	// It is linked to FCREPLOpSystem class
	int GetAgentOS();

	// Return if local DBEngine is Memphis
	bool IsMasterAgent();

	// Return is automatic scan and track c-tree DBEngine changes: DBENGINE_CHECK
	bool IsCheckDBEngine();

	// Memphis database user login
	const char *GetMasterLogin();

	// Memphis database password
	const char *GetMasterPass();
 
    // Plan manager Hash
    FCHashTable<RCESReplPlanMngr> *GetReplPlanMngrHash();

    // Engine manager hash
    FCHashTable<RCESDBEngineMngr> *GetDBEngineMngrHash();

    // Fail over hash
    FCHashTable<RCESFailOverMngr> *GetFailOverMngrHash();

    // Repl agent data Hash
    FCHashTable<ReplicationAgentData> *GetReplAgentDataHash();

    // Repl monitor data hash
    FCHashTable<ReplicationMonitorData> *GetReplMonitorDataHash();

    // Repl dump data hash
    FCHashTable<ReplicationDumpData> *GetReplDumpDataHash();

    // Platform
    RCESPlatform GetPlatform();

    // Retrieve the Platform name
    const char *GetPlatformName();

    // Retrieve Accept Connection
    bool GetAcceptConn();

    // Retrieve Read only
    RCESReadOnly GetReadOnly();

    // Retrieve the JVM Lib Path
    const char *GetJVMLibPath();

    // Clean up global FailOver manager hash
    void CleanFailOverMngrHash();

    // Retrieve IS Connected flag
    bool IsConnected();
*/

/*
** Setters
*/

	// Local agent type: DBEngine, ReplStudio, ReplAgent, WebServer, etc
	void SetAgentType(FCREPLLogAgent agentType) { ((pRCESConfig)this)->SetAgentType((RCESLogAgent)agentType); };

	// Local agent name
	void SetAgentName(const char *agentName) { ((pRCESConfig)this)->SetAgentName(agentName); };

	// Local server name
	void SetLocalServerName(const char *localServerName) { ((pRCESConfig)this)->SetLocalServerName(localServerName); };

	// Local user name
	void SetLocalUserName(const char *localUserName) { ((pRCESConfig)this)->SetLocalUserName(localUserName); };

	// Local user password
	void SetLocalUserPass(const char *localUserPass) { ((pRCESConfig)this)->SetLocalUserPass(localUserPass); };

	// Memphis directory
	void SetMemphisDBDir(const char *dbDir) { ((pRCESConfig)this)->SetMemphisDBDir(dbDir); };

	// Local directory path
	void SetLocalPath(const char *localPath) { ((pRCESConfig)this)->SetLocalPath(localPath); };

	// Memphis database user login
	void SetMasterLogin(const char *masterLogin) { ((pRCESConfig)this)->SetMasterLogin(masterLogin); };

	// Memphis database password
	void SetMasterPass(const char *masterPass) { ((pRCESConfig)this)->SetMasterPass(masterPass); };

/*
	Inherited setters

	// Memphis OpSystem identification.
	// It is linked to FCREPLOpSystem class
	void SetMasterOS( int masterOS );

	// Local OpSystem identification.
	// It is linked to FCREPLOpSystem class
	void SetAgentOS( int agentOS );

	// Local DBEngine identification.
	// It is linked to FCREPLDBEngine class
	void SetLocalDBEngineID( int localDBEngineID );

	// Local agent identification.
	// It is linked to FCREPLAgent class
	void SetAgentID( int agentID );

	// Set if current agent is embedded to a DBEngine
	void SetIsEmbedded( bool isEmbedded );

	// Local library handle: can be mtclient.dll or ctreedbs.dll handles
	void SetLocalLibHandle( void *localLibHandle );

    // Set Agent type
    void SetAgentType(RCESLogAgent agentType);
 
    // Set Agent name
    void SetAgentName(const char *agentName);
 
    // Set Local server name
    void SetLocalServerName(const char *localServerName);
 
    // Set Local user name
    void SetLocalUserName(const char *localUserName);
 
    // Set local user password
    void SetLocalUserPass(const char *localUserPass);

	// Return if Web API Debug is enabled
	void SetWebAPIDebug( bool enable );

	// Memphis Volume identification.
	// It is linked to FCREPLVolume class
	void SetMemphisDBVolID( int volumeID );
	
    // Set Memphis DB directory
    void SetMemphisDBDir(const char *dbDir);
 
    // Set Local path
    void SetLocalPath(const char *localPath);
 
    // Set Master connection pool
    void SetMasterConnPool(FCPool<RCESMasterConnPooled> *masterConnPool);

	// Trace status
	void SetTrace( bool isTrace );

	// Web trace status
	void SetWebTrace( bool webTrace );

	// FilSystem scan
	void SetFSScan(bool fsScan);

    // Set Master login
    void SetMasterLogin(const char *masterLogin);

    // Set Master password
    void SetMasterPass(const char *masterPass);

    // Set DB engine manager hash
    void SetDBEngineMngrHash(FCHashTable<RCESDBEngineMngr> *dbEngineMngrHash);

    // Set Accept connection flag
    void SetAcceptConn(bool acceptConn);

    // Set Read only
    void SetReadOnly(RCESReadOnly readOnly);

    // Set JVM library path
    void SetJVMLibPath(const char *jvmLibPath);

    // Set Is connected path
    void SetIsConnected(bool isConnected);
*/
};


/*^****************************************************************************\
*
*   Class:      FCREPLConn
*               Replication Studio connection. It can keep both connections to
*               the local DBEngine and Memphis, keeping both data providers.
*
\******************************************************************************/
class FCREPL_API FCREPLConn : public RCESConn
{
public:
	FCREPLConn(pFCREPLConfig config);

/*
** Getters
*/

	// Return current configuration object
	pFCREPLConfig GetConfig() { return (pFCREPLConfig)((pRCESConn)this)->GetConfig(); };
};
typedef FCREPLConn *pFCREPLConn, **ppFCREPLConn;

#endif /* _FCREPLCONN_HPP_ */
