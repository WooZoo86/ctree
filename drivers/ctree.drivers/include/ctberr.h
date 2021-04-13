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

#ifndef ctBERRH
#define ctBERRH

#define	BT_NO_ERROR	0	/* No Error */

#define	BT_FMOD_ERR	1	/* Invalid Operation */
#define	BT_IOER_ERR	2	/* I/O error */
#define	BT_FOPN_ERR	3	/* File Not Open */
#define	BT_INOT_ERR	4	/* Key value Not Found */
#define	BT_KDUP_ERR	5	/* Key Dup error */
#define	BT_BKEY_ERR	6	/* Invalid Key Number */
#define	BT_SKEY_ERR	7	/* Different Key Number */
#define	BT_ICUR_ERR	8	/* Invalid Positioning */
#define	BT_KEOF_ERR	9	/* END-OF-FILE */
#define	BT_KMOD_ERR	10	/* Modifiable Key Value Error */
#define	BT_FNAM_ERR	11	/* Invalid Filename */
#define	BT_FNOP_ERR	12	/* File Not Found */
#define	BT_EXFL_ERR	13	/* Extended File Error */
#define	BT_PNOP_ERR	14	/* Pre-Image Open Error */
#define	BT_PIIO_ERR	15	/* Pre-Image I/O Error */
#define	BT_EXPN_ERR	16	/* Expansion Error */
#define	BT_FCLS_ERR	17	/* Close Error */
#define	BT_DFUL_ERR	18	/* Disk Full */
#define	BT_FCRP_ERR	19	/* Unrecoverable Error */
#define	BT_FINT_ERR	20	/* Record Manager Inactive */
#define	BT_KBLN_ERR	21	/* Key Buffer Length error */
#define	BT_DTLN_ERR	22	/* Data Buffer Length error */
#define	BT_PBLN_ERR	23	/* Position Block Length error */
#define	BT_PGSZ_ERR	24	/* Page Size error */
#define	BT_FCRE_ERR	25	/* Create I/O error */
#define	BT_NBRK_ERR	26	/* Number of keys error */
#define	BT_KSEG_ERR	27	/* Invalid key position */
#define	BT_RLEN_ERR	28	/* Invalid record length */
#define	BT_KLEN_ERR	29	/* Invalid key length */
#define	BT_BTFL_ERR	30	/* Not A Btrieve File */
#define	BT_EXTD_ERR	31	/* File Already Extended */
#define	BT_EXIO_ERR	32	/* Extended I/O Error */

#define	BT_EXNM_ERR	34	/* Invalid Expansion Name */
#define	BT_CDIR_ERR	35	/* Directory Error */
#define	BT_TRNS_ERR	36	/* Transaction Error */
#define	BT_ATRN_ERR	37	/* Transaction Is active */
#define	BT_TCIO_ERR	38	/* Transaction Control File I/O Error*/
#define	BT_PNDG_ERR	39	/* End/Abort Transaction Error*/
#define	BT_MTRN_ERR	40	/* Transaction Max Files */
#define	BT_ILOP_ERR	41	/* Operation Not Allowed */
#define	BT_IACC_ERR	42	/* Incomplete Accelerated Access */
#define	BT_IPTR_ERR	43	/* Invalid Record Address */
#define	BT_NLKP_ERR	44	/* Null Key Path */
#define	BT_IKYF_ERR	45	/* Inconsistent Key Flag */
#define	BT_SWRT_ERR	46	/* Access To File Denied */
#define	BT_MOPN_ERR	47	/* Maximum Open Files */
#define	BT_IALT_ERR	48	/* Invalid Alternate Sequence Definition */
#define	BT_KTYP_ERR	49	/* Key Type Error */
#define	BT_OWNR_ERR	50	/* Owner Already Set */
#define	BT_IOWN_ERR	51	/* Invalid Owner */
#define	BT_AWRT_ERR	52	/* Error Writing Cache */
#define	BT_IINT_ERR	53	/* Invalid Interface */
#define	BT_VARP_ERR	54	/* Variable Page Error */
#define	BT_AINC_ERR	55	/* Auto Increment Error */
#define	BT_IIDX_ERR	56	/* Incomplete Index */
#define	BT_EMEM_ERR	57	/* Expanded Memory Error */
#define	BT_CBTS_ERR	58	/* Compression Buffer Too Short */
#define	BT_DOPN_ERR	59	/* File Already Exist */
#define	BT_REJC_ERR	60	/* Reject Count Reached */
#define	BT_WSTS_ERR	61	/* Work Space Too Small */
#define	BT_IDSC_ERR	62	/* Incorrect Descriptor */
#define	BT_IEIB_ERR	63	/* Invalid Extended Insert Buffer */
#define	BT_FLIM_ERR	64	/* Filter Limit Reached */
#define	BT_IFLD_ERR	65	/* Incorrect Field Offset */

#define	BT_TABT_ERR	74	/* Automatic Transaction Abort */

#define	BT_DEAD_ERR	78	/* Deadlock Detected */

#define	BT_CONF_ERR	80	/* Conflict */
#define	BT_LOCK_ERR	81	/* Lock Error */
#define	BT_LPOS_ERR	82	/* Lost Position */
#define	BT_TRED_ERR	83	/* Read Outside Transaction */
#define	BT_RLOK_ERR	84	/* Record Locked */
#define	BT_FLOK_ERR	85	/* File Locked */
#define	BT_FFUL_ERR	86	/* File Table Full */
#define	BT_HFUL_ERR	87	/* Handle Table Full */
#define	BT_IMOD_ERR	88	/* Incompatible Mode Error */

#define	BT_RDTF_ERR	90	/* Redirected Device Table Full */
#define	BT_SRVR_ERR	91	/* Server Error */
#define	BT_TFUL_ERR	92	/* Transaction Table Full */
#define	BT_LTYP_ERR	93	/* Incompatible Lock Type */
#define	BT_ACCS_ERR	94	/* Permission Error */
#define	BT_SESS_ERR	95	/* Session No Longer Valid */
#define	BT_COMM_ERR	96	/* Communications Environment Error */
#define	BT_BTBZ_ERR	97	/* Data Message Too Small */
#define	BT_ITRN_ERR	98	/* Internal Transaction Error */

#define	BT_FSZL_ERR	132	/* The file has reached its size limit */
#define	BT_BADU_ERR	170	/* Login Failed Bad Username */
#define	BT_BADP_ERR	171	/* Login Failed Bad Password */

#endif	/* ~ctBERRH */

/* end of cterrc.h */
