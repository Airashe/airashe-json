cmake_minimum_required(VERSION 3.29)
project(airashe-json-tests LANGUAGES CXX)

# setup variables
set(AIRASHEJSON_TEST_PROJECT_NAME "airashe-json-tests")

# find dependencies
find_package(GTest REQUIRED)
if(NOT TARGET airashe-json)
    find_package(airashe-json REQUIRED)
endif()

# setup tests target
add_executable(${AIRASHEJSON_TEST_PROJECT_NAME}
    parsing.cc
)

# link dependencies
target_link_libraries(${AIRASHEJSON_TEST_PROJECT_NAME}
    GTest::gtest_main
    airashe::json
)

include(GoogleTest)
message("Discovering tests")
gtest_discover_tests(${AIRASHEJSON_TEST_PROJECT_NAME})