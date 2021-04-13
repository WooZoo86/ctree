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

#ifndef __CTDBCNDX_H
#define __CTDBCNDX_H
#ifndef ctPORTH
#include "ctstdr.h"
#include "ctoptn.h"
#include "ctstrc.h"
#endif /* ~ctPORTH */

#define CTDB_NOCTREEP
#include "ctdbsdk.h"

#ifdef ctCLIENT
#define getcndxmem(a)   mballc(1,(UINT)(a))
#define putcndxmem(a)   mbfree((pVOID)(a))
#define putcndxmemn(a)  mbfren((ppVOID)(a))
#define RES_msgsuppress 0
#define gcidx(a,b,c)    GETCRES(a,b,c)
#else
#define getcndxmem(a)   ctgetmem((VRLEN)(a))
#define putcndxmem(a)   ctputmem((pTEXT)(a))
#define putcndxmemn(a)  ctputmemn((ppVOID)(a))
#define RES_msgsuppress RES_SRVR
#define gcidx(a,b,c)    iGETCRES(a,b,c,NO)
#endif

#define	YYLMAX		CNDX_MAX_TOKEN	/* token and pushback buffer size */
#ifndef yy_state_t
#define yy_state_t NINT
#endif

struct LEXINST_S
{
	unsigned char* yyInput;
	int		yyInputSize;
	int		yyPointer;
	int		yylineno;
	int		yyleng;
	unsigned char	yytext[YYLMAX+1];
	yy_state_t	yy_sbuf[YYLMAX+1];
	int		yy_end;
	int		yy_start;
	int		yy_lastc;
	unsigned char 	yy_save;
};

#define CNDX_MAX_UINT           "4294967295"
#define CNDX_MAX_INT            "2147483674"

#ifdef ctFeatUDF_EXPR
#define UDF_FUNC_NBR            -1
#define UDF_MAX_STR             256
#endif

#define ERY_NONE                0       /* No errors detected */
#define ERY_SYNTAX              1       /* Syntax error detected */
#define ERY_TYPE                2       /* Invalid type mixup */
#define ERY_FIELD               3       /* Unknown field name */
#define ERY_INTERN              4       /* Internal yacc error */
#define ERY_MEMORY              5       /* Memory allocation failed */
#define ERY_OVERFLOW            6       /* Stack overflow */
#define ERY_UNDERFLOW           7       /* Stack Underflow */
#define ERY_EXEC                8       /* Invalid execution node */
#define ERY_DIVISION            9       /* Division by zero */
#define ERY_NOSCHEMA            10
#define ERY_NORECBUF            11
#define ERY_SDAT_ERR			12		/* not enough data */
#define ERY_FUNCTION			13		/* invalid function number */
#define ERY_ARGUMENT			14		/* invalid argument */
#define ERY_RUNTIME				15		/* runtime error */
#define ERY_NULL				16		/* NULL popped from stack */

enum PT_NODE_TYPES
{
	PT_NONE,
	
	/*
	 * special NULL type
	 */
	PT_NULL,

	/*
	 * other data types
	 */
	PT_BOOL,
	PT_UNSIGN,
	PT_MONEY,
	PT_BIGINT,
	PT_CURRENCY,
	PT_FLOAT,

	/*
	 * Data Fields
	 */
	PT_FIELD,
	
	/*
	 * Terminators
	 */
	PT_INTEGER,
	PT_DATE,
	PT_TIME,
	PT_TIMEMS, 
	PT_STAMP,
	PT_NUMBER,
	PT_TEXT,
	PT_VSET, 
	PT_UTF16,
	/* new one... remeber to update runtable in ctdbcrun.c*/
	PT_INFO,
	
