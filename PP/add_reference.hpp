#pragma once
#include "is_referencable.hpp"
#include "get_type.hpp"

namespace PP
{
	PP_FUNCTOR(add_reference, value_wrap auto rvalue, type_wrap auto type)
	{
		constexpr auto T = PP_COPY_TYPE(type);

		if constexpr (is_referencable(T))
		{
			if constexpr (PP_GET_VALUE(rvalue))
				return type_v<PP_GET_TYPE(T)&&>;
			else
				return type_v<PP_GET_TYPE(T)&>;
		}
		else
			return t;
	}};
	
	constexpr inline auto lvalue_tag = value_v<false>;
	constexpr inline auto rvalue_tag = value_v<true>;

	template <bool rvalue>
	constexpr auto operator+(type_wrap auto t, value_wrap auto rvalue) noexcept
	{
		return add_reference(rvalue, t);
	}
}
