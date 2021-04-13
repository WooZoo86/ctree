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

#ifndef ctREPLH
#define ctREPLH

#ifndef ctREPLHonce
#define ctREPLHonce

#ifdef MULTITRD
#define ctREPL_EXTRACT_SUPPORT
#define ctREPL_LOCAL
#define ctREPL_FULL_API
#endif

#ifdef ctLOCLIB
#define ctREPL_APPLY_SUPPORT
#define ctREPL_EXTRACT_SUPPORT
#define ctREPL_LOCAL
#define ctREPL_REMOTE
#define ctREPL_MULTI_INST
#define ctREPL_FULL_API
#endif

#ifdef ctCLIENT
#define ctREPL_APPLY_SUPPORT
#define ctREPL_EXTRACT_SUPPORT
#define ctREPL_REMOTE
#define ctREPL_MULTI_INST
#define ctREPL_FULL_API
#endif

#ifdef ctMTCLIENT
#define ctREPL_APPLY_SUPPORT
#define ctREPL_EXTRACT_SUPPORT
#define ctREPL_REMOTE
#define ctREPL_MULTI_INST
#define ctREPL_FULL_API
#endif

#ifdef NOTFORCE 
#ifdef CTBOUND 
#ifndef ctLOCLIB
#ifndef ctBNDSRVR
#define ctREPL_APPLY_SUPPORT
#define ctREPL_LOCAL
#define ctREPL_MULTI_INST
#endif
#endif
#endif
#endif

#define REPLSESS_EXTR		0x00000001	/* Extract type session					*/
#define REPLSESS_APPL		0x00000002	/* Apply type session					*/
#define REPLSESS_NEW_ONLY	0x00000004	/* Do not return entries before target log position	*/
#define REPLSESS_BATCH		0x00000008	/* Enable batch retrieval mode for extract session	*/
#define REPLSESS_CONNTIMEOUT	0x00000010	/* Enable TCP/IP connection timeout			*/
#define REPLSESS_APICALLBACK	0x00000020	/* Enable replication API callback function		*/
#define REPLSESS_REPLPOS	0x00000040	/* Enable replication agent setting log requirements	*/
#define REPLSESS_FULLNAME	0x00000080	/* Return full file names from source server		*/
#define REPLSESS_DFRIDX		0x00000100	/* Read deferred index operation entries from log	*/
#define REPLSESS_QUIET		0x00000200	/* Agent is capable of responding to ctQUIET request	*/
#define REPLSESS_CVTSUBST	0x00000400	/* Return file name with SUBST converted to actual path	*/

/* Replication operation codes */
typedef enum replOpCodes_t {
	REPL_BEGTRAN	= 0,	/* begin transaction */
	REPL_SUCTRAN	= 1,	/* transaction commit succeeded */
	REPL_ABRTRAN	= 2,	/* abort transaction */
	REPL_ADDREC	= 3,	/* add record */
	REPL_RWTREC	= 4,	/* update record */
	REPL_DELREC	= 5,	/* delete record */
	REPL_OPNFIL	= 6,	/* open file */
	REPL_CLSFIL	= 7,	/* close file */
	REPL_ENDTRAN	= 8,	/* commit transaction */
	REPL_USRTRAN	= 9,	/* user-defined log entry */
	REPL_CHKPNT	= 10,	/* check point */
	REPL_DFRKEY	= 11,	/* deferred key operation */
	REPL_ALTER_SCHEMA = 12,	/* alter schema */
	REPL_RESYNC_FILE = 13,	/* resync file operation */
	REPL_PTADMIN	= 14,	/* PTADMIN() operation */
	REPL_TRUNCATE_FILE = 15,/* truncate file */
	REPL_DIRINFO	= 16,	/* directory info */
	REPL_CREIFIL	= 17,	/* create file */
	REPL_SETDEFBLK	= 18,	/* update file schema definition */
	REPL_CREATE_INDEX = 19,	/* create index */
	REPL_ADDRES	= 20,	/* add resource */
	REPL_UPDRES	= 21,	/* update resource */
	REPL_DELRES	= 22,	/* delete resource */
	REPL_DELIFIL	= 23,	/* delete file */
	REPL_DROP_INDEX = 24,	/* drop index */
	REPL_RENIFIL	= 25,	/* rename file */
	REPL_ADD_IDFIELD = 26,	/* add identity field */
	REPL_DEL_IDFIELD = 27,	/* delete identity field */
	REPL_RESET_IDFIELD = 28,/* reset identity field */
	REPL_XTDATR_IDFIELD = 29, /* set identity field extended attributes */
	REPL_CREATE_DATA_FILE = 30, /* lowlevel create data file */
	REPL_DELETE_DATA_FILE = 31, /* lowlevel delete data file */
	REPL_SYNC_COMMIT = 32 /* sync commit */
/*
NOTE: When adding a new replication opcode here, also update:
* ctrepd utility
* scnlog() function
* replication agent
*/
} REPL_OPCODES;
#define REPL_TOTAL	33 /* total number of replication operation codes */

/* Replication change buffer (ctCHGB) flags field bits: */
#define REPLFLAG_APPLY		(TEXT)0x01 /* operation done by replication writer */
#define REPLFLAG_DEFERADD_FRS	(TEXT)0x02 /* first update with deferred key add */
#define REPLFLAG_DEFERADD_LST	(TEXT)0x04 /* last update with deferred key add	*/
#define REPLFLAG_PARTHOST	(TEXT)0x08 /* partition host file */
#define REPLFLAG_DEFERTRAN	(TEXT)0x10 /* tran begin deferred (used in ctTRNB) */
#define REPLFLAG_REPIMGRWTFRS	(TEXT)0x20 /* first of multiple operations */
#define REPLFLAG_REPIMGRWT	(TEXT)0x40 /* subsequent operation */
#define REPLFLAG_UNQKEY		(TEXT)0x80 /* change buffer includes relative keyno of replication unique index */

/* Replication change buffer (ctCHGB) flags2 field bits: */
#define REPLFLAG2_HASFLXDAT	(TEXT)0x01 /* has schema ID for record image */
#define REPLFLAG2_HASTDELTA	(TEXT)0x02 /* for ENDTRAN operation: tstamp is relative time */
#define REPLFLAG2_SKIPTRAN	(TEXT)0x04 /* skip this transaction */
#define REPLFLAG2_DELNRAN	(TEXT)0x08 /* for CLSTRAN operation: this is the commit of a tran-dependent file delete */
#define REPLFLAG2_SUPHST	(TEXT)0x10 /* file is a superfile host */
/*
** NOTE: when adding a flags2 field bit, update ctrepd.c to display its value.
*/

/* ctreplopts connection state variable bits: */
#define REPLOPT_BATCH		0x00000001	/* Replication batch read support	*/
#define REPLOPT_FULLNAME	0x00000002	/* Return full file names to repl reader*/
#define REPLOPT_NOTIFYEVENTS	0x00000004	/* Event notification to external prog	*/
#define REPLOPT_QUIET		0x00000008	/* Handle ctQUIET() request		*/
#define REPLOPT_CVTSUBST	0x00000010	/* Resolve SUBST'd drives to real drive */

/* ctReplPersistMinLog() mode bits: */
#define REPLINST_REG	0x00000001	/* register replication instance		*/
#define REPLINST_UNR	0x00000002	/* unregister replication instance		*/
#define REPLINST_ATT	0x00000004	/* attach to replication instance		*/
#define REPLINST_LOG	0x00000008	/* set log number for replication instance	*/
#define REPLINST_DSC	0x00000010	/* disconnect replication instance		*/
#ifdef ctFeatREPL_TARGET_SVN
#define REPLINST_LOG2	0x00000020	/* set log number and target svn for replication instance */
#endif
#define REPLINST_QUIET	0x00000040	/* notify source server that agent is caught up */
#define REPLINST_CMTPOS	0x00000080	/* send agent commit position to primary server */

/* Replication version bits */
#define REPLVER_REPLPOS		0x00000001 /* replication agent maintains its position	*/
#define REPLVER_MULTIPOS	0x00000002 /* Server remembers all agents' positions	*/

#define ctFILE_KEYLEN	4	/* 4b tfil						*/
#define ctTRNOP_KEYLEN	8	/* 8b tranno						*/
#define ctTRNCMT_KEYLEN	17	/* 4b logser + 4b logpos + 8b tranno/tfil + 1b opcode	*/
#define ctREPL_ERROR_LEN	1024 /* Max error message length */

typedef enum {
	CTREPL_INST_SRV = 1,			/* Server instance			*/
	CTREPL_INST_LOC = 2			/* Local instance			*/
} ctREPINST;

typedef enum {
	NOREPL = 1,	/* File is not replicated */
	YESREPL = 2	/* File is replicated */
} RFLSTT;

enum {
	RA_STATUS_REP = -1,/* message from ctrepa.c	*/
	RA_STATUS_INF = 0, /* informational message	*/
	RA_STATUS_WRN = 1, /* warning message		*/
	RA_STATUS_ERR = 2  /* error message		*/
};

#if REPL_CHGBUF_VERSION >= 2
/* Fixed part of change buffer read from server includes all fields that precede bufsiz. */
#define ctCHG_FIXED_SIZE	(SegOff(ctCHGB, bufsiz))
#else
/* Fixed part of change buffer read from server stops after flags field. */
#define ctCHG_FIXED_SIZE	(SegOff(ctCHGB, avail))
#endif

/* Fixed part of change buffer is followed by log position */
#define ctCHG_FIXED_RET_SIZE	(ctCHG_FIXED_SIZE+ctSIZE(ctLOGP))

#ifdef ctFeatREPL_TARGET_SVN
#define RA_INST_NAME "INST_NAME"
#define RA_AGENT_SVN "AGENT_SVN"
#define RA_REPLICA_SVN "REPLICA_SVN"
#define RA_LOG_DIR "LOG_DIR"
#endif

/*
#define ctREPL_DBGMEMUSE
*/

/* Log read return values. */
typedef struct ctreadlog_t {
	ctLOGP	commitPosition; /* [IN] optional commit position to pass to source server */
	pTEXT	outBuffer; /* [OUT] buffer where log read data is written */
	ULONG	outBufferSize; /* [IN] size of output buffer in bytes */
	ULONG	numberOfBytesRead; /* [OUT] number of bytes read from log */
	TEXT	readStatus; /* [OUT] read status bits */
} ctRDLG, *pctRDLG;

/* Transaction commit list item. */
typedef struct _ctTCMT {
	LONG8		tranno;	/* Transaction number			*/
	struct _ctTCMT	*nxttrn;/* Pointer to next list item		*/
} ctTCMT, *pctTCMT;

typedef struct ctreplbfhlst {
	struct ctreplbfhlst ctMEM *flnk;
	struct ctreplbfhlst ctMEM *blnk;
	pVOID		     hbuf;
	} RBHL;
typedef RBHL ctMEM *	pRBHL;
typedef RBHL ctMEM * ctMEM * ppRBHL;

typedef struct fflti {
	TEXT	filnam[MAX_NAME];
	RBHL	bhlfil;	/* File list hash pointers	*/
	RFLSTT	replstatus;
} FFLTI, *pFFLTI, **ppFFLTI;

/* wildcard file filter list entry */
typedef struct wcfflti {
	pVOID	pRegularExpression; /* compiled regular expression */
	RBHL	bhlfil;	/* File list hash pointers	*/
	RFLSTT	replstatus; /* replication status for this file name */
	TEXT	filnam[MAX_NAME]; /* file name specification */
	TEXT	regex[MAX_NAME]; /* regular expression */
	TEXT	isRegularExpression; /* non-zero if this entry is a regular expression */
} WCFFLTI, *pWCFFLTI, **ppWCFFLTI;

