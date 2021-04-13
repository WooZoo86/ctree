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

#define P1_NO_LEN	0
#define P1_RCKLEN	1
#define P1_VRKLEN	2
#define P1_KEYLEN	3
#define P1_RECLEN	4
#define P1_VARLEN	5
#define P1_OPNLEN	6
#define P1_ISMLEN	7
#define P1_IFLLEN	8
#define P1_LOGLEN	9
#define P1_CRELEN	10
#define P1_ESTLEN	11
#define P1_TRNLEN	12
#define P1_KYSLEN	13
#define P2_KEYLEN	14
#define P2_RECLEN	15
#define P1_RKYLEN	16
#define P2_RKYLEN	17
#define P1_RORLEN	18
#define A2_RETFIL	19
#define A2_LOGOFF	20
#define P1_RESLEN	21
#define P2_VARLEN	22
#define P1_BATLEN	23
#define P1_CTULEN	24
#define P1_SEQLEN	25
#define A2_FNCRET	26
#define P1_LNGLEN	27
#define P1_DEFLEN	28
#define P1_PADLEN	29
#define P1_DDXLEN	30
#define P1_PWZLEN	31
#define P2_DARLEN	32
#define P1_COMLEN	33
#define P1_GIFLEN	34
#define P1_USRLLN	35
#define P1_USRINF	36
#define P1_IDZLEN	37
#define P1_IOPLEN	38
#define P1_STRING	39
#define P1_STRSHR	40
#define P1_CFGLEN	41
				/*
				** reserve 42 through 48 for ctCUSTOM use
				*/
#define P1_CUSOP1	42	/* ptr1 custom length */
#define P1_CUSOP2	43
#define P2_CUSOP2	44

#define P1_SEGLEN	49
#define P1_HSTLEN	50
#define P1_KVRLEN	51
#define P1_RVRLEN	52
#define P2_PVRLEN	53
#define P1_IOPXLN	54
#define P1_RTSCRP	55
#define P1_SESSLEN	56
#define P2_SESSLEN	57
#define A2_TRNFIL	58
#define P1_SEPLNG	59
#define P2_SEPLNG	60
#define P1_ALTDEFCHK	61
#define P1_PTALEN	62	/* partition admin len (name or key)	*/
#define A3_TRNFIL	63	/* PUTHDR IICTxtd commit/abort		*/
#define P12_LAST	63	/* last valid inp/out typ value		*/

#define SP_SETCUR	0x0001	/* maintain local current ISAM pos	*/
#define SP_ZLEN		0x0002	/* zero output length on error		*/
#define SP_LOWVAR	0x0004	/* low level auto var length		*/
#define SP_CLSFIL	0x0008	/* close or deletes files		*/
#define SP_APPXFN	0x0010	/* special ctappx processing		*/
#define SP_BLKCLI	0x0020	/* block client from calling function	*/
/*			0x0040	   future use				*/
/*			0x0080	   future use				*/
#define SP_PLEN		0x0100	/* input/output plen argument		*/
#define SP_CHKMAP	0x0200	/* check segment & key maps		*/
#define SP_RTREE	0x0400	/* r-tree launch function		*/
#define SP_SETHGH	0x1000	/* ctSETHGH on request			*/
#define SP_GETHGH	0x2000	/* ctGETHGH on response			*/
#define SP_WRTSIZ	0x4000	/* check that qbsz <= ctusrlen		*/

#define SP_ISMRET	(SP_SETCUR | SP_ZLEN)
#define SP_ISMVAR	(SP_SETCUR | SP_PLEN)
#define SP_APPMAP	(SP_APPXFN | SP_CHKMAP)


typedef struct {
	COUNT	numarg;
	COUNT	inptyp;
	COUNT	outtyp;
	COUNT	spltyp;
} FNARRAY;

