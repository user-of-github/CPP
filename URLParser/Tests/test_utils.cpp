#include <gtest/gtest.h>
#include "../Library/Utils/utils.hpp"
#include "../Library/Utils/utils.cpp"


TEST(Utils, Trim)
{
    EXPECT_STREQ(Utils::Trim(" eriughtegu ").c_str(), "eriughtegu");
    EXPECT_STREQ(Utils::Trim("\n\n\n\t").c_str(), "");
    EXPECT_STREQ(Utils::Trim(" \n \n\n \t  ").c_str(), "");
    EXPECT_STREQ(Utils::Trim("\n\n   \n\t  ").c_str(), "");
    EXPECT_STREQ(Utils::Trim("String without tabs on edges").c_str(), "String without tabs on edges");
    EXPECT_STREQ(Utils::Trim(" \t \n String with tabs on the left").c_str(), "String with tabs on the left");
    EXPECT_STREQ(Utils::Trim("string with tabs on the right\n\t   \t").c_str(), "string with tabs on the right");
}