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
 *      Copyright (c) 1992 - 2020 FairCom Corporation.
 *	This is an unpublished work, and is subject to limited distribution and
 *	restricted disclosure only. ALL RIGHTS RESERVED.
 *	
 *	In addition:
 *	This Module also contains Proprietary Information of
 *	Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 *	and should be treated as Confidential.
 *	
 *	Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *	Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *	
 *
 *			RESTRICTED RIGHTS LEGEND
 *	Use, duplication, or disclosure by the Government is subject to
 *	restrictions set forth in subparagraph (c)(1)(ii) of the Rights in
 * 	Technical Data and Computer Software clause at DFARS 252.227-7013, and/or
 *      in similar or successor clauses in the FAR, DOD or NASA FAR Supplement.
 *      Unpublished rights reserved under the Copyright Laws of the United States.
 *	FairCom Corporation, 6300 West Sugar Creek Drive, Columbia, MO 65203.
 *
 *	c-treeACE(tm)	Version 11
 */

 //
 //	Copyright (C) Dharma Systems Inc.        1988-2011.
 //	Copyright (C) Dharma Systems (P) Ltd.    1988-2011.
 //
 //	This Module contains Proprietary Information of
 //	Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 //	and should be treated as Confidential.
 //

 //
 // $RCSfile: stub_seq.hxx,v $ $Revision: 1.1.1.1 $Date $
 // $State: Exp $
 //



 /* -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project number   : DC_20170106_4264
 * Date             : 2017-JAN-06
 * Title            : Support for SEQUENCES.
 * -------------------------------------------------------------------------
 */

#ifndef stub_sequences_included
#define stub_sequences_included
#include "tpesysdf.h"
#include "fldl.hxx"
#include "keydesc.hxx"
#include "rsstypes.hxx"
#include "seg.hxx"
#include "tid.hxx"
#include "tpl.hxx"
#include "seq.hxx"
#include "rss_hdl.hxx"
#include "rds_env.hxx"
#include "stub_env.hxx"
#include "stub_std.hxx"
#include "stub_tpl.hxx"
#include "sql_tree.hxx"


#include "ctdbsdk.h"
#include "ctdbport.h"

class stub_seq_hdl_t : seq_hdl_t
{
private:
		TEXT seqname[MAX_SEQ_NAME_LEN + 1];
		dh_boolean isOpen;
		LONG hdl;
		tagCTDB	*ctreedb;
		status_t Open(void);
public:

	stub_seq_hdl_t();

	virtual ~stub_seq_hdl_t();

	//
	// Constructor to be called from stub_rss_hdl_t::seq_hdl_ctor ()
	//
	stub_seq_hdl_t(
		stub_rss_hdl_t *rss_hdl,
		dh_identifier_t const &, // IN sequence owner
		dh_identifier_t const &, // IN sequence name
		status_t &       // OUT status
	);

	status_t nextval(
		dh_longlong_t & // OUT  value
	);

	status_t currval(
		dh_longlong_t &, // OUT  value
		dh_boolean
	);
};

#endif		/* stub_sequences_included  */

// end of stub_sequences.hxx

