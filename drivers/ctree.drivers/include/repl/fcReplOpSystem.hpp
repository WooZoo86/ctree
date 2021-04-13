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

#ifndef _FCREPLOPSYSTEM_HPP_
#define _FCREPLOPSYSTEM_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesos.hpp"
#include "fcrcesip.hpp"

/* Forward class declaration */
class FCREPLOpSystem;
typedef FCREPLOpSystem *pFCREPLOpSystem, **ppFCREPLOpSystem;

/* FCREPLPlatform table */
typedef enum
{
	FCREPL_PLATFORM_NONE = -1,
	FCREPL_PLATFORM_WINDOWS64 = 0,
	FCREPL_PLATFORM_LINUX64 = 1,
	FCREPL_PLATFORM_RASPBIAN32 = 2
} FCREPLPlatform;


/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - OpSystem
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetOSs
*               Retrieve all the OpSystem entity objects for the given hardware
*               identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               hardwareID [IN]
*               Hardware identification
*
*               osList [OUT]
*               OS entity list
*
*               osCount [OUT]
*               Number of OS entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetOSs(pFCREPLConn replConn, int hardwareID, ppFCREPLOpSystem *osList, int *osCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetOS
*               Retrieve the OS entity object by its Name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               hardwareID [IN]
*               Hardware identification
*
*               name [IN]
*               Hardware name
*
*               opSystem [OUT]
*               OS entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetOS(pFCREPLConn replConn, int hardwareID, const char *name, ppFCREPLOpSystem opSystem);

/*^****************************************************************************\
*
*   Function:   fcReplGetOS
*               Retrieve the OS entity object by its Hostname.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               hostName [IN]
*               Host name
*
*               opSystem [OUT]
*               OS entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetOS(pFCREPLConn replConn, const char *hostName, ppFCREPLOpSystem opSystem);

/*^****************************************************************************\
*
*   Function:   fcReplGetOSByIP
*               Retrieve the OS entity object by its IP address.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               ipAddress [IN]
*               IP address
*
*               opSystem [OUT]
*               OS entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetOSByIP(pFCREPLConn replConn, const char *ipAddress, ppFCREPLOpSystem opSystem);

/*^****************************************************************************\
*
*   Function:   fcReplPersistOS
*               Add a OS entity into the database. If there already is a
*               OS with the given hardwareID/name, update the existing record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               opSystem [IN]
*               OS entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistOS(pFCREPLConn replConn, pFCREPLOpSystem opSystem);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveOS
*               Delete the OS by its identification.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               osID [IN]
*               OS identification
*
*               recursive [IN]
*               Recursive flag
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveOS(pFCREPLConn replConn, int osID, bool recursive);



/*^****************************************************************************\
*
*   Class:      FCREPLIp
*               IP address representation
*
\******************************************************************************/
class FCREPL_API FCREPLIp : public RCESIp
{
public:
	FCREPLIp();
	FCREPLIp(pFCREPLJson ip, int osID);
	

/*
** Getters
*/

/*
	Inherited getters

	// IP address identification.
	int GetID();

	// IP address.
	const char *GetAddress();

	// IP address type.
	const char *GetType();

	// OpSystem identification.
	// It is linked to FCREPLOpSystem class
	int GetOSID();
*/

/*
** Setters
*/

	// IP address.
	void SetAddress(const char *address) { ((pRCESIp)this)->SetAddress(address); };

	// IP address type.
	void SetType(const char *type) { ((pRCESIp)this)->SetType(type); };

/*
	Inherited setters

	// IP address identification.
	void SetID( int id );

    // Address
    void SetAddress( const char *address );
 
    // Type
    void SetType( const char *type );

    // OpSystem identification.
	// It is linked to FCREPLOpSystem class
	void SetOSID( int osID );
*/
};
typedef FCREPLIp *pFCREPLIp, **ppFCREPLIp;



/*^****************************************************************************\
*
*   Class:      FCREPLOpSystem
*               It is below Hardware hierarchy and has a list of Volumes.
*               It represents the OpSystem running on a physical machine or a
*               virtual machine.
*
\******************************************************************************/
class FCREPL_API FCREPLOpSystem : public RCESOpSystem
{
public:
	FCREPLOpSystem();
	FCREPLOpSystem(pFCREPLJson opSystem);
	
/*
** Getters
*/

	// List of IP addresses for the OpSystem
	void GetIPAddresses(ppFCREPLIp *ipList, int *ipCount) { ((pRCESOpSystem)this)->GetIPAddresses((ppRCESIp *)ipList, ipCount); };

/*
	Inherited getters

	// OpSystem identification.
	int GetID();

	// Hardware identification.
	// It is linked to FCREPLHardware class.
	int GetHardwareID();

	// OpSystem name.
	const char *GetName();

	// OpSystem host name.
	const char *GetHostName();

    // OpSystem IP list, count
    void GetIPAddresses(ppRCESIp *ipList, int *ipCount);

	// OpSystem type.
	const char *GetType();

	// OpSystem edition.
	const char *GetEdition();

	// Opsystem description.
	const char *GetDescription();

	// OpSystem memory.
	int GetMemory();

	// OpSystem disk space.
	int GetDiskSpace();

	// OpSystem CPU count.
	int GetCPU();

	// Flag indicating if the OpSystem has path case sensitive or not
	bool isPathCaseSensitive();

    // OpSystem platform
    RCESPlatform GetPlatform();
*/


/*
** Setters
*/

	// List of IP addresses for the OpSystem
	void SetIPAddresses(ppFCREPLIp ipList, int ipCount) { ((pRCESOpSystem)this)->SetIPAddresses((ppRCESIp)ipList, ipCount); };

	// OpSystem name.
	void SetName(const char *name) { ((pRCESOpSystem)this)->SetName(name); };

	// OpSystem host name.
	void SetHostName(const char *hostName) { ((pRCESOpSystem)this)->SetHostName(hostName); };

	// OpSystem type.
	void SetType(const char *type) { ((pRCESOpSystem)this)->SetType(type); };

	// OpSystem edition.
	void SetEdition(const char *edition) { ((pRCESOpSystem)this)->SetEdition(edition); };

	// Opsystem description.
	void SetDescription(const char *description) { ((pRCESOpSystem)this)->SetDescription(description); };

/*
	Inherited setters

	// OpSystem identification.
	void SetID(int id);

	// Hardware identification.
	// It is linked to FCREPLHardware class.
	void SetHardwareID(int hardwareId);

    // OpSystem name
    void SetName(const char *name);
 
    // OpSystem host name
    void SetHostName(const char *hostName);
 
    // OpSystem IP list, count
    void SetIPAddresses(ppRCESIp ipList, int ipCount);
 
    // OpSystem type
    void SetType(const char *type);
 
    // OpSystem edition
    void SetEdition(const char *edition);
 
    // OpSystem description
    void SetDescription(const char *description);

	// OpSystem memory.
	void SetMemory(int memory);

	// OpSystem disk space.
	void SetDiskSpace(int diskSpace);

	// OpSystem CPU count.
	void SetCPU(int cpu);

	// Flag indicating if the OpSystem has path case sensitive or not
	void SetPathCaseSensitive(bool pathCaseSensitive);

    // OpSystem platform
    void SetPlatform(RCESPlatform platform);
*/
};

#endif /* _FCREPLOPSYSTEM_HPP_ */
