#pragma once
#include "functor.hpp"

namespace PP
{
	namespace detail
	{
		template <typename T>
		constexpr T&& declval_() noexcept;
		template <typename F, typename G, typename... Args>
		concept compose_concept = requires
		{
			declval_<F>()(declval_<G>()(declval_<Args>()...));
		};
	}
	
	PP_FUNCTOR(compose, auto&& f, auto&& g)
	{
		return functor([f = PP_FORWARD(f), g = PP_FORWARD(g)]
			(auto&&... args) -> decltype(auto)
			requires detail::compose_concept<decltype(f), decltype(g), decltype(args)...>
			{
				return f(g(PP_FORWARD(args)...));
			});
	});

	constexpr auto operator|(concepts::functor auto&& f, concepts::functor auto&& g)
	{
		return compose(unwrap_functor(PP_FORWARD(f)), unwrap_functor(PP_FORWARD(g)));
	}
}
