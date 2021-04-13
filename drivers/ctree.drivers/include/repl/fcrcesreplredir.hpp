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

#ifndef _FCRCESREPLREDIR_HPP_
#define _FCRCESREPLREDIR_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"
#include "fcrcesreplplanmngr.hpp"

/* Class type definitions */
class RCESReplRedir;
class RCESMasterProvider;
typedef RCESReplRedir *pRCESReplRedir, **ppRCESReplRedir;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_REDIR_SOURCE "sourcePath"
#define RCES_REDIR_TARGET "targetPath"

/*^****************************************************************************\
*
*   RCESReplRedir
*   Recon-e-Sense Replication Redirection class
*
\******************************************************************************/
class RCESReplRedir
{
	public:
		/* Constructors & destructor */
		RCESReplRedir();
		RCESReplRedir(pRCESReplRedir replRedir);
		virtual ~RCESReplRedir();

		/* Public services */
		static int ctGetReplRedirsByReplPlan( pRCESMasterProvider masterProv, int replPlanID, ppRCESReplRedir *replRedirList, int *replRedirCount );
		static int ctPersistReplRedir( pRCESMasterProvider masterProv, pRCESReplRedir replRedir );
		static void Json2RedirList(pRCESJson redirListJson, ppRCESReplRedir *redirList, int *redirListCount);
		static pRCESJson RedirList2Json(ppRCESReplRedir redirList, int redirListCount);

		/* Public methods */
		int GetSubsID() { return _subsID;  };
		const char *GetSource() { return _source; };
		const char *GetTarget() { return _target; };
		RCESReplicationDirection GetDirection() { return _direction; };
		bool IsSourcePathCaseSensitive() {return _sourcePathCaseSensitive;};

		void SetSubsID(int subsID) { _subsID = subsID; }
		void SetSource( const char *source );
		void SetTarget( const char *target );
		void SetDirection( RCESReplicationDirection direction ) { _direction = direction; };
		void SetSourcePathCaseSensitive(bool sourcePathCaseSensitive) { _sourcePathCaseSensitive = sourcePathCaseSensitive; };

		pRCESJson GetJson();

	private:
		/* Private properties */
		int _subsID;
		char *_source;
		char *_target;
		bool _sourcePathCaseSensitive;
		RCESReplicationDirection _direction;
};
/*~****************************************************************************/

#endif /* _FCRCESREPLREDIR_HPP_ */