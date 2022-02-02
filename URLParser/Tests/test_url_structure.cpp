struct UrlForTest
{
    const std::string full_url;
    const std::string protocol;
    const std::string host;
};

const UrlForTest tester[] {
        {"http://www.services.world.com/images/hardware?key1=param1&key2=param2#justsomehash", "http", "www.services.com"},
        {"http://www.services.com/images/hardware?key1=param1&key2=param2#justsomehash", "http", "www.services.com"},
        {"https://www.eurosport.ru/watch/schedule.shtml?time=12024458#somehashagain", "https", "www.eurosport.ru"},
        {"ftp.funet.fi/pub/standards/RFC/rfc959.txt#", Url::kUndefinedUrlPartDesignation, "ftp.funet.fi"},
        {"httpeurosport.ru/watch/schedule.shtml?aa=bb&cc=dd#", Url::kUndefinedUrlPartDesignation, "httpeurosport.ru"},
        {"hthpseurosport.ru/watch/schedule.shtml?#2022", Url::kUndefinedUrlPartDesignation, "hthpseurosport.ru"},
        {"ftpeurosport.ru/watch/schedule.shtml?aa=bb&cc=dd#kek", Url::kUndefinedUrlPartDesignation, "ftpeurosport.ru"},
        {"fileeurosport.ru/watch/schedule.shtml?aa=bb&cc=dd#kek", Url::kUndefinedUrlPartDesignation, "fileeurosport.ru"},
        {"ftp.funet.fi/pub/standards/RFC/rfc959.txt", Url::kUndefinedUrlPartDesignation, "ftp.funet.fi"},
        {"http://www.domain.org/abc?foo=bar&bar=foo#", "http", "www.domain.org"},
        {"/domain.org/a?foo=bar", Url::kUndefinedUrlPartDesignation, "domain.org"},
        {"/apple.com/a?foo=bar", Url::kUndefinedUrlPartDesignation, "apple.com"},
        {"https://developer.mozilla.org/en-US/docs/Web/API/URL/pathname?q=value", "https", "developer.mozilla.org"},
        {"https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host", "https", "developer.mozilla.org:443"},
        {"https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host?", "https", "developer.mozilla.org:443"},
        {"https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host?kek=keke&lol=5f", "https", "developer.mozilla.org:443"},
        {"https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host?kek=keke&lol=5f", "https", "developer.mozilla.org:443"},
};