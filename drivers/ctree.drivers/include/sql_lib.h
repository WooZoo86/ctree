#ifndef __SQL_LIB_H__
#define __SQL_LIB_H__
/*^******************************************************************************************************************************************************/
#ifdef   FAIRCOM_MOD	/* FairCom source code modification												*/
			/* Define to identify a Dharma (non-FairCom) source module - may be used to isolate changes to Dharma vs.FairCom modules	*/
#include "ctsqlall.h"	/* FairCom Header intended to be included in ALL Dharma SQL source code for porting and other reasons				*/
			/* OFFICIAL NOTIFICATION: the following CONFIDENTIAL and PROPRIETARY property legend shall not be removed from this source code	*/
#endif			/* Portions Copyright (c) 1992 - 2020 FairCom Corporation. Corporation.								*/
/*~******************************************************************************************************************************************************/
#ifdef FAIRCOM_MOD
#include "ctsql_lib.h"	/* FairCom's SQL Global Header Files */
#endif
/*

 * --------------------------------------------------------------------
 *      Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *      Copyright (C) Dharma Systems (P) Ltd.    1992 - 2020.
 *
 *      This Module contains Proprietary Information of
 *      Dharma Systems Inc. and Dharma Systems (P) Ltd.
 *      and should be treated as Confidential.
 *
 *
 * --------------------------------------------------------------------
 * --------------------------------------------------------------------
 *
 * $RCSfile: sql_lib.h,v $ $Revision: 1.3 $ $Date $
 * 	SQL library dh_i32_t interface.
 * --------------------------------------------------------------------

*/

/*
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC065
 * Date             : 15-03-97.
 * Title	    : Descriptor Implementation
 * -------------------------------------------------------------------

 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC044
 * Date             : 23-11-96.
 * Description      : 
 *			The sqlca was enhanced to contain the
 *			diagnostics information and a few 
 *			associated enum structures are defined
 *			for implementing the diagnostics.
 *			The prototype of the descriptor C API is declared here.
 * -------------------------------------------------------------------
*/

/* ---------------------------------------------------------------------------
 * Project number   : DC096
 * Date             : 12-mar-1997
 * Description      : Macro SQL_ERR_INV_LONGREF was introduced,to display
 *		      error for invalid LONG data type references.
 * ---------------------------------------------------------------------------
 */

/* ---------------------------------------------------------------------------
 * Project number   : DC109
 * Date             : 05/05/97
 * Description      : Macro SQL_ERR_INVFORMAT was introduced,to display
 *		      error for invalid FORMAT types w.r.t date time timestamp
 * ---------------------------------------------------------------------------
 */

/* ---------------------------------------------------------------------------
 * Project number   : DC151
 * Date             : 1997/07/07
 * Description      : Big_t patch integration and stabilization
 * ---------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC137/DS_19970121_682
 * Date             : 1996/06/26 
 * Title            : Implement general database logon structure
 * --------------------------------------------------------------------
 */ 

/*
 *--------------------------------------------------------------------------
 * Change History 
 *--------------------------------------------------------------------------
 * Project Number     : DC118
 * Date               : 1997/04/17
 * Description        : IN this file Cost,card member of cost_val_t structure 
 *                       are changed from unsigned long to double.
 *
 *--------------------------------------------------------------------------

*/

/* ---------------------------------------------------------------------------
 * Project number   : DC097
 * Date             : 27-mar-1997
 * Description      : Macro SQL_ERR_PROCEXISTS was introduced,to display
 *		      when it is attempted to create a procedure which
 *		      already exists.
 * ---------------------------------------------------------------------------
 */

/* ---------------------------------------------------------------------------
 * Project number   : DC091
 * Date             : 1997/07/26
 * Description      : Host buffers for National Character.
 *		      TPE types for National Character.
 *		      FLD types for National Character.
 * ---------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC113
 * Date             : 6th June, 1997
 * Description      : Defined new error codes
 *                    for Java Stored Procedure
 *
 * ------------------------------------------------------------------- */
/* -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project Number : DC166
 * Date		  : 1997/08/19
 * Title          : Cleanup of comparision functions in data_t to 
 *                  avoid overflows
 * -------------------------------------------------------------------------*/

/* --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC187
 * Date             : 1997/12/16
 * Description      : Implimetation of tableid changes.
 * ------------------------------------------------------------------- */

/* --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC215 (DS_19971118_783)
 * Date             : 02 Jan 1998
 * Description      : Increased default statement size
 * ------------------------------------------------------------------- */
  
/* --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC197
 * Date             : 
 * Description      : Defined new error code
 *                    for DHRSS storage system
 *
 * ------------------------------------------------------------------- */

/*
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC223
 * Date             : Jan 13 1998 
 * Description      : Implementation of Drop column changes.
 *                    Introduced new errors.
 * -------------------------------------------------------------------
*/

/*
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC317
 * Date             : 1998-DEC-21 
 * Description      : Macros introduced -
 *
 *		          i) DH_EXTDATA_MIN_BYTELEN - Minimum byte length
 *			     			      beyond which an 
 *						      extended data object
 *						      is created, in FF 
 *						      and Data Manager.
 *
 *		         ii) TPE_EXT_MAX_FLDLEN     - Maximum field width
 *						      for extended types.
 *
 *			iii) DH_EXTTBL_FLDLEN	    - The width of the 
 *						      buffer table in FF
 *						      and MMSM for extended
 *						      types. 
 *
 *	                 iv) TPE_NCHAR_HDR_SZ	    - The sizeof
 *	                 			      tpe_nchar_t excluding
 *	                 			      the sizeof nchar_data
 *	                 			      array.
 *
 *	                 iv) TPE_BINARY_HDR_SZ	    - The sizeof
 *	                 			      tpe_binary_t excluding
 *	                 			      the sizeof tb_data
 *	                 			      array.
 *
 *			  v) sbuf_hdl_t		    - A structure used by 
 *						      the Stream Buffer 
 *						      Manager for storing
 *						      information about
 *						      extended data types
 *						      in MM table.
 *	                 			     
 * -------------------------------------------------------------------
*/

/*
 * -------------------------------------------------------------------------
 * Change history
 * -------------------------------------------------------------------------
 * Project number   : DC354
 * Date             : 1998-DEC-31
 * Description      : Bug-Fixes
 *                    DC_19981210_344 - Introduced new errors.
 * -------------------------------------------------------------------------
*/

/*
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number : DC355
 * Date           : 1998-DEC-14
 * Title          : Validation and Stabilization of JDBC
 * -------------------------------------------------------------------
*/

/*
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC272
 * Date             : 1998-SEP-10
 * Description      : Statement caching implementation for JSP performance
 *                    improvement.
 * -------------------------------------------------------------------
*/

/*
 * ------------------------------------------------------------------------
 * Change history
 * ------------------------------------------------------------------------
 * Project number : DC310
 * Date           : 1998-JULY-27
 * Title          : Bug fix for 6.2 release.
 * ------------------------------------------------------------------------
*/

/*
 * ------------------------------------------------------------------------
 * Change history
 * ------------------------------------------------------------------------
 * Project number : DC342 - DC_19990125_430
 * Date           : 1999-FEB-10
 * Title          : Error message for error code 20155 is incomplete. 
 * ------------------------------------------------------------------------

 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC368
 * Date             : 1999-APR-07
 * Title            : Multi-user performance improvement of Integrator.
 * --------------------------------------------------------------------
*/

/*
 * ------------------------------------------------------------------------
 * Change history
 * ------------------------------------------------------------------------
 * Project number : DC363
 * Date           : 1999-MAY-04
 * Title          : Introduced new error codes
                    SQL_ERR_NOTRIG_ALWD     - No triggers allowed
                    SQL_ERR_NOREVOKE        - No revoke
                    SQL_ERR_JSPTFENOTSUP    - JSPT feature not supported
                    SQL_ERR_PARAMNOTREGSTRD - Parameter not registered
                    SQL_ERR_PARAM_CANT_REGSTRD - Parameter Can not be
                                                 registered
                    SQL_ERR_REG_PARAM_NOTYET - Third argument for 
		                               registerOutParam  API is not
					       implemented
 * ------------------------------------------------------------------------
*/

/*
 *--------------------------------------------------------------------------
 * Change History
 *--------------------------------------------------------------------------
 * Project number   : DC364 / DC_19990810_1030
 * Date             : 1999-SEP-02
 * Description      : LIKE with ESCAPE fetching wrong result for
 *                  some of the queries.
 *
 *--------------------------------------------------------------------------

 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC368
 * Date             : 1999-APR-07
 * Title            : Multi-user performance improvement of Integrator.
 * --------------------------------------------------------------------
 *
 * ------------------------------------------------------------------------
 * Change history
 * ------------------------------------------------------------------------
 * Project number : DC362
 * Date           : 1999-APR-14
 * Title          : JDBC bugfixing on v621
 * Description    : DC_19990323_666
 *                getColumnTypeName() is not working.
 * ------------------------------------------------------------------------
 *
 * --------------------------------------------------------------------
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC404
 * Date             : 1999-OCT-28
 * Title            : Enabling the JSPT feature in merged model on NT
 * Description      : EXPORT is defined as blank for NT and WIN95
 * --------------------------------------------------------------------
 *
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC404
 * Date             : 1999-OCT-28
 * Title            : Enabling the JSPT feature in merged model on NT
 * Description      : EXPORT is defined as blank for NT and WIN95
 * --------------------------------------------------------------------
 *
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC424
 * Date             : 2000-JAN-25
 * Title            : Introduction of Character Set and i18N Managers.
 * Description      : Introduction  of  enumerations  for  collations, 
 *                    character sets and coercibility.
 * --------------------------------------------------------------------
 *
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC427
 * Date             : 2000-JAN-25
 * Title            : RDS related changes for i18N Manager.
 * Description      : Introduction the structure nchar_str_atrib_tag.
 * --------------------------------------------------------------------
*/

/*
 *--------------------------------------------------------------------------
 * Change History
 *--------------------------------------------------------------------------
 * Project Number      : DC_20000905_1737.
 * Date                : 07-Sep-2000.
 * Project             : New tpe interface for freeing up cursor space.
 * Description 	       : Added new interface tpe_release_cursor to free
 *			 up cursor space allocated in the client side.	
 *--------------------------------------------------------------------------
*/
/*
 * -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project Number : DC555
 * Date           : 2002-JUL-22
 * Title          : Unicode Architecture for Internationalization
 *                  DC_20010123_2156
 * -------------------------------------------------------------------------
*/    

/*
  * -------------------------------------------------------------------------
  * Change History
  * -------------------------------------------------------------------------
  * Project Number : DC569 - DC_20020607_3072
  * Date           : 2002-JUN-07
  * Title          : Error message length needs to be increased from
  *                  256 characters
  * -------------------------------------------------------------------------
 */

/*
 * -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project Number : DC514 DC_20011220_2874
 * Date           : 2001-DEC-20
 * Title          : STORAGE_ATTRIBUTES data  of more than
 *                  TPE_MAX_STOR_DFLT_LEN  crashes the server
 * -------------------------------------------------------------------------
*/ 

/*
 *--------------------------------------------------------------------------
 * Change History
 *--------------------------------------------------------------------------
 * Project Number      : DC555 - DC_20020828_3155
 * Date                : 16-SEP-2002
 * Description         : User isolation level to be used for Dictionary
 *                       operations if DH_USR_ISO_FOR_DICT is defined.
 *-------------------------------------------------------------------------- 
*/
/*--------------------------------------------------------------------------
 * Change History
 *--------------------------------------------------------------------------
 * Project Number      : DC569/DC_20020914_3158
 * Date                : 17-SEP-2002
 * Description         : User name length exceeding the limit 
 *			 crashes the server
 *--------------------------------------------------------------------------   
*/

/*
 * -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project Number : DC569 - DC_20020801_3147
 * Date           : 2002-AUG-16
 * Title          : Support for setting non zero value to 
 *		    SQL_ATTR_LOGIN_TIMEOUT  through ODBC.
 * -------------------------------------------------------------------------
*/
/*
 *--------------------------------------------------------------------------
 * Change History
 *--------------------------------------------------------------------------
 * Project Number      : DC555/DC_20020919_3159
 * Date                : 19-SEP-2002
 * Description         : Dharma ODBC driver doesn't display the server error
 *                       message through VB
 *--------------------------------------------------------------------------
*/            
/*
 *--------------------------------------------------------------------------
 * Change History
 *--------------------------------------------------------------------------
 * Project Number      : DC569/DC_20020723_3127
 * Date                : 24-JULY-2002
 * Project             : Dharma C Programmatic interfaces are not thread safe
 * Description         : Added  new thread safe API's
 *
 *--------------------------------------------------------------------------
*/
/*
 *--------------------------------------------------------------------------
 * Change History
 *--------------------------------------------------------------------------
 * Project Number      : DC587/DC_20020822_3153
 * Date                : 09-OCT-2002
 * Description         : Default isolation level to be set based on
 *                     DH_DFLT_ISOLATION_LEVEL flag
 *--------------------------------------------------------------------------
*/

/*
 * ------------------------------------------------------------------------
 * Project number  : DC587 - DC_20021007_3167
 * Date            : 06-OCT-2002
 * Title           : Performanace improvement by using stack memory
 * Description     : For better performance stack memory should be used for NULL
 *                   character buffer instead of dynamic memory
 * ------------------------------------------------------------------------
*/
/*
 * -----------------------------------------------------------------------------
 * Change History
 * -----------------------------------------------------------------------------
 * Project Number : DC530
 * Date           : 2001-AUG-31
 * Description    : Changes for error log viewing - introduced new error code -
 *                  ACCESS_LMTEXEED_LITERAL_LEN
 * -----------------------------------------------------------------------------
 */
/*
 * -----------------------------------------------------------------------------
 * Change History
 * -----------------------------------------------------------------------------
 * Project Number : DC560
 * Date           : 2002-APR-19
 * Title          : Changes for viewing the query execution plan
 * -----------------------------------------------------------------------------
 */
/*
 * Change history
 * ------------------------------------------------------------------------
 * Project number : DC581
 * Date           : 2002-AUG-09
 * Description    : Conformance to JDBC 3.0 Spec
 * ------------------------------------------------------------------------
*/
/*
 * --------------------------------------------------------------------
 * Change history
 * --------------------------------------------------------------------
 * Project number   : DC571
 * Date             : 2002-OCT-10
 * Description      : Implementation of Batchupdate
 * -------------------------------------------------------------------
*/
/*
 * -----------------------------------------------------------------------------
 * Change History
 * -----------------------------------------------------------------------------
 * Project Number : DC587 - DC_20020730_3143
 * Date           : 2002-DEC-03
 * Title          : Support for NULL Constraint
 * -----------------------------------------------------------------------------
 */



/*
 * -----------------------------------------------------------------------------
 * Change History
 * -----------------------------------------------------------------------------
 * Project Number : DC591
 * Date           : 2003-JAN-20
 * Title          : Stabilization of JDBC driver on Unix platforms.
 * Description    : Inconsistent jdbc failures in unicode version because of 
 *                    tpe_uuid_t changes.
 * -----------------------------------------------------------------------------
 */
/*
 * ---------------------------------------------------------------------------
 * Change History
 * ---------------------------------------------------------------------------
 * Project Number : DC590
 * Date           : 2003-JAN-10
 * Description    : Changes for introduction of a new constant to define the
 *                  maximum size of the error message field in the error log.
 * ---------------------------------------------------------------------------
 */ 

 /*
  * -------------------------------------------------------------------------
  * Change History
  * -------------------------------------------------------------------------
  * Project Number : dc604
  * Date           : 2003-JUN-12
  * Title          : Integration of "DC588 : IP Address filtering by database
  *                  server" to Dharma/SQL 9.0 version. 
  * Description    : Added two error numbers.
  * -------------------------------------------------------------------------
 */
/* ---------------------------------------------------------------------------
 * Change history
 * ---------------------------------------------------------------------------
 * Project Number :DC594
 * Bug ID         :DC_20030410_3284
 * Date           :2003-JUN-23
 * Title          :Bug fixing over Dharma/SQL version 9.0
 * Description    :Defined a new error code SQL_ERR_INVDBNAME.
 * ---------------------------------------------------------------------------
 */
/*
 * ---------------------------------------------------------------------------
 *  Change History
 * ---------------------------------------------------------------------------
 *  Project Number : dc639
 *  Date           : 2004-FEB-05
 *  Title          : Case sensitive and insensitive search in Dharma/SQL
 *  Description    : Added one enum to have db case information.
 * ---------------------------------------------------------------------------
 */
/*
 * -----------------------------------------------------------------------------
 * Change History
 * -----------------------------------------------------------------------------
 * Project Number : DC602
 * Date           : 2003-MAY-13
 * Title          : Limiting number of records in result sets.
 * Description    : Error code for PERCENT and WITH TIES not supported in 
 *                  TOP clause
 * -----------------------------------------------------------------------------
 */

/* ---------------------------------------------------------------------------
 * Change history
 * ---------------------------------------------------------------------------
 * Project Number : dc611
 * Date           : 2003-SEP-09
 * Title          : Porting Customer changes to Dharma/SQL 9.0
 * Description    : Included dh_literals.h that contains all vendor specific
 *                  literals.
 * ---------------------------------------------------------------------------
 */

/* -------------------------------------------------------------------------
 *  Change History
 * -------------------------------------------------------------------------
 *  Project Number        : dc632
 *  Date                  : 
 *  Title                 : User Defined Scalar Functions
 *  Change Description    : Added two new error numbers
 *  -------------------------------------------------------------------------
 */
/*
 *--------------------------------------------------------------------------
 * Change History
 *--------------------------------------------------------------------------
 * Project Number      : dc625.
 * Date                : 24-Feb-2004.
 * Project             : Supporting 64 character identifiers in Dharma SQL.
 * Description         : Made changes so that we can have 64 character identifiers
 *--------------------------------------------------------------------------
*/
/*
 * -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project Number : dc630
 * Date           : 2003-DEC-16
 * Title          : Context sensitive error messages
 * Description    : Added context sensitive error information to make the 
 *                  error message more informative.
 * -------------------------------------------------------------------------
*/

/* ----------------------------------------------------------------------------
 * Change History
 * ----------------------------------------------------------------------------
 * Project Number : dc598
 * Date           : 2004-JUL-16
 * Title          : Dharma/SQL 10.0 Release Stabilization.
 * -----------------------------------------------------------------------------
 */

/* ---------------------------------------------------------------------------
 * Change History
 * ---------------------------------------------------------------------------
 * Project Number : dc598
 * Date           : 2004-JUL-18
 * Title          : Dharma/SQL 10.0 Release Stabilization.(version_change)
 * ---------------------------------------------------------------------------
 */
/* --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : dc643
 * Bug ID         : DC_19990720_948
 * Date           : 2004-NOV-20
 * Title          : Drop table with synonym name should return error.
 * Description    : Added new error number.
 * --------------------------------------------------------------------------*/

/* ----------------------------------------------------------------------------
 * Change History
 * ----------------------------------------------------------------------------
 * Project Number      : DC676
 * Date                : 2005-AUG-18
 * Title               : Disabling sqlda validation by default.
 * Change description  : Defined new API dh_set_sqlda_validation() and
 *                       tpe_set_sqlda_validation() to make validation of 
 *                       sqlda optional.
 * ----------------------------------------------------------------------------
 */

/* ----------------------------------------------------------------------------
 * Change History
 * ----------------------------------------------------------------------------
 * Project Number     : DC691
 * Date               : 2005-DEC-12
 * Title              : Performance Improvement of Marshalling and Unmarshalling
 * Change description : Introduced two macros SNW_SHORT_SZ1 & SNW_USHORT_SZ1 
 *                      representing 2 byte shor integer, which will be used 
 *                      by newly introduced marshalling routines for short ints.  
 * ----------------------------------------------------------------------------
 */


/* ----------------------------------------------------------------------------
 * Change History
 * ----------------------------------------------------------------------------
 * Project number   : DC672
 * Date             : 2005-JUN-14
 * Title            : Warning Removal over Dharma/SQL10.1
 * ----------------------------------------------------------------------------
 */

/* --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC_20060927_3699
 * Date           : 2006-SEP-27
 * Title          : Memory overwrite error in stored procedure execution
 *                  when total columns exceed 50.
 * --------------------------------------------------------------------------
 */
/* ------------------------------------------------------------------------
 * Change History
 * ------------------------------------------------------------------------
 * Project Number    : DC_20061204_3724
 * Date              : 2007-MAY-15
 * Title             : Support for 'Order By' in subqueries.
 * Description       : Added two new errors -20261 and -20262.
 * ------------------------------------------------------------------------
 */
/* ----------------------------------------------------------------------------
 * Change History
 * ----------------------------------------------------------------------------
 * Project Number     : DC717
 * Date               : 2006-DEC-18
 * Title              : odbcisql.
 * Change description : Introduced a dharma specific diagnostic identifier
 *                      SQL_DIAG_SYNTAX_ERR_POS to get the syntax error
 *                      position.
 * ----------------------------------------------------------------------------
 */


/* ----------------------------------------------------------------------------
 * Change History
 * ----------------------------------------------------------------------------
 * Project Number     : DC711 - DC_20070308_3767
 * Date               : 2007-MAR-08
 * Title              : Bug fixes in Access 11.02.
 * Change description : Fix for Drop synonym failure in ODBC: Introduced four 
 *                      macros SQL_SQLCA_STATE_LENGTH,
 *                      SQL_SQLCA_STATE_LENGTH_P1, SQL_SQLCA_NAME_LENGTH and 
 *                      SQL_SQLCA_NAME_LENGTH_P1 to avoid the hard coded values
 *                      for sqlca state and name lengths.
 * ----------------------------------------------------------------------------
 */

