#include "CppUTest/TestHarness.h"
#include "kozos_unit_testBuildTime.h"

TEST_GROUP(kozos_unit_testBuildTime)
{
  kozos_unit_testBuildTime* projectBuildTime;

  void setup()
  {
    projectBuildTime = new kozos_unit_testBuildTime();
  }
  void teardown()
  {
    delete projectBuildTime;
  }
};

TEST(kozos_unit_testBuildTime, Create)
{
  CHECK(0 != projectBuildTime->GetDateTime());
}

