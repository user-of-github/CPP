#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <stack>
#include <functional>
#include <cmath>


namespace Calculator
{
    template<typename ValueType = double>
    class Calculator
    {
    public:
        Calculator(const std::string &) noexcept;

        void Compute();

    private:
        const std::map<const char, const std::function<void()>> kOperations;
        std::string source_;
        std::stack<char> arithmetic_signs_;
        std::stack<ValueType> numbers_;
    };

    template<typename ValueType>
    Calculator<ValueType>::Calculator(const std::string &source) noexcept: source_{source} {}

    template<typename ValueType>
    void Calculator<ValueType>::Compute()
    {

    }
}


#endif //CALCULATOR_CALCULATOR_H
