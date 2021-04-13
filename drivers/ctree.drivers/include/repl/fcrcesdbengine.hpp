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

#ifndef _FCRCESDBENGINE_HPP_
#define _FCRCESDBENGINE_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"
#include "fcrcesconfig.hpp"
#include "fcrcesip.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESDBEngine;
typedef RCESDBEngine *pRCESDBEngine, **ppRCESDBEngine;

#define RCES_DBENGINE_LIST "dbEngineList"
#define RCES_DBENGINE_STATUS_LIST "dbEngineStatusList"
#define RCES_DBENGINE "dbEngine"
#define RCES_DBENGINE_ID "id"
#define RCES_DBENGINE_OS "opSystem" 
#define RCES_DBENGINE_VOLUME "volume"
#define RCES_DBENGINE_NAME "name"
#define RCES_DBENGINE_WORKINGVOLUME "workingVolume"
#define RCES_DBENGINE_WORKINGVOLUME_NAME "workingVolumeName"
#define RCES_DBENGINE_WORKINGDIR "workingDir"
#define RCES_DBENGINE_STATUS "status"
#define RCES_DBENGINE_STATUS_CODE "statusCode"
#define RCES_DBENGINE_DESCRIPTION "description"
#define RCES_DBENGINE_AUTHCONTENT "authContent"
#define RCES_DBENGINE_ISSQL "isSQL"
#define RCES_DBENGINE_PORTNBR "portNbr"
#define RCES_DBENGINE_SQLPORTNBR "sqlPortNbr"
#define RCES_DBENGINE_LOCALVOLUME "localVolume"
#define RCES_DBENGINE_LOCALVOLUME_NAME "localVolumeName"
#define RCES_DBENGINE_LOCALDIR "localDir"
#define RCES_DBENGINE_USERS "users"
#define RCES_DBENGINE_STATUSTIME "statusTime"
#define RCES_DBENGINE_LASTCHECKTIME "lastCheckTime"
#define RCES_DBENGINE_RELEASEVERSION "releaseVersion"
#define RCES_DBENGINE_SERIAL "serial"
#define RCES_DBENGINE_LICENSEOEM "licenseOEM"
#define RCES_DBENGINE_LICENSETYPE "licenseType"
#define RCES_DBENGINE_LICENSECPUNBR "licenseCPUNbr"
#define RCES_DBENGINE_LICENSESERVERTYPE "licenseServerType"
#define RCES_DBENGINE_LICENSEUSERNBR "licenseUserNbr"
#define RCES_DBENGINE_ISAGENT "isAgent"
#define RCES_DBENGINE_LOGICALNAME "logicalName"
#define RCES_DBENGINE_LOGIN "login"
#define RCES_DBENGINE_PASS "pass"
#define RCES_DBENGINE_TOTAL "total"
#define RCES_DBENGINE_RECURSIVE "recursive"
#define RCES_DBENGINE_REPLNODEID "replNodeID"
#define RCES_DBENGINE_CHECKDB "checkDB"
#define RCES_DBENGINE_CHECKCONN "checkConnection"
#define RCES_DBENGINE_MANAGED "managed"
#define RCES_DBENGINE_ACTIONID "actionID"
#define RCES_DBENGINE_CONNBYIP "isConnectByIP"
#define RCES_DBENGINE_IPADDRESS "ipAddress"
#define RCES_DBENGINE_IPLIST "ipList"
#define RCES_DATABASE_IPLIST "databaseList"
#define RCES_DBENGINE_BASIC "basic"
#define RCES_DBENGINE_ACCEPTCONN "acceptConn"
#define RCES_DBENGINE_READONLY "readOnly"
#define RCES_DBENGINE_ISMEMPHIS "isMemphis"
#define RCES_DBENGINE_WEBSERVERCONFIG "WebServerConfig"

/* DBEngine status values */
#define RCES_DBENGINE_INACTIVE   "inactive"
#define RCES_DBENGINE_ACTIVE     "active"
#define RCES_DBENGINE_STOPPING   "stopping"
#define RCES_DBENGINE_STARTING   "starting"
#define RCES_DBENGINE_CHECKING   "checking"
#define RCES_DBENGINE_WARNING    "warning"
#define RCES_DBENGINE_ERROR      "error"
#define RCES_DBENGINE_UNMANAGED  "unmanaged"

