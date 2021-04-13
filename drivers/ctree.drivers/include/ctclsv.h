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

#ifdef ctFeatSRVDLL

#include <signal.h>
#ifdef ctPortUNIX
#include <dlfcn.h>
#endif
#include "ctdbsdk.h"

#undef  uerr_cod
#define uerr_cod	ctAppGetUEC()
#undef  isam_err
#define isam_err	ctAppGetIEC()
#undef  isam_fil
#define isam_fil	ctAppGetIFL()
#undef  sysiocod
#define sysiocod	ctAppGetSEC()

#ifndef ctrt_printf
#define ctrt_printf printf /* ensure console (non-GUI) output */
#endif

#undef ctrt_exit
#define ctrt_exit exit

#ifdef ctAppESQL
#define ctSQLS		/* Server DLL supports SQL functions */
#else
#define ctSQLS ";"	/* Server DLL does not support SQL functions */
#endif

/*
 * To add support for additional c-tree functions, search for <NEW_ENTRY>
 * and make the appropriate changes.
 */

/*
 * c-tree Plus API function type definitions,
 * used to define appropriate data types for function pointers.
 */

#ifdef PROTOTYPE
#define __(args)        args
#else
#define __(args)        ()
#endif

typedef NINT		(* pctThrdInit_t) __((NINT, LONG, pctINIT));
typedef NINT		(*pctThrdTerm_t) __((VOID));
typedef COUNT		(* pINTISAMX_t) __((COUNT, FILNO, COUNT, COUNT, COUNT, pTEXT, pTEXT, pTEXT));
typedef COUNT		(* pSTPUSR_t) __((VOID));
typedef pTEXT		(* pWCHCTREE_t) __((VOID));
typedef pCTGVAR		(* pGETCTREE_t) __((pTEXT));
typedef COUNT		(* pOPNFIL_t) __((FILNO, pTEXT, COUNT));
#ifdef ctPortWIN32
typedef LONG		* ptlsIndex_t;
#else
typedef NINT		(* ppthread_OWNER_t) __((VOID));
#endif
typedef pCTSTATV	*pctstatv_t;
typedef NINT		*pcttflg_t;
typedef NINT		(*pctThrdSleep_t) __((LONG));
typedef COUNT		(*pctSETEXITFNC_t) __((ctexitfnc_t));
typedef COUNT		(*pTRANEND_t) __((COUNT));
typedef COUNT		(*pTRANABTX_t) __((COUNT));
typedef COUNT		(*pRWTVREC_t) __((FILNO, pVOID, VRLEN));
typedef COUNT		(*pRWTREC_t) __((FILNO, pVOID));
typedef COUNT		(*pDELVREC_t) __((FILNO));
typedef COUNT		(*pEQLVREC_t) __((FILNO, pVOID, pVOID, pVRLEN));
typedef COUNT		(*pDELREC_t) __((FILNO));
typedef COUNT		(*pEQLREC_t) __((FILNO, pVOID, pVOID));
typedef COUNT		(*pADDVREC_t) __((FILNO, pVOID, VRLEN));
typedef VOID		(*pmbfree_t) __((pVOID));
typedef COUNT		(*pREDIVREC_t) __((FILNO, LONG, pVOID, pVRLEN));
typedef COUNT		(*pADDREC_t) __((FILNO, pVOID));
typedef COUNT		(*pLKISAM_t) __((COUNT));
typedef LONG		(*pTRANBEG_t) __((COUNT));
typedef COUNT		(*pSWTCTREE_t) __((pTEXT));
typedef COUNT		(*pREDIREC_t) __((FILNO, LONG, pVOID));
typedef NINT		(*pctSETHGH_t) __((LONG));
typedef pTEXT		(*pmballc_t) __((NINT, UINT));
typedef VOID		(*pctThrdExit_t) __((VOID));
typedef NINT		(*pctThrdMutexRel_t) __((pctMUTEX));
typedef NINT		(*pctThrdMutexGet_t) __((pctMUTEX));
typedef NINT		(*pctSysQueueRead_t) __((NINT, pVOID, NINT, LONG));
typedef NINT		(*pctNotify_t) __((NINT, NINT, NINT, NINT, NINT));
typedef NINT		(*pctCallback_t) __((NINT, NINT, ctCallbackPtr, NINT, NINT));
typedef NINT		(*pctSysQueueOpen_t) __((pTEXT, NINT));
typedef LONG		(*pGETFIL_t) __((FILNO, COUNT));
typedef FILNO		(*pOPNRFIL_t) __((FILNO, pTEXT, COUNT));
typedef COUNT		(*pREGCTREE_t) __((pTEXT));
typedef NINT		(*pctThrdCreate_t) __((pctFUNC, pVOID, pVOID, LONG));
typedef NINT		(*pctThrdMutexInit_t) __((pctMUTEX));
typedef NINT		(*pctThrdAttach_t) __((VOID));
typedef NINT		(*pctThrdDetach_t) __((VOID));
typedef COUNT		(*pTRANSAV_t) __((VOID));
typedef COUNT		(*pTRANRST_t) __((COUNT));
typedef COUNT		(*pTRANABT_t) __((VOID));
typedef NINT		(*pctThrdQueueWrite_t) __((NINT, pVOID, NINT));
typedef COUNT		(*pGTEREC_t) __((FILNO, pVOID, pVOID));
typedef COUNT		(*pcttestfunc_t) __((VOID));
typedef FILNO		(*pOPNRFILX_t) __((FILNO, pTEXT, COUNT, pTEXT));
typedef COUNT		(*pPUTDODA_t) __((FILNO, pDATOBJ, UCOUNT));
typedef COUNT		(*pCREIFILX_t) __((pIFIL,pTEXT, pTEXT, LONG, pTEXT ,pTEXT));
typedef COUNT		(*pDELIFIL_t) __((pIFIL ifilptr));
typedef COUNT		(*pOPNIFILX_t) __((pIFIL, pTEXT, pTEXT, pTEXT));
typedef NINT		(*pctThrdQueueRead_t) __((NINT, pVOID, NINT, LONG));
typedef NINT		(*pctThrdQueueMlen_t) __((NINT, LONG));
typedef NINT		(*pctThrdMutexCls_t) __((pctMUTEX));
typedef NINT		(*pctThrdQueueOpen_t) __((VOID));
typedef NINT		(*pctThrdBlockInit_t) __((pctBLOCK));
typedef COUNT		(*pFRSREC_t) __((FILNO, pVOID));
typedef COUNT		(*pCLRFIL_t) __((FILNO));
typedef VRLEN		(*pGETIFIL_t) __((FILNO, LONG, pVOID));
typedef VRLEN		(*pGETDODA_t) __((FILNO, LONG, pVOID, COUNT));
typedef COUNT		(*pGETNAM_t) __((FILNO, pTEXT, VRLEN, COUNT));
typedef NINT		(*pGETXCREBLK_t) __((FILNO, pXCREblk));
typedef COUNT		(*pCREIFILX8_t) __((pIFIL,pTEXT, pTEXT, LONG, pTEXT ,pTEXT, pXCREblk));
typedef COUNT		(*pFRSVREC_t) __((FILNO, pVOID, pVRLEN));
typedef COUNT		(*pNXTVREC_t) __((FILNO, pVOID, pVRLEN));
typedef COUNT		(*pNXTREC_t) __((FILNO, pVOID));
typedef LONG		(*pSETOPS_t) __((LONG, VRLEN));
typedef COUNT		(*pREDVREC_t) __((FILNO, pVOID, VRLEN));
typedef COUNT		(*pCLISAM_t) __(());
typedef COUNT		(*pGTEVREC_t) __((FILNO, pVOID, pVOID, pVRLEN));
typedef pTEXT		(*pGETCURK_t) __((FILNO, pVOID, pVRLEN));
typedef COUNT		(*pSETNODE_t) __((pTEXT));
typedef COUNT		(*pBATSET_t) __((FILNO, pVOID, pVOID, VRLEN, UCOUNT));
typedef COUNT		(*pSECURITY_t) __((FILNO, pVOID, VRLEN, COUNT));
typedef COUNT		(*pCLIFIL_t) __((pIFIL));
typedef COUNT		(*pctSysQueueLIFOWrite_t) __((NINT, pVOID, NINT));
typedef COUNT		(*pLOKREC_t) __((FILNO, COUNT, LONG));
typedef LONG		(*pGETCURP_t) __((FILNO));
typedef LONG		(*pEQLKEY_t) __((FILNO, pVOID));
typedef NINT		(*pctCLSNAM_t) __((pTEXT, pTEXT));
typedef COUNT		(*pSYSCFG_t) __((pVOID));
typedef LONG		(*pCTUSER_t) __((pTEXT, pTEXT, VRLEN));
typedef COUNT		(*pctLOKDMP_t) __((FILNO, pTEXT, COUNT));
typedef NINT		(*pctSysQueueWrite_t) __((NINT, pVOID, NINT));
typedef COUNT		(*pCLSFIL_t) __((FILNO, COUNT));
typedef COUNT		(*pCREIDXX8_t) __((FILNO, pTEXT, COUNT, COUNT, COUNT, COUNT, UCOUNT, COUNT, LONG, pTEXT, pTEXT, pXCREblk));
typedef FILNO		(*pAVLFILNUM_t) __((COUNT));
typedef LONG		(*pGTEKEY_t) __((FILNO, pVOID, pVOID));
typedef LONG		(*pctGETHGH_t) __((VOID));
typedef COUNT		(*pADDKEY_t) __((FILNO, pVOID, LONG, COUNT));
typedef COUNT		(*pDELCHK_t) __((FILNO, pVOID, LONG));
typedef COUNT		(*pctGetUserErrorCode_t) __((VOID));
typedef COUNT		(*pctGetIsamErrorCode_t) __((VOID));
typedef COUNT		(*pctGetIsamFileNbr_t) __((VOID));
typedef COUNT		(*pctGetSystemErrorCode_t) __((VOID));
typedef COUNT		(*pUNRCTREE_t) __((pTEXT));
#ifdef ctAppESQL
typedef void		(*pdh_free_sqlenv_t) __((dh_sqlenv_hdl_t));
typedef void		(*pdh_sql_disconnect_t) __((dh_sqlenv_hdl_t, tpe_discon_sp_t, dh_char_t *, struct sqlca *));
typedef void		(*pdh_tm_mark_abort_t) __((dh_sqlenv_hdl_t, tpe_tm_hdl_t, struct sqlca *));
typedef void		(*pdh_sqlselect_t) __((dh_sqlenv_hdl_t, tpe_tm_hdl_t, tpe_db_hdl_t, tpe_cursor_t,  struct sqlda *, struct sqlda *, struct sqlca *));
typedef void		(*pdh_tm_end_trans_t) __((dh_sqlenv_hdl_t, tpe_tm_hdl_t, struct sqlca *));
typedef void		(*pdh_release_cursor_t) __((dh_sqlenv_hdl_t, tpe_cursor_t *));
typedef void		(*pdh_sqlexecute_t) __((dh_sqlenv_hdl_t, tpe_tm_hdl_t, tpe_db_hdl_t, tpe_cursor_t, struct sqlda *, struct sqlca *));
typedef void		(*pdh_set_cursorname_t) __((tpe_cursor_t, dh_char_t *, struct sqlca *));
typedef void		(*pdh_set_cursor_t) __((dh_sqlenv_hdl_t, tpe_tm_hdl_t, tpe_db_hdl_t, tpe_cursor_t *, tpe_uuid__t *, dh_i32_t, dh_char_t *, struct sqlca *));
typedef void		(*pdh_sql_chk_connection_t) __((dh_sqlenv_hdl_t, struct sqlca *));
typedef void		(*ptpe_set_sqlda_t) __((struct sqlda *, dh_i32_t, dh_i32_t, dh_i16_t *, dh_i32_t *, dh_i32_t *, dh_char_t **, dh_char_t **, dh_char_t **, dh_char_t **));
typedef void		(*pdh_set_ptrs_t) __((dh_char_t **, dh_i32_t, ...));
typedef tpe_db_hdl_t	(*pdh_get_curdbhdl_t) __((dh_sqlenv_hdl_t));
typedef tpe_tm_hdl_t	(*pdh_get_curtmhdl_t) __((dh_sqlenv_hdl_t));
typedef void		(*pdh_sqlconnect_t) __((const dh_sqlenv_hdl_t, const dh_char_t *, const dh_char_t *, const dh_char_t *, const dh_char_t *, const dh_char_t *, struct sqlca *));
typedef void		(*pdh_alloc_sqlenv_t) __((dh_sqlenv_hdl_t *));
#endif /* ctAppESQL */
typedef COUNT		(*pRWTPREC_t) __((FILNO, pVOID, VRLEN));
typedef LONG		(*pSERIALNUM_t) __((FILNO));
typedef LONG		(*pIDXENT_t) __((FILNO));
typedef LONG		(*pctDISTINCTest_t) __((FILNO));
typedef LONG		(*pctDISTINCTset_t) __((FILNO, NINT));
typedef COUNT		(*pDELFIL_t) __((FILNO));
typedef CTDBRET		(*pctdbAbort_t) __((CTHANDLE));
typedef CTHANDLE	(*pctdbAddField_t) __((CTHANDLE, pTEXT, CTDBTYPE, VRLEN));
typedef CTHANDLE	(*pctdbAddIndex_t) __((CTHANDLE, pTEXT, CTDBKEY, CTBOOL, CTBOOL));
typedef CTDBRET		(*pctdbAddLocateCriteria_t) __((CTHANDLE, CTSTRING, CTSTRING));
typedef CTHANDLE	(*pctdbAddSegment_t) __((CTHANDLE, CTHANDLE, CTSEG_MODE));
typedef CTHANDLE	(*pctdbAllocDatabase_t) __((CTHANDLE));
typedef CTHANDLE	(*pctdbAllocRecord_t) __((CTHANDLE));
typedef CTHANDLE	(*pctdbAllocSession_t) __((CTSESSION_TYPE));
typedef CTHANDLE	(*pctdbAllocTable_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbAlterTable_t) __((CTHANDLE, NINT));
typedef CTDBRET		(*pctdbBegin_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbClearRecord_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbCloneTable_t) __((CTHANDLE, pTEXT, CTHANDLE));
typedef CTDBRET		(*pctdbCloseAll_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbCloseTable_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbCommit_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbConnect_t) __((CTHANDLE, pTEXT));
typedef CTDBRET		(*pctdbCreateTable_t) __((CTHANDLE, pTEXT, CTCREATE_MODE));
typedef CTDBRET		(*pctdbDeleteRecord_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbDisconnect_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbFilterRecord_t) __((CTHANDLE, pTEXT));
typedef CTHANDLE	(*pctdbFindActiveTable_t) __((CTHANDLE, pTEXT));
typedef CTDBRET		(*pctdbFindKey_t) __((CTHANDLE, pCTOFFSET, CTFIND_MODE));
typedef CTDBRET		(*pctdbFindRowid_t) __((CTHANDLE, CTROWID, CTFIND_MODE));
typedef CTDBRET		(*pctdbFirstRecord_t) __((CTHANDLE));
typedef VOID		(*pctdbFreeDatabase_t) __((CTHANDLE));
typedef VOID		(*pctdbFreeRecord_t) __((CTHANDLE));
typedef VOID		(*pctdbFreeSession_t) __((CTHANDLE));
typedef VOID		(*pctdbFreeTable_t) __((CTHANDLE));
typedef CTHANDLE	(*pctdbGetBestIndex_t) __((CTHANDLE, pCTDBLIST, CTLOC_MODE));
typedef CTDBRET		(*pctdbGetCndxIndex_t) __((CTHANDLE, NINT, pTEXT, NINT));
typedef NINT		(*pctdbGetCndxIndexLength_t) __((CTHANDLE, NINT));
typedef pTEXT		(*pctdbGetDatabaseName_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbGetError_t) __((CTHANDLE));
typedef CTHANDLE	(*pctdbGetField_t) __((CTHANDLE, NINT));
typedef CTDBRET		(*pctdbGetFieldAsBigint_t) __((CTHANDLE, NINT, pCTBIGINT));
typedef CTDBRET		(*pctdbGetFieldAsString_t) __((CTHANDLE, NINT, CTSTRING, VRLEN));
typedef CTDBRET		(*pctdbGetFieldAsBinary_t) __((CTHANDLE, NINT, pVOID, VRLEN));
typedef CTHANDLE	(*pctdbGetFieldByName_t) __((CTHANDLE, pTEXT));
typedef VRLEN		(*pctdbGetFieldLength_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetFieldName_t) __((CTHANDLE));
typedef NINT		(*pctdbGetFieldNbr_t) __((CTHANDLE));
typedef CTBOOL		(*pctdbGetFieldNullFlag_t) __((CTHANDLE));
typedef NINT		(*pctdbGetFieldNumber_t) __((CTHANDLE, pTEXT));
typedef NINT		(*pctdbGetFieldNumberByName_t) __((CTHANDLE, pTEXT));
typedef CTDBTYPE	(*pctdbGetFieldType_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetFilter_t) __((CTHANDLE));
typedef CTHANDLE	(*pctdbGetIndex_t) __((CTHANDLE, NINT));
typedef CTBOOL		(*pctdbGetIndexDuplicateFlag_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetIndexExtension_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbGetIndexNbr_t) __((CTHANDLE, pVRLEN));
typedef VRLEN		(*pctdbGetIndexSegmentCount_t) __((CTHANDLE));
typedef CTHANDLE	(*pctdbGetRecord_t) __((CTHANDLE, NINT));
typedef pVOID		(*pctdbGetRecordBuffer_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbGetRecordCount_t) __((CTHANDLE, pCTUINT64));
typedef VRLEN		(*pctdbGetRecordLength_t) __((CTHANDLE));
typedef CTLOCK_MODE	(*pctdbGetRecordLock_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbGetRowid_t) __((CTHANDLE, pCTROWID));
typedef CTHANDLE	(*pctdbGetSegment_t) __((CTHANDLE, NINT));
typedef CTHANDLE	(*pctdbGetSegmentField_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetSegmentFieldName_t) __((CTHANDLE));
typedef CTSEG_MODE	(*pctdbGetSegmentMode_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetServerName_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetTableExtension_t) __((CTHANDLE));
typedef VRLEN		(*pctdbGetTableFieldCount_t) __((CTHANDLE));
typedef VRLEN		(*pctdbGetTableIndexCount_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetTableName_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetTablePath_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetUserLogonName_t) __((CTHANDLE));
typedef pTEXT		(*pctdbGetUserPassword_t) __((CTHANDLE));
typedef CTBOOL		(*pctdbIsActiveDatabase_t) __((CTHANDLE));
typedef CTBOOL		(*pctdbIsEditedRecord_t) __((CTHANDLE));
typedef CTBOOL		(*pctdbIsFilteredRecord_t) __((CTHANDLE));
typedef CTBOOL		(*pctdbIsNewRecord_t) __((CTHANDLE));
typedef CTBOOL		(*pctdbIsNullField_t) __((CTHANDLE, NINT));
typedef CTBOOL		(*pctdbIsTransActive_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbJumpToRecord_t) __((CTHANDLE, LONG));
typedef CTDBRET		(*pctdbLastRecord_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbLockRecord_t) __((CTHANDLE, NINT));
typedef CTDBRET		(*pctdbLogon_t) __((CTHANDLE, pTEXT, pTEXT, pTEXT));
typedef CTDBRET		(*pctdbLogout_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbNextRecord_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbOpenTable_t) __((CTHANDLE, pTEXT, CTOPEN_MODE));
typedef CTDBRET		(*pctdbPrevRecord_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbReadRecord_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbSetDefaultIndex_t) __((CTHANDLE, NINT));
typedef CTDBRET		(*pctdbSetDefaultIndexByName_t) __((CTHANDLE, pTEXT));
typedef CTDBRET		(*pctdbSetError_t) __((CTHANDLE, CTDBRET));
typedef CTDBRET		(*pctdbSetFieldAsBigint_t) __((CTHANDLE, NINT, CTBIGINT));
typedef CTDBRET		(*pctdbSetFieldAsDate_t) __((CTHANDLE, NINT, CTDATE));
typedef CTDBRET		(*pctdbSetFieldAsDateTime_t) __((CTHANDLE, NINT, CTDATETIME));
typedef CTDBRET		(*pctdbSetFieldAsNumber_t) __((CTHANDLE, NINT, pCTNUMBER));
typedef CTDBRET		(*pctdbSetFieldAsSigned_t) __((CTHANDLE, NINT, CTSIGNED));
typedef CTDBRET		(*pctdbSetFieldAsString_t) __((CTHANDLE, NINT, CTSTRING));
typedef CTDBRET		(*pctdbSetFieldAsBinary_t) __((CTHANDLE, NINT, pVOID, VRLEN));
typedef CTDBRET		(*pctdbSetFieldAsTime_t) __((CTHANDLE, NINT, CTTIME));
typedef CTDBRET		(*pctdbSetIndexCndxExpr_t) __((CTHANDLE, pTEXT));
typedef CTDBRET		(*pctdbSetIndexFilename_t) __((CTHANDLE, pTEXT, pTEXT));
typedef CTDBRET		(*pctdbSetIndexTemporaryFlag_t) __((CTHANDLE, CTBOOL));
typedef CTDBRET		(*pctdbSetRecordCriteria_t) __((CTHANDLE, CTLOC_MODE));
typedef CTDBRET		(*pctdbUpdateRecordCriteria_t) __((CTHANDLE, CTLOC_MODE));
typedef CTDBRET		(*pctdbStartDatabaseEngine_t) __((VOID));
typedef VOID		(*pctdbStopDatabaseEngine_t) __((VOID));
typedef CTDBRET		(*pctdbUnlockRecord_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbWriteRecord_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbParseRecordExpr_t) __((CTHANDLE, pTEXT, pCTDBTYPE, pNINT));
typedef CTDBRET		(*pctdbEvalExprAsSigned_t) __((CTHANDLE, NINT, pCTSIGNED));
typedef CTDBRET		(*pctdbEvalExprAsDate_t) __((CTHANDLE, NINT, pCTDATE));
typedef CTDBRET		(*pctdbEvalExprAsTime_t) __((CTHANDLE, NINT, pCTTIME));
typedef CTDBRET		(*pctdbEvalExprAsDateTime_t) __((CTHANDLE, NINT, pCTDATETIME));
typedef CTDBRET		(*pctdbEvalExprAsNumber_t) __((CTHANDLE, NINT, pCTNUMBER));
typedef CTDBRET		(*pctdbEvalExprAsString_t) __((CTHANDLE, NINT, pTEXT, pVRLEN));
typedef CTDBRET		(*pctdbSetDefDateType_t) __((CTHANDLE, CTDATE_TYPE));
typedef CTDBRET		(*pctdbSetDefTimeType_t) __((CTHANDLE, CTTIME_TYPE));
typedef NINT		(*pctFILWCD_t) __((pTEXT, NINT, pTEXT, pVRLEN));
typedef CTDBRET		(*pctdbAddUserDefFunc_t) __((CTHANDLE, pTEXT, ctdbUDFFunc, CTDBTYPE, pCTDBTYPE, COUNT));
typedef pVOID		(*p_ctdb_allocFunc_t) __((VRLEN, VRLEN));
typedef pVOID		(*p_ctdb_freeFunc_t) __((pVOID));
typedef pCTDBLIST	(*p_ctdbListAllocFunc_t) __(());
typedef pCTDBLIST	(*p_ctdbListFreeFunc_t) __((pCTDBLIST));
typedef NINT		(*p_ctdbListCountFunc_t) __((pCTDBLIST));
typedef CTDBRET		(*p_ctdbListDeleteExFunc_t) __((pCTDBLIST, pVOID));
typedef pVOID		(*p_ctdbListItemFunc_t) __((pCTDBLIST, NINT));
typedef CTDBRET		(*p_ctdbListAddFunc_t) __((pCTDBLIST, pVOID));
typedef CTDBRET		(*p_ctdbSetFieldDefaultValue_t) __((CTHANDLE, pTEXT, VRLEN));
typedef pTEXT		(*p_ctdbGetFieldDefaultValue_t) __((CTHANDLE, pVRLEN));
typedef CTDBRET		(*p_ctdbDeleteTable_t) __((CTHANDLE, pTEXT, pTEXT));
typedef CTDBRET		(*p_ctdbFindTable_t) __((CTHANDLE, pTEXT, pTEXT, VRLEN));
typedef CTDBRET		(*p_ctdbFirstTable_t) __((CTHANDLE, pTEXT, VRLEN, pTEXT, VRLEN));
typedef CTDBRET		(*p_ctdbNextTable_t) __((CTHANDLE, pTEXT, VRLEN, pTEXT, VRLEN));
typedef CTDBRET		(*p_ctdbCreateDatabase_t) __((CTHANDLE, pTEXT, pTEXT));
typedef CTDBRET		(*p_ctdbSetRecordBuffer_t) __((CTHANDLE, pVOID, VRLEN, CTRECBUF_MODE));
typedef CTHANDLE	(*p_ctdbAddSegmentEx_t) __((CTHANDLE, NINT, NINT, CTSEG_MODE));
typedef NINT		(*p_ctdbGetFieldPrecision_t) __((CTHANDLE));
typedef NINT		(*p_ctdbGetFieldScale_t) __((CTHANDLE));
typedef NINT		(*p_ctdbGetIndexEmptyChar_t) __((CTHANDLE));
typedef CTDBKEY		(*p_ctdbGetIndexKeyType_t) __((CTHANDLE));
typedef CTBOOL		(*p_ctdbGetIndexNullFlag_t) __((CTHANDLE));
typedef CTCREATE_MODE	(*p_ctdbGetTableCreateMode_t) __((CTHANDLE));
typedef CTDBRET		(*p_ctdbSetFieldNullFlag_t) __((CTHANDLE, CTBOOL));
typedef CTDBRET		(*p_ctdbSetFieldPrecision_t) __((CTHANDLE, NINT));
typedef CTDBRET		(*p_ctdbSetFieldScale_t) __((CTHANDLE, NINT));
typedef CTDBRET		(*p_ctdbSetIndexEmptyChar_t) __((CTHANDLE, NINT));
typedef CTDBRET		(*p_ctdbSetAutoCommit_t) __((CTHANDLE, CTBOOL));
typedef NINT		(*p_ctCreateSequence_t) __((pctSEQATTR));
typedef NINT		(*p_ctDeleteSequence_t) __((pTEXT));
typedef NINT		(*p_ctOpenSequence_t) __((pTEXT,pLONG));
typedef NINT		(*p_ctGetCurrentSequenceValue_t) __((LONG, pLONG8, pNINT));
typedef NINT		(*p_ctSetCurrentSequenceValue_t) __((LONG, LONG8));
typedef NINT		(*p_ctGetNextSequenceValue_t) __((LONG, pLONG8, pNINT));
typedef VRLEN		(*p_ctdbGetFieldDataLength_t) __((CTHANDLE, NINT));
typedef CTDBRET		(*p_ctdbClearField_t) __((CTHANDLE, NINT));
typedef CTDBRET		(*p_ctdbGetFieldAsNumber_t) __((CTHANDLE, NINT, pCTNUMBER));
typedef CTDBRET		(*p_ctdbGetFieldAsCurrency_t) __((CTHANDLE, NINT, pCTCURRENCY));
typedef CTDBRET		(*p_ctdbGetFieldAsUnsignedBigint_t) __((CTHANDLE, NINT, pCTUBIGINT));
typedef CTDBRET		(*p_ctdbGetFieldAsFloat_t) __((CTHANDLE, NINT, pCTFLOAT));
typedef CTDBRET		(*p_ctdbGetFieldAsMoney_t) __((CTHANDLE, NINT, pCTMONEY));
typedef CTDBRET		(*p_ctdbGetFieldAsSigned_t) __((CTHANDLE, NINT, pCTSIGNED));
typedef CTDBRET		(*p_ctdbGetFieldAsUnsigned_t) __((CTHANDLE, NINT, pCTUNSIGNED));
typedef CTDBRET		(*p_ctdbGetFieldAsBool_t) __((CTHANDLE, NINT, pCTBOOL));
typedef CTDBRET		(*p_ctdbSetFieldAsCurrency_t) __((CTHANDLE, NINT, CTCURRENCY));
typedef CTDBRET		(*p_ctdbSetFieldAsUnsignedBigint_t) __((CTHANDLE, NINT, CTUBIGINT));
typedef CTDBRET		(*p_ctdbSetFieldAsFloat_t) __((CTHANDLE, NINT, CTFLOAT));
typedef CTDBRET		(*p_ctdbSetFieldAsMoney_t) __((CTHANDLE, NINT, CTMONEY));
typedef CTDBRET		(*p_ctdbSetFieldAsUnsigned_t) __((CTHANDLE, NINT, CTUBIGINT));
typedef CTDBRET		(*p_ctdbSetFieldAsBool_t) __((CTHANDLE, NINT, CTBOOL));
typedef CTDBRET		(*p_ctdbAssignRecordBuffer_t) __((CTHANDLE, pVOID, VRLEN));
typedef CTDBRET		(*p_ctdbListDeleteFunc_t) __((pCTDBLIST, NINT));
typedef CTDBRET		(*p_ctdbSetTransactionMode_t) __((CTHANDLE, CTBEGIN_MODE));
typedef CTBOOL		(*p_ctdbIsActiveSession_t) __((CTHANDLE));
typedef CTBOOL		(*p_ctdbLocateRecord_t) __((CTHANDLE, CTLOC_MODE));
typedef CTDBRET		(*p_ctdbBigIntToString_t) __((CTBIGINT, pTEXT, NINT));
typedef CTDBRET		(*pctdbFindRecord_t) __((CTHANDLE, CTFIND_MODE));
typedef NINT		(*pctdbSetSavePoint_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbRestoreSavePoint_t) __((CTHANDLE, NINT));
typedef CTOPEN_MODE	(*pctdbGetTableOpenMode_t) __((CTHANDLE));
typedef CTDBRET		(*pctdbCreateDir_t) __((pTEXT));
typedef pTEXT		(*pctdbGetPathPrefix_t) __((CTHANDLE));
typedef CTBOOL		(*pctdbIsActiveTable_t) __((CTHANDLE));
typedef CTHANDLE	(*pctdbGetIndexByName_t) __((CTHANDLE, pTEXT));
typedef CTDBRET		(*pctdbCreateSession_t) __((CTHANDLE, pTEXT, pTEXT, pTEXT));
typedef CTDBRET		(*pctdbAddTableXtd_t) __((CTHANDLE, pTEXT, pTEXT, pTEXT));
typedef COUNT		(*pBATSETX_t) __((FILNO, pVOID, pVOID, VRLEN, ULONG));
typedef NINT		(*pctdbGetCtreeOWNER_t) __((VOID));
typedef VOID		(*pctdbSetCtreeOWNER_t) __((NINT));
typedef LONG		(*pGETRES_t) __((FILNO, pVOID, pVOID, VRLEN, COUNT));
typedef COUNT		(*pADDRES_t) __((FILNO, pVOID, VRLEN));
typedef COUNT		(*pSETVARBYTS_t) __((FILNO, pUTEXT));
/* <NEW_ENTRY>
typedef RTNTYP   (*pctNewAPIFunction_t) __((PARAMLIST));
*/

