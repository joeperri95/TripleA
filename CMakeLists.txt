cmake_minimum_required(VERSION "3.13.4")

project(TripleA CXX)

add_compile_options(-Wall -Wno-unknown-pragmas)
include_directories(..)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE)


set(JSON_BuildTests OFF CACHE INTERNAL "")
set(BUILD_TESTING OFF "")
enable_testing()


add_subdirectory(external/googletest)
add_subdirectory(external/json)
add_subdirectory(external/SFML-2.5.1)

add_subdirectory(TripleA)
add_subdirectory(test)
