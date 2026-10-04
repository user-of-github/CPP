#include "./excel_generator.hpp"


namespace reports {

void ExcelGenerator::build_sheet(
    const std::string& file_path,
    const std::vector<std::string>& headers,
    const std::vector<std::vector<std::variant<int, double, std::string>>>& rows) {

  lxw_workbook* workbook {workbook_new(file_path.c_str())};
  if (!workbook) {
    throw std::runtime_error{"Failed to create workbook"};
  }

  lxw_worksheet* worksheet {workbook_add_worksheet(workbook, nullptr)};
  if (!worksheet) {
    workbook_close(workbook);
    throw std::runtime_error{"Failed to create worksheet"};
  }

  lxw_format* bold {workbook_add_format(workbook)};
  format_set_bold(bold);

  for (std::size_t col {0}; col < headers.size(); ++col) {
    worksheet_write_string(worksheet, 0, col, headers[col].c_str(), bold);
  }

  for (std::size_t row{0}; row < rows.size(); ++row) {
    for (std::size_t col{0}; col < rows.at(row).size(); ++col) {
      const auto& cell = rows.at(row).at(col);

      std::visit([worksheet, row, col]<typename T0>(const T0& value) {
        using T = std::decay_t<T0>;

        if constexpr (std::is_same_v<T, int>) {
          worksheet_write_number(worksheet, row + 1, col, static_cast<double>(value), nullptr);
        } else if constexpr (std::is_same_v<T, double>) {
          worksheet_write_number(worksheet, row + 1, col, value, nullptr);
        } else if constexpr (std::is_same_v<T, std::string>) {
          worksheet_write_string(worksheet, row + 1, col, value.c_str(), nullptr);
        }
      }, cell);
    }
  }

  workbook_close(workbook);
}

}
