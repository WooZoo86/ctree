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

/***********************************************************************/
#ifndef CTPLUGIN_H
#define CTPLUGIN_H

#define CTPLUGIN_DATA_VERSION 1

#define CTPLUGIN_MAX_NAME 1024

#define CTPLUGIN_CONFIG_DIR "config"

#define CTPLUGIN_CTAGENT_NAME "ctagent"
#define CTPLUGIN_CTHTTPD_NAME "cthttpd"

#ifdef ctPortWIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

typedef enum {
	ctPLUGIN_LIC_MODE_MEMPHISNODE = 1, /* ctAgent license (Memphis Node) */
	ctPLUGIN_LIC_MODE_HIGHAVAIL = 2,   /* High Availability license */
	ctPLUGIN_LIC_MODE_HTTPD = 3,       /* HTTPD license */
	ctPLUGIN_LIC_MODE_MQTT = 4,        /* MQTT license */
	ctPLUGIN_LIC_MODE_REST = 5,        /* REST license */
	ctPLUGIN_LIC_MODE_THINGWORX = 6,   /* Thingworx license */
	ctPLUGIN_LIC_MODE_OPC = 7,         /* OPC license */
	ctPLUGIN_LIC_MODE_TIMESTAMP = 8,   /* Timestamp (aggregation) license */
	ctPLUGIN_LIC_MODE_MEMGRID = 9      /* Memory Grid license */
} ctPLUGIN_LIC_MODE;

typedef int(*p_ctplugin_checkLicense)(ctPLUGIN_LIC_MODE);
int ctplugin_checkLicense(ctPLUGIN_LIC_MODE mode);

typedef struct tag_pluginData {
	int    version;     /* Plugin data version */
	int    isembed;     /* Plugin is running embedded in a server - some plugins can run also in standalone mode */
	char  *localPath;   /* Server's local path */
	char  *srvnam;      /* Server's name */
	char  *jvmLibName;  /* JVM library name */
	int   *readonly;    /* Server's readonly flag */
	int   *cttflg;      /* Flag indicating if the server is active or shutting down */
	void  *context;     /* Generic buffer for send and receive information from and to plugin */
	p_ctplugin_checkLicense  licenseCheckerFunc; /* License check function pointer */
} CTPLUGINDATA, *pCTPLUGINDATA;

typedef short int(*p_ctrcvlog)(char *, int);

typedef int(*p_ctplugin_init)(p_ctrcvlog, const char *);
typedef int(*p_ctplugin_term)(void);
typedef int(*p_ctplugin_start)(pCTPLUGINDATA);
typedef int(*p_ctplugin_stop)(void);
typedef int(*p_ctplugin_call)(int, const char *, char *, int *);

typedef struct tag_pluginFuncs {
	p_ctplugin_init  init;
	p_ctplugin_term  term;
	p_ctplugin_start start;
	p_ctplugin_stop  stop;
	p_ctplugin_call  call;
} CTPLUGINFUNCS;

typedef int(*p_callback_init)(void);
typedef int(*p_callback_term)(void);
typedef int(*p_callback_desc)(char *,size_t *,int);

struct callbackdesc {
	char * name;
	void * addr;
};

struct callableFuncs {
	p_callback_init init;   /* global scope init */
	p_callback_term term;   /* global scopre term */
	p_callback_desc describe;  /* describe functions number and names */
	struct callbackdesc * functions; /* callbackdesc array */
	size_t num; /* number of elements in functions */
};



typedef struct tag_plugin {
	char name[CTPLUGIN_MAX_NAME];
	char path[CTPLUGIN_MAX_NAME];
	union { 
		CTPLUGINFUNCS functions;
		struct callableFuncs cb;
	} u;
	void *handle;
	int type;
	int errorCd;
	pCTPLUGINDATA data;
} CTPLUGIN, *pCTPLUGIN;

typedef struct tag_plugin_list {
	CTPLUGIN * list;
	unsigned int count; /* number of elements */
	int (*load_fn)(pCTPLUGIN,char *);
	void (*unload_fn)(pCTPLUGIN);
} CTPLUGIN_LIST;

int ctplugin_load(int);
void ctplugin_unload(int);
DLLEXPORT pCTPLUGIN ctplugin_get(const char *pluginName);


#endif /* CTPLUGIN_H */
