#include "kozos_unit_testBuildTime.h"

kozos_unit_testBuildTime::kozos_unit_testBuildTime()
: dateTime(__DATE__ " " __TIME__)
{
}

kozos_unit_testBuildTime::~kozos_unit_testBuildTime()
{
}

const char* kozos_unit_testBuildTime::GetDateTime()
{
    return dateTime;
}

