#include "utils.hpp"

namespace LinearAlgebra::Utils
{
    template<typename ValueType>
    bool IsInEpsilonNeighborHood(const ValueType &x0, const ValueType &epsilon, const ValueType &x)
    {
        return std::fabs(x - x0) <= epsilon;
    }
}