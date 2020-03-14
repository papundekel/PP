#pragma once
#include "first_rest.hpp"

constexpr auto first = [](auto x)
{
    return dfirst_rest::_<true>(x);
};