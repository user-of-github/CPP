#include "./Library/Matrix/Vector/vector.hpp"
#include "./Library/Matrix/Vector/vector.cpp"


int main()
{
    LinearAlgebra::Vector<std::string> test({});
    std::cout << test;
    try
    {
        std::cout << test[0];
    }
    catch (const std::exception &exception)
    {
        std::cout << exception.what();
    }
    return 0;
}
