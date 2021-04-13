# -*- coding: Latin-1 -*-

import enum


END_OF_FILE = 101
CTDBRET_OK = 0

NO = 0
YES = 1

# The three session types.  These are modes that control how the client-side CTDB code operates.
#   A "per-connection" thing.  NOT stored in the session DB.
class SessionTypeEnum(enum.Enum):
    LEGACY_CTDB=0
    LEGACY_ISAM=1
    NAV_SQL=2

# Session-wide locking modes
class LockModeEnum(enum.Enum):
    TURN_OFF_LOCKING = 0				    # free any locks
    NON_BLOCKING_READ = 1				    # non blocking read locks
    BLOCKING_READ = 2		    # blocking read locks
    NON_BLOCKING_WRITE = 3			    # non blocking write locks
    BLOCKING_WRITE = 4		    # blocking write locks
    RESTART_WRITE_LOCKING = 5			    # equivalent to first calling ctdbLock with CTLOCK_FREE followed by CTLOCK_WRITE
    PAUSE_LOCKING = 6			    # temporarily suspend locking
    RESUME_NON_BLOCKING_READ = 7		    # restore CTLOCK_READ mode
    RESUME_BLOCKING_READ = 8	# restore CTLOCK_READ_BLOCK mode
    RESUME_NON_BLOCKING_WRITE = 9		# restore CTLOCK_WRITE mode
    RESUME_BLOCKING_WRITE = 10	# restore CTLOCK_WRITE_BLOCK mode
    # RESUME = ????  # Un-suspend to whatever mode was active before suspecd was called.  Vomit - look this up!


# The various modes which are used when opening a table.
class OpenModeEnum(enum.Enum):
    NORMAL		= 0 
    CTOPEN_EXCLUSIVE	= 1
    CTOPEN_PERMANENT	= 2
    CTOPEN_CORRUPT		= 4
    CTOPEN_CHECKLOCK	= 8
    CTOPEN_CHECKREAD	= 16
    CTOPEN_READONLY	= 32
    CTOPEN_DATAONLY	= 64

# The various field / column types
class FieldTypeEnum(enum.Enum):
    BOOLEAN	=	(1 << 3)
    INT8_SIGNED	=	(2 << 3)
    INT8_UNSIGNED	=(3 << 3)
    INT16_SIGNED	=	((4 << 3) + 1)
    INT16_UNSIGNED	=((5 << 3) + 1)
    INT32_SIGNED	=	((6 << 3) + 3)
    INT32_UNSIGNED	=((7 << 3) + 3)
    MONEY	=((8 << 3) + 3)
    DATE	=	((9 << 3) + 3)
    TIME	=	((10 << 3) + 3)
    FLOAT32	=((11 << 3) + 3)
    FLOAT64	=((12 << 3) + 7)

    DECIMAL	= ((13 << 3) + 1)	

    TIMESTAMP	=((15 << 3) + 4)
    BINARY_FIXED_LENGTH	=(16 << 3)
    CURRENCY=	((17 << 3) + 7)

    STRING_FIXED_LENGTH	=(18 << 3)
    STRING	=((21 << 3) + 2) 


    INT64_SIGNED	=	((28 << 3) + 7)
    INT64_UNSIGNED	=((29 << 3) + 7)


    CT_TINYINT      =INT8_SIGNED      
    CT_UTINYINT     =INT8_UNSIGNED		
    CT_SMALLINT     =INT16_SIGNED		
    CT_USMALLINT    =INT16_UNSIGNED		
    CT_INTEGER      =INT32_SIGNED		
    CT_UINTEGER     =INT32_UNSIGNED		
    CT_BIGINT		=INT64_SIGNED		
    CT_UBIGINT		=INT64_UNSIGNED		
    CT_FLOAT        =FLOAT32	
    CT_DOUBLE       =FLOAT64	
    CT_TIMESTAMP    =TIMESTAMP		
    CT_CHARS        =STRING_FIXED_LENGTH	
    CT_LVB   		=STRING	




CTFIND_EQ = 0
CTFIND_LT = 1
CTFIND_LE = 2
CTFIND_GT = 3
CTFIND_GE = 4


