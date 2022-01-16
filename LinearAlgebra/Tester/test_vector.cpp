#include <gtest/gtest.h>
#include "../Library/Matrix/Vector/vector.hpp"
#include "../Library/Matrix/Vector/vector.cpp"
#include "../Library/Utils/utils.hpp"
#include "../Library/Utils/utils.cpp"


TEST(Vector, Size)
{
    const std::size_t size = 10;
    const double default_value = 2022.05;

    LinearAlgebra::Vector<double> to_test(size, default_value);

    EXPECT_EQ(to_test.Size(), size);

    for (std::size_t counter = 0; counter < size; ++counter)
        EXPECT_EQ(to_test[counter], default_value);

    EXPECT_EQ(LinearAlgebra::Vector<double>({1, 2, 2, -201}).Size(), 4);
    EXPECT_EQ(LinearAlgebra::Vector<double>({1}).Size(), 1);
    EXPECT_EQ(LinearAlgebra::Vector<double>({1, 1, 1, 1, 1, 1, 1}).Size(), 7);
    EXPECT_EQ(LinearAlgebra::Vector<double>({-20220116}).Size(), 1);

    LinearAlgebra::Vector<int> to_test2({2, 3, 4});
    for (std::size_t counter = std::rand() % 100 + 100; counter < std::rand() % 1000 + 100; ++counter)
    {
        EXPECT_NO_THROW(to_test2.Resize(counter, counter));
        EXPECT_EQ(to_test2.Size(), counter);
    }

    EXPECT_THROW(to_test2.Resize(0), std::runtime_error);
    EXPECT_THROW(LinearAlgebra::Vector<std::string>(-1, ""), std::runtime_error);
    int initial[] = {1, 2, 3, -2000};

    EXPECT_EQ(LinearAlgebra::Vector<int>(initial, sizeof(initial) / sizeof(int)).Sum(), -1994);
}

TEST(Vector, Operators)
{
    LinearAlgebra::Vector<int> tester(10, 0);
    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
    {
        tester[counter] = counter;
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

    LinearAlgebra::Vector<int> tester3(tester);
    EXPECT_TRUE(tester3 == tester);
    EXPECT_NO_THROW(tester3 += 6);
    EXPECT_FALSE(tester3 == tester);
    EXPECT_NO_THROW(tester.Resize(100, 0));
    EXPECT_THROW(tester == tester3, std::runtime_error);
}

TEST(Vector, Norm)
{
    ASSERT_EQ(LinearAlgebra::Vector<int>({4, 4, 4, 4, 0, 0, 0}).GetNorm(), 8);
    ASSERT_EQ(LinearAlgebra::Vector<int>({0, 0, 0, 0, 0, 0, 0, 0, 0}).GetNorm(), 0);
    ASSERT_EQ(LinearAlgebra::Vector<int>({0, -1, 0, 0, 0, 0, 0}).GetNorm(), 1);
    ASSERT_EQ(LinearAlgebra::Vector<int>({0, 0, 0, 0, 0, 0, 1}).GetNorm(), 1);
    ASSERT_EQ(LinearAlgebra::Vector<int>({3, 4, 0, 0, 0, 0, 0}).GetNorm(), 5);

    LinearAlgebra::Vector<double> tester(10, 0);
    double to_check = 0;
    for (std::size_t counter = 0; counter < 10; ++counter)
    {
        double new_item = (std::rand() % 255 - 100) * 0.555; // -100..155
        to_check += new_item * new_item;
        tester[counter] = new_item;
        EXPECT_EQ(tester[counter], new_item);
    }
    EXPECT_TRUE(LinearAlgebra::Utils::IsInEpsilonNeighborHood(std::sqrt(to_check), 0.1, tester.GetNorm()));

    EXPECT_NO_THROW(tester.Normalize());
    EXPECT_TRUE(LinearAlgebra::Utils::IsInEpsilonNeighborHood(1.0, 0.1, tester.GetNorm()));

    EXPECT_TRUE(LinearAlgebra::Utils::IsInEpsilonNeighborHood(3.5327, 0.1, LinearAlgebra::Vector<double>(
            {2.8, 1.6, -0.8, -1.2}).GetNorm()));

    EXPECT_THROW(LinearAlgebra::Vector<double>({0, 0}).Normalize(), std::runtime_error);
}

TEST(Vector, Sum)
{
    const std::size_t size = std::rand() % 200 + 100; // 100 ... 300
    LinearAlgebra::Vector<int> tester(size, 0);
    EXPECT_EQ(tester.Sum(), 0);
    EXPECT_EQ(tester.Size(), size);
    EXPECT_ANY_THROW(tester.Normalize());
    EXPECT_EQ(tester.GetNorm(), 0);

    int to_check = 0;

    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
    {
        const int new_item = std::rand() % 10000 - 5000; // -5000 ... 5000
        to_check += new_item;
        EXPECT_NO_THROW(tester[counter] = new_item);
        EXPECT_TRUE(tester[counter] == new_item);
    }

    EXPECT_EQ(tester.Sum(), to_check);

    LinearAlgebra::Vector<double> tester2({5.0, 6, 7, 8});
    const auto sum_previous = tester2.Sum();
    const auto norm_previous = tester2.GetNorm();
    EXPECT_NO_THROW(tester2.Normalize());
    EXPECT_TRUE(LinearAlgebra::Utils::IsInEpsilonNeighborHood(sum_previous / norm_previous, 0.1, tester2.Sum()));
}