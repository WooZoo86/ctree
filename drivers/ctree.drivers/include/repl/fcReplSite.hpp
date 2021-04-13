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

#ifndef _FCREPLSITE_HPP_
#define _FCREPLSITE_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcessite.hpp"

/* Forward class declaration */
class FCREPLSite;
typedef FCREPLSite *pFCREPLSite, **ppFCREPLSite;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Site
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetSites
*               Retrieve all the Site entity objects
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               siteList [OUT]
*               Site entity list
*
*               siteCount [OUT]
*               Number of site entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetSites(pFCREPLConn replConn, ppFCREPLSite *siteList, int *siteCount);

/*^****************************************************************************\
*
*   Function:   fcReplGetSite
*               Retrieve the Site entity object by its Name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               name [IN]
*               Site name to be retrieved
*
*               site [OUT]
*               Site entity retrieved
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetSite(pFCREPLConn replConn, const char *name, ppFCREPLSite site);

/*^****************************************************************************\
*
*   Function:   fcReplPersistSite
*               Add a Site entity into the database. If there already is a site
*               with the given name, update the existing record.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               site [IN]
*               Site entity to be persisted
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistSite(pFCREPLConn replConn, pFCREPLSite site);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveSite
*               Delete the Site by its identification.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               siteID [IN]
*               Site identification to be removed
*
*               recursive [IN]
*               Recursive flag
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveSite(pFCREPLConn replConn, int siteID, bool recursive);


/*^****************************************************************************\
*
*   Class:      FCREPLSite
*               Represents the top level on the Replication Studio hierarchy.
*               Could represent the local network, cloud, remote datacenter, etc.
*
\******************************************************************************/
class FCREPL_API FCREPLSite : public RCESSite
{
public:
	FCREPLSite();
	FCREPLSite(pFCREPLJson site);

/*
** Getters
*/

/*
	Inherited getters

	// Site identification.
	int GetID();

	// Site name.
	const char *GetName();

	// Site type.
	const char *GetType();

	// Site description.
	const char *GetDescription();
*/


/*
** Setters
*/

	// Site name.
	void SetName(const char *name) { ((pRCESSite)this)->SetName(name); };

	// Site type.
	void SetType(const char *type) { ((pRCESSite)this)->SetType(type); };

	// Site description.
	void SetDescription(const char *description) { ((pRCESSite)this)->SetDescription(description); };

/*
	Inherited getters

	// Site identification.
	void SetID(int id);

    // Site name
    void SetName(const char *name);
 
    // Site type
    void SetType(const char *type);
 
    // Site description
    void SetDescription(const char *description);
*/

};

#endif /* _FCREPLSITE_HPP_ */
