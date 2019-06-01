#pragma once
#include "enable_if.hpp"
#include "is_iterator.hpp"
#include "is_comparable.hpp"
#include "begin_end.hpp"
#include "declval.hpp"

template <typename T, typename = void>
constexpr bool is_container = false;

template <typename T>
constexpr bool is_container<T, enable_if<
	is_iterator<decltype(::begin(declval<T&>()))>
&&	is_comparable<decltype(::begin(declval<T&>())), decltype(::end(declval<T&>()))>
&&	is_iterator<decltype(::begin(declval<const T&>()))>
&&	is_comparable<decltype(::begin(declval<const T&>())), decltype(::end(declval<const T&>()))>>> = true;

/*template <typename T>
constexpr bool is_container<T, enable_if<
	is_iterator<decltype(begin(declval<T&>()))>
&&	is_comparable<decltype(begin(declval<T&>())), decltype(end(declval<T&>()))>
&&	is_iterator<decltype(begin(declval<const T&>()))>
&&	is_comparable<decltype(begin(declval<const T&>())), decltype(end(declval<const T&>()))>>> = true;*/