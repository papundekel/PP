#pragma once
#include "array.hpp"
#include "functional/apply_partially.hpp"
#include "tuple_apply.hpp"
#include "tuple_like.hpp"

namespace PP
{
	PP_FUNCTOR(tuple_make_array, concepts::type auto t, concepts::tuple auto&& tp)
	{
		return (make_array * t)[PP_FORWARD(tp)];
	}};
	PP_FUNCTOR(tuple_forward_array, concepts::type auto t, concepts::tuple auto&& tp)
	{
		return (forward_as_array * t)[PP_FORWARD(tp)];
	}};

	constexpr auto operator*(concepts::tuple auto&& t)
	{
		return tuple_make_array(type_void, PP_FORWARD(t));
	}
	constexpr auto operator~(concepts::tuple auto&& t) noexcept
	{
		return tuple_forward_array(type_void, PP_FORWARD(t));
	}
}
