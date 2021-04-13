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

#ifndef _FCRCESREPLAGENTMNGR_HPP_
#define _FCRCESREPLAGENTMNGR_HPP_

#include "fc_rces.h"
#include "fcrcesaux.hpp"
#include "fcrcesconfig.hpp"
#include "fcrcesreplagentdata.hpp"

/* Class type definitions */
class RCESReplAgentMngr;
typedef RCESReplAgentMngr *pRCESReplAgentMngr, **ppRCESReplAgentMngr;

/* External functions defined in the data provider dynamic library */
int RCESStartReplAgent(pAgentThrdData agentThrdData, void **agentThrdHandle);
int RCESCheckReplConnected(pAgentThrdData agentThrdData);

int RCESDPReplStartByCfg(pRCESReplAgentMngr replAgentMngr, const char *cfgFileName, char **errorMsg);
int RCESDPReplStopByCfg(pRCESReplAgentMngr replAgentMngr, char **errorMsg);
void RCESDPReplFreeByCfg(pRCESReplAgentMngr replAgentMngr);

/*^****************************************************************************\
*
*   RCESRepLAgentMngr
*   Recon-e-Sense replication agent manager class
*
*   Replication Agent manager class
*
\******************************************************************************/
class RCESReplAgentMngr
{
	public:
		/* Constructors & destructor */
		RCESReplAgentMngr(pRCESConfig config, const char *cfgFileName);
		virtual ~RCESReplAgentMngr();

		/* Public services */
		static int ctGetReplAgentMngr(pRCESConfig config, const char *cfgFileName, void *localServerData, ppRCESReplAgentMngr replAgentMngr, char **errorMsg);

		/* Public methods */
		void Start();
		void Stop();
		bool Check();
		void StartReplAgent();

		const char *GetCfgFileName() { return _cfgFileName; };
		void **GetReplAgentDataList() { return _replAgentData ? _replAgentData->replAgentDatatList : NULL; };
		pAgentThrdData *GetThrdDataList() { return _replAgentData ? _replAgentData->agentThrdData : NULL; };
		void **GetThrdHandleList() { return _replAgentData ? _replAgentData->agentThrdHandle : NULL; };
		void *GetInitReplAgentData() { return _initReplAgentData; };

		void SetInitReplAgentData(void *replAgentData) { _initReplAgentData = replAgentData; };

		virtual void LockMutex() { fcMutexGet(_hReplAgentMutex); };
		virtual void FreeMutex() { fcMutexRel(_hReplAgentMutex); };

	private:
		/* Private properties */
		char *_cfgFileName;
		void *_initReplAgentData;
		pReplicationAgentData _replAgentData;
		pRCESConfig _config;
		void *_hReplAgentMutex;

		/* private methods */
		void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESREPLAGENTMNGR_HPP_ */