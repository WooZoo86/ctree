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

#include "ctrepluser.h"

/*
** Enable REPLUSER_LOGGING if you wish to log messages for each event to the
** file ctrepluser.log.
*/
/* #define REPLUSER_LOGGING */

/*
** Enable REPLUSER_OPEN_EXAMPLE if you wish to test the ability to open files
** from external library callback functions.
*/
/* #define REPLUSER_OPEN_EXAMPLE */

/* Name of file to open. */
#define REPLUSER_OPEN_FILENAME "mark.dat"

/*
** Enable REPLUSER_SKIP_EXAMPLE if you wish to test the ability to skip
** operations. 
*/
/* #define REPLUSER_SKIP_EXAMPLE */

/* Name of file whose operations should be skipped. */
#define REPLUSER_SKIP_FILENAME "mark.dat"

#ifdef REPLUSER_LOGGING
/* replication external library state variables */
typedef struct rxstt {
	pFILE	logfp;
	NINT	logLevel;
	struct {
		pTEXT	name;
		LONG8	count;
	} func[RXF_TOTAL];
} RXSTT, *pRXSTT;

enum {
	RX_STATUS_INF = 0, /* informational message	*/
	RX_STATUS_WRN = 1, /* warning message		*/
	RX_STATUS_ERR = 2  /* error message		*/
};

enum {
	RX_LOGLEVEL_INF = 0, /* log informational, warning, and error message */
	RX_LOGLEVEL_WRN = 1, /* log warning and error messages only */
	RX_LOGLEVEL_ERR = 2  /* log error messages only */
};

static cpTEXT msgdesc[] = {
	"INF",
	"WRN",
	"ERR"
};
#endif

/* replication external library record information */
typedef struct rxrec {
	NINT keylen;     /* replication unique key length */
	NINT reclen;     /* record length (add, delete, and before update) */
	NINT updreclen;  /* record length (after update) */
	pTEXT keyval;    /* replication unique key value (add, delete, and before update) */
	pTEXT recbuf;    /* record image (add, delete, and before update) */
	pTEXT updkeyval; /* replication unique key value (after update) */
	pTEXT updrecbuf; /* record image (after update) */
} RXREC, *pRXREC;

#ifdef REPLUSER_LOGGING
/*^***********************************/
/*
** Get the description for the specified message type.
*/
cpTEXT ctRXgetmsgdesc (NINT msgtyp)
{
	if (msgtyp < 0 || msgtyp > sizeof(msgdesc)/sizeof(*msgdesc))
		return("UNKNOWN");
	
	return(msgdesc[msgtyp]);
}
/*~***********************************/
#endif

#ifdef REPLUSER_LOGGING
#include <stdarg.h>

/*^***********************************/
/*
** Write a message to the extension library log.
*/
NINT ctRXlogmsg (pRXSTT prxstt, NINT msgtyp, cpTEXT fmt, ...)
{
#ifndef ctSRVR
	time_t		t;
	struct tm	res;
#endif
	va_list		arg;
	pTEXT		tp;
	TEXT		buf[1024];

	va_start(arg, fmt);

	if (!prxstt || msgtyp < prxstt->logLevel)
		goto err_ret;

	t = cttime();
	ctrt_localtime_r(&t, &res);
	ctrt_asctime_r(&res, buf);
	tp = buf + 24;
	sprintf(tp, ": %s: ", ctRXgetmsgdesc(msgtyp));
	tp += strlen(tp);

	vsprintf(tp, fmt, arg);
	tp = buf + strlen(buf) - 1;
	if (*tp == '\n')
		*tp = '\0';

	if (prxstt->logfp) {
		fprintf(prxstt->logfp, "%s\n", buf);
		fflush(prxstt->logfp);
	}

err_ret:
	va_end(arg);

	return(0);
}
/*~***********************************/
#endif /* REPLUSER_LOGGING */

