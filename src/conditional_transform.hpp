#pragma once
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "type.hpp"

template <bool test, typename Transform, typename T>
constexpr auto conditional_transform(Transform transform, T t)
{
    if constexpr (test)
        return transform(t);
    else
        return t;
}

#pragma GCC diagnostic pop