cmake_minimum_required(VERSION 3.16)
project(test_lab2)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(lib1 src/dynamic_class.cpp src/simple_class.cpp src/include/simple_class.h src/include/dynamic_class.h)

link_libraries(lib1)

add_executable(test_lab2 Dialogue/main_2.cpp)

find_package(Catch2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fprofile-arcs -ftest-coverage")

add_executable(test tests/catch2.cpp)

target_link_libraries(test PRIVATE Catch2::Catch2WithMain)
