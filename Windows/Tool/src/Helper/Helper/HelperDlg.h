
// HelperDlg.h : 头文件
//

#pragma once

#include "IniConfig.h"

#define CONFIG_FILE         _T("Helper.ini")
#define CONFIG_SECTION      _T("Helper")
#define CONFIG_KEY_TITLE    _T("Title")
#define CONFIG_KEY_PATH     _T("Path")
#define CONFIG_KEY_FILTER   _T("Filter")

// CHelperDlg 对话框
class CHelperDlg : public CDialog
{
// 构造
public:
	CHelperDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HELPER_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

    void InitTree();

    void InitTreeNode(HTREEITEM hParent, Std_String strPath, std::list<Std_String>& lstFilter);

    INT64 GetFolderSize(LPCTSTR szFolder);

    Std_String GetCurPath();

    bool CreateExampleConf(bool bCN);


    // 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

    afx_msg void OnNMDblclkTreeDoc(NMHDR *pNMHDR, LRESULT *pResult);
protected:
    CStatic m_cltPic;
    CTreeCtrl m_ctlDoc;

    std::map<DWORD, Std_String> m_pathMap;

    DWORD m_dwKey;

};
