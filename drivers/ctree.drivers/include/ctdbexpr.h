/*
 * regcomp and regexec
 *
 *	Copyright (c) 1986 by University of Toronto.
 *	Written by Henry Spencer.  Not derived from licensed software.
 *
 *	Permission is granted to anyone to use this software for any
 *	purpose on any computer system, and to redistribute it freely,
 *	subject to the following restrictions:
 *
 *	1. The author is not responsible for the consequences of use of
 *		this software, no matter how awful, even if they arise
 *		from defects in it.
 *
 *	2. The origin of this software must not be misrepresented, either
 *		by explicit claim or by omission.
 *
 *	3. Altered versions must be plainly marked as such, and must not
 *		be misrepresented as being the original software.
 ***
 *** THIS IS AN ALTERED VERSION.  It was altered by John Gilmore,
 *** hoptoad!gnu, on 27 Dec 1986, to add \n as an alternative to |
 *** to assist in implementing egrep.
 ***
 *** THIS IS AN ALTERED VERSION.  It was altered by John Gilmore,
 *** hoptoad!gnu, on 27 Dec 1986, to add \< and \> for word-matching
 *** as in BSD grep and ex.
 ***
 *** THIS IS AN ALTERED VERSION.  It was altered by John Gilmore,
 *** hoptoad!gnu, on 28 Dec 1986, to optimize characters quoted with \.
 ***
 *** THIS IS AN ALTERED VERSION.  It was altered by James A. Woods,
 *** ames!jaw, on 19 June 1987, to quash a regcomp() redundancy.
 ***
 *** THIS IS AN ALTERED VERSION. It was altered by Ricardo Machado
 *** on 21 Jul 2000, to add a new interface for FairCom CTDB SDK
 *** the header file was rename to ctdbexpr.h and the source file
 *** regexp.c was renamed to ctdbexpr.c
 *
 */
#ifndef _REGEXP_H_
#define _REGEXP_H_
/******************************************************************************\
*
*	Header files
*
\******************************************************************************/
#include "ctdbsdk.h"
#include "ctdbport.h"
#include <ctype.h>

/******************************************************************************\
*
*	Guard against C++ compilers
*
\******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************\
*
*	Regular expression
*
\******************************************************************************/
#define NSUBEXP  10

enum RXERR
{
	RXERR_NONE,				/*  0 - No error detected */
	RXERR_NULL,				/*  1 - NULL pointer passed */
	RXERR_TOOBIG,			/*  2 - Regular expression too big */
	RXERR_NOMEMORY,			/*  3 - Out of heap space */
	RXERR_TOOMANYPAR,		/*  4 - Too many parenthesis () */
	RXERR_MISSINGPAR,		/*  5 - Unmatched parenthesis () */
	RXERR_JUNK,				/*  6 - Junk on end of expression */
	RXERR_EMPTY,			/*  7 - *+ operand could be empty */
	RXERR_NESTED,			/*  8 - nested *?+ */
	RXERR_INVRANGE,			/*  9 - invalid [] range */
	RXERR_MISSINGBRACKET,	/* 10 - Unmatched [] bracket */
	RXERR_NOTHING,			/* 11 - ?+* follows nothing */
	RXERR_TRAILING,			/* 12 - Trailing \\ */
	RXERR_CORRUPTED,		/* 13 - corrupted program */
	RXERR_BADMEMORY,		/* 14 - memory corruption */
	RXERR_BADPOINTER,		/* 15 - corrupted pointer */
	RXERR_BADOPCODE,		/* 16 - corrupted opcode */
	RXERR_NOMATCH,			/* 17 - No matched string */
	RXERR_SIZE,				/* 18 - Size of destination string too small */
	RXERR_INDEX,			/* 19 - Invalid index */

	RXERR_INTERNAL			/* Internal error detected */
};

typedef struct _regexp	_regexp;

typedef struct regexp
{
	_regexp* prog;
	char*	Text[ NSUBEXP ];
	int	reg_err;
	char	*reg_parse;
	int	reg_npar;
	char	reg_dummy;
	char	*reg_code;
	long	reg_size;
	char	*reg_input;		
	char	*reg_bol;		
	char	**reg_startp;	
	char	**reg_endp;		

} regexp;

#ifdef PROTOTYPE
regexp* ctdb_regnew( void );
void ctdb_regfree( regexp* regx );
int ctdb_regcomp( regexp* regx, char* string );
int ctdb_regexec( regexp* regx, char* string );
char* ctdb_regtext( regexp* regx, int index );
int ctdb_regerror( regexp* regx );
#else
regexp* ctdb_regnew();
void ctdb_regfree();
int ctdb_regcomp();
int ctdb_regexec();
char* ctdb_regtext();
int ctdb_regerror();
#endif

/******************************************************************************/
#ifdef __cplusplus
}
#endif
/******************************************************************************/
#endif /* _REGEXP_H_ */
/******************************************************************************/

/* end of ctdbexpr.h */

