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

#ifndef _FCRCESDATAPROV_HPP_
#define _FCRCESDATAPROV_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrceslogger.hpp"
#include "fcrcesaction.hpp"
#include "fcrcesreplplan.hpp"
#include "fchashtable.hpp"
#include "fcrcesrecblock.hpp"
#include "fcrcesfile.hpp"
#include "fcrcesdatabase.hpp"
#include "fccache.hpp"
#include "fcrcesreplfile.hpp"

/* Class type definitions */
class RCESSite;
class RCESHardware;
class RCESOpSystem;
class RCESVolume;
class RCESPublication;
class RCESSubscription;
class RCESLayout;
class RCESLayoutInfo;
class RCESMac;
class RCESIp;
class RCESReplRedir;
class RCESLog;
class RCESReplAgent;
class RCESAgentConsumer;
typedef RCESSite *pRCESSite, **ppRCESSite;
typedef RCESHardware *pRCESHardware, **ppRCESHardware;
typedef RCESOpSystem *pRCESOpSystem, **ppRCESOpSystem;
typedef RCESVolume *pRCESVolume, **ppRCESVolume;
typedef RCESPublication *pRCESPublication, **ppRCESPublication;
typedef RCESSubscription *pRCESSubscription, **ppRCESSubscription;
typedef RCESLayout *pRCESLayout, **ppRCESLayout;
typedef RCESLayoutInfo *pRCESLayoutInfo, **ppRCESLayoutInfo;
typedef RCESMac *pRCESMac, **ppRCESMac;
typedef RCESIp *pRCESIp, **ppRCESIp;
typedef RCESReplRedir *pRCESReplRedir, **ppRCESReplRedir;
typedef RCESLog *pRCESLog, **ppRCESLog;
typedef RCESReplAgent *pRCESReplAgent, **ppRCESReplAgent;
typedef RCESAgentConsumer *pRCESAgentConsumer, **ppRCESAgentConsumer;

/* API to be provided by the data provider */
int RCESDPConnect(const char *connStr, bool ctdbOnly, void *&conn, char **errorMsg);
int RCESDPDisconnect( void *conn );
bool RCESDPIsActive( void *conn );
int RCESDPAttach(void *conn);
int RCESDPDetach( void *conn );
int RCESDPCommitWork( void *conn );
int RCESDPKill( void *conn, int taskID );
int RCESDPGetThreadOwner();
int RCESDPThreadAttach(bool *attached);
int RCESDPThreadDetach();
void RCESDPDumpCancel(pReplicationDumpData dumpData);

/* File */
int RCESDPGetFiles( void *conn, int volumeID, const char *rootTreePath, const char *mask, bool recursive, int checkReplPlan, 
                    int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles );
int RCESDPGetFiles( void *conn, int databaseID, int checkReplPlan, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, 
                    int *totalFiles );
int RCESDPGetFolders(void *conn, int volumeID, const char *rootTreePath, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles);
int RCESDPGetSubscriptionTargetTables( void *conn, int subscriptionID, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles );
int RCESDPGetSubscriptionTargetFiles(void *conn, int subscriptionID, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles);
int RCESDPGetFile( void *conn, int fileID, ppRCESFile file );
int RCESDPGetFileByName( void *conn, int volumeID, const char *path, const char *name, ppRCESFile file );
int RCESDPAddFile( void *conn, int volumeID, const char *filePath, const char *fileName, RCESDateTime fileCreateDate, 
                   RCESDateTime fileUpdateDate, RCESSize fileSize, bool isDir, bool isPartitioned, int fileType, int databaseID, const char *tableName, 
                   bool isBlockInsert, int *newFileID );
int RCESDPDeleteFile( void *conn, int fileID, bool recursive, bool tree );
int RCESDPRemoveDBFile( void *conn, int fileID );
int RCESDPUpdateFile( void *conn, int fileID, RCESDateTime createFileDate, RCESDateTime updateFileDate, RCESSize fileSize,
                      int databaseID, const char *tableName, int fileType, bool isPartitioned);
