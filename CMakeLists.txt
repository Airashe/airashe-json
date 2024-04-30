cmake_minimum_required(VERSION 3.15)
project(airashe-json CXX)

set(AIRASHEJSON_PROJECT_NAME "airashe-json")

add_library(${AIRASHEJSON_PROJECT_NAME} 
    src/json_parser.cpp
)

target_include_directories(${AIRASHEJSON_PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>/src
    $<INSTALL_INTERFACE:include>
)

set_target_properties(${AIRASHEJSON_PROJECT_NAME} PROPERTIES PUBLIC_HEADER "src/json_parser.hpp")
# instalation
install(TARGETS ${AIRASHEJSON_PROJECT_NAME})

#install headers
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*"
)