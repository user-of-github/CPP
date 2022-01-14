#include "matrix.h"


namespace LinearAlgebra
{
    template<typename ValueType>
    Matrix<ValueType>::Matrix(const std::size_t rows, const std::size_t cols, const ValueType default_value):
            vectors_(rows, Vector<ValueType>(cols, default_value))
    {}

    template<typename ValueType2>
    std::ostream &operator<<(std::ostream &stream, const Matrix<ValueType2> &to_print)
    {
        stream << "Matrix (" << to_print.vectors_.size() << " x " << to_print.vectors_.at(1).Size() << ')' << ':'
               << '\n';

        for (std::size_t counter = 0; counter < to_print.vectors_.size(); ++counter)
        {
            stream << '\t';
            to_print.PrintVectorsRowForOstream(stream, counter);
            stream << '\n';
        }

        return stream;
    }

    template<typename ValueType>
    void Matrix<ValueType>::PrintVectorsRowForOstream(std::ostream &stream, const std::size_t index) const
    {
        this->vectors_.at(index).PrintVectorRowByStream(stream);
    }

    template<typename ValueType>
    Vector<ValueType> &Matrix<ValueType>::operator[](const std::size_t index)
    {
        return this->vectors_.at(index);
    }

    template<typename ValueType>
    const Vector<ValueType> &Matrix<ValueType>::operator[](const std::size_t index) const
    {
        return this->vectors_.at(index);
    }
}