#ifndef RECEIPT_SERVICE_CHEQUE_CONTROLLER_HPP
#define RECEIPT_SERVICE_CHEQUE_CONTROLLER_HPP

#pragma once

#include <drogon/drogon.h>
#include "./cheque_repository.hpp"

namespace expenses::cheques {
  class ChequeController : public drogon::HttpController<ChequeController> {
  public:
    METHOD_LIST_BEGIN
      ADD_METHOD_TO(ChequeController::get_all, "/cheques", drogon::Get);
      ADD_METHOD_TO(ChequeController::get_one, "/cheques/{1}", drogon::Get);
      ADD_METHOD_TO(ChequeController::create, "/cheques", drogon::Post);
      ADD_METHOD_TO(ChequeController::remove, "/cheques/{1}", drogon::Delete);
    METHOD_LIST_END

    drogon::Task<drogon::HttpResponsePtr> get_all(drogon::HttpRequestPtr req) const;

    drogon::Task<drogon::HttpResponsePtr> get_one(drogon::HttpRequestPtr req, const int id) const;

    drogon::Task<drogon::HttpResponsePtr> create(drogon::HttpRequestPtr req) const;

    drogon::Task<drogon::HttpResponsePtr> remove(drogon::HttpRequestPtr req, const int id) const;

  private:
    ChequeRepository repository_;

    Json::Value aggregate_to_json(const ChequeAggregate &agg) const;
  };
} // namespace expenses::cheques

#endif //RECEIPT_SERVICE_CHEQUE_CONTROLLER_HPP
