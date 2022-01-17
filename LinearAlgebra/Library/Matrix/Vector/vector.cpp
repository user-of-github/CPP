#include "vector.hpp"

namespace LinearAlgebra
{
    template<typename ValueType>
    Vector<ValueType>::Vector(): values_(0)
    {}

    template<typename ValueType>
    Vector<ValueType>::Vector(const std::size_t size, const ValueType default_value): values_(0)
    {
        Vector<ValueType>::CheckValidityOfSize(size);
        this->values_.resize(size, default_value);
    }

    template<typename ValueType>
    Vector<ValueType>::Vector(const std::initializer_list<ValueType> &initial_values): values_(0)
    {
        Vector<ValueType>::CheckValidityOfSize(initial_values.size());
        for (const auto item : initial_values)
            this->values_.push_back(item);
    }

    template<typename ValueType>
    Vector<ValueType>::Vector(const std::vector<ValueType> &initial_values)
    {
        Vector<ValueType>::CheckValidityOfSize(initial_values.size());
        for (const auto item : initial_values)
            this->values_.push_back(item);
    }

    template<typename ValueType>
    Vector<ValueType>::Vector(const ValueType *initial_values, const std::size_t size):values_(0)
    {
        Vector<ValueType>::CheckValidityOfSize(size);
        for (std::size_t counter = 0; counter < size; ++counter)
            this->values_.push_back(initial_values[counter]);
    }

    template<typename ValueType>
    Vector<ValueType>::Vector(const Vector <ValueType> &rhs)
    {
        this->CopyFullStdVector(rhs.values_);
    }


    template<typename ValueType>
    constexpr std::size_t Vector<ValueType>::Size() const
    {
        return this->values_.size();
    }

    template<typename ValueType>
    constexpr ValueType Vector<ValueType>::GetNorm() const
    {
        ValueType response{};
        for (const auto &item : this->values_)
            response += item * item;
        return sqrt(response);
    }

    template<typename ValueType>
    constexpr ValueType Vector<ValueType>::Sum() const
    {
        return std::accumulate(
                std::begin(this->values_),
                std::end(this->values_),
                ValueType()
        );
    }

    template<typename ValueType>
    void Vector<ValueType>::Normalize()
    {
        const auto norm = this->GetNorm();
        if (norm == 0)
            throw std::runtime_error("Can't normalize vector. Attempted to divide by Zero");

        for (auto &item : this->values_)
            item /= norm;
    }

    template<typename ValueType>
    void Vector<ValueType>::Resize(const std::size_t new_size, const ValueType fill_with)
    {
        Vector<ValueType>::CheckValidityOfSize(new_size);
        this->values_.resize(new_size, fill_with);
    }


    template<typename ValueType>
    const ValueType Vector<ValueType>::operator[](const std::size_t index) const
    {
        this->CheckIndexCompatibility(index);
        return this->values_.at(index);
    }

    template<typename ValueType>
    ValueType &Vector<ValueType>::operator[](const std::size_t index)
    {
        this->CheckIndexCompatibility(index);
        return this->values_.at(index);
    }

    template<typename ValueType>
    Vector <ValueType> &Vector<ValueType>::operator+=(const ValueType &scalar)
    {
        for (auto &item : this->values_)
            item += scalar;
        return *this;
    }

    template<typename ValueType>
    Vector <ValueType> &Vector<ValueType>::operator-=(const ValueType &scalar)
    {
        for (auto &item : this->values_)
            item -= scalar;
        return *this;
    }

    template<typename ValueType>
    Vector <ValueType> &Vector<ValueType>::operator*=(const ValueType &scalar)
    {
        for (auto &item : this->values_)
            item *= scalar;
        return *this;
    }

    template<typename ValueType>
    Vector <ValueType> &Vector<ValueType>::operator/=(const ValueType &scalar)
    {
        if (scalar == 0)
        {
            throw std::invalid_argument("Division by zero is not allowed");
            return *this;
        }

        for (auto &item : this->values_)
            item /= scalar;
        return *this;
    }

    template<typename ValueType>
    Vector <ValueType> Vector<ValueType>::operator+(const ValueType &scalar) const
    {
        Vector<ValueType> response(*this);
        for (auto &item : response.values_)
            item += scalar;
        return response;
    }

    template<typename ValueType>
    Vector <ValueType> Vector<ValueType>::operator-(const ValueType &scalar) const
    {
        Vector<ValueType> response(*this);
        for (auto &item : response.values_)
            item -= scalar;
        return response;
    }

    template<typename ValueType>
    Vector <ValueType> Vector<ValueType>::operator*(const ValueType &scalar) const
    {
        Vector<ValueType> response(*this);
        for (auto &item : response.values_)
            item *= scalar;
        return response;
    }

    template<typename ValueType>
    Vector <ValueType> Vector<ValueType>::operator/(const ValueType &scalar) const
    {
        if (scalar == 0)
            throw std::invalid_argument("Division by zero is not allowed");

        Vector<ValueType> response(*this);
        for (auto &item : response.values_)
            item /= scalar;
        return response;
    }

    template<typename ValueType>
    Vector <ValueType> &Vector<ValueType>::operator+=(const Vector <ValueType> &scalar)
    {
        Vector<ValueType>::CheckSizesCompatibility(this->values_, scalar.values_);

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            this->values_.at(counter) += scalar.values_.at(counter);

        return *this;
    }

    template<typename ValueType>
    Vector <ValueType> &Vector<ValueType>::operator-=(const Vector <ValueType> &scalar)
    {
        Vector<ValueType>::CheckSizesCompatibility(this->values_, scalar.values_);

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            this->values_.at(counter) -= scalar.values_.at(counter);

        return *this;
    }

    template<typename ValueType>
    Vector <ValueType> Vector<ValueType>::operator+(const Vector <ValueType> &scalar) const
    {
        Vector<ValueType>::CheckSizesCompatibility(this->values_, scalar.values_);

        Vector<ValueType> response(*this);

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            response.values_.at(counter) += scalar.values_.at(counter);

        return response;
    }

    template<typename ValueType>
    Vector <ValueType> Vector<ValueType>::operator-(const Vector <ValueType> &scalar) const
    {
        Vector<ValueType>::CheckSizesCompatibility(this->values_, scalar.values_);

        auto response = Vector<ValueType>(*this);

        for (std::size_t counter = 0; counter < this->Size(); ++counter)
            response.values_.at(counter) -= scalar.values_.at(counter);

        return response;
    }

    template<typename ValueType>
    Vector <ValueType> &Vector<ValueType>::operator=(const Vector <ValueType> &rhs)
    {
        this->CopyFullStdVector(rhs.values_);
        return *this;
    }

    template<typename ValueType1>
    bool operator==(const Vector <ValueType1> &first, const Vector <ValueType1> &second)
    {
        if (!Vector<ValueType1>::CheckSizesCompatibility(first.values_, second.values_, false))
            return false;

        for (std::size_t counter = 0; counter < first.values_.size(); ++counter)
            if (first.values_.at(counter) != second.values_.at(counter))
                return false;
        return true;
    }

    template<typename ValueType1>
    std::ostream &operator<<(std::ostream &stream, const Vector <ValueType1> &obj)
    {
        stream << "Vector (" << obj.Size() << "): [ ";
        obj.PrintVectorRowByStream(stream);
        stream << ']' << '\n';
        return stream;
    }


    template<typename ValueType>
    void Vector<ValueType>::CopyFullStdVector(const std::vector<ValueType> &rhs)
    {
        this->values_.resize(rhs.size());
        this->values_.shrink_to_fit();
        for (std::size_t counter = 0; const auto &item : rhs)
            this->values_.at(counter++) = item;
    }

    template<typename ValueType>
    bool Vector<ValueType>::CheckSizesCompatibility(const std::vector<ValueType> &first,
                                                    const std::vector<ValueType> &second,
                                                    const bool to_throw_exception)
    {
        if (first.size() != second.size())
        {
            if (to_throw_exception)
                throw std::runtime_error("Vectors' sizes incompatible");
            return false;
        }
        return true;
    }

    template<typename ValueType>
    void Vector<ValueType>::CheckValidityOfSize(const std::size_t size)
    {
        if ((int) size <= 0)
            throw std::invalid_argument("Size is invalid");
    }

    template<typename ValueType>
    void Vector<ValueType>::CheckIndexCompatibility(const std::size_t index) const
    {
        if (index >= this->values_.size() || index < 0)
            throw std::invalid_argument("Index is less than zero or greater than vector's size");
    }

    template<typename ValueType>
    void Vector<ValueType>::PrintVectorRowByStream(std::ostream &os) const
    {
        for (const auto &item : this->values_)
            os << item << ' ';
    }
}
