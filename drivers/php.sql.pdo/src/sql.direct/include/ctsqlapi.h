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
#ifndef _CTSQLAPI_H_
#define _CTSQLAPI_H_

#if defined UNICODE && !defined _WIN32
#include <wchar.h>
#endif

#ifndef FAIRCOM_CODE
#define FAIRCOM_CODE
#endif
#include "ctsql_lib.h"

#define SQLAPI_BATCHES
#define SQLAPI_NO_LTYPE_GETFIELD

/****************************************************************************/
#ifdef _WIN32_WCE
#ifdef CTSQLAPI_EXPORTS
#define CTSQLAPI_API __declspec(dllexport)
#else
#define CTSQLAPI_API __declspec(dllimport)
#endif
// This class is exported from the ctsqlapi.dll
class CTSQLAPI_API CCtsqlapi {
public:
	CCtsqlapi(void);
	// TODO: add your methods here.
};

extern CTSQLAPI_API int nCtsqlapi;
CTSQLAPI_API int fnCtsqlapi(void);
#endif /*  _WIN32_WCE */
/****************************************************************************/


/****************************************************************************\
*
*	defines
*
\****************************************************************************/
#define ctsqlDECL
#define CTSQL_MAX_ERRLEN	512
#ifdef ctSQL_MAX_FLDLEN
#define CTSQL_MAX_FLDLEN	ctSQL_MAX_FLDLEN
#else
#error ctSQL_MAX_FLDLEN not defined
#endif
#define CTSQL_FALSE			0
#define CTSQL_TRUE			1
/****************************************************************************\
*
*	Base types
*
\****************************************************************************/
typedef unsigned char	BIT;
typedef char			TINYINT;
typedef unsigned char	UTINYINT;
typedef short			SMALLINT;
typedef unsigned short	USMALLINT;
typedef int				INTEGER;
typedef unsigned int	UINTEGER;
typedef float			SMALLFLOAT;
typedef double			FLOATT;
#if defined(UNICODE) && !defined(ctPortWINIOT)
typedef wchar_t			CTSQLCHAR;
#else
typedef char			CTSQLCHAR;
#endif

/****************************************************************************\
*
*	dh_sql functions wrappers
*
\****************************************************************************/
#ifdef ctSQLSRVR
extern status_t get_thread_rds_env (rds_env_t **);
#define DH_SQLDESCRIBE_PARAM(a) ssm_describe_param(a->m_sqlenv, a->m_conn->m_user, a->m_cursor->m_uuid, TRUE, a->m_cursor->m_sqlcmd, a->m_isqlda, &a->m_conn->m_sqlca);tpe_check_error (&a->m_conn->m_sqlca)
#define DH_SQL_CHK_CONNECTION(a,b) (b->sqlcode = 0)
#define DH_SQLPREPARE(hCmd,b) ssm_prepare(hCmd->m_sqlenv, hCmd->m_conn->m_user, hCmd->m_cursor->m_uuid, TRUE, hCmd->m_cursor->m_sqlcmd, b); tpe_check_error (b)
#define DH_SQLDECLARE(a,s) NULL
#define DH_SQLEXECUTEBATCH(hCmd,b) ssm_execute_batch(hCmd->m_sqlenv, hCmd->m_conn->m_user, hCmd->m_cursor->m_uuid, TRUE, hCmd->m_cursor->m_sqlcmd, b, &hCmd->m_conn->m_sqlca); tpe_check_error (&hCmd->m_conn->m_sqlca)
#define DH_SQLEXECUTE(hCmd,b,c,d) ssm_execute(hCmd->m_sqlenv, hCmd->m_conn->m_user, hCmd->m_cursor->m_uuid, TRUE, hCmd->m_cursor->m_sqlcmd, b, &hCmd->m_conn->m_sqlca,c,d); tpe_check_error (&hCmd->m_conn->m_sqlca)
#define DH_SQLDESCRIBE(hCmd,b) ssm_describe(hCmd->m_sqlenv, hCmd->m_conn->m_user, hCmd->m_cursor->m_uuid, TRUE, hCmd->m_cursor->m_sqlcmd, b, &hCmd->m_conn->m_sqlca); tpe_check_error (&hCmd->m_conn->m_sqlca)
#define DH_SQLOPEN(hCmd,b) ssm_open(hCmd->m_sqlenv, hCmd->m_conn->m_user, hCmd->m_cursor->m_uuid, TRUE, hCmd->m_cursor->m_sqlcmd, b, &hCmd->m_conn->m_sqlca); tpe_check_error (&hCmd->m_conn->m_sqlca)
#define DH_SQLCLOSE(hCmd) ssm_close(hCmd->m_sqlenv, hCmd->m_conn->m_user, hCmd->m_cursor->m_uuid, TRUE, hCmd->m_cursor->m_sqlcmd, &hCmd->m_conn->m_sqlca); tpe_check_error (&hCmd->m_conn->m_sqlca)
#define DH_SQLFETCH(hCursor) ssm_fetch(hCursor->m_sqlenv, hCursor->m_cmd->m_conn->m_user, hCursor->m_cursor->m_uuid, TRUE, hCursor->m_cmd->m_sqlcmd, hCursor->m_sqlda, hCursor->m_sqlcaptr); tpe_check_error (hCursor->m_sqlcaptr)
#define DH_SQLPUTDATA(hCmd, vartype, ptr, len, offset, dataptr) NULL /* TODO */
#define DH_SQLGETDATA(hCursor,dtype,ptr,a,b,buf,r) NULL /* TODO */
#define DH_ALLOC_SQLENV(a) get_thread_rds_env((rds_env_t **) a)
#define DH_FREE_SQLENV(a) (a = (rds_env_t *) NULL)
#define DH_SET_CURSOR(hCmd,b,c) {\
	hCmd->m_cursor = (ctSQLSRVCURSOR*) ctsql_alloc(sizeof(ctSQLSRVCURSOR),1);\
	if (hCmd->m_cursor)\
	{\
		hCmd->m_cursor->m_uuid = &hCmd->m_uuid;\
		hCmd->m_cursor->m_sqlcmd = hCmd->m_sqlcmd;\
	}\
	}
