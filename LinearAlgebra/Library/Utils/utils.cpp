#include "utils.hpp"

#pragma once


namespace LinearAlgebra::Utils
{
    template<typename ValueType>
    bool IsInEpsilonNeighborHood(const ValueType &x0, const ValueType &epsilon, const ValueType &x)
    {
        return std::abs(x - x0) <= epsilon;
    }
}