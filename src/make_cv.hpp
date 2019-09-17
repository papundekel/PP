#pragma once
#include "make_const.hpp"
#include "make_volatile.hpp"
template <typename T>
constexpr auto make_cv(T t) { return make_const(make_volatile(t)); }