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


#if !defined(AFX_SCANRACE_H__40AD8267_56C4_11D6_B47E_00B0D0CDB4FC__INCLUDED_)
#define AFX_SCANRACE_H__40AD8267_56C4_11D6_B47E_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Student.h"
class CElectSoftDoc;
class CPrintRace;

class CScanRace
{
public:
	CScanRace(CPrintRace* pPRace); //ClassYear year, int position, CElectSoftDoc* pDoc);
	BOOL GetCand(BYTE code, CString& candidate) { return m_candidates.Lookup(code, candidate); }
	int GetMaxVotes() { return m_MaxVotes; }
	void GetLocation(UINT& col, UINT& row0, int& length) { col=m_col; row0=m_row0; length=m_length; }
	BOOL IsEligible(CStudent* pStudent);
	CString GetName() { return m_name; }
	ClassYear GetYear() { return m_year; }
private:
	ClassYear m_year;
	Affiliation m_aff;
	UINT m_col, m_row0;
	int m_length;
	int m_MaxVotes;
	CString m_name;
	CMap<BYTE, BYTE, CString, CString> m_candidates;
};

#endif // !defined(AFX_SCANRACE_H__40AD8267_56C4_11D6_B47E_00B0D0CDB4FC__INCLUDED_)