	/*
	 * Actions
	 */
	PT_RECINFO,
	PT_CONSTANT,			/* push a constant to top of stack	*/
	PT_LOGOR,				/* logical OR on two variants		*/
	PT_LOGAND,				/* logical AND on two variants		*/
	PT_BINOR,				/* binary OR on two variants		*/
	PT_BINXOR,				/* binary XOR on two variants		*/
	PT_BINAND,				/* binary AND on two variants		*/
	PT_EQ,					/* relational EQ on two variants	*/
	PT_NE,					/* relational NE on two variants	*/
	PT_LT,					/* relational LT on two variants	*/
	PT_LE,					/* relational LE on two variants	*/
	PT_GT,					/* relational GT on two variants	*/
	PT_GE,					/* relational GE on two variants	*/
	PT_ADD,					/* math add on two variants			*/
	PT_SUB,					/* math subtract on two variants	*/
	PT_MUL,					/* math multiply on two variants	*/
	PT_DIV,					/* math divide on two variants		*/
	PT_MOD,					/* math modulus on two variants		*/
	PT_MINUS,				/* negate a numeric value			*/
	PT_PLUS,				/* make a numeric value positive	*/
	PT_BINNOT,				/* binary not on a variant			*/
	PT_LOGNOT,				/* logical not on a variant			*/
	PT_CAST,				/* type cast a variant variable		*/
	PT_FUNCTION,			/* perform a function call			*/
	PT_ARGUMENT,			/* function argument 				*/
	PT_ISNULL,				/* check if field is NULL			*/
	PT_NOTNULL,				/* chekc fi field is NOT NULL		*/
	
	PT_LAST
};

/* function numbers */
enum FN_NUMBERS
{
	FN_ABS, 			/*   0 */
	FN_ACOS, 			/*   1 */
	FN_ADD_DAYS,		/*   2 */
	FN_ADD_MONTHS, 		/*   3 */
	FN_ASCII, 			/*   4 */
	FN_ASIN, 			/*   5 */
	FN_ATAN, 			/*   6 */
	FN_ATOF, 			/*   7 */
	FN_ATOI, 			/*   8 */
	FN_ATOL, 			/*   9 */
	FN_CEIL, 			/*  10 */
	FN_CEILING, 		/*  11 */
	FN_CHAR, 			/*  12 */
	FN_CHR, 			/*  13 */
	FN_CONCAT, 			/*  14 */
	FN_CONVERT, 		/*  15 */
	FN_COS, 			/*  16 */
	FN_CURDATE, 		/*  17 */
	FN_CURTIME, 		/*  18 */
	FN_DAYNAME, 		/*  19 */
	FN_DAYOFMONTH, 		/*  20 */
	FN_DAYOFWEEK, 		/*  21 */
	FN_DAYOFYEAR, 		/*  22 */
	FN_EXP, 			/*  23 */
	FN_FABS, 			/*  24 */
	FN_FLOOR, 			/*  25 */
	FN_FMOD, 			/*  26 */
	FN_GREATEST, 		/*  27 */
	FN_HOUR, 			/*  28 */
	FN_INSERT, 			/*  29 */
	FN_INSTR,			/*  30 */
	FN_LABS, 			/*  31 */
	FN_LAST_DAY, 		/*  32 */
	FN_LCASE, 			/*  33 */
	FN_LEAST, 			/*  34 */
	FN_LEFT, 			/*  35 */
	FN_LENGTH, 			/*  36 */
	FN_LOCATE, 			/*  37 */
	FN_LOG10, 			/*  38 */
	FN_LOWER, 			/*  39 */
	FN_LPAD, 			/*  40 */
	FN_LTRIM, 			/*  41 */
	FN_MEMCMP, 			/*  42 */
	FN_MINUTE, 			/*  43 */
	FN_MOD, 			/*  44 */
	FN_MONTH, 			/*  45 */
	FN_MONTHNAME, 		/*  46 */
	FN_NOW, 			/*  47 */
	FN_PACK_DATE, 		/*  48 */
	FN_PACK_TIME, 		/*  49 */
	FN_PACK_TIMESTAMP, 	/*  50 */
	FN_PI, 				/*  51 */
	FN_POWER, 			/*  52 */
	FN_PREFIX, 			/*  53 */
	FN_QUARTER, 		/*  54 */
	FN_RAND, 			/*  55 */
	FN_REPEAT, 			/*  56 */
	FN_REPLACE, 		/*  57 */
	FN_RIGHT, 			/*  58 */
	FN_RPAD, 			/*  59 */
	FN_RTRIM, 			/*  60 */
	FN_SECOND, 			/*  61 */
	FN_SIGN, 			/*  62 */
	FN_SIN, 			/*  63 */
	FN_SPACE, 			/*  64 */
	FN_SQRT, 			/*  65 */
	FN_STRCMP, 			/*  66 */
	FN_STRICMP, 		/*  67 */
	FN_STRLEN, 			/*  68 */
	FN_STRNCMP, 		/*  69 */
	FN_STRNICMP, 		/*  70 */
	FN_SUBSTR, 			/*  71 */
	FN_SUBSTRING, 		/*  72 */
	FN_SUFFIX, 			/*  73 */
	FN_SYSDATE, 		/*  74 */
	FN_SYSTIME, 		/*  75 */
	FN_SYSTIMESTAMP,	/*  76 */
	FN_TAN, 		 	/*  77 */
	FN_UCASE, 		 	/*  78 */
	FN_UPPER, 		 	/*  79 */
	FN_WEEK, 		 	/*  80 */
	FN_YEAR, 		 	/*  81 */
	FN_MATCH, 		 	/*  82 */
	FN_MATCHI, 		 	/*  83 */
	FN_ROWID, 		 	/*  84 */
#ifdef ctFeatABL
	FN_ENTRY, 		 	/*  85 */
	FN_INDEX, 		 	/*  86 */
	FN_INDEXI, 		 	/*  87 */
	FN_LOOKUP, 		 	/*  88 */
	FN_LOOKUPI, 		/*  89 */
	FN_NUM_ENTRIES, 	/*  90 */
	FN_RINDEX, 			/*  91 */
	FN_RINDEXI, 		/*  92 */
	FN_REPLACEI, 		/*  93 */
	FN_ROUND, 			/*  94 */
	FN_TRIM, 			/*  95 */
	FN_TRUNCATE, 		/*  96 */
	FN_MAXSTR, 			/*  97 */
	FN_MAXSTRI, 		/*  98 */
	FN_MAXNBR, 			/*  99 */
	FN_MINSTR, 			/* 100 */
	FN_MINSTRI, 		/* 101 */
	FN_MINNBR, 			/* 102 */
#endif
	FN_FIELD, 			/* 103 */
	FN_BETWEEN, 		/* 104 */
	FN_BETWEENI, 		/* 105 (case insensitive)*/
	FN_SQLSTRCMP, 		/* 106 SQL compliant (ignore trailing spaces)*/
	FN_SQLSTRICMP, 		/* 107 SQL compliant (ignore trailing spaces)(case insensitive)*/
	FN_IN, 				/* 108 */
	FN_INI,				/* 109 (case insensitive)*/
	FN_TIMET2CTDATE,		/* 110 Convert Unix time_t to CT_DATE  */
	FN_TIMET2CTTIME,		/* 111 Convert Unix time_t to CT_TIME  */
	FN_TIMET2CTTIMES,	/* 112 Convert Unix time_t to CT_TIMES */
	FN_STRCMP_U,   /* 113 Unicode string compare using specified collator automatic conversion to utf-8 in case of mixed encoding */
	FN_SQLSTRCMP_U8,   /* 114 UTF8 string compare using specified collator, SQL compatible ignore trailing spaces */
	FN_SQLSTRCMP_U16,  /* 115 UTF16 string compare using specified collator, SQL compatible ignore trailing spaces */
	/* when adding here remeber to upgrade the FunName array in ctdbcrun.c */
	FN_LAST				/* last function number marker */
};

