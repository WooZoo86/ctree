#include "ctjobs2.h"

/*^************************************************/
#ifdef  __CTDJOB02CLI__		/* Client-Side Version of Job Q Reader */
#ifndef __CTDJOB02CLIPTRS__	/* Client-Side Version of Job Q Reader - Using function pointers */
#define __CTJOBS_H__
#define ctgetmem(a)	mballc(1, (UINT)(a))
#define ctputmem(a)     mbfree((pVOID)(a))
#endif
#endif
/*~************************************************/

#ifndef __CTJOBS_H__

/****************************************************************************/
/* Prototypes of server functions that will be called from communications DLL */
#ifdef PROTOTYPE

#ifndef __CTDJOB02CLI__	/* Client-Side Version of Job Q Reader */
typedef pCTSTATV	*SvctstatvFuncPtr;
#endif

typedef	 pNINT		SvcttflgFuncPtr;
#ifdef ctPortWIN32
typedef long		SvtlsIndexFuncPtr;
#endif
typedef  pTEXT        	(*SvmballcFuncPtr)(NINT numobj,UINT sizobj);
typedef  VOID         	(*SvmbfreeFuncPtr)(pVOID objptr);

#if (defined(ctPortUNIX) && defined(__PTHREAD__))
typedef	 NINT		(*Svpthread_OWNERFuncPtr)(VOID);
#endif

typedef ctCONV  VOID  (ctDECL *SvctThrdExitFuncPtr)(VOID );
typedef ctCONV  NINT  (ctDECL *SvctThrdMutexRelFuncPtr)(pctMUTEX );
typedef ctCONV  NINT  (ctDECL *SvctThrdMutexGetFuncPtr)(pctMUTEX );
typedef ctCONV  COUNT (ctDECL *SvSTPUSRFuncPtr)(VOID );
typedef ctCONV  COUNT (ctDECL *SvLOKRECFuncPtr)(COUNT datno,COUNT lokmod,LONG recbyt);
typedef ctCONV  LONG  (ctDECL *SvGETCURPFuncPtr)(COUNT datno);
typedef ctCONV  COUNT (ctDECL *SvDELVRECFuncPtr)(COUNT datno);
typedef ctCONV  COUNT (ctDECL *SvDELRECFuncPtr)(COUNT datno);
typedef ctCONV  COUNT (ctDECL *SvGTEVRECFuncPtr)(COUNT keyno,pVOID target,pVOID recptr,pVRLEN plen);
typedef ctCONV  COUNT (ctDECL *SvGTERECFuncPtr)(COUNT keyno,pVOID target,pVOID recptr);
typedef ctCONV  COUNT (ctDECL *SvADDVRECFuncPtr)(COUNT datno,pVOID recptr,VRLEN varlen);
typedef ctCONV  COUNT (ctDECL *SvADDRECFuncPtr)(COUNT datno,pVOID recptr);
typedef ctCONV  LONG  (ctDECL *SvSETOPSFuncPtr)(LONG ops,VRLEN dat);
typedef ctCONV  LONG  (ctDECL *SvGETFILFuncPtr)(COUNT filno,COUNT mode);
typedef ctCONV  COUNT (ctDECL *SvOPNRFILFuncPtr)(COUNT filno,pTEXT filnam,COUNT filmod);
typedef ctCONV  NINT  (ctDECL *SvctThrdSleepFuncPtr)(LONG );
typedef ctCONV  COUNT (ctDECL *SvINTISAMXFuncPtr)(COUNT bufs,COUNT fils,COUNT sect,COUNT dbufs,
					COUNT userprof,pTEXT userid,pTEXT userword,pTEXT servname);
typedef ctCONV LONG (ctDECL *SvCTUSERFuncPtr)(pTEXT command,pTEXT bufptr,VRLEN bufsiz);
typedef ctCONV  COUNT (ctDECL *SvGETNAMFuncPtr)(COUNT filno,pTEXT nambuf,VRLEN buflen,COUNT mode);
typedef ctCONV  COUNT (ctDECL *SvPUTDODAFuncPtr)(COUNT datno,pDATOBJ doda,UCOUNT numfld);
typedef ctCONV  COUNT (ctDECL *SvCREIFILX8FuncPtr)(struct ifil ctMEM *ifilptr,pTEXT dataextn,
	pTEXT indxextn,LONG permmask,pTEXT groupid,pTEXT fileword,
	pXCREblk pxcreblk);
typedef ctCONV  COUNT (ctDECL *SvDELRFILFuncPtr)(COUNT datno);
typedef ctCONV  NINT  (ctDECL *SvctThrdTermFuncPtr)(VOID );
typedef ctCONV  NINT  (ctDECL *SvctThrdMutexClsFuncPtr)(pctMUTEX );
typedef ctCONV  NINT  (ctDECL *SvctThrdCreateFuncPtr)(pctFUNC ,pVOID ,pVOID ,LONG );
typedef ctCONV  NINT  (ctDECL *SvctThrdMutexInitFuncPtr)(pctMUTEX );
typedef ctCONV  NINT  (ctDECL *SvctThrdInitFuncPtr)(NINT ,LONG ,pctINIT );
typedef ctCONV  COUNT (ctDECL *SvSETNODEFuncPtr)(pTEXT );


typedef NINT	(*Svctrt_printfFuncPtr)( cpTEXT fmt, ... );
typedef pTEXT   (*SvctgetmemFuncPtr)(VRLEN iosize);
typedef VOID    (*SvctputmemFuncPtr)(pTEXT loc);
typedef COUNT   (*SvctrcvlogFuncPtr)(pTEXT msg,NINT err);

typedef ctCONV  COUNT (ctDECL *SvBLKIRECFuncPtr)(COUNT filno,NINT opcode,LONG timeoutsec,pTEXT blockcond,pVOID target,pVOID recptr,pVRLEN plen);

typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbLogonFuncPtr)(CTHANDLE Handle, pTEXT dbengine, pTEXT userid, pTEXT password);
typedef ctdbEXPORT CTHANDLE 	 (ctdbDECL *SvctdbAllocSessionFuncPtr)(CTSESSION_TYPE SessionType);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbCreateTableFuncPtr)(CTHANDLE Handle, pTEXT TableName, CTCREATE_MODE CreateMode);
typedef ctdbEXPORT CTHANDLE 	 (ctdbDECL *SvctdbAddFieldFuncPtr)(CTHANDLE Handle, pTEXT FieldName, CTDBTYPE FieldType, VRLEN FieldLength);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbOpenTableFuncPtr)(CTHANDLE Handle, pTEXT TableName, CTOPEN_MODE OpenMode);
typedef ctdbEXPORT CTHANDLE 	 (ctdbDECL *SvctdbAllocTableFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTHANDLE 	 (ctdbDECL *SvctdbAllocRecordFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbWriteRecordFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbSetFieldAsStringFuncPtr)(CTHANDLE Handle, NINT FieldNbr, CTSTRING Value);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbClearRecordFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbNextRecordFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbGetFieldAsStringFuncPtr)(CTHANDLE Handle, NINT FieldNbr, CTSTRING pValue, VRLEN size);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbFirstRecordFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT VOID 	 (ctdbDECL *SvctdbFreeSessionFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT VOID 	 (ctdbDECL *SvctdbFreeTableFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT VOID 	 (ctdbDECL *SvctdbFreeRecordFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbLogoutFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbCloseTableFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbDeleteRecordFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbUpdateCreateModeFuncPtr)(CTHANDLE Handle, CTCREATE_MODE mode);
typedef ctdbEXPORT CTCREATE_MODE (ctdbDECL *SvctdbGetTableCreateModeFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT NINT          (ctdbDECL *SvctdbGetFieldNumberByNameFuncPtr)(CTHANDLE Handle, pTEXT FieldName);
typedef ctdbEXPORT NINT          (ctdbDECL *SvctdbGetIdxnoByNameFuncPtr)(CTHANDLE Handle, pTEXT indexname);

typedef ctdbEXPORT pVOID         (ctdbDECL *SvctdbGetRecordBufferFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT VRLEN         (ctdbDECL *SvctdbGetRecordLengthFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT VRLEN         (ctdbDECL *SvctdbGetRecordSizeFuncPtr)(CTHANDLE Handle);

typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbHelloWorldFuncPtr)(pTEXT HelloFileName,pTEXT HelloTextData,NINT HelloNintData, ULONG HelloULongData, CTFLOAT HelloFloatData); /* CTDB HELLO WORLD */

typedef ctdbEXPORT VOID          (ctdbDECL *SvctdbFreeDatabaseFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbDropTableFuncPtr)(CTHANDLE Handle, pTEXT Name);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbAddTableFuncPtr)(CTHANDLE Handle, pTEXT Name, pTEXT Path);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbAddTableXtdFuncPtr)(CTHANDLE Handle, pTEXT Name, pTEXT PhysicName, pTEXT Path);
typedef NINT                              (*SvctSQLImportTableFuncPtr)(pCTSQLIMPOPTS pctsqlimpopts);
typedef ctCONV     COUNT         (ctDECL   *SvCLIFILFuncPtr)(struct ifil ctMEM *ifilptr);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbConnectFuncPtr)(CTHANDLE Handle, pTEXT Name);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbCreateDatabaseFuncPtr)(CTHANDLE Handle, pTEXT Name, pTEXT Path);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetPathPrefixFuncPtr)(CTHANDLE Handle, pTEXT path);
typedef ctdbEXPORT CTHANDLE      (ctdbDECL *SvctdbAllocDatabaseFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbCreateSessionFuncPtr)(CTHANDLE Handle, pTEXT dbengine, pTEXT userid, pTEXT password);
typedef ctCONV     LONG          (ctDECL   *SvCTSQLCTLFuncPtr)(pTEXT ctlbufptr,VRLEN ctlbufsiz, pTEXT inbufptr,VRLEN inbufsiz,pTEXT outbufptr,VRLEN outbufsiz);
typedef ctCONV     COUNT         (ctDECL   *SvSYSCFGFuncPtr)(pVOID bufptr);
typedef ctCONV     LONG          (ctDECL   *SvFRSKEYFuncPtr)(COUNT keyno,pVOID idxval);
typedef ctCONV     LONG          (ctDECL   *SvNXTKEYFuncPtr)(COUNT keyno,pVOID idxval);
typedef ctCONV     COUNT         (ctDECL   *SvEQLRECFuncPtr)(COUNT keyno,pVOID target,pVOID recptr);
typedef ctCONV     COUNT         (ctDECL   *SvEQLVRECFuncPtr)(COUNT keyno,pVOID target,pVOID recptr,pVRLEN plen);
typedef ctCONV     pTEXT         (ctDECL   *SvGETCURKFuncPtr)(COUNT keyno,pVOID idxval,pVRLEN plen);
typedef ctCONV     pTEXT         (ctDECL   *SvTFRMKEYFuncPtr)(COUNT keyno,pVOID tarptr);
typedef ctCONV     COUNT         (ctDECL   *SvRWTRECFuncPtr)(COUNT datno,pVOID recptr);
typedef ctCONV     COUNT         (ctDECL   *SvCLISAMFuncPtr)(VOID);
typedef ctCONV     LONG          (ctDECL   *SvTRANBEGFuncPtr)(COUNT mode);
typedef ctCONV     COUNT         (ctDECL   *SvTRANENDFuncPtr)(COUNT mode);
typedef ctCONV     COUNT         (ctDECL   *SvTRANABTFuncPtr)(VOID);
typedef ctCONV     COUNT         (ctDECL   *SvLKISAMFuncPtr)(COUNT lokmod);
typedef ctCONV     NINT          (ctDECL   *SvctThrdAttachFuncPtr)(VOID);
typedef ctCONV     NINT          (ctDECL   *SvctThrdDetachFuncPtr)(VOID);
typedef ctCONV     NINT          (ctDECL   *SvctThrdBlockGetFuncPtr)(pctBLOCK block,LONG timeout);
typedef ctCONV     NINT          (ctDECL   *SvctThrdBlockRelFuncPtr)(pctBLOCK block);
typedef ctCONV     COUNT         (ctDECL   *SvTRANRSTFuncPtr)(COUNT savpnt);
typedef ctCONV     COUNT         (ctDECL   *SvPUTHDRFuncPtr)(COUNT filno,LONG hdrval,COUNT mode);
typedef ctCONV     COUNT         (ctDECL   *SvRWTVRECFuncPtr)(COUNT datno, pVOID recbuf, VRLEN reclen);
typedef ctCONV     COUNT         (ctDECL   *SvFRSVSETFuncPtr)(COUNT keyno,pVOID target,pVOID recptr,COUNT siglen,pVRLEN plen);
typedef ctCONV     COUNT         (ctDECL   *SvFRSSETFuncPtr)(COUNT keyno,pVOID target,pVOID recptr,COUNT siglen);
typedef ctCONV     COUNT         (ctDECL   *SvNXTVSETFuncPtr)(COUNT keyno,pVOID recptr,pVRLEN plen);
typedef ctCONV     COUNT         (ctDECL   *SvNXTSETFuncPtr)(COUNT keyno,pVOID recptr);

typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetFieldAsSignedFuncPtr)(CTHANDLE Handle, NINT FieldNbr, CTSIGNED Value);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbGetFieldAsTimeFuncPtr)(CTHANDLE Handle, NINT FieldNbr, pCTTIME pValue);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbCurrentTimeFuncPtr)(pCTTIME pTime);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *Sv_ctdbRecordSetSizeFuncPtr)(pCTDBRECORD pRecord, VRLEN reclen);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *Sv_ctdbUpdateRecordFuncPtr)(pCTDBRECORD pRecord, const CTBOOL isNew);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetNewRecordFuncPtr)(CTHANDLE Handle, CTBOOL flag);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbBeginFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbPrepareCommitFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbCommitFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbAbortFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbGetErrorFuncPtr)(CTHANDLE Handle);
#ifdef CTDB_CNDX_IDX
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbUpdateCndxIndexByNameFuncPtr)(CTHANDLE Handle, pTEXT indexname, pTEXT cndexpr);
#endif
typedef ctdbEXPORT CTHANDLE      (ctdbDECL *SvctdbAddSegmentByNameFuncPtr)(CTHANDLE Handle, NINT IndexNbr, pTEXT FieldName, CTSEG_MODE SegMode);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetIndexEmptyCharFuncPtr)(CTHANDLE Handle, NINT EmptyChar);
typedef ctdbEXPORT CTHANDLE      (ctdbDECL *SvctdbAddIndexFuncPtr)(CTHANDLE Handle, pTEXT name, CTDBKEY key_type, CTBOOL AllowDuplicates, CTBOOL NullFlag);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbCurrentDateFuncPtr)(pCTDATE pDate);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetFieldAsDateFuncPtr)(CTHANDLE Handle, NINT FieldNbr, CTDATE Value);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetFieldAsTimeFuncPtr)(CTHANDLE Handle, NINT FieldNbr, CTTIME Value);

typedef ctdbEXPORT CTBOOL        (ctdbDECL *SvctdbLocateRecordFuncPtr)(CTHANDLE Handle, CTLOC_MODE LocateMode);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetRecordCriteriaFuncPtr)(CTHANDLE Handle, CTLOC_MODE LocateMode);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbUpdateRecordCriteriaFuncPtr)(CTHANDLE Handle, CTLOC_MODE LocateMode);
typedef ctdbEXPORT CTHANDLE      (ctdbDECL *SvctdbGetBestIndexFuncPtr)(CTHANDLE Handle, pCTDBLIST fieldNameList, CTLOC_MODE LocateMode);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbAddLocateCriteriaFuncPtr)(CTHANDLE Handle, CTSTRING LocateFieldName, CTSTRING LocateFieldValue);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbFindRecordFuncPtr)(CTHANDLE Handle, CTFIND_MODE FindMode);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbRecordSetOnFuncPtr)(CTHANDLE Handle, NINT siglen);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbRecordSetOffFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTBOOL        (ctdbDECL *SvctdbIsRecordSetOnFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetFieldAsUnsignedFuncPtr)(CTHANDLE Handle, NINT FieldNbr, CTUNSIGNED Value);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbGetFieldAsUnsignedFuncPtr)(CTHANDLE Handle, NINT FieldNbr, pCTUNSIGNED pValue);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetDefaultIndexByNameFuncPtr)(CTHANDLE Handle, pTEXT name);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbGetFieldAsSignedFuncPtr)(CTHANDLE Handle, NINT FieldNbr, pCTSIGNED pValue);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbReadRecordFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbUnlockFuncPtr)(CTHANDLE Handle);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbLockFuncPtr)(CTHANDLE Handle, CTLOCK_MODE mode);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetDefaultIndexFuncPtr)(CTHANDLE Handle, NINT indexno);
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbUpdateCndxIndexFuncPtr)(CTHANDLE Handle, NINT indexnbr, pTEXT cndexpr);
typedef ctdbEXPORT NINT	         (ctdbDECL *SvctdbGetIdxnoByNumberFuncPtr)(CTHANDLE Handle, NINT index);
typedef ctdbEXPORT CTDBRET 	     (ctdbDECL *SvctdbCloneTableFuncPtr)(CTHANDLE tarHandle, pTEXT tarTableName, CTHANDLE srcHandle);

/* RAB:HELPDLL:HERE 1 */
#else 	/* ~PROTOTYPE */

typedef pCTSTATV	*SvctstatvFuncPtr;
typedef	 pNINT		SvcttflgFuncPtr;

#ifdef ctPortWIN32
typedef long		SvtlsIndexFuncPtr;
#endif
typedef  pTEXT		(*SvmballcFuncPtr)();
typedef  VOID		(*SvmbfreeFuncPtr)();