CTDATE_MDCY = 1   	
CTDATE_MDY = 2		
CTDATE_DMCY = 3		
CTDATE_DMY = 4		
CTDATE_CYMD = 5		
CTDATE_YMD = 6		

CTTIME_HMSP = 1            
CTTIME_HMP = 2             
CTTIME_HMS = 3             
CTTIME_HM = 4              
CTTIME_MIL = 5             
CTTIME_HHMSP = 6           
CTTIME_HHMP = 7            
CTTIME_HHMS = 8            
CTTIME_HHM = 9             
CTTIME_HMST = 10           
CTTIME_HHMST = 11          


CTCREATE_NORMAL	= 0x00000000
CTCREATE_PREIMG	= 0x00000001
CTCREATE_TRNLOG	= 0x00000002
CTCREATE_WRITETHRU	= 0x00000004
CTCREATE_CHECKLOCK	= 0x00000008
CTCREATE_VRLEN		= 0x00000010
CTCREATE_NORECBYT	= 0x00000020
CTCREATE_NOROWID	= 0x00000040
CTCREATE_CHECKREAD	= 0x00000080
CTCREATE_HUGEFILE	= 0x00000100
CTCREATE_NODELFLD	= 0x00000200
CTCREATE_NONULFLD	= 0x00000400
CTCREATE_PARTAUTO	= 0x00000800 # partitioned table */
CTCREATE_V8DELFLD	= 0x00001000 # create the table using sizeof(LONG)(4) bytes delfld size as it was in v9 and previous*/
CTCREATE_COMPRESS	= 0x00002000 # create table using data compression */
CTCREATE_NOFLUSH	= 0x00004000 # for non TRNLOG files, disbale disk flushing */
CTCREATE_DYNPARTHOST	= 0x00008000 # create the table as a dynamic partition host */
CTCREATE_FLEXREC	= 0x00010000  # use flexible record format */
CTCREATE_BLOCKCOMPRESSDAT = 0x00020000 # create data file with block compression */
CTCREATE_BLOCKCOMPRESSIDX = 0x00040000 # create indexes with block compression */
CTCREATE_AUTOMKDIR = 0x00080000  # create directories if needed */
CTCREATE_NOCLSADD = 0x00100000 


CTDB_ALTER_NORMAL		=0	#/* check for changes before altering	*/
CTDB_ALTER_INDEX		=1	#/* Force rebuild of all indexes			*/
CTDB_ALTER_FULL			=3	#/* Force full table rebuild				*/
CTDB_ALTER_FTI			=4	#/* Force rebuild af all Full Text indexes */
CTDB_ALTER_HOT			=8	#/* Force hot alter table */
CTDB_ALTER_PURGEDUP		=0x1000	#/* Purge duplicate record			*/
CTDB_ALTER_TRUNCATE		=0x2000	#/* Truncate the table - forces CTDB_ALTER_FULL */
CTDB_ALTER_OWNER		=0x4000	#/* Force owner reasignement			*/
CTDB_ALTER_KEEPTRAN		=0x8000	#/* use the existing transaction mode even during the alter*/
CTDB_ALTER_V8DELFLD		=0x0100	#/* force CTCREATE_V8DELFLD during alter table */
CTDB_ALTER_MASK			=0x00ff


FIXED_LENGTH_KEY                       = 0x00000000  #/* fixed length key               */
CTINDEX_LEADING                     = 0x00000004  #/* COL_PREFIX - leading character compression  */
CTINDEX_PADDING                     = 0x00000008  #/* COL_SUFFIX padding compression            */
CTINDEX_LEADPAD                     = 0x0000000C  #/* COL_BOTH leading/padding compression    */
CTINDEX_NOMOD                       = 0x00000080  #/* KTYP_NOISMKEYUPD - unmodifiable key    */
CTINDEX_DFRIDX                      = 0x00000100  #/* KTYP_DFRIDX  - deferred index maintenance */
CTINDEX_VARIABLE_LENGTH_COMPRESSION = 0x00000200  #/* KTYP_VLENNOD - index node contains offset list	*/
CTINDEX_TRNMRKOPT                   = 0x00000400  #/* KTYP_TRNMRKOPT - transaction marks stored with keys	*/
CTINDEX_RLE_KEY_COMPRESSION         = 0x00000800  #/* KTYP_KEYCOMPSRLE - index uses sRLE key compression	*/
CTINDEX_CMPOFFSET                   = 0x00001000  #/* KTYP_CMPOFFSET - index uses compressed offsets	*/
CTINDEX_CMPTRNMRK                   = 0x00002000  #/* KTYP_CMPTRNMRK - index uses compressed transaction marks */

