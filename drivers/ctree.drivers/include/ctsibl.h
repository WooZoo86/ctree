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

/*^*****************************************************************/
/* RNM(nnnnn) macro: function return hook locale identifier.	   */
/*								   */
/* See revision 2299 for details.				   */
/*								   */
/* LastRNMvalue  13892  used by JPK				   */
/*~*****************************************************************/
/*^*****************************************************************/
/* terr(): fatal internal error locale identifier */		
/*								   */
/* Last terr() value  8002  used by JPK				   */
/* When we reach 8335, we will need to find a new range.	   */
/*~*****************************************************************/

/*^*****************************************************************/
/* SMN(nnnn) macro: semaphore request locale identifier.	   */
/*								   */
/* See developer log entry #1273 "add a debugging compile-time	   */
/* option to track ctsemrqs" for details.			   */
/*								   */
/* LastSMNvalue   4935 used by JAK				   */
/* --------------------------------------------------------------- */
/*  When we reach 5000, we will find a new range to use such as	   */
/*  5006 -> 5999						   */
/*  consider SQLSMN taking the range from 9700->to 9700+SQLSMN     */
/*~*****************************************************************/

/*^*****************************************************************/
/* SQLSMN(nnnn) macro: semaphore request locale identifier in SQL code.	   */
/*								   */
/* See developer log entry #1273 "add a debugging compile-time	   */
/* option to track ctsemrqs" for details.			   */
/*								   */
/* LastSQLSMNvalue   37 used by PF   */
/* --------------------------------------------------------------- */
/*  When we reach 299, we will find a new range considering that  */
/*  SQLSMN occupies the SMN numbers > 9700-9999 */
/*~*****************************************************************/

/*^*****************************************************************/
/* CMN(nnnn) macro: ctpconcsema request locale identifier.	   */
/*								   */
/* LastCMNvalue   4351  used by JPK				   */
/*~*****************************************************************/

/*^*****************************************************************/
/* UPD(nnnn) macro: file update flag locale identifier.		   */
/*								   */
/* See revision 111 for details.				   */
/*								   */
/* LastUPDvalue   2162  used by JAK				   */
/*~*****************************************************************/

/*^*****************************************************************/
/* ctSETupdflg(nnnn) macro: file update flag locale identifier.	   */
/*								   */
/* See revision	111 for details.				   */
/*								   */
/* LastSETupdflg  1085  used by JAK				   */
/*~*****************************************************************/

/*^*****************************************************************/
/* DLN(nnnn) macro: 64-bit (double long) arithmetic-function call  */
/* counter locale identifier.					   */
/*								   */
/* LastDLNvalue   1333  used by JAK				   */
/*~*****************************************************************/

/*^*****************************************************************/
/* setMsgLen(nnnn) macro: comm buffer MsgLen locale identifier.	   */
/*								   */
/* See 2000-01-30-MOD#1258 for details.				   */
/*								   */
/* LastMsgLen     1155  used by JAK				   */
/*~*****************************************************************/

/*^*****************************************************************/
/* ION(nnnn) macro: low-level I/O locale identifier.		   */
/*								   */
/* See revision 109 for details.				   */
/*								   */
/* LastIONvalue   1705  used by JPK				   */
/*~*****************************************************************/

/*^********************************************/
/* { ctSIBLING_... Comments */

/*
** The c-tree source code uses the string ctSIBLING_ in comments to identify
** related source code. For example, by searching for ctSIBLING_wxyz, one can
** find all occurrences in the source code that are related to 'wxyz'.
**
** This header file lists each ctSIBLING_ comment marker and describes
** its purpose.
*/

/*^*******************/
/*
** ctSIBLING_VERSIONID: To add a new c-tree Server activation key version ID
** and/or change the current version ID, search for ctSIBLING_VERSIONID.
*/
/*~*******************/


/*^*******************/
/*
** ctSIBLING_HANDSHAKE: This identified the code locations for the OEM
** "handshake" feature. Search for ctSIBLING_HANDSHAKE_ for steps.
*/
/*~*******************/

/*^*******************/
/*
** ctSIBLING_EXPRESS_HANDSHAKE: Here is where we had the special considerations
** for the range of servers for c-treeExpress.
*/
/*~*******************/

