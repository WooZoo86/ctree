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

#ifndef _FCRCESMASTERCONNPOOLED_HPP_
#define _FCRCESMASTERCONNPOOLED_HPP_

#include "fc_rces.h"
#include "fcpooledobj.hpp"
#include "fcrcesmasterprov.hpp"

/*^****************************************************************************\
*
*   RCESMasterConnPooled
*   Master connection pooled class
*
\******************************************************************************/
class RCESMasterConnPooled : public FCPooledObj, public RCESMasterProvider
{
	public:
		/* Constructors & destructor */
		RCESMasterConnPooled( pFCConfig config );
		virtual ~RCESMasterConnPooled();

		/* Public Methods */
		void Init();
		void Term();
		void Attach();
		void Detach();

	private:
		/* Private properties */

		/* Private methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESMasterConnPooled *pRCESMasterConnPooled, **ppRCESMasterConnPooled;

#endif /* _FCRCESMASTERCONNPOOLED_HPP_ */