#if (defined(ctPortUNIX) && defined(__PTHREAD__))
typedef	 NINT		(*Svpthread_OWNERFuncPtr)();
#endif

typedef ctCONV  VOID  (ctDECL *SvctThrdExitFuncPtr)();
typedef ctCONV  NINT  (ctDECL *SvctThrdMutexRelFuncPtr)();
typedef ctCONV  NINT  (ctDECL *SvctThrdMutexGetFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvSTPUSRFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvLOKRECFuncPtr)();
typedef ctCONV  LONG  (ctDECL *SvGETCURPFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvDELVRECFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvDELRECFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvGTEVRECFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvGTERECFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvADDVRECFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvADDRECFuncPtr)();
typedef ctCONV  LONG  (ctDECL *SvSETOPSFuncPtr)();
typedef ctCONV  LONG  (ctDECL *SvGETFILFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvOPNRFILFuncPtr)();
typedef ctCONV  NINT  (ctDECL *SvctThrdSleepFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvINTISAMXFuncPtr)();
typedef ctCONV LONG (ctDECL *SvCTUSERFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvGETNAMFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvPUTDODAFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvCREIFILX8FuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvDELRFILFuncPtr)();
typedef ctCONV  NINT  (ctDECL *SvctThrdTermFuncPtr)();
typedef ctCONV  NINT  (ctDECL *SvctThrdMutexClsFuncPtr)();
typedef ctCONV  NINT  (ctDECL *SvctThrdCreateFuncPtr)();
typedef ctCONV  NINT  (ctDECL *SvctThrdMutexInitFuncPtr)();
typedef ctCONV  NINT  (ctDECL *SvctThrdInitFuncPtr)();
typedef ctCONV  COUNT (ctDECL *SvSETNODEFuncPtr)();


typedef NINT  (*Svctrt_printfFuncPtr)();
typedef pTEXT (*SvctgetmemFuncPtr)();
typedef VOID  (*SvctputmemFuncPtr)();
typedef COUNT (*SvctrcvlogFuncPtr)();

typedef ctCONV  COUNT (ctDECL *SvBLKIRECFuncPtr)();

typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbLogonFuncPtr)();
typedef ctdbEXPORT CTHANDLE 	 (ctdbDECL *SvctdbAllocSessionFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbCreateTableFuncPtr)();
typedef ctdbEXPORT CTHANDLE 	 (ctdbDECL *SvctdbAddFieldFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbOpenTableFuncPtr)();
typedef ctdbEXPORT CTHANDLE 	 (ctdbDECL *SvctdbAllocTableFuncPtr)();
typedef ctdbEXPORT CTHANDLE 	 (ctdbDECL *SvctdbAllocRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbWriteRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbSetFieldAsStringFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbClearRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbNextRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbGetFieldAsStringFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbFirstRecordFuncPtr)();
typedef ctdbEXPORT VOID 	 (ctdbDECL *SvctdbFreeSessionFuncPtr)();
typedef ctdbEXPORT VOID 	 (ctdbDECL *SvctdbFreeTableFuncPtr)();
typedef ctdbEXPORT VOID 	 (ctdbDECL *SvctdbFreeRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbLogoutFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbCloseTableFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbDeleteRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbUpdateCreateModeFuncPtr)();
typedef ctdbEXPORT CTCREATE_MODE (ctdbDECL *SvctdbGetTableCreateModeFuncPtr)();
typedef ctdbEXPORT NINT          (ctdbDECL *SvctdbGetFieldNumberByNameFuncPtr)();
typedef ctdbEXPORT NINT          (ctdbDECL *SvctdbGetIdxnoByNameFuncPtr)();
typedef ctdbEXPORT pVOID         (ctdbDECL *SvctdbGetRecordBufferFuncPtr)();
typedef ctdbEXPORT VRLEN         (ctdbDECL *SvctdbGetRecordLengthFuncPtr)();
typedef ctdbEXPORT VRLEN         (ctdbDECL *SvctdbGetRecordSizeFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbHelloWorldFuncPtr)(); /* CTDB HELLO WORLD */

typedef ctdbEXPORT VOID          (ctdbDECL *SvctdbFreeDatabaseFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbDropTableFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbAddTableFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbAddTableXtdFuncPtr)();
typedef NINT                              (*SvctSQLImportTableFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvCLIFILFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbConnectFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbCreateDatabaseFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetPathPrefixFuncPtr)();
typedef ctdbEXPORT CTHANDLE      (ctdbDECL *SvctdbAllocDatabaseFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbCreateSessionFuncPtr)();
typedef ctCONV     LONG          (ctDECL   *SvCTSQLCTLFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvSYSCFGFuncPtr)();
typedef ctCONV     LONG          (ctDECL   *SvFRSKEYFuncPtr)();
typedef ctCONV     LONG          (ctDECL   *SvNXTKEYFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvEQLRECFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvEQLVRECFuncPtr)();
typedef ctCONV     pTEXT         (ctDECL   *SvGETCURKFuncPtr)();
typedef ctCONV     pTEXT         (ctDECL   *SvTFRMKEYFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvRWTRECFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvCLISAMFuncPtr)();
typedef ctCONV     LONG          (ctDECL   *SvTRANBEGFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvTRANENDFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvTRANABTFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvLKISAMFuncPtr)();
typedef ctCONV     NINT          (ctDECL   *SvctThrdAttachFuncPtr)();
typedef ctCONV     NINT          (ctDECL   *SvctThrdDetachFuncPtr)();
typedef ctCONV     NINT          (ctDECL   *SvctThrdBlockGetFuncPtr)();
typedef ctCONV     NINT          (ctDECL   *SvctThrdBlockRelFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvTRANRSTFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvPUTHDRFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvRWTVRECFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvFRSVSETFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvFRSSETFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvNXTVSETFuncPtr)();
typedef ctCONV     COUNT         (ctDECL   *SvNXTSETFuncPtr)();

typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetFieldAsSignedFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbGetFieldAsTimeFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbCurrentTimeFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *Sv_ctdbRecordSetSizeFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *Sv_ctdbUpdateRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetNewRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbBeginFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbPrepareCommitFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbCommitFuncPtr)();
typedef ctdbEXPORT CTDBRET 	 (ctdbDECL *SvctdbAbortFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbGetErrorFuncPtr)();
#ifdef CTDB_CNDX_IDX
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbUpdateCndxIndexByNameFuncPtr)();
#endif
typedef ctdbEXPORT CTHANDLE      (ctdbDECL *SvctdbAddSegmentByNameFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetIndexEmptyCharFuncPtr)();
typedef ctdbEXPORT CTHANDLE      (ctdbDECL *SvctdbAddIndexFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbCurrentDateFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetFieldAsDateFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetFieldAsTimeFuncPtr)();
typedef ctdbEXPORT CTBOOL        (ctdbDECL *SvctdbLocateRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetRecordCriteriaFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbUpdateRecordCriteriaFuncPtr)();
typedef ctdbEXPORT CTHANDLE      (ctdbDECL *SvctdbGetBestIndexFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbAddLocateCriteriaFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbFindRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbRecordSetOnFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbRecordSetOffFuncPtr)();
typedef ctdbEXPORT CTBOOL        (ctdbDECL *SvctdbIsRecordSetOnFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetFieldAsUnsignedFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbGetFieldAsUnsignedFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetDefaultIndexByNameFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbGetFieldAsSignedFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbReadRecordFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbUnlockFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbLockFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbSetDefaultIndexFuncPtr)();
typedef ctdbEXPORT CTDBRET       (ctdbDECL *SvctdbUpdateCndxIndexFuncPtr)();
typedef ctdbEXPORT NINT	         (ctdbDECL *SvctdbGetIdxnoByNumberFuncPtr)();
typedef ctdbEXPORT CTDBRET 	     (ctdbDECL *SvctdbCloneTableFuncPtr)();

/* RAB:HELPDLL:HERE 2 */
#endif 	/* ~PROTOTYPE */

typedef struct SCTDBFuncStruct {
Svctrt_printfFuncPtr			Svctrt_printf;
SvctgetmemFuncPtr			Svctgetmem;
SvctputmemFuncPtr			Svctputmem;
SvctrcvlogFuncPtr			Svctrcvlog;
SvBLKIRECFuncPtr			SvBLKIREC;

SvctdbLogonFuncPtr			SvctdbLogon;
SvctdbAllocSessionFuncPtr              	SvctdbAllocSession;
SvctdbCreateTableFuncPtr               	SvctdbCreateTable;
SvctdbAddFieldFuncPtr                  	SvctdbAddField;
SvctdbOpenTableFuncPtr                 	SvctdbOpenTable;
SvctdbAllocTableFuncPtr                	SvctdbAllocTable;
SvctdbAllocRecordFuncPtr               	SvctdbAllocRecord;
SvctdbWriteRecordFuncPtr               	SvctdbWriteRecord;
SvctdbSetFieldAsStringFuncPtr          	SvctdbSetFieldAsString;
SvctdbClearRecordFuncPtr		SvctdbClearRecord;
SvctdbNextRecordFuncPtr                	SvctdbNextRecord;
SvctdbGetFieldAsStringFuncPtr          	SvctdbGetFieldAsString;
SvctdbFirstRecordFuncPtr               	SvctdbFirstRecord;
SvctdbFreeSessionFuncPtr               	SvctdbFreeSession;
SvctdbFreeTableFuncPtr                 	SvctdbFreeTable;
SvctdbFreeRecordFuncPtr                	SvctdbFreeRecord;
SvctdbLogoutFuncPtr                    	SvctdbLogout;
SvctdbCloseTableFuncPtr                	SvctdbCloseTable;
SvctdbDeleteRecordFuncPtr              	SvctdbDeleteRecord;
SvctdbUpdateCreateModeFuncPtr          	SvctdbUpdateCreateMode;
SvctdbGetTableCreateModeFuncPtr        	SvctdbGetTableCreateMode;
SvctdbGetFieldNumberByNameFuncPtr	SvctdbGetFieldNumberByName;
SvctdbGetIdxnoByNameFuncPtr		SvctdbGetIdxnoByName;
SvctdbGetRecordBufferFuncPtr		SvctdbGetRecordBuffer;
SvctdbGetRecordLengthFuncPtr		SvctdbGetRecordLength;
SvctdbGetRecordSizeFuncPtr		SvctdbGetRecordSize;
SvctdbCloneTableFuncPtr               	SvctdbCloneTable;
SvctdbHelloWorldFuncPtr			SvctdbHelloWorld;

#ifndef __CTDJOB02CLI__	/* Client-Side Version of Job Q Reader */
SvctstatvFuncPtr			Svctstatv;
#endif
SvcttflgFuncPtr				Svcttflg;

#ifdef ctPortWIN32
SvtlsIndexFuncPtr			SvtlsIndex;
#endif
SvmballcFuncPtr				Svmballc;
SvmbfreeFuncPtr				Svmbfree;

#if (defined(ctPortUNIX) && defined(__PTHREAD__))
Svpthread_OWNERFuncPtr			Svpthread_OWNER;
#endif

SvctThrdExitFuncPtr			SvctThrdExit;
SvctThrdMutexRelFuncPtr			SvctThrdMutexRel;
SvctThrdMutexGetFuncPtr			SvctThrdMutexGet;
SvSTPUSRFuncPtr				SvSTPUSR;
SvLOKRECFuncPtr				SvLOKREC;
SvGETCURPFuncPtr			SvGETCURP;
SvDELVRECFuncPtr			SvDELVREC;
SvDELRECFuncPtr				SvDELREC;
SvGTEVRECFuncPtr			SvGTEVREC;
SvGTERECFuncPtr				SvGTEREC;
SvADDVRECFuncPtr			SvADDVREC;
SvADDRECFuncPtr				SvADDREC;
SvSETOPSFuncPtr				SvSETOPS;
SvGETFILFuncPtr				SvGETFIL;
SvOPNRFILFuncPtr			SvOPNRFIL;
SvctThrdSleepFuncPtr			SvctThrdSleep;
SvINTISAMXFuncPtr			SvINTISAMX;
SvCTUSERFuncPtr				SvCTUSER;
SvGETNAMFuncPtr				SvGETNAM;
SvPUTDODAFuncPtr			SvPUTDODA;
#ifdef ctHUGEFILE
SvCREIFILX8FuncPtr			SvCREIFILX8;
#endif
SvDELRFILFuncPtr			SvDELRFIL;
SvctThrdTermFuncPtr			SvctThrdTerm;
SvctThrdMutexClsFuncPtr			SvctThrdMutexCls;
SvctThrdCreateFuncPtr			SvctThrdCreate;
SvctThrdMutexInitFuncPtr		SvctThrdMutexInit;
SvctThrdInitFuncPtr			SvctThrdInit;
SvSETNODEFuncPtr			SvSETNODE;

SvctdbFreeDatabaseFuncPtr		SvctdbFreeDatabase;
SvctdbDropTableFuncPtr			SvctdbDropTable;
SvctdbAddTableFuncPtr			SvctdbAddTable;
SvctdbAddTableXtdFuncPtr			SvctdbAddTableXtd;
SvctSQLImportTableFuncPtr		SvctSQLImportTable;
SvCLIFILFuncPtr				SvCLIFIL;
SvctdbConnectFuncPtr			SvctdbConnect;
SvctdbCreateDatabaseFuncPtr		SvctdbCreateDatabase;
SvctdbSetPathPrefixFuncPtr		SvctdbSetPathPrefix;
SvctdbAllocDatabaseFuncPtr		SvctdbAllocDatabase;
SvctdbCreateSessionFuncPtr		SvctdbCreateSession;
SvCTSQLCTLFuncPtr			SvCTSQLCTL;
SvSYSCFGFuncPtr				SvSYSCFG;
SvFRSKEYFuncPtr				SvFRSKEY;
SvNXTKEYFuncPtr				SvNXTKEY;
SvEQLRECFuncPtr				SvEQLREC;
SvEQLVRECFuncPtr			SvEQLVREC;
SvGETCURKFuncPtr			SvGETCURK;
SvTFRMKEYFuncPtr			SvTFRMKEY;
SvRWTRECFuncPtr				SvRWTREC;
SvCLISAMFuncPtr				SvCLISAM;
SvTRANBEGFuncPtr			SvTRANBEG;
SvTRANENDFuncPtr			SvTRANEND;
SvTRANABTFuncPtr			SvTRANABT;
SvLKISAMFuncPtr				SvLKISAM;
SvctThrdAttachFuncPtr			SvctThrdAttach;
SvctThrdDetachFuncPtr			SvctThrdDetach;
SvctThrdBlockGetFuncPtr			SvctThrdBlockGet;
SvctThrdBlockRelFuncPtr			SvctThrdBlockRel;
SvTRANRSTFuncPtr			SvTRANRST;
SvPUTHDRFuncPtr				SvPUTHDR;
SvRWTVRECFuncPtr			SvRWTVREC;
SvFRSVSETFuncPtr			SvFRSVSET;
SvFRSSETFuncPtr				SvFRSSET;
SvNXTVSETFuncPtr			SvNXTVSET;
SvNXTSETFuncPtr				SvNXTSET;

SvctdbSetFieldAsSignedFuncPtr		SvctdbSetFieldAsSigned;
SvctdbGetFieldAsTimeFuncPtr		SvctdbGetFieldAsTime;
SvctdbCurrentTimeFuncPtr		SvctdbCurrentTime;
Sv_ctdbRecordSetSizeFuncPtr		Sv_ctdbRecordSetSize;
Sv_ctdbUpdateRecordFuncPtr		Sv_ctdbUpdateRecord;
SvctdbSetNewRecordFuncPtr		SvctdbSetNewRecord;
SvctdbBeginFuncPtr			SvctdbBegin;
SvctdbPrepareCommitFuncPtr			SvctdbPrepareCommit;
SvctdbCommitFuncPtr             	SvctdbCommit;
SvctdbAbortFuncPtr              	SvctdbAbort;
SvctdbGetErrorFuncPtr			SvctdbGetError;
#ifdef CTDB_CNDX_IDX
SvctdbUpdateCndxIndexByNameFuncPtr	SvctdbUpdateCndxIndexByName;
#endif
SvctdbAddSegmentByNameFuncPtr		SvctdbAddSegmentByName;
SvctdbSetIndexEmptyCharFuncPtr		SvctdbSetIndexEmptyChar;
SvctdbAddIndexFuncPtr			SvctdbAddIndex;
SvctdbCurrentDateFuncPtr		SvctdbCurrentDate;
SvctdbSetFieldAsDateFuncPtr		SvctdbSetFieldAsDate;
SvctdbSetFieldAsTimeFuncPtr		SvctdbSetFieldAsTime;

SvctdbLocateRecordFuncPtr		SvctdbLocateRecord;
SvctdbSetRecordCriteriaFuncPtr	SvctdbSetRecordCriteria;
SvctdbUpdateRecordCriteriaFuncPtr	SvctdbUpdateRecordCriteria;
SvctdbGetBestIndexFuncPtr	    SvctdbGetBestIndex;
SvctdbAddLocateCriteriaFuncPtr	SvctdbAddLocateCriteria;
SvctdbFindRecordFuncPtr			SvctdbFindRecord;
SvctdbRecordSetOnFuncPtr                SvctdbRecordSetOn;
SvctdbRecordSetOffFuncPtr               SvctdbRecordSetOff;
SvctdbIsRecordSetOnFuncPtr              SvctdbIsRecordSetOn;
SvctdbSetFieldAsUnsignedFuncPtr         SvctdbSetFieldAsUnsigned;
SvctdbGetFieldAsUnsignedFuncPtr         SvctdbGetFieldAsUnsigned;
SvctdbSetDefaultIndexByNameFuncPtr      SvctdbSetDefaultIndexByName;
SvctdbGetFieldAsSignedFuncPtr		SvctdbGetFieldAsSigned;
SvctdbReadRecordFuncPtr			SvctdbReadRecord;
SvctdbUnlockFuncPtr                     SvctdbUnlock;
SvctdbLockFuncPtr                       SvctdbLock;
SvctdbSetDefaultIndexFuncPtr		SvctdbSetDefaultIndex;
#ifdef CTDB_CNDX_IDX
SvctdbUpdateCndxIndexFuncPtr		SvctdbUpdateCndxIndex;
#endif
SvctdbGetIdxnoByNumberFuncPtr		SvctdbGetIdxnoByNumber;

/* RAB:HELPDLL:HERE 3 */
} SCTDBFuncPtrs, ctMEM *pSCTDBFuncPtrs;


