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

#ifndef ctSTRCH
#define ctSTRCH

#ifdef  ctPortCTB
#ifndef CTFILE_HAS_UsrData
#define CTFILE_HAS_UsrData
#endif
#endif

#ifdef  ctPortCHE
#ifndef CTFILE_HAS_UsrData
#define CTFILE_HAS_UsrData
#endif
#endif

			/* Data Structures */
#include "ctsema.h"

#ifdef ctCUSTOM
typedef struct custmem {
	struct
	custmem	*toplink;
	struct
	custmem *botlink;
	pTEXT	 signature;
	} CUSTMEM;
typedef CUSTMEM ctMEM * pCUSTMEM;
#define ctCUSTmemhdr	ctSIZE(CUSTMEM)
#define ctCUSTmemsig	((pTEXT) 0x12344321)
#endif

#ifdef ctBEHAV_CLUP
typedef struct ctclup {
	LONG	hwt;	/* hgh word tran	*/
	ULONG	lwt;	/* low word tran	*/
	NINT	act;	/* action		*/
	} ctCLUP, *pctCLUP;
#endif

#ifdef ctCONDIDX
typedef struct savcndexp {
	LONG	opc;
	LONG	typ;
	pVOID	flt;
	UINT	key;
	UINT	nlk;
	} SAVCNDEXP, * pSAVCNDEXP;
#endif

#ifdef ctFeatDATFLTsecurity
#define ROWSECsiz	112
typedef struct rowsec {
		ULONG	restyp;
		ULONG	resnum;
		TEXT	resnam[FCRNAM_LEN];
		TEXT	resstr[ROWSECsiz];	/* place holder */
	} ROWSEC, * pROWSEC;
#endif


#ifdef DBG749x

#define DBG749xSIG	0x796a5b4c
#define DBG749xUSE	0x68594a3b
typedef struct pctspc {
	union {
	pLONG	ptr;
	LONG	lng;
	} uctSPC;
	LONG	sig;	/* debug signature */
} pctSPC;

#else  /* ~DBG749x */

typedef union pctspc {
	pLONG	ptr;
#ifdef ctMEMALIGN
	TEXT	align[ctMEMALIGN];
#else
	LONG	lng;
#endif
} pctSPC;

#endif /* ~DBG749x */

/*
** Direct Access Resources: common resource structure beginning
**
** ctSIBLING_DAR
*/

#define FC_DAR_RESNAM	"FC!DAR"
#define FC_DAR_STRLEN	64
#define FC_DAR_BINLEN	128

typedef struct dar {
	ULONG	restyp;			/* FC_DAR  >filled-in automatically */
	ULONG	resnum;			/* 1,2,... >filled-in automatically */
	TEXT	resnam[FCRNAM_LEN];	/* name    >filled-in automatically */
	ULONG	dartyp;			/* e.g., FC_DAR_IDfield		    */
	UCOUNT	verson;			/* version number		    */
	UCOUNT	attrib;			/* attribute bit map		    */
	LONG	darpos2;		/* self-referential position hw	    */
	LONG	darpos1;		/* self-referential position lw	    */
	union {
		LONG8	darval8[4];
		LONG	darval4[8];
	}	ary;			/* 32 bytes of integers		    */
	TEXT	darstr[FC_DAR_STRLEN];	/* 64-byte string space		    */
	union {
		TEXT	dartxt[FC_DAR_BINLEN];	/* 128 bytes of unstructured,
						** but aligned space	    */
		LONG8	darval8[16];		/* LONG8 array		    */
		LONG	darval4[32];		/* LONG array		    */
	}	bin;
} DAR, * pDAR;


#define FC_ATTR_RESNAM "FC!ATTR"

/* FairCom Attribute Resource Data Block structure */
typedef struct {
	ULONG	restyp;
	ULONG	resnum;
	TEXT	resdat[12]; /* This holds the Resource Name and Data */
} FC_ATTR;

/*
** Resource length for FAIRCOM.FCS version 2
**	4 byte resource type
**	4 byte resource number
**	7 byte resource name
*/
#define FC_ATTR_RESLEN_V2	15

/*
** Resource length for FAIRCOM.FCS version 3
**	4 byte resource type
**	4 byte resource number
**	8 byte null-terminated resource name
**	1 byte resource attribute bits
*/
#define FC_ATTR_RESLEN_V3	17

typedef struct {
	TEXT	userid[IDZ];
	LONG	userstmp;
	LONG	usermem;
	LONG	userattr;
#ifdef ctFeatPWDLEN
	LONG	usermaxlgn;
	TEXT	userword[PWH];
	TEXT	usersalt[PWS];
#else
	TEXT	userword[16];
#endif
	TEXT	userds[DSZ];
} FC_USER, FC_USER_VER3;
#define FC_USER_VERSION 3
/* ctSIBLING_FC_USER */
typedef FC_USER ctMEM *	pFC_USER;

typedef struct {
	TEXT	userid[IDZ];
	LONG	userstmp;
	LONG	usermem;
	LONG	userattr;
	TEXT	userword[16];
	TEXT	userds[DSZ];
} FC_USER_VER2;

typedef struct {
	TEXT	userid[IDZ];
	LONG	userstmp;
	LONG	usermem;
	LONG	userattr;
	TEXT	userword[PWZ];
	TEXT	userds[DSZ];
} FC_USER_ORIG;

typedef struct {
	TEXT	userid[IDZ];
	ULONG	begstamp;	/* beginning date for valid user logon	*/
	ULONG	endstamp;	/* last valid date for user logon 	*/
	LONG	lgonover;	/* limit on consecutive logon failures	*/
	LONG	reserved;
	ULONG	rsmstamp;	/* temporary logon block 		*/
	LONG	lgonfail;	/* current number of failed login attempts*/
	ULONG	lgonany; 	/* last logon attempt date		*/
	ULONG	lgonok;	 	/* last successful login date		*/
	ULONG	lgonbad; 	/* last failed login date		*/
	LONG	lgonoknum; 	/* Total number of successful logins(ever)*/
	LONG	lgonbadnum;	/* Total number of failed logins(ever)  */
	ULONG   disstamp; 	/* when logon was disabled		*/
	LONG    lgonmust;	/* user must login within this period	*/
#ifdef ctFeatPWDEXP
	ULONG	lastpasschg;	/* time of last change to password	*/
	ULONG	passvaliddays;	/* number of days that password is valid*/
#else
	ULONG	unused[2];
#endif
	TEXT	resrv[92];
} FC_UVAL;
typedef FC_UVAL ctMEM *	pFC_UVAL;


typedef struct {
	TEXT	groupid[IDZ];
	LONG	groupstmp;
	LONG	groupmem;
	LONG	groupattr;
#ifdef ctFeatPWDLEN
	LONG	groupmaxlgn;
#endif
	TEXT	groupds[DSZ];
} FC_GROUP;
typedef FC_GROUP ctMEM * pFC_GROUP;

typedef struct {
	TEXT	groupid[IDZ];
	LONG	groupstmp;
	LONG	groupmem;
	LONG	groupattr;
	TEXT	groupds[DSZ];
} FC_GROUP_ORIG;

typedef struct {
	TEXT	userid[IDZ];
	TEXT	seqnum;
	TEXT	groupid[IDZ];
} FC_UG;
typedef FC_UG ctMEM * pFC_UG;


typedef struct admfiles {
	pTEXT u_pfilnam;	/* FAIRCOM.FCS!USER.dat file name */
	pTEXT uv_pfilnam;	/* FAIRCOM.FCS!UVAL.dat file name */
	pTEXT g_pfilnam;	/* FAIRCOM.FCS!GROUP.dat file name */
	pTEXT ug_pfilnam;	/* FAIRCOM.FCS!UG.dat file name */

	FILNO ugfnum;		/* FAIRCOM.FCS file number */
	COUNT ugfmode;		/* FAIRCOM.FCS file mode */

	FILNO u_tfilno;		/* FAIRCOM.FCS!USER.dat file number */
	COUNT u_dfilmod;	/* FAIRCOM.FCS!USER.dat file mode */

	FILNO uv_tfilno;	/* FAIRCOM.FCS!UVAL.dat file number */
	COUNT uv_dfilmod;	/* FAIRCOM.FCS!UVAL.dat file mode */

	FILNO g_tfilno;		/* FAIRCOM.FCS!GROUP.dat file number */
	COUNT g_dfilmod;	/* FAIRCOM.FCS!GROUP.dat file mode */

	FILNO ug_tfilno;	/* FAIRCOM.FCS!UG.dat file number */
	COUNT ug_dfilmod;	/* FAIRCOM.FCS!UG.dat file mode */
} AdmFils, ctMEM *	pAdmFils;



typedef struct ct_fnbi {
	NINT	typ;		/* function attributes		*/
#ifdef ctDBG_FNBcoverage
	NINT	cvr;		/* coverage flag		*/
	pTEXT	fnc;		/* function name		*/
#endif
#ifdef ctTESTsrvdllquiet
	NINT	pre;		/*  PREFNC skip flag		*/
	NINT	pst;		/* POSTFNC skip flag		*/
	NINT	ism;		/* ISAM level flag		*/
#endif
} CT_FNBI;

#ifdef ctDYNHASH
/*
** dynamic hash state
*/
typedef struct hshstt {
	UINT	startbins;		/* starting # of bins (minbins)	*/
	UINT	maxbins;		/* maximum # of bins		*/
	UINT	bins;			/* current number of bins	*/
	UINT	index;			/* rightmost active bin		*/
	UINT	totcnt;			/* total entries in hash table	*/
	UINT	rehashC;		/* rehash count			*/
	UINT	dehashC;		/* dehash count			*/
	UINT	state;			/* state bit field		*/
	UINT	loadF;			/* load factor (dyn trigger)	*/
	UINT	rehashF;		/* fraction of bins rehashed	*/
	} HSHSTT, * pHSHSTT;

typedef struct rlokhsh {
	struct reclok
	      *h;
	struct reclok
	      *t;
	/* UINT cnt */
	} RLOKHSH, * pRLOKHSH;

typedef struct ulokhsh {
	struct lok *h;
	struct lok *t;
	/* UINT	cnt */
	} ULOKHSH, * pULOKHSH;
#endif

#ifdef ctFeatFILENAMEhash
typedef struct fnamele {
	struct fnamele *
		next;			/* next entry in this hash bin	    */
	NINT	filnum;			/* system file number for this file */
#if defined(ctHUGEFILE) && defined(ctSRVR)
	NINT	ofluser;		/* user initiating pending delete   */
	NINT	refcnt;			/* reference count for entry	    */
#endif
	TEXT	filnam[MAX_NAME];	/* filename			    */
	} FNAMELE, * pFNAMELE;

typedef struct fnamhsh {
	pFNAMELE h;
	pFNAMELE t;
	} FNAMHSH, * pFNAMHSH;
#endif

#ifdef CTPERM /* this block contains code for internal use only */

#ifdef ctFeatOPTIMIZE_FILE_OPEN

/* pending open file name hash table entry */
typedef struct pfoele {
	struct pfoele *
		next;			/* next entry in this hash bin */
	NINT	taskid;			/* task id of connection that added the entry */
	NINT	opcode;			/* opcode bits (ctPENDING_FILE_OPEN, etc.) */
	LONG	closeCount;		/* number of pending file closes */
	LONG	deleteCount;		/* number of pending file deletes */
	TEXT	fileName[MAX_NAME];	/* filename */
	} PFOELE, * pPFOELE;

/* pending open file name hash table bin entry */
typedef struct pfohsh {
	pPFOELE h; /* head of list */
	pPFOELE t; /* tail of list */
	} PFOHSH, * pPFOHSH;

#ifdef ctFeatSYSTEM_FILE_ID_LIST

/* system file id hash table entry */
typedef struct sysidele {
	LONG8	devid;		/* device id */
	LONG8	fileidx;	/* file id */
	struct sysidele *
		next;		/* next entry in this hash bin */
	NINT	taskid;		/* task id of connection that added the entry */
	} SYSIDELE, * pSYSIDELE;

/* system file id hash table bin entry */
typedef struct sysidhsh {
	pSYSIDELE h; /* head of list */
	pSYSIDELE t; /* tail of list */
	} SYSIDHSH, * pSYSIDHSH;

#endif /* ctFeatSYSTEM_FILE_ID_LIST */

#endif /* ctFeatOPTIMIZE_FILE_OPEN */

#ifdef ctCMPREC
/* connection-level connection attributes set by ctSETCOMPRESS() */
typedef struct usrcmpatr_t {
	pTEXT	compressionAttributes;
	pTEXT	compressionDllName;
	NINT	compressionType;
	NINT	compressionVersion;
	NINT	compressionAttributeLength;
} USER_COMPRESSION_ATTRIBUTES, *pUSER_COMPRESSION_ATTRIBUTES;
#endif

/* data type to hold ClearFileState() options parameter values */
typedef ULONG CLEAR_FILE_STATE_OPTIONS;

/* supported values for ClearFileState() options parameter */
#define CLEAR_FILE_STATE_KEY_BUFFERS 0x00000001 /* clear the ISAM and low-level key buffers for all ISAM contexts */
#define CLEAR_FILE_STATE_CURRENT_ISAM_POSITION 0x00000002 /* clear the current ISAM record position */

#define CLEAR_FILE_STATE_SUPPORTED_OPTIONS (CLEAR_FILE_STATE_KEY_BUFFERS | CLEAR_FILE_STATE_CURRENT_ISAM_POSITION) /* the supported options for ClearFileState() */

#endif /* CTPERM - end of block containing code for internal use only */

#define REPL_FILE_FILTER_PURPOSE_LEN	32 /* maximum length of purpose tag in replication file filter  */

/* purposes for a replication file filter; can specify one or more */
typedef enum replFileFilterPurpose_t {
	REPL_FILE_FILTER_PURPOSE_NONE		= 0x00000000, /* no purpose specified for file filter */
	REPL_FILE_FILTER_PURPOSE_CREATE_FILE	= 0x00000001, /* file filter is used when creating a file */
	REPL_FILE_FILTER_PURPOSE_READ_LOG	= 0x00000002, /* file filter is used when reading transaction log */
	REPL_FILE_FILTER_PURPOSE_SYNC_COMMIT	= 0x00000004, /* file filter is used when committing a transaction on the source server, to synchronize source server transaction commit with replication agent log state */
	REPL_FILE_FILTER_PURPOSE_OPEN_FILE	= 0x00000008 /* file filter is used when opening a file */
} REPL_FILE_FILTER_PURPOSE, *pREPL_FILE_FILTER_PURPOSE;

#ifdef ctFeatREPLICAT_SYNC_SRVR
/* sync repl file-agent hash map list entry */
typedef struct srfele {
	struct srfele *
		next;			/* next entry in this hash bin	    */
	pULONG	pagentHandleList;	/* list of agent handles	    */
	NINT	agentHandleListSize;	/* size of agent handles list       */
	NINT	nagentHandles;		/* number of agent handles in list  */
	TEXT	filnam[MAX_NAME];	/* filename			    */
	} SRFELE, * pSRFELE;

/* sync repl file-agent hash map list head */
typedef struct srfhsh {
	pSRFELE h; /* head */
	pSRFELE t; /* tail */
	} SRFHSH, * pSRFHSH;
#endif

#ifdef ctFeatLOGLMT
typedef struct llele {
	struct llele *
		nxt;		/* next entry in this hash bin		*/
	LONG	cnt;		/* current logons for this name		*/
	LONG	max;		/* concurrent logon limit for this name	*/
	TEXT	typ;		/* user(U) or group(G) entry		*/
	TEXT	nam[IDZ];	/* user or group name			*/
	} LLELE, * pLLELE;

typedef struct llhsh {
	pLLELE h;
	pLLELE t;
	} LLHSH, * pLLHSH;
#endif

#ifdef ctBEHAV_FLUSH_NODE_MARKS
/* System file number hash table element. */
typedef struct sfilele {
	struct sfilele *
		next;		/* next entry in this hash bin	    */
	NINT	filnum;		/* system file number for this file */
} SFILELE, * pSFILELE;

/* System file number hash table. */
typedef struct sfilhsh {
	pSFILELE h;
	pSFILELE t;
} SFILHSH, * pSFILHSH;
#endif

#ifdef ctHUGEFILE
typedef struct batlst {
	struct
	batlst ctMEM
		*batlnk;
	union {
		LONG	 batposH[2];
		pTEXT	 batkyp;
	} u;
} BATLST;
#else  /* ~ctHUGEFILE */
typedef struct batlst {
	struct
	batlst ctMEM
		*batlnk;
	union {
		LONG	 batpos1;
		pTEXT	 batkyp;
	} u;
} BATLST;
#endif /* ~ctHUGEFILE */
typedef BATLST ctMEM *	pBATLST;

typedef struct bathdr {
	pBATLST	 sbathed;	/* retrieval list hdr		*/
	pBATLST	 sbatail;	/* retrieval list tail		*/
	pBATLST	 sbatlsp;	/* retrieval list current pos	*/
	pBATLST	 sbatmrk;	/* retrieval list perm mark	*/
	pVOID	 sbatrqp;	/* request pointer		*/
	pTEXT	 sbatcnu;	/* continuation buffer pointer	*/
#ifdef ctFeatBATCH_ALLOC_OPT
	pTEXT	 sbatcnu2;	/* continuation buffer pointer	*/
#endif
	pTEXT	 sbatbfp;	/* buffer pointer		*/
	pTEXT	 sbatcrp;	/* current pointer		*/

	pVOID	 sbatrbp;	/* record buffer pointer	*/
	LONG	 sbattot;	/* total count			*/
	LONG	 sbatlkd;	/* number accessible		*/
	LONG	 sbatrem;	/* remaining to be processed	*/
	ULONG	 sbatreq;	/* record selection (PKEY etc.)	*/
	ULONG	 sbatmod;	/* batreq modifier		*/
	VRLEN	 sbatrbz;	/* record buffer size		*/
	VRLEN	 sbatbfz;	/* buffer size			*/
	LONG	 sbatnxt2;	/* next phy pos high word	*/
	LONG	 sbatnxt1;	/* next phy pos low  word	*/
	ULONG	 sbatopc;	/* current function		*/
	ULONG	 sbatvry;	/* verify key/rec flag		*/
	ULONG	 sbatret;	/* return type			*/
	ULONG	 sbatlok;	/* lock type			*/
	ULONG	 sbatcom;	/* complete vs partial flag	*/
	ULONG	 sbatulk;	/* unlock strategy		*/
	NINT	 sbatpnt;	/* size of file address (pntr)	*/
	NINT	 sbatfil;	/* filno			*/
	NINT	 sbatprt;	/* last partition		*/
	VRLEN	 sbatrsz;	/* required space on BTBZ_ERR	*/
#ifdef ctFeatBATCHEXT
	TEXT	 sreq2;		/* using pkeyreq2 */
	TEXT	 sfilter;	/* filter has been set (pkeyreq2)*/
	TEXT	 srange;	/* range has been set (pkeyreq2)*/
#ifdef ctFeatBATCHCOLFLTR
	RCDSC	 sbatrdc;	/* record column filtering information */
	pVOID	 sbatrdp;	/* converted record buffer */
	VRLEN    sbatrdz;	/* converted buffer size */
	pDATOBJ	 sbatdod;	/* original buffer DODA */
	ULONG	 sbatrcv;	/* record image conversion (heterogeneous C/S)*/
#endif
#endif
	} BATHDR;
typedef BATHDR ctMEM *	pBATHDR;

#ifndef ctOldALCBAT
typedef struct savbat {
	struct savbat
		*sblnk;		/* save batch link */
	BATHDR	 sbhdr;		/* save batch header */
	COUNT	 sbnum;		/* save batch number */
	} SAVBAT;
typedef SAVBAT ctMEM *	pSAVBAT;
typedef SAVBAT ctMEM * ctMEM *	ppSAVBAT;
#endif

typedef struct {
	UCOUNT	repad;		/* alignment padding */
	UCOUNT	remrk;		/* record mark */
	VRLEN	retot;		/* total length */
	VRLEN	relen;		/* in-use length */
	LONG	resup;		/* super file member */
	LONG	reflk1;		/* forward link */
	LONG	reblk1;		/* back link */
	ULONG	retyp;		/* resource type */
	ULONG	renum;		/* resource number */
	TEXT	renam;		/* optional name */
	} RESHDR;
typedef RESHDR ctMEM *	pRESHDR;

#ifdef ctHUGEFILE
typedef struct {
	UCOUNT	repad;		/* alignment padding */
	UCOUNT	remrk;		/* record mark */
	VRLEN	retot;		/* total length */
	VRLEN	relen;		/* in-use length */
	LONG	resup;		/* super file member */
#ifdef LOW_HIGH
#ifdef UNIFRMAT
	LONG	reflk2;
	LONG	reflk1;		/* forward link */
	LONG	reblk2;
	LONG	reblk1;		/* back link */
#else
	LONG	reflk1;		/* forward link */
	LONG	reflk2;
	LONG	reblk1;		/* back link */
	LONG	reblk2;
#endif

#else /* HIGH_LOW */

#ifdef UNIFRMAT
	LONG	reflk1;		/* forward link */
	LONG	reflk2;
	LONG	reblk1;		/* back link */
	LONG	reblk2;
#else
	LONG	reflk2;
	LONG	reflk1;		/* forward link */
	LONG	reblk2;
	LONG	reblk1;		/* back link */
#endif
#endif /* HIGH_LOW */
	ULONG	retyp;		/* resource type */
	ULONG	renum;		/* resource number */
	TEXT	renam;		/* optional name */
	} RESHDR8;
typedef RESHDR8 ctMEM *	pRESHDR8;
#endif /* ctHUGEFILE */

typedef struct lstitm {
	struct
	lstitm ctMEM
	       *lstlnk;
	pTEXT	lstbuf;
} LSTITM;
typedef LSTITM ctMEM *	pLSTITM;
typedef LSTITM ctMEM * ctMEM * ppLSTITM;

typedef struct lsthed {
	struct
	lsthed ctMEM
	       *hedprv;
	struct
	lsthed ctMEM
	       *hednxt;
	struct
	lstanc ctMEM
	       *hedanc;
	pLSTITM hedstk;
	pTEXT   hednew;
#ifdef ctMEMALIGN
#ifdef ct8P
	/* ensures struct size==64 (if UINT is 4 bytes) */
	TEXT	hedpad[8];
#else
	/* ensures struct size is multiple of ctMEMALIGN (if UINT is 4 bytes) */
	TEXT	hedpad[ctMEMALIGN - 4];
#endif
#endif
	UINT	hedcnt;
	UINT	hedtot;
	UINT	hedavl;
	UINT	hedrsv;
} LSTHED;
typedef LSTHED ctMEM *	pLSTHED;
typedef LSTHED ctMEM * ctMEM * ppLSTHED;

typedef struct lstanc {
	pLSTHED	ancact;		/* active list */
#ifdef ctFeatLSTAVLptr
	pLSTHED	ancdiv;		/* division between lists w/ & w/o avl space */
#endif
	LONG	anctot;		/* total items */
	LONG	ancavl;		/* # of avl items */
	UINT	anclst;		/* # of lists */
	UINT	anclav;		/* # of list with avl items */
} LSTANC;
typedef LSTANC ctMEM *	pLSTANC;