/*
 * c-tree Plus API function identifiers,
 * used as index into function pointer list.
 */

#define SHFN_TOTAL		310
/* <NEW_ENTRY>
#define SHFN_TOTAL		311
*/

#define	SHFN_ctThrdInit			0
#define	SHFN_ctThrdTerm			1
#define	SHFN_INTISAMX			2
#define	SHFN_STPUSR			3
#define	SHFN_GETCTREE			4
#define	SHFN_WCHCTREE			5
#define	SHFN_OPNFIL			6
#ifdef ctPortWIN32
#define	SHFN_tlsIndex			7
#else
#define	SHFN_pthread_OWNER		7
#endif
#define	SHFN_ctstatv			8
#define	SHFN_cttflg			9
#define	SHFN_ctThrdSleep		10
#define	SHFN_ctSETEXITFNC		11
#define	SHFN_TRANEND			12
#define	SHFN_TRANABTX			13
#define	SHFN_RWTVREC			14
#define	SHFN_RWTREC			15
#define	SHFN_DELVREC			16
#define	SHFN_EQLVREC			17
#define	SHFN_DELREC			18
#define	SHFN_EQLREC			19
#define	SHFN_ADDVREC			20
#define	SHFN_mbfree			21
#define	SHFN_REDIVREC			22
#define	SHFN_ADDREC			23
#define	SHFN_LKISAM			24
#define	SHFN_TRANBEG			25
#define	SHFN_SWTCTREE			26
#define	SHFN_REDIREC			27
#define	SHFN_ctSETHGH			28
#define	SHFN_mballc			29
#define	SHFN_ctThrdExit			30
#define	SHFN_ctThrdMutexRel		31
#define	SHFN_ctThrdMutexGet		32
#define	SHFN_ctSysQueueRead		33
#define	SHFN_ctNotify			34
#define	SHFN_ctCallback			35
#define	SHFN_ctSysQueueOpen		36
#define	SHFN_GETFIL			37
#define	SHFN_OPNRFIL			38
#define	SHFN_REGCTREE			39
#define	SHFN_ctThrdCreate		40
#define	SHFN_ctThrdMutexInit		41
#define	SHFN_ctThrdAttach		42
#define	SHFN_ctThrdDetach		43
#define	SHFN_TRANSAV			44
#define	SHFN_TRANRST			45
#define	SHFN_TRANABT			46
#define	SHFN_ctThrdQueueWrite		47
#define	SHFN_GTEREC			48
#define	SHFN_cttestfunc			49
#define	SHFN_OPNRFILX			50
#define	SHFN_PUTDODA			51
#define	SHFN_CREIFILX			52
#define	SHFN_DELIFIL			53
#define	SHFN_OPNIFILX			54
#define	SHFN_ctThrdQueueRead		55
#define	SHFN_ctThrdQueueMlen		56
#define	SHFN_ctThrdMutexCls		57
#define	SHFN_ctThrdQueueOpen		58
#define	SHFN_ctThrdBlockInit		59
#define	SHFN_FRSREC			60
#define	SHFN_CLRFIL			61
#define	SHFN_GETIFIL			62
#define	SHFN_GETDODA			63
#define	SHFN_GETNAM			64
#define	SHFN_GETXCREBLK			65
#define	SHFN_CREIFILX8			66
#define	SHFN_FRSVREC			67
#define	SHFN_NXTVREC			68
#define	SHFN_NXTREC			69
#define	SHFN_SETOPS			70
#define	SHFN_REDVREC			71
#define	SHFN_CLISAM			72
#define	SHFN_GTEVREC			73
#define	SHFN_GETCURK			74
#define	SHFN_SETNODE			75
#define	SHFN_BATSET			76
#define	SHFN_SECURITY			77
#define	SHFN_CLIFIL			78
#define	SHFN_ctSysQueueLIFOWrite	79
#define	SHFN_LOKREC			80
#define	SHFN_GETCURP			81
#define	SHFN_EQLKEY			82
#define	SHFN_ctCLSNAM			83
#define	SHFN_SYSCFG			84
#define	SHFN_CTUSER			85
#define	SHFN_ctLOKDMP			86
#define	SHFN_ctSysQueueWrite		87
#define	SHFN_CLSFIL			88
#define	SHFN_CREIDXX8			89
#define	SHFN_AVLFILNUM			90
#define	SHFN_GTEKEY			91
#define	SHFN_ctGETHGH			92
#define	SHFN_ADDKEY			93
#define	SHFN_DELCHK			94
#define	SHFN_ctGetUserErrorCode		95
#define	SHFN_ctGetIsamErrorCode		96
#define	SHFN_ctGetIsamFileNbr		97
#define	SHFN_ctGetSystemErrorCode	98
#define	SHFN_UNRCTREE			99
#define SHFN_dh_free_sqlenv		100
#define SHFN_dh_sql_disconnect		101
#define SHFN_dh_tm_mark_abort		102
#define SHFN_dh_sqlselect		103
#define SHFN_dh_tm_end_trans		104
#define SHFN_dh_release_cursor		105
#define SHFN_dh_sqlexecute		106
#define SHFN_dh_set_cursorname		107
#define SHFN_dh_set_cursor		108
#define SHFN_dh_sql_chk_connection	109
#define SHFN_tpe_set_sqlda		110
#define SHFN_dh_set_ptrs		111
#define SHFN_dh_get_curdbhdl		112
#define SHFN_dh_get_curtmhdl		113
#define SHFN_dh_sqlconnect		114
#define SHFN_dh_alloc_sqlenv		115
#define	SHFN_RWTPREC			116
#define SHFN_SERIALNUM			117
#define SHFN_IDXENT			118
#define	SHFN_DELFIL			119
#define SHFN_ctDISTINCTest		120
#define SHFN_ctDISTINCTset		121
#define SHFN_ctdbAbort			122
#define SHFN_ctdbAddField		123
#define SHFN_ctdbAddIndex		124
#define SHFN_ctdbAddLocateCriteria	125
#define SHFN_ctdbAddSegment		126
#define SHFN_ctdbAllocDatabase		127
#define SHFN_ctdbAllocRecord		128
#define SHFN_ctdbAllocSession		129
#define SHFN_ctdbAllocTable		130
#define SHFN_ctdbAlterTable		131
#define SHFN_ctdbBegin			132
#define SHFN_ctdbClearRecord		133
#define SHFN_ctdbCloneTable		134
#define SHFN_ctdbCloseAll		135
#define SHFN_ctdbCloseTable		136
#define SHFN_ctdbCommit			137
#define SHFN_ctdbConnect		138
#define SHFN_ctdbCreateTable		139
#define SHFN_ctdbDeleteRecord		140
#define SHFN_ctdbDisconnect		141
#define SHFN_ctdbFilterRecord		142
#define SHFN_ctdbFindActiveTable	143
#define SHFN_ctdbFindKey		144
#define SHFN_ctdbFindRowid		145
#define SHFN_ctdbFirstRecord		146
#define SHFN_ctdbFreeDatabase		147
#define SHFN_ctdbFreeRecord		148
#define SHFN_ctdbFreeSession		149
#define SHFN_ctdbFreeTable		150
#define SHFN_ctdbGetBestIndex		151
#define SHFN_ctdbGetCndxIndex		152
#define SHFN_ctdbGetCndxIndexLength	153
#define SHFN_ctdbGetDatabaseName	154
#define SHFN_ctdbGetError		155
#define SHFN_ctdbGetField		156
#define SHFN_ctdbGetFieldAsBigint	157
#define SHFN_ctdbGetFieldAsString	158
#define SHFN_ctdbGetFieldByName		159
#define SHFN_ctdbGetFieldLength		160
#define SHFN_ctdbGetFieldName		161
#define SHFN_ctdbGetFieldNbr		162
#define SHFN_ctdbGetFieldNullFlag	163
#define SHFN_ctdbGetFieldNumber		164
#define SHFN_ctdbGetFieldNumberByName	165
#define SHFN_ctdbGetFieldType		166
#define SHFN_ctdbGetFilter		167
#define SHFN_ctdbGetIndex		168
#define SHFN_ctdbGetIndexDuplicateFlag	169
#define SHFN_ctdbGetIndexExtension	170
#define SHFN_ctdbGetIndexNbr		171
#define SHFN_ctdbGetIndexSegmentCount	172
#define SHFN_ctdbGetRecord		173
#define SHFN_ctdbGetRecordBuffer	174
#define SHFN_ctdbGetRecordCount		175
#define SHFN_ctdbGetRecordLength	176
#define SHFN_ctdbGetRecordLock		177
#define SHFN_ctdbGetRowid		178
#define SHFN_ctdbGetSegment		179
#define SHFN_ctdbGetSegmentField	180
#define SHFN_ctdbGetSegmentFieldName	181
#define SHFN_ctdbGetSegmentMode		182
#define SHFN_ctdbGetServerName		183
#define SHFN_ctdbGetTableExtension	184
#define SHFN_ctdbGetTableFieldCount	185
#define SHFN_ctdbGetTableIndexCount	186
#define SHFN_ctdbGetTableName		187
#define SHFN_ctdbGetTablePath		188
#define SHFN_ctdbGetUserLogonName	189
#define SHFN_ctdbGetUserPassword	190
#define SHFN_ctdbIsActiveDatabase	191
#define SHFN_ctdbIsEditedRecord		192
#define SHFN_ctdbIsFilteredRecord	193
#define SHFN_ctdbIsNewRecord		194
#define SHFN_ctdbIsNullField		195
#define SHFN_ctdbIsTransActive		196
#define SHFN_ctdbJumpToRecord		197
#define SHFN_ctdbLastRecord		198
#define SHFN_ctdbLockRecord		199
#define SHFN_ctdbLogon			200
#define SHFN_ctdbLogout			201
#define SHFN_ctdbNextRecord		202
#define SHFN_ctdbOpenTable		203
#define SHFN_ctdbPrevRecord		204
#define SHFN_ctdbReadRecord		205
#define SHFN_ctdbSetDefaultIndex	206
#define SHFN_ctdbSetDefaultIndexByName	207
#define SHFN_ctdbSetError		208
#define SHFN_ctdbSetFieldAsBigint	209
#define SHFN_ctdbSetFieldAsDate		210
#define SHFN_ctdbSetFieldAsDateTime	211
#define SHFN_ctdbSetFieldAsNumber	212
#define SHFN_ctdbSetFieldAsSigned	213
#define SHFN_ctdbSetFieldAsString	214
#define SHFN_ctdbSetFieldAsTime		215
#define SHFN_ctdbSetIndexCndxExpr	216
#define SHFN_ctdbSetIndexFilename	217
#define SHFN_ctdbSetIndexTemporaryFlag	218
#define SHFN_ctdbSetRecordCriteria	219
#define SHFN_ctdbStartDatabaseEngine	220
#define SHFN_ctdbStopDatabaseEngine	221
#define SHFN_ctdbUnlockRecord		222
#define SHFN_ctdbWriteRecord		223
#define SHFN_ctdbParseRecordExpr	224
#define SHFN_ctdbEvalExprAsSigned	225
#define SHFN_ctdbEvalExprAsDate		226
#define SHFN_ctdbEvalExprAsTime		227
#define SHFN_ctdbEvalExprAsDateTime	228
#define SHFN_ctdbEvalExprAsNumber	229
#define SHFN_ctdbEvalExprAsString	230
#define SHFN_ctdbSetDefDateType		231
#define SHFN_ctdbSetDefTimeType		232
#define SHFN_ctFILWCD			233
#define SHFN_ctdbAddUserDefFunc		234
#define SHFN__ctdb_alloc		235
#define SHFN__ctdb_free			236
#define SHFN__ctdbListAlloc		237
#define SHFN__ctdbListFree		238
#define SHFN__ctdbListCount		239
#define SHFN__ctdbListDeleteEx		240
#define SHFN__ctdbListItem		241
#define SHFN__ctdbListAdd		242
#define SHFN__ctdbSetFieldDefaultValue	243
#define SHFN__ctdbGetFieldDefaultValue	244
#define SHFN__ctdbDeleteTable		245
#define SHFN__ctdbFindTable		246
#define SHFN__ctdbFirstTable		247
#define SHFN__ctdbNextTable		248
#define SHFN__ctdbCreateDatabase	249
#define SHFN__ctdbSetRecordBuffer	250
#define SHFN__ctdbAddSegmentEx		251
#define SHFN__ctdbGetFieldPrecision	252
#define SHFN__ctdbGetFieldScale		253
#define SHFN__ctdbGetIndexEmptyChar	254
#define SHFN__ctdbGetIndexKeyType	255
#define SHFN__ctdbGetIndexNullFlag	256
#define SHFN__ctdbGetTableCreateMode	257
#define SHFN__ctdbSetFieldNullFlag	258
#define SHFN__ctdbSetFieldPrecision	259
#define SHFN__ctdbSetFieldScale		260
#define SHFN__ctdbSetIndexEmptyChar	261
#define SHFN__ctdbSetAutoCommit		262
#define SHFN__ctCreateSequence		263
#define SHFN__ctDeleteSequence		264
#define SHFN__ctOpenSequence		265
#define SHFN__ctGetCurrentSequenceValue	266
#define SHFN__ctSetCurrentSequenceValue	267
#define SHFN__ctGetNextSequenceValue	268
#define SHFN__ctdbGetFieldDataLength	269
#define SHFN__ctdbClearField		270
#define SHFN__ctdbGetFieldAsNumber	271
#define SHFN__ctdbGetFieldAsCurrency	272
#define SHFN__ctdbGetFieldAsUnsignedBigint 273
#define SHFN__ctdbGetFieldAsFloat	274
#define SHFN__ctdbGetFieldAsMoney	275
#define SHFN__ctdbGetFieldAsSigned	276
#define SHFN__ctdbGetFieldAsUnsigned	277
#define SHFN__ctdbGetFieldAsBool	278
#define SHFN__ctdbSetFieldAsCurrency	279
#define SHFN__ctdbSetFieldAsUnsignedBigint 280
#define SHFN__ctdbSetFieldAsFloat	281
#define SHFN__ctdbSetFieldAsMoney	282
#define SHFN__ctdbSetFieldAsUnsigned	283
#define SHFN__ctdbSetFieldAsBool	284
#define SHFN__ctdbAssignRecordBuffer	285
#define SHFN__ctdbListDelete	286
#define SHFN__ctdbSetTransactionMode	287
#define SHFN__ctdbIsActiveSession	288
#define SHFN__ctdbLocateRecord	289
#define SHFN__ctdbBigIntToString	290
#define SHFN_ctdbUpdateRecordCriteria	291
#define SHFN_ctdbSetFieldAsBinary	292
#define SHFN_ctdbGetFieldAsBinary	293
#define SHFN_ctdbFindRecord	294
#define SHFN_ctdbSetSavePoint	295
#define SHFN_ctdbRestoreSavePoint	296
#define SHFN_ctdbGetTableOpenMode	297
#define SHFN_ctdbCreateDir	298
#define SHFN_ctdbGetPathPrefix	299
#define SHFN_ctdbIsActiveTable	300
#define SHFN_ctdbGetIndexByName	301
#define SHFN_ctdbCreateSession	302
#define SHFN_ctdbAddTableXtd	303
#define SHFN_BATSETX		304
#define SHFN_ctdbGetCtreeOWNER	305
#define SHFN_ctdbSetCtreeOWNER	306
#define SHFN_GETRES		307
#define SHFN_ADDRES		308
#define SHFN_SETVARBYTS		309
/* <NEW_ENTRY>
#define	SHFN_ctNewAPIFunction		310
*/

