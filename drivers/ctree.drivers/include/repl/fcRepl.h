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
*      Copyright (c) 2013 - 2015 FairCom Corporation.
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
*/

#ifndef _FCREPL_HPP_
#define _FCREPL_HPP_

/*^****************************************************************************\
*
*   Faircom Replication API C/C++
*
\******************************************************************************/
#include "fcReplTrace.hpp"
#include "fcReplLog.hpp"
#include "fcReplConn.hpp"
#include "fcReplSite.hpp"
#include "fcReplHardware.hpp"
#include "fcReplOpSystem.hpp"
#include "fcReplVolume.hpp"
#include "fcReplDBEngine.hpp"
#include "fcReplDatabase.hpp"
#include "fcReplFile.hpp"
#include "fcReplPlan.hpp"
#include "fcReplPublication.hpp"
#include "fcReplSubscription.hpp"
#include "fcReplAgent.hpp"
#include "fcReplAction.hpp"
#include "fcReplRedir.hpp"
#include "fcReplAgentConsumer.hpp"
#include "fcReplAvailGroup.hpp"
#include "fcReplReplica.hpp"

/* 
** Memory allocation 
*/
FCREPL_API void *FCREPLAlloc(int bufSize);
FCREPL_API void FCREPLFree(void *buffer);

