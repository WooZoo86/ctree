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
 *      Copyright (c) 2013 - 2014 FairCom Corporation.
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

#ifndef _FCRCESMQTTPERSISTFIELD_HPP_
#define _FCRCESMQTTPERSISTFIELD_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
	#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESMqttPersistField;
typedef RCESMqttPersistField *pRCESMqttPersistField, **ppRCESMqttPersistField;

#define RCES_MQTTPERSISTFIELD_PROPERTY "jsonPropertyPath"
#define RCES_MQTTPERSISTFIELD_FIELD_NAME "fieldName"
#define RCES_MQTTPERSISTFIELD_FIELD_TYPE "fieldType"
#define RCES_MQTTPERSISTFIELD_FIELD_WIDTH "fieldWidth"
#define RCES_MQTTPERSISTFIELD_FIELD_SCALE "fieldScale"

/*^****************************************************************************\
*
*   RCESMqttPersistField
*   Recon-e-Sense MQTT Persistence Field class
*
\******************************************************************************/
class RCESMqttPersistField
{
	public:
		/* Constructors & destructor */
		RCESMqttPersistField();
		RCESMqttPersistField(pRCESMqttPersistField mqttPersistField);
		RCESMqttPersistField(pRCESJson mqttPersistField);
		virtual ~RCESMqttPersistField();

		/* Public services */

		/* Public methods */
		const char *GetProperty() { return _property; };
		const char *GetFieldName() { return _fieldName; };
		const char *GetFieldType() { return _fieldType; };
		int GetFieldWidth() { return _fieldWidth; };
		int GetFieldScale() { return _fieldScale; };

		void SetProperty(const char *property);
		void SetFieldName(const char *fieldName);
		void SetFieldType(const char *fieldType);
		void SetFieldWidth(int fieldWidth) { _fieldWidth = fieldWidth; };
		void SetFieldScale(int fieldScale) { _fieldScale = fieldScale; };

		pRCESJson GetJson();

	private:
		/* private methods */
		void _init();

		/* Private properties */
		char *_property;
		char *_fieldName;
		char *_fieldType;
		int _fieldWidth;
		int _fieldScale;
};
/*~****************************************************************************/

#endif /* _FCRCESMQTTPERSISTFIELD_HPP_ */