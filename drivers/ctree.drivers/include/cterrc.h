/** @file cterrc.h */
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
/** @version Version 11 */
#ifndef ctERRCH
#define ctERRCH

		/* USER ERROR CODES */
#ifdef 	NO_ERROR
#undef  NO_ERROR
#endif
#define NO_ERROR	0

#define	KDUP_ERR	2	/**< Key value already exists */
#define	KMAT_ERR	3	/**< Could not delete since pntr's don't match */
#define	KDEL_ERR	4	/**< Could not find key to delete */
#define	KBLD_ERR	5	/**< Cannot call delete w/o verification with  */
				/**< duplicate keys */
#define BJMP_ERR	6	/**< c-tree(...) jump table error */
#define TUSR_ERR	7	/**< Terminate user */

#define FCNF_COD	-8	/**< sysiocod value when FNOP_ERR caused by
				   conflicting open requests (server) */
#define FDEV_COD	-9	/**< sysiocod value when FNOP_ERR, DCRAT_ERR or
				   KCRAT_ERR caused by device access error */

#define SPAC_ERR	10	/**< INTREE parameters require too much space */
#define SPRM_ERR	11	/**< Bad INTREE parameters */
#define FNOP_ERR	12	/**< Could not open file: not there or locked */
#define	FUNK_ERR	13	/**< Unknown file type */
#define FCRP_ERR	14	/**< File corrupt at open */
#define FCMP_ERR	15	/**< File has been compacted */
#define KCRAT_ERR	16	/**< Could not create index file */
#define DCRAT_ERR	17	/**< Could not create data file */
#define KOPN_ERR	18	/**< Tried to create existing index file */
#define DOPN_ERR	19	/**< Tried to create existing data file */
#define KMIN_ERR	20	/**< Key length too large for node size */
#define DREC_ERR	21	/**< Record length too small */
#define FNUM_ERR	22	/**< File number out of range */
#define KMEM_ERR	23	/**< Illegal index member info */
#define FCLS_ERR	24	/**< Could not close file */
#define KLNK_ERR	25	/**< Bad link in deleted node list. REBUILD */
#define FACS_ERR	26	/**< File number not active */
#define LBOF_ERR	27	/**< drn before beginning of data records */
#define ZDRN_ERR	28	/**< Zero drn in ADDKEY */
#define ZREC_ERR	29	/**< Zero drn in data file routine */
#define LEOF_ERR	30	/**< drn exceeds logical end of file */
#define DELFLG_ERR	31	/**< Flag not set on record in delete chain */
#define	DDRN_ERR	32	/**< Attempt to delete record twice in a row */
#define DNUL_ERR	33	/**< Attempt to use NULL ptr in read/write */
#define PRDS_ERR	34	/**< Predecessor repeat attempts exhausted */
#define SEEK_ERR	35	/**< Seek error:  check sysiocod value  */
#define READ_ERR	36	/**< Read error:  check sysiocod error  */
#define WRITE_ERR	37	/**< Write error: check sysiocod error */
#define	VRTO_ERR	38	/**< Could not convert virtual open to actual */
#define FULL_ERR	39	/**< No more records available */
#define KSIZ_ERR	40	/**< Index node size too large */
#define UDLK_ERR	41	/**< Could not unlock data record */
#define DLOK_ERR	42	/**< Could not obtain data record lock */
#define FVER_ERR	43	/**< Version incompatibility */
#define OSRL_ERR	44	/**< Data file serial number overflow */
#define KLEN_ERR	45	/**< Key length exceeds MAXLEN parameter */
#define	FUSE_ERR	46	/**< File number already in use */
#define FINT_ERR	47	/**< c-tree has not been initialized */
#define FMOD_ERR	48	/**< Operation incompatible with type of file */
#define	FSAV_ERR	49	/**< Could not save file */
#define LNOD_ERR	50	/**< Could not lock node */
#define UNOD_ERR	51	/**< Could not unlock node */
#define KTYP_ERR	52	/**< Variable length keys disabled OR invalid key type */
#define FTYP_ERR	53	/**< File mode inconsistent with c-tree config  */
#define REDF_ERR	54	/**< Attempt to write a read only file */
#define DLTF_ERR	55	/**< File deletion failed */
#define DLTP_ERR	56	/**< File must be opened exclusive for delete */
#define DADV_ERR	57	/**< Proper lock is not held (ctCHECKLOCK/READ) */
#define KLOD_ERR	58	/**< LOADKEY called with incorrect key number.
				   You cannot continue */
#define KLOR_ERR	59	/**< LOADKEY called with key out of order
				   You may skip this key & continue */
#define KFRC_ERR	60	/**< Percent out of range */
#define CTNL_ERR	61	/**< NULL fcb detected during I/O */
#define LERR_ERR	62	/**< File must be opened exclusively */
#define RSER_ERR	63	/**< Start file / log file serial number error */
#define RLEN_ERR	64	/**< Checkpoint past end of log file */
#define RMEM_ERR	65	/**< Not enough memory during tran processing */
#define RCHK_ERR	66	/**< Log file entry failed to find checkpoint */
#define RENF_ERR	67	/**< Could not rename file */
#define LALC_ERR	68	/**< Could not allocate memory for control list */
#define BNOD_ERR	69	/**< Node does not belong to index */
#define TEXS_ERR	70	/**< Transaction already pending */
#define TNON_ERR	71	/**< No active transaction */
#define TSHD_ERR	72	/**< No space for shadow buffer */
#define TLOG_ERR	73	/**< ctLOGFIL encountered during shadow only */
#define TRAC_ERR	74	/**< Recovery: two active tran for user */
#define TROW_ERR	75	/**< Recovery: bad tran owner */
#define TBAD_ERR	76	/**< Recovery: bad tran type */
#define TRNM_ERR	77	/**< Recovery: file name too long */
#define TABN_ERR	78	/**< Transaction abandoned: too many log extents
				   or dynamic dump wait exhausted */
#define FLOG_ERR	79	/**< Could not log file opn/cre/cls/del */
#define BKEY_ERR	80	/**< NULL target or bad keyno */
#define ATRN_ERR	81	/**< Transaction allocation error */
#define UALC_ERR	82	/**< User allocation error */
#define IALC_ERR	83	/**< ISAM allocation error */
#define MUSR_ERR	84	/**< Maximum users exceeded */
#define LUPD_ERR	85	/**< Reduce lock to read lock after update */
#define DEAD_ERR	86	/**< Dead lock detected */
#define QIET_ERR	87	/**< System not quiet: files in use */
#define LMEM_ERR	88	/**< Linked list memory allocation error */
#define TMEM_ERR	89	/**< Memory allocation during tran processing */
#define NQUE_ERR	90	/**< Could not create queue */
#define QWRT_ERR	91	/**< Queue write error */
#define QMRT_ERR	92	/**< Queue memory error during write */
#define QRED_ERR	93	/**< Queue read error */
#define PNDG_ERR	94	/**< Pending error: cannot save or commit tran */
#define STSK_ERR	95	/**< Could not start task */
#define LOPN_ERR	96	/**< Start-file/log open error */
#define SUSR_ERR	97	/**< Bad user handle */
#define BTMD_ERR	98	/**< Bad transaction mode */
#define TTYP_ERR	99	/**< Transaction type / filmod conflict */

#define	ICUR_ERR	100	/**< No current record for isam datno */
#define	INOT_ERR	101	/**< Could not find isam keyno request */
#define INOD_ERR	102	/**< Could not open ISAM parameter file */
#define IGIN_ERR	103	/**< Could not read first 5 parameters in ISAM
				   parameter file */
#define IFIL_ERR	104	/**< Too many files in ISAM parameter file */
#define IUND_ERR	105	/**< Could not undo ISAM update. Rebuild Files */
#define IDRI_ERR	106	/**< Could not read data file record in ISAM
				   parameter file */
#define IDRK_ERR	107	/**< Too many keys for data file in ISAM
				   parameter file */
#define IMKY_ERR	108	/**< Incorrect keyno for index member in
				   parameter file */
#define IKRS_ERR	109	/**< Too many key segments defined in ISAM
				   parameter file */
#define ISRC_ERR	110	/**< Could not read segment record in ISAM
				   parameter file */
#define	IKRI_ERR	111	/**< Could not read index file record in ISAM
				   parameter file */
#define IPND_ERR	112	/**< LKISAM(ctENABLE) found pending locks */
#define INOL_ERR	113	/**< No memory for user lock table */
#define IRED_ERR	114	/**< 1st byte of data record equals delete flag
				   or bad variable length record mark */
#define ISLN_ERR	115	/**< Key segments do not match key length */
#define IMOD_ERR	116	/**< Bad mode parameter */
#define	IMRI_ERR	117	/**< Could not read index member record */
#define SKEY_ERR	118	/**< NXTSET called before FRSSET for keyno */
/* #define SKTY_ERR	119 */	/* FRSSET called for index with wrong keytyp */

#define RRLN_ERR	120	/**< Data record length exceeds rebuild max */
#define KBUF_ERR	121	/**< Tried to update data with ctISAMKBUFhdr on */
#define RMOD_ERR	122	/**< Attempt to change fixed vs variable len */
#define	RVHD_ERR	123	/**< Var length header has bad record mark */
#define INIX_ERR	124	/**< # of indices does not match (OPNIFIL) */
#define IINT_ERR	125	/**< c-tree already initialized */

#define ABDR_ERR	126	/**< Bad directory path get */
#define ARQS_ERR	127	/**< Could not send request */
#define ARSP_ERR	128	/**< Could not receive answer */
#define NINT_ERR	129	/**< c-tree not initialized */
#define AFNM_ERR	130	/**< Empty file name on call to open or create */
#define AFLN_ERR	131	/**< File name length exceeds msg size */
#define ASPC_ERR	132	/**< No room for application message buffer */
#define ASKY_ERR	133	/**< Server is not active */
#define ASID_ERR	134	/**< Could not get servers message id */
#define AAID_ERR	135	/**< Could not allocate application id */
#define AMST_ERR	136	/**< Could not get application msg status */
#define AMQZ_ERR	137	/**< Could not set message appl msg size */
#define AMRD_ERR	138	/**< Could not get rid of application msg */
#define ABNM_ERR	139	/**< Badly formed file name */
#define VMAX_ERR	140	/**< Variable record length too long */
#define AMSG_ERR	141	/**< Required message size exceeds maximum */

#define SMXL_ERR	142	/**< Application MAXLEN > server's MAXLEN */
#define SHND_ERR	143	/**< Communications handler not installed */
#define QMEM_ERR	144	/**< Application could not id output queue */
#define SCSF_ERR	145	/**< Could not find COMM software */
#define	VDLK_ERR	146	/**< Could not update free space info */
#define VDLFLG_ERR	147	/**< Space to be reused is not marked deleted */
#define	VLEN_ERR	148	/**< WRTVREC cannot fit record at recbyt */
#define	VRLN_ERR	149	/**< Varlen less than minimum in ADDVREC or GTVLEN */
#define SHUT_ERR	150	/**< Server is shutting down */
#define STRN_ERR	151	/**< Could not shut down. transactions pending */
#define LEXT_ERR	152	/**< Could not extend logfile */
#define	VBSZ_ERR	153	/**< Buffer too small */
#define	VRCL_ERR	154	/**< Zero length record in REDVREC or ADDVREC */
#define SYST_ERR	155	/**< Native system failure */
#define NTIM_ERR	156	/**< timeout error */
#define	VFLG_ERR	158	/**< REDVREC record not marked active */
#define	VPNT_ERR	159	/**< Zero recbyt value */
#define ITIM_ERR	160	/**< Multi-user interference: index information
				   updated by the time user got to actual data
				   record */
#define SINA_ERR	161	/**< User appears inactive */
#define SGON_ERR	162	/**< Server has gone away */
#define SFRE_ERR	163	/**< No more room in server lock table */
#define SFIL_ERR	164	/**< File number out of range */
#define SNFB_ERR	165	/**< No file control block available */
#define SNMC_ERR	166	/**< No more ct file control blocks in server */
#define SRQS_ERR	167	/**< Could not read request */
#define SRSP_ERR	168	/**< Could not send answer */
#define TCRE_ERR	169	/**< Create file already opened (in recovery) */

#define SFUN_ERR	170	/**< Bad function number */
#define SMSG_ERR	171	/**< Application msg size exceeds server size */
#define SSPC_ERR	172	/**< Could not allocate server msg buffer */
#define SSKY_ERR	173	/**< Could not identify server */
#define SSID_ERR	174	/**< Could not get server message id */
#define SAMS_ERR	175	/**< Server could not allocate user msg area */
#define SMST_ERR	176	/**< Could not get server msg status */
#define SMQZ_ERR	177	/**< Could not set message server msg size */
#define SINM_ERR	178	/**< Unexpected file# assigned to [si] in rcv */
#define SOUT_ERR	179	/**< Server is at full user capacity */


