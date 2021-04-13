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

#ifndef _FC_RCESAUX_HPP_
#define _FC_RCESAUX_HPP_

#include "fc_rces.h"
#include "fcrcesplatform.h"
#include "fcaux.hpp"

#define _YES                    "YES"
#define _NO                     "NO"

#define PROGRESS_SLEEP 5 /* Time to refresh the progress information in seconds */
#define RCESDB_DICT_QUEUE "dbDictQueue"

 /*^****************************************************************************\
 *
 *   Defines
 *
 \******************************************************************************/

#define RCES_MAX_CONFIG_LEN 256
#define RCES_MAX_CONFIG_KEYS 32
#define RCES_MAX_ERRMSG_LEN FC_MAX_ERRMSG_LEN
#define RCES_DATETIME_STRLEN 30
#define RCES_LOCK_ATT_COUNT 30
#define RCES_SLEEP 1000
#define RCES_REFRESH 100 /* time to wait (in milliseconds) before refreshing the state */
#define RCES_DB_REFRESH 500 /* time to wait (in milliseconds) before getting DBEngine manager mutex */
#define RCES_TIMEOUT 60 /* timeout for the action event to be processed in seconds */
#define RCES_LOG_TIMEOUT 3 /* timeout for the message to be logged, we don't want to hang long inc ase Memphis server is not available */
#define RCES_TERMTIMEOUT 5 /* timeout for the consumer to terminate in seconds */
#define RCES_READTIMEOUT 5 /* read timeout in seconds */
#define RCES_FILE_WAIT 10 /* wait for access permission timeout in seconds */
#define RCES_WAIT_DBEGINE 4 /* future action for DBEngine check in seconds */
#define RCES_ACTION_TIMEOUT 10 /* default action timeout */
#define RCES_REFRESH_DBENGINE 10 /* frequency for DBEngine check in seconds */
#define RCES_WAIT_CONN_RETRY 2 /* frequency for connection retry in seconds */
#define RCES_COUNT_CONN_RETRY 5 /* number of connection retries */
#define RCES_WAIT_FS_TIMEOUT 120 /* timEout for FileSystem long actions in seconds */
#define RCES_CHECK_DBENGINE_SHORT_TIMEOUT 2 /* "short" timeout for the DBEngine connection check */
#define RCES_CHECK_DBENGINE_LONG_TIMEOUT 10 /* "long" timeout for the DBEngine connection check */
#define RCES_REPLPLAN_REFRESH_RATE 5 /* frequency to get the Replication Plan refreshed in seconds */
#define RCES_SCHEMASLEEP 5000
#define RCES_MAX_BUF 1024
#define RCES_MAX_PATH FC_MAX_PATH
#define RCES_MAX_VOLUME 64
#define RCES_MAX_SERVNAME 64
#define RCES_MAX_IDENTNAME 64
#define RCES_MAX_KEY 32
#define RCES_MAX_CONNSTR 256
#define RCES_MAX_REPL_FILES 1024
#define RCES_MAX_SUBPATH 512
#define RCES_BLOCK_SIZE 8192
#define RCES_BATCHSIZE 81920
#define RCES_MAX_QUEUE_COUNT 100
#define RCES_QUEUEMAX_RETRIES 100
#define RCES_CTREE_CONSUMER_THRD_COUNT 4
#define RCES_BASIC_CONSUMER_THRD_COUNT 4
#define RCES_DFLT_EXTENSION ".tmp"
#define RCES_CACHE_SIZE 100
#define RCES_LOGPOS_LEN 64
#define RCES_MAX_ACCESS_RETRY 50
#define RCES_ACCESS_RETRY_SLEEP 100
#define RCES_REPLNODEID_LEN 32
#define _TRACE "TRACE"

#define RCES_CFG_FILE_NAME "ctsrvr.cfg"

#define RCES_DUMP_SCRIPT_FILE_NAME "dyndump.txt"
#define RCES_DUMP_FILE_NAME "dyndump.fcd"
#define RCES_REPL_DUMP_DIR "./replRunDir"
#define RCES_TEMP_DIR "./temp"
#define RCES_DUMP_DIR "dump"
#define RCES_AGENT_DIR "agent"
#define RCES_ACTIONEXEC_DIR "ctactionexec"
#define RCES_MEMPHIS_REPO_DIR "repo"

