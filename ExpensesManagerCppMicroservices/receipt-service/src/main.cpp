#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>
#include "./common/env.hpp"
#include "./common/drogon_db_config.hpp"
#include "./common/exceptions.hpp"

int main() {
  trantor::Logger::setLogLevel(trantor::Logger::kTrace);
  drogon::app().setLogPath("");

  expenses::common::exceptions::set_up_custom_errors_handling();

  const auto env_config{expenses::common::load_env_config()};
  const auto database_configuration {expenses::common::get_drogon_db_config(env_config)};

  drogon::app().addDbClient(database_configuration);
  drogon::app().addListener("0.0.0.0", env_config.app_port).run();

  return 0;
}
