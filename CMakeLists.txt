cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 20)

project(foxgame CXX)

add_executable(foxgame src/main.cpp src/board.cpp src/bag.cpp)
