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


#if !defined(AFX_SCANNING_H__1E7E96E1_84A2_11D7_9809_00B0D0CDB4FC__INCLUDED_)
#define AFX_SCANNING_H__1E7E96E1_84A2_11D7_9809_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CScanning
{
public:
	static UINT MainRoutine(LPVOID pParam);
private:
	static BOOL GetBallotInfo(CScannerInterface* pSI, ClassYear& year, int& number);
	static void CheckStudent(CScanBallot* pSBallot, CCount* pCount);
	static BOOL StatusCleared(BallotStatus status);
	static void ScanBallot(CScannerInterface* pSI, BOOL voiding);
	static void ScanStack();
	static void ProcessBallot(CScannerInterface* pSI, BOOL voiding, CPrintBallot* pPBallot, CScanBallot* pSBallot);
};

#endif // !defined(AFX_SCANNING_H__1E7E96E1_84A2_11D7_9809_00B0D0CDB4FC__INCLUDED_)