cmake_minimum_required(VERSION 3.15)
project(airashe-json CXX)

# include
include(GNUInstallDirs)

# setup variables
set(AIRASHEJSON_PROJECT_NAME "airashe-json")
set(AIRASHEJSON_TARGET_NAME ${AIRASHEJSON_PROJECT_NAME}Targets)
set(AIRASHEJSON_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${AIRASHEJSON_PROJECT_NAME})

# create target
add_library(${AIRASHEJSON_PROJECT_NAME} 
    src/json_parser.cpp
)

# set public api
set_target_properties(${AIRASHEJSON_PROJECT_NAME} PROPERTIES PUBLIC_HEADER 
    "src/json_parser.hpp"
)

# set include directories
target_include_directories(${AIRASHEJSON_PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/src
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>/src
    $<INSTALL_INTERFACE:${AIRASHEJSON_INCLUDE_DIR}>
)

# instalation of binaries
install(TARGETS ${AIRASHEJSON_PROJECT_NAME}
        EXPORT ${AIRASHEJSON_TARGET_NAME}
        DESTINATION ${CMAKE_INSTALL_LIBDIR})

#install headers (so other packages can use them from include directory)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
    DESTINATION ${AIRASHEJSON_INCLUDE_DIR}
    FILES_MATCHING PATTERN "*.h*"
)