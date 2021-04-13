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

#ifdef 	ctCTAPPX_C /* if included by ctappx.c */
#ifndef ctMTFPG
#ifdef  ctLOCLIB
#ifdef  UNIFRMAT
#ifndef ctUNFMH
#define extUNFM
#endif /* ifndef ctUNFMH */
#endif /* ifdef UNIFRMAT */
#endif /* ifdef ctLOCLIB */
#endif /* ifndef ctMTFPG */
#endif /* ifdef ctCTAPPX_C */

#ifdef 	ctCTRSRC_C /* if included by ctrsrc.c */
#ifndef ctMTFPG
#ifdef  ctLOCLIB
#ifdef  UNIFRMAT
#ifndef ctUNFMH
#define extUNFM
#endif /* ifndef ctUNFMH */
#endif /* ifdef  UNIFRMAT */
#endif /* ifdef  ctLOCLIB */
#endif /* ifndef ctMTFPG */
#endif /* ifdef  ctCTAPPX_C */

#ifdef ctCTUNF2_C
#ifdef UNIFRMAT
#ifndef ctUNFMH
#define extUNFM
#endif /* ifndef ctUNFMH */
#endif /* ifdef UNIFRMAT */
#endif /* ifdef ctCTUNF2_C */

#ifndef ctUNFMH
/* Offset of fldr field in CTDBFLDR structure. */
#define ctdbDFLDfldrOffset	20

/* Size of CTFLDX structure. */
#define ctdbDFLDfldxSize	32
#endif

#ifdef extUNFM
#define ctUNFMH
extern ConvMap cthdrcmap;
extern ConvBlkN cthdrcfld[];
extern ConvMap cthdrcmap8;
extern ConvBlkN cthdrcfld8[];
extern ConvMap ctrescmap;
extern ConvBlkN ctrescfld[];
extern ConvMap ctrescmap8;
extern ConvBlkN ctrescfld8[];
extern ConvMap ctnodcmap;
extern ConvBlkN ctnodcfld[];
extern ConvMap ctnodcmap8;
extern ConvBlkN ctnodcfld8[];
extern ConvMap ctvarcmap;
extern ConvBlkN ctvarcfld[];
extern ConvMap ctsupcmap;
extern ConvBlkN ctsupcfld[];
extern ConvMap ctsupcmap8;
extern ConvBlkN ctsupcfld8[];
extern ConvMap ctmapcmap;
extern ConvBlkN ctmapcfld[];
extern ConvMap ctblkcmap;
extern ConvBlkN ctblkcfld[];
#ifdef ctFeatXTDFLDTYP
extern ConvMap ctblkcmap2;
extern ConvBlkN ctblkcfld2[];
#endif
extern ConvMap ctdelcmap;
extern ConvBlkN ctdelcfld[];
extern ConvBlkN ctdelcfld8[];
extern ConvMap ctsctcmap;
extern ConvBlkN ctsctcfld[];
extern ConvMap ctcamcmap;
extern ConvBlkN ctcamcfld[];
extern ConvMap ctsgmcmap;
extern ConvBlkN ctsgmcfld[];
extern ConvMap ctseqcmap;
extern ConvBlkN ctseqcfld[];
extern ConvMap ctfdfcmap;
extern ConvBlkN ctfdfcfld[];
extern ConvMap ctfilcmap;
extern ConvBlkN ctfilcfld[];
extern ConvMap ctidxcmap;
extern ConvBlkN ctidxcfld[];
extern ConvMap ctfilcmap2;
extern ConvBlkN ctfilcfld2[];
extern ConvMap ctsegcmap;
extern ConvBlkN ctsegcfld[];
extern ConvMap ctcihcmap;
extern ConvBlkN ctcihcfld[];
extern ConvMap ctcibcmap;
extern ConvBlkN ctcibcfld[];
extern ConvMap ctdbDFLDcmap;
extern ConvBlkN ctdbDFLDcfld[];
extern ConvMap ctdbDPADcmap;
extern ConvBlkN ctdbDPADcfld[];
#endif
/***************************************************************************/

/***************************************************************************/
#ifndef ctUNFMH
#define ctUNFMH

ConvMap cthdrcmap   = { 0,1,0,0,0,46,7 };
ConvBlkN cthdrcfld[] = {
			{4,CT_INT4,9},
			{2,CT_INT2,7},
			{1,CT_CHAR,7},
			{2,CT_INT2,3},
			{4,CT_INT4,4},
			{2,CT_INT2,3},
			{4,CT_INT4,6}
		};

