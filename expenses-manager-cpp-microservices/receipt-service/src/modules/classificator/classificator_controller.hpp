#ifndef RECEIPT_SERVICE_CLASSIFICATOR_CONTROLLER_HPP
#define RECEIPT_SERVICE_CLASSIFICATOR_CONTROLLER_HPP

#include <drogon/drogon.h>
#include <nlohmann/json.hpp>
#include "./classificator_repository.hpp"
#include "../../common/utils.hpp"


namespace expenses::classificators {
  class ClassificatorController : public drogon::HttpController<ClassificatorController> {
  public:
    METHOD_LIST_BEGIN
      ADD_METHOD_TO(ClassificatorController::get_payment_methods, "/payment-methods", drogon::Get);
      ADD_METHOD_TO(ClassificatorController::get_categories, "/categories", drogon::Get);
      ADD_METHOD_TO(ClassificatorController::get_retails_chains, "/retail-chains", drogon::Get);
      //ADD_METHOD_TO(ClassificatorController::get_retail_shops, "/shops/retail-chain-id={1}", drogon::Get);

    METHOD_LIST_END

    drogon::Task<drogon::HttpResponsePtr> get_payment_methods(drogon::HttpRequestPtr req) const;

    drogon::Task<drogon::HttpResponsePtr> get_categories(drogon::HttpRequestPtr req) const;

    drogon::Task<drogon::HttpResponsePtr> get_retails_chains(drogon::HttpRequestPtr req) const;

    drogon::Task<drogon::HttpResponsePtr> get_retail_shops(drogon::HttpRequestPtr req, const int &retail_chain_id) const;

    ClassificatorController() = default;

    ~ClassificatorController() override = default;

  private:
    ClassificatorRepository repository_;
  };
}

#endif //RECEIPT_SERVICE_CLASSIFICATOR_CONTROLLER_HPP
