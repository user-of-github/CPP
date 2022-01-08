#include <cmath>
#include "Vector.h"

namespace LinearAlgebra
{
    template<typename ValueType>
    Vector<ValueType>::Vector(const std::size_t size, const ValueType default_value_): values_(size, default_value_)
    {}

    template<typename ValueType>
    Vector<ValueType>::Vector(const std::initializer_list<ValueType> &initial_values_): values_(initial_values_)
    {}

    template<typename ValueType>
    constexpr std::size_t Vector<ValueType>::Size() const
    {
        return this->values_.size();
    }

    template<typename ValueType>
    void Vector<ValueType>::Resize(const std::size_t new_size, const ValueType fill_with)
    {
        this->values_.resize(new_size, fill_with);
    }

    template<typename ValueType>
    ValueType Vector<ValueType>::GetNorm() const
    {
        ValueType response{};
        for (const auto &item : this->values_)
            response += item * item;
        return sqrt(response);
    }

    template<typename ValueType>
    void Vector<ValueType>::Normalize()
    {
        const auto norm = this->GetNorm();
        for (auto &item : this->values_)
            item /= norm;
    }

    template<typename ValueType>
    ValueType &Vector<ValueType>::operator[](const std::size_t index) const
    {
        return this->values_.at(index);
    }

    template<typename ValueType>
    ValueType &Vector<ValueType>::operator[](const std::size_t index)
    {
        return this->values_[index];
    }
}
