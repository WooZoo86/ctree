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

#ifndef _FCLIST_HPP_
#define _FCLIST_HPP_

#include <stdio.h>

/*^****************************************************************************\
*
*   FCList
*   Generic object list class
*
\******************************************************************************/
template <class T> class FCList
{
	public:
		/* Constructors & destructor */
		FCList();
		virtual ~FCList();

		/* Public Methods */
		void Add( T *value );
		void Remove( T *value, bool deleteIt = true );
		void Remove( int index, bool deleteIt = true );
		void Clean( bool deleteIt = true );
		T *Get( int index );
		T *First(bool keepLocked);
		T *Next();
		T *Pull();
		int GetCount() { return _count; };
		int GetPos(T *value);
		void ReleaseLock();
		void AcquireLock();

	private:
		/* Private properties */
		int _capacity;
		int _count;
		T **_list;
		int _currentPos;
		void *_hListMutex;

		/* Private methods */
		void _checkCapacity();
};
/*~****************************************************************************/

#include "fclist.ipp"

#endif /* _FCLIST_HPP_ */