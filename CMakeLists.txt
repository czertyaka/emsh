cmake_minimum_required(VERSION 3.25)

project(emsh CXX)

add_library(emsh)
target_sources(
    emsh PRIVATE
        "${CMAKE_SOURCE_DIR}/src/console/termios_raw_mode.cpp"
        "${CMAKE_SOURCE_DIR}/src/console/prompt.cpp"
)
target_sources(
    emsh PUBLIC
        FILE_SET HEADERS BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
        FILES
            "include/emsh.h"
            "include/console/termios_raw_mode.h"
            "include/console/prompt.h"
)

install(
    TARGETS
        emsh
    FILE_SET HEADERS
        DESTINATION "include/emsh"
)
