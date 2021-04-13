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

#ifndef _FCRCESLOGGER_HPP_
#define _FCRCESLOGGER_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrcesexception.hpp"

/*^****************************************************************************\
*
*   RCESLogger
*   Recon-e-Sense logger class
*
*   Processes the log actions, building the message and directing to the correct
*   output.
*
\******************************************************************************/
class RCESLogger
{
	public:
		/* Services */
		static void log(FCPool<RCESMasterConnPooled> *connPool, const char *errMessage, const char *functionName, RCESLogAgent agentType = RCES_LOGAGENT_INVALID);
		static void trace(FCPool<RCESMasterConnPooled> *connPool, const char *functionName, RCESLogAgent agentType, RCESDetailLevel detailLevel, const char *format, ...);
		static void error(FCPool<RCESMasterConnPooled> *connPool, const char *errMessage, int errCode, const char *functionName, RCESSeverity level, RCESLogAgent agentType = RCES_LOGAGENT_INVALID);
		static void exception(FCPool<RCESMasterConnPooled> *connPool, FCException &excep, RCESLogAgent agentType = RCES_LOGAGENT_INVALID);

		/* Constructors & destructor */
		RCESLogger(pRCESConfig config, pRCESMasterProvider provider);
		virtual ~RCESLogger();

		/* Public methods */
		void log(const char *logMessage, const char *functionName, RCESLogAgent agentType = RCES_LOGAGENT_INVALID);
		void trace(const char *functionName, RCESLogAgent agentType, RCESDetailLevel detailLevel, const char *format, ...);
		void error(const char *errMessage, int errCode, const char *functionName, RCESSeverity level, RCESLogAgent agentType = RCES_LOGAGENT_INVALID);
		void exception(FCException &e, RCESLogAgent agentType = RCES_LOGAGENT_INVALID);
		void traceFormat(const char *functionName, RCESLogAgent agentType, RCESDetailLevel detailLevel, const char *format, va_list arg);

	private:
		/* Private properties */
		pRCESMasterProvider _provider;
		FILE *_logFile;
		char _currTimeStr[RCES_DATETIME_STRLEN];
		pRCESConfig _config;
#ifdef RCES_TRACE
		char _traceMsg[RCES_MAX_ERRMSG_LEN+1];
#endif
		char _msgBuffer[RCES_MAX_ERRMSG_LEN+1];

		/* Private methods */
		void _openLogFile(const char *logFileName);
		char *_getCurrTime();
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESLogger *pRCESLogger, **ppRCESLogger;

#endif /* _FCRCESLOGGER_HPP_ */