#ifndef LINEARALGEBRA_UTILS_H
#define LINEARALGEBRA_UTILS_H

#pragma once

#include <cmath>


namespace LinearAlgebra::Utils
{
    template<typename ValueType>
    bool IsInEpsilonNeighborHood(const ValueType &, const ValueType &, const ValueType &);
}
#endif //LINEARALGEBRA_UTILS_H
