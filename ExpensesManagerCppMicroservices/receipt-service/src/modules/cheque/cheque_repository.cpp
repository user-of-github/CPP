#include "./cheque_repository.hpp"
#include "../../common/drogon_db_config.hpp"

namespace expenses::cheques {
  drogon::orm::DbClientPtr ChequeRepository::get_db_client() const {
    return drogon::app().getDbClient(common::kDbClientName);
  }

  drogon::Task<std::vector<Cheques> > ChequeRepository::get_all(const int limit, const int offset) const {
    drogon::orm::CoroMapper<Cheques> mapper{this->get_db_client()};
    co_return co_await mapper
        .orderBy(Cheques::Cols::_receipt_date, drogon::orm::SortOrder::DESC)
        .limit(limit)
        .offset(offset)
        .findAll();
  }

  drogon::Task<std::optional<ChequeAggregate> > ChequeRepository::get_by_id(const int id) const {
    const auto db {this->get_db_client()};
    drogon::orm::CoroMapper<Cheques> cheque_mapper{db};
    drogon::orm::CoroMapper<ChequeItems> items_mapper{db};

    try {
      Cheques cheque = co_await cheque_mapper.findByPrimaryKey(id);
      const auto items{
        co_await items_mapper.findBy(drogon::orm::Criteria(
          ChequeItems::Cols::_cheque_id, drogon::orm::CompareOperator::EQ, id))
      };

      co_return ChequeAggregate{std::move(cheque), std::move(items)};
    } catch (const drogon::orm::UnexpectedRows &) {
      co_return std::nullopt;
    }
  }

  drogon::Task<ChequeAggregate> ChequeRepository::create(const Cheques &cheque, const std::vector<ChequeItems> &items) const {
    const auto transaction{co_await this->get_db_client()->newTransactionCoro()};

    drogon::orm::CoroMapper<Cheques> cheque_mapper{transaction};
    drogon::orm::CoroMapper<ChequeItems> items_mapper{transaction};

    Cheques saved_cheque = co_await cheque_mapper.insert(cheque);
    int64_t cheque_id = saved_cheque.getValueOfId();

    std::vector<ChequeItems> saved_items;
    saved_items.reserve(items.size());

    for (const auto &item: items) {
      item.setChequeId(cheque_id);
      saved_items.push_back(co_await items_mapper.insert(item));
    }

    co_return ChequeAggregate{.cheque = std::move(saved_cheque), .items = std::move(saved_items)};
  }

  drogon::Task<bool> ChequeRepository::remove(const int id) const {
    drogon::orm::CoroMapper<Cheques> mapper{this->get_db_client()};

    const auto deleted_count{
      co_await mapper.deleteBy(drogon::orm::Criteria(Cheques::Cols::_id, drogon::orm::CompareOperator::EQ, id))
    };

    co_return deleted_count > 0;
  }
} // namespace expenses::cheques
