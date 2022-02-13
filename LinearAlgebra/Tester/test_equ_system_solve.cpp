#include <gtest/gtest.h>
#include "../Library/EquationSystemSolver/equation_system_solver.hpp"
#include "../Library/EquationSystemSolver/equation_system_solver.cpp"


TEST(Matrix, EquationSystemSolver)
{
    const std::size_t size_x2{2};
    const float initial_coeff_x2[][size_x2][size_x2]{{{3, 2}, {1, 4}},
                                                     {{3, 7}, {5, 9}}};
    const float free_coeff_x2[][size_x2]{{1,  -3},
                                         {-1, 1}};
    const float roots_x2[][size_x2]{{1, -1},
                                    {2, -1}};
    for (std::size_t counter = 0; counter < 2; ++counter)
    {
        EXPECT_TRUE(
                LinearAlgebra::EquationSystemSolver::Cramer(
                        LinearAlgebra::Matrix((const float *) initial_coeff_x2[counter], size_x2, size_x2),
                        LinearAlgebra::Vector((const float *) free_coeff_x2[counter], size_x2)
                ) == LinearAlgebra::Vector((const float *) roots_x2[counter], size_x2)
        );
        EXPECT_TRUE(
                LinearAlgebra::EquationSystemSolver::InverseMatrix(
                        LinearAlgebra::Matrix((const float *) initial_coeff_x2[counter], size_x2, size_x2),
                        LinearAlgebra::Vector((const float *) free_coeff_x2[counter], size_x2)
                ) == LinearAlgebra::Vector((const float *) roots_x2[counter], size_x2)
        );
        EXPECT_TRUE(
                LinearAlgebra::EquationSystemSolver::Gauss(
                        LinearAlgebra::Matrix((const float *) initial_coeff_x2[counter], size_x2, size_x2),
                        LinearAlgebra::Vector((const float *) free_coeff_x2[counter], size_x2)
                ) == LinearAlgebra::Vector((const float *) roots_x2[counter], size_x2)
        );

    }

    const std::size_t size_x3{3};
    const float initial_coeff_x3[][size_x3][size_x3]{{{2, 3, 1}, {3, -1, 2},  {1, 4,  -1}},
                                                     {{1, 1, 1}, {2, -1, -6}, {3, -2, 0}},
                                                     {{1, 1, 1}, {1, 1,  2},  {1, 2,  3}}};
    const float free_coeff_x3[][size_x3]{{1, 1,  2},
                                         {2, -1, 8},
                                         {2, 4,  5}};
    const float roots_x3[][size_x3]{{1, 0,  -1},
                                    {2, -1, 1},
                                    {1, -1, 2}};
    for (std::size_t counter = 0; counter < 3; ++counter)
    {
        EXPECT_TRUE(
                LinearAlgebra::EquationSystemSolver::Cramer(
                        LinearAlgebra::Matrix((const float *) initial_coeff_x3[counter], size_x3, size_x3),
                        LinearAlgebra::Vector((const float *) free_coeff_x3[counter], size_x3)
                ) == LinearAlgebra::Vector((const float *) roots_x3[counter], size_x3)
        );

        EXPECT_TRUE(
                LinearAlgebra::EquationSystemSolver::InverseMatrix(
                        LinearAlgebra::Matrix((const float *) initial_coeff_x3[counter], size_x3, size_x3),
                        LinearAlgebra::Vector((const float *) free_coeff_x3[counter], size_x3)
                ) == LinearAlgebra::Vector((const float *) roots_x3[counter], size_x3)
        );

        EXPECT_TRUE(
                LinearAlgebra::EquationSystemSolver::Gauss(
                        LinearAlgebra::Matrix((const float *) initial_coeff_x3[counter], size_x3, size_x3),
                        LinearAlgebra::Vector((const float *) free_coeff_x3[counter], size_x3)
                ) == LinearAlgebra::Vector((const float *) roots_x3[counter], size_x3)
        );
    }


    const std::size_t size_x4{4};
    const float initial_coeff_x4[][size_x4][size_x4]{{{1, 2, 3,  4}, {2, 1, 2,  3}, {3, 2, 1,  2}, {4, 3, 2,  1}},
                                                     {{2, 2, -1, 1}, {4, 3, -1, 2}, {8, 5, -3, 4}, {3, 3, -2, 2}}};
    const float free_coeff_x4[][size_x4]{{7, 6, 7,  18},
                                         {4, 6, 12, 6}};
    const float roots_x4[][size_x4]{{2, 1, 5,  -3},
                                    {1, 1, -1, -1}};
    for (std::size_t counter = 0; counter < 2; ++counter)
    {
        EXPECT_TRUE(
                LinearAlgebra::EquationSystemSolver::Cramer(
                        LinearAlgebra::Matrix((const float *) initial_coeff_x4[counter], size_x4, size_x4),
                        LinearAlgebra::Vector((const float *) free_coeff_x4[counter], size_x4)
                ) == LinearAlgebra::Vector((const float *) roots_x4[counter], size_x4)
        );

        EXPECT_TRUE(
                LinearAlgebra::EquationSystemSolver::InverseMatrix(
                        LinearAlgebra::Matrix((const float *) initial_coeff_x4[counter], size_x4, size_x4),
                        LinearAlgebra::Vector((const float *) free_coeff_x4[counter], size_x4)
                ) == LinearAlgebra::Vector((const float *) roots_x4[counter], size_x4)
        );

        EXPECT_TRUE(
                LinearAlgebra::EquationSystemSolver::Gauss(
                        LinearAlgebra::Matrix((const float *) initial_coeff_x4[counter], size_x4, size_x4),
                        LinearAlgebra::Vector((const float *) free_coeff_x4[counter], size_x4)
                ) == LinearAlgebra::Vector((const float *) roots_x4[counter], size_x4)
        );
    }
}
