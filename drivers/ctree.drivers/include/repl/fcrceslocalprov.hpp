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

#ifndef _FCRCESLOCALPROV_HPP_
#define _FCRCESLOCALPROV_HPP_

#include "fc_rces.h"
#include "fcrcesdataprov.hpp"
#include "fcrcesfile.hpp"
#include "fcrcesconfig.hpp"
#include "fcrcesfiletransferremote.hpp"

/* API to be provided by the local data provider */
const char *RCESDPLocalGetErrorMsg( void *conn );

int RCESDPLocalLoadSymbols( pRCESDynServer dynServer, char **errorMsg );
int RCESDPLocalLoadSymbols( void *libHandle, char **errorMsg );
int RCESDPLocalLoadClientSymbols( char **errorMsg );
int RCESDPLocalConnect( const char *serverName, const char *userName, const char *password, void *&conn );
int RCESDPLocalDisconnect( void *conn );
bool RCESDPLocalIsActive( void *conn );
int RCESDPLocalAttach(void *conn);
int RCESDPLocalDetach( void *conn );
int RCESDPLocalGetDir( void *conn, char *localDir, int localDirBufLen );
int RCESDPLocalGetThreadOwner();

int RCESDPLocalAddFile( void *conn, int volumeID, const char *filePath, const char *fileName, RCESDateTime fileCreateDate, RCESDateTime fileUpdateDate, 
                        RCESSize fileSize, bool isDir, bool isPartitioned, int fileType, int databaseID, const char *tableName, bool isBlockInsert, int *newFileID );
int RCESDPLocalStartInsBatch( void *conn );
int RCESDPLocalFinishInsBatch( void *conn );
int RCESDPLocalIsCtreeFile( void *conn, const char *fileName, int *errorCd );
int RCESDPLocalGetTempFSFileName( void *conn, char *tempFSFileName );
int RCESDPLocalCreateFSFile( void *conn, const char *tempFSFileName );
int RCESDPLocalFlushFSFile( void *conn );
int RCESDPLocalReadBlockFS( void *conn, const char *tempFSFileName, pRCESRecBlock recBlock );
int RCESDPLocalCloseFSFile( void *conn );
int RCESDPLocalDeleteFSFile( void *conn, const char *tempFSFileName );
int RCESDPLocalOpenFSFile( void *conn, const char *tempFSFileName );

int RCESDPLocalGetDatabasesByDict( void *conn, const char *fileName, ppRCESDatabase *databaseList, int *databaseCount );
int RCESDPLocalGetFilesByDict( void *conn, pRCESDBEngine dbEngine, bool isCaseSensitive, char *dictFileName, ppRCESVolume volumeList, int volumeCount,
                               bool *isSQL, ppRCESFile *fileList, int *fileCount );

int RCESDPLocalStartDictNotify(void *conn, pRCESDBEngineRfrsr dbRefresher);
int RCESDPLocalStopDictNotify(void *conn, pRCESDBEngineRfrsr dbRefresher);
int RCESDPLocalPushDictNotify(void *conn, pRCESDBEngineRfrsr dbRefresher);
int RCESDPLocalOpenQueue(void *conn, const char *queueName, int *qHandle);
int RCESDPLocalCheckQueue(void *conn, int qHandle, pRCESThrdState thrdState, bool *found);
int RCESDPLocalStartDBNotification(void *conn, pRCESDatabase database, int qHandle, int *datno);
int RCESDPLocalStopDBNotification(void *conn, bool isNotified, int qHandle, int datno);

int RCESDPLocalConvertPartFile(void *conn, pRCESReplPlan replPlan, const char *tempFileName, char *targetFileName);

/*^****************************************************************************\
*
*   RCESLocalProvider
*   Recon-e-Sense local provider class
*
*   Implement the data management interface for the local server DLL database
*
\******************************************************************************/
class RCESLocalProvider : public RCESDataProvider
{
	public:
		/* Constructors & destructor */
		RCESLocalProvider(FCPool<RCESMasterConnPooled> *masterConnPool);
		RCESLocalProvider(pRCESMasterProvider masterProv);
		RCESLocalProvider(pRCESConfig config);
		virtual ~RCESLocalProvider();

		/* Public methods */
		int SetLocalServerDLL( pRCESDynServer dynServer );
		int SetLocalClientDLL();
		int Connect();
		void Disconnect();
		bool IsActive();
		int GetThreadOwner();
		int ConnAttach();
		int ConnDetach();
		int GetTempFSFileName( char *tempFSFileName );
		int CreateFSFile( const char *tempFSFileName );
		int OpenFSFile( const char *tempFSFileName );
		int CloseTempFS();
		int DeleteFSFile( const char *tempFSFileName );
		int UploadFSFile( char *tempFSFileName );
		int ReadBlockFS( const char *tempFSFileName, pRCESRecBlock recBlock );
		bool IsMasterProvider() { return false; };
		int GetDatabases( const char *fileName, ppRCESDatabase *databaseList, int *databaseCount );
		int GetFiles( pRCESDBEngine dbEngine, bool isCaseSensitive, char *dictFileName, ppRCESVolume volumeList, int volumeCount, bool *isSQL,
		              ppRCESFile *fileList, int *fileCount );
		void CheckFileType( pRCESFile fileName );
		int StartInsBatch();
		int FinishInsBatch();
		int AddFile( pRCESFile file, bool isBlockInsert = TRUE );
		const char *GetErrorMsg();
		int StartDictNotify(pRCESDBEngineRfrsr dbRefresher);
		int StopDictNotify(pRCESDBEngineRfrsr dbRefresher);
		int PushDictNotify(pRCESDBEngineRfrsr dbRefresher);
		int OpenQueue(const char *queueName, int *qHandle);
		int CheckQueue(int qHandle, pRCESThrdState thrdState, bool *found);
		int StartDBListNotification(int qHandle, ppRCESDatabase databaseList, int databaseCount);
		int StopDBListNotification(int qHandle, ppRCESDatabase databaseList, int databaseCount);
		int StartDBNotification(pRCESDatabase database, int qHandle, int *datno);
		int StopDBNotification(bool isNotified, int qHandle, int datno);
		int ConvertPartFile(pRCESReplPlan replPlan, const char *tempFileName, char *targetFileName);
		void _log(const char *errMessage, const char *functionName);
		void _error(const char *errMessage, int errCode, const char *functionName, RCESSeverity level);
		void _exception(FCException &excep);

		int GetVolume( int volumeID, ppRCESVolume volume ) { return RCES_NOTSUP_ERR; };

	private:
		/* Private properties */
		pRCESFileTransferRemote _fileTransfer;
		pRCESDBEngineMngr _masterDBEngineMngr;
		FCPool<RCESMasterConnPooled> *_masterConnPool;
		pRCESMasterProvider _masterProv;

		/* Private methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESLocalProvider *pRCESLocalProvider, **ppRCESLocalProvider;

#endif /* _FCRCESLOCALPROV_HPP_ */