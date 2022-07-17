#include "utils.hpp"


namespace Calculator::Utils
{
    const double StringToDouble(const std::string &source)
    {
        try
        {
            return std::stod(source);
        }
        catch (const std::exception &exception)
        {
            throw std::invalid_argument{std::string{"Invalid float number"} + exception.what()};
        }
    }

    std::string ExtractNumber(const std::string_view &source, const std::size_t extract_from)
    {
        std::size_t commas_counter{0};
        std::size_t total_length{source.size()};
        std::size_t index{extract_from};

        const auto check_conditions{[&]() -> bool {
            if (index >= total_length) return false;
            const auto &curr{source.at(index)};
            return !kBrackets.contains(curr) && !kOperators.contains(curr) && !kSpaceSymbols.contains(curr);
        }};

        while (check_conditions())
        {
            const auto &current_symbol{source.at(index)};

            if (kFloatDividers.contains(current_symbol))
            {
                if (++commas_counter > 1)
                    throw std::invalid_argument{"Invalid float number. To many commas"};
            }
            else if (!kDigits.contains(current_symbol))
                break;

            ++index;
        }

        if (extract_from == index)
            throw std::invalid_argument{"Invalid float number. Provided range doesn't start with a digit"};

        return std::string{source.substr(extract_from, index - extract_from)};
    }
}
