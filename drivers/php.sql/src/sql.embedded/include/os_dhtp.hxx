
/*
 *	Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *	Copyright (C) Dharma Systems (P) Ltd.    1992 - 2020.
 *
 *	This Module contains Proprietary Information of
 *	Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 *	and should be treated as Confidential.
 */

/*
 * $RCSfile: os_dhtp.hxx,v $ $Revision: 1.1.1.1 $Date: 2006/08/04 07:25:51 $
 * $State: Exp $
 */

/* --------------------------------------------------------------------
*  Change history
*  --------------------------------------------------------------------
* Project number   : DC094, DC095
* Date             : 27 - 02 - 1997
* Description      : 1. For better portability of Dharma/SQL across 
*		      various platforms, Dharma specific datatypes 
*		      are defined for the data types. Dharma/SQL source 
*                     uses Dharma data types. Based on the  platform
*                     the definition for the datatypes will get
*                     modified.
*                     2. The range of the datatypes has been defined
*                     for uniformity.
*                     3. The definition for character data type will
*                     get modified based on the code format supported.
*                     Ex : UNICODE
*                     4. The assumption that the null terminator for
*                     a string is 1 byte wide becomes invalid with
*                     code formats like UNICODE where the null
*                     terminator is of 2 bytes. DH_NULLTERMSZ is
*                     defined to handle such discrepancies.
*                     5. To support UNICODE format, the string
*                     literals and character literals has to pass
*                     through the macros DH_STRING_LITERAL and
*                     DH_CHAR_LITERAL.
*                     6. The assumption that the sizeof(any pointer)
*                     is 4 bytes wide becomes invalid in UNICODE.
*                     DH_VOIDSTARSZ is provided to handle this
*                     discrepancy.
* -------------------------------------------------------------------
*/                                                                             

/* -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project Number : DC125
 * Date           : 1997/06/20
 * Description    : Transformation of YEAR and HOUR scalar function for
 *                  effective usage of indexes.
 *                  Like predicate transformation
 * -------------------------------------------------------------------------
 */

/*--------------------------------------------------------------------------
// Change History
//--------------------------------------------------------------------------
// Project Number      :DS_19960412_472
// Date                : 12-06_1997
// Title             : Bugfix - DS_19960412_472 (time_t used incosistently)
//--------------------------------------------------------------------------
*/

/* --------------------------------------------------------------------
// Change history
// --------------------------------------------------------------------
// Project number   : DC126/DS_19960624_552
// Date             : 1996/06/06 
// Title            : Problems when turn up DBL_MAX to system values. 
// --------------------------------------------------------------------
*/

/* ------------------------------------------------------------------------
 * Change history
 * ------------------------------------------------------------------------
 * Project number : DC142
 * Date           : 1997/06/23
 * Title          : 64-bit int representation for big_t (long long support)
 * ------------------------------------------------------------------------
 */                                                                   
/* ------------------------------------------------------------------------
 * Change history
 * ------------------------------------------------------------------------
 * Project number : DC569 DC_20020427_3051
 * Date           : 2002/04/30
 * Title          : Enabling LONGLONG support on NT
 * ------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project number   : DS_20140314_0004
 * Date             : 2014-MAR-14
 * Title            : Scrollable Cursors
 * --------------------------------------------------------------------------
 */
/* ------------------------------------------------------------------------
 * Change History
 * ------------------------------------------------------------------------
 * Project number   : DC777
 * Date             : 2014-APR-09
 * Title            : Dharma/SQL Access 14.0 Release.
 * ------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project number   : DC_20170106_4264
 * Date             : 2017-JAN-06
 * Title            : Support for SEQUENCES.
 * --------------------------------------------------------------------------
 */
#ifdef FAIRCOM_MOD
#ifndef ctPortNLM
#if _MSC_VER > 1200
#include   "winsock2.h"
#else
#include <windows.h>
#include <sys\types.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#endif
#endif
#endif
#include   "tchar.h"
                                                                               
#ifndef	os_dhtp_included
#define	os_dhtp_included

#if defined (c_plusplus) && !defined (__cplusplus)
#define	__cplusplus
#endif

