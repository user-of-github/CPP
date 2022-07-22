#include <gtest/gtest.h>
#include "./data_for_tests.hpp"
#include "../Library/Calculator/calculator.hpp"
#include "../Library/Calculator/calculator.cpp"


TEST(Calculator, baseConstructors)
{
    for (const auto &[source, result] : tasks)
        EXPECT_DOUBLE_EQ(Calculator::Calculator{source}.Compute(), result);
}