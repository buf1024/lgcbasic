// CRCtextDlg.h : header file
//
// Copyright © 2000 Richard A. Ellingson
// http://www.createwindow.com
// mailto:relling@hughes.net

#if !defined(AFX_CRCTEXTDLG_H__7525C326_CAA5_11D3_96B1_00A0CC52C86A__INCLUDED_)
#define AFX_CRCTEXTDLG_H__7525C326_CAA5_11D3_96B1_00A0CC52C86A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCRCtextDlg dialog

class CCRCtextDlg : public CDialog
{
// Construction
public:
	CCRCtextDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCRCtextDlg)
	enum { IDD = IDD_CRCTEXT_DIALOG };
	CStatic	m_ctlCRC;
	CEdit	m_ctlTextEdit;
	CString	m_csURL;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCRCtextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
// ******* Begin custom code *******

	ULONG crc32_table[256]; // Lookup table array
	void Init_CRC32_Table(); // Builds Lookup table array
	ULONG Reflect(ULONG ref, char ch); // Reflects CRC bits in the lookup table
	int Get_CRC(CString& text); // Creates a CRC from a string buffer

// ******* End custom code *******
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCRCtextDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnReset();
	afx_msg void OnChangeText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRCTEXTDLG_H__7525C326_CAA5_11D3_96B1_00A0CC52C86A__INCLUDED_)
