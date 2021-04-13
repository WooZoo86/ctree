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
 *	In addition:
 *	This Module also contains Proprietary Information of
 *	Dharma Systems Inc. and Dharma Systems (P) Ltd.  
 *	and should be treated as Confidential.
 *	
 *	Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *	Copyright (C) Dharma Systems Inc.        1992 - 2020.
 *	
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

#ifndef __stub_ssattrib
#define __stub_ssattrib

/* ssattr_attribute->type values */
#define SSATTRIB_INDEX  0x01
#define SSATTRIB_TABLE  0x02

#define SSATTRIB_NO     0x20
#define SSATTRIB_VALUED 0x40
#define SSATTRIB_OPTVAL 0x80


#define NUM_OF_SSATTR 12
typedef enum
{
	metadata_only   =  0,
	no_milliseconds =  1,
	preimg          =  2,
	ssa_partition   =  3,
	camo            =  4,
	advencryption   =  5,
	hotalter        =  6,
	hugefile        =  7,
	rowid           =  8,
	recbyt          =  9,
	deferred        = 10,
	block_compression = 11,
	invalid         = NUM_OF_SSATTR  /* this must be the last one, used to size array*/
} ssattribute_t;


struct ssattr_attribute
{
	dh_char_t *string;
	dh_u16_t attribute;
	dh_u16_t conflict;
	dh_u8_t type;
};


struct ssattr_values
{
	dh_char_t *string;
	dh_u16_t token;
};

class StorageAttrib_t
{
	public:
		static dh_char_t *VALUE_YES;
		static dh_char_t *VALUE_NO;
		static dh_char_t *VALUE_EMPTY;

	private:
		ssattr_values values[NUM_OF_SSATTR];

	// constructor & destructor
	public:
		StorageAttrib_t();
		~StorageAttrib_t();
		
	// Methods
		status_t Parse(dh_char_t *ss_attrib, dh_u8_t type);
		bool HasAttribute(ssattribute_t attr);
		dh_char_t *Value(ssattribute_t attr);
		status_t GetString(dh_char_t *ss_attrib, dh_u8_t type);
};

#endif 
