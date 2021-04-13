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

#ifndef _FCRCESACTIONEXECBASE_HPP_
#define _FCRCESACTIONEXECBASE_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrceslogger.hpp"
#include "fcrcesmasterprov.hpp"
#include "fcrceslocalprov.hpp"
#include "fcrcesfiletransfer.hpp"
#include "fcrcesreplplanmngr.hpp"

/* Class type definitions */
class RCESConsumer;
class RCESActionExecBase;
typedef RCESConsumer *pRCESConsumer, **ppRCESConsumer;
typedef RCESActionExecBase *pRCESActionExecBase, **ppRCESActionExecBase;

/*^****************************************************************************\
*
*   RCESActionExecBase
*   Recon-e-Sense action executor common class for both ctree and non-ctree 
*   executor classes 
*
\******************************************************************************/
class RCESActionExecBase
{
public:
	/* Constructors & destructor */
	RCESActionExecBase(pRCESActionQueueCriteria queueCriteria, FCPool<RCESMasterConnPooled> *masterConnPool,
	                   FCCache<RCESVolume> *volumeCache);
	virtual ~RCESActionExecBase();

	/* Public Methods */

protected:
	/* Protected properties */
	pRCESConfig _config;
	FCPool<RCESMasterConnPooled> *_masterConnPool;
	FCCache<RCESVolume> *_volumeCache;
	pRCESLocalProvider _localProvider;
	pRCESActionQueueCriteria _queueCriteria;
	char _sourceFileName[RCES_MAX_PATH + 1];
	char _targetFileName[RCES_MAX_PATH + 1];
	char _sourceFilePath[RCES_MAX_PATH + 1];
	char _targetFilePath[RCES_MAX_PATH + 1];
	int _maskCount;
	const char **_maskList;
	char _errorMsg[RCES_MAX_ERRMSG_LEN + 1];

	/* Protected methods */
#ifdef NCTREE_FILE_SUPPORT
	void Sync(pRCESAction action, FCHashTable<int> *fileList);
	void Delete(pRCESAction action);
#endif /* NCTREE_FILE_SUPPORT */

protected:

	/* Protected methods */
#ifdef NCTREE_FILE_SUPPORT
	bool _buildFullNames(pRCESAction action);
	void _copyDir(const char *sourceDir, const char *targetDir, FCHashTable<int> *fileList);
	void _addFileList(pRCESFile file, FCHashTable<int> *fileList);
#endif /* NCTREE_FILE_SUPPORT */
	void ConnectLocalProv();
};
/*~****************************************************************************/

#endif /* _FCRCESACTIONEXECBASE_HPP_ */