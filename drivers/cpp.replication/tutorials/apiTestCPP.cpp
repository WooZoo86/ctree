/*
*      OFFICIAL NOTIFICATION: the following CONFIDENTIAL and PROPRIETARY
*  property legend shall not be removed from this source code module
*  for any reason.
*
*  This program is the CONFIDENTIAL and PROPRIETARY property
*  of FairCom(R) Corporation. Any unauthorized use, reproduction or
*  transfer of this computer program is strictly prohibited. The
*      contents of this file may not be disclosed to third parties, copied or
*      duplicated in any form, in whole or in part, without the prior written
*      permission of the FairCom(R) Corporation.
*
*      Copyright (c) 2013 - 2015 FairCom Corporation.
*  This is an unpublished work, and is subject to limited distribution and
*  restricted disclosure only. ALL RIGHTS RESERVED.
*
*      RESTRICTED RIGHTS LEGEND
*  Use, duplication, or disclosure by the Government is subject to
*  restrictions set forth in subparagraph (c)(1)(ii) of the Rights in
*  Technical Data and Computer Software clause at DFARS 252.227-7013, and/or
*      in similar or successor clauses in the FAR, DOD or NASA FAR Supplement.
*      Unpublished rights reserved under the Copyright Laws of the United States.
*  FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203.
*
*/

#include "fcRepl.h"

#define MAX_HOST_LEN 255
#define MAX_PATH_LEN 260

char memphisHost[MAX_HOST_LEN+1];
char memphisServerName[MAX_HOST_LEN+1];
char memphisSQLPort[8];
char memphisDatabase[MAX_HOST_LEN+1];

/* Forward function declaration */
void DisplayUsage();
void RetrieveParms(int argc, const char *argv[]);

pFCREPLDBEngine GetDBEngine(pFCREPLConn replConn);
pFCREPLReplPlan GetReplPlan(pFCREPLConn replConn, pFCREPLDBEngine sourceDBEngine, pFCREPLDBEngine targetDBEngine);
pFCREPLPublication GetPublication(pFCREPLConn replConn, pFCREPLDBEngine sourceDBEngine, const char *sourceDataPath);
pFCREPLSubscription GetSubscription(pFCREPLConn replConn, pFCREPLDBEngine targetDBEngine, const char *targetDataPath, pFCREPLPublication publication, const char *sourcePath, pFCREPLReplPlan replPlan);
void fcSleep(int milliseconds);