/*
** exactly one and only one of the following must be defined:
**		ABTnint
**		ABTint2
**		ABTint4
*/
#ifndef ABTnint
#define ABTnint
#endif

#ifdef ABTint2
#undef ABTnint
#ifdef ABTint4
#undef ABTint4
#endif
#endif

#ifdef ABTint4
#undef ABTnint
#endif

typedef struct abtlst {
	struct abtlst ctMEM
	       *ablink;
#ifdef ctFeatABLISThash
	struct abtlst ctMEM
		*abtrnprv;	/* node abort list by tran prev entry */
	struct abtlst ctMEM
		*abtrnnxt;	/* node abort list by tran next entry */
#endif
#ifdef ctLOG_IDX_NEW
        struct trebuf ctMEM
               *abbuf;	/* reverse pointer to buffer holding node.if any*/
	ULONG	abseq;	/* abort list sequence number			*/
#endif
#ifdef ctFeatABLISThash
	UINT	ablstnum;	/* abort node list hash bin number */
#endif
	LONG	abpos1;	/* ABNODSIZ is based on fields being contiguous */
#ifdef ctHUGEFILE
	LONG	abpos2;
#endif
	LONG	abtran;
	ULONG	abkey;
#ifdef ABTnint
	NINT	abnum;
#endif
#ifdef ABTint2
	COUNT	abnum;
#endif
#ifdef ABTint4
	LONG	abnum;
#endif
#ifdef ctFeat6BT
	UCOUNT	abtran2;
#endif
} ABTLST;
typedef ABTLST ctMEM *	pABTLST;

#ifdef ctHUGEFILE
			/* HUGEFILE forces ABTint4 */
#ifdef ctFeat6BT
#define ABNODSIZ	(5 * ctSIZE(LONG) + ctSIZE(UCOUNT))
#else
#define ABNODSIZ	(5 * ctSIZE(LONG))
#endif
#else  /* ~ctHUGEFILE */

#ifdef ABTnint
#define ABNODSIZ	(3 * ctSIZE(LONG) + ctSIZE(NINT))
#endif
#ifdef ABTint2
#define ABNODSIZ	(3 * ctSIZE(LONG) + ctSIZE(COUNT))
#endif
#ifdef ABTint4
#define ABNODSIZ	(4 * ctSIZE(LONG))
#endif

#endif /* ~ctHUGEFILE */

typedef struct idxlst {
	struct
	idxlst ctMEM
	       *ixlink;
#ifdef ctHUGEFILE
	LONG	ixnod2;
#endif
	LONG	ixnod1;
} IDXLST;
typedef IDXLST ctMEM *	pIDXLST;

typedef struct comlst {
	struct
	comlst ctMEM
	       *cmlink;
	LONG	cmtran;
#ifdef ctFeat6BT
	UCOUNT	cmtran2;
#endif
} COMLST;
typedef COMLST ctMEM *	pCOMLST;
typedef COMLST ctMEM * ctMEM * ppCOMLST;

#ifdef ctFeat6BT
#define COMLSTSIZ	(ctSIZE(LONG) + ctSIZE(UCOUNT))
#else
#define COMLSTSIZ	ctSIZE(LONG)
#endif

typedef struct dqmsg {
#ifdef ctHUGEFILE
	LONG	dnode2;  /* node offset - high word */
#endif
	LONG	dnode1;	 /* node offset */
	LONG	dtime;   /* creation time */
	LONG	dfid[3]; /* file id */
	COUNT	dmemb;   /* member number */
	COUNT	dflmd;	 /* file mode */
	COUNT	datmp;   /* retry counter */
	COUNT	dflmx;   /* flags */
	TEXT	dfile[MAX_NAME + 1]; /* file name */
} DQMSG;
typedef DQMSG ctMEM *	pDQMSG;
#ifdef ctHUGEFILE
#define	DELNODsiz	33
#else
#define	DELNODsiz	29
#endif

typedef struct  {
	LONG count; /* reference count */
	NINT status; /* error code */
} REF_STATUS;


/* internal queues */
typedef struct ctqHDR {
	struct ctqHDR * next;
	NINT size;
	TEXT BeginMessage;
} CTQHDR;
/* internal server queues */
typedef struct ctqdef {
	LONG ctqcnt;
	LONG ctqlmt;
	LONG ctqcntLIFO;
	NINT ctqhndls;
	NINT qmsgln;
	SEMA qlist;
	SEMAtim qcntl;
	CTQHDR * qhead;
	CTQHDR * qtail;
	CTQHDR * qsrch;
} CTQUEUEI;
/* macros for accessing global array */
#define ctqcnt(x) (ctqglobal[x].ctqcnt)
#define ctqlmt(x) (ctqglobal[x].ctqlmt)
#define ctqhndls(x) (ctqglobal[x].ctqhndls)


#define ctqFIFO 1   /* FIFO Queue mode */
#define ctqLIFO 2   /* LIFO Queue mode */

enum QUEUE_OP {
	QUEUE_OP_RETURN_ITEM = 1, /* unlink from queue and add to output message */
	QUEUE_OP_CONTINUE = 2  /* no - op */
};


#define ctKOCQFLAGzeropages	0x0001	/* closing file with zero cache pages in use */
#define ctKOCQFLAGisamstate	0x0002	/* ISAM state changing (e.g., delete index)  */

typedef struct kocqmsg {
	LONG	flags;		  /* options for closing the file	*/
	TEXT	filnam[MAX_NAME]; /* name of file to close		*/
} KOCQMSG;
typedef KOCQMSG ctMEM *	pKOCQMSG;

/* auto partition member purge queue message format */
typedef struct papqmsg {
	TEXT	filnam[MAX_NAME]; /* name of partition host file */
} PAPQMSG;
typedef PAPQMSG ctMEM *	pPAPQMSG;

typedef struct rqmsg {
#ifdef ctHUGEFILE
	LONG	rhdrpos2;
	LONG	rtime2;
#endif /* ctHUGEFILE */
	LONG	rfilpos1;
	LONG	rhdrpos1;
	LONG	rtime1;
	LONG	rmmbr;		/* deleted member (or chk spc mgt) */
	LONG	rfileid;
	LONG	rservid;
	LONG	rtimeid;
	LONG	rsrvd;
	TEXT	rfile[MAX_NAME + 1];
} RQMSG;
typedef RQMSG ctMEM *	pRQMSG;


typedef struct dedlok {
	COUNT	blkdby;	/* blocked by user#   */
	COUNT	blking;	/* # of users blocked */
} DEDLOK;
typedef DEDLOK ctMEM *	pDEDLOK;

typedef struct ctconbuf {	/* context key value info	*/
	pVOID	cb_rng;		/* ptr to range definition	*/
	FILNO	cb_key;		/* keyno			*/
	COUNT	cb_len;		/* key length			*/
	TEXT	cb_flg;		/* key existence flag		*/
	TEXT	cb_rsv;		/* reserved			*/
	TEXT	cb_val[2];	/* key value buffer head	*/
	} ctCONBUF;
typedef ctCONBUF ctMEM * pctCONBUF;
#define ctCONBUFSIZ	ctSIZE(ctCONBUF)
#define ctCONBUFm1	(ctCONBUFSIZ - 1)

typedef struct cticon {		/* ISAM context			*/
	struct cticon ctMEM
	       *iconptr;	/* context pointer (link)	*/
	pctCONBUF
		iconbuf;	/* alloc'd key value info	*/
#ifdef ctFeatDATFLT
#ifdef ctFeatDATFLTmulti
	pctDTFLT datflthed[ctDATFLT_MAX_INDEX];
				/* data filter list heads	*/
#else
	pVOID	datflt;		/* pointer to filter		*/
	LONG	dttflt;		/* type of data filter		*/
#endif
#endif
#ifdef ctPARTITION
	LONG	curpt;		/* current ISAM partition	*/
	LONG	curtt;		/* temporary ISAM partition	*/
	NINT	ptlst;		/* previous partition searched  */
#ifdef ctFeatPARTSERbuf
	NINT	ptkeyno;	/* user filno of last partition in key search */
#endif
#endif
	ctRECPT	iconpos1;	/* context record position	*/
#ifdef ctHUGEFILE
	ctRECPT	iconpos2;
#endif
	LONG	iconrsv;	/* reserved			*/
	COUNT	iconid;		/* context ID			*/
	FILNO	icondat;	/* user datno			*/
	COUNT	iconkeys;	/* number of keys in context	*/
#ifdef ctBEHAV_UPDATE_CONTEXT
	COUNT	allkeys;	/* is context on all keys?	*/
#endif
	UCOUNT	iflmd;		/* context sensitive file mode	*/
#ifdef ctFeatDAR
	UTEXT	IDfield_cur[8];	/* context IDfield buffer	*/
	UTEXT	IDfield_clen;	/* length/contents indicator	*/
#endif
#ifdef ctFeatFULLTEXTIDX
	pVOID	cb_fultxt;	/* ptr to full text index state	*/
#endif
	} ctICON;
typedef ctICON ctMEM *	pctICON;
typedef ctICON ctMEM * ctMEM * ppctICON;

typedef struct lticon {		/* local ISAM context		*/
	struct lticon ctMEM
	       *iconptr;	/* context pointer (link)	*/
	NINT	iconid;		/* context ID			*/
	NINT	icondat;	/* user datno			*/
	} ltICON;
typedef ltICON ctMEM *	pltICON;

#ifdef MULTITRD

#ifdef ctFeatFNCMEMSTATS
typedef struct {
	LONG8	alcbyt;
	LONG8	frebyt;
	LONG8	netbyt;
} FNCMEM;
#endif

typedef struct ctnotify	{
	struct ctnotify *notlnk;	/* object link		*/
	struct ctnotify *notqnk;	/* queue link		*/
	ctCallbackPtr	 notcbk;	/* function callback	*/
	NINT		 notobj;	/* object handle	*/
	NINT		 notmem;	/* idx memno		*/
	NINT		 notsys;	/* obj sys hndl		*/
	NINT		 notque;	/* queue handle		*/
	NINT		 notqin;	/* queue instance	*/
	NINT		 notown;	/* owner		*/
	NINT		 notcod;	/* opcode		*/
	NINT		 notcon;	/* contents		*/
	NINT		 notctl;	/* controls		*/
	} CTNOTIFY, * pNOTIFY;

typedef struct uasync {
	LONG	ua_handle;	/* async handle		*/
	LONG	ua_retval;	/* return value		*/
	NINT	ua_thrdid;	/* thread handle	*/
	NINT	ua_type;	/* thread type		*/
	} ctUASYNC, * pctUASYNC;


typedef struct blklst {
	SEMAblk	semab;
	struct
	blklst ctMEM
	       *blklnk;
	struct
	reclok ctMEM
	       *blklok;
	pVOID	blkfcb;
#ifdef ctSSrel2
	NINT	blksrl;		/* strict serialization flag	*/
#endif
	COUNT	blkusr;
	COUNT	blktyp;
#ifdef ctDBGreclok
	UINT	blkdbg;
	NINT	blkdbr;
	NINT	blkrsv;
#endif
#ifdef MTDEBUG
	TEXT	semtyp;
	TEXT	semnam[SNAMELEN];
#endif
	} BLKLST;
typedef BLKLST ctMEM *	pBLKLST;
typedef BLKLST ctMEM * ctMEM * ppBLKLST;

typedef struct timlst {
	SEMAtim	semab;
	struct
	timlst ctMEM
	       *blklnk;
	struct
	reclok ctMEM
	       *blklok;
	pVOID	blkfcb;
#ifdef ctSSrel2
	NINT	blksrl;		/* strict serialization flag	*/
#endif
	COUNT	blkusr;
	FILNO	blktyp;	/* block type- defined as FILNO because in some cases we store a user file number here */
#ifdef ctDBGreclok
	UINT	blkdbg;
	NINT	blkdbr;
	NINT	blkrsv;
#endif
#ifdef MTDEBUG
	TEXT	semtyp;
	TEXT	semnam[SNAMELEN];
#endif
	} TIMLST;
typedef TIMLST ctMEM *	pTIMLST;
typedef TIMLST ctMEM * ctMEM * ppTIMLST;

#ifdef ctFeatUSRBLKTIMOUT

/*
** support timeout attribute on user blocks
*/

#define BLULST		TIMLST
#define pBLULST		pTIMLST
#define ppBLULST	ppTIMLST

#define ctblurqs	cttimrqs
#define ctbluclr	cttimclr
#define ctbluwat	cttimwat
#define ctblubsy	cttimbsy
#define ctblucls	cttimcls

#else

#define BLULST		BLKLST
#define pBLULST		pBLKLST
#define ppBLULST	ppBLKLST

#define ctblurqs	ctblkrqs
#define ctbluclr	ctblkclr
#define ctbluwat	ctblkwat
#define ctblubsy	ctblkbsy
#define ctblucls	ctblkcls

#endif

#endif /* MULTITRD */

#ifdef ctFeatRWLOCKwindows
/*^***********************************/
/*
** Reader/writer lock support
*/

typedef    VOID (WINAPI    *pRWLFNC)(pVOID);
typedef BOOLEAN (WINAPI *pRWLFNCret)(pVOID);

#ifdef ctFeatRWLOCKctree
#define  ctCTRWLK_H	"ctrwlk.h"
#include ctCTRWLK_H
#endif

typedef struct ctrwlock {
	union {
#ifdef ctFeatRWLOCKctree
		ctRWL		 rwl;	/* c-tree reader/writer lock	   */
#else
		CRITICAL_SECTION cs;	/* Windows critical section	   */
#endif
		SRWLOCK		 srw;	/* Windows slim reader/writer lock */
	} u;
        int	   	padg;
#if	defined(ctMTXtoWLOCK) || defined(needRWLauxflds)
	int		ownr;
#endif
#if	defined(needRWLauxflds)
	int		type;
#endif
#if defined(ctDBGSEMCNT) || defined(ctDBGRWLCNT)
	int		loc;
#endif
#ifdef ctDBGfcqa
	int		netlok;
#endif
} ctRWLOCK;
typedef ctRWLOCK ctMEM *    pctRWLOCK;
/*~***********************************/
#endif /* ctFeatRWLOCKwindows */

#if defined(ctPortUNIX) && defined(MULTITRD) && defined(ctPortNATIVE_THREADS)
/*^***********************************/
/*
** Reader-writer lock support for Unix systems.
*/

typedef struct ctrwlock {
#ifdef ctPortSOLARIS
        rwlock_t        rwl;
#else
        pthread_rwlock_t rwl;
#endif
        int              padg;
        int              ownr;
        int              type;
#if defined(ctDBGSEMCNT) || defined(ctDBGRWLCNT)
        int              loc;
#endif
#ifdef ctDBGfcqa
        int              netlok;
#endif
} ctRWLOCK;
typedef ctRWLOCK ctMEM * pctRWLOCK;

/*~***********************************/
#endif /* ctPortUNIX && MULTITRD && ctPortNATIVE_THREADS */


#ifdef ctFeatOPENSSL
#include "ctssl.h"
#endif

/* options for ctdll_load() */
typedef enum ctDllLoadOptions_t {
	CTDLL_LOAD_OPTION_USE_SYSTEM_DIR = 0x00000001 /* use system directory for this DLL */
} CTDLL_LOAD_OPTIONS;

typedef struct ctdllinf_t {
#ifdef ctFeatCTDLLerrbuf
	NINT		size;		/* [IN] Size of structure.	*/
	NINT		errbuflen;	/* [IN] Size of error buffer.	*/
	pTEXT		errbuf;		/* [OUT] Optional error buffer.	*/
#endif
	pTEXT		name;		/* [IN] Name of DLL		*/
	pVOID		handle;		/* [OUT] Handle to DLL		*/
#ifdef ctFeatDLL_LOAD_OPTIONS
	NINT		options;	/* [IN] Option bits (see CTDLL_LOAD_OPTIONS) */
#endif
	NINT		fnccount;	/* [IN] Number of DLL functions	*/
	ppTEXT		fncnames;	/* [IN] List of function names	*/
	ppVOID		fncptrs;	/* [OUT] List of function pointers */
} CTDLL, ctMEM *pCTDLL;

#ifdef ctPARTITION
typedef struct partmbr {
	NINT	filno;		/* system file number			*/
	NINT	status;		/* existence status			*/
#ifdef ctPARTITIONinstnc
	NINT	instnc;		/* instance number			*/
#endif
#ifdef ctFeatFILEBLOCK
	NINT	filnob;		/* store filno after internal FILBLK	*/
#endif
	pTEXT	filnam;		/* partition member data file name	*/
	} PARTMBR;
typedef PARTMBR ctMEM * pPARTMBR;

#define partresPLCsize		16
typedef struct partres {
		ULONG	restyp;
		ULONG	resnum;
		TEXT	resnam[FCRNAM_LEN];
		TEXT	resstr[partresPLCsize];	/* place holder */
	} PARTRES, * pPARTRES;

#define partserPLCsize		16
typedef struct partser {
		ULONG	curseq;		/* current mbr sequence nbr	*/
		LONG	cur_hw;		/* high word record offset	*/
		ULONG	cur_lw;
		ULONG	curstt;		/* status indicator		*/
		TEXT	curkey[partserPLCsize];	/* key buf place holder	*/
	} PARTSER, * pPARTSER;
#endif

typedef struct chnstrc  {
	SEMA	siosema;	/* channel semaphore			*/
	RNDFILE	safd;		/* channel file descriptor		*/
#ifdef ctBEHAV_CHKSAVE
	UINT	skipsave;	/* TRUE: skip save action		*/
#endif
	} CHNSTRC, * pCHNSTRC, ** ppCHNSTRC;

typedef struct bfhlst {
	struct bfhlst ctMEM *flnk;
	struct bfhlst ctMEM *blnk;
	pVOID		     hbuf;
#if (defined(ctDBGputhsh) || defined(ctDBGputdsh))
	UINT		     binn;	/* bin number */
#endif
	} BHL;
typedef BHL ctMEM *	pBHL;
typedef BHL ctMEM * ctMEM * ppBHL;

#if defined(ctFeatDBSEMAhsh) || defined(ctFeatGNSEMAhsh)
#ifdef ctFeatRWLOCK
#ifdef ctDBG_RWLOCK
#include "ctatrd.h"
#endif
#endif

typedef struct bfhary {
	BHL	  bhl;
	SEMAmut	  mtx;
#ifdef ctFeatRWLOCK
	RWLOCKmut rwl;
#endif
	} BHLARY;
typedef BHLARY ctMEM *	pBHLARY;
typedef BHLARY ctMEM * ctMEM * ppBHLARY;

#if defined(ctFeatDISTbufcnt) || defined(ctFeatDISTdatcnt)
typedef struct bfharycnt {
	BHLARY	bhlary;
	LONG	bhlcnt;
	} BHLARYCNT;
typedef BHLARYCNT ctMEM *	pBHLARYCNT;
typedef BHLARYCNT ctMEM * ctMEM * ppBHLARYCNT;
#endif
#endif

/*
** ctCMPREC resource definition
**
** actual contents of parm member may be smaller or larger than
** the sixteen byte placeholder.
*/
typedef struct cmprecres_t {
	ULONG	restyp;
	ULONG	resnum;
	TEXT	resnam[FCRNAM_LEN];
	LONG	cmptype;	/* compression type ID			*/
	LONG	cmpvrsn;	/* compression version # (> 0)		*/
	LONG	totlen;		/* entire resource length		*/
	LONG	cmplen;		/* length of compression parameter strct*/
	TEXT	parm[16];	/* place holder for strct and DLL name	*/
	} CMPRECRES, *pCMPRECRES, **ppCMPRECRES;

#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)

/*
** compression function pointers
*/
#ifdef PROTOTYPE
struct cmprecfnc_t; /* forward declaration */
typedef NINT  (*pCMPRECplaceHolder)(pVOID );
typedef NINT  (*pCMPREC_FncInit)(struct cmprecfnc_t * , pTEXT , VRLEN);
typedef NINT  (*pCMPREC_FncExit)(struct cmprecfnc_t * );
typedef pVOID (*pCMPREC_CmpInit)(struct cmprecfnc_t * );
typedef NINT  (*pCMPREC_CmpActn)(pVOID , struct cmprecfnc_t * ,pVOID , VRLEN , pVOID , pVRLEN); 
typedef NINT  (*pCMPREC_CmpExit)(pVOID , struct cmprecfnc_t *);
typedef pVOID (*pCMPREC_ExpInit)(struct cmprecfnc_t * );
typedef NINT  (*pCMPREC_ExpActn)(pVOID , struct cmprecfnc_t * ,pVOID , VRLEN , pVOID , pVRLEN); 
typedef NINT  (*pCMPREC_ExpExit)(pVOID , struct cmprecfnc_t *);
#else
typedef NINT  (*pCMPRECplaceHolder)();	/* used as place holder in union     */
typedef NINT  (*pCMPREC_FncInit)();	/* one time init after load	     */
typedef NINT  (*pCMPRECFncExit)();	/* one time exit before unload	     */
typedef pVOID (*pCMPREC_CmpInit)();	/* user/file cmp init after open     */
typedef NINT  (*pCMPREC_CmpActn)();	/* compress			     */
typedef NINT  (*pCMPREC_CmpExit)();	/* user/file cmp exit before close   */
typedef pVOID (*pCMPREC_ExpInit)();	/* user/file exp init after open     */
typedef NINT  (*pCMPREC_ExpActn)();	/* expand			     */
typedef NINT  (*pCMPREC_ExpExit)();	/* user/file exp exit before close   */
#endif

typedef struct cmprecproc_t {
	pCMPREC_FncInit	FncInit;
	pCMPREC_FncExit	FncExit;
	pCMPREC_CmpInit	CmpInit;
	pCMPREC_CmpActn	CmpActn;
	pCMPREC_CmpExit	CmpExit;
	pCMPREC_ExpInit	ExpInit;
	pCMPREC_ExpActn	ExpActn;
	pCMPREC_ExpExit	ExpExit;
	} CMPRECPROC;

/*
** compression FNC structure
*/
typedef struct cmprecfnc_t {
	union  {
		pCMPRECplaceHolder	fncloop[NbrCmpFnc];
		CMPRECPROC		fncaddr;
	} fncU;
	pVOID		dllhandle;
	pVOID		attrval;	/* addr of attrval IF allocated */
	NINT		comptype;
	NINT		compvrsn;
	TEXT		dllname[MAX_NAME];
	} CMPRECFNC, *pCMPRECFNC;
#endif /* ctCMPREC */

/*
** Deferred index resource definition
**
** actual contents of parm member may be smaller or larger than
** the sixteen byte placeholder.
*/
typedef struct dfrkresdat_t {
	LONG	dfrktype;	/* deferred index type ID		*/
	LONG	dfrkvrsn;	/* resource version # (> 0)		*/
	LONG	totlen;		/* entire resource length		*/
	LONG	prmlen;		/* length of parameter structure	*/
	TEXT	parm[16];	/* place holder for struct and DLL name	*/
} DFRKRDT, *pDFRKRDT;

typedef struct dfrkres_t {
	ULONG	restyp;
	ULONG	resnum;
	TEXT	resnam[FCRNAM_LEN];
	DFRKRDT	resdat;
	} DFRKRES, *pDFRKRES, **ppDFRKRES;

