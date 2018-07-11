cmake_minimum_required(VERSION 3.10)
project(chapter02)

set(CMAKE_CXX_STANDARD 11)

add_executable(chapter02 main.cpp bandit.cpp bandit.h simulation.h)