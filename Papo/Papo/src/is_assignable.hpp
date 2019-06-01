#pragma once
#include "declval.hpp"
#include "void_t.hpp"
template <typename to, typename from, typename = void_t<>>
constexpr bool is_assignable = false;

template <typename to, typename from>
constexpr bool is_assignable<to, from, void_t<decltype(
	declval<to&>() = declval<from>())>>
= true;