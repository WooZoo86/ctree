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

#ifndef _FCREPLAGENT_HPP_
#define _FCREPLAGENT_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesagent.hpp"

/* Forward class declaration */
class FCREPLAgent;
typedef FCREPLAgent *pFCREPLAgent, **ppFCREPLAgent;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Agent
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetAgents
*               Retrieve all the Agent entity objects for the given opSystem
*               identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               osId [IN]
*               OS identification or -1 for all Agents
*
*               agentList [OUT]
*               Agent entity list
*
*               agentCount [OUT]
*               Number of Agent entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetAgents(pFCREPLConn replConn, int osID, ppFCREPLAgent *agentList, int *agentCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetAgent
*               Retrieve the Agent entity object by its ID.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               agentID [IN]
*               Agent identification
*
*               agent [OUT]
*               Agent entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetAgent(pFCREPLConn replConn, int agentID, ppFCREPLAgent agent);

/*^****************************************************************************\
*
*   Function:   fcReplGetAgentByDBEngine
*               Retrieve the Agent entity object by its DBEngine identification.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               Embedded DBEngine identification
*
*               agent [OUT]
*               Agent entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetAgentByDBEngine(pFCREPLConn replConn, int dbEngineID, ppFCREPLAgent agent);

/*^****************************************************************************\
*
*   Function:   fcReplGetAgentByPath
*               Retrieve the Agent entity object by working path.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               workingVolumeID [IN]
*               Working volume identification
*
*               workingDir [IN]
*               Working directory
*
*               agent [OUT]
*               Agent entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetAgentByPath(pFCREPLConn replConn, int workingVolumeID, const char *workingDir, ppFCREPLAgent agent);

/*^****************************************************************************\
*
*   Function:   fcReplPersistAgent
*               Add an Agent entity into the database. If there already is a
*               Agent with the given working path, update the existing record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               agent [IN]
*               Agent entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistAgent(pFCREPLConn replConn, pFCREPLAgent agent);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveAgent
*               Delete the Agent by its ID.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               agentID [IN]
*               Agent identification
*
*               recursive [IN]
*               Recursive flag
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveAgent(pFCREPLConn replConn, int agentID, bool recursive);

/*^****************************************************************************\
*
*   Function:   fcReplCheckAgentStatus
*               Push a heartbeat action in order to check if the agent is
*               running or not and update its status. After validating it,
*               returns its status.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               agentID [IN]
*               Agent identification or -1 if it is for all the Agents
*
*               agentList [OUT]
*               Agent entity list retrieved or NULL in case it doesn't want
*               to retrieve it.
*
*               agentCount [OUT]
*               Agent entity list count.
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplCheckAgentStatus(pFCREPLConn replConn, int agentID, ppFCREPLAgent *agentList, int *agentCount);

/*^****************************************************************************\
*
*   Function:   fcReplSetAgentStatus
*               Update current status for the given agent.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               agentID [IN]
*               Agent identification
*
*               status [IN]
*               New status
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplSetAgentStatus(pFCREPLConn replConn, int agentID, FCREPLAgentStatus status);



/*^****************************************************************************\
*
*   Class:      FCREPLAgent
*               The Replication Studio has a distributed management so it is
*               requires at least one Replication Studio Agent per machine. This
*               class manage this agent information.
*
*               Note that you shouldn't manually create/change any of these
*               objects since it is managed internally, but you can check the
*               details from a specific object.
*
\******************************************************************************/
class FCREPL_API FCREPLAgent : public RCESAgent
{
public:
	FCREPLAgent();
	
/*
** Getters
*/

	// Current agent status
	FCREPLAgentStatus GetStatus() { return (FCREPLAgentStatus)((pRCESAgent)this)->GetStatus(); };

/*
	Inherited getters

	// Agent identification
	int GetID();

	// OpSystem identification that is running the agent.
	// It is linked to FCREPLOpSystem class
	int GetOSID();

	// DBEngine identification that has the agent embedded with
	// It is linked to FCREPLDBEngine class
	int GetDBEngineID();

    // Status
    RCESAgentStatus GetStatus();
 
    // Agent status string
    const char *GetStatusStr();
 
	// Last time that the agent status changed
	FCREPLDateTime GetStatusTime();

	// Agent's working volume identification
	// It is linked to FCREPLVolume class
	int GetWorkingVolumeID();
 
	// Agent's working directory
	char *GetWorkingDir();

    // Agent's working volume name
    char *GetWorkingVolumeName();

    // Agent consumer list
    ppRCESAgentConsumer GetConsumerList();
 
    // Agent Customer Count
    int GetConsumerCount();
 */

/*
** Setters
*/

	// Current agent status
	void SetStatus(FCREPLAgentStatus status) { ((pRCESAgent)this)->SetStatus((RCESAgentStatus)status); };

	// Agent's working volume name
	void SetWorkingVolumeName(const char *workingVolumeName) { ((pRCESAgent)this)->SetWorkingVolumeName(workingVolumeName); };

	// Agent's working directory
	void SetWorkingDir(const char *workingDir) { ((pRCESAgent)this)->SetWorkingDir(workingDir); };

/*
	Inherited setters

	// Agent identification
	void SetID(int id);

	// OpSystem identification that is running the agent.
	// It is linked to FCREPLOpSystem class
	void SetOSID(int osID);

	// DBEngine identification that has the agent embedded with
	// It is linked to FCREPLDBEngine class
	void SetDBEngineID(int dbEngineID);

    // Status
    void SetStatus(RCESAgentStatus status);

    // Last time that the agent status changed
	void SetStatusTime(FCREPLDateTime statusTime);

	// Agent's working volume identification
	// It is linked to FCREPLVolume class
	void SetWorkingVolumeID(int workingVolumeID) ;

    // Working volume name
    void SetWorkingVolumeName(const char *workingVolumeName);
 
    // Working Directory
    void SetWorkingDir(const char *workingDir);
 
    // Agent consumer list
    void SetConsumerList(ppRCESAgentConsumer agentConsumerList, int agentConsumerCount);
*/
};

#endif /* _FCREPLAGENT_HPP_ */
