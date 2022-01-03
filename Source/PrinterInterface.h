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


#if !defined(AFX_PRINTERINTERFACE_H__586A8BC0_9532_11D7_8464_00B0D0CDB4FC__INCLUDED_)
#define AFX_PRINTERINTERFACE_H__586A8BC0_9532_11D7_8464_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WATER_MARK 220

class CPrinterInterface
{
public:
	CPrinterInterface();
	BOOL PrintAlignment();
	BOOL Print(ClassYear year, CElectSoftDoc* pDoc, BOOL Sample=false);
	BOOL static PrintQueue(DWORD& cJobs);
	BOOL static CheckPrinterConfig();
private:
	void AddCandidate(UINT col, UINT row, BOOL Sample, CGroup* pGroup, int cc);
	CString WriteYearCode(ClassYear year);
	void AddSeperator(UINT col, UINT row);
	void PlotInfo(BOOL Sample, ClassYear year, CElectSoftDoc* pDoc);
	void FillRandList(CByteList* pRandList, int size);
	void AddRace(CPrintRace* pPRace, BOOL Sample);
	void Arrow(UINT col, UINT row, CString candidate);
	void AddSerial(ClassYear year, int number, BOOL Sample, CElectSoftDoc* pDoc);
	void AddLine(UINT col, UINT row, CString text, BOOL bold);
	void BallotVoid();
	void AddHeading(ClassYear year, CElectSoftDoc* pDoc);
	void AddDot(int x, int y);
	
#ifdef _SIM_BALLOT
	char m_sheet[48][63];
#else
	void SetUpDC();
	BOOL TextOut(float x, float y, CString string);
	void AddAlignment();
	CDC* m_pDC;
#endif
	BYTE m_patterns[32];
};

#endif // !defined(AFX_PRINTERINTERFACE_H__586A8BC0_9532_11D7_8464_00B0D0CDB4FC__INCLUDED_)
