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

#pragma once
#pragma warning(disable : 4482) 

#using <mscorlib.dll>
#using <system.dll>
#using <system.drawing.dll>
#using <system.windows.forms.dll>
using namespace System;
using namespace System::Reflection;
using namespace System::Text;
using namespace System::Runtime::InteropServices;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;


namespace FairCom {

	namespace CtreeDb {

		public __gc class TextToFile 
		{
			static String* FILE_NAME = "ctdbDebugLog.txt";
			StreamWriter* sr;
			static bool opened = false;
/*
			TextToFile()
			{
				sr = new StreamWriter(FILE_NAME);
			}

			~TextToFile()
			{
				Close();
			}
*/
#undef MessageBox
		public:
			void Open()
			{
				try
				{
					if (!File::Exists(FILE_NAME))
					{
						sr = File::CreateText(FILE_NAME);
						sr->WriteLine("c-tree Plus for .NET Debug Log");
						sr->Close();
					}
					sr = File::AppendText(FILE_NAME);
					sr->Write("File Opened: ");
					sr->Write(DateTime::Now.ToShortDateString());
					sr->Write(" ");
					sr->WriteLine(DateTime::Now.ToShortTimeString());
					sr->Flush();
					opened = true;
				}
				catch(Exception* ex)
				{
					MessageBox::Show(ex->Message);
				}
			}

			void Close()
			{
				try
				{
					if(sr && opened)
					{
						sr->Write("File Closed: ");
						sr->Write(DateTime::Now.ToShortDateString());
						sr->Write(" ");
						sr->WriteLine(DateTime::Now.ToShortTimeString());
						sr->WriteLine();
						sr->Close();
						opened = false;
					}
				}
				catch(Exception* ex)
				{
					MessageBox::Show(ex->Message);
				}
			}

			void Write(String* text)
			{
				sr->Write(text);
			}

			void WriteLine(String* text)
			{
				sr->WriteLine(text);
			}
		};

#ifdef plugin
		namespace PluginBase
			{
				public __gc __interface IPlugin
				{

					String* PluginName ();
					
					ToolBar* HideToolBar();
					
					Icon* GetImages();
/*
					void SetPluginMode();

					CTSession* GetSession();

					void ShareSession(CTSession* session);
*/
				};
			}
#endif
		__value public struct ctdbNUMBER
		{
			COUNT	dec_num;
			byte b0;byte b1;byte b2;byte b3;byte b4;
			byte b5;byte b6;byte b7;byte b8;byte b9;
			byte b10;byte b11;byte b12;byte b13;byte b14;
			byte b15;byte b16;
		};

		__value public struct ctdbBLOB
		{
			VRLEN size;
			pUTEXT data;
			VRLEN allocated;
		};

		public __gc class ctdb
		{
		private:
			static CTDBRET ret;
			static LONG debugFlag = 0;
			static TextToFile* debugLog = new TextToFile();
		public:
			
			__value struct IFIL_STRUCT
			{
				String*   pfilnam;
				COUNT	dfilno;	
				UCOUNT	dreclen;
				UCOUNT	dxtdsiz;
				COUNT	dfilmod;
				COUNT	dnumidx;
				UCOUNT	ixtdsiz;
				COUNT	ifilmod;
				pIIDX   ix;		
				String*   rfstfld;
				String*   rlstfld;
				COUNT	tfilno;	
			};

			__value struct IIDX_STRUCT
			{
				COUNT	ikeylen;
				COUNT	ikeytyp;	
				COUNT	ikeydup;	
				COUNT	inulkey;	
				COUNT	iempchr;	
				COUNT	inumseg;	
				pISEG   seg;	
				String* ridxnam;
				String*	aidxnam;
				pCOUNT	altseq;
				pUTEXT	pvbyte;
			};

			__value struct ISEG_STRUCT
			{
				COUNT	soffset;
				COUNT	slength;
				COUNT	segmode;	
			};

			__value struct DATOBJ_STRUCT
			{
				String*   fsymb;
				pTEXT   fadr;	
				UCOUNT	ftype;
				UCOUNT	flen;	
				COUNT	fwhat;
				COUNT	flev;	
				UCOUNT	fhrc;	
				COUNT	frsv;	
				pVOID	fusrp;
				pVOID	frsrv;
			};

			__value enum DEBUG_FLAG
			{
				ALLOC_SESSION = 0x01
			};

			__value enum SESSION_TYPE
			{
				CTDB_SESSION	= CTSESSION_CTDB,
				CTREE_SESSION	= CTSESSION_CTREE,
				SQL_SESSION		= CTSESSION_SQL
			};

			__value enum ATTACH_MODE
			{
				NONE	=	CTATTACH_NONE,
				SESSION	=	CTATTACH_SESSION,
				CTREEID	=	CTATTACH_CTREEID,
				CURRENT	=	CTATTACH_CURRENT
			};

			[Flags]
			__value enum OPEN_MODE
			{
				NORMAL_OPEN		= CTOPEN_NORMAL,
				EXCLUSIVE_OPEN	= CTOPEN_EXCLUSIVE,
				PERMANENT_OPEN	= CTOPEN_PERMANENT,
				CORRUPT_OPEN	= CTOPEN_CORRUPT,
				CHECKLOCK_OPEN	= CTOPEN_CHECKLOCK,
				CHECKREAD_OPEN	= CTOPEN_CHECKREAD,
				READONLY_OPEN	= CTOPEN_READONLY,
				DATAONLY_OPEN	= CTOPEN_DATAONLY
			};
			__value enum SESSION_PARAM
			{
				BUFS	 = CT_BUFS,
				FILS	 = CT_FILS,
				SECT	 = CT_SECT,
				DBUFS	 = CT_DBUFS,
				USERPROF = CT_USERPROF
			}; 
			
			__value enum KEY_TYPE
			{
				FIXED_INDEX	= CTINDEX_FIXED,
				LEADING_INDEX   = CTINDEX_LEADING,
				PADDING_INDEX   = CTINDEX_PADDING,
				LEADPAD_INDEX   = CTINDEX_LEADPAD,
				ERROR_INDEX     = CTINDEX_ERROR
			}; 
				
			__value enum FIELD_TYPE
			{
				BOOL		= CT_BOOL,		
				CHAR		= CT_CHAR,		
				CHARU		= CT_CHARU,	
				INT2		= CT_INT2,
				INT2U		= CT_INT2U,
				INT4		= CT_INT4,
				INT4U		= CT_INT4U,
				MONEY		= CT_MONEY,
				DATE		= CT_DATE,
				TIME		= CT_TIME,
				SFLOAT		= CT_SFLOAT,
				DFLOAT		= CT_DFLOAT,
				TIMES		= CT_TIMES,
				EFLOAT		= CT_EFLOAT,
				ARRAY		= CT_ARRAY,
				FSTRING		= CT_FSTRING,
				FPSTRING	= CT_FPSTRING,
				F2STRING	= CT_F2STRING,
				F4STRING	= CT_F4STRING,
				BIGINT		= CT_INT8,	//CT_BIGINT
				UBIGINT		= CT_INT8U, //CT_UBIGINT
				NUMBER		= CT_NUMBER,
				CURRENCY	= CT_CURRENCY,
				VSTRING		= CT_STRING,
				VPSTRING	= CT_PSTRING,
				V2STRING	= CT_2STRING,
				V4STRING	= CT_4STRING,
#ifdef ctUNICODE
				FUNICODE	= CT_FUNICODE,	
				CTUNICODE	= CT_UNICODE,	
				F2UNICODE	= CT_F2UNICODE,
				V2UNICODE	= CT_2UNICODE,	
#endif
				TINYINT		= CT_TINYINT,		
				UTINYINT	= CT_UTINYINT,	
				SMALLINT	= CT_SMALLINT,
				USMALLINT	= CT_USMALLINT,
				INTEGER		= CT_INTEGER,
				UINTEGER	= CT_UINTEGER,
				FLOAT		= CT_FLOAT,
				DOUBL		= CT_DOUBLE,
				TIMESTAMP	= CT_TIMESTAMP,
				BINARY		= CT_BINARY,
				CHARS		= CT_CHARS,
				VARCHAR		= CT_VARCHAR,
#ifdef ctUNICODE
				NCHAR		= CT_NCHAR,
				NVARCHAR	= CT_NVARCHAR,
#endif
				LVC			= CT_LVC,
				VARBINARY	= CT_VARBINARY,
				LVB			= CT_LVB
				};

			__value enum SEG_MODE
			{
				REGSEG_SEG		= CTSEG_REGSEG,	
				INTSEG_SEG		= CTSEG_INTSEG,	
				UREGSEG_SEG		= CTSEG_UREGSEG,	
				SRLSEG_SEG		= CTSEG_SRLSEG,	
				VARSEG_SEG		= CTSEG_VARSEG,	
				UVARSEG_SEG		= CTSEG_UVARSEG,	
				SGNSEG_SEG		= CTSEG_SGNSEG,
				FLTSEG_SEG		= CTSEG_FLTSEG,	
				DECSEG_SEG		= CTSEG_DECSEG,	
				BCDSEG_SEG		= CTSEG_BCDSEG,	
				SCHSEG_SEG		= CTSEG_SCHSEG,
				USCHSEG_SEG		= CTSEG_USCHSEG,	
				VSCHSEG_SEG		= CTSEG_VSCHSEG,	
				UVSCHSEG_SEG	= CTSEG_UVSCHSEG,	
				DESCENDING_SEG	= CTSEG_DESCENDING,
				ALTSEG_SEG		= CTSEG_ALTSEG,
				ENDSEG_SEG		= CTSEG_ENDSEG,
				SCHSRL_SEG		= CTSEG_SCHSRL,
				INVALID_SEG		= CTSEG_INVALID
			};

			[Flags]
			__value enum CREATE_MODE
			{
				NORMAL_CREATE		= CTCREATE_NORMAL,		
				PREIMG_CREATE		= CTCREATE_PREIMG,
				TRNLOG_CREATE		= CTCREATE_TRNLOG,
				WRITETHRU_CREATE	= CTCREATE_WRITETHRU,
				CHECKLOCK_CREATE	= CTCREATE_CHECKLOCK,
				VRLEN_CREATE		= CTCREATE_VRLEN,
				NORECBYT_CREATE		= CTCREATE_NORECBYT,
				NOROWID_CREATE		= CTCREATE_NOROWID,
				CHECKREAD_CREATE	= CTCREATE_CHECKREAD,	
				HUGEFILE_CREATE		= CTCREATE_HUGEFILE,
				NODELFLD_CREATE		= CTCREATE_NODELFLD,
				NONULFLD_CREATE		= CTCREATE_NONULFLD
			};

			__value enum LOCK_MODE
			{
				FREE_LOCK				= CTLOCK_FREE,				
				READ_LOCK				= CTLOCK_READ,				
				READ_BLOCK_LOCK			= CTLOCK_READ_BLOCK,			
				WRITE_LOCK				= CTLOCK_WRITE,				
				WRITE_BLOCK_LOCK		= CTLOCK_WRITE_BLOCK,			
				RESET_LOCK				= CTLOCK_RESET,				
				SUSPEND_LOCK			= CTLOCK_SUSPEND,				
				RESTORE_READ_LOCK		= CTLOCK_RESTORE_READ,		
				RESTORE_READ_BLOCK_LOCK	= CTLOCK_RESTORE_READ_BLOCK,	
				RESTORE_WRITE_LOCK		= CTLOCK_RESTORE_WRITE,		
				RESTORE_WRITE_BLOCK_LOCK= CTLOCK_RESTORE_WRITE_BLOCK
			};

			__value enum DATE_TYPE
			{
//				DEF_DATE	= CTDATE_DEF,	
				MDCY_DATE	= CTDATE_MDCY,
				MDY_DATE	= CTDATE_MDY,	
				DMCY_DATE	= CTDATE_DMCY,
				DMY_DATE	= CTDATE_DMY,	
				CYMD_DATE	= CTDATE_CYMD,
				YMD_DATE	= CTDATE_YMD	
			};

			__value enum TIME_TYPE
			{
//				DEF_TIME	= CTTIME_DEF,   
				HMSP_TIME	= CTTIME_HMSP,  
				HMP_TIME	= CTTIME_HMP,
				HMS_TIME	= CTTIME_HMS,   
				HM_TIME		= CTTIME_HM,    
				MIL_TIME	= CTTIME_MIL    
			};

			__value enum FIND_MODE
			{
				EQ	= CTFIND_EQ,   
				LT	= CTFIND_LT,   
				LE	= CTFIND_LE,   
				GT	= CTFIND_GT,   
				GE = CTFIND_GE
			};

			__value enum RECBUF_MODE
			{
				AUTO_RECBUF		= CTRECBUF_AUTO,   
				STATIC_RECBUF	= CTRECBUF_STATIC,   
				RAW_RECBUF		= CTRECBUF_RAW   
			};

			[Flags]
			__value enum LIB_TYPE
			{
				SINGLE	= CTLIB_SINGLE,	/* 1 single user             */
				MUSER	= CTLIB_MUSER,	/* 2 multi user              */
				CLIENT	= CTLIB_CLIENT,	/* 4 client                  */
				LOCLIB	= CTLIB_LOCLIB,	/* 8 loclib                  */
				SERVER	= CTLIB_SERVER,	/* 10 server side library    */
				THREA	= CTLIB_THREA,	/* 20 multi thread           */
				TRAN	= CTLIB_TRAN,	/* 40 transaction processing */
				HUGE	= CTLIB_HUGE    /* 80 huge file support      */
			};

			__value enum ALTER_TABLE
			{
				NORMAL	= CTDB_ALTER_NORMAL,
				INDEX	= CTDB_ALTER_INDEX,
				FULL	= CTDB_ALTER_FULL	
			};

			__value enum IDXNO
			{
				RECBYT_NO	= CTDB_RECBYT_IDXNO,
				ROWID_NO	= CTDB_ROWID_IDXNO,
				DATA_NO		= CTDB_DATA_IDXNO
			};

			__value enum KEEP_MODE
			{
				FREE_KEEP	= CTKEEP_FREE,
				LOCK_KEEP	= CTKEEP_LOCK,
				OUT_KEEP	= CTKEEP_OUT,
				OUTALL_KEEP	= CTKEEP_OUTALL
			};

			__value enum RANGE_OP
			{
				EQ		= CTIX_EQ,	
				GT		= CTIX_GT,	
				GE		= CTIX_GE,	
				LE		= CTIX_LE,	
				LT		= CTIX_LT,	
				NE		= CTIX_NE,	
				BET		= CTIX_BET,	
				BET_IE	= CTIX_BET_IE,
				BET_EI	= CTIX_BET_EI,
				BET_EE	= CTIX_BET_EE,
				NOTBET	= CTIX_NOTBET
			};

			__value enum TABLE_PERMS
			{
				O_READ		= OPF_READ,
				O_WRITE		= OPF_WRITE,
				O_DEF		= OPF_DEF,
				O_DELETE	= OPF_DELETE,
				O_ALL		= OPF_ALL,
				O_NOPASS	= OPF_NOPASS,
				G_READ		= GPF_READ,
				G_WRITE		= GPF_WRITE,
				G_DEF		= GPF_DEF,
				G_DELETE	= GPF_DELETE,
				G_ALL		= GPF_ALL,
				G_NOPASS	= GPF_NOPASS,
				W_READ		= WPF_READ,
				W_WRITE		= WPF_WRITE,
				W_DEF		= WPF_DEF,
				W_DELETE	= WPF_DELETE,
				W_ALL		= WPF_ALL,
				W_NOPASS	= WPF_NOPASS
			};

			__value enum USER_PROF
			{
				NTKEY	= USERPRF_NTKEY,
				SAV_ENV	= USERPRF_SAVENV,
				SERIAL	= USERPRF_SERIAL,	
				MEMABS	= USERPRF_MEMABS,	
				NDATA	= USERPRF_NDATA,	
				LOCLIB	= USERPRF_LOCLIB,	
				PTHTMP	= USERPRF_PTHTMP,	
				CODCNV	= USERPRF_CODCNV,	
				CLRCHK	= USERPRF_CLRCHK,
				CUSTOM	= USERPRF_CUSTOM,	
				ENCRYPT	= USERPRF_ENCRYPT,
				ADMSPCL	= USERPRF_ADMSPCL,
				LOGRED	= USERPRF_LOGRED
			};

			__value enum TABLE_TYPE
			{
				NONE			= CTDB_TABLE_NONE,			/* not table handle or table not active */
				SESSION_DICT	= CTDB_TABLE_SESSION_DICT,	/* session dictionary table 			*/
				DATABASE_DICT	= CTDB_TABLE_DATABASE_DICT,	/* database dictionary table 			*/
				SQL_CATALOG		= CTDB_TABLE_SQL_CATALOG,	/* ctreeSQL catalog table 				*/
				USER			= CTDB_TABLE_USER			/* user table 							*/
			};

			__value enum SYS_FILTER
			{
				NONE	= CTSYSFILTER_NONE,			/* indicate no system wide record filter */
				READ	= CTSYSFILTER_READ,			/* indicate a read system wide filter 	 */
				WRITE	= CTSYSFILTER_WRITE			/* indicate a write system wide filter 	 */
			};

			__value enum FIELD_STATUS
			{
				OLD		=	CTDBFIELD_OLD,			/* Original field as read from table */
				NEW		=	CTDBFIELD_NEW,			/* Field added or inserted */
				DEL		=	CTDBFIELD_DEL,			/* Original field deleted */
				MOVED	=	CTDBFIELD_MOVED,		/* Original field moved */
				NAME	=	CTDBFIELD_NAME,			/* Field name changed */
				TYPE	=	CTDBFIELD_TYPE,			/* Field type changed */
				LEN		=	CTDBFIELD_LEN,			/* Field length changed */
				RES		=	CTDBFIELD_RESOURCE		/* Field resource changed */
			};

			__value enum INDEX_STATUS
			{
				OLD		=	CTDBINDEX_OLD,		/* Original value (no changes) */
				NEW		=	CTDBINDEX_NEW,		/* Index added */
				DEL		=	CTDBINDEX_DEL,		/* Original Index deleted */
				KEYTYPE	=	CTDBINDEX_KEYTYPE,	/* Index key type changed */
				EMPCHAR	=	CTDBINDEX_EMPCHAR,	/* Index empty char changed */
				DUPFLAG	=	CTDBINDEX_DUPFLAG,	/* Index duplicate flag changed */
				NULLFLAG=	CTDBINDEX_NULLFLAG,	/* Index null flag changed */
				AIDXNAM	=	CTDBINDEX_AIDXNAM,	/* Index file name changed */
				RIDXNAM	=	CTDBINDEX_RIDXNAM	/* Index symbolic name changed */
			};

			__value enum SEGMENT_STATUS
			{
				OLD		=	CTDBISEG_OLD,		/* Original segment as read from file */
				NEW		=	CTDBISEG_NEW,		/* Segment added or inserted */
				DEL		=	CTDBISEG_DEL,		/* Original segment deleted */
				MOVED	=	CTDBISEG_MOVED,		/* Original segment moved */
				MODE	=	CTDBISEG_MODE,		/* Segment mode changed	 */		
				FIELD	=	CTDBISEG_FIELD		/* Segment field changed	 */		
			};

			__value enum TABLE_STATUS
			{
				REBUILD_NONE	=	CTDB_REBUILD_NONE,		/* Nothing to be done, table is ok	  */
				REBUILD_DODA	=	CTDB_REBUILD_DODA,		/* Update the table doda			  */
				REBUILD_RESOURCE=	CTDB_REBUILD_RESOURCE,	/* Update table FC!DFLD resource      */
				REBUILD_INDEX	=	CTDB_REBUILD_INDEX,		/* Add new indices 					  */
				REBUILD_ALL		=	CTDB_REBUILD_ALL,		/* Rebuild all indices				  */
				REBUILD_FULL	=	CTDB_REBUILD_FULL,		/* Full table rebuild. A temporary	  */
															/* table is created and all data is	  */
															/* moved to new table building 		  */
															/* indices on the fly				  */
			};

			__value enum BATCH_MODE
			{
				NONE			= CTBATCH_NONE,				/* batch is not active				  */  
				GET				= CTBATCH_GET,				/* retrieve records by partial key	  */   
				RANGE			= CTBATCH_RANGE,			/* retrieve records by index range	  */       
				PHYS			= CTBATCH_PHYS,				/* retrieve records by physical order */       
				DEL				= CTBATCH_DEL,				/* delete group of related records	  */   
				INS				= CTBATCH_INS,				/* insert a group of records		  */   
				MANDATORY		= CTBATCH_MANDATORY,		/* mask for mandatory modes			  */
				GKEY			= CTBATCH_GKEY,				/* process records >= target key	  */                
				LKEY			= CTBATCH_LKEY,				/* process records <= target key	  */       
				VERIFY			= CTBATCH_VERIFY,			/* verify target keys				  */       
				LOCK_KEEP		= CTBATCH_LOCK_KEEP,		/* keep locks after ctdbBatchEnd	  */       
				LOCK_READ		= CTBATCH_LOCK_READ,		/* apply read locks					  */
				LOCK_WRITE		= CTBATCH_LOCK_WRITE,		/* apply write locks				  */       
				LOCK_BLOCK		= CTBATCH_LOCK_BLOCK,		/* locks should block				  */       
				LOCK_ONE		= CTBATCH_LOCK_ONE,			/* lock on during read				  */       
				LOCK_COMPLETE	= CTBATCH_COMPLETE			/* return success only if all locked  */       
			};

			__value enum BEGIN_MODE
			{
				NONE_BEGIN		= CTBEGIN_NONE,		/* No begin transaction mode set. Apply 	*/
													/* default begin transaction mode			*/

				PREIMG_BEGIN	= CTBEGIN_PREIMG,	/* Transaction atomicity only. Auto-recovery*/
													/* is not availabe. Mutually exclusive with	*/
													/* CTBEGIN_TRNLOG.							*/

				TRNLOG_BEGIN	= CTBEGIN_TRNLOG,	/* Full transaction processing functionality*/
													/* including auto-recovery. Mutually 		*/
													/* exclusive to CTBEGIN_PREIMG. This is the	*/
													/* default begin transaction mode.			*/
	
				DEFER_BEGIN		= CTBEGIN_DEFER,	/* Defer begin transaction until update		*/

				AUTOSAVE_BEGIN	= CTBEGIN_AUTOSAVE	/* Automatically invokes savepoints after	*/
													/* each successful record or resource update*/
			};

			__value enum REBUILD_MODE
			{
				NONE		= CTREBUILD_NONE,			/* normal rebuild mode					*/        
				PURGEDUP	= CTREBUILD_PURGEDUP,		/* purge duplicate records				*/
				UPDATEIFIL	= CTREBUILD_UPDATEIFIL,		/* update table IFIL structure			*/
				DATAONLY	= CTREBUILD_DATAONLY 		/* rebuild only the data file			*/
			};

			[Flags]
			__value enum OPS_STATE
			{
				OFF		=	OPS_STATE_OFF,	// 0x00000000 - Turn a status bit off.
				SET		=	OPS_STATE_SET,	// 0x00000001 - Set the entire status word.
				ON		=	OPS_STATE_ON,	// 0x00000002 -	Turn a status bit on.
				RET		=	OPS_STATE_RET	// 0x00000003 - Return the entire status word.
				//VRET	=	OPS_STATE_VRET	// 0x00000004
			};

			[Flags]
			__value enum OPS_MODE
			{
				LOCKON_GET		=	OPS_LOCKON_GET, 	//	Lock next fetch only.
				UNLOCK_ADD		=	OPS_UNLOCK_ADD,		//	Automatic unlock on add.
				UNLOCK_RWT		=	OPS_UNLOCK_RWT, 	//	Automatic unlock on rewrite.
				UNLOCK_UPD		=	OPS_UNLOCK_UPD, 	//	(OPS_UNLOCK_ADD | OPS_UNLOCK_RWT)
				LOCKON_BLK		=	OPS_LOCKON_BLK,		//	Blocking lock on next fetch only.
				FUNCTION_MON	=	OPS_FUNCTION_MON, 	//  Toggle function monitor. (Server)
				LOCK_MON		=	OPS_LOCK_MON,		//	Toggle lock monitor. (Server)
				TRACK_MON		=	OPS_TRACK_MON, 		//	Toggle memory track monitor. (Server)
				MIRROR_NOSWITCH	=	OPS_MIRROR_NOSWITCH,//  Don't continue if mirror or primary fails. (Server)
				MIRROR_TRM		=	OPS_MIRROR_TRM,		//	A primary or mirror has been shutdown.
				MEMORY_SWP		=	OPS_MEMORY_SWP,		//	Memory swapping active.
				AUTOISAM_TRN	=	OPS_AUTOISAM_TRN, 	//	Automatic ISAM transactions.
				COMMIT_SWP		=	OPS_COMMIT_SWP,		//	Auto commit on swap occurred.
				SERIAL_UPD		=	OPS_SERIAL_UPD,		//	Changes GetSerialNbr operation.
				DEFER_CLOSE		=	OPS_DEFER_CLOSE, 	//	Defer file closes or deletes during transactions.
				DISK_IO			=	OPS_DISK_IO 		//	Set sysiocod on disk reads and writes.
			};

		private:

			static void CTN2ctN(CTNUMBER* N, ctdbNUMBER* n)
			{
				n->dec_num = N->dec_num;
				n->b0 = N->dec_digits[0];n->b1 = N->dec_digits[1];n->b2 = N->dec_digits[2];
				n->b3 = N->dec_digits[3];n->b4 = N->dec_digits[4];n->b5 = N->dec_digits[5];
				n->b6 = N->dec_digits[6];n->b7 = N->dec_digits[7];n->b8 = N->dec_digits[8];
				n->b9 = N->dec_digits[9];n->b10 = N->dec_digits[10];n->b11 = N->dec_digits[11];
				n->b12 = N->dec_digits[12];n->b13 = N->dec_digits[13];n->b14 = N->dec_digits[14];
				n->b15 = N->dec_digits[15];n->b16 = N->dec_digits[16];
			}
			static void ctN2CTN(ctdbNUMBER* n, CTNUMBER* N)
			{
				N->dec_num = n->dec_num ;
				N->dec_digits[0] = n->b0;N->dec_digits[1] = n->b1;N->dec_digits[2] = n->b2;
				N->dec_digits[3] = n->b3;N->dec_digits[4] = n->b4;N->dec_digits[5] = n->b5;
				N->dec_digits[6] = n->b6;N->dec_digits[7] = n->b7;N->dec_digits[8] = n->b8;
				N->dec_digits[9] = n->b9;N->dec_digits[10] = n->b10;N->dec_digits[11] = n->b11;
				N->dec_digits[12] = n->b12;N->dec_digits[13] = n->b13;N->dec_digits[14] = n->b14;
				N->dec_digits[15] = n->b15;N->dec_digits[16] = n->b16;
			}

		public:

			static int SystemLogWrite(COUNT EvClass, LONG Event, String* Buffer)
			{
				int buflen = Buffer->Length > SYSLOGvar ? SYSLOGvar : Buffer->Length + 1;
				char __pin * dbuf = new char[buflen];
				memset(dbuf,0,buflen);
				IntPtr sbuf = Marshal::StringToHGlobalAnsi(Buffer);
				memcpy(dbuf,(pTEXT)sbuf.ToPointer(),buflen);
				int ret = SYSLOG(EvClass, Event, dbuf, buflen);
				Marshal::FreeHGlobal(sbuf);
				delete[] dbuf;
				return ret;
			}

			static NINT ThrdInit(NINT NumThreads, LONG Mode)
			{
#ifdef ctPortNATIVE_THREADS
				return ctThrdInit(NumThreads, Mode, NULL);
#else
				return 0;
#endif
			}

			static NINT ThrdAttach()
			{
#ifdef ctPortNATIVE_THREADS
				return ctThrdAttach();
#else
				return 0;
#endif
			}

			static NINT ThrdDetach()
			{
#ifdef ctPortNATIVE_THREADS
				return ctThrdDetach();
#else
				return 0;
#endif
			}

			static void SetDebugFlag(LONG Level)
			{
				debugFlag = Level;
				if (debugFlag != 0)
					debugLog->Open();
				else
					debugLog->Close();
			}

			static CTDBRET Abort(IntPtr Session)
			{
				return ctdbAbort((CTHANDLE)Session);
			}

			static CTDBRET AddDatabase(IntPtr Session, String* Name, String* Path)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				IntPtr path = Marshal::StringToHGlobalAnsi(Path);
				ret = ctdbAddDatabase((CTHANDLE)Session, (pTEXT)name.ToPointer(),(pTEXT)path.ToPointer());
				Marshal::FreeHGlobal(name);
				Marshal::FreeHGlobal(path);
				return ret;
			}

