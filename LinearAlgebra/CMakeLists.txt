cmake_minimum_required(VERSION 3.14)
project(demo_library)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

add_executable(demo demo.cpp Library/Matrix/Vector/vector.cpp Library/Matrix/Vector/vector.h Library/Utils/utils.cpp Library/Utils/utils.h Library/Matrix/matrix.cpp Library/Matrix/matrix.h)