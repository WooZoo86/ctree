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

#ifndef _FC_RCESMETADATA_HPP_
#define _FC_RCESMETADATA_HPP_

#include "fc_rces.h"

/*
 * META DATA information
 *
 * It must be on sync with the meta data tables in the database
 */

/* EntityType table - if changing this enum type, change also the table records and the FCREPLEntityType type */
typedef enum 
{
	RCES_NONE             = -1,
	RCES_SITE             = 0,
	RCES_HARDWARE         = 1,
	RCES_OPSYSTEM         = 2,
	RCES_VOLUME           = 3,
	RCES_FILE             = 4,
	RCES_DBENGINE_ENT     = 5,
	RCES_SUBSCRIPTION_ENT = 6,
	RCES_REPLPLAN_ENT     = 7,
} RCESEntityType;

/* Consumer table - if changing this enum type or the library names, change also the table records and the FCREPLConsumerType type*/
typedef enum 
{
	RCES_DEFAULT         = -2, /* Default consumer   */
	RCES_UNDEF           = -1, /* Undefined consumer */
	RCES_BASIC           = 0,  /* Basic action consumer                 - Action Type from 0 to 99    */
	RCES_FILESYSTEM      = 1,  /* General Filesystem action consumer    - Action Type from 100 to 100 */
	RCES_REPL            = 2,  /* General replication plan consumer     - Action Type from 200 to 299 */
	RCES_REPL_CTREE      = 3,  /* Ctree replication action consumer     - Action Type from 300 to 399 */
#ifdef NCTREE_FILE_SUPPORT
	RCES_REPL_NCTREE     = 3,  /* Non-ctree replication action consumer - Action Type from 400 to 499 */
#endif
} RCESConsumerType;

#define CONSUMER_BASIC_NAME       "BASIC"
#define CONSUMER_FILESYSTEM_NAME  "FILE_SYSTEM"
#define CONSUMER_REPL_NAME        "REPLICATION"
#define CONSUMER_REPL_CTREE_NAME  "REPL_CTREE"
#define CONSUMER_REPL_NCTREE_NAME "REPL_NON_CTREE"

#define CONSUMER_BASIC_LIB       "ctactionexecbasic"
#define CONSUMER_FILESYSTEM_LIB  "ctactionexecfs"
#define CONSUMER_REPL_LIB        "ctactionexecrepl"
#define CONSUMER_REPL_CTREE_LIB  "ctactionexecreplctree"
#define CONSUMER_REPL_NCTREE_LIB "ctactionexecreplnctree"

/* ActionType table - if changing this enum type, change also the table records and the FCREPLActionType type */
typedef enum 
{
	/* Basic actions */
	RCES_BASIC_LOAD                  = 0,     /* executor load                                          */
	RCES_BASIC_UNLOAD                = 1,     /* executor unload                                        */

	/* FileSystem actions */
	RCES_FS_ADD                      = 100,   /* filesystem add                                         */
	RCES_FS_DELETE                   = 101,   /* filesystem remove                                      */
	RCES_FS_CHANGE                   = 102,   /* filesystem  change                                     */
	RCES_FS_SCAN                     = 103,   /* filesystem scan                                        */
	RCES_FS_LOAD                     = 104,   /* temporary filesystem load                              */
	RCES_FS_CHECK_DBENGINE           = 105,   /* check DBEngine changes                                 */
	RCES_FS_SCAN_FOLDER              = 106,   /* filesystem scan folder                                 */
	RCES_FS_SCAN_REPLAGENT           = 107,   /* scan for Replication Agent                             */
	RCES_FS_IMPORT_REPLAGENT         = 108,   /* import Replication Agent                               */

	/* Basic Replication actions */
	RCES_REPL_DEPLOY                 = 200, /* deploy replication plan                                  */
	RCES_REPL_START                  = 201, /* start replication plan                                   */
	RCES_REPL_STOP                   = 202, /* stop replication plan                                    */
	RCES_REPL_REG                    = 203, /* register consumer for replication plan                   */
	RCES_REPL_REG_SOURCE             = 204, /* register consumer in source OS for non-ctree replication */
	RCES_REPL_UNREG                  = 205, /* unregister consumer for replication plan                 */
	RCES_REPL_HEARTBEAT              = 206, /* replication agent heartbeat basic                        */
	RCES_REPL_START_MONITOR          = 207, /* start replication monitoring                             */
	RCES_REPL_STOP_MONITOR           = 208, /* stop replication monitoring                              */
	RCES_REPL_START_EXCEPLOG         = 209, /* start replication exception log                          */
	RCES_REPL_STOP_EXCEPLOG          = 210, /* stop replication exception log                           */
	RCES_REPL_START_FUNCTIME         = 211, /* start replication function timing collection             */
	RCES_REPL_STOP_FUNCTIME          = 212, /* stop replication function timing collection              */
	RCES_REPL_RESET_FUNCTIME         = 213, /* reset replication function timing collection             */
	RCES_REPL_GET_FUNCTIME           = 214, /* get replication function times                           */
	RCES_REPL_PAUSE                  = 215, /* pause replication                                        */
	RCES_REPL_RESUME                 = 216, /* resume replication                                       */
	RCES_REPL_SETTRACE               = 217, /* set trace                                                */
	RCES_REPL_CHECKFAILOVER          = 218, /* check failover manager                                   */

	/* Ctree actions */
	RCES_CTREE_START                 = 300, /* ctree replication start                                  */
	RCES_CTREE_STOP                  = 301, /* ctree replication stop                                   */
	RCES_CTREE_DUMPFILES             = 302, /* ctree dynamic dump files                                 */
	RCES_CTREE_CANCEL                = 303, /* cancel replication plan deployment                       */
	RCES_CTREE_START_MONITOR         = 304, /* start replication monitoring                             */
	RCES_CTREE_STOP_MONITOR          = 305, /* stop replication monitoring                              */
	RCES_CTREE_START_EXCEPLOG        = 306, /* start replication exception log                          */
	RCES_CTREE_STOP_EXCEPLOG         = 307, /* stop replication exception log                           */
	RCES_CTREE_START_FUNCTIME        = 308, /* start replication function timing collection             */
	RCES_CTREE_STOP_FUNCTIME         = 309, /* stop replication function timing collection              */
	RCES_CTREE_RESET_FUNCTIME        = 310, /* reset replication function timing collection             */
	RCES_CTREE_GET_FUNCTIME          = 311, /* get replication function times                           */
	RCES_CTREE_PAUSE                 = 312, /* pause replication                                        */
	RCES_CTREE_RESUME                = 313, /* resume replication                                       */
	RCES_CTREE_RESYNC                = 314, /* resync files                                             */
	RCES_CTREE_HEARTBEAT             = 315, /* replication agent heartbeat                              */

	/* Non-ctree actions */
	RCES_ADD                         = 400, /* File add                                                 */
	RCES_DELETE                      = 401, /* File remove                                              */
	RCES_CHANGE                      = 402, /* File change                                              */
	RCES_REPL_HEARTBEAT_TARGET       = 403, /* replication agent heartbeat target                       */

	RCES_UNKNOWN                     = 99999 /* Unknown action */
} RCESActionType;

