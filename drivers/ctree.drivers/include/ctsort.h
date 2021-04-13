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

#ifndef ctSORTH
#define ctSORTH

#ifndef MAX_HANDLES
#define MAX_HANDLES 500 /* this is the maximum number of file handles */
			/* the sort will try to allocate min=3 the more */
			/* the better.  if it can't get this many it */
			/* use what it can get (min 3) */
#endif

#ifndef MAX_K_TO_USE
/* Max number of kilobytes the sort will try to allocate. The more the better.
** If it can't get this much it will use less */
#ifdef ctFeatV11SERVERdefaults
#define MAX_K_TO_USE 100000
#else
#define MAX_K_TO_USE 100000
#endif
#endif

#define MAX_INT_VALUE 65000 /*max value that can be held in an integer */
#define MAX_CTREE_IO_SIZE (64 * 1024 * 1024)  /* limited by ictio81 to 2GB-1 */
#ifndef WORK_DRIVE_OR_PATH
#define WORK_DRIVE_OR_PATH (ct_tmppth!=NULL)?ct_tmppth:""
#endif

#define SORT_SGLOBV	1
#define SORT_SRTSTT	2

#define SORT_COMPLETED 1

/* refine sort work file generation in order to ensure that each process and thread uses a unique sort work file name */
#define CTSORTWORK_UNIQUE_FILENAME

/* Structure that maps global variables */
typedef struct globalv {
#ifdef ctFeatRBLSORT
	LONG	gvtype;		/* sort method indicator: SORT_SGLOBV */
#endif
#ifdef ctHUGEFILE
#ifdef ctHUGEFILEsegm
	LONG	segmax;
#endif
	LONG	outpos2;
	LONG	wf_pos2[MAX_HANDLES];
	LONG	srcsiz2;
#endif
	LONG	outpos1;	/* file position */
	LONG	wf_pos1[MAX_HANDLES];/* file position */
	LONG	srcsiz1;	/* measure of total bytes to sort */
	ppUTEXT ptr_area_p;	/* pointer to pointer area */
	pUTEXT 	out_buf;	/* ptr to output buffer */
	pUTEXT 	data_area[MAX_HANDLES];/* ptrs to data areas */
	pUTEXT 	in_buf;		/* address of current input buffer */
	pUTEXT 	m_ptr[MAX_HANDLES];/* pointers to cur rec in merge buf */
	UINT	last_rec_given;	/* last record given by givrec */
	NINT	last_buf;	/* merge buffer assignment */
	NINT	last_buf_moved;	/* last buffer moved from */
#ifdef ctFeatREBUILD_OPT
	ULONG8	next_ptr;  	/* next pointer number to be used */
	ULONG8	bytes_in_buf;	/* number of bytes in data buf */
	ULONG8	cur_data_area;	/* number of current data area */
	ULONG8	data_area_num;	/* number of data areas allocated */
	ULONG8	data_area_size; /* data area size in bytes */
	ULONG	first_mergefile;/* number of first file to merge */
	ULONG8	m_bytes_in_buf[MAX_HANDLES];/* num of bytes in each merge buf */
	ULONG8	num_ptrs;  	/* number of pointers that can be held */
	ULONG	number_handles; /* number of handles available */
	ULONG8	out_buf_cur_off;/* current offset into output buffer */
	ULONG8	out_buf_size;	/* output buffer size in bytes */
	ULONG8  keys_in;	/* actual keys added for sorting (ctsadd) */
	ULONG8  keys_out;	/* actual sorted keys read (ctsval) */
#else
	UCOUNT	next_ptr;  	/* next pointer number to be used */
	UCOUNT	bytes_in_buf;	/* number of bytes in data buf */
	UCOUNT	cur_data_area;	/* number of current data area */
	UCOUNT	data_area_num;	/* number of data areas allocated */
	UCOUNT	data_area_size; /* data area size in bytes */
	UCOUNT	first_mergefile;/* number of first file to merge */
	UCOUNT	m_bytes_in_buf[MAX_HANDLES];/* num of bytes in each merge buf */
	UCOUNT	num_ptrs;  	/* number of pointers that can be held */
	UCOUNT	number_handles; /* number of handles available */
	UCOUNT	out_buf_cur_off;/* current offset into output buffer */
	UCOUNT	out_buf_size;	/* output buffer size in bytes */
#endif
	UCOUNT	recl;  		/* record length */
	UCOUNT	return_code;  	/* main return code */
	UCOUNT	wf_num;		/* num of current workfile (rel 1) */
	FILNO	outnum;
	FILNO   wfnum[MAX_HANDLES];	/* ctree fcb's */
#ifdef CTSORTWORK_UNIQUE_FILENAME
#define WF_ROOT_LEN (2 /* sw */ + 7 /* c-tree task id in hex */ + \
		9 /* process id in hex */ + 9 /* system time in hex */ + 1 /* . */)
#else
#define WF_ROOT_LEN (2 /* sw */ + 6 /* timestamp/task id */ + 1 /* . */)
#endif
	UTEXT 	wf_root[WF_ROOT_LEN + 4];	/* init sets to "swtttttt.00 z"  */
	TEXT 	filename_hold[MAX_NAME];/* hold area for filename */
	UTEXT 	m_eof[MAX_HANDLES];/* eof indicators */
	UTEXT 	givrec_subsequent;/* indicates if subsequent givrec */
	UTEXT 	in_memory_sort;	  /* indicates if in_memory sort */
	UTEXT 	m_intermediate;	  /* intermediate merge indicator */
	UTEXT 	merge1_subsequent;/* indicates subsequent merge1 called */
	UTEXT	no_more_recs;  	/* indicates if all recs given */
	UTEXT 	sinit_done;	/* flag indicating if sinit done */
	UTEXT 	sreturn_started;/* indicates if return phase started */
#ifdef ctFeatREBUILD_OPT
#ifdef ctHUGEFILE
	LONG8	nument;	/* indicates the number of keys (8-byte) */
#else
	ULONG	nument;	/* indicates the number of keys (4-byte) */
#endif
#endif /* ctFeatREBUILD_OPT */
	} SGLOBV;
typedef SGLOBV ctMEM *	pSGLOBV;

#ifdef ctFeatREBUILD_OPT
extern pSGLOBV ctsinit(NINT rec_size,NINT max_hndl,pCTFILE dnum,NINT sorttype);
#else
extern pSGLOBV ctsinit(NINT rec_size,NINT max_hndl,pLhw LONG size);
#endif
extern NINT ctsadd(pSGLOBV gv,pVOID rec_area);
extern NINT ctsval(pSGLOBV gv,pVOID rec_area);
extern NINT ctsabort(pSGLOBV gv);

#endif /* ctSORTH */

/* end of ctsort.h */