RCESFileType RCESDPGetFileType( void *conn, int fileID );
int RCESDPGetFileID( void *conn, int volumeID, const char *filePath, const char *fileName, int *fileID );
int RCESDPReloadSchemas( void *conn, int volumeID );
int RCESDPStartInsBatch( void *conn );
int RCESDPFinishInsBatch( void *conn );
int RCESDPCleanFiles( void *conn, int volumeID );
int RCESDPSetReplicate( void *conn, const char *fileName, int indexCount );
int RCESDPAdjustTargetFileName( void *conn, const char *targetFileName, pRCESReplPlan replPlan, pRCESSubscription subscription, bool isSourceCaseSensitive, int *indexCount );
int RCESDPAddBlockFS( void *conn, pRCESRecBlock recBlock );
int RCESDPCheckPath( void *conn, int volumeID, const char *volumeName, const char *path );
int RCESDPDumpFiles(void *conn, pRCESReplPlan replPlan, ppRCESReplFile replFileList, int fileCount, char *logPos, char *tempPath, int currDBEngineID, int *progress, pReplicationDumpData dumpData);
int RCESDPReplaceFiles(void *conn, pRCESReplPlan replPlan, ppRCESReplFile replFileList, int fileCount, char *tempPath, bool forceReplace, bool isSourceCaseSensitive, int *progress, pReplicationDumpData dumpData, pRCESDBEngineMngr dbEngineMngr);
int RCESDPBlockFile( void *conn, const char *fileName );
int RCESDPUnblockFile( void *conn, const char *fileName );
int RCESDPCheckAgent(void *conn, const char *agentID, bool isParallel);
int RCESDPUpdateReadOnly(void *conn, bool readonly);
int RCESDPUpdateNodeID(void *conn, const char *nodeID);

/* Replication plan */
int RCESDPGetReplPlans( void *conn, int replPlanListSize, int replPlanStart,  ppRCESReplPlan *replPlanList, int *replPlanCount, int *totalReplPlans, bool archived);
int RCESDPGetReplPlan( void *conn, int replPlanID, ppRCESReplPlan replPlan );
int RCESDPGetReplPlanByDBEngine(void *conn, int sourceDBEngineID, int targetDBEngineID, ppRCESReplPlan replPlan);
int RCESDPGetReplPlansByDBEngine(void *conn, int dbEngineID, ppRCESReplPlan *replPlanList, int *replPlanCount);
int RCESDPGetReplPlansByName( void *conn, const char *name, bool partial, int replPlanListSize, int replPlanStart, ppRCESReplPlan *replPlanList, int *replPlanCount, int *totalReplPlans, bool archived);
int RCESDPGetReplPlansByOS( void *conn, int osID, ppRCESReplPlan *replPlanList, int *replPlanCount );
int RCESDPGetReplPlansByPublication(void *conn, int publicationID, ppRCESReplPlan *replPlanList, int *replPlanCount);
int RCESDPPersistReplPlan( void *conn, pRCESReplPlan replPlan );
int RCESDPRemoveReplPlan( void *conn, int replPlanID, bool recursive );
int RCESDPGetReplSubscriptions( void *conn, int replPlanID, int replSubsListSize, int replSubsStart,  ppRCESSubscription *subsList, int *subsCount, int *totalReplSubs );
int RCESDPSetReplPlanStatus( void *conn, int replPlanID, RCESReplStatus status, const char *statusMsg, int actionID, int sourceAgentID, int targetAgentID );
int RCESDPSetReplPlanMonitor( void *conn, int replPlanID, bool isMonitorActive, int refreshRate );
int RCESDPSetReplPlanExcepLog( void *conn, int replPlanID, bool isExcepLogActive );
int RCESDPSetReplPlanFuncTime( void *conn, int replPlanID, bool isFuncTimeActive );
int RCESDPSetReplPlanPause( void *conn, int replPlanID, bool isPaused );
int RCESDPGetReplPlanStatus( void *conn, int replPlanID, RCESReplStatusInfo &statusInfo, char *statusMsg, int *sourceAgentID, int *targetAgentID );
int RCESDPCheckDeployed( void *conn, int replPlanID );
int RCESDPSetDeployed( void *conn, int replPlanID );
int RCESDPUpdateReplSourceLogPos( void *conn, int replPlanID, const char *sourceLogPos, const char *sourceTranID);
int RCESDPUpdateReplTargetLogPos( void *conn, int replPlanID, const char *targetLogPos, const char *targetTranID);
int RCESDPGetReplFileList( void *conn, int replPlanID, int replFileListSize, int replFileStart, ppRCESReplFileList replFileList, int *replFileCount, int *totalReplFiles );
int RCESDPGetReplFiles( void *conn, int replPlanID, int sourceFileID, ppRCESReplFile *replFileList, int *replFileCount );
int RCESDPCheckCircularRepl( void *conn, int replPlanID );
int RCESDPMarkReplPlanDirtyByPublication( void *conn, int publicationID );
int RCESDPMarkReplPlanDirtyByFileGroup( void *conn, int fileGroupID );
int RCESDPSyncReplPlan( void *conn, pRCESReplPlan replPlan );
int RCESDPGetTempReplPlanName( void *conn, char *tempReplPlanName );
int RCESDPSetReplPlanAckExceps(void *conn, int replPlanID);
int RCESDPSetReplPlanNAckFlag(void *conn, int replPlanID, bool nAckFlag);
int RCESDPCheckReplPlanNodes(void *conn, pRCESReplPlan replPlan);
int RCESDPSetReplPlanLatency(void *conn, int replPlanID, RCESReplicationDirection direction, int latency);

