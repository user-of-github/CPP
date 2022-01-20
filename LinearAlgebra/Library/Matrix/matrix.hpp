#ifndef LINEARALGEBRA_MATRIX_H
#define LINEARALGEBRA_MATRIX_H

#pragma once

#include <ostream>
#include "./Vector/vector.hpp"
#include "./Vector/vector.cpp"
#include <tuple>
#include "../Utils/utils.hpp"
#include "../Utils/utils.cpp"


namespace LinearAlgebra
{
    template<typename ValueType>
    class Matrix
    {
    public:
        Matrix() = delete;

        Matrix(const std::size_t, const std::size_t, const ValueType = 0);

        Matrix(const ValueType **, const std::size_t, const std::size_t);

        Matrix(const ValueType *, const std::size_t, const std::size_t);

        Matrix(const Vector<ValueType> &);

        Matrix(const Matrix<ValueType> &);


        constexpr ValueType Sum() const;

        constexpr std::tuple<std::size_t, std::size_t> Sizes() const;

        void Transpose();

        void Resize(const std::size_t, const std::size_t, const ValueType = ValueType());

        constexpr std::size_t Triangulate();

        constexpr double Determinant() const;


        Vector<ValueType> &operator[](const size_t);

        const Vector<ValueType> &operator[](const std::size_t) const;

        Matrix<ValueType> &operator+=(const ValueType);

        Matrix<ValueType> &operator-=(const ValueType);

        Matrix<ValueType> &operator*=(const ValueType);

        Matrix<ValueType> &operator/=(const ValueType);

        Matrix<ValueType> operator*(const ValueType) const;

        Matrix<ValueType> operator+(const Matrix<ValueType> &) const;

        Matrix<ValueType> operator-(const Matrix<ValueType> &) const;

        Matrix<ValueType> &operator=(Matrix<ValueType> &&) noexcept = default;

        Matrix<ValueType> &operator=(const Matrix<ValueType> &);

        template<typename ValueType1>
        friend bool operator==(const Matrix<ValueType1> &, const Matrix<ValueType1> &);

        template<typename ValueType2>
        friend std::ostream &operator<<(std::ostream &, const Matrix<ValueType2> &);

    private:
        std::vector<Vector<ValueType>> vectors_;

        void CopyItems(const Matrix<ValueType> &);

        void PrintVectorsRowForOstream(std::ostream &, const std::size_t) const;

        static constexpr bool CheckMatricesCompatibility(const Matrix<ValueType> &,
                                                         const Matrix<ValueType> &,
                                                         const bool = true);

        static constexpr bool IsMatrixSquare(const Matrix<ValueType> &, const bool = true);

        static void CheckValidityOfDimensions(const std::size_t, const std::size_t);

        static constexpr std::size_t Gauss(double **, const std::size_t, const std::size_t);

        double **GetSimilarMatrixOfDouble() const;

        void FreeTemporaryMatrix(double **) const;
    };
}
#endif //LINEARALGEBRA_MATRIX_H
