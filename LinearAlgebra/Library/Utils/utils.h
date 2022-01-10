#ifndef LINEARALGEBRA_UTILS_H
#define LINEARALGEBRA_UTILS_H

#include <cmath>


namespace Utils
{
    template<typename ValueType>
    bool IsInEpsilonNeighborHood(const ValueType &, const ValueType &, const ValueType &);
}
#endif //LINEARALGEBRA_UTILS_H
