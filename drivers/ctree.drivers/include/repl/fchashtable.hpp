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

#ifndef _FCHASHTABLE_HPP_
#define _FCHASHTABLE_HPP_

#include "fchashitem.hpp"

/*^****************************************************************************\
*
*   FCHashTable
*   Sorted hash list class
*
\******************************************************************************/
template <class T> class FCHashTable
{
	public:
		/* Constructors & destructor */
		FCHashTable( int size = 100, bool deleteItem = true );
		virtual ~FCHashTable();

		/* Public Methods */
		void Add( const char *key, T *value );
		void Remove( const char *key );
		void Clean();
		T *Get( const char *key );
		T *GetByPos(int pos);
		T *First(bool keepLocked);
		T *Next();
		T *Get();
		const char *FirstK(bool keepLocked);
		const char *NextK();
		const char *GetK();
		bool KeyExists( const char *key );
		int GetCount();
		void ReleaseLock();

	private:
		/* Private properties */
		int _capacity;
		int _count;
		FCHashItem<T> **_list;
		int _currentPos;
		void *_hHashMutex;
		bool _deleteItem;
		bool _isLocked;

		/* Private methods */
		void _checkCapacity();
		int _getPos( const char *key );
};
/*~****************************************************************************/

#include "fchashtable.ipp"

#endif /* _FCHASHTABLE_HPP_ */