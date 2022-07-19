#include "calculator.hpp"

#include <utility>

namespace Calculator
{
    /*template<typename ValueType>
    const std::map<const char, const std::function<void()>> Calculator::kOperations{
            {'+', [](const ValueType a, const ValueType b) -> ValueType { return a + b; },}
            { '-', [](const ValueType a, const ValueType b) -> ValueType { return a - b; }, }
            { '/', [](const ValueType a, const ValueType b) -> ValueType { return a / b; }, }
            { '*', [](const ValueType a, const ValueType b) -> ValueType { return a * b; }, }
            { '^', [](const ValueType a, const ValueType b) -> ValueType { return std::pow(a, b); }, }
    };*/


    template<typename ValueType>
    Calculator<ValueType>::Calculator(std::string source) noexcept: source_{std::move(source)}
    {}

    template<typename ValueType>
    void Calculator<ValueType>::Compute()
    {
        if (!Utils::CheckForCorrectBracketSequence(this->source_))
            throw std::invalid_argument("Provided arithmetic expression is incorrect");

        Utils::RemoveSpaceSymbolsFromString(this->source_);

        std::size_t counter {0}, length {this->source_.size()};
    }
}