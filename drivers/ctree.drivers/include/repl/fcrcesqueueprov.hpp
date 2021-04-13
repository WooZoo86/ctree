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

#ifndef _FCRCESQUEUEPROV_HPP_
#define _FCRCESQUEUEPROV_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrceslogger.hpp"
#include "fcrcesaction.hpp"
#include "fcrcesreplplan.hpp"

/* API to be provided by the queue provider */
int RCESDPQueueConnect( const char *connStr, int osID, int agentID, void **conn, char **errorMsg );
int RCESDPQueueAttach( void *dataProvConn, int osID, int agentID, void **conn, char **errorMsg );
int RCESDPQueueDisconnect( void *conn );
int RCESDPQueueConnCheck( void *conn );
int RCESDPQueuePush( void *conn, int osID, int agentID, RCESConsumerType consumerType, int replPlanID, const char *params, const char *desc, 
                     RCESActionType actionType, RCESEntityType entityType, int entityPK, int parentActionID, int ownerActionID, double factor,
                     int waitSecs, int fileVolumeID, const char *filePath, const char *fileName );
int RCESDPQueuePushAndGet( void *conn, int osID, int agentID, RCESConsumerType consumerType, int replPlanID, const char *params, const char *desc, 
                           RCESActionType actionType, RCESEntityType entityType, int entityPK, int parentActionID, int ownerActionID, double factor,
                           int waitSecs, int fileVolumeID, const char *filePath, const char *fileName, int *actionID );
int RCESDPQueuePull( void *conn, int *actionID, char *paramsStr, char *desc, RCESConsumerType *consumerType, RCESActionType *actionType, 
                     int *replPlanID, RCESEntityType *entityType, int *entityPK, int *parentActionID, int *ownerActionID, double *factor, 
                     int *fileVolumeID, char *filePath, char *fileName );
int RCESDPQueueStartProcess(void *conn, int actionID);
int RCESDPQueueSetProgress( void *conn, int actionID, int progress );
int RCESDPQueueSetContent( void *conn, int actionID, const char *content, int contentLen );
int RCESDPQueueGetContent( void *conn, pRCESAction action );
bool RCESDPQueueCheckPendingPathActions( void *conn, int osID, int replPlanID, RCESConsumerType consumerType, int actionID, const char *path );
bool RCESDPQueueCheckPendingReplActions( void *conn, int replPlanID, RCESConsumerType consumerType, int initActionID, int startActionID, bool checkError, int *errorCode,
                                         char **errorMsg );
int RCESDPQueueCheckAction( void *conn, char *errorMsg, int actionID, int timeout );
int RCESDPCleanUnproc( void *conn, int replPlanID, RCESConsumerType consumerType);
int RCESDPGetTaskID( void *conn );
void RCESDPQueueCriteriaUpdate( void *conn, pRCESActionQueueCriteria criteria );
int RCESDPQueueGetPendingAction( void *conn, RCESEntityType entityType, int entityPK, int volumeID, const char *filePath, const char *fileName, 
                                 int *pendingActionID, RCESActionType *pendingActionType );
int RCESDPQueueUnlock( void *conn );
int RCESDPQueueUpdate( void *conn, int actionID, RCESActionType newActionType, const char *newParamsStr );
int RCESDPQueueRemove( void *conn, int actionID );
int RCESDPQueueGetAction( void *conn, int actionID, ppRCESAction action );
int RCESDPQueueCheckGroup( void *conn, pRCESAction action );
int RCESDPQueueCancelAction( void *conn, int actionID, bool checkGroup, bool onlyPending );
int RCESDPQueueGetUncompActions( void *conn, int agentID, ppRCESAction *actionList, int *actionCount );

int RCESDPQueueSetError( void *conn, int actionID, int errorCd, const char *errorMsg, bool onlyUnproc = false );
int RCESDPQueueGetErrorCode( void *conn );
const char *RCESDPQueueGetErrorMsg( void *conn );
const char *RCESDPQueueGetUserErrorMsg( void *conn );

typedef void *RCESHandle;

/*^****************************************************************************\
*
*   RCESQueueProvider
*   Recon-e-Sense queue provider class. It is an option for the queue managed in
*   memory. It stores the actions in a database and keeps its history.
*
*   Implement the queue management interface
*
\******************************************************************************/
class RCESQueueProvider
{
	public:
		/* Constructors & destructor */
		RCESQueueProvider( int osID, int agentID, pRCESMasterProvider masterProv );
		virtual ~RCESQueueProvider();

		/* Public methods */
		int Connect();
		int Disconnect();
		int CheckConnection();
		int QueuePush( int osID, int agentID, pRCESAction action );
		int QueuePushAndGet( int osID, int agentID, pRCESAction action );
		int StartProcess(pRCESAction action);
		pRCESAction QueuePull();
		int CheckAction( int parentActionID, char *errorMsg, int timeout = RCES_TIMEOUT );
		int CleanUnproc( int replPlanID, RCESConsumerType consumerType);
		int GetTaskID();
		const char *GetErrorMsg();
		const char *GetUserErrorMsg();
		int GetErrorCode();
		void UpdateCriteria(pRCESActionQueueCriteria criteria);
		int GetPendingAction( RCESEntityType entityType, int entityPK, int volumeID, const char *filePath, const char *fileName, 
		                      int *pendingActionID, RCESActionType *pendingActionType );
		bool CheckPendingReplAction( int replPlanID, RCESConsumerType consumerType );
		int Unlock();
		int Update( int actionID, RCESActionType newActionType, pFCParamHash newParams );
		int Remove( int actionID );
		int GetAction( int actionID, ppRCESAction action );
		int CheckGroup( pRCESAction action );
		int CancelAction( int actionID, bool checkGroup, bool onlyPending );
		int GetUncompActions( int agentID, ppRCESAction *actionList, int *actionCount );

		int SetProgress( int actionID, int progress );
		int SetError( int actionID, int errorCd, const char *errorMsg );
		void SetErrorMsg( const char *errorMsg ) { strncpy( _errorMsg, errorMsg, RCES_MAX_ERRMSG_LEN); };

		int SetContent( int actionID, const char *content, int contentLen );
		int GetContent( pRCESAction action );
		pRCESMasterProvider GetMasterProvider() { return _masterProv; };

#ifdef NCTREE_FILE_SUPPORT
		int WaitParentPath( int actionID, const char *path, int timeout = RCES_TIMEOUT );
#endif

	private:
		/* Private properties */
		char _fileName[RCES_MAX_PATH+1];
		char _filePath[RCES_MAX_PATH+1];
		int _osID;
		int _agentID;
		char _paramsStr[RCES_MAX_BUF+1];
		char _desc[RCES_MAX_BUF+1];
		char _errorMsg[RCES_MAX_ERRMSG_LEN+1];
		pRCESMasterProvider _masterProv;
		RCESHandle _conn;

		/* Private methods */
		char *_getHost();
		const char *_buildParamStr( pFCParamHash params );
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESQueueProvider *pRCESQueueProvider, **ppRCESQueueProvider;

#endif /* _FCRCESQUEUEPROV_HPP_ */