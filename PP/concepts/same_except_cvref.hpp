#pragma once
#include "../apply_transform.hpp"
#include "../functional/functor.hpp"
#include "../remove_cvref.hpp"
#include "same.hpp"

namespace PP
{
	namespace concepts
	{
		template <typename T, typename U>
		concept same_except_cvref = same<apply_transform_t<remove_cvref, T>, apply_transform_t<remove_cvref, U>>;
		template <typename T, typename U>
		concept different_except_cvref = !same_except_cvref<T, U>;
	}

	PP_FUNCTOR(is_same_except_cvref, auto t, auto u)
	{
		return concepts::same_except_cvref<PP_GET_TYPE(t), PP_GET_TYPE(u)>;
	}};
}