typedef struct {
	pVOID	ctfnc[SHFN_TOTAL];
	NINT	cttyp;
} CTSHFNC, *pCTSHFNC;

#define ctAppMAXTHRDS	MXU2
extern NINT	pCURENV[ctAppMAXTHRDS];	/* Current environment for each thread. */
extern CTSHFNC	ctSHENV[2];		/* Data for each subsystem.		*/
extern NINT	ctAppTlsInit;		/* TLS index status.			*/

#ifdef ctPortWIN32
extern LONG		ctAppTlsIndex;	/* Thread local storage index.		*/
#else
extern pthread_key_t	ctAppTlsIndex;
#endif

/*
 * Set thread's c-tree environment to the specified environment.
 * Requires local variable CURENV of type NINT.
 */
#define ctAppSwitchCtreeEnv(newenv) {CURENV = pCURENV[ctAppGetTid()] = newenv;}

/*
 * c-tree Plus API function macros,
 * used to map API function calls to function pointer references.
 */

#define	ctThrdInit			(*(pctThrdInit_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdInit])
#define	ctThrdTerm			(*(pctThrdTerm_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdTerm])
#ifdef ctFeatMAXFILE32
#undef INTISAMX
#endif
#define	INTISAMX			(*(pINTISAMX_t)ctSHENV[CURENV].ctfnc[SHFN_INTISAMX])
#define	STPUSR				(*(pSTPUSR_t)ctSHENV[CURENV].ctfnc[SHFN_STPUSR])
#define	GETCTREE			(*(pGETCTREE_t)ctSHENV[CURENV].ctfnc[SHFN_GETCTREE])
#define	WCHCTREE			(*(pWCHCTREE_t)ctSHENV[CURENV].ctfnc[SHFN_WCHCTREE])
#define	OPNFIL				(*(pOPNFIL_t)ctSHENV[CURENV].ctfnc[SHFN_OPNFIL])
#ifdef ctPortWIN32
#define	tlsIndex			(*(ptlsIndex_t)ctSHENV[CURENV].ctfnc[SHFN_tlsIndex])
#else
#define	pthread_OWNER			(*(ppthread_OWNER_t)ctSHENV[CURENV].ctfnc[SHFN_pthread_OWNER])
#endif
#define	ctstatv				((pctstatv_t)ctSHENV[CURENV].ctfnc[SHFN_ctstatv])
#define	cttflg				(*(pcttflg_t)ctSHENV[CURENV].ctfnc[SHFN_cttflg])
#define	ctThrdSleep			(*(pctThrdSleep_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdSleep])
#define	ctSETEXITFNC			(*(pctSETEXITFNC_t)ctSHENV[CURENV].ctfnc[SHFN_ctSETEXITFNC])
#define	TRANEND				(*(pTRANEND_t)ctSHENV[CURENV].ctfnc[SHFN_TRANEND])
#define	TRANABTX			(*(pTRANABTX_t)ctSHENV[CURENV].ctfnc[SHFN_TRANABTX])
#define	RWTVREC				(*(pRWTVREC_t)ctSHENV[CURENV].ctfnc[SHFN_RWTVREC])
#define	RWTREC				(*(pRWTREC_t)ctSHENV[CURENV].ctfnc[SHFN_RWTREC])
#define	DELVREC				(*(pDELVREC_t)ctSHENV[CURENV].ctfnc[SHFN_DELVREC])
#define	EQLVREC				(*(pEQLVREC_t)ctSHENV[CURENV].ctfnc[SHFN_EQLVREC])
#define	DELREC				(*(pDELREC_t)ctSHENV[CURENV].ctfnc[SHFN_DELREC])
#define	EQLREC				(*(pEQLREC_t)ctSHENV[CURENV].ctfnc[SHFN_EQLREC])
#define	ADDVREC				(*(pADDVREC_t)ctSHENV[CURENV].ctfnc[SHFN_ADDVREC])
#undef mbfree
#define	mbfree				(*(pmbfree_t)ctSHENV[CURENV].ctfnc[SHFN_mbfree])
#define	REDIVREC			(*(pREDIVREC_t)ctSHENV[CURENV].ctfnc[SHFN_REDIVREC])
#define	ADDREC				(*(pADDREC_t)ctSHENV[CURENV].ctfnc[SHFN_ADDREC])
#define	LKISAM				(*(pLKISAM_t)ctSHENV[CURENV].ctfnc[SHFN_LKISAM])
#define	TRANBEG				(*(pTRANBEG_t)ctSHENV[CURENV].ctfnc[SHFN_TRANBEG])
#define	SWTCTREE			(*(pSWTCTREE_t)ctSHENV[CURENV].ctfnc[SHFN_SWTCTREE])
#define	REDIREC				(*(pREDIREC_t)ctSHENV[CURENV].ctfnc[SHFN_REDIREC])
#define	ctSETHGH			(*(pctSETHGH_t)ctSHENV[CURENV].ctfnc[SHFN_ctSETHGH])
#undef mballc
#define	mballc				(*(pmballc_t)ctSHENV[CURENV].ctfnc[SHFN_mballc])
#define	ctThrdExit			(*(pctThrdExit_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdExit])
#define	ctThrdMutexRel			(*(pctThrdMutexRel_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdMutexRel])
#define	ctThrdMutexGet			(*(pctThrdMutexGet_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdMutexGet])
#define	ctSysQueueRead			(*(pctSysQueueRead_t)ctSHENV[CURENV].ctfnc[SHFN_ctSysQueueRead])
#define	ctNotify			(*(pctNotify_t)ctSHENV[CURENV].ctfnc[SHFN_ctNotify])
#define	ctCallback			(*(pctCallback_t)ctSHENV[CURENV].ctfnc[SHFN_ctCallback])
#define	ctSysQueueOpen			(*(pctSysQueueOpen_t)ctSHENV[CURENV].ctfnc[SHFN_ctSysQueueOpen])
#define	GETFIL				(*(pGETFIL_t)ctSHENV[CURENV].ctfnc[SHFN_GETFIL])
#define	OPNRFIL				(*(pOPNRFIL_t)ctSHENV[CURENV].ctfnc[SHFN_OPNRFIL])
#define	REGCTREE			(*(pREGCTREE_t)ctSHENV[CURENV].ctfnc[SHFN_REGCTREE])
#define	ctThrdCreate			(*(pctThrdCreate_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdCreate])
#define	ctThrdMutexInit			(*(pctThrdMutexInit_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdMutexInit])
#define	ctThrdAttach			(*(pctThrdAttach_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdAttach])
#define	ctThrdDetach			(*(pctThrdDetach_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdDetach])
#define	TRANSAV				(*(pTRANSAV_t)ctSHENV[CURENV].ctfnc[SHFN_TRANSAV])
#define	TRANRST				(*(pTRANRST_t)ctSHENV[CURENV].ctfnc[SHFN_TRANRST])
#define	TRANABT				(*(pTRANABT_t)ctSHENV[CURENV].ctfnc[SHFN_TRANABT])
#define	ctThrdQueueWrite		(*(pctThrdQueueWrite_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdQueueWrite])
#define	GTEREC				(*(pGTEREC_t)ctSHENV[CURENV].ctfnc[SHFN_GTEREC])
#define	cttestfunc			(*(pcttestfunc_t)ctSHENV[CURENV].ctfnc[SHFN_cttestfunc])
#define	OPNRFILX			(*(pOPNRFILX_t)ctSHENV[CURENV].ctfnc[SHFN_OPNRFILX])
#define	PUTDODA				(*(pPUTDODA_t)ctSHENV[CURENV].ctfnc[SHFN_PUTDODA])
#define	CREIFILX			(*(pCREIFILX_t)ctSHENV[CURENV].ctfnc[SHFN_CREIFILX])
#define	DELIFIL				(*(pDELIFIL_t)ctSHENV[CURENV].ctfnc[SHFN_DELIFIL])
#define	OPNIFILX			(*(pOPNIFILX_t)ctSHENV[CURENV].ctfnc[SHFN_OPNIFILX])
#define	ctThrdQueueRead			(*(pctThrdQueueRead_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdQueueRead])
#define	ctThrdQueueMlen			(*(pctThrdQueueMlen_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdQueueMlen])
#define	ctThrdMutexCls			(*(pctThrdMutexCls_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdMutexCls])
#define	ctThrdQueueOpen			(*(pctThrdQueueOpen_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdQueueOpen])
#define	ctThrdBlockInit			(*(pctThrdBlockInit_t)ctSHENV[CURENV].ctfnc[SHFN_ctThrdBlockInit])
#define	FRSREC				(*(pFRSREC_t)ctSHENV[CURENV].ctfnc[SHFN_FRSREC])
#define	CLRFIL				(*(pCLRFIL_t)ctSHENV[CURENV].ctfnc[SHFN_CLRFIL])
#define	GETIFIL				(*(pGETIFIL_t)ctSHENV[CURENV].ctfnc[SHFN_GETIFIL])
#define	GETDODA				(*(pGETDODA_t)ctSHENV[CURENV].ctfnc[SHFN_GETDODA])
#define	GETNAM				(*(pGETNAM_t)ctSHENV[CURENV].ctfnc[SHFN_GETNAM])
#define	GETXCREBLK			(*(pGETXCREBLK_t)ctSHENV[CURENV].ctfnc[SHFN_GETXCREBLK])
#define	CREIFILX8			(*(pCREIFILX8_t)ctSHENV[CURENV].ctfnc[SHFN_CREIFILX8])
#define	FRSVREC				(*(pFRSVREC_t)ctSHENV[CURENV].ctfnc[SHFN_FRSVREC])
#define	NXTVREC				(*(pNXTVREC_t)ctSHENV[CURENV].ctfnc[SHFN_NXTVREC])
#define	NXTREC				(*(pNXTREC_t)ctSHENV[CURENV].ctfnc[SHFN_NXTREC])
#define	SETOPS				(*(pSETOPS_t)ctSHENV[CURENV].ctfnc[SHFN_SETOPS])
#define	REDVREC				(*(pREDVREC_t)ctSHENV[CURENV].ctfnc[SHFN_REDVREC])
#define	CLISAM				(*(pCLISAM_t)ctSHENV[CURENV].ctfnc[SHFN_CLISAM])
#define	GTEVREC				(*(pGTEVREC_t)ctSHENV[CURENV].ctfnc[SHFN_GTEVREC])
#define	GETCURK				(*(pGETCURK_t)ctSHENV[CURENV].ctfnc[SHFN_GETCURK])
#define	SETNODE				(*(pSETNODE_t)ctSHENV[CURENV].ctfnc[SHFN_SETNODE])
#define	BATSET				(*(pBATSET_t)ctSHENV[CURENV].ctfnc[SHFN_BATSET])
#define	SECURITY			(*(pSECURITY_t)ctSHENV[CURENV].ctfnc[SHFN_SECURITY])
#define	CLIFIL				(*(pCLIFIL_t)ctSHENV[CURENV].ctfnc[SHFN_CLIFIL])
#define	ctSysQueueLIFOWrite		(*(pctSysQueueLIFOWrite_t)ctSHENV[CURENV].ctfnc[SHFN_ctSysQueueLIFOWrite])
#define	LOKREC				(*(pLOKREC_t)ctSHENV[CURENV].ctfnc[SHFN_LOKREC])
#define	GETCURP				(*(pGETCURP_t)ctSHENV[CURENV].ctfnc[SHFN_GETCURP])
#define	EQLKEY				(*(pEQLKEY_t)ctSHENV[CURENV].ctfnc[SHFN_EQLKEY])
#define	ctCLSNAM			(*(pctCLSNAM_t)ctSHENV[CURENV].ctfnc[SHFN_ctCLSNAM])
#define	SYSCFG				(*(pSYSCFG_t)ctSHENV[CURENV].ctfnc[SHFN_SYSCFG])
#define	CTUSER				(*(pCTUSER_t)ctSHENV[CURENV].ctfnc[SHFN_CTUSER])
#define	ctLOKDMP			(*(pctLOKDMP_t)ctSHENV[CURENV].ctfnc[SHFN_ctLOKDMP])
#define	ctSysQueueWrite			(*(pctSysQueueWrite_t)ctSHENV[CURENV].ctfnc[SHFN_ctSysQueueWrite])
#define	CLSFIL				(*(pCLSFIL_t)ctSHENV[CURENV].ctfnc[SHFN_CLSFIL])
#define	CREIDXX8			(*(pCREIDXX8_t)ctSHENV[CURENV].ctfnc[SHFN_CREIDXX8])
#define	AVLFILNUM			(*(pAVLFILNUM_t)ctSHENV[CURENV].ctfnc[SHFN_AVLFILNUM])
#define	GTEKEY				(*(pGTEKEY_t)ctSHENV[CURENV].ctfnc[SHFN_GTEKEY])
#define	ctGETHGH			(*(pctGETHGH_t)ctSHENV[CURENV].ctfnc[SHFN_ctGETHGH])
#define	ADDKEY				(*(pADDKEY_t)ctSHENV[CURENV].ctfnc[SHFN_ADDKEY])
#define	DELCHK				(*(pDELCHK_t)ctSHENV[CURENV].ctfnc[SHFN_DELCHK])
#define	ctGetUserErrorCode		(*(pctGetUserErrorCode_t)ctSHENV[CURENV].ctfnc[SHFN_ctGetUserErrorCode])
#define	ctGetIsamErrorCode		(*(pctGetIsamErrorCode_t)ctSHENV[CURENV].ctfnc[SHFN_ctGetIsamErrorCode])
#define	ctGetIsamFileNbr		(*(pctGetIsamFileNbr_t)ctSHENV[CURENV].ctfnc[SHFN_ctGetIsamFileNbr])
#define	ctGetSystemErrorCode		(*(pctGetSystemErrorCode_t)ctSHENV[CURENV].ctfnc[SHFN_ctGetSystemErrorCode])
#define	UNRCTREE			(*(pUNRCTREE_t)ctSHENV[CURENV].ctfnc[SHFN_UNRCTREE])
#ifdef ctAppESQL
#define	dh_free_sqlenv			(*(pdh_free_sqlenv_t)ctSHENV[CURENV].ctfnc[SHFN_dh_free_sqlenv])
#define	dh_sql_disconnect		(*(pdh_sql_disconnect_t)ctSHENV[CURENV].ctfnc[SHFN_dh_sql_disconnect])
#define	dh_tm_mark_abort		(*(pdh_tm_mark_abort_t)ctSHENV[CURENV].ctfnc[SHFN_dh_tm_mark_abort])
#define	dh_sqlselect			(*(pdh_sqlselect_t)ctSHENV[CURENV].ctfnc[SHFN_dh_sqlselect])
#define	dh_tm_end_trans			(*(pdh_tm_end_trans_t)ctSHENV[CURENV].ctfnc[SHFN_dh_tm_end_trans])
#define	dh_release_cursor		(*(pdh_release_cursor_t)ctSHENV[CURENV].ctfnc[SHFN_dh_release_cursor])
#define dh_sqlexecute			(*(pdh_sqlexecute_t)ctSHENV[CURENV].ctfnc[SHFN_dh_sqlexecute])
#define	dh_set_cursorname		(*(pdh_set_cursorname_t)ctSHENV[CURENV].ctfnc[SHFN_dh_set_cursorname])
#define dh_set_cursor			(*(pdh_set_cursor_t)ctSHENV[CURENV].ctfnc[SHFN_dh_set_cursor])
#define dh_sql_chk_connection		(*(pdh_sql_chk_connection_t)ctSHENV[CURENV].ctfnc[SHFN_dh_sql_chk_connection])
#define tpe_set_sqlda			(*(ptpe_set_sqlda_t)ctSHENV[CURENV].ctfnc[SHFN_tpe_set_sqlda])
#define dh_set_ptrs			(*(pdh_set_ptrs_t)ctSHENV[CURENV].ctfnc[SHFN_dh_set_ptrs])
#define dh_get_curdbhdl			(*(pdh_get_curdbhdl_t)ctSHENV[CURENV].ctfnc[SHFN_dh_get_curdbhdl])
#define dh_get_curtmhdl			(*(pdh_get_curtmhdl_t)ctSHENV[CURENV].ctfnc[SHFN_dh_get_curtmhdl])
#define dh_sqlconnect			(*(pdh_sqlconnect_t)ctSHENV[CURENV].ctfnc[SHFN_dh_sqlconnect])
#define dh_alloc_sqlenv			(*(pdh_alloc_sqlenv_t)ctSHENV[CURENV].ctfnc[SHFN_dh_alloc_sqlenv])
#endif /* ctAppESQL */
#define	RWTPREC				(*(pRWTPREC_t)ctSHENV[CURENV].ctfnc[SHFN_RWTPREC])
#define SERIALNUM			(*(pSERIALNUM_t)ctSHENV[CURENV].ctfnc[SHFN_SERIALNUM])
#define IDXENT				(*(pIDXENT_t)ctSHENV[CURENV].ctfnc[SHFN_IDXENT])
#define DELFIL				(*(pDELFIL_t)ctSHENV[CURENV].ctfnc[SHFN_DELFIL])
#define ctDISTINCTest			(*(pctDISTINCTest_t)ctSHENV[CURENV].ctfnc[SHFN_ctDISTINCTest])
#define ctDISTINCTset			(*(pctDISTINCTset_t)ctSHENV[CURENV].ctfnc[SHFN_ctDISTINCTset])
#define ctdbAbort			(*(pctdbAbort_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAbort])
#define ctdbAddField			(*(pctdbAddField_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAddField])
#define ctdbAddIndex			(*(pctdbAddIndex_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAddIndex])
#define ctdbAddLocateCriteria		(*(pctdbAddLocateCriteria_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAddLocateCriteria])
#define ctdbAddSegment			(*(pctdbAddSegment_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAddSegment])
#define ctdbAllocDatabase		(*(pctdbAllocDatabase_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAllocDatabase])
#define ctdbAllocRecord			(*(pctdbAllocRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAllocRecord])
#define ctdbAllocSession		(*(pctdbAllocSession_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAllocSession])
#define ctdbAllocTable			(*(pctdbAllocTable_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAllocTable])
#define ctdbAlterTable			(*(pctdbAlterTable_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAlterTable])
#define ctdbBegin			(*(pctdbBegin_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbBegin])
#define ctdbClearRecord			(*(pctdbClearRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbClearRecord])
#define ctdbCloneTable			(*(pctdbCloneTable_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbCloneTable])
#define ctdbCloseAll			(*(pctdbCloseAll_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbCloseAll])
#define ctdbCloseTable			(*(pctdbCloseTable_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbCloseTable])
#define ctdbCommit			(*(pctdbCommit_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbCommit])
#define ctdbConnect			(*(pctdbConnect_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbConnect])
#define ctdbCreateTable			(*(pctdbCreateTable_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbCreateTable])
#define ctdbDeleteRecord		(*(pctdbDeleteRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbDeleteRecord])
#define ctdbDisconnect			(*(pctdbDisconnect_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbDisconnect])
#define ctdbFilterRecord		(*(pctdbFilterRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFilterRecord])
#define ctdbFindActiveTable		(*(pctdbFindActiveTable_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFindActiveTable])
#define ctdbFindKey			(*(pctdbFindKey_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFindKey])
#define ctdbFindRowid			(*(pctdbFindRowid_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFindRowid])
#define ctdbFirstRecord			(*(pctdbFirstRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFirstRecord])
#define ctdbFreeDatabase		(*(pctdbFreeDatabase_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFreeDatabase])
#define ctdbFreeRecord			(*(pctdbFreeRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFreeRecord])
#define ctdbFreeSession			(*(pctdbFreeSession_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFreeSession])
#define ctdbFreeTable			(*(pctdbFreeTable_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFreeTable])
#define ctdbGetBestIndex		(*(pctdbGetBestIndex_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetBestIndex])
#define ctdbGetCndxIndex		(*(pctdbGetCndxIndex_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetCndxIndex])
#define ctdbGetCndxIndexLength		(*(pctdbGetCndxIndexLength_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetCndxIndexLength])
#define ctdbGetDatabaseName		(*(pctdbGetDatabaseName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetDatabaseName])
#define ctdbGetError			(*(pctdbGetError_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetError])
#define ctdbGetField			(*(pctdbGetField_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetField])
#define ctdbGetFieldAsBigint		(*(pctdbGetFieldAsBigint_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldAsBigint])
#define ctdbGetFieldAsString		(*(pctdbGetFieldAsString_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldAsString])
#define ctdbGetFieldAsBinary		(*(pctdbGetFieldAsBinary_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldAsBinary])
#define ctdbGetFieldByName		(*(pctdbGetFieldByName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldByName])
#define ctdbGetFieldLength		(*(pctdbGetFieldLength_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldLength])
#define ctdbGetFieldName		(*(pctdbGetFieldName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldName])
#define ctdbGetFieldNbr			(*(pctdbGetFieldNbr_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldNbr])
#define ctdbGetFieldNullFlag		(*(pctdbGetFieldNullFlag_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldNullFlag])
#define ctdbGetFieldNumber		(*(pctdbGetFieldNumber_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldNumber])
#define ctdbGetFieldNumberByName	(*(pctdbGetFieldNumberByName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldNumberByName])
#define ctdbGetFieldType		(*(pctdbGetFieldType_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFieldType])
#define ctdbGetFilter			(*(pctdbGetFilter_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetFilter])
#define ctdbGetIndex			(*(pctdbGetIndex_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetIndex])
#define ctdbGetIndexDuplicateFlag	(*(pctdbGetIndexDuplicateFlag_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetIndexDuplicateFlag])
#define ctdbGetIndexExtension		(*(pctdbGetIndexExtension_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetIndexExtension])
#define ctdbGetIndexNbr			(*(pctdbGetIndexNbr_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetIndexNbr])
#define ctdbGetIndexSegmentCount	(*(pctdbGetIndexSegmentCount_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetIndexSegmentCount])
#define ctdbGetRecord			(*(pctdbGetRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetRecord])
#define ctdbGetRecordBuffer		(*(pctdbGetRecordBuffer_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetRecordBuffer])
#define ctdbGetRecordCount		(*(pctdbGetRecordCount_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetRecordCount])
#define ctdbGetRecordLength		(*(pctdbGetRecordLength_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetRecordLength])
#define ctdbGetRecordLock		(*(pctdbGetRecordLock_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetRecordLock])
#define ctdbGetRowid			(*(pctdbGetRowid_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetRowid])
#define ctdbGetSegment			(*(pctdbGetSegment_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetSegment])
#define ctdbGetSegmentField		(*(pctdbGetSegmentField_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetSegmentField])
#define ctdbGetSegmentFieldName		(*(pctdbGetSegmentFieldName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetSegmentFieldName])
#define ctdbGetSegmentMode		(*(pctdbGetSegmentMode_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetSegmentMode])
#define ctdbGetServerName		(*(pctdbGetServerName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetServerName])
#define ctdbGetTableExtension		(*(pctdbGetTableExtension_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetTableExtension])
#define ctdbGetTableFieldCount		(*(pctdbGetTableFieldCount_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetTableFieldCount])
#define ctdbGetTableIndexCount		(*(pctdbGetTableIndexCount_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetTableIndexCount])
#define ctdbGetTableName		(*(pctdbGetTableName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetTableName])
#define ctdbGetTablePath		(*(pctdbGetTablePath_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetTablePath])
#define ctdbGetUserLogonName		(*(pctdbGetUserLogonName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetUserLogonName])
#define ctdbGetUserPassword		(*(pctdbGetUserPassword_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetUserPassword])
#define ctdbIsActiveDatabase		(*(pctdbIsActiveDatabase_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbIsActiveDatabase])
#define ctdbIsEditedRecord		(*(pctdbIsEditedRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbIsEditedRecord])
#define ctdbIsFilteredRecord		(*(pctdbIsFilteredRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbIsFilteredRecord])
#define ctdbIsNewRecord			(*(pctdbIsNewRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbIsNewRecord])
#define ctdbIsNullField			(*(pctdbIsNullField_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbIsNullField])
#define ctdbIsTransActive		(*(pctdbIsTransActive_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbIsTransActive])
#define ctdbJumpToRecord		(*(pctdbJumpToRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbJumpToRecord])
#define ctdbLastRecord			(*(pctdbLastRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbLastRecord])
#define ctdbLockRecord			(*(pctdbLockRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbLockRecord])
#define ctdbLogon			(*(pctdbLogon_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbLogon])
#define ctdbLogout			(*(pctdbLogout_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbLogout])
#define ctdbNextRecord			(*(pctdbNextRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbNextRecord])
#define ctdbOpenTable			(*(pctdbOpenTable_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbOpenTable])
#define ctdbPrevRecord			(*(pctdbPrevRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbPrevRecord])
#define ctdbReadRecord			(*(pctdbReadRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbReadRecord])
#define ctdbSetDefaultIndex		(*(pctdbSetDefaultIndex_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetDefaultIndex])
#define ctdbSetDefaultIndexByName	(*(pctdbSetDefaultIndexByName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetDefaultIndexByName])
#define ctdbSetError			(*(pctdbSetError_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetError])
#define ctdbSetFieldAsBigint		(*(pctdbSetFieldAsBigint_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetFieldAsBigint])
#define ctdbSetFieldAsDate		(*(pctdbSetFieldAsDate_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetFieldAsDate])
#define ctdbSetFieldAsDateTime		(*(pctdbSetFieldAsDateTime_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetFieldAsDateTime])
#define ctdbSetFieldAsNumber		(*(pctdbSetFieldAsNumber_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetFieldAsNumber])
#define ctdbSetFieldAsSigned		(*(pctdbSetFieldAsSigned_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetFieldAsSigned])
#define ctdbSetFieldAsString		(*(pctdbSetFieldAsString_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetFieldAsString])
#define ctdbSetFieldAsBinary		(*(pctdbSetFieldAsBinary_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetFieldAsBinary])
#define ctdbSetFieldAsTime		(*(pctdbSetFieldAsTime_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetFieldAsTime])
#define ctdbSetIndexCndxExpr		(*(pctdbSetIndexCndxExpr_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetIndexCndxExpr])
#define ctdbSetIndexFilename		(*(pctdbSetIndexFilename_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetIndexFilename])
#define ctdbSetIndexTemporaryFlag	(*(pctdbSetIndexTemporaryFlag_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetIndexTemporaryFlag])
#define ctdbSetRecordCriteria		(*(pctdbSetRecordCriteria_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetRecordCriteria])
#define ctdbUpdateRecordCriteria		(*(pctdbUpdateRecordCriteria_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbUpdateRecordCriteria])
#define ctdbStartDatabaseEngine		(*(pctdbStartDatabaseEngine_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbStartDatabaseEngine])
#define ctdbStopDatabaseEngine		(*(pctdbStopDatabaseEngine_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbStopDatabaseEngine])
#define ctdbUnlockRecord		(*(pctdbUnlockRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbUnlockRecord])
#define ctdbWriteRecord			(*(pctdbWriteRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbWriteRecord])
#define ctdbParseRecordExpr		(*(pctdbParseRecordExpr_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbParseRecordExpr])
#define ctdbEvalExprAsSigned		(*(pctdbEvalExprAsSigned_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbEvalExprAsSigned])
#define ctdbEvalExprAsDate		(*(pctdbEvalExprAsDate_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbEvalExprAsDate])
#define ctdbEvalExprAsTime		(*(pctdbEvalExprAsTime_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbEvalExprAsTime])
#define ctdbEvalExprAsDateTime		(*(pctdbEvalExprAsDateTime_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbEvalExprAsDateTime])
#define ctdbEvalExprAsNumber		(*(pctdbEvalExprAsNumber_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbEvalExprAsNumber])
#define ctdbEvalExprAsString		(*(pctdbEvalExprAsString_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbEvalExprAsString])
#define ctdbSetDefDateType		(*(pctdbSetDefDateType_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetDefDateType])
#define ctdbSetDefTimeType		(*(pctdbSetDefTimeType_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetDefTimeType])
#define ctFILWCD			(*(pctFILWCD_t)ctSHENV[CURENV].ctfnc[SHFN_ctFILWCD])
#define ctdbAddUserDefFunc		(*(pctdbAddUserDefFunc_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAddUserDefFunc])
#define _ctdb_alloc			(*(p_ctdb_allocFunc_t)ctSHENV[CURENV].ctfnc[SHFN__ctdb_alloc])
#define _ctdb_free			(*(p_ctdb_freeFunc_t)ctSHENV[CURENV].ctfnc[SHFN__ctdb_free])
#define _ctdbListAlloc			(*(p_ctdbListAllocFunc_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbListAlloc])
#define _ctdbListFree			(*(p_ctdbListFreeFunc_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbListFree])
#define _ctdbListCount			(*(p_ctdbListCountFunc_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbListCount])
#define _ctdbListDeleteEx		(*(p_ctdbListDeleteExFunc_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbListDeleteEx])
#define _ctdbListItem			(*(p_ctdbListItemFunc_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbListItem])
#define _ctdbListAdd			(*(p_ctdbListAddFunc_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbListAdd])
#define ctdbSetFieldDefaultValue	(*(p_ctdbSetFieldDefaultValue_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldDefaultValue])
#define ctdbGetFieldDefaultValue	(*(p_ctdbGetFieldDefaultValue_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldDefaultValue])
#define ctdbDeleteTable			(*(p_ctdbDeleteTable_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbDeleteTable])
#define ctdbFindTable			(*(p_ctdbFindTable_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbFindTable])
#define ctdbFirstTable			(*(p_ctdbFirstTable_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbFirstTable])
#define ctdbNextTable			(*(p_ctdbNextTable_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbNextTable])
#define ctdbCreateDatabase		(*(p_ctdbCreateDatabase_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbCreateDatabase])
#define ctdbSetRecordBuffer		(*(p_ctdbSetRecordBuffer_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetRecordBuffer])
#define ctdbAddSegmentEx		(*(p_ctdbAddSegmentEx_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetRecordBuffer])
#define ctdbGetFieldPrecision		(*(p_ctdbGetFieldPrecision_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetRecordBuffer])
#define ctdbGetFieldScale		(*(p_ctdbGetFieldScale_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldScale])
#define ctdbGetIndexEmptyChar		(*(p_ctdbGetIndexEmptyChar_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetIndexEmptyChar])
#define ctdbGetIndexKeyType		(*(p_ctdbGetIndexKeyType_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetIndexKeyType])
#define ctdbGetIndexNullFlag		(*(p_ctdbGetIndexNullFlag_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetIndexNullFlag])
#define ctdbGetTableCreateMode		(*(p_ctdbGetTableCreateMode_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetTableCreateMode])
#define ctdbSetFieldNullFlag		(*(p_ctdbSetFieldNullFlag_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldNullFlag])
#define ctdbSetFieldPrecision		(*(p_ctdbSetFieldPrecision_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldPrecision])
#define ctdbSetFieldScale		(*(p_ctdbSetFieldScale_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldScale])
#define ctdbSetIndexEmptyChar		(*(p_ctdbSetIndexEmptyChar_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetIndexEmptyChar])
#define ctdbSetAutoCommit		(*(p_ctdbSetAutoCommit_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetAutoCommit])
#define ctCreateSequence		(*(p_ctCreateSequence_t)ctSHENV[CURENV].ctfnc[SHFN__ctCreateSequence])
#define ctDeleteSequence		(*(p_ctDeleteSequence_t)ctSHENV[CURENV].ctfnc[SHFN__ctDeleteSequence])
#define ctOpenSequence			(*(p_ctOpenSequence_t)ctSHENV[CURENV].ctfnc[SHFN__ctOpenSequence])
#define ctGetCurrentSequenceValue	(*(p_ctGetCurrentSequenceValue_t)ctSHENV[CURENV].ctfnc[SHFN__ctGetCurrentSequenceValue])
#define ctSetCurrentSequenceValue	(*(p_ctSetCurrentSequenceValue_t)ctSHENV[CURENV].ctfnc[SHFN__ctSetCurrentSequenceValue])
#define ctGetNextSequenceValue		(*(p_ctGetNextSequenceValue_t)ctSHENV[CURENV].ctfnc[SHFN__ctGetNextSequenceValue])
#define ctdbGetFieldDataLength		(*(p_ctdbGetFieldDataLength_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldDataLength])
#define ctdbClearField			(*(p_ctdbClearField_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbClearField])
#define ctdbGetFieldAsNumber		(*(p_ctdbGetFieldAsNumber_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldAsNumber])
#define ctdbGetFieldAsCurrency		(*(p_ctdbGetFieldAsCurrency_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbClearField])
#define ctdbGetFieldAsUnsignedBigint	(*(p_ctdbGetFieldAsUnsignedBigint_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldAsUnsignedBigint])
#define ctdbGetFieldAsFloat		(*(p_ctdbGetFieldAsFloat_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldAsFloat])
#define ctdbGetFieldAsMoney		(*(p_ctdbGetFieldAsMoney_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldAsMoney])
#define ctdbGetFieldAsSigned		(*(p_ctdbGetFieldAsSigned_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldAsSigned])
#define ctdbGetFieldAsUnsigned		(*(p_ctdbGetFieldAsUnsigned_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldAsUnsigned])
#define ctdbGetFieldAsBool		(*(p_ctdbGetFieldAsBool_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbGetFieldAsBool])
#define ctdbSetFieldAsCurrency		(*(p_ctdbSetFieldAsCurrency_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldAsCurrency])
#define ctdbSetFieldAsUnsignedBigint	(*(p_ctdbSetFieldAsUnsignedBigint_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldAsUnsignedBigint])
#define ctdbSetFieldAsFloat		(*(p_ctdbSetFieldAsFloat_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldAsFloat])
#define ctdbSetFieldAsMoney		(*(p_ctdbSetFieldAsMoney_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldAsMoney])
#define ctdbSetFieldAsUnsigned		(*(p_ctdbSetFieldAsUnsigned_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldAsUnsigned])
#define ctdbSetFieldAsBool		(*(p_ctdbSetFieldAsBool_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetFieldAsBool])
#define ctdbAssignRecordBuffer		(*(p_ctdbAssignRecordBuffer_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbAssignRecordBuffer])
#define _ctdbListDelete		(*(p_ctdbListDeleteFunc_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbListDelete])
#define ctdbSetTransactionMode		(*(p_ctdbSetTransactionMode_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbSetTransactionMode])
#define ctdbIsActiveSession		(*(p_ctdbIsActiveSession_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbIsActiveSession])
#define ctdbLocateRecord		(*(p_ctdbLocateRecord_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbLocateRecord])
#define ctdbBigIntToString		(*(p_ctdbBigIntToString_t)ctSHENV[CURENV].ctfnc[SHFN__ctdbBigIntToString])
#define ctdbFindRecord		(*(pctdbFindRecord_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbFindRecord])
#define ctdbSetSavePoint		(*(pctdbSetSavePoint_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetSavePoint])
#define ctdbRestoreSavePoint		(*(pctdbRestoreSavePoint_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbRestoreSavePoint])
#define ctdbGetTableOpenMode		(*(pctdbGetTableOpenMode_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetTableOpenMode])
#define ctdbCreateDir		(*(pctdbCreateDir_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbCreateDir])
#define ctdbGetPathPrefix		(*(pctdbGetPathPrefix_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetPathPrefix])
#define ctdbIsActiveTable		(*(pctdbIsActiveTable_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbIsActiveTable])
#define ctdbGetIndexByName		(*(pctdbGetIndexByName_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetIndexByName])
#define ctdbCreateSession		(*(pctdbCreateSession_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbCreateSession])
#define ctdbAddTableXtd		(*(pctdbAddTableXtd_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbAddTableXtd])
#define BATSETX				(*(pBATSETX_t)ctSHENV[CURENV].ctfnc[SHFN_BATSETX])
#define ctdbGetCtreeOWNER		(*(pctdbGetCtreeOWNER_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbGetCtreeOWNER])
#define ctdbSetCtreeOWNER		(*(pctdbSetCtreeOWNER_t)ctSHENV[CURENV].ctfnc[SHFN_ctdbSetCtreeOWNER])
#define GETRES			(*(pGETRES_t)ctSHENV[CURENV].ctfnc[SHFN_GETRES])
#define ADDRES			(*(pADDRES_t)ctSHENV[CURENV].ctfnc[SHFN_ADDRES])
#define SETVARBYTS		(*(pSETVARBYTS_t)ctSHENV[CURENV].ctfnc[SHFN_SETVARBYTS])
/* <NEW_ENTRY>
#define	ctNewAPIFunction		(*(pctNewAPIFunction_t)ctSHENV[CURENV].ctfnc[SHFN_ctNewAPIFunction])
*/

