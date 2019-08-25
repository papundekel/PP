#include "range.hpp"
#include "swap.hpp"
#include <cstdlib>
#include <ctime>
#include "next.hpp"
template <Range R>
requires iterator_ra<typename R::begin_t> && iterator_ra<typename R::end_t>
typename R::begin_t k_smallest(R r, size_t k)
{
    auto partition = [r](typename R::begin_t pivot)
    {
        swap(*pivot, r.last());
        auto l = r.begin;
        for (auto i = next(r.begin); i != r.end - 1; ++i)
        {
            if (*i < *pivot)
            {
                swap(*l, *i);
                ++l;
            }
        }
        swap(*l, r.last());
        return l;
    };

    auto count = distance(r);

    std::srand(std::time(nullptr));
    auto pivot = r.begin + std::rand() % count;
    pivot = partition(pivot);

    auto L = range(r.begin, pivot);
    auto dis = distance(L);
    if (k < dis)
        return k_smallest(L, k);
    else if (k > dis)
        return k_smallest(range(next(pivot), r.end), k - dis - 1);
    else
        return pivot;
}