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

#include "fcpool.hpp"
#include "fcexception.hpp"

extern const char *_INACTIVE_TIMEOUT;

/*^****************************************************************************\
*
*   Constructor: FCPool
*
*   Parameters:  poolSize
*                Pool size
*
\******************************************************************************/
template <class T> FCPool<T>::FCPool( int poolSize )
{
	_init( poolSize );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Constructor: FCPool
*                When all the elements will be of the same config
*
*   Parameters:  config
*                Config object for the object to be acquired.
*
*                poolSize
*                Pool size
*
*                inactiveTimeOut
*                Inactive timeout in seconds
*
\******************************************************************************/
template <class T> FCPool<T>::FCPool( pFCConfig config, int poolSize, int inactiveTimeOut )
{
	_init( poolSize );

	/* Keep the configuration object for the pool */
	_config = config;

	_inactiveTimeout = inactiveTimeOut;
	_lastUsedTime = fcGetSysTimer();
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Destructor: FCPool::FCPool
*
\******************************************************************************/
template <class T> FCPool<T>::~FCPool()
{
	/* Block new acquires */
	_block = true;

	/* Release all the objects */
	try {
		ReleaseAll( FC_TIMEOUT );
	}
	catch (FCException &) {
	}

	/* Term and detroy all the pooled objects */
	for( int i = 0; i < _availCount; i++ )
	{
		if(_availList[i]) {
			_availList[i]->Term();
			delete (T *)_availList[i];
		}
	}

	/* Release resources */
	if( _availList )
		RCESFree( _availList );
	if( _usedList )
		RCESFree( _usedList );
	if( _blockList )
		delete _blockList;
	fcMutexFree( _poolMutex );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Acquire
*               Retrieve a object from the pool when the internal config object
*               will be used.
*
*   Parameters: timeout [IN]
*               Timeout in seconds or -1 if wait forever.
*
*   Returns:    Object from the pool or NULL if there isn't any available
*
\******************************************************************************/
template <class T> T *FCPool<T>::Acquire( int timeout )
{
	return Acquire( _config, timeout );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Acquire
*               Retrieve a object from the pool.
*
*   Parameters: config [IN]
*               Config object for the object to be acquired.
*
*               timeout [IN]
*               Timeout in seconds or -1 if wait forever.
*
*   Returns:    Object from the pool or NULL if there isn't any available
*
\******************************************************************************/
template <class T> T *FCPool<T>::Acquire( pFCConfig config, int timeout )
{
	T *retval = NULL;
	int retries = 0;
	bool mutrel = false;
	bool userel = false;

	/* Check if pool is already blocked */
	if( _isBlocked( config ) )
		throw FCException(0, NULL, "FCPool::Acquire", 1, FC_POOL_LOCKED_ERR, "Couldn't acquire object, pool is blocked", __FILE__, __LINE__ );

	try {
		/* If there isn't any available, retry up to timeout */
		while( retval == NULL && ( ( retries * FC_REFRESH ) < timeout * 1000  || timeout < 0 ) )
		{
			userel = false;
			fcMutexGet(_poolMutex);
			mutrel = true;

			/* If there is any object available, try to acquire it */
			if( _availCount > 0 )
			{
				/* Check if any of the available object matches the request */
				for( int i = (_availCount-1); i >= 0 && retval == NULL; i-- )
				{
					if( _availList[i] && _availList[i]->Matches( config ) )
					{
						/* Move the available object form the available to the used list */
						retval = _availList[i];
						for( int j = i; j < (_availCount-1); j++ )
							_availList[j] = _availList[j+1];
						_availCount--;
					}
				}
			}

			/* If not found any available object, check if it is possible to create a new one */
			bool isNew = false;
			if( retval == NULL && (_availCount + _usedCount) < _poolSize )
			{
				retval = new T( config );
				isNew = true;
			}

			if( retval )
			{
				_usedList[ _usedCount++ ] = retval;
				userel = true;
			}

			fcMutexRel( _poolMutex );
			mutrel = false;

			if( !retval )
				fcSleep( FC_REFRESH );
			else
				if( isNew )
					retval->Init();
				else
					retval->Attach();

			retries++;
		}
	}
	catch(FCException &ex) {
		if (userel)
		{
			if (!mutrel) {
				fcMutexGet(_poolMutex);
				mutrel = true;
			}
			_usedCount--;
			_usedList[_usedCount++] = NULL;
		}

		if (mutrel)
			fcMutexRel( _poolMutex );

		if(retval) {
			delete retval;
			retval = NULL;
		}

		throw FCException(ex);
	}

	if( !retval )
		throw FCException(0, NULL, "FCPool::Acquire", 2, FC_LISTFULL_ERR, "Couldn't acquire object, pool is exhausted", __FILE__, __LINE__ );

	return retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Acquire
*               Retrieve a object from the pool.
*
*
*   Returns:    Object from the pool or NULL if there isn't any available, 
*               does not attempt o create a new object.
*
\******************************************************************************/
template <class T> T *FCPool<T>::Acquire()
{
	T *retval = NULL;
	bool need_relese = false;

	/* Check if pool is already blocked */
	if (_isBlocked(_config))
		throw FCException(0, NULL, "FCPool::Acquire", 1, FC_POOL_LOCKED_ERR, "Couldn't acquire object, pool is blocked", __FILE__, __LINE__);

	try {
		/* If there isn't any available, retry up to timeout */
		fcMutexGet(_poolMutex);
		need_relese = true;

		/* If there is any object available, try to acquire it */
		if (_availCount > 0)
		{
			/* Check if any of the available object matches the request */
			for (int i = (_availCount - 1); i >= 0 && retval == NULL; i--)
			{
				if (_availList[i] && _availList[i]->Matches(_config))
				{
					/* Move the available object form the available to the used list */
					retval = _availList[i];
					for (int j = i; j < (_availCount - 1); j++)
						_availList[j] = _availList[j + 1];
					_availCount--;
				}
			}
		}

		if (retval)
		{
			_usedList[_usedCount++] = retval;
		}
		fcMutexRel(_poolMutex);
		need_relese = false;

		if (retval)
			retval->Attach();
	}
	catch (FCException &ex) {

		if (need_relese)
			fcMutexRel(_poolMutex);

		if (retval) {
			delete retval;
			retval = NULL;
		}

		throw FCException(ex);
	}

	if (!retval)
		throw FCException(0, NULL, "FCPool::Acquire", 2, FC_LISTFULL_ERR, "Couldn't acquire object, pool is exhausted", __FILE__, __LINE__);

	return retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Release
*               Return an object into the pool
*
*   Parameters: object [IN]
*               Object to be returned into the pool
*
\******************************************************************************/
template <class T> void FCPool<T>::Release( T *object )
{
	fcMutexGet(_poolMutex);

	int pos = 0;

	/* Search for the object to be released in the used list */
	while( _usedList[pos] != object && pos < _usedCount )
		pos++;

	/* In case object is not in the pool, ignore it */
	if(  _usedList[pos] != object )
		goto EXIT;

	try {
		object->Detach();
	}
	catch(FCException &) {
	}

	/* Move the object from the used to the available list */
	_availList[ _availCount++ ] = object;
	while( pos < _usedCount && _usedList[pos] )
	{
		_usedList[pos] = _usedList[pos+1];
		pos++;
	}
	_usedCount--;

EXIT:
	fcMutexRel( _poolMutex );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     ReleaseAll
*               Return all objects in use into the pool
*
*   Parameters: timeout [IN]
*               Timeout in seconds or -1 if wait forever.
*
\******************************************************************************/
template <class T> void FCPool<T>::ReleaseAll( int timeout )
{
	int retries = 0;

	/* If there is at least one object in use, retry up to timeout */
	while( _isPending() && ( ( retries * FC_REFRESH ) < timeout * 1000  || timeout < 0 ) )
	{
		fcSleep( FC_REFRESH );
		retries++;
	}

	/* If timeout, throw an exception */
	if( _isPending() )
		throw FCException(0, NULL, "FCPool::ReleaseAll", 2, FC_POOL_INUSE_ERR, "Pool has at least one object holding the releaseAll", __FILE__, __LINE__ );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Clean
*               Terminate and destroy all the objects of the given configuration,
*               if NULL is provided, clean all of them when the internal config
*               object will be used.
*
*   Parameters: timeout [IN]
*               Timeout in seconds or -1 if wait forever.
*
\******************************************************************************/
template <class T> void FCPool<T>::Clean( int timeout )
{
	Clean( timeout, _config );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Clean
*               Terminate and destroy all the objects of the given configuration,
*               if NULL is provided, clean all of them
*
*   Parameters: timeout [IN]
*               Timeout in seconds or -1 if wait forever.
*
*               config [IN]
*               Config object to be cleaned
*
\******************************************************************************/
template <class T> void FCPool<T>::Clean( int timeout, pFCConfig config )
{
	/* Check if pool is already blocked */
	if( _isBlocked( config ) )
		throw FCException(0, NULL, "FCPool::Clean", 1, FC_POOL_LOCKED_ERR, "Couldn't clean pool, it is blocked", __FILE__, __LINE__ );

	/* Block the matching objects */
	if( !config )
		_block = true;
	else
		_blockList->Add( config );

	/* If there is at least one object in use, retry up to timeout */
	int retries = 0;
	while( _isPending() && ( ( retries * FC_REFRESH ) < timeout * 1000  || timeout < 0 ) )
	{
		fcSleep( FC_REFRESH );
		retries++;
	}

	/* If timeout, throw an exception */
	if( _isPending() )
	{
		_blockList->Remove( config, false );
		throw FCException(0, NULL, "FCPool::Clean", 1, FC_POOL_INUSE_ERR, "Pool has at least one object holding the cleanup", __FILE__, __LINE__ );
	}

	fcMutexGet(_poolMutex);

	try {
		/* Clean all the matching objects */
		for( int i = _availCount-1; i >= 0; i-- )
		{
			if( _availList[i] && _availList[i]->Matches( config ) )
			{
				delete (T *)_availList[i];
				for( int j = i; j < (_availCount-1); j++ )
					_availList[j] = _availList[j+1];
				_availCount--;
			}
		}
	}
	catch(FCException &e) {
		fcMutexRel( _poolMutex );
		throw e;
	}

	fcMutexRel( _poolMutex );

	/* Unblock it after clean it up */
	_blockList->Remove( config, false );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     CleanUnused
*               Check through all the available objects which ones haven't been
*               used for the INACTIVE_TIMEOUT period of time (this value is set
*               ctsrvr.cfg at SUBSYSTEM REPLICATION AGENT session. All the ones
*               that are inactive, will be removed from the pool. It is only 
*               possible because the Acquire() method always return the object
*               using the same sort.
*
\******************************************************************************/
template <class T> void FCPool<T>::CleanUnused()
{
	fcMutexGet(_poolMutex);

	try {
		/* Loop through all the available objects */
		for( int i = 0; i < _availCount; i++ )
		{
			/* Check if current pooled object is inactive */
			if( ( (long)( fcGetSysTimer() - _availList[i]->GetLastUsed() ) / 1000 ) >= _inactiveTimeout )
			{
				delete (T *)_availList[i];
				for( int j = i; j < (_availCount-1); j++ )
					_availList[j] = _availList[j+1];
				_availCount--;
			}
		}
	}
	catch(FCException &e) {
		fcMutexRel( _poolMutex );
		throw e;
	}

	fcMutexRel( _poolMutex );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     _isPending
*               Check if there at least one object in use for the given 
*               configuration object, if NULL is provided, check for all the
*               objects
*
*   Parameters: config [IN]
*               Config object to be cleaned
*
*   Return:     True if there at least one matching object in use, otherwise,
*               False
*
\******************************************************************************/
template <class T> bool FCPool<T>::_isPending( pFCConfig config )
{
	bool isPending = false;

	fcMutexGet(_poolMutex);
	if( !config )
		isPending = _usedCount > 0;
	else
	{
		for( int i = 0; i < _usedCount && !isPending; i++ )
		{
			if( _usedList[i] && _usedList[i]->Matches( config ) )
				isPending = true;
		}
	}
	fcMutexRel( _poolMutex );

	return isPending;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     _isBlocked
*               Check if the given configuration is blocked or not
*
*   Parameters: config [IN]
*               Config object to be checked
*
*   Return:     True if given configuration is blocked, otherwise, False
*
\******************************************************************************/
template <class T> bool FCPool<T>::_isBlocked( pFCConfig config )
{
	if( _block )
		return true;
	else
		return _blockList->GetPos( config ) > 0;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     IncUse
*               Increment pool usage
*
\******************************************************************************/
template <class T> void FCPool<T>::IncUse()
{
	fcMutexGet(_poolMutex);
	_useCount++;
	fcMutexRel( _poolMutex );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     DecUse
*               Decrement pool usage
*
\******************************************************************************/
template <class T> void FCPool<T>::DecUse()
{
	fcMutexGet(_poolMutex);
	_useCount--;
	fcMutexRel( _poolMutex );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     GetUseCount
*               Retrieve the pool usage count
*
\******************************************************************************/
template <class T> int FCPool<T>::GetUseCount()
{
	int retval = 0;
	fcMutexGet(_poolMutex);
	retval = _useCount;
	fcMutexRel( _poolMutex );
	return retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method: isInactive
*           Check if the current object pool is not already inactive
*
\******************************************************************************/
template <class T> bool FCPool<T>::isInactive()
{ 
	return _usedCount == 0 && (int)( ( fcGetSysTimer() - _lastUsedTime ) / 1000 ) >= _inactiveTimeout; 
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method: GetRemainTime
*           Retrieve the remaining time before the object timeout by inactivity
*
\******************************************************************************/
template <class T> int FCPool<T>::GetRemainTime()
{
	return _inactiveTimeout - (int)( ( fcGetSysTimer() - _lastUsedTime ) / 1000 );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method: _init
*           Initialize the pool object
*
*   Parameters:  poolSize
*                Pool size
*
\******************************************************************************/
template <class T> void FCPool<T>::_init( int poolSize )
{
	_useCount = 0;
	_poolSize = poolSize;
	_availCount = _usedCount = 0;
	_block = false;

	_inactiveTimeout = 60;
	_lastUsedTime = fcGetSysTimer();

	/* Allocate both available and used list */
	_availList = (T **) RCESAlloc( poolSize * sizeof(T *) );
	if( !_availList )
		throw FCException(0, NULL, "FCPool::FCPool", 0, FC_MEM_ERR, "Couldn't allocate available list array", __FILE__, __LINE__);
	_usedList = (T **) RCESAlloc( poolSize * sizeof(T *) );
	if( !_usedList )
		throw FCException(0, NULL, "FCPool::FCPool", 0, FC_MEM_ERR, "Couldn't allocate user list array", __FILE__, __LINE__);
	memset( _usedList, 0, poolSize * sizeof(T *) );

	/* Allocate the list of object configurations to be blocked */
	_blockList = new FCList<FCConfig>;
	
	_config = NULL;

	/* Create mutex for synchronizing all the pool operations in multi-threads */
	_poolMutex = fcMutexCreate();
}
/*~****************************************************************************/