#define RCES_DUNDMP_PROG_REFRESH 5        /* Refresh frequence for the dynamic dump progress in seconds */
#define RCES_DYNDMP_REBUILD_FACTOR 0.35
#define RCES_DYNDMP_NO_RBLD_FACTOR 0.45
#define RCES_RESTORE_REBUILD_FACTOR 0.3
#define RCES_RESTORE_NO_RBLD_FACTOR 0.45
#define RCES_REPLACE_REBUILD_FACTOR 0.35
#define RCES_REPLACE_NO_RBLD_FACTOR 0.1

#define RCES_SCAN_CREATE_PROG 1
#define RCES_SCAN_EVAL_PROG 11
#define RCES_SCAN_FSCAN_PROG 91
#define RCES_SCAN_FSCAN_PCT 80
#define RCES_SCAN_UPLOAD_PROG 94
#define RCES_SCAN_LOAD_PROG 99
#define RCES_SCAN_LOAD_PCT 5

#define RCES_DFTL_REPL_PLAN_NAME "ReplPlan"
#define RCES_DFTL_PUB_NAME "Publication"
#define RCES_DFTL_SUBS_NAME "Subscription"

#ifndef ctPortANDROID
#define RCES_MAST_AUTH_FILE "./agent/masterAuthFile.set"
#define RCES_AUTH_USERID "USERID"
#define RCES_AUTH_PASSWD "PASSWD"
#define RCES_DFLT_MASTER_SERVER_NAME "MEMPHIS"
#define RCES_SCHEMA_SCRIPT_NAME "./agent/FcFatDB_schema.sql"
#define RCES_METADATA_SCRIPT_NAME "./agent/FcFatDB_metadata.sql"
#else
#define RCES_MAST_AUTH_FILE "masterAuthFile.set"
#define RCES_AUTH_USERID "USERID"
#define RCES_AUTH_PASSWD "PASSWD"
#define RCES_DFLT_MASTER_SERVER_NAME "MEMPHIS"
#define RCES_SCHEMA_SCRIPT_NAME "FcFatDB_schema.sql"
#define RCES_METADATA_SCRIPT_NAME "FcFatDB_metadata.sql"
#endif

#define RCES_DBENGINE_CFG_PATH "config/"
#define RCES_DBENGINE_CFG_FILENAME "ctsrvr.cfg"
#define RCES_REPLAGENT_CFG_FILENAME "ctreplagent.cfg"
#define RCES_LIC_EXT "lic"
#define RCES_CTREELOGFILE "CTSTATUS.FCS"
#ifndef ctPortANDROID
#define RCES_AGENT_AUTH_FILE "./agent/agentAuthFile.set"
#else
#define RCES_AGENT_AUTH_FILE "agentAuthFile.set"
#endif
#define RCES_REPLAGENT_DBNAME "ReplicationAgent" /* This database name will be ignored from the database list in Memphis */

#define RCES_ROOT_LOCAL "***LOCAL***"
#define RCES_ROOT_MCP "***MCP***"

 /* MAC adapter type supported */
#define RCES_ETHERNET "Ethernet"

 /* IP address type */
#define RCES_IPV4 "ipV4"
#define RCES_IPV6 "ipV6"

 /* Supported synchronous replication mode */
#define RCES_SYNC_MODE "cc"

#define RCES_TRACE 1			/* Trace some extra information into the log */

#define RCES_DEFAULT_WARNINGTHRESHOLD 30    /* After 30 seconds behind the Replication Plan is in WARNING state by default */
#define RCES_DEFAULT_ERRORTHRESHOLD 300     /* After 300 seconds behind the Replication Plan is in ERROR state by default */
#define RCES_DEFAULT_MONITOR_RATE 5         /* Default Replication Plan monitor rate in seconds */
#define RCES_DEFAULT_ANALYZERTHREADSCOUNT 1 /* Default replication parallelism analyzer threads count */
#define RCES_DEFAULT_APPLYTHREADSCOUNT    8 /* Default replication parallelism apply threads count */

