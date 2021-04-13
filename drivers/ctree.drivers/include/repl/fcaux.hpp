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
 *      Copyright (c) 2013 - 2015 FairCom Corporation.
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

#ifndef _FCAUX_HPP_
#define _FCAUX_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "ctplatform.h"

#define FC_MAX_CONFIG_LEN 256
#define FC_MAX_ERRMSG_LEN 1024
#define FC_DATETIME_STRLEN 30
#define FC_MAX_PATH 1024
#define FC_CONN_POOL_SHRINK 5 /* Frequence of master connection pool cleanup check in seconds */
#define FC_BLOCK_SIZE 8192
#define FC_BUFFER_SIZE 1024

#define FCSize FCBigInt
#define FCDateTime time_t
#define FC_MAX_DATETIME ULONG_MAX

#define SEP '/'
#define NOT_SEP '\\'
#define SEPSTR "/"
#define NOT_SEPSTR "\\"
#define DOUBLE_SEP "//"

#ifdef CT_THINGWORX
#define TWRUC_NAME "ctthingworx.always-onRUC"
#endif

typedef enum {
	THRD_WAIT = 0,   /* Wait for the thread initilization  */
	THRD_RUN = 1,    /* RUN state  */
	THRD_STOP = 2,   /* STOP state */
	THRD_STOPED = 3, /* STOPED state */
	THRD_ERROR = 4,  /* Thread error */
	THRD_EXEC = 5    /* Thread execute */
} ThrdState, *pThrdState;

typedef struct ThrdData {
	int errorCd;
	char msg[FC_MAX_ERRMSG_LEN + 1];
	ThrdState state;
	void *context;
	void *mutex;
} ThrdData, *pThrdData, **ppThrdData;

typedef FC_FUNC_RET(FCAPI *FC_THRD_FUNCTION)(void *fcThrdParam);
typedef FC_THRD_FUNCTION pFC_THRD_FUNCTION;


/* String manipulation */
char *dupStr( const char *str );
void strToUpper( char *str );
int fcstricmp(const char *str1, const char *str2);
int fcstrnicmp(const char *str1, const char *str2, int len);
int fcstrcmp(const char *str1, const char *str2);
int fcstrncmp(const char *str1, const char *str2, int len);
bool CheckWildcard(const char *fileName, const char *mask);


/* Mutex */
void *fcMutexCreate();
void fcMutexFree(void *mutex);
FCULONG fcMutexGet(void *mutex, int waitTime = -1);
void fcMutexRel(void *mutex);


/* Thread */
void *fcThrdCreate(pFC_THRD_FUNCTION fcThrdFunction, void *fcThrdParam, bool detach = false);
void fcThrdFree(void *thrdHandle);
FCULONG fcThrdWait(void *thrdHandle);
void fcThrdWaitMulti(int thrdCount, void **thrdHandleList);
void fcSleep(int milliseconds);
FCBigInt fcGetCurrentThreadId();


/* File System */
typedef struct fcFileData {
	char name[FC_MAX_PATH + 1];
	bool isDir;
	FCSize size;
	FCDateTime createTime;
	FCDateTime updateTime;
} FCFileData, *pFCFileData, **ppFCFileData;

typedef struct fcFileFindHandle {
	void *findHandle;
	FCFileData fileData;
#ifndef _WINDOWS
	char *mask;
	char *path;
	char fileDirName[FC_MAX_PATH + 1];
#endif
} FCFileFindHandle, *pFCFileFindHandle, **ppFCFileFindHandle;

pFCFileFindHandle fcFindFileFirst(const char *dir);
void fcFindFileClose(pFCFileFindHandle fileFindHandle);
int fcFindFileNext(pFCFileFindHandle fileFindHandle);

pFCFileFindHandle fcFindDirFirst(const char *path);
void fcFindDirClose(pFCFileFindHandle dirFindHandle);
int fcFindDirNext(pFCFileFindHandle dirFindHandle);

void fcCheckDir(const char *path);
void fcDeleteFileDir(const char *path);
int fcMoveFile(const char *sourceFileName, const char *targetFileName);
void fcCopyFile(const char *sourceFileName, const char *targetFileName);
void fcValidatePath(char *path);
void fcValidateDrive(const char *volumeName);
bool fcCheckFile(char *fileName);
int fcComparePath(const char *path1, const char *path2, int len);
int fcGetCurrentDir(char *pathBuf, int bufLen);
int fcGetCurrentBinName(char *execName, int bufLen);

int fcGetHostName(char **hostName, char **errorMsg);

TIMER fcGetSysTimer();

#endif /* _FCAUX_HPP_ */