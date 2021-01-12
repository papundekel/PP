#pragma once
#include "make_function_type.hpp"
#include "function_info.hpp"

namespace PP
{
	constexpr inline auto add_function_cvrefn = []
		< bool N = false
		, cv_qualifier CV = cv_qualifier::none
		, ref_qualifier REF = ref_qualifier::none>
			( auto f
			, value_t<N> Noexcept = {}
			, value_t<CV> cv = {}
			, value_t<REF> ref = {})
		{
			constexpr auto info = function_info(f);
			return make_function_type(info.return_type, info.parameter_types, Noexcept, cv, ref);
		};
}
