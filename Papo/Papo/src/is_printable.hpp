#pragma once
#include "void_t.hpp"
#include "declval.hpp"

template <typename T, typename = void_t<>>
constexpr bool is_printable = false;

template <typename T>
constexpr bool is_printable<T, void_t<
	decltype(to_chars(declval<char*>(), declval<char*>(), declval<T>()))>>
= true;