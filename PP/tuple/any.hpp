#pragma once
#include "../forward_wrap.hpp"
#include "../wrap.hpp"
#include "apply.hpp"

namespace PP::tuple
{
PP_FUNCTOR(any, auto&& pp, concepts::tuple auto&& t) -> decltype(auto)
{
	return functor(
	    [p = PP_FW(pp)](auto&&... e) -> decltype(auto)
	    {
		    return (false || ... || p(PP_F(e)));
	    })[PP_F(t)];
});
}

namespace PP
{
constexpr decltype(auto) operator||(concepts::functor auto&& f,
                                    concepts::tuple auto&& tuple)
{
	return tuple::all(PP_UF(f), PP_F(tuple));
}
}
