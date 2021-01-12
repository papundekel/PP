#pragma once
#include "is_referencable.hpp"
#include "get_type_weak.hpp"

namespace PP
{
	template <bool rvalue>
	struct reference_tag_t {};
	template <bool rvalue>
	constexpr inline reference_tag_t<rvalue> reference_tag = {};
	constexpr inline reference_tag_t<false> lvalue_tag = {};
	constexpr inline reference_tag_t<true > rvalue_tag = {};

	template <bool rvalue>
	constexpr auto operator+(auto t, reference_tag_t<rvalue>) noexcept
	{
		using T = PP_GET_TYPE_WEAK(t);

		if constexpr (is_referencable(type_v<T>))
		{
			if constexpr (rvalue)
				return type_v<T&&>;
			else
				return type_v<T&>;
		}
		else
			return t;
	}
}
