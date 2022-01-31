cmake_minimum_required(VERSION 3.19)
project(linear_algebra_library)
set(CMAKE_CXX_STANDARD 20)
add_library(linear_algebra ./Utils/utils.cpp ./Matrix/Vector/vector.cpp ./Matrix/matrix.cpp ./EquationSystemSolver/equation_system_solver.cpp)