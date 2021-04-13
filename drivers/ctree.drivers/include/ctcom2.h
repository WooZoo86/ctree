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

#ifndef ctCOM2H
#define ctCOM2H

#ifdef  ctPortUNIX
#ifndef ctCLIENT
#ifndef ctPortVINES
#define ctUNXCOM_ACTIVE /* Activate multiple bound protocols. */
#endif  /* ~ctPortVINES */
#endif	/* ~ctCLIENT 	*/
#endif	/*  ctPortUNIX 	*/

#if defined(ctFeatIPv6) || !defined(ctDLLOAD)
#ifdef ctPortWIN32
#ifndef ctCLIENT
#define ctUNXCOM_ACTIVE
#endif
#endif
#endif

#ifdef  ctUNXCOM_ACTIVE 

/*^***********************************/
#ifdef 	ctUNXCOM_ADSP
#define ctNpInit 		ADSPctNpInit
#define ctNpPolice		ADSPctNpPolice
#define ctNpSetAttribute	ADSPctNpSetAttribute   
#define ctNpGetAttribute	ADSPctNpGetAttribute
#define ctNpStart		ADSPctNpStart
#define ctNpStop		ADSPctNpStop
#define ctNpOpen		ADSPctNpOpen
#define ctNpClose		ADSPctNpClose
#define ctNpWrite		ADSPctNpWrite
#define ctNpRead		ADSPctNpRead
#define ctNpPackSiz		ADSPctNpPackSiz
#define ctNpMakeNmPipe		ADSPctNpMakeNmPipe
#define ctNpDisconnectNmPipe	ADSPctNpDisconnectNmPipe
#define ctNpConnectNmPipe	ADSPctNpConnectNmPipe
#define ctNPCommCRC_LogErr	ADSPctNPCommCRC_LogErr

/**/
#define ctNpGlobals		ADSPctNpGlobals
#define NPfree			ADSPNPfree
#define NPalloc			ADSPNPalloc
#define NPwaitWhile		ADSPNPwaitWhile
#define NPdefer			ADSPNPdefer
#define NPcttcre		ADSPNPcttcre
#define NPrevobj		ADSPNPrevobj
#define NPctsemrqs		ADSPNPctsemrqs
#define NPctsemclr		ADSPNPctsemclr
#define NPctsemwat		ADSPNPctsemwat
#define NPctblkrqs		ADSPNPctblkrqs
#define NPctblkclr		ADSPNPctblkclr
#define NPctblkwat		ADSPNPctblkwat
#define NPcttimrqs		ADSPNPcttimrqs
#define NPcttimclr		ADSPNPcttimclr
#define NPcttimwat		ADSPNPcttimwat
#define NPGetSrVariable		ADSPNPGetSrVariable
#define NPusrstat		ADSPNPusrstat
#define NPgetactivestatus	ADSPNPgetactivestatus
#define NPsetinactive		ADSPNPsetinactive
#define NPctrt_printf		ADSPNPctrt_printf
#define NPUserAlive		ADSPNPUserAlive
/**/
#define at_CommunicationPolice	ADSPat_CommunicationPolice
#define at_CommunicationInit	ADSPat_CommunicationInit
#define at_SessionSetAttribute	ADSPat_SessionSetAttribute
#define at_SessionValidate	ADSPat_SessionValidate
#define at_SessionNew		ADSPat_SessionNew
#define at_SessionDispose	ADSPat_SessionDispose
#define at_SessionOpen		ADSPat_SessionOpen
#define at_SessionClose		ADSPat_SessionClose
#define at_SessionSend		ADSPat_SessionSend
#define at_SessionReceive	ADSPat_SessionReceive
#define at_SessionMake		ADSPat_SessionMake
#define at_SessionConnect	ADSPat_SessionConnect
#define at_SessionDisconnect	ADSPat_SessionDisconnect
#define at_CommunicationStart	ADSPat_CommunicationStart
#define at_CommunicationStop	ADSPat_CommunicationStop
/*#define find_syssem		ADSPfind_syssem */
/*#define find_wait		ADSPfind_wait */
#define VectorToBuffer		ADSPVectorToBuffer
#define BufferToVector		ADSPBufferToVector
#define IsPIDAlive		ADSPIsPIDAlive
#endif /* ctUNXCOM_ADSP */
/*~***********************************/


/*^***********************************/
#ifdef 	ctUNXCOM_TCP
#define ctNpInit 		TCPctNpInit
#define ctNpPolice		TCPctNpPolice
#define ctNpSetAttribute	TCPctNpSetAttribute   
#define ctNpGetAttribute	TCPctNpGetAttribute
#define ctNpStart		TCPctNpStart
#define ctNpStop		TCPctNpStop
#define ctNpOpen		TCPctNpOpen
#define ctNpClose		TCPctNpClose
#define ctNpWrite		TCPctNpWrite
#define ctNpRead		TCPctNpRead
#define ctNpPackSiz		TCPctNpPackSiz
#define ctNpMakeNmPipe		TCPctNpMakeNmPipe
#define ctNpDisconnectNmPipe	TCPctNpDisconnectNmPipe
#define ctNpConnectNmPipe	TCPctNpConnectNmPipe
#define ctNPCommCRC_LogErr	TCPctNPCommCRC_LogErr

