#include <gtest/gtest.h>
#include <array>
#include "./types_for_tests.hpp"
#include "./data_for_tests.hpp"
#include "../Library/Utils/utils.hpp"


TEST(Utils, ExtractingNumberValid)
{
    for (auto item : valid_strings_for_extracting_numbers)
    {
        std::string response{};
        EXPECT_NO_THROW(response = Calculator::Utils::ExtractDoubleNumberDefault(item.source, item.extract_from));
        EXPECT_STREQ(response.c_str(), item.right_response.c_str());
    }
}

TEST(Utils, ExtractingNumberInvalid)
{
    for (auto[source, from] : invalid_strings_for_extracting_numbers)
        EXPECT_THROW(Calculator::Utils::ExtractDoubleNumberDefault(source, from), std::invalid_argument);
}

TEST(Utils, ConvertingAndExtractingNumberValid)
{
    for (auto item : valid_strings_for_converting_to_numbers)
    {
        std::string extracted{};
        EXPECT_NO_THROW(extracted = Calculator::Utils::ExtractDoubleNumberDefault(item.source, item.extract_from));
        double response{};
        EXPECT_NO_THROW(response = Calculator::Utils::StringToDoubleConverterDefault(extracted));
        EXPECT_DOUBLE_EQ(response, item.right_response);
    }
}

TEST(Utils, CheckingCorrectBracketSequenceValid)
{
    for (const auto &sequence : correct_sequences_with_brackets)
        EXPECT_TRUE(Calculator::Utils::CheckForCorrectBracketSequence(sequence));
}

TEST(Utils, CheckingCorrectBracketSequenceInvalid)
{
    for (const auto &sequence : invalid_sequences_with_brackets)
        EXPECT_FALSE(Calculator::Utils::CheckForCorrectBracketSequence(sequence));
}

TEST(Utils, RemovingSpaceSymbols)
{
    for (const auto &[source, response] : sentences_with_space_symbols)
    {
        auto copy{source};
        Calculator::Utils::RemoveSpaceSymbolsFromString(copy);
        EXPECT_STREQ(copy.c_str(), response.c_str());
    }
}
