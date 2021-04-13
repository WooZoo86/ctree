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
#ifndef _CTPRSTDR_H_
#define _CTPRSTDR_H_

#include "ctstdr.h"
#include "ctoptn.h"
#include "cterrc.h"
#include "ctstrc.h"
#include "ctgvar.h"
#include "ctcndx.h"
#include "ctisam.h"


#ifdef ctFeatDYNPARTRUL

/*^**************************************************************************\
*
*	CTPRTYPE
*	Enumerated partition rule type
*
\****************************************************************************/
typedef enum
{
	CTPR_INVALID = 0,
	CTPR_STRING,
	CTPR_DLL,
	CTPR_CBK,
	CTPR_PTREE
} CTPRTYPE;
/*~**************************************************************************/

/*^**************************************************************************\
*
*	CTPRULE
*	structure containing the partition rules after parsing
*
\****************************************************************************/
#define CTPR_ARRAYSIZE	32 /* the array will be resized in multiples of */
			   /* CTPR_ARRAYSIZE items */

typedef struct
{
	CTPRTYPE partexprtype;	  /* expression type */
	pVOID partexprtree; /* either pPTREE or pFUNC */
	pConvMap partexprschema; /* CONVMAP for expression parsing/execution */
#ifdef ctThrds
	SEMAmut mutex;
#endif
} CTPRULE, ctMEM* pCTPRULE;
/*~**************************************************************************/



#else /* ctFeatDYNPARTRUL */



/*^**************************************************************************\
*
*	header files
*
\****************************************************************************/
#include "ctstdr.h"
#include "ctoptn.h"
#include "ctstrc.h"
#include "ctdbsdk.h"
/*~**************************************************************************/

/*^**************************************************************************\
*
*	defines
*
\****************************************************************************/
#define CTPR_MAXSTR				255

#define ctpr_malloc(n)				ctgetmem((VRLEN)(n))
#define ctpr_mfree(ptr)				ctputmem((pTEXT)(ptr))
#define ctpr_strcmp				ctrt_strcmp
#define ctpr_strcpy				ctrt_strcpy
#define ctpr_strlen				ctrt_strlen
#define ctpr_memcpy				memcpy
#define ctpr_memset				memset
#define ctpr_atoi				atoi
#define ctpr_atol				atol
#define ctpr_atof				atof
#define ctpr_strtol				strtol
/*~**************************************************************************/


/*^**************************************************************************\
*
*	CTPRTYPE
*	Enumerated partition rule type
*
\****************************************************************************/
typedef enum
{
	CTPR_INTEGER = 0,
	CTPR_FLOAT,
	CTPR_DATE,
	CTPR_BCD,
	CTPR_SDK
} CTPRTYPE;
/*~**************************************************************************/


/*^**************************************************************************\
*
*	CTPRINTV
*	Enumerated interval type
*
\****************************************************************************/
typedef enum
{
	CTPR_ARRAY	= 0,	/* interval type ARRAY */
	CTPR_FIXED,			/* interval type FIXED */
	CTPR_CALENDAR,		/* interval type CALENDAR (without value) */
	CTPR_CALVALUE		/* interval type CALENDAR with integer value */
} CTPRINTV;
/*~**************************************************************************/


/*^**************************************************************************\
*
*	CTPRCALEND
*	Enumerated calendar types
*
\****************************************************************************/
typedef enum
{
	CTPR_YEAR = 0,
	CTPR_QUARTER,
	CTPR_MONTH,
	CTPR_WEEK,
	CTPR_DAY
} CTPRCALEND;
/*~**************************************************************************/


/*^**************************************************************************\
*
*	CTPRFMT
*	Enumerated format type
*
\****************************************************************************/
typedef enum
{
	CTPR_STRING	= 0,
	CTPR_BINARY,
	CTPR_SYSTIME,
	CTPR_CTTIME,
	CTPR_YYYYMMDD,
	CTPR_YYMMDD,
	CTPR_YY_MM_DD
} CTPRFMT;
/*~**************************************************************************/


/*^**************************************************************************\
*
*	CTPRFIRST
*	Enumerated first type
*
\****************************************************************************/
typedef enum
{
	CTPR_FIRST	= 0,
	CTPR_EXISTING
} CTPRFIRST;
/*~**************************************************************************/