#define IKRU_ERR	180	/**< Could not read symbolic key name */
#define IKMU_ERR	181	/**< Could not get mem for key symb name */
#define IKSR_ERR	182	/**< No room for sort key. increase MAXFIL */
#define IDRU_ERR	183	/**< Could not read file field number values */
#define ISDP_ERR	184	/**< Attempt to reallocate set space */
#define ISAL_ERR	185	/**< Not enough memory for addt'l sets-batches */
#define ISNM_ERR	186	/**< Set number out of range */
#define IRBF_ERR	187	/**< Null buffer in rtread.c */
#define ITBF_ERR	188	/**< Null target buffer in rtread.c */
#define IJSK_ERR	189	/**< Join_to skip */
#define IJER_ERR	190	/**< Join_to error */
#define IJNL_ERR	191	/**< Join_to null fill */
#define IDSK_ERR	192	/**< Detail_for skip */
#define IDER_ERR	193	/**< Detail_for error */
#define IDNL_ERR	194	/**< Detail_for null fill */
#define IDMU_ERR	195	/**< Could not get mem for dat symb name */
#define ITML_ERR	196	/**< Exceeded RETRY_LIMIT in RTREAD.C */

#define IMEM_ERR	197	/**< Could not get memory for ifil block */
#define BIFL_ERR	198	/**< Improper ifil block */
#define NSCH_ERR	199	/**< Schema not defined for data file */

#define RCRE_ERR	400	/**< Resource already enabled */
#define RNON_ERR	401	/**< Resources not enabled */
#define RXCL_ERR	402	/**< File must be exclusive to enable res*/
#define RZRO_ERR	403	/**< Empty resource id */
#define RBUF_ERR	404	/**< Output buffer too small */
#define RDUP_ERR	405	/**< Resource id already added */
#define RCSE_ERR	406	/**< Bad resource search mode */
#define RRED_ERR	407	/**< Attempt to get non-resource info */
#define RNOT_ERR	408	/**< Resource not found */
#define RELN_ERR	409	/**< Resource length <= 0 */
#define USTP_ERR	410	/**< User not active */
#define BSUP_ERR	411	/**< Not a superfile */
#define LCIP_ERR	412	/**< WRL to WXL commit promote pending(CIL) */
#define SDIR_ERR	413	/**< Superfile host not opened */
#define SNST_ERR	414	/**< Cannot nest superfiles */
#define SADD_ERR	415	/**< Illegal ADDKEY to superfile */
#define SDEL_ERR	416	/**< Illegal DELBLD to superfile */
#define SPAG_ERR	417	/**< Cache page size error */
#define SNAM_ERR	418	/**< Max name inconsistency */
#define SRCV_ERR	419	/**< Host superfile does not support recovery */
#define TPND_ERR	420	/**< Key update with pending transaction */
#define BTFL_ERR	421	/**< Filter not supported yet */
#define BTFN_ERR	422	/**< Other functions not sup */
#define BTIC_ERR	423	/**< Incomplete */
#define BTAD_ERR	424	/**< Add list err */
#define BTIP_ERR	425	/**< Batch in progress */
#define BTNO_ERR	426	/**< No batch active */
#define BTST_ERR	427	/**< Status info already returned */
#define BTMT_ERR	428	/**< No more info, batch cancelled */
#define BTBZ_ERR	429	/**< Bufsiz too small for record */
#define BTRQ_ERR	430	/**< Request is empty or inconsistent */
#define LAGR_ERR	431	/**< Aggregate/serialization lock denied */
#define FLEN_ERR	432	/**< Fixed length string requires len in DODA */
#define SSCH_ERR	433	/**< Segment def inconsistent with schema */
#define DLEN_ERR	434	/**< Very long def block not supported */
#define FMEM_ERR	435	/**< File def memory error */
#define DNUM_ERR	436	/**< Bad def number */
#define DADR_ERR	437	/**< defptr NULL during GETDEFBLK */
#define	DZRO_ERR	438	/**< Requested def blk is empty */
#define DCNV_ERR	439	/**< No conversion routine for Definition Block */
#define DDDM_ERR	440	/**< Dynamic dump or ctQUIET currently active */
#define DMEM_ERR	441	/**< No memory for dynamic dump file buffer */
#define DAVL_ERR	442	/**< One or more files not available for dump */
#define DSIZ_ERR	443	/**< File length discrepancy */
#define DCRE_ERR	444	/**< Could not create file during dump rcv */
#define SDAT_ERR	445	/**< Not enough data to assemble key value */
#define BMOD_ERR	446	/**< Bad mode: parameter out of range */
#define BOWN_ERR	447	/**< Only the file's owner can perform op */
#define DEFP_ERR	448	/**< Permission to set file definition denied */
#define DADM_ERR	449	/**< ADMIN has opened file. Cannot delete file */
#define LUID_ERR	450	/**< Invalid user id */
#define LPWD_ERR	451	/**< Invalid password */
#define LSRV_ERR	452	/**< Server could not process user/acct info */
#define NSRV_ERR	453	/**< No such server */
#define NSUP_ERR	454	/**< Service not supported */
#define SGRP_ERR	455	/**< User does not belong to group */
#define SACS_ERR	456	/**< Group access denied */
#define SPWD_ERR	457	/**< File password invalid */
#define SWRT_ERR	458	/**< Write permission not granted */
#define SDLT_ERR	459	/**< File delete permission denied */
#define SRES_ERR	460	/**< Resource not enabled */
#define SPER_ERR	461	/**< Bad permission flag */
#define SHDR_ERR	462	/**< No directory found in superfile */
#define UQID_ERR	463	/**< File id uniqueness error */
#define IISM_ERR	464	/**< ISAM level logon not performed */

#define IINI_ERR	465	/**< Incremental Index: dnumidx < 1 */
#define IIDT_ERR	466	/**< Incremental Index: dfilno not a ISAM file */
#define IINM_ERR	467	/**< Incremental Index: aidxnam NULL for 1st */
#define IITR_ERR	468	/**< Incremental Index: active tran not allowed */
#define NGIO_ERR	469	/**< Negative I/O request */
#define LGST_ERR	470	/**< Guest logons disabled */
#define JOBT_ERR	471	/**< Job Thread Launch error  - ctFeatJOBMGTSYS*/

/*  472- 475 are available */
/*
#define UNUSED_ERR   472 
#define UNUSED_ERR   473 
#define UNUSED_ERR   474 
#define UNUSED_ERR   475 
*/

#define SORT_SWDEL_ERR  476 /* error deleting sortwork file */
#define SORT_ALC_ERR    477 /* error getting first data area */
#define SORT_INITS_ERR  478 /* sinit phase not previously performed-srelease */
#define SORT_RET_ERR    479 /* sreturn phase already started */
#define SORT_DATA_ERR   480 /* no records in data buffers */
#define SORT_INITR_ERR  481 /* sint phase not previously performed-sreturn */
#define SORT_NOMEM_ERR  482 /* not enough memory */
#define SORT_DATAP_ERR  483 /* no valid record pointers in merge buffers */
#define SORT_SWOPN_ERR  484 /* error opening sortwork file */
#define SORT_SWCRE_ERR  485 /* error creating sortwork.00x file */
#define SORT_SIZO_ERR   486 /* no records fit in output buffer */
#define SORT_READ_ERR   487 /* error reading sortwork file */
#define SORT_SIZM_ERR   488 /* bytes in buf <> merge buf size */
#define SORT_PTR_ERR    489 /* error adjusting file pointer */
#define SORT_SWECL_ERR  490 /* error closing sortwork.00x */
#define SORT_SWCL_ERR   491 /* error closing sortwork file */
#define SORT_SWDEL2_ERR 492 /* error deleting sortwork file */
#define SORT_REN_ERR    493 /* error renaming sortwork.00x */
#define SORT_CLSO_ERR   494 /* error closing output file */
#define SORT_CREO_ERR   495 /* error creating output file */
#define SORT_SWAP_ERR   496 /* insufficient disk space or no more work file segments */
#define SORT_PATH_ERR   497 /* ct_tmppth too long */

#define NLOG_ERR		498 /**< Old log file found during log create */
#define FIDD_ERR		499 /**< Mismatch between recv log & file id */
#define SQLINIT_ERR		500 /**< Server could not init SQL engine */
#define SQLCONNECT_ERR		501 /**< Could not init SQL for a user */
#define SQL_REQUEST_ERROR	502 /**< Could not access SQL master info */
#define SQL_INVALID_CONTINUE	503 /**< Could not continue SQL request */
#define NSQL_ERR		504 /**< Server does not support SQL */
#define USQL_ERR		505 /**< User profile does not enable SQL */
#define SRFL_ERR		506 /**< Could open save-restore file */
#define SRIO_ERR		507 /**< Could not process save-restore file */
#define SRIN_ERR		508 /**< Save restore inconsistency */
#define DSRV_ERR		509 /**< Duplicate server */
#define RFCK_ERR		510 /**< Active chkpnt at start of roll-forward */
#define ILOP_ERR		511 /**< Index nodes form illegal loop: rebuild */
#define DLOP_ERR		512 /**< Data file loop detected */
#define SBLF_ERR		513 /**< FPUTFGET does not support CTSBLDX () */
#define CQUE_ERR		514 /**< Queue has been closed */
#define OIFL_ERR		515 /**< Cannot convert old IFIL structure */
#define GNUL_ERR		516 /**< ctNOGLOBALS not allocated */
#define GNOT_ERR		517 /**< 'regid' is not registered */
#define GEXS_ERR		518 /**< 'regid' is already registered */
#define IEOF_ERR		519 /**< index logical EOF error */
#define HTRN_ERR		520 /**< Attempt to update index with
				       inconsistent tran# */
				    
/*				521 - 526 reserved for BANYAN env */
#ifdef ctPortVINES
#define BMAL_ERR		521 /**< Could not allocate memory for the
				       streettalk login message buffer */
#define STID_ERR		522 /**< Userid in INTISAM does not match
				       current login id */
#endif /**< ifdef ctPortVINES */

#define BIDX_ERR		527 /**< index must be rebuilt:see CTSTATUS.FCS */
#define SLEN_ERR		528 /**< key segment length error		  */
#define CHKP_ERR		529 /**< system checkpoints terminated	  */
#define LMTC_ERR		530 /**< client does not match server	  */
#define BREP_ERR		531 /**< index reorg entry error		  */
#define ASAV_ERR		532 /**< TRANSAV called with ctAUTOSAVE on  */
#define MTRN_ERR		533 /**< file header high-water-mark overflow*/
#define OTRN_ERR		534 /**< transaction # overflow		  */
#define REGC_ERR		535 /**< ctree not registered. Call REGCTREE*/
#define AREG_ERR		536 /**< only automatic REGCTREEs allowed   */
#define TCOL_ERR		537 /**< transaction log collision	  */
#define PIOT_ERR		538 /**< client-side bad function array type*/
#define BFIL_COD	       -539 /**< sysiocod when file does not appear
				       to contain any valid information	  */

#define PNUL_ERR		540 /**< null parameter			  */
#define LWRT_ERR		541 /**< transaction log cannot be written  */
#define MCRE_ERR		542 /**< could not create mirror file	  */
#define MOPN_ERR		543 /**< could not open mirror file	  */
#define MCLS_ERR		544 /**< could not close mirror file	  */
#define MDLT_ERR		545 /**< could not delete mirror file	  */
#define MWRT_ERR		546 /**< could not write to mirror file	  */
#define MSAV_ERR		547 /**< could not save mirror file	  */
#define MRED_ERR		548 /**< could not read from mirror	  */
#define MHDR_ERR		549 /**< mismatch between mirror headers	  */
#define MSKP_ERR		550 /**< attempt to open primary w/o mirror:*/
				    /**< or'ing in a file mode of ctMIRROR_SKP*/
				    /**< permits a primary to be opened w/o */
				    /**< error				  */
#define MNOT_ERR		551 /**< file already opened without mirror */
#define MSEG_ERR		552 /**< segmented file cannot be mirrored  */
#define FBEG_ERR		553 /**< fixed length record beginning err  */
#define ISRL_ERR		554 /**< inconsistent SerialNum defn info	  */
#define PREA_ERR		555 /**< could not read primary, switching  */
#define PWRT_ERR		556 /**< could not write primary, switching */
#define CWRT_ERR		557 /**< could not write mirror,suspend mir */
#define PSAV_ERR		558 /**< could not save primary, switching  */
#define CSAV_ERR		559 /**< could not save mirror, suspend mir */

#define SMON_ERR		560 /**< only one of each monitor at a time */
#define DDMP_BEG		561 /**< SYSMON: dynamic dump begins	  */
#define DDMP_END		562 /**< SYSMON: dynamic dump ends	  */
#define DDMP_ERR		563 /**< SYSMON: dynamic dump ends (errors) */


/* *** At the end of automatic recovery, the following conditions     *** */
/* *** were detected which require cleanup before continuing. The     *** */
/* *** specifics are reported on in CTSTATUS.FCS:		      *** */

#define RCL1_ERR		570 /**< incomplete compression		  */
#define RCL2_ERR		571 /**< index rebuild required		  */
#define RCL3_ERR		572 /**< incomplete compression & index re- */
				    /**< build required			  */
#define RCL4_ERR		573 /**< primary\mirror out-of-sync. Copy	  */
				    /**< good file over bad.		  */
#define RCL5_ERR		574 /**< incomplete compression & primary\  */
				    /**< mirror out-of-sync		  */
#define RCL6_ERR		575 /**< index rebuild required & primary\  */
				    /**< mirror out-of-sync		  */
#define RCL7_ERR		576 /**< incomplete compression & index re- */
				    /**< build required & primary\mirror	  */
				    /**< out-of-sync			  */

#define DWRT_ERR		577 /**< update refused during protected dmp*/