/*^*******************/
/*
** ctSIBLING_HARD_CODED_ACTIVATION: This identifies the code locations to "hard
** code" a serial number and other activation settings.
*/
/*~*******************/

/*
** ctSIBLING_CTSTATE: Identifies locations where we must add code when we add
** a new ctstate variable.
*/

/*
** ctSIBLING_FC_USER: Identifies locations where we must consider the effect of
** modifying the FC_USER structure.
*/

/*
** ctSIBLING_VERSIONS: Product Version Numbers References-
** Identifies locations where product version number is
** implemented or considered. 
** Also use FAIRCOM_CODE_LINE_MAINTENANCE_ to find locations.
*/

/*
** ctSIBLING_PRODUCT_NAME: Product Name References-
** Identifies locations where product name is
** implemented or considered: ACE vs EDGE vs RTG, etc.
*/

/* } END ctSIBLING_... Comments */
/*~********************************************/

/*^********************************************

  PERFORMANCE NOTES:

  ctpcomsema - #define ctBEHAV_COMNOD_UPDFLG introduces additional requests to
	the commit node list mutex (ctpcomsema) for ctTRNLOG files (and ctPREIMG
	files when PREIMAGE_DUMP is enabled).

  Large I/O operations - #define ctFeatINTERMEDIATE_BLOCK_PAGING changes our
	block I/O routine's behavior for read and write operations that span
	more than 2 + MPAGE_CACHE cache pages. If necessary, the configuration
	option INTERMEDIATE_BLOCK_PAGING NO can be used to restore the previous
	behavior.

*~********************************************/

/*^********************************************/
/*
HELPER comments - Ray maintains a list of tokens that can be grepped in order
to help maintain different key subsystems.

FAIRCOM_MOD_HELPER - #define FAIRCOM_MOD_HELPER - used throughout the SQL
subsystem to locate key spots. Activating this #define will cause the function
FairModHelper() to exist and then you are able to place breakpoints in
FairModHelper() to stop the logic at key locations.

FAIRJOB_HELPER - #define FAIRJOB_HELPER - used throughout the Job management
subsystem to locate key spots. Activating this #define will cause the function
FairJobHelper() to exist and then you are able to place breakpoints in
FairJobHelper() to stop the logic at key locations.
*/
/*~********************************************/

