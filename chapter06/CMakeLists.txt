cmake_minimum_required(VERSION 3.10)
project(chapter06)

set(CMAKE_CXX_STANDARD 11)

add_executable(chapter06 main.cpp random_walk.cpp random_walk.h grid_world.h grid_world.cpp cliff_walk.h cliff_walk.cpp
        windy_grid.h windy_grid.cpp)