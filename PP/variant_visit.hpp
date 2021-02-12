#pragma once
#include <variant>

#include "reference_wrapper.hpp"

namespace PP
{
	PP_FUNCTOR(variant_visit, auto&& f, auto&& variant) -> decltype(auto)
	{
		return std::visit(functor{ ref(f) } | unref, PP_FORWARD(variant));
	}};
}
