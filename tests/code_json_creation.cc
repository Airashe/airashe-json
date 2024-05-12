#include "gtest/gtest.h"
#include "structs/jtoken.hpp"

void test_json_string()
{
    airashe::json::jtoken str = "test_string";
}

void test_json_array()
{
    airashe::json::jtoken array = airashe::json::jarray("value1", "value2");
    ASSERT_STREQ(array[0].c_str(), "value1");
    
    array[1] = "test2";
    ASSERT_STREQ(array[1].c_str(), "test2");

    airashe::json::jtoken empty_array = airashe::json::jarray();
    array[0] = "test3";
    ASSERT_STREQ(array[0].c_str(), "test3");
}

void test_json_object()
{
    /*airashe::json::jtoken obj = airashe::json::jobject({
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"}
    });*/
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
        test_json_array();
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
