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
 *      Copyright (C) Dharma Systems Inc.        1988-2002. 
 *      Copyright (C) Dharma Systems (P) Ltd.    1988-2002. 
 * 
 *      This Module contains Proprietary Information of 
 *      Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 *      and should be treated as Confidential. 
 */

#ifndef _CTLOGGER_H_
#define _CTLOGGER_H_

#define CTPERM
#ifdef __cplusplus
extern "C" {
#endif
#include "ctstdr.h"
#include "ctoptn.h"
#include "ctlogids.h"
#ifdef __cplusplus
}
#endif

#define ERR_UNUSED  0 /* not specified */
 /*^****************************************************************************\
 *
 *   There are essential use cases for monitoring and alerting.
 *   Each aligns to a functional role in an enterprise.
 *   A user may have one or more of these functional roles.
 *   We call these audiences.
 *   a log entry could apply to multiple audiences.
 *
 *   Defining "audience" bitmask here.
 *   When adding a new logging entry consider, 
 *   "Who does this message provide meaningful information to?"
 *
 \*****************************************************************************/
#define CTLOG_AUDIENCE_OPS 0x01 /* Alerting (performance, imminent outages, etc.) */
#define CTLOG_AUDIENCE_DBA       0x02 /* Database Troubleshooting (permissions, SQL performance) */
#define CTLOG_AUDIENCE_DEVELOPER 0x04 /* Application debugging (custom messages from client application / function monitor) */
#define CTLOG_AUDIENCE_SECURITY  0x08 /* Security auditing (authentication, etc.) */
#define CTLOG_AUDIENCE_FAIRCOM   0x10 /* Database Troubleshooting (transaction processing, internal debugging, diagnostic) */
#define CTLOG_AUDIENCE_DEBUG     0x20 /* Internal Faircom development, specific trouble shootign requiring special gens */

/* audience excluding particular cases: faircom debugging and customer application entries*/
#define CTLOG_AUDIENCE_EVERYONE (CTLOG_AUDIENCE_OPS|CTLOG_AUDIENCE_DBA|CTLOG_AUDIENCE_SECURITY| CTLOG_AUDIENCE_FAIRCOM) 
/* all of the  audience */
#define CTLOG_AUDIENCE_ALL (CTLOG_AUDIENCE_EVERYONE | CTLOG_AUDIENCE_DEVELOPER | CTLOG_AUDIENCE_DEBUG)

#define CTLOG_AUDIENCE_INTERNAL (CTLOG_AUDIENCE_FAIRCOM|CTLOG_AUDIENCE_DEBUG)
#define CTLOG_AUDIENCE_DEFAULT (CTLOG_AUDIENCE_OPS|CTLOG_AUDIENCE_FAIRCOM)
#define CTLOG_AUDIENCE_ADMIN	(CTLOG_AUDIENCE_OPS|CTLOG_AUDIENCE_DBA)
#define CTLOG_AUDIENCE_DEV	(CTLOG_AUDIENCE_FAIRCOM|CTLOG_AUDIENCE_DEVELOPER)

