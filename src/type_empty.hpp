#pragma once
#include "type.hpp"
#include "type_count.hpp"
template <typename T>
constexpr auto empty(T t) { return count(t) == 0; }