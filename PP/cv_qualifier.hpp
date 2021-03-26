#pragma once
#include "functional/functor.hpp"

namespace PP
{
	enum class cv_qualifier : unsigned int
	{
		none = 0b00,
		Const = 0b01,
		Volatile = 0b10,
		const_volatile = 0b11
	};

	constexpr bool operator&(cv_qualifier a, cv_qualifier b) noexcept
	{
		return (unsigned int)a & (unsigned int)b;
	}

	constexpr auto operator|(cv_qualifier a, cv_qualifier b) noexcept
	{
		return cv_qualifier((unsigned int)a | (unsigned int)b);
	}

	PP_FUNCTOR(cv_is_const, cv_qualifier q)
	{
		return q & cv_qualifier::Const;
	});

	PP_FUNCTOR(cv_is_volatile, cv_qualifier q)
	{
		return q & cv_qualifier::Volatile;
	});

	constexpr bool operator>=(cv_qualifier a, cv_qualifier b) noexcept
	{
		return ((!cv_is_const(b) || cv_is_const(a)) && (!cv_is_volatile(b) || cv_is_volatile(a)));
	}
	constexpr bool operator==(cv_qualifier a, cv_qualifier b) noexcept
	{
		return (unsigned int)a == (unsigned int)b;
	}
	constexpr bool operator>(cv_qualifier a, cv_qualifier b) noexcept
	{
		return a >= b && a != b;
	}
}
