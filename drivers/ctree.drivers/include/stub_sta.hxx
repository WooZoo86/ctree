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
 *	In addition:
 *	This Module also contains Proprietary Information of
 *	Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 *	and should be treated as Confidential.
 *	
 *	Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *	Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *	
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

/******************************************************************************\
*
*	Project	: Dharma SQL with ctdb
*	Date	: 30 Aug 2011
*	Author	: Paolo
*	Notes	: new file containing bridge from SQL XX statistics and c-tree
*			  SQL snapshot feature 
*
\******************************************************************************/

#ifndef __STUB_STA_INCLUDED
#define __STUB_STA_INCLUDED

#ifndef __cplusplus
extern void UpdateSQLSnapshot(pctSQLS sqls);
#else
extern "C" void UpdateSQLSnapshot(pctSQLS sqls);
class SQLSnapshot;
extern SQLSnapshot * SQLsnapshots;
	
/**************************************************************************\
 * enum StatClassType                                                      *
 * enumerator for the various types of snapshot statistics we collect      *
\**************************************************************************/
enum StatClassType {
	stat_none,
	stat_gcache_stmt_dyn,
	stat_gcache_stmt_loc,
	stat_gcache_stmt_sta,
	stat_stub_idx_scan
};

/**************************************************************************\
 * class SQLBaseStat                                                      *
 * base class for the various types of snapshot statistics we collect     *
\**************************************************************************/
class SQLBaseStat
{
protected:
	StatClassType StatType;

public:
	SQLBaseStat(StatClassType t);
	virtual ~SQLBaseStat(void){};
	dh_i32_t Register(SQLSnapshot *);
	dh_i32_t UnRegister(SQLSnapshot *);
	virtual void UpdateSnapshot(pctSQLS sqls) = 0;
};


/**************************************************************************\
 * class gcache_snapshott                                                 *
 * specialization of SQLBaseStat for gcache                               *
\**************************************************************************/

class gcache_snapshot : public SQLBaseStat
{
private:
	dh_longlong_t	requests;
	dh_longlong_t	hits;
	dh_i32_t	max_entries;
	dh_i32_t	entries;  
	dh_i32_t	high_entries; /* highest number on entries */

public:
	gcache_snapshot(StatClassType t, dh_i32_t max) : SQLBaseStat(t) 
	{
		requests = 0;
		hits = 0;
		max_entries = max;
		entries = 0;
		high_entries = 0;
	};
	~gcache_snapshot(void) {};
	void UpdateSnapshot(pctSQLS sqls);
	void AddEntry(void);
	void DelEntry(void);
	void AddHitReq(void);
	void AddMissReq(void);
};

/**************************************************************************\
 * class stubidx_snapshot                                                 *
 * specialization of SQLBaseStat for index scan snapshots                 *
\**************************************************************************/

class stubidx_snapshot : public SQLBaseStat
{
private:
	dh_longlong_t if_accounted;
	dh_longlong_t rf_accounted;
	dh_longlong_t	indexonlyfetch;
	dh_longlong_t	rec_indexfetch;
	SQLSnapshot *main_stat;

public:
	stubidx_snapshot(void) : SQLBaseStat(stat_stub_idx_scan) 
	{
		indexonlyfetch = 0;
		rec_indexfetch = 0;
		if_accounted = 0;
		rf_accounted = 0;
		main_stat = NULL;
	};
	~stubidx_snapshot(void);
	dh_i32_t Register(SQLSnapshot *s);
	void UpdateSnapshot(pctSQLS sqls);
	void AddFetch(dh_boolean idx_only);
};

/**************************************************************************\
 * class SQLSnapshot                                                      *
 * this is a generic container for snapshot we collect in the SQL code    *
 * this class is thread safe                                              *
\**************************************************************************/
class SQLSnapshot
{
private:
	void *StatisticList;
	void *mutex;
public:
	SQLSnapshot(void);
	~SQLSnapshot(void);
	dh_i32_t Init(void);
	dh_i32_t Register(SQLBaseStat *);
	dh_i32_t UnRegister(SQLBaseStat *);
	void UpdateSnapshot(pctSQLS sqls);
	void UpdateSingleSnapshot(pctSQLS sqls, SQLBaseStat *item);
};

#endif

#endif /*__STUB_STA_INCLUDED*/