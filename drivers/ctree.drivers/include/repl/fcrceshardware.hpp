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

#ifndef _FCRCESHARDWARE_HPP_
#define _FCRCESHARDWARE_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESHardware;
class RCESMac;
class RCESMasterProvider;
typedef RCESHardware *pRCESHardware, **ppRCESHardware;
typedef RCESMac *pRCESMac, **ppRCESMac;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_HARDWARE_LIST "hardwareList"
#define RCES_HARDWARE "hardware"
#define RCES_HARDWARE_ID "id"
#define RCES_HARDWARE_SITE "site" 
#define RCES_HARDWARE_NAME "name"
#define RCES_HARDWARE_MAC "mac"
#define RCES_HARDWARE_MEMORY "memory"
#define RCES_HARDWARE_DISKSPACE "diskSpace"
#define RCES_HARDWARE_CPU "cpu"
#define RCES_HARDWARE_DESCRIPTION "description"
#define RCES_HARDWARE_TOTAL "total"
#define RCES_HARDWARE_RECURSIVE "recursive"
#define RCES_HARDWARE_MACLIST "macList"

/*^****************************************************************************\
*
*   RCESHardware
*   Recon-e-Sense hardware class
*
\******************************************************************************/
class RCESHardware
{
public:
	/* Constructors & destructor */
	RCESHardware();
	RCESHardware(pRCESJson hardware);
	virtual ~RCESHardware();

	/* Public services */
	static int ctGetHardwares(pRCESMasterProvider masterProv, int siteID, int hardwareListSize, int hardwareStart, ppRCESHardware *hardwareList, int *hardwareCount, int *totalSites);
	static int ctGetHardwares(pRCESMasterProvider masterProv, int siteID, bool isPaging, int hardwareListSize, int hardwareStart, ppRCESJson result);
	static int ctGetHardware(pRCESMasterProvider masterProv, int hardwareID, ppRCESHardware hardware);
	static int ctGetHardware(pRCESMasterProvider masterProv, int hardwareID, bool isPaging, ppRCESJson result);
	static int ctGetHardware(pRCESMasterProvider masterProv, int siteID, const char *name, ppRCESHardware hardware);
	static int ctGetHardware(pRCESMasterProvider masterProv, int siteID, const char *name, bool isPaging, ppRCESJson result);
	static int ctGetHardware(pRCESMasterProvider masterProv, const char *mac, ppRCESHardware hardware);
	static int ctGetHardware(pRCESMasterProvider masterProv, const char *mac, bool isPaging, ppRCESJson result);
	static int ctPersistHardware(pRCESMasterProvider masterProv, pRCESHardware hardware);
	static int ctPersistHardware(pRCESMasterProvider masterProv, pRCESJson hardware, ppRCESJson result);
	static int ctRemoveHardware(pRCESMasterProvider masterProv, int hardwareId, bool recursive);
	static int ctRemoveHardware(pRCESMasterProvider masterProv, int hardwareId, bool recursive, ppRCESJson result);

	/* Public methods */
	int GetID() { return _id; };
	int GetSiteID() { return _siteID; };
	const char *GetName() { return _name; };
	void GetMacAddresses(ppRCESMac *macList, int *macCount) { *macList = _macList; *macCount = _macCount; };
	const char *GetDescription() { return _description; };
	int GetMemory() { return _memory; };
	int GetDiskSpace() { return _diskSpace; };
	int GetCPU() { return _cpu; };

	void SetID(int id) { _id = id; };
	void SetSiteID(int siteID) { _siteID = siteID; };
	void SetName(const char *name);
	void SetMacAddresses(ppRCESMac macList, int macCount);
	void SetDescription(const char *description);
	void SetMemory(int memory) { _memory = memory; };
	void SetDiskSpace(int diskSpace) { _diskSpace = diskSpace; };
	void SetCPU(int cpu) { _cpu = cpu; };

	pRCESJson GetJson();
	void Update(pRCESJson hardwarePatch);
	bool IsMACListReplaced() { return _newMacCount > 0; };
	void UpdateMacList();

private:
	/* Private properties */
	int _id;
	int _siteID;
	char *_name;
	ppRCESMac _macList;
	int _macCount;
	char *_description;
	int _memory;
	int _diskSpace;
	int _cpu;

	ppRCESMac _newMacList;
	int _newMacCount;
};
/*~****************************************************************************/

#endif /* _FCRCESHARDWARE_HPP_ */