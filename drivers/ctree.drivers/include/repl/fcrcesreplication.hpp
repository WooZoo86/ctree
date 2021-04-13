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

#ifndef _FCRCESREPLICATION_HPP_
#define _FCRCESREPLICATION_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrceslogger.hpp"
#include "fcrcesdataprov.hpp"
#include "fcrcesreplbase.hpp"
#include "fcrcesreplctree.hpp"
#include "fcrcesreplnctree.hpp"
#include "fcrcessubscription.hpp"
#include "fcrcesconn.hpp"
#include "fcrcesreplstat.hpp"
#include "fcrcesreplexcep.hpp"
#include "fcrcesreplfunc.hpp"

extern "C" {
    #include "fcrcesjson.h"
}

#define RCES_REPLPLAN_SUBSCRIPTION "subscription"
#define RCES_REPLPLAN_SUBSCRIPTIONLIST "subscriptionList"
#define RCES_REPLPLAN_SUBSSTATUSLIST "subscriptionStatusList"
#define RCES_REPLPLAN_STARTFILE "startFile"
#define RCES_REPLPLAN_FILECOUNT "fileCount"
#define RCES_REPLPLAN_ADDDATABASE "addDatabase"
#define RCES_REPLPLAN_FILEGROUP "fileGroup"

/*^****************************************************************************\
*
*   RCESReplication
*   Recon-e-Sense replication class
*
*   Manage the replication plan
*
\******************************************************************************/
class RCESReplication
{
    public:
        /* Constructors & destructor */
        RCESReplication( int replPlanID, pRCESMasterProvider masterProv );
		RCESReplication( pRCESReplPlan replPlan, pRCESMasterProvider masterProv );
        virtual ~RCESReplication();