/* Replication Plan Redirection */
int RCESDPPersistRedirection( void *conn, pRCESReplRedir replRedir );
int RCESDPCleanRedirection( void *conn, int subsID );
int RCESDPGetRedirectionsByReplPlan( void *conn, int replPlanID, ppRCESReplRedir *redirList, int *redirCount );

/* Site */
int RCESDPGetSites( void *conn, int siteListSize, int siteStart, ppRCESSite *siteList, int *siteCount, int *totalSites );
int RCESDPGetSite( void *conn, int siteID, ppRCESSite site );
int RCESDPGetSite( void *conn, const char *name, ppRCESSite site );
int RCESDPPersistSite( void *conn, pRCESSite site );
int RCESDPRemoveSite( void *conn, int siteID, bool recursive );

/* Hardware */
int RCESDPGetHardwares( void *conn, int siteID, int hardwareListSize, int hardwareStart, ppRCESHardware *hardwareList, 
                        int *hardwareCount, int *totalHardwares );
int RCESDPGetHardware( void *conn, int hardwareID, ppRCESHardware hardware );
int RCESDPGetHardware( void *conn, int siteID, const char *name, ppRCESHardware hardware );
int RCESDPGetHardware( void *conn, const char *mac, ppRCESHardware hardware );
int RCESDPPersistHardware( void *conn, pRCESHardware hardware );
int RCESDPRemoveHardware( void *conn, int hardwareID, bool recursive, bool inTransaction = false);

/* MAC */
int RCESDPGetMacs( void *conn, int hardwareID, int macListSize, int macStart, ppRCESMac *macList, int *macCount, int *totalMacs );
int RCESDPPersistMac( void *conn, pRCESMac mac );
int RCESDPRemoveMac( void *conn, const char *macAddress );

/* OpSystem */
int RCESDPGetOSs( void *conn, int hardwareID, int osListSize, int osStart, ppRCESOpSystem *osList, int *osCount, int *totalOSs );
int RCESDPGetOS( void *conn, int hardwareID, const char *name, ppRCESOpSystem opSystem );
int RCESDPGetOS( void *conn, const char *hostName, ppRCESOpSystem opSystem );
int RCESDPGetOS( void *conn, int osID, ppRCESOpSystem opSystem );
int RCESDPGetOSByIP( void *conn, const char *ipAddress, ppRCESOpSystem opSystem );
int RCESDPPersistOS( void *conn, pRCESOpSystem opSystem );
int RCESDPRemoveOS( void *conn, int osID, bool recursive, bool inTransaction = false );

/* IP */
int RCESDPGetIPs( void *conn, int osID, int ipListSize, int ipStart, ppRCESIp *ipList, int *ipCount, int *totalIPs );
int RCESDPPersistIP( void *conn, pRCESIp ip );
int RCESDPRemoveIP( void *conn, int ipID );