/*^****************************************************************************\
 *
 *   log category 
 *
 *   Defining the database subsytem related to the message.
 *
 *
\*****************************************************************************/
typedef enum
{
	CTLOG_CATEGORY_0 = 0, /* undefined should not be used.*/
	CTLOG_CATEGORY_CTFILE,  /* File Management subsystem */
	CTLOG_CATEGORY_CTINDEX, /* Ctree Indexing subsystem */
	CTLOG_CATEGORY_TRAN, /* Transaction Management subsystem */
	CTLOG_CATEGORY_REPL, /* Replication subsystem */
	CTLOG_CATEGORY_TRANREPL, /* Client Side Synchronous Replication */
	CTLOG_CATEGORY_RECOVER, /* Transaction recovery subsystem */
	CTLOG_CATEGORY_DIAG, /* diagnostic subsystem (Most DIAGNOSTICS messages probably fall under a more specific entry) */
	CTLOG_CATEGORY_MIRROR, /* File Mirroring subsystem */
	CTLOG_CATEGORY_COMM, /* Communication subsystem */
	CTLOG_CATEGORY_DDMP, /* Dynamic Dump Backup subsystem */
	CTLOG_CATEGORY_VSS, /* VSS Backup subsystem */
	CTLOG_CATEGORY_SYSTEM, /* OS or filesystem */
	CTLOG_CATEGORY_CONFIG, /* Database configuration. (compile time, keywords, environment, etc) */
	CTLOG_CATEGORY_INIT, /* Database Startup */
	CTLOG_CATEGORY_THREAD, /* Thread management subsystem */
	CTLOG_CATEGORY_GENERAL, /* possibly multiple subsystems */
	CTLOG_CATEGORY_NONE, /* unclassified */
	CTLOG_CATEGORY_SHUTDOWN, /* Shutdown related messages */
	CTLOG_CATEGORY_QUIET,	/* ctQUIET */
	CTLOG_CATEGORY_CACHE,	/* caching subsystem */
	CTLOG_CATEGORY_LICENSE, /* licensing */
	CTLOG_CATEGORY_AUTH,    /* Authentication and security */
	CTLOG_CATEGORY_MEM,	/* memory management subsystem */
	CTLOG_CATEGORY_IO,	/* IO subsystem */
	CTLOG_CATEGORY_LOCK,	/* Lock management subsystem */
	CTLOG_CATEGORY_RPC,	/* Marshalling/Unmarshalling */


	CTLOG_CATEGORY_SQLMONITOR, /* SQL Monitor output */
	CTLOG_CATEGORY_FMONITOR, /* Function Monitor output */
	CTLOG_CATEGORY_LASTONE /* last category. used jsut for checking */
	/* when adding new categories, remember to update the category string array in ctlogent.cpp*/
} CTLOG_CATEGORY;

/*
 *  CTLOG_ACTION 
 *  What is the suggested action to take when encountering this message?
 */
