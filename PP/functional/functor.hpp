#pragma once
#include "../forward.hpp"

namespace PP
{
	constexpr inline struct partial_tag_t { static constexpr char THIS_IS_STUPID = {}; } partial_tag;
	
	template <typename F>
	struct functor
	{
		F f;

		constexpr decltype(auto) operator()() const&
		requires requires { f(); }
		{
			return f();
		}
		constexpr decltype(auto) operator()() const&&
		requires requires { std::move(f)(); }
		{
			return std::move(f)();
		}
		constexpr decltype(auto) operator()(auto&& arg, auto&&... args) const&
		requires (!requires { arg.THIS_IS_STUPID; }) && requires { f(PP_FORWARD(arg), PP_FORWARD(args)...); }
		{
			return f(PP_FORWARD(arg), PP_FORWARD(args)...);
		}
		constexpr decltype(auto) operator()(auto&& arg, auto&&... args) const&&
		requires (!requires { arg.THIS_IS_STUPID; }) && requires { std::move(f)(PP_FORWARD(arg), PP_FORWARD(args)...); }
		{
			return std::move(f)(PP_FORWARD(arg), PP_FORWARD(args)...);
		}

		constexpr auto operator()(partial_tag_t, auto&&... args) const&;
		constexpr auto operator()(partial_tag_t, auto&&... args) const&&;

		constexpr decltype(auto) operator[](auto&& tuple) const&;
		constexpr decltype(auto) operator[](auto&& tuple) const&&;

		static constexpr char arbitrary_concept_tag_functor = {};
	};
	
	template <typename F>
	concept is_functor = requires(F f)
	{
		f.arbitrary_concept_tag_functor;
	};

	constexpr decltype(auto) operator<<=(is_functor auto&& f, auto&& arg)
	{
		return PP_FORWARD(f)(PP_FORWARD(arg));
	}

	constexpr auto operator&&(is_functor auto&& f, is_functor auto&& g)
	{
		return functor{ [f = PP_FORWARD(f).f, g = PP_FORWARD(g).f](auto&&... args) -> decltype(auto)
			{
				return f(PP_FORWARD(args)...) && g(PP_FORWARD(args)...);
			}};
	}
	constexpr auto operator||(is_functor auto&& f, is_functor auto&& g) -> decltype(auto)
	{
		return functor{ [f = PP_FORWARD(f).f, g = PP_FORWARD(g).f](auto&&... args) -> decltype(auto)
			{
				return f(PP_FORWARD(args)...) || g(PP_FORWARD(args)...);
			}};
	}

	#define PP_FUNCTOR(name, ...) constexpr inline ::PP::functor name{[](__VA_ARGS__)
}