extern VOID		*bndhnd;
extern VOID		*mtchnd;

#define ctAPPERR_LIBLOAD	1
#define ctAPPERR_FNCLOAD	2

#define CTTYP_SRV		0 /* c-tree Server subsystem id.                */
#define CTTYP_MTC		1 /* c-tree multi-threaded client subsystem id. */

/*
 * c-tree Plus API function names,
 * used to retrieve function addresses from c-tree DLL or shared library.
 */

extern pTEXT	ctshfnam[SHFN_TOTAL][2];

extern NINT	sigflg;

#ifndef CTCLSV_MULTI_MOD

NINT	pCURENV[ctAppMAXTHRDS];		/* Current environment for each thread. */
CTSHFNC	ctSHENV[2];			/* Data for each subsystem.		*/
NINT	ctAppTlsInit = 0;		/* TLS index status.			*/

#ifdef ctPortWIN32
LONG		ctAppTlsIndex;		/* Thread local storage index.		*/
#else
pthread_key_t	ctAppTlsIndex;
#endif

VOID		*bndhnd;
VOID		*mtchnd;

pTEXT ctshfnam[SHFN_TOTAL][2] = {
	/* Server functions */	/* Client functions */
	"ctThrdInit",			"ctThrdInit",
	"ctThrdTerm",			"ctThrdTerm",
#ifdef ctFeatMAXFILE32
	"INTISAMX4",			"INTISAMX4",
#else
	"INTISAMX",			"INTISAMX",
#endif
	"STPUSR",			"STPUSR",
	"GETCTREE",			"GETCTREE",
	"WCHCTREE",			"WCHCTREE",
	"OPNFIL",			"OPNFIL",
#ifdef ctPortWIN32
	"tlsIndex",			";tlsIndex",
#else
	"pthread_OWNER",		";pthread_OWNER",
#endif
	"ctstatv",			";ctstatv",
	"cttflg",			";cttflg",
	"ctThrdSleep",			"ctThrdSleep",
	"ctSETEXITFNC",			"ctSETEXITFNC",
	"TRANEND",			"TRANEND",
	"TRANABTX",			"TRANABTX",
	"RWTVREC",			"RWTVREC",
	"RWTREC",			"RWTREC",
	"DELVREC",			"DELVREC",
	"EQLVREC",			"EQLVREC",
	"DELREC",			"DELREC",
	"EQLREC",			"EQLREC",
	"ADDVREC",			"ADDVREC",
	"mbfree",			"mbfree",
	"REDIVREC",			"REDIVREC",
	"ADDREC",			"ADDREC",
	"LKISAM",			"LKISAM",
	"TRANBEG",			"TRANBEG",
	"SWTCTREE",			"SWTCTREE",
	"REDIREC",			"REDIREC",
	"ctSETHGH",			"ctSETHGH",
	"mballc",			"mballc",
	"ctThrdExit",			"ctThrdExit",
	"ctThrdMutexRel",		"ctThrdMutexRel",
	"ctThrdMutexGet",		"ctThrdMutexGet",
	"ctSysQueueRead",		"ctSysQueueRead",
	"ctNotify",			"ctNotify",
	"ctCallback",			";ctCallback",
	"ctSysQueueOpen",		"ctSysQueueOpen",
	"GETFIL",			"GETFIL",
	"OPNRFIL",			"OPNRFIL",
	"REGCTREE",			"REGCTREE",
	"ctThrdCreate",			"ctThrdCreate",
	"ctThrdMutexInit",		"ctThrdMutexInit",
	"ctThrdAttach",			"ctThrdAttach",
	"ctThrdDetach",			"ctThrdDetach",
	"TRANSAV",			"TRANSAV",
	"TRANRST",			"TRANRST",
	"TRANABT",			"TRANABT",
	"ctThrdQueueWrite",		"ctThrdQueueWrite",
	"GTEREC",			"GTEREC",
	"cttestfunc",			"cttestfunc",
	"OPNRFILX",			"OPNRFILX",
	"PUTDODA",			"PUTDODA",
	"CREIFILX",			"CREIFILX",
	"DELIFIL",			"DELIFIL",
	"OPNIFILX",			"OPNIFILX",
	"ctThrdQueueRead",		"ctThrdQueueRead",
	"ctThrdQueueMlen",		"ctThrdQueueMlen",
	"ctThrdMutexCls",		"ctThrdMutexCls",
	"ctThrdQueueOpen",		"ctThrdQueueOpen",
	"ctThrdBlockInit",		"ctThrdBlockInit",
	"FRSREC",			"FRSREC",
	"CLRFIL",			"CLRFIL",
	"GETIFIL",			"GETIFIL",
	"GETDODA",			"GETDODA",
	"GETNAM",			"GETNAM",
	"GETXCREBLK",			"GETXCREBLK",
	"CREIFILX8",			"CREIFILX8",
	"FRSVREC",			"FRSVREC",
	"NXTVREC",			"NXTVREC",
	"NXTREC",			"NXTREC",
	"SETOPS",			"SETOPS",
	"REDVREC",			"REDVREC",
	"CLISAM",			"CLISAM",
	"GTEVREC",			"GTEVREC",
	"GETCURK",			"GETCURK",
	"SETNODE",			"SETNODE",
	"BATSET",			"BATSET",
	"SECURITY",			"SECURITY",
	"CLIFIL",			"CLIFIL",
	"ctSysQueueLIFOWrite",		"ctSysQueueLIFOWrite",
	"LOKREC",			"LOKREC",
	"GETCURP",			"GETCURP",
	"EQLKEY",			"EQLKEY",
	"ctCLSNAM",			"ctCLSNAM",
	"SYSCFG",			"SYSCFG",
	"CTUSER",			"CTUSER",
	"ctLOKDMP",			"ctLOKDMP",
	"ctSysQueueWrite",		"ctSysQueueWrite",
	"CLSFIL",			"CLSFIL",
	"CREIDXX8",			"CREIDXX8",
	"AVLFILNUM",			"AVLFILNUM",
	"GTEKEY",			"GTEKEY",
	"ctGETHGH",			"ctGETHGH",
	"ADDKEY",			"ADDKEY",
	"DELCHK",			"DELCHK",
	"ctGetUserErrorCode",		";ctGetUserErrorCode",
	"ctGetIsamErrorCode",		";ctGetIsamErrorCode",
	"ctGetIsamFileNbr",		";ctGetIsamFileNbr",
	"ctGetSystemErrorCode",		";ctGetSystemErrorCode",
	"UNRCTREE",			"UNRCTREE",
	/* SQL functions */
	ctSQLS "dh_free_sqlenv",	";dh_free_sqlenv",
	ctSQLS "dh_sql_disconnect",	";dh_sql_disconnect",
	ctSQLS "dh_tm_mark_abort",	";dh_tm_mark_abort",
	ctSQLS "dh_sqlselect",		";dh_sqlselect",
	ctSQLS "dh_tm_end_trans",	";dh_tm_end_trans",
	ctSQLS "dh_release_cursor",	";dh_release_cursor",
	ctSQLS "dh_sqlexecute",		";dh_sqlexecute",
	ctSQLS "dh_set_cursorname",	";dh_set_cursorname",
	ctSQLS "dh_set_cursor",		";dh_set_cursor",
	ctSQLS "dh_sql_chk_connection",	";dh_sql_chk_connection",
	ctSQLS "tpe_set_sqlda",		";tpe_set_sqlda",
	ctSQLS "dh_set_ptrs",		";dh_set_ptrs",
	ctSQLS "dh_get_curdbhdl",	";dh_get_curdbhdl",
	ctSQLS "dh_get_curtmhdl",	";dh_get_curtmhdl",
	ctSQLS "dh_sqlconnect",		";dh_sqlconnect",
	ctSQLS "dh_alloc_sqlenv",	";dh_alloc_sqlenv",
	/* End SQL functions */
	"RWTPREC",			"RWTPREC",
	"SERIALNUM",			"SERIALNUM",
	"IDXENT",			"IDXENT",
	"DELFIL",			"DELFIL",
	"ctDISTINCTest",		"ctDISTINCTest",
	"ctDISTINCTset",		"ctDISTINCTset",
	"ctdbAbort",			"ctdbAbort",
	"ctdbAddField",			"ctdbAddField",
	"ctdbAddIndex",			"ctdbAddIndex",
	"ctdbAddLocateCriteria",	"ctdbAddLocateCriteria",
	"ctdbAddSegment",		"ctdbAddSegment",
	"ctdbAllocDatabase",		"ctdbAllocDatabase",
	"ctdbAllocRecord",		"ctdbAllocRecord",
	"ctdbAllocSession",		"ctdbAllocSession",
	"ctdbAllocTable",		"ctdbAllocTable",
	"ctdbAlterTable",		"ctdbAlterTable",
	"ctdbBegin",			"ctdbBegin",
	"ctdbClearRecord",		"ctdbClearRecord",
	"ctdbCloneTable",		"ctdbCloneTable",
	"ctdbCloseAll",			"ctdbCloseAll",
	"ctdbCloseTable",		"ctdbCloseTable",
	"ctdbCommit",			"ctdbCommit",
	"ctdbConnect",			"ctdbConnect",
	"ctdbCreateTable",		"ctdbCreateTable",
	"ctdbDeleteRecord",		"ctdbDeleteRecord",
	"ctdbDisconnect",		"ctdbDisconnect",
	"ctdbFilterRecord",		"ctdbFilterRecord",
	"ctdbFindActiveTable",		"ctdbFindActiveTable",
	"ctdbFindKey",			"ctdbFindKey",
	"ctdbFindRowid",		"ctdbFindRowid",
	"ctdbFirstRecord",		"ctdbFirstRecord",
	"ctdbFreeDatabase",		"ctdbFreeDatabase",
	"ctdbFreeRecord",		"ctdbFreeRecord",
	"ctdbFreeSession",		"ctdbFreeSession",
	"ctdbFreeTable",		"ctdbFreeTable",
	"ctdbGetBestIndex",		"ctdbGetBestIndex",
	"ctdbGetCndxIndex",		"ctdbGetCndxIndex",
	"ctdbGetCndxIndexLength",	"ctdbGetCndxIndexLength",
	"ctdbGetDatabaseName",		"ctdbGetDatabaseName",
	"ctdbGetError",			"ctdbGetError",
	"ctdbGetField",			"ctdbGetField",
	"ctdbGetFieldAsBigint",		"ctdbGetFieldAsBigint",
	"ctdbGetFieldAsString",		"ctdbGetFieldAsString",
	"ctdbGetFieldByName",		"ctdbGetFieldByName",
	"ctdbGetFieldLength",		"ctdbGetFieldLength",
	"ctdbGetFieldName",		"ctdbGetFieldName",
	"ctdbGetFieldNbr",		"ctdbGetFieldNbr",
	"ctdbGetFieldNullFlag",		"ctdbGetFieldNullFlag",
	"ctdbGetFieldNumber",		"ctdbGetFieldNumber",
	"ctdbGetFieldNumberByName",	"ctdbGetFieldNumberByName",
	"ctdbGetFieldType",		"ctdbGetFieldType",
	"ctdbGetFilter",		"ctdbGetFilter",
	"ctdbGetIndex",			"ctdbGetIndex",
	"ctdbGetIndexDuplicateFlag",	"ctdbGetIndexDuplicateFlag",
	"ctdbGetIndexExtension",	"ctdbGetIndexExtension",
	"ctdbGetIndexNbr",		"ctdbGetIndexNbr",
	"ctdbGetIndexSegmentCount",	"ctdbGetIndexSegmentCount",
	"ctdbGetRecord",		"ctdbGetRecord",
	"ctdbGetRecordBuffer",		"ctdbGetRecordBuffer",
	"ctdbGetRecordCount",		"ctdbGetRecordCount",
	"ctdbGetRecordLength",		"ctdbGetRecordLength",
	"ctdbGetRecordLock",		"ctdbGetRecordLock",
	"ctdbGetRowid",			"ctdbGetRowid",
	"ctdbGetSegment",		"ctdbGetSegment",
	"ctdbGetSegmentField",		"ctdbGetSegmentField",
	"ctdbGetSegmentFieldName",	"ctdbGetSegmentFieldName",
	"ctdbGetSegmentMode",		"ctdbGetSegmentMode",
	"ctdbGetServerName",		"ctdbGetServerName",
	"ctdbGetTableExtension",	"ctdbGetTableExtension",
	"ctdbGetTableFieldCount",	"ctdbGetTableFieldCount",
	"ctdbGetTableIndexCount",	"ctdbGetTableIndexCount",
	"ctdbGetTableName",		"ctdbGetTableName",
	"ctdbGetTablePath",		"ctdbGetTablePath",
	"ctdbGetUserLogonName",		"ctdbGetUserLogonName",
	"ctdbGetUserPassword",		"ctdbGetUserPassword",
	"ctdbIsActiveDatabase",		"ctdbIsActiveDatabase",
	"ctdbIsEditedRecord",		"ctdbIsEditedRecord",
	"ctdbIsFilteredRecord",		"ctdbIsFilteredRecord",
	"ctdbIsNewRecord",		"ctdbIsNewRecord",
	"ctdbIsNullField",		"ctdbIsNullField",
	"ctdbIsTransActive",		"ctdbIsTransActive",
	"ctdbJumpToRecord",		"ctdbJumpToRecord",
	"ctdbLastRecord",		"ctdbLastRecord",
	"ctdbLockRecord",		"ctdbLockRecord",
	"ctdbLogon",			"ctdbLogon",
	"ctdbLogout",			"ctdbLogout",
	"ctdbNextRecord",		"ctdbNextRecord",
	"ctdbOpenTable",		"ctdbOpenTable",
	"ctdbPrevRecord",		"ctdbPrevRecord",
	"ctdbReadRecord",		"ctdbReadRecord",
	"ctdbSetDefaultIndex",		"ctdbSetDefaultIndex",
	"ctdbSetDefaultIndexByName",	"ctdbSetDefaultIndexByName",
	"ctdbSetError",			"ctdbSetError",
	"ctdbSetFieldAsBigint",		"ctdbSetFieldAsBigint",
	"ctdbSetFieldAsDate",		"ctdbSetFieldAsDate",
	"ctdbSetFieldAsDateTime",	"ctdbSetFieldAsDateTime",
	"ctdbSetFieldAsNumber",		"ctdbSetFieldAsNumber",
	"ctdbSetFieldAsSigned",		"ctdbSetFieldAsSigned",
	"ctdbSetFieldAsString",		"ctdbSetFieldAsString",
	"ctdbSetFieldAsTime",		"ctdbSetFieldAsTime",
	"ctdbSetIndexCndxExpr",		"ctdbSetIndexCndxExpr",
	"ctdbSetIndexFilename",		"ctdbSetIndexFilename",
	"ctdbSetIndexTemporaryFlag",	"ctdbSetIndexTemporaryFlag",
	"ctdbSetRecordCriteria",	"ctdbSetRecordCriteria",
	"ctdbStartDatabaseEngine",	"ctdbStartDatabaseEngine",
	"ctdbStopDatabaseEngine",	"ctdbStopDatabaseEngine",
	"ctdbUnlockRecord",		"ctdbUnlockRecord",
	"ctdbWriteRecord",		"ctdbWriteRecord",
	"ctdbParseRecordExpr",		"ctdbParseRecordExpr",
	"ctdbEvalExprAsSigned",		"ctdbEvalExprAsSigned",
	"ctdbEvalExprAsDate",		"ctdbEvalExprAsDate",
	"ctdbEvalExprAsTime",		"ctdbEvalExprAsTime",
	"ctdbEvalExprAsDateTime",	"ctdbEvalExprAsDateTime",
	"ctdbEvalExprAsNumber",		"ctdbEvalExprAsNumber",
	"ctdbEvalExprAsString",		"ctdbEvalExprAsString",
	"ctdbSetDefDateType",		"ctdbSetDefDateType",
	"ctdbSetDefTimeType",		"ctdbSetDefTimeType",
	"ctFILWCD",			"ctFILWCD",
	"ctdbAddUserDefFunc",		"ctdbAddUserDefFunc",
	"_ctdb_alloc",			"_ctdb_alloc",
	"_ctdb_free",			"_ctdb_free",
	"_ctdbListAlloc",		"_ctdbListAlloc",
	"_ctdbListFree",		"_ctdbListFree",
	"_ctdbListCount",		"_ctdbListCount",
	"_ctdbListDeleteEx",		"_ctdbListDeleteEx",
	"_ctdbListItem",		"_ctdbListItem",
	"_ctdbListAdd",			"_ctdbListAdd",
	"ctdbSetFieldDefaultValue",	"ctdbSetFieldDefaultValue",
    "ctdbGetFieldDefaultValue",	"ctdbGetFieldDefaultValue",
	"ctdbDeleteTable",		"ctdbDeleteTable",
	"ctdbFindTable",		"ctdbFindTable",
	"ctdbFirstTable",		"ctdbFirstTable",
	"ctdbNextTable",		"ctdbNextTable",
	"ctdbCreateDatabase",		"ctdbCreateDatabase",
	"ctdbSetRecordBuffer",		"ctdbSetRecordBuffer",
	"ctdbAddSegmentEx",		"ctdbAddSegmentEx",
	"ctdbGetFieldPrecision",	"ctdbGetFieldPrecision",
	"ctdbGetFieldScale",		"ctdbGetFieldScale",
	"ctdbGetIndexEmptyChar",	"ctdbGetIndexEmptyChar",
	"ctdbGetIndexKeyType",		"ctdbGetIndexKeyType",
	"ctdbGetIndexNullFlag",		"ctdbGetIndexNullFlag",
	"ctdbGetTableCreateMode",	"ctdbGetTableCreateMode",
	"ctdbSetFieldNullFlag",		"ctdbSetFieldNullFlag",
	"ctdbSetFieldPrecision",	"ctdbSetFieldPrecision",
	"ctdbSetFieldScale",		"ctdbSetFieldScale",
	"ctdbSetIndexEmptyChar",	"ctdbSetIndexEmptyChar",
	"ctdbSetAutoCommit",		"ctdbSetAutoCommit",
	"ctCreateSequence",		"ctCreateSequence",
	"ctDeleteSequence",		"ctDeleteSequence",
	"ctOpenSequence",		"ctOpenSequence",
	"ctGetCurrentSequenceValue",	"ctGetCurrentSequenceValue",
	"ctSetCurrentSequenceValue",	"ctSetCurrentSequenceValue",
	"ctGetNextSequenceValue",	"ctGetNextSequenceValue",
	"ctdbGetFieldDataLength",	"ctdbGetFieldDataLength",
	"ctdbClearField",		"ctdbClearField",
	"ctdbGetFieldAsNumber",		"ctdbGetFieldAsNumber",
	"ctdbGetFieldAsCurrency",	"ctdbGetFieldAsCurrency",
	"ctdbGetFieldAsUnsignedBigint",	"ctdbGetFieldAsUnsignedBigint",
	"ctdbGetFieldAsFloat",		"ctdbGetFieldAsFloat",
	"ctdbGetFieldAsMoney",		"ctdbGetFieldAsMoney",
	"ctdbGetFieldAsSigned",		"ctdbGetFieldAsSigned",
	"ctdbGetFieldAsUnsigned",	"ctdbGetFieldAsUnsigned",
	"ctdbGetFieldAsBool",		"ctdbGetFieldAsBool",
	"ctdbSetFieldAsCurrency",	"ctdbSetFieldAsCurrency",
	"ctdbSetFieldAsUnsignedBigint",	"ctdbSetFieldAsUnsignedBigint",
	"ctdbSetFieldAsFloat",		"ctdbSetFieldAsFloat",
	"ctdbSetFieldAsMoney",		"ctdbSetFieldAsMoney",
	"ctdbSetFieldAsUnsigned",	"ctdbSetFieldAsUnsigned",
	"ctdbSetFieldAsBool",		"ctdbSetFieldAsBool",
	"ctdbAssignRecordBuffer",	"ctdbAssignRecordBuffer",
	"_ctdbListDelete",		"_ctdbListDelete",
	"ctdbSetTransactionMode",	"ctdbSetTransactionMode",
	"ctdbIsActiveSession",	"ctdbIsActiveSession",
	"ctdbLocateRecord",	"ctdbLocateRecord",
	"ctdbBigIntToString",	"ctdbBigIntToString",
	"ctdbUpdateRecordCriteria",	"ctdbUpdateRecordCriteria",
	"ctdbSetFieldAsBinary",		"ctdbSetFieldAsBinary",
	"ctdbGetFieldAsBinary",		"ctdbGetFieldAsBinary",
	"ctdbFindRecord",		"ctdbFindRecord",
	"ctdbSetSavePoint",		"ctdbSetSavePoint",
	"ctdbRestoreSavePoint",		"ctdbRestoreSavePoint",
	"ctdbGetTableOpenMode",		"ctdbGetTableOpenMode",
	"ctdbCreateDir",		"ctdbCreateDir",
	"ctdbGetPathPrefix",		"ctdbGetPathPrefix",
	"ctdbIsActiveTable",		"ctdbIsActiveTable",
	"ctdbGetIndexByName",		"ctdbGetIndexByName",
	"ctdbCreateSession",		"ctdbCreateSession",
	"ctdbAddTableXtd",		"ctdbAddTableXtd",
	"BATSETX",			"BATSETX",
	"ctdbGetCtreeOWNER",		"ctdbGetCtreeOWNER",
	"ctdbSetCtreeOWNER",		"ctdbSetCtreeOWNER",
	"GETRES",			"GETRES",
	"ADDRES",			"ADDRES",
	"SETVARBYTS",			"SETVARBYTS",
/* <NEW_ENTRY>
	,"ctNewAPIFunction",		"ctNewAPIFunction"
*/
};

