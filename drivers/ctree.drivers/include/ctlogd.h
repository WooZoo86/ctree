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

static pTEXT logdesc[] = {
			"ILLEGAL",
			"LHDRCOMP",
			"LADDKEY",
			"LADDSI",
			"LDELKEY",
			"LDELSI",
			"SH_INVLD",
			"BEGTRAN",
			"ENDTRAN",
			"ABRTRAN",
			"NEWLINK",
			"SH_VLINK",
			"NEWIMAGE",
			"OLDFILL",
			"OLDIMAGE",
			"DIFIMAGE",
			"RDYTRAN",
			"LHDRSHST",
			"LOGEXTFIL",
			"NODEXTFIL",
			"SH_QNODE",
			"LHDRWORD",
			"UNDTRAN",
			"BEG2FASE",
			"ACK2FASE",
			"SH_RSTFIL",
			"CHKPNT",
			"OPNTRAN",
			"CRETRAN",
			"DELTRAN",
			"CLSTRAN",
			"LLOGIN",
			"LLOGOFF",
			"UPDTRAN",
			"ENDLOG",
			"LPRMIDX",
			"RESTRAN",
			"SH_WRITE",
			"SH_REUSE",
			"SH_RSTRUS",
			"ABNTRAN",
			"LPABYTE",
			"INDXADD",
			"INDXDEL",
			"LTFLMAP",
			"USRTRANI",
			"DSTINDEX",
			"HDRVALUE",
			"PARTHST",
			"RSTPNT",
			"SYSTRANI",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"NotInUse",
			"DARWRDdir",
			"FRCTRAN",
			"SEGTRAN",
			"LLOGNODE",
			"CMPTRAN",
			"ENCTRAN",
			"RENTRAN",
			"RENTRANU",
			"SEGMRES",
			"CREDRAN",
			"DELDRAN",
			"CRENRAN",
			"DELNRAN",
			"INDXEND",
			"INDXERR",
			"INDXVUL",
			"SUCTRAN",
			"LCMPRECRES",
			"NotInUse",
			"NotInUse",
			"PRMIDXDEP",
			"SEGDCRE",
			"SEGDDEL",
			"SEGNCRE",
			"SEGNDEL",
			"SEGMOLD",
			"RSPACE",
			"ALNEXTFIL",
			"DROPIDX",
			"LPARTRES",
			"LHDRSNUM",
			"RENDRAN",
			"RENNRAN",
			"PreimageOnly",
			"PreimageOnly",
			"REPIMAGE",
			"LFNDKEY",
			"USRTRAN",
			"SH:NotInUse",
			"SH:NotInUse",
			"SH:NotInUse",
			"SH:NotInUse",
			"DARWRD",
			"DFRKEY",
			"PreimageOnly",
			"SYSTRAN",
			"PreimageOnly"
		};
#define MAXLOGVAL	(ctSIZE(logdesc) / ctSIZE(pTEXT))

#ifdef PROTOTYPE
static pTEXT getlogdesc(NINT typ)
#else
static pTEXT getlogdesc(typ)
NINT typ;
#endif
{
	typ &= FLSHMSK;
	if (typ < 1 || typ > MAXLOGVAL)
		typ = 0;
	return(logdesc[typ]);
}

/* end of ctlogd.h */