#define RCES_DEFAULT_HEARTBEAT_FREQUENCY  4  /* Default availability group heartbeat frequency */
#define RCES_DEFAULT_HEARTBEAT_TIMEOUT    10 /* Default availability group heartbeat timeout */

/*#define RCES_DEBUG 1*/ 		/* Debug FAT DB application */
#ifdef RCES_DEBUG
#define ctCHECK_MAX_PATH		/* Debug the size of a file path name */
#endif

#include "fcrcesmetadata.hpp"
#include "fchashtable.hpp"

typedef enum 
{
	RCES_WAIT           = 0, /* Wait for the consumer initilization  */
	RCES_SETTRANSFER    = 1, /* Create/Set transfer object state  */
	RCES_RUN            = 2, /* RUN state  */
	RCES_STOP           = 3, /* STOP state */
	RCES_STOPED         = 4, /* STOPED state */
	RCES_PROCESS        = 5, /* Processing state */
	RCES_PROCESSED      = 6, /* Processed state */
	RCES_ERROR          = 7  /* Thread error */
} RCESThrdState, *pRCESThrdState;

typedef enum 
{
	RCES_FILESYSTEMONLY = 0, /* Only scan filesystem */
	RCES_DBENGINEONLY   = 1, /* Only scan DBEngine */
	RCES_FSDBENGINE     = 2, /* Scan both filesystem and dbengine  */
	RCES_DIRCOUNTONLY   = 3, /* Only count the directory to be checked  */
	RCES_REPLAGENTONLY  = 4, /* Scan replication agent only  */
} RCESScanMode;

typedef enum 
{
	INVALID                 = -1,

	/* Config parameters */
	LOG_FILE                = 0,
	LOCAL_CTREE_CHECK       = 1,
	CTREE_CHECK_MASK        = 2,
	MEMPHIS_TYPE            = 3,
	MEMPHIS_SERVER_NAME     = 4,
	MEMPHIS_SQL_PORT        = 5,
	MEMPHIS_HOST            = 6,
	MEMPHIS_DATABASE        = 7,
	MEMPHIS_MAX_CONN        = 8,
	VERBOSE_SCAN_COUNT      = 9,
	VERBOSE_SHOW_NAME       = 10,
	QUEUE_THREAD_COUNT      = 11,
	SCAN_THREAD_COUNT       = 12,
	LOAD_THREAD_COUNT       = 13,
	ADV_FULL_MASK           = 14,
	DBENGINE_CHECK          = 15,
	LOCAL_CONN_POOL_SIZE    = 16,
	EMBEDDED                = 17,
	STANDALONE_AGENT        = 18,
	LOCAL_SERVERNAME        = 19,
	TRACE                   = 20,
	WEB_TRACE               = 21,
	DBENGINE_CONN_BY_IP     = 22,
	ACCEPT_CONN             = 23,
	READ_ONLY               = 24,
	JVM_LIB                 = 25,
	MANAGED                 = 26,
	CFG_FILE_LIST           = 27,

	/* Memphis server specific keywords */
	INACTIVE_TIMEOUT        = 50,
	MEMPHIS_CONN_POOL_SIZE  = 51,
	CHECKSTATUS_WAIT        = 52,
	DEBUG_WEB_API           = 53,
	ARCHIVE_ACTION          = 54,
	ARCHIVE_LOG             = 55,
	CHECK_DBENGINE_THRD_COUNT = 56,
	CHECK_REPLPLAN_THRD_COUNT = 57,
	ARCHIVE_REPLSTAT        = 58,

	/* Action parameters */
	FILE_SIZE               = 100,
	FILE_UPDATETIME         = 101,
	FILE_CREATETIME         = 102,

	SOURCE_FILEID           = 200,
	ISFILE                  = 201,
	SOURCE_VOLUME           = 202,
	SOURCE_FILEPATH         = 203,
	SOURCE_FILENAME         = 204,
	TARGET_VOLUME           = 205,
	TARGET_FILEPATH         = 206,
	TARGET_FILENAME         = 207,
	NOTIF_PATH              = 208,
	ISDB                    = 209,

	WORKING_VOLUME          = 300,
	WORKING_VOLUME_NAME     = 301,
	WORKING_DIR             = 302,
	LOCAL_VOLUME            = 303,
	LOCAL_VOLUME_NAME       = 304,
	LOCAL_DIR               = 305,
	CAN_REMOVE              = 306,

	VOLUME_ID               = 400,
	ROOT_PATH               = 401,
	SCAN_MASK               = 402,
	TEMP_FS_NAME            = 403,
	CTREE_ONLY              = 404,
	FILE_COUNT              = 405,
	SCAN_RECURSIVE          = 406,
	SCAN_PHYSICALCHECK      = 407,

	REPL_REVERSE            = 500,
	REFRESH_RATE            = 501,
	LOG_POS                 = 502,
	SOURCE_LOG_POS          = 503,
	TARGET_LOG_POS          = 504,
	REPLPLAN_NAME           = 505,
	REPLPLAN_DESC           = 506,
	PUB_ID                  = 507,
	PUB_NAME                = 508,
	PUB_DESC                = 509,
	PUB_DATABASE            = 510,
	SUBS_NAME               = 511,
	SUBS_DESC               = 512,
	SUBS_DATABASE           = 513,
	SIMPLE_MODE             = 514,
	REPL_FORCEREPLACE       = 515,
	REPL_FILEIDLIST         = 516,
	RESYNC_ADDFILES         = 517,

	AGENT_ID                = 600,
	ACTION_ID               = 601,
	CONSUMER_TYPE           = 602,
	CONSUMER_LIB            = 603,
	CONSUMER_THRD_COUNT     = 604
} RCESParam;

