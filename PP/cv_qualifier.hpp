#pragma once

namespace PP
{
	enum class cv_qualifier
	{
		none,
		Const,
		Volatile,
		const_volatile,
	};

	constexpr bool is_const(cv_qualifier q) noexcept
	{
		return q == cv_qualifier::Const || q == cv_qualifier::const_volatile;
	}

	constexpr bool is_volatile(cv_qualifier q) noexcept
	{
		return q == cv_qualifier::Volatile || q == cv_qualifier::const_volatile;
	}

	constexpr bool operator>=(cv_qualifier a, cv_qualifier b) noexcept
	{
		// is_const(b) -> is_const(a) && is_volatile(b) -> is_volatile(a)
		return ((!is_const(b) || is_const(a)) && (!is_volatile(b) || is_volatile(a)));
	}
}