/*^**************************************************************************\
*
*	CTPRVAL
*	Partition rule values
*
\****************************************************************************/
typedef struct
{
	CTPRTYPE ptype; /* value type CTPR_INTEGER, CTPR_DATE, CTPR_FLOAT and */
					/* CTPR_BCD */
	union
	{
		ULONG	 ival;	/* integer value */
		CTNUMBER bval;  /* BCD value */
		double	 fval;	/* float value */
		CTDATE	 dval;	/* date value */
	} pval;
} CTPRVAL, ctMEM* pCTPRVAL;
/*~**************************************************************************/


/*^**************************************************************************\
*
*	CTPRULE
*	structure containing the partition rules after parsing
*
\****************************************************************************/
#define CTPR_ARRAYSIZE	32 /* the array will be resized in multiples of */
			   /* CTPR_ARRAYSIZE items */

typedef struct
{
	CTPRTYPE rule;	  /* rule type: SDK, INTEGER, FLOAT, DATE or BCD */
	CTPRINTV interval;/* interval type: ARRAY, FIXED or */
			  /* CALENDAR or CALVALUE */
	CTPRFMT	 format;  /* format type: BINARY, STRING, SYSTIME, etc */
	CTPRFIRST
		 first;	  /* FIRST or EXISTING */
	NINT	 rawno;	  /* 0 indicates no RAW_NO specified, 1 indicates */
			  /* RAW_NO specified and value is in rawvalue */
	pTEXT	 sdk;	  /* SDK sdk_name */
	CTPRVAL	 fixed;	  /* partition value for interval FIXED */
	CTPRVAL	*array;	  /* list of partition values for interval ARRAY*/
	NINT	 size;	  /* number of partition value items allocated */
			  /* for array list */
	NINT	 count;	  /* actual number of partition value items used */
			  /* for array list */
	CTPRCALEND
		 calendar;/* calendar type */
	ULONG	 calvalue;/* integer value for interval type CALVALUE */
	CTPRVAL	 firstval;/* value for FIRST or EXISTING */
	ULONG	 rawvalue;/* value for RAW_NO */	
} CTPRULE, ctMEM* pCTPRULE;
/*~**************************************************************************/


/*^**************************************************************************\
*
*	Error codes returned by ctpr_parse
*
\****************************************************************************/
typedef enum
{
	CTPRET_OK	   = 0,	   /* no error detected */
	CTPRET_INVRULE	   = 5001, /* invalid rule type. Rule types must be */
				   /* INTEGER, DATE, FLOAT, BCD or SDK */
	CTPRET_INVINTERVAL = 5002, /* invalid interval type. The valid types */
				   /* are ARRAY, FIXED or CALENDAR */
	CTPRET_ARRAY	   = 5003, /* Cannot mix different types in array */
	CTPRET_INVTYPE	   = 5004 /* invalid constant type */
} CTPRET;
/*~**************************************************************************/


/*^**************************************************************************\
*
*	function prototypes
*
\****************************************************************************/
#ifdef PROTOTYPE
pTEXT ctpr_strdup(pTEXT str);
NINT ctpr_stricmp(pTEXT s1, pTEXT s2);
NINT ctpr_hexdigit(TEXT Char);
pTEXT ctpr_strfix(pTEXT Text);
pTEXT ctpr_datefix(pTEXT Text);
NINT ctpr_convert(pCTPRVAL pVal, CTPRTYPE atype, pTEXT value, NINT radix);
NINT ctpr_addarray(pCTPRULE pRule, CTPRTYPE atype, pTEXT value, NINT radix);
NINT ctpr_checkarray(pCTPRULE pRule, CTPRTYPE atype);
NINT ctpr_parse(pVOID handle, pCTPRULE prule);
pVOID ctpr_alloc(pTEXT str);
VOID ctpr_free(pVOID hparse);
#else
pTEXT ctpr_strdup();
NINT ctpr_stricmp();
NINT ctpr_hexdigit();
pTEXT ctpr_strfix();
pTEXT ctpr_datefix();
NINT ctpr_convert();
NINT ctpr_addarray();
NINT ctpr_checkarray();
NINT ctpr_parse();
pVOID ctpr_alloc();
VOID ctpr_free();
#endif
/*~**************************************************************************/
#endif /* ~ctFeatDYNPARTRUL */

#endif /* _CTPRSTDR_H_ */

/* end of ctprstdr.h */
