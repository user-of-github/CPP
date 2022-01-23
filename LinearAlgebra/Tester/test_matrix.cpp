#include <gtest/gtest.h>
#include "../Library/Matrix/matrix.hpp"
#include "../Library/Matrix/matrix.cpp"

TEST(Matrix, Constructors)
{
    EXPECT_EQ(LinearAlgebra::Matrix<int>(LinearAlgebra::Vector<int>({1, 2, 3})).Sum(), 6);
    EXPECT_NO_THROW(LinearAlgebra::Matrix<int>(LinearAlgebra::Vector<int>({1, 2, 3})));
    auto tester = LinearAlgebra::Matrix<int>(5, 6, 7);
    EXPECT_NO_THROW(LinearAlgebra::Matrix<int>(tester).Sum());
    EXPECT_ANY_THROW(LinearAlgebra::Matrix<std::string>(5, 6, ""));
}

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
    EXPECT_THROW(std::cout << tester[4][2] << '\n', std::invalid_argument);

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
    EXPECT_THROW(tester2 /= 0, std::invalid_argument);
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
    auto tester = LinearAlgebra::Matrix<int>((const int *) initial, 4, 4);
    auto tester_transposed = LinearAlgebra::Matrix<int>((const int *) initial_transposed, 4, 4);
    EXPECT_NO_THROW(tester.Transpose());
    EXPECT_TRUE(tester == tester_transposed);
    EXPECT_NO_THROW(tester_transposed.Transpose());
    EXPECT_TRUE(tester_transposed == LinearAlgebra::Matrix<int>((const int *) initial, 4, 4));

    auto tester2 = LinearAlgebra::Matrix<unsigned short>(4, 4, 2022);
    EXPECT_NO_THROW(tester2.Transpose());
    EXPECT_TRUE(tester2 == LinearAlgebra::Matrix<unsigned short>(4, 4, 2022));

    auto tester3 = LinearAlgebra::Matrix<int>(5, 6, 2022);
    const auto sum3 = tester3.Sum();
    tester3 /= 2;
    EXPECT_EQ(tester3.Sum(), ((5 * 6 * 2022) / 2));
}

TEST(Matrix, Triangulate)
{
    const int initial1[3][4] = {{6,  5,  4,  3},
                                {6,  3,  0,  -3},
                                {-2, -3, -4, -5}};
    const int initial1_triangulated[3][4] = {{6, 5,  4,  3},
                                             {0, -2, -4, -6},
                                             {0, 0,  0,  0}};
    auto tester1 = LinearAlgebra::Matrix<int>((const int *) initial1, 3, 4);
    EXPECT_NO_THROW(tester1.Triangulate());
    EXPECT_TRUE(tester1 == LinearAlgebra::Matrix<int>((const int *) initial1_triangulated, 3, 4));


    const double initial2[3][3] = {{2, 6,  -1},
                                   {0, 2,  1},
                                   {2, -1, 0}};
    const double initial2_triangulated[3][3] = {{2, 6,  -1},
                                                {0, -7, 1},
                                                {0, 0,  (9.0 / 7.0)}};
    auto tester2 = LinearAlgebra::Matrix<double>((const double *) initial2, 3, 3);
    EXPECT_NO_THROW(tester2.Triangulate());
    EXPECT_TRUE(tester2 == LinearAlgebra::Matrix<double>((const double *) initial2_triangulated, 3, 3));

    const double initial3[3][3] = {{4,   0,   12},
                                   {160, 200, 240},
                                   {35,  40,  1000}};
    const double initial3_triangulated[3][3] = {{160, 200, 240},
                                                {0,   -5,  6},
                                                {0,   0,   943}};
    auto tester3 = LinearAlgebra::Matrix<double>((const double *) initial3, 3, 3);
    EXPECT_NO_THROW(tester3.Triangulate());
    EXPECT_TRUE(tester3 == LinearAlgebra::Matrix<double>((const double *) initial3_triangulated, 3, 3));

    const double initial4[2][2] = {{1, 2},
                                   {3, 4}};
    const double initial4_triangulated[2][2] = {{3, 4},
                                                {0, 2.0 / 3.0}};
    auto tester4 = LinearAlgebra::Matrix<double>((const double *) initial4, 2, 2);
    EXPECT_NO_THROW(tester4.Triangulate());
    EXPECT_TRUE(LinearAlgebra::Matrix<double>((const double *) initial4_triangulated, 2, 2) == tester4);

    const short initial5[2][2] = {{-1, 1},
                                  {-1, 1}};
    const short initial5_triangulated[2][2] = {{-1, 1},
                                               {0,  0}};
    auto tester5 = LinearAlgebra::Matrix<short>((const short *) initial5, 2, 2);
    EXPECT_NO_THROW(tester5.Triangulate());
    EXPECT_TRUE(LinearAlgebra::Matrix<short>((const short *) initial5_triangulated, 2, 2) == tester5);

    const short initial6[2][2] = {{2,     -12},
                                  {-1000, 2000}};
    short initial6_triangulated[2][2] = {{-1000, 2000},
                                         {0,     8}};
    auto tester6 = LinearAlgebra::Matrix<short>((const short *) initial6, 2, 2);
    EXPECT_NO_THROW(tester6.Triangulate());
    EXPECT_FALSE(LinearAlgebra::Matrix<short>((const short *) initial6_triangulated, 2, 2) == tester6);
    EXPECT_NO_THROW(initial6_triangulated[1][1] = -8);
    EXPECT_TRUE(LinearAlgebra::Matrix<short>((const short *) initial6_triangulated, 2, 2) == tester6);

    /*const double initial7[4][5] = {{1, 2, 3, 4, 7},
                                   {2, 1, 2, 3, 6},
                                   {3, 2, 1, 2, 7},
                                   {4, 3, 2, 1, 18}};
    const double initial7_triangulated[4][5] = {{4, 3,    2,   1,    18},
                                                {0, 1.25, 2.5, 4.25, 2.5},
                                                {0, 0,    2,   4,    -2},
                                                {0, 0,    0,   2,    -6}};
    auto tester7 = LinearAlgebra::Matrix<double>((const double *) initial7, 4, 5);
    EXPECT_NO_THROW(tester7.Triangulate());
    EXPECT_TRUE(LinearAlgebra::Matrix<double>((const double *) initial7_triangulated, 4, 5) == tester7);*/

}

