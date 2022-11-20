cmake_minimum_required(VERSION 3.22)
project(crypto)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(crypto main.cpp)