NINT	sigflg = 0;

/*
 * sighandler: When SIGINT received, set shutdown flag.
 */

/*^***********************************/
#ifdef PROTOTYPE
VOID sighandler(int signum)
#else
VOID sighandler(signum)
int signum;
#endif
{
	sigflg = 1;
}
/*~***********************************/


TEXT	errbuf[256];

/*^***********************************/
#ifdef PROTOTYPE
NINT ctAppLoadCtree(pTEXT filnam, NINT cttyp, ppVOID phandle)
#else
NINT ctAppLoadCtree(filnam, cttyp, phandle)
pTEXT	filnam;
NINT	cttyp;
ppVOID	phandle;
#endif
{
	NINT	fncnum;
	NINT	rc;
#ifdef UNICODE
	WCHAR	wfilnam[MAX_NAME];
#endif
	if (!phandle)
		return(PNUL_ERR);

	if (!ctAppTlsInit) {
#ifdef ctPortWIN32
		if ((ctAppTlsIndex = TlsAlloc()) == 0xffffffff)
			return(-1);
#else
#ifdef ctPortLYNXOS386
		if ((rc = pthread_keycreate(&ctAppTlsIndex, NULL)))
#else
		if ((rc = pthread_key_create(&ctAppTlsIndex, NULL)))
#endif
			return(-1);
#endif
		ctsfill(pCURENV, 0, ctAppMAXTHRDS*ctSIZE(NINT));
		ctAppTlsInit = 1;
	}

#ifdef ctPortWIN32
#ifdef UNICODE
	if (!MultiByteToWideChar(CP_ACP,
		MB_ERR_INVALID_CHARS,
		filnam,
		(int) strlen(filnam)+1,
		(LPWSTR)wfilnam,
		MAX_NAME)) {
		rc = -1;
		goto err_ret;
	}
			
	if (!(*phandle = LoadLibrary(wfilnam)))
#else
	if (!(*phandle = LoadLibrary(filnam)))
#endif
#else
	if (!(*phandle = dlopen(filnam, RTLD_LAZY)))
#endif
	{
#ifdef ctPortWIN32
		sprintf(errbuf, "Error: Unable to load c-tree module %s: %d",
			filnam, GetLastError());
#else
		sprintf(errbuf, "Error: Unable to load c-tree module: %.200s", dlerror());
#endif
		rc = ctAPPERR_LIBLOAD;
		goto err_ret;
	}

	for (fncnum=0; fncnum<SHFN_TOTAL; fncnum++) {
		if (ctshfnam[fncnum][cttyp][0] == ';')
			continue;

		if (!(ctSHENV[cttyp].ctfnc[fncnum] =
#ifdef ctPortWIN32
			GetProcAddress((HMODULE)*phandle, ctshfnam[fncnum][cttyp])
#else
			dlsym(*phandle, ctshfnam[fncnum][cttyp])
#endif
			)) {
				sprintf(errbuf, "Error: Unable to resolve c-tree function %s.\n",
					ctshfnam[fncnum][cttyp]);
				rc = ctAPPERR_FNCLOAD;
				goto err_ret;
		}
	}

	rc = 0;
err_ret:
	return(rc);
}
/*~***********************************/


