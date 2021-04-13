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

/* c-tree SQL Override Dharma Settings File for Windows CE */

#ifndef _CTSQLOCE_H
#define _CTSQLOCE_H
 
/* This section is used to override the capacities in the Dharama SQL Engine */ 
/*****************************************/
/* Passed in from makefile cammand line:
#define ISQL_LMAX 32762 
#define FGL_LMAX 32762
#define RDS_LMAX 32762 
*/

#ifndef ISQL_LMAX
#define ISQL_LMAX 32762 
#endif

#ifndef FGL_LMAX
#define FGL_LMAX 32762
#endif

#ifndef RDS_LMAX
#define RDS_LMAX 32762 
#endif
/*****************************************/

 
/*****************************************/
/* ..\ctreeSDK\ctreeAPI\ctree\include\sql_lib.h */
/* Dharma Original Setting:
#define		TPE_MAX_SQLSTMTLEN      FAIRCOM_MOD_35000	
*/
#define 	ctSQL_MAX_FLDLEN 	2000
#define		TPE_MAX_SQLSTMTLEN      4096	
#define 	FAIRCOM_MOD_35000	TPE_MAX_SQLSTMTLEN
/*****************************************/

/*****************************************/
/* ..\ctreeSDK\ctreeAPI\ctree\include\sql_lib.h */
/* Dharma Original Setting:
#define		TPE_MAX_PROC_ARGS	50
*/

#define		TPE_MAX_PROC_ARGS	50
/*****************************************/

/*****************************************/
/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\snw\snr\snr_nw.cxx */
/* Dharma Original Settings 
#define DEFAULT_SVR_DA_BUFFER 		1000
#define DEFAULT_SVR_DA_BUFFER_MIN 10  
#define DEFAULT_SVR_DA_BUFFER_MAX 10000
#define DH_BUFSZ 									1000000
*/

#define DEFAULT_SVR_DA_BUFFER 		256			// 060225: tried 128 and ODBC did not work
#define DEFAULT_SVR_DA_BUFFER_MIN 4  					
#define DEFAULT_SVR_DA_BUFFER_MAX 10000
#define DH_BUFSZ 									128000	// rays first was 250000, yet 128000 looks ok on 060225.		
/*****************************************/

/*****************************************/
/* ..\\ctreeSDK\ctreeAPI\ctree\sql\src\snw\include\snr_nw.hxx
 Dharma Original settings
#define DH_NETBUF_SIZE 1500000
*/

#define DH_NETBUF_SIZE 128000 //was: 1500000
/*****************************************/


/*****************************************/
/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\rds\sql_defs.hxx */
/* Dharma Original Settings:
#ifndef ctSQL_MAXBLOCKS
#define ctSQL_MAXBLOCKS 25
#endif
const int          SQL_MAXBLOCKS = ctSQL_MAXBLOCKS;
#else
const int          SQL_MAXBLOCKS = 25;
#endif
*/

#define ctSQL_MAXBLOCKS 6
/*****************************************/


/*****************************************/
/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\rds\sql_defs.hxx */
/* Dharma Original Settings:
#ifndef ctSQL_MAXTBLREF
#define ctSQL_MAXTBLREF 250
#endif
const int          SQL_MAXTBLREF = ctSQL_MAXTBLREF;	
#else
#ifdef DH_OS_MSWIN
const int          SQL_MAXTBLREF = 50;	
#else
const int          SQL_MAXTBLREF = 250;	
#endif
*/

#define ctSQL_MAXTBLREF 25;								/* tried 12, yet ODBC did not work */
/*****************************************/


/*****************************************/
/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\mm\mm_env.hxx */
/* Dharma Original Settings:
#define	    TPE_DEFAULT_MM_CACHESIZE   1000	// 1 Meg
*/

#define     TPE_DEFAULT_MM_CACHESIZE   500 // Tried 100 and ODBC did not connect	
/*****************************************/

 
/*****************************************/
/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\rds\psr_env.hxx */
/* Dharma Original Setting:
#define		RDS_MAXDEPTH	500
*/
#define		RDS_MAXDEPTH	150
/*****************************************/


/*****************************************/
/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\rds\psr_gram.cxx */
/* Dharma Original Setting:
#define		RDS_MAXDEPTH	500
*/
#ifndef 	RDS_MAXDEPTH /* Dharma had it defined twice: see lines just above in this file */
#define		RDS_MAXDEPTH	150
#endif
/*****************************************/


/*****************************************/
/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\public\os\windows\os_dhtp.hxx */
/* Dharma Original Setting:
/* DC361 DC_19990401_682 BEGIN
** The scheme for minimum and default value of stmt cache size is changed.
** Now there are 8 const values related to stmt cache size.
** These values are OS dependent and should be set based on memory 
** available. While setting these values, it should be remebered that
** cache is shared by all threads in thread mode while each process has
** its own cache. These are:- 

const dh_i16_t DEFAULT_STATIC_STMT_CACHE_SIZE_THREAD = 150;
const dh_i16_t DEFAULT_STATIC_STMT_CACHE_SIZE_PROCESS = 30;
const dh_i16_t DEFAULT_DYN_STMT_CACHE_SIZE_THREAD = 150;
const dh_i16_t DEFAULT_DYN_STMT_CACHE_SIZE_PROCESS = 30;
const dh_i16_t MAX_STATIC_STMT_CACHE_SIZE_THREAD = 500;
const dh_i16_t MAX_STATIC_STMT_CACHE_SIZE_PROCESS = 100;
const dh_i16_t MAX_DYN_STMT_CACHE_SIZE_THREAD = 500;
const dh_i16_t MAX_DYN_STMT_CACHE_SIZE_PROCESS = 100;

 The cache size can be explicitly specified at runtime using environment
** variables - DH_DYN_CACHED_STATEMENTS and DH_STATIC_CACHED_STATEMENTS.
** The minimum permissible value of cache size is 1.
** DC361 DC_19990401_682 END 
*/

#define ctSQL_DEFAULT_STATIC_STMT_CACHE_SIZE_THREAD  	5
#define ctSQL_DEFAULT_STATIC_STMT_CACHE_SIZE_PROCESS  5
#define ctSQL_DEFAULT_DYN_STMT_CACHE_SIZE_THREAD  		5
#define ctSQL_DEFAULT_DYN_STMT_CACHE_SIZE_PROCESS  		5
#define ctSQL_MAX_STATIC_STMT_CACHE_SIZE_THREAD  			30
#define ctSQL_MAX_STATIC_STMT_CACHE_SIZE_PROCESS  		30
#define ctSQL_MAX_DYN_STMT_CACHE_SIZE_THREAD  				30
#define ctSQL_MAX_DYN_STMT_CACHE_SIZE_PROCESS  				30

/*****************************************/

#endif /* ~ _CTSQLOCE_H */ /* bring in header only once */

/* end of ctsqloce.h */
