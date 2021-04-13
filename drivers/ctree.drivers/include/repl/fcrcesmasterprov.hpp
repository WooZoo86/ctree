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

#ifndef _FCRCESMASTERPROV_HPP_
#define _FCRCESMASTERPROV_HPP_

#include "fc_rces.h"
#include "fcrcesdataprov.hpp"
#include "fcrcesconfig.hpp"
#include "fcrceslogger.hpp"
#include "fcrcesaction.hpp"
#include "fcrcesreplplan.hpp"
#include "fchashtable.hpp"
#include "fcrcesfile.hpp"
#include "fcrcesdbenginegroup.hpp"
#include "fcrcespublication.hpp"
#include "fcrcessubscription.hpp"
#include "fcrcesreplstat.hpp"
#include "fcrcesreplparallelstat.hpp"
#include "fcrcesreplexcep.hpp"
#include "fcrceslayout.hpp"
#include "fcrceslayoutinfo.hpp"
#include "fcrcesmasterconfig.hpp"

/* Class type definitions */
class RCESSite;
class RCESHardware;
class RCESOpSystem;
class RCESVolume;
class RCESActionQueue;
class RCESMac;
class RCESIp;
class RCESAgent;
class RCESReplStat;
class RCESReplParallelStat;
class RCESReplExcep;
class RCESAgentConsumer;
typedef RCESSite *pRCESSite, **ppRCESSite;
typedef RCESHardware *pRCESHardware, **ppRCESHardware;
typedef RCESOpSystem *pRCESOpSystem, **ppRCESOpSystem;
typedef RCESVolume *pRCESVolume, **ppRCESVolume;
typedef RCESActionQueue *pRCESActionQueue, **ppRCESActionQueue;
typedef RCESMac *pRCESMac, **ppRCESMac;
typedef RCESIp *pRCESIp, **ppRCESIp;
typedef RCESAgent *pRCESAgent, **ppRCESAgent;
typedef RCESReplStat *pRCESReplStat, **ppRCESReplStat;
typedef RCESReplParallelStat *pRCESReplParallelStat, **ppRCESReplParallelStat;
typedef RCESReplExcep *pRCESReplExcep, **ppRCESReplExcep;
typedef RCESAgentConsumer *pRCESAgentConsumer, **ppRCESAgentConsumer;

/*^****************************************************************************\
*
*   RCESMasterProvider
*   Recon-e-Sense data provider class
*
*   Implement the data management interface with the master database
*
\******************************************************************************/
class RCESMasterProvider : public RCESDataProvider
{
	public:

		/* Public Services */
		static int ctReplConnect( pRCESMasterConfig masterConfig, pRCESDynServer dynServer, ppRCESMasterProvider masterProv, char **errorMsg );
		static int ctGetVolumeCached( FCPool<RCESMasterConnPooled> *masterProvPool, FCCache<RCESVolume> *volumeCache, int volumeID, 
		                              ppRCESVolume volume, char **errorMsg );

		/* Constructors & destructor */
		RCESMasterProvider(pRCESMasterConfig masterConfig);
		virtual ~RCESMasterProvider();

		/* General */
		bool IsMasterProvider() { return true; };
		void GetConnStr( char *connStr );
		int CommitWork();
		int Kill( int taskID );
		pRCESActionQueue GetQueue() { return _queue; };
		int Connect(bool ctdbOnly = false);
		void Disconnect();
		bool IsActive();
		int GetThreadOwner();
		int ConnAttach();
		int ConnDetach();
		int StartInsBatch();
		int FinishInsBatch();
		const char *GetErrorMsg();
		pRCESLogger GetLogger() { return _logger;  };

		/* Log */
		int GetLogs(RCESDateTime startTime, RCESDateTime endTime, short maxDetailLevel, short maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent, bool showWebServer,
			int dbEngineID, const char *funcName, int errorCode, int logListSize, int logStart, ppRCESLog *logList, int *logCount, int *totalLogs);
		int GetLatestLogs(int latestCount, short maxDetailLevel, short maxSevLevel, bool showDBEngine, bool showReplStudio, bool showReplAgent, bool showWebServer, int dbEngineID,
			const char *funcName, int errorCode, int logListSize, int logpStart, ppRCESLog *logList, int *logCount, int *totalLogs);
		int AddLog(pRCESLog log);
		int ArchiveLog(int daysToArchive);

