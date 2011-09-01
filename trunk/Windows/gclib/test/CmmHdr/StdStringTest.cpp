#include "stdafx.h"
#include "StdStringTest.h"
#include "StdString.h"

StdStringTest::StdStringTest()
{

}
StdStringTest::~StdStringTest()
{

}

void StdStringTest::setup()
{

}
void StdStringTest::tearDown()
{

}

void StdStringTest::testStdString()
{
    //GetAnsiString
    std::string strAnsi = GetAnsiString(L"hello");
    CPPUNIT_ASSERT(strAnsi == "hello");
    strAnsi = GetAnsiString(L"");
    CPPUNIT_ASSERT(strAnsi == "");

    //GetWideString
    std::wstring strWide = GetWideString("hello");
    CPPUNIT_ASSERT(strWide == L"hello");
    strWide = GetWideString(L"");
    CPPUNIT_ASSERT(strWide == L"");

    //GetCStyleAnsiString
    char szBuf[64] = {0};
    const char* pTmp = GetCStyleAnsiString("hello", szBuf);
    CPPUNIT_ASSERT_EQUAL(0, lstrcmpA(pTmp, "hello"));
    pTmp = GetCStyleAnsiString("", szBuf);
    CPPUNIT_ASSERT_EQUAL(0, lstrlenA(pTmp));

    //GetCStyleWideString
    wchar_t szBuf2[64] = {0};
    const wchar_t* pTmp2 = GetCStyleWideString(L"hello", szBuf2);
    CPPUNIT_ASSERT_EQUAL(0, lstrcmpW(pTmp2, L"hello"));
    pTmp2 = GetCStyleWideString(L"", szBuf2);
    CPPUNIT_ASSERT_EQUAL(0, lstrlenW(pTmp2));

    //Split
    std::string strDel = " \t";
    strAnsi = " a\t hello                         world         ";
    std::list<std::string> rgpRet;
    int nVal = Split(strAnsi, strDel, rgpRet);
    CPPUNIT_ASSERT(3 == nVal);
    CPPUNIT_ASSERT(3u == rgpRet.size());

    std::list<std::string>::iterator iter = rgpRet.begin();
    CPPUNIT_ASSERT(*iter == "a");
    iter++;
    CPPUNIT_ASSERT(*iter == "hello");
    iter++;
    CPPUNIT_ASSERT(*iter == "world");
    
    //Trim
    strAnsi = "     \t a evil world                     \t               ";
    strAnsi = TrimLeft(strAnsi, strDel);
    CPPUNIT_ASSERT(strAnsi == "a evil world                     \t               ");
    strAnsi = "     \t a evil world                     \t               ";
    strAnsi = TrimRight(strAnsi, strDel);
    CPPUNIT_ASSERT(strAnsi == "     \t a evil world");
    strAnsi = "     \t a evil world                     \t               ";
    strAnsi = Trim(strAnsi, strDel);
    CPPUNIT_ASSERT(strAnsi == "a evil world");

    //StartsWith
    strAnsi = "this is a world";
    strDel = "this";
    CPPUNIT_ASSERT(StartsWith(strAnsi, strDel));
    strDel = "his";
    CPPUNIT_ASSERT(!StartsWith(strAnsi, strDel));

    //EndsWith
    strDel = "world";
    CPPUNIT_ASSERT(EndsWith(strAnsi, strDel));
    strDel = "his";
    CPPUNIT_ASSERT(!EndsWith(strAnsi, strDel));

    //Contains
    strDel = "is";
    CPPUNIT_ASSERT(Contains(strAnsi, strDel));
    strDel = "his name";
    CPPUNIT_ASSERT(!Contains(strAnsi, strDel));

}
CPPUNIT_TEST_SUITE_REGISTRATION(StdStringTest);
