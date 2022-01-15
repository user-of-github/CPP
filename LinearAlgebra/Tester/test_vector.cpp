#include <gtest/gtest.h>
#include "../Library/Matrix/Vector/vector.h"
#include "../Library/Matrix/Vector/vector.cpp"


TEST(VectorTests, VectorSize)
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
    EXPECT_EQ(LinearAlgebra::Vector<double>({}).Size(), 0);

    LinearAlgebra::Vector<int> to_test2({2, 3, 4});
    for (std::size_t counter = std::rand() % 100; counter < std::rand() % 1000 + 100; ++counter)
    {
        to_test2.Resize(counter, counter);
        EXPECT_EQ(to_test2.Size(), counter);
    }
}

TEST(VectorTests, VectorOperators)
{
    LinearAlgebra::Vector<int> tester(10, 0);
    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
        tester[counter] = counter;

    //std::cout << "Tester: " << tester;
    const int rand1 = std::rand() % 1000;

    tester += rand1;
    //std::cout << "Tester: " << tester;

    auto tester2 = tester;
    tester2 += rand1;
    //std::cout << "Tester 2: " << tester2;

    EXPECT_TRUE(tester + rand1 == tester2);

    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
        EXPECT_TRUE(tester2[counter] == tester[counter] + rand1);

    tester += tester2;
    tester *= rand1;

    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
        EXPECT_TRUE(tester[counter] == (tester2[counter] + (tester2[counter] - rand1)) * rand1);

    tester /= rand1;
    tester -= tester2;
    tester += rand1;

    EXPECT_THROW(tester + LinearAlgebra::Vector<int>({std::rand() % 255}), std::runtime_error);
    EXPECT_NO_THROW(tester + LinearAlgebra::Vector<int>(tester.Size(), 0));

    EXPECT_THROW(tester - LinearAlgebra::Vector<int>({std::rand() % 255}), std::runtime_error);
    EXPECT_NO_THROW(tester - LinearAlgebra::Vector<int>(tester.Size(), 0));

    EXPECT_NO_THROW(tester * (std::rand() % 255));
    EXPECT_NO_THROW(tester / (std::rand() % 255));
    EXPECT_NO_THROW(tester + (std::rand() % 255));
    EXPECT_NO_THROW(tester - (std::rand() % 255));
}