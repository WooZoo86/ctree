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

#ifndef _CTDBXMLI_H_
#define _CTDBXMLI_H_

#include "ctdbxmlp.h"

typedef struct
{
	NINT	idxno;		/* number of indices */
	NINT	segno;		/* number of segments */
	NINT	fldno;		/* number of fields */
	NINT	isize;		/* size of strings in table, index and segment */
	NINT	dsize;		/* size of strings in fields */
	pUTEXT 	buffer;		/* pointer to buffer */
	pIFIL	ifilptr;	/* pointer to IFIL */
	pIIDX	iidxptr;	/* pointer to IIDX */
	pISEG	isegptr;	/* pointer to ISEG */
	pTEXT	istrptr;	/* pointer to next string in IFIL */
	pDATOBJ	dodaptr;	/* pointer to DODA */
	pTEXT	dstrptr;	/* pointer to next string in DODA */
	NINT	idxindex;	/* index to IIDX */
	NINT	segindex;	/* index to ISEG */
	NINT	fldindex;	/* index to DODA */
} CTXMLTAG, *pCTXMLTAG;

typedef struct
{
	char*	str;		/* mode name */
	UINT	mode;		/* mode value */
} CTXMLMODE, *pCTXMLMODE;

/****************************************************************************\
*
*	ctxmlCallback
*	Type of callback function that each node will call
*
\****************************************************************************/
#ifdef PROTOTYPE
typedef NINT (*ctxmlCallback)(pCTXMLNODE Node, CTXMLTYPE type, pTEXT name, pTEXT value, NINT level);
#else
typedef NINT (*ctxmlCallback)();
#endif

#endif /* ~_CTDBXMLI_H_ */

/* end of ctdbxmli.h */
