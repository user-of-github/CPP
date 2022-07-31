#include <gtest/gtest.h>
#include "./data_for_tests.hpp"
#include "../Library/Calculator/calculator.hpp"
#include "../Library/Calculator/calculator.cpp"


TEST(Calculator, tasksPack1)
{
    for (const auto &[source, result] : tasks_pack_1)
        EXPECT_DOUBLE_EQ(Calculator::Calculator{source}.Compute(), result);
}

TEST(Calculator, tasksPack2)
{
    for (const auto &[source, result] : tasks_pack_2)
        EXPECT_DOUBLE_EQ(Calculator::Calculator{source}.Compute(), result);
}