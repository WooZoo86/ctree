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

#ifndef _FCREPLSUBSCRIPTION_HPP_
#define _FCREPLSUBSCRIPTION_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcessubscription.hpp"

/* Forward class declaration */
class FCREPLSubscription;
class FCREPLReplRedir;
typedef FCREPLSubscription *pFCREPLSubscription, **ppFCREPLSubscription;
typedef FCREPLReplRedir *pFCREPLReplRedir, **ppFCREPLReplRedir;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Subscription
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetSubscriptions
*               Retrieve all the Subscription entity objects
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               publication [IN]
*               Publication Identification
*
*               dbEngine [IN]
*               DBEngine Identification
*
*               subscriptionListSize [IN]
*               Subscription list count to be retrieved
*
*               subscriptionStart [IN]
*               Subscription list start record
*
*               subscriptionList [OUT]
*               Subscription entity list
*
*               subscriptionCount [OUT]
*               Number of Subscription entities in the list
*
*               totalSubscriptions [OUT]
*               Total number of Subscription entities
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetSubscriptions(pFCREPLConn replConn, int publication, int dbEngine, int subscriptionListSize, int subscriptionStart, ppFCREPLSubscription *subscriptionList, int *subscriptionCount, int *totalSubscriptions);

/*^****************************************************************************\
*
*   Function:   fcReplGetSubscriptions
*               Retrieve all the subscription entity objects for the given
*               replication plan.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Replication plan identification
*
*               replSubsListSize [IN]
*               Replication subscription list count to be retrieved
*
*               replSubsStart [IN]
*               Replication subscription list start record
*
*               subsList [OUT]
*               Subscription entity list
*
*               subsCount [OUT]
*               Number of subscription entities in the list
*
*               totalReplSubs [OUT]
*               Total replication subscription
*
*   Returns:    Error code or FCREPL_MORE_RESULT in case of pending files to be
*               read
*
\******************************************************************************/
FCREPL_API int fcReplGetSubscriptions(pFCREPLConn replConn, int replPlanID, int replSubsListSize, int replSubsStart, ppFCREPLSubscription *subsList, int *subsCount, int *totalReplSubs);

