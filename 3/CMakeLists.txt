cmake_minimum_required(VERSION 3.16)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb3")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_compile_options(-fPIC)
add_link_options(-fPIC)

add_library (lib2 src/include/matrix.hpp src/include/matrix.cpp)

link_libraries(lib2)

add_library (lib1 src/include/classes.hpp src/skill.cpp src/school.cpp src/table_of_schools.cpp src/initiative_creatures.cpp src/summoner.cpp src/squad.cpp src/landscape.cpp  src/Graphics_UI.cpp src/AI.cpp src/heritance_lib.cpp)

link_libraries(lib1)

find_package(Boost 1.45.0 COMPONENTS filesystem)

add_library(dynamic_lib SHARED src/include/dynamic_library/my_plugin.cpp)

set_target_properties(dynamic_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(dynamic_lib  ${Boost_LIBRARIES})

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

add_subdirectory(raylib)

add_executable(lab3 src/include/main.cpp game.cpp)

set_target_properties(lab3 PROPERTIES ENABLE_EXPORTS ON)

target_link_libraries(lab3 ${Boost_LIBRARIES}  raylib)