/**/
#define ctNpGlobals		TCPctNpGlobals
#define NPfree			TCPNPfree
#define NPalloc			TCPNPalloc
#define NPwaitWhile		TCPNPwaitWhile
#define NPdefer			TCPNPdefer
#define NPcttcre		TCPNPcttcre
#define NPrevobj		TCPNPrevobj
#define NPctsemrqs		TCPNPctsemrqs
#define NPctsemclr		TCPNPctsemclr
#define NPctsemwat		TCPNPctsemwat
#define NPctblkrqs		TCPNPctblkrqs
#define NPctblkclr		TCPNPctblkclr
#define NPctblkwat	       	TCPNPctblkwat
#define NPcttimrqs		TCPNPcttimrqs
#define NPcttimclr		TCPNPcttimclr
#define NPcttimwat		TCPNPcttimwat
#define NPGetSrVariable		TCPNPGetSrVariable
#define NPusrstat		TCPNPusrstat
#define NPgetactivestatus	TCPNPgetactivestatus
#define NPsetinactive		TCPNPsetinactive
#define NPctrt_printf		TCPNPctrt_printf
#define NPUserAlive		TCPNPUserAlive
/**/
#define at_CommunicationPolice	TCPat_CommunicationPolice
#define at_CommunicationInit	TCPat_CommunicationInit
#define at_SessionSetAttribute	TCPat_SessionSetAttribute
#define at_SessionValidate	TCPat_SessionValidate
#define at_SessionNew		TCPat_SessionNew
#define at_SessionDispose	TCPat_SessionDispose
#define at_SessionOpen		TCPat_SessionOpen
#define at_SessionClose		TCPat_SessionClose
#define at_SessionSend		TCPat_SessionSend
#define at_SessionReceive	TCPat_SessionReceive
#define ctRead_select		TCPctRead_select
#define at_SessionMake		TCPat_SessionMake
#define at_SessionConnect	TCPat_SessionConnect
#define at_SessionDisconnect	TCPat_SessionDisconnect
#define at_CommunicationStart	TCPat_CommunicationStart
#define at_CommunicationStop	TCPat_CommunicationStop
/*#define find_syssem		TCPfind_syssem */
/*#define find_wait		TCPfind_wait */
#define VectorToBuffer		TCPVectorToBuffer
#define BufferToVector		TCPBufferToVector
#define IsPIDAlive		TCPIsPIDAlive
#endif /* ctUNXCOM_TCP */
/*~***********************************/

/*^***********************************/
#ifdef 	ctUNXCOM_TCPIPV6
#define ctNpInit 		TCPIPV6ctNpInit
#define ctNpPolice		TCPIPV6ctNpPolice
#define ctNpSetAttribute	TCPIPV6ctNpSetAttribute   
#define ctNpGetAttribute	TCPIPV6ctNpGetAttribute
#define ctNpStart		TCPIPV6ctNpStart
#define ctNpStop		TCPIPV6ctNpStop
#define ctNpOpen		TCPIPV6ctNpOpen
#define ctNpClose		TCPIPV6ctNpClose
#define ctNpWrite		TCPIPV6ctNpWrite
#define ctNpRead		TCPIPV6ctNpRead
#define ctNpPackSiz		TCPIPV6ctNpPackSiz
#define ctNpMakeNmPipe		TCPIPV6ctNpMakeNmPipe
#define ctNpDisconnectNmPipe	TCPIPV6ctNpDisconnectNmPipe
#define ctNpConnectNmPipe	TCPIPV6ctNpConnectNmPipe
#define ctNPCommCRC_LogErr	TCPIPV6ctNPCommCRC_LogErr

/**/
#define ctNpGlobals		TCPIPV6ctNpGlobals
#define NPfree			TCPIPV6NPfree
#define NPalloc			TCPIPV6NPalloc
#define NPwaitWhile		TCPIPV6NPwaitWhile
#define NPdefer			TCPIPV6NPdefer
#define NPcttcre		TCPIPV6NPcttcre
#define NPrevobj		TCPIPV6NPrevobj
#define NPctsemrqs		TCPIPV6NPctsemrqs
#define NPctsemclr		TCPIPV6NPctsemclr
#define NPctsemwat		TCPIPV6NPctsemwat
#define NPctblkrqs		TCPIPV6NPctblkrqs
#define NPctblkclr		TCPIPV6NPctblkclr
#define NPctblkwat	       	TCPIPV6NPctblkwat
#define NPcttimrqs		TCPIPV6NPcttimrqs
#define NPcttimclr		TCPIPV6NPcttimclr
#define NPcttimwat		TCPIPV6NPcttimwat
#define NPGetSrVariable		TCPIPV6NPGetSrVariable
#define NPusrstat		TCPIPV6NPusrstat
#define NPgetactivestatus	TCPIPV6NPgetactivestatus
#define NPsetinactive		TCPIPV6NPsetinactive
#define NPctrt_printf		TCPIPV6NPctrt_printf
#define NPUserAlive		TCPIPV6NPUserAlive
/**/
#define at_CommunicationPolice	TCPIPV6at_CommunicationPolice
#define at_CommunicationInit	TCPIPV6at_CommunicationInit
#define at_SessionSetAttribute	TCPIPV6at_SessionSetAttribute
#define at_SessionValidate	TCPIPV6at_SessionValidate
#define at_SessionNew		TCPIPV6at_SessionNew
#define at_SessionDispose	TCPIPV6at_SessionDispose
#define at_SessionOpen		TCPIPV6at_SessionOpen
#define at_SessionClose		TCPIPV6at_SessionClose
#define at_SessionSend		TCPIPV6at_SessionSend
#define at_SessionReceive	TCPIPV6at_SessionReceive
#define ctRead_select		TCPIPV6ctRead_select
#define at_SessionMake		TCPIPV6at_SessionMake
#define at_SessionConnect	TCPIPV6at_SessionConnect
#define at_SessionDisconnect	TCPIPV6at_SessionDisconnect
#define at_CommunicationStart	TCPIPV6at_CommunicationStart
#define at_CommunicationStop	TCPIPV6at_CommunicationStop
/*#define find_syssem		TCPIPV6find_syssem */
/*#define find_wait		TCPIPV6find_wait */
#define VectorToBuffer		TCPIPV6VectorToBuffer
#define BufferToVector		TCPIPV6BufferToVector
#define IsPIDAlive		TCPIPV6IsPIDAlive

#define ntKillAccept		TCPIPV6ntKillAccept
#define select_thrd		TCPIPV6select_thrd
#define SetNonBlocking		TCPIPV6SetNonBlocking
#define SetOtherSockOpts	TCPIPV6SetOtherSockOpts
#define DerivePortNumber	TCPIPV6DerivePortNumber
#define ParseOutHostName	TCPIPV6ParseOutHostName
#define ParseOutServerName	TCPIPV6ParseOutServerName
#define ctCommCRC		TCPIPV6ctCommCRC
#define ctCommCRC_Set		ctCommCRC_Set_TCPIPV6
#define ctCommCRC_Check		ctCommCRC_Check_TCPIPV6
#define ctSocket_select		TCPIPV6ctSocket_select
#endif /* ctUNXCOM_TCPIPV6 */
/*~***********************************/


