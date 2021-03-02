#pragma once
#include <iosfwd>

#include "any_view.hpp"
#include "array.hpp"
#include "to_chars.hpp"

namespace PP
{
	constexpr auto make_any_view_chars(const char* b, const char* e)
	{
		return any_view<iterator_category::forward, const char&>(b, e);
	}

	class simple_ostream
	{
		constexpr void write_num(auto number) noexcept
		{
			array<char, 32> buffer;
			auto end = to_chars(buffer, number);
			write(make_any_view_chars(view_begin(buffer), end));
		}

	public:
		constexpr virtual void write(any_view<iterator_category::forward, const char&> view) noexcept = 0;
		void virtual write_to_ostream(std::ostream&) noexcept = 0;

		template <size_t N>
		constexpr void write(const char(&arr)[N]) noexcept
		{
			write(make_any_view_chars(arr, arr + N - 1));
		}
		constexpr void write(long long number) noexcept
		{
			write_num(number);
		}
		constexpr void write(long number) noexcept
		{
			write_num(number);
		}
		constexpr void write(unsigned long number) noexcept
		{
			write_num(number);
		}
		constexpr void write(unsigned long long number) noexcept
		{
			write_num(number);
		}
		constexpr void write_ptr(const void* ptr) noexcept
		{
			write(size_t(ptr));
		}
	};
}