/* Modes for dfrkUpdateDeferredIndexResource() */
#define DFRKPRM_SETCALLBACK	1	/* set callback information	  */
#define DFRKPRM_SETPENDINGIDX	2	/* set pending index information  */
#define DFRKPRM_CMTPENDINGIDX	3	/* make pending indices permanent */

struct iidx; /* forward declaration */
typedef struct dfrkrpm_t {
	LONG	mode;		/* What is being updated		*/
	LONG	numidx;		/* Number of pending indices		*/
	FILNO	frskeyno;	/* User filno of first pending index	*/
	pTEXT	dllname;	/* Callback DLL name			*/
	pTEXT	params;		/* Callback parameters			*/
   struct iidx *pidxs;		/* Pending index definitions		*/
} DFRKRPM, *pDFRKRPM;

/*
** Deferred indexing function pointers
*/
#ifdef PROTOTYPE
struct dfrkfnc_t; /* forward declaration */

struct _dfkctx; /* forward declaration */
typedef struct _dfkctx *pDFKCTX;

struct dfrky; /* forward declaration */
typedef struct dfrky *pDFRKY;

struct dfrst; /* forward declaration */
typedef struct dfrst *pDFRST;

typedef NINT  (*pDFRKplaceHolder)(pVOID );
typedef NINT  (*pDFRK_FileOpenFnc)(struct dfrkfnc_t * , pTEXT , VRLEN);
typedef NINT  (*pDFRK_FileCloseFnc)(struct dfrkfnc_t * );
typedef NINT  (*pDFRK_PerformOpFnc)(pDFKCTX pdfkctx,pDFRKY pdfrky,pNINT pdoidxop); 
typedef NINT  (*pDFRK_ErrorFnc)(NINT errcod,pDFKCTX pdfkctx,pDFRKY pdfrky,pDFRST pdfrst);
#else
typedef NINT  (*pDFRKplaceHolder)();	/* used as place holder in union     */
typedef NINT  (*pDFRK_FileOpenFnc)();	/* one time init after load	     */
typedef NINT  (*pDFRK_FileCloseFnc)();	/* one time exit before unload	     */
typedef NINT  (*pDFRK_PerformOpFnc)();	/* perform operation		     */
typedef NINT  (*pDFRK_ErrorFnc)();	/* error			     */
#endif

typedef struct dfrkproc_t {
	pDFRK_FileOpenFnc	FileOpenFunc;
	pDFRK_FileCloseFnc	FileCloseFunc;
	pDFRK_PerformOpFnc	PerformOpFunc;
	pDFRK_ErrorFnc		ErrorFunc;
	} DFRKPROC;

/*
** Deferred indexing FNC structure
*/
typedef struct dfrkfnc_t {
	union  {
		pDFRKplaceHolder	fncloop[NbrDfrkFnc];
		DFRKPROC		fncaddr;
	} fncU;
	pVOID		dllhandle;
	pVOID		attrval;	/* addr of attrval IF allocated */
	NINT		dfrktype;
	NINT		dfrkvrsn;
	TEXT		dllname[MAX_NAME];
	} DFRKFNC, *pDFRKFNC;

/*
** Record update callback resource definition
**
** actual contents of parm member may be smaller or larger than
** the sixteen byte placeholder.
*/

#define RUCBRES_VERS_V01	1	/* initial version of structure	*/

#define RUCBRES_VERS_CUR	RUCBRES_VERS_V01	/* current version */

typedef struct rucbres_t {
	ULONG	restyp;
	ULONG	resnum;
	TEXT	resnam[FCRNAM_LEN];
	LONG	verson;		/* resource version # (> 0)		*/
	LONG	totlen;		/* entire resource length		*/
	LONG	numrucb;	/* number of callback functions		*/
	TEXT	resdat[16];	/* place holder for callback info	*/
	} RUCBRES, *pRUCBRES, **ppRUCBRES;

/* Modes for ctSetRecordUpdateCallbackResource() */
#define RUCBPRM_ADDCALLBACK	1	/* add callback function	*/
#define RUCBPRM_UPDCALLBACK	2	/* modify callback function	*/
#define RUCBPRM_DELCALLBACK	3	/* remove callback function	*/

/*
** Record update callback function pointers
*/

/* record update callback parameters */
typedef struct rucbf {
	pTEXT	datnam;		/* Data file name.			     */
	pTEXT	params;		/* Optional callback parameter string.	     */
	NINT	callbk;		/* Current context for this call.	     */
	FILNO	datno;		/* User file number of data file.	     */
	pVOID	psession;	/* User-defined connection-level pointer.    */
	pVOID	ptable;		/* User-defined table-level pointer.	     */
} RUCBF, *pRUCBF;

/* State information to pass to record update callback function: */
typedef struct rucbstt_t {
	LONG	verson;	/* structure version			*/
	LONG	avail;	/* padding- available for use		*/
	LONG8	tranno;	/* transaction number for the operation */
} RUCBSTT, *pRUCBSTT;

#define RUCBSTT_VERSION_V01	1		/* initial version of struct */
#define RUCBSTT_VERSION	RUCBSTT_VERSION_V01	/* current version of struct */

typedef NINT  (*pRUCBplaceHolder)(pVOID );
typedef NINT  (*pRUCB_FileOpenFnc)(pRUCBF prucbf);
typedef NINT  (*pRUCB_FileCloseFnc)(pRUCBF prucbf);
typedef NINT  (*pRUCB_RecordUpdateFnc)(pRUCBF prucbf,pDFRKY pdfrky);
typedef NINT  (*pRUCB_RecordUpdateFnc2)(pRUCBF prucbf,pDFRKY pdfrky,pRUCBSTT prucbstt);
typedef NINT  (*pRUCB_CheckVersionFnc)(pRUCBACB prucbacb,pLONG pversion); 
typedef NINT  (*pRUCB_Has4byteFilnoSupportFnc)(void);

#define RUCB_MASK_FILE		(0x00000100) /* file state change	*/
#define RUCB_MASK_RECORD	(0x00000200) /* record modification	*/
#define RUCB_MASK_GET_MUTEX	(0x00000400) /* must acquire mutex	*/

#define	RUCB_OPEN_FILE		(0x00000001 | RUCB_MASK_FILE)
#define	RUCB_CLOSE_FILE		(0x00000002 | RUCB_MASK_FILE)
#define	RUCB_DELETE_FILE	(0x00000003 | RUCB_MASK_FILE)
#define	RUCB_ADD_RECORD		(0x00000004 | RUCB_MASK_RECORD)
#define	RUCB_UPDATE_RECORD	(0x00000005 | RUCB_MASK_RECORD)
#define	RUCB_DELETE_RECORD	(0x00000006 | RUCB_MASK_RECORD)
#define	RUCB_COMMIT_TRAN	(0x00000007)
#define	RUCB_APPLY_OP_THRD	(0x00000008)
#define	RUCB_DATASCAN		(0x00000009) /* scan of data file	*/

typedef struct rucbproc_t {
	pRUCB_FileOpenFnc	FileOpenFunc;
	pRUCB_FileCloseFnc	FileCloseFunc;
	pRUCB_RecordUpdateFnc	RecordUpdateFunc;
	} RUCBPROC;

typedef struct rucblst {
/* permanent information: */
	LONG	verson;		/* Version of structure			    */
	LONG	calltm;		/* Time at which callback is called	    */
	LONG	varlen;		/* Size of variable-length region	    */
/* permanent information that resides in pvarinf region in memory: */
	pTEXT	cbname;		/* Name for this callback		    */
	pTEXT	dllname;	/* Name of the DLL that contains the callback
				** functions				    */
	pTEXT	params;		/* Optional callback parameter string	    */
	ppTEXT	fncnames;	/* Callback function names		    */
/* temporary (in memory) information: */
	LONG	apiversion;	/* Version of RUCB API in use		    */
	LONG	refcnt;		/* Number of user references to callback    */
	pVOID	dllhandle;	/* Handle to loaded callback DLL	    */
	RUCBPROC
		fncptrs;	/* Callback function pointers		    */
	pTEXT	pvarinf;	/* Storage for the variable-length callback
				** information				    */
} RUCBLST, *pRUCBLST, **ppRUCBLST;

/* Size of fixed length part of permanent info in RUBCLST structure */
#define RUCBLST_FIXED_LEN (3 * sizeof(LONG))

/* JSON key description. */
typedef struct jsnkds {
	/* In the union below, jsnkey is used for jsntyp == json_type_object,
	and jsnaryidx is used for jsntyp == json_type_array. */
    union {
      struct {
	pTEXT		jsnkey;		/* [IN,OUT] buffer for json key name */
	NINT		jsnkeymax;	/* [IN,OUT] size of jsnkey buffer in bytes */
      } obj;
	LONG8		jsnaryidx;	/* [OUT] json array index value */
    } u;
	NINT		jsntyp;		/* [IN,OUT] type of the key entry */
} JSNKDS, *pJSNKDS, **ppJSNKDS;

/* Wrapper for JSON key description. */
typedef struct jsnkdsw {
	pJSNKDS	pjsnkds;	/* array of key desc entries */
	LONG	njsnkds;	/* number of entries in key desc list */
	TEXT	jsnkst[1];	/* json key string */
} JSNKDSW, *pJSNKDSW, **ppJSNKDSW;
/*
** ctFeatFLEXREC resource definition
**
** actual contents of parm member may be smaller or larger than
** the sixteen byte placeholder.
*/
typedef struct flexrecres_t {
	ULONG	restyp;
	ULONG	resnum;
	TEXT	resnam[FCRNAM_LEN];
	LONG	verson;		/* resource version # (> 0)		*/
	LONG	totlen;		/* entire resource length		*/
	LONG	numflxr;	/* number of record converters		*/
	} FLEXRECRES, *pFLEXRECRES, **ppFLEXRECRES;

/* Supported record descriptor types: */
#define ctRDSCver1 1 /* record descriptor version 1 */

typedef struct recschdsc {
	LONG	action;		/* field action */
	pTEXT	fsymb;		/* field name */
	UCOUNT	ftype;		/* field type */
	UCOUNT	flen;		/* field length */
	pVOID	fdflt;		/* default value */
	UCOUNT	fdlen;		/* default value len */
	pTEXT	newfsymb;	/* new field name */
	UCOUNT	newftype;	/* new field type */
	UCOUNT	newflen;	/* new field length */
	pVOID	newfdflt;	/* new default value */
	UCOUNT	newfdlen;	/* new default value len */
} RCSCHD, *pRCSCHD;

#define RCACTnochange	0	/* no changes to this field */
#define RCACTaddfield	1	/* add this field */
#define RCACTdelfield	2	/* delete this field */
#define RCACTupdfield	3	/* change attributes of this field */

#define RCACTmask	0x00000003 /* action mask */

#define RCACTupdflen	0x00000004	/* update field length */
#define RCACTupdftyp	0x00000008	/* update field type */
#define RCACTupdfnam	0x00000010	/* update field name */
#define RCACTupdfdef	0x00000020	/* update field default value */

/* Record converter resource format, version 1:

LONG version (rdtype)
LONG resource length (rclen)
LONG numactions (rdcount)
LONG old record length (oldrln)
LONG new record length (newrln)

for each action (RCSCHD)
TEXT action
if action is add:
	UCOUNT fieldtype
	UCOUNT fieldlen
	TEXT fieldname[] (null terminated)
	LONG defaultvaluelen
	TEXT defaultvalue[defaultvaluelen]
if action is delete or no change:
	UCOUNT fieldtype
	UCOUNT fieldlen
	TEXT fieldname[] (null terminated)
if action is update:
    old values
	UCOUNT fieldtype
	UCOUNT fieldlen
	TEXT fieldname[] (null terminated)
	LONG defaultvaluelen
	TEXT defaultvalue[defaultvaluelen]
    new values
	if (action & RCACTupdftyp):
		UCOUNT newfieldtype
	if (action & RCACTupdflen):
		UCOUNT newfieldlen
	if (action & RCACTupdfnam):
		TEXT newfieldname[] (null terminated)
	if (action & RCACTupdfdef):
		LONG defaultvaluelen
		TEXT defaultvalue[defaultvaluelen]
...

*/

/*
** memory file hash list
**
** file header will use a MHL:	overload ppMHL in mlnk to point to
**				array of MHL anchors; and msiz will
**				store # of anchors
**
** each memory record begins with a MHL:
*/
typedef struct mhl {
	struct mhl ctMEM *
		mlnk;	/* pointer to next hash overflow		 */
	VRLEN	msiz;	/* size of memory area				 */
#ifdef ctFeatMEMFILErefcnt
	AULONG	mstt;	/* state bits: drrrrrrr uuuuuuuu, where d is deleted
			** bit, rrrrrrr is refcnt, and uuuuuuuu is musr */
#else
	NINT	musr;	/* sOWNR if record is not committed, or ctMEMNODEmusr
			** to signify memory record is for an index node */
#endif
#if defined(ctPortSOLARIS) && !defined(ct8P) && defined(ctFeatRWLOCK)
	/* 32bit Solaris requires 8-byte alignment for rwlock_t. Here we add
	** 4 byte padding so that this memory record header is a multiple of
	** 8 bytes. This ensures that a memory index buffer's idxsem field is
	** 8-byte aligned. */
	LONG	pad;
#endif
	} MHL, ctMEM * pMHL, ctMEM * ctMEM * ppMHL;

#define BEGCTL		phyrec1
#define iostart(ctnum)	((pTEXT) &ctnum->phyrec1)
#ifdef ctHUGEFILE
#define iostart2(ctnum)	((pTEXT) &ctnum->phyrec2)
#define BEGCTL2		phyrec2
#endif /* ctHUGEFILE */
#define ctFILE3(ctnum)	 ((pCTFILE3) iostart(ctnum))
#define ctFILE3s(hdrnum) ((pCTFILE3) &hdrnum.phyrec1)

typedef struct wfils2 {	/* Partial File Control Structure	*/
	ctRECPT	phyrec1;	/* last byte offset of file		*/
	ctRECPT	delstk1;	/* top of delete stack: fixed len data	*/
	ctRECPT	numrec1;	/* last byte offset written		*/
	LONG	reshdr1;	/* resource header			*/
	LONG	lstmbr1;	/* last super file member/position	*/
	ctRECPT	sernum1;	/* serial number			*/
#ifdef ctHUGEFILE
	ctRECPT	phyrec2;	/* last byte offset of file		*/
	ctRECPT	delstk2;	/* top of delete stack: fixed len data	*/
	ctRECPT	numrec2;	/* last byte offset written		*/
	LONG	reshdr2;	/* resource header			*/
	LONG	lstmbr2;	/* last super file member/position	*/
	ctRECPT	sernum2;	/* serial number			*/
#endif /* ctHUGEFILE */
} CTFILE2;
typedef CTFILE2 ctMEM *	pCTFILE2;

typedef struct wfils3 {	/* Partial File Control Structure		*/
	ctRECPT	phyrec1;/* last byte offset of file		00x	*/
	ctRECPT	delstk1;/* top of delete stack: fixed len data	04x	*/
	ctRECPT	numrec1;/* last byte offset written		08x	*/
	LONG	reshdr1;/* resource header			0cx	*/
	LONG	lstmbr1;/* last super file member/position	10x	*/
	ctRECPT	sernum1;/* serial number			14x	*/
	ctRECPT nument1;/* active entries			18x	*/
	LONG    root1;/* B-Tree root 				1cx	*/
	LONG	fileid;	/* unique file id			20x	*/
	LONG	servid;	/* unique server id			24x	*/
	UCOUNT	verson;	/* configuration options at create	28x	*/
	UCOUNT	recszh;	/* node record size			2ax	*/
	UCOUNT	reclen;	/* data record length			2cx	*/
	UCOUNT	extsiz;	/* extend file (chunk) size		2ex	*/
	UCOUNT	flmode;	/* file mode (virtual, etc)		30x	*/
	UCOUNT	logtyp; /* permanent components of file mode	32x	*/
	UCOUNT	maxkbl;	/* maximum key bytes leaf-var		34x	*/
	UCOUNT	maxkbn;	/* maximum key bytes non leaf-var 	36x	*/
	TEXT	updflg;	/* update (corrupt) flag		38x	*/
#ifdef ctFeatNOISMKEYUPD
	UTEXT	ktype;	/* file type flag			39x	*/
#else
	TEXT	ktype;	/* file type flag			39x	*/
#endif
	TEXT	keydup; /* duplicate flag			3ax	*/
	TEXT	deltyp; /* flag for type of idx delete		3bx	*/
	UTEXT	keypad; /* padding byte				3cx	*/
	UTEXT	flflvr;	/* file flavor				3dx	*/
	UTEXT	flalgn;	/* file alignment			3ex	*/
	UTEXT	flpntr;	/* file pointer size			3fx	*/
	UCOUNT	clstyp; /* flag for file type			40x	*/
	COUNT   length;	/* key length 				42x	*/
	COUNT	nmem;	/* number of members			44x	*/
	COUNT	kmem;	/* member number			46x	*/
	LONG	lanchr1;/* left most leaf anchor		48x	*/
	LONG	supid;	/* super file member #			4cx	*/
	LONG	hdrpos1;/* header position			50x	*/
	LONG	sihdr;	/* superfile header index hdr position	54x	*/
	LONG	timeid;	/* time id#				58x	*/
	UCOUNT	suptyp;	/* super file type 			5cx	*/
	UCOUNT	maxmrk;	/* maximum exc mark entries per leaf	5ex	*/
	UCOUNT	namlen;	/* MAX_NAME at creation			60x	*/
	UCOUNT	xflmod; /* extended file mode info		62x	*/
	LONG	defrel;	/* file def release mask		64x	*/
	LONG	hghtrn;	/* tran# high water mark for idx	68x	*/
	LONG	hdrseq1;/* wrthdr sequence #			6cx	*/
	LONG	tstamp; /* update time stamp			70x	*/
	LONG	camanc; /* camo anchor (4 bytes only)		74x	*/
	LONG	xtdhdr1;/* extended header anchor		78x	*/
	LONG	cretrn;	/* dependent transaction ID		7cx	*/
} CTFILE3;
typedef CTFILE3 ctMEM *	pCTFILE3;

#ifdef ctHUGEFILE
typedef struct wfils8 {	/* Partial Extended File Control Structure	*/
	ctRECPT	phyrec2;/* last byte offset of file		0x00 80	*/
	ctRECPT	delstk2;/* top of delete stack: fixed len data	0x04 84	*/
	ctRECPT	numrec2;/* last byte offset written		0x08 88	*/
	LONG	reshdr2;/* resource header			0x0c 8c	*/
	LONG	lstmbr2;/* last super file position		0x10 90	*/
	ctRECPT	sernum2;/* serial number			0x14 94	*/
	ctRECPT nument2;/* active entries			0x18 98	*/
	LONG    root2;	/* B-Tree root 				0x1c 9c	*/
	LONG	seganc2;/* offset in 1st segment to segmap anchr0x20 a0	*/
	LONG	seganc1;/* low word				0x24 a4	*/
	LONG	lxtsiz;	/* large extent size			0x28 a8	*/
	LONG	fxtsiz;	/* first extent size			0x2c ac	*/
	LONG	flmode2;/* x8 only additional file mode bits	0x30 b0	*/
	LONG	segsiz2;/* host segment size			0x34 b4	*/
	LONG	segsiz1;/* low word				0x38 b8	*/
	LONG	mxfilz2;/* max file size high word		0x3c bc	*/
	LONG	mxfilz1;/* low word				0x40 c0	*/
	LONG	sghdrz;	/* segment header size			0x44 c4	*/
	LONG	lanchr2;/* left most leaf anchor		0x48 c8	*/
	LONG	segmax;	/* maximum # of segments		0x4c cc	*/
	LONG	hdrpos2;/* header position			0x50 d0	*/
	LONG	x8sign; /* extended header verify signature	0x54 d4	*/
	LONG	timeid2;/* reserved for eventual 8-byte time	0x58 d8	*/
	LONG	seglst; /* # activated segments			0x5c dc	*/
	LONG	prawno;	/* partition raw member # | host shift	0x60 e0	*/
	LONG	flmode3;/* extended hdr file mode bits		0x64 e4	*/
	LONG	hghtrn2;/* reserved for eventual 8-byte tran	0x68 e8	*/
	LONG	hdrseq2;/* matching hdr sequence number		0x6c ec	*/
	LONG	tstamp2;/* reserved for eventual 8-byte time	0x70 f0	*/
	ULONG	dskful;	/* disk full threshold			0x74 f4	*/
	LONG	xtdhdr2;/* extended header anchor high word	0x78 f8	*/
	LONG	cretrn2;/* available for extended tfil# range	0x7c fc	*/
	UCOUNT	hsrlpos;/* offset to serial # in record (ISAM)	0x00 100*/
	COUNT	hsrllen;/* length of serial number field	0x02 102*/
	UCOUNT	maxpartmbr; /* max partition members		0x04 104*/
	UCOUNT	schmid;	/* flexrec schema ID			0x06 106*/
	LONG	prtkey;	/* relative key # for partition key	0x08 108*/
	ULONG	splcnt;	/* split counter			0x0c 10c*/
	LONG	xtdcmp;	/* extended key compression factor	0x10 110*/
	LONG	idxhgt;	/* index height				0x14 114*/
	LONG	dstent1;/* approx # distinct index entries LW	0x18 118*/
	LONG	dstent2;/* approx # distinct index entries HW	0x1c 11c*/
	LONG	dstsegx;/* maxNbr of partial key distinct counts0x20 120*/
	LONG	dstsegn;/* number of partial key distinct counts0x24 124*/
	LONG	dstsegs[ctMAXSEGdistinct];/* # of sgements	0x28 128*/
	LONG	dstsegl[ctMAXSEGdistinct];/* tot len of segments0x38 138*/
	LONG	dstseg1[ctMAXSEGdistinct];/* distinct count low	0x48 148*/
	LONG	dstseg2[ctMAXSEGdistinct];/* distinct count high0x58 158*/
	LONG	dstrsvd[8];/* rsrv space for 2 more partial keys0x68 168*/
	LONG	darhdr2;/* high word DAR anchor position	0x88 188*/
	LONG	darhdr1;/*  low word DAR anchor position	0x8c 18c*/
	UTEXT	darnbr[FC_DAR_NBR];/* count of each DAR		0x90 190*/
	LONG	pinstnc;/* partition member instance number	0x98 198*/
	ULONG	dfrkctr;/* deferred index create counter	0x9c 19c*/
	LONG8	pprgent8;/* partition host purged entries	0xa0 1a0*/
	LONG8	pachent8;/* partition host archived entries	0xa8 1a8*/
	LONG8	dfrkops;/* count of deferred key operations	0xb0 1b0*/
	LONG8	sfidino;/* system file ID- inode ID		0xb8 1b8*/
	ULONG	sfiddev;/* system file ID- device ID		0xc0 1c0*/
	LONG	lrsv1;	/* reserve for future LONG value	0xc4 1c4*/

	/* Be sure to update rev_fhdr2 for UNIFRMAT when adding to this structure */
#ifdef ctHDRPAD
	/*				padding starts at	0xc8 1c8*/
	TEXT	rspad[ctHDRPAD];
#endif
} CTFILE8;
typedef CTFILE8 ctMEM *	pCTFILE8;
#define ctFILE8(ctnum)	 	((pCTFILE8) iostart2(ctnum))
#define ctFILE8s(hdrnum)	((pCTFILE8) &hdrnum.phyrec2)

