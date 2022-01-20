#include "./Library/Matrix/matrix.hpp"
#include "./Library/Matrix/matrix.cpp"


int main()
{
    const double initial3[3][3] = {
            {1, 0, 3},
            {4, 5, 6},
            {7, 8, 2022}};

    const double initial3_triangulated[3][3] = {
            {7, 8,          200},
            {0, -8.0 / 7.0, -179.0 / 7.0},
            {0, 0,          -943.0 / 8.0}};

    auto tester3 = LinearAlgebra::Matrix<double>((const double *) initial3, 3, 3);
    const auto tester3_triangulated = LinearAlgebra::Matrix<double>((const double *) initial3_triangulated, 3, 3);

    tester3.Triangulate();

    std::cout << tester3 << '\n' << tester3_triangulated;

    // check HardFire's code //

    return 0;
}
