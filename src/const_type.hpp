#pragma once
#include "same.hpp"
#include "make_const.hpp"
template <typename T>
constexpr auto const_type(T t) { return same(t, make_const(t)); }