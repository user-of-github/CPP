#include <gtest/gtest.h>
#include "../Library/Calculator/calculator.hpp"


TEST(Calculator, baseConstructors)
{
    Calculator::Calculator test {"1 + 2 + 3 + 4"};
}