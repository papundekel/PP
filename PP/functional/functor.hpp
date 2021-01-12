#pragma once
#include "../forward.hpp"

namespace PP
{
	constexpr inline struct partial_tag_t {} partial_tag;
	
	template <typename F>
	struct functor
	{
		F f;

		constexpr decltype(auto) operator()(auto&&... args) const&
		{
			return f(PP_FORWARD(args)...);
		}
		constexpr decltype(auto) operator()(auto&&... args) const&&
		{
			return std::move(f)(PP_FORWARD(args)...);
		}

		constexpr auto operator()(partial_tag_t, auto&&... args) const&;
		constexpr auto operator()(partial_tag_t, auto&&... args) const&&;

		constexpr decltype(auto) operator[](auto&& tuple) const&;
		constexpr decltype(auto) operator[](auto&& tuple) const&&;
	};

	#define PP_FUNCTOR(name, ...) constexpr inline ::PP::functor name{[](__VA_ARGS__)
}
