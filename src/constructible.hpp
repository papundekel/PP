#pragma once
#include "val.hpp"
#include "forward.hpp"

template <typename T, typename... Args>
using constructible = val<requires (Args... args)
{
    T(frwd<Args>(args)...);
}>;