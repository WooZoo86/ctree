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

#ifndef _FCRCESOS_HPP_
#define _FCRCESOS_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESOpSystem;
class RCESIp;
class RCESMasterProvider;
typedef RCESOpSystem *pRCESOpSystem, **ppRCESOpSystem;
typedef RCESIp *pRCESIp, **ppRCESIp;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_OS_LIST "opSystemList"
#define RCES_OS "opSystem"
#define RCES_OS_ID "id"
#define RCES_OS_HARDWARE "hardware" 
#define RCES_OS_NAME "name"
#define RCES_OS_HOSTNAME "hostname"
#define RCES_OS_IP "ip"
#define RCES_OS_TYPE "type"
#define RCES_OS_EDITION "edition"
#define RCES_OS_MEMORY "memory"
#define RCES_OS_DISKSPACE "diskSpace"
#define RCES_OS_CPU "cpu"
#define RCES_OS_DESCRIPTION "description"
#define RCES_OS_TOTAL "total"
#define RCES_OS_RECURSIVE "recursive"
#define RCES_OS_IPLIST "ipList"
#define RCES_OS_PATHCASE "pathCaseSensitive"
#define RCES_OS_PLATFORM "platform"

/*^****************************************************************************\
*
*   RCESOpSystem
*   Recon-e-Sense Operational System class
*
\******************************************************************************/
class RCESOpSystem
{
public:
	/* Constructors & destructor */
	RCESOpSystem();
	RCESOpSystem(pRCESJson opSystem);
	virtual ~RCESOpSystem();

	/* Public services */
	static int ctGetOSs(pRCESMasterProvider masterProv, int hardwareID, int osListSize, int osStart, ppRCESOpSystem *osList, int *osCount, int *totalOSs);
	static int ctGetOSs(pRCESMasterProvider masterProv, int hardwareID, bool isPaging, int osListSize, int osStart, ppRCESJson result);
	static int ctGetOS(pRCESMasterProvider masterProv, int osId, ppRCESOpSystem opSystem);
	static int ctGetOS(pRCESMasterProvider masterProv, int osId, bool isPaging, ppRCESJson result);
	static int ctGetOS(pRCESMasterProvider masterProv, int hardwareId, const char *name, ppRCESOpSystem opSystem);
	static int ctGetOS(pRCESMasterProvider masterProv, int hardwareId, const char *name, bool isPaging, ppRCESJson result);
	static int ctGetOS(pRCESMasterProvider masterProv, const char *hostName, ppRCESOpSystem opSystem);
	static int ctGetOS(pRCESMasterProvider masterProv, const char *hostName, bool isPaging, ppRCESJson result);
	static int ctGetOSByIP(pRCESMasterProvider masterProv, const char *ipAddress, ppRCESOpSystem opSystem);
	static int ctGetOSByIP(pRCESMasterProvider masterProv, const char *ipAddress, bool isPaging, ppRCESJson result);
	static int ctPersistOS(pRCESMasterProvider masterProv, pRCESOpSystem opSystem);
	static int ctPersistOS(pRCESMasterProvider masterProv, pRCESJson opSystem, ppRCESJson result);
	static int ctRemoveOS(pRCESMasterProvider masterProv, int osId, bool recursive);
	static int ctRemoveOS(pRCESMasterProvider masterProv, int osId, bool recursive, ppRCESJson result);
	static RCESPlatform GetPlatformByName(const char *platformName);
	static const char *GetPlatformName(RCESPlatform platform);

	/* Public methods */
	int GetID() { return _id; };
	int GetHardwareID() { return _hardwareId; };
	const char *GetName() { return _name; };
	const char *GetHostName() { return _hostName; };
	void GetIPAddresses(ppRCESIp *ipList, int *ipCount) { *ipList = _ipList; *ipCount = _ipCount; };
	const char *GetType() { return _type; };
	const char *GetEdition() { return _edition; };
	const char *GetDescription() { return _description; };
	int GetMemory() { return _memory; };
	int GetDiskSpace() { return _diskSpace; };
	int GetCPU() { return _cpu; };
	bool isPathCaseSensitive() {return _pathCaseSensitive;};
	RCESPlatform GetPlatform() { return _platform; };

	void SetID(int id) { _id = id; };
	void SetHardwareID(int hardwareId) { _hardwareId = hardwareId; };
	void SetName(const char *name);
	void SetHostName(const char *hostName);
	void SetIPAddresses(ppRCESIp ipList, int ipCount);
	void SetType(const char *type);
	void SetEdition(const char *edition);
	void SetDescription(const char *description);
	void SetMemory(int memory) { _memory = memory; };
	void SetDiskSpace(int diskSpace) { _diskSpace = diskSpace; };
	void SetCPU(int cpu) { _cpu = cpu; };
	void SetPathCaseSensitive(bool pathCaseSensitive) {_pathCaseSensitive = pathCaseSensitive;};
	void SetPlatform(RCESPlatform platform) { _platform = platform; };

	pRCESJson GetJson();
	void Update(pRCESJson osPatch);
	bool IsIPListReplaced() { return _newIpCount > 0; };
	void UpdateIPList();

private:
	/* Private properties */
	int _id;
	int _hardwareId;
	char *_name;
	char *_hostName;
	ppRCESIp _ipList;
	int _ipCount;
	char *_type;
	char *_edition;
	char *_description;
	int _memory;
	int _diskSpace;
	int _cpu;
	bool _pathCaseSensitive;
	RCESPlatform _platform;

	ppRCESIp _newIpList;
	int _newIpCount;

	/* Private methods */
	void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESOS_HPP_ */