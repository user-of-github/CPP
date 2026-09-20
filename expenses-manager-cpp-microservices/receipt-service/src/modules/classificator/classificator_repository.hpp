#ifndef RECEIPT_SERVICE_CLASSIFICATOR_REPOSITORY_HPP
#define RECEIPT_SERVICE_CLASSIFICATOR_REPOSITORY_HPP

#include <drogon/drogon.h>
#include "./classificator_dto.hpp"


namespace expenses::classificators {
  class ClassificatorRepository {
  public:
    drogon::Task<std::vector<PaymentMethodDto> > get_payment_methods() const;

    drogon::Task<std::vector<CategoryDto> > get_categories() const;

    ClassificatorRepository() = default;

  private:
    drogon::orm::DbClientPtr get_db_client() const;
  };
}
#endif //RECEIPT_SERVICE_CLASSIFICATOR_REPOSITORY_HPP
