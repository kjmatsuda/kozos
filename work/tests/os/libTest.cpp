#include "CppUTest/TestHarness.h"

extern "C"
{
#include "lib.h"
}

TEST_GROUP(lib)
{
	void setup()
	{
	}
	void teardown()
	{
	}
};

TEST(lib, k_kz_strlen)
{
	char str[] = "Hello";

	LONGS_EQUAL(5, kz_strlen(str));
}
