cmake_minimum_required(VERSION 3.10)
project(chapter08)

set(CMAKE_CXX_STANDARD 11)

add_executable(chapter08 main.cpp grid_world.h grid_world.cpp maze.cpp maze.h dyna_params.h trivial_model.cpp trivial_model.h time_model.cpp time_model.h priority_model.cpp priority_model.h)