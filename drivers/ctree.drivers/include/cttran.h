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

#ifndef CTTRANH
#define CTTRANH

#ifdef ctSRVR
#ifndef ctFeatSNAPSHOT
extern LONG	ct_compflg2;
#endif
#endif

#ifdef ctFeat6BT
typedef ULONG	TRNSTORE[2];
#else
typedef ULONG	TRNSTORE;
#endif
typedef TRNSTORE ctMEM * pTRNSTORE;

typedef ULONG	ctTFLMAP[3];
typedef ctTFLMAP ctMEM * pctTFLMAP;
#define ctTFLMAPver	1		/* TFLMAP version #	*/

#ifndef ctNOGLOBALS
#ifdef ctXTDLOG
EXTERN VRLEN	ct_mxusrlog;	/* maximum size of user log entry */
#endif
#ifndef MULTITRD
EXTERN LONG ct_trnhghmrk;  /* threshold to warn about tran high-water mark */
EXTERN LONG ct_usrtl[MXU2];/* log file sequence number for BEGTRAN */
EXTERN LONG ct_usrix[MXU2];/* log file index op number */
EXTERN LONG ct_usrty[MXU2];/* ctSHADOW / ctLOGFIL transaction type */
EXTERN LONG ct_usrtr[MXU2];/* active transaction # for user or zero */
#ifdef ctFeatDFRIDX
EXTERN LONG ct_usrdkln[MXU2];/* log number of first deferred key entry for tran */
EXTERN LONG ct_usrdklp[MXU2];/* log offset of first deferred key entry for tran */
#define ct_usrdkln(a)	ct_usrdkln[a]
#define ct_usrdklp(a)	ct_usrdklp[a]
EXTERN LONG ct_usrdkln2[MXU2];/* log number of last deferred key entry for tran */
EXTERN LONG ct_usrdklp2[MXU2];/* log offset of last deferred key entry for tran */
#define ct_usrdkln2(a)	ct_usrdkln2[a]
#define ct_usrdklp2(a)	ct_usrdklp2[a]
#if defined(ctFeatRUCB) && defined(TRANPROC)
EXTERN pSHADLST rucbh[MXU2]; /* first record update callback DFRKEY entry */
EXTERN pSHADLST rucbt[MXU2]; /* last record update callback DFRKEY entry */
#define rucbhed(a)	rucbh[a]
#define rucbend(a)	rucbt[a]
#endif
#endif
#define ct_usrtr(a)	ct_usrtr[a]
#define ct_usrty(a)	ct_usrty[a]
#ifdef ctFeat6BT
EXTERN LONG ct_usrtr2[MXU2];
EXTERN LONG ct_usrix2[MXU2];
#define ct_usrtr2(a)	ct_usrtr2[a]
#define ct_usrix2(a)	ct_usrix2[a]
#endif
#ifdef ctSUCTRAN
EXTERN LONG ct_usrbl[MXU2];/* log file sequence number for BEGTRAN */
EXTERN LONG ct_usrbp[MXU2];/* log file position for BEGTRAN */
EXTERN LONG ct_usrel[MXU2];/* log file sequence number for ENDTRAN */
EXTERN LONG ct_usrep[MXU2];/* log file position for ENDTRAN */
EXTERN LONG ct_usrtv[MXU2];/* save tran# for SUCTRAN pending list */
EXTERN LONG ct_usrtv2[MXU2];
#endif
#endif
#endif

#define drpSIZ		8	/* ctlogdropidx idx LONG array elements */

#define CHKPHDR		10	/* number of longs which begin checkpoint rec */
#define CHKPHDRsiz	(CHKPHDR * ctSIZE(LONG))

#define CM_CHKPHDR	0	/* commit mode				      */
#define LL_CHKPHDR	1	/* previous chkpnt log			      */
#define LP_CHKPHDR	2	/* previous chkpnt log position		      */
#define TR_CHKPHDR	3	/* active transactions			      */
#define FL_CHKPHDR	4	/* active files				      */
#define AN_CHKPHDR	5	/* abort nodes				      */
#define CN_CHKPHDR	6	/* commit nodes				      */
#define CD_CHKPHDR	7	/* commit dat				      */
#define VI_CHKPHDR	8	/* vulnerable index updates		      */
#define A1_CHKPHDR	9	/* # of auxhdr blocks (each CHKPHDR in len)   */

				/* auxhdr */
