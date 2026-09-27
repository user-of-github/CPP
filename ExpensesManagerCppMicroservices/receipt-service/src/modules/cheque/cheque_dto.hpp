#ifndef RECEIPT_SERVICE_CHEQUE_DTO_HPP
#define RECEIPT_SERVICE_CHEQUE_DTO_HPP

#include <string>
#include <vector>
#include "../../common/exceptions.hpp"


namespace expenses::cheques {
  struct CreateChequeItemDto {
  int category_id;
  std::string product_name;
  double quantity;
  double unit_price;
  double total_price;
};

struct CreateChequeDto {
  int concrete_store_id;
  int payment_method_id;
  double total_amount;
  std::vector<CreateChequeItemDto> items;

  static CreateChequeDto parse(const Json::Value& json) {
    if (!json.isObject()) {
      throw common::exceptions::BadRequestException("Body must be a JSON object");
    }

    if (!json.isMember("concrete_store_id") || !json["concrete_store_id"].isInt()) {
      throw common::exceptions::BadRequestException("'concrete_store_id' must be an integer");
    }

    if (!json.isMember("payment_method_id") || !json["payment_method_id"].isInt()) {
      throw common::exceptions::BadRequestException("'payment_method_id' must be an integer");
    }

    if (!json.isMember("total_amount") || !json["total_amount"].isNumeric()) {
      throw common::exceptions::BadRequestException("'total_amount' must be a number");
    }

    if (!json.isMember("items") || !json["items"].isArray()) {
      throw common::exceptions::BadRequestException("'items' must be an array");
    }

    CreateChequeDto dto{
        .concrete_store_id = json["concrete_store_id"].asInt(),
        .payment_method_id = json["payment_method_id"].asInt(),
        .total_amount = json["total_amount"].asDouble(),
        .items = {},
    };

    for (const auto& value : json["items"]) {
      dto.items.push_back(parse_item(value));
    }

    dto.validate();
    return dto;
  }

 private:
  static CreateChequeItemDto parse_item(const Json::Value& json) {
    if (!json.isObject()) {
      throw common::exceptions::BadRequestException("Each item must be a JSON object");
    }

    if (!json.isMember("category_id") || !json["category_id"].isInt()) {
      throw common::exceptions::BadRequestException("'items.category_id' must be an integer");
    }

    if (!json.isMember("product_name") || !json["product_name"].isString()) {
      throw common::exceptions::BadRequestException("'items.product_name' must be a string");
    }

    if (!json.isMember("quantity") || !json["quantity"].isNumeric()) {
      throw common::exceptions::BadRequestException("'items.quantity' must be a number");
    }

    if (!json.isMember("unit_price") || !json["unit_price"].isNumeric()) {
      throw common::exceptions::BadRequestException("'items.unit_price' must be a number");
    }

    if (!json.isMember("total_price") || !json["total_price"].isNumeric()) {
      throw common::exceptions::BadRequestException("'items.total_price' must be a number");
    }

    return CreateChequeItemDto{
        .category_id = json["category_id"].asInt(),
        .product_name = json["product_name"].asString(),
        .quantity = json["quantity"].asDouble(),
        .unit_price = json["unit_price"].asDouble(),
        .total_price = json["total_price"].asDouble(),
    };
  }

  void validate() const {
    if (concrete_store_id <= 0) {
      throw common::exceptions::BadRequestException("'concrete_store_id' must be positive");
    }

    if (payment_method_id <= 0) {
      throw common::exceptions::BadRequestException("'payment_method_id' must be positive");
    }

    if (total_amount < 0) {
      throw common::exceptions::BadRequestException("'total_amount' must be non-negative");
    }

    if (items.empty()) {
      throw common::exceptions::BadRequestException("'items' must contain at least one item");
    }

    for (const auto& item : items) {
      if (item.product_name.empty()) {
        throw common::exceptions::BadRequestException("'items.product_name' must not be empty");
      }

      if (item.quantity <= 0) {
        throw common::exceptions::BadRequestException("'items.quantity' must be positive");
      }

      if (item.unit_price < 0 || item.total_price < 0) {
        throw common::exceptions::BadRequestException("'items.unit_price' and 'items.total_price' must be non-negative");
      }
    }
  }
};
}

#endif //RECEIPT_SERVICE_CHEQUE_DTO_HPP
