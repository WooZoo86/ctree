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

#ifndef _FCREPLDBENGINE_HPP_
#define _FCREPLDBENGINE_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesdbengine.hpp"

/* Forward class declaration */
class FCREPLDBEngine;
typedef FCREPLDBEngine *pFCREPLDBEngine, **ppFCREPLDBEngine;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - DBEngine
*
\******************************************************************************/

/* EngineStatus table */
typedef enum
{
	FCREPL_NOTSUP = -1,   /* Engine invalid status                */
	FCREPL_INACTIVE = 0,  /* Engine inactive                      */
	FCREPL_ACTIVE = 1,    /* Engine active                        */
	FCREPL_STOPPING = 2,  /* Engine stopping                      */
	FCREPL_STARTING = 3,  /* Engine starting                      */
	FCREPL_CHECKING = 4,  /* Engine checking                      */
	FCREPL_DBWARNING = 5, /* Engine active with warning           */
	FCREPL_DBERROR = 6,   /* Engine unavailable                   */
	FCREPL_SWITCHING = 7, /* Switching Avail Group to new primary */
	FCREPL_UNMANAGED = 8  /* Engine unmanaged                     */
} FCREPLEngineStatus, FCREPLAgentStatus;

/*^****************************************************************************\
*
*   Function:   fcReplGetDBEngines
*               Retrieve all the DB Engines entity objects for the given OpSystem
*               identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               osID [IN]
*               OS identification
*
*               dbEngineList [OUT]
*               DBEngine entity list
*
*               dbEngineCount [OUT]
*               Number of DBEngine entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetDBEngines(pFCREPLConn replConn, int osID, ppFCREPLDBEngine *dbEngineList, int *dbEngineCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetDBEngine
*               Retrieve the DBEngine entity object by its Name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               osID [IN]
*               OS identification
*
*               workingVolume [IN]
*               Working volume
*
*               workingDir [IN]
*               Working directory
*
*               dbEngine [OUT]
*               DBEngine entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetDBEngine(pFCREPLConn replConn, int osID, int workingVolume, const char *workingDir, ppFCREPLDBEngine dbEngine);

/*^****************************************************************************\
*
*   Function:   fcReplPersistDBEngine
*               Add a DBEngine entity into the database. If there already is a
*               DBEngine with the given osID/name, update the existing record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngine [IN]
*               DBEngine entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistDBEngine(pFCREPLConn replConn, pFCREPLDBEngine dbEngine);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveDBEngine
*               Delete the DBEngine by its identification.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineId [IN]
*               DBEngine identification
*
*               recursive [IN]
*               Recursive flag
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveDBEngine(pFCREPLConn replConn, int dbEngineID, bool recursive);

/*^****************************************************************************\
*
*   Function:   fcReplAuthDBEngine
*               Creates an authentication encrypted file for the given DBEngine
*               based no the provided login/pass. It will be stored the encrypted
*               information into the DBEngine record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineId [IN]
*               DBEngine identification
*
*               login [IN]
*               DBEngine user login
*
*               pass [IN]
*               DBEngine user password
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplAuthDBEngine(pFCREPLConn replConn, int dbEngineID, const char *login, const char *pass);

/*^****************************************************************************\
*
*   Function:   fcReplCheckDBEngineStatus
*               Try to connect to the dbEngine from the Memphis server in order
*               to update its status. After validating it, returns its status.
*               In case of checkConnection for all the DBEngines, an action ID
*               is returned and the execution will happen in background.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               DBEngine identification
*
*               checkConn [IN]
*               Flag indicating that the Memphis should try to connect to the
*               DBEngine in order update the status
*
*               dbEngineList [OUT]
*               DBEngine entity list retrieved or NULL in case it doesn't want
*               to retrieve it.
*
*               dbEngineCount [OUT]
*               DBEngine entity list count.
*
*               actionID [OUT]
*               Action identification returned in case of checkConnection for 
*               all the DBEngines.
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplCheckDBEngineStatus(pFCREPLConn replConn, int dbEngineID, bool checkConn, ppFCREPLDBEngine *dbEngineList, int *dbEngineCount, int *actionID);

/*^****************************************************************************\
*
*   Function:   fcReplSetDBEngineManaged
*               Remove or restore the given DBEngine to be managed by the
*               Replication Studio system.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               DBEngine identification
*
*               managed [IN]
*               TRUE for restoring a unmanaged DBEngine or FALSE to unmanage
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplSetDBEngineManaged(pFCREPLConn replConn, int dbEngineID, bool managed);

/*^****************************************************************************\
*
*   Function:   fcReplSetDBEngineAcceptConn
*               Set if the DBEngine accepts or not external connections.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               DBEngine identification
*
*               managed [IN]
*               Flag indicating if the DBEngine can or can't accept external
*               connections
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplSetDBEngineAcceptConn(pFCREPLConn replConn, int dbEngineID, bool managed);

/*^****************************************************************************\
*
*   Function:   fcReplSetDBEngineReadOnly
*               Set the DBEngine readonly status.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineID [IN]
*               DBEngine identification
*
*               readOnly [IN]
*               Flag indicating if the DBEngine is readonly
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplSetDBEngineReadOnly(pFCREPLConn replConn, int dbEngineID, bool readOnly);

/*^****************************************************************************\
*
*   Function:   fcReplSetDBEngineStatus
*               Update current status for the given DBEngine.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               dbEngineId [IN]
*               DBEngine identification
*
*               status [IN]
*               New status
*
*               managed [IN]
*               Flag indicating that DBEngine should be restored as managed
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplSetDBEngineStatus(pFCREPLConn replConn, int dbEngineID, FCREPLEngineStatus status, bool managed);



/*^****************************************************************************\
*
*   Class:      FCREPLDBEngine
*               Represents a physical Database Server. Initially it supports
*               only c-tree type.
*
\******************************************************************************/
class FCREPL_API FCREPLDBEngine : public RCESDBEngine
{
public:
	FCREPLDBEngine();
	FCREPLDBEngine(pFCREPLJson dbEngine);

	
/*
** Getters
*/

