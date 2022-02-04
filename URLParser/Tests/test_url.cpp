#include <gtest/gtest.h>
#include "../Library/Url/url.hpp"
#include "../Library/Url/url.cpp"
#include "test_url_structure.cpp"


TEST(Url, Valid)
{
    for (const auto &url : tester)
        EXPECT_TRUE(Url::CheckValidity(url.source));

    for (const auto &not_url : not_valid_urls)
        EXPECT_FALSE(Url::CheckValidity(not_url));
}

TEST(Url, Protocol)
{
    for (const auto &url : tester)
        EXPECT_STREQ(Url(url.source).Protocol().c_str(), url.protocol.c_str());
}

TEST(Url, Host)
{
    for (const auto &url : tester)
        EXPECT_STREQ(Url(url.source).Host().c_str(), url.host.c_str());
}

TEST(Url, DomainZone)
{
    for (const auto &url : tester)
        EXPECT_STREQ(Url(url.source).DomainZone().c_str(), url.domain_zone.c_str());
}

TEST(Url, Constructors)
{

}