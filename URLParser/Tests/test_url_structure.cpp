#include "../Library/Url/url.hpp"


struct UrlForTest
{
    const std::string source;
    const std::string protocol;
    const std::string host;
    const std::string domain_zone;
    const std::variant<std::string, unsigned short> port;
    const std::string path;
    const std::string query;
    const std::string hash;
};

const UrlForTest valid_urls[]{
        {
                "http://www.services.world.com/images/hardware?key1=param1&key2=param2#justsomehash",
                "http",
                "www.services.world.com",
                "com",
                Url::kDefaultUrlPort,
                "/images/hardware",
                "?key1=param1&key2=param2",
                "#justsomehash"
        },
        {
                "http://www.services.com/images/hardware?key1=param1&key2=param2#justsomehash",
                "http",
                "www.services.com",
                "com",
                Url::kDefaultUrlPort,
                "/images/hardware",
                "?key1=param1&key2=param2",
                "#justsomehash"
        },
        {
                "https://www.eurosport.ru/watch/schedule.shtml?time=12024458#somehashagain",
                "https",
                "www.eurosport.ru",
                "ru",
                Url::kDefaultUrlPort,
                "/watch/schedule.shtml",
                "?time=12024458",
                "#somehashagain"
        },
        {
                "ftp.funet.fi/pub/standards/RFC/rfc959.txt#",
                Url::kUndefinedUrlPartDesignation,
                "ftp.funet.fi",
                "fi",
                Url::kDefaultUrlPort,
                "/pub/standards/RFC/rfc959.txt",
                "?",
                "#"
        },
        {
                "httpeurosport.ru/watch/schedule.shtml?aa=bb&cc=dd#",
                Url::kUndefinedUrlPartDesignation,
                "httpeurosport.ru",
                "ru",
                Url::kDefaultUrlPort,
                "/watch/schedule.shtml",
                "?aa=bb&cc=dd",
                "#"
        },
        {
                "hthpseurosport.ru/watch/schedule.shtml?#2022",
                Url::kUndefinedUrlPartDesignation,
                "hthpseurosport.ru",
                "ru",
                Url::kDefaultUrlPort,
                "/watch/schedule.shtml",
                "?",
                "#2022"
        },
        {
                "ftpeurosport.ru/watch/schedule.shtml?aa=bb&cc=dd#kek",
                Url::kUndefinedUrlPartDesignation,
                "ftpeurosport.ru",
                "ru",
                Url::kDefaultUrlPort,
                "/watch/schedule.shtml",
                "?aa=bb&cc=dd",
                "#kek"
        },
        {
                "fileeurosport.ru/watch/schedule.shtml?aa=bb&cc=dd#kek",
                Url::kUndefinedUrlPartDesignation,
                "fileeurosport.ru",
                "ru",
                Url::kDefaultUrlPort,
                "/watch/schedule.shtml",
                "?aa=bb&cc=dd",
                "#kek"
        },
        {
                "ftp.funet.fi/pub/standards/RFC/rfc959.txt",
                Url::kUndefinedUrlPartDesignation,
                "ftp.funet.fi",
                "fi",
                Url::kDefaultUrlPort,
                "/pub/standards/RFC/rfc959.txt",
                "?",
                "#"
        },
        {
                "http://www.domain.org/abc?foo=bar&bar=foo#",
                "http",
                "www.domain.org",
                "org",
                Url::kDefaultUrlPort,
                "/abc",
                "?foo=bar&bar=foo",
                "#"
        },
        {
                "/domain.org/a?foo=bar",
                Url::kUndefinedUrlPartDesignation,
                "domain.org",
                "org",
                Url::kDefaultUrlPort,
                "/a",
                "?foo=bar",
                "#"
        },
        {
                "/apple.com/a?foo=bar",
                Url::kUndefinedUrlPartDesignation,
                "apple.com",
                "com",
                Url::kDefaultUrlPort,
                "/a",
                "?foo=bar",
                "#"
        },
        {
                "https://developer.mozilla.org/en-US/docs/Web/API/URL/pathname?q=value",
                "https",
                "developer.mozilla.org",
                "org",
                Url::kDefaultUrlPort,
                "/en-US/docs/Web/API/URL/pathname",
                "?q=value",
                "#"
        },
        {
                "https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host",
                "https",
                "developer.mozilla.org:443",
                "org",
                443,
                "/en-US/docs/Web/API/URL/host",
                "?",
                "#"
        },
        {
                "https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host?",
                "https",
                "developer.mozilla.org:443",
                "org",
                443,
                "/en-US/docs/Web/API/URL/host",
                "?",
                "#"
        },
        {
                "https://developer.mozilla.org:443/en-US/docs/Web/API/URL/host?kek=keke&lol=5f",
                "https",
                "developer.mozilla.org:443",
                "org",
                443,
                "/en-US/docs/Web/API/URL/host",
                "?kek=keke&lol=5f",
                "#"
        },
        {
                "https://localhost/catalog.html?authorized=false#login",
                "https",
                "localhost",
                Url::kUndefinedUrlPartDesignation,
                Url::kDefaultUrlPort,
                "/catalog.html",
                "?authorized=false",
                "#login"
        },
        {
                "http://sites.utoronto.ca/webdocs/HTMLdocs/NewHTML/url_ftp.html",
                "http",
                "sites.utoronto.ca",
                "ca",
                Url::kDefaultUrlPort,
                "/webdocs/HTMLdocs/NewHTML/url_ftp.html",
                "?",
                "#"
        },
        {
                "https://e.mail.ru/inbox",
                "https",
                "e.mail.ru",
                "ru",
                Url::kDefaultUrlPort,
                "/inbox",
                "?",
                "#"
        },
        {
                "https://yandex.by/internet/",
                "https",
                "yandex.by",
                "by",
                Url::kDefaultUrlPort,
                "/internet/",
                "?",
                "#"
        },
        {
                "https://learn.javascript.ru/xmlhttprequest",
                "https",
                "learn.javascript.ru",
                "ru",
                Url::kDefaultUrlPort,
                "/xmlhttprequest",
                "?",
                "#"
        },
        {
                "http://192.168.0.1:80/html/index/login",
                "http",
                "192.168.0.1:80",
                "1",
                80,
                "/html/index/login",
                "?",
                "#"
        },
        {
                "192.168.0.1:80/html/index/login",
                Url::kUndefinedUrlPartDesignation,
                "192.168.0.1:80",
                "1",
                80,
                "/html/index/login",
                "?",
                "#"
        },
        {
                "https://github.com/user-of-github?tab=repositories",
                "https",
                "github.com",
                "com",
                Url::kDefaultUrlPort,
                "/user-of-github",
                "?tab=repositories",
                "#"
        },
        {
                "https://github.com/user-of-github/BSUIR_Labs_Programming/blob/master/.github/workflows/main.yml",
                "https",
                "github.com",
                "com",
                Url::kDefaultUrlPort,
                "/user-of-github/BSUIR_Labs_Programming/blob/master/.github/workflows/main.yml",
                "?",
                "#"
        },
        {
                "https://vk.com",
                "https",
                "vk.com",
                "com",
                Url::kDefaultUrlPort,
                "/",
                "?",
                "#"
        },
        {
                "https://github.com?kek=kek",
                "https",
                "github.com",
                "com",
                Url::kDefaultUrlPort,
                "/",
                "?kek=kek",
                "#"
        },
        {
                "https://github.com/?kek=kek",
                "https",
                "github.com",
                "com",
                Url::kDefaultUrlPort,
                "/",
                "?kek=kek",
                "#"
        },
        {
                "https://github.com/",
                "https",
                "github.com",
                "com",
                Url::kDefaultUrlPort,
                "/",
                "?",
                "#"
        },
        {
                "https://github.com/?",
                "https",
                "github.com",
                "com",
                Url::kDefaultUrlPort,
                "/",
                "?",
                "#"
        },
        {
                "https://github.com/?#",
                "https",
                "github.com",
                "com",
                Url::kDefaultUrlPort,
                "/",
                "?",
                "#"
        },
};


const std::string not_valid_urls[]{
        "htps://www.vk.com",
        "http:://www.vk.com",
        "ftp://file.domain/path1/path2/#?query=5",
        "httpp://learn.javascript.ru/xmlhttprequest",
        "https:.//learn.javascript.ru/xmlhttprequest",
        "https:/./learn.javascript.ru/xmlhttprequest",
        "https://.learn.javascript.ru/xmlhttprequest",
        "https:////lear.javascript.ru/xmlhttprequest",
        "https://lear..javascript.ru/xmlhttprequest",
        "https://lear.javascript.ru./xmlhttprequest",
        "https://lear.javascript..ru/xmlhttprequest",
};