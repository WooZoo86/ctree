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

#ifndef _FCRCESREPLICASTATUS_HPP_
#define _FCRCESREPLICASTATUS_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
	#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESReplicaStatus;
class RCESMasterProvider;
class RCESIp;
typedef RCESReplicaStatus *pRCESReplicaStatus, **ppRCESReplicaStatus;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;
typedef RCESIp *pRCESIp, **ppRCESIp;

#define RCES_REPLICASTATUS_LIST "replicaStatusList"
#define RCES_REPLICASTATUS_DBENGINE "dbEngine"
#define RCES_REPLICASTATUS_STATUS "status"
#define RCES_REPLICASTATUS_STATUS_CODE "statusCode"
#define RCES_REPLICASTATUS_ISPRIMARY "isPrimary"
#define RCES_REPLICASTATUS_ISSYNC "isSync"
#define RCES_REPLICASTATUS_LATENCY "latency"
#define RCES_REPLICASTATUS_RECOVERORDER "recoverOrder"
#define RCES_REPLICASTATUS_TRANSACTIONID "transactionID"
#define RCES_REPLICASTATUS_NAME "name"
#define RCES_REPLICASTATUS_HOST "hostname"
#define RCES_REPLICASTATUS_IPLIST "ipList"
#define RCES_REPLICASTATUS_ISSQL "isSQL"
#define RCES_REPLICASTATUS_PORTNBR "portNbr"
#define RCES_REPLICASTATUS_SQLPORTNBR "sqlPortNbr"
#define RCES_REPLICASTATUS_ACCEPTCONN "acceptConn"
#define RCES_REPLICASTATUS_READONLY "readOnly"

/*^****************************************************************************\
*
*   RCESReplicaStatus
*   Recon-e-Sense Replica Status class
*
\******************************************************************************/
class RCESReplicaStatus
{
public:
	/* Constructors & destructor */
	RCESReplicaStatus();
	RCESReplicaStatus(pRCESReplicaStatus replicaStatus);
	RCESReplicaStatus(pRCESJson replicaStatus);
	virtual ~RCESReplicaStatus();

	/* Public services */

	/* Public methods */
	int GetDBEngineID() { return _dbEngineID; };
	RCESEngineStatus GetStatus() { return _status; };
	bool IsPrimary() { return _isPrimary; };
	bool IsSync() { return _isSync; };
	int GetLatency() { return _latency; };
	int GetRecoverOrder() { return _recoverOrder; };
	const char *GetTransactionID() { return _transactionID; };
	char *GetName() { return _name; };
	char *GetHost() { return _host; };
	ppRCESIp GetIPAddressList() { return _ipList; };
	int GetIPAddressCount() { return _ipCount; };
	bool GetIsSQL() { return _isSQL; };
	int GetPortNumber() { return _portNumber; };
	int GetSqlPortNumber() { return _sqlPortNumber; };
	bool GetAcceptConn() { return _acceptConn; };
	RCESReadOnly GetReadOnly() { return _readOnly; };

	void SetDBEngineID(int dbEngineID) { _dbEngineID = dbEngineID; };
	void SetStatus(RCESEngineStatus status) { _status = status; };
	void SetIsPrimary(bool isPrimary) { _isPrimary = isPrimary; };
	void SetIsSync(bool isSync) { _isSync = isSync; };
	void SetLatency(int latency) { _latency = latency; };
	void SetRecoverOrder(int recoverOrder) { _recoverOrder = recoverOrder; };
	void SetTransactionID(const char *transactionID);
	void SetName(const char *name);
	void SetHost(const char *host);
	void SetIPAddressList(ppRCESIp ipList) { _ipList = ipList; };
	void SetIPAddressCount(int ipCount) { _ipCount = ipCount; };
	void SetIsSQL(bool isSQL) { _isSQL = isSQL; };
	void SetPortNumber(int portNumber) { _portNumber = portNumber; };
	void SetSqlPortNumber(int sqlPortNumber) { _sqlPortNumber = sqlPortNumber; };
	void SetAcceptConn(bool acceptConn) { _acceptConn = acceptConn; };
	void SetReadOnly(RCESReadOnly readOnly) { _readOnly = readOnly; };

	pRCESJson GetJson();

private:
	/* private methods */
	void _init();

	/* Private properties */
	int _dbEngineID;
	RCESEngineStatus _status;
	bool _isPrimary;
	bool _isSync;
	int _latency;
	int _recoverOrder;
	char *_transactionID;
	char *_name;
	char *_host;
	ppRCESIp _ipList;
	int _ipCount;
	bool _isSQL;
	int _portNumber;
	int _sqlPortNumber;
	bool _acceptConn;
	RCESReadOnly _readOnly;
};
/*~****************************************************************************/

#endif /* _FCRCESREPLICASTATUS_HPP_ */