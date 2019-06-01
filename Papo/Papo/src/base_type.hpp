#pragma once
#include "declval.hpp"
#include "container.hpp"
#include "remove_reference.hpp"

template <typename T>
constexpr auto& _base_type()
{
	if constexpr (iterator<T>)
		return *declval<T>();
	else if constexpr (container<T>)
		return _base_type<begin_t<T>>();
}

template <typename T>
using base_type = remove_reference<decltype(_base_type<T>())>;