#pragma once
#include "void_t.hpp"
#include "declval.hpp"

template <class T, typename = void_t<>, class... args>
constexpr bool _is_constructible = false;

template <typename T, class... args>
constexpr bool _is_constructible<T, void_t<decltype(
	T(declval<args>()...))>, args...>
= true;

template <typename T, class... args>
constexpr bool is_constructible = _is_constructible<T, void_t<>, args...>;