TEST(Matrix, Determinant)
{
    for (int random = std::rand() % 100 - 50; random < std::rand() % 200 + 100; ++random)
        EXPECT_EQ(LinearAlgebra::Matrix<int>(1, 1, random).Determinant(), random);

    const int initial1[4][4] = {{1, 2, 3, 4},
                                {2, 1, 2, 3},
                                {3, 2, 1, 2},
                                {4, 3, 2, 1}};
    auto tester1 = LinearAlgebra::Matrix<int>((const int *) initial1, 4, 4);
    EXPECT_EQ(tester1.Determinant(), -20);
    EXPECT_NO_THROW(tester1.Transpose());
    EXPECT_EQ(tester1.Determinant(), -20);

    const int initial2[3][3] = {{0, 1, 2},
                                {1, 0, 3},
                                {0, 0, 2}};
    auto tester2 = LinearAlgebra::Matrix<int>((const int *) initial2, 2, 2);
    EXPECT_EQ(tester2.Determinant(), -2);
    EXPECT_NO_THROW(tester2.Transpose());
    EXPECT_EQ(tester2.Determinant(), -2);

    const int initial3[4][4] = {{1, 2,  3, 1},
                                {1, -1, 1, 4},
                                {2, 1,  0, 1},
                                {1, 1,  2, 4}};
    auto tester3 = LinearAlgebra::Matrix<int>((const int *) initial3, 4, 4);
    EXPECT_DOUBLE_EQ(tester3.Determinant(), 28.0);
    EXPECT_NO_THROW(tester3.Transpose());
    EXPECT_DOUBLE_EQ(tester3.Determinant(), 28.0);

    EXPECT_THROW(LinearAlgebra::Matrix<int>(2, 3, 5).Determinant(), std::invalid_argument);
    EXPECT_THROW(LinearAlgebra::Matrix<int>(100, 2).Determinant(), std::invalid_argument);
    EXPECT_THROW(LinearAlgebra::Matrix<int>(100, 101).Determinant(), std::invalid_argument);
    EXPECT_NO_THROW(LinearAlgebra::Matrix<int>(20, 20, 0).Determinant());
    EXPECT_EQ(LinearAlgebra::Matrix<int>(20, 20, 0).Determinant(), 0);

    const double initial4[6][6] = {{1,  2,   3,  4,   5,  6},
                                   {7,  8,   9,  10,  11, 12},
                                   {13, 14,  15, 16,  17, 18},
                                   {19, 20,  1,  22,  23, 24},
                                   {25, -26, 27, -28, 29, 30},
                                   {11, 11,  11, -11, 10, -10}};


    EXPECT_DOUBLE_EQ(LinearAlgebra::Matrix<double>((const double *) initial4, 6, 6).Determinant(), -4344000.0);

    const short initial5[2][2] = {{1,  3},
                                  {-2, 5}};
    auto tester5 = LinearAlgebra::Matrix<short>((const short *) initial5, 2, 2);
    EXPECT_EQ(tester5.Determinant(), 11);
    EXPECT_NO_THROW(tester5.Transpose());
    EXPECT_EQ(tester5.Determinant(), 11);

    const float initial6[3][3] = {{1,   0, -2},
                                  {0.5, 3, 1},
                                  {0,   2, -1}};
    auto tester6 = LinearAlgebra::Matrix<float>((const float *) initial6, 3, 3);
    EXPECT_DOUBLE_EQ(tester6.Determinant(), -7.0);
    EXPECT_NO_THROW(tester6.Transpose());
    EXPECT_DOUBLE_EQ(tester6.Determinant(), -7.0);

    const float initial7[3][3] = {{0, -1, 0},
                                  {1, 3,  -2},
                                  {2, 5,  -1}};
    auto tester7 = LinearAlgebra::Matrix<float>((const float *) initial7, 3, 3);
    EXPECT_EQ(tester7.Determinant(), 3);
    EXPECT_NO_THROW(tester7.Transpose());
    EXPECT_EQ(tester7.Determinant(), 3);
    EXPECT_NO_THROW(tester7.Transpose());
    EXPECT_EQ(tester7.Determinant(), 3);
    const float to_change_sign7 = tester7.Triangulate() % 2 == 1 ? -1.0 : 1.0;

    EXPECT_EQ(tester7.Determinant() * to_change_sign7, 3.0);

    const short initial8[4][4] = {{2, 3,  0,  5},
                                  {4, -3, -1, 1},
                                  {2, 5,  1,  3},
                                  {2, 7,  2,  -2}};
    auto tester8 = LinearAlgebra::Matrix<short>((const short *) initial8, 4, 4);
    auto tester8_copy = tester8;
    EXPECT_NO_THROW(tester8.Transpose());
    EXPECT_DOUBLE_EQ(tester8_copy.Determinant(), 42.0);
    EXPECT_DOUBLE_EQ(tester8.Determinant(), 42.0);
    EXPECT_NO_THROW(tester8_copy.Transpose());
    EXPECT_TRUE(tester8_copy == tester8);
    EXPECT_NO_THROW(tester8_copy.Resize(6, 10, 0));
    EXPECT_THROW(tester8_copy.Determinant(), std::invalid_argument);


    const short initial9[4][4] = {{5, 7,  1,  4},
                                  {2, -3, -4, 2},
                                  {3, 2,  1,  1},
                                  {2, 4,  3,  -1}};
    auto tester9 = LinearAlgebra::Matrix<short>((const short *) initial9, 4, 4);
    EXPECT_DOUBLE_EQ(tester9.Determinant(), 75.0);
    EXPECT_NO_THROW(tester9.Transpose());
    EXPECT_EQ(std::round(tester9.Determinant()), 75);

    const short initial10[4][4] = {{3, 4, 2, 1},
                                   {3, 2, 1, 0},
                                   {3, 1, 0, 3},
                                   {3, 3, 2, 1}};
    auto tester10 = LinearAlgebra::Matrix<short>((const short *) initial10, 4, 4);
    EXPECT_DOUBLE_EQ(tester10.Determinant(), 12.0);
    EXPECT_NO_THROW(tester10.Transpose());
    EXPECT_EQ(std::round(tester10.Determinant()), 12);

    const short initial11[4][4] = {{1, 2, 1, 3},
                                   {2, 1, 4, 1},
                                   {3, 3, 2, -1},
                                   {4, 2, 2, -1}};
    auto tester11 = LinearAlgebra::Matrix<short>((const short *) initial11, 4, 4);
    EXPECT_DOUBLE_EQ(tester11.Determinant(), 63.0);
    EXPECT_NO_THROW(tester11.Transpose());
    EXPECT_EQ(std::round(tester11.Determinant()), 63);

    for (std::size_t rows = 1; rows < 10; ++rows)
    {
        for (std::size_t cols = 1; cols < 10; ++cols)
        {
            if (rows == cols) continue;
            EXPECT_ANY_THROW(LinearAlgebra::Matrix<int>(rows, cols, std::rand() % 15 - 5).Determinant());
        }
    }
}