/* Volume */
int RCESDPGetVolumes( void *conn, int osID, int volumeListSize, int volumeStart, ppRCESVolume *volumeList, int *volumeCount, 
                      int *totalVolumes );
int RCESDPGetVolume( void *conn, int osID, const char *name, ppRCESVolume volume );
int RCESDPGetVolumeCached( void *conn, int osID, const char *name, ppRCESVolume volume );
int RCESDPGetVolume( void *conn, int volumeID, ppRCESVolume volume );
int RCESDPPersistVolume( void *conn, pRCESVolume volume );
int RCESDPRemoveVolume( void *conn, int volumeID, bool recursive, bool inTransaction = false );

/* DBEngine */
int RCESDPGetDBEngines( void *conn, int osID, int dbEngineListSize, int dbEngineStart, ppRCESDBEngine *dbEngineList, int *dbEngineCount,
                        int *totalDBEngines );
int RCESDPGetDBEnginesByVolume( void *conn, int volumeID, int dbEngineListSize, int dbEngineStart, ppRCESDBEngine *dbEngineList, int *dbEngineCount,
                                int *totalDBEngines );
int RCESDPGetDBEngine( void *conn, int osID, int workingVolume, const char *workingDir, bool caseSensitive, ppRCESDBEngine dbEngine );
int RCESDPGetDBEngine( void *conn, int dbEngineID, ppRCESDBEngine dbEngine );
int RCESDPGetDBEngineByLocalDir( void *conn, int osID, int localVolume, const char *localDir, bool caseSensitive, ppRCESDBEngine dbEngine );
int RCESDPGetDBEngineByName(void *conn, int osID, const char *name, ppRCESDBEngine dbEngine);
int RCESDPPersistDBEngine( void *conn, pRCESDBEngine dbEngine );
int RCESDPSetDBEngineAuth( void *conn, int dbEngineID, const char *authContent );
int RCESDPRemoveDBEngine( void *conn, int dbEngineID, bool recursive );
int RCESDBCheck( pRCESMasterProvider masterProv, int osID, const char *volumeName, int volume, const char *path, bool canRemove, int *fileCount );
int RCESDBCheck( FCPool<RCESMasterConnPooled> *masterConnPool, int osID, const char *volumeName, int volume, const char *path, bool canRemove, int *fileCount );
int RCESDPSetDBEngineStatus( void *conn, int dbEngineID, RCESEngineStatus status );
int RCESDPSetDBEngineAcceptConn(void *conn, int dbEngineID, bool acceptConn);
int RCESDPSetDBEngineReadOnly(void *conn, int dbEngineID, bool readOnly);
int RCESDPSetDBEngineConnByIP(void *conn, int dbEngineID, bool connByIP);
int RCESDPUpdateDBEngineLastCheck( void *conn, int dbEngineID );
int RCESDPCheckDBEngineRepl(void *conn, int dbEngineID, char *replPlanNameList, int replPlanNameListSize);
int RCESDPSyncDBEngine(void *conn, pRCESDBEngine dbEngine);
int RCESDPUpdateDBEngineWebServer(void *conn, int dbEngineID, const char *webServerStr);

/* Database */
int RCESDPGetDatabases( void *conn, int dbEngineID, int databaseListSize, int databaseStart, ppRCESDatabase *databaseList, 
                        int *databaseCount, int *totalDatabases );
int RCESDPGetDatabase( void *conn, int databaseID, ppRCESDatabase database );
int RCESDPGetDatabase( void *conn, int dbEngineID, const char *name, ppRCESDatabase database );
int RCESDPPersistDatabase( void *conn, pRCESDatabase database );
int RCESDPRemoveDatabase( void *conn, int databaseID );
int RCESDPGetMemphisDBDir( void *conn, int osID, const char *dbEngineName, const char *databaseName, int *dbVolumeID, char *dbDirectory );

/* File Group */
int RCESDPGetFileGroups( void *conn, int dbEngineID, int fGroupListSize, int fGroupStart, ppRCESFileGroup *fGroupList, int *fGroupCount, 
                         int *totalFileGroups );
