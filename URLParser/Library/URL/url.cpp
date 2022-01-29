#include "url.hpp"


const std::regex Url::kUrlRegularExpression{
        "(?:(https?|ftp|):\\/)?"
        "\\/?"
        "([^:\\/\\s]+)"
        ".*"
};

const std::string Url::kUndefinedUrlPartDesignation{"<UNDEFINED>"};


Url::Url(const char *source) : source_(Trim(std::string{source}))
{
    this->Update();
}

Url::Url(const std::string &source) : source_(Trim(source))
{
    this->Update();
}

Url::Url(const Url &rhs) : source_(rhs.source_), domain_(rhs.domain_), protocol_(rhs.protocol_), result_(rhs.result_)
{}


std::string Url::Protocol() const
{
    return this->protocol_;
}

std::string Url::Domain() const
{
    return this->domain_;
}

std::string Url::Query() const
{
    return this->query_;
}

std::string Url::Source() const
{
    return this->source_;
}

constexpr bool Url::CheckValidity(const std::string &url)
{
    return false;
}

std::ostream &operator<<(std::ostream &stream, const Url &url)
{
    stream << "URL: " << url.source_ << '\n';
    stream << '\t' << "Protocol: " << url.Protocol() << '\n';
    stream << '\t' << "Domain: " << url.Domain() << '\n';
    stream << '\t' << "Query: " << url.Query() << '\n';

    return stream;
}

void Url::Update()
{
    std::regex_match(this->source_.c_str(), this->result_, Url::kUrlRegularExpression);

    auto result_it = std::cbegin(this->result_);
    std::advance(result_it, 1);
    const auto found_protocol = std::string{*result_it};
    this->protocol_ = found_protocol.empty() ? Url::kUndefinedUrlPartDesignation : found_protocol;
}



// useful links:
/*
    https://stackoverflow.com/questions/18633334/regex-optional-group
    https://gist.github.com/metafeather/202974
 */