typedef enum
{
  ACTION_UNDEF,   /* no action defined */
  ACTION_NONE,    /* No action needed for this message. */
  ACTION_FAIRCOM, /* Please contact technical support with the contents of the message. */
  ACTION_REBUILD, /* File integrity problem detected. Rebuild the specified file or restore from backup. Contact Faircom*/
  ACTION_REBUILD_OPTIONAL, /* An index rebuild may improve performance or recover some wasted disk space */
  ACTION_REBUILD_PURGE, /* Duplicate keys encountered during index rebuild, indicating likely data corruption.  Faircom recommends restoring from a good backup. Otherwise, file contents should be reviewed. */
  ACTION_REBUILD_INDEX, /* The index definition has changed and must be rebuilt. */
  ACTION_COMPACT, /* A file compact can recover some wasted disk space */
  ACTION_NODEDELAY_ZERO, /* Reduce NODE_DELAY configuration option. Zero is preferred.  */
  ACTION_MESG, /* Review the message. The message contains actionable information. Contact Support for assistance. */ 
  ACTION_MEMORY, /* Memory allocation failed. Check process and system memory usage and limits. */
  ACTION_STACKDUMP, /* Stack dump created.  Contact technical support with message and stack dump */
  ACTION_LICENSE, /* upgrade server license */
  ACTION_KEYWORD, /* Review configurations in ctsrvr.cfg */
  ACTION_FILESYSTEM, /* Likely IO failure.  Check disk space or system error logs */ 
  ACTION_USER, /* unknown user/application defined message  */
  ACTION_BAD_LOG, /* Transaction logs contain inconsistencies.  Restore to backup */
  ACTION_BAD_LOG_VERSION, /* Transaction logs contain unsupported features.  Were they created by a newer server version? */
  ACTION_BAD_FILE_VERSION, /* File uses unsupported features.  Were they created by a newer server version? */
  ACTION_LOG_READER_NO_LOGS, /* A transaction log reader (such as for replication or deferred indexing) has fallen too far behind and may need to be resync'd.  */
  ACTION_FIXEDLOG, /* Don't use the FIXED_LOG_SIZE keyword. */
  ACTION_DUMP_SCRIPT, /* review and correct the dynamic dump backup script contents and/or file permissions */
  ACTION_DUMP_REBUILD, /* Non-transaction file updated during backup. After restore the index must be rebuilt */
  ACTION_TOOMANY_USERS, /* Reduce the number of active server connections */
  ACTION_TRY_AGAIN, /* Retry later */
  ACTION_MOREFILES, /* Raise the FILES limit */
  ACTION_TFLSTT_LOOP, /* Potential live-locked task, but may be due to an unusual system delay. If the message repeats without resolution, killing the user/task id generating the message may resolve the problem. */
  ACTION_DNODE_ERROR, /* Some indexes/variable length data files may have some wasted space.  Rebuild/Compact will reclaim this immediately. This space may be eventually reclaimed without special action. Contact Faircom if frequent.*/
  ACTION_REPL_ENABLE, /* replication was not enabled for file, it may need to be manually enabled */
  ACTION_RENAME_COLLISION, /* Rename failure, does target name already exist?  Does directory structure exist? */
  ACTION_DMAP, /* DMAP_ERR - Index associated with multiple data files.  Check for incorrect IFIL pfilnam or aidxnam with paths. Note that IFIL definition may reside in data file and/or application code.  Index may be corrupt. */
  ACTION_NETWORKDRIVE, /* Opening this file via different names cannot be detected and could result in data corruption or other undefined behavior */
  ACTION_CTREEVERSION, /* Feature requires a different version of ctree */
  ACTION_NON_TRAN, /* non-ctTRNLOG files.  Data loss & corruption is possible without further action */
  ACTION_FAIRCOM_FCS, /* FAIRCOM.FCS may be damaged, contact Faircom.  Restore from backup, rebuild, or recreate this file */
  ACTION_NETWORK, /* Check the hosts networking configuration */
  ACTION_SERVERSTART, /* Startup troubleshooting. Is a server running? Are system resources available? Trace for errors. */
  ACTION_DUPFIDD, /* Duplicate ctree file id.  The file appears to be a copy of an already open file.  Update the ctree file id after duplication to avoid this. */
  ACTION_TRANOVERFLOW, /* Reset all file Transaction watermarks */
  ACTION_PURGE_ACTIVE, /* Attempt to purge an inuse partition.  Wait for all usage of partition to end */
  ACTION_REBUILD_MODE, /* Invalid rebuild options,  modify the request  */
  ACTION_PLUGIN_DEV, /* Error with the plugin.  Contact the plugin developer (Faircom?)*/
  ACTION_FWD_START, /* Forward roll starting point (usually specified by file S0000000.FCS or S0000001.FCS) is invalid.  Review the recovery procedures */
  ACTION_UNEXPECTED_LOG, /* unexpected transaction log. Unrelated old log?  Corrupted log? Removing this file may resolve the problem */
  ACTION_COMPACT_RECOVERY, /* interrupted Compact detected in recovery.  Compact should be re-run on the original files */
  ACTION_NO_RP_ROLLBACK, /* DELAYED_DURABILITY enabled but unable to rollback to RP at recovery.  The database recovered with relaxed ACID semantics, but without the planned rollback to an application defined state.  Database level transactions are in a consistent state, but Business level transactions could be inconsistent.  A manual rollback is possible. */
  ACTION_RECOVERY_FAILURE, /* Contact Faircom.  Save copies of files and transaction logs for analysis.  Restore to backup */
  ACTION_TRAN_REPL_LOAD, /* Failed to load client module for transactional replication.  If you are not using transactional replication model this can be ignored. */
  ACTION_MUSR_ERR, /* check CONNECTIONS/USERS keywords in ctsrvr.cfg and licensed user limits. Contact Faircom for assistance. */
  ACTION_LOOP_DELAY, /* This delay should self-resolve.  Contact Faircom if frequent or excessive */ 
   
} CTLOG_ACTION;

