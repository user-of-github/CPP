#include "url.hpp"


const std::regex Url::kUrlRegularExpression{
        // protocol
        "(?:(https?|ftp|):\\/)?"
        "\\/?"
        // Domain: {host, domain zone, port}
        "("
        "(?:www\\.)?"
        "(?:(?:[^:\\/\\s]+\\.([A-Za-z0-9_]+))|(?:[^:\\/\\s\\.]+))"
        "(?:\\:([0-9]{1,5}))?" // port
        ")"
        // path, file and extension
        "((?:\\/[A-Za-z0-9-_]+)*(?:\\.[a-zA-Z_-]+)?\\/?)"
        // query (search)
        "("
        "\\?" // there can be just '?' sign without any parameters after it
        "(?:"
        "[a-zA-Z0-9]+(?:\\=[a-zA-Z0-9-_]+)?" // exactly catch first pair (key=value) (maybe without value)
        "(?:&[a-zA-Z0-9]+(?:\\=[a-zA-Z0-9-_]+)?)*" // and other are with '&' sign before them, if there are
        ")?"
        ")?"
        // hash (anchor)
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

Url::Url(const Url &rhs) : source_(rhs.source_), domain_zone_(rhs.domain_zone_),
                           protocol_(rhs.protocol_), result_(rhs.result_)
{}


std::string Url::Protocol() const
{
    return this->protocol_;
}

std::string Url::Domain() const
{
    return this->domain_zone_;
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
    if (!std::regex_match(this->source_.c_str(), this->result_, Url::kUrlRegularExpression))
        throw std::invalid_argument("Not a valid URL");

    const auto result_it{std::cbegin(this->result_)};

    const auto found_protocol{std::string{*(result_it + Url::kProtocolOrder)}};
    this->protocol_ = found_protocol.empty() ? Url::kUndefinedUrlPartDesignation : found_protocol;

    const auto found_host{std::string{*(result_it + Url::kHostOrder)}};
    this->host_ = found_host.empty() ? Url::kUndefinedUrlPartDesignation : found_host;

    const auto found_domain_zone{std::string{*(result_it + Url::kDomainZoneOrder)}};
    this->domain_zone_ = found_domain_zone.empty() ? Url::kUndefinedUrlPartDesignation : found_domain_zone;

    const auto found_port{std::string(*(result_it + Url::kPortOrder))};
    this->port_ = found_port.empty() ? Url::kDefaultUrlPort : std::stoi(found_port);

    const auto found_path {std::string(*(result_it + Url::kPathOrder))};

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