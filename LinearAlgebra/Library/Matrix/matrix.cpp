#include "matrix.hpp"


namespace LinearAlgebra
{
    template<typename ValueType>
    Matrix<ValueType>::Matrix(const std::size_t rows, const std::size_t cols, const ValueType default_value):
            vectors_(rows, Vector<ValueType>(cols, default_value))
    {}

    template<typename ValueType2>
    std::ostream &operator<<(std::ostream &stream, const Matrix <ValueType2> &to_print)
    {
        stream << "Matrix (" << to_print.vectors_.size() << " x " << to_print.vectors_.at(1).Size() << "):\n";

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
    Vector <ValueType> &Matrix<ValueType>::operator[](const std::size_t index)
    {
        return this->vectors_.at(index);
    }

    template<typename ValueType>
    const Vector <ValueType> &Matrix<ValueType>::operator[](const std::size_t index) const
    {
        return this->vectors_.at(index);
    }

    template<typename ValueType>
    void Matrix<ValueType>::CheckMatricesCompatibility(const Matrix <ValueType> &first,
                                                       const Matrix <ValueType> &second)
    {
        if (first.vectors_.size() != second.vectors_.size() ||
            first.vectors_.at(0).values_.size() != second.vectors_.at(0).values_.size())
            throw std::runtime_error("Matrices' sizes incompatible");
    }

    template<typename ValueType>
    const std::tuple<std::size_t, std::size_t> Matrix<ValueType>::Sizes() const
    {
        return std::tuple<std::size_t, std::size_t>(this->vectors_.size(), this->vectors_.at(0).values_.size());
    }

    template<typename ValueType>
    ValueType Matrix<ValueType>::Sum() const
    {
        return std::accumulate(
                std::begin(this->vectors_),
                std::end(this->vectors_),
                0,
                [](ValueType response, const Vector<ValueType> &current) -> ValueType {
                    return response + current.Sum();
                });
    }

    template<typename ValueType>
    void Matrix<ValueType>::Resize(const std::size_t new_rows, const std::size_t new_cols)
    {
        Matrix<ValueType>::CheckValidityOfDimensions(new_rows, new_cols);
        this->vectors_.resize(new_rows, Vector<ValueType>(new_cols, 0));
        for (auto &row : this->vectors_)
            row.Resize(new_cols, 0);
    }

    template<typename ValueType>
    void Matrix<ValueType>::CheckValidityOfDimensions(const std::size_t rows_count, const std::size_t cols_count)
    {
        if (rows_count <= 0 || cols_count <= 0)
            throw std::runtime_error("Sizes are invalid");
    }
}