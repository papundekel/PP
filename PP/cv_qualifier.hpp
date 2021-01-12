#pragma once
#include <type_traits>
#include <cstdint>

#include "functional/apply_partially.hpp"
#include "functional/compose.hpp"

namespace PP
{
	namespace detail
	{
		using cv_qualifier_t = std::uint_fast8_t;
	}

	enum class cv_qualifier : detail::cv_qualifier_t
	{
		none = 0b00,
		Const = 0b01,
		Volatile = 0b10,
		const_volatile = 0b11,
	};

	constexpr bool operator&(cv_qualifier a, cv_qualifier b) noexcept
	{
		return (detail::cv_qualifier_t)a & (detail::cv_qualifier_t)b;
	}

	namespace detail
	{
		constexpr inline auto bool_to_int = [](bool p) { return p ? 1 : 0; };
	}

	//constexpr inline auto is_const_v = detail::bool_to_int | apply_partially(map_v, template_v<std::is_const>);
	//constexpr inline auto is_volatile_v = detail::bool_to_int | apply_partially(map_v, template_v<std::is_volatile>);

	constexpr bool is_const(cv_qualifier q) noexcept
	{
		return q & cv_qualifier::Const;
	}

	constexpr bool is_volatile(cv_qualifier q) noexcept
	{
		return q & cv_qualifier::Volatile;
	}

	constexpr bool operator>=(cv_qualifier a, cv_qualifier b) noexcept
	{
		// is_const(b) -> is_const(a) && is_volatile(b) -> is_volatile(a)
		return ((!is_const(b) || is_const(a)) && (!is_volatile(b) || is_volatile(a)));
	}
}
