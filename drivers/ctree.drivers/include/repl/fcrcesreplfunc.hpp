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

#ifndef _FCRCESREPLFUNC_HPP_
#define _FCRCESREPLFUNC_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#define RCES_REPLFUNC_TIMELIST "replPlanFunctionTimingList"
#define RCES_REPLFUNC_DIRECTION "direction"
#define RCES_REPLFUNC_NAME "name"
#define RCES_REPLFUNC_TOTALPERCENT "total_percent"
#define RCES_REPLFUNC_TOTALTIME "total_time"
#define RCES_REPLFUNC_CALLS "calls"
#define RCES_REPLFUNC_AVERAGE "average"

/* Replication exception direction string values */
#define RCES_REPLFUNC_DIRECT "direct"
#define RCES_REPLFUNC_REVERSE "reverse"

/* Class type definitions */
class RCESReplFunc;
typedef RCESReplFunc *pRCESReplFunc, **ppRCESReplFunc;

/*^****************************************************************************\
*
*   RCESReplFunc
*   Recon-e-Sense replication function timing class
*
\******************************************************************************/
class RCESReplFunc
{
public:
	/* Constructors & destructor */
	RCESReplFunc();
	virtual ~RCESReplFunc();

	/* Public services */

	/* Public methods */
	const char *GetName() { return _name; };
	int GetTotalPercent() { return _totalPercent; };
	RCESBigInt GetTotalTime() { return _totalTime; };
	RCESBigInt GetCalls() { return _calls; };
	RCESBigInt GetAverageTime() { return _averageTime; };

	void SetName(const char *name);
	void SetTotalPercent(int totalPercent) { _totalPercent = totalPercent; };
	void SetTotalTime(RCESBigInt totalTime) { _totalTime = totalTime; };
	void SetCalls(RCESBigInt calls) { _calls = calls; };
	void SetAverageTime(RCESBigInt averageTime) { _averageTime = averageTime; };

	pRCESJson GetJson(RCESReplDirection direction);

private:
	/* private properties */
	char *_name;
	int _totalPercent;
	RCESBigInt _totalTime;
	RCESBigInt _calls;
	RCESBigInt _averageTime;

	/* private methods */
};
/*~****************************************************************************/

#endif /* _FCRCESREPLFUNC_HPP_ */