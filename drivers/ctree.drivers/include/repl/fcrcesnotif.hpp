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

#ifndef _FCRCESNOTIF_HPP_
#define _FCRCESNOTIF_HPP_

#ifdef NCTREE_FILE_SUPPORT

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrceslogger.hpp"
#include "fcrcesaction.hpp"
#include "fcrcesactionqueue.hpp"

#include "fchashtable.hpp"

typedef struct NotifThrdData {
    const char *path;
    const char *keyPath;
    const char *mask;
    pRCESActionQueue queue;
	char errorMsg[RCES_MAX_ERRMSG_LEN+1];
    int errorCode;
    pRCESLogger logger;
	pRCESConfig config;
    RCESThrdState state;
    bool isCreateNew;
    bool isDeleteOld;
	FCHashTable<int> *fileList;
    void *dirHandle;
    bool isFileSystem;
    int volumeID;
	const char *volumeStr;
	int sourceOSID;
	int targetOSID;
	bool dbEngine;
} NotifThrdData, *pNotifThrdData, **ppNotifThrdData;

/*^****************************************************************************\
*
*   RCESNotification
*   Recon-e-Sense notification class
*
*   Implements a File System change notification
*
\******************************************************************************/
class RCESNotification
{
    public:
        /* Constructors & destructor */
        RCESNotification( int targetOSID, pRCESVolume volume, pRCESConfig config, pRCESLogger logger );
        virtual ~RCESNotification();

        /* Public methods */
        const char *GetErrorMsg();
        int GetErrorCode();
        void Start();
        void Terminate();

    protected:
        /* Protected properties */
        pRCESConfig _config;
        pRCESLogger _logger;
        pRCESActionQueue _queue;
        ppNotifThrdData _notifThrdListData;
        int _notifThrdCount;
        int _osID;
        pRCESVolume _volume;
        void **_notifThrdHandles;
        char _fileName[RCES_MAX_PATH+1];
		int _targetOSID;
		bool _dbEngine;

        /* Protected methods */
		virtual pRCESReplPlan _getReplPlan() = 0;
        virtual const char *_getPath() = 0;
        virtual const char *_getMask() = 0;
        virtual bool _getCreateNew() = 0;
        virtual bool _getDeleteOld() = 0;
		virtual FCHashTable<int> *_getFileList() = 0;
        virtual RCESConsumerType _getConsumer() = 0;
        virtual bool _getIsFileSystem() = 0;

        char *_getFullPath();
        void _createNotifThread();
        const char *_buildFileName( const char *filePath, const char *fileName );
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESNotification *pRCESNotification, **ppRCESNotification;

#endif /* NCTREE_FILE_SUPPORT */

#endif /* _FCRCESLOGGER_HPP_ */