/*^***********************************/
#ifdef PROTOTYPE
NINT ctAppUnloadCtree(ppVOID phandle)
#else
NINT ctAppUnloadCtree(phandle)
ppVOID	phandle;
#endif
{
	NINT	rc;

	rc = NO_ERROR;
	if (!phandle)
		return(PNUL_ERR);

	if (!*phandle)
		return(NO_ERROR);

#ifdef ctPortWIN32
	if (!FreeLibrary((HMODULE)*phandle)) {
		sprintf(errbuf, "Error: Unable to unload c-tree module: %d\n",
			rc = GetLastError());
	}
	TlsFree(ctAppTlsIndex);
#else
	dlclose(*phandle);
	pthread_key_delete(ctAppTlsIndex);
#endif
	ctAppTlsInit = 0;

	return(rc);
}
/*~***********************************/


/*^***********************************/
#ifdef PROTOTYPE
NINT ctAppSetTid(NINT tid)
#else
NINT ctAppSetTid(tid)
NINT	tid;
#endif
{
#ifdef ctPortWIN32
	return((NINT)TlsSetValue(ctAppTlsIndex, (pVOID)(NLONG)tid));
#else
	return(pthread_setspecific(ctAppTlsIndex, (pVOID)(NLONG)tid));
#endif
}
/*~***********************************/


