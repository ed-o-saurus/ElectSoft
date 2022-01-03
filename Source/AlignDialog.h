// ********************************************************************************
// **                                                                            **
// ** Copyright 2003 Edward F. Behn, Jr.                                         **
// **                                                                            **
// ** This file is part of Electsoft.                                            **
// **                                                                            **
// ** Electsoft is free software; you can redistribute it and/or modify it under **
// ** the terms of the GNU General Public License as published by the Free       **
// ** Software Foundation; either version 2 of the License, or (at your option)  **
// ** any later version.                                                         **
// **                                                                            **
// ** Electsoft is distributed in the hope that it will be useful, but WITHOUT   **
// ** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or      **
// ** FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for  **
// ** more details.                                                              **
// **                                                                            **
// ** You should have received a copy of the GNU General Public License along    **
// ** with Electsoft; if not, write to the Free Software Foundation, Inc.,       **
// ** 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA                    **
// **                                                                            **
// ** ElectSoft was written for use by the Rules and Elections Committee of the  **
// ** RPI Student Senate.  It may, however, be used by any organization.         **
// **                                                                            **
// ********************************************************************************


#if !defined(AFX_ALIGNDIALOG_H__12BC8B80_931D_11D7_8464_00B0D0CDB4FC__INCLUDED_)
#define AFX_ALIGNDIALOG_H__12BC8B80_931D_11D7_8464_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class CAlignDialog : public CDialog
{
public:
	BOOL m_changed;
	CAlignDialog(CWnd* pParent = NULL);
	enum { IDD = IDD_ALIGN };
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint() { CPaintDC dc(this); DrawImage(); } 
	DECLARE_MESSAGE_MAP()
private:
	void AddCircles(CPaintDC* pDC, CRect Rect);
	void AddGrid(CPaintDC* pDC, CRect Rect);
	void AddDot(CPaintDC* pDC, CRect Rect, CPoint center, CRect BoundingRect);
	CPoint PushInto(CPoint point, CRect BoundingRect);
	CPoint Angle(CRect rect, int angle);
	BOOL UpdatePos();
	void DrawImage();
	int m_Tpos, m_Rpos, m_Lpos, m_Bpos;
};

#endif // !defined(AFX_ALIGNDIALOG_H__12BC8B80_931D_11D7_8464_00B0D0CDB4FC__INCLUDED_)