#define LG_CHKPHDR	0	/* login ID information		      	      */
#define XU_CHKPHDR	1	/* MXU2 value				      */
#define OL_CHKPHDR	2	/* (old) low log at checkpoint		      */
#define RD_CHKPHDR	3	/* redolist [ctSUCTRAN]			      */
#define SZ_CHKPHDR	4	/* size of NINT				      */
#define RP_CHKPHDR	5	/* replication file tfil map to unique key    */
#define RV_CHKPHDR	6	/* tfil map version #			      */
#define SC_CHKPHDR	7	/* SUCTRAN pending list			      */
#define RF_CHKPHDR	8	/* recovery flag (ctrflg) indicator	      */
#define BL_CHKPHDR	9	/* beginning log position for active trans    */

				/* ax2hdr */
#define RL_CHKPHDR	0	/* oldest log required by replication	      */
#define DT_CHKPHDR	1	/* distinct counts			      */
#define DG_CHKPHDR	2	/* distinct counts partial keys		      */
#define DZ_CHKPHDR	3	/* ctMAXSEGdistinct			      */
#define ID_CHKPHDR	4	/* IDfield water marks			      */
#define DR_CHKPHDR	5	/* FC_DAR_TYPES				      */
#define FX_CHKPHDR	6	/* extra file info			      */
#define XZ_CHKPHDR	7	/* extra file info: bytes per file	      */
#define CR_CHKPHDR	8	/* compressed record resources		      */
#define GU_CHKPHDR	9	/* enhanced IDXENT GUIx support		      */

				/* ax3hdr */
#define PH_CHKPHDR	0	/* partition host map list		      */
#define RA_CHKPHDR	1	/* oldest log required by all replicators     */
#define ML_CHKPHDR	2	/* ctminlogsync (DELAYED_DURABILITY) value    */
#define RN_CHKPHDR	3	/* number of restore points in checkpoint     */
#define RT_CHKPHDR	4	/* list of active restore points	      */
#define RZ_CHKPHDR	5	/* bytes per restore point (in list)	      */
#define RC_CHKPHDR	6	/* rollback to RP pending		      */
#define RR_CHKPHDR	7	/* restore point version		      */
#define RS_CHKPHDR	8	/* restore point last serial number (8 bytes) */
		   /*	9 */	/* IN USE: last 4 bytes of serial number      */

				/* ax4hdr */
#define SL_CHKPHDR	0	/* restore point skip forward log #	      */
#define SP_CHKPHDR	1	/* restore point skip forward log position    */
#define DK_CHKPHDR	2	/* deferred index operation support	      */
#define PB_CHKPHDR	3	/* lowest log with begin of active trans      */
#define BD_CHKPHDR	4	/* LOCAL_DIRECTORY or current working dir     */
#define SD_CHKPHDR	5	/* list of SUBST'd drives		      */


/*
** LOGINDX tranmgt indicators
*/
#define NOtran		0L
#define YEStran		1L
#define NEWtran		2L
#define COMtran		3L
#define CHKtran		4L
#define IDXtran		5L
#define DATtran		6L
#define BAKtran		9L
#define RCVtran		10L
#define UNDtran		11L
#define BAKtran_cmplt	12L	/* beginning and end of transaction found */

/*
** transaction log entry header structure
*/
typedef struct trandsc {
	LONG	trannum;  /* transaction number */
	LONG	tranpos1; /* data offset */
#ifdef ctHUGEFILE
	LONG	tranpos2; /* data offset (high word) */
	UCOUNT	trannum2; /* 6 byte transaction number (high 2 bytes ) */
	UCOUNT	tranaux;  /* auxillary info */
#endif
	ULONG	tranfil;  /* tfil number */
	ULONG	tranlen;  /* current entry length (forward link) */
	ULONG	tranpln;  /* previous entry length (back link) */
#ifdef ctXTDLOG
	LONG	trantorg;
	LONG	tranatr;  /* attributes */
#endif
	UCOUNT	trantyp;  /* operation type */
	UCOUNT	tranusr;  /* task id */
#ifdef ctCMPLOG
	VRLEN	trandln;
	LONG	tranxtd;
#endif
	} TRANDSC;
typedef TRANDSC ctMEM *	pTRANDSC;

#ifdef ctFeatMAXFILE32

typedef SYSNO CTSHFT; /* shadfil data type */
#define SHADFIL_NONE 0xffffffff /* shadfil does not contain a valid system file number */

#else

