#ifndef REPORTS_SERVICE_REPORTS_REPOSITORY_HPP
#define REPORTS_SERVICE_REPORTS_REPOSITORY_HPP

#pragma once

#include <string>
#include <optional>
#include <vector>
#include <variant>
#include <pqxx/pqxx>
#include <stdexcept>

namespace reports {
  struct ReportRawData {
    std::vector<std::string> headers;
    std::vector<std::vector<std::variant<int, double, std::string>>> rows;
  };

  class ReportRepository {
  public:
    explicit ReportRepository(std::string conn_str);

    std::optional<std::string> find_procedure_name_by_id(const int report_id) const;
    ReportRawData execute_procedure(const std::string& procedure_name) const;

  private:
    std::string connection_string_;
  };

}

#endif //REPORTS_SERVICE_REPORTS_REPOSITORY_HPP
