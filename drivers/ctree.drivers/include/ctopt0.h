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

#if (!defined(ctOPT0H) && defined(ctFEATURE_SET)) /* This file is not even concidered if no ctFEATURE_SET defined */
#define ctOPT0H


/*^***************************************************************************************************/
#if ctFEATURE_SET >= 1
#undef  ctMAXUSERS
#define ctMAXUSERS	10	/*  Support up 10 concurrent connections */
#else
#undef  ctMAXUSERS
#define ctMAXUSERS	100	/*  Support up 100 concurrent connections */
#endif
/*~***************************************************************************************************/

/*^***************************************************************************************************/
#if ctFEATURE_SET >= 2
#undef  ctMAXFIL
#define ctMAXFIL	64	/*  Support up to 64 concurrent open physical files */
#else
#undef  ctMAXFIL
#define ctMAXFIL	100	/*  Support up to 100 concurrent open physical files */
#endif
/*^***************************************************************************************************/


/*^***************************************************************************************************/
#if ctFEATURE_SET >= 3

#undef 	ctFeatJOBMGTSYS			/* No Job Management Support */
#define NO_ctFeatJOBMGTSYS


#undef     CTHISTORY			/*  No transaction history support */
#define NO_CTHISTORY			

#undef     MIRROR			/*  No mirror support */
#define NO_MIRROR			

#undef     PARMF			/*  No parameter file support */
#define NO_PARMF			

#undef     ctCUSTOM			/*  No custom API support */
#define NO_ctCUSTOM			

#undef     ctFeatCTUSER			/*  No CT_USER API support */
#define NO_ctFeatCTUSER			

#undef     ctFeatFILEBLOCK		/*  No file block support */
#define NO_ctFeatFILEBLOCK		

#undef     ctFeatFILEUSRLST		/*  No user file list support */
#define NO_ctFeatFILEUSRLST		

#undef     ctBEHAV_IDLE_FLUSH		/*  No idle flush supported */
#define NO_ctBEHAV_IDLE_FLUSH		

#undef     ctFeatDIAGNOSE_UDEFER_CHK	/*  No support for DIAGNOSTICS CHECK_UDEFER */
#define NO_ctFeatDIAGNOSE_UDEFER_CHK	

#undef     RTREE			/*  No r-tree support */
#define NO_RTREE			

#undef     ctTEST_LOCAL			/*  No local/network file check support */
#define NO_ctTEST_LOCAL			

#undef     ctFeatWIN32_GFIBH		/*  No enhanced unique file detection support */
#define NO_ctFeatWIN32_GFIBH		

#undef     ctFeatASYNC			/*  No support for CTASYNC function */
#define NO_ctFeatASYNC			

#undef     ctFeatLOKLST			/*  No lock list API function support */
#define NO_ctFeatLOKLST			

#undef     ctFeatKEY_ESTIMATE		/*  No support for ESTKEY/FRCKEY functions */
#define NO_ctFeatKEY_ESTIMATE		

#undef     ctFeatIOPERFORMANCE		/*  No support for IOPERFORMANCE(X) functions */
#define NO_ctFeatIOPERFORMANCE		

#undef     ctFeatRWTPREC		/*  No support for partial record rewrite */
#define NO_ctFeatRWTPREC		

#undef     ctFeatDUPOPEN		/*  No dupopen() support */
#define NO_ctFeatDUPOPEN		

#undef     ctFeatVIRTUAL_FILES		/*  No virtual file support */
#define NO_ctFeatVIRTUAL_FILES		

#undef     ctFeatDISK_FULL_CHECK	/*  No disk free space checking support */
#define NO_ctFeatDISK_FULL_CHECK	

#undef     ctFeatISAM_SET		/*  No ISAM set support */
#define NO_ctFeatISAM_SET		

#undef     ctFeatISAM_RANGE		/*  No ISAM range support */
#define NO_ctFeatISAM_RANGE		

#undef     CTINOD_C			/*  Exclude ctinod_a.c from ctclib module */
#define NO_CTINOD_C			

#undef     ctFeatBlockingRead		/*  No blocking ISAM read support */
#define NO_ctFeatBlockingRead		

#undef     ctSYSQUE			/*  No system queue support */
#define NO_ctSYSQUE			

#undef     ctREPLICATION		/*  No replication support */
#define NO_ctREPLICATION		

#undef     ctFeatREPLICAT		/*  No replication API support */
#define NO_ctFeatREPLICAT		

#define ctNO_CAMO			/*  No encryption support */

#undef     ctCAMOsdk			/*  No advanced encryption support */
#define NO_ctCAMOsdk			

#undef     CONDIDX			/*  No conditional index support */
#define NO_CONDIDX			

#undef     ctFeatSNAPSHOT		/*  No snapshot support */
#define NO_ctFeatSNAPSHOT		

#undef     ctFeatSECURITY		/*  No FAIRCOM.FCS security support */
#define NO_ctFeatSECURITY		

#undef     SUPER			/*  No superfile support */
#define NO_SUPER			

#undef     VARLK			/*  No key compression support */
#define NO_VARLK			

