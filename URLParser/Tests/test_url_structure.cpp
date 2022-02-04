struct UrlForTest
{
    const std::string source;
    const std::string protocol;
    const std::string host;
    const std::string domain_zone;
};

const UrlForTest tester[] {
        {"http://www.services.world.com/images/hardware?key1=param1&key2=param2#justsomehash", "http", "www.services.world.com", "com"},
        {"http://www.services.com/images/hardware?key1=param1&key2=param2#justsomehash", "http", "www.services.com", "com"},
        {"https://www.eurosport.ru/watch/schedule.shtml?time=12024458#somehashagain", "https", "www.eurosport.ru", "ru"},
        {"ftp.funet.fi/pub/standards/RFC/rfc959.txt#", Url::kUndefinedUrlPartDesignation, "ftp.funet.fi", "fi"},
        {"httpeurosport.ru/watch/schedule.shtml?aa=bb&cc=dd#", Url::kUndefinedUrlPartDesignation, "httpeurosport.ru", "ru"},
        {"hthpseurosport.ru/watch/schedule.shtml?#2022", Url::kUndefinedUrlPartDesignation, "hthpseurosport.ru", "ru"},
        {"ftpeurosport.ru/watch/schedule.shtml?aa=bb&cc=dd#kek", Url::kUndefinedUrlPartDesignation, "ftpeurosport.ru", "ru"},
        {"fileeurosport.ru/watch/schedule.shtml?aa=bb&cc=dd#kek", Url::kUndefinedUrlPartDesignation, "fileeurosport.ru", "ru"},
        {"ftp.funet.fi/pub/standards/RFC/rfc959.txt", Url::kUndefinedUrlPartDesignation, "ftp.funet.fi", "fi"},
        {"http://www.domain.org/abc?foo=bar&bar=foo#", "http", "www.domain.org", "org"},
        {"/domain.org/a?foo=bar", Url::kUndefinedUrlPartDesignation, "domain.org", "org"},
        {"/apple.com/a?foo=bar", Url::kUndefinedUrlPartDesignation, "apple.com", "com"},
        {"https://developer.mozilla.org/en-US/docs/Web/API/URL/pathname?q=value", "https", "developer.mozilla.org", "org"},
        {"https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host", "https", "developer.mozilla.org:443", "org"},
        {"https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host?", "https", "developer.mozilla.org:443", "org"},
        {"https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host?kek=keke&lol=5f", "https", "developer.mozilla.org:443", "org"},
        {"https://localhost/catalog.html?authorized=false#login", "https", "localhost", Url::kUndefinedUrlPartDesignation},
        {"http://sites.utoronto.ca/webdocs/HTMLdocs/NewHTML/url_ftp.html", "http", "sites.utoronto.ca", "ca"},
        {"https://e.mail.ru/inbox", "https", "e.mail.ru", "ru"},
        {"https://yandex.by/internet/", "https", "yandex.by", "by"},
        {"https://learn.javascript.ru/xmlhttprequest", "https", "learn.javascript.ru", "ru"}
};


const std::string not_valid_urls[] {
    "htps://www.vk.com",
    "http:://www.vk.com",
    "ftp://file.domain/path1/path2/#?query=5",
    "httpp://learn.javascript.ru/xmlhttprequest",
    "https:.//learn.javascript.ru/xmlhttprequest",
    "https:/./learn.javascript.ru/xmlhttprequest",
    "https://.learn.javascript.ru/xmlhttprequest",
    "https:////lear.javascript.ru/xmlhttprequest",
    "https://lear..javascript.ru/xmlhttprequest",
};