/* User Defined Function type */
#ifdef ctFeatUDF_EXPR
typedef struct UDF_S UDF, ctMEM *pUDF, ctMEM * ctMEM *ppUDF;
#endif

/* Symbol table entry */
typedef struct
{
	pTEXT	name;			/* symbol name */
	NINT	val;			/* value associated with name */
	NINT	minargs;		/* minimum number of arguments if function */
	NINT	maxargs;		/* maximum number of arguments if function */
	NINT	retype;			/* return type if function */
	NINT	fnbr;			/* function number, if function */
#ifdef ctFeatUDF_EXPR
	/* REVISIT - it migth be better to have the list of symbols table (symtab) populated dynamically,
                 then UDF symbols could be simply added to this table. For now, only to avoid major
                 impacts in the general expression evaluation, UDF info are kept in an extra table */
	pUDF	udf;			/* UDF's pointer */
#endif
} CTSYMBOL, ctMEM* pCTSYMBOL;

typedef struct LEXINST_S*       LEXINST;
typedef struct PTREE_S*         PTREE;
typedef struct tagRECINFO		RECINFO, ctMEM* pRECINFO;

typedef struct PLEAF_U
{
	NINT	vtype;			/* PT_INTEGER, PT_DATE, PT_TIME, PT_STAMP, PT_NUMBER, PT_TEXT, PT_INFO, PT_NULL */
	NINT	set_offset;		/* in case of PT_VSET the number of set element in use */
	VRLEN	len;			/* number of bytes in Text (or max number of set elements) */
	TEXT	byref;			/* Text is by reference (in case of PT_VSET the current available position) */
	TEXT	isbin;			/* indicate if string is binary or nor */
	union
	{
		LONG8    Signed;
		ULONG   Unsign;
		pTEXT   Text;
		UINT    Offset;
		CTDATE	Date;
		CTTIME	Time;
		CTDATETIME Stamp;
		CTNUMBER Number;
		pRECINFO recinfo;
		struct PLEAF_U *set_elem;
	} var;
#ifdef ctFeatUDF_EXPR
	pUDF	udf;			/* UDF's pointer */
#endif
} PLEAF;

