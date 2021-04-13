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
This header is used for FairCom ADD-ON'S and special settings for 
extra functionality added by FairCom to the Dharma engine.
*/

#ifndef	 __CTSQLRAY_H__
#define  __CTSQLRAY_H__

#ifdef 	_DEBUG
/* #define FAIRCOM_MOD_HELPER */
#endif

#ifdef 	ctPortNLM
/* #define FAIRCOM_MOD_HELPER */
#endif

/*~****************************************/
#ifdef FAIRCOM_MOD_HELPER
/* The following section defined the FairCom Helper Function. This function is strategically called from
key locations in the engine in order to facilitate an easy centralized place by which debugger breakpoints can be added.
*/

/* Location codes form the FairModHelper function */

/*^****************************************/
/*~****************************************/


/*^****************************************/
/*  
fcHELPER_LOC_JUST_BEFORE_SQL_THREAD_LAUNCH:
..\ctreeSDK\ctreeAPI\ctree\source\ctsqlsys.c 

You are now inside of ctLaunchSQL() which is the SQL subsystem launch function 
that is called from ctsrvr.c's mainline. This is just before the dmnxx_main 
function gets launched as a thread.
*/
#define fcHELPER_LOC_JUST_BEFORE_SQL_THREAD_LAUNCH	10	
/*~****************************************/


/*^****************************************/
/* fcHELPER_LOC_OS_ACCEPT_XXXX: ..\ctreeSDK\ctreeAPI\ctree\sql\src\snw\snr\tcp_dmn.cxx 
Here we are in 'dmn_start' and are looping on os_accept. This is the SQL looping 
thread that looks for incoming connections by calling the 'os_accept' function.
It will wait here until an SQL Client comes in.

FairModHelper()
dmn_start()
StartListenerService()
dmn_main()
server_main()
dmnxx_main()
ThreadStub()


We have 2 spots here:
fcHELPER_LOC_OS_ACCEPT_TOP_OF_LOOP: 	is at the top of the loop
fcHELPER_LOC_OS_ACCEPT_AFTER:		is just after a incoming low-level accept.
*/
#define fcHELPER_LOC_OS_ACCEPT_TOP_OF_LOOP	20
#define fcHELPER_LOC_OS_ACCEPT_AFTER		30	
/*~****************************************/


/*^****************************************/
/* 
fcHELPER_LOC_createthread_async_dsn_listen:

We are now in run_async_dsn_listen() wich was called by dmn_start(). 
run_async_dsn_listen() 's job is to launch a new thread "async_dsn_listen". Then 
the 'run_async_dsn_listen()' function returns to the primary accept loop, which 
in turn then looks for another connection. This is just before we launch the 
async_dsn_listen thread. We suspect that the overhead of setting up a new SQL 
connection (users) takes a long time, so Dhrama used this technique to launch 
async_dsn_listen (new user stuff) so that it could get right back quicky to the 
next os_accept, to speed up logins.

Call Stack:
FairModHelper()
run_async_dsn_listen()
dmn_start()
StartListenerService()
dmn_main()
server_main()
dmnxx_main()
ThreadStub()

*/
#define fcHELPER_LOC_createthread_async_dsn_listen	40	
/*~****************************************/


/*^****************************************/
/*
fcHELPER_LOC_async_dsn_listen_dsn_listen:

Here I am in the async_dsn_listen thread, and am about to call nethdl->dsn_listen. 
The nethdl->dsn_listen function looks like it is where the some 
type of individual context (handle; user; ?) is now being applied to the logic. 
Once we are in the nethdl->dsn_listen, references are "user/context (rays 
words)?", and we have the network read loop in nethdl->dsn_listen.

Call Stack:
FairModHelper()
async_dsn_listen()
ThreadStub()
*/

#define fcHELPER_LOC_async_dsn_listen_dsn_listen 50
/*~****************************************/



/*^****************************************/

/*
fcHELPER_LOC_dsn_listen_loop_top:

Here we are in dsn_status_t dnw_hdl_t::dsn_listen (dsn_svr_t sid, dh_i32_t flags, void *heap_info)
This is where it looks like we are placed in a loop reading from the network. 
This spot is at the top of this "read while loop".

Call Stack:
FairModHelper()
dnw_hdl_t::dsn_listen()
async_dsn_listen()
ThreadStub()
*/

#define fcHELPER_LOC_dsn_listen_loop_top	55	
/*~****************************************/


