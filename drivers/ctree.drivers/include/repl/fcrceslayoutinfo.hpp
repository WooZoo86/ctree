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

#ifndef _FCRCESLAYOUTINFO_HPP_
#define _FCRCESLAYOUTINFO_HPP_

#include "fc_rces.h"
#include "fcaux.hpp"

extern "C" {
#include "fcrcesjson.h"
}

/* Class type definitions */
class RCESLayoutInfo;
class RCESConn;
typedef RCESLayoutInfo *pRCESLayoutInfo, **ppRCESLayoutInfo;
typedef RCESConn *pRCESConn, **ppRCESConn;

#define RCES_LAYOUTINFO_OBJ "layoutInfo"
#define RCES_LAYOUTINFO_LIST "layoutInfoList"
#define RCES_LAYOUTINFO_ID "id"
#define RCES_LAYOUTINFO_LAYOUTIDX "layoutIdx"
#define RCES_LAYOUTINFO_DESCRIPTION "description"
#define RCES_LAYOUTINFO_ZOOM "zoom"
#define RCES_LAYOUTINFO_TOTAL "total"
#define RCES_LAYOUTINFO_PANX "panX"
#define RCES_LAYOUTINFO_PANY "panY"


/*^****************************************************************************\
*
*   RCESLayoutInfo
*   Recon-e-Sense Layout class
*
\******************************************************************************/
class RCESLayoutInfo
{
public:
	/* Constructors & destructor */
	RCESLayoutInfo();
	RCESLayoutInfo( pRCESJson layoutInfo );
	virtual ~RCESLayoutInfo();

	/* Public services */
	static int ctGetLayoutInfo( pRCESMasterProvider masterProv, int layout, bool isPaging, int layoutInfoListSize, int layoutInfoStart, ppRCESJson result  );

	static int ctGetLayoutInfo( pRCESMasterProvider masterProv, int layout, int layoutInfoListSize, int layoutInfoStart, 
		ppRCESLayoutInfo *layoutInfoList, int *layoutInfoCount, int *totalLayoutInfos );

	static int ctPersistLayoutInfo( pRCESMasterProvider masterProv, pRCESLayoutInfo layoutInfo );
	static int ctPersistLayoutInfo( pRCESMasterProvider masterProv, pRCESJson layoutInfo, ppRCESJson result );
	static int ctRemoveLayoutInfo( pRCESMasterProvider masterProv, int layout);
	static int ctRemoveLayoutInfo( pRCESMasterProvider masterProv, int layout, ppRCESJson result );


	/* Public methods */
	int GetID() { return _id; };
	int GetLayout() { return _layoutIdx; };
	const char *GetDescription() { return _description; };
	int GetZoom() {return _zoom; };
	int GetPanX() {return _panX; };
	int GetPanY() {return _panY; };

	void SetID( int id ) { _id = id; };
	void SetLayout( int layout ) { _layoutIdx = layout; };
	void SetDescription( const char *description );
	void SetZoom( int zoom ) { _zoom = zoom; };
	void SetPanX( int panX ) { _panX = panX; };
	void SetPanY( int panY ) { _panY = panY; };

	pRCESJson GetJson();

private:
	/* Private properties */
	int _id;
	int _layoutIdx;
	char * _description;
	int _zoom;
	int _panX;
	int _panY;
};
/*~****************************************************************************/

#endif /* _FCRCESLAYOUTINFO_HPP_ */