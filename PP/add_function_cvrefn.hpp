#pragma once
#include "make_function_type.hpp"
#include "get_function_info.hpp"

namespace PP
{
	template <typename F, cv_qualifier cv, ref_qualifier ref, bool Noexcept>
	using add_function_cvrefn = make_function_type
		< typename get_function_info<F>::return_type
		, typename get_function_info<F>::parameter_types
		, Noexcept
		, cv
		, ref>;
}
