cmake_minimum_required(VERSION 3.25)
project(lab1_oop)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(lab1 func.cpp func.h)

link_libraries(lab1)

add_executable(lab1_oop main.cpp)