TEST(Matrix, IdentityMatrix)
{
    const short initial1[1][1] = {{1}};
    EXPECT_TRUE(LinearAlgebra::Matrix<unsigned short>::IdentityMatrix(1) ==
                LinearAlgebra::Matrix<short>((const short *) initial1, 1, 1));

    const short initial2[2][2] = {{1, 0},
                                  {0, 1}};
    EXPECT_TRUE(LinearAlgebra::Matrix<unsigned short>::IdentityMatrix(2) ==
                LinearAlgebra::Matrix<short>((const short *) initial2, 2, 2));

    const short initial3[3][3] = {{1, 0, 0},
                                  {0, 1, 0},
                                  {0, 0, 1}};
    EXPECT_TRUE(LinearAlgebra::Matrix<unsigned short>::IdentityMatrix(3) ==
                LinearAlgebra::Matrix<short>((const short *) initial3, 3, 3));


    for (std::size_t counter = 1; counter < 20; ++counter)
        EXPECT_EQ(LinearAlgebra::Matrix<short>::IdentityMatrix(counter).Determinant(), 1);

    for (std::size_t counter = 1; counter < 20; ++counter)
    {
        const auto tester = LinearAlgebra::Matrix<short>::IdentityMatrix(counter);
        auto tester_copy = tester;
        EXPECT_NO_THROW(tester_copy.Transpose());
        EXPECT_TRUE(tester_copy == tester);
    }
}

