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

#ifndef _FCREPLVOLUME_HPP_
#define _FCREPLVOLUME_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesvolume.hpp"

/* Forward class declaration */
class FCREPLVolume;
typedef FCREPLVolume *pFCREPLVolume, **ppFCREPLVolume;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Volume
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetVolumes
*               Retrieve all the Volume entity objects for the given OpSystem
*               identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               osID [IN]
*               OS identification
*
*               volumeList [OUT]
*               Volume entity list
*
*               volumeCount [OUT]
*               Number of volume entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetVolumes(pFCREPLConn replConn, int osID, ppFCREPLVolume *volumeList, int *volumeCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetVolume
*               Retrieve the Volume entity object by its Name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               osID [IN]
*               OS identification
*
*               name [IN]
*               Hardware name
*
*               volume [OUT]
*               Volume entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetVolume(pFCREPLConn replConn, int osID, const char *name, ppFCREPLVolume volume);

/*^****************************************************************************\
*
*   Function:   fcReplPersistVolume
*               Add a Volume entity into the database. If there already is a
*               Volume with the given osID/name, update the existing record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               volume [IN]
*               Volume entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistVolume(pFCREPLConn replConn, pFCREPLVolume volume);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveVolume
*               Delete the Volume by its identification.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               volumeID [IN]
*               Volume identification
*
*               recursive [IN]
*               Recursive flag
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveVolume(pFCREPLConn replConn, int volumeID, bool recursive);


/*^****************************************************************************\
*
*   Class:      FCREPLVolume
*               Represents the top level on the File System hierarchy. On
*               Replication Studio, it is just below OpSystem.
*
\******************************************************************************/
class FCREPL_API FCREPLVolume : public RCESVolume
{
public:
	FCREPLVolume();
	FCREPLVolume(pFCREPLJson volume);
	

/*
** Getters
*/

/*
	Inherited getters

	// Volume identification.
	int GetID();

	// OpSystem identification.
	// It is linked to FCREPLOpSystem class.
	int GetOSID();

	// Volume name.
	const char *GetName();

	// Volume description.
	const char *GetDescription();

	// Volume total disk space.
	int GetTotalDiskSpace();

	// Volume available disk space.
	int GetAvailDiskSpace();
*/


/*
** Setters
*/

	// Volume name.
	void SetName(const char *name) { ((pRCESVolume)this)->SetName(name); };

	// Volume description.
	void SetDescription(const char *description) { ((pRCESVolume)this)->SetDescription(description); };

/*
	Inherited setters

	// Volume identification.
	void SetID(int id);

	// OpSystem identification.
	// It is linked to FCREPLOpSystem class.
	void SetOSID(int osID);

    // Name
    void SetName(const char *name);

    // Description
    void SetDescription(const char *description);

	// Volume total disk space.
	void SetTotalDiskSpace(int totalDiskSpace);

	// Volume available disk space.
	void SetAvailDiskSpace(int availDiskSpace);
*/
};

#endif /* _FCREPLVOLUME_HPP_ */
