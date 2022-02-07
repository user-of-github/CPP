#include <gtest/gtest.h>
#include "../Library/Utils/utils.hpp"
#include "../Library/Utils/utils.cpp"
#include "./test_url_structure.cpp"


TEST(Utils, Trim)
{
    EXPECT_STREQ(Utils::Trim(" eriughtegu ").c_str(), "eriughtegu");
    EXPECT_STREQ(Utils::Trim("\n\n\n\t").c_str(), "");
    EXPECT_STREQ(Utils::Trim(" \n \n\n \t  ").c_str(), "");
    EXPECT_STREQ(Utils::Trim("\n\n   \n\t  ").c_str(), "");
    EXPECT_STREQ(Utils::Trim("String without tabs on edges").c_str(), "String without tabs on edges");
    EXPECT_STREQ(Utils::Trim(" \t \n String with tabs on the left").c_str(), "String with tabs on the left");
    EXPECT_STREQ(Utils::Trim("string with tabs on the right\n\t   \t").c_str(), "string with tabs on the right");

    for (const auto &item : not_valid_urls)
        EXPECT_STREQ(Utils::Trim(item).c_str(), item.c_str());
}

TEST(Urils, Split)
{
    struct ToTest
    {
        const std::string source;
        const unsigned short index;
        const std::string result;
        const char divider;
        const unsigned short result_length;
    };

    const ToTest tester[]{
            {
                    "strings separated by space",
                    1,
                    "separated",
                    ' ',
                    4
            },
            {
                    "strings,separated,by,comma",
                    0,
                    "strings",
                    ',',
                    4
            },
            {
                    "strings/separated/by/slash/",
                    3,
                    "slash",
                    '/',
                    4
            },
            {
                    "strings separeated by spaces",
                    3,
                    "spaces",
                    ' ',
                    4
            },
            {
                    "query1=param1&query2=param3&query3=param3&query4=param4",
                    3,
                    "query4=param4",
                    '&',
                    4
            },
            {
                    "query1=param1&query2=param3&query3=param3&query4=param4",
                    0,
                    "query1=param1&query2=param3&query3=param3&query4=param4",
                    '/',
                    1
            },
    };

    for (const auto &item : tester)
    {
        const auto response{Utils::Split(item.source, item.divider)};
        const unsigned short length = std::distance(std::cbegin(response), std::cend(response));
        EXPECT_EQ(length, item.result_length);
        unsigned short counter = 0;
        for (const auto &word : response)
        {
            if (counter == item.index)
                EXPECT_STREQ(word.c_str(), item.result.c_str());
            ++counter;
        }
    }

}