typedef struct PNODE_S
{
	PTREE   Left;
	PTREE   Right;
} PNODE;

typedef union PBRANCH_U
{
	PLEAF   Leaf;
	PNODE   Node;
} PBRANCH;

struct PTREE_S
{
	PBRANCH Branch;
	COUNT   NodeType;
	COUNT   ExprType;
	UINT	refcount;
};

#define RECINFO_FOR_CIDX	0x00000001 /* conditional index */

struct tagRECINFO
{
	pDATOBJ	 doda;		/* doda 			*/
	pConvMap schema;	/* record schema 		*/
	pDATOBJ	 nulfld;	/* null field entry 		*/
	pUTEXT	 recptr;	/* record buffer		*/
	pNINT	 bitnum;	/* number of bit in $NULFLD$	*/
	pTEXT	 rowid;		/* ROWID address 		*/
	VRLEN	 fixlen;	/* fixed portion of record	*/
	VRLEN	 datlen;	/* total size of data		*/
	VRLEN	 fldcount;	/* number of fields in doda	*/
	LONG	 attrib;	/* special attributes		*/
};

#ifdef ctFeatUDF_EXPR
struct UDF_S
{
    ctdbUDFFunc funcPrt;        /* Function pointer         */
    NINT        retType;        /* Return type              */
    pNINT       argTypeList;    /* List of argument types   */
    COUNT       argListCount;   /* Argument list count      */
    pVOID       prev;           /* Previous UDF in the list */
    pCTSYMBOL   ctSymbol;       /* Symbol table entry       */

    /* REVISIT - For now, return buffer is limited to UDF_MAX_STR, but we can't ensure that the UDF is respecting this limit */
    pVOID       retValBuf;      /* Return value buffer      */
    ppVOID      argList;        /* Argument list            */
};
#endif /* ctFeatUDF_EXPR */

#ifdef ctCLIENT
#define ptAlloc(a)              mballc(1, (UINT)(a))
#define ptFree(a)               mbfree((pVOID)(a))
#else
#define ptAlloc(a)              ctgetmem((VRLEN)(a))
#define ptFree(a)               ctputmem((pTEXT)(a))
#endif

NINT	testparse(FILNO datno,pTEXT condexpr,PTREE *ptree,pLONG ptfilter);
pTEXT	ctgetnames(FILNO datno);

NINT ctcxparse( pConvMap Schema, pTEXT Names, pTEXT InputText, NINT InputTextSize, PTREE* pTree );

VOID ptFreeMem( pVOID Memory );
PTREE ptCreate( COUNT NodeType, COUNT ExprType );
VOID ptDestroy( PTREE Tree );
PTREE ptCopy( PTREE Tree );
PTREE ptPutInteger( LONG8 Value );
PTREE ptPutText( pTEXT Value, VRLEN len, NINT byref );
PTREE ptPutField( COUNT NodeType, COUNT ExprType, UINT Value );
PTREE ptPutNode( COUNT NodeType, COUNT ExprType, PTREE Left, PTREE Right );
PTREE ptPutRecinfo(pConvMap schema, pTEXT names, PTREE Right);
COUNT ptGetNodeType( PTREE Tree );
COUNT ptGetExprType( PTREE Tree );
LONG8 ptGetInteger( PTREE Tree );
pTEXT ptGetText( PTREE Tree );
UINT ptGetField( PTREE Tree );
PTREE ptGetLeft( PTREE Tree );
PTREE ptGetRight( PTREE Tree );
VOID ptPrint( PTREE Tree );

