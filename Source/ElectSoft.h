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


#if !defined(AFX_ELECTSOFT_H__8D75FFC4_677A_11D6_B47E_00B0D0CDB4FC__INCLUDED_)
#define AFX_ELECTSOFT_H__8D75FFC4_677A_11D6_B47E_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "ElectSoftView.h"
#include "RegistyInterface.h"
#include "Printing.h"
#include "Scanning.h"

class CElectSoftApp : public CWinApp
{
public:
	void StartPrinting(CElectSoftView* pView, UINT AlignmentRate, ClassYear year, UINT size);
	void StopPrinting();
	
	void StartScanning(CElectSoftView* pView, BOOL voiding);
	void StopScanning();
	
#ifdef _SIM_BALLOT
	CStringList m_InputBallots;
#endif
	CString m_GPL;
	
	struct st_PrintInfo  // info used by the print thread 
	{
	public:
		CWinThread* pThread;
		BOOL bRunning;
		BOOL bKill;
		CElectSoftView* pView;
		UINT AlignmentRate;
		ClassYear year;
		UINT size;
		CPrintBallot* pPBallot;
	} m_PrintInfo;
	
	struct st_ScanInfo  // info used by the print thread 
	{
	public:
		CWinThread* pThread;
		BOOL bRunning;
		BOOL bKill;
		CElectSoftView* pView;
		BOOL voiding;
		CScanBallot* pSBallot;
	} m_ScanInfo;
	
	struct st_AlignInfo  // info used to align the printer
	{
	public:
		st_AlignInfo() { bx=343; mx=240.0F; by=486; my=240.0F; }
		CPoint translate(float x, float y) { return CPoint(bx+(int)(mx*x), by+(int)(my*y)); } // translates grid coordinates to physical ones 
		void ChangeParameters(int Tpos, int Rpos, int Lpos, int Bpos);
	private:
		int bx, by;
		float mx, my;
	} m_AlignInfo;
	
	DECLARE_MESSAGE_MAP()
private:
	virtual BOOL InitInstance();
	afx_msg void OnAppAbout();
	void FillGPL();
};

#endif // !defined(AFX_ELECTSOFT_H__8D75FFC4_677A_11D6_B47E_00B0D0CDB4FC__INCLUDED_)