/*^****************************************/
/*
fcHELPER_LOC_dsn_listen_before_peek:
..\ctreeSDK\ctreeAPI\ctree\sql\src\snw\snr\snr_nw.cxx

This looks like a major pivot point. This is just BEFORE the call to:

	st = ((dxp_rptcphdl_t *) dxp_hdl)->dxp_pek (
		this,&pkt_hdr, hdr_len, xprcv_pkt, &xprcv_len,
	    		&xprel_pkt, &xprel_len, use_timeout);

This call (I think) does some type of network "peek" to check for incomming data 
from the network.

Call Stack:
FairModHelper()
dnw_hdl_t::dsn_listen()
async_dsn_listen()
ThreadStub()
*/
#define fcHELPER_LOC_dsn_listen_before_peek	60	
/*~****************************************/


/*^****************************************/
/*
fcHELPER_LOC_dsn_listen_after_peek:
..\ctreeSDK\ctreeAPI\ctree\sql\src\snw\snr\snr_nw.cxx

This looks like a major pivot point. This is just AFTER the call to:

	st = ((dxp_rptcphdl_t *) dxp_hdl)->dxp_pek (
		this,&pkt_hdr, hdr_len, xprcv_pkt, &xprcv_len,
	    		&xprel_pkt, &xprel_len, use_timeout);

This call (I think) does some type of network "peek" to check for incomming data 
from the network.

Call Stack:
FairModHelper()
dnw_hdl_t::dsn_listen()
async_dsn_listen()
ThreadStub()
*/
#define fcHELPER_LOC_dsn_listen_after_peek	61	
/*~****************************************/


/*^****************************************/
/*
fcHELPER_LOC_dxp_pek_before_select:
..\sql\src\snw\snr\snr_tcp.cxx
Here we are in the dxp_pek function and because there is a timeout value 
defined, we will go into a os_select() loop, timimg out while looking at the 
tcp/ip socket with the os_select() function.
This is just BEFORE that call to os_select()
*/
#define fcHELPER_LOC_dxp_pek_before_select 70
/*~****************************************/


/*^****************************************/
/*
fcHELPER_LOC_dxp_pek_after_select
..\sql\src\snw\snr\snr_tcp.cxx
Here we are in the dxp_pek function and because there is a timeout value 
defined, we will go into a os_select() loop, timimg out while looking at the 
tcp/ip socket with the os_select() function.
This is just AFTER that call to os_select()
*/
#define fcHELPER_LOC_dxp_pek_after_select 71
/*~****************************************/


/*^****************************************/
/*
fcHELPER_LOC_dxp_pek_before_recv
..\sql\src\snw\snr\snr_tcp.cxx
Here we are in the dxp_pek function we are just about to do an os_revc
to read data from the network.
This is just BEFORE that call to os_recv()
*/
#define fcHELPER_LOC_dxp_pek_before_recv	80
/*~****************************************/


/*^****************************************/
/*
fcHELPER_LOC_dxp_pek_after_recv
..\sql\src\snw\snr\snr_tcp.cxx
Here we are in the dxp_pek function we are just about to do an os_revc
to read data from the network.
This is just AFTER that call to os_recv()
*/
#define fcHELPER_LOC_dxp_pek_after_recv		81
/*~****************************************/



/*^****************************************/
/*
fcHELPER_LOC_ADDWRK1:
..\ctreeAPI\ctree\sql\src\snw\snr\snr_nw.cxx 

Here we are in the main network read loop in dsn_listen() (snr_nw.cxx). We are 
about to perform some work, so this spot is just after the FairCom call to 
ctaddwork(). 

Call Stack:
FairModHelper()
dnw_hdl_t::dsn_listen()
async_dsn_listen()
ThreadStub()
*/

#define fcHELPER_LOC_ADDWRK1		90	
/*~****************************************/



/*^****************************************/
/*
fcHELPER_LOC_RMVWRK1:
..\ctreeAPI\ctree\sql\src\snw\snr\snr_nw.cxx 

Here we are in the main network read loop in dsn_listen() (snr_nw.cxx). We are 
done performing some work, so this spot is just after the FairCom call to 
ctrmvwork().


Just after:

 		st = fp ((dh_u8_t *) this, pkt, pkt_hdr.msg_len,
  		    ssrcv_pkt, &ssrcv_len, &ssrel_pkt, &ssrel_len,
  		    &mstat);
 

Call Stack:
FairModHelper()
dnw_hdl_t::dsn_listen()
async_dsn_listen()
ThreadStub()
*/

#define fcHELPER_LOC_RMVWRK1		95	
/*~****************************************/