		/* Action */
		int ArchiveAction(int daysToArchive);

		/* File */
		int GetFiles( int volumeID, const char *rootTreePath, const char *mask, bool recursive, int checkReplPlan, int fileListSize, 
		              int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles );
		int GetFiles( int databaseID, int checkReplPlan, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, 
		              int *totalFiles );
		int GetFolders(int volumeID, const char *rootTreePath, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles);
		int GetSubscriptionTargetTables( int subscriptionID, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles );
		int GetSubscriptionTargetFiles(int subscriptionID, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles);
		int GetFile( int fileID, ppRCESFile file );
		int GetFileByName( int volumeID, const char *path, const char *name, ppRCESFile file );
		int PersistFile( pRCESFile file );
		int UpdateFile( pRCESFile file );
		int RemoveFile( pRCESFile file, bool recursive );
		int RemoveFile( int fileID, bool recursive, bool tree = true );
		int RemoveDBFile( pRCESFile file );
		int RemoveDBFile( int fileID );
		RCESFileType GetFileType( int fileID );
		void ReloadSchemas( int volumeID );
		int AddBlockFS( pRCESRecBlock recBlock );
		int CheckPath( int volumeID, const char *volumeName, const char *path );
		int AddFile( pRCESFile file, bool isBlockInsert = TRUE );
		int CleanFiles( int volumeID );

		/* Replication plan */
		int GetReplPlans( int replPlanListSize, int replPlanStart, ppRCESReplPlan *replPlanList, int *replPlanCount, int *totalReplPlan, bool archived = false );
		int GetReplPlansByName( const char *name, bool partial, int replPlanListSize, int replPlanStart, ppRCESReplPlan *replPlanList, int *replPlanCount, int *totalReplPlan, bool archived = false);
		int GetReplPlansByOS( int osID, ppRCESReplPlan *replPlanList, int *replPlanCount );
		int GetReplPlansByPublication(int publicationID, ppRCESReplPlan *replPlanList, int *replPlanCount);
		int GetReplPlan( int replPlanID, ppRCESReplPlan replPlan );
		int GetReplPlanByDBEngine( int sourceDBEngineID, int targetDBEngineID, ppRCESReplPlan replPlan );
		int GetReplPlansByDBEngine(int dbEngineID, ppRCESReplPlan *replPlanList, int *replPlanCount);
		int PersistReplPlan( pRCESReplPlan replPlan );
		int RemoveReplPlan( int replPlanID, bool recursive );
		int GetReplSubscriptions( int replPlanID, int replSubsListSize, int replSubsStart,  ppRCESSubscription *subsList, int *subsCount,  int *totalReplSubs );
		int SetReplPlanStatus( int replPlanID, RCESReplStatus status, const char *statusMsg, int actionID, int sourceAgentID = -1, int targetAgentID = -1 );
		int SetReplPlanMonitor( int replPlanID, bool isMonitorActive, int refreshRate = 0 );
		int SetReplPlanExcepLog( int replPlanID, bool isExcepLogActive );
		int SetReplPlanFuncTime( int replPlanID, bool isFuncTimeActive );
		int SetReplPlanPause( int replPlanID, bool isPaused );
		int GetReplPlanStatus( int replPlanID, RCESReplStatusInfo &replStatusInfo, char *statusMsg, int *sourceAgentID = NULL, int *targetAgentID = NULL );
		int CheckDeployed( int replPlanID );
		int SetDeployed( int replPlanID );
		int UpdateReplSourceLogPos( int replPlanID, const char *sourceLogPos, const char *sourceTranID);
		int UpdateReplTargetLogPos( int replPlanID, const char *targetLogPos, const char *targetTranID);
		int GetReplFileList( int replPlanID, int replFileListSize, int replFileStart, ppRCESReplFileList replFileList, int *replFileCount, int *totalReplFiles );
		int GetReplFiles( int replPlanID, int sourceFileID, ppRCESReplFile *replFileList, int *replFileCount );
		int CheckCircularRepl( int replPlanID );
		int MarkReplPlanDirtyByPublication( int publicationID );
		int MarkReplPlanDirtyByFileGroup( int fileGroup );
		int SyncReplPlan( pRCESReplPlan replPlan );
		int GetTempReplPlanName( char *tempReplPlanName );
		int SetReplPlanAckExceps(int replPlanID);
		int SetReplPlanNAckFlag(int replPlanID, bool nAckFlag);
		int CheckReplPlanNodes(pRCESReplPlan replPlan);
		int SetReplPlanLatency(int replPlanID, RCESReplicationDirection direction, int latency);