#else  /* ~ctHUGEFILE */

typedef TEXT * pCTFILE8;
#define ctFILE8(ctnum)		((pCTFILE8) 0)
#define ctFILE8s(hdrnum)	((pCTFILE8) 0)

#endif /* ~ctHUGEFILE */

typedef struct reuselist {
	struct reuselist ctMEM
		*lstlnk;
	LONG	node2;
	LONG	node1;
	LONG	nstamp;
} RUSLST, ctMEM * pRUSLST;

#ifdef MULTITRD

typedef struct reclok {
	struct reclok ctMEM
		*rllink;/* forward link				*/
	struct reclok ctMEM
		*rlrlnk;/* reverse link				*/
	ctRECPT	rlbpos1;/* byte position			*/
#ifdef ctHUGEFILE
	ctRECPT	rlbpos2;/* byte position			*/
#endif
	pBLULST rlblkh;	/* block list head			*/
	pBLULST rlblkt; /* block list tail			*/
	NINT	rlusrn;	/* user number of owner			*/
	NINT	rltype;	/* write lock or read lock		*/
#ifdef ctMULTIOPN
	NINT	rlufil;	/* user file number (reverse map)	*/
#endif
#ifdef ctFeatLOKDYN
#ifdef TRANPROC
	LONG	rlsavp;	/* savepoint# on lock acquisition	*/
	LONG	rlsvpp;	/* savepoint# on prior read lock	*/
#endif
#endif
#ifdef ctBEHAV_CMTLOK
	NINT	rlcmt;	/* commit lock count
				-1	write lock
				0 or 1	no commit lock
				n >= 2	n-1 readers
				n < -1	-n-1 readers with writer
					waiting. no more readers
					accepted until write
					lock completes.		*/
#endif
#ifdef ctSSrel2
	NINT	rlsrl;	/* strict serialization flag		*/
#endif
#ifdef ctDBGreclok
	UINT	rlstmp;		/* sequence #			*/
	UINT	rlcrat;		/* creation locale		*/
	UINT	rlpath;		/* processing flags		*/
	NINT	rlprir;		/* prior type			*/
#endif
	NINT	rlflags;/* lock flags */
} RECLOK;
typedef RECLOK ctMEM *	pRECLOK;
typedef RECLOK ctMEM * ctMEM * ppRECLOK;

/* rlflags bits */
#define RLFLAGS_FORCE_BLOCKING_LOCK	0x00000001 /* attempt to acquire this lock is automatically blocked even if not requested */

#endif /* MULTITRD */

#ifdef ctFeatLOCKfile
/* Lock request order */
typedef struct lokord {
	NINT	taskid;
	struct lokord *next;
	struct lokord *prev;
} LOKORD, *pLOKORD;
#endif

/* resource list entry */
typedef struct ctreslstentry {
	ULONG8	offset; /* starting offset of resource in data file */
	ULONG	length; /* size of resource in bytes */
} CTRESOURCE_LIST_ENTRY, *pCTRESOURCE_LIST_ENTRY;

/* resource list for a data file */
typedef struct ctreslst {
	pCTRESOURCE_LIST_ENTRY pResourceList; /* resource list (array) */
	NINT	allocatedEntries; /* number of entries allocated for list */
	NINT	usedEntries; /* number of entries used in list */
	NINT	resourceOperationCount; /* counter to compare to file level counter in order to detect need to refresh the list */
} CTRESOURCE_LIST, *pCTRESOURCE_LIST;

#ifdef ctSRVR
/* lock the resource list */
#define LOCK_CTRESOURCE_LIST(dnum,type,loc) ctRWLrqs(&(dnum)->resourceListLock,RWL(type) sOWNR SMN(loc));
/* unlock the resource list */
#define UNLOCK_CTRESOURCE_LIST(dnum,type) ctRWLclr(&(dnum)->resourceListLock,RWCA(type,sOWNR));
#else
#define LOCK_CTRESOURCE_LIST(dnum,type,loc)
#define UNLOCK_CTRESOURCE_LIST(dnum,type)
#endif

typedef enum scan_direction {
	SCAN_FORWARD = 1, /* scanning forward in file */
	SCAN_BACKWARD = 2  /* scanning backward in file */
} SCAN_DIRECTION;

typedef struct wfils {	/* File Control Structure 		*/
#ifdef ctFLEXFILE
	struct wfils ctMEM
	       *lstlnk;	/* CTFILE link for getlst ONLY		*/
#else
	struct wfils ctMEM
	       *nxtfcb;	/* CTFILE link				*/
#endif
#ifndef ct8P
	LONG	align8;	/* ensure 8-byte alignment for phyrec1	*/
#endif
	ctRECPT	phyrec1;/* last byte offset of file		*/
	ctRECPT	delstk1;/* top of delete stack: fixed len data	*/
	ctRECPT	numrec1;/* last byte offset written		*/
	LONG	reshdr1;/* resource header			*/
	LONG	lstmbr1;/* last super file member/position	*/
	ctRECPT	sernum1;/* serial number			*/
	ctRECPT nument1;/* active entries			*/
	LONG    root1;	/* B-Tree root 				*/
	LONG	fileid;	/* unique file id			*/
	LONG	servid;	/* unique server id			*/
	UCOUNT	verson;	/* configuration options at create	*/
	UCOUNT	recszh;	/* node record size			*/
	UCOUNT	reclen;	/* data record length			*/
	UCOUNT	extsiz;	/* extend file (chunk) size		*/
	UCOUNT	flmode;	/* file mode (virtual, etc)		*/
	UCOUNT	logtyp; /* permanent components of file mode	*/
	UCOUNT	maxkbl;	/* maximum key bytes leaf-var		*/
	UCOUNT	maxkbn;	/* maximum key bytes non leaf-var 	*/
	TEXT	updflg;	/* update (corrupt) flag		*/
#ifdef ctFeatNOISMKEYUPD
	UTEXT	ktype;	/* file type flag			*/
#else
	TEXT	ktype;	/* file type flag			*/
#endif
	TEXT	keydup; /* duplicate flag			*/
	TEXT	deltyp; /* flag for type of idx delete		*/
	UTEXT	keypad; /* padding byte				*/
	UTEXT	flflvr;	/* file flavor				*/
	UTEXT	flalgn;	/* file alignment			*/
	UTEXT	flpntr;	/* file pointer size			*/
	UCOUNT	clstyp; /* flag for file type			*/
	COUNT   length;	/* key length 				*/
	COUNT	nmem;	/* number of members			*/
	COUNT	kmem;	/* member number			*/
	LONG	lanchr1;/* left most leaf anchor		*/
	LONG	supid;	/* super file member #			*/
	LONG	hdrpos1;/* header position			*/
	LONG	sihdr;	/* superfile header index hdr position	*/
	LONG	timeid;	/* time id#				*/
	UCOUNT	suptyp;	/* super file type 			*/
	UCOUNT	maxmrk;	/* maximum exc mark entries per leaf	*/
	UCOUNT	namlen;	/* MAX_NAME at creation			*/
	UCOUNT	xflmod; /* extended file mode info		*/
	LONG	defrel;	/* file def release mask		*/
	LONG	hghtrn;	/* tran# high water mark for idx	*/
	LONG	hdrseq1;/* wrthdr sequence #			*/
	LONG	tstamp;	/* update time stamp			*/
	LONG	camanc; /* camo anchor (4 bytes only)		*/
	LONG	xtdhdr1;/* extended header anchor		*/
	LONG	cretrn;	/* dependent transaction ID		*/

#ifdef ctHUGEFILE
	ctRECPT	phyrec2;/* last byte offset of file		*/
	ctRECPT	delstk2;/* top of delete stack: fixed len data	*/
	ctRECPT	numrec2;/* last byte offset written		*/
	LONG	reshdr2;/* resource header			*/
	LONG	lstmbr2;/* last super file member/position	*/
	ctRECPT	sernum2;/* serial number			*/
	ctRECPT nument2;/* active entries			*/
	LONG    root2;	/* B-Tree root 				*/
	LONG	seganc2;/* offset in 1st segment to segmap anchr*/
	LONG	seganc1;/* low word				*/
	LONG	lxtsiz;	/* large extent size			*/
	LONG	fxtsiz;	/* first extent size			*/
	LONG	flmode2;/* x8 only additional file mode bits	*/
	LONG	segsiz2;/* host segment size			*/
	LONG	segsiz1;/*					*/
	LONG	mxfilz2;/* max file size high word		*/
	LONG	mxfilz1;/* low word				*/
	LONG	sghdrz;	/* segment header size			*/
	LONG	lanchr2;/* left most leaf anchor		*/
	LONG	segmax;	/* maximum # of segments		*/
	LONG	hdrpos2;/* header position			*/
	LONG	x8sign; /* extended header verify signature	*/
	LONG	timeid2;
	LONG	seglst; /* # activated segments			*/
	LONG	prawno;	/* partition raw member # | host shift	*/
	LONG	flmode3;/* extended hdr file mode bits		*/
	LONG	hghtrn2;
	LONG	hdrseq2;
	LONG	tstamp2;
	ULONG	dskful;
	LONG	xtdhdr2;/* extended header anchor high word	*/
	LONG	cretrn2;/* available for extended tfil# range	*/
	UCOUNT	hsrlpos;/* offset to serial # in record (ISAM)	*/
	COUNT	hsrllen;/* length of serial number field	*/
	UCOUNT	maxpartmbr; /* max partition members		*/
	UCOUNT	schmid;	/* flexrec schema ID			*/
	LONG	prtkey;	/* relative key # for partition key	*/
	ULONG	splcnt;	/* split counter			*/
	LONG	xtdcmp;	/* extended key compression factor	*/
	LONG	idxhgt;	/* index height				*/
	LONG	dstent1;/* approx # distinct index entries LW	*/
	LONG	dstent2;/* approx # distinct index entries HW	*/
	LONG	dstsegx;/* maxNbr of partial key distinct counts*/
	LONG	dstsegn;/* number of partial key distinct counts*/
	LONG	dstsegs[ctMAXSEGdistinct];/* # of sgements	*/
	LONG	dstsegl[ctMAXSEGdistinct];/* tot len of segments*/
	LONG	dstseg1[ctMAXSEGdistinct];/* distinct count low	*/
	LONG	dstseg2[ctMAXSEGdistinct];/* distinct count high*/
	LONG	dstrsvd[8];/* rsrv space for 2 more partial keys*/
	LONG	darhdr2;/* high word DAR anchor position	*/
	LONG	darhdr1;/*  low word DAR anchor position	*/
	UTEXT	darnbr[FC_DAR_NBR];/* count of each DAR		*/
	LONG	pinstnc;/* partition member instance number	*/
	ULONG	dfrkctr;/* deferred index create counter	*/
	LONG8	pprgent8;/* partition host purged entries	*/
	LONG8	pachent8;/* partition host archived entries	*/
	LONG8	dfrkops;/* count of deferred key operations	*/
	LONG8	sfidino;/* system file ID- inode ID		*/
	ULONG	sfiddev;/* system file ID- device ID		*/
	LONG	lrsv1;	/* reserve for future LONG value	*/

#ifdef ctHDRPAD
	TEXT	rspad[ctHDRPAD];
#endif
#endif /* ctHUGEFILE */

	/*
	** end of permanent information
	*/

#ifdef ctFeatFILEupdseq
#ifdef ctFeatATOMICop
	AULONG	updseq;	/* 32-bit update sequence number.	**
			** updseq is incremented on each call	**
			** to tstupd(). it is allowed to	**
			** overflow. must be aligned: position	**
			** just after permanent info		*/
#else
	ULONG	updseq;
#endif
#endif

#ifdef ctFeatDAR
	NINT	darunq[FC_DAR_TYPES]; /* unique indicator	*/
#ifdef MULTITRD
	SEMAmut	darmtx;	/* DAR mutex: used if FC_DAR_reqmtx on	*/
#endif

	/*
	** Identity Field
	*/
	pDAR	IDfield;	/* ptr to IDfield DAR		*/
#ifdef TRANPROC
	pVOID
		dfrDARWRD;	/* defer DARwrd until OPNTRAN	*/
#endif
#ifndef MULTITRD
	UTEXT	IDfield_cur[8];	/* current ISAM IDfield value	*/
	UTEXT	IDfield_tmp[8];	/* tmp store for IDfield value	*/
	UTEXT	IDfield_clen;	/* cur indicator		*/
	UTEXT	IDfield_tlen;	/* tmp indicator		*/
#endif

	/*
	** add temporary header ptr field and associated fields
	** for new DAR right after pDAR IDfield
	**
	** ctSIBLING_DAR
	*/
#endif
#ifdef ctHUGEFILEint8
	NLONG	phyrc8;	/* last byte offset of file		*/
	NLONG	delst8;	/* top of delete stack: fixed len data	*/
	NLONG	numrc8;	/* last byte offset written		*/
	NLONG	reshd8;	/* resource header			*/
	NLONG	lstmb8;	/* last super file member/position	*/
	NLONG	sernm8;	/* serial number			*/
	NLONG	numen8;	/* active entries			*/
	NLONG	root8;	/* B-Tree root 				*/
	NLONG	lanch8;	/* left most leaf anchor		*/
	NLONG	hdrps8;	/* header position			*/
	NLONG	sihdr8;	/* superfile header index hdr position	*/ /* ???? */
	NLONG	dsten8;	/* approx # distinct index entries	*/
#endif /* ctHUGEFILEint8 */

#ifdef ctFeatDISTINCTkeysegDBG
	LONG	dstent1_bef,dstseg1_bef;
#endif


#ifdef ctFeatIopFile
#ifdef ctFeatSNAPSHOT
	LONG8	fredops;/* file specific # of read  ops		*/
	LONG8	fredbyt;/* file specific # of bytes read	*/
	LONG8	fwrtops;/* file specific # of write ops		*/
	LONG8	fwrtbyt;/* file specific # of bytes written	*/
	ULONG	mhghbyt2;/* memory file high water bytes hw	*/
	ULONG	mhghbyt1;/* memory file high water bytes lw	*/
#ifdef ctFeatDISKIOtime
	LONG8	fredtim;/* file specific disk read call time	*/
	LONG8	fwrttim;/* file specific disk write call time	*/
#endif
#else
	UNLONG	fredops;/* file specific # of read  ops		*/
	UNLONG	fredbyt;/* file specific # of bytes read	*/
	UNLONG	fwrtops;/* file specific # of write ops		*/
	UNLONG	fwrtbyt;/* file specific # of bytes written	*/
#endif
#endif

#ifdef ctFeatSrvLockFile
	UNLONG	floktry;
	UNLONG	flokhlk;
	UNLONG	flokblk;
	UNLONG	flokhbk;
	UNLONG	flokdlk;
	UNLONG	flokkil;
	UNLONG	flokdny;
	UNLONG	flokfre;
	UNLONG	flokrel;
#endif
	NINT	hdradj;	/* size of record header of var len file
			** and/or SUPERFILE members		*/
	NINT	resadj;	/* size of resource header		*/
	UCOUNT	srlpos;	/* offset to serial # in record (ISAM)	*/
	COUNT	srllen; /* length of serial number field	*/

#ifdef ctBEHAV_WRTMRK
#ifdef ctHUGEFILE
	LONG	wrtmrk2;
#endif
	LONG	wrtmrk1;
#endif

	LONG	hdroff1;/* index member header offset		*/
	LONG	nodstk1;/* temporary index delete stk ptr	*/
	LONG	botstk1;/* temporary index delete stk ptr	*/
#ifdef ctHUGEFILE
	LONG	hdroff2;/* index member header offset		*/
	LONG	nodstk2;/* temporary index delete stk ptr	*/
	LONG	botstk2;/* temporary index delete stk ptr	*/
#else
	ULONG	splcnt;	/* split counter			*/
#endif
#ifdef ctFeat6BT
	LONG	tmptrn2;
#endif
	LONG	tmptrn;	/* temporary tran# high water mark	*/
	LONG	tflmod; /* temporary file attributes		*/
	LONG	tflmod2;/* temporary file attributes2		*/
	LONG	tflmod3;/* temporary file attributes3		*/
	LONG	tflmod4;/* temporary file attributes4		*/
	LONG	tflstt; /* temporary file status: mtx controlled*/
#ifdef ctFeatMEMFILE
	ULONG	memcnt;	/* number of memory records		*/
	ULONG	hghcnt;	/* high water # of memory records	*/
#endif
#ifdef ctCAMO
	LONG	camthr; /* (4 bytes only)			*/
	LONG	camlen;
	LONG	camver;
	LONG	camblk;
	pTEXT	camptr;
#else
	LONG	unused_camthr;
	LONG	unused_camlen;
	LONG	unused_camver;
	LONG	unused_camblk;
	pTEXT	unused_camptr;
#endif
#ifdef ctXTDKEYSEG
	NINT	unchnd;	 /* file-wide handle			*/
	pNINT	uncseg;	 /* ptr to array of kseg handles	*/
#endif
#ifdef ctNogloTran
	pIDXLST	ixlist; /* vulnerable node list head ptr	*/
#ifdef ctHUGEFILE
	LONG	cresav;	/* savepoint at time of creation	*/
	LONG	lstent2;
#endif
	LONG	lstent1;/* nument at last clean point		*/
	ULONG	loghnd;	/* unique id entered into tran log	*/
	ULONG	tmphnd;	/* unique id entered into tran log	*/
#ifdef ctFeatRECOVERY_CHECK_DUPFID
	ULONG	rcvhnd;	/* unique id to avoid dup in recovery	*/
#endif
	LONG	dellog;	/* delete file high water mark log#	*/
	LONG	delpos;	/*   "     "    "     "    "   position	*/
	LONG	opnlog;	/*   open file high water mark log#	*/
	LONG	opnpos;	/*   "     "    "     "    "   position	*/
	COUNT	omitcp;	/* omit from checkpoint (flag)		*/
	COUNT	resrv1;
#endif
#if defined(ctFeatUSRBLKTIMOUT) || defined(ctFeatFPGloktimout)
	LONG	timout;	/* > 0 is timeout in seconds		*/
#endif
#if defined(ctSS) || defined(ctFeatLOCKfile)
	LONG	wlkcnt;	/* write lock count			*/
#endif
#ifdef ctFeatLOCKfile
	LONG	rlkcnt;	/* read lock count			*/
	LONG	rltcnt; /* current # of table read locks held	*/
	LONG	wltusr; /* task ID that owns table write lock	*/
	LONG	rltwat; /* # of table read lock waiters		*/
	LONG	wltwat; /* # of table write lock waiters	*/
	pRECLOK	itlok;	/* intent and table lock list		*/
	pLOKORD	lokorh; /* lock request order head		*/
	pLOKORD	lokort; /* lock request order tail		*/
	pBLULST twblkt;	/* table write lock wait list tail	*/
	pBLULST trblkt;	/* table read lock wait list tail	*/
#endif
#ifdef ctSSrel2
	LONG	redlzr;	/* user who can stay read serializer	*/
#endif
#ifdef ctFeatSPLCACHE
	ULONG	datlmt;	/* max number of special cache pages	*/
	ULONG	datspl;	/* actual number of special cache pages	*/
#endif
#ifdef ctPARTITIONidxent
	/*
	** these only are defined for the system FCB since we
	** restrict only one thread to perform reorganization
	** and physical opening of member partitions
	*/
	LONG8	nentpprg8;/* PTADMIN delta pprgent		*/
	LONG8	nentpach8;/* PTADMIN delta pachent		*/
#endif
#ifndef MULTITRD
	LONG   	retnod1;/* current node				*/
	LONG	nent;	/* incremental chg to nument		*/
#if defined(ctFeatDISTINCTkey) && defined(TRANPROC)
	LONG	ndst;	/* within tran distinct delete count	*/
#ifdef ctFeatDISTINCTkeyseg
	LONG	ndstseg[ctMAXSEGdistinct]; /* partial key counts*/
#endif
#endif
	LONG	curp1;	/* current byte position		*/
	LONG	curt1;	/* temporary byte position		*/
	ULONG	curtf;	/* temporary file mode			*/
	LONG	curr1;	/* current resource position		*/
#ifdef ctPARTITION
	LONG	curpt;	/* current ISAM partition		*/
	LONG	curtt;	/* temporary ISAM partition		*/
#endif
#ifdef ctPARTITIONidxent
	LONG	nentiprg;/* individual  pprgent			*/
#endif
#ifdef ctFeatDFRIDX
	LONG	ndfrkops;/* incremental chg to dfrkops		*/
#endif
#ifdef ctHUGEFILE
	LONG   	retnod2;/* current node				*/
	LONG	curp2;	/* current byte position		*/
	LONG	curt2;	/* temporary byte position		*/
	LONG	curr2;	/* current resource position		*/
#endif /* ctHUGEFILE */
	pTEXT   keyp;	/* current key value ptr		*/
	pTEXT   keyt;	/* temporary key value ptr		*/
	pTEXT   keyl;	/* low level key result			*/
#ifdef CTS_ISAM
	pctICON	concur;	/* current context			*/
	pVOID	prange;	/* index range query			*/
#endif
#ifdef ctFeatFULLTEXTIDX
	pVOID	pfultxt; /* full text search handle		*/
#endif
#ifdef ctFLEXFILE
	struct wfils ctMEM
	       *hmem;	/* host member ptr			*/
	struct wfils ctMEM
	       *xmem;	/* next member ptr			*/
#endif
#else /* MULTITRD */
#ifdef ctBEHAV_FCBSTK
	struct wfils ctMEM
	       *fcbstk;	/* available fcb stack link		*/
#ifdef ctFeatKEEPOPENclose
	struct wfils ctMEM
	       *kepopnN;/* KEEPEOPEN list Next link		*/
	struct wfils ctMEM
	       *kepopnP;/* KEEPEOPEN list Previous link		*/
	NINT	kepopnI;/* number FCB's in ISAM set		*/
	NINT	kepopnL;/* sublist #				*/
#endif
#endif
	SEMA	semaf;	/* permanent info semaphore		*/
	SEMAmut	thdrf;	/* temporary info semaphore		*/
#ifdef ctFeatDFRIDXsrvr
	ctRWLOCK
		dfrkf;	/* file-level deferred index state lock	*/
#endif
#ifdef ctFeatFLSHSAVErwl
	ctRWLOCK
		rwlfls;	/* reader/writer lock for file flush	*/
#endif
#ifdef ctSYSQUEsrvr
	pNOTIFY	pnotify;/* notify list anchor			*/
	NINT	notism;	/* count of current ISMUPD notifiers	*/
	NINT	nottch;	/* count of current TOUCH  notifiers	*/
#endif
#ifdef ctFeatCHANNELS
#ifdef ctALGNCHNL
	ppCHNSTRC
		chnary;	/* aligned array of channel struct	*/
	pTEXT	chnbas;	/* base address				*/
#else
	SEMA	xiosema[2 * NUMCHANEL];
	pSEMA	iosema;
#endif
#else
	SEMA	iosema[2 * NUMCHANEL];
			/* file i/o semaphore			*/
#endif
#if defined(ctFeatMEMFILE) && defined(ctFeatRWLOCK)
	RWLOCKmut memrwlok;
#endif
#ifdef ctBEHAV_DYNDUMP_PROTECT_NODESPLIT
	ctRWLOCK dumpRWL;
#endif
	pRUSLST	ruslst;	/* time stamped node re-use list	*/
#ifdef ctBEHAV_BLM
	struct datbuf ctMEM
		*datlst;	/* list of  cache pages		*/
	LONG	datcnt;		/* number of data cache pages	*/
#ifdef ctFeatFILEupdpag
	AULONG	updcnt;		/* count of updated pages	*/
#endif
#ifdef ctMXLOGS
	NINT	trnlst;		/* multiple log channel		*/
	NINT	ablset;		/* prior log channel: resetabtnod */
#endif
#endif
#ifdef ctDYNHASH
	HSHSTT	rlokstt;
	RLOKHSH
	       *rlok; 	/* hash bin ptrs for record locks	*/
#else
	struct reclok ctMEM
	      **rlokh;	/* head of record locks			*/
	struct reclok ctMEM
	      **rlokt;	/* tail of record locks			*/
#endif
	struct wfils ctMEM
	       *hmem;	/* host member ptr			*/
	struct wfils ctMEM
	       *xmem;	/* next member ptr			*/
#ifdef DBGhash
	pLONG	dbg_lhsh_f;
#endif
#ifdef ctFeatFILEBLOCK
	pTEXT	altlist;
#endif
/* #ifdef ctBEHAV_MEMSUB_SPCLST */
	pLSTANC	spclst;
/* #endif */
#ifdef ctHUGEFILE
	pTEXT	oflname;/* orig filname during pending delete	*/
	NINT	ofluser;/* user initiating pending delete	*/
#endif
#ifdef ctPARTITION
	NINT	numopnhst;	/* # of partition opens through host	*/
#endif
	NINT	numopnism;	/* # of ISAM level opens	*/
#endif /* MULTITRD */

#ifdef ctFeatMEMFILE
	MHL	mhlhdr;	/* MHL anchor info			*/
#endif
#ifdef ctBEHAV_DumpProtect
	NINT	updnum;	/* # of updaters on file during prot dmp*/
#endif
	LONG	typflt;	/* filter type				*/
#ifdef ctBEHAV_CHKHSTLNK
#ifdef ctHUGEFILE
	LONG	lstext2;/* SUPERFILE offset of last LOGEXTFIL in log */
#endif
	LONG	lstext1;/* SUPERFILE offset of last LOGEXTFIL in log */
	LONG	lenext;	/* last LOGEXTFIL trclen		     */
#endif
#ifndef MULTITRD
#ifdef  ctFeatDATFLT
	LONG	dttflt;	/* type of data filter			*/
	pVOID	datflt;	/* pointer to data filter		*/
#endif
#endif
#ifdef  ctFeatDATFLTsecurity
	LONG	rctflt;	/* type of read security filter		*/
	pVOID	recflt;	/* pointer to read security filter	*/
	LONG	wctflt;	/* type of write security filter	*/
	pVOID	wecflt;	/* pointer to write security filter	*/
#endif
#ifdef ctBEHAV_BLM
	struct trebuf ctMEM
		*buflst;	/* list of buffer pages		*/
	LONG	bufcnt;		/* number of buffer pages	*/
#ifdef ctFeatFILEupdbuf
	AULONG	updidxbuf;	/* count of updated index buffers */
#endif
#endif
	struct wfils ctMEM
	       *psuper;	/* ptr to super file control struct	*/
	struct wfils ctMEM
	       *puse;	/* prev link for use list		*/
	struct wfils ctMEM
	       *nuse;	/* next link for use list		*/
	pVOID	idxflt;	/* pointer to index filter		*/
#ifdef ctFeatABLISThash
	pABTLST ablist[NUMABL]; /* node abort list pointers	*/
	pABTLST abtrnlst[NUMABL]; /* node abort list by tran	*/
#else
	pABTLST ablist; /* node abort list pointer		*/
#endif
	pCOUNT  altseq;	/* alternative sequence			*/
	pConvMap schema;/* record schema Map			*/
#ifdef ctMIRROR
	pTEXT	mflname;/* pointer to mirror file name		*/
	RNDFILE	mfd;
	NINT	mstatus;/* mirror status			*/
#else
#ifdef ctLOCLIB
	pTEXT	mflname;
	RNDFILE	mfd;
	NINT	mstatus;
#endif
#endif /* ctMIRROR */

#ifdef MULTITRD
#ifdef ctFeatCHANNELS
#ifndef ctALGNCHNL
	RNDFILE	xafd[2 * NUMCHANEL];
	pRNDFILE afd;
#endif
#else
	RNDFILE	afd[2 * NUMCHANEL];
			/* file descriptor			*/
#endif
#ifdef ctNogloTran
	NINT	dmpflg; /* track clean dyn dump for non-ctTRNLOG	*/
			/* during recovery, show clean ctTRNLOG	*/
#endif
#ifdef ctALGNCHNL
	NINT	alcchn;	/* number of channels allocated		*/
#endif
	NINT	numchn;	/* number of channels			*/
	UINT	toggle; /* multi channel toggle			*/
#ifdef ctHUGEFILEsegm
	NINT	segupd;	/* seg definition update flag (iosema)	*/
	NINT	seglop;	/* seg definition loop indicator	*/
#endif
#else  /* ~MULTITRD */
	RNDFILE	ctfd;	/* file descriptor			*/
	NINT	retelm;	/* current node element			*/
#ifdef ctNogloTran
	NINT	dmpflg;
#endif
#endif /* ~MULTITRD */
	struct wfils ctMEM
	       *rcnum;	/* ptr to data file with RECBYT index	*/
	struct wfils ctMEM
	       *unqnum;	/* ptr to replication-capable unique key*/
	struct wfils ctMEM
	       *rvnum;	/* ptr to ISAM associated data file	*/
	LONG	hrlkey;	/* relative key # of rep unique key	*/
#ifdef ctPARTITION
	pNINT	 ptmap;	/* segment map from KINCprt key value
			** to KORDprt key value			*/
	struct wfils ctMEM
	        *phost;	/* ptr to host data file		*/
	pPARTMBR ptmbr;	/* partition member files		*/
#ifdef ctFeatPARTSERbuf
	pPARTSER ptser;	/* member search buffer			*/
#endif
	pVOID	 ptrul;	/* ptr to parsed partition rule	CTPRULE */
	NINT	 ptcur;	/* ctdallc current index		*/
	NINT	 pttot;	/* ctdallc total available		*/
	NINT	 ptlow;	/* current low raw partition number	*/
#ifndef MULTITRD
	NINT	 ptlst;	/* last partition in key search		*/
#endif
#ifdef ctFeatPARTSERbuf
#ifndef MULTITRD
	NINT	 ptkeyno; /* user filno of last partition in key search */
#endif
#endif
#ifdef MULTITRD
	NINT	 ptcre; /* Thrd ID for current crethrd call	*/
	NINT	 ptref; /* Partition create reference count	*/
#endif
#ifdef ctFeatPARTSERrawno
	NINT	 ptfraw;/* first active raw partition number	*/
	NINT	 ptlraw;/*  last active raw partition number	*/
#endif
#ifdef ctFeatPARTREPL
	LONG	 phosti;/* index into checkpoint partition host list */
#endif
#endif
#ifdef ctFeatDELSTK_COMMIT_SEC
	LONG8	dsctim;	/* delete stack commit timestamp */
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
	pCMPRECRES
		cmprec_res;	/* compression resource		*/
	pCMPRECFNC
		cmprec_fnc;	/* function ptrs/DLL support	*/
#ifndef MULTITRD
	pVOID	cmprec_cmp;	/*   compression context	*/
	pVOID	cmprec_exp;	/* decompression context	*/
#endif
#ifdef TRANPROC
	ULONG	cmprec_hnd;	/* unique (temp) compression	**
				** resource handle		*/
#endif
#endif
#ifdef ctFeatDFRIDX
	pDFRKRES
		dfridx_res;	/* deferred indexing resource	*/
	pDFRKFNC
		dfridx_fnc;	/* function ptrs/DLL support	*/
	LONG	numpndidx;	/* count of pending indices	*/
   struct iidx *ppndidx;	/* pending index definitions	*/
	pLONG	ppndkeynos;	/* pending index system filnos	*/
#ifdef ctFeatPNDIDXsrvr
	LONG8	curlodbyt;	/* offset of last record processed by
				** background index load thread	*/
#endif
#endif
#ifdef ctFeatRUCB
	pRUCBLST
		rucb_lst;	/* record update callback list  */
	LONG	numrucb;	/* count of record update callbacks */
#ifndef MULTITRD
	ppVOID	rucbstate;	/* Record update callback function: per-
				** user per callback state pointer	*/
#endif
#endif
#ifdef ctFeatFLEXREC
	ppRCDSC	rcnv_lst;	/* record converter list */
	LONG	numrcnv;	/* count of record converters */
#endif
#ifdef ctHUGEFILEsegm
	pRNDFILE sgfd;	/* segmented file descriptors 		*/
	ppTEXT	sgfn;	/* segmented file names			*/
	pLONG	sghz;	/* segmented file size limit: hw	*/
	pLONG	sglz;	/* segmented file size limit: lw	*/
	pLONG	sgcn;	/* segmented file cretrn		*/
#ifdef ctBEHAV_CHKSAVE
	pUINT	sgskipsave;
			/* segmented file skip ctsave flg	*/
#endif
	LONG	sgslst;	/* shadow seglst value for undos	*/
	LONG	sgpaghw;/* last page that fits in last seg hw	*/
	LONG	sgpaglw;/* last page that fits in last seg lw	*/
#endif
	UINT	recsiz;	/* recszh converted to proper UINT val	*/
	UINT	hshshf;	/* hash shift factor			*/
#ifdef ctDISKFULL
	NINT	dskvol;	/* findvol result indicator		*/
#endif
#ifdef ctFeatOPNCNTatomic
	AULONG	opncnt;	/* track file opens (e.g., see iCTFLUSH)*/
#else
	UINT	opncnt;	/* track file opens (e.g., see iCTFLUSH)*/
#endif
#ifdef ctFeatDISTINCTkey
	UINT	cointoss; /* randomizing element on 1st in node	*/
	UINT	dnctflg;  /* status of in-process ctDISTINCTset	*/
#endif
	UCOUNT	schlen;	/* Map length				*/
	COUNT	usrcnt;	/* number of users with file open	*/
#ifdef ctFeatXTDUSRCNT
	NINT	actusrcnt; /* user count w/o KEEPOPEN		*/
	NINT	thdusrcnt; /* distinct thread count w/o KEEPOPEN*/
#ifdef ctFeatCOFILE_FILELOCK
	NINT	sysmodlev; /* system FCB file mode level	*/
	NINT	modusrcnt[ctFileModeLevels];
			/* distinct thd count of file mode opens*/
#endif
#endif
	SYSNO	filnum;	/* file number assigned by user		*/
	UCOUNT	rcvcre;	/* recovery create flag			*/
	UCOUNT	rcvwrt;	/* recovery update flag			*/
#ifdef MULTITRD
#ifdef ctFeatDISTINCTkey
	NINT	dncthrd;  /* ctDISTINCTset update thread ID	*/
#endif
#else
	UCOUNT	fupd;	/* per transaction update flag		*/
	UCOUNT	plen;	/* keyp length flag			*/
	UCOUNT	tlen;	/* keyt length flag			*/
#endif
#ifdef ctFeatNOBUFFERING
	UCOUNT	dscsiz;	/* disk sector size for this file	*/
#endif
#ifdef ctFeatSHAREstate
	COUNT	blkwrt;	/* count of opens that block write access */
	COUNT	totwrt;	/* total opens of file with write access  */
#endif
#ifdef ctFeatREPLICAT_SYNC_SRVR
	ULONG	sraCount; /* number of sync replication agents for this file */
	pULONG	sraList; /* handles to sync replication agents for this file */
	RWLOCKmut
		sraRwl; /* reader/writer lock for sync repl file state vars */
#endif
#if defined(FPUTFGET) || defined(ctLOCLIB) || defined(ctPortREALIA)
	UCOUNT	savprm;	/* save virtual/permanent info		*/
	NINT	lokcnt;
	NINT	tstmbr;
	ctFUID	uniqid;
#endif /* FPUTFGET || ctLOCLIB || ctPortREALIA */
#if defined(ctFeatFPGloktimout) && defined(ctPortWIN32)
	HANDLE	hAsyncIOEvent;
#endif
	TEXT	autodup;
	TEXT	distinct;
	TEXT	chnacs;	/* 'y' 'n' 'v'				*/
	TEXT	flname[MAX_NAME];	/* file name		*/
#ifdef  CTFILE_HAS_UsrData
	pVOID	UsrData;
#endif
#ifdef ctFeatAUTOSYSTIME
	pA_STFIELDS autoST_def;
	LONG *autoST_dodoff; 
	UINT *autoST_dodtyp;
	UINT *autoST_dodlen;
#ifdef MULTITRD
	SEMAmut	autoST_mtx;
#endif
#endif
	CTRESOURCE_LIST	resourceList; /* resource list for file */
	LONG	resourceOperationCount; /* current count of resource add, delete, update for this file */
#ifdef ctSRVR
	RWLOCKmut
		resourceListLock; /* reader/writer lock	for resource list */
#endif
#ifdef ctFeatKEEPOPENoffAtLogoff
	NINT	keepopenOffTaskId; /* task id of the connection that will turn off KEEPOPEN for this file when it disconnects */
#endif

} CTFILE;
typedef CTFILE ctMEM *	pCTFILE;
typedef CTFILE ctMEM * ctMEM * ppCTFILE;
#define ctkey(filno)	ctfcbhdr[(filno)]
#define	DATFILE		CTFILE
#ifdef ctPortSTR
#define	ctKEYFILE	CTFILE
#else
#define	KEYFILE		CTFILE
#endif
#define	VATFILE		CTFILE

