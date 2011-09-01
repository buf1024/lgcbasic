#pragma once
#include <cppunit.h>
#include "hash.h"
#include "HashSHA1Impl.h"

class SHA1Test
	: public TestFixture
{
	CPPUNIT_TEST_SUITE(SHA1Test);
	CPPUNIT_TEST(testString);
	CPPUNIT_TEST(testFile);
	CPPUNIT_TEST_SUITE_END();
public:
	SHA1Test(void);
	~SHA1Test(void);
public:
	void setUp();
	void tearDown();

public:
	void testString();
	void testFile();
private:
	Hash *pHash;
};
