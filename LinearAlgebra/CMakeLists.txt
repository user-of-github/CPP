cmake_minimum_required(VERSION 3.19)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 20)

add_executable(LinearAlgebra main.cpp Library/Matrix/Vector/Vector.cc Library/Matrix/Vector/Vector.h Tester/test_vector.cpp Tester/test_vector.h)