/*
** offset (bytes) of member of file header structure
*/
#define ctHdrOff(member)	(SegOff(CTFILE,member) - SegOff(CTFILE,phyrec1))
#define ctHdrOffArray(member)	(ArraySegOff(CTFILE,member) - SegOff(CTFILE,phyrec1))

#ifdef ctDYNHASH
#define	rlokh(bin)	rlok[bin].h
#define	rlokt(bin)	rlok[bin].t
#else
#define	rlokh(bin)	rlokh[bin]
#define	rlokt(bin)	rlokt[bin]
#endif

/*
** GENBUF structure specifies the common beginning to the DATBUF and
** TREEBUFF (pTREBUF)  structures.
*/

typedef struct genbuf {
	struct
	genbuf ctMEM
		*nxtbuf;
	pTEXT	 genorg;
#ifdef ctBEHAV_BLM
	struct genbuf ctMEM
	       *updprv;
	struct genbuf ctMEM
	       *updnxt;
	struct genbuf ctMEM
	       *comprv;
	struct genbuf ctMEM
	       *comnxt;
	struct genbuf ctMEM
	       *filprv;
	struct genbuf ctMEM
	       *filnxt;
	struct wfils  ctMEM
	       *flnum;
	NINT	trnlst;
#ifdef ctBEHAV_CHKBUFUPD
	NINT	cmtchk;		/* count of commit checks with NULL updprv */
#endif
#endif
	NINT	fileno;
	LONG	pos1;
#ifdef ctHUGEFILE
	LONG	pos2;
#endif
	BHL	hashlist;
#if defined(ctFeatNoDatPndgList) || defined(ctFeatNoIdxPndgList)
	ULONG	status;
#ifdef ctDBGfcqa
	NINT	sttthd;
	NINT	sttloc;
	NINT	prvstt;
	NINT	prvloc;
	NINT	prvthd;
#endif
#endif
} GENBUF;
typedef GENBUF ctMEM *	pGENBUF;

typedef struct datbuf {
	struct
	datbuf ctMEM
		*nxtbuf;
	pTEXT	 datorg;
#ifdef ctBEHAV_BLM
	struct datbuf ctMEM
	       *updprv;
	struct datbuf ctMEM
	       *updnxt;
	struct datbuf ctMEM
	       *comprv;
	struct datbuf ctMEM
	       *comnxt;
	struct datbuf ctMEM
	       *filprv;
	struct datbuf ctMEM
	       *filnxt;
	struct wfils  ctMEM
	       *flnum;
	NINT	trnlst;
#ifdef ctBEHAV_CHKBUFUPD
	NINT	cmtchk;		/* count of commit checks with NULL updprv */
#endif
#endif
	NINT	 datfil;
	LONG	 datpos1;
#ifdef ctHUGEFILE
	LONG	 datpos2;
#endif
	BHL	 bhlDU;
#ifdef ctFeatNoDatPndgList
	ULONG	 cacstt;	/* cache status word */
#ifdef ctDBGfcqa
	NINT	 sttthd;
	NINT	 sttloc;
	NINT	 prvstt;
	NINT	 prvloc;
	NINT	 prvthd;
#endif
#endif
#ifdef ctFeatBACKGROUNDflush
	LONG8	 updtim;	/* time of first update to cache page */
#endif
	NINT	 datatr;		/* attribute word	*/
#ifdef MULTITRD
#ifndef ctFeatNoDatPndgList
	NINT	 datown;
	NINT	 datavl;	/* detect avail cache page reused too soon */
	NINT	 datpfn;
	LONG	 datpps1;
#ifdef ctHUGEFILE
	LONG	 datpps2;
#endif
	BHL	 bhlDP;
#endif

	SEMA	 datsem;
#endif
#ifdef TRANPROC
	LONG	 trstmp;
	LONG	 cpstmp;
	pCOMLST	 datcom;
#endif
#ifdef ctFeatNoDatPndgList
#ifdef ctFeatSCANCACHE
	struct datbuf ctMEM
	        *scnlnk;
#endif
#else
	BHL	 bhlDA;
#endif
#ifdef ctFeatDALISTnum
	LONG	 bhlDAnum; /* data cache LRU list number for page */
#endif
#ifdef ctFeatRECBKT
	BHL	 bhlDB;		/* record bucket hash list link		*/
	NINT	 bktOWNR;	/* task id of record bucket updater	*/
#endif
	pCTFILE	 datnm;
#ifdef CTSUPERDEL
#ifdef MULTITRD
	pCTFILE	 datpnm;
#endif
#endif
#ifdef ctFeatLOGFLUSH_MOD
	ULONG	 datmog[2];	/* required log flush high point	*/
#endif
	VRLEN	 dathgh;
	NINT	 datupd;
} DATBUF;
typedef DATBUF ctMEM *	pDATBUF;
typedef pDATBUF ctMEM *	ppDATBUF;

typedef struct rplist {
	ULONG	rp_log;		/* log number			*/
	ULONG	rp_pos;		/* offset to RP in log		*/
	ULONG	rp_tim;		/* RP time stamp		*/
	ULONG	rp_tim2;	/* room for 64-bit time		*/
	LONG	rp_chklog;	/* CP log assoc w/ RP		*/
	ULONG	rp_chkpos;	/* CP pos assoc w/ RP		*/
				/* skplog/skppos only filled-in	**
				** if RP used as rcv terminus	*/
	ULONG	rp_skplog;	/* auto rcv skip mark log	*/
	ULONG	rp_skppos;	/* auto rcv skip mark pos	*/
	ULONG	rp_rcvlog;	/* oldest rcv log assoc w/ RP	*/
	UCOUNT	rp_versn;	/* structure version		*/
	UCOUNT	rp_type;	/* lightweigt or checkpoint	*/
	LONG8	rp_srn;		/* serial number		*/
} RPLIST, * pRPLIST;

#define ctRP_VERSION	2	/* RPLIST version: 20140707	*/
#define ctRP_LW		2	/* lightweight RP		*/
#define ctRP_CP		3	/* checkpoint  RP		*/

#define ctRP_offVERSION	0	/* 4 bytes, but only 2 in RPLIST*/
#define ctRP_offCHKLOG	4	/* checkpoint			*/
#define ctRP_offCHKPOS	8
#define ctRP_offRCVLOG	12	/* checkpoint's oldest rcv log	*/
#define ctRP_offSKPLOG	16	/* skip forward log & position	*/
#define ctRP_offSKPPOS	20
#define ctRP_offAVAIL1	24	/* available for future use	*/
#define ctRP_offAVAIL2	28
#define ctRP_offSRN	32	/* 8 byte serial number		*/


#ifdef ctFeatNoDatPndgList
typedef struct crawl {
	ppDATBUF
		pag;		/* ptr to list of pages		*/
	ULONG	pos;		/* position within list		*/
	ULONG	tot;		/* size of list			*/
	LONG	cnt;		/* equivalent to bhlcnt		*/
	} CRAWL, * pCRAWL, ** ppCRAWL;
#endif

#ifdef ctFeatDatEmptyList
typedef struct empdat {
	LONG	BegEmp;	/* beg position in empty list		*/
	LONG	EndEmp;	/* end position in empty list		*/
	LONG	CntEmp;	/* empty list count			*/
	ppDATBUF
		LstEmp;	/* empty list				*/
	SEMAmut	MtxEmp;
	} EMPDAT, * pEMPDAT, ** ppEMPDAT;
#endif

#ifdef MULTITRD