/* EngineStatus table - if changing this enum type, change also the table records and the FCREPLEngineStatus type */
typedef enum 
{
	RCES_NOTSUP     = -1, /* Engine invalid status                */
	RCES_INACTIVE   = 0,  /* Engine inactive                      */
	RCES_ACTIVE     = 1,  /* Engine active                        */
	RCES_STOPPING   = 2,  /* Engine stopping                      */
	RCES_STARTING   = 3,  /* Engine starting                      */
	RCES_CHECKING   = 4,  /* Engine checking                      */
	RCES_DBWARNING  = 5,  /* Engine active with warning           */
	RCES_DBERROR    = 6,  /* Engine unavailable                   */
	RCES_SWITCHING  = 7,  /* Switching Avail Group to new primary */
	RCES_UNMANAGED  = 8   /* Engine unmanaged                     */
} RCESEngineStatus, RCESAgentStatus;

/* FileType table - if changing this enum type, change also the table records and the FCREPLFileType type */
typedef enum
{
    RCES_INVALID          =-1,
    RCES_CTREE            = 0,    /* File is c-tree                                                               */
    RCES_CTREE_CORRUPT    = 1,    /* File is c-tree but it is corrupted                                           */
    RCES_CTREP_QUALIF     = 2,    /* File is c-tree and qualifies to replication                                  */
	RCES_CTREP_QUALIF_RTG = 3,    /* File is c-tree RTG and qualifies to replication                              */
    RCES_CTREP_NO_IFIL    = 4,    /* File is c-tree but doesn't have IFIL, so doesn't qualify for replication     */
    RCES_CTREP_NO_TRNLOG  = 5,    /* File is c-tree but is not TRNLOG, so doesn't qualify for replication         */
    RCES_CTREP_NO_IDX     = 6,    /* File is c-tree but doesn't have an index that qualifies for replication      */
    RCES_CTREP_NO_XHEADER = 7,    /* File doesn't support extended header - probably created before V7            */
    RCES_PENDING          = 8,    /* File is pending on the schema checked - problably due to permission issue    */
    RCES_CTREEIDX         = 9,    /* File is a c-tree index                                                       */
    RCES_CTREESUPER       = 10,   /* File is a c-tree super file                                                  */
    RCES_DIR              = 11,   /* Item is a directory                                                          */
    RCES_NCTREE           = 12,   /* This is not a c-tree file                                                    */
    RCES_CTREP_FTI        = 13,   /* File is c-tree but has a Full Text Index, so doesn't qualify for replication */
	RCES_CTERROR          = 14    /* File seems to be a c-tree file, but there was an error trying to open it     */
} RCESFileType;

/* ReplicationStatus table - if changing this enum type, change also the table records and the FCREPLReplStatus type */
typedef enum 
{
	RCES_REPL_INACTIVE  = 0,
	RCES_REPL_ACTIVE    = 1,
	RCES_REPL_STOPPING  = 2,
	RCES_REPL_STARTING  = 3,
	RCES_REPL_DEPLOYING = 4,
	RCES_REPL_PAUSED    = 5,
	RCES_REPL_RESYNCING = 6,
	RCES_REPL_ARCHIVED  = 7
} RCESReplStatus;

