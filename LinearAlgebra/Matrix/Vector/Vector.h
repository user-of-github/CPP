#ifndef LINEARALGEBRA_VECTOR_H
#define LINEARALGEBRA_VECTOR_H

#include <vector>


namespace LinearAlgebra
{
    template<typename ValueType>
    class Vector
    {
    public:
        explicit Vector(const std::size_t = 0, const ValueType = 0);

        explicit Vector(const std::initializer_list<ValueType> &);

        constexpr std::size_t Size() const;

        void Resize(const std::size_t, const ValueType fill_with_ = 0);

        ValueType GetNorm() const;

        void Normalize();

        ValueType &operator[](const std::size_t) const;

        ValueType &operator[](const std::size_t);

    private:
        std::vector<ValueType> values_;
    };
}
#endif //LINEARALGEBRA_VECTOR_H
