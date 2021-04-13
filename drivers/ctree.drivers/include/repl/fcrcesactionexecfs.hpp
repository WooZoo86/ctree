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

#ifndef _FCRCESACTIONEXECFS_HPP_
#define _FCRCESACTIONEXECFS_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrcesmasterprov.hpp"
#include "fcrcesfilesystem.hpp"
#include "fcrcesactionexecbase.hpp"
#include "fcrcesfiletransfer.hpp"

/* Class type definitions */
class RCESFileSystem;
typedef RCESFileSystem *pRCESFileSystem, **ppRCESFileSystem;

/*^****************************************************************************\
*
*   RCESActionExecFS
*   Recon-e-Sense action executor class for Filesystem actions
*
\******************************************************************************/
class RCESActionExecFS : public RCESActionExecBase
{
public:
	/* Constructors & destructor */
	RCESActionExecFS(pRCESActionQueueCriteria queueCriteria, FCPool<RCESMasterConnPooled> *masterConnPool, FCCache<RCESVolume> *volumeCache);
	virtual ~RCESActionExecFS();

	/* Public Methods */
	void Add(pRCESAction action);
	void Update(pRCESAction action);
	void Delete(pRCESAction action);
	void Scan(pRCESAction action);
	void Load(pRCESAction action);
	void CheckDBEngine(pRCESAction action);
	void ScanReplAgent(pRCESAction action);
	void ImportReplAgent(pRCESAction action);
	void ScanFolder(pRCESAction action);

	pRCESConfig GetConfig() { return _config; };

private:
	/* Private properties */
	pRCESFileSystem _fileSystem;

	/* Private methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESActionExecFS *pRCESActionExecFS, **ppRCESActionExecFS;

#endif /* _FCRCESACTIONEXECFS_HPP_ */