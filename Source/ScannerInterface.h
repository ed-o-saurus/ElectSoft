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


#if !defined(AFX_SCANNERINTERFACE_H__69254A20_F337_11D5_B47E_00B0D0CDB4FC__INCLUDED_)
#define AFX_SCANNERINTERFACE_H__69254A20_F337_11D5_B47E_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommSettings.h"
#include "ScanRace.h"
#define BUFFER_SIZE 16
#define THRESHOLD 0x04

class CScannerInterface
{
public:
	CScannerInterface();
	~CScannerInterface() { CloseComm(); }
	void FillCodeList(CScanRace* pSRace, CByteList* pCodeList);
	BOOL GetSerial(ClassYear &year, int &number);
	BOOL GetRIN(CString& RIN);
	BOOL CheckHopper();
	BOOL ScanBallot();
	BOOL CloseComm();
	BOOL OpenComm();
	BOOL HopperEmpty() { return m_HopperEmpty; }
	
private:
#ifndef _SIM_BALLOT
	void FillCommQueue(DWORD dwMilliseconds);
	BOOL ReadLine(int y, BYTE& head);
	BOOL ReadLinePortion(int y, int& pos);
	BOOL Eval(char val);
	BOOL Write(BYTE output);
	BOOL Read(BYTE& inp);
	
	CByteList m_CommQueue;
	HANDLE m_hComm;
#endif
	
	BOOL m_sheet[48][63];
	BOOL m_HopperEmpty;
	BYTE m_codes[32];  // used to translate the dot pattern to a code 
};

#endif // !defined(AFX_SCANNERINTERFACE_H__69254A20_F337_11D5_B47E_00B0D0CDB4FC__INCLUDED_)