/*^****************************************************************************\
*
*   Function:   fcReplGetSubscriptionsByName
*               Retrieve the Publication list by Name, or partially filtered
*               by name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               publication [IN]
*               Publication ID
*
*               dbEngine [IN]
*               DBEngine ID
*
*               name [IN]
*               Publication name
*
*               partial [IN]
*               Flag indicating that the search by name should use partial name
*
*               subscriptionListSize [IN]
*               Subscription list count to be retrieved
*
*               subscriptionStart [IN]
*               Subscription list start record
*
*               subscriptionList [OUT]
*               Subscription entity list
*
*               subscriptionCount [OUT]
*               Number of Subscription entities in the list
*
*               totalSubscriptions [OUT]
*               Total number of Subscription entities
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetSubscriptionsByName(pFCREPLConn replConn, int publication, int dbEngine, const char *name, bool partial, int subscriptionListSize, int subscriptionStart, ppFCREPLSubscription *subscriptionList,
	int *subscriptionCount, int *totalSubscriptions);

/*^****************************************************************************\
*
*   Function:   fcReplGetSubscription
*               Retrieve the Subscription entity object by its ID.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               subscriptionID [IN]
*               Subscription identification
*
*               subscription [OUT]
*               Subscription entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetSubscription(pFCREPLConn replConn, int subscriptionID, ppFCREPLSubscription subscription);

/*^****************************************************************************\
*
*   Function:   fcReplPersistSubscription
*               Add a Subscription entity into the database. If there already
*               is a subscription with the given ID, update the existing record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               subscription [IN]
*               Subscription entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistSubscription(pFCREPLConn replConn, pFCREPLSubscription subscription);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveSubscription
*               Delete the Subscription by its ID.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               subscriptionID [IN]
*               Subscription identification
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveSubscription(pFCREPLConn replConn, int subscriptionID);

/*^****************************************************************************\
*
*   Function:   fcReplSubsFilesPreview
*               Build a list of target files for the given Publication and
*               Subscription root path setup in a preview mode.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               publicationID [IN]
*               Publication identification
*
*               rootVolumeID [IN]
*               Subscription root volume identification
*
*               rootPath [IN]
*               Subscription root path
*
*               dbEngineID [IN]
*               Subscription DBEngine
*
*               fileListSize [IN]
*               File list count to be retrieved
*
*               fileStart [IN]
*               File list start record
*
*               calcRootVolume [OUT]
*               Subscription's calculated root volume
*
*               calcRootPath [OUT]
*               Subscription's calculated root path
*
*               fileList [OUT]
*               File entity list
*
*               fileCount [OUT]
*               Number of File entities in the list
*
*               totalFiles [OUT]
*               Total File
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplSubsFilesPreview(pFCREPLConn replConn, int publicationID, int rootVolumeID, const char *rootPath, int dbEngineID, int fileListSize, int fileStart, int *calcRootVolume, char **calcRootPath, ppFCREPLFile *fileList,
	int *fileCount, int *totalFiles);

/*^****************************************************************************\
*
*   Function:   fcReplGetTempSubsName
*               Retrieve the next available default name for a Subscription.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               tempSubsName [OUT]
*               Temporary subscription name
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetTempSubsName(pFCREPLConn replConn, char *tempSubsName);


/*^****************************************************************************\
*
*   Class:      FCREPLSubscription
*               Represents a group of file published and subscribed for 
*               replication. In order to set a replication, this publication 
*               must be subscribed, which forms a FCREPLSubscription, which is 
*               assigned to a FCREPLReplPlan (Replication Plan).
*
\******************************************************************************/
class FCREPL_API FCREPLSubscription : public RCESSubscription
{
public:
	FCREPLSubscription();
	FCREPLSubscription(pFCREPLJson subscription);

/*
** Getters
*/

/*
	Inherited getters

	// Subscription identification.
	int GetID();

	// Publication identification.
	// It is linked to FCREPLPublication class.
	int GetPublicationID();

    // Publication
    pRCESPublication GetPublication();

	// DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	int GetDBEngineID();

    // DBEngine
    pRCESDBEngine GetDBEngine() { return _dbEngine; };

	// Database identification.
	// It is linked to FCREPLDatabase class.
	int GetDatabaseID();

    // Database
    pRCESDatabase GetDatabase();

	// Subscription name.
	const char *GetName();

	// Subscription description.
	const char *GetDescription();

	// Return if the Subscription is bidirectional.
	bool GetIsBiDir();

	// Replication Plan identification.
	// It is linked to FCREPLReplPlan class.
	int GetReplPlanID();

    // Redirection list
    ppRCESReplRedir GetRedirList();
 
    // Redirection list count
    int GetRedirListCount();
*/


/*
** Setters
*/

	// Publication entity object.
	void SetPublication(pFCREPLPublication publication) { ((pRCESSubscription)this)->SetPublication((pRCESPublication)publication); };

	// DBEngine entity object.
	void SetDBEngine(pFCREPLDBEngine dbEngine) { ((pRCESSubscription)this)->SetDBEngine((pRCESDBEngine)dbEngine); };

	// Database entity object.
	void SetDatabase(pFCREPLDatabase database) { ((pRCESSubscription)this)->SetDatabase((pRCESDatabase)database); };

	// Subscription name.
	void SetName(const char *name) { ((pRCESSubscription)this)->SetName(name); };

	// Subscription description.
	void SetDescription(const char *description) { ((pRCESSubscription)this)->SetDescription(description); };

	// Redirection list.
	void SetRedirList(ppFCREPLReplRedir redirList, int redirListCount) { ((pRCESSubscription)this)->SetRedirList((ppRCESReplRedir)redirList, redirListCount); };

/*
	Inherited setters

	// Subscription identification.
	void SetID(int id);

	// Publication identification.
	// It is linked to FCREPLPublication class.
	void SetPublicationID(int publicationID);

    // Publication
    void SetPublication(pRCESPublication publication);

	// DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	void SetDBEngineID(int dbEngineID);

    // DBEngine
    void SetDBEngine(pRCESDBEngine dbEngine);

	// Database identification.
	// It is linked to FCREPLDatabase class.
	void SetDatabaseID(int databaseID);

    // Database
    void SetDatabase(pRCESDatabase database);
 
    // Name
    void SetName(const char *name);
 
    // Description
    void SetDescription(const char *description);

	// Return if the Subscription is bidirectional.
	void SetIsBiDir(bool isBiDir);

	// Replication Plan identification.
	// It is linked to FCREPLReplPlan class.
	void SetReplPlanID(int replPlanID);

    // Redirection list
    void SetRedirList(ppRCESReplRedir redirList, int redirListCount);
*/
};

#endif /* _FCREPLSUBSCRIPTION_HPP_ */
