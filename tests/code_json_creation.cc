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
	const char* str = array[0];
	ASSERT_STREQ(str, "value1");

	array[1] = "test2";
	str = array[1];
	ASSERT_STREQ(str, "test2");

	jtoken empty_array = jarray();
	array[0] = "test3";
	str = array[0];
	ASSERT_STREQ(str, "test3");

	str = array;
	ASSERT_STREQ(str, "[\"test3\", \"test2\"]");

	str = empty_array;
	ASSERT_STREQ(str, "[]");

	str = array;
	std::string str2 = array.to_string();
	ASSERT_STREQ(str, str2.c_str());
}

void test_json_object()
{
	jtoken obj = jobject({
		{"key1", "value1"},
		});

	const char* test = obj;

	obj["key1"] = "value2";
	const char* test2 = obj;
	ASSERT_STREQ(test, "{\"key1\": \"value1\"}");
	ASSERT_STREQ(test2, "{\"key1\": \"value2\"}");

	test = obj.c_str();
	std::string test3 = obj;

	ASSERT_STREQ(test, test3.c_str());

	jtoken empty_obj = jobject();
	test = empty_obj;
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

TEST(ValuesConvertion, ToNumbers)
{
	jtoken str_val = "5";
	long long int val = str_val;
	ASSERT_EQ(val, 5);

	jtoken str_overflow = "18446744073709551615";
	val = str_overflow;
	ASSERT_EQ(val, 0);

	unsigned long long int val2 = str_overflow;
	ASSERT_EQ(val2, 18446744073709551615);

	jtoken float_val = "5.5";
	float val3 = float_val;
	ASSERT_EQ(val3, 5.5);
}

TEST(ValueConvertion, ToStrings)
{
	jtoken token = "test";
	const char* val = token;
	ASSERT_STREQ(val, "test");

	std::string val2 = token;
	ASSERT_STREQ(val2.c_str(), "test");

	token = 5.5f;
	std::string val3 = token;
	ASSERT_STREQ(val3.c_str(), "5.5");

	double t_double = 5.21;
	token = t_double;
	val3 = token.to_string();
	ASSERT_STREQ(val3.c_str(), "5.21");

	long double t_ld = 5.23;
	token = t_ld;
	val3 = token.to_string();
	ASSERT_STREQ(val3.c_str(), "5.23");

	token = "5.25";
	val3 = token.to_string();
	ASSERT_STREQ(val3.c_str(), "5.25");
	ASSERT_EQ(token.to_ld(), 5.25);

	token = 5;
}