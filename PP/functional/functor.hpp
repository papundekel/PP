#pragma once
#include "../utility/forward.hpp"
#include "../utility/move.hpp"

namespace PP
{
	constexpr inline struct partial_tag_t
	{
	} partial_tag;

	namespace concepts
	{
		template <typename T>
		concept functor_call_not_partial = !requires(T t)
		{
			partial_tag_t{t};
		};
	}

	template <typename F>
	struct functor
	{
		F f;

#ifdef __clang__
		constexpr functor(auto&& f)
			: f(PP_FORWARD(f))
		{}
#endif

		constexpr decltype(auto) operator()(auto&&... args) const& requires(
			concepts::functor_call_not_partial<decltype(args)>&&...) &&
			requires
		{
			f(PP_FORWARD(args)...);
		}
		{
			return f(PP_FORWARD(args)...);
		}
		constexpr decltype(auto) operator()(auto&&... args) const&& requires(
			concepts::functor_call_not_partial<decltype(args)>&&...) &&
			requires
		{
			move(f)(PP_FORWARD(args)...);
		}
		{
			return move(f)(PP_FORWARD(args)...);
		}

		constexpr auto operator()(partial_tag_t,
								  auto i,
								  auto&& arg) const& noexcept;
		constexpr auto operator()(partial_tag_t,
								  auto i,
								  auto&& arg) const&& noexcept;

		constexpr decltype(auto) operator[](auto&& tuple) const&;
		constexpr decltype(auto) operator[](auto&& tuple) const&&;

		static constexpr char arbitrary_concept_tag_functor = {};
	};

#ifdef __clang__
	template <typename F>
	functor(F) -> functor<F>;
#endif

	namespace concepts
	{
		template <typename F>
		concept functor = requires(F f)
		{
			f.arbitrary_concept_tag_functor;
		};
	}

	constexpr auto&& unwrap_functor(auto&& f)
	{
		if constexpr (concepts::functor<decltype(f)>)
			return unwrap_functor(PP_FORWARD(f).f);
		else
			return PP_FORWARD(f);
	}

	constexpr decltype(auto) operator<<=(concepts::functor auto&& f, auto&& arg)
	{
		return unwrap_functor(PP_FORWARD(f))(PP_FORWARD(arg));
	}

	constexpr auto operator&&(concepts::functor auto&& f,
							  concepts::functor auto&& g)
	{
		return functor(
			[f = unwrap_functor(PP_FORWARD(f)),
			 g = unwrap_functor(PP_FORWARD(g))](
				auto&&... args) -> decltype(auto)
			{
				return f(PP_FORWARD(args)...) && g(PP_FORWARD(args)...);
			});
	}
	constexpr auto operator||(concepts::functor auto&& f,
							  concepts::functor auto&& g) -> decltype(auto)
	{
		return functor(
			[f = unwrap_functor(PP_FORWARD(f)),
			 g = unwrap_functor(PP_FORWARD(g))](
				auto&&... args) -> decltype(auto)
			{
				return f(PP_FORWARD(args)...) || g(PP_FORWARD(args)...);
			});
	}

#define PP_FUNCTOR(name, ...) constexpr inline auto name = ::PP::functor([](__VA_ARGS__)
}