/* LogType table - if changing this enum type, change also the table records and the FCREPLLogType type */
typedef enum
{
	RCES_LOGTYPE_INVALID = -1,
	RCES_LOGTYPE_INFO = 0,
	RCES_LOGTYPE_WARNING = 1,
	RCES_LOGTYPE_ERROR = 2,
	RCES_LOGTYPE_EXCEPTION = 3,
	RCES_LOGTYPE_TRACE = 4
} RCESLogType;

/* LogAgentType table - if changing this enum type, change also the table records and the FCREPLLogAgent type */
typedef enum
{
	RCES_LOGAGENT_INVALID = -1,
	RCES_LOGAGENT_INTERNAL = 0,
	RCES_LOGAGENT_DBENGINE = 1,
	RCES_LOGAGENT_REPLSTUDIO = 2,
	RCES_LOGAGENT_REPLAGENT = 3,
	RCES_LOGAGENT_WEBSERVER = 4
} RCESLogAgent;

/* Platform table - if changing this enum type, change also the table records and the FCREPLPlatform type */
typedef enum
{
	RCES_PLATFORM_NONE = -1,
	RCES_PLATFORM_WINDOWS64 = 0,
	RCES_PLATFORM_LINUX64 = 1,
	RCES_PLATFORM_RASPBIAN32 = 2,
	RCES_PLATFORM_MACOSX = 3
} RCESPlatform;

#define PLATFORM_WINDOWS64_NAME       "winX64"
#define PLATFORM_LINUX64_NAME         "LinuxX64"
#define PLATFORM_RASPBIAN32_NAME      "Raspbian32"
#define PLATFORM_MACOSX_NAME          "MacOSX"

/* Readonly status */
typedef enum
{
	RCES_READONLY_NOTSUP = -1,
	RCES_READONLY_FALSE = 0,
	RCES_READONLY_TRUE = 1,
	RCES_READONLY_NEVER = 2
} RCESReadOnly;

#define READONLY_FALSE      "false"
#define READONLY_TRUE       "true"
#define READONLY_NEVER      "never"


/* MQTTFormat table - if changing this enum type, change also the table records and the FCMQTTFormat type */

#define MQTTFORMAT_JSON_NAME       "JSON"

typedef enum
{
	RCES_MQTTFORMAT_UNDEF = -1,
	RCES_MQTTFORMAT_JSON = 0
} RCESMqttMsgFormat;


/* MQTTRetentionUnit table - if changing this enum type, change also the table records and the FCMQTTRetentionUnit type */

#define MQTTUNIT_MIN_NAME       "minute"
#define MQTTUNIT_HOUR_NAME      "hour"
#define MQTTUNIT_DAY_NAME       "day"
#define MQTTUNIT_MONTH_NAME     "month"
#define MQTTUNIT_YEAR_NAME      "year"

typedef enum
{
	RCES_MQTTUNIT_UNDEF = -1,
	RCES_MQTTUNIT_MIN = 0,
	RCES_MQTTUNIT_HOUR = 1,
	RCES_MQTTUNIT_DAY = 2,
	RCES_MQTTUNIT_MONTH = 3,
	RCES_MQTTUNIT_YEAR = 4
} RCESMqttRetentionUnit;


/* FailOver parameters */
#define FAILOVER_CONN_MODE "connectionMode"
#define FAILOVER_ACCEPT_LATENCY "acceptableLatency"
#define FAILOVER_ACCEPT_LATENCY_DFLT 5

#define FAILOVER_CONN_MODE_READONLY "read"
#define FAILOVER_CONN_MODE_WRITE "write"

typedef enum
{
	RCES_FAILOVER_UNDEF = -1,
	RCES_FAILOVER_READONLY = 0,
	RCES_FAILOVER_WRITE = 1
} RCESFailoverConnMode;

typedef enum
{
	RCES_PUBLICATION_MODE_UNDEF = -1,
	RCES_PUBLICATION_MODE_FILE = 0,
	RCES_PUBLICATION_MODE_FOLDER = 1,
	RCES_PUBLICATION_MODE_DATABASE = 2
} RCESPublicationMode;

#define PUBLICATION_MODE_UNDEF    "undefined"
#define PUBLICATION_MODE_FILE     "file"
#define PUBLICATION_MODE_FOLDER   "folder"
#define PUBLICATION_MODE_DATABASE "database"

typedef enum
{
	RCES_PUBLICATION_RULE_TYPE_UNDEF = -1,
	RCES_PUBLICATION_RULE_TYPE_INCLUDE = 0,
	RCES_PUBLICATION_RULE_TYPE_EXCLUDE = 1
} RCESPublicationRuleType;

typedef enum
{
	RCES_RULE_TYPE_UNDEF = -1,
	RCES_RULE_TYPE_NAME = 0,
	RCES_RULE_TYPE_WILDCARD = 1,
	RCES_RULE_TYPE_REGEX = 2
} RCESRuleType;

#endif /* _FC_RCESMETADATA_HPP_ */