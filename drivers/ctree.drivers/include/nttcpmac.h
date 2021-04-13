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


#define ctMacTCP_BUFFSIZE  8192
#define WaitEverPeekShtdwn (-31939) /* Unused unique value */
#define ctrt_memcpy(s1,s2,n)	memcpy(((pTEXT)(s1)),((pTEXT)(s2)),((long)(n)))
#define cpybig(dp,sp,n) 	ctrt_memcpy(dp,sp,((size_t)(n)))

void revlng(pTEXT, NINT);
void revbyt(pTEXT, NINT);
void revwrd(pTEXT, NINT);
void revobj(pTEXT, NINT);

struct iovec {
	LONG	iov_len;
	pTEXT	iov_base;
};

ULONG 	mac_RDSToVector(rdsEntry *pRDS, struct iovec *pVectors, NINT nVectors);
int 	mac_TCPRecvData(pTCPSOCK Handle,  SOCKET Socket, Ptr pRDS, COUNT numRDSEntry, TEXT retry);
int 	mac_TCPRecvDataFinish(pTCPSOCK Handle, SOCKET Socket, Ptr pRDS);
int 	mac_recv(pTCPSOCK Handle, SOCKET Socket, char * buf, int len, int flags);
ULONG 	mac_VectorToWDS(struct iovec *pVectors, NINT nVectors, wdsEntry *pWDS, NINT nEntries);
int 	mac_TCPSendData(pTCPSOCK Handle,  SOCKET Socket, Ptr pWDS, TEXT retry);
int 	mac_send (pTCPSOCK Handle,SOCKET Socket, char * buf, int len, int flags);
int 	mac_gethostname (char * name, int namelen);
struct	mac_hostent *mac_gethostbyname(pTCPSOCK Handle,const char * name);
int 	mac_setsockopt(SOCKET s, int level, int optname,
                           const char * optval, int optlen);
int 	mac_getsockopt(SOCKET s, int level, int optname,
                           char * optval, int *optlen);
SOCKET 	mac_socket (pTCPSOCK Handle, int af, int type, int protocol);
unsigned short 	mac_htons (unsigned short hostshort);
unsigned long 	mac_htonl (unsigned long hostlong);
unsigned long 	mac_ntohl (unsigned long netlong);
int 	mac_bind (SOCKET s, const struct mac_sockaddr_in *addr, int namelen);
SOCKET 	mac_accept (pCONNECTION Connection,SOCKET Socket);
int 	mac_connect (SOCKET s, const struct mac_sockaddr_in *name, int namelen);
int 	mac_listen (SOCKET s, int backlog);
int 	mac_close (pTCPSOCK Handle,SOCKET Socket);
int 	mac_shutdown (SOCKET s, int how);
int 	mac_ioctl (SOCKET s, long cmd, unsigned long *argp);
int 	mac_TCPGetConnection(pTCPSOCK Handle, SOCKET  Socket,  
					  TEXT timeOut, 
					  COUNT localPort,
					  LONG localHost);
int 	mac_TCPAbortConnection(pTCPSOCK Handle, SOCKET Socket);
int 	mac_TCPCloseConnection(pTCPSOCK Handle, SOCKET Socket);
int 	mac_TCPDestroyStream(pTCPSOCK Handle, SOCKET Socket);
int 	mac_GetMyIpAddress(pCONNECTION Connection);
int 	mac_TCPWait(pCONNECTION Connection, pCOUNT pFlag, NINT where);

/* end of nttcpmac.h */