#if (defined(ctSQLMTFPG) && defined(ctSQLSRVR))
/*
** For ctreex() in c-treeSQL Server with SQL FPUTFGET file access, block calls
** by external clients to open and create files.
*/
#define ctBLKCRE SP_BLKCLI /* do not allow clients to call functions that create files */
#define ctBLKOPN SP_BLKCLI /* do not allow clients to call functions that open files */
#else
/*
** For standard server, no limits on calls by external clients.
*/
#define ctBLKCRE 0 /* allow clients to call functions that create files */
#define ctBLKOPN 0 /* allow clients to call functions that open files */
#endif

FNARRAY ctfunc[] = {
	{0},						/* NOFUNCT*/
	{6},						/* PUTFIL */
	{6,0,0,SP_SETCUR},				/* UPDCURI */
	{1,0,A2_FNCRET,SP_CLSFIL},			/* DELFIL */
	{1},						/* LKISAM */
	{1},						/* DELREC */
	{1},						/* ALCSET */
	{1},						/* CHGSET */
	{1},						/* DELVREC */
	{0,0,A2_LOGOFF,SP_CLSFIL},			/* CLISAM */
	{0,0,A2_LOGOFF},				/* STPUSR */
	{0},						/* FRESET */
	{1,0,A2_FNCRET,SP_CLSFIL},			/* CLSFIL */
	{1,0,A2_TRNFIL,SP_SETCUR},			/* TRANEND */
	{1,0,A2_TRNFIL,SP_SETCUR},			/* TRANRST */
	{0,0,A2_TRNFIL,SP_SETCUR},			/* TRANABT */
	{0},						/* TRANCLR */
	{1,0,A2_FNCRET,SP_CLSFIL | SP_APPMAP},		/* CLRFIL */
	{1,0,A2_FNCRET,SP_CLSFIL | SP_APPMAP},		/* DELRFIL */
	{1},						/* ALCBAT */
	{1},						/* CHGBAT */
	{0},						/* FREBAT */
	{1},						/* PERFORM */
	{2,0,P1_USRLLN},				/* USERLIST */
	{2,0,P1_USRINF},				/* USERINFO */
	{2,P1_IDZLEN},					/* CTKLUSR */
	{0},						/* CTTESTFUNC */
	{1,0,0,SP_SETCUR},				/* CHGICON */
	{1},						/* CLSICON */
	{1},						/* CTFLUSH */
	{0},						/* CTCHKPNT */
	{1,0,A2_TRNFIL,SP_SETCUR},			/* TRANABTX */
	{1},						/* CHGHST */
	{0},						/* FREHST */
	{0},						/* SAVPCLR */
	{1},						/* TESTHUGE */
	{2,P1_STRING},					/* ctRENFIL */
	{2,P1_STRING},					/* UPDCIDX */
	{2,P1_STRING},					/* SETFLTR */
	{2,P1_RCKLEN,0,SP_SETCUR | SP_APPMAP},		/* ADDUSR */
	{4,P1_RCKLEN,P2_DARLEN,SP_SETCUR | SP_APPMAP},	/* ADDREC */
	{4,P1_RCKLEN,P2_DARLEN,SP_SETCUR},		/* RWTREC */
	{2,0,P1_RORLEN,SP_ISMRET},			/* NXTREC */
	{2,0,P1_RORLEN,SP_ISMRET},			/* PRVREC */
	{2,0,P1_RORLEN,SP_ISMRET},			/* FRSREC */
	{2,0,P1_RORLEN,SP_ISMRET},			/* LSTREC */
	{2,0,P1_RECLEN,SP_ISMRET},			/* RRDREC */
	{2,0,P1_RKYLEN,SP_ISMRET},			/* NXTSET */
	{2,0,P1_RKYLEN,SP_ISMRET},			/* PRVSET */
	{2,P1_SEQLEN},					/* SETALTSEQ */
	{2,0,P1_SEQLEN},				/* GETALTSEQ */
	{3,P1_DEFLEN},					/* SETDEFBLKX */
	{6,0,P1_RKYLEN,SP_ISMRET},			/* MIDSET */
	{6,0,0,SP_APPXFN},				/* ..PUTDODAX.. */
	{2,P1_PADLEN},					/* SETVARBYTS */
	{6,P1_KEYLEN,P2_PVRLEN,SP_ISMVAR},		/* FRSVSET */
	{6,P1_KEYLEN,P2_PVRLEN,SP_ISMVAR},		/* LSTVSET */
	{6,0,P1_KVRLEN,SP_ISMVAR},			/* MIDVSET */
	{0},						/* TRANRDY */
	{5,0,P1_VARLEN},				/* SYSMON */
	{5,P1_VARLEN,0,SP_LOWVAR | SP_SETHGH | SP_WRTSIZ},/* WRTVREC */
	{5,0,P1_VARLEN,SP_LOWVAR | SP_SETHGH},		/* RDVREC */
	{3,0,P1_RECLEN,SP_LOWVAR | SP_ZLEN | SP_SETHGH},/* REDREC */
	{3,P1_RECLEN,0,SP_SETHGH},			/* WRTREC */
	{5,P1_KYSLEN,0,SP_SETCUR | SP_SETHGH},		/* SETCURI */
	{3,0,0,SP_SETHGH},				/* RETREC */
	{3,0,0,SP_SETHGH},				/* RETVREC */
	{3,0,P1_RKYLEN,SP_ISMRET | SP_SETHGH},		/* reset_cur */
	{5,0,0,SP_SETCUR | SP_SETHGH},			/* SETCURI2 */
	{5,P1_KEYLEN,P2_PVRLEN,SP_ISMVAR},		/* EQLVREC */
	{5,P1_KEYLEN,P2_PVRLEN,SP_ISMVAR},		/* GTEVREC */
	{5,P1_KEYLEN,P2_PVRLEN,SP_ISMVAR},		/* LTEVREC */
	{5,P1_KEYLEN,P2_PVRLEN,SP_ISMVAR},		/* GTVREC */
	{5,P1_KEYLEN,P2_PVRLEN,SP_ISMVAR},		/* LTVREC */
	{6,0,P1_VARLEN},				/* GETMNAME */
	{6,0,P1_VARLEN},				/* GETNAM */
	{5,0,P1_VARLEN},				/* GETSEG */
	{5,0,P1_VARLEN},				/* GETMAP */
	{6,P1_VARLEN,0,SP_SETCUR},			/* SECURITY */
	{5,P1_VARLEN},					/* SYSLOG   */
	{6,P1_KEYLEN,P2_RKYLEN,SP_ISMRET},		/* FRSSET */
	{6,P1_KEYLEN,P2_RKYLEN,SP_ISMRET},		/* LSTSET */
	{4,P1_KEYLEN,P2_RKYLEN,SP_ISMRET},		/* EQLREC */
	{4,P1_KEYLEN,P2_RKYLEN,SP_ISMRET},		/* GTEREC */
	{4,P1_KEYLEN,P2_RKYLEN,SP_ISMRET},		/* LTEREC */
	{4,P1_KEYLEN,P2_RKYLEN,SP_ISMRET},		/* GTREC */
	{4,P1_KEYLEN,P2_RKYLEN,SP_ISMRET},		/* LTREC */
	{3,0,P1_RECLEN,SP_ISMRET | SP_SETHGH},		/* REDIREC */
	{1,0,A2_LOGOFF},				/* STPUSRA */
	{2,P1_PWZLEN,0,SP_SETCUR},			/* CHGUSR */
	{2,P1_ISMLEN,A2_RETFIL},			/* CREISAM */
	{2,P1_ISMLEN,A2_RETFIL},			/* OPNISAM */
	{1},						/* TRANISO */
	{2,P1_IFLLEN,0,SP_CLSFIL | SP_APPMAP},		/* DELIFIL */
	{2,P1_IFLLEN,0,ctBLKOPN},			/* RBLIFIL */
	{2,P1_IFLLEN,A2_RETFIL,ctBLKCRE},		/* CREIFIL */
	{2,P1_IFLLEN,0,SP_CLSFIL | SP_APPMAP},		/* CLIFIL */
	{2,P1_IFLLEN,A2_RETFIL,ctBLKOPN},		/* OPNIFIL */
	{2,P1_IFLLEN,A2_RETFIL,ctBLKCRE},		/* PRMIIDX */
	{2,P1_IFLLEN,A2_RETFIL,ctBLKCRE},		/* TMPIIDX */
	{2,P1_IFLLEN,0,ctBLKOPN},			/* PUTIFIL */
	{2,P1_IFLLEN,0,ctBLKOPN},			/* CMPIFIL */
	{2,P1_IFLLEN,0,ctBLKOPN},			/* EXPIFIL */
	{2,P1_IFLLEN,0,ctBLKOPN},			/* RBLIIDX */
	{5,0,P1_RVRLEN,SP_ISMVAR},			/* NXTVREC */
	{5,0,P1_RVRLEN,SP_ISMVAR},			/* PRVVREC */
	{5,0,P1_RVRLEN,SP_ISMVAR},			/* FRSVREC */
	{5,0,P1_RVRLEN,SP_ISMVAR},			/* LSTVREC */
	{5,0,P1_KVRLEN,SP_ISMVAR},			/* NXTVSET */
	{5,0,P1_KVRLEN,SP_ISMVAR},			/* PRVVSET */
	{2,P1_LOGLEN},					/* INTREE */
	{2,P1_LOGLEN},					/* INTISAM */
	{3,P1_STRING},					/* SETFLTRN */
	{3},						/* RESETFLTR */
	{2,P1_IFLLEN,0,ctBLKOPN},			/* RENIFIL */
	{2,P1_STRING},					/* SETNODE */
	{1},						/* UNDOFLEX */
	{2,P1_SEGLEN},					/* ctSETSEG */
	{6,P1_STRING},					/* ctLOKDMP */
	{5,P1_VRKLEN,0,SP_SETCUR | SP_WRTSIZ},		/* RWTPREC */
	{5,P1_VRKLEN,P2_DARLEN,SP_SETCUR | SP_APPMAP | SP_WRTSIZ},/* ADDVREC */
	{5,P1_VRKLEN,P2_DARLEN,SP_SETCUR | SP_WRTSIZ},	/* RWTVREC */
	{5,0,P1_VARLEN,SP_SETCUR | SP_LOWVAR},		/* REDVREC */
	{2,P1_RESLEN},					/* DELRES */
	{1},						/* ENARES */
	{5,P1_VARLEN,0,SP_WRTSIZ},			/* UPDRES */
	{5,P1_VARLEN,0,SP_WRTSIZ},			/* ADDRES */
	{5,P1_VARLEN,0,SP_WRTSIZ},			/* PUTCRES */
	{0},						/* NOFUNCT */
	{6,P1_PTALEN},					/* PTADMIN */
	{6,P1_KEYLEN,0,SP_SETHGH},			/* ADDKEY */
	{6,P1_KEYLEN,0,SP_SETHGH},			/* LOADKEY */
	{3,P1_KEYLEN,0,SP_SETHGH},			/* DELCHK */
	{1},						/* FREBATN */
	{1},						/* FRESETN */
	{1},						/* FREHSTN */
	{5,0,0,SP_APPXFN},				/* SETOPS */
	{1},						/* FRERNG */
	{2,0,P1_RKYLEN,SP_ISMRET},			/* FRSRNG */
	{5,0,P1_KVRLEN,SP_ISMVAR},			/* FRSVRNG */
	{2,P1_CRELEN,A2_RETFIL},			/* CREDAT */
	{2,P1_CRELEN,A2_RETFIL},			/* CREIDX */
	{2,P1_CRELEN,A2_RETFIL},			/* CREMEM */
	{1,0,A2_FNCRET,SP_CLSFIL},			/* ctDROPIDX */
	{2,0,P1_RKYLEN,SP_ISMRET},			/* LSTRNG */
	{5,0,P1_KVRLEN,SP_ISMVAR},			/* LSTVRNG */
	{2,0,P1_RKYLEN,SP_ISMRET},			/* NXTRNG */
	{5,0,P1_KVRLEN,SP_ISMVAR},			/* NXTVRNG */
	{2,0,P1_RKYLEN,SP_ISMRET},			/* PRVRNG */
	{5,0,P1_KVRLEN,SP_ISMVAR},			/* PRVVRNG */
	{4,P1_KEYLEN,P2_KEYLEN,SP_GETHGH},		/* GTEKEY */
	{4,P1_KEYLEN,P2_KEYLEN,SP_GETHGH},		/* GTKEY */
	{4,P1_KEYLEN,P2_KEYLEN,SP_GETHGH},		/* LTKEY */
	{4,P1_KEYLEN,P2_KEYLEN,SP_GETHGH},		/* LTEKEY */
	{3,P1_KEYLEN,0,SP_GETHGH},			/* DELBLD */
	{3,P1_KEYLEN,0,SP_GETHGH},			/* EQLKEY */
	{3,0,P1_KEYLEN,SP_GETHGH},			/* FRSKEY */
	{3,0,P1_KEYLEN,SP_GETHGH},			/* LSTKEY */
	{3,0,0,SP_APPXFN | SP_GETHGH},			/* GETCURP */
	{3,0,0,SP_GETHGH},				/* NEWREC */
	{3,0,0,SP_GETHGH},				/* DATENT */
	{3,0,0,SP_GETHGH},				/* IDXENT */
	{3,0,0,SP_GETHGH},				/* SERIALNUM */
	{3,0,0,SP_GETHGH},				/* TRANBEG */
	{3,0,P1_KEYLEN,SP_GETHGH},			/* NXTKEY */
	{3,0,P1_KEYLEN,SP_GETHGH},			/* PRVKEY */
	{6,P1_RESLEN,P2_VARLEN,SP_GETHGH},		/* GETRES */
	{3,P1_DDXLEN},					/* ctdidx */
	{3,0,0,SP_GETHGH},				/* ctDISTINCTest */
#ifdef ctPREV_66A3_CTUSER
	{3,P1_STRING,0,SP_SETCUR},			/* CTUSER */
#else
	{5,P1_STRING,P2_VARLEN,SP_SETCUR}, 		/* CTUSER */
#endif
	{6,0,0,SP_APPXFN | SP_GETHGH},			/* GETFIL */
	{6,P1_SEPLNG,P2_SEPLNG,SP_SETHGH | SP_GETHGH},	/* ctSEPLNG */
	{5,P1_STRING,P2_VARLEN,SP_SETCUR}, 		/* CTUSERXold */
	{5,P1_STRING,P2_VARLEN,SP_SETCUR}, 		/* CTSQLCTL */
	{5,P1_STRING,P2_VARLEN,SP_SETCUR}, 		/* CTSRVCTL */
	{6,0,0,SP_GETHGH},				/* ctDISTINCTset */
	{5,P1_CTULEN,P2_VARLEN,SP_SETCUR}, 		/* CTUSERX */
	{6,0,0,0},					/* ctImpersonateTask */
	{0},						/* NOFUNCL */
	{0},						/* NOFUNCL */
	{5,0,0,SP_LOWVAR | SP_SETHGH},			/* GTVLEN */
	{5,0,0,SP_LOWVAR},				/* GETVLEN */
	{5,P1_ALTDEFCHK,P1_GIFLEN},			/* GETIFILX */
	{6,P1_ALTDEFCHK,P1_LNGLEN},			/* GETDODAX */
	{5,0,P1_LNGLEN},				/* GETCRES */
	{5,0,P1_LNGLEN},				/* GETCIDX */
	{0},						/* NOFUNCV */
	{0},						/* NOFUNCV */
	{2,P1_KEYLEN,P1_KEYLEN,SP_APPXFN | SP_SETHGH},	/* TFRMKEY */
	{5,0,P1_KEYLEN},				/* GETCURK */
	{2,0,P1_KEYLEN},				/* GETCURKL */
	{6,P1_BATLEN,P2_VARLEN},			/* BATSETX */
	{2,P1_OPNLEN},					/* CTSBLDX */
	{5},						/* TSTVREC */
	{5,P1_COMLEN},					/* COMMBUF */
	{0},						/* NOFUNCT */
	{3,P1_OPNLEN,A2_RETFIL,ctBLKCRE},		/* OPNRFIL */
	{5,P1_STRSHR,P1_VARLEN},			/* TMPNAME */
#ifdef ctFeatRTG_API
	{4,P1_CUSOP2,P2_CUSOP2,SP_GETHGH | SP_SETCUR},	/* RTG */
#else
	{0},						/* NOFUNCT */
#endif
	{5,P1_VARLEN},					/* DYNDMP */
	{6,0,P1_KEYLEN,SP_GETHGH},			/* FRCKEY */
	{2,0,P1_TRNLEN},				/* AVLFILNUM */
	{2,P1_OPNLEN,A2_RETFIL,ctBLKOPN},		/* OPNFIL */
	{6,P1_BATLEN,P2_VARLEN},			/* BATSET */
	{6,0,0,SP_SETHGH},				/* LOKREC */
	{3,P1_ESTLEN,0,SP_GETHGH},			/* ESTKEY */
	{5,0,0,SP_GETHGH},				/* NEWVREC */
	{2,0,P1_TRNLEN},				/* TRANSAV */
	{3,P1_TRNLEN},					/* TRANBAK */
	{5,P1_VARLEN},					/* SETFNDVAL */
	{2,0,P1_IOPLEN},				/* IOPERFORMANCE */
	{2,P1_OPNLEN},					/* CLNIDXX */
	{3,P1_ESTLEN,0,SP_GETHGH},			/* RNGENT */
	{5,P1_KEYLEN,P2_KEYLEN,SP_GETHGH},		/* ORDKEY */
	{6,0,P1_TRNLEN},				/* OPNICON */
	{2,0,P1_CFGLEN},				/* SYSCFG */
#ifdef A3_TRNFILsup
	{6,0,A3_TRNFIL,SP_SETCUR | SP_SETHGH},		/* PUTHDR */
#else
	{6,0,0,SP_SETCUR | SP_SETHGH},			/* PUTHDR */
#endif
	{3,P1_LOGLEN},					/* CUST_LOGON */
	{3,0,A2_LOGOFF,SP_CLSFIL},			/* CUST_LOGOFF */
	{3,P1_CUSOP1,0,SP_GETHGH | SP_SETCUR},		/* CUST_OPC1 */
	{4,P1_CUSOP2,P2_CUSOP2,SP_GETHGH | SP_SETCUR},	/* CUST_OPC2 */
	{6},						/* CUST_OPC3 */
	{6},						/* CUST_OPC4 */
	{6,P1_HSTLEN,P2_VARLEN,SP_APPXFN | SP_SETHGH},	/* CTHIST */
	{2,0,P1_IOPXLN},				/* IOPERFORMANCEX*/
	{5,0,P1_RVRLEN,SP_ISMVAR | SP_SETHGH},		/* REDIVREC */
	{5,0,P1_RVRLEN,SP_ISMVAR | SP_SETHGH},		/* reset_cur2 */
	{6,P1_RTSCRP,P2_VARLEN,SP_RTREE},		/* RTSCRIPT */
	{5,P1_VARLEN},					/* ctSETENCRYPT */
	{4,P1_SESSLEN,P2_SESSLEN},			/* SESSVAL */
	{4,P1_SESSLEN,P2_SESSLEN},			/* SESSINC */
	{2,0,P1_TRNLEN},				/* SPCLSAV */
	{0}						/* NOFUNCT */
	};