typedef UCOUNT CTSHFT; /* shadfil data type */
#define SHADFIL_NONE 0xffff /* shadfil does not contain a valid system file number */

#endif

#ifdef ctSHADOWMEM
/*
** add a small data region to avoid a second sub-allocator call
** on shadow entries with small data needs
*/

/*
** optional components
*/
#ifdef ctHUGEFILE
#define shadowHUGEFILE	8
#else
#define shadowHUGEFILE	0
#endif

#ifdef ctXTDLOG
#define shadowXTDLOG	4
#else
#define shadowXTDLOG	0
#endif

#ifdef ctDYNHASH
#define shadowDYNHASH	4	/* ctSIZE(NINT) */
#else
#define shadowDYNHASH	0
#endif

#ifdef ctMULTIOPN
#define shadowMULTIOPN	4	/* ctSIZE(NINT) */
#else
#define shadowMULTIOPN	0
#endif

#ifdef ctFeatLOGFLUSH_MOD
#define MOGPTRinit	-11	/* indicator that 1st parameter of ctwrtlog  **
				** points to array of LONGs, not a single    **
				** LONG. Value is an arbitrary negative	     **
				** value and not equal to a valid log number.*/
#define shadowFLUSH	8	/* 2 * ctSIZE(LONG) */
#else
#define shadowFLUSH	0
#endif

#ifdef ctFeatMAXFILE32

/*
** core elements: 6 pointers, 4 LONGs, 3 COUNTS, and one LONG
*/
#ifdef ct8P
#define shadowCORE	74
#else
#define shadowCORE	50
#endif

#else

/*
** core elements: 6 pointers, 4 LONGs and 4 COUNTS
*/
#ifdef ct8P
#define shadowCORE	72
#else
#define shadowCORE	48
#endif

#endif

#define shadowTOT	(shadowCORE + shadowHUGEFILE + shadowXTDLOG + shadowDYNHASH + shadowMULTIOPN + shadowFLUSH)

#if (shadowTOT == 64)
#define ctSHADOWlen	128
#else
#define ctSHADOWlen	((((shadowTOT + 63) / 64) * 64) - shadowTOT)
#endif

#endif /* ctSHADOWMEM */

typedef struct shadlst {
	struct shadlst ctMEM *shadlnk; /* list link */
	struct shadlst ctMEM *shadprv; /* list back link */
	struct shadlst ctMEM *shadbak; /* save point back link */
	struct shadlst ctMEM *shadfwd; /* save point forward link */
	struct shadlst ctMEM *shadhsh; /* hash link */
	pTEXT	              shadloc; /* pointer to info in shadow buffer */
	LONG		      shadsav; /* savepoint */
	LONG		      shadpos1;/* actual file location */
#ifdef ctHUGEFILE
	LONG		      shadpos2;/* actual file location */
	VRLEN		      shadtorg;/* offset to origin */
#endif
#ifdef ctXTDLOG
	LONG		      shadatr; /* attribute bits */
#endif
	LONG		      shadcnt; /* hash count */
	VRLEN		      shadlen; /* actual record length */
#ifdef ctDYNHASH
	UINT		      shadseq; /* ctgetlst sequence nbr */
#endif
#ifdef ctMULTIOPN
	NINT		      shadufl; /* user file number */
#endif
#ifdef ctFeatLOGFLUSH_MOD
	LONG		      shadmog[2]; /* required log flush highpoint */
#endif
	CTSHFT		      shadfil; /* actual file number */
	UCOUNT		      shadshf; /* shadow hash shift factor */
	UCOUNT		      shadswp; /* swap space indicator */
	UCOUNT		      shadtyp; /* type of shadow entry */
#ifdef ctDBGpreimgspc
	UCOUNT		      shaddbg; /* original type before SH_INVLD */
#endif
#ifdef ctSHADOWMEM
	TEXT		      shaddat[ctSHADOWlen]; /* small data region */
#endif
	} SHADLST;
typedef SHADLST ctMEM *	pSHADLST;
typedef SHADLST ctMEM * ctMEM * ppSHADLST;

typedef struct coalst {
	pCTFILE	cnum;
	LONG	fid[3];
#ifdef ctHUGEFILE
	LONG	pv2;
	LONG	recbyt2;
#endif
	LONG	pv1;
	LONG	recbyt1;
	} COALST;
typedef COALST ctMEM *	pCOALST;
typedef COALST ctMEM * ctMEM * ppCOALST;

