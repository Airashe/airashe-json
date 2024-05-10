#include "gtest/gtest.h"
#include "structs/jtoken.hpp"

void test_json_string()
{
    airashe::json::jtoken token = "test_string";
}

TEST(JSONString, BasicTest)
{
    test_json_string();
}