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
 *      Copyright (c) 1992 - 2014 FairCom Corporation.
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

/* Header files. ***********************************************************/

#ifdef PROTOTYPE
#include <stdarg.h>
#else
#include <varargs.h>
#endif


/* Global constants. *******************************************************/

/*
 * Uncomment this define to log times to disk.
#define ctLOGTIMESTODISK
 */

#define SVN_DEFAULT "FAIRCOMS"	/* Default server name.		*/
#define UID_DEFAULT ""		/* Default user name.		*/
#define UPW_DEFAULT ""		/* Default user password.	*/
#define NUML	     6
#define NAML        24
#define CLSL         2
#define PADG        88

#if ctVER_LT(10,0)
int vlogerr (char *text, ...)
{
	return(0);
}

int ctree_lock (pIFIL ifilptr, NINT mode)
{
	return(0);
}

#ifdef ctPortLINUX
#define ctrt_localtime_r localtime_r
#define ctrt_asctime_r asctime_r
#define ctrt_fgets fgets
#endif

#endif

#ifndef ctrt_printf
#define ctrt_printf printf /* ensure console (non-GUI) output */
#endif

/* Global structures. ******************************************************/

typedef struct		/* Data record structure. */
{
	COUNT dlfg;
	TEXT  unqu[NUML];
	LONG  sern; /* Auto serial number. */
	COUNT dlen;
	TEXT  name[NAML];
	TEXT  clss[CLSL];
	TEXT  grbg[128 - ctSIZE(COUNT) - ctSIZE(LONG) - ctSIZE(COUNT) -
               NUML - NAML - CLSL];
} DREC;

#define ACTION_ADD		1	/* add records			*/
#define ACTION_GET		2	/* read records			*/
#define ACTION_UPDATE		3	/* update records		*/
#define ACTION_DELETE		4	/* delete records		*/
#define ACTION_TESTFUNC		5	/* call test function		*/
#define ACTION_CTUSERX		6	/* call CTUSERX function	*/
#define ACTION_STOP		7	/* logoff			*/
#define ACTION_OPENCLOSE	8	/* open/close files		*/
#define ACTION_ADDKEY		9	/* add keys to index member	*/
#define ACTION_NEWREC		10	/* allocate space in data file	*/

typedef struct		/* Application options. */
{
	NINT	action;		/* Type of action.			*/
	TEXT	filestat;	/* Create new files?			*/
	TEXT	mode;		/* Transaction processing mode.		*/
	LONG	trials;		/* Number of trials.			*/
	pTEXT	svn;		/* Server name.				*/
	pTEXT	uid;		/* User name.				*/
	pTEXT	upw;		/* User password.			*/
	pTEXT	enc;		/* File encryption cipher.		*/
	pTEXT	filnam;		/* Data file name.			*/
	TEXT	filnamx[MAX_NAME]; /* Data file name with extension.	*/
	NINT	compress;	/* Create compressed record file.	*/
	NINT	vlen;		/* Create variable-length record file.	*/
#ifdef ctFeatVARLENnodefmt
	NINT	vlennod;	/* Use variable-length node data format.*/
	NINT	trnmrkopt;	/* Transaction mark optimized storage.	*/
	NINT	cmpoff;		/* Offset compression in index nodes.	*/
#endif
	NINT	atotrnmod;	/* Create files w/auto switch to tran.	*/
	NINT	datmem;		/* Data cache size in MB.		*/
	NINT	idxmem;		/* Index cache size in MB.		*/
	NINT	huge_ctfile;	/* Create huge file.			*/
	NINT	segm;		/* Create segmented file.		*/
	NINT	noxhdr;		/* Create file without extended header.	*/
	UCOUNT	seed;		/* Random number seed.			*/
	COUNT	trnlen;		/* Number of operations per transaction.*/
	NINT	maxfiles;	/* Maximum number of files.		*/
	NINT	quiet;		/* Quiet mode.				*/
	NINT	exclusive;	/* Open files in exclusive mode.	*/
	NINT	pagesize;	/* Index page size.			*/
	LONG	bufs;		/* Number of index buffers.		*/
	LONG	dbufs;		/* Number of data cache pages.		*/
	LONG	round;		/* Round number (1, 2, or 3).		*/
} APPOPTS, *pAPPOPTS;


/* Function prototypes. ****************************************************/
#ifdef PROTOTYPE
VOID appDescribe(VOID);
#else
VOID appDescribe();
#endif
#ifdef CTSTAP_C
#ifdef PROTOTYPE
VOID th_printf(NINT t, pTEXT arg0, ... );
#else
VOID th_printf();
#endif
#else  /* ~CTSTAP_C */
VOID th_printf(LONG proc_id, pTEXT fmt, ... );
#endif /* ~CTSTAP_C */


/* Global variables. *******************************************************/

COUNT     trnlen;	/* Number of operations per transaction.	*/
UCOUNT    seed;		/* Random number seed.				*/
NINT	  quiet;	/* Quiet mode.					*/
struct tm ct_tm;	/* Start/end date and time.			*/
TEXT      mode;		/* Transaction processing mode.			*/
NINT      action;	/* Type of action.				*/
pTEXT     svn;		/* Server name.					*/
pTEXT     uid;		/* User name.					*/
pTEXT     upw;		/* User password.				*/
#ifdef TRANPROC
COUNT	  filmod;	/* File mode.					*/
#endif
#ifdef ctLOGTIMESTODISK
FILE	 *fpTIMES;	/* Working file pointer to log info to disk.	*/
#endif
#if defined(ctCAMOsdk) && !defined(ctCLIENT) && !defined(ctDLLLIB)
extern NINT cmosdksup;
#endif
#define width 80

VRLEN     inbufsiz = 0;		/* Input buffer size for CTUSERX() calls  */
VRLEN     outbufsiz = 0;	/* Output buffer size for CTUSERX() calls */

/* ************************************************************************* */
/* ************************************************************************* */

/*
 * sysdate: Return current system time.
 */

#ifdef PROTOTYPE
LONG sysdate(void)
#else
LONG sysdate()
#endif
{
	time_t	ltime;

	time(&ltime);
	ctrt_localtime_r(&ltime, &ct_tm);
	return((LONG)ltime);
} /* sysdate() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * rate: Compute and display elapsed time and time per operation for a trial.
 */

