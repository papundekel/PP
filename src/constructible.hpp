#pragma once
#include "value_t.hpp"
#include "forward.hpp"

template <typename T, typename... Args>
using constructible = value_t<requires (Args... args)
{
    T(frwd<Args>(args)...);
}>;