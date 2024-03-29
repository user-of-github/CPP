#include "url.hpp"


const std::regex Url::kUrlRegularExpression{
        // Protocol
        "(?:(https?):\\/)?"
        "\\/?"
        // Domain: {host, domain zone, port}
        "("
        "(?:www\\.)?"
        "(?:(?:[^:\\/\\s\\.]+(?:\\.[^:\\/\\s\\.]+)*\\.([A-Za-z0-9_]+))|(?:[^:\\/\\s\\.]+))" // hostname (one with .com.by.., another - without domain at all (ex. localhost))
        "(?:\\:([0-9]{1,5}))?" // port
        ")"
        // Path, file and extension
        "((?:\\/[A-Za-z0-9-_\\.]+)*(?:\\.[A-Za-z_-]+)?\\/?)"
        // Query (search)
        "("
        "\\?" // there can be just '?' sign without any parameters after it
        "(?:"
        "[a-zA-Z0-9]+(?:\\=[a-zA-Z0-9-_]+)?" // exactly catch first pair (key=value) (maybe without value)
        "(?:&[a-zA-Z0-9]+(?:\\=[a-zA-Z0-9-_]+)?)*" // and others are with '&' sign before them, if there are
        ")?"
        ")?"
        // Hash (anchor)
        "(#[a-zA-Z0-9]*)?"
};

const std::string Url::kUndefinedDesignation{"undefined"};
const std::string Url::kDefaultUrlPort{"default"};
const std::size_t Url::kProtocolOrder{1};
const std::size_t Url::kHostOrder{2};
const std::size_t Url::kDomainZoneOrder{3};
const std::size_t Url::kPortOrder{4};
const std::size_t Url::kPathOrder{5};
const std::size_t Url::kQueryOrder{6};
const std::size_t Url::kHashOrder{7};


Url::Url(const char *source) : source_{Utils::Trim(std::string{source})}
{
    this->Update();
}

Url::Url(const std::string &source) : source_{Utils::Trim(source)}
{
    this->Update();
}

Url::Url(const Url &rhs) : source_{rhs.source_}, protocol_{rhs.protocol_}, domain_zone_{rhs.domain_zone_},
                           port_{rhs.port_}, path_{rhs.path_}, whole_query_{rhs.whole_query_},
                           query_{rhs.query_}, hash_{rhs.hash_}, result_{rhs.result_}
{}


std::string Url::Protocol() const
{
    return this->protocol_;
}

std::string Url::Host() const
{
    return this->host_;
}

std::string Url::DomainZone() const
{
    return this->domain_zone_;
}

std::variant<std::string, int> Url::Port() const
{
    return this->port_;
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

void Url::Set(const std::string &new_to_parse)
{
    this->source_ = new_to_parse;
    this->Update();
}

std::string Url::GetQueryParameterByKey(const std::string &key)
{
    if (!this->query_.count(key)) // Map::contains does not work in GitHub Actions
        return Url::kUndefinedDesignation;

    return this->query_.at(key);
}

bool Url::CheckValidity(const std::string &url)
{
    std::cmatch temp_result{};
    return std::regex_match(url.c_str(), temp_result, Url::kUrlRegularExpression);
}


Url &Url::operator=(const Url &rhs)
{
    std::tie(
            this->source_, this->protocol_, this->port_, this->path_,
            this->whole_query_, this->query_, this->hash_, this->result_
    ) = std::tie(
            rhs.source_, rhs.protocol_, rhs.port_, rhs.path_,
            rhs.whole_query_, rhs.query_, rhs.hash_, rhs.result_
    );

    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Url &url)
{
    stream << "URL: " << url.source_ << '\n';
    stream << '\t' << "Protocol: " << url.protocol_ << '\n';
    stream << '\t' << "Host: " << url.host_ << '\n';
    stream << '\t' << "Domain zone: " << url.domain_zone_ << '\n';
    stream << '\t' << "Port: ";
    if (url.port_.index() == 0)
        stream << std::get<std::string>(url.port_);
    else
        stream << std::get<int>(url.port_);
    stream << '\n';
    stream << '\t' << "Path: " << url.path_ << '\n';
    stream << '\t' << "Query: " << url.whole_query_ << '\n';
    stream << '\t' << "Hash (anchor): " << url.hash_ << '\n';

    stream << '\t' << "Splited query: " << '\n';
    for (const auto &[key, value] : url.query_)
        stream << '\t' << '\t' << key << " = " << value << '\n';

    return stream;
}


void Url::Update()
{
    if (!std::regex_match(this->source_.c_str(), this->result_, Url::kUrlRegularExpression))
        throw std::invalid_argument{"Not a valid URL"};

    const auto result_it{std::cbegin(this->result_)};

    const std::string found_protocol{*(result_it + Url::kProtocolOrder)};
    this->protocol_ = found_protocol.empty() ? Url::kUndefinedDesignation : found_protocol;

    const std::string found_host{*(result_it + Url::kHostOrder)};
    this->host_ = found_host.empty() ? Url::kUndefinedDesignation : found_host;

    const std::string found_domain_zone{*(result_it + Url::kDomainZoneOrder)};
    this->domain_zone_ = found_domain_zone.empty() ? Url::kUndefinedDesignation : found_domain_zone;

    const std::string found_port{*(result_it + Url::kPortOrder)};
    if (found_port.empty())
        this->port_ = Url::kDefaultUrlPort;
    else
        this->port_ = std::stoi(found_port);


    const std::string found_path{*(result_it + Url::kPathOrder)};
    this->path_ = found_path.empty() ? "/" : found_path;

    const std::string found_query{*(result_it + Url::kQueryOrder)};
    this->whole_query_ = found_query.empty() ? "?" : found_query;
    this->SplitQuery();

    const std::string found_hash{*(result_it + Url::kHashOrder)};
    this->hash_ = found_hash.empty() ? "#" : found_hash;
}

void Url::SplitQuery()
{
    this->query_.clear();

    const auto query_without_question_mark{this->whole_query_.substr(1, this->whole_query_.size() - 1)};
    const auto splited_query{Utils::Split(query_without_question_mark, '&')};
    for (const auto &item : splited_query)
    {
        const auto splited_item{Utils::Split(item, '=')};
        const auto item_size{std::distance(std::cbegin(splited_item), std::cend(splited_item))};
        this->query_.insert({splited_item.front(), item_size == 2 ? *(++std::begin(splited_item)) : ""});
    }
}