int RCESDPGetFileGroup( void *conn, int dbEngineID, const char *name, ppRCESFileGroup fileGroup );
int RCESDPGetFileGroup( void *conn, int fileGroupID, ppRCESFileGroup fileGroup );
int RCESDPPersistFileGroup( void *conn, pRCESFileGroup fileGroup );
int RCESDPRemoveFileGroup( void *conn, int fileGroupID, bool recursive );
int RCESDPGetFilesFromGroup( void *conn, int fileGroupID, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles );
int RCESDPAddFilesToGroup( void *conn, int fileGroupID, int *fileIDList, int fileCount );
int RCESDPRemoveFilesFromGroup( void *conn, int fileGroupID, int *fileIDList, int fileCount );

/* DBEngine Group */
int RCESDPGetDBEngineGroups( void *conn, int dGroupListSize, int dGroupStart, ppRCESDBEngineGroup *dGroupList, int *dGroupCount, 
                             int *totalDBEngineGroups );
int RCESDPGetDBEngineGroupsByName( void *conn, const char *name, bool partial, int dGroupListSize, int dGroupStart, 
                                   ppRCESDBEngineGroup *dGroupList, int *dGroupCount, int *totalDBEngineGroups );
int RCESDPGetDBEngineGroup( void *conn, int dbEngineGroupID, ppRCESDBEngineGroup dbEngineGroup );
int RCESDPPersistDBEngineGroup( void *conn, pRCESDBEngineGroup dbEngineGroup );
int RCESDPRemoveDBEngineGroup( void *conn, int dbEngineGroupID );
int RCESDPGetDBEnginesFromGroup( void *conn, int dbEngineGroupID, int dbEngineListSize, int dbEngineStart, ppRCESDBEngine *dbEngineList, 
                                 int *dbEngineCount, int *totalDBEngine );
int RCESDPAddDBEnginesToGroup( void *conn, int dbEngineGroupID, int *dbEngineIDList, int dbEngineCount );
int RCESDPRemoveDBEnginesFromGroup( void *conn, int dbEngineGroupID, int *dbEngineIDList, int dbEngineCount );
int RCESDPGetDBEnginesByGroup( void *conn, int dbEngineGroupItemListSize, int dbEngineGroupItemStart, ppRCESDBEngineGroupItem *dbEngineGroupItemList, 
                               int *dbEngineGroupItemCount, int *totalDBEngineGroupItems );

/* Publication */
int RCESDPGetPublications( void *conn, int dbEngineID, int publicationListSize, int publicationStart, ppRCESPublication *publicationList, 
                           int *publicationCount, int *totalPublications );
int RCESDPGetPublicationsByName( void *conn, int dbEngineID, const char *name, bool partial, int publicationListSize, int publicationStart, 
                                 ppRCESPublication *publicationList, int *publicationCount, int *totalPublications );
int RCESDPGetPublicationsByDatabase(void *conn, int databaseID, ppRCESPublication *publicationList, int *publicationCount);
int RCESDPGetPublicationsByFileGroup( void *conn, int fileGroupID, int publicationListSize, int publicationStart, ppRCESPublication *publicationList, 
                                      int *publicationCount, int *totalPublications );
int RCESDPGetPublication( void *conn, int publicationID, ppRCESPublication publication );
int RCESDPPersistPublication( void *conn, pRCESPublication publication );
int RCESDPRemovePublication( void *conn, int publicationID, bool recursive );
int RCESDPSetPublicationMode(void *conn, int publicationID, RCESPublicationMode mode);
int RCESDPGetFilesFromPublication( void *conn, int publicationID, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles );
int RCESDPAddFilesToPublication( void *conn, int publicationID, int *fileIDList, int fileCount );
int RCESDPRemoveFilesFromPublication( void *conn, int publicationID, int *fileIDList, int fileCount );
int RCESDPGetFileGroupsFromPublication( void *conn, int publicationID, int fileGroupListSize, int fileGroupStart, ppRCESFileGroup *fileGroupList, 
                                        int *fileGroupCount, int *totalFileGroups );
