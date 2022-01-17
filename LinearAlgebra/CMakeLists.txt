cmake_minimum_required(VERSION 3.14)
project(demo_library)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 20)

add_executable(demo sandbox.cpp ./Library/Matrix/Vector/vector.cpp ./Library/Matrix/matrix.cpp)


# to build lib ?
add_library(LinearAlgebraLib ./Library/Matrix/Vector/vector.cpp Library/Matrix/Vector/vector.cpp)