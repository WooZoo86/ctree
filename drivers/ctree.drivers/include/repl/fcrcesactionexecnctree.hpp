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

#ifdef NCTREE_FILE_SUPPORT

#ifndef _FCRCESACTIONEXECNCTREE_HPP_
#define _FCRCESACTIONEXECNCTREE_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrcesmasterprov.hpp"
#include "fcrcesactionexecbase.hpp"
#include "fcrcesnotifnctree.hpp"

/*^****************************************************************************\
*
*   RCESActionExecNCtree
*   Recon-e-Sense action executor class for NON c-tree actions
*
\******************************************************************************/
class RCESActionExecNCtree : public RCESActionExecBase
{
    public:
        /* Constructors & destructor */
		RCESActionExecNCtree( pRCESSubscriptionMngr subscriptionMngr, pRCESActionQueue queue, FCPool<RCESMasterConnPooled> *masterConnPool, 
		                      FCCache<RCESVolume> *volumeCache, FCHashTable<RCESConsumer> *consumerList, FCHashTable<RCESNotifNCtree> *notifList );
        virtual ~RCESActionExecNCtree();

        /* Public Methods */
        void Add( pRCESAction action );
        void Update( pRCESAction action );
        void Delete( pRCESAction action );
        void Sync( pRCESAction action );
		void CheckConsumers( pRCESAction action );

    private:
		/* Private properties */
		FCHashTable<RCESNotifNCtree> *_notifList;
		int _targetOSID;
		pRCESReplPlanMngr _replPlanMngr;

        /* Private methods */
        void _intCopyFile( bool isFile );

        void _checkNotification( pRCESReplFile replFile );
        pRCESNotifNCtree _findNotifByPath( const char *path );
		void _addNotif( const char *filePath, bool isDir, bool createNew, bool deleteOld, ppRCESNotifNCtree notification);
		void _setNotificationFileList( FCHashTable<int> *fileList );
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESActionExecNCtree *pRCESActionExecNCtree, **ppRCESActionExecNCtree;

#endif /* _FCRCESACTIONEXECNCTREE_HPP_ */

#endif /* NCTREE_FILE_SUPPORT */