typedef struct {
	VRLEN	segoff;
	VRLEN	seglen;
	} DIFSEG;
typedef DIFSEG ctMEM *	pDIFSEG;

/* checkpoint types: */
/* note: update cmode_name in ctldmp.c when adding a new checkpoint type */
/*	AVAIL_CHECK	 10L						*/
/*	AVAIL_CHECK	 9L						*/
#define RECOVER_CHECK	 8L	/* at end of automatic recovery		*/
/*	AVAIL_CHECK	 7L						*/
#ifdef ctBEHAV_API_CHECK
#define API_CHECK	 6L
#endif
#define QUIET_CHECK	 5L	/* called by ctQUIET			*/
#define NORCV_CHECK	 4L	/* no recovery, but clean chkpnt needed */
#define IDLE_CHECK	 3L
#define SETSEG_CHECK	 2L
#define FILCRE_CHECK	 1L
#define STDR_CHECK	 0L
#define FINAL_CHECK	-1L
#define BDUMP_CHECK	-2L
#define EDUMP_CHECK	-3L
/*	AVAIL_CHECK	-4L						*/

#ifndef ctBEHAV_API_CHECK
#define API_CHECK	-5L
#endif
#define PDUMP_CHECK	-6L
#define RESTORE_CHECK	-7L
#define AUTORP_CHECK	-8L
/*	AVAIL_CHECK	-9L						*/
/*	AVAIL_CHECK	-10L						*/

#define SLNULL		(pSHADLST) NULL
#define DATCOM_WINDOW	2
#define IDXABT_WINDOW	4
#define MAXREGIONS	10

#define DIFF0		20
#define DIFF1		42
#define DIFF2		64
#ifdef ctFeat6BT
#define SIZLOGKEY	(1 + ctSIZE(LONG) + ctSIZE(UCOUNT))
#else
#define SIZLOGKEY	(1 + ctSIZE(LONG))
#endif
#define SIZLOGKEY1	(SIZLOGKEY - 1)

#ifdef ctHUGEFILE
#define DD_CHUNK	(VRLEN) 65536
#ifdef ctFeat8K_LOGIO
#define LOGBLOCKS	8
#else
#define LOGBLOCKS	32
#endif
#else
#define DD_CHUNK	(VRLEN) 59392
#define LOGBLOCKS	24
#endif

#ifdef ctFeat8K_LOGIO
#define BLOGPOS		8192L
#else
#define BLOGPOS		2048L	/* (BLOGPOS * LOGBLOCKS) determines the
				** size of the internal transaction log buffer.
				** If these are changed such that the product
				** is different, the resulting code will not
				** work properly with existing log files.
				*/
#endif

#ifndef ctLOGPAGSIZ
#define ctLOGPAGSIZ	BLOGPOS	/* ctLOGPAGSIZ determines the minium I/O
				** size during log writes. It must divide
				** evenly into (BLOGPOS * LOGBLOCKS)
				*/
#endif
#ifdef ctCTTRDELAT
#define CTTRDELTA	ctCTTRDELAT
#else
#define CTTRDELTA	500000L	/* # of updates that cause flush */
#endif
#ifdef ctCTCPDELTA
#define CTCPDELTA	ctCTCPDELTA
#else
#define CTCPDELTA	2L	/* # of chkpnts (less 1) that cause flush */
#endif
#ifndef LOGCHUNKX
#define LOGCHUNKX	1100000L
#endif
#ifndef LOGCHUNKN
#define LOGCHUNKN	550000L
#endif
#define LOGLIMIT	2500000L
#define LOGSPR		NO
#define LOGPURGE	4

