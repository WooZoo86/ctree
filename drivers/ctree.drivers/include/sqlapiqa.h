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
#include "ctatrd.h"
#include "cthelp.h"
typedef pVOID 		CTHANDLE;
typedef NINT		CTSESSION_TYPE;
typedef NINT		CTDBRET;
typedef NINT		CTDBTYPE;
typedef NINT		CTDBKEY;
typedef NINT		CTBOOL;
typedef NINT		CTSEG_MODE;
typedef NINT		CTCREATE_MODE;
typedef NINT		CTOPEN_MODE;
typedef NINT		(*pctThrdInit_t)(NINT, LONG, pctINIT);
typedef NINT		(*pctThrdTerm_t)(VOID);
typedef COUNT		(*pINTISAMX_t)(COUNT, COUNT, COUNT, COUNT, COUNT, pTEXT, pTEXT, pTEXT);
typedef COUNT		(*pSTPUSR_t)(VOID);
typedef COUNT		(*pOPNIFILX_t)(struct ifil ctMEM *, pTEXT, pTEXT, pTEXT);
typedef COUNT		(*pOPNRFILX_t)(COUNT, pTEXT, COUNT, pTEXT);
typedef COUNT		(*pctGetUserErrorCode_t)(VOID);
typedef COUNT		(*pctGetIsamErrorCode_t)(VOID);
typedef COUNT		(*pctGetIsamFileNbr_t)(VOID);
typedef COUNT		(*pctGetSystemErrorCode_t)(VOID);
typedef COUNT		(*pCLIFIL_t)(struct ifil ctMEM *);
typedef LONG		(*pGETFIL_t)(COUNT, COUNT);
typedef COUNT		(*pSETNODE_t)(pTEXT);
typedef COUNT		(*pCLRFIL_t)(COUNT);
typedef LONG		(*pTRANBEG_t)(COUNT);
typedef COUNT           (*pTRANRDY_t)(VOID);
typedef COUNT           (*pTRANEND_t)(COUNT);
typedef COUNT           (*pTRANABT_t)(VOID);
typedef COUNT           (*pTRANABTX_t)(COUNT);
typedef COUNT           (*pADDREC_t)(COUNT, pVOID);
typedef COUNT           (*pADDVREC_t)(COUNT, pVOID, VRLEN);
typedef COUNT           (*pTRANSAV_t) (VOID);
typedef COUNT           (*pTRANRST_t) (COUNT);
typedef LONG            (*pSPCLSAV_t) (VOID);
typedef COUNT           (*pFRSREC_t) (COUNT,pVOID);
typedef COUNT           (*pFRSVREC_t) (COUNT,pVOID,pVRLEN);
typedef COUNT           (*pLSTREC_t) (COUNT,pVOID);
typedef COUNT           (*pLSTVREC_t)(COUNT,pVOID,pVRLEN);
typedef COUNT           (*pNXTREC_t) (COUNT,pVOID);
typedef COUNT           (*pNXTVREC_t) (COUNT,pVOID,pVRLEN);
typedef COUNT           (*pPRVREC_t) (COUNT,pVOID);
typedef COUNT           (*pPRVVREC_t)(COUNT,pVOID,pVRLEN);
typedef COUNT           (*pRWTREC_t) (COUNT,pVOID);
typedef COUNT           (*pRWTVREC_t) (COUNT,pVOID,VRLEN);
typedef COUNT           (*pDELREC_t) (COUNT);
typedef COUNT           (*pDELVREC_t) (COUNT);
typedef COUNT           (*pEQLREC_t) (COUNT,pVOID,pVOID);
typedef COUNT           (*pGTEREC_t) (COUNT,pVOID,pVOID);
typedef COUNT           (*pGTREC_t) (COUNT,pVOID,pVOID);
typedef COUNT           (*pLTEREC_t)(COUNT,pVOID,pVOID);
typedef COUNT           (*pLTREC_t) (COUNT,pVOID,pVOID);
typedef COUNT           (*pEQLVREC_t)(COUNT,pVOID,pVOID,pVRLEN);
typedef COUNT           (*pGTEVREC_t) (COUNT,pVOID,pVOID,pVRLEN);
typedef COUNT           (*pGTVREC_t) (COUNT,pVOID,pVOID,pVRLEN);
typedef COUNT           (*pLTEVREC_t) (COUNT,pVOID,pVOID,pVRLEN);
typedef COUNT           (*pLTVREC_t) (COUNT,pVOID,pVOID,pVRLEN);
typedef LONG		(*pSETOPS_t) (LONG,VRLEN);
typedef COUNT		(*pCREIFILX8_t) (struct ifil ctMEM *,pTEXT, pTEXT, LONG, pTEXT ,pTEXT, pXCREblk);
typedef COUNT		(*pPUTDODA_t) (COUNT, pDATOBJ, UCOUNT);
typedef COUNT		(*pREDVREC_t) (COUNT, pVOID, VRLEN);
typedef COUNT           (*pSAVPCLR_t) (VOID);
typedef LONG            (*pCTUSERX_t) (pTEXT,pTEXT,VRLEN,pTEXT,pVRLEN);
typedef LONG            (*pctTransferFile_t) (pctXFRFIL pxfr);
typedef NINT            (*pctOWNER_t) (VOID);
typedef VOID            (*pctSetOWNER_t) (NINT sOWNR);
typedef NINT            (*pctThrdSleep_t) (LONG);
typedef COUNT		(*pREGCTREE_t) (pTEXT regid);
typedef COUNT		(*pUNRCTREE_t) (pTEXT regid);
typedef NINT		(*pctThrdAttach_t) (VOID);
typedef NINT		(*pctThrdDetach_t) (VOID);
typedef pVOID		(*pGETCTREE_t) (pTEXT regid);
typedef NINT		(*pctSETCLIENTID_t) (pVOID pclientid, NINT clientidlen);
typedef NINT            (*pctdbGetCtreeOWNER_t) (VOID);
typedef VOID            (*pctdbSetCtreeOWNER_t) (NINT sOWNR);
typedef COUNT           (*pOPNFILX_t) (COUNT filno,pTEXT filnam,COUNT filmod,pTEXT fileword);
typedef COUNT           (*pPUTIFILX8_t) (struct ifil ctMEM *ifilptr,pTEXT dataextn,pTEXT indxextn,pTEXT fileword,pXCREblk pxcreblk);
typedef COUNT           (*pAVLFILNUM_t) (COUNT numfils);
typedef COUNT           (*pCLSFIL_t) (COUNT filno,COUNT filmod);
typedef NINT            (*pSetXtdFileOpenMode_t) (LONG mode);
typedef COUNT           (*pRWTPREC_t) (COUNT,pVOID,VRLEN);
typedef COUNT		(*pSYSCFG_t) (VOID *);
typedef pTEXT		(*pWCHCTREE_t)(VOID);
typedef COUNT		(*pSWTCTREE_t)(pTEXT);
typedef COUNT		(*pctklusr_t)(NINT,pTEXT);
typedef NINT		(*pctThrdCreate_t)(pctFUNC,pVOID,pVOID,LONG);
typedef NINT		(*pctThrdMutexGet_t)(ctMUTEX * mutex);
typedef NINT		(*pctThrdMutexRel_t)(ctMUTEX * mutex);
typedef NINT		(*pctThrdBlockGet_t)(ctBLOCK *,LONG);
typedef NINT		(*pctThrdBlockWait_t)(ctBLOCK *,LONG);
typedef NINT		(*pctThrdBlockRel_t)(ctBLOCK *);
typedef NINT		(*pctThrdBlockCls_t)(ctBLOCK *);
typedef NINT		(*pctThrdMutexCls_t)(ctMUTEX *);
typedef NINT		(*pSA_LOGON_t)(pTEXT,pTEXT,pTEXT,pTEXT);
typedef NINT		(*pSA_LOGOF_t)(void);
typedef NINT		(*pSA_GROUP_t)(COUNT action,saGRPINFO * grpinfo);
typedef NINT		(*pctQUIET_t)(pTEXT filespec, LONG timeoutSEC, LONG action);
typedef CTHANDLE	(*pctdbAllocSession_t)(CTSESSION_TYPE sessionType);
typedef VOID		(*pctdbFreeSession_t)(CTHANDLE handle);
typedef CTHANDLE	(*pctdbAllocTable_t)(CTHANDLE handle);
typedef VOID		(*pctdbFreeTable_t)(CTHANDLE handle);
typedef CTDBRET		(*pctdbLogon_t)(CTHANDLE handle, pTEXT dbEngine, pTEXT userId, pTEXT password);
typedef CTHANDLE	(*pctdbAddField_t)(CTHANDLE handle, pTEXT fieldName, CTDBTYPE fieldType, VRLEN fieldLength);
typedef CTHANDLE	(*pctdbAddIndex_t)(CTHANDLE handle, pTEXT name, CTDBKEY keyType, CTBOOL allowDuplicates, CTBOOL nullFlag);
typedef CTHANDLE	(*pctdbAddSegment_t)(CTHANDLE handle, CTHANDLE fieldHandle, CTSEG_MODE segMode);
typedef CTDBRET		(*pctdbSetTablePath_t)(CTHANDLE handle, pTEXT path);
typedef CTDBRET		(*pctdbCreateTable_t)(CTHANDLE handle, pTEXT tableName, CTCREATE_MODE createMode);
typedef CTDBRET		(*pctdbOpenTable_t)(CTHANDLE handle, pTEXT tableName, CTOPEN_MODE openMode);
typedef CTDBRET		(*pctdbRemoveTable_t)(CTHANDLE handle);
typedef CTHANDLE	(*pctdbAllocRecord_t)(CTHANDLE handle);
typedef CTDBRET		(*pctdbWriteRecord_t)(CTHANDLE handle);
typedef CTDBRET		(*pctdbClearRecord_t)(CTHANDLE handle);
typedef CTDBRET		(*pctdbSetFieldAsSigned_t)(CTHANDLE handle, NINT fieldNumber, LONG Value);
typedef CTDBRET		(*pctdbRenameTable_t)(CTHANDLE handle, pTEXT oldName, pTEXT newName);
typedef CTDBRET		(*pctdbCloseTable_t)(CTHANDLE handle);
typedef CTHANDLE	(*pctdbAddSegmentEx_t)(CTHANDLE handle, NINT offset, NINT length, CTSEG_MODE segMode);
typedef VRLEN	(*pctdbGetFieldOffset_t)(CTHANDLE handle, NINT fieldNumber);
typedef CTDBRET	(*pctdbFirstRecord_t)(CTHANDLE handle);
typedef CTDBRET	(*pctdbSetTableOwner_t)(CTHANDLE handle, pTEXT owner);
typedef NINT	(*pSA_USERS_t)(COUNT action, saUSRINFO * userInfo);
typedef COUNT		(*pINTISAMX4_t)(COUNT, FILNO, COUNT, COUNT, COUNT, pTEXT, pTEXT, pTEXT);

