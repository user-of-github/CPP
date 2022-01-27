#include "url.hpp"

const std::regex URL::kUrlRegularExpression = std::regex("[a-z]");


URL::URL(const char *source) : source_(source)
{}

URL::URL(const std::string_view source) : source_(source)
{}

std::ostream &operator<<(std::ostream &stream, const URL &url)
{
    return stream;
}

constexpr bool URL::CheckValidity(const std::string_view url)
{
    return false;
}

std::string URL::Host() const
{
    return "";
}

std::string URL::Domain() const
{
    return "";
}

std::string URL::Query() const
{
    return "";
}

std::string URL::Source() const
{
    return this->source_;
}