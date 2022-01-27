#include "utils.hpp"


std::string Trim(const std::string &line)
{
    const char kWhiteSpaces[] = {" \t\n\r"};
    const auto first = line.find_first_not_of(kWhiteSpaces);
    if (first == std::string::npos)
        return {};
    const auto last = line.find_last_not_of(kWhiteSpaces);
    return line.substr(first, (last - first + 1));
}