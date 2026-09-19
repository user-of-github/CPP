#ifndef RECEIPT_SERVICE_CLASSIFICATOR_DTO_HPP
#define RECEIPT_SERVICE_CLASSIFICATOR_DTO_HPP

#include <string>
#include <nlohmann/json.hpp>

namespace expenses::classificators {
    struct PaymentMethodDto {
        int id{0};
        std::string name{};
        bool is_active{true};
    };

    struct CategoryDto {
        int id{0};
        std::string name{};
        std::string description{};
    };

    struct RetailChainDto {
        int id{0};
        std::string name{};
    };

    struct ConcreteShopDto {
        int id{0};
        int retail_chain_id {0};
        std::string address{};
        bool is_active{true};
    };

    // automatically generates to_json function for (de)serialization
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PaymentMethodDto, id, name, is_active)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CategoryDto, id, name, description)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ConcreteShopDto, id, retail_chain_id, address, is_active)
}

#endif //RECEIPT_SERVICE_CLASSIFICATOR_DTO_HPP
