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
    public:
        explicit Calculator(std::string) noexcept;

        void Compute();

        void SetConverter(const std::function<const ValueType(const std::string_view)> &);
        // temp
        void SetExtractor(const std::function<const std::string(const std::string_view &, std::size_t &)> &);

    private:
        const std::map<const char, const std::function<const ValueType(const ValueType, const ValueType)>> kOperations{
                {'+', [](const ValueType a, const ValueType b) -> ValueType const { return a + b; }},
                {'-', [](const ValueType a, const ValueType b) -> ValueType const { return a - b; }},
                {'*', [](const ValueType a, const ValueType b) -> ValueType const { return a * b; }},
                {'/', [](const ValueType a, const ValueType b) -> ValueType const { return a / b; }},
        };

        std::string source_;

        std::function<const ValueType(const std::string_view)> converter_ {Utils::StringToDoubleConverterDefault};
        std::function<const std::string_view(const std::string_view &, std::size_t &)> extractor_ {Utils::ExtractDoubleNumberDefault};

        std::stack<char> arithmetic_signs_;
        std::stack<ValueType> numbers_;
    };
}


#endif //CALCULATOR_CALCULATOR_H
