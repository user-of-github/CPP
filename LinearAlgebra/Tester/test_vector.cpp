#pragma once

#include "./test_vector.h"



void TestVector()
{
    const auto test_size = [](){
        assert(LinearAlgebra::Vector<double>({1, 2, 2, -201}).Size() == 4);
        LinearAlgebra::Vector<int> tester({2, 3, 4});
        for (std::size_t counter = std::rand() % 100 ; counter < std::rand() % 1000 + 100; ++counter)
        {
            tester.Resize(counter, counter);
            assert(tester.Size() == counter);
        }
    };

    const auto test_operators = [](){
        LinearAlgebra::Vector<int> tester(10);
        for (std::size_t counter = 0; counter < tester.Size(); ++counter)
            tester[counter] = counter;

        const int rand1 = std::rand() % 1000;
        const int rand2 = std::rand() % 2000;

        tester += rand1;

        // copy constructor !!!
        // other mistakes in operators
        auto tester2 = tester * rand2;

    };


    test_size();
    test_operators();
}
