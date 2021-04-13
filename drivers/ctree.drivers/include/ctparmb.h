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

#ifndef ctPARMBH
#define ctPARMBH

/* ctSIBLING_SEPLNG: Add entry for new function here */

#define FNB_INTREE			10
#define FNB_STPUSR			11
#define FNB_STPUSRA			12
#define FNB_STPSRV			13

#define FNB_CREDAT			20
#define FNB_CREIDX			21
#define FNB_CREMEM			22
#define FNB_OPNFIL			23
#define FNB_RENFIL			24
#define FNB_CLSFIL			25
#define FNB_DELFIL			26
#define FNB_CLSNAM			27
#define FNB_AVLFILNUM			28
#define FNB_TSTFILNUM			29
#define FNB_INTISAM			30
#define FNB_CREISAM			31
#define FNB_OPNISAM			32
#define FNB_CLISAM			33

#define FNB_OPNIFIL			40
#define FNB_PUTIFIL			41
#define FNB_RBLIFIL			42
#define FNB_CMPIFIL			43
#define FNB_RENIFIL			44
#define FNB_EXPIFIL			45
#define FNB_CREIFIL			46
#define FNB_PRMIIDX			47
#define FNB_RBLIIDX			48
#define FNB_TMPIIDX			49
#define FNB_DROPIDX			50
#define FNB_OPNRFIL			51
#define FNB_CLRFIL			52
#define FNB_DELRFIL			53
#define FNB_CLIFIL			54
#define FNB_DELIFIL			55

#define FNB_SETSEG			60
#define FNB_PTADMIN			61
#define FNB_CTTESTFUNC			62
#define FNB_NOTIFY			63

#define FNB_SERIALNUM			70
#define FNB_DATENT			71
#define FNB_IDXENT			72
#define FNB_ctDISTINCTest		73
#define FNB_ctDISTINCTset		74
#define FNB_LOKDYN			75
#define FNB_ctImpersonateTask		76
#define FNB_ctTransferFile		77
#define FNB_ctSEQUENCE			78
#define FNB_ctMASTERCTL			79
#define FNB_SECURITY			80
#define FNB_GETFIL			81
#define FNB_PUTCRES			82
#define FNB_GETCRES			83
#define FNB_GETCIDX			84
#define FNB_UPDCIDX			85
#define FNB_PUTDODA			86
#define FNB_SETFLTR			87
#define FNB_GETIFIL			88
#define FNB_GETDODA			89
#define FNB_GETRES			90
#define FNB_ADDRES			91
#define FNB_UPDRES			92
#define FNB_DELRES			93
#define FNB_ENARES			94
#define FNB_SETALTSEQ			95
#define FNB_SETVARBYTS			96
#define FNB_GETALTSEQ			97
#define FNB_SETDEFBLK			98
#define FNB_PUTKSEGDEF			99
#define FNB_GETKSEGDEF			100
#define FNB_GETXCREBLK			101
#define FNB_XFMKSEGDEF			102
#define FNB_UPDTICU			103
#define FNB_VERIFYidx			104
#define FNB_addIDfield			105
#define FNB_delIDfield			106
#define FNB_getIDfield			107
#define FNB_resetIDfield		108
#define FNB_wchIDfield			109
#define FNB_SETFLTRN			110
#define FNB_RESETFLTR			111
#define FNB_MEMSTAT			112
#define FNB_SETCOMPRESS			113
#define FNB_xtdatrIDfield		114
#define FNB_ctCopyFile			115
#define FNB_ctVerifyFile		116
#define FNB_GETFILX			117
#define FNB_ctDeferredIndexControl	118
#define FNB_ctRecordUpdateCallbackControl 119
#define FNB_OPNICON			120
#define FNB_CHGICON			121
#define FNB_CLSICON			122
#define FNB_ctFullText			123
#define FNB_ctAlterSchema		124
#define FNB_ctTempDir			125
#define FNB_ctReplLogFileResync		126
#define FNB_ctSyncReplControl		127
#define FNB_ctSetTransactionId		128
#define FNB_ctReplSetPosByTransactionId	129
#define FNB_PUTFIL			130
#define FNB_PUTHDR			131
#define FNB_GETMNAME			132
#define FNB_GETNAM			133
#define FNB_SETOPS			134
#define FNB_SetXtdFileOpenMode		135
#define FNB_ctSetCurrentSuperfileHost	136
#define FNB_ctGetAccountExpirationTime	137
#define FNB_ctGetConnectionInfo		138
#define FNB_UpdateRecordOffsetForKey	139
#define FNB_reset_cur			140
#define FNB_reset_cur2			141
#define FNB_GETCURP			142
#define FNB_GETCURK			143
#define FNB_GETCURKL			144
#define FNB_UPDCURI			145
#define FNB_SETCURI			146

#define FNB_NEWREC			150
#define FNB_RETREC			151
#define FNB_REDIREC			152
#define FNB_REDREC			153
#define FNB_WRTREC			154
#define FNB_LOKREC			155
#define FNB_ADDKEY			156
#define FNB_DELCHK			157
#define FNB_DELBLD			158
#define FNB_ESTKEY			159
#define FNB_RNGENT			160
#define FNB_ORDKEY			161
#define FNB_FRCKEY			162
#define FNB_GTVLEN			163
#define FNB_NEWVREC			164
#define FNB_TSTVREC			165
#define FNB_RETVREC			166
#define FNB_WRTVREC			167
#define FNB_RDVREC			168
#define FNB_ctLOKTIMOUT			169

#define FNB_LKISAM			180
#define FNB_ADDREC			181
#define FNB_RWTREC			182
#define FNB_DELREC			183
#define FNB_TESTHUGE			184
#define FNB_EQLREC			185
#define FNB_GTEREC			186
#define FNB_GTREC			187
#define FNB_LTEREC			188
#define FNB_LTREC			189
#define FNB_NXTREC			190
#define FNB_PRVREC			191
#define FNB_FRSREC			192
#define FNB_LSTREC			193
#define FNB_RRDREC			194
#define FNB_GETVLEN			195
#define FNB_ADDVREC			196
#define FNB_DELVREC			197
#define FNB_RWTVREC			198
#define FNB_REDVREC			199
#define FNB_EQLVREC			200
#define FNB_GTEVREC			201
#define FNB_GTVREC			202
#define FNB_LTEVREC			203
#define FNB_LTVREC			204
#define FNB_NXTVREC			205
#define FNB_PRVVREC			206
#define FNB_FRSVREC			207
#define FNB_LSTVREC			208
#define FNB_REDIVREC			209
#define FNB_BLKIREC			210
#define FNB_RWTPREC			211

