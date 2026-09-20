#ifndef RECEIPT_SERVICE_ENV_HPP
#define RECEIPT_SERVICE_ENV_HPP

#include <string>
#include "./env_config_type.hpp"

namespace expenses::common {
    inline EnvConfigType load_env_config() {
        EnvConfigType response{};

        const char* host = std::getenv("POSTGRES_HOST");
        response.db_host = host ? host : "127.0.0.1";

        response.db_name = std::getenv("POSTGRES_DB");
        response.db_password = std::getenv("POSTGRES_PASSWORD");
        response.db_user = std::getenv("POSTGRES_USER");
        response.db_port = std::stoi(std::getenv("POSTGRES_PORT"));
        response.app_port = std::stoi(std::getenv("APP_PORT"));

        return response;
    }
}

#endif //RECEIPT_SERVICE_ENV_HPP