/*^***********************************/
#ifdef 	ctUNXCOM_SSLTCP
#define ctNpInit 		SSLTCPctNpInit
#define ctNpPolice		SSLTCPctNpPolice
#define ctNpSetAttribute	SSLTCPctNpSetAttribute   
#define ctNpGetAttribute	SSLTCPctNpGetAttribute
#define ctNpStart		SSLTCPctNpStart
#define ctNpStop		SSLTCPctNpStop
#define ctNpOpen		SSLTCPctNpOpen
#define ctNpClose		SSLTCPctNpClose
#define ctNpWrite		SSLTCPctNpWrite
#define ctNpRead		SSLTCPctNpRead
#define ctNpPackSiz		SSLTCPctNpPackSiz
#define ctNpMakeNmPipe		SSLTCPctNpMakeNmPipe
#define ctNpDisconnectNmPipe	SSLTCPctNpDisconnectNmPipe
#define ctNpConnectNmPipe	SSLTCPctNpConnectNmPipe
#define ctNPCommCRC_LogErr	SSLTCPctNPCommCRC_LogErr

/**/
#define ctNpGlobals		SSLTCPctNpGlobals
#define NPfree			SSLTCPNPfree
#define NPalloc			SSLTCPNPalloc
#define NPwaitWhile		SSLTCPNPwaitWhile
#define NPdefer			SSLTCPNPdefer
#define NPcttcre		SSLTCPNPcttcre
#define NPrevobj		SSLTCPNPrevobj
#define NPctsemrqs		SSLTCPNPctsemrqs
#define NPctsemclr		SSLTCPNPctsemclr
#define NPctsemwat		SSLTCPNPctsemwat
#define NPctblkrqs		SSLTCPNPctblkrqs
#define NPctblkclr		SSLTCPNPctblkclr
#define NPctblkwat	       	SSLTCPNPctblkwat
#define NPcttimrqs		SSLTCPNPcttimrqs
#define NPcttimclr		SSLTCPNPcttimclr
#define NPcttimwat		SSLTCPNPcttimwat
#define NPGetSrVariable		SSLTCPNPGetSrVariable
#define NPusrstat		SSLTCPNPusrstat
#define NPgetactivestatus	SSLTCPNPgetactivestatus
#define NPsetinactive		SSLTCPNPsetinactive
#define NPctrt_printf		SSLTCPNPctrt_printf
#define NPUserAlive		SSLTCPNPUserAlive

/**/
#define at_CommunicationPolice	SSLTCPat_CommunicationPolice
#define at_CommunicationInit	SSLTCPat_CommunicationInit
#define at_SessionSetAttribute	SSLTCPat_SessionSetAttribute
#define at_SessionValidate	SSLTCPat_SessionValidate
#define at_SessionNew		SSLTCPat_SessionNew
#define at_SessionDispose	SSLTCPat_SessionDispose
#define at_SessionOpen		SSLTCPat_SessionOpen
#define at_SessionClose		SSLTCPat_SessionClose
#define at_SessionSend		SSLTCPat_SessionSend
#define at_SessionReceive	SSLTCPat_SessionReceive
#define ctRead_select		SSLTCPctRead_select
#define at_SessionMake		SSLTCPat_SessionMake
#define at_SessionConnect	SSLTCPat_SessionConnect
#define at_SessionDisconnect	SSLTCPat_SessionDisconnect
#define at_CommunicationStart	SSLTCPat_CommunicationStart
#define at_CommunicationStop	SSLTCPat_CommunicationStop
/*#define find_syssem		SSLTCPfind_syssem */
/*#define find_wait		SSLTCPfind_wait */
#define VectorToBuffer		SSLTCPVectorToBuffer
#define BufferToVector		SSLTCPBufferToVector
#define IsPIDAlive		SSLTCPIsPIDAlive
#endif /* ctUNXCOM_SSLTCP */
/*~***********************************/

/*^***********************************/
#ifdef 	ctUNXCOM_CRYTCP
#define ctNpInit 		CRYTCPctNpInit
#define ctNpPolice		CRYTCPctNpPolice
#define ctNpSetAttribute	CRYTCPctNpSetAttribute   
#define ctNpGetAttribute	CRYTCPctNpGetAttribute
#define ctNpStart		CRYTCPctNpStart
#define ctNpStop		CRYTCPctNpStop
#define ctNpOpen		CRYTCPctNpOpen
#define ctNpClose		CRYTCPctNpClose
#define ctNpWrite		CRYTCPctNpWrite
#define ctNpRead		CRYTCPctNpRead
#define ctNpPackSiz		CRYTCPctNpPackSiz
#define ctNpMakeNmPipe		CRYTCPctNpMakeNmPipe
#define ctNpDisconnectNmPipe	CRYTCPctNpDisconnectNmPipe
#define ctNpConnectNmPipe	CRYTCPctNpConnectNmPipe
#define ctNPCommCRC_LogErr	CRYTCPctNPCommCRC_LogErr

/**/
#define ctNpGlobals		CRYTCPctNpGlobals
#define NPfree			CRYTCPNPfree
#define NPalloc			CRYTCPNPalloc
#define NPwaitWhile		CRYTCPNPwaitWhile
#define NPdefer			CRYTCPNPdefer
#define NPcttcre		CRYTCPNPcttcre
#define NPrevobj		CRYTCPNPrevobj
#define NPctsemrqs		CRYTCPNPctsemrqs
#define NPctsemclr		CRYTCPNPctsemclr
#define NPctsemwat		CRYTCPNPctsemwat
#define NPctblkrqs		CRYTCPNPctblkrqs
#define NPctblkclr		CRYTCPNPctblkclr
#define NPctblkwat	       	CRYTCPNPctblkwat
#define NPcttimrqs		CRYTCPNPcttimrqs
#define NPcttimclr		CRYTCPNPcttimclr
#define NPcttimwat		CRYTCPNPcttimwat
#define NPGetSrVariable		CRYTCPNPGetSrVariable
#define NPusrstat		CRYTCPNPusrstat
#define NPgetactivestatus	CRYTCPNPgetactivestatus
#define NPsetinactive		CRYTCPNPsetinactive
#define NPctrt_printf		CRYTCPNPctrt_printf
#define NPUserAlive		CRYTCPNPUserAlive
/**/
#define at_CommunicationPolice	CRYTCPat_CommunicationPolice
#define at_CommunicationInit	CRYTCPat_CommunicationInit
#define at_SessionSetAttribute	CRYTCPat_SessionSetAttribute
#define at_SessionValidate	CRYTCPat_SessionValidate
#define at_SessionNew		CRYTCPat_SessionNew
#define at_SessionDispose	CRYTCPat_SessionDispose
#define at_SessionOpen		CRYTCPat_SessionOpen
#define at_SessionClose		CRYTCPat_SessionClose
#define at_SessionSend		CRYTCPat_SessionSend
#define at_SessionReceive	CRYTCPat_SessionReceive
#define ctRead_select		CRYTCPctRead_select
#define at_SessionMake		CRYTCPat_SessionMake
#define at_SessionConnect	CRYTCPat_SessionConnect
#define at_SessionDisconnect	CRYTCPat_SessionDisconnect
#define at_CommunicationStart	CRYTCPat_CommunicationStart
#define at_CommunicationStop	CRYTCPat_CommunicationStop
/*#define find_syssem		CRYTCPfind_syssem */
/*#define find_wait		CRYTCPfind_wait */
#define VectorToBuffer		CRYTCPVectorToBuffer
#define BufferToVector		CRYTCPBufferToVector
#define IsPIDAlive		CRYTCPIsPIDAlive

