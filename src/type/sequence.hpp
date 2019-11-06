#pragma once
#include "type.hpp"
#include "val.hpp"

namespace dsequence
{
    constexpr auto middle(size_t x, size_t y)
    {
        return x + (y - x) / 2;
    }

    template <size_t begin, size_t end, auto arr>
    using x = x<begin, middle(begin, end)>;
}

template <auto arr>
using sequence = dsequence::