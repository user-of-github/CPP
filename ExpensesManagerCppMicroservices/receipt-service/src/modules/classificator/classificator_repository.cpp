#include "./classificator_repository.hpp"
#include "../../common/drogon_db_config.hpp"
#include "../../db/__generated__/ConcreteShops.h"


namespace expenses::classificators {
  drogon::orm::DbClientPtr ClassificatorRepository::get_db_client() const {
    return drogon::app().getDbClient(common::kDbClientName);
  }

  drogon::Task<std::vector<PaymentMethods> > ClassificatorRepository::get_payment_methods() const {
    drogon::orm::CoroMapper<PaymentMethods> mapper{this->get_db_client()};
    const auto response{
      co_await mapper.findBy(drogon::orm::Criteria(
        PaymentMethods::Cols::_is_active,
        drogon::orm::CompareOperator::EQ,
        true
      ))
    };
    co_return response;
  }

  drogon::Task<std::vector<Categories> > ClassificatorRepository::get_categories() const {
    drogon::orm::CoroMapper<Categories> mapper{this->get_db_client()};
    const auto response{co_await mapper.findAll()};
    co_return response;
  }

  drogon::Task<std::vector<RetailChains> > ClassificatorRepository::get_retail_chains() const {
    drogon::orm::CoroMapper<RetailChains> mapper{this->get_db_client()};
    const auto response{co_await mapper.findAll()};
    co_return response;
  }

  drogon::Task<std::vector<ConcreteShops>> ClassificatorRepository::get_retail_shops(const int retail_id) const {
    drogon::orm::CoroMapper<ConcreteShops> mapper{this->get_db_client()};
    const auto response{co_await mapper.findBy(drogon::orm::Criteria(
      ConcreteShops::Cols::_retail_chain_id, drogon::orm::CompareOperator::EQ, retail_id
    ))};
    co_return response;
  }

  drogon::Task<std::optional<ConcreteShops>> ClassificatorRepository::get_shop_by_id(const int shop_id) const {
    drogon::orm::CoroMapper<ConcreteShops> mapper{this->get_db_client()};
    try {
      co_return co_await mapper.findByPrimaryKey(shop_id);
    } catch (const drogon::orm::UnexpectedRows &) {
      co_return std::nullopt; // Запись не найдена
    }
  }
}
