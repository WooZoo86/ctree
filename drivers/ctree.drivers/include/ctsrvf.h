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

#ifndef ctSRVFH
#define ctSRVFH

#ifdef ctLOCLIB

#ifndef ctFRCSNG
#define cttseg		loccttseg
#define ctuseg		locctuseg
#define ctgetseginfo	srv_ctgetseginfo
#endif

#define putdodanx	srv_putdodanx
#define putdodasx	srv_putdodasx
#define dodaflen	srv_dodaflen
#define cptifilx	srv_cptifilx
#define ctadjadr	srv_ctadjadr
#define ctadjfld	srv_ctadjfld
#define makifil		srv_makifil
#define makifilx	srv_makifilx
#define cthdrcfld	srv_cthdrcfld
#define ctlfsegget	srv_ctlfsegget
#define ctlfsegput	srv_ctlfsegput
#define ctsysint	srv_ctsysint
#define ctsysdint	srv_ctsysdint
#if !defined(ctMTFPG) && !defined(ctFRCSNG_FPUTFGET)
#define ierr		srv_ierr
#define uerr		srv_uerr
#endif
#define vtclose		srv_vtclose
#define ctasskey	srv_ctasskey 
#define ictasskey	srv_ictasskey 
#define ufill		srv_ufill
#define ctwalkfld	srv_ctwalkfld
#define ctMBprefix	srv_ctMBprefix
/* ctcndx.c */
#define ctfcidxstk	srv_ctfcidxstk
#define ctfreecidx	srv_ctfreecidx
#define ctcpydatflt	srv_ctcpydatflt
#define ctinitcidx	srv_ctinitcidx
#define ctgetnames	srv_ctgetnames
#define ctigetcidx	srv_ctigetcidx
#define ctevalcidx	srv_ctevalcidx
#define ictevalcidx	srv_ictevalcidx
/* ctcrun.c */
#define cndxrun		srv_cndxrun
#define cndxfree	srv_cndxfree
#define cndxparse	srv_cndxparse
#define testparse	srv_testparse
#define cndxeval	srv_cndxeval
#define clbkeval	srv_clbkeval
#define ctclbkinit	srv_ctclbkinit
#define clbkrun		srv_clbkrun
/* ctdbcrun.c */
#define cndxSetCondIdxFlag srv_cndxSetCondIdxFlag
#define ctdbptPutUTF16	srv_ctdbptPutUTF16
#define ptPutUTF16	srv_ptPutUTF16
/* ctgram.c */
#define ptFreeMem	srv_ptFreeMem
#define ptCreate	srv_ptCreate
#define ptDestroy	srv_ptDestroy
#define ptCopy		srv_ptCopy
#define ptPutSigned	srv_ptPutSigned
#define ptPutUnsign	srv_ptPutUnsign
#define ptPutReal	srv_ptPutReal
#define ptPutText	srv_ptPutText
#define ptPutField	srv_ptPutField
#define ptPutNode	srv_ptPutNode
#define ptGetNodeType	srv_ptGetNodeType
#define ptGetExprType	srv_ptGetExprType
#define ptGetSigned	srv_ptGetSigned
#define ptGetUnsign	srv_ptGetUnsign
#define ptGetReal	srv_ptGetReal
#define ptGetText	srv_ptGetText
#define ptGetField	srv_ptGetField
#define ptGetLeft	srv_ptGetLeft
#define ptGetRight	srv_ptGetRight
#define ptPrint		srv_ptPrint
#define TriplexCall	srv_TriplexCall
#define DuplexCall	srv_DuplexCall
#define SimplexCall	srv_SimplexCall
#define FieldName	srv_FieldName
#define CastToSigned	srv_CastToSigned
#define CastToUnsign	srv_CastToUnsign
#define CastToReal	srv_CastToReal
#define DuplexType	srv_DuplexType
#define DuplexMath	srv_DuplexMath
#define DuplexRelational	srv_DuplexRelational
#define DuplexBinary	srv_DuplexBinary
#define DuplexLogical	srv_DuplexLogical
#define ctcxparse	srv_ctcxparse
/* ctismu.c */
#define iuTFRMKEY	srv_iuTFRMKEY
/* ctscan.c */
#define ctcx_mmove	srv_ctcx_mmove
#define yylexcreate	srv_yylexcreate
#define yylexdestroy	srv_yylexdestroy
#define LexScan		srv_LexScan
#define TextDup		srv_TextDup
#define HexDigit	srv_HexDigit
#define atox		srv_atox
#define Text2Escape	srv_Text2Escape
#define Quote2Text	srv_Quote2Text
/* ctdbcrun.c */
#define ptPutInteger	srv_ptPutInteger
#define ptPutRecinfo	srv_ptPutRecinfo
#define ptGetInteger	srv_ptGetInteger
#define ptFieldName	srv_ptFieldName
#define ptDuplexNumeric	srv_ptDuplexNumeric
#define ptSymbolLookup	srv_ptSymbolLookup
#define ptArgCount	srv_ptArgCount
#define ptAddToExprList	srv_ptAddToExprList
#define ptPutDate	srv_ptPutDate
#define ptPutTime	srv_ptPutTime
#define ptPutTimeMsec srv_ptPutTimeMsec
#define ptPutStamp	srv_ptPutStamp
#define ptPutNumber	srv_ptPutNumber
#define	ptGetDate	srv_ptGetDate
#define ptGetTime	srv_ptGetTime
#define ptGetTimeMsec	srv_ptGetTimeMsec
#define ptGetStamp	srv_ptGetStamp
#define ptGetNumber	srv_ptGetNumber
#define ptGetLength	srv_ptGetLength
#define runPopString	srv_runPopString
#define runPopInteger	srv_runPopInteger
#define runPopNumber	srv_runPopNumber
#define runPopDate	srv_runPopDate
#define runPopTime	srv_runPopTime
#define runPopTimeMsec	srv_runPopTimeMsec
#define runPopStamp	srv_runPopStamp
#define convCTType	srv_convCTType
#define udfInit		srv_udfInit
#define udfTerm		srv_udfTerm
#define udfFind		srv_udfFind
#define udfFind		srv_udfFind
#define udfAdd		srv_udfAdd
#define ptSetUDFNode	srv_ptSetUDFNode
#define ptGetUDFNode	srv_ptGetUDFNode
#define ptGetDataSize	srv_ptGetDataSize
#define ctfillseg	srv_ctfillseg
#define ptPutSet	srv_ptPutSet
#define ptCopyIntoSet	srv_ptCopyIntoSet
#define ptPutNULL	srv_ptPutNULL
#define BinComp		srv_BinComp

