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

#ifndef ctIFILH
#define ctIFILH

#define DAT_EXTENT	".dat"
#define IDX_EXTENT	".idx"

#ifdef ctDBGbigISEG
typedef struct iseg {
	COUNT	soffset,	/* segment offset	*/
		slength,	/* segment length	*/
		segmode;	/* segment mode		*/
	COUNT	padding;	/* force 8-byte ISEG	*/
	} ISEG;
#else
typedef struct iseg {
	COUNT	soffset,	/* segment offset	*/
		slength,	/* segment length	*/
		segmode;	/* segment mode		*/
	} ISEG;
#endif
typedef ISEG ctMEM *	pISEG;
#define ISEG_LEN	6
#define ISEG_PLEN	6

typedef struct iidx {
	COUNT	ikeylen,	/* key length		*/
		ikeytyp,	/* key type		*/
		ikeydup,	/* duplicate flag	*/
		inulkey,	/* null ct_key flag	*/
		iempchr,	/* empty character	*/
		inumseg;	/* number of segments	*/
	pISEG   seg;		/* segment information	*/
	pTEXT   ridxnam;	/* r-tree symbolic name	*/
	pTEXT	aidxnam;	/* (opt) index filnam	*/
	pCOUNT	altseq;		/* (opt) alt sequence	*/
	pUTEXT	pvbyte;		/* (opt) ptr to pad byte*/
	} IIDX;

typedef IIDX ctMEM *	pIIDX;
#define IIDX_LEN	12

typedef struct {
	COUNT	c[6];
	LONG	seg;
	LONG	ridxnam;
	LONG	aidxnam;
	LONG	altseq;
	LONG	pvbyte;
	} IIDXz;
typedef IIDXz ctMEM *	pIIDXz;
#define IIDX_PLEN	ctSIZE(IIDXz)
#define INUMSEG		5		/* last element of c[6] */

typedef struct {
	COUNT	c[6];
	LONG	seg;
	LONG	ridxnam;
	} IIDX1z;

struct ifil {
	pTEXT   pfilnam;	/* file name (w/o ext)	*/
	COUNT	dfilno;		/* data file number	*/
	UCOUNT	dreclen;	/* data record length	*/
	UCOUNT	dxtdsiz;	/* data file ext size	*/
	COUNT	dfilmod;	/* data file mode	*/
	COUNT	dnumidx;	/* number of indices	*/
	UCOUNT	ixtdsiz;	/* index file ext size	*/
	COUNT	ifilmod;	/* index file mode	*/
	pIIDX   ix;		/* index information	*/
	pTEXT   rfstfld;	/* r-tree 1st fld name	*/
	pTEXT   rlstfld;	/* r-tree last fld name	*/
	COUNT	tfilno;		/* temporary file number*/
	};
#define IFIL_LEN	14	/* total length of ifil data for dfilno through ifilmod */
#define IFIL_PLEN	36	/* size of streamed ifil data */
#define IFIL_1LEN	32	/* size of streamed ifil data 1-byte aligned */

#ifdef ctFeatMAXFILE32

/* IFIL structure with 4-byte file numbers */
struct ifil4 {
	pTEXT   pfilnam;	/* file name (w/o ext)	*/
	LONG	dfilno;		/* data file number	*/
	UCOUNT	dreclen;	/* data record length	*/
	UCOUNT	dxtdsiz;	/* data file ext size	*/
	COUNT	dfilmod;	/* data file mode	*/
	COUNT	dnumidx;	/* number of indices	*/
	UCOUNT	ixtdsiz;	/* index file ext size	*/
	COUNT	ifilmod;	/* index file mode	*/
	pIIDX   ix;		/* index information	*/
	pTEXT   rfstfld;	/* r-tree 1st fld name	*/
	pTEXT   rlstfld;	/* r-tree last fld name	*/
	LONG	tfilno;		/* temporary file number*/
	};
#define IFIL4_LEN	16	/* total length of ifil4 data for dfilno through ifilmod */
#define IFIL4_1LEN	36	/* size of streamed ifil4 data 1-byte aligned */

#endif /* ctFeatMAXFILE32 */

/* IFIL data stream sent between client and server */
struct ifilz {
	LONG    pfilnam;	/* file name (w/o ext)	*/
	COUNT	dfilno;		/* data file number	*/
	UCOUNT	dreclen;	/* data record length	*/
	UCOUNT	dxtdsiz;	/* data file ext size	*/
	COUNT	dfilmod;	/* data file mode	*/
	COUNT	dnumidx;	/* number of indices	*/
	UCOUNT	ixtdsiz;	/* index file ext size	*/
	COUNT	ifilmod;	/* index file mode	*/
	LONG    ix;		/* index information	*/
	LONG    rfstfld;	/* r-tree 1st fld name	*/
	LONG    rlstfld;	/* r-tree last fld name	*/
	COUNT	tfilno;		/* temporary file number*/
	};

/* IFIL data stream sent between client and server, using 4-byte file numbers */
typedef struct ifil4z {
	LONG    pfilnam;	/* file name (w/o ext)	*/
	LONG	dfilno;		/* data file number	*/
	UCOUNT	dreclen;	/* data record length	*/
	UCOUNT	dxtdsiz;	/* data file ext size	*/
	COUNT	dfilmod;	/* data file mode	*/
	COUNT	dnumidx;	/* number of indices	*/
	UCOUNT	ixtdsiz;	/* index file ext size	*/
	COUNT	ifilmod;	/* index file mode	*/
	LONG    ix;		/* index information	*/
	LONG    rfstfld;	/* r-tree 1st fld name	*/
	LONG    rlstfld;	/* r-tree last fld name	*/
	LONG	tfilno;		/* temporary file number*/
	} IFIL4z;