#ifdef ctBEHAV_REPLPOS
/* Number of hash bins in transaction count hash table */
#define RTCH_BINS	17

/* Replication transaction count hash element */
typedef struct ctrtce {
	struct ctrtce *
		prev;		/* Previous entry in log number ordered list */
	struct ctrtce *
		next;		/* Next entry in log number ordered list     */
	RBHL	bhltc;		/* Transaction count list hash pointers	     */
	NINT	lognum;		/* Transaction log number for this entry     */
	ULONG	chkpos;		/* Offset of first checkpoint in this log    */
	NINT	chkposminlog;	/* Minimum required log as of checkpoint pos */
	NINT	count;		/* Number of active trans for this log	     */
#ifdef ctFeatTRANSACTION_ID
	LONG8	tranno;		/*  Transaction number for checkpoint	     */
#endif
} RTCE, ctMEM * pRTCE;
#endif

#ifdef ctBEHAV_REPLMINLOG
typedef struct chkinf {
	LONG	oldlog;		/* oldest log needed for recovery at chkpnt  */
} CHKINF, *pCHKINF;
#endif

/* Maximum length of replication agent unique ID */
#define UNQIDLEN	32

#define FILEAGENT_FILTER_ID	"<AGENT_FILTER>" /* replication file filter record identifier prefix */
#define FILEAGENT_FILTER_ID_LEN 14 /* length of replication file filter record identifier prefix */

/* values for SRASTT status field */
typedef enum srasttStatus_t {
	SRASTT_STATUS_SYNC = 0x00000001 /* synchronous; otherwise asynchronous */
} SRASTT_STATUS;

/* sync replication agent current state information, stored in memory of primary server */
typedef struct srastt {
	TEXT	agentId[UNQIDLEN]; /* replication agent unique ID */
#ifdef ctFeatREPLICAT_SYNC2
	TEXT	agentServerName[MAX_SERVER_NAME]; /* replication agent server name */
#endif
	ULONG	agentHandle; /* unique integer value assigned to this agent */
	SRASTT_STATUS status; /* status bits */
	ULONG	refcnt; /* reference count */
	ULONG	cmtlognum; /* transaction log number of last commit */
	ULONG	cmtlogpos; /* offset in transaction log of last commit */
} SRASTT, *pSRASTT;

#if defined(ctFeatREPLICAT_SRVRparallel) && defined(ctPortWIN32)
#include <synchapi.h>
#endif

#ifdef ctFeatREPLAGENTparallel
/* exclusive open list element */
typedef struct exclusiveOpenListEntry_t {
	struct exclusiveOpenListEntry_t *next; /* pointer to next item in list */
	ULONG	fileid;	/* tfil for data file */
} EXCLUSIVE_OPEN_LIST_ENTRY, *pEXCLUSIVE_OPEN_LIST_ENTRY;

/* list of file handles for files that are open exclusive */
typedef struct exclusiveOpenList_t {
	pEXCLUSIVE_OPEN_LIST_ENTRY head; /* pointer to first entry in list */
} EXCLUSIVE_OPEN_LIST, *pEXCLUSIVE_OPEN_LIST;
#endif

/* ctCNXH stateBits field bits */
#define REPLCNX_STATE_APPLY_PERSISTENT_FILE_FILTER 0x00000001 /* applying persistent file filter */

/* Connection handle. */
typedef struct replcnx {
#ifdef ctREPL_MULTI_INST
#ifdef ctREPL_REMOTE
	pVOID	srvinst;	/* c-tree Server instance name		*/
#endif
#ifdef ctREPL_LOCAL
	pVOID	locinst;	/* Local c-tree instance name		*/
#endif
#endif
	pTEXT	recbuf;		/* Record buffer for target record read	*/
	VRLEN	bufsiz;		/* Size of record buffer		*/
	VRLEN	redsiz;		/* Size of record last read into buffer */
	NINT	sesstype;	/* Session type: extract or apply	*/
	NINT	initscan;	/* Initial scan after setting pos	*/
	NINT	chkphs;		/* Processing checkpoint		*/
	LONG8	chktim;		/* Checkpoint timestamp			*/
	LONG	chklen;		/* Checkpoint size			*/
	FILNO	trnfil;		/*
				 * For extract: File number for transaction list idx
				 * For apply  : Replication state data file number
				 */
	FILNO	opsfil;		/*
				 * For extract: File number for operation list index
				 * For apply  : File number for tran op list index
				 */
	FILNO	tflfil;		/*
				 * For extract: File number for dat/idx tfil map
				 * For apply  : Not used
				 */
	FILNO	tfnfil;		/*
				 * For extract: File number for dat/filnam index
				 * For apply: File number for file list index
				 */
#ifdef ctFeatREPL_NODEID
#ifdef MULTITRD
	FILNO	nodfil;		/*
				 * For server: File number for node id index
				 */
	ULONG	replid;		/*
				 * For server: This client's replication node id
				 */
#endif
#endif
#ifdef ctFeatREPL_READ_BUFFER
#ifdef MULTITRD
	ctLOGP	lgrdpos;	/* Current log read position		*/
	ctLOGP	lgrdprv;	/* Previous log read position		*/
	pTEXT	lgrdbuf;	/* Log read buffer			*/
	pTEXT	lgrdchkbuf;	/* Log read check buffer		*/
	ULONG	lstpntred;	/* lstpnt when log read occurred	*/
	ULONG	lgrdsiz;	/* Log read buffer size			*/
	ULONG	lgrdchksiz;	/* Log read check buffer size		*/
	ULONG	lgrduse;	/* Log read buffer used length		*/
#endif
#endif
#ifdef ctFeatREPL_BATCH
#ifdef MULTITRD
	LONG	batops;		/* # of add/upd/del ops in buffer	*/
#else
	pTEXT	batbuf;		/* Buffer to hold multiple changes	*/
	pTEXT	batpos;		/* Pointer to current change in buffer	*/
	LONG	batsiz;		/* Size of batch buffer			*/
	LONG	batnxtsiz;	/* Size of next change from server	*/
#endif
	LONG	batnum;		/* Number of changes in buffer		*/
#endif
	ctLOGP	logpos;		/* Current log scan position		*/
	ctLOGP	tgtpos;		/* Target log scan position		*/
	FILNO	tcmtfil;	/* File number for tran commit list	*/
#ifdef ctREPL_DBGMEMUSE
	LONG	opslstent;	/* # entries in ops list		*/
	LONG	opslstmem;	/* memory in use by ops list		*/
	LONG	opslstmem0;	/* memory in use by ops list hdr	*/
	LONG	opslstmem1;	/* memory in use by ops list buf	*/
	LONG	opslstmem2;	/* memory in use by ops list var	*/
	LONG	tcmtlstent;	/* # entries in tran cmt list		*/
	LONG	tcmtlstmem;	/* memory in use by tran cmt list	*/
#endif
#ifdef ctMXLOGS
	LONG	logset;
#endif
#ifdef MULTITRD
	LONG	lowlog;		/* lowest log needed by repl reader	*/
	LONG	constt;		/* replication connection state bits	*/
	TEXT	instname[IDZ];	/* name of this persistent instance	*/
	struct thrdgv
		*ictgv;		/* ctgv for the connection		*/
	struct replcnx
		*replst;	/* replication thread list link		*/
	ctLOGP	oldtrnpos;	/*
				 * Log position of BEGTRAN for oldest
				 * pending transaction as of target
				 * log position.
				 */
#ifdef ctBEHAV_REPLMINLOG
	CHKINF	chkinf;		/* Checkpoint info			*/
#endif
#endif
#ifdef ctBEHAV_REPLPOS
#ifdef MULTITRD
	LONG	frscp;		/* First checkpoint in log		*/
	LONG	chklog;		/* Log of start checkpoint		*/
	LONG	chkpos;		/* Position of start checkpoint in log	*/
#else
	ppRBHL	tlcbhl;		/* Pointer to tran count hash bins	*/
	pRTCE	tlcfrs;		/* First entry in hash table (min tran)	*/
	pRTCE	tlclst;		/* Last entry in hash table (max tran)	*/
#endif
#endif
#ifdef ctFeatREPLENG_LOCAL_LIST
	ppRBHL	filbhl;		/* Pointer to file list hash bins	*/
	ppRBHL	opbhl;		/* Pointer to op list hash bins		*/
	ppRBHL	trnbhl;		/* Pointer to tran list hash bins	*/
#ifdef ctFeatREPL_FILENAME_HASH
	ppRBHL	fnmbhl;		/* Pointer to filename list hash bins	*/
#endif
	NINT	filhbins;	/* Number of hash bins for file list	*/
	NINT	ophbins;	/* Number of hash bins for op list	*/
	NINT	trnhbins;	/* Number of hash bins for tran list	*/
#ifdef ctFeatREPL_FILENAME_HASH
	NINT	fnmhbins;	/* Number of hash bins for filename list*/
#endif
	pVOID	trnfrs;		/* Head of tran commit order list	*/
	pVOID	trnlst;		/* Tail of tran commit order list	*/
#endif
#ifdef ctFeatREPL_FILTERfileSRV
	ppRBHL	fltbhl;		/* Pointer to filename filter hash bins	*/
	pRTCE	fltfrs;		/* First entry in hash table (file filt)*/
	pRTCE	fltlst;		/* Last entry in hash table (file filt)	*/
	NINT	flthbins;	/* Number of hash bins for filename filt*/
	ppRBHL	wcdbhl;		/* Pointer to filename filter hash bins	*/
	pRTCE	wcdfrs;		/* First entry in hash table (file wcrd)*/
	pRTCE	wcdlst;		/* Last entry in hash table (file wcrd)	*/
#endif
#ifdef ctFeatREPLENG_LOCK_RETRY
	NINT	lokretry;	/* Max attempts to retry record lock	*/
	NINT	loksleep;	/* msec between record lock attempts	*/
	NINT	lokdiag;	/* Lock error diagnostic information	*/
#endif
#ifdef ctFeatSET_ALIGN
	TEXT	set_align;	/* Set source record image alignment	*/
#endif
#ifdef ctCMPREC
	pVOID	popsbuf;	/* Current operation buffer		*/
#endif
	pVOID	pvrepstt;	/* replication agent state pointer	*/
#ifdef ctFeatREPL_TARGET_SVN
	TEXT	agentsvn[MAX_SERVER_NAME];	/* Server name for the replica agent	*/
	TEXT	replsvn[MAX_SERVER_NAME];	/* Server name for the replica server	*/
#endif
#ifdef ctFeatSCNLOGkeepalive
	LONG	maxrsptim;	/* Maximum allowed time in seconds for a call to
				ctReplGetNextChange() to return a response */
#ifdef ctSRVR
	LONG8	maxrsptimbas;	/* Base high resolution timer value */
	LONG8	maxrsptimthr;	/* High resolution timer value corresponding to
				the time at which a response must be returned */
	NINT	totdefertime;	/* Total ctdefer() time for current request */
	NINT	curdefertime;	/* ctdefer() time for current loop */
#endif
#endif
	NINT	replsrlsegusesource; /* REPL_SRLSEG_USE_SOURCE setting on server */
	NINT	replidentusesource; /* REPL_IDENTITY_USE_SOURCE setting on server */
#ifdef ctFeatREPLICAT_SYNC_SRVR
	pSRASTT	sraList; /* pointer to sync replication agent state list entry */
	RWLOCKmut sraListRwlock; /* mutex for serializing access to sraList pointer */
#endif
	TEXT	logDirectory[MAX_NAME]; /* transaction log directory	*/
	TEXT	baseDirectory[MAX_NAME]; /* source server's base directory */
	TEXT	pendingDirInfo; /* non-zero if we have directory info that we haven't yet returned */
	TEXT	substDrives[26][MAX_NAME]; /* source server's SUBST'd drives */
	TEXT	substDrivesInit; /* non-zero if SUBST'd drives list has been initialized */
	ctLOGP	logShipPosition;/* Current log ship write position	*/
	TEXT	errbuf[300];	/* buffer for error message		*/
	TEXT	serverLicenseType; /* server license type */
#ifdef ctFeatREPLICAT_SRVRparallel
	struct replcnx *logShipListEntry; /* pointer to our entry on the log ship list */
	TEXT	logFlushPositionInit; /* if non-zero, log flush position notification has been initialized */
#ifdef ctPortWIN32
	SRWLOCK logFlushPositionRWL; /* reader/writer lock for log flush notification */
	CONDITION_VARIABLE logFlushPositionCV; /* condition variable for log flush notification */
#else
	pthread_mutex_t logFlushPositionMTX; /* reader/writer lock for log flush notification */
	pthread_cond_t logFlushPositionCV; /* condition variable for log flush notification */
#endif
#endif
#ifdef ctFeatREPLAGENTparallel
	ULONG8	parallelTransactionSequenceNumber; /* last transaction sequence number used by replication agent */
	EXCLUSIVE_OPEN_LIST exclusiveOpenList; /* list of file handles that are open exclusive */
#endif
#ifdef ctSRVR
	ULONG	stateBits; /* state bits */
#endif
} ctCNXH, *pctCNXH;

