#ifndef RECEIPT_SERVICE_CLASSIFICATOR_REPOSITORY_HPP
#define RECEIPT_SERVICE_CLASSIFICATOR_REPOSITORY_HPP

#include <drogon/drogon.h>
#include "../../db/__generated__/PaymentMethods.h"
#include "../../db/__generated__/Categories.h"
#include "../../db/__generated__/RetailChains.h"



namespace expenses::classificators {
  using namespace drogon_model::expense_db;

  class ClassificatorRepository {
  public:
    drogon::Task<std::vector<PaymentMethods> > get_payment_methods() const;

    drogon::Task<std::vector<Categories> > get_categories() const;

    drogon::Task<std::vector<RetailChains> > get_retail_chains() const;

    drogon::Task<std::vector<RetailChains> > get_retail_shops(const int shop_id) const;

    ClassificatorRepository() = default;

  private:
    drogon::orm::DbClientPtr get_db_client() const;
  };
}
#endif //RECEIPT_SERVICE_CLASSIFICATOR_REPOSITORY_HPP
