cmake_minimum_required(VERSION 3.25)

project(emsh CXX)

option(BUILD_TESTS OFF)

add_library(emsh)
target_sources(
    emsh PRIVATE
        "${CMAKE_SOURCE_DIR}/src/console/console.cpp"
        "${CMAKE_SOURCE_DIR}/src/console/escape_sequences.cpp"
        "${CMAKE_SOURCE_DIR}/src/console/input.cpp"
        "${CMAKE_SOURCE_DIR}/src/console/prompt.cpp"
        "${CMAKE_SOURCE_DIR}/src/console/termios_wrappers.cpp"
)
target_sources(
    emsh PUBLIC
        FILE_SET HEADERS BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
        FILES
            "include/emsh/console/console.h"
            "include/emsh/console/escape_sequences.h"
            "include/emsh/console/input.h"
            "include/emsh/console/prompt.h"
            "include/emsh/console/termios_wrappers.h"
            "include/emsh/emsh.h"
)

install(TARGETS emsh FILE_SET HEADERS)

if (BUILD_TESTS)
    add_subdirectory("${CMAKE_SOURCE_DIR}/unit_tests")
endif()
