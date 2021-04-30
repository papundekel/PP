#pragma once
#include <compare>

#include "functional/functor.hpp"

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

	constexpr bool operator&(cv_qualifier a, cv_qualifier b) noexcept
	{
		return (cv_qualifier_underlying)a & (cv_qualifier_underlying)b;
	}

	constexpr auto operator|(cv_qualifier a, cv_qualifier b) noexcept
	{
		return cv_qualifier((cv_qualifier_underlying)a |
							(cv_qualifier_underlying)b);
	}

	PP_FUNCTOR(cv_is_const, cv_qualifier q)
	{
		return q & cv_qualifier::Const;
	});

	PP_FUNCTOR(cv_is_volatile, cv_qualifier q)
	{
		return q & cv_qualifier::Volatile;
	});

	constexpr std::partial_ordering operator<=>(cv_qualifier a,
												cv_qualifier b) noexcept
	{
		auto ai = (cv_qualifier_underlying)a;
		auto bi = (cv_qualifier_underlying)b;

		if (ai == bi)
			return std::partial_ordering::equivalent;
		else if (ai == 0 || bi == 3)
			return std::partial_ordering::less;
		else if (bi == 0 || ai == 3)
			return std::partial_ordering::greater;
		else
			return std::partial_ordering::unordered;
	}
}
