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

#ifndef _FCRCESPUBLICATION_HPP_
#define _FCRCESPUBLICATION_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESPublication;
class RCESMasterProvider;
class RCESRule;
typedef RCESPublication *pRCESPublication, **ppRCESPublication;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;
typedef RCESRule *pRCESRule, **ppRCESRule;

#define RCES_PUBLICATION_LIST "publicationList"
#define RCES_PUBLICATION "publication"
#define RCES_PUBLICATION_ID "id"
#define RCES_PUBLICATION_DBENGINE "dbEngine"
#define RCES_PUBLICATION_DBENGINEDETAIL "dbEngineDetail"
#define RCES_PUBLICATION_NAME "name"
#define RCES_PUBLICATION_DESCRIPTION "description"
#define RCES_PUBLICATION_TOTAL "total"
#define RCES_PUBLICATION_FILELIST "fileList"
#define RCES_PUBLICATION_FILEGROUPLIST "fileGroupList"
#define RCES_PUBLICATION_FILE_ID "id"
#define RCES_PUBLICATION_FILEGROUP "fileGroup"
#define RCES_PUBLICATION_PARTIAL "partial"
#define RCES_PUBLICATION_DATABASE "database"
#define RCES_PUBLICATION_RECURSIVE "recursive"
#define RCES_FILE_ID "id"
#define RCES_FILEGROUP_ID "id"
#define RCES_PUBLICATION_RULES "rules"
#define RCES_PUBLICATION_TYPE "type"

/*^****************************************************************************\
*
*   RCESPublication
*   Recon-e-Sense Publication class
*
\******************************************************************************/
class RCESPublication
{
public:
	/* Constructors & destructor */
	RCESPublication();
	RCESPublication(pRCESPublication publication);
	RCESPublication(pRCESJson publication);
	virtual ~RCESPublication();

