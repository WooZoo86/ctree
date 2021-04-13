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

#ifndef _FCCONFIG_HPP_
#define _FCCONFIG_HPP_

#include "fcparam.hpp"

/* Class type definitions */
class FCConfig;
typedef FCConfig *pFCConfig, **ppFCConfig;

/*^****************************************************************************\
 *
 *   FCConfig
 *   Pooled object configuration interface
 *
\******************************************************************************/
class FCConfig
{
	public:
		/* Constructors & destructor */
		FCConfig();
		FCConfig( const char *paramsStr );
		virtual ~FCConfig();

		/* Public methods */
		virtual const char *GetParam( const char *key ) { return _config->Get( key ); };
		virtual pFCParamHash GetParams() { return _config; };
		virtual void AddParam( const char *key, const char *value ) { _config->Add( key, value ); };
		virtual bool Matches( pFCConfig config ) = 0;
		const char *ToString() { return _config->ToString(); };
		void Use() { _lastUsedTime = fcGetSysTimer(); };
		bool isInactive();

	protected:
		/* Protected Properties */
		pFCParamHash _config;
		TIMER _lastUsedTime;
		int _inactiveTimeout; /* Inactive timeout in seconds */

		/* Protected Methods */
		void SetInactiveTimeout( int inactiveTimeOut ) { _inactiveTimeout = inactiveTimeOut; };
};
/*~****************************************************************************/

#endif /* _FCCONFIG_HPP_ */