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

    template<typename ValueType>
    const std::string Calculator<ValueType>::kInvalidExpressionException{"Error. Provided exception is invalid"};

    template<typename ValueType>
    Calculator<ValueType>::Calculator(const std::string_view &source): raw_source_{source}, source_{source}
    {}

    template<typename ValueType>
    ValueType Calculator<ValueType>::Compute()
    {
        if (!Utils::CheckForCorrectBracketSequence(this->source_))
            throw std::invalid_argument(Calculator::kInvalidExpressionException);

        Utils::RemoveSpaceSymbolsFromString(this->source_);

        const auto &total_length{this->source_.size()};
        std::size_t index{0};
        this->last_computed_token_ = TokenType::kExpressionBeginning;

        while (index < total_length)
        {
            if (const auto &current_symbol{this->source_.at(index)}; Utils::is_digit(current_symbol))
                this->ComputeNumber(index);
            else if (Utils::is_bracket(current_symbol))
                this->ComputeBracket(current_symbol, index);
            else if (Utils::is_operator(current_symbol))
                this->ComputeOperator(current_symbol, index);
            else
                throw std::runtime_error(Calculator::kInvalidExpressionException);
        }

        this->ExecutePriorityOperators();

        this->response_ = this->numbers_.top();

        return this->response_;
    }

    template<typename ValueType>
    void Calculator<ValueType>::ComputeBracket(const char bracket, std::size_t &index)
    {
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
        const auto value{(ValueType) Utils::StringToDoubleConverterDefault(extracted_string)};
        this->numbers_.push(value);
    }

    template<typename ValueType>
    void Calculator<ValueType>::ComputeOperator(const char symbol, size_t &index)
    {
        ++index;

        if (symbol == '-' && this->DefineIfMinusRefersToNegativeNumber()) this->numbers_.push(ValueType(0));

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

        this->ExecutePriorityOperators(Calculator::kPriorities.at(symbol));
        this->arithmetic_signs_.push(symbol);
    }

    template<typename ValueType>
    void Calculator<ValueType>::ExecutePriorityOperators(const char priority)
    {
        const auto default_conditions{[&]() -> bool {
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
        }
        catch (const std::exception &exception)
        {
            std::cout << exception.what() << '\n';
            throw std::runtime_error("Some troubles in 'PerformSingleOperation' function");
        }
    }

    template<typename ValueType>
    bool Calculator<ValueType>::DefineIfMinusRefersToNegativeNumber() const
    {
        if (this->last_computed_token_ == Calculator::TokenType::kExpressionBeginning) return true;
        if (this->last_computed_token_ == Calculator::TokenType::kOpeningBracket) return true;
        if (this->last_computed_token_ == Calculator::TokenType::kNumber) return false;
        if (this->last_computed_token_ == Calculator::TokenType::kClosingBracket) return false;

        throw std::invalid_argument(Calculator::kInvalidExpressionException);
    }


    template<typename ValueType>
    std::ostream &operator<<(std::ostream &stream, Calculator<ValueType> &rhs)
    {
        stream << rhs.raw_source_ << " = ";
        return stream;
    }
}