#define ntKillAccept		CRYTCPntKillAccept
#define select_thrd		CRYTCPselect_thrd
#define SetNonBlocking		CRYTCPSetNonBlocking
#define SetOtherSockOpts	CRYTCPSetOtherSockOpts
#define DerivePortNumber	CRYTCPDerivePortNumber
#define ParseOutHostName	CRYTCPParseOutHostName
#define ParseOutServerName	CRYTCPParseOutServerName
#define TickleAlarm		CRYTCPTickleAlarm
#define Tickle			CRYTCPTickle
#define ctCommCRC		CRYTCPctCommCRC
#define ctCommCRC_Set		ctCommCRC_Set_CRYTCP
#define ctCommCRC_Check		ctCommCRC_Check_CRYTCP
#define find_syssem		CRYTCPfind_syssem
#define find_wait		CRYTCPfind_wait
#define clrallsem		CRYTCPclrallsem
#define ctSocket_select		CRYTCPctSocket_select

#ifdef ctPortMAC
#define GetHostName		CRYTCPGetHostName
#define GetServerName		CRYTCPGetServerName
#define DNRResultProc		CRYTCPDNRResultProc
#define RDSToVector		CRYTCPRDSToVector
#define VectorToWDS		CRYTCPVectorToWDS
#define TCPWait			CRYTCPTCPWait
#define TCPCreateStream		CRYTCPTCPCreateStream
#define TCPDestroyStream	CRYTCPTCPDestroyStream
#define TCPOpenConnection	CRYTCPTCPOpenConnection
#define TCPCloseConnection	CRYTCPTCPCloseConnection
#define TCPAbortConnection	CRYTCPTCPAbortConnection
#define TCPSendData		CRYTCPTCPSendData
#define TCPRecvData		CRYTCPTCPRecvData
#define TCPRecvDataFinish	CRYTCPTCPRecvDataFinish
#define TCPGetConnection	CRYTCPTCPGetConnection
#define GetMyIpAddress		CRYTCPGetMyIpAddress
#endif /* ctPortMAC */

#endif /* ctUNXCOM_CRYTCP */
/*~***********************************/


/*^***********************************/
#ifdef 	ctUNXCOM_OTP
#define ctNpInit 		OTPctNpInit
#define ctNpPolice		OTPctNpPolice
#define ctNpSetAttribute	OTPctNpSetAttribute   
#define ctNpGetAttribute	OTPctNpGetAttribute
#define ctNpStart		OTPctNpStart
#define ctNpStop		OTPctNpStop
#define ctNpOpen		OTPctNpOpen
#define ctNpClose		OTPctNpClose
#define ctNpWrite		OTPctNpWrite
#define ctNpRead		OTPctNpRead
#define ctNpPackSiz		OTPctNpPackSiz
#define ctNpMakeNmPipe		OTPctNpMakeNmPipe
#define ctNpDisconnectNmPipe	OTPctNpDisconnectNmPipe
#define ctNpConnectNmPipe	OTPctNpConnectNmPipe
#define ctNPCommCRC_LogErr	OTPctNPCommCRC_LogErr

/**/
#define ctNpGlobals		OTPctNpGlobals
#define NPfree			OTPNPfree
#define NPalloc			OTPNPalloc
#define NPwaitWhile		OTPNPwaitWhile
#define NPdefer			OTPNPdefer
#define NPcttcre		OTPNPcttcre
#define NPrevobj		OTPNPrevobj
#define NPctsemrqs		OTPNPctsemrqs
#define NPctsemclr		OTPNPctsemclr
#define NPctsemwat		OTPNPctsemwat
#define NPctblkrqs		OTPNPctblkrqs
#define NPctblkclr		OTPNPctblkclr
#define NPctblkwat	       	OTPNPctblkwat
#define NPcttimrqs		OTPNPcttimrqs
#define NPcttimclr		OTPNPcttimclr
#define NPcttimwat		OTPNPcttimwat
#define NPGetSrVariable		OTPNPGetSrVariable
#define NPusrstat		OTPNPusrstat
#define NPgetactivestatus	OTPNPgetactivestatus
#define NPsetinactive		OTPNPsetinactive
#define NPctrt_printf		OTPNPctrt_printf
#define NPUserAlive		OTPNPUserAlive
/**/
#define at_CommunicationPolice	OTPat_CommunicationPolice
#define at_CommunicationInit	OTPat_CommunicationInit
#define at_SessionSetAttribute	OTPat_SessionSetAttribute
#define at_SessionValidate	OTPat_SessionValidate
#define at_SessionNew		OTPat_SessionNew
#define at_SessionDispose	OTPat_SessionDispose
#define at_SessionOpen		OTPat_SessionOpen
#define at_SessionClose		OTPat_SessionClose
#define at_SessionSend		OTPat_SessionSend
#define at_SessionReceive	OTPat_SessionReceive
#define ctRead_select		OTPctRead_select
#define at_SessionMake		OTPat_SessionMake
#define at_SessionConnect	OTPat_SessionConnect
#define at_SessionDisconnect	OTPat_SessionDisconnect
#define at_CommunicationStart	OTPat_CommunicationStart
#define at_CommunicationStop	OTPat_CommunicationStop
/*#define find_syssem		OTPfind_syssem */
/*#define find_wait		OTPfind_wait */
#define VectorToBuffer		OTPVectorToBuffer
#define BufferToVector		OTPBufferToVector
#define IsPIDAlive		OTPIsPIDAlive

