#include "test_matrix.h"


void TestMatrix()
{
    LinearAlgebra::Matrix<int> tester(5, 5, 0);
    std::cout << tester;
}