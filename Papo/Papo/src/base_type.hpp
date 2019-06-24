#pragma once
#include "declval.hpp"
#include "container.hpp"
#include "remove_reference.hpp"

namespace detail
{
	template <typename T>
	constexpr auto& base_type()
	{
		if constexpr (iterator<T>)
			return *declval<T>();
		else if constexpr (container<T>)
			return base_type<begin_t<T>>();
	}
}

template <typename T>
using base_type = remove_reference<decltype(detail::base_type<T>())>;