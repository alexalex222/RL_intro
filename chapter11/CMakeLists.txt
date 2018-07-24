cmake_minimum_required(VERSION 3.10)
project(chapter11)

set(CMAKE_CXX_STANDARD 17)
set(EIGEN_INCLUDE_DIR /Users/kuilinchen/Repositories/eigen)
include_directories(${EIGEN_INCLUDE_DIR})


add_executable(chapter11 main.cpp baird.h baird.cpp)