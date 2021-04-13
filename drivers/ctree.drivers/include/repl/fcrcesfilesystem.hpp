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

#ifndef _FCRCESFILESYSTEM_HPP_
#define _FCRCESFILESYSTEM_HPP_

#include "fcrcesaux.hpp"
#include "fcrcesschema.hpp"
#include "fcrcesconn.hpp"
#include "fcrcesconfig.hpp"
#include "fcrceslogger.hpp"
#include "fcrcesmasterprov.hpp"
#include "fcrcesqueue.hpp"
#include "fcrcesnotiffs.hpp"
#include "fcrceslocalconnpooled.hpp"

typedef struct CleanThrdData {
	int volumeID;
	FCPool<RCESMasterConnPooled> *masterConnPool;
	int errorCode;
	char errorMsg[ RCES_MAX_ERRMSG_LEN+1 ];
} CleanThrdData, *pCleanThrdData;

typedef struct LoadThrdData {
	char errorMsg[RCES_MAX_ERRMSG_LEN+1];
	int errorCode;
	RCESThrdState state;
	pRCESQueue queue;
	void *loadMutex;
	int actionID;
	int totalFileCount;
	int *currFileCount;
	int *currLoadPct;
	FCPool<RCESMasterConnPooled> *masterConnPool;
} LoadThrdData, *pLoadThrdData, **ppLoadThrdData;

/* Class type definitions */
class RCESConn;
typedef RCESConn *pRCESConn, **ppRCESConn;

/*^****************************************************************************\
*
*   RCESFilePath
*   Recon-e-Sense file path class
*
*   Directory identification in Memphis: Volume ID, Volume Name and Path
*
\******************************************************************************/
class RCESFilePath
{
	public:
		/* Constructors & destructor */
		RCESFilePath( int volumeID, const char *volumeName, const char *path );
		virtual ~RCESFilePath();

		/* Public methods */
		int GetVolumeID() { return _volumeID; };
		const char *GetVolumeName() { return _volumeName; };
		const char *GetPath() { return _path; };

	private:
		/* Private properties */
		int _volumeID;
		char *_volumeName;
		char *_path;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   RCESFileSystem
*   Recon-e-Sense filesystem class
*
*   Monitor the File System information
*
\******************************************************************************/
class RCESFileSystem
{
	public:
		/* Constructors & destructor */
		RCESFileSystem( FCPool<RCESMasterConnPooled> *masterConnPool );
		virtual ~RCESFileSystem();

		/* Public methods */
		void Cleanup( int volumeID );
		void Scan( int actionID, ppRCESVolume volumeList, int volumeCount, const char *rootPath, const char *mask, RCESScanMode scanMode, 
			bool cleanFlag = false, bool ctreeOnly = false, bool recursive = true );
		void ScanFolder(int actionID, pRCESVolume volume, const char *rootPath);
		void LoadTempFSFile( int actionID, int fileCount, const char *tempFSName );
		void DeleteTempFSFile( const char *tempFSName );
		void ImportReplAgent( const char *path, ppRCESReplPlan replPlan, ppRCESPublication publication, ppRCESSubscription subscription, FCHashTable<char> **redirectStrList, char *filterName);
		void CheckCtreeMask(const char *mask);
		void PhysicalCheck(pRCESVolume volume, const char *rootPath, const char *mask, bool recursive);

		/* Public Services */
#ifdef NCTREE_FILE_SUPPORT
		static int ctScan( pRCESConn replConn, ppRCESVolume volumes, int volumeCount, const char *rootTreePath, 
		const char *maskFilter, bool cleanFlag, ppRCESNotifFS notifFSList, char **errorMsg );
#endif
		static int ctDBEngineScan( FCPool<RCESMasterConnPooled> *masterConnPool, ppRCESVolume volumes, int volumeCount, char **errorMsg );

		static void ctCheckDBEngine( int osID, int volume, const char *volumeName, const char *workingPath, const char *localDir, 
		                             pRCESMasterProvider masterProvider, bool canRemove );

	private:
		/* Private properties */
		FCPool<RCESMasterConnPooled> *_masterConnPool;
		pRCESLocalProvider _localProvider;
		pSchemaThrdData _schemaThrdData;
		bool _dbEngine;
		void *_schemaThrdHandle;
		void *_hSchemaMutex;
		void **_cleanThrdHandles;
		pCleanThrdData _cleanThrdData;
		int _volumeCount;
		int _loadThrdCount;
		ppLoadThrdData _loadThrdListData;
		void **_loadThrdHandles;
		void *_hLoadMutex;
		int _nextQueueInd;
		bool _freeLocalProv;
#ifdef ctCHECK_MAX_PATH
		char _maxPath[RCES_MAX_PATH+1];
#endif
		int _maskCount;
		const char **_maskList;
		pRCESConfig _config;

		/* Private methods */
		void _Scan( const char *path, const char *mask );
		void _createSchemaThread( int volumeID );
		void _prepareTempFS( char *tempFSName );
		void _loadTempFS( int actionID, int filecount, char *tempFSName );
		void _loadMasterFS( int actionID, int filecount, const char *tempFSName );
		void _cleanVolumes( ppRCESVolume volumeList );
		void _checkCleanThreads();
		void _startLoadThrds( int actionID, int totalFileCount, int *currFileCount, int *currLoadPct );
		void _queueBlockFS( pRCESRecBlock recBlock );
		void _finishLoadThrds();
		void _checkPaths( FCList<RCESFilePath> *pathList );
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESFileSystem *pRCESFileSystem, **ppRCESFileSystem;
typedef RCESFilePath *pRCESFilePath, **ppRCESFilePath;

#endif /* _FCRCESFILESYSTEM_HPP_ */