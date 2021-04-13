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

#ifndef _FCREPLAGENTCONSUMER_HPP_
#define _FCREPLAGENTCONSUMER_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesagentconsumer.hpp"

/* Forward class declaration */
class FCREPLAgentConsumer;
typedef FCREPLAgentConsumer *pFCREPLAgentConsumer, **ppFCREPLAgentConsumer;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Agent Consumer
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetAgentConsumers
*               Retrieve all the consumers per agent identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               agentID [IN]
*               Agent identification
*
*               agentConsumerList [OUT]
*               Consumer status entity list
*
*               agentConsumerCount [OUT]
*               Number of Consumer status entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetAgentConsumers(pFCREPLConn replConn, int agentID, ppFCREPLAgentConsumer *agentConsumerList, int *agentConsumerCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetAgentConsumersByDB
*               Retrieve all the consumers per DBEngine identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               DBEngine identification
*
*               agentConsumerList [OUT]
*               Consumer status entity list
*
*               agentConsumerCount [OUT]
*               Number of Consumer status entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetAgentConsumersByDB(pFCREPLConn replConn, int agentID, ppFCREPLAgentConsumer *agentConsumerList, int *agentConsumerCount);

/*^****************************************************************************\
*
*   Function:   fcReplLoadActionExec
*               Load a given Action Executor for the given agent
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               agentID [IN]
*               Agent identification
*
*               consumerType [IN]
*               Consumer type
*
*               libName [IN]
*               Library name
*
*               thrdCount [IN]
*               Executor thread count
*
*               osID [IN]
*               OpSystem identification. If not provided, it will be retrieved
*               from the Agent record
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplLoadActionExec(pFCREPLConn replConn, int agentID, FCREPLConsumerType consumerType, const char *libName, int thrdCount, int osID = -1);

/*^****************************************************************************\
*
*   Function:   fcReplLoadActionExecByDB
*               Load a given Action Executor for the given dbEngine
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               DBEngine identification
*
*               consumerType [IN]
*               Consumer type
*
*               libName [IN]
*               Library name
*
*               thrdCount [IN]
*               Executor thread count
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplLoadActionExecByDB(pFCREPLConn replConn, int dbEngine, FCREPLConsumerType consumerType, const char *libName, int thrdCount);

/*^****************************************************************************\
*
*   Function:   fcReplUnloadActionExec
*               Unload a given Action Executor for the given agent
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               agentID [IN]
*               Agent identification
*
*               consumerType [IN]
*               Consumer type
*
*               osID [IN]
*               OpSystem identification. If not provided, it will be retrieved
*               from the Agent record
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplUnloadActionExec(pFCREPLConn replConn, int agentID, FCREPLConsumerType consumerType, int osID = -1);

/*^****************************************************************************\
*
*   Function:   fcReplUnloadActionExecByDB
*               Unload a given Action Executor for the given dbEngine
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               DBEngine identification
*
*               consumerType [IN]
*               Consumer type
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplUnloadActionExecByDB(pFCREPLConn replConn, int dbEngine, FCREPLConsumerType consumerType);




/*^****************************************************************************\
*
*   Class:      FCREPLAgentConsumer
*               This entity class represents the Action Executor/Consumer running
*               on an Agent.
*
\******************************************************************************/
class FCREPL_API FCREPLAgentConsumer : public RCESAgentConsumer
{
public:
	FCREPLAgentConsumer();
	
/*
** Getters
*/

/*
	Inherited getters

	// Agent identification
	int GetAgentID();

	// Consumer/Executor type
	RCESConsumerType GetConsumerType();

	// Consumer/Executor thread count
	int GetThrdCount();

	// Indicate if consumer/executor is active or not for Agent
	bool IsActive();

	// When current status has changed
	RCESDateTime GetStatusTime();
*/

/*
** Setters
*/

/*
	Inherited getters

	// Agent identification
	void SetAgentID(int agentID);

	// Consumer/Executor type
	void SetConsumerType(RCESConsumerType consumerType);

	// Consumer/Executor thread count
	void SetThrdCount(int thrdCount);

	// Indicate if consumer/executor is active or not for Agent
	void SetActive(bool active);

	// When current status has changed
	void SetStatusTime(RCESDateTime statusTime);
*/
};

#endif /* _FCREPLAGENTCONSUMER_HPP_ */