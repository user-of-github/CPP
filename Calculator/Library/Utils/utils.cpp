#include "utils.hpp"


namespace Calculator::Utils
{
    const std::string_view ExtractDoubleNumberDefault(const std::string_view &source, std::size_t &extract_from)
    {
        std::size_t commas_counter{0};
        std::size_t total_length{source.size()};
        std::size_t index{extract_from};

        const auto check_conditions{[&]() -> bool {
            if (index >= total_length) return false;
            const auto &curr{source.at(index)};
            return std::find(std::cbegin(kBrackets), std::cend(kBrackets), curr) == std::cend(kBrackets)
                   && std::find(std::cbegin(kOperators), std::cend(kOperators), curr) == std::cend(kOperators)
                   && std::find(std::cbegin(kSpaceSymbols), std::cend(kSpaceSymbols), curr) == std::cend(kSpaceSymbols);
        }};

        while (check_conditions())
        {
            if (const auto &current_symbol{source.at(index)}; kFloatDividers.contains(current_symbol))
            {
                if (++commas_counter > 1) throw std::invalid_argument{"Invalid float number. To many commas"};
            }
            else if (!kDigits.contains(current_symbol)) break;

            ++index;
        }

        if (extract_from == index) throw std::invalid_argument{"Invalid float number. Provided range doesn't start with a digit"};

        const auto response{std::string_view{source.substr(extract_from, index - extract_from)}};

        extract_from = index;

        return response;
    }


    const double StringToDoubleConverterDefault(const std::string_view &source)
    {
        try
        {
            std::string copy{source};
            std::replace(std::begin(copy), std::end(copy), ',', '.');
            return std::stod(copy);
        }
        catch (const std::exception &exception)
        {
            throw std::invalid_argument{std::string{"Invalid float number. "} + exception.what()};
        }
    }


    const bool CheckForCorrectBracketSequence(const std::string_view &query)
    {
        std::stack<char> brackets{};

        for (const auto &symbol : query)
        {
            const auto found_bracket{std::find(std::cbegin(kBrackets), std::cend(kBrackets), symbol)};

            if (found_bracket == std::cend(kBrackets)) continue; // not a bracket

            if (brackets.empty())
            {
                brackets.push(symbol);
                continue;
            }

            if (const auto index{std::distance(std::cbegin(kBrackets), found_bracket)}; index % 2 == 1) // closing brace
            {
                if (kBrackets.at(index - 1) == brackets.top())
                    brackets.pop();
                else
                    return false;
            }
            else // opening bracket
            {
                brackets.push(symbol);
            }
        }

        return brackets.empty();
    }

    void RemoveSpaceSymbolsFromString(std::string &source)
    {
        const auto check_if_space_symbol{[](char symbol) -> bool { return Utils::kSpaceSymbols.contains(symbol); }};
        const auto new_end{std::remove_if(std::begin(source), std::end(source), check_if_space_symbol)};
        source.erase(new_end, std::end(source));
        source.shrink_to_fit();
    }
}
