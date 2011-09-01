
// UnitTest.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "UnitTest.h"
#include "MainFrm.h"

#include "UnitTestDoc.h"
#include "UnitTestView.h"

#include <cppunit.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUnitTestApp

BEGIN_MESSAGE_MAP(CUnitTestApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CUnitTestApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// CUnitTestApp ����

CUnitTestApp::CUnitTestApp()
{

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CUnitTestApp ����

CUnitTestApp theApp;


// CUnitTestApp ��ʼ��

BOOL CUnitTestApp::InitInstance()
{
	CWinApp::InitInstance();
	RunUnitTest();
	return FALSE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CUnitTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CUnitTestApp ��Ϣ�������



void CUnitTestApp::RunUnitTest()
{
	CppUnit::MfcUi::TestRunner runner;
	CppUnit::TestFactoryRegistry& reg = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(reg.makeTest());
	runner.run();
}

