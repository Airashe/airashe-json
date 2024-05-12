#include "gtest/gtest.h"
#include "structs/jproperty.hpp"
#include "structs/jtoken.hpp"
using namespace airashe::json;

void test_json_string()
{
    jtoken str = "test_string";
    ASSERT_STREQ(str.c_str(), "test_string");
}

void test_json_array()
{
    jtoken array = jarray({"value1", "value2"});
    ASSERT_STREQ(array[0].c_str(), "value1");
    
    array[1] = "test2";
    ASSERT_STREQ(array[1].c_str(), "test2");

    jtoken empty_array = jarray();
    array[0] = "test3";
    ASSERT_STREQ(array[0].c_str(), "test3");
}

void test_json_object()
{
    jtoken obj = jobject({
        {"key1", "val1"},
        {"key2", "val2"}
    });

    ASSERT_STREQ(obj["key1"].c_str(), "val1");

    jtoken empty_obj = jobject();
    obj["key3"] = "val3";
    ASSERT_STREQ(obj["key3"].c_str(), "val3");
}

TEST(JSON, CreateString)
{
    try
    {
        test_json_string();
    }
    catch (std::exception&)
    {
        FAIL();
    }
}

TEST(JSON, CreateArray)
{
    try
    {
        test_json_array();
    }
    catch (std::exception&)
    {
        FAIL();
    }
}

TEST(JSON, CreateObject)
{
    try
    {
        test_json_object();
    }
    catch (std::exception&)
    {
        FAIL();
    }
}