#define RCES_DBENGINE_FILENAME "dbEngine.json"

/*^****************************************************************************\
*
*   RCESDBEngine
*   Recon-e-Sense database engine class
*
\******************************************************************************/
class RCESDBEngine
{
public:
	/* Constructors & destructor */
	RCESDBEngine();
	RCESDBEngine(pRCESDBEngine dbEngine);
	RCESDBEngine(pRCESJson dbEngine);
	virtual ~RCESDBEngine();

	/* Public services */
	static int ctGetDBEngines(pRCESMasterProvider masterProv, int osID, int dbEngineListSize, int dbEngineStart, ppRCESDBEngine *dbEngineList, int *dbEngineCount, int *totalDBEngines);
	static int ctGetDBEngines(pRCESMasterProvider masterProv, int osID, bool basic, bool isPaging, int dbEngineListSize, int dbEngineStart, ppRCESJson result);
	static int ctGetDBEnginesByVolume(pRCESMasterProvider masterProv, int volumeID, int dbEngineListSize, int dbEngineStart, ppRCESDBEngine *dbEngineList, int *dbEngineCount, int *totalDBEngines);
	static int ctGetDBEnginesByVolume(pRCESMasterProvider masterProv, int volumeID, bool basic, bool isPaging, int dbEngineListSize, int dbEngineStart, ppRCESJson result);
	static int ctGetDBEngine(pRCESMasterProvider masterProv, int dbEngineID, ppRCESDBEngine dbEngine);
	static int ctGetDBEngine(pRCESMasterProvider masterProv, int dbEngineID, bool basic, bool isPaging, ppRCESJson result);
	static int ctGetDBEngine(pRCESMasterProvider masterProv, int osID, int workingVolume, const char *workingDir, ppRCESDBEngine dbEngine);
	static int ctGetDBEngine(pRCESMasterProvider masterProv, int osID, int workingVolume, const char *workingDir, bool basic, bool isPaging, ppRCESJson result);
	static int ctPersistDBEngine(pRCESMasterProvider masterProv, pRCESDBEngine dbEngine);
	static int ctPersistDBEngine(pRCESMasterProvider masterProv, pRCESJson dbEngine, bool checkDB, ppRCESJson result);
	static int ctRemoveDBEngine(pRCESMasterProvider masterProv, int dbEngineID, bool recursive);
	static int ctRemoveDBEngine(pRCESMasterProvider masterProv, int dbEngineID, bool recursive, ppRCESJson result);
	static int ctAuthDBEngine(pRCESMasterProvider masterProv, int dbEngineID, const char *login, const char *pass);
	static int ctAuthDBEngine(pRCESMasterProvider masterProv, int dbEngineID, const char *login, const char *pass, ppRCESJson result);
	static int ctCheckDBEngineStatus(pRCESMasterProvider masterProv, int dbEngineID, bool checkConn, ppRCESDBEngine *dbEngineList, int *dbEngineCount, int *actionID = NULL);
	static int ctCheckDBEngineStatus(pRCESMasterProvider masterProv, int dbEngineID, bool checkConn, ppRCESJson result);
	static int ctSetDBEngineManaged(pRCESMasterProvider masterProv, int dbEngineID, bool managed);
	static int ctSetDBEngineManaged(pRCESMasterProvider masterProv, int dbEngineID, bool managed, ppRCESJson result);
	static int ctSetDBEngineAcceptConn(pRCESMasterProvider masterProv, int dbEngineID, bool acceptConn);
	static int ctSetDBEngineAcceptConn(pRCESMasterProvider masterProv, int dbEngineID, bool acceptConn, ppRCESJson result);
	static int ctSetDBEngineReadOnly(pRCESMasterProvider masterProv, int dbEngineID, bool readOnly);
	static int ctSetDBEngineReadOnly(pRCESMasterProvider masterProv, int dbEngineID, bool readOnly, ppRCESJson result);
	static int ctSetDBEngineConnByIP(pRCESMasterProvider masterProv, int dbEngineID, bool connByIP);
	static int ctSetDBEngineConnByIP(pRCESMasterProvider masterProv, int dbEngineID, bool connByIP, ppRCESJson result);
	static int ctStartDBCheckThread(pRCESMasterProvider masterProv, int osID, char **errorMsg);
	static int ctStopDBCheckThread(char **errorMsg);
	static int ctCheckDBEngine(pRCESMasterProvider masterProv, pRCESDBEngine dbEngine, pRCESThrdState thrdState);
	static int ctSetDBEngineStatus(pRCESConfig config, pRCESMasterProvider masterProv, FCPool<RCESMasterConnPooled> *masterProvConnPool, pRCESDBEngine dbEngine, RCESEngineStatus status, bool managed);
	static int ctCheckDBEngineConn(pRCESMasterProvider masterProv, FCPool<RCESMasterConnPooled> *masterConnPool, int timeout, ppRCESDBEngine dbEngine, ppRCESDBEngineMngr dbEngineMngr = NULL);

