cmake_minimum_required(VERSION 3.24)
project(hw_05)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -g)

add_executable(hw_05 provided_files/main.cpp provided_files/mtrand.cpp provided_files/traincar.cpp)
