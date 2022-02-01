#include "url.hpp"


const std::regex Url::kUrlRegularExpression{
        "(?:(https?|ftp|):\\/)?" // protocol
        "\\/?"
        "("
        "(?:www\\.)?"
        "(?:(?:(?:[^:\\/\\s\\.]+)|(?:[^:\\/\\s]+\\.([a-zA-Z]+)))"
        "(?:\\.([a-zA-Z]{2,6}))?(?:\\:([0-9]+))?)"
        ")" // host + port
        ""
        ".*"
        "(#[a-zA-Z0-9]*)?"
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
    return this->whole_query_;
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
    /*stream << '\t' << "Protocol: " << url.Protocol() << '\n';
    stream << '\t' << "Domain: " << url.Domain() << '\n';
    stream << '\t' << "Query: " << url.Query() << '\n';*/

    for (const auto &item : url.result_)
        stream << '\t' << item << '\n';

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

Url &Url::operator=(const Url &rhs)
{
    *this = Url(rhs);
    return *this;
}

void Url::Set(const std::string &new_to_parse)
{
    this->source_ = new_to_parse;
    this->Update();
}

std::string Url::Hash() const
{
    return this->hash_;
}



// useful links:
/*
    https://stackoverflow.com/questions/18633334/regex-optional-group
    https://gist.github.com/metafeather/202974
 */