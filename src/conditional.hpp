#pragma once
#include "conditional_transform.hpp"
#include "ignore.hpp"
template <bool test, typename T, typename U>
constexpr auto conditional(T t, U u) { return conditional_transform<test>([t](auto){ return t; }, u); }