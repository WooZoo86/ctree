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

#ifndef _FCREPLDATABASE_HPP_
#define _FCREPLDATABASE_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesdatabase.hpp"

/* Forward class declaration */
class FCREPLDatabase;
typedef FCREPLDatabase *pFCREPLDatabase, **ppFCREPLDatabase;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Database
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetDatabases
*               Retrieve all the Databases entity objects for the given DBEngine
*               identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               DBEngine identification
*
*               databaseList [OUT]
*               Database entity list
*
*               databaseCount [OUT]
*               Number of database entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetDatabases(pFCREPLConn replConn, int dbEngineID, ppFCREPLDatabase *databaseList, int *databaseCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetDatabase
*               Retrieve the Database entity object by its Name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               DBEngine identification
*
*               name [IN]
*               Database name
*
*               database [OUT]
*               Database entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetDatabase(pFCREPLConn replConn, int dbEngineID, const char *name, ppFCREPLDatabase database);

/*^****************************************************************************\
*
*   Function:   fcReplPersistDatabase
*               Add a Database entity into the database. If there already is a
*               database with the given dbEngine/name, update the existing
*               record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               database [IN]
*               Database entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistDatabase(pFCREPLConn replConn, pFCREPLDatabase database);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveDatabase
*               Delete the Database by its identification.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               databaseId [IN]
*               Database identification
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveDatabase(pFCREPLConn replConn, int databaseID);

/*^****************************************************************************\
*
*   Method:     fcReplAddFilesToDatabase
*               Link list of files to a database.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               databaseId [IN]
*               Database identification
*
*               fileList [IN]
*               File ID list
*
*               fileCount [IN]
*               File count
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplAddFilesToDatabase(pFCREPLConn replConn, int databaseId, int *fileList, int fileCount);



/*^****************************************************************************\
*
*   Class:      FCREPLDatabase
*               It is below DBEngine hierarchy and has a list of tables/files.
*               In c-tree it can of be a SQL or CTDB type.
*
\******************************************************************************/
class FCREPL_API FCREPLDatabase : public RCESDatabase
{
public:
	FCREPLDatabase();
	FCREPLDatabase(pFCREPLJson database);


/*
** Getters
*/

	// Database path.
	const char *GetPath() { return ((pRCESDatabase) this)->GetPath(); };

/*
	Inherited getters

	// Database identification.
	int GetID();

	// DBEngine identification.
	// It is linked to FCREPLDBEngine class
	int GetDBEngineID();

	// Database name.
	const char *GetName();

	// Database dictionary file name.
	const char *GetDictFileName();

	// Return if database is SQL.
	bool GetIsSQL();
 
    // Retrieve the database path
    const char *GetPath();

*/

/*
** Setters
*/

	// Database name.                                              
	void SetName(const char *name) { ((pRCESDatabase)this)->SetName(name); };

	// Database dictionary file name.
	void SetDictFileName(const char *dictFileName) { ((pRCESDatabase)this)->SetDictFileName(dictFileName); };

/*
	Inherited setters

	// Database identification.
	void SetID(int id);

	// DBEngine identification.
	// It is linked to FCREPLDBEngine class
	void SetDBEngineID(int dbEngineID);

    // Set Name
    void SetName(const char *name);
 
    // Set File name string
    void SetDictFileName(const char *dictFileName);

	// Database SQL flag.
	void SetIsSQL(bool isSQL);
*/

};

#endif /* _FCREPLDATABASE_HPP_ */