TEST(Matrix, Multiplication)
{
    for (std::size_t counter = 1; counter < 11; ++counter)
    {
        const auto tester = LinearAlgebra::Matrix<short>::RandomizedMatrix(counter, counter, -100, 100);
        EXPECT_TRUE(tester * LinearAlgebra::Matrix<short>::IdentityMatrix(counter) == tester);
    }

    EXPECT_ANY_THROW(LinearAlgebra::Matrix<short>::RandomizedMatrix(1, 2, -100, 100) *
                     LinearAlgebra::Matrix<short>::RandomizedMatrix(12, 1, -100, 100));
    EXPECT_ANY_THROW(LinearAlgebra::Matrix<short>::RandomizedMatrix(1, 2, -100, 100) *
                     LinearAlgebra::Matrix<short>::RandomizedMatrix(1, 1, -100, 100));
    EXPECT_ANY_THROW(LinearAlgebra::Matrix<short>::RandomizedMatrix(3, 3, -100, 100) *
                     LinearAlgebra::Matrix<short>::RandomizedMatrix(4, 4, -100, 100));
    EXPECT_NO_THROW(LinearAlgebra::Matrix<short>::RandomizedMatrix(1, 2, -100, 100) *
                    LinearAlgebra::Matrix<short>::RandomizedMatrix(2, 1, -100, 100));

    const short initial1_1[2][2] = {{4, 2},
                                    {9, 0}};
    const short initial1_2[2][2] = {{3,  1},
                                    {-3, 4}};
    const short result1[2][2] = {{6,  12},
                                 {27, 9}};
    EXPECT_TRUE(LinearAlgebra::Matrix<short>((const short *) initial1_1, 2, 2) *
                LinearAlgebra::Matrix<short>((const short *) initial1_2, 2, 2) ==
                LinearAlgebra::Matrix<short>((const short *) result1, 2, 2));
    EXPECT_FALSE(LinearAlgebra::Matrix<short>((const short *) initial1_2, 2, 2) *
                 LinearAlgebra::Matrix<short>((const short *) initial1_1, 2, 2) ==
                 LinearAlgebra::Matrix<short>((const short *) result1, 2, 2));

    const short initial2_1[3][2] = {{2,  1},
                                    {-3, 0},
                                    {4,  -1}};
    const short initial2_2[2][3] = {{5,  -1, 6},
                                    {-3, 0,  7}};
    const short result2[3][3] = {{7,   -2, 19},
                                 {-15, 3,  -18},
                                 {23,  -4, 17}};
    EXPECT_TRUE(LinearAlgebra::Matrix<short>((const short *) initial2_1, 3, 2) *
                LinearAlgebra::Matrix<short>((const short *) initial2_2, 2, 3) ==
                LinearAlgebra::Matrix<short>((const short *) result2, 3, 3));
    EXPECT_FALSE(LinearAlgebra::Matrix<short>((const short *) initial2_2, 2, 3) *
                 LinearAlgebra::Matrix<short>((const short *) initial1_2, 3, 2) ==
                 LinearAlgebra::Matrix<short>((const short *) result2, 3, 3));
}

