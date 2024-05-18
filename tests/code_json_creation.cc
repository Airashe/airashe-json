#include "gtest/gtest.h"
#include "structs/jproperty.hpp"
#include "structs/jtoken.hpp"
using namespace airashe::json;

void test_json_string()
{
	jtoken str = "test_string";
	const char* str_val = str.c_str();
	ASSERT_STREQ(str_val, "test_string");
}

void test_json_array()
{
	jtoken array = jarray({ "value1", "value2" });
	const char* str = array[0].c_str();
	ASSERT_STREQ(str, "value1");

	array[1] = "test2";
	str = array[1].c_str();
	ASSERT_STREQ(str, "test2");

	jtoken empty_array = jarray();
	array[0] = "test3";
	str = array[0].c_str();
	ASSERT_STREQ(str, "test3");

	str = array.c_str();
	ASSERT_STREQ(str, "[\"test3\", \"test2\"]");

	str = empty_array.c_str();
	ASSERT_STREQ(str, "[]");

	str = array.c_str();
	std::string str2 = array.to_string();
	ASSERT_STREQ(str, str2.c_str());
}

void test_json_object()
{
	jtoken obj = jobject({
		{"key1", "value1"},
		});

	const char* test = obj.c_str();

	obj["key1"] = "value2";
	const char* test2 = obj.c_str();
	ASSERT_STREQ(test, "{\"key1\": \"value1\"}");
	ASSERT_STREQ(test2, "{\"key1\": \"value2\"}");

	test = obj.c_str();
	std::string test3 = obj;

	ASSERT_STREQ(test, test3.c_str());

	jtoken empty_obj = jobject();
	test = empty_obj.c_str();
	ASSERT_STREQ(test, "{}");
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