#define ntKillAccept		OTPntKillAccept
#define select_thrd		OTPselect_thrd
#define SetNonBlocking		OTPSetNonBlocking
#define SetOtherSockOpts	OTPSetOtherSockOpts
#define DerivePortNumber	OTPDerivePortNumber
#define ParseOutHostName	OTPParseOutHostName
#define ParseOutServerName	OTPParseOutServerName
#define TickleAlarm		OTPTickleAlarm
#define Tickle			OTPTickle
#define ctCommCRC		OTPctCommCRC
#define ctCommCRC_Set		ctCommCRC_Set_OTP
#define ctCommCRC_Check		ctCommCRC_Check_OTP
#define find_syssem		OTPfind_syssem
#define find_wait		OTPfind_wait
#define clrallsem		OTPclrallsem
#define ctSocket_select		OTPctSocket_select

#define GetHostName		OTPGetHostName
#define GetServerName		OTPGetServerName
#define DNRResultProc		OTPDNRResultProc
#define RDSToVector		OTPRDSToVector
#define VectorToWDS		OTPVectorToWDS
#define TCPWait			OTPTCPWait
#define TCPCreateStream		OTPTCPCreateStream
#define TCPDestroyStream	OTPTCPDestroyStream
#define TCPOpenConnection	OTPTCPOpenConnection
#define TCPCloseConnection	OTPTCPCloseConnection
#define TCPAbortConnection	OTPTCPAbortConnection
#define TCPSendData		OTPTCPSendData
#define TCPRecvData		OTPTCPRecvData
#define TCPRecvDataFinish	OTPTCPRecvDataFinish
#define TCPGetConnection	OTPTCPGetConnection
#define GetMyIpAddress		OTPGetMyIpAddress

#endif /* ctUNXCOM_OTP */
/*~***********************************/


/*^***********************************/
#ifdef 	ctUNXCOM_SPX
#define ctNpInit 		SPXctNpInit
#define ctNpPolice		SPXctNpPolice
#define ctNpSetAttribute	SPXctNpSetAttribute   
#define ctNpGetAttribute	SPXctNpGetAttribute
#define ctNpStart		SPXctNpStart
#define ctNpStop		SPXctNpStop
#define ctNpOpen		SPXctNpOpen
#define ctNpClose		SPXctNpClose
#define ctNpWrite		SPXctNpWrite
#define ctNpRead		SPXctNpRead
#define ctNpPackSiz		SPXctNpPackSiz
#define ctNpMakeNmPipe		SPXctNpMakeNmPipe
#define ctNpDisconnectNmPipe	SPXctNpDisconnectNmPipe
#define ctNpConnectNmPipe	SPXctNpConnectNmPipe
#define ctNPCommCRC_LogErr	SPXctNPCommCRC_LogErr

/**/
#define ctNpGlobals		SPXctNpGlobals
#define NPfree			SPXNPfree
#define NPalloc			SPXNPalloc
#define NPwaitWhile		SPXNPwaitWhile
#define NPdefer			SPXNPdefer
#define NPcttcre		SPXNPcttcre
#define NPrevobj		SPXNPrevobj
#define NPctsemrqs		SPXNPctsemrqs
#define NPctsemclr		SPXNPctsemclr
#define NPctsemwat		SPXNPctsemwat
#define NPctblkrqs		SPXNPctblkrqs
#define NPctblkclr		SPXNPctblkclr
#define NPctblkwat	       	SPXNPctblkwat
#define NPcttimrqs		SPXNPcttimrqs
#define NPcttimclr		SPXNPcttimclr
#define NPcttimwat		SPXNPcttimwat
#define NPGetSrVariable		SPXNPGetSrVariable
#define NPusrstat		SPXNPusrstat
#define NPgetactivestatus	SPXNPgetactivestatus
#define NPsetinactive		SPXNPsetinactive
#define NPctrt_printf		SPXNPctrt_printf
#define NPUserAlive		SPXNPUserAlive
/**/
#define at_CommunicationPolice	SPXat_CommunicationPolice
#define at_CommunicationInit	SPXat_CommunicationInit
#define at_SessionSetAttribute	SPXat_SessionSetAttribute
#define at_SessionValidate	SPXat_SessionValidate
#define at_SessionNew		SPXat_SessionNew
#define at_SessionDispose	SPXat_SessionDispose
#define at_SessionOpen		SPXat_SessionOpen
#define at_SessionClose		SPXat_SessionClose
#define at_SessionSend		SPXat_SessionSend
#define at_SessionReceive	SPXat_SessionReceive
#define at_SessionMake		SPXat_SessionMake
#define at_SessionConnect	SPXat_SessionConnect
#define at_SessionDisconnect	SPXat_SessionDisconnect
#define at_CommunicationStart	SPXat_CommunicationStart
#define at_CommunicationStop	SPXat_CommunicationStop
/*#define find_syssem		SPXfind_syssem */
/*#define find_wait		SPXfind_wait */
#define VectorToBuffer		SPXVectorToBuffer
#define BufferToVector		SPXBufferToVector
#define IsPIDAlive		SPXIsPIDAlive
#endif /* ctUNXCOM_SPX */

#ifdef 	ctUNXCOM_SSLSPX
#define ctNpInit 		SSLSPXctNpInit
#define ctNpPolice		SSLSPXctNpPolice
#define ctNpSetAttribute	SSLSPXctNpSetAttribute   
#define ctNpGetAttribute	SSLSPXctNpGetAttribute
#define ctNpStart		SSLSPXctNpStart
#define ctNpStop		SSLSPXctNpStop
#define ctNpOpen		SSLSPXctNpOpen
#define ctNpClose		SSLSPXctNpClose
#define ctNpWrite		SSLSPXctNpWrite
#define ctNpRead		SSLSPXctNpRead
#define ctNpPackSiz		SSLSPXctNpPackSiz
#define ctNpMakeNmPipe		SSLSPXctNpMakeNmPipe
#define ctNpDisconnectNmPipe	SSLSPXctNpDisconnectNmPipe
#define ctNpConnectNmPipe	SSLSPXctNpConnectNmPipe
#define ctNPCommCRC_LogErr	SSLSPXctNPCommCRC_LogErr

