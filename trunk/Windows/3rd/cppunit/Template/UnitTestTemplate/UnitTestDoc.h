
// UnitTestDoc.h : CUnitTestDoc ��Ľӿ�
//


#pragma once


class CUnitTestDoc : public CDocument
{
protected: // �������л�����
	CUnitTestDoc();
	DECLARE_DYNCREATE(CUnitTestDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CUnitTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