#ifdef ctDLLLIB					/* if included in DLL */

pSCTDBFuncPtrs FPtr;				/* DLL global pointer */

#define ctstatv				(FPtr->Svctstatv)
#define cttflg				(*(FPtr->Svcttflg))
#ifdef ctPortWIN32
#define tlsIndex			(FPtr->SvtlsIndex)
#endif

#undef  mballc
#undef  mbfree
#define mballc				(FPtr->Svmballc)
#define mbfree				(FPtr->Svmbfree)

#if (defined(ctPortUNIX) && defined(__PTHREAD__))
#undef  OWNER
#define OWNER				(FPtr->Svpthread_OWNER)()
#endif

#define ctThrdExit			(FPtr->SvctThrdExit)
#define ctThrdMutexRel			(FPtr->SvctThrdMutexRel)
#define ctThrdMutexGet			(FPtr->SvctThrdMutexGet)
#define STPUSR				(FPtr->SvSTPUSR)
#define LOKREC				(FPtr->SvLOKREC)
#define GETCURP				(FPtr->SvGETCURP)
#define DELVREC				(FPtr->SvDELVREC)
#define DELREC				(FPtr->SvDELREC)
#define GTEVREC				(FPtr->SvGTEVREC)
#define GTEREC				(FPtr->SvGTEREC)
#define ADDVREC				(FPtr->SvADDVREC)
#define ADDREC				(FPtr->SvADDREC)
#define SETOPS				(FPtr->SvSETOPS)
#define GETFIL				(FPtr->SvGETFIL)
#define OPNRFIL				(FPtr->SvOPNRFIL)
#define ctThrdSleep			(FPtr->SvctThrdSleep)
#define INTISAMX			(FPtr->SvINTISAMX)
#define CTUSER				(FPtr->SvCTUSER)
#define GETNAM				(FPtr->SvGETNAM)
#define PUTDODA				(FPtr->SvPUTDODA)
#define CREIFILX8			(FPtr->SvCREIFILX8)
#define DELRFIL				(FPtr->SvDELRFIL)
#define ctThrdTerm			(FPtr->SvctThrdTerm)
#define ctThrdMutexCls			(FPtr->SvctThrdMutexCls)
#define ctThrdCreate			(FPtr->SvctThrdCreate)
#define ctThrdMutexInit			(FPtr->SvctThrdMutexInit)
#define ctThrdInit			(FPtr->SvctThrdInit)
#define SETNODE				(FPtr->SvSETNODE)


#undef  ctrt_printf
#define ctrt_printf				(FPtr->Svctrt_printf)
#define ctgetmem				(FPtr->Svctgetmem)
#define ctputmem				(FPtr->Svctputmem)
#define ctrcvlog				(FPtr->Svctrcvlog)

#define BLKIREC					(FPtr->SvBLKIREC)

#define ctdbLogon				(FPtr->SvctdbLogon)
#define ctdbAllocSession			(FPtr->SvctdbAllocSession)
#define ctdbCreateTable				(FPtr->SvctdbCreateTable)
#define ctdbAddField				(FPtr->SvctdbAddField)
#define ctdbOpenTable				(FPtr->SvctdbOpenTable)
#define ctdbAllocTable				(FPtr->SvctdbAllocTable)
#define ctdbAllocRecord				(FPtr->SvctdbAllocRecord)
#define ctdbWriteRecord				(FPtr->SvctdbWriteRecord)
#define ctdbSetFieldAsString			(FPtr->SvctdbSetFieldAsString)
#define ctdbClearRecord				(FPtr->SvctdbClearRecord)
#define ctdbNextRecord				(FPtr->SvctdbNextRecord)
#define ctdbGetFieldAsString			(FPtr->SvctdbGetFieldAsString)
#define ctdbFirstRecord				(FPtr->SvctdbFirstRecord)
#define ctdbFreeSession				(FPtr->SvctdbFreeSession)
#define ctdbFreeTable				(FPtr->SvctdbFreeTable)
#define ctdbFreeRecord				(FPtr->SvctdbFreeRecord)
#define ctdbLogout				(FPtr->SvctdbLogout)
#define ctdbCloseTable				(FPtr->SvctdbCloseTable)
#define ctdbDeleteRecord			(FPtr->SvctdbDeleteRecord)
#define ctdbUpdateCreateMode			(FPtr->SvctdbUpdateCreateMode)
#define ctdbGetTableCreateMode			(FPtr->SvctdbGetTableCreateMode)
#define ctdbGetFieldNumberByName		(FPtr->SvctdbGetFieldNumberByName)
#define ctdbGetIdxnoByName			(FPtr->SvctdbGetIdxnoByName)
#define ctdbGetRecordBuffer			(FPtr->SvctdbGetRecordBuffer)
#define ctdbGetRecordLength			(FPtr->SvctdbGetRecordLength)
#define ctdbGetRecordSize			(FPtr->SvctdbGetRecordSize)

#define ctdbHelloWorld				(FPtr->SvctdbHelloWorld)	/* CTDB HELLO WORLD */

