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
 *      Copyright (c) 2013 - 2014 FairCom Corporation.
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

#ifndef _FCRCESDBENGINEGROUP_HPP_
#define _FCRCESDBENGINEGROUP_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
	#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESDBEngineGroup;
class RCESMasterProvider;
typedef RCESDBEngineGroup *pRCESDBEngineGroup, **ppRCESDBEngineGroup;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_DBENGINEGROUP_LIST "dbEngineGroupList"
#define RCES_DBENGINEGROUP "dbEngineGroup"
#define RCES_DBENGINEGROUP_ID "id"
#define RCES_DBENGINEGROUP_NAME "name"
#define RCES_DBENGINEGROUP_DESCRIPTION "description"
#define RCES_DBENGINEGROUP_TOTAL "total"
#define RCES_DBENGINEGROUP_DBENGINELIST "dbEngineList"
#define RCES_DBENGINEGROUP_DBENGINE "dbEngine"
#define RCES_DBENGINEGROUP_PARTIAL "partial"
#define RCES_DBENGINEGROUP_DBENGINEBYGROUPLIST "dbEngineByGroupList"

/*^****************************************************************************\
*
*   RCESDBEngineGroup
*   Recon-e-Sense DBEngine group class
*
\******************************************************************************/
class RCESDBEngineGroup
{
	public:
		/* Constructors & destructor */
		RCESDBEngineGroup();
		RCESDBEngineGroup( pRCESDBEngineGroup dbEngineGroup );
		RCESDBEngineGroup( pRCESJson dbEngineGroup );
		virtual ~RCESDBEngineGroup();

		/* Public services */
		static int ctGetDBEngineGroups( pRCESMasterProvider masterProv, int dGroupListSize, int dGroupStart,
		                                ppRCESDBEngineGroup *dGroupList, int *dGroupCount, int *totalDBEngineGroups );
		static int ctGetDBEngineGroups( pRCESMasterProvider masterProv, bool isPaging, int dGroupListSize, int dGroupStart, 
		                                ppRCESJson result );
		static int ctGetDBEngineGroupsByName( pRCESMasterProvider masterProv, const char *name, bool partial, int dGroupListSize, 
		                                      int dGroupStart, ppRCESDBEngineGroup *dGroupList, int *dGroupCount, int *totalDBEngineGroups );
		static int ctGetDBEngineGroupsByName( pRCESMasterProvider masterProv, const char *name, bool partial, bool isPaging, 
		                                      int dGroupListSize, int dGroupStart, ppRCESJson result );
		static int ctGetDBEngineGroup( pRCESMasterProvider masterProv, int dbEngineGroupID, ppRCESDBEngineGroup dbEngineGroup );
		static int ctGetDBEngineGroup( pRCESMasterProvider masterProv, int dbEngineGroupID, int isPaging, ppRCESJson result );
		static int ctPersistDBEngineGroup( pRCESMasterProvider masterProv, pRCESDBEngineGroup dbEngineGroup );
		static int ctPersistDBEngineGroup( pRCESMasterProvider masterProv, pRCESJson dbEngineGroup, ppRCESJson result );
		static int ctRemoveDBEngineGroup( pRCESMasterProvider masterProv, int dbEngineGroupId );
		static int ctRemoveDBEngineGroup( pRCESMasterProvider masterProv, int dbEngineGroupId, ppRCESJson result );
		static int ctGetDBEnginesFromGroup( pRCESMasterProvider masterProv, int dbEngineGroupID, int dbEngineListSize, 
		                                    int dbEngineStart, ppRCESDBEngine *dbEngineList, int *dbEngineCount, int *totalDBEngines );
		static int ctGetDBEnginesFromGroup( pRCESMasterProvider masterProv, int dbEngineGroupID, bool isPaging, 
		                                    int dbEngineListSize, int dbEngineStart, ppRCESJson result );
		static int ctAddDBEnginesToGroup( pRCESMasterProvider masterProv, int dbEngineGroupID, int *dbEngineIDList, 
		                                  int dbEngineCount );
		static int ctAddDBEnginesToGroup( pRCESMasterProvider masterProv, int dbEngineGroupID, int *dbEngineIDList, 
		                                  int dbEngineCount, ppRCESJson result );
		static int ctRemoveDBEnginesFromGroup( pRCESMasterProvider masterProv, int dbEngineGroupID, int *dbEngineIDList, 
		                                       int dbEngineCount );
		static int ctRemoveDBEnginesFromGroup( pRCESMasterProvider masterProv, int dbEngineGroupID, int *dbEngineIDList, 
		                                       int dbEngineCount, ppRCESJson result );
		static int ctGetDBEnginesByGroup( pRCESMasterProvider masterProv, int dbEngineGroupItemListSize, int dbEngineGroupItemStart, 
		                                  ppRCESDBEngineGroupItem *dbEngineGroupItemList, int *dbEngineGroupItemCount, int *totalDBEngineGroupItems );
		static int ctGetDBEnginesByGroup( pRCESMasterProvider masterProv, bool isPaging, int dbEngineGroupItemListSize, 
		                                  int dbEngineGroupItemStart, ppRCESJson result );

		/* Public methods */
		int GetID() { return _id; };
		const char *GetName() { return _name; };
		const char *GetDescription() { return _description; };

		void SetID( int id ) { _id = id; };
		void SetName( const char *name );
		void SetDescription( const char *description );

		pRCESJson GetJson();
		void Update(pRCESJson dbEngineGroupPatch);

	private:
		/* Private properties */
		int _id;
		char *_name;
		char *_description;
};
/*~****************************************************************************/

#endif /* _FCRCESDBENGINEGROUP_HPP_ */