#define LIVL_ERR		579 /**< logon interval error		  */
#define FSEC_ERR		580 /**< could not perform file security op */
#define EGRP_ERR		581 /**< group does not exist		  */
#define KSML_ERR		582 /**< key length too small		  */
#define SAVL_ERR		583 /**< file extension exceeds diskfull limit*/
#define LRSM_ERR		584 /**< exceeded failed logon limit	  */
#define LVAL_ERR		585 /**< logon date exception		  */
#define MFID_COD	       -586 /**< diff file name, matching file ID	  */
#define CPND_COD	       -587 /**< close/delete deferred: pending tran*/
#define CPND_ERR		588 /**< attempt to close or delete file	  */
				    /**< with pending (active) tran	  */
#define LADM_ERR		589 /**< member of ADMIN group required	  */
#define NCON_ERR		590 /**< could not find ISAM context ID	  */
#define OCON_ERR		591 /**< old context ID. Call CLSICON()	  */
#define ECON_ERR		592 /**< context ID exists		  */
#define XUSR_ERR		593 /**< non ADMIN user blocked from log on */
#define XUSR_COD	       -594 /**< users in SEC_BLOCK class logged on */
#define CLEN_ERR		595 /**< varlen too small in PUTCRES	  */
#define CMIS_ERR		596 /**< missing information 		  */
#define CINI_ERR		597 /**< could not initialize expression	  */
#define CVAL_ERR		598 /**< could not evaluate conditional exp */
#define DEXT_ERR		599 /**< dynamic dump extent error	  */
#define CTHD_ERR		600 /**< no more client threads		  */
#define VRFY_ERR		601 /**< ctVERIFY detected problems with idx*/
#define CMEM_ERR		602 /**< no memory for system lock table	  */
#define FLEX_ERR		603 /**< could not allocate FCB		  */
#define FINC_ERR		604 /**< could not increase user files	  */
#define KSRL_ERR		605 /**< records with bad (all FF) serial #s*/
#define DCOD_ERR		606 /**< could not handle file encoding	  */
#define RCOD_ERR		607 /**< recovery could not enable encoding */
#define IAIX_ERR		608 /**< IIDX attributes do not match file  */
#define LTPW_ERR		609 /**< one-use temp password failure	  */
#define HNUL_ERR		610 /**< CTHIST target==NULL		     */
#define HLOG_ERR		611 /**< CTHIST could not access log	     */
#define HSTR_ERR		612 /**< CTHIST must be called with ctHISTfirst*/
#define HONE_ERR		613 /**< CTHIST can only access data or index  */
#define HMAP_ERR		614 /**< no valid ISAM map from index to data  */
#define HIDX_ERR		615 /**< cannot get index info from data filno */
#define HACT_ERR		616 /**< CTHIST cannot be called during a tran */
#define HNOT_ERR		617 /**< did not find target		     */
#define HENT_ERR		618 /**< log scan terminated: EOF or bad entry */
#define HZRO_ERR		619 /**< CTHIST on data file: recbyt==0	     */
#define HSIZ_ERR		620 /**< bufsiz too small			     */
#define HTYP_ERR		621 /**< transaction type not expected	     */
#define HMID_ERR		622 /**< must reset CTHIST first		     */
#define HMEM_ERR		623 /**< not enough memory for CTHIST	     */
#define HNET_ERR		624 /**< net change only applies to specific
				       match of key or record position	     */
#define HMTC_ERR		625 /**< must specify exactly one matching
				       criteria (user & node may be combined)*/ 
#define HUND_ERR		626 /**< encountered an UNDTRAN going forward:
				       must completely restart this CTHIST
				       sequence				     */
#define HUNK_ERR		627 /**< unknown type of request		     */
#define HFIL_ERR		628 /**< must specify filno		     */
#define HTFL_ERR		629 /**< could not initialize internal file ID */
#define HUNX_ERR		630 /**< unexpected length in log entry	     */
#define SSLO_ERR		631 /**< could not get ctSS_LOCK on file	  */
#define LLOK_COD	       -632 /**< user lost locks found on close	  */
#define NPLN_ERR		633 /**< null plen (pointer to size)	  */
#define NLEN_ERR		634 /**< negative length specified	  */
#define TSYC_ERR		635 /**< could not create thread sync object*/
#define TSYF_ERR		636 /**< thread sync object 'get' failed	  */
#define TSYR_ERR		637 /**< thread sync object 'rel' failed	  */
#define TQUE_ERR		638 /**< queue message truncated to fit	  */
#define TZRO_ERR		639 /**< semaphore must be init with count>0*/
#define TINT_ERR		640 /**< semaphore already initialized	  */
#define TSYX_ERR		641 /**< thread sync object 'cls' failed	  */
#define EXCT_ERR		642 /**< must use exact file names	  */
#define DPND_ERR		643 /**< access a file pending delete	  */
#define RDEL_COD	       -644 /**< reversible TRANDEP delete	  */
#define CHGF_ERR		645 /**< changed file # after deferred close*/
#define SDEP_ERR		646 /**< superfile member/host TRANDEP !=	  */
#define E2GB_COD	       -647 /**< no support above 2GB		  */
#define E4GB_COD	       -648 /**< no support above 4GB		  */
/*				649    ... reserved ...			  */
#define DUPJ_ERR		650 /**< duplicate keys purged and logged	  */
#define DUPX_ERR		651 /**< could not process dup key log	  */
#define DUPL_ERR		652 /**< duplicate keys rejected and listed */
#define MAPL_ERR		653 /**< attempt to exceed mapped lock limit*/
#define TLNG_ERR		654 /**< record length too long for log size*/
#define FREO_ERR		655 /**< could not reopen using freopen	  */
#define LHDR_ERR		656 /**< transaction log header is bad	  */
#define CPYF_ERR		657 /**< could not create copy file	  */
#define CPYW_ERR		658 /**< could not write copy file	  */
#define CPYR_ERR		659 /**< could not read entire original file*/
#define CPYB_ERR		660 /**< rbld complete, but failed mirror copy  */
#define CPYX_ERR		661 /**< failed process dup log and copy mirror */
#define CPYJ_ERR		662 /**< dup purged, but could not copy mirror  */
#define CPYL_ERR		663 /**< dup rejected, but could not copy mirror*/
#define LPRI_ERR		664 /**<  primary log (or start) file failed    */
#define LMIR_ERR		665 /**< mirrored log (or start) file failed    */
#define LFRM_ERR		666 /**< incompatible log format		      */
#define MAXZ_ERR		667 /**< attempt to exceed max file size	     */
#define LRGN_ERR		668 /**< large page size not a multiple of 16K */
#define XCRE_ERR		669 /**< inconsistent XCREblk		     */
#define HMIN_ERR		670 /**< node sectors too small for huge file  */
#define XOVR_ERR		671 /**< non-zero high long with non-huge file */
#define HDR8_ERR		672 /**< inconsistency: file attr & sys version*/
#define SIG8_ERR		673 /**< extended header bad signature	     */
#define SEGM_ERR		674 /**< additional file segments needed	     */
#define SEGS_ERR		675 /**< file segments not supported	     */
#define SEGO_ERR		676 /**< could not open segment		     */
#define SEGD_ERR		677 /**< cannot directly operate on seg def    */
#define SEGN_ERR		678 /**< bad file segment name		     */
#define SEGZ_ERR		679 /**< bad file segment size		     */
#define SEGC_ERR		680 /**< could not create file segment	     */
#define SEGH_ERR		681 /**< could not process segment header	     */
#define SEGL_ERR		682 /**< seg resource cannot move		     */
#define SEGU_ERR		683 /**< seg update invalid, see CTSTATUS.FCS  */
#define SEGX_ERR		684 /**< segment update already in progress    */
#define SEGF_ERR		685 /**< i/o on segmented file terminated	     */
#define SEGR_ERR		686 /**< segment definition too large	     */
#define SEGQ_ERR		687 /**< unexpected value during recovery	     */
#define SEGP_ERR		688 /**< pending segment mismatch		     */
#define SEQ8_ERR		689 /**< 1st & 2nd headers out of sync	     */
#define CREQ_ERR		690 /**< bad request  header CheckSum	     */
#define CRSP_ERR		691 /**< bad response header CheckSum	     */
#define CRCQ_ERR		692 /**< bad request (to server) CRC	     */
#define CRCP_ERR		693 /**< bad response (from server) CRC	     */
#define NUNC_ERR		694 /**< no Unicode support		     */
#define BSPC_ERR		695 /**< could not get work buffer for blk I/O */
#define SEGK_ERR		696 /**< OPNFIL called for a segment	     */
#define DSPC_ERR		697 /**< could not allocate encoding buff	     */

#define OSEG_ERR		700 /**< could not open key segment definition */
#define CSEG_ERR		701 /**< could not process comp options	     */
#define ASEG_ERR		702 /**< could not process comp attributes     */
#define HSEG_ERR		703 /**< invalid key segment handle	     */
#define SSEG_ERR		704 /**< invalid source type		     */
#define DSEG_ERR		705 /**< segment definition already exists     */
#define NSEG_ERR		706 /**< no segment data produced		     */
#define USEG_ERR		707 /**< no segment definition		     */
#define MBSP_ERR		708 /**< multibyte names not supported	     */
#define MBNM_ERR		709 /**< badly formed multibyte name	     */
#define MBFM_ERR		710 /**< multibyte variant not supported	     */
#define DIDX_ERR		711 /**< cannot call UPDCIDX while DROPIDX pndg*/
#define PLOW_ERR		712 /**< partition number out of range - low   */
#define PHST_ERR		713 /**< file is not partition host	     */
#define PMBR_ERR		714 /**< file is not partition member	     */
#define PNOT_ERR		715 /**< raw partition does not exist	     */
#define PXPR_ERR		716 /**< bad value for partition key	     */
#define POVR_ERR		717 /**< could not overload partition #	     */
#define PUSD_ERR		718 /**< partition member in use		     */
#define PPND_ERR		719 /**< partition member pending purge	     */
#define PPRG_ERR		720 /**< partition member purged		     */
#define PARC_ERR		721 /**< partition member archived	     */
#define PLST_ERR		722 /**< bad partition host list		     */
#define PTRY_ERR		723 /**< must retry operation		     */
#define PCRP_ERR		724 /**< bad current ISAM position for host    */
#define PVRN_ERR		725 /**< PARTRES version error		     */
#define PPRG_COD		-726 /**< duplicate error caused by purged part */
#define PFMD_ERR		727 /**< bad partition file mode settings      */
#define PSUP_ERR		728 /**< Partition support not enabled	     */
#define PUNQ_ERR		729 /**< purged unique global keys encountered */
#define PHGH_ERR		730 /**< partition number out of range - high  */
#define PRIK_ERR		731 /**< illegal operation with primary key    */
#define UMOD_ERR		732 /**< illegal file mode / x8mode value      */
#define PMOP_ERR		733 /**< cannot open this member except RO     */
#define EXTH_ERR		734 /**< extended header (V7 file) required    */
#define CUNF_ERR		735 /**< client does not support UNIFRMAT srvr */
#define AOVR_ERR		736 /**< async handle overflow		     */
#define PMTC_ERR		737 /**< partition member characteristics	     */
				    /**< do not match			     */
#define MINT_ERR		738 /**< ctThrdInit must be called first	     */
#define FFLT_ERR		739 /**< record does not pass filter	     */
#define DDCR_ERR		740 /**< dynamic dump refused SF member create */
#define DDDR_ERR		741 /**< dynamic dump refused SF member delete */
#define S6BT_ERR		742 /**< superfile member idx / host 6BTRAN != */
#define SFHI_ERR		743 /**< superfile host directory index null   */
#define FREL_ERR		744 /**< file requires unavailable feature     */
#define R6BT_ERR		745 /**< 6BTRAN file required		     */
#define ACHN_ERR		746 /**< could not allocate I/O channel(s)     */
#define RSYN_ERR		747 /**< partition rule syntax error	     */
#define REXT_ERR		748 /**< read failed external cause: sysiocod  */
#define PBAD_ERR		749 /**< bad parameter value		     */
#define ICUV_ERR		750 /**< different ICU version, rebuild index  */
#define CHKM_ERR		751 /**< checkpoint memory inconsistency	     */
#define LSET_ERR		752 /**< more than one log set in transaction  */
#define SPCL_ERR		753 /**< cannot RST/CLR past special savepoint */
#define QOWN_ERR		754 /**< only Q creator can perform operation  */
#define SQUE_ERR		755 /**< a system queue is required	     */
#define NACT_ERR		756 /**< server is not activated		     */
#define STPU_ERR		757 /**< must uninit c-tree (STPUSR)	     */
#define QNOT_ERR		758 /**< only notifications to queue	     */
#define QUIN_ERR		759 /**< wrong queue instance		     */
#define XMON_ERR		760 /**< SYSMON interrupted / cancelled	     */
#define NMON_ERR		761 /**< no active SYSMON			     */
#define NRNG_ERR		762 /**< no range defined for index	     */
#define ORNG_COD		763 /**< segment out of range		     */
#define CRNG_ERR		764 /**< range defined but no FRS/LST RNG	     */
#define CIOB_ERR		765 /**< comm I/O has been blocked-ctcomioblk
				       has been set by user		     */
#define VCLS_ERR		766 /**< insufficient file handles and could
				       not find file to close for virtual
				       processing			     */
