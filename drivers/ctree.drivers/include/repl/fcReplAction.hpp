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

#ifndef _FCREPLACTION_HPP_
#define _FCREPLACTION_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesaction.hpp"

/* Forward class declaration */
class FCREPLAction;
typedef FCREPLAction *pFCREPLAction, **ppFCREPLAction;

/* ActionType table */
typedef enum
{
	/* Non-ctree actions */
	FCREPL_ADD                   = 0, /* File add                                                 */
	FCREPL_DELETE                = 1, /* File remove                                              */
	FCREPL_CHANGE                = 2, /* File change                                              */
	FCREPL_REPL_HEARTBEAT_TARGET = 3, /* replication agent heartbeat target                       */

	/* Ctree actions */
	FCREPL_CTREE_START          = 100, /* ctree replication start                                  */
	FCREPL_CTREE_STOP           = 101, /* ctree replication stop                                   */
	FCREPL_CTREE_DUMPFILES      = 102, /* ctree dynamic dump files                                 */
	FCREPL_CTREE_CANCEL         = 103, /* cancel replication plan deployment                       */
	FCREPL_CTREE_START_MONITOR  = 104, /* start replication monitoring                             */
	FCREPL_CTREE_STOP_MONITOR   = 105, /* stop replication monitoring                              */
	FCREPL_CTREE_START_EXCEPLOG = 106, /* start replication exception log                          */
	FCREPL_CTREE_STOP_EXCEPLOG  = 107, /* stop replication exception log                           */
	FCREPL_CTREE_START_FUNCTIME = 108, /* start replication function timing collection             */
	FCREPL_CTREE_STOP_FUNCTIME  = 109, /* stop replication function timing collection              */
	FCREPL_CTREE_RESET_FUNCTIME = 110, /* reset replication function timing collection             */
	FCREPL_CTREE_GET_FUNCTIME   = 111, /* get replication function times                           */
	FCREPL_CTREE_PAUSE          = 112, /* pause replication                                        */
	FCREPL_CTREE_RESUME         = 113, /* resume replication                                       */
	FCREPL_CTREE_RESYNC         = 114, /* resync files                                             */
	FCREPL_CTREE_HEARTBEAT      = 115, /* replication agent heartbeat                              */

	/* FileSystem Sync actions */
	FCREPL_FS_ADD               = 200, /* filesystem add                                           */
	FCREPL_FS_DELETE            = 201, /* filesystem remove                                        */
	FCREPL_FS_CHANGE            = 202,  /* filesystem  change                                       */

	/* FileSystem actions */
	FCREPL_FS_SCAN              = 300, /* filesystem scan                                          */
	FCREPL_FS_LOAD              = 301, /* temporary filesystem load                                */
	FCREPL_FS_CHECK_DBENGINE    = 302, /* check DBEngine changes                                   */
	FCREPL_FS_SCAN_FOLDER       = 303, /* filesystem scan folder                                   */
	FCREPL_FS_SCAN_REPLAGENT    = 304, /* scan for Replication Agent                               */
	FCREPL_FS_IMPORT_REPLAGENT  = 305, /* import Replication Agent                                 */

	/* Basic Replication actions */
	FCREPL_REPL_DEPLOY          = 400, /* deploy replication plan                                  */
	FCREPL_REPL_START           = 401, /* start replication plan                                   */
	FCREPL_REPL_STOP            = 402, /* stop replication plan                                    */
	FCREPL_REPL_REG             = 403, /* register consumer for replication plan                   */
	FCREPL_REPL_REG_SOURCE      = 404, /* register consumer in source OS for non-ctree replication */
	FCREPL_REPL_UNREG           = 405, /* unregister consumer for replication plan                 */
	FCREPL_REPL_HEARTBEAT       = 406, /* replication agent heartbeat basic                        */
	FCREPL_REPL_START_MONITOR   = 407, /* start replication monitoring                             */
	FCREPL_REPL_STOP_MONITOR    = 408, /* stop replication monitoring                              */
	FCREPL_REPL_START_EXCEPLOG  = 409, /* start replication exception log                          */
	FCREPL_REPL_STOP_EXCEPLOG   = 410, /* stop replication exception log                           */
	FCREPL_REPL_START_FUNCTIME  = 411, /* start replication function timing collection             */
	FCREPL_REPL_STOP_FUNCTIME   = 412, /* stop replication function timing collection              */
	FCREPL_REPL_RESET_FUNCTIME  = 413, /* reset replication function timing collection             */
	FCREPL_REPL_GET_FUNCTIME    = 414, /* get replication function times                           */
	FCREPL_REPL_PAUSE           = 415, /* pause replication                                        */
	FCREPL_REPL_RESUME          = 416, /* resume replication                                       */
	FCREPL_REPL_SETTRACE        = 417, /* set trace                                                */

	FCREPL_UNKNOWN              = 500  /* Unknown action                                           */
} FCREPLActionType;

/* EntityType table */
typedef enum
{
	FCREPL_NONE             = -1,
	FCREPL_SITE             = 0,
	FCREPL_HARDWARE         = 1,
	FCREPL_OPSYSTEM         = 2,
	FCREPL_VOLUME           = 3,
	FCREPL_FILE             = 4,
	FCREPL_DBENGINE_ENT     = 5,
	FCREPL_SUBSCRIPTION_ENT = 6,
	FCREPL_REPLPLAN_ENT     = 7
} FCREPLEntityType;

