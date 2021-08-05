#pragma once
#include <compare>

#include "functor.hpp"

namespace PP
{
using cv_qualifier_underlying = unsigned int;

enum class cv_qualifier : cv_qualifier_underlying
{
	none = 0b00,
	Const = 0b01,
	Volatile = 0b10,
	const_volatile = 0b11
};
}

constexpr bool operator&(PP::cv_qualifier a, PP::cv_qualifier b) noexcept
{
	return (PP::cv_qualifier_underlying)a & (PP::cv_qualifier_underlying)b;
}

constexpr auto operator|(PP::cv_qualifier a, PP::cv_qualifier b) noexcept
{
	return PP::cv_qualifier((PP::cv_qualifier_underlying)a |
	                        (PP::cv_qualifier_underlying)b);
}

namespace PP
{
PP_FUNCTOR(cv_is_const, cv_qualifier q)
{
	return q & cv_qualifier::Const;
});

PP_FUNCTOR(cv_is_volatile, cv_qualifier q)
{
	return q & cv_qualifier::Volatile;
});
}

constexpr std::partial_ordering operator<=>(PP::cv_qualifier a,
                                            PP::cv_qualifier b) noexcept
{
	auto ai = (PP::cv_qualifier_underlying)a;
	auto bi = (PP::cv_qualifier_underlying)b;

	if (ai == bi)
		return std::partial_ordering::equivalent;
	else if (ai == 0 || bi == 3)
		return std::partial_ordering::less;
	else if (bi == 0 || ai == 3)
		return std::partial_ordering::greater;
	else
		return std::partial_ordering::unordered;
}
