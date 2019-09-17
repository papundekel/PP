#pragma once 
#include "number.hpp"
#include "pointer_type.hpp"
#include "character.hpp"
#include "floating.hpp"
#include "fundamental_integers.hpp"
#include "fundamental_floats.hpp"
#include "fundamental_chars.hpp"

constexpr auto fundamental_types = join(
    types<void, nullptr_t, bool>{},
    fundamental_integers,
    fundamental_floats,
    fundamental_chars);

template <typename T>
constexpr auto fundamental(T t) { return pointer_type(t) || contains(fundamental_types, [t](auto x){ return x == t; }); }