/* 
 * CTLOG_SEVERITY
 * How important is this message?
 */
typedef enum {
	CTLOG_LEVEL_UNDEF = 0, /* undefined should not be used.*/
	CTLOG_LEVEL_SERVICEDOWN = 1, /* Denial of service, feature not available (for instance server shutdown, communication protocol not started or stopped, missing DLL...)*/
	CTLOG_LEVEL_DEGRADED = 2, /* service degraded may end-up in DOS soon (for instance disk low, error writing to disk [that does not cause a server shutdown]..) */
	CTLOG_LEVEL_ERROR, /* localized degradation or failure (table or index unavailable), or unexpected situation */
	CTLOG_LEVEL_WARN, /* service warning, situation that may or may not be a concern like client abruptly disconnected, internal unexpected situation that we where able to resolve...*/
	CTLOG_LEVEL_WARN_PERF, /* performance warning */
	CTLOG_LEVEL_INFO_HIGH, /* higher priority informative message */
	CTLOG_LEVEL_INFO, /* informative message */
	CTLOG_LEVEL_DEBUG, /* debugging/diagnostic message */
	CTLOG_LEVEL_LASTONE/* last level. used jsut for checking */
} CTLOG_SEVERITY;


/*
 * CTLOG_ERRTYPE
 * specifies interpretation of error codes.
 */
typedef enum {
	ERRTYPE_NONE, /* no value */
	ERRTYPE_CTREE,  /* ctree or ctdb error */
	ERRTYPE_CRT, /* c-runtime error (errno) */
	ERRTYPE_SQL, /* c-treeSQL error code */
	ERRTYPE_SAADMIN, /* SA_ADMIN error code (cthelp.h) */
	ERRTYPE_SYSTEM, /* system error (e.g. errno, GetLastError()). Negative values may be special ctree values */
	ERRTYPE_NUMBER, /* Just a number, unclassified */
	ERRTYPE_LOC,    /* location identifier */
	ERRTYPE_IDXMEM, /* Index member number (relative number) */
	ERRTYPE_TEXT, /* no value, but the message contains an error */
	ERRTYPE_SSL, /* OPENSSL error code */
	ERRTYPE_AWS, /* AWS or CTAWS error*/
	ERRTYPE_AUTLIC, /* AUTLIC error */
	ERRTYPE_LDAP, /* LDAP error */
	ERRTYPE_ICU, /* ICU error */
	ERRTYPE_TASKID, /* ctree task id */
	ERRTYPE_SPECIAL, /* Special identifier */
	ERRTYPE_UNKNOWN, /* undefined */

	ERRTYPE_INVALID /* Last one */
} CTLOG_ERRTYPE;

/* 
 * CTLOG_TARGET
 * Bits that control the default destination of messages. 
 * A library should NEVER assume it is safe to write to stdout, stderr, or open a window, 
 * except for (maybe) a fatal error.  These are controlled by the application, don't interfere with it.
 *
 * Legacy c-tree usage of these besides SYSLOGDT and CTSTATUS is mostly arbitrary.
 */
#define CTLOG_TARGET_LOG  	0x00000001  /* CTSTATUS.FCS */
#define CTLOG_TARGET_STDOUT 	0x00000002  /* stdout */
#define CTLOG_TARGET_STDERR	0x00000004  /* stderr */
#define CTLOG_TARGET_CTEVENT 	0x00000008  /* SYSLOGDT.FCS */
#define CTLOG_TARGET_POPUP	0x00000010  /* Gui popup like MessageBox()*/
#define CTLOG_TARGET_SYSMON     0x00000020  /* ctmqwrt(SYSMON_MAIN) */
#define CTLOG_TARGET_BALLOONTIP 0x00000040  /* ctShowBalloonTipMessage() */
#define CTLOG_TARGET_MONITOR	0x00000080  /* ctrt_monitor() */

