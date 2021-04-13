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

#ifndef _FCRCESIP_HPP_
#define _FCRCESIP_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
	#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESIp;
class RCESMasterProvider;
typedef RCESIp *pRCESIp, **ppRCESIp;
typedef RCESMasterProvider *pRCESMasterProvider, **ppRCESMasterProvider;

#define RCES_IP_ID "id"
#define RCES_IP_ADDRESS "ip"
#define RCES_IP_TYPE "type"

/*^****************************************************************************\
*
*   RCESId
*   Recon-e-Sense IP class
*
\******************************************************************************/
class RCESIp
{
	public:
		/* Constructors & destructor */
		RCESIp();
		RCESIp( pRCESIp ip );
		RCESIp( pRCESJson ip, int osID );
		virtual ~RCESIp();

		/* Public services */
		static int ctGetIPs( pRCESMasterProvider masterProv, int osID, int ipListSize, int ipStart, ppRCESIp *ipList, int *ipCount, int *totalIPs );
		static int ctPersistIP( pRCESMasterProvider masterProv, pRCESIp ip );
		static int ctRemoveIP( pRCESMasterProvider masterProv, int ipID );

		/* Public methods */
		int GetID() { return _id; };
		const char *GetAddress() { return _address; };
		const char *GetType() { return _type; };
		int GetOSID() { return _osID; };

		void SetID( int id ) { _id = id; };
		void SetAddress( const char *address );
		void SetType( const char *type );
		void SetOSID( int osID ) { _osID = osID; };

		pRCESJson GetJson();

	private:
		/* Private properties */
		int _id;
		char *_address;
		char *_type;
		int _osID;
};
/*~****************************************************************************/

#endif /* _FCRCESIP_HPP_ */