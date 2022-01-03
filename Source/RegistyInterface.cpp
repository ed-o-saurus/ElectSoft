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
#include "RegistyInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

void CRegistyInterface::SetUpFileTypes()
{
	//configures the data types used by ElectSoft
	
	TCHAR szLongPathName[_MAX_PATH], szShortPathName[_MAX_PATH];
	CString ShortPathName, TypeName, TxtCommand;
	
	GetModuleFileName(AfxGetInstanceHandle(), szLongPathName, _MAX_PATH); // get the path to the program 
	GetShortPathName(szLongPathName, szShortPathName, _MAX_PATH);
	ShortPathName=szShortPathName;
	
	DefaultRegSet(".stu", "ElectSoftStudentFile"); // configure Student File (.stu) type 
	DefaultRegSet("ElectSoftStudentFile", "ElectSoft Student File");
	RegSetEditFlags("ElectSoftStudentFile");
	DefaultRegSet("ElectSoftStudentFile\\DefaultIcon", ShortPathName+",1");
	
	DefaultRegSet(".els", "ElectSoftFile"); // configure ElectSoftFile (.els) type 
	DefaultRegSet("ElectSoftFile", "ElectSoft File");
	RegSetEditFlags("ElectSoftFile");
	DefaultRegSet("ElectSoftFile\\shell\\open\\command", ShortPathName+" \"%1\"");
	DefaultRegSet("ElectSoftFile\\DefaultIcon", ShortPathName+",2");
	
	DefaultRegSet(".cou", "ElectSoftCountFile"); // configure Count File (.cou) type 
	DefaultRegSet("ElectSoftCountFile", "ElectSoft Count File");
	RegSetEditFlags("ElectSoftCountFile");
	DefaultRegSet("ElectSoftCountFile\\DefaultIcon", ShortPathName+",3");
	
	DefaultRegSet(".rac", "ElectSoftRaceFile"); // configure Race File (.rac) type 
	DefaultRegSet("ElectSoftRaceFile", "ElectSoft Race File");
	RegSetEditFlags("ElectSoftRaceFile");
	DefaultRegSet("ElectSoftRaceFile\\DefaultIcon", ShortPathName+",4");
	
	TypeName=DefaultRegGet(".txt");
	if(TypeName.IsEmpty())
		return;
	
	TxtCommand=DefaultRegGet(TypeName+"\\shell\\open\\command");
	if(TxtCommand.IsEmpty())
		return;
	
	DefaultRegSet("ElectSoftStudentFile\\shell\\open\\command", TxtCommand); // open these file types with a text editor
	DefaultRegSet("ElectSoftRaceFile\\shell\\open\\command", TxtCommand);	
}

void CRegistyInterface::DefaultRegSet(CString SubKey, CString Data)
{
	//Sets the default item in the SubKey
	HKEY hKey;
	DWORD Disposition;
	
	RegCreateKeyEx(HKEY_CLASSES_ROOT, SubKey, 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &Disposition);
	RegSetValueEx(hKey, NULL, 0, REG_EXPAND_SZ, (LPBYTE)Data.GetBuffer(0), Data.GetLength()+1);
	RegCloseKey(hKey);
}

void CRegistyInterface::RegSetEditFlags(CString SubKey)
{
	//set the EditFlags item to 0x00 0x00 0x00 0x00 in SubKey
	
	HKEY hKey;
	DWORD Disposition;
	BYTE EditFlags[]={0x00, 0x00, 0x00, 0x00};
	
	RegCreateKeyEx(HKEY_CLASSES_ROOT, SubKey, 0, "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &Disposition);
	RegSetValueEx(hKey, "EditFlags", 0, REG_BINARY, EditFlags, 4);
	RegCloseKey(hKey);
}

CString CRegistyInterface::DefaultRegGet(CString SubKey)
{
	//Gets the default item in the SubKey
	
	HKEY hKey;
	DWORD Type;
	unsigned char Data[_MAX_PATH];
	DWORD size=_MAX_PATH;
	
	RegOpenKeyEx(HKEY_CLASSES_ROOT, SubKey, 0, KEY_ALL_ACCESS, &hKey);
	RegQueryValueEx(hKey, NULL, 0, &Type, Data, &size);
	RegCloseKey(hKey);
	
	return size?CString(Data):"";
}