#define DH_SET_CURSORNAME(a,s,d) NULL
#define DH_SET_QUERY_TIMEOUT(a) NULL /* no query timeout on server side as it may collide with the one set from the client */
#define GEN_UUID(a,b) (b)->uuid_gen()
#define DH_RELEASE_CURSOR(a,b) (ctsql_free(*b),*b=NULL)
#define DH_TM_SET_LEVEL(a,s,d) NULL
#define DH_TM_GET_LEVEL(a,s,d) 0
#else
#define DH_SQLCONNECT dh_sqlconnect
#define DH_SQL_DISCONNECT dh_sql_disconnect
#define DH_SQLDESCRIBE_PARAM(hCmd) dh_sqldescribe_param(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, hCmd->m_isqlda, &hCmd->m_conn->m_sqlca)
#define DH_SQL_CHK_CONNECTION dh_sql_chk_connection
#define DH_SQLPREPARE(hCmd,b) dh_sqlprepare(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, b)
#define DH_SQLDECLARE(hCmd,b) dh_sqldeclare(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, NULL, b)
#define DH_SQLEXECUTEBATCH(hCmd,b) dh_sqlexecutebatch(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, b, &hCmd->m_conn->m_sqlca)
#define DH_SQLEXECUTE(hCmd,b,c,d) dh_sqlexecute(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, b, &hCmd->m_conn->m_sqlca)
#define DH_SQLDESCRIBE(hCmd,b) dh_sqldescribe(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, b, &hCmd->m_conn->m_sqlca)
#define DH_SQLOPEN(hCmd,b) dh_sqlopen(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, b, &hCmd->m_conn->m_sqlca)
#define DH_SQLCLOSE(hCmd) dh_sqlclose(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, &hCmd->m_conn->m_sqlca)
#define DH_SQLPUTDATA(hCmd, vartype, ptr, len, offset, dataptr) dh_sqlputdata(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, vartype, ptr, len, offset, dataptr, hCmd->m_sqlca)
#define DH_SQLFETCH(hCursor) dh_sqlfetch(hCursor->m_sqlenv, dh_get_curtmhdl(hCursor->m_sqlenv), dh_get_curdbhdl(hCursor->m_sqlenv), hCursor->m_cursor, hCursor->m_sqlda, hCursor->m_sqlcaptr)
#define DH_SQLGETDATA(hCursor,dtype,ptr,a,b,buf,r) dh_sqlgetdata(hCursor->m_sqlenv, dh_get_curtmhdl(hCursor->m_sqlenv), dh_get_curdbhdl(hCursor->m_sqlenv), hCursor->m_cursor, dtype, ptr, a, b, buf, r, hCursor->m_sqlcaptr)
#define DH_ALLOC_SQLENV dh_alloc_sqlenv
#define DH_FREE_SQLENV dh_free_sqlenv
#define DH_SET_CURSOR(hCmd,b,type) dh_set_cursor(hCmd->m_sqlenv, dh_get_curtmhdl(hCmd->m_sqlenv), dh_get_curdbhdl(hCmd->m_sqlenv), &hCmd->m_cursor, &hCmd->m_uuid, type, hCmd->m_sqlcmd, b)
#define DH_SET_CURSORNAME dh_set_cursorname
#define DH_SET_QUERY_TIMEOUT(hCmd) dh_set_query_timeout(dh_get_curdbhdl(hCmd->m_sqlenv), hCmd->m_cursor, hCmd->m_timeout);
#define FC_SQLDUMP_STP(hConn,hprocinfo) fc_sqldump_stp(hConn->m_sqlenv, dh_get_curtmhdl(hConn->m_sqlenv), dh_get_curdbhdl(hConn->m_sqlenv), hprocinfo, &hConn->m_sqlca)
#define FC_SQLDEPLOY_STP(hConn,hprocinfo) fc_sqldeploy_stp(hConn->m_sqlenv, dh_get_curtmhdl(hConn->m_sqlenv), dh_get_curdbhdl(hConn->m_sqlenv), hprocinfo, &hConn->m_sqlca)
#define GEN_UUID gen_uuid
#define DH_RELEASE_CURSOR dh_release_cursor
#define DH_TM_MARK_ABORT(hConn) dh_tm_mark_abort(hConn->m_sqlenv, dh_get_curtmhdl(hConn->m_sqlenv), &hConn->m_sqlca)
#define DH_TM_END_TRANS(hConn) dh_tm_end_trans(hConn->m_sqlenv, dh_get_curtmhdl(hConn->m_sqlenv), &hConn->m_sqlca)
#define DH_TM_SET_LEVEL dh_tm_set_level
#define DH_TM_GET_LEVEL dh_tm_get_level
#endif

#define FC_IS_LONG_TYPE(x)  (((x) == TPE_DT_LVC || (x) == TPE_DT_NLVC || (x) == TPE_DT_LVB || (x) == TPE_DT_BLOB || (x) == TPE_DT_CLOB || (x) == TPE_DT_NCLOB)?1:0)
/****************************************************************************\
*
*	portability macros	
*
\****************************************************************************/
#define ctsql_alloc(size,count)		calloc((count),(size))
#define ctsql_free(ptr)				free(ptr)
#define ctsql_stralloc(size)		(CTSQLCHAR*)ctsql_alloc(sizeof(CTSQLCHAR),(size))
#define ctsql_memcpy				memcpy
#define ctsql_memset				memset
#if defined(UNICODE) && !defined(ctPortWINIOT)
#define ctsql_atoi(a)				wcstol(a, NULL, 10)
#define ctsql_atof(a)				wcstod(a, NULL)
#define ctsql_strlen(st)			((st) ? wcslen(st) : 0)
#define ctsql_strcpy(dst,src)		wcscpy(dst,src)
#define ctsql_strcat(dst,src)		wcscat(dst,src)
#ifdef _WIN32
#define ctsql_strdup(st)			_wcsdup(st)
#else
#define ctsql_strdup(st)			wcsdup(st)
#endif
#define ctsql_strchr(st,ch)			wcschr(st,ch)
#define ctsql_strcmp(s1,s2)			wcscmp(s1,s2)
#define ctsql_strncmp(s1,s2,l)		wcsncmp(s1,s2,l)
#define ctsql_strrchr(st,ch)			wcsrchr(st,ch)
#define ctsql_sprintf			wsprintf
#else
#define ctsql_atoi(a)				atoi(a)
#define ctsql_atof(a)				atof(a)
#define ctsql_strlen(st)			((st) ? strlen(st) : 0)
#define ctsql_strcpy(dst,src)		strcpy(dst,src)
#define ctsql_strcat(dst,src)		strcat(dst,src)
#ifdef DH_OS_UNIX
#define ctsql_strdup(st)			strdup(st)
#else
#define ctsql_strdup(st)			_strdup(st)
#endif
#define ctsql_strchr(st,ch)			strchr(st,ch)
#define ctsql_strcmp(s1,s2)			strcmp(s1,s2)
#define ctsql_strncmp(s1,s2,l)			strncmp(s1,s2,l)
#define ctsql_strrchr(st,ch)			strrchr(st,ch)
#define ctsql_sprintf			sprintf
#endif
#define ctsql_strset(st,val)		{if (st) ctsql_free(st); st = ctsql_strdup(val);}