		/* Replication Plan Redirection */
		int PersistRedirection( pRCESReplRedir replRedir );
		int CleanRedirection( int subsID );
		int GetRedirectionsByReplPlan( int replPlanID, ppRCESReplRedir *redirList, int *redirCount );

		/* Site */
		int GetSites( int siteListSize, int siteStart, ppRCESSite *siteList, int *siteCount, int *totalSites );
		int GetSite( int siteID, ppRCESSite site );
		int GetSite( const char *name, ppRCESSite site );
		int PersistSite( pRCESSite site );
		int RemoveSite( int siteID, bool recursive );

		/* Hardware */
		int GetHardwares( int siteID, int hardwareListSize, int hardwareStart, ppRCESHardware *hardwareList, int *hardwareCount, 
		                  int *totalHardwares );
		int GetHardware( int hardwareID, ppRCESHardware hardware );
		int GetHardware( int siteID, const char *name, ppRCESHardware hardware );
		int GetHardware( const char *mac, ppRCESHardware hardware );
		int PersistHardware( pRCESHardware hardware );
		int RemoveHardware( int hardwareID, bool recursive );

		/* MAC address */
		int GetMacs( int hardwareID, int macListSize, int macStart, ppRCESMac *macList, int *macCount, int *totalMacs );
		int PersistMac( pRCESMac mac );
		int RemoveMac( const char *macAddress );

		/* OpSystem */
		int GetOSs( int hardwareID, int osListSize, int osStart, ppRCESOpSystem *osList, int *osCount, int *totalOSs );
		int GetOS( int hardwareID, const char *name, ppRCESOpSystem opSystem );
		int GetOS( const char *hostName, ppRCESOpSystem opSystem );
		int GetOS( int osID, ppRCESOpSystem opSystem );
		int GetOSByIP( const char *ipAddress, ppRCESOpSystem opSystem );
		int PersistOS( pRCESOpSystem opSystem );
		int RemoveOS( int osID, bool recursive );

		/* IP address */
		int GetIPs( int osID, int ipListSize, int ipStart, ppRCESIp *ipList, int *ipCount, int *totalIPs );
		int PersistIP( pRCESIp ip );
		int RemoveIP( int ipID );

		/* Volume */
		int GetVolumes( int osID, int volumeListSize, int volumeStart, ppRCESVolume *volumeList, int *volumeCount, int *totalVolumes );
		int GetVolume( int osID, const char *name, ppRCESVolume volume );
		int GetVolumeCached( int osID, const char *name, ppRCESVolume volume );
		int GetVolume( int volumeID, ppRCESVolume volume );
		int GetVolumeCached( int volumeID, ppRCESVolume volume );
		int GetVolumeByPath( int osID, const char *fullFileName, ppRCESVolume volume );
		int PersistVolume( pRCESVolume volume );
		int RemoveVolume( int volumeID, bool recursive );

		/* DBEngine */
		int GetDBEngines( int osID, int dbEngineListSize, int dbEngineStart, ppRCESDBEngine *dbEngineList, int *dbEngineCount, 
		                  int *totalDBEngines );
		int GetDBEnginesByVolume( int volumeID, int dbEngineListSize, int dbEngineStart, ppRCESDBEngine *dbEngineList, int *dbEngineCount, 
		                          int *totalDBEngines );
		int GetDBEngine( int osID, int workingVolume, const char *workingDir, bool caseSensitive, ppRCESDBEngine dbEngine );
		int GetDBEngine( int dbEngineID, ppRCESDBEngine dbEngine );
		int GetDBEngineByLocalDir( int osID, int volume, const char *localDir, bool caseSensitive, ppRCESDBEngine dbEngine );
		int GetDBEngineByName(int osID, const char *name, ppRCESDBEngine dbEngine);
		int PersistDBEngine( pRCESDBEngine dbEngine );
		int SetDBEngineAuth( int dbEngineID, const char *authContent );
		int RemoveDBEngine( int dbEngineID, bool recursive );
		int CheckDBEngines( int osID );
		int SetDBEngineStatus( int dbEngineID, RCESEngineStatus status, bool managed );
		int SetDBEngineAcceptConn(int dbEngineID, bool acceptConn);
		int SetDBEngineReadOnly(int dbEngineID, bool readOnly);
		int SetDBEngineConnByIP(int dbEngineID, bool connByIP);
		int UpdateDBEngineLastCheck( int dbEngineID );
		int CheckDBEngineRepl(int dbEngineID, char *replPlanNameList, int replPlanNameListSize);
		int SyncDBEngine(pRCESDBEngine dbEngine);
		int UpdateDBEngineWebServer(int dbEngineID, const char *webServerStr);

