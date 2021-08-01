#pragma once
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "functor_concept.hpp"
#include "get_value.hpp"
#include "wrap.hpp"

namespace PP
{
PP_FUNCTOR(apply_partially_first, auto&& f, auto&& arg)
{
	return functor(
	    [f = PP_F(f), a = PP_F(arg)](auto&&... other_args) -> decltype(auto)
	    {
		    return unwrap_forward(f)(unwrap_forward(a), PP_F(other_args)...);
	    });
});
}

constexpr auto operator*(PP::concepts::wrap auto&& f, auto&& arg) noexcept
{
	return PP::apply_partially_first(PP_UF(f), PP_F(arg));
}