#define ctVOLATILE	24	/* size of dynamic region for SH_HDRCP	  */
#define SIZCTL		28	/* size of header area for chkpnt logging */
#define TOTCTL		0	/* header area index for LONG phyrec	  */
#define DELCTL		1	/* header area index for LONG delstk	  */
#define LOGCTL		2	/* header area index for LONG numrec	  */	
#define NUMCTL		6	/* header area index for long NUMENT	  */
/* ---------------------------------------------------------------------- */
#define LNGCTL		(SIZCTL / ctSIZE(LONG))
#define ctRCV_cntl	0
#ifdef ctHUGEFILE
#define ctRCV_ctl2	LNGCTL
#define ctRCV_lnum	(2 * LNGCTL)
#else  /* ~ctHUGEFILE */
#define ctRCV_lnum	LNGCTL
#endif /* ~ctHUGEFILE */
#define ctRCV_lpos	(ctRCV_lnum + 1)
#define ctRCV_fwrd	(ctRCV_lnum + 2)
#define ctRCV_fnam	(ctRCV_lnum + 3)
#define ctRCV_bytes	(ctRCV_fnam * ctSIZE(LONG))
/* ----------------------------------------------------------------- */
#define ctRDM_lnksiz	(ctSIZE(pTEXT) / ctSIZE(LONG))
#define ctRDM_link	0
#define ctRDM_cntl	(ctRCV_cntl + ctRDM_lnksiz)
#ifdef ctHUGEFILE
#define ctRDM_cntl2	(ctRCV_ctl2 + ctRDM_lnksiz)
#endif
#define ctRDM_lnum	(ctRCV_lnum + ctRDM_lnksiz)
#define ctRDM_lpos	(ctRCV_lpos + ctRDM_lnksiz)
#define ctRDM_fwrd	(ctRCV_fwrd + ctRDM_lnksiz)
#define ctRDM_fnam	(ctRCV_fnam + ctRDM_lnksiz)
#define ctRDM_bytes	(ctRDM_fnam * ctSIZE(LONG))
/* ----------------------------------------------------------------- */
#define ctSFL_siz2	0
#define ctSFL_siz1	1
#define ctSFL_max	2
#define ctSFL_lst	3
#define ctSFL_hdrz	4
#define ctSFL_fid	5
#define ctSFL_vid	6
#define ctSFL_tid	7
#define ctSFL_ver	8
#define ctSFL_typ	9
#define ctSFL_sup	10
/* ----------------------------------------------------------------- */
#define ctDEF_hghtrn2	0
#define ctDEF_hghtrn1	1
/* ----------------------------------------------------------------- */
#define ctHDRLOClocl	0
#ifdef ctHUGEFILE
#define ctHDRLOCloc2	1
#define ctHDRLOCsupi	2
#else  /* ~ctHUGEFILE */
#define ctHDRLOCsupi	1
#endif /* ~ctHUGEFILE */
#define ctHDRLOClnum	(ctHDRLOCsupi + 1)
#define ctHDRLOClpos	(ctHDRLOClnum + 1)
#define ctHDRLOCsize	(ctHDRLOClpos + 1)
/* ----------------------------------------------------------------- */
#define ctMBRLSTsupi	ctRDM_lnksiz
#define ctMBRLSTfili	(ctRDM_lnksiz + 1)
#define ctMBRLSTsrvi	(ctRDM_lnksiz + 2)
#define ctMBRLSTtimi	(ctRDM_lnksiz + 3)
#define ctMBRLSTsize	(ctMBRLSTtimi + 1)

/*
** preimage space state indicators stored in SHADLST shadswp field
*/
#define SHDSWPyes	0x0001
#define SHDSWPhys	0x0002
#define SHDSWPon	(SHDSWPyes | SHDSWPhys)
#define SHDSWPntfy	0x0004		/* notification turned on at time
					** shadow space entry made
					*/
#define SHDSWPcnt	0x0008		/* entry contributes to shadcnt of
					** hash bin root
					*/
#define SHDSWPalc	0x0010		/* reallocate preimage swap buffer
					without reading from swap file */
#define SHDSWPreplOff	0x0020		/* replication logging suppressed at
					time shadow space entry was made */
#define SHDSWPtruncate	0x0040		/* shadow space entry was made during a
					file truncate operation */

/*	used		0x1000 		see ctSETSEGTRN/ctTRANAUXsetseg */
/*	used		0x2000 		see ctANYSEGTRN/ctTRANAUXanyseg */

#ifdef ctHUGEFILE
/*
** the extended VOLATILE region is the exception to the rule that the higher
** order bytes come before the (regular) lower order bytes:
**		24 bytes beginning with phyrec1, then
**		24 bytes beginning with phyrec2
*/
#define ctVOLATILEtot	(2 * ctVOLATILE)
#else  /* ~ctHUGEFILE */
#define ctVOLATILEtot	ctVOLATILE
#endif /* ~ctHUGEFILE */


#ifdef ctMXLOGS

/*
** multiple log sets
*/

#include "cttran_x.h"

#else

/*
** single log set
*/

#include "cttran_s.h"

#endif

#include "ctfunt.h"

#endif /* CTTRANH */

/* end of cttran.h */

