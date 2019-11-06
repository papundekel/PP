#pragma once
#include "type.hpp"

constexpr auto almost = [](auto x)
{
    return [x](auto y)
    {
        return same(remove_cv_ref(x))(remove_cv_ref(y));
    };
}