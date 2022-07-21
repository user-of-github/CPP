#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <stack>
#include <map>
#include <functional>
#include <cmath>
#include "../Utils/utils.hpp"


namespace Calculator
{
    template<typename ValueType = double>
    class Calculator
    {
        using ConverterFunctionType = std::function<const ValueType(const std::string_view)>;
        using ExtractorFunctionType = std::function<const std::string_view(const std::string_view &, std::size_t &)>;

    public:
        Calculator(const ExtractorFunctionType & = Utils::ExtractDoubleNumberDefault,
                   const ConverterFunctionType & = Utils::StringToDoubleConverterDefault);

        void SetExpression(const std::string_view &);

        void Compute();

    private:
        const std::map<const char, const std::function<const ValueType(const ValueType, const ValueType)>> kOperations{
                {'+', [](const ValueType a, const ValueType b) -> ValueType const { return a + b; }},
                {'-', [](const ValueType a, const ValueType b) -> ValueType const { return a - b; }},
                {'*', [](const ValueType a, const ValueType b) -> ValueType const { return a * b; }},
                {'/', [](const ValueType a, const ValueType b) -> ValueType const { return a / b; }},
        };

        ConverterFunctionType converter_;
        ExtractorFunctionType extractor_;

        std::string source_;

        std::stack<char> arithmetic_signs_;
        std::stack<ValueType> numbers_;
    };
}


#endif //CALCULATOR_CALCULATOR_H
