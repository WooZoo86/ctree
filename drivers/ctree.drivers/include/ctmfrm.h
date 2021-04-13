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

#define ctSHOW_STATUS_BAR

//////////////////
// Main frame for CTSMFC.
//
class CMainFrame : public CFrameWnd {
public:
	CMainFrame();
	virtual ~CMainFrame();
	
protected:
	DECLARE_DYNAMIC(CMainFrame)
	CBitmap		*m_pMainBmp;	// Main window bitmap.
	CConsWnd	*m_pFuncWnd;	// Function monitor window.
	CConsWnd	*m_pConsWnd;	// Message monitor window.
#ifdef ctSHOW_STATUS_BAR
	CStatusBar	m_wndStatusBar;	// Main window status bar.
#endif
	BOOL		m_bShutdown;	// Indicates if OK to terminate CTSMFC.
	BOOL		m_isPainted;	// Indicates if main window needs repaint.
	BOOL		m_bCheckConsole;// Message monitor window status.
	int		m_iCheckMonitor;// Function monitor window status.
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMainFrame)
	afx_msg LRESULT OnTrayNotification(WPARAM wp, LPARAM lp);
	afx_msg LRESULT OnUpdateBitmap(WPARAM uID, LPARAM lEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnAppOpen();
	afx_msg void OnControlShutdown();
	afx_msg void OnViewServerfunctionmonitor();
	afx_msg void OnPaint();
	afx_msg void OnViewServerconsolescreen();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryEndSession();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/* end of ctmfrm.h */
