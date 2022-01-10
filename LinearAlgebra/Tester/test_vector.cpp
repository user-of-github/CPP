#include "./test_vector.h"

const auto test_size = []() {
    assert(LinearAlgebra::Vector<double>({1, 2, 2, -201}).Size() == 4);
    LinearAlgebra::Vector<int> tester({2, 3, 4});
    for (std::size_t counter = std::rand() % 100; counter < std::rand() % 1000 + 100; ++counter)
    {
        tester.Resize(counter, counter);
        assert(tester.Size() == counter);
    }
};

const auto test_operators = []() {
    LinearAlgebra::Vector<int> tester(10);
    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
        tester[counter] = counter;

    //std::cout << "Tester: " << tester;
    const int rand1 = std::rand() % 1000;

    tester += rand1;
    //std::cout << "Tester: " << tester;

    auto tester2 = tester;
    tester2 += rand1;
    //std::cout << "Tester 2: " << tester2;

    assert(tester + rand1 == tester2);

    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
        assert(tester2[counter] == tester[counter] + rand1);

    tester += tester2;
    tester *= rand1;

    for (std::size_t counter = 0; counter < tester.Size(); ++counter)
        assert(tester[counter] == (tester2[counter] + (tester2[counter] - rand1)) * rand1);

    tester /= rand1;
    tester -= tester2;
    tester += rand1;
};

const auto test_norm = []() {
    assert(LinearAlgebra::Vector<int>({4, 4, 4, 4, 0, 0, 0}).GetNorm() == 8);
    assert(LinearAlgebra::Vector<int>({0, 0, 0, 0, 0, 0, 0, 0, 0}).GetNorm() == 0);
    assert(LinearAlgebra::Vector<int>({0, -1, 0, 0, 0, 0, 0}).GetNorm() == 1);
    assert(LinearAlgebra::Vector<int>({0, 0, 0, 0, 0, 0, 1}).GetNorm() == 1);
    assert(LinearAlgebra::Vector<int>({3, 4, 0, 0, 0, 0, 0}).GetNorm() == 5);

    LinearAlgebra::Vector<double> tester(10);
    double to_check = 0;
    for (std::size_t counter = 0; counter < 10; ++counter)
    {
        /// TO DO (with epsilion)
        tester[counter] = (std::rand() % 255 - 100);
    }
};

void TestVector()
{
    test_size();
    test_operators();
    test_norm();
}
