#include "./Library/Matrix/matrix.hpp"
#include "./Library/Matrix/matrix.cpp"


int main()
{
    const int initial[4][4] = {{1,  2,  3,  4},
                               {5,  6,  7,  8},
                               {9,  10, 11, 12},
                               {13, 14, 15, 16}};

    const int initial_transposed[4][4] = {{1, 5, 9,  13},
                                          {2, 6, 10, 14},
                                          {3, 7, 11, 15},
                                          {4, 8, 12, 16}};
    auto tester = LinearAlgebra::Matrix<int>((int *) initial, 4, 4);
    auto tester_transposed = LinearAlgebra::Matrix<int>((int *) initial_transposed, 4, 4);
    tester.Transpose();
    std::cout << tester << '\n' << tester_transposed << '\n';
    return 0;
}
