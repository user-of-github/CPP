#ifndef URLPARSER_URL_HPP
#define URLPARSER_URL_HPP

#include <regex>
#include "../Utils/utils.hpp"


class Url
{
public:
    Url() = delete;

    Url(const char *);

    Url(const std::string &);

    Url(const Url &);

    Url(Url &&) = default;


    std::string Protocol() const;

    std::string Domain() const;

    std::string Query() const;

    std::string Source() const;

    static constexpr bool CheckValidity(const std::string &);


    friend std::ostream &operator<<(std::ostream &, const Url &);

private:
    static const std::regex kUrlRegularExpression;
    static const std::string kUndefinedUrlPartDesignation;

    std::cmatch result_;

    std::string source_;
    std::string protocol_;
    std::string domain_;
    std::string query_;

    void Update();
};


#endif //URLPARSER_URL_HPP
