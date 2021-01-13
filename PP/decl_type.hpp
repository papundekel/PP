#pragma once
#include "type_t.hpp"
#include "functional/functor.hpp"

namespace PP
{
	PP_FUNCTOR(decl_type_copy, auto v)
	{
		return PP_DECLTYPE(v);
	}};
	PP_FUNCTOR(decl_type, auto&& v)
	{
		return PP_DECLTYPE(v);
	}};
}