/****************************************************************************\
*
*	Field type
*
\****************************************************************************/
typedef SMALLINT CTSQLTYPE;

#define CTSQL_INVTYPE         -1
#define CTSQL_CHAR             1
#define CTSQL_NUMERIC          2
#define CTSQL_SMALLINT         3
#define CTSQL_INTEGER          4
#define CTSQL_SMALLFLOAT       5
#define CTSQL_REAL             5
#define CTSQL_FLOAT            6
#define CTSQL_DATE             7
#define CTSQL_MONEY            8
#define CTSQL_TIME             9
#define CTSQL_TIMESTAMP       10
#define CTSQL_TINYINT         11
#define CTSQL_BINARY          12
#define CTSQL_BIT             13
#define CTSQL_LVC             14
#define CTSQL_LVB             15
#define CTSQL_BIGINT          16
#define CTSQL_NCHAR           17
#define CTSQL_NVARCHAR        18
#define CTSQL_NCHAR_CS        19
#define CTSQL_NVARCHAR_CS     20
#define CTSQL_VARCHAR         21
#define CTSQL_BLOB            22
#define CTSQL_CLOB            23
#define CTSQL_NLVC            24
#define CTSQL_NCLOB           25
#define CTSQL_VARBINARY       26
/****************************************************************************\
*
*	Transaction isolation level
*
\****************************************************************************/
typedef enum 
{ 
    CTSQL_READ_UNCOMMITTED = 0, 
    CTSQL_READ_COMMITTED = 1,
    CTSQL_REPEATABLE_READ = 2, 
    CTSQL_SERIALIZABLE = 3, 
    CTSQL_INVALID_ISOLATION_LEVEL = 4
} CTSQL_ISOLEVEL ; 
/****************************************************************************\
*
*	Nullability flags
*
\****************************************************************************/
typedef enum  
{
	CTSQL_NO_NULLS,
	CTSQL_NULLABLE,
	CTSQL_NULLABLE_UNKNOWN
} CTSQL_NULLABILITY;
/****************************************************************************\
*
*	SQL numeric type
*
\****************************************************************************/
#define SQL_NUMERIC_SIZE 16

typedef struct 
{
	SMALLINT dec_num;
	TINYINT	 dec_digits[SQL_NUMERIC_SIZE + 1];
} NUMERIC;

#ifndef TEST_SP
/****************************************************************************\
*
*	SQL DATE
*
\****************************************************************************/
typedef struct 
{
	SMALLINT year ;
	UTINYINT month;
	UTINYINT day ;
} SQLDATE;
/****************************************************************************\
*
*	SQL TIME
*
\****************************************************************************/
typedef struct 
{
	UTINYINT  hours;
	UTINYINT  mins;
	UTINYINT  secs;
	USMALLINT msecs;
} SQLTIME;
/****************************************************************************\
*
*	SQL TIMESTAMP
*
\****************************************************************************/
typedef struct 
{
	SQLDATE ts_date;
    SQLTIME ts_time;
}  SQLTIMESTAMP;  
#endif /* ~TEST_SP */
/****************************************************************************\
*
*	SQL BINARY
*
\****************************************************************************/
typedef struct 
{
	INTEGER	 tb_len;
	UTINYINT tb_data [CTSQL_MAX_FLDLEN] ;
} BINARY;
/****************************************************************************\
*
*	SQL BIGINT
*
\****************************************************************************/
typedef struct 
{
	UINTEGER ll ;
	INTEGER  hl ;
} BIGINT;

typedef enum {
	INFO_STP,
	INFO_UDF,
	INFO_TRG
 } STP_TYPE;

#undef  CT_STRING_LITERAL
#if defined(UNICODE) && !defined(ctPortWINIOT)
#define CT_STR_LIT(s) L ## s
#define CT_STRING_LITERAL(s) CT_STR_LIT(s)
#else
#define CT_STRING_LITERAL(s) s
#endif


/****************************************************************************\
*
*	Return types
*
\****************************************************************************/
typedef INTEGER			CTSQLRET, *pCTSQLRET;

#define CTSQLRET_OK					0

#define	CTSQL_NOTFOUND				100
#define CTSQL_NULLRESULT    		101

