#include "matrix.hpp"


namespace LinearAlgebra
{
    template<typename ValueType>
    Matrix<ValueType>::Matrix(const std::size_t rows, const std::size_t cols, const ValueType default_value)
    {
        Matrix<ValueType>::CheckValidityOfDimensions(rows, cols);
        this->vectors_.resize(rows, Vector<ValueType>(cols, default_value));
    }

    template<typename ValueType>
    Matrix<ValueType>::Matrix(const ValueType **array, std::size_t rows, const std::size_t cols):
            vectors_(rows, Vector<ValueType>(cols, ValueType()))
    {
        Matrix<ValueType>::CheckValidityOfDimensions(rows, cols);
        for (std::size_t row = 0; row < rows; ++row)
            for (std::size_t col = 0; col < cols; ++col)
                this->vectors_.at(row).values_.at(col) = array[row][col];
    }

    template<typename ValueType>
    Matrix<ValueType>::Matrix(const Vector <ValueType> &vector): vectors_(1, Vector<ValueType>(vector))
    {
        this->vectors_.at(0) = vector;
    }

    template<typename ValueType>
    Matrix<ValueType>::Matrix(const Matrix <ValueType> &rhs)
    {
        *this = Matrix(rhs.vectors_.size(), rhs.vectors_.at(0).values_.size());
        this->CopyItems(rhs);
    }

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
        if (index >= vectors_.size() || index < 0)
            throw std::runtime_error("Index is less than zero or greater than vector's size");

        return this->vectors_.at(index);
    }

    template<typename ValueType>
    const Vector <ValueType> &Matrix<ValueType>::operator[](const std::size_t index) const
    {
        if (index >= vectors_.size() || index < 0)
            throw std::runtime_error("Index is less than zero or greater than vector's size");

        return this->vectors_.at(index);
    }

    template<typename ValueType>
    bool Matrix<ValueType>::CheckMatricesCompatibility(const Matrix <ValueType> &first,
                                                       const Matrix <ValueType> &second,
                                                       const bool should_throw)
    {
        if (first.vectors_.size() != second.vectors_.size() ||
            first.vectors_.at(0).values_.size() != second.vectors_.at(0).values_.size())
        {
            if (should_throw)
                throw std::runtime_error("Matrices' sizes incompatible");
            return false;
        }
        return true;
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
                ValueType(),
                [&](ValueType response, const Vector<ValueType> &row) -> ValueType {
                    return response + row.Sum();
                });
    }

    template<typename ValueType>
    void Matrix<ValueType>::Resize(const std::size_t new_rows, const std::size_t new_cols, const ValueType fill_with)
    {
        Matrix<ValueType>::CheckValidityOfDimensions(new_rows, new_cols);
        this->vectors_.resize(new_rows, Vector<ValueType>(new_cols, fill_with));
        this->vectors_.shrink_to_fit();
        for (auto &row : this->vectors_)
            row.Resize(new_cols, fill_with);
    }

    template<typename ValueType>
    void Matrix<ValueType>::CheckValidityOfDimensions(const std::size_t rows_count, const std::size_t cols_count)
    {
        if (rows_count <= 0 || cols_count <= 0)
            throw std::runtime_error("Sizes are invalid");
    }

    template<typename ValueType>
    Matrix <ValueType> &Matrix<ValueType>::operator*=(const ValueType ratio)
    {
        for (auto &row : this->vectors_)
            row *= ratio;
        return *this;
    }

    template<typename ValueType>
    Matrix <ValueType> &Matrix<ValueType>::operator/=(const ValueType ratio)
    {
        if (ratio == 0)
        {
            throw std::runtime_error("Division by zero is not allowed");
            return *this;
        }

        for (auto &row : this->vectors_)
            row *= ratio;
        return *this;
    }

    template<typename ValueType>
    Matrix <ValueType> Matrix<ValueType>::operator+(const Matrix <ValueType> &rhs) const
    {
        Matrix<ValueType>::CheckMatricesCompatibility(*this, rhs);
        auto response = Matrix<ValueType>(*this);
        for (std::size_t counter = 0; auto &row : response.vectors_)
            row += rhs.vectors_.at(counter++);
        return response;
    }

    template<typename ValueType>
    Matrix<ValueType>::Matrix(const ValueType *array, const std::size_t rows, const std::size_t cols):
            vectors_(rows, Vector<ValueType>(cols, 0))
    {
        Matrix<ValueType>::CheckValidityOfDimensions(rows, cols);
        for (std::size_t row = 0; row < rows; ++row)
            for (std::size_t col = 0; col < cols; ++col)
                this->vectors_.at(row).values_.at(col) = *(array + row * cols + col);
    }

    template<typename ValueType>
    Matrix <ValueType> Matrix<ValueType>::operator-(const Matrix <ValueType> &rhs) const
    {
        Matrix<ValueType>::CheckMatricesCompatibility(*this, rhs);
        auto response = Matrix<ValueType>(*this);
        for (std::size_t counter = 0; auto &row : response.vectors_)
            row -= rhs.vectors_.at(counter++);
        return response;
    }

    template<typename ValueType1>
    bool operator==(const Matrix <ValueType1> &first, const Matrix <ValueType1> &second)
    {
        if (!Matrix<ValueType1>::CheckMatricesCompatibility(first, second, false))
            return false;

        for (std::size_t counter = 0; const auto &row : first.vectors_)
            if (!(row == second.vectors_.at(counter++)))
                return false;

        return true;
    }

    template<typename ValueType>
    void Matrix<ValueType>::CopyItems(const Matrix <ValueType> &rhs)
    {
        for (std::size_t row = 0; row < this->vectors_.size(); ++row)
            for (std::size_t col = 0; col < this->vectors_.at(row).values_.size(); ++col)
                this->vectors_.at(row).values_.at(col) = rhs.vectors_.at(row).values_.at(col);
    }

    template<typename ValueType>
    Matrix <ValueType> &Matrix<ValueType>::operator=(const Matrix <ValueType> &rhs)
    {
        this->CopyItems(rhs);
        return *this;
    }

    template<typename ValueType>
    Matrix <ValueType> Matrix<ValueType>::operator*(const ValueType scalar) const
    {
        auto response = Matrix<ValueType>(*this);
        response *= scalar;
        return response;
    }

    template<typename ValueType>
    void Matrix<ValueType>::Transpose()
    {
        if (!(Matrix<ValueType>::CheckMatrixsSquareness(*this, true)))
            return;

        const auto[rows, cols] = this->Sizes();

        for (std::size_t row = 0; row < rows; ++row)
        {
            for (std::size_t col = 0; col < row; ++col)
            {
                const auto temp = this->vectors_.at(row).values_.at(col);
                this->vectors_.at(row).values_.at(col) = this->vectors_.at(col).values_.at(row);
                this->vectors_.at(col).values_.at(row) = temp;
            }
        }
    }

    template<typename ValueType>
    bool Matrix<ValueType>::CheckMatrixsSquareness(const Matrix <ValueType> &matrix, const bool should_throw)
    {
        const auto[row, col] = matrix.Sizes();
        if (row != col)
        {
            if (should_throw)
                throw std::runtime_error("Unable to perform operation with non-square matrix");

            return false;
        }
        return true;
    }
}