/* <NEW_ENTRY>
typedef RTNTYP   (*pctNewAPIFunction_t) __((PARAMLIST));
*/

/*
** c-tree Plus API function identifiers,
** used as index into function pointer list.
*/

#define	CTCLI_ctThrdInit		0
#define	CTCLI_ctThrdTerm		1
#define	CTCLI_INTISAMX			2
#define	CTCLI_STPUSR			3
#define	CTCLI_OPNIFILX			4
#define	CTCLI_OPNRFILX			5
#define CTCLI_ctGetUserErrorCode	6
#define CTCLI_ctGetIsamErrorCode	7
#define CTCLI_ctGetIsamFileNbr		8
#define CTCLI_ctGetSystemErrorCode	9
#define CTCLI_CLIFIL			10
#define CTCLI_GETFIL			11
#define CTCLI_SETNODE			12
#define CTCLI_CLRFIL			13
#define CTCLI_TRANBEG			14
#define CTCLI_TRANRDY			15
#define CTCLI_TRANEND			16
#define CTCLI_TRANABT			17
#define CTCLI_TRANABTX			18
#define CTCLI_ADDREC			19
#define CTCLI_ADDVREC			20
#define CTCLI_TRANSAV			21
#define CTCLI_TRANRST			22
#define CTCLI_SPCLSAV			23
#define CTCLI_FRSREC 			24
#define CTCLI_FRSVREC			25
#define CTCLI_LSTREC 			26
#define CTCLI_LSTVREC			27
#define CTCLI_NXTREC 			28
#define CTCLI_NXTVREC			29
#define CTCLI_PRVREC 			30
#define CTCLI_PRVVREC			31
#define CTCLI_RWTREC 			32
#define CTCLI_RWTVREC			33
#define CTCLI_DELREC			34
#define CTCLI_DELVREC			35
#define CTCLI_EQLREC			36
#define CTCLI_GTEREC			37
#define CTCLI_GTREC			38
#define CTCLI_LTEREC			39
#define CTCLI_LTREC			40
#define CTCLI_EQLVREC			41
#define CTCLI_GTEVREC			42
#define CTCLI_GTVREC			43
#define CTCLI_LTEVREC			44
#define CTCLI_LTVREC			45
#define CTCLI_SETOPS			46
#define CTCLI_CREIFILX8			47
#define CTCLI_PUTDODA			48
#define CTCLI_ctThrdCreate		49
#define CTCLI_REDVREC			50
#define CTCLI_SAVPCLR			51
#define CTCLI_CTUSERX			52
#define CTCLI_ctTransferFile		53
#define CTCLI_ctOWNER			54
#define CTCLI_ctSetOWNER		55
#define CTCLI_ctThrdSleep		56
#define CTCLI_REGCTREE			57
#define CTCLI_UNRCTREE			58
#define CTCLI_ctThrdAttach		59
#define CTCLI_ctThrdDetach		60
#define CTCLI_GETCTREE			61
#define CTCLI_ctSETCLIENTID		62
#define CTCLI_ctdbGetCtreeOWNER 	63
#define CTCLI_ctdbSetCtreeOWNER 	64
#define CTCLI_OPNFILX		 	65
#define CTCLI_PUTIFILX8		 	66
#define CTCLI_AVLFILNUM		 	67
#define CTCLI_CLSFIL		 	68
#define CTCLI_SetXtdFileOpenMode	69
#define CTCLI_RWTPREC			70
#define CTCLI_SYSCFG			71
#define CTCLI_WCHCTREE			72
#define CTCLI_SWTCTREE			73
#define CTCLI_ctklusr			74
#define CTCLI_ctThrdMutexGet		75
#define CTCLI_ctThrdMutexRel		76
#define CTCLI_SA_LOGON			77
#define CTCLI_SA_LOGOF			78
#define CTCLI_SA_GROUP			79
#define CTCLI_ctQUIET			80
#define CTCLI_ctdbAllocSession	81
#define CTCLI_ctdbFreeSession	82
#define CTCLI_ctdbAllocTable	83
#define CTCLI_ctdbFreeTable		84
#define CTCLI_ctdbLogon			85
#define CTCLI_ctdbAddField		86
#define CTCLI_ctdbAddIndex		87
#define CTCLI_ctdbAddSegment	88
#define CTCLI_ctdbSetTablePath	89
#define CTCLI_ctdbCreateTable	90
#define CTCLI_ctdbOpenTable		91
#define CTCLI_ctdbRemoveTable	92
#define CTCLI_ctdbAllocRecord	93
#define CTCLI_ctdbWriteRecord	94
#define CTCLI_ctdbClearRecord	95
#define CTCLI_ctdbSetFieldAsSigned	96
#define CTCLI_ctdbRenameTable	97
#define CTCLI_ctdbCloseTable	98
#define CTCLI_ctdbAddSegmentEx	99
#define CTCLI_ctdbGetFieldOffset	100
#define CTCLI_ctdbFirstRecord	101
#define CTCLI_ctdbSetTableOwner	102
#define CTCLI_SA_USERS	103
#define CTCLI_INTISAMX4	        104
#define CTCLI_ctThrdBlockGet	105	
#define CTCLI_ctThrdBlockWait	106	
#define CTCLI_ctThrdBlockRel	107	
#define CTCLI_ctThrdBlockCls	108	
#define CTCLI_ctThrdMutexCls	109	

