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


#if !defined(AFX_COMMSETTINGS_H__F0F64580_3793_11D6_B47E_00B0D0CDB4FC__INCLUDED_)
#define AFX_COMMSETTINGS_H__F0F64580_3793_11D6_B47E_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

class CCommSettings : public CDialog
{
// a dialog box used to configure the serial port 
public:
	CCommSettings(CWnd* pParent=NULL);
	CString m_name;  //port name (i.e. com1, com2, etc.)
	DWORD m_BaudRate;
	DWORD m_RIT, m_RTTM, m_RTTC, m_WTTM, m_WTTC;
	enum { IDD=IDD_COMM };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
};

#endif // !defined(AFX_COMMSETTINGS_H__F0F64580_3793_11D6_B47E_00B0D0CDB4FC__INCLUDED_)