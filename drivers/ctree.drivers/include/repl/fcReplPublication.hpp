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

#ifndef _FCREPLPUBLICATION_HPP_
#define _FCREPLPUBLICATION_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcReplFile.hpp"
#include "fcrcespublication.hpp"

/* Forward class declaration */
class FCREPLPublication;
typedef FCREPLPublication *pFCREPLPublication, **ppFCREPLPublication;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Publication
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetPublications
*               Retrieve all the Publication entity objects
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngine [IN]
*               DBEngine Identification
*
*               publicationListSize [IN]
*               Publication list count to be retrieved
*
*               publicationStart [IN]
*               Publication list start record
*
*               publicationList [OUT]
*               Publication entity list
*
*               publicationCount [OUT]
*               Number of Publication entities in the list
*
*               totalPublications [OUT]
*               Total number of Publication entities
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetPublications(pFCREPLConn replConn, int dbEngine, int publicationListSize, int publicationStart, ppFCREPLPublication *publicationList, int *publicationCount, int *totalPublications);

/*^****************************************************************************\
*
*   Function:   fcReplGetPublicationsByName
*               Retrieve the Publication list by Name, or partially filtered
*               by name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
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
*               publicationListSize [IN]
*               Publication list count to be retrieved
*
*               publicationStart [IN]
*               Publication list start record
*
*               publicationList [OUT]
*               Publication entity list
*
*               publicationCount [OUT]
*               Number of Publication entities in the list
*
*               totalPublications [OUT]
*               Total number of Publication entities
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetPublicationsByName(pFCREPLConn replConn, int dbEngine, const char *name, bool partial, int publicationListSize, int publicationStart, ppFCREPLPublication *publicationList, int *publicationCount, int *totalPublications);

/*^****************************************************************************\
*
*   Function:   fcReplGetPublication
*               Retrieve the Publication entity object by its ID.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               publicationID [IN]
*               Publication identification
*
*               publication [OUT]
*               Publication entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetPublication(pFCREPLConn replConn, int publicationID, ppFCREPLPublication publication);

/*^****************************************************************************\
*
*   Function:   fcReplPersistPublication
*               Add a Publication entity into the database. If there already
*               is a publication with the given ID, update the existing record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               publication [IN]
*               Publication entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistPublication(pFCREPLConn replConn, pFCREPLPublication publication);

/*^****************************************************************************\
*
*   Function:   fcReplRemovePublication
*               Delete the Publication by its ID.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               publicationID [IN]
*               Publication identification
*
*               recursive [IN]
*               Recursive flag
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemovePublication(pFCREPLConn replConn, int publicationID, bool recursive);

/*^****************************************************************************\
*
*   Function:   fcReplGetFilesFromPublication
*               Retrieve the list of Files from the given Publication.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               publicationID [IN]
*               Publication identification
*
*               fileListSize [IN]
*               File list count to be retrieved
*
*               fileStart [IN]
*               File list start record
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
FCREPL_API int fcReplGetFilesFromPublication(pFCREPLConn replConn, int publicationID, int fileListSize, int fileStart, ppFCREPLFile *fileList, int *fileCount, int *totalFiles);

/*^****************************************************************************\
*
*   Function:   fcReplAddFilesToPublication
*               Add list of Files to a group.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               publicationID [IN]
*               Existing Publication identification
*
*               fileIDList [IN]
*               Existing File identification list
*
*               fileCount [IN]
*               Number of Files to be added
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplAddFilesToPublication(pFCREPLConn replConn, int publicationID, int *fileIDList, int fileCount);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveFilesFromPublication
*               Remove list of Files from a Publication.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               publicationID [IN]
*               Existing Publication identification
*
*               fileIDList [IN]
*               Existing File identification list
*
*               fileCount [IN]
*               Number of Files to be removed
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveFilesFromPublication(pFCREPLConn replConn, int publicationID, int *fileIDList, int fileCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetTempPubName
*               Retrieve the next available default name for a Publication.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               tempPubName [OUT]
*               Temporary publication name
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetTempPubName(pFCREPLConn replConn, char *tempPubName);


/*^****************************************************************************\
*
*   Class:      FCREPLPublication
*               Represents a group of file to be published. In order to set a
*               replication, this publication must be subscribed, which forms
*               a FCREPLSubscription, which is assigned to a FCREPLReplPlan
*               (Replication Plan).
*
\******************************************************************************/
class FCREPL_API FCREPLPublication : public RCESPublication
{
public:
	FCREPLPublication();
	FCREPLPublication(pFCREPLJson publication);
	
/*
** Getters
*/

/*
	Inherited getters

	// Publication identification.
	int GetID();

	// DBEngine identification.
	// It is linked to FCREPLDBEngine class.
	int GetDBEngineID();

    // DBEngine
    pRCESDBEngine GetDBEngine();

	// Database identification.
	// It is linked to FCREPLDatabase class.
	int GetDatabaseID();

    // Database
    pRCESDatabase GetDatabase();

	// Publication name.
	const char *GetName();

	// Publication description.
	const char *GetDescription();
*/


/*
** Setters
*/

	// DBEngine entity object
	void SetDBEngine(pFCREPLDBEngine dbEngine) { ((pRCESPublication)this)->SetDBEngine((pRCESDBEngine)dbEngine); };

	// Database entity object
	void SetDatabase(pFCREPLDatabase database) { ((pRCESPublication)this)->SetDatabase((pRCESDatabase)database); };

	// Publication name.
	void SetName(const char *name) { ((pRCESPublication)this)->SetName(name); };

	// Publication description.
	void SetDescription(const char *description) { ((pRCESPublication)this)->SetDescription(description); };

/*
	Inherited setters

	// Publication identification.
	void SetID(int id) ;

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
*/
};

#endif /* _FCREPLPUBLICATION_HPP_ */
