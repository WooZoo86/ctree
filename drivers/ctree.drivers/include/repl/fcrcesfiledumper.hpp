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

#ifndef _FCRCESFILEDUMPER_HPP_
#define _FCRCESFILEDUMPER_HPP_

#include "fcrcesreplplanmngr.hpp"

/*^****************************************************************************\
*
*   RCESFileDump
*   Recon-e-Sense file dump class
*
*   Implement the file dynamic dump instigated by the target agent from the 
*   source server. It doesn't require that the source server is quiesced nor
*   file blocked during the process. It restore the file in a temporary
*   directory and fileblock the file to be overwritten before moving it over.
*
\******************************************************************************/
class RCESFileDumper
{
	public:
		/* Constructors & destructor */
		RCESFileDumper(pRCESMasterProvider masterProv, pRCESReplPlanMngr replPlanMngr, bool reverse, pReplicationDumpData dumpData);
		virtual ~RCESFileDumper();

		/* Public services */
		static void ctDump( pRCESMasterProvider masterProv, pRCESReplPlanMngr replPlanMngr, bool reverse, int actionID, pRCESReplFileList replFileList,
		                    ppRCESSubscription subsList, int subsCount, bool forceReplace, pReplicationDumpData dumpData, const char *replPlanDeps, bool isSourceCaseSensitive, char *logPos );
		static void ctCancel(pRCESConfig config, int actionID);

		/* Public Methods */
		void Dump( int actionID, pRCESReplFileList replFileList, ppRCESSubscription subsList, int subsCount, bool forceReplace, const char *replPlanDeps, bool isSourceCaseSensitive, char *logPos );
		bool IsReverse() { return _reverse; };

	protected:
		/* Protected properties */
		bool _reverse;
		pRCESReplPlanMngr _replPlanMngr;
		pRCESMasterProvider _masterProv;
		pReplicationDumpData _dumpData;

		/* Protected methods */
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESFileDumper *pRCESFileDumper, **ppRCESFileDumper;

#endif /* _FCRCESFILEDUMPER_HPP_ */