#ifdef PROTOTYPE
VOID rate(NINT proc_id,LONG lstop,LONG lstart,LONG trials,pTEXT th_str)
#else
VOID rate(proc_id,lstop,lstart,trials,th_str)
NINT	proc_id;
LONG	lstop,lstart,trials;
pTEXT	th_str;
#endif
{
	if (!trials)
		return;
	lstop -= lstart;        /* Elapsed seconds. */
	th_printf(proc_id,
"Elapsed time: %ld (sec)\nTime per op: %ld (sec/1000)\n",
		lstop, (lstop * 1000) / trials);

#ifdef ctLOGTIMESTODISK
	fprintf(fpTIMES,
"\n%s  Elapsed time : %ld (sec) time per op = %ld (sec/1000)\n\n",
		th_str, lstop, (lstop * 1000) / trials);  
#endif
} /* rate() */


#ifdef TRANPROC
/* ************************************************************************* */
/* ************************************************************************* */

/*
 * tbeg: Start a transaction.
 */

#ifdef PROTOTYPE
COUNT tbeg(pNINT ptlen,pNINT ptrst)
#else
COUNT tbeg(ptlen,ptrst)
pNINT ptlen,ptrst;
#endif
{
	COUNT	status = 0;

	if (*ptlen == 0)
	{
		*ptlen = trnlen;
		*ptrst = 0;
		TRANBEG((COUNT)(mode == 't' ?
		     (ctPREIMG | ctENABLE) : (ctTRNLOG | ctENABLE)));
		status = uerr_cod;
	}
	return(status);
} /* tbeg() */
#endif


#ifdef TRANPROC
/* ************************************************************************* */
/* ************************************************************************* */

/*
 * tend: Commit or abort a transaction, or set or restore a save point.
 */

#ifdef PROTOTYPE
COUNT tend(NINT proc_id,pNINT ptlen,NINT status,pNINT ptrst,pNINT tcnt,NINT tchg)
#else
COUNT tend(proc_id,ptlen,status,ptrst,tcnt,tchg)
NINT  proc_id;
pNINT ptlen,ptrst,tcnt;
NINT  status,tchg;
#endif
{

	if (status)
		if (*ptlen == trnlen || ++(*ptrst) > 3)
		{
			*ptlen = *ptrst = 0;
			TRANABT();
			return(status);
		}
		else
		{
			TRANRST(-1);
			return(status);
		}

	(*ptlen)--;
	if (*ptlen == 0)
	{
		*ptrst = 0;
		if (status)
			status = TRANABT();
		else
		{
			status = TRANEND(ctFREE);
			if (status == 0)
			{
				*tcnt += tchg;
				if (!quiet)
				th_printf(proc_id, "\r  TT %d", *tcnt);
			}
		}
		return(status);
	} else
		TRANSAV();

	return(0);
} /* tend() */
#endif


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * unif: Return a number in the range l..u.
 */

static ULONG unif (ULONG l,ULONG u)
{
	ULONG retval;

	seed = 11737 * seed + 3731;
	retval = (seed % ((ULONG) (u - l + 1))) + l;

	return(retval);
} /* unif() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * setval: Generate a field value.
 */

static void setval (PFAST pTEXT tp,COUNT vl,COUNT fl,COUNT vr)
{
	FAST COUNT i;
	COUNT      keyl;
	TEXT       lstchr;

	for (i = 0; i < vl; i++)
		*tp++ = 'A' + (TEXT) unif(0,vr);
	lstchr = *(tp - 1);
	keyl   = (COUNT) unif(vl,fl);
	for (i = vl; i < keyl; i++)
		*tp++ = lstchr;
	for (i = keyl; i < fl; i++)
		*tp++ = ' ';
} /* setval() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * getskey: Return a number in the range l..u.
 */

FILNO getskey (FILNO l,FILNO u)
{
	FILNO retval;

	retval = (FILNO) unif(l,u);
	return(retval);
} /* getskey() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * getnum: Return the numeric (LONG) value of a string.
 */

#ifdef PROTOTYPE
LONG getnum(pTEXT tp)
#else
LONG getnum(tp)
pTEXT tp;
#endif
{
	LONG retval;

	retval = 0L;
	do
	{
		if (*tp >= '0' && *tp <= '9')
		{
			retval *= 10;
			retval += (*tp - '0');
		}
	} while (*tp++);
	return(retval);
} /* getnum() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * getwrd3: Prompt user for input and get user's input.
 */