/* Server license type values: */
#define SRVLICTYP_UNKNOWN	0	/* unknown server license type */
#define SRVLICTYP_DEVELOPMENT	1	/* server is licensed for development use */
#define SRVLICTYP_PRODUCTION	2	/* server is licensed for production use */

/* Server replication connection handle state bits (ctCNXH constt field): */
#define RCST_LOWLOGADJ	0x00000001 /* lowlog adjusted */
#define RCST_QUIETREQ	0x00000002 /* quiet requested */
#define RCST_QUIET	0x00000004 /* agent has caught up */
#define RCST_READSUC	0x00000008 /* sync repl agent read thread has read SUCTRAN entry */

/* Connection info. */
typedef struct {
	NINT	sesstype;	/* Session type				*/
	TEXT	uid[IDZ];	/* User name for server logon		*/
	TEXT	pwd[PWZX];	/* User password for server logon	*/
	TEXT	svn[MAX_SERVER_NAME]; /* Server name for server logon	*/
	TEXT	logpath[MAX_NAME]; /* Transaction log path		*/
	LONG	batsiz;		/* Batch buffer size			*/
	LONG	socktimeout;	/* TCP/IP connection timeout		*/
	pAPICB	ctapicallback;	/* c-tree API callback function		*/
	TEXT	TLScertSet;	/* Is TLS certificate name specified?	*/
	TEXT	TLScert[MAX_NAME]; /* TLS certificate file name		*/
} ctCNXI, *pctCNXI;

/* File identifier for data file on source system. */
typedef ULONG ctFLID;

/* File attributes */
typedef enum fileInfoFlags_t {
	FILINF_FLAG_NOREPL = 0x00000001, /* file is not replicated to this agent */
	FILINF_FLAG_YESREPL = 0x00000002, /* file is replicated to this agent */
	FILINF_FLAG_SUPHST = 0x00000004 /* file is a superfile host */
} FILE_INFO_FLAGS;

/* Information for file referenced in data source transaction log. */
typedef struct {
	TEXT	filnam[MAX_NAME];
	ULONG	keyid;	/* tfil for unique index	*/
	NINT	opnst;	/* open status			*/
	NINT	refct;	/* reference count		*/
#ifdef ctFeatREPL_FILTERfile
	FILE_INFO_FLAGS flags; /* file attributes */
#endif
	COUNT	nmem;	/* number of index members	*/
#ifdef ctCMPREC
	struct cmprecres_t *
		pcmpres;/* compression resource handle	*/
	struct cmprecfnc_t *
		pcmpfnc;/* compression function ptrs	*/
	pVOID
		pcmpexp;/* decompression context	*/
#endif
#ifdef ctFeatPARTREPL
	TEXT	parthst[MAX_NAME];
#endif
} ctFILI, *pctFILI, **ppctFILI;

/* Replication agent blocking lock timeout in seconds. */
#define ctREPL_LOKTIKMOUT	5

/* Replication socket timeout adjustment macro: Used to set the socket timeout
** to a value that is larger than the specified timeout. */
#define ctREPL_TIMEADJ(t) (t + 5)

/* File handle structure version */
#define REPFILH_VER1	1
#define REPFILH_VERSION REPFILH_VER1 /* current version of ctFILH */

/* File handle attribute bits: */
typedef enum fileHandleAttrib_t {
	FILHND_ATTRIB_PARTHOST = 0x00000001, /* file is a partition host */
	FILHND_ATTRIB_SUPHOST = 0x00000002, /* file is a superfile host */
	FILHND_ATTRIB_SUPMBR = 0x00000004 /* file is a superfile member */
} FILE_HANDLE_ATTRIB;

/* an entry in the superfile host list */
typedef struct superfileHostListEntry_t {
	TEXT	fileName[MAX_NAME]; /* the name of the file to close */
	FILNO	fileNumber; /* superfile host file number */
	ULONG	fileId;	/* tfil for superfile host */
	ULONG	numberOfOpenMembers; /* current number of open members */
	RBHL	nameHashBin; /* hash bin links for file name */
	RBHL	filnoHashBin; /* hash bin links for file number */
} SUPERFILE_HOST_LIST_ENTRY, *pSUPERFILE_HOST_LIST_ENTRY;

/* Information for file open on target. */
typedef struct ctfilh {
	ULONG	fileid;	/* tfil for source data file	*/
	FILNO	datno;	/* c-tree data file number	*/
	FILNO	keyno;	/* unique key file number	*/
#ifdef ctFeatREPLICAT_SUPERFILE
	pSUPERFILE_HOST_LIST_ENTRY pSuperfileHostListEntry; /* superfile host open file info */
#endif
	COUNT	filmod; /* data file mode		*/
	COUNT	reclen;	/* data record length		*/
	COUNT	keylen;	/* length of unique key		*/
	COUNT	numidx;	/* number of indexes		*/
	COUNT	srlpos; /* serial number offset		*/
	COUNT	srllen; /* serial number length		*/
	COUNT	idfield;/* identity field number	*/
	LONG	loktim;	/* lock timeout in seconds	*/
#ifdef ctFeatREPLENG_LOCAL_LIST
	RBHL	bhlfil;	/* File list hash pointers	*/
#ifdef ctFeatREPL_FILENAME_HASH
	RBHL	bhlfnm;	/* Filename list hash pointers	*/
	struct ctfilh
		*pofilhnd; /* Host file handle		*/
#endif
#endif
#ifdef ctFeatREPL_NODEID
	TEXT	filnam[MAX_NAME];
#endif
#ifdef ctFeatREPL_FILENAME_HASH
	NINT	refcnt;	/* file open reference count	*/
#endif
	NINT	flags;	/* replication flags		*/
	FILE_HANDLE_ATTRIB attrib; /* file attributes		*/
#ifdef ctFeatSET_ALIGN
	TEXT	align;	/* target record alignment	*/
#endif
#ifdef ctFeatREPLICAT_FLXDAT
	FLXDAT	schmid; /* file's schema version	*/
#endif
#ifdef ctFeatREPLAGENTparallel
	ctLOGP	lastUsedLogPosition; /* last log position of an operation on this file id */
	struct ctfilh *prevFileHandle; /* previous file handle in list */
	struct ctfilh *nextFileHandle; /* next file handle in list */
#endif
	NINT	opnmod;	/* file open mode		*/
} ctFILH, *pctFILH, **ppctFILH;

/* Change buffer. */
typedef struct {
	LONG8	tranno;		/*  0: Transaction number	*/
	LONG8	tstamp;		/*  8: Timestamp		*/
	LONG	logser;		/* 16: Log number		*/
	ULONG	logpos;		/* 20: Position in log		*/
	ctFLID	fileid;		/* 24: File ID			*/
	VRLEN	oldrln;		/* 28: Old record length	*/
	VRLEN	reclen;		/* 32: Record length		*/
	NINT	varlen;		/* 36: Size of variable info	*/
	NINT	oldkln;		/* 40: Old key length		*/
	NINT	keylen;		/* 44: Key length		*/
	TEXT	opcode;		/* 48: Operation code		*/
	TEXT	flags;		/* 49: Special status flags	*/
#if REPL_CHGBUF_VERSION >= 2
	TEXT	keyno;		/* 50: Relative index number of
				       replication unique index	*/
	TEXT	flags2;		/* 51: Special status flags #2	*/
#else
	TEXT	avail[2];	/* 50: Unused padding field	*/
#endif
	LONG	bufsiz;		/* 52: Size of varinf buffer	*/
	pTEXT	varinf;		/* 56: Ptr to variable info	*/
				/* Contents are in this order:	*/
				/* oldkey, key, oldrec, rec	*/
} ctCHGB, *pctCHGB;

#ifdef ctFeatREPL_NODEID
/* Node name list item. */
typedef struct {
	NINT	logst;		/* User logon status		*/
	ULONG	replid;		/* Replication node id		*/
} ctNODI, *pctNODI, **ppctNODI;
#endif

/* Replication agent commit position. The replication agent sends data in this
format to the primary server in a call to ctReplPersistMinLog() with mode
parameter of REPLINST_CMTPOS. */
typedef struct rcmpos {
	TEXT	instname[IDZ];	/* name of this persistent instance	*/
	ULONG	lognum; /* transaction log number */
	ULONG	logpos; /* offset in transaction log */
} RCMPOS, *pRCMPOS;

#ifdef ctFeatREPLmultipos
/* Replication agent log position stored in checkpoint */
typedef struct ralogp {
	TEXT	instname[IDZ];
	LONG	lowlog;
#ifdef ctFeatREPL_TARGET_SVN
	TEXT	agentsvn[MAX_SERVER_NAME];
	TEXT	replsvn[MAX_SERVER_NAME];
#endif
	TEXT	pad[2];
} RALOGP, *pRALOGP;

#ifdef ctFeatREPL_TARGET_SVN
/* Replication agent log position stored in checkpoint */
typedef struct ralogpv1 {
	TEXT	instname[IDZ];
	LONG	lowlog;
} RALOGPv1, *pRALOGPv1;
#endif

/* Extended replication agent log position returned in snapshot */

/* Version 1 of structure */
typedef struct ralogx1 {
	TEXT	instname[IDZ];
	LONG	lowlog;
	LONG	curlog;
	ULONG	curpos;
} RALOGX1, *pRALOGX1;

/* Current version of structure */
typedef struct ralogx {
	TEXT	instname[IDZ];
	LONG	lowlog;
	LONG	curlog;
	ULONG	curpos;
#ifdef ctFeatREPL_TARGET_SVN
	TEXT	agentsvn[MAX_SERVER_NAME];
	TEXT	replsvn[MAX_SERVER_NAME];
#endif
} RALOGX, *pRALOGX;
#endif

#ifdef ctFeatREPLICAT_TDELTA
#define raSTATvern	6	/* raSTAT (replication agent) version #	*/
#else
#define raSTATvern	3	/* raSTAT (replication agent) version #	*/
#endif

/* counters for pass/failure of a specified operation */
typedef struct rastatCounters_t {
	LONG8	pass;
	LONG8	fail;
} raSTAT_COUNTERS;

/* raSTAT structure configOptions field values */
typedef enum rastatConfigOptions_t {
	RASTAT_CONFIG_OPTION_PARALLEL = 0x00000001, /* parallel apply */
	RASTAT_CONFIG_OPTION_REPLICATE_FILE_CREATES = 0x00000002 /* replicating file creates */
} RASTAT_CONFIG_OPTIONS;