/*^****************************************************************************\
*
*   Method:     main
*               Main function for the C++ high level API example for Replication
*               Studio.
*
*   Parameters: argc [IN]
*               Number of input parameters
*
*               argv [IN]
*               List of input parameters
*
\******************************************************************************/
int main(int argc, const char *argv[])
{
	int retval;
	char *errorMsg = NULL;
	pFCREPLConn replConn = NULL;
	char sourcePath[MAX_PATH_LEN + 1], targetPath[MAX_PATH_LEN + 1];
	pFCREPLDBEngine sourceDBEngine = NULL, targetDBEngine = NULL;
	pFCREPLPublication publication = NULL;
	pFCREPLSubscription subscription = NULL;
	pFCREPLReplPlan replPlan = NULL;
	pFCREPLAction deployAction = NULL;
	bool deployCompleted = 0;

	/* Retrieve input parameters */
	RetrieveParms(argc, argv);

	printf("\n Faircom Replication Test Application\n");
	printf(" ====================================\n\n");
	
	/* Connect to Memphis server */
	if ((retval = fcReplConnect(memphisHost, memphisServerName, memphisSQLPort, memphisDatabase, "ADMIN", "ADMIN", &replConn, &errorMsg)) != FCREPL_SUCCESS) {
		printf("ERROR - Not able to connect to Memphis server - %d - %s\n\n", retval, errorMsg);
		FCREPLFree(errorMsg);
		goto EXIT;
	}

	printf("INFO - Connected to Memphis server\n");

	/* Retrieve the source DBEngine */
	printf("\nPlease select SOURCE DBEngine:\n");
	if (!(sourceDBEngine = GetDBEngine(replConn))) {
		printf("ERROR - Not able to retrieve SOURCE DBEngine\n\n");
		goto EXIT;
	}

	/* Retrieve the publication, it will be created if missing */
	printf("\nPlease enter the SOURCE data directory: ");
	scanf("%255s", sourcePath);
	if (!(publication = GetPublication(replConn, sourceDBEngine, sourcePath))) {
		printf("ERROR - Not able to retrieve PUBLICATION\n\n");
		goto EXIT;
	}

	/* Retrieve the target DBEngine */
	printf("\nPlease select TARGET DBEngine:\n");
	if (!(targetDBEngine = GetDBEngine(replConn))) {
		printf("ERROR - Not able to retrieve TARGET DBEngine\n\n");
		goto EXIT;
	}

	/* Retrieve Replication Plan, it will be created if missing */
	if (!(replPlan = GetReplPlan(replConn, sourceDBEngine, targetDBEngine))) {
		printf("ERROR - Not able to retrieve REPLICATION PLAN\n\n");
		goto EXIT;
	}

	/* Retrieve the subscription */
	printf("\nPlease enter the TARGET data directory: ");
	scanf("%255s", targetPath);
	if (!(subscription = GetSubscription(replConn, targetDBEngine, targetPath, publication, sourcePath, replPlan))) {
		printf("ERROR - Not able to retrieve SUBSCRIPTION\n\n");
		goto EXIT;
	}

	/* Deploy Replication Plan */
	int deployActionID;
	if ((retval = fcReplDeploy(replConn, replPlan->GetID(), 1, &deployActionID)) != FCREPL_SUCCESS) {
		printf("ERROR - Not able to deploy Replication Plan - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
		goto EXIT;
	}
	printf("\nINFO - Replication Plan deployment started...\n");

	/* Check Replication Plan deployment action progress */
	while (!deployCompleted) {
		if ((retval = fcReplCheckAction(replConn, deployActionID, 1, &deployAction)) != FCREPL_SUCCESS) {
			printf("ERROR - Not able to check Replication Plan deployment action - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
			goto EXIT;
		}

		/* Check if deployment action failed */
		if (deployAction->GetErrorCode() != FCREPL_SUCCESS) {
			printf("ERROR - Not able to check Replication Plan deployment action - %d - %s\n\n", retval, deployAction->GetErrorMessage());
			delete deployAction;
			goto EXIT;
		}

		/* Check if deployment action is completed */
		if (deployAction->GetProgress() == 100)
			deployCompleted = 1;
		else
			fcSleep(2000);

		delete deployAction;
	}
	printf("\nINFO - Replication Plan deployment completed...\n");
	

EXIT:
	/* Delete objects */
	if (replPlan)
		delete replPlan;
	if (subscription)
		delete subscription;
	if (publication)
		delete publication;
	if (sourceDBEngine)
		delete sourceDBEngine;
	if (targetDBEngine)
		delete targetDBEngine;

	/* Disconnect from Memphis server */
	if (replConn) {
		if ((retval = fcReplDisconnect(replConn)) != FCREPL_SUCCESS)
			printf("ERROR - Not able to disconnect from Memphis server - %d\n\n", retval);
		else
			printf("\nINFO - Disconnected from Memphis server\n");
	}

	printf("Press any key to exit...");
	getchar();
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     GetDBEngine
*               List all the available DBEngines and load the one selected by
*               the user
*
*   Parameters: replConn [IN]
*               Replication connection
*
*   Return:     DBEngine entity object
*
\******************************************************************************/
pFCREPLDBEngine GetDBEngine(pFCREPLConn replConn)
{
	int retval;
	ppFCREPLDBEngine dbEngineList = NULL;
	pFCREPLDBEngine dbEngine = NULL;
	int dbEngineCount = 0;
	int selDBEngineIdx;

	/* Retrieve the list of DBEngines */
	if ((retval = fcReplGetDBEngines(replConn, -1, &dbEngineList, &dbEngineCount)) != FCREPL_SUCCESS) {
		printf("ERROR - Not able to retrieve list of DBEngines - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
		goto EXIT;
	}
	if (!dbEngineCount) {
		printf("ERROR - Not able to find any DBEngine. Please make sure at least one c-treeACE server and set to connect to Memphis server. Check ctagent.json configuration file.\n\n");
		goto EXIT;
	}

	/* If only returned one DBEngine, assume it is the one */
	if (dbEngineCount == 1) {
		printf("\nINFO - DBEngine select from [%s%c%s]\n", dbEngineList[0]->GetWorkingVolumeName(), SEP, dbEngineList[0]->GetWorkingDir());
		dbEngine = dbEngineList[0];
		goto EXIT;
	}

	/* If multiple DBEngines found on the given host, list all options */
	printf("\nINFO - Multiple DBEngines [%d] found. Please select one from the list:\n", dbEngineCount);
	for (int i = 0; i < dbEngineCount; i++)
		printf("   %d - %s (%s%c%s)\n", i+1, dbEngineList[i]->GetName(), dbEngineList[i]->GetWorkingVolumeName(), SEP, dbEngineList[i]->GetWorkingDir());

	/* Retrieve the user selected one */
	printf("Please select one: ");
	while (1) {
		scanf("%d", &selDBEngineIdx);
		if(selDBEngineIdx <= 0 || selDBEngineIdx > dbEngineCount)
			printf("ERROR - Please select one option between 1 and %d\n", dbEngineCount);
		else {
			if (!dbEngineList[selDBEngineIdx - 1]) {
				printf("ERROR - Internal error, invalid DBEngine object in position [%d]\n", selDBEngineIdx - 1);
				goto EXIT;
			}

			dbEngine = dbEngineList[selDBEngineIdx - 1];
			goto EXIT;
		}
	}

EXIT:
	/* Release allocated object */
	if (dbEngineList) {
		for (int i = 0; i < dbEngineCount; i++) {
			if (dbEngineList[i] && dbEngine != dbEngineList[i])
				delete dbEngineList[i];
		}
		FCREPLFree(dbEngineList);
	}

	return dbEngine;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     GetReplPlan
*               Create or retrieve a replication plan for the provided
*               publication and subscription.
*
*   Parameters: replConn [IN]
*               Replication connection
*
*               sourceDBEngine [IN]
*               Source DBEngine entity object
*
*               targetDBEngine [IN]
*               Target DBEngine entity object
*
*   Return:     Replication Plan entity object
*
\******************************************************************************/
pFCREPLReplPlan GetReplPlan(pFCREPLConn replConn, pFCREPLDBEngine sourceDBEngine, pFCREPLDBEngine targetDBEngine)
{
	int retval;

	ppFCREPLReplPlan replPlanList = NULL;
	int replPlanCount;
	pFCREPLReplPlan replPlan = NULL;

RETRY:
	/* Check Replication Plan entity object */
	if ((retval = fcReplGetReplPlans(replConn, &replPlanList, &replPlanCount)) != FCREPL_SUCCESS) {
		printf("ERROR - Not able to retrieve REPLICATION PLAN - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
		goto EXIT;
	}

	for (int i = 0; i < replPlanCount; i++) {
		if (!strcmp(replPlanList[i]->GetName(), "ReplPlan_Test")) {
			replPlan = replPlanList[i];
			break;
		}
	}

	/* If Replication Plan not found, create and persist it */
	if (!replPlan) {
		replPlan = new FCREPLReplPlan();

		replPlan->SetName("ReplPlan_Test");
		replPlan->SetDescription("Replication Plan test description");
		replPlan->SetSourceDBEngineID(sourceDBEngine->GetID());
		replPlan->SetTargetDBEngineID(targetDBEngine->GetID());

		/* Persist new Replication Plan into Memphis */
		if ((retval = fcReplPersistReplPlan(replConn, replPlan)) != FCREPL_SUCCESS) {
			printf("ERROR - Not able to persist REPLICATION PLAN - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
			goto EXIT;
		}

		delete replPlan;
		replPlan = NULL;

		goto RETRY;
	}

EXIT:
	if (replPlanList)
		FCREPLFree(replPlanList);

	if (retval != FCREPL_SUCCESS) {
		if (replPlan) {
			delete replPlan;
			replPlan = NULL;
		}
	}

	return replPlan;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     GetPublication
*               Create or retrieve a publication for the provided source 
*               DBEngine with all the c-tree data files in the provided source
*               data directory.
*
*   Parameters: replConn [IN]
*               Replication connection
*
*               sourceDBEngine [IN]
*               Source DBEngine
*
*               sourceDataPath [IN]
*               Source data path
*
*   Return:     Publication entity object
*
\******************************************************************************/
pFCREPLPublication GetPublication(pFCREPLConn replConn, pFCREPLDBEngine sourceDBEngine, const char *sourceDataPath)
{
	int retval;

	int *fileIDList = NULL;
	ppFCREPLPublication publicationList = NULL;
	int publicationCount, totalPublications;
	pFCREPLPublication publication;
	ppFCREPLFile fileList;
	int fileCount, totalFiles, ctFileCount = 0;
	const char *dataPathNoVolume = NULL;

	/* Retrieve the volume identification for the provided sourceDataPath */
	pFCREPLVolume volume = NULL;
	char volumeName[3];
#ifdef _WINDOWS
	strncpy(volumeName, sourceDataPath, 2);
	volumeName[2] = 0;
	volumeName[0] = toupper(volumeName[0]);
#else
	volumeName[0] = 0;
#endif
	if ((retval = fcReplGetVolume(replConn, sourceDBEngine->GetOSID(), volumeName, &volume)) != FCREPL_SUCCESS) {
		printf("ERROR - Not able to find Volume by name [%s] in opSystemID [%d] - %d - %s\n\n", volumeName, sourceDBEngine->GetOSID(), retval, replConn->GetDataProvider()->GetErrorMsg());
		goto EXIT;
	}

#ifdef _WINDOWS
	dataPathNoVolume = &sourceDataPath[3];
#else
	dataPathNoVolume = &sourceDataPath[1];
#endif

	/* Check Publication entity object */
RETRY:
	if ((retval = fcReplGetPublicationsByName(replConn, sourceDBEngine->GetID(), "Publication_Test", 0, 1, -1, &publicationList, &publicationCount, &totalPublications )) != FCREPL_SUCCESS || publicationCount == 0) {
		if (retval == FCREPL_NOTFOUND || publicationCount == 0) {
			publication = new FCREPLPublication();

			publication->SetName("Publication_Test");
			publication->SetDescription("Publication test description");
			publication->SetDBEngineID(sourceDBEngine->GetID());

			/* Persist new Publication into Memphis */
			if ((retval = fcReplPersistPublication(replConn, publication)) != FCREPL_SUCCESS) {
				printf("ERROR - Not able to persist PUBLICATION - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
				goto EXIT;
			}

			delete publication;
			publication = NULL;

			goto RETRY;
		}
		else {
			printf("ERROR - Not able to retrieve PUBLICATION - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
			goto EXIT;
		}
	}
	else {
		publication = publicationList[0];
		FCREPLFree(publicationList);
	}

	/* Load all the c-tree data files from source data path into Memphis */
	printf("\nINFO - Please wait while the files from the given path are loaded.\n");
	if ((retval = fcReplGetFiles(replConn, volume->GetID(), dataPathNoVolume, "*.dat", 0, 0, -1, 1, 1, -1, -1, &fileList, &fileCount, &totalFiles)) != FCREPL_SUCCESS) {
		printf("ERROR - Not able to retrieve list of files to be published - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
		goto EXIT;
	}
	else if (fileCount > 0) {
		/* Allocate the file ID list */
		fileIDList = (int *)FCREPLAlloc(sizeof(int) * fileCount);

		/* Show all the files being published - only the ones that qualifies for c-tree replication */
		printf("\nINFO - List of files being published:\n");
		for (int i = 0; i < fileCount; i++) {
			if (fileList[i]->GetType() == FCREPL_CTREP_QUALIF) {
				fileIDList[ctFileCount++] = fileList[i]->GetID();
				printf("   %s\n", fileList[i]->GetName());
			}
		}
	}

	/* Check if there is at least one c-tree file that qualifies for Replication */
	if (!ctFileCount) {
		retval = FCREPL_NOTFOUND;
		printf("ERROR - Not found any c-tree data file on the provided path. Please make sure you have at least one c-tree file with extension of .dat in TRNLOG mode and at least one unique index.\n\n");
		goto EXIT;
	}

	/* Add the file list into the Publication */
	if ((retval = fcReplAddFilesToPublication(replConn, publication->GetID(), fileIDList, ctFileCount)) != FCREPL_SUCCESS)
		printf("ERROR - Not able to add the list of files into the PUBLICATION - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());

EXIT:
	if (fileIDList)
		FCREPLFree(fileIDList);
	if (volume)
		delete volume;

	if (retval != FCREPL_SUCCESS) {
		if (publication) {
			delete publication;
			publication = NULL;
		}
	}

	return publication;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     GetSubscription
*               Create or retrieve a subscription for the provided target
*               DBEngine and target data directory.
*
*   Parameters: replConn [IN]
*               Replication connection
*
*               targetDBEngine [IN]
*               Target DBEngine
*
*               targetDataPath [IN]
*               Target data path
*
*               publication [IN]
*               Publication entity object
*
*               sourcePath [IN]
*               Source path
*
*               replPlan [IN]
*               Replication Plan entity object
*
*   Return:     Subscription entity object
*
\******************************************************************************/
pFCREPLSubscription GetSubscription(pFCREPLConn replConn, pFCREPLDBEngine targetDBEngine, const char *targetDataPath, pFCREPLPublication publication, const char *sourcePath, pFCREPLReplPlan replPlan)
{
	int retval;

	ppFCREPLSubscription subscriptionList = NULL;
	int subscriptionCount, totalSubscriptions;
	pFCREPLSubscription subscription;
	const char *dataPathNoVolume = NULL;

	/* Retrieve the volume identification for the provided targetDataPath */
	pFCREPLVolume volume = NULL;
	char volumeName[3];
#ifdef _WINDOWS
	strncpy(volumeName, targetDataPath, 2);
	volumeName[2] = 0;
	volumeName[0] = toupper(volumeName[0]);
#else
	volumeName[0] = 0;
#endif
	if ((retval = fcReplGetVolume(replConn, targetDBEngine->GetOSID(), volumeName, &volume)) != FCREPL_SUCCESS) {
		printf("ERROR - Not able to find Volume by name [%s] in opSystemID [%d] - %d - %s\n\n", volumeName, targetDBEngine->GetOSID(), retval, replConn->GetDataProvider()->GetErrorMsg());
		goto EXIT;
	}

#ifdef _WINDOWS
	dataPathNoVolume = &targetDataPath[3];
#else
	dataPathNoVolume = &targetDataPath[1];
#endif

	/* Check Subscription entity object */
RETRY:
	if ((retval = fcReplGetSubscriptionsByName(replConn, publication->GetID(), targetDBEngine->GetID(), "Subscription_Test", 0, 1, -1, &subscriptionList, &subscriptionCount, &totalSubscriptions)) != FCREPL_SUCCESS || subscriptionCount == 0) {
		if (retval == FCREPL_NOTFOUND || subscriptionCount == 0) {
			subscription = new FCREPLSubscription();

			subscription->SetName("Subscription_Test");
			subscription->SetDescription("Subscription test description");
			subscription->SetDBEngineID(targetDBEngine->GetID());
			subscription->SetPublicationID(publication->GetID());
			subscription->SetReplPlanID(replPlan->GetID());

			/* Set redirection rule based on the provided source and target paths */
			ppFCREPLReplRedir redirList = (ppFCREPLReplRedir)FCREPLAlloc(sizeof(pFCREPLReplRedir));
			if (redirList) {
				redirList[0] = new FCREPLReplRedir();
				redirList[0]->SetSource(sourcePath);
				redirList[0]->SetTarget(targetDataPath);

				subscription->SetRedirList(redirList, 1);
			}

			/* Persist new Subscription into Memphis */
			if ((retval = fcReplPersistSubscription(replConn, subscription)) != FCREPL_SUCCESS) {
				printf("ERROR - Not able to persist SUBSCRIPTION - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
				goto EXIT;
			}

			delete subscription;
			subscription = NULL;

			goto RETRY;
		}
		else {
			printf("ERROR - Not able to retrieve SUBSCRIPTION - %d - %s\n\n", retval, replConn->GetDataProvider()->GetErrorMsg());
			goto EXIT;
		}
	}
	else {
		subscription = subscriptionList[0];
		FCREPLFree(subscriptionList);
	}

EXIT:
	if (volume)
		delete volume;

	if (retval != FCREPL_SUCCESS) {
		if (subscription) {
			delete subscription;
			subscription = NULL;
		}
	}

	return subscription;
}
/*~****************************************************************************/



/*^****************************************************************************\
*
*   Method:     DisplayUsage
*               Display the usage of the test application
*
\******************************************************************************/
void DisplayUsage()
{
	printf("\n Faircom Replication Test Application\n");
	printf(" ====================================\n\n");
	printf("USAGE:\n");
	printf(" apiTestCPP -h<Memphis host> -n<Memphis server name> -p<Memphis SQL port> -d<Memphis Database Name>\n");
	printf("    -h<Memphis host> - Memphis server host (name or IP address) - default is <localhost>\n");
	printf("    -n<Memphis server name> - Memphis server name - default is <MEMPHIS>\n");
	printf("    -p<Memphis SQL port> - Memphis server SQL port - default is <7000>\n");
	printf("    -d<Memphis Database Name> - Memphis database name - default is <MEMPHIS>\n\n");

	printf("Press any key to exit...");
	getchar();
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     RetrieveParms
*               Retrieve input parameters
*
*   Parameters: argc [IN]
*               Number of input parameters
*
*               argv [IN]
*               List of input parameters
*
\******************************************************************************/
void RetrieveParms(int argc, const char *argv[])
{
	/* Set the default values */
	strcpy(memphisHost, "localhost");
	strcpy(memphisServerName, "MEMPHIS");
	strcpy(memphisSQLPort, "7000");
	strcpy(memphisDatabase, "MEMPHIS");

	/* Retrieve the input parameters */
	for (int i = 1; i < argc; i++)
	{
		/* Check if the full scan option is passed as parameter */
		if (!strcmp(argv[i], "?") || strcmp(argv[i], "help"))
			DisplayUsage();

		/* Check if it is passed the path/mask for the initial scan */
		else if (!strncmp(argv[i], "-h", 2))
			strncpy(memphisHost, &argv[i][2], MAX_HOST_LEN);
		else if (!strncmp(argv[i], "-n", 2))
			strncpy(memphisServerName, &argv[i][2], MAX_HOST_LEN);
		else if (!strncmp(argv[i], "-p", 2))
			strncpy(memphisSQLPort, &argv[i][2], 7);
		else if (!strncmp(argv[i], "-d", 2))
			strncpy(memphisDatabase, &argv[i][2], MAX_HOST_LEN);
	}
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     fcSleep
*               fcSleep a number of milliseconds.
*
*   Parameters: milliseconds [IN]
*               Time to sleep
*
\******************************************************************************/
void fcSleep(int milliseconds)
{
#ifdef _WINDOWS
	Sleep(milliseconds);
#else
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
#endif
}
/*~****************************************************************************/