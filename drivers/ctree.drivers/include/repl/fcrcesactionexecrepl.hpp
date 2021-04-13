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

#ifndef _FCRCESACTIONEXECREPL_HPP_
#define _FCRCESACTIONEXECREPL_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrcesmasterprov.hpp"
#include "fcrcesactionexecbase.hpp"

/* Class type definitions */
class RCESConsumer;
typedef RCESConsumer *pRCESConsumer, **ppRCESConsumer;

/*^****************************************************************************\
*
*   RCESActionExecRepl
*   Recon-e-Sense action executor class for generic replication actions
*
\******************************************************************************/
class RCESActionExecRepl : public RCESActionExecBase
{
public:
	/* Constructors & destructor */
	RCESActionExecRepl(pRCESActionQueueCriteria queueCriteria, FCPool<RCESMasterConnPooled> *masterConnPool,
		FCCache<RCESVolume> *volumeCache, FCHashTable<RCESConsumer> *consumerList, void *localServerData);
	virtual ~RCESActionExecRepl();

	/* Public Methods */
	void Deploy(pRCESAction action);
	void Start(pRCESAction action);
	void Stop(pRCESAction action);
	void Register(pRCESAction action);
	void RegisterSource(pRCESAction action);
	void Unregister(pRCESAction action);
	void Cancel(pRCESAction action);
	void CheckConsumers(pRCESAction action);
	void StartMonitor(pRCESAction action);
	void StopMonitor(pRCESAction action);
	void StartExcepLog(pRCESAction action);
	void StopExcepLog(pRCESAction action);
	void StartFuncTime(pRCESAction action);
	void StopFuncTime(pRCESAction action);
	void ResetFuncTime(pRCESAction action);
	void GetFuncTimes(pRCESAction action);
	void Pause(pRCESAction action);
	void Resume(pRCESAction action);
	void SetTrace(pRCESAction action);
	void CheckFailOverMngr(pRCESAction action);

	pRCESConfig GetConfig() { return _config; };

private:
	/* Private properties */
	FCHashTable<RCESConsumer> *_consumerList;
	void *_localServerData;

	/* Private methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESActionExecRepl *pRCESActionExecRepl, **ppRCESActionExecRepl;

#endif /* _FCRCESACTIONEXECREPL_HPP_ */