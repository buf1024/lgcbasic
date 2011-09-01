
// HelperDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Helper.h"
#include "HelperDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHelperDlg �Ի���




CHelperDlg::CHelperDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelperDlg::IDD, pParent)
    , m_dwKey(1L)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_PIC, m_cltPic);
	DDX_Control(pDX, IDC_TREE_DOC, m_ctlDoc);
}

BEGIN_MESSAGE_MAP(CHelperDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_NOTIFY(NM_DBLCLK, IDC_TREE_DOC, &CHelperDlg::OnNMDblclkTreeDoc)
END_MESSAGE_MAP()


// CHelperDlg ��Ϣ�������

BOOL CHelperDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_NORMAL);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

    InitTree();
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHelperDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

Std_String CHelperDlg::GetCurPath()
{
    TCHAR szBuf[MAX_PATH] = {0};
    DWORD dwRet = ::GetModuleFileName(AfxGetApp()->m_hInstance, szBuf, MAX_PATH);
    for (int i = dwRet - 1; i >= 0; i--)
    {
        if (szBuf[i] == _T('\\'))
        {
            break;
        }
        szBuf[i] = _T('\0');        
    }
    return szBuf;
}

void CHelperDlg::InitTree()
{
    lgc::Section* pSec = new lgc::Section(CONFIG_SECTION);

    Std_String strCurDir = GetCurPath();

    Std_String strFile = strCurDir;
    if (AfxGetApp()->m_lpCmdLine != NULL && lstrcmp(AfxGetApp()->m_lpCmdLine, _T("")) != 0)
    {
        strFile.append(AfxGetApp()->m_lpCmdLine);
    }
    else
    {
        strFile.append(CONFIG_FILE);
    }   

    if (pSec->Load(strFile))
    {
        Std_String strFilter;
        Std_String strPath;
        Std_String strTitle;

        pSec->GetValue(CONFIG_KEY_FILTER, strFilter, _T("*"));
        pSec->GetValue(CONFIG_KEY_PATH, strPath, GetCurPath());
        pSec->GetValue(CONFIG_KEY_TITLE, strTitle, _T("Helper"));

        if (!strTitle.empty())
        {
            SetWindowText(strTitle.c_str());

            if (!strPath.empty())
            {
                HTREEITEM hti = m_ctlDoc.InsertItem(strPath.c_str());
                m_ctlDoc.SetItemData(hti, 0);
                
                const TCHAR* szPath = strPath.c_str();
                int nPos = strPath.length() - 1;
                if (szPath[nPos] != _T('\\'))
                {
                    strPath.append(_T("\\"));
                }

                const TCHAR* pszFilter = strFilter.c_str();
                int nLen = strFilter.length();
                nPos = 0;
                std::list<Std_String> lstFilter;
                for (int i=0; i<nLen; i++)
                {
                    TCHAR buf[MAX_PATH] = {0};
                    if (pszFilter[i] == _T('|'))
                    {
                        if (i > 0 && nPos < i)
                        {
                            memcpy(buf, pszFilter+nPos, (i-nPos)*sizeof(TCHAR));
                            nPos = i+1;
                            lstFilter.push_back(buf);
                        }

                    }
                    else
                    {
                        if (i == nLen - 1 && nPos != nLen)
                        {
                            memcpy(buf, pszFilter+nPos, (nLen-nPos)*sizeof(TCHAR));
                            lstFilter.push_back(buf);
                        }
                    }
                }

                InitTreeNode(hti, strPath, lstFilter);
                m_ctlDoc.Expand(hti, TVE_EXPAND);
                m_ctlDoc.SortChildren(TVI_ROOT); 
            }            
        }
    }
    else
    {
        CString strMsg;
        UINT acp = GetACP();        
        if (CreateExampleConf(acp == 936))
        {
            if (acp == 936)
            {
                strMsg.Format(_T("�Ҳ��������ļ� %s!\r\n\r\n�Ѿ��� %s Ŀ¼������һ�������ļ����ӣ������ʵ������޸�!"),
                    CONFIG_FILE, strCurDir.c_str());
            }
            else
            {
                strMsg.Format(_T("Configuration file %s not found!\r\n\r\nA new configuration file is generated in %s, please modify it accordingly!"),
                    CONFIG_FILE, strCurDir.c_str());
            } 
        }
        else
        {
            if (acp == 936)
            {
                strMsg.Format(_T("�Ҳ��������ļ� %s!\r\n\r\n�޷���Ŀ¼%s�����������ļ�����!"),
                    CONFIG_FILE, strCurDir.c_str());
            }
            else
            {
                strMsg.Format(_T("Configuration file %s not found!\r\n\r\nCant not create sample configuration file in directory %s!"),
                    CONFIG_FILE, strCurDir.c_str());
            } 
        }
        AfxMessageBox(strMsg);
    }

    delete pSec;
}