#define FALG_ERR		767 /**< fixed length record offset not aligned*/
#define CMLK_ERR		768 /**< commit lock error: make sure record
				       update performed with lock	     */
#define CULK_ERR		769 /**< unexpected CMTLOK unlock failure: call
				       FairCom				     */
#define XTRN_ERR		770 /**< cannot turn off file's tran support in
				       middle of transaction if file updated */
#define COMP_ERR		771 /**< compatibility option not enabled	     */
#define PLAT_ERR		772 /**< platform does not support compatibility
				       option */
#define SREP_ERR		773 /**< superfile host & member must have same
				       REPLICATION attribute */
#define SMEM_ERR		774 /**< superfile members must all be closed  */
#define UNQK_ERR		775 /**< no UNQKEY support for REPLICATION     */
#define SUPR_ERR		776 /**< operation not supported for SUPERFILES */
#define REPU_ERR		777 /**< cannot unregister another client's
				       replication instance		     */
#define REPI_ERR		778 /**< the specified replication instance name
				       is not registered		     */
#define REPR_ERR		779 /**< the specified replication instance name
				       is already registered		     */
#define REPA_ERR		780 /**< cannot attach to replication instance
				       with active connection		     */
#define REPC_ERR		781 /**< this replication connection already has
				       a registered instance name	     */
#define UCMP_ERR		782 /**< decompression error: unexpected
				       output length			     */
#define IITI_ERR		783 /**< incremental index: cannot add permanent
				       indices while temporary indices exist */
#define LDPI_ERR		784 /**< LDAP initialization failed            */
#define LDPC_ERR		785 /**< error connecting to LDAP server	     */
#define LDPB_ERR		786 /**< error binding to LDAP server	     */
#define LDPA_ERR		787 /**< LDAP user authentication failed       */
#define LDPG_ERR		788 /**< error checking user's LDAP groups     */
#define LGRP_ERR		789 /**< member of c-tree login group required */
#define LSST_ERR		790 /**< strict serializer must be in
				       transaction to access record	     */
#define LSSK_ERR		791 /**< strict serializer cannot keep locks   */
#define XSHT_ERR		792 /**< external server shutdown disabled     */
#define PKSP_ERR		793 /**< partial record rewrite has keys
				       spanning partial record and remaining
				       region of record			     */
#define XBUF_ERR		794 /**< Tried to update data with missing key
				       buffer contents			     */
#define VTSM_COD		-795 /**< recursive ctptsema call for open or
				       create				     */
#define FCPY_ERR		796 /**< file copy failed			     */
#define DRST_ERR		797 /**< immediate dump restore failed	     */
#define FBLK_ERR		798 /**< file is blocked, retry later	     */
#define FBLK_RDO		799 /**< file block cleared: close/reopen file */
#define TDEP_ERR		800 /**< TRANDEP file operation pending	     */
#define FBLK_PND		801 /**< trying to set file block. leave core. */
#define FBLK_SUP		802 /**< file block not supported for file type*/
#define LNEW_ERR		803 /**< existing lock not replaced: cts_lok81 */
#define SETO_ERR		804 /**< cannot override configuration option
				       that was specified in settings file   */
#define MSTK_ERR		805 /**< no memory for func stack alloc	     */
#define KCON_ERR		806 /**< failed to connect to kernel engine    */
#define MSTK_COD		807 /**< ctDBGstack limit exceeded: debugging
				       only				     */
#define TRQS_ERR		808 /**< request timed out		     */
#define TRSP_ERR		809 /**< response timed out		     */
#define SLOG_ERR		810 /**< status log write failure		     */
#define IAPI_ERR		811 /**< update only from internal API	     */
#define ZRCZ_ERR		812 /**< unexpected zero node size in header   */
#define UBLK_ERR		813 /**< unexpected state for user block obj   */
#define FBLK_ACT		814 /**< thread did not have ctFBactive set    */
#define FBLK_NTF		815 /**< ctFILBLK already in progress for file */
#define QTUQ_ERR		816 /**< only one ctQUIET process at a time    */
#define QTAB_ERR		817 /**< transaction aborted by ctQUIET	     */
#define QTFB_ERR		818 /**< ctQUIET / ctFILBLK  conflict	     */
#define QTBB_ERR		819 /**< unexpected failure to block thread    */
#define QTBK_PND		820 /**< trying to get QUIET. leave core.	     */
#define MLAB_ERR		821 /**< transaction abandoned: MAX_USER_LOGS  */
#define MLHG_ERR		822 /**< abort request would be suspended	     */
#define TRAB_COD	       -823 /**< QTAB_ERR or MLAB_ERR or TTAB_ERR but
				       operation performed		     */
#define MIMP_ERR		824 /**< problem impersonating thread	     */
#define QTOP_ERR		825 /**< ctQUIET called with files opened	     */

#define QBAD_ERR		826 /**< improper ctQT actions: see sysiocod   */
#define QBKU_COD	1	/* block and unblock actions mixed	     */
#define QBUN_COD	2	/* cannot block after unblock has begun	     */
#define QMBK_COD	3	/* mixed file block types 		     */
#define QSPC_COD	4	/* missing filespec			     */
#define QMAP_COD	5	/* mixed API block types		     */
#define QBAP_COD	6	/* blockAllFiles requires blockAPI	     */
#define QBFA_COD	7	/* cannotBlockAllFiles after blockFiles	     */
#define QFAP_COD	8	/* file flush requires blockAPI		     */
#define QLAP_COD	9	/* blockLogFiles requires blockAPI	     */
#define QDUP_COD	10	/* block action already requested	     */
#define QLOG_COD	11	/* unblockLogFiles required		     */
#define QLGR_COD	12	/* cannot mox ctQTlog_restorepoint with      **
				** other block modes			     */
#define QLGK_COD	13	/* ctQTlog_checkpoint can only be used with  **
				** ctQT_logrestorepoint			     */

#define UTIM_OUT		827 /**< user block timed out		     */
#define ICUV_COD	       -828 /**< ICU version updated		     */
#define ICUV_REB	       -829 /**< ICU version updated & rebuild required*/
#define TTAB_ERR		830 /**< transaction abandoned: TRAN_TIMEOUT   */
#define TTHG_ERR		831 /**< abort request would be suspended	     */

#define ITMP_COD	       -832 /**< sysiocod value when ITIM_ERR occurs
				       on a temporary index and record is
				       skipped				     */

#define XNOD_ERR		833 /**< The connection attempt has been
				       rejected because it would exceed the
				       maximum number of concurrent
				       client machines allowed		     */

#define XCON_ERR		834 /**< The connection attempt has been
				       rejected because it would exceed the
				       maximum number of concurrent
				       connections allowed from this client
				       machine				     */
#define TRAB_ERR		835 /**< transaction aborted (e.g., MLAB_ERR or
				       TTAB_ERR) before the requested
				       operation was processed. (Compare with
				       TRAB_COD.)			     */

#define LCON_ERR		836 /**< The connection attempt has been
				       rejected because only connections
				       from the local system are allowed     */

#define IDUP_COD	       -837 /**< sysiocod value when KDUP_ERR occurs
				       on a temporary index and error is
				       ignored				     */
#define CEXC_ERR		838 /**< clnleaf(CLNIDXX) failed to clean
				       node. very unexpected. call FairCom   */
#define CTRN_ERR		839 /**< index file requires key level lock
				       cleaning				     */
#define CTRN_COD	       -840 /**< sysiocod when read only, admin open
				       request blocked by on the fly CLNIDXX */
#define SHMC_ERR		841 /**< A connection attempt using the shared
				       memory protocol failed due to an
				       incompatibility between client and
				       server				     */
#define FBLK_ABT		842 /**< could not clear all threads from
				       core, abort ctFILBLK attempt	     */
#define QTBK_ABT		843 /**< could not clear all threads from
				       core, abort ctQUIET attempt	     */
#define BTNO_COD	       -844 /**< batch has been closed		     */
#define DNCT_ERR		845 /**< index does not have distinct attribute*/
#define DNCT_XCL		846 /**< ctDISTINCTset update in progress	     */
#define RPTD_ERR		847 /**< auto recovery interrupted	     */
#define RDND_COD	       -848 /**< sysiocod: LOKDYN demotion denied	     */
#define SAVP_COD	       -849 /**< sysiocod: LOKDYN free denied	     */
#define TR_CLIL_ERR	        850 /**< Transactional replication: Failed to
				       start c-tree remote client subsystem:
				       see CTSTATUS.FCS for details	     */
#define TR_RMAP_ERR	        851 /**< Transactional replication: Failed to
				       open replication mapping file: see
				       CTSTATUS.FCS for details		     */
#define TR_RATR_ERR		852 /**< Transactional replication: Failed to
				       open replica for writing because the
				       file does not meet the requirements
				       for replication: see CTSTATUS.FCS for
				       details				     */
#define TR_FNOD_ERR	        853 /**< Transactional replication: Failed to
				       set node name for connection to master
				       server: see CTSTATUS.FCS for details  */
#define TR_REDF_ERR	        854 /**< Transactional replication: Attempted
				       to update replica without enabling
				       transactional replication for the
				       connection			     */
#define TR_SAVP_ERR		855 /**< Transactional replication: Failed to
				       establish a savepoint because savepoint
				       number is out of sync with master     */
#define TR_RDIF_ERR		856 /**< Transactional replication: Failed to
				       read record for update: local record
				       differs from master record	     */
#define XSUP_ERR		857 /**< In multi-user standalone mode: The
				       superfile host is open in exclusive mode.
				       The superfile member must be opened in
				       exclusive mode, not shared mode.	     */
#define TR_NSUP_ERR		858 /**< Transactional replication: This feature
				       is not supported for replicas.	     */
#define UVRC_ERR		859 /**< The client's structure definition for
				       the file FAIRCOM.FCS!USER.dat is
				       out of date. Update client library.   */
#define UVRS_ERR		860 /**< The server's structure definition for
				       the file FAIRCOM.FCS!USER.dat is
				       out of date. Update c-tree Server.    */
#define KLLX_ERR		861 /**< after recovery, a key level lock for
				       an undone transaction discovered in
				       optional diagnostic scan		     */
#define UNPG_ERR		862 /**< LOCK_CACHE: System pagesize query
				       failed                                */
#define IMPD_ERR		863 /**< The request to impersonate the specified
				       connection was denied because the target
				       connection does not allow impersonation.
									     */
#define IMPU_ERR		864 /**< The request to impersonate the specified
				       connection was denied because the target
				       connection does not allow impersonation
				       by the specified connection.	     */
#define IMPA_ERR		865 /**< The request to impersonate the specified
				       connection was denied because the target
				       connection is already being impersonated.
									     */
#define IMPB_ERR		866 /**< The request to impersonate the specified
				       connection was denied because the target
				       connection is executing a database
				       operation or is blocked.		     */
#define CBKD_ERR		867 /**< Failed to load the filter callback
				       library. See CTSTATUS.FCS for details.*/
#define CBKF_ERR		868 /**< Failed to resolve the filter callback
				       function in the filter callback DLL.
				       See CTSTATUS.FCS for details.	     */
#define RCBK_ERR		869 /**< A user-defined callback function
				       terminated the rebuild operation.     */
#define CBKV_ERR		870 /**< The filter callback DLL version is not
				       compatible with the c-tree Server's
				       filter callback version.
				       See CTSTATUS.FCS for details.	     */
/**
** Symbolic Constant: XFR_SOPN_ERR
**
** Description:
**
** The file transfer operation failed because the source file could not be
** opened for reading. Check sysiocod for the system error code.
*/
#define XFR_SOPN_ERR		871

/**
** Symbolic Constant: XFR_DOPN_ERR
**
** Description:
**
** The file transfer operation failed because the destination file could not
** be opened for writing. Check sysiocod for the system error code.
*/
#define XFR_DOPN_ERR		872

/**
** Symbolic Constant: XFR_READ_ERR
**
** Description:
**
** The file transfer operation failed because the source file could not be
** read. Check sysiocod for the system error code.
*/
#define XFR_READ_ERR		873

/**
** Symbolic Constant: XFR_WRITE_ERR
**
** Description:
**
** The file transfer operation failed because the destination file could not
** be written. Check sysiocod for the system error code.
*/
#define XFR_WRITE_ERR		874

/**
** Symbolic Constant: XFR_BCON_ERR
**
** Description:
**
** A bound database connection called the file transfer function, but this
** function is supported for client connections only.
*/
#define XFR_BCON_ERR		875

/**
** Symbolic Constant: XFR_BSIZ_ERR
**
** Description:
**
** The file transfer operation failed because the caller specified an invalid
** file transfer block size.
*/
#define XFR_BSIZ_ERR		876

/**
** Symbolic Constant: XFR_SFNM_ERR
**
** Description:
**
** The file transfer operation failed because the caller specified a NULL or
** empty source file name.
*/
#define XFR_SFNM_ERR		877

/**
** Symbolic Constant: XFR_DFNM_ERR
**
** Description:
**
** The file transfer operation failed because the caller specified a NULL or
** empty destination file name.
*/
#define XFR_DFNM_ERR		878

/**
** Symbolic Constant: XFR_VER_ERR
**
** Description:
**
** The version of the file transfer structure supplied by the caller is not
** compatible with the c-tree library's structure definition. Check sysiocod
** for the required file transfer structure version.
*/
#define XFR_VER_ERR		879

