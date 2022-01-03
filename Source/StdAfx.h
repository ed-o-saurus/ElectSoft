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


// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__69E56026_562F_11D6_B47E_00B0D0CDB4FC__INCLUDED_)
#define AFX_STDAFX_H__69E56026_562F_11D6_B47E_00B0D0CDB4FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#include <afxtempl.h>
#include <afxsock.h>
#include <math.h>
#include <winspool.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#define GET_APP ((CElectSoftApp*)AfxGetApp())

typedef enum {AL, FR, SO, JR, SR, GR} ClassYear;
typedef enum {BOTH, GREEK, INDEPENDENT} Affiliation;
typedef enum {PRINTED, OUTSTANDING, COUNTED, VOIDED, REPORTED_LOST_DESTROYED} BallotStatus;
typedef CList<BYTE, BYTE> CByteList;

#include "ScanBallot.h"
#include "ScanRace.h"

typedef CArray<CScanBallot*, CScanBallot*> CScanBallotArray;
typedef CArray<CScanRace*, CScanRace*> CScanRaceArray;

UINT AFXAPI HashKey(CString key);
CArchive& operator>>(CArchive& ar, ClassYear& year);
CArchive& operator>>(CArchive& ar, Affiliation& aff);

#endif // !defined(AFX_STDAFX_H__69E56026_562F_11D6_B47E_00B0D0CDB4FC__INCLUDED_)