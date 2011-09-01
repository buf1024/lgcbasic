// CRCtextDlg.cpp : implementation file
//
// Copyright © 2000 Richard A. Ellingson
// http://www.createwindow.com
// mailto:relling@hughes.net

#include "stdafx.h"
#include "CRCtext.h"
#include "CRCtextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCRCtextDlg dialog

CCRCtextDlg::CCRCtextDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCRCtextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCRCtextDlg)
	m_csURL = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCRCtextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCRCtextDlg)
	DDX_Control(pDX, IDC_CRCTEXT, m_ctlCRC);
	DDX_Control(pDX, IDC_TEXT, m_ctlTextEdit);
	DDX_Text(pDX, IDC_URL, m_csURL);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCRCtextDlg, CDialog)
	//{{AFX_MSG_MAP(CCRCtextDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_EN_CHANGE(IDC_TEXT, OnChangeText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCRCtextDlg message handlers

BOOL CCRCtextDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);

			// ******* Begin custom code *******

			// We have a Minimize box on the dialog, but we don't want
			// the Size and Maximize options on the system menu so disable them.
			pSysMenu->EnableMenuItem(SC_SIZE, MF_GRAYED);
			pSysMenu->EnableMenuItem(SC_MAXIMIZE, MF_GRAYED);

			// ******* End custom code *******
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

// ******* Begin custom code *******

	// Don't forget to create the lookup table first
	Init_CRC32_Table();

	// Limit the maximum text for the edit box,
	// just so we don't crash if the user tries
	// to dump too much in there.
	m_ctlTextEdit.SetLimitText(50000);
	// Display a warning about NULL characters.
	m_ctlTextEdit.SetWindowText("NULL characters pasted here cause false CRC values");
	// Send the Create Window URL to the dialog
	m_csURL = "http://www.createwindow.com";
	UpdateData(FALSE);

// ******* End custom code *******
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCRCtextDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCRCtextDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCRCtextDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
// Everything above this line is AppWizard generated code
// except for a few lines in OnInitDialog()

// ******* Begin custom code *******

// Handler for Close program messages
void CCRCtextDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	// I like to override this function so the dialog
	// doesn't close when the Escape key is pressed.
	if(GetKeyState(VK_ESCAPE) & 128)
		return;

	CDialog::OnCancel();
}

// Handler for the Reset button
void CCRCtextDlg::OnReset() 
{
	// TODO: Add your control notification handler code here

	// Reset the CRC value
	m_ctlCRC.SetWindowText("0");
	// Empty the edit box
	m_ctlTextEdit.SetWindowText("");
	// Set focus to the Edit box
	m_ctlTextEdit.SetFocus();
	
}

// Handler for when the user changes the text in the edit box.
void CCRCtextDlg::OnChangeText() 
{// Called by Windows when text changes
	
	// TODO: Add your control notification handler code here

	CString csText;
	int nCRC;
	char chCRC[8];

	// Get the text from the edit box.
	// Note that we can't handle NULL characters that the user might
	// paste into the Edit box because the text string terminates
	// at the first NULL character.
	m_ctlTextEdit.GetWindowText(csText);
	// Pass the text string to Get_CRC().
	// The return value is a CRC integer.
	nCRC = Get_CRC(csText);
	// Convert the integer to an ASCII character string.
	itoa(nCRC, chCRC, 16); // Note that the CRC number is in hex
	// Set the CRC string in the sunken static box on the dialog.
	m_ctlCRC.SetWindowText(chCRC);
	
}

// Call this function only once to initialize the CRC table.
void CCRCtextDlg::Init_CRC32_Table()
{// Called by OnInitDialog()

	// This is the official polynomial used by CRC-32 
	// in PKZip, WinZip and Ethernet. 
	ULONG ulPolynomial = 0x04c11db7;

	// 256 values representing ASCII character codes.
	for(int i = 0; i <= 0xFF; i++)
	{
		crc32_table[i]=Reflect(i, 8) << 24;
		for (int j = 0; j < 8; j++)
			crc32_table[i] = (crc32_table[i] << 1) ^ (crc32_table[i] & (1 << 31) ? ulPolynomial : 0);
		crc32_table[i] = Reflect(crc32_table[i], 32);
	}
}

// Reflection is a requirement for the official CRC-32 standard.
// You can create CRCs without it, but they won't conform to the standard.
ULONG CCRCtextDlg::Reflect(ULONG ref, char ch)
{// Used only by Init_CRC32_Table()

	ULONG value(0);

	// Swap bit 0 for bit 7
	// bit 1 for bit 6, etc.
	for(int i = 1; i < (ch + 1); i++)
	{
		if(ref & 1)
			value |= 1 << (ch - i);
		ref >>= 1;
	}
	return value;
}

// Once the lookup table has been filled in by the two functions above,
// this function creates all CRCs using only the lookup table.
int CCRCtextDlg::Get_CRC(CString &text)
{// Called by OnChangeText()

	// Be sure to use unsigned variables,
	// because negative values introduce high bits
	// where zero bits are required.

	// Start out with all bits set high.
	ULONG  ulCRC(0xffffffff);
	int len;
	unsigned char* buffer;

	// Get the length.
	// Note that if the text contains NULL characters
	// processing ends at the first NULL and the CRC value is invalid.
	// See the 32 Bit File Demonstration source code
	// for a method of dealing with NULL characters in files.
	len = text.GetLength();
	// Save the text in the buffer.
	buffer = (unsigned char*)(LPCTSTR)text;
	// Perform the algorithm on each character
	// in the string, using the lookup table values.
	while(len--)
		ulCRC = (ulCRC >> 8) ^ crc32_table[(ulCRC & 0xFF) ^ *buffer++];
	// Exclusive OR the result with the beginning value.
	return ulCRC ^ 0xffffffff;
}
// ******* End custom code *******