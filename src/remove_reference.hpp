#pragma once
#include "type.hpp"

template <typename T>
constexpr auto remove_reference(type<T> t) { return t; }
template <typename T>
constexpr auto remove_reference(type<T&>) { return type<T>{}; }
template <typename T>
constexpr auto remove_reference(type<T&&>) { return type<T>{}; }