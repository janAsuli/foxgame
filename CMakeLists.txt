cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)

project(foxgame CXX)

add_executable(foxgame)
target_sources(foxgame
  PUBLIC
    src/main.cpp)
target_sources(foxgame
  PUBLIC
    FILE_SET all_my_modules TYPE CXX_MODULES FILES
    src/bag.cpp
    src/board.cpp
    src/tile.cpp)
