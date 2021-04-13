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

#ifndef _FCRCESSITE_HPP_
#define _FCRCESSITE_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESSite;
class RCESMasterProvider;
typedef RCESSite *pRCESSite, **ppRCESSite;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_SITE_LIST "siteList"
#define RCES_SITE "site"
#define RCES_SITE_ID "id"
#define RCES_SITE_NAME "name"
#define RCES_SITE_TYPE "type"
#define RCES_SITE_DESCRIPTION "description"
#define RCES_SITE_TOTAL "total"
#define RCES_SITE_RECURSIVE "recursive"

/*^****************************************************************************\
*
*   RCESSite
*   Recon-e-Sense site class
*
\******************************************************************************/
class RCESSite
{
public:
	/* Constructors & destructor */
	RCESSite();
	RCESSite(pRCESJson site);
	virtual ~RCESSite();

	/* Public services */
	static int ctGetSites(pRCESMasterProvider masterProv, int siteListSize, int siteStart, ppRCESSite *siteList, int *siteCount, int *totalSites);
	static int ctGetSites(pRCESMasterProvider masterProv, bool isPaging, int siteListSize, int siteStart, ppRCESJson result);
	static int ctGetSite(pRCESMasterProvider masterProv, int siteID, ppRCESSite site);
	static int ctGetSite(pRCESMasterProvider masterProv, int siteID, bool isPaging, ppRCESJson result);
	static int ctGetSite(pRCESMasterProvider masterProv, const char *name, ppRCESSite site);
	static int ctGetSite(pRCESMasterProvider masterProv, const char *name, bool isPaging, ppRCESJson result);
	static int ctPersistSite(pRCESMasterProvider masterProv, pRCESSite site);
	static int ctPersistSite(pRCESMasterProvider masterProv, pRCESJson site, ppRCESJson result);
	static int ctRemoveSite(pRCESMasterProvider masterProv, int siteID, bool recursive);
	static int ctRemoveSite(pRCESMasterProvider masterProv, int siteID, bool recursive, ppRCESJson result);

	/* Public methods */
	int GetID() { return _id; };
	const char *GetName() { return _name; };
	const char *GetType() { return _type; };
	const char *GetDescription() { return _description; };

	void SetID(int id) { _id = id; };
	void SetName(const char *name);
	void SetType(const char *type);
	void SetDescription(const char *description);

	pRCESJson GetJson();
	void Update(pRCESJson sitePatch);

private:
	/* Private properties */
	int _id;
	char *_name;
	char *_type;
	char *_description;
};
/*~****************************************************************************/

#endif /* _FCRCESSITE_HPP_ */