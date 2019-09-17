#pragma once
#include "reference_lvalue.hpp"
#include "reference_rvalue.hpp"

template <typename T>
constexpr auto reference(T t) { return reference_lvalue(t) || reference_rvalue(t); }