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

#include "fccachestr.hpp"
#include "fcexception.hpp"

/*^****************************************************************************\
*
*   Constructor: FCCacheStr
*
*   Parameters:  cacheSize
*                Cache size
*
\******************************************************************************/
template <class T> FCCacheStr<T>::FCCacheStr( int cacheSize )
{
	/* Allocate the hash table */
	_list = new FCHashTable<T>( cacheSize );
	if( !_list )
		throw FCException(0, NULL, "FCCacheStr::FCCacheStr", 0, FC_MEM_ERR, "Couldn't allocate hash table", __FILE__, __LINE__ );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Destructor: FCCacheStr::FCCacheStr
*
\******************************************************************************/
template <class T> FCCacheStr<T>::~FCCacheStr()
{
	delete _list;
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Get
*               Retrieve a object from the cache.
*
*   Parameters: key [IN]
*               Key to be searched in the cache
*
*   Returns:    Object from the cache or NULL if there isn't any available
*
\******************************************************************************/
template <class T> T *FCCacheStr<T>::Get( const char *key )
{
	return _list->Get( key );
}
/*~****************************************************************************/

/*^****************************************************************************\
*
*   Method:     Add
*               Retrieve a object from the cache.
*
*   Parameters: key [IN]
*               Key to be added in the cache
*
*               value [IN]
*               Value to be added in the cache
*
*   Returns:    Object from the cache or NULL if there isn't any available
*
\******************************************************************************/
template <class T> void FCCacheStr<T>::Add( const char *key, T *value)
{
	_list->Add( key, value );
}
/*~****************************************************************************/