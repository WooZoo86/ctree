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

#ifndef _FCRCESREPLEXCEP_HPP_
#define _FCRCESREPLEXCEP_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#define RCES_REPLEXCEP_LIST "replPlanMonitorExceptionList"
#define RCES_REPLEXCEP_REPLPLAN_ID "replPlanID"
#define RCES_REPLEXCEP_DIRECTION "direction"
#define RCES_REPLEXCEP_SEQUENCE_NUMBER "sequenceNumber"
#define RCES_REPLEXCEP_EXCEPTION_TIME "exceptionTime"
#define RCES_REPLEXCEP_TRANSACTION_NUMBER "transactionNumber"
#define RCES_REPLEXCEP_LOG_ENTRY_TIME "logEntryTime"
#define RCES_REPLEXCEP_LOG_NUMBER "logNumber"
#define RCES_REPLEXCEP_LOG_POSITION "logPosition"
#define RCES_REPLEXCEP_FILE_ID "fileID"
#define RCES_REPLEXCEP_OPERATION "operation"
#define RCES_REPLEXCEP_ERROR_CODE "errorCode"
#define RCES_REPLEXCEP_FILE_NAME "fileName"
#define RCES_REPLEXCEP_TOTAL "total"

/* Replication exception direction string values */
#define RCES_REPLEXCEP_DIRECT "direct"
#define RCES_REPLEXCEP_REVERSE "reverse"

/* Class type definitions */
class RCESReplExcep;
typedef RCESReplExcep *pRCESReplExcep, **ppRCESReplExcep;

/*^****************************************************************************\
*
*   RCESReplExcep
*   Recon-e-Sense replication exception class
*
\******************************************************************************/
class RCESReplExcep
{
public:
	/* Constructors & destructor */
	RCESReplExcep();
	virtual ~RCESReplExcep();

	/* Public services */
	static int ctAddReplExcep(pRCESMasterProvider masterProv, pRCESReplExcep replExcep);

	/* Public methods */
	int GetReplPlanID() { return _replPlanID; };
	RCESReplicationDirection GetDirection() { return _direction; };
	RCESBigInt GetSequenceNumber() { return _sequenceNumber; };
	RCESDateTime GetTime() { return _time; };
	RCESBigInt GetTransactionNumber() { return _transactionNumber; };
	RCESDateTime GetLogEntryTime() { return _logEntryTime; };
	int GetLogNumber() { return _logNumber; };
	int GetLogPosition() { return _logPostion; };
	int GetFileID() { return _fileID; };
	const char *GetOperation() { return _operation; };
	int GetErrorCode() { return _errorCode; };
	const char *GetFileName() { return _fileName; };

	void SetReplPlanID(int replPlanID) { _replPlanID = replPlanID; };
	void SetDirection(RCESReplicationDirection direction) { _direction = direction; };
	void SetSequenceNumber(RCESBigInt sequenceNumber) { _sequenceNumber = sequenceNumber; };
	void SetTime(RCESDateTime time) { _time = time; };
	void SetTransactionNumber(RCESBigInt transactionNumber) { _transactionNumber = transactionNumber; };
	void SetLogEntryTime(RCESDateTime logEntryTime) { _logEntryTime = logEntryTime; };
	void SetLogNumber(int logNumber) { _logNumber = logNumber; };
	void SetLogPosition(int logPostion) { _logPostion = logPostion; };
	void SetFileID(int fileID) { _fileID = fileID; };
	void SetOperation(const char *operation);
	void SetErrorCode(int errorCode) { _errorCode = errorCode; };
	void SetFileName(const char *fileName);

	pRCESJson GetJson();

private:
	/* private properties */
	int _replPlanID;
	RCESReplicationDirection _direction;
	RCESBigInt _sequenceNumber;
	RCESDateTime _time;
	RCESBigInt _transactionNumber;
	RCESDateTime _logEntryTime;
	int _logNumber;
	int _logPostion;
	int _fileID;
	char *_operation;
	int _errorCode;
	char *_fileName;

	/* private methods */
	void _init();
};
/*~****************************************************************************/

#endif /* _FCRCESREPLEXCEP_HPP_ */