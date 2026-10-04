#ifndef REPORTS_SERVICE_ENV_HPP
#define REPORTS_SERVICE_ENV_HPP

#include <string>

namespace reports::common {
  struct EnvConfig {
    std::string db_host{"127.0.0.1"};
    std::string db_name;
    std::string db_user;
    std::string db_password;
    unsigned short db_port{5432};
    unsigned short app_port{4001};
  };

  inline EnvConfig load_env_config() {
    EnvConfig config{};

    if (const char* host {std::getenv("POSTGRES_HOST")}) {
      config.db_host = host;
    }
    if (const char* name {std::getenv("POSTGRES_DB")}) {
      config.db_name = name;
    }
    if (const char* user {std::getenv("POSTGRES_USER")}) {
      config.db_user = user;
    }
    if (const char* pass {std::getenv("POSTGRES_PASSWORD")}) {
      config.db_password = pass;
    }
    if (const char* port {std::getenv("POSTGRES_PORT")}) {
      config.db_port = std::stoi(port);
    }
    if (const char* app_port {std::getenv("REPORTS_SERVICE_APP_PORT")}) {
      config.app_port = std::stoi(app_port);
    }

    return config;
  }

  inline std::string build_connection_string(const EnvConfig& config) {
    return "dbname=" + config.db_name +
           " user=" + config.db_user +
           " password=" + config.db_password +
           " host=" + config.db_host +
           " port=" + std::to_string(config.db_port);
  }
}

#endif //REPORTS_SERVICE_ENV_HPP