/*^***********************************/
#ifdef PROTOTYPE
NINT ctAppGetTid(VOID)
#else
NINT ctAppGetTid()
#endif
{
#ifdef ctPortWIN32
	return((NINT)(NLONG)TlsGetValue(ctAppTlsIndex));
#else
	NINT	tid;
#ifdef ctPortLYNXOS386
	pthread_getspecific(ctAppTlsIndex, (ppVOID)&tid);
#else
	tid = (NINT)(NLONG)pthread_getspecific(ctAppTlsIndex);
#endif
	return(tid);
#endif
}
/*~***********************************/


/*^***********************************/
#ifdef PROTOTYPE
COUNT ctAppGetUEC(VOID)
#else
COUNT ctAppGetUEC()
#endif
{
	NINT	CURENV = pCURENV[ctAppGetTid()];

	if (CURENV == CTTYP_SRV)
#ifdef ctBNDentryPointMutex
		return(ctGetUserErrorCode());
#else  /* ~ctBNDentryPointMutex */
#ifdef ctPortWIN32
		return(ctstatv[(LONG)(UNLONG)TlsGetValue(tlsIndex)]->uec);
#else
		return(ctstatv[pthread_OWNER()]->uec);
#endif
#endif /* ~ctBNDentryPointMutex */

	return(((pCTGVAR)GETCTREE(WCHCTREE()))->suerr_cod);
}
/*~***********************************/


