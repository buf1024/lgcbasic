
// UnitTestDoc.cpp : CUnitTestDoc ���ʵ��
//

#include "stdafx.h"
#include "UnitTest.h"

#include "UnitTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUnitTestDoc

IMPLEMENT_DYNCREATE(CUnitTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CUnitTestDoc, CDocument)
END_MESSAGE_MAP()


// CUnitTestDoc ����/����

CUnitTestDoc::CUnitTestDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CUnitTestDoc::~CUnitTestDoc()
{
}

BOOL CUnitTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CUnitTestDoc ���л�

void CUnitTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CUnitTestDoc ���

#ifdef _DEBUG
void CUnitTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUnitTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CUnitTestDoc ����
