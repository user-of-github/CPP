#pragma once

#include "vector.h"


namespace LinearAlgebra
{
    template<typename ValueType>
    Vector<ValueType>::Vector(const std::size_t size, const ValueType default_value): values_(size, default_value)
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
    const ValueType Vector<ValueType>::operator[](const std::size_t index) const
    {
        return this->values_.at(index);
    }

    template<typename ValueType>
    ValueType &Vector<ValueType>::operator[](const std::size_t index)
    {
        return this->values_.at(index);
    }

    template<typename ValueType>
    Vector<ValueType>::Vector(const Vector<ValueType> &rhs)
    {
        this->CopyFullStdVector(rhs.values_);
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
        Vector <ValueType> response(*this);
        for (auto &item : response.values_)
            item *= scalar;
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
        Vector <ValueType> response(*this);
        for (auto &item : response.values_)
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
        Vector <ValueType> response(*this);
        for (auto &item : response.values_)
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
    const Vector<int> Vector<ValueType>::operator/(const ValueType &scalar)
    {
        Vector <ValueType> response(*this);
        for (auto &item : response.values_)
            item /= scalar;
        return response;
    }

    template<typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator+=(const Vector<ValueType> &scalar)
    {
        Vector<ValueType>::CheckSizesCompatibility(this->values_, scalar.values_);

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            this->values_.at(counter) += scalar.values_.at(counter);

        return *this;
    }

    template<typename ValueType>
    Vector<ValueType> Vector<ValueType>::operator+(const Vector<ValueType> &scalar)
    {
        Vector<ValueType>::CheckSizesCompatibility(this->values_, scalar.values_);

        Vector <ValueType> response(*this);

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            response.values_.at(counter) += scalar.values_.at(counter);

        return response;
    }

    template<typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator-=(const Vector<ValueType> &scalar)
    {
        Vector<ValueType>::CheckSizesCompatibility(this->values_, scalar.values_);

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            this->values_.at(counter) -= scalar.values_.at(counter);

        return *this;
    }

    template<typename ValueType>
    Vector<ValueType> Vector<ValueType>::operator-(const Vector<ValueType> &scalar)
    {
        Vector<ValueType>::CheckSizesCompatibility(this->values_, scalar.values_);

        auto response = Vector<ValueType>(*this);

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            response.values_.at(counter) -= scalar.values_.at(counter);

        return response;
    }

    template<typename ValueType>
    void Vector<ValueType>::CheckSizesCompatibility(const std::vector<ValueType> &first,
                                                    const std::vector<ValueType> &second)
    {
        if (first.size() != second.size())
            throw std::runtime_error("Runtime Error: Vectors' sizes incompatible");
    }

    template<typename ValueType>
    Vector<ValueType> &Vector<ValueType>::operator=(const Vector<ValueType> &rhs)
    {
        Vector<ValueType>::CopyFullStdVector(rhs.values_);
        return *this;
    }

    template<typename ValueType>
    bool Vector<ValueType>::operator==(const Vector<ValueType> &rhs) const
    {
        Vector<ValueType>::CheckSizesCompatibility(this->values_, rhs.values_);
        for (std::size_t counter = 0; counter < this->values_.size(); ++counter)
            if (this->values_.at(counter) != rhs.values_.at(counter))
                return false;
        return true;
    }

    template<typename ValueType1>
    std::ostream &operator<<(std::ostream &stream, const Vector<ValueType1> &obj)
    {
        stream << "Vector (" << obj.Size() << "): [ ";
        obj.PrintVectorRowByStream(stream);
        stream << ' ' << ']' << '\n';
        return stream;
    }

    template<typename ValueType>
    ValueType Vector<ValueType>::Sum() const
    {
        return std::accumulate(
                std::begin(this->values_),
                std::end(this->values_),
                ValueType()
        );
    }

    /*template<typename ValueType>
    template<typename Functor>
    void Vector<ValueType>::Transform(Functor &changer)
    {
        for (std::size_t counter = 0; const auto &item : this->values_)
            changer(item, counter++);
    }*/
    template<typename ValueType>
    void Vector<ValueType>::PrintVectorRowByStream(std::ostream &os) const
    {
        for (const auto &item : this->values_)
            os << item << ' ';
    }
}