#define CTLOG_TARGET_ALL (CTLOG_TARGET_LOG|CTLOG_TARGET_STDOUT|CTLOG_TARGET_STDERR|CTLOG_TARGET_CTEVENT|CTLOG_TARGET_POPUP|CTLOG_TARGET_SYSMON|CTLOG_TARGET_BALLOONTIP|CTLOG_TARGET_MONITOR)

#ifdef MULTITRD
#define CTLOG_TARGET_USERMESG     CTLOG_TARGET_LOG
#else
#define CTLOG_TARGET_USERMESG     CTLOG_TARGET_STDOUT
#endif

typedef struct {
	TEXT * text;
	NINT err;
	CTLOG_ERRTYPE errtype;
} CTLOG_MESG;

#ifdef ctFeatADVLOG

#ifdef __cplusplus
#ifdef MULTITRD
extern "C" NINT memsubflg;
extern "C" pTEXT ctgetmem(VRLEN iosize);
extern "C" VOID  ctputmem(pTEXT loc);
#endif

struct ctlog_catend
{
	NINT mode;
	NINT location;
	SYSNO fil;
	LONG position;
	NINT recurs;
};
/* max function name length */
#define CTMAXSYM 64
/* max FILE and LINE length  */
#define CTMAXLINE 256
class ctlog_entry
{
private:
	/* internal functions */
#ifdef MULTITRD
	pVOID calloc(size_t cnt, size_t sz) {
		if (this->suballocator)
			return ctgetmem(static_cast<COUNT>((sz*cnt)));
		else
			return ::calloc(cnt, sz);
	}

	VOID free(pVOID ptr) {
		if (this->suballocator)
			return ctputmem(static_cast<pTEXT>(ptr));
		else
			return ::free(ptr);
	}
#endif
	bool allocCatend() {
		if (!catend)
			catend = static_cast<ctlog_catend *>(calloc(1, sizeof(ctlog_catend)));
		return (catend != nullptr);
	}
	void ctlog_entry::init(CTLOG_CATEGORY category, CTLOG_SEVERITY level, const TEXT * message, NINT error, CTLOG_ERRTYPE context);
	/* internal object management */
#ifdef MULTITRD
	bool suballocator;
#endif

	/* log entry properties */
	CTLOG_ENTRY_ID entryid;
#ifdef ctFeatADVLOG_msec
	ULONG8  entrytime;
#else
	time_t entrytime;
#endif
	NINT userid;
	TEXT audience;
	CTLOG_CATEGORY category; /* subsystem id */
	CTLOG_SEVERITY severitylevel;
	NINT action; /* suggested action */
	NINT desthint; /* bit map of suggested targets for a message (log, stderr, etc). */
	bool tryopen; /* old CTRCVLOG_TRYOPEN */
	ctlog_catend *catend;
	TEXT location[CTMAXSYM]; /* calling function */
	TEXT sourceline[CTMAXLINE];  /* source && line */
	CTLOG_MESG * messages;
	NINT msg_size;
	NINT msg_last;
	TEXT entry_timestamp[64];
	pTEXT filename;
	NINT filembr;
	LONG FM_cnt;
	NINT FM_mon;
	NINT FM_mfn;
	pTEXT sqllogfile;

public:
	ctlog_entry(CTLOG_ENTRY_ID id, TEXT audience, CTLOG_CATEGORY category, NINT userid, const TEXT * message);
	ctlog_entry(CTLOG_ENTRY_ID id, TEXT audience, CTLOG_CATEGORY category, CTLOG_SEVERITY level, NINT userid, const TEXT * message,NINT error, CTLOG_ERRTYPE context);
	~ctlog_entry();
#ifdef MULTITRD
	void *operator new (size_t sz);
	void operator delete (void *ptr);
#endif

#ifdef ctFeatADVLOG_msec
	const ULONG8 getTimestamp() { return (entrytime); }
#else
	const time_t *getTimestamp() { return (const_cast<const time_t *>(&entrytime)); }
#endif
	const NINT getUserid() { return (userid); }
	const CTLOG_ENTRY_ID getEntryid() { return (entryid); }
	const TEXT getAudience() { return (audience); }
	const CTLOG_CATEGORY getCategory() { return (category); }
	const TEXT * getCategoryName();
	static const TEXT * getSeverityName(CTLOG_SEVERITY level);
	static const TEXT * getErrorTypeName(CTLOG_ERRTYPE context);
	const TEXT * getNextAudienceName(NINT &iterator);

