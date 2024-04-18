cmake_minimum_required(VERSION 3.27)
project(Maze)

set(CMAKE_CXX_STANDARD 17)

add_executable(Maze main.cpp position.cpp mazeUtils.cpp maze.cpp)
