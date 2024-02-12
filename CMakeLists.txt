cmake_minimum_required(VERSION 3.25)

project(emsh CXX)

option(BUILD_TESTS OFF)

add_library(emsh)
target_sources(
    emsh PRIVATE
        "${CMAKE_SOURCE_DIR}/src/console/input.cpp"
        "${CMAKE_SOURCE_DIR}/src/console/prompt.cpp"
        "${CMAKE_SOURCE_DIR}/src/console/termios_raw_mode.cpp"
)
target_sources(
    emsh PUBLIC
        FILE_SET HEADERS BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
        FILES
            "include/console/input.h"
            "include/console/prompt.h"
            "include/console/termios_raw_mode.h"
            "include/emsh.h"
)

install(
    TARGETS
        emsh
    FILE_SET HEADERS
        DESTINATION "include/emsh"
)

if (BUILD_TESTS)
    add_subdirectory("${CMAKE_SOURCE_DIR}/unit_tests")
endif()
