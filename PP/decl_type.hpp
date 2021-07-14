#pragma once
#include "functor.hpp"
#include "type_t.hpp"

namespace PP
{
	PP_FUNCTOR(decl_type_copy, auto v)
	{
		return PP_DECLTYPE(v);
	});
	PP_FUNCTOR(decl_type_forward, auto&& v)
	{
		return PP_DECLTYPE(v);
	});
}