#define ctdbptAddToExprList	srv_ctdbptAddToExprList 
#define ctdbptCopyIntoSet	srv_ctdbptCopyIntoSet
#define ctdbptDestroy		srv_ctdbptDestroy
#define ctdbptFreeMem		srv_ctdbptFreeMem
#define ctdbptGetExprType	srv_ctdbptGetExprType
#define ctdbptGetInteger	srv_ctdbptGetInteger
#define ctdbptPutDate		srv_ctdbptPutDate
#define ctdbptPutField		srv_ctdbptPutField
#define ctdbptPutInteger	srv_ctdbptPutInteger
#define ctdbptPutNode		srv_ctdbptPutNode
#define ctdbptPutNumber		srv_ctdbptPutNumber
#define ctdbptPutRecinfo	srv_ctdbptPutRecinfo
#define ctdbptPutSet		srv_ctdbptPutSet
#define ctdbptPutStamp		srv_ctdbptPutStamp
#define ctdbptPutText		srv_ctdbptPutText
#define ctdbptPutTime		srv_ctdbptPutTime
#define ctdbptPutTimeMsec	srv_ctdbptPutTimeMsec
#define ctdbptPutNULL		srv_ctdbptPutNULL

#define ctfldadr		srv_ctfldadr
#define GETKSEGDEFwrap		srv_GETKSEGDEFwrap

#endif /* ctLOCLIB */

#endif /* ctSRVFH */
