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


#if !defined(AFX_TIMESOCKET_H__4B49E241_985E_11D7_8464_00B0D0CDB4FC__INCLUDED_)
#define AFX_TIMESOCKET_H__4B49E241_985E_11D7_8464_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CElectSoftView;

class CTimeSocket : public CSocket
{
// This class serves as a way of setting the system clock based on the 
// National Institute of Standards and Technology's atomic clock.  
// It requests the correct time from a SNTP (simple network time protocol) 
// server and sets the system clock accrdingly.  
// For more information consult the NIST website at http://www.nist.gov/

public:
	CTimeSocket() { Create(0, SOCK_DGRAM); m_MessageBox=false; }
	void TrasRequest(BOOL MessageBox);  // Sends a request for the correct time to the server  
	virtual void OnReceive(int nErrorCode); // executed when a time is receved  
	CElectSoftView* m_pView;

private:
	BOOL m_MessageBox;  // true : A message box is displayed when the clock is set. 
};

#endif // !defined(AFX_TIMESOCKET_H__4B49E241_985E_11D7_8464_00B0D0CDB4FC__INCLUDED_)