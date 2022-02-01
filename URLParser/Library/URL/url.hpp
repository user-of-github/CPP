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

    std::variant<std::string, short> Port() const;

    std::string Domain() const;

    std::string PathName() const;

    std::string Query() const;

    std::string Hash() const;

    std::string Source() const;

    void Set(const std::string &);

    static constexpr bool CheckValidity(const std::string &);


    Url &operator=(const Url &);

    Url &operator=(Url &&) = default;

    friend std::ostream &operator<<(std::ostream &, const Url &);

private:
    static const std::regex kUrlRegularExpression;

    std::cmatch result_;

    std::string source_;
    std::string protocol_;
    std::string host_;
    std::string domain_;
    std::string whole_query_;
    std::string hash_;
    std::map<std::string, std::string> query_;

    void Update();
};


#endif //URLPARSER_URL_HPP
