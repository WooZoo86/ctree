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

#ifndef _FCQUEUE_HPP_
#define _FCQUEUE_HPP_

#include <stdio.h>

/*^****************************************************************************\
*
*   FCQueue
*   Basic FIFO queue implementation class
*
\******************************************************************************/
class FCQueue
{
    public:
        /* Constructors & destructor */
		FCQueue( int maxLen );
        virtual ~FCQueue();

        /* Public methods */
        int Push( void* element );
        void *Pull();
        bool IsEmpty() { return _avl == 0; };

    private:
        /* Private properties */
        int _in, _out, _avl, _max;
        void **_queue;
        void *_hQueueMutex;
};
/*~****************************************************************************/

/* Class type definitions */
typedef FCQueue *pFCQueue, **ppFCQueue;

#endif /* _FCQUEUE_HPP_ */