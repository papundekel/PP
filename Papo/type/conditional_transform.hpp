#pragma once
#include "type.hpp"

template <bool test>
constexpr auto conditional_transform = []
(auto transform)
{
    return [transform]
    (auto x)
    {
        if constexpr (test)
            return transform(x);
        else
            return x;
    };
};