int RCESDPAddFileGroupsToPublication( void *conn, int publicationID, int *fileGroupIDList, int fileGroupCount );
int RCESDPRemoveFileGroupsFromPublication( void *conn, int publicationID, int *fileGroupIDList, int fileGroupCount );
int RCESDPGetTempPubName( void *conn, char *tempPubName );
int RCESDPGetFoldersFromPublication(void *conn, int publicationID, int folderRuleListSize, int folderRuleStart, ppRCESFolderRule *folderRuleList, int *folderRuleCount, 
	int *totalFolderRules);
int RCESDPAddFoldersToPublication(void *conn, int publicationID, ppRCESFolderRule folderRuleList, int folderRuleCount);
int RCESDPRemoveFoldersFromPublication(void *conn, int publicationID, int *folderIDList, int folderCount);
int RCESDPGetDBRulesFromPublication(void *conn, int publicationID, ppRCESDatabaseRule dbRuleList);
int RCESDPPersistDBRule(void *conn, int publicationID, pRCESDatabaseRule dbRule);

/* Subscription */
int RCESDPGetSubscriptions( void *conn, int publication, int dbEngine, int subscriptionListSize, int subscriptionStart, 
                            ppRCESSubscription *subscriptionList, int *subscriptionCount, int *totalSubscriptions );
int RCESDPGetSubscriptionsByName( void *conn, int publication, int dbEngine, const char *name, bool partial, int subscriptionListSize, 
                                  int subscriptionStart, ppRCESSubscription *subscriptionList, int *subscriptionCount, int *totalSubscriptions );
int RCESDPGetSubscription( void *conn, int subscriptionID, ppRCESSubscription subscription );
int RCESDPPersistSubscription( void *conn, pRCESSubscription subscription );
int RCESDPRemoveSubscription( void *conn, int subscriptionID );
int RCESDPAddReplItem( void *conn, pRCESSubscription subscription, int targetVolumeCount, ppRCESVolume targetVolumeList, int fileID, bool isSourceCaseSensitive,  bool addDatabase, bool ignorePartitioned);
int RCESDPPopulateSubscriptionFileTable( void *conn, pRCESSubscription subscription, bool ignorePartitioned, ppRCESFile fileList, int fileCount);
int RCESDPGetTempSubsName( void *conn, char *tempSubsName );

/* Agent */
int RCESDPGetAgents( void *conn, int osID, int agentListSize, int agentStart, ppRCESAgent *agentList, int *agentCount, int *totalAgents );
int RCESDPGetAgent( void *conn, int agentID, ppRCESAgent agent );
int RCESDPGetAgentByDBEngine( void *conn, int dbEngineID, ppRCESAgent agent );
int RCESDPGetAgentByPath( void *conn, int workingVolumeID, const char *workingDir, bool caseSensitive, ppRCESAgent agent );
int RCESDPPersistAgent( void *conn, pRCESAgent agent );
int RCESDPRemoveAgent( void *conn, int agentID, bool recursive );
int RCESDPSetAgentStatus( void *conn, int agentID, RCESAgentStatus status );
int RCESDPGetAgentConsumers(void *conn, int agentID, ppRCESAgentConsumer *agentConsumerList, int *agentConsumerCount);
int RCESDPGetAgentConsumersByDB(void *conn, int dbEngineID, ppRCESAgentConsumer *agentConsumerList, int *agentConsumerCount);
int RCESDPUpdateAgentConsumer(void *conn, int agentID, RCESConsumerType consumer, bool active, int thrdCount);

/* Replication Statistics */
int RCESDPGetReplStatByID(void *conn, int replPlanID, RCESBigInt id, ppRCESReplStat replStat);
int RCESDPGetReplStats( void *conn, int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int replStatListSize, int replStatStart, 
                        ppRCESReplStat *replStatList, int *replStatCount, int *totalReplStats );
int RCESDPAddReplStat( void *conn, pRCESReplStat replStat );
int RCESDPArchiveReplStat(void *conn, int daysToArchive);
int RCESDPGetReplParallelStatByID(void *conn, int replPlanID, RCESBigInt id, ppRCESReplParallelStat replStat);
int RCESDPGetReplParallelStats(void *conn, int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int replStatListSize, int replStatStart,
	ppRCESReplParallelStat *replStatList, int *replStatCount, int *totalReplStats);