/*^***********************************/
#ifdef PROTOTYPE
COUNT ctAppGetIEC(VOID)
#else
COUNT ctAppGetIEC()
#endif
{
	NINT	CURENV = pCURENV[ctAppGetTid()];

	if (CURENV == CTTYP_SRV)
#ifdef ctBNDentryPointMutex
		return(ctGetIsamErrorCode());
#else  /* ~ctBNDentryPointMutex */
#ifdef ctPortWIN32
		return(ctstatv[(LONG)(UNLONG)TlsGetValue(tlsIndex)]->iec);
#else
		return(ctstatv[pthread_OWNER()]->iec);
#endif
#endif /* ~ctBNDentryPointMutex */

	return(((pCTGVAR)GETCTREE(WCHCTREE()))->sisam_err);
}
/*~***********************************/


/*^***********************************/
FILNO ctAppGetIFL (void)
{
	NINT	CURENV = pCURENV[ctAppGetTid()];

	if (CURENV == CTTYP_SRV)
#ifdef ctBNDentryPointMutex
		return(ctGetIsamFileNbr());
#else  /* ~ctBNDentryPointMutex */
#ifdef ctPortWIN32
		return(ctstatv[(LONG)(UNLONG)TlsGetValue(tlsIndex)]->ifl);
#else
		return(ctstatv[pthread_OWNER()]->ifl);
#endif
#endif /* ~ctBNDentryPointMutex */

	return(((pCTGVAR)GETCTREE(WCHCTREE()))->sisam_fil);
}
/*~***********************************/

/*^***********************************/
#ifdef PROTOTYPE
COUNT ctAppGetSEC(VOID)
#else
COUNT ctAppGetSEC()
#endif
{
	NINT	CURENV = pCURENV[ctAppGetTid()];

	if (CURENV == CTTYP_SRV)
#ifdef ctBNDentryPointMutex
		return(ctGetSystemErrorCode());
#else  /* ~ctBNDentryPointMutex */
#ifdef ctPortWIN32
		return(ctstatv[(LONG)(UNLONG)TlsGetValue(tlsIndex)]->sec);
#else
		return(ctstatv[pthread_OWNER()]->sec);
#endif
#endif /* ~ctBNDentryPointMutex */

	return(((pCTGVAR)GETCTREE(WCHCTREE()))->ssysiocod);
}
/*~***********************************/

#else /* CTCLSV_MULTI_MOD */

#ifdef __cplusplus
extern "C"
{
#endif

VOID sighandler();
NINT ctAppLoadCtree(pTEXT filnam, NINT cttyp, ppVOID phandle);
NINT ctAppUnloadCtree(ppVOID phandle);
NINT ctAppSetTid(NINT tid);
NINT ctAppGetTid(VOID);
COUNT ctAppGetUEC(VOID);
COUNT ctAppGetIEC(VOID);
FILNO ctAppGetIFL(void);
COUNT ctAppGetSEC(VOID);

#ifdef __cplusplus
}
#endif

#endif /* CTCLSV_MULTI_MOD */

#endif /* ctFeatSRVDLL */

/* end ctclsv.h */
