cmake_minimum_required(VERSION "3.13.4")
add_compile_options(-Wall -lstdc++fs)

find_package(Threads REQUIRED)

add_subdirectory(GUI)

