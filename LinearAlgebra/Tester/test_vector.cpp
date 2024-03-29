#include <gtest/gtest.h>
#include "../Library/Matrix/matrix.hpp"
#include "../Library/Matrix/matrix.cpp"


TEST(Vector, Constructors)
{
    auto tester1_matrix{LinearAlgebra::Matrix(1, 6, 5)};
    const auto tester1{LinearAlgebra::Vector(tester1_matrix)};
    EXPECT_EQ(tester1.Sum(), 6 * 5);
    LinearAlgebra::Vector tester2 = LinearAlgebra::Matrix(1, 2, 3);
    EXPECT_EQ(tester2.Sum(), 6);
    EXPECT_THROW(tester2 = LinearAlgebra::Matrix(2, 2, 1), std::runtime_error);
    EXPECT_NO_THROW(tester1_matrix.Resize(2, 6, 5));
    EXPECT_ANY_THROW((LinearAlgebra::Vector<int>) tester1_matrix);
}

TEST(Vector, Size)
{
    const std::size_t size{10};
    const double default_value{2022.05};

    const auto to_test{LinearAlgebra::Vector<double>(size, default_value)};

    EXPECT_EQ(to_test.Size(), size);

    for (std::size_t counter = 0; counter < size; ++counter)
        EXPECT_EQ(to_test[counter], default_value);

    EXPECT_EQ(LinearAlgebra::Vector<double>({1, 2, 2, -201}).Size(), 4);
    EXPECT_EQ(LinearAlgebra::Vector<double>({1}).Size(), 1);
    EXPECT_EQ(LinearAlgebra::Vector<double>({1, 1, 1, 1, 1, 1, 1}).Size(), 7);
    EXPECT_EQ(LinearAlgebra::Vector<double>({-20220116}).Size(), 1);

    LinearAlgebra::Vector to_test2({2, 3, 4});
    for (std::size_t counter = std::rand() % 100 + 100; counter < std::rand() % 1000 + 100; ++counter)
    {
        EXPECT_NO_THROW(to_test2.Resize(counter, counter));
        EXPECT_EQ(to_test2.Size(), counter);
    }

    EXPECT_THROW(to_test2.Resize(0), std::invalid_argument);
    EXPECT_THROW(LinearAlgebra::Vector<std::string>(-1, ""), std::invalid_argument);

    const int initial[]{1, 2, 3, -2000};
    EXPECT_EQ(LinearAlgebra::Vector(initial, sizeof(initial) / sizeof(int)).Sum(), -1994);
}

TEST(Vector, Operators)
{
    auto tester = LinearAlgebra::Vector<int>(10, 0);
    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
    {
        tester[counter] = (int) counter;
        EXPECT_EQ(tester[counter], counter);
    }
    EXPECT_ANY_THROW(tester[tester.Size()]);
    EXPECT_ANY_THROW(tester[-1]);
    EXPECT_NO_THROW(tester[0]);
    EXPECT_ANY_THROW(LinearAlgebra::Vector<std::string>({})[0]);
    EXPECT_ANY_THROW(LinearAlgebra::Vector<std::string>({})[1]);
    EXPECT_ANY_THROW(LinearAlgebra::Vector<std::string>({})[-1]);

    //std::cout << "Tester: " << tester;
    const int rand1 = std::rand() % 1000;

    tester += rand1;
    //std::cout << "Tester: " << tester;

    auto tester2 = tester;
    EXPECT_NO_THROW(tester2 += rand1);
    //std::cout << "Tester 2: " << tester2;

    EXPECT_TRUE(tester + rand1 == tester2);

    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
        EXPECT_TRUE(tester2[counter] == tester[counter] + rand1);

    EXPECT_NO_THROW(tester += tester2);
    EXPECT_NO_THROW(tester *= rand1);

    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
        EXPECT_TRUE(tester[counter] == (tester2[counter] + (tester2[counter] - rand1)) * rand1);

    EXPECT_NO_THROW(tester /= rand1);
    EXPECT_NO_THROW(tester -= tester2);
    EXPECT_NO_THROW(tester += rand1);

    EXPECT_THROW(tester + LinearAlgebra::Vector<int>({std::rand() % 255}), std::runtime_error);
    EXPECT_NO_THROW(tester + LinearAlgebra::Vector<int>(tester.Size(), 0));

    EXPECT_ANY_THROW(tester - LinearAlgebra::Vector<int>({std::rand() % 255}));
    EXPECT_NO_THROW(tester - LinearAlgebra::Vector<int>(tester.Size(), 0));

    EXPECT_NO_THROW(tester * (std::rand() % 255));
    EXPECT_NO_THROW(tester / (std::rand() % 255));
    EXPECT_NO_THROW(tester + (std::rand() % 255));
    EXPECT_NO_THROW(tester - (std::rand() % 255));

    auto tester3 = LinearAlgebra::Vector<int>(tester);
    EXPECT_TRUE(tester3 == tester);
    EXPECT_NO_THROW(tester3 += 6);
    EXPECT_FALSE(tester3 == tester);
    EXPECT_NO_THROW(tester.Resize(100, 0));
    EXPECT_FALSE(tester == tester3);

    EXPECT_TRUE(LinearAlgebra::Vector<int>({1, 2, 3}) == LinearAlgebra::Vector<int>({1, 2, 3}));
    EXPECT_FALSE(LinearAlgebra::Vector<int>({1, 2, 4}) == LinearAlgebra::Vector<int>({1, 2, 3}));
    EXPECT_FALSE(LinearAlgebra::Vector<int>({1, 2}) == LinearAlgebra::Vector<int>({1, 2, 3}));

    auto tester4 = LinearAlgebra::Vector<int>(6, 2022);
    const auto sum4{tester4.Sum()};
    EXPECT_NO_THROW(tester4 /= 2);
    EXPECT_EQ(sum4 / 2, tester4.Sum());
}

