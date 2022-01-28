#include <gtest/gtest.h>
#include "../Library/Url/url.hpp"
#include "../Library/Url/url.cpp"

#include <array>


TEST(Url, UrlValidating)
{

}

TEST(Url, Protocol)
{
    const std::array<std::pair<const char *, const char *>, 12> tester = {
            std::make_pair("http://www.services.com/images/hardware.gif", "http"),
            std::make_pair("https://www.eurosport.ru/watch/schedule.shtml", "https"),
            std::make_pair("file:///C:/Users/User/Desktop/cpp.pdf", "<UNDEFINED>"),
            std::make_pair("ftp.funet.fi/pub/standards/RFC/rfc959.txt", "<UNDEFINED>"),
            std::make_pair("httpeurosport.ru/watch/schedule.shtml", "<UNDEFINED>"),
            std::make_pair("hthpseurosport.ru/watch/schedule.shtml", "<UNDEFINED>"),
            std::make_pair("ftpeurosport.ru/watch/schedule.shtml", "<UNDEFINED>"),
            std::make_pair("fileeurosport.ru/watch/schedule.shtml", "<UNDEFINED>"),
            std::make_pair("ftp.funet.fi/pub/standards/RFC/rfc959.txt", "<UNDEFINED>"),
            std::make_pair("http://www.domain.org/a?foo=bar", "http"),
            std::make_pair("/domain.org/a?foo=bar", "<UNDEFINED>"),
            std::make_pair("/apple.com/a?foo=bar", "<UNDEFINED>"),
    };

    for (const auto &test_pair : tester)
    {
        EXPECT_STREQ(Url(test_pair.first).Protocol().c_str(), test_pair.second);
    }
}