#include <gtest/gtest.h>
#include "../Library/Matrix/Vector/vector.h"
#include "../Library/Matrix/Vector/vector.cpp"


TEST(VectorSize, VectorTests)
{
    const std::size_t size = 10;
    const double default_value = 2022.05;

    LinearAlgebra::Vector<double> to_test(size, default_value);

    EXPECT_EQ(to_test.Size(), size);

    for (std::size_t counter = 0; counter < size; ++counter)
        EXPECT_EQ(to_test[counter], default_value);
}