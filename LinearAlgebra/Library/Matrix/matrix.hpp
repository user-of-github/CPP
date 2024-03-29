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
    class EquationSystemSolver;

    template<typename ValueType>
    class Matrix
    {
    public:
        friend class Vector<ValueType>;

        friend class EquationSystemSolver;


        Matrix() = delete;

        Matrix(const std::size_t, const std::size_t, const ValueType = 0);

        Matrix(const ValueType **, const std::size_t, const std::size_t);

        Matrix(const ValueType *, const std::size_t, const std::size_t);

        Matrix(const Vector<ValueType> &);

        Matrix(const Matrix<ValueType> &);


        ValueType Sum() const;

        std::tuple<std::size_t, std::size_t> Sizes() const;

        void Transpose();

        void Resize(const std::size_t, const std::size_t, const ValueType = ValueType());

        std::size_t Triangulate();

        Matrix<ValueType> Pow(const std::size_t);

        double Determinant() const;

        double Minor(const std::size_t, const std::size_t) const;

        double Cofactor(const std::size_t, const std::size_t) const;

        static Matrix<ValueType> IdentityMatrix(const std::size_t);

        static Matrix<ValueType> RandomizedMatrix(const std::size_t, const std::size_t, const int = 0, const int = 100);

        bool IsSymmetric() const;

        ValueType Track() const;

        std::size_t Rank() const;

        Matrix<ValueType> GetSubmatrixWithoutRowAndColumn(const std::size_t, const std::size_t) const;

        Matrix<ValueType> GetInverseMatrix() const;


        Vector<ValueType> &operator[](const size_t);

        const Vector<ValueType> &operator[](const std::size_t) const;

        Matrix<ValueType> &operator+=(const ValueType);

        Matrix<ValueType> &operator-=(const ValueType);

        Matrix<ValueType> &operator*=(const ValueType);

        Matrix<ValueType> &operator/=(const ValueType);

        Matrix<ValueType> operator*(const ValueType) const;

        Matrix<ValueType> operator+(const Matrix<ValueType> &) const;

        Matrix<ValueType> operator-(const Matrix<ValueType> &) const;

        Matrix<ValueType> operator*(const Matrix<ValueType> &) const;

        Matrix<ValueType> &operator=(Matrix<ValueType> &&) noexcept = default;

        Matrix<ValueType> &operator=(const Matrix<ValueType> &);

        Matrix<ValueType> &operator=(const Vector<ValueType> &);

        template<typename ValueType1>
        friend bool operator==(const Matrix<ValueType1> &, const Matrix<ValueType1> &);

        template<typename ValueType2>
        friend std::ostream &operator<<(std::ostream &, const Matrix<ValueType2> &);

    private:
        std::vector<Vector<ValueType>> vectors_;


        void CopyItems(const Matrix<ValueType> &);

        void PrintVectorsRowForOstream(std::ostream &, const std::size_t) const;

        static bool CheckMatricesCompatibility(const Matrix<ValueType> &,
                                                         const Matrix<ValueType> &,
                                                         const bool = true);

        static bool IsMatrixSquare(const Matrix<ValueType> &, const bool = true);

        static void CheckValidityOfDimensions(const std::size_t, const std::size_t);

        static std::size_t Gauss(double **, const std::size_t, const std::size_t);

        double **GetSimilarMatrixOfDouble() const;

        void FreeTemporaryMatrix(double **) const;

        constexpr void CheckGenericType() const;

        bool CheckValidityOfIndexes(const std::size_t, const std::size_t, const bool = true) const;

        static Matrix<ValueType> CreateColMatrixFromVector(const Vector<ValueType> &);
    };
}
#endif //LINEARALGEBRA_MATRIX_H
