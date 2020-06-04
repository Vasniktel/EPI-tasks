cmake_minimum_required(VERSION 3.16)
project(cracking_the_coding_interview)

set(CMAKE_CXX_STANDARD 17)

set(TARGETS unique_characters)

add_executable(unique_characters 1_1_unique_characters.cpp)

add_subdirectory(external)