TEST(Vector, Norm)
{
    EXPECT_EQ(LinearAlgebra::Vector({4, 4, 4, 4, 0, 0, 0}).GetNorm(), 8);
    EXPECT_EQ(LinearAlgebra::Vector({0, 0, 0, 0, 0, 0, 0, 0, 0}).GetNorm(), 0);
    EXPECT_EQ(LinearAlgebra::Vector({0, -1, 0, 0, 0, 0, 0}).GetNorm(), 1);
    EXPECT_EQ(LinearAlgebra::Vector({0, 0, 0, 0, 0, 0, 1}).GetNorm(), 1);
    EXPECT_EQ(LinearAlgebra::Vector({3, 4, 0, 0, 0, 0, 0}).GetNorm(), 5);

    auto tester = LinearAlgebra::Vector<double>(10, 0);
    double to_check = 0;
    for (std::size_t counter = 0; counter < 10; ++counter)
    {
        double new_item{(std::rand() % 255 - 100) * 0.555}; // -100..155
        to_check += new_item * new_item;
        tester[counter] = new_item;
        EXPECT_EQ(tester[counter], new_item);
    }
    EXPECT_TRUE(LinearAlgebra::Utils::IsInEpsilonNeighborHood(std::sqrt(to_check), 0.1, tester.GetNorm()));

    EXPECT_NO_THROW(tester.Normalize());
    EXPECT_DOUBLE_EQ(tester.GetNorm(), 1.0);

    EXPECT_TRUE(LinearAlgebra::Utils::IsInEpsilonNeighborHood(3.5327, 0.001, LinearAlgebra::Vector<double>(
            {2.8, 1.6, -0.8, -1.2}).GetNorm()));

    EXPECT_THROW(LinearAlgebra::Vector<double>({0, 0}).Normalize(), std::runtime_error);
}

TEST(Vector, Sum)
{
    const std::size_t size = std::rand() % 200 + 100; // 100 ... 300
    auto tester = LinearAlgebra::Vector(size, 0);
    EXPECT_EQ(tester.Sum(), 0);
    EXPECT_EQ(tester.Size(), size);
    EXPECT_ANY_THROW(tester.Normalize());
    EXPECT_EQ(tester.GetNorm(), 0);

    int to_check{0};

    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
    {
        const int new_item{std::rand() % 10000 - 5000}; // -5000 ... 5000
        to_check += new_item;
        EXPECT_NO_THROW(tester[counter] = new_item);
        EXPECT_TRUE(tester[counter] == new_item);
    }

    EXPECT_EQ(tester.Sum(), to_check);

    auto tester2{LinearAlgebra::Vector({5.0, 6.0, 7.0, 8.0})};
    const auto sum_previous{tester2.Sum()};
    const auto norm_previous{tester2.GetNorm()};
    EXPECT_NO_THROW(tester2.Normalize());
    EXPECT_TRUE(LinearAlgebra::Utils::IsInEpsilonNeighborHood(sum_previous / norm_previous, 0.1, tester2.Sum()));
}