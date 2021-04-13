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

#ifndef _FCREPLFILE_HPP_
#define _FCREPLFILE_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesfile.hpp"

/* Forward class declaration */
class FCREPLFile;
typedef FCREPLFile *pFCREPLFile, **ppFCREPLFile;

/* FileType table */
typedef enum
{
	FCREPL_INVALID = -1,
	FCREPL_CTREE            = 0,    /* File is c-tree                                                               */
	FCREPL_CTREE_CORRUPT    = 1,    /* File is c-tree but it is corrupted                                           */
	FCREPL_CTREP_QUALIF     = 2,    /* File is c-tree and qualifies to replication                                  */
	FCREPL_CTREP_QUALIF_RTG = 3,    /* File is c-tree and qualifies to replication                                  */
	FCREPL_CTREP_NO_IFIL    = 4,    /* File is c-tree but doesn't have IFIL, so doesn't qualify for replication     */
	FCREPL_CTREP_NO_TRNLOG  = 5,    /* File is c-tree but is not TRNLOG, so doesn't qualify for replication         */
	FCREPL_CTREP_NO_IDX     = 6,    /* File is c-tree but doesn't have an index that qualifies for replication      */
	FCREPL_CTREP_NO_XHEADER = 7,    /* File doesn't support extended header - probably created before V7            */
	FCREPL_PENDING          = 8,    /* File is pending on the schema checked - problably due to permission issue    */
	FCREPL_CTREEIDX         = 9,    /* File is a c-tree index                                                       */
	FCREPL_CTREESUPER       = 10,   /* File is a c-tree super file                                                  */
	FCREPL_DIR              = 11,   /* Item is a directory                                                          */
	FCREPL_NCTREE           = 12,   /* This is not a c-tree file                                                    */
	FCREPL_CTREP_FTI        = 13    /* File is c-tree but has a Full Text Index, so doesn't qualify for replication */
} FCREPLFileType;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - File
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplLoadFiles (Ctree File System Load)
*               Recursively scan all the files under the given "rootTreePath"
*               filtered by a given "maskFilter" using the given "configFileName"
*               and populate both VOLUME and FILE tables.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               volumeID [IN]
*               Volume identification to be monitored
*
*               rootTreePath [IN]
*               Local path to be monitored. Examples: "C:\path" or "/home/path"
*
*               maskFilter [IN]
*               File/Dir mask to be monitored. Supported multiple masks delimited
*               by [;]. Example: "*.dat;*.txt;*.rpo"
*
*               ctreeOnly [IN]
*               Flag indicating that we should scan only for c-tree data files
*
*               recursive [IN]
*               Flag indicating that we should scan from root recursivelly or not
*
*               physicalCheck [IN]
*               Check if the files in FileTable physically exist
*
*               wait [IN]
*               Flag indicating that we should wait for the scan to terminate or
*               run it asynchronous
*
*               actionID [OUT]
*               Action identification for the FS load action
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplLoadFiles(pFCREPLConn replConn, int volumeID, const char *rootTreePath, const char *maskFilter, bool ctreeOnly, bool recursive, bool physicalCheck, bool wait, int *actionID);

/*^****************************************************************************\
*
*   Function:   fcReplGetFiles
*               Retrieve the list of files from a given root tree. It can be
*               called several times in order to retrieve all the blocks of
*               files.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               volumeID [IN]
*               Volume identification
*
*               rootTreePath [IN]
*               Root path
*
*               mask [IN]
*               File mask for the file search
*
*               recursive [IN]
*               Flag indicating if it must search also on the children folders
*
*               physicalCheck [IN]
*               Check if the files in FileTable physically exist
*
*               checkReplPlan [IN]
*               Replication plan to be checked against the file or -1, if not
*               checked.
*
*               refresh [IN]
*               Flag indicating if we should execute a FileSystem scan before
*               returning the files
*
*               ctreeOnly [IN]
*               Flag indicating that we should scan only for c-tree data files.
*               It is only in case of refresh is TRUE
*
*               fileListSize [IN]
*               File list count to be retrieved
*
*               fileStart [IN]
*               File list start record
*
*               fileList [OUT]
*               File entity list
*s
*               fileCount [OUT]
*               Number of file entities in the list
*
*               totalFiles [OUT]
*               Total number of files entities
*
*   Returns:    Error code or FCREPL_MORE_RESULT in case of pending files to be
*               read
*
\******************************************************************************/
FCREPL_API int fcReplGetFiles(pFCREPLConn replConn, int volumeID, const char *rootTreePath, const char *mask, bool recursive, bool physicalCheck, int checkReplPlan, bool refresh, bool ctreeOnly, int fileListSize, int fileStart,
	ppFCREPLFile *fileList, int *fileCount, int *totalFiles);

/*^****************************************************************************\
*
*   Function:   fcReplGetFiles
*               Retrieve the list of files from a given database ID.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               databaseID [IN]
*               Database identification
*
*               checkReplPlan [IN]
*               Replication plan to be checked against the file or -1, if not
*               checked.
*
*               fileListSize [IN]
*               File list count to be retrieved
*
*               fileStart [IN]
*               File list start record
*
*               fileList [OUT]
*               File entity list
*
*               fileCount [OUT]
*               Number of file entities in the list
*
*               totalFiles [OUT]
*               Total number of files entities
*
*   Returns:    Error code or FCREPL_MORE_RESULT in case of pending files to be
*               read
*
\******************************************************************************/
FCREPL_API int fcReplGetFiles(pFCREPLConn replConn, int databaseID, int checkReplPlan, int fileListSize, int fileStart, ppFCREPLFile *fileList, int *fileCount, int *totalFiles);

