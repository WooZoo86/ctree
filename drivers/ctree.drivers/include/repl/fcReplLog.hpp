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

#ifndef _FCREPLLOG_HPP_
#define _FCREPLLOG_HPP_

#include "fcReplCommon.hpp"
#include "fcrceslog.hpp"
#include "fcrcesconn.hpp"

/* Forward class declaration */
class FCREPLConn;
class FCREPLLog;
typedef FCREPLConn *pFCREPLConn, **ppFCREPLConn;
typedef FCREPLLog *pFCREPLLog, **ppFCREPLLog;


/* LogAgentType table */
typedef enum
{
	FCREPL_LOGAGENT_INVALID = -1,
	FCREPL_LOGAGENT_INTERNAL = 0,
	FCREPL_LOGAGENT_DBENGINE = 1,
	FCREPL_LOGAGENT_REPLSTUDIO = 2,
	FCREPL_LOGAGENT_REPLAGENT = 3,
	FCREPL_LOGAGENT_WEBSERVER = 4
} FCREPLLogAgent;

/* LogType table */
typedef enum
{
	FCREPL_LOGTYPE_INVALID = -1,
	FCREPL_LOGTYPE_INFO = 0,
	FCREPL_LOGTYPE_WARNING = 1,
	FCREPL_LOGTYPE_ERROR = 2,
	FCREPL_LOGTYPE_EXCEPTION = 3,
	FCREPL_LOGTYPE_TRACE = 4
} FCREPLLogType;

/* Log/Trace severity level */
typedef enum
{
	FCREPL_CRITICAL = 0,    /* Most critical severity level */
	FCREPL_SEV1 = 1,        /* Severity 1 - critical        */
	FCREPL_SEV2 = 2,        /* Severity 2 - important       */
	FCREPL_SEV3 = 3,        /* Severity 3 - normal          */
	FCREPL_INFO = 4,        /* Long information             */
	FCREPL_TRACE_LEVEL = 5  /* Trace information            */
} FCREPLSeverity;