int RCESDPAddReplParallelStat(void *conn, pRCESReplParallelStat replStat);
int RCESDPArchiveReplParallelStat(void *conn, int daysToArchive);

/* Replication Exception */
int RCESDPGetReplExceps(void *conn, int replPlanID, RCESDateTime startTime, RCESDateTime endTime, const char *dumpFileName, int replExcepListSize, int replExcepStart, ppRCESReplExcep *replExcepList, int *replExcepCount, int *totalReplExceps);
int RCESDPDeleteReplExceps(void *conn, int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int *totalReplExceps);
int RCESDPArchiveReplExceps(void *conn, int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int *totalReplExceps);
int RCESDPSetDumpExceptionsStatus(void *conn, int replPlanID, bool start);
int RCESDPGetReplExcep(void *conn, int replPlanID, ppRCESReplExcep replExcep);
int RCESDPAddReplExcep( void *conn, pRCESReplExcep replExcep );
int RCESDPGetNAckReplExceps(void *conn, int replPlanID, ppRCESReplExcep replExcep);
int RCESDPReplPlanHasAckTime(void *conn, int replPlanID);

/* Log */
int RCESDPGetLogs(void *conn, RCESDateTime startTime, RCESDateTime endTime, short maxDetailLevel, short maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent,
	bool showWebServer, int dbEngineID, const char *funcName, int errorCode, int logListSize, int logStart, ppRCESLog *logList, int *logCount, int *totalLogs);
int RCESDPGetLatestLogs(void *conn, int latestCount, short maxDetailLevel, short maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent, bool showWebServer, int dbEngineID,
	const char *funcName, int errorCode, int logListSize, int logStart, ppRCESLog *logList, int *logCount, int *totalLogs);
int RCESDPAddLog(void *conn, pRCESLog log);
int RCESDPArchiveLog(void *conn, int daysToArchive);

/* Action */
int RCESDPArchiveAction(void *conn, int daysToArchive);

/* Globals */
int RCESDPSetGlobal(void *conn, const char *key, const char *value);
int RCESDPGetGlobal(void *conn, const char *key, char *value);
int RCESDPRemoveGlobal(void *conn, const char *key);

/* Replication Agent */
void RCESReplAgentCheck(FCPool<RCESMasterConnPooled> *masterConnPool, int actionID, int osID, const char *path);
void RCESReplAgentImport(FCPool<RCESMasterConnPooled> *masterConnPool, const char *path, ppRCESReplPlan replPlan, ppRCESSubscription subscription, ppRCESPublication publication, FCHashTable<char> **redirectStrList, char *filterName);
int RCESDPGetReplAgents(void *conn, int actionID, ppRCESReplAgent *replAgentList, int *replAgentCount);
int RCESDPGetReplAgent(void *conn, int actionID, int osID, const char *path, bool caseSensitive, ppRCESReplAgent replAgent);
int RCESDPPersistReplAgent(void *conn, pRCESReplAgent replAgent, bool caseSensitive);
int RCESDPRemoveReplAgents(void *conn, int actionID);

/* Availability Group */
int RCESDPGetAvailGroups(void *conn, int aGroupListSize, int aGroupStart, ppRCESAvailGroup *aGroupList, int *aGroupCount, int *totalAvailGroups);
int RCESDPGetAvailGroupsByName(void *conn, const char *name, bool partial, int aGroupListSize, int aGroupStart, ppRCESAvailGroup *aGroupList, int *aGroupCount, int *totalAvailGroups);
int RCESDPGetAvailGroup(void *conn, int availGroupID, ppRCESAvailGroup availGroup);
int RCESDPGetAvailGroupByDBEngine(void *conn, int dbEngineID, ppRCESAvailGroup availGroup);
int RCESDPGetAvailGroupByReplPlan(void *conn, int replPlanID, ppRCESAvailGroup availGroup);
int RCESDPPersistAvailGroup(void *conn, pRCESAvailGroup availGroup);
int RCESDPRemoveAvailGroup(void *conn, int availGroupID);
int RCESDPSetAvailGroupDeployed(void *conn, int availGroupID, bool isDeployed);
int RCESDPSetAvailGroupStatus(void *conn, int availGroupID, RCESEngineStatus status, RCESReplStatus replicaStatus, const char *statusMsg, int actionID);