	// DBEngine status.
	FCREPLEngineStatus GetStatus() { return (FCREPLEngineStatus)((pRCESDBEngine)this)->GetStatus(); };

	// Server connection string.
	char *GetServName() { return ((pRCESDBEngine)this)->GetServName(); };

	// Full absolute local directory.
	char *GetFullDataPath() { return ((pRCESDBEngine)this)->GetFullDataPath(); };

/*
	Inherited getters

	// DBEngine identification.
	int GetID();

	// OpSystem identification that is running the agent.
	// It is linked to FCREPLOpSystem class.
	int GetOSID();

	// DBEngine name.
	char *GetName();

    // Status
    RCESEngineStatus GetStatus();

	// Last time that the DBEngine status changed.
	RCESDateTime GetStatusTime();

	// Last time that the DBEngine status has been checked.
	RCESDateTime GetLastCheckTime();

	// Host name/IP address.
	char *GetHost();

	// DBEngine description.
	char *GetDescription();

	// Encrypted authentication information: Login and Password.
	char *GetAuthContent();

	// Working volume identification.
	// It is linked to FCREPLVolume class.
	int GetWorkingVolume();

	// Working directory.
	char *GetWorkingDir();

	// User name.
	char *GetUser();

	// Password.
	char *GetUserPass();

    // Retrieve the server name
    char *GetServName();
 
    // Retrieve the server name by IP address
    char *GetServNameByIP(const char *ipAddress = NULL);

    // Windows service name.
	char *GetServiceName();

	// Executable name.
	char *GetExeName();

	// Return if DBEngine is a SQL server.
	bool GetIsSQL();

	// ISAM port number.
	int GetPortNumber();

	// SQL port number.
	int GetSqlPortNumber();

	// Local directory's volume identification.
	// It is linked to FCREPLVolume class.
	int GetLocalVolume();

	// Local directory.
	char *GetLocalDir();

	// Maximum number of users.
	int GetUsers();

	// Release version.
	char *GetVersion();

	// Serial number.
	char *GetSerial();

	// License OEM.
	int GetLicenseOEM();

	// License Type (Development, Production, etc).
	char *GetLicenseType();

	// License number of CPU limit.
	int GetLicenseCPUNbr();

	// License server type (ISAM, SQL, etc). 
	char *GetLicenseServerType();

	// License User number.
	int GetLicenseUserNumber();

    // Working volume name
    char *GetWorkingVolumeName();

    // Local volumen name
    char *GetLocalVolumeName();

    // Retrieve the full data directory
    char *GetFullDataPath();

	// DBEngine has Replication Studio embedded.
	bool GetIsAgent();

	// Logical name.
	char *GetLogicalName();
	
    // Retrieve the authentication info for the current DBEngine
    void GetAuthInfo();

	// Return if DBEngine is the Memphis server.
	bool IsMaster();

	// Replication Unique Node identification.
	char *GetReplNodeID();

	// Flag indicating that the DBEngine must be connected by the IP address instead of the host name
	bool IsConnectByIP();

	// Speficy IP address to be used when trying to connect to the DBEngine
	char *GetIPAddress();

    // Return IP address list
    ppRCESIp GetIPAddressList();

	// Number of IP addresses in the list
	int GetIPAddressCount();

	// Flag indicating if the DBEngine accepts external connections
	bool GetAcceptConn();

	// Flag for the DBEngine readonly status
	RCESReadOnly GetReadOnly();

    // Get read only string
    const char *GetReadOnlyName();
 
    // Get Is memphis flag
    bool IsMemphis(pRCESConfig config);

	// Web Server config
	char *GetWebServerConfig();
*/

/*
** Setters
*/

	// DBEngine status.
	void SetStatus(FCREPLEngineStatus status) { ((pRCESDBEngine)this)->SetStatus((RCESEngineStatus)status); };

	// DBEngine name.
	void SetName(const char *name) { ((pRCESDBEngine)this)->SetName(name); };

	// Host name/IP address.
	void SetHost(const char *host) { ((pRCESDBEngine)this)->SetHost(host); };

	// DBEngine description.
	void SetDescription(const char *description) { ((pRCESDBEngine)this)->SetDescription(description); };

