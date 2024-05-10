#include "gtest/gtest.h"
#include "structs/jtoken.hpp"

void test_json_string()
{
    airashe::json::jtoken str = "test_string";
}

void test_json_array()
{
    airashe::json::jtoken array = {
        "first",
        "second",
        "third"
    };
    
    array[0] = "test2";
    airashe::json::jtoken first = array[0];
}

void test_json_object()
{

}

TEST(JSONString, BasicTest)
{
    try
    {
        test_json_string();
    }
    catch (std::exception& e)
    {
        FAIL();
    }
}

TEST(JSONArray, BasicTest)
{
    try
    {
        while (true)
        {
            test_json_array();
        }
    }
    catch (std::exception& e)
    {
        FAIL();
    }
}

TEST(JSONObject, BasicTest)
{
    try
    {
		test_json_object();
    }
    catch (std::exception& e)
    {
		FAIL();
    }
}