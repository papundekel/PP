#pragma once
#include "type.hpp"
template <typename T>
constexpr auto make_reference_lvalue(T) { return type<untype<T>&>{}; }