/* replication agent statistic structure, version 5 format */
typedef struct rastat5 {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	LONG8	fnseqno;	/* current function call sequence #	*/
	LONG8	ntotl;		/* Total successful operations		*/
	LONG8	nappl;		/* Successful apply operations		*/
	LONG8	ntbeg;		/* Successful transaction begins	*/
	LONG8	ntabt;		/* Successful transaction aborts	*/
	LONG8	ntend;		/* Successful transaction commits	*/
	LONG8	ntsuc;		/* Successful transaction success	*/
	LONG8	ntusr;		/* Successful user-defined entries	*/
	LONG8	nradd;		/* Successful record adds		*/
	LONG8	nrupd;		/* Successful record updates		*/
	LONG8	nrdel;		/* Successful record deletes		*/
	LONG8	nfopn;		/* Successful physical file opens	*/
	LONG8	nfcls;		/* Successful physical file closes	*/
	LONG8	etotl;		/* Total failed operations		*/
	LONG8	eappl;		/* Failed apply operations		*/
	LONG8	etbeg;		/* Failed transaction begins		*/
	LONG8	etabt;		/* Failed transaction aborts		*/
	LONG8	etend;		/* Failed transaction commits		*/
	LONG8	etsuc;		/* Failed transaction success		*/
	LONG8	eradd;		/* Failed record adds			*/
	LONG8	erupd;		/* Failed record updates		*/
	LONG8	erdel;		/* Failed record deletes		*/
	LONG8	efopn;		/* Failed physical file opens		*/
	LONG8	efcls;		/* Failed physical file closes		*/
	LONG	lognum;		/* Log number of current scan pos	*/
	ULONG	logpos;		/* Offset of current scan pos		*/
	LONG	curstate;	/* current status of replication agent	*/
	LONG	curctfunc;	/* current c-tree API function		*/
	LONG	constate;	/* server connection status		*/
#ifdef ctFeatREPLICAT_TDELTA
	LONG	tdelta;		/* Relative time of last commit (sec)	*/
#else
	LONG	avail;		/* available for future use		*/
#endif
	LONG8	nsalt;		/* Successful alter schema operations	*/
	LONG8	esalt;		/* Failed alter schema operations	*/
	LONG8	nsrsc;		/* Successful file resync operations	*/
	LONG8	esrsc;		/* Failed file resync operations	*/
	LONG8	nspta;		/* Successful PTADMIN operations	*/
	LONG8	espta;		/* Failed PTADMIN operations		*/
} raSTAT5, ctMEM * praSTAT5;

/* replication agent statistic structure, current version */
typedef struct rastat {
	ULONG	client_ver;	/* client version of structure		*/
	ULONG	server_ver;	/* server version of structure		*/
	LONG8	fnseqno;	/* current function call sequence #	*/
	LONG8	ntotl;		/* Total successful operations		*/
	LONG8	nappl;		/* Successful apply operations		*/
	LONG8	ntbeg;		/* Successful transaction begins	*/
	LONG8	ntabt;		/* Successful transaction aborts	*/
	LONG8	ntend;		/* Successful transaction commits	*/
	LONG8	ntsuc;		/* Successful transaction success	*/
	LONG8	ntusr;		/* Successful user-defined entries	*/
	LONG8	nradd;		/* Successful record adds		*/
	LONG8	nrupd;		/* Successful record updates		*/
	LONG8	nrdel;		/* Successful record deletes		*/
	LONG8	nfopn;		/* Successful physical file opens	*/
	LONG8	nfcls;		/* Successful physical file closes	*/
	LONG8	etotl;		/* Total failed operations		*/
	LONG8	eappl;		/* Failed apply operations		*/
	LONG8	etbeg;		/* Failed transaction begins		*/
	LONG8	etabt;		/* Failed transaction aborts		*/
	LONG8	etend;		/* Failed transaction commits		*/
	LONG8	etsuc;		/* Failed transaction success		*/
	LONG8	eradd;		/* Failed record adds			*/
	LONG8	erupd;		/* Failed record updates		*/
	LONG8	erdel;		/* Failed record deletes		*/
	LONG8	efopn;		/* Failed physical file opens		*/
	LONG8	efcls;		/* Failed physical file closes		*/
	LONG	lognum;		/* Log number of current scan pos	*/
	ULONG	logpos;		/* Offset of current scan pos		*/
	LONG	curstate;	/* current status of replication agent	*/
	LONG	curctfunc;	/* current c-tree API function		*/
	LONG	constate;	/* server connection status		*/
#ifdef ctFeatREPLICAT_TDELTA
	LONG	tdelta;		/* Relative time of last commit (sec)	*/
#else
	LONG	avail;		/* available for future use		*/
#endif
	LONG8	alterSchemaOk;	/* Successful alter schema operations	*/
	LONG8	alterSchemaFail; /* Failed alter schema operations	*/
	LONG8	fileResyncOk;	/* Successful file resync operations	*/
	LONG8	fileResyncFail;	/* Failed file resync operations	*/
	LONG8	PTADMINok;	/* Successful PTADMIN operations	*/
	LONG8	PTADMINfail;	/* Failed PTADMIN operations		*/
	raSTAT_COUNTERS counters[REPL_TOTAL]; /* pass/fail operation counters */
	ULONG	numberOfOpenFiles; /* number of open files (sum over all threads) */
	ULONG	configOptions;	/* replication agent configuration options */
	LONG	threadType;	/* Type of thread			*/
	LONG	threadInstance;	/* Thread instance			*/
	TEXT	curfuncname[64];/* Name of current function		*/

/*
NOTE: When changing this raSTAT structure:
1) Increment the raSTATvern value (#ifdef ctFeatREPLICAT_TDELTA) above.
2) Add a new size macro below for the new structure size.
3) Add code to revrastat() that reverses the new values if needed.
*/

} raSTAT, ctMEM * praSTAT;

/* Size of version 1 raSTAT structure */
#define RASTAT_SIZE_V1	(SegOff(raSTAT5,constate) + sizeof(LONG))

/* Size of version 2 raSTAT structure */
#define RASTAT_SIZE_V2	(SegOff(raSTAT5,esalt) + sizeof(LONG8))

/* Size of version 3 raSTAT structure */
#define RASTAT_SIZE_V3	(SegOff(raSTAT5,esrsc) + sizeof(LONG8))

/* Size of version 4 raSTAT structure */
#define RASTAT_SIZE_V4	RASTAT_SIZE_V3

/* Size of version 5 raSTAT structure */
#define RASTAT_SIZE_V5	sizeof(raSTAT5)

/* Size of version 6 raSTAT structure */
#define RASTAT_SIZE_V6	sizeof(raSTAT)

/*
** parallel replication state
*/

#define REPLAGENT_PARALLEL_STATE_VERSION	1	/* replication agent parallel state version number */

typedef struct replagentParallelState_t {
	ULONG	clientVersion; /* client version of structure */
	ULONG	serverVersion; /* server version of structure */
	LONG	tranStatusEntryCount; /* number of entries in transaction status list */
	LONG	analysisQueueEntryCount; /* number of entries in analysis queue */
	LONG	dependQueueEntryCount; /* number of entries in dependency queue */
	LONG	dependGraphEntryCount; /* number of entries in dependency graph */
	LONG	tranReadyQueueEntryCount; /* number of entries in transaction ready queue */
	LONG	numberOfApplyConnectedToTarget; /* number of apply threads connected to target server */
	TEXT	logShipConnectedToSource; /* logship thread is connected to source server */
	TEXT	logReadConnectedToSource; /* logship thread is connected to local source server */
} REPLAGENT_PARALLEL_STATE, *pREPLAGENT_PARALLEL_STATE;

/* size of version 1 replication agent parallel state structure */
#define REPLAGENT_PARALLEL_STATE_SIZE_V1	(SegOff(REPLAGENT_PARALLEL_STATE,logReadConnectedToSource) + sizeof(TEXT))

struct _ctrastt; /* forward declaration */
typedef struct _ctrastt *pctRASTT;
typedef NINT (*pctRACB)(NINT opcd, pTEXT ibuf, VRLEN ilen, pTEXT obuf, pVRLEN olen, pctRASTT prepstt);
typedef NINT (*pctRAMN)(NINT argc, pVOID argv);
/* Prototype for replication agent logging function pointer. */
typedef NINT (*pRALFN)(pctRASTT prepstt, NINT msgtyp, cpTEXT fmt, ...);
/* Prototype for memory allocation function */
typedef pVOID (*allocFunc_t)(LONG allocSize);
/* Prototype for memory free function */
typedef void (*freeFunc_t)(pVOID ptr);

enum {
	ctRAOPshutdown	= 1,	/* shutdown replication agent	*/
	ctRAOPgetstats	= 2,	/* get replication statistics	*/
	ctRAOPpause	= 3,	/* pause or resume replication agent	*/
	ctRAOPgetfuncs	= 4,	/* get function call statistics	*/
	ctRAOPgetfuncsd	= 5,	/* get function call statistics	(delta) */
	ctRAOPresetfuncs= 6,	/* reset function call statistics */
	ctRAOPfnctim	= 7,	/* enable or disable function time collection */
	ctRAOPexceptlog = 8,	/* set exception logging options */
	ctRAOPchangefilter = 9,	/* change replication file filter	*/
	ctRAOPremovefilter = 10,	/* remove replication file filter	*/
	ctRAOPgetfilters = 11,	/* get file filter list	*/
	ctRAOPresync = 12,	/* resync the list of replicated files	*/
	ctRAOPresyncstate = 13,	/* retrieve resync state by ID or all active ones */
	ctRAOPgetresyncfiles = 14,	/* retrieve resync list of files */
	ctRAOPresyncclean = 15,	/* cleanup resync resources */
	ctRAOPunreg	= 16,	/* unregister replication agent */
	ctRAOPresume	= 17,	/* resume replication agent	*/
	ctRAOPfnctimOff	= 18,	/* disable function time collection */
	ctRAOPexceptlogOff = 19,/* turn off exception logging */
	ctRAOPgetagentids = 20,	/* get agent ID list */
	ctRAOPskipops = 21,	/* skip applying operations */
	ctRAOPskipopsOff = 22,	/* resume applying operations */
	ctRAOPgetparallelstate = 23, /* get parallel replication state */
	ctRAOPgetparallelthreads = 24, /* list parallel replication threads */
	ctRAOPgetstate = 25,	/* get replication statistics	*/
	ctRAOPsetconfig = 26,	/* set replication configuration option */
	ctRAOPgetcommitpos = 27	/* get replication agent last commit position */

/* NOTE: When adding an entry here, also increment ctRAOP_TOTAL below, and
   add an entry to ctRAOPoutputOnError in ctrepl.c to indicate if the new
   operation returns output data on failure or not. */

};
#define ctRAOP_TOTAL	26

/* Options that can be OR'd into the ctReplAgentOp() opcd parameter: */
#define ctRAOPhasAgentId	0x00800000
#define ctRAOPhasThreadId	0x00400000

/* All supported flags that can OR'd into the opcd parameter: */
#define ctRAOPflagsALL	(ctRAOPhasAgentId | ctRAOPhasThreadId)

/* NOTE: Internally the client library turns on one of these two bits in the
ctReplAgentOp() opcd parameter to indicate the client's byte order. */
#define ctRAOPflagHILO	0x01000000
#define ctRAOPflagLOHI	0x02000000

/* Internal opcd option bits: */
#define ctRAOPflagINTERNAL (ctRAOPflagHILO|ctRAOPflagLOHI)

extern NINT ctRAOPoutputOnError[];

