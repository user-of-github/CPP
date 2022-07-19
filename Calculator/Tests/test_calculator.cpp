#include <gtest/gtest.h>
#include "../Library/Calculator/calculator.hpp"
#include "../Library/Calculator/calculator.cpp"


TEST(Calculator, baseConstructors)
{
    Calculator::Calculator test {"1 + 2 + 3 + 4"};
}