/*^***********************************/
/*
** Retrieve the record information from the Data Function callback
*/
VOID ctRXgetrecbuf(prxDATOP prxdatop, pRXREC recinfo)
{
	pctCHGB pchgbuf = prxdatop->pchgbuf;

	recinfo->keylen = pchgbuf->keylen;
	recinfo->updreclen = 0;
	recinfo->updkeyval = recinfo->updrecbuf = NULL;

	switch (pchgbuf->opcode) {
	case REPL_ADDREC:
	case REPL_DELREC:
		recinfo->reclen = pchgbuf->reclen;
		recinfo->keyval = pchgbuf->varinf;
		recinfo->recbuf = pchgbuf->varinf + pchgbuf->keylen;
		break;

	case REPL_RWTREC:
		recinfo->reclen = pchgbuf->oldrln;
		recinfo->keyval = pchgbuf->varinf;
		recinfo->recbuf = pchgbuf->varinf + pchgbuf->oldkln + pchgbuf->keylen;
		recinfo->updreclen = pchgbuf->reclen;
		recinfo->updkeyval = pchgbuf->varinf + pchgbuf->oldkln;
		recinfo->updrecbuf = recinfo->recbuf + pchgbuf->oldrln;
		break;

	default:
		recinfo->reclen = 0;
		recinfo->keyval = recinfo->recbuf = NULL;
	}
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent is starting.
*/
rxEXPORT VOID rxOnStartAgent (prxEVENT prxevent)
{
	prxVEROP prxverop;
	if (prxevent) {
#ifdef REPLUSER_LOGGING
		pRXSTT	prxstt;
#endif
		if (prxevent->versn != RX_EVENT_VERSION)
			return;
		if ((prxverop = &prxevent->ev.verop)) {
			/* Return the structure versions that we are using. */
			prxverop->verop_ver = RX_VEROP_VERSION;
			prxverop->event_ver = RX_EVENT_VERSION;
			prxverop->filop_ver = RX_FILOP_VERSION;
			prxverop->trnop_ver = RX_TRNOP_VERSION;
			prxverop->datop_ver = RX_DATOP_VERSION;
			prxverop->excop_ver = RX_EXCOP_VERSION;
			prxverop->filh_ver = REPFILH_VERSION;
		}
#ifdef REPLUSER_LOGGING
		/* Allocate user context pointer. */	
		if ((prxstt = calloc(1,sizeof(RXSTT)))) {
			prxevent->pusrctx = prxstt;
			prxstt->logfp = fopen("ctrepluser.log", "a");
			prxstt->logLevel = RX_LOGLEVEL_INF;
			NINT	i;
			for (i=0; i<RXF_TOTAL; i++) {
				prxstt->func[i].name = rxLibFuncNames[i];
			}
			++prxstt->func[RXF_OnStartAgent].count;
		}
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnStartAgent: unique_id=%s",
			prxevent->unqid);
#endif
	}
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent connected to source server.
*/
rxEXPORT VOID rxOnSourceConnected (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;
	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnSourceConnected].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnSourceConnected: source_server=%s; source_nodeid=%s",
			prxevent->srcsvn,prxevent->srcnodeid);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent connected to target server.
*/
rxEXPORT VOID rxOnTargetConnected (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;
	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnTargetConnected].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnTargetConnected: target_server=%s; target_nodeid=%s",
			prxevent->tgtsvn,prxevent->tgtnodeid);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent lost connection to source server.
*/
rxEXPORT VOID rxOnSourceLostConnection (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;
	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnSourceLostConnection].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnSourceLostConnection");
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent lost connection to target server.
*/
rxEXPORT VOID rxOnTargetLostConnection (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;
	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnTargetLostConnection].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnTargetLostConnection");
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent disconnected from source server.
*/
rxEXPORT VOID rxOnSourceDisconnected (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;
	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnSourceDisconnected].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnSourceDisconnected");
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent disconnected from target server.
*/
rxEXPORT VOID rxOnTargetDisconnected (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;
	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnTargetDisconnected].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnTargetDisconnected");
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent terminating due to exception.
*/
rxEXPORT VOID rxOnTerminateAgent (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;
	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnTerminateAgent].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnTerminateAgent: errcod=%d",
			prxevent->errcod);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent is pausing its operation.