enum {
	ctMASTERCTLrstlok = 1,	/* restore lock state of record we just read */
	ctMASTERCTLsetlsh = 2	/* set secure logon hash callback function */
};

/* Replication agent flags */
#define ctRAFLGcfgapi	0x00000001 /* replication agent config set by API calls */
#define ctRAFLGsigint	0x00000002 /* replication agent shuts down on SIGINT */
#define ctRAFLGoutlog	0x00000004 /* redirect standard error/output to log */
#define ctRAFLGchksvc	0x00000008 /* check if process is running as service */
#define ctRAFLGappmtc	0x00000010 /* application initialized mtclient DLL */
#define ctRAFLGappsrv	0x00000020 /* application initialized server DLL */
#define ctRAFLGsetpos	0x00000040 /* application set start position */
#define ctRAFLGsetposid	0x00000080 /* use transaction id to set start position */
#define ctRAFLGgetcurpos 0x00000100 /* get current log position from source server */

/* Replication agent state bits */
#define ctRASTTlogopn	0x00000001 /* log already open, so do not close it */
#define ctRASTTsetmin	0x00000002 /* chkpnt updated minlog */
#define ctRASTTaddkydfr 0x00000004 /* key add is deferred */
#define ctRASTTdbinit	0x00000008 /* replagent database engine has been initialized */

#ifdef ctFeatREPL_FILTER_CHANGE
#include "ctatrd.h"

typedef enum {
	CTREPL_FFCHG_INIT = 0,			/* File filter change initial */
	CTREPL_FFCHG_REQ = 1,			/* File filter change request */
	CTREPL_FFCHG_DONE = 2,			/* File filter change done    */
	CTREPL_FFCHG_ERROR = 3 			/* File filter change error   */
} ctREPFFCHG;
#endif /* ctFeatREPL_FILTER_CHANGE */

#ifdef ctFeatTRANREPL

/* Default names for c-tree dynamically loaded client module. */

#ifdef ctPortWIN32
#define ctDEFAULT_CLIENT_MODULE_NAME "mtclient.dll"
#endif

#ifdef ctPortMACOSX
#define ctDEFAULT_CLIENT_MODULE_NAME "libmtclient.dylib"
#endif

#ifdef ctPortHPUX
#define ctDEFAULT_CLIENT_MODULE_NAME "libmtclient.sl"
#endif

#ifndef ctDEFAULT_CLIENT_MODULE_NAME
#define ctDEFAULT_CLIENT_MODULE_NAME "libmtclient.so"
#endif

/*
** To add support for additional c-tree functions, search for <NEW_ENTRY>
** and make the appropriate changes.
*/

/*
** c-tree Plus API function type definitions,
** used to define appropriate data types for function pointers.
*/
#ifndef ctCTCLSVAP /* Suppress these definitions when compiling ctclsv.c */
typedef NINT		(*pctThrdInit_t)(NINT, LONG, pctINIT);
typedef NINT		(*pctThrdTerm_t)(VOID);
typedef COUNT		(*pINTISAMX_t)(COUNT, FILNO, COUNT, COUNT, COUNT, pTEXT, pTEXT, pTEXT);
typedef COUNT		(*pSTPUSR_t)(VOID);
typedef COUNT		(*pOPNIFILX_t)(pIFIL, pTEXT, pTEXT, pTEXT);
typedef FILNO		(*pOPNRFILX_t)(FILNO, pTEXT, COUNT, pTEXT);
typedef COUNT		(*pctGetUserErrorCode_t)(VOID);
typedef COUNT		(*pctGetIsamErrorCode_t)(VOID);
typedef COUNT		(*pctGetIsamFileNbr_t)(VOID);
typedef COUNT		(*pctGetSystemErrorCode_t)(VOID);
typedef COUNT		(*pCLIFIL_t)(pIFIL);
typedef LONG		(*pGETFIL_t)(FILNO, COUNT);
typedef COUNT		(*pSETNODE_t)(pTEXT);
typedef COUNT		(*pCLRFIL_t)(FILNO);
typedef LONG		(*pTRANBEG_t)(COUNT);
typedef COUNT		(*pTRANRDY_t)(VOID);
typedef COUNT		(*pTRANEND_t)(COUNT);
typedef COUNT		(*pTRANABT_t)(VOID);
typedef COUNT		(*pTRANABTX_t)(COUNT);
typedef COUNT		(*pADDREC_t)(FILNO, pVOID);
typedef COUNT		(*pADDVREC_t)(FILNO, pVOID, VRLEN);
typedef COUNT		(*pTRANSAV_t)(VOID);
typedef COUNT		(*pTRANRST_t)(COUNT);
typedef LONG		(*pSPCLSAV_t)(VOID);
typedef COUNT		(*pFRSREC_t)(FILNO,pVOID);
typedef COUNT		(*pFRSVREC_t)(FILNO,pVOID,pVRLEN);
typedef COUNT		(*pLSTREC_t)(FILNO,pVOID);
typedef COUNT		(*pLSTVREC_t)(FILNO,pVOID,pVRLEN);
typedef COUNT		(*pNXTREC_t)(FILNO,pVOID);
typedef COUNT		(*pNXTVREC_t)(FILNO,pVOID,pVRLEN);
typedef COUNT		(*pPRVREC_t)(FILNO,pVOID);
typedef COUNT		(*pPRVVREC_t)(FILNO,pVOID,pVRLEN);
typedef COUNT		(*pRWTREC_t)(FILNO,pVOID);
typedef COUNT		(*pRWTVREC_t)(FILNO,pVOID,VRLEN);
typedef COUNT		(*pDELREC_t)(FILNO);
typedef COUNT		(*pDELVREC_t)(FILNO);
typedef COUNT		(*pEQLREC_t)(FILNO,pVOID,pVOID);
typedef COUNT		(*pGTEREC_t)(FILNO,pVOID,pVOID);
typedef COUNT		(*pGTREC_t)(FILNO,pVOID,pVOID);
typedef COUNT		(*pLTEREC_t)(FILNO,pVOID,pVOID);
typedef COUNT		(*pLTREC_t)(FILNO,pVOID,pVOID);
typedef COUNT		(*pEQLVREC_t)(FILNO,pVOID,pVOID,pVRLEN);
typedef COUNT		(*pGTEVREC_t)(FILNO,pVOID,pVOID,pVRLEN);
typedef COUNT		(*pGTVREC_t)(FILNO,pVOID,pVOID,pVRLEN);
typedef COUNT		(*pLTEVREC_t)(FILNO,pVOID,pVOID,pVRLEN);
typedef COUNT		(*pLTVREC_t)(FILNO,pVOID,pVOID,pVRLEN);
typedef LONG		(*pSETOPS_t)(LONG,VRLEN);
typedef COUNT		(*pCREIFILX8_t)(pIFIL,pTEXT, pTEXT, LONG, pTEXT ,pTEXT, pXCREblk);
typedef COUNT		(*pPUTDODA_t)(FILNO, pDATOBJ, UCOUNT);
typedef NINT		(*pctReplAgentSetCallback_t)(pctRACB);
typedef COUNT		(*pREDVREC_t)(FILNO, pVOID, VRLEN);
typedef COUNT		(*pSAVPCLR_t)(VOID);
typedef LONG		(*pCTUSERX_t)(pTEXT,pTEXT,VRLEN,pTEXT,pVRLEN);
typedef LONG		(*pctTransferFile_t)(pctXFRFIL pxfr);
typedef NINT		(*pctOWNER_t)(VOID);
typedef VOID		(*pctSetOWNER_t)(NINT sOWNR);
typedef NINT		(*pctReplMasterControl_t)(LONG mode, pVOID data);
typedef COUNT		(*pREGCTREE_t)(pTEXT regid);
typedef COUNT		(*pUNRCTREE_t)(pTEXT regid);
typedef NINT		(*pctThrdAttach_t)(VOID);
typedef NINT		(*pctThrdDetach_t)(VOID);
typedef pVOID		(*pGETCTREE_t)(pTEXT regid);
typedef NINT		(*pctSETCLIENTID_t)(pVOID pclientid, NINT clientidlen);
typedef NINT		(*pctdbGetCtreeOWNER_t)(VOID);
typedef VOID		(*pctdbSetCtreeOWNER_t)(NINT sOWNR);
typedef COUNT		(*pOPNFILX_t)(FILNO filno,pTEXT filnam,COUNT filmod,pTEXT fileword);
typedef COUNT		(*pPUTIFILX8_t)(pIFIL ifilptr,pTEXT dataextn,pTEXT indxextn,pTEXT fileword,pXCREblk pxcreblk);
typedef COUNT		(*pAVLFILNUM_t)(COUNT numfils);
typedef COUNT		(*pCLSFIL_t)(FILNO filno,COUNT filmod);
typedef NINT		(*pSetXtdFileOpenMode_t)(LONG mode);
typedef COUNT		(*pRWTPREC_t)(FILNO,pVOID,VRLEN);
typedef NINT		(*pctConnStateAlloc_t)(NINT mode,NINT alcsiz,ppVOID ppvalue);
typedef NINT		(*pctConnStateFree_t)(NINT mode);
typedef NINT		(*pctConnStateGet_t)(NINT mode,ppVOID ppvalue);
typedef COUNT		(*pLKISAM_t)(COUNT mode);
typedef COUNT		(*pGETNAM_t)(FILNO filno, pTEXT nambuf, VRLEN buflen, COUNT mode);
typedef NINT		(*pctReplAgentSetState_t)(NINT mode,pctRASTT prepstt);
typedef NINT		(*pctReplAgentSetArgs_t)(NINT argc,ppTEXT argv);
typedef COUNT		(*pSETFLTR_t)(FILNO datno, pTEXT condexpr);
typedef NINT		(*pctRecordUpdateCallbackControl_t)(pRUCBCTL prucbctl);
typedef COUNT		(*pSWTCTREE_t)(pTEXT regid);
typedef NINT            (*pctReplAgentOp_t)(NINT opcd, pTEXT ibuf, VRLEN ilen, pTEXT obuf, pVRLEN polen);
typedef NINT		(*pctSetCommProtocolOption_t)(NINT option,pVOID value);
typedef NINT		(*pctWorkerThrdAttach_t)(VOID);
/* <NEW_ENTRY>
typedef RTNTYP		(*pctNewAPIFunction_t)(PARAMLIST);
*/
#endif /* ~ctCTCLSVAP */

/*
** c-tree Plus API function identifiers,
** used as index into function pointer list.
*/