/*
 * ------------------------------------------------------------------------
 * Change history
 * ------------------------------------------------------------------------
 * Project number   : DC_20070827_3848
 * Date             : 2007-AUG-27
 * Title            : Increasing the depth of recursion in JSPs.
 * Description      : Increased the value of macro TPE_MAX_RECS_LEVEL.
 * ------------------------------------------------------------------------
 */
/* --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC_20070518_3797
 * Date           : 2007-AUG-01
 * Title          : Support for Preserve cursor behavior.
 * Description    : Included  new macros PRSRV_CUR and PRESERVE_CURSOR_KW
 * --------------------------------------------------------------------------
 */
/*
 * ---------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC737
 * Date           : 2008-APR-10
 * Title          : Customization Framework.
 * Description    : Used #if !defined(...) for various constants to define 
 *                  dharma default values. Also changed macros MAX and MIN to
 *                  DH_MAX and DH_MIN to avoid platform dependencies.
 * --------------------------------------------------------------------------
 */
/*
 * -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project Number   : DC_20080521_3912
 * Date             : 2008-JUN-30
 * Title            : Deletion of code that references extended data types.
 * Description      : Deleted the definition of the TPE_EXT_MAX_FLDLEN and
 *                    struct sbuf_hdl_t.
 * Date             : 2008-SEP-04
 * Title            : Added new error for data exceeding maximum literal
 *                    length, error number 20185:SQL_ERR_EXCEEDS_MAX_LITLEN.
 * -------------------------------------------------------------------------
 */
/* --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC738
 * Date           : 2008-JUL-9
 * Title          : SQL Engine Independent Portable ODBC Driver.
 * Description    : Declared the prototype for the function
 *                  dh_formsql_for_tables() and definition of 
 *                  enum table_info_type.
 * Date           : 2008-JUL-24
 * Description    : Declared the prototype for the function
 *                  dh_formsql_for_primaryrkeys().
 * Date           : 2008-JUL-25
 * Description    : Declared the prototype for the functions
 *                  dh_formsql_for_procedures() and dh_formsql_for_columns().
 * Date           : 2008-JUL-28
 * Description    : Declared the prototype for the functions
 *                  dh_formsql_for_foreignkeys(),
 *                  dh_formsql_for_columnprivileges,  
 *                  dh_formsql_for_tableprivileges, 
 *                  dh_formsql_for_procedurecolumns() and
 *                  dh_formsql_for_specialcolumns.
 * Date           : 2008-JULY-29
 * Description    : Added prototypes for functions dh_set_login_timeout(),
 *                  dh_get_db_case(), dh_get_identifier_case(),
 *                  dh_set_open_deferred() and dh_set_query_timeout().
 * Date           : 2008-JUL-31
 * Description    : Declared the prototype for the function
 *                  dh_formsql_for_statistics.
 * Date           : 2008-AUG-14
 * Description    : Declared the prototype for the function
 *                  dh_sqlgettypeinfo(). 
 * Date           : 2008-SEP-02
 * Description    : Declared the enum of type sql_idcase_t. 
 * --------------------------------------------------------------------------
 */
/*
 * --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC746
 * Date           : 2009-MAR-03
 * Title          : Support for new scalar functions.
 * Description    : Added tpe_truncate function prototype.
 * --------------------------------------------------------------------------
 */
/*
 * --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC698, DC753 / DC_20090608_3997
 * Date           : 2009-Jun-11
 * Title          : Dharma/SQL Access 11.05 Release
 * Description    : Fix for the bug - Retrievel from lvc column fails in
 *                  MS Word and MS Excel: Added constant TPE_DT_VARBINARY
 *                  for varbinary data types.
 * --------------------------------------------------------------------------
 */
/*
 * --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC_20091203_4062
 * Date           : 2009-DEC-03
 * Title          : Support for IDENTITY column in tables.
 * Description    : Added two new macros,
 *                  SQL_ERR_DUP_DFLT_IDENT and
 *                  SQL_ERR_INS_UPD_IDENT.
 * --------------------------------------------------------------------------
 */
/*
 * --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC_20100615_4100
 * Date           : 2010-JUN-29
 * Title          : Support for Primary key, Foreign key and Unique key
 *                  constraints with Dynamic metadata.
 * --------------------------------------------------------------------------
 */
/*
 * --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DC763
 * Date           : 2010-JUNE-30
 * Title          : Support for implementation of SKIP clause.
 * Description    : Modified constant name SQL_ERR_ORDBY_WOUT_TOP_IN_SUBQ to
 *                  SQL_ERR_ORDBY_WOUT_TOP_OR_SKIP_IN_SUBQ in order to use it
 *                  for TOP as well as SKIP clause.
 *
 * --------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change history
 * -------------------------------------------------------------------------
 * Project Number : DC761
 * Date           : 2010-AUG-09
 * Title          : Integration of SDK11.04 changes into SQL/Access.
 * -------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change history
 * -------------------------------------------------------------------------
 * Project Number : DC767
 * Date           : 2010-AUG-10
 * Title          : Alter Statement Enhancements
 * -------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project Number : DC_20110915_4181
 * Date           : 2011-SEP-16
 * Title          : SDK Server crashes if dhcs_ix_open() is not defined
 *                  even when DHCS_IX_UPD_REQUIRED is false.
 * -------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change history
 * -------------------------------------------------------------------------
 * Project number  : DC_20111018_4183 
 * Date            : 2011-OCT-03
 * Title           : Fixing minor issues relating to alter table MODIFY_COL
 *                   command.
 * -------------------------------------------------------------------------
 */
/* --------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project Number : DS2010407_SKIP
 * Date           : 2012-April-10
 * Title          : Implement SKIP functionality
 * Description    : Back port of SKIP functionality from V12 to V11
 * --------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project number   : DC_20130904_4225
 * Date             : 2013-AUG-01
 * Title            : Enhancing and fixing bugs in WITH clause implementation.
 * --------------------------------------------------------------------------
 */
/* ------------------------------------------------------------------------
 * Change History
 * ------------------------------------------------------------------------
 * Project number   : DC777
 * Date             : 2013-OCT-31
 * Title            : Dharma/SQL Access 14.0 Release.
 * ------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project number   : DC_20140319_4233
 * Date             : 2014-APR-14
 * Title            : Support for USERGROUP feature,so that Grant and Revoke
 *		      operations could be done on a group of users.	
 * -------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * -------------------------------------------------------------------------
 * Project number   : DC_20140530_4235
 * Date             : 2014-MAY-30
 * Title            : Support for having Java Stored Procedures with 
 * 		      resultsets as table references in SELECT queries.	
 * -------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project number   : DS_20140314_0004
 * Date             : 2014-MAR-14
 * Title            : Scrollable Cursors
 * --------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project number   : DS_20151102_0009
 * Date             : 2015-NOV-02
 * Title            : Warning removal
 * --------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project number   : DC_20170106_4264
 * Date             : 2017-JAN-06
 * Title            : Support for SEQUENCES.
 * --------------------------------------------------------------------------
 */
/* -------------------------------------------------------------------------
 * Change History
 * --------------------------------------------------------------------------
 * Project number   : DC780
 * Date             : 2017-DEC-04
 * Title            : Dharma/SQL Access 15.00 Release.
 *		      Selecting from a view that has self-reference, crashes 
 *		      the server.		      
 * --------------------------------------------------------------------------
 */

#ifndef		sql_lib_included
#define		sql_lib_included
#include <stdio.h> 
/* DC317 BEGIN */
#include <stddef.h>
/* DC317 END */
#include "os_dhtp.hxx" 

/* dc611 BEGIN : Porting Customer changes to Dharma/SQL 9.0 
 * 
 * Included dh_literals.h that contains all vendor specific literals.
 */

#include "dh_literals.h"

#ifdef FAIRCOM_MOD
#if defined ctSQLSRVR || defined CTREE_STDHDR
#ifdef __cplusplus
extern "C" {
#endif
#include "ctstdr.h"
#include "ctoptn.h"
#ifdef __cplusplus
}
#endif
#endif
#endif

/* dc611 END : Porting Customer changes to Dharma/SQL 9.0 */

#ifdef  DH_OS_MSWIN

#ifndef EXPORT
#define EXPORT __export
#endif
#else /* MSWIN */
#if defined (DH_OS_WINNT) || defined (DH_OS_WIN95)
    /* DC404 BEGIN */
/*  For NT the symbols are exported by including their name in dhserver.def file and hence EXPORT is defined as blank.*/
#define EXPORT 
    /* DC404 END */
#else /* Winnt / Win95 */

#ifndef EXPORT
#define EXPORT 
#endif
#endif /* Winnt / Win95 */
#endif /* MSWIN */

#if defined FAIRCOM_MOD && defined ctSQLSRVR
#if defined(__cplusplus)
	extern "C" ULONG ctmusers; /* Maximum allowed connected clients. */
#else
	extern ULONG ctmusers; /* Maximum allowed connected clients. */
#endif

#ifdef ctFeatCONNGROUP
#define TPE_MAX_THREADS MXU2
#else
#define TPE_MAX_THREADS ctmusers
#endif
#else
#define TPE_MAX_THREADS 202  /* DC368 */
#endif

/*
 * dc629 BEGIN : Performance enhancement.
 * Default value for odbc fetch buffer size. Used when
 * DH_ODBC_FETCH_BUFFER_SZ is not set.
 */
#define DFLT_MF_ARRAYSIZE 1000000
/*
 * dc629 END : Performance enhancement.
 */

/*
 * DC717 BEGIN
 * Introduced a new Dharma specific diagnostic field identifier for use in
 * odbcisql to get syntax error position in an SQL statement using ODBC API
 * SQLGetDiagField(...) as the ODBC standard does not a have such an
 * identifier.
 */
                                                                                
#define SQL_DIAG_SYNTAX_ERR_POS  99
                                                                                
/*
 * DC717 END
 */

/*
 * enumerated type for procedure arguments (input arg or input/output arg) 
 */
typedef enum  {
	INPUT_PARAM,
	INPUT_OUTPUT_PARAM
} proc_argtype_t ;


typedef		void	   *tpe_db_hdl_t ;
typedef		void	   *tpe_cursor_t ;
typedef		void	   *tpe_tm_hdl_t ;

/* BEGIN DC569 DC_20020723_3127 */
typedef void *dh_sqlenv_hdl_t;
/* END DC569 DC_20020723_3127 */
typedef  dh_i32_t tpe_status_t  ;

/* DC591 BEGIN : Stabilization of JDBC driver on Unix platforms */

/* All dh_char_t datatype variables are changed to dh_u8_t */
typedef struct {
     dh_u32_t time_high ; 
     dh_u16_t time_low ; 
     dh_u16_t time_out ;  /*DC_20080910_3930 */
     dh_u8_t family ; 
     dh_u8_t host1 ; 
     dh_u8_t host2 ; 
     dh_u8_t host3 ; 
     dh_u8_t host4 ; 
     dh_u8_t host5 ; 
     dh_u8_t host6 ; 
     dh_u8_t host7 ; 
} tpe_uuid__t  ;

/* DC591 END : Stabilization of JDBC driver on Unix platforms */

/*
 * Types of nullability for sqlda_flags 
 */
typedef enum  {
	SQL_NO_NULLS,
	SQL_NULLABLE,
	SQL_NULLABLE_UNKNOWN
} tpe_nullability_t ;

/* Attach to a database */

typedef enum {
    SQL_ATTACH_REMOTE, /* for attaching to a remote database */
    SQL_ATTACH_LOCAL   /* for attaching to a local database  */
} tpe_attachtype_t ; 

typedef enum {
    SQL_COMPAT_ANSI    /* ANSI SQL compatibility. */
} tpe_sqlcompat_t ;

typedef enum {
	SQL_DISCONNECT_CONNECTION,
	SQL_DISCONNECT_ALL,
	SQL_DISCONNECT_DEFAULT,
	SQL_DISCONNECT_CURRENT
} tpe_discon_sp_t;

/* DC698 BEGIN */
/* dc651 BEGIN : Enabling Client-Server Edition Mismatch checks */
enum sdk_server_edition {SDK_PR = 1, SDK_NC, SQL_AC};
/* dc651 END : Enabling Client-Server Edition Mismatch checks */
/* DC698 END */

/* DC_20100615_4100 Begin  */
#define		SQL_ERR_INVAL_CNSTR	-20264
/* DC_20100615_4100 End  */

/* DC_20170106_4264 BEGIN */
#define		SQL_ERR_DUPSEQ	   	     -20265
#define		SQL_ERR_BADSEQ		     -20266
#define		SQL_ERR_NOSEQ		     -20267
#define		SQL_ERR_STRT_GT_MAXVAL	     -20268
#define		SQL_ERR_STRT_LT_MINVAL	     -20269
#define		SQL_ERR_INVLD_MINVAL         -20270
#define		SQL_ERR_INVLD_INCR	     -20271
#define		SQL_ERR_ALT_STRT 	     -20272
#define		SQL_ERR_ALT_NO_OPT	     -20273
#define		SQL_ERR_NXT_EXCDS_MAXVL	     -20274
#define		SQL_ERR_NXT_EXCDS_MINVL	     -20275
#define		SQL_ERR_INVLD_SEQ_PRIV	     -20276
/* DC_20170106_4264 END */

#define         SQL_ERR_MULTDBNOTSUPP        -20277    /* DS_20170619_0018 */
#define         SQL_ERR_MULTINSNOPARAM       -20278    /* DS_20170619_0019 */

#define		SQL_ERR_BADVIEWREF           -20279 /* DC780 */

typedef struct {
       /* 
        * In case data members in cost_card_t or cost_time_t are changed  to 
        * type other than dh_u32_t, these also should be changed .
        */	
/* DC118 BEGIN */

	dh_f64_t cost;
	dh_f64_t card;

/* DC118 END */
	dh_i32_t treesize;
        dh_i32_t rss_calls;
} cost_val_t ;
	