/**
** Symbolic Constant: XFR_DEXS_ERR
**
** Description:
**
** The file transfer operation failed because the destination file exists and
** the caller did not specify that the destination file is to be overwritten.
*/
#define XFR_DEXS_ERR		880

/**
** Symbolic Constant: XFR_TREP_ERR
**
** Description:
**
** The file transfer operation between a local and master server failed because
** the server does not support the transactional replication feature.
*/
#define XFR_TREP_ERR		881

/**
** Symbolic Constant: XFR_TRLC_ERR
**
** Description:
**
** The file transfer operation between a local and master server failed because
** the server is not configured as a local server. Use the REPL_MAPPINGS option
** to configure the server as a local server.
*/
#define XFR_TRLC_ERR		882

/**
** Symbolic Constant: MUOP_ERR
**
** Description:
**
** An attempt was made to open a file multiple times by the same user with
** different user file numbers but this support is disabled.
*/
#define MUOP_ERR		883

/**
** Symbolic Constant: DUFL_COD
**
** Description:
**
** A sysiocod value that indicates a user file number mismatch during lock or
** unlock operations.
*/
#define DUFL_COD	       -884

/**
** Symbolic Constant: OCHK_COD
**
** Description:
**
** A sysiocod value that indicates that this API call to perform a checkpoint
** took no action because a checkpoint was already in progress.
*/
#define OCHK_COD	       -885

/**
** Symbolic Constant: UFLK_ERR
**
** Description:
**
** Unexpected CHG_UFLOCK failure: call FairCom (sysiocod specifies locale)
*/
#define UFLK_ERR		886

/**
** Symbolic Constant: DUFL_ERR
**
** Description:
**
** Promoting a secondary lock from read to write is not supported.
*/
#define DUFL_ERR		887

/**
** Symbolic Constant: CONGRP_INVTASKID_ERR
**
** Description:
**
** The specified task ID does not correspond to an active client connection.
*/
#define CONGRP_INVTASKID_ERR	888

/**
** Symbolic Constant: CONGRP_INUSE_ERR
**
** Description:
**
** The specified connection is a member of a connection group.
*/
#define CONGRP_INUSE_ERR	889

/**
** Symbolic Constant: HSTNAM_ERR
**
** Description:
**
** An attempt to get the name of the host system failed. Check that the
** system's host name is properly configured.
*/
#define HSTNAM_ERR		890

/**
** Symbolic Constant: HSTADR_ERR
**
** Description:
**
** An attempt to get the IP addresses associated with the host system
** failed. Check that TCP/IP name resolution is properly configured on
** the host system.
*/
#define HSTADR_ERR		891

/**
** Symbolic Constants: MBUF_ERR / DBUF_ERR / NKEY_ERR
**
** Description:
**
** An attempt to perform a sequential, index based retrieval when the index
** does not have a current key value. This may occur because ctISAMKBUFhdr
** has turned off key buffer updates (MBUF_ERR); or a partial record read
** or changing current ISAM record location does not permit the current key
** value to be assembled (DBUF_ERR); or a conditional index constraint or
** NUL key results in no key value (NKEY_ERR).
*/
#define MBUF_ERR		892
#define DBUF_ERR		893
#define NKEY_ERR		894

/**
** Symbolic Constant: TSEG_ERR
**
** Description:
**
** Partition index segment definition does not satisfy the following
** constraint: there must be at least one segment used to perform the
** key-to-partition map, and all the segments used must come at the
** beginning of the key.
*/
#define TSEG_ERR		895

/**
** Symbolic Constant: VSEG_ERR
**
** Description:
**
** Covering index segment definitions do not map to partition index.
** Call FairCom.
*/
#define VSEG_ERR		896

/**
** Symbolic Constant: KINC_ERR
**
** Description:
**
** Covering index segment map (ptmap) is empty
*/
#define KINC_ERR		897

/**
** Symbolic Constant: QABN_ERR
**
** Description:
**
** A logon fails with QABN_ERR when a ctQUIET call has been abandoned,
** blocking attempts to validate user logons. Only the super user can
** logon when a ctQUIET has been abandoned.  The super user can then
** call ctQUIET with a ctQTunblockALL argument.
*/
#define QABN_ERR		898

/**
** Symbolic Constant: PMCN_ERR
**
** Description:
**
** Cannot perform ISAM Context operations on partition member
** unless it has been opened in stand-alone mode (i.e., independently
** of the host file).
*/
#define PMCN_ERR		899

/**
** Symbolic Constant: SEQDUP_ERR
**
** Description:
**
** A sequence having the specified name already exists.
*/
#define SEQDUP_ERR		900

/**
** Symbolic Constant: SEQNAM_ERR
**
** Description:
**
** An invalid sequence name was specified: the name is NULL, empty, or too long.
*/
#define SEQNAM_ERR		901

/**
** Symbolic Constant: SEQHND_ERR
**
** Description:
**
** The specified sequence handle is invalid.
*/
#define SEQHND_ERR		902

/**
** Symbolic Constant: SEQTYP_ERR
**
** Description:
**
** The specified sequence type contains an invalid combination of sequence type
** options. The sequence type must be set to either ctSEQINC (incrementing
** sequence) or ctSEQDEC (decrementing sequence), and either ctSEQCYC (cycling
** sequence) or ctSEQTRM (terminating sequence), and optionally includes
** ctSEQLIM (enforce sequence limit).
*/
#define SEQTYP_ERR		903

/**
** Symbolic Constant: SEQINI_ERR
**
** Description:
**
** The initial value specified for the sequence is out of range. If the
** sequence enforces a limit, the initial sequence value must be less than
** the sequence limit for an incrementing sequence or must be greater than
** the sequence limit for a decrementing sequence.
*/
#define SEQINI_ERR		904

/**
** Symbolic Constant: SEQCUR_ERR
**
** Description:
**
** The current value specified for the sequence is out of range. For an
** incrementing sequence, the current sequence value must be greater than or
** equal to the initial sequence value, and if the sequence enforces a limit
** the current sequence value must be less than or equal to the limit value.
** For a decrementing sequence, the current sequence value must be less than or
** equal to the initial sequence value, and if the sequence enforces a limit
** the current sequence value must be greater than or equal to the sequence
** limit.
*/
#define SEQCUR_ERR		905

/**
** Symbolic Constant: SEQLIM_ERR
**
** Description:
**
** The limit value specified for the sequence is out of range. The sequence
** limit must be greater than the initial sequence value for an incrementing
** sequence or must be less than the initial sequence value for a decrementing
** sequence. The sequence limit is only enforced if the sequence type specifies
** the ctSEQLIM bit.
*/
#define SEQLIM_ERR		906

/**
** Symbolic Constant: SEQINC_ERR
**
** Description:
**
** The increment value specified for the sequence is out of range. The sequence
** increment amount must be a positive value that is less than the difference
** between the initial sequence value and the sequence limit.
*/
#define SEQINC_ERR		907

/**
** Symbolic Constant: DSTX_ERR
**
** Description:
**
** The file header indicates that the maximum number of partial key distinct
** counts supported by the file is greater than the system support limit:
** ctMAXSEGdistinct. The file cannot be opened.
*/
#define DSTX_ERR		908

/**
** Symbolic Constant: VFYVER_ERR
**
** Description:
**
** The structure version specified for the input and output structures is not
** supported by this version of the code.
*/
#define VFYVER_ERR		909

/**
** Symbolic Constant: VFYTRM_ERR
**
** Description:
**
** A user-defined callback function terminated the index verify operation.
*/
#define VFYTRM_ERR		910

/**
** Symbolic Constant: NSUP_DAR
**
** Description:
**
** File contains a Direct Access Resource (DAR) that is not supported. sysiocod
** contains the type of DAR: see ctopt2.h for "dartyp assignments".
*/
#define NSUP_DAR		911

/**
** Symbolic Constant: URES_ERR
**
** Description:
**
** Special resource can only be added by system routine. sysiocod holds
** the special resource type.
*/
#define URES_ERR		912

/**
** Symbolic Constant: DDAR_ERR
**
** Description:
**
** Duplicate DAR not allowed. sysiocod holds the 'dartyp' value: see
** FC_DAR_TYPES in ctopt2.h for intrpetation.
*/
#define DDAR_ERR		913

/**
** Symbolic Constant: XDAR_ERR
**
** Description:
**
** Requested DAR does not exist.
*/
#define XDAR_ERR		914

/**
** Symbolic Constant: LAUG_ERR
**
** Description:
**
** Log file requires augmented log entries that are not supported.
*/
#define LAUG_ERR		915

/**
** Symbolic Constant: NDAR_ERR
**
** Description:
**
** Mismatch between header DAR count, and DARs found in resource chain.
*/
#define NDAR_ERR		916

/**
** Symbolic Constant: ODAR_ERR
**
** Description:
**
** Reached limit on the number of instances of a particular DAR type
** for a single file. Cannot add any more.
*/
#define ODAR_ERR		917

/**
** Symbolic Constant: RDAR_ERR
**
** Description:
**
** DAR attribute word is marked deleted (FC_DAR_delete bit). A nonTran
** file DAR delete forces DAR image to disk with FC_DAR_delete bit set
** in attribute word.
*/
#define RDAR_ERR		918

/**
** Symbolic Constant: REPL_ERR
**
** Description:
**
** Low-level operations are not allowed on replicated files.
*/
#define REPL_ERR		919

/**
** Symbolic Constant: FNAC_ERR
**
** Description:
**
** The file exists but could not be accessed. Check the system error code
** stored in sysiocod for the reason.
*/
#define FNAC_ERR		920

/**
** Symbolic Constant: IDFL_CHG
**
** Description:
**
** Attempt to change IDfield during an ISAM rewrite operation. Rewrite
** fails.
*/
#define IDFL_CHG		921

/**
** Symbolic Constant: IDFL_BUF
**
** Description:
**
** Attempt an ISAM rewrite operation without current ISAM IDfield buffer
** contents. No way to determine if IDfield has been changed. Rewrite fails.
*/
#define IDFL_BUF		922

/**
** Symbolic Constant: IERR_COD
**
** Description:
**
** An internal error has occurred; similar to a catastrophic terr. Instead
** of terminating execution, IERR_COD is returned, sysiocod is set to a
** local code, and a message is written into CTSTATUS.FCS.
*/
#define IERR_COD		923

/**
** Symbolic Constant: SADM_ERR
**
** Description:
**
** Only the super administrator user account (named ADMIN) can perform this
** operation. For example, only ADMIN can change ADMIN group membership.
*/
#define SADM_ERR		924

/**
** Symbolic Constant: SCMP_ERR
**
** Description:
**
** The c-tree client is attempting to use features of the SECURITY API function
** that this c-tree Server does not support. Update your c-tree Server.
*/
#define SCMP_ERR		925

/**
** Symbolic Constant: HLMT_ERR
**
** Description:
**
** The transaction history log scan terminated because the user-specified limit
** on the number of logs to scan was reached.
*/
#define HLMT_ERR		926

/**
** Symbolic Constant: PNST_ERR
**
** Description:
**
** The instance number of a partition does not match the instance number
** maintained for the partition by the host file. Typically the instance
** number of a partition is increased only when it has been purged and
** then a new partition (with the same raw partition number) is created;
** or an individual partition member has been rebuilt through a call
** to PTADMIN.
*/
#define PNST_ERR		927

/**
** Symbolic Constant: PMRB_ERR
**
** Description:
**
** Partitioned file rebuild did not successfully rebuild all partitions.
** See CTSTATUS.FCS for more details.
*/
#define PMRB_ERR		928

/**
** Symbolic Constant: PRBL_ERR
**
** Description:
**
** Partitioned file rebuild requires special support. Rebuilding the
** entire partitioned file requires ctPARTITION to be defined at compile
** time. Rebuilding an individual partition member may require ctPARTITIONinstnc
** to be defined at compile time, and the member rebuild must be initiated
** through PTADMIN().
*/
#define PRBL_ERR		929

/**
** Symbolic Constant: PNSX_ERR
**
** Description:
**
** Partition member instance # exceeds maximum of 255 for a non-huge
** partitioned file. Use RBLIFILX8 to rebuild the entire set of partitioned
** files.
*/
#define PNSX_ERR		930

/**
** Symbolic Constant: PALL_ERR
**
** Description:
**
** Could not rebuild only bad partitioned file components. Must rebuild
** entire partitioned file. Remove badpartIFIL from tfilno member of
** IFIL used in RBLIFILX8.
*/
#define PALL_ERR		931

/**
** Symbolic Constant: BMPW_ERR
**
** Description:
**
** The specified encryption master password is incorrect.
*/
#define BMPW_ERR		932

/**
** Symbolic Constant: ICOD_ERR
**
** Description:
**
** An encryption operation failed due to an unexpected internal error. See
** CTSTATUS.FCS for details.
*/
#define ICOD_ERR		933

/**
** Symbolic Constant: IICT_ERR
**
** Description:
**
** Encountered IICT operations without ctFeatIICT enabled. [IICT stands
** for Immediate Independent Commit Transaction: a single ISAM update
** operation treated as a separate transaction within an existing, pending
** transaction.]
*/
#define IICT_ERR		934

