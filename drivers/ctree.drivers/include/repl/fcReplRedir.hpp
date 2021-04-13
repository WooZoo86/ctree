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

#ifndef _FCREPLREDIR_HPP_
#define _FCREPLREDIR_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesreplredir.hpp"

/* Forward class declaration */
class FCREPLReplRedir;
typedef FCREPLReplRedir *pFCREPLReplRedir, **ppFCREPLReplRedir;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Replication redirection
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Function:   fcReplGetReplRedirsByReplPlan
*               Retrieve all the replication redirections for the given 
*               Replication Plan
*
*   Parameters: replConn [IN]
*               Replication connection handle
*
*               replPlanID [IN]
*               Replication plan identification
*
*               replRedirList [OUT]
*               Replication redirection entity list
*
*               replRedirCount [OUT]
*               Number of Replication redirection entities in the list
*
*   Return:     Error code
*
\******************************************************************************/
FCREPL_API int fcReplGetReplRedirsByReplPlan(pFCREPLConn replConn, int replPlanID, ppFCREPLReplRedir *replRedirList, int *replRedirCount);

/*^****************************************************************************\
*
*   Class:      FCREPLReplRedir
*               Represents a group a replication redirection object.
*               It defines a rules of path transformation between the source
*               and the target.
*
\******************************************************************************/
class FCREPL_API FCREPLReplRedir : public RCESReplRedir
{
public:
	FCREPLReplRedir();

/*
** Getters
*/

	// Direction.
	FCREPLReplicationDirection GetDirection() { return (FCREPLReplicationDirection)((pRCESReplRedir)this)->GetDirection(); };

/*
	Inherited getters

	// Subscription identification.
	int GetSubsID();

	// Source Path
	const char *GetSource();

	// Target Path
	const char *GetTarget();

	// Retrieve Subscription information in Json.
	pRCESJson GetJson(bool details);
*/


/*
** Setters
*/

	// Direction.
	void SetDirection(FCREPLReplicationDirection direction) { ((pRCESReplRedir)this)->SetDirection((RCESReplicationDirection)direction); };

	// Source path.
	void SetSource(const char *sourcePath) { ((pRCESReplRedir)this)->SetSource(sourcePath); };

	// Target path.
	void SetTarget(const char *targetPath) { ((pRCESReplRedir)this)->SetTarget(targetPath); };

/*
	Inherited setters

	// Subscription identification.
	void SetSubsID(int subsID);

*/
};

#endif /* _FCREPLREDIR_HPP_ */