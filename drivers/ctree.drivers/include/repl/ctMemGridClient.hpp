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
 *      Copyright (c) 2013 - 2020 FairCom Corporation.
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

#ifndef _CTMEMGRIDCLIENT_HPP_
#define _CTMEMGRIDCLIENT_HPP_

#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#ifdef ctFeatMEMGRID

/* Class type definitions */
class CTMemGridClient;
class CTMemGridClientConnListener;
class CTMemGridClientMemberListener;
class RCESLogger;
typedef CTMemGridClient *pCTMemGridClient, **ppCTMemGridClient;
typedef CTMemGridClientConnListener *pCTMemGridClientConnListener, **ppCTMemGridClientConnListener;
typedef CTMemGridClientMemberListener *pCTMemGridClientMemberListener, **ppCTMemGridClientMemberListener;
typedef RCESLogger *pRCESLogger, **ppRCESLogger;

#undef  __
#ifdef PROTOTYPE
#define __(args)        args
#else
#define __(args)        ()
#endif

/* Memory Grid symbol indexes */
#define CTFN_MEMGRID_TOTAL 11

#define	CTFN_RCESMemGridConnect                0
#define	CTFN_RCESMemGridDisconnect             1
#define	CTFN_RCESMemGridGetErrorMsg            2
#define	CTFN_RCESMemGridGetErrorCode           3
#define	CTFN_RCESMemGridSetReplicaDBStatus     4
#define	CTFN_RCESMemGridPutReplicaInfo         5
#define	CTFN_RCESMemGridRemoveReplicaInfo      6
#define	CTFN_RCESMemGridGetAvailGroupJson      7
#define	CTFN_RCESMemGridGetStatus              8
#define	CTFN_RCESMemGridSetAvailGroupStatus    9
#define	CTFN_RCESMemGridUpdateAvailGroupStatus 10

/* Memory Grid c-tree symbol types */
typedef int(*pRCESMemGridConnect_t) __((pCTMemGridClient, const char *, void *&, char *));
typedef int(*pRCESMemGridDisconnect_t) __((void *));
typedef const char *(*pRCESMemGridGetErrorMsg_t) __((void *));
typedef int(*pRCESMemGridGetErrorCode_t) __((void *));
typedef int(*pRCESMemGridSetReplicaDBStatus_t) __((void *, int, RCESEngineStatus, bool *));
typedef int(*pRCESMemGridPutReplicaInfo_t) __((void *, int, pRCESJson));
typedef int(*pRCESMemGridRemoveReplicaInfo_t) __((void *, int));
typedef pRCESJson(*pRCESMemGridGetAvailGroupJson_t) __((void *, bool));
typedef pRCESJson(*pRCESMemGridGetStatus_t) __((void *, int));
typedef int(*pRCESMemGridSetAvailGroupStatus_t) __((void *, RCESEngineStatus));
typedef int(*pRCESMemGridUpdateAvailGroupStatus_t) __((void *));

/* Memory Grid symbol pointer array */
extern pVOID memgridfnc[CTFN_MEMGRID_TOTAL];