#ifdef ctFeatFNCMEMSTATS
#include "ctgvar.h"
#include "ctparm.h"

FNCMEM ctfuncmem[MXU2][CTI_MXFN+1];
#endif

NINT ctsepfunc[] = {
	0,				/* unused */
	0,				/* PUTKSEGDEF */
	0,				/* GETKSEGDEF */
	0,				/* XFMKSEGDEF */
	0,				/* ctunic */
	0,				/* GETXCREBLK */
	0,				/* CTFLUSHX */
	0,				/* CTASYNC */
	0,				/* ctksegswpchk */
	0,				/* ctSNAPSHOT */
	0,				/* ctSYSPUT */
	ctBLKOPN,			/* ctCLSNAM */
	0,				/* ctSysQueueOpen */
	0,				/* ctSysQueueClose */
	0,				/* ctSysQueueWrite */
	0,				/* ctSysQueueLIFOWrite */
	SP_ZLEN,			/* ctSysQueueRead */
	0,				/* ctSysQueueMlen */
	0,				/* ctSysQueueCount */
	0,				/* ctNotify */
	0,				/* ALCRNG */
	SP_SETCUR | SP_ZLEN | SP_PLEN,	/* BLKIREC */
	0,				/* TRANUSR */
	0,				/* ctReplSetPosByLogPos */
	0,				/* ctReplSetPosByTime */
	0,				/* ctReplGetFileName */
	0,				/* ctReplGetNextChange */
	0,				/* ctReplPersistMinLog */
	0,				/* SETCBRBL */
	ctBLKOPN,			/* ctFILMTX */
	0,				/* ctLOKLST */
	ctBLKOPN,			/* ctFILBLK */
	0,				/* ctSETCFG */
	0,				/* ctFILWCD */
	0,				/* ctQUIET */
	0,				/* ctLOKTIMOUT */
	0,				/* ctUPDTICU */
	0,				/* ctGetOpenFiles */
	0,				/* ctGetFileUsers */
	0,				/* ctGetFileLocks */
	0,				/* ctLOKDYN */
	0,				/* ctReplAgentOp */
	ctBLKOPN,			/* ctTransferFile */
	0,				/* ESTRNG */
	0,				/* ctSEQUENCE */
	0,				/* ctMASTERCTL */
	0,				/* ctDISTINCTestXtd */
	0,				/* ctDISTINCTsetXtd */
	ctBLKOPN,			/* ctVERIFYidx */
	0,				/* addIDfield */
	0,				/* delIDfield */
	0,				/* getIDfield */
	0,				/* resetIDfield */
	0,				/* wchIDfield */
	0,				/* ctMEMSTAT */
	0,				/* ctSETCOMPRESS */
	0,				/* xtdatrIDfield */
	ctBLKOPN,			/* ctCopyFile */
	ctBLKOPN,			/* ctVerifyFile */
	0,				/* GETFILX */
	0,				/* ctDeferredIndexControl */
	0,				/* ctRecordUpdateCallbackControl */
	0,				/* ctReplSetFileFilter */
	SP_SETCUR,			/* ctFullText */
	0,				/* ctAlterSchema */
	0,				/* ctReplCheckFileFilter */
	0,				/* ctTempDir */
	0,				/* ctReplLogFileResync */
	0,				/* ctGetAccountExpirationTime */
	0,				/* ctGetConnectionInfo */
	0,				/* UpdateRecordOffsetForKey */
	0,				/* USERINFOX */
	0,				/* ctSyncReplControl */
	0,				/* addAutoSysTimeFields */
	0,				/* RemoveAutoSysTimeFields */
	0,				/* WhichAutoSysTimeFields */
	0,				/* UpdateAutoSysTimeFields */
	0,				/* GetFileRegions */
	0,				/* ctGetOpenFilesXtd */
	0,				/* ctReplSetPosByTransactionId */
	0,				/* ctFILELIST */
	0,				/* ctReplReadLogData */
	0,				/* replagentfunction */
	0,				/* ctReplCleanupTranStateKeys */
	0,				/* ctClusterConfig */
	0,				/* ctTruncateFile */
/*
** ctSIBLING_SEPLNG: Add new array entry here with desired attributes.
** NOTE: use the SP_BLKCLI attribute if you want to block an external client
** from calling that function. See the ctBLKOPN macro for example.
*/
	};

typedef TEXT checkSizeOfSepFuncArray[sizeof(ctsepfunc) / sizeof(*ctsepfunc) == ctSEPLNGlimit];

/* end of ctfary.h */
