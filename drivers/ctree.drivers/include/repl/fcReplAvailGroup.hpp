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

#ifndef _FCREPLAVAILGROUP_HPP_
#define _FCREPLAVAILGROUP_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesavailgroup.hpp"
#include "fcrcesreplica.hpp"

/* Forward class declaration */
class FCREPLAvailGroup;
class FCREPLReplica;
typedef FCREPLAvailGroup *pFCREPLAvailGroup, **ppFCREPLAvailGroup;
typedef FCREPLReplica *pFCREPLReplica, **ppFCREPLReplica;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Availability Group
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetAvailGroups
*               Retrieve all the Availability Groups entity objects
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               aGroupListSize [IN]
*               Availability group list count to be retrieved
*
*               aGroupStart [IN]
*               Availability group list start record
*
*               aGroupList [OUT]
*               Availability group entity list
*
*               aGroupCount [OUT]
*               Number of Availability group entities in the list
*
*               totalAvailGroups [OUT]
*               Total number of Availability group entities
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetAvailGroups(pFCREPLConn replConn, int aGroupListSize, int aGroupStart, ppFCREPLAvailGroup *aGroupList, int *aGroupCount, int *totalAvailGroups);

/*^****************************************************************************\
*
*   Function:   fcReplGetAvailGroupsByName
*               Retrieve the Availability Group list by Name, or partially
*               filtered by name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               name [IN]
*               Availability Group name
*
*               partial [IN]
*               Flag indicating that the search by name should use partial name
*
*               aGroupListSize [IN]
*               Availability group list count to be retrieved
*
*               aGroupStart [IN]
*               Availability group list start record
*
*               aGroupList [OUT]
*               Availability group entity list
*
*               aGroupCount [OUT]
*               Number of Availability group entities in the list
*
*               totalAvailGroups [OUT]
*               Total number of Availability group entities
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetAvailGroupsByName(pFCREPLConn replConn, const char *name, bool partial, int aGroupListSize, int aGroupStart, ppFCREPLAvailGroup *aGroupList, int *aGroupCount, int *totalAvailGroups);

/*^****************************************************************************\
*
*   Function:   fcReplGetAvailGroup
*               Retrieve the Availability Group entity object by its ID.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               availGroupID [IN]
*               Availability Group identification
*
*               availGroup [OUT]
*               Availability Group entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetAvailGroup(pFCREPLConn replConn, int availGroupID, ppFCREPLAvailGroup availGroup);

/*^****************************************************************************\
*
*   Function:   fcReplPersistAvailGroup
*               Add a Availability Group entity into the database. If there
*               already is a ctGetAvailGroup group with the given ID, update the
*               existing record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               availGroup [IN]
*               Availability group entity to be persisted
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistAvailGroup(pFCREPLConn replConn, pFCREPLAvailGroup availGroup);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveAvailGroup
*               Delete the Availability Group by its ID.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               availGroupId [IN]
*               Availability group identification
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveAvailGroup(pFCREPLConn replConn, int availGroupId);

/*^****************************************************************************\
*
*   Function:   fcReplPersistReplicasToGroup
*               Add list of Replicas to an Availability Group.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               availGroupId [IN]
*               Availability group identification
*
*               replicaList [IN]
*               Replica entity object list
*
*               replicaCount [IN]
*               Number of Replicas to be added
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistReplicasToGroup(pFCREPLConn replConn, int availGroupID, ppFCREPLReplica replicaList, int replicaCount);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveReplicasFromGroup
*               Remove list of Replicas from an Availability Group.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineIDList [IN]
*               DBEngine ID list
*
*               dbEngineCount [IN]
*               Number of DBEngines to be removed
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveReplicasFromGroup(pFCREPLConn replConn, int *dbEngineIDList, int dbEngineCount);



/*^****************************************************************************\
*
*   Class:      FCREPLAvailGroup
*               An Availability Group entity links gather a number of replicas
*               being one the primary and others secondaries. It is used for
*               setting up failover rules.
*
\******************************************************************************/
class FCREPL_API FCREPLAvailGroup : public RCESAvailGroup
{
public:
	FCREPLAvailGroup();
	FCREPLAvailGroup(pFCREPLJson availGroup);

/*
** Getters
*/

	// Availability Group status
	FCREPLReplStatus GetStatus() { return (FCREPLReplStatus)((pRCESAvailGroup)this)->GetStatus(); };

	// List of replicas
	ppFCREPLReplica GetReplicaList() { return (ppFCREPLReplica)((pRCESAvailGroup)this)->GetReplicaList(); };

/*
	Inherited getters

	// Availability Group identification
	int GetID();

	// Availability Group name
	const char *GetName();

	// Availability Group description
	const char *GetDescription();

	// Status time
	RCESDateTime GetStatusTime();

	// Last status message
	char *GetStatusMsg();

	// Action identification for the current status
	int GetStatusActionID();

	// Flag indicating if Availability Group has been deployed
	int IsDeployed();

	// Replica count
	int GetReplicaCount();
*/


/*
** Setters
*/

	// Replication Plan status
	void SetStatus(FCREPLEngineStatus status) { ((pRCESAvailGroup)this)->SetStatus((RCESEngineStatus)status); };

	// Source DBEngine object
	void SetReplicaList(ppFCREPLReplica replicaList, int replicaCount) { ((pRCESAvailGroup)this)->SetReplicaList((ppRCESReplica)replicaList, replicaCount); };

/*
	Inherited setters

	// Replication Plan identification
	void SetID(int id);

	// Availability Group name
	void SetName( const char *name );

	// Availability Group description
	void SetDescription( const char *description );

	// Status time
	void SetStatusTime(RCESDateTime statusTime);

	// Last status message
	void SetStatusMsg(const char *statusMsg);

	// Action identification for the current status
	void SetStatusActionID(int statusActionID);

	// Flag indicating if Availability Group has been deployed
	void SetIsDeployed(bool isDeployed);
*/
};

#endif /* _FCREPLAVAILGROUP_HPP_ */