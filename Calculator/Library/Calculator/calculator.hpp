#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <stack>
#include <map>
#include <functional>
#include <cmath>
#include "../Utils/utils.hpp"


namespace Calculator
{
    template<typename ValueType = int>
    class Calculator
    {
        enum class TokenType {kNumber, kOpeningBracket, kClosingBracket, kOperator, kExpressionBeginning};

    public:
        Calculator(const std::string_view &);

        const ValueType Compute();

    private:
        const static std::map<const char, const char> kPriorities;

        const static std::string kInvalidExpressionException;

        const std::map<const char, const std::function<const ValueType(const ValueType, const ValueType)>> kOperations{
                {'+', [](const ValueType a, const ValueType b) -> ValueType const { return a + b; }},
                {'-', [](const ValueType a, const ValueType b) -> ValueType const { return a - b; }},
                {'*', [](const ValueType a, const ValueType b) -> ValueType const { return a * b; }},
                {'/', [](const ValueType a, const ValueType b) -> ValueType const { return a / b; }},
        };

        std::string source_;

        std::stack<char> arithmetic_signs_;
        std::stack<ValueType> numbers_;

        TokenType last_computed_token_;

        void ComputeBracket(const char, std::size_t &);

        void ComputeNumber(std::size_t &);

        void ComputeOperator(const char, std::size_t &);

        void ExecutePriorityOperators(const char = 0);

        void PerformSingleOperation();

        const bool DefineIfMinusRefersToNegativeNumber() const;
    };
}


#endif //CALCULATOR_CALCULATOR_H