	/* Public services */
	static int ctGetPublications(pRCESMasterProvider masterProv, int dbEngine, int publicationListSize, int publicationStart, ppRCESPublication *publicationList, int *publicationCount, int *totalPublications);
	static int ctGetPublications(pRCESMasterProvider masterProv, int dbEngine, bool isPaging, int publicationListSize, int publicationStart, ppRCESJson result);
	static int ctGetPublicationsByName(pRCESMasterProvider masterProv, int dbEngine, const char *name, bool partial, int publicationListSize, int publicationStart, ppRCESPublication *publicationList, int *publicationCount, int *totalPublications);
	static int ctGetPublicationsByName(pRCESMasterProvider masterProv, int dbEngine, const char *name, bool partial, bool isPaging, int publicationListSize, int publicationStart, ppRCESJson result);
	static int ctGetPublicationsByDatabase(pRCESMasterProvider masterProv, int databaseID, ppRCESPublication *publicationList, int *publicationCount);
	static int ctGetPublication(pRCESMasterProvider masterProv, int publicationID, ppRCESPublication publication);
	static int ctGetPublication(pRCESMasterProvider masterProv, int publicationID, bool isPaging, ppRCESJson result);
	static int ctPersistPublication(pRCESMasterProvider masterProv, pRCESPublication publication);
	static int ctPersistPublication(pRCESMasterProvider masterProv, pRCESJson publication, ppRCESJson result);
	static int ctRemovePublication(pRCESMasterProvider masterProv, int publicationID, bool recursive);
	static int ctRemovePublication(pRCESMasterProvider masterProv, int publicationID, bool recursive, ppRCESJson result);
	static int ctGetFilesFromPublication(pRCESMasterProvider masterProv, pRCESPublication publication, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles);
	static int ctGetRulesFromPublication(pRCESMasterProvider masterProv, pRCESPublication publication, int ruleListSize, int ruleStart, ppRCESRule *ruleList, int *ruleCount, int *totalRules);
	static int ctGetRulesFromPublication(pRCESMasterProvider masterProv, pRCESPublication publication, bool isPaging, int ruleListSize, int ruleStart, ppRCESJson result);
	static int ctGetRulesFromPublication(pRCESMasterProvider masterProv, int publicationID, bool isPaging, int ruleListSize, int ruleStart, ppRCESJson result);
	static int ctAddFilesToPublication(pRCESMasterProvider masterProv, int publicationID, int *fileIDList, int fileCount);
	static int ctAddFilesToPublication(pRCESMasterProvider masterProv, int publicationID, int *fileIDList, int fileCount, ppRCESJson result);
	static int ctRemoveFilesFromPublication(pRCESMasterProvider masterProv, int publicationID, int *fileIDList, int fileCount);
	static int ctRemoveFilesFromPublication(pRCESMasterProvider masterProv, int publicationID, int *fileIDList, int fileCount, ppRCESJson result);
	static int ctGetFileGroupsFromPublication(pRCESMasterProvider masterProv, int publicationID, int fileGroupListSize, int fileGroupStart, ppRCESFileGroup *fileGroupList, int *fileGroupCount, int *totalFileGroups);
	static int ctGetFileGroupsFromPublication(pRCESMasterProvider masterProv, int publicationID, bool isPaging, int fileGroupListSize, int fileGroupStart, ppRCESJson result);
	static int ctAddFileGroupsToPublication(pRCESMasterProvider masterProv, int publicationID, int *fileGroupIDList, int fileGroupCount);
	static int ctAddFileGroupsToPublication(pRCESMasterProvider masterProv, int publicationID, int *fileGroupIDList, int fileGroupCount, ppRCESJson result);
	static int ctRemoveFileGroupsFromPublication(pRCESMasterProvider masterProv, int publicationID, int *fileGroupIDList, int fileGroupCount);
	static int ctRemoveFileGroupsFromPublication(pRCESMasterProvider masterProv, int publicationID, int *fileGroupIDList, int fileGroupCount, ppRCESJson result);
	static int ctGetTempPubName(pRCESMasterProvider masterProv, char *tempPubName);
	static int ctGetTempPubName(pRCESMasterProvider masterProv, ppRCESJson result);
	static int ctCheckPublication(pRCESMasterProvider masterProv, pRCESPublication publication, pRCESReplPlan replPlan, ppRCESPublication newPublication);
	static const char *ctGetPublicationModeStr(RCESPublicationMode mode);

	/* Public methods */
	int GetID() { return _id; };
	int GetDBEngineID() { return _dbEngineID; };
	pRCESDBEngine GetDBEngine() { return _dbEngine; };
	int GetDatabaseID() { return _databaseID; };
	pRCESDatabase GetDatabase() { return _database; };
	const char *GetName() { return _name; };
	const char *GetDescription() { return _description; };
	bool IsByDatabase() { return false; };
	RCESPublicationMode GetMode() { return _mode; };
	bool IsPathCaseSensitive() { return _pathCaseSensitive; };

	void SetID(int id) { _id = id; };
	void SetDBEngineID(int dbEngineID) { _dbEngineID = dbEngineID; };
	void SetDBEngine(pRCESDBEngine dbEngine) { _dbEngine = dbEngine; };
	void SetDatabaseID(int databaseID) { _databaseID = databaseID; };
	void SetDatabase(pRCESDatabase database) { _database = database; };
	void SetName(const char *name);
	void SetDescription(const char *description);
	void SetMode(RCESPublicationMode mode) { _mode = mode; };
	void SetPathCaseSensitive(bool pathCaseSensitive) { _pathCaseSensitive = pathCaseSensitive; };

	pRCESJson GetJson(bool details, pRCESMasterProvider provider = NULL);
	void Update(pRCESJson hardwarePatch);

private:
	/* Private properties */
	int _id;
	int _dbEngineID;
	pRCESDBEngine _dbEngine;
	int _databaseID;
	pRCESDatabase _database;
	char *_name;
	char *_description;
	RCESPublicationMode _mode;
	bool _pathCaseSensitive;

	void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESPUBLICATION_HPP_ */