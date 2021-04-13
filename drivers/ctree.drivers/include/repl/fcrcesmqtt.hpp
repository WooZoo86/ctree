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

#ifndef _FCRCESMQTT_HPP_
#define _FCRCESMQTT_HPP_

#include "fc_rces.h"
#include "fcrcesconfig.hpp"
#include "fcrcesdataprov.hpp"

extern "C" {
    #include "fcrcesjson.h"
}

/*^****************************************************************************\
*
*   RCESMqtt
*   Recon-e-Sense MQTT class
*
*   Manage the MQTT broker
*
\******************************************************************************/
class RCESMqtt
{
    public:
        /* Constructors & destructor */
		RCESMqtt( int mqttPersistID, pRCESMasterProvider masterProv );
		RCESMqtt( pRCESMqttPersist mqttPersist, pRCESMasterProvider masterProv );
        virtual ~RCESMqtt();

        /* Public Services */
		static int ctMQTTCreate(pRCESMasterProvider masterProv, pRCESMqttPersist mqttPersist);
		static int ctMQTTCreate(pRCESMasterProvider masterProv, pRCESJson mqttPersist, ppRCESJson result);
		static int ctMQTTAlter(pRCESMasterProvider masterProv, pRCESMqttPersist mqttPersist);
		static int ctMQTTAlter(pRCESMasterProvider masterProv, pRCESJson mqttPersist, ppRCESJson result);
		static int ctMQTTRename(pRCESMasterProvider masterProv, int mqttPersistID, const char *newTopic);
		static int ctMQTTRename(pRCESMasterProvider masterProv, int mqttPersistID, const char *newTopic, ppRCESJson result);
		static int ctMQTTDelete(pRCESMasterProvider masterProv, int mqttPersistID);
		static int ctMQTTDelete(pRCESMasterProvider masterProv, int mqttPersistID, ppRCESJson result);
		static int ctMQTTPause(pRCESMasterProvider masterProv, int mqttPersistID);
		static int ctMQTTPause(pRCESMasterProvider masterProv, int mqttPersistID, ppRCESJson result);
		static int ctMQTTResume(pRCESMasterProvider masterProv, int mqttPersistID);
		static int ctMQTTResume(pRCESMasterProvider masterProv, int mqttPersistID, ppRCESJson result);

        /* Public Methods */
		pRCESMqttPersist GetMQTTPersist() { return _mqttPersist; };

    private:
        /* Private properties */
        pRCESConfig _config;
        pRCESLogger _logger;
        pRCESMasterProvider _provider;
		pRCESMqttPersist _mqttPersist;

        /* Private methods */
		void Create();
		void Alter();
		void Rename(const char *newTopic);
		void Delete();
		void Pause();
		void Resume();
};
/*~****************************************************************************/

/* Class type definitions */
typedef RCESMqtt *pRCESMqtt, **ppRCESMqtt;

#endif /* _FCRCESMQTT_HPP_ */