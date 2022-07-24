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
        using ConverterFunctionType = std::function<const ValueType(const std::string_view)>;
        using ExtractorFunctionType = std::function<const std::string_view(const std::string_view &, std::size_t &)>;

    public:
        Calculator(const std::string_view &, const ExtractorFunctionType & = Utils::ExtractDoubleNumberDefault,
                   const ConverterFunctionType & = Utils::StringToDoubleConverterDefault);

        const ValueType Compute();

    private:
        const static std::map<const char, const char> kPriorities;

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

        void ComputeBracket(const char, std::size_t &);
        void ComputeNumber(std::size_t &);
        void ComputeOperator(const char, std::size_t &);
        void ExecutePriorityOperators(const char = 0);
        void PerformSingleOperation();
    };
}


#endif //CALCULATOR_CALCULATOR_H
