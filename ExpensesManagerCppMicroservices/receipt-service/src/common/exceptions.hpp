#ifndef RECEIPT_SERVICE_EXCEPTIONS_HPP
#define RECEIPT_SERVICE_EXCEPTIONS_HPP

#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <drogon/drogon.h>
#include <json/value.h>

namespace expenses::common::exceptions {
  class HttpException : public std::runtime_error {
  public:
    HttpException(const drogon::HttpStatusCode status, std::string message, std::string error_name)
      : std::runtime_error(message), status_code_(status),
        message_(std::move(message)), error_name_(std::move(error_name)) {
    }

    drogon::HttpStatusCode status_code() const noexcept { return status_code_; }
    const std::string &message() const noexcept { return message_; }
    const std::string &error_name() const noexcept { return error_name_; }

  private:
    drogon::HttpStatusCode status_code_;
    std::string message_;
    std::string error_name_;
  };

  // 400 Bad Request
  class BadRequestException : public HttpException {
  public:
    explicit BadRequestException(std::string message = "Bad Request") : HttpException(
      drogon::k400BadRequest, std::move(message), "Bad Request") {
    }
  };

  // 401 Unauthorized
  class UnauthorizedException : public HttpException {
  public:
    explicit UnauthorizedException(std::string message = "Unauthorized") : HttpException(
      drogon::k401Unauthorized, std::move(message), "Unauthorized") {
    }
  };

  // 403 Forbidden
  class ForbiddenException : public HttpException {
  public:
    explicit ForbiddenException(std::string message = "Forbidden") : HttpException(
      drogon::k403Forbidden, std::move(message), "Forbidden") {
    }
  };

  // 404 Not Found
  class NotFoundException : public HttpException {
  public:
    explicit NotFoundException(std::string message = "Not Found") : HttpException(
      drogon::k404NotFound, std::move(message), "Not Found") {
    }
  };

  // 500 Internal Server Error
  class InternalServerErrorException : public HttpException {
  public:
    explicit InternalServerErrorException(std::string message = "Internal Server Error") : HttpException(
      drogon::k500InternalServerError, std::move(message), "Internal Server Error") {
    }
  };


  inline void set_up_custom_errors_handling() {
    drogon::app().setCustomErrorHandler([](const drogon::HttpStatusCode status, const drogon::HttpRequestPtr &) {
      Json::Value body;
      body["statusCode"] = static_cast<int>(status);
      body["error"] = drogon::statusCodeToString(status).data();

      if (const auto current_ex{std::current_exception()}) {
        try {
          std::rethrow_exception(current_ex);
        } catch (const HttpException &ex) {
          body["statusCode"] = static_cast<int>(ex.status_code());
          body["message"] = ex.message();
          body["error"] = ex.error_name();

          auto resp = drogon::HttpResponse::newHttpJsonResponse(body);
          resp->setStatusCode(ex.status_code());
          return resp;
        } catch (const std::exception &ex) {
          body["message"] = ex.what();
        }
      } else {
        body["message"] = drogon::statusCodeToString(status).data();
      }

      const auto resp {drogon::HttpResponse::newHttpJsonResponse(body)};
      resp->setStatusCode(status);
      return resp;
    });
  }
}

#endif //RECEIPT_SERVICE_EXCEPTIONS_HPP
