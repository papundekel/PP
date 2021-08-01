#pragma once
#include "macros/CIA.hpp"
#include "utility/forward.hpp"
#include "utility/move.hpp"
#include "value_t.hpp"

namespace PP
{
constexpr inline struct partial_tag_t
{
} partial_tag;
}

namespace PP::concepts
{
template <typename T>
concept functor_call_not_partial = !requires(T t)
{
	partial_tag_t{t};
};
}

namespace PP
{
template <typename F>
struct functor
{
	F f;

	constexpr decltype(auto) operator()(auto&&... args) const& requires(
	    concepts::functor_call_not_partial<decltype(args)>&&...) &&
	    requires
	{
		f(PP_F(args)...);
	}
	{
		return f(PP_F(args)...);
	}
	constexpr decltype(auto) operator()(auto&&... args) const&& requires(
	    concepts::functor_call_not_partial<decltype(args)>&&...) &&
	    requires
	{
		move(f)(PP_F(args)...);
	}
	{
		return move(f)(PP_F(args)...);
	}

	constexpr auto operator()(partial_tag_t,
	                          auto i,
	                          auto&& arg) const& noexcept;
	constexpr auto operator()(partial_tag_t,
	                          auto i,
	                          auto&& arg) const&& noexcept;

	constexpr decltype(auto) operator[](auto&& tuple) const&;
	constexpr decltype(auto) operator[](auto&& tuple) const&&;
};
}

namespace PP::detail
{
template <typename T>
concept functor_helper = requires(T t)
{
	[]<typename F>(const functor<F>&)
	{
	}(t);
};
}

namespace PP
{
constexpr auto&& unwrap_functor_impl(detail::functor_helper auto&& f) noexcept
{
	return PP_F(f).f;
}

#define PP_FUNCTOR(name, ...) PP_CIA name = ::PP::functor([](__VA_ARGS__)
}