/*^****************************************/
/* fcHELPER_LOC_find_svr_launch_rds_main:

We are just before the location where the rds_main() Thread gets launched for a 
user Here we are in the find_svr() function:


Call Stack:
FairModHelper()
find_svr_pvt()
find_svr1()
find_svr1_ss()
dnw_hdl_t::dsn_listen()
async_dsn_listen()
ThreadStub()
*/
#define fcHELPER_LOC_find_svr_launch_rds_main	100	
/*~****************************************/



/*^****************************************/
/* fcHELPER_LOC_rds_main:
Here I am at the top of the rds_main() thread logic.
I think this is to top of the user's thread that will now 
handle the user'rs request. We will see? 
Call Stack:
FairModHelper()
rds_main()
ThreadStub()
*/
#define fcHELPER_LOC_rds_main		110
/*~****************************************/




/*^****************************************/
/* fcHELPER_LOC_SQL_PARSER
Here we parse the statement and produce the execution 
plan.
Call Stack:
FairModHelper()
ssm_env_t::ssm_get_tree()
ssm_open_pvt()
ssm_open()
ddm_get_idcase()
setDatabaseCase()
sql_attach()
rem_attach()
rem_attach_ss()
dnw_hdl_t::dsn_listen()
dsn_listen()
cm_rp_nethdl_t::cm_rp_exec()
rds_main()
ThreadStub()
*/
#define fcHELPER_LOC_SQL_PARSER		200
/*~****************************************/


/*^****************************************/
/* fcHELPER_LOC_SQL_OPTIMIZER
Here we start the optimization of the execution plan
Call Stack:
FairModHelper()
ssm_env_t::ssm_get_tree()
ssm_open_pvt()
ssm_open()
ddm_get_tblid()
psr_env_t::psr_chk_tbl()
psr_env_t::RDS_parse()
psr_env_t::psr_parse_stmt()
psr_env_t::psr_parse()
ssm_env_t::ssm_get_tree()
ssm_open_pvt()
ssm_open()
ddm_get_idcase()
setDatabaseCase()
sql_attach()
rem_attach()
rem_attach_ss()
dnw_hdl_t::dsn_listen()
dsn_listen()
cm_rp_nethdl_t::cm_rp_exec()
rds_main()
ThreadStub()
*/
#define fcHELPER_LOC_SQL_OPTIMIZER	205
/*~****************************************/



#define fcHELPER_LOC_FNCMON1				210	/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\rds\sql_iapi.cxx */
#define fcHELPER_LOC_FNCMON2				220	/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\rds\sql_iapi.cxx */
#define fcHELPER_LOC_FNCMON3				230	/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\rds\sql_iapi.cxx */
#define fcHELPER_LOC_SETTIMEOUT				240	/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\rds\sql_iapi.cxx */
#define fcHELPER_LOC_CURTIMEOUT				250	/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\rds\ssm_curm.cxx */
#define fcHELPER_LOC_PANIC				260	/* ..\ctreeSDK\ctreeAPI\ctree\sql\src\public\err\rss_misc.cxx*/

/*~****************************************/


/*******************************************************************************************************/
/*******************************************************************************************************/
/* SQL Client Side Defines: */

	
/*^****************************************/
/*
fcHELPER_CLI_os_connect_timed_windows
..\\sql\src\public\os\windows\os_net.cxx

Here we are in the os_connect_timed() function on the client-side for windows and we are abount to call
the connect() network function to connect to a server.
Call Stack:
isql.exe!os_connect_timed()
isql.exe!dxp_rqtcphdl_t::dxp_rqtcphdl_t()
isql.exe!dxp_hdl_t::dxp_build_clthdl()
isql.exe!dnw_hdl_t::dsn_build_clthdl()
isql.exe!cm_rq_nethdl_t::cm_rq_nethdl_t()
isql.exe!db_dh_hdl_t::db_dh_hdl_t()
isql.exe!sql_env_t::iattach()
isql.exe!sql_env_t::attach()
isql.exe!sql_env_t::connect()
isql.exe!dh_sqlconnect()
isql.exe!tpe_sqlconnect()
isql.exe!main()
*/
#define fcHELPER_CLI_os_connect_timed_windows 5000
/*~****************************************/


/*******************************************************************************************************/
/*******************************************************************************************************/


/*^****************************************/
/* Operation Mode for the FairModHelper function*/
#define fcHELPER_OP_GENERAL				0	/* Nothing specific: Default */
/*~****************************************/

#ifdef __cplusplus
extern "C" {
#endif

	int FairModHelper(int location, int mode, void* buffer, long buflen);

#ifdef __cplusplus
}
#endif

#endif /* FAIRCOM_MOD_HELPER */
/*~*******************************************/

#endif /* ~__CTSQLRAY_H__ */

/* end of ctsqlray.h */
