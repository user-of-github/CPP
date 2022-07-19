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
    public:
        explicit Calculator(std::string ) noexcept;

        void Compute();

    private:
        const std::map<const char, const std::function<void()>> kOperations;
        std::string source_;
        std::stack<char> arithmetic_signs_;
        std::stack<ValueType> numbers_;
    };
}


#endif //CALCULATOR_CALCULATOR_H
