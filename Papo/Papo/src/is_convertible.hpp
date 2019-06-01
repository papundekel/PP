#pragma once
#include "declval.hpp"
#include "void_t.hpp"

template <typename from, typename to, typename = void_t<>>
constexpr bool is_convertible = false;

template <typename from, typename to>
constexpr bool is_convertible<from, to, void_t<decltype(
	declval<to&>() = declval<from>())>>
= true;