#define FNB_LOADKEY			220
#define FNB_EQLKEY			221
#define FNB_GTEKEY			222
#define FNB_FRSKEY			223
#define FNB_LSTKEY			224
#define FNB_NXTKEY			225
#define FNB_PRVKEY			226
#define FNB_GTKEY			227
#define FNB_LTKEY			228
#define FNB_LTEKEY			229

#define FNB_ALCSET			240
#define FNB_FRESET			241
#define FNB_FRESETN			242
#define FNB_CHGSET			243
#define FNB_FRSSET			244
#define FNB_MIDSET			245
#define FNB_LSTSET			246
#define FNB_NXTSET			247
#define FNB_PRVSET			248
#define FNB_FRSVSET			249
#define FNB_MIDVSET			250
#define FNB_LSTVSET			251
#define FNB_NXTVSET			252
#define FNB_PRVVSET			253

#define FNB_ctDISTINCTestXtd		267
#define FNB_ctDISTINCTsetXtd		268
#define FNB_ESTRNG			269
#define FNB_ALCRNG			270
#define FNB_FRERNG			271
#define FNB_FRSRNG			272
#define FNB_LSTRNG			273
#define FNB_FRSVRNG			274
#define FNB_LSTVRNG			275
#define FNB_NXTRNG			276
#define FNB_PRVRNG			277
#define FNB_NXTVRNG			278
#define FNB_PRVVRNG			279
#define FNB_ALCBAT			280
#define FNB_FREBAT			281
#define FNB_FREBATN			282
#define FNB_CHGBAT			283
#define FNB_FREHST			284
#define FNB_FREHSTN			285
#define FNB_CHGHST			286
#define FNB_BATSET			287
#define FNB_BATSETX			288

#define FNB_PERFORM			300
#define FNB_USERLIST			301
#define FNB_USERINFO			302
#define FNB_CTKLUSR			303
#define FNB_SETNODE			304
#define FNB_LOKDMP			305
#define FNB_CTUSER			306
#define FNB_CTUSERX			307
#define FNB_CTSQLCTL			308
#define FNB_CTSRVCTL			309
#define FNB_ctLOKLST			310
#define FNB_ADDUSR			311
#define FNB_CHGUSR			312
#define FNB_USERINFOX			313

#define FNB_CTDIDX			320
#define FNB_CTFLUSH			321
#define FNB_SYSMON			322
#define FNB_SYSLOG			323

#define FNB_TRANBEG			330
#define FNB_TRANEND			331
#define FNB_TRANABTX			332
#define FNB_TRANRST			333
#define FNB_TRANABT			334
#define FNB_TRANCLR			335
#define FNB_SAVPCLR			336
#define FNB_TRANSAV			337
#define FNB_SPCLSAV			338
#define FNB_TRANISO			339
#define FNB_TRANBAK			340
#define FNB_CTCHKPNT			341
#define FNB_TRANUSR			342
#define FNB_TRANRDY			343

#define FNB_SETFNDVAL			350
#define FNB_SQR				351
#define FNB_CTSBLD			352
#define FNB_CLNIDX			353
#define FNB_SQL				354
#define FNB_TMPNAME			355
#define FNB_IOPERFORMANCE		356
#define FNB_IOPERFORMANCEX		357
#define FNB_SYSCFG			358
#define FNB_CTFLUSHX			359
#define FNB_CTASYNC			360
#define FNB_SNAPSHOT			361
#define FNB_SYSPUT			362
#define FNB_SETCBRBL			363
#define FNB_FILMTX			364
#define FNB_FILBLK			365
#define FNB_ctSETCFG			366
#define FNB_SEPLNG			367
#define FNB_FILWCD			368
#define FNB_QUIET			369
#define FNB_CTHIST			370
#define FNB_SETENCRYPT			371
#define FNB_SESSVAL			372
#define FNB_SESSINC			373
#define FNB_GETCBRBLST			374

#define FNB_SysQueueOpen		380
#define FNB_SysQueueClose		381
#define FNB_SysQueueWrite		382
#define FNB_SysQueueLIFOWrite		383
#define FNB_SysQueueRead		384
#define FNB_SysQueueMlen		385
#define FNB_SysQueueCount		386
#define FNB_WorkerThrdAttach		387

#define FNB_ThrdAttach			390
#define FNB_ThrdBlockCls		391
#define FNB_ThrdBlockGet		392
#define FNB_ThrdBlockInit		393
#define FNB_ThrdBlockRel		394
#define FNB_ThrdBlockWait		395
#define FNB_ThrdCreate			396
#define FNB_ThrdData			397
#define FNB_ThrdDataSet			398
#define FNB_ThrdDetach			399
#define FNB_ThrdExit			400
#define FNB_ThrdHandle			401
#define FNB_ThrdInit			402
#define FNB_ThrdLIFOWrite		403
#define FNB_ThrdMutexCls		404
#define FNB_ThrdMutexGet		405
#define FNB_ThrdMutexInit		406
#define FNB_ThrdMutexRel		407
#define FNB_ThrdMutexTry		408
#define FNB_ThrdQueueClose		409
#define FNB_ThrdQueueCount		410
#define FNB_ThrdQueueMlen		411
#define FNB_ThrdQueueOpen		412
#define FNB_ThrdQueueRead		413
#define FNB_ThrdQueueReadDirect		414
#define FNB_ThrdQueueWrite		415
#define FNB_ThrdQueueWriteDirect	416
#define FNB_ThrdSemapCls		417
#define FNB_ThrdSemapGet		418
#define FNB_ThrdSemapInit		419
#define FNB_ThrdSemapRel		420
#define FNB_ThrdSemapTry		421
#define FNB_ThrdSleep			422
#define FNB_ThrdTerm			423
#define FNB_ctReplSetPosByLogPos	424
#define FNB_ctReplSetPosByTime		425
#define FNB_ctReplGetFileName		426
#define FNB_ctReplGetNextChange		427
#define FNB_ctReplPersistMinLog		428
#define FNB_ctReplAgentOp		429
#define FNB_SWTCTREE			430
#define FNB_GETCTREE			431
#define FNB_WCHCTREE			432
#define FNB_REGCTREE			433
#define FNB_UNRCTREE			434
#define FNB_NXTCTREE			435
#define FNB_ctGetOpenFiles		436
#define FNB_ctGetFileUsers		437
#define FNB_ctGetFileLocks		438
#define FNB_ctReplSetFileFilter		439
#define FNB_TFRMKEY			440
#define FNB_frmkey			441
#define FNB_cttseg			442
#define FNB_ctuseg			443
#define FNB_frmkeyx			444
#define FNB_GetFileRegions		445
#define FNB_ctGetOpenFilesXtd		446
#define FNB_ctFILELIST			447
#define FNB_ctClusterConfig		448
#define FNB_ctTruncateFile		449
#define FNB_CTGETUEC			450
#define FNB_CTGETIEC			451
#define FNB_CTGETIFL			452
#define FNB_CTGETSEC			453
#define FNB_ctSETHGH			454
#define FNB_ctGETHGH			455
#define FNB_ctReplCheckFileFilter	456
#define FNB_addAutoSysTimeFields	457
#define FNB_RemoveAutoSysTimeFields	458
#define FNB_WhichAutoSysTimeFields	459
#define FNB_UpdateAutoSysTimeFields	460

