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

    template<typename ValueType>
    Vector<ValueType>::Vector(const Vector<ValueType> &rhs)
    {
        this->CopyFullStdVector(rhs);
    }

    template<typename ValueType>
    void Vector<ValueType>::CopyFullStdVector(const std::vector<ValueType> &rhs)
    {
        this->values_.resize(0);
        this->values_.shrink_to_fit();
        for (const auto &item : rhs)
            this->values_.push_back(item);
    }

    template<typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator*=(const ValueType &scalar)
    {
        for (auto &item : this->values_)
            item *= scalar;
        return *this;
    }

    template<typename ValueType>
    Vector<ValueType> Vector<ValueType>::operator*(const ValueType &scalar) const
    {
        Vector<ValueType> response(*this);
        for (std::size_t counter = 0; counter < response.Size(); ++counter)
            response[counter] *= scalar;
        return response;
    }

    template<typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator+=(const ValueType &scalar)
    {
        for (auto &item : this->values_)
            item += scalar;
        return *this;
    }

    template<typename ValueType>
    Vector<ValueType> Vector<ValueType>::operator+(const ValueType &scalar) const
    {
        Vector<ValueType> response(*this);
        for (auto &item : response)
            item += scalar;
        return response;
    }

    template<typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator-=(const ValueType &scalar)
    {
        for (auto &item : this->values_)
            item -= scalar;
        return *this;
    }

    template<typename ValueType>
    Vector<ValueType> Vector<ValueType>::operator-(const ValueType &scalar) const
    {
        Vector<ValueType> response(*this);
        for (auto &item : response)
            item -= scalar;
        return response;
    }

    template<typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator/=(const ValueType &scalar)
    {
        for (auto &item : this->values_)
            item /= scalar;
        return *this;
    }

    template<typename ValueType>
    Vector<ValueType> Vector<ValueType>::operator/(const ValueType &scalar) const
    {
        Vector<ValueType> response(*this);
        for (auto &item : response)
            item /= scalar;
        return response;
    }

    template<typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator+=(const Vector<ValueType> &scalar)
    {
        if (scalar.Size() != this->Size())
            throw std::runtime_error("Vectors' sizes aren't equal");

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            this->values_.at(counter) += scalar[counter];

        return *this;
    }

    template<typename ValueType>
    Vector<ValueType> Vector<ValueType>::operator+(const Vector<ValueType> &scalar)
    {
        Vector<ValueType> response(*this);

        if (scalar.Size() != this->Size())
            throw std::runtime_error("Vectors' sizes aren't equal");

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            response[counter] += scalar[counter];

        return response;
    }

    template<typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator-=(const Vector<ValueType> &scalar)
    {
        if (scalar.Size() != this->Size())
            throw std::runtime_error("Vectors' sizes aren't equal");

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            this->values_.at(counter) -= scalar[counter];

        return *this;
    }

    template<typename ValueType>
    Vector<ValueType> Vector<ValueType>::operator-(const Vector<ValueType> &scalar)
    {
        auto response = Vector<ValueType>(*this);

        if (scalar.Size() != this->Size())
            throw std::runtime_error("Vectors' sizes aren't equal");

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            response[counter] -= scalar[counter];

        return response;
    }
}