/* Consumer table */
typedef enum
{
	FCREPL_DEFAULT         = -2, /* Default consumer                         */
	FCREPL_UNDEF           = -1, /* Undefined consumer                       */
	FCREPL_FILESYSTEM      = 0,  /* General Filesystem action consumer       */
	FCREPL_FILESYSTEM_SYNC = 1,  /* Filesystem sync action consumer          */
	FCREPL_REPL            = 2,  /* General replication plan consumer        */
	FCREPL_REPL_CTREE      = 3   /* Ctree replication action consumer        */
} FCREPLConsumerType;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Action
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplCheckAction
*               Check the current status for a given action identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               actionID [IN]
*               Action identification
*
*               checkGroup [IN]
*               Flag indicating if the children actions should also be checked
*
*               action [OUT]
*               Action entity object with the status updated
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplCheckAction(pFCREPLConn replConn, int actionID, bool checkGroup, ppFCREPLAction action);

/*^****************************************************************************\
*
*   Function:   fcReplCancelAction
*               Cancel a given action execution
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               actionID [IN]
*               Action identification
*
*               checkGroup [IN]
*               Flag indicating if the children actions should also be cancelled
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplCancelAction(pFCREPLConn replConn, int actionID, bool checkGroup);

/*^****************************************************************************\
*
*   Function:   fcArchiveAction
*               Archive the Action events that happened before a given number of
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
FCREPL_API int fcArchiveAction(pFCREPLConn replConn, int daysToArchive);


/*^****************************************************************************\
*
*   Class:      FCREPLAction
*               The Replication Studio has a distributed management based on
*               action objects pushed, consumed and checked to/from a central 
*               queue (ACTION table in Memphis).
*
*               Note that you shouldn't manually create/change any of these 
*               objects since it is managed internally, but you can check the 
*               details from a specific object.
*
\******************************************************************************/
class FCREPL_API FCREPLAction : public RCESAction
{
public:
	FCREPLAction();

/*
** Getters
*/

	// Action type
	FCREPLActionType GetActionType() { return (FCREPLActionType)GetAction(); };

	// Entity type related to the action: DBEngine, ReplPlan, etc
	FCREPLEntityType GetEntityType() { return (FCREPLEntityType)GetEntity(); };

	// Consumer type to process this action
	FCREPLConsumerType GetConsumerType() { return (FCREPLConsumerType)GetConsumer(); };

/*
	Inherited getters 

	// Action identification
	int GetActionID();

	// Parent action identification - action process which generated current one.
	// It is used for providing an action hierarchy
	int GetParentActionID();

	// Onwer action identification - action that groups a list of sub-actions.
	// The progress if the owner action depending on the progress of the whole group
	int GetOwnerActionID();

	// List of action parameters
	pFCParamHash GetParams();

	// Action description
	const char *GetDescription();

    // Action type
    RCESActionType GetAction();
 
    // Entity type
    RCESEntityType GetEntity();
 
	// Entity identification related to the action: DBEngine ID, ReplPlan ID, etc
	int GetEntityPK();

    // Action type string
    const char *GetActionStr();
 
	// Time to wait before action can start being processed
	int GetWaitSecs();

    // File volume ID
    int GetFileVolumeID();
 
    // File path
    const char *GetFilePath();
 
    // File name
    const char *GetFileName();
 
	// Current action progress
	int GetProgress();

    // JSON action information
    pRCESJson GetJson();
 
	// Action error code
	int GetErrorCode();

	// Action error message
	char *GetErrorMessage();

	// Agent identification that is processing or processed the action
	// It is linked to FCREPLAgent class
	int GetAgentID();

	// Replication Plan identification when the action is specific for a Replication Plan.
	// It is linked to FCREPLReplPlan class
	int GetReplPlanID();

    // Consumer type
    RCESConsumerType GetConsumer();
 
	// Action content length
	int GetContentLen();

	// Action content
	void *GetContent();

	// Factor of the action progress to impact the owner action.
	// For example, this action can represent 20% of the owner action progress
	double GetFactor();
 
 
    Inherited Setters
 
    // Action ID
    SetActionID(int actionID);
 
    // Time processed
    SetTimeProcessed(RCESDateTime timeProcessed);
 
    // Error code
    SetErrorCode(int errorCode);
 
    // Error Message
    SetErrorMessage(const char *errorMessage);
 
    // Action Time
    SetActionTime(RCESDateTime actionTime);
 
    // Progress
    SetProgress(int progress);
 
    // Entity Type
    SetEntityType(RCESEntityType entityType);
 
    // Entity PK
    SetEntityPK(int entityPK);
 
    // Owner Action ID
    SetOwnerActionID(int ownerActionID);
 
    // Agent ID
    SetAgentID(int agentID);
 
    //  Content string
    SetContent(void *content, int contentLen);
 
    // Factor
    SetFactor(double factor);
 
    // Action type
    SetAction(RCESActionType actionType);

*/

};

#endif /* _FCREPLACTION_HPP_ */