	VOID setSeverityLevel(CTLOG_SEVERITY lvl) { severitylevel = lvl; }
	const CTLOG_SEVERITY getSeverityLevel() { return (severitylevel); }

	VOID setError(NINT error, CTLOG_ERRTYPE context);

	VOID setLocation(const TEXT * loc) { 
		strncpy(location,loc,CTMAXSYM-1);
		location[CTMAXSYM-1]='\0';
	}
	const TEXT * getLocation() { return location; }

	VOID setSourceLine(const TEXT * codeloc) { 
		strncpy(sourceline,codeloc,CTMAXLINE-1);
		sourceline[CTMAXLINE-1]='\0'; 
	}
	const TEXT * getSourceLine() { return sourceline; }

	VOID setCatend(NINT mode, NINT location, SYSNO fil, LONG pos, NINT recurs);
	bool getIsCatend() { return catend != nullptr; }
	VOID getCatend(NINT &mode, NINT &location, SYSNO &fil, LONG &pos, NINT &recurs);
	
	VOID setTryOpen(bool val) { tryopen = val; }
	const bool getTryOpen() { return (tryopen); }
	
	VOID setAction(NINT act) {action = act;}
	const NINT getAction() {return action;}

	VOID setDestinationHint(LONG hint) {desthint = hint;}
	const LONG getDestinationHint() const {return desthint;}

	VOID  setAdditionalMessage(const TEXT * msg,NINT err,CTLOG_ERRTYPE context );
	const CTLOG_MESG * getNextMessage(NINT &iterator);
	CTLOG_MESG * getNextMessageNC(NINT &iterator);

	VOID setFunctionMonitor(NINT mon, LONG cnt, NINT mfn)
	{
		FM_mon = mon;
		FM_cnt = cnt;
		FM_mfn = mfn;
	}
	
	VOID setSQLMonitorFile(const TEXT  * fileName);
	const TEXT * getSQLMonitorFile()
	{
		return sqllogfile;
	}
	TEXT * getSQLMonitorFileNC()
	{
		return sqllogfile;
	}
	
	VOID getFunctionMonitor(LONG &cnt, NINT &mfn)
	{
		cnt = FM_cnt;
		mfn = FM_mfn;
	}

	bool getFunctionMonitorToFile() 
	{
		return (FM_mon == HYS);
	}

	VOID setFileName(const TEXT * fn);
	const TEXT * getFileName() { return filename; }
	TEXT * getFileNameNC() { return filename; }
	
	VOID setFileMember(NINT mbr) { filembr = mbr; }
	NINT getFileMember() { return filembr; }

	bool getIsMonitor() { return (category == CTLOG_CATEGORY_FMONITOR || category == CTLOG_CATEGORY_SQLMONITOR); }

	const TEXT * getTimeString();
	time_t getTimetime_t();
};

extern "C" {
#include "json.h"
}

typedef COUNT(*dispatchfn)(const ctlog_entry *entry);
typedef COUNT(*dispatchJfn)(const json_object *jentry, CTLOG_CATEGORY category, NINT level, TEXT audience, NINT options);

class ctlog_dispatcher
{
private:
	NINT disp_number;
	NINT dispJ_number;
	dispatchfn *fns;
	dispatchJfn *Jfns;

