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

#ifndef _FCRCESDYNSERVER_HPP_
#define _FCRCESDYNSERVER_HPP_

#include "fcrcesaux.hpp"

/* Class type definitions */
class RCESDynServer;
typedef RCESDynServer *pRCESDynServer, **ppRCESDynServer;

/* External functions defined in the data provider dynamic library */
int RCESDynServerStart(pRCESDynServer dynServer, char **errorMsg);
void RCESDynServerStop(pRCESDynServer dynServer);

typedef struct DynServerThrdData {
	void *serverData;
	void *dynServerMutex;
	char errorMsg[RCES_MAX_ERRMSG_LEN+1];
	int errorCode;
} DynServerThrdData, *pDynServerThrdData, **ppDynServerThrdData;

/*^****************************************************************************\
*
*   RCESDynServer
*   Recon-e-Sense dynamic server management
*
\******************************************************************************/
class RCESDynServer
{
public:
	/* Constructors & destructor */
	RCESDynServer(pRCESConfig config);
	virtual ~RCESDynServer();

	/* Public methods */
	void Start();
	void Stop();
	void *GetDynServerMutex() { return _hDynServerMutex; };
	void *GetServerData() { return _serverData; };
	pDynServerThrdData GetThrdData() { return _dynServerThrdData; };
	void *GetThrdHandle() { return _dynServerThrdHandle; };

	void SetServerData(void *serverData) { _serverData = serverData; };
	void SetThrdData(pDynServerThrdData dynServerThrdData) { _dynServerThrdData = dynServerThrdData; };
	void SetThrdHandle(void *dynServerThrdHandle) { _dynServerThrdHandle = dynServerThrdHandle; };

private:
	/* Private properties */
	void *_serverData;
	pDynServerThrdData _dynServerThrdData;
	void *_dynServerThrdHandle;
	void *_hDynServerMutex;
	pRCESConfig _config;

	/* private methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESDynServer *pRCESDynServer, **ppRCESDynServer;

#endif /* _FCRCESDYNSERVER_HPP_ */