#define	CTCLI_ctThrdInit		0
#define	CTCLI_ctThrdTerm		1
#define	CTCLI_INTISAMX			2
#define	CTCLI_STPUSR			3
#define	CTCLI_OPNIFILX			4
#define	CTCLI_OPNRFILX			5
#define CTCLI_ctGetUserErrorCode	6
#define CTCLI_ctGetIsamErrorCode	7
#define CTCLI_ctGetIsamFileNbr		8
#define CTCLI_ctGetSystemErrorCode	9
#define CTCLI_CLIFIL			10
#define CTCLI_GETFIL			11
#define CTCLI_SETNODE			12
#define CTCLI_CLRFIL			13
#define CTCLI_TRANBEG			14
#define CTCLI_TRANRDY			15
#define CTCLI_TRANEND			16
#define CTCLI_TRANABT			17
#define CTCLI_TRANABTX			18
#define CTCLI_ADDREC			19
#define CTCLI_ADDVREC			20
#define CTCLI_TRANSAV			21
#define CTCLI_TRANRST			22
#define CTCLI_SPCLSAV			23
#define CTCLI_FRSREC 			24
#define CTCLI_FRSVREC			25
#define CTCLI_LSTREC 			26
#define CTCLI_LSTVREC			27
#define CTCLI_NXTREC 			28
#define CTCLI_NXTVREC			29
#define CTCLI_PRVREC 			30
#define CTCLI_PRVVREC			31
#define CTCLI_RWTREC 			32
#define CTCLI_RWTVREC			33
#define CTCLI_DELREC			34
#define CTCLI_DELVREC			35
#define CTCLI_EQLREC			36
#define CTCLI_GTEREC			37
#define CTCLI_GTREC			38
#define CTCLI_LTEREC			39
#define CTCLI_LTREC			40
#define CTCLI_EQLVREC			41
#define CTCLI_GTEVREC			42
#define CTCLI_GTVREC			43
#define CTCLI_LTEVREC			44
#define CTCLI_LTVREC			45
#define CTCLI_SETOPS			46
#define CTCLI_CREIFILX8			47
#define CTCLI_PUTDODA			48
#define CTCLI_ctReplAgentSetCallback	49
#define CTCLI_REDVREC			50
#define CTCLI_SAVPCLR			51
#define CTCLI_CTUSERX			52
#define CTCLI_ctTransferFile		53
#define CTCLI_ctOWNER			54
#define CTCLI_ctSetOWNER		55
#define CTCLI_ctReplMasterControl	56
#define CTCLI_REGCTREE			57
#define CTCLI_UNRCTREE			58
#define CTCLI_ctThrdAttach		59
#define CTCLI_ctThrdDetach		60
#define CTCLI_GETCTREE			61
#define CTCLI_ctSETCLIENTID		62
#define CTCLI_ctdbGetCtreeOWNER 	63
#define CTCLI_ctdbSetCtreeOWNER 	64
#define CTCLI_OPNFILX		 	65
#define CTCLI_PUTIFILX8		 	66
#define CTCLI_AVLFILNUM		 	67
#define CTCLI_CLSFIL		 	68
#define CTCLI_SetXtdFileOpenMode	69
#define CTCLI_RWTPREC			70
#define CTCLI_ctConnStateAlloc		71
#define CTCLI_ctConnStateFree		72
#define CTCLI_ctConnStateGet		73
#define CTCLI_LKISAM			74
#define CTCLI_GETNAM			75
#define CTCLI_ctReplAgentSetState	76
#define CTCLI_ctReplAgentSetArgs	77
#define CTCLI_SETFLTR			78
#define CTCLI_ctRecordUpdateCallbackControl 79
#define CTCLI_SWTCTREE			80
#define CTCLI_ctReplAgentOp		81
#define CTCLI_ctSetCommProtocolOption	82
#define CTCLI_ctWorkerThrdAttach	83
/* <NEW_ENTRY>
#define	CTCLI_ctNewAPIFunction		84
*/

#define CTCLI_TOTAL			84
/* <NEW_ENTRY>
#define CTCLI_TOTAL			85
*/

extern pVOID	ctClientFuncPtrs[CTCLI_TOTAL];

/*
** c-tree Plus API function macros,
** used to map API function calls to function pointer references.
*/

#define	ctThrdInit_C		(*(pctThrdInit_t)ctClientFuncPtrs[CTCLI_ctThrdInit])
#define	ctThrdTerm_C		(*(pctThrdTerm_t)ctClientFuncPtrs[CTCLI_ctThrdTerm])
#define	INTISAMX_C		(*(pINTISAMX_t)ctClientFuncPtrs[CTCLI_INTISAMX])
#define	STPUSR_C		(*(pSTPUSR_t)ctClientFuncPtrs[CTCLI_STPUSR])
#define	OPNIFILX_C		(*(pOPNIFILX_t)ctClientFuncPtrs[CTCLI_OPNIFILX])
#define	OPNRFILX_C		(*(pOPNRFILX_t)ctClientFuncPtrs[CTCLI_OPNRFILX])
#define ctGetUserErrorCode_C	(*(pctGetUserErrorCode_t)ctClientFuncPtrs[CTCLI_ctGetUserErrorCode])
#define ctGetIsamErrorCode_C	(*(pctGetIsamErrorCode_t)ctClientFuncPtrs[CTCLI_ctGetIsamErrorCode])
#define ctGetIsamFileNbr_C	(*(pctGetIsamFileNbr_t)ctClientFuncPtrs[CTCLI_ctGetIsamFileNbr])
#define ctGetSystemErrorCode_C	(*(pctGetSystemErrorCode_t)ctClientFuncPtrs[CTCLI_ctGetSystemErrorCode])
#define	CLIFIL_C		(*(pCLIFIL_t)ctClientFuncPtrs[CTCLI_CLIFIL])
#define	GETFIL_C		(*(pGETFIL_t)ctClientFuncPtrs[CTCLI_GETFIL])
#define	SETNODE_C		(*(pSETNODE_t)ctClientFuncPtrs[CTCLI_SETNODE])
#define	CLRFIL_C		(*(pCLRFIL_t)ctClientFuncPtrs[CTCLI_CLRFIL])
#define	TRANBEG_C		(*(pTRANBEG_t)ctClientFuncPtrs[CTCLI_TRANBEG])
#define	TRANRDY_C		(*(pTRANRDY_t)ctClientFuncPtrs[CTCLI_TRANRDY])
#define	TRANEND_C		(*(pTRANEND_t)ctClientFuncPtrs[CTCLI_TRANEND])
#define	TRANABT_C		(*(pTRANABT_t)ctClientFuncPtrs[CTCLI_TRANABT])
#define	TRANABTX_C		(*(pTRANABTX_t)ctClientFuncPtrs[CTCLI_TRANABTX])
#define	ADDREC_C		(*(pADDREC_t)ctClientFuncPtrs[CTCLI_ADDREC])
#define	ADDVREC_C		(*(pADDVREC_t)ctClientFuncPtrs[CTCLI_ADDVREC])
#define	TRANSAV_C		(*(pTRANSAV_t)ctClientFuncPtrs[CTCLI_TRANSAV])
#define	TRANRST_C		(*(pTRANRST_t)ctClientFuncPtrs[CTCLI_TRANRST])
#define	SPCLSAV_C		(*(pSPCLSAV_t)ctClientFuncPtrs[CTCLI_SPCLSAV])
#define	FRSREC_C		(*(pFRSREC_t)ctClientFuncPtrs[CTCLI_FRSREC])
#define	FRSVREC_C		(*(pFRSVREC_t)ctClientFuncPtrs[CTCLI_FRSVREC])
#define	LSTREC_C		(*(pLSTREC_t)ctClientFuncPtrs[CTCLI_LSTREC])
#define	LSTVREC_C		(*(pLSTVREC_t)ctClientFuncPtrs[CTCLI_LSTVREC])
#define	NXTREC_C		(*(pNXTREC_t)ctClientFuncPtrs[CTCLI_NXTREC])
#define	NXTVREC_C		(*(pNXTVREC_t)ctClientFuncPtrs[CTCLI_NXTVREC])
#define	PRVREC_C		(*(pPRVREC_t)ctClientFuncPtrs[CTCLI_PRVREC])
#define	PRVVREC_C		(*(pPRVVREC_t)ctClientFuncPtrs[CTCLI_PRVVREC])
#define	RWTREC_C		(*(pRWTREC_t)ctClientFuncPtrs[CTCLI_RWTREC])
#define	RWTVREC_C		(*(pRWTVREC_t)ctClientFuncPtrs[CTCLI_RWTVREC])
#define	DELREC_C		(*(pDELREC_t)ctClientFuncPtrs[CTCLI_DELREC])
#define	DELVREC_C		(*(pDELVREC_t)ctClientFuncPtrs[CTCLI_DELVREC])
#define	EQLREC_C		(*(pEQLREC_t)ctClientFuncPtrs[CTCLI_EQLREC])
#define	GTEREC_C		(*(pGTEREC_t)ctClientFuncPtrs[CTCLI_GTEREC])
#define	GTREC_C			(*(pGTREC_t)ctClientFuncPtrs[CTCLI_GTREC])
#define	LTEREC_C		(*(pLTEREC_t)ctClientFuncPtrs[CTCLI_LTEREC])
#define	LTREC_C			(*(pLTREC_t)ctClientFuncPtrs[CTCLI_LTREC])
#define	EQLVREC_C		(*(pEQLVREC_t)ctClientFuncPtrs[CTCLI_EQLVREC])
#define	GTEVREC_C		(*(pGTEVREC_t)ctClientFuncPtrs[CTCLI_GTEVREC])
#define	GTVREC_C		(*(pGTVREC_t)ctClientFuncPtrs[CTCLI_GTVREC])
#define	LTEVREC_C		(*(pLTEVREC_t)ctClientFuncPtrs[CTCLI_LTEVREC])
#define	LTVREC_C		(*(pLTVREC_t)ctClientFuncPtrs[CTCLI_LTVREC])
#define	SETOPS_C		(*(pSETOPS_t)ctClientFuncPtrs[CTCLI_SETOPS])
#define	CREIFILX8_C		(*(pCREIFILX8_t)ctClientFuncPtrs[CTCLI_CREIFILX8])
#define	PUTDODA_C		(*(pPUTDODA_t)ctClientFuncPtrs[CTCLI_PUTDODA])
#define	ctReplAgentSetCallback_C (*(pctReplAgentSetCallback_t)ctClientFuncPtrs[CTCLI_ctReplAgentSetCallback])
#define	REDVREC_C		(*(pREDVREC_t)ctClientFuncPtrs[CTCLI_REDVREC])
#define	SAVPCLR_C		(*(pSAVPCLR_t)ctClientFuncPtrs[CTCLI_SAVPCLR])
#define	CTUSERX_C		(*(pCTUSERX_t)ctClientFuncPtrs[CTCLI_CTUSERX])
#define	ctTransferFile_C	(*(pctTransferFile_t)ctClientFuncPtrs[CTCLI_ctTransferFile])
#define	ctOWNER_C		(*(pctOWNER_t)ctClientFuncPtrs[CTCLI_ctOWNER])
#define	ctSetOWNER_C		(*(pctSetOWNER_t)ctClientFuncPtrs[CTCLI_ctSetOWNER])
#define ctReplMasterControl_C	(*(pctReplMasterControl_t)ctClientFuncPtrs[CTCLI_ctReplMasterControl])
#define REGCTREE_C		(*(pREGCTREE_t)ctClientFuncPtrs[CTCLI_REGCTREE])
#define UNRCTREE_C		(*(pUNRCTREE_t)ctClientFuncPtrs[CTCLI_UNRCTREE])
#define ctThrdAttach_C		(*(pctThrdAttach_t)ctClientFuncPtrs[CTCLI_ctThrdAttach])
#define ctThrdDetach_C		(*(pctThrdDetach_t)ctClientFuncPtrs[CTCLI_ctThrdDetach])
#define GETCTREE_C		(*(pGETCTREE_t)ctClientFuncPtrs[CTCLI_GETCTREE])
#define ctSETCLIENTID_C		(*(pctSETCLIENTID_t)ctClientFuncPtrs[CTCLI_ctSETCLIENTID])
#define	ctdbGetCtreeOWNER_C	(*(pctdbGetCtreeOWNER_t)ctClientFuncPtrs[CTCLI_ctdbGetCtreeOWNER])
#define	ctdbSetCtreeOWNER_C	(*(pctdbSetCtreeOWNER_t)ctClientFuncPtrs[CTCLI_ctdbSetCtreeOWNER])
#define	OPNFILX_C		(*(pOPNFILX_t)ctClientFuncPtrs[CTCLI_OPNFILX])
#define	PUTIFILX8_C		(*(pPUTIFILX8_t)ctClientFuncPtrs[CTCLI_PUTIFILX8])
#define	AVLFILNUM_C		(*(pAVLFILNUM_t)ctClientFuncPtrs[CTCLI_AVLFILNUM])
#define	CLSFIL_C		(*(pCLSFIL_t)ctClientFuncPtrs[CTCLI_CLSFIL])
#define	SetXtdFileOpenMode_C	(*(pSetXtdFileOpenMode_t)ctClientFuncPtrs[CTCLI_SetXtdFileOpenMode])
#define RWTPREC_C		(*(pRWTPREC_t)ctClientFuncPtrs[CTCLI_RWTPREC])
#define ctConnStateAlloc_C	(*(pctConnStateAlloc_t)ctClientFuncPtrs[CTCLI_ctConnStateAlloc])
#define ctConnStateFree_C	(*(pctConnStateFree_t)ctClientFuncPtrs[CTCLI_ctConnStateFree])
#define ctConnStateGet_C	(*(pctConnStateGet_t)ctClientFuncPtrs[CTCLI_ctConnStateGet])
#define LKISAM_C		(*(pLKISAM_t)ctClientFuncPtrs[CTCLI_LKISAM])
#define GETNAM_C		(*(pGETNAM_t)ctClientFuncPtrs[CTCLI_GETNAM])
#define	ctReplAgentSetState_C	(*(pctReplAgentSetState_t)ctClientFuncPtrs[CTCLI_ctReplAgentSetState])
#define	ctReplAgentSetArgs_C	(*(pctReplAgentSetArgs_t)ctClientFuncPtrs[CTCLI_ctReplAgentSetArgs])
#define	SETFLTR_C		(*(pSETFLTR_t)ctClientFuncPtrs[CTCLI_SETFLTR])
#define ctRecordUpdateCallbackControl_C (*(pctRecordUpdateCallbackControl_t)ctClientFuncPtrs[CTCLI_ctRecordUpdateCallbackControl])
#define SWTCTREE_C		(*(pSWTCTREE_t)ctClientFuncPtrs[CTCLI_SWTCTREE])
#define ctReplAgentOp_C		(*(pctReplAgentOp_t)ctClientFuncPtrs[CTCLI_ctReplAgentOp])
#define ctSetCommProtocolOption_C (*(pctSetCommProtocolOption_t)ctClientFuncPtrs[CTCLI_ctSetCommProtocolOption])
#define ctWorkerThrdAttach_C	(*(pctWorkerThrdAttach_t)ctClientFuncPtrs[CTCLI_ctWorkerThrdAttach])
/* <NEW_ENTRY>
#define	ctNewAPIFunction_C	(*(pctNewAPIFunction_t)ctClientFuncPtrs[CTCLI_ctNewAPIFunction])
*/

