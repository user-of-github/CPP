#include "equation_system_solver.hpp"
#pragma once

namespace LinearAlgebra
{
    template<typename ValueType>
    Vector<ValueType> EquationSystemSolver<ValueType>::Cramer(const Matrix<ValueType> &coefficients_matrix,
                                                                        const Vector<ValueType> &free_coefficients_vector)
    {
        auto coefficients = coefficients_matrix;
        const auto size = std::get<0>(coefficients.Sizes());

        auto copy = new ValueType[size];

        const auto replace_column_to_free_coefficients = [&](const std::size_t col) -> void {
            for (std::size_t row = 0; row < size; ++row)
            {
                copy[row] = coefficients[row][col];
                coefficients[row][col] = free_coefficients_vector[row];
            }
        };

        const auto put_values_back_to_coefficient_matrix = [&](const std::size_t col) -> void {
            for (std::size_t row = 0; row < size; ++row)
                coefficients[row][col] = copy[row];
        };

        const auto main_determinant = coefficients.Determinant();
        if (Utils::IsInEpsilonNeighborHood(0.0, 0.001, main_determinant))
            throw std::runtime_error("Unable to use Cramer's method: main system determinant equals zero");

        auto response = Vector<ValueType>(size, 0);

        for (std::size_t counter = 0; auto &item : response.values_)
        {
            replace_column_to_free_coefficients(counter);
            const auto determinant = coefficients.Determinant();
            const auto x = determinant / main_determinant;
            item = x;
            put_values_back_to_coefficient_matrix(counter);
            ++counter;
        }

        delete[] copy;

        return response;
    }

    template<typename ValueType>
    Vector<ValueType>
    EquationSystemSolver<ValueType>::InverseMatrix(const Matrix<ValueType> &coefficients_matrix,
                                                             const Vector<ValueType> &free_coefficients_vector)
    {
        return Vector<ValueType>(
                coefficients_matrix.GetInverseMatrix() *
                Matrix<ValueType>::CreateColMatrixFromVector(free_coefficients_vector)
        );
    }

    template<typename ValueType>
    Vector<ValueType> EquationSystemSolver<ValueType>::Gauss(const Matrix<ValueType> &coefficients_matrix,
                                                                       const Vector<ValueType> &free_coefficients_vector)
    {
        const auto size = std::get<0>(coefficients_matrix.Sizes());

        auto full_system_matrix = Matrix<ValueType>(coefficients_matrix);
        full_system_matrix.Resize(size, size + 1, 0);
        for (std::size_t row = 0; row < size; ++row)
            full_system_matrix[row][size] = free_coefficients_vector[row];

        auto response = Vector<ValueType>(size, 0); // X Vector

        // Gauss back substitution (обратный ход)
        for (int var_counter = size - 1; var_counter >= 0; --var_counter)
        {
            response[var_counter] =
                    full_system_matrix[var_counter][size] / full_system_matrix[var_counter][var_counter];
            for (int rest_row = 0; rest_row < var_counter; rest_row++)
                full_system_matrix[rest_row][size] -= full_system_matrix[rest_row][var_counter] * response[var_counter];
        }

        return response;
    }
}