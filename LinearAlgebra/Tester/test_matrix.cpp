#include <gtest/gtest.h>
#include "../Library/Matrix/matrix.hpp"
#include "../Library/Matrix/matrix.cpp"


TEST(Matrix, Size)
{
    auto test = LinearAlgebra::Matrix<double>(4, 5, 1);
    const auto[rows, cols] = test.Sizes();
    EXPECT_EQ(rows, 4);
    EXPECT_EQ(cols, 5);
    EXPECT_NO_THROW(test.Resize(10, 20, 0));
    EXPECT_EQ(std::get<0>(test.Sizes()), 10);
    EXPECT_EQ(std::get<1>(test.Sizes()), 20);

    const int initial2[4][4] = {{1, 0, 0, 0},
                                {0, 1, 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}};
    auto tester = LinearAlgebra::Matrix<int>((int *) (initial2), 4, 4);
    EXPECT_THROW(std::cout << tester[4][2] << '\n', std::runtime_error);

    EXPECT_ANY_THROW(tester.Resize(0, 1));

    EXPECT_NO_THROW(tester.Resize(5, 5));

    EXPECT_TRUE(tester[0][0] == 1 && tester[4][4] == 0 && tester[2][2] == 1);
}

TEST(Matrix, Sum)
{
    const auto initial = new const int *[2]{new int[3]{6, 5, 7}, new int[3]{1, 2, 3}};
    EXPECT_EQ(LinearAlgebra::Matrix<int>((initial), 2, 3).Sum(), 24);

    EXPECT_EQ(LinearAlgebra::Matrix<int>(LinearAlgebra::Vector<int>(5, 6)).Sum(),
              LinearAlgebra::Vector<int>(5, 6).Sum());

    LinearAlgebra::Vector<int> vector1 = {1, 2, 3, 4};
    EXPECT_EQ(vector1.Sum(), 10);
    auto matrix1 = LinearAlgebra::Matrix<typeof(vector1[0])>(vector1);
    EXPECT_EQ(matrix1.Sum(), 10);

    const int initial2[4][4] = {{1, 0, 0, 0},
                                {0, 1, 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}};
    auto tester = LinearAlgebra::Matrix<int>((int *) (initial2), 4, 4);
    EXPECT_EQ(tester.Sum(), 4);
    EXPECT_NO_THROW(tester.Resize(5, 5));
    EXPECT_TRUE(tester[0][0] == 1 && tester[4][4] == 0 && tester[2][2] == 1);
    EXPECT_EQ(tester.Sum(), 4);
    EXPECT_NO_THROW(tester.Resize(6, 6, 1));
    EXPECT_EQ(tester.Sum(), 4 + 11);
}

TEST(Matrix, Operators)
{
    EXPECT_TRUE(LinearAlgebra::Matrix<int>(4, 4, 1) == LinearAlgebra::Matrix<int>(4, 4, 1));
    const int initial1[4][4] = {{1,  2,  3,  4},
                                {5,  6,  7,  8},
                                {10, 11, 12, 13},
                                {14, 15, 16, 17}};

    const int initial2[4][4] = {{-1,  -2,  -3,   -4},
                                {5,   6,   7,    8},
                                {10,  11,  12,   13},
                                {114, 115, 1161, 1171}};

    auto tester1 = LinearAlgebra::Matrix<int>((int *) (initial1), 4, 4);
    auto tester2 = LinearAlgebra::Matrix<int>((int *) (initial2), 4, 4);

    EXPECT_FALSE(tester1 == tester2);
    auto sum1 = tester1.Sum();
    EXPECT_NO_THROW(tester1 *= 5);
    EXPECT_EQ(sum1 * 5, tester1.Sum());
    auto sum2 = tester2.Sum();
    EXPECT_NO_THROW(tester2.Resize(5, 5, 1));
    EXPECT_EQ(sum2 + 9, tester2.Sum());
    EXPECT_THROW(tester2 /= 0, std::runtime_error);
    tester2.Resize(4, 4);
    tester1.Resize(4, 4);

    LinearAlgebra::Matrix<int> testerSum = tester1 + tester2;
    EXPECT_NE(testerSum.Sum(), tester1.Sum());
    EXPECT_NO_THROW(LinearAlgebra::Matrix<int>(tester1 + tester2).Sum());
    EXPECT_EQ(testerSum.Sum(), tester1.Sum() + tester2.Sum());
    EXPECT_EQ((tester1 - tester2).Sum(), tester1.Sum() - tester2.Sum());
    EXPECT_EQ((tester2 - tester2).Sum(), 0);
}

TEST(Matrix, Transpose)
{
    const int initial[4][4] = {{1,  2,  3,  4},
                               {5,  6,  7,  8},
                               {9,  10, 11, 12},
                               {13, 14, 15, 16}};

    const int initial_transposed[4][4] = {{1, 5, 9,  13},
                                          {2, 6, 10, 14},
                                          {3, 7, 11, 15},
                                          {4, 8, 12, 16}};
    auto tester = LinearAlgebra::Matrix<int>((int *) initial, 4, 4);
    auto tester_transposed = LinearAlgebra::Matrix<int>((int *) initial_transposed, 4, 4);
    EXPECT_NO_THROW(tester.Transpose());
    EXPECT_TRUE(tester == tester_transposed);
    EXPECT_NO_THROW(tester_transposed.Transpose());
    EXPECT_TRUE(tester_transposed == LinearAlgebra::Matrix<int>((int *) initial, 4, 4));

    auto tester0 = LinearAlgebra::Matrix<unsigned short>(4, 4, 2022);
    EXPECT_NO_THROW(tester0.Transpose());
    EXPECT_TRUE(tester0 == LinearAlgebra::Matrix<unsigned short>(4, 4, 2022));
}