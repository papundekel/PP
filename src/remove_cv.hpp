#pragma once
#include "remove_const.hpp"
#include "remove_volatile.hpp"

template <typename T>
constexpr auto remove_cv(T t) { return remove_volatile(remove_const(t)); }