#pragma once
#include "ptrdiff_t.hpp"

namespace PP
{
	template <typename T>
	struct empty_iterator
	{
		constexpr auto& operator++() noexcept
		{
			return *this;
		}
		constexpr auto& operator--() noexcept
		{
			return *this;
		}
		constexpr auto&& operator*() const noexcept
		{
			return reinterpret_cast<T&&>(const_cast<empty_iterator&>(*this));
		}
		constexpr auto& operator+=(ptrdiff_t) noexcept
		{
			return *this;
		}
		constexpr auto operator+(ptrdiff_t) const noexcept
		{
			return *this;
		}
		constexpr auto&& operator[](ptrdiff_t) const noexcept
		{
			return **this;
		}
		constexpr bool operator==(empty_iterator) const noexcept
		{
			return true;
		}
		constexpr ptrdiff_t operator-(empty_iterator) const noexcept
		{
			return 0;
		}
	};
}
