#ifndef LINEARALGEBRA_MATRIX_H
#define LINEARALGEBRA_MATRIX_H

#pragma once

#include <ostream>
#include "./Vector/vector.h"
#include "./Vector/vector.cpp"
#include <tuple>


namespace LinearAlgebra
{
    template<typename ValueType>
    class Matrix
    {
    public:
        Matrix(const std::size_t, const std::size_t, const ValueType = 0);

        template<typename ValueType2>
        friend std::ostream &operator<<(std::ostream &, const Matrix<ValueType2> &);

        Vector<ValueType> &operator[](const size_t);

        const Vector<ValueType> &operator[](const std::size_t) const;

        const std::tuple<std::size_t, std::size_t> Sizes() const;

        ValueType Sum() const;

        void Resize(const std::size_t, const std::size_t);

    private:
        std::vector<Vector<ValueType>> vectors_;

        void PrintVectorsRowForOstream(std::ostream &, const std::size_t) const;

        static void CheckMatricesCompatibility(const Matrix<ValueType> &, const Matrix<ValueType> &);

        static bool CheckValidityOfDimensions(const std::size_t, const std::size_t);
    };
}
#endif //LINEARALGEBRA_MATRIX_H