/*
** c-tree Plus API function names,
** used to retrieve function addresses from c-tree DLL or shared library.
*/

extern pTEXT	ctClientFuncNames[CTCLI_TOTAL];

#endif /* ctFeatTRANREPL */

/* structure for replication state table record format */
typedef struct {
	TEXT	unqid[UNQIDLEN]; /* replication agent unique id */
	LONG	readlognum; /* last read transaction log number */
	ULONG	readlogpos; /* last read offset in transaction log */
} replocst_t;

/* Replication record update check status codes: */
typedef enum rcustt {
	RCU_MATCHOLD = 1, /* current record on target matches old image from source */
	RCU_MATCHNEW = 2, /* current record on target matches new image from source */
	RCU_CONFLICT = 3  /* current record on target differs from old & new images */
} RCUSTT;

typedef struct rfncstt {
	ULONG	cnt;	/* function call count				*/
	LONG8	tim;	/* high resolution elapsed function time	*/
} ctRFSTT, ctMEM * pctRFSTT;

#define RFSTTvers_V01	1 /* replication agent file stats version 1	*/
#define	RFSTTvers_CUR	RFSTTvers_V01 /* current version */

#define RRSYNCvers_V01	1 /* replication agent resync version 1	*/
#define	RRSYNCvers_CUR	RRSYNCvers_V01 /* current version */

/* Resync ID length */
#define RSYNCIDLEN	22
#define RSYNCFNAME	"FRESYNCDT.FCS"

/* Replication agent (ctreplagent.cfg) exception_logging options: */
#define RXPLOGoff	0x00000001	/* off: Exception logging is disabled */

/* Replication agent external library actions: */
typedef enum rxact {
	RXA_DEFAULT	= 0,	/* Perform the default action for this event. */
	RXA_SKIP	= 1,	/* Skip the default action for this event. */
	RXA_SHUTDOWN	= 2	/* Shut down the replication agent. */
} RXACT;

typedef struct logshipstate_t {
	TEXT	instname[IDZ]; /* name of this persistent instance */
	ctLOGP	logShipPosition; /* write position in log */
} LSHPSTT, *pLSHPSTT;

/* the name of the log ship state data file without extension */
#define LOG_SHIP_STATE_DATA_FILENAME_BASE "REPLOGSHIPDT"

/* the name of the log ship state data file */
#define LOG_SHIP_STATE_DATA_FILENAME "REPLOGSHIPDT.FCS"
/* the name of the log ship state index file */
#define LOG_SHIP_STATE_INDEX_FILENAME "REPLOGSHIPIX.FCS"

/* value used to call scnlog() for ctReplSetPosByTransactionId() function */
#define SCNLOG_SETPOSBYTRANSACTIONID (pTEXT)3

/* the size of a key in the transaction state index */
#define REPL_TRAN_STATE_INDEX_KEY_LENGTH	(2 * sizeof(LONG) + sizeof(LONG8))

/* a buffer used to hold a transaction state key value */
typedef TEXT TRAN_STATE_KEY[REPL_TRAN_STATE_INDEX_KEY_LENGTH];

/*^***********************************/
/*
** Definitions for sync replication agent table
*/

/* size of sync repl agent table record, version 1 */
#define ctRSDT1_RECLEN_V01	UNQIDLEN

#ifdef ctFeatREPLICAT_SYNC2

/* size of sync repl agent table record, version 2 */
#define ctRSDT1_RECLEN_V02	(UNQIDLEN + sizeof(LONG) + MAX_SERVER_NAME)
/* size of sync repl agent table record, current version */
#define ctRSDT1_RECLEN_CUR	ctRSDT1_RECLEN_V02

#else

/* size of sync repl agent table record, current version */
#define ctRSDT1_RECLEN_CUR	ctRSDT1_RECLEN_V01

#endif

/* replication agent options that we persist in the AgentOptions field of the REPLSYNCDT1.FCS record */
typedef enum replAgentPersistOptions_t {
	REPLAGENT_PERSIST_OPTION_SYNCHRONOUS = 0x00000001 /* replication agent is synchronous */
} REPLAGENT_PERSIST_OPTIONS;

/*^***********************************/
/*
** Definitions for sync replication file/agent relationship table
*/

/* Size of version 1 record. */
#define ctRSDT2_RECLEN_V01	(2 * sizeof(ULONG))
/* Size of current version record. */
#define ctRSDT2_RECLEN_CUR	ctRSDT2_RECLEN_V01

#ifdef CTPERM

#ifdef ctSRVR

/* sync repl state API handle */
typedef struct ctsrshnd {
	FILNO	agentDatno; /* data file number for agent data file */
	FILNO	fileAgentDatno; /* data file number for file-agent data file */
	NINT	sOWNR; /* task ID of the calling connection */
} ctSRSHND, *pctSRSHND;

static NINT ctSRSInit(pctSRSHND *ppsrsHandle);
static void ctSRSFinal(pctSRSHND *ppsrsHandle);
static NINT ctSyncReplAgentListGetHandle(cpTEXT agentId,pULONG pagentHandle,NINT sOWNR);
static NINT ctSRSAddFileAgent(pctSRSHND psrsHandle,cpTEXT DataFileName,cpTEXT AgentId,NINT ReplMode);
static NINT ctSRSGetFileAgentRecord(pctSRSHND psrsHandle,cpTEXT DataFileName,ppTEXT precbuf,pVRLEN preclen);

#ifdef ctFeatREPLAGENT_FILE_FILTER

/* an entry in the list of replication agent file filters */
typedef struct replAgentFileFilter_t {
	ppRBHL	fltbhl;		/* Pointer to filename filter hash bins	*/
	pRTCE	fltfrs;		/* First entry in specific file name hash table */
	pRTCE	fltlst;		/* Last entry in specific file name hash table */
	ppRBHL	wcdbhl;		/* Pointer to filename filter hash bins	*/
	pRTCE	wcdfrs;		/* First entry in wildcard file name hash table */
	pRTCE	wcdlst;		/* Last entry in wildcard file name hash table */
	struct replAgentFileFilter_t *next; /* pointer to next entry in list */
	struct replAgentFileFilter_t *prev; /* pointer to previous entry in list */
	pTEXT	xmlFilter;	/* The xml filter */
	UINT	flthbins;	/* Number of hash bins for filename filter */
	ULONG	agentHandle; /* unique integer value assigned to this agent */
	REPL_FILE_FILTER_PURPOSE purposes; /* purposes of the filter */
	TEXT	agentId[UNQIDLEN]; /* replication agent unique id */
} REPLAGENT_FILE_FILTER, *pREPLAGENT_FILE_FILTER;

/* a list of replication agent file filters */
typedef struct replAgentFileFilterList_t {
	pREPLAGENT_FILE_FILTER head; /* pointer to first entry in list */
	ULONG numberOfEntries; /* total number of entries in list */
	ULONG numberOfCreateFileEntries; /* number of entries in list for file create */
	ULONG numberOfReadLogEntries; /* number of entries in list for read log */
	ULONG numberOfSyncCommitEntries; /* number of entries in list for sync commit */
	ULONG numberOfOpenFileEntries; /* number of entries in list for file open */
} REPLAGENT_FILE_FILTER_LIST, pREPLAGENT_FILE_FILTER_LIST;

/* replication agent handle list */
typedef struct replAgentHandleList_t {
	pULONG	agentHandleArray; /* array of agent handles */
	NINT	numberOfAgentHandles; /* number of entries in agent handle array */
	NINT	sizeOfAgentHandleArray; /* allocated size of agent handle array */
} REPLAGENT_HANDLE_LIST, *pREPLAGENT_HANDLE_LIST;

extern NINT checkReplAgentFileFilterLists(cpTEXT fileName, REPL_FILE_FILTER_PURPOSE purposes, pREPLAGENT_HANDLE_LIST pReplAgentHandleList, pNINT pResult, NINT sOWNR);
extern NINT ctReplAgentFileFilterListInit(void);
extern void ctReplAgentFileFilterListFinal(void);
extern NINT ctReplAgentFileFilterListAdd(cpTEXT agentId, cpTEXT filterText, TEXT replaceExisting);
extern void ctReplAgentFileFilterListRemoveEntry(pREPLAGENT_FILE_FILTER pListEntry, NINT sOWNR);
extern NINT ctReplAgentFileFilterAddEntry(pREPLAGENT_FILE_FILTER pHashList, pTEXT filnam,RFLSTT replstatus,NINT update);
extern NINT ctReplAgentFileFilterWCAddEntry(pREPLAGENT_FILE_FILTER pHashList, pTEXT filnam, pTEXT pRegularExpression, RFLSTT replstatus);
static NINT ctSRSRemoveAgentFileFilter(pctSRSHND psrsHandle,cpTEXT AgentId);

#endif /* ctFeatREPLAGENT_FILE_FILTER */

extern NINT initReplConnectHandle(struct thrdgv *lctgv);
extern void freeReplConnectHandle(struct thrdgv *lctgv);
static NINT ctSyncReplAgentListAdd(cpTEXT agentId,REPLAGENT_PERSIST_OPTIONS agentOptions,cpTEXT agentServerName,pULONG pagentHandle,NINT sOWNR);

#endif /* ctSRVR */

#endif /* CTPERM */

#endif /* ~ctREPLHonce */

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function prototypes
 */

