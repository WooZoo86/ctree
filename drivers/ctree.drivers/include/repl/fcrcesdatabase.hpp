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
 *      Copyright (c) 2013 - 2014 FairCom Corporation.
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

#ifndef _FCRCESDATABASE_HPP_
#define _FCRCESDATABASE_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESDatabase;
class RCESMasterProvider;
class RCESLocalProvider;
typedef RCESDatabase *pRCESDatabase, **ppRCESDatabase;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;
typedef RCESLocalProvider *pRCESLocalProvider, **ppRCESLocalProvider;

#define RCES_DATABASE_LIST "databaseList"
#define RCES_DATABASE "database"
#define RCES_DATABASE_ID "id"
#define RCES_DATABASE_DBENGINE "dbEngine" 
#define RCES_DATABASE_NAME "name"
#define RCES_DATABASE_FILE "file"
#define RCES_DATABASE_DICTFILENAME "dictFileName"
#define RCES_DATABASE_ISSQL "isSQL"
#define RCES_DATABASE_TOTAL "total"

/*^****************************************************************************\
*
*   RCESDatabase
*   Recon-e-Sense database class
*
\******************************************************************************/
class RCESDatabase
{
public:
	/* Constructors & destructor */
	RCESDatabase();
	RCESDatabase(pRCESDatabase database);
	RCESDatabase(pRCESJson database);
	virtual ~RCESDatabase();

	/* Public services */
	static int ctGetDatabases(pRCESMasterProvider masterProv, int dbEngineID, int databaseListSize, int databaseStart, ppRCESDatabase *databaseList, int *databaseCount, int *totalDatabases);
	static int ctGetDatabases(pRCESMasterProvider masterProv, int dbEngineID, bool paging, int databaseListSize, int databaseStart, ppRCESJson result);
	static int ctGetDatabase(pRCESMasterProvider masterProv, int databaseID, ppRCESDatabase database);
	static int ctGetDatabase(pRCESMasterProvider masterProv, int databaseID, bool isPaging, ppRCESJson result);
	static int ctGetDatabase(pRCESMasterProvider masterProv, int dbEngineID, const char *name, ppRCESDatabase database);
	static int ctGetDatabase(pRCESMasterProvider masterProv, int dbEngineID, const char *name, bool isPaging, ppRCESJson result);
	static int ctPersistDatabase(pRCESMasterProvider masterProv, pRCESDatabase database);
	static int ctPersistDatabase(pRCESMasterProvider masterProv, pRCESJson database, ppRCESJson result);
	static int ctRemoveDatabase(pRCESMasterProvider masterProv, int databaseId);
	static int ctRemoveDatabase(pRCESMasterProvider masterProv, int databaseId, ppRCESJson result);
	static int ctAddFilesToDatabase(pRCESMasterProvider masterProv, int databaseId, int *fileList, int fileCount);

	/* Public methods */
	int GetID() { return _id; };
	int GetDBEngineID() { return _dbEngineID; };
	const char *GetName() { return _name; };
	const char *GetDictFileName() { return _dictFileName; };
	bool GetIsSQL() { return _isSQL; };
	const char *GetPath();

	void SetID(int id) { _id = id; };
	void SetDBEngineID(int dbEngineID) { _dbEngineID = dbEngineID; };
	void SetName(const char *name);
	void SetDictFileName(const char *dictFileName);
	void SetIsSQL(bool isSQL) { _isSQL = isSQL; };

	pRCESJson GetJson();
	void Update(pRCESJson databasePatch);
	int StartNotification(pRCESLocalProvider localProv, int qHandle);
	int StopNotification(pRCESLocalProvider localProv, int qHandle);

private:
	/* Private properties */
	int _id;
	int _dbEngineID;
	char *_name;
	char *_dictFileName;
	bool _isSQL;
	char *_path;
	int _datno;
	bool _notified;
};
/*~****************************************************************************/

#endif /* _FCRCESDATABASE_HPP_ */