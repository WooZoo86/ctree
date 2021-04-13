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

#ifndef _FCRCESREPLBASE_HPP_
#define _FCRCESREPLBASE_HPP_

#include "fc_rces.h"
#include "fcrcesrepl.hpp"
#include "fcrcesreplplan.hpp"

/*^****************************************************************************\
*
*   RCESReplBase
*   Recon-e-Sense replication base class
*
*   Manage the replication basic actions
*
\******************************************************************************/
class RCESReplBase : public RCESRepl
{
    public:
        /* Constructors & destructor */
		RCESReplBase( pRCESReplPlan replPlan, pRCESMasterProvider provider );
        virtual ~RCESReplBase();

		/* Public Methods */
		void Deploy( bool forceReplace, int *actionID );
		void Start( const char *sourceLogPos, const char *targetLogPos, bool ignoreDeploy, int *actionID );
		void Stop( bool wait, int *actionID = NULL );
		void RegConsumers( int ownerActionID );
		void CheckReplPlanAgents();
		void CleanPendingReplication();
		void CheckPendingReplication();
		void StartMonitor( int refreshRate );
		void StopMonitor();
		void StartExcepLog();
		void StopExcepLog();
		void StartFuncTime();
		void StopFuncTime();
		void ResetFuncTime();
		void GetFuncTimes( char **content, int *contentLen );
		void Pause();
		void Resume();
		void Resync(int *fileIDList, int fileCount, bool addNewFiles, int *actionID);

    private:
        /* Private properties */

        /* Private methods */
		void _registerSource( int actionID );
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESReplBase *pRCESReplBase, **ppRCESReplBase;

#endif /* _FCRCESREPLBASE_HPP_ */