#pragma once
#include "is_reference_lvalue.hpp"
#include "is_reference_rvalue.hpp"

template <typename T>
constexpr bool is_reference = is_reference_lvalue<T> || is_reference_rvalue<T>;