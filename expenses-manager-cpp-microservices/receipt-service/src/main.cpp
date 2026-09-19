#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>
#include "./common/env.hpp"

int main() {
  trantor::Logger::setLogLevel(trantor::Logger::kTrace);
  drogon::app().setLogPath("");

  const auto env_config{expenses::common::load_env_config()};
  const drogon::orm::PostgresConfig database_configuration{
    .host = env_config.db_host,
    .port = env_config.db_port,
    .databaseName = env_config.db_name,
    .username = env_config.db_user,
    .password = env_config.db_password,
  };

  drogon::app().addDbClient(database_configuration);
  drogon::app().addListener("0.0.0.0", env_config.app_port).run();

  return 0;
}
