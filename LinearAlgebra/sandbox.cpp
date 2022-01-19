#include "./Library/Matrix/matrix.hpp"
#include "./Library/Matrix/matrix.cpp"


int main()
{
    const int initial[3][4] = {{6,  5,  4,  3},
                               {6,  3,  0,  -3},
                               {-2, -3, -4, -5}};

    auto matrix = LinearAlgebra::Matrix<int>((int *) initial, 3, 4);

    std::cout << matrix;

    try
    {
        matrix.Triangulate();
        std::cout << '\n' << matrix;
    }
    catch (std::exception &exception)
    {
        std::cout << exception.what() << '\n';
    }


    // check HardFire's code //

    return 0;
}
