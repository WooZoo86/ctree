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

#ifndef _FCREPLREPLICA_HPP_
#define _FCREPLREPLICA_HPP_

#include "fcReplCommon.hpp"
#include "fcReplConn.hpp"
#include "fcrcesreplica.hpp"

/* Forward class declaration */
class FCREPLReplica;
typedef FCREPLReplica *pFCREPLReplica, **ppFCREPLReplica;

/*^****************************************************************************\
*
*   Faircom Replication API C/C++ - Replica (Availability Group)
*
\******************************************************************************/

/*^****************************************************************************\
*
*   Class:      FCREPLReplica
*               Entity to represent replicas in an availability group 
*               environment
*
\******************************************************************************/
class FCREPL_API FCREPLReplica : public RCESReplica
{
public:
	FCREPLReplica();
	FCREPLReplica(pFCREPLJson replica);

/*
** Getters
*/

	// DBEngine
	pFCREPLDBEngine GetDBEngine() { return (pFCREPLDBEngine)((pRCESReplica)this)->GetDBEngine(); };

	// Publication
	pFCREPLPublication GetPublication() { return (pFCREPLPublication)((pRCESReplica)this)->GetPublication(); };

	// Replication Plan
	pFCREPLReplPlan GetReplPlan() { return (pFCREPLReplPlan)((pRCESReplica)this)->GetReplPlan(); };

/*
	Inherited getters

	// Availability Group identification
	int GetAvailGroupID();

	// DBEngine identification
	int GetDBEngineID();

	// Publication identification
	int GetPublicationID();
	
	// Replication Plan identification
	int GetReplPlanID();
	
	// Flag indicating if the replica is synchronous
	bool IsSync();

	// Flag indicating if the replica is primary or secondary
	bool IsPrimary();
*/


/*
** Setters
*/

	// DBEngine
	void SetDBEngine(pFCREPLDBEngine dbEngine) { ((pRCESReplica)this)->SetDBEngine((pRCESDBEngine)dbEngine); };

	// Publication
	void SetPublication(pFCREPLPublication publication) { ((pRCESReplica)this)->SetPublication((pRCESPublication)publication); };

	// Replication Plan
	void SetReplPlan(pFCREPLReplPlan replPlan) { ((pRCESReplica)this)->SetReplPlan((pRCESReplPlan)replPlan); };

/*
	Inherited setters

	// Replication Plan identification
	void SetAvailGroupID(int id);

	// DBEngine identification
	void SetDBEngineID(int dbEngineID);

	// Publication identification
	void SetPublicationID(int publicationID);

	// Replication Plan identification
	void SetReplPlanID(int replPlanID);

	// Flag indicating if the replica is synchronous
	void SetIsSync(bool isSync);

	// Flag indicating if the replica is primary or secondary
	void SetIsPrimary(bool isPrimary);
*/
};

#endif /* _FCREPLREPLICA_HPP_ */