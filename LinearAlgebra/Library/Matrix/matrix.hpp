#ifndef LINEARALGEBRA_MATRIX_H
#define LINEARALGEBRA_MATRIX_H

#pragma once

#include <ostream>
#include "./Vector/vector.hpp"
#include "./Vector/vector.cpp"
#include <tuple>


namespace LinearAlgebra
{
    template<typename ValueType>
    class Matrix
    {
    public:
        Matrix(const std::size_t, const std::size_t, const ValueType = 0);

        Matrix(const ValueType **, const std::size_t, const std::size_t);

        Matrix(const ValueType *, const std::size_t, const std::size_t);

        Matrix(const Vector<ValueType> &);

        Matrix(const Matrix<ValueType> &);

        template<typename ValueType2>
        friend std::ostream &operator<<(std::ostream &, const Matrix<ValueType2> &);

        Vector<ValueType> &operator[](const size_t);

        const Vector<ValueType> &operator[](const std::size_t) const;

        const std::tuple<std::size_t, std::size_t> Sizes() const;

        ValueType Sum() const;

        void Resize(const std::size_t, const std::size_t, const ValueType = ValueType());

        Matrix<ValueType> &operator*=(const ValueType);

        Matrix<ValueType> &operator/=(const ValueType);

        Matrix<ValueType> operator*(const ValueType) const;

        Matrix<ValueType> operator+(const Matrix<ValueType> &) const;

        Matrix<ValueType> operator-(const Matrix<ValueType> &) const;

        template<typename ValueType1>
        friend bool operator==(const Matrix<ValueType1> &, const Matrix<ValueType1> &);

        Matrix<ValueType> &operator=(Matrix<ValueType> &&) noexcept = default;

        Matrix<ValueType> &operator=(const Matrix<ValueType> &);

        void Transpose();

    private:
        std::vector<Vector<ValueType>> vectors_;

        void CopyItems(const Matrix<ValueType> &);

        void PrintVectorsRowForOstream(std::ostream &, const std::size_t) const;

        static bool CheckMatricesCompatibility(const Matrix<ValueType> &, const Matrix<ValueType> &, const bool = true);

        static bool CheckMatrixsSquareness(const Matrix<ValueType> &, const bool = true);

        static void CheckValidityOfDimensions(const std::size_t, const std::size_t);
    };
}
#endif //LINEARALGEBRA_MATRIX_H