TEST(Matrix, Pow)
{
    for (std::size_t size = 1; size < 10; ++size)
        for (std::size_t degree = 1; degree < 10; ++degree)
            EXPECT_TRUE(LinearAlgebra::Matrix<short>::IdentityMatrix(size).Pow(degree) ==
                        LinearAlgebra::Matrix<short>::IdentityMatrix(size));

    const short initial1[3][3] = {{1, 2, 3},
                                  {4, 5, 6},
                                  {7, 8, 9}};
    const short result1_2[3][3] = {{30,  36,  42},
                                   {66,  81,  96},
                                   {102, 126, 150}};
    const short result1_3[3][3] = {{468,  576,  684},
                                   {1062, 1305, 1548},
                                   {1656, 2034, 2412}};
    EXPECT_TRUE(LinearAlgebra::Matrix<short>((const short *) initial1, 3, 3).Pow(2)
                == LinearAlgebra::Matrix<short>((const short *) result1_2, 3, 3));

    EXPECT_TRUE(LinearAlgebra::Matrix<short>((const short *) initial1, 3, 3).Pow(3)
                == LinearAlgebra::Matrix<short>((const short *) result1_3, 3, 3));
}

TEST (Matrix, IsSymmetric)
{
    for (std::size_t rows = 1; rows < 11; ++rows)
    {
        for (std::size_t cols = 1; cols < 11; ++cols)
        {
            if (rows != cols)
                EXPECT_FALSE(LinearAlgebra::Matrix<short>(rows, cols, 2).IsSymmetric());
            else
                EXPECT_TRUE(LinearAlgebra::Matrix<short>(rows, cols, 2).IsSymmetric());
        }
    }

    const int initial1[3][3] = {{1,  2, -3},
                                {2,  0, 6},
                                {-3, 6, 3}};
    EXPECT_TRUE(LinearAlgebra::Matrix<int>((const int *) initial1, 3, 3).IsSymmetric());

    const int initial2[3][3] = {{1,  2, -3},
                                {2,  0, -6},
                                {-3, 6, 3}};
    EXPECT_FALSE(LinearAlgebra::Matrix<int>((const int *) initial2, 3, 3).IsSymmetric());
}

TEST (Matrix, Track)
{
    for (std::size_t size = 1; size < 15; ++size)
        EXPECT_EQ(LinearAlgebra::Matrix<short>::IdentityMatrix(size).Track(), size);

    for (std::size_t rows = 1; rows < 10; ++rows)
    {
        for (std::size_t cols = 1; cols < 10; ++cols)
        {
            if (rows != cols)
                EXPECT_ANY_THROW(LinearAlgebra::Matrix<short>(rows, cols, std::rand() % 255).Track());
            else
                EXPECT_NO_THROW(LinearAlgebra::Matrix<short>(rows, cols, std::rand() % 255).Track());
        }
    }

    const short initial[3][3] = {{1,  2, 4},
                                 {-1, 5, 2},
                                 {0,  1, -2}};
    EXPECT_EQ(LinearAlgebra::Matrix<short>((const short *) initial, 3, 3).Track(), 4);
}

TEST(Matrix, SelectingSubmatrixForMinor)
{
    const short initial[4][4] = {{1, 2, 1, 3},
                                 {2, 1, 4, 1},
                                 {3, 3, 2, -1},
                                 {4, 2, 2, -1}};
    const auto tester = LinearAlgebra::Matrix<short>((const short *) initial, 4, 4);
    const short result[16][3][3] = {
            {{1, 4, 1}, {3, 2, -1}, {2, 2, -1}},
            {{2, 4, 1}, {3, 2, -1}, {4, 2, -1}},
            {{2, 1, 1}, {3, 3, -1}, {4, 2, -1}},
            {{2, 1, 4}, {3, 3, 2},  {4, 2, 2}},
            {{2, 1, 3}, {3, 2, -1}, {2, 2, -1}},
            {{1, 1, 3}, {3, 2, -1}, {4, 2, -1}},
            {{1, 2, 3}, {3, 3, -1}, {4, 2, -1}},
            {{1, 2, 1}, {3, 3, 2},  {4, 2, 2}},
            {{2, 1, 3}, {1, 4, 1},  {2, 2, -1}},
            {{1, 1, 3}, {2, 4, 1},  {4, 2, -1}},
            {{1, 2, 3}, {2, 1, 1},  {4, 2, -1}},
            {{1, 2, 1}, {2, 1, 4},  {4, 2, 2}},
            {{2, 1, 3}, {1, 4, 1},  {3, 2, -1}},
            {{1, 1, 3}, {2, 4, 1},  {3, 2, -1}},
            {{1, 2, 3}, {2, 1, 1},  {3, 3, -1}},
            {{1, 2, 1}, {2, 1, 4},  {3, 3, 2}}
    };

    for (std::size_t row = 0; row < 4; ++row)
        for (std::size_t col = 0; col < 4; ++col)
            EXPECT_TRUE(tester.GetSubmatrixWithoutRowAndColumn(row, col) ==
                        LinearAlgebra::Matrix<short>((const short *) result[row * 4 + col], 3, 3));
}