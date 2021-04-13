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

#ifndef _FCRCESEXECUTOR_HPP_
#define _FCRCESEXECUTOR_HPP_

#include "fcrcesaux.hpp"
#include "fcrcesactionexec.hpp"

/* Executor external function */
#define INIT "init"
#define TERM "term"
#define CREATE "create"
#define DESTROY "destroy"
#define EXECUTE "execute"
typedef int(*p_init)(FCPool<RCESMasterConnPooled> *masterConnPool);
typedef int(*p_term)();
typedef pRCESActionExecBase(*p_create)(pRCESActionQueueCriteria queueCriteria, FCPool<RCESMasterConnPooled> *masterConnPool, FCCache<RCESVolume> *volumeCache, FCHashTable<RCESConsumer> *consumerList, void *localServerData,
	pRCESReplPlanMngr replPlanMngr, int *errorCd, char *errorMsg);
typedef void(*p_destroy)(pRCESActionExecBase actionExec);
typedef int(*p_execute)(pRCESActionExecBase actionExec, pRCESAction action, char *errorMsg);

/* Class type definitions */
class RCESActionExec;
class RCESExecutor;
typedef RCESActionExec *pRCESActionExec, **ppRCESActionExec;
typedef RCESExecutor *pRCESExecutor, **ppRCESExecutor;

#ifdef NCTREE_FILE_SUPPORT
class RCESNotifNCtree;
typedef RCESNotifNCtree *pRCESNotifNCtree, **ppRCESNotifNCtree;
#endif

typedef struct ProcThrdData {
	char errorMsg[RCES_MAX_ERRMSG_LEN+1];
	int errorCode;
	pRCESReplPlanMngr replPlanMngr;
#ifdef NCTREE_FILE_SUPPORT
	FCHashTable<RCESNotifNCtree> *notifList;
#endif
	pRCESConfig config;
	RCESThrdState state;
	FCHashTable<RCESConsumer> *consumerList;
	void *localServerData;
	void *procMutex;
	pRCESActionExec actionExec;
	FCHashTable<RCESAction> *actionRequestList;
	FCHashTable<RCESAction> *actionResultList;
	pRCESExecutor executor;
	FCPool<RCESMasterConnPooled> *masterConnPool;
	FCCache<RCESVolume> *volumeCache;
} ProcThrdData, *pProcThrdData, **ppProcThrdData;

/*^****************************************************************************\
*
*   RCESExecutor
*   Recon-e-Sense executor class
*
\******************************************************************************/
class RCESExecutor
{
	public:
		/* Constructors & destructor */
		RCESExecutor( FCPool<RCESMasterConnPooled> *masterConnPool, FCCache<RCESVolume> *volumeCache, pRCESActionQueueCriteria queueCriteria, 
		              pRCESReplPlanMngr replPlanMngr, FCHashTable<RCESConsumer> *consumerList, void *localServerData, RCESConsumerType consumerType, const char *libName );
		virtual ~RCESExecutor();

		/* Public services */
		static int ctPushActionRequest( FCHashTable<RCESConsumer> *consumerList, pRCESAction action, char **errorMsg );

		/* Public methods */
		void PushActionRequest( pRCESAction action );
		pRCESAction PullActionRequest();
		bool IsOk() { return GetErrorCode() == RCES_SUCCESS; };
		void Start( int threadCount = 1 );
		void Stop();
		const char *GetErrorMsg();
		int GetErrorCode();
		pRCESActionQueueCriteria GetQueueCriteria() { return _queueCriteria; };
		RCESConsumerType GetConsumerType() { return _consumerType; };

		int Execute(pRCESActionExecBase actionExec, pRCESAction action, char *errorMsg) { return (*_execute)(actionExec, action, errorMsg); };
		void Destroy(pRCESActionExecBase actionExec) { return (*_destroy)(actionExec); };
		pRCESActionExecBase Create(pRCESActionQueueCriteria queueCriteria, FCPool<RCESMasterConnPooled> *masterConnPool, FCCache<RCESVolume> *volumeCache, FCHashTable<RCESConsumer> *consumerList, void *localServerData, 
			                       pRCESReplPlanMngr replPlanMngr, int *errorCd, char *errorMsg) {
			return (*_create)(queueCriteria, masterConnPool, volumeCache, consumerList, localServerData, replPlanMngr, errorCd, errorMsg);
		};

	private:
		/* Private properties */
		pRCESConfig _config;
		void *_hProcMutex;
		pRCESReplPlanMngr _replPlanMngr;
		FCHashTable<RCESConsumer> *_consumerList;
		pRCESActionQueueCriteria _queueCriteria;
		void *_localServerData;
		FCPool<RCESMasterConnPooled> *_masterConnPool;
		FCCache<RCESVolume> *_volumeCache;
		RCESConsumerType _consumerType;

		int _procThrdCount;
		ppProcThrdData _procThrdListData;

		FCList<RCESAction> *_actionRequestList;

		p_init _init;
		p_term _term;
		p_create _create;
		p_destroy _destroy;
		p_execute _execute;

#ifdef NCTREE_FILE_SUPPORT
		FCHashTable<RCESNotifNCtree> *_notifList;
		void _stopNotif();
#endif

		/* Private methods */
		void _createProcThreads( int threadCount );
		void _loadExecutorLib(const char *libName, FCPool<RCESMasterConnPooled> *masterConnPool);
};
/*~****************************************************************************/

#endif /* _FCRCESEXECUTOR_HPP_ */