/*^****************************************************************************\
*
*   FairCom Replication return codes
*
\******************************************************************************/
typedef enum
{
	FCREPL_SUCCESS = 0,             /* Success                                      */
	FCREPL_EOF = 1,                 /* Cursor is at EOF                             */
	FCREPL_DUPKEY = 2,              /* Key value already exists                     */
	FCREPL_NOTFOUND = 100,          /* Record not found                             */
	FCREPL_DISCONNECTED = 129,      /* Disconnected server                          */
	FCREPL_SERVERNOTFOUND = 133,    /* Not able to connect to server                */
	FCREPL_SHUTDOWN_ERR = 150,      /* Shutdown error                               */
	FCREPL_TIMEOUT_ERR = 156,       /* Timeout error                                */
	FCREPL_BATFINISHED = 428,       /* No more info; batch cancelled                */
	FCREPL_NOTSUP_ERR = 454,        /* Feature not supported yet                    */
	FCREPL_WARNING = 9000,          /* Warning error code                           */
	FCREPL_CONFIG_ERR = 9001,       /* Couldn't initialize the configuration object */
	FCREPL_LOGGER_ERR = 9002,       /* Couldn't initialize the logger object        */
	FCREPL_NOTIF_ERR = 9003,        /* Couldn't initialize the notification object  */
	FCREPL_FILESYSTEM_ERR = 9004,   /* Couldn't initialize the filesystem object    */
	FCREPL_PROVIDER_ERR = 9005,     /* Couldn't initialize the data provider object */
	FCREPL_INVARG_ERR = 9006,       /* Invalid argument count                       */
	FCREPL_INVARGVAL_ERR = 9007,    /* Invalid argument value                       */
	FCREPL_MISARG_ERR = 9008,       /* Missing required argument                    */
	FCREPL_HASHFULL_ERR = 9009,     /* Hash table exceeded the max size             */
	FCREPL_MEM_ERR = 9010,          /* Memory allocation error                      */
	FCREPL_QUEUEFULL_ERR = 9011,    /* Queue exceeded the max size                  */
	FCREPL_INVACTION_ERR = 9012,    /* Invalid notification action                  */
	FCREPL_QUEUE_ERR = 9013,        /* Queue is not initilized                      */
	FCREPL_MUTEX_ERR = 9014,        /* Mutex is not initilized                      */
	FCREPL_PROCTHRD_ERR = 9015,     /* Mutex is not start the process thread        */
	FCREPL_ACTION_ERR = 9016,       /* Invalid action                               */
	FCREPL_DB_TYPE_ERR = 9017,      /* Mismatch provider DB type                    */
	FCREPL_LOCALCT_ERR = 9018,      /* Couldn't load local c-tree library           */
	FCREPL_SESSION_ERR = 9019,      /* Couldn't allocate ctree session              */
	FCREPL_INVFLD_ERR = 9020,       /* Invalid field number                         */
	FCREPL_SCHEMATHRD_ERR = 9021,   /* Couldn't start schema update thread          */
	FCREPL_INTERN_ERR = 9022,       /* Internal error                               */
	FCREPL_REPL_ERR = 9023,         /* Couldn't initialize the replication object   */
	FCREPL_INVREPLOBJ_ERR = 9024,   /* Invalid replication object                   */
	FCREPL_STARTED_ERR = 9025,      /* Already started error                        */
	FCREPL_CONSUMER_ERR = 9026,     /* Consumer not found                           */
	FCREPL_ALREADYEX_ERR = 9027,    /* Already exists error                         */
	FCREPL_INVFILTYP_ERR = 9028,    /* Invalid file type                            */
	FCREPL_INVFILVOL_ERR = 9029,    /* Invalid file volume                          */
	FCREPL_REPLNDEP_ERR = 9030,     /* Replication plan is not deployed             */
	FCREPL_MISAUTH_ERR = 9031,      /* Missing authentication information           */
	FCREPL_FTRNSFR_ERR = 9032,      /* File transfer not initialized                */
	FCREPL_REPLACT_ERR = 9033,      /* Replication plan is not stopped              */
	FCREPL_REPLNFOUND_ERR = 9034,   /* Replication plan is not found                */
	FCREPL_INUSE_ERR = 9035,        /* Entity is in use                             */
	FCREPL_MISREPL_ERR = 9036,      /* Missing Replication Plan error               */
	FCREPL_MISDB_ERR = 9037,        /* Missing database in subscription             */
	FCREPL_MISVOL_ERR = 9038,       /* Missing volume information                   */
	FCREPL_FNOTFOUND_ERR = 9039,    /* File not found error                         */
	FCREPL_INVSUBS_ERR = 9040,      /* Invalid subscription                         */
	FCREPL_INVPATH_ERR = 9041,      /* Invalid file path                            */
	FCREPL_INVFUNC_ERR = 9042,      /* Invalid function                             */
	FCREPL_INVOS_ERR = 9043,        /* Invalid opSystem                             */
	FCREPL_NOTRUN_ERR = 9044,       /* Thread is not running                        */
	FCREPL_NACTIVE_ERR = 9045,      /* Replication Plan is not started              */
	FCREPL_MISLPOS_ERR = 9046,      /* Replication Plan is missing log position     */
	FCREPL_NCONN_ERR = 9047,        /* Agent is not connected                       */
	FCREPL_INVTOK_ERR = 9048,       /* Invalid token, it can be wrong or expired    */
	FCREPL_DBINUSE_ERR = 9049,      /* DBEngine is in use                           */
	FCREPL_REPLAGENT_ERR = 9050,    /* Replication agent error                      */
	FCREPL_MASTERNOTRDY_ERR = 9051, /* Master server is not ready yet               */
	FCREPL_MISSUBS_ERR = 9052,      /* Replication doesn't have any Subscription    */
	FCREPL_TARFIL_ERR = 9053,       /* Target file already exists                   */
	FCREPL_REPLDISC_ERR = 9054,     /* Replication agent is disconnected            */
	FCREPL_RESYNC_ERR = 9055,       /* Replication resync failed                    */
	FCREPL_INRESYNC_ERR = 9056,     /* Replication is in a resync operation now     */
	FCREPL_EREPLFILE_ERR = 9057,    /* Replication doesn't have any file            */
	FCREPL_CANCELLED_ERR = 9058,    /* Operation has been cancelled                 */
	FCREPL_RESTORE_ERR = 9059,      /* File dump restore error                      */
	FCREPL_SQLPORT_ERR = 9060,      /* SQL Port mismatch                            */
	FCREPL_REPLEXIST_ERR = 9061,    /* Replication Plan information already exist   */
	FCREPL_NINACTIVE_ERR = 9062     /* Replication Plan is not inactive             */
} FCREPLRET;

/*^****************************************************************************\
*
*   RCESDP return codes
*
\******************************************************************************/
typedef enum
{
	FCREPLDP_SUCCESS = 0,            /* RCESSDP API returned OK               */
	FCREPLDP_MEM_ERR = 9501,         /* Couldn't allocate memory              */
	FCREPLDP_INVHDL_ERR = 9502,      /* Invalid handle                        */
	FCREPLDP_INVSTR_ERR = 9503,      /* Invalid connection string             */
	FCREPLDP_PREPARE_ERR = 9504,     /* Error during the SQL command prepare  */
	FCREPLDP_MORE_RESULT = 9505,     /* There are more record to be retrieves */
	FCREPLDP_INVFILETYPE_ERR = 9506, /* Invalid file type                     */
	FCREPLDP_INVARG_ERR = 9507,      /* Invalid argument                      */
	FCREPLDP_MISSYM_ERR = 9508,      /* Missing symbol                        */
	FCREPLDP_CIRFIL_ERR = 9509,      /* Circular file replication             */
	FCREPLDP_NOFILE_ERR = 9510,      /* Empty publication                     */
} FCREPLDPRET;

#endif /* _FCFCREPL_HPP_ */