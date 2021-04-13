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

#ifndef _FCRCESREPLICA_HPP_
#define _FCRCESREPLICA_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
	#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESReplica;
class RCESMasterProvider;
typedef RCESReplica *pRCESReplica, **ppRCESReplica;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_REPLICA_LIST "replicaList"
#define RCES_REPLICA_ISPRIMARY "isPrimary"
#define RCES_REPLICA_ISSYNC "isSyncronous"
#define RCES_REPLICA_DBENGINESTATUS "dbEngineStatus"
#define RCES_REPLICA_DBENGINE "dbEngine"
#define RCES_REPLICA_PUBLICATION "publication"
#define RCES_REPLICA_REPLPLAN "replPlan"
#define RCES_REPLICA_RECOVERORDER "recoverOrder"
#define RCES_REPLICA_TRANSACTIONID "transactionID"
#define RCES_REPLICA_NEWPRIMARY "primaryDBEngine"

/*^****************************************************************************\
*
*   RCESReplica
*   Recon-e-Sense Replica class
*
\******************************************************************************/
class RCESReplica
{
	public:
		/* Constructors & destructor */
		RCESReplica();
		RCESReplica(pRCESReplica replica);
		RCESReplica(pRCESJson replica);
		virtual ~RCESReplica();

		/* Public services */

		/* Public methods */
		int GetAvailGroupID() { return _availGroupID; };
		int GetDBEngineID() { return _dbEngineID; };
		int GetPublicationID() { return _publicationID; };
		int GetReplPlanID() { return _replPlanID; };
		bool IsSync() { return _isSync; };
		bool IsPrimary() { return _isPrimary; };
		pRCESDBEngine GetDBEngine() { return _dbEngine; };
		pRCESPublication GetPublication() { return _publication; };
		pRCESReplPlan GetReplPlan() { return _replPlan; };
		int GetRecoverOrder() { return _recoverOrder; };
		const char *GetTransactionID() { return _transactionID; };

		void SetAvailGroupID(int availGroupID) { _availGroupID = availGroupID; };
		void SetDBEngineID(int dbEngineID) { _dbEngineID = dbEngineID; };
		void SetPublicationID(int publicationID) { _publicationID = publicationID; };
		void SetReplPlanID(int replPlanID) { _replPlanID = replPlanID; };
		void SetIsSync(bool isSync) { _isSync = isSync; };
		void SetIsPrimary(bool isPrimary) { _isPrimary = isPrimary; };
		void SetDBEngine(pRCESDBEngine dbEngine) { _dbEngine = dbEngine; };
		void SetPublication(pRCESPublication publication) { _publication = publication; };
		void SetReplPlan(pRCESReplPlan replPlan);
		void SetRecoverOrder(int recoverOrder) { _recoverOrder = recoverOrder; };
		void SetTransactionID(const char *transactionID);

		pRCESJson GetJson(bool detail);

		void Check();

	private:
		/* private methods */
		void _init();

		/* Private properties */
		int _availGroupID;
		int _dbEngineID;
		int _publicationID;
		int _replPlanID;
		bool _isSync;
		bool _isPrimary;
		pRCESDBEngine _dbEngine;
		pRCESPublication _publication;
		pRCESReplPlan _replPlan;
		int _recoverOrder;
		char *_transactionID;
};
/*~****************************************************************************/

#endif /* _FCRCESREPLICA_HPP_ */