        /* Public Services */
		static int ctReplDeploy( pRCESMasterProvider masterProv, int replPlanID, bool forceReplace, int *actionID );
		static int ctReplStart( pRCESMasterProvider masterProv, int replPlanID, const char *sourceLogPos, const char *targetLogPos, bool ignoreDeploy, int *actionID );
		static int ctReplStop( pRCESMasterProvider masterProv, int replPlanID, bool waitForCheck, int *actionID );
		static int ctReplCheck( pRCESMasterProvider masterProv, int replPlanID, bool checkConn, ppRCESReplPlan *replPlanList, int *replPlanCount, int *actionID);
		static int ctReplCheck( pRCESMasterProvider masterProv, int replPlanID, bool checkConn, ppRCESJson result );
		static int ctCancelRepl( pRCESMasterProvider masterProv, int replPlanID, int actionID );
		static int ctReplStartMonitor( pRCESMasterProvider masterProv, int replPlanID, int refreshRate );
		static int ctReplStopMonitor( pRCESMasterProvider masterProv, int replPlanID );
		static int ctReplGetStatByID(pRCESMasterProvider masterProv, int replPlanID, RCESBigInt id, ppRCESReplStat parallelStat);
		static int ctReplGetStatByID(pRCESMasterProvider masterProv, int replPlanID, RCESBigInt id, bool detail, ppRCESJson result);
		static int ctReplGetStats( pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, int statListSize, 
		                           int statStart, ppRCESReplStat *statList, int *statCount, int *totalReplStats );
		static int ctReplGetStats(pRCESMasterProvider masterProv, int replPlanID, bool detail, RCESDateTime begin, RCESDateTime end, bool isPaging,
			                      int statListSize, int statStart, ppRCESJson result);
		static int ctReplGetParallelStatByID(pRCESMasterProvider masterProv, int replPlanID, RCESBigInt id, ppRCESReplParallelStat parallelStat);
		static int ctReplGetParallelStatByID(pRCESMasterProvider masterProv, int replPlanID, RCESBigInt id, bool threadDetails, ppRCESJson result);
		static int ctReplGetParallelStats(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, int statListSize,
		                                  int statStart, ppRCESReplParallelStat *statList, int *statCount, int *totalReplStats);
		static int ctReplGetParallelStats(pRCESMasterProvider masterProv, int replPlanID, bool threadDetails, RCESDateTime begin, RCESDateTime end, bool isPaging,
			                              int statListSize, int statStart, ppRCESJson result);
		static int ctReplStartExcepLog( pRCESMasterProvider masterProv, int replPlanID );
		static int ctReplStopExcepLog( pRCESMasterProvider masterProv, int replPlanID );
		static int ctReplGetExceptions(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, const char *dumpFileName, int excepListSize, int excepStart, ppRCESReplExcep *excepList, int *excepCount, int *totalReplExceps);
		static int ctReplGetExceptions(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, const char *dumpFileName, bool isPaging, int excepListSize, int excepStart, ppRCESJson result );
		static int ctReplCleanExceptions(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, bool deleteFlag, int *totalReplExceps);
		static int ctReplCleanExceptions(pRCESMasterProvider masterProv, int replPlanID, RCESDateTime begin, RCESDateTime end, bool deleteFlag, ppRCESJson result);
		static int ctReplPlanFuncTimeStart( pRCESMasterProvider masterProv, int replPlanID );
		static int ctReplPlanFuncTimeStop( pRCESMasterProvider masterProv, int replPlanID );
		static int ctReplPlanFuncTimeReset( pRCESMasterProvider masterProv, int replPlanID );
		static int ctReplPlanGetFuncTimes( pRCESMasterProvider masterProv, int replPlanID, ppRCESReplFunc *sourceFuncList, int *sourceFuncCount,
		                                   ppRCESReplFunc *targetFuncList, int *targetFuncCount );
		static int ctReplPlanGetFuncTimes( pRCESMasterProvider masterProv, int replPlanID, ppRCESJson result );
		static int ctReplPlanPause( pRCESMasterProvider masterProv, int replPlanID );
		static int ctReplPlanResume( pRCESMasterProvider masterProv, int replPlanID );
		static int ctGetTempReplPlanName( pRCESMasterProvider masterProv, char *tempReplPlanName );
		static int ctGetTempReplPlanName( pRCESMasterProvider masterProv, ppRCESJson result );
		static int ctReplPlanAckExceptions(pRCESMasterProvider masterProv, int replPlanID);
		static int ctResyncFiles(pRCESMasterProvider masterProv, int replPlanID, int *fileIDList, int fileCount, bool addNewFiles, int *actionID);
		static void ReplPlanCheck(pRCESMasterProvider masterProv, pRCESReplPlan replPlan);

        /* Public Methods */
		pRCESReplPlan GetReplPlan() { return _replPlan; };

    private:
        /* Private properties */
        pRCESConfig _config;
        pRCESLogger _logger;
        pRCESMasterProvider _provider;
		pRCESReplPlan _replPlan;
		bool _deleteReplPlan;

        /* Private methods */
		void Deploy( bool forceReplace, int *actionID );
		void Start( const char *sourceLogPos, const char *targetLogPos, bool ignoreDeploy, int *actionID );
		void Stop( bool waitForCheck, int *actionID );
		void CheckActiveReplPlan();
		void CheckReplPlanAgents();
		void CheckReplPlanBasicAgents();
		void StartMonitor( int refreshRate );
		void StopMonitor();
		void StartExcepLog();
		void StopExcepLog();
		void StartFuncTime();
		void StopFuncTime();
		void ResetFuncTime();
		void GetFuncTimes( ppRCESReplFunc *sourceFuncList, int *sourceFuncCount, ppRCESReplFunc *targetFuncList, int *targetFuncCount );
		void Pause();
		void Resume();
		void Resync(int *fileIDList, int fileCount, bool addNewFiles, int *actionID);

		void _getFuncTimeList( char *content, int contentLen, ppRCESReplFunc *funcList, int *funcCount );
		void _checkAgent(pRCESAgent agent, RCESReplicationDirection direction);
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESReplication *pRCESReplication, **ppRCESReplication;

#endif /* _FCRCESREPLICATION_HPP_ */