/*^****************************************************************************\
*
*   Function:   fcReplGetFile
*               Retrieve the file from a given volume, path and name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               volumeID [IN]
*               Volume identification to be monitored
*
*               path [IN]
*               File path
*
*               name [IN]
*               File name
*
*               file [OUT]
*               Files read from the calling criteria
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetFile(pFCREPLConn replConn, int volumeID, const char *path, const char *name, ppFCREPLFile file);

/*^****************************************************************************\
*
*   Function:   fcReplGetFile
*               Retrieve the file from a given OpSystem and full file name.
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               osID [IN]
*               OpSystem identification
*
*               fullFileName [IN]
*               Full file name
*
*               file [OUT]
*               Files read from the calling criteria
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetFile(pFCREPLConn replConn, int osID, const char *fullFileName, ppFCREPLFile file);

/*^****************************************************************************\
*
*   Function:   fcReplPersistFile
*               Persist a File entity object into the master database
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               file [IN]
*               File entity object
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplPersistFile(pFCREPLConn replConn, pFCREPLFile file);

/*^****************************************************************************\
*
*   Function:   fcReplRemoveFile
*               Remove a file from the master database by its identification
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               fileID [IN]
*               File identification
*
*               recursive [IN]
*               Recursive flag
*
*   Returns:    Error code
*
\******************************************************************************/
FCREPL_API int fcReplRemoveFile(pFCREPLConn replConn, int fileID, bool recursive);



/*^****************************************************************************\
*
*   Class:      FCREPLFile
*               Represents a physical file, table or directory from FileSystem
*               and from database (FCREPLDatabase).
*
\******************************************************************************/
class FCREPL_API FCREPLFile : public RCESFile
{
public:
	FCREPLFile();
	FCREPLFile(pFCREPLJson file);
	FCREPLFile(int volumeID, const char* filePath, const char* fileName, FCREPLSize fileSize = 0, FCREPLDateTime fileCreateTime = 0, FCREPLDateTime fileUpdateTime = 0, bool isDir = false, bool isPartitioned = false, int databaseID = -1);

/*
** Getters
*/

	// File type
	FCREPLFileType GetType() { return (FCREPLFileType)((pRCESFile)this)->GetType(); };

/*
	Inherited getters

	// Return if the object is for a c-tree file
	bool IsCtree();

	// File identification
	int GetID();

	// File volume identification.
	// It is linked to FCREPLVolume class.
	int GetVolumeID();

	// File path.
	const char *GetPath();

	// File name.
	const char *GetName();

	// Table name, in case it is part of a database.
	const char *GetTable();

	// File size on disk.
	RCESSize GetSize();

	// File creation time.
	RCESDateTime GetCreateTime();

	// File update time.
	RCESDateTime GetUpdateTime();

	// Return if the file is a directory.
	bool GetIsDir();

	// Return if the file is a c-tree partitioned one.
	bool GetIsPartitioned();

    // Return the type
    RCESFileType GetType();

	// Return if the file is replicated
	bool GetIsReplicated();

    // Database identification.
    // It is linked to FCREPLDatabase class.
    int GetDatabaseID();

    // File volume name;
    const char *GetVolumeName();

    // Return Rel file ID
    int GetRelFileID();
*/

/*
** Setters
*/

	// File type
	void SetType(FCREPLFileType type) { ((pRCESFile)this)->SetType((RCESFileType)type); };

	// File path.
	void SetPath(const char *path) { ((pRCESFile)this)->SetPath(path); };

	// File name.
	void SetName(const char *name) { ((pRCESFile)this)->SetName(name); };

	// Table name, in case it is part of a database.
	void SetTable(const char *table) { ((pRCESFile)this)->SetTable(table); };

/*
	Inherited setters

	// File identification
	void SetID(int fileID);

	// File volume identification.
	// It is linked to FCREPLVolume class.
	void SetVolumeID(int volumeID);

    // Path
    void SetPath(const char *path);

    // Name
    void SetName(const char *name);

    // Table
    void SetTable(const char *table);

	// File size on disk.
	void SetSize(RCESSize size);

	// File creation time.
	void SetCreateTime(RCESDateTime createTime);

	// File update time.
	void SetUpdateTime(RCESDateTime updateTime);

	// Set if the file is a directory.
	void SetIsDir(bool isDir);

	// Set if the file is a c-tree partitioned file.
	void SetIsPartitioned(bool isPartitioned);

    // Type
    void SetType(RCESFileType type);

	// Set if the file is replicated
	void SetIsReplicated(bool isReplicated);

    // Database identification.
    // It is linked to FCREPLDatabase class.
    void SetDatabaseID(int databaseID);
 
    // Volume name
    void SetVolumeName(const char *volumeName);
 
    // Rel file ID
    void SetRelFileID(int relFileID) { _relFileID = relFileID; };
*/
};
typedef FCREPLFile *pFCREPLFile, **ppFCREPLFile;

#endif /* _FCREPLFILE_HPP_ */
