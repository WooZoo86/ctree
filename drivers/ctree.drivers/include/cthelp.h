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

#ifndef CTHELP_H
#define CTHELP_H

#define hNO_HELP	0
#define hWORD2		1
#define hSRVNAM		2
#define hADMFILWRD	3
#define hADMUSRWRD	4
#define hF_MENU		5
#define hFILNAM		6
#define hG_MENU		7
#define hU_MENU		8
#define hNEWOWNER	9
#define hNEWGROUP	10
#define hPERM		11
#define hNEWFILWRD	12
#define hUSERID2	13
#define hGDESC		14
#define hGROUPID	15
#define hGNUM2		16
#define hNEWUSRWRD	17
#define hGNUM1		18
#define hUSRWRD		19
#define hUDESC		20
#define hUSERID		21
#define hM_MENU		22
#define hSUPWRD		23
#define hFILWRD		24
#define hNEWOWNER2	25
#define hSTPDLY		26
#define hDMPSCP		27
#define hROLSCP		28
#define hSCPNAM		29
#define hUMEM		30
#define hUMEMR		31
#define hGMEM		32
#define hGMEMR		33
#define hC_MENU		34
#define hTASKN		35
#define hUSERID3	36
#define hSTPSRV		37
#define hADMUSRID	38
#define hUXBEGDAT	39
#define hUXENDDAT	40
#define hUXLIMIT	41
#define hUXRSMDAT	42
#define hUXMUST		43
#define hMON_MENU	44
#define hCHGSET_MENU	45
#define hCHGSET_FNCMON	46
#define hCHGSET_CHKMON	47
#define hCHGSET_MEMMON	48
#define hCHGSET_RQTMON	49
#define hCHGSET_DMPDFR	50
#define hCHGSET_DMPDNT	51
#define hCHGSET_STTMSK	52
#define hCHGSET_ENCMPC	53
#define hCHGSET_ENCMPN	54
#define hCHGSET_ENCFNM	55
#define hCHGSET_hFILNAM 56
#define hCHGSET_DIAGNO  57
#define hULOGLMT	58
#define hGLOGLMT	59
#define hQTIMOUT	60
#define hUSRLDAPAUTH	61
#define hCHGSET_CONFIG	62
#define hCHGSET_ENCLEV	63
#define hUXPWDEXP	64

/****************************************************************************/
#define SA1001	1001	/* SA_LOGON: Could not logon to server.				*/
#define SA1002	1002	/* SA_LOGON: Could not open administrative file (FAIRCOM.FCS).	*/
#define SA1003	1003	/* SA_LOGON: User-Could not open administrative file.		*/
#define SA1004	1004	/* SA_LOGON: UserX-Could not open administrative file.		*/
#define SA1005	1005	/* SA_LOGON: Group-Could not open administrative file.		*/
#define SA1006	1006	/* SA_LOGON: UsrGp-Could not open administrative file.		*/

