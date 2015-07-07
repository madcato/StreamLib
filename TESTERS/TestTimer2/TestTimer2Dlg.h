// TestTimer2Dlg.h : header file
//

#if !defined(AFX_TESTTIMER2DLG_H__6B5E7794_1BBF_4542_8AAA_8D32A22140C0__INCLUDED_)
#define AFX_TESTTIMER2DLG_H__6B5E7794_1BBF_4542_8AAA_8D32A22140C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestTimer2Dlg dialog

class CTestTimer2Dlg : public CDialog
{
// Construction
public:
	CTestTimer2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestTimer2Dlg)
	enum { IDD = IDD_TESTTIMER2_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTimer2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestTimer2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTIMER2DLG_H__6B5E7794_1BBF_4542_8AAA_8D32A22140C0__INCLUDED_)
