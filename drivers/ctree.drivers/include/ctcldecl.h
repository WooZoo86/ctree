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

#ifndef __TCLctdecl

#define PKG_VERSION "7.12.02"
#define __TCLctdecl
#define TCLFUN(x) int x (ClientData clientData, Tcl_Interp *interp,int objc, Tcl_Obj * const objv[])

TCLFUN(FairCom);
TCLFUN(FairComCmd);

TCLFUN(ctSession);
TCLFUN(ctSessionCmd);
void ctSessionDel(ClientData clientData); 

TCLFUN(ctDatabase);
TCLFUN(ctDatabaseCmd);
void ctDatabaseDel(ClientData clientData); 

TCLFUN(ctTable);
TCLFUN(ctTableCmd);
void ctTableDel(ClientData clientData); 

TCLFUN(ctRecord);
TCLFUN(ctRecordCmd);
void ctRecordDel(ClientData clientData);

TCLFUN(CTGetDef);
//TCLFUN(automatic);
//TCLFUN(ctmodel);
TCLFUN(ListValid);
TCLFUN(CTReset);
TCLFUN(CTSymb);

/*internal use only functions */
int base (int index, ClientData clientData, Tcl_Interp *interp,int objc, Tcl_Obj * const objv[]);
CTBOOL Hash_init();
CTBOOL _def (Tcl_Interp *interp, CTDefTypes type, char *key, int &value);
CTBase *GetClientData(Tcl_Interp *interp,DString &name); //get the clientdata from a command 
DString GetCommandName(CTBase *v);	//get the command name from clientdata
CTBOOL CanOr (CTDefTypes type);
DString _value(CTDefTypes cmdidx,int value);

#define RECORD_FIRST	0
#define RECORD_INIT	1
#define RECORD_NORMAL	2
#define CT_MIN_SECT 1
#define CT_MAX_SECT 1024
#endif /*__TCLctdecl*/

/* end of ctcldecl.h */

