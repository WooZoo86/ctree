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

#ifndef _FCRCESNOTIFFS_HPP_
#define _FCRCESNOTIFFS_HPP_

#ifdef NCTREE_FILE_SUPPORT

#include "fcrcesnotif.hpp"

/*^****************************************************************************\
*
*   RCESNotifFS
*   Recon-e-Sense notification class for full filesystem
*
*   Implements a File System change notification for full filesystem
*
\******************************************************************************/
class RCESNotifFS : public RCESNotification
{
    public:
        /* Constructors & destructor */
        RCESNotifFS( int targetOSID, pRCESVolume volume, const char *mask, const char *rootTreePath, pRCESConfig config, pRCESLogger logger );
        virtual ~RCESNotifFS();

        /* Public methods */

    protected:
        /* Protected properties */

        /* Protected methods */
		pRCESReplPlan _getReplPlan() { return NULL; };
        const char *_getRootPath() { return _path; };
        const char *_getPath() { return ""; };
        const char *_getMask() { return _mask; };
        bool _getCreateNew() { return true; };
        bool _getDeleteOld() { return true; };
		FCHashTable<int> *_getFileList() { return NULL; };
        RCESConsumerType _getConsumer() { return RCES_FILESYSTEM_SYNC; };
        bool _getIsFileSystem() { return true; };

    private:
        /* Private properties */
        char *_mask;
		char *_path;

        /* Private methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESNotifFS *pRCESNotifFS, **ppRCESNotifFS;

#endif /* NCTREE_FILE_SUPPORT */

#endif /* _FCRCESNOTIFFS_HPP_ */