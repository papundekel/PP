#pragma once
#include "forward.hpp"

template <typename T, typename... Args>
concept constructible_c = requires (Args... args)
{
    T(frwd<Args>(args)...);
};