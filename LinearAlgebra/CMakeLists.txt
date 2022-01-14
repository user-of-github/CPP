cmake_minimum_required(VERSION 3.19)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 20)

add_executable(LinearAlgebra main.cpp Library/Matrix/Vector/vector.cpp Library/Matrix/Vector/vector.h Tester/test_vector.cpp Tester/test_vector.h Library/Utils/utils.cpp Library/Utils/utils.h Library/Matrix/matrix.cpp Library/Matrix/matrix.h Tester/test_matrix.cpp Tester/test_matrix.h)