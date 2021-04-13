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

#ifndef _FCCACHE_HPP_
#define _FCCACHE_HPP_

#include "fchashinttable.hpp"

/*^****************************************************************************\
*
*   FCCache
*   Generic object cache class with integer key
*
\******************************************************************************/
template <class T> class FCCache
{
	public:
		/* Constructors & destructor */
		FCCache( int cacheSize );
		virtual ~FCCache();

		/* Public Methods */
		T *Get( int key );
		void Add( int key, T *value );
		int Count() { return _list->Count(); };

	private:
		/* Private properties */
		FCHashIntTable<T> *_list;
};
/*~****************************************************************************/

#include "fccache.ipp"

#endif /* _FCCACHE_HPP_ */