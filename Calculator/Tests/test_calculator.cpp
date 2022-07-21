#include <gtest/gtest.h>
#include "../Library/Calculator/calculator.hpp"
#include "../Library/Calculator/calculator.cpp"


TEST(Calculator, baseConstructors)
{
    Calculator::Calculator test {};

    test.SetExpression("1 + 2 + 69853 + 448");

    test.Compute();
}