ConvMap cthdrcmap8   = { 0,1,0,0,0,106 + 4 * ctMAXSEGdistinct,13};
ConvBlkN cthdrcfld8[] = {
			{4,CT_INT4,9},
			{2,CT_INT2,7},
			{1,CT_CHAR,7},
			{2,CT_INT2,3},
			{4,CT_INT4,4},
			{2,CT_INT2,3},
			{4,CT_INT4,6},
			{4,CT_INT4,31},
			{2,CT_INT2,3},
			{4,CT_INT4,17 + 4 * ctMAXSEGdistinct},
			{FC_DAR_NBR,CT_CHAR,0},
			{4,CT_INT4,1},
			{8,CT_INT8,2}
		};

ConvMap ctrescmap   = { 0,1,0,0,0,8,2 };
ConvBlkN ctrescfld[] = {
			{2,CT_INT2U,0},
			{4,CT_INT4,6}
		};

ConvMap ctrescmap8   = { 0,1,0,0,0,8,4 };
ConvBlkN ctrescfld8[] = {
			{2,CT_INT2U,0},
			{4,CT_INT4,2},
			{8,CT_INT8,1},
			{4,CT_INT4,1}
		};

ConvMap ctnodcmap   = { 0,1,0,0,0,8,3 };
ConvBlkN ctnodcfld[] = {
			{4,CT_INT4,1},
			{2,CT_INT2,3},
			{1,CT_CHAR,1}
		};

ConvMap ctnodcmap8   = { 0,1,0,0,0,12,4 };
ConvBlkN ctnodcfld8[] = {
			{4,CT_INT4,1},
			{2,CT_INT2,3},
			{1,CT_CHAR,3},
			{4,CT_INT4,1}
		};

ConvMap ctvarcmap   = { 0,1,0,0,0,3,2 };
ConvBlkN ctvarcfld[] = {
			{2,CT_INT2U,0},
			{4,CT_INT4,1}
		};

ConvMap ctsupcmap   = { 0,1,0,0,0,5,3 };
ConvBlkN ctsupcfld[] = {
			{2,CT_INT2U,0},
			{4,CT_INT4,1},
			{4,CT_INT4,1}
		};

ConvMap ctsupcmap8   = { 0,1,0,0,0,6,3 };
ConvBlkN ctsupcfld8[] = {
			{2,CT_INT2U,0},
			{4,CT_INT4,1},
			{4,CT_INT4,2}
		};

ConvMap ctmapcmap   = { 0,1,0,0,0,7,2 };
ConvBlkN ctmapcfld[] = {
			{1,CT_CHARU,3},
			{4,CT_INT4,2}
		};

ConvMap ctblkcmap   = { 0,1,0,0,0,3,2 };
ConvBlkN ctblkcfld[] = {
			{2,CT_INT2U,0},
			{1,CT_CHARU,1}
		};

#ifdef ctFeatXTDFLDTYP
ConvMap ctblkcmap2  = { 0,1,0,0,0,4,2 };
ConvBlkN ctblkcfld2[] = {
			{2,CT_INT2U,1},
			{1,CT_CHARU,1}
		};
#endif

ConvMap ctdelcmap   = { 0,1,0,0,0,2,2 };
ConvBlkN ctdelcfld[] = {
			{1,CT_CHARU,0},
			{4,CT_INT4,0}
		};
ConvBlkN ctdelcfld8[]= {
			{1,CT_CHARU,0},
			{8,CT_INT4,0}
		};

ConvMap ctsctcmap   = { 0,1,0,0,0,3,2 };
ConvBlkN ctsctcfld[] = {
			{FCRNAM_LEN,CT_FSTRING,0},
			{4,CT_INT4U,1}
		};

ConvMap ctcamcmap   = { 0,1,0,0,0,7,2 };
ConvBlkN ctcamcfld[] = {
			{FCRNAM_LEN,CT_FSTRING,0},
			{4,CT_INT4U,5}
		};

ConvMap ctsgmcmap   = { 0,1,0,0,0,7,2 };
ConvBlkN ctsgmcfld[] = {
			{FCRNAM_LEN,CT_FSTRING,0},
			{4,CT_INT4U,5}
		};

ConvMap ctseqcmap   = { 0,1,0,0,0,256,1 };
ConvBlkN ctseqcfld[] = {
			{2,CT_INT2,255}
		};

ConvMap ctfdfcmap   = { 0,1,0,0,0,99,66};
ConvBlkN ctfdfcfld[] = {
			{FCRNAM_LEN,CT_FSTRING,0},
			{4,CT_INT4U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1},
			{4,CT_INT4U,0},
			{2,CT_INT2U,1}
		};

ConvMap ctfilcmap   = { 0,1,0,0,0,8,2};
ConvBlkN ctfilcfld[] = {
			{4,CT_INT4U,0},
			{2,CT_INT2,6}
		};

