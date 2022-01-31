#ifndef TEST_LIBRARY_EQUATION_SYSTEM_SOLVER_HPP
#define TEST_LIBRARY_EQUATION_SYSTEM_SOLVER_HPP

#pragma once


#include "../Matrix/matrix.hpp"
#include "../Matrix/matrix.cpp"
#include "../Matrix/Vector/vector.cpp"
#include "../Matrix/Vector/vector.cpp"


namespace LinearAlgebra
{

    class EquationSystemSolver
    {
    public:

        template<typename ValueType>
        static Vector <ValueType> Cramer(const Matrix <ValueType> &, const Vector <ValueType> &);

        template<typename ValueType>
        static Vector <ValueType> InverseMatrix(const Matrix <ValueType> &,
                                                const Vector <ValueType> &);

        template<typename ValueType>
        static Vector <ValueType> Gauss(const Matrix <ValueType> &, const Vector <ValueType> &);
    };
}


#endif //TEST_LIBRARY_EQUATION_SYSTEM_SOLVER_HPP