bool CHelperDlg::CreateExampleConf(bool bCN)
{   
    Std_String strPath = GetCurPath();
    strPath.append(CONFIG_FILE);
    const TCHAR* szFile = strPath.c_str();
    HANDLE hFie =  CreateFile(szFile, GENERIC_WRITE | GENERIC_READ, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if (hFie == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    CHAR szUsr[MAX_PATH] = {0};
    SHGetSpecialFolderPathA(NULL, szUsr, CSIDL_PERSONAL, FALSE);
    
    std::string strCont;
    strCont.append("[Helper]");
    strCont.append("\r\n");
    if (bCN)
    {
        strCont.append(";��������ʱ��ʾ�ı���");        
    }
    else
    {
        strCont.append(";The Application title");   
    } 
    strCont.append("\r\n");
    strCont.append("Title=Helper qucik accessor");
    strCont.append("\r\n");
    if (bCN)
    {
        strCont.append(";����������·��");
    }
    else
    {
        strCont.append(";The application search path");
    }
    strCont.append("\r\n");
    strCont.append("Path=");
    strCont.append(szUsr);
    strCont.append("\r\n");
    if (bCN)
    {
        strCont.append(";����ͨ���");
    }
    else
    {
        strCont.append(";Search widcard");
    }
    strCont.append("\r\n");
    strCont.append("Filter=*.txt|*.pdf|*.chm|*.jpg");
    strCont.append("\r\n");

    DWORD dwReal = 0L;
    bool bRet = false;
    if (WriteFile(hFie, strCont.c_str(), strCont.length(), &dwReal, NULL))
    {
        bRet = true;
    }
    CloseHandle(hFie);
    return bRet;
}

void CHelperDlg::InitTreeNode(HTREEITEM hParent, Std_String strPath, std::list<Std_String>& lstFilter)
{        
    Std_String strTmpPath = strPath;
    strTmpPath.append(_T("*"));
    HANDLE hFile = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA wfd = {0};
    hFile = FindFirstFile(strTmpPath.c_str(), &wfd);
    if (hFile != INVALID_HANDLE_VALUE)
    {
        do 
        {
            if(wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
            {
                if (lstrcmp(wfd.cFileName, _T(".")) != 0 &&
                    lstrcmp(wfd.cFileName, _T("..")) != 0)
                {
                    Std_String subPath = strPath;
                    subPath.append(wfd.cFileName);
                    subPath.append(_T("\\"));
                    if (GetFolderSize(subPath.c_str()) > 0)
                    {
                        HTREEITEM hti = m_ctlDoc.InsertItem(wfd.cFileName, hParent);
                        m_ctlDoc.SetItemData(hti, 0);
                        InitTreeNode(hti, subPath, lstFilter);
                        if (m_ctlDoc.GetChildItem(hti) == NULL)
                        {
                            m_ctlDoc.DeleteItem(hti);
                        }
                        else
                        {
                            m_ctlDoc.Expand(hti, TVE_EXPAND);
                        }                        
                    }
                }

            }

        } while (FindNextFile(hFile, &wfd));

        FindClose(hFile);
    }
    for(std::list<Std_String>::iterator iter = lstFilter.begin();
        iter != lstFilter.end(); ++iter)
    {
        strTmpPath = strPath;
        strTmpPath.append(*iter);
        hFile = FindFirstFile(strTmpPath.c_str(), &wfd);
        if (hFile != INVALID_HANDLE_VALUE)
        {
            do 
            {
                if(wfd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
                {
                    
                    HTREEITEM hti = m_ctlDoc.InsertItem(wfd.cFileName, hParent);
                    m_ctlDoc.SetItemData(hti, m_dwKey);
                    
                    Std_String subPath = strPath;
                    subPath.append(wfd.cFileName);

                    m_pathMap.insert(std::make_pair(m_dwKey, subPath));
                    m_dwKey++;

                }

            } while (FindNextFile(hFile, &wfd));

            FindClose(hFile);
        }
    }

}


void CHelperDlg::OnNMDblclkTreeDoc(NMHDR *pNMHDR, LRESULT *pResult)
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    *pResult = 0;

    HTREEITEM hti = m_ctlDoc.GetSelectedItem();
    
    if (hti != NULL)
    {
        DWORD itd = (DWORD)m_ctlDoc.GetItemData(hti);
        if (itd != 0)
        {
            Std_String strPath = m_pathMap[itd];
            ::ShellExecute(NULL, _T("open"), strPath.c_str(), NULL, NULL, SW_SHOW);
        }
    }


}


INT64 CHelperDlg::GetFolderSize(LPCTSTR szFolder)
{
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    CString strFolder(szFolder);
    strFolder.Append( _T("\\*") );

    INT64 folderSize = 0;
    hFind = FindFirstFile(strFolder, &FindFileData);
    if (hFind != INVALID_HANDLE_VALUE) 
    {
        _tprintf (_T("First file name is %s\n"), FindFileData.cFileName);
        do 
        {
            _tprintf (_T("Next file name is %s\n"), FindFileData.cFileName);

            if( _tcsicmp(_T("."), FindFileData.cFileName)==0 
                || _tcsicmp(_T(".."), FindFileData.cFileName)==0 )
            {
                continue;
            }
            if( FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
            {
                CString strResult = szFolder;
                LPCTSTR pszResult;
                LPCTSTR pchLast;
                pszResult = strResult;
                pchLast = _tcsdec( pszResult, pszResult+strResult.GetLength() );
                ATLASSERT(pchLast!=NULL);
                if ((*pchLast != _T('\\')) && (*pchLast != _T('/')))
                    strResult += _T('\\');
                strResult += FindFileData.cFileName;

                folderSize += GetFolderSize( strResult );
            }
            else
            {
                ULARGE_INTEGER nFileSize;
                nFileSize.LowPart = FindFileData.nFileSizeLow;
                nFileSize.HighPart = FindFileData.nFileSizeHigh;
                folderSize += nFileSize.QuadPart;
            }

        } while (FindNextFile(hFind, &FindFileData) != 0);
        FindClose(hFind);
    }
    return folderSize;
}