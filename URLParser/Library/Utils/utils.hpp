#ifndef URLPARSER_UTILS_HPP
#define URLPARSER_UTILS_HPP

#include <string>
#include <forward_list>


std::string Trim(const std::string &);

std::forward_list<std::string> Split(const std::string &, const char);

#endif //URLPARSER_UTILS_HPP