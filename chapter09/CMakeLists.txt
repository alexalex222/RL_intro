cmake_minimum_required(VERSION 3.10)
project(chapter09)

set(CMAKE_CXX_STANDARD 11)

add_executable(chapter09 main.cpp random_walk.h random_walk.cpp value_function.cpp value_function.h tilings_value_function.cpp tilings_value_function.h basis_value_function.cpp basis_value_function.h aggreg_value_function.cpp aggreg_value_function.h learning_methods.h)