cmake_minimum_required(VERSION 3.25)
project(PackageTest CXX)

find_package(emsh CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example emsh::emsh)
