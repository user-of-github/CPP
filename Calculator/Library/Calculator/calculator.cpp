#include "calculator.hpp"


namespace Calculator
{
    template<typename ValueType>
    Calculator<ValueType>::Calculator(const ExtractorFunctionType &extractor, const ConverterFunctionType &converter)
            : extractor_{extractor}, converter_{converter}
    {};

    template<typename ValueType>
    void Calculator<ValueType>::Compute()
    {
        if (!Utils::CheckForCorrectBracketSequence(this->source_))
            throw std::invalid_argument("Provided arithmetic expression is incorrect");

        Utils::RemoveSpaceSymbolsFromString(this->source_);

        std::size_t counter{0}, length{this->source_.size()};

        const auto is_digit{[](const auto symbol) -> bool const { return symbol >= '0' && symbol <= '9'; }};
        const auto is_bracket{[](const auto symbol) -> bool const { return Utils::kBracketsSet.contains(symbol); }};
        const auto is_operator{[](const auto symbol) -> bool const { return Utils::kOperators.contains(symbol); }};
        const auto get_bracket_index{[](const auto symbol) -> std::size_t const {
            return std::distance(std::cbegin(Utils::kBrackets), Utils::FindInCollection(Utils::kBrackets, symbol));
        }};

        while (counter < length)
        {
            const auto &current_symbol{this->source_.at(counter)};
            if (is_digit(current_symbol))
            {
                const auto extracted_string{this->extractor_(this->source_, counter)};
                const auto value{this->converter_(extracted_string)};
                std::cout <<"Number " << value << '\n';
                this->numbers_.push(value);
            }
            else if (is_bracket(current_symbol))
            {
                if (get_bracket_index(current_symbol) % 2 == 0) // opening
                {
                    std::cout << "Opening bracket: " << current_symbol << '\n';
                }
                else // closing
                {
                    std::cout << "Closing bracket: " << current_symbol << '\n';
                }
                ++counter;
            }
            else if (is_operator(current_symbol))
            {
                std::cout << "Operator: " << current_symbol << '\n';
                ++counter;
            }
        }
    }

    template<typename ValueType>
    void Calculator<ValueType>::SetExpression(const std::string_view &source)
    {
        this->source_ = std::string{source};
    }
}
