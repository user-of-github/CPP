#include "calculator.hpp"


namespace Calculator
{
    template<typename ValueType>
    const std::map<const char, const char> Calculator<ValueType>::kPriorities{{'+', 1},
                                                                              {'-', 1},
                                                                              {'*', 2},
                                                                              {'/', 2}};

    template<typename ValueType>
    Calculator<ValueType>::Calculator(const std::string_view &source, const ExtractorFunctionType &extractor,
                                      const ConverterFunctionType &converter)
            : source_{source}, extractor_{extractor}, converter_{converter}
    {};

    template<typename ValueType>
    const ValueType Calculator<ValueType>::Compute()
    {
        if (!Utils::CheckForCorrectBracketSequence(this->source_))
            throw std::invalid_argument("Provided arithmetic expression is incorrect");

        Utils::RemoveSpaceSymbolsFromString(this->source_);

        std::size_t counter{0}, length{this->source_.size()};

        while (counter < length)
        {
            const auto &current_symbol{this->source_.at(counter)};
            if (Utils::is_digit(current_symbol))
                this->ComputeNumber(counter);
            else if (Utils::is_bracket(current_symbol))
                this->ComputeBracket(current_symbol, counter);
            else if (Utils::is_operator(current_symbol))
                this->ComputeOperator(current_symbol, counter);
            else
                throw std::runtime_error("Something strange met in provided arithmetic expression");
        }

        this->ExecutePriorityOperators();

        //std::cout << "RESULT: " << this->numbers_.top() << '\n';

        return this->numbers_.top();
    }

    template<typename ValueType>
    void Calculator<ValueType>::ComputeBracket(const char bracket, std::size_t &index)
    {
        //std::cout << "BRACKET " << bracket << '\n';

        if (Utils::get_bracket_index(bracket) % 2 == 0) // opening
        {
            this->arithmetic_signs_.push(bracket);
        }
        else // closing
        {
            this->ExecutePriorityOperators();
            if (!Utils::is_bracket(this->arithmetic_signs_.top()))
                throw std::runtime_error("Here must be opening bracket ! 'ComputeBracket' function");

            this->arithmetic_signs_.pop(); // it must be an opening bracket
        }
        ++index;
    }

    template<typename ValueType>
    void Calculator<ValueType>::ComputeNumber(std::size_t &index)
    {
        const auto extracted_string{this->extractor_(this->source_, index)};
        const auto value{this->converter_(extracted_string)};
        //std::cout << "NUMBER " << value << '\n';
        this->numbers_.push(value);
    }

    template<typename ValueType>
    void Calculator<ValueType>::ComputeOperator(const char symbol, size_t &index)
    {
        //std::cout << "Operator: " << symbol << '\n';
        //std::cout << "OPERATOR " << symbol << '\n';

        if (symbol == '-')
            if (this->numbers_.empty() ||(!this->arithmetic_signs_.empty() && Utils::is_bracket(this->arithmetic_signs_.top()) && Utils::get_bracket_index(this->arithmetic_signs_.top()) % 2 == 0))
                this->numbers_.push(ValueType(0));

        if (this->arithmetic_signs_.empty())
        {
            this->arithmetic_signs_.push(symbol);
            ++index;
            return;
        }

        const auto &current_top_operator{this->arithmetic_signs_.top()};
        const auto current_operator_priority{Calculator::kPriorities.at(symbol)};

        if (Utils::is_bracket(current_top_operator))
        {
            // ?? if (const auto index{Utils::get_bracket_index(current_top_operator)}; index % 2 == 0) // opening
            this->arithmetic_signs_.push(symbol);
            ++index;
            return;
        }

        const auto current_top_priority{Calculator::kPriorities.at(current_top_operator)};

        if (current_operator_priority > current_top_priority)
        {
            this->arithmetic_signs_.push(symbol);
            ++index;
            return;
        }

        this->ExecutePriorityOperators();
    }

    template<typename ValueType>
    void Calculator<ValueType>::ExecutePriorityOperators(const char priority)
    {
        const auto conditions{[&]() -> bool const {
            return !this->arithmetic_signs_.empty()
                   && !Utils::is_bracket(this->arithmetic_signs_.top())
                   && priority <= Calculator::kPriorities.at(this->arithmetic_signs_.top());
        }};

        while (conditions())
            this->PerformSingleOperation();
    }

    template<typename ValueType>
    void Calculator<ValueType>::PerformSingleOperation()
    {
        try
        {
            const auto second{this->numbers_.top()};
            this->numbers_.pop();
            const auto first{this->numbers_.top()};
            this->numbers_.pop();

            const auto result{this->kOperations.at(this->arithmetic_signs_.top())(first, second)};
            this->arithmetic_signs_.pop();

            this->numbers_.push(result);
        }
        catch (const std::exception &exception)
        {
            std::cout << exception.what() << '\n';
            throw std::runtime_error("Some troubles in 'PerformSingleOperation' function");
        }
    }
}
