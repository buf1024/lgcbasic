
// UnitTestView.cpp : CUnitTestView ���ʵ��
//

#include "stdafx.h"
#include "UnitTest.h"

#include "UnitTestDoc.h"
#include "UnitTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUnitTestView

IMPLEMENT_DYNCREATE(CUnitTestView, CView)

BEGIN_MESSAGE_MAP(CUnitTestView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CUnitTestView ����/����

CUnitTestView::CUnitTestView()
{
	// TODO: �ڴ˴���ӹ������

}

CUnitTestView::~CUnitTestView()
{
}

BOOL CUnitTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CUnitTestView ����

void CUnitTestView::OnDraw(CDC* /*pDC*/)
{
	CUnitTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CUnitTestView ��ӡ

BOOL CUnitTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CUnitTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CUnitTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CUnitTestView ���

#ifdef _DEBUG
void CUnitTestView::AssertValid() const
{
	CView::AssertValid();
}

void CUnitTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUnitTestDoc* CUnitTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUnitTestDoc)));
	return (CUnitTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CUnitTestView ��Ϣ�������
