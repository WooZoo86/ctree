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

#ifndef __TCLctCMDS
#define __TCLctCMDS

#include "ctclport.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctdbsdk.hpp>
#include <ctdbport.h>
#include "ctcllist.hpp"
#include "ctcllass.hpp"
#include "ctcldecl.h"

extern List <CTDatabase> *DatabaseList;
extern List <CTSession> *SessionList;
extern List <CTTable> *TableList;
extern List <CTRecord> *RecordList;
extern CTHash *CTdefines;

#define DEF_VAR	Tcl_Obj *retobj;

#define DEF_FIELD(key,value) if (!_def (interp,fields,key,value))  \
				return TCL_ERROR;

#define DEF_DATE(key,value) if (!_def (interp,datet,key,value))  \
				return TCL_ERROR;

#define DEF_TIME(key,value) if (!_def (interp,timet,key,value))  \
				return TCL_ERROR;

#define DEF_PARAM(key,value) if (!_def (interp,sessparam,key,value))  \
				return TCL_ERROR;

#define DEF_INDEX(key,value) if (!_def (interp,indx,key,value))  \
				return TCL_ERROR;

#define DEF_SEGM(key,value) if (!_def (interp,segm,key,value))  \
				return TCL_ERROR;

#define DEF_CREAT(key,value) if (!_def (interp,tabcre,key,value))  \
				return TCL_ERROR;

#define DEF_OPEN(key,value) if (!_def (interp,tabopn,key,value))  \
				return TCL_ERROR;

#define DEF_LOCK(key,value) if (!_def (interp,locks,key,value))  \
				return TCL_ERROR;

#define DEF_ALTER(key,value) if (!_def (interp,alter,key,value))  \
				return TCL_ERROR;

#define DEF_FIND(key,value) if (!_def (interp,find,key,value))  \
				return TCL_ERROR;

#define DEF_BEGIN(key,value) if (!_def (interp,begin,key,value))  \
				return TCL_ERROR;

#define DEF_COMMIT(key,value) if (!_def (interp,commit,key,value))  \
				return TCL_ERROR;

#define RETURNERR(x)	{ retobj= Tcl_GetObjResult(interp); \
			Tcl_SetIntObj(retobj,x); \
			return TCL_ERROR; }

#define RETURNSTRERR(x)	{ retobj= Tcl_GetObjResult(interp); \
			Tcl_SetStringObj(retobj,x,-1); \
			return TCL_ERROR; }

#define TRY(x)	try { \
			x;\
		}\
		catch (CTException &_err_) { \
			RETURNERR(_err_.GetErrorCode()); \
		}


#define RETURNINT(x)	{ retobj= Tcl_GetObjResult(interp); \
			Tcl_SetIntObj(retobj,x); \
			return TCL_OK; }

#define RETURNUINT(x)	RETURNINT(x);

#define RETURNLONG(x)	{ retobj= Tcl_GetObjResult(interp); \
			Tcl_SetLongObj(retobj,x); \
			return TCL_OK; }

#define RETURNULONG(x)	RETURNLONG(x)

#define RETURNBOOL(rv)  { retobj= Tcl_GetObjResult(interp); \
			Tcl_SetBooleanObj(retobj,rv); \
			return TCL_OK;}

#define RETURNVRLEN(x)	RETURNLONG(x)

#define UNKNOW 	{ retobj= Tcl_GetObjResult(interp); \
		Tcl_SetStringObj(retobj, "unknown command",-1);\
		return TCL_ERROR; }

#define ARG_ERR(x) { Tcl_WrongNumArgs(interp, 1,objv,x);\
		return TCL_ERROR; }

#define CMD_ARG(x) { Tcl_WrongNumArgs(interp, 2,objv,x);\
		return TCL_ERROR; }

#define IMPLEMENT { retobj= Tcl_GetObjResult(interp); \
		Tcl_SetStringObj(retobj,"not yet implemented",-1);\
		return TCL_ERROR; }

#define ADDERR { retobj= Tcl_GetObjResult(interp); \
		Tcl_SetStringObj(retobj,"Cannot add to the internal list",-1);\
		return TCL_ERROR; }

//#define BASE return ( base(cmdidx,clientData,interp,objc,objv) );

#define WRONGPAR { Tcl_WrongNumArgs(interp, 2,objv,"unknown List type");\
		return TCL_ERROR; }

#define BASECMD "abort","begin","clearerror","commit","getdefdatetype","getdeffloatformat",\
		"getdeftimetype","geterror","istranactive","lock","restoresavepoint",\
		"setdefdatetype","setdeffloatformat","setdeftimetype","setsavepoint","unlock"

#define BASEFN Abort,Begin,ClearError,Commit,GetDefDateType,GetDefFloatFormat,\
			GetDefTimeType,GetError,IstranActive,Lock,RestoreSavePoint,SetDefDateType,\
			SetDefFloatFormat,SetDefTimeType,SetSavePoint,UnLock

#endif //__TCLctCMDS

/* end of ctclcmds.h */