/*^********************************************/
/*

DEFINE Considerations: Below of a log of #define conciderations that should be
monitored by the FairCom GenMaster:
--------------------------------------------------------------------------------------
130616:RAB- NO OPEN CONCERNS AT THIS TIME

--------------------------------------------------------------------------------------
130616:RAB- ctsql_lib.h - #define ctSQL_CTTBL - Activated in v10.1.3  on 6/16/13
Rev 69196
ctSQL_CTTBL  - cttbl syntax support

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctBEHAV_QT_DYNDMP - Activated in v10.1.3  on 6/16/13
Rev 69196
ctBEHAV_QT_DYNDMP changes the way ctQUIET and Dynamic Dump interact. The ctp1dmsema,
meant to avoid overlap between multiple dynamic dumps, and between ctQUIET and dynamic
dumps, was not employed effectively in all cases. This modification changes how ctp1dmsema
is employed. Also, ctaddwork() has been modified to better detect interactions between
ctQUIET and dynamic dumps; and ctaddwork() invocation has been moved from the time idyndmp()
thread is launched to the scheduled time of the actual dump.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define NO_ctFeat_V11_NewCache - Activated in v10.2.0  on 6/16/13
Rev 69196
NO_ctFeat_V11_NewCache - eliminate data-cache/index-buffer pending lists to streamline
the search and update of the cache/buffer spaces.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatDISTbufcnt - Activated in v10.2.0  on 6/16/13
Rev 69196
ctFeatDISTbufcnt enables distributed computation of ctbufcnt when
ctFeatAVLISTnum is on. It reduces extra mutex calls and reduces
contention betweeen threads by controlling ctbufcnt with the
ctFeatAVLISTnum mutex array.

Turning this option on has the side effact of reducing the accuracy
of the ctbufhgh attribute because ctbufhgh is only checked periodically,
not every time ctbufcnt is incremented.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatDISTdatcnt - Activated in v10.2.0  on 6/16/13
Rev 69196
ctFeatDISTdatcnt enables distributed computation of ctdatcnt when
ctFeatDALISTnum is on. It reduces extra mutex calls and reduces
contention betweeen threads by controlling ctdatcnt with the
ctFeatDALISTnum mutex array.

Turning this option on has the side effact of reducing the accuracy
of the ctdathgh attribute because ctdathgh is only checked periodically,
not every time ctdatcnt is incremented.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatPARTREPL - Activated in v10.1.3  on 6/16/13
Rev 69196
ctFeatPARTREPL enables additional transaction log entries that are required in order
to replicate changes to partitioned files.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatDYNPARTMBR - Activated in v10.1.3  on 6/16/13
Rev 69196
ctFeatDYNPARTMBR enables support for dynamic partition members.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctDBGRCVR - Activated in v10.1.3  on 6/16/13
Rev 69196
ctDBGRCVR logs automatic recovery details to the file RECOVERY.FCS when
DIAGNOSTICS TRAN_RECOVERY is enabled in ctsrvr.cfg.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatCFGsubsys - Activated in v10.1.3  on 6/16/13
Rev 69196
ctFeatCFGsubsys enables support for c-tree Server's SUBSYSTEM keyword.


--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatBATCH_ALLOC_OPT - Activated in v10.1.3  on 6/16/13
Rev 69196
ctFeatBATCH_ALLOC_OPT reduces memory allocations during physical order batch read
operations in two ways:
 1) saving the batch continuation pointer across batch calls
    so that it can be reused, and
 2) skipping the creation of the batch record offset list
    when reading in physical order and not locking records
    or only locking one record at a time.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatCTDLLerrbuf - Activated in v10.1.2  on 6/16/13
Rev 69196
ctFeatCTDLLerrbuf enables support for passing an error buffer to ctdll_load().

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatZLIBdynamic - Activated in v10.1.2  on 6/16/13
Rev 69196
ctFeatZLIBdynamic causes c-tree to load the zlib compression library at run-time on
Unix systems rather than statically linking with the zlib library at compile time.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctBEHAV_THREADSAFE - Activated in v10.1.3  on 6/16/13
Rev 69196
ctBEHAV_THREADSAFE - replaces non-threadsafe system calls with thread safe versions

--------------------------------------------------------------------------------------
130616:RAB- ctdbsdk.h - #define CTDB_VARSTRTERM -  Activated in v10.1.3 on 6/16/13
Rev 69196
130517:RAB- ctdbsdk.h - rev 68226 - #define CTDB_VARSTRTERM -  use schema
                                    information for variable length string terminator
Activated the CTDB_VARSTRTERM for ctPortSTR or ctVER_GE(10,2) Did not want to
turn this for production in prior to v10.2, except for STR or other special
cases.
--------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatOPENSSL - Activated in v10.1.3  on 6/16/13
Rev 69196
ctFeatOPENSSL enables the use of the OpenSSL library, used to support SSL for TCP/IP
connections and to support secure password transmission from client to server when not
using SSL.

--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatKEYXCHG - Activated in v10.1.3  on 6/16/13
Rev 69196
ctFeatKEYXCHG enables Diffie-Hellman key exchange, used	to allow a c-tree client to
securely send its password to c-tree Server.


--------------------------------------------------------------------------------------
130616:RAB- ctopt2.h - #define ctFeatLDAP - Activated in v10.1.3  on 6/16/13
Rev 69196
ctFeatLDAP enables support for using an LDAP server for c-tree Server's user authentication.
This feature replaces the old ctFeatOS_SECURITY_LDAP feature.

--------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------
130616:RAB- ctsql_lib.h- #define FAIRCOM_MOD_KEY_EXCHANGE and  FAIRCOM_MOD_KEY_EXCHANGE_FC_RNG - Activated in v10.1.3  on 6/16/13
Rev 69196
FAIRCOM_MOD_KEY_EXCHANGE - secure key exchange support
FAIRCOM_MOD_KEY_EXCHANGE_FC_RNG - use FairCom random number generator for secure key exchange


*/
/*~********************************************/



/* end of ctsibl.h */
