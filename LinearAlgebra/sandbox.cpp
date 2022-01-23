#include "./Library/Matrix/matrix.hpp"
#include "./Library/Matrix/matrix.cpp"


int main()
{
    const short initial[4][4] = {{1, 2, 1, 3},
                                 {2, 1, 4, 1},
                                 {3, 3, 2, -1},
                                 {4, 2, 2, -1}};
    const auto tester = LinearAlgebra::Matrix<short>((const short *) initial, 4, 4);
    const short result[16][3][3] = {
            {{1, 4, 1}, {3, 2, -1}, {2, 2, -1}},
            {{2, 4, 1}, {3, 2, -1}, {4, 2, -1}},
            {{2, 1, 1}, {3, 3, -1}, {4, 2, -1}},
            {{2, 1, 4}, {3, 3, 2},  {4, 2, 2}},
            {{2, 1, 3}, {3, 2, -1}, {2, 2, -1}},
            {{1, 1, 3}, {3, 2, -1}, {4, 2, -1}},
            {{1, 2, 3}, {3, 3, -1}, {4, 2, -1}},
            {{1, 2, 1}, {3, 3, 2},  {4, 2, 2}}
    };


    for (std::size_t row = 0; row < 2; ++row)
        for (std::size_t col = 0; col < 2; ++col)
        {
            if(!(tester.GetSubmatrixWithoutRowAndColumn(row, col) ==
                LinearAlgebra::Matrix<short>((const short *) result[row * 4 + col], 3, 3)))
            {
                std::cout << "counter: " << row * 4 + col <<"| Row & col: " << row << ' ' << col << "\n" ;
                std::cout <<  tester.GetSubmatrixWithoutRowAndColumn(row, col) << '\n';
                std::cout << LinearAlgebra::Matrix<short>((const short *) result[row * 4 + col], 3, 3) << "\n\n";
            }
        }

    return 0;
}
