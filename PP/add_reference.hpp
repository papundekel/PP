#pragma once
#include "concepts/atomic/referencable.hpp"
#include "get_type.hpp"
#include "get_value.hpp"

namespace PP
{
	PP_FUNCTOR(add_reference, concepts::value auto rvalue, concepts::type auto t)
	{
		using T = PP_GET_TYPE(t);

		if constexpr (is_referencable(type<T>))
		{
			if constexpr (PP_GET_VALUE(rvalue))
				return type<T&&>;
			else
				return type<T&>;
		}
		else
			return t;
	}};
	
	constexpr inline auto lvalue_tag = value<false>;
	constexpr inline auto rvalue_tag = value<true>;

	constexpr auto operator+(concepts::type auto t, concepts::value auto rvalue) noexcept
	{
		return add_reference(rvalue, t);
	}
}
