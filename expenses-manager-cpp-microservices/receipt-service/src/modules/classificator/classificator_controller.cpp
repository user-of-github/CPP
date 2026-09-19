#include "./classificator_controller.hpp"

namespace expenses::classificators {
  drogon::Task<drogon::HttpResponsePtr> ClassificatorController::get_payment_methods(drogon::HttpRequestPtr req) const {
    const auto payment_methods{co_await this->repository_.get_payment_methods()};
    const nlohmann::json body{payment_methods};
    const auto response{drogon::HttpResponse::newHttpResponse(drogon::k200OK, drogon::CT_APPLICATION_JSON)};
    response->setBody(body.dump());
    co_return response;
  }

  drogon::Task<drogon::HttpResponsePtr> ClassificatorController::get_categories(drogon::HttpRequestPtr req) const {
    const auto categories{co_await this->repository_.get_categories()};
    const nlohmann::json body{categories};
    const auto response{drogon::HttpResponse::newHttpResponse(drogon::k200OK, drogon::CT_APPLICATION_JSON)};
    response->setBody(body.dump());
    co_return response;
  }
}
