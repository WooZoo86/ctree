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

/* 
This header was added to aid the MAC compiler when function prototypes
are required. 
*/

#ifdef ctPortMAC
#ifdef __cplusplus
extern "C" {
#endif
extern VOID exitMac(NINT status);				/* ctlsup.c */
#ifdef __cplusplus
}
#endif
extern VOID macCTSTATUSType(pTEXT afilnam);			/* ctclib.c */
extern NINT ctfilexists(pTEXT filnam);				/* ctclb2.c */
extern NINT ctarcnam(pTEXT ap,pTEXT np,TEXT a,pTEXT mp,NINT mflag); /* ctclb3.c */
extern NINT ctmatch(pTEXT pp,pTEXT ep,pTEXT tp,pTEXT et,NINT casen);/* ctsstr_a.c */

extern VOID stopServerSide(void);				/* ctclib.c */
extern COUNT CTCOMP(pTEXT val1,pTEXT val2,COUNT keylen);	/* ctclib.c */
extern VRLEN CTCOMPU(pTEXT val1,pTEXT val2,UINT keylen);	/* ctclib.c */
extern pVOID memoryMacCtNp(ULONG nbr,ULONG size);		/* ctclib.c */
extern VOID memoryfreeMacCtNp(pTEXT p);				/* ctclib.c */
extern VOID ctrt_beep(LONG len);				/* ctclib.c */
/* extern void	SysBeep(short len); */				/* ctclib.c */
/* extern NINT setfposMac();	    */				/* ctclib.c */

extern LONG chkhgh(COUNT filno,LONG nodex);			/* ctdbug.c */
/* extern LONG ctcntexc(pTREBUF buffer,NINT endpnt,LONG frsnod,NINT frspnt); */	/* ctgpln.c */

extern VOID  loadpath(pTEXT fname,pTEXT pname);			/* cticmp.c */

/* extern ctCONV COUNT ctDECL TMPIIDX(pIFIL ifilptr); */	/* ctiidx.c */
/* extern pCIFIL ctinitcidx(COUNT datno,pTEXT idxcnd,pConvMap schema,pTEXT names); *//* ctcndx.c */
extern ctCONV COUNT ctDECL NOFUNCT(void);			/* ctjump.c */
extern ctCONV LONG ctDECL NOFUNCL(void);			/* ctjump.c */
extern ctCONV VRLEN ctDECL NOFUNCV(void);			/* ctjump.c */
extern COUNT TRANSACTION(COUNT mode);				/* ctocfl.c */
/* extern COUNT supass1(pCTFILE dnum,COUNT resno,COUNT hdrno); */ /* ctsbl2.c */
extern COUNT supass2(COUNT datno,pTEXT datnam,pTEXT fileword,COUNT resno,COUNT hdrno,pNINT pstage); /* ctsbl2.c */
extern COUNT RBLSUPX(pTEXT datnam,pTEXT fileword);		/* ctsbl2.c */
extern NINT s__comp(ppVOID pp1,ppVOID pp2, NINT w);		/* ctsort.c */
extern NINT cttrnupd(COUNT ufilno);				/* cttran.c */
extern NINT PIFlush(NINT sOWNR,VRLEN iosize);			/* cttran.c */
extern pTEXT gettenv(NINT sOWNR,pVRLEN plen);			/* cttran.c */

extern VOID  loadpath(pTEXT fname,pTEXT pname);			/* cticmp.c */
/* extern NINT prtkey(pTEXT tp,pCTFILE knum); */		/* ctvrfy.c */

#endif /* ctPortMAC */

/* end of ctfun2.h */