/* <NEW_ENTRY>
#define	CTCLI_ctNewAPIFunction		108
*/

#define CTCLI_TOTAL			110
/* <NEW_ENTRY>
#define CTCLI_TOTAL			106
*/

pVOID	ctClientFuncPtrs[CTCLI_TOTAL];

/*
** c-tree Plus API function macros,
** used to map API function calls to function pointer references.
*/
#ifdef ctOPT1H
#ifdef ctFeatMAXFILE32 /* These are defined in ctopt1.h and case duplicate definitions if not 'undef'd' */
#undef CREISAM
#undef CREISAMX
#undef INTISAM
#undef INTISAMX
#undef INTREE
#undef INTREEX
#undef OPNISAM
#undef OPNISAMX
#endif /* ctFeatMAXFILE32 */
#endif /* ctOPT1H */

#define	ctThrdInit		(*(pctThrdInit_t)ctClientFuncPtrs[CTCLI_ctThrdInit])
#define	ctThrdTerm		(*(pctThrdTerm_t)ctClientFuncPtrs[CTCLI_ctThrdTerm])
#define	INTISAMX		(*(pINTISAMX_t)ctClientFuncPtrs[CTCLI_INTISAMX])
#define	STPUSR		(*(pSTPUSR_t)ctClientFuncPtrs[CTCLI_STPUSR])
#define	OPNIFILX		(*(pOPNIFILX_t)ctClientFuncPtrs[CTCLI_OPNIFILX])
#define	OPNRFILX		(*(pOPNRFILX_t)ctClientFuncPtrs[CTCLI_OPNRFILX])
#define ctGetUserErrorCode	(*(pctGetUserErrorCode_t)ctClientFuncPtrs[CTCLI_ctGetUserErrorCode])
#define ctGetIsamErrorCode	(*(pctGetIsamErrorCode_t)ctClientFuncPtrs[CTCLI_ctGetIsamErrorCode])
#define ctGetIsamFileNbr	(*(pctGetIsamFileNbr_t)ctClientFuncPtrs[CTCLI_ctGetIsamFileNbr])
#define ctGetSystemErrorCode	(*(pctGetSystemErrorCode_t)ctClientFuncPtrs[CTCLI_ctGetSystemErrorCode])
#define	CLIFIL		(*(pCLIFIL_t)ctClientFuncPtrs[CTCLI_CLIFIL])
#define	GETFIL		(*(pGETFIL_t)ctClientFuncPtrs[CTCLI_GETFIL])
#define	SETNODE		(*(pSETNODE_t)ctClientFuncPtrs[CTCLI_SETNODE])
#define	CLRFIL		(*(pCLRFIL_t)ctClientFuncPtrs[CTCLI_CLRFIL])
#define	TRANBEG		(*(pTRANBEG_t)ctClientFuncPtrs[CTCLI_TRANBEG])
#define	TRANRDY		(*(pTRANRDY_t)ctClientFuncPtrs[CTCLI_TRANRDY])
#define	TRANEND		(*(pTRANEND_t)ctClientFuncPtrs[CTCLI_TRANEND])
#define	TRANABT		(*(pTRANABT_t)ctClientFuncPtrs[CTCLI_TRANABT])
#define	TRANABTX		(*(pTRANABTX_t)ctClientFuncPtrs[CTCLI_TRANABTX])
#define	ADDREC		(*(pADDREC_t)ctClientFuncPtrs[CTCLI_ADDREC])
#define	ADDVREC		(*(pADDVREC_t)ctClientFuncPtrs[CTCLI_ADDVREC])
#define	TRANSAV		(*(pTRANSAV_t)ctClientFuncPtrs[CTCLI_TRANSAV])
#define	TRANRST		(*(pTRANRST_t)ctClientFuncPtrs[CTCLI_TRANRST])
#define	SPCLSAV		(*(pSPCLSAV_t)ctClientFuncPtrs[CTCLI_SPCLSAV])
#define	FRSREC		(*(pFRSREC_t)ctClientFuncPtrs[CTCLI_FRSREC])
#define	FRSVREC		(*(pFRSVREC_t)ctClientFuncPtrs[CTCLI_FRSVREC])
#define	LSTREC		(*(pLSTREC_t)ctClientFuncPtrs[CTCLI_LSTREC])
#define	LSTVREC		(*(pLSTVREC_t)ctClientFuncPtrs[CTCLI_LSTVREC])
#define	NXTREC		(*(pNXTREC_t)ctClientFuncPtrs[CTCLI_NXTREC])
#define	NXTVREC		(*(pNXTVREC_t)ctClientFuncPtrs[CTCLI_NXTVREC])
#define	PRVREC		(*(pPRVREC_t)ctClientFuncPtrs[CTCLI_PRVREC])
#define	PRVVREC		(*(pPRVVREC_t)ctClientFuncPtrs[CTCLI_PRVVREC])
#define	RWTREC		(*(pRWTREC_t)ctClientFuncPtrs[CTCLI_RWTREC])
#define	RWTVREC		(*(pRWTVREC_t)ctClientFuncPtrs[CTCLI_RWTVREC])
#define	DELREC		(*(pDELREC_t)ctClientFuncPtrs[CTCLI_DELREC])
#define	DELVREC		(*(pDELVREC_t)ctClientFuncPtrs[CTCLI_DELVREC])
#define	EQLREC		(*(pEQLREC_t)ctClientFuncPtrs[CTCLI_EQLREC])
#define	GTEREC		(*(pGTEREC_t)ctClientFuncPtrs[CTCLI_GTEREC])
#define	GTREC			(*(pGTREC_t)ctClientFuncPtrs[CTCLI_GTREC])
#define	LTEREC		(*(pLTEREC_t)ctClientFuncPtrs[CTCLI_LTEREC])
#define	LTREC			(*(pLTREC_t)ctClientFuncPtrs[CTCLI_LTREC])
#define	EQLVREC		(*(pEQLVREC_t)ctClientFuncPtrs[CTCLI_EQLVREC])
#define	GTEVREC		(*(pGTEVREC_t)ctClientFuncPtrs[CTCLI_GTEVREC])
#define	GTVREC		(*(pGTVREC_t)ctClientFuncPtrs[CTCLI_GTVREC])
#define	LTEVREC		(*(pLTEVREC_t)ctClientFuncPtrs[CTCLI_LTEVREC])
#define	LTVREC		(*(pLTVREC_t)ctClientFuncPtrs[CTCLI_LTVREC])
#define	SETOPS		(*(pSETOPS_t)ctClientFuncPtrs[CTCLI_SETOPS])
#define	CREIFILX8		(*(pCREIFILX8_t)ctClientFuncPtrs[CTCLI_CREIFILX8])
#define	PUTDODA		(*(pPUTDODA_t)ctClientFuncPtrs[CTCLI_PUTDODA])
#define	ctThrdCreate (*(pctThrdCreate_t)ctClientFuncPtrs[CTCLI_ctThrdCreate])
#define	REDVREC		(*(pREDVREC_t)ctClientFuncPtrs[CTCLI_REDVREC])
#define	SAVPCLR		(*(pSAVPCLR_t)ctClientFuncPtrs[CTCLI_SAVPCLR])
#define	CTUSERX		(*(pCTUSERX_t)ctClientFuncPtrs[CTCLI_CTUSERX])
#define	ctTransferFile	(*(pctTransferFile_t)ctClientFuncPtrs[CTCLI_ctTransferFile])
#define	ctOWNER		(*(pctOWNER_t)ctClientFuncPtrs[CTCLI_ctOWNER])
#define	ctSetOWNER		(*(pctSetOWNER_t)ctClientFuncPtrs[CTCLI_ctSetOWNER])
#define ctThrdSleep	(*(pctThrdSleep_t)ctClientFuncPtrs[CTCLI_ctThrdSleep])
#define REGCTREE		(*(pREGCTREE_t)ctClientFuncPtrs[CTCLI_REGCTREE])
#define UNRCTREE		(*(pUNRCTREE_t)ctClientFuncPtrs[CTCLI_UNRCTREE])
#define ctThrdAttach		(*(pctThrdAttach_t)ctClientFuncPtrs[CTCLI_ctThrdAttach])
#define ctThrdDetach		(*(pctThrdDetach_t)ctClientFuncPtrs[CTCLI_ctThrdDetach])
#define GETCTREE		(*(pGETCTREE_t)ctClientFuncPtrs[CTCLI_GETCTREE])
#define ctSETCLIENTID		(*(pctSETCLIENTID_t)ctClientFuncPtrs[CTCLI_ctSETCLIENTID])
#define	ctdbGetCtreeOWNER	(*(pctdbGetCtreeOWNER_t)ctClientFuncPtrs[CTCLI_ctdbGetCtreeOWNER])
#define	ctdbSetCtreeOWNER	(*(pctdbSetCtreeOWNER_t)ctClientFuncPtrs[CTCLI_ctdbSetCtreeOWNER])
#define	OPNFILX		(*(pOPNFILX_t)ctClientFuncPtrs[CTCLI_OPNFILX])
#define	PUTIFILX8		(*(pPUTIFILX8_t)ctClientFuncPtrs[CTCLI_PUTIFILX8])
#define	AVLFILNUM		(*(pAVLFILNUM_t)ctClientFuncPtrs[CTCLI_AVLFILNUM])
#define	CLSFIL		(*(pCLSFIL_t)ctClientFuncPtrs[CTCLI_CLSFIL])
#define	SetXtdFileOpenMode	(*(pSetXtdFileOpenMode_t)ctClientFuncPtrs[CTCLI_SetXtdFileOpenMode])
#define RWTPREC		(*(pRWTPREC_t)ctClientFuncPtrs[CTCLI_RWTPREC])
#define SYSCFG		(*(pSYSCFG_t)ctClientFuncPtrs[CTCLI_SYSCFG])
#define WCHCTREE	(*(pWCHCTREE_t)ctClientFuncPtrs[CTCLI_WCHCTREE])
#define SWTCTREE	(*(pSWTCTREE_t)ctClientFuncPtrs[CTCLI_SWTCTREE])
#define	ctklusr		(*(pctklusr_t)ctClientFuncPtrs[CTCLI_ctklusr])
#define ctThrdMutexGet  (*(pctThrdMutexGet_t)ctClientFuncPtrs[CTCLI_ctThrdMutexGet])
#define ctThrdMutexRel	(*(pctThrdMutexRel_t)ctClientFuncPtrs[CTCLI_ctThrdMutexRel])
#define SA_LOGON	(*(pSA_LOGON_t)ctClientFuncPtrs[CTCLI_SA_LOGON])
#define SA_LOGOF	(*(pSA_LOGOF_t)ctClientFuncPtrs[CTCLI_SA_LOGOF])
#define SA_GROUP	(*(pSA_GROUP_t)ctClientFuncPtrs[CTCLI_SA_GROUP])
#define ctQUIET		(*(pctQUIET_t)ctClientFuncPtrs[CTCLI_ctQUIET])
#define ctdbAllocSession	(*(pctdbAllocSession_t)ctClientFuncPtrs[CTCLI_ctdbAllocSession])
#define ctdbFreeSession		(*(pctdbFreeSession_t)ctClientFuncPtrs[CTCLI_ctdbFreeSession])
#define ctdbAllocTable		(*(pctdbAllocTable_t)ctClientFuncPtrs[CTCLI_ctdbAllocTable])
#define ctdbFreeTable		(*(pctdbFreeTable_t)ctClientFuncPtrs[CTCLI_ctdbFreeTable])
#define ctdbLogon		(*(pctdbLogon_t)ctClientFuncPtrs[CTCLI_ctdbLogon])
#define ctdbAddField		(*(pctdbAddField_t)ctClientFuncPtrs[CTCLI_ctdbAddField])
#define ctdbAddIndex		(*(pctdbAddIndex_t)ctClientFuncPtrs[CTCLI_ctdbAddIndex])
#define ctdbAddSegment		(*(pctdbAddSegment_t)ctClientFuncPtrs[CTCLI_ctdbAddSegment])
#define ctdbSetTablePath	(*(pctdbSetTablePath_t)ctClientFuncPtrs[CTCLI_ctdbSetTablePath])
#define ctdbCreateTable		(*(pctdbCreateTable_t)ctClientFuncPtrs[CTCLI_ctdbCreateTable])
#define ctdbOpenTable		(*(pctdbOpenTable_t)ctClientFuncPtrs[CTCLI_ctdbOpenTable])
#define ctdbRemoveTable		(*(pctdbRemoveTable_t)ctClientFuncPtrs[CTCLI_ctdbRemoveTable])
#define ctdbAllocRecord		(*(pctdbAllocRecord_t)ctClientFuncPtrs[CTCLI_ctdbAllocRecord])
#define ctdbWriteRecord		(*(pctdbWriteRecord_t)ctClientFuncPtrs[CTCLI_ctdbWriteRecord])
#define ctdbClearRecord		(*(pctdbClearRecord_t)ctClientFuncPtrs[CTCLI_ctdbClearRecord])
#define ctdbSetFieldAsSigned		(*(pctdbSetFieldAsSigned_t)ctClientFuncPtrs[CTCLI_ctdbSetFieldAsSigned])
#define ctdbRenameTable		(*(pctdbRenameTable_t)ctClientFuncPtrs[CTCLI_ctdbRenameTable])
#define ctdbCloseTable		(*(pctdbCloseTable_t)ctClientFuncPtrs[CTCLI_ctdbCloseTable])
#define ctdbAddSegmentEx	(*(pctdbAddSegmentEx_t)ctClientFuncPtrs[CTCLI_ctdbAddSegmentEx])
#define ctdbGetFieldOffset	(*(pctdbGetFieldOffset_t)ctClientFuncPtrs[CTCLI_ctdbGetFieldOffset])
#define ctdbFirstRecord		(*(pctdbFirstRecord_t)ctClientFuncPtrs[CTCLI_ctdbFirstRecord])
#define ctdbSetTableOwner	(*(pctdbSetTableOwner_t)ctClientFuncPtrs[CTCLI_ctdbSetTableOwner])
#define SA_USERS	(*(pSA_USERS_t)ctClientFuncPtrs[CTCLI_SA_USERS])
#define	INTISAMX4		(*(pINTISAMX4_t)ctClientFuncPtrs[CTCLI_INTISAMX4])
#define ctThrdBlockGet		(*(pctThrdBlockGet_t)ctClientFuncPtrs[CTCLI_ctThrdBlockGet])
#define ctThrdBlockWait		(*(pctThrdBlockWait_t)ctClientFuncPtrs[CTCLI_ctThrdBlockWait])
#define ctThrdBlockRel		(*(pctThrdBlockRel_t)ctClientFuncPtrs[CTCLI_ctThrdBlockRel])
#define ctThrdBlockCls		(*(pctThrdBlockCls_t)ctClientFuncPtrs[CTCLI_ctThrdBlockCls])
#define ctThrdMutexCls		(*(pctThrdMutexCls_t)ctClientFuncPtrs[CTCLI_ctThrdMutexCls])
/* <NEW_ENTRY>
#define	ctNewAPIFunction_C	(*(pctNewAPIFunction_t)ctClientFuncPtrs[CTCLI_ctNewAPIFunction])
*/