#define ctdbFreeDatabase			(FPtr->SvctdbFreeDatabase)
#define ctdbDropTable				(FPtr->SvctdbDropTable)
#define ctdbAddTable				(FPtr->SvctdbAddTable)
#define ctdbAddTableXtd				(FPtr->SvctdbAddTableXtd)
#define ctSQLImportTable			(FPtr->SvctSQLImportTable)
#define CLIFIL					(FPtr->SvCLIFIL)
#define ctdbConnect				(FPtr->SvctdbConnect)
#define ctdbCreateDatabase			(FPtr->SvctdbCreateDatabase)
#define ctdbSetPathPrefix			(FPtr->SvctdbSetPathPrefix)
#define ctdbAllocDatabase			(FPtr->SvctdbAllocDatabase)
#define ctdbCreateSession			(FPtr->SvctdbCreateSession)
#define CTSQLCTL				(FPtr->SvCTSQLCTL)
#define SYSCFG					(FPtr->SvSYSCFG)
#define FRSKEY					(FPtr->SvFRSKEY)
#define NXTKEY					(FPtr->SvNXTKEY)
#define EQLREC					(FPtr->SvEQLREC)
#define EQLVREC					(FPtr->SvEQLVREC)
#define GETCURK					(FPtr->SvGETCURK)
#define TFRMKEY					(FPtr->SvTFRMKEY)
#define RWTREC					(FPtr->SvRWTREC)
#define CLISAM					(FPtr->SvCLISAM)
#define TRANBEG					(FPtr->SvTRANBEG)
#define TRANEND					(FPtr->SvTRANEND)
#define TRANABT					(FPtr->SvTRANABT)
#define LKISAM					(FPtr->SvLKISAM)
#define ctThrdAttach				(FPtr->SvctThrdAttach)
#define ctThrdDetach				(FPtr->SvctThrdDetach)
#define ctThrdBlockGet				(FPtr->SvctThrdBlockGet)
#define ctThrdBlockRel				(FPtr->SvctThrdBlockRel)
#define TRANRST					(FPtr->SvTRANRST)
#define PUTHDR					(FPtr->SvPUTHDR)
#define RWTVREC					(FPtr->SvRWTVREC)
#define FRSVSET					(FPtr->SvFRSVSET)
#define FRSSET					(FPtr->SvFRSSET)
#define NXTVSET					(FPtr->SvNXTVSET)
#define NXTSET					(FPtr->SvNXTSET)

#define ctdbSetFieldAsSigned			(FPtr->SvctdbSetFieldAsSigned)
#define ctdbGetFieldAsTime			(FPtr->SvctdbGetFieldAsTime)
#define ctdbCurrentTime				(FPtr->SvctdbCurrentTime)
#define _ctdbRecordSetSize			(FPtr->Sv_ctdbRecordSetSize)
#define _ctdbUpdateRecord			(FPtr->Sv_ctdbUpdateRecord)
#define ctdbSetNewRecord			(FPtr->SvctdbSetNewRecord)
#define ctdbBegin				(FPtr->SvctdbBegin)
#define ctdbPrepareCommit			(FPtr->SvctdbPrepareCommit)
#define ctdbCommit				(FPtr->SvctdbCommit)
#define ctdbAbort				(FPtr->SvctdbAbort)

#define ctdbGetError				(FPtr->SvctdbGetError)
#ifdef CTDB_CNDX_IDX
#define ctdbUpdateCndxIndexByName               (FPtr->SvctdbUpdateCndxIndexByName)
#endif
#define ctdbAddSegmentByName                    (FPtr->SvctdbAddSegmentByName)
#define ctdbSetIndexEmptyChar                   (FPtr->SvctdbSetIndexEmptyChar)
#define ctdbAddIndex                            (FPtr->SvctdbAddIndex)
#define ctdbCurrentDate				(FPtr->SvctdbCurrentDate)
#define ctdbSetFieldAsDate			(FPtr->SvctdbSetFieldAsDate)
#define ctdbSetFieldAsTime			(FPtr->SvctdbSetFieldAsTime)

#define ctdbLocateRecord			(FPtr->SvctdbLocateRecord)
#define ctdbSetRecordCriteria		(FPtr->SvctdbSetRecordCriteria)
#define ctdbUpdateRecordCriteria		(FPtr->SvctdbUpdateRecordCriteria)
#define ctdbGetBestIndex		    (FPtr->SvctdbGetBestIndex)
#define ctdbAddLocateCriteria		(FPtr->SvctdbAddLocateCriteria)
#define ctdbFindRecord				(FPtr->SvctdbFindRecord)
#define ctdbRecordSetOn				(FPtr->SvctdbRecordSetOn)
#define ctdbRecordSetOff			(FPtr->SvctdbRecordSetOff)
#define ctdbIsRecordSetOn			(FPtr->SvctdbIsRecordSetOn)
#define ctdbSetFieldAsUnsigned			(FPtr->SvctdbSetFieldAsUnsigned)
#define ctdbGetFieldAsUnsigned			(FPtr->SvctdbGetFieldAsUnsigned)
#define ctdbSetDefaultIndexByName		(FPtr->SvctdbSetDefaultIndexByName)
#define ctdbGetFieldAsSigned			(FPtr->SvctdbGetFieldAsSigned)
#define ctdbReadRecord				(FPtr->SvctdbReadRecord)
#define ctdbUnlock				(FPtr->SvctdbUnlock)
#define ctdbLock				(FPtr->SvctdbLock)
#define ctdbSetDefaultIndex			(FPtr->SvctdbSetDefaultIndex)
#define ctdbUpdateCndxIndex			(FPtr->SvctdbUpdateCndxIndex)
#define ctdbGetIdxnoByNumber			(FPtr->SvctdbGetIdxnoByNumber)
#define ctdbCloneTable				(FPtr->SvctdbCloneTable)

/* RAB:HELPDLL:HERE 4 */
#endif /* ~ctDLLLIB */


#endif /* ~__CTJOBS_H__ */

/* end of ctjobs.h */
