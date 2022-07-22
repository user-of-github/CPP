#ifndef CALCULATOR_UTILS_H
#define CALCULATOR_UTILS_H

#include <string_view>
#include <string>
#include <set>
#include <stack>
#include <iostream>
#include <algorithm>
#include <variant>


namespace Calculator::Utils
{
    const std::set kDigits{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const std::set kFloatDividers{'.', ','};
    const std::set kSpaceSymbols{' ', '\t', '\r', '\n'};
    const std::array kBrackets{'(', ')', '<', '>', '[', ']', '{', '}'};
    const std::set<char> kBracketsSet{std::cbegin(kBrackets), std::cend(kBrackets)};
    const std::set kOperators {'+', '-', '*', '/', '^', '%'};

    const std::string_view ExtractDoubleNumberDefault(const std::string_view &, std::size_t &);

    const double StringToDoubleConverterDefault(const std::string_view &);

    const bool CheckForCorrectBracketSequence(const std::string_view &);

    void RemoveSpaceSymbolsFromString(std::string &);

    const auto is_digit{[](const auto symbol) -> bool const { return symbol >= '0' && symbol <= '9'; }};
    const auto is_bracket{[](const auto symbol) -> bool const { return kBracketsSet.contains(symbol); }};
    const auto is_operator{[](const auto symbol) -> bool const { return kOperators.contains(symbol); }};
    const auto get_bracket_index{[](const auto symbol) -> std::size_t const {
        return std::distance(std::cbegin(kBrackets), std::find(std::cbegin(kBrackets), std::cend(kBrackets), symbol));
    }};

    //template <typename ValueType, std::size_t Size>
    //using CollectionsType = std::variant<std::set<ValueType>, std::array<ValueType, Size>, std::set<ValueType>>;
    //template <typename ValueType, std::size_t Size>
    //auto FindInCollection(const CollectionsType<ValueType, Size> &, const ValueType);
}


#endif //CALCULATOR_UTILS_H