#define	CTSQLRET_INTERNAL			-20000
#define	CTSQLRET_NOMEM				-20001
#define	CTSQLRET_INITFAIL			-20002
#define	CTSQLRET_INSYNTAX			-20003
#define	CTSQLRET_NOUSER				-20004
#define	CTSQLRET_NOTBL				-20005
#define	CTSQLRET_NOCOL				-20006
#define	CTSQLRET_NOCOLS				-20007
#define	CTSQLRET_INTYPES			-20008
#define	CTSQLRET_AMBCOL				-20009
#define	CTSQLRET_DUPCOL				-20010
#define	CTSQLRET_BADLEN				-20011
#define	CTSQLRET_BADPREC			-20012
#define	CTSQLRET_BADSC				-20013
#define	CTSQLRET_NOINS				-20014
#define	CTSQLRET_SUBQRETS			-20015
#define	CTSQLRET_BADNULL			-20016
#define	CTSQLRET_MOREVALS			-20017
#define	CTSQLRET_LESSVALS			-20018
#define	CTSQLRET_BADTBLREF			-20019
#define	CTSQLRET_BADGBCOL			-20020
#define	CTSQLRET_NOTGEIN_HVG		-20021
#define	CTSQLRET_NOTGEIN_SLCT 		-20022
#define	CTSQLRET_BADSETFN			-20023
#define	CTSQLRET_NOTYET				-20024
#define	CTSQLRET_AFNESTED			-20025
#define	CTSQLRET_TBLREFCNT			-20026
#define	CTSQLRET_BADSORTFNUM		-20027
#define	CTSQLRET_DUPIDX				-20028
#define	CTSQLRET_NOIDX				-20029
#define	CTSQLRET_SEGEXISTS			-20030
#define	CTSQLRET_DUPCLUST			-20031
#define	CTSQLRET_NOCLUST			-20032
#define	CTSQLRET_NOTBLSP			-20033
#define	CTSQLRET_BADFPCT			-20034
#define	CTSQLRET_NONULL				-20035
#define	CTSQLRET_NOTPREPARED		-20036
#define	CTSQLRET_EXECSELECT			-20037
#define	CTSQLRET_NOTCLOSED			-20038
#define	CTSQLRET_NOTSELECT			-20039
#define	CTSQLRET_NOTOPENED			-20040
#define	CTSQLRET_TBLEXISTS			-20041
#define	CTSQLRET_MULTIDIST			-20042
#define	CTSQLRET_TPLSZHI			-20043
#define	CTSQLRET_ARRAYSZHI			-20044
#define	CTSQLRET_NOFILE				-20045
#define	CTSQLRET_FVNONULL			-20046
#define	CTSQLRET_GRSELF				-20047
#define	CTSQLRET_RVKSELF			-20048
#define	CTSQLRET_KEYWDUSED			-20049
#define	CTSQLRET_FLDCNTHI			-20050
#define	CTSQLRET_IDXCNTHI			-20051
#define	CTSQLRET_OVERFLOW			-20052
#define	CTSQLRET_DBNOTOPEN			-20053
#define	CTSQLRET_NODB				-20054
#define	CTSQLRET_DBNOTSTARTED		-20055
#define	CTSQLRET_NOTDBA				-20056
#define	CTSQLRET_NORES				-20057
#define	CTSQLRET_TRANS_ABORTED		-20058
#define	CTSQLRET_NOTSFILES			-20059
#define	CTSQLRET_TBLNOTEMPTY		-20060
#define	CTSQLRET_INPUTSZHI			-20061
#define	CTSQLRET_NOTPATHNM			-20062
#define	CTSQLRET_DUPFILE			-20063
#define	CTSQLRET_BADATCHT			-20064
#define	CTSQLRET_BADSTMTT			-20065
#define	CTSQLRET_BADSQLDA			-20066
#define	CTSQLRET_1LOCALONLY			-20067
#define	CTSQLRET_BADARG				-20068
#define	CTSQLRET_SMLSQLDA			-20069
#define	CTSQLRET_BUFLENHI			-20070
#define	CTSQLRET_INVALID_OPN		-20071
#define	CTSQLRET_SVRNOTALLOCD		-20072
#define	CTSQLRET_STMT_TOOLONG		-20073
#define	CTSQLRET_NOVIEWCOLLIST		-20074
#define	CTSQLRET_LESSCOLNS			-20075
#define	CTSQLRET_MORECOLNS			-20076
#define	CTSQLRET_CHK_OPTION			-20077
#define	CTSQLRET_ILLEGAL_OPN		-20078
#define	CTSQLRET_MAXTBL				-20079
#define	CTSQLRET_CHKOPT				-20080
#define	CTSQLRET_INVAL_CNT			-20081
#define	CTSQLRET_BADSORTFLD			-20082
#define	CTSQLRET_NOTCOLREF			-20083
#define	CTSQLRET_OJONSUBQUERY		-20084
#define	CTSQLRET_ERRINOUTER			-20085
#define	CTSQLRET_DUPCNST			-20086
#define	CTSQLRET_COLCNTMM			-20087
#define	CTSQLRET_INVUSER 			-20088
#define CTSQLRET_SDATESETTING    	-20089
#define	CTSQLRET_NOTBLCOLLIST		-20090
#define	CTSQLRET_QSTMTTOOLONG		-20091
#define	CTSQLRET_NOTPL				-20092
#define	CTSQLRET_SYNEXISTS			-20093
#define	CTSQLRET_LINKEXISTS			-20094
#define	CTSQLRET_NOLINK				-20095
#define	CTSQLRET_MANDUSER			-20096
#define	CTSQLRET_OPNNOTALLWD		-20097
#define	CTSQLRET_MUL_ROWS			-20098
#define	CTSQLRET_FTCH_RID			-20099
#define	CTSQLRET_BADSUBQRY			-20100
#define	CTSQLRET_NOREFS				-20101
#define	CTSQLRET_PKEYNULL			-20102
#define	CTSQLRET_NOKEY				-20103
#define	CTSQLRET_INCPKEYS			-20104
#define	CTSQLRET_NOPERM				-20105
#define	CTSQLRET_BADTID				-20106
#define	CTSQLRET_REMDBNOTUP			-20107
#define	CTSQLRET_REMSVRNOTUP		-20108
#define	CTSQLRET_NOREMDB			-20109
#define	CTSQLRET_NOREMHOST			-20110
#define	CTSQLRET_REFSPRSNT			-20115
#define	CTSQLRET_CNSTVIOLN			-20116
#define	CTSQLRET_TBLINCMPL			-20117
#define	CTSQLRET_DUPCONSTRAINT		-20118
#define	CTSQLRET_NOCONSTRAINT		-20119
#define	CTSQLRET_RESERVEWORD		-20120
#define	CTSQLRET_NOPERMISSION		-20121
#define	CTSQLRET_NOPROC				-20122
#define	CTSQLRET_INVALPROC			-20123
#define CTSQL_QUERY_TERMINATE     	-20124
#define	CTSQLRET_EXCEEDSMAX_OPNCURS	-20125
#define	CTSQLRET_INV_CURSNAME		-20126
#define	CTSQLRET_BADPARAM			-20127
#define CTSQLRET_NUMRANGE        	-20128
#define CTSQLRET_DATATRUNC       	-20129
#define CTSQLRET_TRNSRLBK        	-20130
#define CTSQLRET_MISSINGPARAM    	-20131
#define	CTSQLRET_RVKRESTRICT		-20132
#define CTSQLRET_FENOTSUP        	-20133
#define CTSQLRET_INV_LONGREF     	-20134        
#define	CTSQLRET_GETDIAG			-20135
#define CTSQLRET_BADCNTNS        	-20136
#define CTSQLRET_BADCNTNSTP      	-20137
#define CTSQLRET_NOCNTNSIDX      	-20138
#define CTSQLRET_BADLNGIDX       	-20139
#define CTSQLRET_PROCEXISTS      	-20140
#define CTSQLRET_JAVA_COMPILE       -20141
#define CTSQLRET_JAVA_EXEC          -20142
#define CTSQLRET_TOOMANYRECS        -20143
#define CTSQLRET_NULLVAL            -20144
#define CTSQLRET_INVALFLD           -20145
#define CTSQLRET_TRGEXISTS     		-20146
#define CTSQLRET_NOTRIGGER     		-20147
#define CTSQLRET_TRIGEXEC     		-20148
#define CTSQLRET_NOTFOUND     		-20149
#define CTSQLRET_NOVIEWRSSID     	-20150
#define CTSQLRET_USEDRTBL        	-20151 
#define CTSQLRET_ALLOC_FAILED    	-20152
#define CTSQLRET_TREENOT_INCACHE 	-20153 
#define CTSQLRET_GCACHE_INSERT   	-20154      
#define CTSQLRET_ENVFLGSET       	-20155 
#define CTSQLRET_NOSTMT           	-20156
#define CTSQLRET_NOTRIG_ALWD     	-20158       
#define CTSQLRET_NOREVOKE        	-20159       
#define CTSQLRET_JSPTFENOTSUP    	-20160       
#define CTSQLRET_PARAMNOTREGSTRD 	-20161       
#define CTSQLRET_PARAM_CANT_REGSTRD -20162    
#define	CTSQLRET_REG_PARAM_NOTYET 	-20163      
#define CTSQLRET_INV_ESCAPE         -20164
#define CTSQLRET_INV_ESCSEQUENCE    -20165
#define CTSQLRET_BATCHHASRESULTSET  -20174
#define CTSQLRET_QEP_INVPTBL 		-20169L
#define CTSQLRET_QEP_NORES 			-20170L
#define CTSQLRET_QEP_NOTDBA 		-20171L
#define CTSQLRET_QEP_BADAUTH 		-20172L
#define CTSQLRET_QEP_NOID 			-20173L
#define CTSQLRET_QEP_DUPID 			-20176L
#define CTSQLRET_NULLCNST 			-20175L
#define CTSQLRET_PKNULL 			-20177L
#define CTSQLRET_FUNCEXISTS 		-20182L
#define CTSQLRET_NOFUNC 			-20183L
#define	CTSQLRET_RPC				-20211
#define	CTSQLRET_DAEMON				-20212
#define	CTSQLRET_SQLSVR				-20213
#define	CTSQLRET_SERVICE			-20214
#define	CTSQLRET_INVHOST			-20215
#define	CTSQLRET_INVDB				-20216
#define	CTSQLRET_NWERR				-20217
#define	CTSQLRET_INVPROTO			-20218
#define	CTSQLRET_INVCONNAME			-20219
#define	CTSQLRET_DUPCONNAME			-20220
#define	CTSQLRET_NOACTIVECONN		-20221
#define	CTSQLRET_NOENVDEFDB			-20222
#define	CTSQLRET_MULTILOCALCON		-20223
#define	CTSQLRET_INVPROTOCOL		-20224
#define	CTSQLRET_EXCEEDEDMAXCON		-20225
#define	CTSQLRET_BADDBHDL			-20226
#define	CTSQLRET_INVHOSTNAME		-20227
#define	CTSQLRET_BADAUTH			-20228
#define	CTSQLRET_INVDATE			-20229
#define	CTSQLRET_INVDATESTR			-20230
#define	CTSQLRET_INVNUMBER			-20231
#define	CTSQLRET_INVNUMSTR			-20232
#define	CTSQLRET_INVTIME			-20233
#define	CTSQLRET_INVTIMESTR			-20234
#define	CTSQLRET_INVTSSTR			-20235
#define	CTSQLRET_DIVBYZERO			-20236
#define CTSQLRET_BADISCAN        	-20237
#define CTSQLRET_INVFORMAT       	-20238
#define CTSQLRET_INV_CHARSET     	-20239 
#define CTSQLRET_INV_COLLATE     	-20240
#define CTSQLRET_SERVICE_INUSE   	-20241 
#define CTSQLRET_INVTS           	-20242 
#define CTSQLRET_ILLEGAL_BUFSZ   	-20243 
#define CTSQLRET_COERCION        	-20244 
#define CTSQLRET_MISSING_DBOPT   	-20245 
#define CTSQLRET_BAD_DBOPT       	-20246 
#define CTSQLRET_INV_CHARACTERS  	-20247 
#define CTSQLRET_INVENVHDL       	-20254
#define CTSQLRET_IDENTIFIER_OVFLOW    -20248 
#define CTSQLRET_IDENTIFIER_INCOMPCHARSET -20249 
#define CTSQLRET_INV_IDENTIFIER  	-20250 
#define CTSQLRET_MISSING_SQUOT   	-20251
#define CTSQLRET_MISSING_DQUOT   	-20252
#define	CTSQLRET_NO_INDVAR			-20114
#define	CTSQLRET_QUERY_ABORTED		-30001
#define CTSQLRET_INVTBLID        	-23000
#define CTSQLRET_INVIDXID        	-23001
#define	CTSQLRET_VLDONATCHT	    	-25001
#define	CTSQLRET_INVLDONATCHT		-25002
/****************************************************************************\
*
*	SQL Handles:
*
*	pCTSQLCONN
*		SQL connection handle
*
*	pCTSQLCMD
*		SQL command handle
*
*	pCTSQLCURSOR
*
*		SQL cursor handle
*
*	pCTSQLPROCINFO
*
*		Stored procedure(trigger & udf) information handle
*
\****************************************************************************/
typedef struct tagCTSQLCONN		*pCTSQLCONN, **ppCTSQLCONN;
typedef struct tagCTSQLCMD		*pCTSQLCMD, **ppCTSQLCMD;
typedef struct tagCTSQLCURSOR	*pCTSQLCURSOR, **ppCTSQLCURSOR;
typedef void *pCTSQLPROCINFO, **ppCTSQLPROCINFO;

