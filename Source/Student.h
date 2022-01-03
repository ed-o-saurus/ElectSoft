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


#if !defined(AFX_STUDENT_H__5AB7EAE1_4623_11D5_B355_FFFFFF000000__INCLUDED_)
#define AFX_STUDENT_H__5AB7EAE1_4623_11D5_B355_FFFFFF000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStudent
{
public:
	BOOL IsYear(ClassYear year) { return((year==AL)||(year==m_year1)||(year==m_year2)); }
	CStudent(CString string, BOOL& eligible, BOOL& valid);
	Affiliation GetAff() { return m_aff; }
	CString GetName() { return m_name; }
	CString GetRIN() { return m_RIN; }
	CString YearString();
private:
	BOOL ReadYearCode(CString code, ClassYear& year);
	ClassYear m_year1, m_year2;  // class year(s) of the student 
	Affiliation m_aff; // Affiliation of the student (Greek or Independent)
	CString m_name;    // Student's name 
	CString m_RIN;     // Rensselaer identification number
};

#endif // !defined(AFX_STUDENT_H__5AB7EAE1_4623_11D5_B355_FFFFFF000000__INCLUDED_)