		/* Database */
		int GetDatabases( int dbEngineID, int databaseListSize, int databaseStart, ppRCESDatabase *databaseList, int *databaseCount,
		                  int *totalDatabases);
		int GetDatabase( int databaseID, ppRCESDatabase database );
		int GetDatabase( int dbEngineID, const char *name, ppRCESDatabase database );
		int PersistDatabase( pRCESDatabase database );
		int RemoveDatabase( int databaseID );
		int GetMemphisDBDir( int osID, const char *dbEngineName, const char *databaseName, int *dbVolumeID, char *dbDirectory );

		/* File Group */
		int GetFileGroups( int dbEngineID, int fGroupListSize, int fGroupStart, ppRCESFileGroup *fGroupList, int *fGroupCount, 
		                   int *totalFileGroups );
		int GetFileGroup( int dbEngineID, const char *name, ppRCESFileGroup fileGroup );
		int GetFileGroup( int fileGroupID, ppRCESFileGroup fileGroup );
		int PersistFileGroup( pRCESFileGroup fileGroup );
		int RemoveFileGroup( int fileGroupID, bool recursive );
		int GetFilesFromGroup( int fileGroupID, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, 
		                       int *totalFiles );
		int AddFilesToGroup( int fileGroupID, int *fileIDList, int fileCount );
		int RemoveFilesFromGroup( int fileGroupID, int *fileIDList, int fileCount );

		/* DBEngine Group */
		int GetDBEngineGroups( int dGroupListSize, int dGroupStart, ppRCESDBEngineGroup *dGroupList, int *dGroupCount, 
		                       int *totalDBEngineGroups );
		int GetDBEngineGroupsByName( const char *name, bool partial, int dGroupListSize, int dGroupStart, 
		                             ppRCESDBEngineGroup *dGroupList, int *dGroupCount, int *totalDBEngineGroups );
		int GetDBEngineGroup( int dbEngineGroupID, ppRCESDBEngineGroup dbEngineGroup );
		int PersistDBEngineGroup( pRCESDBEngineGroup dbEngineGroup );
		int RemoveDBEngineGroup( int dbEngineGroupID );
		int GetDBEnginesFromGroup( int dbEngineGroupID, int dbEngineListSize, int dbEngineStart, ppRCESDBEngine *dbEngineList, 
		                           int *dbEngineCount, int *totalDBEngine );
		int AddDBEnginesToGroup( int dbEngineGroupID, int *dbEngineIDList, int dbEngineCount );
		int RemoveDBEnginesFromGroup( int dbEngineGroupID, int *dbEngineIDList, int dbEngineCount );
		int GetDBEnginesByGroup( int dbEngineGroupItemListSize, int dbEngineGroupItemStart, ppRCESDBEngineGroupItem *dbEngineGroupItemList, 
		                         int *dbEngineGroupItemCount, int *totalDBEngineGroupItems );

