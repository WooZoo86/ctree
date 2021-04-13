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

#ifndef _FCRCESMQTTPERSIST_HPP_
#define _FCRCESMQTTPERSIST_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
	#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESMqttPersist;
class RCESMqttPersistField;
typedef RCESMqttPersist *pRCESMqttPersist, **ppRCESMqttPersist;
typedef RCESMqttPersistField *pRCESMqttPersistField, **ppRCESMqttPersistField;

#define RCES_MQTTPERSIST_LIST "mqttPersistenceList"
#define RCES_MQTTPERSIST "mqttPersistence"
#define RCES_MQTTPERSIST_ID "id"
#define RCES_MQTTPERSIST_DETAIL "detail"
#define RCES_MQTTPERSIST_TOPIC "persistenceTopic"
#define RCES_MQTTPERSIST_PARTIAL "partial"
#define RCES_MQTTPERSIST_NEWTOPIC "newPersistenceTopic"
#define RCES_MQTTPERSIST_TOTAL "total"
#define RCES_MQTTPERSIST_STATUS "status"
#define RCES_MQTTPERSIST_STATUS_CODE "statusCode"
#define RCES_MQTTPERSIST_STATUSTIME "statusTime"
#define RCES_MQTTPERSIST_STATUSMSG "statusMsg"
#define RCES_MQTTPERSIST_FORMAT "persistenceTopicMessageFormat"
#define RCES_MQTTPERSIST_THREADS "persistenceTopicThreads"
#define RCES_MQTTPERSIST_DBENGINE "dbEngine"
#define RCES_MQTTPERSIST_DATABASE "database"
#define RCES_MQTTPERSIST_TABLE_NAME "tableName"
#define RCES_MQTTPERSIST_REPLICATION "tableReplicationReady"
#define RCES_MQTTPERSIST_TIMESTAMP "tableAutoTimeStamp"
#define RCES_MQTTPERSIST_TIMESTAMP_INDEX "tableAutoTimeStampIndex"
#define RCES_MQTTPERSIST_RETENTION_PERIOD "tableRetentionPeriod"
#define RCES_MQTTPERSIST_RETENTION_UNIT "tableRetentionUnit"
#define RCES_MQTTPERSIST_PROPERTIES_MAP "mapOfPropertiesToFields"

/*^****************************************************************************\
*
*   RCESMqttPersist
*   Recon-e-Sense MQTT Persistence class
*
\******************************************************************************/
class RCESMqttPersist
{
	public:
		/* Constructors & destructor */
		RCESMqttPersist();
		RCESMqttPersist(pRCESMqttPersist mqttPersist);
		RCESMqttPersist(pRCESJson mqttPersist);
		virtual ~RCESMqttPersist();

		/* Public services */
		static int ctGetMQTTPersists(pRCESMasterProvider masterProv, int dbEngineID, int mqttListSize, int mqttStart, ppRCESMqttPersist *mqttList, int *mqttCount, int *totalMQTTPersists);
		static int ctGetMQTTPersists(pRCESMasterProvider masterProv, int dbEngineID, bool detail, bool isPaging, int mqttListSize, int mqttStart, ppRCESJson result);
		static int ctGetMQTTPersistsByTopic(pRCESMasterProvider masterProv, const char *topic, int dbEngineID, bool partial, int mqttListSize, int mqttStart, ppRCESMqttPersist *mqttList, int *mqttCount, int *totalMQTTPersists);
		static int ctGetMQTTPersistsByTopic(pRCESMasterProvider masterProv, const char *topic, int dbEngineID, bool detail, bool partial, bool isPaging, int mqttListSize, int mqttStart, ppRCESJson result);
		static int ctGetMQTTPersist(pRCESMasterProvider masterProv, int mqttPersistID, ppRCESMqttPersist mqttPersist);
		static int ctGetMQTTPersist(pRCESMasterProvider masterProv, int mqttPersistID, bool detail, int isPaging, ppRCESJson result);
		static int ctPersistMQTTPersist(pRCESMasterProvider masterProv, pRCESMqttPersist mqttPersist);
		static int ctPersistMQTTPersist(pRCESMasterProvider masterProv, pRCESJson mqttPersist, ppRCESJson result);
		static int ctRemoveMQTTPersist(pRCESMasterProvider masterProv, int mqttPersistID);
		static int ctRemoveMQTTPersist(pRCESMasterProvider masterProv, int mqttPersistID, ppRCESJson result);

