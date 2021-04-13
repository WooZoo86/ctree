/*********************************************************************
** SQLTYPES.H - This file defines the types used in ODBC
**
** (C) Copyright 1995-1996 By Microsoft Corp.
**
**		Created 04/10/95 for 2.50 specification
**		Updated 12/11/95 for 3.00 specification
*********************************************************************/
/*
 * Change History
 * -------------------------------------------------------------------------
 * Project Number : DC_20110223_4145
 * Date           : 2011-MAR-25
 * Title          : Making Dharma ODBC driver API's 64bit compliant. 
 * -------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project number   : DC779
 * Date             : 2016-OCT-19
 * Title            : Dharma/SQL Access 14.02 Release.
 * 		      Fix for issue while retrieving data using 64 bit MS Word.
 * -------------------------------------------------------------------------
 */

#ifndef __SQLTYPES
#define __SQLTYPES

/* BEGIN DC432 */
/* The file "sqlunx.h" need to be included in case of UNIX */

#ifdef DH_OS_UNIX
#include "sqlunx.h"
#endif      

/* END DC432 */

#if defined (DH_OS_WINNT) || defined (DH_OS_WIN95)
#ifndef ctPortNLM
#include <wchar.h>
#endif
#endif /* Header file not present in sunos,solaris or mswin */

/* if ODBCVER is not defined, assume version 3.00 */
#ifndef ODBCVER
#define ODBCVER	0x0300
#endif  /* ODBCVER */

