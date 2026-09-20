#include "./classificator_controller.hpp"

namespace expenses::classificators {
  drogon::Task<drogon::HttpResponsePtr> ClassificatorController::get_payment_methods(drogon::HttpRequestPtr req) const {
    const auto payment_methods{co_await this->repository_.get_payment_methods()};
    co_return common::to_json_response(payment_methods);
  }

  drogon::Task<drogon::HttpResponsePtr> ClassificatorController::get_categories(drogon::HttpRequestPtr req) const {
    const auto categories{co_await this->repository_.get_categories()};
    co_return common::to_json_response(categories);
  }

  drogon::Task<drogon::HttpResponsePtr> ClassificatorController::get_retails_chains(drogon::HttpRequestPtr req) const {
    const auto retail_chains{co_await this->repository_.get_retail_chains()};
    co_return common::to_json_response(retail_chains);
  }

  drogon::Task<drogon::HttpResponsePtr> ClassificatorController::get_retail_shops(drogon::HttpRequestPtr req, const int &retail_chain_id) const {
    const auto shops{co_await this->repository_.get_retail_shops(retail_chain_id)};
    co_return common::to_json_response(shops);
  }
}
