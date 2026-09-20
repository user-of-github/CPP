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

  drogon::Task<drogon::HttpResponsePtr> ClassificatorController::get_shop_by_id(drogon::HttpRequestPtr req, const int &shop_id) const {
    if (shop_id <= 0) {
      throw common::exceptions::BadRequestException("Shop ID must be a positive integer");
    }

    const auto shop = co_await this->repository_.get_shop_by_id(shop_id);

    if (!shop.has_value()) {
      throw common::exceptions::NotFoundException("Shop with id " + std::to_string(shop_id) + " not found");
    }

    co_return common::to_json_response(*shop);
  }
}