/****************************************************************************\
*
*	c-treeACE SQL connection functions
*
\****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
CTSQLRET ctsqlDECL ctsqlSetSSL(pCTSQLCONN hConn, CTSQLCHAR* certificate);
pCTSQLCONN ctsqlDECL ctsqlNewConnection(void);
void ctsqlDECL ctsqlFreeConnection(pCTSQLCONN hConn);
CTSQLRET ctsqlDECL ctsqlConnect(pCTSQLCONN hConn, CTSQLCHAR* dbname, CTSQLCHAR* username, CTSQLCHAR* password);
CTSQLRET ctsqlDECL ctsqlDisconnect(pCTSQLCONN hConn);
CTSQLRET ctsqlDECL ctsqlAttach(pCTSQLCONN hConn);
CTSQLRET ctsqlDECL ctsqlDetach(pCTSQLCONN hConn);
CTSQLCHAR* ctsqlDECL ctsqlGetDatabase(pCTSQLCONN hConn);
CTSQLCHAR* ctsqlDECL ctsqlGetUsername(pCTSQLCONN hConn);
CTSQLCHAR* ctsqlDECL ctsqlGetPassword(pCTSQLCONN hConn);
BIT ctsqlDECL ctsqlIsActiveConn(pCTSQLCONN hConn);
CTSQLRET ctsqlDECL ctsqlBegin(pCTSQLCONN hConn);
CTSQLRET ctsqlDECL ctsqlCommit(pCTSQLCONN hConn);
CTSQLRET ctsqlDECL ctsqlAbort(pCTSQLCONN hConn);
CTSQLCHAR* ctsqlDECL ctsqlGetErrorMessage(pCTSQLCONN hConn);
CTSQLRET ctsqlDECL ctsqlGetError(pCTSQLCONN hConn);
void ctsqlDECL ctsqlClearError(pCTSQLCONN hConn);
CTSQLRET ctsqlDECL ctsqlSetIsolationLevel(pCTSQLCONN hConn, CTSQL_ISOLEVEL level);
CTSQL_ISOLEVEL ctsqlDECL ctsqlGetIsolationLevel(pCTSQLCONN hConn);
BIT ctsqlDECL ctsqlGetAutoCommit(pCTSQLCONN hConn);
CTSQLRET ctsqlDECL ctsqlSetAutoCommit(pCTSQLCONN hConn, BIT flag);
CTSQLRET ctsqlDECL ctsqlSetTypeCheckOnGet(pCTSQLCONN hConn, BIT flag);
CTSQLRET ctsqlDECL ctsqlClearAutoCommit(pCTSQLCONN hConn);
INTEGER ctsqlDECL ctsqlGetErrorPos(pCTSQLCONN hConn);
BIT ctsqlIsUnicodeLib(void);
CTSQLRET ctsqlDECL ctsqlSetPreserveCursor(pCTSQLCONN hCmd, BIT flag);
#ifdef __cplusplus
}
#endif
/****************************************************************************\
*
*	c-treeACE SQL command functions
*
\****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
pCTSQLCMD ctsqlDECL ctsqlNewCommand(pCTSQLCONN hConn);
void ctsqlDECL ctsqlFreeCommand(pCTSQLCMD hCmd);
CTSQLRET ctsqlDECL ctsqlGetParameter(pCTSQLCMD hCmd, INTEGER index, void* buffer, INTEGER length);
CTSQLRET ctsqlDECL ctsqlSetParameter(pCTSQLCMD hCmd, INTEGER index, CTSQLTYPE ptype, INTEGER length, BIT isnull, void* buffer);
CTSQLRET ctsqlDECL ctsqlSetParameterAsString(pCTSQLCMD hCmd, INTEGER index, CTSQLCHAR* buffer);
CTSQLRET ctsqlDECL ctsqlSetIntegerParameter(pCTSQLCMD hCmd, INTEGER index, CTSQLTYPE ptype, BIT isnull, INTEGER buffer);
CTSQLRET ctsqlDECL ctsqlSetBigIntParameter(pCTSQLCMD hCmd, INTEGER index, BIT isnull, BIGINT* buffer);
CTSQLRET ctsqlDECL ctsqlSetNumericParameter(pCTSQLCMD hCmd, INTEGER index, CTSQLTYPE ptype, BIT isnull, NUMERIC* buffer);
CTSQLRET ctsqlDECL ctsqlSetFloatParameter(pCTSQLCMD hCmd, INTEGER index, CTSQLTYPE ptype, BIT isnull, FLOATT buffer);
CTSQLRET ctsqlDECL ctsqlSetDateParameter(pCTSQLCMD hCmd, INTEGER index, BIT isnull, SQLDATE* buffer);
CTSQLRET ctsqlDECL ctsqlSetTimeParameter(pCTSQLCMD hCmd, INTEGER index, BIT isnull, SQLTIME* buffer);
CTSQLRET ctsqlDECL ctsqlSetTimeStampParameter(pCTSQLCMD hCmd, INTEGER index, BIT isnull, SQLTIMESTAMP* buffer);
CTSQLRET ctsqlDECL ctsqlSetNCharParameter(pCTSQLCMD hCmd, INTEGER index, CTSQLTYPE ptype, BIT isnull, CTSQLCHAR* buffer, INTEGER len);
CTSQLRET ctsqlDECL ctsqlSetCharParameter(pCTSQLCMD hCmd, INTEGER index, CTSQLTYPE ptype, BIT isnull, char* buffer, INTEGER len);
CTSQLRET ctsqlDECL ctsqlSetBinaryParameter(pCTSQLCMD hCmd, INTEGER index, BIT isnull, void* buffer, INTEGER size);
INTEGER ctsqlDECL ctsqlGetParameterCount(pCTSQLCMD hCmd);
CTSQLTYPE ctsqlDECL ctsqlGetParameterType(pCTSQLCMD hCmd, INTEGER index);
INTEGER ctsqlDECL ctsqlGetParameterLength(pCTSQLCMD hCmd, INTEGER index);
SMALLINT ctsqlDECL ctsqlGetParameterPrecision(pCTSQLCMD hCmd, INTEGER index);
INTEGER ctsqlDECL ctsqlGetParameterPrecisionX(pCTSQLCMD hCmd, INTEGER index);
SMALLINT ctsqlDECL ctsqlGetParameterScale(pCTSQLCMD hCmd, INTEGER index);
CTSQL_NULLABILITY ctsqlDECL ctsqlGetParameterNullFlag(pCTSQLCMD hCmd, INTEGER index);
CTSQLCHAR* ctsqlDECL ctsqlGetParameterName(pCTSQLCMD hCmd, INTEGER index);
INTEGER ctsqlDECL ctsqlGetParameterIndexByName(pCTSQLCMD hCmd, CTSQLCHAR* name);
CTSQLRET ctsqlDECL ctsqlSetParameterScale(pCTSQLCMD hCmd, INTEGER index, SMALLINT scale);
CTSQLRET ctsqlDECL ctsqlSetParameterPrecision(pCTSQLCMD hCmd, INTEGER index, SMALLINT precision);
CTSQLRET ctsqlDECL ctsqlSetParameterPrecisionX(pCTSQLCMD hCmd, INTEGER index, INTEGER precision);
CTSQLRET ctsqlDECL ctsqlPrepare(pCTSQLCMD hCmd, CTSQLCHAR* sqlcmd);
CTSQLRET ctsqlDECL ctsqlExecute(pCTSQLCMD hCmd, ppCTSQLCURSOR pCursor);
CTSQLRET ctsqlDECL ctsqlExecuteDirect(pCTSQLCMD hCmd, CTSQLCHAR* sqlcmd);
INTEGER ctsqlDECL ctsqlAffectedRows(pCTSQLCMD hCmd);
CTSQLRET ctsqlDECL ctsqlClose(pCTSQLCMD hCmd);
CTSQLRET ctsqlDECL ctsqlSetBlob(pCTSQLCMD hCmd, INTEGER colnumber, void* buffer, INTEGER size, INTEGER offset);
INTEGER ctsqlDECL ctsqlGetTimeout(pCTSQLCMD hCmd);
CTSQLRET ctsqlDECL ctsqlSetTimeout(pCTSQLCMD hCmd, INTEGER timeout);
BIT ctsqlDECL ctsqlIsSelect(pCTSQLCMD hCmd);
BIT ctsqlDECL ctsqlIsProcedureCall(pCTSQLCMD hCmd);
CTSQLRET ctsqlDECL ctsqlSetTupleCount(pCTSQLCMD hCmd, INTEGER count);
INTEGER ctsqlDECL ctsqlGetTupleCount(pCTSQLCMD hCmd);
CTSQLRET ctsqlDECL ctsqlPrepareBatch(pCTSQLCMD hCmd, CTSQLCHAR* sqlcmd, INTEGER batch_size);
INTEGER ctsqlDECL ctsqlNextBatchItem(pCTSQLCMD hCmd);
CTSQLRET ctsqlDECL ctsqlSetNumericParameterAsString(pCTSQLCMD hCmd, INTEGER index, CTSQLTYPE ptype, BIT isnull, CTSQLCHAR* buffer);
CTSQLRET ctsqlDECL ctsqlGetNumericParameterAsString(pCTSQLCMD hCmd, INTEGER index, CTSQLCHAR* buffer, INTEGER length);
BIT ctsqlDECL ctsqlIsParameterNull(pCTSQLCMD hCmd, INTEGER index);
CTSQLRET ctsqlDECL ctsqlSetScrollableCursor(pCTSQLCMD hCmd, BIT flag);
BIT ctsqlDECL ctsqlGetScrollableCursor(pCTSQLCMD hCmd);
#ifdef __cplusplus
}
#endif
/****************************************************************************\
*
*	c-treeACE SQL cursor functions
*
\****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
pCTSQLCURSOR ctsqlDECL ctsqlNewCursor(pCTSQLCMD hCmd);
pCTSQLCURSOR ctsqlDECL ctsqlNewDACursor(void *psqlda);
void ctsqlDECL ctsqlFreeCursor(pCTSQLCURSOR hCursor);
INTEGER ctsqlDECL ctsqlGetColumnCount(pCTSQLCURSOR hCursor);
INTEGER ctsqlDECL ctsqlGetColumnNameLen(pCTSQLCURSOR hCursor, INTEGER colnumber);
CTSQLCHAR* ctsqlDECL ctsqlGetColumnName(pCTSQLCURSOR hCursor, INTEGER colnumber);
TINYINT* ctsqlDECL ctsqlGetVariableAddress(pCTSQLCURSOR hCursor, INTEGER colnumber);
CTSQLRET ctsqlDECL ctsqlGetColumnTitle(pCTSQLCURSOR hCursor, INTEGER colnumber, CTSQLCHAR* colname, int size);
CTSQLTYPE ctsqlDECL ctsqlGetColumnType(pCTSQLCURSOR hCursor, INTEGER colnumber);
INTEGER ctsqlDECL ctsqlGetColumnLength(pCTSQLCURSOR hCursor, INTEGER colnumber);
SMALLINT ctsqlDECL ctsqlGetColumnPrecision(pCTSQLCURSOR hCursor, INTEGER colnumber);
INTEGER ctsqlDECL ctsqlGetColumnPrecisionX(pCTSQLCURSOR hCursor, INTEGER colnumber);
SMALLINT ctsqlDECL ctsqlGetColumnScale(pCTSQLCURSOR hCursor, INTEGER colnumber);
CTSQL_NULLABILITY ctsqlDECL ctsqlIsNullable(pCTSQLCURSOR hCursor, INTEGER colnumber);
CTSQLRET ctsqlDECL ctsqlNext(pCTSQLCURSOR hCursor);
BIT ctsqlDECL ctsqlIsColumnNull(pCTSQLCURSOR hCursor, INTEGER colnumber);
CTSQLRET ctsqlDECL ctsqlGetNChar(pCTSQLCURSOR hCursor, INTEGER colnumber, CTSQLCHAR* buffer);
CTSQLRET ctsqlDECL ctsqlGetChar(pCTSQLCURSOR hCursor, INTEGER colnumber, char* buffer);
CTSQLRET ctsqlDECL ctsqlGetNumeric(pCTSQLCURSOR hCursor, INTEGER colnumber, NUMERIC* buffer);
CTSQLRET ctsqlDECL ctsqlGetSmallInt(pCTSQLCURSOR hCursor, INTEGER colnumber, SMALLINT* buffer);
CTSQLRET ctsqlDECL ctsqlGetInteger(pCTSQLCURSOR hCursor, INTEGER colnumber, INTEGER* buffer);
CTSQLRET ctsqlDECL ctsqlGetReal(pCTSQLCURSOR hCursor, INTEGER colnumber, SMALLFLOAT* buffer);
CTSQLRET ctsqlDECL ctsqlGetFloat(pCTSQLCURSOR hCursor, INTEGER colnumber, FLOATT* buffer);
CTSQLRET ctsqlDECL ctsqlGetDate(pCTSQLCURSOR hCursor, INTEGER colnumber, SQLDATE* buffer);
CTSQLRET ctsqlDECL ctsqlGetMoney(pCTSQLCURSOR hCursor, INTEGER colnumber, NUMERIC* buffer);
CTSQLRET ctsqlDECL ctsqlGetTime(pCTSQLCURSOR hCursor, INTEGER colnumber, SQLTIME* buffer);
CTSQLRET ctsqlDECL ctsqlGetTimeStamp(pCTSQLCURSOR hCursor, INTEGER colnumber, SQLTIMESTAMP* buffer);
CTSQLRET ctsqlDECL ctsqlGetTinyInt(pCTSQLCURSOR hCursor, INTEGER colnumber, TINYINT* buffer);
CTSQLRET ctsqlDECL ctsqlGetBinary(pCTSQLCURSOR hCursor, INTEGER colnumber, BINARY* buffer);
INTEGER ctsqlDECL ctsqlGetBytes(pCTSQLCURSOR hCursor, INTEGER colnumber, UTINYINT buffer[], INTEGER size);
CTSQLRET ctsqlDECL ctsqlGetBit(pCTSQLCURSOR hCursor, INTEGER colnumber, BIT* buffer);
CTSQLRET ctsqlDECL ctsqlGetBigInt(pCTSQLCURSOR hCursor, INTEGER colnumber, BIGINT* buffer);
CTSQLRET ctsqlDECL ctsqlGetBlob(pCTSQLCURSOR hCursor, INTEGER colnumber, void* buffer, INTEGER size, INTEGER offset, INTEGER *bytesread);
CTSQLRET ctsqlDECL ctsqlGetBlobByAddress(pCTSQLCURSOR hCursor, TINYINT* address, void* buffer, INTEGER size, INTEGER offset, INTEGER *bytesread);
CTSQLRET ctsqlDECL ctsqlGetTableName(pCTSQLCURSOR hCursor, INTEGER colnumber, CTSQLCHAR* buffer, INTEGER size);
CTSQLRET ctsqlDECL ctsqlGetBaseTableName(pCTSQLCURSOR hCursor, INTEGER colnumber, CTSQLCHAR* buffer, INTEGER size);
CTSQLRET ctsqlDECL ctsqlGetBaseColumnName(pCTSQLCURSOR hCursor, INTEGER colnumber, CTSQLCHAR* buffer, INTEGER size);
INTEGER ctsqlDECL ctsqlIsSearchable(pCTSQLCURSOR hCursor, INTEGER colnumber);
INTEGER ctsqlDECL ctsqlIsUpdatable(pCTSQLCURSOR hCursor, INTEGER colnumber);
CTSQLRET ctsqlDECL ctsqlGetNumericAsString(pCTSQLCURSOR hCursor, INTEGER colnumber, CTSQLCHAR* buffer, INTEGER size);
#ifdef __cplusplus
}
#endif
/****************************************************************************\
*
*	data conversion functions	
*
\****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
CTSQLRET ctsqlDECL ctsqlCompare(CTSQLTYPE dtype, void* buffer1, INTEGER length1, void* buffer2, INTEGER length2, INTEGER* result);
CTSQLRET ctsqlDECL ctsqlConvert(CTSQLTYPE stype, void* buffer1, INTEGER length1, CTSQLCHAR* fmt, CTSQLTYPE dtype, void* buffer2, INTEGER length2);
int ctsqlDECL ctsqlDayOfWeek(SQLDATE date);
CTSQLRET ctsqlDECL ctsqlAddNumeric(NUMERIC* num1, NUMERIC* num2, NUMERIC* res);
CTSQLRET ctsqlDECL ctsqlSubNumeric(NUMERIC* num1, NUMERIC* num2, NUMERIC* res);
CTSQLRET ctsqlDECL ctsqlMulNumeric(NUMERIC* num1, NUMERIC* num2, NUMERIC* res);
CTSQLRET ctsqlDECL ctsqlDivNumeric(NUMERIC* num1, NUMERIC* num2, NUMERIC* res);
CTSQLRET ctsqlDECL ctsqlRoundNumeric(NUMERIC* num, INTEGER precision, INTEGER scale);
CTSQLRET ctsqlDECL ctsqlNumericToString(NUMERIC* num, CTSQLCHAR* str, INTEGER len);
CTSQLRET ctsqlDECL ctsqlStringToNumeric(CTSQLCHAR *str, INTEGER len, NUMERIC* num);
#ifdef __cplusplus
}
#endif
/****************************************************************************/