/* Replica */
int RCESDPCleanAvailGroup(void *conn, int availGroupID);
int RCESDPAddReplicasToGroup(void *conn, ppRCESReplica replicaList, int replicaCount);
int RCESDPRemoveReplicasFromGroup(void *conn, int *dbEngineIDList, int dbEngineCount);
int RCESDPPersistReplica(void *conn, pRCESReplica replica);
int RCESDPRemoveReplica(void *conn, int dbEngineID);
int RCESDPGetReplica(void *conn, int dbEngineID, ppRCESReplica replica);

/* Availability Group Status */
int RCESDPGetAvailGroupStatus(void *conn, int availGroupID, ppRCESAvailGroupStatus availGroupStatus);
int RCESDPGetAvailGroupStatusByName(void *conn, const char *availGroupName, ppRCESAvailGroupStatus availGroupStatus);
int RCESDPGetReplicaStatus(void *conn, int dbEngineID, ppRCESReplicaStatus replicaStatus);

/* Layout */
int RCESDPGetLayouts( void *conn, int layoutID, int layoutListSize, int layoutStart, ppRCESLayout *layoutList, int *layoutCount, int *totalLayouts );
int RCESDPPersistLayout( void *conn, pRCESLayout layout );
int RCESDPRemoveLayouts( void *conn, int objectType, int objectId );
int RCESDPRemoveLayoutDbEngines(void *conn);
int RCESDPRemoveLayoutGroups(void *conn);

/* Layout Info*/
int RCESDPGetLayoutInfo( void *conn, int layout, int layoutInfoListSize, int layoutInfoStart, ppRCESLayoutInfo *layoutInfoList, int *layoutInfoCount, int *totalLayoutInfos );
int RCESDPPersistLayoutInfo( void *conn, pRCESLayoutInfo layoutInfo );
int RCESDPRemoveLayoutInfo( void *conn, int layout );

/* General */
const char *RCESDPGetType();
const char *RCESDPGetErrorMsg( void *conn );
void RCESDPSetError( void *conn, int errorCode, const char *errorMsg );

typedef void *RCESHandle;

/*^****************************************************************************\
*
*   RCESDataProvider
*   Recon-e-Sense data provider class
*
*   Implement the data management interface
*
\******************************************************************************/
class RCESDataProvider
{
	public:
		/* Static services */
		static int ThreadAttach(bool *attached);
		static int ThreadDetach();

		/* Constructors & destructor */
		RCESDataProvider( pRCESConfig config );
		virtual ~RCESDataProvider();

		/* Public methods */
		virtual int Connect( bool ctdbOnly = false );
		virtual void Disconnect() = 0;
		virtual int GetThreadOwner() = 0;
		virtual int ConnDetach() = 0;
		virtual const char *GetErrorMsg() = 0;
		virtual bool IsMasterProvider() = 0;

		/* File */
		virtual int AddFile( pRCESFile file, bool isBlockInsert = TRUE ) = 0;
		virtual int StartInsBatch() = 0;
		virtual int FinishInsBatch() = 0;
		virtual int OpenFSFile( const char *tempFSFileName ) { return RCES_SUCCESS; };

		/* Volume */
		virtual int GetVolume( int volumeID, ppRCESVolume volume ) = 0;

		/* General */
		pRCESConfig GetConfig() { return _config; };
		bool IsConnected() { return _isConnected; }
		char *GetErrorBuf() { return _errorMsg; };
		RCESHandle GetConnHandle() { return _conn; };

	protected:
		/* Protected properties */
		pRCESConfig _config;
		RCESHandle _conn;
		bool _isConnected;
		bool _isCtreeActive;
		char _fileName[RCES_MAX_PATH+1];

		/* Protected methods */
		char *_getHost();
		char _errorMsg[RCES_MAX_ERRMSG_LEN+1];
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESDataProvider *pRCESDataProvider, **ppRCESDataProvider;

#endif /* _FCRCESDATAPROV_HPP_ */