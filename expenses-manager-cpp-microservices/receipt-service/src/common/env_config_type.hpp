#ifndef RECEIPT_SERVICE_ENV_CONFIG_TYPE_HPP
#define RECEIPT_SERVICE_ENV_CONFIG_TYPE_HPP

#include <string>

struct EnvConfigType {
    std::string db_host{};
    std::string db_name {};
    std::string db_user {};
    std::string db_password {};
    unsigned short db_port {};
    unsigned short app_port {};
};

#endif //RECEIPT_SERVICE_ENV_CONFIG_TYPE_HPP
