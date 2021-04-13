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

#ifndef _FCPOOL_HPP_
#define _FCPOOL_HPP_

#define FC_MAX_HASH_SIZE 1024
#define FC_MAX_BUF 1024
#define FC_TIMEOUT 10          /* Default timeout in seconds                      */
#define FC_REFRESH 1000        /* Refresh sleep time in miliseconds               */
#define LIST_BLOCK_SIZE 100    /* Block size for incremental list capacity expand */
#define MAX_CONFIG_KEYS 32     /* Max number of configuration elements            */

#include "fcaux.hpp"
#include "fchashtable.hpp"
#include "fclist.hpp"

/* Class type definitions */
class FCConfig;
typedef FCConfig *pFCConfig, **ppFCConfig;

/*^****************************************************************************\
*
*   FCPool
*   Generic object pool class
*
\******************************************************************************/
template <class T> class FCPool
{
	public:
		/* Constructors & destructor */
		FCPool( pFCConfig config, int poolSize, int inactiveTimeOut );
		FCPool( int poolSize );
		virtual ~FCPool();

		/* Public Methods */
		T *Acquire();
		T *Acquire( int timeout );
		T *Acquire( pFCConfig config, int timeout );
		void Release( T *obj );
		void ReleaseAll( int timeout );
		void Clean( int timeout );
		void Clean( int timeout, pFCConfig config );
		void CleanUnused();
		int Count() { return _poolSize; };
		pFCConfig GetConfig() { return _config; };

		void IncUse();
		void DecUse();
		int GetUseCount();
		bool IsEmpty() { return ((_availCount + _usedCount) == 0); }

		void Use() { _lastUsedTime = fcGetSysTimer(); };
		bool isInactive();
		int GetRemainTime();

	protected:
		T **_availList;
		int _poolSize;

	private:
		/* Private properties */
		bool _block;
		int _availCount;
		int _usedCount;
		T **_usedList;
		FCList<FCConfig> *_blockList;
		void *_poolMutex;
		pFCConfig _config;
		int _useCount;
		TIMER _lastUsedTime;
		int _inactiveTimeout; /* Inactive timeout in seconds */

		/* Private methods */
		bool _isPending( pFCConfig config = NULL );
		bool _isBlocked( pFCConfig config );
		void _init( int poolSize );
};
/*~****************************************************************************/

#include "fcpool.ipp"

#endif /* _FCPOOL_HPP_ */