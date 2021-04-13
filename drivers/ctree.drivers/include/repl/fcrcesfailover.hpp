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

#ifndef _FCRCESFAILOVER_HPP_
#define _FCRCESFAILOVER_HPP_

#include "fc_rces.h"
#include "fcpool.hpp"

extern "C" {
    #include "fcrcesjson.h"
}

/*^****************************************************************************\
*
*   RCESFailOver
*   Recon-e-Sense failover class
*
*   Manage the HA failover based on the Availability Groups and all the 
*   Replication Plan involved in the replicas.
*
\******************************************************************************/
class RCESFailOver
{
	public:
		/* Constructors & destructor */
		RCESFailOver(int availGroupID, pRCESMasterProvider masterProv);
		RCESFailOver(pRCESAvailGroup availGroup, pRCESMasterProvider masterProv);
		virtual ~RCESFailOver();

		/* Public Services */
		static int ctAvailDeploy(pRCESMasterProvider masterProv, FCPool<RCESMasterConnPooled> *connPool, int availGroupID, int *actionID);
		static int ctAvailStart(pRCESMasterProvider masterProv, FCPool<RCESMasterConnPooled> *connPool, int availGroupID, bool ignoreDeploy, int *actionID);
		static int ctAvailStop(pRCESMasterProvider masterProv, FCPool<RCESMasterConnPooled> *connPool, int availGroupID, int *actionID);
		static int ctAvailRestore(pRCESMasterProvider masterProv, FCPool<RCESMasterConnPooled> *connPool, int availGroupID, int recoverOrder, int newPrimaryDBEngineID);
		static int ctAvailCheck(pRCESMasterProvider masterProv, FCPool<RCESMasterConnPooled> *connPool, int availGroupID, bool checkConn, ppRCESAvailGroup *availGroupList, int *availGroupCount, int *actionID);
		static int ctAvailCheck(pRCESMasterProvider masterProv, FCPool<RCESMasterConnPooled> *connPool, int availGroupID, bool checkConn, ppRCESJson result);
		static void ctAvailConnCheck(pRCESMasterProvider masterProv, pRCESAvailGroup availGroup);
		static void ctAvailSwitchReplica(pRCESMasterProvider masterProv, FCPool<RCESMasterConnPooled> *masterConnPool, int availGroupID);
		static pRCESReplica ctGetRestorePrimaryReplica(pRCESAvailGroup availGroup, int recoverOrder, int newPrimaryDBEngineID);

		/* Public Methods */
		pRCESAvailGroup GetAvailGroup() { return _availGroup; };

	private:
		/* Private properties */
		pRCESMasterProvider _provider;
		pRCESAvailGroup _availGroup;

		/* Private methods */
		void Deploy(FCPool<RCESMasterConnPooled> *connPool, int *actionID);
		void Start(FCPool<RCESMasterConnPooled> *connPool, bool ignoreDeploy, int *actionID);
		void Stop(FCPool<RCESMasterConnPooled> *connPool, int *actionID, bool updateStatus = true);
		void Restore(FCPool<RCESMasterConnPooled> *connPool, int recoverOrder, int newPrimaryDBEngineID);
		void Switch(FCPool<RCESMasterConnPooled> *connPool, int isFailingOver);
		void Check();

		void _checkReplicas();
		void _updatePrimary(char *statusMsg);
		int _getReplicaDatabaseID(pRCESMasterProvider masterProv, int replicaDBEngineID, const char *pubDatabaseName);
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESFailOver *pRCESFailOver, **ppRCESFailOver;

#endif /* _FCRCESFAILOVER_HPP_ */