typedef enum 
{
	RCES_DBTHRD_INIT            = 0,  /* Thread init state                                 */
	RCES_DBTHRD_WAIT            = 1,  /* Thread running state                              */
	RCES_DBTHRD_STOP            = 2,  /* Thread stopping state                             */
	RCES_DBTHRD_TERM            = 3,  /* Thread terminated state                           */
	RCES_DBTHRD_GETINFO         = 4,  /* Thread GetInfo state                              */
	RCES_DBTHRD_BLOCK           = 5,  /* Thread Block state                                */
	RCES_DBTHRD_UNBLOCK         = 6,  /* Thread Unblock state                              */
	RCES_DBTHRD_FTRANSFER       = 7,  /* Thread File transfer state                        */
	RCES_DBTHRD_FDUMP           = 8,  /* Dump all files form the publication to the target */
	RCES_DBTHRD_FREPLACE        = 9,  /* Dump all files form the publication to the target */
	RCES_DBTHRD_FBLOCK          = 10, /* File block                                        */
	RCES_DBTHRD_FUNBLOCK        = 11, /* File unblock                                      */
	RCES_DBTHRD_CHKAGENT        = 12, /* Check agent                                       */
	RCES_DBTHRD_READONLY        = 13, /* Update readonly status                            */
	RCES_DBTHRD_UPDNODEID       = 14  /* Update replication node ID                        */
} RCESDBEngineThrdState;

/* Replication Direction table */
typedef enum
{
	RCES_REPL_NONE = 0, /* Still there is not Subscription assigned, so no direction   */
	RCES_REPL_NORMAL = 1, /* All the replications are from Source DBEngine to the Target */
	RCES_REPL_REVERSE = 2, /* All the replications are from Target DBEngine to the Source */
	RCES_REPL_BOTH = 3  /* There are replication from Source and from Target DBEngines */
} RCESReplDirection;

/*^****************************************************************************\
*
*   RCES replication direction
*
\******************************************************************************/
typedef enum
{
	RCES_REPLPLAN_ORI = 0, /* Original replication direction */
	RCES_REPLPLAN_REV = 1  /* Reverse replication direction  */
} RCESReplicationDirection;