typedef IFIL4z ctMEM *	pIFIL4z;

#ifdef ctCONDIDX
typedef struct ccond {
	COUNT	relkey;		/* relative key number: 0,1,...		*/
	COUNT	explen;		/* length of tokenized expression	*/
	LONG	exptyp;		/* reserved for future use		*/
	pTEXT	cexpr;		/* ptr to tokenized expression (not a
				   NULL terminated ASCII string)	*/
	} CCOND;
typedef CCOND ctMEM *	pCCOND;
typedef CCOND ctMEM * ctMEM * ppCCOND;

typedef struct cifil {
	COUNT	cnumstat;	/* number of static  conditions		*/
	COUNT	cnumdynm;	/* number of dynamic conditions		*/
	ppCCOND	condstat;	/* ptr to array of static  CCOND's	*/
	ppCCOND	conddynm;	/* ptr to array of dynamic CCOND's	*/
	} CIFIL;
typedef CIFIL ctMEM *	pCIFIL;
#endif

typedef struct cbdll_t ctMEM *pCBDLL;

typedef NINT (*pCBFNC)(pCBDLL pcbdll, FILNO datno, pVOID Recptr,
		       pConvMap Schema, VRLEN fixlen, VRLEN datlen);
typedef LONG (*pCBFNCgetver)(VOID);
typedef NINT (*pCBFNCload)(pCBDLL pcbdll);
typedef NINT (*pCBFNCunload)(pCBDLL pcbdll);

typedef struct cbdll_t {
	NINT		cbinst;		/* callback instance count	*/
	pTEXT		cbdll;		/* name of callback DLL		*/
	pTEXT		cbfnc;		/* name of callback function	*/
	pTEXT		cbprm;		/* callback function parameters	*/
	pVOID		cbdllhnd;	/* handle to callback DLL	*/
	pCBFNC		cbfncptr;	/* pointer to callback function	*/
	pCBFNCload	cbload;		/* ctfiltercbLoadLib ptr	*/
	pCBFNCunload	cbunload;	/* ctfiltercbUnloadLib ptr	*/
	pVOID		cbfilterhandle;	/* user-defined library handle	*/
	TEXT		cbfilnam[MAX_NAME]; /* data file name		*/
} CBDLL;

/* The original version of the filter callback DLL interface: */
#define ctFILTERCB_VER01	0x00000001

/*
** Version 2 of the filter callback DLL interface: added the cbfilnam field to
** the CBDLL structure.
*/
#define ctFILTERCB_VER02	0x00000002

#define ctFILTERCB_MAXFILE32	0x80000000 /* using 4-byte file numbers */

/* The current version of the filter callback DLL interface: */
#ifdef ctFeatMAXFILE32
#define ctFILTERCB_VERSION	(ctFILTERCB_VER02 | ctFILTERCB_MAXFILE32)
#else
#define ctFILTERCB_VERSION	ctFILTERCB_VER02
#endif

#ifdef ctFeatVFYIDXspace
#define ctVFYIDX_VERS_CUR ctVFYIDX_VERS_V02	/* current version */
#define ctVFYIDXall	(ctVFYIDXdelstk | ctVFYIDXlink | ctVFYIDXleaf | ctVFYIDXchkkey | ctVFYIDXspace)
#else
#define ctVFYIDX_VERS_CUR ctVFYIDX_VERS_V01	/* version 1 */
#define ctVFYIDXall	(ctVFYIDXdelstk | ctVFYIDXlink | ctVFYIDXleaf | ctVFYIDXchkkey )
#endif

/* ctVERIFYidx Version 1 compatibility output parameters */
typedef struct ctvfyidxout_v1 {
	LONG	smtynod;	 /* number of empty nodes		*/
	LONG	sbadnod;	 /* number of bad nodes			*/
	LONG	sununod;	 /* number of unused nodes		*/
	LONG	sresnod;	 /* number of resource pages		*/
	LONG	smisnod;	 /* number of misaligned nodes		*/
	LONG	sbadlnk;	 /* number of bad links			*/
	LONG	snodcnt[VFYLEV]; /* node count at each level of tree	*/
} ctVFYIDXoutV1, *pctVFYIDXoutV1;

/* ctVERIFYidx output parameters */
typedef struct ctvfyidxout {
	LONG	smtynod;	 /* number of empty nodes		*/
	LONG	sbadnod;	 /* number of bad nodes			*/
	LONG	sununod;	 /* number of unused nodes		*/
	LONG	sresnod;	 /* number of resource pages		*/
	LONG	smisnod;	 /* number of misaligned nodes		*/
	LONG	sbadlnk;	 /* number of bad links			*/
#ifdef ctFeatVFYIDXspace
	LONG    slostnod;	 /* number of lost nodes - version 2    */
#endif
	LONG	snodcnt[VFYLEV]; /* node count at each level of tree	*/
} ctVFYIDXout, *pctVFYIDXout;

#endif /* ctIFILH */

/* end of ctifil.h */
