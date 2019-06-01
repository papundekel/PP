#pragma once
#include "void_t.hpp"
#include "declval.hpp"
#include "is_iterator_bi.hpp"

template <typename T, typename = void_t<>>
constexpr bool is_iterator_ra = false;

template <typename T>
constexpr bool is_iterator_ra<T,
	void_t<decltype(declval<T>()[0]),
	decltype(declval<T>() + 0),
	decltype(declval<T>() - 0),
	decltype(declval<T>() - declval<T>()),
	decltype(declval<T>() < declval<T>())>>
	= is_iterator_bi<T>;