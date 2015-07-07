// TestTimer2.h : main header file for the TESTTIMER2 application
//

#if !defined(AFX_TESTTIMER2_H__362BF893_BD1B_4D52_B72B_929786554991__INCLUDED_)
#define AFX_TESTTIMER2_H__362BF893_BD1B_4D52_B72B_929786554991__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestTimer2App:
// See TestTimer2.cpp for the implementation of this class
//

class CTestTimer2App : public CWinApp
{
public:
	CTestTimer2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTimer2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestTimer2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTIMER2_H__362BF893_BD1B_4D52_B72B_929786554991__INCLUDED_)