	pVOID getJSON(ctlog_entry &entry);
	VOID freeJSON(pVOID hdl);
	json_object *allocjerror(json_object *jroot); /* no need to free it since immediately attached to the root */
	json_object * ctlog_dispatcher::MessageToJSON(const CTLOG_MESG * msg);

public:
	ctlog_dispatcher();
	~ctlog_dispatcher();
	COUNT dispatch(ctlog_entry &entry);
	COUNT register_dispatcher(dispatchfn fn);
	COUNT register_dispatcher(dispatchJfn fn);
};

#endif

#else /* ctFeatADVLOG */
typedef struct {
	CTLOG_MESG * messages;
	LONG desthint;
	CTLOG_SEVERITY severitylevel;
	NINT msg_size;
	NINT msg_last;
} CTLOG_STRUCT;
#endif /* ~ctFeatADVLOG */

#ifdef ctFeatNEWctrcvlog
#ifdef __cplusplus
extern "C" {
#endif
/*^**************************************\
 *
 *   "C" exposed API to perform logging 
 *
\****************************************/

COUNT ctLogMsgDirect(CTLOG_ENTRY_ID id, TEXT audience, CTLOG_CATEGORY category, CTLOG_SEVERITY level, NINT userid, pTEXT message, NINT error, CTLOG_ERRTYPE context);
pVOID ctLogMsgGetHandle(CTLOG_ENTRY_ID id, TEXT audience, CTLOG_CATEGORY category, NINT userid, const TEXT * message);
COUNT ctLogMsgDispatch(ppVOID msghdl);
COUNT ctLogMsgAdvlog(CTLOG_ENTRY_ID id, TEXT audience, CTLOG_CATEGORY category, CTLOG_SEVERITY level, NINT userid, const TEXT * oldmsg, NINT olderr,const TEXT * newmsg, NINT error, CTLOG_ERRTYPE context, NINT usererr,NINT syserr,const TEXT * location,NINT action, const TEXT * codeloc );
void ctLogMsgFormatted(CTLOG_ENTRY_ID logid, NINT whofor,CTLOG_CATEGORY subsystem, CTLOG_SEVERITY severity, 
	NINT sOWNR, NINT err, CTLOG_ERRTYPE errinfo, NINT action, 
	const TEXT* function, const TEXT* loc,  TEXT * buffer, size_t size, const TEXT * fmt, ...);
VOID ctLogMsgSetDestination(pVOID msghdl,LONG destination);
VOID ctLogMsgSetDestinationHint(pVOID msghdl,LONG destination);
VOID ctLogMsgSetTryOpen(pVOID msghdl);
VOID ctLogMsgSetFullError(pVOID msghdl, NINT error,CTLOG_ERRTYPE context);
VOID ctLogMsgSetCatend(pVOID msghdl, NINT mode, NINT location, SYSNO fil, LONG pos, NINT recurs);
VOID ctLogMsgSetAdditionalMessage(pVOID msghdl, const TEXT * message, NINT error, CTLOG_ERRTYPE context);
VOID ctLogMsgSetFunctionMonitor(pVOID msghdl, NINT fncmon,LONG FM_cnt, NINT mfn, const TEXT * info, NINT mbr);
VOID ctLogMsgSetSeverity(pVOID msghdl, CTLOG_SEVERITY lvl);
VOID ctLogMsgSetLocation(pVOID msghdl, const TEXT * func);
VOID ctLogMsgSetAction(pVOID msghdl,CTLOG_ACTION action);
VOID ctLogMsgSetCodeLine(pVOID msghdl, const TEXT * line);

/* dispatch register functions*/
COUNT ctLogRegisterJSONDispatcher(COUNT(*dispatchOfn)(const void *jentry, CTLOG_CATEGORY category, NINT level, TEXT audience, NINT options));
COUNT ctLogRegisterDispatcher(COUNT(*dispatchfn)(const void *entry));
#ifdef __cplusplus
}
#endif 
#endif /* ctFeatNEWctrcvlog */

#endif /*_CTLOGGER_H_*/
/* end of ctlogger.h */