typedef struct fusr {
#ifdef ctBEHAV_ULCNT
	LONG	lcnt;	 /* lock balance counter	*/
#endif
	LONG	pmsk;	 /* permission mask		*/
	LONG	nent;	 /* incremental nument chg	*/
#ifdef ctBEHAV_IICTflexSTT
	LONG	nent2;	 /* incremental nument chg - outer tran	*/
#endif
#if defined(ctFeatDISTINCTkey) && defined(TRANPROC)
	LONG	ndst;	 /* within tran distinct delete count	*/
#ifdef ctFeatDISTINCTkeyseg
	LONG	ndstseg[ctMAXSEGdistinct]; /* partial key counts*/
#endif
#ifdef ctBEHAV_IICTflexSTT
	LONG	ndst2;	 /* within tran distinct delete count - outer tran */
#ifdef ctFeatDISTINCTkeyseg
	LONG	ndstseg2[ctMAXSEGdistinct]; /* partial key counts - outer tran */
#endif
#endif
#endif
	LONG	curp1;	 /* current byte position	*/
	LONG	curt1;	 /* temporary byte position	*/
	ULONG	curtf;	 /* temporary file mode		*/
	LONG	curr1;	 /* current resource position	*/
	LONG	retnod1; /* current node position	*/
#ifdef ctPARTITION
	LONG	curpt;	 /* current ISAM partition	*/
	LONG	curtt;	 /* temporary ISAM partition	*/
#endif
#ifdef ctPARTITIONidxent
	LONG	nentiprg;/* individual  pprgent		*/
#ifdef ctBEHAV_IICTflexSTT
	LONG	nentiprg2;/* individual  pprgent - outer tran */
#endif
#endif
#ifdef ctFeatDFRIDX
	LONG	ndfrkops;/* incremental chg to dfrkops	*/
#ifdef ctBEHAV_IICTflexSTT
	LONG	ndfrkops2;/* incremental chg to dfrkops	- outer tran */
#endif
#ifdef ctFeatDFRIDXsrvr
	ULONG	dfrkctr;  /* data file's deferred index create counter */
	NINT	pndidxlnk;/* data file's pending deferred index list */
#ifdef ctFeatPNDIDXsrvr
	NINT	pndridxlnk;/* data file's pending regular index list */
#endif
	LONG	numpndidx;/* count of pending indices	*/
   struct iidx *ppndidx;  /* pending index definitions	*/
	FILNO	*ppndkeynos; /* user filnos for pending indices */
#endif
#endif
#ifdef ctFeatRUCB
	ppVOID	rucbstate;	/* Record update callback function: per-
				** user per callback state pointer	*/
	NINT	numrucb;	/* Number of RUCB state pointers	*/
#endif
#ifdef ctHUGEFILE
	LONG	curp2;	 /* current byte position	*/
	LONG	curt2;	 /* temporary byte position	*/
	LONG	curr2;	 /* current resource position	*/
	LONG	retnod2; /* current node position	*/
#endif
#ifdef ctFeatUSRBLKTIMOUT
	LONG	timout;	 /* > 0 is timeout in seconds	*/
#endif
#if defined(ctSS) || defined(ctFeatLOCKfile)
	LONG	wlkcnt;	 /* write lock count		*/
#endif
#ifdef ctFeatLOCKfile
	LONG	rlkcnt;	/* read lock count		*/
	LONG	tlkstt;	/* table lock state		*/
#ifdef TRANPROC
	ULONG	tlkseq;	/* table lock tran sequence #	*/
#endif
#endif
#ifdef ctMULTIOPN
	ULONG	fseq;	/* sequence# to find last usage	*/
#endif
#ifdef ctFeatDATFLT
#ifdef ctFeatDATFLTmulti
	pctDTFLT datflthed[ctDATFLT_MAX_INDEX];
			 /* data filter list heads	*/
#else
	LONG	dttflt;	 /* type of data filter		*/
	pVOID	datflt;	 /* pointer to filter		*/
#endif
#endif
#ifdef ctFeatSCANCACHE
	pDATBUF	fdb;	 /* pointer to scanner cache	*/
#endif
	pTEXT   keyp;	 /* current key value ptr	*/
	pTEXT   keyt;	 /* temporary key value ptr	*/
	pTEXT   keyl;	 /* low level key result	*/
#ifdef CTS_ISAM
	pctICON	concur;	 /* current context		*/
	pVOID	prange;	 /* index range query		*/
#endif
#ifdef ctFeatFULLTEXTIDX
	pVOID	pfultxt; /* full text search handle	*/
#endif
#if defined(ctCMPREC) || defined(ctSRVR) && defined(ctPortMTREEPRO_CMPREC_DEPRICATED)
	pVOID	cmprec_cmp;	/*   compression context*/
	pVOID	cmprec_exp;	/* decompression context*/
#endif
#ifdef ctXTDKEYSEG
	pNINT	uncseg;	 /* ptr to array of kseg handles*/
	NINT	unchnd;	 /* file-wide kseg handle	*/
#endif
	NINT	retelm;	 /* current element within node */
#ifdef ctPARTITION
	struct fusr ctMEM
	       *phost;	 /* CTFILE link for getlst ONLY	*/
#ifdef ctFeatPARTSERbuf
	pPARTSER
		ptser;	 /* member search buffer	*/
#endif
	pNINT	ptmbr;	 /* user partition host array	*/
#ifdef ctFeatDYNPARTMBR
	ppTEXT	ptdynmbrnam; /* user partition dynamic member name list */
#endif
	NINT	ptlow;
	NINT	ptcur;
	NINT	pttot;
	NINT	ptlst;	/* last partition in key search	*/
#ifdef ctFeatPARTSERbuf
	NINT	 ptkeyno; /* user filno of last partition in key search */
#endif
#endif
#ifdef ctFeatFILEBLOCK
	NINT	fblku;	 /* file block map		*/
	NINT	flrvmp;	 /* index rvmap to datno	*/
#endif
#ifdef ctBEHAV_MULTIOPN_LINK
	NINT	mltlnk;	 /* symbolic (user filno) link	*/
#endif
#ifdef ctFeatFUSRCLRoptimize
	NINT	trnlnk;	 /* list of files updated in tran (fwd link) */
	NINT	trnplnk; /* list of files updated in tran (back link) */
#ifdef ctBEHAV_IICTflexSTT
	NINT	trnlnko; /* saved trnlnk for outer tran	(fwd link) */
	NINT	trnplnko; /* saved trnlnk for outer tran (back link) */
#endif
#endif
#ifdef ctFeatRECRLOCK
	NINT	filrecr; /* net recursive locks		*/
#endif
	NINT	xtmd;	 /* extended user file mode	*/
#ifdef ctFeatCOFILE_FILELOCK
	NINT	filmodlev; /* file mode level		*/
#endif
#ifdef ctFeatTRANREPL
	FILNO	rfilno;	 /* remote file#		*/
	COUNT	runqkey; /* remote file unique key#	*/
	LONG8	rcurp;	 /* offset of current record	*/
#endif
#ifdef ctFeatREMBUFADR
	struct trebuf ctMEM
		*pretbuf;/* buffer holding current node */
#endif
#ifdef ctFeatDAR
	UTEXT	IDfield_cur[8];	/* current ISAM IDfield */
	UTEXT	IDfield_tmp[8];	/* tmp store for IDfield*/
#ifdef ctLOGAUG
			 /* user specific water-mark for
			 ** IDfield used in augmented
			 ** log entries			*/
	LONG8	IDfield_usrval;
	COUNT	IDfield_status;	/*  0	no value
				**  1	increasing value
				** -1	decreasing value*/
#endif
	UTEXT	IDfield_clen;	/* cur indicator	*/
	UTEXT	IDfield_tlen;	/* tmp indicator	*/
#endif
	SYSNO	flmp;	 /* user to internal file# map	*/
	UCOUNT	flmd;	 /* user file mode		*/
	ULONG	flmd2;	 /* user file mode #2		*/
#ifdef ctFeatREPLICAT_SYNC
	ULONG	fupdSeq; /* preimage space sequence number when fupd was set */
#endif
#ifdef ctFeatSUPHSTcofile
	FILNO	suphst;	 /* superfile host file number	*/
#endif
	TEXT	fupd;	 /* file update flag		*/
	TEXT	plen;	 /* keyp length flag		*/
	TEXT	tlen;	 /* keyt length flag		*/
#ifdef ctFeatTRANISO
	UTEXT	supd;	 /* serialization update flag	*/
#endif
#ifdef ctBEHAV_DumpProtect
	TEXT	pcnt;	 /* pflgchk reference count	*/
#endif
} FUSR;
typedef FUSR ctMEM *	pFUSR;
typedef FUSR ctMEM * ctMEM * ppFUSR;

#ifdef ctALGNCHNL
#define ctfd	chnary[0]->safd
#else
#define ctfd	afd[0]
#endif

typedef struct ctstatV {
#ifdef ctCACHE_MEMORY
	LONG	tot;	/* mem limit	*/
	LONG	sum;	/* mem usage	*/
	NINT	usi;	/* mem status	*/
	NINT	ua;	/* usr alive	*/
	NINT	ma;	/* mem alive	*/
	NINT	wa;	/* work state	*/
#ifdef ctFeatWORKcount
	NINT	wc;	/* work count	*/
#endif
#ifdef ctFeatMAXACTCONN
	NINT	wv;	/* active flag	*/
#endif
	NINT	fbp;	/* FILBLK pndg	*/
	NINT	fbs;	/* FILBLK actv	*/
	NINT	fbr;	/* FILBLK blkr	*/
#endif
	COUNT	uec;	/* uerr_cod	*/
#ifdef ctPortWINKE
	NINT	sec;	/* sysiocod	*/
#else
	COUNT	sec;	/* sysiocod	*/
#endif
	COUNT	iec;	/* isam_err	*/
	FILNO	ifl;	/* isam_fil	*/
	COUNT	cec;	/* cndxerr	*/
	COUNT	dcn;    /* deltaconn    */
	} CTSTATV;
typedef CTSTATV ctMEM *	pCTSTATV;

#else  /* ~MULTITRD */

#ifndef ctFLEXFILE
#define	xmem	nxtfcb
#endif /* ~ctFLEXFILE */
#endif /* ~MULTITRD */

typedef struct trebuf {	/* B-Tree Buffer			*/
	struct trebuf ctMEM
	       *nxtbuf;
	pTEXT   nodorg;	/* pointer to node ct_origin for I/O	*/
#ifdef ctBEHAV_BLM
	struct trebuf ctMEM
	       *updprv;
	struct trebuf ctMEM
	       *updnxt;
	struct trebuf ctMEM
	       *comprv;
	struct trebuf ctMEM
	       *comnxt;
	struct trebuf ctMEM
	       *filprv;
	struct trebuf ctMEM
	       *filnxt;
	struct wfils  ctMEM
	       *flnum;
	NINT	trnlst;
#ifdef ctBEHAV_CHKBUFUPD
	NINT	cmtchk;		/* count of commit checks with NULL updprv */
#endif
#endif
	NINT	keyid;	/* key number				*/
	LONG	nodeid1;/* node number				*/
#ifdef ctHUGEFILE
	LONG	nodeid2;
#endif
	BHL	bhlIN;
#ifdef ctFeatNoIdxPndgList
	ULONG	 bufstt;/* index buffer status word		*/
#ifdef ctDBGfcqa
	NINT	 sttthd;
	NINT	 sttloc;
	NINT	 prvstt;
	NINT	 prvloc;
	NINT	 prvthd;
#endif
#endif
#ifdef ctFeatBACKGROUNDflush
	LONG8	 updtim;/* time of first update to buffer	*/
#endif
#ifdef MULTITRD
#ifndef ctFeatNoIdxPndgList
#ifdef ctFeatGNSEMAhsh
	NINT	idxavl;	/* lrubuf collision detector		*/
	NINT	idxown;
#endif
	NINT	pkeyid; /* pending key id			*/
	LONG	pnodeid1;/* pending node id			*/
#ifdef ctHUGEFILE
	LONG	pnodeid2;
#endif
	BHL	bhlPN;
#endif /* ~ctFeatNoIdxPndgList */
#ifdef IDXrwlock
	RWLOCKmut
		idxsem;	/* buffer slim reader/writer lock	*/
#else
	SEMA	idxsem;	/* buffer semaphore			*/
#endif
	pBLULST bblkh;	/* block list header			*/
	pBLULST bblkt;	/* block list tail			*/
#endif /* MULTITRD */
#ifdef TRANPROC
#ifdef ctBEHAV_FLUSH_NODE_MARKS
	LONG	cpflsh; /* tran commit must write this node	*/
#endif
	LONG	trstmp; /* oldest update tran#			*/
	LONG	cpstmp; /* oldest update chkp#			*/
#ifdef ctFeat6BT
	LONG	hghtrn2;
#endif
	LONG	hghtrn;	/* tran# high water mark for idx	*/
#ifdef ctBEHAV_MYMARKS
	LONG	mytran;	/* all key level locks for this tran	*/
#ifdef ctFeat6BT
	LONG	mytran2;
#endif
	NINT	mymarks;/* owner of all key level locks		*/
#endif
#ifdef ctBEHAV_UPDMARKS
	NINT	skipmarks; /* marks skipped ctgetnod ctclup	*/
#endif
#ifdef ctLOG_IDX
	NINT	mrkupd;	/* vulnerable mark update flag		*/
#ifdef ctLOG_IDX_NEW
	LONG	mrkcpc;	/* vulnerable mark cpcnt		*/
	ULONG	mrkabt;	/* ablist sequence number		*/
#endif
	LONG	watlog; /* log number   high water mark		*/
	ULONG	watpos; /* log position high water mark		*/
	pCOMLST lglist; /* pending log index   list stack ptr	*/
#endif
	pCOMLST cmlist;	/* pending tran commit list stack ptr	*/
	pCOMLST ablist;	/* pending tran abort  list stack ptr	*/
#endif
	BHL	bhlAV;
#ifdef ctFeatAVLISTnum
	LONG	bhlAVnum; /* index LRU list number for page	*/
#endif
#ifdef ctFeatBLKSEMA
	LONG	bbMTXnum; /* index buffer block mtx for page	*/
#endif
	pCTFILE	keynm;
	pTEXT   mrkpos;
	pTEXT   ct_kyval;/* pointer to key values for node	*/
	SYSNO	hstid;	/* host key number			*/
	COUNT   klen;	/* key length 				*/
#ifdef ctFeatPAG64K
	UINT	nkb;	/* working nkbdsk			*/
	UINT	maxb;	/* maximum bytes per node		*/
	UINT	maxmrk;	/* maximum exc mark list entries	*/
#else
	UCOUNT  maxb;	/* maximum bytes per node		*/
	UCOUNT	maxmrk;	/* maximum exc mark list entries	*/
#endif
#ifdef ctFeat6BT
	NINT	mrksiz;	/* exceptional bytes per mark (4 or 6)	*/
#endif
#ifdef ctHUGEFILE
	NINT	hugflg;
#endif
	NINT	ktipe;	/* key type compression flags ONLY	*/
	UINT	begbyt;	/* beginning byte of cur var len key	*/
	NINT	actlen;	/* stored length of cur var len key	*/
	NINT	lstpos;	/* cur var len key pos#			*/
	NINT	cursfx;	/* cur var len key suffix count		*/
#ifdef ctFeatDISTINCTkey
	NINT	presfx;	/* preceding var len suffix count	*/
#endif
#ifdef ctFeatPRVKEY_OPT
	pTEXT	savexp1; /* varkey expansion buffer ptr		*/
	pTEXT	savexp2;
	NINT	prvpos1; /* key pos of 1st tmp varkey exp bufr	*/
	UINT	prvbyt1; /* beginning byte of cur var len key	*/
	NINT	prvlen1; /* stored length of cur var len key	*/
#ifdef ctFeatDISTINCTkey
	NINT	prvsfx1; /* store cursfx for keypos1		*/
	NINT	prvsfx2;
#endif
	NINT	prvpos2;
	UINT	prvbyt2;
	NINT	prvlen2;
#endif /* ctFeatPRVKEY_OPT */
#ifdef ctFeatADAPTIVE_SPLIT
	NINT	lstadd;	/* position of last insertion		*/
	NINT	numadd;	/* # of consecutive insertions		*/
#endif
#ifdef ctFeatVARLENnodefmt
	NINT	hghlen; /* length of data at hghpnt		*/
#endif
#ifdef ctDBGfcqa
	setactlenloc_t actlenLocation;	/* location that last set actlen */
#endif
#ifdef VARLKEYS
#ifdef ctFeatXTDCMP
#ifdef ctFeatDISTINCTkeyseg
	TEXT	xtdcmpdst[MAXLEN / 256 + 1];
#endif
#endif
#endif
#ifdef ctHUGEFILE
	TEXT	keyexp[MAXLEN + 8];
#else
	TEXT	keyexp[MAXLEN + 4]; /* var key - expansion	*/
#endif
	TEXT	update;	/* node update indicator 'y/n' 		*/
	TEXT	confg;	/* regular or duplicate ct_key leaf	*/
#if defined(iSYNC_LOG) && !defined(iSYNC_LOG_AT_OPEN)
	TEXT	syncflg;/* ctsync I/O				*/
#endif
#ifdef ctFeatVARLENnodefmt
	TEXT	nodestat; /* node status bits			*/
#endif
#ifdef ctFeatNODE_COUNTERS
	LONG8	rqstcnt;/* buffer request count			*/
	LONG8	bblkcnt;/* buffer block count			*/
	LONG8	rqsttim;/* cumulative buffer request time	*/
#endif

/* beginning of permanent node */

	LONG    sucesr1;/* right sibling 		0x00	*/
	LONG    predsr1;/*  left sibling 		0x04	*/
	UCOUNT  nkv;	/* number of key values 	0x08	*/
#ifdef ctFeatPAG64K
	UCOUNT  nkbdsk;	/* number of key bytes		0x0a	*/
#else
	UCOUNT  nkb;	/* number of key bytes		0x0a	*/
#endif
	COUNT	numexc;	/* number of exc marks		0x0c	*/
	COUNT	lowexc;	/* max-min pos of 1st mark	0x0e	*/
	TEXT	bmem;	/* member number		0x10	*/
	TEXT	leaf;	/* leaf indicator LEAF/NOLEAF	0x11	*/
#ifdef ctHUGEFILE
#ifdef ctNODEchksum
	UCOUNT	chksum;	/*				0x12	*/
#else
	TEXT	pdg1;	/*				0x12	*/
	TEXT	pdg2;	/*				0x13	*/
#endif
	LONG	sucesr2;/* right sibling (high word)	0x14	*/
	LONG	predsr2;/*  left sibling (high word)	0x18	*/
#endif /* ctHUGEFILE */
} TREEBUFF;
typedef TREEBUFF ctMEM *	pTREBUF;

/* chkremnod parameters */
typedef struct crni {
	pTREBUF	buffer;
	LONG	node1;
#ifdef ctHUGEFILE
	LONG	node2;
#endif
	NINT	filno;
} CRNI, *pCRNI;

typedef struct indxadds {
	LONG	predsr1;
	LONG	sucesr1;
#ifdef ctHUGEFILE
	LONG	predsr2;
	LONG	sucesr2;
#endif
	TEXT	keyval[MAXLEN];
} INDXADDs;
typedef INDXADDs ctMEM *	pINDXADDs;

typedef struct lok {	/* ISAM Lock Table Entry		*/
	struct lok ctMEM
	       *nxtlok;
#ifdef ctFeatRECRLOCK
	NINT	ltrecr;	/* recursive lock count			*/
#endif
	FILNO   datfnm;	/* data file number			*/
	UTEXT	ltltyp;	/* lock type				*/
#ifdef ctBEHAV_MTFPG_LOKSRL
	UCOUNT	ltisam; /* isam level lock flag			*/
#else
	UTEXT	ltisam; /* isam level lock flag			*/
#endif
	ctRECPT recnum1;/* record number			*/
#ifdef ctHUGEFILE
	ctRECPT recnum2;/* record number			*/
#endif
#ifdef ctBEHAV_MTFPG_LOKSRL
	ctRECPT precnum1;/* physical record number		*/
#ifdef ctHUGEFILE
	ctRECPT precnum2;/* physical record number		*/
#endif
#endif
#ifdef ctMTFPG_LOKCNF
	ctFUID  datuid;	/* unique data file id			*/
#endif
#ifdef TRANPROC
	ULONG	trnseq;	/* user transaction sequence number	*/
#endif
} LOKS;
typedef LOKS ctMEM *	pLOKS;
typedef LOKS ctMEM * ctMEM * ppLOKS;

#ifdef ctHUGEFILE
typedef struct vrfmt {	/* beginning of var len records */
	UCOUNT	vpadng;	/* padding for alignment	*/
	UCOUNT	recmrk;	/* record marker		*/
	VRLEN	trclen;	/* total record length		*/
	VRLEN	urclen;	/* utilized record length	*/
	/* super file and resource auxiliary info	*/
	LONG	supmbr;	/* super file member id		*/
	LONG	phylnk1;/* member sequential link	*/
	LONG	phylnk2;
} VHDR;
#else  /* ~ctHUGEFILE */
typedef struct vrfmt {	/* beginning of var len records */
	UCOUNT	vpadng;	/* padding for alignment	*/
	UCOUNT	recmrk;	/* record marker		*/
	VRLEN	trclen;	/* total record length		*/
	VRLEN	urclen;	/* utilized record length	*/
	/* super file and resource auxiliary info	*/
	LONG	supmbr;	/* super file member id		*/
	LONG	phylnk1;/* member sequential link	*/
} VHDR;
#endif /* ~ctHUGEFILE */
typedef VHDR ctMEM *	pVHDR;

typedef struct hstlst {
	struct hstlst ctMEM
		       *listlnk;
#ifdef ctHUGEFILE
	LONG		listhw;
#endif
	LONG		listtrn;
	LONG		listnum;
} HSTLST;
typedef  HSTLST ctMEM *	 pHSTLST;
typedef pHSTLST ctMEM *	ppHSTLST;

typedef struct hsthdr {
	RESHDR		cth_rhdr;	/* var rec hdr (resource also)	    */
	pHSTLST		cth_ntrnlst;	/* list of previously visited trans */ 
	pHSTLST		cth_reclst;	/* list of detail recbyts (by index)*/
	pCTFILE		ctHnum;
	pCTFILE		cth_ctnum;
	pCTFILE		cth_dnum;
	pTEXT		cth_target;	/* current target pointer	    */
	pTEXT		cth_idxval;	/* current image (ctHISTindx)	    */
	pTEXT		cth_image;	/* current image (ctHISTdata)	    */
#ifdef ctFeatHISTORY_COMBINED_IMAGE
	pTEXT		cth_expbuf;	/* buffer for DIFIMAGE expansion    */
#endif
	ppTEXT		cth_filnam;	/* file name array		    */
	ppTEXT		cth_curuid;
	ppTEXT		cth_curnnm;
	ppTEXT		cth_stpuid;
	ppTEXT		cth_stpnnm;
	pTEXT		cth_ustr;	/* user/node name target string	    */
	pVOID		rs1;
	pVOID		rs2;
	ctRECPT		cth_pos1;	/* current target position	    */
	ctRECPT		cth_imgpos1;	/* current data image position	    */
#ifdef ctHUGEFILE
	ctRECPT		cth_pos2;	/* current target position	    */
	ctRECPT		cth_imgpos2;	/* current data image position	    */
#endif /* ctHUGEFILE */
	LONG		cth_lognum;	/* current log number		    */
	ULONG		cth_logpos;	/* current log offset		    */
	ULONG		cth_ctfil;	/* current file handle		    */
	ULONG		cth_dtfil;
	LONG		cth_begnum;	/* beginning log number		    */
	ULONG		cth_begpos;	/* beginning log offset		    */
	ULONG		cth_ctfilb;	/* beginning file handle	    */
	ULONG		cth_dtfilb;
	LONG		cth_stpnum;	/* stop at log number		    */
	ULONG		cth_stppos;	/* stop at log offset		    */
	ULONG		cth_ctfils;	/* stop file handle		    */
	ULONG		cth_dtfils;
#ifdef ctFeat6BT
	LONG		cth_tranno2;
#endif
	LONG		cth_tranno;
#ifdef ctHUGEFILE
	LONG		cth_recbyt2;
	LONG		cth_chgbyt2;
#endif
	LONG		cth_recbyt1;
	LONG		cth_chgbyt1;
#ifdef ctFeat6BT
	LONG		cth_lasttran2;
#endif
	LONG		cth_lasttran;
	LONG		cth_lasttime;
	LONG		cth_oldlg;
	ULONG		cth_oldlp;
#ifdef ctHUGEFILE
	LONG		cth_nxtpos2;
#endif
	LONG		cth_nxtpos1;
	LONG		cth_imagll;	/* imag low  log		    */
	ULONG		cth_imaglp;	/* imag low  pos		    */
	LONG		cth_imaghl;	/* imag high log		    */
	ULONG		cth_imaghp;	/* imag high pos		    */
	LONG		cth_imagsl;	/* imag stop log		    */
	LONG		cth_imagsp;	/* imag stop pos		    */
	LONG		cth_loglmt;	/* limit on number of logs to scan  */
	LONG		rs4;
	VRLEN		cth_szimage;	/* size of image		    */
#ifdef ctFeatHISTORY_COMBINED_IMAGE
	VRLEN		cth_szexpbuf;	/* size of expansion buffer	    */
#endif
	VRLEN		cth_resadj;
	VRLEN		cth_varadj;
	UINT		cth_cusr2;	/* maximum users (cur)		    */
	UINT		cth_susr2;	/* maximum users (stp)		    */
	UINT		cth_cseqn;	/* user ID sequence # (cur)	    */
	UINT		cth_sseqn;	/* user ID sequence # (stp)	    */
	UINT		cth_mode;	/* permanent session attributes	    */
	NINT		cth_start;	/* NO, YES init, HYS retrieval	    */
	NINT		cth_filno;
	NINT		cth_datno;
	NINT		cth_sin;	/* NO index, YES index, HYS idx+dat */
	NINT		cth_klen;
	NINT		cth_klenwo;
	NINT		cth_sflag;	/* search flag			    */
	NINT		cth_tfildb;
	NINT		cth_imagdb;
	NINT		cth_assoc;	/* offset between rechdr and image  */
	NINT		rs5;
	NINT		rs6;
	} HSTHDR;