#ifdef __cplusplus
extern "C" { 			/* Assume C declarations for C++   */
#endif  /* __cplusplus */

/* environment specific definitions */
#ifndef EXPORT
#define EXPORT   
#endif

#ifdef WIN32
#define SQL_API  __stdcall
#else
#define SQL_API
#endif

#ifndef RC_INVOKED

/* API declaration data types */
typedef unsigned char   SQLCHAR;
#if (ODBCVER >= 0x0300)
#ifdef DH_OS_UNIX /*FAIRCOM_MOD*/
typedef signed char             SCHAR;
typedef SCHAR                   SQLSCHAR;
typedef long long               INT64;
#ifdef ctPortHP9000_64
#ifndef _DLFCN_INCLUDED
typedef unsigned long long      UINT64;
#endif
#else
typedef unsigned long long      UINT64;
#endif
#else /*DH_OS_UNIX*/
typedef signed char     SQLSCHAR;
#endif /*DH_OS_UNIX*/
typedef unsigned char   SQLDATE;
typedef unsigned char   SQLDECIMAL;
typedef double          SQLDOUBLE;
typedef double          SQLFLOAT;
#endif
#ifndef DH_64BIT_MODEL
typedef long            SQLINTEGER;
#ifndef  DH_OS_UNIX /*FAIRCOM_MOD*/
typedef unsigned long   SQLUINTEGER;
#endif /*FAIRCOM_MOD*/
#else
typedef int            SQLINTEGER;
#ifndef  DH_OS_UNIX /*FAIRCOM_MOD*/
typedef unsigned int   SQLUINTEGER;
#endif /*FAIRCOM_MOD*/
#endif

/* DC779 Begin */
#define DH_32MAX_SQLUINTEGER  0xffffffff
#define DH_32MAX_SQLINTEGER   0x7fffffff
/* DC779 End */
/* DC_20110223_4145 BEGIN */
#ifdef DH_64BIT_MODEL
/* DC779 Begin */
/* #define DH_MAX_SQLUINTEGER  0xffffffff
 #define DH_MAX_SQLINTEGER   0x7fffffff */
#define DH_64MAX_SQLUINTEGER  0xffffffffffffffff
#define DH_64MAX_SQLINTEGER   0x7fffffffffffffff
/* DC779 End */
#if defined (DH_OS_WINNT)
typedef INT64           SQLLEN;
typedef UINT64          SQLULEN;
typedef UINT64          SQLSETPOSIROW;
#else
typedef long            SQLLEN;
typedef unsigned long   SQLULEN;
typedef unsigned long   SQLSETPOSIROW;
#endif
#else
#define SQLLEN          SQLINTEGER
#define SQLULEN         SQLUINTEGER
#define SQLSETPOSIROW   SQLUSMALLINT
#endif
/* DC_20110223_4145 END*/


#if (ODBCVER >= 0x0300)
typedef unsigned char   SQLNUMERIC;
#endif
typedef void *          SQLPOINTER;
typedef long            SQLADDRESS;
#if (ODBCVER >= 0x0300)
typedef float           SQLREAL;
#endif
typedef short           SQLSMALLINT;
typedef unsigned short  SQLUSMALLINT;
#if (ODBCVER >= 0x0300)
typedef unsigned char   SQLTIME;
typedef unsigned char   SQLTIMESTAMP;
typedef unsigned char   SQLVARCHAR;
#endif

/* function return type */
typedef SQLSMALLINT     SQLRETURN;

/* generic data structures */


/******************************************************************
 This block of code is been commented out for internal relase of
 dharma ODBC 3.0 driver due to porting  problems .

#if (ODBCVER >= 0x0300)  
#if defined(WIN32)  
typedef void*					SQLHANDLE;
#else	
typedef SQLINTEGER		SQLHANDLE; 
#endif 
typedef SQLHANDLE               SQLHENV;
typedef SQLHANDLE               SQLHDBC;
typedef SQLHANDLE               SQLHSTMT;
typedef SQLHANDLE               SQLHDESC;
#else
#if defined(WIN32)
typedef void*					SQLHENV;
typedef void*					SQLHDBC;
typedef void*					SQLHSTMT;
#else
typedef SQLINTEGER              SQLHENV;
typedef SQLINTEGER              SQLHDBC;
typedef SQLINTEGER              SQLHSTMT;
#endif  
#endif 

*********************************************************************/


/******************************************************************/
/*  This is the block of code introduced for dharma ODBC 3.0 driver. */

/* generic data structures */
#if (ODBCVER >= 0x0300)
/* BEGIN DC415 */
/* SQLHANDLE, SQLHENV, SQLHDBC, SQLHSTMT is typedef to void* for
   WIN32 as well as UNIX
   */
typedef void*			SQLHANDLE;

typedef SQLHANDLE               SQLHENV;
typedef SQLHANDLE               SQLHDBC;
typedef SQLHANDLE               SQLHSTMT;
typedef SQLHANDLE               SQLHDESC;

#ifdef  DH_OS_UNIX 
#ifdef FAIRCOM_MOD /* FairCom Modification -Yoshi Unix Port */
/***
typedef void*			SQLHENV;
typedef void*			SQLHDBC;
typedef void*			SQLHSTMT;
 ***/
#else
typedef void*			SQLHENV;
typedef void*			SQLHDBC;
typedef void*			SQLHSTMT;
#endif
#else
typedef void*			SQLHENV;
typedef void*			SQLHDBC;
typedef void*			SQLHSTMT;
#endif /* ~DH_OS_UNIX - end of Yoshi's UNIX change */
#endif /* ODBCVER >= 0x0300 */
/* END DC415 */


/******************************************************************/

/* SQL portable types for C */
typedef unsigned char           UCHAR;
#ifdef  DH_OS_UNIX 
#ifdef FAIRCOM_MOD /* FairCom Modification -Yoshi Unix Port */
/***
typedef signed char             SCHAR;
typedef SCHAR                   SQLSCHAR;
 **/
#else
typedef signed char             SCHAR;
typedef SCHAR                   SQLSCHAR;
#endif
#else
typedef signed char             SCHAR;
typedef SCHAR                   SQLSCHAR;
#endif /* ~DH_OS_UNIX - end of Yoshi's UNIX change */
#ifndef DH_64BIT_MODEL
typedef long int                SDWORD;
#else
typedef int                     SDWORD;
#endif
typedef short int               SWORD;
#ifndef DH_64BIT_MODEL
typedef unsigned long int       UDWORD;
#else
typedef unsigned int            UDWORD;
#endif
typedef unsigned short int      UWORD;
typedef UDWORD                  SQLUINTEGER;

typedef signed long             SLONG;
typedef signed short            SSHORT;
#ifndef FAIRCOM_MOD
typedef unsigned long           ULONG;
#endif
typedef unsigned short          USHORT;
typedef double                  SDOUBLE;
typedef double            		LDOUBLE; 
typedef float                   SFLOAT;

typedef void*              		PTR;

typedef void*              		HENV;
typedef void*              		HDBC;
typedef void*              		HSTMT;

typedef signed short            RETCODE;

#if defined(WIN32) || defined(OS2)
typedef HWND                    SQLHWND;
#elif defined (UNIX)
typedef Widget                  SQLHWND;
#else
/* placehold for future O/S GUI window handle definition */
typedef SQLPOINTER              SQLHWND;
#endif

#ifndef	__SQLDATE
#define	__SQLDATE
/* transfer types for DATE, TIME, TIMESTAMP */
typedef struct tagDATE_STRUCT
{
        SQLSMALLINT    year;
        SQLUSMALLINT   month;
        SQLUSMALLINT   day;
} DATE_STRUCT;

#if (ODBCVER >= 0x0300)
typedef DATE_STRUCT	SQL_DATE_STRUCT;
#endif  /* ODBCVER >= 0x0300 */

typedef struct tagTIME_STRUCT
{
        SQLUSMALLINT   hour;
        SQLUSMALLINT   minute;
        SQLUSMALLINT   second;
} TIME_STRUCT;

#if (ODBCVER >= 0x0300)
typedef TIME_STRUCT	SQL_TIME_STRUCT;
#endif /* ODBCVER >= 0x0300 */

typedef struct tagTIMESTAMP_STRUCT
{
        SQLSMALLINT    year;
        SQLUSMALLINT   month;
        SQLUSMALLINT   day;
        SQLUSMALLINT   hour;
        SQLUSMALLINT   minute;
        SQLUSMALLINT   second;
        SQLUINTEGER    fraction;
} TIMESTAMP_STRUCT;

#if (ODBCVER >= 0x0300)
typedef TIMESTAMP_STRUCT	SQL_TIMESTAMP_STRUCT;
#endif  /* ODBCVER >= 0x0300 */


/*
 * enumerations for DATETIME_INTERVAL_SUBCODE values for interval data types
 * these values are from SQL-92
 */

#if (ODBCVER >= 0x0300)
typedef enum 
{
	SQL_IS_YEAR						= 1,
	SQL_IS_MONTH					= 2,
	SQL_IS_DAY						= 3,
	SQL_IS_HOUR						= 4,
	SQL_IS_MINUTE					= 5,
	SQL_IS_SECOND					= 6,
	SQL_IS_YEAR_TO_MONTH			= 7,
	SQL_IS_DAY_TO_HOUR				= 8,
	SQL_IS_DAY_TO_MINUTE			= 9,
	SQL_IS_DAY_TO_SECOND			= 10,
	SQL_IS_HOUR_TO_MINUTE			= 11,
	SQL_IS_HOUR_TO_SECOND			= 12,
	SQL_IS_MINUTE_TO_SECOND			= 13
} SQLINTERVAL;

#endif  /* ODBCVER >= 0x0300 */

#if (ODBCVER >= 0x0300)
typedef struct tagSQL_YEAR_MONTH
{
		SQLUINTEGER		year;
		SQLUINTEGER		month;
} SQL_YEAR_MONTH_STRUCT;

typedef struct tagSQL_DAY_SECOND
{
		SQLUINTEGER		day;
		SQLUINTEGER		hour;
		SQLUINTEGER		minute;
		SQLUINTEGER		second;
		SQLUINTEGER		fraction;
} SQL_DAY_SECOND_STRUCT;

typedef struct tagSQL_INTERVAL_STRUCT
{
	SQLINTERVAL		interval_type;
	SQLSMALLINT		interval_sign;
	union {
		SQL_YEAR_MONTH_STRUCT		year_month;
		SQL_DAY_SECOND_STRUCT		day_second;
	} intval;

} SQL_INTERVAL_STRUCT;

#endif  /* ODBCVER >= 0x0300 */

#endif	/* __SQLDATE	*/

/* the ODBC C types for SQL_C_SBIGINT and SQL_C_UBIGINT */
/* BEGIN DC514 DC_20010918_2747 */

#define SQLBIGINT tpe_bigint_t

/* END DC514 DC_20010918_2747 */      

/* internal representation of numeric data type */
#if (ODBCVER >= 0x0300)
#define SQL_MAX_NUMERIC_LEN		16
typedef struct tagSQL_NUMERIC_STRUCT
{
	SQLCHAR		precision;
	SQLSCHAR	scale;
	SQLCHAR		sign;	/* 1 if positive, 0 if negative */
	SQLCHAR		val[SQL_MAX_NUMERIC_LEN];
} SQL_NUMERIC_STRUCT;
#endif  /* ODBCVER >= 0x0300 */

typedef unsigned long int       BOOKMARK;

typedef wchar_t SQLWCHAR;

#ifdef UNICODE
typedef SQLWCHAR        SQLTCHAR;
#else
typedef SQLCHAR         SQLTCHAR;
#endif  /* UNICODE */



#endif     /* RC_INVOKED */


#ifdef __cplusplus
}                                    /* End of extern "C" { */
#endif  /* __cplusplus */

#endif /* #ifndef __SQLTYPES */
