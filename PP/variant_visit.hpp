#pragma once
#include <variant>

#include "forward_wrap.hpp"
#include "functional/functor.hpp"
#include "reference_wrapper.hpp"

namespace PP
{
	PP_FUNCTOR(variant_visit, auto&& f, auto&& variant) -> decltype(auto)
	{
		return std::visit(functor(PP_FORWARD_WRAP(f)) | unref, PP_FORWARD(variant));
	});
}
