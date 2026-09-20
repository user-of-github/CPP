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

  drogon::Task<drogon::HttpResponsePtr> ChequeController::get_one(drogon::HttpRequestPtr req, const int id) const {
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
    const auto json {req->getJsonObject()};
    if (!json || !json->isObject()) {
      throw common::exceptions::BadRequestException("Invalid JSON body");
    }

    Cheques cheque(*json);

    std::vector<ChequeItems> items{};
    if (json->isMember("items") && (*json)["items"].isArray()) {
      const auto &items_array = (*json)["items"];
      items.reserve(items_array.size());
      for (const auto &item_json: items_array) {
        items.emplace_back(item_json);
      }
    }

    if (items.empty()) {
      throw common::exceptions::BadRequestException("Cheque must contain at least one item");
    }

    const auto created {co_await this->repository_.create(std::move(cheque), std::move(items))};

    auto resp = drogon::HttpResponse::newHttpJsonResponse(this->aggregate_to_json(created));
    resp->setStatusCode(drogon::k201Created);
    co_return resp;
  }

  drogon::Task<drogon::HttpResponsePtr> ChequeController::remove(drogon::HttpRequestPtr req, const int id) const {
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
