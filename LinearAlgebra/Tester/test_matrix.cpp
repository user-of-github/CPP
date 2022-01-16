#include <gtest/gtest.h>
#include "../Library/Matrix/matrix.hpp"
#include "../Library/Matrix/matrix.cpp"


TEST(Matrix, Size)
{
    LinearAlgebra::Matrix<double> test(4, 5);
    const auto [rows, cols] = test.Sizes();
    EXPECT_EQ(rows, 4);
    EXPECT_EQ(cols, 5);
    EXPECT_EQ(test.Sum(), 0);
}