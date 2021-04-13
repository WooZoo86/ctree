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

void *RCESAlloc( int bufSize );

/*^****************************************************************************\
*
*   Constructor: FCHashTable
*
*   Parameters: size [IN]
*               Hash capacity size
*
*               deleteItem [IN]
*               Flag indicating if the hashed object should be deleted or not
*
\******************************************************************************/
template <class T> FCHashTable<T>::FCHashTable( int size, bool deleteItem )
{
	/* Allocate the list of hash item objects */
	_capacity = size;
	_count = 0;
	_currentPos = 0;
	_list = (FCHashItem<T> **) RCESAlloc( _capacity * sizeof( FCHashItem<T> * ) );
	if( !_list )
		throw FCException(0, NULL, "FCHashTable::FCHashTable", 0, FC_MEM_ERR, "Couldn't allocate list array", __FILE__, __LINE__);
	for( int i = 0; i < _capacity; i++ )
		_list[i] = NULL;

	/* Create mutex for synchronizing all the hash operations in multi-threads */
	_hHashMutex = fcMutexCreate();

	_deleteItem = deleteItem;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Destructor: FCHashTable
*
\******************************************************************************/
template <class T> FCHashTable<T>::~FCHashTable()
{
	Clean();
	fcMutexGet(_hHashMutex);
	RCESFree( _list );
	fcMutexRel( _hHashMutex );
	fcMutexFree( _hHashMutex );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Add
*               Add a new item into the sorted list. If key already exists, ignore it.
*
*   Parameters: key [IN]
*               Key to be added
*
*               value [IN]
*               Value object to be added
*
\******************************************************************************/
template <class T> void FCHashTable<T>::Add( const char *key, T *value )
{
	int location = _count;
	bool moreToSearch = (location > 0);

	fcMutexGet(_hHashMutex);

	/* Check if the current list is big enough or if it must be expanded */
	try
	{
		_checkCapacity();
	}
	catch( FCException &e )
	{
		fcMutexRel( _hHashMutex );
		throw FCException(e);
	}

	/* Create a new hash item with the given information */
	FCHashItem<T> *newItem = new FCHashItem<T>( key, value, _deleteItem );

	/* Find the position by looking from the end to the beggining */
	while( moreToSearch ) 
	{
		switch( newItem->ComparedTo( _list[ location-1 ] ) ) 
		{
			case LESS    : 
				location--;
				moreToSearch = ( location > 0 );
				break;
			case GREATER : 
				moreToSearch = false;
				break;
			case EQUAL :
				/* If key alredy exists, ignore it */
				fcMutexRel( _hHashMutex );
				return;
		}
	}

	/* Move the greater items to one position a head */
	for( int index = _count; index > location; index-- )
		_list[index] = _list[index - 1];

	/* Set new item into the position */
	_list[location] = newItem;
	_count++;

	fcMutexRel( _hHashMutex );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Remove
*               Remove the item by the key
*
*   Parameters: key [IN]
*               Key to be deleted
*
\******************************************************************************/
template <class T> void FCHashTable<T>::Remove( const char *key )
{
	fcMutexGet(_hHashMutex);

	int pos = _getPos( key );
	if( pos < 0 )
	{
		fcMutexRel( _hHashMutex );
		throw FCException(0, NULL, "FCHashTable::Remove", 2, FC_NOTFOUND, "Key not found", __FILE__, __LINE__ );
	}

	/* Free memory allocated for the item being removed */
	delete _list[pos];

	/* Move the greater items to the previous position */
	for( int index = pos; index < _count; index++ )
		_list[index] = _list[index + 1];
	_count--;

	if( _currentPos >= _count )
		_currentPos = _count-1;
	if(_currentPos < 0)
		_currentPos = 0;

	fcMutexRel( _hHashMutex );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Clean
*               Remove all the items from the list
*
\******************************************************************************/
template <class T> void FCHashTable<T>::Clean()
{
	/* Free the list of hash item objects */
	fcMutexGet(_hHashMutex);
	for (int i = 0; i < _count; i++)
	{
		if( _list[i] )
		{
			delete _list[i];
			_list[i] = NULL;
		}
	}
	_currentPos = _capacity = _count = 0;
	fcMutexRel( _hHashMutex );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Get
*               Retrieve the hashed value for the given key
*
*   Parameters: key [IN]
*               Key to be retrieved
*
*   Returns:    Hashed value for the given key, or NULL if it is not found
*
\******************************************************************************/
template <class T> T *FCHashTable<T>::Get( const char *key )
{
	fcMutexGet(_hHashMutex);

	int pos = _getPos( key );
	fcMutexRel( _hHashMutex );

	if( pos >= 0 )
		return (T *)_list[pos]->GetValue();
	else
		return NULL;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     GetByPos
*               Retrieve the hashed value by given position
*
*   Parameters: pos [IN]
*               Position to be retrieved
*
*   Returns:    Hashed value for the given position, or NULL if it is not found
*
\******************************************************************************/
template <class T> T *FCHashTable<T>::GetByPos(int pos)
{
	if( pos >= 0 )
		return (T *)_list[pos]->GetValue();
	else
		return NULL;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     First
*               Retrieve the first item
*
*   Parameters: keepLocked [IN]
*               Flag indicating that the hash table should be unlocked until a 
*               ReleaseLock is called. This is for avoiding interpherence in 
*               multiple threads environment.
*
*   Returns:    First hashed item
*
\******************************************************************************/
template <class T> T *FCHashTable<T>::First(bool keepLocked)
{
	void *retval;

	fcMutexGet(_hHashMutex);
	_isLocked = keepLocked;

	if( _count == 0 )
	{
		if(!keepLocked)
			fcMutexRel( _hHashMutex );
		return NULL;
	}

	_currentPos = 0;

	retval = _list[_currentPos]->GetValue();

	if(!keepLocked)
		fcMutexRel( _hHashMutex );

	return (T *)retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Next
*               Retrieve the next item
*
*   Returns:    Next hashed item
*
\******************************************************************************/
template <class T> T *FCHashTable<T>::Next()
{
	void *retval;

	fcMutexGet(_hHashMutex);

	if( _currentPos >= (_count-1) )
	{
		fcMutexRel( _hHashMutex );
		return NULL;
	}

	retval = _list[++_currentPos]->GetValue();

	fcMutexRel( _hHashMutex );

	return (T *)retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Get
*               Retrieve the current hashed item
*
*   Returns:    Current hashed item
*
\******************************************************************************/
template <class T> T *FCHashTable<T>::Get()
{
	void *retval;

	fcMutexGet(_hHashMutex);

	if( _currentPos >= _count )
	{
		fcMutexRel( _hHashMutex );
		return NULL;
	}

	retval = _list[_currentPos]->GetValue();

	fcMutexRel( _hHashMutex );

	return (T *)retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     FirstK
*               Retrieve the first key
*
*   Parameters: keepLocked [IN]
*               Flag indicating that the hash table should be unlocked until a 
*               ReleaseLock is called. This is for avoiding interpherence in 
*               multiple threads environment.
*
*   Returns:    First key
*
\******************************************************************************/
template <class T> const char *FCHashTable<T>::FirstK(bool keepLocked)
{
	const char *retval;

	fcMutexGet(_hHashMutex);
	_isLocked = keepLocked;

	if( _count == 0 )
	{
		if(!keepLocked)
			fcMutexRel( _hHashMutex );
		return NULL;
	}

	_currentPos = 0;

	retval = _list[_currentPos]->GetKey();

	if(!keepLocked)
		fcMutexRel( _hHashMutex );

	return retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     NextK
*               Retrieve the next key
*
*   Returns:    Next hashed key
*
\******************************************************************************/
template <class T> const char *FCHashTable<T>::NextK()
{
	const char *retval;

	fcMutexGet(_hHashMutex);

	if( _currentPos >= (_count-1) )
	{
		fcMutexRel( _hHashMutex );
		return NULL;
	}

	retval = _list[++_currentPos]->GetKey();

	fcMutexRel( _hHashMutex );

	return retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     GetK
*               Retrieve the current key value
*
*   Returns:    Current hashed key
*
\******************************************************************************/
template <class T> const char *FCHashTable<T>::GetK()
{
	const char *retval;

	fcMutexGet(_hHashMutex);

	if( _currentPos >= _count )
	{
		fcMutexRel( _hHashMutex );
		return NULL;
	}

	retval = _list[_currentPos]->GetKey();

	fcMutexRel( _hHashMutex );

	return retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     KeyExists
*               Check if the given key exists in the list
*
*   Parameters: key [IN]
*               Key to be added
*
*   Returns:    true if the key exists, otherwise returns false
*
\******************************************************************************/
template <class T> bool FCHashTable<T>::KeyExists( const char *key )
{
	bool retval;

	fcMutexGet(_hHashMutex);

	retval = _getPos( key ) >= 0;

	fcMutexRel( _hHashMutex );

	return retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     GetCount
*               Retrieve the number of items in the Hash Table
*
*   Returns:    Item count
*
\******************************************************************************/
template <class T> int FCHashTable<T>::GetCount()
{
	int retval = 0;

	fcMutexGet(_hHashMutex);

	retval = _count;

	fcMutexRel( _hHashMutex );

	return retval;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     _checkCapacity
*               Retrieve the next item
*
\******************************************************************************/
template <class T> void FCHashTable<T>::_checkCapacity()
{
	/* Check if the current list is big enough for the new object */
	if( _capacity <= _count )
	{
		_capacity += LIST_BLOCK_SIZE;
		FCHashItem<T> **_newList = (FCHashItem<T> **) RCESAlloc( _capacity * sizeof( FCHashItem<T> * ) );
		if( !_newList )
			throw FCException(0, NULL, "FCHashTable::_checkCapacity", 0, FC_MEM_ERR, "Not able to allocate hash list", __FILE__, __LINE__ );

		for( int i = 0; i < _count; i++ )
			_newList[i] = _list[i];
		RCESFree( _list );
		_list = _newList;
	}
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     _getPos
*               Retrieve the position for the given key
*
*   Parameters: key [IN]
*               Key to be added
*
*   Returns:    Position for the given key or -1 if it's not found
*
\******************************************************************************/
template <class T> int FCHashTable<T>::_getPos( const char *key )
{
	int midPoint = -1;
	int first = 0;
	int last = _count - 1;
	bool moreToSearch = first <= last;
	bool found = false;
	FCHashItem<T> *item = new FCHashItem<T>( key, NULL, _deleteItem );

	/* Execute a binary search for by the key */
	while( moreToSearch && !found ) 
	{
		midPoint = ( first + last) / 2;
		switch( item->ComparedTo( _list[midPoint] ) ) 
		{
			case LESS    : 
				last = midPoint - 1;
				moreToSearch = first <= last;
				break;
			case GREATER : 
				first = midPoint + 1;
				moreToSearch = first <= last;
				break;
			case EQUAL   : 
				found = true;
				break;
		}
	}

	delete item;

	if( found )
		return midPoint;
	else
		return -1;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     ReleaseLock
*               Release lock acquired for a First() or FirstK() with keep lock
*
\******************************************************************************/
template <class T> void FCHashTable<T>::ReleaseLock()
{
	fcMutexRel( _hHashMutex );
	_isLocked = 0;
}
/*~****************************************************************************/