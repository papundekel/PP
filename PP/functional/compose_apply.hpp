#pragma once
#include "../tuple_apply.hpp"
#include "../tuple_like.hpp"
#include "compose.hpp"
#include "id.hpp"

namespace PP
{
	PP_FUNCTOR(compose_apply, auto&& f, auto&& g)
	{
		return functor{ [f = functor{ PP_FORWARD(f) }, g = PP_FORWARD(g)]
			(auto&&... args) -> decltype(auto)
			{
				if constexpr (concepts::tuple<decltype(g(PP_FORWARD(args)...))>)
					return f[g(PP_FORWARD(args)...)];
				else
					return f(g(PP_FORWARD(args)...));
			}};
	}};

	constexpr auto operator^(concepts::functor auto&& f, concepts::functor auto&& g)
	{
		return compose_apply(PP_FORWARD(f).f, PP_FORWARD(g).f);
	}

	constexpr auto operator*(concepts::functor auto&& f)
	{
		return PP_FORWARD(f) ^ id_forward;
	}
}
