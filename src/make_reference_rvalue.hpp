#pragma once
#include "type.hpp"
template <typename T>
constexpr auto make_reference_rvalue(T) { return type<untype<T>&&>{}; }