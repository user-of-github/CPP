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


        Vector();

        explicit Vector(const std::size_t, const ValueType = 0);

        Vector(const std::initializer_list<ValueType> &);

        Vector(const std::vector<ValueType> &);

        Vector(const ValueType *, const std::size_t);

        Vector(const Vector<ValueType> &);


        constexpr std::size_t Size() const;

        constexpr ValueType GetNorm() const;

        constexpr ValueType Sum() const;

        void Normalize();

        void Resize(const std::size_t, const ValueType fill_with_ = 0);


        const ValueType operator[](const std::size_t) const;

        ValueType &operator[](const std::size_t);

        Vector<ValueType> &operator+=(const ValueType &);

        Vector<ValueType> &operator-=(const ValueType &);

        Vector<ValueType> &operator*=(const ValueType &);

        Vector<ValueType> &operator/=(const ValueType &);

        Vector<ValueType> operator+(const ValueType &) const;

        Vector<ValueType> operator-(const ValueType &) const;

        Vector<ValueType> operator*(const ValueType &) const;

        Vector<ValueType> operator/(const ValueType &) const;

        Vector<ValueType> &operator+=(const Vector<ValueType> &);

        Vector<ValueType> &operator-=(const Vector<ValueType> &);

        Vector<ValueType> operator+(const Vector<ValueType> &) const;

        Vector<ValueType> operator-(const Vector<ValueType> &) const;

        Vector<ValueType> &operator=(const Vector<ValueType> &);

        Vector<ValueType> &operator=(Vector<ValueType> &&) noexcept = default;

        template<typename ValueType1>
        friend bool operator==(const Vector<ValueType1> &, const Vector<ValueType1> &);

        template<typename ValueType1>
        friend std::ostream &operator<<(std::ostream &, const Vector<ValueType1> &);

    private:
        std::vector<ValueType> values_;

        void CopyFullStdVector(const std::vector<ValueType> &);

        static bool CheckSizesCompatibility(const std::vector<ValueType> &,
                                            const std::vector<ValueType> &,
                                            const bool = true);

        static void CheckValidityOfSize(const std::size_t);

        void CheckIndexCompatibility(const std::size_t) const;

        void PrintVectorRowByStream(std::ostream &) const;
    };
}

#endif //LINEARALGEBRA_VECTOR_H