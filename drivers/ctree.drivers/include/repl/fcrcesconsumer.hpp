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

#ifndef _FCRCESCONSUMER_HPP_
#define _FCRCESCONSUMER_HPP_

#include "fc_rces.h"
#include "fcrcesmasterprov.hpp"
#include "fcrcesactionexec.hpp"

/* Class type definitions */
class RCESConn;
class RCESExecutor;
class RCESConsumer;
class RCESConsumerMngr;
typedef RCESConn *pRCESConn, **ppRCESConn;
typedef RCESExecutor *pRCESExecutor, **ppRCESExecutor;
typedef RCESConsumer *pRCESConsumer, **ppRCESConsumer;
typedef RCESConsumerMngr *pRCESConsumerMngr, **ppRCESConsumerMngr;

typedef struct ConsumerThrdData {
	char errorMsg[RCES_MAX_ERRMSG_LEN + 1];
	int errorCode;
	RCESThrdState state;
	pRCESConsumerMngr consumerMngr;
} ConsumerThrdData, *pConsumerThrdData, **ppConsumerThrdData;

/*^****************************************************************************\
*
*   RCESConsumer
*   Recon-e-Sense consumer class
*
\******************************************************************************/
class rcesEXPORT RCESConsumer
{
	public:
		/* Constructors & destructor */
		RCESConsumer( FCPool<RCESMasterConnPooled> *masterConnPool, FCCache<RCESVolume> *volumeCache, pRCESActionQueueCriteria queueCriteria, RCESConsumerType consumerType, const char *libName, int osID, int agentID, 
		              pRCESReplPlanMngr replPlanMngr, FCHashTable<RCESConsumer> *consumerList, void *localServerData );
		virtual ~RCESConsumer();

		/* Public services */
		static int ctStartConsumer( FCPool<RCESMasterConnPooled> *masterConnPool, FCCache<RCESVolume> *volumeCache, pRCESActionQueueCriteria queueCriteria, RCESConsumerType consumerType, const char *libName, 
		                            int threadCount, int osID, int agentID, pRCESReplPlanMngr replPlanMngr, FCHashTable<RCESConsumer> *consumerList, void *localServerData, char **errorMsg );
		static int ctStopConsumer( FCHashTable<RCESConsumer> *consumerList, RCESConsumerType consumerType, int replPlanID, FCPool<RCESMasterConnPooled> *masterConnPool,
		                           char **errorMsg );
		static int ctCheckConsumer( FCHashTable<RCESConsumer> *consumerList, RCESConsumerType consumerType, int replPlanID, FCPool<RCESMasterConnPooled> *masterConnPool,
		                            char **errorMsg );

		/* Public methods */
		void Start( int threadCount = 1 );
		void Stop();
		bool IsOk();
		int GetErrorCode();
		const char *GetErrorMsg();
		pRCESExecutor GetExecutor() { return _executor; };
		RCESConsumerType GetConsumerType() { return _consumerType; };
		int GetOSID() { return _osID; };
		int GetAgentID() { return _agentID; };
		pRCESReplPlanMngr GetReplPlanMngr() { return _replPlanMngr; };
		void CleanCriteria() { _queueCriteria = NULL; };

	private:
		/* Private properties */
		RCESConsumerType _consumerType;
		int _osID;
		int _agentID;
		pRCESReplPlanMngr _replPlanMngr;
		pRCESExecutor _executor;
		pRCESActionQueueCriteria _queueCriteria;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   RCESConsumerMngr
*   Recon-e-Sense consumer manager class
*
\******************************************************************************/
class rcesEXPORT RCESConsumerMngr
{
public:
	/* Public services */
	static void ctCleanUncomplete(pRCESConn replConn, int agentID);

	/* Constructors & destructor */
	RCESConsumerMngr(pRCESConfig config);
	virtual ~RCESConsumerMngr();

	/* Public methods */
	void StopAllConsumers(FCPool<RCESMasterConnPooled> *connPool);
	void StartConsumerThread();
	void StopConsumerThread();
	int CheckConsumerThread();
	void CleanCriteria();

	FCHashTable<RCESConsumer> *GetConsumerList() { return _consumerList; };
	pRCESActionQueueCriteria GetCriteria() { return _criteria; };
	pRCESConfig GetConfig() { return _config; };

	void SetCriteria(pRCESActionQueueCriteria criteria) { _criteria = criteria; };

private:
	/* Private properties */
	pRCESConfig _config;
	FCHashTable<RCESConsumer> *_consumerList;
	pConsumerThrdData _consumerThrdDataRead;
	pRCESActionQueueCriteria _criteria;
	void *_hMutex;
};
/*~****************************************************************************/

#endif /* _FCRCESCONSUMER_HPP_ */