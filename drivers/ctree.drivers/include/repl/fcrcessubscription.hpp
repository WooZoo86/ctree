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

#ifndef _FCRCESSUBSCRIPTION_HPP_
#define _FCRCESSUBSCRIPTION_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESSubscription;
class RCESMasterProvider;
typedef RCESSubscription *pRCESSubscription, **ppRCESSubscription;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_SUBSCRIPTION_LIST "subscriptionList"
#define RCES_SUBSCRIPTION "subscription"
#define RCES_SUBSCRIPTION_ID "id"
#define RCES_SUBSCRIPTION_PUBLICATION "publication"
#define RCES_SUBSCRIPTION_PUBLICATIONDETAIL "publicationDetail"
#define RCES_SUBSCRIPTION_DBENGINE "dbEngine"
#define RCES_SUBSCRIPTION_DBENGINEDETAIL "dbEngineDetail"
#define RCES_SUBSCRIPTION_NAME "name"
#define RCES_SUBSCRIPTION_DESCRIPTION "description"
#define RCES_SUBSCRIPTION_TOTAL "total"
#define RCES_SUBSCRIPTION_PARTIAL "partial"
#define RCES_SUBSCRIPTION_DATABASE "database"
#define RCES_SUBSCRIPTION_ISBIDIRECTIONAL "isBiDirectional"
#define RCES_SUBSCRIPTION_REPLPLAN "replPlan"
#define RCES_SUBSCRIPTION_FILEPREVIEWLIST "fileListPreview"
#define RCES_SUBSCRIPTION_REDIRLIST "redirectionList"

/*^****************************************************************************\
*
*   RCESSubscription
*   Recon-e-Sense Subscription class
*
\******************************************************************************/
class RCESSubscription
{
public:
	/* Constructors & destructor */
	RCESSubscription();
	RCESSubscription(pRCESSubscription subscription);
	RCESSubscription(pRCESJson subscription);
	virtual ~RCESSubscription();

	/* Public services */
	static int ctGetSubscriptions(pRCESMasterProvider masterProv, int publication, int dbEngine, int subscriptionListSize, int subscriptionStart, ppRCESSubscription *subscriptionList, int *subscriptionCount, int *totalSubscriptions);
	static int ctGetSubscriptions(pRCESMasterProvider masterProv, int publication, int dbEngine, bool isPaging, int subscriptionListSize, int subscriptionStart, ppRCESJson result);
	static int ctGetSubscriptions(pRCESMasterProvider masterProv, int replPlanID, int replSubsListSize, int replSubsStart, ppRCESSubscription *subsList, int *subsCount, int *totalReplSubs);
	static int ctGetSubscriptions(pRCESMasterProvider masterProv, int replPlanID, bool isPaging, int replSubsListSize, int replSubsStart, ppRCESJson result);
	static int ctGetSubscriptionsByName(pRCESMasterProvider masterProv, int publication, int dbEngine, const char *name, bool partial, int subscriptionListSize, int subscriptionStart, ppRCESSubscription *subscriptionList, int *subscriptionCount,
		int *totalSubscriptions);
	static int ctGetSubscriptionsByName(pRCESMasterProvider masterProv, int publication, int dbEngine, const char *name, bool partial, bool isPaging, int subscriptionListSize, int subscriptionStart, ppRCESJson result);
	static int ctGetSubscription(pRCESMasterProvider masterProv, int subscriptionID, ppRCESSubscription subscription);
	static int ctGetSubscription(pRCESMasterProvider masterProv, int subscriptionID, bool isPaging, ppRCESJson result);
	static int ctPersistSubscription(pRCESMasterProvider masterProv, pRCESSubscription subscription);
	static int ctPersistSubscription(pRCESMasterProvider masterProv, pRCESJson subscription, ppRCESJson result);
	static int ctRemoveSubscription(pRCESMasterProvider masterProv, int subscriptionID);
	static int ctRemoveSubscription(pRCESMasterProvider masterProv, int subscriptionID, ppRCESJson result);
	static int ctGetSubsFilesPreview(pRCESMasterProvider masterProv, pRCESPublication publication, ppRCESFile sourceFileList, int sourceFileCount, ppRCESVolume targetVolumeList, int targetVolumeCount, ppRCESReplRedir redirList, int redirListCount, ppRCESFile *fileList, int *fileCount);
	static int ctSubsFilesPreview(pRCESMasterProvider masterProv, int publicationID, ppRCESReplRedir redirList, int redirListCount, int dbEngineID, int databaseID, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles);
	static int ctSubsFilesPreview(pRCESMasterProvider masterProv, int publicationID, ppRCESReplRedir redirList, int redirListCount, int dbEngineID, int databaseID, bool isPaging, int fileListSize, int fileStart, ppRCESJson result);
	static int ctGetTempSubsName(pRCESMasterProvider masterProv, char *tempSubsName);
	static int ctGetTempSubsName(pRCESMasterProvider masterProv, ppRCESJson result);

	static void GetTargetPathByRules(const char *sourceFullPath, bool isSourceOSCaseSensitive, ppRCESReplRedir redirList, int redirListCount, char *calcTargetPath);

	/* Public methods */
	int GetID() { return _id; };
	int GetPublicationID() { return _publicationID; };
	pRCESPublication GetPublication() { return _publication; };
	int GetDBEngineID() { return _dbEngineID; };
	pRCESDBEngine GetDBEngine() { return _dbEngine; };
	int GetDatabaseID() { return _databaseID; };
	pRCESDatabase GetDatabase() { return _database; };
	const char *GetName() { return _name; };
	const char *GetDescription() { return _description; };
	bool GetIsBiDir() { return _isBiDir; };
	int GetReplPlanID() { return _replPlanID; };
	ppRCESReplRedir GetRedirList() { return _redirList; };
	int GetRedirListCount() { return _redirListCount; };

	void SetID(int id) { _id = id; };
	void SetPublicationID(int publicationID) { _publicationID = publicationID; };
	void SetPublication(pRCESPublication publication) { _publication = publication; };
	void SetDBEngineID(int dbEngineID) { _dbEngineID = dbEngineID; };
	void SetDBEngine(pRCESDBEngine dbEngine) { _dbEngine = dbEngine; };
	void SetDatabaseID(int databaseID) { _databaseID = databaseID; };
	void SetDatabase(pRCESDatabase database) { _database = database; };
	void SetName(const char *name);
	void SetDescription(const char *description);
	void SetIsBiDir(bool isBiDir) { _isBiDir = isBiDir; };
	void SetReplPlanID(int replPlanID) { _replPlanID = replPlanID; };
	void SetRedirList(ppRCESReplRedir redirList, int redirListCount) { _redirList = redirList; _redirListCount = redirListCount; };

	pRCESJson GetJson(bool details, pRCESMasterProvider provider = NULL);
	void Update(pRCESJson subscriptionPatch);
	void GetTargetPath(const char *sourcePath, bool isSourceCaseSensitive, char *targetPath);

protected:
	/* Private properties */
	int _id;
	int _publicationID;
	pRCESPublication _publication;
	int _dbEngineID;
	pRCESDBEngine _dbEngine;
	int _databaseID;
	pRCESDatabase _database;
	char *_name;
	char *_description;
	bool _isBiDir;
	int _replPlanID;
	ppRCESReplRedir _redirList;
	int _redirListCount;

	/* Private methods */
	void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESSUBSCRIPTION_HPP_ */