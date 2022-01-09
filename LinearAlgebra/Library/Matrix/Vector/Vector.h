#ifndef LINEARALGEBRA_VECTOR_H
#define LINEARALGEBRA_VECTOR_H

#pragma once


#include <vector>
#include <exception>
#include <cmath>
#include <stdexcept>


namespace LinearAlgebra
{
    template<typename ValueType>
    class Vector
    {
    public:
        explicit Vector(const std::size_t = 0, const ValueType = 0);

        Vector(const std::initializer_list<ValueType> &);

        Vector(const Vector<ValueType> &);

        constexpr std::size_t Size() const;

        void Resize(const std::size_t, const ValueType fill_with_ = 0);

        ValueType GetNorm() const;

        void Normalize();

        ValueType &operator[](const std::size_t) const;

        ValueType &operator[](const std::size_t);

        Vector<ValueType> &operator*=(const ValueType &);

        Vector<ValueType> operator*(const ValueType &) const;

        Vector<ValueType> &operator+=(const ValueType &);

        Vector<ValueType> operator+(const ValueType &) const;

        Vector<ValueType> &operator-=(const ValueType &);

        Vector<ValueType> operator-(const ValueType &) const;

        Vector<ValueType> &operator/=(const ValueType &);

        Vector<ValueType> operator/(const ValueType &) const;

        Vector<ValueType> &operator+=(const Vector<ValueType> &);

        Vector<ValueType> operator+(const Vector<ValueType> &);

        Vector<ValueType> &operator-=(const Vector<ValueType> &);

        Vector<ValueType> operator-(const Vector<ValueType> &);

    private:
        std::vector<ValueType> values_;

        void CopyFullStdVector(const std::vector<ValueType> &);
    };
}
#endif //LINEARALGEBRA_VECTOR_H
