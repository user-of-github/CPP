#include "./cheque_controller.hpp"
#include "../../common/utils.hpp"
#include "../../common/exceptions.hpp"

namespace expenses::cheques {
  Json::Value ChequeController::aggregate_to_json(const ChequeAggregate &agg) const {
    Json::Value result {agg.cheque.toJson()};
    Json::Value items_json(Json::arrayValue);
    for (const auto &item: agg.items) {
      items_json.append(item.toJson());
    }
    result["items"] = std::move(items_json);
    return result;
  }

  drogon::Task<drogon::HttpResponsePtr> ChequeController::get_all(drogon::HttpRequestPtr req) const {
    size_t limit{20};
    size_t offset{0};

    const auto &limit_str = req->getParameter("limit");
    const auto &offset_str = req->getParameter("offset");

    if (!limit_str.empty()) {
      limit = std::stoul(limit_str);
    }
    if (!offset_str.empty()) {
      offset = std::stoul(offset_str);
    }

    const auto cheques = co_await this->repository_.get_all(limit, offset);
    co_return common::to_json_response(cheques);
  }

  drogon::Task<drogon::HttpResponsePtr> ChequeController::get(drogon::HttpRequestPtr req, const int64_t id) const {
    if (id <= 0) {
      throw common::exceptions::BadRequestException("Cheque ID must be a positive integer");
    }

    const auto aggregate = co_await this->repository_.get_by_id(id);
    if (!aggregate.has_value()) {
      throw common::exceptions::NotFoundException("Cheque with id " + std::to_string(id) + " not found");
    }

    co_return drogon::HttpResponse::newHttpJsonResponse(this->aggregate_to_json(*aggregate));
  }

  drogon::Task<drogon::HttpResponsePtr> ChequeController::create(drogon::HttpRequestPtr req) const {
    const auto json = req->getJsonObject();

    if (!json) {
      throw common::exceptions::BadRequestException("Invalid JSON body");
    }

    const auto dto {CreateChequeDto::parse(*json)};

    Cheques cheque;
    cheque.setConcreteStoreId(dto.concrete_store_id);
    cheque.setPaymentMethodId(dto.payment_method_id);
    cheque.setTotalAmount(std::format("{:.2f}", dto.total_amount));

    std::vector<ChequeItems> items;
    items.reserve(dto.items.size());

    for (const auto& dto_item : dto.items) {
      ChequeItems item;
      item.setCategoryId(dto_item.category_id);
      item.setProductName(dto_item.product_name);
      item.setQuantity(std::format("{:.3f}", dto_item.quantity));
      item.setUnitPrice(std::format("{:.2f}", dto_item.unit_price));
      item.setTotalPrice(std::format("{:.2f}", dto_item.total_price));

      items.push_back(std::move(item));
    }

    const auto created{co_await repository_.create(std::move(cheque),std::move(items))};

    const auto response {drogon::HttpResponse::newHttpJsonResponse(aggregate_to_json(created))};
    response->setStatusCode(drogon::k201Created);

    co_return response;
  }

  drogon::Task<drogon::HttpResponsePtr> ChequeController::remove(drogon::HttpRequestPtr req, const int64_t id) const {
    if (id <= 0) {
      throw common::exceptions::BadRequestException("Cheque ID must be a positive integer");
    }

    if (const bool deleted {co_await this->repository_.remove(id)}; !deleted) {
      throw common::exceptions::NotFoundException("Cheque with id " + std::to_string(id) + " not found");
    }

    const auto resp {drogon::HttpResponse::newHttpResponse()};
    resp->setStatusCode(drogon::k204NoContent);
    co_return resp;
  }
} // namespace expenses::cheques
