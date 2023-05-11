cmake_minimum_required(VERSION 3.24)
project(hw_09)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(hw_09
        genome_hash.cpp
        genome_hash.h
        main.cpp)
