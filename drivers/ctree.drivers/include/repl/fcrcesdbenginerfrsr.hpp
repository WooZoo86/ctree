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

#ifndef _FCRCESDBENGINERFRSR_HPP_
#define _FCRCESDBENGINERFRSR_HPP_

#include "fc_rces.h"
#include "fcrcesaux.hpp"
#include "fcrcesdbengine.hpp"
#include "fcrceslocalprov.hpp"

#define DB_DICT_FREQ_REFRESHER 5

/* Class type definitions */
class RCESDBEngineRfrsr;
typedef RCESDBEngineRfrsr *pRCESDBEngineRfrsr, **ppRCESDBEngineRfrsr;

/* External functions defined in the data provider dynamic library */
int RCESDBInitDictCBThrd(pRCESDBEngineRfrsr dbEngineRfrsr, ppDictCBThrdData dictCBThrdData, void **dictCBThrdHandle, char **errorMsg );
void RCESDBTermDictCBThrd(pDictCBThrdData dictCBThrdData, void *dictCBThrdHandle);

/*^****************************************************************************\
*
*   RCESDBEngineRfrsr
*   Recon-e-Sense database engine refresher class
*   Keep monitoring all dictionaries in order to keep the databases updated in
*   master server
*
\******************************************************************************/
class RCESDBEngineRfrsr : public RCESDBEngine
{
	public:
		/* Constructors & destructor */
		RCESDBEngineRfrsr(pRCESLocalProvider localProv, pRCESDBEngine dbEngine);
		virtual ~RCESDBEngineRfrsr();

		/* Public methods */
		void Start();
		void Stop();
		void Refresh();
		void StartDBListNotification();
		void StopDBListNotification();
		void CheckDBList();

		pRCESConfig GetConfig() { return _localProv->GetConfig(); };
		pDictCBThrdData GetThrdData() { return _dictCBThrdData; };
		int GetFrequence() { return _freq; };
		const char *GetQueueName() { return _queueName; };
		int GetQueueHandle() { return _queueHandle; };
		int GetCTDBDictDatno() { return _ctdbDictDatno; };
		bool IsNotified() { return _notified; };

		void SetQueueName(const char *queueName);
		void SetQueueHandle(int queueHandle) { _queueHandle = queueHandle; };
		void SetCTDBDictDatno(int ctdbDictDatno) { _ctdbDictDatno = ctdbDictDatno; };
		void SetCTDBDictName(const char *ctdbDictName);
		void SetNotified(bool notified) { _notified = notified; };
		void SetDatabaseList(ppRCESDatabase databaseList, int databaseCount) { _databaseList = databaseList; _databaseCount = databaseCount; };

	private:
		/* Private properties */
		void *_dictCBThrdHandle;
		pDictCBThrdData _dictCBThrdData;
		pRCESLocalProvider _localProv;
		int _freq;
		int _ctdbDictDatno;
		char *_ctdbDictName;
		char *_queueName;
		int _queueHandle;
		bool _notified;
		ppRCESDatabase _databaseList;
		int _databaseCount;

		/* Private methods */
		void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESDBENGINERFRSR_HPP_ */