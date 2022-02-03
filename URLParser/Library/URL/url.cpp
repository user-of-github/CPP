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

const std::string Url::kUndefinedUrlPartDesignation{"undefined"};
const unsigned short Url::kDefaultUrlPort{443}; // 443
const std::size_t Url::kProtocolOrder{1}; // 1
const std::size_t Url::kHostOrder{2}; // 2
const std::size_t Url::kDomainZoneOrder{3}; // 3
const std::size_t Url::kPortOrder{4}; // 4
const std::size_t Url::kPathOrder{5}; // 5
const std::size_t Url::kQueryOrder{6}; // 6
const std::size_t Url::kHashOrder{7}; // 7


Url::Url(const char *source) : source_{Trim(std::string{source})}
{
    this->Update();
}

Url::Url(const std::string &source) : source_{Trim(source)}
{
    this->Update();
}

Url::Url(const Url &rhs) : source_{rhs.source_}, domain_zone_{rhs.domain_zone_},
                           protocol_{rhs.protocol_}, result_{rhs.result_}
{}


std::string Url::Protocol() const
{
    return this->protocol_;
}

std::string Url::Host() const
{
    return this->host_;
}

constexpr unsigned short Url::Port() const
{
    return this->port_;
}

std::string Url::DomainZone() const
{
    return this->domain_zone_;
}

std::string Url::Path() const
{
    return this->path_;
}

std::string Url::Query() const
{
    return this->whole_query_;
}

std::string Url::Hash() const
{
    return this->hash_;
}

std::string Url::Source() const
{
    return this->source_;
}

void Url::Update()
{
    if (!std::regex_match(this->source_.c_str(), this->result_, Url::kUrlRegularExpression))
        throw std::invalid_argument("Not a valid URL");

    const auto result_it{std::cbegin(this->result_)};

    const std::string found_protocol{*(result_it + Url::kProtocolOrder)};
    this->protocol_ = found_protocol.empty() ? Url::kUndefinedUrlPartDesignation : found_protocol;

    const std::string found_host{*(result_it + Url::kHostOrder)};
    this->host_ = found_host.empty() ? Url::kUndefinedUrlPartDesignation : found_host;

    const std::string found_domain_zone{*(result_it + Url::kDomainZoneOrder)};
    this->domain_zone_ = found_domain_zone.empty() ? Url::kUndefinedUrlPartDesignation : found_domain_zone;

    const std::string found_port{*(result_it + Url::kPortOrder)};
    this->port_ = found_port.empty() ? Url::kDefaultUrlPort : std::stoi(found_port);

    const std::string found_path{*(result_it + Url::kPathOrder)};
    this->path_ = found_path.empty() ? "/" : found_path;

    const std::string found_query{*(result_it + Url::kQueryOrder)};
    this->whole_query_ = found_query.empty() ? "?" : found_query;

    const std::string found_hash{*(result_it + Url::kHashOrder)};
    this->hash_ = found_hash.empty() ? "#" : found_hash;
}

void Url::Set(const std::string &new_to_parse)
{
    this->source_ = new_to_parse;
    this->Update();
}

constexpr bool Url::CheckValidity(const std::string &url)
{
    return false;
}


Url &Url::operator=(const Url &rhs)
{
    *this = Url(rhs);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Url &url)
{
    stream << "URL: " << url.source_ << '\n';
    stream << '\t' << "Protocol: " << url.protocol_ << '\n';
    stream << '\t' << "Host: " << url.host_ << '\n';
    stream << '\t' << "Domain zone: " << url.domain_zone_ << '\n';
    stream << '\t' << "Port: " << url.port_ << '\n';
    stream << '\t' << "Path: " << url.path_ << '\n';
    stream << '\t' << "Query: " << url.whole_query_ << '\n';
    stream << '\t' << "Hash (anchor): " << url.hash_ << '\n';

    return stream;
}