/**
** Symbolic Constant: IICT_FIL
**
** Description:
**
** File has already been updated within a transaction. Open the file with
** a different user file number and set IICT state with the new file number.
** Or, an add/rebuild index called for file previously placed in IICT state.
*/
#define IICT_FIL		935

/**
** Symbolic Constant: AREC_BUF
**
** Description:
**
** Could not allocate a buffer for an augmented variable length record
** operation (e.g., ctCMPREC).
*/
#define AREC_BUF		936

/**
** Symbolic Constant: AREC_SUP
**
** Description:
**
** Augmented record support not available (ctAUGREC / ctCMPREC / ctFeatFLEXREC)
*/
#define AREC_SUP		937

/**
** Symbolic Constant: AREC_DCM
**
** Description:
**
** Could not decompress the data record. sysiocod set to Z_xyz_ERROR.
*/
#define AREC_DCM		938

/**
** Symbolic Constant: AREC_ISM
**
** Description:
**
** Compressed record length files require ISAM update; not low level update.
*/
#define AREC_ISM		939

/**
** Symbolic Constant: AREC_NOP
**
** Description:
**
** Requested operation not supported for augmented records.
*/
#define AREC_NOP		940

/**
** Symbolic Constant: LSEC_ERR
**
** Description:
**
** This c-tree Server requires a secure logon that your c-tree client library
** does not support. Update your c-tree client library.
*/
#define LSEC_ERR		941

/**
** Symbolic Constant: LSES_ERR
**
** Description:
**
** This c-tree client uses a secure logon that your c-tree Server does not
** support. Update your c-tree Server.
*/
#define LSES_ERR		942

/**
** Symbolic Constant: TFLN_ERR
**
** Description:
**
** c-tree does not support a rebuild or compact option that you specified in
** the IFIL's tfilno field.
*/
#define TFLN_ERR		943

/**
** Symbolic Constant: AREC_MOD
**
** Description:
**
** Bad augmented record file mode at create. For example, specifying
** ctAugmentedFxd without ctVLENGTH.
*/
#define AREC_MOD		944

/**
** Symbolic Constant: AREC_FXD
**
** Description:
**
** Add/update varlen must match fixed length for file with ctAugmentedFxd
** specified at create.
*/
#define AREC_FXD		945

/**
** Symbolic Constant: CMPR_ERR
**
** Description:
**
** Error setting up compressiion routines. Check sysiocod for details:
**
**	sysiocod	explanation
**	--------	------------------------------------------------------
**	   1		non-zlib compression requires DLL
**	   2		bad version number
**	   3		inconsistent attrstr/attrlen
**	   4		DLL name Unicode conversion error
**	   5		DLL load error
**	 6->13		function name Unicode conversion error
**	14->21		failed to resolve function proc address
**	  32		type/version mismatch in FncInit()
**	  33		could not allocate attrval in FncInit()
**	  34		attrlen disagreement in FncInit()
**	  35		could not initialize compress context in CmpInit()
**	  36		could not initialize decompress context in ExpInit()
**	  37		invalid attrstr contents found by FncInit()
**	  38		could not allocate dedicated attrstr in ctSETCOMPRESS
**	1000+err	where err is a DLL specific unexpected error code
**			returned during CmpActn()/ExpActn()
**	2000+err	where err is a DLL specific code related to corrupted
**			input during a call to ExpActn()
*/
#define CMPR_ERR		946

/**
** Symbolic Constant: SMLO_ERR
**
** Description:
**
** An internal error code returned by the shared memory communication protocol
** receive function for Unix systems when the receive for a logoff operation
** fails on the semaphore wait. This is a normal occurrence if the c-tree
** Server has removed the semaphore set before the client read the response.
** In this case the client side code returns success.
*/
#define SMLO_ERR		947

/**
** Symbolic Constant: PMXS_ERR
**
** Description:
**
** Operation on partition host cannot be performed if partition members
** already exist. Operation must be performed after the host is created, but
** before any partition members are created.
*/
#define PMXS_ERR		948

/**
** Symbolic Constant: IEXS_ERR
**
** Description:
**
** The request to start an IICT failed because an IICT is already active.
*/
#define IEXS_ERR		949

/**
** Symbolic Constant: INON_ERR
**
** Description:
**
** The request to end an IICT failed because no IICT is active.
*/
#define INON_ERR		950

/**
** Symbolic Constant: IACT_ERR
**
** Description:
**
** The request to commit the transaction failed because an IICTxtd is active.
** First commit or abort the IICTxtd. You may also abort the transaction, which
** first aborts the IICTxtd.
*/
#define IACT_ERR		951

/**
** Symbolic Constant: ENCK_ERR
**
** Description:
**
** The current master encryption key's attributes are inconsistent with the
** master key used to encrypt the security resource of the specified file.
** For example, you might be using a 128-bit master key and are trying to
** read a file whose security resource was encrypted with a 256-bit master key.
*/
#define ENCK_ERR		952

/**
** Symbolic Constant: QTOC_ERR
**
** Description:
**
** A call to suspend a thread because of ctQUIET processing failed because
** the thread owned the file open/close semaphore.
*/
#define QTOC_ERR		953

/**
** Symbolic Constant: NCMP_ERR
**
** Description:
**
** Compacting a partitioned file is not supported.
*/
#define NCMP_ERR		954

/**
** Symbolic Constant: DOTX_ERR
**
** Description:
**
** Attempt to acquire internal mutex, ctpdotsema, out of order.
** Unexpected error, contact FairCom.
*/
#define DOTX_ERR		955

/**
** Symbolic Constant: APND_ERR
**
** Description:
**
** Partition member pending archive
*/
#define APND_ERR		956

/**
** Symbolic Constant: DMAP_ERR
**
** Description:
**
** This index file is already mapped to a different data file.
*/
#define DMAP_ERR		957

/**
** Symbolic Constant: IMIS_ERR
**
** Description:
**
** Data record is missing identity field value.
*/
#define IMIS_ERR		958

/**
** Symbolic Constant: LSEV_ERR
**
** Description:
**
** This c-tree client uses a different secure logon version than your
** c-tree Server. Update your c-tree client.
*/
#define LSEV_ERR		959

/**
** Symbolic Constant: LAUT_ERR
**
** Description:
**
** c-tree license authorization failed. Check CTSTATUS.FCS for error message.
*/
#define LAUT_ERR		960

/**
** Symbolic Constant: PWDC_ERR
**
** Description:
**
** This c-tree Server requires a secure password transmission method that your
** c-tree client library does not support. Update your c-tree client library.
*/
#define PWDC_ERR		961

/**
** Symbolic Constant: PWDS_ERR
**
** Description:
**
** This c-tree client uses a secure password transmission method that your
** c-tree Server does not support. Update your c-tree Server.
*/
#define PWDS_ERR		962

/**
** Symbolic Constant: LISM_ERR
**
** Description:
**
** An attempt to close an ISAM data file with the low level file close
** routine CLSFIL.
**
** COMPATIBILITY CLSFIL_ISAM restores the old behavior when CLSFIL
** is called for an ISAM data file. For stand alone applications
** the CLSFIL behavior can be restored by compiling the code with
** NO_ctBEHAV_CLSFIL_ISAM.
*/
#define LISM_ERR		963

/**
** Symbolic Constant: SCNT_ERR
**
** Description:
**
** Pre-image space overflow of image update count. Each update of
** a record location, within a single transaction, causes the pre-image
** update count to be incremented. Repeated update of the same record
** within the transaction eventually overflows the update count.
*/
#define SCNT_ERR		964

/**
** Symbolic Constant: BCOD_ERR
**
** Description:
**
** c-tree Server was not able to decrypt the buffer sent to it by the client.
** This is an unexpected error. Contact FairCom support.
*/
#define BCOD_ERR		965

/**
** Symbolic Constant: BORD_ERR
**
** Description:
**
** c-tree was compiled with the wrong byte order for this platform.
*/
#define BORD_ERR		966

/**
** Symbolic Constant: ULMT_ERR
**
** Description:
**
** Logon is denied because this user account has reached its maximum number of
** concurrent logons.
*/
#define ULMT_ERR		967

/**
** Symbolic Constant: GLMT_ERR
**
** Description:
**
** Logon is denied because one of the groups for this user account has reached
** its maximum number of concurrent logons.
*/
#define GLMT_ERR		968

/**
** Symbolic Constant: QTBK_THD
**
** Description:
**
** Attempt to suspend the thread that invoked ctQUIET. Such a suspension
** would hang the server. sysiocod is set to the type of suspension request
** such as ctQTtranbeg; or to a negative cterrc.h entry such as LWRT_COD.
*/
#define QTBK_THD		969

/**
** Symbolic Constant: ISAM_MUSR_ERR
**
** Description:
**
** The connection attempt has been rejected because it would exceed the
** maximum number of concurrent ISAM connections allowed.
*/
#define ISAM_MUSR_ERR		970

/**
** Symbolic Constant: SQL_MUSR_ERR
**
** Description:
**
** The connection attempt has been rejected because it would exceed the
** maximum number of concurrent SQL connections allowed.
*/
#define SQL_MUSR_ERR		971

/**
** Symbolic Constant: PRTL_COD
** Symbolic Constant: PRTL_FF
**
** Description:
**
** sysiocod is set to PRTL_COD if rebuild detects a partial record (or
** resource) at the end of a truncated data file. If the purgeIFIL option
** is used, a copy of the partial record is placed in a temporary file; the
** record is overwritten with 0xff bytes; and sysiocod is set to PRTL_FF.
** If the record is successfully dumped to the temporary file, but there is
** a problem overwriting the partial record with 0xff bytes, sysiocod will
** be set to PRTL_COD not PRTL_FF.
**
** Whether or not the purge option is used, CTSTATUS.FCS contains the byte
** offset and length of the partial record.
*/
#define PRTL_COD		-972
#define PRTL_FF			-973

/**
** Symbolic Constant: LWRT_COD
**
** Description:
**
** Attempt to write to log files when ctQTblockLogFiles is in force.
*/
#define LWRT_COD		-974


#define FNOP_COD	-975	/**< sysiocod value to indicate to caller of file
				   open that the file is not already open. */
#define FNOR_COD	-976	/**< sysiocod value to indicate to the caller of
				   ctrcvopn81() that FNOP_ERR occurred because
				   the file is not on the dump recovery list. */

/**
** Symbolic Constant: XATO_ERR
**
** Description:
**
** File create called with a segmax > 1 but without ctSEGAUTO bit set in
** x8mode. segmax and x8mode are members of XCREblk.
*/
#define XATO_ERR		977

/**
** Symbolic Constant: SHMP_ERR
**
** Description:
**
** A shared memory connection could not be established because the system denied
** access to the client process. For example, if a client is run as a Windows
** service and c-tree Server is not run as a Windows service (or vice-versa),
** Windows does not allow c-tree Server the access to the client process which
** is needed to establish the shared memory connection.
*/
#define SHMP_ERR		978

/**
** Symbolic Constant: FLIC_ERR
**
** Description:
**
** c-tree is not licensed to use this feature.
*/
#define FLIC_ERR		979

/**
** Symbolic Constant: KEYX_ERR
**
** Description:
**
** Secure key exchange failed. See CTSTATUS.FCS for details.
*/
#define KEYX_ERR		980

/**
** Symbolic Constant: CDLL_ERR
**
** Description:
**
** Could not load the specified DLL or shared library. See CTSTATUS.FCS for
** details.
*/
#define CDLL_ERR		981

/**
** Symbolic Constant: CDLF_ERR
**
** Description:
**
** Could not resolve the specified function name in the specified DLL or
** shared library. See CTSTATUS.FCS for details.
*/
#define CDLF_ERR		982

/**
** Symbolic Constant: IICT_A3T
**
** Description:
**
** client / server mismatch on IICTxtd communications
*/
#define IICT_A3T		983

/**
** Symbolic Constant: ALMT_ERR
**
** Description:
**
** Logon is denied because the number of distinct user accounts that are allowed
** to be connected at one time has been reached.
*/
#define ALMT_ERR		984

/**
** Symbolic Constant: LDRQ_ERR
**
** Description:
**
** Logon is denied because this user account requires LDAP authentication, but
** c-tree Server has not enabled LDAP authentication.
*/
#define LDRQ_ERR		985

/**
** Symbolic Constant: UNKA_ERR
**
** Description:
**
** The specified user account authentication type is invalid or not supported.
*/
#define UNKA_ERR		986

/**
** Symbolic Constant: LRUB_ERR
**
** Description:
**
** LRU scheme for index buffers did not find an available index buffer. Most
** likely caused by a low IDX_MEMORY
*/
#define LRUB_ERR		987

/**
** Symbolic Constant: CLSF_COD
**
** Description:
**
** Internal routine try_FBclsfile successfully closed a low level index
** file during an ISAM file block.
*/
#define CLSF_COD		-988

/**
** Symbolic Constant: OPNF_COD
**
** Description:
**
** Internal routine try_FBopnfile successfully re-opened a low level index
** file during an ISAM file block.
*/
#define OPNF_COD		-989

/**
** Symbolic Constant: DPRT_NSUP_ERR
**
** Description:
**
** This operation is not supported for a dynamic partitioned file.
*/
#define DPRT_NSUP_ERR		990

/**
** Symbolic Constant: DPRT_NOMBR_ERR
**
** Description:
**
** No partition members have been associated with this dynamic partition
** host file.
*/
#define DPRT_NOMBR_ERR		991