CTDB_FTI_MODE_REG   = 0x00000001 # /* default field treatment */
CTDB_FTI_MODE_UTF8  = 0x00000002 # /* field format in utf8 */
CTDB_FTI_MODE_UTF16 = 0x00000004 # /* field format in utf16 */

CTREBUILD_NONE		= 0 #,		/* normal rebuild mode					*/
CTREBUILD_PURGEDUP	= 1 #,		/* purge duplicate records				*/
CTREBUILD_UPDATEIFIL= 2 #,		/* update table IFIL structure			*/
CTREBUILD_DATAONLY	= 4 #, 		/* rebuild only the data file			*/
CTREBUILD_COMPACT	= 8 # 		/* compact and rebuild			*/

CTSEG_REGSEG	= 8
CTSEG_INTSEG	= 8
CTSEG_UREGSEG	= 8
CTSEG_SRLSEG	= 8
CTSEG_VARSEG	= 8
CTSEG_UVARSEG	= 8
CTSEG_SGNSEG	= 8
CTSEG_FLTSEG	= 12
CTSEG_DECSEG	= 12
CTSEG_BCDSEG	= 12
FIELD_NUMBER	= 12 # was CTSEG_SCHSEG
CTSEG_USCHSEG   = 16
CTSEG_VSCHSEG   = 16
CTSEG_UVSCHSEG  = 16
CTSEG_DESCENDING= 16
CTSEG_ALTSEG	= 32
CTSEG_ENDSEG	= 64
CTSEG_UNCSEG	= 128
CTSEG_RECBYT	= 256
CTSEG_SCHSRL	= 257		
CTSEG_GNXSEG	= 1024




# The constants for setting the default indexes
# From ctdbsdk.h
CTDB_RECBYT_IDXNO = 10000 # RECBYT - this index represents the offset of the record inside the table. It is used internally to improve space management, and may be used to sort the table by physical order. 
CTDB_ROWID_IDXNO = 10001 # ROWID - this unique index represents the ordering of the table by input order.
CTDB_DATA_IDXNO = 10002  # physical data table traversal without using any indexes
CTDB_PARTITION_IDXNO = 10003



# CTDB BATCH Mandatory modes
# Only one of the following must be used
CTBATCH_NONE	=	0x00		# batch is not active
CTBATCH_GET		=	0x01		# retrieve records by partial key
CTBATCH_RANGE	=	0x02		# retrieve records by index range
CTBATCH_PHYS	=	0x03		# retrieve records by physical order
CTBATCH_DEL		=	0x04		# delete group of related records
CTBATCH_INS		=	0x05		# insert a group of records
CTBATCH_UPD		=	0x06		# REQRITE a group of records
CTBATCH_MANDATORY	= 0xff 	# mask for mandatory modes

# CTDB BATCH other modes
# these batch modes should be or'ed in to mandatory modes
CTBATCH_GKEY=	0x00000200		# process records >= target key
CTBATCH_LKEY=	0x00000400		# process records <= target key
CTBATCH_VERIFY=	0x00000800		# verify target keys
CTBATCH_LOCK_KEEP=	0x00001000	# keep locks after ctdbBatchEnd
CTBATCH_LOCK_READ=	0x00002000	# apply read locks
CTBATCH_LOCK_WRITE=	0x00004000	# apply write locks
CTBATCH_LOCK_BLOCK=	0x00008000	# locks should block
CTBATCH_LOCK_ONE=	0x00010000	# lock on during read
CTBATCH_COMPLETE=	0x00020000	# return success only if all locked
CTBATCH_KEEPSRLSEG=	0x00040000	# keep serial segment on update
CTBATCH_AUTORESIZE=	0x00080000	# automatically resize buffer if not large enough to contain at least 1 record
CTBATCH_REVERSE=	0x00100000	# return range results in reverse order

BAT_RET_BLK = 0x00200000	# return records as contiguous block w/o position info



CTREE_CHAR_ENCODING = 'Latin-1'
