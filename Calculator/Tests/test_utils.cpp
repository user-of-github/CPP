#include <gtest/gtest.h>
#include <array>
#include "./test_types.hpp"
#include "./data_for_tests.hpp"
#include "../Library/Utils/utils.hpp"
#include "../Library/Utils/utils.cpp"


TEST(Utils, ExtractingNumberValid)
{
    for (const auto &item : valid_strings_for_extracting_numbers)
    {
        std::string response{};
        EXPECT_NO_THROW(response = Calculator::Utils::ExtractNumber(item.source, item.extract_from));
        EXPECT_STREQ(response.c_str(), item.right_response.c_str());
    }
}

TEST(Utils, ExtractingNumberInvalid)
{
    for (const auto &[source, from] : invalid_strings_for_extracting_numbers)
        EXPECT_THROW(Calculator::Utils::ExtractNumber(source, from), std::invalid_argument);
}