/* Forward class and type definitions */
class RCESDBEngineMngr;
class RCESDBEngineRfrsr;
class RCESReplPlanMngr;
class ReplicationAgentData;
class ReplicationMonitorData;
class ReplicationDumpData;
class RCESFailOverMngr;
class RCESReplAgentMngr;
typedef RCESDBEngineMngr *pRCESDBEngineMngr, **ppRCESDBEngineMngr;
typedef RCESDBEngineRfrsr *pRCESDBEngineRfrsr, **ppRCESDBEngineRfrsr;
typedef RCESReplPlanMngr *pRCESReplPlanMngr, **ppRCESReplPlanMngr;
typedef ReplicationAgentData *pReplicationAgentData, **ppReplicationAgentData;
typedef ReplicationMonitorData *pReplicationMonitorData, **ppReplicationMonitorData;
typedef ReplicationDumpData *pReplicationDumpData, **ppReplicationDumpData;
typedef RCESFailOverMngr *pRCESFailOverMngr, **ppRCESFailOverMngr;
typedef RCESReplAgentMngr *pRCESReplAgentMngr, **ppRCESReplAgentMngr;

typedef struct DBEngineThrdData {
	pRCESDBEngineMngr dbEngineMngr;
	void *fileTransfer;
	pRCESReplPlan replPlan;
	pRCESSubscription subscription;
	ppRCESReplFile replFileList;
	int fileCount;
	char tempPath[RCES_MAX_PATH+1];
	char logPos[RCES_LOGPOS_LEN+1];
	char fileName[RCES_MAX_PATH+1];
	void *dpHandle;
	void *dbEngineThrdMutex;
	char errorMsg[RCES_MAX_ERRMSG_LEN+1];
	int errorCode;
	RCESDBEngineThrdState state;
	int progress;
	bool forceReplace;
	char agentID[RCES_MAX_IDENTNAME + 1];
	pReplicationDumpData dumpData;
	int connTimeout;
	bool isSourceOSCaseSensitive;
	bool newReadOnlyFlag;
	int operation;
	bool isParallel;
} DBEngineThrdData, *pDBEngineThrdData, **ppDBEngineThrdData;

typedef enum 
{
	RCES_RARUN      = 0, /* RUN state, agent will start running  */
	RCES_RASTOP     = 1, /* STOP state, agent will start running */
} RCESAgentState;

typedef struct AgentThrdData {
	void *replAgentData;
	void *replConnState;
	RCESAgentState state;
	char errorMsg[RCES_MAX_ERRMSG_LEN+1];
	int errorCode;
} AgentThrdData, *pAgentThrdData, **ppAgentThrdData;

typedef struct MonitorThrdData {
	int replPlanID;
	RCESReplicationDirection direction;
	void *replAgentData;
	int refreshRate;
	RCESThrdState state;
	pRCESConfig config;
	char errorMsg[RCES_MAX_ERRMSG_LEN+1];
	int errorCode;
} MonitorThrdData, *pMonitorThrdData, **ppMonitorThrdData;

typedef struct DictCBThrdData {
	pRCESDBEngineRfrsr dbRefresher;
	char errorMsg[RCES_MAX_ERRMSG_LEN + 1];
	int errorCode;
	RCESThrdState state;
	void *mutex;
} DictCBThrdData, *pDictCBThrdData, **ppDictCBThrdData;

typedef void(*cleanCBPtr)(pRCESReplPlanMngr, RCESReplicationDirection);
typedef void(*actionCBPtr)(FCPool<RCESMasterConnPooled> *, int, int, int, char *);

typedef struct ResyncThrdData {
	char resyncName[RCES_MAX_IDENTNAME + 1];
	int actionID;
	FCPool<RCESMasterConnPooled> *masterConnPool;
	void *replAgentData;
	pRCESReplPlanMngr replPlanMngr;
	cleanCBPtr cleanCB;
	actionCBPtr actionCB;
	char replPlanName[RCES_MAX_IDENTNAME+1];
	RCESReplicationDirection direction;
	RCESThrdState state;
	char errorMsg[RCES_MAX_ERRMSG_LEN + 1];
	int errorCode;
} ResyncThrdData, *pResyncThrdData, **ppResyncThrdData;

typedef struct ReplicationResyncData {
	void *replResyncDatatList[2];
	pResyncThrdData resyncThrdData[2];
	void *resyncThrdHandle[2];
	void *hResyncMutex;
} ReplicationResyncData, *pReplicationResyncData, **ppReplicationResyncData;

typedef struct RCESThrdData {
	RCESThrdState state;
	FCPool<RCESMasterConnPooled> *masterProvConnPool;
} RCESThrdData, *pRCESThrdData, **ppRCESThrdData;

