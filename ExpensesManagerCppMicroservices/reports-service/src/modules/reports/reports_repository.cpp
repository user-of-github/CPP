#include "./reports_repository.hpp"

namespace reports {
  ReportRepository::ReportRepository(std::string conn_str)
    : connection_string_{std::move(conn_str)} {
  }

  std::optional<std::string> ReportRepository::find_procedure_name_by_id(const int report_id) const {
    pqxx::connection conn{connection_string_};
    pqxx::work txn{conn};

    const pqxx::result result{
      txn.exec_params(
        "SELECT procedure_name FROM reports_procedures_names WHERE id = $1",
        report_id
      )
    };

    if (result.empty()) {
      return std::nullopt;
    }

    return result[0]["procedure_name"].as<std::string>();
  }

  ReportRawData ReportRepository::execute_procedure(const std::string &procedure_name) const {
    pqxx::connection conn{connection_string_};
    pqxx::work txn{conn};

    const pqxx::result result{txn.exec("SELECT * FROM " + procedure_name + "()")};

    ReportRawData data{};

    for (pqxx::row::size_type i{0}; i < result.columns(); ++i) {
      data.headers.push_back(result.column_name(i));
    }

    for (const auto &row: result) {
      std::vector<std::variant<int, double, std::string> > row_data{};

      for (pqxx::row::size_type i{0}; i < row.size(); ++i) {
        if (row[i].is_null()) {
          row_data.push_back(std::string{});
        } else {
          const auto &field = row[i];
          const std::string value_str{field.c_str()};

          try {
            std::size_t pos{0};
            const int int_val{std::stoi(value_str, &pos)};
            if (pos == value_str.length()) {
              row_data.push_back(int_val);
              continue;
            }
          } catch (...) {
          }

          try {
            std::size_t pos{0};
            const double dbl_val{std::stod(value_str, &pos)};
            if (pos == value_str.length()) {
              row_data.push_back(dbl_val);
              continue;
            }
          } catch (...) {
          }

          row_data.push_back(value_str);
        }
      }

      data.rows.push_back(std::move(row_data));
    }

    return data;
  }
} // namespace reports
