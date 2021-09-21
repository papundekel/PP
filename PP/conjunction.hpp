#pragma once
#include "wrap.hpp"

namespace PP
{
constexpr auto operator&&(concepts::wrap auto&& f, concepts::wrap auto&& g)
{
	return functor(
	    [f = unwrap_functor(PP_F(f)),
	     g = unwrap_functor(PP_F(g))](auto&&... args) -> decltype(auto)
	    {
		    return unwrap(f)(PP_F(args)...) && unwrap(g)(PP_F(args)...);
	    });
}
}
