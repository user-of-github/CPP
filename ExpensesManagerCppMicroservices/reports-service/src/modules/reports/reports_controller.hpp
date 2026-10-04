#ifndef REPORTS_SERVICE_REPORTS_CONTROLLER_HPP
#define REPORTS_SERVICE_REPORTS_CONTROLLER_HPP

#include <utility>
#include <string>
#include <vector>
#include <variant>
#include <fstream>
#include <filesystem>
#include <crow.h>
#include <memory>
#include "./reports_repository.hpp"
#include "./excel_generator.hpp"

namespace reports {
  class ReportController {
  public:
    explicit ReportController(std::shared_ptr<ReportRepository> repo);

    void register_routes(crow::SimpleApp& app);

  private:
    void handle_generate(const crow::request& req, crow::response& res, const int report_id) const;

    std::shared_ptr<ReportRepository> repo_;
  };

}  // namespace reports

#endif //REPORTS_SERVICE_REPORTS_CONTROLLER_HPP