extern ctCONV  NINT  ctDECL ctReplSetFileStatus(pctCNXH pcnxhnd, pTEXT filnam, NINT status);
extern ctCONV  NINT  ctDECL ctReplGetFileStatus(pctCNXH pcnxhnd, pTEXT filnam, pNINT pstatus);
extern ctCONV  NINT  ctDECL ctReplSetPosByTime(pctCNXH pcnxhnd, pTEXT tstamp);
extern ctCONV  NINT  ctDECL ctReplSetPosByLogPos(pctCNXH pcnxhnd, pctLOGP plogpos);
extern ctCONV  NINT  ctDECL ctReplSetPosByTransactionId(pctCNXH pcnxhnd, ULONG8 transactionId);
extern ctCONV  NINT  ctDECL ctReplGetPos(pctCNXH pcnxhnd, pctLOGP pcurpos);
extern ctCONV  NINT  ctDECL ctReplGetNextChange(pctCNXH pcnxhnd, pctCHGB pchgbuf, NINT timeout);
extern ctCONV  NINT  ctDECL ctReplGetNextChangeDirect(NINT taskid,pctLOGP plogpos,pctCHGB pchgrec,NINT timeout,allocFunc_t allocFunc,freeFunc_t freeFunc);
extern ctCONV  NINT  ctDECL ctReplReadLogData(pctCNXH pcnxhnd, pctRDLG pReadLogData, NINT timeout);
extern ctCONV  NINT  ctDECL ctReplCleanupTranStateKeys(FILNO keyno, pctLOGP pLastCommitPosition, pNINT pNumDeleted);
extern ctCONV  NINT  ctDECL ctReplGetFileName(pctCNXH pcnxhnd, ctFLID fileid, pTEXT filnam, NINT bufsiz);
extern ctCONV  NINT  ctDECL ctReplReadFirstRecord(pctCNXH pcnxhnd, pctFILH pfilhnd, pctCHGB pchgbuf);
extern ctCONV  NINT  ctDECL ctReplReadNextRecord(pctCNXH pcnxhnd, pctFILH pfilhnd, pctCHGB pchgbuf);
extern ctCONV  NINT  ctDECL ctReplReadRecordByKey(pctCNXH pcnxhnd, pctFILH pfilhnd, pTEXT keyval, pctCHGB pchgbuf);
extern ctCONV  NINT  ctDECL ctReplInit(VOID);
extern ctCONV  NINT  ctDECL ctReplTerm(VOID);
extern ctCONV  NINT  ctDECL ctReplInitXtd(pctRASTT prepstt);
extern ctCONV  NINT  ctDECL ctReplTermXtd(pctRASTT prepstt);
extern ctCONV  NINT  ctDECL ctReplConnect(pctCNXI pcnxinf, pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplDisconn(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplOpenFile(pctCNXH pcnxhnd, pTEXT filnam, pctFILH pfilhnd);
extern ctCONV  NINT  ctDECL ctReplCloseFile(pctCNXH pcnxhnd, pctFILH pfilhnd);
extern ctCONV  NINT  ctDECL ctReplChangeRecord(pctCNXH pcnxhnd, pctFILH pfilhnd, pctCHGB pchgbuf);
extern ctCONV  NINT  ctDECL ctReplTranCtl(pctCNXH pcnxhnd, pctCHGB pchgbuf);
extern ctCONV  pVOID ctDECL ctReplAllocMem(LONG memsiz);
extern ctCONV  VOID  ctDECL ctReplFreeMem(pVOID pntr);
extern ctCONV  NINT  ctDECL ctReplPersistMinLog(pctCNXH pcnxhnd, pTEXT data, NINT mode);

extern ctCONV  NINT  ctDECL ctReplCheckExcludedFiles(cpTEXT filnam);
extern ctCONV  NINT  ctDECL ctReplSetFileFilter(pctCNXH pcnxhnd,pTEXT fltnam,pTEXT errbuf,LONG errbufsiz);
extern ctCONV  NINT  ctDECL ctReplCheckFileFilter(pctCNXH pcnxhnd, pTEXT ifilelist, pTEXT ofilelist, LONG bufsiz);
extern ctCONV  NINT  ctDECL ctReplFileFilterListAdd(pctCNXH pcnxhnd,pTEXT filnam,RFLSTT replstatus, NINT update);
extern ctCONV  NINT  ctDECL ctReplFileFilterListDelete(pctCNXH pcnxhnd,pTEXT filnam);
extern ctCONV  NINT  ctDECL ctReplFileFilterListGet(pctCNXH pcnxhnd,pTEXT filnam,ppFFLTI ppfltinf);
extern ctCONV  NINT  ctDECL ctReplFileFilterListCreate(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplFileFilterListDestroy(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplFileFilterWCListAdd(pctCNXH pcnxhnd,pTEXT filnam,pTEXT pRegularExpression,RFLSTT replstatus);
extern ctCONV  NINT  ctDECL ctReplFileFilterWCListDelete(pctCNXH pcnxhnd,pTEXT filnam);
extern ctCONV  NINT  ctDECL ctReplFileFilterWCListGet(pctCNXH pcnxhnd,pTEXT filnam,ppWCFFLTI ppfltinf);
extern ctCONV  NINT  ctDECL ctReplFileFilterWCListCreate(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplFileFilterWCListDestroy(pctCNXH pcnxhnd);

extern ctCONV  NINT  ctDECL ctReplFileListCreate(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplFileListDestroy(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplFileListAdd(pctCNXH pcnxhnd, pctFILH pfilhnd);
extern ctCONV  NINT  ctDECL ctReplFileListDelete(pctCNXH pcnxhnd, pctFILH pfilhnd);
extern ctCONV  NINT  ctDECL ctReplFileListGet(pctCNXH pcnxhnd, ULONG dattfl, ppctFILH pfilhnd);
extern ctCONV  NINT  ctDECL ctReplApplyOpsXtd(pctCNXH psrccnxhnd, pctCNXH ptgtcnxhnd, pctCHGB pchgbuf, pLONG pchgsuc, pLONG pchgerr, praSTAT ras, pVOID prepstt);
extern ctCONV  NINT  ctDECL ctReplTranCmtListCreate(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplTranCmtListDestroy(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplTranCmtListAdd(pctCNXH pcnxhnd, pctCHGB pchgbuf);
extern ctCONV  NINT  ctDECL ctReplTranCmtGetOldestAck(pctCNXH pcnxhnd, pctCHGB pchgbuf);
extern ctCONV  NINT  ctDECL ctReplTranCmtExists(pctCNXH pcnxhnd,pNINT pexists);
extern ctCONV  NINT  ctDECL ctReplTranCmtListRemove(pctCNXH pcnxhnd, pctCHGB pchgbuf, pctRASTT prepstt);
extern ctCONV  NINT  ctDECL ctReplOpListSetCmtAck(pctCNXH pcnxhnd, pctCHGB pchgbuf);
#ifdef ctREPL_FULL_API
extern         NINT  ctDECL ictReplSwitchInst(pctCNXH pcnxhnd, NINT mode);
#endif
extern ctCONV  NINT  ctDECL ctReplAgentOp(NINT opcd, pTEXT ibuf, VRLEN ilen, pTEXT obuf, pVRLEN olen);
#if defined(ctREPLAGENT) && defined(ctPortWIN32) && defined(ctFeatREPLAGENTdll)
#define ctCONVr __declspec(dllexport)
#else
#define ctCONVr
#endif
extern ctCONVr NINT         ctReplAgentMain(pctRASTT prepstt);
extern ctCONVr NINT         ctRAStartDatabaseEngine(pctRASTT prepstt);
extern ctCONVr NINT         ctRAStopDatabaseEngine(pctRASTT prepstt);
extern ctCONVr NINT         ctReplAgentSetConfigOption(NINT kw, pTEXT kv, pctRASTT prepstt, NINT lineno, pTEXT cfgfile);
extern ctCONVr NINT         ctRAReadConfigFile(pTEXT cfgfile, pctRASTT prepstt);

#ifdef ctFeatTRANREPL
#include "ctparm.h"
#include "ctstrc.h"
extern         NINT         ctTranReplClientInit(NINT model, pctRASTT prepstt);
extern         NINT         ctTranReplClientTerm(VOID);
extern         NINT         ctTranReplConnectToMasterServer(FILNO fils, COUNT userprof, pTEXT userid, pTEXT userword, pTEXT servname);
extern         NINT         ctTranReplFileIsReplica(pTEXT filnam, pTEXT mstnam, NINT buflen);
extern         NINT         ctTranReplInit(cpTEXT mapfile);
extern         NINT         ctTranReplOpenFile(pIFILBLK pifilblk, pCTFILE dnum, FILNO ufilno);
extern         NINT         ctTranReplReReadMasterRecord(pCTFILE dnum, FILNO datno, FILNO keyno, FILNO mkeyno, NINT sOWNR);
extern         NINT         ctTranReplSetNodeName(VOID);
#endif

extern ctCONV  NINT  ctDECL ctReplFileNameListCreate(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplFileNameListDestroy(pctCNXH pcnxhnd);
extern ctCONV  NINT  ctDECL ctReplFileNameListAdd(pctCNXH pcnxhnd, pctFILH pfilhnd);
extern ctCONV  NINT  ctDECL ctReplFileNameListDelete(pctCNXH pcnxhnd, pctFILH pfilhnd);
extern ctCONV  NINT  ctDECL ctReplFileNameListGet(pctCNXH pcnxhnd, pTEXT filnam, ppctFILH ppfilhnd);
extern         NINT         ictReplReadLogDataSRV(pctCNXH pcnxhnd, pctRDLG pReadLogData, NINT timeout);
extern         NINT         ctReplUpdateLogShipList(pLSHPSTT pLogShipState);
extern         void         ctReplSetTranStateKeyValue(TRAN_STATE_KEY keyValue, pctLOGP pCommitPosition,LONG8 transactionNumber);
extern         void         ctReplGetTranStateKeyValue(TRAN_STATE_KEY keyValue, pctLOGP pCommitPosition,pLONG8 pTransactionNumber);

/* Internal function prototypes. */
ctCONV  NINT  ctDECL ictReplSetPosByLogPos(pctCNXH pcnxhnd, pctLOGP plogpos);
ctCONV  NINT  ctDECL ictReplSetPosByTime(pctCNXH pcnxhnd, pTEXT tstamp);
ctCONV  NINT  ctDECL ictReplSetPosByTransactionId(pctCNXH pcnxhnd, ULONG8 transactionId);
ctCONV  NINT  ctDECL ictReplGetNextChange(pctCNXH pcnxhnd, pctCHGB chgbuf, NINT timeout);
ctCONV  NINT  ctDECL ictReplReadLogData(pctCNXH pcnxhnd, pctRDLG pReadLogData, NINT timeout);
ctCONV  NINT  ctDECL ictReplGetFileName(pctCNXH pcnxhnd, ctFLID fileid, pTEXT filnam, NINT bufsiz);
ctCONV  NINT  ctDECL ictReplPersistMinLog(pctCNXH pcnxhnd, pTEXT data, NINT mode);
ctCONV  NINT  ctDECL ictReplSetFileFilter(pctCNXH pcnxhnd, pTEXT fltnam,pTEXT errbuf,LONG errbufsiz);
ctCONV  NINT  ctDECL ictReplCheckFileFilter(pctCNXH pcnxhnd, pTEXT ifilelist, pTEXT ofilelist, LONG bufsiz);
extern NINT replApplyFileNameConversions(pctCNXH pcnxhnd, NINT replopts, TEXT filnam[MAX_NAME]);

#ifdef __cplusplus
}
#endif

#endif /* ~ctREPLH */

/* end of ctrepl.h */
