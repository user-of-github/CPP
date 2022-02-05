#include <gtest/gtest.h>
#include "../Library/Url/url.hpp"
#include "../Library/Url/url.cpp"
#include "test_url_structure.cpp"


TEST(Url, Valid)
{
   for (const auto &url : valid_urls)
        EXPECT_TRUE(Url::CheckValidity(url.source));

    for (const auto &not_url : not_valid_urls)
        EXPECT_FALSE(Url::CheckValidity(not_url));
}

TEST(Url, Protocol)
{
    for (const auto &url : valid_urls)
        EXPECT_STREQ(Url{url.source}.Protocol().c_str(), url.protocol.c_str());
}

TEST(Url, Host)
{
    for (const auto &url : valid_urls)
        EXPECT_STREQ(Url{url.source}.Host().c_str(), url.host.c_str());
}

TEST(Url, DomainZone)
{
    for (const auto &url : valid_urls)
        EXPECT_STREQ(Url{url.source}.DomainZone().c_str(), url.domain_zone.c_str());
}

TEST(Url, Port)
{
    for (const auto &url : valid_urls)
        EXPECT_EQ(Url{url.source}.Port(), url.port);
}

TEST(Url, Path)
{
    for (const auto &url : valid_urls)
        EXPECT_STREQ(Url{url.source}.Path().c_str(), url.path.c_str());
}

TEST(Url, Query)
{
    for (const auto &url : valid_urls)
        EXPECT_STREQ(Url{url.source}.Query().c_str(), url.query.c_str());
}

TEST(Url, Hash)
{
    for (const auto &url : valid_urls)
        EXPECT_STREQ(Url{url.source}.Hash().c_str(), url.hash.c_str());
}



TEST(Url, Constructors)
{
    for (const auto &not_url : not_valid_urls)
        EXPECT_THROW(const Url test{not_url}, std::invalid_argument);
}