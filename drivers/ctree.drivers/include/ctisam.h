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

#ifndef CTISAMH
#define CTISAMH

#define ISADD		1
#define ISDEL		2
#define ISRWT		3
#define ISRWTP		4

#ifdef MULTITRD

#ifdef RTREE
#define usrkey(i)	ctis[sOWNR]->s1[i].s1usrkey
#define usrdat(i)	ctis[sOWNR]->s1[i].s1usrdat
#define eusrkey(i)	       pis1->s1usrkey
#define eusrdat(i)	       pis1->s1usrdat
#define srtknm		ctis[sOWNR]->ssrtknm
#define srtdat		ctis[sOWNR]->ssrtdat
#define tmpdat		ctis[sOWNR]->stmpdat
#endif

#define seqbuf		ctis[sOWNR]->sseqbuf
#define seqold		ctis[sOWNR]->sseqold
#define seqlen		ctis[sOWNR]->sseqlen
#define seqkey		ctis[sOWNR]->sseqkey
#define seqnum		ctis[sOWNR]->sseqnum
#define maxqset		ctis[sOWNR]->smaxqset
#define ct_fndval	ctis[sOWNR]->sct_fndval
#define ct_nwrcfg	ctis[sOWNR]->sct_nwrcfg
#define ct_vfsg		ctis[sOWNR]->sct_vfsg
#define ct_ismlk	ctis[sOWNR]->sct_ismlk
#define ct_fndlen	ctis[sOWNR]->sct_fndlen
#ifdef ctFeatRECRLOCK
#define ct_ismrc	ctis[sOWNR]->sct_ismrc
#endif
#define ct_savset	ctis[sOWNR]->sct_savset
#define ct_dtmap(i)	ctis[sOWNR]->s1[i].s1ct_dtmap
#define ct_rvmap(i)	ctis[sOWNR]->s1[i].s1ct_rvmap
#ifdef ctCONDIDX
#define ct_rlkey(i)	ctis[sOWNR]->s1[i].s1ct_rlkey
#endif
#define ct_nlkey(i)	ctis[sOWNR]->s1[i].s1ct_nlkey
#define ct_nlchr(i)	ctis[sOWNR]->s1[i].s1ct_nlchr
#define ct_vfin(i)	ctis[sOWNR]->s1[i].s1ct_vfin
#define ct_sgpos(i,j)	ctis[sOWNR]->s2[i][j].s2ct_sgpos
#define ct_sglen(i,j)	ctis[sOWNR]->s2[i][j].s2ct_sglen
#define ct_sgmod(i,j)	ctis[sOWNR]->s2[i][j].s2ct_sgmod
#define ct_sghnd(i,j)	ctis[sOWNR]->s2[i][j].s2ct_sghnd
#define ct_kyorg(i,j)	ctis[sOWNR]->sct_kyorg[i][j]
#define ct_kymap(i,j)	ctis[sOWNR]->sct_kymap[i][j]

#define ect_dtmap(i)		pis1->s1ct_dtmap
#define ect_rvmap(i)		pis1->s1ct_rvmap
#ifdef ctCONDIDX
#define ect_rlkey(i)		pis1->s1ct_rlkey
#endif
#define ect_nlkey(i)		pis1->s1ct_nlkey
#define ect_nlchr(i)		pis1->s1ct_nlchr
#define ect_vfin(i)		pis1->s1ct_vfin
#define ect_sgpos(i,j)		pis2->s2ct_sgpos
#define ect_sglen(i,j)		pis2->s2ct_sglen
#define ect_sgmod(i,j)		pis2->s2ct_sgmod
#define ect_sghnd(i,j)		pis2->s2ct_sghnd
#define ect_kyorg(i,j)		pis->sct_kyorg[i][j]
#define ect_kymap(i,j)		pis->sct_kymap[i][j]

#else /* MULTITRD */

#ifndef ctNOGLOBALS

#ifdef RTREE
EXTERN COUNT	srtknm,srtdat,tmpdat;
#endif
#ifdef ctDROPCOND
EXTERN pFILNO	*ctskyorg;
#endif
EXTERN pFILNO	*ctskymap;
EXTERN pCTIS1	ctis1;
EXTERN ppCTIS2	ctis2;

EXTERN TEXT	ct_fndval[MAXLEN];

EXTERN COUNT	ct_nwrcfg;
EXTERN COUNT	ct_vfsg;

EXTERN COUNT	ct_ismlk;
#ifdef ctFeatRECRLOCK
EXTERN NINT	ct_ismrc;
#endif

#ifdef ctOldALCSET
EXTERN pSAVSET  ct_savset;
#else
EXTERN ppSAVSET ct_savset;
#endif

#endif /* ~ctNOGLOBALS */

#ifdef RTREE
#define usrkey(i)	ctis1[i].s1usrkey
#define usrdat(i)	ctis1[i].s1usrdat
#define eusrkey(i)	pis1->s1usrkey
#define eusrdat(i)	pis1->s1usrdat
#endif
#define ct_dtmap(i)	ctis1[i].s1ct_dtmap
#define ct_rvmap(i)	ctis1[i].s1ct_rvmap
#ifdef ctCONDIDX
#define ct_rlkey(i)	ctis1[i].s1ct_rlkey
#endif
#define ct_nlkey(i)	ctis1[i].s1ct_nlkey
#define ct_nlchr(i)	ctis1[i].s1ct_nlchr
#define ct_vfin(i)	ctis1[i].s1ct_vfin
#define ct_kyorg(i,j)	ctskyorg[i][j]
#define ct_kymap(i,j)	ctskymap[i][j]
#define ct_sgpos(i,j)	ctis2[i][j].s2ct_sgpos
#define ct_sglen(i,j)	ctis2[i][j].s2ct_sglen
#define ct_sgmod(i,j)	ctis2[i][j].s2ct_sgmod
#define ct_sghnd(i,j)	ctis2[i][j].s2ct_sghnd

#define ect_dtmap(i)	pis1->s1ct_dtmap
#define ect_rvmap(i)	pis1->s1ct_rvmap
#ifdef ctCONDIDX
#define ect_rlkey(i)	pis1->s1ct_rlkey
#endif
#define ect_nlkey(i)	pis1->s1ct_nlkey
#define ect_nlchr(i)	pis1->s1ct_nlchr
#define ect_vfin(i)	pis1->s1ct_vfin
#define ect_kyorg(i,j)	ctskyorg[i][j]
#define ect_kymap(i,j)	ctskymap[i][j]
#define ect_sgpos(i,j)	pis2->s2ct_sgpos
#define ect_sglen(i,j)	pis2->s2ct_sglen
#define ect_sgmod(i,j)	pis2->s2ct_sgmod
#define ect_sghnd(i,j)	pis2->s2ct_sghnd
#endif /* ~MULTITRD */

#endif /* ~CTISAMH */

/* end of ctisam.h */
