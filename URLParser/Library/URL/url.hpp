#ifndef URLPARSER_URL_HPP
#define URLPARSER_URL_HPP

#include <string_view>
#include <regex>
#include "../Utils/utils.hpp"


class URL
{
public:
    URL(const char *);

    URL(const std::string_view);

    friend std::ostream &operator<<(std::ostream &, const URL &);

    static constexpr bool CheckValidity(const std::string_view);

    std::string Host() const;

    std::string Domain() const;

    std::string Query() const;

    std::string Source() const;

private:
    static const std::regex kUrlRegularExpression;
    std::string source_;
    std::cmatch result_;
};

#endif //URLPARSER_URL_HPP
