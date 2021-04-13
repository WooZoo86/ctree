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

#ifndef _FCPARAM_HPP_
#define _FCPARAM_HPP_

#include "fcpool.hpp"

/* Class type definitions */
class FCParamHash;
typedef FCParamHash *pFCParamHash, **ppFCParamHash;

/*^****************************************************************************\
*
*   FCParamHash
*   Auxiliary configuration class
*
*   Manages the configurations of a pooled object
*
\******************************************************************************/
typedef struct 
{
	char *key;
	char *value;
} FCParam, *pFCParam, **ppFCParam;

class FCParamHash
{
	public:
		/* Constructors & destructor */
		FCParamHash();
		FCParamHash( const char *paramsStr );
		virtual ~FCParamHash();

		/* Public methods */
		void Add( const char *key, const char *value );
		const char *Get( const char *key );
		pFCParam GetParam( int index ) { return _paramList[ index ]; };
		int GetCount() { return _count; };
		const char *ToString();
		bool Matches( pFCParamHash params );

	/* Properties */
	private:
		ppFCParam _paramList;
		int _count;
		char _str[FC_MAX_BUF + 1];
		char _tempStr[FC_MAX_BUF + 1];
};
/*~****************************************************************************/

#endif /* _FCPARAM_HPP_ */