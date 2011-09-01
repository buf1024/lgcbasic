// CRCtext.h : main header file for the CRCTEXT application
//
// Copyright © 2000 Richard A. Ellingson
// http://www.createwindow.com
// mailto:relling@hughes.net

#if !defined(AFX_CRCTEXT_H__7525C324_CAA5_11D3_96B1_00A0CC52C86A__INCLUDED_)
#define AFX_CRCTEXT_H__7525C324_CAA5_11D3_96B1_00A0CC52C86A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCRCtextApp:
// See CRCtext.cpp for the implementation of this class
//

class CCRCtextApp : public CWinApp
{
public:
	CCRCtextApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCRCtextApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCRCtextApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRCTEXT_H__7525C324_CAA5_11D3_96B1_00A0CC52C86A__INCLUDED_)
