#include "calculator.hpp"

#include <utility>

namespace Calculator
{
    template<typename ValueType>
    Calculator<ValueType>::Calculator(std::string source) noexcept: source_{std::move(source)}
    {}

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

        while (counter < length)
        {
            if (const auto &current_symbol{this->source_.at(counter)}; is_digit(current_symbol))
            {
                const auto extracted_string{this->extractor_(this->source_, counter)};
                const auto value{this->converter_(extracted_string)}; // LINK TO TEMPLATES (FOR FUTURE)
                std::cout << value << '\n';
                this->numbers_.push(value);
            }
            ++counter;
        }
    }

    template<typename ValueType>
    void Calculator<ValueType>::SetConverter(const std::function<const ValueType(const std::string_view)> &new_converter)
    {
        this->converter_ = new_converter;
    }

    template<typename ValueType>
    void Calculator<ValueType>::SetExtractor(const std::function<const std::string(const std::string_view &, std::size_t &)> &new_extractor)
    {
        this->extractor_ = new_extractor;
    }
}
