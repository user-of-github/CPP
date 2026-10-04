#include "./reports_controller.hpp"

namespace reports {
  ReportController::ReportController(std::shared_ptr<ReportRepository> repo) : repo_{std::move(repo)} {}

  void ReportController::register_routes(crow::SimpleApp &app) {
    CROW_ROUTE(app, "/generate/<int>")
    ([this](const crow::request &req, crow::response &res, const int report_id) {
      this->handle_generate(req, res, report_id);
    });
  }

  void ReportController::handle_generate(const crow::request &req, crow::response &res, const int report_id) const {
    try {
      const auto procedure_name{repo_->find_procedure_name_by_id(report_id)};

      if (!procedure_name) {
        res.code = 404;
        res.set_header("Content-Type", "application/json");
        res.write("{\"error\": \"Report with id " + std::to_string(report_id) + " not found\"}");
        res.end();
        return;
      }

      const auto [headers, rows]{repo_->execute_procedure(*procedure_name)};

      const std::string filepath{"/tmp/report_" + std::to_string(report_id) + ".xlsx"};
      ExcelGenerator::build_sheet(filepath, headers, rows);

      std::ifstream file{filepath, std::ios::binary};
      if (!file) {
        res.code = 500;
        res.set_header("Content-Type", "application/json");
        res.write("{\"error\": \"Failed to read generated file\"}");
        res.end();
        return;
      }

      const std::string content{
        std::istreambuf_iterator(file),
        std::istreambuf_iterator<char>()
      };

      res.set_header("Content-Type","application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
      res.set_header("Content-Disposition","attachment; filename=\"report_" + std::to_string(report_id) + ".xlsx\"");
      res.write(content);
      res.end();

      std::filesystem::remove(filepath);
    } catch (const std::exception &e) {
      res.code = 500;
      res.set_header("Content-Type", "application/json");
      res.write(std::string{"{\"error\": \""} + e.what() + "\"}");
      res.end();
    }
  }
}
