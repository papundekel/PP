#pragma once
#include "declval_impl.hpp"
#include "forward_wrap.hpp"
#include "functor.hpp"
#include "wrap.hpp"

namespace PP
{
PP_FUNCTOR(compose, auto&& f, auto&& g)
{
	return functor(
		[ ff = unwrap_functor(PP_F(f)), gg = unwrap_functor(PP_F(g)) ](
			auto&&... args) -> decltype(auto) requires requires
		{
			unwrap(unwrap_functor(PP_F(f)))(unwrap(PP_F(g))(PP_F(args)...));
		}
		{
			return unwrap(ff)(unwrap(gg)(PP_F(args)...));
		});
});

constexpr auto operator|(concepts::wrap auto&& f, concepts::wrap auto&& g)
{
	return compose(unwrap_functor(PP_F(f)), unwrap_functor(PP_F(g)));
}
}
