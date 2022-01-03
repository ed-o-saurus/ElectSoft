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
#include "TimeSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIME_DIFF 2208988800  //number of seconds from 00:00 1/1/1900 to 00:00 1/1/1970

void CTimeSocket::OnReceive(int nErrorCode) 
{
	SYSTEMTIME SystemTime;
	BYTE data[48];
	struct tm* ptm;
	
	Receive(data, 48); // read the input into data 
	
	// calculate the SystemTime structure
	time_t tt=((data[40]<<24)|(data[41]<<16)|(data[42]<<8)|data[43])-TIME_DIFF;
	ptm=gmtime(&tt);
	
	SystemTime.wYear=  ptm->tm_year+1900;
	SystemTime.wMonth= ptm->tm_mon+1;
	SystemTime.wDay=   ptm->tm_mday;
	SystemTime.wHour=  ptm->tm_hour;
	SystemTime.wMinute=ptm->tm_min;
	SystemTime.wSecond=ptm->tm_sec;
	SystemTime.wMilliseconds=0;
	
	if(SetSystemTime(&SystemTime)) // Set the system time
	{
		if(m_MessageBox)  // If a message box is wanted 
			m_pView->MessageBox(CTime::GetCurrentTime().Format("Time Set To\n%c"), NULL, MB_ICONINFORMATION);
		
		m_MessageBox=false;
	}
	else
		m_pView->MessageBox("Unable to set time", NULL, MB_ICONERROR);
	
	CSocket::OnReceive(nErrorCode);
}

void CTimeSocket::TrasRequest(BOOL MessageBox)
{
	time_t tt;
	m_MessageBox=MessageBox;
	
	CString server=GET_APP->GetProfileString("Time", "Server", "time-a.nist.gov"); // Server name
	
    time(&tt);
	DWORD SC=tt+TIME_DIFF;
	
	// This is the data block to send 
	BYTE data[]={
		0xcb,	0x00,	0x00,	0x00,
		0x00,	0x00,	0x00,	0x00,
		0x00,	0x00,	0x00,	0x00,
		0x00,	0x00,	0x00,	0x00,
		0xcc,	0xcc,	0xcc,	0xcc,
		0xcc,	0xcc,	0xcc,	0xcc,
		0x00,	0x00,	0x00,	0x00,
		0x00,	0x00,	0x00,	0x00,
		0x00,	0x00,	0x00,	0x00,
		0x00,	0x00,	0x00,	0x00,
		0xcc,	0xcc,	0xcc,	0xcc,
		0x00,	0x00,	0x00,	0x00};
	
	data[24]=HIBYTE(HIWORD(SC));
	data[25]=LOBYTE(HIWORD(SC));
	data[26]=HIBYTE(LOWORD(SC));
	data[27]=LOBYTE(LOWORD(SC));
	
	SendTo(data, 48, 123, server);
}