typedef struct ReplExcepThrdData {
	RCESThrdState state;
	FCPool<RCESMasterConnPooled> *masterProvConnPool;
	FCList<RCESReplExcep> *replExcepList;
	pRCESReplPlanMngr replPlanMngr;
} ReplExcepThrdData, *pReplExcepThrdData, **ppReplExcepThrdData;

typedef struct ReplMsgThrdData {
	RCESThrdState state;
	FCPool<RCESMasterConnPooled> *masterProvConnPool;
	FCList<RCESReplMsg> *replMsgList;
} ReplMsgThrdData, *pReplMsgThrdData, **ppReplMsgThrdData;

/*^****************************************************************************\
*
*   RCES replication state
*
\******************************************************************************/
typedef enum
{
	RCES_STAT_TARGET = 0,
	RCES_STAT_SOURCE = 1,
	RCES_STAT_PAUSED = 2,
	RCES_STAT_SELF = 3,
	RCES_STAT_EXITED = 4,
	RCES_STAT_ERROR = 5
} RCESReplicationState;

/*^****************************************************************************\
*
*   Log/Trace severity level
*
\******************************************************************************/
typedef enum
{
	RCES_CRITICAL = 0,    /* Most critical severity level */
	RCES_SEV1 = 1,        /* Severity 1 - critical        */
	RCES_SEV2 = 2,        /* Severity 2 - important       */
	RCES_SEV3 = 3,        /* Severity 3 - normal          */
	RCES_INFO = 4,        /* Long information             */
	RCES_TRACE_LEVEL = 5  /* Trace information            */
} RCESSeverity;

/*^****************************************************************************\
*
*   Log/Trace detail level
*
\******************************************************************************/
typedef enum
{
	RCES_DETAIL_ERROR = 1,    /* Only errors          */
	RCES_DETAIL_INFO = 2,     /* + basic information  */
	RCES_DETAIL_TRACE1 = 3,   /* + trace basic level  */
	RCES_DETAIL_TRACE2 = 4    /* + trace detail level */
} RCESDetailLevel;

/*^****************************************************************************\
*
*   RCES Advanced filter value
*
\******************************************************************************/
typedef enum
{
	RCES_CHECK_MASK		= -1,	/* Check the mask as it is done by default */
	RCES_NOT_PASSED		= 0,	/* File not passed the filter              */
	RCES_PASSED		= 1	/* File passed the filter                  */
} RCESADVFILTER;

void invSep( char *str );
void getFirstSep( char *str, char **prevStr, char **postStr );
void getLastSep( char *str, char **prevStr, char **postStr );
void splitByLastChar( char *str, char sep, char **prevStr, char **postStr );
const char **getMaskList( const char *masks, int *maskCount );
bool FileNameMatches( const char *fileName, const char **maskList, int maskCount );
RCESActionType GetActionCd( int action );
void BuildFullFileName( const char *volume, const char *path, const char *fileName, char *fullFilePath, char *fullFileName );
void _splitFullFileName(char *filePath, bool isCaseSensitive, ppRCESVolume volumeList, int volumeCount, const char **volumeName, int *volumeID, char **path, char **name);
void CheckDir( const char *path );
char *AdjustRelPath( const char *fullFilName, const char *workingDir );
char *getDatetimeStr( RCESDateTime datetime );
void getCurrDatetimeStr( char *dateTimeStr );
char *getCurrDatetimeFileName();
void buildFullPath( const char *rootPath, const char *relativePath, char *absolutePath );
void buildFullPath( const char *relativePath, char *absolutePath );
bool isRelativePath(const char *path);
void copy( const char *sourceFileName, const char *targetFileName, bool isRetry );
void removeFileDir( const char *fileDirName );
void getVolumePath( char *fullPath, char **volumeName, char **path );
int moveFile( const char *sourceFileName, const char *targetFileName );
void validatePath( const char *volumeName, const char *path, char *checkedPath );
bool checkName( const char *name );
const char *_getFileDescription(RCESFileType type);
void *getLocalLibHandle();

#endif /* _FC_RCESAUX_HPP_ */