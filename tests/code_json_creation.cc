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
	jtoken array = jarray({ "value1", "value2" });
	ASSERT_STREQ(array[0].c_str(), "value1");

	array[1] = "test2";
	ASSERT_STREQ(array[1].c_str(), "test2");

	jtoken empty_array = jarray();
	array[0] = "test3";
	ASSERT_STREQ(array[0].c_str(), "test3");

	ASSERT_STREQ(array.c_str(), "[\"test3\", \"test2\"]");
	ASSERT_STREQ(empty_array.c_str(), "[]");

	ASSERT_STREQ(array.c_str(), array.to_string().c_str());
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

	ASSERT_STREQ(obj.c_str(), obj.to_string().c_str());
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
