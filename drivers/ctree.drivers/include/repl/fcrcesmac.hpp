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

#ifndef _FCRCESMAC_HPP_
#define _FCRCESMAC_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESMac;
class RCESMasterProvider;
typedef RCESMac *pRCESMac, **ppRCESMac;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_MAC_ADDRESS "mac"
#define RCES_MAC_TYPE "type"

/*^****************************************************************************\
*
*   RCESMac
*   Recon-e-Sense MAC class
*
\******************************************************************************/
class RCESMac
{
public:
	/* Constructors & destructor */
	RCESMac();
	RCESMac(pRCESMac mac);
	RCESMac(pRCESJson mac, int hardwareID);
	virtual ~RCESMac();

	/* Public services */
	static int ctGetMacs(pRCESMasterProvider masterProv, int hardwareID, int macListSize, int macStart, ppRCESMac *macList, int *macCount, int *totalMacs);
	static int ctPersistMac(pRCESMasterProvider masterProv, pRCESMac mac);
	static int ctRemoveMac(pRCESMasterProvider masterProv, const char *macAddress);

	/* Public methods */
	const char *GetAddress() { return _address; };
	const char *GetType() { return _type; };
	int GetHardwareID() { return _hardwareID; };

	void SetAddress(const char *address);
	void SetType(const char *type);
	void SetHardwareID(int hardwareID) { _hardwareID = hardwareID; };

	pRCESJson GetJson();

private:
	/* Private properties */
	char *_address;
	char *_type;
	int _hardwareID;
};
/*~****************************************************************************/

#endif /* _FCRCESMAC_HPP_ */