/****************************************************************************\
*
*	misc functions	
*
\****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
CTSQLRET ctsqlDECL ctsqlCleanPooled(pCTSQLCONN hConn);
pCTSQLPROCINFO ctsqlDECL ctsqlNewProcInfo(CTSQLCHAR* owner, CTSQLCHAR* name, STP_TYPE kind);
void ctsqlDECL ctsqlFreeProcInfo(pCTSQLPROCINFO hprocinfo);
CTSQLRET ctsqlDECL ctsqlDumpStp(pCTSQLCONN hConn, pCTSQLPROCINFO hprocinfo);
CTSQLRET ctsqlDECL ctsqlDumpStpRaw(pCTSQLCONN hConn, pCTSQLPROCINFO hprocinfo, void** buffer, INTEGER* bufferLen);
CTSQLRET ctsqlDECL ctsqlDeployStp(pCTSQLCONN hConn, pCTSQLPROCINFO hprocinfo);
CTSQLRET ctsqlDECL ctsqlDeployStpRaw(pCTSQLCONN hConn, pCTSQLPROCINFO hprocinfo, void* buffer, INTEGER bufferLen);
void ctsqlDECL ctsqlLogStp(CTSQLCHAR* msg);
void ctsqlDECL ctsqlErrStp(CTSQLCHAR* msg);

#ifdef __cplusplus
}
#endif

#endif /* _CTSQLAPI_H_ */

/* end of ctsqlsdk.h */
