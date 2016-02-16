cmake_minimum_required(VERSION 3.3)
project(magic_square)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_FILES main.cpp main.h)
add_executable(magic_square ${SOURCE_FILES})