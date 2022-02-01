#include <gtest/gtest.h>
#include "../Library/Url/url.hpp"
#include "../Library/Url/url.cpp"
#include "test_url_structure.cpp"


TEST(Url, Protocol)
{
    for (const auto &test_pair : tester)
        // EXPECT_STREQ(Url(test_pair.full_url).Protocol().c_str(), test_pair.protocol.c_str());
        std::cout << Url(test_pair.full_url) << '\n';
}