#define SA1007	1007	/* SA_USERS: Cannot perform user operations w/old client lib.	*/
#define SA1008	1008	/* SA_USERS: User id is NULL. Must have user id.		*/
#define SA1009	1009	/* SA_USERS: Cannot add the GUEST Id. It is reserved.		*/
#define SA1010	1010	/* SA_USERS: Only super ADMIN can update ADMIN group.		*/
#define SA1011	1011	/* SA_USERS: Group cannot be found.				*/
#define SA1012	1012	/* SA_USERS: Start/end validity dates out of order.		*/
#define SA1013	1013	/* SA_USERS: User Id already exists.				*/
#define SA1014	1014	/* SA_USERS: Could not add user.				*/
#define SA1015	1015	/* SA_USERS: Could not end new user TRAN.			*/
#define SA1016	1016	/* SA_USERS: Could not begin new user TRAN.			*/
#define SA1017	1017	/* SA_USERS: Cannot remove super administrator.			*/
#define SA1018	1018	/* SA_USERS: Could not find user.				*/
#define SA1019	1019	/* SA_USERS: Could not remove user.				*/
#define SA1020	1020	/* SA_USERS: Could not end remove user TRAN.			*/
#define SA1021	1021	/* SA_USERS: Could not begin remove user TRAN.			*/
#define SA1022	1022	/* SA_USERS: Could not change user password.			*/
#define SA1023	1023	/* SA_USERS: Could not end change user password TRAN.		*/
#define SA1024	1024	/* SA_USERS: Could not begin change user password TRAN.		*/
#define SA1025	1025	/* SA_USERS: Could not access group information.		*/
#define SA1026	1026	/* SA_USERS: Group cannot be found.				*/
#define SA1027	1027	/* SA_USERS: Could not change groups.				*/
#define SA1028	1028	/* SA_USERS: Could not end change group TRAN.			*/
#define SA1029	1029	/* SA_USERS: Could not begin change group TRAN.			*/
#define SA1030	1030	/* SA_USERS: Could not allocate memory for user list.		*/
#define SA1031	1031	/* SA_USERS: User List Unexpected termination.			*/
#define SA1032	1032	/* SA_USERS: Could not change user description.			*/
#define SA1033	1033	/* SA_USERS: Could not end change user description TRAN.	*/
#define SA1034	1034	/* SA_USERS: Could not begin change user description TRAN.	*/
#define SA1035	1035	/* SA_USERS: Could not change user memory.			*/
#define SA1036	1036	/* SA_USERS: Could not end change user memory TRAN.		*/
#define SA1037	1037	/* SA_USERS: User not member of group. Cannot remove.		*/
#define SA1038	1038	/* SA_USERS: User is already assigned to max number of groups.	*/
#define SA1039	1039	/* SA_USERS: Could not find extended user info.			*/
#define SA1040	1040	/* SA_USERS: Could not create missing extended info record.	*/
#define SA1041	1041	/* SA_USERS: Unexpected error retrieving extended user info.	*/
#define SA1042	1042	/* SA_USERS: Incorrect start/end validity date format.		*/
#define SA1043	1043	/* SA_USERS: Illegal start/end validity date.			*/
#define SA1044	1044	/* SA_USERS: Start/end validity date is out of range.		*/
#define SA1045	1045	/* SA_USERS: User not available for update.			*/
#define SA1046	1046	/* SA_USERS: Could not change extended user info.		*/
#define SA1047	1047	/* SA_USERS: Could not end change extended user info TRAN.	*/
#define SA1048	1048	/* SA_USERS: Invalid user action specified.			*/

#define SA2001  2001	/* SA_GROUP: Empty Group Id not allowed.			*/
#define SA2002  2002	/* SA_GROUP: Cannot add the GUEST Id.				*/
#define SA2003  2003	/* SA_GROUP: Group Id already exists.				*/
#define SA2004	2004	/* SA_GROUP: Could not add group.				*/
#define SA2005  2005	/* SA_GROUP: Could not end new group TRAN.			*/
#define SA2006  2006	/* SA_GROUP: Could not begin new group TRAN.			*/
#define SA2007  2007	/* SA_GROUP: Cannot remove administrator group.			*/
#define SA2008  2008	/* SA_GROUP: Could not find group.				*/
#define SA2009  2009	/* SA_GROUP: Could not remove group.				*/
#define SA2010  2010	/* SA_GROUP: Could not end remove group TRAN.			*/
#define SA2011  2011	/* SA_GROUP: Could not begin remove group TRAN.			*/
#define SA2012  2012	/* SA_GROUP: Could not change group description.		*/
#define SA2013  2013	/* SA_GROUP: Could not end change group description TRAN.	*/
#define SA2014  2014	/* SA_GROUP: Could not begin change group description TRAN.	*/
#define SA2015  2015	/* SA_GROUP: Could not change group memory.			*/
#define SA2016  2016	/* SA_GROUP: Could not end change group memory TRAN.		*/
#define SA2017	2017	/* SA_GROUP: User is already in group.				*/
#define SA2018	2018	/* SA_GROUP: Could not allocate memory for group list.		*/
#define SA2019	2019	/* SA_GROUP: Group List Unexpected termination.			*/
#define SA2020	2020	/* SA_GROUP: Invalid group action specified.			*/