#if defined (__cplusplus)
extern "C" {
#endif

/* BEGIN DC569 - DC_20020607_3072 */
/* Maximum length for error messages */
#define         TPE_MAX_ERRLEN          511
#define         TPE_MAX_ERRLEN_P1       (TPE_MAX_ERRLEN + 1)
/* END   DC569 - DC_20020607_3072 */

/* dc630 BEGIN :context sensitive error message support */
/* 
 * Introduced TPE_MAX_ERR_INFO_NUM for maximum number of 
 * context sensitive error
 */

#define         TPE_MAX_ERR_INFO_NUM    6	

/* dc630 END :context sensitive error message support */

/* DC711 - DC_20070308_3767 BEGIN */
/*
 * Introduced macros for sqlca state and name lengths. 
 */

#define		SQL_SQLCA_STATE_LENGTH		5
#define		SQL_SQLCA_STATE_LENGTH_P1	(SQL_SQLCA_STATE_LENGTH + 1)
#define		SQL_SQLCA_NAME_LENGTH		127
#define		SQL_SQLCA_NAME_LENGTH_P1	(SQL_SQLCA_NAME_LENGTH + 1)

/* DC711 - DC_20070308_3767 END*/

/* DC_20070518_3797 Begin  */
#define  PRSRV_CUR   0x00000001
#define  PRESERVE_CURSOR_KW  DH_STRING_LITERAL("PRSRVCUR")
/* DC_20070518_3797 END    */

#ifdef FAIRCOM_MOD
#define SSL_DBOPTION_KW  DH_STRING_LITERAL("SSL")
#endif
/* (DC044) .BEGIN */
/* enhanced sqlca data structure to contain the sql-92 diagnostics
informations */

struct sqlca {
	dh_char_t	sqlcaid[8] ;
	dh_i32_t	sqlcabc ;
	dh_i32_t	sqlcode ;
	dh_u16_t 	sqlerrml ;
	/* BEGIN DC569 - DC_20020607_3072 */
	/* BEGIN DC355 */
        /* DS_19981124_932 - SQL Error Messages truncated */
        dh_char_t       sqlerrm[TPE_MAX_ERRLEN_P1] ; /* changed from 72 to 256 to 512 */
        /* END DC355 */
	/* END DC569 - DC_20020607_3072 */
	dh_char_t 	sqlerrp[8] ;
	dh_i32_t	sqlerrd[8];
	dh_char_t 	sqlwarn[8] ;
	dh_char_t	sqlext[8] ;
	cost_val_t estimated_cost,          /* estimated cost information */
		   actual_cost;             /* actual cost information */
	
	dh_i32_t	number ;
	dh_char_t	more[1];
        /* DC711 - DC_20070308_3767 BEGIN */
	dh_char_t	command_function[SQL_SQLCA_NAME_LENGTH_P1] ; 
	dh_char_t	dynamic_function[SQL_SQLCA_NAME_LENGTH_P1] ;

	dh_i32_t	condition_number ;
	dh_char_t	returned_sqlstate[SQL_SQLCA_STATE_LENGTH_P1] ; 
	dh_char_t   class_origin[SQL_SQLCA_NAME_LENGTH_P1] ; 
	dh_char_t	subclass_origin[SQL_SQLCA_NAME_LENGTH_P1] ;  
	dh_char_t	table_name[SQL_SQLCA_NAME_LENGTH_P1] ;  
	dh_char_t	column_name[SQL_SQLCA_NAME_LENGTH_P1] ;
        /* DC711 - DC_20070308_3767 END */
} ;


/*
 * sqlca and SQLCODE shoud be defined in the TPE application, 
 * e.g., in isqlmain, syscreat etc
 */


extern	struct	sqlca sqlca ;
extern  dh_i32_t	SQLCODE;
#ifdef FAIRCOM_MOD /*conflicting with ODBC headers*/
#ifdef DH_ESQL
extern dh_char_t  SQLSTATE[6];
#endif
#else
extern dh_char_t  SQLSTATE[6];
#endif

#define DIAG_MAX_CONDNUM  1
#define DIAG_MAX_DIAGVAR  19
#define  DIAG_MAX_DETAIL_AREA 1
#define  DIAG_MIN_HEADER_INFONUM   0
#define  DIAG_MAX_HEADER_INFONUM   4
#define  DIAG_MIN_DETAIL_INFONUM   5
#define  DIAG_MAX_DETAIL_INFONUM   15
/*  DC555 DC_20020919_3159 Begin  */
#define  DH_DFLT_RSS_ERR_STATE     DH_STRING_LITERAL("09000")
#define  DH_DFLT_RSS_ERR_MSG       DH_STRING_LITERAL("Storage System Error")
/*  DC555 DC_20020919_3159 End    */      


typedef enum {
	    NUMCOND,
	    MORE_KW,
	    CMD_FUNC,
	    DYN_FUNC,
	    ROW_CNT,
	    CONDNUM,
	    RET_STATE,
	    CLS_ORG,
	    SCLS_ORG,
	    TBL_NAME,
	    CLM_NAME,
	    MSG_TXT,
	    MSG_LTH,
	    SQCD,
	    SQWN,
	    EST_COST,
	    ACT_COST,
	    POSN,
	    FET_CNT
	  } diag_kwd_t;

/*  (DC044) .END */

/* DC065 .BEGIN. */

 /*
  * NOTE: DC487:DC_20001122_1862
  *
  * The usage of the following fields is clarified:
  *
  * sqld_lengths  : 1. For character data types,it represents the data length 
  *                    in terms of the number of bytes. It includes the null 
  *                    terminator size. For  purposes of any memory allocation
  *                    this field should be made use of.
  *                    eg,
                       n(var)char(10) -> 22
                       n(var)char(10) with CS -> 11
                       (var)char(10)  -> 11
                       (var)char(10) with CS -> 11
  *                 2. For  other  data  types, the content represents the
  *                    number of bytes.
  *
  * sqld_clengths : This field is not used in the SQL9.0 version
  *
  * sqld_precision: For character type fields, this represents the field
  *                 width that is specified during the creation of the table. 
  *                 This represents the maximum number as follows:
  *                 n(var)char field -> Number of Unicode characters
  *                 n(var)char field th CS -> Number of bytes 
  *                 (var)char field -> Number ofbytes 
  *                 (var)char field th CS -> Number of bytes 
  *                 It does not include the null terminator.
  */ 

struct sqlda {
 		dh_i16_t   sqld_size;             
 		dh_i16_t   sqld_nvars;           
 		dh_char_t  ** sqld_varptrs;     
 		dh_i32_t * sqld_lengths;       
 		dh_i16_t * sqld_types  ; 
#if defined FAIRCOM_MOD && defined ctSQL_DAPRECISION
		dh_i32_t * sqld_precision;
#else
		dh_i16_t * sqld_precision; 
#endif
 		dh_i16_t * sqld_scale   ; 
 		dh_i16_t * sqld_flags  ; 
 		dh_i16_t ** sqld_ivarptrs;        
 		dh_i16_t    sqld_varnmsize;      
 		dh_i16_t    sqld_indvarnmsz;    
 		dh_char_t **  sqld_varnames   ;
 		dh_char_t **  sqld_indvarnames ;    
 		dh_i16_t    sqld_arraysz      ;   

		dh_i32_t * sqld_clengths;
		dh_i32_t * sqld_returned_lengths;
		dh_i16_t * sqld_odbc_flags;
 		dh_i16_t *  sqld_date_int_code ; 
 		dh_i16_t *  sqld_date_int_prec ; 
 		dh_char_t **  sqld_collat_name   ;  	
 		dh_char_t **  sqld_charset_name   ; 
 		dh_i16_t   sqld_max_size        ;     

 		dh_char_t **  sqld_base_column_name;
 		dh_char_t **  sqld_base_table_name;
 		dh_i16_t *  sqld_searchable    ;
 		dh_i16_t *  sqld_updatable;
		dh_i16_t *  sqld_param_type;
		dh_char_t **  sqld_table_name;
		dh_i16_t *  sqld_verbose_types;
 };

typedef	struct	sqlda sqlda ;

/* 
For sqld_flags bit operations
*/

#define ITEM_AUTO	0x0001	/*AUTO increment flag*/
#define ITEM_SIGN	0x0002	/*IS_SIGNED flag */
#define ITEM_UNNAMED 	0x0004	/*IS_UNNAMED flag */
#define ITEM_CS		0x0008	/*IS_CASE_SENSITIVITY flag */
/* DC_19990202_460 BEGIN */
#define ITEM_VARCHAR  0x0010  /*IS_VARCHAR flag */
#define ITEM_VARBINARY  0x0020  /*IS_VARBINARY flag */
/* DC_19990202_460 END */
/* BEGIN DC362 */
/* DC_19990323_666
   getColumnTypeName() is not working. */

#define ITEM_MONEY  0x0040  /*IS_MONEY flag */
/* END DC362 */

/* DC581 BEGIN : Conformance to JDBC 3.0 Spec */

#define ITEM_NVARCHAR  0x0080  /*IS_NVARCHAR flag */

/* DC581 BEGIN : Conformance to JDBC 3.0 Spec   */
 
/* 
An enumerated data type descr_kwd_t consisting of all the
descriptor field names 
*/

#define 	BATCH_ANL_PARAM_COUNT 10   /* DC577 (BATCH ANL) */

typedef enum {
	  COUNT_T,
	  TYPE_T,
	  LEN_T,
	  OCT_LEN_T,
	  RET_LEN_T,
	  PREC_T,
	  SCALE_T,
	  DATE_INT_CODE_T,
	  DATE_INT_PREC_T,
	  NULL_T,
	  NAME_T,
	  UNNAMED_T,
	  COLLAT_NAME_T,
	  CHAR_SET_NAME_T,
	  DAT_T,
	  IND_T,
	  COL_NAME_T,
	  TBL_NAME_T,
	  CS_T,
	  SEARCH_T,
	  UNSIGN_T,
	  UPD_T,
	  PARAM_T,
	  TBL_T,
	  AUTO_T,
	  VERBOSE_T
	}descr_kwd_t;

# define DESC_MAX_VAR 27

/* strcture containing the field and host variable informations */

typedef struct {
	   descr_kwd_t  field_info[DESC_MAX_VAR];  
	   /* DC148 */
	   dh_char_t	** host_info;
	   dh_boolean  is_const[DESC_MAX_VAR];
	   }item_lst;


/* DC065 END */
/* 
 * Structure for getting a piece of data from a field of LONG type
 */
 
struct getdata_t {
 	dh_i32_t   position;	/* IN offset , OUT balance data length */
 	void      *buf;	        /* buffer pointer */
 	dh_i32_t   buf_len;	/* length of buffer */
 	dh_char_t *hdl;         /* Field handle */
 	dh_i16_t   htype;  	/* host type  */
};
 
typedef struct getdata_t getdata_t;

/* 
 * Structure for writing a piece of data in to a field of LONG type
 */

struct putdata_t {
 	dh_i32_t   position;	/* IN offset */
 	void      *buf;	        /* buffer pointer */
 	dh_i32_t   buf_len;	/* length of buffer */
 	dh_char_t *hdl;         /* Field handle */
   	dh_i16_t   htype;  	/* host type  */
};
 
typedef struct putdata_t putdata_t;

 
 /* values for type of info in tpe_sqlgetinfo */
 
typedef enum {
 	DH_SQL_CONVERT_FUNCTIONS,
 	DH_SQL_NUMERIC_FUNCTIONS,
 	DH_SQL_STRING_FUNCTIONS,
 	DH_SQL_SYSTEM_FUNCTIONS,
 	DH_SQL_TIMEDATE_FUNCTIONS,
 	DH_SQL_TIMEDATE_ADD_INTERVALS,
 	DH_SQL_TIMEDATE_DIFF_INTERVALS,
 	DH_SQL_DATASOURCE_READ_ONLY,
 	DH_SQL_IDENTIFIER_QUOTE_CHAR,
 	DH_SQL_OWNER_USAGE,
 	DH_SQL_MISC1_FUNCTIONS,
 	DH_SQL_MISC2_FUNCTIONS,
 	DH_SQL_MISC3_FUNCTIONS,
	DH_SQL_FAIRCOM_FUNCTIONS
 }dh_infoid_t;
 	
 
 /* values for type of info in tpe_sqlgetfunction */
 /* The order should not be changed since the mapping will be effected */
 
typedef enum {
 	DH_SQL_API_ALL_FUNCTIONS,
 	DH_SQL_API_SQLALLOCCONNECT,
 	DH_SQL_API_SQLALLOCENV,
 	DH_SQL_API_SQLALLOCSTMT,
 	DH_SQL_API_SQLBINDCOL,
 	DH_SQL_API_SQLCANCEL,
 	DH_SQL_API_SQLCOLATTRIBUTES,
 	DH_SQL_API_SQLCONNECT,
 	DH_SQL_API_SQLDESCRIBECOL,
 	DH_SQL_API_SQLDISCONNECT,
 	DH_SQL_API_SQLERROR,
 	DH_SQL_API_SQLEXECDIRECT,
 	DH_SQL_API_SQLEXECUTE,
 	DH_SQL_API_SQLFETCH,
 	DH_SQL_API_SQLFREECONNECT,
 	DH_SQL_API_SQLFREEENV,
 	DH_SQL_API_SQLFREESTMT,
 	DH_SQL_API_SQLGETCURSORNAME,
 	DH_SQL_API_SQLNUMRESULTCOLS,
 	DH_SQL_API_SQLPREPARE,
 	DH_SQL_API_SQLROWCOUNT,
 	DH_SQL_API_SQLSETCURSORNAME,
	DH_SQL_API_SQLSETPARAM,
        DH_SQL_API_SQLTRANSACT,
 	DH_SQL_API_SQLCOLUMNS = 40,        /*  Level 1 Functions */
	DH_SQL_API_SQLDRIVERCONNECT,
 	DH_SQL_API_SQLGETCONNECTOPTION,
 	DH_SQL_API_SQLGETDATA,
 	DH_SQL_API_SQLGETFUNCTIONS,
 	DH_SQL_API_SQLGETINFO,
 	DH_SQL_API_SQLGETSTMTOPTION,
 	DH_SQL_API_SQLGETTYPEINFO,
 	DH_SQL_API_SQLPARAMDATA,
 	DH_SQL_API_SQLPUTDATA,
 	DH_SQL_API_SQLSETCONNECTOPTION,
 	DH_SQL_API_SQLSETSTMTOPTION,
 	DH_SQL_API_SQLSPECIALCOLUMNS,
 	DH_SQL_API_SQLSTATISTICS,
 	DH_SQL_API_SQLTABLES,
 	DH_SQL_API_SQLBROWSECONNECT,     
 	DH_SQL_API_SQLCOLUMNPRIVILEGES,
 	DH_SQL_API_SQLDATASOURCES,
 	DH_SQL_API_SQLDESCRIBEPARAM,
 	DH_SQL_API_SQLEXTENDEDFETCH,
 	DH_SQL_API_SQLFOREIGNKEYS,
 	DH_SQL_API_SQLMORERESULTS,
 	DH_SQL_API_SQLNATIVESQL,
 	DH_SQL_API_SQLNUMPARAMS,
 	DH_SQL_API_SQLPARAMOPTIONS,
 	DH_SQL_API_SQLPRIMARYKEYS,
 	DH_SQL_API_SQLPROCEDURECOLUMNS,
 	DH_SQL_API_SQLPROCEDURES,
 	DH_SQL_API_SQLSETPOS,
 	DH_SQL_API_SQLSETSCROLLOPTIONS,
 	DH_SQL_API_SQLTABLEPRIVILEGES,
 	DH_SQL_API_SQLDRIVERS,
 	DH_SQL_API_SQLBINDPARAMETRE
}dh_fnid_t;
 
/* BEGIN DC569 DC_20020723_3127 */

/* The function dh_alloc_sqlenv() allocates the Dharma SQL environment required for containing the context for use by the C programmatic interfaces and returns a handle to the allocated SQL environment . This environment cannot be shared across multiple connections ,hence each connection should allocate a seperate sql_env_t handle    */
 
extern  void EXPORT dh_alloc_sqlenv(
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_sqlenv_hdl_t *         /* IN Address of a variable of type dh_sqlenv_hdl_t */
#endif
);

/*  Frees the Dharma SQL environment allocated using the
                           dh_alloc_sqlenv function */

extern  void EXPORT dh_free_sqlenv(
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_sqlenv_hdl_t           /* IN Dharma SQL environment handle */
#endif
);
/* END DC569 DC_20020723_3127 */
 	
/*
 * Set a db handle as the current db handle.
 */

/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_set_curdbhdl (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t,            /* IN Dharma SQL environment handle */
    tpe_db_hdl_t,             /* IN  db handle        */
    struct sqlca      *       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */
extern void EXPORT
tpe_set_curdbhdl (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_db_hdl_t,				/* IN  db handle     	*/
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_sqlconnect(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    const dh_sqlenv_hdl_t  ,        /* IN Dharma SQL environment handle */
    const dh_char_t * ,             /* IN connect_string                */
    const dh_char_t * ,             /* IN connection_name               */
    const dh_char_t * ,             /* IN user_id                       */
    const dh_char_t * ,             /* IN user authentication           */
    const dh_char_t * ,             /* IN user dboptions                */
    struct sqlca    *               /* OUT sqlca pointer                */
#endif
);
/* END DC569 DC_20020723_3127 */

/* DS_19970121_682 START */
extern void EXPORT
tpe_sqlconnect(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    const dh_char_t * ,				/* IN connect_string	*/
    const dh_char_t * ,				/* IN connection_name	*/
    const dh_char_t * ,				/* IN user_id		*/
    const dh_char_t * ,				/* IN user authentication*/
    const dh_char_t * ,                         /* IN user dboptions     */
    struct sqlca    * 				/* OUT sqlca pointer */
#endif
);

/* DS_19960121_682 END */
/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_sql_setconnection(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
        dh_sqlenv_hdl_t ,           /* IN Dharma SQL environment handle */
        dh_char_t * ,               /* IN connection_name   */
        struct sqlca  *             /* OUT sqlca pointer    */
#endif
);
/* END DC569 DC_20020723_3127 */

extern void EXPORT
tpe_sql_setconnection(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_char_t * ,				/* IN connection_name	*/
    struct sqlca	*			/* OUT sqlca pointer    */
#endif
);

/* BEGIN DC569 DC_20020723_3127 */
extern tpe_status_t EXPORT
dh_cancel(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
     dh_sqlenv_hdl_t ,          /* IN Dharma SQL environment handle */
     tpe_db_hdl_t ,                                   /* IN dbhdl */
     tpe_cursor_t                                    /* IN cursor  */
#endif
);
/* END DC569 DC_20020723_3127 */

/* the cancel api used by the client to send
   a cancel request to the server */
extern tpe_status_t EXPORT
tpe_cancel(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
     tpe_db_hdl_t ,				/* IN dbhdl */
     tpe_cursor_t 				/* IN cursor  */
#endif
);

/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_sql_disconnect(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,  /* IN Dharma SQL environment handle */
    tpe_discon_sp_t,   /* Disconnection specification type            */
    dh_char_t * ,      /* IN connection_name  */
    struct sqlca *     /* OUT sqlca pointer        */
#endif
);
/* END DC569 DC_20020723_3127 */

extern void EXPORT
tpe_sql_disconnect(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_discon_sp_t,	/* Disconnection specification type */
    dh_char_t * ,		/* IN connection_name	*/
    struct sqlca	*	/* OUT sqlca pointer    */
#endif
);

/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_get_dbhdl_list(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,               /* IN Dharma SQL environment handle */
    tpe_db_hdl_t      [],                     /* OUT  dbhandle        */
    dh_i16_t          *,                      /* OUT nhandles         */
    struct sqlca      *                       /* OUT sqlca pointer    */
#endif
);
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_get_dbhdl_list(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_db_hdl_t	[],			/* OUT  dbhandle 	*/
    dh_i16_t		*,			/* OUT nhandles		*/
    struct sqlca	*			/* OUT sqlca pointer	*/
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_get_connection_info(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,               /* IN Dharma SQL environment handle */
    tpe_db_hdl_t,                             /* IN  db handle        */
    dh_char_t         *,                      /* OUT dbname           */
    dh_char_t         *,                      /* OUT connection name  */
    dh_boolean                *,              /* OUT is_default       */
    struct sqlca      *                       /* OUT sqlca pointer    */
#endif
);
/* END DC569 DC_20020723_3127 */

extern void EXPORT
tpe_get_connection_info(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_db_hdl_t,				/* IN  db handle 	*/
    dh_char_t		*,			/* OUT dbname		*/
    dh_char_t		*,			/* OUT connection name	*/
    dh_boolean		*,			/* OUT is_default	*/
    struct sqlca	*			/* OUT sqlca pointer	*/
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern dh_boolean  EXPORT
dh_validate_dbhdl(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,           /* IN Dharma SQL environment handle */
    tpe_db_hdl_t              /* IN  db handle        */
#endif
);
/* END DC569 DC_20020723_3127 */

extern dh_boolean  EXPORT
tpe_validate_dbhdl(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_db_hdl_t				/* IN  db handle 	*/
#endif
);

/* BEGIN DC569 DC_20020723_3127 */
extern dh_boolean EXPORT
dh_conn_to_dflt_if_any(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,          /* IN Dharma SQL environment handle */
    struct sqlca      *      /* OUT sqlca pointer          */
#endif
);
/* END DC569 DC_20020723_3127 */

extern dh_boolean EXPORT
tpe_conn_to_dflt_if_any(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    struct sqlca	*			/* OUT sqlca pointer	     */
#endif
);


/*
 * Print out the error message associated with the error code.
 * Also print out the message specified by the app.
 */
extern dh_i32_t  EXPORT
tpe_print_error (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	  dh_i32_t,		/* error code */
	  const dh_char_t *	/* message */
#endif
);

/* 
 * Print out the error message and code stored in the SQLCA.
 */ 
extern dh_i32_t  EXPORT
tpe_check_error (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	  struct sqlca *
#endif
);

/*
 * Set the fields of a sqlda with the given values.
 * 	(Used to allocate sqlda on stack).
 */

/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_set_sqlda (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
struct        sqlda   *,                      /* INOUT pointer to sqlda   */
dh_i32_t              ,                       /* IN    sqlda size         */
dh_i32_t              ,                       /* IN    sqlda array size   */
dh_i16_t              *,                      /* IN    array of types     */
/* DC065 BEGIN .*/
dh_i32_t              *,                      /* IN    array of lengths   */
/* DC065 END. */
dh_char_t             **,                     /* IN    array of var ptrs  */
dh_char_t             **                      /* IN    array of indvar ptrs */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_set_sqlda (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
struct	sqlda	*,			/* INOUT pointer to sqlda   */
dh_i32_t		,			/* IN    sqlda size         */
dh_i32_t		,			/* IN    sqlda array size   */
dh_i16_t		*,			/* IN    array of types     */
/* DC065 BEGIN .*/
dh_i32_t 		*,			/* IN    array of lengths   */
/* DC449 */
dh_i32_t 		*,			/* IN    array of clengths   */
/* DC065 END. */
dh_char_t		**,			/* IN    array of var ptrs  */
dh_char_t		**,			/* IN    array of indvar ptrs */
/* DC587 Begin */
dh_char_t		**,			/* IN    array of collet name ptrs */
dh_char_t		**			/* IN    array of charset name ptrs */
/* DC587 End */
#endif
) ;

/*
 * Set the fields of a sqlda to use the given buffer of given size.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern dh_i32_t  EXPORT
dh_setup_sqlda (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
struct        sqlda   *,                      /* INOUT pointer to sqlda */
dh_char_t             *,                      /* IN    array of bytes */
dh_u32_t                                      /* IN    size of array */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern dh_i32_t  EXPORT
tpe_setup_sqlda (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
struct	sqlda	*,				/* INOUT pointer to sqlda */
dh_char_t		*,				/* IN    array of bytes	*/
dh_u32_t					/* IN    size of array */
#endif
) ;

/*
 * Set all the field types to CHAR so that the BE must do all the conversion
 * and data can be returned as character strings using the given buffer.
 */

extern dh_i32_t   EXPORT
tpe_char_sqlda (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
struct	sqlda	*,				/* INOUT pointer to sqlda   */
dh_char_t		*,			/* IN    array of bytes	*/
dh_u32_t					/* IN    size of array */
#endif
) ;

/*
 * Set all the field types to the appropriate host types
 * and have data returned using the given buffer.
 */

extern dh_i32_t   EXPORT
tpe_host_sqlda (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
struct	sqlda	*,				/* INOUT pointer to sqlda   */
dh_i8_t		*,				/* IN    array of bytes	*/
dh_u32_t					/* IN    size of array */
#endif
) ;

/* Prdh_i32_t the tuples stored in the SQLDA to the given file. */

extern dh_i32_t	 EXPORT 
tpe_print_sqlda(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	struct sqlda *,		/* IN contains the tuples */
	struct sqlca *,		/* IN contains # of tuples */
	dh_file_t *			/* IN output file */
#endif
);

  
/* Print the tuples with LONG data to the given file. */

extern dh_i32_t EXPORT
tpe_print_sqlda_data (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
        struct sqlda *,               /* IN contains the data */
        tpe_db_hdl_t,                 /* IN database */
        tpe_tm_hdl_t,                 /* IN transaction */
        tpe_cursor_t,                 /* IN cursor */
        struct sqlca *,               /* INOUT # tuples & errors */
        dh_file_t *                   /* IN output file */
#endif
);


/* Print the info(colnames,types,...) stored in the SQLDA to the given file. */

extern dh_i32_t     EXPORT
tpe_print_header (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
          struct sqlda *,     /* IN contains the header */
          dh_file_t *         /* IN output file */
#endif
      );

/* Print the info(#rows affected,...) stored in the SQLDA to the given file. */

extern dh_i32_t     EXPORT
tpe_print_footer (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
          const dh_char_t *,  /* IN command_type */
          struct sqlca *,     /* IN */
          dh_file_t *         /* IN output file */
#endif
      );

/* Print the content of the SQLCA to the given file. */

extern dh_i32_t   EXPORT
tpe_print_sqlca (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
          const dh_char_t *,  /* IN the SQL statement */
          struct sqlca *,     /* IN contains # of tuples */
          dh_file_t *         /* IN output file */
#endif
      );


/* Prdh_i32_t the parameters stored in the SQLDA to the given file. */

extern dh_i32_t	 EXPORT
tpe_print_input_sqlda(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	struct sqlda *,		/* IN contains the tuples */
	struct sqlca *,		/* IN contains # of tuples */
	dh_file_t *			/* IN output file */
#endif
);


/* Prdh_i32_t the sqlda_var from an sqlda structure dh_i32_to a file. */

extern void  EXPORT
tpe_print_sqlda_var(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	struct sqlda *,		/* IN contains the tuples */
	dh_file_t *,			/* IN output file */
        dh_i32_t  var_idx,           /* var_index      */
	dh_i32_t  array_idx          /* array_index     */
#endif
);

/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlfetchrid (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_sqlenv_hdl_t ,                      /* IN Dharma SQL environment handle */
tpe_tm_hdl_t  ,                               /* IN - transaction handle */
tpe_db_hdl_t  ,                               /* IN - db handle */
tpe_cursor_t  ,                               /* IN - cursor pointer */
struct sqlda  *,                              /* IN - input parameters */
struct sqlda  *,                              /* IN - input parameters */
struct sqlca  *                               /* OUT - sqlca pointer */
#endif
);
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sqlfetchrid (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
tpe_tm_hdl_t 	,				/* IN - transaction handle */
tpe_db_hdl_t	,			        /* IN - db handle */	
tpe_cursor_t	,				/* IN - cursor pointer */
struct sqlda	*,				/* IN - input parameters */
struct sqlda	*,			        /* IN - input parameters */
struct sqlca	*				/* OUT - sqlca pointer */
#endif
);

/*
 * Get the current db handle.
 */

/* BEGIN DC569 DC_20020723_3127 */
extern tpe_db_hdl_t EXPORT
dh_get_curdbhdl (dh_sqlenv_hdl_t  /* IN Dharma SQL environment handle */) ;
/* END DC569 DC_20020723_3127 */

extern tpe_db_hdl_t EXPORT
tpe_get_curdbhdl () ;


/* 
 * set up cursor structure.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_set_cursor (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t      ,                       /* IN  transaction handle   */
    tpe_db_hdl_t      ,                       /* IN  db handle            */
    tpe_cursor_t      *,                      /* IN  cursor pointer       */
    tpe_uuid__t               *,              /* IN  sql stmt uid */
    dh_i32_t                  ,               /* IN  1-dynamic , 0-static */
    dh_char_t         *,                      /* IN  sql stmt             */
    struct sqlca      *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void EXPORT
tpe_set_cursor (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle	    */
    tpe_cursor_t	*,			/* IN  cursor pointer       */
    tpe_uuid__t		*,			/* IN  sql stmt uid         */
    dh_i32_t			,			/* IN  1-dynamic , 0-static */
    dh_char_t		*,			/* IN  sql stmt             */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;
/* BEGIN DC569 DC_20020723_3127 */
extern void   EXPORT
dh_set_cursorname (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_cursor_t ,                    /* IN  cursor pointer   */
    dh_char_t  *,                     /* IN  cursor name      */
    struct sqlca *                    /* OUT sqlca pointer    */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void   EXPORT
tpe_set_cursorname (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_cursor_t ,			/* IN  cursor pointer   */
    dh_char_t	 *,			/* IN  cursor name	*/
    struct sqlca *			/* OUT sqlca pointer    */
#endif
) ;


/*BEGIN DC_20000905_1737*/
/*
 *Free cursor space (client-side)
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_release_cursor(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,       /* IN Dharma SQL environment handle */
    tpe_cursor_t *        /*IN cursor pointer */
#endif
);
/* END DC569 DC_20020723_3127 */

/* DC738 - BEGIN */
                                                                              
extern void EXPORT
dh_set_login_timeout(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,       /* IN Dharma SQL environment handle */
    unsigned int            /* IN Log time out */
#endif
);

extern void EXPORT
dh_set_query_timeout(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_db_hdl_t ,          		
    tpe_cursor_t ,          
    dh_u16_t            
#endif
);
                                                                              
/* DC738 - END */

extern void EXPORT
tpe_release_cursor(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_cursor_t *			/*IN cursor pointer */
#endif
);

/*END DC_20000905_1737*/

/* dc598 BEGIN : Dharma/SQL 10.0 Release Stabilization. */

/* Method tpe_set_fetchflag is added to set the fetch_flag of */
/* all the cursor to STATUS_OK at the end of the transition. */


extern void EXPORT
tpe_set_fetchflag(
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_cursor_t                      /*IN cursor pointer */
#endif
);

/* dc598 END : Dharma/SQL 10.0 Release Stabilization. */


/*
 * execute a non-select sql statement.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlexecute (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t      ,                       /* IN  transaction handle   */
    tpe_db_hdl_t      ,                       /* IN  db handle            */
    tpe_cursor_t      ,                       /* IN  cursor               */
    struct sqlda      *,                      /* IN  input params         */
    struct sqlca      *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

#ifdef FAIRCOM_MOD
extern void  EXPORT
dh_sqlexecutebatch (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t      ,                       /* IN  transaction handle   */
    tpe_db_hdl_t      ,                       /* IN  db handle            */
    tpe_cursor_t      ,                       /* IN  cursor               */
    struct sqlda      *,                      /* IN  input params         */
    struct sqlca      *                       /* OUT sqlca pointer        */
#endif
) ;
#endif
extern void  EXPORT
tpe_sqlexecute (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    struct sqlda	*,			/* IN  input params         */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_sqlexecdirect (
#if           defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t      ,                       /* IN transaction handle */
    tpe_db_hdl_t      ,                       /* IN db handle          */
    tpe_cursor_t      ,                       /* IN cursor             */
    struct sqlda      *,                      /* IN input params       */
    struct sqlca      *                       /* OUT sqlca pointer     */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void EXPORT
tpe_sqlexecdirect (
#if   	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN transaction handle */
    tpe_db_hdl_t	,			/* IN db handle		 */
    tpe_cursor_t	,			/* IN cursor 		 */
    struct sqlda	*,			/* IN input params	 */
    struct sqlca	*			/* OUT sqlca pointer	 */
#endif
) ;

/*
 * declare a cursor
 */

/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_sqldeclare (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t      ,                       /* IN  transaction handle   */
    tpe_db_hdl_t      ,                       /* IN  db handle            */
    tpe_cursor_t      ,                       /* IN  cursor               */
    struct sqlda      *,                      /* IN  input params         */
    struct sqlca      *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void EXPORT
tpe_sqldeclare (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    struct sqlda	*,			/* IN  input params         */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/*
 * single tuple select
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlselect (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t      ,                       /* IN  transaction handle   */
    tpe_db_hdl_t      ,                       /* IN  db handle            */
    tpe_cursor_t      ,                       /* IN  cursor               */
    struct sqlda      *,                      /* IN  input params         */
    struct sqlda      *,                      /* OUT output params        */
    struct sqlca      *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sqlselect (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    struct sqlda	*,			/* IN  input params         */
    struct sqlda	*,			/* OUT output params        */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/*
 * open a cursor.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlopen (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t      ,                       /* IN  transaction handle   */
    tpe_db_hdl_t      ,                       /* IN  db handle            */
    tpe_cursor_t      ,                       /* IN  cursor               */
    struct sqlda      *,                      /* IN  input params         */
    struct sqlca      *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sqlopen (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    struct sqlda	*,			/* IN  input params         */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_sqlgetinfo(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
      dh_sqlenv_hdl_t ,                /* IN Dharma SQL environment handle */
      tpe_db_hdl_t    ,                       /* IN  database hdl          */
      dh_infoid_t     ,                       /* IN  infoid                */
      void   *        ,                       /* OUT output buffer ptr     */
      dh_i32_t       ,                        /* IN  bufle                 */
      dh_i32_t *     ,                        /* OUT bytes in buffer       */
      struct sqlca *                          /* IN  sqlca                 */
#endif
) ;
/* END DC569 DC_20020723_3127 */
extern void EXPORT
tpe_sqlgetinfo(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	tpe_db_hdl_t    ,      			/* IN  database hdl          */
	dh_infoid_t     ,       		/* IN  infoid                */
	void   *        ,			/* OUT output buffer ptr     */
	dh_i32_t       ,			/* IN  bufle                 */
	dh_i32_t *     ,         		/* OUT bytes in buffer       */
	struct sqlca *  		        /* IN  sqlca	             */
#endif
) ;           			
 
 
/*
 * Get a piece of data from a field of dh_i32_t type
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlgetdata (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
     dh_sqlenv_hdl_t ,                  /* IN Dharma SQL environment handle */
     tpe_tm_hdl_t     ,                       /* IN  transaction handle   */
     tpe_db_hdl_t     ,                       /* IN  db handle            */
     tpe_cursor_t     ,                       /* IN  cursor               */
     dh_i32_t                 ,                       /* htypeid */
     void  *          ,                       /* hdl to field             */
     dh_i32_t                 ,                       /* bufferlen */
     dh_i32_t                 ,                       /* offset into field */
     void  *          ,                       /* buffer                   */
     dh_i32_t  *      ,                       /* balance data from offset */
     struct sqlca     *                       /* OUT sqlca pointer        */
#endif
 ) ;
/* END DC569 DC_20020723_3127 */
 
extern void  EXPORT
tpe_sqlgetdata (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
     tpe_tm_hdl_t	,			/* IN  transaction handle   */
     tpe_db_hdl_t	,			/* IN  db handle            */
     tpe_cursor_t	,			/* IN  cursor               */
     dh_i32_t  		,      			/* htypeid 		    */
     void  * 		,			/* hdl to field	 	    */
     dh_i32_t  		,			/* bufferlen 	  	    */
     dh_i32_t  		,			/* offset into field        */
     void  *		,			/* buffer  		    */
     dh_i32_t  *	,			/* balance data from offset */
     struct sqlca	*			/* OUT sqlca pointer        */
#endif
 ) ;
 
/*
 * Put a piece of data dh_i32_to a field of dh_i32_t type
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlputdata (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
     dh_sqlenv_hdl_t ,                  /* IN Dharma SQL environment handle */
     tpe_tm_hdl_t     ,                       /* IN  transaction handle   */
     tpe_db_hdl_t     ,                       /* IN  db handle            */
     tpe_cursor_t     ,                       /* IN  cursor               */
     dh_i32_t                 ,                       /* htypeid */
     void  *          ,                       /* hdl to field             */
     dh_i32_t                 ,                       /* bufferlen */
     dh_i32_t                 ,                       /* offset into field */
     void  *          ,                       /* buffer                   */
     struct sqlca     *                       /* OUT sqlca pointer        */
#endif
 ) ;
/* END DC569 DC_20020723_3127 */
 
extern void  EXPORT
tpe_sqlputdata (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
     tpe_tm_hdl_t	,			/* IN  transaction handle   */
     tpe_db_hdl_t	,			/* IN  db handle            */
     tpe_cursor_t	,			/* IN  cursor               */
     dh_i32_t  		,      			/* htypeid 		    */
     void  * 		,			/* hdl to field	 	    */
     dh_i32_t  		,			/* bufferlen 	  	    */
     dh_i32_t  		,			/* offset into field        */
     void  *		,			/* buffer  		    */
     struct sqlca	*			/* OUT sqlca pointer        */
#endif
 ) ;
/* BEGIN DC569 DC_20020723_3127 */
extern void EXPORT
dh_sqlgetfunctions(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
      dh_sqlenv_hdl_t ,           /* IN Dharma SQL environment handle */
      tpe_db_hdl_t    ,                       /* IN  database hdl     */
      dh_fnid_t       ,                     /* IN  funcid           */
      dh_u16_t *    ,                       /* OUT Exists           */
      struct sqlca *                        /* OUT sqlca pointer    */
#endif
);
/* END DC569 DC_20020723_3127 */
 
extern void EXPORT
tpe_sqlgetfunctions(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	tpe_db_hdl_t    ,      			/* IN  database hdl 	*/
        dh_fnid_t       , 	       		/* IN  funcid 		*/
        dh_u16_t *	,  	 	        /* OUT Exists 		*/
        struct sqlca *  		        /* OUT sqlca pointer 	*/
#endif
);           			
 
 /* 
 * fetch one or more tuples using a cursor
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void   EXPORT
dh_sqlfetch (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t      ,                       /* IN  transaction handle   */
    tpe_db_hdl_t      ,                       /* IN  db handle            */
    tpe_cursor_t      ,                       /* IN  cursor               */
    struct sqlda      *,                      /* OUT output params        */
    struct sqlca      *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void   EXPORT
tpe_sqlfetch (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    struct sqlda	*,			/* OUT output params        */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;


/* 
 * Prepare and execute SQLTables procedure.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqltables (
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t      ,                       /* IN  transaction handle   */
    tpe_db_hdl_t      ,                       /* IN  db handle            */
    tpe_cursor_t      ,                       /* IN  cursor               */
    dh_char_t                *,                 /* IN  table owner          */
    dh_char_t                *,                 /* IN  table name           */
    struct sqlca      *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sqltables (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    dh_char_t                *,                      /* IN  table owner          */
    dh_char_t                *,                      /* IN  table name           */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/* 
 * Prepare and execute SQLColumns procedure.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlcolumns (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t        ,                       /* IN  transaction handle   */
    tpe_db_hdl_t        ,                       /* IN  db handle            */
    tpe_cursor_t        ,                       /* IN  cursor               */
    dh_char_t                *,                 /* IN  table owner          */
    dh_char_t                *,                 /* IN  table name           */
    struct sqlca        *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sqlcolumns (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    dh_char_t             *,    /* IN  table owner          */
    dh_char_t             *,    /* IN  table name           */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/* 
 * Prepare and execute SQLStatistics procedure.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlstatistics (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t        ,                       /* IN  transaction handle   */
    tpe_db_hdl_t        ,                       /* IN  db handle            */
    tpe_cursor_t        ,                       /* IN  cursor               */
    dh_char_t                *,                 /* IN  table owner          */
    dh_char_t                *,                 /* IN  table name           */
    struct sqlca        *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sqlstatistics (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    dh_char_t            *,     /* IN  table owner          */
    dh_char_t            *,     /* IN  table name           */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlprimarykeys (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t        ,                       /* IN  transaction handle   */
    tpe_db_hdl_t        ,                       /* IN  db handle            */
    tpe_cursor_t        ,                       /* IN  cursor               */
    dh_char_t                *,                 /* IN  table owner          */
    dh_char_t                *,                 /* IN  table name           */
    struct sqlca        *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

/* 
 * Prepare and execute SQLPrimaryKeys procedure.
 */
extern void  EXPORT
tpe_sqlprimarykeys (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    dh_char_t            *,     /* IN  table owner          */
    dh_char_t            *,     /* IN  table name           */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/* 
 * Prepare and execute SQLForeignKeys procedure.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlforeignkeys (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t        ,                       /* IN  transaction handle   */
    tpe_db_hdl_t        ,                       /* IN  db handle            */
    tpe_cursor_t        ,                       /* IN  cursor               */
    dh_char_t                *,                 /* IN  primary table owner  */
    dh_char_t                *,                 /* IN  primary table name   */
    dh_char_t                *,                 /* IN  foreign table owner  */
    dh_char_t                *,                 /* IN  foreign table name   */
    struct sqlca        *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sqlforeignkeys (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    dh_char_t            *,     /* IN  primary table owner  */
    dh_char_t            *,     /* IN  primary table name   */
    dh_char_t            *,     /* IN  foreign table owner  */
    dh_char_t            *,     /* IN  foreign table name   */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;
/*
 * Check for the validity of the database handle before using it.	
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sql_chk_connection(
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
        dh_sqlenv_hdl_t ,
        struct sqlca    *
#endif
);
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sql_chk_connection(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	struct sqlca	*
#endif
);


/*
 * prepare a dynamic statement.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlprepare (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t        ,                       /* IN  transaction handle   */
    tpe_db_hdl_t        ,                       /* IN  db handle            */
    tpe_cursor_t        ,                       /* IN  cursor               */
    struct sqlca        *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sqlprepare (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ; 

/*
 * get the types and lengths of outputs for a dynamic statement.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void   EXPORT
dh_sqldescribe (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t        ,                       /* IN  transaction handle   */
    tpe_db_hdl_t        ,                       /* IN  db handle            */
    tpe_cursor_t        ,                       /* IN  cursor               */
    struct sqlda        *,                      /* OUT output desc          */
    struct sqlca        *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void   EXPORT
tpe_sqldescribe (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    struct sqlda	*,			/* OUT output desc          */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/*
 * get the types, precision and scale of inputs for a dynamic statement.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void   EXPORT
dh_sqldescribe_param (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
     dh_sqlenv_hdl_t ,                  /* IN Dharma SQL environment handle */
     tpe_tm_hdl_t       ,                       /* IN  transaction handle   */
     tpe_db_hdl_t       ,                       /* IN  db handle            */
     tpe_cursor_t       ,                       /* IN  cursor               */
     struct sqlda       *,                      /* OUT output desc          */
     struct sqlca       *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void   EXPORT
tpe_sqldescribe_param (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
     tpe_tm_hdl_t	,			/* IN  transaction handle   */
     tpe_db_hdl_t	,			/* IN  db handle            */
     tpe_cursor_t	,			/* IN  cursor               */
     struct sqlda	*,			/* OUT output desc          */
     struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqldescribe_input (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t        ,                       /* IN  transaction handle   */
    tpe_db_hdl_t        ,                       /* IN  db handle            */
    tpe_cursor_t        ,                       /* IN  cursor               */
    struct sqlda        *,                      /* OUT output desc          */
    struct sqlca        *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */
 
extern void  EXPORT
tpe_sqldescribe_input (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    struct sqlda	*,			/* OUT output desc          */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/*
 * close a cursor.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_sqlclose (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t ,                   /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t        ,                       /* IN  transaction handle   */
    tpe_db_hdl_t        ,                       /* IN  db handle            */
    tpe_cursor_t        ,                       /* IN  cursor               */
    struct sqlca        *                       /* OUT sqlca pointer        */
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_sqlclose (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t	,			/* IN  transaction handle   */
    tpe_db_hdl_t	,			/* IN  db handle            */
    tpe_cursor_t	,			/* IN  cursor               */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;

/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_set_ptrs (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t       **      ,
dh_i32_t ,
...
#endif
);
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_set_ptrs (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t 	**	, 
dh_i32_t , 
... 
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_set_arraysz (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_i32_t arraysz, dh_i32_t nvars, ...
#endif
) ;
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_set_arraysz (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_i32_t arraysz, dh_i32_t nvars, ...
#endif
) ;

extern  sqlda	EXPORT
*sqld_alloc (
/* This is for tm_dlib.c compiled in rds directory */
#if	defined(__cplusplus)
    dh_i16_t size, 
    dh_i16_t varnmsize = 0
#endif
) ;

extern  tpe_status_t EXPORT
sqld_validate (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    struct sqlda * 
#endif
) ;

extern	void	EXPORT
sqld_free (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    sqlda *sqldaptr
#endif
) ;

extern	dh_i32_t	EXPORT 
sqld_getnbytes (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_i16_t size, 
    dh_i16_t varnmsz
#endif
) ;

extern	void	EXPORT 
sqld_setup (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
sqlda *sqldaptr,
dh_i16_t size, 
dh_i16_t varnmsz
#endif
) ;

/* DC065 .BEGIN. */
/* BEGIN DC569 DC_20020723_3127 */
extern  void    EXPORT
dh_sqlallocdesc(
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_sqlenv_hdl_t ,
dh_char_t *     ,
dh_i32_t ,
struct sqlca *
#endif
);
/* END DC569 DC_20020723_3127 */

extern	void	EXPORT 
tpe_sqlallocdesc( 
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *	,
dh_i32_t ,
struct sqlca *   
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern  void    EXPORT
dh_sqldeallocdesc(
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_sqlenv_hdl_t ,
dh_char_t *,
struct sqlca *
#endif
);
/* END DC569 DC_20020723_3127 */

extern	void	EXPORT 
tpe_sqldeallocdesc(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *,
struct sqlca * 
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern  void    EXPORT
dh_sqlgetdesc (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_sqlenv_hdl_t ,
struct sqlda   *,
dh_i32_t ,
item_lst * ,
dh_i32_t ,
struct sqlca *
#endif
);
/* END DC569 DC_20020723_3127 */

extern	void	EXPORT 
tpe_sqlgetdesc (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
struct sqlda   *,
dh_i32_t , 
item_lst * ,
dh_i32_t ,
struct sqlca * 
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern  void    EXPORT
dh_sqlsetdesc (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_sqlenv_hdl_t ,
struct sqlda   *,
dh_i32_t ,
item_lst * ,
dh_i32_t ,
struct sqlca *
#endif
);
/* END DC569 DC_20020723_3127 */

extern	void	EXPORT 
tpe_sqlsetdesc (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
struct sqlda   *,
dh_i32_t , 
item_lst * ,
dh_i32_t ,
struct sqlca * 
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern  struct sqlda * EXPORT
dh_sqlgetsqldaptr(
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_sqlenv_hdl_t ,
dh_char_t *,
/* struct sqlda *,*/
struct sqlca *
#endif
);
/* END DC569 DC_20020723_3127 */

extern	struct sqlda * EXPORT 
tpe_sqlgetsqldaptr(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *, 
/* struct sqlda *,*/ 
struct sqlca * 
#endif
);


/* DC065 .END. */

/* 
 * Check_esqlc is used by the ODBC driver to check for the no. of connections.
 */
extern dh_i32_t EXPORT 
check_esqlc();


/* Maximum # of participants in a distributed transaction */
#define	TPE_MAX_PARTICIPANTS	10

/* Transaction flags */
#define TPE_TRANS_ABORTED	0x1

/* Maximum id for a REAL table. The values above this are assigned for
 virtual tables. */
#if !(defined FAIRCOM_MOD && defined ctSQL_NEG_VIEW_ID)
#define         TPE_MAX_TBLID           32767
#endif

/* DC188 BEGIN */

/* BEGIN DC355 */
/* DS_19981123_926 - Isolation READ UNCOMMITTED failure */
typedef enum { 
    READ_UNCOMMITTED = 0, READ_COMMITTED = 1,
    REPEATABLE_READ = 2, SERIALIZABLE = 3, INVALID_ISOLATION_LEVEL = 4
} tpe_tm_isolation_lvl_t ; 
/* END DC355 */
/* DC188 END */

/*
 * Transaction manager library
 */



/*
 * Allocate a transaction handle.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern tpe_tm_hdl_t  EXPORT
dh_tm_alloc_handle (
) ;
/* END DC569 DC_20020723_3127 */
extern tpe_tm_hdl_t  EXPORT
tpe_tm_alloc_handle (
) ;
/*
 * Get the current user 
 */
extern tpe_status_t EXPORT
tpe_get_cur_user( 
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
       const dh_char_t *dbname,
       dh_char_t *user
#endif
);

/*
 * Get the current user's passwd 
 */
extern tpe_status_t EXPORT
tpe_get_cur_userpw( 
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	const dh_char_t *dbname,
	const dh_char_t *username,
        dh_char_t *passwd
#endif
);

/* 
 * Validate the input username and password
 * Called only from sample rss_init.  Use is at discretion of implementor
 */
extern tpe_status_t EXPORT
tpe_validate(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	const dh_char_t *userid,
	const dh_char_t *passwd,
        const dh_char_t *super_user
#endif
);

/*
 * THIS FUNCTION IS NOW OBSOLETE
 * Get the user from tpe_tm_hdl_t
 *
 */
extern 
dh_char_t *tpe_tm_get_user ( 
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
      tpe_tm_hdl_t tpetmhdl 
#endif
);

/*
 * Set a tm handle  as the current tm handle.
 */

extern void  EXPORT
tpe_set_curtmhdl (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t,				/* IN tm handle */
    struct sqlca	*			/* OUT sqlca pointer        */
#endif
) ;
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_tm_set_level(
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t,            /* IN Dharma SQL environment handle */
    tpe_tm_isolation_lvl_t,     /* IN - the isolation level to be set */
    struct      sqlca   *                       /* OUT sqlca pointer */
#endif
);
/* END DC569 DC_20020723_3127 */
extern void  EXPORT
tpe_tm_set_level(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_isolation_lvl_t,       /* IN - the isolation level to be set */
    struct	sqlca	*			/* OUT sqlca pointer */
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern tpe_tm_isolation_lvl_t   EXPORT
dh_tm_get_level(dh_sqlenv_hdl_t);
/* END DC569 DC_20020723_3127 */

extern tpe_tm_isolation_lvl_t   EXPORT
tpe_tm_get_level();



/*
 * Get the current tm handle.
 */
/* BEGIN DC569 DC_20020723_3127 */
extern tpe_tm_hdl_t EXPORT
dh_get_curtmhdl (dh_sqlenv_hdl_t) ;
/* END DC569 DC_20020723_3127 */
extern tpe_tm_hdl_t EXPORT
tpe_get_curtmhdl () ;

/*
 * start a new or sub transaction
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_tm_begin_trans (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t,            /* IN Dharma SQL environment handle */
    tpe_tm_isolation_lvl_t,             /* IN    consistency level */
    tpe_tm_hdl_t,                               /* INOUT transaction info  */
    struct      sqlca   *                       /* OUT sqlca pointer       */
#endif
);
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_tm_begin_trans (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_isolation_lvl_t,			/* IN    consistency level */
    tpe_tm_hdl_t, 				/* INOUT transaction info  */
    struct	sqlca	*			/* OUT sqlca pointer       */
#endif
);


/*
 * mark transaction as aborted
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_tm_mark_abort (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t,                  /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t,                               /* INOUT transaction info */
    struct      sqlca   *                       /* OUT sqlca pointer */
#endif
);
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_tm_mark_abort (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t,  				/* INOUT transaction info */
    struct	sqlca	*			/* OUT sqlca pointer */
#endif
);


/*
 * Complete a transaction:
 */
/* BEGIN DC569 DC_20020723_3127 */
extern void  EXPORT
dh_tm_end_trans (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t,                  /* IN Dharma SQL environment handle */
    tpe_tm_hdl_t,                               /* INOUT transaction info */
    struct      sqlca   *                       /* OUT sqlca pointer */
#endif
);
/* END DC569 DC_20020723_3127 */

extern void  EXPORT
tpe_tm_end_trans (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_tm_hdl_t, 				/* INOUT transaction info */
    struct	sqlca	*			/* OUT sqlca pointer */
#endif
);

extern void	EXPORT
tpe_print_banner(
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
				 const dh_char_t *	/* banner */
#endif
);

extern void	EXPORT
tpe_sqlc_clear (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	struct sqlca *		/* IN  SQLCA pointer */
#endif
);

#ifndef	TRUE
#define		TRUE	 	1	
#define		FALSE		0
#endif

/* DC777 Begin */
/* Commented the below code during vc10 to vc11 port.*/

/*
#ifndef true
#define true  ((dh_u8_t) 0xff)
#define false ((dh_u8_t) 0x00)
#endif
*/

/* DC777 End */

#ifndef	NULL
#define		NULL		((dh_char_t *)0)
#endif

#ifndef	STATUS_OK
#define	  STATUS_OK	0
#endif

/* DC555 */
/* DC_20010123_2156 */
#ifndef SQL_SUCCESS_WITH_INFO
#define SQL_SUCCESS_WITH_INFO      1
#endif
/* DC_20010123_2156 */ 

#define		DH_MAX(x,y)	((y)>(x)?(y):(x)) /* DC737 */

#define		DH_MIN(x,y)	((y)<(x)?(y):(x)) /* DC737 */



/* Default directory where we should look for tpe specific files */

#ifdef FAIRCOM_MOD
#define DEF_TPEDIR      DH_STRING_LITERAL(".")
#else
#if	defined(DH_OS_MSDOS) || defined(DH_OS_WIN32S) || defined (DH_OS_WINNT)
#if defined(DH_ODBC_INT)
#define	DEF_TPEDIR	DH_STRING_LITERAL("C:\\ODBCI")
#else
#define DEF_TPEDIR      DH_STRING_LITERAL("\\SQL")
#endif
#else
#define	DEF_TPEDIR	DH_STRING_LITERAL("/usr/tpe")
#endif
#endif /* FAIRCOM_MOD */

/* Environment string which determines the directory for tpe specific files */
#define	ENV_TPEROOT	DH_STRING_LITERAL("TPEROOT")

dh_char_t * tpe_itoa (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_i32_t 
#endif
) ;

void tpe_fatal (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
const dh_char_t *, dh_i32_t, const dh_char_t * 
#endif
);

#ifndef	STATIC
#ifdef	DEBUG
#define		STATIC	
#else
#define		STATIC		static
#endif
#endif

#ifdef DH_ODBC_SDK
#if !defined(SQL_ROWID_SIZE)  /* DC737 */
#define         SQL_ROWID_SIZE  255
#endif  /* DC737 */
#else
#if !defined(SQL_ROWID_SIZE)  /* DC737 */
#ifdef FAIRCOM_MOD
#define         SQL_ROWID_SIZE  20 /*we allow 2^64 different rowid  Log10(2^64)=19.26 so 20 digits.*/
#else
#define         SQL_ROWID_SIZE  18
#endif /*FAIRCOM_MOD*/
#endif   /* DC737 */
#endif  

#ifndef		TPE_MAX_PROC_ARGS   /* FAIRCOM_MOD */
#define		TPE_MAX_PROC_ARGS	100
#endif
#ifndef		TPE_MAX_RESULTSET_COLS  /* FAIRCOM_MOD */
#define         TPE_MAX_RESULTSET_COLS  50   /* DC_20060927_3699 */
#endif
/* BEGIN DC569 DC_20020801_3147 */
/* The default value for the attribute SQL_ATTR_LOGIN_TIMEOUTof ODBC API
   SQLSetConnectAttr()*/

#define		DH_DFLT_LOGIN_TIMEOUT	15
/* END DC569 DC_20020801_3147 */


/* DC215 (DS_19971118_783) BEGIN 
The statement size is increased so as to accomodate for large procedures */

/* DC317 BEGIN
 * The statement size is increased to insert extended field data. The
 * statement size has been increased to FAIRCOM_MOD_35000 to take atleast one
 * extended field value of TPE_EXT_MAX_FLDLEN (32K) in the INSERT statement
 * through ISQL and the rest can be used for inserting other fields in 
 * that table. */  
#ifndef 	FAIRCOM_MOD_35000
#define		FAIRCOM_MOD_35000	35000			/* Dharma's original value was 35000 */
#endif

#if !defined(TPE_MAX_SQLSTMTLEN) /* DC737  */
#define		TPE_MAX_SQLSTMTLEN      FAIRCOM_MOD_35000	/* Use Dharma's default if not overridden */
#endif /* DC737 */
/* DC317 END */

/* DC215 (DS_19971118_783) END   */
#define		TPE_MAX_SQLSTMTLEN_P1	(TPE_MAX_SQLSTMTLEN + 1)
#if defined FAIRCOM_CODE && defined ctSQL_DYN_STMT
#define		TPE_MAX_SRV_STMTLEN  (33554432) /* 32 MB */
#endif
/* TPE_MAX_FLDLEN can be increased further if the storage system allows */

/* BEGIN DC555
 * Defines the maximum field width that can be specified
 * during the creation of tables.
 * For n(var)char columns (Unicode, without Character Set), this represents
 * the maximum number  of Unicode characters that the field can hold.
 * For (var)char, (var)char with Character Set and n(var)char with Character
 * Set columns this represents the maximum number of bytes that the field 
 * can hold.
 */
#if !defined(TPE_MAX_FLDLEN) /* DC737 */
#if defined FAIRCOM_MOD && defined ctSQL_MAX_FLDLEN
#define		TPE_MAX_FLDLEN		ctSQL_MAX_FLDLEN
#else 
#define		TPE_MAX_FLDLEN		2000
#endif /* FAIRCOM_MOD*/
#endif /* DC737 */
#define		TPE_MAX_FLDLEN_P1	(TPE_MAX_FLDLEN + 1)

#if defined FAIRCOM_MOD && defined ctSQL_LARGE_FLDLEN && (!defined RDS_LMAX || RDS_LMAX==32762)
#undef RDS_LMAX
#undef ISQL_LMAX
#undef FGL_LMAX
#define RDS_LMAX TPE_MAX_FLDLEN_P1 + 2
#define ISQL_LMAX TPE_MAX_FLDLEN_P1 + 2
#define FGL_LMAX TPE_MAX_FLDLEN_P1 + 2
#endif

/* Maximum size of a character (in bytes) in any supported character set.*/ 
#define         TPE_MAX_CHAR_SZ         4 
/* DC555 END */

/* DC587: DC_20021007_3167  BEGIN */
/* Maximum size of a NULL character (in bytes) in any supported character set*/ 
#define			TPE_MAX_NULL_CHAR_SZ	2
/* DC587: DC_20021007_3167  END */
#ifdef FAIRCOM_MOD
#define		TPE_MAX_DFLT_LEN        ctSQL_MAX_DEFLEN /* Maximum length of default value*/
#define		TPE_MAX_DFLT_LEN_P1     TPE_MAX_DFLT_LEN + 1 /* Maximum length of default value*/
#else
#define		TPE_MAX_DFLT_LEN        250 /* Maximum length of default value*/
#define		TPE_MAX_DFLT_LEN_P1     251 /* Maximum length of default value*/
#endif

/* BEGIN DC384 (DC_19990601_784) */
/* DC514 DC_20011220_2874 BEGIN*/  
/* This is the STORAGE_ATTRIBUTE data limit */   
#if !defined(TPE_MAX_STOR_DFLT_LEN) /* DC737 */
#define               TPE_MAX_STOR_DFLT_LEN    2000
#endif /* DC737 */
/* DC514 DC_20011220_2874 END*/ 
/* END   DC384 (DC_19990601_784) */

/* dc625 BEGIN */
#define		TPE_UUID_LEN		64
/* dc625 END */
#define		TPE_UUID_LEN_P1		(TPE_UUID_LEN + 1)

#define		TPE_MAX_CONNLEN		100
#define		TPE_MAX_CONNLEN_P1	(TPE_MAX_CONNLEN + 1)

/* Maximum length of an identifier in characters. 
 * All identifiers have Unicode characters. 
 */
/* dc625 BEGIN */
#if !defined(TPE_MAX_IDLEN) /* DC737 */
#define		TPE_MAX_IDLEN		64
#endif  /* DC737 */
/* dc625 END */

#if !defined(TPE_MAX_IDLEN_P1) /* DC737 */
#define		TPE_MAX_IDLEN_P1	(TPE_MAX_IDLEN + 1)
#endif /* DC737 */

/* DC737 BEGIN */
/* Maximum length of a database identifier */

#if !defined(TPE_MAX_DBIDLEN)
#define TPE_MAX_DBIDLEN               TPE_MAX_IDLEN
#endif

#define TPE_MAX_DBIDLEN_P1            (TPE_MAX_DBIDLEN + 1)

#if !defined(DH_MAXVIEW_TEXT_LEN)
#define	DH_MAXVIEW_TEXT_LEN	TPE_MAX_FLDLEN
#endif

/* DC737 END */

/* Used to define the maximum amount of storage that needs to be
 * done for dboptions. 
 */

#define         TPE_MAX_DBOPT_STR_SZ   1000  
#define         TPE_MAX_DBOPT_STR_SZ_P1 (TPE_MAX_DBOPT_STR_SZ + 1) /* DC463 */

#ifdef ctSQL_MAX_PATHLEN
#define		TPE_MAX_PATHLEN		ctSQL_MAX_PATHLEN
#else
#error UNEXPECTED
#define		TPE_MAX_PATHLEN		200
#endif
#define		TPE_MAX_PATHLEN_P1	(TPE_MAX_PATHLEN + 1)

#define		TPE_UNAME_LEN		TPE_MAX_IDLEN
/* dc625 BEGIN */
#define		TPE_UNAME_LEN_P1        (TPE_UNAME_LEN + 1)	
/* dc625 END */

/* DC569 DC_20020914_3158 Begin */
/* DC698 BEGIN */
#define         DH_DBOPTIONS_LEN        512
/* DC698 END */
/* DC569 DC_20020914_3158 End */

/*
 * DC317 BEGIN
 */

/* DC590 Begin */
/* Changes for introduction of a new constant to define the maximum size of the
 * error message field in the error log
 */
#define MAX_ERRLOG_MSGLEN 1024
/* DC590 End */    

/*
 * Note : DH_EXTTBL_FLDLEN and DH_EXTDATA_MIN_BYTELEN macros are not
 *        recommended to change across the same DataBase for a RSS which uses 
 *        these macros.
 *
 *        In case of Flat File this macros are used and it should not be
 *        changed across the same DataBase. If it is needed to change these
 *        macros, the tables which have extended type columns should be dropped
 *        before changes and recreate the same tables after the changes.
 *
 *        While assigning the value for DH_EXTDATA_MIN_BYTELEN, 
 *        TPE_NCHAR_HDR_SZ and TPE_BINARY_HDR_SZ should be kept in mind.
 *        MMSM cannot handle column sizes greater than 2k. If a NVARCHAR
 *        or VARBINARY field of 2k is created, an additional header size
 *        is added on due to which the field size in MMSM goes beyond 2k
 *        and MMSM returns an error. So ideally,
 *
 *        DH_EXTDATA_MIN_BYTELEN < TPE_MAX_FLDLEN - MAX(TPE_NCHAR_HDR_SZ, 
 *        				    	        TPE_BINARY_HDR_SZ)
 *
 *	  Also, DH_EXTTBL_FLDLEN < DH_EXTDATA_MIN_BYTELEN
 *
 */ 

/* DC449 BEGIN */
#define		DH_EXTTBL_FLDLEN	1924
#ifdef FAIRCOM_MOD
#ifdef ctSQL_MAX_FLDLEN
#define 	DH_EXTDATA_MIN_BYTELEN	ctSQL_MAX_FLDLEN
#else /*ctSQL_MAX_FLDLEN*/
#define 	DH_EXTDATA_MIN_BYTELEN	1925
#endif /*ctSQL_MAX_FLDLEN*/
#else /*FAIRCOM_MOD*/
#define 	DH_EXTDATA_MIN_BYTELEN	1925
#endif /*FAIRCOM_MOD*/
/* DC449 END */

/*
 * DC317 END
 */

/* DC113 BEGIN */
#define    TPE_MAX_RECS_LEVEL  10  /* DC_20070827_3848: Increased from 2 to 10  */
/* DC113 END */

#if defined FAIRCOM_MOD 
#define		TPE_MAX_FIELDS		2500
#else
/* DC777 BEGIN */
/* Porting Customer changes to Dharma/SQL 14.0 */
/* #define	TPE_MAX_FIELDS		500 */
#define		TPE_MAX_FIELDS		2000  
/* DC777 END */
#endif

#define		TPE_MAX_NO_CONN		10

#define		TPE_CONSTR_LEN		100


/* The scale and the length share a intword with the scale in the low order
   byte;
*/
#define         TPE_FLDLEN_MASK         0xffffff
#define         TPE_FLDLEN_SHIFT        8
#define         TPE_SCALE_MASK          0xff
#ifdef FAIRCOM_MOD
#define        TPE_CEIL_CAST_i16_t(x) ((dh_i16_t)((x>32767)?32767:x))
#endif
/* BEGIN DC569 - DC_20020603_3068
 *  This variable specifies the Default thread stack size for server thread
 *  and misql main. The minimum value must be 1024 KB.
 */
#ifdef FAIRCOM_MOD
#ifdef UNICODE
#define         DH_THREAD_STACK_SZ_KB   (1024 * sizeof(dh_char_t) - 512)
#else
#ifdef ctPortWIN32
#define         DH_THREAD_STACK_SZ_KB   1024
#else
#define         DH_THREAD_STACK_SZ_KB   1536
#endif
#endif /*UNICODE*/
#else /* FAIRCOM_MOD */
#define         DH_THREAD_STACK_SZ_KB   1024
#endif

/* END DC569 - DC_20020603_3068 */

/*dc598 END : Dharma/SQL 10.0 Release Stabilization.*/

#ifdef __cplusplus
#ifdef DH_TRANSLATE_ONLY
/* 
 * Generating the 'c' files from 'c++' files to be compiled on a different
 * platform where 'c++' is not available ; suppress sizeof computation by
 * 'c++' translator 
 */
extern dh_i32_t	v_sizeof ; 
#define	DH_SIZEOF(x)	(sizeof(x) + v_sizeof)
#else
#define	DH_SIZEOF(x)	(sizeof(x))
#endif /* DH_TRANSLATE_ONLY */
#endif /* __cplusplus */

/* TPE field types.	*/

#define 	TPE_DT_ERR	       -1
/* BEGIN DC555
 * TPE type for (var)char columns,
 * the Locale(MBCS) storage representation
 * END DC555
 */
#define         TPE_DT_CHAR             1
#define         TPE_DT_NUMERIC          2
#define         TPE_DT_SMALLINT         3
#define         TPE_DT_INTEGER          4
#define         TPE_DT_SMALLFLOAT       5
#define         TPE_DT_REAL             5
#define         TPE_DT_FLOAT            6
#define         TPE_DT_DATE             7
#define         TPE_DT_MONEY            8
#define         TPE_DT_TIME             9
#define         TPE_DT_TIMESTAMP       10
#define         TPE_DT_TINYINT         11
#define         TPE_DT_BINARY          12
#define         TPE_DT_BIT             13
#define         TPE_DT_LVC             14
#define         TPE_DT_LVB             15
#define         TPE_DT_BIGINT          16
/* BEGIN DC555
 * TPE type for n(char) columns, the Unicode storage representation
 */
#define         TPE_DT_NCHAR           17
#define         TPE_DT_NVARCHAR        18
/* 
 * TPE type for n(char) with character set name specified  columns,
 * the Locale(MBCS) storage representation
 */ 
#define         TPE_DT_NCHAR_CS        19
#define         TPE_DT_NVARCHAR_CS     20
#define         TPE_DT_VARCHAR         21  /* DC587 */
/* END DC555 */
/* END DC091 */

/* DC608 BEGIN : LOB data type implementation.
 * TPE types for character large object type columns and binary large
 * object type columns. Maxtypes changed to 23. 
 */

#define         TPE_DT_BLOB            22
#define         TPE_DT_CLOB            23
/* DC698 Begin */
#define         TPE_DT_NLVC            24
#define         TPE_DT_NCLOB           25
/* DC753 / DC_20090608_3997 : Begin */
#define         TPE_DT_VARBINARY       26
#define         TPE_DT_MAXTYPES        26
/* DC753 / DC_20090608_3997 : End */
/* DC698  End */

/* DC608 END : LOB data type implementation. */
#define         TPE_DT_NTYPEIDS        27 /* DS_20151102_0009 */


/* DC587 Begin */
#ifdef _UNICODE
#define CSM_TPE_CHAR     TPE_DT_CHAR
#define CSM_TPE_VARCHAR  TPE_DT_VARCHAR
#define DFLT_TPE_CHAR    TPE_DT_NCHAR
#define DFLT_TPE_VARCHAR TPE_DT_NVARCHAR
#else
#define CSM_TPE_CHAR     TPE_DT_NCHAR
#define CSM_TPE_VARCHAR  TPE_DT_NVARCHAR
#define DFLT_TPE_CHAR    TPE_DT_CHAR
#define DFLT_TPE_VARCHAR TPE_DT_VARCHAR
#endif

/* BEGIN DC587 */
#define IS_TPE_CHAR_TYPE(type) (type == CSM_TPE_CHAR || type == CSM_TPE_VARCHAR	|| type == DFLT_TPE_CHAR || type == DFLT_TPE_VARCHAR || type == TPE_DT_NCHAR_CS	|| type == TPE_DT_NVARCHAR_CS)
#ifdef FAIRCOM_MOD
#define IS_TPE_CSMCHAR_TYPE(type) (type == CSM_TPE_CHAR || type == CSM_TPE_VARCHAR || type == TPE_DT_NCHAR_CS || type == TPE_DT_NVARCHAR_CS)
#define IS_TPE_LCHAR_TYPE(type) (type == TPE_DT_LVC || type == TPE_DT_CLOB)
#define IS_TPE_NLCHAR_TYPE(type) (type == TPE_DT_NLVC || type == TPE_DT_NCLOB)
#define IS_TPE_LBIN_TYPE(type) (type == TPE_DT_LVB || type == TPE_DT_BLOB)
#define IS_TPE_LONG_TYPE(type)  (type == TPE_DT_LVC || type == TPE_DT_CLOB || type == TPE_DT_NLVC || type == TPE_DT_NCLOB || type == TPE_DT_LVB || type == TPE_DT_BLOB)
#endif
/* END DC587 */

#ifdef _UNICODE
#define CSM_SQL_CHAR     SQL_CHAR
#define CSM_SQL_VARCHAR  SQL_VARCHAR
#define DFLT_SQL_CHAR    SQL_WCHAR
#define DFLT_SQL_VARCHAR SQL_WVARCHAR
#define CSM_SQL_C_CHAR   SQL_C_CHAR
#define DFLT_SQL_C_CHAR  SQL_C_WCHAR
#else
#define CSM_SQL_CHAR     SQL_WCHAR 
#define CSM_SQL_VARCHAR  SQL_WVARCHAR
#define DFLT_SQL_CHAR    SQL_CHAR
#define DFLT_SQL_VARCHAR SQL_VARCHAR
#define CSM_SQL_C_CHAR   SQL_C_WCHAR
#define DFLT_SQL_C_CHAR  SQL_C_CHAR
#endif
/* DC587 End */

/* Precision and scale for numeric data_t. */

#define		TPE_MIN_PRECISION	1
#define		TPE_MAX_PRECISION	32
#define		TPE_MIN_SCALE      	-84
#define		TPE_MAX_SCALE		127

/*
 * Internal representation of some of the 4GL/SQL data types
 */

/* Representation for NUMERIC types.  */
#define TPE_NUMERIC_SIZE 16

typedef struct {
	dh_i16_t	dec_num;
	dh_i8_t		dec_digits[TPE_NUMERIC_SIZE + 1];
} tpe_num_t;

/* Representation for DATE type */
typedef struct {
	dh_i16_t 	year ;
	dh_u8_t 	month;
	dh_u8_t 	day ;
} tpe_date_t ;

/* Internal representation for DATE type */
typedef dh_i32_t	tpe_idate_t;

/* Representation for TIME type */
typedef struct {
	dh_u8_t	hours;
	dh_u8_t	mins;
	dh_u8_t	secs;
	dh_u16_t	msecs;
} tpe_time_t;

/* Representation for TIMESTAMP type */
typedef struct {
	tpe_date_t   	ts_date ;
        tpe_time_t      ts_time ;
}  tpe_timestamp_t ;    

/* Host Representation for BINARY type */
/* DC317 BEGIN		
 *
 * NOTE : NEVER use DH_SIZEOF(tpe_binary_t) in the code. This
 * will result in allocation of large memory on stack. Therefore
 * either use data_max_hostsize () which is a member function of
 * data_t or use tpe_data_gethostlen () for calculating the
 * hostsize.
 *
 * DC317 END
 */
typedef struct {
	dh_i32_t		tb_len ;

	/* BEGIN DC555
	 * The i18n version doesn't support extended data type
	dh_u8_t  		tb_data [TPE_EXT_MAX_FLDLEN] ;
	 */
	
	dh_u8_t  		tb_data [TPE_MAX_FLDLEN] ;
	/* END DC555 */
} tpe_binary_t ;

/* Host Representation for BIGINT type */
typedef struct {
	dh_u32_t		ll ;
	dh_i32_t		hl ;
} tpe_bigint_t ;


/* DC424 BEGIN  */
/* Enumeration for the character sets supported.  */
/* First character set id should not be changed.  */
typedef enum 
{
    INVALID_CHARSET,
    DHARMA_LATIN1_CSID,
    DHARMA_USASCII_CSID,
    DHARMA_UTF8_CSID,
    DHARMA_NOCHARSET_CSID    /* DC555 */
#ifdef FAIRCOM_MOD
	/* when adding to this enum , ensure to update getConverterName in public\os\common\os_clib.cxx */
    , DHARMA_NATIVE_WCHAR
    , DHARMA_SYSTEM_CSID
#endif
} charsetid_t;

/* Enumeration for the collations supported.  */
/* First collation id should not be changed.  */
typedef enum 
{
    INVALID_COLLATE,
    COLLATION_LOGICAL,
    COLLATION_CASEINSENSITIVE
} collateid_t;

/*
According to SQL92 standard,
<character value expression> consisting of a column reference has
the Implicit attribute, with collating sequence as defined when the
column was created. A <character value expression> consisting of a
value other than a column (e.g., a host variable or a literal) has
the Coercible attribute, with the default collation for its char-
acter repertoire. A <character value expression> simply containing
a <collate clause> has the Explicit attribute, with the collating
sequence specified in the <collate clause>.
*/    
typedef enum 
{
    INVALID_COERCION,
    COERCIBLE,
    IMPLICIT,
    NO_COLLATE,
    EXPLICIT
} coercibility_t;

/* The number of character sets and collations supported.  */ 
#ifdef FAIRCOM_MOD
/*this needs cleanup when we add new charsets*/
const dh_i32_t SQL_MAX_CHARSETS_SUPPORTED = 
#ifdef ctSQL_UTF8_SUPPORT
1 +
#endif
#ifdef ctSQL_LATIN1_SUPPORT
1 +
#endif
2;
#else
const dh_i32_t SQL_MAX_CHARSETS_SUPPORTED = 4;    /* DC555 */
#endif
const dh_i32_t SQL_MAX_COLLATIONS_SUPPORTED = 2;

#define SQL_MAX_CHARSET_NAME_LEN_P1    TPE_MAX_IDLEN_P1
#define SQL_MAX_COLLATION_NAME_LEN_P1  TPE_MAX_IDLEN_P1

/* BEGIN DC555
 * Server Character Set Name. 
 * If database character set is not specified while creating the database,
 * this is used as the database character set.
 * Database character set (SQL_TEXT) is the character set for the dictionary 
 * columns and the default character set for user table columns (if the
 * character set name was not specified during creation).
 */
#if (defined FAIRCOM_MOD && defined ctSQL_CS_CLEANUP)
#ifdef DH_SERVER_CHARSET
#undef DH_SERVER_CHARSET
#endif
#else
#define DH_SERVER_CHARSET DH_STRING_LITERAL("UTF8_CS")
#endif

/* END DC555 */

/* BEGIN DC555
 * Structure to hold the details of a Locale(MBCS) character data 
 */
typedef struct nchar_str_atrib_tag
{
     /* Character set id of the literal to be created.  */
     charsetid_t charset;

     /* Collation of the literal to be created.  */
     collateid_t  collate;

     /* Coercibility of the data object to be created.  */
     coercibility_t coerce;
     
}nchar_str_attrib;
/* END DC555 */

/* DC317 BEGIN
 * NOTE : NEVER use DH_SIZEOF(tpe_nchar_t) in the code. This
 * will result in allocation of large memory on stack. Therefore
 * either use data_max_hostsize () which is a member function of
 * data_t or use tpe_data_gethostlen () for calculating the
 * hostsize.
 *
 * DC317 END
 */

/* BEGIN DC555
 * Structure to hold the Locale character Data
 * Use for (var)char columns and n(var)char with character set Columns
 */
typedef struct{
  charsetid_t charsetid;  /* Chracater Set id */

  dh_u32_t    data_size;      /* Length of data buffer in bytes */

  /* The i18n version doesn't support extended data type
   dh_u8_t     nchar_data[TPE_EXT_MAX_FLDLEN];
   */
#ifdef FAIRCOM_MOD   
   dh_u8_t     nchar_data[TPE_MAX_FLDLEN + 4];/*extra 4 bytes to account for string terminator*/
#else
   dh_u8_t     nchar_data[TPE_MAX_FLDLEN];
#endif
			      /* Stores data as array of bytes */
} tpe_nchar_t;
/* END DC555*/

/*
 * TPE_NCHAR_HDR_SZ macro is introduced for calculating the
 * sizeof (charset_name + collation + data_len). These data members
 * are present in tpe_nchar_t structure. This macro can be used
 * in places where hostsize is having the sizeof tpe_nchar_t
 * structure to get the actual data length.
 */

#define TPE_NCHAR_HDR_SZ offsetof(tpe_nchar_t,nchar_data)

/* TPE_BINARY_HDR_SZ macro is introduced for calculating the
 * sizeof (tb_len). This data member
 * is present in tpe_binary_t structure. This macro can be used
 * in places where hostsize is having the sizeof tpe_binary_t
 * structure to get the actual data length.
 */

#define TPE_BINARY_HDR_SZ offsetof(tpe_binary_t,tb_data)

/* DC317 END */

/* Internal representation for TIME type (# of millisecs from start of day) */
typedef dh_i32_t	tpe_itime_t;

/* 
 * Internal representation for TIMESTAMP type
 */ 

typedef struct {
	tpe_idate_t	ts_idate ;
        tpe_itime_t     ts_itime ;
}  tpe_itimestamp_t ;
/* BEGIN DC569 DC_20020723_3127 */
extern tpe_status_t dh_conv_data (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_i32_t,           /* IN  input type */
    dh_i32_t,           /* IN  length of input buffer */
    const void *,       /* IN  input buffer */
    const dh_char_t *,  /* IN  conversion format */
    dh_i32_t,           /* IN  output type desired */
    dh_i32_t,           /* IN  length of the output buffer */
    void *              /* OUT output buffer for result */
#endif
);
/* END DC569 DC_20020723_3127 */
 
/* Convert from one type to another */
extern tpe_status_t tpe_conv_data (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_i32_t,		/* IN  input type */
    dh_i32_t,		/* IN  length of input buffer */
    const void *,	/* IN  input buffer */
    const dh_char_t *,	/* IN  conversion format */
    dh_i32_t,		/* IN  output type desired */
    dh_i32_t,		/* IN  length of the output buffer */
    void *		/* OUT output buffer for result */
#endif
);


extern tpe_status_t tpe_get_datelen (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
     const dh_char_t *,	/* IN   format string */
    dh_i32_t *		/* OUT  length */
#endif
);

extern tpe_status_t tpe_get_timelen (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    const dh_char_t *,	/* IN   format string */
    dh_i32_t *		/* OUT  length */
#endif
);

extern tpe_status_t tpe_get_timestamplen (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    const dh_char_t *,	/* IN   format string */
    dh_i32_t *		/* OUT  length */
#endif
);

/*
 * dc639 BEGIN : case sensitive and insensitive search in Dharma/SQL
 *
 * enumerated type for dbcase
 */

typedef enum
{
  DB_CASE_SENSITIVE,
  DB_CASE_INSENSITIVE
}sql_dbcase_t;

/* DC738 BEGIN : Added the enum declaration. */
typedef enum
{
        IC_UPPER,
        IC_LOWER,
        IC_SENSITIVE,
        IC_MIXED
}
sql_idcase_t;
/* DC738 END */

/*
 * dc639 END : case sensitive and insensitive search in Dharma/SQL
 */

/* BEGIN DC569 DC_20020723_3127 */
extern tpe_status_t dh_compare_data (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_i32_t,           /* IN  type for data object1 and data object2 */
    dh_i32_t,           /* IN  length of input buffer for data object1 */
    void *,             /* IN  input buffer for data object1 */
    dh_i32_t,           /* IN  length of the input buffer for data object2 */
    void *,             /* IN  input buffer for data object2 */
    dh_i32_t *          /* OUT comparison result */
#endif
);
/* END DC569 DC_20020723_3127 */

/* DC166 begin result changed to dh_i32_t */
/* Compare one data object with another */
extern tpe_status_t tpe_compare_data (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_i32_t,		/* IN  type for data object1 and data object2 */
    dh_i32_t,		/* IN  length of input buffer for data object1 */
    void *,		/* IN  input buffer for data object1 */
    dh_i32_t,		/* IN  length of the input buffer for data object2 */
    void *,		/* IN  input buffer for data object2 */
    dh_i32_t *		/* OUT comparison result */
#endif
);
/* DC166 end result changed to dh_i32_t */
/* BEGIN DC569 DC_20020723_3127 */
extern dh_i32_t         dh_dayofweek (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
        tpe_date_t              /* IN  date */
#endif
);
/* END DC569 DC_20020723_3127 */

/* Return day of the week from date */
extern dh_i32_t		tpe_dayofweek (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	tpe_date_t		/* IN  date */
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern tpe_status_t     dh_num_add (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
        tpe_num_t *,    /* IN  operand 1 */
        tpe_num_t *,    /* IN  operand 2 */
        tpe_num_t *     /* OUT result */
#endif
);
/* END DC569 DC_20020723_3127 */

/* Add two numeric data */
extern tpe_status_t	tpe_num_add (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	tpe_num_t *,	/* IN  operand 1 */
	tpe_num_t *,	/* IN  operand 2 */
	tpe_num_t *	/* OUT result */
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern tpe_status_t     dh_num_sub (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
        tpe_num_t *,    /* IN  operand 1 */
        tpe_num_t *,    /* IN  operand 2 */
        tpe_num_t *     /* OUT result */
#endif
);
/* END DC569 DC_20020723_3127 */

/* Subtract two numeric data */
extern tpe_status_t	tpe_num_sub (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	tpe_num_t *,	/* IN  operand 1 */
	tpe_num_t *,	/* IN  operand 2 */
	tpe_num_t *	/* OUT result */
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern tpe_status_t     dh_num_mul (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
        tpe_num_t *,    /* IN  operand 1 */
        tpe_num_t *,    /* IN  operand 2 */
        tpe_num_t *     /* OUT result */
#endif
);
/* END DC569 DC_20020723_3127 */

/* Multiply */
extern tpe_status_t	tpe_num_mul (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	tpe_num_t *,	/* IN  operand 1 */
	tpe_num_t *,	/* IN  operand 2 */
	tpe_num_t *	/* OUT result */
#endif
);
/* BEGIN DC569 DC_20020723_3127 */
extern tpe_status_t     dh_num_div (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
        tpe_num_t *,    /* IN  operand 1 */
        tpe_num_t *,    /* IN  operand 2 */
        tpe_num_t *     /* OUT result */
#endif
);
/* END DC569 DC_20020723_3127 */

/* Divide */
extern tpe_status_t	tpe_num_div (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	tpe_num_t *,	/* IN  operand 1 */
	tpe_num_t *,	/* IN  operand 2 */
	tpe_num_t *	/* OUT result */
#endif
);

/* Convert to dh_i32_ternal representation of date */
extern tpe_status_t tpe_convdatetoi (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_date_t,		/* IN  date */
    tpe_idate_t *	/* OUT dh_i32_ternal form */
#endif
);

/* Convert from dh_i32_ternal representation of date */
extern tpe_status_t tpe_convitodate (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_idate_t,	/* IN  dh_i32_ternal date */
    tpe_date_t *	/* OUT date */
#endif
);

/* Convert to dh_i32_ternal representation of time */
extern tpe_status_t	tpe_convtimetoi (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	tpe_time_t,	/* IN  time */
	tpe_itime_t *	/* OUT dh_i32_ternal time */
#endif
);

/* DC555 BEGIN */
/* Convert a string to a binary format */
extern tpe_status_t tpe_convstrtobinary (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_i32_t,		  /* IN  input buffer length */
dh_i8_t *,	 	  /* IN  input buffer        */
tpe_binary_t *		  /* OUT output buffer	       */ 
#endif
);
extern tpe_status_t tpe_convunistrtobinary (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_i32_t,		  /* IN  input buffer length */
const dh_char_t *,	  /* IN  input buffer        */
tpe_binary_t *		  /* OUT output buffer	       */ 
#endif
);
/* DC555 END */

/* Convert from dh_i32_ternal representation of time */
extern tpe_status_t	tpe_convitotime (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
	tpe_itime_t,	/* IN  dh_i32_ternal time */
	tpe_time_t *	/* OUT time */
#endif
);

/* Round */
extern tpe_status_t tpe_round ( 
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
tpe_num_t * ,
dh_i32_t	precision,
dh_i32_t	scale
#endif
);

/* DC746 BEGIN */
/* Truncate */
extern tpe_status_t tpe_truncate (
#if     defined(__cplusplus) || !defined(NO_PROTOTYPE)
tpe_num_t * ,
dh_i32_t        precision,
dh_i32_t        scale
#endif
);
/* DC746 END */

/* Numdecimal */
extern tpe_status_t tpe_getnumdecimal (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
tpe_num_t *	,
dh_i16_t * ,
dh_i16_t * 
#endif
);

/* DC_20060824_3679 Begin */
typedef struct  {
dh_i32_t optind;
dh_i32_t opterr;
dh_char_t *optarg;
} get_opt_t;
/* DC_20060824_3679 End */

/* (DC044) .BEGIN */

/* For getting the sql diagnostics information, a new C API is
   defined */
/* BEGIN DC569 DC_20020723_3127 */
extern dh_i32_t EXPORT
            dh_sqlgetdiag (
                                dh_sqlenv_hdl_t,
                                struct sqlca* ,
                                diag_kwd_t  *   ,
                                dh_i16_t ,
                                dh_i32_t ,
                                dh_char_t *   ,
                                struct sqlda    *
                                );
/* END DC569 DC_20020723_3127 */

extern dh_i32_t EXPORT 				
	    tpe_sqlgetdiag (
				struct sqlca* ,
				diag_kwd_t  *   ,
				dh_i16_t ,
				dh_i32_t ,
				dh_char_t *   ,
				struct sqlda  	*   
				);

/* DC676 BEGIN */
extern void EXPORT
            dh_set_sqlda_validation (   
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
                                        /* IN Dharma SQL environment handle */
                                        dh_sqlenv_hdl_t ,
                                        /* IN sqlda validation flag */
                                        dh_boolean 
#endif
                                    );

extern void EXPORT
            tpe_set_sqlda_validation (   
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
                                         /* IN sqlda validation flag */
                                         dh_boolean ,    
                                         /* OUT sqlca pointer */
                                         struct sqlca *  
#endif
                                     );
/* DC738 BEGIN */
extern void
dh_odbcgetinfo(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
void *,
tpe_db_hdl_t,
dh_u16_t,
void *,
dh_i32_t,
dh_i32_t *,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
extern void
dh_formsql_for_tables(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *,
dh_char_t *,
dh_char_t * ,
dh_char_t * ,
dh_i32_t,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
extern void
dh_formsql_for_primarykeys(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *,
dh_char_t *,
dh_char_t * ,
dh_i32_t ,
dh_u32_t ,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
extern void
dh_formsql_for_procedures(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t * ,
dh_char_t * ,
dh_char_t * ,
dh_i32_t ,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
void
dh_formsql_for_columns(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *,
dh_char_t *,
dh_char_t *,
dh_char_t *,
dh_i32_t ,
dh_i32_t ,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
extern void
dh_formsql_for_foreignkeys(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *,
dh_char_t *,
dh_char_t * ,
dh_char_t *,
dh_char_t *,
dh_i32_t,
dh_u32_t ,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
void
dh_formsql_for_columnprivileges(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *,
dh_char_t *,
dh_char_t *,
dh_char_t *,
dh_i32_t ,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
extern void
dh_formsql_for_tableprivileges(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *,
dh_char_t *,
dh_char_t * ,
dh_i32_t ,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
extern void
dh_formsql_for_procedurecolumns(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *,
dh_char_t *,
dh_char_t *,
dh_char_t *,
dh_i32_t,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
extern void
dh_formsql_for_specialcolumns(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_char_t *,
dh_char_t *,
dh_u32_t ,
dh_char_t * ,
dh_i32_t ,
struct sqlca *
#endif
);
/* DC738 END */

/* DC738 BEGIN */
extern void 
dh_formsql_for_statistics(
dh_char_t * ,
dh_char_t* ,
dh_u32_t ,
dh_u32_t ,
dh_char_t * ,
dh_i32_t ,
struct sqlca *
);
/* DC738 END */

/* DC738 BEGIN */
extern void
dh_sqlgettypeinfo(
#if  defined(__cplusplus) || !defined(NO_PROTOTYPE)
dh_i16_t ,
dh_boolean *
#endif
);
/* DC738 END */

/* DC676 END */

/* (DC044) .END */

/* prdh_i32_t the tuples stored in the SQLCA to the given file */
  
/* DC555 - DC_20020828_3155 Begin */
/* Defining this macro ensures that user isolation level
 * is used for dictionary operations
 * By default this is undefined and the isolation level of SERIALIZABLE
 * will be used for dictionary operations
*/  

#ifdef ctSQL_ISOLATION_V8C_DICT /* FAIRCOM_MOD */
#define DH_USR_ISO_FOR_DICT
#else
#undef DH_USR_ISO_FOR_DICT
#endif

/* DC555 - DC_20020828_3155 End */

/* DC587 - DC_20020822_3153 Begin */
/*
 * This defines the default user isolation level
 * For the JDBC driver the default isolation level is defined in
 * src/snw/snj/DharmaIsolationLvl.java file
 */
#ifdef FAIRCOM_MOD
#ifndef DH_DFLT_ISOLATION_LEVEL
#define DH_DFLT_ISOLATION_LEVEL READ_COMMITTED
#endif /*~DH_DFLT_ISOLATION_LEVEL*/
#else /* FAIRCOM_MOD */
#define DH_DFLT_ISOLATION_LEVEL SERIALIZABLE
#endif /* FAIRCOM_MOD */
/* DC587 - DC_20020822_3153 End */



#if defined FAIRCOM_MOD
#ifdef ctSQL_POOL_CLEANUP_RPC
extern void   EXPORT
fc_sqlpoolcleanup (
#if	defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t sqlenv_hdl ,
    tpe_tm_hdl_t tpetmhdl,
    tpe_db_hdl_t tpedbhdl,
    struct sqlca * ca
#endif
);
#endif /* ctSQL_POOL_CLEANUP_RPC */

#if defined FAIRCOM_CODE && defined ctSQL_STP_LANG
typedef enum
{
    SQL_PROC_JVM,
#if defined FAIRCOM_CODE && defined ctSQL_STP_CLIRTM
    SQL_PROC_CLIRT
#endif
} sql_procrt_t;

#define SQL_RUN_MAX_LEN 1024
#endif

#if defined FAIRCOM_CODE && defined ctSQL_STP_CLIRTM
#if !(defined FAIRCOM_CODE && defined ctSQL_STP_LANG)
#error ctSQL_STP_CLIRTM requires ctSQL_STP_LANG
#endif
typedef struct{
	dh_i16_t sqld_type;
	dh_i16_t sqld_ivar;
	dh_i32_t sqld_length;
	dh_u8_t *sqld_varptr;
} fc_resultset_tuple;
#endif

#if defined FAIRCOM_CODE && defined ctSQL_SP_RPC
#if !(defined FAIRCOM_CODE && defined ctSQL_STP_LANG)
#error ctSQL_SP_RPC requires ctSQL_STP_LANG
#endif

typedef enum {
	FC_SQL_STP,
	FC_SQL_UDF,
	FC_SQL_TRG
 } fc_stp_type_t;

#define SQL_PROC_OPT_NONE          0x00000000 /* fcdeploy creates */
#define SQL_PROC_OPT_ALTER_CHECK   0x00000001 /* fcdeploy alter after checking that no prototype change occurred */
#define SQL_PROC_OPT_ALTER_NOCHECK 0x00000002 /* fcdeploy alter, if not there creates it */
/* or'd options*/
#define SQL_PROC_OPT_RAWBUF        0x00010000 /* fcdump in raw buffer, fcdeploy from raw buffer */
/*mask*/
#define SQL_PROC_OPT_MASK          0x0000FFFF

typedef enum
{
    SQL_PROC_ARG_UNKNOWN,
    SQL_PROC_ARG_IN ,
    SQL_PROC_ARG_INOUT ,
    SQL_PROC_RESULT,
    SQL_PROC_ARG_OUT ,
    SQL_PROC_RETURN,
    SQL_UDF_RETURN,
    SQL_PROC_ARG_INVALID = -1   /* Should be the last member */
} sql_proccoltype_t;

typedef struct
{
	dh_u16_t        pci_proccolid;	  /* procedure column id */
	dh_char_t pci_col[TPE_MAX_IDLEN_P1];              /* column name */
	dh_char_t       pci_datatype[TPE_MAX_IDLEN_P1];/* data type*/
	sql_proccoltype_t pci_coltype;	/* indicates IN, OUT, RESULT etc*/
	dh_i32_t        pci_width;		/* width*/
	dh_i16_t        pci_scale;		/* scale*/ /*FAIRCOM_MOD */
	dh_boolean      pci_nonull;		/* the column is null or not null*/
	dh_char_t 	   *pci_default;	/* default value*/
} fc_proccolinfo_t;

typedef struct{
	fc_stp_type_t kind;
	void * hm_hdl; /* hm_hdl_t * */
	dh_char_t *owner;
	dh_char_t *name;
	fc_proccolinfo_t *proc_colinfo;
	dh_i32_t col_num;
	dh_char_t *src_head;
	dh_char_t *src_txt;
	dh_u8_t  *bin;
	dh_i32_t bin_len;
	dh_i32_t options;
	sql_procrt_t    sqlp_runtime;
	dh_char_t sqlp_lang[TPE_MAX_IDLEN_P1];
	dh_char_t sqlp_run[SQL_RUN_MAX_LEN];
	/* these apply to stp */
	dh_boolean      has_result_set;		/* result set exists or not*/
	dh_boolean      has_return_value;		/* return value exists or not*/
	dh_boolean      built_in; /* built-in stored procedure*/
	/*these appy to triggers */
    /*dh_i16_t   triggerid;*/ /*trigger id */
    dh_char_t  *tbl_name; /*table name*/
    dh_char_t  *tbl_owner; /*table owner*/
    dh_char_t   trigger_time; 
    dh_char_t   trigger_event;
    dh_boolean   refers_to_old;
    dh_boolean   refers_to_new;
    dh_char_t   statement_or_row;
    /* raw buffer*/
    dh_u8_t  *raw;
    dh_i32_t raw_len;
} fc_stpdump_t;


typedef fc_stpdump_t *fc_stpdump_hdl_t;

fc_stpdump_t * alloc_fc_stpdump_t (void);

void free_fc_stpdump_t (fc_stpdump_t *arg);

extern void  EXPORT fc_sqldump_stp (dh_sqlenv_hdl_t sqlenv_hdl ,tpe_tm_hdl_t tpetmhdl, tpe_db_hdl_t tpedbhdl,
                  fc_stpdump_hdl_t info,
                  struct sqlca * ca);

extern void  EXPORT fc_sqldeploy_stp (dh_sqlenv_hdl_t sqlenv_hdl ,tpe_tm_hdl_t tpetmhdl, tpe_db_hdl_t tpedbhdl,
                  fc_stpdump_hdl_t info,
                  struct sqlca * ca);
#endif /* ctSQL_SP_RPC */
#endif /*FAIRCOM_MOD*/


/* Internal defs */
#define	FLD_NUMERIC	TPE_DT_NUMERIC
#define	FLD_SMALLINT	TPE_DT_SMALLINT
#define	FLD_INTEGER	TPE_DT_INTEGER

/* SMALLFLOAT has been mapped to REAL */
#define	FLD_SMALLFLOAT	TPE_DT_SMALLFLOAT
#define	FLD_REAL	TPE_DT_REAL

#define	FLD_FLOAT	TPE_DT_FLOAT
#define	FLD_DATE	TPE_DT_DATE
#define	FLD_MONEY	TPE_DT_MONEY
#define	FLD_TIME	TPE_DT_TIME
#define FLD_TIMESTAMP   TPE_DT_TIMESTAMP
#define FLD_TEXT	TPE_DT_TEXT
#define FLD_RAW         TPE_DT_RAW
#define FLD_ROWID       TPE_DT_ROWID
#define	FLD_MAXTYPES	TPE_DT_MAXTYPES
#define FLD_TINYINT	TPE_DT_TINYINT
#define FLD_BIGINT	TPE_DT_BIGINT
#define FLD_BINARY      TPE_DT_BINARY
#define FLD_VARBINARY   TPE_DT_VARBINARY  /* DC761 VARBINARY FIX */
#define FLD_BIT         TPE_DT_BIT
#define FLD_LVC       	TPE_DT_LVC
#define FLD_NLVC        TPE_DT_NLVC  /* DC698*/
#define FLD_LVB       	TPE_DT_LVB

/* DC608 BEGIN - LOB data type implementation. */

#define FLD_BLOB        TPE_DT_BLOB
#define FLD_CLOB        TPE_DT_CLOB
#define FLD_NCLOB        TPE_DT_NCLOB  /* DC698*/

/* DC608 END - LOB data type implementation. */


  /* START DC431 - L SUFFIX IN ERROR CODES REMOVED */  


#define		SQL_NOT_FOUND		100
#define         SQL_NULL_RESULT         101  /* DC424 */
#define		SQL_ERR_INTERNAL	-20000
#define		SQL_ERR_NOMEM		-20001
#define		SQL_ERR_INITFAIL	-20002
#define		SQL_ERR_INSYNTAX	-20003
#define		SQL_ERR_NOUSER		-20004
#define		SQL_ERR_NOTBL		-20005
#define		SQL_ERR_NOCOL		-20006
#define		SQL_ERR_NOCOLS		-20007
#define		SQL_ERR_INTYPES		-20008
#define		SQL_ERR_AMBCOL		-20009
#define		SQL_ERR_DUPCOL		-20010
#define		SQL_ERR_BADLEN		-20011
#define		SQL_ERR_BADPREC		-20012
#define		SQL_ERR_BADSC		-20013
#define		SQL_ERR_NOINS		-20014
#define		SQL_ERR_SUBQRETS	-20015
#define		SQL_ERR_BADNULL		-20016
#define		SQL_ERR_MOREVALS	-20017
#define		SQL_ERR_LESSVALS	-20018
#define		SQL_ERR_BADTBLREF	-20019
#define		SQL_ERR_BADGBCOL	-20020
#define		SQL_ERR_NOTGEIN_HVG	-20021
#define		SQL_ERR_NOTGEIN_SLCT	-20022
#define		SQL_ERR_BADSETFN	-20023
#define		SQL_ERR_NOTYET		-20024
#define		SQL_ERR_AFNESTED	-20025
#define		SQL_ERR_TBLREFCNT	-20026
#define		SQL_ERR_BADSORTFNUM	-20027
#define		SQL_ERR_DUPIDX		-20028
#define		SQL_ERR_NOIDX		-20029
#define		SQL_ERR_SEGEXISTS	-20030
#define		SQL_ERR_DUPCLUST	-20031
#define		SQL_ERR_NOCLUST		-20032
#define		SQL_ERR_NOTBLSP		-20033
#define		SQL_ERR_BADFPCT		-20034
#define		SQL_ERR_NONULL		-20035
#define		SQL_ERR_NOTPREPARED	-20036
#define		SQL_ERR_EXECSELECT	-20037
#define		SQL_ERR_NOTCLOSED	-20038
#define		SQL_ERR_NOTSELECT	-20039
#define		SQL_ERR_NOTOPENED	-20040
#define		SQL_ERR_TBLEXISTS	-20041
#define		SQL_ERR_MULTIDIST	-20042
#define		SQL_ERR_TPLSZHI		-20043
#define		SQL_ERR_ARRAYSZHI	-20044
#define		SQL_ERR_NOFILE		-20045
#define		SQL_ERR_FVNONULL	-20046
#define		SQL_ERR_GRSELF		-20047
#define		SQL_ERR_RVKSELF		-20048
#define		SQL_ERR_KEYWDUSED	-20049
#define		SQL_ERR_FLDCNTHI	-20050
#define		SQL_ERR_IDXCNTHI	-20051
#define		SQL_ERR_OVERFLOW	-20052
#define		SQL_ERR_DBNOTOPEN	-20053
#define		SQL_ERR_NODB		-20054
#define		SQL_ERR_DBNOTSTARTED	-20055
#define		SQL_ERR_NOTDBA		-20056
#define		SQL_ERR_NORES		-20057
#define		SQL_ERR_TRANS_ABORTED	-20058
#define		SQL_ERR_NOTSFILES	-20059
#define		SQL_ERR_TBLNOTEMPTY	-20060
#define		SQL_ERR_INPUTSZHI	-20061
#define		SQL_ERR_NOTPATHNM	-20062
#define		SQL_ERR_DUPFILE		-20063
#define		SQL_ERR_BADATCHT	-20064
#define		SQL_ERR_BADSTMTT	-20065
#define		SQL_ERR_BADSQLDA	-20066
#define		SQL_ERR_1LOCALONLY	-20067
#define		SQL_ERR_BADARG		-20068
#define		SQL_ERR_SMLSQLDA	-20069
#define		SQL_ERR_BUFLENHI	-20070
#define		SQL_ERR_INVALID_OPN	-20071
#define		SQL_ERR_SVRNOTALLOCD	-20072
#define		SQL_ERR_STMT_TOOLONG	-20073
#define		SQL_ERR_NOVIEWCOLLIST	-20074
#define		SQL_ERR_LESSCOLNS	-20075
#define		SQL_ERR_MORECOLNS	-20076
#define		SQL_ERR_CHK_OPTION	-20077
#define		SQL_ERR_ILLEGAL_OPN	-20078
#define		SQL_ERR_MAXTBL		-20079
#define		SQL_ERR_CHKOPT		-20080
#define		SQL_ERR_INVAL_CNT	-20081
#define		SQL_ERR_BADSORTFLD	-20082
#define		SQL_ERR_NOTCOLREF	-20083
#define		SQL_ERR_OJONSUBQUERY	-20084
#define		SQL_ERR_ERRINOUTER	-20085
#define		SQL_ERR_DUPCNST		-20086
#define		SQL_ERR_COLCNTMM	-20087
#define		SQL_ERR_INVUSER 	-20088
#define         SQL_ERR_SDATESETTING    -20089
#define		SQL_ERR_NOTBLCOLLIST	-20090
#define		SQL_ERR_QSTMTTOOLONG	-20091
#define		SQL_ERR_NOTPL		-20092
#define		SQL_ERR_SYNEXISTS	-20093
#define		SQL_ERR_LINKEXISTS	-20094
#define		SQL_ERR_NOLINK		-20095
#define		SQL_ERR_MANDUSER	-20096
#define		SQL_ERR_OPNNOTALLWD	-20097
#define		SQL_ERR_MUL_ROWS	-20098
#define		SQL_ERR_FTCH_RID	-20099
#define		SQL_ERR_BADSUBQRY	-20100
#define		SQL_ERR_NOREFS		-20101
#define		SQL_ERR_PKEYNULL	-20102
#define		SQL_ERR_NOKEY		-20103
#define		SQL_ERR_INCPKEYS	-20104
#define		SQL_ERR_NOPERM		-20105
#define		SQL_ERR_BADTID		-20106
#define		SQL_ERR_REMDBNOTUP	-20107
#define		SQL_ERR_REMSVRNOTUP	-20108
#define		SQL_ERR_NOREMDB		-20109
#define		SQL_ERR_NOREMHOST	-20110
#define		SQL_ERR_REFSPRSNT	-20115
#define		SQL_ERR_CNSTVIOLN	-20116
#define		SQL_ERR_TBLINCMPL	-20117
#define		SQL_ERR_DUPCONSTRAINT	-20118
#define		SQL_ERR_NOCONSTRAINT	-20119
#define		SQL_ERR_RESERVEWORD	-20120
#define		SQL_ERR_NOPERMISSION	-20121
#define		SQL_ERR_NOPROC		-20122
#define		SQL_ERR_INVALPROC	-20123
#define         SQL_QUERY_TERMINATE     -20124
#define		SQL_ERR_EXCEEDSMAX_OPNCURS	-20125
#define		SQL_ERR_INV_CURSNAME	-20126
#define		SQL_ERR_BADPARAM	-20127
#define         SQL_ERR_NUMRANGE        -20128
#define         SQL_ERR_DATATRUNC       -20129
#define         SQL_ERR_TRNSRLBK        -20130
#define         SQL_ERR_MISSINGPARAM    -20131
#define		SQL_ERR_RVKRESTRICT	-20132
#define         SQL_ERR_FENOTSUP        -20133
#define         SQL_ERR_INV_LONGREF     -20134        
#define		SQL_ERR_GETDIAG		-20135

#define         SQL_ERR_BADCNTNS        -20136
#define         SQL_ERR_BADCNTNSTP      -20137
#define         SQL_ERR_NOCNTNSIDX      -20138
#define         SQL_ERR_BADLNGIDX       -20139

#define         SQL_ERR_PROCEXISTS      -20140
/* DC113 BEGIN */
#define     SQL_ERR_JAVA_COMPILE        -20141
#define     SQL_ERR_JAVA_EXEC           -20142
#define     SQL_ERR_TOOMANYRECS         -20143
#define     SQL_ERR_NULLVAL             -20144
#define     SQL_ERR_INVALFLD            -20145
#define     SQL_ERR_TRGEXISTS     	-20146
#define     SQL_ERR_NOTRIGGER     	-20147
#define     SQL_ERR_TRIGEXEC     	-20148
#define     SQL_ERR_NOTFOUND     	-20149
/* DC113 END */
/* DC187 BEGIN */
#define         SQL_ERR_NOVIEWRSSID     -20150
/* DC187 END */
#define         SQL_ERR_USEDRTBL        -20151       /* DC223 */ 
#define         SQL_ERR_ALLOC_FAILED    -20152       /* DC272 */
#define         SQL_ERR_TREENOT_INCACHE -20153       /* DC272 */
#define         SQL_ERR_GCACHE_INSERT   -20154       /* DC272 */      
/* DC342 - DC_19990125_430 BEGIN */
#define         SQL_ERR_ENVFLGSET       -20155       /* DC310 */
/* DC342 - DC_19990125_430 END */

/* DC354 (DC_19981210_344) This error code indicates a NULL/empty 
 * sql statement */
#define               SQL_ERR_NOSTMT           -20156

/* DC594 DC_20030410_3284 BEGIN : DNDP connection to  database with */
/* length of 32 characters throws "Database improperly specified". */

#define               SQL_ERR_INVDBNAME        -20257

/* DC594 DC_20030410_3284 END : DNDP connection to database with  */
/* length of 32 characters throws "Database improperly specified". */

/*
 *
 * DC354 (DC_19990203_470) This error code indicates that a JSP/T
 * method is called out of sequence.
 * E.X.
 *  . SQLCursor.found() is called before SQLCursor.fetch()  or
 *  . SQLCursor.getValue() is called when SQLCursor.found() returned false.
 *
 */
#define               JSPT_ERR_SEQUENCE        -20157

#define         SQL_ERR_NOTRIG_ALWD     -20158       /* DC363 */
#define         SQL_ERR_NOREVOKE        -20159       /* DC363 */
#define         SQL_ERR_JSPTFENOTSUP    -20160       /* DC363 */
#define         SQL_ERR_PARAMNOTREGSTRD -20161       /* DC363 */
#define         SQL_ERR_PARAM_CANT_REGSTRD -20162    /* DC363 */
#define		SQL_ERR_REG_PARAM_NOTYET -20163      /* DC363 */

/* BEGIN DC364 / DC_19990810_1030
 * This error code indicates if the ESCAPE sequence is invalid
 */
#define               SQL_ERR_INV_ESCAPE              -20164
#define               SQL_ERR_INV_ESCSEQUENCE         -20165
/* END DC364 / DC_19990810_1030 */

/* BEGIN DC_20111018_4183 */
#define               SQL_ERR_NULLDFLT_MISMATCH       -20166
/* END DC_20111018_4183 */

/* DC571 BEGIN : Batchupdate implementation */
/* This error code indicates if the Batch execution has resulted in resultset.*/

#define               SQL_ERR_BATCHHASRESULTSET         -20174

/* DC571 END : Batchupdate implementation */

/* DC560 Begin - Changes for viewing the query execution plan */
#define SQL_ERR_QEP_INVPTBL -20169L
#define SQL_ERR_QEP_NORES -20170L
#define SQL_ERR_QEP_NOTDBA -20171L
#define SQL_ERR_QEP_BADAUTH -20172L
#define SQL_ERR_QEP_NOID -20173L
#define SQL_ERR_QEP_DUPID -20176L
/* DC560 End - Changes for viewing the query execution plan */	    

/* DC587 - DC_20020730_3143 Begin */
#define SQL_ERR_NULLCNST -20175L
#define SQL_ERR_PKNULL -20177L
/* DC587 - DC_20020730_3143 End */

/*dc632 BEGIN User Defined Scalar Function*/
/* Added new error codes*/
#define SQL_ERR_FUNCEXISTS -20182L
#define SQL_ERR_NOFUNC -20183L
/*dc632 END User Defined Scalar Function*/

/* LIKE only supported on CHAR types */
#define SQL_ERR_LIKENOTCHAR -20186L

/* SQL_NETWORK errcodes */
#define		SQL_ERR_RPC		-20211
#define		SQL_ERR_DAEMON		-20212
#define		SQL_ERR_SQLSVR		-20213
#define		SQL_ERR_SERVICE		-20214
#define		SQL_ERR_INVHOST		-20215
#define		SQL_ERR_INVDB		-20216
#define		SQL_ERR_NWERR		-20217
#define		SQL_ERR_INVPROTO	-20218

#define		SQL_ERR_INVCONNAME	-20219
#define		SQL_ERR_DUPCONNAME	-20220
#define		SQL_ERR_NOACTIVECONN	-20221
#define		SQL_ERR_NOENVDEFDB	-20222
#define		SQL_ERR_MULTILOCALCON	-20223
#define		SQL_ERR_INVPROTOCOL	-20224
#define		SQL_ERR_EXCEEDEDMAXCON	-20225
#define		SQL_ERR_BADDBHDL	-20226
#define		SQL_ERR_INVHOSTNAME	-20227
#define		SQL_ERR_BADAUTH		-20228

#define		SQL_ERR_INVDATE		-20229
#define		SQL_ERR_INVDATESTR	-20230
#define		SQL_ERR_INVNUMBER	-20231
#define		SQL_ERR_INVNUMSTR	-20232
#define		SQL_ERR_INVTIME		-20233
#define		SQL_ERR_INVTIMESTR	-20234
#define		SQL_ERR_INVTSSTR	-20235
#define		SQL_ERR_DIVBYZERO	-20236
#define         SQL_ERR_BADISCAN        -20237
#define         SQL_ERR_INVFORMAT       -20238
#define         SQL_ERR_INV_CHARSET     -20239 /* DC091 */
#define         SQL_ERR_INV_COLLATE     -20240
#define         SQL_ERR_SERVICE_INUSE   -20241 /* DC129 */
#define         SQL_ERR_INVTS           -20242 /* DC354 */

/*DC588 BEGIN : IP Address filtering by database server.*/
/* Error codes for IP address filtering.*/
#define         SQL_ERR_INV_DESTIP      -20255 /* Error code for invalid
                                                * destination IP address. */
#define         SQL_ERR_INV_SRCIP       -20256 /* Error code for invalid
                                                * source IP address. */
/*DC588 END : IP Address filtering by database server.*/

#define         SQL_ERR_ILLEGAL_BUFSZ   -20243 /* DC424 */
#define         SQL_ERR_COERCION        -20244 /* DC424 */
#define         SQL_ERR_MISSING_DBOPT   -20245 /* DC424 */
#define         SQL_ERR_BAD_DBOPT       -20246 /* DC424 */
#define         SQL_ERR_INV_CHARACTERS  -20247 /* DC424 */

/* DC463 BEGIN 
 * The following error codes relate to identifiers.
 */
#define         SQL_ERR_IDENTIFIER_OVFLOW    -20248 
#define         SQL_ERR_IDENTIFIER_INCOMPCHARSET -20249 
#define 	SQL_ERR_INV_IDENTIFIER  -20250 
#define         SQL_ERR_MISSING_SQUOT   -20251
#define         SQL_ERR_MISSING_DQUOT   -20252
/* DC463 END */
/* BEGIN DC569 DC_20020723_3127 */
#define         SQL_ERR_INVENVHDL       -20254
/* END DC569 DC_20020723_3127 */
                                                                                                 
/* DC608 BEGIN : LOB data type implementation. */
/* Error code for invalid lob column references. */
                                                                                                 
#define         SQL_ERR_INV_LOBREF      -20258
#define         SQL_ERR_BADLOBIDX       -20259
                                                                                                 
/* dc692 BEGIN : Hash implementation */
#define         SQL_ERR_NOTGEIN_ORD     -20260
/* dc692 END : Hash implementation */
                                                                                                 
/* DC608 END : LOB data type implementation. */
                                                                                                 
/* DC_20061204_3724 BEGIN : Order by in subquery */
#define         SQL_ERR_BAD_OBFLD_IN_SELDIS       -20261
#define         SQL_ERR_ORDBY_WOUT_TOP_OR_SKIP_IN_SUBQ    -20262 /* DC763 */
/* DC_20061204_3724 END : Order by in subquery */

/* DC698 BEGIN */
/* dc651 BEGIN : Enabling Client-Server Edition Mismatch checks */
/* Error code for Client-Server mismatch */
#define         CLIENT_SERVER_EDITION_MISMATCH  -20263
/* dc651 END : Enabling Client-Server Edition Mismatch checks */
/* DC698 END */

#define		SQL_ERR_NO_INDVAR	-20114
#define		SQL_ERR_QUERY_ABORTED	-30001

/* ODBC SDK specific errors */
#define         SQL_ERR_INVTBLID        -23000
#define         SQL_ERR_INVIDXID        -23001
/* DC_20110915_4181 Begin */
#define         SQL_ERR_INV_IDXHDL       -23002
/* DC_20110915_4181 End */

/* ODBC integrator error codes.  Sub-range of RDS     */

#define		SQL_ERR_VLDONATCHT	    	-25001
#define		SQL_ERR_INVLDONATCHT		-25002
#define         ITG_COPY_OBJECT_EXISTS   	-25003
#define 	ITG_NO_COPY_OBJECT       	-25004		
#define 	ITG_TBL_DROP_FAILED		-25005
#define 	ITG_BAD_COPY_SQL_STMT           -25006
#define 	ITG_UNKNOWN_DATA_TYPE           -25007
#define 	ITG_BAD_INSERT_STMT		-25008
#define 	ITG_FETCH_FAILED		-25009
#define 	ITG_INSERT_FAILED               -25010
#define 	ITG_OPERATION_NOT_STARTED       -25011
#define 	ITG_MARKED_FOR_ABORT		-25012
#define 	ITG_COMMIT_FAILED               -25013
#define 	ITG_CREATE_TBL_FAILED           -25014
#define 	ITG_BAD_SYNC_SQL_STMT           -25015
#define 	ITG_SYNC_OBJECT_EXISTS		-25016
#define 	ITG_CREATE_SYNC_OBJECT_FAILED   -25017
#define 	ITG_CREATE_COPY_OBJECT_FAILED   -25018
#define 	ITG_NO_SYNC_OBJECT		-25019
#define 	ITG_ILLEGAL_COLUMN_NAME         -25020	
#define 	ITG_DUPLICATE_COLUMN_NAME	-25021
#define 	ITG_INSTALL_FAILURE		-25022
#define 	ITG_UNKNOWN_SYNC_MODE           -25023
#define 	ITG_DWNLD_OR_SS_TABLE_MISSING	-25024
#define 	ITG_UPLD_TABLE_MISSING          -25025
#define 	ITG_UPDATE_FAILED               -25026
#define 	ITG_DELETE_FAILED		-25027
#define 	ITG_CLOSE_CURSOR_FAILED         -25028
#define 	ITG_NO_PRIMARY_KEY              -25029
#define 	ITG_MISSING_ROW                 -25030 
#define 	ITG_BAD_PRIMARY_KEY             -25031
#define 	ITG_UPDATE_CONTENTION		-25032
#define 	ITG_ATTACH_TABLE_FAILED         -25033
#define 	ITG_DETACH_TABLE_FAILED        	-25034
#define 	ITG_ATTACH_DATABASE_FAILED      -25035
#define 	ITG_DETACH_DATABASE_FAILED      -25036
#define         ITG_INTERNAL_ERROR              -25037
#define         ITG_OPERATION_ALREADY_STARTED   -25038
#define     ITG_OPEN_COPY_SQL_STMT_FAILED       -25039
#define     ITG_DROP_SYNC_OBJECT_FAILED         -25040
#define     ITG_DROP_COPY_OBJECT_FAILED         -25041
#define     ITG_CLOSING_COPY_SQL_STMT_FAILED    -25042
#define     ITG_TIMESTAMP_UPDATE_FAILED         -25043
#define 	ITG_BAD_ARG_SQL_STMT            -25044

/* ODBC integrator error codes in the TPE-ODBC translation layer */

#define 	ITG_ALLOCENVFAIL      -25101
#define 	ITG_ALLOCONNFAIL      -25102
#define 	ITG_SQLCONNFAIL       -25103
#define 	ITG_SQLGCOPTFAIL      -25104
#define 	ITG_SQLSCOPTFAIL      -25105
#define 	ITG_SQLDISCNFAIL      -25106
#define 	ITG_STMTMAPFAIL       -25107
#define 	ITG_DISCONNFAIL       -25108
#define 	ITG_SQLEXECFAIL       -25109
#define 	ITG_SQLRCNTFAIL       -25110
#define 	ITG_SETPARMFAIL       -25111
#define 	ITG_BINDCOLFAIL       -25112
#define 	ITG_SQLPREPFAIL       -25113
#define 	ITG_SQLRCOLFAIL       -25114
#define 	ITG_DSCRCOLFAIL       -25115
#define 	ITG_SQLFREEFAIL       -25116
#define 	ITG_SQLFTCHFAIL       -25117
#define 	ITG_SQLTRNSFAIL       -25118
#define 	ITG_ALLOCSTMTFAIL     -25119
#define 	ITG_SQLTBLSFAIL       -25120
#define 	ITG_SQLCOLSFAIL       -25121
#define 	ITG_SQLSTATFAIL       -25122
#define         ITG_ODBCIFACEERR      -25123
#define         ITG_ODBCLIMITERR      -25124
#define 	ITG_SQLGINFOFAIL      -25125
#define 	ITG_NOTONRONLYDB      -25126
#define 	ITG_NOTONVWWCK        -25127
#define         ITG_MAXREMROW_LMT     -25128
#define         ITG_SQLPKEYFAIL       -25129
#define         ITG_SQLFKEYFAIL       -25130
#define         ITG_DWNLD_COLINFO_FAIL -25131

#ifdef FAIRCOM_MOD
#define SQL_ERR_INV_CTOPT	-26000  /* ctSQL_CTOPTION */
#define SQL_ERR_FUTFEATNOTSUP	-26001 /* future feature not yet supported */
#define SQL_ERR_IDENTITY_OFF    -26002 /* ctSQL_IDENTITY_INSERT*/ 
#define SQL_ERR_IDENTITY_ON     -26003 /* ctSQL_IDENTITY_INSERT*/ 
#define SQL_ERR_NO_IDENTITY     -26004 /* ctSQL_IDENTITY_INSERT*/ 
#define SQL_ERR_INV_FLD_TYPE    -26005 /* ctSQL_FULLTEXT - invalid field type for full text index */
#define SQL_ERR_FTI_INV_SET     -26006 /* ctSQL_FULLTEXT - invalid index feature options combination */
#define SQL_ERR_BADMATCHTP      -26007 /* ctSQL_FULLTEXT - Index is not defined or does not support MATCH */
#define SQL_ERR_MULTMATCH       -26008 /* ctSQL_FULLTEXT - multiple index candidates */
#define SQL_ERR_MULTMATCHOP     -26009 /* ctSQL_FULLTEXT - multiple match operators on the same restriction */
#define SQL_ERR_SSATTR_SIZ      -26010 /* attribute length too long */
#define SQL_ERR_SSATTR_UNK      -26011 /* unknown attribute */
#define SQL_ERR_SSATTR_WRG      -26012 /* attribute does not apply */
#define SQL_ERR_SSATTR_SYX      -26013 /* attribute syntax error */
#define SQL_ERR_SSATTR_DUP      -26014 /* conflicting/duplicate attributes found */
#define SQL_STP_ERRMSG          -26015 /* stored procedure failed with error message */
#define SQL_RSS_INVID           -26016 /* rss id is invalid - not supported storage engine */
#define SQL_NO_CHARSET_MAX      -26017 /* the charset in use does not provide a char that collates last */
#define SQL_MISSING_CTREE_FILE  -26018 /* the file is missing from disk */
#endif
/* DC530 Begin - Changes for error log viewing */
#define ACCESS_LMTEXEED_LITERAL_LEN -26039L
/* DC530 End - Changes for error log viewing */


/*
 The next two values create potential bugs by over or under estimating
 the sizes of the 'rpc' buffers.
 */
#define MAXSIZE 8                 /* RPC size of double */
#define MAX_STRING_LEN 10000
#define MULTIPLE_OF_FOUR(x) (4*(((x) + 3)/4))


#define		DSN_MAXNAME_LEN		256
#define		DSN_MAXIFCNAME_LEN	32
#define		DSN_MAXTPNAME_LEN	256
#define		DSN_MAXHOSTNAME_LEN	256
#define		DSN_MAXPROC		100
/* dc629 BEGIN : Performance improvement.
 * Increasing the limit on size of requests sent by any client.
 */
#define		DSN_MAXBUF_SZ		50000 

/* Maximum size in bytes of preallocated buffer for
 * client packets. If you do not want preallocation,
 * set this constant to 0.
 */

#define		DSN_MAX_CLI_PREALLOCBUF_SZ		50000 

/* dc629 End : Performance improvement. */
	    
#define		DSN_MAX_STRSZ		1024
#define		DSN_MAXARG		5

#define		DSN_NBLOCK		0x2

#if !defined(DH_DAEMON_PORT) /* DC737 */
#ifdef DH_ODBC_SDK
#define		DH_DAEMON_PORT		1992
#else
#define		DH_DAEMON_PORT		1990
#endif 
#endif /* DC737 */

#define		MC_UNKNOWN		0
#define		MC_INTEL		1
#define		MC_MOTOROLA		2
#define		MC_SPARC		3
#define		MC_VAX			4
#define         MC_PA                   5
#define         MC_RS6000               6

/* dc627 Begin */         
#define         MC_POWERPC              7
/* dc627 End */

#define 	SNW_CHAR_SZ 		4
#define 	SNW_UCHAR_SZ 		4
#define 	SNW_SHORT_SZ 		4
#define 	SNW_USHORT_SZ 		4
/* DC691 BEGIN */
#define 	SNW_SHORT_SZ1 		2
#define 	SNW_USHORT_SZ1 		2
/* DC691 END */
#define 	SNW_LONG_SZ 		4
#define 	SNW_ULONG_SZ 		4
#define 	SNW_FLOAT_SZ 		4
#define 	SNW_DOUBLE_SZ 		8

/*
 List of SQL NETWORK error codes
*/


#define		DSN_STATUS_OK 		0
#define		DSN_NO_MEM		-30011
#define		DSN_INV_HDL		-30002
#define		DSN_INV_INTERFACE	-30003
#define		DSN_INV_PROC		-30004
#define		DSN_ALREADY_ATCHD	-30005
#define		DSN_ENT_NOTFND		-30006
#define		DSN_ENT_EXISTS		-30007
#define		DSN_SIZE_MISMATCH	-30008
#define		DSN_INV_SVRID		-30009
#define		DSN_INV_REPLY		-30010

#define		DSN_XMIT_ERR		-30031
#define		DSN_RECV_ERR		-30032
#define		DSN_NO_DATA		-30033
#define		DSN_ERR_NWERR		-30034

#define		DSN_IN_PROCESS		-30051

#define		DSN_DAEMON_ERR		-30061
#define		DSN_ARGCNT_ERR		-30062
#define		DSN_IFACE_NFND		-30063
#define		DSN_INV_PROCID		-30064
#define		DSN_SVR_NOTAVL		-30065
#define		DSN_INV_CONFIG		-30066
#define		DSN_IFACE_NSUP		-30067

#define		DSN_SERVICE_ERR		-30091
#define		DSN_HOST_ERR		-30092
#define		DSN_ACCEPT_ERR		-30093
#define		DSN_CONNECT_ERR		-30094
#define		DSN_BIND_ERR		-30095
#define		DSN_SOC_ERR		-30096
#define		DSN_HDLOPT_ERR		-30097

#define 	DSN_ATTACH_TYPE_ERR	-30098

#define		DSN_INTERRUPTED		-30101

/* DC095 */
#define		DSN_ERR_NOTCOMPAT	-30102

/* ENV Manager error codes */
#define		SQL_ERR_ENVOVFLOW	-40001

/* DC197 start  */
/* New storage system ( DHRSS ) error code */
#define		DHRSS_ERROR_IMPRPR_CALL	-50000
/* DC197 end   */

/*--------------------------------------------------*/
/* ESQLC converts all capital letters to lower case */

/* dc630 march-19-2004 BEGIN */
#define		SQL_ERR_NOVIEW	-20179
#define     SQL_ERR_NOSYN	-20181

/* dc643 DC_19990720_948 BEGIN :Drop table with synonym name
   should return error. */

#define     SQL_ERR_NOTTBL       -20184L

 /* dc643 DC_19990720_948 BEGIN :Drop table with synonym name 
    should return error. */

/* dc630 march-19-2004 END */

/* DC729 DC_20080521_3912 BEGIN */
                                                                                
#define     SQL_ERR_EXCEEDS_MAX_LITLEN       -20185
                                                                                
/* DC729 DC_20080521_3912 END */

/* DC698: JVM Initialization BEGIN */
                                                                                
#define     SQL_ERR_JVMINIT      -20187
                                                                                
/* DC698: JVM Initialization END */

#define		SQL_ERR_AMBIDX		-20193 /* dc767 */

/* DC_20091203_4062 Begin  */
#define     SQL_ERR_DUP_DFLT_IDENT      -20188
#define     SQL_ERR_INS_UPD_IDENT       -20189
#define     SQL_ERR_INVAL_IDENT_SEED_INCR       -20190
#define     SQL_ERR_IDENT_FLDTYPE       -20191
#define     SQL_ERR_IDENT_FLD_ONLY      -20192
/* DC_20091203_4062 End  */

/* DC_20130904_4225 */
#define		SQL_ERR_SRCHRQD 	-20194


/* DC_20140319_4233 Begin */
#define         SQL_ERR_USR_OR_GRP_EXISTS -20195  
#define         SQL_ERR_NOUSER_OR_GRP     -20196  
#define         SQL_ERR_USER_IN_GRP       -20197  
#define         SQL_ERR_NOUSERGRP         -20198 
#define         SQL_ERR_NOUSER_IN_GRP     -20199 
  /* DS_20151109_0010 adding usergroups to usergroups */
  /*#define         SQL_ERR_CANT_ADD_GRP_TO_GRP     -20200 */
#define         SQL_ERR_GRP_EXISTS_IN_GRP     -20200
/* DC_20140319_4233 End */

/* DC_20140530_4235 Begin */
#define		SQL_ERR_PROC_HAS_OUT_INOUT_PARAM  -20201 
#define		SQL_ERR_PROC_HAS_NO_RESULTSET 	  -20202 
/* DC_20140530_4235 End */

/* DS_20140314_0004 Begin */
#define         SQL_ERR_PROC_NO_SCROLL  -20203
/* DS_20140314_0004 End */

#define SQL_ERR_QUERY_TIMED_OUT               -30012 /* DC_20080910_3930 */

/* DC602 BEGIN : Limiting number of records in result sets.*/

#define		SQL_ERR_PERCNTWITHTIES_NOTSUP	-20178

/* DC602 END : Limiting number of records in result sets.*/

#ifdef FAIRCOM_MOD /*faircom error messages @SQL level */
#define CTREE_LPWD_ERR -17451
#define CTREE_LMTC_ERR -17530
#define CTREE_LSEC_ERR -17941
#define CTREE_LSES_ERR -17942
#define CTREE_LSEV_ERR -17959
#define CTREE_PBAD_ERR -17749
#define CTREE_UALC_ERR -17082
#define CTREE_SSLCONN_ERR -18104
#define CTREE_SERVER_LOGON_REQUIRES_MD5 -18160
#define CTREE_CLIENT_LOGON_REQUIRES_SHA512 -18161
#endif
/* DC737 BEGIN */

#define SQL_LIC_ERR_ENVVARIABLE         -27183
#define SQL_LIC_ERR_FILENOTFOUND        -27184
#define SQL_LIC_ERR_FILESYNTAX          -27185
#define SQL_LIC_ERR_TEXTIGNORE          -27186
#define SQL_LIC_ERR_NODE                -27181
#define SQL_LIC_ERR_DATE                -27182

/* DC737 END */

#if	defined(__cplusplus)
}
#endif

/* dc611 BEGIN : Porting Customer changes to Dharma/SQL 9.0
 *
 * Wrapping of vendor specific literals defined in dh_literals.h
 * with DH_STRING_LITERAL. 
 * dh_literals.h is directly included in login.rc, there it was
 * giving error because of DH_STRING_LITERAL.  
 */

#define DH_CONSTR_PREFIX      DH_STRING_LITERAL(CONSTR_PREFIX)

#define DH_PRODUCT_NAME       DH_STRING_LITERAL(PRODUCT_NAME)

#define DH_COMPANY_NAME1      DH_STRING_LITERAL(COMPANY_NAME1)

#define DH_COMPANY_NAME2      DH_STRING_LITERAL(COMPANY_NAME2)

#define DH_DATA_SOURCE_LOGIN  DH_STRING_LITERAL(DATA_SOURCE_LOGIN)

#define DH_VENDOR             DH_STRING_LITERAL(VENDOR)

/* DC761 Begin */
#define DH_DRV_PRODUCT_NAME   DH_STRING_LITERAL(DRV_PRODUCT_NAME)
/* DC761 End */
 
/* DC738 - BEGIN */
                                                                              
extern sql_dbcase_t EXPORT
dh_get_db_case(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t        /* IN Dharma SQL environment handle */
#endif
);
                                                                              

extern sql_idcase_t EXPORT
dh_get_identifier_case(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    dh_sqlenv_hdl_t        /* IN Dharma SQL environment handle */
#endif
);
                                                                              
                                                                              
extern void EXPORT
dh_set_open_deferred(
#if   defined(__cplusplus) || !defined(NO_PROTOTYPE)
    tpe_cursor_t,          /* IN Cursor */
    dh_sqlenv_hdl_t        /* IN Dharma SQL environment handle */
#endif
);
                                                                              
/* DC738 - END */

/* The naming convention followed for literals above is not used for
 * 'DBA'. Using 'DBA' was causing problem in HP Build as DBA is a token
 * defined in a grammer file.
 */

#ifndef DH_DBA 			/* FAIRCOM_MOD */
#define DH_DBA                DH_STRING_LITERAL(DBA_NAME)
#endif

/* DC737 BEGIN */
#if !defined(DH_ERR_ON_ACTIVE_TRAN)
#define DH_ERR_ON_ACTIVE_TRAN	0 
#endif
/* DC737 END */

/* dc611 END : Porting Customer changes to Dharma/SQL 9.0 */


/*dc598 BEGIN : Dharma/SQL 10.0 Release Stabilization.*/

#ifndef  DH_ACCESS_VERSION 	/* FAIRCOM_MOD */
#define DH_ACCESS_VERSION DH_STRING_LITERAL(ACCESS_VERSION)
#endif

#ifndef  DH_DRIVER_VERSION	/* FAIRCOM_MOD */
#define DH_DRIVER_VERSION DH_STRING_LITERAL(DRIVER_VERSION)
#endif

#ifndef  DH_COPYRIGHT_DATE	/* FAIRCOM_MOD */
#define DH_COPYRIGHT_DATE DH_STRING_LITERAL(COPYRIGHT_DATE)
#endif

/*dc598 BEGIN : Dharma/SQL 10.0 Release Stabilization.*/

/* DC738 BEGIN: Enum definition has been moved here from catalog.cxx file. */
typedef enum    {
        ATTACHED,        /* attached tables  */
        SYNONYM,         /* synonyms         */
        SYSTEM,          /* system tables    */
        TABLE,           /* ordinary tables  */
        VIEW,            /* views            */
        ALL_CATALOGS,    /* special semantics - get all valid catalogs     */
        ALL_SCHEMAS,     /* special semantics - get all valid schemas      */
        ALL_TABLE_TYPES, /* special semantics - get all valid table types  */
        MAX_STMT_TYPES   /* dummy - number of elements in this enumeration */
        } table_info_type;
/* DC738 END */

/* DC738 BEGIN */
/*
 * Defines whether data type information for ODBC API SQLGetTypeInfo() should
 * be obtained from server.
 *
 * Set DH_SQLGETTYPEINFO_FROM_SERVER to 1 to get the type info from the
 * server. Set it to 0 to get the hard coded values from the ODBC driver
 * itself.
 *
 * Value 1 of the constant enables old functionality where SQLGetTypeInfo()
 * executes an SQL Statement to get the type info from the server. The old
 * functionality has been preserved in case customers depend on getting the
 * info from the server.
 *
 * A value of 0 of the constant enables new functionality where interaction
 * with the server is avoided by returing hard coded values.
 *
 * By default its value is 0.
 */
#if !defined(DH_SQLGETTYPEINFO_FROM_SERVER)
#define DH_SQLGETTYPEINFO_FROM_SERVER   0
#endif
/* DC738 END */

#endif		/* sql_lib_included */

#ifdef DH_ESQL /* FAIRCOM_MOD */

#ifdef UNICODE

#if defined FAIRCOM_MOD  && defined DH_OS_WINNT
#define os_printf	wprintf
#endif
#define os_strcpy	wcscpy
#define os_strncpy	wcsncpy
#define os_strlen	wcslen
#ifdef DH_OS_WINNT
#define os_getenv	_wgetenv
#define os_fprintf	_ftprintf
#define os_sprintf	_stprintf
#define os_mbstowcs	mbstowcs
#else /*DH_OS_WINNT  FAIRCOM_MOD */
extern  dh_char_t       *os_getenv (const dh_char_t * senv);
#endif

#ifdef FAIRCOM_MOD
#define os_strcmp	wcscmp
#endif
#else  /* ~UNICODE */

#define os_printf	printf
#define os_strcpy	strcpy
#define os_strncpy	strncpy
#define os_strlen	strlen
#define os_strcmp	strcmp
#define os_getenv	getenv
#define os_fprintf	fprintf
#define os_sprintf	sprintf

#endif /* ~UNICODE */

#endif /* DH_ESQL */

#endif /* ~ __SQL_LIB_H__ */

/* end of sql_lib.h */
