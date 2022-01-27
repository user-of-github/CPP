#include <gtest/gtest.h>
#include "../Library/URL/url.hpp"
#include "../Library/URL/url.cpp"


TEST(URL, Source)
{
    EXPECT_STREQ(URL("example.com").Source().c_str(), "example.com");
}