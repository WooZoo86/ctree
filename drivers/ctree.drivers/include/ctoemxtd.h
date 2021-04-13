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

#ifndef __CTOEMXTD_H__
#define __CTOEMXTD_H__

#ifdef ctPortACE_EXPRESS_HANDSHAKE_V9_0_0
#include "ct_acehs.h"
#endif

#ifdef ctPortAMICUS
#include "ctsplg.h"
#endif

#ifdef ctPortTLT
#include "ct_tlt.h"
#endif

#ifdef ctPortHCL
#include "ct_hcl.h"
#endif

#ifdef ctPortNUMEGA_TR
#include "ct_ntr.h"
#endif

#ifdef ctPortATTACH2
#include "ctatache.h"
#endif

#ifdef ctPortMSIGA
#include "ct_msiga.h"
#endif

#ifdef ctPortIMAGENOW
#include "ctimgnow.h"
#endif

#ifdef ctPortZEACOM
#include "ctzeacom.h"
#endif

#ifdef ctPortACI
#include "ctaciaci.h"
#endif

#ifdef ctPortVISA
#include "ctvisaci.h"
#endif

#ifdef ctPortCGM
#include "ct_cgm.h"
#endif

#ifdef ctPortVERYANT
#include "ctvryant.h"
#endif

#ifdef ctPortBENEFITPLAN
#include "ctbenplan.h"
#endif

#ifdef ctPortGREENBOX
#include "ctupswce.h"
#endif

#ifdef ctPortUPS_BRUCE
#include "ctupsbrc.h"
#endif

#ifdef ctPortTDSRX30
#define  ctCTARTECH_H 	"ctartech.h"
#include ctCTARTECH_H
#endif

#ifdef ctPortDENTRIX
#define  ctCTDENTRIX_H 	"ctdentrix.h"
#include ctCTDENTRIX_H
#endif

#ifdef ctPortAPPMAT
#define  ctCTAPPMAT_H	"ctappmat.h"
#include ctCTAPPMAT_H
#endif

#ifdef ctPortADVENT
#define  ctCTADVENT_H	"ctadvent.h"
#include ctCTADVENT_H
#endif

#ifdef ctPortUSE_THIS /* OLD EURO2000 */
#define  ctCTEURO2000_H	"cteuro2000.h"
#include ctCTEURO2000_H
#endif

#ifdef ctPortBRACOBOL
#define  ctCTBRACOBOL_H	"ctbracobol.h"
#include ctCTBRACOBOL_H
#endif

#ifdef ctPortCOBOLIT
#define  ctCTCOBOLIT_H 	"ctcobolit.h"
#include ctCTCOBOLIT_H
#endif

#ifdef ctPortUSE_THIS /* OLD METODO */
#define  ctCTMETODO_H	"ctmetodo.h"
#include ctCTMETODO_H
#endif

#ifdef ctPortMICROFOCUS
#define  ctCTMFOCUS_H	"ctmfocus.h"
#include ctCTMFOCUS_H
#endif

#ifdef ctPortCHARGER1
#define  ctCTCHRGR1_H	"ctchrgr1.h"
#include ctCTCHRGR1_H
#endif

#ifdef ctPortACECOBOL
#ifndef ctPortCOBOLIT
#ifndef ctPortCGM
#define  ctCTACECOBOL_H	"ctacecobol.h"
#include ctCTACECOBOL_H
#endif
#endif
#endif

#ifdef ctPortABACUS
#define  ctCTABACUS_H	"ctabacus.h"
#include ctCTABACUS_H
#endif

#ifdef ctPortCGMFRIE
#define  ctCTABACUS_H	"ct_cgmfrie.h"
#include ctCTABACUS_H
#endif

#ifdef ctPortNEXTOEM
#define  ctCTNEXTOEM_H	"ct_nextoem.h"
#include ctCTNEXTOEM_H
#endif

/* ctSIBLING_HANDSHAKE_006 */
/*
** Turn on the ACE handshake for those OEMs that do not have their own
** handshake. ctPortFAIRCOM_STANDARD is a special case that we want to
** have no handshake.
*/
#ifndef ctLCBYT
#ifndef ctPortFAIRCOM_STANDARD
#define ctPortACE_EXPRESS_HANDSHAKE_V9_0_0
#include "ct_acehs.h"
#endif
#endif


/* ctSIBLING_HANDSHAKE - ctSIBLING_EXPRESS_HANDSHAKE
Add the OEM special header file. This is the header file
that will set the OEM specific ctLCBYT that is used in the handshake.
*/
/********************************/
#ifndef ctExpressLCBYTVAL_V1
#define ctExpressLCBYTVAL_V1 0x0000
#endif
#ifndef ctExpressLCBYTVAL
#define ctExpressLCBYTVAL 0x0000
#endif
#ifndef ctExpressLCBYTRNG
#define ctExpressLCBYTRNG 0
#endif
#ifndef ctExpressLCBYTSRV
#define ctExpressLCBYTSRV 0x0000
#endif
/********************************/

#endif /* ~__CTOEMXTD_H__ */
/* end of ctoemxtd.h */