		/* Publication */
		int GetPublications( int dbEngineID, int publicationListSize, int publicationStart, ppRCESPublication *publicationList, int *publicationCount, 
		                     int *totalPublications );
		int GetPublicationsByName( int dbEngineID, const char *name, bool partial, int publicationListSize, int publicationStart, 
		                           ppRCESPublication *publicationList, int *publicationCount, int *totalPublications );
		int GetPublicationsByDatabase(int databaseID, ppRCESPublication *publicationList, int *publicationCount);
		int GetPublicationsByFileGroup( int fileGroupID, int publicationListSize, int publicationStart, ppRCESPublication *publicationList, 
		                                int *publicationCount, int *totalPublications );
		int GetPublication( int publicationID, ppRCESPublication publication );
		int PersistPublication( pRCESPublication publication );
		int RemovePublication( int publicationID, bool recursive );
		int SetPublicationMode(int publicationID, RCESPublicationMode mode);
		int GetFilesFromPublication( int publicationID, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles );
		int AddFilesToPublication( int publicationID, int *fileIDList, int fileCount );
		int RemoveFilesFromPublication( int publicationID, int *fileIDList, int fileCount );
		int GetFileGroupsFromPublication( int publicationID, int fileGroupListSize, int fileGroupStart, ppRCESFileGroup *fileGroupList, int *fileGroupCount, 
		                                  int *totalFileGroups );
		int AddFileGroupsToPublication( int publicationID, int *fileGroupIDList, int fileGroupCount );
		int RemoveFileGroupsFromPublication( int publicationID, int *fileGroupIDList, int fileGroupCount );
		int GetTempPubName( char *tempPubName );
		int GetFolderRules(int publicationID, int folderRuleListSize, int folderRuleStart, ppRCESFolderRule *folderRuleList, int *folderRuleCount, int *totalFolderRules);
		int AddFolderRules(int publicationID, ppRCESFolderRule folderRuleList, int folderRuleCount);
		int RemoveFolderRules(int publicationID, int *folderIDList, int folderCount);
		int GetDBRules(int publicationID, ppRCESDatabaseRule dbRuleList);
		int PersistDBRule(int publicationID, pRCESDatabaseRule dbRule);

		/* Subscription */
		int GetSubscriptions( int publicationID, int dbEngine, int subscriptionListSize, int subscriptionStart, ppRCESSubscription *subscriptionList, 
		                      int *subscriptionCount, int *totalSubscriptions );
		int GetSubscriptionsByName( int publicationID, int dbEngine, const char *name, bool partial, int subscriptionListSize, int subscriptionStart, 
		                            ppRCESSubscription *subscriptionList, int *subscriptionCount, int *totalSubscriptions );
		int GetSubscription( int subscriptionID, ppRCESSubscription subscription );
		int PersistSubscription( pRCESSubscription subscription );
		int RemoveSubscription( int subscriptionID );
		int PopulateSubscriptionFileTable( pRCESSubscription subscription, bool ignorePartitioned, ppRCESFile fileList, int fileCount);
		int GetTempSubsName( char *tempSubsName );

		/* Agent */
		int GetAgents( int osID, int agentListSize, int agentStart, ppRCESAgent *agentList, int *agentCount, int *totalAgents );
		int GetAgent( int agentID, ppRCESAgent agent );
		int GetAgentByDBEngine( int dbEngineID, ppRCESAgent agent );
		int GetAgentByPath( int workingVolumeID, const char *workinDir, bool caseSensitive, ppRCESAgent agent );
		int PersistAgent( pRCESAgent agent );
		int RemoveAgent( int agentID, bool recursive );
		int SetAgentStatus( int agentID, RCESAgentStatus status );
		int StartAgentConsumer(int agentID, RCESConsumerType consumer, int thrdCount);
		int StopAgentConsumer(int agentID, RCESConsumerType consumer);
		int GetAgentConsumers(int agentID, ppRCESAgentConsumer *agentConsumerList, int *agentConsumerCount);
		int GetAgentConsumersByDB(int dbEngineID, ppRCESAgentConsumer *agentConsumerList, int *agentConsumerCount);

		/* Replication Statistics */
		int GetReplStatByID(int replPlanID, RCESBigInt id, ppRCESReplStat replStat);
		int GetReplStats( int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int replStatListSize, int replStatStart, 
		                  ppRCESReplStat *replStatList, int *replStatCount, int *totalReplStats );
		int AddReplStat( pRCESReplStat replStat );
		int ArchiveReplStat(int daysToArchive);

		/* Replication Parallel Statistics */
		int GetReplParallelStatByID(int replPlanID, RCESBigInt id, ppRCESReplParallelStat replStat);
		int GetReplParallelStats(int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int replStatListSize, int replStatStart,
			ppRCESReplParallelStat *replStatList, int *replStatCount, int *totalReplStats);
		int AddReplParallelStat(pRCESReplParallelStat replStat);
		int ArchiveReplParallelStat(int daysToArchive);

