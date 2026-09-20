#ifndef RECEIPT_SERVICE_UTILS_HPP
#define RECEIPT_SERVICE_UTILS_HPP

#include <drogon/drogon.h>
#include <vector>

namespace expenses::common {
  // Concept === promise that t has toJson method
  template<typename T>
  concept DrogonModel = requires(const T &t)
  {
    { t.toJson() } -> std::same_as<Json::Value>;
  };

  // For vector of items
  template<DrogonModel T>
  drogon::HttpResponsePtr to_json_response(const std::vector<T> &models, const drogon::HttpStatusCode status = drogon::k200OK) {
    Json::Value array(Json::arrayValue);

    for (const auto &item: models) {
      array.append(item.toJson());
    }

    const auto resp {drogon::HttpResponse::newHttpJsonResponse(std::move(array))};
    resp->setStatusCode(status);
    return resp;
  }

  // For one item
  template<DrogonModel T>
  drogon::HttpResponsePtr to_json_response(const T &model, drogon::HttpStatusCode status = drogon::k200OK) {
    const auto resp {drogon::HttpResponse::newHttpJsonResponse(model.toJson())};
    resp->setStatusCode(status);
    return resp;
  }
}

#endif //RECEIPT_SERVICE_UTILS_HPP
