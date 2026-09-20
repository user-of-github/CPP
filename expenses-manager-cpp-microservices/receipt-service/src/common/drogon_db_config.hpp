#ifndef RECEIPT_SERVICE_DROGON_DB_CONFIG_HPP
#define RECEIPT_SERVICE_DROGON_DB_CONFIG_HPP

#include <drogon/drogon.h>
#include "./env.hpp"

namespace expenses::common {
  constexpr std::string kDbClientName {"default"};
  constexpr int kDbConnectionNumber {4};


  inline drogon::orm::PostgresConfig get_drogon_db_config(const EnvConfigType &env_config) {
    const drogon::orm::PostgresConfig database_configuration{
      .host = env_config.db_host,
      .port = env_config.db_port,
      .databaseName = env_config.db_name,
      .username = env_config.db_user,
      .password = env_config.db_password,
      .connectionNumber = kDbConnectionNumber,
      .name = kDbClientName,
      .isFast = false
    };

    return database_configuration;
  }
}
#endif //RECEIPT_SERVICE_DROGON_DB_CONFIG_HPP
