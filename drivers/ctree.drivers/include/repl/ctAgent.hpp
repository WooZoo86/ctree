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
 *      Copyright (c) 2013 - 2020 FairCom Corporation.
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
 */

#ifndef _CTAGENT_HPP_
#define _CTAGENT_HPP_

#include "fcrcesaux.hpp"
#include "ctplugin.h"
#include "fcrcesreplplan.hpp"
#include "fcrcesrecblock.hpp"
#include "fcrcesaction.hpp"

typedef enum
{
	AGENT_START = 0,
	AGENT_STARTED = 1,
	AGENT_STOP = 2,
	AGENT_STOPED = 3
} AgentState;

typedef struct ctagentthd {
	AgentState state;

	pCTPLUGINDATA ctPluginData;

	char *logfile;
	char *memphistype;
	char *memphisname;
	char *memphissqlport;
	char *memphishost;
	char *memphisdb;
	int memphismaxconn;

	int qthrdcount;
	int ctcheck;
	char *ctcheckmask;
	int dbcheck;
	int verscancount;
	int vershowname;
	int connpoolsize;
	int scanthrdcount;
	int loadthrdcount;
	int advfullmask;
	int trace;
	int webtrace;
	char *byip;
	int acceptconn;
	char *jvmLibPath;

	int managed;
	char *cfgFileList;
} CTAGENTTHD, * pCTAGENTTHD;

/* call plugin modes */
typedef enum ctAgentPluginOption_t {

	/* Availability Group options */
	GET_SERVER_LIST = 1, /* get the server list */

	/* Web server options */
	UPD_LOCAL_WEB_SERVER = 10
} ctAGENT_PLUGIN_OPTION;

#define SITE "local"

typedef short int(*p_ctrcvlog)(char *, int);
extern p_ctrcvlog agentlog;

/* Ops Manager agent export symbols */
extern "C" rcesEXPORT int ctPlugin_init(p_ctrcvlog ctLogger, const char *path);
extern "C" rcesEXPORT int ctPlugin_term();
extern "C" rcesEXPORT int ctPlugin_start(pCTPLUGINDATA ctPluginData);
extern "C" rcesEXPORT int ctPlugin_stop();
extern "C" rcesEXPORT int ctPlugin_call(int operation, const char *input, char *output, int *outputSize);

void EmbLog(const char *msg, int errCd);

#endif /* _CTAGENT_HPP_ */