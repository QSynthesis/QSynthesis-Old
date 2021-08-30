cmake_minimum_required(VERSION 3.17)
project(libvsqx)

set(CMAKE_CXX_STANDARD 11)

add_executable(test test1.cpp vsqx.h libvsqx.cpp)