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

#include "ctreep.h"

#ifdef ctPortWIN32
#define rxEXPORT __declspec(dllexport)
#else
#define rxEXPORT
#endif

/* Categories of replication events: */
typedef enum _rxevc {
	RX_EVENT_AGENT		= 1,	/* agent event			  */
	RX_EVENT_FILE		= 2,	/* file operation		  */
	RX_EVENT_TRANSACTION	= 3,	/* transaction operation	  */
	RX_EVENT_DATA		= 4,	/* data operation		  */
	RX_EVENT_EXCEPTION	= 5	/* exception			  */
} RXEVC;

/* Check structure versions for compatibility: */

#define RX_VEROP_VER1		1
#define RX_VEROP_VERSION	RX_VEROP_VER1 /* current version of rxVEROP  */

typedef struct _rxverop {
	LONG	verop_ver;	/* [OUT] Set to version of rxVEROP	  */
	LONG	event_ver;	/* [OUT] Set to version of rxEVENT	  */
	LONG	filop_ver;	/* [OUT] Set to version of rxFILOP	  */
	LONG	trnop_ver;	/* [OUT] Set to version of rxTRNOP	  */
	LONG	datop_ver;	/* [OUT] Set to version of rxDATOP	  */
	LONG	excop_ver;	/* [OUT] Set to version of rxEXCOP	  */
	LONG	filh_ver;	/* [OUT] Set to version of ctFILH	  */
} rxVEROP, *prxVEROP;

/* Parameters for file events: */

#define RX_FILOP_VER1		1
#define RX_FILOP_VERSION	RX_FILOP_VER1 /* current version of rxFILOP  */

typedef struct _rxfilop {
	pctCHGB pchgbuf;	/* [IN] File operation details		  */
	pctFILH	pfilhnd;	/* [IN] File information		  */
} rxFILOP, *prxFILOP;

/* Parameters for transaction events: */

#define RX_TRNOP_VER1		1
#define RX_TRNOP_VERSION	RX_TRNOP_VER1 /* current version of rxTRNOP  */

typedef struct _rxtrnop {
	pctCHGB pchgbuf;	/* [IN] Transaction operation details	  */
} rxTRNOP, *prxTRNOP;

/* Parameters for data events: */

#define RX_DATOP_VER1		1
#define RX_DATOP_VERSION	RX_DATOP_VER1 /* current version of rxDATOP  */

typedef struct _rxdatop {
	pctCHGB pchgbuf;	/* [IN] Data operation details		  */
	pctFILH	pfilhnd;	/* [IN] File information		  */
} rxDATOP, *prxDATOP;

/* Parameters for exceptions: */

#define RX_EXCOP_VER1		1
#define RX_EXCOP_VERSION	RX_EXCOP_VER1 /* current version of rxEXCOP  */

typedef struct _rxexcop {
	LONG	errcod;		/* [IN] Error code */
	pctCHGB pchgbuf;	/* [IN] Operation that failed */
	pctFILH	pfilhnd;	/* [IN] File information */
} rxEXCOP, *prxEXCOP;

/* Parameters for all events: */

#define RX_EVENT_VER1		1
#define RX_EVENT_VERSION	RX_EVENT_VER1 /* current version of rxEVENT  */

typedef struct _rxevent {
	LONG	versn;		   /* [IN] version of this structure	     */
	LONG	errcod;		   /* [IN] Error code			     */
	pctCNXH	psrccnxhnd;	   /* [IN] Source server connection handle   */
	pctCNXH	ptgtcnxhnd;	   /* [IN] Target server connection handle   */
	pVOID	pusrctx;	   /* [OUT] User context pointer	     */
	RXACT	action;		   /* [OUT] Set to action to take	     */
	union {
		rxVEROP verop;	   /* [IN] Parameters for version check	     */
		rxFILOP filop;     /* [IN] Parameters for file events	     */
		rxTRNOP trnop;     /* [IN] Parameters for transaction events */
		rxDATOP datop;     /* [IN] Parameters for data events	     */
		rxEXCOP excop;     /* [IN] Parameters for exceptions	     */
	} ev;
	TEXT	unqid[UNQIDLEN+1]; /* [IN] Replication agent unique ID	     */
	TEXT	srcsvn[MAX_SERVER_NAME]; /* [IN] Name of source c-tree Server */
	TEXT	tgtsvn[MAX_SERVER_NAME]; /* [IN] Name of target c-tree Server */
	TEXT	srcnodeid[IDZ];    /* [IN] Expected node ID of source server */
	TEXT	tgtnodeid[IDZ];    /* [IN] Expected node ID of target server */
} rxEVENT, *prxEVENT;

/*
   To add a new event callback:

   1) Add a new event identifier using the current value of RXF_TOTAL to the
      RXEVT enumerated data type list. The new event identifier can be added
      in any position in EXEVT, but do not renumber the existing event
      identifiers, because code in an external library might expect these
      values to be consistent between releases.
   2) Increment RXF_TOTAL.
   3) Add the new callback function name to the end of the rxLibFuncNames array.
*/

