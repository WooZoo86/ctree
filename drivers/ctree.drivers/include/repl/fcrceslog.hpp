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

#ifndef _FCRCESLOG_HPP_
#define _FCRCESLOG_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESLog;
class RCESMasterProvider;
typedef RCESLog *pRCESLog, **ppRCESLog;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_LOG_LIST "logList"
#define RCES_LOG "log"
#define RCES_LOG_TIME "time"
#define RCES_LOG_TYPE "type"
#define RCES_LOG_AGENT "agent"
#define RCES_LOG_DBENGINE "dbEngine"
#define RCES_LOG_AGENTNAME "agentName"
#define RCES_LOG_FUNCNAME "functionName"
#define RCES_DETAIL_LEVEL "detailLevel"
#define RCES_SEV_LEVEL "severity"
#define RCES_LOG_ERRORCODE "errorCode"
#define RCES_LOG_MESSAGE "message"
#define RCES_LOG_BEGINTIME "beginTime"
#define RCES_LOG_ENDTIME "endTime"
#define RCES_LOG_MAXDETAILLEVEL "maxDetailLevel"
#define RCES_LOG_MAXSEVLEVEL "maxSevLevel"
#define RCES_LOG_SHOWDBENGINE "showDBEngine"
#define RCES_LOG_SHOWREPLSTUDIO "showReplStudio"
#define RCES_LOG_SHOWREPLAGENT "showReplAgent"
#define RCES_LOG_SHOWWEBSERVER "showWebServer"
#define RCES_LOG_DBENGINE "dbEngine"
#define RCES_LOG_FUNCNAMEFILTER "FunctionNameFilter"
#define RCES_LOG_LATEST "latest"

#define RCES_LOG_TOTAL "total"

/* Log type string values */
#define RCES_LOGTYPE_INVALID_STR          "Invalid"
#define RCES_LOGTYPE_INFO_STR             "Info"
#define RCES_LOGTYPE_WARNING_STR          "Warning"
#define RCES_LOGTYPE_ERROR_STR            "Error"
#define RCES_LOGTYPE_EXCEPTION_STR        "Exception"
#define RCES_LOGTYPE_TRACE_STR            "Trace"

/* Agent type string values */
#define RCES_LOGAGENT_INVALID_STR         "Invalid"
#define RCES_LOGAGENT_INTERNAL_STR        "Internal"
#define RCES_LOGAGENT_DBENGINE_STR        "DBEngine"
#define RCES_LOGAGENT_REPLSTUDIO_STR      "Replication Studio"
#define RCES_LOGAGENT_REPLAGENT_STR       "Replication Agent"
#define RCES_LOGAGENT_WEBSERVER_STR       "Web Server"

/*^****************************************************************************\
*
*   RCESLog
*   Recon-e-Sense log class
*
\******************************************************************************/
class RCESLog
{
public:
	/* Constructors & destructor */
	RCESLog();
	RCESLog(RCESLogType type, RCESLogAgent agent, int dbEngineID, const char *agentName, const char *functionName, RCESDetailLevel detailLevel, RCESSeverity sevLevel, int errorCode, const char *message);
	virtual ~RCESLog();

	/* Public services */
	static int ctGetLatestLogs(pRCESMasterProvider masterProv, int latestCount, short maxDetailLevel, short maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent, bool showWebServer,
		int dbEngineID, const char *funcName, int errorCode, int logListSize, int logStart, ppRCESLog *logList, int *logCount, int *totalLogs);
	static int ctGetLatestLogs(pRCESMasterProvider masterProv, int latestCount, short maxDetailLevel, short maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent, bool showWebServer,
		int dbEngineID, const char *funcName, int errorCode, bool isPaging, int logListSize, int logStart, ppRCESJson result);

	static int ctGetLogs(pRCESMasterProvider masterProv, RCESDateTime startTime, RCESDateTime endTime, short maxDetailLevel, short maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent,
		bool showWebServer, int dbEngineID, const char *funcName, int errorCode, int logListSize, int logStart, ppRCESLog *logList, int *logCount, int *totalLogs);
	static int ctGetLogs(pRCESMasterProvider masterProv, RCESDateTime startTime, RCESDateTime endTime, short maxDetailLevel, short maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent,
		bool showWebServer, int dbEngineID, const char *funcName, int errorCode, bool isPaging, int logListSize, int logStart, ppRCESJson result);
	static int ctArchive(pRCESMasterProvider masterProv, int daysToArchive);

	/* Public methods */
	RCESDateTime GetTime() { return _time; };
	RCESLogType GetType() { return _type; };
	int GetDBEngineID() { return _dbEngineID; };
	RCESLogAgent GetAgent() { return _agent; };
	const char *GetAgentName() { return _agentName; };
	const char *GetFunctionName() { return _functionName; };
	RCESDetailLevel GetDetailLevel() { return _detailLevel; };
	RCESSeverity GetSevLevel() { return _sevLevel; };
	int GetErrorCode() { return _errorCode; };
	const char *GetErrorMessage() { return _message; };

	void SetTime(RCESDateTime time) { _time = time; };
	void SetType(RCESLogType type) { _type = type; };
	void SetAgent(RCESLogAgent agent) { _agent = agent; };
	void SetDBEngineID(int dbEngineID) { _dbEngineID = dbEngineID; };
	void SetAgentName(const char *agentName);
	void SetFunctionName(const char *functionName);
	void SetDetailLevel(RCESDetailLevel detailLevel) { _detailLevel = detailLevel; };
	void SetSevLevel(RCESSeverity sevLevel) { _sevLevel = sevLevel; };
	void SetErrorCode(int errorCode) { _errorCode = errorCode; };
	void SetMessage(const char *message);

	pRCESJson GetJson();

private:
	/* Private methods */
	const char *_getTypeStr();
	const char *_getAgentStr();

	/* Private properties */
	RCESDateTime _time;
	RCESLogType _type;
	int _dbEngineID;
	RCESLogAgent _agent;
	char *_agentName;
	char *_functionName;
	RCESDetailLevel _detailLevel;
	RCESSeverity _sevLevel;
	int _errorCode;
	char *_message;
};
/*~****************************************************************************/

#endif /* _FCRCESLOG_HPP_ */