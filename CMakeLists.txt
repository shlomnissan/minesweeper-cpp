cmake_minimum_required(VERSION 3.15)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(minesweeper main.cpp board.cpp board.hpp level.hpp cell.hpp)