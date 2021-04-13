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

#ifndef _CTMEMGRIDNODE_HPP_
#define _CTMEMGRIDNODE_HPP_

#include "fcrcesaux.hpp"

#ifdef ctFeatMEMGRID

#include <jni.h>

#define CTMEMGRIDNODE_PATH "-Djava.class.path=./classes/ctMemGrid.jar;./classes/hazelcast-3.11.jar"
#define CTMEMGRIDNODE_CLASSNAME "com/faircom/ctMemGrid"
#define CTMEMGRIDNODE_INITFUNCNAME "init"
#define CTMEMGRIDNODE_TERMFUNCNAME "term"
#define CTMEMGRIDNODE_INITFUNCARGS "(Ljava/lang/String;III)I"
#define CTMEMGRIDNODE_TERMFUNCARGS "(Ljava/lang/String;)V"

#define CTMEMGRIDNODE_JNICREATEJMV "JNI_CreateJavaVM"
#define CTMEMGRIDNODE_JNIGETJMVS   "JNI_GetCreatedJavaVMs"

/* Class type definitions */
class CTMemGridNode;
class RCESLogger;
typedef CTMemGridNode *pCTMemGridNode, **ppCTMemGridNode;
typedef RCESLogger *pRCESLogger, **ppRCESLogger;

/*^****************************************************************************\
*
*   CTMemGridNode
*   FairCom's memory grid node class
*
\******************************************************************************/
class CTMemGridNode
{
public:
	/* Constructors & destructor */
	CTMemGridNode(FCPool<RCESMasterConnPooled> *masterConnPool, const char *groupName, int DBEngineID, int heartbeatFrequency, int heartbeatTimeout, const char *jvmLibName);
	virtual ~CTMemGridNode();

	/* Public methods */
	int GetPort() { return _port; };

private:
	/* Private properties */
	FCPool<RCESMasterConnPooled> *_masterConnPool; /* Connection pool */
	JavaVM *_jvm;           /* Pointer to the JVM (Java Virtual Machine) */
	int _port;              /* Hazelcast port number */
	char *_groupName;       /* Group name */
	int _dbEngineID;        /* DBEngine identification */
	int _heartbeatFrequency;
	int _heartbeatTimeout;

	/* private methods */
	void _loadJVM(const char *jvmLibName);
	JNIEnv *_getEnv();
	void _loadCTMemGridNode();
	void _unloadCTMemGridNode();
};
/*~****************************************************************************/

#endif /* ctFeatMEMGRID */

#endif /* _CTMEMGRIDNODE_HPP_ */