#ifdef PROTOTYPE
static VOID getwrd3(pTEXT tp,NINT size,pTEXT prompt)
#else
static VOID getwrd3(tp,size,prompt)
pTEXT tp;
NINT  size;
pTEXT prompt;
#endif
{
	pTEXT sp;
	TEXT  dflt[MAX_NAME];

	sp = tp;
	ctrt_strcpy(dflt,tp); 

loop:
	tp = sp;
#ifdef ctMACINTOSH
	ctrt_printf("\nEnter %s: [%s]\n",prompt,dflt);
	gets(tp);
	while (size)
	{
#else
	ctrt_printf("\nEnter %s: [%s] ",prompt,dflt);
	fflush(stdout);
	while (size)
	{
		*tp = (TEXT)getchar(); /* if possible change to a no echo form */
#endif
		if (*tp == '\r' || *tp == '\n' || *tp == '\0')
		{
			if (sp != tp)
				*tp = '\0';
			else
				*tp = *dflt;
			if (ctrt_strcmp((pTEXT) sp,(pTEXT) "?") == 0)
			{
				ctrt_printf("\n");
				goto loop;
			}
			return;
		}
		tp++;
		size--;
	}
	*(tp - 1) = '\0';
} /* getwrd3() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * getstr2: Get a string from user.
 */

#ifdef PROTOTYPE
pTEXT getstr2(pTEXT dflt,pTEXT prompt)
#else
pTEXT getstr2(dflt,prompt)
pTEXT dflt;
pTEXT prompt;
#endif
{
	getwrd3(dflt,MAX_NAME,prompt); 
	return(dflt);
} /* getstr2() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * getchr: Get a string from user; return a character.
 */

#ifdef PROTOTYPE
TEXT getchr(TEXT dflt,pTEXT prompt)
#else
TEXT getchr(dflt,prompt)
TEXT  dflt;
pTEXT prompt;
#endif
{
	TEXT inpbuf[MAX_NAME], inpchr;

	ctrt_sprintf(inpbuf,"%c",dflt);
	getwrd3(inpbuf,MAX_NAME,prompt);
	inpchr = inpbuf[0];
	return(inpchr);
} /* getchr() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * getlng: Get a string from user; return a LONG.
 */

#ifdef PROTOTYPE
LONG getlng(LONG dflt,pTEXT prompt)
#else
LONG getlng(dflt,prompt)
LONG  dflt;
pTEXT prompt;
#endif
{
	LONG inplng;
	TEXT inpbuf[MAX_NAME];

	ctrt_sprintf(inpbuf, "%d", dflt);
	getwrd3(inpbuf, MAX_NAME, prompt);
	inplng = getnum(inpbuf);
	return(inplng);
} /* getlng() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * getcnt: Get a string from user; return a UCOUNT.
 */

#ifdef PROTOTYPE
UCOUNT getcnt(COUNT dflt,pTEXT prompt)
#else
UCOUNT getcnt(dflt,prompt)
COUNT dflt;
pTEXT prompt;
#endif
{
	TEXT   inpbuf[MAX_NAME];
	UCOUNT inpcnt;

	ctrt_sprintf(inpbuf, "%d", dflt);
	getwrd3(inpbuf, MAX_NAME, prompt);
	inpcnt = (UCOUNT)getnum(inpbuf);
	return(inpcnt);
} /* getcnt() */


/* ************************************************************************* */
/* ************************************************************************* */

/*
 * tcode: Run a trial.
 */

static NINT tcode (pVOID t)
{
	NINT		proc_id;
	LONG		round;
	LONG		trials;
	LONG		itrial,lstart,lstop;
	NINT		tlen,trst;
	NINT		status;
	NINT		tcnt = 0;
	COUNT		finds,locks;
	FILNO		key;
	FILNO		datno;
	pAPPOPTS	pOptions;
	DREC		updblk,datblk;
	TEXT		th_str[48];
	TEXT		keybuf[80];
	TEXT		newbuf[80];
	TEXT		qmsg[20];
	TEXT		timebuf[26];
	TEXT		filnamx[MAX_NAME];

	pOptions = (pAPPOPTS)t;
	trials   = pOptions->trials;
	proc_id  = (pOptions->round % 100L) - 1;
	round = (pOptions->round / 100L) + 1L;
	strcpy(filnamx,pOptions->filnamx);

	th_printf(proc_id, "Started.\n");

	sprintf(th_str, " Round #%d", round);

	memset(&datblk,0,sizeof(datblk));
	memset(&updblk,0,sizeof(updblk));
	lstart = 0L;
	tlen = trst = 0;

	/* Stop. ***************************************************/
	if (action == ACTION_STOP)
	{
		STPUSR();
		goto exit_thrd;
	}

#if defined(ctCAMOsdk) && !defined(ctCLIENT) && !defined(ctDLLLIB)
	/* request for advanced encryption? */
	if(pOptions->enc[0] && strcmp(pOptions->enc,ctENCR))
		/* initialize advanced encryption */
		cmosdksup=1;
#endif

	if (pOptions->datmem) {
		pOptions->dbufs = (LONG) (((LONG8) pOptions->datmem * 1024 * 1024) /
			(pOptions->pagesize * 128));
	}
	if (pOptions->idxmem) {
		pOptions->bufs = (LONG) (((LONG8) pOptions->idxmem * 1024 * 1024) /
			(pOptions->pagesize * 128));
	}
	if (INTISAMX((COUNT) pOptions->bufs, 12, pOptions->pagesize, (COUNT) pOptions->dbufs, 0, uid, upw, svn))
	{
		th_printf(proc_id, "\nCould not init (%d,%d)\n", isam_err, isam_fil);
		goto exit_thrd;
	}

#ifdef ctCLIENT
	th_printf(proc_id,"Connected to server.\n");
#else
	th_printf(proc_id,"Initialized c-tree Plus.\n");
#endif

	/* Open data and index files. */
	if ((datno = OPNRFILX(-1, filnamx,
	    (pOptions->exclusive ? ctEXCLUSIVE : ctSHARED) | ctDUPCHANEL, NULL)) == -1) {
		th_printf(proc_id,"Could not open files (%d,%d)\n",
			isam_err, isam_fil);
		if (isam_err == FNOP_ERR)
			th_printf(proc_id, "Have you created the files?\n");
		goto exit_thrd;
	}

	th_printf(proc_id, "Opened data and index files in %s mode.\n",
		pOptions->exclusive ? "exclusive" : "shared");

#ifdef TRANPROC
	if (filmod == (COUNT)-1)
		filmod = (COUNT)GETFIL(datno, FILMOD);

	if ((COUNT)(filmod & LOGFIL))
	{
		th_printf(proc_id, "Using full transaction processing.\n");
		mode = 'T';
	}
	else if ((COUNT)(filmod & PREIMG))
	{
		th_printf(proc_id, "Using no log transaction processing.\n");
		mode = 't';
	}
	else
	{
		th_printf(proc_id, "Using no transaction processing.\n");
		mode = 'N';
	}
#else
	th_printf(proc_id, "Using no transaction processing.\n");
#endif

	lstart = sysdate();
	ctrt_asctime_r(&ct_tm, timebuf);
	th_printf(proc_id,"Start time: %s\n", timebuf);
#ifdef ctLOGTIMESTODISK
	fprintf(fpTIMES,"%s  Start time   : %s",th_str,timebuf);
#endif

	if (action == ACTION_OPENCLOSE)
	{
		COUNT	filmod = ctSHARED | ctDUPCHANEL;

		printf("Opening and closing the files...\n");
		for (itrial = 1; itrial <= trials; itrial++)
		{
			CLRFIL(datno);
			if (filmod & ctDUPCHANEL)
				filmod &= ~ctDUPCHANEL;
			else
				filmod |= ctDUPCHANEL;
			/* Open data and index files. */
			if ((datno = OPNRFILX(-1, filnamx,
			    filmod, NULL)) == -1) {
				th_printf(proc_id,"Could not open files (%d,%d)\n",
					isam_err, isam_fil);
				if (isam_err == FNOP_ERR)
					th_printf(proc_id, "Have you created the files?\n");
				goto exit_thrd;
			}
		}
		goto exit_thrd;
	}

	if (action == ACTION_ADDKEY)
	{
		TEXT	target[20];
		LONG	recbyt;

		printf("Adding keys to member index...\n");

		key = (FILNO) (datno + 2);
		recbyt = LSTKEY(key,target) + 1;
		memset(target,'a',sizeof(target));
		for (itrial = 1; itrial <= trials; itrial++,recbyt++)
		{
			status = ADDKEY(key,target,recbyt,REGADD);
			if (status) {
				if (status == KDUP_ERR) {
					recbyt = LSTKEY(key,target) + 1;
					continue;
				}
				th_printf(proc_id,"\n (%ld:%d)",itrial,status);
				break;
			}
		}
		goto exit_thrd;
	}

	/* Run cttestfunc() routine.*******************************************/
	if (action == ACTION_TESTFUNC)
	{
		LONG8	tbas, tstart, tstop = 0;
		LONG	elapsed;
#ifdef TRANPROC
		if (mode != 'N')
		{
			ctrt_hrtimbas(tbas);
			ctrt_hrtimer(tstart);
			for (itrial = 1; itrial <= trials; itrial++)
			{
				status = cttestfunc();
				if (status) {
					th_printf(proc_id,"\n (%ld:%d)",itrial,status);
					break;
				}

				/* assignments intended */
				status = (tbeg(&tlen,&trst) || cttestfunc());
				if (status)
					th_printf(proc_id,"\n (%ld:%d)\n",itrial,status);
				status = tend(proc_id,&tlen,status,&trst,&tcnt,1);
				if (status)
					th_printf(proc_id,"\n (%ldT%d)\n",itrial,status);
			}
		}
		else
#endif
		{
			ctrt_hrtimbas(tbas);
			ctrt_hrtimer(tstart);
			for (itrial = 1; itrial <= trials; itrial++)
			{
				status = cttestfunc();
				if (status) {
					th_printf(proc_id,"\n (%ld:%d)",itrial,status);
					break;
				}
			}
		}
		ctrt_hrtimer(tstop);
		if (tstop) {
			elapsed = (LONG) ((tstop - tstart) * 1000 / tbas);
			th_printf(proc_id,"Elapsed time: %d msec.\n", elapsed);
			th_printf(proc_id,"%d calls/sec.\n",
				(LONG) ((LONG8)trials * 1000 / elapsed));
		}
		goto exit_thrd;
	}
#ifndef ctBNDSRVR
	/* Run CTUSERX() routine.*******************************************/
	else if (action == ACTION_CTUSERX)
	{
#if ctVER_GE(10,0)
		LONG8	tbas, tstart, tstop = 0;
		LONG	elapsed;
		pTEXT	inbuf, outbuf;
		VRLEN	outsiz;

		if (inbufsiz)
			inbuf = mballc(1, inbufsiz);
		else
			inbuf = NULL;
		if (outbufsiz)
			outbuf = mballc(1, outbufsiz);
		else
			outbuf = NULL;

		ctrt_hrtimbas(tbas);
		ctrt_hrtimer(tstart);
		for (itrial = 1; itrial <= trials; itrial++)
		{
			outsiz = outbufsiz;
			status = CTUSERX(">LOCAL>", inbuf, inbufsiz, outbuf,
				&outsiz);
			if (status) {
				th_printf(proc_id,"\n (%ld:%d)",itrial,status);
				break;
			}
		}

		ctrt_hrtimer(tstop);
		if (tstop) {
			elapsed = (LONG) ((tstop - tstart) * 1000 / tbas);
			if (!elapsed)
				elapsed = 1;
			ctrt_printf("Elapsed time: %d msec.\n", elapsed);
			ctrt_printf("%d calls/sec.\n", trials / elapsed * 1000);
		}
#endif
		goto exit_thrd;
	}
#endif /* ~ctBNDSRVR */

	/* Add data. **********************************************************/
	if (action == ACTION_ADD)
	{
		th_printf(proc_id,"Adding records...\n");

		datblk.dlfg = 0;
		for (itrial = 1; itrial <= trials; itrial++)
		{
			setval(datblk.unqu,NUML,NUML,27);
			setval(datblk.name,8,NAML,16);
			setval(datblk.clss,CLSL,CLSL,4);
#ifdef TRANPROC
			if (mode != 'N')
			{
				/* assignments intended */
				if ((status=tbeg(&tlen,&trst)) ||
				    (status=(pOptions->vlen ? ADDVREC(datno,&datblk,sizeof(datblk)) : ADDREC(datno,&datblk))))
					th_printf(proc_id,"\n (%ld:%d:%.6s)\n",
						itrial,status,datblk.unqu);
				/* Stop in case of unexpected errors */
				if (status == BNOD_ERR || status == BIDX_ERR || status == DLOK_ERR)
					break;
				status = tend(proc_id,&tlen,status,&trst,&tcnt,1);
				if (status)
					th_printf(proc_id,"\n (%ldT%d)\n",itrial,status);
			}
			else
#endif
			{
		                /* assignments intended */
				if ((status = LKISAM(ctENABLE)) ||
				    (status=(pOptions->vlen ? ADDVREC(datno,&datblk,sizeof(datblk)) : ADDREC(datno,&datblk))))
					th_printf(proc_id,"\n (%ld:%d:%.6s)\n",
						itrial,status,datblk.unqu);
				/* Stop in case of unexpected errors */
				if (status == BNOD_ERR || status == BIDX_ERR || status == DLOK_ERR)
					break;
				++tcnt;
				if (!quiet && !(itrial % 100))
					th_printf(proc_id, "\r  TT %d", tcnt);

				/* assignment intended */
				if (status = LKISAM(ctFREE))
					th_printf(proc_id,"\n (%ldL%d)\n",itrial,status);
			}
			if (status == ARQS_ERR || status == ARSP_ERR ||
			    status == TUSR_ERR || status == SHUT_ERR ||
			    status == NINT_ERR)
				break;
		}

		goto exit_thrd;
	}

	if (action == ACTION_NEWREC)
	{
		TEXT	target[20];
		LONG	recbyt;

		printf("Allocating new space in file...\n");

		key = (FILNO) (datno + 2);
		recbyt = LSTKEY(key,target) + 1;
		memset(target,'a',sizeof(target));
		for (itrial = 1; itrial <= trials; itrial++,recbyt++)
		{
			LONG recbyt;
			if (pOptions->vlen)
				recbyt = NEWVREC(datno,128);
			else
				recbyt = NEWREC(datno);
			if (!recbyt) {
				status = uerr_cod;
				th_printf(proc_id,"\n (%ld:%d)",itrial,status);
				break;
			}
			if (pOptions->vlen)
				status = RETVREC(datno,recbyt);
			else
				status = RETREC(datno,recbyt);
			if (status) {
				th_printf(proc_id,"\n RETREC (%ld:%d)",itrial,status);
				break;
			}
		}
		goto exit_thrd;
	}

	/* Get, Delete, or Update. ********************************************/
	switch (action)
	{
	case ACTION_GET:
		th_printf(proc_id,"Retrieving records...\n");
		break;

	case ACTION_DELETE:
		th_printf(proc_id,"Deleting records...\n");
		break;

	case ACTION_UPDATE:
		th_printf(proc_id,"Updating records...\n");
		break;
	}
	
	for (itrial = 1; itrial <= trials; itrial++)
	{
		finds = locks = 0;
gfind:
		for (key = 0; key < 30; key++)
			keybuf[key] = 0;
		key = getskey((FILNO)(datno+1),(FILNO)(datno+2));
		switch (key-datno)
		{
		case 2:
			setval(keybuf,NUML,NUML,27);
		        break;
		case 1:
			setval(keybuf,8,NAML,16);
			break;
		}

#ifdef TRANPROC
		if (mode != 'N')
		/* Transaction processing. *******************************************/
		{
			if (tbeg(&tlen,&trst))
			{
				th_printf(proc_id,"\n (%ld:%d)\n",itrial,isam_err);
				continue;
			}
tlock1:
			status = GTEREC(key,keybuf,&datblk);
			if (status != 0)
			{
				if (status == 101 && finds++ < 10)
				{
					TRANABT();
					tlen = 0;
					goto gfind;
				}
				if (status != 42)
					th_printf(proc_id,"\n (%ld:%d:%d:%s)\n",
						itrial,status,key,keybuf);
				if (status == 42)
				{
					if (locks++ < 10)
						goto tlock1;
					else
						th_printf(proc_id,"\n (%ld:%d)\n",itrial,status);
				}

				/* assignment intended */
				if (status = TRANABT())
					th_printf(proc_id,"\n (%ldT%d)",itrial,status);
				tlen = 0;
				continue;
			}

			switch (action)
			{
case ACTION_GET: /* Get. ************************************************************/
			if (!quiet)
			{
			/* Truncate key value for display purposes. */
			if (width >= 6)
				keybuf[width-6] = '\0';
			if (!(itrial % 100))
				th_printf(proc_id,"\r G [%s]", keybuf);
			}
			status = tend(proc_id,&tlen,status,&trst,&tcnt,0);
			if (status)
				th_printf(proc_id,"\n (%ldT%d)",itrial,status);
			break;

case ACTION_DELETE: /* Delete. *********************************************************/
			if (pOptions->vlen && (status = DELVREC(datno)) != 0 ||
			    !pOptions->vlen && (status = DELREC(datno)) != 0)
				th_printf(proc_id," (D%ld:%d)",itrial,status);
			else if (!quiet)
			{
				/* Truncate key value for display purposes. */
				if (width >= 6)
					keybuf[width-6] = '\0';
				if (!(itrial % 100))
					th_printf(proc_id,"\r D [%s]", keybuf);
			}
			status = tend(proc_id,&tlen,status,&trst,&tcnt,-1);
			if (status)
				th_printf(proc_id,"\n (%ldT%d)",itrial,status);
			break;

case ACTION_UPDATE: /* Update. *********************************************************/
			cpybuf(&updblk,&datblk,128);
			/* Choose a key to update. */
			switch (getskey((FILNO)(datno+1),(FILNO)(datno+3))-datno)
			{
		case 2:
			cpybuf(keybuf,datblk.unqu,NUML);
			setval(updblk.unqu,NUML,NUML,27);
			cpybuf(newbuf,updblk.unqu,NUML);
			newbuf[NUML] = '\0';
			break;

		case 1:
			cpybuf(keybuf,datblk.name,NAML);
			setval(updblk.name,8,NAML,16);
			cpybuf(newbuf,updblk.name,NAML);
			newbuf[NAML] = '\0';
			break;

		case 3:
			cpybuf(keybuf,datblk.clss,CLSL);
			setval(updblk.clss,CLSL,CLSL,4);
			cpybuf(newbuf,updblk.clss,CLSL);
			newbuf[CLSL] = '\0';
			break;
			}
			if (pOptions->vlen && (status = RWTVREC(datno,&updblk,sizeof(updblk))) != 0 ||
			    !pOptions->vlen && (status = RWTREC(datno,&updblk)) != 0)
				th_printf(proc_id,"\n (R%ld:%d)",itrial,status);
			else if (!quiet)
			{
				/* Truncate key value for display purposes. */
				if (width >= 6)
					newbuf[width-6] = '\0';
				if (!(itrial % 100))
					th_printf(proc_id,"\r U [%s]", newbuf);
			}

			status = tend(proc_id,&tlen,status,&trst,&tcnt,0);
			if (status)
				th_printf(proc_id,"\n (%ldT%d)",itrial,status);
			} /* end switch */
		}
		else
#endif
		/* No transaction processing. ****************************************/
		{
			if (LKISAM(ctENABLE))
			{
				th_printf(proc_id,"\n (%ld:%d)\n",itrial,isam_err);
				continue;
			}
tlock0:
			if ((status = GTEREC(key,keybuf,&datblk)) != 0)
			{
				if (status == 101 && finds++ < 10)
				{
					LKISAM(ctFREE);
					goto gfind;
				}
				if (status != 42 && status != 101)
					th_printf(proc_id,"\n (%ld:%d:%d:%s)\n",
						itrial,status,key,keybuf);
				if (status == 42)
					goto tlock0;
				LKISAM(ctFREE);
				continue;
			}

			switch (action)
			{
case ACTION_GET: /* Get. ************************************************************/
			if (!quiet)
			{
			/* Truncate key value for display purposes. */
			if (width >= 6)
				keybuf[width-6] = '\0';
			if (!(itrial % 100))
				th_printf(proc_id,"\r G [%s]", keybuf);
			}
			LKISAM(ctFREE);
			break;

case ACTION_DELETE: /* Delete. *********************************************************/
			if (pOptions->vlen && (status = DELVREC(datno)) != 0 ||
			    !pOptions->vlen && (status = DELREC(datno)) != 0)
				th_printf(proc_id,"\n (%ld:%d)\n",itrial,status);
			else if (!quiet)
			{
				/* Truncate key value for display purposes. */
				if (width >= 6)
					keybuf[width-6] = '\0';
				if (!(itrial % 100))
					th_printf(proc_id,"\r D [%s]", keybuf);
			}
			LKISAM(ctFREE);
			break;

case ACTION_UPDATE: /* Update. *********************************************************/
			cpybuf(&updblk,&datblk,128);
			/* Choose a key to update. */
			switch (getskey((FILNO)(datno+1),(FILNO)(datno+3))-datno)
			{
		case 2:
/*
			cpybuf(keybuf,datblk.unqu,NUML);
			setval(updblk.unqu,NUML,NUML,27);
			cpybuf(newbuf,updblk.unqu,NUML);
			newbuf[NUML] = '\0';
			break;
*/
		case 1:
			cpybuf(keybuf,datblk.name,NAML);
			setval(updblk.name,8,NAML,16);
			cpybuf(newbuf,updblk.name,NAML);
			newbuf[NAML] = '\0';
			break;
		case 3:
			cpybuf(keybuf,datblk.clss,CLSL);
			setval(updblk.clss,CLSL,CLSL,4);
			cpybuf(newbuf,updblk.clss,CLSL);
			newbuf[CLSL] = '\0';
			break;
			}
			if (pOptions->vlen && (status = RWTVREC(datno,&updblk,sizeof(updblk))) != 0 ||
			    !pOptions->vlen && (status = RWTREC(datno,&updblk)) != 0)
				th_printf(proc_id,"\n (%ld:%d)\n",itrial,status);
			else if (!quiet)
			{
				/* Truncate key value for display purposes. */
				if (width >= 6)
					newbuf[width-6] = '\0';
				if (!(itrial % 100))
					th_printf(proc_id,"\r U [%s]", newbuf);
			}
			LKISAM(ctFREE);
			} /* end switch */
		}
		if (status == ARQS_ERR || status == ARSP_ERR ||
		    status == TUSR_ERR || status == SHUT_ERR ||
		    status == NINT_ERR)
			break;
	}

exit_thrd:
	if (lstart)
	{
		lstop = sysdate();
		ctrt_asctime_r(&ct_tm, timebuf);
		th_printf(proc_id,"\nEnd time: %s", timebuf);
#ifdef ctLOGTIMESTODISK
		fprintf(fpTIMES,"%s  End time     : %s ",th_str,timebuf);
#endif
		rate(proc_id,lstop,lstart,trials,th_str);
		th_printf(proc_id, "***** Successful Run\n\n");
	}

	STPUSR();

	sprintf(qmsg, "Finished.");

	return(0);  
} /* tcode() */


/* ************************************************************************* */
/* ************************************************************************* */

DREC	dodablk;	/* Data record buffer.	*/

DATOBJ doda[] = {	/* Field definitions for data record. */
		{"Dlfg", (pTEXT) &dodablk.dlfg, CT_INT2},
		{"Unqu", (pTEXT)  dodablk.unqu, CT_FSTRING, NUML},
		{"Sern", (pTEXT) &dodablk.sern, CT_INT4},
		{"Dlen", (pTEXT) &dodablk.dlen, CT_INT2},
		{"Name", (pTEXT)  dodablk.name, CT_FSTRING, NAML},
		{"Clss", (pTEXT)  dodablk.clss, CT_FSTRING, CLSL},
		{"Grbg", (pTEXT)  dodablk.grbg, CT_FSTRING, PADG}
	};

ISEG segments[] = {	/* Key segment definitions. */
		{14,16,0},
		{ 2, 6,0},
		{38, 2,0},
#ifdef ctAppNOTIFY_LOCAL_COPY
		{ 8, 4,1}
#else
		{ 8, 4,3}
#endif
	};

IIDX ndxs[] = {		/* Index definitions. */
		{20,COL_BOTH,1,1,32,1, segments},
		{10, 0,1,0, 0,1,&segments[1]},
#ifdef ctAppNOTIFY
		{ 6, 0,0,0, 0,2,&segments[2]}
#else
		{10, 0,1,1,32,2,&segments[2]}
#endif
	};

IFIL markdata = {	/* Data and index file definitions. */
		"mark",
		-1,			/* file #        */
		128,			/* record length */
		8192,			/* dat xtdsiz	 */
		ctSHARED | ctPERMANENT,	/* dat file mode */
		3,			/* nbr of idxs	 */
		0,			/* idx xtdsiz	 */
		ctSHARED | ctPERMANENT,	/* idx file mode */
		ndxs			/* idx defs	 */
	};

#ifdef PROTOTYPE
pTEXT getactdesc (NINT action)
#else
pTEXT getactdesc (action)
NINT	action;
#endif
{
	switch(action) {
		case ACTION_ADD: return("add");
		case ACTION_DELETE: return("delete");
		case ACTION_GET: return("get");
		case ACTION_STOP: return("stop");
		case ACTION_TESTFUNC: return("testfunc");
		case ACTION_UPDATE: return("update");
		case ACTION_CTUSERX: return("ctuserx");
		case ACTION_NEWREC: return("newrec");
		case ACTION_OPENCLOSE: return("openclose");
		case ACTION_ADDKEY: return("addkey");
		default: return("unknown");
	}
}

#ifdef PROTOTYPE
NINT getactioncode (pTEXT tp,pAPPOPTS pOptions)
#else
NINT getactioncode (tp,pOptions)
pTEXT	tp;
pAPPOPTS pOptions;
#endif
{
	NINT	rc = 0;
	pTEXT	sp = tp;

	switch (toupper(*++tp)) {
case 'A':	pOptions->action = ACTION_ADD;
		break;
case 'D':	pOptions->action = ACTION_DELETE;
		break;
case 'G':	pOptions->action = ACTION_GET;
		break;
case 'U':	pOptions->action = ACTION_UPDATE;
		break;
case 'T':	pOptions->action = ACTION_TESTFUNC;
		break;
case 'X':	pOptions->action = ACTION_CTUSERX;
		break;
case 'S':	pOptions->action = ACTION_STOP;
		break;
case ':':
		for (sp=tp; *sp; sp++) {
			*sp = toupper(*sp);
		}
		if (!strcmp(tp,":NEWREC")) {
			pOptions->action = ACTION_NEWREC;
			break;
		} else if (!strcmp(tp,":ADDKEY")) {
			pOptions->action = ACTION_ADDKEY;
			break;
		} else if (!strcmp(tp,":OPENCLOSE")) {
			pOptions->action = ACTION_OPENCLOSE;
			break;
		}
		break;
default:
		rc = 1;
		break;
	}
	return(rc);
}
/*
 * appGetArgs: Process command-line arguments or prompt user.
 */
#ifdef PROTOTYPE
NINT appGetArgs(NINT argc, ppTEXT argv, pAPPOPTS pOptions)
#else
NINT appGetArgs(argc, argv, pOptions)
NINT		argc;
ppTEXT		argv;
pAPPOPTS	pOptions;
#endif
{
	pTEXT	tp;		/* Pointer to current command line argument. */
	NINT	rc;		/* Return code.		*/
	XCREblk xcreblk[2];

	pOptions->svn = mballc(1,(UINT)MAX_NAME);
	pOptions->uid = mballc(1,(UINT)MAX_NAME);
	pOptions->upw = mballc(1,(UINT)MAX_NAME);
	pOptions->enc = mballc(1,IDZ);

	/* DEFAULTS */
	pOptions->action   = ACTION_GET;
	pOptions->filestat = 'n';
	pOptions->mode     = 'N';
	pOptions->trials   = 100L;
	ctrt_strcpy(pOptions->svn, SVN_DEFAULT);
	ctrt_strcpy(pOptions->uid, UID_DEFAULT);
	ctrt_strcpy(pOptions->upw, UPW_DEFAULT);
	pOptions->enc[0] = '\0';
	pOptions->filnam = "";
	pOptions->filnamx[0] = '\0';
	pOptions->compress = NO;
#ifdef ctFeatVARLENnodefmt
	pOptions->vlennod = NO;
	pOptions->trnmrkopt = NO;
	pOptions->atotrnmod = NO;
	pOptions->cmpoff = NO;
#endif
	pOptions->datmem = 0;
	pOptions->idxmem = 0;
	pOptions->huge_ctfile	   = NO;
	pOptions->segm	   = NO;
	pOptions->vlen	   = NO;
	pOptions->noxhdr   = NO;
	pOptions->seed     = 1;
	pOptions->trnlen   = 1;
	pOptions->maxfiles = 0;
	pOptions->quiet    = NO;
	pOptions->exclusive = NO;
	pOptions->pagesize = 8192;
	pOptions->bufs = 16 * pOptions->pagesize;
	pOptions->dbufs = 16 * pOptions->pagesize;

	if (argc <= 1) /* if command line args not entered */
	{
		appDescribe();
		goto err_ret;
	}
	else
	{
	        /* COMMAND LINE */
	        while (--argc > 0)
		{
			tp = *++argv; 
			switch (*tp)
			{
case 'A':
case 'a':		/* Action. */
			getactioncode(tp,pOptions);
			/*
			** CTUSERX() test option. The option format is:
			**
			** aX(i,o) where i specifies the CTUSERX() input buffer
			** size and o specifies the CTUSERX() output buffer
			** size in bytes.
			*/
			if (pOptions->action == ACTION_CTUSERX) {
#ifdef ctBNDSRVR
				ctrt_printf("This operational model does not support the CTUSERX() option.\n");
				goto err_ret;
#else
				pTEXT	sp;

				sp = tp + 1;
				if (*sp == '(') {
					++sp;
					inbufsiz = atoi(sp);
					while (*sp && *sp != ',')
						++sp;
					if (*sp == ',') {
						++sp;
						outbufsiz = atoi(sp);
					}
				}
#endif
			}
			break;
case 'E':
case 'e':		/* Encrypt files. */
			strncpy(pOptions->enc, tp+1, IDZ);
			break;
case 'I':
case 'i':
			switch (toupper(*(tp + 1))) {
		case 'C':
#ifdef ctCMPREC
				pOptions->compress = YES;
				break;
#else
				ctrt_printf("The compression option is not supported; recompile with #define ctCMPREC\n");
				goto err_ret;
#endif
		case 'H':	pOptions->huge_ctfile = YES;
				if (pOptions->noxhdr) {
					printf("Error: The huge_ctfile option is not compatible with the no extended header option.\n");
					goto err_ret;
				}
				break;
		case 'S':	pOptions->segm = YES;
				if (pOptions->noxhdr) {
					printf("Error: The segmented option is not compatible with the no extended header option.\n");
					goto err_ret;
				}
				break;
		case 'N':	pOptions->noxhdr = YES;
				if (pOptions->huge_ctfile || pOptions->segm) {
					printf("Error: The no extended header option is not compatible with huge_ctfile and segmented options.\n");
					goto err_ret;
				}
				break;
		case 'V':	pOptions->vlen = YES;
				break;
			}
			break;
case 'F':
case 'f':		/* Create files. */
			pOptions->filestat = *++tp;
			break;
#ifdef TRANPROC
case 'G':
case 'g':		/* Transaction aborts. */
			pOptions->trnlen = atoi(++tp);
			break;
#endif
case 'H':
case 'h':
			pOptions->filnam = ++tp;
			sprintf(pOptions->filnamx,"%s.dat",pOptions->filnam);
			break;
case 'M':
case 'm':		/* Transaction mode. */
			pOptions->mode = *++tp;
			if (pOptions->mode == 'T') /* mT */
			{
				markdata.dfilmod |= TRNLOG;
				markdata.ifilmod |= TRNLOG;
#ifdef TRANPROC
				if (*(tp + 1) == 'a') /* mTa */
#endif
				{
					pOptions->atotrnmod = YES;
				}
			}
			else if (pOptions->mode == 't') /* mt */
			{
				markdata.dfilmod |= PREIMG;
				markdata.ifilmod |= PREIMG;
#ifdef TRANPROC
				if (*(tp + 1) == 'a') /* mta */
#endif
				{
					pOptions->atotrnmod = YES;
				}
			}
#ifdef ctFeatVARLENnodefmt
			else if (pOptions->mode == 'x') /* mx */
				pOptions->vlennod = YES;
			else if (pOptions->mode == 'm') /* mm */
				pOptions->trnmrkopt = YES;
			else if (pOptions->mode == 'c') /* mc */
				pOptions->cmpoff = YES;
#endif
			else if (pOptions->mode == 'd') /* md */
				pOptions->datmem = atoi(tp + 1);
			else if (pOptions->mode == 'i') /* mi */
				pOptions->idxmem = atoi(tp + 1);
			break;
case 'N':
case 'n':		/* Number of trials. */
			pOptions->trials = atol(++tp);
			break;
case 'O':
case 'o':
			switch (toupper(*(tp + 1))) {
		case 'D': /* data cache size in bytes */
				pOptions->dbufs = atol(tp + 2);
				break;
		case 'I': /* index cache size in bytes */
				pOptions->bufs = atol(tp + 2);
				break;
		case 'P': /* page size in bytes */
				pOptions->pagesize = atoi(tp + 2);
				if (!pOptions->pagesize) {
					printf("Error: Page size must be non-zero.\n");
					goto err_ret;
				}
				break;
		case 'X': /* open files in exclusive mode */
				pOptions->exclusive = YES;
				break;
			}
			break;
case 'P':
case 'p':		/* User password. */
			strncpy(pOptions->upw, tp+1, MAX_NAME);
			break;
case 'Q':
case 'q':		/* quiet mode */
			pOptions->quiet = YES;
			break;
case 'R':
case 'r':		/* Random number seed. */
			pOptions->seed = atoi(++tp);
			break;
case 'S':
case 's':		/* Server name. */
			strncpy(pOptions->svn, tp+1, MAX_NAME);
			break;
case 'U':
case 'u':		/* User name. */
			strncpy(pOptions->uid, tp+1, MAX_NAME);
			break;
case 'X':
case 'x':		/* Maximum number of files. */
			pOptions->maxfiles = atoi(++tp);
			break;
			}
		}
	}  /* end command line */

#ifndef ctCLIENT
	printf("  Page size: %12d bytes\n", pOptions->pagesize);
	printf(" Data cache: %12d bytes\n", pOptions->dbufs);
	printf("Index cache: %12d bytes\n", pOptions->bufs);

	pOptions->bufs /= pOptions->pagesize;
	pOptions->dbufs /= pOptions->pagesize;
	pOptions->pagesize /= 128;

	if (pOptions->bufs > 32767) {
		printf("Maximum number of index buffers is 32767.\n");
		rc = 1;
		goto err_ret;
	}
	if (pOptions->dbufs > 32767) {
		printf("Maximum number of data cache pages is 32767.\n");
		rc = 1;
		goto err_ret;
	}
#endif

	ctrt_printf("\ntrials=%d mode=%c seed=%d action=%s trnlen=%d\n",
		pOptions->trials, pOptions->mode, pOptions->seed,
		getactdesc(pOptions->action), pOptions->trnlen);

	if (!pOptions->filnam[0]) {
		/* File name not specified, so use default. */
		if (pOptions->vlen)
			pOptions->filnam = "markv";
		else
			pOptions->filnam = "mark";
		sprintf(pOptions->filnamx,"%s.dat",pOptions->filnam);
	}
	markdata.pfilnam = pOptions->filnam;

	/* Create data and index files if specified. */
	if (pOptions->filestat == 'c' || pOptions->filestat == 'C')
	{
#if defined(ctCAMOsdk) && !defined(ctCLIENT) && !defined(ctDLLLIB)
		/* request for advanced encryption? */
		if(pOptions->enc[0] && strcmp(pOptions->enc,ctENCR))
			/* initialize advanced encryption */
			cmosdksup=1;
#endif
		if (INTISAMX(16, 12, pOptions->pagesize, 16, 0, pOptions->uid, pOptions->upw, pOptions->svn))
		{
			ctrt_printf("\nCould not init (%d,%d)\n", isam_err, isam_fil);
			goto err_ret;
		}

		/* Attempt to delete existing data and index files. */
		markdata.dfilmod &= ~(ctNONEXCLUSIVE);
		markdata.ifilmod &= ~(ctNONEXCLUSIVE);
		if (OPNRFIL(1,pOptions->filnamx,markdata.dfilmod | ctOPENCRPT) == 1) {
#ifdef TRANPROC
			LONG	flmode2;

			if (((flmode2 = GETFIL(1, FLMODE2)) == -1L) && (rc = uerr_cod)) {
				printf("\nError: Could not check for transaction dependent mode on existing data file: %d\n",
					rc);
				goto err_ret;
			}

			if (flmode2 & ctTRANDEP) {
				TRANBEG(ctTRNLOG | ctENABLE);
			}
#endif
			if (!DELRFIL(1))
				ctrt_printf("\nDeleted existing data and index files.\n");
#ifdef TRANPROC
			if (flmode2 & ctTRANDEP) {
				TRANEND(ctFREE);
			}
#endif
		}
		markdata.dfilmod |= ctSHARED;
		markdata.ifilmod |= ctSHARED;

		if (pOptions->enc[0]) {
			TEXT	enckey[PWZ+1];

			memset(enckey, 0xbf, PWZ);
			enckey[PWZ] = '\0';
			if ((rc = ctSETENCRYPT(pOptions->enc, enckey, PWZ))) {
				ctrt_printf("\nCould not enable file encryption: %d\n", rc);
				goto err_ret;
			}

			ctrt_printf("\nSuccessfully enabled encryption for the file.\n");
		}

		memset(xcreblk, 0, sizeof(xcreblk));
		xcreblk[0].x8mode = ctFRC2HDRS;
		xcreblk[1].x8mode = ctFRC2HDRS;
#ifdef ctCMPREC
		if (pOptions->compress) {
			xcreblk[0].splval = ctAugmentedFxd | ctCompressRec;
			markdata.dfilmod |= ctVLENGTH;

			if ((rc = ctSETCOMPRESS(ctCMPRECzlib, 1, NULL, NULL, 0))) {
				ctrt_printf("\nCould not enable compression for %s (%d,%d)\n",
					markdata.pfilnam, isam_err, isam_fil);
				goto err_ret;
			}
		}
#endif
#ifdef ctFeatVARLENnodefmt
		if (pOptions->vlennod) {
			NINT	i;
			for (i=0; i<markdata.dnumidx; i++) {
				markdata.ix[i].ikeytyp |= KTYP_VLENNOD;
				/* turn off prefix compression because the new node format doesn't support it */
				markdata.ix[i].ikeytyp &= ~COL_PREFIX;
				if (pOptions->trnmrkopt)
					markdata.ix[i].ikeytyp |= KTYP_TRNMRKOPT;
				if (pOptions->cmpoff)
					markdata.ix[i].ikeytyp |= KTYP_CMPOFFSET;
			}
		}
#endif
		if (pOptions->noxhdr) {
			xcreblk[0].x8mode = ctNO2HDRS;
			xcreblk[1].x8mode = ctNO2HDRS;
		}
		if (pOptions->segm) {
			xcreblk[0].x8mode = ctSEGAUTO;
			xcreblk[0].segsiz = 1; /* 1 MB */
			xcreblk[0].segmax = 1000;
			xcreblk[1].x8mode = ctSEGAUTO;
			xcreblk[1].segsiz = 1; /* 1MB */
			xcreblk[1].segmax = 1000;
		}
		if (pOptions->huge_ctfile) {
			xcreblk[0].x8mode |= ctFILEPOS8;
			xcreblk[1].x8mode |= ctFILEPOS8;
			ndxs[0].ikeylen += sizeof(LONG);
			ndxs[1].ikeylen += sizeof(LONG);
#ifndef ctAppNOTIFY
			ndxs[2].ikeylen += sizeof(LONG);
#endif
		}
		if (pOptions->vlen)
			markdata.dfilmod |= ctVLENGTH;
		else
			markdata.dfilmod &= ~ctVLENGTH;
#ifdef QA_TRANRECOV
		xcreblk[0].x8mode |= ctTRANDEP;
		xcreblk[1].x8mode |= ctTRANDEP;
		TRANBEG(ctTRNLOG | ctENABLE);
#endif
		if (pOptions->atotrnmod) {
			xcreblk[0].x8mode |= ctTRANMODE;
			xcreblk[1].x8mode |= ctTRANMODE;
		}
		/* Create new data and index files. */
		rc = CREIFILX8(&markdata, NULL, NULL, 0L, NULL, NULL, xcreblk);
		if (rc)
		{
			ctrt_printf("\nCould not create %s (%d,%d)\n",
				markdata.pfilnam, isam_err, isam_fil);
			goto err_ret;
		}

		if (PUTDODA(markdata.tfilno, doda, (UCOUNT)7))
			ctrt_printf("\nError on PUTDODA (%d)", uerr_cod);
#ifdef QA_TRANRECOV
		TRANEND(ctFREE);
#endif

		STPUSR();
	}

	/* Set globals. */
	mode	= pOptions->mode;
	svn	= pOptions->svn;
	uid	= pOptions->uid;
	upw	= pOptions->upw;
	trnlen	= pOptions->trnlen;
	quiet	= pOptions->quiet;
	seed	= pOptions->seed;
	action	= pOptions->action;
#ifdef TRANPROC
	filmod  = (COUNT)-1;
#endif

	return (0);

err_ret:
	return (1);
} /* appGetArgs() */


/* ************************************************************************* */
/* ************************************************************************* */

/* end ctstap.h */
