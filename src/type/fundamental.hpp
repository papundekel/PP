#pragma once 
#include "fundamental_integers.hpp"
#include "fundamental_floats.hpp"
#include "fundamental_chars.hpp"
#include "type/pointer.hpp"

constexpr auto fundamental_types = join(
    t<void, nullptr_t, bool>,
    fundamental_integers,
    fundamental_floats,
    fundamental_chars);

constexpr auto fundamental = []
(auto x)
{
    return pointer_type(x) || contains<fundamental_types, same(x)>;
};