/*
** c-tree Plus API function names,
** used to retrieve function addresses from c-tree DLL or shared library.
*/

pTEXT	ctClientFuncNames[CTCLI_TOTAL] = 
{
	"ctThrdInit",
	"ctThrdTerm",
	"INTISAMX",
	"STPUSR",
	"OPNIFILX",
	"OPNRFILX",
	"ctGetUserErrorCode",
	"ctGetIsamErrorCode",
	"ctGetIsamFileNbr",
	"ctGetSystemErrorCode",
	"CLIFIL",
	"GETFIL",
	"SETNODE",
	"CLRFIL",
	"TRANBEG",
	"TRANRDY",
	"TRANEND",
	"TRANABT",
	"TRANABTX",
	"ADDREC",
	"ADDVREC",
	"TRANSAV",
	"TRANRST",
	"SPCLSAV",
	"FRSREC",
	"FRSVREC",
	"LSTREC",
	"LSTVREC",
	"NXTREC",
	"NXTVREC",
	"PRVREC",
	"PRVVREC",
	"RWTREC",
	"RWTVREC",
	"DELREC",
	"DELVREC",
	"EQLREC",
	"GTEREC",
	"GTREC",
	"LTEREC",
	"LTREC",
	"EQLVREC",
	"GTEVREC",
	"GTVREC",
	"LTEVREC",
	"LTVREC",
	"SETOPS",
	"CREIFILX8",
	"PUTDODA",
	"ctThrdCreate",
	"REDVREC",
	"SAVPCLR",
	"CTUSERX",
	"ctTransferFile",
	"ctOWNER",
	"ctSetOWNER",
	"ctThrdSleep",
	"REGCTREE",
	"UNRCTREE",
	"ctThrdAttach",
	"ctThrdDetach",
	"GETCTREE",
	"ctSETCLIENTID",
	"ctdbGetCtreeOWNER",
	"ctdbSetCtreeOWNER",
	"OPNFILX",
	"PUTIFILX8",
	"AVLFILNUM",
	"CLSFIL",
	"SetXtdFileOpenMode",
	"RWTPREC",
	"SYSCFG",
	"WCHCTREE",
	"SWTCTREE",
	"ctklusr",
	"ctThrdMutexGet",
	"ctThrdMutexRel",
	"SA_LOGON",
	"SA_LOGOF",
	"SA_GROUP",
	"ctQUIET",
	"ctdbAllocSession",
	"ctdbFreeSession",
	"ctdbAllocTable",
	"ctdbFreeTable",
	"ctdbLogon",
	"ctdbAddField",
	"ctdbAddIndex",
	"ctdbAddSegment",
	"ctdbSetTablePath",
	"ctdbCreateTable",
	"ctdbOpenTable",
	"ctdbRemoveTable",
	"ctdbAllocRecord",
	"ctdbWriteRecord",
	"ctdbClearRecord",
	"ctdbSetFieldAsSigned",
	"ctdbRenameTable",
	"ctdbCloseTable",
	"ctdbAddSegmentEx",
	"ctdbGetFieldOffset",
	"ctdbFirstRecord",
	"ctdbSetTableOwner",
	"SA_USERS",
	"INTISAMX4",
	"ctThrdBlockGet",
	"ctThrdBlockWait",
	"ctThrdBlockRel",
	"ctThrdBlockCls",
	"ctThrdMutexCls"/*,

	"ctdbGetError"*/
};