/**/
#define ctNpGlobals		SSLSPXctNpGlobals
#define NPfree			SSLSPXNPfree
#define NPalloc			SSLSPXNPalloc
#define NPwaitWhile		SSLSPXNPwaitWhile
#define NPdefer			SSLSPXNPdefer
#define NPcttcre		SSLSPXNPcttcre
#define NPrevobj		SSLSPXNPrevobj
#define NPctsemrqs		SSLSPXNPctsemrqs
#define NPctsemclr		SSLSPXNPctsemclr
#define NPctsemwat		SSLSPXNPctsemwat
#define NPctblkrqs		SSLSPXNPctblkrqs
#define NPctblkclr		SSLSPXNPctblkclr
#define NPctblkwat	       	SSLSPXNPctblkwat
#define NPcttimrqs		SSLSPXNPcttimrqs
#define NPcttimclr		SSLSPXNPcttimclr
#define NPcttimwat		SSLSPXNPcttimwat
#define NPGetSrVariable		SSLSPXNPGetSrVariable
#define NPusrstat		SSLSPXNPusrstat
#define NPgetactivestatus	SSLSPXNPgetactivestatus
#define NPsetinactive		SSLSPXNPsetinactive
#define NPctrt_printf		SSLSPXNPctrt_printf
#define NPUserAlive		SSLSPXNPUserAlive
/**/
#define at_CommunicationPolice	SSLSPXat_CommunicationPolice
#define at_CommunicationInit	SSLSPXat_CommunicationInit
#define at_SessionSetAttribute	SSLSPXat_SessionSetAttribute
#define at_SessionValidate	SSLSPXat_SessionValidate
#define at_SessionNew		SSLSPXat_SessionNew
#define at_SessionDispose	SSLSPXat_SessionDispose
#define at_SessionOpen		SSLSPXat_SessionOpen
#define at_SessionClose		SSLSPXat_SessionClose
#define at_SessionSend		SSLSPXat_SessionSend
#define at_SessionReceive	SSLSPXat_SessionReceive
#define at_SessionMake		SSLSPXat_SessionMake
#define at_SessionConnect	SSLSPXat_SessionConnect
#define at_SessionDisconnect	SSLSPXat_SessionDisconnect
#define at_CommunicationStart	SSLSPXat_CommunicationStart
#define at_CommunicationStop	SSLSPXat_CommunicationStop
/*#define find_syssem		SSLSPXfind_syssem */
/*#define find_wait		SSLSPXfind_wait */
#define VectorToBuffer		SSLSPXVectorToBuffer
#define BufferToVector		SSLSPXBufferToVector
#define IsPIDAlive		SSLSPXIsPIDAlive
#endif /* ctUNXCOM_SSLSPX */
/*~***********************************/


/*^***********************************/
#ifdef 	ctUNXCOM_QUE
#define ctNpInit 		QUEctNpInit
#define ctNpPolice		QUEctNpPolice
#define ctNpSetAttribute   	QUEctNpSetAttribute   
#define ctNpGetAttribute	QUEctNpGetAttribute
#define ctNpStart		QUEctNpStart
#define ctNpStop		QUEctNpStop
#define ctNpOpen		QUEctNpOpen
#define ctNpClose		QUEctNpClose
#define ctNpWrite		QUEctNpWrite
#define ctNpRead		QUEctNpRead
#define ctNpPackSiz		QUEctNpPackSiz
#define ctNpMakeNmPipe		QUEctNpMakeNmPipe
#define ctNpDisconnectNmPipe	QUEctNpDisconnectNmPipe
#define ctNpConnectNmPipe	QUEctNpConnectNmPipe
#define ctNPCommCRC_LogErr	QUEctNPCommCRC_LogErr
/**/
#define ctNpGlobals		QUEctNpGlobals
#define NPfree			QUENPfree
#define NPalloc			QUENPalloc
#define NPwaitWhile		QUENPwaitWhile
#define NPdefer			QUENPdefer
#define NPcttcre		QUENPcttcre
#define NPrevobj		QUENPrevobj
#define NPctsemrqs		QUENPctsemrqs
#define NPctsemclr		QUENPctsemclr
#define NPctsemwat		QUENPctsemwat
#define NPctblkrqs		QUENPctblkrqs
#define NPctblkclr		QUENPctblkclr
#define NPctblkwat		QUENPctblkwat
#define NPcttimrqs		QUENPcttimrqs
#define NPcttimclr		QUENPcttimclr
#define NPcttimwat		QUENPcttimwat
#define NPGetSrVariable		QUENPGetSrVariable
#define NPusrstat		QUENPusrstat
#define NPgetactivestatus	QUENPgetactivestatus
#define NPsetinactive		QUENPsetinactive
#define NPctrt_printf		QUENPctrt_printf
#define NPUserAlive		QUENPUserAlive
/**/
#define at_CommunicationPolice	QUEat_CommunicationPolice
#define at_CommunicationInit	QUEat_CommunicationInit
#define at_SessionSetAttribute	QUEat_SessionSetAttribute
#define at_SessionValidate	QUEat_SessionValidate
#define at_SessionNew		QUEat_SessionNew
#define at_SessionDispose	QUEat_SessionDispose
#define at_SessionOpen		QUEat_SessionOpen
#define at_SessionClose		QUEat_SessionClose
#define at_SessionSend		QUEat_SessionSend
#define at_SessionReceive	QUEat_SessionReceive
#define at_SessionMake		QUEat_SessionMake
#define at_SessionConnect	QUEat_SessionConnect
#define at_SessionDisconnect	QUEat_SessionDisconnect
#define at_CommunicationStart	QUEat_CommunicationStart
#define at_CommunicationStop	QUEat_CommunicationStop
#define find_syssem		QUEfind_syssem
#define find_wait		QUEfind_wait
#define VectorToBuffer		QUEVectorToBuffer
#define BufferToVector		QUEBufferToVector
#define IsPIDAlive		QUEIsPIDAlive

#endif /* ctUNXCOM_QUE */
/*^***********************************/