/* External library events: */
typedef enum _rxevt {
	/* Replication agent state change events: */
	RXF_OnStartAgent		= 0,
	RXF_OnSourceConnected		= 1,
	RXF_OnTargetConnected		= 2,
	RXF_OnSourceLostConnection	= 3,
	RXF_OnTargetLostConnection	= 4,
	RXF_OnSourceDisconnected	= 5,
	RXF_OnTargetDisconnected	= 6,
	RXF_OnTerminateAgent		= 7,
	RXF_OnPauseAgent		= 8,
	RXF_OnResumeAgent		= 9,
	RXF_OnStopAgent			= 10,

	/* File events: */
	RXF_OnOpenFile			= 11,
	RXF_AfterOpenFile		= 12,
	RXF_OnCloseFile			= 13,
	RXF_OnAlterSchema		= 14,
	RXF_OnResyncFile		= 25,
	RXF_OnPTADMIN			= 26,
	RXF_OnTruncateFile		= 27,
	RXF_OnCREIFIL			= 28,
	RXF_OnSETDEFBLK			= 29,
	RXF_OnCreateIndex		= 30,
	RXF_OnDeleteFile		= 34,
	RXF_OnDropIndex			= 35,
	RXF_OnRENIFIL			= 36,
	RXF_OnAddIdField		= 37,
	RXF_OnDelIdField		= 38,
	RXF_OnResetIdField		= 39,
	RXF_OnXtdatrIdField		= 40,
	RXF_OnCreateDataFile		= 41,
	RXF_OnDeleteDataFile		= 42,

	/* Transaction events: */
	RXF_OnStartTransaction		= 15,
	RXF_OnCommitTransaction		= 16,
	RXF_OnAbortTransaction		= 17,
	RXF_OnUserTransaction		= 18,
	RXF_OnCheckpoint		= 19,

	/* Data events: */
	RXF_OnAddRecord			= 20,
	RXF_OnUpdateRecord		= 21,
	RXF_OnDeleteRecord		= 22,
	RXF_OnDeferredKey		= 23,
	RXF_OnAddResource		= 31,
	RXF_OnUpdateResource		= 32,
	RXF_OnDeleteResource		= 33,

	/* Exception events: */
	RXF_OnException			= 24
} RXEVT;

#define RXF_TOTAL			43 /* Total number of events */

/* Name of the functions exported by the external library. Those functions that
are prefixed with ? are optional. */
pTEXT rxLibFuncNames[] = {
	"rxOnStartAgent",
	"?rxOnSourceConnected",
	"?rxOnTargetConnected",
	"?rxOnSourceLostConnection",
	"?rxOnTargetLostConnection",
	"?rxOnSourceDisconnected",
	"?rxOnTargetDisconnected",
	"?rxOnTerminateAgent",
	"?rxOnPauseAgent",
	"?rxOnResumeAgent",
	"?rxOnStopAgent",
	"?rxOnOpenFile",
	"?rxAfterOpenFile",
	"?rxOnCloseFile",
	"?rxOnAlterSchema",
	"?rxOnStartTransaction",
	"?rxOnCommitTransaction",
	"?rxOnAbortTransaction",
	"?rxOnUserTransaction",
	"?rxOnCheckpoint",
	"?rxOnAddRecord",
	"?rxOnUpdateRecord",
	"?rxOnDeleteRecord",
	"?rxOnDeferredKey",
	"?rxOnException",
	"?rxOnResyncFile",
	"?rxOnPTADMIN",
	"?rxOnTruncateFile",
	"?rxOnCREIFIL",
	"?rxOnSETDEFBLK",
	"?rxOnCreateIndex",
	"?rxOnAddResource",
	"?rxOnUpdateResource",
	"?rxOnDeleteResource",
	"?rxOnDeleteFile",
	"?rxOnDropIndex",
	"?rxOnRENIFIL",
	"?rxOnAddIdField",
	"?rxOnDelIdField",
	"?rxOnResetIdField",
	"?rxOnXtdatrIdField",
	"?rxOnCreateDataFile",
	"?rxOnDeleteDataFile"

	/* Add new function names here */
};

typedef TEXT checkSizeOfRxLibFuncNamesArray[sizeof(rxLibFuncNames) / sizeof(*rxLibFuncNames) == RXF_TOTAL];

typedef VOID (*pRXFNCP)(prxEVENT prxagentev);
pRXFNCP rxLibFuncPtrs[RXF_TOTAL];

	/* Agent state change events: */
extern rxEXPORT VOID rxOnStartAgent(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnSourceConnected(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnTargetConnected(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnSourceLostConnection(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnTargetLostConnection(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnSourceDisconnected(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnTargetDisconnected(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnTerminateAgent(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnPauseAgent(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnResumeAgent(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnStopAgent(prxEVENT prxagentev);

	/* File events: */
extern rxEXPORT VOID rxOnOpenFile(prxEVENT prxagentev);
extern rxEXPORT VOID rxAfterOpenFile(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnCloseFile(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnAlterSchema(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnResyncFile(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnPTADMIN(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnTruncateFile(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnCREIFIL(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnSETDEFBLK(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnCreateIndex(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnDeleteFile(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnDropIndex(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnRENIFIL(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnAddIdField(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnDelIdField(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnResetIdField(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnXtdatrIdField(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnCreateDataFile(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnDeletDataFile(prxEVENT prxagentev);

	/* Transaction events: */
extern rxEXPORT VOID rxOnStartTransaction(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnCommitTransaction(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnAbortTransaction(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnUserTransaction(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnCheckpoint(prxEVENT prxagentev);

	/* Data events: */
extern rxEXPORT VOID rxOnAddRecord(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnUpdateRecord(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnDeleteRecord(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnDeferredKey(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnAddResource(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnUpdateResource(prxEVENT prxagentev);
extern rxEXPORT VOID rxOnDeleteResource(prxEVENT prxagentev);

	/* Exception events: */
extern rxEXPORT VOID rxOnException(prxEVENT prxagentev);

/* end of ctrepluser.h */
