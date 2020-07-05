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

TEST(lib, strlen)
{ 
  char str[5];
  LONGS_EQUAL(5, strlen(str));
}

