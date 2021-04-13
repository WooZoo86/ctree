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

#ifdef ctFeatSECURITY

#ifndef ctADMLOC
#define ctADMLOC
#endif
#define UGFNUM	(COUNT) (NAMINDX + 2)

#ifdef ctFeatADMIN_SECURITY
#define UGFPERM (UCOUNT) (OPF_ALL | GPF_READ | WPF_NONE)
#else
#define UGFPERM 0L
#endif

ctADMLOC ISEG u_seg[] = {
		{0,IDZ,UREGSEG}
		};
ctADMLOC ISEG v_seg[] = {
		{0,IDZ,UREGSEG}
		};
ctADMLOC ISEG g_seg[] = {
		{0,IDZ,UREGSEG}
		};
ctADMLOC ISEG ug_seg[] = {
		{0,IDZ + 1,UREGSEG},
		{IDZ + 1,IDZ,UREGSEG},
		{IDZ + 1,IDZ,UREGSEG},
		{0,IDZ,UREGSEG},
		};

ctADMLOC IIDX u_idx[] = {
		{IDZ,0,0,0,0,1,u_seg}
		};
ctADMLOC IIDX v_idx[] = {
		{IDZ,0,0,0,0,1,v_seg}
		};
ctADMLOC IIDX g_idx[] = {
		{IDZ,0,0,0,0,1,g_seg}
		};
ctADMLOC IIDX ug_idx[] = {
		{2 * IDZ + 1,0,0,0,0,2,ug_seg},
		{2 * IDZ,0,0,0,0,2,ug_seg + 2}
		};

#ifdef ctSRVR
#define ctUGlmt	(MAXCOMMP + 1)
#else
#define ctUGlmt	3
#endif

ctADMLOC IFIL ctiug[ctUGlmt] = {
	{
	"FAIRCOM.FCS!UG",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_UG),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	2,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	ug_idx
	},
	{
	"FAIRCOM.FCS!UG",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_UG),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	2,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	ug_idx
	},
	{
	"FAIRCOM.FCS!UG",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_UG),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	2,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	ug_idx
	}
};

#ifdef ctFeatADMIN_SECURITY
ctADMLOC DATOBJ ctiugflds[] = {
	{"userid",  NULL, CT_FSTRING, IDZ},
	{"seqnum",  NULL, CT_FSTRING, 1},
	{"groupid", NULL, CT_FSTRING, IDZ}
};
#define CTIUGNUMFLDS (sizeof(ctiugflds)/sizeof(*ctiugflds))
#endif

ctADMLOC IFIL ctigroup[ctUGlmt] = {
	{
	"FAIRCOM.FCS!GROUP",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_GROUP),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	1,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	g_idx
	},
	{
	"FAIRCOM.FCS!GROUP",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_GROUP),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	1,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	g_idx
	},
	{
	"FAIRCOM.FCS!GROUP",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_GROUP),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	1,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	g_idx
	}
};

#ifdef ctFeatADMIN_SECURITY
ctADMLOC DATOBJ ctigroupflds[] = {
	{"groupid",   NULL, CT_FSTRING, IDZ},
	{"groupstmp", NULL, CT_INT4},
	{"groupmem",  NULL, CT_INT4},
	{"groupattr", NULL, CT_INT4},
#ifdef ctFeatPWDLEN
	{"groupmaxlgn", NULL, CT_INT4},
#endif
	{"groupds",   NULL, CT_FSTRING, DSZ}
};
#define CTIGROUPNUMFLDS (sizeof(ctigroupflds)/sizeof(*ctigroupflds))
#endif

ctADMLOC IFIL ctiuser[ctUGlmt] = {
	{
	"FAIRCOM.FCS!USER",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_USER),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	1,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	u_idx
	},
	{
	"FAIRCOM.FCS!USER",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_USER),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	1,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	u_idx
	},
	{
	"FAIRCOM.FCS!USER",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_USER),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	1,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	u_idx
	}
};

#ifdef ctFeatADMIN_SECURITY
ctADMLOC DATOBJ ctiuserflds[] = {
	{"userid",   NULL, CT_FSTRING, IDZ},
	{"userstmp", NULL, CT_INT4},
	{"usermem" , NULL, CT_INT4},
	{"userattr", NULL, CT_INT4},
#ifdef ctFeatPWDLEN
	{"usermaxlgn",NULL, CT_INT4},
	{"userword", NULL, CT_FSTRING, PWH},
	{"usersalt", NULL, CT_FSTRING, PWS},
#else
	{"userword", NULL, CT_FSTRING, 16},
#endif
	{"userds",   NULL, CT_FSTRING, DSZ}
};
#define CTIUSERNUMFLDS (sizeof(ctiuserflds)/sizeof(*ctiuserflds))
#endif

ctADMLOC IFIL ctiuval[ctUGlmt] = {
	{
	"FAIRCOM.FCS!UVAL",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_UVAL),
#else
	0,
#endif
	0,
	(ctSHARED | ctVLENGTH | ctTRNLOG | ctADMOPEN),
	1,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	v_idx
	},
	{
	"FAIRCOM.FCS!UVAL",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_UVAL),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctVLENGTH | ctADMOPEN),
	1,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	v_idx
	},
	{
	"FAIRCOM.FCS!UVAL",
	-1,
#ifdef ctSTRCH
	ctSIZE(FC_UVAL),
#else
	0,
#endif
	0,
	(ctSHARED | ctTRNLOG | ctVLENGTH | ctADMOPEN),
	1,
	0,
	(ctSHARED | ctTRNLOG | ctADMOPEN),
	v_idx
	}
};

#ifdef ctFeatADMIN_SECURITY
ctADMLOC DATOBJ ctiuvalflds[] = {
	{"userid",     NULL, CT_FSTRING, IDZ},
	{"begstamp",   NULL, CT_INT4U},
	{"endstamp",   NULL, CT_INT4U},
	{"lgonover",   NULL, CT_INT4U},
	{"reserved",   NULL, CT_INT4U},
	{"rsmstamp",   NULL, CT_INT4U},
	{"lgonfail",   NULL, CT_INT4},
	{"lgonany",    NULL, CT_INT4U},
	{"lgonok",     NULL, CT_INT4U},
	{"lgonbad",    NULL, CT_INT4U},
	{"lgonoknum",  NULL, CT_INT4},
	{"lgonbadnum", NULL, CT_INT4},
	{"disstamp",   NULL, CT_INT4U},
	{"lgonmust",   NULL, CT_INT4},
	{"lastpasschg", NULL, CT_INT4},
	{"passvaliddays", NULL, CT_INT4},
	{"resrv",      NULL, CT_FSTRING, 92}
};
#define CTIUVALNUMFLDS (sizeof(ctiuvalflds)/sizeof(*ctiuvalflds))
#endif

#endif /* ctFeatSECURITY */
