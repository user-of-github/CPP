#include "./Library/Matrix/matrix.hpp"
#include "./Library/Matrix/matrix.cpp"


int main()
{
    const auto test = LinearAlgebra::Vector<int>({2, 3, 4});
    std::cout << test;
    try
    {
        std::cout << test[4];
    }
    catch (const std::exception &exception)
    {
        std::cout << exception.what() << '\n';
    }

    const int initial[4][4] = {{1, 0, 0, 0},
                               {0, 1, 0, 0},
                               {0, 0, 1, 0},
                               {0, 0, 0, 1}};

    auto test2 = LinearAlgebra::Matrix<int>((const int *) (initial), 4, 4);
    std::cout << test2 << '\n';
    test2.Resize(5, 5, 1);
    std::cout << test2 << '\n' << test2.Sum() << '\n';

    try
    {
        test2.Resize(4, 4);
        std::cout << test2 << '\n' << test2.Sum() << '\n';;
    }
    catch (std::exception &exception)
    {
        std::cout << exception.what() << '\n';
    }


    try
    {
        test2 *= 2;
        std::cout << test2 << '\n';
    }
    catch (std::exception &exception)
    {
        std::cout << exception.what() << '\n';
    }

    try
    {
        // COPY CONSTRUCTOR DOES NOT WORK !
        std::cout << LinearAlgebra::Matrix<int>(test2) << '\n';
    }
    catch (std::exception &exception)
    {
        std::cout << exception.what() << '\n';
    }


    return 0;
}