/**
** Symbolic Constant: ALGN_ERR
**
** Description:
**
** Client cannot correct difference between client alignment and the
** alignment of the data file on disk.
*/
#define ALGN_ERR		992

/**
** Symbolic Constant: DPRT_DDIF_ERR
**
** Description:
**
** The table, index, record, or field definitions of the partition member differ
** from those of the dynamic partition host file.
*/
#define DPRT_DDIF_ERR		993

/**
** Symbolic Constant: SCNV_ERR
**
** Description:
**
** Server does not support server-side record image conversion.
*/
#define SCNV_ERR		994

/**
** Symbolic Constant: VSSI_ERR
**
** Description:
**
** Unable to initialize VSS writer support. See CTSTATUS.FCS for details.
*/
#define VSSI_ERR		995

/**
** Symbolic Constant: MOFL_ERR
**
** Description:
**
** The MULTIOPN_DIFUSR/SAMUSR setting cannot be changed on this file because
** this connection has other open instances of this file that are using a
** different MULTIOPN_DIFUSR/SAMUSR  setting than the one specified by the
** caller, or this file has pending locks.
*/
#define MOFL_ERR		996

/**
** Symbolic Constant: RTGTRM_ERR
**
** Description:
**
** A user-defined callback function terminated the RTG operation.
*/
#define RTGTRM_ERR		997

/**
** Symbolic Constant: MUOP_RCR
**
** Description:
**
** Attempt to perform multiple file open (co-file) with active recursive locks
** on the file.
*/
#define MUOP_RCR		998

/**
** Symbolic Constant: MLOK_ERR
**
** Description:
**
** Recursive data file lock not allowed if user has opened the file multiple
** times (co-files).
*/
#define MLOK_ERR		999

/**
** Symbolic Constant: IDFL_MOD
**
** Description:
**
** Could not enable the specified identity field mode due to a conflicting mode
** that is already in effect. For example, identity field override and identity
** field preservation are mutually exclusive.
*/
#define IDFL_MOD		1000

/**
** Symbolic Constant: NOISMKEYUPD_ERR
**
** Description:
**
** Could not update the specified key value because this index does not allow
** an ISAM record update to change the key value.
*/
#define NOISMKEYUPD_ERR		1001

/**
** Symbolic Constant: IDVR_ERR
**
** Description:
**
** IDfield overflows (or underflows if delta is negative)
*/
#define IDVR_ERR		1002

/**
** Symbolic Constant: IDXA_ERR
**
** Description:
**
** Invalid IDfield extended attribute (xtdatr)
**
**	sysiocod indicates the validation issue:
**		1	mutually exclusive attributes
**		2	specified version incompatible with other attributes
**		3	if version reset to 0, no other attributes allowed
**		4	cannot turn off overflowed indicator unless the
**			no overflow detection attribute is turned on
**		5	cannot turn on the overflowed indicator unless the
**			no overflow detection attribute is off
**		6	IDfield_xtdatr_versn__1 requires IDfield_xtdatr_noovrflw
*/
#define IDXA_ERR		1003

/**
** Symbolic Constant: IBLK_ERR
**
** Description:
**
** File is temporarily blocked from being opened by an internal thread.
*/
#define IBLK_ERR		1004

/**
** Symbolic Constant: SINT_ERR
**
** Description:
**
** System-dependent initialization failed. See CTSTATUS.FCS for details.
*/
#define SINT_ERR		1005

/**
** Symbolic Constant: COFL_ERR
**
** Description:
**
** All co-file opens for a given file by the same thread must agree
** on the ctXOPN_COFILE_FILELOCK attribute.
*/
#define COFL_ERR		1006

/**
** Symbolic Constant: COFS_ERR
**
** Description:
**
** SUPERFILE hosts cannot be opened as co-files [i.e., same SUPERFILE cannot
** be opened by the same user with different file numbers]. When members of
** a SUPERFILE are opened, the open request does not use the SUPERFILE host
** user file number.
*/
#define COFS_ERR		1007

/**
** Symbolic Constant: COFP_ERR
**
** Description:
**
** Partition Hosts cannot be opened as co-files [i.e., same Partition Host
** cannot be opened by the same user with different file numbers].
*/
#define COFP_ERR		1008

/**
** Symbolic Constant: COFL_COD
**
** Description:
**
** Special internal file open cannot use ctXOPN_COFILE_FILELOCK attribute.
*/
#define COFL_COD		-1009

/**
** Symbolic Constant: DTPC_ERR
**
** Description:
**
** This file uses data types that your client library does not support.
** Update your client library.
*/
#define DTPC_ERR		1010

/**
** Symbolic Constant: DTPS_ERR
**
** Description:
**
** This client library uses data type support that your server does not support.
** Update your c-tree Server.
*/
#define DTPS_ERR		1011

/**
** Symbolic Constant: SCRIT_STATE_ERR
**
** Description:
**
** The Shared Critical has an unexpected internal state.
*/

#define SCRIT_STATE_ERR 	1012

/**
** Symbolic Constant: SCPY_ERR
**
** Description:
**
** The file copy API function does not allow copying a FairCom system file.
*/
#define SCPY_ERR		1013

/**
** Symbolic Constant: DCPY_ERR
**
** Description:
**
** When using the file copy API option to copy files to a new directory, the
** source data and index files must all reside in one directory.
*/
#define DCPY_ERR		1014

/**
** Symbolic Constant: CBKTRM_ERR
**
** Description:
**
** A user-defined callback function terminated the operation.
*/
#define CBKTRM_ERR		1015

/**
** Symbolic Constant: GFSZ_ERR
**
** Description:
**
** Error getting file size. Check sysiocod for system error code value.
*/
#define GFSZ_ERR		1016

/**
** Symbolic Constant: FDIF_ERR
**
** Description:
**
** The file comparison detected differences between the two files.
*/
#define FDIF_ERR		1017

/**
** Symbolic Constant: XPND_ERR
**
** Description:
**
** The specified operation cannot be completed because an index exists that has
** not yet been made permanent. Physically close the data file so that the index
** can be made permanent.
*/
#define XPND_ERR		1018

/**
** Symbolic Constant: TUXP_ERR
**
** Description:
**
** Transaction log entry has valid transaction type but unexpected contents.
*/
#define TUXP_ERR		1019

/**
** Symbolic Constant: NORP_ERR
**
** Description:
**
** DELAYED_DURABILITY on at time of system crash, and RECOVER_TO_RESTORE_POINT
** YES entry in configuration at time of automatic recovery, and no active
** restore points. To avoid NORP_ERR, and recovery without a rollback to the
** last active restore point, enter RECOVER_TO_RESTORE_POINT NO in the
** configuration.
*/
#define NORP_ERR		1020

/**
** Symbolic Constant: NORB_ERR
**
** Description:
**
** DELAYED_DURABILITY on at time of system crash and active restore points exist,
** but no RECOVER_TO_RESTORE_POINT entry in configuration at time of
** automatic recovery. To avoid NORB_ERR, and recovery without a rollback
** to the last active restore point, enter RECOVER_TO_RESTORE_POINT NO in
** the configuration. To startup the server and rollback to the last active
** restore point, enter RECOVER_TO_RESTORE_POINT YES in the configuration.
*/
#define NORB_ERR		1021

/**
** Symbolic Constant: XMLP_ERR
**
** Description:
**
** Failed to parse the XML file. Check error message buffer for details.
*/
#define XMLP_ERR		1022

/**
** Symbolic Constant: XMLI_ERR
**
** Description:
**
** The XML document was successfully parsed, but an error occurred when interpreting
** the contents of the XML document. Check error message buffer for details.
*/
#define XMLI_ERR		1023

/**
** Symbolic Constant: DLKT_COD
**
** Description:
**
** sysiocod value: Could not obtain data record lock because the table is
** locked, or a request to lock the table is pending.
*/
#define DLKT_COD		-1024

/**
** Symbolic Constant: TLOK_ERR
**
** Description:
**
** Could not obtain table lock because the table is locked, or a request to lock
** the table is pending, or a conflicting data record read or write lock exists.
*/
#define TLOK_ERR		1025

/**
** Symbolic Constant: REDT_ERR
**
** Description:
**
** Could not update the table because the table is locked. NOTE: This error code
** is no longer used.
*/
#define REDT_ERR		1026

/**
** Symbolic Constant: LWRP_ERR
**
** Description:
**
** Lightweight Restore Point cannot be used in this context (e.g., as a
** Roll Forward target).
*/
#define LWRP_ERR		1027

/**
** Symbolic Constant: RPSK_ERR
**
** Description:
**
** The skip forward information stored in a Restore Point (during a recovery
** to a Restore Point) is inconsistent with the state of the log files during
** a subsequent roll forward operation.
*/
#define RPSK_ERR		1028

/**
** Symbolic Constant: UPDM_COD
**
** Description:
**
** UPDM_COD indicates that an index node split has been deferred, the
** key marks cleaned up to the extent possible, and the add key will be retried.
**
** ctBEHAV_UPDMARKSsplit
*/
#define UPDM_COD		-1029

/**
** Symbolic Constant: MACT_ERR
**
** Description:
**
** Maximum concurrent active connections exceeded.
*/
#define MACT_ERR		1030

/**
** Symbolic Constant: QTFA_ERR
**
** Description:
**
** A call to ctQUIET() failed because the ctQTfailAfterTimeout option was
** specified and transactions remained active after the specified timeout
** period elapsed.
*/
#define QTFA_ERR		1031

/**
** Symbolic Constant: RBAD_ERR
**
** Description:
**
** A call to ALCRNG() failed because improper options were specified. Check
** sysiocod for one of the following values:
*/
#define RBAD_ERR		1032

/* ALGRNG() RBAD_ERR return sysiocod values: */
#define RNGS_COD	1	/* Negative segment count, or no lower range.*/
#define RSGB_COD	2	/* The CTIX_SSG and CTIX_ESG options cannot
				be specified together.			     */
#define RSGE_COD	3	/* Must end current segment group before
				starting another segment group.		     */
#define RSGO_COD	4	/* The current segment's operator does not
				match the current segment group's operator.  */
#define RSGM_COD	5	/* The current segment's segment mode does not
				match the current segment group's operator.  */
#define RSGN_COD	6	/* Not in a segment group, but the end segment
				group option was specified.		     */
#define RNGO_COD	7	/* Operators out of range, or between operator
				requires upper range value.		     */
#define RSGD_COD	8	/* Missing end segment group operator.	     */
#define RNGU_COD	9	/* Unsupported operator value.		     */

/**
** Symbolic Constant: QREP_COD
**
** Description:
**
** sysiocod value when ctReplGetNextChange() returns NTIM_ERR and quiesce is
** waiting for replication readers to finish process committed transactions.
*/
#define QREP_COD		-1033

/**
** Symbolic Constant: SEQFIL_ERR
**
** Description:
**
** The sequence file is not available because it could not be created or
** converted to the current format. Check CTSTATUS.FCS for error messages.
*/
#define SEQFIL_ERR		1034

/**
** Symbolic Constant: DFOP_ERR
**
** Description:
**
** Failed to parse output of DISK_FULL_ACTION script.
*/
#define DFOP_ERR		1035

/**
** Symbolic Constant: SEQNCR_ERR
**
** Description:
**
** The sequence was created with the requirement that ctGetNextSequenceValue()
** must be called before ctGetCurrentSequenceValue() is called.
*/
#define SEQNCR_ERR		1036

/**
** Symbolic Constant: SCHV_ERR
**
** Description:
**
** Failed to replicate a record add, delete, or update operation because the
** source record image contains a record schema ID that does not match the
** record schema ID in the target data file.
*/
#define SCHV_ERR		1037

#define CTJSON_NOT_JSON		-1038 /* Not a valid JSON object */
#define CTJSON_NOT_OBJECT	-1039 /* Valid JSON, but not an object */
#define CTJSON_UNSUPPORTED_TYPE	-1040 /* The specified key data type is not supported */

/**
** Symbolic Constant: RUCBDLL_NOT_LOADED_COD
**
** Description:
**
** sysiocod value when a file open succeeds even though the record update
** callback DLL was not loaded for data file.
*/
#define RUCBDLL_NOT_LOADED_COD	-1041

/**
** Symbolic Constant: FORCE_BLOCKING_LOCK_COD
**
** Description:
**
** sysiocod value set internally when a non-blocking lock request is forced to
** block.
*/
#define FORCE_BLOCKING_LOCK_COD	-1042

/**
** Symbolic Constant: FILE_ALREADY_OPEN_COD
**
** Description:
**
** sysiocod value set when a caller requested to know that the file is already open.
*/
#define FILE_ALREADY_OPEN_COD	-1043

/******************************************************************************/
/*
** NOTE: Error codes 1001 through 1048 are already used by the SA_ADMIN API, so
** it is recommended to avoid defining new c-tree error code values here that
** would duplicate those values.
*/
/******************************************************************************/


/**
** Symbolic Constant: WMEM_ERR
**
** Description:
**
** Not able to allocate memory for HTTP server
*/
#define WMEM_ERR		1100

/**
** Symbolic Constant: WCRE_ERR
**
** Description:
**
** Not able to create HTTP server
*/
#define WCRE_ERR		1101

/**
** Symbolic Constant: WCFG_ERR
**
** Description:
**
** Not able to set HTTP config
*/
#define WCFG_ERR		1102

