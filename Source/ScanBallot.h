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


#if !defined(AFX_SCANBALLOT_H__618A6761_9106_11D6_B481_00B0D0CDB4FC__INCLUDED_)
#define AFX_SCANBALLOT_H__618A6761_9106_11D6_B481_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ScannerInterface.h"
class CCount;

class CScanBallot
{
public:
	CString SerialString();
	BOOL ReadInfo(CString string);
	ClassYear GetYear() { return m_year; }
	CScanBallot(ClassYear year, int number, CCount* pCount);
	CString WriteInfo();
	~CScanBallot();
	BOOL ReadInfo(CCount* pCount, CScannerInterface* pSI);
	BOOL HasWriteIn();
	CString GetRIN() { return m_RIN; }
	void GetSerial(ClassYear& year, int& number) { year=m_year; number=m_number; }
	void SetStatus(BallotStatus status) { m_status=status; }
	BallotStatus GetStatus() { return m_status; }
	CByteList* GetCodeListAllAt(int position)  { return m_CodeListArray_all[position]; }
	CByteList* GetCodeListYearAt(int position) { return m_CodeListArray_year[position]; }
private:
	CString StripCodes(CString& string);
	CString WriteCodeList(CByteList* pCodeList);
	void FillCodeList(CString codes, CByteList* pCodeList);
	CString m_RIN;
	int m_number;
	ClassYear m_year;
	BallotStatus m_status;
	CArray<CByteList*, CByteList*> m_CodeListArray_all;  // the codes of the votes cast in the general elections
	CArray<CByteList*, CByteList*> m_CodeListArray_year; // the votes cast in the year specific elections 
};

#endif // !defined(AFX_SCANBALLOT_H__618A6761_9106_11D6_B481_00B0D0CDB4FC__INCLUDED_)