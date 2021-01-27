#pragma once
#include "../utility/forward.hpp"

namespace PP
{
	constexpr inline struct partial_tag_t {} partial_tag;
	
	namespace concepts
	{
		template <typename T>
		concept functor_call_not_partial =
			!requires (T t)
			{
				partial_tag_t{ t };
			};
	}

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
		requires concepts::functor_call_not_partial<decltype(arg)> && requires { f(PP_FORWARD(arg), PP_FORWARD(args)...); }
		{
			return f(PP_FORWARD(arg), PP_FORWARD(args)...);
		}
		constexpr decltype(auto) operator()(auto&& arg, auto&&... args) const&&
		requires concepts::functor_call_not_partial<decltype(arg)> && requires { std::move(f)(PP_FORWARD(arg), PP_FORWARD(args)...); }
		{
			return std::move(f)(PP_FORWARD(arg), PP_FORWARD(args)...);
		}

		constexpr auto operator()(partial_tag_t, auto i, auto&& arg) const& noexcept;
		constexpr auto operator()(partial_tag_t, auto i, auto&& arg) const&& noexcept;

		constexpr decltype(auto) operator[](auto&& tuple) const&;
		constexpr decltype(auto) operator[](auto&& tuple) const&&;

		static constexpr char arbitrary_concept_tag_functor = {};
	};
	
	namespace concepts
	{
		template <typename F>
		concept functor = requires(F f)
		{
			f.arbitrary_concept_tag_functor;
		};
	}

	constexpr decltype(auto) operator<<=(concepts::functor auto&& f, auto&& arg)
	{
		return PP_FORWARD(f)(PP_FORWARD(arg));
	}

	constexpr auto operator&&(concepts::functor auto&& f, concepts::functor auto&& g)
	{
		return functor{ [f = PP_FORWARD(f).f, g = PP_FORWARD(g).f]
			(auto&&... args) -> decltype(auto)
			{
				return f(PP_FORWARD(args)...) && g(PP_FORWARD(args)...);
			}};
	}
	constexpr auto operator||(concepts::functor auto&& f, concepts::functor auto&& g) -> decltype(auto)
	{
		return functor{ [f = PP_FORWARD(f).f, g = PP_FORWARD(g).f]
			(auto&&... args) -> decltype(auto)
			{
				return f(PP_FORWARD(args)...) || g(PP_FORWARD(args)...);
			}};
	}

	#define PP_FUNCTOR(name, ...) constexpr inline ::PP::functor name{[](__VA_ARGS__)
}
