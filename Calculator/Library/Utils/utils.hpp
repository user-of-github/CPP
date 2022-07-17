#ifndef CALCULATOR_UTILS_H
#define CALCULATOR_UTILS_H

#include <string_view>
#include <string>
#include <set>
#include <iostream>
#include <algorithm>


namespace Calculator::Utils
{
    const std::set kDigits {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const std::set kFloatDividers {'.', ','};
    const std::set kSpaceSymbols {' ', '\t', '\r', '\n'};
    const std::set kBrackets {'[', ']', '(', ')', '{', '}', '<', '>'};
    const std::set kOperators {'+', '-', '*', '/', '^', '%'};


    const std::string ExtractNumber(const std::string_view &, const std::size_t);

    const double StringToDouble(const std::string_view &);
}


#endif //CALCULATOR_UTILS_H
