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
    Matrix<ValueType>::Matrix(const ValueType *array, const std::size_t rows, const std::size_t cols):
            vectors_(rows, Vector<ValueType>(cols, 0))
    {
        Matrix<ValueType>::CheckValidityOfDimensions(rows, cols);
        for (std::size_t row = 0; row < rows; ++row)
            for (std::size_t col = 0; col < cols; ++col)
                this->vectors_.at(row).values_.at(col) = *(array + row * cols + col);
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


    template<typename ValueType>
    constexpr ValueType Matrix<ValueType>::Sum() const
    {
        return std::accumulate(
                std::begin(this->vectors_),
                std::end(this->vectors_),
                ValueType(),
                [&](ValueType response, const Vector <ValueType> &row) -> ValueType {
                    return response + row.Sum();
                });
    }

    template<typename ValueType>
    constexpr std::tuple<std::size_t, std::size_t> Matrix<ValueType>::Sizes() const
    {
        return std::tuple<std::size_t, std::size_t>(this->vectors_.size(), this->vectors_.at(0).values_.size());
    }

    template<typename ValueType>
    void Matrix<ValueType>::Transpose()
    {
        if (!(Matrix<ValueType>::IsMatrixSquare(*this, true)))
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
    void Matrix<ValueType>::Resize(const std::size_t new_rows, const std::size_t new_cols, const ValueType fill_with)
    {
        Matrix<ValueType>::CheckValidityOfDimensions(new_rows, new_cols);
        this->vectors_.resize(new_rows, Vector<ValueType>(new_cols, fill_with));
        this->vectors_.shrink_to_fit();
        for (auto &row : this->vectors_)
            row.Resize(new_cols, fill_with);
    }

    template<typename ValueType>
    constexpr std::size_t Matrix<ValueType>::Triangulate()
    {
        const auto sizes = this->Sizes();
        const auto rows = std::get<0>(sizes), cols = std::get<1>(sizes);

        const auto get_similar_matrix_of_double = [&]() -> double ** {
            auto response = new double *[rows];
            for (std::size_t row = 0; row < rows; ++row)
                response[row] = new double[cols];

            for (std::size_t row = 0; row < rows; ++row)
                for (std::size_t col = 0; col < cols; ++col)
                    response[row][col] = static_cast<double>((*this)[row][col]);

            return response;
        };

        const auto gauss = [&](double **matrix) -> const std::size_t {
            // http://hardfire.ru/gauss
            const auto find_row_with_max_first_element = [&](const int from) -> const std::size_t {
                std::size_t response = from;
                for (std::size_t row = from + 1; row < rows; ++row)
                    if (std::abs(matrix[row][from]) > std::abs(matrix[response][from]))
                        response = row;
                return response;
            };

            const auto swap_rows = [&](const std::size_t row1, const std::size_t row2) -> void {
                if (row1 == row2) return;
                for (std::size_t col = 0; col < cols; ++col)
                    std::swap(matrix[row1][col], matrix[row2][col]);
            };

            std::size_t number_of_swaps = 0;
            for (std::size_t row = 0; row < rows; ++row)
            {
                // находим строку с максимальным первым элементом
                const auto row_with_max_first_item = find_row_with_max_first_element(row);

                if (Utils::IsInEpsilonNeighborHood(0.0, 0.1, matrix[row_with_max_first_item][row])) continue;

                swap_rows(row_with_max_first_item, row);

                number_of_swaps += (row_with_max_first_item != row) ? 1 : 0;

                //  вычитаем текущую строку из всех остальных
                for (std::size_t j = row + 1; j < rows; ++j)
                {
                    const auto q = (-1) * (double) (matrix[j][row]) / (double) (matrix[row][row]);
                    for (std::size_t k = cols - 1; k >= row; --k)
                    {
                        matrix[j][k] += (q * (double) matrix[row][k]);
                        if (k == 0) break; // because std::size_t === unsigned long long => overflow
                    }
                }
            }

            return number_of_swaps;
        };

        const auto copy_transformed_matrix_to_original = [&](const double **instance) -> void {
            for (std::size_t row = 0; row < rows; ++row)
                for (std::size_t col = 0; col < cols; ++col)
                    (*this)[row][col] = (ValueType) (instance[row][col]);
        };

        const auto free_matrix = [&](double **instance) -> void {
            for (std::size_t row = 0; row < rows; ++row)
                delete[] instance[row];
            delete[] instance;
        };

        auto to_count = get_similar_matrix_of_double();

        const auto number_of_swaps = gauss(to_count);
        copy_transformed_matrix_to_original((const double **) to_count); // <warning> casting to const ?</warning>
        free_matrix(to_count);

        return number_of_swaps;
    }

    template<typename ValueType>
    constexpr ValueType Matrix<ValueType>::Determinant() const
    {
        Matrix<ValueType>::IsMatrixSquare(*this, true);
        const auto rows = std::get<0>(this->Sizes());


        ValueType response = (ValueType) (1);
        auto triangled_matrix = Matrix<ValueType>(*this);
        const auto number_of_permutations = triangled_matrix.Triangulate();
        for (std::size_t row = 0; row < rows; ++row)
            response *= (*this)[row][row];

        if (number_of_permutations % 2 == 1)
            response *= -1;

        return response;
    }


    template<typename ValueType>
    Vector <ValueType> &Matrix<ValueType>::operator[](const std::size_t index)
    {
        if (index >= vectors_.size() || index < 0)
            throw std::invalid_argument("Index is less than zero or greater than vector's size");

        return this->vectors_.at(index);
    }

    template<typename ValueType>
    const Vector <ValueType> &Matrix<ValueType>::operator[](const std::size_t index) const
    {
        if (index >= vectors_.size() || index < 0)
            throw std::invalid_argument("Index is less than zero or greater than vector's size");

        return this->vectors_.at(index);
    }

    template<typename ValueType>
    Matrix <ValueType> &Matrix<ValueType>::operator+=(const ValueType ratio)
    {
        for (auto &row : this->vectors_)
            row += ratio;
        return *this;
    }

    template<typename ValueType>
    Matrix <ValueType> &Matrix<ValueType>::operator-=(const ValueType ratio)
    {
        for (auto &row : this->vectors_)
            row -= ratio;
        return *this;
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
            throw std::invalid_argument("Division by zero is not allowed");
            return *this;
        }

        for (auto &row : this->vectors_)
            row /= ratio;
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
    Matrix <ValueType> Matrix<ValueType>::operator+(const Matrix <ValueType> &rhs) const
    {
        Matrix<ValueType>::CheckMatricesCompatibility(*this, rhs);
        auto response = Matrix<ValueType>(*this);
        for (std::size_t counter = 0; auto &row : response.vectors_)
            row += rhs.vectors_.at(counter++);
        return response;
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

    template<typename ValueType>
    Matrix <ValueType> &Matrix<ValueType>::operator=(const Matrix <ValueType> &rhs)
    {
        this->CopyItems(rhs);
        return *this;
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
    void Matrix<ValueType>::CopyItems(const Matrix <ValueType> &rhs)
    {
        for (std::size_t row = 0; row < this->vectors_.size(); ++row)
            for (std::size_t col = 0; col < this->vectors_.at(row).values_.size(); ++col)
                this->vectors_.at(row).values_.at(col) = rhs.vectors_.at(row).values_.at(col);
    }

    template<typename ValueType>
    void Matrix<ValueType>::PrintVectorsRowForOstream(std::ostream &stream, const std::size_t index) const
    {
        this->vectors_.at(index).PrintVectorRowByStream(stream);
    }

    template<typename ValueType>
    constexpr bool Matrix<ValueType>::CheckMatricesCompatibility(const Matrix <ValueType> &first,
                                                                 const Matrix <ValueType> &second,
                                                                 const bool should_throw)
    {
        if (first.vectors_.size() != second.vectors_.size() ||
            first.vectors_.at(0).values_.size() != second.vectors_.at(0).values_.size())
        {
            if (should_throw)
                throw std::invalid_argument("Matrices' sizes incompatible");
            return false;
        }
        return true;
    }

    template<typename ValueType>
    constexpr bool Matrix<ValueType>::IsMatrixSquare(const Matrix <ValueType> &matrix, const bool should_throw)
    {
        const auto[row, col] = matrix.Sizes();
        if (row != col)
        {
            if (should_throw)
                throw std::invalid_argument("Unable to perform operation with non-square matrix");

            return false;
        }
        return true;
    }

    template<typename ValueType>
    void Matrix<ValueType>::CheckValidityOfDimensions(const std::size_t rows_count, const std::size_t cols_count)
    {
        if (rows_count <= 0 || cols_count <= 0)
            throw std::invalid_argument("Sizes are invalid");
    }
}