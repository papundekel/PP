#pragma once
#include "functor.hpp"

namespace PP
{
	PP_FUNCTOR(compose, auto&& f, auto&& g)
	{
		return functor{
			[f = PP_FORWARD(f), g = PP_FORWARD(g)](auto&&... args) -> decltype(auto)
			{
				return f(g(PP_FORWARD(args)...));
			}};
	}};

	template <typename F, typename G>
	constexpr auto operator|(const functor<F>& f, const functor<G>& g)
	{
		return compose(f.f, g.f);
	}
	template <typename F, typename G>
	constexpr auto operator|(const functor<F>& f, const functor<G>&& g)
	{
		return compose(f.f, std::move(g).f);
	}
	template <typename F, typename G>
	constexpr auto operator|(const functor<F>&& f, const functor<G>& g)
	{
		return compose(std::move(f).f, g.f);
	}
	template <typename F, typename G>
	constexpr auto operator|(const functor<F>&& f, const functor<G>&& g)
	{
		return compose(std::move(f).f, std::move(g).f);
	}
}
