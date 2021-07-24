#pragma once
#include "decl_type.hpp"
#include "functor.hpp"
#include "get_type.hpp"
#include "overloaded.hpp"
#include "value_t.hpp"

namespace PP
{
namespace detail
{
template <typename T>
concept has_value_f = requires
{
	T::value_f();
};
template <typename T>
concept has_value = !has_value_f<T> && requires
{
	T::value;
};
}

namespace concepts
{
template <typename T>
concept value = detail::has_value_f<T> || detail::has_value<T>;
}

constexpr inline auto get_type_value = make_overloaded_pack(
	[](auto t) -> decltype(auto) requires detail::has_value_f<PP_GT(t)>
	{
		return PP_GT(t)::value_f();
	},
	[](auto t) -> decltype(auto) requires detail::has_value<PP_GT(t)>
	{
		return (PP_GT(t)::value);
	});

constexpr inline auto get_value = get_type_value | decl_type_copy;

constexpr decltype(auto) operator*(concepts::value auto v) noexcept
{
	return get_value(v);
}

constexpr decltype(auto) operator-(
	concepts::type auto t) noexcept requires requires
{
	get_type_value(t);
}
{
	return get_type_value(t);
}

#define PP_GV(x) (-PP_DT(x))
#define PP_CV(x) (::PP::value<PP_GV(x)>)
#define PP_CV_MEMBER(x, member) (::PP::value<PP_GV(x).member>)
#define PP_GV_TYPE(x) PP_DT(PP_GV(x))

constexpr auto operator==(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) == PP_GV(y)>;
}
constexpr auto operator!=(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) != PP_GV(y)>;
}
constexpr auto operator<(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) < PP_GV(y)>;
}
constexpr auto operator<=(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) <= PP_GV(y)>;
}
constexpr auto operator>(concepts::value auto x, concepts::value auto y)
{
	return value<(PP_GV(x) > PP_GV(y))>;
}
constexpr auto operator>=(concepts::value auto x, concepts::value auto y)
{
	return value<(PP_GV(x) >= PP_GV(y))>;
}
constexpr auto operator+(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) + PP_GV(y)>;
}
constexpr auto operator-(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) - PP_GV(y)>;
}
constexpr auto operator*(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) * PP_GV(y)>;
}
constexpr auto operator/(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) / PP_GV(y)>;
}
constexpr auto operator%(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) % PP_GV(y)>;
}
constexpr auto operator&(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) & PP_GV(y)>;
}
constexpr auto operator|(concepts::value auto x, concepts::value auto y)
{
	return value<PP_GV(x) | PP_GV(y)>;
}
constexpr auto operator-(concepts::value auto x)
{
	return value<-PP_GV(x)>;
}
constexpr auto operator!(concepts::value auto x)
{
	return value<!PP_GV(x)>;
}
constexpr auto operator&&(concepts::value auto x, concepts::value auto y)
{
	return value < PP_GV(x) && PP_GV(y) > ;
}
constexpr auto operator||(concepts::value auto x, concepts::value auto y)
{
	return value < PP_GV(x) || PP_GV(y) > ;
}

constexpr auto operator<=(concepts::type auto x,
                          concepts::type auto y) requires requires
{
	-x;
	-y;
}
{
	return -x <= -y;
}

PP_FUNCTOR(to_value_t, concepts::value auto x)
{
	return value<PP_GV(x)>;
});
}