#define SA3001  3001	/* SA_FILES: Could not open superfile host.			*/
#define SA3002  3002	/* SA_FILES: Could not open file.				*/
#define SA3003  3003	/* SA_FILES: Could not change file password.			*/
#define SA3004  3004	/* SA_FILES: Invalid file permission mask specified.		*/
#define SA3005  3005	/* SA_FILES: Could not update permission mask.			*/
#define SA3006  3006	/* SA_FILES: Could not find group.				*/
#define SA3007  3007	/* SA_FILES: Could not change Group Id.				*/
#define SA3008  3008	/* SA_FILES: Could not find owner.				*/
#define SA3009  3009	/* SA_FILES: Could not change Owner Id.				*/
#define SA3010	3010	/* SA_FILES: Invalid file action specified.			*/
#define SA3011	3011	/* SA_FILES: Could not get current file permission mask.	*/
/****************************************************************************/

/* SA_USERS Action Codes */
#define ctuNEW		1
#define ctuREMOVE	2
#define ctuLIST		3
#define ctuWORD		4
#define ctuGROUP	5
#define ctuDESC		6
#define ctuMEM		7
#define ctuXINFO	8
#define ctuLOGLMT	9
#define ctuGROUPRM	9	/* used by SA_ADMIN API but not by user() */
#define ctuSHOW		10	/* used by SA_ADMIN API but not by user() */

/* SA_GROUP Action Codes */
#define ctgNEW		1
#define ctgREMOVE	2
#define ctgLIST		3
#define ctgMEMBAD	4
#define ctgDESC		5
#define ctgMEM		6
#define ctgLOGLMT	7
#define ctgSHOW		7	/* used by SA_ADMIN API but not by group() */
#define ctgMEMBRM	8	/* used by SA_ADMIN API but not by group() */

/* SA_FILES Action Codes */
#define ctfPASS		1
#define ctfPERM		2
#define ctfGROUP	3
#define ctfOWNER	4
#define ctfSHOW		5

/* Action Class Codes */
#define ctUSRtyp	1
#define ctGRPtyp	2
#define ctFILtyp	3

/* Server Monitoring Action Codes */
#define ctmonLISTallopenfiles	1
#define ctmonLISTconnopenfiles	2
#define ctmonLISTfileusers	3
#define ctmonLISTfilelocks	4
#define ctmonCLOSEkeepopenfile	5

/* Change Server Settings Action Codes */
#define ctchgsetFNCMON 1
#define ctchgsetCHKMON 2
#define ctchgsetMEMMON 3
#define ctchgsetRQTMON 4
#define ctchgsetDMPDFR 5
#define ctchgsetDMPDNT 6
#define ctchgsetSTTMSK 7
#define ctchgsetENCMPW 8
#define ctchgsetDIAGNO 9
#define ctchgsetCONFIG 10
#define ctchgsetLOGONS 11


/****************************************************************************/
/* USER definition structure */
typedef struct _saUSRI
{
	TEXT		usr_pass[PWZX];		/* User Password		*/
	TEXT		usr_group[MAX_NAME];	/* User Group			*/
	TEXT		usr_id[IDZ];		/* User Id			*/
	TEXT		usr_desc[DSZ];		/* User Description		*/
	TEXT		usr_memory[11];		/* User Memory Limit		*/
	TEXT		usr_memrule[2];		/* User Memory Rule		*/
	TEXT		usr_xbegdat[11];	/* Begin validity period	*/
	TEXT		usr_xenddat[11];	/* End validity period		*/
	TEXT		usr_xlgnlmt[11];	/* Invalid logon limit		*/
	TEXT		usr_xlgnrsm[11];	/* Logon block time remaining	*/
	TEXT		usr_xmstlgn[11];	/* Must logon limit		*/
	TEXT		usr_authtype[10];	/* Authentication type		*/
	TEXT		usr_xpwdexp[11];	/* Password expiration in days	*/
	struct _saUSRI	*usr_list;		/* Ptr to user list		*/
} saUSRINFO;

/****************************************************************************/


