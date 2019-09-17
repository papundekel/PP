#pragma once
#include "type.hpp"
template <typename... T>
constexpr auto last(types<T...>) { return type<decl_type<(type<T>{}, ...)>>{}; }