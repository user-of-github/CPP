#ifndef LINEARALGEBRA_TEST_H
#define LINEARALGEBRA_TEST_H

#include "Matrix/Vector/Vector.h"
#include "Matrix/Vector/Vector.cpp"
#include "cassert"

void TestNorm();

void test()
{
    TestNorm();
}

void TestNorm()
{
    assert(LinearAlgebra::Vector<double>({1, 2, 3, 4}).GetNorm() == 5);
}

#endif //LINEARALGEBRA_TEST_H