/****************************************************************************/
/* Group definition structure */
typedef struct _saGRPI
{
	TEXT		grp_id[IDZ];		/* Group Id			*/
	TEXT		grp_desc[DSZ];		/* Group Description		*/
	TEXT		grp_memory[32];		/* Group Memory Limit		*/
	TEXT		grp_memrule[2];		/* Group Memory Rule		*/
	TEXT		grp_user[IDZ+1];	/* User id to add or remove	*/
	struct _saGRPI	*grp_list;		/* Ptr to group list		*/
} saGRPINFO;
/****************************************************************************/


/****************************************************************************/
/* File definition structure */
typedef struct
{
	TEXT		fil_pass[PWZ];		/* File Password	*/
	TEXT		fil_group[IDZ];		/* File Group		*/
	TEXT		fil_name[MAX_NAME];	/* File name		*/
	TEXT		fil_mask[16];		/* File Permission mask */
	TEXT		fil_owner[IDZ];		/* File Owner		*/
	TEXT		fil_maskmode;		/* Permission mask mode	*/
} saFILINFO;
/****************************************************************************/


/****************************************************************************/
/* User/group/file definition structure */
typedef struct _saALLI
{
	pTEXT		all_pass;		/* usr_pass, fil_pass		*/
	pTEXT		all_group;		/* usr_group, grp_id, fil_group */
	pTEXT		all_id;			/* usr_id, fil_owner		*/
	pTEXT		all_desc;		/* usr_desc, grp_desc		*/
	pTEXT		all_memory;		/* usr_memory, grp_memory	*/
	pTEXT		all_memrule;		/* usr_memrule, grp_memrule	*/
	pTEXT		all_xbegdat;		/* usr_xbegdat			*/
	pTEXT		all_xenddat;		/* usr_xenddat			*/
	pTEXT		all_xlgnlmt;		/* usr_xlgnlmt			*/
	pTEXT		all_xlgnrsm;		/* usr_xlgnrsm			*/
	pTEXT		all_xmstlgn;		/* usr_xmstlgn			*/	
	pTEXT		all_authtyp;		/* usr_authtype			*/
	pTEXT		all_xpwdexp;		/* usr_xpwdexp			*/
	pTEXT		all_filname;		/* fil_name			*/
	pTEXT		all_filmask;		/* fil_mask			*/
	pVOID		all_list;		/* usr_list, grp_list		*/
	TEXT		all_filmode;		/* fil_maskmode			*/
} saALLINFO;

/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PROTOTYPE
extern NINT  SA_LOGON(pTEXT admnuser, pTEXT admnpass, pTEXT filepass, pTEXT servername);
extern NINT  SA_LOGOF();
extern NINT  SA_USERS(COUNT action, saUSRINFO *usrinfo);
extern NINT  SA_GROUP(COUNT action, saGRPINFO *grpinfo);
extern NINT  SA_FILES(COUNT action, saFILINFO *filinfo);
extern pTEXT SA_ERRMSG(COUNT errcode);
extern NINT  SA_ERROR(VOID);
#else
extern NINT  SA_LOGON();
extern NINT  SA_LOGOF();
extern NINT  SA_USERS();
extern NINT  SA_GROUP();
extern NINT  SA_FILES();
extern pTEXT SA_ERRMSG();
extern NINT  SA_ERROR();
#endif

#ifdef __cplusplus
}
#endif


#ifdef ctFeatADMIN_API

extern NINT	my_tp;

#ifdef ctrt_printf
#undef ctrt_printf
#endif

#define ctrt_printf	sa_printf
#ifdef PROTOTYPE
extern ctCONV VOID ctDECLV sa_printf(pTEXT fmt, ...);
#else
extern ctCONV VOID ctDECLV sa_printf();
#endif

#else  /* ~ctFeatADMIN_API */

extern COUNT	sa_errno;
#ifdef ctFeatADMIN_SECURITY
extern COUNT	sa_noperm; /* client denied permission to open security files */
#endif
extern COUNT	sa_cterrno;

#endif /* ~ctFeatADMIN_API */

#endif /* ~CTHELP_H */

/* end of cthelp.h */