PTREE cndxparse(  pConvMap Schema, pTEXT Names, pTEXT InputText,  NINT InputTextSize ,pLONG ptfilter);
COUNT cndxeval( PTREE Tree, pVOID Recptr, pConvMap Schema ,VRLEN fixlen,VRLEN datlen);
NINT  clbkeval( pTEXT Clbk, LONG typflt, FILNO datno, pVOID Recptr, pConvMap Schema ,VRLEN fixlen,VRLEN datlen);
NINT  clbkeval_rowl( pTEXT Clbk, pVOID Recptr, pConvMap Schema ,VRLEN fixlen,VRLEN datlen,pVOID oldptr,VRLEN oldlen);
NINT  ctclbkinit(pTEXT filnam,pVOID expr,LONG flttyp);
VOID  cndxfree( PTREE Tree );
COUNT cndxSetCondIdxFlag(PTREE Tree);

#ifdef ctGVARH
NINT clbkrun( pTEXT Clbk, LONG typflt, FILNO datno, pVOID Recptr, pConvMap Schema ,VRLEN fixlen,VRLEN datlen pthHan);
COUNT cndxrun( PTREE Tree, pVOID Recptr, pConvMap Schema,VRLEN fixlen,VRLEN datlen pinHan);
NINT ctfiltercb( pTEXT Clbk, pVOID Recptr, pConvMap Schema,VRLEN fixlen,VRLEN datlen pinHan);
NINT ctfiltercb_rowl( pTEXT Clbk, pVOID Recptr, pConvMap Schema,VRLEN fixlen,VRLEN datlen,pTEXT username,pTEXT nodename,pVOID oldptr,VRLEN oldlen,LONG opcode pinHan);
NINT ctfiltercb_init(pTEXT Clbk pinHan);
NINT ctfiltercb_uninit(pTEXT Clbk pinHan);
NINT ctfiltercbdll_load(pCBDLL pcbdll, NINT getoptcb);
NINT ctfiltercbdll_unload(pCBDLL pcbdll);

#ifdef ctFeatUDF_EXPR
VOID  udfInit( pinHan1 );
VOID  udfTerm( pinHan1 );
pUDF  udfFind( pTEXT name pinHan );
COUNT udfAdd( pTEXT name, ctdbUDFFunc funcPrt, CTDBTYPE retType, pCTDBTYPE argTypeList, COUNT argListCount pinHan );
pUDF  ptGetUDFNode( PTREE Tree );
NINT  ptGetDataSize( NINT ptType );
#endif

COUNT runPopInteger(pLONG8 pVal pinHan);
COUNT runPopDate(pCTDATE pVal pinHan);
COUNT runPopTime(pCTTIME pVal pinHan);
COUNT runPopTimeMsec(pCTTIMEMS pVal pinHan);
COUNT runPopStamp(pCTDATETIME pVal pinHan);
COUNT runPopNumber(pCTNUMBER pVal pinHan);
COUNT runPopString(pTEXT pVal, pVRLEN len pinHan);
#endif /* ctGVARH */

#ifdef ctFeatUDF_EXPR
VOID  ptSetUDFNode( PTREE Tree, pUDF udfPtr );
#endif

PTREE ptFieldName( pConvMap Schema, pTEXT Names, pTEXT Ident );
pCTSYMBOL ptSymbolLookup(pTEXT symbolName);
NINT ptArgCount(PTREE Tree);
PTREE ptAddToExprList(PTREE List, PTREE expr);
PTREE ptPutNULL();
PTREE ptPutDate(CTDATE Value);
PTREE ptPutTime(CTTIME Value);
PTREE ptPutTimeMsec(CTTIMEMS Value);
PTREE ptPutStamp(CTDATETIME Value);
PTREE ptPutNumber(pCTNUMBER Value);
CTDATE ptGetDate(PTREE Tree);
CTTIME ptGetTime(PTREE Tree);
CTDATETIME ptGetStamp(PTREE Tree);
pCTNUMBER ptGetNumber(PTREE Tree);
VRLEN ptGetLength(PTREE Tree);
COUNT ptDuplexNumeric(PTREE Left, PTREE Right);
NINT convCTType( NINT cttype );
PTREE ptPutSet( VRLEN Value );
PTREE ptCopyIntoSet(PTREE set, PTREE node);

#endif  /* __CTDBCNDX_H */
