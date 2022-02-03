#ifndef URLPARSER_URL_HPP
#define URLPARSER_URL_HPP

#include <regex>
#include "../Utils/utils.hpp"


class Url
{
public:
    static const std::string kUndefinedUrlPartDesignation;


    Url() = delete;

    Url(const char *);

    Url(const std::string &);

    Url(const Url &);

    Url(Url &&) = default;


    std::string Protocol() const;

    std::string Host() const;

    constexpr unsigned short Port() const;

    std::string DomainZone() const;

    std::string Path() const;

    std::string Query() const;

    std::string Hash() const;

    std::string Source() const;

    void Update();

    void Set(const std::string &);

    static constexpr bool CheckValidity(const std::string &);


    Url &operator=(const Url &);

    Url &operator=(Url &&) = default;

    friend std::ostream &operator<<(std::ostream &, const Url &);

private:
    static const std::regex kUrlRegularExpression;
    static const unsigned short kDefaultUrlPort; // 443
    static const std::size_t kProtocolOrder; // 1
    static const std::size_t kHostOrder; // 2
    static const std::size_t kDomainZoneOrder; // 3
    static const std::size_t kPortOrder; // 4
    static const std::size_t kPathOrder; // 5
    static const std::size_t kQueryOrder; // 6
    static const std::size_t kHashOrder; // 7

    std::cmatch result_;

    std::string source_;
    std::string protocol_;
    std::string host_;
    std::string domain_zone_;
    unsigned short port_;
    std::string path_;
    std::string whole_query_;
    std::string hash_;
    std::map<std::string, std::string> query_;
};


#endif //URLPARSER_URL_HPP
