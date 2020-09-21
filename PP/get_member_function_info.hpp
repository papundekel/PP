#pragma once
#include "get_function_info.hpp"
#include "add_cv.hpp"
#include "add_ref.hpp"

namespace PP
{
	template <typename T>
	struct get_member_function_info {};
	template <typename F, typename C>
	struct get_member_function_info<F C::*>
	{
		using Function = F;
		using Class = C;
		using Caller = add_ref_t<get_function_info<F>::ref, add_cv_t<get_function_info<F>::cv, C>>;
	};
}
