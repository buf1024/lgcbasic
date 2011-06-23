#pragma once
#include <cppunit.h>

class StdStringTest : public TestFixture
{
    CPPUNIT_TEST_SUITE(StdStringTest);
    CPPUNIT_TEST(testStdString);
    CPPUNIT_TEST_SUITE_END();
public:
    StdStringTest();
    ~StdStringTest();
public:
    virtual void setup();
    virtual void tearDown();

public:
    void testStdString();

};