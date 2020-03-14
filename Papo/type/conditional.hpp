#pragma once
#include "conditional_transform.hpp"
#include "ignore.hpp"

template <bool test>
constexpr auto conditional = []
(auto x){ return conditional_transform<test>(ignore(x)); };