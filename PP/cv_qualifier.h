#pragma once

enum class cv_qualifier
{
	none,
	const_,
	volatile_,
	const_volatile,
};

constexpr bool is_const(cv_qualifier q) noexcept
{
	return q == cv_qualifier::const_ || q == cv_qualifier::const_volatile;
}

constexpr bool is_volatile(cv_qualifier q) noexcept
{
	return q == cv_qualifier::volatile_ || q == cv_qualifier::const_volatile;
}