/* Log/Trace detail level */
typedef enum
{
	FCREPL_DETAIL_ERROR = 1,    /* Only errors          */
	FCREPL_DETAIL_INFO = 2,     /* + basic information  */
	FCREPL_DETAIL_TRACE1 = 3,   /* + trace basic level  */
	FCREPL_DETAIL_TRACE2 = 4    /* + trace detail level */
} FCREPLDetailLevel;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Log
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcGetLatestLogs
*               Retrieve the latest Log entity objects.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               latestCount [IN]
*               Number of latest log entries to be retrieved
*
*               maxDetailLevel [IN]
*               Maximum detail level to be retrieved.
*
*               maxSevLevel [IN]
*               Maximum severity level to be retrieved.
*
*               showDBEngine [IN]
*               Show DBEngine messages
*
*               showReplStudio [IN]
*               Show Replication Studio messages
*
*               showReplAgent [IN]
*               Show Replication Agent messages
*
*               showWebServer [IN]
*               Show Web Server messages
*
*               dbEngineID [IN]
*               DBEngine identification to have the logs filtered by
*
*               funcName [IN]
*               Partial function name to have the logs filtered by
*
*               errorCode [IN]
*               Error code to have the logs filtered by
*
*               logList [OUT]
*               Log list in JSON format
                
                logCount [OUT]
                Number of items in the logList
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetLatestLogs(pFCREPLConn replConn, int latestCount, FCREPLDetailLevel maxDetailLevel, FCREPLSeverity maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent, bool showWebServer,
	int dbEngineID, const char *funcName, int errorCode, ppFCREPLLog *logList, int *logCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetLogs
*               Retrieve the Log entity objects
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               startTime [IN]
*               Period start time
*
*               endTime [IN]
*               Period end time
*
*               maxDetailLevel [IN]
*               Maximum detail level to be retrieved
*
*               maxSevLevel [IN]
*               Maximum severity level to be retrieved
*
*               showDBEngine [IN]
*               Show DBEngine messages
*
*               showReplStudio [IN]
*               Show Replication Studio messages
*
*               showReplAgent [IN]
*               Show Replication Agent messages
*
*               showWebServer [IN]
*               Show Web Server messages
*
*               dbEngineID [IN]
*               DBEngine identification to have the logs filtered by
*
*               funcName [IN]
*               Partial function name to have the logs filtered by
*
*               errorCode [IN]
*               Error code to have the logs filtered by
*
*               logListSize [IN]
*               Log list count to be retrieved
*
*               logStart [IN]
*               Log list start record
*
*               logList [OUT]
*               Log entity list
*
*               logCount [OUT]
*               Number of log entities in the list
*
*               totalLogs [OUT]
*               Total number of log entities
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetLogs(pFCREPLConn replConn, FCREPLDateTime startTime, FCREPLDateTime endTime, FCREPLDetailLevel maxDetailLevel, FCREPLSeverity maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent,
	bool showWebServer, int dbEngineID, const char *funcName, int errorCode, int logListSize, int logStart, ppFCREPLLog *logList, int *logCount, int *totalLogs);

/*^****************************************************************************\
*
*   Function:   fcArchiveLog
*               Archive the Log events that happened before a given number of
*               days
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               daysToArchive [IN]
*               Number of days to keep active
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcArchiveLog(pFCREPLConn replConn, int daysToArchive);



/*^****************************************************************************\
*
*   Class:      FCREPLLog
*               Log/trace/exception entity class.
*
\******************************************************************************/
class FCREPL_API FCREPLLog : public RCESLog
{
public:
	FCREPLLog();
	FCREPLLog(FCREPLLogType type, FCREPLLogAgent agent, int dbEngineID, const char *agentName, const char *functionName, FCREPLDetailLevel detailLevel, FCREPLSeverity sevLevel, int errorCode, const char *message);
	
/*
** Getters
*/

	// Log type
	FCREPLLogType GetType() { return (FCREPLLogType)((pRCESLog)this)->GetType(); };

	// Log agent type
	FCREPLLogAgent GetAgent() { return (FCREPLLogAgent)((pRCESLog)this)->GetAgent(); };

	// Log detail level
	FCREPLDetailLevel GetDetailLevel() { return (FCREPLDetailLevel)((pRCESLog)this)->GetDetailLevel(); };

	// Log severity level
	FCREPLSeverity GetSevLevel() { return (FCREPLSeverity)((pRCESLog)this)->GetSevLevel(); };

/*
	Inherited getters

	// Log event time
	RCESDateTime GetTime();

    // Log event type
    RCESLogType GetType();

    // DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	int GetDBEngineID();

    // Log agent
    RCESLogAgent GetAgent();

	// Log agent name
	const char *GetAgentName();

	// Log function name
	const char *GetFunctionName();

    // Log detail level
    RCESDetailLevel GetDetailLevel();

    // Log severity level
    RCESSeverity GetSevLevel();

	// Log error code
	int GetErrorCode();

	// Log error message
	const char *GetErrorMessage();
*/


/*
** Setters
*/

	// Log type
	void SetType(FCREPLLogType type) { ((pRCESLog)this)->SetType((RCESLogType)type); };

	// Log agent type
	void SetAgent(FCREPLLogAgent agent) { ((pRCESLog)this)->SetAgent((RCESLogAgent)agent); };

	// Log detail level
	void SetDetailLevel(FCREPLDetailLevel detailLevel) { ((pRCESLog)this)->SetDetailLevel((RCESDetailLevel)detailLevel); };

	// Log severity level
	void SetSevLevel(FCREPLSeverity sevLevel) { ((pRCESLog)this)->SetSevLevel((RCESSeverity)sevLevel); };

	// Log agent name
	void SetAgentName(const char *agentName) { ((pRCESLog)this)->SetAgentName(agentName); };

	// Log function name
	void SetFunctionName(const char *functionName) { ((pRCESLog)this)->SetFunctionName(functionName); };

	// Log error message
	void SetMessage(const char *message) { ((pRCESLog)this)->SetMessage(message); };

/*
	Inherited getters

	// Log event time
	void SetTime(RCESDateTime time);

    // Log type
    void SetType(RCESLogType type);
 
    // Log agent
    void SetAgent(RCESLogAgent agent);

	// DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	void SetDBEngineID(int dbEngineID);

    // Log agent name
    void SetAgentName(const char *agentName);
 
    // Log function name
    void SetFunctionName(const char *functionName);
 
    // Log detail level
    void SetDetailLevel(RCESDetailLevel detailLevel);
 
    // Log severity level
    void SetSevLevel(RCESSeverity sevLevel);

	// Log error code
	void SetErrorCode(int errorCode);

    // Log message
    void SetMessage(const char *message);
*/
};

#endif /* _FCREPLLOG_HPP_ */