*/
rxEXPORT VOID rxOnPauseAgent (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;
	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnPauseAgent].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnPauseAgent");
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent is resuming its operation.
*/
rxEXPORT VOID rxOnResumeAgent (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;
	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnResumeAgent].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnResumeAgent");
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Replication agent is shutting down.
*/
rxEXPORT VOID rxOnStopAgent (prxEVENT prxevent)
{
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt;

	if (prxevent && (prxstt = (pRXSTT) prxevent->pusrctx)) {
		++prxstt->func[RXF_OnStopAgent].count;
		if (prxstt->logfp) {
			ctRXlogmsg(prxstt, RX_STATUS_INF, "OnStopAgent");
			fclose(prxstt->logfp);
		}
		free(prxstt);
		prxevent->pusrctx = NULL;
	}
#endif
}
/*~***********************************/

#ifdef REPLUSER_SKIP_EXAMPLE
NINT g_skip = YES;
#endif

/*^***********************************/
/*
** Event: Read a "file open" entry from source server.
*/
rxEXPORT VOID rxOnOpenFile (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnOpenFile].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnOpenFile: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
#ifdef REPLUSER_SKIP_EXAMPLE
	if (g_skip && !strcmp(prxfilop->pfilhnd->filnam, REPLUSER_SKIP_FILENAME))
		prxevent->action = RXA_SKIP;
#endif

	/* Source server connection handle: prxevent->psrccnxhnd */
	/* Target server connection handle: prxevent->ptgtcnxhnd */
	/* Change buffer for this operation: prxfilop->pchgbuf */
	/* File handle for this operation: prxfilop->pfilhnd */

#ifdef REPLUSER_OPEN_EXAMPLE
	if (prxfilop) {
		/* Demonstrating switching to source and target server and
		opening a file on each server. */
		NINT	rc;
		COUNT datno;
		ctFILH filhnd;
		ctCHGB	chgbuf;
		TEXT	keyval[100];

		memset(&filhnd,0,sizeof(filhnd));
		cpynbuf(filhnd.filnam,REPLUSER_OPEN_FILENAME,MAX_NAME);
		if ((rc = ctReplOpenFile(prxevent->psrccnxhnd, filhnd.filnam, &filhnd)))
			goto err_ret;
		memset(&chgbuf,0,sizeof(chgbuf));
		/* read the first record in replication unique key order */
		if (!(rc = ctReplReadFirstRecord(prxevent->psrccnxhnd, &filhnd, &chgbuf))) {
			/* read the next record in replication unique key order */
			if (!(rc = ctReplReadNextRecord(prxevent->psrccnxhnd, &filhnd, &chgbuf))) {
			}
		}
		if (chgbuf.keylen <= sizeof(keyval)) {
			memcpy(keyval,chgbuf.varinf,chgbuf.keylen);
			uTFRMKEY(filhnd.keyno,keyval);
			/* read the record that has the specified replication unique key */
			if (!(rc = ctReplReadRecordByKey(prxevent->psrccnxhnd, &filhnd,
			    keyval,&chgbuf))) {
			}
		}
		if (chgbuf.varinf) {
			ctReplFreeMem(chgbuf.varinf);
			chgbuf.varinf = NULL;
		}
		ctReplCloseFile(prxevent->psrccnxhnd,&filhnd);

		memset(&filhnd,0,sizeof(filhnd));
		cpynbuf(filhnd.filnam,REPLUSER_OPEN_FILENAME,MAX_NAME);
		if ((rc = ctReplOpenFile(prxevent->ptgtcnxhnd, filhnd.filnam, &filhnd)))
			goto err_ret;
		ctReplCloseFile(prxevent->ptgtcnxhnd,&filhnd);

		/* Switch to source server. */
		if ((rc = ictReplSwitchInst(prxevent->psrccnxhnd, CTREPL_INST_SRV)))
			goto err_ret;
		/* Open file on source server. */
		if ((datno = OPNRFILX(-1,REPLUSER_OPEN_FILENAME,ctSHARED,NULL)) < 0)
			goto err_ret;
		CLRFIL(datno);

		/* Switch to target server. */
		if ((rc = ictReplSwitchInst(prxevent->ptgtcnxhnd, CTREPL_INST_SRV)))
			goto err_ret;
		/* Open file on target server. */
		if ((datno = OPNRFILX(-1,REPLUSER_OPEN_FILENAME,ctSHARED,NULL)) < 0)
			goto err_ret;
		CLRFIL(datno);
err_ret: ;
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Called after successful file open operation.
*/
rxEXPORT VOID rxAfterOpenFile (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif
	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_AfterOpenFile].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "AfterOpenFile: logser=%d; logpos=%d; fileid=%d; filnam=%s; datno=%d",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pchgbuf->fileid,prxfilop->pfilhnd->filnam,
			prxfilop->pfilhnd->datno);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a "file close" entry from source server.
