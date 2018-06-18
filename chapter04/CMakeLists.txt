cmake_minimum_required(VERSION 3.10)
project(chapter04)

set(CMAKE_CXX_STANDARD 11)

add_executable(chapter04 main.cpp GridWorld.cpp GridWorld.h gambler.cpp gambler.h)