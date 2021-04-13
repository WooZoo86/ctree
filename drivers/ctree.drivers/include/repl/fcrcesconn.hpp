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

#ifndef _FCRCESCONN_HPP_
#define _FCRCESCONN_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrceslogger.hpp"
#include "fcrcesmasterprov.hpp"
#include "fcrceslocalprov.hpp"
#include "fcrcesmasterconfig.hpp"

 /* Class type definitions */
class RCESConn;
class RCESConsumer;
typedef RCESConn *pRCESConn, **ppRCESConn;
typedef RCESConsumer *pRCESConsumer, **ppRCESConsumer;

/*^****************************************************************************\
 *
 *   RCESConn
 *   Recon-e-Sense connection class
 *
 *   Manages the master database connection and associated logger and config
 *   objects
 *
\******************************************************************************/
class RCESConn
{
public:

	/* Constructors & destructor */
	RCESConn(pRCESConfig config);
	virtual ~RCESConn();

	/* Public methods */
	void Connect();
	void ConnectMaster();
	void Disconnect();
	pRCESConfig GetConfig() { return _config; };
	pRCESLogger GetLogger() { return _logger; };
	pRCESMasterProvider GetDataProvider() { return _provider; };
	pRCESLocalProvider GetLocalProvider() { return _localProvider; };
	pRCESDynServer GetLocalServerDLL() { return _localServerDLL; };
	void SetLocalServerDLL(pRCESDynServer dynServer);
	void SetLocalClientDLL();
	void ConnectLocal();
	bool IsActive() { return _provider && _localProvider && _provider->IsActive() && _localProvider->IsActive(); };
	void StartConsumerThread();
	void SetTempConfig(bool tempConfig) { _tempConfig = tempConfig; };

	/* Public Services */
	static int ctReplConnect(pRCESConfig config, pRCESDynServer dynServer, ppRCESConn replConn, char **errorMsg);
	static int ctReplDisconnect(pRCESConn replConn);
	static int ctReplMasterConnect(pRCESConfig config, ppRCESConn replConn, char **errorMsg);
	static int ctReplLocalConnect(pRCESConn replConn, char **errorMsg);

private:
	/* Private Properties */
	pRCESLogger _logger;
	pRCESConfig _config;
	pRCESMasterConfig _masterConfig;
	pRCESMasterProvider _provider;
	pRCESLocalProvider _localProvider;
	pRCESDynServer _localServerDLL;
	bool _tempConfig;

	/* Private Methods */
};
/*~****************************************************************************/

#endif /* _FCRCESCONN_HPP_ */