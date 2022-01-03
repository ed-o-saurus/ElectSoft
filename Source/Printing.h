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


#if !defined(AFX_PRINTING_H__1E7E96E0_84A2_11D7_9809_00B0D0CDB4FC__INCLUDED_)
#define AFX_PRINTING_H__1E7E96E0_84A2_11D7_9809_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPrinting
{
public:
	static UINT MainRoutine(LPVOID pParam);  //The thread's main routine 
private:
	static void PrintStack();  //Print the ballots 
	static void AlignPrinter(UINT& AlignmentCountdown);  //Print an alignment form
	static void PrintBallot(int& size, UINT& AlignmentCountdown); //Print a ballot
	static BOOL QueueEmpty(BOOL& AutoReg); //Is the pring queue empty 
	static void Step(BOOL& AutoReg, UINT& AlignmentCountdown, int& size);
};

#endif // !defined(AFX_PRINTING_H__1E7E96E0_84A2_11D7_9809_00B0D0CDB4FC__INCLUDED_)
