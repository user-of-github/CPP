#ifndef RECEIPT_SERVICE_CHEQUE_REPOSITORY_HPP
#define RECEIPT_SERVICE_CHEQUE_REPOSITORY_HPP

#pragma once

#include <vector>
#include <optional>
#include <drogon/drogon.h>
#include <drogon/orm/CoroMapper.h>
#include "../../db/__generated__/Cheques.h"
#include "../../db/__generated__/ChequeItems.h"

namespace expenses::cheques {
  using drogon_model::expense_db::Cheques;
  using drogon_model::expense_db::ChequeItems;

  struct ChequeAggregate {
    Cheques cheque;
    std::vector<ChequeItems> items;
  };

  class ChequeRepository {
  public:
    ChequeRepository() = default;

    drogon::Task<std::vector<Cheques> > get_all(const int limit, const int offset) const;

    drogon::Task<std::optional<ChequeAggregate>> get_by_id(const int id) const;

    drogon::Task<ChequeAggregate> create(const Cheques &cheque, const std::vector<ChequeItems> &items) const;

    drogon::Task<bool> remove(const int id) const;

  private:
    drogon::orm::DbClientPtr get_db_client() const;
  };
}

#endif //RECEIPT_SERVICE_CHEQUE_REPOSITORY_HPP
