#pragma once
#include "void_t.hpp"
#include "declval.hpp"

template <typename T, typename U, typename = void_t<>>
constexpr bool is_comparable = false;

template <typename T, typename U>
constexpr bool is_comparable<T, U, void_t<decltype(
	declval<T>() == declval<U>(),
	declval<T>() != declval<U>()
)>> = true;