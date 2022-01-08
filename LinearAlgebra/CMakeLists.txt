cmake_minimum_required(VERSION 3.19)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 20)

add_executable(LinearAlgebra main.cpp Matrix/Vector/Vector.cpp Matrix/Vector/Vector.h test.h)