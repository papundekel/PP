#pragma once

namespace PP
{
	enum class cv_qualifier : unsigned int
	{
		none = 0b00,
		Const = 0b01,
		Volatile = 0b10,
		const_volatile = 0b11,
	};

	constexpr bool operator&(cv_qualifier a, cv_qualifier b) noexcept
	{
		return (unsigned int)a & (unsigned int)b;
	}

	constexpr auto operator|(cv_qualifier a, cv_qualifier b) noexcept
	{
		return cv_qualifier((unsigned int)a | (unsigned int)b);
	}

	namespace detail
	{
		constexpr inline auto bool_to_int = [](bool p) { return p ? 1 : 0; };
	}

	constexpr bool cv_is_const(cv_qualifier q) noexcept
	{
		return q & cv_qualifier::Const;
	}

	constexpr bool cv_is_volatile(cv_qualifier q) noexcept
	{
		return q & cv_qualifier::Volatile;
	}

	constexpr bool operator>=(cv_qualifier a, cv_qualifier b) noexcept
	{
		// cv_is_const(b) -> cv_is_const(a) && cv_is_volatile(b) -> cv_is_volatile(a)
		return ((!cv_is_const(b) || cv_is_const(a)) && (!cv_is_volatile(b) || cv_is_volatile(a)));
	}
}
