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

#ifndef _FCRCESFILEGROUP_HPP_
#define _FCRCESFILEGROUP_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
	#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESFileGroup;
class RCESMasterProvider;
typedef RCESFileGroup *pRCESFileGroup, **ppRCESFileGroup;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_FILEGROUP_LIST "fileGroupList"
#define RCES_FILEGROUP "fileGroup"
#define RCES_FILEGROUP_ID "id"
#define RCES_FILEGROUP_DBENGINE "dbEngine" 
#define RCES_FILEGROUP_NAME "name"
#define RCES_FILEGROUP_DESCRIPTION "description"
#define RCES_FILEGROUP_TOTAL "total"
#define RCES_FILEGROUP_FILELIST "fileList"
#define RCES_FILEGROUP_FILE "file"
#define RCES_FILEGROUP_RECURSIVE "recursive"
#define RCES_FILE_ID "id"

/*^****************************************************************************\
*
*   RCESFileGroup
*   Recon-e-Sense file group class
*
\******************************************************************************/
class RCESFileGroup
{
	public:
		/* Constructors & destructor */
		RCESFileGroup();
		RCESFileGroup( pRCESFileGroup fileGroup );
		RCESFileGroup( pRCESJson fileGroup );
		virtual ~RCESFileGroup();

		/* Public services */
		static int ctGetFileGroups( pRCESMasterProvider masterProv, int dbEngineID, int fGroupListSize, int fGroupStart,
		                            ppRCESFileGroup *fGroupList, int *fGroupCount, int *totalFileGroups );
		static int ctGetFileGroups( pRCESMasterProvider masterProv, int dbEngineID, bool isPaging, int fGroupListSize, int fGroupStart, 
		                            ppRCESJson result );
		static int ctGetFileGroup( pRCESMasterProvider masterProv, int dbEngineID, const char *name, ppRCESFileGroup fileGroup );
		static int ctGetFileGroup( pRCESMasterProvider masterProv, int dbEngineID, const char *name, bool isPaging, ppRCESJson result );
		static int ctGetFileGroup( pRCESMasterProvider masterProv, int fileGroupID, ppRCESFileGroup fileGroup );
		static int ctGetFileGroup( pRCESMasterProvider masterProv, int fileGroupID, bool isPaging, ppRCESJson result );
		static int ctPersistFileGroup( pRCESMasterProvider masterProv, pRCESFileGroup fileGroup );
		static int ctPersistFileGroup( pRCESMasterProvider masterProv, pRCESJson fileGroup, ppRCESJson result );
		static int ctRemoveFileGroup( pRCESMasterProvider masterProv, int fileGroupId, bool recursive );
		static int ctRemoveFileGroup( pRCESMasterProvider masterProv, int fileGroupId, bool recursive, ppRCESJson result );
		static int ctGetFilesFromGroup( pRCESMasterProvider masterProv, int fileGroupID, int fileListSize, int fileStart, ppRCESFile *fileList, 
		                                int *fileCount, int *totalFiles );
		static int ctGetFilesFromGroup( pRCESMasterProvider masterProv, int fileGroupID, bool isPaging, int fileListSize, int fileStart, 
		                                ppRCESJson result );
		static int ctAddFilesToGroup( pRCESMasterProvider masterProv, int fileGroupID, int *fileIDList, int fileCount );
		static int ctAddFilesToGroup( pRCESMasterProvider masterProv, int fileGroupID, int *fileIDList, int fileCount, ppRCESJson result );
		static int ctRemoveFilesFromGroup( pRCESMasterProvider masterProv, int fileGroupID, int *fileIDList, int fileCount );
		static int ctRemoveFilesFromGroup( pRCESMasterProvider masterProv, int fileGroupID, int *fileIDList, int fileCount, ppRCESJson result );

		/* Public methods */
		int GetID() { return _id; };
		int GetDBEngineID() { return _dbEngineID; };
		const char *GetName() { return _name; };
		const char *GetDescription() { return _description; };

		void SetID( int id ) { _id = id; };
		void SetDBEngineID( int dbEngineID ) { _dbEngineID = dbEngineID; };
		void SetName( const char *name );
		void SetDescription( const char *description );

		pRCESJson GetJson();
		void Update(pRCESJson fileGroupPatch);

	private:
		/* Private properties */
		int _id;
		int _dbEngineID;
		char *_name;
		char *_description;
};
/*~****************************************************************************/

#endif /* _FCRCESFILEGROUP_HPP_ */