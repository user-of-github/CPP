#include <gtest/gtest.h>
#include "../Library/Matrix/matrix.hpp"
#include "../Library/Matrix/matrix.cpp"


TEST(Matrix, Size)
{
    LinearAlgebra::Matrix<double> test(4, 5, 1);
    const auto[rows, cols] = test.Sizes();
    EXPECT_EQ(rows, 4);
    EXPECT_EQ(cols, 5);
    EXPECT_EQ(test.Sum(), 20);
    EXPECT_NO_THROW(test.Resize(10, 20, 0));
    EXPECT_EQ(test.Sum(), 20);
    EXPECT_EQ(std::get<0>(test.Sizes()), 10);
    EXPECT_EQ(std::get<1>(test.Sizes()), 20);
}

TEST(Matrix, Sum)
{
    const auto initial = new const int *[2]{new int[3]{6, 5, 7}, new int[3]{1, 2, 3}};
    EXPECT_EQ(LinearAlgebra::Matrix<int>((initial), 2, 3).Sum(), 24);

    EXPECT_EQ(LinearAlgebra::Matrix<int>(LinearAlgebra::Vector<int>(5, 6)).Sum(),
              LinearAlgebra::Vector<int>(5, 6).Sum());

    LinearAlgebra::Vector<int> vector1 = {1, 2, 3, 4};
    EXPECT_EQ(vector1.Sum(), 10);
    LinearAlgebra::Matrix<typeof(vector1[0])> matrix1(vector1);
    EXPECT_EQ(matrix1.Sum(), 10);
}