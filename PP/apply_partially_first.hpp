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
		[f = unwrap_functor(PP_F(f)),
	     a = unwrap_functor(PP_F(arg))](auto&&... other_args) -> decltype(auto)
		{
			return unwrap(f)(unwrap(a), PP_F(other_args)...);
		});
});

constexpr auto operator*(concepts::wrap auto&& f, auto&& arg) noexcept
{
	return apply_partially_first(unwrap_functor(PP_F(f)),
	                             unwrap_functor(PP_F(arg)));
}
}
