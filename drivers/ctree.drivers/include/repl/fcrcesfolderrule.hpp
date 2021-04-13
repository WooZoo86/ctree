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

#ifndef _FCRCESFOLDERRULE_HPP_
#define _FCRCESFOLDERRULE_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesaux.hpp"
#include "fcrcespublicationrule.hpp"
#include "fcrcesrule.hpp"

extern "C" {
#include "fcrcesjson.h"
}

#define RCES_FOLDERRULE_LIST "folderList"
#define RCES_FOLDERRULE_ID "id"
#define RCES_FOLDERRULE_VOLUME "folderVolume"
#define RCES_FOLDERRULE_PATH "folderPath"
#define RCES_FOLDERRULE_TYPE "listType"
#define RCES_FOLDERRULE_FILENAMES "filenames"
#define RCES_FOLDERRULE_FILEWILDCARDS "filenameWildcards"
#define RCES_FOLDERRULE_FILEREGEX "filenameRegex"

#define RCES_FOLDERRULE_TYPE_EXCLUDE "exclude"
#define RCES_FOLDERRULE_TYPE_INCLUDE "include"

/*^****************************************************************************\
*
*   RCESFolderRule
*   Recon-e-Sense publication folder rule class
*
\******************************************************************************/
class RCESFolderRule : public RCESRule
{
public:
	/* Constructors & destructor */
	RCESFolderRule();
	RCESFolderRule(RCESFolderRule *folderRule);
	RCESFolderRule(pRCESJson folderRule);
	virtual ~RCESFolderRule();

	/* Public services */
	static int ctGetFolderRules(pRCESMasterProvider masterProv, int publicationID, int folderRuleListSize, int folderRuleStart, ppRCESFolderRule *folderRuleList,
		int *folderRuleCount, int *totalFolderRules);
	static int ctGetFolderRules(pRCESMasterProvider masterConn, int publicationID, bool paging, int folderRuleListSize, int folderRuleStart, ppRCESJson result);
	static int ctAddFoldersToPublication(pRCESMasterProvider masterProv, int publicationID, ppRCESFolderRule folderRuleList, int folderRuleCount);
	static int ctRemoveFoldersFromPublication(pRCESMasterProvider masterProv, int publicationID, int *folderIDList, int folderCount);

	/* Public methods */
	int GetID() { return _id; };
	int GetVolumeID() { return _volumeID; };
	const char *GetVolumeName() { return _volumeName; };
	const char *GetPath() { return _path; };
	RCESPublicationRuleType GetType() { return _type; };
	FCList<RCESPublicationRule> *GetFileNameRules() { return _fileNameRuleList; };
	FCList<RCESPublicationRule> *GetFileWildcardRules() { return _fileWildcardRuleList; };
	FCList<RCESPublicationRule> *GetFileRegexRules() { return _fileRegexRuleList; };

	void SetID(int fileID) { _id = fileID; };
	void SetVolumeID(int volumeID) { _volumeID = volumeID; };
	void SetVolumeName(const char *volumeName);
	void SetPath(const char *path);
	void SetType(RCESPublicationRuleType type) { _type = type; };

	pRCESJson GetJson();
	bool FileMatchesRules(const char *fileName, bool caseSensitive);

private:
	/* Private properties */
	int _id;
	int _volumeID;
	char *_volumeName;
	char *_path;
	RCESPublicationRuleType _type;
	FCList<RCESPublicationRule> *_fileNameRuleList;
	FCList<RCESPublicationRule> *_fileWildcardRuleList;
	FCList<RCESPublicationRule> *_fileRegexRuleList;

	/* Private methods */
	void _init();
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESFolderRule *pRCESFolderRule, **ppRCESFolderRule;

#endif /* _FCRCESFOLDERRULE_HPP_ */