/* when adding new function remember to increase FNB_LAST id and update the ctfnbinf array below */
#define FNB_LASTID			461

#ifdef ctDBG_FNBcoverage
#define FNBdbg(fn)	,0,fn
#else
#define FNBdbg(fn)
#endif

#ifdef ctTESTsrvdllquiet
			/*
			** a:  PREFNC skip flag
			** b: POSTFNC skip flag
			** c: ISAM level flag
			*/
#define SKP(a,b,c)	,a,b,c
#else
#define SKP(a,b,c)
#endif

enum {
	FNI_NONE   =  0x00,	/* No special attributes	*/
	FNI_SHTDWN =  0x01,	/* Shutdown function		*/
	FNI_REINIT =  0x02,	/* Initialization function	*/
	FNI_SWINST =  0x04,	/* Instance switching function	*/
	FNI_RGINST =  0x08,	/* Instance registration fnc	*/
	FNI_TRMTRD =  0x10,	/* Terminating thread fnc	*/
	/* add more flags here */
	FNI_UNUSED =  0x80	/* Unused function		*/
};

CT_FNBI ctfnbinf[FNB_LASTID] = {
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  0 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  1 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  2 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  3 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  4 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  5 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  6 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  7 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  8 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		  9 */
	{FNI_NONE FNBdbg("INTREE") SKP(NO,NO,NO)},	/*		 10 */
	{FNI_NONE FNBdbg("STPUSR") SKP(NO,NO,NO)},	/*		 11 */
	{FNI_NONE FNBdbg("STPUSRA") SKP(NO,NO,NO)},	/*		 12 */
	{FNI_NONE FNBdbg("STPSRV") SKP(NO,NO,NO)},	/*		 13 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 14 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 15 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 16 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 17 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 18 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 19 */
	{FNI_NONE FNBdbg("CREDAT") SKP(NO,NO,NO)},	/*		 20 */
	{FNI_NONE FNBdbg("CREIDX") SKP(NO,NO,NO)},	/*		 21 */
	{FNI_NONE FNBdbg("CREMEM") SKP(NO,NO,NO)},	/*		 22 */
	{FNI_NONE FNBdbg("OPNFIL") SKP(NO,NO,NO)},	/*		 23 */
	{FNI_NONE FNBdbg("RENFIL") SKP(NO,NO,NO)},	/*		 24 */
	{FNI_NONE FNBdbg("CLSFIL") SKP(NO,NO,NO)},	/*		 25 */
	{FNI_NONE FNBdbg("DELFIL") SKP(NO,NO,NO)},	/*		 26 */
	{FNI_NONE FNBdbg("CLSNAM") SKP(NO,NO,NO)},	/*		 27 */
	{FNI_NONE FNBdbg("AVLFILNUM") SKP(NO,NO,NO)},	/*		 28 */
	{FNI_NONE FNBdbg("TSTFILNUM") SKP(NO,NO,NO)},	/*		 29 */
	{FNI_NONE FNBdbg("INTISAM") SKP(NO,NO,YES)},	/*		 30 */
	{FNI_NONE FNBdbg("CREISAM") SKP(NO,NO,YES)},	/*		 31 */
	{FNI_NONE FNBdbg("OPNISAM") SKP(NO,NO,YES)},	/*		 32 */
	{FNI_NONE FNBdbg("CLISAM") SKP(NO,NO,YES)},	/*		 33 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 34 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 35 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 36 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 37 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 38 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 39 */
	{FNI_NONE FNBdbg("OPNIFIL") SKP(NO,NO,YES)},	/*		 40 */
	{FNI_NONE FNBdbg("PUTIFIL") SKP(NO,NO,YES)},	/*		 41 */
	{FNI_NONE FNBdbg("RBLIFIL") SKP(NO,NO,YES)},	/*		 42 */
	{FNI_NONE FNBdbg("CMPIFIL") SKP(NO,NO,YES)},	/*		 43 */
	{FNI_NONE FNBdbg("RENIFIL") SKP(NO,NO,YES)},	/*		 44 */
	{FNI_NONE FNBdbg("EXPIFIL") SKP(NO,NO,YES)},	/*		 45 */
	{FNI_NONE FNBdbg("CREIFIL") SKP(NO,NO,YES)},	/*		 46 */
	{FNI_NONE FNBdbg("PRMIIDX") SKP(NO,NO,YES)},	/*		 47 */
	{FNI_NONE FNBdbg("RBLIIDX") SKP(NO,NO,YES)},	/*		 48 */
	{FNI_NONE FNBdbg("TMPIIDX") SKP(NO,NO,YES)},	/*		 49 */
	{FNI_NONE FNBdbg("DROPIDX") SKP(NO,NO,YES)},	/*		 50 */
	{FNI_NONE FNBdbg("OPNRFIL") SKP(NO,NO,YES)},	/*		 51 */
	{FNI_NONE FNBdbg("CLRFIL") SKP(NO,NO,YES)},	/*		 52 */
	{FNI_NONE FNBdbg("DELRFIL") SKP(NO,NO,YES)},	/*		 53 */
	{FNI_NONE FNBdbg("CLIFIL") SKP(NO,NO,YES)},	/*		 54 */
	{FNI_NONE FNBdbg("DELIFIL") SKP(NO,NO,YES)},	/*		 55 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 56 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 57 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 58 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 59 */
	{FNI_NONE FNBdbg("SETSEG") SKP(NO,NO,NO)},	/*		 60 */
	{FNI_NONE FNBdbg("PTADMIN") SKP(NO,NO,NO)},	/*		 61 */
	{FNI_NONE FNBdbg("CTTESTFUNC") SKP(NO,NO,NO)},	/*		 62 */
	{FNI_NONE FNBdbg("NOTIFY") SKP(NO,NO,NO)},	/*		 63 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 64 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 65 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 66 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 67 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 68 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 69 */
	{FNI_NONE FNBdbg("SERIALNUM") SKP(NO,NO,NO)},	/*		 70 */
	{FNI_NONE FNBdbg("DATENT") SKP(NO,NO,NO)},	/*		 71 */
	{FNI_NONE FNBdbg("IDXENT") SKP(NO,NO,NO)},	/*		 72 */
	{FNI_NONE FNBdbg("ctDISTINCTest") SKP(NO,NO,NO)},/*		 73 */
	{FNI_NONE FNBdbg("ctDISTINCTset") SKP(NO,NO,NO)},/*		 74 */
	{FNI_NONE FNBdbg("ctLOKDYN") SKP(NO,NO,NO)},	/*		 75 */
	{FNI_NONE FNBdbg("ctImpersonateTask") SKP(NO,NO,NO)},	/*	 76 */
	{FNI_NONE FNBdbg("ctTransferFile") SKP(NO,NO,NO)},	/*	 77 */
	{FNI_NONE FNBdbg("ctSEQUENCE") SKP(NO,NO,NO)},	/*		 78 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		 79 */
	{FNI_NONE FNBdbg("SECURITY") SKP(NO,NO,NO)},	/*		 80 */
	{FNI_NONE FNBdbg("GETFIL") SKP(NO,NO,NO)},	/*		 81 */
	{FNI_NONE FNBdbg("PUTCRES") SKP(NO,NO,YES)},	/*		 82 */
	{FNI_NONE FNBdbg("GETCRES") SKP(NO,NO,YES)},	/*		 83 */
	{FNI_NONE FNBdbg("GETCIDX") SKP(NO,NO,YES)},	/*		 84 */
	{FNI_NONE FNBdbg("UPDCIDX") SKP(NO,NO,YES)},	/*		 85 */
	{FNI_NONE FNBdbg("PUTDODA") SKP(NO,NO,NO)},	/*		 86 */
	{FNI_NONE FNBdbg("SETFLTR") SKP(NO,NO,NO)},	/*		 87 */
	{FNI_NONE FNBdbg("GETIFIL") SKP(NO,NO,YES)},	/*		 88 */
	{FNI_NONE FNBdbg("GETDODA") SKP(NO,NO,NO)},	/*		 89 */
	{FNI_NONE FNBdbg("GETRES") SKP(NO,NO,NO)},	/*		 90 */
	{FNI_NONE FNBdbg("ADDRES") SKP(NO,NO,NO)},	/*		 91 */
	{FNI_NONE FNBdbg("UPDRES") SKP(NO,NO,NO)},	/*		 92 */
	{FNI_NONE FNBdbg("DELRES") SKP(NO,NO,NO)},	/*		 93 */
	{FNI_NONE FNBdbg("ENARES") SKP(NO,NO,NO)},	/*		 94 */
	{FNI_NONE FNBdbg("SETALTSEQ") SKP(NO,NO,NO)},	/*		 95 */
	{FNI_NONE FNBdbg("SETVARBYTS") SKP(NO,NO,NO)},	/*		 96 */
	{FNI_NONE FNBdbg("GETALTSEQ") SKP(NO,NO,NO)},	/*		 97 */
	{FNI_NONE FNBdbg("SETDEFBLK") SKP(NO,NO,NO)},	/*		 98 */
	{FNI_NONE FNBdbg("PUTKSEGDEF") SKP(NO,NO,NO)},	/*		 99 */
	{FNI_NONE FNBdbg("GETKSEGDEF") SKP(NO,NO,NO)},	/*		100 */
	{FNI_NONE FNBdbg("GETXCREBLK") SKP(NO,NO,NO)},	/*		101 */
	{FNI_NONE FNBdbg("XFMKSEGDEF") SKP(NO,NO,NO)},	/*		102 */
	{FNI_NONE FNBdbg("UPDTICU") SKP(NO,NO,NO)},	/*		103 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		104 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		105 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		106 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		107 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		108 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		109 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		110 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		111 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		112 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		113 */
	{FNI_NONE FNBdbg("xtdatrIDfield") SKP(NO,NO,NO)},/*		114 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		115 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		116 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		117 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		118 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		119 */
	{FNI_NONE FNBdbg("OPNICON") SKP(NO,NO,YES)},	/*		120 */
	{FNI_NONE FNBdbg("CHGICON") SKP(NO,NO,YES)},	/*		121 */
	{FNI_NONE FNBdbg("CLSICON") SKP(NO,NO,YES)},	/*		122 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		123 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		124 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		125 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		126 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		127 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		128 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		129 */
	{FNI_NONE FNBdbg("PUTFIL") SKP(NO,NO,NO)},	/*		130 */
	{FNI_NONE FNBdbg("PUTHDR") SKP(NO,NO,NO)},	/*		131 */
	{FNI_NONE FNBdbg("GETMNAME") SKP(NO,NO,NO)},	/*		132 */
	{FNI_NONE FNBdbg("GETNAM") SKP(NO,NO,NO)},	/*		133 */
	{FNI_NONE FNBdbg("SETOPS") SKP(NO,NO,NO)},	/*		134 */
	{FNI_NONE FNBdbg("SetXtdFileOpenMode") SKP(NO,NO,NO)},	/*	135 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		136 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		137 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		138 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		139 */
	{FNI_NONE FNBdbg("reset_cur") SKP(NO,NO,YES)},	/*		140 */
	{FNI_NONE FNBdbg("reset_cur2") SKP(NO,NO,YES)},	/*		141 */
	{FNI_NONE FNBdbg("GETCURP") SKP(NO,NO,YES)},	/*		142 */
	{FNI_NONE FNBdbg("GETCURK") SKP(NO,NO,YES)},	/*		143 */
	{FNI_NONE FNBdbg("GETCURKL") SKP(NO,NO,YES)},	/*		144 */
	{FNI_NONE FNBdbg("UPDCURI") SKP(NO,NO,YES)},	/*		145 */
	{FNI_NONE FNBdbg("SETCURI") SKP(NO,NO,YES)},	/*		146 */
	{FNI_NONE FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		147 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		148 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		149 */
	{FNI_NONE FNBdbg("NEWREC") SKP(NO,NO,NO)},	/*		150 */
	{FNI_NONE FNBdbg("RETREC") SKP(NO,NO,NO)},	/*		151 */
	{FNI_NONE FNBdbg("REDIREC") SKP(NO,NO,YES)},	/*		152 */
	{FNI_NONE FNBdbg("REDREC") SKP(NO,NO,NO)},	/*		153 */
	{FNI_NONE FNBdbg("WRTREC") SKP(NO,NO,NO)},	/*		154 */
	{FNI_NONE FNBdbg("LOKREC") SKP(NO,NO,NO)},	/*		155 */
	{FNI_NONE FNBdbg("ADDKEY") SKP(NO,NO,NO)},	/*		156 */
	{FNI_NONE FNBdbg("DELCHK") SKP(NO,NO,NO)},	/*		157 */
	{FNI_NONE FNBdbg("DELBLD") SKP(NO,NO,NO)},	/*		158 */
	{FNI_NONE FNBdbg("ESTKEY") SKP(NO,NO,NO)},	/*		159 */
	{FNI_NONE FNBdbg("RNGENT") SKP(NO,NO,NO)},	/*		160 */
	{FNI_NONE FNBdbg("ORDKEY") SKP(NO,NO,NO)},	/*		161 */
	{FNI_NONE FNBdbg("FRCKEY") SKP(NO,NO,NO)},	/*		162 */
	{FNI_NONE FNBdbg("GTVLEN") SKP(NO,NO,NO)},	/*		163 */
	{FNI_NONE FNBdbg("NEWVREC") SKP(NO,NO,NO)},	/*		164 */
	{FNI_NONE FNBdbg("TSTVREC") SKP(NO,NO,NO)},	/*		165 */
	{FNI_NONE FNBdbg("RETVREC") SKP(NO,NO,NO)},	/*		166 */
	{FNI_NONE FNBdbg("WRTVREC") SKP(NO,NO,NO)},	/*		167 */
	{FNI_NONE FNBdbg("RDVREC") SKP(NO,NO,NO)},	/*		168 */
	{FNI_NONE FNBdbg("ctLOKTIMOUT") SKP(NO,NO,NO)},	/*		169 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		170 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		171 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		172 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		173 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		174 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		175 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		176 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		177 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		178 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		179 */
	{FNI_NONE FNBdbg("LKISAM") SKP(NO,NO,YES)},	/*		180 */
	{FNI_NONE FNBdbg("ADDREC") SKP(NO,NO,YES)},	/*		181 */
	{FNI_NONE FNBdbg("RWTREC") SKP(NO,NO,YES)},	/*		182 */
	{FNI_NONE FNBdbg("DELREC") SKP(NO,NO,YES)},	/*		183 */
	{FNI_NONE FNBdbg("TESTHUGE") SKP(NO,NO,NO)},	/*		184 */
	{FNI_NONE FNBdbg("EQLREC") SKP(NO,NO,YES)},	/*		185 */
	{FNI_NONE FNBdbg("GTEREC") SKP(NO,NO,YES)},	/*		186 */
	{FNI_NONE FNBdbg("GTREC") SKP(NO,NO,YES)},	/*		187 */
	{FNI_NONE FNBdbg("LTEREC") SKP(NO,NO,YES)},	/*		188 */
	{FNI_NONE FNBdbg("LTREC") SKP(NO,NO,YES)},	/*		189 */
	{FNI_NONE FNBdbg("NXTREC") SKP(NO,NO,YES)},	/*		190 */
	{FNI_NONE FNBdbg("PRVREC") SKP(NO,NO,YES)},	/*		191 */
	{FNI_NONE FNBdbg("FRSREC") SKP(NO,NO,YES)},	/*		192 */
	{FNI_NONE FNBdbg("LSTREC") SKP(NO,NO,YES)},	/*		193 */
	{FNI_NONE FNBdbg("RRDREC") SKP(NO,NO,YES)},	/*		194 */
	{FNI_NONE FNBdbg("GETVLEN") SKP(NO,NO,YES)},	/*		195 */
	{FNI_NONE FNBdbg("ADDVREC") SKP(NO,NO,YES)},	/*		196 */
	{FNI_NONE FNBdbg("DELVREC") SKP(NO,NO,YES)},	/*		197 */
	{FNI_NONE FNBdbg("RWTVREC") SKP(NO,NO,YES)},	/*		198 */
	{FNI_NONE FNBdbg("REDVREC") SKP(NO,NO,YES)},	/*		199 */
	{FNI_NONE FNBdbg("EQLVREC") SKP(NO,NO,YES)},	/*		200 */
	{FNI_NONE FNBdbg("GTEVREC") SKP(NO,NO,YES)},	/*		201 */
	{FNI_NONE FNBdbg("GTVREC") SKP(NO,NO,YES)},	/*		202 */
	{FNI_NONE FNBdbg("LTEVREC") SKP(NO,NO,YES)},	/*		203 */
	{FNI_NONE FNBdbg("LTVREC") SKP(NO,NO,YES)},	/*		204 */
	{FNI_NONE FNBdbg("NXTVREC") SKP(NO,NO,YES)},	/*		205 */
	{FNI_NONE FNBdbg("PRVVREC") SKP(NO,NO,YES)},	/*		206 */
	{FNI_NONE FNBdbg("FRSVREC") SKP(NO,NO,YES)},	/*		207 */
	{FNI_NONE FNBdbg("LSTVREC") SKP(NO,NO,YES)},	/*		208 */
	{FNI_NONE FNBdbg("REDIVREC") SKP(NO,NO,YES)},	/*		209 */
	{FNI_NONE FNBdbg("BLKIREC") SKP(NO,NO,YES)},	/*		210 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		211 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		212 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		213 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		214 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		215 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		216 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		217 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		218 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		219 */
	{FNI_NONE FNBdbg("LOADKEY") SKP(NO,NO,NO)},	/*		220 */
	{FNI_NONE FNBdbg("EQLKEY") SKP(NO,NO,NO)},	/*		221 */
	{FNI_NONE FNBdbg("GTEKEY") SKP(NO,NO,NO)},	/*		222 */
	{FNI_NONE FNBdbg("FRSKEY") SKP(NO,NO,NO)},	/*		223 */
	{FNI_NONE FNBdbg("LSTKEY") SKP(NO,NO,NO)},	/*		224 */
	{FNI_NONE FNBdbg("NXTKEY") SKP(NO,NO,NO)},	/*		225 */
	{FNI_NONE FNBdbg("PRVKEY") SKP(NO,NO,NO)},	/*		226 */
	{FNI_NONE FNBdbg("GTKEY") SKP(NO,NO,NO)},	/*		227 */
	{FNI_NONE FNBdbg("LTKEY") SKP(NO,NO,NO)},	/*		228 */
	{FNI_NONE FNBdbg("LTEKEY") SKP(NO,NO,NO)},	/*		229 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		230 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		231 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		232 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		233 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		234 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		235 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		236 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		237 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		238 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		239 */
	{FNI_NONE FNBdbg("ALCSET") SKP(NO,NO,YES)},	/*		240 */
	{FNI_NONE FNBdbg("FRESET") SKP(NO,NO,YES)},	/*		241 */
	{FNI_NONE FNBdbg("FRESETN") SKP(NO,NO,YES)},	/*		242 */
	{FNI_NONE FNBdbg("CHGSET") SKP(NO,NO,YES)},	/*		243 */
	{FNI_NONE FNBdbg("FRSSET") SKP(NO,NO,YES)},	/*		244 */
	{FNI_NONE FNBdbg("MIDSET") SKP(NO,NO,YES)},	/*		245 */
	{FNI_NONE FNBdbg("LSTSET") SKP(NO,NO,YES)},	/*		246 */
	{FNI_NONE FNBdbg("NXTSET") SKP(NO,NO,YES)},	/*		247 */
	{FNI_NONE FNBdbg("PRVSET") SKP(NO,NO,YES)},	/*		248 */
	{FNI_NONE FNBdbg("FRSVSET") SKP(NO,NO,YES)},	/*		249 */
	{FNI_NONE FNBdbg("MIDVSET") SKP(NO,NO,YES)},	/*		250 */
	{FNI_NONE FNBdbg("LSTVSET") SKP(NO,NO,YES)},	/*		251 */
	{FNI_NONE FNBdbg("NXTVSET") SKP(NO,NO,YES)},	/*		252 */
	{FNI_NONE FNBdbg("PRVVSET") SKP(NO,NO,YES)},	/*		253 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		254 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		255 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		256 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		257 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		258 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		259 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		260 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		261 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		262 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		263 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		264 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		265 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		266 */
	{FNI_NONE FNBdbg("ctDISTINCTestXtd") SKP(NO,NO,NO)},	/*	267 */
	{FNI_NONE FNBdbg("ctDISTINCTsetXtd") SKP(NO,NO,NO)},	/*	268 */
	{FNI_NONE FNBdbg("ESTRNG") SKP(NO,NO,YES)},	/*		269 */
	{FNI_NONE FNBdbg("ALCRNG") SKP(NO,NO,YES)},	/*		270 */
	{FNI_NONE FNBdbg("FRERNG") SKP(NO,NO,YES)},	/*		271 */
	{FNI_NONE FNBdbg("FRSRNG") SKP(NO,NO,YES)},	/*		272 */
	{FNI_NONE FNBdbg("LSTRNG") SKP(NO,NO,YES)},	/*		273 */
	{FNI_NONE FNBdbg("FRSVRNG") SKP(NO,NO,YES)},	/*		274 */
	{FNI_NONE FNBdbg("LSTVRNG") SKP(NO,NO,YES)},	/*		275 */
	{FNI_NONE FNBdbg("NXTRNG") SKP(NO,NO,YES)},	/*		276 */
	{FNI_NONE FNBdbg("PRVRNG") SKP(NO,NO,YES)},	/*		277 */
	{FNI_NONE FNBdbg("NXTVRNG") SKP(NO,NO,YES)},	/*		278 */
	{FNI_NONE FNBdbg("PRVVRNG") SKP(NO,NO,YES)},	/*		279 */
	{FNI_NONE FNBdbg("ALCBAT") SKP(NO,NO,YES)},	/*		280 */
	{FNI_NONE FNBdbg("FREBAT") SKP(NO,NO,YES)},	/*		281 */
	{FNI_NONE FNBdbg("FREBATN") SKP(NO,NO,YES)},	/*		282 */
	{FNI_NONE FNBdbg("CHGBAT") SKP(NO,NO,YES)},	/*		283 */
	{FNI_NONE FNBdbg("FREHST") SKP(NO,NO,NO)},	/*		284 */
	{FNI_NONE FNBdbg("FREHSTN") SKP(NO,NO,NO)},	/*		285 */
	{FNI_NONE FNBdbg("CHGHST") SKP(NO,NO,NO)},	/*		286 */
	{FNI_NONE FNBdbg("BATSET") SKP(NO,NO,YES)},	/*		287 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		288 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		289 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		290 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		291 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		292 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		293 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		294 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		295 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		296 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		297 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		298 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		299 */
	{FNI_NONE FNBdbg("PERFORM") SKP(NO,NO,NO)},	/*		300 */
	{FNI_NONE FNBdbg("USERLIST") SKP(NO,NO,NO)},	/*		301 */
	{FNI_NONE FNBdbg("USERINFO") SKP(NO,NO,NO)},	/*		302 */
	{FNI_NONE FNBdbg("CTKLUSR") SKP(NO,NO,NO)},	/*		303 */
	{FNI_NONE FNBdbg("SETNODE") SKP(NO,NO,NO)},	/*		304 */
	{FNI_NONE FNBdbg("LOKDMP") SKP(NO,NO,NO)},	/*		305 */
	{FNI_NONE FNBdbg("CTUSER") SKP(NO,NO,NO)},	/*		306 */
	{FNI_NONE FNBdbg("CTUSERX") SKP(NO,NO,NO)},	/*		307 */
	{FNI_NONE FNBdbg("CTSQLCTL") SKP(NO,NO,NO)},	/*		308 */
	{FNI_NONE FNBdbg("CTSRVCTL") SKP(NO,NO,NO)},	/*		309 */
	{FNI_NONE FNBdbg("ctLOKLST") SKP(NO,NO,NO)},	/*		310 */
	{FNI_NONE FNBdbg("ADDUSR") SKP(NO,NO,NO)},	/*		311 */
	{FNI_UNUSED FNBdbg("CHGUSR") SKP(NO,NO,NO)},	/*		312 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		313 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		314 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		315 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		316 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		317 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		318 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		319 */
	{FNI_NONE FNBdbg("CTDIDX") SKP(NO,NO,NO)},	/*		320 */
	{FNI_NONE FNBdbg("CTFLUSH") SKP(NO,NO,NO)},	/*		321 */
	{FNI_NONE FNBdbg("SYSMON") SKP(NO,NO,NO)},	/*		322 */
	{FNI_NONE FNBdbg("SYSLOG") SKP(NO,NO,NO)},	/*		323 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		324 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		325 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		326 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		327 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		328 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		329 */
	{FNI_NONE FNBdbg("TRANBEG") SKP(NO,NO,NO)},	/*		330 */
	{FNI_NONE FNBdbg("TRANEND") SKP(NO,NO,NO)},	/*		331 */
	{FNI_NONE FNBdbg("TRANABTX") SKP(NO,NO,NO)},	/*		332 */
	{FNI_NONE FNBdbg("TRANRST") SKP(NO,NO,NO)},	/*		333 */
	{FNI_NONE FNBdbg("TRANABT") SKP(NO,NO,NO)},	/*		334 */
	{FNI_NONE FNBdbg("TRANCLR") SKP(NO,NO,NO)},	/*		335 */
	{FNI_NONE FNBdbg("SAVPCLR") SKP(NO,NO,NO)},	/*		336 */
	{FNI_NONE FNBdbg("TRANSAV") SKP(NO,NO,NO)},	/*		337 */
	{FNI_NONE FNBdbg("SPCLSAV") SKP(NO,NO,NO)},	/*		338 */
	{FNI_NONE FNBdbg("TRANISO") SKP(NO,NO,NO)},	/*		339 */
	{FNI_NONE FNBdbg("TRANBAK") SKP(NO,NO,NO)},	/*		340 */
	{FNI_NONE FNBdbg("CTCHKPNT") SKP(NO,NO,NO)},	/*		341 */
	{FNI_NONE FNBdbg("TRANUSR") SKP(NO,NO,NO)},	/*		342 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		343 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		344 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		345 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		346 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		347 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		348 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		349 */
	{FNI_NONE FNBdbg("SETFNDVAL") SKP(NO,NO,NO)},	/*		350 */
	{FNI_NONE FNBdbg("SQR") SKP(NO,NO,NO)},		/*		351 */
	{FNI_NONE FNBdbg("CTSBLD") SKP(NO,NO,NO)},	/*		352 */
	{FNI_NONE FNBdbg("CLNIDX") SKP(NO,NO,NO)},	/*		353 */
	{FNI_NONE FNBdbg("SQL") SKP(NO,NO,NO)},		/*		354 */
	{FNI_NONE FNBdbg("TMPNAME") SKP(NO,NO,NO)},	/*		355 */
	{FNI_NONE FNBdbg("IOPERFORMANCE") SKP(NO,NO,NO)},	/*	356 */
	{FNI_NONE FNBdbg("IOPERFORMANCEX") SKP(NO,NO,NO)},	/*	357 */
	{FNI_NONE FNBdbg("SYSCFG") SKP(NO,NO,NO)},	/*		358 */
	{FNI_NONE FNBdbg("CTFLUSHX") SKP(NO,NO,NO)},	/*		359 */
	{FNI_NONE FNBdbg("CTASYNC") SKP(NO,NO,NO)},	/*		360 */
	{FNI_NONE FNBdbg("SNAPSHOT") SKP(NO,NO,NO)},	/*		361 */
	{FNI_NONE FNBdbg("SYSPUT") SKP(NO,NO,NO)},	/*		362 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		363 */
	{FNI_NONE FNBdbg("FILMTX") SKP(NO,NO,NO)},	/*		364 */
	{FNI_NONE FNBdbg("FILBLK") SKP(NO,NO,NO)},	/*		365 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		366 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		367 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		368 */
	{FNI_NONE FNBdbg("QUIET") SKP(NO,NO,NO)},	/*		369 */
	{FNI_NONE FNBdbg("CTHIST") SKP(NO,NO,NO)},	/*		370 */
	{FNI_NONE FNBdbg("SETENCRYPT") SKP(NO,NO,NO)},	/*		371 */
	{FNI_NONE FNBdbg("SESSVAL") SKP(NO,NO,NO)},	/*		372 */
	{FNI_NONE FNBdbg("SESSINC") SKP(NO,NO,NO)},	/*		373 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		374 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		375 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		376 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		377 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		378 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		379 */
	{FNI_NONE FNBdbg("SysQueueOpen") SKP(YES,YES,NO)},	/*	380 */
	{FNI_NONE FNBdbg("SysQueueClose") SKP(YES,YES,NO)},/*		381 */
	{FNI_NONE FNBdbg("SysQueueWrite") SKP(YES,YES,NO)},/*		382 */
	{FNI_NONE FNBdbg("SysQueueLIFOWrite") SKP(YES,YES,NO)},	/*	383 */
	{FNI_NONE FNBdbg("SysQueueRead") SKP(YES,YES,NO)},	/*	384 */
	{FNI_NONE FNBdbg("SysQueueMlen") SKP(YES,YES,NO)},	/*	385 */
	{FNI_NONE FNBdbg("SysQueueCount") SKP(YES,YES,NO)},/*		386 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		387 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		388 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		389 */
	{FNI_REINIT FNBdbg("ThrdAttach") SKP(YES,YES,NO)},	/*	390 */
	{FNI_NONE FNBdbg("ThrdBlockCls") SKP(YES,YES,NO)},	/*	391 */
	{FNI_NONE FNBdbg("ThrdBlockGet") SKP(YES,YES,NO)},	/*	392 */
	{FNI_NONE FNBdbg("ThrdBlockInit") SKP(YES,YES,NO)},/*		393 */
	{FNI_NONE FNBdbg("ThrdBlockRel") SKP(YES,YES,NO)},	/*	394 */
	{FNI_NONE FNBdbg("ThrdBlockWait") SKP(YES,YES,NO)},/*		395 */
	{FNI_NONE FNBdbg("ThrdCreate") SKP(NO,NO,NO)},	/*		396 */
	{FNI_NONE FNBdbg("ThrdData") SKP(YES,YES,NO)},	/*		397 */
	{FNI_NONE FNBdbg("ThrdDataSet") SKP(YES,YES,NO)},	/*	398 */
	{FNI_NONE FNBdbg("ThrdDetach") SKP(YES,YES,NO)},	/*	399 */
	{FNI_TRMTRD FNBdbg("ThrdExit") SKP(YES,YES,NO)},/*		400 */
	{FNI_NONE FNBdbg("ThrdHandle") SKP(YES,YES,NO)},/*		401 */
	{FNI_NONE FNBdbg("ThrdInit") SKP(NO,NO,NO)},	/*		402 */
	{FNI_NONE FNBdbg("ThrdLIFOWrite") SKP(YES,YES,NO)},/*		403 */
	{FNI_NONE FNBdbg("ThrdMutexCls") SKP(YES,YES,NO)},	/*	404 */
	{FNI_NONE FNBdbg("ThrdMutexGet") SKP(YES,YES,NO)},	/*	405 */
	{FNI_NONE FNBdbg("ThrdMutexInit") SKP(YES,YES,NO)},/*		406 */
	{FNI_NONE FNBdbg("ThrdMutexRel") SKP(YES,YES,NO)},/*		407 */
	{FNI_NONE FNBdbg("ThrdMutexTry") SKP(YES,YES,NO)},/*		408 */
	{FNI_NONE FNBdbg("ThrdQueueClose") SKP(YES,YES,NO)},	/*	409 */
	{FNI_NONE FNBdbg("ThrdQueueCount") SKP(YES,YES,NO)},	/*	410 */
	{FNI_NONE FNBdbg("ThrdQueueMlen") SKP(YES,YES,NO)},	/*	411 */
	{FNI_NONE FNBdbg("ThrdQueueOpen") SKP(YES,YES,NO)},	/*	412 */
	{FNI_NONE FNBdbg("ThrdQueueRead") SKP(YES,YES,NO)},	/*	413 */
	{FNI_NONE FNBdbg("ThrdQueueReadDirect") SKP(YES,YES,NO)},/*	414 */
	{FNI_NONE FNBdbg("ThrdQueueWrite") SKP(YES,YES,NO)},	/*	415 */
	{FNI_NONE FNBdbg("ThrdQueueWriteDirect") SKP(YES,YES,NO)},/*	416 */
	{FNI_NONE FNBdbg("ThrdSemapCls") SKP(YES,YES,NO)},/*		417 */
	{FNI_NONE FNBdbg("ThrdSemapGet") SKP(YES,YES,NO)},/*		418 */
	{FNI_NONE FNBdbg("ThrdSemapInit") SKP(YES,YES,NO)},	/*	419 */
	{FNI_NONE FNBdbg("ThrdSemapRel") SKP(YES,YES,NO)},/*		420 */
	{FNI_NONE FNBdbg("ThrdSemapTry") SKP(YES,YES,NO)},/*		421 */
	{FNI_NONE FNBdbg("ThrdSleep") SKP(YES,YES,NO)},	/*		422 */
	{FNI_SHTDWN FNBdbg("ThrdTerm") SKP(NO,YES,NO)},	/*		423 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		424 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		425 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		426 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		427 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		428 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		429 */
	{FNI_SWINST FNBdbg("SWTCTREE") SKP(NO,NO,NO)},	/*		430 */
	{FNI_NONE FNBdbg("GETCTREE") SKP(NO,NO,NO)},	/*		431 */
	{FNI_NONE FNBdbg("WCHCTREE") SKP(NO,NO,NO)},	/*		432 */
	{FNI_RGINST FNBdbg("REGCTREE") SKP(NO,NO,NO)},	/*		433 */
	{FNI_NONE FNBdbg("UNRCTREE") SKP(NO,NO,NO)},	/*		434 */
	{FNI_SWINST FNBdbg("NXTCTREE") SKP(NO,NO,NO)},	/*		435 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		436 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		437 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		438 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		439 */
	{FNI_NONE FNBdbg("TFRMKEY") SKP(NO,NO,YES)},	/*		440 */
	{FNI_NONE FNBdbg("frmkey") SKP(NO,NO,YES)},	/*		441 */
	{FNI_NONE FNBdbg("cttseg") SKP(NO,NO,YES)},	/*		442 */
	{FNI_NONE FNBdbg("ctuseg") SKP(NO,NO,YES)},	/*		443 */
	{FNI_NONE FNBdbg("frmkeyx") SKP(NO,NO,YES)},	/*		444 */
	{FNI_UNUSED FNBdbg("GetFileRegions") SKP(NO,NO,NO)},	     /* 445 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		446 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		447 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		448 */
	{FNI_UNUSED FNBdbg("UNUSED") SKP(NO,NO,NO)},	/*		449 */
	{FNI_NONE FNBdbg("CTGETUEC") SKP(NO,NO,NO)},	/*		450 */
	{FNI_NONE FNBdbg("CTGETIEC") SKP(NO,NO,NO)},	/*		451 */
	{FNI_NONE FNBdbg("CTGETIFL") SKP(NO,NO,NO)},	/*		452 */
	{FNI_NONE FNBdbg("CTGETSEC") SKP(NO,NO,NO)},	/*		453 */
	{FNI_NONE FNBdbg("ctSETHGH") SKP(NO,NO,NO)},	/*		454 */
	{FNI_NONE FNBdbg("ctGETHGH") SKP(NO,NO,NO)},	/*		455 */
	{ FNI_NONE FNBdbg("ctReplCheckFileFilter") SKP(NO,NO,NO) },  /* 456 */
	{ FNI_NONE FNBdbg("addAutoSysTimeFields") SKP(NO,NO,NO) },   /* 457 */
	{ FNI_NONE FNBdbg("RemoveAutoSysTimeFields") SKP(NO,NO,NO) },/* 458 */
	{ FNI_NONE FNBdbg("WhichAutoSysTimeFields") SKP(NO,NO,NO) }, /* 459 */
	{ FNI_NONE FNBdbg("UpdateAutoSysTimeField") SKP(NO,NO,NO) }, /* 460 */
};
#endif /* ctPARMBH */

/* end of ctparmb.h */
