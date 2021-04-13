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

#ifndef _FCRCESLAYOUT_HPP_
#define _FCRCESLAYOUT_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESLayout;
class RCESConn;
typedef RCESLayout *pRCESLayout, **ppRCESLayout;
typedef RCESConn *pRCESConn, **ppRCESConn;

#define RCES_LAYOUT_OBJ "layout"
#define RCES_LAYOUT_LIST "layoutList"
#define RCES_LAYOUT_ID "id"
#define RCES_LAYOUT_LAYOUTID "layoutId"
#define RCES_LAYOUT_GROUPID "groupId"
#define RCES_LAYOUT_OBJECTTYPE "objectType"
#define RCES_LAYOUT_OBJECTID "objectId"
#define RCES_LAYOUT_POSX "posX"
#define RCES_LAYOUT_POSY "posY"
#define RCES_LAYOUT_HEIGHT "height"
#define RCES_LAYOUT_WIDTH "width"
#define RCES_LAYOUT_COLLAPSED "collapsed"
#define RCES_LAYOUT_TOTAL "total"

/*^****************************************************************************\
*
*   RCESLayout
*   Recon-e-Sense Layout class
*
\******************************************************************************/
class RCESLayout
{
public:
	/* Constructors & destructor */
	RCESLayout();
	RCESLayout( pRCESJson layout );
	virtual ~RCESLayout();

	/* Public services */
	static int ctGetLayouts( pRCESMasterProvider masterProv, int layoutId, bool isPaging, int layoutListSize, int layoutStart, ppRCESJson result  );


	static int ctGetLayouts( pRCESMasterProvider masterProv, int layoutId, int layoutListSize, int layoutStart, 
		ppRCESLayout *layoutList, int *layoutCount, int *layoutVolumes );

	static int ctPersistLayout( pRCESMasterProvider masterProv, pRCESLayout layout );
	static int ctPersistLayout( pRCESMasterProvider masterProv, int layoutId, pRCESJson layout, ppRCESJson result );
	static int ctRemoveLayouts( pRCESMasterProvider masterProv, int objectType, int objectId );
	static int ctRemoveLayouts( pRCESMasterProvider masterProv, int objectType, int objectID, ppRCESJson result );
	static int ctUpdateLayoutDbEngines(pRCESMasterProvider masterProv, ppRCESJson result);
	static int ctUpdateLayoutGroups(pRCESMasterProvider masterProv, ppRCESJson result);


	/* Public methods */
	int GetID() { return _id; };
	int GetLayoutID() { return _layoutId; };
	int GetObjectType() { return _objectType; };
	int GetObjectID() { return _objectId; };
	int GetPosX() {return _posX; };
	int GetPosY() {return _posY; };
	int GetHeigth() {return _height; };
	int GetWidth() {return _width; };
	bool GetCollapsed() {return _collapsed; };

	void SetID( int id ) { _id = id; };
	void SetLayoutID( int layout ) { _layoutId = layout; };
	void SetObjectType( int objectType ) { _objectType = objectType; };
	void SetObjectID( int objectId ) { _objectId = objectId; };
	void SetPosX( int posX ) { _posX = posX; };
	void SetPosY( int posY ) { _posY = posY; };
	void SetHeigth( int height ) { _height = height; };
	void SetWidth( int width ) { _width = width; };
	void SetCollapsed( bool collapsed ) { _collapsed = collapsed; };

	pRCESJson GetJson(bool full);

private:
	/* Private properties */
	int _id;
	int _layoutId;
	int _objectType;
	int _objectId;
	int _posX;
	int _posY;
	int _height;
	int _width;
	bool _collapsed;
};
/*~****************************************************************************/

#endif /* _FCRCESLAYOUT_HPP_ */