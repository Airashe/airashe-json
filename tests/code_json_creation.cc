#include "jparser.hpp"
#include "gtest/gtest.h"
#include "structs/jproperty.hpp"
#include "structs/jtoken.hpp"
#include "iostream"
using namespace airashe::json;

void test_json_string()
{
	jtoken str = "test_string";
	const char* str_val = str.c_str();
	ASSERT_STREQ(str_val, "test_string");
}

void test_json_l()
{
	jtoken token = 5;
	const char* str = token;
	
	str = token = -5;
	str = token = 5.5;
	str = token = 5.5f;
	str = token = "5.5";

	str = token = true;
	str = token = false;

	str = token = nullptr;
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

	empty_obj["bool_key"] = true;
	empty_obj["double_key"] = 5.5;
	empty_obj["int_key"] = 5;
	empty_obj["null_key"] = nullptr;
	empty_obj["str_key"] = "str";
	
	ASSERT_STREQ(empty_obj.c_str(), R"({"bool_key": true, "double_key": 5.5, "int_key": 5, "null_key": null, "str_key": "str"})");
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
	catch (std::exception& e)
	{
		FAIL();
	}
}

TEST(JSON, CheckLeak)
{
	try
	{
		test_json_l();
	}
	catch (std::exception&)
	{
		FAIL();
	}
}

TEST(ValueConvertion, ToNumbers)
{
	jtoken str_val = "5";
	long long int val = str_val;
	long long int val_e = 5;
	ASSERT_EQ(val, 5);

	unsigned long long int val2_e = 18446744073709551615ull;
	val_e = static_cast<long long int>(val2_e);
	jtoken str_overflow = "18446744073709551615";
	val = str_overflow;
	ASSERT_EQ(val, val_e);

	unsigned long long int val2 = str_overflow;
	ASSERT_EQ(val2, val2_e);

	jtoken float_val = "5.5";
	float val3 = float_val;
	float val3_e = 5.5;
	ASSERT_EQ(val3, val3_e);

	str_overflow = -1l;
	unsigned long t2 = str_overflow;
	unsigned long t3 = -1l;
	ASSERT_EQ(t2, t3);
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
	
	token = 5l;
	val3 = token.to_string();
	ASSERT_STREQ(val3.c_str(), "5");

	std::string val4 = "hello world";
	token = val4;
	ASSERT_STREQ(token.c_str(), val4.c_str());
}

TEST(ValueConvertion, StringToNumbers)
{
	jtoken token = "-5";
	unsigned long long int val = token;
	unsigned long long int val_e = -5;
	ASSERT_EQ(val, val_e);

	long long int val2 = token;
	long long int val2_e = -5;
	ASSERT_EQ(val2, val2_e);

	token = "5.5";
	float val3 = token;
	float val3_e = 5.5;
	ASSERT_EQ(val3, val3_e);

	int val4 = token;
	int val4_e = 5;
	ASSERT_EQ(val4, val4_e);

	token = "5";
	double val5 = token;
	double val5_e = 5.0;
	ASSERT_EQ(val5, val5_e);

	token = "0xFF";
	unsigned char val6 = token;
	unsigned char val6_e = 0xFF;
	ASSERT_EQ(val6, val6_e);

	token = "9";
	char val7 = token;
	char val7_e = '9';
	ASSERT_EQ(val7, val7_e);
}

TEST(ValueConvertion, Booleans)
{
	jtoken test = true;
	bool test_v = test;
	bool test_e = true;
	ASSERT_EQ(test_v, test_e);
	
	if (!test)
		FAIL();
	if ((bool)test == false)
		FAIL();

	test = false;
	test_v = test;
	test_e = false;
	ASSERT_EQ(test_v, test_e);
	if (test)
		FAIL();
	if ((bool)test == true)
		FAIL();

	std::string test_e2 = "false";
	ASSERT_STREQ(test.c_str(), test_e2.c_str());
	
	test = "true";
	test_v = test;
	test_e = true;
	ASSERT_EQ(test_v, test_e);

	if (!test)
		FAIL();
	if ((bool)test == false)
		FAIL();
	
	test = "false";
	test_v = test;
	test_e = false;
	ASSERT_EQ(test_v, test_e);
	if (test)
		FAIL();
	if ((bool)test == true)
		FAIL();

	test = "1";
	test_v = test;
	test_e = true;
	ASSERT_EQ(test_v, test_e);

	if (!test)
		FAIL();
	if ((bool)test == false)
		FAIL();

	test = "0";
	test_v = test;
	test_e = false;
	ASSERT_EQ(test_v, test_e);
	if (test)
		FAIL();
	if ((bool)test == true)
		FAIL();
	
	test = 0;
	test_v = test;
	test_e = false;
	ASSERT_EQ(test_v, test_e);
	if (test)
		FAIL();
	if ((bool)test == true)
		FAIL();

	test = 1;
	test_v = test;
	test_e = true;
	ASSERT_EQ(test_v, test_e);
	if (!test)
		FAIL();
	if ((bool)test == false)
		FAIL();
}

TEST(ValueConvertion, Nulls)
{
	jtoken test = nullptr;
	ASSERT_EQ(test.get_type(), jtoken_null);

	test = airashe::json::jnull();
	ASSERT_EQ(test.get_type(), jtoken_null);
}

TEST(PARSER, Parse)
{	
	jtoken test = json(R"([
	 {
		"id": "12345", 
		"balance": 1000.00
	}
]
)");
	
	if (test.get_type() == jtoken_err)
	{
		FAIL() << test.c_str();
	}
	else
	{
		std::cout << "[ VALUE    ] " << test[0]["id"].c_str() << '\n';
	}
	const char* test_val = test.c_str();
}