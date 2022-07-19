#include "calculator.hpp"

namespace Calculator
{
    template<typename ValueType>
    const std::map<char, std::function<void()>> Calculator::kOperations{
            {'+', [](const ValueType a, const ValueType b) -> ValueType { return a + b; },}
            { '-', [](const ValueType a, const ValueType b) -> ValueType { return a - b; }, }
            { '/', [](const ValueType a, const ValueType b) -> ValueType { return a / b; }, }
            { '*', [](const ValueType a, const ValueType b) -> ValueType { return a * b; }, }
            { '^', [](const ValueType a, const ValueType b) -> ValueType { return std::pow(a, b); }, }
    };
}