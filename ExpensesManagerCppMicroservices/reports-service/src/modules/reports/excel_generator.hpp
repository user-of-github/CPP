#ifndef REPORTS_SERVICE_EXCEL_GENERATOR_HPP
#define REPORTS_SERVICE_EXCEL_GENERATOR_HPP

#pragma once

#include <string>
#include <vector>
#include <variant>
#include <stdexcept>
#include <xlsxwriter.h>

namespace reports {
  class ExcelGenerator {
  public:
    static void build_sheet(
      const std::string& file_path,
      const std::vector<std::string>& headers,
      const std::vector<std::vector<std::variant<int, double, std::string>>>& rows
    );
  };
}

#endif //REPORTS_SERVICE_EXCEL_GENERATOR_HPP