	// Working directory.
	void SetWorkingDir(const char *workingDir) { ((pRCESDBEngine)this)->SetWorkingDir(workingDir); };

	// User name.
	void SetUserName(const char *userName) { ((pRCESDBEngine)this)->SetUserName(userName); };

	// Password.
	void SetUserPass(const char *userPass) { ((pRCESDBEngine)this)->SetUserPass(userPass); };

	// Encrypted authentication information: Login and Password.
	void SetAuthContent(const char *authContent) { ((pRCESDBEngine)this)->SetAuthContent(authContent); };

	// Local directory.
	void SetLocalDir(const char *localDir) { ((pRCESDBEngine)this)->SetLocalDir(localDir); };

	// Release version.
	void SetVersion(const char *version) { ((pRCESDBEngine)this)->SetVersion(version); };

	// Serial number.
	void SetSerial(const char *serial) { ((pRCESDBEngine)this)->SetSerial(serial); };

	// License Type (Development, Production, etc).
	void SetLicenseType(const char *licenseType) { ((pRCESDBEngine)this)->SetLicenseType(licenseType); };

	// License server type (ISAM, SQL, etc).
	void SetLicenseServerType(const char *licenseServerType) { ((pRCESDBEngine)this)->SetLicenseServerType(licenseServerType); };

	// Logical name.
	void SetLogicalName(const char *logicalName) { ((pRCESDBEngine)this)->SetLogicalName(logicalName); };

	// Replication Unique Node identification.
	void SetReplNodeID(char *replNodeID) { ((pRCESDBEngine)this)->SetReplNodeID(replNodeID); };

	// Speficy IP address to be used when trying to connect to the DBEngine
	void SetIPAddress(char *ipAddress) { ((pRCESDBEngine)this)->SetIPAddress(ipAddress); };

	// Web Server config
	void SetWebServerConfig(char *webServerConfig) { ((pRCESDBEngine)this)->SetWebServerConfig(webServerConfig); };

/*
Inherited setters

	// DBEngine identification.
	void SetID(int id);

	// OpSystem identification that is running the agent.
	// It is linked to FCREPLOpSystem class.
	void SetOSID(int osID);

    // Name
    void SetName(const char *name);
 
    // Status
    void SetStatus(RCESEngineStatus status);

    // Last time that the DBEngine status changed.
	void SetStatusTime(RCESDateTime statusTime);

	// Last time that the DBEngine status has been checked.
	void SetLastCheckTime(RCESDateTime lastCheckTime);

    // Host
    void SetHost(const char *host);
 
    // Description
    void SetDescription(const char *description);

	// Working volume identification.
	// It is linked to FCREPLVolume class.
	void SetWorkingVolume(int workingVolume);

    // Working directory
    void SetWorkingDir(const char *workingDir);
 
    // Auth content
    void SetAuthContent(const char *authContent);

	// Return if DBEngine is a SQL server.
	void SetIsSQL(bool isSQL);

	// ISAM port number.
	void SetPortNumber(int portNumber);

	// SQL port number.
	void SetSqlPortNumber(int sqlPortNumber);

	// Local directory's volume identification.
	// It is linked to FCREPLVolume class.
	void SetLocalVolume(int localVolume);

    // Local Directory
    void SetLocalDir(const char *localDir);

	// Maximum number of users.
	void SetUsers(int users);

    // Version
    void SetVersion(const char *version);
 
    // Serial
    void SetSerial(const char *serial);

	// License OEM.
	void SetLicenseOEM(int licenseOEM);

    // License type
    void SetLicenseType(const char *licenseType);

	// License number of CPU limit.
	void SetLicenseCPUNbr(int licenseCPUNbr);

    // License server type
    void SetLicenseServerType(const char *licenseServerType);

	// License User number.
	void SetLicenseUserNumber(int licenseUserNumber);

    // Working volume name
    void SetWorkingVolumeName(const char *workingVolumeName);

    // Local volume name
    void SetLocalVolumeName(const char *localVolumeName);

    // User name
    void SetUserName(const char *userName);

    // User password
    void SetUserPass(const char *userPass);

	// DBEngine has Replication Studio embedded.
	void SetIsAgent(bool isAgent);

    // Logical name
    void SetLogicalName(const char *logicalName);

	// DBEngine is Memphis server.
	void SetIsMaster(bool isMaster);

    // Repl node ID
    void SetReplNodeID(const char *replNodeID);

	// Flag indicating that the DBEngine must be connected by the IP address instead of the host name
	void SetIsConnectByIP(bool connectByIP) { _connectByIP = connectByIP; };

    // IP address
    void SetIPAddress(char *ipAddress);
 
    // IP address list
    void SetIPAddressList(ppRCESIp ipList) { _ipList = ipList; };

	// Number of IP addresses in the list
	void SetIPAddressCount(int ipCount) { _ipCount = ipCount; };

	// Flag indicating if the DBEngine accepts external connections
	void SetAcceptConn(bool acceptConn);

	// Flag for the DBEngine readonly status
	void SetReadOnly(bool readOnly);
*/

};

#endif /* _FCREPLDBENGINE_HPP_ */