		static const char *GetMsgTypeStr(RCESMqttMsgFormat msgFormat);
		static RCESMqttMsgFormat GettMsgType(const char *msgFormatStr);
		static const char *GetRetentionUnitStr(RCESMqttRetentionUnit retentionUnit);
		static RCESMqttRetentionUnit GetRetentionUnit(const char *retentionUnitStr);

		/* Public methods */
		int GetID() { return _id; };
		const char *GetTopic() { return _topic; };
		RCESReplStatus GetStatus() { return _status; };
		RCESDateTime GetStatusTime() { return _statusTime; };
		char *GetStatusMsg() { return _statusMsg; };
		RCESMqttMsgFormat GetMsgFormat() { return _msgFormat; };
		int GetThreads() { return _threads; };
		int GetDBEngineID() { return _dbEngineID; };
		pRCESDBEngine GetDBEngine() { return _dbEngine; };
		int GetDatabaseID() { return _databaseID; };
		pRCESDatabase GetDatabase() { return _database; };
		char *GetTableName() { return _tableName; };
		bool HasReplication() { return _replication; };
		bool HasTimestamp() { return _timestamp; };
		bool HasTimestampIdx() { return _timestampIdx; };
		int GetRetentionPeriod() { return _retentionPeriod; };
		RCESMqttRetentionUnit GetRetentionUnit() { return _retentionUnit; };
		int GetFieldCount() { return _fieldCount; };
		ppRCESMqttPersistField GetFieldList() { return _fieldList; };

		void SetID( int id ) { _id = id; };
		void SetTopic( const char *topic );
		void SetStatus(RCESReplStatus status) { _status = status; };
		void SetStatusTime(RCESDateTime statusTime) { _statusTime = statusTime; };
		void SetStatusMsg(const char *statusMsg);
		void SettMsgFormat(RCESMqttMsgFormat msgFormat) { _msgFormat = msgFormat; };
		void SetThreads(int threads) { _threads = threads; };
		void SetDBEngineID(int dbEngineID) { _dbEngineID = dbEngineID; };
		void SetDBEngine(pRCESDBEngine dbEngine) { _dbEngine = dbEngine; };
		void SetDatabaseID(int databaseID) { _databaseID = databaseID; };
		void SetDatabase(pRCESDatabase database) { _database = database; };
		void SetTableName(const char *tableName);
		void SetHasReplication(bool replication) { _replication = replication; };
		void SetHasTimestamp(bool timestamp) { _timestamp = timestamp; };
		void SetHasTimestampIdx(bool timestampIdx) { _timestampIdx = timestampIdx; };
		void SetRetentionPeriod(int retentionPeriod) { _retentionPeriod = retentionPeriod; };
		void SetRetentionUnit(RCESMqttRetentionUnit retentionUnit) { _retentionUnit = retentionUnit; };
		void SetFieldList(ppRCESMqttPersistField fieldList, int fieldCount) { _fieldCount = fieldCount; _fieldList = fieldList; };

		pRCESJson GetJson(bool detail);

	private:
		/* private methods */
		void _init();

		/* Private properties */
		int _id;
		char *_topic;
		RCESReplStatus _status;
		RCESDateTime _statusTime;
		char *_statusMsg;
		RCESMqttMsgFormat _msgFormat;
		int _threads;
		int _dbEngineID;
		pRCESDBEngine _dbEngine;
		int _databaseID;
		pRCESDatabase _database;
		char *_tableName;
		bool _replication;
		bool _timestamp;
		bool _timestampIdx;
		int _retentionPeriod;
		RCESMqttRetentionUnit _retentionUnit;
		int _fieldCount;
		ppRCESMqttPersistField _fieldList;
};
/*~****************************************************************************/

#endif /* _FCRCESMQTTPERSIST_HPP_ */