#if !defined (c_plusplus) && defined (__cplusplus)
#define	c_plusplus
#endif

#if defined (__cplusplus)
extern          "C"
{
#endif

#if !defined (__cplusplus)
#define	inline static
#endif

#include   "stdio.h"

/*
 * DS_19960624_552 START
 * Definitions for maximum and minimum values of system data types 
 * are defined in values.h and float.h files in include directory.
 */

#include "values.h"
#include "float.h"
#include "time.h"

#ifndef ctPortNLM
#define DH_LONGLONG_SUPPORT /* DC569 DC_20020427_3051 */
#endif


/* DS_19960624_552 END*/

/* DC094 , DC095 BEGIN
 * Definitions for Dharma specific  data types. 
*/

/* DC569 DC_20020427_3051 BEGIN */
#ifdef DH_LONGLONG_SUPPORT
typedef   __int64             dh_longlong_t;
typedef   unsigned  __int64   dh_ulonglong_t; // DC_20170106_4264
#endif

/* DC569 DC_20020427_3051 END */

typedef   char    		dh_i8_t;
typedef   unsigned char 	dh_u8_t;
typedef   short    		dh_i16_t;
typedef   long     		dh_i32_t;
typedef   float    		dh_f32_t;
typedef   double   		dh_f64_t;

typedef   unsigned short   	dh_u16_t;
typedef   unsigned long    	dh_u32_t;

typedef   unsigned char    	dh_boolean;
/* DS_20140314_0004 BEGIN */
typedef   dh_boolean            dh_flags;
enum dh_flags_enum
{
  DH_FLAG_DYNAMIC  = 1,
  DH_FLAG_SCROLLABLE
};

/* DS_20140314_0004 END */

#if defined(FAIRCOM_MOD) && defined(ctPortDIAD_FS)
typedef	  XFILE			dh_file_t ;
#else
typedef	  FILE			dh_file_t ;
#endif

/* DC431 BEGIN
 * A new type dh_address_t is added for type-casting of pointers to long
 */

/* Windows 64 bit port Begin */
#ifdef DH_64BIT_MODEL
typedef   __int64       dh_address_t;
#else
typedef   long          dh_address_t;
#endif
/* Windows 64 bit port End */

/* END DC431 */

/*	DS_19960412_472 BEGIN
	A new variable dh_os_time_t is type defined as time_t
*/
typedef   time_t		dh_os_time_t ;
/*
	DS_19960412_472 END
*/

/* 
 * UNICODE related definitions for character data type.
*/

#if (defined(FAIRCOM_MOD) && defined(_WIN32_WCE))		/* FAIRCOM_MOD - RAB:051104: Windows CE Port */
#ifndef UNICODE
typedef char			dh_char_t;
typedef unsigned char	dh_uchar_t;
#ifdef _WIN32_WCE
typedef char			_TCHAR;
typedef unsigned char	_TUCHAR;
#endif
#else
typedef   _TCHAR        dh_char_t;
typedef   _TUCHAR		dh_uchar_t;
#endif
#else
typedef   _TCHAR        dh_char_t;
typedef   _TUCHAR		dh_uchar_t;
#endif

#ifdef ctPortNLM
#ifdef FAIRCOM_MOD
typedef   dh_i32_t		SOCKET;
#endif
#endif

/*
 * Data type range definitions
*/

/*
 * DS_19960624_552 START 
 * The range of system dependent data types are actually defined  in
 * \include\limits.h or \include\float.h. The range of these data 
 * types may vary from one system to another. Instead of hard 
 * coding the range of the Dharma data types, their range should 
 * be set to the defined value of the corresponding system data type
 * which it maps to.
 */

#ifdef SCHAR_MIN
	#define   DH_MIN_I8      SCHAR_MIN
#else
	#define   DH_MIN_I8      -128
#endif

#ifdef SCHAR_MAX
	#define   DH_MAX_I8      SCHAR_MAX
#else
	#define   DH_MAX_I8      127
#endif


#ifdef SHRT_MIN
	#define   DH_MIN_I16    SHRT_MIN
#else
	#define   DH_MIN_I16    -32768
#endif

#ifdef SHRT_MAX
	#define   DH_MAX_I16     SHRT_MAX 
#else
	#define   DH_MAX_I16     32767
#endif


#ifdef INT_MIN
	#define   DH_MIN_I32    INT_MIN	
#else
	#define   DH_MIN_I32    ( (long) 0x80000000L)
#endif

#ifdef INT_MAX 
	#define   DH_MAX_I32    INT_MAX
#else
	#define   DH_MAX_I32    2147483647L
#endif

/* DC142 max and min values for I64  begin */
#ifdef LLONG_MAX
        #define   DH_MAX_I64    LLONG_MAX
#else
        #define   DH_MAX_I64    9223372036854775807
#endif

#ifdef LLONG_MIN
        #define   DH_MIN_I64    LLONG_MIN
#else
        #define   DH_MIN_I64    -9223372036854775807
#endif
/* DC142 max and min values for I64  end */                           

#ifdef ctPortNLM
#undef FLT_MIN
#endif
#ifdef  FLT_MIN                 
	#define   DH_MIN_F32    FLT_MIN 	
#else
	#define   DH_MIN_F32    1.175494351E-38F
#endif

#ifdef ctPortNLM
#undef FLT_MAX
#endif
#ifdef FLT_MAX
	#define   DH_MAX_F32    FLT_MAX	
#else
	#define   DH_MAX_F32    3.402823466E+38F
#endif

#ifdef ctPortNLM
#undef DBL_MIN
#endif

#ifdef  DBL_MIN
	#define   DH_MIN_F64    DBL_MIN
#else
	#define   DH_MIN_F64    2.2250738585072014E-308
#endif

#ifdef ctPortNLM
#undef DBL_MAX
#endif

#ifdef  DBL_MAX
	#define   DH_MAX_F64    DBL_MAX	
#else
	#define   DH_MAX_F64    1.7976931348623157E+308
#endif

/*  DS_19960624_522 END */

/* 
 * UNICODE related definitions for literals.
*/

/* DC777 Begin */
/* Esqlc uses the C preprocessor to allow #defines in .pc files
 * because the preprocessor evaluates #defines. It is necessary
 * to be able to include several #defines again when the actual
 * .c file is generated, so move those #defines to a seperate 
 * file os_strlit.hxx.
 */
/* Moved DH_STRING_LITERAL definitions to os_strlit.hxx file */

#include "os_strlit.hxx"
#include "os_strfnc.hxx"
/* DC777 End */
#define DH_CHAR_LITERAL(char_lit)       _T(char_lit)
#define DH_WCHAR_LITERAL(wchar_lit)      L##wchar_lit  /* DC761 */

/* 
 * UNICODE related definitions for null terminator.
*/

#define DH_NULLTERM_SZ          sizeof(dh_char_t)

#define DH_VOIDSTAR_SZ 		sizeof(void *)

/* DC555 BEGIN
 * The highest value of a Unicode character is set as 0xfffe.
 * 0xffff is not set since it is considered to be an invalid character.
 */

#ifdef _UNICODE
#define DH_CHAR_MAX              0xfffe
#else
#define DH_CHAR_MAX              127
#endif

/* DC555 END */

/* DC361 DC_19990401_682 BEGIN
** The scheme for minimum and default value of stmt cache size is changed.
** Now there are 8 const values related to stmt cache size.
** These values are OS dependent and should be set based on memory 
** available. While setting these values, it should be remebered that
** cache is shared by all threads in thread mode while each process has
** its own cache. These are:- */
#ifdef FAIRCOM_MOD
#ifndef ctSQL_DEFAULT_STATIC_STMT_CACHE_SIZE_THREAD
#define ctSQL_DEFAULT_STATIC_STMT_CACHE_SIZE_THREAD  	150
#endif

#ifndef ctSQL_DEFAULT_STATIC_STMT_CACHE_SIZE_PROCESS
#define ctSQL_DEFAULT_STATIC_STMT_CACHE_SIZE_PROCESS  30
#endif

#ifndef ctSQL_DEFAULT_DYN_STMT_CACHE_SIZE_THREAD
#define ctSQL_DEFAULT_DYN_STMT_CACHE_SIZE_THREAD  		150
#endif

#ifndef ctSQL_DEFAULT_DYN_STMT_CACHE_SIZE_PROCESS
#define ctSQL_DEFAULT_DYN_STMT_CACHE_SIZE_PROCESS  		30
#endif

#ifndef ctSQL_MAX_STATIC_STMT_CACHE_SIZE_THREAD
#ifdef FAIRCOM_MOD
#define ctSQL_MAX_STATIC_STMT_CACHE_SIZE_THREAD  			16000
#else
#define ctSQL_MAX_STATIC_STMT_CACHE_SIZE_THREAD  			500
#endif
#endif

#ifndef ctSQL_MAX_STATIC_STMT_CACHE_SIZE_PROCESS
#define ctSQL_MAX_STATIC_STMT_CACHE_SIZE_PROCESS  		100
#endif

#ifndef ctSQL_MAX_DYN_STMT_CACHE_SIZE_THREAD
#ifdef FAIRCOM_MOD
#define ctSQL_MAX_DYN_STMT_CACHE_SIZE_THREAD  				16000
#else
#define ctSQL_MAX_DYN_STMT_CACHE_SIZE_THREAD  				500
#endif
#endif

#ifndef ctSQL_MAX_DYN_STMT_CACHE_SIZE_PROCESS
#define ctSQL_MAX_DYN_STMT_CACHE_SIZE_PROCESS  				100
#endif

#ifndef ctCTSRVR_C
const dh_i16_t DEFAULT_STATIC_STMT_CACHE_SIZE_THREAD  = ctSQL_DEFAULT_STATIC_STMT_CACHE_SIZE_THREAD;
const dh_i16_t DEFAULT_STATIC_STMT_CACHE_SIZE_PROCESS = ctSQL_DEFAULT_STATIC_STMT_CACHE_SIZE_PROCESS;
const dh_i16_t DEFAULT_DYN_STMT_CACHE_SIZE_THREAD      = ctSQL_DEFAULT_DYN_STMT_CACHE_SIZE_THREAD;
const dh_i16_t DEFAULT_DYN_STMT_CACHE_SIZE_PROCESS 			= ctSQL_DEFAULT_DYN_STMT_CACHE_SIZE_PROCESS;
const dh_i16_t MAX_STATIC_STMT_CACHE_SIZE_THREAD 				= ctSQL_MAX_STATIC_STMT_CACHE_SIZE_THREAD;
const dh_i16_t MAX_STATIC_STMT_CACHE_SIZE_PROCESS 			= ctSQL_MAX_STATIC_STMT_CACHE_SIZE_PROCESS;
const dh_i16_t MAX_DYN_STMT_CACHE_SIZE_THREAD 					= ctSQL_MAX_DYN_STMT_CACHE_SIZE_THREAD;
const dh_i16_t MAX_DYN_STMT_CACHE_SIZE_PROCESS 					= ctSQL_MAX_DYN_STMT_CACHE_SIZE_PROCESS;
#endif
#else
const dh_i16_t DEFAULT_STATIC_STMT_CACHE_SIZE_THREAD = 150;
const dh_i16_t DEFAULT_STATIC_STMT_CACHE_SIZE_PROCESS = 30;
const dh_i16_t DEFAULT_DYN_STMT_CACHE_SIZE_THREAD = 150;
const dh_i16_t DEFAULT_DYN_STMT_CACHE_SIZE_PROCESS = 30;
const dh_i16_t MAX_STATIC_STMT_CACHE_SIZE_THREAD = 500;
const dh_i16_t MAX_STATIC_STMT_CACHE_SIZE_PROCESS = 100;
const dh_i16_t MAX_DYN_STMT_CACHE_SIZE_THREAD = 500;
const dh_i16_t MAX_DYN_STMT_CACHE_SIZE_PROCESS = 100;
#endif
/* The cache size can be explicitly specified at runtime using environment
** variables - DH_DYN_CACHED_STATEMENTS and DH_STATIC_CACHED_STATEMENTS.
** The minimum permissible value of cache size is 1.
** DC361 DC_19990401_682 END */

#if defined (__cplusplus)
}				// extern "C"

#endif
#endif

