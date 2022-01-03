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


#include "stdafx.h"
#include "ElectSoft.h"
#include "CommSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

CCommSettings::CCommSettings(CWnd* pParent) : CDialog(CCommSettings::IDD, pParent)
{
	m_name="com1";
	m_RIT=20; m_RTTM=10; m_RTTC=100; m_WTTM=10; m_WTTC=100;
}

void CCommSettings::DoDataExchange(CDataExchange* pDX)
{
	int baud=2;
	
	CDialog::DoDataExchange(pDX);
	
	DDX_CBString(pDX, IDC_PORT, m_name);
	DDX_Radio(pDX, IDC_B_38400, baud);
	
	DDX_Text(pDX, IDC_RIT,  m_RIT);
	DDX_Text(pDX, IDC_RTTM, m_RTTM);
	DDX_Text(pDX, IDC_RTTC, m_RTTC);
	DDX_Text(pDX, IDC_WTTM, m_WTTM);
	DDX_Text(pDX, IDC_WTTC, m_WTTC);
	
	if(!pDX->m_bSaveAndValidate)
		return;
	
	switch(baud)
	{
	case 0: m_BaudRate=CBR_38400; break;
	case 1: m_BaudRate=CBR_19200; break;
	case 2: m_BaudRate=CBR_9600; break;
	case 3: m_BaudRate=CBR_4800; break;
	case 4: m_BaudRate=CBR_2400; break;
	case 5: m_BaudRate=CBR_1200; break;
	}
}

BOOL CCommSettings::OnInitDialog() 
{
	CComboBox* pComboBox=(CComboBox*)GetDlgItem(IDC_PORT);
	
	pComboBox->AddString("com1"); pComboBox->AddString("com2");
	pComboBox->AddString("com3"); pComboBox->AddString("com4");
	
	return CDialog::OnInitDialog();
}