/*^***********************************/
#ifdef 	ctUNXCOM_QNX
#define ctNpInit 		QNXctNpInit
#define ctNpPolice		QNXctNpPolice
#define ctNpSetAttribute   	QNXctNpSetAttribute   
#define ctNpGetAttribute	QNXctNpGetAttribute
#define ctNpStart		QNXctNpStart
#define ctNpStop		QNXctNpStop
#define ctNpOpen		QNXctNpOpen
#define ctNpClose		QNXctNpClose
#define ctNpWrite		QNXctNpWrite
#define ctNpRead		QNXctNpRead
#define ctNpPackSiz		QNXctNpPackSiz
#define ctNpMakeNmPipe		QNXctNpMakeNmPipe
#define ctNpDisconnectNmPipe	QNXctNpDisconnectNmPipe
#define ctNpConnectNmPipe	QNXctNpConnectNmPipe
#define ctNPCommCRC_LogErr	QNXctNPCommCRC_LogErr
/**/
#define ctNpGlobals		QNXctNpGlobals
#define NPfree			QNXNPfree
#define NPalloc			QNXNPalloc
#define NPwaitWhile		QNXNPwaitWhile
#define NPdefer			QNXNPdefer
#define NPcttcre		QNXNPcttcre
#define NPrevobj		QNXNPrevobj
#define NPctsemrqs		QNXNPctsemrqs
#define NPctsemclr		QNXNPctsemclr
#define NPctsemwat		QNXNPctsemwat
#define NPctblkrqs		QNXNPctblkrqs
#define NPctblkclr		QNXNPctblkclr
#define NPctblkwat		QNXNPctblkwat
#define NPcttimrqs		QNXNPcttimrqs
#define NPcttimclr		QNXNPcttimclr
#define NPcttimwat		QNXNPcttimwat
#define NPGetSrVariable		QNXNPGetSrVariable
#define NPusrstat		QNXNPusrstat
#define NPgetactivestatus	QNXNPgetactivestatus
#define NPsetinactive		QNXNPsetinactive
#define NPctrt_printf		QNXNPctrt_printf
#define NPUserAlive		QNXNPUserAlive
/**/
#define at_CommunicationPolice	QNXat_CommunicationPolice
#define at_CommunicationInit	QNXat_CommunicationInit
#define at_SessionSetAttribute	QNXat_SessionSetAttribute
#define at_SessionValidate	QNXat_SessionValidate
#define at_SessionNew		QNXat_SessionNew
#define at_SessionDispose	QNXat_SessionDispose
#define at_SessionOpen		QNXat_SessionOpen
#define at_SessionClose		QNXat_SessionClose
#define at_SessionSend		QNXat_SessionSend
#define at_SessionReceive	QNXat_SessionReceive
#define at_SessionMake		QNXat_SessionMake
#define at_SessionConnect	QNXat_SessionConnect
#define at_SessionDisconnect	QNXat_SessionDisconnect
#define at_CommunicationStart	QNXat_CommunicationStart
#define at_CommunicationStop	QNXat_CommunicationStop
#define find_syssem		QNXfind_syssem
#define find_wait		QNXfind_wait
#define VectorToBuffer		QNXVectorToBuffer
#define BufferToVector		QNXBufferToVector
#define IsPIDAlive		QNXIsPIDAlive

#endif /* ctUNXCOM_QNX */
/*~***********************************/


/*^***********************************/
#ifdef 	ctUNXCOM_BAN
#define ctNpInit 		BANctNpInit
#define ctNpPolice		BANctNpPolice
#define ctNpSetAttribute   	BANctNpSetAttribute   
#define ctNpGetAttribute	BANctNpGetAttribute
#define ctNpStart		BANctNpStart
#define ctNpStop		BANctNpStop
#define ctNpOpen		BANctNpOpen
#define ctNpClose		BANctNpClose
#define ctNpWrite		BANctNpWrite
#define ctNpRead		BANctNpRead
#define ctNpPackSiz		BANctNpPackSiz
#define ctNpMakeNmPipe		BANctNpMakeNmPipe
#define ctNpDisconnectNmPipe	BANctNpDisconnectNmPipe
#define ctNpConnectNmPipe	BANctNpConnectNmPipe
#define ctNPCommCRC_LogErr	BANctNPCommCRC_LogErr
/**/
#define ctNpGlobals		BANctNpGlobals
#define NPfree			BANNPfree
#define NPalloc			BANNPalloc
#define NPwaitWhile		BANNPwaitWhile
#define NPdefer			BANNPdefer
#define NPcttcre		BANNPcttcre
#define NPrevobj		BANNPrevobj
#define NPctsemrqs		BANNPctsemrqs
#define NPctsemclr		BANNPctsemclr
#define NPctsemwat		BANNPctsemwat
#define NPctblkrqs		BANNPctblkrqs
#define NPctblkclr		BANNPctblkclr
#define NPctblkwat		BANNPctblkwat
#define NPcttimrqs		BANNPcttimrqs
#define NPcttimclr		BANNPcttimclr
#define NPcttimwat		BANNPcttimwat
#define NPGetSrVariable		BANNPGetSrVariable
#define NPusrstat		BANNPusrstat
#define NPgetactivestatus	BANNPgetactivestatus
#define NPsetinactive		BANNPsetinactive
#define NPctrt_printf		BANNPctrt_printf
#define NPUserAlive		BANNPUserAlive
/**/
#define at_CommunicationPolice	BANat_CommunicationPolice
#define at_CommunicationInit	BANat_CommunicationInit
#define at_SessionSetAttribute	BANat_SessionSetAttribute
#define at_SessionValidate	BANat_SessionValidate
#define at_SessionNew		BANat_SessionNew
#define at_SessionDispose	BANat_SessionDispose
#define at_SessionOpen		BANat_SessionOpen
#define at_SessionClose		BANat_SessionClose
#define at_SessionSend		BANat_SessionSend
#define at_SessionReceive	BANat_SessionReceive
#define at_SessionMake		BANat_SessionMake
#define at_SessionConnect	BANat_SessionConnect
#define at_SessionDisconnect	BANat_SessionDisconnect
#define at_CommunicationStart	BANat_CommunicationStart
#define at_CommunicationStop	BANat_CommunicationStop
#define find_syssem		BANfind_syssem
#define find_wait		BANfind_wait
#define VectorToBuffer		BANVectorToBuffer
#define BufferToVector		BANBufferToVector
#define IsPIDAlive		BANIsPIDAlive

#endif /* ctUNXCOM_BAN */
/*^***********************************/


