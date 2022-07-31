#include "calculator.hpp"


namespace Calculator
{
    template<typename ValueType>
    const std::map<const char, const char> Calculator<ValueType>::kPriorities{
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2}
    };

    template <typename ValueType>
    const std::string Calculator<ValueType>::kInvalidExpressionException {"Error. Provided exception is invalid"};

    template<typename ValueType>
    Calculator<ValueType>::Calculator(const std::string_view &source): source_{source}
    {};

    template<typename ValueType>
    const ValueType Calculator<ValueType>::Compute()
    {
        if (!Utils::CheckForCorrectBracketSequence(this->source_))
            throw std::invalid_argument(Calculator::kInvalidExpressionException);

        Utils::RemoveSpaceSymbolsFromString(this->source_);

        const auto &length{this->source_.size()};
        std::size_t counter{0};

        this->last_computed_token_ = TokenType::kExpressionBeginning;

        while (counter < length)
        {
            std::cout << "index: " << counter << '\n';
            const auto &current_symbol{this->source_.at(counter)};
            if (Utils::is_digit(current_symbol))
                this->ComputeNumber(counter);
            else if (Utils::is_bracket(current_symbol))
                this->ComputeBracket(current_symbol, counter);
            else if (Utils::is_operator(current_symbol))
                this->ComputeOperator(current_symbol, counter);
            else
                throw std::runtime_error(Calculator::kInvalidExpressionException);
        }
        std::cout << "STACKS NUMBERS SIZE " << this->numbers_.size() << '\n';
        std::cout << "STACKS OPERATORS SIZE " << this->arithmetic_signs_.size() << '\n';

        this->ExecutePriorityOperators();

        return this->numbers_.top();
    }

    template<typename ValueType>
    void Calculator<ValueType>::ComputeBracket(const char bracket, std::size_t &index)
    {
        std::cout << "BRACKET: " << bracket << '\n';

        if (Utils::get_bracket_index(bracket) % 2 == 0) // opening
        {
            this->last_computed_token_ = TokenType::kOpeningBracket;
            this->arithmetic_signs_.push(bracket);
        }
        else // closing
        {
            this->last_computed_token_ = TokenType::kClosingBracket;
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
        this->last_computed_token_ = TokenType::kNumber;
        const auto extracted_string{Utils::ExtractDoubleNumberDefault(this->source_, index)};
        const auto value{Utils::StringToDoubleConverterDefault(extracted_string)};
        std::cout << "NUMBER: " << value << '\n';
        this->numbers_.push(value);
    }

    template<typename ValueType>
    void Calculator<ValueType>::ComputeOperator(const char symbol, size_t &index)
    {

        std::cout << "OPERATOR: " << symbol << '\n';
        ++index;
        // is minus referred to number (negative) or just operator
        if (symbol == '-')
            if (this->DefineIfMinusRefersToNegativeNumber()) this->numbers_.push(ValueType(0));

        this->last_computed_token_ = TokenType::kOperator;

        if (this->arithmetic_signs_.empty())
        {
            this->arithmetic_signs_.push(symbol);
            return;
        }

        const auto &current_top_operator{this->arithmetic_signs_.top()};
        const auto current_operator_priority{Calculator::kPriorities.at(symbol)};

        if (Utils::is_bracket(current_top_operator))
        {
            this->arithmetic_signs_.push(symbol);
            return;
        }

        const auto current_top_priority{Calculator::kPriorities.at(current_top_operator)};

        if (current_operator_priority > current_top_priority)
        {
            this->arithmetic_signs_.push(symbol);
            return;
        }

        this->ExecutePriorityOperators();
        this->arithmetic_signs_.push(symbol);
    }

    template<typename ValueType>
    void Calculator<ValueType>::ExecutePriorityOperators(const char priority)
    {

        const auto default_conditions{[&]() -> bool const {
            return !this->arithmetic_signs_.empty()
                   && !Utils::is_bracket(this->arithmetic_signs_.top())
                   && priority <= Calculator::kPriorities.at(this->arithmetic_signs_.top());
        }};

        while (default_conditions())
            this->PerformSingleOperation();
    }

    template<typename ValueType>
    void Calculator<ValueType>::PerformSingleOperation()
    {
        std::cout << "<Performing single operation>\n";
        std::cout << "Operations stack size: " << this->arithmetic_signs_.size() << '\n';
        try
        {
            const auto second{this->numbers_.top()};
            this->numbers_.pop();

            const auto first{this->numbers_.top()};
            this->numbers_.pop();

            const auto operation{this->arithmetic_signs_.top()};
            this->arithmetic_signs_.pop();

            const auto result{this->kOperations.at(operation)(first, second)};

            this->numbers_.push(result);

            std::cout << first << " " << operation << " " << second << " = " << result << '\n';
        }
        catch (const std::exception &exception)
        {
            std::cout << exception.what() << '\n';
            throw std::runtime_error("Some troubles in 'PerformSingleOperation' function");
        }
        std::cout << "Operations stack size: " << this->arithmetic_signs_.size() << '\n';
        std::cout << "</Performing single operation>\n";
    }

    template<typename ValueType>
    const bool Calculator<ValueType>::DefineIfMinusRefersToNegativeNumber() const
    {
        if (this->last_computed_token_ == Calculator::TokenType::kExpressionBeginning) return true;
        if (this->last_computed_token_ == Calculator::TokenType::kNumber) return false;
        if (this->last_computed_token_ == Calculator::TokenType::kOpeningBracket) return true;
        if (this->last_computed_token_ == Calculator::TokenType::kClosingBracket) return false;

        std::cout << this->source_ << '\n';
        throw std::invalid_argument(Calculator::kInvalidExpressionException);
    }
}
