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
 
#include <jni.h>
/* Header for class ctree_jdbc_ctSHMjni */

#ifndef _Included_ctree_jdbc_ctSHMjni
#define _Included_ctree_jdbc_ctSHMjni
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     ctree_jdbc_ctSHMjni
 * Method:    createSocketID
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_ctree_jdbc_ctSHMjni_createSocketID
  (JNIEnv *, jclass);

/*
 * Class:     ctree_jdbc_ctSHMjni
 * Method:    connect
 * Signature: (JII)I
 */
JNIEXPORT jint JNICALL Java_ctree_jdbc_ctSHMjni_connect
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     ctree_jdbc_ctSHMjni
 * Method:    receive
 * Signature: (JLjava/nio/ByteBuffer;I)I
 */
JNIEXPORT jint JNICALL Java_ctree_jdbc_ctSHMjni_receive
  (JNIEnv *, jclass, jlong, jobject, jint);

/*
 * Class:     ctree_jdbc_ctSHMjni
 * Method:    send
 * Signature: (JLjava/nio/ByteBuffer;I)I
 */
JNIEXPORT jint JNICALL Java_ctree_jdbc_ctSHMjni_send
  (JNIEnv *, jclass, jlong, jobject, jint);

/*
 * Class:     ctree_jdbc_ctSHMjni
 * Method:    close
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_ctree_jdbc_ctSHMjni_close
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
