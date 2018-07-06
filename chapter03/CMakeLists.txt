cmake_minimum_required(VERSION 3.10)
project(chapter03)

set(CMAKE_CXX_STANDARD 11)

#Python
set(PYTHON_LIBRARY /Users/kuilinchen/anaconda3/lib/libpython3.6m.dylib)
set(PYTHON_INCLUDE_DIR /Users/kuilinchen/anaconda3/include/python3.6m)
set(PYTHON_EXECUTABLE /Users/kuilinchen/anaconda3/bin/python)
find_package(PythonInterp)
if(PythonInterp_FOUND)
    message(STATUS "PYTHON_DIRS: ${PYTHON_EXECUTABLE}")
endif()
find_package(PythonLibs REQUIRED)
if(PythonLibs_FOUND)
    message(STATUS "PYTHON_INCLUDE_DIRS: ${PYTHON_INCLUDE_DIRS}")
    message(STATUS "PYTHON_LIBRARIES: ${PYTHON_LIBRARIES}")
    message(STATUS "PYTHON_VERSION: ${PYTHON_VERSION}")

    include_directories(${PYTHON_INCLUDE_DIRS})

endif()

add_executable(chapter03 main.cpp gridworld.cpp gridworld.h)
target_link_libraries(chapter03 ${PYTHON_LIBRARIES})