*/
rxEXPORT VOID rxOnCloseFile (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnCloseFile].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnCloseFile: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read an "alter schema" entry from source server.
*/
rxEXPORT VOID rxOnAlterSchema (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_ALTER_SCHEMA_EXAMPLE
	/* This example code shows how to read the alter schema parameters from
	the replication change buffer. */
	{
	pRCDSC	prcdsc = NULL;
	NINT	rc;

	if ((rc = makAlterSchema(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,(ppTEXT) &prcdsc))) {
		/* Error reading parameters. */
		if (prcdsc)
			mbfree(prcdsc);
	} else {
		/* Successfully read parameters. */
		mbfree(prcdsc);
	}
	}
#endif

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnAlterSchema].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnAlterSchema: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a resync file entry from source server.
*/
rxEXPORT VOID rxOnResyncFile (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnResyncFile].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnResyncFile: logser=%d; logpos=%d; resyncid=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pchgbuf->varinf);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a PTADMIN entry from source server.
*/
rxEXPORT VOID rxOnPTADMIN (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_PTADMIN_EXAMPLE
	/* This example code shows how to read the PTADMIN() parameters from the
	replication change buffer. */
	{
	pctPTAPM ptaprm = NULL;
	NINT	rc;

	if ((rc = makPTADMIN(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,&ptaprm))) {
		/* Error reading parameters. */
		if (ptaprm)
			mbfree(ptaprm);
	} else {
		/* Successfully read parameters. */
		mbfree(ptaprm);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnPTADMIN].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnPTADMIN: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a CREIFIL entry from source server.
*/
rxEXPORT VOID rxOnCREIFIL (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_CREIFIL_EXAMPLE
	/* This example code shows how to read the CREIFIL() parameters from the
	replication change buffer. */
	{
	pCREATE_IFIL_PARAMS pCreateIfilParams = NULL;
	NINT	rc;

	if ((rc = makCREIFIL(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pCreateIfilParams))) {
		/* Error reading parameters. */
		freCREIFIL(pCreateIfilParams);
	} else {
		/* Successfully read parameters. */
		freCREIFIL(pCreateIfilParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnCREIFIL].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnCREIFIL: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a RENIFIL entry from source server.
*/
rxEXPORT VOID rxOnRENIFIL (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_RENIFIL_EXAMPLE
	/* This example code shows how to read the RENIFIL() parameters from the
	replication change buffer. */
	{
	pRENAME_IFIL_PARAMS pRenameIfilParams = NULL;
	NINT	rc;

	if ((rc = makRENIFIL(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pRenameIfilParams))) {
		/* Error reading parameters. */
		freRENIFIL(pRenameIfilParams);
	} else {
		/* Successfully read parameters. */
		freRENIFIL(pRenameIfilParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnRENIFIL].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnRENIFIL: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read an addIDfield entry from source server.
*/
rxEXPORT VOID rxOnAddIdField (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_ADDIDFIELD_EXAMPLE
	/* This example code shows how to read the addIDfield() parameters from the
	replication change buffer. */
	{
	pADD_IDFIELD_PARAMS pAddIdFieldIfilParams = NULL;
	NINT	rc;

	if ((rc = makADDIDFIELD(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pAddIdFieldIfilParams))) {
		/* Error reading parameters. */
		freADDIDFIELD(pAddIdFieldIfilParams);
	} else {
		/* Successfully read parameters. */
		freADDIDFIELD(pAddIdFieldIfilParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnAddIdField].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnAddIdFIeld: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a delIDfield entry from source server.
*/
rxEXPORT VOID rxOnDelIdField (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_DELIDFIELD_EXAMPLE
	/* This example code shows how to read the delIDfield() parameters from the
	replication change buffer. */
	{
	pDEL_IDFIELD_PARAMS pDelIdFieldIfilParams = NULL;
	NINT	rc;

	if ((rc = makDELIDFIELD(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pDelIdFieldIfilParams))) {
		/* Error reading parameters. */
		freDELIDFIELD(pDelIdFieldIfilParams);
	} else {
		/* Successfully read parameters. */
		freDELIDFIELD(pDelIdFieldIfilParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnDelIdField].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnDelIdFIeld: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a resetIDfield entry from source server.
*/
rxEXPORT VOID rxOnResetIdField (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_RESETIDFIELD_EXAMPLE
	/* This example code shows how to read the resetIDfield() parameters from the
	replication change buffer. */
	{
	pRESET_IDFIELD_PARAMS pResetIdFieldIfilParams = NULL;
	NINT	rc;

	if ((rc = makRESETIDFIELD(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pResetIdFieldIfilParams))) {
		/* Error reading parameters. */
		freRESETIDFIELD(pResetIdFieldIfilParams);
	} else {
		/* Successfully read parameters. */
		freRESETIDFIELD(pResetIdFieldIfilParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnResetIdField].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnResetIdFIeld: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a xtdatrIDfield entry from source server.
*/
rxEXPORT VOID rxOnXtdatrIdField (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_XTDATRIDFIELD_EXAMPLE
	/* This example code shows how to read the xtdatrIDfield() parameters from the
	replication change buffer. */
	{
	pXTDATR_IDFIELD_PARAMS pXtdatrIdFieldIfilParams = NULL;
	NINT	rc;

	if ((rc = makXTDATRIDFIELD(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pXtdatrIdFieldIfilParams))) {
		/* Error reading parameters. */
		freXTDATRIDFIELD(pXtdatrIdFieldIfilParams);
	} else {
		/* Successfully read parameters. */
		freXTDATRIDFIELD(pXtdatrIdFieldIfilParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnXtdatrIdField].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnXtdatrIdFIeld: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a delete file entry from source server.
*/
rxEXPORT VOID rxOnDeleteFile (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_DELETE_FILE_EXAMPLE
	/* This example code shows how to read the delete file parameters from the
	replication change buffer. */
	{
	pDELETE_IFIL_PARAMS pDeleteIfilParams = NULL;
	NINT rc;
		
	if ((rc = makDELIFIL(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pDeleteIfilParams))) {
		freDELIFIL(pDeleteIfilParams);
	} else {
		freDELIFIL(pDeleteIfilParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnDeleteFile].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnDeleteFile: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a lowlevel create data file entry from source server.
*/
rxEXPORT VOID rxOnCreateDataFile (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_CREDAT_EXAMPLE
	/* This example code shows how to read the create data file parameters from the
	replication change buffer. */
	{
	pCREATE_DATA_FILE_PARAMS pCreateDataFileParams = NULL;
	NINT rc;
		
	if ((rc = makCREDATX8(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pCreateDataFileParams))) {
		freCREDATX8(pCreateDataFileParams);
	} else {
		freCREDATX8(pCreateDataFileParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnCreateDataFile].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnCreateDataFile: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a lowlevel delete data file entry from source server.
*/
rxEXPORT VOID rxOnDeleteDataFile (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_DELFIL_EXAMPLE
	/* This example code shows how to read the delete data file parameters from the
	replication change buffer. */
	{
	pDELETE_DATA_FILE_PARAMS pDeleteDataFileParams = NULL;
	NINT rc;
		
	if ((rc = makDELFIL(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pDeleteDataFileParams))) {
		freDELFIL(pDeleteDataFileParams);
	} else {
		freDELFIL(pDeleteDataFileParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnDeleteDataFile].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnDeleteDataFile: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a SETDEFBLK entry from source server.
*/
rxEXPORT VOID rxOnSETDEFBLK (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_SETDEFBLK_EXAMPLE
	/* This example code shows how to read the SETDEFBLKX() parameters from the
	replication change buffer. */
	{
	pSETDEFBLKX_PARAMS SetDefBlkXParams = NULL;
	NINT	rc;

	if ((rc = makSETDEFBLK(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&SetDefBlkXParams))) {
		/* Error reading parameters. */
		freSETDEFBLK(SetDefBlkXParams);
	} else {
		/* Successfully read parameters. */
		freSETDEFBLK(SetDefBlkXParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnSETDEFBLK].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnSETDEFBLK: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a create index entry from source server.
*/
rxEXPORT VOID rxOnCreateIndex (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_CREIDX_EXAMPLE
	/* This example code shows how to read the create index parameters from the
	replication change buffer. */
	{
	pCREATE_ISAM_INDEX_PARAMS pCreateIsamIndexParams = NULL;
	pIFILBLK pifilblk;
	NINT rc;
		
	if ((rc = makCreateIsamIndex(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pCreateIsamIndexParams))) {
		freCreateIsamIndex(pCreateIsamIndexParams);
	} else {
		pifilblk = pCreateIsamIndexParams->pifilblk;
		freCreateIsamIndex(pCreateIsamIndexParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnCreateIndex].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnCreateIndex: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a drop index entry from source server.
*/
rxEXPORT VOID rxOnDropIndex (prxEVENT prxevent)
{
	prxFILOP prxfilop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxfilop = &prxevent->ev.filop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

#ifdef REPLUSER_DROPIDX_EXAMPLE
	/* This example code shows how to read the drop index parameters from the
	replication change buffer. */
	{
	pDROP_INDEX_PARAMS pDropIndexParams = NULL;
	NINT rc;
		
	if ((rc = makDROPIDX(prxfilop->pchgbuf->varinf,prxfilop->pchgbuf->varlen,NO,&pDropIndexParams))) {
		freDROPIDX(pDropIndexParams);
	} else {
		freDROPIDX(pDropIndexParams);
	}
	}
#endif
	/* Change buffer for this operation: prxfilop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnDropIndex].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnDropIndex: logser=%d; logpos=%d; fileid=%d; filnam=%s",
			prxfilop->pchgbuf->logser,prxfilop->pchgbuf->logpos,
			prxfilop->pfilhnd->fileid,prxfilop->pfilhnd->filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a "transaction begin" entry from source server.
*/
rxEXPORT VOID rxOnStartTransaction (prxEVENT prxevent)
{
	prxTRNOP prxtrnop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxtrnop = &prxevent->ev.trnop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxtrnop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxtrnop && prxstt) {
		++prxstt->func[RXF_OnStartTransaction].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnStartTransaction: logser=%d; logpos=%d; tranno=" ctLLd "; timestamp=" ctLLd,
			prxtrnop->pchgbuf->logser,prxtrnop->pchgbuf->logpos,
			prxtrnop->pchgbuf->tranno,prxtrnop->pchgbuf->tstamp);
#ifdef REPLUSER_SKIP_EXAMPLE
		if (g_skip)
			prxevent->action = RXA_SKIP;
#endif
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a "commit succeeded" entry from source server.
*/
rxEXPORT VOID rxOnCommitTransaction (prxEVENT prxevent)
{
	prxTRNOP prxtrnop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxtrnop = &prxevent->ev.trnop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxtrnop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnCommitTransaction].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnCommitTransaction: logser=%d; logpos=%d; tranno=" ctLLd "; timestamp=" ctLLd,
			prxtrnop->pchgbuf->logser,prxtrnop->pchgbuf->logpos,
			prxtrnop->pchgbuf->tranno,prxtrnop->pchgbuf->tstamp);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a "transaction abort" entry from source server.
*/
rxEXPORT VOID rxOnAbortTransaction (prxEVENT prxevent)
{
	prxTRNOP prxtrnop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxtrnop = &prxevent->ev.trnop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxtrnop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnAbortTransaction].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnAbortTransaction: logser=%d; logpos=%d; tranno=" ctLLd "; timestamp=" ctLLd,
			prxtrnop->pchgbuf->logser,prxtrnop->pchgbuf->logpos,
			prxtrnop->pchgbuf->tranno,prxtrnop->pchgbuf->tstamp);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a "user-defined" entry from source server.
*/
rxEXPORT VOID rxOnUserTransaction (prxEVENT prxevent)
{
	prxTRNOP prxtrnop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxtrnop = &prxevent->ev.trnop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxtrnop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnUserTransaction].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnUserTransaction: logser=%d; logpos=%d",
			prxtrnop->pchgbuf->logser,prxtrnop->pchgbuf->logpos);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a "checkpoint" entry from source server.
*/
rxEXPORT VOID rxOnCheckpoint (prxEVENT prxevent)
{
	prxTRNOP prxtrnop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxtrnop = &prxevent->ev.trnop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Log number of checkpoint: prxtrnop->pchgbuf->logser */
	/* Offset of checkpoint: prxtrnop->pchgbuf->logpos */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnCheckpoint].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnCheckpoint: logser=%d; logpos=%d; timestamp=" ctLLd,
			prxtrnop->pchgbuf->logser,prxtrnop->pchgbuf->logpos,
			prxtrnop->pchgbuf->tstamp);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read an "add record" entry from source server.
*/
rxEXPORT VOID rxOnAddRecord (prxEVENT prxevent)
{
	prxDATOP prxdatop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif
	RXREC recinfo;

	if (prxevent) {
		prxdatop = &prxevent->ev.datop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Retrieve new record buffer */
	ctRXgetrecbuf(prxdatop, &recinfo);

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		pTEXT	filnam = "";

		++prxstt->func[RXF_OnAddRecord].count;
		if (prxdatop->pfilhnd)
			filnam = prxdatop->pfilhnd->filnam;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnAddRecord: logser=%d; logpos=%d; tranno=" ctLLd"; fileid=%d; filnam=%s",
			prxdatop->pchgbuf->logser,prxdatop->pchgbuf->logpos,
			prxdatop->pchgbuf->tranno,prxdatop->pchgbuf->fileid,
			filnam);
#ifdef REPLUSER_SKIP_EXAMPLE
		if (g_skip && !strcmp(prxdatop->pfilhnd->filnam, REPLUSER_SKIP_FILENAME))
			prxevent->action = RXA_SKIP;
#endif
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read an "update record" entry from source server.
*/
rxEXPORT VOID rxOnUpdateRecord (prxEVENT prxevent)
{
	prxDATOP prxdatop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif
	RXREC recinfo;

	if (prxevent) {
		prxdatop = &prxevent->ev.datop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Retrieve old and new record buffers */
	ctRXgetrecbuf(prxdatop, &recinfo);

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		pTEXT	filnam = "";

		++prxstt->func[RXF_OnUpdateRecord].count;
		if (prxdatop->pfilhnd)
			filnam = prxdatop->pfilhnd->filnam;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnUpdateRecord: logser=%d; logpos=%d; tranno=" ctLLd"; fileid=%d; filnam=%s",
			prxdatop->pchgbuf->logser,prxdatop->pchgbuf->logpos,
			prxdatop->pchgbuf->tranno,prxdatop->pchgbuf->fileid,
			filnam);
#ifdef REPLUSER_SKIP_EXAMPLE
		if (g_skip && !strcmp(prxdatop->pfilhnd->filnam, REPLUSER_SKIP_FILENAME))
			prxevent->action = RXA_SKIP;
#endif
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a "delete record" entry from source server.
*/
rxEXPORT VOID rxOnDeleteRecord (prxEVENT prxevent)
{
	prxDATOP prxdatop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif
	RXREC recinfo;

	if (prxevent) {
		prxdatop = &prxevent->ev.datop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Retrieve old record buffer */
	ctRXgetrecbuf(prxdatop, &recinfo);

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		pTEXT	filnam = "";

		++prxstt->func[RXF_OnDeleteRecord].count;
		if (prxdatop->pfilhnd)
			filnam = prxdatop->pfilhnd->filnam;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnDeleteRecord: logser=%d; logpos=%d; tranno=" ctLLd"; fileid=%d; filnam=%s",
			prxdatop->pchgbuf->logser,prxdatop->pchgbuf->logpos,
			prxdatop->pchgbuf->tranno,prxdatop->pchgbuf->fileid,
			filnam);
#ifdef REPLUSER_SKIP_EXAMPLE
		if (g_skip && !strcmp(prxdatop->pfilhnd->filnam, REPLUSER_SKIP_FILENAME))
			prxevent->action = RXA_SKIP;
#endif
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a "deferred key" entry from source server.
*/
rxEXPORT VOID rxOnDeferredKey (prxEVENT prxevent)
{
	prxDATOP prxdatop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxdatop = &prxevent->ev.datop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxdatop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		pTEXT	filnam = "";

		++prxstt->func[RXF_OnDeferredKey].count;
		if (prxdatop->pfilhnd)
			filnam = prxdatop->pfilhnd->filnam;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnDeferredKey: logser=%d; logpos=%d; tranno=" ctLLd"; fileid=%d; filnam=%s",
			prxdatop->pchgbuf->logser,prxdatop->pchgbuf->logpos,
			prxdatop->pchgbuf->tranno,prxdatop->pchgbuf->fileid,
			filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read an add resource entry from source server.
*/
rxEXPORT VOID rxOnAddResource (prxEVENT prxevent)
{
	prxDATOP prxdatop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxdatop = &prxevent->ev.datop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxdatop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		pTEXT	filnam = "";

		++prxstt->func[RXF_OnAddResource].count;
		if (prxdatop->pfilhnd)
			filnam = prxdatop->pfilhnd->filnam;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnAddResource: logser=%d; logpos=%d; tranno=" ctLLd"; fileid=%d; filnam=%s",
			prxdatop->pchgbuf->logser,prxdatop->pchgbuf->logpos,
			prxdatop->pchgbuf->tranno,prxdatop->pchgbuf->fileid,
			filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read an update resource entry from source server.
*/
rxEXPORT VOID rxOnUpdateResource (prxEVENT prxevent)
{
	prxDATOP prxdatop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxdatop = &prxevent->ev.datop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxdatop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		pTEXT	filnam = "";

		++prxstt->func[RXF_OnUpdateResource].count;
		if (prxdatop->pfilhnd)
			filnam = prxdatop->pfilhnd->filnam;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnUpdateResource: logser=%d; logpos=%d; tranno=" ctLLd"; fileid=%d; filnam=%s",
			prxdatop->pchgbuf->logser,prxdatop->pchgbuf->logpos,
			prxdatop->pchgbuf->tranno,prxdatop->pchgbuf->fileid,
			filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: Read a delete resource entry from source server.
*/
rxEXPORT VOID rxOnDeleteResource (prxEVENT prxevent)
{
	prxDATOP prxdatop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxdatop = &prxevent->ev.datop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxdatop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		pTEXT	filnam = "";

		++prxstt->func[RXF_OnDeleteResource].count;
		if (prxdatop->pfilhnd)
			filnam = prxdatop->pfilhnd->filnam;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnDeleteResource: logser=%d; logpos=%d; tranno=" ctLLd"; fileid=%d; filnam=%s",
			prxdatop->pchgbuf->logser,prxdatop->pchgbuf->logpos,
			prxdatop->pchgbuf->tranno,prxdatop->pchgbuf->fileid,
			filnam);
	}
#endif
}
/*~***********************************/

/*^***********************************/
/*
** Event: An action performed by the replication agent fails.
*/
rxEXPORT VOID rxOnException (prxEVENT prxevent)
{
	prxEXCOP prxexcop = NULL;
#ifdef REPLUSER_LOGGING
	pRXSTT	prxstt = NULL;
#endif

	if (prxevent) {
		prxexcop = &prxevent->ev.excop;
#ifdef REPLUSER_LOGGING
		prxstt = (pRXSTT) prxevent->pusrctx;
#endif
	}

	/* Change buffer for this operation: prxexcop->pchgbuf */

#ifdef REPLUSER_LOGGING
	if (prxstt) {
		++prxstt->func[RXF_OnException].count;
		ctRXlogmsg(prxstt, RX_STATUS_INF, "OnException: opcode=%d; errcod=%d; logser=%d; logpos=%d; filnam=%s",
			prxexcop->pchgbuf->opcode,prxexcop->errcod,
			prxexcop->pchgbuf->logser,prxexcop->pchgbuf->logpos,
			prxexcop->pfilhnd ? prxexcop->pfilhnd->filnam : "");
	}
#endif
}
/*~***********************************/

/* end of ctrepluser.c */