typedef struct savhst {
	struct savhst
		*shlnk;		/* save history link */
	HSTHDR	 shhdr;		/* save history header */
	COUNT	 shnum;		/* save history number */
	} SAVHST;
typedef SAVHST ctMEM *	pSAVHST;
typedef SAVHST ctMEM * ctMEM *	ppSAVHST;

#define ctHISTkeep	((pCTFILE) 1)
#define ctSHDLread	((pCTFILE) 2) /* cttrnmem() call for preimage swap */

#ifndef ctMEMHDR
/* define ctMEMHDR in ctcmpl.h if default causes alignment problems */
#define ctMEMHDR	ctSIZE(pctSPC)
#endif

typedef struct pi1_s {
	pctSPC	 pi1lnk;
	TEXT	 pi1[PI_UNIT];
} PI1LST;

typedef struct pi2_s {
	pctSPC	 pi2lnk;
	TEXT	 pi2[2 * PI_UNIT];
} PI2LST;

typedef struct pi4_s {
	pctSPC	 pi4lnk;
	TEXT	 pi4[4 * PI_UNIT];
} PI4LST;

typedef struct pi8_s {
	pctSPC	 pi8lnk;
	TEXT	 pi8[8 * PI_UNIT];
} PI8LST;

typedef struct piw_s {
	pctSPC	piwlnk;
	TEXT	piw[16 * PI_UNIT];
} PIwLST;

typedef struct pix_s {
	pctSPC	pixlnk;
	TEXT	pix[32 * PI_UNIT];
} PIxLST;

typedef struct piy_s {
	pctSPC	piylnk;
	TEXT	piy[64 * PI_UNIT];
} PIyLST;

typedef struct piz_s {
	pctSPC	pizlnk;
	TEXT	piz[128 * PI_UNIT];
} PIzLST;

typedef struct pia_s {
	pctSPC	pialnk;
	TEXT	pia[256 * PI_UNIT];
} PIaLST;

typedef struct pib_s {
	pctSPC	piblnk;
	TEXT	pib[512 * PI_UNIT];
} PIbLST;

#ifdef ctOldALCSET
typedef struct savset {		/* Multiple-Set Buffer		*/
	COUNT	qlen;		/* significant length		*/
	COUNT	qkey;		/* sequence keyno + 1		*/
	TEXT	qbuf[MAXLEN];	/* ct_key buffer		*/
	TEXT	qold[MAXLEN];
	} SAVSET;
typedef SAVSET ctMEM *	pSAVSET;
#else
typedef struct savset {		/* Multiple-Set Buffer		*/
	struct savset
	       *qlnk;		/* link field for hashing	*/
	COUNT	qnum;		/* save set number		*/
	COUNT	qlen;		/* significant length		*/
	FILNO	qkey;		/* sequence keyno + 1		*/
	TEXT	qbuf[MAXLEN];	/* ct_key buffer		*/
	TEXT	qold[MAXLEN];
	} SAVSET;
typedef SAVSET ctMEM *	pSAVSET;
typedef SAVSET ctMEM * ctMEM *	ppSAVSET;
#endif

/*
** extended key segment definition list and resource
*/
typedef struct keyseglst {
	ctKSEGDEF	ksegdef;	/* segment definition		*/
	pVOID		systhnd;	/* system resource handle	*/
	NINT		systlst;	/* system (vs user) list handle	*/
	NINT		scope;		/* system/application/file	*/
	NINT		closeflg;	/* close flag:	YES system close*/
					/*		HYS clone close	*/
	UINT		ksgcnt;		/* multiple use count		*/
	} KSEGLST;
typedef  KSEGLST ctMEM *  pKSEGLST;
typedef pKSEGLST ctMEM * ppKSEGLST;

typedef struct ksegres {		/* file segment resource	*/
		ULONG	restyp;
		ULONG	resnum;
		TEXT	resnam[FCRNAM_LEN];
		ctKSEGDEF
			resdef;
	} KSEGRES, * pKSEGRES;


#ifdef ctCONDIDX
typedef struct cidxhdr {	/* conditional index header	*/
	COUNT	relkey;		/* relative key number		*/
	COUNT	explen;		/* ASCII len + nul byte		*/
	LONG	exptyp;		/* 0:expr  1:callback		*/
	} CIDXHDR;
#endif

#ifdef ctFeatMAX_NAME_4K
#define DFNAM_SIZE (2 * MAX_NAME) /* size of the ddmphdr struct dfnam field */
#define DDMPHDR_SIZE 16384 /* size of the ddmphdr struct */
#else
#define DFNAM_SIZE 512 /* size of the ddmphdr struct dfnam field */
#define DDMPHDR_SIZE 2048 /* size of the ddmphdr struct */
#endif

/* total length of ddmphdr fields (excluding dxtra) */
#define DDMPHDR_FIELD_LENGTHS (128 + DFNAM_SIZE + 43 * sizeof(LONG))
/* size of the ddmphdr structure */
#define DXTRA_SIZE (DDMPHDR_SIZE - DDMPHDR_FIELD_LENGTHS)

typedef struct ddmphdr {
	TEXT	ddesc[128];   /* header */
	TEXT	dfnam[DFNAM_SIZE];   /* file name */
	LONG	dchnk;	      /* Block size */
	LONG	ddtim;	      /* timestamp of dump */
	ULONG	dsize;
	ULONG	doffs;	      
	LONG	dftyp;	      /* type of entry */
	LONG	dctim;	      /* timestamp this entry */
	LONG	dsize2;
	LONG	doffs2;
	LONG	dbyte2;
	LONG	dbyte1;
	LONG	dcntl[32];
	ULONG	dattr;		/* attribute bits */
	TEXT	dxtra[DXTRA_SIZE];
	} DDMPHDR;
typedef DDMPHDR ctMEM *	pDDMPHDR;

/* check that DDMPHDR is properly sized */
typedef char checkDumpHeaderStructSize[sizeof(DDMPHDR) == DDMPHDR_SIZE];

typedef struct logtrnlst {
	LONG	lowlog;
#ifdef ctFeat6BT
	LONG	lowtrn2;
#endif
	ULONG	lowtrn;
	} LOGTRNLST;
typedef LOGTRNLST  ctMEM *  pLOGTRNLST;

#define ctREVDELcre	1	/* transaction-dependent file create */
#define ctREVDELdel	2	/* transaction-dependent file delete */
#define ctREVDELidx	3
#define ctREVDELrdo	4
#define ctREVDELudo	5
#define ctREVDELnon	6
#define ctREVDELren	7	/* transaction-dependent file rename */
#define ctREVPREinv	16	/* invalidates a revdel list entry during **
				** ctBEHAV_TRANDEP_SCAN (pre-scan)	  */
#define ctREVPREdel	(ctREVDELdel + ctREVPREinv)
#define ctREVPREren	(ctREVDELren + ctREVPREinv)

#ifdef ctHUGEFILE
typedef struct numrechgh {
	LONG	nrh_fid[3];
	ULONG	nrh_tfil;
	LONG	nrh_rec2;
	LONG	nrh_rec1;
	NINT	nrh_taux;
	NINT	nrh_link;
	} NUMRECHGH;
typedef NUMRECHGH ctMEM * pNUMRECHGH;

typedef struct revdel {
#ifdef ctFeat6BT
	LONG	revtrn2;
#endif
	LONG	revtrn;			/* trannum		*/
	LONG	revcre;			/* cretrn		*/
	ULONG	revtfl;			/* tranfil		*/
	LONG	revfid[3];		/* fid			*/
	LONG	revhps[2];		/* header position	*/
	NINT	revops;			/* type of entry	*/
	NINT	revcmt;			/* redo / undo / none	*/
	TEXT	revtmp[MAX_NAME];	/* orignal name		*/
	TEXT	revorg[MAX_NAME];	/* copy (re)name	*/
	} REVDEL;
typedef REVDEL ctMEM * pREVDEL;
#endif

typedef struct dedlst {
	pVOID	dedaux;			/* ptr auxiliary data	*/
	LONG	dedval;			/* value		*/
	LONG	dedmbr;			/* member		*/
#ifdef ctFeatCFG_SCALE
	LONG	dedscl;			/* scale		*/
#endif
	NINT	dedstt;			/* state		*/
	TEXT	dednam[MAX_NAME];	/* file name		*/
	} DEDLST;
typedef DEDLST ctMEM * pDEDLST;

typedef struct renlst {
	SYSNO	rensys;			/* system filno		*/
	FILNO	rennum;			/* user filno		*/
	COUNT	renseg;			/* optional segment #	*/
	TEXT	rennam[MAX_NAME];	/* old name		*/
	} RENLST;
typedef RENLST ctMEM * pRENLST;

typedef struct renrst {
#ifdef ctFeat6BT
	LONG	rentran2;
#endif
	LONG	rentran;
	ULONG	rentfil;
	NINT	rentype;
	NINT	renstat;
	pTEXT	reninfo;
	} RENRST;
typedef RENRST ctMEM * pRENRST;

typedef struct ressegm {		/* file segment resource	*/
		ULONG	restyp;
		ULONG	resnum;
		TEXT	resnam[FCRNAM_LEN];
		LONG	resact;		/* number of active seg		*/
		LONG	resflg;		/* client/server flag		*/
		LONG	resseq;		/* update counter		*/
		LONG	resavl;		/* available for use		*/
		LONG	reslen;		/* total resource length	*/
		LONG	restot;		/* number of seg in resource	*/
		TEXT	reskey[8];	/* beginning of ASCII stream	*/
	} RESSEGM, * pRESSEGM, * * ppRESSEGM;
#define RESSEGMsiz	(ctSIZE(RESSEGM) - 8)

typedef struct seglst {
	struct seglst ctMEM *	nxtseg;
	pRESSEGM		resseg;
	LONG			avlseg;
#ifdef ctFeatMAXFILE32
	FILNO			filseg;
#else
	COUNT			filseg;
	COUNT			padseg;
#endif
	} SEGLST;
typedef SEGLST ctMEM *	pSEGLST;
typedef SEGLST ctMEM * ctMEM * ppSEGLST;

typedef struct segchk {
	LONG	segmax;
	LONG	seglst;
	LONG	segsiz2;
	LONG	segsiz1;
	LONG	seganc2;
	LONG	seganc1;
	} SEGCHK, * pSEGCHK;

typedef struct reblst {
	struct reblst ctMEM *	nxtreb;
#ifdef ctFeat6BT
	LONG			trnreb2;
#endif
	LONG			trnreb;
	FILNO			numreb;
	COUNT			flgreb;
	TEXT			namreb[MAX_NAME];
	TEXT			tmpreb[MAX_NAME];
	} REBLST;
typedef REBLST ctMEM *	pREBLST;
typedef REBLST ctMEM * ctMEM * ppREBLST;

typedef struct usrlst {
	ULONG	usslst;
	TEXT	ussid[IDZ];
	} USRLST, ctMEM *pUSRLST;

#ifdef ctFeatDISKFULLactionEXT

/* DISK_FULL_ACTION logtype values: */
#define DFA_LOGTYPE_NO		0	/* no logging			*/
#define DFA_LOGTYPE_SYSLOG	1	/* write to c-tree system log	*/

/* DISK_FULL_ACTION action values: */
#define DFA_ACTION_CONTINUE	0	/* continue normal operation	*/
#define DFA_ACTION_SHUTDOWN	1	/* shut down server		*/

#endif /* ctFeatDISKFULLactionEXT */

typedef struct dfdef {
	pTEXT	volname;
#ifdef ctFeatCFG_SCALE_N8
	LONG8	volimit;
#else
	ULONG	volimit;
#endif
	NINT	volen;
#ifdef ctFeatDISKFULLactionEXT
	LONG8	prevtime;	  /* time of previous invocation	*/
	pTEXT	runcmd;		  /* command to execute			*/
#ifdef ctFeatDISKFULLactionEXT_UNX
	ppTEXT	arglist;	  /* argument list, like argv		*/
#endif
	LONG	freq;		  /* frequency				*/
	LONG	maxruntime;	  /* maximum script run time		*/
	LONG	errcod;		  /* error code				*/
#ifdef ctFeatDISKFULLactionEXTsyslog
	TEXT	logtype;	  /* type of logging			*/
	TEXT	scrlogtype;	  /* log option returned by script	*/
#endif
	pTEXT	scrcomment;	  /* comment returned by script		*/
	NINT	scraction;	  /* action returned by script		*/
	NINT	acttype;	  /* action type			*/
#endif
	} DFDEF, ctMEM * pDFDEF;

/* acttype values: */
enum {
	DF_ACTTYP_DFA = 0, /* disk full action invoking external script	*/
	DF_ACTTYP_DMP = 1  /* dynamic dump invoking ctrdmp utility	*/
};

/* dump restore parameters passed to immediate restore */
typedef struct ctdrp {
	pFILE	diaglog;	/* optional diagnostic log for ctrdmp output */
} ctDRP, *pctDRP;

typedef struct redlst {
	NINT	orglen;
	NINT	newlen;
	TEXT	orgpth[MAX_NAME];
	TEXT	newpth[MAX_NAME];
	} REDLST, * pREDLST;

/*
** Transaction log file types
*/
#define LOGTYP_NON	0x00000000	/* not a transaction log file	 */
#define LOGTYP_FCS	0x00000001	/* active transaction log file	 */
#define LOGTYP_FCT	0x00000002	/* transaction log file template */
#define LOGTYP_FCA	0x00000004	/* inactive transaction log file */

/*
** Encryption modification options
*/
#define ctENCMODlowl	0x00000001	/* low-level file open		 */
#define ctENCMODisam	0x00000002	/* ISAM level file open		 */
#define ctENCMODutil	0x00000004	/* call by ctencrypt util	 */
#define ctENCMODsysl	0x00000008	/* key encrypted at system level */
#define ctENCMODchk	0x00000010	/* check master password	 */

/* all currently-defined options */
#define ctENCMODall	(ctENCMODlowl|ctENCMODisam|ctENCMODutil|ctENCMODsysl|ctENCMODchk)

typedef struct ctencmod {
	LONG	options;
	LONG	numfiles;
	TEXT	varinf[4];
	} ctENCMOD, *pctENCMOD;


/* This typedef is used by the _findfirst,_findnext OS specific code	*/
/* in ct_findfile function. 						*/
#define CTFILEFIND_ALLOC 	1	/* OpCode Alloc 	*/
#define CTFILEFIND_FIRST 	2	/* OpCode Find First 	*/
#define CTFILEFIND_NEXT		3	/* OpCode Find Next 	*/
#define CTFILEFIND_CLOSE	4	/* OpCode Find CLose	*/
#define CTFILEFIND_FREE 	5	/* OpCode Free 		*/

#define CTFILEINFO_NOMATCH	 0L	/* wildcard pattern found-no match found*/
#define CTFILEINFO_OKMATCH	 1L	/* wildcard pattern found-match name found*/
#define CTFILEINFO_MISMATCH	-2L	/* wildcard pattern recurse all found-file does not match special compare */
#define CTFILEINFO_DOTDIR	-3L	/* wildcard pattern found-match file is DOT sub directory*/
#define CTFILEINFO_FC_FCS	-4L	/* wildcard pattern found-match file is DOT sub directory*/
#define CTFILEINFO_SUBDIR	-5L	/* wildcard pattern found-match file is FairCom LOG 	 */
#define CTFILEINFO_HIDDEN	-6L	/* wildcard pattern found-match file is hidden file  	 */
#define CTFILEINFO_SYSTEM	-7L	/* wildcard pattern found-match file is system file  	 */
#define CTFILEINFO_PATHERR_LOC	-86L	/* wildcard pattern found-PATH ERROR with LOCAL_DIRECTORY*/
#define CTFILEINFO_PATHERR_SRV	-87L	/* wildcard pattern found-PATH ERROR with SYSTEM_DIRECTORY*/
#define CTFILEINFO_BADRESULT	-88L	/* wildcard pattern found-Bad result found in OS function call */
#define CTFILEINFO_NOPATTERN	-99L	/* no wildcard patern in file name */

#define CTFILEFIND_MAXDIRLEV 	32	/* Max number of directories to recurse */

#define CTFILEFIND_RECURSE_NO	0	/* No subdirectory recusion 					*/
#define CTFILEFIND_RECURSE_YES	1	/* Recurse: Apply pattern to both file names and dir names	*/
#define CTFILEFIND_RECURSE_HYS	2	/* Recurse all subdirectoies, only apply pattern to file names 	*/

#define CTFILEFINDOPT_PREPEND_OFF 0x00000001	/* Do not prepend server directory name */
#define CTFILEFINDOPT_UGCHECK_OFF 0x00000002	/* Do not chech for valid file user/group (UNIX)*/
#define CTFILEFINDOPT_MATCH_FCS	  0x00000004	/* Return CTFILEINFO_FC_FCS status for all *.FCS files */

typedef struct ctOsFileFindInfo {
	NINT	myOpCode;	 	/* Current OpCode		*/
	NINT	myResurse;	 	/* Current Recurse Type		*/
	NINT	myhIdx;	 		/* Current myhFile (dir level) Index */
	NINT	myfIdx;	 		/* Current file number index within dir */
	NINT	myOptions;		/* Search options */
	NLONG	myhFile[CTFILEFIND_MAXDIRLEV];/* Handle returned by _first call	*/
	LONG 	myLastResult;	 	/* OS function last result code	     */
	LONG	myAttrib;		/* File Attribute		*/
	pTEXT	myScriptName;		/* Backup Script File Name	*/
	pTEXT	myBackupName; 		/* Backup File Name		*/
	TEXT	myBaseWildCard[MAX_NAME];/* Initial Wildcard Pattern 	*/		
	TEXT	myWildCard[MAX_NAME]; 	/* WildCard pattern used for find    */
	TEXT	myctWildCard[MAX_NAME]; /* WildCard pattern used ctrt_filmtc */
	TEXT	myDirName[MAX_NAME]; 	/* Current Directory name 	*/
	TEXT	myFileName[MAX_NAME]; 	/* Current file name 		*/
	} ctOS_FILE_FIND_INFO;
typedef ctOS_FILE_FIND_INFO ctMEM *pctOS_FILE_FIND_INFO;

#ifdef ctFeatFILMTX
/*
** file mutex structure
*/
typedef struct filmtx {
	NINT	fm_state;		/* in use, available, abandoned	*/
	NINT	fm_recr;		/* recursive count		*/
	NINT	fm_ownr;		/* non-persistent mutex owner	*/
					/* -1 for persistent mutex	*/
	RNDFILE	fm_fd;			/* file descrptor		*/
#if defined(ctFeatFPGloktimout) && defined(ctPortWIN32)
	HANDLE	fm_event;		/* async I/O event handle	*/
#endif
	TEXT	fm_name[MAX_NAME];	/* file mutex name		*/
	} FILMTX, * pFILMTX;
#endif

#ifdef ctFeatFILEUSRLST
/*
** user list structure
*/
typedef struct usrlstanc {
	pNINT	ul_ptr;
	NINT	ul_cur;
	NINT	ul_tot;
	} USRLSTANC, * pUSRLSTANC, ** ppUSRLSTANC;
#endif

/*^*******************/
#ifdef ctDIAG_FNC_MON
/* The ctDIAG_FNCMON option activate logics which will hold the last 	*/
/* ctDIAG_FNC_MON (defaults to 10) functions number called by each user */
/* This allows, as an example, the ctcatend or Exception handler to dump*/
/* the last function request by each user. 				*/
typedef struct ctsDIAGFNC {
	NINT	ctdiag_fn;	/* function number passed to doserver */
	LONG	ctdiag_time;	/* time of function */
	LONG	ctdiag_FM_cnt;  /* function sequence number */
#ifdef ctDIAG_FNC_MON_FNAM
	TEXT	ctdiag_fnam[ctDIAG_FNC_MON_FNAM];/* Open file only: just last ctDIAG_FNC_MON_FNAM chars */
#endif
	} CTDIAGFNC;
#endif /* ctDIAG_FNC_MON */
/*~*******************/

#ifdef ctFeatSrvTimer
#ifdef ctFeatSNAPSHOT
typedef struct srvtimer {
	LONG8	stim_call;
	LONG8	stim_recv;
	LONG8	stim_work;
	LONG8	stim_send;
	LONG8	stim_prev;
	LONG8	stmpwrk;
	LONG8	stmprcv;
	LONG8	stmpsnd;
	UINT	stmpcal;
	} SRVTIMER;
#else
typedef struct srvtimer {
	UNLONG	stim_call;
	UNLONG	stim_recv;
	UNLONG	stim_work;
	UNLONG	stim_send;
	UNLONG	stim_prev;
	UNLONG	stmpwrk;
	UNLONG	stmprcv;
	UNLONG	stmpsnd;
	UINT	stmpcal;
	} SRVTIMER;
#endif
#endif

#ifdef ctFeatSrvLock
typedef struct srvlock {
	UNLONG	sloktry;
	UNLONG	slokhlk;
	UNLONG	slokblk;
	UNLONG	slokhbk;
	UNLONG	slokdlk;
	UNLONG	slokkil;
	UNLONG	slokdny;
	UNLONG	slokfre;
	UNLONG	slokrel;
	} SRVLOCK;
#endif

typedef struct ctusrst {
	pTEXT	cmbuf;		/* communication buffer			*/
	NINT	clnver;		/* client attributes			*/
	LONG	apos1;		/* auto current ISAM position: lo word	*/
#ifdef ctHUGEFILE
	LONG	apos2;		/* auto current ISAM position: hi word	*/
#endif
	UTEXT	upntr;		/* user pointer size			*/
	COUNT	fndlen;		/* saved key length			*/
	TEXT	fndval[MAXLEN]; /* saved key buffer			*/
} ctUSRST, ctMEM * pctUSRST;

/*
** CTUSER pre-function modes:
*/
#define ctUSRPREcommbuff	0x00000001 /* use communication buffer	*/
#define ctUSRPREflexfile	0x00000002 /* use FLEXFILE feature	*/

#ifdef ctFeatCTSRVR_COMMP
#define CTUSER_PREFNC(usecombuf) ctUserPreFnc(sOWNR, usecombuf)
#define CTUSER_POSTFNC		 ctUserPostFnc(sOWNR)
#else
#define CTUSER_PREFNC (void)
#define CTUSER_POSTFNC
#endif

