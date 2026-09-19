#include "classificator_repository.hpp"

#include <utility>

namespace expenses::classificators {
  drogon::Task<std::vector<PaymentMethodDto> > ClassificatorRepository::get_payment_methods() const {
    const auto db_client = drogon::app().getDbClient("default");

    const std::string sql{"SELECT ID, NAME FROM PAYMENT_METHODS WHERE IS_ACTIVE=TRUE"};
    const auto result{co_await db_client->execSqlCoro(sql)};

    std::vector<PaymentMethodDto> payment_methods;
    payment_methods.reserve(std::size(result));

    for (const auto &row: result) {
      payment_methods.emplace_back(
        row["id"].as<int>(),
        row["name"].as<std::string>()
      );
    }

    co_return payment_methods;
  }

  drogon::Task<std::vector<CategoryDto> > ClassificatorRepository::get_categories() const {
    const auto db_client = drogon::app().getDbClient("default");

    const std::string sql{"SELECT ID, NAME FROM CATEGORIES WHERE IS_ACTIVE=TRUE"};
    const auto result{co_await db_client->execSqlCoro(sql)};

    std::vector<CategoryDto> categories;
    categories.reserve(std::size(result));

    for (const auto &row: result) {
      categories.emplace_back(
        row["id"].as<int>(),
        row["name"].as<std::string>(),
        row["description"].as<std::string>()
      );
    }

    co_return categories;
  }
}
