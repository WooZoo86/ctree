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

#ifndef _FCRCESDBRULE_HPP_
#define _FCRCESDBRULE_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"
#include "fcrcespublicationrule.hpp"
#include "fcrcesrule.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#define RCES_DBRULE_LIST "databaseRuleList"
#define RCES_DBRULE_DATABASE "database"
#define RCES_DBRULE_DATABASENAME "databaseName"
#define RCES_DBRULE_TYPE "listType"
#define RCES_DBRULE_FILENAMES "tableNames"
#define RCES_DBRULE_FILEWILDCARDS "tableNameWildcards"
#define RCES_DBRULE_FILEREGEX "tableNameRegex"

#define RCES_DBRULE_TYPE_EXCLUDE "exclude"
#define RCES_DBRULE_TYPE_INCLUDE "include"

/*^****************************************************************************\
*
*   RCESDatabaseRule
*   Recon-e-Sense publication database rule class
*
\******************************************************************************/
class RCESDatabaseRule : public RCESRule
{
public:
	/* Constructors & destructor */
	RCESDatabaseRule();
	RCESDatabaseRule(pRCESDatabaseRule dbRule);
	RCESDatabaseRule(pRCESJson dbRule);
	virtual ~RCESDatabaseRule();

	/* Public services */
	static int ctGetDatabaseRules(pRCESMasterProvider masterProv, int publicationID, ppRCESDatabaseRule dbRuleList);
	static int ctGetDatabaseRules(pRCESMasterProvider masterConn, int publicationID, ppRCESJson result);
	static int ctPersistDatabaseRule(pRCESMasterProvider masterProv, int publicationID, pRCESDatabaseRule dbRule);

	/* Public methods */
	int GetID() { return _id; };
	const char *GetDatabaseName() { return _databaseName; };
	RCESPublicationRuleType GetType() { return _type; };
	FCList<RCESPublicationRule> *GetTableNameRules() { return _tableNameRuleList; };
	FCList<RCESPublicationRule> *GetTableWildcardRules() { return _tableWildcardRuleList; };
	FCList<RCESPublicationRule> *GetTableRegexRules() { return _tableRegexRuleList; };

	void SetID(int databaseID) { _id = databaseID; };
	void SetDatabaseName(const char *databaseName);
	void SetType(RCESPublicationRuleType type) { _type = type; };

	pRCESJson GetJson();
	bool TableMatchesRules(const char *tableName);

private:
	/* Private properties */
	int _id;
	char *_databaseName;
	RCESPublicationRuleType _type;
	FCList<RCESPublicationRule> *_tableNameRuleList;
	FCList<RCESPublicationRule> *_tableWildcardRuleList;
	FCList<RCESPublicationRule> *_tableRegexRuleList;

	/* Private methods */
	void _init();
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESDatabaseRule *pRCESDatabaseRule, **ppRCESDatabaseRule;

#endif /* _FCRCESDBRULE_HPP_ */