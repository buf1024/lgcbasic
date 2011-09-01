#include "StdAfx.h"
#include "RegTest.h"

#include "Reg.h"
#include <strsafe.h>

RegTest::RegTest(void)
{
}

RegTest::~RegTest(void)
{
}

void RegTest::setUp()
{

}
void RegTest::tearDown()
{

}

void RegTest::testFactory()
{
	RegFactory* pFactory = RegFactory::GetInstPtr();
	RegNode* pNode = pFactory->CreateRegNode(HKEY_CURRENT_USER, _T("Software\\LGCBasic"), true);
	CPPUNIT_ASSERT(pNode->IsValid() == true);
	RegData* pData = new RegData;
	pData->SetDataType(REG_DWORD);
	TCHAR szBuf[] = _T("AAAAAAAAAAAAAAAAA");
	pData->SetKeyName(szBuf);
	DWORD val = 153L;
	pData->SetData(&val, sizeof(val));
	pNode->AddRegData(pData);

	pData = new RegData;
	pData->SetValue(REG_DWORD, _T(""), &val, sizeof(val));
	pNode->AddRegData(pData);

	CPPUNIT_ASSERT(pNode != NULL);

	pNode->DeleteNode(_T(""));

	CPPUNIT_ASSERT(pNode->IsValid() == false);

	delete pNode;

    RegFactory::ReleaseRC();
}

CPPUNIT_TEST_SUITE_REGISTRATION(RegTest);