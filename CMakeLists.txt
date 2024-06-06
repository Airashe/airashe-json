cmake_minimum_required(VERSION 3.29)
set (AIRASHEJSON_VERSION 0.5.0)

project(airashe-json LANGUAGES CXX VERSION ${AIRASHEJSON_VERSION})

# include
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# setup variables
set(AIRASHEJSON_PROJECT_NAME "airashe-json")
set(AIRASHEJSON_TARGET_NAME ${AIRASHEJSON_PROJECT_NAME}Targets)
set(AIRASHEJSON_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/${AIRASHEJSON_PROJECT_NAME})
set(AIRASHEJSON_INSTALL_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${AIRASHEJSON_PROJECT_NAME})
set(AIRASHEJSON_CONFIGVERSION_FILE "${AIRASHEJSON_PROJECT_NAME}-config-version.cmake")
set(AIRASHEJSON_CONFIG_FILE "${AIRASHEJSON_PROJECT_NAME}-config.cmake")

# create target
add_library(${AIRASHEJSON_PROJECT_NAME}
    src/behaviours/jbehaviour_factory.hpp
    src/behaviours/jboolean_behaviour.hpp
    src/behaviours/jcontainer_behaviour.hpp
    src/behaviours/jnull_behaviour.hpp
    src/behaviours/jnumber_behaviour.hpp 
    src/behaviours/jstring_behaviour.hpp 
    src/behaviours/jtoken_behaviour.hpp 
    src/structs/jindex.cpp
    src/structs/jindex.hpp
    src/structs/jmodifiers.hpp
    src/structs/jtoken.cpp
    src/structs/jtoken.hpp
    src/structs/jtoken_type.hpp
    src/structs/jtoken_value.hpp
    src/structs/jtoken_value_container.hpp
    
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
set_property(TARGET ${AIRASHEJSON_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_target_properties(${AIRASHEJSON_PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(${AIRASHEJSON_PROJECT_NAME} PROPERTIES EXPORT_NAME json)

add_library(airashe::json ALIAS ${AIRASHEJSON_PROJECT_NAME})

# enable testing
if(NOT BUILD_TESTING STREQUAL OFF)
    message("Tests enabled")
    enable_testing()
    add_subdirectory(tests)
endif()

# add tools to project
if(NOT AIRASHE_INCLUDE_TOOLS STREQUAL OFF)

endif()

# set public api
set_target_properties(${AIRASHEJSON_PROJECT_NAME} PROPERTIES PUBLIC_HEADER "src/structs/jtoken.hpp")

# set include directories
target_include_directories(${AIRASHEJSON_PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Configure CMake find_package() config files.
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${AIRASHEJSON_CONFIG_FILE}.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${AIRASHEJSON_CONFIG_FILE}"
    INSTALL_DESTINATION ${AIRASHEJSON_INSTALL_CMAKE_DIR}
)

write_basic_package_version_file(
    ${AIRASHEJSON_CONFIGVERSION_FILE}
    VERSION ${AIRASHEJSON_VERSION}
    COMPATIBILITY SameMajorVersion
)

# install CMake find_package() config files.
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${AIRASHEJSON_CONFIGVERSION_FILE}
    ${CMAKE_CURRENT_BINARY_DIR}/${AIRASHEJSON_CONFIG_FILE}
    DESTINATION ${AIRASHEJSON_INSTALL_CMAKE_DIR}
)

# install binaries
install(TARGETS ${AIRASHEJSON_PROJECT_NAME} 
        EXPORT ${AIRASHEJSON_TARGET_NAME} 
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT ${AIRASHEJSON_PROJECT_NAME}_Runtime
                NAMELINK_COMPONENT ${AIRASHEJSON_PROJECT_NAME}_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT ${AIRASHEJSON_PROJECT_NAME}_Development
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                COMPONENT ${AIRASHEJSON_PROJECT_NAME}_Runtime
        INCLUDES DESTINATION ${AIRASHEJSON_INCLUDE_DIR}
        PUBLIC_HEADER DESTINATION ${AIRASHEJSON_INCLUDE_DIR}
)

# install CMake targets
install(EXPORT ${AIRASHEJSON_TARGET_NAME}
    DESTINATION ${AIRASHEJSON_INSTALL_CMAKE_DIR}
    NAMESPACE airashe::
    FILE ${AIRASHEJSON_TARGET_NAME}.cmake
    COMPONENT ${AIRASHEJSON_PROJECT_NAME}_Development
)

# install headers (so other packages can use them from include directory)
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
    DESTINATION ${AIRASHEJSON_INCLUDE_DIR}
    FILES_MATCHING PATTERN "*.h*"
)