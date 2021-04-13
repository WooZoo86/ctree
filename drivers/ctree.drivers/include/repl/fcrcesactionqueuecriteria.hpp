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

#ifndef _FCRCESACTIONQUEUECRITERIA_HPP_
#define _FCRCESACTIONQUEUECRITERIA_HPP_

#include "fc_rces.h"
#include "fcrcesqueueprov.hpp"

/* Class type definitions */
class RCESActionQueueCriteriaItem;
typedef RCESActionQueueCriteriaItem *pRCESActionQueueCriteriaItem, **ppRCESActionQueueCriteriaItem;

/*^****************************************************************************\
*
*   RCESActionQueueCriteriaItem
*   Recon-e-Sense Action Queue Criteria Item class
*
*   Manages the consumer element criteria that is part of the queue criteria
*
\******************************************************************************/
class RCESActionQueueCriteriaItem
{
	public:
		/* Constructors & destructor */
		RCESActionQueueCriteriaItem( RCESConsumerType consumerType, int osID, int agentID, int replPlanID );
		RCESActionQueueCriteriaItem(pRCESActionQueueCriteriaItem queueCriteriaItem);
		virtual ~RCESActionQueueCriteriaItem();

		/* Public methods */
		RCESConsumerType GetConsumerType() { return _consumerType; };
		int GetOSID() { return _osID; };
		int GetAgentID() { return _agentID; };
		int GetReplPlanID() { return _replPlanID; };

	private:
		/* Private properties */
		RCESConsumerType _consumerType;
		int _osID;
		int _agentID;
		int _replPlanID;
};
/*~****************************************************************************/

/*^****************************************************************************\
*
*   RCESActionQueueCriteria
*   Recon-e-Sense Action Queue Criteria class
*
*   Manages the action queue criteria
*
\******************************************************************************/
class RCESActionQueueCriteria
{
	public:
		/* Constructors & destructor */
		RCESActionQueueCriteria( pRCESQueueProvider queueProv, int osID, int agentID );
		RCESActionQueueCriteria(pRCESActionQueueCriteria queueCriteria);
		virtual ~RCESActionQueueCriteria();

		/* Public methods */
		void Clean();
		void AddItem( RCESConsumerType consumerType, int osID, int agentID, int replPlanID );
		void RemoveItem( RCESConsumerType consumerType, int osID, int agentID, int replPlanID );
		void Update();
		bool IsDirty() { return _isDirty; };

		int GetOSID() { return _osID; };
		int GetAgentID() { return _agentID; };
		FCHashTable<RCESActionQueueCriteriaItem> *GetList() { return _criteriaItemList; };

		void SetOSID(int osID) { _osID = osID; };
		void SetAgentID(int agentID) { _agentID = agentID; };

	private:
		/* Private properties */
		int _osID;
		int _agentID;
		char _key[RCES_MAX_KEY+1];
		bool _isDirty;
		pRCESQueueProvider _queueProv;
		FCHashTable<RCESActionQueueCriteriaItem> *_criteriaItemList;
};
/*~****************************************************************************/

#endif /* _FCRCESACTIONQUEUECRITERIA_HPP_ */