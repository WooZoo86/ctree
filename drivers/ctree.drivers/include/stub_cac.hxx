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

class stub_rss_env_t; /*foreward declaration*/

class CCacheItem
{
	// constructor & destructor
	public:
		CCacheItem(const tableid_t &uid, CTHANDLE hTable, CTHANDLE hRecord, CTBOOL excl);
		virtual ~CCacheItem();
		
	// Methods
	public:
		CCacheItem* GetNext()
			{return m_next;}
		CCacheItem* GetPrev()
			{return m_prev;}
		tableid_t *GetUid()
			{return &m_uid;}
		CTHANDLE GetTable()
			{return m_hTable;}
		CTHANDLE GetRecord()
			{return m_hRecord;}
		ULONG GetCounter()
			{return m_counter;}
#ifdef ctSQL_OLD_LRU
		clock_t GetTimer()
			{return m_timer;}
#endif
		CTBOOL IsExclusive(tagCTDB* ctreedb)
			{return (ctreedb->GetTableOpenMode(m_hTable) & CTOPEN_EXCLUSIVE)? YES : NO;}
#ifdef PAOLO_REMOVED190213
		void SetExclusive(CTBOOL flag)
			{m_excl = flag;}
		CTBOOL GetExclusive()
			{return m_excl;}
#endif
		
		void SetNext(CCacheItem* ptr)
			{m_next = ptr;}
		void SetPrev(CCacheItem* ptr)
			{m_prev = ptr;}
		void IncrCounter()
			{m_counter += 1;}
		void DecrCounter()
			{if (m_counter) m_counter -= 1;}
#ifdef ctSQL_OLD_LRU
		void TouchTimer()
		{
			m_timer = clock();
#ifdef ctSQL_PRESERVE_CURSOR
			m_recentlyused = 1;
#endif
		}
#endif
#ifdef ctSQL_PRESERVE_CURSOR
		CTBOOL GetRecentlyUsed ()
		{ return m_recentlyused;}
		
		void SetRecentlyUsed (CTBOOL value)
		{ m_recentlyused = value;}
#endif

#ifdef ctSQL_LV_SEC
		CTBOOL get_lv_permission(CTBOOL put)
		{
			if (put)
				return m_lv_put;
			else
				return m_lv_get;
		}
		void set_lv_permission(CTBOOL put, CTBOOL perm)
		{
			if (put)
				m_lv_put = perm;
			else
				m_lv_get = perm;
			return;
		}
#else
		CTBOOL get_lv_permission(CTBOOL put) { return (1);}
		void set_lv_permission(CTBOOL put, CTBOOL perm) {return;}
#endif
		
	// Members
	private:
		CCacheItem*	m_next;
		CCacheItem* m_prev;
		tableid_t	m_uid;
		CTHANDLE	m_hTable;
		CTHANDLE	m_hRecord;
		ULONG		m_counter;
#ifdef ctSQL_OLD_LRU
		clock_t		m_timer;
#endif
#ifdef PAOLO_REMOVED190213
		CTBOOL		m_excl;
#endif
#ifdef ctSQL_PRESERVE_CURSOR
		CTBOOL		m_recentlyused;
#endif
#ifdef ctSQL_LV_SEC
		CTBOOL		m_lv_get;
		CTBOOL		m_lv_put;
#endif
};

#define CACHE_SHRINK_ALL -1
#define CACHE_SHRINK_TO_LEVEL -2

class CCacheTable
{
	// constructor & destructor
	public:
		CCacheTable(stub_rss_env_t * env, ULONG level, tagCTDB* ctreedb);
		virtual ~CCacheTable();
		
	// Methods
	public:
		CTDBRET Clear();
		CTDBRET ClearExclusive();
		CTDBRET Shrink(COUNT items);
		status_t Close(const tableid_t &tableid);
		status_t HardClose(const tableid_t &tableid, bool checklocks);
		status_t Open(const tableid_t &table_id, CTHANDLE& hTable, CTHANDLE& hRecord, CTBOOL force_exc);
#ifdef ctSQL_PRESERVE_CURSOR
		CTDBRET FreeTableLocks (tpe_tm_isolation_lvl_t isolation_level, dh_boolean pvi);
#endif			
		CTBOOL get_lv_permission(const tableid_t &table_id , CTBOOL put);
		void set_lv_permission(const tableid_t &table_id, CTBOOL put, CTBOOL perm);

private:
		void Touch(CCacheItem* ptr);
		void Add(CCacheItem* ptr, CTBOOL tail);
		CTDBRET Add(const tableid_t &table_id, CTHANDLE hTable, CTHANDLE hRecord, CTBOOL excl);
		//CTDBRET Delete(ULONG uid);
		CTDBRET HardClose(CCacheItem* ptr, bool checklocks);
		void Remove(CCacheItem* ptr);
		CCacheItem* Find(const tableid_t &table_id);
#ifdef ctSQL_OLD_LRU
		CCacheItem* LeastUsed();
#endif

	// Members
	private:	
		stub_rss_env_t * m_env;
		CCacheItem*	m_first;
		CCacheItem* m_last;
		CCacheItem* m_last_found;
		ULONG		m_count;
		ULONG		m_inuse;
		ULONG		m_cache_level;
		tagCTDB*    ctreedb;
};

typedef CCacheItem*	pCCacheItem;
typedef CCacheTable* pCCacheTable;