			static IntPtr AddField(IntPtr Table, String* Name, FIELD_TYPE Type, VRLEN Length)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				CTHANDLE pField = ctdbAddField((CTHANDLE)Table, (pTEXT)name.ToPointer(), (CTDBTYPE)Type, Length);
				Marshal::FreeHGlobal(name);
				return pField;
			}

			static IntPtr AddIndex(IntPtr Table, String* Name, KEY_TYPE KeyType, bool AllowDuplicates, bool NullFlag)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				CTHANDLE pIndex = ctdbAddIndex((CTHANDLE)Table, (pTEXT)name.ToPointer(), (CTDBKEY)KeyType, AllowDuplicates, NullFlag);
				Marshal::FreeHGlobal(name);
				return pIndex;
			}

			static CTDBRET AddResource(IntPtr resource, Byte data __gc[])
			{
				long size = data->Length;
				GCHandle gch = GCHandle::Alloc( data, GCHandleType::Pinned);
				ret = ctdbAddResource((CTHANDLE)resource, gch.AddrOfPinnedObject().ToPointer(), size);
				gch.Free();
				return ret;
			}

			static IntPtr AddSegment(IntPtr Index, IntPtr FieldHandle, SEG_MODE SegMode)
			{
				return ctdbAddSegment((CTHANDLE) Index, (CTHANDLE) FieldHandle, (CTSEG_MODE)SegMode);
			}

			static IntPtr AddSegmentByName(IntPtr Table, NINT IndexNbr, String* FieldName, SEG_MODE SegMode)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(FieldName);
				IntPtr ret = ctdbAddSegmentByName((CTHANDLE) Table, IndexNbr, (pTEXT)name.ToPointer(), (CTSEG_MODE) SegMode);
				Marshal::FreeHGlobal(name);
				return ret;
			}

			
			static IntPtr AddSegmentByNbr(IntPtr Table, NINT IndexNbr, NINT FieldNbr, SEG_MODE SegMode)
			{
				return ctdbAddSegmentByNbr((CTHANDLE) Table, IndexNbr, FieldNbr, (CTSEG_MODE) SegMode);
			}

			static IntPtr AddSegmentEx(IntPtr Index, NINT Offset, NINT Length, SEG_MODE SegMode)
			{
				return ctdbAddSegmentEx((CTHANDLE) Index, Offset, Length, (CTSEG_MODE)SegMode);
			}

			static CTDBRET AddTable(IntPtr Database, String* Name, String* Path)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				IntPtr path = Marshal::StringToHGlobalAnsi(Path);
				ret = ctdbAddTable((CTHANDLE)Database, (pTEXT)name.ToPointer(),(pTEXT)path.ToPointer());
				Marshal::FreeHGlobal(name);
				Marshal::FreeHGlobal(path);
				return ret;
			}

			static IntPtr AllocDatabase(IntPtr Session)
			{
				return ctdbAllocDatabase((CTHANDLE)Session);
			}

			static IntPtr AllocRecord(IntPtr Table)
			{
				return ctdbAllocRecord((CTHANDLE)Table);
			}

			static IntPtr AllocResource(IntPtr Table, ULONG type, ULONG number, String* Name)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				IntPtr handle = ctdbAllocResource((CTHANDLE) Table, type, number, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return handle;
			}

			static IntPtr AllocSession(SESSION_TYPE Type)
			{
				Init();
				return ctdbAllocSession((CTSESSION_TYPE)Type);
			}

			static IntPtr AllocTable(IntPtr Database)
			{
				return ctdbAllocTable((CTHANDLE)Database);
			}

			static CTDBRET AlterTable(IntPtr Table, NINT Action)
			{
				return ctdbAlterTable((CTHANDLE) Table, Action);
			}

			static CTDBRET AttachSession(IntPtr Handle, IntPtr Session, ATTACH_MODE mode, bool isTransactionActive)
			{
				return ctdbAttachSession((CTHANDLE) Handle, (CTHANDLE) Session, (CTATTACH_MODE)mode, isTransactionActive);
			}
			
			static CTDBRET AttachSession(IntPtr Handle, String* CtreeId, ATTACH_MODE mode, bool isTransactionActive)
			{
				IntPtr ctreeid = Marshal::StringToHGlobalAnsi(CtreeId);
				ret = ctdbAttachSession((CTHANDLE) Handle, (pTEXT)ctreeid.ToPointer(), (CTATTACH_MODE)mode, isTransactionActive);
				Marshal::FreeHGlobal(ctreeid);
				return ret;
			}

			static CTDBRET AttachTable(IntPtr Table, NINT Datno)
			{
				return ctdbAttachTable((CTHANDLE) Table, Datno);
			}

			static LONG BatchLoaded(IntPtr Record)
			{
				return ctdbBatchLoaded((CTHANDLE) Record);
			}

			static LONG BatchLocked(IntPtr Record) 
			{
				return ctdbBatchLocked((CTHANDLE) Record);
			}

			static LONG BatchTotal(IntPtr Record) 
			{
				return ctdbBatchTotal((CTHANDLE) Record);
			}

			static CTBATCH_MODE BatchMode(IntPtr Record) 
			{
				return ctdbBatchMode((CTHANDLE) Record);
			}

			static bool IsBatchActive(IntPtr Record) 
			{
				return ctdbIsBatchActive((CTHANDLE) Record);
			}

			static CTDBRET EndBatch(IntPtr Record)
			{
				return ctdbEndBatch((CTHANDLE) Record);
			}

			static CTDBRET InsertBatch(IntPtr Record)
			{
				return ctdbInsertBatch((CTHANDLE) Record);
			}

			static CTDBRET NextBatch(IntPtr Record)
			{
				return ctdbNextBatch((CTHANDLE) Record);
			}

			static CTDBRET SetBatch(IntPtr Record, CTBATCH_MODE mode, VRLEN targetLen, VRLEN bufferLen)
			{
				return ctdbSetBatch((CTHANDLE) Record, mode, targetLen, bufferLen);
			}

			static CTDBRET Begin(IntPtr Session)
			{
				return ctdbBegin((CTHANDLE)Session);
			}

			static CTDBRET BigIntToCurrency(CTBIGINT Bigint, [Out] CTCURRENCY __gc* Currency)
			{
				CTCURRENCY cur;
				ret = ctdbBigIntToCurrency(Bigint, &cur);
				*Currency = cur;
				return ret;
			}

			static CTDBRET BigIntToFloat(CTBIGINT Bigint, [Out] float __gc* Float)
			{
				CTFLOAT val;
				ret = ctdbBigIntToFloat(Bigint, &val);
				*Float = (float)val;
				return ret;
			}

			static CTDBRET BigIntToLong(CTBIGINT Bigint, [Out] __int64 __gc* Long)
			{
				LONG val;
				ret = ctdbBigIntToLong(Bigint, &val);
				*Long = val;
				return ret;
			}

			static CTDBRET BigIntToNumber(CTBIGINT Bigint, [Out]ctdbNUMBER __gc *Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ret = ctdbBigIntToNumber(Bigint, num);
				CTN2ctN(num,Number);
				return ret;
			}

			static CTDBRET BigIntToString(CTBIGINT Bigint, StringBuilder* Buffer, VRLEN BufferSize)
			{
				char __pin * buf = new char[BufferSize];
				memset(buf,0,BufferSize);
				ret = ctdbBigIntToString(Bigint, buf, BufferSize);
				Buffer->Length = 0;
				if (!ret)
				{
					Buffer->Insert(0,buf);
				}
				delete[] buf;
				return ret;
			}

			static ctdbBLOB BlobAlloc(VRLEN Size)
			{
				CTBLOB __pin * pBLOB = new CTBLOB;
				ctdbBLOB blob;
				pBLOB = ctdbBlobAlloc(Size);
				blob.size = pBLOB->size;
				blob.data = pBLOB->data;
				blob.allocated = pBLOB->allocated;
				return blob;
			}

			static CTDBRET BlobClear([Out]ctdbBLOB __gc* pBlob)
			{
				CTBLOB __pin * pBLOB = new CTBLOB;
				pBLOB->size = pBlob->size;
				pBLOB->data = pBlob->data;
				pBLOB->allocated = pBlob->allocated;
				ret = ctdbBlobClear(pBLOB);
				pBlob->size = pBLOB->size;
				pBlob->data = pBLOB->data;
				pBlob->allocated = pBLOB->allocated;

				return ret;
			}

			static NINT BlobCmp(ctdbBLOB Left, ctdbBLOB Right)
			{
				CTBLOB __pin * pBLOB = new CTBLOB;
				pBLOB->size = Left.size;
				pBLOB->data = Left.data;
				pBLOB->allocated = Left.allocated;
				CTBLOB __pin * pBLOB2 = new CTBLOB;
				pBLOB2->size = Right.size;
				pBLOB2->data = Right.data;
				pBLOB2->allocated = Right.allocated;
				return ctdbBlobCmp(pBLOB, pBLOB2);
			}

			static VOID BlobFree([Out]ctdbBLOB __gc* pBlob)
			{
				CTBLOB __pin * pBLOB = new CTBLOB;
				pBLOB->size = pBlob->size;
				pBLOB->data = pBlob->data;
				pBLOB->allocated = pBlob->allocated;
				ctdbBlobFree(pBLOB);
				pBlob->size = 0;
				pBlob->data = 0;
				pBlob->allocated = 0;
			}

			static IntPtr BlobGetData(ctdbBLOB Blob)
			{
				return Blob.data;
			}

			static VRLEN BlobGetSize(ctdbBLOB Blob)
			{
				return Blob.size;
			}

			static CTDBRET BlobSet([Out]ctdbBLOB __gc* Blob, IntPtr data, VRLEN size)
			{
				CTBLOB __pin * pBLOB = new CTBLOB;
				pBLOB->size = Blob->size;
				pBLOB->data = Blob->data;
				pBLOB->allocated = Blob->allocated;
				ret = ctdbBlobSet(pBLOB,(void*)data,size);
				Blob->size = pBLOB->size;
				Blob->data = pBLOB->data;
				Blob->allocated = pBLOB->allocated;
				return ret;
			}

			static CTDBRET BuildTargetKey(IntPtr Record, FIND_MODE FindMode, IntPtr Target, [In][Out]VRLEN __gc* TargetLen)
			{
				VRLEN len = *TargetLen;
				ret = ctdbBuildTargetKey((CTHANDLE) Record, (CTFIND_MODE) FindMode, (pVOID) Target, &len);
				*TargetLen = len;
				return ret;
			}

			static CTDBRET ClearAllFieldDefaultValue(IntPtr Table)
			{
				return ctdbClearAllFieldDefaultValue((CTHANDLE)Table);
			}

			static CTDBRET ClearFieldDefaultValue(IntPtr Field)
			{
				return ctdbClearFieldDefaultValue((CTHANDLE)Field);
			}

			static void ClearError(IntPtr Handle)
			{
				ctdbClearError((CTHANDLE)Handle);
			}
			
			static CTDBRET ClearField(IntPtr Record, NINT FieldNbr)
			{
				return ctdbClearField((CTHANDLE)Record, FieldNbr);
			}

			static CTDBRET ClearPathPrefix(IntPtr Handle)
			{
				return ctdbClearPathPrefix((CTHANDLE)Handle);
			}

			static CTDBRET ClearRecord(IntPtr Record)
			{
				return ctdbClearRecord((CTHANDLE)Record);
			}

			static CTDBRET CloseAll(IntPtr Database)
			{
				return ctdbCloseAll((CTHANDLE)Database);
			}

			static CTDBRET CloseTable(IntPtr Table)
			{
				return ctdbCloseTable((CTHANDLE)Table);
			}
			
			static CTDBRET CndxCompile(IntPtr Record, String* Expression)
			{
				IntPtr expr = Marshal::StringToHGlobalAnsi(Expression);
				ret = ctdbCndxCompile((CTHANDLE) Record, (pTEXT)expr.ToPointer());
				Marshal::FreeHGlobal(expr);
				return ret;
			}

			static String* CndxGetExpression(IntPtr Record)
			{
				return ctdbCndxGetExpression((CTHANDLE) Record);
			}

			static CTDBRET CndxEval(IntPtr Record)
			{
				return ctdbCndxEval((CTHANDLE) Record);
			}

			static CTDBRET CndxFree(IntPtr Record)
			{
				return ctdbCndxFree((CTHANDLE) Record);
			}

			static CTDBRET Commit(IntPtr Session)
			{
				return ctdbCommit((CTHANDLE)Session);
			}

			static CTDBRET CompareRecords(IntPtr Record1, IntPtr Record2)
			{
    			return ctdbCompareRecords((CTHANDLE)Record1,(CTHANDLE)Record2);
			}

			static CTDBRET Connect(IntPtr Database, String* Name)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				ret = ctdbConnect((CTHANDLE)Database,(pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET CopyRecordBuffer(IntPtr Source, IntPtr Dest)
			{
				return ctdbCopyRecordBuffer((CTHANDLE)Source, (CTHANDLE)Dest);
			}

			static CTDBRET CreateDatabase(IntPtr Session, String* Name, String* Path)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				IntPtr path = Marshal::StringToHGlobalAnsi(Path);
				ret = ctdbCreateDatabase((CTHANDLE)Session, (pTEXT)name.ToPointer(), (pTEXT)path.ToPointer());
				Marshal::FreeHGlobal(path);
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET CreateSession(IntPtr Session, String* DbEngine, String* UserId, String* Password)
			{
				IntPtr db = Marshal::StringToHGlobalAnsi(DbEngine);
				IntPtr user = Marshal::StringToHGlobalAnsi(UserId);
				IntPtr pass = Marshal::StringToHGlobalAnsi(Password);
				ret = ctdbCreateSession((CTHANDLE)Session,(pTEXT)db.ToPointer(),(pTEXT)user.ToPointer(),(pTEXT)pass.ToPointer());
				Marshal::FreeHGlobal(pass);
				Marshal::FreeHGlobal(user);
				Marshal::FreeHGlobal(db);
				return ret;
			}

			static CTDBRET CreateTable(IntPtr Table,String* Name, CREATE_MODE CreateMode)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				ret = ctdbCreateTable((CTHANDLE)Table, (pTEXT)name.ToPointer(), (CTCREATE_MODE)CreateMode);
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTCURRENCY CurrencyAbs (CTCURRENCY Currency)
			{
				return ctdbCurrencyAbs(Currency);
			}

			static CTDBRET CurrencyAdd(CTCURRENCY Left, CTCURRENCY Right, [Out] CTCURRENCY __gc* Result)
			{
				CTCURRENCY res;
                ret = ctdbCurrencyAdd(Left, Right, &res);
				*Result = res;
				return ret;
			}

			static CTDBRET CurrencyDiv(CTCURRENCY Left, CTCURRENCY Right, [Out] CTCURRENCY __gc* Result)
			{
				CTCURRENCY res;
                ret = ctdbCurrencyDiv(Left, Right, &res);
				*Result = res;
				return ret;
			}

			static CTDBRET CurrencyMul(CTCURRENCY Left, CTCURRENCY Right, [Out] CTCURRENCY __gc* Result)
			{
				CTCURRENCY res;
                ret = ctdbCurrencyMul(Left, Right, &res);
				*Result = res;
				return ret;
			}

			static CTDBRET CurrencyToBigInt(CTCURRENCY Currency, [Out] CTBIGINT __gc* BigInt)
			{
				CTBIGINT val;
				ret = ctdbCurrencyToBigInt(Currency, &val);
				*BigInt = val;
				return ret;
			}

			static CTDBRET CurrencyToFloat(CTCURRENCY Currency, [Out] float __gc * Float)
			{
				CTFLOAT val;
				ret = ctdbCurrencyToFloat(Currency, &val);
				*Float = (float)val;
				return ret;
			}
			
			static CTDBRET CurrencyToLong(CTCURRENCY Currency, [Out] __int64 __gc* Long)
			{
				CTSIGNED val;
				ret = ctdbCurrencyToLong(Currency, &val);
				*Long = val;
				return ret;
			}

			static CTDBRET CurrencyToMoney(CTCURRENCY Currency, [Out] CTMONEY __gc* Money)
			{
				CTMONEY val;
				ret = ctdbCurrencyToMoney(Currency, &val);
				*Money = val;
				return ret;
			}

			static CTDBRET CurrencyToNumber(CTCURRENCY Currency, [Out]ctdbNUMBER __gc *Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ret = ctdbCurrencyToNumber(Currency, num);
				CTN2ctN(num,Number);
				return ret;
			}

			static CTDBRET CurrencyToString(CTCURRENCY Currency, StringBuilder* Buffer, VRLEN BufferSize)
			{
				char __pin * buf = new char[BufferSize];
				memset(buf,0,BufferSize);
				ret = ctdbCurrencyToString(Currency, buf, BufferSize);
				Buffer->Length = 0;
				if (!ret)
				{
					Buffer->Insert(0,buf);
				}
				delete[] buf;
				return ret;
			}

			static CTDBRET CurrencyRound(CTCURRENCY __gc* Currency, NINT Scale)
			{
				CTCURRENCY cur = *Currency;
				ret = ctdbCurrencyRound(&cur, Scale);
				*Currency = cur;
				return ret;
			}

			static CTDBRET CurrencySub(CTCURRENCY Left, CTCURRENCY Right, [Out] CTCURRENCY __gc* Result)
			{
				CTCURRENCY res;
                ret = ctdbCurrencySub(Left, Right, &res);
				*Result = res;
				return ret;
			}

			static NINT CurrencyCmp(CTCURRENCY Left, CTCURRENCY Right)
			{
				return ctdbCurrencyCmp(Left, Right);
			}

			static CTDBRET CurrentDate([Out]CTDATE __gc* Date)
			{
				CTDATE date;
			    ret = ctdbCurrentDate(&date);
				*Date = date;
				return ret;
			}

		    static CTDBRET CurrentDateTime([Out]CTDATETIME __gc* DateTime)
			{
				CTDATETIME datetime;
				ret = ctdbCurrentDateTime(&datetime);
				*DateTime = datetime;
				return ret;
			}

			static CTDBRET CurrentTime([Out]CTTIME __gc* Time)
			{
				CTTIME time;
			    ret = ctdbCurrentTime(&time);
				*Time = time;
				return ret;
			}

			static CTDBRET DateCheck(NINT Year, NINT Month, NINT Day)
			{
				return ctdbDateCheck(Year, Month, Day);
			}

			static CTDBRET DatePack([Out]CTDATE __gc * Date, NINT Year, NINT Month, NINT Day)
			{
				CTDATE date;
				ret = ctdbDatePack(&date, Year, Month, Day);
				*Date = date;
				return ret;
			}

			static CTDBRET DateTimeGetDate(CTDATETIME DateTime, [Out]CTDATE __gc* Date)
			{
				CTDATE date;
				ret = ctdbDateTimeGetDate(DateTime, &date);
				*Date = date;
				return ret;
			}

			static CTDBRET DateTimeGetTime(CTDATETIME DateTime, [Out]CTTIME __gc* Time)
			{
				CTTIME time;
				ret = ctdbDateTimeGetTime(DateTime, &time);
				*Time = time;
				return ret;
			}

			static CTDBRET DateTimeSetDate(CTDATETIME __gc* DateTime, CTDATE Date)
			{
				CTDATETIME datetime = *DateTime;
				ret = ctdbDateTimeSetDate(&datetime, Date);
				*DateTime = datetime;
				return ret;
			}

			static CTDBRET DateTimeSetTime(CTDATETIME __gc* DateTime, CTTIME Time)
			{
				CTDATETIME datetime = *DateTime;
				ret = ctdbDateTimeSetTime(&datetime, Time);
				*DateTime = datetime;
				return ret;
			}

			static CTDBRET DateTimePack([Out]CTDATETIME __gc * DateTime, NINT Year, NINT Month, NINT Day, NINT Hour, NINT Minute, NINT Second)
			{
				CTDATETIME datetime;
				ret = ctdbDateTimePack(&datetime, Year, Month, Day, Hour, Minute, Second);
				*DateTime = datetime;
				return ret;
			}

			static CTDBRET DateTimeToString(CTDATETIME DateTime, DATE_TYPE DateType, TIME_TYPE TimeType, StringBuilder* Buffer, VRLEN BufferSize)
			{
				char __pin * buf = new char[BufferSize];
				memset(buf,0,BufferSize);
				ret = ctdbDateTimeToString(DateTime, (CTDATE_TYPE)DateType, (CTTIME_TYPE)TimeType, buf, BufferSize);
				Buffer->Length = 0;
				if (!ret)
				{
					Buffer->Insert(0,buf);
				}
				delete[] buf;
				return ret;
			}

			static CTDBRET DateTimeUnpack(CTDATETIME DateTime, [Out]NINT __gc * Year, [Out]NINT __gc *Month, [Out]NINT __gc *Day, [Out]NINT __gc * Hour, [Out]NINT __gc *Minute, [Out]NINT __gc *Second)
			{
				NINT y,m,d,H,M,S;
				ret = ctdbDateTimeUnpack(DateTime, &y, &m, &d, &H, &M, &S);
				*Year = y;
				*Month = m;
				*Day = d;
				*Hour = H;
				*Minute = M;
				*Second = S;
				return ret;
			}

			static CTDBRET DateToString(CTDATE Date, DATE_TYPE DateType, StringBuilder* Buffer, VRLEN BufferSize)
			{
				char __pin * buf = new char[BufferSize];
				memset(buf,0,BufferSize);
				ret = ctdbDateToString(Date, (CTDATE_TYPE)DateType, buf, BufferSize);
				Buffer->Length = 0;
				if (!ret)
				{
					Buffer->Insert(0,buf);
				}
				delete[] buf;
				return ret;
			}

			static CTDBRET DateUnpack(CTDATE Date, [Out]NINT __gc * Year, [Out]NINT __gc *Month, [Out]NINT __gc *Day)
			{
				NINT y,m,d;
				ret = ctdbDateUnpack(Date, &y, &m, &d);
				*Year = y;
				*Month = m;
				*Day = d;
				return ret;
			}

			static NINT DayOfWeek(CTDATE Date)
			{
			    return ctdbDayOfWeek(Date);
			}

			static CTDBRET DeleteDatabase(IntPtr Session, String* DatabaseName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(DatabaseName);
				ret = ctdbDeleteDatabase((CTHANDLE)Session,(pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET DeleteRecord(IntPtr Record)
			{
				return ctdbDeleteRecord((CTHANDLE)Record);
			}

			static CTDBRET DeleteResource(IntPtr Res)
			{
				return ctdbDeleteResource((CTHANDLE) Res);
			}

			static CTDBRET DeleteTable(IntPtr Database, String* TableName,String* Password)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(TableName);
				IntPtr pass = Marshal::StringToHGlobalAnsi(Password);
				ret = ctdbDeleteTable((CTHANDLE)Database, (pTEXT)name.ToPointer(), (pTEXT)pass.ToPointer());
				Marshal::FreeHGlobal(name);
				Marshal::FreeHGlobal(pass);
				return ret;
			}

			static CTDBRET DelField(IntPtr Table, NINT FieldNumber)
			{
				return ctdbDelField((CTHANDLE)Table, FieldNumber);
			}

			static CTDBRET DelFieldByName(IntPtr Table, String* FieldName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(FieldName);
				ret = ctdbDelFieldByName((CTHANDLE)Table, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET DelIndex(IntPtr Table, NINT IndexNumber)
			{
				return ctdbDelIndex((CTHANDLE)Table, IndexNumber);
			}

			static CTDBRET DelSegment(IntPtr Index, NINT SegmentNumber)
			{
			   return ctdbDelSegment((CTHANDLE)Index, SegmentNumber);
			}
			
			static CTDBRET DelSegmentEx(IntPtr Segment)
			{
				return ctdbDelSegmentEx((CTHANDLE) Segment);
			}

			static CTDBRET DetachTable(IntPtr Table)
			{
				return ctdbDetachTable((CTHANDLE)Table);
			}

			static CTDBRET DetachSession(IntPtr Session)
			{
				return ctdbDetachSession((CTHANDLE)Session);
			}

			static CTDBRET Disconnect(IntPtr Database)
			{
				return ctdbDisconnect((CTHANDLE)Database);
			}

			static CTDBRET DisconnectAll(IntPtr Session)
			{
				return ctdbDisconnectAll((CTHANDLE)Session);
			}

			static CTDBRET DropDatabase(IntPtr Session,String* DatabaseName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(DatabaseName);
				ret = ctdbDropDatabase((CTHANDLE)Session, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET DropTable(IntPtr Database,String* TableName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(TableName);
				ret = ctdbDropTable((CTHANDLE)Database, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static IntPtr DuplicateRecord(IntPtr Record)
			{
				return ctdbDuplicateRecord((CTHANDLE)Record);
			}

			static LONG EstimateSpan(IntPtr Handle, Byte Key1 __gc[], Byte Key2 __gc[])
			{
				GCHandle gch1 = GCHandle::Alloc( Key1, GCHandleType::Pinned);
				void* key1 = (pUTEXT)gch1.AddrOfPinnedObject().ToPointer();
				GCHandle gch2 = GCHandle::Alloc( Key2, GCHandleType::Pinned);
				void* key2 = (pUTEXT)gch2.AddrOfPinnedObject().ToPointer();
				LONG ret = ctdbEstimateSpan((CTHANDLE) Handle, (pVOID) key1, (pVOID) key2);
				gch1.Free();
				gch2.Free();
				return ret;
			}

			static CTDBRET FilterRecord(IntPtr Handle, String* FilterExpr)
			{
				IntPtr expr = Marshal::StringToHGlobalAnsi(FilterExpr);
				ret = ctdbFilterRecord((CTHANDLE) Handle, (pTEXT)expr.ToPointer());
				Marshal::FreeHGlobal(expr);
				return ret;
			}

			static CTDBRET FindDatabase(IntPtr Session, String* Name, StringBuilder* Path, VRLEN PathSize)
			{
				char __pin * pPath = new char[PathSize];
				memset(pPath,0,PathSize);
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				ret = ctdbFindDatabase((CTHANDLE)Session, (pTEXT)name.ToPointer(), pPath, PathSize);
				Marshal::FreeHGlobal(name);
				Path->Length = 0;
				if (!ret)
				{
					Path->Insert(0,pPath);
				}
				delete[] pPath;
				return ret;
			}

			static CTDBRET FindDatabaseByUID(IntPtr Session, [In]unsigned __int64 Uid, StringBuilder* Name, VRLEN NameSize, StringBuilder* Path, VRLEN PathSize)
			{
		        char __pin * pName = new char[NameSize];
				memset(pName,0,NameSize);
				char __pin * pPath = new char[PathSize];
				memset(pPath,0,PathSize);
				ret = ctdbFindDatabaseByUID((CTHANDLE)Session, Uid, pName, NameSize, pPath, PathSize);
				Name->Length = 0;
				Path->Length = 0;
				if (!ret)
				{
					Name->Insert(0,pName);
					Path->Insert(0,pPath);
				}
				delete[] pName;
				delete[] pPath;
				return ret;
			}

			static CTDBRET FindRecord(IntPtr Record, FIND_MODE FindMode)
			{
				return ctdbFindRecord((CTHANDLE)Record, (CTFIND_MODE)FindMode);
			}

			static CTDBRET FindResource(IntPtr Resource, ULONG Type, ULONG Number, bool Lock)
			{
				return ctdbFindResource((CTHANDLE) Resource, Type, Number, Lock);
			}

			static CTDBRET FindResourceByName(IntPtr Resource, String* Name, bool Lock)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				ret = ctdbFindResourceByName((CTHANDLE) Resource, (pTEXT)name.ToPointer(), Lock);
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET FindRowid(IntPtr Record, __int64 Rowid, FIND_MODE FindMode)
			{
				return ctdbFindRowid((CTHANDLE)Record, Rowid, (CTFIND_MODE)FindMode);
			}

			static CTDBRET FindTable(IntPtr Database, String* Name, StringBuilder* Path, VRLEN PathSize)
			{
				char __pin * pPath = new char[PathSize];
				memset(pPath,0,PathSize);
				IntPtr pName = Marshal::StringToHGlobalAnsi(Name);
				ret = ctdbFindTable((CTHANDLE)Database, (pTEXT)pName.ToPointer(), pPath, PathSize);
				Marshal::FreeHGlobal(pName);
				Path->Length = 0;
				if (!ret)
				{
					Path->Insert(0,pPath);
				}
				delete[] pPath;
				return ret;
			}

			static CTDBRET FindTableByUID(IntPtr Database, [In]unsigned __int64 Uid, StringBuilder* Name, VRLEN NameSize, StringBuilder* Path, VRLEN PathSize)
			{
				char __pin * pName = new char[NameSize];
				memset(pName,0,NameSize);
				char __pin * pPath = new char[PathSize];
				memset(pPath,0,PathSize);
				ret = ctdbFindTableByUID((CTHANDLE)Database, Uid, pName, NameSize, pPath, PathSize);
				Name->Length = 0;
				Path->Length = 0;
				if (!ret)
				{
					Name->Insert(0,pName);
					Path->Insert(0,pPath);
				}
				delete[] pName;
				delete[] pPath;
				return ret;
			}

			static CTDBRET FindTarget(IntPtr Record, IntPtr Target, FIND_MODE FindMode)
			{
				return ctdbFindTarget((CTHANDLE)Record, (pVOID)Target, (CTFIND_MODE)FindMode);
			}

			static CTDBRET FindTargetKey(IntPtr Record, IntPtr Target, [Out]CTOFFSET __gc* Offset, FIND_MODE FindMode)
			{
				CTOFFSET offset;
				ret = ctdbFindTargetKey((CTHANDLE) Record, (pVOID) Target, &offset, (CTFIND_MODE) FindMode);
				*Offset = offset;
				return ret;
			}

			static CTDBRET FirstDatabase(IntPtr Session,[Out]StringBuilder *Name, VRLEN NameSize, [Out]StringBuilder *Path, VRLEN PathSize)
			{
		        char __pin * pName = new char[NameSize];
				memset(pName,0,NameSize);
				char __pin * pPath = new char[PathSize];
				memset(pPath,0,PathSize);
				ret = ctdbFirstDatabase((CTHANDLE)Session, pName, NameSize, pPath, PathSize);
				Name->Length = 0;
				Path->Length = 0;
				if (!ret)
				{
					Name->Insert(0,pName);
					Path->Insert(0,pPath);
				}
				delete[] pName;
				delete[] pPath;
				return ret;
			}

			static CTDBRET FirstRecord(IntPtr Record)
			{
				return ctdbFirstRecord((CTHANDLE)Record);
			}
			
			static CTDBRET JumpToRecord(IntPtr Record, LONG offset)
			{
				return ctdbJumpToRecord((CTHANDLE)Record, offset);
			}

			static CTDBRET FirstResource(IntPtr resource, bool lock)
			{
				return ctdbFirstResource((CTHANDLE) resource, lock);
			}

			static CTDBRET FirstTable(IntPtr Database,StringBuilder *Name, VRLEN NameSize, StringBuilder *Path, VRLEN PathSize)
			{
				char __pin * pName = new char[NameSize];
				memset(pName,0,NameSize);
				char __pin * pPath = new char[PathSize];
				memset(pPath,0,PathSize);
				ret = ctdbFirstTable((CTHANDLE)Database, pName, NameSize, pPath, PathSize);
				Name->Length = 0;
				Path->Length = 0;
				if (!ret)
				{
					Name->Insert(0,pName);
					Path->Insert(0,pPath);
				}
				delete[] pName;
				delete[] pPath;
				return ret;
			}
			
			static CTDBRET FloatToBigInt(float Value, [Out] CTBIGINT __gc* BigInt)
			{
				CTBIGINT big;
				ret = ctdbFloatToBigInt(Value, &big);
				*BigInt = big;
				return ret;
			}

			static CTDBRET FloatToCurrency(float Value, [Out] CTCURRENCY __gc* Currency)
			{
				CTCURRENCY cur;
				ret = ctdbFloatToCurrency(Value, &cur);
				*Currency = cur;
				return ret;
			}

			static CTDBRET FloatToMoney(float Value, [Out]CTMONEY __gc* Money)
			{
				CTMONEY mon;
			    ret = ctdbFloatToMoney(Value, &mon);
				*Money = mon;
				return ret;

			}

			static CTDBRET FloatToNumber(float Value, [Out]ctdbNUMBER __gc* Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ret = ctdbFloatToNumber(Value, num);
				CTN2ctN(num,Number);
				return ret;
			}

			static void FreeDatabase(IntPtr Database)
			{
				ctdbFreeDatabase((CTHANDLE)Database);
			}
			
			static void FreeRecord(IntPtr Record)
			{
				ctdbFreeRecord((CTHANDLE)Record);
			}

			static void FreeSession(IntPtr Session)
			{
				ctdbFreeSession((CTHANDLE)Session);
			}
			
			static void FreeTable(IntPtr Table)
			{
				ctdbFreeTable((CTHANDLE)Table);
			}

			static bool GetAttachMode(IntPtr Handle)
			{
				return ctdbGetAttachMode((CTHANDLE) Handle);
			}

			static bool GetAutoCommit(IntPtr Handle)
			{
				return ctdbGetAutoCommit((CTHANDLE) Handle);
			}

			static CTDBRET GetCndxIndex(IntPtr Table, NINT IndexNbr, StringBuilder* Buffer, NINT BufferLen)
			{
		        char __pin * buf = new char[BufferLen];
				memset(buf,0,BufferLen);
				ret = ctdbGetCndxIndex((CTHANDLE) Table, IndexNbr, buf, BufferLen);
				Buffer->Length = 0;
				if (!ret)
					Buffer->Insert(0,buf);
				delete[] buf;
				return ret;

			}

			static CTDBRET GetCndxIndexByName(IntPtr Table, String* IndexName, StringBuilder* Buffer, NINT BufferLen)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(IndexName);
		        char __pin * buf = new char[BufferLen];
				memset(buf,0,BufferLen);
				ret = ctdbGetCndxIndexByName((CTHANDLE) Table, (pTEXT)name.ToPointer(), buf, BufferLen);
				Buffer->Length = 0;
				if (!ret)
					Buffer->Insert(0,buf);
				delete[] buf;
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static NINT GetCndxIndexLength(IntPtr Table, NINT IndexNbr)
			{
				return ctdbGetCndxIndexLength((CTHANDLE) Table, IndexNbr);
			}

			static NINT GetCndxIndexLengthByName(IntPtr Table, String* IndexName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(IndexName);
				NINT ret = ctdbGetCndxIndexLengthByName((CTHANDLE) Table, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static NINT GetDatabaseCount(IntPtr Session)
			{
				return ctdbGetDatabaseCount((CTHANDLE)Session);
			}

			static IntPtr GetDatabaseHandle(IntPtr Handle)
			{
				return ctdbGetDatabaseHandle((CTHANDLE) Handle);
			}

			static String* GetDatabaseName(IntPtr Database)
			{
				return ctdbGetDatabaseName((CTHANDLE)Database);
			}

			static String* GetDatabasePath(IntPtr Database)
			{
				return ctdbGetDatabasePath((CTHANDLE)Database);
			}

			static CTDBRET GetDatabaseUID(IntPtr Session, String* DatabaseName, [Out] unsigned __int64 __gc* Uid)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(DatabaseName);
				ULONG ptr;
				ret = ctdbGetDatabaseUID((CTHANDLE)Session, (pTEXT)name.ToPointer(), &ptr);
				Marshal::FreeHGlobal(name);
				*Uid = (ULONG)ptr;
				return ret;
			}

			static NINT GetDatno(IntPtr Table)
			{
				return ctdbGetDatno((CTHANDLE) Table);
			}

			static NINT GetDay(CTDATE Date)
			{
				return ctdbGetDay(Date);
			}

			static NINT GetDefaultIndex(IntPtr Record)
			{
				return ctdbGetDefaultIndex((CTHANDLE)Record);
			}

			static String* GetDefaultIndexName(IntPtr Record)
			{
				return ctdbGetDefaultIndexName((CTHANDLE)Record);
			}

			static String* GetDefaultSqlTableOwner(IntPtr Handle)
			{
				return ctdbGetDefaultSqlTableOwner((CTHANDLE)Handle);
			}
			
			static String* GetDefFloatFormat(IntPtr Handle)
			{
				return ctdbGetDefFloatFormat((CTHANDLE)Handle);
			}

			static TIME_TYPE GetDefTimeType(IntPtr Handle)
			{
				return (TIME_TYPE)ctdbGetDefTimeType((CTHANDLE)Handle);
			}

			static DATE_TYPE GetDefDateType(IntPtr Handle)
			{
				return (DATE_TYPE)ctdbGetDefDateType((CTHANDLE)Handle);
			}

			static CTDBRET GetError(IntPtr Handle)
			{
				return ctdbGetError((CTHANDLE)Handle);
			}

			static NINT GetErrorIndex(IntPtr Record)
			{
				return ctdbGetErrorIndex((CTHANDLE) Record);
			}

			static IntPtr GetField(IntPtr Table,NINT Index)
			{
				return ctdbGetField((CTHANDLE)Table, Index);
			}

			static IntPtr GetFieldAddress(IntPtr Record, NINT FieldNumber)
			{
				return ctdbGetFieldAddress((CTHANDLE) Record, FieldNumber);
			}

			static FIELD_STATUS GetFieldStatus(IntPtr Field)
			{
				return (FIELD_STATUS)ctdbGetFieldStatus((CTHANDLE) Field);
			}

/*Bool*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNumber, [Out]bool __gc* Bool)
			{
				bool val;
				ret = ctdbGetFieldAsBool((CTHANDLE)Record, FieldNumber, (pCTBOOL)&val);
				*Bool = val;
				return ret;
			}

/*Int32*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNumber, [Out]CTSIGNED __gc* Value)
			{
				CTSIGNED val;
				ret = ctdbGetFieldAsSigned((CTHANDLE)Record, FieldNumber, &val);
				*Value = val;
				return ret;
			}

/*UInt32*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNumber, [Out] CTUNSIGNED __gc* Value)
			{
				CTUNSIGNED val;
				ret = ctdbGetFieldAsUnsigned((CTHANDLE)Record, FieldNumber, &val);
				*Value = val;
				return ret;
			}

/*Int64*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNumber, [Out]CTBIGINT __gc* Value)
			{
				CTBIGINT val;
				ret = ctdbGetFieldAsBigint((CTHANDLE)Record, FieldNumber, &val);
				*Value = val;
				return ret;
			}

/*UInt64*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNumber, [Out]CTUBIGINT __gc* Value)
			{
				CTUBIGINT val;
				ret = ctdbGetFieldAsUnsignedBigint((CTHANDLE)Record, FieldNumber, &val);
				*Value = val;
				return ret;
			}

/*String*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNumber, [Out]StringBuilder __gc* Value)
			{
#ifdef ctUNICODE
				FIELD_TYPE type = GetFieldType(FieldNumber);
				if(type == FIELD_TYPE::F2UNICODE || type == FIELD_TYPE::V2UNICODE)
				{
					WCHAR __pin * pName = new WCHAR[Value->Capacity];
					memset(pName,0,Value->Capacity);
					ret = ctdbGetFieldAsUTF16((CTHANDLE)Record, FieldNumber, pName, Value->Capacity);
					Value->Length = 0;
					if (ret == 0 || ret == CTDBRET_MOREDATA)
						Value->Insert(0,pName);
					delete[] pName;
				}
				else
				{
					char __pin * pName = new char[Value->Capacity];
					memset(pName,0,Value->Capacity);
					ret = ctdbGetFieldAsString((CTHANDLE)Record, FieldNumber, pName, Value->Capacity);
					Value->Length = 0;
					if (ret == 0 || ret == CTDBRET_MOREDATA)
						Value->Insert(0,pName);
					delete[] pName;
				}
#else
				char __pin * pName = new char[Value->Capacity];
				memset(pName,0,Value->Capacity);
				ret = ctdbGetFieldAsString((CTHANDLE)Record, FieldNumber, pName, Value->Capacity);
				Value->Length = 0;
				if (ret == 0 || ret == CTDBRET_MOREDATA)
					Value->Insert(0,pName);
				delete[] pName;
#endif
				return ret;
			}

/*Float*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNumber, [Out] float __gc* Float)
			{
				CTFLOAT val;
				ret = ctdbGetFieldAsFloat((CTHANDLE)Record, FieldNumber, &val);
				float f = (float)val;
				*Float = f;
				return ret;
			}

/*Double*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNumber, [Out] CTFLOAT __gc* Float)
			{
				CTFLOAT val;
				ret = ctdbGetFieldAsFloat((CTHANDLE)Record, FieldNumber, &val);
				*Float = val;
				return ret;
			}

/*Bytes*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNbr, Byte Arr __gc[])
			{
				VRLEN size = Arr->Length;
				VRLEN fieldSize = ctdbGetFieldDataLength((CTHANDLE)Record, FieldNbr);
				if (size < fieldSize)
					return CTDBRET_ARGSMALL;
				GCHandle gch = GCHandle::Alloc( Arr, GCHandleType::Pinned);
				void* data = (pUTEXT)gch.AddrOfPinnedObject().ToPointer();
				void* fieldData = ctdbGetFieldAddress((CTHANDLE)Record, FieldNbr);
				memcpy(data, fieldData, fieldSize);
				gch.Free();
				return CTDBRET_OK;
			}

/*Binary*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNbr, IntPtr pData, VRLEN size)
			{
				return ctdbGetFieldAsBinary((CTHANDLE) Record, FieldNbr, (pVOID) pData, size);
			}

/*Blob*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNbr, [Out]ctdbBLOB __gc* pBlob)
			{
				CTBLOB __pin * blob = new CTBLOB;
				blob->data = NULL;
				blob->size = 0;
				blob->allocated = 0;
				ret = ctdbGetFieldAsBlob((CTHANDLE) Record, FieldNbr, blob);
				pBlob->data = blob->data;
				pBlob->size = blob->size;
				pBlob->allocated = blob->allocated;
				return ret;
			}

/*Number*/	static CTDBRET GetFieldValue(IntPtr Record, NINT FieldNumber, [Out]ctdbNUMBER __gc* Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ret = ctdbGetFieldAsNumber((CTHANDLE)Record, FieldNumber, num);
				CTN2ctN(num,Number);
				return ret;
			}


#ifdef oldGetSet
			static CTDBRET GetFieldAsBlob(IntPtr Record, NINT FieldNbr, [Out]ctdbBLOB __gc* pBlob)
			{
				CTBLOB __pin * blob = new CTBLOB;
				blob->data = NULL;
				blob->size = 0;
				blob->allocated = 0;
				ret = ctdbGetFieldAsBlob((CTHANDLE) Record, FieldNbr, blob);
				pBlob->data = blob->data;
				pBlob->size = blob->size;
				pBlob->allocated = blob->allocated;
				return ret;
			}

			static CTDBRET GetFieldAsBytes(IntPtr Record, NINT FieldNbr, Byte arr __gc[])
			{
				VRLEN size = arr->Length;
				VRLEN fieldSize = ctdbGetFieldDataLength((CTHANDLE)Record, FieldNbr);
				if (size < fieldSize)
					return CTDBRET_ARGSMALL;
				GCHandle gch = GCHandle::Alloc( arr, GCHandleType::Pinned);
				void* data = (pUTEXT)gch.AddrOfPinnedObject().ToPointer();
				void* fieldData = ctdbGetFieldAddress((CTHANDLE)Record, FieldNbr);
				memcpy(data, fieldData, fieldSize);
				gch.Free();
				return CTDBRET_OK;
			}
			
			static CTDBRET GetFieldAsBool(IntPtr Record, NINT FieldNumber, [Out]bool __gc* Bool)
			{
				bool val;
				ret = ctdbGetFieldAsBool((CTHANDLE)Record, FieldNumber, (int*)&val);
				*Bool = val;
				return ret;
			}

		    static CTDBRET GetFieldAsBigint(IntPtr Record, NINT FieldNumber, [Out]CTBIGINT __gc* Bigint)
			{
				CTBIGINT val;
				ret = ctdbGetFieldAsBigint((CTHANDLE)Record, FieldNumber, &val);
				*Bigint = val;
				return ret;
			}

		    static CTDBRET GetFieldAsUnsignedBigint(IntPtr Record, NINT FieldNumber, [Out]CTUBIGINT __gc* Bigint)
			{
				CTUBIGINT val;
				ret = ctdbGetFieldAsUnsignedBigint((CTHANDLE)Record, FieldNumber, &val);
				*Bigint = val;
				return ret;
			}

			static CTDBRET GetFieldAsBinary(IntPtr Record, NINT FieldNbr, IntPtr pData, VRLEN size)
			{
				return ctdbGetFieldAsBinary((CTHANDLE) Record, FieldNbr, (pVOID) pData, size);
			}

		    static CTDBRET GetFieldAsCurrency(IntPtr Record, NINT FieldNumber, [Out]CTCURRENCY __gc* Currency)
			{
				CTCURRENCY val;
				ret = ctdbGetFieldAsCurrency((CTHANDLE)Record, FieldNumber, &val);
				*Currency = val;
				return ret;
			}

			static CTDBRET GetFieldAsDate(IntPtr Record, NINT FieldNumber, [Out] CTDATE __gc* Date)
			{
				CTDATE val;
				ret = ctdbGetFieldAsDate((CTHANDLE)Record, FieldNumber, &val);
				*Date = val;
				return ret;
			}

			static CTDBRET GetFieldAsDateTime(IntPtr Record, NINT FieldNumber, [Out] CTDATETIME __gc* DateTime)
			{
				CTDATETIME val;
				ret = ctdbGetFieldAsDateTime((CTHANDLE)Record, FieldNumber, &val);
				*DateTime = val;
				return ret;
			}

			static CTDBRET GetFieldAsMoney(IntPtr Record, NINT FieldNumber, [Out] CTMONEY __gc* Money)
			{
				CTMONEY val;
				ret = ctdbGetFieldAsMoney((CTHANDLE)Record, FieldNumber, &val);
				*Money = val;
				return ret;
			}

		    static CTDBRET GetFieldAsNumber(IntPtr Record, NINT FieldNumber, [Out]ctdbNUMBER __gc* Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ret = ctdbGetFieldAsNumber((CTHANDLE)Record, FieldNumber, num);
				CTN2ctN(num,Number);
				return ret;
			}
 
			static CTDBRET GetFieldAsSigned(IntPtr Record, NINT FieldNumber, [Out] long __gc* Signed)
			{
				CTSIGNED val;
				ret = ctdbGetFieldAsSigned((CTHANDLE)Record, FieldNumber, &val);
				*Signed = val;
				return ret;
			}

			static CTDBRET GetFieldAsTime(IntPtr Record, NINT FieldNumber, [Out] CTTIME __gc* Time)
			{
				CTTIME val;
				ret = ctdbGetFieldAsTime((CTHANDLE)Record, FieldNumber, &val);
				*Time = val;
				return ret;
			}

			static CTDBRET GetFieldAsUnsigned(IntPtr Record, NINT FieldNumber, [Out] unsigned long __gc* Unsigned)
			{
				CTUNSIGNED val;
				ret = ctdbGetFieldAsUnsigned((CTHANDLE)Record, FieldNumber, &val);
				*Unsigned = val;
				return ret;
			}

			static CTDBRET GetFieldAsFloat(IntPtr Record, NINT FieldNumber, [Out] double __gc* Float)
			{
				CTFLOAT val;
				ret = ctdbGetFieldAsFloat((CTHANDLE)Record, FieldNumber, &val);
				*Float = val;
				return ret;
			}

#endif oldGetSet

			static CTDBRET GetFieldAsString(IntPtr Record, NINT FieldNbr, StringBuilder* Buffer, VRLEN BufferSize)
			{
#ifdef ctUNICODE
				FIELD_TYPE type = GetFieldType(FieldNbr);
				if(type == FIELD_TYPE::F2UNICODE || type == FIELD_TYPE::V2UNICODE)
				{
					WCHAR __pin * pName = new WCHAR[BufferSize];
					memset(pName,0,BufferSize);
					ret = ctdbGetFieldAsUTF16((CTHANDLE)Record, FieldNbr, pName, BufferSize);
					Buffer->Length = 0;
					if (!ret)
						Buffer->Insert(0,pName);
					delete[] pName;
				}
				else
				{
					char __pin * pName = new char[BufferSize];
					memset(pName,0,BufferSize);
					ret = ctdbGetFieldAsString((CTHANDLE)Record, FieldNbr, pName, BufferSize);
					Buffer->Length = 0;
					if (!ret)
						Buffer->Insert(0,pName);
					delete[] pName;
				}
#else
		        char __pin * pName = new char[BufferSize];
				memset(pName,0,BufferSize);
				ret = ctdbGetFieldAsString((CTHANDLE)Record, FieldNbr, pName, BufferSize);
				Buffer->Length = 0;
				if (!ret)
					Buffer->Insert(0,pName);
				delete[] pName;
#endif
				return ret;
			}

			static IntPtr GetFieldByName(IntPtr Table, String* FieldName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(FieldName);
				CTHANDLE pField = ctdbGetFieldByName((CTHANDLE)Table, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return pField;
			}

			static NINT GetFieldNumber(IntPtr Table, String* FieldName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(FieldName);
				NINT num = ctdbGetFieldNumber((CTHANDLE)Table, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return num;
			}

			static NINT GetFieldNumberByName(IntPtr Record, String* FieldName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(FieldName);
				NINT num = ctdbGetFieldNumberByName((CTHANDLE) Record, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return num;
			}

			static VRLEN GetFieldOffset(IntPtr Record, NINT FieldNbr)
			{
				return ctdbGetFieldOffset((CTHANDLE) Record, FieldNbr);
			}

			static VRLEN GetFieldSize(IntPtr Record, NINT FieldNbr)
			{
				return ctdbGetFieldSize((CTHANDLE) Record, FieldNbr);
			}

			static String* GetFilter(IntPtr Handle)
			{
				return ctdbGetFilter((CTHANDLE) Handle);
			}

			static VRLEN GetFieldDataLength(IntPtr Record, NINT FieldNbr)
			{
				return ctdbGetFieldDataLength((CTHANDLE)Record,FieldNbr);
			}

			static DATE_TYPE GetFieldDefaultDateType(IntPtr Field)
			{
				 return (DATE_TYPE)ctdbGetFieldDefaultDateType((CTHANDLE) Field);
			}

			static TIME_TYPE GetFieldDefaultTimeType(IntPtr Field)
			{
				 return (TIME_TYPE)ctdbGetFieldDefaultTimeType((CTHANDLE) Field);
			}

			static String* GetFieldDefaultValue(IntPtr Field, [Out] int __gc* Length)
			{
				VRLEN pnt;
				String* s = ctdbGetFieldDefaultValue((CTHANDLE)Field, &pnt);
				*Length = pnt;
				return s;
			}

			static NINT GetFieldLength(IntPtr Field)
			{
				return ctdbGetFieldLength((CTHANDLE) Field);
			}

			static IntPtr GetFieldHandle(IntPtr Handle)
			{
				return ctdbGetFieldHandle((CTHANDLE) Handle);
			}

			static String* GetFieldName(IntPtr Field)
			{
				return ctdbGetFieldName((CTHANDLE)Field);
			}

			static VRLEN GetFieldNbr(IntPtr Field)
			{
				return ctdbGetFieldNbr((CTHANDLE)Field);
			}

			static bool GetFieldNullFlag(IntPtr Field)
			{
				return (ctdbGetFieldNullFlag((CTHANDLE)Field)!=0);
			}

			static NINT GetFieldPrecision(IntPtr Field)
			{
				return ctdbGetFieldPrecision((CTHANDLE)Field);
			}

			static NINT GetFieldScale(IntPtr Field)
			{
				return ctdbGetFieldScale((CTHANDLE)Field);
			}

			static FIELD_TYPE GetFieldType(IntPtr Field)
			{
				return (FIELD_TYPE)ctdbGetFieldType((CTHANDLE) Field);
			}

			static CTDBRET GetFieldProperties(IntPtr Field, [Out]StringBuilder** FieldName,[Out] FIELD_TYPE __gc* Type, [Out] VRLEN __gc* Length)
			{
				char* fieldname;
				CTDBTYPE type;
				VRLEN length;
				CTDBRET ret = ctdbGetFieldProperties((CTHANDLE)Field, &fieldname, &type, &length);
				*Type = (FIELD_TYPE)type;
				*Length = length;
				(*FieldName)->Length = 0;
				if (!ret)
					(*FieldName)->Insert(0,fieldname);
				return ret;
			}

			static NINT GetHandleType(IntPtr Handle)
			{
				return ctdbGetHandleType((CTHANDLE) Handle);
			}
			
			static NINT GetHour(CTTIME Time)
			{
				return ctdbGetHour(Time);
			}

			static NINT GetIdxno(IntPtr Index)
			{
				return ctdbGetIdxno((CTHANDLE) Index);
			}

			static NINT GetIdxnoByName(IntPtr Table, String* IndexName)
			{
				IntPtr indexname = Marshal::StringToHGlobalAnsi(IndexName);
				NINT number = ctdbGetIdxnoByName((CTHANDLE) Table, (pTEXT)indexname.ToPointer());
				Marshal::FreeHGlobal(indexname);
				return number;
			}

			static NINT GetIdxnoByNumber(IntPtr Table, NINT Index)
			{
				return ctdbGetIdxnoByNumber((CTHANDLE) Table, Index);
			}

			static IntPtr GetIndex(IntPtr Table,NINT Index)
			{
				return ctdbGetIndex((CTHANDLE)Table, Index);
			}

			static IntPtr GetIndexByName(IntPtr Table, String* Name)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				CTHANDLE pIndex = ctdbGetIndexByName((CTHANDLE)Table, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return pIndex;
			}

			static void GetIFIL(IntPtr Table, [Out] IFIL_STRUCT __gc* i)
			{
				pCTDBTABLE pTable = (pCTDBTABLE)ctdbGetTableHandle((CTHANDLE)Table);
				pIFIL ifil = pTable->ifilptr;
				i->dfilmod = ifil->dfilmod;
				i->dfilno = ifil->dfilno;
				i->dnumidx = ifil->dnumidx;
				i->dreclen = ifil->dreclen;
				i->dxtdsiz = ifil->dxtdsiz;
				i->ifilmod = ifil->ifilmod;
				i->ix = ifil->ix;
				i->ixtdsiz = ifil->ixtdsiz;
				i->pfilnam = ifil->pfilnam;
				i->rfstfld = ifil->rfstfld;
				i->rlstfld = ifil->rlstfld;
				i->tfilno = ifil->tfilno;
			}

			static void GetIIDX(IFIL_STRUCT __gc* ifil, [Out] IIDX_STRUCT __gc* i, int indexNo)
			{
				pIIDX iidx = ifil->ix;
				while(indexNo > 0)
				{
					iidx++;
					indexNo--;
				}
				i->aidxnam = iidx->aidxnam;
				i->altseq = iidx->altseq;
				i->iempchr = iidx->iempchr;
				i->ikeydup = iidx->ikeydup;
				i->ikeylen = iidx->ikeylen;
				i->ikeytyp = iidx->ikeytyp;
				i->inulkey = iidx->inulkey;
				i->inumseg = iidx->inumseg;
				i->pvbyte = iidx->pvbyte;
				i->ridxnam = iidx->ridxnam;
				i->seg = iidx->seg;
			}

			static void GetISEG(IIDX_STRUCT __gc* iidx, [Out] ISEG_STRUCT __gc* i, int segNo)
			{
				pISEG iseg = iidx->seg;
				while(segNo > 0)
				{
					iseg++;
					segNo--;
				}
				i->segmode = iseg->segmode;
				i->slength = iseg->slength;
				i->soffset = iseg->soffset;
			}

			static void GetDATOBJ(IntPtr Table, DATOBJ_STRUCT __gc* doda, int fieldNo)
			{
				pCTDBTABLE pTable = (pCTDBTABLE)ctdbGetTableHandle((CTHANDLE)Table);
				pDATOBJ dodaPtr = pTable->dodaptr;
				while(fieldNo > 0)
				{
					dodaPtr++;
					fieldNo--;
				}
				doda->fadr = dodaPtr->fadr;
				doda->fhrc = dodaPtr->fhrc;
				doda->flen = dodaPtr->flen;
				doda->flev = dodaPtr->flev;
				doda->frsrv = dodaPtr->frsrv;
				doda->frsv = dodaPtr->frsv;
				doda->fsymb = dodaPtr->fsymb;
				doda->ftype = dodaPtr->ftype;
			}

			static IntPtr GetIndexByUID(IntPtr Handle, unsigned __int64 Uid)
			{
				return ctdbGetIndexByUID((CTHANDLE) Handle, Uid);
			}

			static bool GetIndexDuplicateFlag(IntPtr Index)
			{
				return (ctdbGetIndexDuplicateFlag((CTHANDLE)Index)!=0);
			}
			
			static NINT GetIndexEmptyChar(IntPtr Index)
			{
				return ctdbGetIndexEmptyChar((CTHANDLE)Index);
			}

			static IntPtr GetIndexHandle(IntPtr Handle)
			{
				return ctdbGetIndexHandle((CTHANDLE) Handle);
			}

			static NINT GetIndexKeyLength(IntPtr Index)
			{
				return ctdbGetIndexKeyLength((CTHANDLE)Index);
			}

			static KEY_TYPE GetIndexKeyType(IntPtr Index)
			{
				return (KEY_TYPE)ctdbGetIndexKeyType((CTHANDLE)Index);
			}

			static String* GetIndexExtension(IntPtr Table)
			{
				return ctdbGetIndexExtension((CTHANDLE)Table);
			}

			static String* GetIndexFilename(IntPtr Index)
			{
				return ctdbGetIndexFilename((CTHANDLE)Index);
			}

			static String* GetIndexName(IntPtr Index)
			{
				return ctdbGetIndexName((CTHANDLE)Index);
			}

			static CTDBRET GetIndexNbr(IntPtr Index, [Out] int __gc* Number)
			{
				VRLEN ptr;
				ret = ctdbGetIndexNbr((CTHANDLE)Index, &ptr);
				*Number = (VRLEN)ptr;
				return ret;
			}

			static NINT GetIndexNbrByName(IntPtr Table, String* IndexName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(IndexName);
				NINT IndexNo = ctdbGetIndexNbrByName((CTHANDLE)Table, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return IndexNo;
			}

			static bool GetIndexNullFlag(IntPtr Index)
			{
				return (ctdbGetIndexNullFlag((CTHANDLE)Index)!=0);
			}

			static NINT GetIndexSegmentCount(IntPtr Index)
			{
				return ctdbGetIndexSegmentCount((CTHANDLE)Index);
			}

			static INDEX_STATUS GetIndexStatus(IntPtr Index)
			{
				return (INDEX_STATUS)ctdbGetIndexStatus((CTHANDLE) Index);
			}

			static bool GetIndexTemporaryFlag(IntPtr Index)
			{
				return ctdbGetIndexTemporaryFlag((CTHANDLE)Index);
			}

			static CTDBRET GetIndexUID(IntPtr Index, String* IdxName, [Out] unsigned __int64 __gc* Uid)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(IdxName);
				ULONG ptr;
				ret = ctdbGetIndexUID((CTHANDLE)Index, (pTEXT)name.ToPointer(), &ptr);
				Marshal::FreeHGlobal(name);
				*Uid = (ULONG)ptr;
				return ret;
			}

			static KEEP_MODE GetKeepLock(IntPtr Handle)
			{
				return (KEEP_MODE)ctdbGetKeepLock((CTHANDLE)Handle);
			}

			static LIB_TYPE GetLibType(IntPtr Handle)
			{
				return (LIB_TYPE)ctdbGetLibType((CTHANDLE)Handle);
			}

			static LOCK_MODE GetLockMode(IntPtr Handle)
			{
				return (LOCK_MODE)ctdbGetLockMode((CTHANDLE)Handle);
			}

			static bool GetLogonOnly(IntPtr Session)
			{
				return (ctdbGetLogonOnly((CTHANDLE)Session)!=0);
			}

			static NINT GetMinute(CTTIME Time)
			{
				return ctdbGetMinute(Time);
			}

			static NINT GetMonth(CTDATE Date)
			{
				return ctdbGetMonth(Date);
			}

			static OPS_MODE GetOperationState(IntPtr Handle)
			{
				return (OPS_MODE)ctdbGetOperationState((CTHANDLE) Handle);
			}

			static CTDBRET GetPadChar(IntPtr Handle, [Out] TEXT __gc* pPadChar, [Out] TEXT __gc* pDmlChar)
			{
				TEXT pChar,dChar;
				ret = ctdbGetPadChar((CTHANDLE) Handle, &pChar, &dChar);
				*pPadChar = pChar;
				*pDmlChar = dChar;
				return ret;
			}

			static String* GetPathPrefix(IntPtr Session)
			{
				return ctdbGetPathPrefix((CTHANDLE) Session);
			}

			static IntPtr GetRecord(IntPtr Table, NINT Index)
			{
				return ctdbGetRecord((CTHANDLE) Table, Index);
			}

			static IntPtr GetRecordBuffer(IntPtr Handle)
			{
				return ctdbGetRecordBuffer((CTHANDLE) Handle);
			}

			static CTDBRET GetRecordCount(IntPtr Record, [Out] unsigned __int64 __gc* Count)
			{
				CTUINT64 val;
				ret = ctdbGetRecordCount((CTHANDLE)Record, &val);
				*Count = val;
				return ret;
			}

			static IntPtr GetRecordHandle(IntPtr Handle)
			{
				return ctdbGetRecordHandle((CTHANDLE) Handle);
			}

			static VRLEN GetRecordLength(IntPtr Record)
			{
			    return ctdbGetRecordLength((CTHANDLE)Record);
			}

			static LOCK_MODE GetRecordLock(IntPtr Record)
			{
				return (LOCK_MODE)ctdbGetRecordLock((CTHANDLE)Record);
			}

			static NINT GetRecordNbr(IntPtr Record)
			{
				return ctdbGetRecordNbr((CTHANDLE) Record);
			}

			static CTDBRET GetRecordPos(IntPtr Record, [Out]__int64 __gc* Offset)
			{
				CTOFFSET offset;
				ret = ctdbGetRecordPos((CTHANDLE)Record, &offset);
				*Offset = offset;
				return ret;
			}

			static CTDBRET GetRecordPosAtOffset(IntPtr Handle, [Out]__int64 __gc* Offset)
			{
				CTOFFSET offset = *Offset;
				ret = ctdbRecordPosAtOffset((CTHANDLE) Handle, (pCTOFFSET)&offset);
				*Offset = offset;
				return ret;
			}

			static __int64 GetRecordPosAtPercentile(IntPtr Record, int Percentile)
			{
				TEXT idxval[MAXLEN];
				COUNT keyno = ctdbGetDefaultIndex((CTHANDLE)Record);
				pCTDBINDEX index = (pCTDBINDEX)ctdbGetIndex(ctdbGetTableHandle((CTHANDLE)Record),keyno);
				return FRCKEY(index->idxno, idxval, Percentile);
			}

			static VRLEN GetRecordSize(IntPtr Record)
			{
			    return ctdbGetRecordSize((CTHANDLE)Record);
			}

			static CTDBRET GetResourceData(IntPtr Resource, Byte arr __gc[], VRLEN Size)
			{
				VRLEN arrSize = arr->Length;
				if (arrSize < Size)
					return CTDBRET_ARGSMALL;
				GCHandle gch = GCHandle::Alloc( arr, GCHandleType::Pinned);
				void* data = (pUTEXT)gch.AddrOfPinnedObject().ToPointer();
				void* fieldData = ctdbGetResourceData((CTHANDLE)Resource);
				memcpy(data, fieldData, Size);
				gch.Free();
				return CTDBRET_OK;
			}

			static VRLEN GetResourceDataLength(IntPtr Resource)
			{
				return ctdbGetResourceDataLength((CTHANDLE) Resource);
			}

			static String* GetResourceName(IntPtr Resource)
			{
				return ctdbGetResourceName((CTHANDLE) Resource);
			}

			static ULONG GetResourceNumber(IntPtr Resource)
			{
				return ctdbGetResourceNumber((CTHANDLE) Resource);
			}

			static ULONG GetResourceType(IntPtr Resource)
			{
				return ctdbGetResourceType((CTHANDLE) Resource);
			}

			static CTDBRET GetRowid(IntPtr Record, [Out]__int64 __gc* Id)
			{
				CTROWID val;
				ret = ctdbGetRowid((CTHANDLE)Record, &val);
				*Id = val;
				return ret;
			}

			static NINT GetSecond(CTTIME Time)
			{
				return ctdbGetSecond(Time);
			}

			static IntPtr GetSegment(IntPtr Index, NINT SegmentNumber)
			{
				return ctdbGetSegment((CTHANDLE)Index, SegmentNumber);
			}

			static IntPtr GetSegmentField(IntPtr Segment)
			{
				return ctdbGetSegmentField((CTHANDLE)Segment);
			}
			
			static IntPtr GetSegmentPartialField(IntPtr Segment)
			{
				return ctdbGetSegmentPartialField((CTHANDLE)Segment);
			}

			static IntPtr GetSegmentHandle(IntPtr Segment)
			{
				return ctdbGetSegmentHandle((CTHANDLE) Segment);
			}

			static String* GetSegmentFieldName(IntPtr Segment)
			{
				return ctdbGetSegmentFieldName((CTHANDLE) Segment);
			}

			static SEG_MODE GetSegmentMode(IntPtr Segment)
			{
				return (SEG_MODE)ctdbGetSegmentMode((CTHANDLE)Segment);
			}

			static CTDBRET GetSegmentNbr(IntPtr Segment, [Out] int __gc* Index)
			{
				VRLEN ptr;
				ret = ctdbGetSegmentNbr((CTHANDLE)Segment, &ptr);
				*Index = (VRLEN)ptr;
				return ret;
			}

			static SEGMENT_STATUS GetSegmentStatus(IntPtr Segment)
			{
				return (SEGMENT_STATUS)ctdbGetSegmentStatus((CTHANDLE) Segment);
			}

			static String* GetServerName(IntPtr Session)
			{
				return ctdbGetServerName((CTHANDLE)Session);
			}

			static IntPtr GetSessionHandle(IntPtr Handle)
			{
				return ctdbGetSessionHandle((CTHANDLE) Handle);
			}

			static CTDBRET GetSessionPath(IntPtr Session,StringBuilder *Path, VRLEN PathSize)
			{
				char __pin * pPath = new char[PathSize];
				memset(pPath,0,PathSize);
				ret = ctdbGetSessionPath((CTHANDLE)Session, pPath, PathSize);
				Path->Length = 0;
				if (!ret)
					Path->Insert(0,pPath);
				delete[] pPath;
				return ret;
			}

			static NINT GetSessionParams(IntPtr Session,SESSION_PARAM Param)
			{
				return ctdbGetSessionParams((CTHANDLE)Session,(CTSESSION_PARAM)Param);
			}

			static SESSION_TYPE GetSessionType(IntPtr Session)
			{
				return (SESSION_TYPE)ctdbGetSessionType((CTHANDLE)Session);
			}

			static LONG GetSystemConfig(NINT index)
			{
				return ctdbGetSystemConfig(index);
			}

			static IntPtr GetTable(IntPtr Database, NINT Index)
			{
				return ctdbGetTable((CTHANDLE) Database, Index);
			}

			static CREATE_MODE GetTableCreateMode(IntPtr Table)
			{
				return (CREATE_MODE)ctdbGetTableCreateMode((CTHANDLE)Table);
			}

			static NINT GetTableDefaultDataExtentSize(IntPtr Table)
			{
				return ctdbGetTableDefaultDataExtentSize((CTHANDLE)Table);
			}

			static NINT GetTableDefaultIndexExtentSize(IntPtr Table)
			{
				return ctdbGetTableDefaultIndexExtentSize((CTHANDLE)Table);
			}

			static String* GetTableExtension(IntPtr Table)
			{
				return ctdbGetTableExtension((CTHANDLE)Table);
			}

			static VRLEN GetTableFieldCount(IntPtr Table)
			{
				return ctdbGetTableFieldCount((CTHANDLE)Table);
			}

			static String* GetTableGroupid(IntPtr Table)
			{
				return ctdbGetTableGroupid((CTHANDLE)Table);
			}

			static IntPtr GetTableHandle(IntPtr Handle)
			{
				return ctdbGetTableHandle((CTHANDLE) Handle);
			}

			static VRLEN GetTableIndexCount(IntPtr Table)
			{
				return ctdbGetTableIndexCount((CTHANDLE)Table);
			}

			static String* GetTableName(IntPtr Table)
			{
				return ctdbGetTableName((CTHANDLE)Table);
			}

			static NINT GetTableNbr(IntPtr Table)
			{
				return ctdbGetTableNbr((CTHANDLE) Table);
			}

			static OPEN_MODE GetTableOpenMode(IntPtr Table)
			{
				return (OPEN_MODE)ctdbGetTableOpenMode((CTHANDLE)Table);
			}

			static String* GetTableOwner(IntPtr Table)
			{
				return ctdbGetTableOwner((CTHANDLE)Table);
			}

			static String* GetTablePassword(IntPtr Table)
			{
				return ctdbGetTablePassword((CTHANDLE)Table);
			}

			static LONG GetTablePermission(IntPtr Table)
			{
				return ctdbGetTablePermission((CTHANDLE)Table);
			}

			static String* GetTablePath(IntPtr Table)
			{
				return ctdbGetTablePath((CTHANDLE)Table);
			}

			static TABLE_STATUS GetTableStatus(IntPtr Table)
			{
				return (TABLE_STATUS)ctdbGetTableStatus((CTHANDLE) Table);
			}

			static TABLE_TYPE GetTableType(IntPtr Table)
			{
				return (TABLE_TYPE)ctdbGetTableType((CTHANDLE) Table);
			}

			static CTDBRET GetTableUID(IntPtr Database, String* TableName, [Out] unsigned __int64 __gc* Uid)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(TableName);
				ULONG ptr;
				ret = ctdbGetTableUID((CTHANDLE)Database, (pTEXT)name.ToPointer(), &ptr);
				Marshal::FreeHGlobal(name);
				*Uid = (ULONG)ptr;
				return ret;
			}

			static NINT GetTableCount(IntPtr Database)
			{
				return ctdbGetTableCount((CTHANDLE)Database);
			}

			static BEGIN_MODE GetTransactionMode(IntPtr Handle)
			{
				return (BEGIN_MODE)ctdbGetTransactionMode((CTHANDLE)Handle);
			}

			static String* GetUserLogonName(IntPtr Session)
			{
				return ctdbGetUserLogonName((CTHANDLE)Session);
			}
			
			static String* GetUserPassword(IntPtr Session)
			{
				return ctdbGetUserPassword((CTHANDLE)Session);
			}

			static CTDBRET GetUserTag(IntPtr Handle, [Out]IntPtr* TagPtr)
			{
				void* ptr;
				CTDBRET ret = ctdbGetUserTag((CTHANDLE)Handle, &ptr);
				*TagPtr = ptr;
				return ret;
			}

			static bool HasDelField(IntPtr Handle)
			{
				return ctdbHasDelField((CTHANDLE) Handle);
			}

			static NINT GetYear(CTDATE Date)
			{
				return ctdbGetYear(Date);
			}

			static bool HasNullFieldSupport(IntPtr Table)
			{
				return ctdbHasNullFieldSupport((CTHANDLE) Table);
			}

			static bool HasRecbyt(IntPtr Table)
			{
				return ctdbHasRecbyt((CTHANDLE) Table);
			}

			static bool HasRowid(IntPtr Table)
			{
				return ctdbHasRowid((CTHANDLE) Table);
			}

			static IntPtr InsField(IntPtr Table, NINT BeforeField, String* Name,  FIELD_TYPE Type, VRLEN Length)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				CTHANDLE pField = ctdbInsField((CTHANDLE)Table, BeforeField, (pTEXT)name.ToPointer(), (CTDBTYPE)Type, Length);
				Marshal::FreeHGlobal(name);
				return pField;
			}

			static IntPtr InsFieldByName(IntPtr Table, String* BeforeField, String* Name, FIELD_TYPE Type, VRLEN Length)
			{
				IntPtr before = Marshal::StringToHGlobalAnsi(BeforeField);
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				CTHANDLE pField = ctdbInsFieldByName((CTHANDLE)Table, (pTEXT)before.ToPointer(), (pTEXT)name.ToPointer(), (CTDBTYPE)Type, Length);
				Marshal::FreeHGlobal(name);
				Marshal::FreeHGlobal(before);
				return pField;
			}
			static IntPtr InsSegment(IntPtr Index, NINT BeforeSegment, IntPtr FieldHandle, SEG_MODE SegMode)
			{
			    return ctdbInsSegment((CTHANDLE)Index, BeforeSegment, (CTHANDLE)FieldHandle, (CTSEG_MODE)SegMode);
			}

			static IntPtr InsSegmentByName(IntPtr Table, NINT IndexNbr, NINT SegNumber, String* FieldName, SEG_MODE SegMode)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(FieldName);
				CTHANDLE ret = ctdbInsSegmentByName((CTHANDLE) Table, IndexNbr, SegNumber, (pTEXT)name.ToPointer(), (CTSEG_MODE) SegMode);
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static IntPtr InsSegmentByNbr(IntPtr Table, NINT IndexNbr, NINT SegNumber, NINT FieldNbr, SEG_MODE SegMode)
			{
				return ctdbInsSegmentByNbr((CTHANDLE) Table, IndexNbr, SegNumber, FieldNbr, (CTSEG_MODE) SegMode);
			}

			static IntPtr InsSegmentEx(IntPtr Index, NINT BeforeSegment, NINT Offset, NINT Length, SEG_MODE SegMode)
			{
			    return ctdbInsSegmentEx((CTHANDLE) Index, BeforeSegment, Offset, Length, (CTSEG_MODE)SegMode);
			}

			static bool IsActiveDatabase(IntPtr Database)
			{
				return (ctdbIsActiveDatabase((CTHANDLE)Database)!=0);
			}

			static bool IsActiveSession(IntPtr Session)
			{
				return (ctdbIsActiveSession((CTHANDLE)Session)!=0);
			}

			static bool IsActiveTable(IntPtr Table)
			{
				return (ctdbIsActiveTable((CTHANDLE)Table)!=0);
			}

			static bool IsDatabaseExclusive(IntPtr Database)
			{
				return ctdbIsDatabaseExclusive((CTHANDLE)Database);
			}

			static bool IsFieldDefaultValueSet(IntPtr Field)
			{
				return ctdbIsFieldDefaultValueSet((CTHANDLE)Field);
			}

			static bool IsFieldNumeric(IntPtr Field)
			{
				return ctdbIsFieldNumeric((CTHANDLE)Field);
			}

			static bool IsLockActive(IntPtr Session)
			{
				return (ctdbIsLockActive((CTHANDLE)Session)!=0);
			}

			static bool IsEditedRecord(IntPtr Record)
			{
			    return ctdbIsEditedRecord((CTHANDLE) Record);
			}

			static bool IsExtSegment(SEG_MODE SegMode)
			{
				return ctdbIsExtSegment((CTSEG_MODE) SegMode);
			}

			static bool IsFilteredRecord(IntPtr Record)
			{
				return ctdbIsFilteredRecord((CTHANDLE) Record);
			}

			static bool IsLeapYear(CTDATE Date)
			{
			    return ctdbIsLeapYear(Date);
			}

			static bool IsNewRecord(IntPtr Record)
			{
			    return ctdbIsNewRecord((CTHANDLE) Record);
			}

			static bool IsNullField(IntPtr Record, NINT FieldNumber)
			{
				return ctdbIsNullField((CTHANDLE) Record, FieldNumber);
			}

			static bool IsNumberZero(ctdbNUMBER Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ctN2CTN(&Number, num);
				return ctdbIsNumberZero(num);
			}

			static bool IsRecordRangeOn(IntPtr Record)
			{
				return ctdbIsRecordRangeOn((CTHANDLE) Record);
			}

			static bool IsRecordSetOn(IntPtr Record)
			{
				return ctdbIsRecordSetOn((CTHANDLE) Record);
			}

			static bool IsResourceLocked(IntPtr Resource)
			{
				return ctdbIsResourceLocked((CTHANDLE) Resource);
			}

			static bool IsSessionExclusive(IntPtr Session)
			{
				return ctdbIsSessionExclusive((CTHANDLE) Session);
			}

			static bool IsSQLDatabase(IntPtr Database)
			{
				return ctdbIsSQLDatabase((CTHANDLE) Database);
			}

			static bool IsSQLServer(IntPtr Session)
			{
				return ctdbIsSQLServer((CTHANDLE) Session);
			}

			static bool IsTransActive(IntPtr Session)
			{
				return (ctdbIsTransActive((CTHANDLE)Session)!=0);
			}

			static bool IsVariableField(IntPtr Record, NINT FieldNbr)
			{
				return ctdbIsVariableField((CTHANDLE) Record, FieldNbr);
			}
			
			static bool IsUnicodeLib()
			{
#ifdef ctUNICODE
				return true;
#else
				return false;
#endif
			}

			static CTDBRET LastRecord(IntPtr Record)
			{
				return ctdbLastRecord((CTHANDLE)Record);
			}

			static CTDBRET Lock(IntPtr Handle, LOCK_MODE Mode)
			{
				return ctdbLock((CTHANDLE)Handle, (CTLOCK_MODE)Mode);
			}

			static CTDBRET LockRecord(IntPtr Record, LOCK_MODE Mode)
			{
				return ctdbLockRecord((CTHANDLE)Record, Mode);
			}

			static CTDBRET Logon(IntPtr Session, String* DbEngine, String* UserId, String* Password)
			{
				IntPtr db = Marshal::StringToHGlobalAnsi(DbEngine);
				IntPtr user = Marshal::StringToHGlobalAnsi(UserId);
				IntPtr pass = Marshal::StringToHGlobalAnsi(Password);
				ret = ctdbLogon((CTHANDLE)Session,(pTEXT)db.ToPointer(),(pTEXT)user.ToPointer(),(pTEXT)pass.ToPointer());
				Marshal::FreeHGlobal(pass);
				Marshal::FreeHGlobal(user);
				Marshal::FreeHGlobal(db);
				return ret;
			}

			static CTDBRET Logout(IntPtr Session)
			{
				return ctdbLogout((CTHANDLE)Session);
			}

			static CTDBRET LongToBigInt(__int64 Long, [Out] CTBIGINT __gc* BigInt)
			{
				CTBIGINT big;
				ret = ctdbLongToBigInt(Long, &big);
				*BigInt = big;
				return ret;
			}

			static CTDBRET LongToCurrency(__int64 Long, [Out] CTCURRENCY __gc* Currency)
			{
				CTCURRENCY cur;
				ret = ctdbLongToCurrency(Long, &cur);
				*Currency = cur;
				return ret;
			}

			static CTDBRET LongToNumber(__int64 Long, [Out]ctdbNUMBER __gc *Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ret = ctdbLongToNumber(Long, num);
				CTN2ctN(num,Number);
				return ret;
			}

			static CTDBRET LongToMoney(__int64 Long, [Out]CTMONEY __gc *Money)
			{
				CTMONEY money;
				ret = ctdbLongToMoney(Long, &money);
				*Money = money;
				return ret;
			}

			static CTMONEY MoneyAbs(CTMONEY Money)
			{
				return ctdbMoneyAbs(Money);
			}

			static CTDBRET MoneyAdd(CTMONEY Left, CTMONEY Right, [Out]CTMONEY __gc* Retval)
			{
				CTMONEY retval;
				ret = ctdbMoneyAdd(Left, Right, &retval);
				*Retval = retval;
				return ret;
			}

			static NINT MoneyCmp(CTMONEY Left, CTMONEY Right)
			{
			    return ctdbMoneyCmp(Left, Right);
			}

			static CTDBRET MoneyDiv(CTMONEY Left, CTMONEY Right, [Out]CTMONEY __gc* Retval)
			{
				CTMONEY retval;
				ret = ctdbMoneyDiv(Left, Right, &retval);
				*Retval = retval;
				return ret;
			}

			static CTDBRET MoneyMul(CTMONEY Left, CTMONEY Right, [Out]CTMONEY __gc* Retval)
			{
				CTMONEY retval;
				ret = ctdbMoneyMul(Left, Right, &retval);
				*Retval = retval;
				return ret;
			}

			static CTDBRET MoneySub(CTMONEY Left, CTMONEY Right, [Out]CTMONEY __gc* Retval)
			{
				CTMONEY retval;
				ret = ctdbMoneySub(Left, Right, &retval);
				*Retval = retval;
				return ret;
			}

			static CTDBRET MoneyToCurrency(CTMONEY Money, [Out] CTCURRENCY __gc* Currency)
			{
				CTCURRENCY cur;
				ret = ctdbMoneyToCurrency(Money, &cur);
				*Currency = cur;
				return ret;
			}

			static CTDBRET MoneyToFloat(CTMONEY Money, [Out] float __gc* Value)
			{
				CTFLOAT val;
				ret = ctdbMoneyToFloat(Money, &val);
				*Value = val;
				return ret;
			}

			static CTDBRET MoneyToLong(CTMONEY Money, [Out] __int64 __gc* Value)
			{
				LONG val;
				ret = ctdbMoneyToLong(Money, &val);
				*Value = val;
				return ret;
			}

			static CTDBRET MoneyToNumber(CTMONEY Value, [Out]ctdbNUMBER __gc *Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ret = ctdbMoneyToNumber(Value, num);
				CTN2ctN(num,Number);
				return ret;
			}

			static CTDBRET MoneyToString(CTMONEY Money, StringBuilder* Buffer, VRLEN BufferSize)
			{
		        char __pin * buf = new char[BufferSize];
				memset(buf,0,BufferSize);
				ret = ctdbMoneyToString(Money, buf, BufferSize);
				Buffer->Length=0;
				if (!ret)
				{
					Buffer->Insert(0,buf);
				}
				delete[] buf;
				return ret;
			}

			static CTDBRET MoveField(IntPtr Field, NINT NewIndex)
			{
				return ctdbMoveField((CTHANDLE)Field, NewIndex);
			}

			static CTDBRET MoveSegment(IntPtr Segment, NINT NewIndex)
			{
				return ctdbMoveSegment((CTHANDLE)Segment, NewIndex);
			}

			static CTDBRET NextDatabase(IntPtr Session, StringBuilder* Name, VRLEN NameSize, StringBuilder* Path, VRLEN PathSize)
			{
		        char __pin * pName = new char[NameSize];
				memset(pName,0,NameSize);
				char __pin * pPath = new char[PathSize];
				memset(pPath,0,PathSize);
				ret = ctdbNextDatabase((CTHANDLE)Session, pName, NameSize, pPath, PathSize);
				Name->Length = 0;
				Path->Length = 0;
				if (!ret)
				{
					Name->Insert(0,pName);
					Path->Insert(0,pPath);
				}
				delete[] pName;
				delete[] pPath;
				return ret;
			}

			static CTDBRET NextRecord(IntPtr Record)
			{
				return ctdbNextRecord((CTHANDLE)Record);
			}

			static CTDBRET NextResource(IntPtr resource, bool lock)
			{
				return ctdbNextResource((CTHANDLE) resource, lock);
			}

			static CTDBRET NextTable(IntPtr Database,StringBuilder *Name, VRLEN NameSize, StringBuilder *Path, VRLEN PathSize)
			{
				char __pin * pName = new char[NameSize];
				memset(pName,0,NameSize);
				char __pin * pPath = new char[PathSize];
				memset(pPath,0,PathSize);
				ret = ctdbNextTable((CTHANDLE)Database, pName, NameSize, pPath, PathSize);
				Name->Length = 0;
				Path->Length = 0;
				if (!ret)
				{
					Name->Insert(0,pName);
					Path->Insert(0,pPath);
				}
				delete[] pName;
				delete[] pPath;
				return ret;
			}

			static CTDBRET NumberAbs(ctdbNUMBER Source, [Out]ctdbNUMBER __gc* Result)
			{
				CTNUMBER __pin * source = new CTNUMBER;
				CTNUMBER __pin * result = new CTNUMBER;
				ctN2CTN(&Source, source);
				ctN2CTN(Result, result);
				ret = ctdbNumberAbs(source, result);
				CTN2ctN(result, Result);
				return ret;
			}

			static CTDBRET NumberAdd(ctdbNUMBER Left, ctdbNUMBER Right, [Out] ctdbNUMBER __gc* Dest)
			{
				CTNUMBER __pin * left = new CTNUMBER;
				CTNUMBER __pin * right = new CTNUMBER;
				CTNUMBER __pin * dest = new CTNUMBER;
				ctN2CTN(&Left, left);
				ctN2CTN(&Right, right);
				ctN2CTN(Dest, dest);
				ret = ctdbNumberAdd(left, right, dest); 
				CTN2ctN(dest, Dest);
				return ret;
			}

			static NINT NumberCmp(ctdbNUMBER Left, ctdbNUMBER Right)
			{
				CTNUMBER __pin * left = new CTNUMBER;
				CTNUMBER __pin * right = new CTNUMBER;
				ctN2CTN(&Left, left);
				ctN2CTN(&Right, right);
				return ctdbNumberCmp(left, right);
			}

			static CTDBRET NumberCopy([Out] ctdbNUMBER __gc* Dest, ctdbNUMBER Source)
			{
				CTNUMBER __pin * dest = new CTNUMBER;
				CTNUMBER __pin * source = new CTNUMBER;
				ctN2CTN(Dest, dest);
				ctN2CTN(&Source, source);
				ret = ctdbNumberCopy(dest, source); 
				CTN2ctN(dest, Dest);
				return ret;
			}

			static CTDBRET NumberDiv(ctdbNUMBER Left, ctdbNUMBER Right, [Out] ctdbNUMBER __gc* Dest)
			{
				CTNUMBER __pin * left = new CTNUMBER;
				CTNUMBER __pin * right = new CTNUMBER;
				CTNUMBER __pin * dest = new CTNUMBER;
				ctN2CTN(&Left, left);
				ctN2CTN(&Right, right);
				ctN2CTN(Dest, dest);
				ret = ctdbNumberDiv(left, right, dest); 
				CTN2ctN(dest, Dest);
				return ret;
			}

			static CTDBRET NumberGetDecimal(ctdbNUMBER Number, [Out] NINT __gc* Before, [Out] NINT __gc* After)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				NINT before, after;
				ctN2CTN(&Number, num);
				ret = ctdbNumberGetDecimal(num, &before, &after);
				*Before = before;
				*After = after;
				return ret;
			}

			static CTDBRET NumberMul(ctdbNUMBER Left, ctdbNUMBER Right, [Out] ctdbNUMBER __gc* Dest)
			{
				CTNUMBER __pin * left = new CTNUMBER;
				CTNUMBER __pin * right = new CTNUMBER;
				CTNUMBER __pin * dest = new CTNUMBER;
				ctN2CTN(&Left, left);
				ctN2CTN(&Right, right);
				ctN2CTN(Dest, dest);
				ret = ctdbNumberMul(left, right, dest); 
				CTN2ctN(dest, Dest);
				return ret;
			}

			static CTDBRET NumberNegate(ctdbNUMBER Source, [Out] ctdbNUMBER __gc* Result)
			{
				CTNUMBER __pin * source = new CTNUMBER;
				CTNUMBER __pin * result = new CTNUMBER;
				ctN2CTN(&Source, source);
				ctN2CTN(Result, result);
				ret = ctdbNumberNegate(source, result);
				CTN2ctN(result, Result);
				return ret;
			}

			static LONG NumberOfKeyEntries(IntPtr Record, NINT index)
			{
				return ctdbNumberOfKeyEntries((CTHANDLE) Record, index);
			}

			static CTDBRET NumberSub(ctdbNUMBER Left, ctdbNUMBER Right, [Out] ctdbNUMBER __gc* Dest)
			{
				CTNUMBER __pin * left = new CTNUMBER;
				CTNUMBER __pin * right = new CTNUMBER;
				CTNUMBER __pin * dest = new CTNUMBER;
				ctN2CTN(&Left, left);
				ctN2CTN(&Right, right);
				ctN2CTN(Dest, dest);
				ret = ctdbNumberSub(left, right, dest); 
				CTN2ctN(dest, Dest);
				return ret;
			}

			static CTDBRET NumberToBigInt(ctdbNUMBER Number, [Out] __int64 __gc* Bigint)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				CTBIGINT val;
				ctN2CTN(&Number, num);
				ret = ctdbNumberToBigInt(num, &val);
				*Bigint = val;
				return ret;
			}

			static CTDBRET NumberToCurrency(ctdbNUMBER Number, [Out] CTCURRENCY __gc* Currency)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				CTCURRENCY val;
				ctN2CTN(&Number, num);
				ret = ctdbNumberToCurrency(num, &val);
				*Currency = val;
				return ret;
			}

			static CTDBRET NumberToFloat(ctdbNUMBER Number, [Out] float __gc* Float)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				CTFLOAT val;
				ctN2CTN(&Number, num);
				ret = ctdbNumberToFloat(num, &val);
				*Float = val;
				return ret;
			}

			static CTDBRET NumberToLong(ctdbNUMBER Number, [Out] __int64 __gc* Long)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				long val;
				ctN2CTN(&Number, num);
				ret = ctdbNumberToLong(num, &val);
				*Long = val;
				return ret;
			}

			static CTDBRET NumberToMoney(ctdbNUMBER Number, [Out] CTMONEY __gc* Money)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				CTMONEY val;
				ctN2CTN(&Number, num);
				ret = ctdbNumberToMoney(num, &val);
				*Money = val;
				return ret;
			}

			static CTDBRET NumberToString(ctdbNUMBER Number, StringBuilder* Buffer, VRLEN BufferSize)
			{
		        char __pin * buf = new char[BufferSize];
				memset(buf,0,BufferSize);
				CTNUMBER __pin * num = new CTNUMBER;
				ctN2CTN(&Number, num);
				ret = ctdbNumberToString(num, buf, BufferSize);
				Buffer->Length=0;
				if (!ret)
				{
					Buffer->Insert(0,buf);
				}
				delete[] buf;
				return ret;
			}

			static CTDBRET NumberRound(ctdbNUMBER __gc* Number, NINT Scale)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ctN2CTN(Number, num);
				ret = ctdbNumberRound(num, Scale);
				CTN2ctN(num, Number);
				return ret;
			}

			static CTDBRET NumberZero(ctdbNUMBER __gc* Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ctN2CTN(Number, num);
				ret = ctdbNumberZero(num);
				CTN2ctN(num, Number);
				return ret;
			}

			static CTDBRET OpenTable(IntPtr Table, String* TableName, OPEN_MODE Mode)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(TableName);
				ret = ctdbOpenTable((CTHANDLE)Table, (pTEXT)name.ToPointer(), (CTOPEN_MODE)Mode);
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET PrevRecord(IntPtr Record)
			{
				return ctdbPrevRecord((CTHANDLE) Record);
			}

			static CTDBRET ReadRecord(IntPtr Record)
			{
				return ctdbReadRecord((CTHANDLE) Record);
			}

			static CTDBRET RebuildTable(IntPtr Table, REBUILD_MODE mode)
			{
				return ctdbRebuildTable((CTHANDLE) Table, (CTREBUILD_MODE)mode);
			}

			static CTDBRET RecordAtPercentile(IntPtr Handle, NINT Percent)
			{
				return ctdbRecordAtPercentile((CTHANDLE)Handle, Percent);
			}

			static CTDBRET RecordRangeOn(IntPtr Record,	NINT SegCount, IntPtr lRange, IntPtr uRange, RANGE_OP Operators __gc[])
			{
				int __pin * ops = new int[SegCount];
				for(int i=0 ; i<SegCount ; i++)
				{
					ops[i] = Operators[i];
				}
				ret = ctdbRecordRangeOn((CTHANDLE) Record, SegCount, (pVOID) lRange, (pVOID) uRange, ops);
				delete[] ops;
				return ret;
			}

			static CTDBRET RecordRangeOff(IntPtr Record)
			{
				return ctdbRecordRangeOff((CTHANDLE) Record);
			}

			static CTDBRET RecordSetOn(IntPtr Record, NINT SigLen)
			{
				return ctdbRecordSetOn((CTHANDLE) Record, SigLen);
			}

			static CTDBRET RecordSetOff(IntPtr Record)
			{
				return ctdbRecordSetOff((CTHANDLE) Record);
			}

			static CTDBRET RemoveTable(IntPtr Table)
			{
				return ctdbRemoveTable((CTHANDLE) Table);
			}

			static CTDBRET RenameTable(IntPtr Database ,String* OldName,String* NewName)
			{
				IntPtr oldName = Marshal::StringToHGlobalAnsi(OldName);
				IntPtr newName = Marshal::StringToHGlobalAnsi(NewName);
				ret = ctdbRenameTable((CTHANDLE)Database, (pTEXT)oldName.ToPointer(), (pTEXT)newName.ToPointer());
				Marshal::FreeHGlobal(oldName);
				Marshal::FreeHGlobal(newName);
				return ret;

			}

			static CTDBRET ResetAll(IntPtr Table)
			{
				return ctdbResetAll((CTHANDLE) Table);
			}

			static CTDBRET ResetRecord(IntPtr Record)
			{
				return ctdbResetRecord((CTHANDLE)Record);
			}

			static CTDBRET RestoreSavePoint(IntPtr Session, NINT SavePoint)
			{
				return ctdbRestoreSavePoint((CTHANDLE)Session, SavePoint);
			}

			static CTDBRET SeekRecord(IntPtr Record, [In]__int64 Offset)
			{
				return ctdbSeekRecord((CTHANDLE)Record, Offset);
			}

			static CTDBRET SetAutoCommit(IntPtr Handle, bool flag)
			{
				return ctdbSetAutoCommit((CTHANDLE) Handle, flag);
			}

			static CTDBRET SetCurrentNodeName(IntPtr Session, String* NodeName)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(NodeName);
				ret = ctdbSetCurrentNodeName((CTHANDLE) Session, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET SetDefaultIndex(IntPtr Record, NINT IndexNo)
			{
				return ctdbSetDefaultIndex((CTHANDLE)Record, IndexNo);
			}

			static CTDBRET SetDefaultIndexByName(IntPtr Record, String* Name)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				ret = ctdbSetDefaultIndexByName((CTHANDLE)Record, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET SetDefaultSqlTableOwner(IntPtr Handle, String* Owner)
			{
				IntPtr owner = Marshal::StringToHGlobalAnsi(Owner);
				ret = ctdbSetDefaultSqlTableOwner((CTHANDLE) Handle, (pTEXT)owner.ToPointer());
				Marshal::FreeHGlobal(owner);
				return ret;
			}		

			static CTDBRET SetDefDateType(IntPtr Handle, DATE_TYPE DateType)
			{
				return ctdbSetDefDateType((CTHANDLE)Handle, (CTDATE_TYPE)DateType);
			}

			static CTDBRET SetDefFloatFormat(IntPtr Handle, String* Format)
			{
				IntPtr format = Marshal::StringToHGlobalAnsi(Format);
				ret = ctdbSetDefFloatFormat((CTHANDLE)Handle,(pTEXT)format.ToPointer());
				Marshal::FreeHGlobal(format);
				return ret;
			}

			static CTDBRET SetDefTimeType(IntPtr Handle, TIME_TYPE DateType)
			{
				return ctdbSetDefTimeType((CTHANDLE)Handle, (CTTIME_TYPE)DateType);
			}

			static CTDBRET SetEditedRecord(IntPtr Record, bool Flag)
			{
				return ctdbSetEditedRecord((CTHANDLE)Record, Flag);
			}

			static CTDBRET SetError(IntPtr Handle, CTDBRET Error)
			{
				return ctdbSetError((CTHANDLE)Handle, Error);
			}
	
			static CTDBRET SetDatabaseExclusive(IntPtr Database, bool Flag)
			{
				return ctdbSetDatabaseExclusive((CTHANDLE)Database, Flag);
			}

			static CTDBRET SetFieldDefaultValue(IntPtr Handle, String* Value, VRLEN Length)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(Value);
				ret = ctdbSetFieldDefaultValue((CTHANDLE)Handle, (pTEXT)st.ToPointer(), Length);
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetFieldDefaultDateTimeType(IntPtr Handle, DATE_TYPE DateType, TIME_TYPE TimeType)
			{
				return ctdbSetFieldDefaultDateTimeType((CTHANDLE) Handle, (CTDATE_TYPE) DateType, (CTTIME_TYPE) TimeType);
			}

			static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNumber, CTBIGINT Bigint)
			{
				return ctdbSetFieldAsBigint((CTHANDLE)Record, FieldNumber, Bigint);
			}

			static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNumber, CTUBIGINT Bigint)
			{
				return ctdbSetFieldAsUnsignedBigint((CTHANDLE)Record, FieldNumber, Bigint);
			}

			static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNbr, IntPtr pData, VRLEN size)
			{
				return ctdbSetFieldAsBinary((CTHANDLE) Record, FieldNbr, (pVOID) pData, size);
			}

			static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNbr, ctdbBLOB pBlob)
			{
				CTBLOB __pin * blob = new CTBLOB;
				blob->data = pBlob.data;
				blob->size = pBlob.size;
				blob->allocated = pBlob.allocated;
				return ctdbSetFieldAsBlob((CTHANDLE) Record, FieldNbr, blob);
			}

			static CTDBRET SetFieldValue(IntPtr Handle, NINT FieldNbr, Byte arr __gc[])
			{
				CTBLOB __pin * blob = new CTBLOB;
				blob->size = arr->Length;
				GCHandle gch = GCHandle::Alloc( arr, GCHandleType::Pinned);
				blob->data = (pUTEXT)gch.AddrOfPinnedObject().ToPointer();
				ret = ctdbSetFieldAsBlob((CTHANDLE) Handle, FieldNbr, blob);
				gch.Free();
				return ret;
			}

			static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNumber, bool Bool)
			{
				return ctdbSetFieldAsBool((CTHANDLE)Record, FieldNumber, Bool);
			}

		    static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNumber, CTDATETIME DateTime)
			{
				return ctdbSetFieldAsDateTime((CTHANDLE)Record, FieldNumber, DateTime);
			}

			static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNumber, float Float)
			{
				return ctdbSetFieldAsFloat((CTHANDLE)Record, FieldNumber, Float);
			}

		    static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNumber, ctdbNUMBER Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ctN2CTN(&Number,num);
				return ctdbSetFieldAsNumber((CTHANDLE)Record, FieldNumber, num);
			}

			static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNumber, long Signed)
			{
				return ctdbSetFieldAsSigned((CTHANDLE)Record, FieldNumber, Signed);
			}

		    static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNumber, String* Buffer)
			{
#ifdef ctUNICODE
				FIELD_TYPE type = GetFieldType(FieldNumber);
				if(type == FIELD_TYPE::F2UNICODE || type == FIELD_TYPE::V2UNICODE)
				{
					IntPtr st = Marshal::StringToHGlobalUni(Buffer);
					ret = ctdbSetFieldAsUTF16((CTHANDLE)Record, FieldNumber, (pWCHAR)st.ToPointer());
					Marshal::FreeHGlobal(st);
				}
				else
				{
					IntPtr st = Marshal::StringToHGlobalAnsi(Buffer);
					ret = ctdbSetFieldAsString((CTHANDLE)Record, FieldNumber, (pTEXT)st.ToPointer());
					Marshal::FreeHGlobal(st);
				}
#else
				IntPtr st = Marshal::StringToHGlobalAnsi(Buffer);
				ret = ctdbSetFieldAsString((CTHANDLE)Record, FieldNumber, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
#endif
				return ret;
			}

			static CTDBRET SetFieldValue(IntPtr Record, NINT FieldNumber, unsigned long Unsigned)
			{
				return ctdbSetFieldAsUnsigned((CTHANDLE)Record, FieldNumber, Unsigned);
			}

			static CTDBRET SetFieldAsString(IntPtr Record, NINT FieldNumber, String* Buffer)
			{
#ifdef ctUNICODE
				FIELD_TYPE type = GetFieldType(FieldNumber);
				if(type == FIELD_TYPE::F2UNICODE || type == FIELD_TYPE::V2UNICODE)
				{
					IntPtr st = Marshal::StringToHGlobalUni(Buffer);
					ret = ctdbSetFieldAsUTF16((CTHANDLE)Record, FieldNumber, (pWCHAR)st.ToPointer());
					Marshal::FreeHGlobal(st);
				}
				else
				{
					IntPtr st = Marshal::StringToHGlobalAnsi(Buffer);
					ret = ctdbSetFieldAsString((CTHANDLE)Record, FieldNumber, (pTEXT)st.ToPointer());
					Marshal::FreeHGlobal(st);
				}
#else
				IntPtr st = Marshal::StringToHGlobalAnsi(Buffer);
				ret = ctdbSetFieldAsString((CTHANDLE)Record, FieldNumber, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
#endif
				return ret;
			}

#ifdef oldGetSet
		    static CTDBRET SetFieldAsBigint(IntPtr Record, NINT FieldNumber, CTBIGINT Bigint)
			{
				return ctdbSetFieldAsBigint((CTHANDLE)Record, FieldNumber, Bigint);
			}

		    static CTDBRET SetFieldAsUnsignedBigint(IntPtr Record, NINT FieldNumber, CTUBIGINT Bigint)
			{
				return ctdbSetFieldAsUnsignedBigint((CTHANDLE)Record, FieldNumber, Bigint);
			}

			static CTDBRET SetFieldAsBinary(IntPtr Record, NINT FieldNbr, IntPtr pData, VRLEN size)
			{
				return ctdbSetFieldAsBinary((CTHANDLE) Record, FieldNbr, (pVOID) pData, size);
			}

			static CTDBRET SetFieldAsBlob(IntPtr Record, NINT FieldNbr, ctdbBLOB pBlob)
			{
				CTBLOB __pin * blob = new CTBLOB;
				blob->data = pBlob.data;
				blob->size = pBlob.size;
				blob->allocated = pBlob.allocated;
				return ctdbSetFieldAsBlob((CTHANDLE) Record, FieldNbr, blob);
			}

			static CTDBRET SetFieldAsBytes(IntPtr Handle, NINT FieldNbr, Byte arr __gc[])
			{
				CTBLOB __pin * blob = new CTBLOB;
				blob->size = arr->Length;
				GCHandle gch = GCHandle::Alloc( arr, GCHandleType::Pinned);
				blob->data = (pUTEXT)gch.AddrOfPinnedObject().ToPointer();
				ret = ctdbSetFieldAsBlob((CTHANDLE) Handle, FieldNbr, blob);
				gch.Free();
				return ret;
			}

			static CTDBRET SetFieldAsBool(IntPtr Record, NINT FieldNumber, bool Bool)
			{
				return ctdbSetFieldAsBool((CTHANDLE)Record, FieldNumber, Bool);
			}

		    static CTDBRET SetFieldAsCurrency(IntPtr Record, NINT FieldNumber, CTCURRENCY Currency)
			{
				return ctdbSetFieldAsCurrency((CTHANDLE)Record, FieldNumber, Currency);
			}

			static CTDBRET SetFieldAsDate(IntPtr Record, NINT FieldNumber, CTDATE Date)
			{
				return ctdbSetFieldAsDate((CTHANDLE)Record, FieldNumber, Date);
			}

		    static CTDBRET SetFieldAsDateTime(IntPtr Record, NINT FieldNumber, CTDATETIME DateTime)
			{
				return ctdbSetFieldAsDateTime((CTHANDLE)Record, FieldNumber, DateTime);
			}

			static CTDBRET SetFieldAsFloat(IntPtr Record, NINT FieldNumber, float Float)
			{
				return ctdbSetFieldAsFloat((CTHANDLE)Record, FieldNumber, Float);
			}

		    static CTDBRET SetFieldAsMoney(IntPtr Record, NINT FieldNumber, CTMONEY Money)
			{
				return ctdbSetFieldAsMoney((CTHANDLE)Record, FieldNumber, Money);
			}

		    static CTDBRET SetFieldAsNumber(IntPtr Record, NINT FieldNumber, ctdbNUMBER Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				ctN2CTN(&Number,num);
				return ctdbSetFieldAsNumber((CTHANDLE)Record, FieldNumber, num);
			}

			static CTDBRET SetFieldAsSigned(IntPtr Record, NINT FieldNumber, long Signed)
			{
				return ctdbSetFieldAsSigned((CTHANDLE)Record, FieldNumber, Signed);
			}

		    static CTDBRET SetFieldAsTime(IntPtr Record, NINT FieldNumber, CTTIME Time)
			{
				return ctdbSetFieldAsTime((CTHANDLE)Record, FieldNumber, Time);
			}

			static CTDBRET SetFieldAsUnsigned(IntPtr Record, NINT FieldNumber, unsigned long Unsigned)
			{
				return ctdbSetFieldAsUnsigned((CTHANDLE)Record, FieldNumber, Unsigned);
			}

#endif oldGetSet

			static CTDBRET SetFieldLength(IntPtr Field, VRLEN Len)
			{
				return ctdbSetFieldLength((CTHANDLE) Field, Len);
			}

			static CTDBRET SetFieldName(IntPtr Field, String* Name)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(Name);
				ret = ctdbSetFieldName((CTHANDLE) Field, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetFieldNullFlag(IntPtr Field, bool Flag)
			{
				return ctdbSetFieldNullFlag((CTHANDLE)Field, Flag);
			}

			static CTDBRET SetFieldPrecision(IntPtr Field, NINT Precision)
			{
				return ctdbSetFieldPrecision((CTHANDLE)Field, Precision);
			}

			static CTDBRET SetFieldProperties(IntPtr Field, String* FieldName, FIELD_TYPE Type, VRLEN Length)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(FieldName);
				ret = ctdbSetFieldProperties((CTHANDLE)Field, (pTEXT)st.ToPointer(), (CTDBTYPE)Type, Length);
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetFieldScale(IntPtr Field, NINT Scale)
			{
				return ctdbSetFieldScale((CTHANDLE)Field, Scale);
			}

			static CTDBRET SetFieldType(IntPtr Field, FIELD_TYPE Type)
			{
				return ctdbSetFieldType((CTHANDLE) Field, Type);
			}

			static CTDBRET SetIndexDuplicateFlag(IntPtr Index, bool DupFlag)
			{
				return ctdbSetIndexDuplicateFlag((CTHANDLE)Index, DupFlag);
			}

		    static CTDBRET SetIndexEmptyChar(IntPtr Index, NINT EmptyChar)
			{
				return ctdbSetIndexEmptyChar((CTHANDLE)Index, EmptyChar);
			}

			static CTDBRET SetIndexExtension(IntPtr Index, String* Ext)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(Ext);
				ret = ctdbSetIndexExtension((CTHANDLE)Index, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetIndexFilename(IntPtr Index, String* Path, String* Filename)
			{
				IntPtr path = Marshal::StringToHGlobalAnsi(Path);
				IntPtr filename = Marshal::StringToHGlobalAnsi(Filename);
				ret = ctdbSetIndexFilename((CTHANDLE)Index, (pTEXT)path.ToPointer(), (pTEXT)filename.ToPointer());
				Marshal::FreeHGlobal(path);
				Marshal::FreeHGlobal(filename);
				return ret;
			}

			static CTDBRET SetIndexKeyType(IntPtr Index, KEY_TYPE KeyType)
			{
				return ctdbSetIndexKeyType((CTHANDLE) Index, KeyType);
			}

			static CTDBRET SetIndexName(IntPtr Index, String* IndexName)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(IndexName);
				ret = ctdbSetIndexName((CTHANDLE)Index, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetIndexNullFlag(IntPtr Index, bool NullFlag)
			{
				return ctdbSetIndexNullFlag((CTHANDLE)Index, NullFlag);
			}

			static CTDBRET SetIndexTemporaryFlag(IntPtr Index, bool TempFlag)
			{
				return ctdbSetIndexTemporaryFlag((CTHANDLE)Index, TempFlag);
			}

			static CTDBRET SetKeepLock(IntPtr Handle, KEEP_MODE mode)
			{
				return ctdbSetKeepLock((CTHANDLE)Handle, (CTKEEP_MODE)mode);
			}

			static CTDBRET SetLogonOnly(IntPtr Session,bool Flag)
			{
				return ctdbSetLogonOnly((CTHANDLE)Session, Flag);
			}

			static CTDBRET SetNewRecord(IntPtr Record, bool Flag)
			{
				return ctdbSetNewRecord((CTHANDLE)Record, Flag);
			}

			static CTDBRET SetOperationState(IntPtr Handle, OPS_MODE mode, OPS_STATE state)
			{
				return ctdbSetOperationState((CTHANDLE) Handle, mode, state);
			}

			static CTDBRET SetPadChar(IntPtr Handle, NINT padchar, NINT dmlchar)
			{
				return ctdbSetPadChar((CTHANDLE) Handle, padchar, dmlchar);
			}

			static CTDBRET SetPathPrefix(IntPtr Session, String* Path)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(Path);
				ret = ctdbSetPathPrefix((CTHANDLE)Session, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetRecordOffset(IntPtr Record, [In]__int64 Offset)
			{
				return ctdbSetRecordOffset((CTHANDLE)Record, Offset);
			}

			static CTDBRET SetRecordPos(IntPtr Record, [In]__int64 Offset)
			{
				return ctdbSetRecordPos((CTHANDLE)Record, Offset);
			}

			static CTDBRET SetResourceData(IntPtr resource, Byte data __gc[])
			{
				long size = data->Length;
				GCHandle gch = GCHandle::Alloc( data, GCHandleType::Pinned);
				ret = ctdbSetResourceData((CTHANDLE)resource, gch.AddrOfPinnedObject().ToPointer(), size);
				gch.Free();
				return ret;
			}

			static CTDBRET SetResourceName(IntPtr Resource, String* Name)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(Name);
				ret = ctdbSetResourceName((CTHANDLE) Resource, (pTEXT)name.ToPointer());
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET SetResourceNumber(IntPtr Resource, ULONG Number)
			{
				return ctdbSetResourceNumber((CTHANDLE) Resource, Number);
			}

			static CTDBRET SetResourceType(IntPtr Resource, ULONG Type)
			{
				return ctdbSetResourceType((CTHANDLE) Resource, Type);
			}

			static NINT SetSavePoint(IntPtr Session)
			{
				return ctdbSetSavePoint((CTHANDLE)Session);
			}

			static CTDBRET SetSegmentField(IntPtr Segment, IntPtr Field)
			{
				return ctdbSetSegmentField((CTHANDLE)Segment, (CTHANDLE)Field);
			}

			static CTDBRET SetSegmentMode(IntPtr Segment, SEG_MODE SegMode)
			{
				return ctdbSetSegmentMode((CTHANDLE)Segment, SegMode);
			}
			
			static CTDBRET SetSessionExclusive(IntPtr Session, bool Flag)
			{
				return ctdbSetSessionExclusive((CTHANDLE)Session, Flag);
			}

			static CTDBRET SetSessionParams(IntPtr Session, SESSION_PARAM Param,NINT Value)
			{
				return ctdbSetSessionParams((CTHANDLE)Session, (CTSESSION_PARAM)Param, Value);
			}

			static CTDBRET SetSessionPath(IntPtr Session, String* Path)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(Path);
				ret = ctdbSetSessionPath((CTHANDLE)Session, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetSessionType(IntPtr Session, SESSION_TYPE SessionType)
			{
				return ctdbSetSessionType((CTHANDLE)Session, (CTSESSION_TYPE)SessionType);
			}

			static CTDBRET SetTableDefaultDataExtentSize(IntPtr Table, NINT Size)
			{
				return ctdbSetTableDefaultDataExtentSize((CTHANDLE)Table, Size);
			}

			static CTDBRET SetTableDefaultIndexExtentSize(IntPtr Table, NINT Size)
			{
				return ctdbSetTableDefaultIndexExtentSize((CTHANDLE)Table, Size);
			}

			static CTDBRET SetTableExtension(IntPtr Table,String* Ext)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(Ext);
				ret = ctdbSetTableExtension((CTHANDLE)Table, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetTableGroupid(IntPtr Table,String* GroupId)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(GroupId);
				ret = ctdbSetTableGroupid((CTHANDLE)Table, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetTableOwner(IntPtr Table, String* Owner)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(Owner);
				ret = ctdbSetTableOwner((CTHANDLE)Table, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetTablePassword(IntPtr Table, String* Password)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(Password);
				ret = ctdbSetTablePassword((CTHANDLE)Table, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetTablePath(IntPtr Table, String* Path)	
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(Path);
				ret = ctdbSetTablePath((CTHANDLE)Table, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET SetTablePermission(IntPtr Table, LONG PermMask)
			{
				return ctdbSetTablePermission((CTHANDLE)Table, PermMask);
			}

			static CTDBRET SetTransactionMode(IntPtr Handle, BEGIN_MODE Mode)
			{
				return ctdbSetTransactionMode((CTHANDLE)Handle, (CTBEGIN_MODE)Mode);
			}

			static CTDBRET SetUserTag(IntPtr Handle, [In]IntPtr TagPtr)
			{
				void* ptr = (void*)TagPtr;
				return ctdbSetUserTag((CTHANDLE)Handle, ptr);
			}

			static CTDBRET SetConfigurationFile(String* ConfigFile)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(ConfigFile);
				ret = ctdbSetConfigurationFile((pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET StartDatabaseEngine(void)
			{
				return ctdbStartDatabaseEngine();
			}

			static void StopDatabaseEngine(void)
			{
				ctdbStopDatabaseEngine();
			}

			static int AcquireSessionId(void)
			{
				return ctdbAcquireSessionId();
			}

			static int GetSessionId(IntPtr Session)
			{
				return ctdbGetSessionId((CTHANDLE) Session);
			}

			static void SetSessionId(IntPtr Session, int sessid)
			{
				ctdbSetSessionId((CTHANDLE) Session, sessid);
			}

			static CTDBRET StringToBigInt(String* Str, [Out] CTBIGINT __gc* BigInt)
			{
				CTBIGINT big;
				IntPtr st = Marshal::StringToHGlobalAnsi(Str);
				ret = ctdbStringToBigInt((pTEXT)st.ToPointer(), &big);
				Marshal::FreeHGlobal(st);
				*BigInt = big;
				return ret;
			}

			static CTDBRET StringToCurrency(String* Str, [Out] CTCURRENCY __gc* Currency)
			{
				CTCURRENCY cur;
				IntPtr st = Marshal::StringToHGlobalAnsi(Str);
				ret = ctdbStringToCurrency((pTEXT)st.ToPointer(), &cur);
				Marshal::FreeHGlobal(st);
				*Currency = cur;
				return ret;
			}

			static CTDBRET StringToDate(String* Str, DATE_TYPE DateType, [Out] CTDATE __gc* Date)
			{
				CTDATE date;
				IntPtr st = Marshal::StringToHGlobalAnsi(Str);
				ret = ctdbStringToDate((pTEXT)st.ToPointer(), (CTDATE_TYPE)DateType, &date);
				Marshal::FreeHGlobal(st);
				*Date = date;
				return ret;
			}

			static CTDBRET StringToDateTime(String* Str, [Out] CTDATETIME __gc* DateTime, DATE_TYPE DateType, TIME_TYPE TimeType)
			{
				CTDATETIME datetime;
				IntPtr st = Marshal::StringToHGlobalAnsi(Str);
				ret = ctdbStringToDateTime((pTEXT)st.ToPointer(), &datetime, (CTDATE_TYPE)DateType, (CTTIME_TYPE)TimeType);
				Marshal::FreeHGlobal(st);
				*DateTime = datetime;
				return ret;
			}

			static CTDBRET StringToMoney(String* Str, [Out]CTMONEY __gc* Money)
			{
				CTMONEY mon;
				IntPtr st = Marshal::StringToHGlobalAnsi(Str);
				ret = ctdbStringToMoney((pTEXT)st.ToPointer(), &mon);
				Marshal::FreeHGlobal(st);
				*Money = mon;
				return ret;
			}

			static CTDBRET StringToNumber(String* Str, [Out]ctdbNUMBER __gc* Number)
			{
				CTNUMBER __pin * num = new CTNUMBER;
				IntPtr st = Marshal::StringToHGlobalAnsi(Str);
				ret = ctdbStringToNumber((pTEXT)st.ToPointer(), num);
				Marshal::FreeHGlobal(st);
				CTN2ctN(num,Number);
				return ret;
			}

			static CTDBRET StringToTime(String* Str, TIME_TYPE TimeType, [Out] CTTIME __gc* Time)
			{
				CTTIME time;
				IntPtr st = Marshal::StringToHGlobalAnsi(Str);
				ret = ctdbStringToTime((pTEXT)st.ToPointer(), (CTTIME_TYPE)TimeType, &time);
				Marshal::FreeHGlobal(st);
				*Time = time;
				return ret;
			}

			static CTDBRET SwitchContext(CTHANDLE Record)
			{
				return ctdbSwitchContext((CTHANDLE) Record);
			}

			static CTDBRET SwitchInstance(IntPtr Handle)
			{
				return ctdbSwitchInstance((CTHANDLE) Handle);
			}

			static CTDBRET SystemFilterOn(IntPtr Handle, SYS_FILTER Mode)
			{
				return ctdbSystemFilterOn((CTHANDLE)Handle, (CTSYSFILTER) Mode);
			}

			static CTDBRET SystemFilterOff(IntPtr Handle, SYS_FILTER Mode)
			{
				return ctdbSystemFilterOff((CTHANDLE)Handle, (CTSYSFILTER) Mode);
			}

			static CTDBRET TimeCheck(NINT Hour, NINT Minute, NINT Second)
			{
				return ctdbTimeCheck(Hour, Minute, Second);
			}

			static CTDBRET TimePack([Out]CTTIME __gc * Time, NINT Hour, NINT Minute, NINT Second)
			{
				CTTIME time;
				ret = ctdbTimePack(&time, Hour, Minute, Second);
				*Time = time;
				return ret;
			}

			static CTDBRET TimeToString(CTTIME Time, TIME_TYPE TimeType, StringBuilder* Buffer, VRLEN BufferSize)
			{
				char __pin * buf = new char[BufferSize];
				memset(buf,0,BufferSize);
				ret = ctdbTimeToString(Time, (CTTIME_TYPE)TimeType, buf, BufferSize);
				Buffer->Length = 0;
				if (!ret)
				{
					Buffer->Insert(0,buf);
				}
				delete[] buf;
				return ret;
			}

		    static CTDBRET TimeUnpack(CTTIME Time, [Out]NINT __gc * Hour, [Out]NINT __gc * Minute, [Out]NINT __gc * Second)
			{
				NINT h,m,s;
			    ret = ctdbTimeUnpack(Time, &h, &m, &s);
				*Hour = h;
				*Minute = m;
				*Second = s;
				return ret;
			}

			static CTDBRET Unlock(IntPtr Session)
			{
				return ctdbUnlock((CTHANDLE) Session);
			}

			static CTDBRET UnlockRecord(IntPtr Record)
			{
				return ctdbUnlockRecord((CTHANDLE) Record);
			}
#undef UnlockResource
			static CTDBRET UnlockResource(IntPtr Res)
			{
				return ctdbUnlockResource((CTHANDLE) Res);
			}

			static CTDBRET UnlockTable(IntPtr Table)
			{
				return ctdbUnlockTable((CTHANDLE) Table);
			}

			static CTDBRET UpdateCndxIndex(IntPtr Table, NINT IndexNbr, String* CndExpr)
			{
				IntPtr st = Marshal::StringToHGlobalAnsi(CndExpr);
				ret = ctdbUpdateCndxIndex((CTHANDLE) Table,  IndexNbr, (pTEXT)st.ToPointer());
				Marshal::FreeHGlobal(st);
				return ret;
			}

			static CTDBRET UpdateCndxIndexByName(IntPtr Table, String* IndexName, String* CndExpr)
			{
				IntPtr idx = Marshal::StringToHGlobalAnsi(IndexName);	
				IntPtr cndx = Marshal::StringToHGlobalAnsi(CndExpr);
				ret = ctdbUpdateCndxIndexByName((CTHANDLE) Table, (pTEXT)idx.ToPointer(), (pTEXT)cndx.ToPointer());
				Marshal::FreeHGlobal(cndx);
				Marshal::FreeHGlobal(idx);
				return ret;
			}

			static CTDBRET UpdateCreateMode(IntPtr Table, CREATE_MODE Mode)
			{
				return ctdbUpdateCreateMode((CTHANDLE) Table, (CTCREATE_MODE)Mode);
			}

			static CTDBRET UpdatePadChar(IntPtr Handle, NINT padchar, NINT dmlchar, bool rebuild)
			{
				return ctdbUpdatePadChar((CTHANDLE) Handle, padchar, dmlchar, rebuild);
			}

			static CTDBRET UpdateResource(IntPtr resource, Byte data __gc[])
			{
				long size = data->Length;
				GCHandle gch = GCHandle::Alloc( data, GCHandleType::Pinned);
				ret = ctdbUpdateResource((CTHANDLE)resource, gch.AddrOfPinnedObject().ToPointer(), size);
				gch.Free();
				return ret;
			}

			static CTDBRET WriteRecord(IntPtr Record)
			{
				return ctdbWriteRecord((CTHANDLE)Record);
			}

			static CTDBRET CloneTable(IntPtr tarTable, String* tarName, IntPtr srcTable)
			{
				IntPtr name = Marshal::StringToHGlobalAnsi(tarName);
				ret = ctdbCloneTable((CTHANDLE)tarTable, (pTEXT)name.ToPointer(), (CTHANDLE)srcTable);
				Marshal::FreeHGlobal(name);
				return ret;
			}

			static CTDBRET HelloWorld(String* HelloFileName,String* HelloTextData,NINT HelloNintData, ULONG HelloULongData, CTFLOAT HelloFloatData) /* CTDB HELLO WORLD */
			{
				// There maybe sometimes a need to do some special handling here.
				// As an example, here we are passing in pTEXT, which we are assumed to be Strings.
				// Strings (perhaps because of UNICODE) are one type that needs special handling.
				// Here we define the incoming as "String *", and then use the marshal technique below.
				// Other types, such as pointers, may need to be defined as incoming IntPtr.			
				// As an example, if you were passing in a CTHANDLE, you would define the incoming as a IntPtr. See Logon above for example.
				// Other complex types might need other special handling. See other functions in this source file for examples.
				
				IntPtr HelloFilName = Marshal::StringToHGlobalAnsi(HelloFileName);
				IntPtr HelloTxtData = Marshal::StringToHGlobalAnsi(HelloTextData);
				ret = ctdbHelloWorld((pTEXT)HelloFilName.ToPointer(),(pTEXT)HelloTxtData.ToPointer(), HelloNintData, HelloULongData, HelloFloatData); 
				Marshal::FreeHGlobal(HelloFilName);
				Marshal::FreeHGlobal(HelloTxtData);
				return ret;
			}


#undef MessageBox
			private:
			static void Init()
			{
#ifndef NO_ctFEAT_STRONGSIGN
				try
				{
					Assembly* thisOne = Assembly::GetAssembly(__typeof(ctdb));
					Assembly* exe = Assembly::GetEntryAssembly();
					if(debugFlag & DEBUG_FLAG::ALLOC_SESSION)
					{
						debugLog->Write("dll name: ");
						if(thisOne != NULL)
						{
							debugLog->WriteLine(thisOne->FullName);
							debugLog->WriteLine(thisOne->CodeBase);
						}
						debugLog->Write("Application name: ");
						if(exe != NULL)
						{
							debugLog->WriteLine(exe->FullName);
							debugLog->WriteLine(exe->CodeBase);
						}
					}
					if (thisOne != NULL && exe != NULL)
					{
						Byte thisPk[] = thisOne->GetName()->GetPublicKey();
						Byte exePk[] = exe->GetName()->GetPublicKey();
						if(debugFlag & DEBUG_FLAG::ALLOC_SESSION)
						{
							debugLog->Write("dll public key  : ");
							for (int x=0;x<thisPk->Length;x++)
							{
								debugLog->Write(((Byte)thisPk[x]).ToString());
							}
							debugLog->WriteLine("");
							debugLog->Write("exe public key: ");
							for (int x=0;x<exePk->Length;x++)
							{
								debugLog->Write(((Byte)exePk[x]).ToString());
							}
							debugLog->WriteLine("");
						}
						if (thisPk->Length != exePk->Length)
							goto error;
						for (int x=0;x<thisPk->Length;x++)
						{
							if (thisPk[x] != exePk[x])
							{
								goto error;
							}
						}
					}
					return;
error:
					MessageBox::Show("Unlicensed DLL usage !!!\n\nPlease contact FairCom Corporation at http:\\\\www.faircom.com.", "Error");
					Environment::Exit(-1);
				}
				catch (Exception* ex)
				{
					MessageBox::Show(ex->Message);
				}
#endif
			}
		};

		__value public enum SESSION_TYPE
		{
			CTDB_SESSION	= ctdb::SESSION_TYPE::CTDB_SESSION,
			CTREE_SESSION	= ctdb::SESSION_TYPE::CTREE_SESSION,
			SQL_SESSION		= ctdb::SESSION_TYPE::SQL_SESSION
		};

		__value public enum ATTACH_MODE
		{
			NONE	=	ctdb::ATTACH_MODE::NONE,
			SESSION	=	ctdb::ATTACH_MODE::SESSION,
			CTREEID	=	ctdb::ATTACH_MODE::CTREEID,
			CURRENT	=	ctdb::ATTACH_MODE::CURRENT
		};

		[Flags]
		__value public enum OPEN_MODE
		{
			NORMAL_OPEN		= ctdb::OPEN_MODE::NORMAL_OPEN,
			EXCLUSIVE_OPEN	= ctdb::OPEN_MODE::EXCLUSIVE_OPEN,
			PERMANENT_OPEN	= ctdb::OPEN_MODE::PERMANENT_OPEN,
			CORRUPT_OPEN	= ctdb::OPEN_MODE::CORRUPT_OPEN,
			CHECKLOCK_OPEN	= ctdb::OPEN_MODE::CHECKLOCK_OPEN,
			CHECKREAD_OPEN	= ctdb::OPEN_MODE::CHECKREAD_OPEN,
			READONLY_OPEN	= ctdb::OPEN_MODE::READONLY_OPEN,
			DATAONLY_OPEN	= ctdb::OPEN_MODE::DATAONLY_OPEN
		};
		__value public enum SESSION_PARAM
		{
			BUFS		= ctdb::SESSION_PARAM::BUFS,
			FILS		= ctdb::SESSION_PARAM::FILS,
			SECT		= ctdb::SESSION_PARAM::SECT,
			DBUFS		= ctdb::SESSION_PARAM::DBUFS,
			USERPROF	= ctdb::SESSION_PARAM::USERPROF
		};
				
		__value public enum KEY_TYPE
		{
			FIXED_INDEX		= ctdb::KEY_TYPE::FIXED_INDEX,
			LEADING_INDEX	= ctdb::KEY_TYPE::LEADING_INDEX,
			PADDING_INDEX	= ctdb::KEY_TYPE::PADDING_INDEX,
			LEADPAD_INDEX	= ctdb::KEY_TYPE::LEADPAD_INDEX,
			ERROR_INDEX		= ctdb::KEY_TYPE::ERROR_INDEX
		};

		__value public enum FIELD_TYPE
			{
				BOOL		= ctdb::FIELD_TYPE::BOOL,		
				CHAR		= ctdb::FIELD_TYPE::CHAR,		
				CHARU		= ctdb::FIELD_TYPE::CHARU,	
				INT2		= ctdb::FIELD_TYPE::INT2,
				INT2U		= ctdb::FIELD_TYPE::INT2U,
				INT4		= ctdb::FIELD_TYPE::INT4,
				INT4U		= ctdb::FIELD_TYPE::INT4U,
				MONEY		= ctdb::FIELD_TYPE::MONEY,
				DATE		= ctdb::FIELD_TYPE::DATE,
				TIME		= ctdb::FIELD_TYPE::TIME,
				SFLOAT		= ctdb::FIELD_TYPE::SFLOAT,
				DFLOAT		= ctdb::FIELD_TYPE::DFLOAT,
				TIMES		= ctdb::FIELD_TYPE::TIMES,
				EFLOAT		= ctdb::FIELD_TYPE::EFLOAT,
				ARRAY		= ctdb::FIELD_TYPE::ARRAY,
				FSTRING		= ctdb::FIELD_TYPE::FSTRING,
				FPSTRING	= ctdb::FIELD_TYPE::FPSTRING,
				F2STRING	= ctdb::FIELD_TYPE::F2STRING,
				F4STRING	= ctdb::FIELD_TYPE::F4STRING,
				BIGINT		= ctdb::FIELD_TYPE::BIGINT,
				NUMBER		= ctdb::FIELD_TYPE::NUMBER,
				CURRENCY	= ctdb::FIELD_TYPE::CURRENCY,
				VSTRING		= ctdb::FIELD_TYPE::VSTRING,
				VPSTRING	= ctdb::FIELD_TYPE::VPSTRING,
				V2STRING	= ctdb::FIELD_TYPE::V2STRING,
				V4STRING	= ctdb::FIELD_TYPE::V4STRING,
#ifdef ctUNICODE
				FUNICODE	= ctdb::FIELD_TYPE::FUNICODE,	
				CTUNICODE	= ctdb::FIELD_TYPE::CTUNICODE,	
				F2UNICODE	= ctdb::FIELD_TYPE::F2UNICODE,
				V2UNICODE	= ctdb::FIELD_TYPE::V2UNICODE,	
#endif
				TINYINT		= ctdb::FIELD_TYPE::TINYINT,		
				UTINYINT	= ctdb::FIELD_TYPE::UTINYINT,	
				SMALLINT	= ctdb::FIELD_TYPE::SMALLINT,
				USMALLINT	= ctdb::FIELD_TYPE::USMALLINT,
				INTEGER		= ctdb::FIELD_TYPE::INTEGER,
				UINTEGER	= ctdb::FIELD_TYPE::UINTEGER,
				FLOAT		= ctdb::FIELD_TYPE::FLOAT,
				DOUBL		= ctdb::FIELD_TYPE::DOUBL,
				TIMESTAMP	= ctdb::FIELD_TYPE::TIMESTAMP,
				BINARY		= ctdb::FIELD_TYPE::BINARY,
				CHARS		= ctdb::FIELD_TYPE::CHARS,
				VARCHAR		= ctdb::FIELD_TYPE::VARCHAR,
#ifdef ctUNICODE
				NCHAR		= ctdb::FIELD_TYPE::NCHAR,
				NVARCHAR	= ctdb::FIELD_TYPE::NVARCHAR,
#endif
				LVC			= ctdb::FIELD_TYPE::LVC,
				VARBINARY	= ctdb::FIELD_TYPE::VARBINARY,
				LVB			= ctdb::FIELD_TYPE::LVB
			};


		__value public enum SEG_MODE
			{
				REGSEG_SEG		= ctdb::SEG_MODE::REGSEG_SEG,	
				INTSEG_SEG		= ctdb::SEG_MODE::INTSEG_SEG,	
				UREGSEG_SEG		= ctdb::SEG_MODE::UREGSEG_SEG,	
				SRLSEG_SEG		= ctdb::SEG_MODE::SRLSEG_SEG,	
				VARSEG_SEG		= ctdb::SEG_MODE::VARSEG_SEG,	
				UVARSEG_SEG		= ctdb::SEG_MODE::UVARSEG_SEG,	
				SGNSEG_SEG		= ctdb::SEG_MODE::SGNSEG_SEG,
				FLTSEG_SEG		= ctdb::SEG_MODE::FLTSEG_SEG,	
				DECSEG_SEG		= ctdb::SEG_MODE::DECSEG_SEG,	
				BCDSEG_SEG		= ctdb::SEG_MODE::BCDSEG_SEG,	
				SCHSEG_SEG		= ctdb::SEG_MODE::SCHSEG_SEG,
				USCHSEG_SEG		= ctdb::SEG_MODE::USCHSEG_SEG,	
				VSCHSEG_SEG		= ctdb::SEG_MODE::VSCHSEG_SEG,	
				UVSCHSEG_SEG	= ctdb::SEG_MODE::UVSCHSEG_SEG,	
				DESCENDING_SEG	= ctdb::SEG_MODE::DESCENDING_SEG,
				ALTSEG_SEG		= ctdb::SEG_MODE::ALTSEG_SEG,
				ENDSEG_SEG		= ctdb::SEG_MODE::ENDSEG_SEG,
				SCHSRL_SEG		= ctdb::SEG_MODE::SCHSRL_SEG,
				INVALID_SEG		= ctdb::SEG_MODE::INVALID_SEG
			};

		[Flags]
		__value public enum CREATE_MODE
			{
				NORMAL_CREATE		= ctdb::CREATE_MODE::NORMAL_CREATE,		
				PREIMG_CREATE		= ctdb::CREATE_MODE::PREIMG_CREATE,
				TRNLOG_CREATE		= ctdb::CREATE_MODE::TRNLOG_CREATE,
				WRITETHRU_CREATE	= ctdb::CREATE_MODE::WRITETHRU_CREATE,
				CHECKLOCK_CREATE	= ctdb::CREATE_MODE::CHECKLOCK_CREATE,
				VRLEN_CREATE		= ctdb::CREATE_MODE::VRLEN_CREATE,
				NORECBYT_CREATE		= ctdb::CREATE_MODE::NORECBYT_CREATE,
				NOROWID_CREATE		= ctdb::CREATE_MODE::NOROWID_CREATE,
				CHECKREAD_CREATE	= ctdb::CREATE_MODE::CHECKREAD_CREATE,	
				HUGEFILE_CREATE		= ctdb::CREATE_MODE::HUGEFILE_CREATE,
				NODELFLD_CREATE		= ctdb::CREATE_MODE::NODELFLD_CREATE,
				NONULFLD_CREATE		= ctdb::CREATE_MODE::NONULFLD_CREATE
			};

		__value public enum LOCK_MODE
			{
				FREE_LOCK					= ctdb::LOCK_MODE::FREE_LOCK,				
				READ_LOCK					= ctdb::LOCK_MODE::READ_LOCK,				
				READ_BLOCK_LOCK				= ctdb::LOCK_MODE::READ_BLOCK_LOCK,			
				WRITE_LOCK					= ctdb::LOCK_MODE::WRITE_LOCK,				
				WRITE_BLOCK_LOCK			= ctdb::LOCK_MODE::WRITE_BLOCK_LOCK,			
				RESET_LOCK					= ctdb::LOCK_MODE::RESET_LOCK,				
				SUSPEND_LOCK				= ctdb::LOCK_MODE::SUSPEND_LOCK,				
				RESTORE_READ_LOCK			= ctdb::LOCK_MODE::RESTORE_READ_LOCK,		
				RESTORE_READ_BLOCK_LOCK		= ctdb::LOCK_MODE::RESTORE_READ_BLOCK_LOCK,	
				RESTORE_WRITE_LOCK			= ctdb::LOCK_MODE::RESTORE_WRITE_LOCK,		
				RESTORE_WRITE_BLOCK_LOCK	= ctdb::LOCK_MODE::RESTORE_WRITE_BLOCK_LOCK
			};

		__value public enum DATE_TYPE
			{
//				DEF_DATE	= ctdb::DATE_TYPE::DEF_DATE,	
				MDCY_DATE	= ctdb::DATE_TYPE::MDCY_DATE,
				MDY_DATE	= ctdb::DATE_TYPE::MDY_DATE,	
				DMCY_DATE	= ctdb::DATE_TYPE::DMCY_DATE,
				DMY_DATE	= ctdb::DATE_TYPE::DMY_DATE,	
				CYMD_DATE	= ctdb::DATE_TYPE::CYMD_DATE,
				YMD_DATE	= ctdb::DATE_TYPE::YMD_DATE	
			};

		__value public enum TIME_TYPE
			{
//				DEF_TIME	= ctdb::TIME_TYPE::DEF_TIME,   
				HMSP_TIME	= ctdb::TIME_TYPE::HMSP_TIME,  
				HMP_TIME	= ctdb::TIME_TYPE::HMP_TIME,
				HMS_TIME	= ctdb::TIME_TYPE::HMS_TIME,   
				HM_TIME		= ctdb::TIME_TYPE::HM_TIME,    
				MIL_TIME	= ctdb::TIME_TYPE::MIL_TIME    
			};

		namespace ENUMS
		{
			__value public enum FIND_MODE
				{
					EQ	= ctdb::FIND_MODE::EQ,   
					LT	= ctdb::FIND_MODE::LT,   
					LE	= ctdb::FIND_MODE::LE,   
					GT	= ctdb::FIND_MODE::GT,   
					GE	= ctdb::FIND_MODE::GE
				};
		};

		__value public enum RECBUF_MODE
			{
				AUTO_RECBUF		= ctdb::RECBUF_MODE::AUTO_RECBUF,   
				STATIC_RECBUF	= ctdb::RECBUF_MODE::STATIC_RECBUF,   
				RAW_RECBUF		= ctdb::RECBUF_MODE::RAW_RECBUF
			};

		namespace ENUMS
		{
		[Flags]
		__value public enum LIB_TYPE
			{
				SINGLE	= ctdb::LIB_TYPE::SINGLE,	/* single user            */
				MUSER	= ctdb::LIB_TYPE::MUSER,	/* multi user             */
				CLIENT	= ctdb::LIB_TYPE::CLIENT,	/* client                 */
				LOCLIB	= ctdb::LIB_TYPE::LOCLIB,	/* loclib                 */
				SERVER	= ctdb::LIB_TYPE::SERVER,	/* server side library    */
				THREA	= ctdb::LIB_TYPE::THREA,	/* multi thread           */
				TRAN	= ctdb::LIB_TYPE::TRAN,		/* transaction processing */
				HUGE	= ctdb::LIB_TYPE::HUGE		/* huge file support      */
			};
		};

		__value public enum ALTER_TABLE
			{
				NORMAL	= ctdb::ALTER_TABLE::NORMAL,
				INDEX	= ctdb::ALTER_TABLE::INDEX,
				FULL	= ctdb::ALTER_TABLE::FULL
			};

		__value public enum IDXNO
			{
				RECBYT_NO	= ctdb::IDXNO::RECBYT_NO,
				ROWID_NO	= ctdb::IDXNO::ROWID_NO,
				DATA_NO		= ctdb::IDXNO::DATA_NO
			};

		__value public enum KEEP_MODE
			{
				FREE_KEEP	= ctdb::KEEP_MODE::FREE_KEEP,
				LOCK_KEEP	= ctdb::KEEP_MODE::LOCK_KEEP,
				OUT_KEEP	= ctdb::KEEP_MODE::OUT_KEEP,
				OUTALL_KEEP	= ctdb::KEEP_MODE::OUTALL_KEEP
			};

		__value public enum RANGE_OP
			{
				EQ		= ctdb::RANGE_OP::EQ,	
				GT		= ctdb::RANGE_OP::GT,	
				GE		= ctdb::RANGE_OP::GE,	
				LE		= ctdb::RANGE_OP::LE,	
				LT		= ctdb::RANGE_OP::LT,	
				NE		= ctdb::RANGE_OP::NE,	
				BET		= ctdb::RANGE_OP::BET,	
				BET_IE	= ctdb::RANGE_OP::BET_IE,
				BET_EI	= ctdb::RANGE_OP::BET_EI,
				BET_EE	= ctdb::RANGE_OP::BET_EE,
				NOTBET	= ctdb::RANGE_OP::NOTBET
			};

		__value public enum TABLE_PERMS
			{
				O_READ		= ctdb::TABLE_PERMS::O_READ,
				O_WRITE		= ctdb::TABLE_PERMS::O_WRITE,
				O_DEF		= ctdb::TABLE_PERMS::O_DEF,
				O_DELETE	= ctdb::TABLE_PERMS::O_DELETE,
				O_ALL		= ctdb::TABLE_PERMS::O_ALL,
				O_NOPASS	= ctdb::TABLE_PERMS::O_NOPASS,
				G_READ		= ctdb::TABLE_PERMS::G_READ,
				G_WRITE		= ctdb::TABLE_PERMS::G_WRITE,
				G_DEF		= ctdb::TABLE_PERMS::G_DEF,
				G_DELETE	= ctdb::TABLE_PERMS::G_DELETE,
				G_ALL		= ctdb::TABLE_PERMS::G_ALL,
				G_NOPASS	= ctdb::TABLE_PERMS::G_NOPASS,
				W_READ		= ctdb::TABLE_PERMS::W_READ,
				W_WRITE		= ctdb::TABLE_PERMS::W_WRITE,
				W_DEF		= ctdb::TABLE_PERMS::W_DEF,
				W_DELETE	= ctdb::TABLE_PERMS::W_DELETE,
				W_ALL		= ctdb::TABLE_PERMS::W_ALL,
				W_NOPASS	= ctdb::TABLE_PERMS::W_NOPASS
			};
			
		__value public enum USER_PROF
			{
				NTKEY	= ctdb::USER_PROF::NTKEY,
				SAV_ENV	= ctdb::USER_PROF::SAV_ENV,
				SERIAL	= ctdb::USER_PROF::SERIAL,	
				MEMABS	= ctdb::USER_PROF::MEMABS,	
				NDATA	= ctdb::USER_PROF::NDATA,	
				LOCLIB	= ctdb::USER_PROF::LOCLIB,	
				PTHTMP	= ctdb::USER_PROF::PTHTMP,	
				CODCNV	= ctdb::USER_PROF::CODCNV,	
				CLRCHK	= ctdb::USER_PROF::CLRCHK,
				CUSTOM	= ctdb::USER_PROF::CUSTOM,	
				ENCRYPT	= ctdb::USER_PROF::ENCRYPT,
				ADMSPCL	= ctdb::USER_PROF::ADMSPCL,
				LOGRED	= ctdb::USER_PROF::LOGRED
			};

		__value public enum TABLE_TYPE
			{
				INVALID			= ctdb::TABLE_TYPE::NONE,			/* not table handle or table not active */
				SESSION_DICT	= ctdb::TABLE_TYPE::SESSION_DICT,	/* session dictionary table 			*/
				DATABASE_DICT	= ctdb::TABLE_TYPE::DATABASE_DICT,	/* database dictionary table 			*/
				SQL_CATALOG		= ctdb::TABLE_TYPE::SQL_CATALOG,	/* ctreeSQL catalog table 				*/
				USER			= ctdb::TABLE_TYPE::USER			/* user table 							*/
			};

		namespace ENUMS
		{
			__value public enum SYS_FILTER
				{
					NONE	= ctdb::SYS_FILTER::NONE,		/* indicate no system wide record filter */
					READ	= ctdb::SYS_FILTER::READ,		/* indicate a read system wide filter 	 */
					WRITE	= ctdb::SYS_FILTER::WRITE		/* indicate a write system wide filter 	 */
				};
		}
				
		__value public enum FIELD_STATUS
			{
				OLD		=	ctdb::FIELD_STATUS::OLD,	/* Original field as read from table */
				NEW		=	ctdb::FIELD_STATUS::NEW,	/* Field added or inserted */
				DEL		=	ctdb::FIELD_STATUS::DEL,	/* Original field deleted */
				MOVED	=	ctdb::FIELD_STATUS::MOVED,	/* Original field moved */
				NAME	=	ctdb::FIELD_STATUS::NAME,	/* Field name changed */
				TYPE	=	ctdb::FIELD_STATUS::TYPE,	/* Field type changed */
				LEN		=	ctdb::FIELD_STATUS::LEN,	/* Field length changed */
				RES		=	ctdb::FIELD_STATUS::RES		/* Field resource changed */
			};

		namespace INDEXES
		{
			__value public enum INDEX_STATUS
				{
					OLD		=	ctdb::INDEX_STATUS::OLD,		/* Original value (no changes) */
					NEW		=	ctdb::INDEX_STATUS::NEW,		/* Index added */
					DEL		=	ctdb::INDEX_STATUS::DEL,		/* Original Index deleted */
					KEYTYPE	=	ctdb::INDEX_STATUS::KEYTYPE,	/* Index key type changed */
					EMPCHAR	=	ctdb::INDEX_STATUS::EMPCHAR,	/* Index empty char changed */
					DUPFLAG	=	ctdb::INDEX_STATUS::DUPFLAG,	/* Index duplicate flag changed */
					NULLFLAG=	ctdb::INDEX_STATUS::NULLFLAG,	/* Index null flag changed */
					AIDXNAM	=	ctdb::INDEX_STATUS::AIDXNAM,	/* Index file name changed */
					RIDXNAM	=	ctdb::INDEX_STATUS::RIDXNAM		/* Index symbolic name changed */
				};
		}

		namespace ENUMS
		{
			__value public enum SEGMENT_STATUS
				{
					OLD		=	ctdb::SEGMENT_STATUS::OLD,		/* Original segment as read from file */
					NEW		=	ctdb::SEGMENT_STATUS::NEW,		/* Segment added or inserted */
					DEL		=	ctdb::SEGMENT_STATUS::DEL,		/* Original segment deleted */
					MOVED	=	ctdb::SEGMENT_STATUS::MOVED,	/* Original segment moved */
					MODE	=	ctdb::SEGMENT_STATUS::MODE,		/* Segment mode changed	 */		
					FIELD	=	ctdb::SEGMENT_STATUS::FIELD		/* Segment field changed	 */		
				};
		}

		__value public enum TABLE_STATUS
			{
				REBUILD_NONE	=	ctdb::TABLE_STATUS::REBUILD_NONE,		/* Nothing to be done, table is ok	  */
				REBUILD_DODA	=	ctdb::TABLE_STATUS::REBUILD_DODA,		/* Update the table doda			  */
				REBUILD_RESOURCE=	ctdb::TABLE_STATUS::REBUILD_RESOURCE,	/* Update table FC!DFLD resource      */
				REBUILD_INDEX	=	ctdb::TABLE_STATUS::REBUILD_INDEX,		/* Add new indices 					  */
				REBUILD_ALL		=	ctdb::TABLE_STATUS::REBUILD_ALL,		/* Rebuild all indices				  */
				REBUILD_FULL	=	ctdb::TABLE_STATUS::REBUILD_FULL,		/* Full table rebuild. A temporary	  */
																			/* table is created and all data is	  */
																			/* moved to new table building 		  */
																			/* indices on the fly				  */
			};

		namespace BATCH
		{
			__value public enum BATCH_MODE
				{
					NONE			= ctdb::BATCH_MODE::NONE,			/* batch is not active				  */  
					GET				= ctdb::BATCH_MODE::GET,			/* retrieve records by partial key	  */   
					RANGE			= ctdb::BATCH_MODE::RANGE,			/* retrieve records by index range	  */       
					PHYS			= ctdb::BATCH_MODE::PHYS,			/* retrieve records by physical order */       
					DEL				= ctdb::BATCH_MODE::DEL,			/* delete group of related records	  */   
					INS				= ctdb::BATCH_MODE::INS,			/* insert a group of records		  */   
					MANDATORY		= ctdb::BATCH_MODE::MANDATORY,		/* mask for mandatory modes			  */
					GKEY			= ctdb::BATCH_MODE::GKEY,			/* process records >= target key	  */                
					LKEY			= ctdb::BATCH_MODE::LKEY,			/* process records <= target key	  */       
					VERIFY			= ctdb::BATCH_MODE::VERIFY,			/* verify target keys				  */       
					LOCK_KEEP		= ctdb::BATCH_MODE::LOCK_KEEP,		/* keep locks after ctdbBatchEnd	  */       
					LOCK_READ		= ctdb::BATCH_MODE::LOCK_READ,		/* apply read locks					  */
					LOCK_WRITE		= ctdb::BATCH_MODE::LOCK_WRITE,		/* apply write locks				  */       
					LOCK_BLOCK		= ctdb::BATCH_MODE::LOCK_BLOCK,		/* locks should block				  */       
					LOCK_ONE		= ctdb::BATCH_MODE::LOCK_ONE,		/* lock on during read				  */       
					LOCK_COMPLETE	= ctdb::BATCH_MODE::LOCK_COMPLETE	/* return success only if all locked  */       
				};
		}

		__value public enum BEGIN_MODE
			{
				NONE_BEGIN		= ctdb::BEGIN_MODE::NONE_BEGIN,		/* No begin transaction mode set. Apply 	*/
																	/* default begin transaction mode			*/

				PREIMG_BEGIN	= ctdb::BEGIN_MODE::PREIMG_BEGIN,	/* Transaction atomicity only. Auto-recovery*/
																	/* is not availabe. Mutually exclusive with	*/
																	/* CTBEGIN_TRNLOG.							*/

				TRNLOG_BEGIN	= ctdb::BEGIN_MODE::TRNLOG_BEGIN,	/* Full transaction processing functionality*/
																	/* including auto-recovery. Mutually 		*/
																	/* exclusive to CTBEGIN_PREIMG. This is the	*/
																	/* default begin transaction mode.			*/
	
				DEFER_BEGIN		= ctdb::BEGIN_MODE::DEFER_BEGIN,	/* Defer begin transaction until update		*/

				AUTOSAVE_BEGIN	= ctdb::BEGIN_MODE::AUTOSAVE_BEGIN	/* Automatically invokes savepoints after	*/
																	/* each successful record or resource update*/
			};

		namespace REBUILD
		{
			__value public enum REBUILD_MODE
				{
					NONE		= ctdb::REBUILD_MODE::NONE,			/* normal rebuild mode					*/        
					PURGEDUP	= ctdb::REBUILD_MODE::PURGEDUP,		/* purge duplicate records				*/
					UPDATEIFIL	= ctdb::REBUILD_MODE::UPDATEIFIL,	/* update table IFIL structure			*/
					DATAONLY	= ctdb::REBUILD_MODE::DATAONLY 		/* rebuild only the data file			*/
				};
		}

		[Flags]
		__value public enum OPS_STATE
			{
				OFF		=	ctdb::OPS_STATE::OFF,	// 0x00000000 - Turn a status bit off.
				SET		=	ctdb::OPS_STATE::SET,	// 0x00000001 - Set the entire status word.
				ON		=	ctdb::OPS_STATE::ON,	// 0x00000002 -	Turn a status bit on.	
				RET		=	ctdb::OPS_STATE::RET	// 0x00000003 - Return the entire status word.
				//VRET	=	ctdb::OPS_STATE::VRET	// 0x00000004
			};

		[Flags]
		__value public enum OPS_MODE
			{
				LOCKON_GET		=	ctdb::OPS_MODE::LOCKON_GET, 	//	Lock next fetch only.
				UNLOCK_ADD		=	ctdb::OPS_MODE::UNLOCK_ADD,		//	Automatic unlock on add.
				UNLOCK_RWT		=	ctdb::OPS_MODE::UNLOCK_RWT, 	//	Automatic unlock on rewrite.
				UNLOCK_UPD		=	ctdb::OPS_MODE::UNLOCK_UPD, 	//	(OPS_UNLOCK_ADD | OPS_UNLOCK_RWT)
				LOCKON_BLK		=	ctdb::OPS_MODE::LOCKON_BLK,		//	Blocking lock on next fetch only.
				FUNCTION_MON	=	ctdb::OPS_MODE::FUNCTION_MON, 	//  Toggle function monitor. (Server)
				LOCK_MON		=	ctdb::OPS_MODE::LOCK_MON,		//	Toggle lock monitor. (Server)
				TRACK_MON		=	ctdb::OPS_MODE::TRACK_MON, 		//	Toggle memory track monitor. (Server)
				MIRROR_NOSWITCH	=	ctdb::OPS_MODE::MIRROR_NOSWITCH,//  Don't continue if mirror or primary fails. (Server)
				MIRROR_TRM		=	ctdb::OPS_MODE::MIRROR_TRM,		//	A primary or mirror has been shutdown.
				MEMORY_SWP		=	ctdb::OPS_MODE::MEMORY_SWP,		//	Memory swapping active.
				AUTOISAM_TRN	=	ctdb::OPS_MODE::AUTOISAM_TRN, 	//	Automatic ISAM transactions.
				COMMIT_SWP		=	ctdb::OPS_MODE::COMMIT_SWP,		//	Auto commit on swap occurred.
				SERIAL_UPD		=	ctdb::OPS_MODE::SERIAL_UPD,		//	Changes GetSerialNbr operation.
				DEFER_CLOSE		=	ctdb::OPS_MODE::DEFER_CLOSE, 	//	Defer file closes or deletes during transactions.
				DISK_IO			=	ctdb::OPS_MODE::DISK_IO 		//	Set sysiocod on disk reads and writes.
			};
/* end of ctdbnet.h */
