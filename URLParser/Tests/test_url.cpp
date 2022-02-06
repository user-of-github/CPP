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

TEST(Url, Source)
{
    for (const auto &url : valid_urls)
        EXPECT_STREQ(Url(url.source).Source().c_str(), url.source.c_str());
}

TEST(Url, SetAndConstructors)
{
    for (const auto &not_url : not_valid_urls)
        EXPECT_THROW(const Url test{not_url}, std::invalid_argument);

    const std::size_t urls_size{sizeof(valid_urls) / sizeof(UrlForTest)};
    for (std::size_t counter = 0; counter < urls_size - 1; ++counter)
    {
        const Url tester{valid_urls[counter].source};
        Url tester2{tester};
        EXPECT_STREQ(tester2.Hash().c_str(), valid_urls[counter].hash.c_str());
        EXPECT_STREQ(tester2.Query().c_str(), valid_urls[counter].query.c_str());
        EXPECT_STREQ(tester2.DomainZone().c_str(), valid_urls[counter].domain_zone.c_str());
        EXPECT_STREQ(tester.Hash().c_str(), valid_urls[counter].hash.c_str());
        tester2.Set(valid_urls[counter + 1].source);
        EXPECT_STREQ(tester2.Hash().c_str(), valid_urls[counter + 1].hash.c_str());
        EXPECT_STREQ(tester2.Query().c_str(), valid_urls[counter + 1].query.c_str());
        EXPECT_STREQ(tester2.DomainZone().c_str(), valid_urls[counter + 1].domain_zone.c_str());
        EXPECT_STREQ(tester.Hash().c_str(), valid_urls[counter].hash.c_str());
    }

    for (std::size_t counter = 0; counter < urls_size - 1; ++counter)
    {
        const Url tester{valid_urls[counter].source};
        auto tester2 = tester;
        EXPECT_STREQ(tester2.Hash().c_str(), valid_urls[counter].hash.c_str());
        EXPECT_STREQ(tester2.Query().c_str(), valid_urls[counter].query.c_str());
        EXPECT_STREQ(tester2.DomainZone().c_str(), valid_urls[counter].domain_zone.c_str());
        EXPECT_STREQ(tester.Hash().c_str(), valid_urls[counter].hash.c_str());
        tester2.Set(valid_urls[counter + 1].source);
        EXPECT_STREQ(tester2.Hash().c_str(), valid_urls[counter + 1].hash.c_str());
        EXPECT_STREQ(tester2.Query().c_str(), valid_urls[counter + 1].query.c_str());
        EXPECT_STREQ(tester2.DomainZone().c_str(), valid_urls[counter + 1].domain_zone.c_str());
        EXPECT_STREQ(tester.Hash().c_str(), valid_urls[counter].hash.c_str());
    }
}


TEST(Url, GetQueryParameterByKey)
{
    struct ToTest
    {
        const std::string source;
        const std::string key;
        const std::string value;
    };

    const ToTest tester[]{
            {"http://www.services.world.com/images/hardware?key1=param1&key2=param2#justsomehash", "key2", "param2"},
            {"http://www.services.world.com/images/hardware?key1=param1&key2=param2#justsomehash","key1","param1"},
            {"http://www.services.world.com/images/hardware?key1=param1&key2=param2#justsomehash","key3",Url::kUndefinedDesignation},
            {"www.site.com/path1/path2/file.extension/?key1&key2&key3=value3#fortest","key1",""},
            {"www.site.com/path1/path2/file.extension/?key1&key2&key3=value3#fortest","key2",""},
            {"www.site.com/path1/path2/file.extension/?key1&key2&key3=value3#fortest","key3","value3"},
            {"www.site.com/path1/path2/file.extension/?key1&key2&key3=value3#fortest","key4",Url::kUndefinedDesignation},
            {"www.site.com/path1/path2/file.extension/?key1=MyURLPARSER&key2&key3=value3#fortest","key1","MyURLPARSER"},
    };

    for (const auto &item : tester)
        EXPECT_STREQ(Url{item.source}.GetQueryParameterByKey(item.key).c_str(), item.value.c_str());
}

