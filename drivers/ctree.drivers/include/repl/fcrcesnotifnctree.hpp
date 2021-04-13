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

#ifndef _FCRCESNOTIFNCTREE_HPP_
#define _FCRCESNOTIFNCTREE_HPP_

#include "fcrcesnotif.hpp"
#include "fchashtable.hpp"

/*^****************************************************************************\
*
*   RCESNotifNCtree
*   Recon-e-Sense notification class for non-ctree file replication
*
*   Implements a File System change notification for non-ctree file replication
*
\******************************************************************************/
class RCESNotifNCtree : public RCESNotification
{
    public:
        /* Constructors & destructor */
		RCESNotifNCtree( int targetOSID, pRCESSubscription subscription, pRCESVolume volume, const char *filePath, bool isDir, bool createNew, 
		                 bool deleteOld, pRCESConfig config, pRCESLogger logger );
        virtual ~RCESNotifNCtree();

        /* Public methods */
        bool CheckPath( const char *path );
        void AddFile( int fileID, const char *filePath, const char *fileName );
		void AddFileList( FCHashTable<int> *fileList );
        void RemoveFile( const char *filePath, const char *fileName );

    protected:
        /* Protected properties */

        /* Protected methods */
		pRCESSubscription _getSubscription() { return _subscription; };
        const char *_getPath() { return _path; };
		const char *_getMask() { return _subscription->GetFileMask(); };
        bool _getCreateNew() { return _createNew; };
        bool _getDeleteOld() { return _deleteOld; };
		FCHashTable<int> *_getFileList() { return _fileList; };
        RCESConsumerType _getConsumer() { return RCES_REPL_NCTREE; };
        bool _getIsFileSystem() { return false; };

    private:
        /* Private properties */
        char *_path;
        bool _isDir;
        bool _createNew;
        bool _deleteOld;
		FCHashTable<int> *_fileList;
		pRCESSubscription _subscription;

        /* Private methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESNotifNCtree *pRCESNotifNCtree, **ppRCESNotifNCtree;

#endif /* _FCRCESNOTIFNCTREE_HPP_ */

#endif /* NCTREE_FILE_SUPPORT */