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

#ifndef _CTDBXMLP_H_
#define _CTDBXMLP_H_

/****************************************************************************\
*
*	header files
*
\****************************************************************************/
#include "ctstdr.h"
#include "ctoptn.h"
#include "ctstrc.h"
#include "ctdecl.h"

/****************************************************************************\
*
*	C RTL functions used by the parser
*
\****************************************************************************/
#define ctxmlSTRCAT		strcat
#define ctxmlSTRLEN		strlen
#define ctxmlSTRCPY		strcpy
#define ctxmlSTRCMP		strcmp
#define ctxmlSTRICMP	ctrt_stricmp
#define ctxmlMEMCPY		memcpy
#define ctxmlMEMCMP		memcmp
#define ctxmlMEMSET		memset
#define ctxmlSPRINTF	sprintf
#define ctxmlSEEK		fseek
#define ctxmlTELL		ftell
#define ctxmlOPEN		fopen
#define ctxmlCLOSE		fclose
#define ctxmlREAD		fread
#define ctxmlATOI		atoi
#define ctxmlATOF		atof

#ifdef ctSRVR
#ifndef mballc
extern pTEXT mballc(NINT, UINT);
extern VOID mbfree(pVOID objptr);
#endif
#define ctxmlMALLOC(siz)	(pVOID)mballc(1, (UINT) siz)
#define ctxmlFREE(ptr)		mbfree(ptr)
#else
#define ctxmlMALLOC(siz)	malloc(siz)
#define ctxmlFREE(ptr)		free(ptr)
#endif

#ifndef YYMALLOC
#define YYMALLOC ctxmlMALLOC
#endif
#ifndef YYFREE
#define YYFREE ctxmlFREE
#endif
/****************************************************************************\
*
*	Constants used by fseek
*
\****************************************************************************/
#ifndef SEEK_SET
#define SEEK_SET		0
#endif

#ifndef SEEK_END
#define SEEK_END		2
#endif

/****************************************************************************\
*
*	lex state
*
\****************************************************************************/
typedef enum
{
	CTXMLSTATE_CONTENT,	
	CTXMLSTATE_TAG		
} CTXMLSTATE;

/****************************************************************************\
*
*	XML parser stack size. This is the number of nested element levels
*	allowed.
*
\****************************************************************************/
#define CTXML_STACKSIZE	32

/****************************************************************************\
*
*   Protect against C++ compilers
*
\****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************\
*
*	CTXMLTYPE
*	Type of XML nodes on parsed tree
*
\****************************************************************************/
typedef enum
{
	CTXML_BEGIN,
	CTXML_ATTRIBUTE,
	CTXML_CONTENT,
	CTXML_END
} CTXMLTYPE;

typedef struct tagCTXML		CTXML, *pCTXML, **ppCTXML;

/****************************************************************************\
*
*	CTXMLNODE
*	Definition of each parsed XML node.
*
\****************************************************************************/
typedef struct tagCTXMLNODE
{
	CTXMLTYPE	type;			/* node type								*/
	pTEXT		name;			/* element or parameter name				*/
	pTEXT		value;			/* parameter value or text content			*/
	NINT		root;			/* indicate if root node					*/
	NINT		empty;			/* node is an empty element					*/
	struct tagCTXMLNODE *parent;/* pointer to parent node (element)			*/
	struct tagCTXMLNODE *next;	/* next element or content					*/
	struct tagCTXMLNODE *child;	/* list of child elements or contents		*/
	struct tagCTXMLNODE *attr;	/* list of attributes for this element		*/
	pVOID		usertag;		/* user tag									*/
	pCTXML		handle;			/* XML parser handle						*/	
	NINT		lineno;			/* lineno were the token as declared		*/
	NINT		colno;			/* column number of the token				*/
} CTXMLNODE, *pCTXMLNODE;

/****************************************************************************\
*
*	CTXML
*	c-tree XML handle
*
\****************************************************************************/
struct tagCTXML
{
	pTEXT		instr;		/* input text to be parsed						*/
	NINT		size;		/* size in bytes of input text					*/
	NINT		index;		/* location where input text is being read		*/
	NINT		start;		/* start position of current token				*/
	NINT		count;		/* size in bytes of current token				*/ 
	NINT		state;		/* state of lex. Default is CTXMLSTATE_CONTENTS	*/
	TEXT		errmsg[256];/* error message buffer							*/
	NINT		errflag;	/* error flag: >0 indicate errors				*/
	NINT		lineno;		/* line number of the offending token			*/
	NINT		colno;		/* column number of the offending token			*/
	pTEXT		stack[CTXML_STACKSIZE]; /* element name stack				*/
	NINT		stackptr;	/* element name stack pointer					*/
	NINT		toptag;		/* root element already seen					*/
	pCTXMLNODE	tree;		/* output parse tree of XML document			*/
	pCTXMLNODE	ptr;		/* temporary variable for building the tree		*/
	pVOID		usertag;	/* user tag										*/
};
/****************************************************************************/

#define DELETED_ATTRIB "1*_deleted_*1" /*DELETED_ATTRIB is a placeholder for delete attributes, so that they do not need to be purged before printing */

pCTXMLNODE ctxmlNewNode(pCTXML handle, CTXMLTYPE type, char* name, char* value);
void ctxmlFreeNode(pCTXMLNODE Node);
void ctxmlFree(pCTXML handle);
NINT ctxmlParser(ppCTXML pHandle, pTEXT buffer, NINT bufferLen);
NINT ctxmlFileParser(ppCTXML pHandle, pTEXT filename);
int ctxml_error(pCTXML handle, char* msg);
size_t ctxmlPrintXML(FILE * fp, pTEXT buf, size_t bufsize, pCTXMLNODE tree);
pTEXT ctxmlSTRDUP(cpTEXT str);

#ifdef __cplusplus
}
#endif /* ~__cplusplus */

#endif /* ~_CTDBXMLP_H_ */

/* end of ctdbxmlp.h */
