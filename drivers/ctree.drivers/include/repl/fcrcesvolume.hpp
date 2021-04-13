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

#ifndef _FCRCESVOLUME_HPP_
#define _FCRCESVOLUME_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESVolume;
class RCESConn;
typedef RCESVolume *pRCESVolume, **ppRCESVolume;
typedef RCESConn *pRCESConn, **ppRCESConn;

#define RCES_VOLUME_LIST "volumeList"
#define RCES_VOLUME "volume"
#define RCES_VOLUME_ID "id"
#define RCES_VOLUME_OS "opSystem" 
#define RCES_VOLUME_NAME "name"
#define RCES_VOLUME_TOTALDISKSPACE "totalDiskSpace"
#define RCES_VOLUME_AVAILDISKSPACE "availDiskSpace"
#define RCES_VOLUME_DESCRIPTION "description"
#define RCES_VOLUME_TOTAL "total"
#define RCES_VOLUME_RECURSIVE "recursive"

/*^****************************************************************************\
*
*   RCESVolume
*   Recon-e-Sense Volume class
*
\******************************************************************************/
class RCESVolume
{
public:
	/* Constructors & destructor */
	RCESVolume();
	RCESVolume(pRCESJson volume);
	virtual ~RCESVolume();

	/* Public services */
	static int ctGetVolumes(pRCESMasterProvider masterProv, int osId, int volumeListSize, int volumeStart, ppRCESVolume *volumeList, int *volumeCount, int *totalVolumes);
	static int ctGetVolumes(pRCESMasterProvider masterProv, int osId, bool isPaging, int volumeListSize, int volumeStart, ppRCESJson result);
	static int ctGetVolume(pRCESMasterProvider masterProv, int volumeId, ppRCESVolume volume);
	static int ctGetVolume(pRCESMasterProvider masterProv, int volumeId, bool isPaging, ppRCESJson result);
	static int ctGetVolume(pRCESMasterProvider masterProv, int osId, const char *name, ppRCESVolume volume);
	static int ctGetVolume(pRCESMasterProvider masterProv, int osId, const char *name, bool isPaging, ppRCESJson result);
	static int ctGetVolumeByPath(pRCESMasterProvider masterProv, int osId, const char *fullFileName, ppRCESVolume volume);
	static int ctPersistVolume(pRCESMasterProvider masterProv, pRCESVolume volume);
	static int ctPersistVolume(pRCESMasterProvider masterProv, pRCESJson volume, ppRCESJson result);
	static int ctRemoveVolume(pRCESMasterProvider masterProv, int volumeID, bool recursive);
	static int ctRemoveVolume(pRCESMasterProvider masterProv, int volumeID, bool recursive, ppRCESJson result);

	/* Public methods */
	int GetID() { return _id; };
	int GetOSID() { return _osId; };
	const char *GetName() { return _name; };
	const char *GetDescription() { return _description; };
	int GetTotalDiskSpace() { return _totalDiskSpace; };
	int GetAvailDiskSpace() { return _availDiskSpace; };

	void SetID(int id) { _id = id; };
	void SetOSID(int osID) { _osId = osID; };
	void SetName(const char *name);
	void SetDescription(const char *description);
	void SetTotalDiskSpace(int totalDiskSpace) { _totalDiskSpace = totalDiskSpace; };
	void SetAvailDiskSpace(int availDiskSpace) { _availDiskSpace = availDiskSpace; };

	pRCESJson GetJson();
	void Update(pRCESJson volumePatch);

private:
	/* Private properties */
	int _id;
	int _osId;
	char *_name;
	char *_description;
	int _totalDiskSpace;
	int _availDiskSpace;
};
/*~****************************************************************************/

#endif /* _FCRCESVOLUME_HPP_ */