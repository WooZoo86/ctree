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

#ifndef _FCREPLHARDWARE_HPP_
#define _FCREPLHARDWARE_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrceshardware.hpp"
#include "fcrcesmac.hpp"

/* Forward class declaration */
class FCREPLHardware;
typedef FCREPLHardware *pFCREPLHardware, **ppFCREPLHardware;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Hardware
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetHardwares
*               Retrieve all the Hardware entity objects for the given site
*               identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               siteID [IN]
*               Site identification
*
*               hardwareList [OUT]
*               Hardware entity list
*
*               hardwareCount [OUT]
*               Number of hardware entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetHardwares(pFCREPLConn replConn, int siteID, ppFCREPLHardware *hardwareList, int *hardwareCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetHardware
*               Retrieve the Hardware entity object by its Name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               siteID [IN]
*               Site identification
*
*               name [IN]
*               Hardware name
*
*               hardware [OUT]
*               Hardware entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetHardware(pFCREPLConn replConn, int siteID, const char *name, ppFCREPLHardware hardware);

/*^****************************************************************************\
*
*   Function:   fcReplGetHardware
*               Retrieve the Hardware entity object by its MAC address.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               mac [IN]
*               MAC address
*
*               hardware [OUT]
*               Hardware entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetHardware(pFCREPLConn replConn, const char *mac, ppFCREPLHardware hardware);

/*^****************************************************************************\
*
*   Function:   fcReplPersistHardware
*               Add a Hardware entity into the database. If there already is a
*               hardware with the given siteID/name, update the existing record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               hardware [IN]
*               Hardware entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistHardware(pFCREPLConn replConn, pFCREPLHardware hardware);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveHardware
*               Delete the Hardware by its identification.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               hardwareId [IN]
*               Hardware identification
*
*               recursive [IN]
*               Recursive flag
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveHardware(pFCREPLConn replConn, int hardwareID, bool recursive);



/*^****************************************************************************\
*
*   Class:      FCREPLMac
*               MAC address representation
*
\******************************************************************************/
class FCREPL_API FCREPLMac : public RCESMac
{
public:
	FCREPLMac();
	FCREPLMac(pFCREPLJson mac, int hardwareID);
	
/*
** Getters
*/

/*
	Inherited getters

	// MAC address
	const char *GetAddress();

	// MAC type
	const char *GetType();

	// Hardware identification.
	// It is linked to FCREPLSite class
	int GetHardwareID();
*/

/*
** Setters
*/

	// MAC address
	void SetAddress(const char *address) { ((pRCESMac)this)->SetAddress(address); };

	// MAC type
	void SetType(const char *type) { ((pRCESMac)this)->SetType(type); };

/*
	Inherited setters

    // Address
    void SetAddress(const char *address);
 
    // Type
    void SetType(const char *type);

    // Hardware identification.
	// It is linked to FCREPLSite class
	void SetHardwareID(int hardwareID);
*/
};
typedef FCREPLMac *pFCREPLMac, **ppFCREPLMac;



/*^****************************************************************************\
*
*   Class:      FCREPLHardware
*               It is below Site hierarchy and has a list of OpSystem.
*               It represents the physical computer.
*
\******************************************************************************/
class FCREPL_API FCREPLHardware : public RCESHardware
{
public:
	FCREPLHardware();
	FCREPLHardware(pFCREPLJson hardware);
	
/*
** Getters
*/

	// List of MAC address for the hardware
	void GetMacAddresses(ppFCREPLMac *macList, int *macCount) { ((pRCESHardware)this)->GetMacAddresses((ppRCESMac *)macList, macCount); };

/*
	Inherited getters

	// Hardware identification
	int GetID();

	// Site identification.
	// It is linked to FCREPLSite class.
	int GetSiteID();

	// Hardware name.
	const char *GetName();
	
    // MAC List, count
    void GetMacAddresses(ppRCESMac *macList, int *macCount);

	// Hardware description.
	const char *GetDescription();

	// Hardware memory.
	int GetMemory();

	// Hardware disk space.
	int GetDiskSpace();

	// Hardware number of CPUs.
	int GetCPU();
*/

/*
** Setters
*/

	// List of MAC address for the hardware
	void SetMacAddresses(ppFCREPLMac macList, int macCount) { ((pRCESHardware)this)->SetMacAddresses((ppRCESMac)macList, macCount); };

	// Hardware name.
	void SetName(const char *name) { ((pRCESHardware)this)->SetName(name); };

	// Hardware description.
	void SetDescription(const char *description) { ((pRCESHardware)this)->SetDescription(description); };

/*
	Inherited setters

	// Hardware identification
	void SetID(int id);

	// Site identification.
	// It is linked to FCREPLSite class.
	void SetSiteID(int siteID);

    // Hardware name
    void SetName(const char *name);

    // Hardware MAC list, count
    void SetMacAddresses(ppRCESMac macList, int macCount);

    // Hardware description
    void SetDescription(const char *description);

	// Hardware memory.
	void SetMemory(int memory);

	// Hardware disk space.
	void SetDiskSpace(int diskSpace);

	// Hardware number of CPUs.
	void SetCPU(int cpu);
*/
};

#endif /* _FCREPLHARDWARE_HPP_ */