/*
** The system snapshots and user snapshots may included function timings
** and function call counts following the ctGSMS and ctGUMS structures.
** This data will be a variable number of ctWRKSTT structures.
*/

typedef struct wrkstt {
	ULONG	fnc;	/* function # used during compression of stats	*/
	ULONG	cnt;	/* function call count				*/
#ifdef ctBEHAV_FNCTIMupd
	volatile
	AULONG8	tim;	/* high resolution elapsed function time ATOMIC	*/
#else
	LONG8	tim;	/* high resolution elapsed function time	*/
#endif
	} ctWRKSTT, ctMEM * pctWRKSTT;

#include "ctifil.h"
#include "ctvrec.h"
#ifdef ctFeatREPLICAT
#include "ctrepl.h"
#endif

typedef struct dfrky {
	COUNT	opcode;		  /* deferred index operation code	*/
	TEXT	status1;	  /* status bit field #1		*/
	TEXT	status2;	  /* status bit field #2		*/
	ULONG	dfrkctr;	  /* deferred index create counter	*/
	LONG	fid[3];		  /* unique file ID of data file	*/
	LONG	oreclen;	  /* size of old record image (rewrite) */
	LONG	reclen;		  /* size of record image		*/
	LONG	datnamlen;	  /* length of data file name plus null */
	LONG8	orecbyt;	  /* old record offset (rewrite)	*/
	LONG8	recbyt;		  /* record offset			*/
	TEXT	varinf[1];	  /* variable length information:
		** For ctDFR_ADDKEY and ctDFR_DELKEY:
		**   null-terminated data file name
		**   record image
		**   4-byte number of index file numbers
		**   list of index file numbers
		**   4-byte schema ID (if file uses FLEXREC feature)
		** For ctDFR_RWTKEY and ctDFR_RWTPKEY:
		**   null-terminated data file name
		**   old record image
		**   record image
		**   4-byte number of index file numbers
		**   list of index file numbers
		**   4-byte schema ID for old record image (if using FLEXREC)
		**   4-byte schema ID for new record image (if using FLEXREC)
		** For ctDFR_LOADKEY:
		**   null-terminated data file name
		**   null-terminated index file name
		*/

} DFRKY, ctMEM **ppDFRKY;

/* Data types for record update callback operation information. (Uses the same
** format as the deferred index operation structure.) */
typedef DFRKY RUCBO;
typedef pDFRKY pRUCBO;
typedef ppDFRKY **ppRUCBO;

/* Size of fixed length portion of DFRKY structure (offset of varinf) */
#define DFRKYFIX (SegOff(DFRKY,varinf) - SegOff(DFRKY,opcode))

enum {
	DK_STATUS_INF = 0, /* informational message	*/
	DK_STATUS_WRN = 1, /* warning message		*/
	DK_STATUS_ERR = 2, /* error message		*/
	DK_STATUS_DBG = 3  /* diagnostic logging	*/
};

#ifdef PROTOTYPE
/* Prototype for deferred index logging function pointer. */
typedef NINT (*pDKLFN)(pDFKCTX pdfkctx, NINT msgtyp, cpTEXT fmt, ...);
NINT dfrkLogMsg(pDFKCTX pdfkctx,NINT msgtyp,cpTEXT fmt, ...);
#else
typedef NINT (*pDKLFN)();
NINT dfrkLogMsg();
#endif

/* Maximum length of unique ID. */
#define DFRK_UNQIDLEN	32

/* Deferred indexing state file record schema. */
typedef struct {
	TEXT	unqid[DFRK_UNQIDLEN];
	LONG8	serialnum;
	LONG	readlognum;
	ULONG	readlogpos;
	LONG	lastcmtlognum;
	ULONG	lastcmtlogpos;
	LONG	minlog;
	LONG	pad;
	TEXT	varinf[1];
} DFKSCH, *pDFKSCH;

typedef struct _dfkctx {
	/* These settings are configurable */

	/* Internal state variables */

	TEXT	unqid[DFRK_UNQIDLEN];/* Log read unique id		*/
	LONG8	serialnum;	/* Serial number for operation		*/
	LONG	readlognum;	/* Log number of last read position	*/
	ULONG	readlogpos;	/* Log offset of last read position	*/
	LONG	lastcmtlognum;	/* Log number of last committed position*/
	ULONG	lastcmtlogpos;	/* Log offset of last committed position*/
	LONG	minlog;		/* Minimum transaction log required	*/
	LONG	state;		/* State bits				*/
	LONG	opcount;	/* Operations in current tran		*/
	FILNO	stlgdat;	/* Deferred indexing state file		*/
	DFRKOP	curop;		/* Current operation of thread		*/
	pDKLFN	sctDKlog;	/* Deferred indexing logging function	*/
#ifdef ctFeatREPLICAT
	pctCNXH	pcnxhnd;	/* Log read connection handle		*/
	pctCHGB	pchgbuf;	/* Log read change buffer		*/
	pctCNXI	pcnxinf;	/* Log read connection info		*/
#else
	pVOID	pcnxhnd;	/* Log read connection handle		*/
	pVOID	pchgbuf;	/* Log read change buffer		*/
	pVOID	pcnxinf;	/* Log read connection info		*/
#endif
	ctLOGP	startlogpos;	/* Log read start position		*/
	LONG8	curbyt;		/* Offset of last processed record	*/
	LONG8	newbyt;		/* Offset of next record to process	*/
	pDFKSTT pdfkstt;	/* Deferred indexing statistics		*/
	FILNO	datno;		/* Current data file number		*/
	pCTFILE	dnum;		/* Data file system file control block	*/
	LONG	fid[3];		/* Unique file ID of data file		*/
	TEXT	datnam[MAX_NAME]; /* Current data file name		*/
} DFKCTX;

typedef struct dfrst {
	LONG	npass;	/* number of successful deferred key operations	*/
	LONG	nfail;	/* number of failed deferred key operations     */
} DFRST;

/* state information for creating deferred index load entry */
typedef struct dfrkld {
	LONG	keyno;	 /* file number of first index being created	*/
	LONG	numidx;	 /* total number of indices being created	*/
	LONG	numdfrh; /* number of physical indices in list		*/
	pNINT	pcreflg; /* host/member index indicator			*/
	pNINT	pnumdfr; /* count of deferred index members for host	*/
	pNINT	pnumemb; /* count of members for each host index	*/
} DFRKLD, *pDFRKLD;

/* state information for creating record update callback load entry */
typedef struct rucbld {
	pTEXT	cbname;	 /* name of record update callback		*/
	pTEXT	loadid;	 /* background load identifier			*/
} RUCBLD, *pRUCBLD;

typedef struct ctencatr {
	pTEXT	camptr;
	LONG	camlen;
	LONG	camver;
} ctENCATR, *pctENCATR;

typedef struct ctidxatr {
	NINT	blkcmp;	/* index uses block compression */
} ctIDXATR, *pctIDXATR;

/* singly-linked list state information */
typedef struct ctslst_t {
	pVOID	head;	/* pointer to first entry in list */
	pVOID	tail;	/* pointer to last entry in list */
	pVOID	curr;	/* pointer to current entry in list */
	NINT	nent;	/* number of entries in list */
} CTSLST, *pCTSLST, **ppCTSLST;

/* singly-linked list entry header information */
typedef struct ctslsh_t {
	pVOID	next;	/* pointer to next entry in list */
} CTSLSH, *pCTSLSH;

#define LDAP_ISAM	1
#define LDAP_SQL	2

#ifdef ctFeatLDAP
typedef struct ctlda {
	pTEXT	ldasrv;	/* LDAP server name	*/
	pTEXT	ldapfx;	/* LDAP prefix		*/
	pTEXT	ldasfx;	/* LDAP suffix		*/
	pTEXT	ldaaid;	/* Application ID	*/
	pTEXT	ldaapw;	/* Application ID pass	*/
	pTEXT	ldauid;	/* User ID		*/
	pTEXT	ldaupw;	/* User pass		*/
	LONG	ldatim;	/* LDAP connect timeout	*/
	ULONG	ldaprt;	/* LDAP port		*/
	NINT	ldassl;	/* Use SSL if non-zero	*/
	NINT	ldatyp;	/* Connection type	*/
} ctLDA, ctMEM * pctLDA;
#endif

#ifdef ctFeatSSL
typedef int(*pSSLPWF)(char *buf, int len, int verify, void *p);

typedef struct ctsubSSL {
	pTEXT	ssl_srv_certfile;	/* Name of file containing c-tree Server's certificate. */
	pTEXT	ssl_srv_keyfile;	/* Name of file containing c-tree Server's private key. Optional. */
	pTEXT	ssl_srv_keypassfile;	/* Name of c-tree encrypted store file containing password for c-tree Server's private key. Optional. */
	NINT	ssl_check_client_cert;	/* Check client certificate. */
	NINT	ssl_connect_only;	/* Only allow SSL connections. */
	NINT	ssl_init_complete;	/* Successfully initialized SSL support. */
	pTEXT	ssl_ciphers;		/* Supported SSL ciphers. */
	pSSLPWF	ssl_pfunc;		/* Function used to get server private key password. */
} ctSUSSL, *pctSUSSL;
#endif /* ctFeatSSL */

#define SSL_CIPHERS_DEFAULT "ECDH+AESGCM:DH+AESGCM:ECDH+AES256:DH+AES256:ECDH+AES128:DH+AES:ECDH+3DES:DH+3DES:RSA+AESGCM:RSA+AES:RSA+3DES:!aNULL:!MD5"

#ifdef ctFeatRP_AUTO
typedef struct ctsubARP {
	NINT	arp_init_complete;	/* Successfully initialized AUTO_RESTORE_POINT. */
	NINT	arp_log_interval;	/* Number of logs per automatic restore point. */
	NINT	arp_timeout;		/* Transaction completion timeout. */
	NINT	arp_fail_after_timeout;	/* Fail if transactions remain active after timeout. */
	NINT	arp_checkpoint;		/* Write checkpoint. */
	NINT	arp_lastlog;		/* Last log of successful auto restore point. */
} ctSUARP, *pctSUARP;
#endif

#ifdef ctFeatPWDREQ
typedef struct ctsubPWR {
	NINT	pwdreq_minlen;		/* Minimum allowed password length. */
	NINT	pwdreq_reqcls;		/* Minimum required character classes in password. */
	ULONG	pwdreq_expdays;		/* Systemwide default password expiration in days. */
} ctSUPWR, *pctSUPWR;
#endif

#ifdef ctFeatAWS
#include <ctaws.h>

typedef struct ctawsfnc {
	ctAWSgetLibraryVersionFunc_t	ctAWSgetLibraryVersion;
	ctAWSinitFunc_t			ctAWSinit;
	ctAWSshutdownFunc_t		ctAWSshutdown;
	ctAWSgetCredentialsFunc_t	ctAWSgetCredentials;
	ctAWSgetSecretFunc_t		ctAWSgetSecret;
	ctAWSputSecretFunc_t		ctAWSputSecret;
} ctAWSF, *pctAWSF;
#endif /* ctFeatAWS */

#ifdef ctFeatAWS_KEY_STORE
typedef struct ctsubAWS {
	pTEXT	aws_keyid;		/* master key id */
	pTEXT	aws_region;		/* region */
	LONG	aws_timeout;		/* timeout in seconds */
} ctSUAWS, *pctSUAWS;
#endif

#ifdef ctFeatADVLOG
typedef struct ctadvLOG {
	NINT oldstyle; /* cfgyn require a NINT*/
} ctADVLOG, *pctADVLOG;
#endif

#ifdef ctFeatDISTismcnt

#define ctNUM_ISAM_COUNTERS	4	/* number of ISAM counters	*/

/* Supported ISAM counters. */
typedef enum ismcnttyp {
	ctISAMreadCounter	= 0,	/* ISAM record read counter	*/
	ctISAMaddCounter	= 1,	/* ISAM record add counter	*/
	ctISAMupdateCounter	= 2,	/* ISAM record update counter	*/
	ctISAMdeleteCounter	= 3	/* ISAM record delete counter	*/
} ctICTYP;

/* ISAM counter values. */
typedef struct ismcntval {
	LONG8	ismredcnt;	/* ISAM record reads	*/
	LONG8	ismaddcnt;	/* ISAM record adds	*/
	LONG8	ismupdcnt;	/* ISAM record updates	*/
	LONG8	ismdelcnt;	/* ISAM record deletes	*/
} ctICVAL, *pctICVAL, **ppctICVAL;

#endif /* ctFeatDISTismcnt */

/* compressed transaction mark action info */
typedef struct cmactn {
	TEXT	mrkcval[10]; /* compressed transaction mark value */
	LONG	mrkclen; /* length of compressed transaction mark */
	LONG	action; /* action to take when setting mark */
} CMACTN, *pCMACTN;

/* cmactn action values: */
#define MRKSET 1	/* overwrite the already-allocated mark bytes with the specified value */
#define MRKCLN 2	/* change the mark value to the specified value; the new mark might use less space */

/* recovery list types: */
#define RCVLST_ORIG 1 /* operate on recovery list for original filename */
#define RCVLST_FULL 2 /* operate on recovery list for full filname */

/* automatic recovery filename hash bin list element */
typedef struct rcvopnlstele {
	struct rcvopnlstele *
		next;	/* next entry in this hash bin */
	NINT	sysno;	/* system file number*/
	TEXT	filnam[MAX_NAME]; /* file name */
} RCVOPNLSTELE, * pRCVOPNLSTELE;

/* automatic recovery filename hash table */
typedef struct rcvopnlsthsh {
	pRCVOPNLSTELE h; /* head of list for this hash bin */
	pRCVOPNLSTELE t; /* tail of list for this hash bin */
} RCVOPNLSTHSH, * pRCVOPNLSTHSH;

#ifdef ctPARTITION
/* parameters for ORDKEY() on partition host file */
typedef struct OrdKeyPartInfo_t {
	pCTFILE	partitionHostFCB;
	NINT	partitionHostFileNumber;
	NINT	rawPartitionNumber;
	FILNO	partitionKeyno;
	COUNT	relativeKeyNumber;
} ORDKEY_PART_INFO, *pORDKEY_PART_INFO;
#endif

/* index operation state  */
typedef struct idxOpState {
	TEXT * sctmrklst;	   /* temp storage for exc marks during split */
	TEXT sct_dupkey[MAXLEN+1]; /* for searches of duplicate keys */
	TEXT sspkey[MAXLEN+1];     /* temporary storage for key values during node updates */
	NINT sct_elm;		   /* position within B-Tree node */
	NINT sct_tky;		   /* result of comparison between target	*/
	NINT inuse;		/* use flag  				*/
				/* value and index entry.		*/
				/* ct_tky < 0 => target < index entry	*/
				/*	  = 0 => target = index entry	*/
				/*	  > 0 => target > index entry	*/
	NINT sct_tkp;		/* previous value of ct_tky 		*/
	NINT sct_sfxctp;	/* previous value of suffix count	*/
	NINT sbtlev;		/* b-tree level counter. used as index of */
				/* ct_npath				  */
	LONG sct_lnode1;	/* last node found during walk down tree */
   	LONG sct_fnode1;	/* node found during search/retrieval    */
  	LONG sct_nwnod1;	/* pointer to new node */
   	LONG sct_lnode2;	/* last node found during walk down tree */
  	LONG sct_fnode2;	/* node found during search/retrieval    */
   	LONG sct_nwnod2;	/* pointer to new node */
	LONG sct_npath1[MAXLEV];/* array to trace path down B-tree. Assumes  */
				 /* maximum of MAXLEV - 1 levels in B-tree.   */
	LONG sct_npath2[MAXLEV];
	NINT sct_nelem[MAXLEV]; /* array to trace elm values down B-tree */
	NINT sct_melem[MAXLEV]; /* array to trace nkv values down B-tree using key compression */
	NINT sct_tight[MAXLEV]; /* array to trace node overflow down B-tree using key compression */
} IDXSTATE;

/* ctMonitor_ITIM_ERR() error context codes */
typedef enum {
	ITIM_ERR_MEMORY_FILE_IO				= 1, /* offset not found in memory file hash table during I/O call */
	ITIM_ERR_RECORD_NOT_ACTIVE			= 2, /* offset in data file not marked active during ISAM read */
	ITIM_ERR_KEY_MISMATCH				= 3, /* key does not match current record image during ISAM read */
	ITIM_ERR_MEMORY_INDEX_IO			= 4, /* node offset not found in memory file hash table */
	ITIM_ERR_MEMORY_RECORD_NOT_ACTIVE_PREIMAGE	= 5, /* record image for memory file in preimage space not marked active */
	ITIM_ERR_MEMORY_RECORD_NOT_ACTIVE		= 6, /* record image for memory file not marked active */
	ITIM_ERR_MEMORY_FILE_CHECK			= 7, /* offset not found in memory file hash table when checking validity of offset */
	ITIM_ERR_RECORD_IS_DELETE_STACK_HEAD_ON_LOCK	= 8, /* offset matches delete stack offset during lock call */
	ITIM_ERR_RECORD_NOT_ACTIVE_ON_GET_LENGTH	= 9, /* offset in data file not marked active when getting record length */
	ITIM_ERR_RECORD_NOT_ACTIVE_ON_PREPARE_READ	= 10, /* offset in data file not marked active when preparing for variable length record read */
	ITIM_ERR_RECORD_NOT_ACTIVE_ON_REREAD		= 11 /* key does not match current record image when re-reading variable length record */
} itim_err_context_t;

/* cptifilx() parameters */
typedef struct cptIfilParams_t {
	NINT	preLength; /* number of bytes to reserve in allocated buffer preceding the IFIL data */
	NINT	postLength; /* number of bytes to reserve in allocated buffer following the IFIL data */
	TEXT	xcreblkIndexOnly; /* if non-zero the xcreblk is for index only, no array entry for data file */
} CPTIFIL_PARAMS, *pCPTIFIL_PARAMS;

/* cresmem() parameters */
typedef struct cresmemParams_t {
	LONG	splval; /* splval from xcreblk */
} CRESMEM_PARAMS, *pCRESMEM_PARAMS;

#ifdef CTPERM /* this block contains code for internal use only */

#ifdef ctFeatREPLICAT_SYNC2

/* possible states of a transaction on the secondary server */
typedef enum secondaryTransactionState_t {
	SECONDARY_UNKNOWN = 0, /* transaction state on secondary is unknown */
	SECONDARY_PENDING = 1, /* transaction waiting to be processed on secondary */
	SECONDARY_COMMITTED = 2, /* transaction committed on secondary */
	SECONDARY_ABORTED = 3 /* transaction aborted on secondary */
} SECONDARY_TRANSACTION_STATE;

/* a list of SYNC_COMMIT transcation log entries */
typedef struct syncCommitTranList_t {
	ULONG 	numberOfEntries; /* number of entries in the list */
	UINT	numberOfHashBins; /* size of hash bin array */
	ppBHL	hashBins; /* array of hash bin pointers for search by transaction number */
} SYNC_COMMIT_TRAN_LIST, *pSYNC_COMMIT_TRAN_LIST;

/* information about a synchronous replication agent stored in sync commit list entry */
typedef struct syncCommitListAgentInfo_t {
	TEXT	agentId[UNQIDLEN]; /* replication agent unique id */
	TEXT	agentServerName[MAX_SERVER_NAME]; /* replication agent server name */
} SYNC_COMMIT_TRAN_LIST_AGENT_INFO, *pSYNC_COMMIT_TRAN_LIST_AGENT_INFO;

/* an entry in the sync commit transaction list */
typedef struct syncCommitTranListEntry_t {
	LONG8	transactionNumber; /* transaction number */
	ctLOGP	commitPosition; /* transaction commit position */
	SECONDARY_TRANSACTION_STATE transactionState; /* transaction number */
	pSYNC_COMMIT_TRAN_LIST_AGENT_INFO agentList; /* the sync replication agent list for this transaction */
	ULONG	numAgents; /* number of agents in list */
	BHL	hashBin; /* hash bin links */
} SYNC_COMMIT_TRAN_LIST_ENTRY, *pSYNC_COMMIT_TRAN_LIST_ENTRY;

/* a list of synchronous replication agents */
typedef struct syncReplAgentList_t {
	ULONG 	numberOfEntries; /* number of entries in the list */
	UINT	numberOfHashBins; /* size of hash bin array */
	ppBHL	hashBins; /* array of hash bin pointers for search by agent unique id */
} SYNC_REPLAGENT_LIST, *pSYNC_REPLAGENT_LIST;

/* state bits for an entry in the synchronous replication agent list */
typedef enum syncReplAgentListEntryState_t {
	SYNC_REPLAGENT_STATE_NONE = 0x00000000, /* no state bits set */
	SYNC_REPLAGENT_STATE_REGINST = 0x00000002, /* we have registered a c-tree instance for this replication agent */
	SYNC_REPLAGENT_STATE_CONNECTED = 0x00000004, /* we have connected to the replication agent */
	SYNC_REPLAGENT_STATE_READ_CMTPOS = 0x00000008 /* we have read the commit position */
} SYNC_REPLAGENT_LIST_ENTRY_STATE;

/* length of c-tree instance name for connection to replication agent */
#define AGENT_INSTANCE_PREFIX "recov_"
#define AGENT_INSTANCE_LENGTH (6 + UNQIDLEN + MAX_SERVER_NAME + 1)

/* an entry in the synchronous replication agent list */
typedef struct syncReplAgentListEntry_t {
	SYNC_COMMIT_TRAN_LIST_AGENT_INFO agentInfo; /* information about the replication agent */
	SYNC_REPLAGENT_LIST_ENTRY_STATE agentState; /* our state for this replication agent */
	TEXT	agentInstance[AGENT_INSTANCE_LENGTH]; /* c-tree instance id for mtclient connection to this agent */
	ctLOGP	commitPosition; /* transaction commit position */
	BHL	hashBin; /* hash bin links */
} SYNC_REPLAGENT_LIST_ENTRY, *pSYNC_REPLAGENT_LIST_ENTRY;

/* recovery state variables used by sync commit processing */
typedef struct syncCommitRecoveryState_t {
	pLONG	pundos; /* number of transaction undos */
	pLONG	predos; /* number of transaction redos */
	pSYNC_COMMIT_TRAN_LIST pSyncCommitTranList; /* list of synchronous transactions found during recovery scan */
	pSYNC_REPLAGENT_LIST pSyncReplAgentList; /* list of synchronous replication agents found during recovery scan */
} SYNC_COMMIT_RECOVERY_STATE, *pSYNC_COMMIT_RECOVERY_STATE;

/* server roles */
typedef enum ctServerRole_t {
	SERVER_ROLE_ERROR = -2, /* could not get server role */
	SERVER_ROLE_NONE = -1, /* server has no special role */
	SERVER_ROLE_NOT_SET = 0, /* server role has not been set */
	SERVER_ROLE_PRIMARY = 1, /* server is a primary server */
	SERVER_ROLE_SECONDARY = 2 /* server is a secondary server */
} SERVER_ROLE;

#else  /* ~ctFeatREPLICAT_SYNC2 */
typedef void *pSYNC_COMMIT_RECOVERY_STATE;
#endif /* ~ctFeatREPLICAT_SYNC2 */

#endif /* CTPERM - end of block containing code for internal use only */

#endif /* ctSTRCH */

/* end of ctstrc.h */
