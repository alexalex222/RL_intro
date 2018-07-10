cmake_minimum_required(VERSION 3.10)
project(chapter01)

set(CMAKE_CXX_STANDARD 11)

add_executable(chapter01 main.cpp gridstatus.cpp judger.h judger.cpp player.cpp player.h human_player.cpp human_player.h ai_player.cpp ai_player.h)