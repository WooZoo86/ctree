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

#ifndef _FCREPLTRACE_HPP_
#define _FCREPLTRACE_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesconfig.hpp"

/* Forward class declaration */
class FCREPLDBEngineTrace;
typedef FCREPLDBEngineTrace *pFCREPLDBEngineTrace, **ppFCREPLDBEngineTrace;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Trace
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplSetTrace
*               Update the traceing status by enabling or disabling any of its
*               type of tracing capabilities.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               enableWebTrace [IN]
*               Web API trace enable status
*
*               globalEnableTrace [IN]
*               Global trace enable status
*
*               traceList [IN]
*               List of trace enable status by dbEngine
*
*               traceListCount [IN]
*               Number of trace objects in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplSetTrace(pFCREPLConn replConn, bool enableWebTrace, bool globalEnableTrace, ppFCREPLDBEngineTrace traceList, int traceListCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetTrace
*               Retrieve the current traceing status.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               enableWebTrace [OUT]
*               Web trace setup
*
*               globalEnableTrace [OUT]
*               Global trace setup
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetTrace(pFCREPLConn replConn, bool *enableWebTrace, bool *globalEnableTrace);


/*^****************************************************************************\
*
*   Class:      FCREPLDBEngineTrace
*               Trace status by DBEngine.
*
\******************************************************************************/
class FCREPL_API FCREPLDBEngineTrace : public RCESDBEngineTrace
{
public:
	FCREPLDBEngineTrace(int dbEngineID, bool enabled);

/*
** Getters
*/

/*
	Inherited getters

	// DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	int GetDBEngineID();

	// Return if trace is enabled.
	bool GetEnabled();
*/
};

#endif /* _FCREPLTRACE_HPP_ */
