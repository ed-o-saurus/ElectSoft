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


#if !defined(AFX_SCANBALLOTDIALOG_H__DE5E6320_8AF4_11D7_9809_00B0D0CDB4FC__INCLUDED_)
#define AFX_SCANBALLOTDIALOG_H__DE5E6320_8AF4_11D7_9809_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScanBallotDialog : public CDialog
{
// displays info about a scan ballot
public:
	CScanBallotDialog(CWnd* pParent = NULL);
	enum { IDD = IDD_SCANBALLOT };
	CScanBallot* m_pSBallot;
	CCount* m_pCount;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
private:
	void AddRace(CScanRace* pSRace, CByteList* pCodeList);
	void FillText();
	CString m_votes;
	void AddLine(CString line) { m_votes+=line+"\r\n"; }
	void AddLine() { AddLine(""); }
};

#endif // !defined(AFX_SCANBALLOTDIALOG_H__DE5E6320_8AF4_11D7_9809_00B0D0CDB4FC__INCLUDED_)