/* Memory Grid symbol pointer defines */
#define	RCESMemGridConnect (*(pRCESMemGridConnect_t)memgridfnc[CTFN_RCESMemGridConnect])
#define	RCESMemGridDisconnect (*(pRCESMemGridDisconnect_t)memgridfnc[CTFN_RCESMemGridDisconnect])
#define	RCESMemGridGetErrorMsg (*(pRCESMemGridGetErrorMsg_t)memgridfnc[CTFN_RCESMemGridGetErrorMsg])
#define	RCESMemGridGetErrorCode (*(pRCESMemGridGetErrorCode_t)memgridfnc[CTFN_RCESMemGridGetErrorCode])
#define	RCESMemGridSetReplicaDBStatus (*(pRCESMemGridSetReplicaDBStatus_t)memgridfnc[CTFN_RCESMemGridSetReplicaDBStatus])
#define	RCESMemGridPutReplicaInfo (*(pRCESMemGridPutReplicaInfo_t)memgridfnc[CTFN_RCESMemGridPutReplicaInfo])
#define	RCESMemGridRemoveReplicaInfo (*(pRCESMemGridRemoveReplicaInfo_t)memgridfnc[CTFN_RCESMemGridRemoveReplicaInfo])
#define	RCESMemGridGetAvailGroupJson (*(pRCESMemGridGetAvailGroupJson_t)memgridfnc[CTFN_RCESMemGridGetAvailGroupJson])
#define	RCESMemGridGetStatus (*(pRCESMemGridGetStatus_t)memgridfnc[CTFN_RCESMemGridGetStatus])
#define	RCESMemGridSetAvailGroupStatus (*(pRCESMemGridSetAvailGroupStatus_t)memgridfnc[CTFN_RCESMemGridSetAvailGroupStatus])
#define	RCESMemGridUpdateAvailGroupStatus (*(pRCESMemGridUpdateAvailGroupStatus_t)memgridfnc[CTFN_RCESMemGridUpdateAvailGroupStatus])

/*^****************************************************************************\
*
*   CTMemGridClient
*   FairCom's memory grid client class
*
\******************************************************************************/
class CTMemGridClient
{
public:
	/* Constructors & destructor */
	CTMemGridClient(FCPool<RCESMasterConnPooled> *masterConnPool, const char *groupName, int portNumber, int heartbeatFrequency, int heartbeatTimeout);
	virtual ~CTMemGridClient();

	/* Public methods */
	void Connect();
	void Disconnect();
	void PutAvailGroupInfo(pRCESJson availGroupStatus);
	void PutReplicaInfo(int DBEngineID, pRCESJson replicaStatus);
	pRCESJson GetAvailGroupJson(bool withReplicas);
	pRCESJson GetReplicaJson(int DBEngineID);
	pRCESReplicaStatus GetReplicaStatus(int DBEngineID);
	RCESEngineStatus GetAvailGroupCurrStatus();
	pRCESAvailGroupStatus GetAvailGroupStatus();
	pRCESAvailGroupStatus GetAvailGroupStatusWithReplicas();
	void RemoveReplicaInfo(int DBEngineID);
	bool IsAvailGroupLoaded() { return GetAvailGroupJson(false) != NULL; };
	void SetReplicaDBStatus(int DBEngineID, RCESEngineStatus dbEngineStatus, bool *isPrimary);
	void SetReplicaDBStatusMemGrid(int DBEngineID, RCESEngineStatus dbEngineStatus, bool *isPrimary);
	void SetAvailGroupStatus(RCESEngineStatus availGroupStatus);
	void SetConnPool(FCPool<RCESMasterConnPooled> *connPool) { _masterConnPool = connPool; };
	void UpdateAvailGroupStatusFromMemGrid();
	void SwitchReplica();

	void SetIsConnected(bool isConnected);
	bool IsConnected() { return _isConnected; };

	const char *GetGroup() { return _groupName; };
	int GetPort() { return _port; };
	FCPool<RCESMasterConnPooled> *GetConnPool() { return _masterConnPool; };

private:
	/* Private properties */
	void *_conn;
	FCPool<RCESMasterConnPooled> *_masterConnPool;
	bool _isConnected;
	char *_groupName;
	int _port;
	int _heartbeatFrequency;
	int _heartbeatTimeout;
	char _errorMsg[FC_MAX_ERRMSG_LEN + 1];

	/* private methods */
	void _setReplicaDBStatusMemphis(int DBEngineID, RCESEngineStatus dbEngineStatus);
	void _loadSymbols();
	void _validateConnection(const char *methodName);
};
/*~****************************************************************************/

#endif /* ctFeatMEMGRID */

#endif /* _CTMEMGRIDCLIENT_HPP_ */