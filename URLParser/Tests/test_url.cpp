#include <gtest/gtest.h>
#include "../Library/Url/url.hpp"
#include "../Library/Url/url.cpp"


struct UrlForTest
{
    std::string full_url;
    std::string protocol;
};

static const UrlForTest tester[] = {
        {"http://www.services.com/images/hardware.gif", "http"},
        {"https://www.eurosport.ru/watch/schedule.shtml", "https"},
        {"file:///C:/Users/User/Desktop/cpp.pdf", "<UNDEFINED>"},
        {"ftp.funet.fi/pub/standards/RFC/rfc959.txt", "<UNDEFINED>"},
        {"httpeurosport.ru/watch/schedule.shtml", "<UNDEFINED>"},
        {"hthpseurosport.ru/watch/schedule.shtml", "<UNDEFINED>"},
        {"ftpeurosport.ru/watch/schedule.shtml", "<UNDEFINED>"},
        {"fileeurosport.ru/watch/schedule.shtml", "<UNDEFINED>"},
        {"ftp.funet.fi/pub/standards/RFC/rfc959.txt", "<UNDEFINED>"},
        {"http://www.domain.org/a?foo=bar", "http"},
        {"/domain.org/a?foo=bar", "<UNDEFINED>"},
        {"/apple.com/a?foo=bar", "<UNDEFINED>"}
};


TEST(Url, Protocol)
{
    for (const auto &test_pair : tester)
        EXPECT_STREQ(Url(test_pair.full_url).Protocol().c_str(), test_pair.protocol.c_str());
}