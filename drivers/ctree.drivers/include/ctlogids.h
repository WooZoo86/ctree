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

/*
 *      Copyright (C) Dharma Systems Inc.        1988-2002. 
 *      Copyright (C) Dharma Systems (P) Ltd.    1988-2002. 
 * 
 *      This Module contains Proprietary Information of 
 *      Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 *      and should be treated as Confidential. 
 */

#ifndef _CTLOGIDS_H_
#define _CTLOGIDS_H_

/*^****************************************************************************\
 *
 *   unique log entry identifier
 *
 *   this is an enumerator containing the log entry id (uniqeu per each log entry creation call)
 *   it ies expected the this enumerato gros over time since each log entry needs to has its unique id
 *
\*****************************************************************************/
typedef enum
{
	LOGID_CONT=-1, /* continuation of multipart message. Should never be logged. */
	LOGID_TRYOPEN=0, /* log entry for old ctrcvlog call, try open*/
	CTLOG_ID_1 = 1, /* log entry for old ctrcvlog call */
	/* from HERE significant unique CTLOG_IDs */
	CTLOG_ID_2 = 2,
	LOGID_LIC_INUSE=3,
	CTLOG_LIC_FAIL=4,
	CTLOG_ID_5 = 5, /*ctcatend */
	CTLOG_ID_6 = 6,
	LOGID_WARN_RWLOCK=7,
	LOGID_INFO_RWLOCK=8,
	LOGID_INFO_PID=9,
	LOGID_INFO_ALTSRV=10,
	LOGID_DEBUG_COMP=11,
	LOGID_INFO_VERSION=12,
	LOGID_DEBUG_DIAGTHRD=13,
	LOGID_CRIT_VSSVER=14,
	CTLOG_ID_15 = 15,
	CTLOG_ID_16 = 16,
	CTLOG_ID_17 = 17, 
	LOGID_DEBUG_SIDESTEPS=18,
	LOGID_DEBUG_LEAFRETRY=19,
	LOGID_DEBUG_ADJPATH=20,
	LOGID_WARN_NCOFILE=21,
	LOGID_ERR_BADSPLIT=22,
	LOGID_ERR_NEWNODE=23,
	LOGID_DEBUG_SPLIT=24,
	LOGID_ERR_ADJPATH=25,
	LOGID_DEBUG_RETRYPATH=26,
	LOGID_ERR_BRANCHDETAIL=27,
	LOGID_DEBUG_DBGBUFCNT=28,
	LOGID_DEBUG_NEWNODE_FILE=29,
	LOGID_DEBUG_NEWNODE_ALLOC=30,
	LOGID_DIAG_NODE_REUSE=31,
	LOGID_WARN_NODE_REUSE=32,
	LOGID_WARN_KLNK_DETAIL=33,
	LOGID_WARN_KLNK=34,
	LOGID_INFO_MAXZ1=35,
	LOGID_INFO_MAXZ2=36,
	LOGID_INFO_TRNABT=37,
	LOGID_DEBUG_SRVRPOWER=38,
	LOGID_ERR_ADDWORK=39,
	LOGID_ERR_ADDWORK2=40,
	LOGID_WARN_MAXPAGE=41,
	LOGID_WARN_TRANHASH=42,
	LOGID_DEBUG_KILLQT=43,
	LOGID_ERR_MEMTRACK_LOAD=44,
	LOGID_ERR_MEMTRACK_SYM=45,
	LOGID_MXLOGS=46, /* ctMXLOGS is not enabled */
	LOGID_CTMALERT=47,	
	LOGID_DEBUG_FLUSHT=48,
	LOGID_DEBUG_FLUSHN=49,
	LOGID_INFO_IDLE=50,
	LOGID_ERR_IDLE=51,
	LOGID_IDLETERM=52,
	LOGID_INFO_BG=53,
	LOGID_ERR_BG=54,
	LOGID_INFO_TRNTIMOUT=55,
	LOGID_INFO_DDFLUSH=56,
	LOGID_ERR_DDFLUSH=57,
	LOGID_INFO_DDSTOP=58,
	LOGID_INFO_REPLFLUSH=59,
	LOGID_ERR_REPLFLUSH=60,
	LOGID_INFO_CPULIC=61,
	LOGID_INFO_BROADCAST=62,
	LOGID_ALERT_RQTM=63,
	LOGID_INFO_RQTM=64,
	LOGID_INFO_KEEPOC=65,
	LOGID_WARN_KEEPOC_READ=66,
	LOGID_WARN_KEEPOC_CLS=67,
	LOGID_INFO_DIST_CNT=68,
	LOGID_ERR_DIST_CNT=69,
	LOGID_ERR_DDMP_RESTORE=70,
	LOGID_INFO_DISKFULL_COMMENT=71,
	LOGID_INFO_DISKFULL=72,
	LOGID_ERR_DISKFULL_SPC=73,
	LOGID_ERR_DISKFULL_ACT=74,
	LOGID_FATAL_DISKFULL=75,
	LOGID_INFO_DISKFULL_EXIT=76,
	LOGID_ERR_SETTINGS=77,	
	LOGID_ERR_SETTINGS2=78,	
	LOGID_ERR_SETTINGS3=79,
	LOGID_LIC_CPU=80,	
	LOGID_ERR_ENCSTORE=81,
	LOGID_INFO_UNIFRMAT=82,
	LOGID_INFO_NOTRAN=83,
	LOGID_INFO_LEON=84,
	LOGID_LIC_FILES=85,
	LOGID_DEBUG_FOLLETT=86,
	LOGID_TCOL_ERR=87,
	LOGID_WARN_TOOLTRAY=88,
	LOGID_INFO_CFGNAME=89,
	LOGID_INFO_SETNAME=90,
	LOGID_INFO_BITMAP=91,
	LOGID_INFO_OSVERSION=92,
	LOGID_INFO_LIC=93,
	LOGID_INFO_OPTIONS=94,
	LOGID_FATAL_NOLIC=95,
	LOGID_FATAL_NOLIC2=96,
	LOGID_ERR_CPULIMIT=97,
	LOGID_LIC_FAIL=98,
	LOGID_WARN_CPULIMIT=99,
	LOGID_INFO_DFLT_CONFIG=100,
	LOGID_INFO_CONFIG=101,
	LOGID_CRIT_WOW64=102,
	LOGID_CRIT_WOW642=103,
	LOGID_CRIT_NOWOW64=104,
	LOGID_CRIT_VSSLOAD=105,
	LOGID_CRIT_VSSLOAD2=106,
	LOGID_CRIT_COMINIT=107,
	LOGID_CRIT_COMINIT2=108,
	LOGID_CRIT_VSSDIAG=109,
	LOGID_CRIT_VSSNAME=110,
	LOGID_CRIT_VSSTIMEOUT=111,
	LOGID_CRIT_VSSINIT=112,
	LOGID_INFO_VSSINIT=113,
	LOGID_ERR_REDIR1=114,
	LOGID_ERR_REDIR2=115,
	LOGID_ERR_REDIR3=116,
	LOGID_ERR_REDIR4=117,
	LOGID_ERR_REDIR5=118,
	LOGID_INFO_REDIR6=119,
	LOGID_ERR_REDIR7=120,
	LOGID_INFO_REDIR8=121,
	LOGID_WARN_LIC1=122,
	LOGID_WARN_LIC2=123,
	LOGID_WARN_LIC3=124,
	LOGID_INFO_DATPNDG=125,
	LOGID_INFO_USEDATMT=126,
	LOGID_INFO_NODATMT=127,
	LOGID_INFO_IDXPNDG=128,
	LOGID_INFO_IDXHASH=129,
	LOGID_INFO_DATHASH=130,
	LOGID_INFO_IDXREAD=131,
	LOGID_ERR_STREAM=132,
	LOGID_ERR_MXLOG=133,
	LOGID_INFO_LOGSUP=134,
	LOGID_INFO_DIO=135,
	LOGID_INFO_NODIO=136,
	LOGID_INFO_8KLOG=137,
	LOGID_INFO_DIADFS=138,
	LOGID_FATAL_KEYX=139,
	LOGID_FATAL_LDAP=140,
	LOGID_INFO_LDAP=141,
	LOGID_INFO_NOLDAP=142,
	LOGID_INFO_MINIDXBUF=143,
	LOGID_INFO_MINIDXBUF2=144,
	LOGID_INFO_IDXLRU=145,
	LOGID_INFO_DATLRU=146,
	LOGID_INFO_CACHESTAT=147,
	LOGID_FATAL_SYSMONI=148,
	LOGID_FATAL_MPWRECOV=149,
	LOGID_FATAL_NAMIDX=150,
	LOGID_LIC_TIME=151,
	LOGID_LIC_SQLTIME=152,
	LOGID_FATAL_DNODEMEM=153,
	LOGID_WARN_ADDWRK=154,
	LOGID_WARN_ADDWRK2=155,
	LOGID_WARN_ADDWRK3=156,
	LOGID_WARN_ADDWRK4=157,
	LOGID_WARN_SYSLOGEVT=158,
	LOGID_ERR_QCRE=159,
	LOGID_DBG_QWRT=160,
	LOGID_DBG_QRED=161,
	LOGID_ERR_QCHK=162,
	LOGID_DIAG_CHKPST=163,
	LOGID_WARN_LAUNCH=164,
	LOGID_DEBUG_EXCEP=165,
	LOGID_ERR_FBCLR=166,
	LOGID_ERR_FBCLR2=167,
	LOGID_ERR_FBCLR3=168,
	LOGID_ERR_FBCLR4=169,
	LOGID_ERR_FBCLR5=170,
	LOGID_ERR_FBCLR6=171,
	LOGID_ERR_FBCLR7=172,
	LOGID_ERR_FBCLR8=173,
	LOGID_ERR_FBCLR9=174,
	LOGID_INFO_FILBLK=175,
	LOGID_ERR_FB=176,
	LOGID_ERR_FB2=177,
	LOGID_INFO_FB2=178,
	LOGID_ERR_FB3=179,
	LOGID_ERR_FB4=180,
	LOGID_INFO_FB3=181,
	LOGID_INFO_FB4=182,
	LOGID_ERR_FB5=183,
	LOGID_ERR_FB6=184,
	LOGID_WARN_LIC4=185,
	LOGID_ERR_FB7=186,
	LOGID_DEBUG_HEAP=187,
	LOGID_DEBUG_HEAP2=188,
	LOGID_DEBUG_HEAP3=189,
        LOGID_NSUP_HEAP=190,
	LOGID_DEBUG_FALGERR=191,
	LOGID_DEBUG_FALGERR2=192,
	LOGID_DEBUG_FALGERR3=193,
	LOGID_DEBUG_FALGERR4=194,
	LOGID_DEBUG_DMPOFF=195,
	LOGID_ERR_SET_TIMER_RESOLUTION=196, /* error setting timer resolution */
	LOGID_ERR_INVALID_FILENAME=197, /* the specified filename is invalid */
	LOGID_ERR_FB10=198,
	LOGID_ERR_FB11=199,
	LOGID_ERR_FB12=199,
	LOGID_INFO_QTKILL=200,
	LOGID_INFO_QTTRY=201,
	LOGID_INFO_QTABT=202,
	LOGID_INFO_QTBEG=203,
	LOGID_ERR_QTABT=204,
	LOGID_ERR_QTCLS=205,
	LOGID_ERR_QTCLS2=206,
	LOGID_ERR_QTCLS3=207,
	LOGID_ERR_QTCLS4=208,
	LOGID_ERR_QTOPN=209,
	LOGID_ERR_QTOPN2=210,
	LOGID_ERR_RPCRE=211,
	LOGID_ERR_RPCRE2=212,
	LOGID_ERR_RPCRE3=213,
	LOGID_ERR_QTCHK=214,
	LOGID_ERR_QTRP=215,
	LOGID_INFO_QTRP=216,
	LOGID_ERR_QTLOG=217,
	LOGID_ERR_QTLOG2=218,
	LOGID_ERR_QTLOG3=219,
	LOGID_ERR_QTEND=220,
	LOGID_INFO_QTREPL=221,
	LOGID_INFO_QTREPL2=222,
	LOGID_INFO_QTREPL3=223,
	LOGID_INFO_QTREPL4=224,
	LOGID_INFO_QTREPL5=225,
	LOGID_INFO_QTREPL6=226,
	LOGID_INFO_QTREPL7=227,
	LOGID_INFO_QTREPL8=228,
	LOGID_INFO_QTOFF=229,
	LOGID_INFO_QT=230,
	LOGID_ERR_FB8=231,
	LOGID_ERR_FB9=232,
	LOGID_ERR_LENC=233,
	LOGID_ERR_FENC=234,
	LOGID_ERR_FENC2=235,
	LOGID_ERR_FENC3=236,
	LOGID_INFO_QTBLK=237,
	LOGID_INFO_QTUBLK=238,
	LOGID_INFO_QTUBLK2=239,
	LOGID_INFO_QTBLK2=240,
	LOGID_ERR_QTBLK=241,
	LOGID_INFO_FLUSH1=242,
	LOGID_INFO_FLUSH2=243,
	LOGID_INFO_FLUSH3=244,
	LOGID_INFO_FLUSH4=245,
	LOGID_INFO_FLUSH5=246,
	LOGID_INFO_TRKILL=247,
	LOGID_DEBUG_PRIME=248,
	LOGID_DEBUG_PRIME2=249,
	LOGID_ERR_VSSTO=250,
	LOGID_ERR_CMPUSR=251,
	LOGID_ERR_CMPDLL=252,
	LOGID_ERR_CMPVER=253,
	LOGID_ERR_CMPATR=254,
	LOGID_ERR_CMPALLC=255,
	LOGID_ERR_CMPLOAD=256,
	LOGID_ERR_CMPLOAD2=257,
	LOGID_ERR_CMPFUNC=258,
	LOGID_ERR_CMPFUNC2=259,
	LOGID_ERR_CMPRES=260,
	LOGID_ERR_CMPRES2=261,
	LOGID_ERR_CTSCFG1=262,
	LOGID_ERR_CTSCFG2=263,
	LOGID_ERR_CTSCFG3=264,
	LOGID_ERR_CTSCFG4=265,
	LOGID_INFO_CTSCFG5=266,
	LOGID_INFO_CTSCFG6=267,
	LOGID_INFO_CTSCFG7=268,
	LOGID_ERR_CTSCFG8=269,
	LOGID_ERR_CTSCFG9=270,
	LOGID_WARN_CTSCFG10=271,
	LOGID_WARN_CTSCFG11=272,
	LOGID_ERR_CTSCFG12=273,
	LOGID_WARN_CTSCFG13=274,
	LOGID_WARN_CTSCFG14=275,
	LOGID_ERR_CTSCFG15=276,
	LOGID_CTSCFG16=277,
	LOGID_CTSCFG17=278,
	LOGID_CTSCFG18=279,
	LOGID_CTSCFG19=280,
	LOGID_CTSCFG20=281,
	LOGID_CTSCFG21=282,
	LOGID_CTSCFG22=283,
	LOGID_CTSCFG23=284,
	LOGID_CTSCFG24=285,
	LOGID_CTSCFG25=286,
	LOGID_CTSCFG26=287,
	LOGID_CTSCFG27=288,
	LOGID_CTSCFG28=289,
	LOGID_CTSCFG29=290,
	LOGID_CTSCFG30=291,
	LOGID_CTSCFG31=292,
	LOGID_CTSCFG32=293,
	LOGID_CTSCFG33=294,
	LOGID_CTSCFG34=295,
	LOGID_CTSCFG35=296,
	LOGID_CTSCFG36=297,
	LOGID_CTSCFG37=298,
	LOGID_CTSCFG38=299,
	LOGID_CTSCFG39=300,
	LOGID_CTSCFG40=301,
	LOGID_CTSCFG41=302,
	LOGID_CTSCFG42=303,
	LOGID_CTSCFG43=304,
	LOGID_CTSCFG44=305,
	LOGID_CTSCFG45=306,
	LOGID_CTSCFG46=307,
	LOGID_CTSCFG47=308,
	LOGID_CTSCFG48=309,
	LOGID_CTSCFG49=310,
	LOGID_CTSCFG50=311,
	LOGID_CTSCFG51=312,
	LOGID_CTSCFG52=313,
	LOGID_CTSCFG53=314,
	LOGID_CTSCFG54=315,
	LOGID_CTSCFG55=316,
	LOGID_CTSCFG56=317,
	LOGID_CTSCFG57=318,
	LOGID_CTSCFG58=319,
	LOGID_CTSCFG59=320,
	LOGID_CTSCFG60=321,
	LOGID_322=322,
	LOGID_323=323,
	LOGID_324=324,
	LOGID_325=325,
	LOGID_326=326,
	LOGID_327=327,
	LOGID_328=328,
	LOGID_329=329,
	LOGID_330=330,
	LOGID_331=331,
	LOGID_332=332,
	LOGID_333=333,
	LOGID_334=334,
	LOGID_335=335,
	LOGID_336=336,
	LOGID_337=337,
	LOGID_338=338,
	LOGID_339=339,
	LOGID_340=340,
	LOGID_341=341,
	LOGID_342=342,
	LOGID_343=343,
	LOGID_344=344,
	LOGID_345=345,
	LOGID_346=346,
	LOGID_347=347,
	LOGID_348=348,
	LOGID_349=349,
	LOGID_350=350,
	LOGID_351=351,
	LOGID_352=352,
	LOGID_353=353,
	LOGID_354=354,
	LOGID_355=355,
	LOGID_356=356,
	LOGID_357=357,/* terr */
	LOGID_358=358,
	LOGID_359=359,
	LOGID_360=360,
	LOGID_361=361,
	LOGID_362=362,
	LOGID_363=363,
	LOGID_364=364,
	LOGID_365=365,
	LOGID_366=366,
	LOGID_367=367,
	LOGID_368=368,
	LOGID_369=369,
	LOGID_370=370,
	LOGID_371=371,
	LOGID_372=372,
	LOGID_373=373,
	LOGID_374=374,
	LOGID_375=375,
	LOGID_376=376,
	LOGID_377=377,
	LOGID_378=378,
	LOGID_379=379,
	LOGID_380=380,
	LOGID_381=381,
	LOGID_382=382,
	LOGID_383=383,
	LOGID_384=384,
	LOGID_385=385,
	LOGID_386=386,
	LOGID_387=387,
	LOGID_388=388,
	LOGID_389=389,
	LOGID_390=390,
	LOGID_391=391,
	LOGID_392=392,
	LOGID_393=393,
	LOGID_394=394,
	LOGID_395=395,
	LOGID_396=396,
	LOGID_397=397,
	LOGID_398=398,
	LOGID_399=399,
	LOGID_400=400,
	LOGID_401=401,
	LOGID_402=402,
	LOGID_403=403,
	LOGID_404=404,
	LOGID_405=405,
	LOGID_406=406,
	LOGID_407=407,
	LOGID_408=408,
	LOGID_409=409,
	LOGID_410=410,
	LOGID_411=411,
	LOGID_412=412,
	LOGID_413=413,
	LOGID_414=414,
	LOGID_415=415,
	LOGID_416=416,
	LOGID_417=417,
	LOGID_418=418,
	LOGID_419=419,
	LOGID_420=420,
	LOGID_421=421,
	LOGID_422=422,
	LOGID_423=423,
	LOGID_424=424,
	LOGID_425=425,
	LOGID_426=426,
	LOGID_427=427,
	LOGID_428=428,
	LOGID_429=429,
	LOGID_430=430,
	LOGID_431=431,
	LOGID_432=432,
	LOGID_433=433,
	LOGID_434=434,
	LOGID_435=435,
	LOGID_436=436,
	LOGID_437=437,
	LOGID_438=438,
	LOGID_439=439,
	LOGID_440=440,
	LOGID_441=441,
	LOGID_442=442,
	LOGID_443=443,
	LOGID_444=444,
	LOGID_445=445,
	LOGID_446=446,
	LOGID_447=447,
	LOGID_448=448,
	LOGID_449=449,
	LOGID_450=450,
	LOGID_451=451,
	LOGID_452=452,
	LOGID_453=453,
	LOGID_454=454,
	LOGID_455=455,
	LOGID_456=456,
	LOGID_457=457,
	LOGID_458=458,
	LOGID_459=459,
	LOGID_460=460,
	LOGID_461=461,
	LOGID_462=462,
	LOGID_463=463,
	LOGID_464=464,
	LOGID_465=465,
	LOGID_466=466,
	LOGID_467=467,
	LOGID_468=468,
	LOGID_469=469,
	LOGID_470=470,
	LOGID_471=471,
	LOGID_472=472,
	LOGID_473=473,
	LOGID_474=474,
	LOGID_475=475,
	LOGID_476=476,
	LOGID_477=477,
	LOGID_478=478,
	LOGID_479=479,
	LOGID_480=480,
	LOGID_481=481,
	LOGID_482=482,
	LOGID_483=483,
	LOGID_484=484,
	LOGID_485=485,
	LOGID_486=486,
	LOGID_487=487,
	LOGID_488=488,
	LOGID_489=489,
	LOGID_490=490,
	LOGID_491=491,
	LOGID_492=492,
	LOGID_493=493,
	LOGID_494=494,
	LOGID_495=495,
	LOGID_496=496,
	LOGID_497=497,
	LOGID_498=498,
	LOGID_499=499,
	LOGID_500=500,
	LOGID_501=501,
	LOGID_502=502,
	LOGID_503=503,
	LOGID_504=504,
	LOGID_505=505,
	LOGID_506=506,
	LOGID_507=507,
	LOGID_508=508,
	LOGID_509=509,
	LOGID_510=510,
	LOGID_511=511,
	LOGID_512=512,
	LOGID_513=513,
	LOGID_514=514,
	LOGID_515=515,
	LOGID_516=516,
	LOGID_517=517,
	LOGID_518=518,
	LOGID_519=519,
	LOGID_520=520,
	LOGID_521=521,
	LOGID_522=522,
	LOGID_523=523,
	LOGID_524=524,
	LOGID_525=525,
	LOGID_526=526,
	LOGID_527=527,
	LOGID_528=528,
	LOGID_529=529,
	LOGID_530=530,
	LOGID_531=531,
	LOGID_532=532,
	LOGID_533=533,
	LOGID_534=534,
	LOGID_535=535,
	LOGID_536=536,
	LOGID_537=537,
	LOGID_538=538,
	LOGID_539=539,
	LOGID_540=540,
	LOGID_541=541,
	LOGID_542=542,
	LOGID_543=543,
	LOGID_544=544,
	LOGID_545=545,
	LOGID_546=546,
	LOGID_547=547,
	LOGID_548=548,
	LOGID_549=549,
	LOGID_550=550,
	LOGID_551=551,
	LOGID_552=552,
	LOGID_553=553,
	LOGID_554=554,
	LOGID_555=555,
	LOGID_556=556,
	LOGID_557=557,
	LOGID_558=558,
	LOGID_559=559,
	LOGID_560=560,
	LOGID_561=561,
	LOGID_562=562,
	LOGID_563=563,
	LOGID_564=564,
	LOGID_565=565,
	LOGID_566=566, 
	LOGID_567=567,
	LOGID_568=568,
	LOGID_569=569,
	LOGID_570=570,
	LOGID_571=571,
	LOGID_572=572,
	LOGID_573=573,
	LOGID_574=574,
	LOGID_575=575,
	LOGID_576=576,
	LOGID_577=577,
	LOGID_578=578,
	LOGID_579=579,
	LOGID_580=580,
	LOGID_581=581,
	LOGID_582=582,
	LOGID_583=583,
	LOGID_584=584,
	LOGID_585=585,
	LOGID_586=586,
	LOGID_587=587,
	LOGID_588=588,
	LOGID_589=589,
	LOGID_590=590,
	LOGID_591=591,
	LOGID_592=592,
	LOGID_593=593,
	LOGID_594=594,
	LOGID_595=595,
	LOGID_596=596,
	LOGID_597=597,
	LOGID_598=598,
	LOGID_599=599,
	LOGID_600=600,
	LOGID_601=601,
	LOGID_602=602,
	LOGID_603=603,
	LOGID_604=604,
	LOGID_605=605,
	LOGID_606=606,
	LOGID_607=607,
	LOGID_608=608,
	LOGID_609=609,
	LOGID_610=610,
	LOGID_611=611,
	LOGID_612=612,
	LOGID_613=613,
	LOGID_614=614,
	LOGID_615=615,
	LOGID_616=616,
	LOGID_617=617,
	LOGID_618=618,
	LOGID_619=619,
	LOGID_620=620,
	LOGID_621=621,
	LOGID_622=622,
	LOGID_623=623,
	LOGID_624=624,
	LOGID_625=625,
	LOGID_626=626,
	LOGID_627=627,
	LOGID_628=628,
	LOGID_629=629,
	LOGID_630=630,
	LOGID_631=631,
	LOGID_632=632,
	LOGID_633=633,
	LOGID_634=634,
	LOGID_635=635,
	LOGID_636=636,
	LOGID_637=637,
	LOGID_638=638,
	LOGID_639=639,
	LOGID_640=640,
	LOGID_641=641,
	LOGID_642=642,
	LOGID_643=643,
	LOGID_644=644,
	LOGID_645=645,
	LOGID_646=646,
	LOGID_647=647,
	LOGID_648=648,
	LOGID_649=649,
	LOGID_650=650,
	LOGID_651=651,
	LOGID_652=652,
	LOGID_653=653,
	LOGID_654=654,
	LOGID_655=655,
	LOGID_656=656,
	LOGID_657=657,
	LOGID_658=658,
	LOGID_659=659,
	LOGID_660=660,
	LOGID_661=661,
	LOGID_662=662,
	LOGID_663=663,
	LOGID_664=664,
	LOGID_665=665,
	LOGID_666=666,
	LOGID_667=667,
	LOGID_668=668,
	LOGID_669=669,
	LOGID_670=670,
	LOGID_671=671,
	LOGID_672=672,
	LOGID_673=673,
	LOGID_674=674,
	LOGID_675=675,
	LOGID_676=676,
	LOGID_677=677,
	LOGID_678=678,
	LOGID_679=679,
	LOGID_680=680,
	LOGID_681=681,
	LOGID_682=682,
	LOGID_683=683,
	LOGID_684=684,
	LOGID_685=685,
	LOGID_686=686,
	LOGID_687=687,
	LOGID_688=688,
	LOGID_689=689,
	LOGID_690=690,
	LOGID_691=691,
	LOGID_692=692,
	LOGID_693=693,
	LOGID_694=694,
	LOGID_695=695,
	LOGID_696=696,
	LOGID_697=697,
	LOGID_698=698,
	LOGID_699=699,
	LOGID_700=700,
	LOGID_701=701,
	LOGID_702=702,
	LOGID_703=703,
	LOGID_704=704,
	LOGID_705=705,
	LOGID_706=706,
	LOGID_707=707,
	LOGID_708=708,
	LOGID_709=709,
	LOGID_710=710,
	LOGID_711=711,
	LOGID_712=712,
	LOGID_713=713,
	LOGID_714=714,
	LOGID_715=715,
	LOGID_716=716,
	LOGID_717=717,
	LOGID_718=718,
	LOGID_719=719,
	LOGID_720=720,
	LOGID_721=721,
	LOGID_722=722,
	LOGID_723=723,
	LOGID_724=724,
	LOGID_725=725,
	LOGID_726=726,
	LOGID_727=727,
	LOGID_728=728,
	LOGID_729=729,
	LOGID_730=730,
	LOGID_731=731,
	LOGID_732=732,
	LOGID_733=733,
	LOGID_734=734,
	LOGID_735=735,
	LOGID_736=736,
	LOGID_737=737,
	LOGID_738=738,
	LOGID_739=739,
	LOGID_740=740,
	LOGID_741=741,
	LOGID_742=742,
	LOGID_743=743,
	LOGID_744=744,
	LOGID_745=745,
	LOGID_746=746,
	LOGID_747=747,
	LOGID_748=748,
	LOGID_749=749,
	LOGID_750=750,
	LOGID_751=751,
	LOGID_752=752,
	LOGID_753=753,
	LOGID_754=754,
	LOGID_755=756,
	LOGID_756=756,
	LOGID_757=757,
	LOGID_758=758,
	LOGID_759=759,
	LOGID_760=760,
	LOGID_761=761,
	LOGID_762=762,
	LOGID_763=763,
	LOGID_764=764,
	LOGID_765=765,
	LOGID_766=766,
	LOGID_767=767,
	LOGID_768=768,
	LOGID_769=769,
	LOGID_770=770,
	LOGID_771=771,
	LOGID_772=772,
	LOGID_773=773,
	LOGID_774=774,
	LOGID_775=775,
	LOGID_776=776,
	LOGID_777=777,
	LOGID_778=778,
	LOGID_779=779,
	LOGID_780=780,
	LOGID_781=781,
	LOGID_782=782,
	LOGID_783=783,
	LOGID_784=784,
	LOGID_785=785,
	LOGID_786=786,
	LOGID_787=787,
	LOGID_788=788,
	LOGID_789=789,
	LOGID_790=790,
	LOGID_791=791,
	LOGID_792=792,
	LOGID_793=793,
	LOGID_794=794,
	LOGID_795=795,
	LOGID_796=796,
	LOGID_797=797,
	LOGID_798=798,
	LOGID_799=799,
	LOGID_800=800,
	LOGID_801=801,
	LOGID_802=802,
	LOGID_803=803,
	LOGID_804=804,
	LOGID_805=805,
	LOGID_806=806,
	LOGID_807=807,
	LOGID_808=808,
	LOGID_809=809,
	LOGID_810=810,
	LOGID_811=811,
	LOGID_812=812,
	LOGID_813=813,
	LOGID_814=814,
	LOGID_815=815,
	LOGID_816=816,
	LOGID_817=817,
	LOGID_818=818,
	LOGID_819=819,
	LOGID_820=820,
	LOGID_821=821,
	LOGID_822=822,
	LOGID_823=823,
	LOGID_824=824,
	LOGID_825=825,
	LOGID_826=826,
	LOGID_827=827,
	LOGID_828=828,
	LOGID_829=829,
	LOGID_830=830,
	LOGID_831=831,
	LOGID_832=832,
	LOGID_833=833,
	LOGID_834=834,
	LOGID_835=835,
	LOGID_836=836,
	LOGID_837=837,
	LOGID_838=838,
	LOGID_839=839,
	LOGID_840=840,
	LOGID_841=841,
	LOGID_842=842,
	LOGID_843=843,
	LOGID_844=844,
	LOGID_845=845,
	LOGID_846=846,
	LOGID_847=847,
	LOGID_848=848,
	LOGID_849=849,
	LOGID_850=850,
	LOGID_851=851,
	LOGID_852=852,
	LOGID_853=853,
	LOGID_854=854,
	LOGID_855=855,
	LOGID_856=856,
	LOGID_857=857,
	LOGID_858=858,
	LOGID_859=859,
	LOGID_860=860,
	LOGID_861=861,
	LOGID_862=862,
	LOGID_863=863,
	LOGID_864=864,
	LOGID_865=865,
	LOGID_866=866,
	LOGID_867=867,
	LOGID_868=868,
	LOGID_869=869,
	LOGID_870=870,
	LOGID_871=871,
	LOGID_872=872,
	LOGID_873=873,
	LOGID_874=874,
	LOGID_875=875,
	LOGID_876=876,
	LOGID_877=877,
	LOGID_878=878,
	LOGID_879=879,
	LOGID_880=880,
	LOGID_881=881,
	LOGID_882=882,
	LOGID_883=883,
	LOGID_884=884,
	LOGID_885=885,
	LOGID_886=886,
	LOGID_887=887,
	LOGID_888=888,
	LOGID_889=889,
	LOGID_890=890,
	LOGID_891=891,
	LOGID_892=892,
	LOGID_893=893,
	LOGID_894=894,
	LOGID_895=895,
	LOGID_896=896,
	LOGID_897=897,
	LOGID_898=898,
	LOGID_899=899,
	LOGID_900=900,
	LOGID_901=901,
	LOGID_902=902,
	LOGID_903=903,
	LOGID_904=904,
	LOGID_905=905,
	LOGID_906=906,
	LOGID_907=907,
	LOGID_908=908,
	LOGID_909=909,
	LOGID_910=910,
	LOGID_911=911,
	LOGID_912=912,
	LOGID_913=913,
	LOGID_914=914,
	LOGID_915=915,
	LOGID_916=916,
	LOGID_917=917,
	LOGID_918=918,
	LOGID_919=919,
	LOGID_920=920,
	LOGID_921=921,
	LOGID_922=922,
	LOGID_923=923,
	LOGID_924=924,
	LOGID_925=925,
	LOGID_926=926,
	LOGID_927=927,
	LOGID_928=928,
	LOGID_929=929,
	LOGID_930=930,
	LOGID_931=931,
	LOGID_932=932,
	LOGID_933=933,
	LOGID_934=934,
	LOGID_935=935,
	LOGID_936=936,
	LOGID_937=937,
	LOGID_938=938,
	LOGID_939=939,
	LOGID_940=940,
	LOGID_941=941,
	LOGID_942=942,
	LOGID_943=943,
	LOGID_944=944,
	LOGID_945=945,
	LOGID_946=946,
	LOGID_947=947,
	LOGID_948=948,
	LOGID_949=949,
	LOGID_950=950,
	LOGID_951=951,
	LOGID_952=952,
	LOGID_953=953,
	LOGID_954=954,
	LOGID_955=955,
	LOGID_956=956,
	LOGID_957=957,
	LOGID_958=958,
	LOGID_959=959,
	LOGID_960=960,
	LOGID_961=961,
	LOGID_962=962,
	LOGID_963=963,
	LOGID_964=964,
	LOGID_965=965,
	LOGID_966=966,
	LOGID_967=967,
	LOGID_968=968,
	LOGID_969=969,
	LOGID_970=970,
	LOGID_971=971,
	LOGID_972=972,
	LOGID_973=973,
	LOGID_974=974,
	LOGID_975=975,
	LOGID_976=976,
	LOGID_977=977,
	LOGID_978=978,
	LOGID_979=979,
	LOGID_980=980,
	LOGID_981=981,
	LOGID_982=982,
	LOGID_983=983,
	LOGID_984=984,
	LOGID_985=985,
	LOGID_986=986,
	LOGID_987=987,
	LOGID_988=988,
	LOGID_989=989,
	LOGID_990=990,
	LOGID_991=991,
	LOGID_992=992,
	LOGID_993=993,
	LOGID_994=994,
	LOGID_995=995,
	LOGID_996=996,
	LOGID_997=997,
	LOGID_998=998,
	LOGID_999=999,
	LOGID_1000=1000,
	LOGID_1001=1001,
	LOGID_1002=1002,
	LOGID_1003=1003,
	LOGID_1004=1004,
	LOGID_1005=1005,
	LOGID_1006=1006,
	LOGID_1007=1007,
	LOGID_1008=1008,
	LOGID_1009=1009,
	LOGID_1010=1010,
	LOGID_1011=1011,
	LOGID_1012=1012,
	LOGID_1013=1013,
	LOGID_1014=1014,
	LOGID_1015=1015,
	LOGID_1016=1016,
	LOGID_1017=1017,
	LOGID_1018=1018,
	LOGID_1019=1019,
	LOGID_1020=1020,
	LOGID_1021=1021,
	LOGID_1022=1022,
	LOGID_1023=1023,
	LOGID_1024=1024,
	LOGID_1025=1025,
	LOGID_1026=1026,
	LOGID_1027=1027,
	LOGID_1028=1028,
	LOGID_1029=1029,
	LOGID_1030=1030,
	LOGID_1031=1031,
	LOGID_1032=1032,
	LOGID_1033=1033,
	LOGID_1034=1034,
	LOGID_1035=1035,
	LOGID_1036=1036,
	LOGID_1037=1037,
	LOGID_1038=1038,
	LOGID_1039=1039,
	LOGID_1040=1040,
	LOGID_1041=1041,
	LOGID_1042=1042,
	LOGID_1043=1043,
	LOGID_1044=1044,
	LOGID_1045=1045,
	LOGID_1046=1046,
	LOGID_1047=1047,
	LOGID_1048=1048,
	LOGID_1049=1049,
	LOGID_1050=1050,
	LOGID_1051=1051,
	LOGID_1052=1052,
	LOGID_1053=1053,
	LOGID_1054=1054,
	LOGID_1055=1055,
	LOGID_1056=1056,
	LOGID_1057=1057,
	LOGID_1058=1058,
	LOGID_1059=1059,
	LOGID_1060=1060,
	LOGID_1061=1061,
	LOGID_1062=1062,
	LOGID_1063=1063,
	LOGID_1064=1064,
	LOGID_1065=1065,
	LOGID_1066=1066,
	LOGID_1067=1067,
	LOGID_1068=1068,
	LOGID_1069=1069,
	LOGID_1070=1070,
	LOGID_1071=1071,
	LOGID_1072=1072,
	LOGID_1073=1073,
	LOGID_1074=1074,
	LOGID_1075=1075,
	LOGID_1076=1076,
	LOGID_1077=1077,
	LOGID_1078=1078,
	LOGID_1079=1079,
	LOGID_1080=1080,
	LOGID_1081=1081,
	LOGID_1082=1082,
	LOGID_1083=1083,
	LOGID_1084=1084,
	LOGID_1085=1085,
	LOGID_1086=1086,
	LOGID_1087=1087,
	LOGID_1088=1088,
	LOGID_1089=1089,
	LOGID_1090=1090,
	LOGID_1091=1091,
	LOGID_1092=1092,
	LOGID_1093=1093,
	LOGID_1094=1094,
	LOGID_1095=1095,
	LOGID_1096=1096,
	LOGID_1097=1097,
	LOGID_1098=1098,
	LOGID_1099=1099,
	LOGID_1100=1100,
	LOGID_1101=1101,
	LOGID_1102=1102,
	LOGID_1103=1103,
	LOGID_1104=1104,
	LOGID_1105=1105,
	LOGID_1106=1106,
	LOGID_1107=1107,
	LOGID_1108=1108,
	LOGID_1109=1109,
	LOGID_1110=1110,
	LOGID_1111=1111,
	LOGID_1112=1112,
	LOGID_1113=1113,
	LOGID_1114=1114,
	LOGID_1115=1115,
	LOGID_1116=1116,
	LOGID_1117=1117,
	LOGID_1118=1118,
	LOGID_1119=1119,
	LOGID_1120=1120,
	LOGID_1121=1121,
	LOGID_1122=1122,
	LOGID_1123=1123,
	LOGID_1124=1124,
	LOGID_1125=1125,
	LOGID_1126=1126,
	LOGID_1127=1127,
	LOGID_1128=1128,
	LOGID_1129=1129,
	LOGID_1130=1130,
	LOGID_1131=1131,
	LOGID_1132=1132,
	LOGID_1133=1133,
	LOGID_1134=1134,
	LOGID_1135=1135,
	LOGID_1136=1136,
	LOGID_1137=1137,
	LOGID_1138=1138,
	LOGID_1139=1139,
	LOGID_1140=1140,
	LOGID_1141=1141,
	LOGID_1142=1142,
	LOGID_1143=1143,
	LOGID_1144=1144,
	LOGID_1145=1145,
	LOGID_1146=1146,
	LOGID_1147=1147,
	LOGID_1148=1148,
	LOGID_1149=1149,
	LOGID_1150=1150,
	LOGID_1151=1151,
	LOGID_1152=1152,
	LOGID_1153=1153,
	LOGID_1154=1154,
	LOGID_1155=1155,
	LOGID_1156=1156,
	LOGID_1157=1157,
	LOGID_1158=1158,
	LOGID_1159=1159,
	LOGID_1160=1160,
	LOGID_1161=1161,
	LOGID_1162=1162,
	LOGID_1163=1163,
	LOGID_1164=1164,
	LOGID_1165=1165,
	LOGID_1166=1166,
	LOGID_1167=1167,
	LOGID_1168=1168,
	LOGID_1169=1169,
	LOGID_1170=1170,
	LOGID_1171=1171,
	LOGID_1172=1172,
	LOGID_1173=1173,
	LOGID_1174=1174,
	LOGID_1175=1175,
	LOGID_1176=1176,
	LOGID_1177=1177,
	LOGID_1178=1178,
	LOGID_1179=1179,
	LOGID_1180=1180,
	LOGID_1181=1181,
	LOGID_1182=1182,
	LOGID_1183=1183,
	LOGID_1184=1184,
	LOGID_1185=1185,
	LOGID_1186=1186,
	LOGID_1187=1187,
	LOGID_1188=1188,
	LOGID_1189=1189,
	LOGID_1190=1190,
	LOGID_1191=1191,
	LOGID_1192=1192,
	LOGID_1193=1193,
	LOGID_1194=1194,
	LOGID_1195=1195,
	LOGID_1196=1196,
	LOGID_1197=1197,
	LOGID_1198=1198,
	LOGID_1199=1199,
	LOGID_1200=1200,
	LOGID_1201=1201,
	LOGID_1202=1202,
	LOGID_1203=1203,
	LOGID_1204=1204,
	LOGID_1205=1205,
	LOGID_1206=1206,
	LOGID_1207=1207,
	LOGID_1208=1208,
	LOGID_1209=1209,
	LOGID_1210=1210,
	LOGID_1211=1211,
	LOGID_1212=1212,
	LOGID_1213=1213,
	LOGID_1214=1214,
	LOGID_1215=1215,
	LOGID_1216=1216,
	LOGID_1217=1217,
	LOGID_1218=1218,
	LOGID_1219=1219,
	LOGID_1220=1220,
	LOGID_1221=1221,
	LOGID_1222=1222,
	LOGID_1223=1223,
	LOGID_1224=1224,
	LOGID_1225=1225,
	LOGID_1226=1226,
	LOGID_1227=1227,
	LOGID_1228=1228,
	LOGID_1229=1229,
	LOGID_1230=1230,
	LOGID_1231=1231,
	LOGID_1232=1232,
	LOGID_1233=1233,
	LOGID_1234=1234,
	LOGID_1235=1235,
	LOGID_1236=1236,
	LOGID_1237=1237,
	LOGID_1238=1238,
	LOGID_1239=1239,
	LOGID_1240=1240,
	LOGID_1241=1241,
	LOGID_1242=1242,
	LOGID_1243=1243,
	LOGID_1244=1244,
	LOGID_1245=1245,
	LOGID_1246=1246,
	LOGID_1247=1247,
	LOGID_1248=1248,
	LOGID_1249=1249,
	LOGID_1250=1250,
	LOGID_1251=1251,
	LOGID_1252=1252,
	LOGID_1253=1253,
	LOGID_1254=1254,
	LOGID_1255=1255,
	LOGID_1256=1256,
	LOGID_1257=1257,
	LOGID_1258=1258,
	LOGID_1259=1259,
	LOGID_1260=1260,
	LOGID_1261=1261,
	LOGID_1262=1262,
	LOGID_1263=1263,
	LOGID_1264=1264,
	LOGID_1265=1265,
	LOGID_1266=1266,
	LOGID_1267=1267,
	LOGID_1268=1268,
	LOGID_1269=1269,
	LOGID_1270=1270,
	LOGID_1271=1271,
	LOGID_1272=1272,
	LOGID_1273=1273,
	LOGID_1274=1274,
	LOGID_1275=1275,
	LOGID_1276=1276,
	LOGID_1277=1277,
	LOGID_1278=1278,
	LOGID_1279=1279,
	LOGID_1280=1280,
	LOGID_1281=1281,
	LOGID_1282=1282,
	LOGID_1283=1283,
	LOGID_1284=1284,
	LOGID_1285=1285,
	LOGID_1286=1286,
	LOGID_1287=1287,
	LOGID_1288=1288,
	LOGID_1289=1289,
	LOGID_1290=1290,
	LOGID_1291=1291,
	LOGID_1292=1292,
	LOGID_1293=1293,
	LOGID_1294=1294,
	LOGID_1295=1295,
	LOGID_1296=1296,
	LOGID_1297=1297,
	LOGID_1298=1298,
	LOGID_1299=1299,
	LOGID_1300=1300,
	LOGID_1301=1301,
	LOGID_1302=1302,
	LOGID_1303=1303,
	LOGID_1304=1304,
	LOGID_1305=1305,
	LOGID_1306=1306,
	LOGID_1307=1307,
	LOGID_1308=1308,
	LOGID_1309=1309,
	LOGID_1310=1310,
	LOGID_1311=1311,
	LOGID_1312=1312,
	LOGID_1313=1313,
	LOGID_1314=1314,
	LOGID_1315=1315,
	LOGID_1316=1316,
	LOGID_1317=1317,
	LOGID_1318=1318,
	LOGID_1319=1319,
	LOGID_1320=1320,
	LOGID_1321=1321,
	LOGID_1322=1322,
	LOGID_1323=1323,
	LOGID_1324=1324,
	LOGID_1325=1325,
	LOGID_1326=1326,
	LOGID_1327=1327,
	LOGID_1328=1328,
	LOGID_1329=1329,
	LOGID_1330=1330,
	LOGID_1331=1331,
	LOGID_1332=1332,
	LOGID_1333=1333,
	LOGID_1334=1334,
	LOGID_1335=1335,
	LOGID_1336=1336,
	LOGID_1337=1337,
	LOGID_1338=1338,
	LOGID_1339=1339,
	LOGID_1340=1340,
	LOGID_1341=1341,
	LOGID_1342=1342,
	LOGID_1343=1343,
	LOGID_1344=1344,
	LOGID_1345=1345,
	LOGID_1346=1346,
	LOGID_1347=1347,
	LOGID_1348=1348,
	LOGID_1349=1349,
	LOGID_1350=1350,
	LOGID_1351=1351,
	LOGID_1352=1352,
	LOGID_1353=1353,
	LOGID_1354=1354,
	LOGID_1355=1355,
	LOGID_1356=1356,
	LOGID_1357=1357,
	LOGID_1358=1358,
	LOGID_1359=1359,
	LOGID_1360=1360,
	LOGID_1361=1361,
	LOGID_1362=1362,
	LOGID_1363=1363,
	LOGID_1364=1364,
	LOGID_1365=1365,
	LOGID_1366=1366,
	LOGID_1367=1367,
	LOGID_1368=1368,
	LOGID_1369=1369,
	LOGID_1370=1370,
	LOGID_1371=1371,
	LOGID_1372=1372,
	LOGID_1373=1373,
	LOGID_1374=1374,
	LOGID_1375=1375,
	LOGID_1376=1376,
	LOGID_1377=1377,
	LOGID_1378=1378,
	LOGID_1379=1379,
	LOGID_1380=1380,
	LOGID_1381=1381,
	LOGID_1382=1382,
	LOGID_1383=1383,
	LOGID_1384=1384,
	LOGID_1385=1385,
	LOGID_1386=1386,
	LOGID_1387=1387,
	LOGID_1388=1388,
	LOGID_1389=1389,
	LOGID_1390=1390,
	LOGID_1391=1391,
	LOGID_1392=1392,
	LOGID_1393=1393,
	LOGID_1394=1394,
	LOGID_1395=1395,
	LOGID_1396=1396,
	LOGID_1397=1397,
	LOGID_1398=1398,
	LOGID_1399=1399,
	LOGID_1400=1400,
	LOGID_1401=1401,
	LOGID_1402=1402,
	LOGID_1403=1403,
	LOGID_1404=1404,
	LOGID_1405=1405,
	LOGID_1406=1406,
	LOGID_1407=1407,
	LOGID_1408=1408,
	LOGID_1409=1409,
	LOGID_1410=1410,
	LOGID_1411=1411,
	LOGID_1412=1412,
	LOGID_1413=1413,
	LOGID_1414=1414,
	LOGID_1415=1415,
	LOGID_1416=1416,
	LOGID_1417=1417,
	LOGID_1418=1418,
	LOGID_1419=1419,
	LOGID_1420=1420,
	LOGID_1421=1421,
	LOGID_1422=1422,
	LOGID_1423=1423,
	LOGID_1424=1424,
	LOGID_1425=1425,
	LOGID_1426=1426,
	LOGID_1427=1427,
	LOGID_1428=1428,
	LOGID_1429=1429,
	LOGID_1430=1430,
	LOGID_1431=1431,
	LOGID_1432=1432,
	LOGID_1433=1433,
	LOGID_1434=1434,
	LOGID_1435=1435,
	LOGID_1436=1436,
	LOGID_1437=1437,
	LOGID_1438=1438,
	LOGID_1439=1439,
	LOGID_1440=1440,
	LOGID_1441=1441,
	LOGID_1442=1442,
	LOGID_1443=1443,
	LOGID_1444=1444,
	LOGID_1445=1445,
	LOGID_1446=1446,
	LOGID_1447=1447,
	LOGID_1448=1448,
	LOGID_1449=1449,
	LOGID_1450=1450,
	LOGID_1451=1451,
	LOGID_1452=1452,
	LOGID_1453=1453,
	LOGID_1454=1454,
	LOGID_1455=1455,
	LOGID_1456=1456,
	LOGID_1457=1457,
	LOGID_1458=1458,
	LOGID_1459=1459,
	LOGID_1460=1460,
	LOGID_1461=1461,
	LOGID_1462=1462,
	LOGID_1463=1463,
	LOGID_1464=1464,
	LOGID_1465=1465,
	LOGID_1466=1466,
	LOGID_1467=1467,
	LOGID_1468=1468,
	LOGID_1469=1469,
	LOGID_1470=1470,
	LOGID_1471=1471,
	LOGID_1472=1472,
	LOGID_1473=1473,
	LOGID_1474=1474,
	LOGID_1475=1475,
	LOGID_1476=1476,
	LOGID_1477=1477,
	LOGID_1478=1478,
	LOGID_1479=1479,
	LOGID_1480=1480,
	LOGID_1481=1481,
	LOGID_1482=1482,
	LOGID_1483=1483,
	LOGID_1484=1484,
	LOGID_1485=1485,
	LOGID_1486=1486,
	LOGID_1487=1487,
	LOGID_1488=1488,
	LOGID_1489=1489,
	LOGID_1490=1490,
	LOGID_1491=1491,
	LOGID_1492=1492,
	LOGID_1493=1493,
	LOGID_1494=1494,
	LOGID_1495=1495,
	LOGID_1496=1496,
	LOGID_1497=1497,
	LOGID_1498=1498,
	LOGID_1499=1499,
	LOGID_1500=1500,
	LOGID_1501=1501,
	LOGID_1502=1502,
	LOGID_1503=1503,
	LOGID_1504=1504,
	LOGID_1505=1505,
	LOGID_1506=1506,
	LOGID_1507=1507,
	LOGID_1508=1508,
	LOGID_1509=1509,
	LOGID_1510=1510,
	LOGID_1511=1511,
	LOGID_1512=1512,
	LOGID_1513=1513,
	LOGID_1514=1514,
	LOGID_1515=1515,
	LOGID_1516=1516,
	LOGID_1517=1517,
	LOGID_1518=1518,
	LOGID_1519=1519,
	LOGID_1520=1520,
	LOGID_1521=1521,
	LOGID_1522=1522,
	LOGID_1523=1523,
	LOGID_1524=1524,
	LOGID_1525=1525,
	LOGID_1526=1526,
	LOGID_1527=1527,
	LOGID_1528=1528,
	LOGID_1529=1529,
	LOGID_1530=1530,
	LOGID_1531=1531,
	LOGID_1532=1532,
	LOGID_1533=1533,
	LOGID_1534=1534,
	LOGID_1535=1535,
	LOGID_1536=1536,
	LOGID_1537=1537,
	LOGID_1538=1538,
	LOGID_1539=1539,
	LOGID_1540=1540,
	LOGID_1541=1541,
	LOGID_1542=1542,
	LOGID_1543=1543,
	LOGID_1544=1544,
	LOGID_1545=1545,
	LOGID_1546=1546,
	LOGID_1547=1547,
	LOGID_1548=1548,
	LOGID_1549=1549,
	LOGID_1550=1550,
	LOGID_1551=1551,
	LOGID_1552=1552,
	LOGID_1553=1553,
	LOGID_1554=1554,
	LOGID_1555=1555,
	LOGID_1556=1556,
	LOGID_1557=1557,
	LOGID_1558=1558,
	LOGID_1559=1559,
	LOGID_1560=1560,
	LOGID_1561=1561,
	LOGID_1562=1562,
	LOGID_1563=1563,
	LOGID_1564=1564,
	LOGID_1565=1565,
	LOGID_1566=1566,
	LOGID_1567=1567,
	LOGID_1568=1568,
	LOGID_1569=1569,
	LOGID_1570=1570,
	LOGID_1571=1571,
	LOGID_1572=1572,
	LOGID_1573=1573,
	LOGID_1574=1574,
	LOGID_1575=1575,
	LOGID_1576=1576,
	LOGID_1577=1577,
	LOGID_1578=1578,
	LOGID_1579=1579,
	LOGID_1580=1580,
	LOGID_1581=1581,
	LOGID_1582=1582,
	LOGID_1583=1583,
	LOGID_1584=1584,
	LOGID_1585=1585,
	LOGID_1586=1586,
	LOGID_1587=1587,
	LOGID_1588=1588,
	LOGID_1589=1589,
	LOGID_1590=1590,
	LOGID_1591=1591,
	LOGID_1592=1592,
	LOGID_1593=1593,
	LOGID_1594=1594,
	LOGID_1595=1595,
	LOGID_1596=1596,
	LOGID_1597=1597,
	LOGID_1598=1598,
	LOGID_1599=1599,/* unused */
	LOGID_1600=1600,/* unused */
	LOGID_1601=1601,
	LOGID_1602=1602,
	LOGID_1603=1603,




	LOGID_LASTONE /* DO NOT USE, just for convenience */
} CTLOG_ENTRY_ID;

#endif /*_CTLOGIDS_H_*/
/* end of ctlogids.h */

