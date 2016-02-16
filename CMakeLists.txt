cmake_minimum_required(VERSION 3.3)
project(magic_square)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -std=c++14")

set(SOURCE_FILES main.cpp main.h magic_square.cpp magic_square.h)
add_executable(magic_square ${SOURCE_FILES})