		/* Replication Exception */
		int GetReplExceps(int replPlanID, RCESDateTime startTime, RCESDateTime endTime, const char *dumpFileName, int replExcepListSize, int replExcepStart, ppRCESReplExcep *replExcepList, int *replExcepCount, int *totalReplExceps);
		int DeleteReplExceps(int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int *totalReplExceps);
		int ArchiveReplExceps(int replPlanID, RCESDateTime startTime, RCESDateTime endTime, int *totalReplExceps);
		int AddReplExcep( pRCESReplExcep replExcep );
		int GetNAckReplExceps(int replPlanID, ppRCESReplExcep replExcep);
		int SetDumpExceptionsStatus(int replPlanID, bool start);

		/* Globals */
		int SetGlobal(const char *key, const char *value);
		int GetGlobal(const char *key, char *value);
		int RemoveGlobal(const char *key);

		/* Replication Agent */
		int GetReplAgents(int actionID, ppRCESReplAgent *replAgentList, int *replAgentCount);
		int GetReplAgent(int actionID, int osID, const char *path, bool caseSensitive, ppRCESReplAgent replAgent);
		int PersistReplAgent(pRCESReplAgent replAgent, bool caseSensitive);
		int RemoveReplAgents(int actionID);

		/* Availability Group */
		int GetAvailGroups(int aGroupListSize, int aGroupStart, ppRCESAvailGroup *aGroupList, int *aGroupCount, int *totalAvailGroups);
		int GetAvailGroupsByName(const char *name, bool partial, int aGroupListSize, int aGroupStart, ppRCESAvailGroup *aGroupList, int *aGroupCount, int *totalAvailGroups);
		int GetAvailGroup(int availGroupID, ppRCESAvailGroup availGroup);
		int GetAvailGroupByDBEngine(int dbEngineID, ppRCESAvailGroup availGroup);
		int GetAvailGroupByReplPlan(int replPlanID, ppRCESAvailGroup availGroup);
		int PersistAvailGroup(pRCESAvailGroup availGroup);
		int RemoveAvailGroup(int availGroupID);
		int SetAvailGroupDeployed(int availGroupID, bool isDeployed);
		int SetAvailGroupStatus(int availGroupID, RCESEngineStatus status, RCESReplStatus replicaStatus, const char *statusMsg, int actionID);
		int CleanAvailGroup(int availGroupID);
		int AddReplicasToGroup(ppRCESReplica replicaList, int replicaCount);
		int RemoveReplicasFromGroup(int *dbEngineIDList, int dbEngineCount);
		int PersistReplica(pRCESReplica replica);
		int GetReplica(int dbEngineID, ppRCESReplica replica);

		/* Availability Group Status */
		int GetAvailGroupStatus(int availGroupID, ppRCESAvailGroupStatus availGroupStatus);
		int GetAvailGroupStatusByName(const char *availGroupName, ppRCESAvailGroupStatus availGroupStatus);
		int GetReplicaStatus(int dbEngineID, ppRCESReplicaStatus replicaStatus);

		/* Layout */
		int GetLayouts( int layoutID, int layoutListSize, int layoutStart, ppRCESLayout *layoutList, int *layoutCount, int *totalLayouts );
		int PersistLayout( pRCESLayout layout );
		int RemoveLayouts( int objectType, int objectId );
		int UpdateLayoutDbEngines();
		int UpdateLayoutGroups();

		/* LayoutInfo */
		int GetLayoutInfo( int layout, int layoutInfoListSize, int layoutInfoStart, ppRCESLayoutInfo *layoutInfoList, int *layoutInfoCount, int *totalLayoutInfos );
		int PersistLayoutInfo( pRCESLayoutInfo layoutInfo );
		int RemoveLayoutInfo( int layout );

	private:
		/* Private properties */
		pRCESActionQueue _queue;
		FCCache<RCESVolume> *_volumeCache;
		pRCESLogger _logger;
		pRCESMasterConfig _masterConfig;

		/* Private methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#endif /* _FCRCESMASTERPROV_HPP_ */