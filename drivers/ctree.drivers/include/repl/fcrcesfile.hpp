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

#ifndef _FCRCESFILE_HPP_
#define _FCRCESFILE_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"
#include "fcrcesrule.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#define RCES_FS_LIST "fileList"
#define RCES_FS "file"
#define RCES_FS_ID "id"
#define RCES_FS_VOLUME "volume" 
#define RCES_FS_ROOT "root"
#define RCES_FS_PATH "path"
#define RCES_FS_NAME "name"
#define RCES_FS_TABLE "table"
#define RCES_FS_SIZE "size"
#define RCES_FS_CREATETIME "createTime"
#define RCES_FS_UPDATETIME "updateTime"
#define RCES_FS_ISDIR "isDir"
#define RCES_FS_ISPARTITIONED "isPartitioned"
#define RCES_FS_TYPE "type"
#define RCES_FS_MASK "mask"
#define RCES_FS_STARTFILE "startFile"
#define RCES_FS_COUNT "fileCount"
#define RCES_FS_RECURSIVE "recursive"
#define RCES_FS_CHECKREPLPLAN "checkReplPlan"
#define RCES_FS_ISREPLICATED "isReplicated"
#define RCES_FS_ACTIONID "actionID"
#define RCES_FS_DATABASE "database"
#define RCES_FS_REL_FILE_ID "relFile"
#define RCES_FS_TOTAL "total"
#define RCES_FS_CTREEONLY "ctreeOnly"
#define RCES_FS_REPLICABLE "isReplicable"
#define RCES_FS_DESCRIPTION "description"
#define RCES_FS_REFRESH "refresh"
#define RCES_FS_PHYSICALCHECK "physicalCheck"

/*^****************************************************************************\
*
*   RCESFile
*   Recon-e-Sense file class
*
*   File System file information
*
\******************************************************************************/
class RCESFile : public RCESRule
{
public:
	/* Constructors & destructor */
	RCESFile();
	RCESFile(int volumeID, const char* filePath, const char* fileName, RCESSize fileSize = 0, RCESDateTime fileCreateTime = 0, RCESDateTime fileUpdateTime = 0, bool isDir = false, bool isPartitioned = false, int databaseID = -1);
	RCESFile(RCESFile *file);
	RCESFile(pRCESJson file);
	virtual ~RCESFile();

	/* Public services */
	static int ctReplFSLoad(pRCESMasterProvider masterProv, int volumeID, const char *rootTreePath, const char *maskFilter, bool ctreeOnly, bool recursive, bool physicalCheck, bool wait, int *actionID);
	static int ctReplFSLoadFolders(pRCESMasterProvider masterProv, int volumeID, const char *rootTreePath, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles);
	static int ctReplFSLoadFolders(pRCESMasterProvider masterProv, int volumeID, const char *rootTreePath, bool paging, int fileListSize, int fileStart, ppRCESJson result);
	static int ctGetFiles(pRCESMasterProvider masterProv, int volumeID, const char *rootTreePath, const char *mask, bool recursive, bool physicalCheck, int checkReplPlan, bool refresh, bool ctreeOnly, 
		int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles);
	static int ctGetFiles(pRCESMasterProvider masterConn, int volumeID, const char *rootPath, const char *mask, bool recursive, bool physicalCheck, int checkReplPlan, bool refresh, bool ctreeOnly, bool paging, 
		int fileListSize, int fileStart, ppRCESJson result);
	static int ctGetFiles(pRCESMasterProvider masterProv, int databaseID, int checkReplPlan, int fileListSize, int fileStart, ppRCESFile *fileList, int *fileCount, int *totalFiles);
	static int ctGetFiles(pRCESMasterProvider masterProv, int databaseID, int checkReplPlan, bool paging, int fileListSize, int fileStart, ppRCESJson result);
	static int ctGetFile(pRCESMasterProvider masterProv, int fileID, ppRCESFile file);
	static int ctGetFile(pRCESMasterProvider masterConn, int fileID, bool paging, ppRCESJson result);
	static int ctGetFile(pRCESMasterProvider masterProv, int volumeID, const char *path, const char *name, ppRCESFile file);
	static int ctGetFile(pRCESMasterProvider masterConn, int volumeID, const char *path, const char *name, bool paging, ppRCESJson result);
	static int ctGetFile(pRCESMasterProvider masterProv, int osID, const char* fullFileName, ppRCESFile file);
	static int ctPersistFile(pRCESMasterProvider masterProv, pRCESFile file);
	static int ctPersistFile(pRCESMasterProvider masterProv, pRCESJson file, ppRCESJson result);
	static int ctRemoveFile(pRCESMasterProvider masterProv, int fileID, bool recursive);
	static int ctRemoveFile(pRCESMasterProvider masterProv, int fileID, bool recursive, ppRCESJson result);

	/* Public methods */
	bool IsCtree() { return _type == RCES_CTREP_QUALIF || _type == RCES_CTREP_QUALIF_RTG; };
	int GetID() { return _id; };
	int GetVolumeID() { return _volumeID; };
	const char *GetPath() { return _path; };
	const char *GetName() { return _name; };
	const char *GetTable() { return _table; };
	RCESSize GetSize() { return _size; };
	RCESDateTime GetCreateTime() { return _createTime; };
	RCESDateTime GetUpdateTime() { return _updateTime; };
	bool GetIsDir() { return _isDir; };
	bool GetIsPartitioned() { return _isPartitioned; };
	RCESFileType GetType() { return _type; };
	bool GetIsReplicated() { return _isReplicated; };
	int GetDatabaseID() { return _databaseID; };
	const char *GetVolumeName() { return _volumeName; };
	int GetRelFileID() { return _relFileID; };

	void SetID(int fileID) { _id = fileID; };
	void SetVolumeID(int volumeID) { _volumeID = volumeID; };
	void SetPath(const char *path);
	void SetName(const char *name);
	void SetTable(const char *table);
	void SetSize(RCESSize size) { _size = size; };
	void SetCreateTime(RCESDateTime createTime) { _createTime = createTime; };
	void SetUpdateTime(RCESDateTime updateTime) { _updateTime = updateTime; };
	void SetIsDir(bool isDir) { _isDir = isDir; };
	void SetIsPartitioned(bool isPartitioned) { _isPartitioned = isPartitioned; };
	void SetType(RCESFileType type) { _type = type; };
	void SetIsReplicated(bool isReplicated) { _isReplicated = isReplicated; };
	void SetDatabaseID(int databaseID) { _databaseID = databaseID; };
	void SetVolumeName(const char *volumeName);
	void SetRelFileID(int relFileID) { _relFileID = relFileID; };

	pRCESJson GetJson(bool previewOnly);
	pRCESJson GetJson() { return GetJson(false); };
	void Update(pRCESJson filePatch);
	void Copy(pRCESFile file);
	int CheckConstraints(pRCESMasterProvider masterProv);
	void GetFullPath(char *fullPath);

private:
	/* Private properties */
	int _id;
	int _volumeID;
	char *_path;
	char *_name;
	char *_table;
	RCESSize _size;
	RCESDateTime _createTime;
	RCESDateTime _updateTime;
	bool _isDir;
	bool _isPartitioned;
	bool _ownBuffer;
	RCESFileType _type;
	bool _isReplicated;
	int _databaseID;
	char *_volumeName;
	int _relFileID;

	static int FilesToJson(ppRCESFile fileList, int fileCount, ppRCESJson result);
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESFile *pRCESFile, **ppRCESFile;

#endif /* _FCRCESFILE_HPP_ */