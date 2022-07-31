#include <gtest/gtest.h>
#include "./data_for_tests.hpp"
#include "../Library/Calculator/calculator.hpp"
#include "../Library/Calculator/calculator.cpp"


TEST(Calculator, TasksPack1)
{
    for (const auto &[source, result] : tasks_pack_1)
        EXPECT_DOUBLE_EQ(Calculator::Calculator{source}.Compute(), result);
}

TEST(Calculator, TasksPack2)
{
    for (const auto &[source, result] : tasks_pack_2)
        EXPECT_DOUBLE_EQ(Calculator::Calculator{source}.Compute(), result);
}

TEST(Calculator, TasksPack3FromRealCalcAppHistory)
{
    for (const auto &[source, result] : test_pack_3_with_history_of_my_calculator_app)
        EXPECT_DOUBLE_EQ(Calculator::Calculator<double>{source}.Compute(), result);
}

TEST(Calculator, TasksPack4ComplexExpressions)
{
    for (const auto &[source, result] : test_pack_4_complex)
        EXPECT_DOUBLE_EQ(Calculator::Calculator<double>{source}.Compute(), result);
}

TEST(Calculator, TasksPack5)
{
    for (const auto &[source, result] : test_pack_5)
        EXPECT_EQ(Calculator::Calculator<long long>{source}.Compute(), result);
}