	static const char *GetStatusStr(RCESEngineStatus status);
	static RCESEngineStatus GetStatusFromStr(const char *statusStr);	
	static const char *GetReadOnlyStr(RCESReadOnly readonly);
	static RCESReadOnly GetReadOnlyFromStr(const char *readonlyStr);

	static pRCESDBEngine ctLoadFromDisk(pRCESConfig config);

	/* Public methods */
	int GetID() { return _id; };
	int GetOSID() { return _osID; };
	char *GetName() { return _name; };
	RCESEngineStatus GetStatus() { return _status; };
	RCESDateTime GetStatusTime() { return _statusTime; };
	RCESDateTime GetLastCheckTime() { return _lastCheckTime; };
	char *GetHost() { return _host; };
	char *GetDescription() { return _description; };
	char *GetAuthContent() { return _authContent; };
	int GetWorkingVolume() { return _workingVolume; };
	char *GetWorkingDir() { return _workingDir; };
	char *GetUser() { return _userName; };
	char *GetUserPass() { return _userPass; };
	char *GetServName();
	char *GetServNameByIP(const char *ipAddress = NULL);
	char *GetServiceName() { return _serviceName; };
	char *GetExeName() { return _exeName; };
	bool GetIsSQL() { return _isSQL; };
	int GetPortNumber() { return _portNumber; };
	int GetSqlPortNumber() { return _sqlPortNumber; };
	int GetLocalVolume() { return _localVolume; };
	char *GetLocalDir() { return _localDir; };
	int GetUsers() { return _users; };
	char *GetVersion() { return _version; };
	char *GetSerial() { return _serial; };
	int GetLicenseOEM() { return _licenseOEM; };
	char *GetLicenseType() { return _licenseType; };
	int GetLicenseCPUNbr() { return _licenseCPUNbr; };
	char *GetLicenseServerType() { return _licenseServerType; };
	int GetLicenseUserNumber() { return _licenseUserNumber; };
	char *GetWorkingVolumeName() { return _workingVolumeName; };
	char *GetLocalVolumeName() { return _localVolumeName; };
	char *GetFullDataPath();
	bool GetIsAgent() { return _isAgent; };
	char *GetLogicalName() { return _logicalName; };
	void GetAuthInfo();
	bool IsMaster() { return _isMaster; };
	char *GetReplNodeID() { return _replNodeID; };
	bool IsConnectByIP() { return _connectByIP; };
	char *GetIPAddress() { return _ipAddress; };
	ppRCESIp GetIPAddressList() { return _ipList; };
	int GetIPAddressCount() { return _ipCount; };
	bool GetAcceptConn() { return _acceptConn; };
	RCESReadOnly GetReadOnly() { return _readOnly; };
	const char *GetReadOnlyName() { return RCESDBEngine::GetReadOnlyStr(_readOnly); };
	bool IsMemphis(pRCESConfig config) { return _osID == config->GetMasterOS() && !fcstricmp(_name, config->GetParam(MEMPHIS_SERVER_NAME)); };
	const char *GetWebServerConfig() { return _webServerConfig; };