ConvMap ctidxcmap   = { 0,1,0,0,0,6,1};
ConvBlkN ctidxcfld[] = {
			{2,CT_INT2,5}
		};

#ifdef ctFeatMAXFILE32
/* conversion map for IFIL stream with 4-byte file numbers */
ConvMap ctfilcmap2   = { 0,1,0,0,0,12,5};
/* conversion block for IFIL stream with 4-byte file numbers */
ConvBlkN ctfilcfld2[] = {
			{4,CT_INT4U,0}, /* pfilnam */
			{4,CT_INT4,0}, /* dfilno */
			{2,CT_INT2,5}, /* dreclen through ifilmod */
			{4,CT_INT4U,2}, /* ix, rfstfld, rlstfld */
			{4,CT_INT4,0} /* tfilno */
		};
#else
/* conversion map for IFIL stream with 2-byte file numbers */
ConvMap ctfilcmap2   = { 0,1,0,0,0,12,4};
/* conversion block for IFIL stream with 2-byte file numbers */
ConvBlkN ctfilcfld2[] = {
			{4,CT_INT4U,0}, /* pfilnam */
			{2,CT_INT2,6}, /* dfilno through ifilmod */
			{4,CT_INT4U,2}, /* ix, rfstfld, rlstfld */
			{2,CT_INT2,0} /* tfilno */
		};
#endif

ConvMap ctsegcmap   = { 0,1,0,0,0,3,1};
ConvBlkN ctsegcfld[] = {
			{2,CT_INT2,2}
		};

ConvMap ctcihcmap   = { 0,1,0,0,0,2,1 };
ConvBlkN ctcihcfld[] = {
			{2,CT_INT2,1}
		};

ConvMap ctcibcmap   = { 0,1,0,0,0,3,2 };
ConvBlkN ctcibcfld[] = {
			{2,CT_INT2,1},
			{4,CT_INT4,0}
		};

/*
** Conversion map for CTDB extended field information resource.
** See CTDBFLDR and CTFLXD structures in ctdbport.h.
*/

ConvMap ctdbDFLDcmap   = { 0,1,0,0,0,4,1};
ConvBlkN ctdbDFLDcfld[] = {
			{2,CT_INT2,3}	/* nullflag, prec, scale, binflag  */
		};

/*
** Conversion map for CTDB field padding resource.
** See CTDBFPAD structure in ctdbport.h.
**
** NOTE: We define the high/low fields as CT_FSTRING fields here so that
** we do not convert these fields, in order to be consistent with the code
** in _ctdbGetPadResource().
*/

ConvMap ctdbDPADcmap   = { 0,1,0,0,0,6,4};
ConvBlkN ctdbDPADcfld[] = {
			{FCRNAM_LEN,CT_FSTRING,0},	/* rname	   */
			{4,CT_INT4U,0},			/* version	   */
			{4,CT_FSTRING,1},		/* high/low	   */
			{4,CT_INT4,1}			/* padchar/dlmchar */
		};

/*
** Conversion map for record update callback resource.
** See RUCBRES structure in ctstrc.h.
*/
ConvMap ctruccmap   = { 0,1,0,0,0,4,2 };
ConvBlkN ctruccfld[] = {
			{FCRNAM_LEN,CT_FSTRING,0}, /* resnam */
			{4,CT_INT4U,2} /* verson, totlen, numrucb */
		};

/*
** Conversion map for record update callback resource.
** See RUCBLST structure in ctstrc.h.
*/
ConvMap ctrclcmap   = { 0,1,0,0,0,3,1 };
ConvBlkN ctrclcfld[] = {
			{4,CT_INT4U,2} /* verson, calltm, varlen */
		};

/*
** Conversion map for background load status resource.
** See BGLDRES structure in ctport.h.
*/
ConvMap ctblrcmap   = { 0,1,0,0,0,3,2 };
ConvBlkN ctblrcfld[] = {
			{FCRNAM_LEN,CT_FSTRING,0}, /* resnam */
			{4,CT_INT4U,1} /* verson, numbgl */
		};

/*
** Conversion map for background load status resource.
** See BGLDINF structure in ctport.h.
*/
ConvMap ctblicmap   = { 0,1,0,0,0,11,3 };
ConvBlkN ctblicfld[] = {
			{8,CT_INT8,4}, /* queuedtime, statustime, offset, npass, nfail */
			{4,CT_INT4U,3}, /* status, errcod, curpct, pad */
			{BGLDIDZ,CT_FSTRING,1} /* cbname, loadid */
		};

#endif /* ifndef ctUNFMH */
/**************************************************************************/

