extern "C"
{
#include "lib.h"  
}
#include "CppUTest/TestHarness.h"

TEST_GROUP(lib)
{
	void setup()
	{
	}
	void teardown()
	{
	}
};

TEST(lib, k_strlen)
{
	char str[] = "Hello";

	LONGS_EQUAL(5, k_strlen(str));
}

