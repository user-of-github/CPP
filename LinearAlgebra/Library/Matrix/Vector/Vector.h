#ifndef LINEARALGEBRA_VECTOR_H
#define LINEARALGEBRA_VECTOR_H

#pragma once

#include <iostream>
#include <vector>
#include <exception>
#include <cmath>
#include <stdexcept>
#include <numeric>
#include <functional>


namespace LinearAlgebra
{
    template<typename ValueType>
    class Matrix;


    template<typename ValueType>
    class Vector
    {
    public:
        friend class Matrix<ValueType>;

        explicit Vector(const std::size_t, const ValueType);

        Vector(const std::initializer_list<ValueType> &);

        Vector(const Vector<ValueType> &);

        constexpr std::size_t Size() const;

        void Resize(const std::size_t, const ValueType fill_with_ = 0);

        ValueType GetNorm() const;

        void Normalize();

        const ValueType operator[](const std::size_t) const;

        ValueType &operator[](const std::size_t);

        Vector<ValueType> &operator*=(const ValueType &);

        Vector<ValueType> operator*(const ValueType &) const;

        Vector<ValueType> &operator+=(const ValueType &);

        Vector<ValueType> operator+(const ValueType &) const;

        Vector<ValueType> &operator-=(const ValueType &);

        Vector<ValueType> operator-(const ValueType &) const;

        Vector<ValueType> &operator/=(const ValueType &);

        const Vector<int> operator/(const ValueType &);

        Vector<ValueType> &operator+=(const Vector<ValueType> &);

        Vector<ValueType> operator+(const Vector<ValueType> &);

        Vector<ValueType> &operator-=(const Vector<ValueType> &);

        Vector<ValueType> operator-(const Vector<ValueType> &);

        Vector<ValueType> &operator=(const Vector<ValueType> &);

        Vector<ValueType> &operator=(Vector<ValueType> &&) noexcept = default;

        bool operator==(const Vector<ValueType> &) const;

        template<typename ValueType1>
        friend std::ostream &operator<<(std::ostream &, const Vector<ValueType1> &);

        ValueType Sum() const;

        /*template<typename Functor>
        void Transform(Functor &);*/

    private:
        std::vector<ValueType> values_;

        void CopyFullStdVector(const std::vector<ValueType> &);

        static void CheckSizesCompatibility(const std::vector<ValueType> &, const std::vector<ValueType> &);

        void CheckIndexCompatibility(const std::size_t) const;

        void PrintVectorRowByStream(std::ostream &) const;
    };
}
#endif //LINEARALGEBRA_VECTOR_H
