#pragma once

#include <cppunit.h>

class RegTest : public TestFixture
{
	CPPUNIT_TEST_SUITE(RegTest);
		CPPUNIT_TEST(testFactory);
	CPPUNIT_TEST_SUITE_END();
public:
	RegTest(void);
	~RegTest(void);
public:
	virtual void setUp();
	virtual void tearDown();

public:
	void testFactory();
};