/**
** Symbolic Constant: COFM_ERR
**
** Description:
**
** The file cannot be opened because this connection already has it open the
** maximum number of times.
*/
#define COFM_ERR		1103

/**
** Symbolic Constant: SSLCONN_ERR
**
** Description:
**
** SSL connection attempt failed.
*/
#define SSLCONN_ERR		1104

/**
** Symbolic Constant: REPCNF_ERR
**
** Description:
**
** A conflict was detected when applying a replicated record update.
*/
#define REPCNF_ERR		1105

/**
** Symbolic Constant: HUPD_ERR
**
** Description:
**
** Unable to add a member index to a ctTRNLOG host index because the host index
** has been updated. Physically close and reopen the host index, and then add
** the new member index.
*/
#define HUPD_ERR		1106

/**
** Symbolic Constant: DCPT_ERR
**
** Description:
**
** A Ctree Data file has corrupted data. 
** Restore to a backup.  A rebuild may be able to restore the 
** file to a functional state with some data loss.
** 
*/
#define DCPT_ERR		1107

/**
** Symbolic Constant: CTDR_ERR
**
** Description:
**
** Not able to create a temporary directory.
** Please refer to sysiocod in order to check the File System
** error code.
**
*/
#define CTDR_ERR		1108

/**
** Symbolic Constant: DTDR_ERR
**
** Description:
**
** Not able to delete a temporary directory.
** Please refer to sysiocod in order to check the File System
** error code.
**
*/
#define DTDR_ERR		1109

/**
** Symbolic Constant: NTDR_ERR
**
** Description:
**
** Not a temporary directory. In order to be considered a temporary 
** directory, it must be created by the ctTempDir() interface.
**
*/
#define NTDR_ERR		1110

/**
** Symbolic Constant: NORF_ERR
**
** Description:
**
** A restore point rollforward was requested, but the restore 
** point checkpoint was not found in the transaction logs.
** The required transaction logs are not present.
**
*/
#define NORF_ERR		1111

/**
** Symbolic Constant: FFTI_COD
**
** Description:
**
** sysiocod value when the FNOP_ERR error is caused by missing FTI file(s)
*/
#define FFTI_COD		-1112

/**
** Symbolic Constant: FTIP_ERR
**
** Description:
**
** The full text index is not currently accessible due to index definition
** changes that are pending commit. Commit the current transaction before
** accessing the full text index.
*/
#define FTIP_ERR		1113

/**
** Symbolic Constant: NAUT_ERR
**
** Description:
**
** The RTG client is not authorized to connect to the server.
** Check license restrictions on allowed RTG clients.
*/
#define NAUT_ERR		1114 

/**
** Symbolic Constant: ROSV_ERR
**
** Description:
**
** The server is set in readonly mode.
** operation denied.
*/
#define ROSV_ERR		1115 

/**
** Symbolic Constant: PWDEXP_ERR
**
** Description:
**
** This user account has been disabled because its password has expired.
*/
#define PWDEXP_ERR		1116

/**
** Symbolic Constant: PWDLEN_ERR
**
** Description:
**
** The specified password does not meet the minimum length requirement.
*/
#define PWDLEN_ERR		1117

/**
** Symbolic Constant: PWDCLS_ERR
**
** Description:
**
** The specified password does not contain the required number of character classes.
*/
#define PWDCLS_ERR		1118

/**
** Symbolic Constant: RCVREN_ERR
**
** Description:
**
** During automatic recovery, this error code indicates that the specified file
** is not open, but a renamed version of it is open. This error code is used
** internally and does not necessarily indicate an error situation.
*/
#define RCVREN_ERR		1119

/**
** Symbolic Constant: RCVTFL_ERR
**
** Description:
**
** Automatic recovery failed due to an unexpected error mapping a transaction
** file number to a c-tree file number.
*/
#define RCVTFL_ERR		1120

/**
** Symbolic Constant: OPNSID_ERR
**
** Description:
**
** Failed to open the specified file because its system file ID could not be
** read. Check sysiocod for system error code value.
*/
#define OPNSID_ERR		1121

/**
** Symbolic Constant: JSON_KTFM_ERR
**
** Description:
**
** CT_JSON key transformation failed. Check sysiocod for details. See CTJSON_*
** definitions.
*/
#define JSON_KTFM_ERR		1122

/**
** Symbolic Constant: QCVR_ERR
**
** Description:
**
** An old ctree client version is attempting to use an incompatible system queue api.  Update
** the ctree client.
** 
*/
#define QCVR_ERR		1123

/**
** Symbolic Constant: QSVR_ERR
**
** Description:
**
** A ctree client has attempted to use an incompatible system queue api on an older server. Update
** the ctree server.
** 
*/
#define QSVR_ERR		1124

/**
** Symbolic Constant: NICU_ERR
**
** Description:
**
** A partial or invalid unicode byte sequence has been supplied as a unicode character
** 
*/
#define NICU_ERR		1125

/**
** Symbolic Constant: BICU_ERR
**
** Description:
**
** An ICU error has occurred during unicode string conversion
** 
*/
#define BICU_ERR		1126


/**
** Symbolic Constant: DSYN_ERR
**
** Description:
**
** dynamic dump script syntax error
** 
*/
#define DSYN_ERR		1127


/**
** Symbolic Constant: DNAM_ERR
**
** Description:
**
** File name too long
** 
*/
#define DNAM_ERR		1128

/**
** Symbolic Constant: FCYC_ERR
**
** Description:
**
** A filesystem loop or cycle has been encountered.
** 
*/
#define FCYC_ERR		1129

/**
** Symbolic Constant: POPN_ERR
**
** Description:
**
** File open or create failed because the file is in a pending open state and
** the pending open retry limit has been exceeded.
** 
*/
#define POPN_ERR		1130

/**
** Symbolic Constant: LCOD_ERR
**
** Description:
**
** The transaction log cannot be read because it is encrypted with advanced
** encryption, and either advanced encryption or log encryption is off. Enable
** advanced encryption and log encryption to proceed.
** 
*/
#define LCOD_ERR		1131

/**
** Symbolic Constant: LCAM_ERR
**
** Description:
**
** The transaction log cannot be read because it is camouflaged, and either
** advanced encryption is on, or log camouflage is off. Enable the log
** camouflage option and turn off advanced encryption to proceed.
** 
*/
#define LCAM_ERR		1132

/**
** Symbolic Constant: LEOF_WARN
**
** Description:
**
** ctVerifyFile found unexpected data beyond the logical
** end of file.  This is unlikely to cause problems by itself,
** but might indicate prior data loss or corruption. 
** 
*/
#define LEOF_WARN		1133

/**
** Symbolic Constant: PEOF_WARN
**
** Description:
**
** ctVerifyFile found a discrepancy between end of file tracked in the header
** and the actual file size.  This is unlikely to cause problems by itself,
** but might indicate prior data corruption. 
** 
*/
#define PEOF_WARN		1134

/**
** Symbolic Constant: ISORT_ERR
**
** Description:
**
** Consistency check during sorting failed. 
** Contact FairCom.
** 
*/
#define ISORT_ERR		1135

/**
** Symbolic Constant: FBTU_ERR
**
** Description:
**
** File block failed because the file has been updated in an active transaction
** and the caller requested that the file block should fail in this situation
** instead of aborting the transaction.
*/
#define FBTU_ERR		1136

/**
** Symbolic Constant: CBPO_ERR
**
** Description:
**
** File open wait for a pending conditional index callback initialization timed out.
** Was callback initialization waiting on this operation? 
** Retry the open later.
**
*/
#define CBPO_ERR		1137

/**
** Symbolic Constant: APICOMPAT_ERR
**
** Description:
**
** c-tree initialization failed because the c-tree library's API definition
** is not compatible with the application's compile time options. For example,
** the client library might be using 4-byte file numbers but the application
** is compiled to use 2-byte file numbers.
*/
#define APICOMPAT_ERR		1138

/**
** Symbolic Constant: SRVFILNO_ERR
**
** Description:
**
** The connection attempt failed because the c-tree client library is using
** 4-byte file numbers but the server is using 2-byte file numbers.
*/
#define SRVFILNO_ERR		1139

/**
** Symbolic Constant: TRNU_ERR
**
** Description:
**
** Compact to truncate failed because the file has been updated in an active transaction
*/
#define TRNU_ERR		1140

/**
** Symbolic Constant: PDESC_ERR
**
** Description:
**
** Plugin callback request doesn't match plugin library
*/

#define PDESC_ERR		1141

/**
** Symbolic Constant: PLOAD_ERR
**
** Description:
**
** Plugin callback library failed to load. Check CTSTATUS
*/

#define PLOAD_ERR		1142

/**
** Symbolic Constant: PLINK_ERR
**
** Description:
**
** Plugin callback unable to link function
*/

#define PLINK_ERR		1143

/**
** Symbolic Constant: SMIV_ERR
**
** Description:
**
** An internal error code returned by the shared memory communication protocol
** When an inconsistent shared memory state is detected.
*/
#define SMIV_ERR		1144

/**
** Symbolic Constant: FORCE_DIAG_ERR
**
** Description:
**
** The function call returned an error due to a request by a diagnostic option.
*/
#define FORCE_DIAG_ERR		1145

/**
** Symbolic Constant: ATTR_NOTFOUND_ERR
**
** Description:
**
** Attribute not found / end of iterator scan.
*/
#define ATTR_NOTFOUND_ERR 1146

/**
** Symbolic Constant: ATTR_INVHDL_ERR
**
** Description:
**
** Invalid handle type.
*/
#define ATTR_INVHDL_ERR 1147 

/**
** Symbolic Constant: ATTR_NOMEM_ERR
**
** Description:
**
** memory exhausted
*/
#define ATTR_NOMEM_ERR 1148 

/**
** Symbolic Constant: ATTR_INVALID_ERR
**
** Description:
**
** attribute unkown or not applicable to the handle
*/
#define ATTR_INVALID_ERR 1149 

/**
** Symbolic Constant: ATTR_INTERNAL_ERR
**
** Description:
**
** internal resource text parsing/handling  error
*/
#define ATTR_INTERNAL_ERR 1150 

/**
** Symbolic Constant: ATTR_INVITR_ERR
**
** Description:
**
** invalid iterator
*/
#define ATTR_INVITR_ERR 1151

/**
** Symbolic Constant: ATTR_INVIDX_ERR
**
** Description:
**
** item index out of range
*/
#define ATTR_INVIDX_ERR 1152 

/**
** Symbolic Constant: ATTR_NOTSUP_ERR
**
** Description:
**
** unsupported resource version / unsupported operation.
*/
#define ATTR_NOTSUP_ERR 1153 

/**
** Symbolic Constant: ATTR_ASSOC_ERR
**
** Description:
**
** Handle already added to a parent handle
*/
#define ATTR_ASSOC_ERR 1154 

/**
** Symbolic Constant: REPL_NOBASEDIR_ERR
**
** Description:
**
** The source server's base directory has not been set for replication.
*/
#define REPL_NOBASEDIR_ERR 1155

/**
** Symbolic Constant: RCPT_ERR
**
** Description:
**
** A Ctree Data file has a corrupted resource definition.
** 
*/
#define RCPT_ERR 1156

/**
** Symbolic Constant: LONG8_NSUP_ERR
**
** Description:
**
** The operation is not supported because it requires native 64-bit integer support.
** 
*/
#define LONG8_NSUP_ERR 1157

/**
** Symbolic Constant: SQL_LOGON_BLOCKED_ERR
**
** Description:
**
** SQL connection is blocked from logon due to server startup logon block.
*/
#define SQL_LOGON_BLOCKED_ERR 1158

/**
** Symbolic Constant: SERVER_FAILOVER_ERR
**
** Description:
**
** The connection to the c-tree Server has been lost and this server has failed
** over to another server.
*/
#define SERVER_FAILOVER_ERR 1159

/**
** Symbolic Constant: SERVER_LOGON_REQUIRES_MD5
**
** Description:
**
** The server logon protocol requires MD5 hash support but this library does not support MD5 hash.
*/
#define SERVER_LOGON_REQUIRES_MD5 1160

/**
** Symbolic Constant: CLIENT_LOGON_REQUIRES_SHA512
**
** Description:
**
** The client logon protocol requires SHA512 hash support but the server does not support it. Upgrade server or downgrade client.
*/
#define CLIENT_LOGON_REQUIRES_SHA512 1161

/**
** Symbolic Constant: DUMP_ABANDONED_ERR 
**
** Description: The dynamic dump gave up due to !DELAY setting and active transactions.
**
*/
#define DUMP_ABANDONED_ERR 1162

/**
** Symbolic Constant: INVALID_REGULAR_EXPRESSION
**
** Description: The specified value is not a valid regular expression.
**
*/
#define INVALID_REGULAR_EXPRESSION 1163

/**
** Symbolic Constant: MAX_WORKER_ERR
**
** Description: A worker thread could not attach to the database engine because the worker thread limit has been reached.
*/
#define MAX_WORKER_ERR 1164	/**< Maximum worker threads exceeded */

/******************************************************************************/
/*
** REMEMBER TO UPDATE ctreeSDK\ctreeAPI\ctree\include\dherrors.h file in the
** 17XXX area 
*/
/******************************************************************************/

#endif /* ~ctERRCH */

/* end of cterrc.h */