/*~***********************************/
#ifdef 	ctUNXCOM_NTP
#define ctNpInit 		NTPctNpInit
#define ctNpPolice		NTPctNpPolice
#define ctNpSetAttribute   	NTPctNpSetAttribute   
#define ctNpGetAttribute	NTPctNpGetAttribute
#define ctNpStart		NTPctNpStart
#define ctNpStop		NTPctNpStop
#define ctNpOpen		NTPctNpOpen
#define ctNpClose		NTPctNpClose
#define ctNpWrite		NTPctNpWrite
#define ctNpRead		NTPctNpRead
#define ctNpPackSiz		NTPctNpPackSiz
#define ctNpMakeNmPipe		NTPctNpMakeNmPipe
#define ctNpDisconnectNmPipe	NTPctNpDisconnectNmPipe
#define ctNpConnectNmPipe	NTPctNpConnectNmPipe
#define ctNPCommCRC_LogErr	NTPctNPCommCRC_LogErr
/**/
#define ctNpGlobals		NTPctNpGlobals
#define NPfree			NTPNPfree
#define NPalloc			NTPNPalloc
#define NPwaitWhile		NTPNPwaitWhile
#define NPdefer			NTPNPdefer
#define NPcttcre		NTPNPcttcre
#define NPrevobj		NTPNPrevobj
#define NPctsemrqs		NTPNPctsemrqs
#define NPctsemclr		NTPNPctsemclr
#define NPctsemwat		NTPNPctsemwat
#define NPctblkrqs		NTPNPctblkrqs
#define NPctblkclr		NTPNPctblkclr
#define NPctblkwat		NTPNPctblkwat
#define NPcttimrqs		NTPNPcttimrqs
#define NPcttimclr		NTPNPcttimclr
#define NPcttimwat		NTPNPcttimwat
#define NPGetSrVariable		NTPNPGetSrVariable
#define NPusrstat		NTPNPusrstat
#define NPgetactivestatus	NTPNPgetactivestatus
#define NPsetinactive		NTPNPsetinactive
#define NPctrt_printf		NTPNPctrt_printf
#define NPUserAlive		NTPNPUserAlive
/**/
#define at_CommunicationPolice	NTPat_CommunicationPolice
#define at_CommunicationInit	NTPat_CommunicationInit
#define at_SessionSetAttribute	NTPat_SessionSetAttribute
#define at_SessionValidate	NTPat_SessionValidate
#define at_SessionNew		NTPat_SessionNew
#define at_SessionDispose	NTPat_SessionDispose
#define at_SessionOpen		NTPat_SessionOpen
#define at_SessionClose		NTPat_SessionClose
#define at_SessionSend		NTPat_SessionSend
#define at_SessionReceive	NTPat_SessionReceive
#define at_SessionMake		NTPat_SessionMake
#define at_SessionConnect	NTPat_SessionConnect
#define at_SessionDisconnect	NTPat_SessionDisconnect
#define at_CommunicationStart	NTPat_CommunicationStart
#define at_CommunicationStop	NTPat_CommunicationStop
#define find_syssem		NTPfind_syssem
#define find_wait		NTPfind_wait
#define VectorToBuffer		NTPVectorToBuffer
#define BufferToVector		NTPBufferToVector
#define IsPIDAlive		NTPIsPIDAlive

#endif /* ctUNXCOM_NTP */
/*~***********************************/


/*^***********************************/
#ifdef 	ctUNXCOM_SHM
#define ctNpInit 		SHMctNpInit
#define ctNpPolice		SHMctNpPolice
#define ctNpSetAttribute   	SHMctNpSetAttribute   
#define ctNpGetAttribute	SHMctNpGetAttribute
#define ctNpStart		SHMctNpStart
#define ctNpStop		SHMctNpStop
#define ctNpOpen		SHMctNpOpen
#define ctNpClose		SHMctNpClose
#define ctNpWrite		SHMctNpWrite
#define ctNpRead		SHMctNpRead
#define ctNpPackSiz		SHMctNpPackSiz
#define ctNpMakeNmPipe		SHMctNpMakeNmPipe
#define ctNpDisconnectNmPipe	SHMctNpDisconnectNmPipe
#define ctNpConnectNmPipe	SHMctNpConnectNmPipe
#define ctNPCommCRC_LogErr	SHMctNPCommCRC_LogErr
/**/
#define ctNpGlobals		SHMctNpGlobals
#define NPfree			SHMNPfree
#define NPalloc			SHMNPalloc
#define NPwaitWhile		SHMNPwaitWhile
#define NPdefer			SHMNPdefer
#define NPcttcre		SHMNPcttcre
#define NPrevobj		SHMNPrevobj
#define NPctsemrqs		SHMNPctsemrqs
#define NPctsemclr		SHMNPctsemclr
#define NPctsemwat		SHMNPctsemwat
#define NPctblkrqs		SHMNPctblkrqs
#define NPctblkclr		SHMNPctblkclr
#define NPctblkwat		SHMNPctblkwat
#define NPcttimrqs		SHMNPcttimrqs
#define NPcttimclr		SHMNPcttimclr
#define NPcttimwat		SHMNPcttimwat
#define NPGetSrVariable		SHMNPGetSrVariable
#define NPusrstat		SHMNPusrstat
#define NPgetactivestatus	SHMNPgetactivestatus
#define NPsetinactive		SHMNPsetinactive
#define NPctrt_printf		SHMNPctrt_printf
#define NPUserAlive		SHMNPUserAlive
/**/
#define at_CommunicationPolice	SHMat_CommunicationPolice
#define at_CommunicationInit	SHMat_CommunicationInit
#define at_SessionSetAttribute	SHMat_SessionSetAttribute
#define at_SessionValidate	SHMat_SessionValidate
#define at_SessionNew		SHMat_SessionNew
#define at_SessionDispose	SHMat_SessionDispose
#define at_SessionOpen		SHMat_SessionOpen
#define at_SessionClose		SHMat_SessionClose
#define at_SessionSend		SHMat_SessionSend
#define at_SessionReceive	SHMat_SessionReceive
#define at_SessionReallocCommBuffer SHMat_SessionReallocCommBuffer
#define at_SessionMake		SHMat_SessionMake
#define at_SessionConnect	SHMat_SessionConnect
#define at_SessionDisconnect	SHMat_SessionDisconnect
#define at_CommunicationStart	SHMat_CommunicationStart
#define at_CommunicationStop	SHMat_CommunicationStop

#define find_syssem		SHMfind_syssem
#define find_wait		SHMfind_wait
#define VectorToBuffer		SHMVectorToBuffer
#define BufferToVector		SHMBufferToVector
#define IsPIDAlive		SHMIsPIDAlive
#endif /* ctUNXCOM_SHM */
/*^***********************************/

#endif /* ctUNXCOM_ACTIVE */
#endif /* ctCOM2H */

/* end of ctcom2.h */