#undef     BATCH			/*  No batch support */
#define NO_BATCH			

#undef     ctFeatCHANNELS		/*  No file channel support */
#define NO_ctFeatCHANNELS		

#undef     ctCACHE_MEMORY		/*  No processor cache-aligned memory */
#define NO_ctCACHE_MEMORY		

#undef     ctFeatCFGFILE		/*  No configuration file support */
#define NO_ctFeatCFGFILE		

#undef     CONTEXT			/*  No ISAM context support */
#define NO_CONTEXT			

#undef     ctFeatSYSLOG			/*  No system log support */
#define NO_ctFeatSYSLOG			

#undef     ctBEHAV_freopen		/*  No reuse of stream descriptors */
#define	NO_ctBEHAV_freopen		

#undef     ctFeatSRVR_MONITOR		/*  No message monitor support */
#define NO_ctFeatSRVR_MONITOR		

#undef     ctFeatFILE_COMPACT		/*  No support for file compact */
#define NO_ctFeatFILE_COMPACT		

#undef     ctFeatFILE_REBUILD		/*  No support for file rebuild */
#define NO_ctFeatFILE_REBUILD		

#undef     ctFeatIDLE_THREAD		/*  No idle thread */
#define NO_ctFeatIDLE_THREAD		

#undef     ctFeatSPACE_RECLAIM_QUEUE	/*  No space reclamation queue support */
#define NO_ctFeatSPACE_RECLAIM_QUEUE	

#undef     ctHUGEFILEsegm		/*  No segmented file support */
#define NO_ctHUGEFILEsegm		

#undef     ctFeatDYNAMIC_DUMP		/*  No dynamic dump support */
#define NO_ctFeatDYNAMIC_DUMP		

#undef     ctSS				/*  No strict serialization support */
#define NO_ctSS				

#undef     ctFeatMEMFILE		/*  No memory file support */
#define NO_ctFeatMEMFILE		

#undef     ctFeatPRICACHE		/*  No prime cache support */
#define NO_ctFeatPRICACHE		

#undef     ctRECBYTIDX			/*  No RECBYT index support */
#define NO_ctRECBYTIDX			

#undef     ctFeatSCANCACHE		/*  No scanner LRU support */
#define NO_ctFeatSCANCACHE		

#undef     ctFeatXTDCMP			/*  No extended key compression support */
#define NO_ctFeatXTDCMP			

#undef     RESOURCE			/*  No resource support */
#define NO_RESOURCE			

/*  Note: turning off ctXTDLOG only saves about 2 KB */
#undef     ctXTDLOG			/*  No extended transaction log support */
#define NO_ctXTDLOG			

#undef     ctFeatThrdBlock_API		/*  No ctThrdBlockXxx API support */
#define NO_ctFeatThrdBlock_API		

#undef     ctFeatThrdCreate_API		/*  No ctThrdCreateXxx API support */
#define NO_ctFeatThrdCreate_API		

#undef     ctFeatThrdMutex_API		/*  No ctThrdMutexXxx API support */
#define NO_ctFeatThrdMutex_API		

#undef     ctFeatThrdQueue_API		/*  No ctThrdQueueXxx API support */
#define NO_ctFeatThrdQueue_API		

#undef     ctFeatThrdSemap_API		/*  No ctThrdSemapXxx API support */
#define NO_ctFeatThrdSemap_API		

#undef     ctFeatThrdSleep_API		/*  No ctThrdSleepXxx API support */
#define NO_ctFeatThrdSleep_API		

#undef     ctFeatTRANDEP		/*  No transaction dependent file create/delete support */
#define NO_ctFeatTRANDEP		

#undef     ctFeatRSTRDEL		/*  No restorable file delete support */
#define NO_ctFeatRSTRDEL		

#undef     ctFeatTRAN_BAK_FWD		/*  No rollback and forward roll support */
#define NO_ctFeatTRAN_BAK_FWD		

#undef     ctLOG_IDX			/*  No LOG_IDX support */
#define NO_ctLOG_IDX			

#undef     ctBEHAV_CMTLOK		/*  No COMMIT_READ_LOCK support */
#define NO_ctBEHAV_CMTLOK		
#endif

#undef     ctHUGEFILE			/*  No huge file support */
#define NO_ctHUGEFILE			

#undef     ctUNIQFILE			/*  No automatic duplicate file ID reassignment */
#define NO_ctUNIQFILE			
#endif

/*~***************************************************************************************************/

/*^***************************************************************************************************/
#if ctFEATURE_SET >= 4

#undef     TRANPROC			/*  No transaction support */
#define NO_TRANPROC			

#undef     ctFeatDELETE_NODE_THRD	/*  No delete node thread support */
#define NO_ctFeatDELETE_NODE_THRD	

/*~***************************************************************************************************/

/*^***************************************************************************************************/
#if ctFEATURE_SET < 3
/* #define ctDBGstack */
/* #define ctBNDentryPoint */
#endif
/*~***************************************************************************************************/

#endif /* ~ctOPT0H */

/* end of ctopt0.h */