	void SetID(int id) { _id = id; };
	void SetOSID(int osID) { _osID = osID; };
	void SetName(const char *name);
	void SetStatus(RCESEngineStatus status) { _status = status; };
	void SetStatusTime(RCESDateTime statusTime) { _statusTime = statusTime; };
	void SetLastCheckTime(RCESDateTime lastCheckTime) { _lastCheckTime = lastCheckTime; };
	void SetHost(const char *host);
	void SetDescription(const char *description);
	void SetWorkingVolume(int workingVolume) { _workingVolume = workingVolume; };
	void SetWorkingDir(const char *workingDir) { if (workingDir) strncpy(_workingDir, workingDir, RCES_MAX_PATH); else _workingDir[0] = 0; };
	void SetAuthContent(const char *authContent);
	void SetIsSQL(bool isSQL) { _isSQL = isSQL; };
	void SetPortNumber(int portNumber) { _portNumber = portNumber; };
	void SetSqlPortNumber(int sqlPortNumber) { _sqlPortNumber = sqlPortNumber; };
	void SetLocalVolume(int localVolume) { _localVolume = localVolume; };
	void SetLocalDir(const char *localDir);
	void SetUsers(int users) { _users = users; };
	void SetVersion(const char *version);
	void SetSerial(const char *serial);
	void SetLicenseOEM(int licenseOEM) { _licenseOEM = licenseOEM; };
	void SetLicenseType(const char *licenseType);
	void SetLicenseCPUNbr(int licenseCPUNbr) { _licenseCPUNbr = licenseCPUNbr; };
	void SetLicenseServerType(const char *licenseServerType);
	void SetLicenseUserNumber(int licenseUserNumber) { _licenseUserNumber = licenseUserNumber; };
	void SetWorkingVolumeName(const char *workingVolumeName);
	void SetLocalVolumeName(const char *localVolumeName);
	void SetUserName(const char *userName);
	void SetUserPass(const char *userPass);
	void SetIsAgent(bool isAgent) { _isAgent = isAgent; };
	void SetLogicalName(const char *logicalName);
	void SetIsMaster(bool isMaster) { _isMaster = isMaster; };
	void SetReplNodeID(const char *replNodeID);
	void SetIsConnectByIP(bool connectByIP) { _connectByIP = connectByIP; };
	void SetIPAddress(char *ipAddress);
	void SetIPAddressList(ppRCESIp ipList) { _ipList = ipList; };
	void SetIPAddressCount(int ipCount) { _ipCount = ipCount; };
	void SetAcceptConn(bool acceptConn) { _acceptConn = acceptConn; };
	void SetReadOnly(RCESReadOnly readOnly) { _readOnly = readOnly; };
	void SetWebServerConfig(char *webServerConfig);

	pRCESJson GetJson(bool basic, pRCESMasterProvider provider = NULL);
	void Update(pRCESJson dbEnginePatch);
	pRCESJson GetStatusJson(pRCESMasterProvider provider = NULL);
	void Copy(pRCESDBEngine dbEngine);
	void DumpToDisk(pRCESConfig config);

	virtual void LockMutex() {};
	virtual void FreeMutex() {};

protected:
	/* Protected properties */
	int _id;
	int _osID;
	char *_name;
	RCESEngineStatus _status;
	RCESDateTime _statusTime;
	RCESDateTime _lastCheckTime;
	char *_description;
	char *_host;
	char *_authContent;
	int _workingVolume;
	char _workingDir[RCES_MAX_PATH + 1];
	char _serviceName[RCES_MAX_PATH + 1];
	char _exeName[RCES_MAX_PATH + 1];
	char *_userName;
	char *_userPass;
	char _servName[RCES_MAX_SERVNAME + 1];
	char _servNameByIP[RCES_MAX_SERVNAME + 1];
	bool _isSQL;
	int _portNumber;
	int _sqlPortNumber;
	int _localVolume;
	char *_localDir;
	int _users;
	char *_version;
	char *_serial;
	int _licenseOEM;
	char *_licenseType;
	int _licenseCPUNbr;
	char *_licenseServerType;
	int _licenseUserNumber;
	char *_workingVolumeName;
	char *_localVolumeName;
	bool _isAgent;
	char *_logicalName;
	bool _isMaster;
	char *_replNodeID;
	bool _connectByIP;
	char *_ipAddress;
	ppRCESIp _ipList;
	int _ipCount;
	bool _acceptConn;
	RCESReadOnly _readOnly;
	char *_webServerConfig;

	/* Protected methods */
	void _buildServName();
	void _buildServNameByIP(const char *ipAddress = NULL);

private:
	/* Private methods */
	void _init();

	char _fullDataPath[RCES_MAX_PATH + 1];
};
/*~****************************************************************************/

#endif /* _FCRCESDBENGINE_HPP_ */